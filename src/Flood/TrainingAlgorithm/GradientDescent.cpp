/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   G R A D I E N T   D E S C E N T   C L A S S                                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#include "GradientDescent.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

namespace Flood
{

// GENERAL CONSTRUCTOR 

/// General constructor. It creates a gradient descent training algorithm object associated to an objective 
/// functional object.
/// It also initializes the class members to their default values:
///
/// Training operators:
/// <ul>
/// <li> Training rate method = Brent;
/// </ul>
///
/// Training parameters:
/// <ul>
/// <li> First training rate: 1.0.
/// <li> Bracketing factor: 2.0.
/// <li> Tolerance in training rate: 1.0e-3.
/// </ul>
///
/// Stopping criteria:
/// <ul> 
/// <li> Evaluation goal: -1.0e99.
/// <li> Gradient norm goal: 0.0.
/// <li> Maximum training time: 1.0e6.
/// <li> Maximum number of epochs: 100. 
/// </ul> 
///  
/// User stuff: 
/// <ul>
/// <li> Warning training rate: 1.0e6.
/// <li> Error training rate: 1.0e12.
/// <li> Display: true.
/// <li> Display period: 25.
/// </ul>
///
/// @param new_objective_functional_pointer Pointer to an objective functional object.

GradientDescent::GradientDescent(ObjectiveFunctional* new_objective_functional_pointer)
: TrainingAlgorithm(new_objective_functional_pointer)
{
}


// DEFAULT CONSTRUCTOR
//
/// Default constructor. It creates a gradient descent training algorithm object not associated to any objective 
/// functional object.
/// It also initializes the class members to their default values:
///
/// Training operators:
/// <ul>
/// <li> Training rate method = Brent;
/// </ul>
///
/// Training parameters:
/// <ul>
/// <li> First training rate: 1.0.
/// <li> Bracketing factor: 2.0.
/// <li> Tolerance in training rate: 1.0e-3.
/// </ul>
///
/// Stopping criteria:
/// <ul>
/// <li> Evaluation goal: -1.0e99.
/// <li> Gradient norm goal: 0.0.
/// <li> Maximum training time: 1.0e6.
/// <li> Maximum number of epochs: 100.
/// </ul>
///
/// User stuff:
/// <ul>
/// <li> Warning training rate: 1.0e6.
/// <li> Error training rate: 1.0e12.
/// <li> Display: true.
/// <li> Display period: 25.
/// </ul>

GradientDescent::GradientDescent(void) : TrainingAlgorithm()
{
}


// DESTRUCTOR

/// Destructor.

GradientDescent::~GradientDescent(void)
{
}


// METHODS

// void set_reserve_all_training_history(bool) method

/// This method makes the training history of all variables to reseved or not in memory:
/// <ul>
/// <li> Parameters.
/// <li> Parameters norm.
/// <li> Evaluation.
/// <li> Gradient. 
/// <li> Gradient norm. 
/// <li> Validation error. 
/// <li> Training direction.
/// <li> Training direction norm. 
/// <li> Training rate.
/// </ul>
/// @param new_reserve_all_training_history True if the training history of all variables is to be reserved, false otherwise.

void GradientDescent::set_reserve_all_training_history(bool new_reserve_all_training_history)
{
   // Multilayer perceptron

   reserve_parameters_history = new_reserve_all_training_history;
   reserve_parameters_norm_history = new_reserve_all_training_history;
   
   // Objective functional

   reserve_evaluation_history = new_reserve_all_training_history;
   reserve_gradient_history = new_reserve_all_training_history;
   reserve_gradient_norm_history = new_reserve_all_training_history;

   reserve_validation_error_history = new_reserve_all_training_history;

   // Training algorithm

   reserve_training_direction_history = new_reserve_all_training_history;
   reserve_training_rate_history = new_reserve_all_training_history;

   reserve_elapsed_time_history = new_reserve_all_training_history;
}


// Vector<double> calculate_training_direction(const Vector<double>&) method

Vector<double> GradientDescent::calculate_training_direction(const Vector<double>& gradient)
{
   double gradient_norm = gradient.calculate_norm();

   return(gradient*(-1.0)/gradient_norm);
}



// void train(void) method

/// This method trains a multilayer perceptron with an associated objective functional according to the gradient 
/// descent algorithm.
/// Training occurs according to the training operators, training parameters and stopping criteria.

void GradientDescent::train(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(objective_functional_pointer == NULL)
   {
      std::cerr << "Flood Error: GradientDescent class." << std::endl
                << "void train(void) method." << std::endl
                << "Pointer to objective functional object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   // Start training 

   if(display)
   {
      std::cout << "Training with gradient descent..." << std::endl;
   }

   // Multilayer perceptron stuff

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> parameters(parameters_number);
   double parameters_norm;

   Vector<double> parameters_increment(parameters_number);
   double parameters_increment_norm;

   // Objective functional stuff

   double validation_error = 0.0; 
   double old_validation_error = 0.0;
   double validation_error_increment = 0.0;
      
   double evaluation = 0.0;
   double old_evaluation = 0.0;
   double evaluation_improvement = 0.0;

   Vector<double> gradient(parameters_number);
   double gradient_norm;

   // Training algorithm stuff 

   Vector<double> training_direction(parameters_number);

   double initial_training_rate = 0.0;
   double training_rate = 0.0;
   double old_training_rate = 0.0;

   Vector<double> training_rate_evaluation(2);

   bool stop_training = false;

   time_t beginning_time, current_time;
   time(&beginning_time);
   double elapsed_time;

   resize_training_history(maximum_epochs_number+1);    // Main loop

   for(int epoch = 0; epoch <= maximum_epochs_number; epoch++)
   {
      // Multilayer perceptron stuff

      parameters = multilayer_perceptron_pointer->get_parameters();

      parameters_norm = parameters.calculate_norm();

      if(display && parameters_norm >= warning_parameters_norm)
      {
         std::cout << "Flood Warning: Parameters norm is " << parameters_norm << "." << std::endl;          
      }

      // Objective functional stuff
      
      if(epoch == 0)
      {      
         evaluation = objective_functional_pointer->calculate_evaluation();
         evaluation_improvement = 0.0; 
      }
      else
      {
         evaluation = training_rate_evaluation[1];
         evaluation_improvement = old_evaluation - evaluation; 
      }

      validation_error = objective_functional_pointer->calculate_validation_error();

      if(epoch == 0)
      {
         validation_error_increment = 0.0;
      }
      else 
      {
         validation_error_increment = validation_error - old_validation_error;
      }

      gradient = objective_functional_pointer->calculate_gradient();

      gradient_norm = gradient.calculate_norm();

      if(display && gradient_norm >= warning_gradient_norm)
      {
         std::cout << "Flood Warning: Gradient norm is " << gradient_norm << "." << std::endl;          
      }

      // Training algorithm 

      training_direction = calculate_training_direction(gradient);
                        
      if(epoch == 0)
      {
         initial_training_rate = first_training_rate;
      }
      else
      {
         initial_training_rate = old_training_rate;
      }    
      
	  training_rate_evaluation 
      = calculate_training_rate_evaluation(evaluation, training_direction, initial_training_rate);

      training_rate = training_rate_evaluation[0];

      parameters_increment = training_direction*training_rate;
      parameters_increment_norm = parameters_increment.calculate_norm();
      
      // Elapsed time

      time(&current_time);
      elapsed_time = difftime(current_time, beginning_time);

      // Training history multilayer perceptron 

      if(reserve_parameters_history)
      {
         parameters_history[epoch] = parameters;
      }

      if(reserve_parameters_norm_history)
      {
         parameters_norm_history[epoch] = parameters_norm; 
      }

      // Training history objective functional

      if(reserve_evaluation_history)
      {
         evaluation_history[epoch] = evaluation;
      }

      if(reserve_validation_error_history)
      {
         validation_error_history[epoch] = validation_error;
      }

      if(reserve_gradient_history)
      {
         gradient_history[epoch] = gradient;                                
      }

      if(reserve_gradient_norm_history)
      {
         gradient_norm_history[epoch] = gradient_norm;
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

      if(parameters_increment_norm <= minimum_parameters_increment_norm)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Minimum parameters increment norm reached." << std::endl;
            std::cout << "Parameters increment norm: " << parameters_increment_norm << std::endl;
         }

         stop_training = true;
      }

      else if(epoch != 0 && evaluation_improvement <= minimum_evaluation_improvement)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Minimum evaluation improvement reached." << std::endl
                      << "Evaluation improvement: " << evaluation_improvement << std::endl;
         }

         stop_training = true;
      }

      else if(evaluation <= evaluation_goal)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Evaluation goal reached." << std::endl;
         }

         stop_training = true;
      }

      else if(early_stopping && epoch != 0 && validation_error_increment > 0.0)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Validation error stopped improving." << std::endl;
            std::cout << "Validation error increment: " << validation_error_increment << std::endl;
         }

         stop_training = true;
      }

      else if(gradient_norm <= gradient_norm_goal)
      {
         if(display)
         {
            std::cout << "Epoch " << epoch << ": Gradient norm goal reached." << std::endl;  
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
            std::cout << "Parameters norm: " << parameters_norm << std::endl;
 
            std::cout << "Evaluation: " << evaluation << std::endl;
 
            if(validation_error != 0)
            {
               std::cout << "Validation error: " << validation_error << std::endl;
            }

            std::cout << "Gradient norm: " << gradient_norm << std::endl;

            objective_functional_pointer->print_information();

            std::cout << "Training rate: " << training_rate << std::endl
                      << "Elapsed time: " << elapsed_time << std::endl; 
		 }
    
         resize_training_history(1+epoch);

         break;
      }
      else if(display && epoch % display_period == 0)
      {
         std::cout << "Epoch " << epoch << ";" << std::endl;

         std::cout << "Parameters norm: " << parameters_norm << std::endl;
 
         std::cout << "Evaluation: " << evaluation << std::endl;
 
         if(validation_error != 0)
         {
            std::cout << "Validation error: " << validation_error << std::endl;
         }

         std::cout << "Gradient norm: " << gradient_norm << std::endl;

         objective_functional_pointer->print_information();

         std::cout << "Training rate: " << training_rate << std::endl
                   << "Elapsed time: " << elapsed_time << std::endl; 
      }

      // Set new parameters

      parameters += parameters_increment;

      multilayer_perceptron_pointer->set_parameters(parameters);

      // Update stuff

      old_evaluation = evaluation;
      old_validation_error = validation_error;
   
      old_training_rate = training_rate;
   } 

}


// std::string to_XML(bool) method

/// This method prints to the screen the training parameters, the stopping criteria and other user stuff 
/// concerning the gradient descent object.
/// @param show_declaration True if a XML-type declaration is wanted, false otherwise. 

std::string GradientDescent::to_XML(bool show_declaration)
{
   std::stringstream buffer;    // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='GradientDescent'>" << std::endl;
   }

   // Training operators

   buffer << "<TrainingRateMethod>" << std::endl
   	      << get_training_rate_method_name() << std::endl
          << "</TrainingRateMethod>" << std::endl;

   // Training parameters

   buffer << "<FirstTrainingRate> " << std::endl
          << first_training_rate << std::endl
		  << "</FirstTrainingRate> " << std::endl;

   buffer << "<TrainingRateTolerance>" << std::endl
          << training_rate_tolerance << std::endl
          << "</TrainingRateTolerance>" << std::endl;

   buffer << "<WarningParametersNorm>" << std::endl
          << warning_parameters_norm << std::endl
          << "</WarningParametersNorm>" << std::endl;

   buffer << "<WarningGradientNorm>" << std::endl
          << warning_gradient_norm << std::endl
          << "</WarningGradientNorm>" << std::endl;

   buffer << "<WarningTrainingRate>" << std::endl
          << warning_training_rate << std::endl
          << "</WarningTrainingRate>" << std::endl;

   buffer << "<ErrorParametersNorm>" << std::endl
          << error_parameters_norm << std::endl
          << "</ErrorParametersNorm>" << std::endl;

   buffer << "<ErrorGradientNorm>" << std::endl
          << error_gradient_norm << std::endl
          << "</ErrorGradientNorm>" << std::endl;

   buffer << "<ErrorTrainingRate>" << std::endl
          << error_training_rate << std::endl
          << "</ErrorTrainingRate>" << std::endl;

   // Stopping criteria

   buffer << "<MinimumParametersIncrementNorm>" << std::endl
          << minimum_parameters_increment_norm << std::endl
          << "</MinimumParametersIncrementNorm>" << std::endl;

   buffer << "<MinimumEvaluationImprovement>" << std::endl
          << minimum_evaluation_improvement << std::endl
          << "</MinimumEvaluationImprovement>" << std::endl;

   buffer << "<EvaluationGoal>" << std::endl
          << evaluation_goal << std::endl
          << "</EvaluationGoal>" << std::endl;

   buffer << "<EarlyStopping>" << std::endl
          << early_stopping << std::endl
          << "</EarlyStopping>" << std::endl;

   buffer << "<GradientNormGoal>" << std::endl
          << gradient_norm_goal << std::endl
          << "</GradientNormGoal>" << std::endl;

   buffer << "<MaximumEpochsNumber>" << std::endl
          << maximum_epochs_number << std::endl 
		  << "</MaximumEpochsNumber>" << std::endl;

   buffer << "<MaximumTime>" << std::endl
          << maximum_time << std::endl 
          << "</MaximumTime>" << std::endl;

   // Training history

   buffer << "<ReserveParametersHistory>" << std::endl
          << reserve_parameters_history << std::endl 
          << "</ReserveParametersHistory>" << std::endl;

   buffer << "<ReserveParametersNormHistory>" << std::endl
          << reserve_parameters_norm_history << std::endl 
		  << "</ReserveParametersNormHistory>" << std::endl;

   buffer << "<ReserveEvaluationHistory>" << std::endl
          << reserve_evaluation_history << std::endl 
          << "</ReserveEvaluationHistory>" << std::endl;

   buffer << "<ReserveGradientHistory>" << std::endl
          << reserve_gradient_history << std::endl
          << "</ReserveGradientHistory>" << std::endl;

   buffer << "<ReserveGradientNormHistory>" << std::endl
          << reserve_gradient_norm_history << std::endl 
          << "</ReserveGradientNormHistory>" << std::endl;

   buffer << "<ReserveValidationErrorHistory>" << std::endl
          << reserve_validation_error_history << std::endl 
          << "</ReserveValidationErrorHistory>" << std::endl;

   buffer << "<ReserveTrainingDirectionHistory>" << std::endl
          << reserve_training_direction_history << std::endl 
          << "</ReserveTrainingDirectionHistory>" << std::endl;

   buffer << "<ReserveTrainingRateHistory>"  << std::endl
          << reserve_training_rate_history << std::endl
          << "</ReserveTrainingRateHistory>"  << std::endl;

   buffer << "<ReserveElapsedTimeHistory>" << std::endl
          << reserve_elapsed_time_history << std::endl 
          << "</ReserveElapsedTimeHistory>" << std::endl;

   // User stuff

   buffer << "<Display>" << std::endl
          << display << std::endl
		  << "</Display>" << std::endl;

   buffer << "<DisplayPeriod>" << std::endl
          << display_period << std::endl
		  << "</DisplayPeriod>" << std::endl;

   return(buffer.str());
}


// std::string get_training_history_XML(bool) method

std::string GradientDescent::get_training_history_XML(bool show_declaration)
{
   std::stringstream buffer;    // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='GradientDescent' content='TrainingHistory'>" << std::endl;
   }

   if(reserve_parameters_history)
   {
      buffer << "<ParametersHistory>" << std::endl
             << parameters_history << std::endl     
             << "</ParametersHistory>" << std::endl;
   }

   if(reserve_parameters_norm_history)
   {
      buffer << "<ParametersNormHistory>" << std::endl
             << parameters_norm_history << std::endl     
             << "</ParametersNormHistory>" << std::endl;
   }

   if(reserve_evaluation_history)
   {
      buffer << "<EvaluationHistory>" << std::endl
             << evaluation_history << std::endl     
             << "</EvaluationHistory>" << std::endl;
   }

   if(reserve_gradient_history)
   {
      buffer << "<GradientHistory>" << std::endl
             << gradient_history << std::endl     
             << "</GradientHistory>" << std::endl;
   }

   if(reserve_gradient_norm_history)
   {
      buffer << "<GradientNormHistory>" << std::endl
             << gradient_norm_history << std::endl     
             << "</GradientNormHistory>" << std::endl;
   }

   if(reserve_validation_error_history)
   {
      buffer << "<ValidationErrorHistory>" << std::endl
             << validation_error_history << std::endl     
             << "</ValidationErrorHistory>" << std::endl;
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


// void load(const char*) method

/// This method loads a conjugate gradient object from an XML-type file. 
/// Please mind about the file format, wich is specified in the User's Guide. 
///
/// @param filename Name of conjugate gradient XML-type.

void GradientDescent::load(const char* filename)
{
   // File

   std::fstream file;

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: GradientDescent class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open conjugate gradient object XML-type file."  << std::endl;

      exit(1);
   }

   std::string word;
   std::string line;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='GradientDescent'>") 
   {
      std::cerr << "Flood Error: GradientDescent class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown file declaration: " << line << std::endl;
 
      exit(1);         
   }

   while(!file.eof())
   {
      file >> word; 

	  // Training operators

	  if(word == "<TrainingRateMethod>")
	  {
		 std::string new_training_rate_method; 

         file >> new_training_rate_method;          

         set_training_rate_method(new_training_rate_method);

         file >> word;

		 if(word != "</TrainingRateMethod>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown training rate method end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

	  // Training parameters

	  else if(word == "<BracketingFactor>")
	  {
		 double new_backeting_factor; 

         file >> new_backeting_factor;          

         set_bracketing_factor(new_backeting_factor);

         file >> word;

		 if(word != "</BracketingFactor>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown bracketing factor end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<FirstTrainingRate>")
	  {
		 double new_first_training_rate; 

         file >> new_first_training_rate;          

         set_first_training_rate(new_first_training_rate);

         file >> word;

		 if(word != "</FirstTrainingRate>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown first training rate end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<TrainingRateTolerance>")
	  {
		 double new_training_rate_tolerance; 

         file >> new_training_rate_tolerance;          

         set_training_rate_tolerance(new_training_rate_tolerance);

         file >> word;

		 if(word != "</TrainingRateTolerance>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown training rate tolerance end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<WarningTrainingRate>")
	  {
		 double new_warning_training_rate; 

         file >> new_warning_training_rate;          

         set_warning_training_rate(new_warning_training_rate);

         file >> word;

		 if(word != "</WarningTrainingRate>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown warning training rate end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<ErrorTrainingRate>")
	  {
		 double new_error_training_rate; 

         file >> new_error_training_rate;          

         set_error_training_rate(new_error_training_rate);

         file >> word;

		 if(word != "</ErrorTrainingRate>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown error training rate end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

      // Stopping criteria

	  else if(word == "<MinimumParametersIncrementNorm>")
	  {
		 double new_minimum_parameters_increment_norm; 

         file >> new_minimum_parameters_increment_norm;          

         set_minimum_parameters_increment_norm(new_minimum_parameters_increment_norm);

         file >> word;

		 if(word != "</MinimumParametersIncrementNorm>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown minimum parameters increment norm end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<MinimumEvaluationImprovement>")
	  {
		 double new_minimum_evaluation_improvement; 

         file >> new_minimum_evaluation_improvement;          

         set_minimum_evaluation_improvement(new_minimum_evaluation_improvement);

         file >> word;

		 if(word != "</MinimumEvaluationImprovement>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown minimum evaluation improvement end tag: " << word << std::endl;
 
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
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown evaluation goal end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<GradientNormGoal>")
	  {
		 double new_gradient_norm_goal; 

         file >> new_gradient_norm_goal;          

         set_gradient_norm_goal(new_gradient_norm_goal);

         file >> word;

		 if(word != "</GradientNormGoal>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown gradient norm goal end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<MaximumEpochsNumber>")
	  {
		 int new_maximum_epochs_number; 

         file >> new_maximum_epochs_number;          

         set_maximum_epochs_number(new_maximum_epochs_number);

         file >> word;

		 if(word != "</MaximumEpochsNumber>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown maximum epochs number end tag: " << word << std::endl;
 
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
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown maximum time end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<EarlyStopping>")
	  {
   	     bool new_early_stopping; 

         file >> new_early_stopping;          

         set_early_stopping(new_early_stopping);

         file >> word;

		 if(word != "</EarlyStopping>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown early stopping end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

      // Training history 

	  else if(word == "<ReserveParametersHistory>")
	  {
   	     bool new_reserve_parameters_history; 

         file >> new_reserve_parameters_history;          

         set_reserve_parameters_history(new_reserve_parameters_history);

         file >> word;

		 if(word != "</ReserveParametersHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve parameters history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<ReserveParametersNormHistory>")
	  {
   	     bool new_reserve_parameters_norm_history; 

         file >> new_reserve_parameters_norm_history;          

         set_reserve_parameters_norm_history(new_reserve_parameters_norm_history);

         file >> word;

		 if(word != "</ReserveParametersNormHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve parameters norm history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<ReserveEvaluationHistory>")
	  {
   	     bool new_reserve_evaluation_history; 

         file >> new_reserve_evaluation_history;          

         set_reserve_evaluation_history(new_reserve_evaluation_history);

         file >> word;

		 if(word != "</ReserveEvaluationHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve evaluation history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<ReserveGradientHistory>")
	  {
   	     bool new_reserve_gradient_history; 

         file >> new_reserve_gradient_history;          

         set_reserve_gradient_history(new_reserve_gradient_history);

         file >> word;

		 if(word != "</ReserveGradientHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve gradient history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<ReserveGradientNormHistory>")
	  {
   	     bool new_reserve_gradient_norm_history; 

         file >> new_reserve_gradient_norm_history;          

         set_reserve_gradient_norm_history(new_reserve_gradient_norm_history);

         file >> word;

		 if(word != "</ReserveGradientNormHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve gradient norm history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<ReserveTrainingDirectionHistory>")
	  {
   	     bool new_reserve_training_direction_history; 

         file >> new_reserve_training_direction_history;          

         set_reserve_training_direction_history(new_reserve_training_direction_history);

         file >> word;

		 if(word != "</ReserveTrainingDirectionHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve training direction history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

	  else if(word == "<ReserveTrainingRateHistory>")
	  {
   	     bool new_reserve_training_rate_history; 

         file >> new_reserve_training_rate_history;          

         set_reserve_training_rate_history(new_reserve_training_rate_history);

         file >> word;

		 if(word != "</ReserveTrainingRateHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve training rate history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

	  else if(word == "<ReserveElapsedTimeHistory>")
	  {
   	     bool new_reserve_elapsed_time_history; 

         file >> new_reserve_elapsed_time_history;          

         set_reserve_elapsed_time_history(new_reserve_elapsed_time_history);

         file >> word;

		 if(word != "</ReserveElapsedTimeHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve elapsed time history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

	  else if(word == "<ReserveValidationErrorHistory>")
	  {
   	     bool new_reserve_validation_error_history; 

         file >> new_reserve_validation_error_history;          

         set_reserve_validation_error_history(new_reserve_validation_error_history);

         file >> word;

		 if(word != "</ReserveValidationErrorHistory>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve validation error history end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

	  // User stuff

	  else if(word == "<Display>")
	  {
   	     bool new_display; 

         file >> new_display;          

         set_display(new_display);

         file >> word;

		 if(word != "</Display>") 
         {
            std::cerr << "Flood Error: GradientDescent class." << std::endl
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
            std::cerr << "Flood Error: GradientDescent class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown display period end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else
	  {
	  
	  }
   }

   // Close file

   file.close();
}


// void resize_training_history(int) method

/// This method resizes the vectors or matrices containing training history information to a new size:
///
/// <ul>
/// <li> Elapsed time history vector.
/// <li> Free parameters history matrix.
/// <li> Free parameters norm history vector. 
/// <li> Evaluation history vector.
/// <li> Gradient history matrix.
/// <li> Gradient norm history vector. 
/// <li> Training direction history matrix.
/// <li> Training direction norm history vector
/// <li> Training rate history vector. 
/// </ul>
///
/// @param new_size Size of training history. 

void GradientDescent::resize_training_history(int new_size)
{
   // Free parameters history matrix

   if(reserve_parameters_history)
   {
      parameters_history.resize(new_size);
   }

   // Free parameters norm history vector

   if(reserve_parameters_norm_history)
   {
      parameters_norm_history.resize(new_size);
   }

   // Evaluation history vector

   if(reserve_evaluation_history)
   {
      evaluation_history.resize(new_size);
   }

   // Validation error vector

   if(reserve_validation_error_history)
   {
      validation_error_history.resize(new_size);
   }

   // Gradient history matrix

   if(reserve_gradient_history)
   {
      gradient_history.resize(new_size);
   }
 
   // Gradient norm history vector

   if(reserve_gradient_norm_history)
   {
      gradient_norm_history.resize(new_size);
   }

   // Training direction history matrix

   if(reserve_training_direction_history)
   {
      training_direction_history.resize(new_size);
   }

   // Training rate history vector

   if(reserve_training_rate_history)
   {
      training_rate_history.resize(new_size);
   }

   // Elapsed time history vector

   if(reserve_elapsed_time_history)
   {
      elapsed_time_history.resize(new_size);
   }
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

