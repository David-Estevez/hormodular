//------------------------------------------------------------------------------
//-- SerialModule
//------------------------------------------------------------------------------
//--
//-- Module of the actual robot, controlled by serial port
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

#include "SerialModule.h"

SerialModule::SerialModule(uint8_t num_servos, std::string gait_table_file, std::vector<int *> pjoint_values,
                           sem_t *update_time_sem, std::vector<sem_t *> current_servo_sem,
                           bool invertJoints )
    : Module( num_servos, gait_table_file )
{
    SerialServo * serial_servos = new SerialServo[num_servos];

    for ( int i = 0; i < num_servos; i++)
    {
        serial_servos[i].setJointValuePtr( pjoint_values[i]);
        serial_servos[i].setSemaphores( update_time_sem, current_servo_sem[i]);
        serial_servos[i].init();
        serial_servos[i].setJointInvert( invertJoints);
    }

    this->servos = serial_servos;

    //-- Reset Module
    this->reset();
}

SerialModule::~SerialModule()
{
    delete[] servos;
}
