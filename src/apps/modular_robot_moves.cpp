#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"
#include "ModularRobot.h"

using namespace hormodular;

int main(int argc, char* argv[])
{
    ConfigParser configParser;
    ModularRobot * modularRobot;

    std::string filepath;

    if ( argc != 2)
        filepath = "../data/tmp/newApproach-2014-5-4-1-53-00/MultiDof-7-tripod.xml";
    else
        filepath = argv[1];

    static const unsigned long max_time_ms = 25000;

    configParser.parse(filepath);

    modularRobot = new ModularRobot(configParser);

    modularRobot->setProperty("viewer", "enabled");
    modularRobot->reset();

    modularRobot->run(max_time_ms);

    float distance = modularRobot->getTravelledDistance();
    std::cout << "Distance travelled: " << distance << std::endl;


    delete modularRobot;
}
