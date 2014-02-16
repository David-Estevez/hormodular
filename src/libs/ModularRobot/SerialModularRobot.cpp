#include "SerialModularRobot.h"



SerialModularRobot::SerialModularRobot(std::string port_name, int n_modules, std::string gait_table_file)
{
    //-- Create serial port
    serial_port_name = port_name;
    serial_port = new SerialPort( port_name );
    try
    {
        serial_port->Open( SerialPort::BAUD_57600, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE );
    }
    catch ( SerialPort::OpenFailed e )
    {
        std::cerr << "Error opening the serial port \"" << serial_port_name << "\"" << std::endl;
        exit(-1);
    }

    if ( ! checkConnection() )
    {
        std::cerr << "Error communicating with the robot. Exiting..." << std::endl;
        exit(-1);
    }

    //-- Create array to store the joint positions
    joint_position_array = new int[n_modules];
    for ( int i = 0; i < n_modules; i ++)
        joint_position_array[i] = 0;

    //-- Create sync semaphores
    sem_init( &updateTime_semaphore, 0, 0);

    modules_semaphores = new sem_t[n_modules];
    for( int i = 0; i < n_modules; i++)
        sem_init( modules_semaphores+i, 0, 1);

    //-- Create modules:
    for( int i = 0; i< n_modules; i++)
    {
        std::vector<sem_t* > temp_semaphores;
        temp_semaphores.push_back( modules_semaphores+i);

        std::vector<int *> temp_joint_values;
        temp_joint_values.push_back( joint_position_array+i);
        Module * temp_module;
        if ( i != 2 )
        {
            temp_module = new SerialModule( 1, gait_table_file, temp_joint_values,
                                                   &updateTime_semaphore, temp_semaphores, false);
        }
        else
        {
            temp_module = new SerialModule( 1, gait_table_file, temp_joint_values,
                                                       &updateTime_semaphore, temp_semaphores, true);
        }
        modules.push_back( temp_module );
    }

}



SerialModularRobot::~SerialModularRobot()
{
    //-- Delete modules
    //-- ??

    //-- Free semaphores
    delete[] modules_semaphores;

    //-- Free serial port
    serial_port->Close();
    delete serial_port;

    //-- Free joint pos array
    delete[] joint_position_array;
}



void SerialModularRobot::reset()
{
    //-- Reopen serial port
    serial_port->Close();
    try
    {
        serial_port->Open( SerialPort::BAUD_57600, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE );
    }
    catch ( SerialPort::OpenFailed e )
    {
        std::cerr << "Error opening the serial port \"" << serial_port_name << "\"" << std::endl;
        exit(-1);
    }

    if ( ! checkConnection() )
    {
        std::cerr << "Error communicating with the robot. Exiting..." << std::endl;
        exit(-1);
    }

    //-- Reset joint positions
    for ( int i = 0; i < this->modules.size() ; i ++)
        joint_position_array[i] = 0;

    //-- Reset semaphores:
    sem_init( &updateTime_semaphore, 0, 0);

    for( int i = 0; i < (int) modules.size(); i++)
        sem_init( modules_semaphores+i, 0, 1);

    //-- Call the parent reset function
    this->ModularRobot::reset();
}



bool SerialModularRobot::checkConnection()
{
    //-- Read welcome message to check if connected to the robot
    SerialPort::DataBuffer buffer;
    try
    {
        serial_port->Read( buffer, 13, 1500);
    }
    catch ( SerialPort::ReadTimeout e)
    {
        std::cout << "Timeout! Exiting..." << std::endl;
        return -1;
    }

    //-- Check if connected
    std::string welcomeMessage = "[Debug] Ok!\r\n";
    bool diff_flag = false;

    for (int i = 0; i < (int) buffer.size(); i++)
        if ( welcomeMessage[i] != buffer[i] )
            diff_flag = true;


    return !diff_flag;
}



void SerialModularRobot::updateTime()
{
    std::cout << "[Debug] Running robot with " << this->modules.size() << " modules for " << max_runtime_ms << "ms." << std::endl;

    while (time_elapsed < max_runtime_ms)
    {
        //-- Lock this thread semaphores:
        for (int i = 0; i < (int) modules.size(); i++)
            sem_wait( &updateTime_semaphore);

        //-- Increment time
        for(int i = 0; i < (int) modules.size(); i++)
            modules.at(i)->incrementTime( time_step_ms);

        //-- Send values to robot:
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints
        std::cout << "[Debug] Command: " ;
        for (int i = 0; i < this->modules.size() ; i++)
        {
            outputBuff.push_back( (char) joint_position_array[i] );
            std::cout << (int) outputBuff[i+1] << " ";
        }
        std::cout << std::endl;
        serial_port->Write( outputBuff );

        //-- Unlock modules threads:
        for (int i = 0; i < (int) modules.size(); i++)
            sem_post( modules_semaphores+i);

        //-- Increment time counter
        time_elapsed += time_step_ms;

        //-- Calculate distance travelled this step:
        //calculateDistanceTravelled();

        //-- Wait for time period
        usleep( 1000*time_step_ms); //-- TODO: Set this to a variable
    }
}



void SerialModularRobot::calculatePos()
{
    //-- This, currently, does nothing
}
