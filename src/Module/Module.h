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

//-- Hormodular includes
#include "Servo.h"
#include "SimulatedServo.h"

#include "../Controller/Oscillator.h"
#include "../Controller/SinusoidalOscillator.h"
#include "../Controller/GaitTable.h"
#include "../Controller/Controller.h"

enum ModuleType { SimulatedModule, SerialPortRobot };

class Module
{
    public:
        Module(ModuleType type, uint8_t num_servos, std::string gait_table_file , OpenRAVE::ControllerBasePtr openRave_pcontroller);
        ~Module();

        //-- Controller main interface
        void run(uint32_t time);
        void reset();

        //-- Timing interface (to simulate internal timers)
        uint32_t * getTimePtr();
        void incrementTime( int timeIncrement);
        void setMaxRuntime( uint32_t max_runtime);

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

   private:
        Module();

        //-- Servos
        Servo * servos;
        uint8_t num_servos;

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

        //-- Control table(s)
        std::string gait_table_file;
        GaitTable * control_table;

        //-- Thread pointers (why?)
        pthread_t oscillator_process;

        //-- Static thread wrappers
        static void * runOscillatorThread( void * This);
};

//-- Thread wrappers:
//struct RunOscillatorArgs {
//        //Controller * controller;
//        //uint32_t * time;
//        uint32_t max_time;
//};

//void * runOscillatorHelper( void * args);

#endif //-- MODULE_H
