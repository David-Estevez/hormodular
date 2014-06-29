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

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

namespace hormodular
{

/*!
 * \brief Splits a string into multiple strings using the space character as separator
 *
 * This code has been copied from: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
 *
 */
std::vector<std::string> splitString(std::string stringToSplit);

}
#endif //-- UTILS_H
