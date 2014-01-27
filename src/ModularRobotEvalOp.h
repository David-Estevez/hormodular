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

#include <ecf/ECF.h>
#include "ModularRobot/SimulatedModularRobot.h"
#include "Controller/GaitTable.h"

class ModularRobotEvalOp : public EvaluateOp
{
public:

        ~ModularRobotEvalOp();

        //! Loads custom-made registry entries to the ECF
        bool initialize(StateP state);

        //! This adds the custom-made registry entries to the ECF
        void registerParameters( StateP state);

        //! Objective function
        FitnessP evaluate(IndividualP individual);

 protected:
        SimulatedModularRobot * modularRobot;
        int n_modules;
        int max_runtime;
        int timestep;
        std::string simulation_file;
        std::string gaittable_file;

 private:
        void genotypeToGaitTable(FloatingPoint::FloatingPoint* genotype_amplitude, FloatingPoint::FloatingPoint *genotype_offset, FloatingPoint::FloatingPoint* genotype_phase );
};
