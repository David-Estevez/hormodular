#include "ConfigParser.h"

hormodular::ConfigParser::ConfigParser()
{
    clearData();
}

int hormodular::ConfigParser::parse(const std::string &filepath)
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

            if ( idsElement != NULL )
            {
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

            //-- Get connector info
            std::vector< std::vector<int> > connectorInfo;
            std::vector<std::string> connectorTags;
            connectorTags.push_back("front");
            connectorTags.push_back("right");
            connectorTags.push_back("back");
            connectorTags.push_back("left");

            tinyxml2::XMLElement* connectorElement = moduleNode->FirstChildElement("Connections");

            for (int i = 0; i < (int) connectorTags.size(); i++)
            {
                tinyxml2::XMLElement* currentConnector = connectorElement->FirstChildElement(connectorTags[i].c_str());

                if ( currentConnector )
                {
                    std::vector<int> currentConnectorInfo;

                    //-- Get who is the module connected to this one
                    currentConnectorInfo.push_back(atoi(currentConnector->Attribute("connectedTo")));

                    //-- Get who is the connector connected to this one
                    const char* connectorStr = currentConnector->Attribute("connector");
                    std::string connectorStdStr = std::string(connectorStr);
                    removeBadCharacters(connectorStdStr);

                    if ( connectorStdStr.compare("front") == 0)
                    {
                        currentConnectorInfo.push_back(0);
                    }
                    else if ( connectorStdStr.compare("right") == 0)
                    {
                        currentConnectorInfo.push_back(1);
                    }
                    else if ( connectorStdStr.compare("back") == 0)
                    {
                        currentConnectorInfo.push_back(2);
                    }
                    else if ( connectorStdStr.compare("left") == 0)
                    {
                        currentConnectorInfo.push_back(3);
                    }

                    //-- Get what is the orientation of this connection
                    currentConnectorInfo.push_back(atoi(currentConnector->Attribute("orientation")));

                    //-- Add current connector data to the table
                    connectorInfo.push_back(currentConnectorInfo);
                }
                else
                {
                    connectorInfo.push_back( std::vector<int>() );
                }
            }

            connector_info_vector.push_back(connectorInfo);


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

std::string hormodular::ConfigParser::getRobotName()
{
    return robotName;
}

std::string hormodular::ConfigParser::getSimulationFile()
{
    return simulationFile;
}

std::string hormodular::ConfigParser::getGaitTableFolder()
{
    return gaitTableFolder;
}

int hormodular::ConfigParser::getNumModules()
{
    return numModules;
}

int hormodular::ConfigParser::getJointID(const int &module)
{
    return jointIDs.at(module);
}

std::vector<int> hormodular::ConfigParser::getJointIDs()
{
    return jointIDs;
}

std::vector<hormodular::ModuleFunction> hormodular::ConfigParser::getFunctionIDs()
{
    return id_function_vector;
}

std::vector<int> hormodular::ConfigParser::getDepthIDs()
{
    return id_depth_vector;
}

std::vector<unsigned long> hormodular::ConfigParser::getShapeIDs()
{
    return id_shape_vector;
}

std::vector<int> hormodular::ConfigParser::getNumLimbsIDs()
{
    return id_num_limbs_vector;
}

std::vector<int> hormodular::ConfigParser::getLimbsIDs()
{
    return id_limbs_vector;
}

std::vector<std::vector<int> > hormodular::ConfigParser::getConnectorInfo(int moduleIndex)
{
    if ( moduleIndex < 0 || moduleIndex >= numModules )
    {
        std::vector< std::vector<int> > answer;
        answer.push_back(std::vector<int>());
        answer.push_back(std::vector<int>());
        answer.push_back(std::vector<int>());
        answer.push_back(std::vector<int>());

        std::cerr << "[ConfigParser] Error: selected id (" << moduleIndex <<") does not exist." << std::endl;
        return answer;
    }

    return connector_info_vector[moduleIndex];
}

void hormodular::ConfigParser::clearData()
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

bool hormodular::ConfigParser::removeBadCharacters(std::string& string)
{
    string.erase( std::remove( string.begin(), string.end(), '\n'), string.end());
    string.erase( std::remove( string.begin(), string.end(), '\t'), string.end());
    string.erase( std::remove( string.begin(), string.end(), '\r'), string.end());

    return true;
}
