//------------------------------------------------------------------------------
//-- Hormone
//------------------------------------------------------------------------------
//--
//-- Bio-inspired data container used for intermodular comunication
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

/*! \file Hormone.hpp
 *  \brief Bio-inspired data container used for intermodular comunication
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef HORMONE_H
#define HORMONE_H

#include <string>

namespace hormodular {

/*!
 *  \class Hormone
 *  \brief Bio-inspired data container used for intermodular comunication
 */
class Hormone
{
    public:
        Hormone( int sourceConnector, int type);
        Hormone( int sourceConnector, int type, std::string data);

        int getType();
        int getSourceConnector();
        std::string getData();

        //-- Allowed values for type
        static const int PING_HORMONE = 0;
        static const int LEG_HORMONE = 1;
        static const int HEAD_HORMONE = 2;

   private:
        int type;
        int sourceConnector;
        std::string data;

};

}
#endif //-- HORMONE_H
