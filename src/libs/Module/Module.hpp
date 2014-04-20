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

namespace hormodular {

class Module
{
    public:
        Module( ConfigParser configParser);
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

        GaitTable * gaitTable;
        std::vector<Connector*> connectors;
        Oscillator* oscillator;

        unsigned long id;
        int configurationId;

        float currentJointPos;

        unsigned long elapsedTime;
};

}

#endif //-- MODULE_H
