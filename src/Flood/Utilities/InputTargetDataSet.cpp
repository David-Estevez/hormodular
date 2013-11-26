/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   I N P U T   T A R G E T   D A T A   S E T   C L A S S                                                      */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

// Flood includes

#include "InputTargetDataSet.h"

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>

namespace Flood
{

/// Instances number, input variables number and target variables number constructor. 
/// It creates an input-target data set object with given instances and input and target variables numbers.
/// It also initializes the rest of class members to their default values.
/// @param new_instances_number Number of instances in the data set.
/// @param new_input_variables_number Number of input variables.
/// @param new_target_variables_number Number of target variables.

InputTargetDataSet::InputTargetDataSet(int new_instances_number, int new_input_variables_number, int new_target_variables_number)
{
   set(new_instances_number, new_input_variables_number, new_target_variables_number);
}


// GENERAL CONSTRUCTOR

/// Instances number, input variables number and target variables number constructor. 
/// It creates an input-target data set object with given instances and variables numbers.
/// All the variables are set as input. 
/// It also initializes the rest of class members to their default values.
/// @param new_instances_number Number of instances in the data set.
/// @param new_variables_number Number of variables.

InputTargetDataSet::InputTargetDataSet(int new_instances_number, int new_variables_number)
{
   set(new_instances_number, new_variables_number);
}


// DEFAULT CONSTRUCTOR

/// Default constructor. It creates an input-target data set object with zero instances and zero input and target 
/// variables. 
/// It also initializes the rest of class members to their default values.

InputTargetDataSet::InputTargetDataSet(void)
{
   set();  
}


// FILE CONSTRUCTOR

/// File constructor. It creates an input-target data set object by loading the object members from a XML-type file. 
/// Please mind about the file format. This is specified in the User's Guide.
/// @param filename Input-target data set file name.

InputTargetDataSet::InputTargetDataSet(const char* filename)
{
   set();
   load(filename);
}


// COPY CONSTRUCTOR

/// Copy constructor. It creates a copy of an existing input target data set object. 
///
/// @param other_input_target_data_set Input-target data set object to be copied.

InputTargetDataSet::InputTargetDataSet(const InputTargetDataSet& other_input_target_data_set)
{
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   //std::cout << "Flood Warning: InputTargetDataSet class." << std::endl 
   //          << "InputTargetDataSet(const InputTargetDataSet&) constructor." << std::endl
   //          << "Use of copy constructor might be inefficient." << std::endl;
     
   #endif

   // Data splitting

   training_instances_indices = other_input_target_data_set.training_instances_indices;
   validation_instances_indices = other_input_target_data_set.validation_instances_indices;
   testing_instances_indices = other_input_target_data_set.testing_instances_indices;

   // Input and target variables

   input_variables_indices = other_input_target_data_set.input_variables_indices;
   target_variables_indices = other_input_target_data_set.target_variables_indices;

   // Variables information

   variables_name = other_input_target_data_set.variables_name;
   variables_units = other_input_target_data_set.variables_units;
   variables_description = other_input_target_data_set.variables_description;

   // Utilities

   display = other_input_target_data_set.display;

   // Data

   data = other_input_target_data_set.data;
}


// DESTRUCTOR

/// Destructor. 

InputTargetDataSet::~InputTargetDataSet(void)
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. It assigns to the current object the members of an existing input-target data set object.
///
/// @param other_input_target_data_set Input-target data set object to be assigned.

InputTargetDataSet& InputTargetDataSet::operator=(const InputTargetDataSet& other_input_target_data_set)
{
   if(this != &other_input_target_data_set) 
   {
      // Data splitting

      training_instances_indices = other_input_target_data_set.training_instances_indices;
      validation_instances_indices = other_input_target_data_set.validation_instances_indices;
      testing_instances_indices = other_input_target_data_set.testing_instances_indices;

      // Input and target variables

      input_variables_indices = other_input_target_data_set.input_variables_indices;
      target_variables_indices = other_input_target_data_set.target_variables_indices;

      // Variables information

      variables_name = other_input_target_data_set.variables_name;
      variables_units = other_input_target_data_set.variables_units;
      variables_description = other_input_target_data_set.variables_description;

      // Utilities

      display = other_input_target_data_set.display;

      // Input and target data

      data = other_input_target_data_set.data;
   }

   return(*this);
}


// METHODS

// Vector<int>& get_training_instances_indices(void) method

/// This method returns the indices of the instances which will be used for training.

Vector<int>& InputTargetDataSet::get_training_instances_indices(void)
{
   return(training_instances_indices);
}


// Vector<int>& get_validation_instances_indices(void) method

/// This method returns the indices of the instances which will be used for validation.

Vector<int>& InputTargetDataSet::get_validation_instances_indices(void)
{
   return(validation_instances_indices);
}


// Vector<int>& get_testing_instances_indices(void) method

/// This method returns the indices of the instances which will be used for testing.

Vector<int>& InputTargetDataSet::get_testing_instances_indices(void)
{
   return(testing_instances_indices);
}


// Vector<int>& get_input_variables_indices(void) method

/// This method returns the indices of the input variables.

Vector<int>& InputTargetDataSet::get_input_variables_indices(void)
{
   return(input_variables_indices);
}


/// Vector<int>& get_target_variables_indices(void) method

// This method returns the indices of the target variables.

Vector<int>& InputTargetDataSet::get_target_variables_indices(void)
{
   return(target_variables_indices);
}


// Vector<std::string>& get_variables_name(void) method

/// This method returns the names of all the variables in the data set.

Vector<std::string>& InputTargetDataSet::get_variables_name(void)
{
   return(variables_name);
}


// std::string& get_variable_name(int) method

/// This method returns the name of a single variable in the data set.
/// @param i Index of variable. 

std::string& InputTargetDataSet::get_variable_name(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "std::string& get_variable_name(int) method." << std::endl
                << "Index of variable must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(i >= variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "std::string& get_variable_name(int) method." << std::endl
                << "Index of variable must be less than number of variables." << std::endl;

      exit(1);   
   }

   #endif

   return(variables_name[i]);
}


// Vector<std::string> get_input_variables_name(void) method

/// This method returns the names of the input variables in the data set.

Vector<std::string> InputTargetDataSet::get_input_variables_name(void)
{
   int variables_number = get_variables_number();

   Vector<std::string> input_variables_name;

   if(variables_name.get_size() == variables_number)
   {
      int input_variables_number = get_input_variables_number();

      input_variables_name.set_size(input_variables_number);
      int index;

   	  for(int i = 0; i < input_variables_number; i++)
	  {        
		 index = input_variables_indices[i];

	     input_variables_name[i] = variables_name[index];
      } 
   }

   return(input_variables_name);
}


// Vector<std::string> get_target_variables_name(void) method

/// This method returns the names of the target variables in the data set.

Vector<std::string> InputTargetDataSet::get_target_variables_name(void)
{
   int variables_number = get_variables_number();

   Vector<std::string> target_variables_name;

   if(variables_name.get_size() == variables_number)
   {
      int target_variables_number = get_target_variables_number();

      target_variables_name.set_size(target_variables_number);
      int index;

   	  for(int i = 0; i < target_variables_number; i++)
	  {        
		 index = target_variables_indices[i];

	     target_variables_name[i] = variables_name[index];
      } 
   }

   return(target_variables_name);
}


// Vector<std::string>& get_variables_units(void) method

/// This method returns the units of all the variables in the data set. 

Vector<std::string>& InputTargetDataSet::get_variables_units(void)
{
   return(variables_units);
}


// std::string& get_variable_units(int) method

/// This method returns the units of a single variable in the data set. 
/// @param i Index of variable. 

std::string& InputTargetDataSet::get_variable_units(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "std::string& get_variable_units(int) method." << std::endl
                << "Index of variable must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(i >= variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "std::string& get_variable_units(int) method." << std::endl
                << "Index of variable must be less than number of variables." << std::endl;

      exit(1);   
   }

   #endif

   return(variables_units[i]);
}


// Vector<std::string> get_input_variables_units(void) method

/// This method returns the units of the input variables in the data set. 

Vector<std::string> InputTargetDataSet::get_input_variables_units(void)
{
   int variables_number = get_variables_number();

   Vector<std::string> input_variables_units;

   if(variables_units.get_size() == variables_number)
   {
      int input_variables_number = get_input_variables_number();

      input_variables_units.set_size(input_variables_number);
      int index;

   	  for(int i = 0; i < input_variables_number; i++)
	  {        
		 index = input_variables_indices[i];

	     input_variables_units[i] = variables_units[index];
      } 
   }

   return(input_variables_units);
}


// Vector<std::string> get_target_variables_units(void) method

/// This method returns the units of the target variables in the data set. 

Vector<std::string> InputTargetDataSet::get_target_variables_units(void)
{
   int variables_number = get_variables_number();

   Vector<std::string> target_variables_units;

   if(variables_units.get_size() == variables_number)
   {
      int target_variables_number = get_target_variables_number();

      target_variables_units.set_size(target_variables_number);
      int index;

   	  for(int i = 0; i < target_variables_number; i++)
	  {        
		 index = target_variables_indices[i];

	     target_variables_units[i] = variables_units[index];
      } 
   }

   return(target_variables_units);
}


// Vector<std::string>& get_variables_description(void) method

/// This method returns the description of all the variables in the data set. 

Vector<std::string>& InputTargetDataSet::get_variables_description(void)
{
   return(variables_description);
}


// std::string& get_variable_description(int) method

/// This method returns the description of a single variable in the data set. 
/// @param i Index of variable.

std::string& InputTargetDataSet::get_variable_description(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "std::string& get_variable_description(int) method." << std::endl
                << "Index of variable must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(i >= variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "std::string& get_variable_description(int) method." << std::endl
                << "Index of variable must be less than number of variables." << std::endl;

      exit(1);   
   }

   #endif

   return(variables_description[i]);
}


// Vector<std::string> get_input_variables_description(void) method

/// This method returns the description of the input variables in the data set. 

Vector<std::string> InputTargetDataSet::get_input_variables_description(void)
{
   int variables_number = get_variables_number();

   Vector<std::string> input_variables_description;

   if(variables_units.get_size() == variables_number)
   {
      int input_variables_number = get_input_variables_number();
      input_variables_description.set_size(input_variables_number);
      int index;

   	  for(int i = 0; i < input_variables_number; i++)
	  {        
		 index = input_variables_indices[i];

	     input_variables_description[i] = variables_description[index];
      } 
   }

   return(input_variables_description);
}


// Vector<std::string> get_target_variables_description(void) method

/// This method returns the description of the target variables in the data set. 

Vector<std::string> InputTargetDataSet::get_target_variables_description(void)
{
   int variables_number = get_variables_number();

   Vector<std::string> target_variables_description;

   if(variables_description.get_size() == variables_number)
   {
      int target_variables_number = get_target_variables_number();

      target_variables_description.set_size(target_variables_number);
      int index;

   	  for(int i = 0; i < target_variables_number; i++)
	  {        
		 index = target_variables_indices[i];

	     target_variables_description[i] = variables_description[index];
      } 
   }

   return(target_variables_description);
}


// Vector< Vector<std::string> > get_variables_information(void) method

/// This method returns a vector of vectors with the input and target variables information.
/// The size of this vector is six. 
/// The contents of each element are:
/// <ul>
/// <li> Name of input variables.
/// <li> Units of input variables.
/// <li> Description of input variables.
/// <li> Name of target variables.
/// <li> Units of target variables. 
/// <li> Description of target variables. 
/// </ul>

Vector< Vector<std::string> > InputTargetDataSet::get_variables_information(void)
{
   int variable_index;

   int variables_number = get_variables_number();

   int input_variables_number = get_input_variables_number();

   Vector<std::string> input_variables_name;
   Vector<std::string> input_variables_units;
   Vector<std::string> input_variables_description;

   for(int i = 0; i < input_variables_number; i++)
   {
      variable_index = input_variables_indices[i];

	  if(variables_name.get_size() == variables_number)
	  {
         input_variables_name.set(input_variables_number);
	     input_variables_name[i] = variables_name[variable_index];
	  }

	  if(variables_units.get_size() == variables_number)
	  {
         input_variables_units.set(input_variables_number);
   	     input_variables_units[i] = variables_units[variable_index];
	  }

	  if(variables_description.get_size() == variables_number)
	  {
         input_variables_description.set(input_variables_number);
	     input_variables_description[i] = variables_description[variable_index];  
	  }
   }

   int target_variables_number = get_target_variables_number();

   Vector<std::string> target_variables_name;
   Vector<std::string> target_variables_units;
   Vector<std::string> target_variables_description;

   for(int i = 0; i < target_variables_number; i++)
   {
      variable_index = target_variables_indices[i];

	  if(variables_name.get_size() == variables_number)
	  {
         target_variables_name.set(target_variables_number);
	     target_variables_name[i] = variables_name[variable_index];
	  }

	  if(variables_units.get_size() == variables_number)
	  {
         target_variables_units.set(target_variables_number);
   	     target_variables_units[i] = variables_units[variable_index];
	  }

	  if(variables_description.get_size() == variables_number)
	  {
         target_variables_description.set(target_variables_number);
	     target_variables_description[i] = variables_description[variable_index];  
	  }
   }

   Vector< Vector<std::string> > variables_information(6);

   variables_information[0] = input_variables_name;
   variables_information[1] = input_variables_units;
   variables_information[2] = input_variables_description;

   variables_information[3] = target_variables_name;
   variables_information[4] = target_variables_units;
   variables_information[5] = target_variables_description;

   return(variables_information);
}


// bool get_display(void) method

/// This method returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.

bool InputTargetDataSet::get_display(void)
{
   return(display);   
}


// Matrix<double>& get_data(void) method

/// This method returns a reference to the data matrix in the input-target data set. 
/// The number of rows is equal to the number of instances.
/// The number of columns is equal to the number of variables. 

Matrix<double>& InputTargetDataSet::get_data(void)
{
   return(data);
}


// Matrix<double> get_training_data(void) method

/// This method returns a matrix with the training instances in the input-target data set. 
/// The number of rows is the number of training instances.
/// The number of columns is the number of variables. 

Matrix<double> InputTargetDataSet::get_training_data(void)
{
   int variables_number = get_variables_number();
   Vector<int> variables_indices(variables_number);
   variables_indices.initialize_sequential();

   return(data.get_submatrix(training_instances_indices, variables_indices));
}


// Matrix<double> get_validation_data(void) method

/// This method returns a matrix with the validation instances in the input-target data set. 
/// The number of rows is the number of validation instances.
/// The number of columns is the number of variables. 

Matrix<double> InputTargetDataSet::get_validation_data(void)
{
   int variables_number = get_variables_number();
   Vector<int> variables_indices(variables_number);
   variables_indices.initialize_sequential();

   return(data.get_submatrix(validation_instances_indices, variables_indices));
}


// Matrix<double> get_testing_data(void) method

/// This method returns a matrix with the testing instances in the input-target data set. 
/// The number of rows is the number of testing instances.
/// The number of columns is the number of variables. 

Matrix<double> InputTargetDataSet::get_testing_data(void)
{
   int variables_number = get_variables_number();
   Vector<int> variables_indices(variables_number);
   variables_indices.initialize_sequential();

   return(data.get_submatrix(testing_instances_indices, variables_indices));
}


// Matrix<double> get_input_data(void) method

/// This method returns a matrix with the input variables in the input-target data set.
/// The number of rows is the number of instances.
/// The number of columns is the number of input variables. 

Matrix<double> InputTargetDataSet::get_input_data(void)
{
   int instances_number = get_instances_number();
   Vector<int> instances_indices(instances_number);
   instances_indices.initialize_sequential();

   return(data.get_submatrix(instances_indices, input_variables_indices));
}


// Matrix<double> get_target_data(void) method

/// This method returns a matrix with the target variables in the input-target data set.
/// The number of rows is the number of instances.
/// The number of columns is the number of target variables. 

Matrix<double> InputTargetDataSet::get_target_data(void)
{
   int instances_number = get_instances_number();
   Vector<int> instances_indices(instances_number);
   instances_indices.initialize_sequential();

   return(data.get_submatrix(instances_indices, target_variables_indices));
}


// Matrix<double> get_training_input_data(void) method

/// This method returns a matrix with training instances and input variables.
/// The number of rows is the number of training instances.
/// The number of columns is the number of input variables. 

Matrix<double> InputTargetDataSet::get_training_input_data(void)
{
   return(data.get_submatrix(training_instances_indices, input_variables_indices));
}


// Matrix<double> get_training_target_data(void) method

/// This method returns a matrix with training instances and target variables.
/// The number of rows is the number of training instances.
/// The number of columns is the number of target variables. 

Matrix<double> InputTargetDataSet::get_training_target_data(void) 
{
   return(data.get_submatrix(training_instances_indices, target_variables_indices));
}


// Matrix<double> get_validation_input_data(void) method

/// This method returns a matrix with validation instances and input variables.
/// The number of rows is the number of validation instances.
/// The number of columns is the number of input variables. 

Matrix<double> InputTargetDataSet::get_validation_input_data(void)
{
   return(data.get_submatrix(validation_instances_indices, input_variables_indices));
}


// Matrix<double> get_validation_target_data(void) method

/// This method returns a matrix with validation instances and target variables.
/// The number of rows is the number of validation instances.
/// The number of columns is the number of target variables. 

Matrix<double> InputTargetDataSet::get_validation_target_data(void)
{
   return(data.get_submatrix(validation_instances_indices, target_variables_indices));
}


// Matrix<double> get_testing_input_data(void) method

/// This method returns a matrix with testing instances and input variables.
/// The number of rows is the number of testing instances.
/// The number of columns is the number of input variables. 

Matrix<double> InputTargetDataSet::get_testing_input_data(void)
{
   return(data.get_submatrix(testing_instances_indices, input_variables_indices));
}


// Matrix<double> get_testing_target_data(void) method

/// This method returns a matrix with testing instances and target variables.
/// The number of rows is the number of testing instances.
/// The number of columns is the number of target variables. 

Matrix<double> InputTargetDataSet::get_testing_target_data(void)
{
   return(data.get_submatrix(testing_instances_indices, target_variables_indices));
}


// Vector<double> get_instance(int) method

/// This method returns the input and target values of a single instance in the input-target data set. 
/// @param i Index of the instance. 

Vector<double> InputTargetDataSet::get_instance(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_instance(int) method." << std::endl
                << "Index of instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(i >= instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_instance(int) method." << std::endl
                << "Index of instance must be less than number of instances." << std::endl;

      exit(1);   
   }

   #endif

   // Get instance

   Vector<double> instance = get_input_instance(i);

   return(data.get_row(i));
}


// Vector<double> get_training_instance(int) method

/// This method returns the input and target values of a single training instance in the input-target data set. 
/// @param training_instance_index Index of the training instance. 

Vector<double> InputTargetDataSet::get_training_instance(int training_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int training_instances_number = get_training_instances_number();

   if(training_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_training_instance(int) method." << std::endl
                << "Index of training instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(training_instance_index >= training_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_training_instance(int) method." << std::endl
                << "Index of training instance must be less than number of training instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = training_instances_indices[training_instance_index];

   Vector<double> training_instance = data.get_row(instance_index);

   return(training_instance);
}


// Vector<double> get_validation_instance(int) method

/// This method returns the input and target values of a single validation instance in the input-target data set. 
/// @param validation_instance_index Index of the validation instance. 

Vector<double> InputTargetDataSet::get_validation_instance(int validation_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int validation_instances_number = get_validation_instances_number();

   if(validation_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_validation_instance(int) method." << std::endl
                << "Index of validation instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(validation_instance_index >= validation_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_validation_instance(int) method." << std::endl
                << "Index of validation instance must be less than number of validation instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = validation_instances_indices[validation_instance_index];

   Vector<double> validation_instance = data.get_row(instance_index);

   return(validation_instance);
}


// Vector<double> get_testing_instance(int) method

/// This method returns the input and target values of a single testing instance in the input-target data set. 
/// @param testing_instance_index Index of the testing instance. 

Vector<double> InputTargetDataSet::get_testing_instance(int testing_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int testing_instances_number = get_testing_instances_number();

   if(testing_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_testing_instance(int) method." << std::endl
                << "Index of testing instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(testing_instance_index >= testing_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_testing_instance(int) method." << std::endl
                << "Index of testing instance must be less than number of testing instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = testing_instances_indices[testing_instance_index];

   Vector<double> testing_instance = data.get_row(instance_index);

   return(testing_instance);
}


// Vector<double> get_input_instance(int) method

/// This method returns a vector with the input values of a single instance in the data set. 
/// @param instance_index Index of the instance. 

Vector<double> InputTargetDataSet::get_input_instance(int instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   if(instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_input_instance(int) method." << std::endl
                << "Index of instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(instance_index >= instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_input_instance(int) method." << std::endl
                << "Index of instance must be less than number of instances." << std::endl;

      exit(1);   
   }

   #endif

   int input_variables_number = get_input_variables_number();

   Vector<double> input_instance(input_variables_number);

   int input_variable_index;

   for(int i = 0; i < input_variables_number; i++)
   {
      input_variable_index = input_variables_indices[i];

      input_instance[i] = data[instance_index][input_variable_index];
   }

   return(input_instance);
}


// Vector<double> get_target_instance(int) method

/// This method returns a vector with the target values of a single instance in the data set. 
/// @param instance_index Index of the instance. 

Vector<double> InputTargetDataSet::get_target_instance(int instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   if(instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_target_instance(int) method." << std::endl
                << "Index of instance must be equal or greater than zero." 
                << std::endl;

      exit(1);   
   }
   else if(instance_index >= instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_target_instance(int) method." << std::endl
                << "Index of instance must be less than number of instances." << std::endl;

      exit(1);   
   }

   #endif

   int target_variables_number = get_target_variables_number();

   Vector<double> target_instance(target_variables_number);

   int target_variable_index;

   for(int i = 0; i < target_variables_number; i++)
   {
      target_variable_index = target_variables_indices[i];

      target_instance[i] = data[instance_index][target_variable_index];
   }

   return(target_instance);
}



// Vector<double> get_training_input_instance(int) method

/// This method returns the input values of a given training instance.
/// @param training_instance_index Index of training instance.

Vector<double> InputTargetDataSet::get_training_input_instance(int training_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int training_instances_number = get_training_instances_number();  

   if(training_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_training_input_instance(int) method." << std::endl
                << "Index of training instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(training_instance_index >= training_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_training_input_instance(int) method." << std::endl
                << "Index of training instance (" << training_instance_index << ") must be less than number of training instances (" << training_instances_number << ")." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = training_instances_indices[training_instance_index];      

   return(get_input_instance(instance_index));
}


// Vector<double> get_validation_input_instance(int) method

/// This method returns the input values of a given validation instance.
/// @param validation_instance_index Index of validation instance.

Vector<double> InputTargetDataSet::get_validation_input_instance(int validation_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int validation_instances_number = get_validation_instances_number();
 
   if(validation_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_validation_input_instance(int) method." << std::endl
                << "Index of validation instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(validation_instance_index >= validation_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_validation_input_instance(int) method." << std::endl
                << "Index of validation instance must be less than number of validation instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = validation_instances_indices[validation_instance_index];      

   return(get_input_instance(instance_index));
}


// Vector<double> get_testing_input_instance(int) method

/// This method returns the input values of a given testing instance.
/// @param testing_instance_index Index of testing instance.

Vector<double> InputTargetDataSet::get_testing_input_instance(int testing_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int testing_instances_number = get_testing_instances_number();

   if(testing_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_testing_input_instance(int) method." << std::endl
                << "Index of testing instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(testing_instance_index >= testing_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_testing_input_instance(int) method." << std::endl
                << "Index of testing instance must be less than number of testing instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = testing_instances_indices[testing_instance_index];      

   return(get_input_instance(instance_index));
}

   
// Vector<double> get_training_target_instance(int) method

/// This method returns the target values of a given training instance.
/// @param training_instance_index Index of training instance.

Vector<double> InputTargetDataSet::get_training_target_instance(int training_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int training_instances_number = get_training_instances_number();

   if(training_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_training_target_instance(int) method." << std::endl
                << "Index of training instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(training_instance_index >= training_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_training_target_instance(int) method." << std::endl
                << "Index of training instance must be less than number of training instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = training_instances_indices[training_instance_index];      

   return(get_target_instance(instance_index));
}


// Vector<double> get_validation_target_instance(int) method

/// This method returns the target values of a given validation instance.
/// @param validation_instance_index Index of validation instance.

Vector<double> InputTargetDataSet::get_validation_target_instance(int validation_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int validation_instances_number = get_validation_instances_number();

   if(validation_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_validation_target_instance(int) method." << std::endl
                << "Index of validation instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(validation_instance_index >= validation_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_validation_target_instance(int) method." << std::endl
                << "Index of validation instance must be less than number of validation instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = validation_instances_indices[validation_instance_index];      

   return(get_target_instance(instance_index));
}


// Vector<double> get_testing_target_instance(int) method

/// This method returns the target values of a given testing instance.
/// @param testing_instance_index Index of testing instance.

Vector<double> InputTargetDataSet::get_testing_target_instance(int testing_instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int testing_instances_number = get_testing_instances_number();

   if(testing_instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_testing_target_instance(int) method." << std::endl
                << "Index of testing instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(testing_instance_index >= testing_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "Vector<double> get_testing_target_instance(int) method." << std::endl
                << "Index of testing instance must be less than number of testing instances." << std::endl;

      exit(1);   
   }

   #endif

   int instance_index = testing_instances_indices[testing_instance_index];      

   return(get_target_instance(instance_index));
}


// void set(void) method

/// This method sets zero instances and zero variables in the input-target data set. 

void InputTargetDataSet::set(void)
{
   display = true;
}


// void set(int, int) method

/// This method sets new numbers of instances and variables in the input target data set. 
/// All the instances are set for training. 
/// All the variables are set as input. 
/// @param new_instances_number Number of instances.
/// @param new_variables_number Number of variables.

void InputTargetDataSet::set(int new_instances_number, int new_variables_number)
{
   // Data matrix

   data.set(new_instances_number, new_variables_number);

   // Training, validation and testing indices

   set_training();

   // Input and target variables
  
   set_input();

   // Display

   display = true;
}

// void set(int, int, int) method

/// This method sets new numbers of instances and input and target variables in the input-target data set.
/// All the instances are set for training. 
/// The variables in the data set are the number of inputs plus the number of targets. 
/// The first variables in the data matrix correspond to the input variables.
/// The last variables in the data matrix correspond to the target variables. 
///
/// @param new_instances_number Number of instances.
/// @param new_input_variables_number Number of input variables.
/// @param new_target_variables_number Number of target variables.

void InputTargetDataSet::set(int new_instances_number, int new_input_variables_number, int new_target_variables_number)
{   
   // Data matrix

   int new_variables_number = new_input_variables_number + new_target_variables_number; 

   data.set(new_instances_number, new_variables_number);

   // Training, validation and testing indices

   set_training();
   
   // Input and target variables

   input_variables_indices.set_size(new_input_variables_number);
   input_variables_indices.initialize_sequential();

   target_variables_indices.set_size(new_target_variables_number);
   target_variables_indices.initialize_sequential();
   target_variables_indices += new_input_variables_number;

   display = true;
}


// void set_training_instances_indices(const Vector<int>&) method

/// This method sets new indices for the training instances from a vector of integers.
/// The size of that vector is the number of training instances.
/// This method does not check for repeated indices. 
/// @param new_training_instances_indices Indices of training instances. 

void InputTargetDataSet::set_training_instances_indices(const Vector<int>& new_training_instances_indices)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   int size = new_training_instances_indices.get_size();

   if(size > instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_training_instances_indices(const Vector<double>&) method." << std::endl
                << "Size must be less or equal than number of instances." << std::endl;

      exit(1);
   }
   
   #endif

   training_instances_indices = new_training_instances_indices;
}


// void set_validation_instances_indices(const Vector<int>&) method

/// This method sets new indices for the validation instances from a vector of integers.
/// The size of that vector is the number of validation instances.
/// This method does not check for repeated indices. 
/// @param new_validation_instances_indices Indices of validation instances. 

void InputTargetDataSet::set_validation_instances_indices(const Vector<int>& new_validation_instances_indices)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   int size = new_validation_instances_indices.get_size();

   if(size > instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_validation_instances_indices(const Vector<double>&) method." << std::endl
                << "Size must be less or equal than number of instances." << std::endl;

      exit(1);
   }
   
   #endif

   validation_instances_indices = new_validation_instances_indices;
}


// void set_testing_instances_indices(const Vector<int>&) method

/// This method sets new indices for the testing instances from a vector of integers.
/// The size of that vector is the number of testing instances.
/// This method does not check for repeated indices. 
/// @param new_testing_instances_indices Indices of testing instances. 

void InputTargetDataSet::set_testing_instances_indices(const Vector<int>& new_testing_instances_indices)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   int size = new_testing_instances_indices.get_size();

   if(size > instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_testing_instances_indices(const Vector<double>&) method." << std::endl
                << "Size must be less or equal than number of instances." << std::endl;

      exit(1);
   }
   
   #endif

   testing_instances_indices = new_testing_instances_indices;
}


// void set_training(void) method

/// This method sets all the instances in the data set for training. 

void InputTargetDataSet::set_training(void)
{
   int instances_number = get_instances_number();

   training_instances_indices.set_size(instances_number);
   validation_instances_indices.set_size(0);
   testing_instances_indices.set_size(0);

   training_instances_indices.initialize_sequential();
}


// void set_validation(void) method

/// This method sets all the instances in the data set for validation. 

void InputTargetDataSet::set_validation(void)
{
   int instances_number = get_instances_number();

   training_instances_indices.set_size(0);
   validation_instances_indices.set_size(instances_number);
   testing_instances_indices.set_size(0);

   validation_instances_indices.initialize_sequential();
}


// void set_testing(void) method

/// This method sets all the instances in the data set for testing. 

void InputTargetDataSet::set_testing(void)
{
   int instances_number = get_instances_number();

   training_instances_indices.set_size(0);
   validation_instances_indices.set_size(0);
   testing_instances_indices.set_size(instances_number);

   testing_instances_indices.initialize_sequential();
}


// void set_input_variables_indices(const Vector<int>&) method

/// This method sets new indices for the input variables from a vector of integers.
/// The size of that vector is the number of input variables.
/// This method does not check for repeated indices. 
/// @param new_input_variables_indices Indices of input variables. 

void InputTargetDataSet::set_input_variables_indices(const Vector<int>& new_input_variables_indices)
{
   input_variables_indices = new_input_variables_indices;
}


// void set_target_variables_indices(const Vector<int>&) method

/// This method sets new indices for the target variables from a vector of integers.
/// The size of that vector is the number of target variables.
/// This method does not check for repeated indices. 
/// @param new_target_variables_indices Indices of target variables. 

void InputTargetDataSet::set_target_variables_indices(const Vector<int>& new_target_variables_indices)
{
   target_variables_indices = new_target_variables_indices;
}


// void set_input(void) method

/// This method sets all the variables in the data set as input variables. 

void InputTargetDataSet::set_input(void)
{
   int variables_number = get_variables_number();

   input_variables_indices.resize(variables_number);

   input_variables_indices.initialize_sequential();
}


// void set_target(void) method

/// This method sets all the variables in the data set as target variables. 

void InputTargetDataSet::set_target(void)
{
   int variables_number = get_variables_number();

   target_variables_indices.resize(variables_number);

   target_variables_indices.initialize_sequential();
}


// void set_variables_name(const Vector<std::string>&) method

/// This method sets new names for the variables in the data set from a vector of strings. 
/// The size of that vector must be equal to the total number of variables. 
/// @param new_variables_name Name of variables. 

void InputTargetDataSet::set_variables_name(const Vector<std::string>& new_variables_name)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   int size = new_variables_name.get_size();

   if(size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variables_name(const Vector<std::string>&) method." << std::endl
                << "Size must be equal to number of variables." << std::endl;

      exit(1);
   }
   
   #endif

   variables_name = new_variables_name;
}


// void set_variable_name(int, const std::string&) method

/// This method set the name of a single variable. 
/// If the vector of names is zero the rest of elements are initialized as empty strings. 
/// @param i Index of variable. 
/// @param new_variable_name Name of variable. 

void InputTargetDataSet::set_variable_name(int i, const std::string& new_variable_name)
{
   int variables_number = get_variables_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variable_name(int, const std::string&) method." << std::endl
                << "Index of variable must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(i >= variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variable_name(int, const std::string&) method." << std::endl
                << "Index of variable must be less than number of variables." << std::endl;

      exit(1);   
   }

   #endif

   if(variables_name.get_size() != variables_number)
   {
      variables_name.set(variables_number); 
   }

   // Set name of single variable

   variables_name[i] = new_variable_name;
}


// void set_variables_units(const Vector<std::string>&) method

/// This method sets new units for the variables in the data set from a vector of strings. 
/// The size of that vector must be equal to the total number of variables. 
/// @param new_variables_units Units of variables. 

void InputTargetDataSet::set_variables_units(const Vector<std::string>& new_variables_units)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   int size = new_variables_units.get_size();

   if(size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variables_units(const Vector<std::string>&) method." << std::endl
                << "Size must be equal to number of variables." << std::endl;

      exit(1);
   }
   
   #endif

   variables_units = new_variables_units;
}


// void set_variable_units(int, const std::string&) method

/// This method set the units of a single variable. 
/// If the vector of units is zero the rest of elements are initialized as empty strings. 
/// @param i Index of variable. 
/// @param new_variable_units Units of variable. 

void InputTargetDataSet::set_variable_units(int i, const std::string& new_variable_units)
{
   int variables_number = get_variables_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variable_units(int, const std::string&) method." << std::endl
                << "Index of variable must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(i >= variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variable_units(int, const std::string&) method." << std::endl
                << "Index of variable must be less than number of variables." << std::endl;

      exit(1);   
   }

   #endif

   if(variables_units.get_size() != variables_number)
   {
      variables_units.set(variables_number); 
   }

   // Set units of single variable

   variables_units[i] = new_variable_units;
}


// void set_variables_description(const Vector<std::string>&) method

/// This method sets new descriptions for the variables in the data set from a vector of strings. 
/// The size of that vector must be equal to the total number of variables. 
/// @param new_variables_description Description of variables. 

void InputTargetDataSet::set_variables_description(const Vector<std::string>& new_variables_description)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   int size = new_variables_description.get_size();

   if(size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variables_description(const Vector<std::string>&) method." << std::endl
                << "Size must be equal to number of variables." << std::endl;

      exit(1);
   }
   
   #endif

   variables_description = new_variables_description;
}


// void set_variable_description(int, const std::string&) method

/// This method set the description of a single variable. 
/// If the vector of descriptions is zero the rest of elements are initialized as empty strings. 
/// @param i Index of variable. 
/// @param new_variable_description Description of variable. 

void InputTargetDataSet::set_variable_description(int i, const std::string& new_variable_description)
{
   int variables_number = get_variables_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variable_description(int, const std::string&) method." << std::endl
                << "Index of variable must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(i >= variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variable_description(int, const std::string&) method." << std::endl
                << "Index of variable must be less than number of variables." << std::endl;

      exit(1);   
   }

   #endif

   if(variables_description.get_size() != variables_number)
   {
      variables_description.set(variables_number); 
   }

   // Set description of single variable

   variables_description[i] = new_variable_description;
}


// void set_display(bool) method

/// This method sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void InputTargetDataSet::set_display(const bool new_display)
{
   display = new_display;

   data.set_display(new_display);
}


// void set_data(const Matrix<double>&) method

/// This method sets a new data matrix. 
/// The number of rows must be equal to the number of instances.
/// The number of columns must be equal to the number of variables. 
/// Indices of all training, validation and testing instances and input and target variables do not change.
/// @param new_data Data matrix.

void InputTargetDataSet::set_data(const Matrix<double>& new_data)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int rows_number = new_data.get_rows_number();
   int instances_number = get_instances_number();

   if(rows_number != instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_data(const Matrix<double>&) method." << std::endl
                << "Number of rows must be equal to number of instances." << std::endl;

      exit(1);
   }

   int columns_number = new_data.get_columns_number();
   int variables_number = get_variables_number();

   if(columns_number != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_data(const Matrix<double>&) method." << std::endl
                << "Number of columns must be equal to number of variables." << std::endl;

      exit(1);
   }

   #endif

   // Set data
   
   data = new_data;   
}


// void set_instances_number(int) method

/// This method sets a new number of instances in the input-target data set. 
/// All instances are also set for training. 
/// The indices of the input and target variables do not change. 
/// @param new_instances_number Number of instances. 

void InputTargetDataSet::set_instances_number(int new_instances_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_instances_number < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_instances_number(int) method." << std::endl
                << "New number of instances must be equal or greater than zero." << std::endl;

      exit(1);
   }
   
   #endif

   int variables_number = get_variables_number();

   data.set(new_instances_number, variables_number);

   set_training();
}


// void set_variables_number(int) method

/// This method sets a new number of input variables in the input-target data set. 
/// The indices of the training, validation and testing instances do not change. 
/// All variables are set as input. 
/// @param new_variables_number Number of variables. 

void InputTargetDataSet::set_variables_number(int new_variables_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_variables_number < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_variables_number(int) method." << std::endl
                << "New number of variables must be equal or greater than zero." << std::endl;

      exit(1);
   }
   
   #endif

   int instances_number = get_instances_number();

   data.set(instances_number, new_variables_number);

   set_input();
}


// void set_instance(int, const Vector<double>&)

/// This method sets new input and target values of a single instance in the input-target data set. 
/// @param instance_index Index of the instance. 
/// @param instance New input and target values of the instance.

void InputTargetDataSet::set_instance(int instance_index, const Vector<double>& instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   if(instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_instance(int, const Vector<double>&) method." << std::endl
                << "Index of instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(instance_index >= instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_instance(int, const Vector<double>&) method." << std::endl
                << "Index of instance must be less than number of instances." << std::endl;

      exit(1);   
   }

   int size = instance.get_size();
   int variables_number = get_variables_number();

   if(size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_instance(int, const Vector<double>&) method." << std::endl
                << "Size (" << size << ") must be equal to number of variables (" << variables_number << ")." 
                << std::endl;

      exit(1);   
   } 

   #endif

   // Set instance

   data.set_row(instance_index, instance);
}


// void set_training_instance(int, const Vector<double>&) method

/// This method sets new input and target values of a single training instance in the input-target data set. 
/// @param i Index of the training instance. 
/// @param new_training_instance New input and target values of the training instance.

void InputTargetDataSet::set_training_instance(int i, const Vector<double>& new_training_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int training_instances_number = get_training_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_training_instance(int, const Vector<double>&) method." << std::endl
                << "Training instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= training_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_training_instance(int, const Vector<double>&) method." << std::endl
                << "Training instance index must be less than number of training instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = training_instances_indices[i];

   set_instance(index, new_training_instance);
}


// void set_validation_instance(int, const Vector<double>&) method

/// This method sets new input and target values of a single validation instance in the input-target data set. 
/// @param i Index of the validation instance. 
/// @param new_validation_instance New input and target values of the validation instance.

void InputTargetDataSet::set_validation_instance(int i, const Vector<double>& new_validation_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int validation_instances_number = get_validation_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_validation_instance(int, const Vector<double>&) method." << std::endl
                << "Validation instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= validation_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_validation_instance(int, const Vector<double>&) method." << std::endl
                << "Validation instance index must be less than number of validation instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = validation_instances_indices[i];

   set_instance(index, new_validation_instance);
}


// void set_testing_instance(int, const Vector<double>&) method

/// This method sets new input and target values of a single testing instance in the input-target data set. 
/// @param i Index of the testing instance. 
/// @param new_testing_instance New input and target values of the testing instance.

void InputTargetDataSet::set_testing_instance(int i, const Vector<double>& new_testing_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int testing_instances_number = get_testing_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_testing_instance(int, const Vector<double>&) method." << std::endl
                << "Testing instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= testing_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_testing_instance(int, const Vector<double>&) method." << std::endl
                << "Testing instance index must be less than number of testing instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = testing_instances_indices[i];

   set_instance(index, new_testing_instance);
}


// void set_input_instance(int, const Vector<double>&) method

/// This method sets new input values of a single instance in the input-target data set. 
/// @param instance_index Index of the instance. 
/// @param input_instance New input values of the instance.

void InputTargetDataSet::set_input_instance(int instance_index, const Vector<double>& input_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   if(instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_input_instance(int, const Vector<double>&) method." << std::endl
                << "Index of instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(instance_index >= instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_input_instance(int, const Vector<double>&) method." << std::endl
                << "Index of instance must be less than number of instances." << std::endl;

      exit(1);   
   }

   #endif

   int input_variables_number = get_input_variables_number();

   #ifdef _DEBUG 

   int size = input_instance.get_size();

   if(size != input_variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_input_instance(int, const Vector<double>&) method." << std::endl
                << "Size of input instance must be equal to number of input variables." << std::endl;

      exit(1);   
   }

   #endif

   int input_variable_index;

   for(int i = 0; i < input_variables_number; i++)
   {
      input_variable_index = input_variables_indices[i];

      data[instance_index][input_variable_index] = input_instance[i];
   }
}


// void set_target_instance(int, const Vector<double>&) method

/// This method sets new target values of a single instance in the input-target data set. 
/// @param instance_index Index of the instance. 
/// @param target_instance New target values of the instance.

void InputTargetDataSet::set_target_instance(int instance_index, const Vector<double>& target_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   if(instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_target_instance(int, const Vector<double>&) method." << std::endl
                << "Index of instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(instance_index >= instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_target_instance(int, const Vector<double>&) method." << std::endl
                << "Index of instance must be less than number of instances." << std::endl;

      exit(1);   
   }

   #endif

   int target_variables_number = get_target_variables_number();

   #ifdef _DEBUG 

   int size = target_instance.get_size();

   if(size != target_variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_target_instance(int, const Vector<double>&) method." << std::endl
                << "Size of target instance must be equal to number of target variables." << std::endl;

      exit(1);   
   }

   #endif

   int target_variable_index;

   for(int i = 0; i < target_variables_number; i++)
   {
      target_variable_index = target_variables_indices[i];

      data[instance_index][target_variable_index] = target_instance[i];
   }
}


// void set_training_input_instance(int, const Vector<double>&) method

/// This method sets new input values of a single training instance in the input-target data set. 
/// @param i Index of the training instance. 
/// @param new_training_input_instance New input values of that instance.

void InputTargetDataSet::set_training_input_instance(int i, const Vector<double>& new_training_input_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int training_instances_number = get_training_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_training_input_instance(int, const Vector<double>&) method." << std::endl
                << "Training instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= training_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_training_input_instance(int, const Vector<double>&) method." << std::endl
                << "Training instance index must be less than number of training instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = training_instances_indices[i];

   set_input_instance(index, new_training_input_instance);
}


// void set_validation_input_instance(int, const Vector<double>&) method

/// This method sets new input values of a single validation instance in the input-target data set. 
/// @param i Index of the validation instance. 
/// @param new_validation_input_instance New input values of that instance.

void InputTargetDataSet::set_validation_input_instance(int i, const Vector<double>& new_validation_input_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int validation_instances_number = get_validation_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_validation_input_instance(int, const Vector<double>&) method." << std::endl
                << "Validation instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= validation_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_validation_input_instance(int, const Vector<double>&) method." << std::endl
                << "Validation instance index must be less than number of validation instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = validation_instances_indices[i];

   set_input_instance(index, new_validation_input_instance);
}


// void set_testing_input_instance(int, const Vector<double>&) method

/// This method sets new input values of a single testing instance in the input-target data set. 
/// @param i Index of the testing instance. 
/// @param new_testing_input_instance New input values of that instance.

void InputTargetDataSet::set_testing_input_instance(int i, const Vector<double>& new_testing_input_instance)
{   
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int testing_instances_number = get_testing_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_testing_input_instance(int, const Vector<double>&) method." << std::endl
                << "Testing instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= testing_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_testing_input_instance(int, const Vector<double>&) method." << std::endl
                << "Testing instance index must be less than number of testing instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = testing_instances_indices[i];

   set_input_instance(index, new_testing_input_instance);
}


// void set_training_target_instance(int, const Vector<double>&) method

/// This method sets new target values of a single training instance in the input-target data set. 
/// @param i Index of the training instance. 
/// @param new_training_target_instance New target values of that instance.

void InputTargetDataSet::set_training_target_instance(int i, const Vector<double>& new_training_target_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int training_instances_number = get_training_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_training_target_instance(int, const Vector<double>&) method." << std::endl
                << "Training instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= training_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_training_target_instance(int, const Vector<double>&) method." << std::endl
                << "Training instance index must be less than number of training instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = training_instances_indices[i];

   set_target_instance(index, new_training_target_instance);
}


// void set_validation_target_instance(int, const Vector<double>&) method

/// This method sets new target values of a single validation instance in the input-target data set. 
/// @param i Index of the validation instance. 
/// @param new_validation_target_instance New target values of that instance.

void InputTargetDataSet::
set_validation_target_instance(int i, const Vector<double>& new_validation_target_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int validation_instances_number = get_validation_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_validation_target_instance(int, const Vector<double>&) method." << std::endl
                << "Validation instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= validation_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_validation_target_instance(int, const Vector<double>&) method." << std::endl
                << "Validation instance index must be less than number of validation instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = validation_instances_indices[i];

   set_target_instance(index, new_validation_target_instance);
}


// void set_testing_target_instance(int, const Vector<double>&) method

/// This method sets new target values of a single testing instance in the input-target data set. 
/// @param i Index of the testing instance. 
/// @param new_testing_target_instance New target values of that instance.

void InputTargetDataSet::set_testing_target_instance(int i, const Vector<double>& new_testing_target_instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int testing_instances_number = get_testing_instances_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_testing_target_instance(int, const Vector<double>&) method." << std::endl
                << "Testing instance index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= testing_instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void set_testing_target_instance(int, const Vector<double>&) method." << std::endl
                << "Testing instance index must be less than number of testing instances." << std::endl;

      exit(1);
   }
   
   #endif

   int index = testing_instances_indices[i];

   set_target_instance(index, new_testing_target_instance);
}


// void add_instance(const Vector<double>&) method

/// This method adds a new instance to the data matrix from a vector of real numbers.
/// The size of that vector must be equal to the number of variables. 
/// Note that resizing is here necessary and therefore computationally expensive. 
/// All instances are also set for training. 
/// @param instance Input and target values of the instance to be added. 

void InputTargetDataSet::add_instance(const Vector<double>& instance)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = instance.get_size();
   int variables_number = get_variables_number();

   if(size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void add_instance(const Vector<double>&) method." << std::endl
                << "Size of instance must be equal to number of variables." << std::endl;

      exit(1);   
   }

   #endif

   data.add_row(instance);

   set_training();
}


// void subtract_instance(int) method

/// This method substract the input-target instance with a given index from the input-target data set.
/// All instances are also set for training. 
/// Note that resizing is here necessary and therefore computationally expensive. 
/// @param instance_index Index of instance to be removed. 

void InputTargetDataSet::subtract_instance(int instance_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int instances_number = get_instances_number();

   if(instance_index < 0)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void subtract_instance(int) method." << std::endl
                << "Index of instance must be equal or greater than zero." << std::endl;

      exit(1);   
   }
   else if(instance_index >= instances_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void subtract_instance(int) method." << std::endl
                << "Index of instance must be less than number of instances." << std::endl;

      exit(1);   
   }

   #endif

   data.subtract_row(instance_index);

   set_training();
}


// Vector< Vector<double> > calculate_data_statistics(void) method

/// This method returns a vector of vectors containing some basic statistics of all the variables in the data set. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Mean.
/// <li> Standard deviation.
/// <li> Minimum.
/// <li> Maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_data_statistics(void)
{
   Vector< Vector<double> > data_mean_standard_deviation = data.calculate_mean_standard_deviation();
   Vector< Vector<double> > data_minimum_maximum = data.calculate_minimum_maximum();

   Vector< Vector<double> > statistics(4);

   statistics[0] = data_mean_standard_deviation[0];
   statistics[1] = data_mean_standard_deviation[1];
   statistics[2] = data_minimum_maximum[0];
   statistics[3] = data_minimum_maximum[1];

   return(statistics);
}


// Vector< Vector<double> > calculate_training_instances_statistics(void) method

/// This method returns a vector of vectors containing some basic statistics of all variables on the training instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Training data mean.
/// <li> Training data standard deviation.
/// <li> Training data minimum.
/// <li> Training data maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_training_instances_statistics(void)
{
   int variables_number = get_variables_number();
   Vector<int> variables_indices(variables_number);
   variables_indices.initialize_sequential();

   Vector< Vector<double> > mean_standard_deviation = data.calculate_mean_standard_deviation(training_instances_indices, variables_indices);

   Vector< Vector<double> > minimum_maximum = data.calculate_minimum_maximum(training_instances_indices, variables_indices);

   Vector< Vector<double> > statistics(4);

   statistics[0] = mean_standard_deviation[0];
   statistics[1] = mean_standard_deviation[1];
   statistics[2] = minimum_maximum[0];
   statistics[3] = minimum_maximum[1];

   return(statistics);
}


// Vector< Vector<double> > calculate_validation_instances_statistics(void) method

/// This method returns a vector of vectors containing some basic statistics of all variables on the validation instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Validation data mean.
/// <li> Validation data standard deviation.
/// <li> Validation data minimum.
/// <li> Validation data maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_validation_instances_statistics(void)
{
   int variables_number = get_variables_number();
   Vector<int> variables_indices(variables_number);
   variables_indices.initialize_sequential();

   Vector< Vector<double> > mean_standard_deviation = data.calculate_mean_standard_deviation(validation_instances_indices, variables_indices);

   Vector< Vector<double> > minimum_maximum = data.calculate_minimum_maximum(validation_instances_indices, variables_indices);

   Vector< Vector<double> > statistics(4);

   statistics[0] = mean_standard_deviation[0];
   statistics[1] = mean_standard_deviation[1];
   statistics[2] = minimum_maximum[0];
   statistics[3] = minimum_maximum[1];

   return(statistics);
}


// Vector< Vector<double> > calculate_testing_instances_statistics(void) method

/// This method returns a vector of vectors containing some basic statistics of all variables on the testing instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Testing data mean.
/// <li> Testing data standard deviation.
/// <li> Testing data minimum.
/// <li> Testing data maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_testing_instances_statistics(void)
{
   int variables_number = get_variables_number();
   Vector<int> variables_indices(variables_number);
   variables_indices.initialize_sequential();

   Vector< Vector<double> > mean_standard_deviation = data.calculate_mean_standard_deviation(testing_instances_indices, variables_indices);

   Vector< Vector<double> > minimum_maximum = data.calculate_minimum_maximum(testing_instances_indices, variables_indices);

   Vector< Vector<double> > statistics(4);

   statistics[0] = mean_standard_deviation[0];
   statistics[1] = mean_standard_deviation[1];
   statistics[2] = minimum_maximum[0];
   statistics[3] = minimum_maximum[1];

   return(statistics);
}


// Vector< Vector<double> > calculate_instances_statistics(void) method

/// This method returns a vector of vectors containing some basic statistics of all variables on all data, 
/// training, validation and testing instances. 
/// The size of this vector is twelve. The subvectors are:
/// <ul>
/// <li> Data mean.
/// <li> Data standard deviation.
/// <li> Data minimum.
/// <li> Data maximum.
/// <li> Training instances mean.
/// <li> Training instances standard deviation.
/// <li> Training instances minimum.
/// <li> Training instances maximum.
/// <li> Validation instances mean.
/// <li> Validation instances standard deviation.
/// <li> Validation instances minimum.
/// <li> Validation instances maximum.
/// <li> Testing instances mean.
/// <li> Testing instances standard deviation.
/// <li> Testing instances minimum.
/// <li> Testing instances maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_instances_statistics(void)
{
   Vector< Vector<double> > data_statistics = calculate_data_statistics();
   Vector< Vector<double> > training_instances_statistics = calculate_training_instances_statistics();
   Vector< Vector<double> > validation_instances_statistics = calculate_validation_instances_statistics();
   Vector< Vector<double> > testing_instances_statistics = calculate_testing_instances_statistics();

   return(data_statistics.assemble(training_instances_statistics).assemble(validation_instances_statistics).assemble(testing_instances_statistics));
}


// Vector< Vector<double> > calculate_input_variables_statistics(void) method

/// This method returns a vector of vectors with some basic statistics of the input variables on all instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Input variables mean.
/// <li> Input variables standard deviation.
/// <li> Input variables minimum.
/// <li> Input variables maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_input_variables_statistics(void)
{
   Vector< Vector<double> > mean_standard_deviation = data.calculate_mean_standard_deviation(input_variables_indices);
   Vector< Vector<double> > minimum_maximum = data.calculate_minimum_maximum(input_variables_indices);

   Vector< Vector<double> > statistics(4);

   statistics[0] = mean_standard_deviation[0];
   statistics[1] = mean_standard_deviation[1];
   statistics[2] = minimum_maximum[0];
   statistics[3] = minimum_maximum[1];

   return(statistics);
}


// Vector< Vector<double> > calculate_target_variables_statistics(void) method

/// This method returns a vector of vectors with some basic statistics of the target variables on all instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Target variables mean.
/// <li> Target variables standard deviation.
/// <li> Target variables minimum.
/// <li> Target variables maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_target_variables_statistics(void)
{
   Vector< Vector<double> > mean_standard_deviation = data.calculate_mean_standard_deviation(target_variables_indices);
   Vector< Vector<double> > minimum_maximum = data.calculate_minimum_maximum(target_variables_indices);

   Vector< Vector<double> > statistics(4);

   statistics[0] = mean_standard_deviation[0];
   statistics[1] = mean_standard_deviation[1];
   statistics[2] = minimum_maximum[0];
   statistics[3] = minimum_maximum[1];

   return(statistics);
}



// Vector< Vector<double> > calculate_variables_statistics(void) method

/// This method returns a vector of vectors with some basic statistics of the input and target variables on all instances. 
/// The size of this vector is eight. The subvectors are:
/// <ul>
/// <li> Input variables mean.
/// <li> Input variables standard deviation.
/// <li> Input variables minimum.
/// <li> Input variables maximum.
/// <li> Target variables mean.
/// <li> Target variables standard deviation.
/// <li> Target variables minimum.
/// <li> Target variables maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::calculate_variables_statistics(void)
{
   Vector< Vector<double> > statistics(8);
   
   // Input

   Vector< Vector<double> > input_variables_mean_standard_deviation = data.calculate_mean_standard_deviation(input_variables_indices);
   Vector< Vector<double> > input_variables_minimum_maximum = data.calculate_minimum_maximum(input_variables_indices);

   // Target

   Vector< Vector<double> > target_variables_mean_standard_deviation = data.calculate_mean_standard_deviation(target_variables_indices);
   Vector< Vector<double> > target_variables_minimum_maximum = data.calculate_minimum_maximum(target_variables_indices);
   
   statistics[0] = input_variables_mean_standard_deviation[0];
   statistics[1] = input_variables_mean_standard_deviation[1];
   statistics[2] = input_variables_minimum_maximum[0];
   statistics[3] = input_variables_minimum_maximum[1];
   statistics[4] = target_variables_mean_standard_deviation[0];
   statistics[5] = target_variables_mean_standard_deviation[1];
   statistics[6] = target_variables_minimum_maximum[0];
   statistics[7] = target_variables_minimum_maximum[1];

   return(statistics);
}


// Vector<double> calculate_training_target_data_mean(void) method

/// This method returns the mean values of the target variables on the training instances. 

Vector<double> InputTargetDataSet::calculate_training_target_data_mean(void)
{
   Vector< Vector<double> > training_target_data_mean_standard_deviation = data.calculate_mean_standard_deviation(training_instances_indices, target_variables_indices);

   return(training_target_data_mean_standard_deviation[0]);
}


// Vector<double> calculate_validation_target_data_mean(void) method

/// This method returns the mean values of the target variables on the validation instances. 

Vector<double> InputTargetDataSet::calculate_validation_target_data_mean(void)
{
   Vector< Vector<double> > validation_target_data_mean_standard_deviation = data.calculate_mean_standard_deviation(validation_instances_indices, target_variables_indices);

   return(validation_target_data_mean_standard_deviation[0]);
}


// void scale_data_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method scales the data matrix with given mean and standard deviation values. 
/// It updates the data matrix.
///
/// @param variables_mean Mean of variables.
/// @param variables_standard_deviation Standard deviation of variables.

void InputTargetDataSet::scale_data_mean_standard_deviation(const Vector<double>& variables_mean, const Vector<double>& variables_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   int variables_mean_size = variables_mean.get_size();
   int variables_standard_deviation_size = variables_standard_deviation.get_size();

   if(variables_mean_size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_data_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of variables mean must be equal to number of variables." << std::endl;

      exit(1);   
   }

   if(variables_standard_deviation_size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_data_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of variables standard deviation must be equal to number of variables." << std::endl;

      exit(1);   
   }

   #endif

   data.scale_mean_standard_deviation(variables_mean, variables_standard_deviation);
}


// void scale_data_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method scales the data matrix with given minimum and maximum values. 
/// It updates the data matrix.
///
/// @param variables_minimum Minimum of variables.
/// @param variables_maximum Maximum of variables.

void InputTargetDataSet::scale_data_minimum_maximum(const Vector<double>& variables_minimum, const Vector<double>& variables_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int variables_number = get_variables_number();

   int variables_minimum_size = variables_minimum.get_size();
   int variables_maximum_size = variables_maximum.get_size();

   if(variables_minimum_size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_data_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of variables minimum must be equal to number of variables." << std::endl;

      exit(1);   
   }

   if(variables_maximum_size != variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_data_minimumn_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of variables maximum must be equal to number of variables." << std::endl;

      exit(1);   
   }

   #endif

   data.scale_minimum_maximum(variables_minimum, variables_maximum);
}


// void scale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method scales the input variables with given mean and standard deviation values.
/// It updates the input variables of the data matrix.
///
/// @param input_variables_mean Mean values for the input variables to be used for scaling.
/// @param input_variables_standard_deviation Standard deviation values for the input variables to be used for scaling.

void InputTargetDataSet::scale_input_variables_mean_standard_deviation(const Vector<double>& input_variables_mean,  
const Vector<double>& input_variables_standard_deviation)
{
   int input_variables_number = get_input_variables_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int input_variables_mean_size = input_variables_mean.get_size();
   int input_variables_standard_deviation_size = input_variables_standard_deviation.get_size();

   if(input_variables_mean_size != input_variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of input variables mean must be equal to number of input variables." << std::endl;

      exit(1);   
   }

   if(input_variables_standard_deviation_size != input_variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of input variables standard deviation must be equal to number of input variables." << std::endl;

      exit(1);   
   }

   #endif

   int instances_number = get_instances_number();

   int variable_index;

   // Rescale input data

   for(int j = 0; j < input_variables_number; j++)
   {
      variable_index = input_variables_indices[j];

      if(input_variables_standard_deviation[j] < 1e-99)
      {
         if(display)
         {                                          
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void scale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl
                      << "Standard deviation of input variable " << j << " is zero." << std::endl
                      << "Those inputs won't be scaled." << std::endl;
         }

         // Do nothing
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][variable_index] = (data[i][variable_index] - input_variables_mean[j])/input_variables_standard_deviation[j];
         }
      }
   }
}


// Vector< Vector<double> > scale_input_variables_mean_standard_deviation(void) method

/// This method scales the input variables with the calculated mean and standard deviation values from the data matrix.
/// It updates the input variables of the data matrix.
/// It also returns a vector of vectors with the basic statistics of the input and target variables. 
/// <ul>
/// <li> Input data mean.
/// <li> Input data standard deviation.
/// <li> Input data minimum.
/// <li> Input data maximum.
/// <li> Target data mean.
/// <li> Target data standard deviation.
/// <li> Target data minimum.
/// <li> Target data maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::scale_input_variables_mean_standard_deviation(void)
{
   Vector< Vector<double> > variables_statistics = calculate_variables_statistics();

   scale_input_variables_mean_standard_deviation(variables_statistics[0], variables_statistics[1]);

   return(variables_statistics);
}


// void scale_input_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method scales the input variables with given minimum and maximum values.
/// It updates the input variables of the data matrix.
///
/// @param input_variables_minimum Minimum values for the input variables to be used for scaling.
/// @param input_variables_maximum Maximum values for the input variables to be used for scaling.

void InputTargetDataSet
::scale_input_variables_minimum_maximum(const Vector<double>& input_variables_minimum, const Vector<double>& input_variables_maximum)
{
   // Rescale input data

   int instances_number = get_instances_number();
   int input_variables_number = get_input_variables_number();

   int variable_index;

   for(int j = 0; j < input_variables_number; j++)
   {
      variable_index = input_variables_indices[j];

      if(input_variables_maximum[j] - input_variables_minimum[j] < 1e-99)
      {
         if(display)
         {
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void scale_input_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl
                      << "Minimum and maximum values of input variable " << j << " are equal. " 
                      << "Those inputs won't be scaled." << std::endl;
         }
         
         // Do nothing
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][variable_index] = 2.0*(data[i][variable_index] - input_variables_minimum[j])/(input_variables_maximum[j]-input_variables_minimum[j])-1.0;
         }
      }
   }
}


// Vector< Vector<double> > scale_input_variables_minimum_maximum(void) method

/// This method scales the input variables with the calculated minimum and maximum values from the data matrix.
/// It updates the input variables of the data matrix.
/// It also returns a vector of vectors with the basic statistics of the input and target variables. 
/// <ul>
/// <li> Input data mean.
/// <li> Input data standard deviation.
/// <li> Input data minimum.
/// <li> Input data maximum.
/// <li> Target data mean.
/// <li> Target data standard deviation.
/// <li> Target data minimum.
/// <li> Target data maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::scale_input_variables_minimum_maximum(void)
{
   Vector< Vector<double> > variables_statistics = calculate_variables_statistics();

   scale_input_variables_minimum_maximum(variables_statistics[2], variables_statistics[3]);

   return(variables_statistics);
}


// void scale_target_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&)

/// This method scales the target variables with given mean and standard deviation values.
/// It updates the target variables of the data matrix.
///
/// @param target_variables_mean Mean values for the target variables to be used for scaling.
/// @param target_variables_standard_deviation Standard deviation values for the target variables to be used for scaling.

void InputTargetDataSet::scale_target_variables_mean_standard_deviation(const Vector<double>& 
target_variables_mean, const Vector<double>& target_variables_standard_deviation)
{
   int target_variables_number = get_target_variables_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int target_variables_mean_size = target_variables_mean.get_size();
   int target_variables_standard_deviation_size = target_variables_standard_deviation.get_size();

   if(target_variables_mean_size != target_variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_target_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of target variables mean must be equal to number of target variables." << std::endl;

      exit(1);   
   }

   if(target_variables_standard_deviation_size != target_variables_number)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_target_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of target variables standard deviation must be equal to number of target variables." << std::endl;

      exit(1);   
   }

   #endif

   int instances_number = get_instances_number();

   int variable_index;

   // Rescale target data

   for(int j = 0; j < target_variables_number; j++)
   {
      variable_index = target_variables_indices[j];

      if(target_variables_standard_deviation[j] < 1e-99)
      {
         if(display)
         {
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void scale_target_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl   
                      << "Standard deviation of target variable " <<  j << " is zero." << std::endl
                      << "Those targets won't be scaled." << std::endl;
         }
         
         // Do nothing
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][variable_index] = (data[i][variable_index] - target_variables_mean[j])/target_variables_standard_deviation[j];
         }
      }
   }
}


// Vector< Vector<double> > scale_target_variables_mean_standard_deviation(void) method

/// This method scales the target variables with the calculated mean and standard deviation values from the data matrix.
/// It updates the target variables of the data matrix.
/// It also returns a vector of vectors with the basic statistics of the input and target variables. 
/// <ul>
/// <li> Input data mean.
/// <li> Input data standard deviation.
/// <li> Input data minimum.
/// <li> Input data maximum.
/// <li> Target data mean.
/// <li> Target data standard deviation.
/// <li> Target data minimum.
/// <li> Target data maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::scale_target_variables_mean_standard_deviation(void)
{
   Vector< Vector<double> > variables_statistics = calculate_variables_statistics();

   scale_target_variables_mean_standard_deviation(variables_statistics[4], variables_statistics[5]);

   return(variables_statistics);
}


// void scale_target_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method scales the target variables with given minimum and maximum values.
/// It updates the target variables of the data matrix.
///
/// @param target_variables_minimum Minimum values for the target variables to be used for scaling.
/// @param target_variables_maximum Maximum values for the target variables to be used for scaling.

void InputTargetDataSet::scale_target_variables_minimum_maximum(const Vector<double>& target_variables_minimum,
const Vector<double>& target_variables_maximum)
{
   int instances_number = get_instances_number();
   int target_variables_number = get_target_variables_number();

   int variable_index;

   // Rescale target data

   for(int j = 0; j < target_variables_number; j++)
   {
	   variable_index = target_variables_indices[j];

      if(target_variables_maximum[j] - target_variables_minimum[j] < 1e-99)
      {
         if(display)
         {
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void scale_target_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl   
                      << "Minimum and maximum values of target variable " << j << " are equal. "
                      << "Those targets won't be scaled." << std::endl;
         }
         
         // Do nothing 
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][variable_index] = 2.0*(data[i][variable_index] - target_variables_minimum[j])/(target_variables_maximum[j]-target_variables_minimum[j]) - 1.0;
         }
      }
   }
}


// Vector< Vector<double> > scale_target_variables_minimum_maximum(void) method

/// This method scales the target variables with the calculated minimum and maximum values from the data matrix.
/// It updates the target variables of the data matrix.
/// It also returns a vector of vectors with the basic statistics of the input and target variables. 
/// <ul>
/// <li> Input data mean.
/// <li> Input data standard deviation.
/// <li> Input data minimum.
/// <li> Input data maximum.
/// <li> Target data mean.
/// <li> Target data standard deviation.
/// <li> Target data minimum.
/// <li> Target data maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::scale_target_variables_minimum_maximum(void)
{
   Vector< Vector<double> > variables_statistics = calculate_variables_statistics();

   scale_target_variables_minimum_maximum(variables_statistics[6], variables_statistics[7]);

   return(variables_statistics);
}


// void scale_variables_mean_standard_deviation(const Vector< Vector<double> >) method

/// This method scales the input and the target variables with given mean and standard deviation values.
/// Please note that it takes as argument a vector of vectors of all basic statistics, with size eight.  
/// It updates the input and the target variables of the data matrix.
///
/// @param variables_statistics Statistics for the input and target variables to be used for scaling.

void InputTargetDataSet::scale_variables_mean_standard_deviation(const Vector< Vector<double> > variables_statistics)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = variables_statistics.get_size();

   if(size != 8)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." << std::endl 
                << "Size of input target variables statistics must be 8." << std::endl;

      exit(1);   
   }

   int input_variables_number = get_input_variables_number();

   for(int i = 0;  i < 4; i++)
   {
      size = variables_statistics[i].get_size();

      if(size != input_variables_number)
      {
         std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                   << "void scale_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." << std::endl 
                   << "Size of element " << i << " must be equal to number of input variables." << std::endl;

         exit(1);   
     }
   }

   int target_variables_number = get_target_variables_number();

   for(int i = 4;  i < 8; i++)
   {
      size = variables_statistics[i].get_size();

      if(size != target_variables_number)
      {
         std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                   << "void scale_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." << std::endl 
                   << "Size of element " << i << " must be equal to number of target variables." << std::endl;

         exit(1);   
     } 
   }

   #endif

   scale_input_variables_mean_standard_deviation(variables_statistics[0], variables_statistics[1]);
   scale_target_variables_mean_standard_deviation(variables_statistics[4], variables_statistics[5]);
}


// Vector< Vector<double> > scale_variables_mean_standard_deviation(void) method

/// This method scales the input and the target variables with the mean and standard deviation values calculated from 
/// the data matrix. 
/// It updates the input and target variables of the data.
/// It also returns the vector of vectors containing the computed statistics of the input-target data set:
/// <ul>
/// <li> Input variables mean.
/// <li> Input variables standard deviation.
/// <li> Input variables minimum.
/// <li> Input variables maximum.
/// <li> Target variables mean.
/// <li> Target variables standard deviation.
/// <li> Target variables minimum.
/// <li> Target variables maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::scale_variables_mean_standard_deviation(void)
{
   Vector< Vector<double> > variables_statistics = calculate_variables_statistics();

   scale_variables_mean_standard_deviation(variables_statistics);

   return(variables_statistics);
}


// void scale_variables_minimum_maximum(const Vector< Vector<double> >&) method

/// This method scales the input and the target variables with given minimum and maximum values.
/// Please note that it takes as argument a vector of vectors of all basic statistics, with size eight.  
/// It updates the input and the target variables of the data matrix.
///
/// @param variables_statistics Statistics for the input target variables to be used for scaling.

void InputTargetDataSet::scale_variables_minimum_maximum(const Vector< Vector<double> > variables_statistics)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = variables_statistics.get_size();

   if(size != 8)
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void scale_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl 
                << "Size of input target variables statistics must be 8." << std::endl;

      exit(1);   
   }

   int input_variables_number = get_input_variables_number();

   for(int i = 0;  i < 4; i++)
   {
      size = variables_statistics[i].get_size();

      if(size != input_variables_number)
      {
         std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                   << "void scale_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl 
                   << "Size of element " << i << " must be equal to number of input variables." << std::endl;

         exit(1);   
     }
   }

   int target_variables_number = get_target_variables_number();

   for(int i = 4;  i < 8; i++)
   {
      size = variables_statistics[i].get_size();

      if(size != target_variables_number)
      {
         std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                   << "void scale_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl 
                   << "Size of element " << i << " must be equal to number of target variables." << std::endl;

         exit(1);   
     } 
   }

   #endif

   scale_input_variables_minimum_maximum(variables_statistics[2], variables_statistics[3]);
   scale_target_variables_minimum_maximum(variables_statistics[6], variables_statistics[7]);
}


// Vector< Vector<double> > scale_variables_minimum_maximum(void) method

/// This method scales the input and the target variables with the minumum and maximum values calculated from 
/// the data matrix. 
/// It updates the input and target variables of the data.
/// It also returns the vector of vectors containing the computed statistics of the input-target data set:
/// <ul>
/// <li> Input variables mean.
/// <li> Input variables standard deviation.
/// <li> Input variables minimum.
/// <li> Input variables maximum.
/// <li> Target variables mean.
/// <li> Target variables standard deviation.
/// <li> Target variables minimum.
/// <li> Target variables maximum.
/// </ul> 

Vector< Vector<double> > InputTargetDataSet::scale_variables_minimum_maximum(void)
{
   Vector< Vector<double> > variables_statistics = calculate_variables_statistics();

   scale_variables_minimum_maximum(variables_statistics);

   return(variables_statistics);
}


// void unscale_data_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method unscales the data matrix with given mean and standard deviation values. 
/// It updates the data matrix.
///
/// @param mean Mean of variables.


/// @param standard_deviation Standard deviation of variables.

void InputTargetDataSet::unscale_data_mean_standard_deviation(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   data.unscale_mean_standard_deviation(mean, standard_deviation);
}


// void unscale_data_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method unscales the data matrix with given minimum and maximum values. 
/// It updates the data matrix.
///
/// @param minimum Minimum of variables.
/// @param maximum Maximum of variables.

void InputTargetDataSet::unscale_data_minimum_maximum(const Vector<double>& minimum, const Vector<double>& maximum)
{
   data.unscale_minimum_maximum(minimum, maximum);
}


// void unscale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method unscales the input variables with given mean and standard deviation values.
/// It updates the input variables of the data matrix.
///
/// @param input_variables_mean Mean values for the input variables to be used for unscaling.
/// @param input_variables_standard_deviation Standard deviation values for the input variables to be used for unscaling.

void InputTargetDataSet::unscale_input_variables_mean_standard_deviation(const Vector<double>& input_variables_mean,
const Vector<double>& input_variables_standard_deviation)
{
   int instances_number = get_instances_number();
   int input_variables_number = get_input_variables_number();

   // Postprocess input data

   for(int j = 0; j < input_variables_number; j++)
   {
      if(input_variables_standard_deviation[j] < 1e-99)
      {
         if(display)
         {                                          
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void unscale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl
                      << "Standard deviation of input variable " << j << " is zero." << std::endl
                      << "Those inputs won't be scaled." << std::endl;
         }

         // Do nothing
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][j] = data[i][j]*input_variables_standard_deviation[j] + input_variables_mean[j];
         }
      }
   }
}


// void unscale_input_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method unscales the input variables with given minimum and maximum values.
/// It updates the input variables of the data matrix.
///
/// @param input_variables_minimum Minimum values for the input variables to be used for unscaling.
/// @param input_variables_maximum Maximum values for the input variables to be used for unscaling.

void InputTargetDataSet::unscale_input_variables_minimum_maximum(const Vector<double>& input_variables_minimum, const Vector<double>& input_variables_maximum)
{
   int instances_number = get_instances_number();
   int input_variables_number = get_input_variables_number();

   // Postprocess input data

   for(int j = 0; j < input_variables_number; j++)
   {
      if(input_variables_maximum[j] - input_variables_minimum[j] < 1e-99)
      {
         if(display)
         {
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void unscale_input_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl
                      << "Minimum and maximum values of input variable " << j << " are equal." << std::endl
                      << "Those inputs won't be unscaled." << std::endl;
         }

         // Do nothing
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][j] = 0.5*(data[i][j] + 1.0)*(input_variables_maximum[j]-input_variables_minimum[j]) 
            + input_variables_minimum[j]; 
         }
      }
   }
}


// void unscale_target_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method unscales the target variables with given mean and standard deviation values.
/// It updates the target variables of the data matrix.
///
/// @param target_variables_mean Mean values for the target variables to be used for unscaling.
/// @param target_variables_standard_deviation Standard deviation values for the target variables to be used for unscaling.

void InputTargetDataSet::unscale_target_variables_mean_standard_deviation(const Vector<double>& target_variables_mean, 
const Vector<double>& target_variables_standard_deviation)
{
   int instances_number = get_instances_number();
   int target_variables_number = get_target_variables_number();

   // Rescale target data

   for(int j = 0; j < target_variables_number; j++)
   {
      if(target_variables_standard_deviation[j] < 1e-99)
      {
         if(display)
         {
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void unscale_target_variables_mean_standard_deviation(const Vector<double>&) method." << std::endl   
                      << "Standard deviation of target variable " <<  j << " is zero." << std::endl
                      << "Those targets won't be scaled." << std::endl;
         }
         
        // Do nothing
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][j] = data[i][j]*target_variables_standard_deviation[j] + target_variables_mean[j];
         }
      }
   }
}


// void unscale_target_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method unscales the target variables with given minimum and maximum values.
/// It updates the target variables of the data matrix.
///
/// @param target_variables_minimum Minimum values for the target variables to be used for unscaling.
/// @param target_variables_maximum Maximum values for the target variables to be used for unscaling.

void InputTargetDataSet::unscale_target_variables_minimum_maximum(const Vector<double>& target_variables_minimum,
const Vector<double>& target_variables_maximum)
{
   int instances_number = get_instances_number();
   int target_variables_number = get_target_variables_number();

   // Postprocess target data

   for(int j = 0; j < target_variables_number; j++)
   {
      if(target_variables_maximum[j] - target_variables_minimum[j] < 1e-99)
      {
         if(display)
         {
            std::cout << "Flood Warning: InputTargetDataSet class." << std::endl
                      << "void unscale_target_variables_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl   
                      << "Minimum and maximum values of target variable " << j << " are equal." << std::endl
                      << "Those targets won't be unscaled." << std::endl;
         }
         
         // Do nothing
      }
      else
      {
         for(int i = 0; i < instances_number; i++)
         {
            data[i][j] = 0.5*(data[i][j] + 1.0)*(target_variables_maximum[j]-target_variables_minimum[j]) 
            + target_variables_minimum[j]; 
         }
      }
   }
}


// void unscale_variables_mean_standard_deviation(const Vector< Vector<double> >&) method 

/// This method unscales the input and the target variables with given mean and standard deviation values.
/// Please note that it takes as argument a vector of vectors of all basic statistics, with size eight.  
/// It updates the input and the target variables of the data matrix.
///
/// @param variables_statistics Statistics for the input and target variables to be used for unscaling.

void InputTargetDataSet::unscale_variables_mean_standard_deviation(const Vector< Vector<double> >& variables_statistics)
{
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int size = variables_statistics.get_size();

   if(size != 8)
   {
      std::cerr << "Flood Warning: InputTargetDataSet class." << std::endl 
                << "void unscale_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." << std::endl
                << "Size of statistics must be 8." << std::endl;
   }     

   for(int i = 0; i < 8; i++)
   {
      size = variables_statistics[i].get_size();

      if(size != 8)
      {
         std::cerr << "Flood Warning: InputTargetDataSet class." << std::endl 
                   << "void unscale_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." << std::endl
                   << "Size of statistics element " << i << " must be equal to number of variables." << std::endl;
      }     
   }

   #endif

   unscale_input_variables_mean_standard_deviation(variables_statistics[0], variables_statistics[1]);
   unscale_target_variables_mean_standard_deviation(variables_statistics[4], variables_statistics[5]);
}



// void unscale_variables_minimum_maximum(const Vector< Vector<double> >&) method

/// This method unscales the input and the target variables with given minimum and maximum values.
/// Please note that it takes as argument a vector of vectors of all basic statistics, with size eight.  
/// It updates the input and the target variables of the data matrix.
///
/// @param variables_statistics Statistics for the input and target variables to be used for unscaling.

void InputTargetDataSet::unscale_variables_minimum_maximum(const Vector< Vector<double> >& variables_statistics)
{
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int size = variables_statistics.get_size();

   if(size != 8)
   {
      std::cerr << "Flood Warning: InputTargetDataSet class." << std::endl 
                << "void unscale_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                << "Size of statistics must be 8." << std::endl;
   }     

   #endif

   unscale_input_variables_minimum_maximum(variables_statistics[2], variables_statistics[3]);
   unscale_target_variables_minimum_maximum(variables_statistics[6], variables_statistics[7]);
}


// void initialize_data(double value) method

/// This methods initializes the data matrix with a given value. 
/// @param new_value Initialization value. 

void InputTargetDataSet::initialize_data(double new_value)
{
   data.initialize(new_value);
}


// std::string to_XML(bool) method

/// This method returns a string representation of the input-target data set object:
/// <ul>
/// <li> Instances number.
/// <li> Training instances number.
/// <li> Training instances indices.
/// <li> Validation instances number.
/// <li> Validation instances indices.
/// <li> Testing instances number.
/// <li> Testing instances indices.
/// <li> Input variables number.
/// <li> Input variables indices.
/// <li> Target variables number.
/// <li> Target variables indices.
/// <li> Input variables name. 
/// <li> Target variables name.
/// <li> Input variables description. 
/// <li> Target variables description.
/// <li> Display.
/// <li> Data.
/// </ul> 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::to_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet'>" << std::endl;
   }

   // Write number of instances and number of input and target variables

   int instances_number = get_instances_number();
   int variables_number = get_variables_number();
   
   buffer << "<InstancesNumber>" << std::endl
          << instances_number << std::endl
		  << "</InstancesNumber>" << std::endl;

   buffer << "<VariablesNumber>" << std::endl
          << variables_number << std::endl
          << "</VariablesNumber>" << std::endl;

   // Write training instances

   int training_instances_number = get_training_instances_number();

   buffer << "<TrainingInstancesNumber>" << std::endl
          << training_instances_number << std::endl
          << "</TrainingInstancesNumber>" << std::endl;

   buffer << "<TrainingInstancesIndices>" << std::endl
          << training_instances_indices << std::endl
          << "</TrainingInstancesIndices>" << std::endl;
		  
   // Write validation instances

   int validation_instances_number = get_validation_instances_number();

   buffer << "<ValidationInstancesNumber>" << std::endl
          << validation_instances_number << std::endl
          << "</ValidationInstancesNumber>" << std::endl;

   buffer << "<ValidationInstancesIndices>" << std::endl
          << validation_instances_indices << std::endl
          << "</ValidationInstancesIndices>" << std::endl;
   
   // Write testing instances

   int testing_instances_number = get_testing_instances_number();

   buffer << "<TestingInstancesNumber>" << std::endl
          << testing_instances_number << std::endl
		  << "</TestingInstancesNumber>" << std::endl;

   buffer << "<TestingInstancesIndices>" << std::endl
          << testing_instances_indices << std::endl   
          << "</TestingInstancesIndices>" << std::endl;

   // Write input variables indices

   int input_variables_number = get_input_variables_number();

   buffer << "<InputVariablesNumber>" << std::endl
          << input_variables_number << std::endl
          << "</InputVariablesNumber>" << std::endl;

   buffer << "<InputVariablesIndices>" << std::endl
          << input_variables_indices << std::endl   
          << "</InputVariablesIndices>" << std::endl;

   // Write target variables indices

   int target_variables_number = get_target_variables_number();

   buffer << "<TargetVariablesNumber>" << std::endl
          << target_variables_number << std::endl
          << "</TargetVariablesNumber>" << std::endl;

   buffer << "<TargetVariablesIndices>" << std::endl
          << target_variables_indices << std::endl   
          << "</TargetVariablesIndices>" << std::endl;

   // Write name of variables

   if(variables_name.get_size() != 0)
   {
      buffer << "<VariablesName>" << std::endl;

      for(int i = 0; i < variables_number; i++)
	  {
	     buffer << "<Name>" << std::endl
		        << variables_name[i] << std::endl
				<< "</Name>" << std::endl;         		    		
	  }

      buffer << "</VariablesName>" << std::endl;
   }

   // Write units of variables

   if(variables_units.get_size() != 0)
   {
      buffer << "<VariablesUnits>" << std::endl;

      for(int i = 0; i < variables_number; i++)
	  {
	     buffer << "<Units>" << std::endl
		        << variables_units[i] << std::endl
				<< "</Units>" << std::endl;         		    		
	  }
		  
      buffer << "</VariablesUnits>" << std::endl;
   }

   // Write description of variables

   if(variables_description.get_size() != 0)
   {
      buffer << "<VariablesDescription>" << std::endl;

      for(int i = 0; i < variables_number; i++)
	  {
	     buffer << "<Description>" << std::endl
		        << variables_description[i] << std::endl
				<< "</Description>" << std::endl;         		    		
	  }

	  buffer << "</VariablesDescription>" << std::endl;
   }

   // Write display

   buffer << "<Display>" << std::endl
          << display << std::endl
          << "</Display>" << std::endl;

   // Write input-target data 

   buffer << "<Data>" << std::endl
          << data
          << "</Data>" << std::endl;

   return(buffer.str());    
}


// void print(void) method

/// This method prints to the screen in a XML-type format the members of the input-target data set object. 

void InputTargetDataSet::print(void)
{
   if(display)
   {
      std::cout << to_XML(true) << std::endl;
   }
}


// void save(const char*) method

/// This method saves the members of an input-target data set object to a XML-type file in an XML-type format.
/// @param filename Name of input-target data set XML-type file.

void InputTargetDataSet::save(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save(const char*) method." << std::endl
                << "Cannot open input-target data set file."  << std::endl;

      exit(1);
   }
  
   // Write object

   file << to_XML(true);

   // Close file

   file.close();
}


// void load(const char*) method

/// This method loads the members of an input-target data set object from a XML-type file:
/// <ul>
/// <li> Instances number.
/// <li> Training instances number.
/// <li> Training instances indices.
/// <li> Validation instances number.
/// <li> Validation instances indices.
/// <li> Testing instances number.
/// <li> Testing instances indices.
/// <li> Input variables number.
/// <li> Input variables indices.
/// <li> Target variables number.
/// <li> Target variables indices.
/// <li> Input variables name. 
/// <li> Target variables name.
/// <li> Input variables description. 
/// <li> Target variables description.
/// <li> Display.
/// <li> Data.
/// </ul> 
/// Please mind about the file format. This is specified in the User's Guide.
/// @param filename Name of input-target data set XML-type file.

void InputTargetDataSet::load(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open input-target data set file."  << std::endl;

      exit(1);
   }

   set();

   std::string line;
   std::string word;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='InputTargetDataSet'>") 
   {
//      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
//                << "void load(const char*) method." << std::endl
//				    << "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   // Instances number

   file >> word;

   if(word != "<InstancesNumber>") 
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown instances number begin tag: " << line << std::endl;
 
      exit(1);
   }

   int new_instances_number;

   file >> new_instances_number;

   file >> word;

   if(word != "</InstancesNumber>") 
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown instances number end tag: " << word << std::endl;
 
      exit(1);
   }

   // Variables number

   file >> word;

   if(word != "<VariablesNumber>") 
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown variables number begin tag: " << word << std::endl;
 
      exit(1);
   }

   int new_variables_number;

   file >> new_variables_number;

   file >> word;

   if(word != "</VariablesNumber>") 
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown variables number end tag: " << word << std::endl;
 
      exit(1);
   }

   data.set(new_instances_number, new_variables_number);

   while(!file.eof())
   {
      file >> word; 

      if(word == "<TrainingInstancesNumber>") 
      {
         int new_training_instances_number;

         file >> new_training_instances_number;

         file >> word;

         if(word != "</TrainingInstancesNumber>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown training instances number end tag: " << word << std::endl;
 
            exit(1);
          }

          // Training instances indices

         file >> word;

         if(word != "<TrainingInstancesIndices>") 
         {
            std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                      << "void load(const char*) method." << std::endl
    	              << "Unknown training instances indices begin tag: " << word << std::endl;
 
            exit(1);
         }

         Vector<int> new_training_instances_indices(new_training_instances_number);
         file >> new_training_instances_indices;

         file >> word;

         if(word != "</TrainingInstancesIndices>") 
         {
             std::cerr << "Flood Error: Vector template." << std::endl
                       << "void load(const char*) method." << std::endl
	                   << "Unknown training instances number end tag: " << word << std::endl;
 
             exit(1);
         }

         set_training_instances_indices(new_training_instances_indices);
      }

      else if(word == "<ValidationInstancesNumber>") 
      {
         int new_validation_instances_number;

         file >> new_validation_instances_number;

         file >> word;

         if(word != "</ValidationInstancesNumber>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown validation instances number end tag: " << word << std::endl;
 
            exit(1);
         }

         // Validation instances indices

         file >> word;

         if(word != "<ValidationInstancesIndices>") 
         {
            std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown validation instances indices begin tag: " << word << std::endl;
 
            exit(1);
         }

         Vector<int> new_validation_instances_indices(new_validation_instances_number);

		 file >> new_validation_instances_indices;

         file >> word;

         if(word != "</ValidationInstancesIndices>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown validation instances indices end tag: " << word << std::endl;
 
            exit(1);
         }

         set_validation_instances_indices(new_validation_instances_indices);
	  }
      else if(word == "<TestingInstancesNumber>") 
      {
         int new_testing_instances_number;

         file >> new_testing_instances_number;

         file >> word;

         if(word != "</TestingInstancesNumber>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown testing instances number end tag: " << word << std::endl;
 
            exit(1);
         }

         // Testing instances indices

         file >> word;

         if(word != "<TestingInstancesIndices>") 
         {
             std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                       << "void load(const char*) method." << std::endl
	       	           << "Unknown validation instances indices begin tag: " << word << std::endl;
 
            exit(1);
         }

         Vector<int> new_testing_instances_indices(new_testing_instances_number);

         file >> new_testing_instances_indices;

         file >> word;

         if(word != "</TestingInstancesIndices>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown testing instances indices end tag: " << word << std::endl;
 
            exit(1);
         }

         set_testing_instances_indices(new_testing_instances_indices);
	  }

      else if(word == "<InputVariablesNumber>") 
      {
         int new_input_variables_number;

         file >> new_input_variables_number;

         file >> word;

         if(word != "</InputVariablesNumber>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown input variables number end tag: " << word << std::endl;
 
            exit(1);
         }

         // Input variables indices

         file >> word;

         if(word != "<InputVariablesIndices>") 
         {
            std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown input variables indices begin tag: " << word << std::endl;
 
            exit(1);
         }

         Vector<int> new_input_variables_indices(new_input_variables_number);
         file >> new_input_variables_indices;

         file >> word;

         if(word != "</InputVariablesIndices>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown input variables indices end tag: " << word << std::endl;
 
            exit(1);
         }

         set_input_variables_indices(new_input_variables_indices);
	  }
   
      else if(word == "<TargetVariablesNumber>") 
      {
         int new_target_variables_number;

         file >> new_target_variables_number;

         file >> word;

         if(word != "</TargetVariablesNumber>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown target variables number end tag: " << word << std::endl;
 
            exit(1);
         }

         // Target variables indices

         file >> word;

         if(word != "<TargetVariablesIndices>") 
         {
            std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown target variables indices begin tag: " << word << std::endl;
 
            exit(1);
         }

         Vector<int> new_target_variables_indices(new_target_variables_number);

         file >> new_target_variables_indices;

         file >> word;

         if(word != "</TargetVariablesIndices>") 
         {
            std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown target variables indices end tag: " << word << std::endl;
 
            exit(1);
         }

         set_target_variables_indices(new_target_variables_indices);
	  }

      else if(word == "<VariablesName>")
	  {
         int variables_number = get_variables_number();
 
	     for(int i = 0; i < variables_number; i++) 
		 {
		    file >> word;
   
      	    if(word != "<Name>") 
            {
               std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown name begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

			file >> word;
   
    		if(word != "</Name>") 
            {
               std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown name end tag: " << word << std::endl;
 
               exit(1);
            }  

			set_variable_name(i, line);
         }

        file >> word; 
			   
		if(word != "</VariablesName>") 
        {
           std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                     << "void load(const char*) method." << std::endl
            	     << "Unknown input variables name end tag: " << word << std::endl;
 
           exit(1);
        }  
	  }

      else if(word == "<VariablesUnits>")
	  {
         int variables_number = get_variables_number();

	     for(int i = 0; i < variables_number; i++) 
		 {
		    file >> word;
   
      	    if(word != "<Units>") 
            {
               std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown units begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

			file >> word;
   
    		if(word != "</Units>") 
            {
               std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown units end tag: " << word << std::endl;
 
               exit(1);
            }  

			set_variable_units(i, line);
         }

         file >> word; 
			   
         if(word != "</VariablesUnits>") 
         {
            std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                      << "void load(const char*) method." << std::endl
             	      << "Unknown variables units end tag: " << word << std::endl;
 
            exit(1);
         }   
	  }

      else if(word == "<VariablesDescription>")
	  {
         int variables_number = get_variables_number();

	     for(int i = 0; i < variables_number; i++) 
		 {
		    file >> word;
   
      	    if(word != "<Description>") 
            {
               std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown description begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

			file >> word;
   
    		if(word != "</Description>") 
            {
               std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown description end tag: " << word << std::endl;
 
               exit(1);
            }  

			set_variable_description(i, line);
         }

         file >> word; 
			   
		 if(word != "</VariablesDescription>") 
         {
            std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                      << "void load(const char*) method." << std::endl
             	      << "Unknown variables description end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }

      else if(word == "<Display>")
	  {
         file >> display;

         file >> word;

         if(word != "</Display>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown display end tag: " << word << std::endl;
 
            exit(1);
         }       	  
	  }

      else if(word == "<Data>") 
      {
         file >> data;       

         file >> word;

         if(word != "</Data>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown data end tag: " << word << std::endl;
 
            exit(1);
         }
	  }
   }

   int instances_number = get_instances_number();
   int training_instances_number = get_training_instances_number();
   int validation_instances_number = get_validation_instances_number();
   int testing_instances_number = get_testing_instances_number();

   if(instances_number != 0 && training_instances_number == 0 && validation_instances_number == 0 && testing_instances_number == 0)
   {
      set_training();
   }

   int variables_number = get_variables_number();
   int input_variables_number = get_input_variables_number();
   int target_variables_number = get_target_variables_number();

   if(variables_number != 0 && input_variables_number == 0 && target_variables_number == 0)
   {
      set_input();
   }

   file.close(); 
}


// void print_data(void) method

/// This method prints to the sceen the values of the data matrix. 

void InputTargetDataSet::print_data(void)
{
	std::cout << data;
}


// void save_data(const char*) method

/// This method saves to a file the values of the data matrix. 
/// @param filename Name of data file. 

void InputTargetDataSet::save_data(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_data(const char*) method." << std::endl
                << "Cannot open data file."  << std::endl;

      exit(1);
   }
  
   // Write input and target data

   Matrix<double> data = get_data();

   file << data;

   // Close file

   file.close();
}


// void load_data(const char* filename)

/// This method loads from a file the values of the data matrix. 
/// The number of rows must be equal to the number of instances.
/// The number of columns must be equal to the number of variables.

void InputTargetDataSet::load_data(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl
                << "void load_data(const char*) method." << std::endl
                << "Cannot open data file."  << std::endl;

      exit(1);
   }

   std::string word;

   int instances_number = get_instances_number();
   int variables_number = get_variables_number();

   for(int i = 0; i < instances_number; i++) 
   {
      for(int j = 0; j < variables_number; j++)
      {
         file >> data[i][j];
      }
   }
 
   file.close(); 
}


// void split_given_indices(const Vector<double>&, const Vector<double>&, const Vector<double>&) method

/// This method sets new training, validation and testing indices from given vectors. 
/// @param new_training_instances_indices Indices of instances to be used for training. 
/// @param new_validation_instances_indices Indices of instances to be used for validation. 
/// @param new_testing_instances_indices Indices of instances to be used for testing. 

void InputTargetDataSet::split_given_indices
(const Vector<int>& new_training_instances_indices, const Vector<int>& new_validation_instances_indices, const Vector<int>& new_testing_instances_indices)
{
   int new_training_instances_number = new_training_instances_indices.get_size();
   int new_validation_instances_number = new_validation_instances_indices.get_size();
   int new_testing_instances_number = new_testing_instances_indices.get_size();

   int instances_number = get_instances_number();

   int new_instances_number = new_training_instances_number+new_validation_instances_number+new_testing_instances_number;

   if(display && new_instances_number != instances_number)
   {
      std::cout << "Flood Warning: InputTargetDataSet class." << std::endl 
                << "void split_given_indices(const Vector<double>&, const Vector<double>&, const Vector<double>&) method." << std::endl
                << "New number of instances is not equal to number of instances." << std::endl;
   }
     
   training_instances_indices = new_training_instances_indices;
   validation_instances_indices = new_validation_instances_indices;
   testing_instances_indices = new_testing_instances_indices;
}


// void split_random_indices(double, double, double) method

/// This method creates new training, validation and testing indices at random. 
///
/// @param training_instances_ratio Ratio of training instances in the data set.
/// @param validation_instances_ratio Ratio of validation instances in the data set.
/// @param testing_instances_ratio Ratio of testing instances in the data set.

void InputTargetDataSet::split_random_indices
(double training_instances_ratio, double validation_instances_ratio, double testing_instances_ratio)
{
   double total_ratio = training_instances_ratio + validation_instances_ratio + testing_instances_ratio;

   // Get number of instances for training, validation and testing

   int instances_number = get_instances_number();

   int validation_instances_number = (int)(validation_instances_ratio*instances_number/total_ratio);
   int testing_instances_number = (int)(testing_instances_ratio*instances_number/total_ratio);
   int training_instances_number = instances_number - validation_instances_number - testing_instances_number;

   int sum_instances_number = training_instances_number + validation_instances_number + testing_instances_number;

   if(sum_instances_number != instances_number)
   {
      std::cerr << "Flood Warning: InputTargetDataSet class." << std::endl 
                << "void split_random_indices(double, double, double) method." << std::endl
                << "Sum of numbers of training, validation and testing instances is not equal to number of instances." << std::endl;
   
   }

   // Resize training, validation and testing data set objects

   validation_instances_indices.set(validation_instances_number);
   testing_instances_indices.set(testing_instances_number);
   training_instances_indices.set(training_instances_number);

   Vector<int> indices(instances_number);
   indices.initialize_sequential();
   std::random_shuffle(indices.begin(), indices.end());

   // Training indices

   for(int i = 0; i < training_instances_number; i++)
   {
      training_instances_indices[i] = indices[i];
   }

   std::sort(training_instances_indices.begin(), training_instances_indices.end());

   // Validation indices

   for(int i = 0; i < validation_instances_number; i++)           
   {
      validation_instances_indices[i] = indices[training_instances_number+i];   
   }

   std::sort(validation_instances_indices.begin(), validation_instances_indices.end());

   // Testing indices

   for(int i = 0; i < testing_instances_number; i++)           
   {
      testing_instances_indices[i] = indices[training_instances_number+validation_instances_number+i];   
   }

   std::sort(testing_instances_indices.begin(), testing_instances_indices.end());
}


// void split_random_indices(void) method

/// This method creates new training, validation and testing indices at random. 
/// It uses the following default values:
/// <ul>
/// <li> Training instances ratio: 0.8
/// <li> Validation instances ratio: 0.2
/// <li> Testing instances ratio: 0.2
/// </ul>

void InputTargetDataSet::split_random_indices(void)
{
   split_random_indices(0.8, 0.2, 0.2);
}


// std::string get_instances_information_XML(bool) method

/// This method returns a string with XML-type format with information about the training, validation and testing subsets. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::get_instances_information_XML(bool show_declaration)
{
   std::stringstream buffer;

   int instances_number = get_instances_number();

   int training_instances_number = get_training_instances_number();
   int validation_instances_number = get_validation_instances_number();
   int testing_instances_number = get_validation_instances_number();

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet' content=<InstancesInformation>" << std::endl; 
   }

   buffer << "<InstancesInformation>" << std::endl;

   // Write instances number

   buffer << "<InstancesNumber>" << std::endl
	      << instances_number << std::endl
		  << "</InstancesNumber>" << std::endl;

   // Write training instances number

   buffer << "<TrainingInstancesNumber>" << std::endl
	      << training_instances_number << std::endl
		  << "</TrainingInstancesNumber>" << std::endl;

   // Write training instances indices

   if(training_instances_number != 0)
   {
      buffer << "<TrainingInstancesIndices>" << std::endl
		     << training_instances_indices << std::endl
             << "</TrainingInstancesIndices>" << std::endl;
   }

   // Write validation instances number

   buffer << "<ValidationInstancesNumber>" << std::endl
	      << validation_instances_number << std::endl
		  << "</ValidationInstancesNumber>" << std::endl;

   // Write validation instances indices

   if(validation_instances_number != 0)
   {
      buffer << "<ValidationInstancesIndices>" << std::endl
		     << validation_instances_indices << std::endl
             << "</ValidationInstancesIndices>" << std::endl;
   }

   // Write testing instances number

   buffer << "<TestingInstancesNumber>" << std::endl
	      << testing_instances_number << std::endl
		  << "</TestingInstancesNumber>" << std::endl;

   // Write testing instances indices

   if(testing_instances_number != 0)
   {
      buffer << "<TestingInstancesIndices>" << std::endl
		     << testing_instances_indices << std::endl
             << "</TestingInstancesIndices>" << std::endl;
   }

   buffer << "</InstancesInformation>" << std::endl;

   return(buffer.str());
}


// void print_instances_information(void) method

/// This method prints to the sceen in XML-type format the information about the training, validation and testing subsets.

void InputTargetDataSet::print_instances_information(void)
{
   std::cout << get_instances_information_XML(true);
}


// void save_instances_information(const char*) method

/// This method saves to a XML-type file the information about the training, validation and testing subsets.
/// @param filename Name of instances information XML-type file. 

void InputTargetDataSet::save_instances_information(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_variables_information(const char*) method." << std::endl
                << "Cannot open variables information XML-type file."  << std::endl;

      exit(1);
   }
  
   // Write object

   file << get_instances_information_XML(true);

   // Close file

   file.close();   
}



// std::string get_variables_information_XML(bool) method

/// This method returns a XML-type string with information concerned about the variables in the data set. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::get_variables_information_XML(bool show_declaration)
{
   std::stringstream buffer;

   int variables_number = get_variables_number();
   int input_variables_number = get_input_variables_number();
   int target_variables_number = get_target_variables_number();

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet' content='VariablesInformation'>" << std::endl; 
   }

   // Write number of variables

   buffer << "<VariablesNumber>" << std::endl
	      << variables_number << std::endl
	      << "</VariablesNumber>" << std::endl;

   // Write number of input variables

   buffer << "<InputVariablesNumber>" << std::endl
	      << input_variables_number << std::endl
	      << "</InputVariablesNumber>" << std::endl;
   
   // Write indices of input variables

   if(input_variables_number > 0)
   {
      buffer << "<InputVariablesIndices>" << std::endl
	         << input_variables_indices << std::endl
	         << "</InputVariablesIndices>" << std::endl;
   }

   // Write number of target variables

   buffer << "<TargetVariablesNumber>" << std::endl
	      << target_variables_number << std::endl
	      << "</TargetVariablesNumber>" << std::endl;
   
   // Write indices of target variables

   if(target_variables_number > 0)
   {
      buffer << "<TargetVariablesIndices>" << std::endl
	         << target_variables_indices << std::endl
	         << "</TargetVariablesIndices>" << std::endl;
   }

   if(variables_name.get_size() != variables_number)
   {
      buffer << "<VariablesName>" << std::endl;

      for(int i = 0; i < variables_number; i++)
	  {
	     buffer << "<Name>" << std::endl
		        << variables_name[i] << std::endl
				<< "</Name>" << std::endl;         		    		
	  }

	  buffer << "</VariablesName>" << std::endl;
   }   


   if(variables_units.get_size() != variables_number)
   {
      buffer << "<VariablesUnits>" << std::endl;

      for(int i = 0; i < variables_number; i++)
	  {
	     buffer << "<Units>" << std::endl
		        << variables_units[i] << std::endl
				<< "</Units>" << std::endl;         		    		
	  }

      buffer << "</VariablesUnits>" << std::endl;
   }
   

   if(variables_description.get_size() != variables_number)
   {
      buffer << "<Description>" << std::endl;

      for(int i = 0; i < variables_number; i++)
	  {
	     buffer << "<Description>" << std::endl
		        << variables_description[i] << std::endl
				<< "</Description>" << std::endl;         		    		
	  }

      buffer << "</VariablesDescription>" << std::endl;
   }

   return(buffer.str());
}


// void print_variables_information(void) method

/// This method prints to the screen in a XML-type format information concerned about the variables in the data set. 

void InputTargetDataSet::print_variables_information(void)
{
   if(display)
   {
      std::cout << get_variables_information_XML(true);
   }
}


// void save_variables_information(const char*) method

/// This method saves to a XML-type file with information concerned about the variables in the data set. 
/// @param filename Name of variables information XML-type file.

void InputTargetDataSet::save_variables_information(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_variables_information(const char*) method." << std::endl
                << "Cannot open variables information XML-type file."  << std::endl;

      exit(1);
   }
  
   // Write object

   file << get_variables_information_XML(true);

   // Close file

   file.close();   
}


// std::string get_data_statistics_XML(bool) method

/// This method returns a XML-type formated string with the basic statistics of the data matrix. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::get_data_statistics_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration    
   
   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet' class='DataStatistics'>" << std::endl;
   }

   Vector< Vector<double> > statistics = calculate_data_statistics();

   buffer << "<DataMean>" << std::endl
          << statistics[0] << std::endl
          << "</DataMean>" << std::endl
          << "<DataStandardDeviation>" << std::endl
          << statistics[1] << std::endl 
          << "</DataStandardDeviation>" << std::endl
          << "<DataMinimum>" << std::endl 
          << statistics[2] << std::endl
          << "</DataMinimum>" << std::endl 
          << "<DataMaximum>" << std::endl
          << statistics[3] << std::endl
          << "</DataMaximum>" << std::endl;
   
   return(buffer.str());
}


// void print_data_statistics(void) method

/// This method prints to the screen in a XML-type format the basic statistics of the data matrix. 

void InputTargetDataSet::print_data_statistics(void)
{
   if(display)
   {
      std::cout << get_data_statistics_XML(true);
   }
}


// void save_data_statistics(const char*) method

/// This method saves to a XML-type file the basic statistics of the data matrix. 
/// @param filename Name of XML-type statistics file. 

void InputTargetDataSet::save_data_statistics(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_data_statistics(const char*) method." << std::endl
                << "Cannot open statistics XML-type file."  << std::endl;

      exit(1);
   }
  
   // Write object

   file << get_data_statistics_XML(true);

   // Close file

   file.close();
}


// std::string get_training_instances_statistics_XML(bool) method

/// This method returns a XML-type formated string with the basic statistics of the training instances in the data matrix. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::get_training_instances_statistics_XML(bool show_declaration)
{
   std::stringstream buffer;

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet' content='TrainingInstancesStatistics'>" << std::endl;
   }

   Vector< Vector<double> > training_instances_statistics = calculate_training_instances_statistics();

   buffer << "<TrainingInstancesMean>" << std::endl
          << training_instances_statistics[0] << std::endl
          << "</TrainingInstancesMean>" << std::endl
          << "<TrainingInstancesStandardDeviation>" << std::endl
          << training_instances_statistics[1] << std::endl 
          << "</TrainingInstancesStandardDeviation>" << std::endl
          << "<TrainingInstancesMinimum>" << std::endl 
          << training_instances_statistics[2] << std::endl
          << "</TrainingInstancesMinimum>" << std::endl 
          << "<TrainingInstancesMaximum>" << std::endl
          << training_instances_statistics[3] << std::endl
          << "</TrainingInstancesMaximum>" << std::endl;
   
   return(buffer.str());
}


// void print_training_instances_statistics(void) method

/// This method prints to the screen in a XML-type format the basic statistics of the training instances in the data matrix. 

void InputTargetDataSet::print_training_instances_statistics(void)
{
   std::cout << get_training_instances_statistics_XML(true);
}


// void save_training_instances_statistics(const char*) method

/// This method saves to a XML-type file the basic statistics of the training instances in the data matrix. 
/// @param filename Name of XML-type training instances statistics file. 

void InputTargetDataSet::save_training_instances_statistics(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_training_instances_statistics(const char*) method." << std::endl
                << "Cannot open training data statistics XML-type file."  << std::endl;

      exit(1);
   }
  
   file << get_training_instances_statistics_XML(true);

   file.close();
}


// std::string get_validation_instances_statistics_XML(bool) method

/// This method returns a XML-type formated string with the basic statistics of the validation instances in the data matrix. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::get_validation_instances_statistics_XML(bool show_declaration)
{
   std::stringstream buffer;

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet' content='ValidationInstancesStatistics'>" << std::endl;
   }

   Vector< Vector<double> > validation_instances_statistics = calculate_validation_instances_statistics();

   buffer << "<ValidationInstancesMean>" << std::endl
          << validation_instances_statistics[0] << std::endl
          << "</ValidationInstancesMean>" << std::endl
          << "<ValidationInstancesStandardDeviation>" << std::endl
          << validation_instances_statistics[1] << std::endl 
          << "</ValidationInstancesStandardDeviation>" << std::endl
          << "<ValidationInstancesMinimum>" << std::endl 
          << validation_instances_statistics[2] << std::endl
          << "</ValidationInstancesMinimum>" << std::endl 
          << "<ValidationInstancesMaximum>" << std::endl
          << validation_instances_statistics[3] << std::endl
          << "</ValidationInstancesMaximum>" << std::endl;
   
   return(buffer.str());
}


// void print_validation_instances_statistics(void) method

/// This method prints to the screen in a XML-type format the basic statistics of the validation instances in the data matrix. 

void InputTargetDataSet::print_validation_instances_statistics(void)
{
   if(display)
   {
      std::cout << get_validation_instances_statistics_XML(true);
   }
}


// void save_validation_instances_statistics(const char*) method

/// This method saves to a XML-type file the basic statistics of the validation instances in the data matrix. 
/// @param filename Name of XML-type validation instances statistics file. 

void InputTargetDataSet::save_validation_instances_statistics(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_validation_instances_statistics(const char*) method." << std::endl
                << "Cannot open validation data statistics XML-type file."  << std::endl;

      exit(1);
   }
  
   file << get_validation_instances_statistics_XML(true);

   file.close();
}


// std::string get_testing_instances_statistics_XML(bool) method

/// This method returns a XML-type formated string with the basic statistics of the testing instances in the data matrix. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::get_testing_instances_statistics_XML(bool show_declaration)
{
   std::stringstream buffer;

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet' content='TestingInstancesStatistics'>" << std::endl;
   }

   Vector< Vector<double> > testing_instances_statistics = calculate_testing_instances_statistics();

   buffer << "<TestingInstancesMean>" << std::endl
          << testing_instances_statistics[0] << std::endl
          << "</TestingInstancesMean>" << std::endl
          << "<TestingInstancesStandardDeviation>" << std::endl
          << testing_instances_statistics[1] << std::endl 
          << "</TestingInstancesStandardDeviation>" << std::endl
          << "<TestingInstancesMinimum>" << std::endl 
          << testing_instances_statistics[2] << std::endl
          << "</TestingInstancesMinimum>" << std::endl 
          << "<TestingInstancesMaximum>" << std::endl
          << testing_instances_statistics[3] << std::endl
          << "</TestingInstancesMaximum>" << std::endl;
   
   return(buffer.str());
}


// void print_testing_instances_statistics(void) method

/// This method prints to the screen in a XML-type format the basic statistics of the testing instances in the data matrix. 

void InputTargetDataSet::print_testing_instances_statistics(void)
{
   if(display)
   {
      std::cout << get_testing_instances_statistics_XML(true);
   }   
}


// void save_testing_instances_statistics(const char*) method

/// This method saves to a XML-type file the basic statistics of the testing instances in the data matrix. 
/// @param filename Name of XML-type testing instances statistics file. 

void InputTargetDataSet::save_testing_instances_statistics(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_testing_instances_statistics(const char*) method." << std::endl
                << "Cannot open testing data statistics XML-type file."  << std::endl;

      exit(1);
   }
  
   file << get_testing_instances_statistics_XML(true);

   file.close();
}


// std::string get_instances_statistics_XML(bool) method

/// This method returns a XML-type formated string with the basic statistics of the whole data and
/// the training, validation and testing instances in the data matrix. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string InputTargetDataSet::get_instances_statistics_XML(bool show_declaration)
{
   std::stringstream buffer;

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='InputTargetDataSet' content='InstancesStatistics'>" << std::endl;
   }

   buffer << get_data_statistics_XML(false)
          << get_training_instances_statistics_XML(false)
          << get_validation_instances_statistics_XML(false)
          << get_testing_instances_statistics_XML(false);

   return(buffer.str());
}


// void print_instances_statistics(void) method

/// This method prints to the screen in a XML-type format the basic statistics of the whole data and
/// the training, validation and testing instances in the data matrix. 

void InputTargetDataSet::print_instances_statistics(void)
{
   std::cout << get_instances_statistics_XML(true);
}


// void save_instances_statistics(const char*) method

/// This method saves to a XML-type file the basic statistics of the whole data and
/// the training, validation and testing instances in the data matrix. 

void InputTargetDataSet::save_instances_statistics(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: InputTargetDataSet class." << std::endl 
                << "void save_instances_statistics(const char*) method." << std::endl
                << "Cannot open all data statistics XML-type file."  << std::endl;

      exit(1);
   }
  
   file << get_testing_instances_statistics_XML(true);

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
