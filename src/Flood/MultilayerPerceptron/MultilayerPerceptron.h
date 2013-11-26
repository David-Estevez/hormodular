/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   M U L T I L A Y E R   P E R C E P T R O N   C L A S S   H E A D E R                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MULTILAYERPERCEPTRON_H__
#define __MULTILAYERPERCEPTRON_H__

#include <string>

#include "../Perceptron/Perceptron.h"

#include "../Utilities/Vector.h"
#include "../Utilities/Matrix.h"

namespace Flood
{

/// This class represents the concept of multilayer perceptron neural network. 

class MultilayerPerceptron
{

public:

   // DEFAULT CONSTRUCTOR

   explicit MultilayerPerceptron(void);

   // NETWORK ARCHITECTURE CONSTRUCTOR

   explicit MultilayerPerceptron(int, const Vector<int>&, int);

   // ONE HIDDEN LAYER CONSTRUCTOR

   explicit MultilayerPerceptron(int, int, int);

   // INDEPENDENT PARAMETERS CONSTRUCTOR

   explicit MultilayerPerceptron(int);

   // FILE CONSTRUCTOR

   explicit MultilayerPerceptron(const char*);

   // COPY CONSTRUCTOR

   MultilayerPerceptron(const MultilayerPerceptron&);

   // DESTRUCTOR

   virtual ~MultilayerPerceptron(void);

   // ASSIGNMENT OPERATOR

   MultilayerPerceptron& operator = (const MultilayerPerceptron&);

   // ENUMERATIONS

   /// Enumeration of available activation functions for the hidden and the output layers.

   enum LayerActivationFunction{Logistic, HyperbolicTangent, Threshold, SymmetricThreshold, Linear};

   /// Enumeration of available methods for input variables, output variables and independent parameters scaling.  
   
   enum ScalingMethod{None, MeanStandardDeviation, MinimumMaximum};

   /// Enumeration of available methods for obtaining a numerical value of epsilon to be used in numerical differentiation.

   enum NumericalEpsilonMethod{Absolute, Relative};

   /// Enumeration of available methods for calculating the Jacobian matrix of the multilayer perceptron numerically.

   enum NumericalDifferentiationMethod{ForwardDifferences, CentralDifferences};

   // GET METHODS

   // Network architecture

   /// This method returns the number of inputs in the neural network.

   inline int get_inputs_number(void)
   {
      return(inputs_number);
   }

   /// This method returns the number of hidden layers in the multilayer perceptron. 

   inline int get_hidden_layers_number(void)
   {
      return(hidden_layers_size.get_size());
   }

   /// This method returns a vector containing the numbers of neurons in each hidden layer of the neural network. 

   inline Vector<int>& get_hidden_layers_size(void)
   {
      return(hidden_layers_size);
   }

   /// This method returns a the number of neurons in some hidden layer of the neural network. 
   /// @param i Index of hidden layer.

   inline int get_hidden_layer_size(int i)
   {
      return(hidden_layers_size[i]);
   }

   /// This method returns the number of neurons in the output layer of the neural network.

   inline int get_outputs_number(void)
   {
      return(outputs_number);
   }

   int get_hidden_layer_inputs_number(int);
   int get_output_layer_inputs_number(void);

   Vector< Vector<Perceptron> >& get_hidden_layers(void);
   Vector<Perceptron>& get_hidden_layer(int);

   Vector<Perceptron>& get_output_layer(void);

   // Neural parameters

   int get_neural_parameters_number(void);

   int get_hidden_layers_parameters_number(void);
   int get_hidden_layer_parameters_number(int);

   int get_output_layer_parameters_number(void);

   Vector<double> get_neural_parameters(void);   

   Vector< Vector<double> > get_hidden_layers_biases(void);
   Vector<double> get_hidden_layer_biases(int);

   Vector< Matrix<double> > get_hidden_layers_synaptic_weights(void);
   Matrix<double> get_hidden_layer_synaptic_weights(int);

   Vector< Matrix<double> > get_hidden_layers_parameters(void);
   Matrix<double> get_hidden_layer_parameters(int);

   Vector<double> get_output_layer_biases(void);
   Matrix<double> get_output_layer_synaptic_weights(void);
   Matrix<double> get_output_layer_parameters(void);

   int get_hidden_layer_bias_index(int, int);
   int get_hidden_layer_synaptic_weight_index(int, int, int);

   int get_output_layer_bias_index(int);
   int get_output_layer_synaptic_weight_index(int, int);

   // Activation functions

   Vector<LayerActivationFunction>& get_hidden_layers_activation_function(void);
   Vector<std::string> get_hidden_layers_activation_function_name(void);

   LayerActivationFunction& get_hidden_layer_activation_function(int);
   std::string get_hidden_layer_activation_function_name(int);
   
   LayerActivationFunction& get_output_layer_activation_function(void); 
   std::string get_output_layer_activation_function_name(void);

   // Variables scaling and unscaling

   ScalingMethod& get_inputs_scaling_method(void);
   std::string get_inputs_scaling_method_name(void);

   ScalingMethod& get_outputs_unscaling_method(void);
   std::string get_outputs_unscaling_method_name(void); 

   // Input variables information

   Vector<std::string>& get_input_variables_name(void);
   std::string& get_input_variable_name(int);

   Vector<std::string>& get_input_variables_units(void);
   std::string& get_input_variable_units(int);

   Vector<std::string>& get_input_variables_description(void);
   std::string& get_input_variable_description(int);

   // Output variables information

   Vector<std::string>& get_output_variables_name(void);
   std::string& get_output_variable_name(int);

   Vector<std::string>& get_output_variables_units(void);
   std::string& get_output_variable_units(int);

   Vector<std::string>& get_output_variables_description(void);
   std::string& get_output_variable_description(int);

   // Variables information

   Vector< Vector<std::string>* > get_variables_information(void);
   
   // Input variables statistics

   Vector<double>& get_input_variables_mean(void);
   double get_input_variable_mean(int);

   Vector<double>& get_input_variables_standard_deviation(void);
   double get_input_variable_standard_deviation(int);

   Vector<double>& get_input_variables_minimum(void);
   double get_input_variable_minimum(int);

   Vector<double>& get_input_variables_maximum(void);
   double get_input_variable_maximum(int);

   Vector< Vector<double>* > get_input_variables_mean_standard_deviation(void);
   Vector< Vector<double>* > get_input_variables_minimum_maximum(void);

   // Output variables statistics

   Vector<double>& get_output_variables_mean(void);
   double get_output_variable_mean(int);

   Vector<double>& get_output_variables_standard_deviation(void);
   double get_output_variable_standard_deviation(int);

   Vector<double>& get_output_variables_minimum(void);
   double get_output_variable_minimum(int);

   Vector<double>& get_output_variables_maximum(void);
   double get_output_variable_maximum(int);

   Vector< Vector<double>* > get_output_variables_mean_standard_deviation(void);
   Vector< Vector<double>* > get_output_variables_minimum_maximum(void);

   Vector< Vector<double>* > get_variables_statistics(void);

   // Variables bounds

   Vector<double>& get_output_variables_lower_bound(void);
   double get_output_variables_lower_bound(int);

   Vector<double>& get_output_variables_upper_bound(void);
   double get_output_variable_upper_bound(int);

   Vector< Vector<double>* > get_output_variables_bounds(void);

   // Independent parameters

   /// This method returns the number of parameters independent of the neural network.
   /// Independent parameters can be used in the context of neural netwotks for many purposes.

   inline int get_independent_parameters_number(void)
   {
      return(independent_parameters.get_size());
   }

   Vector<double>& get_independent_parameters(void);   
   double get_independent_parameter(int);   

   // Independent parameters scaling and unscaling

   ScalingMethod& get_independent_parameters_scaling_method(void);
   std::string get_independent_parameters_scaling_method_name(void);

   // Independent parameters information

   Vector<std::string>& get_independent_parameters_name(void);
   std::string& get_independent_parameter_name(int);

   Vector<std::string>& get_independent_parameters_units(void);
   std::string& get_independent_parameter_units(int);

   Vector<std::string>& get_independent_parameters_description(void);
   std::string& get_independent_parameter_description(int);

   Vector< Vector<std::string>* > get_independent_parameters_information(void);     

   // Independent parameters statistics

   Vector<double>& get_independent_parameters_mean(void);
   double get_independent_parameter_mean(int);

   Vector<double>& get_independent_parameters_standard_deviation(void);
   double get_independent_parameter_standard_deviation(int);

   Vector<double>& get_independent_parameters_minimum(void);
   double get_independent_parameter_minimum(int);

   Vector<double>& get_independent_parameters_maximum(void);
   double get_independent_parameter_maximum(int);

   Vector< Vector<double>* > get_independent_parameters_mean_standard_deviation(void);
   Vector< Vector<double>* > get_independent_parameters_minimum_maximum(void);

   Vector< Vector<double>* > get_independent_parameters_statistics(void);

   // Independent parameters bounds

   Vector<double>& get_independent_parameters_lower_bound(void);
   double get_independent_parameter_lower_bound(int);

   Vector<double>& get_independent_parameters_upper_bound(void);
   double get_independent_parameter_upper_bound(int);

   Vector< Vector<double>* > get_independent_parameters_bounds(void);

   // Parameters methods

   int get_parameters_number(void);

   Vector<double> get_parameters(void);      

   // Numerical differentiation

   NumericalDifferentiationMethod& get_numerical_differentiation_method(void);
   std::string get_numerical_differentiation_method_name(void);

   NumericalEpsilonMethod& get_numerical_epsilon_method(void);
   std::string get_numerical_epsilon_method_name(void);

   double get_numerical_epsilon(void);

   // Display messages

   bool get_display_range_out_warning(void);
   bool get_display(void);

   // SET METHODS

   void set(void);
   void set(int, const Vector<int>&, int);
   void set(int, int, int);
   void set(int);
   void set(const char*);
   void set(const MultilayerPerceptron&);

   void set_default(void);

   // Network architecture

   void set_network_architecture(int, const Vector<int>&, int);
   void set_network_architecture(int, int, int);

   void set_hidden_layers_size(const Vector<int>&);
   void set_hidden_layer_size(int);

   // Neural parameters

   void set_neural_parameters(const Vector<double>&);

   void set_hidden_layers_biases(const Vector< Vector<double> >&);
   void set_hidden_layer_biases(int, const Vector<double>&);

   void set_hidden_layers_synaptic_weights(const Vector< Matrix<double> >&);
   void set_hidden_layer_synaptic_weights(int, const Matrix<double>&);

   void set_hidden_layers_parameters(const Vector< Matrix<double> >&);
   void set_hidden_layer_parameters(int, const Matrix<double>&);

   void set_output_layer_biases(const Vector<double>&);
   void set_output_layer_synaptic_weights(const Matrix<double>&);
   void set_output_layer_parameters(const Matrix<double>&);

   // Activation functions

   void set_hidden_layers_activation_function(const Vector<LayerActivationFunction>&);
   void set_hidden_layer_activation_function(int, const LayerActivationFunction&);

   void set_output_layer_activation_function(const LayerActivationFunction&);

   void set_hidden_layers_activation_function(const Vector<std::string>&);
   void set_hidden_layer_activation_function(int, const std::string&);

   void set_output_layer_activation_function(const std::string&);

   // Variables scaling and unscaling

   void set_inputs_scaling_method(const ScalingMethod&);
   void set_outputs_unscaling_method(const ScalingMethod&);

   void set_variables_scaling_method(const ScalingMethod&);

   void set_inputs_scaling_method(const std::string&);
   void set_outputs_unscaling_method(const std::string&);

   // Input variables information

   void set_input_variables_name(const Vector<std::string>&);
   void set_input_variable_name(int, const std::string&);

   void set_input_variables_units(const Vector<std::string>&);
   void set_input_variable_units(int, const std::string&);

   void set_input_variables_description(const Vector<std::string>&);
   void set_input_variable_description(int, const std::string&);

   // Output variables information

   void set_output_variables_name(const Vector<std::string>&);
   void set_output_variable_name(int, const std::string&);

   void set_output_variables_units(const Vector<std::string>&);
   void set_output_variable_units(int, const std::string&);

   void set_output_variables_description(const Vector<std::string>&);
   void set_output_variable_description(int, const std::string&);

   // Variables information

   void set_variables_information(const Vector< Vector<std::string> >&);

   // Input variables statistics

   void set_input_variables_mean(const Vector<double>&);
   void set_input_variable_mean(int, double);

   void set_input_variables_standard_deviation(const Vector<double>&);
   void set_input_variable_standard_deviation(int, double);

   void set_input_variables_minimum(const Vector<double>&);
   void set_input_variable_minimum(int, double);

   void set_input_variables_maximum(const Vector<double>&);
   void set_input_variable_maximum(int, double);

   void set_input_variables_mean_standard_deviation(const Vector< Vector<double> >&);
   void set_input_variables_minimum_maximum(const Vector< Vector<double> >&);

   void set_output_variables_mean(const Vector<double>&);
   void set_output_variable_mean(int, double);

   // Output variables statistics

   void set_output_variables_standard_deviation(const Vector<double>&);
   void set_output_variable_standard_deviation(int, double);

   void set_output_variables_minimum(const Vector<double>&);
   void set_output_variable_minimum(int, double);

   void set_output_variables_maximum(const Vector<double>&);
   void set_output_variable_maximum(int, double);

   void set_output_variables_mean_standard_deviation(const Vector< Vector<double> >&);
   void set_output_variables_minimum_maximum(const Vector< Vector<double> >&);

   // Variables statistics

   void set_variables_statistics(const Vector< Vector<double> >&);

   // Variables bounds

   void set_output_variables_lower_bound(const Vector<double>&);
   void set_output_variable_lower_bound(int, double);

   void set_output_variables_upper_bound(const Vector<double>&);
   void set_output_variable_upper_bound(int, double);

   void set_output_variables_bounds(const Vector< Vector<double> >&);

   // Independent parameters

   void set_independent_parameters_number(int);

   void set_independent_parameters(const Vector<double>&);
   void set_independent_parameter(int, double);

   // Independent parameters scaling and unscaling

   void set_independent_parameters_scaling_method(const ScalingMethod&);
   void set_independent_parameters_scaling_method(const std::string&);

   // Independent parameters information

   void set_independent_parameters_name(const Vector<std::string>&);
   void set_independent_parameter_name(int, const std::string&);

   void set_independent_parameters_units(const Vector<std::string>&);
   void set_independent_parameter_units(int, const std::string&);

   void set_independent_parameters_description(const Vector<std::string>&);
   void set_independent_parameter_description(int, const std::string&);

   // Independent parameters statistics

   void set_independent_parameters_mean(const Vector<double>&);
   void set_independent_parameter_mean(int, double);

   void set_independent_parameters_standard_deviation(const Vector<double>&);
   void set_independent_parameter_standard_deviation(int, double);
   
   void set_independent_parameters_minimum(const Vector<double>&);
   void set_independent_parameter_minimum(int, double);

   void set_independent_parameters_maximum(const Vector<double>&);
   void set_independent_parameter_maximum(int, double);

   void set_independent_parameters_mean_standard_deviation(const Vector< Vector<double> >&);
   void set_independent_parameters_minimum_maximum(const Vector< Vector<double> >&);

   void set_independent_parameters_statistics(const Vector< Vector<double> >&);

   // Independent parameters bounds

   void set_independent_parameters_lower_bound(const Vector<double>&);
   void set_independent_parameter_lower_bound(int, double);

   void set_independent_parameters_upper_bound(const Vector<double>&);
   void set_independent_parameter_upper_bound(int, double);

   void set_independent_parameters_bounds(const Vector< Vector<double> >&);

   // Parameters

   void set_parameters(const Vector<double>&);

   // Variables and independent parameters scaling and unscaling method

   void set_scaling_method(const ScalingMethod&);

   // Numerical differentiation

   void set_numerical_differentiation_method(const NumericalDifferentiationMethod&);
   void set_numerical_differentiation_method(const std::string&);

   void set_numerical_epsilon_method(const NumericalEpsilonMethod&);
   void set_numerical_epsilon_method(const std::string&);

   void set_numerical_epsilon(double);

   // Display messages

   void set_display_range_out_warning(bool);
   void set_display(bool);

   // Neural parameters initialization methods

   void initialize_neural_parameters(double);
   void initialize_biases(double); 
   void initialize_synaptic_weights(double);

   void initialize_neural_parameters_uniform(void);
   void initialize_neural_parameters_uniform(double, double);
   void initialize_neural_parameters_uniform(const Vector<double>&, const Vector<double>&);
   void initialize_neural_parameters_uniform(const Vector< Vector<double> >&);

   void initialize_neural_parameters_normal(void);
   void initialize_neural_parameters_normal(double, double);
   void initialize_neural_parameters_normal(const Vector<double>&, const Vector<double>&);
   void initialize_neural_parameters_normal(const Vector< Vector<double> >&);
 
   // Independent parameters initialization methods

   void initialize_independent_parameters(double);

   void initialize_independent_parameters_uniform(void);
   void initialize_independent_parameters_uniform(double, double);
   void initialize_independent_parameters_uniform(const Vector<double>&, const Vector<double>&);
   void initialize_independent_parameters_uniform(const Vector< Vector<double> >&);

   void initialize_independent_parameters_normal(void);
   void initialize_independent_parameters_normal(double, double);
   void initialize_independent_parameters_normal(const Vector<double>&, const Vector<double>&);
   void initialize_independent_parameters_normal(const Vector< Vector<double> >&);

   // Parameters initialization methods

   void initialize_parameters(double);

   void initialize_parameters_uniform(void);
   void initialize_parameters_uniform(double, double);
   void initialize_parameters_uniform(const Vector<double>&, const Vector<double>&);
   void initialize_parameters_uniform(const Vector< Vector<double> >&);

   void initialize_parameters_normal(void);
   void initialize_parameters_normal(double, double);
   void initialize_parameters_normal(const Vector<double>&, const Vector<double>&);
   void initialize_parameters_normal(const Vector< Vector<double> >&);

   // Parameters norm 

   double calculate_neural_parameters_norm(void);
   double calculate_independent_parameters_norm(void);
   double calculate_parameters_norm(void);

   // Output methods

   Vector<double> calculate_output(const Vector<double>&);
   Matrix<double> calculate_output_matrix(const Matrix<double>&);

   Vector< Vector<double> > calculate_forward_propagation(const Vector<double>&);
   Vector< Vector<double> > calculate_forward_propagation_derivative(const Vector<double>&);
   Vector< Vector<double> > calculate_forward_propagation_second_derivative(const Vector<double>&);

   void check_input_range(const Vector<double>&);

   Vector<double> calculate_scaled_input(const Vector<double>&);

   Vector<double> calculate_hidden_layer_combination(int, const Vector<double>&); 
   Vector<double> calculate_hidden_layer_activation(int, const Vector<double>&);
   Vector<double> calculate_hidden_layer_activation_derivative(int, const Vector<double>&);
   Vector<double> calculate_hidden_layer_activation_second_derivative(int, const Vector<double>&);

   Vector<double> calculate_hidden_layer_output(int, const Vector<double>&);

   Vector<double> calculate_output_layer_combination(const Vector<double>&);
   Vector<double> calculate_output_layer_activation(const Vector<double>&);
   Vector<double> calculate_output_layer_activation_derivative(const Vector<double>&);
   Vector<double> calculate_output_layer_activation_second_derivative(const Vector<double>&);

   Vector<double> calculate_output_layer_output(const Vector<double>&);

   Vector<double> calculate_unscaled_output(const Vector<double>&);
   Vector<double> calculate_bounded_output(const Vector<double>&);

   // Jacobian matrix methods

   Matrix<double> calculate_Jacobian(const Vector<double>&);
   Vector< Matrix<double> > calculate_Jacobian_vector(const Matrix<double>&);

   Matrix<double> calculate_hidden_layer_Jacobian(int, const Vector<double>&);
   Matrix<double> calculate_output_layer_Jacobian(const Vector<double>&);

   Matrix<double> calculate_Jacobian_numerical_differentiation(const Vector<double>&);

   Matrix<double> calculate_Jacobian_forward_differences(const Vector<double>&);
   Matrix<double> calculate_Jacobian_central_differences(const Vector<double>&);

   // Sensitivity matrix methods

   Matrix<double> calculate_sensitivity(const Vector<double>&);
   Vector< Matrix<double> > calculate_sensitivity_vector(const Matrix<double>&);

   Matrix<double> calculate_sensitivity_numerical_differentiation(const Vector<double>&);

   Matrix<double> calculate_sensitivity_forward_differences(const Vector<double>&);
   Matrix<double> calculate_sensitivity_central_differences(const Vector<double>&);

   // Independent parameters methods

   Vector<double> scale_independent_parameters(void);
   void unscale_independent_parameters(const Vector<double>&);

   void bound_independent_parameters(void);
   void bound_independent_parameter(int);

   // Numerical differentiation methods

   double calculate_actual_epsilon(double);
  
   // Expression methods

   std::string get_expression(void);
   
   Vector<std::string> get_inputs_name_expression(void);
   Vector<std::string> get_scaled_inputs_name_expression(void);

   Vector<std::string> get_hidden_layer_inputs_name_expression(int);
   Vector<std::string> get_hidden_layer_outputs_name_expression(int);

   Vector<std::string> get_output_layer_inputs_name_expression(void);

   Vector<std::string> get_scaled_outputs_name_expression(void);
   Vector<std::string> get_outputs_name_expression(void);

   std::string get_hidden_layer_activation_function_expression(int);
   std::string get_output_layer_activation_function_expression(void);

   std::string get_hidden_layer_expression(int);
   std::string get_output_layer_expression(void);

   std::string get_forward_propagation_expression(void);

   std::string get_inputs_scaling_expression(void);
   std::string get_outputs_unscaling_expression(void);

   void save_expression(const char*);

   // Hinton diagram methods

   std::string get_Hinton_diagram(void);
   void save_Hinton_diagram(const char*);

   // Utility methods

   std::string to_XML(bool);

   void print(void);
   void save(const char*);
   void load(const char*);


   // Vector<double> calculate_output(const Vector<double>& input, BoundaryConditionsType& boundary_conditions) method

   /// This method calculates the set of outputs from the neural network in response to a set of inputs, when 
   /// boundary conditions are imposed.
   ///
   /// @param input: Set of inputs to the neural network.
   /// @param boundary_conditions: Boundary conditions given by a set of homogeneous and particular solution terms.
   ///
   /// check_input_range(const Vector<double>&).
   /// calculate_scaled_input(const Vector<double>&).
   /// calculate_hidden_layer_combination(const Vector<double>&).
   /// calculate_hidden_layer_combination(const Vector<double>&).
   /// calculate_hidden_layer_activation_derivative(const Vector<double>&).
   /// calculate_output_layer_combination(const Vector<double>&).
   /// calculate_output_layer_activation(const Vector<double>&).
   /// calculate_output_layer_activation_derivative(const Vector<double>&).
   /// calculate_unscaled_output(const Vector<double>&).

   template<class BoundaryConditionsType> 
   Vector<double> calculate_output(const Vector<double>& input, BoundaryConditionsType& boundary_conditions)
   {      
      // Control sentence (if debug)

      #ifdef _DEBUG 

      int size = input.get_size();

      if(size != inputs_number) 
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "Vector<double> calculate_output(const Vector<double>&, const BoundaryConditionsType&) method." 
                   << std::endl
                   << "Size must be equal to number of inputs." << std::endl;

         exit(1);
      }   

      #endif

      int hidden_layers_number = get_hidden_layers_number();
                     
      check_input_range(input);
 
      // Calculate output

      Vector<double> scaled_input = calculate_scaled_input(input);
  
      Vector< Vector<double> > forward_propagation = calculate_forward_propagation(scaled_input);

      Vector<double> unscaled_output = calculate_unscaled_output(forward_propagation[hidden_layers_number]);

      // Apply boundary conditions

      Vector<double> particular_solution = boundary_conditions.calculate_particular_solution(input);
      Vector<double> homogeneous_solution = boundary_conditions.calculate_homogeneous_solution(input);
      
      Vector<double> boundary_conditions_output = particular_solution + homogeneous_solution*unscaled_output;

      // Apply lower and upper bounds

      Vector<double> bounded_output = calculate_bounded_output(boundary_conditions_output);

      return(bounded_output);
   }


   // Matrix<double> calculate_Jacobian(const Vector<double>&, BoundaryConditionsType&) method

   /// This method returns the the Jacobian matrix of the neural network for a 
   /// set of inputs, corresponding to the point in input space
   /// at which the Jacobian Matrix is to be found.
   /// This method applies when boundary conditions are imposed. 
   /// It uses the back-propagation method. 
   ///
   /// @param input: Set of inputs to the neural network.
   /// @param boundary_conditions: Boundary conditions type.
   ///
   /// @todo this method is implemented only for one input and one or two output variables.
   /// An extension of the algorithm to consider any number of inputs and outputs is required. 

   template<class BoundaryConditionsType> 
   Matrix<double> calculate_Jacobian(const Vector<double>& input, BoundaryConditionsType& boundary_conditions) 
   {
      Vector<double> output = calculate_output(input);
      Matrix<double> Jacobian = calculate_Jacobian(input);

      // Apply boundary conditions

      Vector<double> particular_solution = boundary_conditions.calculate_particular_solution(input);
      Vector<double> homogeneous_solution = boundary_conditions.calculate_homogeneous_solution(input);
      Vector<double> particular_solution_derivative = boundary_conditions.calculate_particular_solution_derivative(input);
      Vector<double> homogeneous_solution_derivative = boundary_conditions.calculate_homogeneous_solution_derivative(input);

      for(int i = 0; i < outputs_number; i++)
      {
         for(int j = 0; j < inputs_number; j++)
         {
            Jacobian[i][j] 
            = particular_solution_derivative[i] 
            + homogeneous_solution_derivative[i]*output[i] 
            + homogeneous_solution[i]*Jacobian[i][j];           
         }
      }

      return(Jacobian);
   }


protected:

   // MEMBERS

   /// Number of network inputs.

   int inputs_number;

   /// Number of neurons in each hidden layer of the neural network.
   /// The size of this vector is the number of hidden layers in the neural network.
   /// The value of each element is the number of neurons in the corresponding layer. 

   Vector<int> hidden_layers_size;

   /// Number of output neurons in the neural network.

   int outputs_number; 

   /// Network's hidden layer. It is built as a vector of vectors of perceptrons.
   /// The size of this vector is equal to the number of hidden layers. 
   /// The size of each subvector is equal to the number of neurons in the corresponding layer.

   Vector< Vector<Perceptron> > hidden_layers;

   /// Network's output layer. It is built as a single vector of perceptrons.
   /// The size of this vector is equal to the number of outputs. 

   Vector<Perceptron> output_layer;

   /// Activation function of the hidden layers.

   Vector<LayerActivationFunction> hidden_layers_activation_function;

   /// Activation function of the output layers.

   LayerActivationFunction output_layer_activation_function;

   /// Scaling method for the input variables.

   ScalingMethod inputs_scaling_method;

   /// Unscaling method for the output variables.

   ScalingMethod outputs_unscaling_method;

   /// Name of input variables.

   Vector<std::string> input_variables_name;

   /// Units of input variables.

   Vector<std::string> input_variables_units;

   /// Description of input variables.

   Vector<std::string> input_variables_description;

   /// Name of output variables.

   Vector<std::string> output_variables_name;

   /// Units of output variables.

   Vector<std::string> output_variables_units;

   /// Description of output variables.

   Vector<std::string> output_variables_description;


   /// Mean of input variables.

   Vector<double> input_variables_mean;

   /// Standard deviation of input variables.

   Vector<double> input_variables_standard_deviation;

   /// Minimum of input variables.

   Vector<double> input_variables_minimum;

   /// Maximum of input variables.

   Vector<double> input_variables_maximum;


   /// Mean of output variables.

   Vector<double> output_variables_mean;

   /// Standard deviation of output variables.

   Vector<double> output_variables_standard_deviation;

   /// Minimum of output variables.

   Vector<double> output_variables_minimum;

   /// Maximum of output variables.

   Vector<double> output_variables_maximum;


   /// Lower bound of output variables

   Vector<double> output_variables_lower_bound;

   /// Upper bound of output variables

   Vector<double> output_variables_upper_bound;


   /// Independent parameters.

   Vector<double> independent_parameters;

   /// Independent parameters scaling and unscaling method.

   ScalingMethod independent_parameters_scaling_method;


   /// Name of independent parameters.

   Vector<std::string> independent_parameters_name;

   /// Units of independent parameters.

   Vector<std::string> independent_parameters_units;

   /// Description of independent parameters.

   Vector<std::string> independent_parameters_description;


   /// Mean of independent parameters.

   Vector<double> independent_parameters_mean;

   /// Standard deviation of independent parameters.

   Vector<double> independent_parameters_standard_deviation;

   /// Minimum of independent parameters.

   Vector<double> independent_parameters_minimum;

   /// Maximum of independent parameters.

   Vector<double> independent_parameters_maximum;


   /// Lower bound of independent parameters.

   Vector<double> independent_parameters_lower_bound;

   /// Upper bound of independent parameters.

   Vector<double> independent_parameters_upper_bound;


   /// Numerical differentiation method variable. 
   /// Numerical differentiation is used for computing the Jacobian matrix and the sensitivity matrix of the 
   /// multilayer perceptron.

   NumericalDifferentiationMethod numerical_differentiation_method;

   /// Numerical epsilon method variable.

   NumericalEpsilonMethod numerical_epsilon_method;
   
   /// Numerical epsilon value. 

   double numerical_epsilon;

   /// Display warning messages when inputs are out of the range defined by minimums and maximums.  

   bool display_range_out_warning;

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
