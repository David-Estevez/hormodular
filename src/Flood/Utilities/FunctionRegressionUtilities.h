/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   F U N C T I O N   R E G R E S S I O N   U T I L I T I E S   C L A S S   H E A D E R                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __FUNCTIONREGRESSIONUTILITIES_H__
#define __FUNCTIONREGRESSIONUTILITIES_H__

// Flood includes

#include "../Utilities/Vector.h"
#include "../Utilities/Matrix.h"
#include "../Utilities/InputTargetDataSet.h"
#include "../MultilayerPerceptron/MultilayerPerceptron.h"

namespace Flood
{

/// This class contains methods which can useful when solving function regression problems.
/// This includes artificial data generators of testing methods for this class of applications.

class FunctionRegressionUtilities
{

public:  

   // DEFAULT CONSTRUCTOR

   explicit FunctionRegressionUtilities(void);

   // MULTILAYER PERCEPTRON CONSTRUCTOR

   explicit FunctionRegressionUtilities(MultilayerPerceptron*);

   // INPUT-TARGET DATA SEET CONSTRUCTOR

   explicit FunctionRegressionUtilities(InputTargetDataSet*);

   // GENERAL CONSTRUCTOR

   explicit FunctionRegressionUtilities(MultilayerPerceptron*, InputTargetDataSet*);

   // DESTRUCTOR

   virtual ~FunctionRegressionUtilities();

   // METHODS

   // Get methods

   MultilayerPerceptron* get_multilayer_perceptron_pointer(void);
   InputTargetDataSet* get_input_target_data_set_pointer(void);
   
   bool get_display(void);

   // Set methods

   void set_multilayer_perceptron_pointer(MultilayerPerceptron*);
   void set_input_target_data_set_pointer(InputTargetDataSet*);

   void set_display(bool);

   // Arfificial data generators

   void generate_artificial_data(const Vector<double>&, const Vector<double>&, const Vector<std::string>&);

   // Testing target output data methods

   Vector< Matrix<double> > calculate_testing_target_output_data(void);
   std::string get_testing_target_output_data(bool);
   void print_testing_target_output_data(void);
   void save_testing_target_output_data(const char*);

   // Linear regression parameters methods

   Vector< Vector<double> > calculate_linear_regression_parameters(void);
   std::string get_linear_regression_parameters(bool);
   void print_linear_regression_parameters(void);
   void save_linear_regression_parameters(const char*);

   // Linear regression analysis methods

   std::string get_linear_regression_analysis(bool);
   void print_linear_regression_analysis(void);
   void save_linear_regression_analysis(const char*);

private: 

   // MEMBERS

   /// Pointer to a multilayer perceptron object.

   MultilayerPerceptron* multilayer_perceptron_pointer;

   /// Pointer to an input-target data set object.

   InputTargetDataSet* input_target_data_set_pointer;

   /// Display messages to screen.
   
   bool display;

   // METHODS

   // Artificial data generator methods

   double calculate_De_Jong_function_evaluation(const Vector<double>&);
   double calculate_Rosenbrock_function_evaluation(const Vector<double>&);
   double calculate_Rastrigin_function_evaluation(const Vector<double>&);

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
