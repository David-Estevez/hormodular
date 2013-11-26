/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   R A N D O M   S E A R C H   C L A S S                                                                      */
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
#include <ctime>

// Flood includes

#include "RandomSearch.h"

namespace Flood
{

// GENERAL CONSTRUCTOR 

/// General constructor. It creates a random search training algorithm object associated to an objective 
/// functional object. 
/// It also initializes the class members to their default values.
/// @param new_objective_functional_pointer Pointer to an objective functional object.

RandomSearch::RandomSearch(ObjectiveFunctional* new_objective_functional_pointer)
: TrainingAlgorithm(new_objective_functional_pointer)
{   
   set_default();
}


// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a random search training algorithm object not associated to any objective 
/// functional object. 
/// It also initializes the class members to their default values.

RandomSearch::RandomSearch(void) : TrainingAlgorithm()
{
   set_default();
}


// DESTRUCTOR

/// Destructor.

RandomSearch::~RandomSearch(void)
{

}


// double get_training_rate_reduction_factor(void) method

/// This method returns the reducing factor for the training rate. 

double RandomSearch::get_training_rate_reduction_factor(void)
{
   return(training_rate_reduction_factor);
}


// int get_training_rate_reduction_period(void) method

/// This method returns the reducing period for the training rate. 

int RandomSearch::get_training_rate_reduction_period(void)
{
   return(training_rate_reduction_period);
}


// bool get_reserve_potential_parameters_history(void) method

/// This method returns true if the potential parameters history is to be reserved, and false otherwise.

bool RandomSearch::get_reserve_potential_parameters_history(void)
{
   return(reserve_potential_parameters_history);
}


// bool get_reserve_potential_parameters_norm_history(void) method

/// This method returns true if the potential parameters norm history is to be reserved, and false otherwise.

bool RandomSearch::get_reserve_potential_parameters_norm_history(void)
{
   return(reserve_potential_parameters_norm_history);
}


// bool get_reserve_potential_evaluation_history(void) method

/// This method returns true if the potential evaluation history is to be reserved, and false otherwise.

bool RandomSearch::get_reserve_potential_evaluation_history(void)
{
   return(reserve_potential_evaluation_history);
}


// Vector< Vector<double> > get_potential_parameters_history(void) method

/// This method returns the history of potential parameters, which is a vector of vectors.

Vector< Vector<double> > RandomSearch::get_potential_parameters_history(void)
{
   return(potential_parameters_history);
}


// Vector<double> get_potential_parameters_norm_history(void) method

/// This method returns the history of potential parameters norm values, which is a vector.

Vector<double> RandomSearch::get_potential_parameters_norm_history(void)
{
   return(potential_parameters_norm_history);
}


// Vector<double> get_potential_evaluation_history(void) method

/// This method returns the history of evaluation values, which is a vector.

Vector<double> RandomSearch::get_potential_evaluation_history(void)
{
   return(potential_evaluation_history);
}


// void set_default(void) method

/// This method sets all the random search object members to their default values:
/// <ul>
/// <li> Training rate reduction factor: 0.9
/// <li> Training rate reduction period: 10
/// <li> Warning parameters norm: 1.0e6
/// <li> Error parameters norm: 1.0e9
/// <li> Evaluation goal: -1.0e99
/// <li> Maximum time: 1.0e6
/// <li> Maximum epochs number: 100
/// <li> Reserve potential parameters history: False
/// <li> Reserve potential parameters norm history: False
/// <li> Reserve evaluation history: False.
/// <li> Display: True
/// <li> Display period: 10
/// </ul>

void RandomSearch::set_default(void)
{   
   // TRAINING PARAMETERS

   first_training_rate = 1.0;

   training_rate_reduction_factor = 0.9;
   training_rate_reduction_period = 10;

   // STOPPING CRITERIA

   minimum_evaluation_improvement = 0.0;
   evaluation_goal = -1.0e99;

   maximum_epochs_number = 1000;
   maximum_time = 1000.0;

   // TRAINING HISTORY

   reserve_potential_parameters_history = false;
   reserve_parameters_history = false;
   reserve_potential_parameters_norm_history = false;
   reserve_parameters_norm_history = false;

   reserve_potential_evaluation_history = false; 
   reserve_evaluation_history = false;

   reserve_training_direction_history = false;
   reserve_training_rate_history = false;
   reserve_elapsed_time_history = false;

   // UTILITIES

   display = true;
   display_period = 100;
}


// void set_training_rate_reduction_factor(double) method

void RandomSearch::set_training_rate_reduction_factor(double new_training_rate_reduction_factor)
{
   training_rate_reduction_factor = new_training_rate_reduction_factor;
}


// void set_training_rate_reduction_period(int) method

void RandomSearch::set_training_rate_reduction_period(int new_training_rate_reduction_period)
{
   training_rate_reduction_period = new_training_rate_reduction_period;
}


// void set_reserve_potential_parameters_history(bool) method

void RandomSearch::set_reserve_potential_parameters_history(bool new_reserve_potential_parameters_history)
{
   reserve_potential_parameters_history = new_reserve_potential_parameters_history;
}


// void set_reserve_potential_parameters_norm_history(bool) method

void RandomSearch::set_reserve_potential_parameters_norm_history(bool new_reserve_potential_parameters_norm_history)
{
   reserve_potential_parameters_norm_history = new_reserve_potential_parameters_norm_history;   
}


// void set_reserve_potential_evaluation_history(bool) method

void RandomSearch::set_reserve_potential_evaluation_history(bool new_reserve_potential_evaluation_history)
{
   reserve_potential_evaluation_history = new_reserve_potential_evaluation_history;
}


// void set_potential_parameters_history(const Vector< Vector<double> >&) method

void RandomSearch::set_potential_parameters_history(const Vector< Vector<double> >& new_potential_parameters_history)
{
   potential_parameters_history = new_potential_parameters_history;
}


// void set_potential_parameters_norm_history(const Vector<double>&) method

void RandomSearch::set_potential_parameters_norm_history(const Vector<double>& new_potential_parameters_norm_history)
{
   potential_parameters_norm_history = new_potential_parameters_norm_history;
}


// void set_potential_evaluation_history(const Vector<double>&) method

void RandomSearch::set_potential_evaluation_history(const Vector<double>& new_potential_evaluation_history)
{
   potential_evaluation_history = new_potential_evaluation_history;
}


// void set_reserve_all_training_history(bool) method

/// This method makes the training history of all variables to reseved or not in memory.
///
/// @param new_reserve_all_training_history True if the training history of all variables is to be reserved, 
/// false otherwise.

void RandomSearch::set_reserve_all_training_history(bool new_reserve_all_training_history)
{
   // Multilayer perceptron

   reserve_potential_parameters_history = new_reserve_all_training_history;
   reserve_parameters_history = new_reserve_all_training_history;

   reserve_potential_parameters_norm_history = new_reserve_all_training_history;
   reserve_parameters_norm_history = new_reserve_all_training_history;
   
   // Objective functional

   reserve_potential_evaluation_history = new_reserve_all_training_history;
   reserve_evaluation_history = new_reserve_all_training_history;
  
   // Training algorithm

   reserve_elapsed_time_history = new_reserve_all_training_history;
}


// Vector<double> calculate_training_direction(void) method

Vector<double> RandomSearch::calculate_training_direction(void)
{   
   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> random(parameters_number);
   double random_norm;

   do
   { 
      random.initialize_uniform();   
      random_norm = random.calculate_norm();             
   }while(random_norm > 1.0);

   return(random/random_norm);
}


// void train(void) method

/// This method trains a multilayer perceptron with an associated 
/// objective function according to the random search training algorithm.
/// Training occurs according to the training parameters. 

void RandomSearch::train(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: RandomSearch class." << std::endl
                << "void train(void) method." << std::endl
                << "Pointer to objective functional object cannot be NULL." << std::endl;

        exit(1);
   }

   #endif

   // Start training 

   if(display)
   {
      std::cout << "Training with random search..." << std::endl;
   }
     
   // Elapsed time

   time_t beginning_time, current_time;
   time(&beginning_time);
   double elapsed_time;

   // Multilayer perceptron stuff

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> parameters(parameters_number);
   Vector<double> potential_parameters(parameters_number);

   double parameters_norm = 0.0;
   double potential_parameters_norm = 0.0;

   // Objective functional stuff
    
   double evaluation = 0.0;
   double potential_evaluation = 0.0;

   // Training algorithm stuff 

   Vector<double> training_direction(parameters_number);
   double training_rate = 0.0;

   Vector<double> parameters_increment(parameters_number);

   bool stop_training = false;

   resize_training_history(maximum_epochs_number+1);

   // Main loop 

   for(int epoch = 0; epoch <= maximum_epochs_number; epoch++)
   {
      if(epoch == 0)
      {
         parameters = multilayer_perceptron_pointer->get_parameters();	  
         potential_parameters = parameters;	  

         parameters_norm = potential_parameters.calculate_norm();
         potential_parameters_norm = parameters_norm;
      }      

      // Objective functional stuff

      if(epoch == 0)
	  {
         evaluation = objective_functional_pointer->calculate_evaluation();
         potential_evaluation = evaluation;
	  }
	  else
	  {
         potential_evaluation = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);
	  }

      if(potential_evaluation < evaluation)
      {      
         parameters = potential_parameters;

         multilayer_perceptron_pointer->set_parameters(potential_parameters);

         evaluation = potential_evaluation;
      }

      // Training algorithm stuff

      training_direction = calculate_training_direction();
  
      if(epoch == 0)
      {
         training_rate = first_training_rate;      
      }
      else if(epoch%training_rate_reduction_period == 0)
      {
         training_rate *= training_rate_reduction_factor; 
      }       

      parameters_increment = training_direction*training_rate;

      // Elapsed time

      time(&current_time);
      elapsed_time = difftime(current_time, beginning_time);

      // Training history multilayer perceptron 

      if(reserve_potential_parameters_history)
      {
         potential_parameters_history[epoch] = potential_parameters;                                
      }

      if(reserve_parameters_history)
      {
         parameters_history[epoch] = parameters;                                
      }

      if(reserve_potential_parameters_norm_history)
      {
         potential_parameters_norm_history[epoch] = potential_parameters_norm; 
      }       if(reserve_parameters_norm_history)
      {
         parameters_norm_history[epoch] = parameters_norm; 
      }

      // Training history objective functional

      if(reserve_potential_evaluation_history)
      {
         potential_evaluation_history[epoch] = potential_evaluation;
      }

      if(reserve_evaluation_history)
      {
         evaluation_history[epoch] = evaluation;
      }

      // Training history training algorithm

      if(reserve_training_direction_history)
      {
         training_direction_history[epoch] = training_direction;                                
      }

      if(reserve_training_rate_history)
      {
         training_rate_history[epoch] = training_rate;
      }

      if(reserve_elapsed_time_history)
      {
         elapsed_time_history[epoch] = elapsed_time;
      }

      // Stopping Criteria

      if(potential_evaluation <= evaluation_goal)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Evaluation goal reached." << std::endl;
         }

         stop_training = true;
      }

      else if(epoch == maximum_epochs_number)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Maximum number of epochs reached." << std::endl;
         }

         stop_training = true;
      }

      else if(elapsed_time >= maximum_time)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Maximum training time reached." << std::endl;
         }

         stop_training = true;
      }

      if(stop_training)
      {
         if(display)
		 {
            std::cout << "Potential parameters norm: " << potential_parameters_norm << std::endl 
                      << "Parameters norm: " << parameters_norm << std::endl 
                      << "Potential evaluation: " << potential_evaluation << std::endl
                      << "Evaluation: " << evaluation << std::endl
                      << "Training rate: " << training_rate << std::endl
                      << "Elapsed time: " << elapsed_time << std::endl; 

            objective_functional_pointer->print_information();
		 }   
 
         break;
      }

      else if(display && epoch % display_period == 0)
      {
         std::cout << "Epoch " << epoch << ";" << std::endl;

         std::cout << "Potential parameters norm: " << potential_parameters_norm << std::endl 
                   << "Parameters norm: " << parameters_norm << std::endl 
                   << "Potential evaluation: " << potential_evaluation << std::endl
                   << "Evaluation: " << evaluation << std::endl
                   << "Training rate: " << training_rate << std::endl
                   << "Elapsed time: " << elapsed_time << std::endl; 

         objective_functional_pointer->print_information();
      }

      // Set new parameters

      potential_parameters = parameters + parameters_increment;
      potential_parameters_norm = potential_parameters.calculate_norm();
   }
}


// void resize_training_history(int) method

/// This method resizes the vectors or matrices containing training history information 
/// to a new size:
///
/// <ul>
/// <li> Elapsed time history vector.
/// <li> Free parameters history matrix.
/// <li> Free parameters norm history vector. 
/// <li> Evaluation history vector.
/// </ul>
///
/// @param new_size Size of training history. 

void RandomSearch::resize_training_history(int new_size)
{
   // Potential parameters history 

   if(reserve_potential_parameters_history)
   {                                        
      potential_parameters_history.resize(new_size);
   }

   // Parameters history 

   if(reserve_parameters_history)
   {                                        
      parameters_history.resize(new_size);
   }

   // Potential parameters norm history 

   if(reserve_potential_parameters_norm_history)
   {
      potential_parameters_norm_history.resize(new_size);
   }

   // Parameters norm history 

   if(reserve_parameters_norm_history)
   {
      parameters_norm_history.resize(new_size);
   }

   // Potential evaluation history vector

   if(reserve_potential_evaluation_history)
   {
      potential_evaluation_history.resize(new_size);
   }

   // Evaluation history vector

   if(reserve_evaluation_history)
   {
      evaluation_history.resize(new_size);
   }

   // Elapsed time history vector

   if(reserve_elapsed_time_history)
   {
      elapsed_time_history.resize(new_size);
   }
}


// std::string get_training_history_XML(bool) method

std::string RandomSearch::get_training_history_XML(bool show_declaration)
{
   std::stringstream buffer;    // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='RandomSearch' content='TrainingHistory'>" << std::endl;
   }

   if(reserve_potential_parameters_history)
   {
      buffer << "<PotentialParametersHistory>" << std::endl
             << potential_parameters_history << std::endl     
             << "</PotentialParametersHistory>" << std::endl;
   }

   if(reserve_parameters_history)
   {
      buffer << "<ParametersHistory>" << std::endl
             << parameters_history << std::endl     
             << "</ParametersHistory>" << std::endl;
   }

   if(reserve_potential_parameters_norm_history)
   {
      buffer << "<PotentialParametersNormHistory>" << std::endl
             << potential_parameters_norm_history << std::endl     
             << "</PotentialParametersNormHistory>" << std::endl;
   }

   if(reserve_parameters_norm_history)
   {
      buffer << "<ParametersNormHistory>" << std::endl
             << parameters_norm_history << std::endl     
             << "</ParametersNormHistory>" << std::endl;
   }

   if(reserve_potential_evaluation_history)
   {
      buffer << "<PotentialEvaluationHistory>" << std::endl
             << potential_evaluation_history << std::endl     
             << "</PotentialEvaluationHistory>" << std::endl;
   }

   if(reserve_evaluation_history)
   {
      buffer << "<EvaluationHistory>" << std::endl
             << evaluation_history << std::endl     
             << "</EvaluationHistory>" << std::endl;
   }

   if(reserve_training_direction_history)
   {
      buffer << "<TrainingDirectionHistory>" << std::endl
             << training_direction_history << std::endl     
             << "</TrainingDirectionHistory>" << std::endl;
   }

   if(reserve_training_rate_history)
   {
      buffer << "<TrainingRateHistory>" << std::endl
             << training_rate_history << std::endl     
             << "</TrainingRateHistory>" << std::endl;
   }

   if(reserve_elapsed_time_history)
   {
      buffer << "<ElapsedTimeHistory>" << std::endl
             << elapsed_time_history << std::endl     
             << "</ElapsedTimeHistory>" << std::endl;
   }

   return(buffer.str());
}


// std::string to_XML(void) method

/// This method prints to the screen the training parameters, the stopping criteria
/// and other user stuff concerning the random search object.
/// @param show_declaration True if an XML-type declaration is to be included, false otherwise. 

std::string RandomSearch::to_XML(bool show_declaration)
{
   std::stringstream buffer;    // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='RandomSearch'>" << std::endl;
   }

   // Training parameters

   buffer << "<FirstTrainingRate>" << std::endl
          << first_training_rate << std::endl
          << "</FirstTrainingRate>" << std::endl;

   buffer << "<TrainingRateReductionPeriod>" << std::endl
          << training_rate_reduction_period << std::endl
          << "</TrainingRateReductionPeriod>" << std::endl;

   buffer << "<TrainingRateReductionFactor>" << std::endl
          << training_rate_reduction_factor << std::endl
          << "</TrainingRateReductionFactor>" << std::endl;

   buffer << "<WarningParametersNorm>" << std::endl
          << warning_parameters_norm << std::endl
          << "</WarningParametersNorm>" << std::endl;

   buffer << "<ErrorParametersNorm>" << std::endl
          << error_parameters_norm << std::endl
          << "</ErrorParametersNorm>" << std::endl;

   // Stopping criteria

   buffer << "<EvaluationGoal>" << std::endl
          << evaluation_goal << std::endl
          << "</EvaluationGoal>" << std::endl;

   buffer << "<MaximumEpochsNumber>" << std::endl
          << maximum_epochs_number << std::endl 
		  << "</MaximumEpochsNumber>" << std::endl;

   buffer << "<MaximumTime>" << std::endl
          << maximum_time << std::endl 
          << "</MaximumTime>" << std::endl;
  
   // Reserve training history

   buffer << "<ReservePotentialParametersHistory>" << std::endl
          << reserve_potential_parameters_history << std::endl 
          << "</ReservePotentialParametersHistory>" << std::endl;

   buffer << "<ReserveParametersHistory>" << std::endl
          << reserve_parameters_history << std::endl 
          << "</ReserveParametersHistory>" << std::endl;

   buffer << "<ReservePotentialParametersNormHistory>" << std::endl
          << reserve_potential_parameters_norm_history << std::endl 
		  << "</ReservePotentialParametersNormHistory>" << std::endl;

   buffer << "<ReserveParametersNormHistory>" << std::endl
          << reserve_parameters_norm_history << std::endl 
		  << "</ReserveParametersNormHistory>" << std::endl;

   buffer << "<ReservePotentialEvaluationHistory>" << std::endl
          << reserve_potential_evaluation_history << std::endl 
          << "</ReservePotentialEvaluationHistory>" << std::endl;

   buffer << "<ReserveEvaluationHistory>" << std::endl
          << reserve_evaluation_history << std::endl 
          << "</ReserveEvaluationHistory>" << std::endl;

   buffer << "<ReserveElapsedTimeHistory>" << std::endl
          << reserve_elapsed_time_history << std::endl 
          << "</ReserveElapsedTimeHistory>" << std::endl;

   // User stuff

   buffer << "<DisplayPeriod>" << std::endl
          << display_period << std::endl
		  << "</DisplayPeriod>" << std::endl;

   buffer << "<Display>" << std::endl
          << display << std::endl
		  << "</Display>" << std::endl;

   return(buffer.str());
}


// void load(const char*) method

/// This method loads a random search object from a data file. 
/// Please mind about the file format, wich is specified in the User's Guide. 
/// @param filename Filename.

void RandomSearch::load(const char* filename)
{
   // File

   std::fstream file;

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: RandomSearch class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open random search object data file."  << std::endl;

      exit(1);
   }

   std::string word;
   std::string line;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='RandomSearch'>") 
   {
//      std::cerr << "Flood Error: RandomSearch class." << std::endl
//                << "void load(const char*) method." << std::endl
//				<< "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   while(!file.eof())
   {
      file >> word; 

	  // Training parameters

	  if(word == "<FirstTrainingRate>")
	  {
		 double new_first_training_rate; 

         file >> new_first_training_rate;          

         file >> word;

		 if(word != "</FirstTrainingRate>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown first training rate end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_first_training_rate(new_first_training_rate);
	  }

	  if(word == "<TrainingRateReductionPeriod>")
	  {
		 int new_training_rate_reduction_period; 

         file >> new_training_rate_reduction_period;          

         file >> word;

		 if(word != "</TrainingRateReductionPeriod>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown training rate reduction period end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_training_rate_reduction_period(new_training_rate_reduction_period);
	  }

	  if(word == "<TrainingRateReductionFactor>")
	  {
		 double new_training_rate_reduction_factor; 

         file >> new_training_rate_reduction_factor;          

         file >> word;

		 if(word != "</TrainingRateReductionFactor>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown training rate reduction factor end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_training_rate_reduction_factor(new_training_rate_reduction_factor);
	  }

	  if(word == "<WarningParametersNorm>")
	  {
		 double new_warning_parameters_norm; 

         file >> new_warning_parameters_norm;          

         file >> word;

		 if(word != "</WarningParametersNorm>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown warning parameters norm end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_warning_parameters_norm(new_warning_parameters_norm);
	  }

	  else if(word == "<ErrorParametersNorm>")
	  {
		 double new_error_parameters_norm; 

         file >> new_error_parameters_norm;          

         file >> word;

		 if(word != "</ErrorParametersNorm>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown error parameters norm end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_error_parameters_norm(new_error_parameters_norm);
	  }

      // Stopping criteria

	  else if(word == "<EvaluationGoal>")
	  {
		 double new_evaluation_goal; 

         file >> new_evaluation_goal;          

         file >> word;

		 if(word != "</EvaluationGoal>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown evaluation goal end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_evaluation_goal(new_evaluation_goal);
	  }

	  else if(word == "<MaximumEpochsNumber>")
	  {
		 int new_maximum_epochs_number; 

         file >> new_maximum_epochs_number;          

         file >> word;

		 if(word != "</MaximumEpochsNumber>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown maximum epochs number end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_maximum_epochs_number(new_maximum_epochs_number);
	  }

	  else if(word == "<MaximumTime>")
	  {
		 double new_maximum_time; 

         file >> new_maximum_time;          

         file >> word;

		 if(word != "</MaximumTime>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown maximum time end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_maximum_time(new_maximum_time);
	  }

      // Training history 

	  else if(word == "<ReservePotentialParametersHistory>")
	  {
   	     bool new_reserve_potential_parameters_history; 

         file >> new_reserve_potential_parameters_history;          

         file >> word;

		 if(word != "</ReservePotentialParametersHistory>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve potential parameters history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_potential_parameters_history(new_reserve_potential_parameters_history);
	  }

	  else if(word == "<ReserveParametersHistory>")
	  {
   	     bool new_reserve_parameters_history; 

         file >> new_reserve_parameters_history;          

         file >> word;

		 if(word != "</ReserveParametersHistory>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve parameters history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_parameters_history(new_reserve_parameters_history);
	  }

	  else if(word == "<ReservePotentialParametersNormHistory>")
	  {
   	     bool new_reserve_potential_parameters_norm_history; 

         file >> new_reserve_potential_parameters_norm_history;          

         file >> word;

		 if(word != "</ReservePotentialParametersNormHistory>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve potential parameters norm history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_potential_parameters_norm_history(new_reserve_potential_parameters_norm_history);
	  }

	  else if(word == "<ReserveParametersNormHistory>")
	  {
   	     bool new_reserve_parameters_norm_history; 

         file >> new_reserve_parameters_norm_history;          

         file >> word;

		 if(word != "</ReserveParametersNormHistory>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve parameters norm history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_parameters_norm_history(new_reserve_parameters_norm_history);
	  }

	  else if(word == "<ReservePotentialEvaluationHistory>")
	  {
   	     bool new_reserve_potential_evaluation_history; 

         file >> new_reserve_potential_evaluation_history;          

         file >> word;

		 if(word != "</ReservePotentialEvaluationHistory>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve potential evaluation history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_potential_evaluation_history(new_reserve_potential_evaluation_history);
	  }

	  else if(word == "<ReserveEvaluationHistory>")
	  {
   	     bool new_reserve_evaluation_history; 

         file >> new_reserve_evaluation_history;          

         file >> word;

		 if(word != "</ReserveEvaluationHistory>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve evaluation history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_evaluation_history(new_reserve_evaluation_history);
	  }

	  else if(word == "<ReserveElapsedTimeHistory>")
	  {
   	     bool new_reserve_elapsed_time_history; 

         file >> new_reserve_elapsed_time_history;          

         file >> word;

		 if(word != "</ReserveElapsedTimeHistory>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve elapsed time history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_elapsed_time_history(new_reserve_elapsed_time_history);
	  }

	  // User stuff

	  else if(word == "<DisplayPeriod>")
	  {
		  int new_display_period; 

         file >> new_display_period;          

         file >> word;

		 if(word != "</DisplayPeriod>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown display period end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_display_period(new_display_period);
	  }

	  else if(word == "<Display>")
	  {
   	     bool new_display; 

         file >> new_display;          

         file >> word;

		 if(word != "</Display>") 
         {
            std::cerr << "Flood Error: RandomSearch class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown display end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_display(new_display);
	  }

	  else
	  {
         //std::cerr << "Flood Error: RandomSearch class." << std::endl
         //          << "void load(const char*) method." << std::endl
         //		   << "Unknown tag: " << word << std::endl;
         // 
         //exit(1);
 	  }
   }

   // Close file

   file.close();
}

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
