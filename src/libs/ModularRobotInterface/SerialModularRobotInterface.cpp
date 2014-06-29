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

#include "SerialModularRobotInterface.hpp"


hormodular::SerialModularRobotInterface::SerialModularRobotInterface(hormodular::ConfigParser configParser)
{
    port_name = configParser.getSerialPort();
    num_modules = configParser.getNumModules();

    for (int i = 0; i < num_modules; i++)
    {
        joint_values.push_back(0);
    }

    serialPort = NULL;
}

bool hormodular::SerialModularRobotInterface::start()
{
    return initSerialPort();
}

bool hormodular::SerialModularRobotInterface::stop()
{
    //-- Close serial port
    if ( serialPort && serialPort->IsOpen() )
        serialPort->Close();

    return true;
}

bool hormodular::SerialModularRobotInterface::destroy()
{
    //-- Close serial port
    if ( serialPort && serialPort->IsOpen() )
        serialPort->Close();

    delete serialPort;
    serialPort = NULL;

    return true;
}

bool hormodular::SerialModularRobotInterface::reset()
{
    if (stop())
    {
        joint_values.clear();
        for (int i = 0; i < num_modules; i++)
            joint_values.push_back(0);

        return start();
    }
    else
        return false;
}

bool hormodular::SerialModularRobotInterface::setProperty(std::string property, std::string value)
{
    if ( property.compare("LED") == 0)
    {
        if ( value.compare("toggle") == 0)
            toggleLED();
        else
        {
            std::cerr << "[SerialModRobInterface] Error: value: " << value << " for property: " << property
                      << " does not exist" << std::endl;
            return false;
        }
    }
    return true;
}

float hormodular::SerialModularRobotInterface::getTravelledDistance()
{
    std::cerr << "[SerialModularRobotInterface] Warning: travelled distance is not implemented yet. Returning -1."
              << std::endl;
    return -1;
}

bool hormodular::SerialModularRobotInterface::sendJointValues(std::vector<float> joint_values, float step_ms)
{
    //-- Check number of input values:
    if (joint_values.size() != num_modules)
    {
        std::cerr << "[SerialModRobInteface] Error: input joint values size differs with number of modules in robot"
                     << std::endl;
        return false;
    }

    //-- Save joint values
    for (int i = 0; i < num_modules; i++)
        this->joint_values[i] = joint_values[i];

    //-- Send actual values:
    bool result = sendJointValuesSerial(joint_values);
    usleep(step_ms * 1000);

    return result;
}

std::vector<float> hormodular::SerialModularRobotInterface::getJointValues()
{
    return joint_values;
}

bool hormodular::SerialModularRobotInterface::initSerialPort()
{
    serialPort = new SerialPort( port_name );
    try
    {
        serialPort->Open( SerialPort::BAUD_57600, SerialPort::CHAR_SIZE_8,
                           SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                           SerialPort::FLOW_CONTROL_NONE );
    }
    catch ( SerialPort::OpenFailed e )
    {
        std::cerr << "[SerialModularRobotInterface] Error opening the serial port"
                     << port_name << std::endl;
        return false;
    }

    if ( ! checkConnection() )
    {
        std::cerr << "Error communicating with the robot. Exiting...\n"
                     << port_name << std::endl;
        return false;
    }

    return true;
}

bool hormodular::SerialModularRobotInterface::checkConnection()
{
    //-- Read welcome message to check if connected to the robot
    SerialPort::DataBuffer buffer;
    try {
        serialPort->Read( buffer, 13, 1500);
    }
    catch ( SerialPort::ReadTimeout e)
    {
        std::cout << "Timeout! Exiting..." << std::endl;
        return false;
    }

    //-- Check if connected
    std::string welcomeMessage = "[Debug] Ok!\r\n";
    bool diffFlag = false;

    for (int i = 0; i < (int) buffer.size(); i++)
    {
        if ( welcomeMessage[i] != buffer[i] )
            diffFlag = true;
    }

    return !diffFlag;
}

bool hormodular::SerialModularRobotInterface::toggleLED()
{
    if ( serialPort && serialPort->IsOpen() )
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x5F); //-- 0x5F -> Toggle LED
        serialPort->Write( outputBuff );

        return true;
    }
    else
    {
        std::cout << "[SerialModRobInterface] Error: LED could not be toggled (no robot connected)"
                     << std::endl;
        return false;
    }
}

bool hormodular::SerialModularRobotInterface::sendJointValuesSerial(std::vector<float> joint_values)
{
    if ( serialPort && serialPort->IsOpen() )
    {
        if ( joint_values.size() <= 8)
        {
            //-- Convert joint position to servo values [0-180]
            for (int i = 0; i < joint_values.size(); i++)
            {
                joint_values[i]+=90;
                if (joint_values[i] < 0) joint_values[i] = 0;
                if (joint_values[i] > 180) joint_values[i] = 180;
            }


            SerialPort::DataBuffer outputBuff;
            outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints

            for (int i = 0; i < joint_values.size(); i++)
                outputBuff.push_back( (char)( (int) (joint_values[i])));

            serialPort->Write( outputBuff );

            return true;
        }
        else
        {
            //-- Temporal solution to more than 8 modules configurations
            std::cerr << "[SerialModRobInterface] Error: more than 8 joints are not supported by "
                      << "the current architecture. Sending just 8 values..." << std::endl;

            SerialPort::DataBuffer outputBuff;
            outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints

            for (int i = 0; i < 8; i++)
                outputBuff.push_back( (char)( (int) (joint_values[i])));

            serialPort->Write( outputBuff );

            return false;
        }
    }
    else
    {
        std::cerr << "Robot could not send joints (because it is not connected)"
                     << std::endl;
        return false;
    }
}
