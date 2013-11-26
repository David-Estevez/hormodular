/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   T R A I N I N G   A L G O R I T H M   C L A S S   H E A D E R                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef __TRAININGALGORITHM_H__
#define __TRAININGALGORITHM_H__

#include "../MultilayerPerceptron/MultilayerPerceptron.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"


namespace Flood
{

/// This abstract class represents the concept of training algorithm
/// for the multilayer perceptron. Any derived class must implement the
/// train(void), print(void) and save(const char*) methods.

class TrainingAlgorithm
{

public:

   // ENUMERATIONS

   /// Available training operators for obtaining the train rate.

   enum TrainingRateMethod{Fixed, GoldenSection, BrentMethod};


   // GENERAL CONSTRUCTOR

   explicit TrainingAlgorithm(ObjectiveFunctional*);


   // DEFAULT CONSTRUCTOR

   explicit TrainingAlgorithm(void);


   // DESTRUCTOR

   virtual ~TrainingAlgorithm(void);


   // METHODS

   // Get methods

   ObjectiveFunctional* get_objective_functional_pointer(void);

   // Training operators

   TrainingAlgorithm::TrainingRateMethod get_training_rate_method(void);
   std::string get_training_rate_method_name(void);

   // Training parameters

   double get_first_training_rate(void);
   double get_bracketing_factor(void);   
   double get_training_rate_tolerance(void);

   double get_warning_parameters_norm(void);
   double get_warning_gradient_norm(void);
   double get_warning_training_rate(void);

   double get_error_parameters_norm(void);
   double get_error_gradient_norm(void);
   double get_error_training_rate(void);

   // Stopping criteria

   double get_minimum_parameters_increment_norm(void);

   double get_minimum_evaluation_improvement(void);
   double get_evaluation_goal(void);
   double get_gradient_norm_goal(void);

   int get_maximum_epochs_number(void);
   double get_maximum_time(void);

   // Early stopping

   bool get_early_stopping(void);

   // Reserve training history

   bool get_reserve_parameters_history(void);
   bool get_reserve_parameters_norm_history(void);

   bool get_reserve_evaluation_history(void);
   bool get_reserve_gradient_history(void);
   bool get_reserve_gradient_norm_history(void);
   bool get_reserve_inverse_Hessian_history(void);
   bool get_reserve_validation_error_history(void);

   bool get_reserve_training_direction_history(void);
   bool get_reserve_training_rate_history(void);
   bool get_reserve_elapsed_time_history(void);

   // Training history

   Vector< Vector<double> >& get_parameters_history(void);
   Vector<double>& get_parameters_norm_history(void);

   Vector<double>& get_evaluation_history(void);
   Vector< Vector<double> >& get_gradient_history(void);
   Vector<double>& get_gradient_norm_history(void);
   Vector< Matrix<double> >& get_inverse_Hessian_history(void);
   Vector<double>& get_validation_error_history(void);

   Vector< Vector<double> >& get_training_direction_history(void);
   Vector<double>& get_training_rate_history(void);
   Vector<double>& get_elapsed_time_history(void);
  
   // Utilities
   
   bool get_display(void);
   int get_display_period(void);
  
   // Set methods

   void set(void);
   void set(ObjectiveFunctional*);
   virtual void set_default(void);

   void set_objective_functional_pointer(ObjectiveFunctional*);

   // Training operators

   void set_training_rate_method(const TrainingRateMethod&);
   void set_training_rate_method(const std::string&);

   // Training parameters

   void set_first_training_rate(double);
   void set_bracketing_factor(double);   
   void set_training_rate_tolerance(double);

   void set_warning_parameters_norm(double);
   void set_warning_gradient_norm(double);
   void set_warning_training_rate(double);

   void set_error_parameters_norm(double);
   void set_error_gradient_norm(double);
   void set_error_training_rate(double);

   // Stopping criteria

   void set_minimum_parameters_increment_norm(double);

   void set_minimum_evaluation_improvement(double);
   void set_evaluation_goal(double);
   void set_gradient_norm_goal(double);

   void set_maximum_epochs_number(int);
   void set_maximum_time(double);

   // Early stopping

   void set_early_stopping(bool);

   // Reserve training history

   void set_reserve_parameters_history(bool);
   void set_reserve_parameters_norm_history(bool);

   void set_reserve_evaluation_history(bool);
   void set_reserve_gradient_history(bool);
   void set_reserve_gradient_norm_history(bool);
   void set_reserve_inverse_Hessian_history(bool);
   void set_reserve_validation_error_history(bool);

   void set_reserve_training_direction_history(bool);
   void set_reserve_training_rate_history(bool);
   void set_reserve_elapsed_time_history(bool);

   /// This method makes the training history of all variables to be reseved or not in memory.

   virtual void set_reserve_all_training_history(bool);

   // Training history

   void set_parameters_history(const Vector< Vector<double> >&);
   void set_parameters_norm_history(const Vector<double>&);

   void set_evaluation_history(const Vector<double>&);
   void set_gradient_history(const Vector< Vector<double> >&);
   void set_gradient_norm_history(const Vector<double>&);
   void set_inverse_Hessian_history(const Vector< Matrix<double> >&);

   void set_training_direction_history(const Vector< Vector<double> >&);
   void set_training_rate_history(const Vector<double>&);
   void set_elapsed_time_history(const Vector<double>&);

   void set_validation_error_history(const Vector<double>&);

   // Utilities

   void set_display(bool);
   void set_display_period(int);

   // Training methods

   /// This method trains a multilayer perceptron which has a objective functional associated. 

   virtual void train(void) = 0;

   // Training rate method

   Vector<double> calculate_training_rate_evaluation(double, const Vector<double>&, double);

   Vector<double> calculate_fixed_training_rate_evaluation(double, const Vector<double>&, double);
   Vector<double> calculate_golden_section_training_rate_evaluation(double, const Vector<double>&, double);
   Vector<double> calculate_Brent_method_training_rate_evaluation(double, const Vector<double>&, double);

   Vector<double> calculate_bracketing_training_rate_evaluation(double, const Vector<double>&, double);

   // Training history methods   

   virtual void resize_training_history(int);

   virtual std::string get_training_history_XML(bool);   
   void print_training_history(void);
   void save_training_history(const char*);

   // Utility methods

   virtual std::string to_XML(bool);   
   void print(void);
   void save(const char*);
   virtual void load(const char*);


protected:

   // FIELDS

   /// Pointer to an objective functional for a multilayer perceptron object.

   ObjectiveFunctional* objective_functional_pointer;

   // TRAINING OPERATORS

   /// Variable containing the actual method used to obtain a suitable train rate. 

   TrainingRateMethod training_rate_method;

   /// Increase factor when bracketing a minimum.

   double bracketing_factor;

   /// Initial train rate in line minimization.

   double first_training_rate;

   /// Tolerance for the train rate.

   double training_rate_tolerance;

   /// Value for the parameters norm at which a warning message is written to the screen. 

   double warning_parameters_norm;

   /// Value for the gradient norm at which a warning message is written to the screen. 

   double warning_gradient_norm;   

   /// Training rate value at wich a warning message is written to the screen.

   double warning_training_rate;

   /// Value for the parameters norm at which the training process is assumed to fail. 
   
   double error_parameters_norm;

   /// Value for the gradient norm at which the training process is assumed to fail. 

   double error_gradient_norm;

   /// Training rate at wich the line minimization algorithm is assumed to be unable to bracket a minimum.

   double error_training_rate;


   // STOPPING CRITERIA

   /// Norm of the parameters increment vector at which training stops.

   double minimum_parameters_increment_norm;

   /// Minimum evaluation improvement between two successive epochs. It is used as a train stopping criterion.

   double minimum_evaluation_improvement;

   /// Goal value for the objective. It is used as a train stopping criterion.

   double evaluation_goal;

   /// Goal value for the norm of the objective function gradient. It is used as a stopping criterion.

   double gradient_norm_goal;

   /// Maximum number of epochs to train. It is used as a train stopping criterion.

   int maximum_epochs_number;

   /// Maximum training time. It is used as a train stopping criterion.

   double maximum_time;

   /// True if early stopping is to be performed, and false otherwise.

   bool early_stopping;

   // TRAINING HISTORY

   /// True if the parameters history matrix is to be reserved, false otherwise.

   bool reserve_parameters_history;

   /// True if the parameters norm history vector is to be reserved, false otherwise.

   bool reserve_parameters_norm_history;

   /// True if the evaluation history vector is to be reserved, false otherwise.

   bool reserve_evaluation_history;

   /// True if the gradient history matrix is to be reserved, false otherwise.

   bool reserve_gradient_history;

   /// True if the gradient norm history vector is to be reserved, false otherwise.

   bool reserve_gradient_norm_history;

   /// True if the inverse Hessian history vector of matrices is to be reserved, false otherwise.

   bool reserve_inverse_Hessian_history;

   /// True if the training direction history matrix is to be reserved, false otherwise.
   
   bool reserve_training_direction_history;

   /// True if the training rate history vector is to be reserved, false otherwise.

   bool reserve_training_rate_history;

   /// True if the elapsed time history vector is to be reserved, false otherwise.

   bool reserve_elapsed_time_history;

   /// True if the validation error history vector is to be reserved, false otherwise. 

   bool reserve_validation_error_history;

   /// Vector of vectors containing the parameters history over the training epochs.

   Vector< Vector<double> > parameters_history;

   /// Vector containing the parameters norm history over the training epochs.

   Vector<double> parameters_norm_history;

   /// Vector containing the evaluation history over the training epochs.

   Vector<double> evaluation_history;

   /// Vector of vectors containing the gradient history over the training epochs.

   Vector< Vector<double> > gradient_history;

   /// Vector containing the gradient norm history over the training epochs.

   Vector<double> gradient_norm_history;
    
   /// Vector of matrices containing the history of the inverse Hessian over the epochs. 

   Vector< Matrix<double> > inverse_Hessian_history;   

   /// Vector of vectors containing the training direction history over the epochs.

   Vector< Vector<double> > training_direction_history;

   /// Vector containing the training rate history over the epochs.

   Vector<double> training_rate_history;

   /// Vector containing the elapsed time history over the training epochs.

   Vector<double> elapsed_time_history;

   /// Vector containing the validation error history over the training epochs. 

   Vector<double> validation_error_history;

   // UTILITIES

   /// Display messages to screen.

   bool display;

   /// Number of epochs between the training showing progress.

   int display_period;
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
