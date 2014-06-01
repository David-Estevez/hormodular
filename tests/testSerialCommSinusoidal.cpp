//------------------------------------------------------------------------------
//-- testSerialCommSinusoidal
//------------------------------------------------------------------------------
//--
//-- Outputs the position signal of a sinusoidal oscillator to the serial port
//-- to control the robot.
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

#include <string>
#include <iostream>
#include <SerialStream.h>
#include <cmath>
#include <gtest/gtest.h>



class TestSerialCommunications: public testing::Test
{
    public:
        static const std::string PORT;
};

const std::string TestSerialCommunications::PORT = std::string("/dev/ttyUSB0");

TEST_F( TestSerialCommunications, RobotIsControlledBySerialPort)
{
    std::cout << "Serial port: " << PORT << std::endl;
    std::cout << "Opening... " << std::endl;

    //-- Create and open a serial port
    SerialPort serialPort(PORT);
    try
    {
        serialPort.Open( SerialPort::BAUD_57600, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE );
    }
    catch ( SerialPort::OpenFailed e )
    {
        std::cerr << "Error opening the serial port \"" << PORT << "\"" << std::endl;
    }

    ASSERT_TRUE(serialPort.IsOpen());

    //-- Read welcome message to check if connected to the robot
    SerialPort::DataBuffer buffer;
    bool timeout_flag = false;
    try {
        serialPort.Read( buffer, 11, 1500);
    }
    catch ( SerialPort::ReadTimeout e)
    {
        std::cout << "Timeout! Exiting..." << std::endl;
        timeout_flag = true;
    }

    ASSERT_FALSE(timeout_flag);

    //-- Check if connected
    std::string welcomeMessage = "[Debug] Ok!";
    bool diff_flag = false;

    for (int i = 0; i < (int) buffer.size(); i++)
    {
        if ( welcomeMessage[i] != buffer[i] )
            diff_flag = true;
    }

    if ( ! diff_flag )
        std::cout << "Connected! " << std::endl;

    ASSERT_FALSE( diff_flag);

    //-- Send the sinusoidal waveform data to the robot
    for (int i = 0; i < 200000; i+=20)
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints

        for (int j = 0; j < 8; j++)
        {
            int pos = ceil( 90 + 60 *  sin( 2*M_PI/4000.0 * i ));
            outputBuff.push_back( (char) pos );
        }

        serialPort.Write( outputBuff );

        usleep( 20000 );
    }

    //-- Close serial port and exit
    serialPort.Close();
}
