/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   O B J E C T I V E   F U N C T I O N A L   C L A S S   H E A D E R                                          */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __OBJECTIVEFUNCTIONAL_H__
#define __OBJECTIVEFUNCTIONAL_H__

// Flood includes

#include "../Utilities/Vector.h"
#include "../Utilities/Matrix.h"
#include "../MultilayerPerceptron/MultilayerPerceptron.h"

// System includes

#include <string>

namespace Flood
{

/// This abstract class represents the concept of objective functional for the multilayer perceptron. 
/// Any derived class must implement the calculate_evaluation(void) method.

class ObjectiveFunctional
{

public:

   // DEFAULT CONSTRUCTOR

   explicit ObjectiveFunctional(void);

   // GENERAL CONSTRUCTOR

   explicit ObjectiveFunctional(MultilayerPerceptron*);

   // DESTRUCTOR

   virtual ~ObjectiveFunctional(void);


   // ENUMERATIONS

   /// Enumeration of available regularization terms. 

   enum RegularizationMethod{None, NeuralParametersNorm};

   /// Enumeration of available methods for calculating any derivative of the objective function numerically.

   enum NumericalDifferentiationMethod{ForwardDifferences, CentralDifferences};

   /// Enumeration of available methods for obtaining a numerical value of epsilon to be used in numerical differentiation.

   enum NumericalEpsilonMethod{Absolute, Relative};

   // METHODS

   // Get methods

   /// This method returns a pointer to the multilayer perceptron object associated to the objective functional.

   inline MultilayerPerceptron* get_multilayer_perceptron_pointer(void)
   {
      return(multilayer_perceptron_pointer);
   }

   // Objective term methods 

   double get_objective_weight(void);

   // Regularization term methods

   RegularizationMethod& get_regularization_method(void);
   std::string get_regularization_method_name(void);

   double get_regularization_weight(void);

   // Numerical differentiation methods

   NumericalDifferentiationMethod get_numerical_differentiation_method(void);
   std::string get_numerical_differentiation_method_name(void);

   NumericalEpsilonMethod get_numerical_epsilon_method(void);
   std::string get_numerical_epsilon_method_name(void);

   double get_numerical_epsilon(void);

   // Counter methods

   int get_calculate_evaluation_count(void);
   int get_calculate_gradient_count(void);
   int get_calculate_Hessian_count(void);

   bool get_display(void);

   // Set methods

   void set_multilayer_perceptron_pointer(MultilayerPerceptron*);

   void set_default(void);

   // Objective term methods 

   void set_objective_weight(double);

   // Regularization term methods

   void set_regularization_method(const RegularizationMethod&); 
   void set_regularization_method(const std::string&);

   void set_regularization_weight(double);

   // Numerical differentiation methods

   void set_numerical_differentiation_method(const NumericalDifferentiationMethod&);
   void set_numerical_differentiation_method(const std::string&);

   void set_numerical_epsilon_method(const NumericalEpsilonMethod&);
   void set_numerical_epsilon_method(const std::string&);

   void set_numerical_epsilon(double);

   // Counter methods

   void set_calculate_evaluation_count(int);
   void set_calculate_gradient_count(int);
   void set_calculate_Hessian_count(int);

   void set_display(bool);

   // Objective functional evaluation methods

   double calculate_evaluation();
   double calculate_evaluation(int,int);
   double calculate_evaluation(int,int,int);

   double calculate_potential_evaluation(const Vector<double>&);
   double calculate_potential_evaluation(const Vector<double>&,int,int);
   double calculate_potential_evaluation(const Vector<double>&,int,int,int);

   /// This method returns the objective value of a multilayer perceptron.

   virtual double calculate_objective() = 0;
   virtual double calculate_objective(int,int) = 0;
   virtual double calculate_objective(int,int,int) = 0;

   virtual double calculate_regularization(void); 

   // Objective function gradient methods

   Vector<double> calculate_gradient(void);
   Vector<double> calculate_potential_gradient(const Vector<double>&);

   double calculate_gradient_norm(void);

   /// This method returns the objective function gradient vector for a multilayer perceptron.

   virtual Vector<double> calculate_objective_gradient(void); 
   virtual Vector<double> calculate_regularization_gradient(void); 

   virtual Vector<double> calculate_neural_parameters_gradient(void);
   virtual Vector<double> calculate_independent_parameters_gradient(void);

   // Objective function gradient numerical differentiation methods

   Vector<double> calculate_objective_gradient_numerical_differentiation(void);

   Vector<double> calculate_neural_parameters_gradient_numerical_differentiation(void);  
   Vector<double> calculate_neural_parameters_gradient_forward_differences(void);
   Vector<double> calculate_neural_parameters_gradient_central_differences(void);

   Vector<double> calculate_independent_parameters_gradient_numerical_differentiation(void);  
   Vector<double> calculate_independent_parameters_gradient_forward_differences(void);
   Vector<double> calculate_independent_parameters_gradient_central_differences(void);

   // Objective function Hessian methods

   /// This method returns the objective function Hessian matrix for a multilayer perceptron.

   virtual Matrix<double> calculate_Hessian(void);
   Matrix<double> calculate_potential_Hessian(const Vector<double>&);

   // Objective function Hessian numerical differentiation methods

   Matrix<double> calculate_Hessian_numerical_differentiation(void);
   Matrix<double> calculate_Hessian_forward_differences(void);
   Matrix<double> calculate_Hessian_central_differences(void);

   // Objective function inverse Hessian methods

   virtual Matrix<double> calculate_inverse_Hessian(void);

   Matrix<double> calculate_DFP_inverse_Hessian
   (const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&);

   Matrix<double> calculate_BFGS_inverse_Hessian
   (const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&);

   // Objective function vector Hessian product methods

   virtual Vector<double> calculate_vector_dot_Hessian(const Vector<double>&);

   // Objective function vector Hessian product numerical differentiation methods

   Vector<double> calculate_vector_dot_Hessian_numerical_differentiation(const Vector<double>&);

   Vector<double> calculate_vector_dot_Hessian_forward_differences(const Vector<double>&);
   Vector<double> calculate_vector_dot_Hessian_central_differences(const Vector<double>&);

   // Validation error methods

   virtual double calculate_validation_error(void);

   // Numerical epsilon methods

   double calculate_actual_epsilon(double); 

   // Utility methods

   virtual std::string to_XML(bool);   

   virtual void print(void);   
   virtual void save(const char*);   
   virtual void load(const char*);   

   virtual void print_information(void);   

protected:

   /// Pointer to a multilayer perceptron object.

   MultilayerPerceptron* multilayer_perceptron_pointer;

   /// Weight of the objective term in the objective functional expression. 

   double objective_weight;

   /// Regularization methods enumeration. 

   RegularizationMethod regularization_method;

   /// Weight of the regularization term in the objective functional expression. 

   double regularization_weight;

   /// Number of calls to the calculate_evaluation(void) method.

   int calculate_evaluation_count;

   /// Number of calls to the calculate_gradient(void) method. 

   int calculate_gradient_count;

   /// Number of calls to the calculate_Hessian(void) method. 

   int calculate_Hessian_count;

   /// Numerical differentiation methods enumeration.

   NumericalDifferentiationMethod numerical_differentiation_method;

   /// Numerical epsilon methods enumeration.

   NumericalEpsilonMethod numerical_epsilon_method;

   /// Epsilon value for the calculation of any derivative with numerical differentiation.

   double numerical_epsilon;   

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
