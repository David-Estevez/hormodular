#include "Controller.h"


Controller::Controller()
{
    this->oscillator = new SinusoidalOscillator( 0, 0, 0, 0);;
    this->control_table = new GaitTable(1, 3);
    this->reset();
}

Controller::Controller(Robot *module)
{
    this->oscillator = new SinusoidalOscillator( 0, 0, 0, 0);;
    this->control_table = new GaitTable(1, 3);
    this->reset();
    this->module = module;
}

Controller::~Controller()
{
    delete oscillator;
    delete control_table;
}

int Controller::run( uint32_t max_iter )
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
    }
    while ( counter < max_iter || run_forever);

    std::cout << "Controller: " << (int) id << " ended!" << std::endl;
    return 0;
}

int Controller::reset()
{
    id = 0;
    internal_time = 0;
    adjust_time = 0;
    oscillator->setParameters(0,0,0,0);

    delete control_table;
    control_table = new GaitTable(1, 3);

    return 0;
}

int Controller::loadGaitTable( const std::string& file_path )
{
    //-- Load new data
    control_table->loadFromFile( file_path);

    return 0;
}

//-- Getters and setters (to be modified later)
//-----------------------------------------------------------------------------------
Robot *Controller::getModule() const
{
    return module;
}

void Controller::setModule(Robot *value)
{
    module = value;
}

uint8_t Controller::getId() const
{
    return id;
}

void Controller::setId(const uint8_t &value)
{
    id = value;
}

uint32_t Controller::getInternal_time() const
{
    return internal_time;
}

void Controller::setInternal_time(const uint32_t &value)
{
    internal_time = value;
}


int32_t Controller::getAdjust_time() const
{
    return adjust_time;
}

void Controller::setAdjust_time(const int32_t &value)
{
    adjust_time = value;
}

Oscillator *Controller::getOscillator() const
{
    return oscillator;
}

void Controller::setOscillator(Oscillator *value)
{
    oscillator = value;
}

GaitTable *Controller::getControl_table() const
{
    return control_table;
}

void Controller::setControl_table(GaitTable *value)
{
    control_table = value;
}

//-- Private functions
//-----------------------------------------------------------------------------------

int Controller::mappingFunction()
{
    oscillator->setAmplitude( control_table->at(id, 0) );
    oscillator->setOffset(control_table->at(id, 1));
    oscillator->setPhase( control_table->at(id, 2));

    return 0;
}

uint32_t Controller::localtime()
{
    return internal_time + adjust_time;
}
