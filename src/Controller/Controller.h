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

//-- Morphomotion includes
#include "Robot.h"

//-- Hormodular includes
#include "Oscillator.h"
#include "SinusoidalOscillator.h"
#include "GaitTable.h"


/*! \class Controller
 *  \brief Distributed hormone-based controller for modular robotics
 */
class Controller
{
    public:
        Controller();
        Controller( Robot* module );
        //--Controller( const Controller& src_controller );

        ~Controller();

        int run();
        int reset();

        //! \brief Loads a gait table from file:
        int loadGaitTable( const std::string& file_path );

        Robot *getModule() const;
        uint8_t getId() const;
        uint32_t getInternal_time() const;
        int32_t getAdjust_time() const;
        Oscillator *getOscillator() const;
        GaitTable *getControl_table() const;

        void setModule(Robot *value);
        void setId(const uint8_t &value);       
        void setInternal_time(const uint32_t &value);
        void setAdjust_time(const int32_t &value);
        void setOscillator(Oscillator *value);
        void setControl_table(GaitTable *value);



private:
        //! \brief Function mapping the gait table with the oscillator outputs
        int mappingFunction();

        //! \brief Returns the local time at the current module (for internal calculations)
        uint32_t localtime();

        Robot * module;
        uint8_t id;
        uint32_t internal_time;
        int32_t adjust_time;
        Oscillator * oscillator;
        GaitTable * control_table;
};

#endif
