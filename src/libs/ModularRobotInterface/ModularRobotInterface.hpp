//------------------------------------------------------------------------------
//-- ModularRobotInterface
//------------------------------------------------------------------------------
//--
//-- Abstract class for different types of interfaces with modular robots
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

/*! \file ModularRobotInterface.hpp
 *  \brief Abstract class for different types of interfaces with modular robots
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef MODULAR_ROBOT_INTERFACE_H
#define MODULAR_ROBOT_INTERFACE_H

namespace hormodular {

/*!
 *  \class ModularRobotInterface
 *  \brief Abstract class for different types of interfaces with modular robots
 */
class ModularRobotInterface
{
public:
    /*!
     * \brief Initialize the robot interface
     * \return True if completed successfully, false otherwise
     */
    virtual bool start() = 0;

    /*!
     * \brief Stops the robot interface
     * \return True if completed successfully, false otherwise
     */
    virtual bool stop() = 0;

    /*!
     * \brief Destroys the robot interface, freeing the dynamically
     * allocated memory
     * \return True if completed successfully, false otherwise
     */
    virtual bool destroy() = 0;

    /*!
     * \brief Resets the robot interface
     * \return True if completed successfully, false otherwise
     */
    virtual bool reset() = 0;



    /*!
     * \brief Configure a property or parameter of the interface
     * \return True if completed successfully, false otherwise
     */
    virtual bool setProperty( std::string property, std::string value );


    //! \brief Returns the distance travelled my the modular robot in meters
    virtual float getTravelledDistance() = 0;

    //! \brief Sends the joint position values to the robot
    virtual bool sendJointValues(std::vector<float> joint_values, float step_ms=0) = 0;

    //! \brief Queries the robot for its joint position values
    virtual std::vector<float> getJointValues() = 0;

};


}

#endif //-- MODULAR_ROBOT_INTERFACE_H
