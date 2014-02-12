//------------------------------------------------------------------------------
//-- test_sin
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

#include <iostream>
#include <SerialStream.h>
#include <cmath>

int main(int argc, char * argv[] )
{
    //-- Check the serial port specified
    if (argc < 2)
    {
        std::cerr << "No serial port specified" << std::endl;
        return -1;
    }

    std::cout << "Serial port: " << argv[1] << std::endl;
    std::cout << "Opening... " << std::endl;

    //-- Create and open a serial port
    SerialPort serialPort( argv[1] );
    try
    {
        serialPort.Open( SerialPort::BAUD_57600, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE );
    }
    catch ( SerialPort::OpenFailed e )
    {
        std::cerr << "Error opening the serial port \"" << argv[1] << "\"" << std::endl;
        return -1;
    }

    //-- Read welcome message to check if connected to the robot
    SerialPort::DataBuffer buffer;
    try {
        serialPort.Read( buffer, 11, 1500);
    }
    catch ( SerialPort::ReadTimeout e)
    {
        std::cout << "Timeout! Exiting..." << std::endl;
        return -1;
    }

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
    return 0;
}
