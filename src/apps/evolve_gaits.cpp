//------------------------------------------------------------------------------
//-- evolve-gaits
//------------------------------------------------------------------------------
//--
//-- Evolves simple locomotion gaits for forward locomotion
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
#include "ModularRobotEvalOp.h"


int main(int argc, char **argv)
{
    StateP state (new State);

    // set the evaluation operator
    state->setEvalOp(new ModularRobotEvalOp);

    state->initialize(argc, argv);
    state->run();

    return 0;
}
