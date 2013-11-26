/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   E V O L U T I O N A R Y   A L G O R I T H M   C L A S S   H E A D E R                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef __EVOLUTIONARYALGORITHM_H__
#define __EVOLUTIONARYALGORITHM_H__

class FileHandler;

#include <vector>

#include "TrainingAlgorithm.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"
#include "FileHandler.h"
#include "GraphFile.h"

//#define ELITE_POPULATION_FILE
#define CROSSOVER_RANK_BASED_PRIORITY

namespace Flood
{

/// This concrete class represents an evolutionary training algorithm for an objective functional of a multilayer
/// perceptron.

class EvolutionaryAlgorithm : public TrainingAlgorithm
{

public:

   // ENUMERATIONS

   /// Enumeration of the available training operators for fitness assignment.

   enum FitnessAssignmentMethod{LinearRanking, MyLinearRanking};

   /// Enumeration of the available training operators for selection.

   enum SelectionMethod{RouletteWheel, MyRouletteWheel, StochasticUniversalSampling};

   /// Enumeration of the available training operators for recombination.

   enum RecombinationMethod{Line, Intermediate, MyIntermediate, MyIntermediateWithElitism, MyIntermediateWithElitismAndES};

   /// Enumeration of the available training operators for mutation.

   enum MutationMethod{Normal, MyNormal, MyNormalWithES, Uniform};
    // GENERAL CONSTRUCTOR

   explicit EvolutionaryAlgorithm(ObjectiveFunctional*);


   // DEFAULT CONSTRUCTOR

   explicit EvolutionaryAlgorithm(void);


   // DESTRUCTOR

   virtual ~EvolutionaryAlgorithm(void);


   // METHODS

   // Get methods

   // Population methods

   int get_population_size(void);

   Matrix<double>& get_population(void);

   // Training operators

   FitnessAssignmentMethod& get_fitness_assignment_method(void);
   std::string get_fitness_assignment_method_name(void);

   SelectionMethod& get_selection_method(void);
   std::string get_selection_method_name(void);

   RecombinationMethod& get_recombination_method(void);
   std::string get_recombination_method_name(void);

   MutationMethod& get_mutation_method(void);
   std::string get_mutation_method_name(void);

   // Population values

   Vector<double>& get_evaluation(void);
   Vector<double>& get_fitness(void);
   Vector<bool>& get_selection(void);

   bool get_elitism(void);
   double get_selective_pressure(void);
   double get_elitism_percentage(void);
   double get_crossover_percentage(void);

   double get_recombination_size(void);
   double get_mutation_rate(void);
   double get_mutation_range(void);
   double get_mutation_rate_for_ES(void);
   double get_mutation_range_for_ES(void);
   int get_evaluation_sample_size(void);
   double get_gen_0_min_evaluation_value(void);
   int get_gen_0_population_size(void);
   double get_maximum_generations_number(void);
   double get_mean_evaluation_goal(void);
   double get_standard_deviation_evaluation_goal(void);

   bool get_fitness_graph_history(void);
   bool get_elite_population_history(void);
   bool get_reserve_population_history(void);
   bool get_reserve_best_individual_history(void);
   bool get_reserve_mean_norm_history(void);
   bool get_reserve_standard_deviation_norm_history(void);
   bool get_reserve_best_norm_history(void);

   bool get_reserve_mean_evaluation_history(void);
   bool get_reserve_standard_deviation_evaluation_history(void);
   bool get_reserve_best_evaluation_history(void);

   Vector< Matrix<double> >& get_population_history(void);

   Vector< Vector<double> >& get_best_individual_history(void);

   Vector<double>& get_mean_norm_history(void);
   Vector<double>& get_standard_deviation_norm_history(void);
   Vector<double>& get_best_norm_history(void);

   Vector<double>& get_mean_evaluation_history(void);
   Vector<double>& get_standard_deviation_evaluation_history(void);
   Vector<double>& get_best_evaluation_history(void);

   // Set methods

   void set(void);
   void set(ObjectiveFunctional*);

   void set_default(void);

   void set_fitness_assignment_method(const FitnessAssignmentMethod&);
   void set_fitness_assignment_method(const std::string&);

   void set_selection_method(const SelectionMethod&);
   void set_selection_method(const std::string&);

   void set_recombination_method(const RecombinationMethod&);
   void set_recombination_method(const std::string&);

   void set_mutation_method(const MutationMethod&);
   void set_mutation_method(const std::string&);

   void set_population_size(int);

   void set_population(const Matrix<double>&);

   void set_evaluation(const Vector<double>&);
   void set_fitness(const Vector<double>&);
   void set_selection(const Vector<bool>&);

   void set_elitism(bool);
   void set_elitism_percentage(double);
   void set_crossover_percentage(double);
   void set_selective_pressure(double);
   void set_recombination_size(double);

   void set_mutation_rate(double);
   void set_mutation_range(double);
   void set_mutation_rate_for_ES(double);
   void set_mutation_range_for_ES(double);

   void set_evaluation_sample_size(int);
   void set_gen_0_min_evaluation_value(double);
   void set_gen_0_population_size(int);

   void set_maximum_generations_number(int);
   void set_mean_evaluation_goal(double);
   void set_standard_deviation_evaluation_goal(double);

   void set_fitness_graph_history(bool);
   void set_fitness_graph_file(GraphFile*);
   void set_elite_population_history(bool);
   void set_elite_population_file(FileHandler*);

   void set_reserve_population_history(bool);

   void set_reserve_best_individual_history(bool);

   void set_reserve_mean_norm_history(bool);
   void set_reserve_standard_deviation_norm_history(bool);
   void set_reserve_best_norm_history(bool);

   void set_reserve_mean_evaluation_history(bool);
   void set_reserve_standard_deviation_evaluation_history(bool);
   void set_reserve_best_evaluation_history(bool);

   void set_reserve_all_training_history(bool);

   void set_population_history(const Vector< Matrix<double> >&);

   void set_best_individual_history(const Vector< Vector<double> >&);

   void set_mean_norm_history(const Vector<double>&);
   void set_standard_deviation_norm_history(const Vector<double>&);
   void set_best_norm_history(const Vector<double>&);

   void set_mean_evaluation_history(const Vector<double>&);
   void set_standard_deviation_evaluation_history(const Vector<double>&);
   void set_best_evaluation_history(const Vector<double>&);

   // Population methods

   Vector<double> get_individual(int);
   void set_individual(int, const Vector<double>&);

   Vector<double> get_best_individual(void);

   double calculate_mean_evaluation(void);
   double calculate_standard_deviation_evaluation(void);

   // Initialization methods

   void initialize_population(double);

   void initialize_population_uniform(void);
   void initialize_population_uniform(double, double);
   void initialize_population_uniform(const Vector<double>&, const Vector<double>&);
   void initialize_population_uniform_independent_parameters(const Vector<double>&, const Vector<double>&); //Avinash Ranganath
   void initialize_population_uniform(const Matrix<double>&);

   void initialize_population_normal(void);
   void initialize_population_normal(double, double);
   void initialize_population_normal(const Vector<double>&, const Vector<double>&);
   void initialize_population_normal(const Matrix<double>&);

   void populate_generation_0(void);
   void populate_generation_0_augmented_polulation(void);

   // Population norm methods

   Vector<double> calculate_population_norm(void);

   // Population evaluation methods

   void perform_fitness_assignment(void);
   void perform_selection(void);
   void perform_recombination(void);
   void perform_mutation(void);

   void evolve_population(void);
   void evolve_population(int);

   void evaluate_population(void);
   void evaluate_population(int);

   // Fitness assignment methods

   void perform_linear_ranking_fitness_assignment(void);
   void perform_my_linear_ranking_fitness_assignment(void);

   // Selection methods

   void perform_roulette_wheel_selection(void);
   void perform_my_roulette_wheel_selection(void);
   void perform_stochastic_universal_sampling_selection(void);

   // Recombination methods

   void perform_intermediate_recombination(void);
   void perform_my_intermediate_recombination(void);
   void perform_my_intermediate_recombination_with_elitism(void);
   void perform_my_intermediate_recombination_with_elitism_and_evolution_strategy(void);
   void perform_line_recombination(void);

   // Mutation methods

   void perform_normal_mutation(void);
   void perform_my_normal_mutation(void);
   void perform_my_normal_mutation_with_ES(void);
   void perform_uniform_mutation(void);

   // Train methods

   void train(void);

   // Training history methods

   void resize_training_history(int);

   std::string get_training_history_XML(bool);

   // Utility methods

   std::string to_XML(bool);
   void load(const char*);
   void save_member(int);

   // TODO: The following two declerations to be removed.
   //void init_elite_population_file(std::string, std::string, std::string, std::string, bool, bool, double, double, int, double, int, int, std::string, bool, int, int, double, double, int, int, Vector<int>&, int, Vector< std::string > &, Vector< double > &, Vector< double > &);
   //void init_fitness_history_file(std::string, std::string);


private:

   // MEMBERS

   /// Fitness assignment training operators enumeration.

   FitnessAssignmentMethod fitness_assignment_method;

   /// Selection training operators enumeration.

   SelectionMethod selection_method;

   /// Recombination training operators enumeration.

   RecombinationMethod recombination_method;

   /// Mutation training operators enumeration.

   MutationMethod mutation_method;

   // Population stuff

   /// Population matrix.

   Matrix<double> population;

   /// Elite population gene
   Matrix<double> elite_population_gene; // Avinash Ranganath;

   /// Elite population
   //Vector<int> elite_population_lookup;

   /// Evaluation of population.

   Vector<double> evaluation;

   /// Rank of population.

   Vector<int> rank; // Avinash Ranganath

   /// Fitness of population.

   Vector<double> fitness;

   /// Selected individuals in population.

   Vector<bool> selection;

   // Training parameters

   double crossover_percentage; // Avinash Ranganath
   bool elitism;
   double elitism_percentage; // Avinash Ranganath

   /// Selective pressure.
   /// Linear ranking allows values for the selective pressure between 1 and 2.

   double selective_pressure;

   /// Recombination size.
   /// The recombination size value must be equal or greater than 0.

   double recombination_size;

   /// Mutation rate.
   /// The mutation rate value must be between 0 and 1.

   double mutation_rate;
   double mutation_rate_for_ES;

   /// Mutation range.
   /// The mutation range value must be 0 or a positive number.

   double mutation_range;
   double mutation_range_for_ES;

   int evaluation_sample_size;
   double gen_0_min_evaluation_value;
   int gen_0_population_size;

   double mean_evaluation_goal;

   double standard_deviation_evaluation_goal;

   /// Maximum number of generations to train.

   int maximum_generations_number;

   bool fitness_graph_history;

   bool elite_population_history;

   /// True if the population history, which is a vector of matrices, is to be reserved, false otherwise.
   /// Reserving the population history can be compuationally expensive if the number of parameters,
   /// the population size and the number of generations are big numbers.

   bool reserve_population_history;

   /// True if the history of the best individual ever is to be reserved, and false otherwise.
   /// The best individual history is a vector of vectors.

   bool reserve_best_individual_history;

   /// True if the mean norm history vector is to be reserved, false otherwise.

   bool reserve_mean_norm_history;

   /// True if the standard deviation of norm history vector is to be reserved, false otherwise.

   bool reserve_standard_deviation_norm_history;

   /// True if the best norm history vector is to be reserved, false otherwise.

   bool reserve_best_norm_history;

   /// True if the mean evaluation history vector is to be reserved, false otherwise.

   bool reserve_mean_evaluation_history;

   /// True if the standard deviation of evaluation history vector is to be reserved, false otherwise.

   bool reserve_standard_deviation_evaluation_history;

   /// True if the best evaluation history vector is to be reserved, false otherwise.

   bool reserve_best_evaluation_history;

   /// Population history over the epochs, which is a vector of matrices.
   /// The element 0 of the vector is the initial population, and so on.

   Vector< Matrix<double> > population_history;

   /// History of best individual ever over the epochs, which is a vector of vectors.
   /// The element 0 is the best individual of the initial population, and so on.

   Vector< Vector<double> > best_individual_history;

   /// Mean population norm training history.
   /// This vector is of the form (MeanOfPopulationNormAtEpoch0,...,MeanOfPopulationNormAtEpochN)

   Vector<double> mean_norm_history;

   /// Standard deviation of population norm training history.
   /// This vector is of the form
   /// (StandardDeviationOfPopulationNormAtEpoch0,...,StandardDeviationOfPopulationNormAtEpochN)

   Vector<double> standard_deviation_norm_history;

   /// Best individual ever norm history.

   Vector<double> best_norm_history;

   /// Mean evaluation training history.

   Vector<double> mean_evaluation_history;

   /// Standard deviation of evaluation training history.

   Vector<double> standard_deviation_evaluation_history;

   /// Best evaluation ever training history.

   Vector<double> best_evaluation_history;

   /// File for saving the genome of the best performing individuals

   FileHandler *elite_population_file;

   GraphFile *fitness_graph_file; // TODO: Maybe needs to be removed

   // METHODS

   // Utility methods

   double calculate_random_uniform(double, double);
   double calculate_random_normal(double, double);
};

}

#endif


// Flood: An Open Source Neural Networks C++ Flood.
// Copyright (C) 2005-2010 Roberto Lopez
//
// This Flood is free software; you can redistribute it and/or
// modify it under the s of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This Flood is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this Flood; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
