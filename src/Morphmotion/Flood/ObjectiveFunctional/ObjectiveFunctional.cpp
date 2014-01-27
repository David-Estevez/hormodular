/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   O B J E C T I V E   F U N C T I O N A L   C L A S S                                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

// Flood includes

#include "../Utilities/Vector.h"
#include "../Utilities/Matrix.h"

#include "ObjectiveFunctional.h"

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>


namespace Flood
{

// GENERAL CONSTRUCTOR

/// General constructor. It creates an objective functional object associated to a multilayer perceptron object. 
/// It also initializes all the rest of class members to their default values.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.

ObjectiveFunctional::ObjectiveFunctional(MultilayerPerceptron* new_multilayer_perceptron_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;

   set_default();
}


// DEFAULT CONSTRUCTOR

/// General constructor. It creates an objective functional object not associated to any multilayer perceptron object.
/// It also initializes all the rest of class members to their default values.

ObjectiveFunctional::ObjectiveFunctional(void)
{
   multilayer_perceptron_pointer = NULL;

   set_default();
}


// DESTRUCTOR

/// Destructor.

ObjectiveFunctional::~ObjectiveFunctional(void)
{

}


// METHODS

// double get_objective_weight(void) method

/// This method returns the weight value of the objective term in the objective functional expression. 

double ObjectiveFunctional::get_objective_weight(void)
{
   return(objective_weight);
}


// RegularizationMethod get_regularization_method(void) method

/// This method returns the regularization method to be used in the objective functional expression. 

ObjectiveFunctional::RegularizationMethod& ObjectiveFunctional::get_regularization_method(void)
{
   return(regularization_method);
}


// std::string get_regularization_method_name(void) method

/// This method returns a string with the name of the regularization method. 

std::string ObjectiveFunctional::get_regularization_method_name(void)
{
   switch(regularization_method)
   {
      case None:
      {
         return("None");
      }
      break;

      case NeuralParametersNorm:
      {
         return("NeuralParametersNorm");
      }
      break;

      default:
      {
         std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                   << "std::string get_regularization_method_name(void) method." << std::endl
                   << "Unknown regularization method." << std::endl;
 
          exit(1);
      }
      break;
   }
}


// double get_regularization_weight(void) method

/// This method returns the weight value of the regularization term in the objective functional expression. 

double ObjectiveFunctional::get_regularization_weight(void)
{
   return(regularization_weight);
}


// NumericalDifferentiationMethod get_numerical_differentiation_method(void) method

/// This method returns the method used for numerical differentiation.

ObjectiveFunctional::NumericalDifferentiationMethod ObjectiveFunctional::get_numerical_differentiation_method(void)
{
   return(numerical_differentiation_method);                           
}


// NumericalEpsilonMethod get_numerical_epsilon_method(void) method

/// This method returns the method used for obtaining a numerical epsilon value.

ObjectiveFunctional::NumericalEpsilonMethod ObjectiveFunctional::get_numerical_epsilon_method(void)
{
   return(numerical_epsilon_method);                           
}


// std::string get_numerical_differentiation_method_name(void) method

/// This method returns a string with the name of the numerical differentiation method. 

std::string ObjectiveFunctional::get_numerical_differentiation_method_name(void)
{
   switch(numerical_differentiation_method)
   {
      case ObjectiveFunctional::ForwardDifferences:
      {
         return("ForwardDifferences");
      }
      break;

      case ObjectiveFunctional::CentralDifferences:
      {
         return("CentralDifferences");
      }
      break;

      default:
      {
         std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                   << "std::string get_numerical_differentiation_method(void) method." << std::endl
                   << "Unknown numerical differentiation method." << std::endl;
 
         exit(1);
      }
      break;
   }
}


// std::string get_numerical_epsilon_method_name(void) method

/// This method returns a string with the name of the method to be used for obtaining a numerical epsilon value. 

std::string ObjectiveFunctional::get_numerical_epsilon_method_name(void)
{
   switch(numerical_differentiation_method)
   {
      case Absolute:
      {
         return("Absolute");
      }
      break;

      case Relative:
      {
         return("Relative");
      }
      break;

      default:
      {
         std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                   << "std::string get_numerical_epsilon_method(int) method." << std::endl
                   << "Unknown numerical epsilon method." << std::endl;
 
          exit(1);
      }
      break;
   }
}


// double get_numerical_epsilon(void) method

/// This method returns the epsilon value for the calculation of the objective function gradient by means of 
/// numerical differentiation.

double ObjectiveFunctional::get_numerical_epsilon(void)
{
   return(numerical_epsilon);
}


// int get_calculate_evaluation_count(void) method

/// This method returns the number of calls to the calculate_evaluation(void) method.

int ObjectiveFunctional::get_calculate_evaluation_count(void)
{
   return(calculate_evaluation_count);
}


// int get_calculate_gradient_count(void) method

/// This method returns the number of calls to the calculate_gradient(void) method.

int ObjectiveFunctional::get_calculate_gradient_count(void)
{
   return(calculate_gradient_count);
}


// int get_calculate_Hessian_count(void) method

/// This method returns the number of calls to the calculate_Hessian(void) method.

int ObjectiveFunctional::get_calculate_Hessian_count(void)
{
   return(calculate_Hessian_count);
}


// bool get_display(void) method

/// This method returns true if messages from this class can be displayed on the screen, or false if messages 
/// from this class can't be displayed on the screen.

bool ObjectiveFunctional::get_display(void)
{
   return(display);
}


// void set_multilayer_perceptron_pointer(MultilayerPerceptron*) method

/// This method sets a pointer to a multilayer perceptron object which is to be associated to the objective 
/// functional.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer percepron object to be associated to the objective 
/// functional.

void ObjectiveFunctional::set_multilayer_perceptron_pointer(MultilayerPerceptron* new_multilayer_perceptron_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;
}


// void set_default(void) method

/// This method sets the members of the objective functional object to their default values:
/// <ul>
/// <li> Objective weight: 1.0.
/// <li> Regularization method: None.
/// <li> Regularization weight: 0.0.
/// <li> Calculate evaluation count: 0.
/// <li> Calculate gradient count: 0.
/// <li> Calculate Hessian count: 0.
/// <li> Numerical differentiation method: Central differences.
/// <li> Numerical epsilon method: Relative.
/// <li> Numerical epsilon: 1.0e-5.
/// <li> Display: true.
/// </ul>

void ObjectiveFunctional::set_default(void)
{
   // Objective term

   objective_weight = 1.0;

   // Regularization term

   regularization_method = None;
   regularization_weight = 0.0;

   // Counters

   calculate_evaluation_count = 0;
   calculate_gradient_count = 0;
   calculate_Hessian_count = 0;

   // Numerical differentiation

   numerical_differentiation_method = CentralDifferences;
   numerical_epsilon_method = Relative;
   numerical_epsilon = 1.0e-6;

   // Utilities

   display = true;
}

// void set_numerical_differentiation_method(const NumericalDifferentiationMethod&)

/// This method sets the method to be used for the numerical differentiation of the error function derivatives.
/// @param new_numerical_differentiation_method New numerical differentiation method.

void ObjectiveFunctional::set_numerical_differentiation_method
(const ObjectiveFunctional::NumericalDifferentiationMethod& new_numerical_differentiation_method)
{
   numerical_differentiation_method = new_numerical_differentiation_method;
}


// void set_numerical_epsilon_method(const NumericalEpsilonMethod&)

/// This method sets the method to be used for obtaining a numerical epsilon value to be used in numerical 
/// differentiation. 
/// @param new_numerical_epsilon_method New numerical epsilon method.

void ObjectiveFunctional
::set_numerical_epsilon_method(const ObjectiveFunctional::NumericalEpsilonMethod& new_numerical_epsilon_method)
{
   numerical_epsilon_method = new_numerical_epsilon_method;
}


// void set_numerical_differentiation_method(const std::string&) method

/// This method sets a new numerical differentiation method from a string with the name of the method. 
/// @param new_numerical_differentiation_method_name Name of numerical differentiation method. 

void ObjectiveFunctional::set_numerical_differentiation_method(const std::string& new_numerical_differentiation_method_name)
{
   if(new_numerical_differentiation_method_name == "ForwardDifferences")
   {
      numerical_differentiation_method = ForwardDifferences;
   }
   else if(new_numerical_differentiation_method_name == "CentralDifferences")
   {
      numerical_differentiation_method = CentralDifferences;
   }
   else
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_numerical_differentiation_method(const std::string&) method." << std::endl
				<< "Unknown numerical differentiation method: " << new_numerical_differentiation_method_name << "." <<std::endl;

	  exit(1);   
   }	
}

// void set_numerical_epsilon_method(const std::string&) method

/// This method sets a new numerical epsilon method from a string with the name of the method. 
/// @param new_numerical_epsilon_method_name Name of numerical epsilon method. 

void ObjectiveFunctional::set_numerical_epsilon_method(const std::string& new_numerical_epsilon_method_name)
{
   if(new_numerical_epsilon_method_name == "Absolute")
   {
      numerical_epsilon_method = Absolute;
   }
   else if(new_numerical_epsilon_method_name == "Relative")
   {
      numerical_epsilon_method = Relative;
   }
   else
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_numerical_epsilon_method_name(const std::string&) method." << std::endl
				<< "Unknown numerical epsilon method: " << new_numerical_epsilon_method_name << "." <<std::endl;

      exit(1);   
   }	
}


// void set_numerical_epsilon(double) method

/// This method sets a new epsilon value for the calculation of the objective function gradient by means of 
/// numerical differentiation.
/// @param new_numerical_epsilon New value for epsilon.

void ObjectiveFunctional::set_numerical_epsilon(double new_numerical_epsilon)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_numerical_epsilon <= 0.0)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_numerical_epsilon(double) method." << std::endl
                << "Numerical epsilon must be greater than 0." << std::endl;

      exit(1);
   }

   #endif

   // Set numerical epsilon

   numerical_epsilon = new_numerical_epsilon;
}


// void set_objective_weight(double) method

/// This method sets a new weight value for the objective term in the objective functional expression. 
/// @param new_objective_weight Weight value for the objective term. 

void ObjectiveFunctional::set_objective_weight(double new_objective_weight)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_objective_weight < 0.0)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_objective_weight(double) method." << std::endl
                << "Objective weight must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   objective_weight = new_objective_weight;
}


// void set_regularization_method(const RegularizationMethod&) method

/// This method sets a new regularization method for the objective functional expression. 
/// @param new_regularization_method Regularization method. 

void ObjectiveFunctional::set_regularization_method
(const ObjectiveFunctional::RegularizationMethod& new_regularization_method)
{
   regularization_method = new_regularization_method;
}


// void set_regularization_method(const std::string&) method

/// This method sets a new regularization method from a string with the name of that method. 
/// @param new_regularization_method_name Regularization method name. 

void ObjectiveFunctional::set_regularization_method(const std::string& new_regularization_method_name)
{
   if(new_regularization_method_name == "None")
   {
      regularization_method = None;
   }
   else if(new_regularization_method_name == "NeuralParametersNorm")
   {
      regularization_method = NeuralParametersNorm;
   }
   else
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_regularization_method(const std::string&) method." << std::endl
				<< "Unknown regularization method: " << new_regularization_method_name << "." <<std::endl;
   
      exit(1);   
   }
}


// void set_regularization_weight(double) method

/// This method sets a new weight value for the regularization term in the objective functional expression. 
/// @param new_regularization_weight Weight value for the regularization term. 

void ObjectiveFunctional::set_regularization_weight(double new_regularization_weight)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_regularization_weight < 0.0)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_regularization_weight(double) method." << std::endl
                << "Regularization weight must be equal or greater than 0." << std::endl;

      exit(1);
   }

   #endif

   regularization_weight = new_regularization_weight;
}


// void set_calculate_evaluation_count(int) method

/// This method sets the number of calls to the get_objective(void) method to a new value. 
/// @param new_calculate_evaluation_count New number of calls to the calculate_evaluation(void) method.

void ObjectiveFunctional::set_calculate_evaluation_count(int new_calculate_evaluation_count)
{
   // Control sentence

   if(new_calculate_evaluation_count < 0)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_calculate_evaluation_count(int) method." << std::endl
                << "Count of calculate_evaluation() calls must be equal or greater than 0." << std::endl;

      exit(1);
   }

   // Set number of evaluations

   calculate_evaluation_count = new_calculate_evaluation_count;
}


// void set_calculate_gradient_count(int) method

/// This method sets the number of calls to the calculate_gradient(void) method to a new value. 
/// @param new_calculate_gradient_count New number of calls to the calculate_gradient(void) method.

void ObjectiveFunctional::set_calculate_gradient_count(int new_calculate_gradient_count)
{
   // Control sentence

   if(new_calculate_gradient_count < 0)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_calculate_gradient_count(int) method." << std::endl
                << "Count of calculate_gradient() calls must be equal or greater than 0." << std::endl;

      exit(1);
   }

   // Set number of evaluations

   calculate_gradient_count = new_calculate_gradient_count;
}


// void set_calculate_Hessian_count(int) method

/// This method sets the number of calls to the calculate_Hessian(void) method to a new value. 
/// @param new_calculate_Hessian_count New number of calls to the calculate_Hessian(void) method.

void ObjectiveFunctional::set_calculate_Hessian_count(int new_calculate_Hessian_count)
{
   // Control sentence

   if(new_calculate_Hessian_count < 0)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void set_calculate_gradient_count(int) method." << std::endl
                << "Count of calculate_Hessian() calls must be equal or greater than 0." << std::endl;

      exit(1);
   }

   // Set number of evaluations

   calculate_Hessian_count = new_calculate_Hessian_count;
}


// void set_display(bool) method

/// This method sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void ObjectiveFunctional::set_display(bool new_display)
{
   display = new_display;
}


// double calculate_evaluation(void) method

/// This method calculates the evaluation value of the objective functional, 
/// as the sum of the objective and the regularization terms. 

double ObjectiveFunctional::calculate_evaluation()
{
   // Increment number of evaluations count

   calculate_evaluation_count++;

   if(regularization_method == None)
   {
      double objective = calculate_objective();

      return(objective_weight*objective);
   }
   else
   {
      double objective = calculate_objective();
      double regularization = calculate_regularization();
   
      return(objective_weight*objective + regularization_weight*regularization);
   }
}


/*---------------------------Avinash Ranganath------------------------------------------*/
double ObjectiveFunctional::calculate_evaluation(int generation, int individual)
{
   // Increment number of evaluations count

   calculate_evaluation_count++;

   if(regularization_method == None)
   {
      double objective = calculate_objective(generation, individual);

      return(objective_weight*objective);
   }
   else
   {
      double objective = calculate_objective(generation, individual);
      double regularization = calculate_regularization();
   
      return(objective_weight*objective + regularization_weight*regularization);
   }
}


/*---------------------------Avinash Ranganath------------------------------------------*/
double ObjectiveFunctional::calculate_evaluation(int generation, int individual, int evaluation_sample_size)
{
   // Increment number of evaluations count

   calculate_evaluation_count++;

   if(regularization_method == None)
   {
      double objective = calculate_objective(generation, individual, evaluation_sample_size);

      return(objective_weight*objective);
   }
   else
   {
      double objective = calculate_objective(generation, individual, evaluation_sample_size);
      double regularization = calculate_regularization();
   
      return(objective_weight*objective + regularization_weight*regularization);
   }
}

// double calculate_regularization(void) method

/// This method returns the evaluation of the regularization term in the objective functional,
/// according to the regularization method used. 

double ObjectiveFunctional::calculate_regularization(void) 
{
   switch(regularization_method)   
   {
      case None:
      {
         return(0.0);
      }             
      break;

      case NeuralParametersNorm:
      {
         double regularization = multilayer_perceptron_pointer->calculate_neural_parameters_norm();

         return(regularization);
      }             
      break;

      default:
      {
          std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                    << "double calculate_regularization(void) method." << std::endl
                    << "Unknown regularization method." << std::endl;
 
          exit(1);
      }// end default
      break;
   }   
}


// double calculate_potential_evaluation(const Vector<double>&) method

/// This method returns which would be the objective evaluation of a multilayer perceptron for an hypothetical 
/// vector of parameters. It does not set that vector of parameters to the multilayer perceptron. 
/// @param potential_parameters Vector of a potential parameters for the multilayer perceptron associated 
/// to the objective functional.

double ObjectiveFunctional::calculate_potential_evaluation(const Vector<double>& potential_parameters)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = potential_parameters.get_size();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "double calculate_potential_evaluation(const Vector<double>&) method." << std::endl
                << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ")." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();

   // Set potential parameters

   multilayer_perceptron_pointer->set_parameters(potential_parameters);

   // Get Objective

   double potential_evaluation = calculate_evaluation();

   // Restart original parameters

   multilayer_perceptron_pointer->set_parameters(parameters);

   return(potential_evaluation);
}


/*---------------------------Avinash Ranganath-------------------------------------*/
double ObjectiveFunctional::calculate_potential_evaluation(const Vector<double>& potential_parameters,int generation, int individual)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = potential_parameters.get_size();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "double calculate_potential_evaluation(const Vector<double>&) method." << std::endl
                << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ")." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();

   // Set potential parameters

   multilayer_perceptron_pointer->set_parameters(potential_parameters);

   // Get Objective

   double potential_evaluation = calculate_evaluation(generation, individual);

   // Restart original parameters

   multilayer_perceptron_pointer->set_parameters(parameters);

   return(potential_evaluation);
}


/*---------------------------Avinash Ranganath-------------------------------------*/
double ObjectiveFunctional::calculate_potential_evaluation(const Vector<double>& potential_parameters, 
                                                           int generation, 
                                                           int individual, 
                                                           int evaluation_sample_size)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = potential_parameters.get_size();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "double calculate_potential_evaluation(const Vector<double>&) method." << std::endl
                << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ")." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();

   // Set potential parameters

   multilayer_perceptron_pointer->set_parameters(potential_parameters);

   // Get Objective

   double potential_evaluation = calculate_evaluation(generation, individual, evaluation_sample_size);

   // Restart original parameters

   multilayer_perceptron_pointer->set_parameters(parameters);

   return(potential_evaluation);
}


// Vector<double> calculate_gradient(void) method

/// This method returns the objective function gradient, as the sum of the objective and the regularization gradient vectors. 

Vector<double> ObjectiveFunctional::calculate_gradient(void)
{
   // Increment number of gradients count
 
   calculate_gradient_count++;

   if(regularization_method == None)
   {
      return(calculate_objective_gradient()*objective_weight);   
   }
   else
   {
      return(calculate_objective_gradient()*objective_weight + calculate_regularization_gradient()*regularization_weight);
   }
}


// double calculate_gradient_norm(void) method

/// This method returns the norm of the objective function gradient vector. 

double ObjectiveFunctional::calculate_gradient_norm(void)
{
   Vector<double> gradient = calculate_gradient();

   return(gradient.calculate_norm());
}


// Vector<double> calculate_objective_gradient(void) method

/// This method returns the default objective function gradient vector, which is computed using numerical 
/// differentiation.

Vector<double> ObjectiveFunctional::calculate_objective_gradient(void)
{
   Vector<double> neural_parameters_gradient = calculate_neural_parameters_gradient();
   Vector<double> independent_parameters_gradient = calculate_independent_parameters_gradient();

   return(neural_parameters_gradient.assemble(independent_parameters_gradient));
}


// Vector<double> calculate_objective_gradient_numerical_differentiation(void) method

/// This method calculates the gradient of the objective term in by means of numerical differentiation. 

Vector<double> ObjectiveFunctional::calculate_objective_gradient_numerical_differentiation(void)
{
   Vector<double> neural_parameters_gradient_numerical_differentiation = calculate_neural_parameters_gradient_numerical_differentiation();
   Vector<double> independent_parameters_gradient_numerical_differentiation = calculate_independent_parameters_gradient_numerical_differentiation();

   return(neural_parameters_gradient_numerical_differentiation.assemble(independent_parameters_gradient_numerical_differentiation));
}


// Vector<double> calculate_regularization_gradient(void) method

/// This method calculates the gradient of the regularization term in by means of numerical differentiation. 

Vector<double> ObjectiveFunctional::calculate_regularization_gradient(void) 
{
   switch(regularization_method)   
   {
      case None:
      {
        int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

        Vector<double> regularization_gradient(parameters_number, 0.0);

        return(regularization_gradient);
      }             
      break;

      case NeuralParametersNorm:
      {  
         Vector<double> neural_parameters = multilayer_perceptron_pointer->get_neural_parameters();                     
           
         double neural_parameters_norm = multilayer_perceptron_pointer->calculate_neural_parameters_norm();

         Vector<double> neural_parameters_regularization_gradient = neural_parameters/neural_parameters_norm;
         
         int independent_parameters_number = multilayer_perceptron_pointer->get_independent_parameters_number();
         
         Vector<double> independent_parameters_regularization_gradient(independent_parameters_number, 0.0);
         
         return(neural_parameters_regularization_gradient.assemble(independent_parameters_regularization_gradient));         
      }             
      break;

	  default:
	  {
          std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                    << "Vector<double> calculate_regularization_gradient(double) method." << std::endl
                    << "Unknown regularization method." << std::endl;
 
          exit(1);       	  
	  }
      break;
   }   
}


// double calculate_actual_epsilon(double) method

/// This method returns the numerical epsilon value to be used for numerical differentiation, 
/// according to the numerical epsilon method used. 
/// @param parameter Parameter value on which depends the numerical epsilon value. 

double ObjectiveFunctional::calculate_actual_epsilon(double parameter)
{
   double actual_epsilon;

   // Numerical epsilon method

   switch(numerical_epsilon_method)   
   {
      case Absolute:
      {
         actual_epsilon = numerical_epsilon;
      }             
      break;
            
      case Relative:
      {
         if(fabs(parameter) < 1.0)
         {
            actual_epsilon = numerical_epsilon;              
         }
         else
         {     
            actual_epsilon = numerical_epsilon*fabs(parameter);
         }
      }                          
      break;           

      default:
      {
          std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                    << "double calculate_actual_epsilon(double) method." << std::endl
                    << "Unknown numerical epsilon method." << std::endl;
 
          exit(1);
      }// end default
      break;
   }// end numerical epsilon switch

   return(actual_epsilon);
}


// Vector<double> calculate_neural_parameters_gradient_numerical_differentiation(void) method

/// This method returns the derivatives of the objective function with respect to the neural parameters 
/// by means of numerical differentiation. 
/// This vector depends on the numerical differentiation method used. 

Vector<double> ObjectiveFunctional::calculate_neural_parameters_gradient_numerical_differentiation(void)  
{
   switch(numerical_differentiation_method)   
   {
      case ForwardDifferences:
      {
         return(calculate_neural_parameters_gradient_forward_differences());
      }

      break;

      case CentralDifferences:
      {
         return(calculate_neural_parameters_gradient_central_differences());
      }

      break;

      default:
      {
         std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                   << "Vector<double> calculate_neural_parameters_gradient_numerical_differentiation(void) method." << std::endl
                   << "Unknown numerical differentiation method." << std::endl;
 
         exit(1);
      }// end default
      break;
   }// end numerical differentiation method switch
}


// Vector<double> calculate_neural_parameters_gradient_forward_differences(void) method 

/// This method returns the derivatives of the objective function with respect to the neural parameters 
/// by means of the forward differences method for numerical differentiation. 

Vector<double> ObjectiveFunctional::calculate_neural_parameters_gradient_forward_differences(void)
{
   int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();

   Vector<double> neural_parameters_gradient(neural_parameters_number);

   // Multilayer perceptron stuff

   Vector<double> potential_neural_parameters = multilayer_perceptron_pointer->get_neural_parameters();   

   Vector<double> scaled_independent_parameters = multilayer_perceptron_pointer->scale_independent_parameters();

   // Objective functional stuff

   double evaluation = calculate_evaluation();

   double evaluation_forward;

   double actual_epsilon;

   // Calculate gradient

   for(int i = 0; i < neural_parameters_number; i++)
   {
      // Calculate actual epsilon

      actual_epsilon = calculate_actual_epsilon(potential_neural_parameters[i]);

	  // Add epsilon to parameter

      potential_neural_parameters[i] += actual_epsilon;

      // Get potential evaluation

      evaluation_forward = calculate_potential_evaluation(potential_neural_parameters.assemble(scaled_independent_parameters));

      // Restart parameter

      potential_neural_parameters[i] -= actual_epsilon;

      // Calculate derivative

      neural_parameters_gradient[i] = (evaluation_forward - evaluation)/actual_epsilon;
   }// end for 

   return(neural_parameters_gradient);
}


// Vector<double> calculate_neural_parameters_gradient_central_differences(void) method 

/// This method returns the derivatives of the objective function with respect to the neural parameters 
/// by means of the central differences method for numerical differentiation. 

Vector<double> ObjectiveFunctional::calculate_neural_parameters_gradient_central_differences(void)
{
   int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();

   Vector<double> neural_parameters_gradient(neural_parameters_number);

   Vector<double> potential_neural_parameters = multilayer_perceptron_pointer->get_neural_parameters();   

   Vector<double> scaled_independent_parameters = multilayer_perceptron_pointer->scale_independent_parameters();

   double actual_epsilon;

   double evaluation_forward;
   double evaluation_backward;

   for(int i = 0; i < neural_parameters_number; i++)
   {
      // Calculate actual epsilon

      actual_epsilon = calculate_actual_epsilon(potential_neural_parameters[i]);

      // Add epsilon to parameter

      potential_neural_parameters[i] += actual_epsilon;

      // Get potential evaluation

      evaluation_forward = calculate_potential_evaluation(potential_neural_parameters.assemble(scaled_independent_parameters));

      // Restart parameter

      potential_neural_parameters[i] -= actual_epsilon;

      // Substract epsilon from parameter

      potential_neural_parameters[i] -= actual_epsilon;

      // Get potential evaluation

      evaluation_backward = calculate_potential_evaluation(potential_neural_parameters.assemble(scaled_independent_parameters));

      // Restart parameter

      potential_neural_parameters[i] += actual_epsilon;

      // Calculate derivative

      neural_parameters_gradient[i] = (evaluation_forward - evaluation_backward)/(2.0*actual_epsilon);

   }// end for

   return(neural_parameters_gradient);
}


// Vector<double> calculate_independent_parameters_gradient_numerical_differentiation(void) method

/// This method returns the derivatives of the objective function with respect to the independent parameters 
/// by means of numerical differentiation. 
/// This vector depends on the numerical differentiation method used. 

Vector<double> ObjectiveFunctional::calculate_independent_parameters_gradient_numerical_differentiation(void)
{
   switch(numerical_differentiation_method)   
   {
      case ForwardDifferences:
      {
         return(calculate_independent_parameters_gradient_forward_differences());
      }

      break;

      case CentralDifferences:
      {
         return(calculate_independent_parameters_gradient_central_differences());
      }

      break;

      default:
      {
         std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                   << "Vector<double> calculate_independent_parameters_gradient_numerical_differentiation(void) method." << std::endl
                   << "Unknown numerical differentiation method." << std::endl;
 
         exit(1);
      }// end default
      break;

   }// end numerical differentiation method switch
}


// Vector<double> calculate_independent_parameters_gradient_forward_differences(void) method 

/// This method returns the derivatives of the objective function with respect to the independent parameters 
/// by means of the forward differences method for numerical differentiation. 

Vector<double> ObjectiveFunctional::calculate_independent_parameters_gradient_forward_differences(void)
{

   // Multilayer perceptron stuff

   Vector<double> neural_parameters = multilayer_perceptron_pointer->get_neural_parameters();

   int independent_parameters_number = multilayer_perceptron_pointer->get_independent_parameters_number();

   Vector<double> scaled_independent_parameters = multilayer_perceptron_pointer->scale_independent_parameters();   

   Vector<double> independent_parameters_lower_bound 
   = multilayer_perceptron_pointer->get_independent_parameters_lower_bound();

   Vector<double> independent_parameters_upper_bound 
   = multilayer_perceptron_pointer->get_independent_parameters_upper_bound();

   // Objective functional stuff

   double evaluation = calculate_evaluation();

   Vector<double> independent_parameters_gradient(independent_parameters_number);

   double evaluation_forward;
   double actual_epsilon;

   // Calculate gradient

   for(int i = 0; i < independent_parameters_number; i++)
   {
      if(independent_parameters_lower_bound != 0 && independent_parameters_upper_bound != 0)
      {
         if(independent_parameters_lower_bound[i] == independent_parameters_upper_bound[i])
         {
            independent_parameters_gradient[i] = 0.0;      
         }
      }
      else
      {
         // Calculate actual epsilon

         actual_epsilon = calculate_actual_epsilon(scaled_independent_parameters[i]);

         // Add epsilon to parameter

         scaled_independent_parameters[i] += actual_epsilon;

         // Get potential evaluation

         evaluation_forward = calculate_potential_evaluation(neural_parameters.assemble(scaled_independent_parameters));

         // Restart parameter

         scaled_independent_parameters[i] -= actual_epsilon;

         // Calculate derivative

         independent_parameters_gradient[i] = (evaluation_forward - evaluation)/actual_epsilon;
      }
   }// end for 

   return(independent_parameters_gradient);
}


// Vector<double> calculate_independent_parameters_gradient_central_differences(void) method 

/// This method returns the derivatives of the objective function with respect to the independent parameters 
/// by means of the forward differences method for numerical differentiation. 

Vector<double> ObjectiveFunctional::calculate_independent_parameters_gradient_central_differences(void)
{
   // Multilayer perceptron stuff

   Vector<double> neural_parameters = multilayer_perceptron_pointer->get_neural_parameters();

   int independent_parameters_number = multilayer_perceptron_pointer->get_independent_parameters_number();

   Vector<double> scaled_independent_parameters = multilayer_perceptron_pointer->scale_independent_parameters();   

   Vector<double> independent_parameters_lower_bound 
   = multilayer_perceptron_pointer->get_independent_parameters_lower_bound();

   Vector<double> independent_parameters_upper_bound 
   = multilayer_perceptron_pointer->get_independent_parameters_upper_bound();

   // Calculate gradient

   Vector<double> independent_parameters_gradient(independent_parameters_number);

   double actual_epsilon;

   double evaluation_forward;
   double evaluation_backward;

   for(int i = 0; i < independent_parameters_number; i++)
   {
      if(independent_parameters_lower_bound.get_size() != 0 && independent_parameters_upper_bound.get_size() != 0)
      {
         if(independent_parameters_lower_bound[i] == independent_parameters_upper_bound[i])
         {
            independent_parameters_gradient[i] = 0.0;      
         }
      }
      else
      {
         // Calculate actual epsilon

         actual_epsilon = calculate_actual_epsilon(scaled_independent_parameters[i]);

         // Add epsilon to parameter

         scaled_independent_parameters[i] += actual_epsilon;

         // Get potential evaluation

         evaluation_forward = calculate_potential_evaluation(neural_parameters.assemble(scaled_independent_parameters));

         // Restart parameter

         scaled_independent_parameters[i] -= actual_epsilon;

         // Substract epsilon from parameter

         scaled_independent_parameters[i] -= actual_epsilon;

         // Get potential evaluation

         evaluation_backward = calculate_potential_evaluation(neural_parameters.assemble(scaled_independent_parameters));

         // Restart parameter

         scaled_independent_parameters[i] += actual_epsilon;

         // Calculate derivative

         independent_parameters_gradient[i] = (evaluation_forward - evaluation_backward)/(2.0*actual_epsilon);
      }
   }// end for

   return(independent_parameters_gradient);
}


// Vector<double> calculate_neural_parameters_gradient(void) method

Vector<double> ObjectiveFunctional::calculate_neural_parameters_gradient(void)
{
   return(calculate_neural_parameters_gradient_numerical_differentiation());
}


// Vector<double> calculate_independent_parameters_gradient(void) method

Vector<double> ObjectiveFunctional::calculate_independent_parameters_gradient(void)
{
   return(calculate_independent_parameters_gradient_numerical_differentiation());
}


// Vector<double> calculate_potential_gradient(const Vector<double>&) method

/// This method returns which would be the objective function gradient of a multilayer perceptron for an 
/// hypothetical vector of parameters.
/// It does not set that vector of parameters to the multilayer perceptron.
/// @param potential_parameters Vector of a potential parameters for the multilayer perceptron associated 
/// to the objective functional.

Vector<double> ObjectiveFunctional::calculate_potential_gradient(const Vector<double>& potential_parameters)
{
   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "double calculate_potential_gradient(const Vector<double>&) method." << std::endl
                << "Multilayer perceptron pointer cannot be NULL." << std::endl;

      exit(1);   
   }

   #endif

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = potential_parameters.get_size();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "double calculate_potential_gradient(const Vector<double>&) method." << std::endl
                << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ")." 
   				 << std::endl;

      exit(1);
   }
   
   #endif
    
   // Calculate potential gradient

   Vector<double> parameters = multilayer_perceptron_pointer->get_parameters();

   Vector<double> potential_gradient(parameters_number);

   // Set potential parameters

   multilayer_perceptron_pointer->set_parameters(potential_parameters);

   // Get Objective function gradient

   potential_gradient = calculate_gradient();

   // Restart original parameters

   multilayer_perceptron_pointer->set_parameters(parameters);

   return(potential_gradient);
}


// Matrix<double> calculate_Hessian_forward_differences(void) method

/// This method returns the Hessian matrix of the objective function calculated by means of
/// the forward differences method for numerical differentiation. 
/// @todo This method is not yet implemented. 

Matrix<double> ObjectiveFunctional::calculate_Hessian_forward_differences(void)
{
   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Matrix<double> Hessian(parameters_number, parameters_number);

   std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
             << "Matrix<double> calculate_Hessian_forward_differences(void) method." << std::endl
             << "Numerical differentiation of Hessian matrix with forward differences is not yet implemented." << std::endl
             << "Please use central differences." << std::endl;
//   exit(1);

   return(Hessian);
}


// Matrix<double> calculate_Hessian_central_differences(void) method

/// This method returns the Hessian matrix of the objective function calculated by means of
/// the central differences method for numerical differentiation. 

Matrix<double> ObjectiveFunctional::calculate_Hessian_central_differences(void)
{
   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Matrix<double> Hessian(parameters_number, parameters_number);

   Vector<double> potential_parameters = multilayer_perceptron_pointer->get_parameters();

   double actual_epsilon_i = 0.0;
   double actual_epsilon_j = 0.0;

   double evaluation_backward_backward = 0.0; 
   double evaluation_backward_forward = 0.0;
   double evaluation_forward_backward = 0.0; 
   double evaluation_forward_forward = 0.0;

   // Obtain the upper part of the Hessian matrix

   for(int i = 0; i < parameters_number; i++)
   {
      // Calculate actual epsilon

      actual_epsilon_i = calculate_actual_epsilon(potential_parameters[i]);

      for(int j = i; j < parameters_number; j++)
      {
         // Calculate actual epsilon

         actual_epsilon_j = calculate_actual_epsilon(potential_parameters[j]);
             
         // Perturb potential parameters i and j

         potential_parameters[i] += actual_epsilon_i;
         potential_parameters[j] += actual_epsilon_j;

         // Calculate evaluation

         evaluation_forward_forward = calculate_potential_evaluation(potential_parameters);

         // Restart potential parameters i and j

         potential_parameters[i] -= actual_epsilon_i;
         potential_parameters[j] -= actual_epsilon_j;

         // Perturb potential parameters i and j

         potential_parameters[i] += actual_epsilon_i;
         potential_parameters[j] -= actual_epsilon_j;

         // Calculate evaluation

         evaluation_forward_backward = calculate_potential_evaluation(potential_parameters);

         // Restart potential parameters i and j

         potential_parameters[i] -= actual_epsilon_i;
         potential_parameters[j] += actual_epsilon_j;

         // Perturb potential parameters i and j

         potential_parameters[i] -= actual_epsilon_i;
         potential_parameters[j] += actual_epsilon_j;

         // Calculate evaluation

         evaluation_backward_forward = calculate_potential_evaluation(potential_parameters);

         // Restart potential parameters i and j

         potential_parameters[i] += actual_epsilon_i;
         potential_parameters[j] -= actual_epsilon_j;

         // Perturb potential parameters i and j

         potential_parameters[i] -= actual_epsilon_i;
         potential_parameters[j] -= actual_epsilon_j;

         // Calculate evaluation

         evaluation_backward_backward = calculate_potential_evaluation(potential_parameters);

         // Restart potential parameters i and j

         potential_parameters[i] += actual_epsilon_i;
         potential_parameters[j] += actual_epsilon_j;

         // Calculate second derivative

         Hessian[i][j] = (evaluation_forward_forward - evaluation_forward_backward
                       - evaluation_backward_forward + evaluation_backward_backward)
                       /(4.0*pow(numerical_epsilon,2));
      }
   }

   // Obtain the rest of elements by symmetry

   for(int i = 0; i < parameters_number; i++)
   {
      for(int j = 0; j < i; j++)
      {
         Hessian[i][j] = Hessian[j][i];
      }
   }

   return(Hessian);
}


// Matrix<double> calculate_Hessian_numerical_differentiation(void) method

/// This method returns the Hessian matrix of the objective function calculated by means of
/// the chosen method for numerical differentiation. 

Matrix<double> ObjectiveFunctional::calculate_Hessian_numerical_differentiation(void)
{
   switch(numerical_differentiation_method)   
   {
      case ForwardDifferences:
      {                      
         return(calculate_Hessian_forward_differences());
      }

      break;
                                     
      case CentralDifferences:
      {
         return(calculate_Hessian_central_differences());
      }

      break;

      default:
      {
          std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                    << "double calculate_Hessian_numerical_differentiation(void) method." << std::endl
                    << "Unknown numerical differentiation method." << std::endl;
 
          exit(1);
      }// end default
      break;

   }// end numerical differentiation method switch
}


// Matrix<double> calculate_Hessian(void) method

/// This method returns the default objective function Hessian matrix, which is computed using numerical 
/// differentiation.

Matrix<double> ObjectiveFunctional::calculate_Hessian(void)
{
   // Increment number of Hessians count
 
   calculate_Hessian_count++;

   return(calculate_Hessian_numerical_differentiation());
}


// Vector<double> calculate_potential_Hessian(const Vector<double>&) method

/// This method returns which would be the objective function Hessian of a multilayer perceptron for an 
/// hypothetical vector of parameters.
/// It does not set that vector of parameters to the multilayer perceptron.
/// @param potential_parameters Vector of a potential parameters for the multilayer perceptron associated 
/// to the objective functional.

Matrix<double> ObjectiveFunctional::calculate_potential_Hessian(const Vector<double>& potential_parameters)
{
   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = potential_parameters.get_size();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "double calculate_potential_Hessian(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   // Calculate potential Hessian

   Vector<double> original_parameters = multilayer_perceptron_pointer->get_parameters();

   Matrix<double> potential_Hessian(parameters_number, parameters_number);

   // Set potential parameters

   multilayer_perceptron_pointer->set_parameters(potential_parameters);

   // Get objective function Hessian

   potential_Hessian = calculate_Hessian();

   // Restart original parameters

   multilayer_perceptron_pointer->set_parameters(original_parameters);

   return(potential_Hessian);
}


// Matrix<double> calculate_inverse_Hessian(void) method

/// This method returns inverse matrix of the Hessian.
/// It first computes the Hessian matrix and then computes its inverse. 

Matrix<double> ObjectiveFunctional::calculate_inverse_Hessian(void)
{  
   Matrix<double> Hessian = calculate_Hessian();
   
   Matrix<double> inverse_Hessian = Hessian.calculate_inverse();
      
   return(inverse_Hessian);               
}


// Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method

/// This method returns an approximation of the inverse Hessian matrix according to the Davidon-Fletcher-Powel 
/// (DFP) algorithm. 
/// @param old_parameters A previous set of parameters.
/// @param old_gradient The gradient of the objective function for that previous set of parameters.
/// @param old_inverse_Hessian The Hessian of the objective function for that previous set of parameters.
/// @param parameters Actual set of parameters.
/// @param gradient The gradient of the objective function for the actual set of parameters.

Matrix<double> ObjectiveFunctional::calculate_DFP_inverse_Hessian(
const Vector<double>& old_parameters, const Vector<double>& parameters, const Vector<double>& old_gradient, const Vector<double>& gradient, const Matrix<double>& old_inverse_Hessian)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();            

   int old_parameters_size = old_parameters.get_size();
   int parameters_size = parameters.get_size();

   if(old_parameters_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of old parameters vector must be equal to number of parameters." << std::endl;

      exit(1);
   }
   else if(parameters_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of parameters vector must be equal to number of parameters." << std::endl;

      exit(1);
   }

   int old_gradient_size = old_gradient.get_size();
   int gradient_size = gradient.get_size();
    
   if(old_gradient_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of old gradient vector must be equal to number of parameters." << std::endl;

      exit(1);
   }
   else if(gradient_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of gradient vector must be equal to number of parameters." << std::endl
                << std::endl;

      exit(1);
   }

   int rows_number = old_inverse_Hessian.get_rows_number();
   int columns_number = old_inverse_Hessian.get_columns_number();

   if(rows_number != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Number of rows in old inverse Hessian must be equal to number of parameters." << std::endl;

      exit(1);
   }
   else if(columns_number != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Number of columns in old inverse Hessian must be equal to number of parameters." << std::endl;

      exit(1);
   }
 
   #endif

   // Parameters difference Vector
   
   Vector<double> parameters_difference = parameters - old_parameters;
   
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(parameters_difference > -1.0e-50 && parameters_difference < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Parameters difference vector is zero." << std::endl;

      exit(1);
   }

   #endif

   // Gradient difference Vector
   
   Vector<double> gradient_difference = gradient - old_gradient;

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(gradient_difference > -1.0e-50 && gradient_difference < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Gradient difference vector is zero." << std::endl;

      exit(1);
   }

   #endif

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(old_inverse_Hessian > -1.0e-50 && old_inverse_Hessian < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Old inverse Hessian matrix is zero." << std::endl;

      exit(1);
   }

   if(fabs(parameters_difference.dot(gradient_difference)) < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Denominator of first term is zero." << std::endl;

      exit(1);
   }
   else if(fabs(gradient_difference.dot(old_inverse_Hessian).dot(gradient_difference)) < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Denominator of second term is zero." << std::endl;

      exit(1);
   }

   #endif

   Matrix<double> DFP_inverse_Hessian = old_inverse_Hessian
   + parameters_difference.outer(parameters_difference)
   /parameters_difference.dot(gradient_difference)
   - (old_inverse_Hessian.dot(gradient_difference)).outer(old_inverse_Hessian.dot(gradient_difference))
   /gradient_difference.dot(old_inverse_Hessian).dot(gradient_difference);

   return(DFP_inverse_Hessian);               

}


// Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Matrix<double>&, const Vector<double>&, const Vector<double>&) method

/// This method returns an approximation of the inverse Hessian matrix according to the 
/// Broyden-Fletcher-Goldfarb-Shanno (BGFS) algorithm. 
/// @param old_parameters A previous set of parameters.
/// @param old_gradient The gradient of the objective function for that previous set of parameters.
/// @param old_inverse_Hessian The Hessian of the objective function for that previous set of parameters.
/// @param parameters Actual set of parameters.
/// @param gradient The gradient of the objective function for the actual set of parameters.

Matrix<double> ObjectiveFunctional::calculate_BFGS_inverse_Hessian(
const Vector<double>& old_parameters, const Vector<double>& parameters, const Vector<double>& old_gradient, const Vector<double>& gradient, const Matrix<double>& old_inverse_Hessian)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();            

   int old_parameters_size = old_parameters.get_size();
   int parameters_size = parameters.get_size();
    
   if(old_parameters_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of old parameters vector must be equal to number of parameters." << std::endl;

      exit(1);
   }
   else if(parameters_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of parameters vector must be equal to number of parameters." << std::endl;

      exit(1);
   }

   int old_gradient_size = old_gradient.get_size();
   int gradient_size = gradient.get_size();

   if(old_gradient_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of old gradient vector must be equal to number of parameters." << std::endl;

      exit(1);
   }
   else if(gradient_size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Size of gradient vector must be equal to number of parameters." << std::endl;

      exit(1);
   }

   int rows_number = old_inverse_Hessian.get_rows_number();
   int columns_number = old_inverse_Hessian.get_columns_number();

   if(rows_number != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Number of rows in old inverse Hessian must be equal to number of parameters." << std::endl;

      exit(1);
   }
   else if(columns_number != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Number of columns in old inverse Hessian must be equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   // Parameters difference Vector
   
   Vector<double> parameters_difference = parameters - old_parameters;


   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(parameters_difference > -1.0e-50 && parameters_difference < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_BFGS_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Parameters difference vector is zero." << std::endl;

      exit(1);
   }

   #endif

   // Gradient difference Vector
   
   Vector<double> gradient_difference = gradient - old_gradient;

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(gradient_difference > -1.0e-50 && gradient_difference < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Gradient difference vector is zero." << std::endl;

      exit(1);
   }

   #endif

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(old_inverse_Hessian > -1.0e-50 && old_inverse_Hessian < 1.0e-50)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Matrix<double> calculate_DFP_inverse_Hessian(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method." << std::endl
                << "Old inverse Hessian matrix is zero." << std::endl;

      exit(1);
   }

   #endif

   // BGFS Vector

   Vector<double> BFGS = parameters_difference/parameters_difference.dot(gradient_difference) 
   - old_inverse_Hessian.dot(gradient_difference)
   /gradient_difference.dot(old_inverse_Hessian).dot(gradient_difference);

   // Calculate inverse Hessian approximation

   Matrix<double> BFGS_inverse_Hessian = old_inverse_Hessian
   + parameters_difference.outer(parameters_difference)
   /parameters_difference.dot(gradient_difference) 
   - (old_inverse_Hessian.dot(gradient_difference)).outer(gradient_difference.dot(old_inverse_Hessian))
   /gradient_difference.dot(old_inverse_Hessian).dot(gradient_difference)
   + (BFGS.outer(BFGS))*(gradient_difference.dot(old_inverse_Hessian).dot(gradient_difference));   
   
   return(BFGS_inverse_Hessian);               
}


// Vector<double> calculate_vector_dot_Hessian_forward_differences(const Vector<double>&) method

/// This method returns the dot product between a given vector and the Hessian matrix of the objective function 
/// by means of the forward differences method for numerical differentiation. 
/// @todo This method is not yet implemented. 
/// @param vector Vector in the dot product. 

Vector<double> ObjectiveFunctional::calculate_vector_dot_Hessian_forward_differences(const Vector<double>&)
{
   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> vector_Hessian_product(parameters_number);

   std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
             << "Vector<double> calculate_vector_dot_Hessian(Vector<double>) method." << std::endl
             << "Numerical differentiation of vector-Hessian matrix with forward differences is not yet implemented." << std::endl
             << "Please use central differences." << std::endl;

//   exit(1);

   return(vector_Hessian_product);
}


// Vector<double> calculate_vector_dot_Hessian_central_differences(Vector<double>) method

/// This method returns the dot product between a given vector and the Hessian matrix of the objective function 
/// by means of the forward differences method for numerical differentiation. 
/// @param vector Vector in the dot product. 

Vector<double> ObjectiveFunctional::calculate_vector_dot_Hessian_central_differences(const Vector<double>& vector)
{ 
   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = vector.get_size();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Vector<double> calculate_vector_dot_Hessian_central_differences(Vector<double>) method." << std::endl
                << "Size of vector must be equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> vector_Hessian_product;

   Vector<double> gradient_forward(parameters_number);
   Vector<double> gradient_backward(parameters_number);

   double actual_epsilon;

   Vector<double> potential_parameters = multilayer_perceptron_pointer->get_parameters();

   for(int i = 0; i < parameters_number; i++)
   {
      // Calculate actual epsilon

      actual_epsilon = calculate_actual_epsilon(potential_parameters[i]);

      // Add actual_epsilon*vector[i] to parameter i

      potential_parameters[i] += actual_epsilon*vector[i];

      // Calculate objective function gradient

      gradient_forward = calculate_potential_gradient(potential_parameters);

      // Restart parameter i

      potential_parameters[i] -= actual_epsilon*vector[i];

      // Substract numerical_epsilon*vector[i] to parameter i

      potential_parameters[i] -= actual_epsilon*vector[i];

      // Calculate objective function gradient

      gradient_backward = calculate_potential_gradient(potential_parameters);

      // Restart potential parameter i

      potential_parameters[i] += actual_epsilon*vector[i];

      // Calculate the product

      vector_Hessian_product[i] = (gradient_forward[i] - gradient_backward[i])/(2.0*actual_epsilon);
   }

   return(vector_Hessian_product);
}


// Vector<double> calculate_vector_dot_Hessian(Vector<double>) method

/// This method returns the default product of some vector with the objective function Hessian matrix, which is 
/// computed using numerical differentiation.
/// @param vector Vector in the dot product. 

Vector<double> ObjectiveFunctional::calculate_vector_dot_Hessian(const Vector<double>& vector)
{
   // Control sentence

   int size = vector.get_size();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "Vector<double> calculate_vector_dot_Hessian(Vector<double>) method." << std::endl
                << "Size of vector must be equal to number of parameters." << std::endl;

      exit(1);
   }

   // Calculate vector Hessian product

   Vector<double> vector_Hessian_product(parameters_number);

   switch(numerical_differentiation_method)   
   {
      case ForwardDifferences:
      {
          vector_Hessian_product = calculate_vector_dot_Hessian_forward_differences(vector);
      }

      break;
                                     
      case CentralDifferences:
      {
          vector_Hessian_product = calculate_vector_dot_Hessian_central_differences(vector);
      }

      break;
   }// end numerical differentiation method switch

   return(vector_Hessian_product);
}


// double calculate_validation_error(void) method

double ObjectiveFunctional::calculate_validation_error(void)
{
   return(0.0);
}


// std::string to_XML(bool) method 

/// This method returns a default string representation of and objective functional object, in a XML-type format. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string ObjectiveFunctional::to_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='ObjectiveFunctional'>" << std::endl;
   }

   buffer << "<RegularizationMethod>" << std::endl
     	  << get_regularization_method_name() << std::endl
          << "</RegularizationMethod>" << std::endl;
 
   buffer << "<ObjectiveWeight>" << std::endl
          << objective_weight << std::endl
          << "</ObjectiveWeight>" << std::endl;
   buffer << "<RegularizationWeight>" << std::endl
    	  << regularization_weight << std::endl
          << "</RegularizationWeight>" << std::endl;
 
    buffer << "<CalculateEvaluationCount>" << std::endl
   	      << calculate_evaluation_count << std::endl
          << "</CalculateEvaluationCount>" << std::endl;

   buffer << "<CalculateGradientCount>" << std::endl
	      << calculate_gradient_count << std::endl
          << "</CalculateGradientCount>" << std::endl;

   buffer << "<CalculateHessianCount>" << std::endl
	      << calculate_Hessian_count << std::endl
          << "</CalculateHessianCount>" << std::endl;

   buffer << "<NumericalDifferentiationMethod>" << std::endl
	      << get_numerical_differentiation_method_name() << std::endl
          << "</NumericalDifferentiationMethod>" << std::endl;

   buffer << "<NumericalEpsilonMethod>" << std::endl
	      << get_numerical_epsilon_method_name() << std::endl
          << "</NumericalEpsilonMethod>" << std::endl;

   buffer << "<NumericalEpsilon>" << std::endl
   	      << numerical_epsilon << std::endl
          << "</NumericalEpsilon>" << std::endl;
      
   buffer << "<Display>" << std::endl
	      << display << std::endl
          << "</Display>" << std::endl;

   return(buffer.str());   
}


// void print(void) method

/// This method prints the members of the objective functional object to the screen in XML-type format. 

void ObjectiveFunctional::print(void)
{
	std::cout << to_XML(true) << std::endl;
}


// void save(const char*) method

/// This method saves to a XML-type file a string representation of the objective functional object. 
/// @param filename Name of XML-type objective functional file. 

void ObjectiveFunctional::save(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void save(const char*) method." << std::endl
                << "Cannot open objective functional XML-type file." << std::endl;

      exit(1);
   }

   // Write file header

   file << to_XML(true);

   // Close file

   file.close();
}


// void load(const char*) method

/// This method loads a default objective functional XML-type file. 
/// @param filename Name of default XML-type objective functional file. 

void ObjectiveFunctional::load(const char* filename)
{
   std::fstream file;

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open objective functional XML-type file." << std::endl;

      exit(1);
   }

   std::string line;
   std::string word;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='ObjectiveFunctional'>") 
   {
//      std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
//                << "void load(const char*) method." << std::endl
//				<< "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   // Objective weight

   while(!file.eof())
   {
      file >> word;
   
      if(word == "<RegularizationMethod>") 
      {
         std::string new_regularization_method_name;

         file >> new_regularization_method_name;

		 set_regularization_method(new_regularization_method_name);

         file >> word;

		 if(word != "</RegularizationMethod>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown regularization method end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
	  else if(word == "<ObjectiveWeight>")
	  {
         double new_objective_weight;

		 file >> new_objective_weight;

		 set_objective_weight(new_objective_weight);

         file >> word;

		 if(word != "</ObjectiveWeight>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown objective weight end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<RegularizationWeight>")
	  {
	     double new_regularization_weight;

		 file >> new_regularization_weight;

		 set_regularization_weight(new_regularization_weight);

         file >> word;

		 if(word != "</RegularizationWeight>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown regularization weight end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<CalculateEvaluationCount>")
	  {
         int new_calculate_evaluation_count;

		 file >> new_calculate_evaluation_count;

		 set_calculate_evaluation_count(new_calculate_evaluation_count);

         file >> word;

		 if(word != "</CalculateEvaluationCount>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown calculate evaluation count end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<CalculateGradientCount>")
	  {
         int new_calculate_gradient_count;

		 file >> new_calculate_gradient_count;

		 set_calculate_gradient_count(new_calculate_gradient_count);

         file >> word;

		 if(word != "</CalculateGradientCount>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown calculate gradient count end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<CalculateHessianCount>")
	  {
         int new_calculate_Hessian_count;

		 file >> new_calculate_Hessian_count;

		 set_calculate_Hessian_count(new_calculate_Hessian_count);

         file >> word;

		 if(word != "</CalculateHessianCount>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown calculate Hessian count end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<NumericalDifferentiationMethod>")
	  {
		 std::string new_numerical_differentiation_method_name;

         file >> new_numerical_differentiation_method_name;

		 set_numerical_differentiation_method(new_numerical_differentiation_method_name);

         file >> word;

		 if(word != "</NumericalDifferentiationMethod>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown numerical differentiation method end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<NumericalEpsilonMethod>")
	  {
    	 std::string new_numerical_epsilon_method_name;

         file >> new_numerical_epsilon_method_name;

		 set_numerical_epsilon_method(new_numerical_epsilon_method_name);

         file >> word;

		 if(word != "</NumericalEpsilonMethod>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown numerical epsilon method end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<NumericalEpsilon>")
	  {
         double new_numerical_epsilon;

		 file >> new_numerical_epsilon;

		 set_numerical_epsilon(new_numerical_epsilon);

         file >> word;

		 if(word != "</NumericalEpsilon>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown numerical epsilon end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<Display>")
	  {
         bool new_display;

		 file >> new_display;

		 set_display(new_display);

         file >> word;

		 if(word != "</Display>") 
         {
            std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown display end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else
	  {
//         std::cerr << "Flood Error: ObjectiveFunctional class." << std::endl
//                   << "void load(const char*) method." << std::endl
//      			   << "Unknown tag: " << word << std::endl;
 
//         exit(1);  
 	  }
   }

   file.close();
}


// void print_information(void) method

/// This method prints any useful information about the objective function during training. By default it prints 
/// nothing.

void ObjectiveFunctional::print_information(void)  
{
   // Do nothing
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
