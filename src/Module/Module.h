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

#ifndef MODULE_H
#define MODULE_H

//-- General includes
#include <stdint.h>
#include <iostream>
#include <string>
#include <pthread.h>
#include <semaphore.h>

//-- Hormodular includes
#include "Servo.h"

#include "../Controller/Oscillator.h"
#include "../Controller/SinusoidalOscillator.h"
#include "../Controller/GaitTable.h"
#include "../Controller/Controller.h"

//#define DEBUG_MESSAGES

class Module
{
    public:
        ~Module();

        //-- Controller main interface
        void run(uint32_t time);
        void reset();

        //-- Timing interface (to simulate internal timers)
        uint32_t * getTimePtr();
        void incrementTime( int timeIncrement);
        void setMaxRuntime( uint32_t max_runtime);

        //-- Set id manually (only for testing)
        void setID( uint8_t id);

        //! \brief Returns the local time at the current module (for internal calculations)
        uint32_t localtime();

        //! \brief Loads a gait table from file:
        void loadGaitTable();

        //-- Controller main functions:
        void runController();
        void runOscillator();
        void syncMechanism();
        void morphFinder();
        void sensorDataManagement();
        void hormoneQueueManagement();

        //-- Semaphore interface
//        sem_t * getUpdateTimeSemaphore();
//        sem_t * getServoWriteSemaphore();

   protected:
        Module(uint8_t num_servos, std::string gait_table_file);

        //-- Servos
        Servo * servos;
        uint8_t num_servos;

   private:
        Module();

        //-- Controller (deprecated)
        //Controller * controller;

        //-- Module id (shape+pos id)
        uint8_t id;
        pthread_mutex_t id_mutex;

        //-- Timing
        uint32_t internal_time;
        int32_t adjust_time;
        uint32_t max_runtime;

        //-- Oscillator
        Oscillator * oscillator;
        pthread_mutex_t oscillator_mutex;
        static const float OSCILLATOR_PERIOD = 2000;

        //-- Control table(s)
        std::string gait_table_file;
        GaitTable * control_table;

        //-- Threads
        pthread_t oscillator_thread;

        //-- Static thread wrappers
        static void * runOscillatorThread( void * This);

        //-- Semaphores for sync simulation
//        sem_t * updateTimeSemaphore;
//        sem_t * servoWriteSemaphore;
};

//-- Thread wrappers:
//struct RunOscillatorArgs {
//        //Controller * controller;
//        //uint32_t * time;
//        uint32_t max_time;
//};

//void * runOscillatorHelper( void * args);

#endif //-- MODULE_H
