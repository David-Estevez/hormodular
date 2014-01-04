#include "Controller.h"


Controller::Controller(Servo *servos, std::string gait_table_file, uint32_t *time)
{
    //-- Default values
    this->servos = servos;
    this->gait_table_file = gait_table_file;
    this->oscillator = new SinusoidalOscillator( 0, 0, 0, 0);
    this->control_table = new GaitTable( gait_table_file);
    this->id = 0;
    this->internal_time = time;

    //-- Create mutexes
    pthread_mutex_init( &id_mutex, NULL);
    pthread_mutex_init( &oscillator_mutex, NULL);

    //-- Reset module
    this->reset();
}

Controller::~Controller()
{
    delete oscillator;
    delete control_table;
}

/*int Controller::run( uint32_t max_iter )
{
    //-- If run time is 0, run the controller forever
    bool run_forever = max_iter == 0;

    //-- Read values of the oscillator from the gait table:
    mappingFunction();

    //-- Simulation variables:
    static const float simulation_step = 0.0025; //-- uS
    unsigned long currentTime =  0;
    int counter = 0;

    do
    {
        currentTime = module->get_elapsed_evaluation_time();
        float position = oscillator->calculatePos( currentTime / 1000 ); //-- localtime returns us
        module->set_moduleServo_position(id, position -90);
        module->step("");

        std::cout <<"[Debug][Controller] ID:" << (int) id << " Iteration: " << counter++ << " Position: " << position << std::endl;

        while( module->get_elapsed_evaluation_time() - currentTime < simulation_step );
        //usleep(2500);
    }
    while ( counter < max_iter || run_forever);

    std::cout << "Controller: " << (int) id << " ended!" << std::endl;
    return 0;
} */

void Controller::reset()
{
    id = 0;
    adjust_time = 0; //! \todo make this random to test sync
    oscillator->setParameters(0,0,0,0);
    loadGaitTable();

    //-- Run controller once to start oscillator parameters
    runController();
}

void Controller::loadGaitTable()
{
    control_table->loadFromFile( gait_table_file);
}

void Controller::runOscillator()
{
    //-- Calculate actuator new position
    float angle = oscillator->calculatePos( localtime() );

    //-- Lock the semaphore

    //-- Move the servo
    servos[0].write( angle);

    //-- Unlock the semaphore
}


//-- Private functions
//-----------------------------------------------------------------------------------

void Controller::runController()
{
    //-- Lock the oscillator & id mutexes
    pthread_mutex_lock( &oscillator_mutex);
    pthread_mutex_lock( &id_mutex);

    //-- Recalculate oscillator parameters according to the current state
    oscillator->setAmplitude( control_table->at(id, 0) );
    oscillator->setOffset(control_table->at(id, 1));
    oscillator->setPhase( control_table->at(id, 2));

    //-- Unlock the oscillator & id mutexes
    pthread_mutex_unlock( &oscillator_mutex);
    pthread_mutex_unlock(&id_mutex);

}

uint32_t Controller::localtime()
{
    return *internal_time + adjust_time;
}
