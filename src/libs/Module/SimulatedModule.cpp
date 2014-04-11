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

#include "SimulatedModule.h"

SimulatedModule::SimulatedModule(uint8_t num_servos,
                                  GaitTable* gait_table_shape, GaitTable*  gait_table_limbs,
                                  pthread_mutex_t *gait_table_shape_mutex, pthread_mutex_t *gait_table_limbs_mutex,

                                  OpenRAVE::ControllerBasePtr openRave_pcontroller,
                                  std::vector<int> joint_ids,
                                  sem_t * update_time_sem, std::vector<sem_t*> current_servo_sem)
    : Module( num_servos, gait_table_shape, gait_table_limbs, gait_table_shape_mutex, gait_table_limbs_mutex )
{
    SimulatedServo * sim_servos = new SimulatedServo[num_servos];

    for (int i = 0; i < num_servos; i++)
    {
        sim_servos[i].setOpenRaveController( openRave_pcontroller );
        sim_servos[i].setJointID( joint_ids[i] );
        sim_servos[i].setSemaphores( update_time_sem, current_servo_sem[i]);
        sim_servos[i].init();
    }

    this->servos = sim_servos;

    //-- Reset module
    this->reset();
}

SimulatedModule::~SimulatedModule()
{
    delete[] servos;
}

void SimulatedModule::setOpenRAVEController(OpenRAVE::ControllerBasePtr openRave_pcontroller)
{
    for (int i = 0; i < num_servos; i++)
    {
        ((SimulatedServo *)servos)[i].setOpenRaveController( openRave_pcontroller );
        ((SimulatedServo *)servos)[i].init();
    }
}

