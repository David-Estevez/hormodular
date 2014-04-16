//------------------------------------------------------------------------------
//-- Connector
//------------------------------------------------------------------------------
//--
//-- Device that connects different modules for communications
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

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <vector>
#include "Hormone.hpp"

namespace hormodular {

class Connector
{
    public:
        std::vector<Hormone> inputBuffer;
        std::vector<Hormone> outputBuffer;

        Connector * remoteConnector;
};

}
#endif //-- CONNECTOR_H
