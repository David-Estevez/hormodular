#include "SimulatedModularRobotInterface.hpp"

hormodular::SimulatedModularRobotInterface::SimulatedModularRobotInterface(hormodular::ConfigParser configParser)
{
    environment_file = configParser.getSimulationFile();
    step_ms = 1;    //!-- \todo Configure this somehow
    step_s = step_ms / (double)1000;

    simulation = new SimulationOpenRAVE( environment_file, false);

    controller = simulation->getRobot(0)->GetController();

    calculatePos();
    start_pos = current_pos;

}

bool hormodular::SimulatedModularRobotInterface::start()
{
    //! \todo Check if this is ok or not
    simulation->start(step_ms, true);

    calculatePos();
    start_pos = current_pos;

    return true;
}

bool hormodular::SimulatedModularRobotInterface::stop()
{
    simulation->stop();
    return true;
}

bool hormodular::SimulatedModularRobotInterface::destroy()
{
    simulation->stop();
    delete simulation;
    simulation = NULL;
    return true;
}

bool hormodular::SimulatedModularRobotInterface::reset()
{
    simulation->reset();
    controller = simulation->getRobot(0)->GetController();

    calculatePos();
    start_pos = current_pos;

    return true;
}

bool hormodular::SimulatedModularRobotInterface::setProperty(std::string property, std::string value)
{
    if ( property.compare("viewer") == 0 && value.compare("enabled") == 0)
    {
        simulation->showViewer();
        return true;
    }

    return false;
}

float hormodular::SimulatedModularRobotInterface::getTravelledDistance()
{
    calculatePos();

    //-- Position tracking
    std::ofstream ofile("./positions.txt");

    if ( ofile.is_open() )
    {
        for (int i = 0; i < pos.size(); i++)
            ofile << pos[i].x << " " <<pos[i].y << std::endl;
        ofile.close();
    }

    return sqrt( pow( current_pos.first - start_pos.first, 2) +
                 pow( current_pos.second - start_pos.second, 2));
}

bool hormodular::SimulatedModularRobotInterface::sendJointValues(std::vector<float> joint_values, float step_ms)
{
    if (!controller)
    {
        std::cerr << "[SimModRobInterface][Error] Could not access the controller." << std::endl;
        return false;
    }

    //-- Send joint values to openRAVE:
    std::stringstream is, os;
    is << "setpos ";

    for (int i = 0; i < (int) joint_values.size(); i++)
        is << joint_values[i] << " ";

    //std::cout << "[Debug] Joint values sent:" << is.str() << std::endl;
    if (!controller->SendCommand(os,is) )
        return false;

    if ( step_ms > 0)
            simulation->step(step_ms / 1000);

    //-- Get current robot position
    OpenRAVE::Vector robot_pos = simulation->getRobot(0)->GetCenterOfMass();
    pos.push_back(robot_pos);


    return true;
}

std::vector<float> hormodular::SimulatedModularRobotInterface::getJointValues()
{
    if (!controller)
    {
        std::cerr << "[SimModRobInterface][Error] Could not access the controller." << std::endl;
        return std::vector<float>();
    }

    //-- Send request to get the joint values:
    std::stringstream is, os;
    is << "getpos";
    controller->SendCommand(os,is);

    //-- Read the returned values:
    std::vector<float> joint_values;
    float aux;

    while( os.good() )
    {
        os >> aux;
        joint_values.push_back(aux);
    }

    return joint_values;
}

void hormodular::SimulatedModularRobotInterface::calculatePos()
{
    //-- Get current robot position
    OpenRAVE::Vector robot_pos = simulation->getRobot(0)->GetCenterOfMass();

    //-- Update current position stored:
    current_pos = std::pair<float, float>( robot_pos.x, robot_pos.y );
}
