/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   I N P U T - T A R G E T   D A T A   S E T   C L A S S   H E A D E R                                        */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __INPUTTARGETDATASET_H__
#define __INPUTTARGETDATASET_H__

#include <string>

#include "../Utilities/Vector.h"
#include "../Utilities/Matrix.h"

namespace Flood
{

/// This class represents the concept of input-target data set for data modelling problems, such as function
/// regression, pattern recognition and time series prediction.

class InputTargetDataSet 
{

public:  

   // INSTANCES AND INPUT AND TARGET VARIABLES CONSTRUCTOR

   explicit InputTargetDataSet(int, int, int);

   // INSTANCES AND VARIABLES CONSTRUCTOR

   explicit InputTargetDataSet(int, int);

   // DEFAULT CONSTRUCTOR

   explicit InputTargetDataSet(void);

   // COPY CONSTRUCTOR

   InputTargetDataSet(const InputTargetDataSet&);

   // FILE CONSTRUCTOR

   explicit InputTargetDataSet(const char*);

   // DESTRUCTOR

   virtual ~InputTargetDataSet(void);

   // ASSIGNMENT OPERATOR

   InputTargetDataSet& operator = (const InputTargetDataSet&);

   // METHODS

   // Get methods

   /// This method returns the number of instances in the input-target data set.

   inline int get_instances_number(void)
   {
      return(data.get_rows_number());   
   }

   /// This method returns the number of instances in the data set which will be used for training.

   int get_training_instances_number(void)
   {
      return(training_instances_indices.get_size());
   }

   /// This method returns the number of instances in the data set which will be used for validation.

   int get_validation_instances_number(void)
   {
      return(validation_instances_indices.get_size());
   }

   /// This method returns the number of instances in the data set which will be used for testing.

   int get_testing_instances_number(void)
   {
      return(testing_instances_indices.get_size());
   }

   /// This method returns the total number of variables in the input-target data set.

   inline int get_variables_number(void)
   {
      return(data.get_columns_number());   
   }

   /// This method returns the number of input variables of the input-target data set.

   inline int get_input_variables_number(void)
   {
      return(input_variables_indices.get_size());   
   }

   /// This method returns the number of target variables of the input-target data set.

   inline int get_target_variables_number(void)
   {
      return(target_variables_indices.get_size());   
   }

   // Instances methods

   Vector<int>& get_training_instances_indices(void);
   Vector<int>& get_validation_instances_indices(void);
   Vector<int>& get_testing_instances_indices(void);

   // Variables methods

   Vector<int>& get_input_variables_indices(void);
   Vector<int>& get_target_variables_indices(void); 

   // Information methods

   Vector<std::string>& get_variables_name(void);
   std::string& get_variable_name(int);

   Vector<std::string> get_input_variables_name(void);
   Vector<std::string> get_target_variables_name(void);

   Vector<std::string>& get_variables_units(void);
   std::string& get_variable_units(int);

   Vector<std::string> get_input_variables_units(void);
   Vector<std::string> get_target_variables_units(void);

   Vector<std::string>& get_variables_description(void);
   std::string& get_variable_description(int);

   Vector<std::string> get_input_variables_description(void);
   Vector<std::string> get_target_variables_description(void);

   Vector< Vector<std::string> > get_variables_information(void);

   bool get_display(void);

   // Data methods

   Matrix<double>& get_data(void);

   Matrix<double> get_training_data(void);
   Matrix<double> get_validation_data(void);
   Matrix<double> get_testing_data(void);

   Matrix<double> get_input_data(void);
   Matrix<double> get_target_data(void);

   Matrix<double> get_training_input_data(void);
   Matrix<double> get_training_target_data(void);  
   Matrix<double> get_validation_input_data(void);
   Matrix<double> get_validation_target_data(void);
   Matrix<double> get_testing_input_data(void);
   Matrix<double> get_testing_target_data(void);

   // Instance methods

   Vector<double> get_instance(int);

   Vector<double> get_training_instance(int);
   Vector<double> get_validation_instance(int);
   Vector<double> get_testing_instance(int);

   Vector<double> get_input_instance(int);
   Vector<double> get_target_instance(int);

   Vector<double> get_training_input_instance(int);
   Vector<double> get_training_target_instance(int);

   Vector<double> get_validation_input_instance(int);
   Vector<double> get_validation_target_instance(int);

   Vector<double> get_testing_input_instance(int);
   Vector<double> get_testing_target_instance(int);

   // Set methods

   void set(void);
   void set(int, int);
   void set(int, int, int);

   // Instances methods

   void set_training_instances_indices(const Vector<int>&);
   void set_validation_instances_indices(const Vector<int>&);
   void set_testing_instances_indices(const Vector<int>&);

   void set_training(void);
   void set_validation(void);
   void set_testing(void);

   // Variables methods

   void set_input_variables_indices(const Vector<int>&);
   void set_target_variables_indices(const Vector<int>&);

   void set_input(void);
   void set_target(void);

   // Information methods

   void set_variables_name(const Vector<std::string>&);
   void set_variable_name(int, const std::string&);

   void set_variables_units(const Vector<std::string>&);
   void set_variable_units(int, const std::string&);

   void set_variables_description(const Vector<std::string>&);
   void set_variable_description(int, const std::string&);

   void set_display(bool);

   // Data methods

   void set_data(const Matrix<double>&);

   void set_instances_number(int);
   void set_variables_number(int);

   // Instance methods

   void set_instance(int, const Vector<double>&);

   void set_training_instance(int, const Vector<double>&);
   void set_validation_instance(int, const Vector<double>&);
   void set_testing_instance(int, const Vector<double>&);

   void set_input_instance(int, const Vector<double>&);
   void set_target_instance(int, const Vector<double>&);

   void set_training_input_instance(int, const Vector<double>&);
   void set_training_target_instance(int, const Vector<double>&);

   void set_validation_input_instance(int, const Vector<double>&);
   void set_validation_target_instance(int, const Vector<double>&);

   void set_testing_input_instance(int, const Vector<double>&); 
   void set_testing_target_instance(int, const Vector<double>&);

   // Data resizing methods

   void add_instance(const Vector<double>&);
   void subtract_instance(int);
 
   // Data splitting methods
  
   void split_given_indices(const Vector<int>&, const Vector<int>&, const Vector<int>&);
   void split_random_indices(double, double, double);
   void split_random_indices(void);

   // Initialization methods

   void initialize_data(double);

   // Statistics methods

   Vector< Vector<double> > calculate_data_statistics(void);

   Vector< Vector<double> > calculate_training_instances_statistics(void);
   Vector< Vector<double> > calculate_validation_instances_statistics(void);
   Vector< Vector<double> > calculate_testing_instances_statistics(void);

   Vector< Vector<double> > calculate_instances_statistics(void);

   Vector< Vector<double> > calculate_input_variables_statistics(void);
   Vector< Vector<double> > calculate_target_variables_statistics(void);
   
   Vector< Vector<double> > calculate_variables_statistics(void);

   Vector<double> calculate_training_target_data_mean(void);
   Vector<double> calculate_validation_target_data_mean(void);

   // Data scaling

   void scale_data_mean_standard_deviation(const Vector<double>&, const Vector<double>&);  
   void scale_data_minimum_maximum(const Vector<double>&, const Vector<double>&); 

   // Input variables scaling

   void scale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&);
   Vector< Vector<double> > scale_input_variables_mean_standard_deviation(void);

   void scale_input_variables_minimum_maximum(const Vector<double>&, const Vector<double>&);
   Vector< Vector<double> > scale_input_variables_minimum_maximum(void);

   // Target variables scaling

   void scale_target_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&);
   Vector< Vector<double> > scale_target_variables_mean_standard_deviation(void);

   void scale_target_variables_minimum_maximum(const Vector<double>&, const Vector<double>&);
   Vector< Vector<double> > scale_target_variables_minimum_maximum(void);

   // Input-target variables scaling

   void scale_variables_mean_standard_deviation(const Vector< Vector<double> >);
   Vector< Vector<double> > scale_variables_mean_standard_deviation(void);

   void scale_variables_minimum_maximum(const Vector< Vector<double> >);
   Vector< Vector<double> > scale_variables_minimum_maximum(void);

   // Data unscaling

   void unscale_data_mean_standard_deviation(const Vector<double>&, const Vector<double>&);
   void unscale_data_minimum_maximum(const Vector<double>&, const Vector<double>&);

   // Input variables unscaling

   void unscale_input_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&);
   void unscale_input_variables_minimum_maximum(const Vector<double>&, const Vector<double>&);

   // Target variables unscaling

   void unscale_target_variables_mean_standard_deviation(const Vector<double>&, const Vector<double>&);
   void unscale_target_variables_minimum_maximum(const Vector<double>&, const Vector<double>&);

   // Input-target variables unscaling

   void unscale_variables_mean_standard_deviation(const Vector< Vector<double> >&);
   void unscale_variables_minimum_maximum(const Vector< Vector<double> >&);

   // Utility methods

   std::string to_XML(bool);

   void print(void);
   void save(const char*);
   void load(const char*);

   void print_data(void);
   void save_data(const char*);
   void load_data(const char*);

   std::string get_instances_information_XML(bool);
   void print_instances_information(void);
   void save_instances_information(const char*);

   std::string get_variables_information_XML(bool);
   void print_variables_information(void);
   void save_variables_information(const char*);

   std::string get_data_statistics_XML(bool);
   void print_data_statistics(void);
   void save_data_statistics(const char*);

   std::string get_training_instances_statistics_XML(bool);
   void print_training_instances_statistics(void);
   void save_training_instances_statistics(const char*);

   std::string get_validation_instances_statistics_XML(bool);
   void print_validation_instances_statistics(void);
   void save_validation_instances_statistics(const char*);

   std::string get_testing_instances_statistics_XML(bool);
   void print_testing_instances_statistics(void);
   void save_testing_instances_statistics(const char*);

   std::string get_instances_statistics_XML(bool);
   void print_instances_statistics(void);
   void save_instances_statistics(const char*);

private:

   // MEMBERS

   /// Data Matrix.

   Matrix<double> data;

   /// Indices of instances for training.

   Vector<int> training_instances_indices;

   /// Indices of instances for validation.

   Vector<int> validation_instances_indices;

   /// Indices of instances for testing.

   Vector<int> testing_instances_indices;

   /// Indices of input variables.

   Vector<int> input_variables_indices;

   /// Indices of target variables.

   Vector<int> target_variables_indices;

   /// Name of input variables.

   Vector<std::string> variables_name;

   /// Units of input variables.

   Vector<std::string> variables_units;

   /// Description of input variables.

   Vector<std::string> variables_description;

   /// Display messages to screen.
   
   bool display;
};

}

#endif

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
