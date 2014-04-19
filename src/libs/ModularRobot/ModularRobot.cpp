//------------------------------------------------------------------------------
//-- ModularRobot
//------------------------------------------------------------------------------
//--
//-- Modular robot for modular robotics
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

#include "ModularRobot.h"



hormodular::ModularRobot::ModularRobot(hormodular::ConfigParser configParser)
{
    this->configParser = configParser;

    //-- Create as many modules as needed
    for(int i = 0; i < configParser.getNumModules(); i++)
        modules.push_back( new Module(configParser) );

    //-- Create robot, simulated type
    robotInterface = createModularRobotInterface( "simulated", configParser);

    reset();
}

hormodular::ModularRobot::~ModularRobot()
{
    robotInterface->destroy();
    delete robotInterface;
    robotInterface = NULL;

    //-- Destroy modules
    for(int i = 0; i < (int) modules.size(); i++)
    {
        delete modules[i];
        modules[i] = NULL;
    }
}

bool hormodular::ModularRobot::run(unsigned long runTime)
{
    //-- Movement loop
        while( elapsed_time < runTime )
        {
            //-- Process incoming hormones
            for(int i = 0; i < (int) modules.size(); i++)
                modules[i]->processHormones();

            //-- Get oscillator parameters from gait table:
            for( int i = 0; i < (int) modules.size(); i++)
                modules[i]->updateOscillatorParameters();

            //-- Update joint values
            for ( int i = 0; i < (int) modules.size(); i++)
                joint_values[i] = modules[i]->calculateNextJointPos();

            //-- Send joint values
            robotInterface->sendJointValues(joint_values, step_ms);

            //-- Send hormones
            for(int i = 0; i < (int) modules.size(); i++)
                modules[i]->sendHormones();

            //-- Update time:
            for ( int i = 0; i < (int) modules.size(); i++)
                modules[i]->updateElapsedTime(step_ms);

            elapsed_time+=step_ms;
            //std::cout << "Run time: " << elapsed_time << std::endl;
            //usleep( step_ms * 1000);
        }

        return true;
}

bool hormodular::ModularRobot::reset()
{
    //-- Reset robot
    if (!robotInterface->reset())
        return false;

    //-- Initialize joint vector to 0
    for (int i = 0; i < (int) configParser.getNumModules(); i++)
        joint_values.push_back(0);

    //-- Attach modules
    if (!attachModules())
        return false;

    elapsed_time = 0;
    step_ms = 1; //! \todo Get this from the configParser

    return true;
}

float hormodular::ModularRobot::getTravelledDistance()
{
    return robotInterface->getTravelledDistance();
}

bool hormodular::ModularRobot::attachModules()
{
    //-- Attach the modules to the other modules
    for(int i = 0; i < (int) modules.size(); i++)
    {
        std::vector< std::vector<int> > connectorConfig = configParser.getConnectorInfo(i);

        if (connectorConfig.size() == 0)
        {
            std::cerr << "[ModularRobot] Error: no connector info was found!" << std::endl;
            return false;
        }

        for (int j = 0; j < (int) connectorConfig.size(); j++)
        {
            if ( connectorConfig[j].size() != 0 )
            {
                int moduleConnectedTo = connectorConfig[j][0];
                int connectorConnectedTo = connectorConfig[j][1];
                int orientation = connectorConfig[j][2];
                modules[i]->attach( j,
                                    modules[moduleConnectedTo]->getConnector(connectorConnectedTo),
                                    orientation);
            }
            else
                modules[i]->attach(j, NULL);
        }
    }
    return true;
}
