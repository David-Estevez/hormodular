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

    //! \brief Constructs a empty gait table
    GaitTable( uint8_t n_modules, uint8_t n_parameters);
    //! \brief Loads data from a file and creates a gait table
    GaitTable(const std::string file_path  );

    //! \brief Frees the memory
    ~GaitTable();

    //! \brief Get element of the gait table
    float at( uint8_t id, uint8_t parameter );
    //! \brief Get all the parameter values of a certain id
    float * getParameters( uint8_t id);
    //! \brief Get number of modules
    uint8_t getNModules();
    //! \brief Get number of parameters
    uint8_t getNParameters();

    //! \brief Change a value of the table
    void set( uint8_t id, uint8_t parameter, float value);
    //! \brief Saves the gait table to a octave file
    void saveToFile(const std::string file_path);

private:
    /*! \var data
     *	\brief Stores the parameter values
     *
     *  Data in the table:
     *
     *  | id | param0 | param1 | ... | paramN |
     *  |  0 |   X00  |   X01  | ... |   X0N  |
     *  | ...|   ...  |   ...  | ... |   ...  |
     *  |  m |   XM0  |   XM1  | ... |   XMN  |
     *
     *  And internally is stored like this:
     *  | X00 | X01 | ... | X0N | X10 | X11 | ... | XM0 | XM1 | ... | XMN |
     *
     *  Therefore to access the element i,j:
     *  element(i, j) = *(data + i + n_modules * j)
     */
    float * data;
    uint8_t n_modules;
    uint8_t n_parameters;
};

#endif
