#include "ModularRobotInterfaceFactory.hpp"

hormodular::ModularRobotInterface *hormodular::createModularRobotInterface(std::string type, ConfigParser configParser)
{
    if ( type == "simulated")
        return (ModularRobotInterface*) new SimulatedModularRobotInterface(configParser);
    else
    {
        std::cerr << "[Error][ModularRobotInterface] Could not create robot with type: \"" << type << "\"" << std::endl;
        return (ModularRobotInterface * ) NULL;
    }
}
