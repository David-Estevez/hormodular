#include "ConfigParser.h"

ConfigParser::ConfigParser()
{
    clearData();
}

int ConfigParser::parse(const std::string &filepath)
{
    clearData();

    //-- Create a xml document and load the file
    tinyxml2::XMLDocument xmldoc;
    xmldoc.LoadFile(filepath.c_str());

    //-- Error checking
    if ( xmldoc.ErrorID() == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED ||
         xmldoc.ErrorID() == tinyxml2::XML_ERROR_FILE_NOT_FOUND ||
         xmldoc.ErrorID() == tinyxml2::XML_ERROR_FILE_READ_ERROR )
    {
        std::cerr << "[Error] ConfigParser: error opening \"" << filepath.c_str()
                  << "\", xml file could not be opened!" << std::endl;
        return -1;
    }
    else if ( xmldoc.ErrorID() != tinyxml2::XML_SUCCESS )
    {
        std::cerr << "[Error] ConfigParser: Some error occurred with the xml file. Error code: "
                     << xmldoc.ErrorID() << std::endl;
        return -2;
    }

    //-- Extract data for the robot
    //-- Robot name:
    tinyxml2::XMLElement* modularRobotElement = xmldoc.FirstChildElement("ModularRobot");
    if ( !modularRobotElement )
    {
        std::cerr << "[Error] Error extracting tag \"ModularRobot\"" << std::endl;
        return -3;
    }
    robotName = std::string( modularRobotElement->Attribute("name") );

    //-- Simulation file
    const char * simulationFileStr = modularRobotElement->FirstChildElement("simulationFile")->GetText();
    simulationFile = std::string(simulationFileStr);
    removeBadCharacters(simulationFile);

    //-- Gait table folder
    const char * gaitTableFolderStr = modularRobotElement->FirstChildElement("gaitTableFolder")->GetText();
    gaitTableFolder = std::string(gaitTableFolderStr);
    removeBadCharacters(gaitTableFolder);

    //-- Get modules
    int auxNumModules = 0;
    tinyxml2::XMLNode* moduleNode = modularRobotElement->FirstChild();

    while(moduleNode)
    {
        const char* tagName = moduleNode->ToElement()->Name();
        if ( strcmp(tagName, "Module") == 0)
        {
            auxNumModules++;

            //-- Get Joint ID
            jointIDs.push_back(atoi(moduleNode->FirstChildElement("Joint")->GetText()));

            //-- Get Auxiliar IDs
            tinyxml2::XMLElement* idsElement = moduleNode->FirstChildElement("IDs");

            //-- Get Function ID
            const char* functionStr = idsElement->FirstChildElement("Function")->GetText();
            std::string functionStdStr = std::string(functionStr);
            removeBadCharacters(functionStdStr);

            if ( functionStdStr.compare("Limb") == 0)
                id_function_vector.push_back(ModuleFunction_limb);
            else if ( functionStdStr.compare("Coxa") == 0)
                id_function_vector.push_back(ModuleFunction_coxa);
            else if ( functionStdStr.compare("Thorax") == 0)
                id_function_vector.push_back(ModuleFunction_thorax);
            else
                id_function_vector.push_back(ModuleFunction_none);

            //-- Get Remaining IDs
            id_depth_vector.push_back(atoi(idsElement->FirstChildElement("Depth")->GetText()));
            id_shape_vector.push_back(atoi(idsElement->FirstChildElement("Shape")->GetText()));
            id_num_limbs_vector.push_back(atoi(idsElement->FirstChildElement("NumLimbs")->GetText()));
            id_limbs_vector.push_back(atoi(idsElement->FirstChildElement("LimbID")->GetText()));
        }

        //-- Get next element
        moduleNode = moduleNode->NextSibling();

    }
    numModules = auxNumModules;

    if (jointIDs.size() != (unsigned) numModules
        || id_function_vector.size() != (unsigned) numModules
        || id_shape_vector.size() != (unsigned) numModules
        || id_depth_vector.size() != (unsigned) numModules
        || id_num_limbs_vector.size() != (unsigned) numModules
        || id_limbs_vector.size() != (unsigned) numModules )
    {
        std::cerr << "[Error] Size of characteristic vectors is not consistent! Error Reading data!" << std::endl;
        clearData();
        return -4;
    }

    return 0;
}

std::string ConfigParser::getRobotName()
{
    return robotName;
}

std::string ConfigParser::getSimulationFile()
{
    return simulationFile;
}

std::string ConfigParser::getGaitTableFolder()
{
    return gaitTableFolder;
}

int ConfigParser::getNumModules()
{
    return numModules;
}

int ConfigParser::getJointID(const int &module)
{
    return jointIDs.at(module);
}

std::vector<int> ConfigParser::getJointIDs()
{
    return jointIDs;
}

std::vector<ModuleFunction> ConfigParser::getFunctionIDs()
{
    return id_function_vector;
}

std::vector<int> ConfigParser::getDepthIDs()
{
    return id_depth_vector;
}

std::vector<unsigned long> ConfigParser::getShapeIDs()
{
    return id_shape_vector;
}

std::vector<int> ConfigParser::getNumLimbsIDs()
{
    return id_num_limbs_vector;
}

std::vector<int> ConfigParser::getLimbsIDs()
{
    return id_limbs_vector;
}

void ConfigParser::clearData()
{
    robotName = "";
    simulationFile = "";
    gaitTableFolder = "";
    numModules = 0;
    jointIDs.clear();
    id_function_vector.clear();
    id_shape_vector.clear();
    id_depth_vector.clear();
    id_num_limbs_vector.clear();
    id_limbs_vector.clear();
}

bool ConfigParser::removeBadCharacters(std::string& string)
{
    string.erase( std::remove( string.begin(), string.end(), '\n'), string.end());
    string.erase( std::remove( string.begin(), string.end(), '\t'), string.end());
    string.erase( std::remove( string.begin(), string.end(), '\r'), string.end());
}
