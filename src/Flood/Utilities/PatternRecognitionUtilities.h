/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   P A T T E R N   R E C O G N I T I O N   U T I L I T I E S   C L A S S   H E A D E R                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __PATTERNRECOGNITIONUTILITIES_H__
#define __PATTERNRECOGNITIONUTILITIES_H__

// System includes

#include "../Utilities/Vector.h"
#include "../Utilities/Matrix.h"
#include "../Utilities/InputTargetDataSet.h"
#include "../MultilayerPerceptron/MultilayerPerceptron.h"

namespace Flood
{

/// This class contains some useful utilities for pattern recognition (or classification problems).
/// That includes generating artificial data or performing testing of results. 

class PatternRecognitionUtilities
{

public:  

   // DEFAULT CONSTRUCTOR

   explicit PatternRecognitionUtilities(void);

   // MULTILAYER PERCEPTRON CONSTRUCTOR

   explicit PatternRecognitionUtilities(MultilayerPerceptron*);

   // INPUT-TARGET DATA SET CONSTRUCTOR

   explicit PatternRecognitionUtilities(InputTargetDataSet*);

   // GENERAL CONSTRUCTOR

   explicit PatternRecognitionUtilities(MultilayerPerceptron*, InputTargetDataSet*);

   // DESTRUCTOR

   virtual ~PatternRecognitionUtilities(void);


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

   void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&);

   // Output data methods

   Matrix<bool> calculate_binary_output_data(void);

   Matrix<bool> calculate_binary_training_output_data(void);
   Matrix<bool> calculate_binary_validation_output_data(void);
   Matrix<bool> calculate_binary_testing_output_data(void);

   // Target data methods

   Matrix<bool> get_binary_target_data(void);

   Matrix<bool> get_binary_training_target_data(void);
   Matrix<bool> get_binary_validation_target_data(void);
   Matrix<bool> get_binary_testing_target_data(void);

   // Class distribution methods

   Vector<int> calculate_class_distribution(void);
   std::string get_class_distribution_XML(bool);
   void print_class_distribution(void);
   void save_class_distribution(const char*);
   
   // Binary classification test methods
   
   Vector<double> calculate_binary_classification_test(void);
   std::string get_binary_classification_test_XML(bool);
   void print_binary_classification_test(void);
   void save_binary_classification_test(const char*);
 
   // Confusion matrix methods

   Matrix<int> calculate_confusion(void);
   std::string get_confusion_XML(bool);
   void print_confusion(void);
   void save_confusion(const char*);


private: 

   // FIELDS

   /// Pointer to a multilayer perceptron object.

   MultilayerPerceptron* multilayer_perceptron_pointer;

   /// Pointer to an input-target data set object.

   InputTargetDataSet* input_target_data_set_pointer;

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
