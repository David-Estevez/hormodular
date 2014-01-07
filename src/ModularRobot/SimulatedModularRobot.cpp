#include "SimulatedModularRobot.h"

SimulatedModularRobot::SimulatedModularRobot(OpenRAVE::RobotBasePtr openRAVE_robot, OpenRAVE::EnvironmentBasePtr penv, std::string gait_table_file) : ModularRobot()
{
    //-- Gather simulation objects
    this->openRAVE_robot = openRAVE_robot;
    this->penv = penv;


    //-- Get modules info from openRAVE robot:
    int num_modules = openRAVE_robot->GetDOF();

    std::vector<int> dofindices( openRAVE_robot->GetDOF());
    for (int i = 0; i < (int) dofindices.size(); i++)
        dofindices[i] = i;

    OpenRAVE::ControllerBasePtr pcontroller = openRAVE_robot->GetController();


    //-- Create sync semaphores
    sem_init( &this->updateTime_semaphore, 0, 0);

    this->modules_semaphores = new sem_t[num_modules];
    for( int i = 0; i < num_modules; i++)
        sem_init( this->modules_semaphores+i, 0, 1);


    //-- Create modules:
    for( int i = 0; i< num_modules; i++)
    {
        std::vector<sem_t* > temp_semaphores;
        temp_semaphores.push_back( modules_semaphores+i);

        std::vector<int> temp_indices;
        temp_indices.push_back(dofindices[i]);

        Module * temp_module = new SimulatedModule(1, gait_table_file, pcontroller, temp_indices,
                                                   &updateTime_semaphore, temp_semaphores);
        modules.push_back( temp_module );
    }


}

SimulatedModularRobot::~SimulatedModularRobot()
{
    delete[] modules_semaphores;
}


void SimulatedModularRobot::updateTime()
{

    while (time_elapsed < max_runtime_ms)
    {
        //-- Lock this thread semaphores:
        for (int i = 0; i < (int) this->modules.size(); i++)
            sem_wait( &updateTime_semaphore);

        //-- Increment time
        for(int i = 0; i < (int) this->modules.size(); i++)
            modules.at(i)->incrementTime( time_step_ms); //-- 2ms

        //-- Update simulation
        penv->StepSimulation( time_step_s);

        //-- Unlock modules threads:
        for (int i = 0; i < (int) modules.size(); i++)
            sem_post( modules_semaphores+i);

        //-- Increment time counter
        time_elapsed += time_step_ms;

        //-- Wait for time period
        //usleep( 1000*STEP_MS);
    }
}

void SimulatedModularRobot::calculatePos()
{
    //-- Get current robot position
    OpenRAVE::Vector robot_pos = openRAVE_robot->GetCenterOfMass();

    //-- Keep last position
    last_pos = current_pos;

    //-- Update current position stored:
    current_pos = std::pair<float, float>( robot_pos.x, robot_pos.y );

}


