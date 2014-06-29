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

/*! \file ConfigParser.h
 *  \brief Reads the configuration file and gets the main parameters
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

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

/*!
 *  \class ConfigParser
 *  \brief Parses a XML configuration file and stores the configuration options
 */
class ConfigParser
{
    public:
        ConfigParser();

        /*!
         * \brief Parses the specified file
         * \param filepath String containing the path to the XML file
         * \return 0 if finished correctly, error code otherwise
         */
        int parse(const std::string& filepath);

        std::string getRobotName();
        std::string getSimulationFile();
        std::string getGaitTableFolder();
        std::string getFrequencyTableFile();
        std::string getSerialPort();
        int getNumModules();
        int getJointID(const int& module);
        std::vector<int> getJointIDs();
        std::vector< std::vector<int> > getConnectorInfo(int moduleIndex);
        std::vector<Orientation> getOrientations();

        //-- Error constants
        static const int FILE_NOT_OPENED = -1;
        static const int FILE_XML_ERROR = -2;
        static const int TAG_NOT_FOUND = -3;

        //-- Deprecated functions:
        //! \deprecated This function was used only for development purposes
        std::vector<ModuleFunction> getFunctionIDs();
        //! \deprecated This function was used only for development purposes
        std::vector<int> getDepthIDs();
        //! \deprecated This function was used only for development purposes
        std::vector<unsigned long> getShapeIDs();
        //! \deprecated This function was used only for development purposes
        std::vector<int> getNumLimbsIDs();
        //! \deprecated This function was used only for development purposes
        std::vector<int> getLimbsIDs();

    private:

        //! \brief Restores the initial, empty, state of the configParser object
        void clearData();

        /*!
         * \brief Removes all the undesired characters, such as spaces and tabulations
         * from a string.
         * \param string String from which the undesired caracters will be removed
         * \return True if the operation was successful, false otherwise
         */
        bool removeBadCharacters(std::string& string);

        std::string robotName;
        std::string simulationFile;
        std::string gaitTableFolder;
        std::string frequencyTableFile;
        std::string serialPort;
        int numModules;
        std::vector<int> jointIDs;
        std::vector< std::vector< std::vector<int> > > connector_info_vector;
        std::vector<Orientation> orientation_vector;

        //-- Deprecated variables
        //! \deprecated This variable was used only for development purposes
        std::vector<ModuleFunction> id_function_vector;
        //! \deprecated This variable was used only for development purposes
        std::vector<int> id_depth_vector;
        //! \deprecated This variable was used only for development purposes
        std::vector<unsigned long> id_shape_vector;
        //! \deprecated This variable was used only for development purposes
        std::vector<int> id_num_limbs_vector;
        //! \deprecated This variable was used only for development purposes
        std::vector<int> id_limbs_vector;

};
}


#endif // CONFIGPARSER_H
