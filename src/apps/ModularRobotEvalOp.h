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
//#include "SimulatedModularRobot.h"
#include "SimulatedModularRobotSingleThread.h"
#include "GaitTable.h"

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
        static const int MAX_AMPLITUDE = 60;
        static const int MAX_OFFSET = 10;
        static const int MAX_PHASE = 360;
        static const float MAX_FREQUENCY = 1.5;

        static const float MAX_AMP_0_5 = 0.5 * MAX_AMPLITUDE;
        static const float MAX_PHA_0_5 = 0.5 * MAX_PHASE;
        float MAX_FREQ_0_5;

        SimulatedModularRobotSingleThread * modularRobot;
        int n_modules;
        int max_runtime;
        int timestep;
        std::string config_file;

 private:
        void genotypeToGaitTable(FloatingPoint::FloatingPoint* genotype);
};
