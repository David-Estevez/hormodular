//------------------------------------------------------------------------------
//-- SimulatedModule
//------------------------------------------------------------------------------
//--
//-- Module simulated on OpenRAVE
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

#ifndef SIMULATED_MODULE_H
#define SIMULATED_MODULE_H

#include <openrave-core.h>
#include <semaphore.h>

#include "SimulatedServo.h"

#include "Module.h"

class SimulatedModule: public Module
{
    public:
        SimulatedModule(uint8_t num_servos,
                        std::string gait_table_shape_file, std::string gait_table_limbs_file,
                        OpenRAVE::ControllerBasePtr openRave_pcontroller,
                        std::vector<int> joint_ids,
                        sem_t * update_time_sem,
                        std::vector<sem_t*> current_servo_sem);
        ~SimulatedModule();

        void setOpenRAVEController( OpenRAVE::ControllerBasePtr openRave_pcontroller );

    private:
        SimulatedModule();
};

#endif //-- SIMULATED_MODULE_H
