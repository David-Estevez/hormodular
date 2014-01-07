//------------------------------------------------------------------------------
//-- SimulatedModularRobot
//------------------------------------------------------------------------------
//--
//-- Modular robot simulated on OpenRAVE
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

#ifndef SIMULATED_MODULAR_ROBOT_H
#define SIMULATED_MODULAR_ROBOT_H

#include <openrave-core.h>
#include <iostream>
#include <vector>
#include <semaphore.h>

#include "ModularRobot.h"
#include "../Module/SimulatedModule.h"

class SimulatedModularRobot: public ModularRobot
{
    public:
        SimulatedModularRobot( OpenRAVE::RobotBasePtr openRAVE_robot, OpenRAVE::EnvironmentBasePtr penv, std::string gait_table_file);
        ~SimulatedModularRobot();

    private:
        virtual void updateTime();
        virtual void calculatePos();

        OpenRAVE::RobotBasePtr openRAVE_robot;
        OpenRAVE::EnvironmentBasePtr penv;

        //-- Semaphores for syncing:
        sem_t* modules_semaphores;
        sem_t updateTime_semaphore;
};

#endif //--SIMULATED_MODULAR_ROBOT_H
