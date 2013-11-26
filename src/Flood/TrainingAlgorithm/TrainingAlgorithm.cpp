/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   T R A I N I N G   A L G O R I T H M   C L A S S                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

#include "TrainingAlgorithm.h"

namespace Flood
{

// GENERAL CONSTRUCTOR

/// General constructor. It creates a training algorithm object associated to an objective functional object.
/// @param new_objective_functional_pointer Pointer to an objective functional object.

TrainingAlgorithm::TrainingAlgorithm(ObjectiveFunctional* new_objective_functional_pointer)
{
   objective_functional_pointer = new_objective_functional_pointer;

   set_default();
}


// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a training algorithm object not associated to any objective functional object.  

TrainingAlgorithm::TrainingAlgorithm(void)
{ 
   objective_functional_pointer = NULL;

   set_default();
}


// DESTRUCTOR 

/// Destructor

TrainingAlgorithm::~TrainingAlgorithm(void)
{ 
}


// METHODS

// ObjectiveFunctional* get_objective_functional_pointer(void) method

/// This method returns a pointer to the objective functional object to which the training algorithm is 
/// associated.

ObjectiveFunctional* TrainingAlgorithm::get_objective_functional_pointer(void)
{
   return(objective_functional_pointer);
}


// TrainingRateMethod get_training_rate_method(void) method

/// This method returns the training rate method used for training.

TrainingAlgorithm::TrainingRateMethod TrainingAlgorithm::get_training_rate_method(void)
{
   return(training_rate_method);
}


// std::string get_training_rate_method_name(void) method

/// This method returns a string with the name of the training rate method to be used. 

std::string TrainingAlgorithm::get_training_rate_method_name(void)
{
   switch(training_rate_method)
   {
      case Fixed:
      {
         return("Fixed");
	  }
      break;

      case GoldenSection:
      {
         return("GoldenSection");
	  }
      break;

      case BrentMethod:
      {
         return("BrentMethod");
	  }
      break;

	  default:
      {
         std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                   << "std::string get_training_rate_method(void) method." << std::endl
                   << "Unknown training rate method." << std::endl;
 
         exit(1);
	  }
      break;
   }
}


// double get_first_training_rate(void) method

/// This method returns the initial training rate value in line minimization.

double TrainingAlgorithm::get_first_training_rate(void)
{
   return(first_training_rate);
}


// double get_bracketing_factor(void) method

/// This method returns the increase factor when bracketing a minimum in line minimization. 

double TrainingAlgorithm::get_bracketing_factor(void)
{
   return(bracketing_factor);       
}


// double get_training_rate_tolerance(void) method

/// This method returns the tolerance value in line minimization.

double TrainingAlgorithm::get_training_rate_tolerance(void)
{
   return(training_rate_tolerance);
}


// double get_warning_parameters_norm(void) method

/// This method returns the minimum value for the norm of the parameters vector at wich a warning message is 
/// written to the screen. 

double TrainingAlgorithm::get_warning_parameters_norm(void)
{
   return(warning_parameters_norm);       
}


// double get_warning_gradient_norm(void) method

/// This method returns the minimum value for the norm of the gradient vector at wich a warning message is written
/// to the screen. 

double TrainingAlgorithm::get_warning_gradient_norm(void)
{
   return(warning_gradient_norm);       
}


// double get_warning_training_rate(void) method

/// This method returns the training rate value at wich a warning message is written to the screen during line 
/// minimization.

double TrainingAlgorithm::get_warning_training_rate(void)
{
   return(warning_training_rate);
}


// double get_error_parameters_norm(void) method

/// This method returns the value for the norm of the parameters vector at wich an error message is 
/// written to the screen and the program exits. 

double TrainingAlgorithm::get_error_parameters_norm(void)
{
   return(error_parameters_norm);
}


// double get_error_gradient_norm(void) method

/// This method returns the value for the norm of the gradient vector at wich an error message is written
/// to the screen and the program exits. 

double TrainingAlgorithm::get_error_gradient_norm(void)
{
   return(error_gradient_norm);
}


// double get_error_training_rate(void) method

/// This method returns the training rate value at wich the line minimization algorithm is assumed to fail when 
/// bracketing a minimum.

double TrainingAlgorithm::get_error_training_rate(void)
{
   return(error_training_rate);
}


// double get_minimum_parameters_increment_norm(void) void

/// This method returns the minimum norm of the parameter increment vector used as a stopping criteria when training. 

double TrainingAlgorithm::get_minimum_parameters_increment_norm(void)
{
   return(minimum_parameters_increment_norm);
}


// double get_minimum_evaluation_improvement(void) method

/// This method returns the minimum evaluation improvement during training.  

double TrainingAlgorithm::get_minimum_evaluation_improvement(void)
{
   return(minimum_evaluation_improvement);
}


// double get_evaluation_goal(void) method

/// This method returns the goal value for the evaluation. 
/// This is used as a stopping criterium when training a neural network.

double TrainingAlgorithm::get_evaluation_goal(void)
{
   return(evaluation_goal);
}


// double get_gradient_norm_goal(void) method

/// This method returns the goal value for the norm of the objective function gradient.
/// This is used as a stopping criterium when training a neural network.

double TrainingAlgorithm::get_gradient_norm_goal(void)
{
   return(gradient_norm_goal);
}


// int get_maximum_epochs_number(void) method

/// This method returns the maximum number of epochs for training.

int TrainingAlgorithm::get_maximum_epochs_number(void)
{
   return(maximum_epochs_number);
}


// double get_maximum_time(void) method

/// This method returns the maximum training time.  

double TrainingAlgorithm::get_maximum_time(void)
{
   return(maximum_time);
}


// bool get_early_stopping(void) method

/// This method returns true if early stopping is to be performed during training, and false otherwise. 

bool TrainingAlgorithm::get_early_stopping(void)
{
   return(early_stopping);
}


// bool get_reserve_parameters_history(void) method

/// This method returns true if the parameters history matrix is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_parameters_history(void)
{
   return(reserve_parameters_history);     
}


// bool get_reserve_parameters_norm_history(void) method 

/// This method returns true if the parameters norm history vector is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_parameters_norm_history(void)
{
   return(reserve_parameters_norm_history);     
}


// bool get_reserve_evaluation_history(void) method

/// This method returns true if the evaluation history vector is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_evaluation_history(void)
{
   return(reserve_evaluation_history);     
}


// bool get_reserve_gradient_history(void) method

/// This method returns true if the gradient history matrix is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_gradient_history(void)
{
   return(reserve_gradient_history);     
}


// bool get_reserve_gradient_norm_history(void) method

/// This method returns true if the gradient norm history vector is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_gradient_norm_history(void)
{
   return(reserve_gradient_norm_history);     
}


// bool get_reserve_inverse_Hessian_history(void) method

bool TrainingAlgorithm::get_reserve_inverse_Hessian_history(void)
{
   return(reserve_inverse_Hessian_history);
}


// bool get_reserve_training_direction_history(void) method

/// This method returns true if the training direction history matrix is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_training_direction_history(void)
{
   return(reserve_training_direction_history);     
}


// bool get_reserve_training_rate_history(void) method

/// This method returns true if the training rate history vector is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_training_rate_history(void)
{
   return(reserve_training_rate_history);     
}


// bool get_reserve_elapsed_time_history(void) method

/// This method returns true if the elapsed time history vector is to be reserved, and false otherwise.

bool TrainingAlgorithm::get_reserve_elapsed_time_history(void)
{
   return(reserve_elapsed_time_history);     
}


// bool get_reserve_validation_error_history(void) method

bool TrainingAlgorithm::get_reserve_validation_error_history(void)
{
   return(reserve_validation_error_history);
}


// Vector< Vector<double> >& get_parameters_history(void) method

/// This method returns a matrix containing the parameters history over the training epochs.

Vector< Vector<double> >& TrainingAlgorithm::get_parameters_history(void)
{
   return(parameters_history);     
}


// Vector<double> get_parameters_norm_history(void) method

/// This method returns a vector containing the parameters norm history over the training epochs.

Vector<double>& TrainingAlgorithm::get_parameters_norm_history(void)
{
   return(parameters_norm_history);     
}


// Vector<double> get_evaluation_history(void) method

/// This method returns a vector containing the evaluations history over the training epochs.

Vector<double>& TrainingAlgorithm::get_evaluation_history(void)
{
   return(evaluation_history);     
}


// Vector< Vector<double> >& get_gradient_history(void) method

/// This method returns a matrix containing the gradient history over the training epochs.

Vector< Vector<double> >& TrainingAlgorithm::get_gradient_history(void)
{
   return(gradient_history);     
}


// Vector<double> get_gradient_norm_history(void) method

/// This method returns a vector containing the gradient norm history over the training epochs.

Vector<double>& TrainingAlgorithm::get_gradient_norm_history(void)
{
   return(gradient_norm_history);     
}


// Vector< Matrix<double> >& get_inverse_Hessian_history(void) method

Vector< Matrix<double> >& TrainingAlgorithm::get_inverse_Hessian_history(void)
{
   return(inverse_Hessian_history);
}


// Vector< Vector<double> >& get_training_direction_history(void) method

/// This method returns the training direction history matrix. 

Vector< Vector<double> >& TrainingAlgorithm::get_training_direction_history(void)
{
   return(training_direction_history);               
}


// Vector<double> get_training_rate_history(void) method

/// This method returns the training rate history vector. 

Vector<double>& TrainingAlgorithm::get_training_rate_history(void)
{
   return(training_rate_history);               
}


// Vector<double> get_elapsed_time_history(void) method

/// This method returns a matrix containing the elapsed time history over the training epochs.

Vector<double>& TrainingAlgorithm::get_elapsed_time_history(void) 
{
   return(elapsed_time_history);     
}


// Vector<double> get_validation_error_history(void) method

Vector<double>& TrainingAlgorithm::get_validation_error_history(void)
{
   return(validation_error_history);
}


// int get_display_period(void) method

/// This method returns the number of epochs between the training showing progress. 

int TrainingAlgorithm::get_display_period(void)
{
   return(display_period);
}


// bool get_display(void) method

/// This method returns true if messages from this class can be displayed on the screen, or false if messages from
/// this class can't be displayed on the screen.

bool TrainingAlgorithm::get_display(void)
{
   return(display);
}


// void set(void) method

/// This method sets the objective functional pointer to NULL.
/// It also sets the rest of members to their default values. 

void TrainingAlgorithm::set(void)
{
   objective_functional_pointer = NULL;
   set_default();
}


// void set(ObjectiveFunctional*) method

/// This method sets a new objective functional pointer.
/// It also sets the rest of members to their default values. 
/// @param new_objective_functional_pointer Pointer to an objective functional object. 

void TrainingAlgorithm::set(ObjectiveFunctional* new_objective_functional_pointer)
{
   objective_functional_pointer = new_objective_functional_pointer;
   set_default();
}


// void set_default(void) method 

/// This method sets the members of the training algorithm object to their default values:
/// <ul>
/// <li> Training rate method: Brent method
/// <li> Bracketing factor: 1.5
/// <li> First training rate: 1.0e-2
/// <li> Training rate tolerance: 1.0e-3
/// <li> Warning parameters norm: 1.0e6
/// <li> Warning gradient norm: 1.0e6 
/// <li> Warning training rate: 1.0e6
/// <li> Error parameters norm: 1.0e9
/// <li> Error gradient norm: 1.0e9 
/// <li> Error training rate: 1.0e9
/// <li> Minimum parameters increment norm: 0.0
/// <li> Minimum evaluation improvement: 0.0
/// <li> Evaluation goal: -Inf
/// <li> Gradient norm goal: 0.0
/// <li> Early stopping: False
/// <li> Maximum epochs number: 1000
/// <li> Maximum time: 1000 
/// <li> Reserve parameters history: False
/// <li> Reserve parameters norm history: False
/// <li> Reserve evaluation history: False
/// <li> Reserve gradient history: False
/// <li> Reserve gradient norm history: False
/// <li> Reserve inverse Hessian history: False
/// <li> Reserve validation error history: False
/// <li> Reserve training direction history: False
/// <li> Reserve training direction norm history: False
/// <li> Reserve training rate history: False
/// <li> Reserve elapsed time history: False
/// <li> Display: True
/// <li> Display period: 100
/// </ul>

void TrainingAlgorithm::set_default(void)
{
   // TRAINING OPERATORS

   training_rate_method = BrentMethod;

   // TRAINING PARAMETERS

   bracketing_factor = 1.5;
   first_training_rate = 1.0e-2;
   training_rate_tolerance = 1.0e-6;

   warning_parameters_norm = 1.0e6;
   warning_gradient_norm = 1.0e6;   
   warning_training_rate = 1.0e6;

   error_parameters_norm = 1.0e9;
   error_gradient_norm = 1.0e9;
   error_training_rate = 1.0e9;

   // STOPPING CRITERIA

   minimum_parameters_increment_norm = 0.0;

   minimum_evaluation_improvement = 0.0;
   evaluation_goal = -1.0e99;
   gradient_norm_goal = 0.0;
   early_stopping = false;

   maximum_epochs_number = 1000;
   maximum_time = 1000.0;

   // TRAINING HISTORY

   reserve_parameters_history = false;
   reserve_parameters_norm_history = false;

   reserve_evaluation_history = false;
   reserve_gradient_history = false;
   reserve_gradient_norm_history = false;
   reserve_inverse_Hessian_history = false;
   reserve_validation_error_history = false;

   reserve_training_direction_history = false;
   reserve_training_rate_history = false;
   reserve_elapsed_time_history = false;

   // UTILITIES

   display = true;
   display_period = 100;
}


// void set_objective_functional_pointer(ObjectiveFunctional*) method

/// This method sets a pointer to an objective functional object to be associated to the training algorithm.
/// @param new_objective_functional_pointer Pointer to an objective functional object.

void TrainingAlgorithm::set_objective_functional_pointer(ObjectiveFunctional* new_objective_functional_pointer)
{
   objective_functional_pointer = new_objective_functional_pointer;
}


// void set_training_rate_method(TrainingRateMethod) method

/// This method sets a new training rate method to be used for training.
/// @param new_training_rate_method Training rate method.

void TrainingAlgorithm::set_training_rate_method(const TrainingAlgorithm::TrainingRateMethod& new_training_rate_method)
{
   training_rate_method = new_training_rate_method;
}


// void set_training_rate_method(const std::string&) method

/// This method sets the method for obtaining the training rate from a string with the name of the method. 
/// @param new_training_rate_method_name Name of training rate method

void TrainingAlgorithm::set_training_rate_method(const std::string& new_training_rate_method_name)
{
   if(new_training_rate_method_name == "Fixed")
   {
      training_rate_method = Fixed;
   }
   else if(new_training_rate_method_name == "GoldenSection")
   {
      training_rate_method = GoldenSection;
   }
   else if(new_training_rate_method_name == "BrentMethod")
   {
      training_rate_method = BrentMethod;
   }
   else
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_training_rate_method(const std::string&) method." << std::endl
				<< "Unknown training rate method name: " << new_training_rate_method_name << "." <<std::endl;
   
      exit(1);   
   }
}


// void set_first_training_rate(double) method

/// This method sets a new value to be used as an initial training rate in line  minimization.
/// @param new_first_training_rate Initial training rate value.

void TrainingAlgorithm::set_first_training_rate(double new_first_training_rate)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
     
   if(new_first_training_rate < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_first_training_rate(double) method." << std::endl
                << "First training rate must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set first training rate

   first_training_rate = new_first_training_rate;
}


// void set_bracketing_factor(double) method

/// This method sets a new increase factor value to be used for line minimization when bracketing a minimum.
/// @param new_bracketing_factor Bracketing factor value.

void TrainingAlgorithm::set_bracketing_factor(double new_bracketing_factor)
{ 
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_bracketing_factor < 0.0) 
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_bracketing_factor(double) method." << std::endl
                << "Bracketing factor must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   bracketing_factor = new_bracketing_factor;
}


// void set_training_rate_tolerance(double) method

/// This method sets a new tolerance value to be used in line minimization.
/// @param new_training_rate_tolerance Tolerance value in line minimization.

void TrainingAlgorithm::set_training_rate_tolerance(double new_training_rate_tolerance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
                                      
   if(new_training_rate_tolerance < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_training_rate_tolerance(double) method." << std::endl
                << "Tolerance must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set training rate tolerance

   training_rate_tolerance = new_training_rate_tolerance;
}


// void set_warning_parameters_norm(double) method

/// This method sets a new value for the parameters vector norm at which a warning message is written to the 
/// screen. 
/// @param new_warning_parameters_norm Warning norm of parameters vector value. 

void TrainingAlgorithm::set_warning_parameters_norm(double new_warning_parameters_norm)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_warning_parameters_norm < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_warning_parameters_norm(double) method." << std::endl
                << "Warning parameters norm must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set warning parameters norm

   warning_parameters_norm = new_warning_parameters_norm;     
}


// void set_warning_gradient_norm(double) method

/// This method sets a new value for the gradient vector norm at which 
/// a warning message is written to the screen. 
/// @param new_warning_gradient_norm Warning norm of gradient vector value. 

void TrainingAlgorithm::set_warning_gradient_norm(double new_warning_gradient_norm)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_warning_gradient_norm < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_warning_gradient_norm(double) method." << std::endl
                << "Warning gradient norm must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set warning gradient norm

   warning_gradient_norm = new_warning_gradient_norm;     
}


// void set_warning_training_rate(double) method

/// This method sets a new training rate value at wich a warning message is written to the screen during line 
/// minimization.
/// @param new_warning_training_rate Warning training rate value.

void TrainingAlgorithm::set_warning_training_rate(double new_warning_training_rate)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_warning_training_rate < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl 
                << "void set_warning_training_rate(double) method." << std::endl
                << "Warning training rate must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   warning_training_rate = new_warning_training_rate;
}


// void set_error_parameters_norm(double) method

/// This method sets a new value for the parameters vector norm at which an error message is written to the 
/// screen and the program exits. 
/// @param new_error_parameters_norm Error norm of parameters vector value. 

void TrainingAlgorithm::set_error_parameters_norm(double new_error_parameters_norm)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_error_parameters_norm < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_error_parameters_norm(double) method." << std::endl
                << "Error parameters norm must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set error parameters norm

   error_parameters_norm = new_error_parameters_norm;
}


// void set_error_gradient_norm(double) method

/// This method sets a new value for the gradient vector norm at which an error message is written to the screen 
/// and the program exits. 
/// @param new_error_gradient_norm Error norm of gradient vector value. 

void TrainingAlgorithm::set_error_gradient_norm(double new_error_gradient_norm)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_error_gradient_norm < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_error_gradient_norm(double) method." << std::endl
                << "Error gradient norm must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set error gradient norm

   error_gradient_norm = new_error_gradient_norm;
}


// void set_error_training_rate(double) method

/// This method sets a new training rate value at wich a the line minimization algorithm is assumed to fail when 
/// bracketing a minimum.
/// @param new_error_training_rate Error training rate value.

void TrainingAlgorithm::set_error_training_rate(double new_error_training_rate)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_error_training_rate < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_error_training_rate(double) method." << std::endl
                << "Error training rate must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set error training rate

   error_training_rate = new_error_training_rate;
}


// void set_minimum_parameters_increment_norm(double) method

/// This method sets a new value for the minimum parameters increment norm stopping criterium. 
/// @param new_minimum_parameters_increment_norm Value of norm of parameters increment norm used to stop training. 

void TrainingAlgorithm::set_minimum_parameters_increment_norm(double new_minimum_parameters_increment_norm)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_minimum_parameters_increment_norm < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void new_minimum_parameters_increment_norm(double) method." << std::endl
                << "Minimum parameters increment norm must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set error training rate

   minimum_parameters_increment_norm = new_minimum_parameters_increment_norm;
}


// void set_minimum_evaluation_improvement(double) method

/// This method sets a new minimum evaluation improvement during training.  
/// @param new_minimum_evaluation_improvement Minimum improvement in the evaluation between two epochs.

void TrainingAlgorithm::set_minimum_evaluation_improvement(double new_minimum_evaluation_improvement)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_minimum_evaluation_improvement < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_minimum_evaluation_improvement(double) method." << std::endl
                << "Minimum evaluation improvement must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set minimum evaluation improvement

   minimum_evaluation_improvement = new_minimum_evaluation_improvement;
}


// void set_evaluation_goal(double) method

/// This method sets a new goal value for the evaluation. 
/// This is used as a stopping criterium when training a neural network.
/// @param new_evaluation_goal Goal value for the evaluation.

void TrainingAlgorithm::set_evaluation_goal(double new_evaluation_goal)
{
   evaluation_goal = new_evaluation_goal;
}


// void set_gradient_norm_goal(double) method

/// This method sets a new the goal value for the norm of the objective function gradient. 
/// This is used as a stopping criterium when training a neural network.
/// @param new_gradient_norm_goal Goal value for the norm of the objective function gradient.

void TrainingAlgorithm::set_gradient_norm_goal(double new_gradient_norm_goal)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_gradient_norm_goal < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_gradient_norm_goal(double) method." << std::endl
                << "Gradient norm goal must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set gradient norm goal

   gradient_norm_goal = new_gradient_norm_goal;
}


// void set_maximum_epochs_number(int) method

/// This method sets a maximum number of epochs for training.
/// @param new_maximum_epochs_number Maximum number of epochs for training.

void TrainingAlgorithm::set_maximum_epochs_number(int new_maximum_epochs_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_maximum_epochs_number < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_maximum_epochs_number(int) method." << std::endl
                << "Number of epochs must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set maximum epochs number

   maximum_epochs_number = new_maximum_epochs_number;
}


// void set_maximum_time(double) method

/// This method sets a new maximum training time.  
/// @param new_maximum_time Maximum training time.

void TrainingAlgorithm::set_maximum_time(double new_maximum_time)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_maximum_time < 0.0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void set_maximum_time(double) method." << std::endl
                << "Maximum time must be equal or greater than 0." << std::endl;

      exit(1);
   }
   
   #endif

   // Set maximum time

   maximum_time = new_maximum_time;
}


// void set_early_stopping(bool) method

/// This method activates or not early stopping in the training process.
/// @param new_early_stopping True if early stopping is to be performed, false otherwise. 

void TrainingAlgorithm::set_early_stopping(bool new_early_stopping)
{
   early_stopping = new_early_stopping;
}


// void set_reserve_parameters_history(bool) method

/// This method makes the parameters history vector of vectors to be reseved or not in memory.
/// @param new_reserve_parameters_history True if the parameters history matrix is to be reserved, false 
/// otherwise.

void TrainingAlgorithm::set_reserve_parameters_history(bool new_reserve_parameters_history)
{
   reserve_parameters_history = new_reserve_parameters_history;     
}


// void set_reserve_parameters_norm_history(bool) method

/// This method makes the parameters norm history vector to be reseved or not in memory.
/// @param new_reserve_parameters_norm_history True if the parameters norm history vector is to be reserved, 
/// false otherwise.

void TrainingAlgorithm::set_reserve_parameters_norm_history(bool new_reserve_parameters_norm_history)
{
   reserve_parameters_norm_history = new_reserve_parameters_norm_history;     
}


// void set_reserve_evaluation_history(bool) method

/// This method makes the evaluation history vector to be reseved or not in memory.
/// @param new_reserve_evaluation_history True if the evaluation history vector is to be reserved, false otherwise.

void TrainingAlgorithm::set_reserve_evaluation_history(bool new_reserve_evaluation_history)
{
   reserve_evaluation_history = new_reserve_evaluation_history;     
}


// void set_reserve_gradient_history(bool) method

/// This method makes the gradient history vector of vectors to be reseved or not in memory.
/// @param new_reserve_gradient_history True if the gradient history matrix is to be reserved, false otherwise.

void TrainingAlgorithm::set_reserve_gradient_history(bool new_reserve_gradient_history)
{
   reserve_gradient_history = new_reserve_gradient_history;    
}


// void set_reserve_gradient_norm_history(bool) method

/// This method makes the gradient norm history vector to be reseved or not in memory.
/// @param new_reserve_gradient_norm_history True if the gradient norm history matrix is to be reserved, false 
/// otherwise.

void TrainingAlgorithm::set_reserve_gradient_norm_history(bool new_reserve_gradient_norm_history)
{
   reserve_gradient_norm_history = new_reserve_gradient_norm_history;     
}


// void set_reserve_inverse_Hessian_history(bool) method

/// This method sets the history of the inverse of the Hessian matrix to be reserved or not in memory.
/// This is a vector of matrices. 
/// @param new_reserve_inverse_Hessian_history True if the inverse Hessian history is to be reserved, false otherwise. 

void TrainingAlgorithm::set_reserve_inverse_Hessian_history(bool new_reserve_inverse_Hessian_history)
{
   reserve_inverse_Hessian_history = new_reserve_inverse_Hessian_history;
}


// void set_reserve_training_direction_history(bool) method

/// This method makes the training direction history vector of vectors to be reseved or not in memory.
/// @param new_reserve_training_direction_history True if the training direction history matrix is to be reserved, 
/// false otherwise.

void TrainingAlgorithm::set_reserve_training_direction_history(bool new_reserve_training_direction_history)
{
   reserve_training_direction_history = new_reserve_training_direction_history;          
}


// void set_reserve_training_rate_history(bool) method

/// This method makes the training rate history vector to be reseved or not in memory.
/// @param new_reserve_training_rate_history True if the training rate history vector is to be reserved, false 
/// otherwise.

void TrainingAlgorithm::set_reserve_training_rate_history(bool new_reserve_training_rate_history)
{
   reserve_training_rate_history = new_reserve_training_rate_history;          
}


// void set_reserve_elapsed_time_history(bool) method

/// This method makes the elapsed time over the epochs to be reseved or not in memory. This is a vector.
/// @param new_reserve_elapsed_time_history True if the elapsed time history vector is to be reserved, false 
/// otherwise.

void TrainingAlgorithm::set_reserve_elapsed_time_history(bool new_reserve_elapsed_time_history)
{
   reserve_elapsed_time_history = new_reserve_elapsed_time_history;     
}


// void set_reserve_validation_error_history(bool) method

/// This method makes the validation error history to be reserved or not in memory. 
/// This is a vector. 
/// @param new_reserve_validation_error_history True if the validation error history is to be reserved, false otherwise. 

void TrainingAlgorithm::set_reserve_validation_error_history(bool new_reserve_validation_error_history)  
{
   reserve_validation_error_history = new_reserve_validation_error_history;
}


// void set_parameters_history(const Vector< Vector<double> >&) method

/// This method sets a new vector of vectors containing the parameters history over the training epochs.
/// Each element in the vector contains the parameters of a single epoch. 
/// @param new_parameters_history Free parameters history vector of vectors. 

void TrainingAlgorithm::set_parameters_history(const Vector< Vector<double> >& new_parameters_history)
{
   parameters_history = new_parameters_history;     
}


// void set_parameters_norm_history(const Vector<double>&) method

/// This method sets a new matrix containing the parameters norm history over the training epochs.
/// Each element in the vector contains the parameters norm of one single epoch. 
///
/// @param new_parameters_norm_history Free parameters norm history vector. 

void TrainingAlgorithm::set_parameters_norm_history(const Vector<double>& new_parameters_norm_history)
{
   parameters_norm_history = new_parameters_norm_history;     
}


// void set_evaluation_history(const Vector<double>&) method

/// This method sets a new vector containing the evaluation history over the training epochs.
/// Each row in the matrix contains the parameters vector of one single epoch. 
/// @param new_evaluation_history Evaluation history vector. 

void TrainingAlgorithm::set_evaluation_history(const Vector<double>& new_evaluation_history)
{
   evaluation_history = new_evaluation_history;     
}


// void set_gradient_history(const Vector< Vector<double> >&) method

/// This method sets a new gradient history matrix over the training epochs. 
/// The number of rows must be equal to the training size.
/// The number of columns must be equal to the number of parameters. 
/// @param new_gradient_history Gradient history matrix.

void TrainingAlgorithm::set_gradient_history(const Vector< Vector<double> >& new_gradient_history)
{
   gradient_history = new_gradient_history;     
}


// void set_gradient_norm_history(const Vector<double>&) method

/// This method sets a new gradient norm history vector. 
/// The elements in the vector are the gradient norm values over the training epochs.
/// @param new_gradient_norm_history Gradient norm history vector. 

void TrainingAlgorithm::set_gradient_norm_history(const Vector<double>& new_gradient_norm_history)
{
   gradient_norm_history = new_gradient_norm_history;     
}


// void set_inverse_Hessian_history(const Vector< Matrix<double> >&) method

/// This method sets a new history of the inverse Hessian over the epochs from a vector of matrices.
/// @param new_inverse_Hessian_history History of the inverse Hessian matrix. 

void TrainingAlgorithm::set_inverse_Hessian_history(const Vector< Matrix<double> >& new_inverse_Hessian_history)
{
   inverse_Hessian_history = new_inverse_Hessian_history;
}


// void set_training_direction_history(const Vector< Vector<double> >&) method

/// This method sets a new vector of vectors containing the training direction history over the training epochs.
/// Each element contains the training direction vector of one single epoch. 
/// @param new_training_direction_history Training direction history. 

void TrainingAlgorithm::
set_training_direction_history(const Vector< Vector<double> >& new_training_direction_history)
{
   training_direction_history = new_training_direction_history;     
}


// void set_training_rate_history(const Vector<double>&) method

/// This method sets a new vector containing the training rate history over the training epochs.
/// Each element in the vector contains the training rate of one single epoch. 
/// @param new_training_rate_history Training rate history vector. 

void TrainingAlgorithm::set_training_rate_history(const Vector<double>& new_training_rate_history)
{
   training_rate_history = new_training_rate_history;     
}


// void set_elapsed_time_history(const Vector<double>&) method

/// This method sets a new elapsed time history vector. 
/// The elements in the vector are the measured times over the training epochs.
/// @param new_elapsed_time_history Elapsed time history vector. 

void TrainingAlgorithm::set_elapsed_time_history(const Vector<double>& new_elapsed_time_history)
{
   elapsed_time_history = new_elapsed_time_history;     
}


// void set_display_period(int) method

/// This method sets a new number of epochs between the training showing progress. 
/// @param new_display_period
/// Number of epochs between the training showing progress. 

void TrainingAlgorithm::set_display_period(int new_display_period)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
     
   if(new_display_period <= 0)
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl

                << "void set_display_period(double) method." << std::endl
                << "First training rate must be greater than 0." << std::endl;

      exit(1);
   }

   #endif

   display_period = new_display_period;
}


// void set_display(bool) method

/// This method sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void TrainingAlgorithm::set_display(bool new_display)
{
   display = new_display;
}


// Vector<double> calculate_training_rate_evaluation(double, const Vector<double>&, double) method

/// This method returns a vector with two elements, the training rate calculated by means of the training rate
/// object member, and the evaluation for that training rate. 
/// @param evaluation Initial objective function evaluation.
/// @param training_direction Initial training direction.
/// @param initial_training_rate Initial training rate to start the algorithm. 

Vector<double> TrainingAlgorithm::calculate_training_rate_evaluation
(double evaluation, const Vector<double>& training_direction, double initial_training_rate)
{
   Vector<double> training_rate_evaluation(2);

   // Get training rate

   switch(training_rate_method)
   {
      case TrainingAlgorithm::Fixed:
      {
         return(calculate_fixed_training_rate_evaluation(evaluation, training_direction, initial_training_rate));
      }
      break;

      case TrainingAlgorithm::GoldenSection:
      {
         return(calculate_golden_section_training_rate_evaluation(evaluation, training_direction, initial_training_rate));
      }
      break;

      case TrainingAlgorithm::BrentMethod:
      {
         return(calculate_Brent_method_training_rate_evaluation(evaluation, training_direction, initial_training_rate));
      }
      break;

	  default:
	  {
         std::cerr << "Flood Error: TrainingAlgorithm class" << std::endl
                   << "void calculate_training_rate_evaluation(double, const Vector<double>&, double) method." << std::endl 
                   << "Unknown training rate method." << std::endl;

         exit(1); 	  
	  }
   }
   Vector <double> d;
   return d;
}


// Vector<double> calculate_bracketing_training_rate_evaluation(double, const Vector<double>&, double) method

/// This method returns a vector with two elements, a bracketing training rate for the optimum, 
/// and the evaluation for that training rate. 
/// This algorithm is used by line minimization algorithms. 
/// @param evaluation Initial objective function evaluation.
/// @param training_direction Initial training direction.
/// @param initial_training_rate Initial training rate to start the algorithm. 

Vector<double> TrainingAlgorithm::calculate_bracketing_training_rate_evaluation
(double evaluation, const Vector<double>& training_direction, double initial_training_rate)
{
   // Multilayer perceptron

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();

   // Training algorithm

   Vector<double> potential_parameters(parameters_number);
   Vector<double> parameters_increment(parameters_number);
   
   // Set initial training rate

   double bracketing_training_rate = initial_training_rate;

   parameters_increment = training_direction*bracketing_training_rate;

   potential_parameters = parameters + parameters_increment;

   double bracketing_evaluation = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);

   // Find initial interval where minimum evaluation occurs

   while(evaluation > bracketing_evaluation)
   {
      // Set new b

      bracketing_training_rate *= bracketing_factor;

      if(bracketing_training_rate >= error_training_rate)
      {
         std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                   << "Vector<double> calculate_bracketing_training_rate_evaluation(double, Vector<double>, double) method." << std::endl
                   << "Unable to bracket a minimum." << std::endl;
                 
         std::cerr << "Evaluation : " << evaluation << std::endl
                   << "Training direction norm: " << training_direction.calculate_norm() << std::endl
                   << "Initial training rate: " << initial_training_rate << std::endl;
     
         exit(1);
      }
      else if(display && bracketing_training_rate >= warning_training_rate)
      {
         std::cout << "Flood Warning: Training rate is " << bracketing_training_rate << std::endl;
      }

      // Calculate evaluation for new b

      parameters_increment = training_direction*bracketing_training_rate;

      potential_parameters = parameters + parameters_increment;

      bracketing_evaluation = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);
   }

   // Return vector

   Vector<double> bracketing_training_rate_evaluation(2);
   bracketing_training_rate_evaluation[0] = bracketing_training_rate;
   bracketing_training_rate_evaluation[1] = bracketing_evaluation;

   return(bracketing_training_rate_evaluation);
}


// Vector<double> calculate_fixed_training_rate_evaluation(double, const Vector<double>&, double) method

/// This method returns a vector with two elements, a fixed training rate equal to the first training rate object member, 
/// and the evaluation for that training rate. 
/// @param training_direction Initial training direction.

Vector<double> TrainingAlgorithm::calculate_fixed_training_rate_evaluation
(double, const Vector<double>& training_direction, double)
{
   Vector<double> training_rate_evaluation(2);

   MultilayerPerceptron* multilayer_perceptron_pointer 
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();   

   Vector<double> parameters_increment = training_direction*first_training_rate;   
   
   Vector<double> potential_parameters = parameters + parameters_increment;

   double evaluation = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);

   training_rate_evaluation[0] = first_training_rate;
   training_rate_evaluation[1] = evaluation;

   return(training_rate_evaluation);
}


// Vector<double> calculate_golden_section_training_rate_evaluation(double, Vector<double>, double) method

/// This method returns the training rate by searching in a given direction to locate the minimum of the objective 
/// function in that direction. It uses the golden section method.
/// @param evaluation Neural network's evaluation value.
/// @param training_direction Training direction vector.
/// @param initial_training_rate Initial training rate in line minimization.

Vector<double> TrainingAlgorithm::calculate_golden_section_training_rate_evaluation
(double evaluation, const Vector<double>& training_direction, double initial_training_rate)
{
   Vector<double> training_rate_evaluation(2);

   // Multilayer perceptron

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();

   Vector<double> potential_parameters(parameters_number);
   Vector<double> parameters_increment(parameters_number);

   // Golden number

   const double tau = (3.0-sqrt(5.0))/2.0; // 0.382

   // Start

   double a = 0.0;
   double evaluation_a = evaluation;

   // Bracket minimum

   Vector<double> b_and_evaluation 
   = calculate_bracketing_training_rate_evaluation(evaluation, training_direction, initial_training_rate);

   double b = b_and_evaluation[0];
   double evaluation_b = b_and_evaluation[1];

   // Initialize c and d (interior points for line minimization)

   double c = a + tau*(b-a);
   parameters_increment = training_direction*c;

   potential_parameters = parameters + parameters_increment;

   double evaluation_c = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);

   double d = b -tau*(b-a);

   parameters_increment = training_direction*d;

   potential_parameters = parameters + parameters_increment;

   double evaluation_d = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);

   // Reduce the interval with the golden section algorithm

   while(b-a > training_rate_tolerance)
   {
      Vector<double> evaluation_vector_left(3);
      evaluation_vector_left[0] = evaluation_a;
      evaluation_vector_left[1] = evaluation_c;
      evaluation_vector_left[2] = evaluation_d;

      double minimum_evaluation_left = evaluation_vector_left.calculate_minimum();

      Vector<double> evaluation_vector_right(3);
      evaluation_vector_right[0] = evaluation_b;
      evaluation_vector_right[1] = evaluation_c;
      evaluation_vector_right[2] = evaluation_d;

      double minimum_evaluation_right = evaluation_vector_right.calculate_minimum();

      if((evaluation_c <= evaluation_d && evaluation_b >= minimum_evaluation_left)
      || (evaluation_a <=  minimum_evaluation_right))

      // There is a minimum between a and b
      {
         b=d;
         d=c;

         evaluation_b = evaluation_d;
         evaluation_d = evaluation_c;

         // Set new c point

         c = a + tau*(b-a);

         parameters_increment = training_direction*c;

         potential_parameters = parameters + parameters_increment;

         evaluation_c = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);
      }
      else if((evaluation_d <= evaluation_c && evaluation_a >= minimum_evaluation_right)
      || (evaluation_b <= minimum_evaluation_left))

      // There is a minimum between c and b
      {
         a = c;
         c = d;

         evaluation_a = evaluation_c;
         evaluation_c = evaluation_d;

         // Set new d point

         d = b - tau*(b-a);

         parameters_increment = training_direction*d;

         potential_parameters = parameters + parameters_increment;

         evaluation_d = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);
      }
      else
      {
         std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                   << "Vector<double> calculate_golden_section_training_rate_evaluation(double, const Vector<double>&, double) method." << std::endl
                   << "Unable to find were the minimum is." << std::endl;

         exit(1);
      }
   }

   // Get minimum evaluation and training rate among points A, B, C and D

   double minimum_evaluation = evaluation;
   double training_rate = 0.0;

   if(evaluation_a < minimum_evaluation)
   {
      minimum_evaluation  = evaluation_a;
      training_rate = a;
   }
   else if(evaluation_b < minimum_evaluation)
   {
      minimum_evaluation = evaluation_b;
      training_rate = b;
   }
   else if(evaluation_c < minimum_evaluation)
   {
      minimum_evaluation = evaluation_c;
      training_rate = c;
   }
   else if(evaluation_d < minimum_evaluation)
   {
      minimum_evaluation = evaluation_d;
      training_rate = d;
   }

   training_rate_evaluation[0] = training_rate;
   training_rate_evaluation[1] = minimum_evaluation;

   return(training_rate_evaluation);
}


// double calculate_Brent_method_training_rate_evaluation(double, const Vector<double>, double) method

/// This method returns the training rate by searching in a given direction to locate the minimum of the evaluation 
/// function in that direction. It uses the Brent's method.
/// @param evaluation Neural network's evaluation value.
/// @param training_direction Training direction vector.
/// @param initial_training_rate Initial training rate in line minimization.

Vector<double> TrainingAlgorithm::calculate_Brent_method_training_rate_evaluation
(double evaluation, const Vector<double>& training_direction, double initial_training_rate)
{
   Vector<double> training_rate_evaluation(2);

   // Multilayer perceptron

   MultilayerPerceptron* multilayer_perceptron_pointer 
   = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();

   Vector<double> potential_parameters(parameters_number);

   Vector<double> parameters_increment(parameters_number);

   // Golden number

   double tau = (3.0-sqrt(5.0))/2.0; // 0.382

   // Start

   double a = 0.0;
   double evaluation_a = evaluation;

   // Bracket minimum

   Vector<double> b_and_evaluation 
   = calculate_bracketing_training_rate_evaluation(evaluation, training_direction, initial_training_rate);

   double b = b_and_evaluation[0];
   double evaluation_b = b_and_evaluation[1];

   double u = 0.0;
   double evaluation_u = evaluation;
   double v = 0.0;
   double evaluation_v = evaluation;
   double w = 0.0;
   double evaluation_w = evaluation;
   double x = 0.0;
   double evaluation_x = evaluation;

   // Get intermediate point V

   v = a + tau*(b-a);

   parameters_increment = training_direction*v;

   potential_parameters = parameters + parameters_increment;

   evaluation_v = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);

   // Set initial W and X points

   w = v;
   evaluation_w = evaluation_v;

   x = v;
   evaluation_x = evaluation_v;

   // Maximum and minimum intervals ???

   bool golden_section = false;

   // Reduce the interval

   while(b-a > training_rate_tolerance)
   {
      // Quadratic interpolation

      if(w != x && w != v && x != v) // Can construct parabola
      {
         // zz vector

         Vector<double> training_rate_vector(3);
         training_rate_vector[0] = v;
         training_rate_vector[1] = w;
         training_rate_vector[2] = x;

         std::sort(training_rate_vector.begin(), training_rate_vector.end(), std::less<double>());

         // pp vector

         Vector<double> evaluation_vector(3);

         for(int i = 0; i < 3; i++)
         {
            if(training_rate_vector[i] == v)
            {
               evaluation_vector[i] = evaluation_v;
            }
            else if(training_rate_vector[i] == w)
            {
               training_rate_vector[i] = evaluation_w;
            }
            else if(training_rate_vector[i] == x)
            {
               training_rate_vector[i] = evaluation_x;
            }
            else
            {
               std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                         << "Vector<double> calculate_Brent_method_training_rate_evaluation(double, const Vector<double>&, double) method." << std::endl
                         << "Unable to construct training rate and evaluation vectors right." << std::endl;

               exit(1);
            }
         }

         // xStar is the minimum of the parabola through the three training rate points

         double numerator
         = (pow(training_rate_vector[2],2) - pow(training_rate_vector[1],2))*evaluation_vector[0]
         + (pow(training_rate_vector[1],2) - pow(training_rate_vector[0],2))*evaluation_vector[2]
         + (pow(training_rate_vector[0],2) - pow(training_rate_vector[2],2))*evaluation_vector[1];

         double denominator
         = (training_rate_vector[2] - training_rate_vector[1])*evaluation_vector[0]
         + (training_rate_vector[1] - training_rate_vector[0])*evaluation_vector[2]
         + (training_rate_vector[0] - training_rate_vector[2])*evaluation_vector[1];

         double xStar = 0.5*numerator/denominator;

         if(xStar < b && a < xStar) // xStar is in [a,b]
         {
            u = xStar;

            // Good, no need to perform golden section

            golden_section = false;
         }
         else // xStar is not in [a,b]
         {
            // Bad, need to perform golden section

            golden_section = true;
         }
      }
      else // Cannot construct parabola
      {
         // Bad, need to perform golden section

         golden_section = true;
      }

      //
      // Golden section
      //

      if(golden_section == true)
      {
         if(x >= (a+b)/2.0)
         {
            u = x-tau*(x-a);
         }
         else
         {
            u = x+tau*(b-x);
         }
      }

      // Calculate evaluation for U

      parameters_increment = training_direction*u;

      potential_parameters = parameters + parameters_increment;

      evaluation_u = objective_functional_pointer->calculate_potential_evaluation(potential_parameters);

      // Update points

      if(evaluation_u <= evaluation_x)
      {
         if(u < x)
         {
            b = x;
            evaluation_b = evaluation_x;
         }
         else
         {
            a = x;
            evaluation_a = evaluation_x;
         }

         v = w;
         evaluation_v = evaluation_w;

         w = x;
         evaluation_w = evaluation_x;

         x = u;
         evaluation_x = evaluation_u;
      }
      else
      {
         if(u < x)
         {
            a = u;
            evaluation_a = evaluation_u;
         }
         else
         {
            b = u;
            evaluation_b = evaluation_u;
         }

         if((evaluation_u <= evaluation_w) || (w == x))
         {
             v = w;
             evaluation_v = evaluation_w;

             w = u;
             evaluation_w = evaluation_u;
         }
         else if((evaluation_u <= evaluation_v) || (v == x) || (v == w))
         {
            v = u;
            evaluation_v = evaluation_u;
         }
      }
   } // while loop

   // Get minimum evaluation and training rate among points A, B, V, W and X

   double minimum_evaluation = evaluation;
   double training_rate = 0.0;

   if(evaluation_a < minimum_evaluation)
   {
      minimum_evaluation = evaluation_a;
      training_rate = a;
   }
   else if(evaluation_b < minimum_evaluation)
   {
      minimum_evaluation = evaluation_b;
      training_rate = b;
   }
   else if(evaluation_u < minimum_evaluation)
   {
      minimum_evaluation = evaluation_u;
      training_rate = u;
   }
   else if(evaluation_v < minimum_evaluation)
   {
      minimum_evaluation = evaluation_v;
      training_rate = v;
   }
   else if(evaluation_w < minimum_evaluation)
   {
      minimum_evaluation = evaluation_w;
      training_rate = w;
   }
   else if(evaluation_x < minimum_evaluation)
   {
      minimum_evaluation = evaluation_x;
      training_rate = x;
   }

   training_rate_evaluation[0] = training_rate;
   training_rate_evaluation[1] = minimum_evaluation;

   return(training_rate_evaluation);
}


// std::string to_XML(bool) method

/// This method returns a default string representation in XML-type format of the training algorithm object.
/// This containts the training operators, the training parameters, stopping criteria and other stuff.
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string TrainingAlgorithm::to_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='TrainingAlgorithm'>" << std::endl;
   }

   // Training operators

   buffer << "<TrainingRateMethod>" << std::endl
   	      << get_training_rate_method_name() << std::endl
          << "</TrainingRateMethod>" << std::endl;

   // Training parameters

   buffer << "<BracketingFactor> " << std::endl
          << bracketing_factor << std::endl
		  << "</BracketingFactor> " << std::endl;

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

   buffer << "<GradientNormGoal>" << std::endl
          << gradient_norm_goal << std::endl
          << "</GradientNormGoal>" << std::endl;

   buffer << "<MaximumEpochsNumber>" << std::endl
          << maximum_epochs_number << std::endl 
		  << "</MaximumEpochsNumber>" << std::endl;

   buffer << "<MaximumTime>" << std::endl
          << maximum_time << std::endl 
          << "</MaximumTime>" << std::endl;
 
   // Early stopping

   buffer << "<EarlyStopping>" << std::endl
          << early_stopping << std::endl 
          << "</EarlyStopping>" << std::endl;
  
   // Reserve training history

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

   buffer << "<ReserveInverseHessianHistory>" << std::endl
          << reserve_inverse_Hessian_history << std::endl 
          << "</ReserveInverseHessianHistory>" << std::endl;

   buffer << "<ReserveTrainingDirectionHistory>" << std::endl
          << reserve_training_direction_history << std::endl 
          << "</ReserveTrainingDirectionHistory>" << std::endl;

   buffer << "<ReserveTrainingRateHistory>"  << std::endl
          << reserve_training_rate_history << std::endl
          << "</ReserveTrainingRateHistory>"  << std::endl;

   buffer << "<ReserveElapsedTimeHistory>" << std::endl
          << reserve_elapsed_time_history << std::endl 
          << "</ReserveElapsedTimeHistory>" << std::endl;

   buffer << "<ReserveValidationErrorHistory>" << std::endl
          << reserve_validation_error_history << std::endl 
          << "</ReserveValidationErrorHistory>" << std::endl;

   // User stuff

   buffer << "<Display>" << std::endl
          << display << std::endl
		  << "</Display>" << std::endl;

   buffer << "<DisplayPeriod>" << std::endl
          << display_period << std::endl
		  << "</DisplayPeriod>" << std::endl;

   return(buffer.str());
}


// void print(void) method

/// This method prints to the screen the XML-type representation of the training algorithm object. 

void TrainingAlgorithm::print(void)
{
   std::cout << to_XML(true);
}


// void save(const char*) method

/// This method saves to a XML-type file the members of the training algorithm object. 
/// @param filename Name of training algorithm XML-type file. 

void TrainingAlgorithm::save(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void save(const char*) method." << std::endl
                << "Cannot open training algorithm XML-type file." << std::endl;

      exit(1);
   }

   // Write file header

   file << to_XML(true);

   // Close file

   file.close();
}


// void load(const char*) method

/// This method loads a gradient descent object from a XML-type file. 
/// Please mind about the file format, wich is specified in the User's Guide. 
/// @param filename Name of training algorithm XML-type file. 

void TrainingAlgorithm::load(const char* filename)
{
   // File

   std::fstream file;

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open training algorithm object XML-type file."  << std::endl;

      exit(1);
   }

   std::string word;
   std::string line;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='TrainingAlgorithm'>") 
   {
//      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
//                << "void load(const char*) method." << std::endl
//				<< "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   while(!file.eof())
   {
      file >> word; 

	  // Training operators

	  if(word == "<TrainingRateMethod>")
	  {
		 std::string new_training_rate_method; 

         file >> new_training_rate_method;          

         file >> word;

		 if(word != "</TrainingRateMethod>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown training rate method end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_training_rate_method(new_training_rate_method);
	  }

	  // Training parameters

	  else if(word == "<BracketingFactor>")
	  {
		 double new_backeting_factor; 

         file >> new_backeting_factor;          

         file >> word;

		 if(word != "</BracketingFactor>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown bracketing factor end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_bracketing_factor(new_backeting_factor);
	  }
	  else if(word == "<FirstTrainingRate>")
	  {
		 double new_first_training_rate; 

         file >> new_first_training_rate;          

         file >> word;

		 if(word != "</FirstTrainingRate>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown first training rate end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_first_training_rate(new_first_training_rate);
	  }
	  else if(word == "<TrainingRateTolerance>")
	  {
		 double new_training_rate_tolerance; 

         file >> new_training_rate_tolerance;          

         file >> word;

		 if(word != "</TrainingRateTolerance>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown training rate tolerance end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_training_rate_tolerance(new_training_rate_tolerance);
	  }

	  else if(word == "<WarningParametersNorm>")
	  {
		 double new_warning_parameters_norm; 

         file >> new_warning_parameters_norm;          

         file >> word;

		 if(word != "</WarningParametersNorm>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown warning parameters norm end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_warning_parameters_norm(new_warning_parameters_norm);
	  }

	  else if(word == "<WarningGradientNorm>")
	  {
		 double new_warning_gradient_norm; 

         file >> new_warning_gradient_norm;          

         file >> word;

		 if(word != "</WarningGradientNorm>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown warning gradient norm end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_warning_gradient_norm(new_warning_gradient_norm);
	  }

	  else if(word == "<WarningTrainingRate>")
	  {
		 double new_warning_training_rate; 

         file >> new_warning_training_rate;          

         file >> word;

		 if(word != "</WarningTrainingRate>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown warning training rate end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_warning_training_rate(new_warning_training_rate);
	  }

	  else if(word == "<ErrorParametersNorm>")
	  {
		 double new_error_parameters_norm; 

         file >> new_error_parameters_norm;          

         file >> word;

		 if(word != "</ErrorParametersNorm>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown error parameters norm end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_error_parameters_norm(new_error_parameters_norm);
	  }

	  else if(word == "<ErrorGradientNorm>")
	  {
		 double new_error_gradient_norm; 

         file >> new_error_gradient_norm;          

         file >> word;

		 if(word != "</ErrorGradientNorm>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown error gradient norm end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_error_gradient_norm(new_error_gradient_norm);
	  }

	  else if(word == "<ErrorTrainingRate>")
	  {
		 double new_error_training_rate; 

         file >> new_error_training_rate;          

         set_error_training_rate(new_error_training_rate);

         file >> word;

		 if(word != "</ErrorTrainingRate>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
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

         file >> word;

		 if(word != "</MinimumParametersIncrementNorm>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown minimum parameters increment norm end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_minimum_parameters_increment_norm(new_minimum_parameters_increment_norm);
	  }

	  else if(word == "<MinimumEvaluationImprovement>")
	  {
		 double new_minimum_evaluation_improvement; 

         file >> new_minimum_evaluation_improvement;          

         file >> word;

		 if(word != "</MinimumEvaluationImprovement>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown minimum evaluation improvement end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_minimum_evaluation_improvement(new_minimum_evaluation_improvement);
	  }
	  else if(word == "<EvaluationGoal>")
	  {
		 double new_evaluation_goal; 

         file >> new_evaluation_goal;          

         file >> word;

		 if(word != "</EvaluationGoal>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown evaluation goal end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_evaluation_goal(new_evaluation_goal);
	  }
	  else if(word == "<GradientNormGoal>")
	  {
		 double new_gradient_norm_goal; 

         file >> new_gradient_norm_goal;          

         file >> word;

		 if(word != "</GradientNormGoal>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown gradient norm goal end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_gradient_norm_goal(new_gradient_norm_goal);
	  }
	  else if(word == "<MaximumEpochsNumber>")
	  {
		 int new_maximum_epochs_number; 

         file >> new_maximum_epochs_number;          

         file >> word;

		 if(word != "</MaximumEpochsNumber>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
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
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown maximum time end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_maximum_time(new_maximum_time);
	  }
	  else if(word == "<EarlyStopping>")
	  {
   	     bool new_early_stopping; 

         file >> new_early_stopping;          

         file >> word;

		 if(word != "</EarlyStopping>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown early stopping end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_early_stopping(new_early_stopping);
	  }

      // Training history 

	  else if(word == "<ReserveParametersHistory>")
	  {
   	     bool new_reserve_parameters_history; 

         file >> new_reserve_parameters_history;          

         file >> word;

		 if(word != "</ReserveParametersHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve parameters history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_parameters_history(new_reserve_parameters_history);
	  }

	  else if(word == "<ReserveParametersNormHistory>")
	  {
   	     bool new_reserve_parameters_norm_history; 

         file >> new_reserve_parameters_norm_history;          

         file >> word;

		 if(word != "</ReserveParametersNormHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve parameters norm history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_parameters_norm_history(new_reserve_parameters_norm_history);
	  }
	  else if(word == "<ReserveEvaluationHistory>")
	  {
   	     bool new_reserve_evaluation_history; 

         file >> new_reserve_evaluation_history;          

         file >> word;

		 if(word != "</ReserveEvaluationHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve evaluation history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_evaluation_history(new_reserve_evaluation_history);
	  }

	  else if(word == "<ReserveGradientHistory>")
	  {
   	     bool new_reserve_gradient_history; 

         file >> new_reserve_gradient_history;          

         file >> word;

		 if(word != "</ReserveGradientHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve gradient history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_gradient_history(new_reserve_gradient_history);
	  }

	  else if(word == "<ReserveGradientNormHistory>")
	  {
   	     bool new_reserve_gradient_norm_history; 

         file >> new_reserve_gradient_norm_history;          

         file >> word;

		 if(word != "</ReserveGradientNormHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve gradient norm history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_gradient_norm_history(new_reserve_gradient_norm_history);
	  }

	  else if(word == "<ReserveInverseHessianHistory>")
	  {
   	     bool new_reserve_inverse_Hessian_history; 

         file >> new_reserve_inverse_Hessian_history;          

         file >> word;

		 if(word != "</ReserveInverseHessianHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve inverse Hessian history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_inverse_Hessian_history(new_reserve_inverse_Hessian_history);
	  }

	  else if(word == "<ReserveTrainingDirectionHistory>")
	  {
   	     bool new_reserve_training_direction_history; 

         file >> new_reserve_training_direction_history;          

         file >> word;

		 if(word != "</ReserveTrainingDirectionHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve training direction history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_training_direction_history(new_reserve_training_direction_history);
	  }

	  else if(word == "<ReserveTrainingRateHistory>")
	  {
   	     bool new_reserve_training_rate_history; 

         file >> new_reserve_training_rate_history;          

         file >> word;

		 if(word != "</ReserveTrainingRateHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve training rate history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_training_rate_history(new_reserve_training_rate_history);
	  }

	  else if(word == "<ReserveElapsedTimeHistory>")
	  {
   	     bool new_reserve_elapsed_time_history; 

         file >> new_reserve_elapsed_time_history;          

         file >> word;

		 if(word != "</ReserveElapsedTimeHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve elapsed time history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_elapsed_time_history(new_reserve_elapsed_time_history);
	  }

	  else if(word == "<ReserveValidationErrorHistory>")
	  {
   	     bool new_reserve_validation_error_history; 

         file >> new_reserve_validation_error_history;          

         file >> word;

		 if(word != "</ReserveValidationErrorHistory>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown reserve validation error history end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_reserve_validation_error_history(new_reserve_validation_error_history);
	  }

	  // User stuff

	  else if(word == "<DisplayPeriod>")
	  {
		  int new_display_period; 

         file >> new_display_period;          

         file >> word;

		 if(word != "</DisplayPeriod>") 
         {
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
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
            std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown display end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_display(new_display);
	  }

	  else
	  {
      //   std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
      //             << "void load(const char*) method." << std::endl
      //  		   << "Unknown tag: " << word << std::endl;
      //
      //   exit(1);
 	  }
   }

   // Close file

   file.close();
}


// void set_reserve_all_training_history(bool) method

/// This method makes the training history of all default variables to reseved or not in memory.
/// Reserving all the training history is memory expensive. 
/// @param new_reserve_all_training_history True if the training history of all variables is to be reserved, 
/// false otherwise.

void TrainingAlgorithm::set_reserve_all_training_history(bool new_reserve_all_training_history)
{
   reserve_parameters_history = new_reserve_all_training_history;
   reserve_parameters_norm_history = new_reserve_all_training_history;

   reserve_evaluation_history = new_reserve_all_training_history;
   reserve_gradient_history = new_reserve_all_training_history;
   reserve_gradient_norm_history = new_reserve_all_training_history;
   reserve_inverse_Hessian_history = new_reserve_all_training_history;

   reserve_validation_error_history = new_reserve_all_training_history;

   reserve_training_direction_history = new_reserve_all_training_history;
   reserve_training_rate_history = new_reserve_all_training_history;
   reserve_elapsed_time_history = new_reserve_all_training_history;
}


// void resize_training_history(int) method

/// This method resizes all the default training history vectors. 
/// @param new_size Size vectors containing the training history variables. 

void TrainingAlgorithm::resize_training_history(int new_size)
{
   // Multilayer perceptron

   if(reserve_parameters_history)
   {
      parameters_history.resize(new_size);
   }

   if(reserve_parameters_norm_history)
   {
      parameters_norm_history.resize(new_size);
   }

   // Objective functional

   if(reserve_evaluation_history)
   {
      evaluation_history.resize(new_size);
   }

   if(reserve_gradient_history)
   {
      gradient_history.resize(new_size);
   }
 
   if(reserve_gradient_norm_history)
   {
      gradient_norm_history.resize(new_size);
   }

   if(reserve_inverse_Hessian_history)
   {
      inverse_Hessian_history.resize(new_size);
   }

   if(reserve_validation_error_history)
   {
      validation_error_history.resize(new_size);
   }

   // Training algorithm

   if(reserve_training_direction_history)
   {
      training_direction_history.resize(new_size);
   }
  
   if(reserve_training_rate_history)
   {
      training_rate_history.resize(new_size);
   }

   if(reserve_elapsed_time_history)
   {
      elapsed_time_history.resize(new_size);
   }
}


// std::string get_training_history_XML(bool) method

/// This method returns a string with the history of the training process in XML-type format. 
/// Only that training history variables which have been reserved are included here. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string TrainingAlgorithm::get_training_history_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='TrainingAlgorithm' content='TrainingHistory'>" << std::endl;
   }

   // Multilayer perceptron

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

   // Objective functional

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

   if(reserve_inverse_Hessian_history)
   {
      buffer << "<InverseHessianHistory>" << std::endl;

      int size = inverse_Hessian_history.get_size();

	  for(int i = 0; i < size; i++)
	  {
		  buffer << "<InverseHessian>" << std::endl
                 << inverse_Hessian_history[i] << std::endl  
				 << "</InverseHessian>" << std::endl;	  
	  }

      buffer << "</InverseHessianHistory>" << std::endl;
   }

   // Training algorithm

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

   if(reserve_validation_error_history)
   {
      buffer << "<ValidationErrorHistory>" << std::endl
             << validation_error_history << std::endl     
             << "</ValidationErrorHistory>" << std::endl;
   }

   return(buffer.str());
}


// void print_training_history(void) method

/// This method prints to the screen the history of the training process for the reserved variables. 

void TrainingAlgorithm::print_training_history(void)
{
	std::cout << get_training_history_XML(true);
}


// void save_training_history(const char*) method

/// This method saves the training history to a XML-type file. 
/// @param filename Training history XML-type filename. 

void TrainingAlgorithm::save_training_history(const char* filename)
{
   std::fstream file; 

   // Open file 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: TrainingAlgorithm class." << std::endl
                << "void save_training_history(const char*) method." << std::endl
                << "Cannot open training history XML-type file." << std::endl;

      exit(1);
   }

   // Write file 

   file << get_training_history_XML(true);

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
