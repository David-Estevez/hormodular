#include "SimulatedModularRobotInterface.hpp"

hormodular::SimulatedModularRobotInterface::SimulatedModularRobotInterface(hormodular::ConfigParser configParser)
{
    environment_file = configParser.getSimulationFile();
    step_ms = 1;    //!-- \todo Configure this somehow
    step_s = step_ms / (double)1000;

    //!-- \todo Add options changeOption("option", "newValue"); to the inteface
    simulation = new SimulationOpenRAVE( environment_file, false);

    controller = simulation->getRobot(0)->GetController();
}

bool hormodular::SimulatedModularRobotInterface::start()
{
    simulation->start(step_ms, true);
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
    return true;
}

float hormodular::SimulatedModularRobotInterface::getTravelledDistance()
{
    return false;
}

bool hormodular::SimulatedModularRobotInterface::sendJointValues(std::vector<float> joint_values, int step_ms)
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

    if (!controller->SendCommand(os,is) )
        return false;

    if ( step_ms > 0)
        simulation->step(step_ms);

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
