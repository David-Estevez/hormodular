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

#ifndef SERIAL_MODULE_H
#define SERIAL_MODULE_H

#include <semaphore.h>
#include <inttypes.h>

#include "SerialServo.h"
#include "Module.h"

class SerialModule: public Module
{
    public:
        SerialModule(uint8_t num_servos,
                     GaitTable *gait_table_shape, GaitTable *gait_table_limbs, pthread_mutex_t *gait_table_shape_mutex, pthread_mutex_t *gait_table_limbs_mutex,
                     std::vector<int *> pjoint_values,
                     sem_t * update_time_sem,
                     std::vector<sem_t*> current_servo_sem, bool invertJoints);
        ~SerialModule();

    private:
        SerialModule();
};

#endif //-- SIMULATED_MODULE_H
