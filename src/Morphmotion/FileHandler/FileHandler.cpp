/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   M Y F I L E   C L A S S                                                                                    */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/

#include "FileHandler.h"

// With Flood::EvolutionaryAlgorithm*
// CONSTRUCTOR FOR SAVING ELITE GENE POPULATION
FileHandler::FileHandler(std::string note,
               bool gen0_preeval,
               bool gen0_aug_pop,
               Flood::EvolutionaryAlgorithm *ea,
               Robot *robot,
               SimulationOpenRave *simuOR,
               Controller *controller,
               Flood::MultilayerPerceptron *mlp)
{
  time_t rawtime;
  struct tm * timeinfo;
  char filename[100];
  stringstream ss;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strftime (filename, 100, "_%m_%d_%H_%M_elite_population.gne", timeinfo);
  ss << "../Evolution_Files/" << robot->get_robot_environment() << "/" << robot->get_robot_type() << "/" << controller->get_controller_type() << "/Gene_Files/" << robot->get_robot_environment() << filename;

  myFile_name = ss.str();
  cout <<" Opening elite_population data file: " << myFile_name << endl;
  myFile.open(myFile_name.c_str(), fstream::in | fstream::out | fstream::app);

  myFile << "<Morphomotion: Flood + OpenRave + Y1>" << std::endl;
  myFile << std::endl << "<FileType>" << std::endl << "   GeneFile" << std::endl << "</FileType>" << std::endl;

  if(note != "No Notes")
  {
    myFile << std::endl << "<Note>" << std::endl << note << std::endl << "</Note>" << std::endl;
  }

  myFile << std::endl << "<Evolution>" << std::endl;
  myFile << "\t<FitnessAssignmentMethod>" << std::endl << "\t   " << ea->get_fitness_assignment_method_name() << std::endl << "\t</FitnessAssignmentMethod>" << std::endl;
  myFile << std::endl << "\t<SelectionMethod>" << std::endl << "\t   " << ea->get_selection_method_name() << std::endl << "\t</SelectionMethod>" << std::endl;
  myFile << std::endl << "\t<RecombinationMethod>" << std::endl << "\t   " << ea->get_recombination_method_name() << std::endl << "\t</RecombinationMethod>" << std::endl;
  myFile << std::endl << "\t<MutationMethod>" << std::endl << "\t   " << ea->get_mutation_method_name() << std::endl << "\t</MutationMethod>" << std::endl;
  myFile << std::endl << "\t<EvaluationMethod>" << std::endl << "\t   " << robot->get_evaluation_method() << std::endl << "\t</EvaluationMethod>" << std::endl;
  myFile << std::endl << "\t<PopulationSize>" << std::endl << "\t   " << ea->get_population_size() << std::endl << "\t</PopulationSize>" << std::endl;
  myFile << std::endl << "\t<CrossoverPercentage>" << std::endl << "\t   " << ea->get_crossover_percentage() << std::endl << "\t</CrossoverPercentage>" << std::endl;
  myFile << std::endl << "\t<Elitism>" << std::endl << "\t   " << ea->get_elitism() << std::endl << "\t</Elitism>" << std::endl;
  myFile << std::endl << "\t<ElitismPercentage>" << std::endl << "\t   " << ea->get_elitism_percentage() << std::endl << "\t</ElitismPercentage>" << std::endl;
  myFile << std::endl << "\t<SelectivePressure>" << std::endl << "\t   " << ea->get_selective_pressure() << std::endl << "\t</SelectivePressure>" << std::endl;
  myFile << std::endl << "\t<RecombinationSize>" << std::endl << "\t   " << ea->get_recombination_size() << std::endl << "\t</RecombinationSize>" << std::endl;
  myFile << std::endl << "\t<MutationRate>" << std::endl << "\t   " << ea->get_mutation_rate() << std::endl << "\t</MutationRate>" << std::endl;
  myFile << std::endl << "\t<MutationRateForES>" << std::endl << "\t   " << ea->get_mutation_rate_for_ES() << std::endl << "\t</MutationRateForES>" << std::endl;
  myFile << std::endl << "\t<MutationRange>" << std::endl << "\t   " << ea->get_mutation_range() << std::endl << "\t</MutationRange>" << std::endl;
  myFile << std::endl << "\t<MutationRangeForES>" << std::endl << "\t   " << ea->get_mutation_range_for_ES() << std::endl << "\t</MutationRangeForES>" << std::endl;
  myFile << std::endl << "\t<EvaluationSampleSize>" << std::endl << "\t   " << ea->get_evaluation_sample_size() << std::endl << "\t</EvaluationSampleSize>" << std::endl;
  if(gen0_preeval)
  {
    myFile << std::endl << "\t<Gen0_Pre-Evaluation>" << std::endl << "\t   " << "True" << std::endl << "\t</Gen0_Pre-Evaluation>" << std::endl;
  }
  else
  {
    myFile << std::endl << "\t<Gen0_Pre-Evaluation>" << std::endl << "\t   " << "False" << std::endl << "\t</Gen0_Pre-Evaluation>" << std::endl;
  }
  if(gen0_aug_pop)
  {
    myFile << std::endl << "\t<Gen0_AugmentedPopulation>" << std::endl << "\t   " << "True" << std::endl << "\t</Gen0_AugmentedPopulation>" << std::endl;
  }
  else
  {
    myFile << std::endl << "\t<Gen0_AugmentedPopulation>" << std::endl << "\t   " << "False" << std::endl << "\t</Gen0_AugmentedPopulation>" << std::endl;
  }
  myFile << std::endl << "\t<Gen0_MinimumEvaluationValue>" << std::endl << "\t   " << ea->get_gen_0_min_evaluation_value() << std::endl << "\t</Gen0_MinimumEvaluationValue>" << std::endl;
  myFile << std::endl << "\t<Gen0_PopulationSize>" << std::endl << "\t   " << ea->get_gen_0_population_size() << std::endl << "\t</Gen0_PopulationSize>" << std::endl;
  myFile << "</Evolution>" << std::endl;

  myFile << std::endl << "<Robot>" << std::endl;
  myFile << "\t<RobotEnvironment>" << std::endl << "\t   " << robot->get_robot_environment() << std::endl << "\t</RobotEnvironment>" << std::endl;
  myFile << std::endl << "\t<RobotType>" << std::endl << "\t   " << robot->get_robot_type() << std::endl << "\t</RobotType>" << std::endl;
  myFile << std::endl << "\t<NumberOfModules>" << std::endl << "\t   " << robot->get_number_of_modules() << std::endl << "\t</NumberOfModules>" << std::endl;
  myFile << "</Robot>" << std::endl;

  if(robot->get_robot_environment() == "SimulationOpenRave")
  {
    if(simuOR)
    {
      myFile << std::endl << "<SimulationEnvironment>" << std::endl;
      myFile << "\t<SceneFileName>" << std::endl << "\t   " << simuOR->get_scene_file_name() << std::endl << "\t</SceneFileName>" << std::endl;
      myFile << std::endl << "\t<SimResolution>" << std::endl << "\t   " << simuOR->get_simu_resolution_microseconds() << std::endl << "\t</SimResolution>" << std::endl;
      myFile << "</SimulationEnvironment>" << std::endl;
    }
    else
    {
      std::cerr << "Morphomotion Error: FileHandler class." << std::endl
                << "FileHandler(std::string, bool, bool, Flood::EvolutionaryAlgorithm*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*)" << std::endl
                << "robot_pointer = NULL " << std::endl;
      exit(1);
    }
  }

  myFile << std::endl << "<Controller>" << std::endl;
  myFile << "\t<ControllerType>" << std::endl << "\t   " << controller->get_controller_type() << std::endl << "\t</ControllerType>" << std::endl;
  myFile << std::endl << "\t<EvaluationPeriod>" << std::endl << "\t   " << controller->get_evaluation_period() << std::endl << "\t</EvaluationPeriod>" << std::endl;
  myFile << std::endl << "\t<ServoMax>" << std::endl << "\t   " << controller->get_servo_max() << std::endl << "\t</ServoMax>" << std::endl;
  myFile << std::endl << "\t<ServoMin>" << std::endl << "\t   " << controller->get_servo_min() << std::endl << "\t</ServoMin>" << std::endl;
  if(controller->get_controller_type() != "Sinusoidal_Controller" || controller->get_controller_type() != "Sine_Controller")
  {
    myFile << std::endl << "\t<StartAngleType>" << std::endl << "\t   " << controller->get_start_angle_type() << std::endl << "\t</StartAngleType>" << std::endl;
    myFile << std::endl << "\t<ServoDeltaThreshold>" << std::endl << "\t   " << controller->get_servo_delta_threshold() << std::endl << "\t</ServoDeltaThreshold>" << std::endl;
  }
  if(controller->get_controller_type() == "Neural_Controller" || controller->get_controller_type() == "Naive_Controller")
  {
    myFile << std::endl << "\t<ServoDerivativeThreshold>" << std::endl << "\t   " << controller->get_servo_derivative_threshold() << std::endl << "\t</ServoDerivativeThreshold>" << std::endl;
  }
  if(controller->get_controller_type() == "Neural_Controller" || controller->get_controller_type() == "Naive_Controller" || controller->get_controller_type() == "Semi_Hybrid_Controller")
  {
    myFile << std::endl << "\t<ServoDerivativeEpsilon>" << std::endl << "\t   " << controller->get_servo_derivative_epsilon() << std::endl << "\t</ServoDerivativeEpsilon>" << std::endl;
  }
  myFile << "</Controller>" << std::endl;

  if(mlp->get_inputs_number() > 0)
  {
    myFile << std::endl << "<NeuralNetwork>" << std::endl;
    myFile << "\t<NumberOfNNInputs>" << std::endl << "\t   " << mlp->get_inputs_number() << std::endl << "\t</NumberOfNNInputs>" << std::endl;
    if(mlp->get_hidden_layers_number() > 0)
    {
      myFile << std::endl << "\t<HiddenLayers>"; //<< "\t   " << number_of_inputs_to_NN << std::endl << "\t</NumberOfNNInputs>" << std::endl;
      for(int i=0; i<mlp->get_hidden_layers_number(); i++)
      {
        myFile << std::endl << "\t   <Layer>" << std::endl << "\t      " << mlp->get_hidden_layer_size(i) << std::endl << "\t   </Layer>" << std::endl;
      }
      myFile << "\t</HiddenLayers>" << std::endl;
    }
    myFile << std::endl << "\t<NumberOfNNOutputs>" << std::endl << "\t   " << mlp->get_outputs_number() << std::endl << "\t</NumberOfNNOutputs>" << std::endl;
    myFile << "</NeuralNetwork>" << std::endl;
  }

  if(mlp->get_independent_parameters_number() > 0)
  {
    myFile << std::endl << "<IndependentParameters>";
    for(int i=0; i<mlp->get_independent_parameters_number(); i++)
    {
      myFile << std::endl << "\t<Parameter>";
      myFile << std::endl << "\t   <Name>" << std::endl << "\t      " << mlp->get_independent_parameter_name(i) << std::endl << "\t   </Name>" << std::endl;
      myFile << std::endl << "\t   <Minimum>" << std::endl << "\t      " << mlp->get_independent_parameter_minimum(i) << std::endl << "\t   </Minimum>" << std::endl;
      myFile << std::endl << "\t   <Maximum>" << std::endl << "\t      " << mlp->get_independent_parameter_maximum(i) << std::endl << "\t   </Maximum>" << std::endl;
      myFile << "\t</Parameter>" << std::endl;
    }

    myFile << "</IndependentParameters>" << std::endl;
  }

  myFile << std::endl << "<Gene>" << std::endl;
  myFile << std::endl << "</Gene>" << std::endl;
  myFile << std::endl << "</Morphomotion>";

  myFile.close();
}


void FileHandler::save_gene(int generation, Flood::Vector<double> elite_gene)
{
  myFile.open(myFile_name.c_str(), fstream::in | fstream::out);

  if(!myFile.is_open())
  {
    std::cerr << std::endl
              << "Morphomotion Error: FileHandler class." << std::endl
              << "void save_gene(int, vector<double>) method." << std::endl
              << "Cannot open Gene file."  << std::endl;
    exit(1);
  }
  else
  {
    std::cout << std::endl
              << "Saving elite members to gene file..." << std::endl;
  }

  std::string word;
  do
  {
    myFile >> word;
  }while(word != "</Gene>");
  myFile.seekp (-25, ios::end);

  if(generation != 1)
  {
    myFile << std::endl;
  }
  myFile << "Generation_" << generation << ":" << std::endl;
  myFile << elite_gene << std::endl;

  myFile << "</Gene>" << std::endl;
  myFile << std::endl << "</Morphomotion>" << std::endl;

  myFile.close();
}


// CONSTRUCTOR FOR EXTRACTING PARAMETERS FROM PARAMETERS FILE
FileHandler::FileHandler(char* filename, Robot *robot, SimulationOpenRave *simuEnv, Controller *controller, Flood::MultilayerPerceptron *mlp)
{
  std::fstream file;
  file.open(filename, std::ios::in);
  if(!file.is_open())
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*)" << std::endl
              << "Cannot open Parameter file: "<< filename  << std::endl;

    exit(1);
  }

  std::string line;
  std::string word;

  getline(file, line);

  if(line != "<Morphomotion: Flood + OpenRave + Y1>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*)" << std::endl
              << "Unknown file declaration: " << line << std::endl;

    exit(1);
  }

  // File type
  file >> word;

  if(word != "<FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*)" << std::endl
              << "Unknown file type begin tag: " << word << std::endl;

    exit(1);
  }

  file >> word;

  if(word != "Evolution_Parameters")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*)" << std::endl
              << "Unknown file type: " << word << std::endl;

    exit(1);
  }

  file >> word;

  if(word != "</FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*)" << std::endl
              << "Unknown file type end tag: " << word << std::endl;

    exit(1);
  }

  do
  {
    file >> word;

    if(word == "<Robot>")
    {
      load_Robot_parameters(file, robot);
    }

    if(word == "<SimulationEnvironment>")
    {
      load_SimEnv_parameters(file, simuEnv);
    }

    if(word == "<Controller>")
    {
      load_Controller_parameters(file, controller);
    }

    else if(word == "<NeuralNetwork>")
    {
      load_NN_parameters(file, mlp);
    }

    else if(word == "<IndependentParameters>")
    {
      load_independent_parameters(file, mlp);
    }
  }while(word != "</Morphomotion>");
  file.close();
}

// CONSTRUCTOR FOR EXTRACTING PARAMETERS FROM GENE FILE
FileHandler::FileHandler(char* gene_filename, Robot *robot, SimulationOpenRave *simuEnv, Controller *controller, Flood::MultilayerPerceptron *mlp, Flood::Matrix<double>* population, std::vector<std::string>* generation_index)
{
  std::fstream gene_file;
  gene_file.open(gene_filename, std::ios::in);
  if(!gene_file.is_open())
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*)" << std::endl
              << "Cannot open Parameter file: "<< gene_filename  << std::endl;
    exit(1);
  }

  std::string line;
  std::string word;

  getline(gene_file, line);

  if(line != "<Morphomotion: Flood + OpenRave + Y1>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*)" << std::endl
              << "Unknown file declaration: " << line << std::endl;

    exit(1);
  }

  // File type
  gene_file >> word;

  if(word != "<FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*)" << std::endl
              << "Unknown file type begin tag: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "GeneFile")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*)" << std::endl
              << "Unknown file type: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "</FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*)" << std::endl
              << "Unknown file type end tag: " << word << std::endl;

    exit(1);
  }

  do
  {
    gene_file >> word;

    if(word == "<Robot>")
    {
      load_Robot_parameters(gene_file, robot);
    }

    if(word == "<SimulationEnvironment>")
    {
      if(simuEnv)
      {
        load_SimEnv_parameters(gene_file, simuEnv);
      }
    }

    if(word == "<Controller>")
    {
      load_Controller_parameters(gene_file, controller);
    }

    else if(word == "<NeuralNetwork>")
    {
      load_NN_parameters(gene_file, mlp);
    }

    else if(word == "<IndependentParameters>")
    {
      load_independent_parameters(gene_file, mlp);
    }

    else if(word == "<Gene>")
    {
      load_genes(gene_file, mlp, population, generation_index);
    }
  }while(word != "</Morphomotion>");
  gene_file.close();
}


//-- CONSTRUCTOR FOR EXTRACTING PARAMETERS FROM GENE FILE AND FITNESS FILE
FileHandler::FileHandler(char* gene_filename, char* fitness_filename, Robot *robot, SimulationOpenRave *simuEnv, Controller *controller, Flood::MultilayerPerceptron *mlp, Flood::Matrix<double>* population, std::vector<std::string>* generation_index, std::vector<double>* elite_fitness)
{
  std::fstream gene_file;
  std::fstream fitness_file;

  gene_file.open(gene_filename, std::ios::in);
  if(!gene_file.is_open())
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Cannot open Parameter file: "<< gene_filename  << std::endl;
    exit(1);
  }

  fitness_file.open(fitness_filename, std::ios::in);
  if(!fitness_file.is_open())
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Cannot open Fitness file: "<< fitness_filename  << std::endl;
    exit(1);
  }

  std::string line;
  std::string word;

  getline(gene_file, line);

  if(line != "<Morphomotion: Flood + OpenRave + Y1>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file declaration: " << line << std::endl;

    exit(1);
  }

  //-- File type
  gene_file >> word;

  if(word != "<FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file type begin tag: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "GeneFile")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file type: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "</FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Robot*, SimulationOpenRave*, Controller*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file type end tag: " << word << std::endl;

    exit(1);
  }

  do
  {
    gene_file >> word;

    if(word == "<Robot>")
    {
      load_Robot_parameters(gene_file, robot);
    }

    if(word == "<SimulationEnvironment>")
    {
      if(simuEnv)
      {
        load_SimEnv_parameters(gene_file, simuEnv);
      }
    }

    if(word == "<Controller>")
    {
      load_Controller_parameters(gene_file, controller);
    }

    else if(word == "<NeuralNetwork>")
    {
      load_NN_parameters(gene_file, mlp);
    }

    else if(word == "<IndependentParameters>")
    {
      load_independent_parameters(gene_file, mlp);
    }

    else if(word == "<Gene>")
    {
      load_genes(gene_file, mlp, population, generation_index);
    }
  }while(word != "</Morphomotion>");
  gene_file.close();

  load_elite_fitness(fitness_file, elite_fitness);
}


//-- CONSTRUCTOR FOR EXTRACTING MLP PARAMETERS FROM GENE FILE
FileHandler::FileHandler(char* gene_filename, Flood::MultilayerPerceptron *mlp, Flood::Matrix<double>* population, std::vector<std::string>* generation_index)
{
  std::fstream gene_file;
  gene_file.open(gene_filename, std::ios::in);
  if(!gene_file.is_open())
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*)" << std::endl
              << "Cannot open Parameter file: "<< gene_filename  << std::endl;
    exit(1);
  }

  std::string line;
  std::string word;

  getline(gene_file, line);

  if(line != "<Morphomotion: Flood + OpenRave + Y1>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*)" << std::endl
              << "Unknown file declaration: " << line << std::endl;

    exit(1);
  }

  //-- File type
  gene_file >> word;

  if(word != "<FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*)" << std::endl
              << "Unknown file type begin tag: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "GeneFile")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*)" << std::endl
              << "Unknown file type: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "</FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, std::vector<std::string>*)" << std::endl
              << "Unknown file type end tag: " << word << std::endl;

    exit(1);
  }

  do
  {
    gene_file >> word;

    if(word == "<NeuralNetwork>")
    {
      load_NN_parameters(gene_file, mlp);
    }

    else if(word == "<IndependentParameters>")
    {
      load_independent_parameters(gene_file, mlp);
    } // TODO: This should be removed after confirming that this is not needed.

    else if(word == "<Gene>")
    {
      load_genes(gene_file, mlp, population, generation_index);
    }
  }while(word != "</Morphomotion>");
  gene_file.close();
}


//-- CONSTRUCTOR FOR EXTRACTING MLP PARAMETERS FROM GENE FILE AND FITNESS FILE
FileHandler::FileHandler(char* gene_filename, char* fitness_filename, Flood::MultilayerPerceptron *mlp, Flood::Matrix<double>* population, std::vector<std::string>* generation_index, std::vector<double>* elite_fitness)
{
  std::fstream gene_file;
  std::fstream fitness_file;

  gene_file.open(gene_filename, std::ios::in);
  if(!gene_file.is_open())
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Cannot open Parameter file: "<< gene_filename  << std::endl;
    exit(1);
  }

  fitness_file.open(fitness_filename, std::ios::in);
  if(!fitness_file.is_open())
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Cannot open Fitness file: "<< fitness_filename  << std::endl;
    exit(1);
  }

  std::string line;
  std::string word;

  getline(gene_file, line);

  if(line != "<Morphomotion: Flood + OpenRave + Y1>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file declaration: " << line << std::endl;

    exit(1);
  }

  //-- File type
  gene_file >> word;

  if(word != "<FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file type begin tag: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "GeneFile")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file type: " << word << std::endl;

    exit(1);
  }

  gene_file >> word;

  if(word != "</FileType>")
  {
    std::cerr << "Morphomotion Error: FileHandler class." << std::endl
              << "FileHandler(char*, char*, Flood::MultilayerPerceptron*, Flood::Matrix<double>*, Flood::Vector<std::string>*, Flood::Vector<double>*)" << std::endl
              << "Unknown file type end tag: " << word << std::endl;

    exit(1);
  }

  do
  {
    gene_file >> word;

    if(word == "<NeuralNetwork>")
    {
      load_NN_parameters(gene_file, mlp);
    }

    else if(word == "<IndependentParameters>")
    {
      load_independent_parameters(gene_file, mlp);
    }

    else if(word == "<Gene>")
    {
      load_genes(gene_file, mlp, population, generation_index);
    }
  }while(word != "</Morphomotion>");
  gene_file.close();

  load_elite_fitness(fitness_file, elite_fitness);
}


//-- DESTRUCTOR
FileHandler::~FileHandler(void)
{
}


//-- METHODS

void FileHandler::load_Robot_parameters(std::fstream& file, Robot *robot)
{
  std::string word;

  do
  {
    file >> word;

    //-- TODO: This was previouslt uncommented. Need to be looked at
    /*if(word == "<RobotEnvironment>")
    {
      std::string new_robot_environment;
      file >> new_robot_environment;
      robot->set_robot_environment(new_robot_environment);

      file >> word;

      if(word != "</RobotEnvironment>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Robot_parameters(std::fstream&, Robot*) method." << std::endl
                  << "Unknown Robot Environment end tag: " << word << std::endl;

        exit(1);
      }
    }*/

    if(word == "<RobotType>")
    {
      std::string new_robot_type;
      file >> new_robot_type;
      robot->set_robot_type(new_robot_type);

      file >> word;

      if(word != "</RobotType>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Robot_parameters(std::fstream&, Robot*) method." << std::endl
                  << "void load_SimEnv_parameters(std::fstream&, SimEnv*) method." << std::endl
                  << "Unknown Robot Type end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<NumberOfModules>")
    {
      int new_number_of_modules;
      file >> new_number_of_modules;
      robot->set_number_of_modules(new_number_of_modules);

      file >> word;

      if(word != "</NumberOfModules>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Robot_parameters(std::fstream&, Robot*) method." << std::endl
                  << "Unknown Number Of Modules end tag: " << word << std::endl;

        exit(1);
      }
    }

  }while(word != "</Robot>");
}


void FileHandler::load_SimEnv_parameters(std::fstream& file, SimulationOpenRave *simuEnv)
{
  std::string word;

  do
  {
    file >> word;

    if(word == "<SceneFileName>")
    {
      std::string new_scene_file_name;
      file >> new_scene_file_name;
      simuEnv->set_scene_file_name(new_scene_file_name);

      file >> word;

      if(word != "</SceneFileName>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_SimEnv_parameters(std::fstream&, SimulationOpenRave*) method." << std::endl
                  << "Unknown Scene File name end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<SimResolution>")
    {
      double new_sim_resolution;
      file >> new_sim_resolution;
      simuEnv->set_simu_resolution_microseconds(new_sim_resolution);

      file >> word;

      if(word != "</SimResolution>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_SimEnv_parameters(std::fstream&, SimulationOpenRave*) method." << std::endl
                  << "Unknown Simulation Resolution end tag: " << word << std::endl;

        exit(1);
      }
    }
   }while(word != "</SimulationEnvironment>");
}


void FileHandler::load_Controller_parameters(std::fstream& file, Controller *controller)
{
  std::string word;

  do
  {
    file >> word;

    if(word == "<ControllerType>")
    {
      std::string new_controller_type;
      file >> new_controller_type;
      controller->set_controller_type(new_controller_type);

      file >> word;

      if(word != "</ControllerType>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Controller Type end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<EvaluationPeriod>")
    {
      unsigned int new_evaluation_period;
      file >> new_evaluation_period;
      controller->set_evaluation_period(new_evaluation_period);

      file >> word;

      if(word != "</EvaluationPeriod>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Evaluation Period end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<ServoMax>")
    {
      double new_servo_max;
      file >> new_servo_max;
      controller->set_servo_max(new_servo_max);

      file >> word;

      if(word != "</ServoMax>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Servo Max end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<ServoMin>")
    {
      double new_servo_min;
      file >> new_servo_min;
      controller->set_servo_min(new_servo_min);

      file >> word;

      if(word != "</ServoMin>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Servo Min end tag: " << word << std::endl;

        exit(1);
      }
    }


    else if(word == "<StartAngleType>")
    {
      std::string new_start_angle_type;
      file >> new_start_angle_type;
      if(new_start_angle_type == "Zero")
      {
        controller->set_start_angle_type("Zero");
      }
      else if(new_start_angle_type == "Random")
      {
        controller->set_start_angle_type("Random");
      }
      else if(new_start_angle_type == "RandomEqual")
      {
        controller->set_start_angle_type("RandomEqual");
      }
      else if(new_start_angle_type == "Predefined")
      {
        controller->set_start_angle_type("Predefined");
      }
      else if(new_start_angle_type == "RunTime")
      {
        controller->set_start_angle_type("RunTime");
      }
      else
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Start Angle type: " << word << " in <StartAngleType>" << std::endl;

        exit(1);
      }

      file >> word;

      if(word != "</StartAngleType>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Start Angle end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<ServoDeltaThreshold>")
    {
      double new_servo_delta_threshold;
      file >> new_servo_delta_threshold;
      controller->set_servo_delta_threshold(new_servo_delta_threshold);

      file >> word;

      if(word != "</ServoDeltaThreshold>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Servo Delta Threshold end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<ServoDerivativeThreshold>")
    {
      double new_servo_derivative_threshold;
      file >> new_servo_derivative_threshold;
      controller->set_servo_derivative_threshold(new_servo_derivative_threshold);

      file >> word;

      if(word != "</ServoDerivativeThreshold>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Servo Derivative Threshold end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<ServoDerivativeEpsilon>")
    {
      int new_servo_derivative_epsilon;
      file >> new_servo_derivative_epsilon;
      controller->set_servo_derivative_epsilon(new_servo_derivative_epsilon);

      file >> word;

      if(word != "</ServoDerivativeEpsilon>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_Controller_parameters(std::fstream&, Controller*) method." << std::endl
                  << "Unknown Servo Derivative Epsilon end tag: " << word << std::endl;

        exit(1);
      }
    }
  }while(word != "</Controller>");
}


void FileHandler::load_NN_parameters(std::fstream& file, Flood::MultilayerPerceptron *mlp)
{
  std::string word;
  int nnInput = 0;
  int nnOutput = 0;
  std::vector<int> hiddenLayers;

  do
  {
    file >> word;

    if(word == "<NumberOfNNInputs>")
    {
      file >> word;
      nnInput = atoi(word.c_str());

      file >> word;

      if(word != "</NumberOfNNInputs>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_NN_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
                  << "Unknown Number of NNInputs end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<NumberOfNNOutputs>")
    {
      file >> word;
      nnOutput = atoi(word.c_str());

      file >> word;

      if(word != "</NumberOfNNOutputs>")
      {
        std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                  << "void load_NN_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
                  << "Unknown Number of NNOutputs end tag: " << word << std::endl;

        exit(1);
      }
    }

    else if(word == "<HiddenLayers>")
    {
      do
      {
        file >> word;

        if(word == "<Layer>")
        {
          file >> word;
          hiddenLayers.push_back(atoi(word.c_str()));

          file >> word;

          if(word != "</Layer>")
          {
            std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                      << "void load_NN_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
                      << "Unknown NN hidden layers end tag: " << word << std::endl;

            exit(1);
          }
        }
      }while(word != "</HiddenLayers>");
    }
  }while(word != "</NeuralNetwork>");

  Flood::Vector<int> nnHiddenNeurons(hiddenLayers.size());
  for(unsigned int i=0; i<hiddenLayers.size(); i++)
  {
    nnHiddenNeurons[i] = hiddenLayers[i];
  }

  mlp->set_network_architecture (nnInput, nnHiddenNeurons, nnOutput);
}


void FileHandler::load_independent_parameters(std::fstream& file, Flood::MultilayerPerceptron *mlp)
{
  std::string word;
  unsigned int independentParametersNumber = 0;
  std::vector<std::string> independentParametersName;
  std::vector<double> independentParametersMinimum;
  std::vector<double> independentParametersMaximum;

  do
  {
    file >> word;

    if(word == "<Parameter>")
    {
      unsigned int totalParameters=1;
      independentParametersNumber++;

      do
      {
        file >> word;

        if(word == "<TotalParameters>")
        {
          file >> word;
          totalParameters = atoi(word.c_str());

          if(totalParameters > 1)
          {
            //-- Undoing incrementing independentParametersNumber a few lines above.
            independentParametersNumber--;
            independentParametersNumber = independentParametersNumber + totalParameters;
          }

          file >> word;

          if(word != "</TotalParameters>")
          {
            std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                      << "void load_independent_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
                      << "Unknown Total Parameters end tag: " << word << std::endl;

            exit(1);
          }
        }

        else if(word == "<Name>")
        {
          std::string new_independent_parameter_name;
          file >> new_independent_parameter_name;

          if(totalParameters > 1)
          {
            for(unsigned int parameter=0; parameter<totalParameters; parameter++)
            {
              std::string par_no;
              ostringstream intToString;
              intToString << parameter+1;
              par_no = intToString.str();

              std::string parameter_name = new_independent_parameter_name + "-module_" + par_no;
              independentParametersName.push_back(parameter_name);
            }
          }
          else
          {
            independentParametersName.push_back(new_independent_parameter_name);
          }

          file >> word;

          if(word != "</Name>")
          {
            std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                      << "void load_independent_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
                      << "Unknown Independent Parameters Name end tag: " << word << std::endl;

            exit(1);
          }
        }

        else if(word == "<Minimum>")
        {
          file >> word;
          for(unsigned int parameter=0; parameter<totalParameters; parameter++)
          {
            independentParametersMinimum.push_back(atoi(word.c_str()));
          }

          file >> word;

          if(word != "</Minimum>")
          {
            std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                      << "void load_independent_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
                      << "Unknown Independent Parameters Minimum end tag: " << word << std::endl;

            exit(1);
          }
        }

        else if(word == "<Maximum>")
        {
          file >> word;
          for(unsigned int parameter=0; parameter<totalParameters; parameter++)
          {
            independentParametersMaximum.push_back(atoi(word.c_str()));
          }

          file >> word;

          if(word != "</Maximum>")
          {
            std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                      << "void load_independent_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
                      << "Unknown Independent Parameters Maximum end tag: " << word << std::endl;

            exit(1);
          }
        }
      }while(word != "</Parameter>");
    }
  }while(word != "</IndependentParameters>");

  if(independentParametersNumber != independentParametersName.size() || independentParametersNumber != independentParametersMinimum.size() || independentParametersNumber != independentParametersMaximum.size())
  {
    std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
              << "void load_independent_parameters(std::fstream&, Flood::MultilayerPerceptron*) method." << std::endl
              << "Discrepency in Independent Parameters size." << std::endl;
    exit(1);
  }

  Flood::Vector<string> Independent_Parameters_Name(independentParametersNumber);
  Flood::Vector<double> Independent_Parameters_Minimum(independentParametersNumber);
  Flood::Vector<double> Independent_Parameters_Maximum(independentParametersNumber);

  for(unsigned int i=0; i<independentParametersNumber; i++)
  {
    Independent_Parameters_Name[i] = independentParametersName[i];
    Independent_Parameters_Minimum[i] = independentParametersMinimum[i];
    Independent_Parameters_Maximum[i] = independentParametersMaximum[i];
  }

  mlp->set_independent_parameters_number(independentParametersNumber);

  mlp->set_independent_parameters_name(Independent_Parameters_Name);
  mlp->set_independent_parameters_minimum(Independent_Parameters_Minimum);
  mlp->set_independent_parameters_maximum(Independent_Parameters_Maximum);
}


void FileHandler::load_genes(std::fstream& gene_file, Flood::MultilayerPerceptron *mlp, Flood::Matrix<double>* population, std::vector<std::string>* generation_index)
{
   std::string word;
   int parametersNumber = mlp->get_parameters_number();
   Flood::Vector<double> individual;
   individual.set(parametersNumber);
   population->set(1, parametersNumber);


   gene_file >> word;
   if(word != "Generation_0:" && word != "Generation_1:")
   {
      std::cerr << "Morphomotion Error: FileHandler Class." << std::endl
                << "void load_genes(std::fstream&, Flood::MultilayerPerceptron*, Flood::Matrix<double>*) method." << std::endl
                << "Wrong Gene Start tag: "<< word  << std::endl;
      exit(1);
   }

   do
   {
      //-- Adding generation_index.
      generation_index->push_back(word);

      for(int j = 0; j < parametersNumber; j++)
      {
         gene_file >> individual[j];
      }
      population->add_row(individual);
      gene_file >> word;
   }while(word != "</Gene>");
}


void FileHandler::load_elite_fitness(std::fstream& fitness_file, std::vector<double>* elite_fitness)
{
  double fitness;

  do
  {
    //-- index number (Discarded)
    fitness_file >> fitness;

    //-- Best Fitness
    fitness_file >> fitness;
    elite_fitness->push_back(fitness);

    //-- Average Fitness (Discarded)
    fitness_file >> fitness;
    //-- Worst Fitness (Discarded)
    fitness_file >> fitness;
  }while(!fitness_file.eof());
}


/********************************************************* From http://www.dreamincode.net/ *************************************************************/
char* substr(char* str, int start, int end)
{
  char* a = new char[1+(end-start)]; // we need a new char array for the return
  for(int i=start; i<end; i++) // loop through the string
  {
    a[i-start] = str[i]; // set the characters in the new char array to those from the old one compensating for the substring
  }
  a[end-start] = '\0'; // add the null character, so we can output
  return a; // return
}

double atod(char* a)
{
  double retVal = atoi(a); // start off getting the number, assuming it is a valid string to use atoi on.
  int start = 0;
  int end = 0;

  for(int i=0; a[i] != '\0'; i++) // loop through the string to find the positions of the decimal portion, if there is one
  {
    if(a[i] == '.' && start == 0)
    {
      start = i+1; // set the start position to 1 more than the current (avoids a char as the first character - we want a digit)
    }
    else if(start != 0 &&  (a[i] < '0' || a[i] > '9')) // make sure that start is set and that we aren't looking at digits
    {
      end = i; // if so, set the end location for the substring
      break; // we don't need to continue anymore - break out of the loop
    }
  }

  if(end > start) // avoids substring problems.
  {
    char* decimal = substr(a, start, end); // get the string that is after the decimal point
    int dec = atoi(decimal); // make it an integer
    int power = end-start; // find the power of 10 we need to divide by
    retVal += ((double)dec)/(pow(10.0, (double)power)); // divide and add to the return value (thus making it a true double)
  }

  return retVal; // return - simple enough
}
/********************************************************* From http://www.dreamincode.net/ *************************************************************/
