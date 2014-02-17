//------------------------------------------------------------------------------
//-- ModularRobot
//------------------------------------------------------------------------------
//--
//-- Base class for different types of modular robots for modular robotics
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

#ifndef MODULAR_ROBOT_H
#define MODULAR_ROBOT_H

#include <utility>
#include <inttypes.h>

#include "Module.h"

class ModularRobot
{
    public:
        ModularRobot();
        ~ModularRobot();

        //-- Robot interface:
        void run();
        void reset();

        //-- Timing
        void setTimeStep( uint32_t time_step_ms );
        void setMaxRuntime( uint32_t max_runtime_ms); //-- Simulation-only

        //-- Distance / position
        std::pair<float, float> getPosXY;
        double getDistanceTravelled();
        uint32_t getTimeElapsed();
        void selectDistanceCalculationMethod( bool integratePath );

        //-- Constants
        static const bool START_END_POINTS = false;
        static const bool INTEGRATE_PATH = true;

    protected:
        //-- System timer:
        virtual void updateTime() = 0;
        static void * updateTimeThread( void * This);
        pthread_t updateTime_pthread;
        uint32_t max_runtime_ms; //-- Simulation only
        uint32_t time_step_ms;
        float time_step_s;

        //-- Modules
        std::vector<Module *> modules;

        //-- Position / velocity variables
        virtual void calculatePos() = 0;
        void calculateDistanceTravelled();

        std::pair<float, float> start_pos;
        std::pair<float, float> current_pos;
        std::pair<float, float> last_pos;
        double distance_travelled;
        uint32_t time_elapsed;
        bool distance_calculation_method;
};
#endif //-- MODULAR_ROBOT_H
