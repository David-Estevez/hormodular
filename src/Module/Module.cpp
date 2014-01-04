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
Module::Module(ModuleType type, uint8_t num_servos, std::string gait_table_file, OpenRAVE::ControllerBasePtr openRave_pcontroller, sem_t * update_time_sem, std::vector<sem_t*> current_servo_sem)
{

    //-- Create servos:
    this->num_servos = num_servos;

    if ( type == SimulatedModule )
    {
        SimulatedServo * sim_servos = new SimulatedServo[num_servos];

        for (int i = 0; i < num_servos; i++)
        {
            sim_servos[i].setOpenRaveController( openRave_pcontroller );
            sim_servos[i].setJointID( i );
            sim_servos[i].setSemaphores( update_time_sem, current_servo_sem[0]);
            sim_servos[i].init();
        }

        this->servos = sim_servos;
    }

    //-- Set default values for variables:
    this->gait_table_file = gait_table_file;
    this->oscillator = new SinusoidalOscillator( 0, 0, 0, 0);
    this->control_table = new GaitTable( gait_table_file);
    this->id = 0;
    this->internal_time = 0;

    //-- Create mutexes
    pthread_mutex_init( &id_mutex, NULL);
    pthread_mutex_init( &oscillator_mutex, NULL);

    //-- Reset module
    this->reset();

    //-- Create controller:
    //this->controller = new Controller( this->servos, gait_table_file, &this->time );

}

Module::~Module()
{
    //-- Cancel threads & wait for them to finish:
    //pthread_cancel( oscillator_process);
    pthread_join( oscillator_thread, NULL );

    //-- Free memory:
    delete control_table;
    delete oscillator;
    delete[] servos;
}



//-- Main module interface
//---------------------------------------------------------------------------------------

void Module::run(uint32_t time)
{
    //-- Create threads for each of the components:
    pthread_t oscillator_process; //, sync_process, morph_process, hormoneQueue_process;

    //-- Run threads:
    this->max_runtime = time;
    pthread_create( &oscillator_process, NULL, &runOscillatorThread, (void *) this);
}

void Module::reset()
{
    //-- Reset controller
    this->id = 0;
    this->adjust_time = 0; //! \todo make this random to test sync
    this->oscillator->setParameters(0,0,0,0);
    loadGaitTable();

    //-- Run controller once to start oscillator parameters
    this->runController();

    //-- Reset time
    this->internal_time = 0;
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

}

void Module::runOscillator()
{
    //-- Calculate actuator new position
    float angle = oscillator->calculatePos( localtime() );

    //-- Move the servo
    servos[0].write( angle);
}

//-- Semaphore interface
//-----------------------------------------------------------------------------------
//sem_t *Module::getUpdateTimeSemaphore()
//{
//    return &updateTimeSemaphore;
//}

//sem_t *Module::getServoWriteSemaphore()
//{
//    return &servoWriteSemaphore;
//}



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

//void * runOscillatorHelper(void *args)
//{
//    //-- Get parameters
//    struct RunOscillatorArgs * runOscillatorArgs = (struct RunOscillatorArgs *) args;
//    //Controller * controller = runOscillatorArgs->controller;
//    //uint32_t * time = runOscillatorArgs->time;
//    uint32_t max_time = runOscillatorArgs->max_time;

//    //-- Run oscillator
//    while ( controller->localtime() < max_time ){
//        controller->runOscillator();
//        usleep(2000);}

//    return NULL;
//}
