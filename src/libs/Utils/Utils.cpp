//------------------------------------------------------------------------------
//-- Utils
//------------------------------------------------------------------------------
//--
//-- Useful functions for the hormodular project
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

#include "Utils.hpp"

std::vector<std::string> hormodular::splitString(std::string stringToSplit)
{
    /*
      This code has been copied from: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
      */
    std::vector<std::string> tokens;
    std::istringstream iss(stringToSplit);
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string> >(tokens));
    return tokens;

}
