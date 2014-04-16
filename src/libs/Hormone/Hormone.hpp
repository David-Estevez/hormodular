//------------------------------------------------------------------------------
//-- Hormone
//------------------------------------------------------------------------------
//--
//-- Bio-inspired data package used for intermodular comunication
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

#ifndef HORMONE_H
#define HORMONE_H

#include <string>

namespace hormodular {

class Hormone
{
    public:
        Hormone( int sourceConnector, int type);
        Hormone( int sourceConnector, int type, std::string data);

        int getType();
        int getSourceConnector();
        std::string getData();

        static const int PING_HORMONE = 0;

   private:
        int type;
        int sourceConnector;
        std::string data;

};

}
#endif //-- HORMONE_H
