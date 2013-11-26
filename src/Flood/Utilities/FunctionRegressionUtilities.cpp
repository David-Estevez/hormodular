/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   F U N C T I O N   R E G R E S S I O N   U T I L I T I E S   C L A S S                                      */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

// Flood includes

#include "FunctionRegressionUtilities.h"

namespace Flood
{

// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a function regression utilities object 
/// nor associated to a multilayer perceptron neither to an input-target data set.

FunctionRegressionUtilities::FunctionRegressionUtilities(void)
{
   multilayer_perceptron_pointer = NULL;
   input_target_data_set_pointer = NULL;

   display = true;
}


// MULTILAYER PERCEPTRON CONSTRUCTOR

/// Multilayer perceptron constructor. It creates a function regression utilities object 
/// associated to a multilayer perceptron but not to a an input-target data set.
///
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.

FunctionRegressionUtilities::FunctionRegressionUtilities(MultilayerPerceptron* new_multilayer_perceptron_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;
   input_target_data_set_pointer = NULL;

   display = true;
}


// INPUT-TARGET DATA SET CONSTRUCTOR

/// Input-target data set constructor. It creates a function regression utilities object 
/// associated to an input-target data set but not to a multilayer perceptron.
///
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

FunctionRegressionUtilities::FunctionRegressionUtilities(InputTargetDataSet* new_input_target_data_set_pointer)
{
   multilayer_perceptron_pointer = NULL;
   input_target_data_set_pointer = new_input_target_data_set_pointer;

   display = true;
}


// GENERAL CONSTRUCTOR

/// General constructor. It creates a function regression utilities object 
/// associated to a multilayer perceptron and an input-target data set objects.
///
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

FunctionRegressionUtilities::FunctionRegressionUtilities
(MultilayerPerceptron* new_multilayer_perceptron_pointer, InputTargetDataSet* new_input_target_data_set_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;
   
   input_target_data_set_pointer = new_input_target_data_set_pointer;

   display = true;
}


// DESTRUCTOR

/// Destructor. 

FunctionRegressionUtilities::~FunctionRegressionUtilities()
{
}


// METHODS

// MultilayerPerceptron* get_multilayer_perceptron_pointer(void) method

/// This method returns a pointer to the multilayer perceptron object which is 
/// to be validated.

MultilayerPerceptron* FunctionRegressionUtilities::get_multilayer_perceptron_pointer(void)
{
   return(multilayer_perceptron_pointer);   
}


// InputTargetDataSet* get_input_target_data_set(double) method

/// This method returns a pointer to the input-target data set object used for 
/// validating the performance of a trained multilayer perceptron.

InputTargetDataSet* FunctionRegressionUtilities::get_input_target_data_set_pointer(void)
{
   return(input_target_data_set_pointer);   
}


// bool get_display(void) method

/// This method returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.

bool FunctionRegressionUtilities::get_display(void)
{
   return(display);     
}


// void set_multilayer_perceptron_pointer(MultilayerPerceptron*) method

/// This method sets a new multilayer perceptron which is to be validated.
///
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.

void FunctionRegressionUtilities::set_multilayer_perceptron_pointer(MultilayerPerceptron* new_multilayer_perceptron_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;   
}


// void set_input_target_data_set_pointer(InputTargetDataSet*) method

/// This method sets a new input-target data set to be used for validating the
/// quality of a trained multilayer perceptron.
///
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

void FunctionRegressionUtilities
::set_input_target_data_set_pointer(InputTargetDataSet* new_input_target_data_set_pointer)
{
   input_target_data_set_pointer = new_input_target_data_set_pointer;   
}


// void set_display(bool) method

/// This method sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
///
/// @param new_display Display value.

void FunctionRegressionUtilities::set_display(bool new_display)
{
   display = new_display;
}


// Vector< Matrix<double> >  calculate_testing_target_output_data(void) method

/// This method returns a vector of matrices with number of rows equal to number of testing instances and 
/// number of columns equal to two (the target value and the output value). 

Vector< Matrix<double> > FunctionRegressionUtilities::calculate_testing_target_output_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl 
                << "Vector< Matrix<double> > calculate_testing_target_output_data(void)." << std::endl
                << "Multilayer perceptron object cannot be null." << std::endl;

      exit(1);   
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl 
                << "Vector< Matrix<double> > calculate_testing_target_output_data(void)." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif

   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   int testing_instances_number = input_target_data_set_pointer->get_testing_instances_number(); 

   Vector< Matrix<double> > testing_target_output_data(outputs_number);  

   Matrix<double> testing_input_data = input_target_data_set_pointer->get_testing_input_data();

   Matrix<double> testing_target_data = input_target_data_set_pointer->get_testing_target_data();

   Matrix<double> testing_output_data = multilayer_perceptron_pointer->calculate_output_matrix(testing_input_data);

   for(int i = 0; i < outputs_number; i++)
   {
      testing_target_output_data[i].set(testing_instances_number, 2);

	  for(int j = 0; j < testing_instances_number; j++)
	  {
         testing_target_output_data[i][j][0] = testing_target_data[j][i];
         testing_target_output_data[i][j][1] = testing_output_data[j][i];
	  }
   }

   return(testing_target_output_data);
}


// std::string get_testing_target_output_data(bool) method

/// This method returns a string in XML-type format with the targets and the corresponding outputs for the testing instances
/// in the data set. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string FunctionRegressionUtilities::get_testing_target_output_data(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='FunctionRegressionUtilities' content='TestingTargetOutputData'>" << std::endl;
   }

   Vector< Matrix<double> > testing_target_output_data = calculate_testing_target_output_data();

   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   for(int i = 0; i < outputs_number; i++)
   {   
      buffer << "<OutputVariable>" << std::endl;
      buffer << testing_target_output_data[i];
      buffer << "</OutputVariable>" << std::endl;
   }
   
   return(buffer.str());
}


// void print_testing_target_output_data(void) method

/// This method prints to the screen in XML-type format with the targets and the corresponding outputs for 
/// the testing instances in the data set. 

void FunctionRegressionUtilities::print_testing_target_output_data(void)
{
   std::cout << get_testing_target_output_data(true);
}



// void save_testing_target_output_data(const char*) method

/// This method saves to to a XML-type file the targets and the corresponding outputs for 
/// the testing instances in the data set. 

void FunctionRegressionUtilities::save_testing_target_output_data(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl
                << "void save_testing_target_output_data(const char*) method." << std::endl
                << "Cannot open testing target output data file." << std::endl;

      exit(1);
   }

   file << get_testing_target_output_data(true);

   file.close();
}



// Vector< Vector<double> > calculate_linear_regression_parameters(void)

/// This method performs a linear regression analysis between the testing instances in the data set and 
/// the corresponding neural network outputs. 
/// It returns all the provided parameters in a vector of vectors. 
/// The number of elements in the vector is equal to the number of output variables. 
/// The size of each element is equal to the number of regression parameters (2). 
/// In this way, each subvector contains the regression parameters intercept and slope of an output variable.

Vector< Vector<double> > FunctionRegressionUtilities::calculate_linear_regression_parameters(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl 
                << "Matrix<double> calculate_linear_regression_parameters(void)." << std::endl
                << "Multilayer perceptron object cannot be null." << std::endl;

      exit(1);   
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl 
                << "Matrix<double> calculate_linear_regression_parameters(void)." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif

   // Multilayer perceptron stuff
                            
   int inputs_number = multilayer_perceptron_pointer->get_outputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Input target data set stuff

   int testing_instances_number = input_target_data_set_pointer->get_testing_instances_number();

   // Get regression parameters

   Vector<double> input(inputs_number);
   Vector<double> target(outputs_number);
   Vector<double> output(outputs_number);

   Vector<double> targets_sum(outputs_number, 0.0);
   Vector<double> squared_targets_sum(outputs_number, 0.0);
   Vector<double> outputs_sum(outputs_number, 0.0);
   Vector<double> targets_outputs_sum(outputs_number, 0.0);

   for(int i = 0; i < testing_instances_number; i++)
   {
      target = input_target_data_set_pointer->get_testing_target_instance(i);   

      input = input_target_data_set_pointer->get_testing_input_instance(i);   
	  output = multilayer_perceptron_pointer->calculate_output(input);   

	  targets_sum += target;
	  squared_targets_sum += target*target;
	  outputs_sum += output;
      targets_outputs_sum += target*output;
   }

   Vector<double> intercept = (outputs_sum*squared_targets_sum-targets_sum*targets_outputs_sum)
   /(squared_targets_sum*testing_instances_number - targets_sum*targets_sum);
	  

   Vector<double> slope = (targets_outputs_sum*testing_instances_number - outputs_sum*targets_sum)
   /(squared_targets_sum*testing_instances_number - targets_sum*targets_sum);

   Vector< Vector<double> > linear_regression_parameters(outputs_number);   

   for(int i = 0; i < outputs_number; i++)
   {
      linear_regression_parameters[i].set(2);

	  linear_regression_parameters[i][0] = intercept[i];
      linear_regression_parameters[i][1] = slope[i];
   }
 
   return(linear_regression_parameters);          
}


// std::string get_linear_regression_parameters(bool) method

/// This method returns an XML-type string with the linear regression parameters 
/// (intercept and slope).
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string FunctionRegressionUtilities::get_linear_regression_parameters(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='FunctionRegressionUtilities' content='LinearRegressionParameters'>" << std::endl;
   }

   Vector< Vector<double> > linear_regression_parameters = calculate_linear_regression_parameters();

   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   for(int i = 0; i < outputs_number; i++)
   {   
      buffer << "<OutputVariable>" << std::endl;
 
      buffer << "<Intercept>" << std::endl
	         << linear_regression_parameters[i][0] << std::endl
             << "</Intercept>" << std::endl;

	  buffer << "<Slope>" << std::endl
	         << linear_regression_parameters[i][1] << std::endl
	         << "</Slope>" << std::endl;

      buffer << "</OutputVariable>" << std::endl;
   }
   
   return(buffer.str());
}


// void print_linear_regression_parameters(void) method

/// This method prints to the screen in an XML-type format the linear regression parameters 
/// (intercept and slope).

void FunctionRegressionUtilities::print_linear_regression_parameters(void)
{
	std::cout << get_linear_regression_parameters(true);
}


// void save_linear_regression_parameters(const char*) method

/// This method saves to a XML-type file the linear regression parameters 
/// (intercept and slope).
/// @param filename Name of linear regression parameters XML-type file.

void FunctionRegressionUtilities::save_linear_regression_parameters(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl
                << "void save_linear_regression_parameters(const char*) method." << std::endl
                << "Cannot open testing target output data file." << std::endl;

      exit(1);
   }

   file << get_linear_regression_parameters(true);

   file.close();
}


// std::string get_linear_regression_analysis(bool) method

/// This method returns a XML-type string with the complete linear regression analysis results:
/// <ul> 
/// <li> Linear regression parameters.
/// <li> Targets and outputs for the testing instances. 
/// </ul>
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string FunctionRegressionUtilities::get_linear_regression_analysis(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='FunctionRegressionUtilities' content='LinearRegressionAnalysis'>" << std::endl;
   }

   Vector< Vector<double> > linear_regression_parameters = calculate_linear_regression_parameters();
   Vector< Matrix<double> > testing_target_output_data = calculate_testing_target_output_data();

   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   for(int i = 0; i < outputs_number; i++)
   {
      buffer << "<OutputVariable>" << std::endl;
 
      buffer << "<Intercept>" << std::endl
	         << linear_regression_parameters[i][0] << std::endl
             << "</Intercept>" << std::endl;

	  buffer << "<Slope>" << std::endl
	         << linear_regression_parameters[i][1] << std::endl
	         << "</Slope>" << std::endl;
     
	  buffer << "<TestingTargetOutputData>" << std::endl
             << testing_target_output_data[i]
	         << "</TestingTargetOutputData>" << std::endl;

      buffer << "</OutputVariable>" << std::endl;
   }

   return(buffer.str());
}


// void print_linear_regression_analysis(void) method

/// This method prints to the screen the complete results from the linear regression analysis 
/// in an XML-type format. 

void FunctionRegressionUtilities::print_linear_regression_analysis(void)
{
	std::cout << get_linear_regression_analysis(true);
}


// void save_linear_regression_analysis(const char*) method

/// This methods saves to an XML-type file the complete results of linear regression analysis of a multilayer perceptron
/// on an input-target data set. 
/// @param filename Name of linear regression analysis XML-type file.

void FunctionRegressionUtilities::save_linear_regression_analysis(const char* filename)
{ 
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl
                << "void save_linear_regression_analysis(const char*) method." << std::endl
                << "Cannot open regression analysis  XML-type file." << std::endl;

      exit(1);
   }

   file << get_linear_regression_analysis(true);

   file.close();

}


// void generate_artificial_data(const Vector<double>&, const Vector<double>&, const Vector<std::string>&)

/// This method generates artificial input and target data, which can be useful for testing some neural networks
/// algorithms. 
/// The data is generated acording to the number of instances and the number of input and output variables in the 
/// input-target data set object. 
/// The input data matrix is filled at random with values comprised between -1 and +1.
/// The target data matrix is filled with some functions of several variables. 
///
///
/// @param mean Mean values for the input variables. 
/// @param standard_deviation Standard deviation values for the target variables. 
/// @param function_names Names of target functions ("ZeroFunction", "DeJongFunction", "RosenbrockFunction" or "RastriginFunction").

void FunctionRegressionUtilities::generate_artificial_data
(const Vector<double>& mean, const Vector<double>& standard_deviation, const Vector<std::string>& function_names)
{
   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int mean_size = mean.get_size();
   int standard_deviation_size = standard_deviation.get_size();

   if(mean_size != input_variables_number)
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl
				<< "void generate_artificial_data(const Vector<double>&, const Vector<double>&, const Vector<std::string>&) method." << std::endl
                << "Size of mean must be equal to number of input variables." << std::endl;

      exit(1);   
   }

   if(standard_deviation_size != input_variables_number)
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl
				<< "void generate_artificial_data(const Vector<double>&, const Vector<double>&, const Vector<std::string>&) method." << std::endl
                << "Size of standard_deviation must be equal to number of input variables." << std::endl;

      exit(1);   
   }

   int function_names_size = function_names.get_size();

   if(function_names_size != target_variables_number)
   {
      std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl
				<< "void generate_artificial_data(const Vector<double>&, const Vector<double>&, const Vector<std::string>&) method." << std::endl
                << "Size must be equal to number of target variables." << std::endl;

      exit(1);   
   }

   #endif

   // Input-target data set stuff

   int instances_number = input_target_data_set_pointer->get_instances_number();

   Vector<double> input(input_variables_number);
   Vector<double> target(target_variables_number);

   for(int i = 0; i < instances_number; i++)
   {
      input.initialize_normal(mean, standard_deviation);
      
      for(int j = 0; j < target_variables_number; j++)
      {
         if(function_names[j] == "ZeroFunction")   
         {        
      	    target[j] = 0.0;            
         }
         else if(function_names[j] == "DeJongFunction")   
         {        
      	    target[j] = calculate_De_Jong_function_evaluation(input);            
         }
         else if(function_names[j] == "RosenbrockFunction")   
         {
      	    target[j] = calculate_Rosenbrock_function_evaluation(input);            
	     }
         else if(function_names[j] == "RastriginFunction")
         {
      	    target[j] = calculate_Rastrigin_function_evaluation(input);            
   	     }
         else
         {
            std::cerr << "Flood Error: FunctionRegressionUtilities class." << std::endl 
              	 	  << "void generate_artificial_data(const Vector<double>&, const Vector<double>&, const Vector<std::string>&) method." << std::endl
			   	      << "Unknown function name: " << function_names[j] << "." << std::endl;

            exit(1);	  
         }
      }

	  input_target_data_set_pointer->set_input_instance(i, input);
	  input_target_data_set_pointer->set_target_instance(i, target);
   }
}


// double calculate_De_Jong_function_evaluation(const Vector<double>&) method

/// This method returns output value of the De Jong's function for given input values. 
/// @param input Vector of input values. 

double FunctionRegressionUtilities::calculate_De_Jong_function_evaluation(const Vector<double>& input)
{
   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();

   double evaluation = 0.0;

   for(int i = 0; i < input_variables_number; i++)
   {
      evaluation += pow(input[i], 2);
   }            

   return(evaluation);
}


// double calculate_Rosenbrock_function_evaluation(const Vector<double>&) method

/// This method returns output value of the Rosenbrock's function for given input values. 
/// @param input Vector of input values. 

double FunctionRegressionUtilities::calculate_Rosenbrock_function_evaluation(const Vector<double>& input)
{
   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();

   double evaluation = 0.0;

   for(int i = 0; i < input_variables_number-1; i++)
   {
      evaluation += 100.0*pow(input[i+1] - pow(input[i],2), 2) + pow(1.0 - input[i], 2);
   }

   return(evaluation);
}


// double calculate_Rastrigin_function_evaluation(const Vector<double>&) method

/// This method returns output value of the Rastrigin's function for given input values. 
/// @param input Vector of input values. 

double FunctionRegressionUtilities::calculate_Rastrigin_function_evaluation(const Vector<double>& input)
{
   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();

   const double pi = 3.1415927;

   double evaluation = 10.0*input_variables_number;

   for(int i = 0; i < input_variables_number; i++)
   {
      evaluation += pow(input[i], 2) - 10.0*cos(2.0*pi*input[i]);
   }

   return(evaluation);
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
