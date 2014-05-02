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

class Module
{
    public:
        Module(ConfigParser configParser, int index);
        ~Module();

        bool reset();

        bool attach( int localConnector, Connector* remoteConnector, int orientation = -1);
        Connector* getConnector(int localConnector);

        bool processHormones();
        bool sendHormones();

        bool updateOscillatorParameters();
        float calculateNextJointPos();

        bool updateElapsedTime(int timeIncrement_ms);

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
        unsigned long elapsedTime;
        Orientation orientation;
};

}



#endif //-- MODULE_H
