//------------------------------------------------------------------------------
//-- Gait Table
//------------------------------------------------------------------------------
//--
//-- A gait table that contains all the parameters needed for robot locomotion.
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

/*! \file GaitTable.h
 *  \brief A gait table to store all the parameters needed for robot locomotion
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef GAIT_TABLE_H
#define GAIT_TABLE_H

#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace hormodular {

/*! \class GaitTable
 *  \brief A gait table to store all the parameters needed of robot locomotion
 */
class GaitTable
{
public:
    GaitTable(const std::string file_path);

    float at( int id, int parameter );
    std::vector<float> getParameters( int id);
    std::vector<float> operator[](int id);

    int getNumParameters();
    std::vector<unsigned long> getIDs();

    int reload();

private:
    std::vector<unsigned long> ids;
    std::vector< std::vector<float> > data;
    int num_parameters;
    std::string file_path;

    int lookForID(unsigned long id);

    //! \brief Loads a gait table from a file:
    int loadFromFile( const std::string file_path);

    //! \brief Saves the gait table to a octave file
    void saveToFile(const std::string file_path);
};

}
#endif
