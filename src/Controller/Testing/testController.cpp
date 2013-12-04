#include "Robot.h"
#include "SimulationOpenRave.h"
#include "Controller.h"

#include "stdint.h"
#include "assert.h"
#include <iostream>
#include <string>

#include <pthread.h>

void* runController( void* arg );

int main(void)
{
    std::vector< std::string > gait_table_file;
    gait_table_file.push_back("../../data/gait tables/gait_table_straight_3_modules_pyp.txt");
    gait_table_file.push_back("../../data/gait tables/gait_table_sidewalk_3_modules_pyp.txt");
    gait_table_file.push_back("../../data/gait tables/gait_table_turn_3_modules_pyp.txt");

    int gaits = gait_table_file.size();

    //-- Create a robot
    std::cout << "Testing controller..." << std::endl;
    SimulationOpenRave module_OpenRave;
    module_OpenRave.set_number_of_modules(3);
    module_OpenRave.set_scene_file_name("../../data/models/Minicube-II.env.xml");
    module_OpenRave.init_simu_env("");
    module_OpenRave.load_controller("servocontroller");
    module_OpenRave.set_evaluation_method("Euclidean_Distance_Final");
    module_OpenRave.reset_robot();
    module_OpenRave.set_moduleServo_position(0, 90);
    module_OpenRave.set_moduleServo_position(1, 45);

    //-- Wait five seconds so we can find the robot:
    for (int i = 0; i<5; i++)
    {
        std::cout <<"Starting in " << i << "..." << std::endl;
        sleep(1);
    }

    //-- Create 3 controllers
    Controller hormoneController1( &module_OpenRave );
    Controller hormoneController2( &module_OpenRave );
    Controller hormoneController3( &module_OpenRave );


    for (int i = 0; i < gaits; i++ )
    {
        //-- Setup controllers
        hormoneController1.reset();
        hormoneController2.reset();
        hormoneController3.reset();

        hormoneController1.setId(0);
        hormoneController2.setId(1);
        hormoneController3.setId(2);

        hormoneController1.loadGaitTable( gait_table_file.at(i) );
        hormoneController2.loadGaitTable( gait_table_file.at(i) );
        hormoneController3.loadGaitTable( gait_table_file.at(i) );

         //-- Create three threads:
         pthread_t controller1, controller2, controller3;

         pthread_create( &controller1, NULL, runController, (void*) &hormoneController1);
         pthread_create( &controller2, NULL, runController, (void*) &hormoneController2);
         pthread_create( &controller3, NULL, runController, (void*) &hormoneController3);

         //-- Wait for the threads to finish
         pthread_join(controller1, NULL);
         pthread_join(controller2, NULL);
         pthread_join(controller3, NULL);

    }

    while(1);     //-- Avoid openrave crashing

    return 0;
}

//-- Wrapper for the controller run member function
void* runController( void* arg )
{
    Controller * hormoneController = (Controller *)arg;

    std::cout<<"Starting controller: " << (int) hormoneController->getId() << std::endl;
    hormoneController->run( 5000);

    return NULL;
}
