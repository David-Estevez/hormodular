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

#include "Connector.hpp"
#include "ConfigParser.h"

namespace hormodular {

class Module
{
    public:
        Module();
        ~Module();

        bool attach( int localConnector, Connector* remoteConnector, int orientation = -1);
        Connector* getConnector(int localConnector);

        bool processHormones();
        bool sendHormones();

        unsigned long getID();

    private:
        std::vector<Connector*> connectors;
        unsigned long id;
};

}

#endif //-- MODULE_H
