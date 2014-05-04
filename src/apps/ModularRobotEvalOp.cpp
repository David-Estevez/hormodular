//------------------------------------------------------------------------------
//-- ModularRobotEvalOp
//------------------------------------------------------------------------------
//--
//-- Function evaluator (objective function) for the Modular Robot
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

#include "ModularRobotEvalOp.h"




void ModularRobotEvalOp::registerParameters(StateP state)
{
    state->getRegistry()->registerEntry("robot.modules", (voidP) (new uint(1)), ECF::UINT, "Number of modules" );
    state->getRegistry()->registerEntry("robot.runtime", (voidP) (new uint(10000)), ECF::UINT, "Max robot runtime (ms)" );
    state->getRegistry()->registerEntry("robot.timestep", (voidP) (new uint(1)), ECF::UINT, "Time step (ms)" );
    state->getRegistry()->registerEntry("robot.configfile", (voidP) (new std::string()), ECF::STRING, "Robot description file");

    state->getRegistry()->registerEntry("osc.maxamplitude", (voidP) (new uint(90)), ECF::UINT, "Max amplitude of oscillators");
    state->getRegistry()->registerEntry("osc.maxoffset", (voidP) (new uint(90)), ECF::UINT, "Max offset of oscillators");
    state->getRegistry()->registerEntry("osc.maxphase", (voidP) (new uint(360)), ECF::UINT, "Max phase of oscillators");
    state->getRegistry()->registerEntry("osc.maxfrequency", (voidP) (new float(1.0f)), ECF::FLOAT, "Max frequency of oscillators");
}

ModularRobotEvalOp::~ModularRobotEvalOp()
{
    robotInterface->destroy();
    delete robotInterface;
    robotInterface = NULL;

    for ( int i = 0; i < (int) oscillators.size(); i++)
    {
        delete oscillators[i];
        oscillators[i] = NULL;
    }
}

bool ModularRobotEvalOp::initialize(StateP state)
{
    //-- Get the robot values from the registry:
    //-----------------------------------------------------------------------------------------
    //-- Number of modules:
    voidP sptr = state->getRegistry()->getEntry("robot.modules");
    n_modules = *((uint*) sptr.get() );

    //-- Max runtime:
    sptr = state->getRegistry()->getEntry("robot.runtime");
    max_runtime = *((uint*) sptr.get() );

    //-- Time step:
    sptr = state->getRegistry()->getEntry("robot.timestep");
    timestep = *((uint*) sptr.get() );

    //-- Gait table file:
    sptr = state->getRegistry()->getEntry("robot.configfile");
    config_file = *((std::string*) sptr.get() );


    //-- Get the oscillator parameters from the registry:
    //---------------------------------------------------------------------------------------
    //-- Max amplitude:
    sptr = state->getRegistry()->getEntry("osc.maxamplitude");
    int max_amplitude = *((uint*) sptr.get());
    max_amp_0_5 = max_amplitude / 2.0;

    //-- Max offset:
    sptr = state->getRegistry()->getEntry("osc.maxoffset");
    max_offset = *((uint*) sptr.get());

    //-- Max phase:
    sptr = state->getRegistry()->getEntry("osc.maxphase");
    int max_phase = *((uint*) sptr.get());
    max_pha_0_5 = max_phase / 2.0;

    //-- Max frequency:
    sptr = state->getRegistry()->getEntry("osc.maxfrequency");
    float max_frequency = *((float*) sptr.get());
    max_freq_0_5 = max_frequency / 2.0;


    //-- Create and configure the robot parts
    //---------------------------------------------------------------------------------------
    //-- Read test data
    configParser.parse(config_file);

    if ( configParser.getNumModules() != n_modules )
    {
        std::cerr << "[Evolve] Error: number of modules not consitent between config file and "
                  << "robot model." << std::endl;
        return false;
    }
    //-- Create robot, simulated type
    robotInterface = createModularRobotInterface( "simulated", configParser);

    //-- Create sinusoidal oscillators with the test parameters
    oscillators.clear();
    for ( int i = 0; i < configParser.getNumModules(); i++)
        oscillators.push_back(new SinusoidalOscillator( 0, 0, 0, 4000));

    robotInterface->reset();

    return true;
}

FitnessP ModularRobotEvalOp::evaluate(IndividualP individual)
{
    //-- Create a fitness object to maximize the objective (distance travelled in m)
    FitnessP fitness (new FitnessMax);

    //-- We get the genotype:
    FloatingPoint::FloatingPoint* genotype = (FloatingPoint::FloatingPoint*) individual->getGenotype(0).get();

    //-- Value to store the fitness (distance travelled)
    double fitness_value = 0;

    //-- Here we record the genotypes on a gait table file:
    std::cout << "[Evolve] Convert to gait table!" << std::endl;
    genotypeToRobot( genotype );

    //-- Reset the robot:
    std::cout << "[Evolve] Reset!" << std::endl;
    robotInterface->reset();

    //-- Run the robot:
    std::cout << "[Evolve] Run!" << std::endl;

    //-- Here you put the main loop
    unsigned long elapsed_time = 0;
    joint_values.clear();
    for (int i = 0; i < (int) n_modules; i++)
        joint_values.push_back(0);

    while( elapsed_time < max_runtime )
    {
        //-- Update joint values
        for ( int i = 0; i < (int) oscillators.size(); i++)
            joint_values[i] = oscillators[i]->calculatePos(elapsed_time);

        //-- Send joint values
        robotInterface->sendJointValues(joint_values, timestep);

        elapsed_time+=timestep;
    }

    //-- Select the fitness value (distance travelled in m)
    fitness_value = robotInterface->getTravelledDistance();

    //-- Set the fitness value
    fitness->setValue( fitness_value);

    std::cout << "[Evolve] Return!" << std::endl;
    return fitness;
}

void ModularRobotEvalOp::genotypeToRobot(FloatingPoint::FloatingPoint *genotype)
{
    std::vector<float> amplitudes;
    std::vector<float> offsets;
    std::vector<float> phases;
    float frequency;

    for(int i = 0; i < (int) n_modules; i++)
    {
        float amplitude = genotype->realValue[i*3] * max_amp_0_5 + max_amp_0_5;
        float offset = genotype->realValue[i*3+1] * max_offset;
        float phase = genotype->realValue[i*3+2] * max_pha_0_5 + max_pha_0_5;

        amplitudes.push_back(amplitude);
        offsets.push_back(offset);
        phases.push_back(phase);
    }

    frequency = genotype->realValue[n_modules*3] * max_freq_0_5 + max_freq_0_5;

    //-- Set the parameters to the oscillators:
    int period = (int) ( 1000.0 / frequency);

    for (int i = 0; i < (int) oscillators.size(); i++)
        oscillators[i]->setParameters( amplitudes[i], offsets[i], phases[i], period);

}
