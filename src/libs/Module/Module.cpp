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
Module::Module(uint8_t num_servos, GaitTable* gait_table_shape,  GaitTable* gait_table_limbs,
                       pthread_mutex_t* gait_table_shape_mutex, pthread_mutex_t* gait_table_limbs_mutex )
{

    //-- Create servos:
    this->num_servos = num_servos;
    this->servos = NULL;

    //-- Set default values for variables:
    this->gait_table_shape = gait_table_shape;
    this->gait_table_limbs = gait_table_limbs;

    this->oscillator = new SinusoidalOscillator( 0, 0, 0, OSCILLATOR_PERIOD);


    //-- ID initialization
    id_function = ModuleFunction_none;
    id_depth = 0;
    id_shape = -1;
    id_num_limbs = -1;
    id_limb = 0;

    this->internal_time = 0;

    //-- Init mutexes
    pthread_mutex_init( &id_function_mutex, NULL);
    pthread_mutex_init( &id_depth_mutex, NULL);
    pthread_mutex_init( &id_shape_mutex, NULL);
    pthread_mutex_init( &id_num_limbs_mutex, NULL);
    pthread_mutex_init( &id_limb_mutex, NULL);
    pthread_mutex_init( &oscillator_mutex, NULL);

    //-- Gait tables
    this->gait_table_limbs = gait_table_limbs;
    this->gait_table_limbs_mutex = gait_table_limbs_mutex;
    this->gait_table_shape = gait_table_shape;
    this->gait_table_shape_mutex = gait_table_shape_mutex;

}

Module::~Module()
{
    //-- Free memory:
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
    id_shape = -1;
    id_num_limbs = -1;
    id_limb = 0;
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

void Module::setShapeID(unsigned long id_shape)
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

void Module::setLimbID(int id_limb)
{
    pthread_mutex_lock(&id_limb_mutex);
    this->id_limb = id_limb;
    pthread_mutex_unlock(&id_limb_mutex);

    runController();
}

void Module::setIDs(ModuleFunction id_function, int id_depth, unsigned long id_shape,
                    int id_num_limbs, int id_limb)
{
    setFunctionID(id_function);
    setDepthID(id_depth);
    setShapeID(id_shape);
    setNumLimbsID(id_num_limbs);
    setLimbID(id_limb);
}


uint32_t Module::localtime()
{
    return internal_time + adjust_time;
}

//-- Load gait table
//----------------------------------------------------------------------------------
void Module::loadGaitTable()
{
    pthread_mutex_lock(gait_table_shape_mutex);
    gait_table_shape->reload();
    pthread_mutex_unlock(gait_table_shape_mutex);

    pthread_mutex_lock(gait_table_limbs_mutex);
    gait_table_limbs->reload();
    pthread_mutex_unlock(gait_table_limbs_mutex);
}


//-- Controller main functions
//----------------------------------------------------------------------------------
void Module::runController()
{

    pthread_mutex_lock( &id_shape_mutex);
    pthread_mutex_lock( &id_num_limbs_mutex);
    bool valid_id = id_shape != -1 && id_num_limbs != -1;
    pthread_mutex_unlock( &id_num_limbs_mutex);
    pthread_mutex_unlock( &id_shape_mutex);

    if (valid_id)
    {
        float newAmplitude, newOffset, newPhase, newFrequency;
        newAmplitude = newOffset = newPhase = newFrequency = 0;

        //-- Recalculate oscillator parameters according to the current state
        //! \todo Calculate actual parameters
        pthread_mutex_lock(gait_table_shape_mutex);
        pthread_mutex_lock( &id_shape_mutex);

        float baseAmplitude = gait_table_shape->at(id_shape, AMPLITUDE);
        float baseOffset = gait_table_shape->at(id_shape, OFFSET);
        float basePhase = gait_table_shape->at(id_shape, PHASE);

        pthread_mutex_unlock(gait_table_shape_mutex);
        pthread_mutex_unlock( &id_shape_mutex);


        pthread_mutex_lock(gait_table_limbs_mutex);
        pthread_mutex_lock( &id_num_limbs_mutex);

        newFrequency = gait_table_limbs->at(id_num_limbs, FREQUENCY);
        float alpha = gait_table_limbs->at(id_num_limbs, ALPHA);
        float omega = gait_table_limbs->at(id_num_limbs, OMEGA);
        float phi = gait_table_limbs->at(id_num_limbs, PHI);
        float limbPhase = gait_table_limbs->at(id_num_limbs, PHASE_LIMB);

        pthread_mutex_unlock(gait_table_limbs_mutex);
        pthread_mutex_unlock( &id_num_limbs_mutex);


        pthread_mutex_lock( &id_function_mutex);
        if (id_limb == ModuleFunction_limb)
        {
            pthread_mutex_lock( &id_depth_mutex);
            pthread_mutex_lock( &id_limb_mutex);

            newAmplitude = baseAmplitude*pow(id_depth, alpha);
            newOffset = baseOffset*pow(id_depth, omega);
            newPhase = basePhase + phi*id_depth + limbPhase*id_limb;

            pthread_mutex_unlock( &id_depth_mutex);
            pthread_mutex_unlock( &id_limb_mutex);
        }
        else
        {
            newAmplitude = baseAmplitude;
            newOffset = baseOffset;
            newPhase = basePhase;
        }
        pthread_mutex_unlock( &id_function_mutex);


        //-- Lock the oscillator mutex
        pthread_mutex_lock(&oscillator_mutex);

        //-- Set the new values on the oscillator
        oscillator->setAmplitude(newAmplitude);
        oscillator->setOffset(newOffset);
        oscillator->setPhase(newPhase);
        oscillator->setPeriod(1/newFrequency);

        //-- Unlock the oscillator mutex
        pthread_mutex_unlock(&oscillator_mutex);
    }
    else
    {
        std::cerr << "[Module] Error: id not initialized" << std::endl;
    }
    pthread_mutex_unlock( &id_shape_mutex);
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
