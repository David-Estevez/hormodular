/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   C O N J U G A T E   G R A D I E N T   C L A S S   H E A D E R                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef __CONJUGATEGRADIENT_H__
#define __CONJUGATEGRADIENT_H__

#include "TrainingAlgorithm.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"

namespace Flood
{

/// This concrete class represents a conjugate gradient training algorithm for an objective functional of a 
/// multilayer perceptron. 
	
class ConjugateGradient : public TrainingAlgorithm
{

public:

   // ENUMERATIONS

   /// Enumeration of the available training operators for obtaining the training direction.

   enum TrainingDirectionMethod{PolakRibiere, FletcherReeves};


   // GENERAL CONSTRUCTOR

   explicit ConjugateGradient(ObjectiveFunctional*);


   // DEFAULT CONSTRUCTOR

   explicit ConjugateGradient(void); 


   // DESTRUCTOR

   virtual ~ConjugateGradient(void);


   // METHODS

   // Get methods

   TrainingDirectionMethod get_training_direction_method(void);
   std::string get_training_direction_method_name(void);

   // Set methods

   void set_training_direction_method(const TrainingDirectionMethod&);
   void set_training_direction_method(const std::string&);

   // Training direction methods

   double calculate_Polak_Ribiere_parameter(const Vector<double>&, const Vector<double>&);
   double calculate_Fletcher_Reeves_parameter(const Vector<double>&, const Vector<double>&);

   Vector<double> calculate_Polak_Ribiere_training_direction(const Vector<double>&, const Vector<double>&, const Vector<double>&);
   Vector<double> calculate_Fletcher_Reeves_training_direction(const Vector<double>&, const Vector<double>&, const Vector<double>&);

   Vector<double> calculate_training_direction(const Vector<double>&, const Vector<double>&, const Vector<double>&);

   Vector<double> calculate_gradient_descent_training_direction(const Vector<double>&);

   // Train methods

   void train(void);

   // Training history methods

   void set_reserve_all_training_history(bool);
   void resize_training_history(int);

   std::string get_training_history_XML(bool);

   // Utility methods

   std::string to_XML(bool);
   void load(const char*);

private:

   TrainingDirectionMethod training_direction_method;
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

