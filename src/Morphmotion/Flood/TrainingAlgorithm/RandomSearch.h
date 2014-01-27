/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   R A N D O M   S E A R C H   C L A S S   H E A D E R                                                        */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __RANDOMSEARCH_H__
#define __RANDOMSEARCH_H__

#include "TrainingAlgorithm.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"
 
namespace Flood
{

/// This concrete class represents a random search training algorithm
/// for an objective functional of a multilayer perceptron.

class RandomSearch : public TrainingAlgorithm
{

public:

   // GENERAL CONSTRUCTOR

   explicit RandomSearch(ObjectiveFunctional*); 


   // DEFAULT CONSTRUCTOR

   explicit RandomSearch(void); 


   // DESTRUCTOR

   virtual ~RandomSearch(void);

   // METHODS

   // Get methods

   double get_training_rate_reduction_factor(void);
   int get_training_rate_reduction_period(void);

   bool get_reserve_potential_parameters_history(void);
   bool get_reserve_potential_parameters_norm_history(void);

   bool get_reserve_potential_evaluation_history(void);

   Vector< Vector<double> > get_potential_parameters_history(void);
   Vector<double> get_potential_parameters_norm_history(void);

   Vector<double> get_potential_evaluation_history(void);

   // Set methods

   void set_default(void);

   void set_training_rate_reduction_factor(double);
   void set_training_rate_reduction_period(int);

   void set_reserve_potential_parameters_history(bool);
   void set_reserve_potential_parameters_norm_history(bool);

   void set_reserve_potential_evaluation_history(bool);

   void set_potential_parameters_history(const Vector< Vector<double> >&);
   void set_potential_parameters_norm_history(const Vector<double>&);

   void set_potential_evaluation_history(const Vector<double>&);

   // Train methods

   Vector<double> calculate_training_direction(void);

   void train(void);

   // Training history methods

   void resize_training_history(int);
   void set_reserve_all_training_history(bool);

   std::string get_training_history_XML(bool);

   // Utiltity methods

   std::string to_XML(bool);
   void load(const char*);

private: 

   // MEMBERS

   double training_rate_reduction_factor;
   int training_rate_reduction_period;

   bool reserve_potential_parameters_history;
   bool reserve_potential_parameters_norm_history;

   bool reserve_potential_evaluation_history;
   
   Vector< Vector<double> > potential_parameters_history;
   Vector<double> potential_parameters_norm_history;

   Vector<double> potential_evaluation_history;
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
