#include "ConfigParser.h"
#include "Module.h"
#include "assert.h"
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
    //static const std::string FILEPATH = "../../data/robots/Test_robot.xml";
    static const std::string FILEPATH = "../../data/robots/Test_robot2.xml";

    ConfigParser testParser = ConfigParser();

    std::cout << "Testing Config Parser:" << std::endl;
    std::cout << "--------------------------" << std::endl;

    //--Read file
    std::cout << "\tParsing file..." << std::endl;
    testParser.parse(FILEPATH);

    //-- Get the parameters
    std::cout << "\tChecking robot name..." << std::endl;
    assert(testParser.getRobotName() == "Test_robot");

    std::cout << "\tChecking simulation file..." << std::endl;
    assert(testParser.getSimulationFile() == "../../data/models/REPY-2.1/Kusanagi-2.env.xml");

    std::cout << "\tChecking gait table output folder..." << std::endl;
    assert(testParser.getGaitTableFolder() == "../../data/gait tables/test");

    std::cout << "\tChecking number of Modules..." << std::endl;
    assert(testParser.getNumModules() == 2);

    std::cout << "\tChecking module data..." << std::endl;
    std::cout << "\t\tChecking module id..." << std::endl;
    assert(testParser.getJointID(0) == 0);
    assert(testParser.getJointID(1) == 1);
    
    std::cout << "\t\tChecking IDs..." << std::endl;
    std::vector< ModuleFunction > id_function_vector = testParser.getFunctionIDs();
    assert(id_function_vector.at(0) == ModuleFunction_limb);
    assert(id_function_vector.at(1) == ModuleFunction_coxa);

    std::cout << "\t\tChecking depths..." << std::endl;
    std::vector<int> id_depth_vector = testParser.getDepthIDs();
    assert(id_depth_vector.at(0) == 0);
    assert(id_depth_vector.at(1) == -1);

    std::cout << "\t\tChecking shape ids..." << std::endl;
    std::vector<unsigned long> id_shape_vector = testParser.getShapeIDs();
    assert(id_shape_vector.at(0) == 42);
    assert(id_shape_vector.at(1) == 66);

    std::cout << "\t\tChecking number of limbs..." << std::endl;
    std::vector<int> id_num_limbs_vector = testParser.getNumLimbsIDs();
    assert(id_num_limbs_vector.at(0) == 1);
    assert(id_num_limbs_vector.at(1) == 1);

    std::cout << "\t\tChecking limb ids..." << std::endl;
    std::vector<int> id_limbs_vector = testParser.getLimbsIDs();
    assert(id_limbs_vector.at(0) == 0);
    assert(id_limbs_vector.at(1) == -1);

    std::cout <<"All tests were successful!" << std::endl;
}
