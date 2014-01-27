/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   N O R M A L I Z E D   S Q U A R E D   E R R O R   C L A S S   H E A D E R                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef __NORMALIZEDSQUAREDERROR_H__
#define __NORMALIZEDSQUAREDERROR_H__

#include "ObjectiveFunctional.h"
#include "../Utilities/InputTargetDataSet.h"

namespace Flood
{

/// This class represents the normalized squared error objective functional of a multilayer perceptron. This 
/// objective functional is used in data modeling problems. If it has a value of unity then the neural network
/// predicting the data "in the mean" while a value of zero means perfect prediction of data.

class NormalizedSquaredError : public ObjectiveFunctional
{

public:

   // DEFAULT CONSTRUCTOR

   explicit NormalizedSquaredError(void);

   // MULTILAYER PERCEPTRON CONSTRUCTOR

   explicit NormalizedSquaredError(MultilayerPerceptron*);

   // INPUT-TARGET DATA SET CONSTRUCTOR

   explicit NormalizedSquaredError(InputTargetDataSet*);

   // GENERAL CONSTRUCTOR

   explicit NormalizedSquaredError(MultilayerPerceptron*, InputTargetDataSet*);

   // DESTRUCTOR

   virtual ~NormalizedSquaredError(void);


   // METHODS

   // Get methods

   /// This method returns a pointer to the input-target data set object on which the objective functional is measured.

   inline InputTargetDataSet* get_input_target_data_set_pointer(void)
   {
      return(input_target_data_set_pointer);
   }

   // Set methods

   void set(void);
   void set(MultilayerPerceptron*);
   void set(InputTargetDataSet*);
   void set(MultilayerPerceptron*, InputTargetDataSet*);

   void set_input_target_data_set_pointer(InputTargetDataSet*);

   // Normalization coefficients 

   double calculate_training_normalization_coefficient(void);
   double calculate_validation_normalization_coefficient(void);

   // Objective functional evaluation methods

   double calculate_objective(void);

   // Validation error methods

   double calculate_validation_error(void);   

   // Objective function gradient vector methods

   Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&);
   Vector< Vector<double> > calculate_hidden_errors(const Vector< Vector<double> >&, const Vector<double>&);
   Vector<double> calculate_hidden_layers_error_gradient(const Vector<double>&, const Vector< Vector<double> >&, const Vector< Vector<double> >&);
   Vector<double> calculate_output_layer_error_gradient(const Vector< Vector<double> >&, const Vector<double>&);

   Vector<double> calculate_objective_gradient(void);


private:

   // MEMBERS

   /// Pointer to an input-target data set object.

   InputTargetDataSet* input_target_data_set_pointer;

   /// Mean values of all the target variables. 

   Vector<double> training_target_mean;
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

