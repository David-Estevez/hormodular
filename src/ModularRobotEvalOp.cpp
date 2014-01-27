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
    state->getRegistry()->registerEntry("robot.simulationfile", (voidP) (new std::string()), ECF::STRING, "Simulation model file");
    state->getRegistry()->registerEntry("robot.gaittablefile", (voidP) (new std::string() ), ECF::STRING, "Gait table file");
}

ModularRobotEvalOp::~ModularRobotEvalOp()
{
    delete modularRobot;
}

bool ModularRobotEvalOp::initialize(StateP state)
{
    //-- Get the variables values from the registry:
    //-- Number of modules:
    voidP sptr = state->getRegistry()->getEntry("robot.modules");
    n_modules = *((uint*) sptr.get() );

    //-- Max runtime:
    sptr = state->getRegistry()->getEntry("robot.runtime");
    max_runtime = *((uint*) sptr.get() );

    //-- Time step:
    sptr = state->getRegistry()->getEntry("robot.timestep");
    timestep = *((uint*) sptr.get() );

    //-- Simulation file:
    sptr = state->getRegistry()->getEntry("robot.simulationfile");
    simulation_file = *((std::string*) sptr.get() );

    //-- Gait table file:
    sptr = state->getRegistry()->getEntry("robot.gaittablefile");
    gaittable_file = *((std::string*) sptr.get() );


    //-- Create and configure the robot:
    modularRobot = new SimulatedModularRobot( simulation_file, gaittable_file);
    modularRobot->setMaxRuntime(max_runtime);
    modularRobot->setTimeStep(1);
    modularRobot->selectDistanceCalculationMethod( ModularRobot::START_END_POINTS );

    return true;
}

FitnessP ModularRobotEvalOp::evaluate(IndividualP individual)
{
    //-- Create a fitness object to maximize the objective (distance travelled)
    FitnessP fitness (new FitnessMax);

    //-- We get the genotypes:
    FloatingPoint::FloatingPoint* genotype_amplitude = (FloatingPoint::FloatingPoint*) individual->getGenotype(0).get();
    FloatingPoint::FloatingPoint* genotype_offset = (FloatingPoint::FloatingPoint*) individual->getGenotype(1).get();
    FloatingPoint::FloatingPoint* genotype_phase = (FloatingPoint::FloatingPoint*) individual->getGenotype(2).get();

    //-- Value to store the fitness (distance travelled)
    double fitness_value = 0;

    //-- Here we record the genotypes on a gait table file:
    genotypeToGaitTable( genotype_amplitude, genotype_offset, genotype_phase );

    //-- Reset the robot:
    modularRobot->reset();

    //-- Run the robot:
    modularRobot->run();

    //-- Select the fitness value (distance travelled, in this case)
    fitness_value = modularRobot->getDistanceTravelled();

    //-- Set the fitness value
    fitness->setValue( fitness_value);
    return fitness;
}

void ModularRobotEvalOp::genotypeToGaitTable(FloatingPoint::FloatingPoint *genotype_amplitude, FloatingPoint::FloatingPoint* genotype_offset, FloatingPoint::FloatingPoint *genotype_phase)
{
    //-- Create temporal table:
    GaitTable temp_table( n_modules, 3);

    //-- Set the genotype values to the table:
    for (int i = 0; i < n_modules; i ++ )
    {
        //-- Set amplitude
        temp_table.set(i, 0, genotype_amplitude->realValue[i]);

        //-- Set offset
        temp_table.set(i, 1, genotype_offset->realValue[i]);

        //-- Set phase
        temp_table.set(i, 2, genotype_phase->realValue[i]);
    }

    //-- Save the table to a file:
    temp_table.saveToFile(gaittable_file);


}
