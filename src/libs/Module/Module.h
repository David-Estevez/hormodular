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

#include "Oscillator.h"
#include "SinusoidalOscillator.h"
#include "GaitTable.h"

//#define DEBUG_MESSAGES

using namespace hormodular;

enum ModuleFunction { ModuleFunction_none = -1,
                      ModuleFunction_limb = 0,
                      ModuleFunction_thorax = 1,
                      ModuleFunction_coxa = 2 };


class Module
{
    public:
        ~Module();

        //-- Controller main interface
        void run(uint32_t time);
        void reset();
        void join();

        //-- Timing interface (to simulate internal timers)
        uint32_t * getTimePtr();
        void incrementTime( int timeIncrement);
        void setMaxRuntime( uint32_t max_runtime);

        //-- Set id manually (only for testing)
        void setFunctionID( ModuleFunction id_function);
        void setDepthID( int id_depth);
        void setShapeID(unsigned long id_shape);
        void setNumLimbsID( int id_num_limbs);
        void setLimbID( int id_limb);
        void setIDs(ModuleFunction id_function, int id_depth, unsigned long id_shape,
                     int id_num_limbs, int id_limb);

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

        //-- Parameters constants:
        static const int AMPLITUDE = 0;
        static const int OFFSET = 1;
        static const int PHASE = 2;
        static const int FREQUENCY = 0;
        static const int ALPHA = 1;
        static const int OMEGA = 2;
        static const int PHI = 3;
        static const int PHASE_LIMB = 4;

   protected:
        Module(uint8_t num_servos, GaitTable* gait_table_shape,  GaitTable* gait_table_limbs,
               pthread_mutex_t* gait_table_shape_mutex, pthread_mutex_t* gait_table_limbs_mutex );

        //-- Servos
        Servo * servos;
        uint8_t num_servos;

   private:
        Module();

        //-- Module ids
        ModuleFunction id_function;
        int id_depth;
        unsigned long id_shape;
        int id_num_limbs;
        int id_limb;

        //-- Id mutexes
        pthread_mutex_t id_function_mutex;
        pthread_mutex_t id_depth_mutex;
        pthread_mutex_t id_shape_mutex;
        pthread_mutex_t id_num_limbs_mutex;
        pthread_mutex_t id_limb_mutex;

        //-- Timing
        uint32_t internal_time;
        int32_t adjust_time;
        uint32_t max_runtime;

        //-- Oscillator
        Oscillator * oscillator;
        pthread_mutex_t oscillator_mutex;
        static const float OSCILLATOR_PERIOD = 2000;

        //-- Control table(s)
        GaitTable * gait_table_shape;
        GaitTable * gait_table_limbs;
        pthread_mutex_t * gait_table_shape_mutex;
        pthread_mutex_t * gait_table_limbs_mutex;

        //-- Threads
        pthread_t oscillator_thread;

        //-- Static thread wrappers
        static void * runOscillatorThread( void * This);
};

#endif //-- MODULE_H
