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
    /*!
     * \brief Creates a gait table from a file containing the table data
     * \param file_path Path to the file containing the table data
     */
    GaitTable(const std::string file_path);



    /*!
     * \brief Returns the value of the specified parameter for a given ID
     * \return The value stored at (id, parameter) on the gait table. If the ID
     * was not found, returns 0 (and shows an error message).
     */
    float at( int id, int parameter );

    /*!
     * \brief Returns the value of all the parameters for a given ID
     * \return The value of all the parameters for a given ID. If the ID was not
     * found, returns a vector of zeroes with the correct dimensions (and shows an
     * error message).
     */
    std::vector<float> getParameters( int id);

    /*!
     * \brief Returns the value of all the parameters for a given ID
     * \return The value of all the parameters for a given ID. If the ID was not
     * found, returns a vector of zeroes with the correct dimensions (and shows an
     * error message).
     */
    std::vector<float> operator[](int id);


    int getNumParameters();

    /*!
     * \brief Returns a vector containing all the IDs from all the entries on
     * the table
     */
    std::vector<unsigned long> getIDs();


    /*!
     * \brief Erases the current table and loads the data from the file again.
     * \return 0 if completed successfully, -1 if the file could not be opened.
     */
    int reload();

private:
    /*!
     * \brief Contains all the gait table data.
     *
     * Data is stored as a vector of the different parameter values (other vector) for
     * each ID.
     */
    std::vector< std::vector<float> > data;
    std::vector<unsigned long> ids;
    int num_parameters;
    std::string file_path;

    //! \brief Returns the index of the row containing the data for the given ID
    int lookForID(unsigned long id);

    //! \brief Loads a gait table from a file:
    int loadFromFile( const std::string file_path);

    //! \brief Saves the gait table to a Matlab/Octave file
    void saveToFile(const std::string file_path);
};

}
#endif
