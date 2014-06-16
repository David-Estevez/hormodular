//------------------------------------------------------------------------------
//-- ConfigParser
//------------------------------------------------------------------------------
//--
//-- Reads the configuration file and gets the main parameters
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Hormodular project
//-- (https://github.com/David-Estevez/hormodular.git)
//--
//------------------------------------------------------------------------------
//-- Author: David Estevez-Fernandez
//--
//-- Released under the GPL license (more info on LICENSE.txt file)
//------------------------------------------------------------------------------

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <tinyxml2.h>
#include "Orientation.hpp"

namespace hormodular {

enum ModuleFunction { ModuleFunction_none = -1,
                      ModuleFunction_limb = 0,
                      ModuleFunction_thorax = 1,
                      ModuleFunction_coxa = 2 };

class ConfigParser
{
    public:
        ConfigParser();

        int parse(const std::string& filepath);

        std::string getRobotName();
        std::string getSimulationFile();
        std::string getGaitTableFolder();
        std::string getFrequencyTableFile();
        std::string getSerialPort();
        int getNumModules();
        int getJointID(const int& module);
        std::vector<int> getJointIDs();
        std::vector<ModuleFunction> getFunctionIDs(); //-- Deprecated
        std::vector<int> getDepthIDs(); //-- Deprecated
        std::vector<unsigned long> getShapeIDs(); //-- Deprecated
        std::vector<int> getNumLimbsIDs(); //-- Deprecated
        std::vector<int> getLimbsIDs(); //-- Deprecated
        std::vector< std::vector<int> > getConnectorInfo(int moduleIndex);
        std::vector<Orientation> getOrientations();

        //-- Error constants
        static const int FILE_NOT_OPENED = -1;
        static const int FILE_XML_ERROR = -2;
        static const int TAG_NOT_FOUND = -3;

    private:
        void clearData();
        bool removeBadCharacters(std::string& string);

        std::string robotName;
        std::string simulationFile;
        std::string gaitTableFolder;
        std::string frequencyTableFile;
        std::string serialPort;
        int numModules;
        std::vector<int> jointIDs;
        std::vector<ModuleFunction> id_function_vector; //-- Deprecated
        std::vector<int> id_depth_vector; //-- Deprecated
        std::vector<unsigned long> id_shape_vector; //-- Deprecated
        std::vector<int> id_num_limbs_vector; //-- Deprecated
        std::vector<int> id_limbs_vector; //-- Deprecated
        std::vector< std::vector< std::vector<int> > > connector_info_vector;
        std::vector<Orientation> orientation_vector;
};
}


#endif // CONFIGPARSER_H
