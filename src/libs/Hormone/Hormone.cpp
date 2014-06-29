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

#include "Hormone.hpp"

hormodular::Hormone::Hormone(int sourceConnector, int type)
{
    this->sourceConnector = sourceConnector;
    this->type = type;
    data = "";
}

hormodular::Hormone::Hormone(int sourceConnector, int type, std::string data)
{
    this->sourceConnector = sourceConnector;
    this->type = type;
    this->data = data;
}

int hormodular::Hormone::getType()
{
    return type;
}

int hormodular::Hormone::getSourceConnector()
{
    return sourceConnector;
}

std::string hormodular::Hormone::getData()
{
    return data;
}
