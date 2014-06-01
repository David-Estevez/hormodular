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
        Connector();

        bool connectTo( Connector * remoteConnector);
        bool sendHormones();

        bool addOutputHormone(Hormone outputHormone);
        bool clearInputBuffer();

        int getLocalOrientation() const;
        void setLocalOrientation(int localOrientation);

        std::vector<Hormone> getInputBuffer();
        Connector * getRemoteConnector();

   private:
        std::vector<Hormone> inputBuffer;
        std::vector<Hormone> outputBuffer;

        Connector * remoteConnector;
        int localOrientation;

        bool addInputHormone(Hormone inputHormone );
};

}
#endif //-- CONNECTOR_H
