#include "Controller.h"


Controller::Controller()
{
    this->oscillator = NULL;
    this->control_table = NULL;
    this->reset();
}

Controller::Controller(Robot *module)
{
    this->oscillator = NULL;
    this->control_table = NULL;
    this->reset();
    this->module = module;
}

Controller::~Controller()
{
    delete oscillator;
    delete control_table;
}

int Controller::run()
{

    //-- Read values of the oscillator from the gait table:
    mappingFunction();

    static const float simulation_step = 0.0025; //-- uS
    unsigned long currentTime =  0;

    int counter = 0;

    while(1)
    {
        currentTime = module->get_elapsed_evaluation_time();
        float position = oscillator->calculatePos( currentTime / 1000 ); //-- localtime returns us
        module->set_moduleServo_position(id, position -90);
        module->step("");

        std::cout <<"[Debug][Controller] ID:" << (int) id << " Iteration: " << counter++ << " Position: " << position << std::endl;

        while( module->get_elapsed_evaluation_time() - currentTime < simulation_step );
    }
    return 0;
}

int Controller::reset()
{
    id = 0;
    internal_time = 0;
    adjust_time = 0;

    if (oscillator != NULL) delete oscillator;
    if (control_table != NULL) delete control_table;

    oscillator = new SinusoidalOscillator( 0, 0, 0, 0);
    control_table = new GaitTable(1, 3);

    return 0;
}

int Controller::loadGaitTable( const std::string& file_path )
{
    //-- Free previous control table:
    if (control_table != NULL) delete control_table;

    //-- Load new data
    control_table = new GaitTable( file_path);

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
