/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   F I L E H A N D L E R   C L A S S   H E A D E R                                                            */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef FILEHANDLER_H
#define FILEHANDLER_H

namespace Flood
{
  class EvolutionaryAlgorithm;
}

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "EvolutionaryAlgorithm.h"
#include "Robot.h"
#include "SimulationOpenRave.h"
#include "Y1ModularRobot.h"
#include "Controller.h"
#include "MultilayerPerceptron.h"


class FileHandler
{

private:
  std::fstream myFile;
  std::string myFile_name;

public:

  // CONSTRUCTOR FOR SAVING ELITE GENE POPULATION
  FileHandler(std::string, bool, bool, Flood::EvolutionaryAlgorithm*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*);

  // CONSTRUCTOR FOR EXTRACTING PARAMETERS FROM PARAMETERS FILE
  FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*);

  // CONSTRUCTOR FOR EXTRACTING PARAMETERS FROM GENE FILE
  FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*);

  // CONSTRUCTOR FOR EXTRACTING PARAMETERS FROM GENE FILE AND FITNESS FILE
  FileHandler(char*, char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*, std::vector<double>*);

  // CONSTRUCTOR FOR EXTRACTING MLP PARAMETERS FROM GENE FILE
  FileHandler(char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*);

  // CONSTRUCTOR FOR EXTRACTING MLP PARAMETERS FROM GENE FILE AND FITNESS FILE
  FileHandler(char*, char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*, std::vector<double>*);

  // DESTRUCTOR
  virtual ~FileHandler(void);


  // Methods
  void save_gene(int, Flood::Vector<double>);
  void load_Robot_parameters(std::fstream&, Robot*);
  void load_SimEnv_parameters(std::fstream&, SimulationOpenRave*);
  void load_Controller_parameters(std::fstream&, Controller*);
  void load_NN_parameters(std::fstream&, Flood::MultilayerPerceptron*);
  void load_independent_parameters(std::fstream&, Flood::MultilayerPerceptron*);
  void load_genes(std::fstream&, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*);
  void load_elite_fitness(std::fstream&, std::vector<double>*);
};

#endif

