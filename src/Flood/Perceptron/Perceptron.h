/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   P E R C E P T R O N   C L A S S   H E A D E R                                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include "../Utilities/Vector.h"

namespace Flood
{

/// This class represents the concept of perceptron neuron model.
/// The perceptron implemented here admits a variety of activation or transfer functions. 

class Perceptron
{
public:

   // DEFAULT CONSTRUCTOR

   explicit Perceptron(void);

   // INPUTS NUMBER CONSTRUCTOR

   explicit Perceptron(int);

   // INPUTS NUMBER AND INITIALIZATION CONSTRUCTOR

   explicit Perceptron(int, double);

   // FILE CONSTRUCTOR

   explicit Perceptron(const char*);

   // COPY CONSTRUCTOR

   Perceptron(const Perceptron&);

   // DESTRUCTOR

   virtual ~Perceptron(void);

   // ASSIGNMENT OPERATOR

   Perceptron& operator = (const Perceptron&);

   // ENUMERATIONS

   /// Enumeration of available activation functions for the perceptron neuron model. 

   enum ActivationFunction{Threshold, SymmetricThreshold, Logistic, HyperbolicTangent, Linear};

   // METHODS

   // Get methods

   /// This method returns the number of inputs in the neuron. 

   inline int get_inputs_number(void)
   {
      return(inputs_number);
   }    ActivationFunction& get_activation_function(void);
   std::string get_activation_function_name(void);

   double get_bias(void);   

   Vector<double>& get_synaptic_weights(void);
   double get_synaptic_weight(int);

   int get_parameters_number(void);
   Vector<double> get_parameters(void);

   bool get_display(void);

   // Set methods

   void set(void);
   void set(int);
   void set(int, double);
   void set(const Perceptron&);

   void set_inputs_number(int);

   void set_activation_function(const ActivationFunction&);
   void set_activation_function(const std::string&);

   void set_bias(double);
   void set_synaptic_weights(const Vector<double>&);
   void set_synaptic_weight(int, double);

   void set_parameters(const Vector<double>&);

   void set_display(bool);

   // Initialization methods

   void initialize_bias(double);
   void initialize_bias_uniform(double, double);
   void initialize_bias_normal(double, double);

   void initialize_synaptic_weights(double);
   void initialize_synaptic_weights_uniform(double, double);
   void initialize_synaptic_weights_normal(double, double);

   void initialize_parameters(double);

   // Combination methods

   double calculate_combination(const Vector<double>&);

   // Activation methods

   double calculate_activation(double);
   double calculate_activation_derivative(double);
   double calculate_activation_second_derivative(double);

   // Output methods

   double calculate_output(const Vector<double>&);

   // Utility methods

   std::string to_XML(bool);

   void print(void);

   void save(const char*);
   void load(const char*);

private: 

   // FIELDS

   /// Activation function variable. 

   ActivationFunction activation_function;

   /// Number of inputs in the neuron.

   int inputs_number;

   /// Bias value.

   double bias;

   /// Synaptic weight values.

   Vector<double> synaptic_weights;

   /// Display messages to screen. 

   bool display;

   // METHODS

   // Utility methods

   double calculate_random_uniform(double, double);
   double calculate_random_normal(double, double);
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

