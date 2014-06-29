//------------------------------------------------------------------------------
//-- Module
//------------------------------------------------------------------------------
//--
//-- Base class for different types of modules for modular robotics
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

/*! \file Module.hpp
 *  \brief Base class for different types of modules for modular robotics
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <sstream>

#include "Connector.hpp"
#include "SinusoidalOscillator.h"
#include "ConfigParser.h"
#include "GaitTable.h"
#include "Orientation.hpp"
#include "Utils.hpp"

namespace hormodular {


/*!
 *  \class Module
 *  \brief Base class for different types of modules for modular robotics
 */
class Module
{
    public:
        /*!
         * \brief Creates a Module, indicating which position it occuppies inside the modular robot
         * \param configParser ConfigParser object contaning the module configuration parameters
         * \param index Position occupied by the module inside the modular robot, used to extract the
         *  correct configuration from the configParser, as well as for debugging purposes.
         */
        Module(ConfigParser configParser, int index);
        ~Module();



        //! Resets the module to its initial state
        bool reset();



        /*!
         * \brief Connects a connector from this module to other connector from other module
         * \param localConnector Identifier of the connector from this module (0 for front, 1 for right,
         * 2 for back and 3 for left)
         * \param remoteConnector Remote connector to be connected to this module connector
         * \param orientation Orientation between both connectors (no longer being used, replaced by Orientation class)
         * \return True if completed successfully, false otherwise
         */
        bool attach( int localConnector, Connector* remoteConnector, int orientation = -1);
        Connector* getConnector(int localConnector);



        /*!
         * \brief Process the incoming hormones, and discover the different  module IDs from them
         * \return True if completed successfully, false otherwise
         */
        bool processHormones();

        /*!
         * \brief Send the hormones in the output buffer to their destination modules
         * \return True if completed successfully, false otherwise
         */
        bool sendHormones();

        /*!
         * \brief Gets the parameters for the current module IDs and sets them on the oscillator
         * \return True if completed successfully, false otherwise
         */
        bool updateOscillatorParameters();


        //! \brief Returns the next joint position according to the current elapsed time
        float calculateNextJointPos();

        /*!
         * \brief updateElapsedTime
         * \param timeIncrement_ms
         * \return True if completed successfully, false otherwise
         */
        bool updateElapsedTime(float timeIncrement_ms);



        unsigned long getID();
        float getCurrentJointPos();


    private:
        ConfigParser configParser;
        std::vector<GaitTable *> gaitTables;
        GaitTable * frequencyTable;
        std::vector<Connector*> connectors;
        Oscillator* oscillator;
        int module_index;
        unsigned long id;
        int configurationId;
        float currentJointPos;
        unsigned long elapsedTime; //-- This time is in uS
        Orientation orientation;
};

}



#endif //-- MODULE_H
