#include "SimulatedModularRobotSingleThread.h"

SimulatedModularRobotSingleThread::SimulatedModularRobotSingleThread(std::string config_file)
    : ModularRobot(config_file)
{
    simulation = new Simulation_OpenRAVE(configParser.getSimulationFile(), false );

    for(int i = 0; i < (int) configParser.getNumModules(); i++)
        oscillators.push_back(new SinusoidalOscillator());

    createTables();
    reset();
}

SimulatedModularRobotSingleThread::~SimulatedModularRobotSingleThread()
{
    delete simulation;

    for(int i = 0; i < (int) configParser.getNumModules(); i++)
        delete oscillators[configParser.getNumModules()-i];
}

void SimulatedModularRobotSingleThread::run()
{
    std::cout << "[Debug] Running robot with " << configParser.getNumModules() << " modules for "
              << max_runtime_ms << "ms." << std::endl;

    while ( time_elapsed < max_runtime_ms )
    {
        //std::cout << "[Debug] Time: " << (int) time_elapsed << std::endl;

        //-- Calculate the joint values at this time
        calculateJointValues();

        sendJointValues();

        //-- Simulate & update time
        simulation->step(time_step_s);
        time_elapsed += time_step_ms;

        //-- Calculate distance travelled this step:
        calculateDistanceTravelled();
    }
}

void SimulatedModularRobotSingleThread::reset()
{
    std::cout << "[SimModRobSingleThread] Resetting simulation..." << std::endl;
    simulation->reset();
    simulation->stop();

    std::cout << "[SimModRobSingleThread] Getting controller..." << std::endl;
    pcontroller = simulation->getRobot(0)->GetController();

    for (int i = 0; i < configParser.getNumModules(); i++)
    {
        joint_values.clear();
        joint_values.push_back(0);
    }

    //-- Get current pos
    std::cout << "[SimModRobSingleThread] Calculating current position..." << std::endl;
    this->calculatePos();

    //-- Reset position/distance values
    start_pos = current_pos;
    last_pos = current_pos;
    distance_travelled = 0;
    time_elapsed = 0;

    std::cout << "[SimModRobSingleThread] Reloading gait tables..." << std::endl;
    gait_table_limbs->reload();
    gait_table_shape->reload();

    std::cout << "[SimModRobSingleThread] Calculating oscillator values..." << std::endl;
    calculateOscillatorValues();
}

void SimulatedModularRobotSingleThread::showSimulationViewer()
{
    simulation->showViewer();
}

bool SimulatedModularRobotSingleThread::createTables()
{
    std::vector<float> emptyRowShape;
    emptyRowShape.push_back(0);
    emptyRowShape.push_back(0);
    emptyRowShape.push_back(0);

    std::vector<float> emptyRowLimbs;
    emptyRowLimbs.push_back(0);
    emptyRowLimbs.push_back(0);
    emptyRowLimbs.push_back(0);
    emptyRowLimbs.push_back(0);
    emptyRowLimbs.push_back(0);

    for(int i = 0; i < (int)configParser.getShapeIDs().size(); i++)
        gait_table_shape->setRow(configParser.getShapeIDs()[i], emptyRowShape);

    for(int i = 0; i < (int)configParser.getNumLimbsIDs().size(); i++)
        gait_table_limbs->setRow(configParser.getNumLimbsIDs()[i], emptyRowLimbs);

    return true;
}

bool SimulatedModularRobotSingleThread::calculateJointValues()
{
//    //--Debug things
//    for (int i = 0; i < (int)oscillators.size(); i++)
//        std::cerr << oscillators[i]->getAmplitude() << " ";
//    std::cerr << std::endl;

    for (int i = 0; i < (int)oscillators.size(); i++)
        joint_values[i] = oscillators[i]->calculatePos(time_elapsed);

    return true;
}

bool SimulatedModularRobotSingleThread::calculateOscillatorValues()
{

    std::vector<int> joint_ids = configParser.getJointIDs();
    std::vector<unsigned long> shape_ids = configParser.getShapeIDs();
    std::vector<int> num_limbs_ids = configParser.getNumLimbsIDs();
    std::vector<int> depth_ids = configParser.getDepthIDs();
    std::vector<int> limb_ids = configParser.getLimbsIDs();

    //-- Other IDs

            //-- Test this with only one gait table first
            //-- Get parameters for the oscillator from that table
            //-- Remember to check whether or not the id is -1 (default value)
            //-- To avoid polluting the gait table
    for (int i = 0; i < (int) joint_ids.size(); i++)
    {
        int joint = joint_ids[i];

        //-- Check if any of the ids is not valid
        if ( shape_ids[i] == (unsigned long)-1 && num_limbs_ids[i] == -1)
        {
            std::cerr << "[SimModRobSingleThread] Error: id not valid (not set)." << std::endl;
            return false;
        }

        //-- Create variables to store new parameters
        float newAmplitude, newOffset, newPhase, newFrequency;
        newAmplitude = newOffset = newPhase = newFrequency = 0;

        //-- Extract from the shape gait tables the base parameters:
        float baseAmplitude = gait_table_shape->at(shape_ids[i], AMPLITUDE);
        float baseOffset = gait_table_shape->at(shape_ids[i], OFFSET);
        float basePhase = gait_table_shape->at(shape_ids[i], PHASE);

        //-- Extract additional parameters
        newFrequency = gait_table_limbs->at(num_limbs_ids[i], FREQUENCY);
        float alpha = gait_table_limbs->at(num_limbs_ids[i], ALPHA);
        float omega = gait_table_limbs->at(num_limbs_ids[i], OMEGA);
        float phi = gait_table_limbs->at(num_limbs_ids[i], PHI);
        float limbPhase = gait_table_limbs->at(num_limbs_ids[i], PHASE_LIMB);

        //- Calculate new parameters
        newAmplitude = baseAmplitude*pow(depth_ids[i], alpha);
        newOffset = baseOffset*pow(depth_ids[i], omega);
        newPhase = basePhase + phi*depth_ids[i] + limbPhase*limb_ids[i];


        //-- Set final parameters on the selected oscillator
        oscillators[joint]->setParameters(newAmplitude, newOffset, newPhase, newFrequency);
    }

    return true;
}

bool SimulatedModularRobotSingleThread::sendJointValues()
{
    std::stringstream is, os;
    is << "setpos ";

    for (int i = 0; i < (int)oscillators.size(); i++)
        is << joint_values[i] << " " ;

    pcontroller->SendCommand(os, is);

    return true;
}

void SimulatedModularRobotSingleThread::calculatePos()
{
    //-- Get current robot position
    OpenRAVE::Vector robot_pos = simulation->getRobots()[0]->GetCenterOfMass();

    //-- Keep last position
    last_pos = current_pos;

    //-- Update current position stored:
    current_pos = std::pair<float, float>( robot_pos.x, robot_pos.y );
}

void SimulatedModularRobotSingleThread::updateTime()
{
    return;
}
