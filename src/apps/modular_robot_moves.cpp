#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"
#include "ModularRobot.h"

using namespace hormodular;

int main(void)
{
    ConfigParser configParser;
    ModularRobot * modularRobot;

    static const std::string FILEPATH = "../data/test/Test_robot3.xml";;
    static const unsigned long max_time_ms = 5000;

    configParser.parse(FILEPATH);

    modularRobot = new ModularRobot(configParser);

    //modularRobot->reset();

    modularRobot->run(max_time_ms);

    float distance = modularRobot->getTravelledDistance();
    std::cout << "Distance travelled: " << distance << std::endl;


    delete modularRobot;
}
