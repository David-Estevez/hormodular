//------------------------------------------------------------------------------
//-- SerialModularRobotInterface
//------------------------------------------------------------------------------
//--
//-- Interface to the modular robot via serial port
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

/*! \file SerialModularRobotInterface.hpp
 *  \brief Interface to the modular robot via serial port
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */


#ifndef SERIAL_MODULAR_ROBOT_INTERFACE_H
#define SERIAL_MODULAR_ROBOT_INTERFACE_H

#include "ModularRobotInterface.hpp"
#include "ConfigParser.h"
#include <string>
#include <vector>
#include <iostream>
#include <SerialStream.h>

namespace hormodular {

/*!
 *  \class SerialModularRobotInterface
 *  \brief Interface to the modular robot via serial port
 */
class SerialModularRobotInterface : public ModularRobotInterface
{
    public:
        SerialModularRobotInterface(ConfigParser configParser);


        /*!
         * \brief Connects with the modular robot using the serial port
         * \return True if completed successfully, false otherwise
         */
        virtual bool start();

        /*!
         * \brief Stops the communication with the modular robot, closing the serial port
         * \return True if completed successfully, false otherwise
         */
        virtual bool stop();

        /*!
         * \brief Stops the communication with the modular robot, closing the serial port
         * and frees all the dynamically allocated memory.
         * \return True if completed successfully, false otherwise
         */
        virtual bool destroy();

        /*!
         * \brief Resets the communication with the modular robot, closing the serial port
         *  and connecting again to the robot
         * \return True if completed successfully, false otherwise
         */
        virtual bool reset();



        /*!
         * \brief Configure a property or parameter of the interface
         * \param property Property to be changed. Currently, only the "LED" property
         * is available, which controls the onboard LED.
         * \param value Value to be set on the property. For "LED", the only
         * available value is "toggle".
         * \return True if completed successfully, false otherwise
         */
        virtual bool setProperty(std::string property, std::string value);



        /*!
         * \brief Returns the distance travelled my the modular robot in meters
         *
         * Since a way to measure the distance travelled by a real robot has not been
         * implemented yet, this function only gives a warning message.
         *
         * \return -1, since this function is not implemented yet.
         */
        virtual float getTravelledDistance();

        //! \brief Sends the specified joint position values to the modular robot through the serial connection
        virtual bool sendJointValues(std::vector<float> joint_values, float step_ms=0);

        /*!
         * \brief Returns the joint position values stored in this class.
         *
         * Does not return the actual joint values, since the robot has no sensor for
         * measuring them (yet)
         */
        virtual std::vector<float> getJointValues();

   private:
        std::string port_name;
        SerialPort* serialPort;

        int step_ms;

        int num_modules;
        std::vector<float> joint_values;

        //-- Serial port related functions:
        //! \brief Configures and opens the serial port
        bool initSerialPort();

        //! \brief Checks that the modular robot is connected by checking the initial message from the robot
        bool checkConnection();

        //! \brief Sends the commands required for toggling the user LED on the robot board
        bool toggleLED();

        //! \brief Sends the commands required for setting the joint position values on the modular robots
        bool sendJointValuesSerial(std::vector<float> joint_values);
};

}

#endif //-- SERIAL_MODULAR_ROBOT_INTERFACE_H
