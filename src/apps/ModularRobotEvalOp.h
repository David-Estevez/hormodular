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
#include "ConfigParser.h"
#include "SinusoidalOscillator.h"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"

using namespace hormodular;


/*!
 *  \class ModularRobotEvalOp
 *  \brief Function evaluator (objective function) for the Modular Robot
 */
class ModularRobotEvalOp : public EvaluateOp
{
    public:

        ~ModularRobotEvalOp();

        //! \brief Loads custom-made registry entries to the ECF
        bool initialize(StateP state);

        //! \brief This adds the custom-made registry entries to the ECF
        void registerParameters( StateP state);

        //!\brief Objective function
        FitnessP evaluate(IndividualP individual);

    protected:

        /***** Constants to bound the oscillator values *****/
        int max_offset;
        float max_amp_0_5;
        float max_pha_0_5;
        float max_freq_0_5;

        /* Other needed stuff */
        ConfigParser configParser;
        std::vector<Oscillator *> oscillators;
        ModularRobotInterface * robotInterface;
        std::vector<float> joint_values;

        int n_modules;
        unsigned long max_runtime;
        float timestep;
        std::string config_file;

    private:
        //! \brief Extract the oscillator parameters encoded in the genotype and set them in the oscillators
        void genotypeToRobot(FloatingPoint::FloatingPoint* genotype);
};
