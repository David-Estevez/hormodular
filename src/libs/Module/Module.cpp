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
    this->id = 0;
    this->internal_time = 0;

    //-- Create mutexes
    pthread_mutex_init( &id_mutex, NULL);
    pthread_mutex_init( &oscillator_mutex, NULL);

}

Module::~Module()
{
    //-- Free memory:
    delete control_table;
    delete oscillator;
    //delete[] servos;
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
    this->id = 0;
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

void Module::setID(uint8_t id)
{
    //-- Lock mutex
    pthread_mutex_lock( &id_mutex);

    //-- Change id
    this->id = id;

    //-- Unlock mutex
    pthread_mutex_unlock( &id_mutex);

#ifdef DEBUG_MESSAGES
    //-- Debug message:
    std::cout << "[Debug] ID set to: " << (int) this->id << std::endl;
#endif

    //-- Run controller
    runController();
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
    //-- Lock the oscillator & id mutexes
    pthread_mutex_lock( &oscillator_mutex);
    pthread_mutex_lock( &id_mutex);

    //-- Recalculate oscillator parameters according to the current state
    oscillator->setAmplitude( control_table->at(id, 0) );
    oscillator->setOffset(control_table->at(id, 1));
    oscillator->setPhase( control_table->at(id, 2));

    //-- Unlock the oscillator & id mutexes
    pthread_mutex_unlock( &oscillator_mutex);
    pthread_mutex_unlock(&id_mutex);

#ifdef DEBUG_MESSAGES
    //-- Debug: print parameters
    std::cout << "[Debug] Amplitude for module: " << (int) id << " -> " << control_table->at(id, 0) <<std::endl;
    std::cout << "[Debug] Offset for module: " << (int) id << " -> " << control_table->at(id, 1) <<std::endl;
    std::cout << "[Debug] Phase for module: " << (int) id << " -> " << control_table->at(id, 2) <<std::endl;
#endif
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
