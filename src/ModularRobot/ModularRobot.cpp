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

#include "ModularRobot.h"



ModularRobot::ModularRobot()
{
    //-- Default robot timestep:
    this->time_step_ms = 1;
    this->max_runtime_ms = 1000;
    this->distance_calculation_method = START_END_POINTS;

    //-- Default position/distance values
    this->current_pos = std::pair<float, float>(0,0);
    this->last_pos = current_pos;
    this->distance_travelled = 0;
    this->time_elapsed = 0;

}

ModularRobot::~ModularRobot()
{
    pthread_join(updateTime_thread, NULL);

    for(int i = 0; i < (int) modules.size(); i++)
        delete modules.at( modules.size() - 1 - i);
}

void ModularRobot::run()
{
    //-- Launch sytem timer thread
    pthread_create( &updateTime_thread, NULL, &updateTimeThread, (void *) this );

    //-- Launch modules threads
    for(int i = 0; i < (int) modules.size() ; i++)
        modules[i]->run( max_runtime_ms );

    //-- Temporarily wait for timer thread to end:
    //-- This could be later selected by a NO_WAIT parameter
    pthread_join( updateTime_thread, NULL);
}

void ModularRobot::reset()
{
    //-- Get current pos
    calculatePos();

    //-- Reset position/distance values
    this->last_pos = current_pos;
    this->distance_travelled = 0;
    this->time_elapsed = 0;
}

void ModularRobot::setTimeStep(uint32_t time_step_ms)
{
    this->time_step_ms = time_step_ms;
}

void ModularRobot::setMaxRuntime(uint32_t max_runtime_ms)
{
    this->max_runtime_ms = max_runtime_ms;
}

double ModularRobot::getDistanceTravelled()
{
    if ( distance_calculation_method == INTEGRATE_PATH )
        return distance_travelled;
    else if (distance_calculation_method == START_END_POINTS)
        return sqrt( pow( current_pos.first - start_pos.first, 2) +
                     pow( current_pos.second - start_pos.second, 2));
    else
        return 0;
}

uint32_t ModularRobot::getTimeElapsed()
{
    return time_elapsed;
}

void ModularRobot::selectDistanceCalculationMethod(bool integratePath)
{
    this->distance_calculation_method = integratePath;
}

void *ModularRobot::updateTimeThread(void *This)
{
    ((ModularRobot *) This)->updateTime();

    return NULL;
}

void ModularRobot::calculateDistanceTravelled()
{
    //-- Only calculates distance if integration is needed, to
    //-- recalculating point-to-point distances each iteration
    if ( distance_calculation_method == INTEGRATE_PATH )
    {
        distance_travelled += sqrt( pow( current_pos.first - last_pos.first, 2) +
                                    pow( current_pos.second - last_pos.second, 2));
    }
}
