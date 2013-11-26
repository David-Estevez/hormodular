/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   G R A D I E N T   D E S C E N T   C L A S S   H E A D E R                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __GRADIENTDESCENT_H__
#define __GRADIENTDESCENT_H__

#include "TrainingAlgorithm.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"


namespace Flood
{

/// This concrete class represents the gradient descent training algorithm for an objective functional of a 
/// multilayer perceptron.

class GradientDescent : public TrainingAlgorithm
{

public:

   // GENERAL CONSTRUCTOR

   explicit GradientDescent(ObjectiveFunctional*);


   // DEFAULT CONSTRUCTOR

   explicit GradientDescent(void); 


   // DESTRUCTOR

   virtual ~GradientDescent(void);


   // METHODS

   // Set methods

   void set_reserve_all_training_history(bool);

   // Train methods

   Vector<double> calculate_training_direction(const Vector<double>&);

   void train(void);

   // Training history methods

   void resize_training_history(int);

   std::string get_training_history_XML(bool);

   // Utility methods

   std::string to_XML(bool);

   void load(const char*);
};

}

#endif
