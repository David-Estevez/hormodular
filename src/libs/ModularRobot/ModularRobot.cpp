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
    this->time_step_s = 1;
    this->distance_calculation_method = START_END_POINTS;

    //-- Default position/distance values
    this->current_pos = std::pair<float, float>(0,0);
    this->last_pos = current_pos;
    this->distance_travelled = 0;
    this->time_elapsed = 0;

}

ModularRobot::~ModularRobot()
{
    //pthread_join(updateTime_pthread, NULL);

    //std::cout << "[Debug] Just called -> ~ModularRobot(), " << modules.size() << " modules to destroy." << std::endl;
    for(int i = 0; i < (int) modules.size(); i++)
        delete modules.at( modules.size() - 1 - i);
}

void ModularRobot::run()
{
    //-- Launch system timer thread
    pthread_create( &updateTime_pthread, NULL, &updateTimeThread, (void *) this );

    //-- As we don't have yet a method to determine the module
    //-- local id, we force them temporarily:
    std::vector< ModuleFunction > id_function = configParser.getFunctionIDs();
    std::vector<unsigned long> id_shape = configParser.getShapeIDs();
    std::vector<int> id_depth = configParser.getDepthIDs();
    std::vector<int> id_limbs = configParser.getLimbsIDs();
    std::vector<int> id_num_limbs = configParser.getNumLimbsIDs();

    for(int i = 0; i < (int) modules.size() ; i++)
        modules[i]->setIDs(id_function[i], id_depth[i], id_shape[i], id_num_limbs[i], id_limbs[i]);

    //-- Launch modules threads
    for(int i = 0; i < (int) modules.size() ; i++)
        modules[i]->run( max_runtime_ms );

    //-- Temporarily wait for timer thread to end:
    //-- This could be later selected by a NO_WAIT parameter
    pthread_join( updateTime_pthread, NULL);

    //-- Wait for all the modules to end:
    for(int i = 0; i < (int) modules.size() ; i++)
        modules[i]->join();

}

void ModularRobot::reset()
{
    //-- Get current pos
    this->calculatePos();

    //-- Reset position/distance values
    this->start_pos = current_pos;
    this->last_pos = current_pos;
    this->distance_travelled = 0;
    this->time_elapsed = 0;

    //-- Reset individual modules
    for (int i = 0; i < (int) modules.size(); i++)
        modules[i]->reset();
}

void ModularRobot::setTimeStep(uint32_t time_step_ms)
{
    this->time_step_ms = time_step_ms;
    this->time_step_s = time_step_ms / 1000.0;
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
    {
        calculatePos();
        return sqrt( pow( current_pos.first - start_pos.first, 2) +
                     pow( current_pos.second - start_pos.second, 2));
    }
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
    calculatePos();

    //-- Only calculates distance if integration is needed, to
    //-- recalculating point-to-point distances each iteration
    if ( distance_calculation_method == INTEGRATE_PATH )
    {
        distance_travelled += sqrt( pow( current_pos.first - last_pos.first, 2) +
                                    pow( current_pos.second - last_pos.second, 2));
    }
}
