//------------------------------------------------------------------------------
//-- SimulatedModularRobotInterface
//------------------------------------------------------------------------------
//--
//-- Interface to the simulated robot
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

#ifndef SIMULATED_MODULAR_ROBOT_INTERFACE_H
#define SIMULATED_MODULAR_ROBOT_INTERFACE_H

#include "ModularRobotInterface.hpp"
#include "SimulationOpenRAVE.hpp"
#include "ConfigParser.h"

namespace hormodular {

class SimulatedModularRobotInterface : public ModularRobotInterface
{
    public:
        SimulatedModularRobotInterface( ConfigParser configParser);

        virtual bool start();
        virtual bool stop();
        virtual bool destroy();
        virtual bool reset();

        virtual bool setProperty(std::string property, std::string value);

        virtual float getTravelledDistance();
        virtual bool sendJointValues(std::vector<float> joint_values, float step_ms=0);
        virtual std::vector<float> getJointValues();

    private:
        SimulationOpenRAVE * simulation;
        std::string environment_file;
        OpenRAVE::ControllerBasePtr controller;

        int step_ms;
        double step_s;

        //-- Position-related things:
        void calculatePos();

        std::pair<float, float> start_pos;
        std::pair<float, float> current_pos;

        //-- Tracking position
        std::vector<OpenRAVE::Vector> pos;

};

}

#endif
