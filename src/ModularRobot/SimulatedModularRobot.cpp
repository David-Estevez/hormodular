#include "SimulatedModularRobot.h"

SimulatedModularRobot::SimulatedModularRobot( std::string environment_file, std::string gait_table_file) : ModularRobot()
{
    //-- Create simulation
    this->simulation = new Simulation_OpenRAVE( environment_file, false);

    //-- Gather simulation objects
    this->openRAVE_robot = simulation->getRobot(0);

    //-- Get modules info from openRAVE robot:
    int num_modules = openRAVE_robot->GetDOF();

    //-- Get vector with dof indices
    std::vector<int> dofindices( num_modules );
    for (int i = 0; i < (int) dofindices.size(); i++)
        dofindices[i] = i;

    //-- Get controller from robot
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
                                                   &this->updateTime_semaphore, temp_semaphores);
        modules.push_back( temp_module );
    }


}

SimulatedModularRobot::~SimulatedModularRobot()
{
    //-- Free modules
    //int num_modules = modules.size();

    //std::cout << "[Debug] Just called -> ~SimulatedModularRobot(), " << num_modules << " modules to destroy." << std::endl;

//    for (int i = 0; i < num_modules; i++)
//        delete modules[i];

    //-- Free semaphores
    delete[] modules_semaphores;

    //-- Free simulation
    delete simulation;
}

void SimulatedModularRobot::showSimulationViewer()
{
    simulation->showViewer();
}

void SimulatedModularRobot::reset()
{
    //-- Call the parent reset function
    this->ModularRobot::reset();

    //-- Reset simulation
    simulation->reset();
    simulation->stop();

    //-- Gather simulation objects
    this->openRAVE_robot = simulation->getRobot(0);

    //-- Get controller from robot
    OpenRAVE::ControllerBasePtr pcontroller = openRAVE_robot->GetController();

    //-- Set controller on robots again:
    for( int i = 0; i < (int) this->modules.size(); i++)
        ((SimulatedModule*)modules[i])->setOpenRAVEController( pcontroller);

    //-- Reset semaphores:
    sem_init( &this->updateTime_semaphore, 0, 0);

    for( int i = 0; i < (int) this->modules.size(); i++)
        sem_init( this->modules_semaphores+i, 0, 1);
}


void SimulatedModularRobot::updateTime()
{
    std::cout << "[Debug] Running robot with " << this->modules.size() << " modules for " << max_runtime_ms << "ms." << std::endl;

    while (time_elapsed < max_runtime_ms)
    {
//        std::cout << "[Debug] Current time: " << time_elapsed << std::endl;
//        std::cout.flush();

        //-- Lock this thread semaphores:
        for (int i = 0; i < (int) this->modules.size(); i++)
            sem_wait( &updateTime_semaphore);

        //-- Increment time
        for(int i = 0; i < (int) this->modules.size(); i++)
            modules.at(i)->incrementTime( time_step_ms); //-- 2ms

        //-- Update simulation
        simulation->step( time_step_s);

        //-- Unlock modules threads:
        for (int i = 0; i < (int) modules.size(); i++)
            sem_post( modules_semaphores+i);

        //-- Increment time counter
        time_elapsed += time_step_ms;

        //-- Calculate distance travelled this step:
        calculateDistanceTravelled();

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


