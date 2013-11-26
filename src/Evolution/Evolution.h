/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   E V O L U T I O N   C L A S S   H E A D E R                                                                */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "ObjectiveFunctional.h"
#include "EvolutionaryAlgorithm.h"

#include "Robot.h"
#include "SimulationOpenRave.h"
#include "Y1ModularRobot.h"
#include "Controller.h"
#include "OscillationAnalyzer_OutputSignal.h"

namespace Flood
{

class Evolution : public ObjectiveFunctional
{

private:
  Robot *robot;
  Controller *controller;

public:

  //-- GENERAL CONSTRUCTOR WITH MULTILAYER PERCEPTRON OBJECT
  Evolution(MultilayerPerceptron*);

  //-- GENERAL CONSTRUCTOR WITH SIMULATION ENVIRONMENT OBJECT
  Evolution(MultilayerPerceptron*, Robot*, Controller*);

  //-- DEFAULT CONSTRUCTOR
  Evolution(void);


  //-- DESTRUCTOR
  virtual ~Evolution(void);


  //-- Objective methods
  double calculate_objective(); // Default objective function for debugging purpose.
  double calculate_objective(int,int); // TODO: To be removed from here nand ObjectiveFunction.h
  double calculate_objective(int,int,int);

};

}

#endif

