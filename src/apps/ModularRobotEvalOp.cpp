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
    modularRobot->setTimeStep(timestep);
    modularRobot->selectDistanceCalculationMethod( ModularRobot::START_END_POINTS );

    return true;
}

FitnessP ModularRobotEvalOp::evaluate(IndividualP individual)
{
    //-- Create a fitness object to maximize the objective (distance travelled)
    FitnessP fitness (new FitnessMax);

    //-- We get the genotype:
    FloatingPoint::FloatingPoint* genotype = (FloatingPoint::FloatingPoint*) individual->getGenotype(0).get();

    //-- Value to store the fitness (distance travelled)
    double fitness_value = 0;

    //-- Here we record the genotypes on a gait table file:
    genotypeToGaitTable( genotype );

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

void ModularRobotEvalOp::genotypeToGaitTable(FloatingPoint::FloatingPoint *genotype)
{
    //-- Create temporal table:
    GaitTable temp_table( n_modules, 3);

    //-- Set the genotype values to the table:
    for (int i = 0; i < n_modules; i++ )
    {
        //-- Set amplitude
        temp_table.setValue(i, 0, genotype->realValue[i*3] * 45 + 45);

        //-- Set offset
        temp_table.setValue(i, 1, genotype->realValue[i*3+1] * 90);

        //-- Set phase
        temp_table.setValue(i, 2, genotype->realValue[i*3+2] * 180 + 180);
    }

    //-- Save the table to a file:
    temp_table.saveToFile(gaittable_file);


}
