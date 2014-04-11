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
}

ModularRobotEvalOp::~ModularRobotEvalOp()
{
    delete modularRobot;
}

bool ModularRobotEvalOp::initialize(StateP state)
{
    MAX_FREQ_0_5 = 0.5 * MAX_FREQUENCY;

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

    //-- Gait table file:
    sptr = state->getRegistry()->getEntry("robot.configfile");
    config_file = *((std::string*) sptr.get() );


    //-- Create and configure the robot:
    modularRobot = new SimulatedModularRobotSingleThread(config_file);
    modularRobot->setMaxRuntime(max_runtime);
    modularRobot->setTimeStep(timestep);
    modularRobot->selectDistanceCalculationMethod( ModularRobot::START_END_POINTS );
    //modularRobot->showSimulationViewer();

    modularRobot->reset();

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
    std::cout << "[Evolve] Convert to gait table!" << std::endl;
    genotypeToGaitTable( genotype );

    //-- Reset the robot:
    std::cout << "[Evolve] Reset!" << std::endl;
    modularRobot->reset();

    //-- Run the robot:
    std::cout << "[Evolve] Run!" << std::endl;
    modularRobot->run();

    //-- Select the fitness value (distance travelled, in this case)
    fitness_value = modularRobot->getDistanceTravelled();

    //-- Set the fitness value
    fitness->setValue( fitness_value);

    std::cout << "[Evolve] Return!" << std::endl;
    return fitness;
}

void ModularRobotEvalOp::genotypeToGaitTable(FloatingPoint::FloatingPoint *genotype)
{
    //-- Get robot configuration:
    std::cout << "[Evolve] get configparser!" << std::endl;
    ConfigParser configParser = modularRobot->getConfigParser();

    //-- Get gait tables folder:
    std::cout << "[Evolve] Get gait tables folder!" << std::endl;
    std::string gait_tables_folder = configParser.getGaitTableFolder();

    //-- Open the gait tables:
    std::cout << "[Evolve] Open the gait tables!" << std::endl;
    GaitTable shape_gait_table( gait_tables_folder+"/gait_table_shape.txt", 3);
    GaitTable limbs_gait_table( gait_tables_folder+"/gait_table_limbs.txt", 5);

    //-- Get the ids:
    std::vector<unsigned long> shape_ids = configParser.getShapeIDs();
    std::vector<int> limbs_ids = configParser.getNumLimbsIDs();

    //-- Set the genotype values to the table:
    std::cout << "[Evolve] get Set the genotype values to the table! [shape]" << std::endl;
    for (int i = 0; i < (int)shape_ids.size(); i++ )
    {
        float amplitude = genotype->realValue[i*3] * MAX_AMP_0_5 + MAX_AMP_0_5;
        float offset = genotype->realValue[i*3+1] * MAX_OFFSET;
        float phase = genotype->realValue[i*3+2] * MAX_PHA_0_5 + MAX_PHA_0_5;

        std::vector<float> v;
        v.push_back(amplitude);
        v.push_back(offset);
        v.push_back(phase);

        shape_gait_table.setRow(shape_ids[i], v);
    }

    std::cout << "[Evolve] get Set the genotype values to the table! [limbs]" << std::endl;
    for (int i = 0; i < (int)limbs_ids.size(); i++)
    {
        float alpha = genotype->realValue[shape_ids.size()*3 + i*5];
        float omega = genotype->realValue[shape_ids.size()*3 + i*5+1];
        float phi = genotype->realValue[shape_ids.size()*3 + i*5+2] * MAX_PHA_0_5 + MAX_PHA_0_5;
        float phase_limb = genotype->realValue[shape_ids.size()*3 + i*5+3] * MAX_PHA_0_5 + MAX_PHA_0_5;;
        float frequency = genotype->realValue[shape_ids.size()*3 + i*5+4] * MAX_FREQ_0_5 + MAX_FREQ_0_5;

        std::vector<float> v;
        v.push_back(alpha);
        v.push_back(omega);
        v.push_back(phi);
        v.push_back(phase_limb);
        v.push_back(frequency);

        limbs_gait_table.setRow(limbs_ids[i], v);
    }

}
