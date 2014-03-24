//------------------------------------------------------------------------------
//-- Module
//------------------------------------------------------------------------------
//--
//-- Base class for different types of modules for modular robotics
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Hormodular project
//-- (https://github.com/David-Estevez/hormodular.git)
//--
//------------------------------------------------------------------------------
//-- Author: David Estevez-Fernandez
//--
//-- Released under the GPL license (more info on LICENSE.txt file)
//------------------------------------------------------------------------------

#include "Module.h"


//-- Constructors & destructors
//------------------------------------------------------------------------------
Module::Module( uint8_t num_servos, std::string gait_table_file)
{

    //-- Create servos:
    this->num_servos = num_servos;
    this->servos = NULL;

    //-- Set default values for variables:
    this->gait_table_file = gait_table_file;
    this->oscillator = new SinusoidalOscillator( 0, 0, 0, OSCILLATOR_PERIOD);
    this->control_table = new GaitTable( gait_table_file);
    id_function = ModuleFunction_none;
    id_depth = 0;
    id_shape = 0;
    id_num_limbs = 0;

    this->internal_time = 0;

    //-- Init mutexes
    pthread_mutex_init( &id_function_mutex, NULL);
    pthread_mutex_init( &id_depth_mutex, NULL);
    pthread_mutex_init( &id_shape_mutex, NULL);
    pthread_mutex_init( &id_num_limbs_mutex, NULL);
    pthread_mutex_init( &oscillator_mutex, NULL);

}

Module::~Module()
{
    //-- Free memory:
    delete control_table;
    delete oscillator;
}


//-- Main module interface
//---------------------------------------------------------------------------------------

void Module::run(uint32_t time)
{
    //-- Run threads:
    this->max_runtime = time;
    pthread_create( &oscillator_thread, NULL, &runOscillatorThread, (void *) this);
    //std::cout << "[Debug] Just run thread: " << oscillator_thread << " from id: " << (int) id << std::endl;
}


void Module::reset()
{
    //-- Wait for threads to finish
    //pthread_join( oscillator_thread, NULL );

    //-- Reset controller
    id_function = ModuleFunction_none;
    id_depth = 0;
    id_shape = 0;
    id_num_limbs = 0;
    this->adjust_time = 0; //! \todo make this random to test sync
    this->oscillator->setParameters(0,0,0, OSCILLATOR_PERIOD);
    loadGaitTable();

    //-- Run controller once to start oscillator parameters
    this->runController();

    //-- Reset time
    this->internal_time = 0;
}

void Module::join()
{
    //std::cout << "[Debug] Joining thread " << oscillator_thread << " from id: " << (int) id << std::endl;

    //-- Wait for all the threads of this module to end
    pthread_join( this->oscillator_thread, NULL);
}



//-- Timing functions
//-----------------------------------------------------------------------------------

uint32_t * Module::getTimePtr()
{
    return &internal_time;
}

void Module::incrementTime(int timeIncrement)
{
    internal_time += timeIncrement;
}

void Module::setMaxRuntime(uint32_t max_runtime)
{
    this->max_runtime = max_runtime;
}

void Module::setFunctionID(ModuleFunction id_function)
{
    pthread_mutex_lock( &id_function_mutex);
    this->id_function = id_function;
    pthread_mutex_unlock( &id_function_mutex);

    runController();
}

void Module::setDepthID(int id_depth)
{
    pthread_mutex_lock(&id_depth_mutex);
    this->id_depth = id_depth;
    pthread_mutex_unlock(&id_depth_mutex);

    runController();
}

void Module::setShapeID(int id_shape)
{
    pthread_mutex_lock(&id_shape_mutex);
    this->id_shape = id_shape;
    pthread_mutex_unlock(&id_shape_mutex);

    runController();
}

void Module::setNumLimbsID(int id_num_limbs)
{
    pthread_mutex_lock(&id_num_limbs_mutex);
    this->id_num_limbs = id_num_limbs;
    pthread_mutex_unlock(&id_num_limbs_mutex);

    runController();
}

void Module::setIDs(ModuleFunction id_function, int id_depth, int id_shape, int id_num_limbs)
{
    setFunctionID(id_function);
    setDepthID(id_depth);
    setShapeID(id_shape);
    setNumLimbsID(id_num_limbs);
}


uint32_t Module::localtime()
{
    return internal_time + adjust_time;
}

//-- Load gait table
//----------------------------------------------------------------------------------
void Module::loadGaitTable()
{
    control_table->loadFromFile( gait_table_file);
}


//-- Controller main functions
//----------------------------------------------------------------------------------
void Module::runController()
{
    float newAmplitude, newOffset, newPhase;
    newAmplitude = newOffset = newPhase = 0;

    //-- Lock the ids mutexes
    pthread_mutex_lock( &id_function_mutex);
    pthread_mutex_lock( &id_depth_mutex);
    pthread_mutex_lock( &id_shape_mutex);

    //-- Recalculate oscillator parameters according to the current state
    newAmplitude = control_table->at(id_shape, 0);
    newOffset = control_table->at(id_shape, 1);
    newOffset = control_table->at(id_shape, 2);

    //-- Unlock the ids mutexes
    pthread_mutex_unlock( &id_function_mutex);
    pthread_mutex_unlock( &id_depth_mutex);
    pthread_mutex_unlock( &id_shape_mutex);

    //-- Lock the oscillator mutex
    pthread_mutex_lock(&oscillator_mutex);

    //-- Set the new values on the oscillator
    oscillator->setAmplitude(newAmplitude);
    oscillator->setOffset(newOffset);
    oscillator->setPhase(newPhase);

    //-- Unlock the oscillator mutex
    pthread_mutex_unlock(&oscillator_mutex);

}


void Module::runOscillator()
{
    //-- Calculate actuator new position
    float angle = oscillator->calculatePos( localtime() );

    //-- Move the servo
    servos[0].write( angle);
}


//-- Thread wrappers
void *Module::runOscillatorThread(void *This)
{
    Module * thisModule = ( Module * ) This;

    //-- Run oscillator
    while ( thisModule->localtime() < thisModule->max_runtime )
    {
        thisModule->runOscillator();
        usleep(2000);
    }

    return NULL;
}
