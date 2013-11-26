/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   E V O L U T I O N A R Y   A L G O R I T H M   C L A S S                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <time.h>

// Flood includes

#include "EvolutionaryAlgorithm.h"


namespace Flood
{

// GENERAL CONSTRUCTOR

/// General constructor. It creates a evolutionary training algorithm object associated to an objective functional object.
/// It also initializes the class members to their default values:
/// Training operators:
/// <ul>
/// <li> Fitness assignment method: Linear ranking.
/// <li> Selection method: Stochastic universal sampling.
/// <li> Recombination method: Intermediate.
/// <li> Mutation method: Normal.
/// </ul>
/// Training parameters:
/// <ul>
/// <li> Population size: 10*parameters_number or 0.
/// <li> Perform elitism: false.
/// <li> Selective pressure: 1.5.
/// <li> Recombination size: 0.25.
/// <li> Mutation rate: = 1/parameters_number or 0.
/// <li> Mutation range: = 0.1
/// </ul>
/// Stopping criteria:
/// <ul>
/// <li> Evaluation goal: -1.0e99.
/// <li> Mean evaluation goal: -1.0e99.
/// <li> Standard deviation of evaluation goal: -1.0e99.
/// <li> Maximum training time: 1.0e6.
/// <li> Maximum number of generations: 100.
/// </ul>
/// Training history:
/// <ul>
/// <li> Population = false.
/// <li> Mean norm = false.
/// <li> Standard deviation norm = false.
/// <li> Best norm = false.
/// <li> Mean evaluation = false.
/// <li> Standard deviation evaluation = false.
/// <li> Best evaluation = false.
/// </ul>
/// User stuff:
/// <ul>
/// <li> Display: true.
/// <li> Display period: 1.
/// </ul>
///
/// @param new_objective_functional_pointer Pointer to an objective functional object.

EvolutionaryAlgorithm::EvolutionaryAlgorithm(ObjectiveFunctional* new_objective_functional_pointer)
: TrainingAlgorithm(new_objective_functional_pointer)
{
   set_default();
}


// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a evolutionary training algorithm object not associated to any objective functional object.
/// It also initializes the class members to their default values:
/// Training operators:
/// <ul>
/// <li> Fitness assignment method: Linear ranking.
/// <li> Selection method: Stochastic universal sampling.
/// <li> Recombination method: Intermediate.
/// <li> Mutation method: Normal.
/// </ul>
/// Training parameters:
/// <ul>
/// <li> Population size: 10*parameters_number or 0.
/// <li> Perform elitism: false.
/// <li> Selective pressure: 1.5.
/// <li> Recombination size: 0.25.
/// <li> Mutation rate: = 1/parameters_number or 0.
/// <li> Mutation range: = 0.1
/// </ul>
/// Stopping criteria:
/// <ul>
/// <li> Evaluation goal: -1.0e99.
/// <li> Mean evaluation goal: -1.0e99.
/// <li> Standard deviation of evaluation goal: -1.0e99.
/// <li> Maximum training time: 1.0e6.
/// <li> Maximum number of generations: 100.
/// </ul>
/// Training history:
/// <ul>
/// <li> Population = false.
/// <li> Mean norm = false.
/// <li> Standard deviation norm = false.
/// <li> Best norm = false.
/// <li> Mean evaluation = false.
/// <li> Standard deviation evaluation = false.
/// <li> Best evaluation = false.
/// </ul>
/// User stuff:
/// <ul>
/// <li> Display: true.
/// <li> Display period: 1.
/// </ul>

EvolutionaryAlgorithm::EvolutionaryAlgorithm(void) : TrainingAlgorithm()
{
   set_default();
}


// DESTRUCTOR

/// Destructor.

EvolutionaryAlgorithm::~EvolutionaryAlgorithm(void)
{
   //elite_population_file.close();
}


// METHODS

// FitnessAssignmentMethod get_fitness_assignment_method(void) method

/// This method returns the fitness assignment method used for training.

EvolutionaryAlgorithm::FitnessAssignmentMethod& EvolutionaryAlgorithm::get_fitness_assignment_method(void)
{
   return(fitness_assignment_method);
}


// std::string get_fitness_assignment_method_name(void) method

/// This method returns a string with the name of the method used for fitness assignment.

std::string EvolutionaryAlgorithm::get_fitness_assignment_method_name(void)
{
   switch(fitness_assignment_method)
   {
      case LinearRanking:
      {
         return("LinearRanking");
    }
      break;

      case MyLinearRanking:
      {
         return("MyLinearRanking");
    }
      break;

    default:
      {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "std::string get_fitness_assignment_method_name(void) method." << std::endl
                   << "Unknown fitness assignment method." << std::endl;

         exit(1);
    }
      break;
   }
}


// SelectionMethod get_selection_method(void) method

/// This method returns the selection method used for training.

EvolutionaryAlgorithm::SelectionMethod& EvolutionaryAlgorithm::get_selection_method(void)
{
   return(selection_method);
}


// std::string get_selection_method_name(void) method

/// This method returns a string with the name of the method used for selection.

std::string EvolutionaryAlgorithm::get_selection_method_name(void)
{
   switch(selection_method)
   {
      case RouletteWheel:
      {
         return("RouletteWheel");
    }
      break;

      case MyRouletteWheel:
      {
         return("MyRouletteWheel");
    }
      break;

      case StochasticUniversalSampling:
      {
         return("StochasticUniversalSampling");
    }
      break;

    default:
      {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "std::string get_selection_method_name(void) method." << std::endl
                   << "Unknown selection method." << std::endl;

         exit(1);
    }
      break;
   }
}


// RecombinationMethod get_recombination_method(void) method

/// This method returns the recombination method used for training.

EvolutionaryAlgorithm::RecombinationMethod& EvolutionaryAlgorithm::get_recombination_method(void)
{
   return(recombination_method);
}


// std::string get_recombination_method_name(void) method

/// This method returns a string with the name of the method used for recombination.

std::string EvolutionaryAlgorithm::get_recombination_method_name(void)
{
   switch(recombination_method)
   {
      case Line:
      {
         return("Line");
    }
      break;

      case Intermediate:
      {
         return("Intermediate");
    }
      break;

      case MyIntermediate:
      {
         return("MyIntermediate");
    }
      break;

      case MyIntermediateWithElitism:
      {
         return("MyIntermediateWithElitism");
    }
      break;

      case MyIntermediateWithElitismAndES:
      {
         return("MyIntermediateWithElitismAndES");
    }
      break;

    default:
      {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "std::string get_recombination_method_name(void) method." << std::endl
                   << "Unknown recombination method." << std::endl;

         exit(1);
    }
      break;
   }
}


// MutationMethod get_mutation_method(void) method

/// This method returns the mutation method used for training.

EvolutionaryAlgorithm::MutationMethod& EvolutionaryAlgorithm::get_mutation_method(void)
{
   return(mutation_method);
}


// std::string get_mutation_method_name(void) method

/// This method returns a string with the name of the method used for mutation.

std::string EvolutionaryAlgorithm::get_mutation_method_name(void)
{
   switch(mutation_method)
   {
      case Normal:
      {
         return("Normal");
    }
      break;

      case MyNormal:
      {
         return("MyNormal");
    }
      break;

      case MyNormalWithES:
      {
         return("MyNormalWithES");
    }
      break;

      case Uniform:
      {
         return("Uniform");
    }
      break;

    default:
      {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "std::string get_mutation_method_name(void) method." << std::endl
                   << "Unknown mutation method." << std::endl;

         exit(1);
    }
      break;
   }
}


// int get_population_size(void) method

/// This method returns the number of individuals in the population.

int EvolutionaryAlgorithm::get_population_size(void)
{
   return(population.get_rows_number());
}


// Matrix<double>& get_population(void) method

/// This method returns the population Matrix.

Matrix<double>& EvolutionaryAlgorithm::get_population(void)
{
   return(population);
}


// Vector<double>& get_evaluation(void) method

/// This method returns the actual evaluation value of all individuals in the population.

Vector<double>& EvolutionaryAlgorithm::get_evaluation(void)
{
   return(evaluation);
}


// Vector<double>& get_fitness(void) method

/// This method returns the actual fitness value of all individuals in the population.

Vector<double>& EvolutionaryAlgorithm::get_fitness(void)
{
   return(fitness);
}


// Vector<bool>& get_selection(void) method

/// This method returns the actual selection value of all individuals in the population.

Vector<bool>& EvolutionaryAlgorithm::get_selection(void)
{
   return(selection);
}


bool EvolutionaryAlgorithm::get_fitness_graph_history(void)
{
   return(fitness_graph_history);
}


bool EvolutionaryAlgorithm::get_elite_population_history(void)
{
   return(elite_population_history);
}


// bool get_reserve_population_history(void) method

/// This method returns true if the population history vector of matrices is to be reserved, and false otherwise.

bool EvolutionaryAlgorithm::get_reserve_population_history(void)
{
   return(reserve_population_history);
}


// bool get_reserve_mean_norm_history(void) method

/// This method returns true if the mean population norm history vector is to be reserved, and false otherwise.

bool EvolutionaryAlgorithm::get_reserve_mean_norm_history(void)
{
   return(reserve_mean_norm_history);
}


// bool get_reserve_standard_deviation_norm_history(void) method

/// This method returns true if the standard deviation of the population norm history vector is to be reserved,
/// and false otherwise.

bool EvolutionaryAlgorithm::get_reserve_standard_deviation_norm_history(void)
{
   return(reserve_standard_deviation_norm_history);
}


// bool get_reserve_best_norm_history(void) method

/// This method returns true if the norm of the best individual in the population history vector is to be
/// reserved, and false otherwise.

bool EvolutionaryAlgorithm::get_reserve_best_norm_history(void)
{
   return(reserve_best_norm_history);
}


// bool get_reserve_mean_evaluation_history(void) method

/// This method returns true if the mean evaluation history vector is to be reserved, and false otherwise.

bool EvolutionaryAlgorithm::get_reserve_mean_evaluation_history(void)
{
   return(reserve_mean_evaluation_history);
}


// bool get_reserve_standard_deviation_evaluation_history(void) method

/// This method returns true if the standard deviation of the evaluation history vector is to be reserved,
/// and false otherwise.

bool EvolutionaryAlgorithm::get_reserve_standard_deviation_evaluation_history(void)
{
   return(reserve_standard_deviation_evaluation_history);
}


// bool get_reserve_best_evaluation_history(void) method

/// This method returns true if the best evaluation history vector is to be reserved, and false otherwise.

bool EvolutionaryAlgorithm::get_reserve_best_evaluation_history(void)
{
   return(reserve_best_evaluation_history);
}


// Vector< Matrix<double> >& get_population_history(void) method

/// This method returns the population history over the training epochs, which is a vector of matrices.

Vector< Matrix<double> >& EvolutionaryAlgorithm::get_population_history(void)
{
   return(population_history);
}


// Vector<double>& get_mean_norm_history(void) method

/// This method returns the mean norm history.

Vector<double>& EvolutionaryAlgorithm::get_mean_norm_history(void)
{
   return(mean_norm_history);
}


// Vector<double>& get_standard_deviation_norm_history(void) method

/// This method returns the standard deviation norm history.

Vector<double>& EvolutionaryAlgorithm::get_standard_deviation_norm_history(void)
{
   return(standard_deviation_norm_history);
}


// Vector<double>& get_best_norm_history(void) method

/// This method returns the best norm history.

Vector<double>& EvolutionaryAlgorithm::get_best_norm_history(void)
{
   return(best_norm_history);
}


// Vector<double>& get_mean_evaluation_history(void) method

/// This method returns a history with the mean evaluation of the population during training.

Vector<double>& EvolutionaryAlgorithm::get_mean_evaluation_history(void)
{
   return(mean_evaluation_history);
}


// Vector<double>& get_standard_deviation_evaluation_history(void) method

/// This method returns a history with the standard deviation of the population evaluation during training.

Vector<double>& EvolutionaryAlgorithm::get_standard_deviation_evaluation_history(void)
{
   return(standard_deviation_evaluation_history);
}


// Vector<double>& get_best_evaluation_history(void) method

/// This method returns a history with the evaluation value of the best individual ever during training.

Vector<double>& EvolutionaryAlgorithm::get_best_evaluation_history(void)
{
   return(best_evaluation_history);
}


// void set(void) method

/// This method sets the objective functional pointer of this object to NULL.
/// It also sets the rest of members to their default values.

void EvolutionaryAlgorithm::set(void)
{
   objective_functional_pointer = NULL;

   set_default();
}


// void set(ObjectiveFunctional*) method

/// This method sets a new objective functional pointer to the evolutionary algorithm object.
/// It also sets the rest of members to their default values.

void EvolutionaryAlgorithm::set(ObjectiveFunctional* new_objective_functional_pointer)
{
   objective_functional_pointer = new_objective_functional_pointer;

   set_default();
}


// void set_default(void) method

/// This method sets the members of the evolutionary algorithm object to their default values.
/// Training operators:
/// <ul>
/// <li> Fitness assignment method: Linear ranking.
/// <li> Selection method: Stochastic universal sampling.
/// <li> Recombination method: Intermediate.
/// <li> Mutation method: Normal.
/// </ul>
/// Training parameters:
/// <ul>
/// <li> Population size: 10*parameters_number or 0.
/// <li> Perform elitism: false.
/// <li> Selective pressure: 1.5.
/// <li> Recombination size: 0.25.
/// <li> Mutation rate: = 1/parameters_number or 0.
/// <li> Mutation range: = 0.1
/// </ul>
/// Stopping criteria:
/// <ul>
/// <li> Evaluation goal: -1.0e99.
/// <li> Mean evaluation goal: -1.0e99.
/// <li> Standard deviation of evaluation goal: -1.0e99.
/// <li> Maximum training time: 1.0e6.
/// <li> Maximum number of generations: 100.
/// </ul>
/// Training history:
/// <ul>
/// <li> Population = false.
/// <li> Mean norm = false.
/// <li> Standard deviation norm = false.
/// <li> Best norm = false.
/// <li> Mean evaluation = false.
/// <li> Standard deviation evaluation = false.
/// <li> Best evaluation = false.
/// </ul>
/// User stuff:
/// <ul>
/// <li> Display: true.
/// <li> Display period: 1.
/// </ul>

void EvolutionaryAlgorithm::set_default(void)
{
   MultilayerPerceptron* multilayer_perceptron_pointer = NULL;

   if(objective_functional_pointer != NULL)
   {
      multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();
      //multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();
   }

   int parameters_number = 0;

   if(multilayer_perceptron_pointer != NULL)
   {
      parameters_number = multilayer_perceptron_pointer->get_parameters_number();
   }
   else
   {
      parameters_number = 0;
   }

   // Fitness assignment method

   fitness_assignment_method = LinearRanking;

   // Selection method

   selection_method = StochasticUniversalSampling;

   // Recombination method

   recombination_method = Intermediate;

   // Mutation method

   mutation_method = Normal;

   // Training parameters

   int population_size = 10*parameters_number;

   crossover_percentage = 0.5;

   elitism = true;
   elitism_percentage = 0.25;

   selective_pressure = 1.5;

   recombination_size = 0.25;

   if(parameters_number != 0)
   {
      mutation_rate = 1.0/(double)parameters_number;
      mutation_rate_for_ES = 0.25;
   }
   else
   {
      mutation_rate = 0.0;
      mutation_rate_for_ES = 0.0;
   }

   mutation_range = 0.1;
   mutation_range_for_ES = 0.15;

   evaluation_sample_size = 1;

   // Stopping criteria

   evaluation_goal = -1.0e99;
   mean_evaluation_goal = -1.0e99;
   standard_deviation_evaluation_goal = 0.0;

   maximum_time = 1.0e6;

   maximum_generations_number = 1000;

   // Population matrix

   population.set(population_size, parameters_number);

   // Elite Population Gene matrix

   elite_population_gene.set(1, parameters_number);

   // Elite Population Lookup vector

   //elite_population_lookup.set(population_size);

   initialize_population_normal();

   // Evaluation vector

   evaluation.set(population_size);

  // Rank vector

   rank.set(population_size);


   // Fitness vector

   fitness.set(population_size);

   // Selection vector

   selection.set(population_size);

   // Training history

   fitness_graph_history = false;
   fitness_graph_file = NULL;

   elite_population_history = false;
   elite_population_file = NULL;

   reserve_population_history = false;

   reserve_best_individual_history = false;

   reserve_mean_norm_history = false;
   reserve_standard_deviation_norm_history = false;
   reserve_best_norm_history = false;

   reserve_mean_evaluation_history = false;
   reserve_standard_deviation_evaluation_history = false;
   reserve_best_evaluation_history = false;

   reserve_elapsed_time_history = false;

   // User stuff

   display_period = 100;
}


// void set_population_size(int) method

/// This method sets a new population with a new number of individuals.
/// The new population size must be an even number equal or greater than four.
///
/// @param new_population_size Number of individuals in the population. This must be an even number equal or
/// greater than four.

void EvolutionaryAlgorithm::set_population_size(int new_population_size)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population_size(int) method." << std::endl
                << "Objective functional pointer cannot be NULL." << std::endl;
       exit(1);
   }

   #endif

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   // Control sentence (if debug)

   #ifdef _DEBUG

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population_size(int) method." << std::endl
                << "Multilayer perceptron pointer cannot be NULL." << std::endl;
       exit(1);
   }

   #endif

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   if(new_population_size < 4)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population_size(int) method." << std::endl
                << "New population size must be equal or greater than 4." << std::endl;

      exit(1);
   }
   else if(new_population_size%2 != 0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population_size(int) method." << std::endl
                << "New population size is not divisible by 2." << std::endl;

      exit(1);
   }
   else
   {
      // Set population matrix

      population.resize(new_population_size, parameters_number);

      initialize_population_normal();

      // Set evaluation vector

      evaluation.resize(new_population_size);

      // Set fitness vector

      fitness.resize(new_population_size);

      // Set selection vector

      selection.resize(new_population_size);

      // Set rank vector

      rank.resize(new_population_size);
   }
}


// void set_fitness_assignment_method(const std::string&) method

/// This method sets a new method for fitness assignment from a string containing the name.
/// Possible values are:
/// <ul>
/// <li> "LinearRanking"
/// </ul>
/// @param new_fitness_assignment_method_name String with name of method for fitness assignment.

void EvolutionaryAlgorithm::set_fitness_assignment_method(const std::string& new_fitness_assignment_method_name)
{
   if(new_fitness_assignment_method_name == "LinearRanking")
   {
      fitness_assignment_method = LinearRanking;
   }
   if(new_fitness_assignment_method_name == "MyLinearRanking")
   {
      fitness_assignment_method = MyLinearRanking;
   }
   else
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_fitness_assignment_method(const std::string&) method." << std::endl
        << "Unknown fitness assignment method: " << new_fitness_assignment_method_name << "." <<std::endl;

      exit(1);
   }
}


// void set_selection_method(const std::string&) method

/// This method sets a new method for selection from a string containing the name.
/// Possible values are:
/// <ul>
/// <li> "LinearRanking"
/// <li> "StochasticUniversalSampling"
/// </ul>
/// @param new_selection_method_name String with name of method for selection.

void EvolutionaryAlgorithm::set_selection_method(const std::string& new_selection_method_name)
{
   if(new_selection_method_name == "RouletteWheel")
   {
      selection_method = RouletteWheel;
   }
   if(new_selection_method_name == "MyRouletteWheel")
   {
      selection_method = MyRouletteWheel;
   }
   else if(new_selection_method_name == "StochasticUniversalSampling")
   {
      selection_method = StochasticUniversalSampling;
   }
   else
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_selection_method(const std::string&) method." << std::endl
        << "Unknown selection method: " << new_selection_method_name << "." <<std::endl;

      exit(1);
   }
}


// void set_recombination_method(const std::string&) method

/// This method sets a new method for recombination from a string containing the name.
/// Possible values are:
/// <ul>
/// <li> "Line"
/// <li> "Intermediate"
/// </ul>
/// @param new_recombination_method_name String with name of method for recombination.

void EvolutionaryAlgorithm::set_recombination_method(const std::string& new_recombination_method_name)
{
   if(new_recombination_method_name == "Line")
   {
      recombination_method = Line;
   }
   else if(new_recombination_method_name == "Intermediate")
   {
      recombination_method = Intermediate;
   }
   else if(new_recombination_method_name == "MyIntermediate")
   {
      recombination_method = MyIntermediate;
   }
   else if(new_recombination_method_name == "MyIntermediateWithElitism")

   {
      recombination_method = MyIntermediateWithElitism;
   }
   else if(new_recombination_method_name == "MyIntermediateWithElitismAndES")

   {
      recombination_method = MyIntermediateWithElitismAndES;
   }
   else
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_recombination_method(const std::string&) method." << std::endl
        << "Unknown recombination method: " << new_recombination_method_name << "." <<std::endl;

      exit(1);
   }
}


// void set_mutation_method(const std::string&) method

/// This method sets a new method for mutation from a string containing the name.
/// Possible values are:
/// <ul>
/// <li> "Normal"
/// <li> "Uniform"
/// </ul>
/// @param new_mutation_method_name String with name of method for mutation.

void EvolutionaryAlgorithm::set_mutation_method(const std::string& new_mutation_method_name)
{
   if(new_mutation_method_name == "Normal")
   {
      mutation_method = Normal;
   }

   else if(new_mutation_method_name == "MyNormal")
   {
      mutation_method = MyNormal;
   }

   else if(new_mutation_method_name == "MyNormalWithES")
   {
      mutation_method = MyNormalWithES;
   }

   else if(new_mutation_method_name == "Uniform")
   {
      mutation_method = Uniform;
   }
   else
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_mutation_method(const std::string&) method." << std::endl
        << "Unknown mutationg method: " << new_mutation_method_name << "." <<std::endl;

      exit(1);
   }
}


// void set_population(const Matrix<double>&) method

/// This method sets a new population.
///
/// @param new_population Population Matrix.

void EvolutionaryAlgorithm::set_population(const Matrix<double>& new_population)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population(const Matrix<double>&) method." << std::endl
                << "Objective functional pointer cannot be NULL." << std::endl;

       exit(1);
   }

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population(const Matrix<double>&) method." << std::endl
                << "Multilayer perceptron pointer cannot be NULL." << std::endl;

       exit(1);
   }

   int population_size = get_population_size();
   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   if(new_population.get_rows_number() != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population(const Matrix<double>&) method." << std::endl
                << "New population size is not equal to population size." << std::endl;

      exit(1);
   }
   else if(new_population.get_columns_number() != parameters_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_population(const Matrix<double>&) method." << std::endl
                << "New number of parameters is not equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set population

   population = new_population;
}


// void set_evaluation(const Vector<double>&) method

/// This method sets a new population evaluation vector.
///
/// @param new_evaluation Population evaluation values.

void EvolutionaryAlgorithm::set_evaluation(const Vector<double>& new_evaluation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   int population_size = get_population_size();

   if(new_evaluation.get_size() != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_evaluation(const Vector<double>&) method." << std::endl
                << "Size is not equal to population size." << std::endl;

      exit(1);
   }

   #endif

   // Set evaluation

   evaluation = new_evaluation;
}


// void set_fitness(const Vector<double>&) method

/// This method sets a new population fitness vector.
///
/// @param new_fitness Population fitness values.

void EvolutionaryAlgorithm::set_fitness(const Vector<double>& new_fitness)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   int population_size = get_population_size();

   if(new_fitness.get_size() != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_fitness(Vector<double>) method." << std::endl
                << "Size is not equal to population size." << std::endl;

      exit(1);
   }

   #endif

   // Set fitness

   fitness = new_fitness;
}


// void set_selection(const Vector<bool>&) method

/// This method sets a new population selection vector.
///
/// @param new_selection Population selection values.

void EvolutionaryAlgorithm::set_selection(const Vector<bool>& new_selection)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   int population_size = get_population_size();

   if(new_selection.get_size() != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_selection(Vector<double>) method." << std::endl
                << "Size is not equal to population size." << std::endl
                << std::endl;

      exit(1);
   }

   #endif

   // Set selection

   selection = new_selection;
}


void EvolutionaryAlgorithm::set_fitness_graph_history(bool new_fitness_graph_history)
{
   fitness_graph_history = new_fitness_graph_history;
}


void EvolutionaryAlgorithm::set_fitness_graph_file(GraphFile *fitness_graph_file_pointer)
{
  fitness_graph_file = fitness_graph_file_pointer;
}

void EvolutionaryAlgorithm::set_elite_population_history(bool new_elite_population_history)
{
   elite_population_history = new_elite_population_history;
}


void EvolutionaryAlgorithm::set_elite_population_file(FileHandler* new_elite_population_file)
{
  elite_population_file = new_elite_population_file;
}


// void set_reserve_population_history(bool) method

/// This method makes the population history vector of matrices to be reseved or not in memory.
///
/// @param new_reserve_population_history True if the population history vector of matrices is to be reserved, false
/// otherwise.

void EvolutionaryAlgorithm::set_reserve_population_history(bool new_reserve_population_history)
{
   reserve_population_history = new_reserve_population_history;
}


// void set_reserve_mean_norm_history(bool) method

/// This method makes the mean norm history vector to be reseved or not in memory.
///
/// @param new_reserve_mean_norm_history True if the mean norm history vector is to be reserved, false otherwise.

void EvolutionaryAlgorithm::set_reserve_mean_norm_history(bool new_reserve_mean_norm_history)
{
   reserve_mean_norm_history = new_reserve_mean_norm_history;
}


// void set_reserve_standard_deviation_norm_history(bool) method

/// This method makes the standard deviation norm history vector to be reseved or not in memory.
///
/// @param new_reserve_standard_deviation_norm_history True if the standard deviation norm history vector is to be
/// reserved, false otherwise.

void EvolutionaryAlgorithm::
set_reserve_standard_deviation_norm_history(bool new_reserve_standard_deviation_norm_history)
{
   reserve_standard_deviation_norm_history = new_reserve_standard_deviation_norm_history;
}


// void set_reserve_best_norm_history(bool) method

/// This method makes the best norm history vector to be reseved or not in memory.
///
/// @param new_reserve_best_norm_history True if the best norm history vector is to be reserved, false otherwise.

void EvolutionaryAlgorithm::set_reserve_best_norm_history(bool new_reserve_best_norm_history)
{
   reserve_best_norm_history = new_reserve_best_norm_history;
}


// void set_reserve_mean_evaluation_history(bool) method

/// This method makes the mean evaluation history vector to be reseved or not in memory.
///
/// @param new_reserve_mean_evaluation_history True if the mean evaluation history vector is to be reserved, false
/// otherwise.

void EvolutionaryAlgorithm::set_reserve_mean_evaluation_history(bool new_reserve_mean_evaluation_history)
{
   reserve_mean_evaluation_history = new_reserve_mean_evaluation_history;
}


// void set_reserve_standard_deviation_evaluation_history(bool) method

/// This method makes the standard deviation evaluation history vector to be reseved or not in memory.
///
/// @param new_reserve_standard_deviation_evaluation_history True if the standard deviation evaluation history vector
/// is to be reserved, false otherwise.

void EvolutionaryAlgorithm
::set_reserve_standard_deviation_evaluation_history(bool new_reserve_standard_deviation_evaluation_history)
{
   reserve_standard_deviation_evaluation_history = new_reserve_standard_deviation_evaluation_history;
}


// void set_reserve_best_evaluation_history(bool) method

/// This method makes the best evaluation history vector to be reseved or not in memory.
///
/// @param new_reserve_best_evaluation_history True if the best evaluation history vector is to be reserved,
/// false otherwise.

void EvolutionaryAlgorithm::set_reserve_best_evaluation_history(bool new_reserve_best_evaluation_history)
{
   reserve_best_evaluation_history = new_reserve_best_evaluation_history;
}


// void set_reserve_all_training_history(bool) method

/// This method makes the training history of all variables to reseved or not in memory.
///
/// @param new_reserve_all_training_history True if the training history of all variables is to be reserved,
/// false otherwise.

void EvolutionaryAlgorithm::set_reserve_all_training_history(bool new_reserve_all_training_history)
{
   // Multilayer perceptron

   reserve_population_history = new_reserve_all_training_history;

   reserve_best_individual_history = new_reserve_all_training_history;

   reserve_mean_norm_history = new_reserve_all_training_history;
   reserve_standard_deviation_norm_history = new_reserve_all_training_history;
   reserve_best_norm_history = new_reserve_all_training_history;

   // Objective functional

   reserve_mean_evaluation_history = new_reserve_all_training_history;
   reserve_standard_deviation_evaluation_history = new_reserve_all_training_history;
   reserve_best_evaluation_history = new_reserve_all_training_history;

   // Training algorithm

   reserve_elapsed_time_history = new_reserve_all_training_history;
}


// void set_population_history(const Vector< Matrix<double> >&) method

/// This method sets a new matrix containing the training direction history over the training epochs.
/// Each element in the vector must contain the population matrix of one single generation.
///
/// @param new_population_history Population history vector of matrices.

void EvolutionaryAlgorithm::set_population_history(const Vector< Matrix<double> >& new_population_history)
{
   population_history = new_population_history;
}


// void set_mean_norm_history(const Vector<double>&) method

/// This method sets a new vector containing the mean norm history over the training epochs.
/// Each element in the vector must contain the mean norm of one single generation.
///
/// @param new_mean_norm_history Mean norm history vector.

void EvolutionaryAlgorithm::set_mean_norm_history(const Vector<double>& new_mean_norm_history)
{
   mean_norm_history = new_mean_norm_history;
}


// void set_standard_deviation_norm_history(Vector<double>) method

/// This method sets a new vector containing the standard deviation norm history over the training epochs.
/// Each element in the vector must contain the standard deviation norm of one single generation.
///
/// @param new_standard_deviation_norm_history Standard deviation norm history vector.

void EvolutionaryAlgorithm::
set_standard_deviation_norm_history(const Vector<double>& new_standard_deviation_norm_history)
{
   standard_deviation_norm_history = new_standard_deviation_norm_history;
}


// void set_best_norm_history(Vector<double>) method

/// This method sets a new vector containing the best norm history over the training epochs.
/// Each element in the vector must contain the best norm of one single generation.
///
/// @param new_best_norm_history Best norm history vector.

void EvolutionaryAlgorithm::set_best_norm_history(const Vector<double>& new_best_norm_history)
{
   best_norm_history = new_best_norm_history;
}


// void set_mean_evaluation_history(Vector<double>) method

/// This method sets a new vector containing the mean evaluation history over the training epochs.
/// Each element in the vector must contain the mean evaluation of one single generation.
///
/// @param new_mean_evaluation_history Mean evaluation history vector.

void EvolutionaryAlgorithm::set_mean_evaluation_history(const Vector<double>& new_mean_evaluation_history)
{
   mean_evaluation_history = new_mean_evaluation_history;
}


// void set_standard_deviation_evaluation_history(Vector<double>) method

/// This method sets a new vector containing the standard deviation evaluation history over the training epochs.
/// Each element in the vector must contain the standard deviation evaluation of one single generation.
///
/// @param new_standard_evaluation_evaluation_history Standard deviation evaluation history vector.

void EvolutionaryAlgorithm
::set_standard_deviation_evaluation_history(const Vector<double>& new_standard_evaluation_evaluation_history)
{
   standard_deviation_evaluation_history = new_standard_evaluation_evaluation_history;
}


// void set_best_evaluation_history(Vector<double>) method

/// This method sets a new vector containing the best evaluation history over the training epochs.
/// Each element in the vector must contain the best evaluation of one single generation.
///
/// @param new_best_evaluation_history Best evaluation history vector.

void EvolutionaryAlgorithm::set_best_evaluation_history(const Vector<double>& new_best_evaluation_history)
{
   best_evaluation_history = new_best_evaluation_history;
}


// Vector<double> get_individual(int) method

/// This method returns the Vector of parameters corresponding to the individual i in the population.
///
/// @param i Index of individual in the population.

Vector<double> EvolutionaryAlgorithm::get_individual(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   int population_size = get_population_size();

   if(i >= population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "Vector<double> get_individual(int) method." << std::endl
                << "Index must be less than population size." << std::endl;

      exit(1);
   }

   #endif

   // Get individual

   Vector<double> individual = population.get_row(i);

   return(individual);
}



// set_individual(int, Vector<double>) method

/// This method sets a new Vector of parameters to the individual i in the population.
///
/// @param i Index of individual in the population.
/// @param individual Vector of parameters to be assigned to individual i.

void EvolutionaryAlgorithm::set_individual(int i, const Vector<double>& individual)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   int size = individual.get_size();

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   int population_size = get_population_size();

   if(i >= population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "set_individual(int, Vector<double>) method." << std::endl
                << "Index must be less than population size." << std::endl;

      exit(1);
   }
   else if(size != parameters_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "set_individual(int, Vector<double>) method." << std::endl
                << "Size must be equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   // Get individual

   population.set_row(i, individual);
}


// Vector<double> calculate_population_norm(void) method

/// This method returns a vector containing the norm of each individual in the population.

Vector<double> EvolutionaryAlgorithm::calculate_population_norm(void)
{
   int population_size = get_population_size();

   Vector<double> population_norm(population_size);

   for(int i = 0; i < population_size; i++)



   {
      Vector<double> individual = get_individual(i);

      population_norm[i] = individual.calculate_norm();
   }

   return(population_norm);
}


// double calculate_mean_evaluation(void) method

double EvolutionaryAlgorithm::calculate_mean_evaluation(void)
{
   return(evaluation.calculate_mean());
}


// double calculate_standard_deviation_evaluation(void) method

double EvolutionaryAlgorithm::calculate_standard_deviation_evaluation(void)
{
   return(evaluation.calculate_standard_deviation());
}


// Training parameters


// bool get_elitism(void) method

bool EvolutionaryAlgorithm::get_elitism(void)
{
   return(elitism);
}



// double get_selective_pressure(void) method /// This method returns the selective pressure value.

double EvolutionaryAlgorithm::get_selective_pressure(void)
{
   return(selective_pressure);
}

// double get_elitism_percentage(void) method

/// This method returns the elitism percentage value.

double EvolutionaryAlgorithm::get_elitism_percentage(void)
{
   return(elitism_percentage);
}


// double get_crossover_percentage(void) method

/// This method returns the crossover percentage value.

double EvolutionaryAlgorithm::get_crossover_percentage(void)
{
   return(crossover_percentage);
}


// double get_recombination_size(void) method

/// This method returns the recombination size value.

double EvolutionaryAlgorithm::get_recombination_size(void)
{
   return(recombination_size);
}


// double get_mutation_rate(void) method

/// This method returns the mutation rate value.

double EvolutionaryAlgorithm::get_mutation_rate(void)
{
   return(mutation_rate);
}


double EvolutionaryAlgorithm::get_mutation_rate_for_ES(void)
{
   return(mutation_rate_for_ES);
}


// double get_mutation_range(void) method

/// This method returns the mutation range value.

double EvolutionaryAlgorithm::get_mutation_range(void)
{
   return(mutation_range);
}


double EvolutionaryAlgorithm::get_mutation_range_for_ES(void)
{
   return(mutation_range_for_ES);
}


int EvolutionaryAlgorithm::get_evaluation_sample_size(void)
{
   return(evaluation_sample_size);
}


double EvolutionaryAlgorithm::get_gen_0_min_evaluation_value(void)
{
   return(gen_0_min_evaluation_value);
}


int EvolutionaryAlgorithm::get_gen_0_population_size(void)
{
   return(gen_0_population_size);
}


// double get_maximum_generations_number(void) method

/// This method returns the maximum number of generations to train.

double EvolutionaryAlgorithm::get_maximum_generations_number(void)
{
   return(maximum_generations_number);
}


// double get_mean_evaluation_goal(void) method

double EvolutionaryAlgorithm::get_mean_evaluation_goal(void)
{
   return(mean_evaluation_goal);
}


// double get_standard_deviation_evaluation_goal(void) method

double EvolutionaryAlgorithm::get_standard_deviation_evaluation_goal(void)
{
   return(standard_deviation_evaluation_goal);
}




// void set_elitism(bool) method

void EvolutionaryAlgorithm::set_elitism(bool new_elitism)
{
   elitism = new_elitism;
}

void EvolutionaryAlgorithm::set_elitism_percentage(double new_elitism_percentage)
{
   if(new_elitism_percentage > 1.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_elitism_percentage(double) method." << std::endl
                << "Elitism percentage cannot be greater than 1.0." << std::endl;

      exit(1);
   }

   // Set recombination size

   elitism_percentage = new_elitism_percentage;
}

void EvolutionaryAlgorithm::set_crossover_percentage(double new_crossover_percentage)
{
   if(new_crossover_percentage > 1.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_crossover_percentage(double) method." << std::endl
                << "Crossover size cannot be greater than 1.0." << std::endl;

      exit(1);
   }

   // Set recombination size

   crossover_percentage = new_crossover_percentage;
}


// void set_selective_pressure(double) method

/// This method sets a new value for the selective pressure parameter.
/// Linear ranking allows values for the selective pressure between 1 and 2.
///
/// @param new_selective_pressure Selective pressure value. This must be between 1 and 2 for linear ranking fitness
/// assignment.

void EvolutionaryAlgorithm::set_selective_pressure(double new_selective_pressure)
{
   switch(fitness_assignment_method)
   {
      case LinearRanking:
    {
         if(new_selective_pressure < 1.0 || new_selective_pressure > 2.0)
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void set_selective_pressure(double) method. "
                      << "Case linear ranking." << std::endl
                      << "Selective pressure must be a value between 1 and 2." << std::endl;

            exit(1);
         }

       // Set selective pressure

       selective_pressure = new_selective_pressure;
    }
      break;
   }
}


// void set_recombination_size(double) method

/// This method sets a new value for the recombination size parameter.
/// The recombination size value must be equal or greater than 0.
///
/// @param new_recombination_size Recombination size value. This must be equal or greater than 0.

void EvolutionaryAlgorithm::set_recombination_size(double new_recombination_size)
{
   if(new_recombination_size < 0.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_recombination_size(double) method." << std::endl
                << "Recombination size must be equal or greater than 0." << std::endl;

      exit(1);
   }

   // Set recombination size

   recombination_size = new_recombination_size;
}


// void set_mutation_rate(double) method

/// This method sets a new value for the mutation rate parameter.
/// The mutation rate value must be between 0 and 1.
///
/// @param new_mutation_rate Mutation rate value. This value must lie in the interval [0,1].

void EvolutionaryAlgorithm::set_mutation_rate(double new_mutation_rate)
{
   // Control sentence

   if(new_mutation_rate < 0.0 || new_mutation_rate > 1.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_mutation_rate(double) method." << std::endl
                << "Mutation rate must be a value between 0 and 1. " << std::endl;

      exit(1);
   }

   // Set mutation rate

   mutation_rate = new_mutation_rate;
}


void EvolutionaryAlgorithm::set_mutation_rate_for_ES(double new_mutation_rate_for_ES)
{
   // Control sentence

   if(new_mutation_rate_for_ES < 0.0 || new_mutation_rate_for_ES > 1.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_mutation_rate(double) method." << std::endl
                << "Mutation rate must be a value between 0 and 1. " << std::endl;

      exit(1);
   }

   // Set mutation rate

   mutation_rate_for_ES = new_mutation_rate_for_ES;
}


// void set_mutation_range(double) method

/// This method sets a new value for the mutation range parameter.
/// The mutation range value must be 0 or a positive number.
///
/// @param new_mutation_range Mutation range value. This must be equal or greater than 0.

void EvolutionaryAlgorithm::set_mutation_range(double new_mutation_range)
{
   // Control sentence

   if(new_mutation_range < 0.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_mutation_range(double) method." << std::endl
                << "Mutation range must be equal or greater than 0. " << std::endl;

      exit(1);
   }

   // Set mutation range

   mutation_range = new_mutation_range;
}


void EvolutionaryAlgorithm::set_mutation_range_for_ES(double new_mutation_range_for_ES)
{
   // Control sentence

   if(new_mutation_range_for_ES < 0.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_mutation_range(double) method." << std::endl
                << "Mutation range must be equal or greater than 0. " << std::endl;

      exit(1);
   }

   // Set mutation range

   mutation_range_for_ES = new_mutation_range_for_ES;
}


void EvolutionaryAlgorithm::set_evaluation_sample_size(int new_evaluation_sample_size)
{
   // Control sentence

   if(new_evaluation_sample_size < 1)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_evaluation_sample_size(double) method." << std::endl
                << "evaluation sample size must be greater or equal to 1. " << std::endl;

      exit(1);
   }

   // Set mutation range

   evaluation_sample_size = new_evaluation_sample_size;
}


void EvolutionaryAlgorithm::set_gen_0_min_evaluation_value(double new_gen_0_min_evaluation_value)
{
   // Control sentence

   if(new_gen_0_min_evaluation_value <= 0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_gen_0_min_evaluation_value(double) method." << std::endl
                << "Generation_0 minimum evaluation value must be greater than 0. " << std::endl;

      exit(1);
   }

   // Set mutation range

   gen_0_min_evaluation_value = new_gen_0_min_evaluation_value;
}


void EvolutionaryAlgorithm::set_gen_0_population_size(int new_gen_0_population_size)
{
   // Control sentence

   if(new_gen_0_population_size <= get_population_size())
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_gen_0_population_size(double) method." << std::endl
                << "Generation_0 minimum evaluation value must be greater than Evolution population size. " << std::endl;

      exit(1);
   }

   // Set mutation range

   gen_0_population_size = new_gen_0_population_size;
}


// void set_maximum_generations_number(int) method

/// This method sets a new value for the maximum number of generations to train.
/// The maximum number of generations value must be a positive number.
///
/// @param new_maximum_generations_number Maximum number of generations value.

void EvolutionaryAlgorithm::set_maximum_generations_number(int new_maximum_generations_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(new_maximum_generations_number == 0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_maximum_generations_number(int) method." << std::endl
                << "Maximum number of generations must be greater than 0. " << std::endl;

      exit(1);
   }

   #endif

   // Set maximum number of generations

   maximum_generations_number = new_maximum_generations_number;
}



// void set_mean_evaluation_goal(double) method

void EvolutionaryAlgorithm::set_mean_evaluation_goal(double new_mean_evaluation_goal)
{
   mean_evaluation_goal = new_mean_evaluation_goal;
}


// void set_standard_deviation_evaluation_goal(double) method

void EvolutionaryAlgorithm::set_standard_deviation_evaluation_goal(double new_standard_deviation_evaluation_goal)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(new_standard_deviation_evaluation_goal < 0.0)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void set_standard_deviation_evaluation_goal(double) method." << std::endl
                << "Standard deviation of evaluation goal must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set standard deviation of evaluation goal

   standard_deviation_evaluation_goal = new_standard_deviation_evaluation_goal;

}

// void set_fitness_assignment_method(FitnessAssignmentMethod) method

/// This method sets a new fitness assignment method to be used for training.
///
/// @param new_fitness_assignment_method Fitness assignment method chosen for training.

void EvolutionaryAlgorithm::set_fitness_assignment_method
(const EvolutionaryAlgorithm::FitnessAssignmentMethod& new_fitness_assignment_method)
{
   fitness_assignment_method = new_fitness_assignment_method;
}


// void set_selection_method(SelectionMethod) method

/// This method sets a new selection method to be used for training.
///
/// @param new_selection_method Selection method chosen for training.

void EvolutionaryAlgorithm::
set_selection_method(const EvolutionaryAlgorithm::SelectionMethod& new_selection_method)
{
   selection_method = new_selection_method;
}


// void set_recombination_method(RecombinationMethod) method

/// This method sets a new recombination method to be used for training.
///
/// @param new_recombination_method Recombination method chosen for training.

void EvolutionaryAlgorithm
::set_recombination_method(const EvolutionaryAlgorithm::RecombinationMethod& new_recombination_method)
{
   recombination_method = new_recombination_method;
}


// void set_mutation_method(MutationMethod) method

/// This method sets a new mutation method to be used for training.
///
/// @param new_mutation_method Mutation method chosen for training.

void EvolutionaryAlgorithm::set_mutation_method(const EvolutionaryAlgorithm::MutationMethod& new_mutation_method)
{
   mutation_method = new_mutation_method;
}


// void initialize_population(double) method



void EvolutionaryAlgorithm::initialize_population(double new_value)
{
   population.initialize(new_value);
}



// void initialize_population_uniform(void) method

/// This method initializes the parameters of all the individuals in the population at random, with values
/// comprised between -1 and 1.

void EvolutionaryAlgorithm::initialize_population_uniform(void)
{
   population.initialize_uniform();
}


// void initialize_population_uniform(double, double) method

/// This method initializes the parameters of all the individuals in the population at random, with values
/// comprised between a minimum and a maximum value.
///
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.

void EvolutionaryAlgorithm::initialize_population_uniform(double minimum, double maximum)
{
   population.initialize_uniform(minimum, maximum);
}


// void initialize_population_uniform(Vector<double>, Vector<double>) method

/// This method initializes the parameters of all the individuals in the population at random, with values
/// comprised between different minimum and maximum values for each variable.
///
/// @param minimum Vector of minimum initialization values.
/// @param maximum Vector of maximum initialization values.

void EvolutionaryAlgorithm::
initialize_population_uniform(const Vector<double>& minimum, const Vector<double>& maximum)
{
   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG

   int minimum_size = minimum.get_size();
   int maximum_size = maximum.get_size();

   if(minimum_size != parameters_number || maximum_size != parameters_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void initialize_population_uniform(Vector<double>, Vector<double>)." << std::endl
                << "Minimum value and maximum value sizes must be equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> individual(parameters_number);

   int population_size = get_population_size();

   for(int i = 0; i < population_size; i++)
   {
      individual.initialize_uniform(minimum, maximum);

      set_individual(i, individual);
   }
}


// Avinash Ranganath
// void initialize_population_uniform_independent_parameters(Vector<double>, Vector<double>) method

/// This method initializes only the independent parameters of all the individuals in the population at random, with values
/// comprised between different minimum and maximum values for each variable.
///
/// @param minimum Vector of minimum initialization values.
/// @param maximum Vector of maximum initialization values.

void EvolutionaryAlgorithm::
initialize_population_uniform_independent_parameters(const Vector<double>& minimum, const Vector<double>& maximum)
{
   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();
   int independent_parameters_number = multilayer_perceptron_pointer->get_independent_parameters_number();
   int parameters_number = neural_parameters_number + independent_parameters_number;

   // Control sentence (if debug)

   #ifdef _DEBUG

   int minimum_size = minimum.get_size();
   int maximum_size = maximum.get_size();

   if(minimum_size != independent_parameters_number || maximum_size != independent_parameters_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void initialize_population_uniform_independent_parameters(Vector<double>, Vector<double>)." << std::endl
                << "Minimum value and maximum value sizes must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> individual(parameters_number);
   Vector<double> neural_parameters(neural_parameters_number);
   Vector<double> independent_parameters(independent_parameters_number);

   int population_size = get_population_size();

   for(int i = 0; i < population_size; i++)
   {
      individual = get_individual(i);

      neural_parameters = individual.extract(0, neural_parameters_number);
      independent_parameters.initialize_uniform(minimum, maximum);

      individual = neural_parameters.assemble(independent_parameters);
      set_individual(i, individual);
   }
}


// void initialize_population_normal(void) method

/// This method initializes the parameters of all the individuals in the population with random values chosen
/// from a normal distribution with mean 0 and standard deviation 1.

void EvolutionaryAlgorithm::initialize_population_normal(void)
{
   population.initialize_normal();
}


// void initialize_population_normal(double, double) method

/// This method initializes the parameters of all the individuals in the population with random values chosen
/// from a normal distribution with a given mean and a given standard deviation.
///
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.

void EvolutionaryAlgorithm::initialize_population_normal(double mean, double standard_deviation)
{
   population.initialize_normal(mean, standard_deviation);
}


// void initialize_population_normal(Vector<double>, Vector<double>) method

/// This method initializes the parameters of all the individuals in the population with random values chosen
/// from normal distributions with different mean and standard deviation for each free parameter.
///
/// @param mean Vector of mean values.
/// @param standard_deviation Vector of standard deviation values.

void EvolutionaryAlgorithm::
initialize_population_normal(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG

   int mean_size = mean.get_size();
   int standard_deviation_size = standard_deviation.get_size();

   if(mean_size != parameters_number || standard_deviation_size != parameters_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void initialize_population_normal(Vector<double>, Vector<double>)." << std::endl
                << "Mean and standard deviation sizes must be equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> individual(parameters_number);

   int population_size = get_population_size();

   for(int i = 0; i < population_size; i++)
   {
      individual.initialize_normal(mean, standard_deviation);

      set_individual(i, individual);
   }
}


// void perform_fitness_assignment(void) method

void EvolutionaryAlgorithm::perform_fitness_assignment(void)
{
   switch(fitness_assignment_method)
   {
      case LinearRanking:
      {
         perform_linear_ranking_fitness_assignment();
      }

      break;

      case MyLinearRanking:
   {
      perform_my_linear_ranking_fitness_assignment();
   }

      break;

    default:
    {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void perform_fitness_assignment(void)." << std::endl
                   << "Unknown fitness assignment method." << std::endl;

         exit(1);
    }
    break;
   }
}


// void perform_selection(void) method

void EvolutionaryAlgorithm::perform_selection(void)
{
   switch(selection_method)
   {
      case RouletteWheel:
      {
         perform_roulette_wheel_selection();
      }
      break;

      case MyRouletteWheel:
      {
         perform_my_roulette_wheel_selection();
      }
      break;

      case StochasticUniversalSampling:
      {
         perform_stochastic_universal_sampling_selection();
      }
      break;

    default:
    {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void perform_selection(void)." << std::endl
                   << "Unknown selection method." << std::endl;

         exit(1);
    }
    break;
   }

}


// void perform_recombination(void) method

void EvolutionaryAlgorithm::perform_recombination(void)
{
   switch(recombination_method)
   {
      case Intermediate:
      {
         perform_intermediate_recombination();
      }
      break;

      case MyIntermediate:
      {
         perform_my_intermediate_recombination();
      }

      case MyIntermediateWithElitism:
      {
         perform_my_intermediate_recombination_with_elitism();
      }
      break;

      case MyIntermediateWithElitismAndES:
      {
         perform_my_intermediate_recombination_with_elitism_and_evolution_strategy();
      }
      break;

      case Line:
      {
         perform_line_recombination();
      }
      break;

    default:
    {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void perform_recombination(void)." << std::endl
                   << "Unknown recombination method." << std::endl;

         exit(1);
    }
    break;
   }
}


// void perform_mutation(void) method

void EvolutionaryAlgorithm::perform_mutation(void)
{
   switch(mutation_method)
   {
      case Normal:
      {
         perform_normal_mutation();
      }
      break;

      case MyNormal:
      {
         perform_my_normal_mutation();
      }
      break;

      case MyNormalWithES:
      {
         perform_my_normal_mutation_with_ES();
      }
      break;

      case Uniform:
      {
         perform_uniform_mutation();
      }
      break;

    default:
    {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void perform_mutationg(void)." << std::endl
                   << "Unknown mutation method." << std::endl;

         exit(1);
    }
    break;
   }
}


// void evolve_population(void) method

void EvolutionaryAlgorithm::evolve_population(void)
{
   // Fitness assignment

   perform_fitness_assignment();

   // Selection

   perform_selection();

   // Recombination

   perform_recombination();

   // Mutation

   perform_mutation();
}


//Avinash Ranganath
// This method is similar to the method evolve_population(void), but here the generation information
// is passed as a parameter, and a method to save the best performing individual(s) is invoked.

void EvolutionaryAlgorithm::evolve_population(int generation)
{
   // Fitness assignment

   perform_fitness_assignment();

   if(elite_population_history)
   {
      save_member(generation);
   }

   // Selection

   perform_selection();

   // Recombination

   perform_recombination();

   // Mutation

   perform_mutation();
}


// Avinash Ranganath

// This methos is same as the , but here the generation details are passed to the bjective function.

void EvolutionaryAlgorithm::populate_generation_0(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void populate_generation_0(void)." << std::endl
                << "Objective functional pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   // Multilayer perceptron

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   // Control sentence (if debug)

   #ifdef _DEBUG

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void populate_generation_0(void)." << std::endl
                << "Multilayer perceptron pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> individual(parameters_number);

   // Evaluate objective functional for all individuals

   int population_size = get_population_size();
   double evaluation = 0;
   int i=0;

   //for(int i = 0; i < population_size; i++)
   do
   {
      individual.initialize_normal();

      evaluation = objective_functional_pointer->calculate_potential_evaluation(individual, 0, i, 1); // Should be reverted
      //evaluation = objective_functional_pointer->calculate_potential_evaluation(individual);

      if(!(evaluation > -1.0e99 && evaluation < 1.0e99))
      {

         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void populate_generation_0(void) method." << std::endl
                   << "Evaluation of individual " << i << " is not a real number." << std::endl;

         exit(1);
      }

      if(evaluation >= gen_0_min_evaluation_value)
      {
         set_individual(i, individual);
         i++;
      }
   }while(i<population_size);
}


// Avinash Ranganath

// This methos is used for evaluating an initial population of size n > m [Size of the evolution population size], and select the top m individuals to populate the actual evolution population.

void EvolutionaryAlgorithm::populate_generation_0_augmented_polulation(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void populate_generation_0_augmented_polulation(void)." << std::endl
                << "Objective functional pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   // Multilayer perceptron

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   // Control sentence (if debug)

   #ifdef _DEBUG

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void populate_generation_0_augmented_polulation(void)." << std::endl
                << "Multilayer perceptron pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Matrix<double> gen_0_population(gen_0_population_size, parameters_number);
   gen_0_population.initialize_normal();
   Vector<double> evaluation(gen_0_population_size);

   Vector<double> individual(parameters_number);

   // Evaluate objective functional for all individuals

   for(int i = 0; i < gen_0_population_size; i++)
   {
      individual = gen_0_population.get_row(i);

      evaluation[i] = objective_functional_pointer->calculate_potential_evaluation(individual, 0, i, 5);
      //std::cout << generation << " -- " << i << ": " << 5.0-evaluation[i] << std::endl; // Debugger

      if(!(evaluation[i] > -1.0e99 && evaluation[i] < 1.0e99))
      {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void evaluate_population(void) method." << std::endl
                   << "Evaluation of individual " << i << " is not a real number." << std::endl;

         exit(1);
      }
      //std::cout << std::endl << individual << std::endl; //Debugger
   }

/**********************************************DEBUGGER*****************************************************/
   std::cout << endl;
   for(int i = 0; i < gen_0_population_size; i++)
   {
      std::cout << "Evaluation[" << i << "] = " << evaluation[i] << std::endl;
   }
/**********************************************DEBUGGER*****************************************************/

   Vector<double> evaluation_rank_index(gen_0_population_size);
   double temp;

   for(int i = 0; i < gen_0_population_size; i++)
   {
      evaluation_rank_index[i] = i;
      for(int j = 0; j < gen_0_population_size; j++)
      {
         if(evaluation[j] >= evaluation[evaluation_rank_index[i]])
         {
            /*temp = evaluation[i];
            evaluation[i] = evaluation[j];
            evaluation[j] = temp;*/
            evaluation_rank_index[i] = j;
         }
      }
      evaluation[evaluation_rank_index[i]] = -10;
      //std::cout << "Completed assigning rank: " << i << std::endl;
   }

/**********************************************DEBUGGER*****************************************************/
   std::cout << endl;
   for(int i = 0; i < gen_0_population_size-1; i++)
   {
      std::cout << "Evaluation[" << i << "] = " << evaluation[i] << "  Evaluation_Rank_Index[" << i << "] = " << evaluation_rank_index[i] << std::endl;
   }
   std::cout << endl;
/**********************************************DEBUGGER*****************************************************/

   int population_size = get_population_size();
   //int row_index = 0;

   for(int i = 0; i < population_size; i++)
   {
      individual = gen_0_population.get_row(evaluation_rank_index[i]);
      set_individual(i, individual);
   }
}


// void evaluate_population(void) method

/// This method evaluates the objective functional of all individuals in the population.
/// Results are stored in the evaluation vector.

void EvolutionaryAlgorithm::evaluate_population()
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void evaluate_population(void)." << std::endl
                << "Objective functional pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   // Multilayer perceptron

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   // Control sentence (if debug)

   #ifdef _DEBUG

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void evaluate_population(void)." << std::endl
                << "Multilayer perceptron pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> individual(parameters_number);

   // Evaluate objective functional for all individuals

   int population_size = get_population_size();

   for(int i = 0; i < population_size; i++)
   {
      individual = get_individual(i);

      evaluation[i] = objective_functional_pointer->calculate_potential_evaluation(individual);
      //std::cout << generation << " -- " << i << ": " << 5.0-evaluation[i] << std::endl; // Debugger

      if(!(evaluation[i] > -1.0e99 && evaluation[i] < 1.0e99))
      {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void evaluate_population(void) method." << std::endl
                   << "Evaluation of individual " << i << " is not a real number." << std::endl;

         exit(1);
      }
   }
}


// Avinash Ranganath

// This methos is same as the , but here the generation details are passed to the bjective function.

void EvolutionaryAlgorithm::evaluate_population(int generation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void evaluate_population(void)." << std::endl
                << "Objective functional pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   // Multilayer perceptron

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   // Control sentence (if debug)

   #ifdef _DEBUG

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void evaluate_population(void)." << std::endl
                << "Multilayer perceptron pointer cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> individual(parameters_number);

   // Evaluate objective functional for all individuals

   int population_size = get_population_size();

   for(int i = 0; i < population_size; i++)
   {
      individual = get_individual(i);

      evaluation[i] = objective_functional_pointer->calculate_potential_evaluation(individual, generation, i,evaluation_sample_size);
      //std::cout << generation << " -- " << i << ": " << 5.0-evaluation[i] << std::endl; // Debugger

      if(!(evaluation[i] > -1.0e99 && evaluation[i] < 1.0e99))
      {
         std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                   << "void evaluate_population(void) method." << std::endl
                   << "Evaluation of individual " << i << " is not a real number." << std::endl;

         exit(1);
      }
      //std::cout << std::endl << individual << std::endl; //Debugger
   }
}


// void perform_linear_ranking_fitness_assignment(void) method
//
/// This method ranks all individuals in the population by their objective evaluation, so that the least fit
/// individual has rank 1 and the fittest individual has rank [population size].
/// It then assigns them a fitness value linearly proportional to their rank. Results are stored in the fitness
/// vector.

void EvolutionaryAlgorithm::perform_linear_ranking_fitness_assignment(void)
{
   // Sorted evaluation vector

   int population_size = get_population_size();

   Vector<double> sorted_evaluation(population_size);

   sorted_evaluation = evaluation;

   std::sort(sorted_evaluation.begin(), sorted_evaluation.end(), std::less<double>());

   // Rank vector

   Vector<int> rank(population_size);

   for(int i = 0; i < population_size; i++)
   {
      for(int j = 0; j < population_size; j++)
      {
         if(evaluation[j] == sorted_evaluation[i])
         {
            rank[j] = population_size - i;
         }
      }
   }

   // Perform linear ranking fitness assignment

   for(int i = 0; i < population_size; i++)
   {
      fitness[i] = 2.0 - selective_pressure
      + 2.0*(selective_pressure - 1.0)*(rank[i] - 1.0)/(population_size - 1.0);

      if(!(fitness[i] > -1.0e99 && fitness[i] < 1.0e99))
      {
         std::cerr << "Flooe Error: EvolutionaryAlgorithm class." << std::endl
                   << "void perform_linear_ranking_fitness_assignment(void) method." << std::endl
                   << "Fitness of individual " << i << " is not a real number." << std::endl;

         exit(1);
      }
   }
}


// Avinash Ranganath
// This is very similar to the linear ranking fitness assignment function, but here the individuals
// are ranked in decending order. This function is an alternate to those evaluations where in there
// is a quantitative increase in the value of higher performing individuals.

void EvolutionaryAlgorithm::perform_my_linear_ranking_fitness_assignment(void)
{
   // Sorted evaluation vector

   int population_size = get_population_size();

   Vector<double> sorted_evaluation(population_size);

   sorted_evaluation = evaluation;

   std::sort(sorted_evaluation.begin(), sorted_evaluation.end(), std::less<double>());

   // Rank vector

   //Vector<int> rank(population_size);

   for(int i = 0; i < population_size; i++)
   {
      for(int j = 0; j < population_size; j++)
      {
         if(evaluation[j] == sorted_evaluation[i])
         {
            //rank[j] = population_size - i;
            rank[j] = i+1;
         }
      }
   }

   // Perform linear ranking fitness assignment

   for(int i = 0; i < population_size; i++)
   {
      fitness[i] = 2.0 - selective_pressure
      + 2.0*(selective_pressure - 1.0)*(rank[i] - 1.0)/(population_size - 1.0);

      if(!(fitness[i] > -1.0e99 && fitness[i] < 1.0e99))
      {
         std::cerr << "Flooe Error: EvolutionaryAlgorithm class." << std::endl
                   << "void perform_linear_ranking_fitness_assignment(void) method." << std::endl
                   << "Fitness of individual " << i << " is not a real number." << std::endl;

         exit(1);
      }
   }

   for(int i = 0; i < population_size; i++)
   {
      std::cout << std::endl << "Sorted_Evaluation[" << i << "]: " << sorted_evaluation[i] << "    Evaluation[" << i << "]: " << evaluation[i] << "    Rank: " << rank[i] << "    Fitness[" << i << "]: " << fitness[i] << std::endl;
   }
}

// void perform_roulette_wheel_selection(void) method

/// This metod performs selection with roulette wheel selection. It selects half of the individuals from the
/// population.
/// Results are stored in the selection vector.

void EvolutionaryAlgorithm::perform_roulette_wheel_selection(void)
{
   // Set selection vector to false

   selection.initialize(false);

   int population_size = get_population_size();

   int selected_individuals_number = population_size/2;

   // Cumulative fitness vector

   Vector<double> cumulative_fitness(population_size);

   cumulative_fitness[0] = fitness[0];

   for(int i = 1; i < population_size; i++)
   {
      cumulative_fitness[i] = cumulative_fitness[i-1] + fitness[i];
   }

   // Select individuals until the desired number of selections is obtained

   int selected_individuals_count = 0;

   if(elitism)
   {
      int best_individual_index = evaluation.calculate_minimal_index();

      selection[best_individual_index] = true;

      selected_individuals_count++;
   }

   do
   {
      // Random number between 0 and total cumulative fitness

      double random = (double)rand()/(RAND_MAX+1.0);

      double pointer = cumulative_fitness[population_size-1]*random;

      // Perform selection

      if(pointer < cumulative_fitness[0])
      {
         if(selection[0] == false)
         {
            selection[0] = true;
            selected_individuals_count++;
         }
      }

      for(int i = 1; i < population_size; i++)
      {
         if(pointer < cumulative_fitness[i] && pointer >= cumulative_fitness[i-1])
         {
            if(selection[i] == false)
            {
               selection[i] = true;
               selected_individuals_count++;
            }
         }
      }
   }while(selected_individuals_count != selected_individuals_number);

   // Control sentence

   if(selected_individuals_count != selected_individuals_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_roulette_wheel_selection(void) method." << std::endl
                << "Count number of selected individuals is not equal to number of selected individuals." << std::endl;

      exit(1);
   }
}


// Avinash Ranganath
// This method is similar to the roulette wheel selection method, but here the top n-ranked
// individuals of the population are selected explicitly, and the rest are selected through
// the roulette wheel process.

void EvolutionaryAlgorithm::perform_my_roulette_wheel_selection(void)
{
   // Set selection vector to false

   selection.initialize(false);

   int population_size = get_population_size();

   int selected_individuals_number = population_size * crossover_percentage;

   // Cumulative fitness vector

   Vector<double> cumulative_fitness(population_size);

   cumulative_fitness[0] = fitness[0];

   for(int i = 1; i < population_size; i++)
   {
      cumulative_fitness[i] = cumulative_fitness[i-1] + fitness[i];
   }

   // Select individuals until the desired number of selections is obtained

   int selected_individuals_count = 0;

   if(elitism)
   {
      //int best_individual_index = evaluation.calculate_minimal_index();
      int elite_population_size = population_size * (crossover_percentage * elitism_percentage);
      for(int i=population_size; i >= population_size-elite_population_size; i--)
      {
         for(int j=0; j<population_size; j++)
         {
            if(rank[j] == i)
            {
               selection[j] = true;
               selected_individuals_count++;
               break;
            }
         }
      }
   }

   do
   {
      // Random number between 0 and total cumulative fitness

      double random = (double)rand()/(RAND_MAX+1.0);

      double pointer = cumulative_fitness[population_size-1]*random;

      // Perform selection

      if(pointer < cumulative_fitness[0])
      {
         if(selection[0] == false)
         {
            selection[0] = true;
            selected_individuals_count++;
         }
      }

      for(int i = 1; i < population_size; i++)
      {
         if(pointer < cumulative_fitness[i] && pointer >= cumulative_fitness[i-1])
         {
            if(selection[i] == false)
            {
               selection[i] = true;
               selected_individuals_count++;
            }
         }
      }
   }while(selected_individuals_count != selected_individuals_number);

   // Control sentence

   if(selected_individuals_count != selected_individuals_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_roulette_wheel_selection(void) method." << std::endl
                << "Count number of selected individuals is not equal to number of selected individuals." << std::endl;

      exit(1);
   }

   std::cout << "Completed perform_my_roulette_wheel_selection()" << std::endl; //Debugger
/********************************************************************Debugger*******************************************************************/
  /*std::cout << std::endl << "roulette_wheel_selection" << std::endl;
  int above = 0, below = 0;
  for(int i=0; i<population_size; i++)
  {
     for(int j=0; j<population_size; j++)
     {
        if(rank[j] == i+1)
        {
           std::cout << "Rank: " << i+1 << " --> " << selection[j] << "    Cumulative Fitness: " << cumulative_fitness[j];
           if(selection[j] == true && i < population_size/2)
           {
              below++;
           }
           else if(selection[j] == true && i >= population_size/2)
           {
              above++;
           }
           break;
        }
     }
     std::cout << "    Cumulative Fitness[" << i << "]: " << cumulative_fitness[i] << std::endl;
  }
  std::cout << "Below = " << below << "    Above = " << above << std::endl;*/
/********************************************************************Debugger*******************************************************************/
}


// void perform_stochastic_universal_sampling_selection(void) method
//
/// This metod performs selection with stochastic universal sampling. It selects half of the individuals from the
/// population.
/// Results are stored in the selection vector.

void EvolutionaryAlgorithm::perform_stochastic_universal_sampling_selection(void)
{
   // Set selection vector to false

   selection.initialize(false);

   int population_size = get_population_size();

   int selected_individuals_number = population_size/2;

   Vector<double> cumulative_fitness(population_size);

   Vector<double> pointer(selected_individuals_number);

   // Cumulative fitness vector

   cumulative_fitness[0] = fitness[0];

   for(int i = 1; i < population_size; i++)
   {
      cumulative_fitness[i] = cumulative_fitness[i-1] + fitness[i];
   }


   // Pointer vector

   // Random number between 0 and totalCumulativeFitnees/(double)selected_individuals_number

   double random = (double)rand()/(RAND_MAX+1.0);

   pointer[0] = random
   *cumulative_fitness[population_size-1]/(double)selected_individuals_number;

   for(int i = 1; i < selected_individuals_number; i++)
   {
      pointer[i] = pointer[i-1]
      + cumulative_fitness[population_size-1]/(double)selected_individuals_number;
   }

   // Selection vector

   int selected_individuals_count = 0;

   if(pointer[0] <= cumulative_fitness[0])
   {
      selection[0] = true;
      selected_individuals_count++;
   }

   for(int i = 0; i < selected_individuals_number; i++)
   {
      for(int j = 1; j < population_size; j++)
      {
         if(pointer[i] <= cumulative_fitness[j] && pointer[i] > cumulative_fitness[j-1])
         {
            selection[j] = true;
            selected_individuals_count++;
         }
      }
   }

   // Number of selected individuals control sentence

   if(selected_individuals_count != selected_individuals_number)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_stochastic_universal_sampling_selection(void) method." << std::endl
                << "Count number of selected individuals is not equal to number of selected individuals." << std::endl;

      exit(1);
   }
}


// void perform_intermediate_recombination(void) method

/// This method performs inediate recombination between pairs of selected individuals to generate a new
/// population.
/// Each selected individual is to be recombined with two other selected individuals chosen at random.
/// Results are stored in the population matrix.

void EvolutionaryAlgorithm::perform_intermediate_recombination(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Matrix<double> new_population(population_size, parameters_number);

   int count = 0;
   for(int i = 0; i < population_size; i++)
   {
      if(selection[i] == true)
      count ++;
   }

   Vector<double> parent_1(parameters_number);
   Vector<double> parent_2(parameters_number);

   Vector<double> offspring(parameters_number);

   Matrix<int> recombination(population_size, 2);

   int offspring_pointer = 0;

   // Start recombination

   int new_population_size_count = 0;

   for(int i = 0; i < population_size; i++)
   {
      if(selection[i] == true)
      {
         // Set parent 1

         parent_1 = get_individual(i);

         // Generate 2 offspring with parent 1

         for(int j = 0; j < 2; j++)
         {
            // Choose parent 2 at random among selected individuals

            bool parent_2_candidate = false;

            do{
               // Integer random number beteen 0 and population size

               double random = (double)rand()/(RAND_MAX+1.0);

               int parent_2_candidate_index = (int)(population_size*random);

               // Check if candidate for parent 2 is ok

               if(selection[parent_2_candidate_index] == true && parent_2_candidate_index != i)
               {
                  parent_2_candidate = true;

                  recombination[new_population_size_count][0] = i;

                  recombination[new_population_size_count][1] = parent_2_candidate_index;

                  parent_2 = get_individual(parent_2_candidate_index);

                  // Perform inediate recombination between parent 1 and parent 2

                  for(int j = 0; j < parameters_number; j++)
                  {
                     // Choose the scaling factor to be a random number between
                     // -recombination_size and 1+recombination_size for each
                     // variable anew.

                     double random = (double)rand()/(RAND_MAX+1.0);

                     double scaling_factor = -1.0*recombination_size + (1.0 + recombination_size)*random;

                     offspring[j] = scaling_factor*parent_1[j] + (1.0 - scaling_factor)*parent_2[j];
                  }

                  // Add offspring to new_population matrix
                  new_population.set_row(new_population_size_count, offspring);
                  new_population_size_count++;
               }
            }while(parent_2_candidate != true);
         }
      }
   }

   // Count number of new individuals control sentence

   if(new_population_size_count != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_intermediate_recombination(void) method." << std::endl
                << "Count new population size is not equal to population size." << std::endl;

      exit(1);
   }

   // Set new population

   population = new_population;
}

// Avinash Ranganath
// This method is similar to intermediate recombination, but here instead of two offsprings per parent pair,
// a single offspring is created and along with the offspring, the primary parent is carried forward to the
// next generation.

void EvolutionaryAlgorithm::perform_my_intermediate_recombination(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Matrix<double> new_population(population_size, parameters_number);

   int count = 0;
   for(int i = 0; i < population_size; i++)
   {
      if(selection[i] == true)
      count ++;
   }

   Vector<double> parent_1(parameters_number);
   Vector<double> parent_2(parameters_number);

   Vector<double> offspring(parameters_number);

   Matrix<int> recombination(population_size, 2);

   int offspring_pointer = 0;

   // Start recombination

   int new_population_size_count = 0;

   for(int i = 0; i < population_size; i++)
   {
      if(selection[i] == true)
      {
         // Set parent 1

         parent_1 = get_individual(i);

         // Generate 1 offspring with parent 1

         for(int j = 0; j < 1; j++)
         {
            // Choose parent 2 at random among selected individuals

            bool parent_2_candidate = false;

            do{
               // Integer random number beteen 0 and population size

               double random = (double)rand()/(RAND_MAX+1.0);

               int parent_2_candidate_index = (int)(population_size*random);

               // Check if candidate for parent 2 is ok

               if(selection[parent_2_candidate_index] == true && parent_2_candidate_index != i)
               {
                  parent_2_candidate = true;

                  recombination[new_population_size_count][0] = i;

                  recombination[new_population_size_count][1] = parent_2_candidate_index;

                  parent_2 = get_individual(parent_2_candidate_index);

                  // Perform inediate recombination between parent 1 and parent 2

                  for(int j = 0; j < parameters_number; j++)
                  {
                     // Choose the scaling factor to be a random number between
                     // -recombination_size and 1+recombination_size for each
                     // variable anew.

                     double random = (double)rand()/(RAND_MAX+1.0);

                     double scaling_factor = -1.0*recombination_size + (1.0 + recombination_size)*random;

                     offspring[j] = scaling_factor*parent_1[j] + (1.0 - scaling_factor)*parent_2[j];
                  }

                  // Add offspring to new_population matrix
                  //new_population.set_row(new_population_size_count, offspring);

      // Replace a non selected member in the population with the offspring
                  for(int n = offspring_pointer; n < population_size; n++)
      {
         if(selection[n] == false)
         {
            new_population.set_row(n, offspring);
                        offspring_pointer = n+1;
      new_population_size_count++;
                        break;
         }
      }

      // Retain the first parent
                  new_population.set_row(i, parent_1);
                  new_population_size_count++;
               }
            }while(parent_2_candidate != true);
         }
      }
   }

   // Count number of new individuals control sentence

   if(new_population_size_count != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_intermediate_recombination(void) method." << std::endl
                << "Count new population size is not equal to population size." << std::endl;

      exit(1);
   }

   // Set new population

   population = new_population;
}


// Avinash Ranganath
// This method is similar to my intermediate recombination, but here instead of all the parents, only the
// elite [Top n ranked parents] parents are carried forward to the next generation.

void EvolutionaryAlgorithm::perform_my_intermediate_recombination_with_elitism(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Matrix<double> new_population(population_size, parameters_number);

   Vector<double> parent_1(parameters_number);
   Vector<double> parent_2(parameters_number);

   Vector<double> offspring(parameters_number);

   Matrix<int> recombination(population_size, 4);

   int crossover_population_size = population_size * crossover_percentage;
   Vector<int> parent_index(crossover_population_size);

   // Start recombination

#ifdef CROSSOVER_RANK_BASED_PRIORITY
   int n=0;
   for(int i=0; i<population_size; i++)
   {
      for(int j=0; j<population_size; j++)
      {
         if(rank[j] == population_size-i && selection[j] == true)
         {
            parent_index[n] = j;
            n++;
            break;
         }
      }
   }
#endif

   int new_population_size_count = 0;
   int elite_population_size = population_size * (crossover_percentage * elitism_percentage);

#ifdef CROSSOVER_RANK_BASED_PRIORITY
//--- Copying the elite members into the next generation without altering their genes
   for(int i=0; i < elite_population_size; i++)
   {
      new_population.set_row(i,get_individual(parent_index[i]));

      recombination[i][0] = parent_index[i];
      recombination[i][1] = parent_index[i];
      recombination[i][2] = rank[parent_index[i]];
      recombination[i][3] = rank[parent_index[i]];

      new_population_size_count++;
   }
#else
   for(int i=population_size; i > population_size - elite_population_size; i--)
   {
      for(int j=0; j<population_size; j++)
      {
         if(rank[j] == i && selection[j] == true)
         {
            new_population.set_row(new_population_size_count,get_individual(j));

            recombination[new_population_size_count][0] = j;
            recombination[new_population_size_count][1] = j;
            recombination[new_population_size_count][2] = rank[j];
      recombination[new_population_size_count][3] = rank[j];

      new_population_size_count++;
            break;
         }
         else if(rank[j] == i && selection[j] != true)
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_my_intermediate_recombination_with_elitism(void) method." << std::endl
                << "selection[j] != true --> Selection of an Elite member is False" << std::endl;

            exit(1);
         }
      }
   }
#endif

   int parent_1_candidate_index = 0;
   int index = 0;
   while(new_population_size_count < population_size)
   {
#ifdef CROSSOVER_RANK_BASED_PRIORITY
      if(index >= crossover_population_size)
      {
         index = 0;
      }
      parent_1_candidate_index = parent_index[index];
#else
      if(parent_1_candidate_index >= population_size)
      {
        parent_1_candidate_index = 0;
      }
#endif

      if(selection[parent_1_candidate_index] == true)
      {
         // Set parent 1

         parent_1 = get_individual(parent_1_candidate_index);

         // Generate 1 offspring with parent 1

         for(int j = 0; j < 1; j++)
         {
            // Choose parent 2 at random among selected individuals

            bool parent_2_candidate = false;

            do{
               // Integer random number beteen 0 and population size

               double random = (double)rand()/(RAND_MAX+1.0);

               int parent_2_candidate_index = (int)(population_size*random);

               // Check if candidate for parent 2 is ok

               if(selection[parent_2_candidate_index] == true && parent_2_candidate_index != parent_1_candidate_index)
               {
                  parent_2_candidate = true;

                  recombination[new_population_size_count][0] = parent_1_candidate_index;
                  recombination[new_population_size_count][1] = parent_2_candidate_index;
                  recombination[new_population_size_count][2] = rank[parent_1_candidate_index];
      recombination[new_population_size_count][3] = rank[parent_2_candidate_index];

                  parent_2 = get_individual(parent_2_candidate_index);

                  // Perform inediate recombination between parent 1 and parent 2

                  for(int j = 0; j < parameters_number; j++)
                  {
                     // Choose the scaling factor to be a random number between
                     // -recombination_size and 1+recombination_size for each
                     // variable anew.

                     double random = (double)rand()/(RAND_MAX+1.0);

                     double scaling_factor = -1.0*recombination_size + (1.0 + recombination_size)*random;

                     offspring[j] = scaling_factor*parent_1[j] + (1.0 - scaling_factor)*parent_2[j];
                  }

                  // Add offspring to new_population matrix
                  new_population.set_row(new_population_size_count, offspring);
                  new_population_size_count++;
               }
            }while(parent_2_candidate != true);
         }
      }
#ifdef CROSSOVER_RANK_BASED_PRIORITY
      index++;
#else
      parent_1_candidate_index++;
#endif
   }

   // Count number of new individuals control sentence

   if(new_population_size_count != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_intermediate_recombination(void) method." << std::endl
                << "Count new population size is not equal to population size." << std::endl;

      exit(1);
   }

   // Set new population

   population = new_population;

  std::cout << std::endl << "Parent Combination:" << std::endl;
  for(int i=0; i<population_size; i++)
  {
     std::cout << "Offsprint " << i << "    Parent 1: " << recombination[i][0] << "[" << recombination[i][2] << "]    Parent 2: " << recombination[i][1] << "[" << recombination[i][3] << "]" << std::endl;
  }
}


void EvolutionaryAlgorithm::perform_my_intermediate_recombination_with_elitism_and_evolution_strategy(void)
{
   int population_size = get_population_size();
   bool independent_parameter_in_range;

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();
   int independent_parameters_number = multilayer_perceptron_pointer->get_independent_parameters_number();
   int parameters_number = neural_parameters_number + independent_parameters_number;

   Matrix<double> new_population(population_size, parameters_number);

   Vector<double> parent_1(parameters_number);
   Vector<double> parent_2(parameters_number);

   Vector<double> offspring(parameters_number);

   Matrix<int> recombination(population_size, 4);

   int crossover_population_size = population_size * crossover_percentage;
   Vector<int> parent_index(crossover_population_size);

   std::cout << "Completed Initialization in perform_my_intermediate_recombination_with_elitism_and_ES()" << std::endl; //Debugger
   // Start recombination

//#ifdef CROSSOVER_RANK_BASED_PRIORITY
   int n=0;
   for(int i=0; i<population_size; i++)
   {
      for(int j=0; j<population_size; j++)
      {
         if(rank[j] == population_size-i && selection[j] == true)
         {
            parent_index[n] = j;
            n++;
            break;
         }
      }
   }
//#endif
   std::cout << "Completed parent_index in perform_my_intermediate_recombination_with_elitism_and_ES()" << std::endl; //Debugger

   int new_population_size_count = 0;
   int elite_population_size = population_size * (crossover_percentage * elitism_percentage);

//#ifdef CROSSOVER_RANK_BASED_PRIORITY
//--- Copying the elite members into the next generation without altering their genes
   for(int i=0; i < elite_population_size; i++)
   {
      new_population.set_row(i,get_individual(parent_index[i]));

      recombination[i][0] = parent_index[i];
      recombination[i][1] = parent_index[i];
      recombination[i][2] = rank[parent_index[i]];
      recombination[i][3] = rank[parent_index[i]];

      new_population_size_count++;
   }

//--- Copying the elite members into the next generation which will be mutated as Evolution Strategy
   for(int n=elite_population_size, i=0; n < elite_population_size*2; n++,i++)
   {
      new_population.set_row(n,get_individual(parent_index[i]));

      recombination[n][0] = parent_index[i];
      recombination[n][1] = parent_index[i];
      recombination[n][2] = rank[parent_index[i]];
      recombination[n][3] = rank[parent_index[i]];

      new_population_size_count++;
   }
      std::cout << "Completed copying Elite and ES population in perform_my_intermediate_recombination_with_elitism_and_ES()" << std::endl; //Debugger
//#else
/*   for(int i=population_size; i > population_size - elite_population_size; i--)
   {
      for(int j=0; j<population_size; j++)
      {
         if(rank[j] == i && selection[j] == true)
         {
            new_population.set_row(new_population_size_count,get_individual(j));

            recombination[new_population_size_count][0] = j;
            recombination[new_population_size_count][1] = j;
            recombination[new_population_size_count][2] = rank[j];
      recombination[new_population_size_count][3] = rank[j];

      new_population_size_count++;
            break;
         }
         else if(rank[j] == i && selection[j] != true)
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_my_intermediate_recombination_with_elitism(void) method." << std::endl
                << "selection[j] != true --> Selection of an Elite member is False" << std::endl;

            exit(1);
         }
      }
   }*/
//#endif

   int parent_1_candidate_index = 0;
   int index = elite_population_size;
   while(new_population_size_count < population_size)
   {
//#ifdef CROSSOVER_RANK_BASED_PRIORITY
      if(index >= crossover_population_size)
      {
         index = 0;
      }
      parent_1_candidate_index = parent_index[index];
//#else
/*      if(parent_1_candidate_index >= population_size)
      {
        parent_1_candidate_index = 0;
      }*/
//#endif

      if(selection[parent_1_candidate_index] == true)
      {
         // Set parent 1

         parent_1 = get_individual(parent_1_candidate_index);

         // Generate 1 offspring with parent 1

         for(int i=0; i<1; i++)
         {
            // Choose parent 2 at random among selected individuals

            bool parent_2_candidate = false;

            do{
               // Integer random number beteen 0 and population size

               double random = (double)rand()/(RAND_MAX+1.0);

               int parent_2_candidate_index = (int)(population_size*random);

               // Check if candidate for parent 2 is ok

               if(selection[parent_2_candidate_index] == true && parent_2_candidate_index != parent_1_candidate_index)
               {
                  parent_2_candidate = true;

                  recombination[new_population_size_count][0] = parent_1_candidate_index;
                  recombination[new_population_size_count][1] = parent_2_candidate_index;
                  recombination[new_population_size_count][2] = rank[parent_1_candidate_index];
                  recombination[new_population_size_count][3] = rank[parent_2_candidate_index];

                  parent_2 = get_individual(parent_2_candidate_index);

                  // Perform inediate recombination between parent 1 and parent 2

                  for(int j = 0; j < parameters_number; j++)
                  {
                     do
                     {
                        //independent_parameter_in_range = false;

                        // Choose the scaling factor to be a random number between
                        // -recombination_size and 1+recombination_size for each
                        // variable anew.

                        double random = (double)rand()/(RAND_MAX+1.0);

                        double scaling_factor = -1.0*recombination_size + (1.0 + recombination_size)*random;

                        offspring[j] = scaling_factor*parent_1[j] + (1.0 - scaling_factor)*parent_2[j];

                        //if(independent_parameters_number > 0 && i >= neural_parameters_number) //Check if the parameter is neural or independent // BUG_Fixed: 'i' should be 'j'
                        if(independent_parameters_number > 0 && j >= neural_parameters_number) //Check if the parameter is neural or independent
                        {
                           /*double minimum = multilayer_perceptron_pointer->get_independent_parameter_minimum(j);
                           double maximum = multilayer_perceptron_pointer->get_independent_parameter_maximum(j);*/ // BUG_Fixed: Pointing to wrong index of independent_parameter_maximum and independent_parameter_maximum vectors.

                           double minimum = multilayer_perceptron_pointer->get_independent_parameter_minimum(j-neural_parameters_number);
                           double maximum = multilayer_perceptron_pointer->get_independent_parameter_maximum(j-neural_parameters_number);


                           if(offspring[j] >= minimum && offspring[j] <= maximum) //Check if the independent parameter is within range
                           {
                              independent_parameter_in_range = true;
                           }
                           else
                           {
                              independent_parameter_in_range = false;
                              std::cout << std::endl << "Independent Parameter: " << j << " Out of range: " << offspring[j] << ".  Child No: " << new_population_size_count << std::endl;
                           }
                        }
                        else
                        {
                           independent_parameter_in_range = true;
                        }
                     }while(!independent_parameter_in_range);
                  }

                  // Add offspring to new_population matrix
                  new_population.set_row(new_population_size_count, offspring);
                  new_population_size_count++;
               }
            }while(parent_2_candidate != true);
         }
      }
//#ifdef CROSSOVER_RANK_BASED_PRIORITY
      index++;
//#else
//      parent_1_candidate_index++;
//#endif
   }

   // Count number of new individuals control sentence

   if(new_population_size_count != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_intermediate_recombination(void) method." << std::endl
                << "Count new population size is not equal to population size." << std::endl;

      exit(1);
   }

   // Set new population

   population = new_population;

  std::cout << std::endl << "Parent Combination:" << std::endl;
  for(int i=0; i<population_size; i++)
  {
     std::cout << "Offsprint " << i << "    Parent 1: " << recombination[i][0] << "[" << recombination[i][2] << "]    Parent 2: " << recombination[i][1] << "[" << recombination[i][3] << "]" << std::endl;
  }
}


// void perform_line_recombination(void) method

/// This method performs line recombination between pairs of selected individuals to generate a new population.
/// Each selected individual is to be recombined with two other selected individuals chosen at random.
/// Results are stored in the population matrix.

void EvolutionaryAlgorithm::perform_line_recombination(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Matrix<double> new_population(population_size, parameters_number);

   Vector<double> parent_1(parameters_number);
   Vector<double> parent_2(parameters_number);

   Vector<double> offspring(parameters_number);
   Vector<double> parent_1_term(parameters_number);
   Vector<double> parent_2_term(parameters_number);

   Matrix<int> recombination(population_size, 2);

   // Start recombination

   int new_population_size_count = 0;

   for(int i = 0; i < population_size; i++)
   {
      if(selection[i] == true)
      {
         // Set parent 1

         parent_1 = get_individual(i);

         // Generate 2 offspring with parent 1

         for(int j = 0; j < 2; j++)
         {
            // Choose parent 2 at random among selected individuals

            bool parent_2_candidate = false;

            do
            {
               // Integer random number beteen 0 and population size

               double random = (double)rand()/(RAND_MAX + 1.0);

               int parent_2_candidate_index = (int)(population_size*random);

               // Check if candidate for parent 2 is ok

               if(selection[parent_2_candidate_index] == true && parent_2_candidate_index != i)
               {
                  parent_2_candidate = true;

                  recombination[new_population_size_count][0] = i;
                  recombination[new_population_size_count][1] = parent_2_candidate_index;

                  parent_2 = get_individual(parent_2_candidate_index);

                  // Perform inediate recombination between parent 1
                  // and parent 2

                  // Choose the scaling factor to be a random number between
                  // -recombination_size and 1+recombination_size for all
                  // variables.

                  double random = (double)rand()/(RAND_MAX+1.0);

                  double scaling_factor = -1.0*recombination_size
                  + (1.0 + recombination_size)*random;

                  parent_1_term = parent_1*scaling_factor;
                  parent_2_term = parent_2*(1.0 - scaling_factor);

                  offspring = parent_1_term + parent_2_term;

                  // Add offspring to new_population matrix

                  new_population.set_row(new_population_size_count, offspring);

                  new_population_size_count++;
               }
            }while(parent_2_candidate == false);
         }
      }
   }

   // Count new population size control sentence

   if(new_population_size_count != population_size)
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void perform_line_recombination(void) method." << std::endl
                << "Count new population size is not equal to population size." << std::endl;

      exit(1);
   }

   // Set new population

   population = new_population;
}


// void perform_normal_mutation(void) method

/// This method performs normal mutation to all individuals in order to generate a new population.
/// Results are stored in the population matrix.

void EvolutionaryAlgorithm::perform_normal_mutation(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> individual(parameters_number);

   for(int i = 0; i < population_size; i++)
   {
      individual = get_individual(i);

      for(int j = 0; j < parameters_number; j++)
      {
         // Random number between 0 and 1

         double pointer = calculate_random_uniform(0.0, 1.0);

         if(pointer < mutation_rate)
         {
            individual[j] += calculate_random_normal(0.0, mutation_range);
         }
      }

      set_individual(i, individual);
   }
}

// Avinash Ranganath
// This method is similar to Normal Mutation method, but the mutation is performed only on the newly created
// offspring population
void EvolutionaryAlgorithm::perform_my_normal_mutation(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> individual(parameters_number);

   int elite_population_size = population_size * (crossover_percentage * elitism_percentage);

   for(int i = elite_population_size; i < population_size; i++)
   {
      individual = get_individual(i);

      for(int j = 0; j < parameters_number; j++)
      {
         // Random number between 0 and 1

         double pointer = calculate_random_uniform(0.0, 1.0);

         if(pointer < mutation_rate)
         {
            individual[j] += calculate_random_normal(0.0, mutation_range);
         }
      }
      set_individual(i, individual);
   }
}


// Avinash Ranganath
// This method is similar to My Normal Mutation method, but here a special mutation [With higher rate and range] is performed
// on a copy of the elite members, and the regular mutation is performed on the newly created offspring population.
void EvolutionaryAlgorithm::perform_my_normal_mutation_with_ES(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   //int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   unsigned int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();
   unsigned int independent_parameters_number = multilayer_perceptron_pointer->get_independent_parameters_number();
   unsigned int parameters_number = neural_parameters_number + independent_parameters_number;

   Vector<double> individual(parameters_number);
   double gene;

   int elite_population_size = population_size * (crossover_percentage * elitism_percentage);

   bool independent_parameter_in_range;

   for(int i = elite_population_size; i < elite_population_size*2; i++)
   {
      individual = get_individual(i);

      for(int j = 0; j < parameters_number; j++)
      {
         // Random number between 0 and 1
         double pointer = calculate_random_uniform(0.0, 1.0);

         if(pointer < mutation_rate_for_ES)
         {
            std::string independent_parameter_name = "No_Name";
            if(independent_parameters_number > 0 && j >= neural_parameters_number) //Check if the parameter is neural or independent
            {
               independent_parameter_name = multilayer_perceptron_pointer->get_independent_parameter_name(j-neural_parameters_number);
            }

            //-- Omit mutation for indemendent parameter 'Sinusoidal_Frequency' and 'Sine_Frequency', since it ranges between 0 and 1.0
            if(independent_parameter_name != "Sinusoidal_Frequency" && independent_parameter_name != "Sine_Frequency")
            {
               do
               {
                  //-- Mutate gene [ES]
                  //individual[j] += calculate_random_normal(0.0, mutation_range_for_ES);
                  gene = individual[j];
                  gene += calculate_random_normal(0.0, mutation_range_for_ES);

                  if(independent_parameters_number > 0 && j >= neural_parameters_number) //Check if the parameter is neural or independent
                  {
                     double minimum = multilayer_perceptron_pointer->get_independent_parameter_minimum(j-neural_parameters_number);
                     double maximum = multilayer_perceptron_pointer->get_independent_parameter_maximum(j-neural_parameters_number);

                     if(individual[j] >= minimum && individual[j] <= maximum) //Check if the independent parameter is within range
                     {
                        independent_parameter_in_range = true;
                     }
                     else
                     {
                        independent_parameter_in_range = false;
                        std::cout << std::endl << "Mutation_ES: Independent Parameter: " << j << " Out of range: " << individual[j] << ".  Child No: " << i << std::endl;
                     }
                  }
                  else
                  {
                     independent_parameter_in_range = true;
                  }
               }while(!independent_parameter_in_range);
               individual[j] = gene;
            }
         }
      }
      set_individual(i, individual);
   }

   for(int i = elite_population_size*2; i < population_size; i++)
   {
      individual = get_individual(i);

      for(int j = 0; j < parameters_number; j++)
      {
         // Random number between 0 and 1

         double pointer = calculate_random_uniform(0.0, 1.0);

         if(pointer < mutation_rate)
         {
            std::string independent_parameter_name = "No_Name";
            if(independent_parameters_number > 0 && j >= neural_parameters_number) //Check if the parameter is neural or independent
            {
               independent_parameter_name = multilayer_perceptron_pointer->get_independent_parameter_name(j-neural_parameters_number);
            }

            //-- Omit mutation for indemendent parameter 'Sinusoidal_Frequency' and 'Sine_Frequency', since it ranges between 0 and 1.0
            if(independent_parameter_name != "Sinusoidal_Frequency" && independent_parameter_name != "Sine_Frequency")
            {
               do
               {
                  //-- Mutate gene [ES]
                  //individual[j] += calculate_random_normal(0.0, mutation_range);
                  gene = individual[j];
                  gene += calculate_random_normal(0.0, mutation_range);

                  if(independent_parameters_number > 0 && j >= neural_parameters_number) //Check if the parameter is neural or independent
                  {
                     double minimum = multilayer_perceptron_pointer->get_independent_parameter_minimum(j-neural_parameters_number);
                     double maximum = multilayer_perceptron_pointer->get_independent_parameter_maximum(j-neural_parameters_number);

                     if(individual[j] >= minimum && individual[j] <= maximum) //Check if the independent parameter is within range
                     {
                        independent_parameter_in_range = true;
                     }
                     else
                     {
                        independent_parameter_in_range = false;
                        std::cout << std::endl << "Mutation_Offspring: Independent Parameter: " << j << " Out of range: " << individual[j] << ".  Child No: " << i << std::endl;
                     }
                  }
                  else
                  {
                     independent_parameter_in_range = true;
                  }
               }while(!independent_parameter_in_range);
               individual[j] = gene;
            }
         }
      }
      set_individual(i, individual);
   }
}


// void perform_uniform_mutation(void) method

/// This method performs uniform mutation to all individuals in order to generate a new population.
/// Results are stored in the population matrix.

void EvolutionaryAlgorithm::perform_uniform_mutation(void)
{
   int population_size = get_population_size();

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> individual(parameters_number, 0.0);

   for(int i = 0; i < population_size; i++)
   {
      individual = get_individual(i);

      for(int j = 0; j < parameters_number; j++)
      {
         // random number between 0 and 1

         double pointer = (double)rand()/(RAND_MAX+1.0);

         if(pointer < mutation_rate)
         {
            // random number between 0 and 1

            double random = (double)rand()/(RAND_MAX+1.0);

            double uniformlyDistributedRandomNumber
            = (-1.0 + 2.0*random)*mutation_range;

            individual[j] += uniformlyDistributedRandomNumber;
         }
      }

      set_individual(i, individual);
   }
}


// void train(void) method

/// This method trains a multilayer perceptron with an associated
/// objective function according to the evolutionary algorithm.
/// Training occurs according to the training operators and their related
/// parameters.

void EvolutionaryAlgorithm::train(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG


   if(objective_functional_pointer == NULL)
   {
      std::cout << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void train(void) method." << std::endl
                << "Pointer to objective functional object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   if(display)
   {
      std::cout << "Training with the evolutionary algorithm..." << std::endl;
   }

   // Population stuff

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   Vector<double> population_norm;

   double mean_norm;
   double standard_deviation_norm;

   Vector<double> best_individual;
   double best_norm = 0.0;

   // Objective functional stuff

   double best_evaluation = 0;
   double worst_evaluation = 10;

   // Training algorithm stuff

   time_t beginning_time, current_time;
   time(&beginning_time);
   double elapsed_time;

   bool stop_training = false;

   resize_training_history(maximum_generations_number+1);    // Main loop

   for(int generation = 1; generation <= maximum_generations_number; generation++)
   {
      // Population stuff

      if(reserve_population_history)
      {
         population_history[generation] = population;
      }

      population_norm = calculate_population_norm();

      // Mean norm

      mean_norm = population_norm.calculate_mean();

      if(reserve_mean_norm_history)
      {
         mean_norm_history[generation] = mean_norm;
      }

      // Standard deviation of norm

      standard_deviation_norm = population_norm.calculate_standard_deviation();

      if(reserve_standard_deviation_norm_history)
      {
         standard_deviation_norm_history[generation] = standard_deviation_norm;
      }

      evaluate_population(generation);  // Should be reverted
      //evaluate_population();

      int population_size = get_population_size();

      for(int i = 0; i < population_size; i++)
      {
         if(evaluation[i] > best_evaluation)
         {
            best_individual = get_individual(i);

            best_norm = best_individual.calculate_norm();

            best_evaluation = evaluation[i];
         }

         if(evaluation[i] < worst_evaluation)
         {
            worst_evaluation = evaluation[i];
         }
      }

      // Best individual

      if(reserve_best_individual_history)
      {
         best_individual_history[generation] = best_individual;
      }

      // Best individual norm

      if(reserve_best_norm_history)
      {
         best_norm_history[generation] = best_norm;
      }

      // Mean evaluation

      double mean_evaluation = evaluation.calculate_mean();

      if(reserve_mean_evaluation_history)
      {
         mean_evaluation_history[generation] = mean_evaluation;
      }

      // Standard deviation of evaluation

      double standard_deviation_evaluation = evaluation.calculate_standard_deviation();

      if(reserve_standard_deviation_evaluation_history)
      {
         standard_deviation_evaluation_history[generation] = standard_deviation_evaluation;
      }

      // Best individual evaluation

      if(reserve_best_evaluation_history)
      {
         best_evaluation_history[generation] = best_evaluation;
      }

      // Elapsed time

      time(&current_time);
      elapsed_time = difftime(current_time, beginning_time);

      if(reserve_elapsed_time_history)
      {
         elapsed_time_history[generation] = elapsed_time;


      }

      // Training history multilayer perceptron

      if(reserve_population_history)
      {
         population_history[generation] = population;
      }

      if(reserve_best_individual_history)
      {
         best_individual_history[generation] = best_individual;
      }

      if(reserve_mean_norm_history)
      {
         mean_norm_history[generation] = mean_norm;
      }

      if(reserve_standard_deviation_norm_history)
      {
         standard_deviation_norm_history[generation] = standard_deviation_norm;
      }

      if(reserve_best_norm_history)
      {
         best_norm_history[generation] = best_norm;
      }

      // Training history training algorithm

      if(reserve_mean_evaluation_history)
      {
         mean_evaluation_history[generation] = mean_evaluation;
      }

      if(reserve_standard_deviation_evaluation_history)
      {
         standard_deviation_evaluation_history[generation] = standard_deviation_evaluation;
      }

      if(reserve_best_evaluation_history)
      {
         best_evaluation_history[generation] = best_evaluation;
      }

      if(reserve_elapsed_time_history)
      {
         elapsed_time_history[generation] = elapsed_time;
      }

      // Stopping criteria

      if(best_evaluation <= evaluation_goal)
      {
         if(display)
         {
            std::cout << "Generation " << generation << ": Evaluation goal reached." << std::endl;

            objective_functional_pointer->print_information();
         }

     stop_training = true;
      }

      if(mean_evaluation <= mean_evaluation_goal)
      {
         if(display)
         {
            std::cout << "Generation " << generation << ": Mean evaluation goal reached." << std::endl;
         }

     stop_training = true;
      }

      if(standard_deviation_evaluation <= standard_deviation_evaluation_goal)
      {
         if(display)
         {
            std::cout << "Generation " << generation << ": Standard deviation of evaluation goal reached." << std::endl;
         }

     stop_training = true;
      }

      else if(elapsed_time >= maximum_time)
      {
         if(display)
         {
            std::cout << "Generation " << generation << ": Maximum training time reached." << std::endl;
         }

     stop_training = true;
      }

      else if(generation == maximum_generations_number)
      {
         if(display)
         {
            std::cout << "Generation " << generation << ": Maximum number of generations reached." << std::endl;
         }

         break;
      }

      if(stop_training)
      {

         if(display)
     {
            std::cout << "Mean norm: " << mean_norm << std::endl;
            std::cout << "Standard deviation of norm: " << standard_deviation_norm << std::endl;
            std::cout << "Best norm: " << best_norm << std::endl;

            std::cout << "Mean evaluation: " << mean_evaluation << std::endl;
            std::cout << "Standard deviation of evaluation: " << standard_deviation_evaluation << std::endl;
            std::cout << "Best evaluation: " << best_evaluation << std::endl;

            std::cout << "Elapsed time: " << elapsed_time << ";" << std::endl;

            objective_functional_pointer->print_information();

            resize_training_history(generation+1);
     }

         break;
    }
      else if(display && generation % display_period == 0)
      {
         std::cout << "Generation " << generation << "; " << std::endl;

         std::cout << "Mean norm: " << mean_norm << std::endl;
         std::cout << "Standard deviation of norm: " << standard_deviation_norm << std::endl;
         std::cout << "Best norm: " << best_norm << std::endl;

         std::cout << "Mean evaluation: " << mean_evaluation << std::endl;
         std::cout << "Standard deviation of evaluation: " << standard_deviation_evaluation << std::endl;
         std::cout << "Best evaluation: " << best_evaluation << std::endl;

         std::cout << "Elapsed time: " << elapsed_time << ";" << std::endl;

         objective_functional_pointer->print_information();

         objective_functional_pointer->print_information();
      }

      if(fitness_graph_history)
      {
         fitness_graph_file->write(generation, best_evaluation, mean_evaluation, worst_evaluation);
      }

      best_evaluation = 0;
      worst_evaluation = 10;

      // Set new parameters

      multilayer_perceptron_pointer->set_parameters(best_individual);

      // Update stuff

      selection.initialize(false);

      evolve_population(generation);
   }
}


// std::string to_XML(void) method

/// This method prints to the screen the members of the evolutionary algorithm object.
///
/// Training operators:
/// <ul>
/// <li> Fitness assignment method.
/// <li> Selection method.
/// <li> Recombination method.
/// <li> Mutation method.
/// </ul>
///
/// Training parameters:
/// <ul>
/// <li> Population size.
/// <li> Selective pressure.
/// <li> Recombination size.
/// <li> Mutation rate.
/// <li> Mutation range.
/// </ul>
///
/// Stopping criteria:
/// <ul>
/// <li> Evaluation goal.
/// <li> Mean evaluation goal.
/// <li> Standard deviation of evaluation goal.
/// <li> Maximum time.
/// <li> Maximum number of generations.
/// </ul>
///
/// User stuff:
/// <ul>
/// <li> Display.
/// <li> Display period.
/// <li> Reserve elapsed time.
/// <li> Reserve mean norm history.

/// <li> Reserve standard deviation of norm history.
/// <li> Reserve best norm history.
/// <li> Reserve mean evaluation history.
/// <li> Reserve standard deviation of evaluation history.
/// <li> Reserve best evaluation history.
/// </ul>
///
/// Population matrix.

std::string EvolutionaryAlgorithm::to_XML(bool show_declaration)
{
   std::stringstream buffer;    int parameters_number = 0;

   if(objective_functional_pointer != NULL)
   {
      MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

      if(multilayer_perceptron_pointer != NULL)
      {
         parameters_number = multilayer_perceptron_pointer->get_parameters_number();
      }
   }

   int population_size = get_population_size();

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='EvolutionaryAlgorithm'>" << std::endl;
   }

   // Training operators

   buffer << "<PopulationSize>" << std::endl
          << population_size << std::endl
          << "</PopulationSize>" << std::endl;

   buffer << "<ParametersNumber>" << std::endl
          << parameters_number << std::endl
          << "</ParametersNumber>" << std::endl;

   // Training operators

   // Fitness assingment method

   buffer << "<FitnessAssignmentMethod>" << std::endl
          << get_fitness_assignment_method_name() << std::endl
          << "</FitnessAssignmentMethod>" << std::endl;

   // Selection method

   buffer << "<SelectionMethod>" << std::endl
          << get_selection_method_name() << std::endl
          << "</SelectionMethod>" << std::endl;

   // Recombination method

   buffer << "<RecombinationMethod>" << std::endl
          << get_recombination_method_name() << std::endl
          << "</RecombinationMethod>" << std::endl;

   // Mutation method

   buffer << "<MutationMethod>" << std::endl
          << get_mutation_method_name() << std::endl
          << "</MutationMethod>" << std::endl;

   // Training parameters

   buffer << "<Elitism>" << std::endl
          << elitism << std::endl
          << "</Elitism>" << std::endl;

   buffer << "<SelectivePressure>" << std::endl
          << selective_pressure << std::endl
          << "</SelectivePressure>" << std::endl;

   buffer << "<RecombinationSize>" << std::endl
          << recombination_size << std::endl
          << "</RecombinationSize>" << std::endl;

   buffer << "<MutationRate>" << std::endl
          << mutation_rate << std::endl
          << "</MutationRate>" << std::endl;

   buffer << "<MutationRange>" << std::endl
          << mutation_range << std::endl
          << "</MutationRange>" << std::endl;

   // Stopping criteria

   buffer << "<EvaluationGoal>" << std::endl
          << evaluation_goal << std::endl
          << "</EvaluationGoal>" << std::endl;

   buffer << "<MeanEvaluationGoal>" << std::endl
          << mean_evaluation_goal << std::endl
          << "</MeanEvaluationGoal>" << std::endl;

   buffer << "<StandardDeviationEvaluationGoal>" << std::endl
          << standard_deviation_evaluation_goal << std::endl
          << "</StandardDeviationEvaluationGoal>" << std::endl;

   buffer << "<MaximumGenerationsNumber>" << std::endl
          << maximum_generations_number << std::endl
          << "</MaximumGenerationsNumber>" << std::endl;

   buffer << "<MaximumTime>" << std::endl
          << maximum_time << std::endl
          << "</MaximumTime>" << std::endl;

   // User stuff

   buffer << "<ReservePopulationHistory>" << std::endl
          << reserve_population_history << std::endl
          << "</ReservePopulationHistory>" << std::endl;

   buffer << "<ReserveBestIndividualHistory>" << std::endl
          << reserve_best_individual_history << std::endl
          << "</ReserveBestIndividualHistory>" << std::endl;

   buffer << "<ReserveMeanNormHistory>" << std::endl
          << reserve_mean_norm_history << std::endl
          << "</ReserveMeanNormHistory>" << std::endl;

   buffer << "<ReserveStandardDeviationNormHistory>" << std::endl
          << reserve_standard_deviation_norm_history << std::endl
          << "</ReserveStandardDeviationNormHistory>" << std::endl;

   buffer << "<ReserveBestNormHistory>" << std::endl
          << reserve_best_norm_history << std::endl
          << "</ReserveBestNormHistory>" << std::endl;

   buffer << "<ReserveMeanEvaluationHistory>" << std::endl
          << reserve_mean_evaluation_history << std::endl
          << "</ReserveMeanEvaluationHistory>" << std::endl;

   buffer << "<ReserveStandardDeviationEvaluationHistory>" << std::endl
          << reserve_standard_deviation_evaluation_history << std::endl
          << "</ReserveStandardDeviationEvaluationHistory>" << std::endl;

   buffer << "<ReserveBestEvaluationHistory>" << std::endl
          << reserve_best_evaluation_history << std::endl
          << "</ReserveBestEvaluationHistory>" << std::endl;

   buffer << "<ReserveElapsedTimeHistory>" << std::endl
          << reserve_elapsed_time_history << std::endl
          << "</ReserveElapsedTimeHistory>" << std::endl;

   buffer << "<Display>" << std::endl
          << display << std::endl
          << "</Display>" << std::endl;

   buffer << "<DisplayPeriod>" << std::endl
          << display_period << std::endl
          << "</DisplayPeriod>" << std::endl;

   buffer << "<Population>" << std::endl;

   if(population_size != 0 && parameters_number != 0)
   {
      buffer << population;
   }

   buffer << "</Population>" << std::endl;

   return(buffer.str());
}


// Avinash Ranganath
// void save_best_member(int,int)

// This method saves the gene of the member whoes index is passed as
// an argument.

/*void EvolutionaryAlgorithm::save_member(int gen, int elite_size)
{
   std::cout << "Entered function save_member(int, int)" << std::endl; //Debugger
   elite_population_file.open(elite_population_file_name.c_str(), fstream::in | fstream::out);

   if(!elite_population_file.is_open())
   {
      std::cerr << std::endl
                << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void save_member(int,int) method." << std::endl
                << "Cannot open elite population data file."  << std::endl
                << std::endl;

      exit(1);
   }
   else
   {
      if(display)
      {
         std::cout << std::endl
                   << "Saving elite members to gene file..." << std::endl;
      }
   }

   std::cout << "File opened in save_member(int, int)" << std::endl; //Debugger

   std::string word;
   do
   {
      elite_population_file >> word;
   }while(word != "</Gene>");
   elite_population_file.seekp (-27, ios::end);

   Vector<double> elite_individual; //Elite individual of the current generation to be saved
   Vector<double> elite_member; //Elite member previously saved in the file.
   int elite_population_size = elite_population_gene.get_rows_number();
   bool elite_member_exist = false;
   int population_size = get_population_size();

   for(int i=0; i<elite_size; i++)
   {
      for(int j=0; j<population_size; j++)
      {
         if(rank[j] == population_size-i)
         {
            elite_individual = get_individual(j);
            for(int k=elite_population_size-1; k>=0; k--)
            {
               elite_member = elite_population_gene.get_row(k);
               if(elite_individual == elite_member)
               {
                  elite_member_exist = true;
                  break;
               }
            }
            if(!elite_member_exist)
            {
               elite_population_gene.add_row(elite_individual);

               elite_population_file << "Generation_" << gen << ":" << std::endl;
               elite_population_file << elite_individual << std::endl;
               elite_population_file << std::endl;
            }
            elite_member_exist = false;
            break;
         }
      }
   }
   elite_population_file << "</Gene>" << std::endl;
   elite_population_file << std::endl << "</CubeRevolution>" << std::endl;

   elite_population_file.close();
}*/


void EvolutionaryAlgorithm::save_member(int generation)
{
   Vector<double> elite_individual; //Elite individual of the current generation to be saved
   Vector<double> elite_member; //Elite member previously saved in the file.
   int elite_population_size = elite_population_gene.get_rows_number();
   bool elite_member_exist = false;
   int population_size = get_population_size();

   for(int j=0; j<population_size; j++)
   {
      if(rank[j] == population_size)
      {
         elite_individual = get_individual(j);
         for(int k=elite_population_size-1; k>=0; k--)
         {
            elite_member = elite_population_gene.get_row(k);
            if(elite_individual == elite_member)
            {
               elite_member_exist = true;
               break;
            }
         }
         if(!elite_member_exist)
         {
            elite_population_gene.add_row(elite_individual);

            /*std::vector<double> elite_gene;
            for(int i=0; i<elite_individual.get_size(); i++)
            {
              elite_gene.push_back(elite_individual[i]);
            }*/
            elite_population_file->save_gene(generation, elite_individual);
         }
         elite_member_exist = false;
         break;
      }
   }
}


// void load(const char*) method

/// This method loads a evolutionary algorithm object from a XML-type file.
/// Please mind about the file format, wich is specified in the User's Guide.
///
/// Training operators:
/// <ul>
/// <li> Fitness assignment method.
/// <li> Selection method.
/// <li> Recombination method.
/// <li> Mutation method.
/// </ul>
///
/// Training parameters:
/// <ul>
/// <li> Population size.
/// <li> Selective pressure.
/// <li> Recombination size.
/// <li> Mutation rate.
/// <li> Mutation range.
/// </ul>
///
/// Stopping criteria:
/// <ul>
/// <li> Evaluation goal.
/// <li> Mean evaluation goal.
/// <li> Standard deviation of evaluation goal.
/// <li> Maximum time.
/// <li> Maximum number of generations.
/// </ul>
///
/// User stuff:
/// <ul>
/// <li> Display.
/// <li> Display period.
/// <li> Reserve elapsed time history.
/// <li> Reserve mean norm history.
/// <li> Reserve standard deviation of norm history.
/// <li> Reserve best norm history.
/// <li> Reserve mean evaluation history.
/// <li> Reserve standard deviation of evaluation history.
/// <li> Reserve best evaluation history.
/// </ul>
///
/// @param filename Filename.

void EvolutionaryAlgorithm::load(const char* filename)
{
   // File

   std::fstream file;

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open evolutionary algorithm object XML-type file."  << std::endl;

      exit(1);
   }

   // Load new number of individuals and new number of parameters form file

   std::string line;
   std::string word;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='EvolutionaryAlgorithm'>")
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void load(const char*) method." << std::endl
        << "Unknown file declaration: " << line << std::endl;

      exit(1);
   }

   // Population size

   file >> word;

   if(word != "<PopulationSize>")
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void load(const char*) method." << std::endl
            << "Unknown population size begin tag: " << word << std::endl;

      exit(1);
   }

   int new_population_size;
   file >> new_population_size;

   file >> word;

   if(word != "</PopulationSize>")
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void load(const char*) method." << std::endl
              << "Unknown population size end tag: " << word << std::endl;

      exit(1);
   }

   // Parameters number

   file >> word;

   if(word != "<ParametersNumber>")
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void load(const char*) method." << std::endl
            << "Unknown parameters number begin tag: " << word << std::endl;

      exit(1);
   }

   int new_parameters_number;
   file >> new_parameters_number;

   file >> word;

   if(word != "</ParametersNumber>")
   {
      std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                << "void load(const char*) method." << std::endl
              << "Unknown population size end tag: " << word << std::endl;

      exit(1);
   }


   while(!file.eof())
   {
      file >> word;

      // Training operators

      if(word == "<FitnessAssignmentMethod>")
      {
       std::string new_fitness_assignment_method_name;
     file >> new_fitness_assignment_method_name;
         set_fitness_assignment_method(new_fitness_assignment_method_name);

         file >> word;

         if(word != "</FitnessAssignmentMethod>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown fitness assignment method end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<SelectionMethod>")
      {
       std::string new_selection_method_name;
     file >> new_selection_method_name;
         set_selection_method(new_selection_method_name);

         file >> word;

         if(word != "</SelectionMethod>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown selection method end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<RecombinationMethod>")
      {
       std::string new_recombination_method_name;
     file >> new_recombination_method_name;
         set_recombination_method(new_recombination_method_name);

         file >> word;

         if(word != "</RecombinationMethod>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown recombination method end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<MutationMethod>")
      {
       std::string new_mutation_method_name;
     file >> new_mutation_method_name;
         set_mutation_method(new_mutation_method_name);

         file >> word;

         if(word != "</MutationMethod>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown mutation method end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<Elitism>")
      {
       bool new_elitism;
     file >> new_elitism;
         set_elitism(new_elitism);

         file >> word;

         if(word != "</Elitism>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown elitism end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<SelectivePressure>")
      {
       double new_selective_pressure;
     file >> new_selective_pressure;
         set_selective_pressure(new_selective_pressure);

         file >> word;

         if(word != "</SelectivePressure>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown selective pressure end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<RecombinationSize>")
      {
       double new_recombination_size;
     file >> new_recombination_size;
         set_recombination_size(new_recombination_size);

         file >> word;

         if(word != "</RecombinationSize>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown recombination size end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<MutationRate>")
      {
       double new_mutation_rate;
     file >> new_mutation_rate;
         set_mutation_rate(new_mutation_rate);

         file >> word;

         if(word != "</MutationRate>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown mutation rate end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<MutationRange>")
      {
       double new_mutation_range;
     file >> new_mutation_range;
         set_mutation_range(new_mutation_range);

         file >> word;

         if(word != "</MutationRange>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown mutation range end tag: " << word << std::endl;

            exit(1);
         }
      }


      else if(word == "<EvaluationGoal>")
      {
       double new_evaluation_goal;
     file >> new_evaluation_goal;
         set_evaluation_goal(new_evaluation_goal);

         file >> word;

         if(word != "</EvaluationGoal>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown evaluation goal end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<MeanEvaluationGoal>")
      {
       double new_mean_evaluation_goal;
     file >> new_mean_evaluation_goal;
         set_mean_evaluation_goal(new_mean_evaluation_goal);

         file >> word;

         if(word != "</MeanEvaluationGoal>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown mean evaluation goal end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<StandardDeviationEvaluationGoal>")
      {
       double new_standard_deviation_evaluation_goal;
     file >> new_standard_deviation_evaluation_goal;
         set_standard_deviation_evaluation_goal(new_standard_deviation_evaluation_goal);

         file >> word;

         if(word != "</StandardDeviationEvaluationGoal>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown standard deviation of evaluation goal end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<MaximumGenerationsNumber>")
      {
       double new_maximum_generations_number;
     file >> new_maximum_generations_number;
         set_maximum_time(new_maximum_generations_number);

         file >> word;

         if(word != "</MaximumGenerationsNumber>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown maximum generations number end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<MaximumTime>")
      {
       double new_maximum_time;
     file >> new_maximum_time;
         set_maximum_time(new_maximum_time);

         file >> word;

         if(word != "</MaximumTime>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown maximum time end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReservePopulationHistory>")
      {
     file >> reserve_population_history;

         file >> word;

         if(word != "</ReservePopulationHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve population history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveBestIndividualHistory>")
      {
     file >> reserve_best_individual_history;

         file >> word;

         if(word != "</ReserveBestIndividualHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve best individual history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveMeanNormHistory>")
      {
     file >> reserve_mean_norm_history;

         file >> word;

         if(word != "</ReserveMeanNormHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve mean norm history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveStandardDeviationNormHistory>")
      {
     file >> reserve_standard_deviation_norm_history;

         file >> word;

         if(word != "</ReserveStandardDeviationNormHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve standard deviation norm history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveBestNormHistory>")
      {
     file >> reserve_best_norm_history;

         file >> word;

         if(word != "</ReserveBestNormHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve best norm history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveMeanEvaluationHistory>")
      {
     file >> reserve_mean_evaluation_history;

         file >> word;

         if(word != "</ReserveMeanEvaluationHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve mean evaluation history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveStandardDeviationEvaluationHistory>")
      {
     file >> reserve_standard_deviation_evaluation_history;

         file >> word;

         if(word != "</ReserveStandardDeviationEvaluationHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve standard deviation evaluation history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveBestEvaluationHistory>")
      {
     file >> reserve_best_evaluation_history;

         file >> word;

         if(word != "</ReserveBestEvaluationHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve best evaluation history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<ReserveElapsedTimeHistory>")
      {
     file >> reserve_elapsed_time_history;

         file >> word;

         if(word != "</ReserveElapsedTimeHistory>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown reserve elapsed time history end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<Display>")
      {
     file >> display;

         file >> word;

         if(word != "</Display>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown display end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<DisplayPeriod>")

      {
       int new_display_period;
     file >> new_display_period;
         set_display_period(new_display_period);

         file >> word;

         if(word != "</DisplayPeriod>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown display period end tag: " << word << std::endl;

            exit(1);
         }
      }

      else if(word == "<Population>")
      {
         if(new_population_size != 0 && new_parameters_number != 0)
         {
            Matrix<double> new_population(new_population_size, new_parameters_number);

        file >> new_population;

        set_population(new_population);
         }

         file >> word;

         if(word != "</Population>")
         {
            std::cerr << "Flood Error: EvolutionaryAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
                  << "Unknown population end tag: " << word << std::endl;

            exit(1);
         }
      }
   }

   // Close file

   file.close();
}


// void resize_training_history(int) method

/// This method resizes the vectors or matrices containing training history information
/// to a new size:
/// <ul>
/// <li> Population.
/// <li> Best individual.
/// <li> Mean norm.
/// <li> Standard deviation norm.
/// <li> Best norm.
/// <li> Mean evaluation.
/// <li> Standard deviation evaluation.
/// <li> Best evaluation.
/// <li> Elapsed time.
/// </ul>
/// @param new_size Size of training history.

void EvolutionaryAlgorithm::resize_training_history(int new_size)
{
   // Population history

   if(reserve_population_history)
   {
      population_history.resize(new_size);
   }

   // Best individual history

   if(reserve_best_individual_history)
   {
      best_individual_history.resize(new_size);
   }

   // Mean population norm history vector

   if(reserve_mean_norm_history)
   {
      mean_norm_history.resize(new_size);
   }

   // Standard deviation population norm history vector

   if(reserve_standard_deviation_norm_history)
   {
      standard_deviation_norm_history.resize(new_size);
   }

   // Best individual norm history vector

   if(reserve_best_norm_history)
   {
      best_norm_history.resize(new_size);
   }

   // Mean evaluation history history vector

   if(reserve_mean_evaluation_history)
   {
      mean_evaluation_history.resize(new_size);
   }

   // Standard deviation of evaluation history vector

   if(reserve_standard_deviation_evaluation_history)
   {
      standard_deviation_evaluation_history.resize(new_size);
   }

   // Best evaluation history vector

   if(reserve_best_evaluation_history)
   {
      best_evaluation_history.resize(new_size);
   }

   // Elapsed time history vector

   if(reserve_elapsed_time_history)
   {
      elapsed_time_history.resize(new_size);
   }
}


// std::string get_training_history_XML(bool) method

/// This method returns a string representation of the training history in XML-type format.
///
/// @param show_declaration True if an XML-type declaration is to be included at the beginning of the string.

std::string EvolutionaryAlgorithm::get_training_history_XML(bool show_declaration)
{
   std::stringstream buffer;    // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='EvolutionaryAlgorithm' content='TrainingHistory'>" << std::endl;
   }

   // Multilayer perceptron

   if(reserve_population_history)
   {
      buffer << "<PopulationHistory>" << std::endl;

    for(int i = 0; i < population_history.get_size(); i++)
    {
         buffer << "<Population>" << std::endl;

         for(int i = 0; i < population_history.get_size(); i++)
         {
        buffer  << population_history[i];
         }

         buffer << "</Population>" << std::endl;

    }

      buffer << "</PopulationHistory>" << std::endl;
   }

   if(reserve_best_individual_history)
   {
      buffer << "<BestIndividualHistory>" << std::endl;

    for(int i = 0; i < best_individual_history.get_size(); i++)
    {
          buffer << best_individual_history[i] << std::endl;
    }

      buffer << "</BestIndividualHistory>" << std::endl;
   }

   if(reserve_mean_norm_history)
   {
      buffer << "<MeanNormHistory>" << std::endl
             << mean_norm_history << std::endl
             << "</MeanNormHistory>" << std::endl;
   }

   if(reserve_standard_deviation_norm_history)
   {
      buffer << "<StandardDeviationNormHistory>" << std::endl
             << standard_deviation_norm_history << std::endl
             << "</StandardDeviationNormHistory>" << std::endl;
   }

   if(reserve_best_norm_history)
   {
      buffer << "<BestNormHistory>" << std::endl
             << best_norm_history << std::endl
             << "</BestNormHistory>" << std::endl;
   }

   // Objective functional





   if(reserve_mean_evaluation_history)
   {
      buffer << "<MeanEvaluationHistory>" << std::endl
             << mean_evaluation_history << std::endl
             << "</MeanEvaluationHistory>" << std::endl;
   }

   if(reserve_standard_deviation_evaluation_history)
   {
      buffer << "<StandardDeviationEvaluationHistory>" << std::endl
             << standard_deviation_evaluation_history << std::endl
             << "</StandardDeviationEvaluationHistory>" << std::endl;
   }

   if(reserve_best_evaluation_history)
   {
      buffer << "<BestEvaluationHistory>" << std::endl
             << best_evaluation_history << std::endl
             << "</BestEvaluationHistory>" << std::endl;
   }

   // Training algorithm

   if(reserve_elapsed_time_history)
   {
      buffer << "<ElapsedTimeHistory>" << std::endl
             << elapsed_time_history << std::endl
             << "</ElapsedTimeHistory>" << std::endl;
   }

   return(buffer.str());
}


// double calculate_random_uniform(double, double) method

double EvolutionaryAlgorithm::calculate_random_uniform(double minimum, double maximum)
{
   double random = (double)rand()/(RAND_MAX+1.0);

   double random_uniform = minimum + (maximum-minimum)*random;

   return(random_uniform);
}


// double calculate_random_normal(double, double) method

double EvolutionaryAlgorithm::calculate_random_normal(double mean, double standard_deviation)
{
   double random_normal = 0.0;

   const double pi = 4.0*atan(1.0);

   double random_uniform_1;
   double random_uniform_2;

   do
   {
      random_uniform_1 = (double)rand()/(RAND_MAX+1.0);

   }while(random_uniform_1 == 0.0);

   random_uniform_2 = (double)rand()/(RAND_MAX+1.0);

   // Box-Muller transformation

   random_normal = mean + sqrt(-2.0*log(random_uniform_1))*sin(2.0*pi*random_uniform_2)*standard_deviation;

   return(random_normal);
}


/*void EvolutionaryAlgorithm::init_elite_population_file(std::string note,
                                                       std::string robotType,
                                                       std::string controllerType,
                                                       std::string scenefilename,

                                                       bool gen0_preeval,
                                                       bool gen0_aug_pop,

                                                       double servo_max,
                                                       double servo_min,
                                                       int number_of_modules,
                                                       double sim_resolution,
                                                       int unit_second,
                                                       int simulation_seconds,
                                                       //bool random_start_angle,
                                                       std::string start_angle_type,
                                                       bool perturbation,
                                                       int perturbation_interval,
                                                       int perturbation_length,
                                                       double feedback_diff_threshold,
                                                       double servo_delta_threshold,
                                                       int servo_history_size,

                                                       int number_of_inputs_to_NN,
                                                       Vector<int> &NN_hidden_layers,
                                                       int number_of_outputs_to_NN,

                                                       Vector< std::string > &independent_parameters_name,
                                                       Vector< double > &independent_parameters_minimum,
                                                       Vector< double > &independent_parameters_maximum)
{
   time_t rawtime;
   struct tm * timeinfo;
   char filename[100];
   stringstream ss;
   //string file_name;

   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   strftime (filename, 100, "/gene_data/%m_%d_%H_%M_elite_population.gne", timeinfo);
   ss << robotType << "/" << controllerType << filename;
   //file_name = ss.str();
   elite_population_file_name = ss.str();
   cout <<" Opening elite_population data file: " << elite_population_file_name << endl;
   elite_population_file.open(elite_population_file_name.c_str(), fstream::in | fstream::out | fstream::app);

   elite_population_file << "<CubeRevolution: Flood + OpenRave + OpenMR>" << std::endl;
   elite_population_file << std::endl << "<FileType>" << std::endl << "   GeneFile" << std::endl << "</FileType>" << std::endl;

   if(note != "No Notes")
   {
      elite_population_file << std::endl << "<Note>" << std::endl << note << std::endl << "</Note>" << std::endl;
   }

   elite_population_file << std::endl << "<Evolution>" << std::endl;
   elite_population_file << "\t<FitnessAssignmentMethod>" << std::endl << "\t   " << get_fitness_assignment_method_name() << std::endl << "\t</FitnessAssignmentMethod>" << std::endl;
   elite_population_file << std::endl << "\t<SelectionMethod>" << std::endl << "\t   " << get_selection_method_name() << std::endl << "\t</SelectionMethod>" << std::endl;
   elite_population_file << std::endl << "\t<RecombinationMethod>" << std::endl << "\t   " << get_recombination_method_name() << std::endl << "\t</RecombinationMethod>" << std::endl;
   elite_population_file << std::endl << "\t<MutationMethod>" << std::endl << "\t   " << get_mutation_method_name() << std::endl << "\t</MutationMethod>" << std::endl;
   elite_population_file << std::endl << "\t<PopulationSize>" << std::endl << "\t   " << get_population_size() << std::endl << "\t</PopulationSize>" << std::endl;
   elite_population_file << std::endl << "\t<CrossoverPercentage>" << std::endl << "\t   " << crossover_percentage << std::endl << "\t</CrossoverPercentage>" << std::endl;
   elite_population_file << std::endl << "\t<Elitism>" << std::endl << "\t   " << elitism << std::endl << "\t</Elitism>" << std::endl;
   elite_population_file << std::endl << "\t<ElitismPercentage>" << std::endl << "\t   " << elitism_percentage << std::endl << "\t</ElitismPercentage>" << std::endl;
   elite_population_file << std::endl << "\t<SelectivePressure>" << std::endl << "\t   " << selective_pressure << std::endl << "\t</SelectivePressure>" << std::endl;
   elite_population_file << std::endl << "\t<RecombinationSize>" << std::endl << "\t   " << recombination_size << std::endl << "\t</RecombinationSize>" << std::endl;
   elite_population_file << std::endl << "\t<MutationRate>" << std::endl << "\t   " << mutation_rate << std::endl << "\t</MutationRate>" << std::endl;
   elite_population_file << std::endl << "\t<MutationRateForES>" << std::endl << "\t   " << mutation_rate_for_ES << std::endl << "\t</MutationRateForES>" << std::endl;
   elite_population_file << std::endl << "\t<MutationRange>" << std::endl << "\t   " << mutation_range << std::endl << "\t</MutationRange>" << std::endl;
   elite_population_file << std::endl << "\t<MutationRangeForES>" << std::endl << "\t   " << mutation_range_for_ES << std::endl << "\t</MutationRangeForES>" << std::endl;
   elite_population_file << std::endl << "\t<EvaluationSampleSize>" << std::endl << "\t   " << evaluation_sample_size << std::endl << "\t</EvaluationSampleSize>" << std::endl;
   if(gen0_preeval)
   {
      elite_population_file << std::endl << "\t<Gen0_Pre-Evaluation>" << std::endl << "\t   " << "True" << std::endl << "\t</Gen0_Pre-Evaluation>" << std::endl;
   }
   else
   {
      elite_population_file << std::endl << "\t<Gen0_Pre-Evaluation>" << std::endl << "\t   " << "False" << std::endl << "\t</Gen0_Pre-Evaluation>" << std::endl;
   }
   if(gen0_aug_pop)
   {
      elite_population_file << std::endl << "\t<Gen0_AugmentedPopulation>" << std::endl << "\t   " << "True" << std::endl << "\t</Gen0_AugmentedPopulation>" << std::endl;
   }
   else
   {
      elite_population_file << std::endl << "\t<Gen0_AugmentedPopulation>" << std::endl << "\t   " << "False" << std::endl << "\t</Gen0_AugmentedPopulation>" << std::endl;
   }
   elite_population_file << std::endl << "\t<Gen0_MinimumEvaluationValue>" << std::endl << "\t   " << gen_0_min_evaluation_value << std::endl << "\t</Gen0_MinimumEvaluationValue>" << std::endl;
   elite_population_file << std::endl << "\t<Gen0_PopulationSize>" << std::endl << "\t   " << gen_0_population_size << std::endl << "\t</Gen0_PopulationSize>" << std::endl;
   elite_population_file << "</Evolution>" << std::endl;


   elite_population_file << std::endl << "<SimulationEnvironment>" << std::endl;
   elite_population_file << "\t<RobotType>" << std::endl << "\t   " << robotType << std::endl << "\t</RobotType>" << std::endl;
   elite_population_file << std::endl << "\t<ControllerType>" << std::endl << "\t   " << controllerType << std::endl << "\t</ControllerType>" << std::endl;
   elite_population_file << std::endl << "\t<SceneFileName>" << std::endl << "\t   " << scenefilename << std::endl << "\t</SceneFileName>" << std::endl;
   elite_population_file << std::endl << "\t<ServoMax>" << std::endl << "\t   " << servo_max << std::endl << "\t</ServoMax>" << std::endl;
   elite_population_file << std::endl << "\t<ServoMin>" << std::endl << "\t   " << servo_min << std::endl << "\t</ServoMin>" << std::endl;
   elite_population_file << std::endl << "\t<NumberOfModules>" << std::endl << "\t   " << number_of_modules << std::endl << "\t</NumberOfModules>" << std::endl;
   elite_population_file << std::endl << "\t<SimResolution>" << std::endl << "\t   " << sim_resolution << std::endl << "\t</SimResolution>" << std::endl;
   elite_population_file << std::endl << "\t<UnitSecond>" << std::endl << "\t   " << unit_second << std::endl << "\t</UnitSecond>" << std::endl;
   elite_population_file << std::endl << "\t<SimulationSeconds>" << std::endl << "\t   " << simulation_seconds << std::endl << "\t</SimulationSeconds>" << std::endl;
   //elite_population_file << std::endl << "\t<RandomStartAngle>" << std::endl << "\t   " << random_start_angle << std::endl << "\t</RandomStartAngle>" << std::endl;
   elite_population_file << std::endl << "\t<StartAngleType>" << std::endl << "\t   " << start_angle_type << std::endl << "\t</StartAngleType>" << std::endl;
   elite_population_file << std::endl << "\t<Perturbation>" << std::endl << "\t   " << perturbation << std::endl << "\t</Perturbation>" << std::endl;
   elite_population_file << std::endl << "\t<PerturbationInterval>" << std::endl << "\t   " << perturbation_interval << std::endl << "\t</PerturbationInterval>" << std::endl;
   elite_population_file << std::endl << "\t<PerturbationLength>" << std::endl << "\t   " << perturbation_length << std::endl << "\t</PerturbationLength>" << std::endl;
   elite_population_file << std::endl << "\t<FeedBackDiffThreshold>" << std::endl << "\t   " << feedback_diff_threshold << std::endl << "\t</FeedBackDiffThreshold>" << std::endl;
   if(controllerType == "Neural_Controller")
   {
      elite_population_file << std::endl << "\t<ServoDeltaThreshold>" << std::endl << "\t   " << servo_delta_threshold << std::endl << "\t</ServoDeltaThreshold>" << std::endl;
      elite_population_file << std::endl << "\t<ServoHistorySize>" << std::endl << "\t   " << servo_history_size << std::endl << "\t</ServoHistorySize>" << std::endl;
   }
   elite_population_file << "</SimulationEnvironment>" << std::endl;


   if(number_of_inputs_to_NN > 0)
   {
      elite_population_file << std::endl << "<NeuralNetwork>" << std::endl;
      elite_population_file << "\t<NumberOfNNInputs>" << std::endl << "\t   " << number_of_inputs_to_NN << std::endl << "\t</NumberOfNNInputs>" << std::endl;
      if(NN_hidden_layers.get_size() > 0)
      {
         elite_population_file << std::endl << "\t<HiddenLayers>"; //<< "\t   " << number_of_inputs_to_NN << std::endl << "\t</NumberOfNNInputs>" << std::endl;
         for(int i=0; i<NN_hidden_layers.get_size(); i++)
         {
            elite_population_file << std::endl << "\t   <Layer>" << std::endl << "\t      " << NN_hidden_layers[i] << std::endl << "\t   </Layer>" << std::endl;
         }
         elite_population_file << "\t</HiddenLayers>" << std::endl;
      }
      elite_population_file << std::endl << "\t<NumberOfNNOutputs>" << std::endl << "\t   " << number_of_outputs_to_NN << std::endl << "\t</NumberOfNNOutputs>" << std::endl;
      elite_population_file << "</NeuralNetwork>" << std::endl;
   }


   if(independent_parameters_name.get_size() > 0)
   {
      elite_population_file << std::endl << "<IndependentParameters>";
      for(int i=0; i<independent_parameters_name.get_size(); i++)
      {
         elite_population_file << std::endl << "\t<Parameter>";
         elite_population_file << std::endl << "\t   <Name>" << std::endl << "\t      " << independent_parameters_name[i] << std::endl << "\t   </Name>" << std::endl;
         elite_population_file << std::endl << "\t   <Minimum>" << std::endl << "\t      " << independent_parameters_minimum[i] << std::endl << "\t   </Minimum>" << std::endl;
         elite_population_file << std::endl << "\t   <Maximum>" << std::endl << "\t      " << independent_parameters_maximum[i] << std::endl << "\t   </Maximum>" << std::endl;
         elite_population_file << "\t</Parameter>" << std::endl;
      }

      elite_population_file << "</IndependentParameters>" << std::endl;
   }


   elite_population_file << std::endl << "<Gene>" << std::endl;
   elite_population_file << std::endl << "</Gene>" << std::endl;
   elite_population_file << std::endl << "</CubeRevolution>";

   elite_population_file.close();
}*/


/*void EvolutionaryAlgorithm::init_fitness_history_file(std::string robotType, std::string controllerType)
{
   time_t rawtime;
   struct tm * timeinfo;
   char filename[100];
   stringstream ss;
   string file_name;

   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   strftime (filename, 100, "/fitnessGraph/%m_%d_%H_%M_fitness_graph.dat", timeinfo);
   ss << robotType << "/" << controllerType << filename;

   file_name = ss.str();

   fitness_graph_file = new GnuPlot (file_name.c_str());
}*/


}


// Flood: An Open Source Neural Networks C++ Library.
// Copyright (C) 2005-2010 Roberto Lopez
//
// This library is free software; you can redistribute it and/or
// modify it under the s of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU

// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
