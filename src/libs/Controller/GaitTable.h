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
 * \date Nov 27th, 2013
 */

#ifndef GAIT_TABLE_H
#define GAIT_TABLE_H

#include <stdint.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*! \class GaitTable
 *  \brief A gait table to store all the parameters needed of robot locomotion
 */
class GaitTable
{
public:
    GaitTable(const std::string file_path, const int num_parameters );

    float at( int id, int parameter );
    std::vector<float> getParameters( int id);

    int getNumParameters();
    std::vector<unsigned long> getIDs();

    void setValue(unsigned long id, int parameter, float value);
    int setRow(unsigned long id, std::vector<float> values);

    int reload();

private:
    std::vector< std::vector<float> > data;
    int num_parameters;
    std::string file_path;

    int lookForID(unsigned long id);

    //! \brief Loads a gait table from a file:
    int loadFromFile( const std::string file_path);

    //! \brief Saves the gait table to a octave file
    void saveToFile(const std::string file_path);
};

#endif
