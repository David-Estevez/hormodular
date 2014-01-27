/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   Q U A S I - N E W T O N   M E T H O D    C L A S S   H E A D E R                                           */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __QUASINEWTONMETHOD_H__
#define __QUASINEWTONMETHOD_H__

#include "TrainingAlgorithm.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"

namespace Flood
{

/// This concrete class represents a quasi-Newton training algorithm for an objective functional of a multilayer 
/// perceptron.

class QuasiNewtonMethod : public TrainingAlgorithm
{

public:

   // ENUMERATIONS

   /// Enumeration of the available training operators for obtaining the approximation to the inverse Hessian.

   enum InverseHessianApproximationMethod{DFP, BFGS};


   // GENERAL CONSTRUCTOR

   explicit QuasiNewtonMethod(ObjectiveFunctional*);


   // DEFAULT CONSTRUCTOR

   explicit QuasiNewtonMethod(void);


   // DESTRUCTOR

   virtual ~QuasiNewtonMethod(void);


   // METHODS

   // Get methods

   InverseHessianApproximationMethod get_inverse_Hessian_approximation_method(void);
   std::string get_inverse_Hessian_approximation_method_name(void);

   // Set methods

   void set_inverse_Hessian_approximation_method(const InverseHessianApproximationMethod&);
   void set_inverse_Hessian_approximation_method(const std::string&);

   // Train methods

   Vector<double> calculate_training_direction(const Vector<double>&, const Matrix<double>&);

   Matrix<double> calculate_inverse_Hessian_approximation(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&);

   Vector<double> calculate_gradient_descent_training_direction(const Vector<double>&);
   
   void train(void);

   // Training history methods

   void resize_training_history(int);

   void set_reserve_all_training_history(bool);

   std::string get_training_history_XML(bool);

   // Utility methods

   std::string to_XML(bool);

   void load(const char*);
   

private: 

   // FIELDS

   /// Variable containing the actual method used to obtain a suitable training rate. 

   InverseHessianApproximationMethod inverse_Hessian_approximation_method;

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
