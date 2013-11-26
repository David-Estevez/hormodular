/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   N E U R A L   M O D E L   E V A L U A T O R                                                                */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/

// System includes
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Robot.h"
#include "SimulationOpenRave.h"
#include "Y1ModularRobot.h"
#include "Controller.h"
#include "FileHandler.h"
#include "OscillationAnalyzer_OutputSignal.h"

void calculate_neural_output(Flood::MultilayerPerceptron *mlp, GraphFile *neural_input_output)
{
  double servo_max=90.0;
  double servo_min=-90.0;

  std::stringstream ss;
  //GraphFile *neural_input_output;

  Flood::Vector<double> nnOutput(mlp->get_outputs_number());
  Flood::Vector<double> nnInput(mlp->get_inputs_number());

  //remove("../Evaluation_Files/neural_input_output.dat");
  //neural_input_output = new GraphFile("../Evaluation_Files/neural_input_output.dat");

  std::cout << std::endl << "   Input   " << "Output   " << std::endl;
  for(double input=servo_min; input<=servo_max; input=input+0.5)
  {
    //-- Following input to the NN is the proprioceptive feedback from the module's actuator, which is scaled down to a value between +/-1.
    nnInput[0] = input/servo_max;

    //-- Calculate the NN output by passing the inputs
    nnOutput = mlp->calculate_output(nnInput);

    //-- Scale up the output to a value between +/- 90 degrees and save it in "Previous Actuation Value" vector 'output[]'
    std::cout << "   " << input << "     " << nnOutput[0]*servo_max << std::endl;

    ss << 2 << " ";
    ss << input << " " << nnOutput[0]*servo_max << " ";
    neural_input_output->write(ss);
  }
}

int main(int argc, char* argv[])
{
  bool evaluate_best_individual = false;

  char* gene_file;
  char* fitness_file;

  GraphFile *neural_input_output;
  //remove("../Evaluation_Files/neural_input_output.dat");
  neural_input_output = new GraphFile("../Evaluation_Files/neural_input_output.dat");

  // Multilayer perceptron object
  Flood::MultilayerPerceptron mlp(0,0,0);
  mlp.set_independent_parameters_number(0);

  // Elite population gene
  Flood::Matrix<double> population;
  std::vector<std::string> generation_index;

  std::vector<double> elite_fitness;

  if(argc == 1)
  {
    std::cerr << "Morphomotion Error: EvaluateNeuralModel." << std::endl
              << "main(int, char*)" << std::endl
              << "No parameter files: "<< std::endl;

    exit(1);
  }
  else if(argc == 2)
  {
    gene_file = argv[1];
    std::cout << "Inside else if(argc == 2)" << std::endl;
    FileHandler geneFileHandler(gene_file, &mlp, &population, &generation_index);
    std::cout << "Exiting else if(argc == 2)" << std::endl;
  }
  else if(argc == 3)
  {
    evaluate_best_individual = true;

    gene_file = argv[1];

    if(argv[2][0] == '-' && argv[2][1] == 'b')
    {
      std::string fitness_file_string;
      fitness_file_string = argv[1];
      fitness_file_string.erase(fitness_file_string.end()-62, fitness_file_string.end()-32);
      fitness_file_string.erase(fitness_file_string.end()-20, fitness_file_string.end());

      fitness_file_string.insert(fitness_file_string.end()-12, 'F');
      fitness_file_string.insert(fitness_file_string.end()-12, 'i');
      fitness_file_string.insert(fitness_file_string.end()-12, 't');
      fitness_file_string.insert(fitness_file_string.end()-12, 'n');
      fitness_file_string.insert(fitness_file_string.end()-12, 'e');
      fitness_file_string.insert(fitness_file_string.end()-12, 's');
      fitness_file_string.insert(fitness_file_string.end()-12, 's');
      fitness_file_string.insert(fitness_file_string.end()-12, 'G');
      fitness_file_string.insert(fitness_file_string.end()-12, 'r');
      fitness_file_string.insert(fitness_file_string.end()-12, 'a');
      fitness_file_string.insert(fitness_file_string.end()-12, 'p');
      fitness_file_string.insert(fitness_file_string.end()-12, 'h');
      fitness_file_string.insert(fitness_file_string.end()-12, '_');
      fitness_file_string.insert(fitness_file_string.end()-12, 'F');
      fitness_file_string.insert(fitness_file_string.end()-12, 'i');
      fitness_file_string.insert(fitness_file_string.end()-12, 'l');
      fitness_file_string.insert(fitness_file_string.end()-12, 'e');
      fitness_file_string.insert(fitness_file_string.end()-12, 's');
      fitness_file_string.insert(fitness_file_string.end()-12, '/');

      fitness_file_string.insert(fitness_file_string.end(), 'F');
      fitness_file_string.insert(fitness_file_string.end(), 'i');
      fitness_file_string.insert(fitness_file_string.end(), 't');
      fitness_file_string.insert(fitness_file_string.end(), 'n');
      fitness_file_string.insert(fitness_file_string.end(), 'e');
      fitness_file_string.insert(fitness_file_string.end(), 's');
      fitness_file_string.insert(fitness_file_string.end(), 's');
      fitness_file_string.insert(fitness_file_string.end(), 'G');
      fitness_file_string.insert(fitness_file_string.end(), 'r');
      fitness_file_string.insert(fitness_file_string.end(), 'a');
      fitness_file_string.insert(fitness_file_string.end(), 'p');
      fitness_file_string.insert(fitness_file_string.end(), 'h');
      fitness_file_string.insert(fitness_file_string.end(), '.');
      fitness_file_string.insert(fitness_file_string.end(), 'd');
      fitness_file_string.insert(fitness_file_string.end(), 'a');
      fitness_file_string.insert(fitness_file_string.end(), 't');

      fitness_file = new char[fitness_file_string.size()+1];

      unsigned int i;
      for(i=0; i<fitness_file_string.size(); i++)
      {
          fitness_file[i] = fitness_file_string[i];
      }
      fitness_file[i] = '\0';
    }
    else
    {
      fitness_file = argv[1];
    }
    FileHandler gene_fitness_FileHandler(gene_file, fitness_file, &mlp, &population, &generation_index, &elite_fitness);
  }

  population.subtract_row(0);

  // Hidden Layer Activation Function
  Flood::Vector<std::string> hiddenLayerActivation(mlp.get_hidden_layers_number());
  hiddenLayerActivation[0] = "HyperbolicTangent";

  // Output Layer Activation Function
  mlp.set_output_layer_activation_function("HyperbolicTangent");

  Flood::Vector<double> individual(mlp.get_parameters_number());
  int population_size = population.get_rows_number();

  if(evaluate_best_individual)
  {
    unsigned int best_individual_fitness_index = 0;
    for(unsigned int i=1; i<elite_fitness.size();i++)
    {
      if(elite_fitness[i] >= elite_fitness[best_individual_fitness_index])
      {
        best_individual_fitness_index = i;
      }
    }

    best_individual_fitness_index++;
    bool best_fitness_gene_found = false;
    do
    {
      best_individual_fitness_index--;
      std::stringstream generation_no;
      generation_no << "Generation_" << best_individual_fitness_index+1 << ":";
      for(unsigned int i=0; i<=population_size-1; i++)
      {
        if(generation_no.str().compare(generation_index[i]) == 0)
        {
          individual = population.get_row(i);
          std::cout << std::endl << "Best_Fitness: Generation " << best_individual_fitness_index+1 << std::endl << individual << std::endl << std::endl;
          best_fitness_gene_found = true;
          break;
        }
      }
    }while(!best_fitness_gene_found);

    mlp.set_parameters(individual);
    calculate_neural_output(&mlp, neural_input_output);
  }
  else
  {
    for(int i=population_size-1; i>=0; i--)
    //for(unsigned int i=0; i<=population_size-1; i++)
    {
      std::cout << std::endl << individual << std::endl << std::endl;

      individual = population.get_row(i);
      mlp.set_parameters(individual);
      calculate_neural_output(&mlp, neural_input_output);
    }
  }
  return 0;
}
