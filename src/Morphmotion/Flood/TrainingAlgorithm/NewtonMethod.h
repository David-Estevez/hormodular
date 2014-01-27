/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   N E W T O N   M E T H O D   C L A S S   H E A D E R                                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __NEWTONMETHOD_H__
#define __NEWTONMETHOD_H__

// Flood includes 

#include "TrainingAlgorithm.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"

namespace Flood
{


/// This concrete class represents the Newton method training algorithm
/// for an objective functional of a multilayer perceptron.

class NewtonMethod : public TrainingAlgorithm
{

public:

   // GENERAL CONSTRUCTOR

   explicit NewtonMethod(ObjectiveFunctional*);


   // DEFAULT CONSTRUCTOR

   explicit NewtonMethod(void); 


   // DESTRUCTOR

   virtual ~NewtonMethod(void);


   // METHODS

   // Train methods

   Vector<double> calculate_training_direction(const Vector<double>&, const Matrix<double>&);
   Vector<double> calculate_gradient_descent_training_direction(const Vector<double>&);

   void train(void);

   // Training history methods

   void set_reserve_all_training_history(bool);
   void resize_training_history(int);

   std::string get_training_history_XML(bool);

   // Utility methods

   std::string to_XML(bool);
   void load(const char*);
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
