//------------------------------------------------------------------------------
//-- SimulatedModularRobotSingleThread
//------------------------------------------------------------------------------
//--
//-- Modular robot simulated on OpenRAVE using a single thread (no separate
//-- controllers for each module)
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

#ifndef SIMULATED_MODULAR_ROBOT_SINGLE_THREAD_H
#define SIMULATED_MODULAR_ROBOT_SINGLE_THREAD_H

#include <openrave-core.h>
#include <iostream>
#include <vector>

#include "ModularRobot.h"
#include "SimulationOpenRAVE.hpp"

class SimulatedModularRobotSingleThread: public ModularRobot
{
public:
    SimulatedModularRobotSingleThread(std::string config_file);
    ~SimulatedModularRobotSingleThread();

    virtual void run();
    virtual void reset();

    void showSimulationViewer();

    bool createTables();

protected:
    static const int AMPLITUDE = 0;
    static const int OFFSET = 1;
    static const int PHASE = 2;
    static const int FREQUENCY = 0;
    static const int ALPHA = 1;
    static const int OMEGA = 2;
    static const int PHI = 3;
    static const int PHASE_LIMB = 4;

    bool calculateJointValues();
    bool calculateOscillatorValues();
    bool sendJointValues();

    void calculatePos();
    void updateTime();

    Simulation_OpenRAVE * simulation;
    OpenRAVE::ControllerBasePtr pcontroller;

    std::vector<Oscillator*> oscillators;
    std::vector<int> joint_values;
};


#endif //SIMULATED_MODULAR_ROBOT_SINGLE_THREAD_H
