//------------------------------------------------------------------------------
//-- Controller
//------------------------------------------------------------------------------
//--
//-- Distributed hormone-based controller for modular robotics
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

/*! \file Controller.h
 *  \brief Distributed hormone-based controller for modular robotics
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 27th, 2013
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

//-- General includes
#include <stdint.h>
#include <iostream>
#include <string>


//-- Hormodular includes
#include "Oscillator.h"
#include "SinusoidalOscillator.h"
#include "GaitTable.h"

//-- Module interface
#include "../Module/Servo.h"


/*! \class Controller
 *  \brief Distributed hormone-based controller for modular robotics
 */
class Controller
{
    public:
        //-- Constructors & destructor
        Controller( Servo * servos, std::string gait_table_file, uint32_t * time);
        ~Controller();

        //-- Setup functions
        //int run( uint32_t run_time_ms = 0); //-- Deprecated
        void reset();

        //! \brief Loads a gait table from file:
        void loadGaitTable();

        //-- Controller main functions:
        void runOscillator();
        void syncMechanism();
        void morphFinder();
        void sensorDataManagement();
        void hormoneQueueManagement();

        //! \brief Returns the local time at the current module (for internal calculations)
        uint32_t localtime();

private:

        //! \brief Recalculates oscillator parameters as a function of the module current state
        void runController();

        Servo * servos;

        uint8_t id;
        pthread_mutex_t id_mutex;

        uint32_t * internal_time;
        int32_t adjust_time;

        Oscillator * oscillator;
        pthread_mutex_t oscillator_mutex;

        std::string gait_table_file;
        GaitTable * control_table;

};

#endif
