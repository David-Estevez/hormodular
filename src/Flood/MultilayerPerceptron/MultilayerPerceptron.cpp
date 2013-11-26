/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   M U L T I L A Y E R   P E R C E P T R O N   C L A S S                                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/
 
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>   

#include "MultilayerPerceptron.h"

namespace Flood
{

// GENERAL CONSTRUCTOR

/// General constructor. It creates a multilayer perceptron object with an arbitrary number of hidden layers 
/// and one output layer of perceptrons. The number of independent parameters is set to zero.  
/// The neural parameters are initialized at random. 
/// This constructor also initializes the rest of class members to their default values:
/// <ul>
/// <li> Hidden layers activation function: Hyperbolic tangent.
/// <li> Output layer activation function: Linear.
/// <li> Inputs scaling method: None. 
/// <li> Outputs unscaling method: None. 
/// </ul> 
/// @param new_inputs_number Number of inputs in the neural network.
/// @param new_hidden_layers_size Numbers of neurons in each hidden layer. The number of hidden layers in the 
/// neural network is the size of this vector.
/// @param new_outputs_number Number of output neurons in the neural network.

MultilayerPerceptron::MultilayerPerceptron
(int new_inputs_number, const Vector<int>& new_hidden_layers_size, int new_outputs_number)
{
   // Set network architecture

   set_network_architecture(new_inputs_number, new_hidden_layers_size, new_outputs_number);

   // Initialize number of independent parameters to 0

   set_independent_parameters_number(0);
   
   // Set other default values
   
   set_default();
}

 
// ONE HIDDEN LAYER CONSTRUCTOR

/// One hidden layer constructor. It creates a multilayer perceptron object with a single hidden layer of
/// perceptrons and an output layer of perceptrons. The number of independent parameters is set to zero.  
/// The neural parameters are initialized at random. 
/// This constructor also initializes the rest of class members to their default values:
/// <ul>
/// <li> Hidden layers activation function: Hyperbolic tangent.
/// <li> Output layer activation function: Linear.
/// <li> Inputs scaling method: None. 
/// <li> Outputs unscaling method: None. 
/// </ul> 
/// @param new_inputs_number Number of inputs in the neural network.
/// @param new_hidden_layer_size Number of neurons in the single hidden layer of the neural network.
/// @param new_outputs_number Number of output neurons in the neural network.

MultilayerPerceptron::MultilayerPerceptron(int new_inputs_number, int new_hidden_layer_size, int new_outputs_number)
{
   // Set network architecture

   Vector<int> new_hidden_layers_size(1, new_hidden_layer_size);

   set_network_architecture(new_inputs_number, new_hidden_layers_size, new_outputs_number);

   // Initialize number of independent parameters to 0

   set_independent_parameters_number(0);
   
   // Set other default values
   
   set_default();
}


// INDEPENDENT PARAMETERS CONSTRUCTOR

/// Independent parameters constructor. It creates a multilayer perceptron without network architecture and a given number of independent parameters.
/// The independent parameters are initialized at random. 
/// This constructor also initializes the rest of class members to their default values:
/// <ul>
/// <li> Independent parameters scaling and unscaling method: None. 
/// </ul> 
/// @param new_independent_parameters_number Number of independent parameters associated to the neural network.

MultilayerPerceptron::MultilayerPerceptron(int new_independent_parameters_number)
{
   // Network architecture

   Vector<int> new_hidden_layers_size;

   set_network_architecture(0, new_hidden_layers_size, 0);

   // Independent parameters 

   set_independent_parameters_number(new_independent_parameters_number);
   
   // Set other default values
   
   set_default();
}


// FILE CONSTRUCTOR

/// File constructor. It creates a multilayer perceptron object by loading its members from an XML-type file.
/// Please be careful with the format of that file, which is specified in the user's guide.
/// @param filename Name of multilayer perceptron file.

MultilayerPerceptron::MultilayerPerceptron(const char* filename)
{
   load(filename);
}


// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a multilayer perceptron object with empty network architecture and 
/// zero independent parameters.

MultilayerPerceptron::MultilayerPerceptron(void)
{
   // Network architecture

   Vector<int> new_hidden_layers_size;

   set_network_architecture(0, new_hidden_layers_size, 0);

   // Independent parameters 

   set_independent_parameters_number(0);

   // Set other default values
   
   set_default();
}


// COPY CONSTRUCTOR

/// Copy constructor. It creates a copy of an existing multilayer perceptron object. 
/// @param other_multilayer_perceptron Multilayer perceptron object to be copied.

MultilayerPerceptron::MultilayerPerceptron(const MultilayerPerceptron& other_multilayer_perceptron)
{
   // Network architecture 

   inputs_number = other_multilayer_perceptron.inputs_number;
   hidden_layers_size = other_multilayer_perceptron.hidden_layers_size;
   outputs_number = other_multilayer_perceptron.outputs_number; 

   set_network_architecture(inputs_number, hidden_layers_size, outputs_number);

   hidden_layers_activation_function = other_multilayer_perceptron.hidden_layers_activation_function;
   output_layer_activation_function = other_multilayer_perceptron.output_layer_activation_function;

   hidden_layers = other_multilayer_perceptron.hidden_layers;
   output_layer = other_multilayer_perceptron.output_layer;

   // Variables scaling and unscaling

   inputs_scaling_method = other_multilayer_perceptron.inputs_scaling_method;
   outputs_unscaling_method = other_multilayer_perceptron.outputs_unscaling_method;

   // Variables information

   input_variables_name = other_multilayer_perceptron.input_variables_name;
   output_variables_name = other_multilayer_perceptron.output_variables_name;

   input_variables_units = other_multilayer_perceptron.input_variables_units;
   output_variables_units = other_multilayer_perceptron.output_variables_units;

   input_variables_description = other_multilayer_perceptron.input_variables_description;
   output_variables_description = other_multilayer_perceptron.output_variables_description;

   // Variables statistics

   input_variables_mean = other_multilayer_perceptron.input_variables_mean;
   output_variables_mean = other_multilayer_perceptron.output_variables_mean;

   input_variables_standard_deviation = other_multilayer_perceptron.input_variables_standard_deviation;
   output_variables_standard_deviation = other_multilayer_perceptron.output_variables_standard_deviation;

   input_variables_minimum = other_multilayer_perceptron.input_variables_minimum;
   output_variables_minimum = other_multilayer_perceptron.output_variables_minimum;

   input_variables_maximum = other_multilayer_perceptron.input_variables_maximum;
   output_variables_maximum = other_multilayer_perceptron.output_variables_maximum;

   output_variables_lower_bound = other_multilayer_perceptron.output_variables_lower_bound;
   output_variables_upper_bound = other_multilayer_perceptron.output_variables_upper_bound;

   // Independent parameters

   independent_parameters = other_multilayer_perceptron.independent_parameters;

   // Independent parameters scaling and unscaling

   independent_parameters_scaling_method 
   = other_multilayer_perceptron.independent_parameters_scaling_method;

   // Independent parameters information

   independent_parameters_name = other_multilayer_perceptron.independent_parameters_name;
   independent_parameters_units = other_multilayer_perceptron.independent_parameters_units;
   independent_parameters_description = other_multilayer_perceptron.independent_parameters_description;

   // Independent parameters statistics

   independent_parameters_mean = other_multilayer_perceptron.independent_parameters_mean;
   independent_parameters_standard_deviation = other_multilayer_perceptron.independent_parameters_standard_deviation;

   independent_parameters_minimum = other_multilayer_perceptron.independent_parameters_minimum;
   independent_parameters_maximum = other_multilayer_perceptron.independent_parameters_maximum;

   independent_parameters_lower_bound = other_multilayer_perceptron.independent_parameters_lower_bound;
   independent_parameters_upper_bound = other_multilayer_perceptron.independent_parameters_upper_bound;

   // Numerical differentiation

   numerical_differentiation_method = other_multilayer_perceptron.numerical_differentiation_method;
   numerical_epsilon_method = other_multilayer_perceptron.numerical_epsilon_method;
   numerical_epsilon = other_multilayer_perceptron.numerical_epsilon;

   // Utilities

   display = other_multilayer_perceptron.display;
   display_range_out_warning = other_multilayer_perceptron.display_range_out_warning;
}


// DESTRUCTOR

/// Destructor.

MultilayerPerceptron::~MultilayerPerceptron(void)
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. It assigns to this object the members of an existing multilayer perceptron object.
/// @param other_multilayer_perceptron Multilayer perceptron object to be assigned.

MultilayerPerceptron& MultilayerPerceptron::operator = (const MultilayerPerceptron& other_multilayer_perceptron)
{
   if(this != &other_multilayer_perceptron) 
   {
      // Network architecture 

      inputs_number = other_multilayer_perceptron.inputs_number;
      hidden_layers_size = other_multilayer_perceptron.hidden_layers_size;
      outputs_number = other_multilayer_perceptron.outputs_number; 

      set_network_architecture(inputs_number, hidden_layers_size, outputs_number);

      hidden_layers = other_multilayer_perceptron.hidden_layers;
      output_layer = other_multilayer_perceptron.output_layer;

      hidden_layers_activation_function = other_multilayer_perceptron.hidden_layers_activation_function;
      output_layer_activation_function = other_multilayer_perceptron.output_layer_activation_function;
   
      // Variables scaling and unscaling

      inputs_scaling_method = other_multilayer_perceptron.inputs_scaling_method;
      outputs_unscaling_method = other_multilayer_perceptron.outputs_unscaling_method;

      // Variables information

      input_variables_name = other_multilayer_perceptron.input_variables_name;
      output_variables_name = other_multilayer_perceptron.output_variables_name;

      input_variables_units = other_multilayer_perceptron.input_variables_units;
      output_variables_units = other_multilayer_perceptron.output_variables_units;

      input_variables_description = other_multilayer_perceptron.input_variables_description;
      output_variables_description = other_multilayer_perceptron.output_variables_description;

      // Variables statistics

      input_variables_mean = other_multilayer_perceptron.input_variables_mean;
      output_variables_mean = other_multilayer_perceptron.output_variables_mean;

      input_variables_standard_deviation = other_multilayer_perceptron.input_variables_standard_deviation;
      output_variables_standard_deviation = other_multilayer_perceptron.output_variables_standard_deviation;

      input_variables_minimum = other_multilayer_perceptron.input_variables_minimum;
      output_variables_minimum = other_multilayer_perceptron.output_variables_minimum;

      input_variables_maximum = other_multilayer_perceptron.input_variables_maximum;
      output_variables_maximum = other_multilayer_perceptron.output_variables_maximum;

      output_variables_lower_bound = other_multilayer_perceptron.output_variables_lower_bound;
      output_variables_upper_bound = other_multilayer_perceptron.output_variables_upper_bound;

      // Independent parameters

      independent_parameters = other_multilayer_perceptron.independent_parameters;

      // Independent parameters scaling and unscaling

      independent_parameters_scaling_method 
      = other_multilayer_perceptron.independent_parameters_scaling_method;
   
      // Independent parameters information

      independent_parameters_name = other_multilayer_perceptron.independent_parameters_name;
      independent_parameters_units = other_multilayer_perceptron.independent_parameters_units;
      independent_parameters_description = other_multilayer_perceptron.independent_parameters_description;

      // Independent parameters statistics

      independent_parameters_mean = other_multilayer_perceptron.independent_parameters_mean;
      independent_parameters_standard_deviation = other_multilayer_perceptron.independent_parameters_standard_deviation;

      independent_parameters_minimum = other_multilayer_perceptron.independent_parameters_minimum;
      independent_parameters_maximum = other_multilayer_perceptron.independent_parameters_maximum;

      independent_parameters_lower_bound = other_multilayer_perceptron.independent_parameters_lower_bound;
      independent_parameters_upper_bound = other_multilayer_perceptron.independent_parameters_upper_bound;

      // Numerical differentiation

      numerical_differentiation_method = other_multilayer_perceptron.numerical_differentiation_method;
      numerical_epsilon_method = other_multilayer_perceptron.numerical_epsilon_method;
      numerical_epsilon = other_multilayer_perceptron.numerical_epsilon;

      // Utilities

      display = other_multilayer_perceptron.display;
      display_range_out_warning = other_multilayer_perceptron.display_range_out_warning;
   }

   return(*this);
}


// METHODS

// Vector< Vector<Perceptron> >& get_hidden_layers(void) method

/// This method returns the hidden layers of the neural network. 
/// The format is a reference to the vector of vectors of hidden perceptrons.
/// Note that each hidden layer might have a different size.

Vector <Vector<Perceptron> >& MultilayerPerceptron::get_hidden_layers(void)
{
   return(hidden_layers);
}


// Vector<Perceptron>& get_hidden_layer(int) method

/// This method returns a reference to the vector of perceptrons in a single hidden layer.
/// @param i Index of hidden layer.

Vector<Perceptron>& MultilayerPerceptron::get_hidden_layer(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<Perceptron>& get_hidden_layer(int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif
 
   return(hidden_layers[i]);
}


// Vector<Perceptron>& get_output_layer(void) method

/// This method returns a reference to the vector of output perceptrons. 

Vector<Perceptron>& MultilayerPerceptron::get_output_layer(void)
{
   return(output_layer);
}


// int get_hidden_layer_inputs_number(int) method

/// This method returns the number of inputs to some hidden layer.
/// @param i Index of hidden layer. 

int MultilayerPerceptron::get_hidden_layer_inputs_number(int i)
{
   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_inputs_number(int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_inputs_number; 

   if(i == 0)
   {
      hidden_layer_inputs_number = inputs_number;
   }
   else
   {
      hidden_layer_inputs_number = hidden_layers_size[i-1];   
   }

   return(hidden_layer_inputs_number);
}


// int get_output_layer_inputs_number(void) method

/// This method returns the number of inputs to the output layer.

int MultilayerPerceptron::get_output_layer_inputs_number(void)
{
   int hidden_layers_number = get_hidden_layers_number();

   int output_layer_outputs_number = hidden_layers_size[hidden_layers_number-1];

   return(output_layer_outputs_number);
}


// int get_hidden_layers_parameters_number(void) method

/// This method returns the number of neural parameters (biases and synaptic weights) of all the hidden layers.

int MultilayerPerceptron::get_hidden_layers_parameters_number(void)
{
   int hidden_layers_parameters_number = 0;

   int hidden_layers_number = get_hidden_layers_number();

   for(int i = 0; i < hidden_layers_number; i++)
   {
      for(int j = 0; j < hidden_layers_size[i]; j++)
      {
         hidden_layers_parameters_number += hidden_layers[i][j].get_parameters_number();
      }
   }

   return(hidden_layers_parameters_number);
}


// int get_hidden_layer_parameters_number(int) method

/// This method returns the number of neural parameters (biases and synaptic weights) of a single hidden layer.
/// @param i Index of hidden layer.

int MultilayerPerceptron::get_hidden_layer_parameters_number(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_parameters_number(int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_parameters_number = 0;

   for(int j = 0; j < hidden_layers_size[i]; j++)
   {
      hidden_layer_parameters_number += hidden_layers[i][j].get_parameters_number();
   }

   return(hidden_layer_parameters_number);
}


// int get_output_layer_parameters_number(void) method

/// This method returns the number of neural parameters (biases and synaptic weights) of the output layer.

int MultilayerPerceptron::get_output_layer_parameters_number(void)
{
   int output_layer_parameters_number = 0;

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer_parameters_number += output_layer[i].get_parameters_number();
   }

   return(output_layer_parameters_number);
}


// int get_neural_parameters_number(void) method

/// This method returns the number neural parameters (biases and synaptic weights) in the neural network. 

int MultilayerPerceptron::get_neural_parameters_number(void)
{
   int hidden_layers_parameters_number = get_hidden_layers_parameters_number();

   int output_layer_parameters_number = get_output_layer_parameters_number();

   int neural_parameters_number = hidden_layers_parameters_number + output_layer_parameters_number;

   return(neural_parameters_number);
}


// Vector< Vector<double> > get_hidden_layers_biases(void) method

/// This method returns the bias values from the neurons in all the hidden layers. 
/// The format is a vector of vectors of real values. 
/// The size of this vector is the number of hidden layers.
/// The size of each subvector is the number of neurons in the corresponding hidden layer. 

Vector< Vector<double> > MultilayerPerceptron::get_hidden_layers_biases(void)
{
   int hidden_layers_number = get_hidden_layers_number();

   Vector< Vector<double> > hidden_layers_biases(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
      hidden_layers_biases[i] = get_hidden_layer_biases(i);
   }

   return(hidden_layers_biases);
}


// Vector<double> get_hidden_layer_biases(int) method

/// This method returns the bias values from the neurons of a single hidden layer. 
/// The format is a vector of real values. 
/// The size of this vector is the number of neurons in that hidden layer.
/// @param i Index of hidden layer.

Vector<double> MultilayerPerceptron::get_hidden_layer_biases(int i)
{   
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> get_hidden_layer_biases(int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_size = hidden_layers_size[i];  

   Vector<double> hidden_layer_biases(hidden_layer_size);

   for(int i = 0; i < hidden_layer_size; i++)
   {
      hidden_layer_biases[i] = hidden_layers[i][i].get_bias();
   }

   return(hidden_layer_biases);
}


// Vector< Matrix<double> > get_hidden_layers_synaptic_weights(void) method

/// This method returns the synaptic weight values from the neurons in all the hidden layers. 
/// The format is a vector of matrices of real values. 
/// The size of this vector is the number of hidden layers.
/// The number of rows of each submatrix is the number of neurons in the corresponding hidden layer. 
/// The number of columns of each submatrix is the number of inputs to the corresponding hidden layer. 

Vector< Matrix<double> > MultilayerPerceptron::get_hidden_layers_synaptic_weights(void)
{
   int hidden_layers_number = get_hidden_layers_number();

   Vector< Matrix<double> > hidden_layers_synaptic_weights(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
      hidden_layers_synaptic_weights[i] = get_hidden_layer_synaptic_weights(i);   
   }

   return(hidden_layers_synaptic_weights);
}


// Matrix<double> get_hidden_layer_synaptic_weights(int) method

/// This method returns the synaptic weights values from the neurons of a single hidden layer. 
/// The format is a matrix of real values. 
/// The number of rows is the number of neurons in that hidden layer. 
/// The number of columns is the number of inputs to that hidden layer. 
/// @param i Index of hidden layer.

Matrix<double> MultilayerPerceptron::get_hidden_layer_synaptic_weights(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Matrix<double> get_hidden_layer_synaptic_weights(int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_size = hidden_layers_size[i]; 

   int hidden_layer_inputs_number = get_hidden_layer_inputs_number(i); 

   Matrix<double> hidden_layer_synaptic_weights(hidden_layer_size, hidden_layer_inputs_number);

   Vector<double> synaptic_weights(hidden_layer_inputs_number);

   for(int i = 0; i < hidden_layer_size; i++)
   {
      synaptic_weights = hidden_layers[i][i].get_synaptic_weights();

      hidden_layer_synaptic_weights.set_row(i, synaptic_weights);
   }

   return(hidden_layer_synaptic_weights);
}


// Vector< Matrix<double> > get_hidden_layers_paramters(void) method

/// This method returns the neural parameter values (biases and synaptic weights) from the neurons in all 
/// the hidden layers. 
/// The format is a vector of matrices of real values. 
/// The size of this vector is the number of hidden layers.
/// The number of rows of each submatrix is the number of neurons in the corresponding hidden layer. 
/// The number of columns of each submatrix is the number of parameters (inputs + 1) to the corresponding hidden layer. 

Vector< Matrix<double> > MultilayerPerceptron::get_hidden_layers_parameters(void)
{
   int hidden_layers_number = get_hidden_layers_number();

   Vector< Matrix<double> > hidden_layers_parameters(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
      hidden_layers_parameters[i] = get_hidden_layer_parameters(i);   
   }

   return(hidden_layers_parameters);
}


// Matrix<double> get_hidden_layer_parameters(int) method

/// This method returns the synaptic weights values from the neurons of a single hidden layer. 
/// The format is a matrix of real values. 
/// The number of rows is the number of neurons in that hidden layer. 
/// The number of columns is the number of inputs to that hidden layer. 
/// @param i Index of hidden layer.

Matrix<double> MultilayerPerceptron::get_hidden_layer_parameters(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Matrix<double> get_hidden_layer_parameters(int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_size = hidden_layers_size[i]; 

   int hidden_layer_parameters_number = get_hidden_layer_inputs_number(i) + 1; 

   Matrix<double> hidden_layer_parameters(hidden_layer_size, hidden_layer_parameters_number);

   Vector<double> neuron_parameters(hidden_layer_parameters_number);

   for(int i = 0; i < hidden_layer_size; i++)
   {
      neuron_parameters = hidden_layers[i][i].get_parameters();

      hidden_layer_parameters.set_row(i, neuron_parameters);
   }

   return(hidden_layer_parameters);
}


// Vector<double> get_output_layer_biases(void) method

/// This method returns the bias values from the output neurons. 
/// The format is a vector of real values. 
/// The size of this vector is the number of outputs of the neural network.

Vector<double> MultilayerPerceptron::get_output_layer_biases(void)
{
   Vector<double> outputLayerBiases(outputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      outputLayerBiases[i] = output_layer[i].get_bias();
   }

   return(outputLayerBiases);
}


// Matrix<double> get_output_layer_synaptic_weights(void) method

/// This method returns the synaptic weight values from the output neurons. 
/// The format is a matrix of real values. 
/// The number of rows is the number of outputs. 
/// The number of columns is the number of inputs to the output layer. 

Matrix<double> MultilayerPerceptron::get_output_layer_synaptic_weights(void)
{
   int hidden_layers_number = hidden_layers.get_size();

   int output_layer_inputs_number = hidden_layers_size[hidden_layers_number-1];

   Matrix<double> output_layer_synaptic_weights(outputs_number, output_layer_inputs_number);

   Vector<double> synaptic_weights(output_layer_inputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      synaptic_weights = output_layer[i].get_synaptic_weights();

      output_layer_synaptic_weights.set_row(i, synaptic_weights);
   }

   return(output_layer_synaptic_weights);
}


// Matrix<double> get_output_layer_parameters(void) method

/// This method returns the neural parameters values (biases and synaptic weight) of the output neurons. 
/// The format is a matrix of real values. 
/// The number of rows is the number of outputs. 
/// The number of columns is the number of inputs to the output layer plus one. 

Matrix<double> MultilayerPerceptron::get_output_layer_parameters(void)
{
   int output_layer_inputs_number = get_output_layer_inputs_number();

   Matrix<double> output_layer_parameters(outputs_number, 1+output_layer_inputs_number);

   Vector<double> neuron_parameters(1+output_layer_inputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      neuron_parameters = output_layer[i].get_parameters();

      output_layer_parameters.set_row(i, neuron_parameters);
   }

   return(output_layer_parameters);
}


// Vector<double> get_neural_parameters(void) method

/// This method returns the values of all the biases and synaptic weights in the neural network as a single vector.

Vector<double> MultilayerPerceptron::get_neural_parameters(void)
{
   int hidden_layers_number = get_hidden_layers_number();

   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   double bias;
   int synaptic_weights_number;

   // Hidden layers parameters

   int position = 0;

   for(int i = 0; i < hidden_layers_number; i++)
   {
      for(int j = 0; j < hidden_layers_size[i]; j++)
      {
         // Bias 

         bias = hidden_layers[i][j].get_bias();
         neural_parameters[position] = bias;
         position++;

    	   // Synaptic weights

         Vector<double>& synaptic_weights = hidden_layers[i][j].get_synaptic_weights();
         synaptic_weights_number = hidden_layers[i][j].get_inputs_number();
         neural_parameters.insert(position, synaptic_weights);
         position += synaptic_weights_number; 
      }
   }

   // Output layer parameters

   for(int i = 0; i < outputs_number; i++)
   {
      // Bias

      bias = output_layer[i].get_bias();
      neural_parameters[position] = bias;
      position++;

      // Synaptic weights

      Vector<double>& synaptic_weights = output_layer[i].get_synaptic_weights();
      synaptic_weights_number = output_layer[i].get_inputs_number();
      neural_parameters.insert(position, synaptic_weights);       
      position += synaptic_weights_number; 
   }

   return(neural_parameters);
}


// int get_hidden_layer_bias_index(int, int) method

/// This method returns the index in the vector of parameters of a bias in a hidden layer. 
/// @param i Index of hidden layer.
/// @param hidden_neuron_index Index of hidden neuron.

int MultilayerPerceptron::get_hidden_layer_bias_index(int hidden_layer_index, int hidden_neuron_index)
{  
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(hidden_layer_index < 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_bias_index(int, int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero." << std::endl;

      exit(1);
   }

   int hidden_layers_number = get_hidden_layers_number();

   if(hidden_layer_index >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_bias_index(int, int) method." << std::endl
                << "Index of hidden layer must be less than number of hidden layers." << std::endl;

      exit(1);
   }

   if(hidden_neuron_index < 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_bias_index(int, int) method." << std::endl
                << "Index of hidden neuron must be equal or greater than zero." << std::endl;

      exit(1);
   }

   int hidden_layer_size = hidden_layers_size[hidden_layer_index];
   
   if(hidden_neuron_index >= hidden_layer_size)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_bias_index(int, int) method." << std::endl
                << "Index of hidden neuron must be less than size of hidden layer." << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_bias_index = 0;

   // Previous hidden layers

   for(int i = 0; i < hidden_layer_index; i++)
   {
      hidden_layer_bias_index += get_hidden_layer_parameters_number(i);
   }

   // Previous hidden layer neurons

   for(int j = 0; j < hidden_neuron_index; j++)
   {
      hidden_layer_bias_index += hidden_layers[hidden_layer_index][j].get_parameters_number();
   }

   return(hidden_layer_bias_index);
}


// int get_hidden_layer_synaptic_weight_index(int, int, int) method

/// This method returns the index in the vector of parameters of a synaptic weight in a hidden layer. 
/// @param i Index of hidden layer.
/// @param hidden_neuron_index Index of hidden neuron.
/// @param hidden_neuron_input_index Index of input to hidden neuron.

int MultilayerPerceptron::get_hidden_layer_synaptic_weight_index
(int hidden_layer_index, int hidden_neuron_index, int hidden_neuron_input_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(hidden_layer_index < 0 || hidden_layer_index >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_bias_index(int, int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   if(hidden_neuron_index < 0 || hidden_neuron_index >= hidden_layers_size[hidden_layer_index])
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_bias_index(int, int) method." << std::endl
                << "Index of hidden neuron must be equal or greater than zero and less than size of hidden layer." 
                << std::endl;

      exit(1);
   }

   int hidden_layer_inputs_number = get_hidden_layer_inputs_number(hidden_layer_index);

   if(hidden_neuron_input_index < 0 || hidden_neuron_input_index >= hidden_layer_inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "int get_hidden_layer_bias_index(int, int) method." << std::endl
                << "Index of hidden neuron must be equal or greater than zero and less than size of hidden layer." 
                << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_synaptic_weight_index = 0;

   // Previous hidden layers

   for(int i = 0; i < hidden_layer_index-1; i++)
   {
      hidden_layer_synaptic_weight_index += get_hidden_layer_parameters_number(hidden_layer_index);
   }

   // Previous hidden layer neurons

   for(int i = 0; i < hidden_neuron_index-1; i++)
   {
      hidden_layer_synaptic_weight_index += hidden_layers[hidden_layer_index][i].get_parameters_number();
   }

   // Hidden neuron bias

   hidden_layer_synaptic_weight_index += 1;

   // Synaptic weight index

   hidden_layer_synaptic_weight_index += hidden_neuron_input_index;

   return(hidden_layer_synaptic_weight_index);
}


// int get_output_layer_bias_index(int) method

/// This method returns the index in the vector of parameters of a bias in the layer. 
/// @param output_neuron_index Index of output neuron.

int MultilayerPerceptron::get_output_layer_bias_index(int output_neuron_index)
{
   int output_layer_bias_index = 0; 

   // All hidden layers

   output_layer_bias_index += get_hidden_layers_parameters_number();

   // Previous output neurons

   for(int i = 0; i < output_neuron_index-1; i++)
   {
      output_layer_bias_index += output_layer[i].get_parameters_number();
   }

   // Bias index

   output_layer_bias_index += 1;

   return(output_layer_bias_index);
}


// int get_output_layer_synaptic_weight_index(int, int) method

/// This method returns the index in the vector of parameters of a synaptic weight in the output layer. 
/// @param output_neuron_index Index of output neuron.
/// @param output_neuron_input_index Index of input to output neuron.

int MultilayerPerceptron::
get_output_layer_synaptic_weight_index(int output_neuron_index, int output_neuron_input_index)
{
	int output_layer_synaptic_weight_index = 0; 

   // All hidden layers

   output_layer_synaptic_weight_index += get_hidden_layers_parameters_number();

   // Previous output neurons

   for(int i = 0; i < output_neuron_index-1; i++)
   {
      output_layer_synaptic_weight_index += output_layer[i].get_parameters_number();
   }

   // Output neuron bias

   output_layer_synaptic_weight_index += 1;

   // Synatpic weight index

   output_layer_synaptic_weight_index += output_neuron_input_index;

   return(output_layer_synaptic_weight_index);
}


// Vector<LayerActivationFunction>& get_hidden_layers_activation_function(void) method

/// This method returns the activation function of every hidden layer in a single vector. 

Vector<MultilayerPerceptron::LayerActivationFunction>& 
MultilayerPerceptron::get_hidden_layers_activation_function(void)
{
   return(hidden_layers_activation_function);
}
   

// LayerActivationFunction get_hidden_layer_activation_function(int) method

/// This method returns the activation function of a single hidden layer. 
/// @param i Index of hidden layer.

MultilayerPerceptron::LayerActivationFunction& 
MultilayerPerceptron::get_hidden_layer_activation_function(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "LayerActivationFunction& get_hidden_layer_activation_function(int) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   return(hidden_layers_activation_function[i]);
}


// OutputLayerActivationFunction get_output_layer_activation_function(void) method

/// This method returns the activation function of the perceptron neurons of the output layer. 

MultilayerPerceptron::LayerActivationFunction& MultilayerPerceptron::get_output_layer_activation_function(void)
{
   return(output_layer_activation_function);
}


// Vector<std::string> get_hidden_layers_activation_function_name(void) method

/// This method returns a vector of strings with the name of the activation functions for the hidden layers. 
/// The size of this vector is the number of hidden layers. 

Vector<std::string> MultilayerPerceptron::get_hidden_layers_activation_function_name(void)
{
   int hidden_layers_number = get_hidden_layers_number();

   Vector<std::string> hidden_layers_activation_function_name(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
	  hidden_layers_activation_function_name[i] = get_hidden_layer_activation_function_name(i);
   }

   return(hidden_layers_activation_function_name);
}









// std::string get_hidden_layer_activation_function_name(int) method

/// This method returns a strings with the name of the activation functions of a single hidden layer. 
/// @param i hidden_layer_index Index of hidden layer

std::string MultilayerPerceptron::get_hidden_layer_activation_function_name(int hidden_layer_index)
{
   switch(hidden_layers_activation_function[hidden_layer_index])
   {
      case Logistic:
      {
         return("Logistic");
      }
      break;

      case HyperbolicTangent:
      {
         return("HyperbolicTangent");
      }
      break;

      case Threshold:
      {
         return("Threshold");
      }
      break;

      case SymmetricThreshold:
      {
         return("SymmetricThreshold");
      }
      break;

      case Linear:
      {
         return("Linear");
      }
      break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "std::string get_hidden_layer_activation_function(int) method." << std::endl
                   << "Unknown hidden layer activation function." << std::endl;
 
          exit(1);
      }
      break;
   }
}


// std::string get_output_layer_activation_function_name(void) method

/// This method returns a strings with the name of the activation functions of the output layer. 

std::string MultilayerPerceptron::get_output_layer_activation_function_name(void)
{
   switch(output_layer_activation_function)
   {
      case Logistic:
      {
         return("Logistic");
      }
      break;

      case HyperbolicTangent:
      {
         return("HyperbolicTangent");
      }
      break;

      case Threshold:
      {
         return("Threshold");
      }
      break;

      case SymmetricThreshold:
      {
         return("SymmetricThreshold");
      }
      break;

      case Linear:
      {
         return("Linear");
      }
      break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "std::string& get_output_layer_activation_function(void) method." << std::endl
                   << "Unknown output layer activation function." << std::endl;
 
          exit(1);
      }
      break;
   }
}


// ScalingMethod& get_inputs_scaling_method(void) method

/// This method returns the method used for scaling the neural network inputs.

MultilayerPerceptron::ScalingMethod& MultilayerPerceptron::get_inputs_scaling_method(void)
{
   return(inputs_scaling_method);
}


// std::string get_inputs_scaling_method_name(void) method

/// This method returns a string with the name of the method used for scaling the neural network inputs. 

std::string MultilayerPerceptron::get_inputs_scaling_method_name(void)
{
   if(inputs_scaling_method == None)
   {
      return("None");
   }
   else if(inputs_scaling_method == MeanStandardDeviation)
   {
      return("MeanStandardDeviation");
   }
   else if(inputs_scaling_method == MinimumMaximum)
   {
      return("MinimumMaximum");
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "std::string get_inputs_scaling_method(void) method." << std::endl
                << "Unknown inputs scaling method." << std::endl;
 
      exit(1);
   }
}


// ScalingMethod& get_outputs_unscaling_method(void) method

/// This method returns the method used for unscaling the neural network outputs.

MultilayerPerceptron::ScalingMethod& MultilayerPerceptron::get_outputs_unscaling_method(void)
{
   return(outputs_unscaling_method);
}


// std::string get_outputs_unscaling_method_name(void) method

/// This method returns a string with the name of the method used for unscaling the neural network outputs. 

std::string MultilayerPerceptron::get_outputs_unscaling_method_name(void)
{
   if(outputs_unscaling_method == None)
   {
      return("None");
   }
   else if(outputs_unscaling_method == MeanStandardDeviation)
   {
      return("MeanStandardDeviation");
   }
   else if(outputs_unscaling_method == MinimumMaximum)
   {
      return("MinimumMaximum");
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "std::string get_outputs_unscaling_method(void) method." << std::endl
                << "Unknown outputs unscaling method." << std::endl;
 
      exit(1);
   }
}


// Vector<std::string>& get_input_variables_name(void) method

/// This method returns the names of the input variables of the neural network. 
/// Such names are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_input_variables_name(void)
{
   return(input_variables_name);
}


// std::string get_input_variable_name(int) method

/// This method returns the name of a single input variable of the neural network. 
/// Such a name is only used to give the user basic information about the problem at hand.
/// @param input_variable_index Index of input variable.

std::string& MultilayerPerceptron::get_input_variable_name(int input_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "std::string get_input_variable_name(int) method." << std::endl
                << "Input variable index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "std::string get_input_variable_name(int) method." << std::endl
                << "Input variable index must be less than number of inputs." << std::endl;

      exit(1);
   }

   if(input_variables_name.get_size() == 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "std::string get_input_variable_name(int) method." << std::endl
                << "Input variables size is zero." << std::endl;

      exit(1);   
   }

   #endif

   return(input_variables_name[input_variable_index]);
}


// Vector<std::string>& get_output_variables_name(void) method

/// This method returns the names of the output variables of the neural network.
/// Such names are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_output_variables_name(void)
{
   return(output_variables_name);
}


// std::string get_output_variable_name(int) method

/// This method returns the name of a single output variable of the neural network. 
/// Such a name is only used to give the user basic information about the problem at hand.
/// @param output_variable_index Index of output variable.

std::string& MultilayerPerceptron::get_output_variable_name(int output_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl  
                << "std::string get_output_variable_name(int) method." << std::endl
                << "Output variable index must be equal or greater than zero and less than number of outputs." 
                << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_name[output_variable_index]);
}


// Vector<std::string>& get_input_variables_units(void) method

/// This method returns the units of the input variables of the neural network as strings. 
/// Such units are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_input_variables_units(void)
{
   return(input_variables_units);
}


// std::string get_input_variable_units(int) method

/// This method returns the units of a single input variable as a string. 

/// Such units are only used to give the user basic information about the problem at hand.
/// @param input_variable_index Index of input variable.

std::string& MultilayerPerceptron::get_input_variable_units(int input_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "std::string get_input_variable_units(int) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." << std::endl;

      exit(1);
   }

   #endif

   return(input_variables_units[input_variable_index]);
}


// Vector<std::string>& get_output_variables_units(void) method

/// This method returns the units of the output variables of the neural network as strings. 
/// Such units are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_output_variables_units(void)
{
   return(output_variables_units);
}


// std::string get_output_variable_units(int) method

/// This method returns the units of a single output variable as a string. 
/// Such units are only used to give the user basic information about the problem at hand.
/// @param output_variable_index Index of output variable.

std::string& MultilayerPerceptron::get_output_variable_units(int output_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "std::string get_output_variable_units(int) method." << std::endl
                << "Index of output variable must be equal or greater than zero and less than number of outputs."
                << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_units[output_variable_index]);
}


// Vector<std::string>& get_input_variables_description(void) method

/// This method returns the description of the input variables of the neural network as strings. 
/// Such descriptions are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_input_variables_description(void)
{
   return(input_variables_description);
}


// std::string get_input_variable_description(int) method

/// This method returns the description of a single input variable as a string. 
/// Such a description is only used to give the user basic information about the problem at hand.
/// @param input_variable_index Index of input variable.

std::string& MultilayerPerceptron::get_input_variable_description(int input_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "std::string get_input_variable_description(int) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   return(input_variables_description[input_variable_index]);
}


// Vector<std::string>& get_output_variables_description(void) method

/// This method returns the description of the output variables of the neural network as strings. 
/// Such descriptions are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_output_variables_description(void)
{
   return(output_variables_description);
}


// std::string get_output_variable_description(int) method

/// This method returns the description of a single input variable as a string. 
/// Such a description is only used to give the user basic information about the problem at hand.


/// @param output_variable_index Index of output variable.

std::string& MultilayerPerceptron::get_output_variable_description(int output_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "std::string get_output_variable_description(int) method." << std::endl
                << "Index of output variable must be less than number of outputs."
                << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_description[output_variable_index]);
}


// Vector< Vector<std::string> > get_variables_information(void) method

/// This method returns all the available information about the input and output variables. 
/// The format is a vector of pointers to vectors of size six: 
/// <ul>
/// <li> Name of input variables.
/// <li> Name of output variables.
/// <li> Units of input variables.
/// <li> Units of output variables.
/// <li> Description of input variables.
/// <li> Description of output variables.
/// </ul>

Vector< Vector<std::string>* > MultilayerPerceptron::get_variables_information(void)
{
   Vector< Vector<std::string>* > variables_information(6);
 
   variables_information[0] = &input_variables_name;
   variables_information[1] = &output_variables_name;

   variables_information[2] = &input_variables_units;
   variables_information[3] = &output_variables_units;

   variables_information[4] = &input_variables_description;
   variables_information[5] = &output_variables_description;

   return(variables_information);
}


// Vector<double>& get_input_variables_mean(void) method

/// This method returns the mean values of all the input variables of the neural network.
/// Such values are to be used for scaling inputs with the mean and standard deviation method. 

Vector<double>& MultilayerPerceptron::get_input_variables_mean(void)
{
   return(input_variables_mean);
}


// double get_input_variable_mean(int) method

/// This method returns the mean value of a single input variable of the neural network.
/// Such a value is to be used for scaling that input with the mean and standard deviation method. 
/// @param input_variable_index Index of input variable.

double MultilayerPerceptron::get_input_variable_mean(int input_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_input_variable_mean(int) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   return(input_variables_mean[input_variable_index]);
}


// Vector<double>& get_output_variables_mean(void)

/// This method returns the mean values of all the output variables of the neural network.
/// Such values are to be used for unscaling the output with the mean and standard deviation method. 

Vector<double>& MultilayerPerceptron::get_output_variables_mean(void)
{
   return(output_variables_mean);
}


// double get_output_variable_mean(int) method

/// This method returns the mean values of a single input variable of the neural network.
/// Such a values is to be used for scaling inputs and unscaling outputs with the mean and 
/// standard deviation method. 
/// @param output_variable_index Index of output variable.

double MultilayerPerceptron::get_output_variable_mean(int output_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_mean(int) method." << std::endl

                << "Index must be less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_mean[output_variable_index]);
}


// Vector<double>& get_input_variables_standard_deviation(void) method

/// This method returns the standard deviation values of all the input variables of the neural network.
/// Such values are to be used for scaling inputs with the mean and standard deviation method. 

Vector<double>& MultilayerPerceptron::get_input_variables_standard_deviation(void)
{
   return(input_variables_standard_deviation);
}


// double get_input_variable_standard_deviation(int) method

/// This method returns the standard deviation value of a single input variable of the neural network.
/// Such a value is to be used for scaling that input with the mean and standard deviation method. 
/// @param input_variable_index Index of input variable.

double MultilayerPerceptron::get_input_variable_standard_deviation(int input_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_input_variable_standard_deviation(int) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   return(input_variables_standard_deviation[input_variable_index]);
}


// Vector<double>& get_output_variables_standard_deviation(void)

/// This method returns the standard deviation values of all the output variables of the neural network.
/// Such values are to be used for unscaling outputs with the mean and standard deviation method. 

Vector<double>& MultilayerPerceptron::get_output_variables_standard_deviation(void)
{
   return(output_variables_standard_deviation);
}


// double get_output_variable_standard_deviation(int) method

/// This method returns the standard deviation value of a single output variable of the neural network.
/// Such a value is to be used for unscaling outputs with the mean and standard deviation method. 
/// @param output_variable_index Index of output variable.

double MultilayerPerceptron::get_output_variable_standard_deviation(int output_variable_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_standard_deviation(int) method." << std::endl
                << "Index of output variable must be equal or greater than zero and less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_standard_deviation[output_variable_index]);
}


// Vector< Vector<double>* > get_input_variables_mean_standard_deviation(void) method

/// This method returns the mean and the standard deviation values of all the input variables. 
/// The format is a vector of pointers to vectors of size two. 
/// The first element contains the mean values of the input variables.
/// The second element contains the standard deviation values of the input variables.
/// Such values are to be used for scaling inputs with the mean and standard deviation method. 

Vector< Vector<double>* > MultilayerPerceptron::get_input_variables_mean_standard_deviation(void)
{
   Vector< Vector<double>* > input_variables_mean_standard_deviation(2);

   input_variables_mean_standard_deviation[0] = &input_variables_mean;
   input_variables_mean_standard_deviation[1] = &input_variables_standard_deviation;

   return(input_variables_mean_standard_deviation);
}


// Vector< Vector<double>* > get_output_variables_mean_standard_deviation(void) method

/// This method returns the mean and the standard deviation values of all the output variables. 
/// The format is a vector of pointers to vectors of size two. 
/// The first element contains the mean values of the output variables.
/// The second element contains the standard deviation values of the output variables.
/// Such values are to be used for unscaling outputs with the mean and standard deviation method. 

Vector< Vector<double>* > MultilayerPerceptron::get_output_variables_mean_standard_deviation(void)
{
   Vector< Vector<double>* > output_variables_mean_standard_deviation(2);

   output_variables_mean_standard_deviation[0] = &output_variables_mean;       
   output_variables_mean_standard_deviation[1] = &output_variables_standard_deviation;

   return(output_variables_mean_standard_deviation);
}


// Vector<double> get_input_variables_minimum(void) method

/// This method returns the minimum values of all the input variables in the neural network.
/// Such values are to be used for scaling inputs with the minimum and maximum method.

Vector<double>& MultilayerPerceptron::get_input_variables_minimum(void)
{
   return(input_variables_minimum);               
}


// double get_input_variable_minimum(int) method

/// This method returns the minimum value of a single input variable in the neural network.
/// Such value is to be used for scaling that input with the minimum and maximum method.

double MultilayerPerceptron::get_input_variable_minimum(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(inputs_number == 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_input_variable_minimum(int) method." << std::endl
                << "Number of inputs is zero." << std::endl;

      exit(1);   
   }
   else if(i >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_input_variable_minimum(int) method." << std::endl
                << "Index must be less than number of inputs." << std::endl;

      exit(1);
   }

   #endif

   return(input_variables_minimum[i]);
}


// Vector<double>& get_output_variables_minimum(void) method

/// This method returns the minimum values of all the output variables in the neural network.
/// Such values are to be used for unscaling outputs with the minimum and maximum method. 

Vector<double>& MultilayerPerceptron::get_output_variables_minimum(void)
{
   return(output_variables_minimum);               
}


// double get_output_variable_minimum(int) method

/// This method returns the minimum value of a single output variable in the neural network.
/// Such value is to be used for unscaling that output with the minimum and maximum method.

double MultilayerPerceptron::get_output_variable_minimum(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(outputs_number == 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_minimum(int) method." << std::endl
                << "Number of outputs is zero." << std::endl;

      exit(1);   
   }
   else if(i >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_minimum(int) method." << std::endl
                << "Index must be less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_minimum[i]);
}


// Vector<double>& get_input_variables_maximum(void) method

/// This method returns the maximum values of all the input variables in the neural network.
/// Such values are to be used for scaling inputs with the minimum and maximum method.

Vector<double>& MultilayerPerceptron::get_input_variables_maximum(void)
{
   return(input_variables_maximum);               
}


// double get_input_variable_maximum(int) method

/// This method returns the maximum value of a single input variable in the neural network.
/// Such value is to be used for scaling that input with the minimum and maximum method.

double MultilayerPerceptron::get_input_variable_maximum(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(inputs_number == 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_input_variable_maximum(int) method." << std::endl
                << "Number of inputs is zero." << std::endl;

      exit(1);   
   }
   else if(i >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_input_variable_maximum(int) method." << std::endl
                << "Index must be less than number of inputs." << std::endl;

      exit(1);
   }

   #endif

   return(input_variables_maximum[i]);
}


// Vector<double>& get_output_variables_maximum(void) method

/// This method returns the maximum values of all the output variables in the neural network.
/// Such values are to be used for unscaling outputs with the minimum and maximum method. 

Vector<double>& MultilayerPerceptron::get_output_variables_maximum(void)
{
   return(output_variables_maximum);               
}


// double get_output_variable_maximum(int) method

/// This method returns the maximum value of a single input variable in the neural network.
/// Such value is to be used for unscaling that output with the minimum and maximum method.

double MultilayerPerceptron::get_output_variable_maximum(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(outputs_number == 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_maximum(int) method." << std::endl
                << "Number of outputs is zero." << std::endl;

      exit(1);   
   }
   else if(i >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_maximum(int) method." << std::endl
                << "Index must be less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_maximum[i]);
}


// Vector< Vector<double>* > get_input_variables_minimum_maximum(void) method

/// This method returns the minimum and the maximum values of all the input variables. 
/// The format is a vector of pointers to vectors of size two. 
/// The first element contains the minimum values of the input variables.
/// The second element contains the maximum values of the input variables.
/// Such values are to be used for scaling inputs with the minimum and maximum method.

Vector< Vector<double>* > MultilayerPerceptron::get_input_variables_minimum_maximum(void)
{
   Vector< Vector<double>* > input_variables_minimum_maximum(2);

   input_variables_minimum_maximum[0] = &input_variables_minimum;
   input_variables_minimum_maximum[1] = &input_variables_maximum;

   return(input_variables_minimum_maximum);
}


// Vector< Vector<double>* > get_output_variables_minimum_maximum(void) method

/// This method returns the minimum and the maximum values of all the output variables. 
/// The format is a vector of pointers to vectors of size two. 
/// The first element contains the minimum values of the output variables.
/// The second element contains the maximum values of the output variables.
/// Such values are to be used for unscaling outputs with the minimum and maximum method. 

Vector< Vector<double>* > MultilayerPerceptron::get_output_variables_minimum_maximum(void)
{
   Vector< Vector<double>* > output_variables_minimum_maximum(2);

   output_variables_minimum_maximum[0] = &output_variables_minimum;
   output_variables_minimum_maximum[1] = &output_variables_maximum;

   return(output_variables_minimum_maximum);
}


// Vector<double>& get_output_variables_lower_bound(void) method

/// This method returns the lower bound of all the output variables in the neural network.
/// These values are used to postprocess the outputs so that they are not less than the lower bounds. 

Vector<double>& MultilayerPerceptron::get_output_variables_lower_bound(void)
{
   return(output_variables_lower_bound);               
}


// double get_output_variables_lower_bound(int) method

/// This method returns the lower bound of a single output variable in the neural network.
/// This value is used to postprocess that output so that it is not less than the lower bound. 

double MultilayerPerceptron::get_output_variables_lower_bound(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(outputs_number == 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variables_lower_bound(int) method." << std::endl
                << "Number of outputs is zero." << std::endl;

      exit(1);   
   }
   else if(i >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variables_lower_bound(int) method." << std::endl
                << "Index must be less than number of output." << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_lower_bound[i]);
}


// Vector<double>& get_output_variables_upper_bound(void) method

/// This method returns the upper bound of all the output variables in the neural network.
/// These values are used to postprocess the outputs so that they are not greater than the upper bounds. 

Vector<double>& MultilayerPerceptron::get_output_variables_upper_bound(void)
{
   return(output_variables_upper_bound);               
}


// double get_output_variable_upper_bound(int) method

/// This method returns the upper bound of a single output variable in the neural network.
/// This value is used to postprocess that output so that it is not greater than the upper bound. 

double MultilayerPerceptron::get_output_variable_upper_bound(int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(outputs_number == 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_upper_bound(int) method." << std::endl
                << "Number of outputs is zero." << std::endl;

      exit(1);   
   }
   else if(i >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_output_variable_upper_bound(int) method." << std::endl
                << "Index must be less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   return(output_variables_upper_bound[i]);
}


// Vector< Vector<double>* > get_output_variables_bounds(void) method

/// This method returns the lower bounds and the upper bounds of all the output variables. 
/// The format is a vector of pointers to vectors of size two. 
/// The first element contains the lower bound values of the output variables.
/// The second element contains the upper bound values of the output variables.
/// These values are used to postprocess the outputs so that they are neither less than the lower bounds nor 
/// greater than the upper bounds.  

Vector< Vector<double>* > MultilayerPerceptron::get_output_variables_bounds(void)
{
   Vector< Vector<double>* > output_variables_bounds(2);

   output_variables_bounds[0] = &output_variables_lower_bound;
   output_variables_bounds[1] = &output_variables_upper_bound;

   return(output_variables_bounds);
}


// Vector< Vector<double>* > get_variables_statistics(void) method

/// This method returns all the available statistics of the input and output variables. 
/// The format is a vector of pointers to vectors of size ten: 
/// <ul>
/// <li> Mean of input variables.
/// <li> Mean of output variables.
/// <li> Standard deviation of input variables.
/// <li> Standard deviation of output variables.
/// <li> Minimum of input variables.
/// <li> Minimum of output variables.
/// <li> Maximum of input variables.

/// <li> Maximum of output variables.
/// </ul>

Vector< Vector<double>* > MultilayerPerceptron::get_variables_statistics(void)
{
   Vector< Vector<double>* > variables_statistics(8);

   variables_statistics[0] = &input_variables_mean;
   variables_statistics[1] = &output_variables_mean;

   variables_statistics[2] = &input_variables_standard_deviation;
   variables_statistics[3] = &output_variables_standard_deviation;

   variables_statistics[4] = &input_variables_minimum;
   variables_statistics[5] = &output_variables_minimum;

   variables_statistics[6] = &input_variables_maximum;
   variables_statistics[7] = &output_variables_maximum;

   return(variables_statistics);
}


// Vector<double> get_independent_parameters(void) method

/// This method returns the values of the independent parameters.
/// These values are postprocessed so that they are neither less than the lower bounds nor greater than the upper 
/// bounds. 

Vector<double>& MultilayerPerceptron::get_independent_parameters(void)
{   
   return(independent_parameters);    
}


// double get_independent_parameter(int) method

/// This method returns the value of a single independent parameter.
/// Such a value is postprocessed so that it is neither less than the lower bound nor greater than the upper 
/// bound. 
/// @param independent_parameter_index Index of independent parameter.

double MultilayerPerceptron::get_independent_parameter(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_independent_parameter(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters[independent_parameter_index]);           
}


// ScalingMethod get_independent_parameters_scaling_method(void) method

/// This method returns the method used for scaling and unscaling the independent parameters.

MultilayerPerceptron::ScalingMethod& MultilayerPerceptron::get_independent_parameters_scaling_method(void)
{
   return(independent_parameters_scaling_method);
}


// std::string get_independent_parameters_scaling_method_name(void) method

/// This method returns a string with the method used for scaling and unscaling the independent parameters.

std::string MultilayerPerceptron::get_independent_parameters_scaling_method_name(void)
{
   if(independent_parameters_scaling_method == None)
   {
      return("None");
   }
   else if(independent_parameters_scaling_method == MeanStandardDeviation)
   {
      return("MeanStandardDeviation");
   }
   else if(independent_parameters_scaling_method == MinimumMaximum)
   {
      return("MinimumMaximum");
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "std::string get_independent_parameters_scaling_method(void) method." << std::endl
                << "Unknown independent parameters scaling and unscaling method." << std::endl;
 
      exit(1);
   }
}


// Vector<std::string>& get_independent_parameters_name(void) method

/// This method returns the name of the independent parameters. 
/// Such names are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_independent_parameters_name(void)
{
   return(independent_parameters_name);    
}


// std::string& get_independent_parameter_name(int) method

/// This method returns the name of a single independent parameter. 
/// Such name is only used to give the user basic information about the problem at hand.
/// @param independent_parameter_index Index of independent parameter.

std::string& MultilayerPerceptron::get_independent_parameter_name(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "std::string get_independent_parameters_name(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than " 
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_name[independent_parameter_index]);
}


// Vector<std::string>& get_independent_parameters_units(void) method

/// This method returns the units of the independent parameters. 
/// Such units are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_independent_parameters_units(void)
{
   return(independent_parameters_units);
}


// std::string get_independent_parameter_units(int) method

/// This method returns the units of a single independent parameter. 
/// Such units are only used to give the user basic information about the problem at hand.
///
/// @param independent_parameter_index Index of independent parameter.

std::string& MultilayerPerceptron::get_independent_parameter_units(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "std::string get_independent_parameters_units(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_units[independent_parameter_index]);
}


// Vector<std::string>& get_independent_parameters_description(void) method

/// This method returns the description of the independent parameters. 
/// Such descriptions are only used to give the user basic information about the problem at hand.

Vector<std::string>& MultilayerPerceptron::get_independent_parameters_description(void)
{
   return(independent_parameters_description);
}


// std::string& get_independent_parameter_description(int) method

/// This method returns the description of a single independent parameter. 
/// Such description is only used to give the user basic information about the problem at hand.
///
/// @param independent_parameter_index Index of independent parameter.

std::string& MultilayerPerceptron::get_independent_parameter_description(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "std::string get_independent_parameters_description(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_description[independent_parameter_index]);
}


// Vector< Vector<std::string>* > get_independent_parameters_information(void) method

/// This method returns all the available information about the independent parameters. 
/// The format is a vector of pointers to vectors of size three: 
/// 
/// <ul>
/// <li> Name of independent parameters.
/// <li> Units of independent parameters.
/// <li> Description of independent parameters.
/// </ul>

Vector< Vector<std::string>* > MultilayerPerceptron::get_independent_parameters_information(void)
{
   Vector< Vector<std::string>* > independent_parameters_information(6);
 
   independent_parameters_information[0] = &independent_parameters_name;
   independent_parameters_information[2] = &independent_parameters_units;
   independent_parameters_information[4] = &independent_parameters_description;

   return(independent_parameters_information);
}


// Vector<double> get_independent_parameters_mean(void) method

/// This method returns the mean values of all the independent parameters.
/// Such values are to be used for scaling and unscaling independent parameters with the mean and standard 
/// deviation method. 

Vector<double>& MultilayerPerceptron::get_independent_parameters_mean(void)
{
   return(independent_parameters_mean);
}


// Vector<double> get_independent_parameters_standard_deviation(void) method

/// This method returns the standard deviation values of all the independent parameters.
/// Such values are to be used for scaling and unscaling independent parameters with the mean and standard 
/// deviation method. 

Vector<double>& MultilayerPerceptron::get_independent_parameters_standard_deviation(void)
{
   return(independent_parameters_standard_deviation);              
}


// Matrix<double> get_independent_parameters_mean_standard_deviation(void) method

/// This method returns the mean and the standard deviation values of all the independent parameters in a single 
/// matrix. 
/// The first row contains the mean values of the independent parameters.
/// The second row contains the standard deviation values of the independent parameters.
/// Such values are to be used for scaling and unscaling independent parameters with the mean and standard 
/// deviation method. 

Vector< Vector<double>* > MultilayerPerceptron::get_independent_parameters_mean_standard_deviation(void)
{
   Vector< Vector<double>* > independent_parameters_mean_standard_deviation(2);

   independent_parameters_mean_standard_deviation[0] = &independent_parameters_mean;
   independent_parameters_mean_standard_deviation[1] = &independent_parameters_standard_deviation;

   return(independent_parameters_mean_standard_deviation);
}


// double get_independent_parameter_mean(int) method

/// This method returns the mean value of a single independent parameter.
/// Such a value is to be used for scaling and unscaling that parameter with the mean and standard deviation 
/// method. 
///
/// @param independent_parameter_index Index of independent parameter.

double MultilayerPerceptron::get_independent_parameter_mean(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_independent_parameters_mean(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_mean[independent_parameter_index]);
}

// double get_independent_parameter_standard_deviation(int) method

/// This method returns the standard deviation value of a single independent parameter.
/// Such a value is to be used for scaling and unscaling that parameter with the mean and standard deviation 
/// method. 
///
/// @param independent_parameter_index Index of independent parameter.

double MultilayerPerceptron::get_independent_parameter_standard_deviation(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_independent_parameters_standard_deviation(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_standard_deviation[independent_parameter_index]);
}



// Vector<double> get_independent_parameters_minimum(void) method

/// This method returns the minimum values of all the independent parameters.
/// Such values are to be used for scaling and unscaling independent parameters with the minimum and maximum 
/// method. 

Vector<double>& MultilayerPerceptron::get_independent_parameters_minimum(void)
{
   return(independent_parameters_minimum);
}


// Vector<double> get_independent_parameters_maximum(void) method

/// This method returns the maximum values of all the independent parameters.
/// Such values are to be used for scaling and unscaling independent parameters with the minimum and maximum 
/// method. 

Vector<double>& MultilayerPerceptron::get_independent_parameters_maximum(void)
{
   return(independent_parameters_maximum);              
}


// Matrix<double> get_independent_parameters_minimum_maximum(void) method

/// This method returns the minimum and maximum values of all the independent parameters.
/// The format is a vector of two pointers to real vectors. 
/// The first element contains the minimum values of the independent parameters.
/// The second element contains the maximum values of the independent parameters.
/// Such values are to be used for scaling and unscaling independent parameters with the minimum and maximum 
/// method. 

Vector< Vector<double>* > MultilayerPerceptron::get_independent_parameters_minimum_maximum(void)
{
   Vector< Vector<double>* > independent_parameters_minimum_maximum(2);

   independent_parameters_minimum_maximum[0] = &independent_parameters_minimum;
   independent_parameters_minimum_maximum[1] = &independent_parameters_maximum;

   return(independent_parameters_minimum_maximum);
}


// double get_independent_parameter_minimum(int) method

/// This method returns the minimum value of a single independent parameter.
/// Such value is to be used for scaling and unscaling that independent parameter with the minimum and maximum 
/// method. 
///
/// @param independent_parameter_index Index of independent parameter.

double MultilayerPerceptron::get_independent_parameter_minimum(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_independent_parameters_minimum(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_minimum[independent_parameter_index]);
}


// double get_independent_parameter_maximum(int) method

/// This method returns the maximum value of a single independent parameter.
/// Such value is to be used for scaling and unscaling that independent parameter with the minimum and maximum 
/// method. 
///
/// @param independent_parameter_index Index of independent parameter.

double MultilayerPerceptron::get_independent_parameter_maximum(int independent_parameter_index)
{

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_independent_parameters_maximum(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_maximum[independent_parameter_index]);
}


// Vector<double> get_independent_parameters_lower_bound(void) method

/// This method returns the lower bounds of all the independent parameters.
/// These values are used to postprocess the independent parameters so that they are not less than the lower 
/// bounds. 

Vector<double>& MultilayerPerceptron::get_independent_parameters_lower_bound(void)
{
   return(independent_parameters_lower_bound);
}


// Vector<double> get_independent_parameters_upper_bound(void) method

/// This method returns the upper bounds of all the independent parameters.
/// These values are used to postprocess the independent parameters so that they are not greater than the upper 
/// bounds. 

Vector<double>& MultilayerPerceptron::get_independent_parameters_upper_bound(void)
{
   return(independent_parameters_upper_bound);
}


// Vector< Vector<double>* > get_independent_parameters_bounds(void) method

/// This method returns the lower and upper bounds of all the independent parameters.
/// The format is a vector of two pointers to real vectors.  
/// The first element contains the lower bounds of the independent parameters.
/// The second element contains the upper bounds of the independent parameters.
/// These values are used to postprocess the independent parameters so that they are neither less than the lower 
/// bounds nor greater than the upper bounds. 

Vector< Vector<double>* > MultilayerPerceptron::get_independent_parameters_bounds(void)
{
   Vector< Vector<double>* > independent_parameters_bounds(2);

   independent_parameters_bounds[0] = &independent_parameters_lower_bound;
   independent_parameters_bounds[1] = &independent_parameters_upper_bound;

   return(independent_parameters_bounds);
}


// double get_independent_parameter_lower_bound(int) method

/// This method returns the lower bound of a single independent parameter.
/// These values are used to postprocess that independent parameter so that it is not less than the lower bound. 
///
/// @param independent_parameter_index Index of independent parameter.

double MultilayerPerceptron::get_independent_parameter_lower_bound(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_independent_parameters_lower_bound(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_lower_bound[independent_parameter_index]);
}


// double get_independent_parameter_upper_bound(int) method

/// This method returns the upper bound of a single independent parameter.
/// These values are used to postprocess that independent parameter so that it is not greater than the upper 
/// bound. 
///
/// @param independent_parameter_index Index of independent parameter.

double MultilayerPerceptron::get_independent_parameter_upper_bound(int independent_parameter_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "double get_independent_parameters_upper_bound(int) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   return(independent_parameters_upper_bound[independent_parameter_index]);
}


// Vector<double> get_parameters(void) method

/// This method returns the values of the parameters in the neural network as a single vector.
/// This contains all the neural parameters (biases and synaptic weights) and preprocessed independent parameters. 

Vector<double> MultilayerPerceptron::get_parameters(void)
{ 
   int independent_parameters_number = get_independent_parameters_number();

   if((inputs_number != 0 && outputs_number != 0) && independent_parameters_number == 0)
   {// Only neural parameters 
      return(get_neural_parameters());
   }
   else if((inputs_number == 0 && outputs_number == 0) && independent_parameters_number != 0)
   {// Only independent parameters
      return(scale_independent_parameters());
   }
   else if((inputs_number != 0 && outputs_number != 0) && independent_parameters_number != 0)
   {// Both neural and independent parameters

      Vector<double> neural_parameters = get_neural_parameters();

      Vector<double> scaled_independent_parameters = scale_independent_parameters();

      return(neural_parameters.assemble(scaled_independent_parameters));
   }
   else 
   {// None neural neither independent parameters

      Vector<double> parameters;

      return(parameters);
   }
}


// NumericalDifferentiationMethod get_numerical_differentiation_method(void) method

/// This method returns the method used for numerical differentiation in order to calculate the Jacobian matrix 
/// for the multilayer perceptron.

MultilayerPerceptron::NumericalDifferentiationMethod& MultilayerPerceptron::get_numerical_differentiation_method(void)
{
   return(numerical_differentiation_method);                           
}


// std::string get_numerical_differentiation_method_name(void) method

std::string MultilayerPerceptron::get_numerical_differentiation_method_name(void)
{
   switch(numerical_differentiation_method)
   {
      case MultilayerPerceptron::ForwardDifferences:
      {
         return("ForwardDifferences");
	  }
	  break;

      case MultilayerPerceptron::CentralDifferences:
      {
         return("CentralDifferences");
 	  }
	  break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "std::string get_numerical_differentiation_method(void) method." << std::endl
                   << "Unknown numerical differentiation method." << std::endl;
 
         exit(1);
	  }
	  break;
   }
}


// NumericalEpsilonMethod get_numerical_epsilon_method(void) method

MultilayerPerceptron::NumericalEpsilonMethod& MultilayerPerceptron::get_numerical_epsilon_method(void)
{
   return(numerical_epsilon_method);
}


// std::string get_numerical_epsilon_method_name(void) method

std::string MultilayerPerceptron::get_numerical_epsilon_method_name(void)
{
   if(numerical_epsilon_method == Absolute)
   {
      return("Absolute");
   }
   else if(numerical_epsilon_method == Relative)
   {
      return("Relative");
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "std::string get_numerical_epsilon_method(void) method." << std::endl
                << "Unknown numerical epsilon method." << std::endl;
 
      exit(1);
   }
}


// double get_numerical_epsilon(void) method

/// This method returns the epsilon value to be used for computing the Jacobian matrix and the sensitivity matrix 
/// of the neural network for a set of inputs and by means of numerical differentiation.

double MultilayerPerceptron::get_numerical_epsilon(void)
{
   return(numerical_epsilon);
}


// Vector< Vector<double>* > get_independent_parameters_statistics(void) method

Vector< Vector<double>* > MultilayerPerceptron::get_independent_parameters_statistics(void) 
{
   Vector< Vector<double>* > independent_parameters_statistics(4);

   independent_parameters_statistics[0] = &independent_parameters_mean;
   independent_parameters_statistics[1] = &independent_parameters_standard_deviation;

   independent_parameters_statistics[4] = &independent_parameters_minimum;
   independent_parameters_statistics[5] = &independent_parameters_minimum;

   return(independent_parameters_statistics);
}


// Vector<double> scale_independent_parameters(void) method

/// This method preprocesses the independendent parameters according to their scaling and unscaling method.
/// This form of scaling is used prior when getting the vector of parameters.

Vector<double> MultilayerPerceptron::scale_independent_parameters(void)
{
   int independent_parameters_number = get_independent_parameters_number();

   switch(independent_parameters_scaling_method)   
   {
      case None:
      {
         return(independent_parameters);
      }
      break;
                                     
      case MeanStandardDeviation:
      {
         Vector<double> scaled_independent_parameters(independent_parameters_number);

         for(int i = 0; i < independent_parameters_number; i++)
         {
            if(independent_parameters_standard_deviation[i] < 1.0e-99)
            {
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class." << std::endl
                            << "Vector<double> scale_independent_parameters(void) method." << std::endl
                            << "Standard deviation of independent parameter " << i << " is zero." << std::endl
                            << "That independent won't be unscaled." << std::endl; 
               }
               
               scaled_independent_parameters[i] = independent_parameters[i];
            }
            else
            {
               scaled_independent_parameters[i] 
               = (independent_parameters[i] - independent_parameters_mean[i])
               /independent_parameters_standard_deviation[i];
            }
         }

         return(scaled_independent_parameters);
	   }
      break;

      case MinimumMaximum:
      {
         Vector<double> scaled_independent_parameters(independent_parameters_number);

         for(int i = 0; i < independent_parameters_number; i++)
         {
            if(independent_parameters_maximum[i]-independent_parameters_minimum[i] < 1.0e-99)
            {
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class." << std::endl
                            << "Vector<double> scale_independent_parameters(void) method." << std::endl
                            << "Maximum and minimum of independent parameter " << i << " are equal." << std::endl
                            << "That independent parameter won't be scaled." << std::endl; 
               }

               scaled_independent_parameters[i] = independent_parameters[i];
            }
            else
            {
               scaled_independent_parameters[i] 
               = 2.0*(independent_parameters[i] - independent_parameters_minimum[i])
               /(independent_parameters_maximum[i]-independent_parameters_minimum[i])-1.0;
            }
         }

		   return(scaled_independent_parameters);	  
	   }
      break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class" << std::endl
                   << "Vector<double> scale_independent_parameters(void) method." << std::endl 
                   << "Unknown independent parameters scaling and unscaling method." << std::endl;

         exit(1); 
      }
      break;
   }// end switch
}


// void unscale_independent_parameters(void) method

/// This method postprocesses the independendent parameters according to their scaling and unscaling method.
/// This form of scaling is used when setting a new vector of parameters.

void MultilayerPerceptron::unscale_independent_parameters(const Vector<double>& scaled_independent_parameters)
{
   int independent_parameters_number = get_independent_parameters_number();

   switch(independent_parameters_scaling_method)   
   {
      case None:
      {
         independent_parameters = scaled_independent_parameters;
      }
      break;
                                     
      case MeanStandardDeviation:
      {
         for(int i = 0; i < independent_parameters_number; i++)
	     {
            if(independent_parameters_standard_deviation[i] < 1e-99)
            {      
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class" << std::endl
                            << "void unscale_independent_parameters(void) method." << std::endl
                            << "Standard deviation of independent parameter " << i << " is zero." << std::endl 
                            << "That independent parameter won't be scaled." << std::endl;
               }
               
               independent_parameters[i] = scaled_independent_parameters[i];
            }      
            else
            {
               independent_parameters[i] = independent_parameters_mean[i]
               + scaled_independent_parameters[i]*independent_parameters_standard_deviation[i]; 
            } 
         }
      }
      break;

      case MinimumMaximum:
      {
         for(int i = 0; i < independent_parameters_number; i++)
	     {
            if(independent_parameters_maximum[i]-independent_parameters_minimum[i] < 1e-99)
            {      
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class" << std::endl
                            << "void unscale_independent_parameters(void) method." << std::endl
                            << "Maximum and minimum of independent parameter " << i << " are equal." << std::endl
                            << "That independent parameter won't be scaled." << std::endl; 
               }
               
               independent_parameters[i] = scaled_independent_parameters[i];
            }      
            else
            {
               independent_parameters[i] = 0.5*(scaled_independent_parameters[i] + 1.0)
               *(independent_parameters_maximum[i]-independent_parameters_minimum[i]) 
               + independent_parameters_minimum[i]; 
            }
         }
      }
      break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class" << std::endl
                   << "void unscale_independent_parameters(void) method." << std::endl 
                   << "Unknown scaling and unscaling method." << std::endl;

         exit(1); 
      }
      break;
   }// end switch       

   bound_independent_parameters();
}


// double calculate_neural_parameters_norm(void) method

/// This method returns the norm of the vector of neural parameters. 

double MultilayerPerceptron::calculate_neural_parameters_norm(void)
{
   double neural_parameters_norm;

   Vector<double> neural_parameters = get_neural_parameters();

   neural_parameters_norm = neural_parameters.calculate_norm();

   return(neural_parameters_norm);
}


// double calculate_independent_parameters_norm(void) method

/// This method returns the norm of the vector of independent parameters.

double MultilayerPerceptron::calculate_independent_parameters_norm(void)
{
   double independent_parameters_norm = independent_parameters.calculate_norm();



   return(independent_parameters_norm);
}


// double calculate_parameters_norm(void) method

/// This method returns the norm of the vector of parameters.

double MultilayerPerceptron::calculate_parameters_norm(void)
{
   Vector<double> parameters = get_parameters();

   double parameters_norm = parameters.calculate_norm();

   return(parameters_norm);
}


// void bound_independent_parameters(void) method

/// This method makes the independent parameters to fall in the range defined by their lower and the upper bounds. 

void MultilayerPerceptron::bound_independent_parameters(void)
{
   int independent_parameters_number = get_independent_parameters_number();

   int independent_parameters_lower_bound_size = independent_parameters_lower_bound.get_size();  
   int independent_parameters_upper_bound_size = independent_parameters_upper_bound.get_size();  
 
   if(independent_parameters_lower_bound_size == independent_parameters_number && independent_parameters_upper_bound_size == independent_parameters_number)
   {
      independent_parameters.apply_lower_upper_bounds(independent_parameters_lower_bound, independent_parameters_upper_bound);
   }
   else if(independent_parameters_lower_bound_size == independent_parameters_number)
   {
      independent_parameters.apply_lower_bound(independent_parameters_lower_bound);   
   }
   else if(independent_parameters_upper_bound_size == independent_parameters_number)
   {
      independent_parameters.apply_upper_bound(independent_parameters_upper_bound);   
   }
}


// void bound_independent_parameter(int) method

/// This method makes a single independent parameter to fall in the range defined by its lower and the upper bounds. 
/// @param independent_parameter_index Index of independent parameters. 

void MultilayerPerceptron::bound_independent_parameter(int independent_parameter_index)
{
   if(independent_parameters_lower_bound != 0 && independent_parameters_upper_bound != 0)
   {
      if(independent_parameters[independent_parameter_index] 
      < independent_parameters_lower_bound[independent_parameter_index])
      {
         independent_parameters[independent_parameter_index] 
         = independent_parameters_lower_bound[independent_parameter_index];
      }
      else if(independent_parameters[independent_parameter_index] 
      > independent_parameters_upper_bound[independent_parameter_index])
      {
         independent_parameters[independent_parameter_index] 
         = independent_parameters_upper_bound[independent_parameter_index];
      }
   }
   else if(independent_parameters_lower_bound != 0)
   {
      if(independent_parameters[independent_parameter_index] 
      < independent_parameters_lower_bound[independent_parameter_index])
      {
         independent_parameters[independent_parameter_index] 
         = independent_parameters_lower_bound[independent_parameter_index];
      }
   }
   else if(independent_parameters_upper_bound != 0)
   {
      if(independent_parameters[independent_parameter_index] 
      > independent_parameters_upper_bound[independent_parameter_index])
      {
         independent_parameters[independent_parameter_index] 
         = independent_parameters_upper_bound[independent_parameter_index];
      }
   }
}


// bool get_display_range_out_warning(void) method

/// This method returns true if a warning message is to be displayed on the screen when some input variables fall outside
/// the range defined by the minimum and maximum, or false otherwise.

bool MultilayerPerceptron::get_display_range_out_warning(void)
{
   return(display_range_out_warning);
}


// bool get_display(void) method

/// This method returns true if messages from this class are to be displayed on the screen, or false if messages 
/// from this class are not to be displayed on the screen.

bool MultilayerPerceptron::get_display(void)
{
   return(display);
}


// void set(void) method

void MultilayerPerceptron::set(void)
{
   Vector<int> new_hidden_layers_size;
   set_network_architecture(0, new_hidden_layers_size, 0);

   set_independent_parameters_number(0);

   set_default();
}


// void set(int, const Vector<int>&, int) method

void MultilayerPerceptron::set(int new_inputs_number, const Vector<int>& new_hidden_layers_size, int new_outputs_number)
{
   set_network_architecture(new_inputs_number, new_hidden_layers_size, new_outputs_number);

   set_independent_parameters_number(0);

   set_default();
}


// void set(int, int, int) method

void MultilayerPerceptron::set(int new_inputs_number, int new_hidden_layer_size, int new_outputs_number)
{
   Vector<int> new_hidden_layers_size(1, new_hidden_layer_size);

   set_network_architecture(new_inputs_number, new_hidden_layers_size, new_outputs_number);

   set_independent_parameters_number(0);

   set_default();
}


// void set(int) method

void MultilayerPerceptron::set(int new_independent_parameters_number)
{
   Vector<int> new_hidden_layers_size;
   set_network_architecture(0, new_hidden_layers_size, 0);
   
   set_independent_parameters_number(new_independent_parameters_number);

   set_default();
}


// void set(const char*) method

void MultilayerPerceptron::set(const char*)
{
}


// void set(const MultilayerPerceptron&) method

void MultilayerPerceptron::set(const MultilayerPerceptron&)
{
}


// void set_default(void) method

void MultilayerPerceptron::set_default(void)
{
   // Pre and unscaling
   
   inputs_scaling_method = None;
   outputs_unscaling_method = None;

   independent_parameters_scaling_method = None;

   // Numerical differentiation 

   numerical_differentiation_method = MultilayerPerceptron::CentralDifferences;
   numerical_epsilon_method = MultilayerPerceptron::Relative;
   numerical_epsilon = 1.0e-6;

   // Display messages
   
   display = true;
   display_range_out_warning = false;
}


// void set_network_architecture(int, const Vector<int>&, int) method

/// This method sets the architecture of the neural network with an arbitrary number of hidden layers. 
/// All the parameters of the neural network are initialized at random.
///
/// @param new_inputs_number New number of inputs in the neural network.
/// @param new_hidden_layers_size New numbers of neurons for the hidden layers of the neural network.
/// The number of elements of this vector is the number of hidden layers. 
/// @param new_outputs_number New number of output neurons in the neural network.

void MultilayerPerceptron::set_network_architecture
(int new_inputs_number, const Vector<int>& new_hidden_layers_size, int new_outputs_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(!(new_inputs_number == 0 && new_hidden_layers_size == 0 && new_outputs_number == 0))
   {  
      if(new_inputs_number == 0)
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                   << "void set_network_architecture(int, const Vector<int>&, int) method." << std::endl
                   << "Number of inputs must be greater than zero." << std::endl;

         exit(1);
      }

      int size = new_hidden_layers_size.get_size();
   
      for(int i = 0; i < size; i++)
      {
         if(new_hidden_layers_size == 0)
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                      << "void set_network_architecture(int, const Vector<int>&, int) method." << std::endl
                      << "Sizo of hidden layer " << i << " must be greater than zero." << std::endl;

            exit(1);
         }
      }

      if(new_outputs_number == 0)
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                   << "void set_network_architecture(int, const Vector<int>&, int) method." << std::endl
                   << "Number of outputs must be greater than zero." << std::endl;
   
         exit(1);
      }
   }
   
   #endif

   // Set new architecture      

   
   inputs_number = new_inputs_number;
   hidden_layers_size = new_hidden_layers_size;
   outputs_number = new_outputs_number;

   // Hidden layers

   int hidden_layers_number = get_hidden_layers_number();

   hidden_layers.set(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
      hidden_layers[i].set(hidden_layers_size[i]);

      for(int j = 0; j < hidden_layers_size[i]; j++)
      {
         if(i == 0)// First hidden layer
         {
            hidden_layers[i][j].set_inputs_number(inputs_number);
         }
         else
         {
            hidden_layers[i][j].set_inputs_number(hidden_layers_size[i-1]);
         }       
      }
   }

   // Output layer

   output_layer.set(outputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer[i].set_inputs_number(hidden_layers_size[hidden_layers_number-1]);
   }

   // Set activation functions

   hidden_layers_activation_function.set_size(hidden_layers_number);

   Vector<MultilayerPerceptron::LayerActivationFunction> new_hidden_layers_activation_function(hidden_layers_number, HyperbolicTangent);

   set_hidden_layers_activation_function(new_hidden_layers_activation_function);

   set_output_layer_activation_function(HyperbolicTangent);
}


// void set_network_architecture(int, int, int) method

/// This method sets the architecture of the neural network with a single hidden layer. 
/// All the parameters of the neural network are initialized at random.
///
/// @param new_inputs_number New number of inputs in the neural network.
/// @param new_hidden_layer_size New numbers of neurons for the hidden layer of the neural network.
/// @param new_outputs_number New number of output neurons in the neural network.

void MultilayerPerceptron::set_network_architecture
(int new_inputs_number, int new_hidden_layer_size, int new_outputs_number)
{
   Vector<int> new_hidden_layers_size(1, new_hidden_layer_size);

   set_network_architecture(new_inputs_number, new_hidden_layers_size, new_outputs_number);
}


// void set_hidden_layers_size(const Vector<int>&) method

/// This method sets the size of the hidden layers of the neural network. 
/// It neither modifies the number of inputs nor the number of outputs. 
///
/// @param new_hidden_layers_size New numbers of neurons for the hidden layers of the neural network.
/// The number of elements of this vector is the number of hidden layers. 

void MultilayerPerceptron::set_hidden_layers_size(const Vector<int>& new_hidden_layers_size)
{
   // Set new architecture      

   set_network_architecture(inputs_number, new_hidden_layers_size, outputs_number);
}


// void set_hidden_layer_size(int) method

/// This method sets the size of the hidden layer of the neural network when this is unique. 
/// All the parameters of the neural network are initialized at random.
///
/// @param new_hidden_layer_size New numbers of neurons for the hidden layer of the neural network.

void MultilayerPerceptron::set_hidden_layer_size(int new_hidden_layer_size)
{
   Vector<int> new_hidden_layers_size(1, new_hidden_layer_size);

   set_network_architecture(inputs_number, hidden_layers_size, outputs_number);
}


// void set_neural_parameters(const Vector<double>&) method

/// This method sets all the biases and synaptic weights in the neural network from a single vector.
///
/// @param new_neural_parameters New set of biases and synaptic weights values. 

void MultilayerPerceptron::set_neural_parameters(const Vector<double>& new_neural_parameters)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_neural_parameters.get_size();

   int neural_parameters_number = get_neural_parameters_number();

   if(size != neural_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_neural_parameters(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of biases and synaptic weights." << std::endl;

      exit(1);
   }

   #endif

   int hidden_layers_number = get_hidden_layers_number();

   double bias;
   Vector<double> synaptic_weights;

   // Hidden layers parameters

   int index = 0;

   for(int i = 0; i < hidden_layers_number; i++)
   {
      if(i == 0)
      {
         synaptic_weights.set(inputs_number);
      }
      else
      {
         synaptic_weights.set(hidden_layers_size[i-1]);	  
      }

      for(int j = 0; j < hidden_layers_size[i]; j++)
      {                  
         // Bias 

         bias = new_neural_parameters[index];           
         hidden_layers[i][j].set_bias(bias);
         index++;

	     // Synaptic weights  

         synaptic_weights = new_neural_parameters.extract(index, hidden_layers[i][j].get_inputs_number());
         hidden_layers[i][j].set_synaptic_weights(synaptic_weights);
         index += hidden_layers[i][j].get_inputs_number();
      }
   }

   // Output layer parameters

   for(int i = 0; i < outputs_number; i++)
   {
      synaptic_weights.set(hidden_layers_size[hidden_layers_number-1]);	  

      // Bias 

      bias = new_neural_parameters[index];           
      output_layer[i].set_bias(bias);
      index++;

      // Synaptic weights

      synaptic_weights = new_neural_parameters.extract(index, output_layer[i].get_inputs_number());
      output_layer[i].set_synaptic_weights(synaptic_weights);
      index += output_layer[i].get_inputs_number();
   }
}


// void set_hidden_layers_biases(const Vector< Vector<double> >&) method

/// This method sets all the biases of the hidden layers in the neural network.
/// The format is a vector of vectors of real numbers. 
/// The size of this vector is the number of hidden layers.
/// The size of each subvector is the number of neurons in the corresponding hidden layer. 
///
/// @param new_hidden_layers_biases New set of biases in the hidden layers. 

void MultilayerPerceptron::set_hidden_layers_biases(const Vector< Vector<double> >& new_hidden_layers_biases)
{
   int hidden_layers_number = get_hidden_layers_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_hidden_layers_biases.get_size();

   if(size != hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layers_biases(const Vector< Vector<double> >&) method." << std::endl
                << "Size must be equal to number of hidden layers." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < hidden_layers_number; i++)
   {
      for(int j = 0; j < hidden_layers_size[i]; j++)
	  {
	     hidden_layers[i][j].set_bias(new_hidden_layers_biases[i][j]); 
	  }   
   }
}


// void set_hidden_layer_biases(int, const Vector<double>&) method

/// This method sets the biases of a single hidden layer in the neural network.
///
/// @param i Index of hidden layer. 
/// @param new_hidden_layer_biases New set of biases in that hidden layer. 

void MultilayerPerceptron::
set_hidden_layer_biases(int i, const Vector<double>& new_hidden_layer_biases)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layer_biases(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   int size = new_hidden_layer_biases.get_size();

   int hidden_layer_size = hidden_layers_size[i];

   if(size != hidden_layer_size)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layer_biases(int, const Vector<double>&) method." << std::endl
                << "Size must be equal to number of hidden layer inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set hidden layer biases

   for(int j = 0; j < hidden_layers_size[i]; j++)
   {
      hidden_layers[i][j].set_bias(new_hidden_layer_biases[j]); 
   }   
}


// void set_hidden_layers_synaptic_weights(const Vector< Matrix<double> >&) method

/// This method sets all the synaptic weights of the hidden layers in the neural network.
/// The format is a vector of matrices of real numbers. 
/// The size of this vector is the number of hidden layers.
/// The number of rows of each submatrix is the number of neurons in the corresponding hidden layer. 
/// The number of columns of each submatrix is the number of inputs to the corresponding hidden layer. 
///
/// @param new_hidden_layers_synaptic_weights New set of synaptic weights in the hidden layers. 

void MultilayerPerceptron
::set_hidden_layers_synaptic_weights(const Vector< Matrix<double> >& new_hidden_layers_synaptic_weights)
{
   int hidden_layers_number = get_hidden_layers_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_hidden_layers_synaptic_weights.get_size();

   if(size != hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layers_synaptic_weights(const Vector< Matrix<double> >&) method." << std::endl
                << "Size must be equal to number of hidden layers." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> synaptic_weights;

   for(int i = 0; i < hidden_layers_number; i++)
   {
      for(int j = 0; j < hidden_layers_size[i]; j++)
      {
         synaptic_weights = new_hidden_layers_synaptic_weights[i].get_row(j);

         hidden_layers[i][j].set_synaptic_weights(synaptic_weights);
      }
   }
}


// void set_hidden_layer_synaptic_weights(int, const Matrix<double>&) method

/// This method sets the synaptic weights of a single hidden layer in the neural network.
/// The format is a matrix of real numbers. 
/// The number of rows is the number of neurons in the corresponding hidden layer. 
/// The number of columns is the number of inputs to the corresponding hidden layer. 
///
/// @param i Index of hidden layer.
/// @param new_hidden_layer_synaptic_weights New set of synaptic weights in that hidden layer. 

void MultilayerPerceptron::set_hidden_layer_synaptic_weights
(int i, const Matrix<double>& new_hidden_layer_synaptic_weights)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0 || i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layer_synaptic_weights(int, const Matrix<double>&) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_size = hidden_layers_size[i];

   int hidden_layer_inputs_number = get_hidden_layer_inputs_number(i);

   Vector<double> synaptic_weights(hidden_layer_size, hidden_layer_inputs_number);

   for(int j = 0; j < hidden_layer_size; j++)
   {
      synaptic_weights = new_hidden_layer_synaptic_weights.get_row(j); 

      hidden_layers[i][j].set_synaptic_weights(synaptic_weights);
   }
}



// void set_hidden_layers_parameters(const Vector< Matrix<double> >&) method

void MultilayerPerceptron::set_hidden_layers_parameters(const Vector< Matrix<double> >& new_hidden_layers_parameters)
{
   int hidden_layers_number = get_hidden_layers_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_hidden_layers_parameters.get_size();

   if(size != hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layers_parameters(const Vector< Matrix<double> >&) method." << std::endl
                << "Size must be equal to number of hidden layers." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> parameters;

   for(int i = 0; i < hidden_layers_number; i++)
   {
      for(int j = 0; j < hidden_layers_size[i]; j++)
      {
         parameters = new_hidden_layers_parameters[i].get_row(j);

         hidden_layers[i][j].set_parameters(parameters);
      }
   }
}


// void set_hidden_layer_parameters(int, const Matrix<double>&) method

void MultilayerPerceptron::set_hidden_layer_parameters(int i, const Matrix<double>& new_hidden_layer_parameters)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(i < 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layer_parameters(int, const Matrix<double>&) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero." << std::endl;

      exit(1);
   }
   if(i >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layer_parameters(int, const Matrix<double>&) method." << std::endl
                << "Index of hidden layer must be less than number of hidden layers." << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_size = hidden_layers_size[i];
   int hidden_layer_parameters_number = get_hidden_layer_parameters_number(i);

   Vector<double> parameters(hidden_layer_size, hidden_layer_parameters_number);

   for(int j = 0; j < hidden_layer_size; j++)
   {
      parameters = new_hidden_layer_parameters.get_row(j); 

      hidden_layers[i][j].set_parameters(parameters);
   }
}


// void set_output_layer_biases(const Vector<double>&) method

/// This method sets the biases of the output layer.
///
/// @param new_output_layer_biases New set of biases in the output layer. 

void MultilayerPerceptron::set_output_layer_biases(const Vector<double>& new_output_layer_biases)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_output_layer_biases.get_size();

   if(size != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_layer_biases(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer[i].set_bias(new_output_layer_biases[i]);
   }
}


// void set_output_layer_synaptic_weights(const Matrix<double>&) method

/// This method sets the synaptic weights of the output layer in the neural network.
/// The format is a matrix of real numbers. 
/// The number of rows is the number of outputs.
/// The number of columns is the number of inputs to the output layer. 
///
/// @param new_output_layer_synaptic_weights New set of synaptic weights in the output layer. 

void MultilayerPerceptron::
set_output_layer_synaptic_weights(const Matrix<double>& new_output_layer_synaptic_weights)
{
   int hidden_layers_number = get_hidden_layers_number();

   int output_layer_inputs_number = hidden_layers_size[hidden_layers_number-1];

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int rows_number = new_output_layer_synaptic_weights.get_rows_number();
   int columns_number = new_output_layer_synaptic_weights.get_columns_number();

   Matrix<double> output_layer_synaptic_weights(outputs_number, output_layer_inputs_number);    

   if(rows_number != outputs_number || columns_number != output_layer_inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layer_synaptic_weights(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero and less than number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   Vector<double> synaptic_weights(output_layer_inputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      synaptic_weights = new_output_layer_synaptic_weights.get_row(i);
		  
      output_layer[i].set_synaptic_weights(synaptic_weights);
   }
}


// void set_hidden_layers_activation_function(const Vector<LayerActivationFunction>&) method

/// This class sets a new activation (or transfer) function in all the hidden layers of the neural network. 
///
/// @param new_hidden_layers_activation_function Activation function for the hidden layers.
/// The size of this Vector must be equal to the number of hidden layers, and each element corresponds
/// to the activation function of one hidden layer. 

void MultilayerPerceptron::set_hidden_layers_activation_function
(const Vector<MultilayerPerceptron::LayerActivationFunction>& new_hidden_layers_activation_function)
{ 
   int hidden_layers_number = get_hidden_layers_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int new_hidden_layers_activation_function_size = new_hidden_layers_activation_function.get_size();

   if(new_hidden_layers_activation_function_size != hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_hidden_layers_activation_function(const Vector<LayerActivationFunction>&) method." << std::endl
                << "Size of activation function of hidden layers must be equal to number of hidden layers." 
                << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < hidden_layers_number; i++)
   {
      set_hidden_layer_activation_function(i, new_hidden_layers_activation_function[i]);
   }
}


// void set_hidden_layer_activation_function(int, const LayerActivationFunction&) method

/// This class sets a new activation (or transfer) function in a single hidden layer. 
///
/// @param i Index of hidden layer. 
/// @param new_hidden_layer_activation_function Activation function for the hidden layer with the previous index.

void MultilayerPerceptron::set_hidden_layer_activation_function
(int i, const MultilayerPerceptron::LayerActivationFunction& new_hidden_layer_activation_function)
{
   hidden_layers_activation_function[i] = new_hidden_layer_activation_function;

   switch(hidden_layers_activation_function[i])
   {
      case Logistic:
      {
         for(int j = 0; j < hidden_layers_size[i]; j++)
         {
            hidden_layers[i][j].set_activation_function(Perceptron::Logistic);
         }
      }          
      break;

      case HyperbolicTangent:
      {
         for(int j = 0; j < hidden_layers_size[i]; j++)
         {
            hidden_layers[i][j].set_activation_function(Perceptron::HyperbolicTangent);
         }
      }          
      break;

      case Threshold:
      {
         for(int j = 0; j < hidden_layers_size[i]; j++)
         {
            hidden_layers[i][j].set_activation_function(Perceptron::Threshold);
         }
      }
      break;

      case SymmetricThreshold:
      {
         for(int j = 0; j < hidden_layers_size[i]; j++)
         {
            hidden_layers[i][j].set_activation_function(Perceptron::SymmetricThreshold);
         }
      }
      break;

      case Linear:
      {
         for(int j = 0; j < hidden_layers_size[i]; j++)
         {
            hidden_layers[i][j].set_activation_function(Perceptron::Linear);
         }
      }          
      break;
   }
}


// void set_output_layer_activation_function(const LayerActivationFunction&) method

/// This class sets a new activation (or transfer) function in the output layer. 
///
/// @param new_output_layer_activation_function Activation function for the output layer. 

void MultilayerPerceptron::set_output_layer_activation_function
(const MultilayerPerceptron::LayerActivationFunction& new_output_layer_activation_function)
{
   output_layer_activation_function = new_output_layer_activation_function;

   switch(output_layer_activation_function)   
   {
      case Logistic:
      {
         for(int i = 0; i < outputs_number; i++)
         {
   	    output_layer[i].set_activation_function(Perceptron::Logistic);
         }
      }
      break;

      case HyperbolicTangent:
      {
         for(int i = 0; i < outputs_number; i++)
         {
            output_layer[i].set_activation_function(Perceptron::HyperbolicTangent);
         }
      }
      break;

      case Threshold:
      {
         for(int i = 0; i < outputs_number; i++)
         {
   	        output_layer[i].set_activation_function(Perceptron::Threshold);
         }
      }
      break;

      case SymmetricThreshold:
      {
         for(int i = 0; i < outputs_number; i++)
         {
   	        output_layer[i].set_activation_function(Perceptron::SymmetricThreshold);
         }
      }
      break;

      case Linear:
      {
         for(int i = 0; i < outputs_number; i++)
         {
            output_layer[i].set_activation_function(Perceptron::Linear);
         }
      }
      break;
   }
}


// void set_hidden_layers_activation_function(const Vector<std::string>&) method

void MultilayerPerceptron::
set_hidden_layers_activation_function(const Vector<std::string>& new_hidden_layers_activation_function)
{
   int hidden_layers_number = get_hidden_layers_number();

   for(int i = 0; i < hidden_layers_number; i++)
   {
      set_hidden_layer_activation_function(i, new_hidden_layers_activation_function[i]);
   }
}


// void set_hidden_layer_activation_function(int, const std::string&) method

void MultilayerPerceptron::set_hidden_layer_activation_function(int hidden_layer_index, const std::string& new_hidden_layer_activation_function)
{
   if(new_hidden_layer_activation_function == "Logistic")
   {
      hidden_layers_activation_function[hidden_layer_index] = MultilayerPerceptron::Logistic;
   }
   else if(new_hidden_layer_activation_function == "HyperbolicTangent")
   {
      hidden_layers_activation_function[hidden_layer_index] = MultilayerPerceptron::HyperbolicTangent;
   }
   else if(new_hidden_layer_activation_function == "Threshold")
   {
      hidden_layers_activation_function[hidden_layer_index] = MultilayerPerceptron::Threshold;
   }
   else if(new_hidden_layer_activation_function == "SymmetricThreshold")
   {
      hidden_layers_activation_function[hidden_layer_index] = MultilayerPerceptron::SymmetricThreshold;
   }
   else if(new_hidden_layer_activation_function == "Linear")
   {
      hidden_layers_activation_function[hidden_layer_index] = MultilayerPerceptron::Linear;
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_hidden_layer_activation_function(int, const std::string&) method." << std::endl
				<< "Unknown hidden layer activation function: " << new_hidden_layer_activation_function << "." <<std::endl;
   
      exit(1);   
   }
}


// void set_output_layer_activation_function(const std::string&) method

void MultilayerPerceptron::set_output_layer_activation_function(const std::string& new_output_layer_activation_function)
{
   if(new_output_layer_activation_function == "Logistic")
   {
      output_layer_activation_function = MultilayerPerceptron::Logistic;
   }
   else if(new_output_layer_activation_function == "HyperbolicTangent")
   {
      output_layer_activation_function = MultilayerPerceptron::HyperbolicTangent;
   }
   else if(new_output_layer_activation_function == "Threshold")
   {
      output_layer_activation_function = MultilayerPerceptron::Threshold;
   }
   else if(new_output_layer_activation_function == "SymmetricThreshold")
   {
      output_layer_activation_function = MultilayerPerceptron::SymmetricThreshold;
   }
   else if(new_output_layer_activation_function == "Linear")
   {
      output_layer_activation_function = MultilayerPerceptron::Linear;
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_layer_activation_function(const std::string&) method." << std::endl
				<< "Unknown output layer activation function: " << new_output_layer_activation_function << "." <<std::endl;
   
      exit(1);   
   }
}


// void set_inputs_scaling_method(ScalingMethod)

/// This method sets the method to be used for scaling the inputs to the neural network.
///
/// @param new_inputs_scaling_method New scaling method for the input variables.

void MultilayerPerceptron::set_inputs_scaling_method
(const MultilayerPerceptron::ScalingMethod& new_inputs_scaling_method)
{
   inputs_scaling_method = new_inputs_scaling_method;   
}


// void set_outputs_unscaling_method(ScalingMethod) method

/// This method sets the method to be used for unscaling the outputs from the neural network.
///
/// @param new_outputs_unscaling_method New unscaling method for the output variables.

void MultilayerPerceptron::set_outputs_unscaling_method
(const MultilayerPerceptron::ScalingMethod& new_outputs_unscaling_method)
{
   outputs_unscaling_method = new_outputs_unscaling_method;
}


// void set_variables_scaling_method(const ScalingMethod&) method

void MultilayerPerceptron::set_variables_scaling_method(const ScalingMethod& new_variables_scaling_method)
{
   inputs_scaling_method = new_variables_scaling_method;   
   outputs_unscaling_method = new_variables_scaling_method;
}


// void set_inputs_scaling_method(const std::string&) method

void MultilayerPerceptron::set_inputs_scaling_method(const std::string& new_inputs_scaling_method)
{
   if(new_inputs_scaling_method == "None")
   {
      inputs_scaling_method = MultilayerPerceptron::None;
   }
   else if(new_inputs_scaling_method == "MeanStandardDeviation")
   {
      inputs_scaling_method = MultilayerPerceptron::MeanStandardDeviation;
   }
   else if(new_inputs_scaling_method == "MinimumMaximum")
   {
      inputs_scaling_method = MultilayerPerceptron::MinimumMaximum;
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_inputs_scaling_method(const std::string&) method." << std::endl
				<< "Unknown inputs scaling method: " << new_inputs_scaling_method << "." <<std::endl;

      exit(1);   
   }
}


// void set_outputs_unscaling_method(const std::string&) method

void MultilayerPerceptron::set_outputs_unscaling_method(const std::string& new_outputs_unscaling_method)
{
   if(new_outputs_unscaling_method == "None")
   {
      outputs_unscaling_method = MultilayerPerceptron::None;
   }
   else if(new_outputs_unscaling_method == "MeanStandardDeviation")
   {
      outputs_unscaling_method = MultilayerPerceptron::MeanStandardDeviation;
   }
   else if(new_outputs_unscaling_method == "MinimumMaximum")
   {
      outputs_unscaling_method = MultilayerPerceptron::MinimumMaximum;
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_outputs_unscaling_method(const std::string&) method." << std::endl
				<< "Unknown outputs unscaling method: " << new_outputs_unscaling_method << "." <<std::endl;

      exit(1);   
   }
}


// void set_input_variables_name(const Vector<std::string>&) method

/// This method sets the names of the input variables.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_input_variables_name New names for the input variables of the neural network.

void MultilayerPerceptron::set_input_variables_name(const Vector<std::string>& new_input_variables_name)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_input_variables_name.get_size();

   if(size != 0 && size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_input_variables_name(const Vector<std::string>&) method." << std::endl
                << "Size of name of input variables vector must be either zero or number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set name of input variables 

   input_variables_name = new_input_variables_name;
}


// void set_input_variable_name(int, const std::string&) method

/// This method sets the name of a single input variable.
/// Such value is only used to give the user basic information on the problem at hand.
///
/// @param input_variable_index Index of input variable.
/// @param new_input_variable_name New name for the input variable with index i.

void MultilayerPerceptron::
set_input_variable_name(int input_variable_index, const std::string& new_input_variable_name)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variable_name(int, const std::string&) method." << std::endl
                << "Index of input variable must be equal or greater than zero or less than number of inputs." 
                << std::endl;

      exit(1);   
   }

   #endif

   if(input_variables_name.get_size() != inputs_number)
   {
      input_variables_name.set(inputs_number); 
   }

   // Set name of single input variable

   input_variables_name[input_variable_index] = new_input_variable_name;
}


// void set_output_variables_name(const Vector<std::string>&) method

/// This method sets the names of the output variables.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_output_variables_name New names for the output variables of the neural network.

void MultilayerPerceptron::set_output_variables_name(const Vector<std::string>& new_output_variables_name)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_output_variables_name.get_size();

   if(size != 0 && size != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_name(const Vector<std::string>&) method." << std::endl 
                << "Size of name of output variables vector must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set name of output variables

   output_variables_name = new_output_variables_name;
}


// void set_output_variable_name(int, const std::string&) method

/// This method sets the name of a single output variable.
/// Such value is only used to give the user basic information on the problem at hand.
///
/// @param output_layer_index Index of output variable.
/// @param new_output_variable_name New name for the output variable with index i.

void MultilayerPerceptron::set_output_variable_name(int output_layer_index, const std::string& new_output_variable_name)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_layer_index < 0 || output_layer_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variable_name(int, const std::string&) method." << std::endl
                << "Index of output varaible must be equal or greater than zero less than number of outputs."
                << std::endl;

      exit(1);   
   }

   #endif

   if(output_variables_name.get_size() != outputs_number)
   {
      output_variables_name.set(outputs_number); 
   }

   // Set name of single output variable

   output_variables_name[output_layer_index] = new_output_variable_name;
}


// void set_input_variables_units(const Vector<std::string>&) method

/// This method sets new units for all the input variables.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_input_variables_units New units for the input variables of the neural network.

void MultilayerPerceptron::set_input_variables_units(const Vector<std::string>& new_input_variables_units)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_input_variables_units.get_size();

   if(size != 0 && size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_input_variables_units(const Vector<std::string>&) method." << std::endl
                << "Size must be either zero or number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set units of input variables

   input_variables_units = new_input_variables_units;
}


// void set_input_variable_units(int, const std::string&) method

/// This method sets new units for a single input variable.
/// Such value is only used to give the user basic information on the problem at hand.
///
/// @param input_variable_index Index of input variable.
/// @param new_input_variable_units New units for that input variable.

void MultilayerPerceptron::set_input_variable_units(int input_variable_index, const std::string& new_input_variable_units)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variable_units(int, const std::string&) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   if(input_variables_units.get_size() != inputs_number)
   {
      input_variables_units.set(inputs_number); 
   }

   // Set units of single input variable

   input_variables_units[input_variable_index] = new_input_variable_units;
}


// void set_output_variables_units(const Vector<std::string>&) method

/// This method sets new units for all the output variables.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_output_variables_units New units for the input variables of the neural network.

void MultilayerPerceptron::set_output_variables_units(const Vector<std::string>& new_output_variables_units)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_output_variables_units.get_size();

   if(size != 0 && size != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class."  << std::endl 
                << "void set_output_variables_units(const Vector<std::string>&) method." << std::endl
                << "Size must be either zero or number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set units of output variables

   output_variables_units = new_output_variables_units;
}


// void set_output_variable_units(int, const std::string&) method

/// This method sets new units for a single output variable.
/// Such value is only used to give the user basic information on the problem at hand.
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_units New units for that output variable.

void MultilayerPerceptron
::set_output_variable_units(int output_variable_index, const std::string& new_output_variable_units)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variable_units(int, const std::string&) method." << std::endl 
                << "Index of output variable must be equal or greater than zero and less than number of outputs."  
                << std::endl;

      exit(1);   
   }

   #endif

   if(output_variables_units.get_size() != outputs_number)
   {
      output_variables_units.set(outputs_number); 
   }

   // Set units of single output variable

   output_variables_units[output_variable_index] = new_output_variable_units;
}


// void set_input_variables_description(const Vector<std::string>&) method

/// This method sets new descriptions for all the input variables.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_input_variables_description New description for the input variables of the neural network.

void MultilayerPerceptron::set_input_variables_description(const Vector<std::string>& new_input_variables_description)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_input_variables_description.get_size();

   if(size != 0 && size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl  
                << "void set_input_variables_description(const Vector<std::string>&) method." << std::endl
                << "Size must be either zero or number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set description of input variables

   input_variables_description = new_input_variables_description;
}


// void set_input_variable_description(int, const std::string&) method

/// This method sets a new description for a single input variable.
/// Such value is only used to give the user basic information on the problem at hand.
///
/// @param input_variable_index Index of input variable.
/// @param new_input_variable_description New description for the input variable with index i.

void MultilayerPerceptron
::set_input_variable_description(int input_variable_index, const std::string& new_input_variable_description)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variable_description(int, const std::string&) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);   
   }

   #endif

   if(input_variables_description.get_size() != inputs_number)
   {
      input_variables_description.set(inputs_number); 
   }

   // Set description of single input variable

   input_variables_description[input_variable_index] = new_input_variable_description;
}


// void set_output_variables_description(const Vector<std::string>&) method

/// This method sets new descriptions for all the output variables.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_output_variables_description New description for the output variables of the neural network.

void MultilayerPerceptron::set_output_variables_description(const Vector<std::string>& new_output_variables_description)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_output_variables_description.get_size();

   if(size != 0 && size != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_output_variables_description(const Vector<std::string>&) method." << std::endl
                << "Size must be either zero or number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set description of output variables

   output_variables_description = new_output_variables_description;
}


// void set_output_variable_description(int, const std::string&) method

/// This method sets a new description for a single output variable.
/// Such value is only used to give the user basic information on the problem at hand.
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_description New description for the output variable with index i.

void MultilayerPerceptron
::set_output_variable_description(int output_variable_index, const std::string& new_output_variable_description)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variable_description(int, const std::string&) method." << std::endl 
                << "Index of output variable must be equal or greater than zero and less than number of outputs." 
                << std::endl;

      exit(1);   
   }

   #endif

   if(output_variables_description.get_size() != outputs_number)
   {
      output_variables_description.set(outputs_number); 
   }

   // Set description of single output variable

   output_variables_description[output_variable_index] = new_output_variable_description;
}


// void set_variables_information(const Vector< Vector<std::string> >&) method

/// This method sets all the possible information about the input and output variables.
/// The format is a vector of vectors of size six: 
/// 
/// <ul>
/// <li> Name of input variables.
/// <li> Name of output variables.
/// <li> Units of input variables.
/// <li> Units of output variables.
/// <li> Description of input variables.
/// <li> Description of output variables.
/// </ul>
///
/// @param new_variables_information Input and output variables information. 

void MultilayerPerceptron::set_variables_information(const Vector< Vector<std::string> >& new_variables_information)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_variables_information.get_size();

   if(size != 6)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_variables_information(const Vector< Vector<std::string> >&) method." << std::endl 
                << "Size of vector must be 6." << std::endl;

      exit(1);   
   }

   for(int i = 0; i < 3; i++)
   {
      size = new_variables_information[i].get_size();

	  if(size != 0 && size != inputs_number)
	  {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "void set_variables_information(const Vector< Vector<std::string> >&) method." << std::endl 
                   << "Size of element "  << i << "  must be equal to number of inputs." << std::endl;

         exit(1);   	  
	  }
   }

   for(int i = 3; i < 6; i++)
   {
      size = new_variables_information[i].get_size();

	  if(size != 0 && size != outputs_number)
	  {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "void set_variables_information(const Vector< Vector<std::string> >&) method." << std::endl 
                   << "Size of element "  << i << "  must be equal to number of outputs." << std::endl;

         exit(1);   	  
	  }
   }

   #endif

   // Set all information

   set_input_variables_name(new_variables_information[0]);
   set_input_variables_units(new_variables_information[1]);
   set_input_variables_description(new_variables_information[2]);

   set_output_variables_name(new_variables_information[3]);
   set_output_variables_units(new_variables_information[4]);
   set_output_variables_description(new_variables_information[5]);
}


//void set_input_variables_mean(const Vector<double>&) method

/// This method sets new mean values for all the input variables.
/// These values are used for scaling the inputs to the neural network with the meand and standard 
/// deviation method. 
///
/// @param new_input_variables_mean New set of mean values for the input variables of the neural network.

void MultilayerPerceptron::set_input_variables_mean(const Vector<double>& new_input_variables_mean)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_input_variables_mean.get_size() != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_input_variables_mean(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set mean of input variables

   input_variables_mean = new_input_variables_mean;
}


// void set_input_variable_mean(int, double) method

/// This method sets a new mean value for a single input variable.
/// These values are used for scaling the inputs to the neural network with the meand and standard 
/// deviation method. 
///
/// @param input_variable_index Index of input variable.
/// @param new_input_variable_mean New mean values for the input variable with index i.

void MultilayerPerceptron::set_input_variable_mean(int input_variable_index, double new_input_variable_mean)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variable_mean(int, double) method." << std::endl
                << "Index of input variable must be equal or greater than zero or less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   // Set vector if necessary

   if(input_variables_mean.get_size() != inputs_number)
   {
      input_variables_mean.set(inputs_number, 0.0);
   }

   // Set mean of single input variable

   input_variables_mean[input_variable_index] = new_input_variable_mean;
}


//void set_output_variables_mean(const Vector< double>&) method

/// This method sets new mean values for all the output variables.
/// These values are used for unscaling the outputs from the neural network with the meand and 
/// standard deviation method. 
///
/// @param new_output_variables_mean New set of mean values for the output variables of the neural network.

void MultilayerPerceptron::set_output_variables_mean(const Vector<double>& new_output_variables_mean)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_mean.get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_output_variables_mean(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set mean of output variables

   output_variables_mean = new_output_variables_mean;
}


// void set_output_variable_mean(int, double) method

/// This method sets a new mean value for a single output variable.
/// These values are used for unscaling the outputs form the neural network with the meand and 
/// standard deviation method. 
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_mean New mean value for the output variable with index i.

void MultilayerPerceptron::set_output_variable_mean(int output_variable_index, double new_output_variable_mean)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variable_mean(int, double) method." << std::endl
                << "Index must be less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set vector if necessary

   if(output_variables_mean.get_size() != outputs_number)
   {
      output_variables_mean.set(outputs_number, 0.0);
   }

   // Set mean of single output variable

   output_variables_mean[output_variable_index] = new_output_variable_mean;
}


// void set_input_variables_standard_deviation(const Vector<double>&) method

/// This method sets new standard deviation values for all the input variables.
/// These values are used for scaling the inputs to the neural network with the meand and standard deviation
/// method. 
///
/// @param new_input_variables_standard_deviation New set of standard deviation values for the input variables of 
/// the neural network.

void MultilayerPerceptron
::set_input_variables_standard_deviation(const Vector<double>& new_input_variables_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_input_variables_standard_deviation.get_size() != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variables_standard_deviation(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set standard deviation of input variables

   input_variables_standard_deviation = new_input_variables_standard_deviation;
}


// void set_input_variable_standard_deviation(int, double) method

/// This method sets a new standard deviation value for a single input variable.
/// These values are used for scaling the inputs to the neural network with the meand and standard 
/// deviation method. 
///
/// @param input_variable_index Index of input variable.
/// @param new_input_variable_standard_deviation New standard deviation value for that input variable.

void MultilayerPerceptron
::set_input_variable_standard_deviation(int input_variable_index, double new_input_variable_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variable_standard_deviation(int, double) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs."
                << std::endl;

      exit(1);
   }

   #endif

   // Set vector if necessary

   if(input_variables_standard_deviation.get_size() != inputs_number)
   {
      input_variables_standard_deviation.set(inputs_number, 1.0);
   }

   // Set standard deviation of single input variable

   input_variables_standard_deviation[input_variable_index] = new_input_variable_standard_deviation;
}


// void set_output_variables_standard_deviation(const Vector<double>&) method

/// This method sets new standard deviation values for all the output variables.
/// These values are used for unscaling the outputs from the neural network with the meand and 
/// standard deviation method. 
///
/// @param new_output_variables_standard_deviation New set of standard deviation values for the output variables of 
/// the neural network.

void MultilayerPerceptron
::set_output_variables_standard_deviation(const Vector<double>& new_output_variables_standard_deviation) 
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_standard_deviation.get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_standard_deviation(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set standard deviation of output variables

   output_variables_standard_deviation = new_output_variables_standard_deviation;
}


// void set_output_variable_standard_deviation(int, double) method

/// This method sets a new standard deviation value for a single output variable.
/// These values are used for unscaling the outputs form the neural network with the meand and 
/// standard deviation method. 
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_standard_deviation New standard deviation value for that output variable.

void MultilayerPerceptron
::set_output_variable_standard_deviation(int output_variable_index, double new_output_variable_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variable_standard_deviation(int, double) method." << std::endl
                << "Index must be equal or greater than zero and less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set vector if necessary

   if(output_variables_standard_deviation.get_size() != outputs_number)
   {
      output_variables_standard_deviation.set(outputs_number, 1.0);
   }

   // Set standard deviation of single output variable

   output_variables_standard_deviation[output_variable_index] = new_output_variable_standard_deviation;
}


// void set_input_variables_mean_standard_deviation(const Vector< Vector<double> >&) method

/// This method sets both the mean and the standard deviation values of all the input variables.
/// The format is a vector of two real vectors.
/// The first element must contain the mean values for the input variables.
/// The second elements must contain the standard deviation values for the input variables.
/// These values are used for scaling the inputs to the neural network with the meand and standard deviation
/// method. 
///
/// @param new_input_variables_mean_standard_deviation New set of mean and standard deviation values for the 
/// input variables of the neural network.

void MultilayerPerceptron::set_input_variables_mean_standard_deviation
(const Vector< Vector<double> >& new_input_variables_mean_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_input_variables_mean_standard_deviation.get_size() != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." << std::endl
                << "Size of vector must be 2." << std::endl;

      exit(1);
   }
   else if(new_input_variables_mean_standard_deviation[0].get_size() != inputs_number
        && new_input_variables_mean_standard_deviation[1].get_size() != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." << std::endl
                << "Number of columns must be equal to number of inputs." << std::endl;

      exit(1);
   }

   // Check that standard deviation of input variables is not zero

   for(int i = 0; i < inputs_number; i++)
   {
      if(new_input_variables_mean_standard_deviation[1][i] < 1.0e-99)
      {
         std::cerr << "Flood Error: MultilayerPerceptron class: " << std::endl
                   << "void set_input_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." 
                   << std::endl
                   << "Standard deviation of input variable "<< i << " is zero." << std::endl;

          exit(1);
      }
   }

   #endif

   // Set mean and standard deviation of input variables

   input_variables_mean = new_input_variables_mean_standard_deviation[0];
   input_variables_standard_deviation = new_input_variables_mean_standard_deviation[1];
}


// void set_output_variables_mean_standard_deviation(const Vector< Vector<double> >&) method

/// This method sets both the mean and the standard deviation values of all the output variables.
/// The format is a vector of two real vectors.
/// The first element must contain the mean values for the output variables.
/// The second element must contain the standard deviation values for the output variables.
///
/// @param new_output_variables_mean_standard_deviation New set of mean and standard deviation values for the 
/// output variables of the neural network.

void MultilayerPerceptron::set_output_variables_mean_standard_deviation
(const Vector< Vector<double> >& new_output_variables_mean_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_mean_standard_deviation.get_size() != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." 
                << std::endl
                << "Size of vector must be 2." << std::endl;

      exit(1);
   }
   else if(new_output_variables_mean_standard_deviation[0].get_size() != outputs_number
        && new_output_variables_mean_standard_deviation[1].get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_mean_standard_deviation(const Vector< Vector<double> >&) method." 
                << std::endl
                << "Number of columns must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set mean and standard deviation of output variables

   output_variables_mean = new_output_variables_mean_standard_deviation[0];   
   output_variables_standard_deviation = new_output_variables_mean_standard_deviation[1];
}


// void set_input_variables_minimum(const Vector<double>&) method

/// This method sets new minimum values for all the input variables.
/// These values are used for scaling the inputs to the neural network with the minimum and maximum method. 
///
/// @param new_input_variables_minimum New set of minimum values for the input variables of the neural network.

void MultilayerPerceptron::set_input_variables_minimum(const Vector<double>& new_input_variables_minimum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_input_variables_minimum.get_size() != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variables_minimum(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set minimum of input variables

   input_variables_minimum = new_input_variables_minimum;
}


// void set_input_variable_minimum(int, double) method

/// This method sets a new minimum value for a single input variable.
/// This value is used for scaling that input to the neural network with the minimum and maximum method. 
///
/// @param input_variable_index Index of input variable.
/// @param new_input_variable_minimum New minimum value for the input variable with index i.

void MultilayerPerceptron::set_input_variable_minimum(int input_variable_index, double new_input_variable_minimum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_input_variable_minimum(int, double) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   if(input_variables_minimum.get_size() == 0)
   {
      input_variables_minimum.set(inputs_number, -1.0);
   }

   // Set minimum of single input variable

   input_variables_minimum[input_variable_index] = new_input_variable_minimum;
}


// void set_output_variables_minimum(const Vector<double>&) method

/// This method sets new minimum values for all the output variables.
/// These values are used for unscaling the outputs from the neural network with the minimum and 
/// maximum method. 
///
/// @param new_output_variables_minimum New set of minimum values for the output variables of the neural network.

void MultilayerPerceptron::set_output_variables_minimum(const Vector<double>& new_output_variables_minimum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_minimum.get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_minimum(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set minimum of output variables

   output_variables_minimum = new_output_variables_minimum;
}


// void set_output_variable_minimum(int, double) method

/// This method sets a new minimum value for a single output variable.
/// This value is used for unscaling that outputs from the neural network with the minimum and 
/// maximum method. 
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_minimum New minimum value for that output variable.

void MultilayerPerceptron::set_output_variable_minimum(int output_variable_index, double new_output_variable_minimum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_output_variable_minimum(int, double) method." << std::endl
                << "Index of output variable must be equal or greater than zero and less than number of outputs." 
                << std::endl;

      exit(1);
   }

   #endif

   if(output_variables_minimum.get_size() == 0)
   {
      output_variables_minimum.set(outputs_number, -1.0);
   }

   // Set minimum of single output variable

   output_variables_minimum[output_variable_index] = new_output_variable_minimum;
}


// void set_input_variables_maximum(const Vector<double>&) method

/// This method sets new maximum values for all the input variables.
/// These values are used for scaling the inputs to the neural network with the minimum and maximum method. 
///
/// @param new_input_variables_maximum New set of maximum values for the input variables of the neural network.

void MultilayerPerceptron::set_input_variables_maximum(const Vector<double>& new_input_variables_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_input_variables_maximum.get_size() != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_input_variables_maximum(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }
   
   #endif

   // Set maximum of input variables

   input_variables_maximum = new_input_variables_maximum;
}


// void set_input_variable_maximum(int, double) method

/// This method sets a new maximum value for a single input variable.
/// This value is used for scaling that input to the neural network with the minimum and maximum method. 
///
/// @param input_variable_index Index of input variable.
/// @param new_input_variable_maximum New maximum value for that input variable.

void MultilayerPerceptron::set_input_variable_maximum(int input_variable_index, double new_input_variable_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_variable_index < 0 || input_variable_index >= inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_input_variable_maximum(int, double) method." << std::endl
                << "Index of input variable must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   if(input_variables_maximum.get_size() == 0)
   {
      input_variables_maximum.set(inputs_number, 1.0);
   }

   // Set maximum of single input variable

   input_variables_maximum[input_variable_index] = new_input_variable_maximum;
}


// void set_output_variables_maximum(const Vector<double>&) method

/// This method sets new maximum values for all the output variables.
/// These values are used for unscaling the outputs from the neural network with the minimum and 
/// maximum method. 
///
/// @param new_output_variables_maximum New set of maximum values for the output variables of the neural network.

void MultilayerPerceptron::set_output_variables_maximum(const Vector<double>& new_output_variables_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_maximum.get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_maximum(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set maximum of output variables

   output_variables_maximum = new_output_variables_maximum;
}


// void set_output_variable_maximum(int, double) method

/// This method sets a new maximum value for a single output variable.
/// This value is used for unscaling that outputs from the neural network with the minimum and 
/// maximum method. 
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_maximum New maximum value for that output variable.

void MultilayerPerceptron::set_output_variable_maximum(int output_variable_index, double new_output_variable_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void new_output_variable_maximum(int, double) method." << std::endl
                << "Index must be equal or greater than zero and less than number of outputs." << std::endl;

      exit(1);
   }

   #endif

   if(output_variables_maximum.get_size() == 0)
   {
      output_variables_maximum.set(outputs_number, 1.0);
   }

   // Set maximum of single output variable

   output_variables_maximum[output_variable_index] = new_output_variable_maximum;
}


// void set_input_variables_minimum_maximum(const Vector< Vector<double> >&) method

/// This method sets both the minimum and the maximum values of all the input variables.
/// The format is a vector of two real vectors. 
/// The first element must contain the minimum values for the input variables.
/// The second element must contain the maximum values for the input variables.
/// These values are used for scaling the inputs to the neural network with the minimum and maximum method. 
///
/// @param new_input_variables_minimum_maximum 
/// New set of minimum and maximum values for the input variables of the neural network.

void MultilayerPerceptron
::set_input_variables_minimum_maximum(const Vector< Vector<double> >& new_input_variables_minimum_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_input_variables_minimum_maximum.get_size() != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_input_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                << "Number of rows must be 2." << std::endl;

      exit(1);
   }
   else if(new_input_variables_minimum_maximum[0].get_size() != inputs_number
	    && new_input_variables_minimum_maximum[1].get_size() != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_input_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                << "Number of columns must be equal to number of inputs." << std::endl;

      exit(1);
   }

   // Check that minimum of input variables is not greater than their maximum

   for(int i = 0; i < inputs_number; i++)
   {
      if(new_input_variables_minimum_maximum[0][i] >= new_input_variables_minimum_maximum[1][i])
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "void set_input_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                   << "Minimum of input variable " << i << " is equal or greater than maximum of that variable."
                   << std::endl;

         exit(1);
      }
   }

   #endif

   // Set minimum and maximum of input variables

   input_variables_minimum = new_input_variables_minimum_maximum[0];
   input_variables_maximum = new_input_variables_minimum_maximum[1];
}


// void set_output_variables_minimum_maximum(const Vector< Vector<double> >&) method

/// This method sets both the minimum and the maximum values of all the output variables.
/// The format is a vector of two real vectors. 
/// The first element must contain the minimum values for the output variables.
/// The second element must contain the maximum values for the output variables.
/// These values are used for unscaling the outputs from network with the minimum and maximum method. 
///
/// @param new_output_variables_minimum_maximum 
/// New set of minimum and maximum values for the output variables of the neural network.

void MultilayerPerceptron
::set_output_variables_minimum_maximum(const Vector< Vector<double> >& new_output_variables_minimum_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_minimum_maximum.get_size() != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_output_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                << "Number of rows must be 2."  << std::endl;

      exit(1);
   }
   else if(new_output_variables_minimum_maximum[0].get_size() != outputs_number
        && new_output_variables_minimum_maximum[1].get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_output_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                << "Number of columns must be equal to number of outputs." << std::endl;

      exit(1);
   }

   // Check that minimum of output variables is not greater than their maximum

   for(int i = 0; i < outputs_number; i++)
   {
      if(new_output_variables_minimum_maximum[0][i] > new_output_variables_minimum_maximum[1][i])
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                   << "void set_output_variables_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                   << "Minimum of output variable " << i << " is greater than maximum of that variable."
                   << std::endl;

         exit(1);
      }
   }

   #endif

   // Set minimum and maximum of output variables

   output_variables_minimum = new_output_variables_minimum_maximum[0];
   output_variables_maximum = new_output_variables_minimum_maximum[0];
}


// void set_output_variables_lower_bound(const Vector<double>&) method

/// This method sets new lower bounds for all the output variables.
/// These values are used for unscaling the outputs so that they are not less than the lower bounds. 
///
/// @param new_output_variables_lower_bound New set of lower bounds for the output variables of the neural network.

void MultilayerPerceptron::set_output_variables_lower_bound(const Vector<double>& new_output_variables_lower_bound)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_lower_bound.get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_lower_bound(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set lower bound of output variables

   output_variables_lower_bound = new_output_variables_lower_bound;
}


// void set_output_variable_lower_bound(int, double) method

/// This method sets a new lower bound for a single output variable.
/// This value is used for unscaling that output so that it is not less than the lower bound. 
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_lower_bound New lower bound for the output variable with index i.

void MultilayerPerceptron
::set_output_variable_lower_bound(int output_variable_index, double new_output_variable_lower_bound)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variable_lower_bound(int, double) method." << std::endl
                << "Index of output variable must be greater than zero and less than number of outputs."
                << std::endl;

      exit(1);
   }

   #endif

   if(output_variables_lower_bound.get_size() != outputs_number)
   {
      output_variables_lower_bound.set(outputs_number, -1.0e99);
   }

   // Set lower bound of single output variable

   output_variables_lower_bound[output_variable_index] = new_output_variable_lower_bound;
}


// void set_output_variables_upper_bound(const Vector<double>&) method

/// This method sets new upper bounds for all the output variables.
/// These values are used for unscaling the outputs so that they are not greater than the upper bounds. 
///
/// @param new_output_variables_upper_bound New set of upper bounds for the output variables of the neural network.

void MultilayerPerceptron::set_output_variables_upper_bound(const Vector<double>& new_output_variables_upper_bound)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_output_variables_upper_bound.get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_upper_bound(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set upper bound of output variables

   output_variables_upper_bound = new_output_variables_upper_bound;
}


// void set_output_variable_upper_bound(int, double) method

/// This method sets a new upper bound for a single output variable.
/// This value is used for unscaling that output so that it is not greater than the upper bound. 
///
/// @param output_variable_index Index of output variable.
/// @param new_output_variable_upper_bound New upper bound for the output variable with index i.

void MultilayerPerceptron
::set_output_variable_upper_bound(int output_variable_index, double new_output_variable_upper_bound)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(output_variable_index < 0 || output_variable_index >= outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variable_upper_bound(int, double) method." << std::endl
                << "Index of output variable must be equal or greater than zero or less than number of outputs." 
                << std::endl;

      exit(1);
   }

   #endif

   if(output_variables_upper_bound.get_size() != outputs_number)
   {
      output_variables_upper_bound.set(outputs_number, 1.0e99);
   }

   // Set upper bound of single output variable

   output_variables_upper_bound[output_variable_index] = new_output_variable_upper_bound;
}


// void set_output_variables_bounds(const Vector< Vector<double> >&) method

/// This method sets both the lower bounds and the upper bounds of all the output variables.
/// The format is a vector of two real vectors.
/// The first element must contain the lower bound values for the output variables.
/// The second element must contain the upper bound values for the output variables.
/// These values are used for unscaling the outputs so that they are neither less than the lower bounds 
/// nor greater than the upper bounds. 
///
/// @param new_output_variables_bounds New set of lower and upper bounds for the output variables of the 
/// neural network.

void MultilayerPerceptron
::set_output_variables_bounds(const Vector< Vector<double> >& new_output_variables_bounds)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_output_variables_bounds.get_size();

   if(size != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_bounds(const Vector< Vector<double> >&) method." << std::endl
                << "Number of rows must be 2." << std::endl;

      exit(1);
   }
   else if(new_output_variables_bounds[0].get_size() != outputs_number
        && new_output_variables_bounds[1].get_size() != outputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_output_variables_bounds(const Vector< Vector<double> >&) method." << std::endl
                << "Number of columns must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set lower and upper bounds of output variables

   output_variables_lower_bound = new_output_variables_bounds[0];
   output_variables_upper_bound = new_output_variables_bounds[1];
}


// void set_variables_statistics(const Vector< Vector<double> >&) method

/// This method sets all the available statistics about the input and output variables.
/// The format is a vector of ten real vectors: 
/// 
/// <ul>
/// <li> Mean of input variables.
/// <li> Standard deviation of input variables.
/// <li> Minimum of input variables.
/// <li> Maximum of input variables.
/// <li> Mean of output variables.
/// <li> Standard deviation of output variables.
/// <li> Minimum of output variables.
/// <li> Maximum of output variables.
/// </ul>
///
/// @param new_variables_statistics Input and output variables statistics. 

void MultilayerPerceptron::set_variables_statistics(const Vector< Vector<double> >& new_variables_statistics)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_variables_statistics.get_size();

   if(size != 8)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_variables_statistics(const Vector< Vector<double> >&) method." << std::endl
                << "Size must be 10." << std::endl;

      exit(1);
   }

   for(int i = 0; i < 4; i++)
   {
      size = new_variables_statistics[i].get_size();

	  if(size != inputs_number)
	  {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "void set_variables_statistics(const Vector< Vector<double> >&) method." << std::endl
                   << "Size of element " << i << " must be equal to number of inputs." << std::endl;

         exit(1);  
	  }
   }

   for(int i = 4; i < 8; i++)
   {
      size = new_variables_statistics[i].get_size();

	  if(size != outputs_number)
	  {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "void set_variables_statistics(const Vector< Vector<double> >&) method." << std::endl
                   << "Size of element " << i << " must be equal to number of outputs." << std::endl;

         exit(1);  
	  }
   }

   #endif

   // Set all statistics
 
   set_input_variables_mean(new_variables_statistics[0]);
   set_input_variables_standard_deviation(new_variables_statistics[1]);
   set_input_variables_minimum(new_variables_statistics[2]);
   set_input_variables_maximum(new_variables_statistics[3]);

   set_output_variables_mean(new_variables_statistics[4]);
   set_output_variables_standard_deviation(new_variables_statistics[5]);
   set_output_variables_minimum(new_variables_statistics[6]);
   set_output_variables_maximum(new_variables_statistics[7]);
}
 

// void set_numerical_differentiation_method(NumericalDifferentiationMethod)

/// This method sets the method to be used for the numerical differentiation of the Jacobian matrix for the 
/// multilayer perceptron.
///
/// @param new_numerical_differentiation_method New numerical differentiation method.

void MultilayerPerceptron::set_numerical_differentiation_method
(const MultilayerPerceptron::NumericalDifferentiationMethod& new_numerical_differentiation_method)
{
   numerical_differentiation_method = new_numerical_differentiation_method;
}


// void set_numerical_differentiation_method(const std::string&) method

void MultilayerPerceptron::set_numerical_differentiation_method(const std::string& new_numerical_differentiation_method)
{
   if(new_numerical_differentiation_method == "ForwardDifferences")
   {
      numerical_differentiation_method = ForwardDifferences;
   }
   else if(new_numerical_differentiation_method == "CentralDifferences")
   {
      numerical_differentiation_method = CentralDifferences;
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_numerical_differentiation_method(const std::string&) method." << std::endl
				<< "Unknown numerical differentiation method: " << new_numerical_differentiation_method << "." <<std::endl;

	  exit(1);   
   }	
}


// void set_numerical_epsilon_method(NumericalEpsilonMethod) method

void MultilayerPerceptron::set_numerical_epsilon_method
(const MultilayerPerceptron::NumericalEpsilonMethod& new_numerical_epsilon_method)
{
   numerical_epsilon_method = new_numerical_epsilon_method;
}


// void set_numerical_epsilon_method(const std::string&) method

void MultilayerPerceptron::set_numerical_epsilon_method(const std::string& new_numerical_epsilon_method)
{
   if(new_numerical_epsilon_method == "Absolute")
   {
      numerical_epsilon_method = Absolute;
   }
   else if(new_numerical_epsilon_method == "Relative")
   {
      numerical_epsilon_method = Relative;
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_numerical_epsilon_method(const std::string&) method." << std::endl
				<< "Unknown numerical epsilon method: " << new_numerical_epsilon_method << "." <<std::endl;

      exit(1);   
   }	
}


// void set_numerical_epsilon(double) method

/// This method sets a new value of epsilon for the computation of the Jacobian matrix by means of numerical 
/// differentiation.
///
/// @param new_numerical_epsilon New value for epsilon. 

void MultilayerPerceptron::set_numerical_epsilon(double new_numerical_epsilon)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_numerical_epsilon <= 0.0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_numerical_epsilon(double) method." << std::endl
                << "Epsilon must be greater than zero." << std::endl;

      exit(1);
   }

   #endif

   // Set numerical epsilon

   numerical_epsilon = new_numerical_epsilon;
}


// void set_independent_parameters_number(int) method

/// This method sets a new number of parameters which are independent of the neural network. 
/// It initializes the independent parameters at random.
/// This method also initializes all the class members related to independent with their default value:
///
/// @param new_independent_parameters_number Number of independent parameters.

void MultilayerPerceptron::set_independent_parameters_number(int new_independent_parameters_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_independent_parameters_number < 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_number(double) method." << std::endl
                << "Number of independent parameters must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   // Independent parameters

   independent_parameters.set_size(new_independent_parameters_number);

   // Initialize independent parameters 
  
   initialize_independent_parameters_normal(0.0, 1.0);

   // Bound independent parameters

   bound_independent_parameters();
}


// void set_independent_parameters(const Vector<double>&) method

/// This method sets new values for all the independent parameters.
///
/// @param new_independent_parameters Independent parameters values.

void MultilayerPerceptron::set_independent_parameters(const Vector<double>& new_independent_parameters)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters(const Vector<double>&) method." << std::endl
                << "Independent parameters vector size must be equal to number of independent parameters."
                << std::endl;

      exit(1);
   }

   #endif

   // Set independent parameters

   independent_parameters = new_independent_parameters;     

   // Bound independent parameters

   bound_independent_parameters();
}


// void set_independent_parameter(int, double) method

/// This method sets a new value for a single independent parameter.
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter Independent parameter value.

void MultilayerPerceptron
::set_independent_parameter(int independent_parameter_index, double new_independent_parameter)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter(int, double) method." << std::endl
                << "Index must be equal or greater than zero and less than number of independent parameters." 
                << std::endl;

      exit(1);   
   }

   #endif

   // Set single independent parameter

   independent_parameters[independent_parameter_index] = new_independent_parameter;

   bound_independent_parameter(independent_parameter_index);
}


// void set_independent_parameters_scaling_method(ScalingMethod) method

/// This method sets the method to be used for scaling and unscaling the independent parameters.
///
/// @param new_independent_parameters_scaling_method New scaling and unscaling method for the output variables.

void MultilayerPerceptron::set_independent_parameters_scaling_method
(const MultilayerPerceptron::ScalingMethod& new_independent_parameters_scaling_method)
{
   independent_parameters_scaling_method = new_independent_parameters_scaling_method;   
}


// void set_independent_parameters_scaling_method(const std::string&) method

void MultilayerPerceptron::set_independent_parameters_scaling_method
(const std::string& new_independent_parameters_scaling_method)
{
   if(new_independent_parameters_scaling_method == "None")
   {
      independent_parameters_scaling_method = MultilayerPerceptron::None;
   }
   else if(new_independent_parameters_scaling_method == "MeanStandardDeviation")
   {
      independent_parameters_scaling_method = MultilayerPerceptron::MeanStandardDeviation;
   }
   else if(new_independent_parameters_scaling_method == "MinimumMaximum")
   {
      independent_parameters_scaling_method = MultilayerPerceptron::MinimumMaximum;
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_scaling_method(const std::string&) method." << std::endl
				<< "Unknown independent parameters scaling method: " << new_independent_parameters_scaling_method << "." <<std::endl;

       exit(1);   
    }
}


// void set_independent_parameters_name(const Vector<std::string>&) method

/// This method sets new names for the independent parameters.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_independent_parameters_name New names for the independent parameters of the neural network.

void MultilayerPerceptron::set_independent_parameters_name(const Vector<std::string>& new_independent_parameters_name)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_name.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_name(const Vector<std::string>&) method."  << std::endl
                << "Name of independent parameters vector size must be equal to number of independent parameters."
                << std::endl;

      exit(1);
   }

   #endif

   // Set name of independent parameters

   independent_parameters_name = new_independent_parameters_name;
}


// void set_independent_parameter_name(int, const std::string&) method

/// This method sets a new name for a single independent parameter.
/// Such a value is only used to give the user basic information on the problem at hand.
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_name New name for the independent parameter of index i.

void MultilayerPerceptron
::set_independent_parameter_name(int independent_parameter_index, const std::string& new_independent_parameter_name)
{
   // Control sentence (if debug)

   int independent_parameters_number = get_independent_parameters_number();

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter_name(int, const std::string&) method." << std::endl
                << "Index must be equal or greater than zero and less than number of independent parameters." 
                << std::endl;

      exit(1);   
   }

   #endif

   if(independent_parameters_name.get_size() != independent_parameters_number)
   {
      independent_parameters_name.set(independent_parameters_number);
   }

   // Set name of single independent parameter

   independent_parameters_name[independent_parameter_index] = new_independent_parameter_name;
}



/// This method sets new units for the independent parameters.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_independent_parameters_units New units for the independent parameters of the neural network.

void MultilayerPerceptron::set_independent_parameters_units(const Vector<std::string>& new_independent_parameters_units)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_units.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_units(const Vector<std::string>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set units of independent parameters

   independent_parameters_units = new_independent_parameters_units;
}


// void set_independent_parameter_units(int, const std::string&) method

/// This method sets new units for a single independent parameter.
/// Such a value is only used to give the user basic information on the problem at hand.
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_units New units for the independent parameter of index i.

void MultilayerPerceptron
::set_independent_parameter_units(int independent_parameter_index, const std::string& new_independent_parameter_units)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter_units(int, const std::string&) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);   
   }

   #endif

   if(independent_parameters_units.get_size() == 0)
   {
      independent_parameters_units.set(independent_parameters_number);
   }

   // Set units of single independent parameter

   independent_parameters_units[independent_parameter_index] = new_independent_parameter_units;
}


// void set_independent_parameters_description(const Vector<std::string>&) method

/// This method sets new descriptions for the independent parameters.
/// Such values are only used to give the user basic information on the problem at hand.
///
/// @param new_independent_parameters_description New description for the independent parameters of the neural 
/// network.

void MultilayerPerceptron
::set_independent_parameters_description(const Vector<std::string>& new_independent_parameters_description)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_description.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_description(const Vector<std::string>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set description of independent parameters

   independent_parameters_description = new_independent_parameters_description;
}


// void set_independent_parameter_description(int, std::string&) method

/// This method sets a new description for a single independent parameter.
/// Such a value is only used to give the user basic information on the problem at hand.
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_description New description for the independent parameter of index i.

void MultilayerPerceptron::set_independent_parameter_description
(int independent_parameter_index, const std::string& new_independent_parameter_description)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter_description(int, const std::string&) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." 
                << std::endl;

      exit(1);   
   }

   #endif

   if(independent_parameters_description.get_size() == 0)
   {
      independent_parameters_description.set(independent_parameters_number);
   }

   // Set description of single independent parameter
   
   independent_parameters_description[independent_parameter_index] = new_independent_parameter_description;
}


// void set_independent_parameters_mean(const Vector<double>&) method

/// This method sets the mean values of all the independent parameters.
/// These values are used for scaling and unscaling the independent parameters with the mean and standard 
/// deviation method. 
///
/// @param new_independent_parameters_mean New set of mean values for the independent parameters of the neural 
/// network.

void MultilayerPerceptron::set_independent_parameters_mean(const Vector<double>& new_independent_parameters_mean)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_mean.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_mean(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set mean of independent parameters

   independent_parameters_mean = new_independent_parameters_mean;                                                   
}


// void set_independent_parameter_mean(int, double) method

/// This method sets a new mean value for a single independent parameter.
/// Such a value is used for scaling and unscaling the independent parameters with the mean and standard 
/// deviation method. 
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_mean New mean value for the independent parameter of index i.

void MultilayerPerceptron
::set_independent_parameter_mean(int independent_parameter_index, double new_independent_parameter_mean)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter_mean(int, double) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);   
   }

   #endif

   // Set independent parameters mean vector

   int size = independent_parameters_mean.get_size();

   if(size != independent_parameters_number)
   {
      independent_parameters_mean.set(independent_parameters_number, 0.0);
   }

   // Set mean of single independent parameter

   independent_parameters_mean[independent_parameter_index] = new_independent_parameter_mean;
}


// void set_independent_parameters_standard_deviation(const Vector<double>&) method

/// This method sets the standard deviation values of all the independent parameters.
/// These values are used for scaling and unscaling the independent parameters with the mean and standard 
/// deviation method. 
///
/// @param new_independent_parameters_standard_deviation New set of standard deviation values for the 
/// independent parameters of the neural network.

void MultilayerPerceptron
::set_independent_parameters_standard_deviation(const Vector<double>& new_independent_parameters_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_standard_deviation.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_standard_deviation(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set standard deviation of independent parameters

   independent_parameters_standard_deviation = new_independent_parameters_standard_deviation;  
}


// void set_independent_parameter_standard_deviation(int, double) method

/// This method sets a new standard deviation value for a single independent parameter.
/// Such a value is used for scaling and unscaling the independent parameters with the mean and standard 
/// deviation method. 
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_standard_deviation New standard deviation value for that independent parameter.

void MultilayerPerceptron::set_independent_parameter_standard_deviation
(int independent_parameter_index, double new_independent_parameter_standard_deviation)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter_standard_deviation(int, double) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." 
                << std::endl;

      exit(1);   
   }

   #endif

   // Set independent parameters standard deviation vector

   int size = independent_parameters_standard_deviation.get_size();

   if(size != independent_parameters_number)
   {
      independent_parameters_standard_deviation.set(independent_parameters_number, 1.0);
   }

   // Set standard deviation of single independent parameter

   independent_parameters_standard_deviation[independent_parameter_index] = new_independent_parameter_standard_deviation;
}


// void set_independent_parameters_mean_standard_deviation(const Vector< Vector<double> >&) method

/// This method sets both the mean and the standard deviation values of all the independent parameters.
/// The format is a vector of two real vectors. 
/// The first element must contain the mean values values for the independent parameters.
/// The second element must contain the standard deviation values for the independent parameters.
/// These values are used for scaling and unscaling the independent parameters with the mean and standard 
/// deviation method. 
///
/// @param new_independent_parameters_mean_standard_deviation 
/// New set of mean and standard deviation values for the independent parameters of the neural network.

void MultilayerPerceptron::set_independent_parameters_mean_standard_deviation
(const Vector< Vector<double> >& new_independent_parameters_mean_standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   int size = new_independent_parameters_mean_standard_deviation.get_size();

   if(size != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_mean_standard_deviation(const Vector< Vector<double> >& ) method." 
                << std::endl
                << "Number of rows must be 2." << std::endl;

      exit(1);
   }
   else if(new_independent_parameters_mean_standard_deviation[0].get_size() != independent_parameters_number
	    && new_independent_parameters_mean_standard_deviation[1].get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_mean_standard_deviation(const Vector< Vector<double> >& ) method." 
                << std::endl
                << "Number of columns must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   // Check that standard deviation of independent parameters is not zero

   if(display)
   {
      for(int i = 0; i < independent_parameters_number; i++)
      {
         if(new_independent_parameters_mean_standard_deviation[1][i] < 1.0e-99)
         {
            std::cerr << "Flood Warning: MultilayerPerceptron class: " << std::endl
                      << "void set_independent_parameters_mean_standard_deviation(const Vector< Vector<double> >& ) method." << std::endl
                      << "Standard deviation of independent parameter " << i << " is zero." << std::endl;
         }
      }
   }

   #endif

   // Set mean and standard deviation of independent parameters

   independent_parameters_mean = new_independent_parameters_mean_standard_deviation[0];
   independent_parameters_standard_deviation = new_independent_parameters_mean_standard_deviation[1];
}


// void set_independent_parameters_minimum(const Vector<double>&) method

/// This method sets the minimum values of all the independent parameters.
/// These values are used for scaling and unscaling the independent parameters with the minimum and maximum 
/// method.
///
/// @param new_independent_parameters_minimum New set of minimum values for the independent parameters of the 
/// neural network.

void MultilayerPerceptron::set_independent_parameters_minimum(const Vector<double>& new_independent_parameters_minimum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_minimum.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_minimum(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set minimum of independent parameters

   independent_parameters_minimum = new_independent_parameters_minimum;                                                   
}


// void set_independent_parameter_minimum(int, double) method

/// This method sets a minimum value for a single independent parameter.
/// Such a value is used for scaling and unscaling that independent parameter with the minimum and maximum 
/// method.
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_minimum New minimum value for the independent parameter of index i.

void MultilayerPerceptron
::set_independent_parameter_minimum(int independent_parameter_index, double new_independent_parameter_minimum)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_minimum(int, double) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);   
   }

   #endif

   if(independent_parameters_minimum.get_size() != independent_parameters_number)
   {
      independent_parameters_minimum.set(independent_parameters_number, -1.0);
   }

   // Set minimum of single independent parameter

   independent_parameters_minimum[independent_parameter_index] = new_independent_parameter_minimum;
}


// void set_independent_parameters_maximum(const Vector<double>&) method

/// This method sets the maximum values of all the independent parameters.
/// These values are used for scaling and unscaling the independent parameters with the minimum and maximum 
/// method.
///
/// @param new_independent_parameters_maximum New set of maximum values for the independent parameters of the 
/// neural network.

void MultilayerPerceptron::set_independent_parameters_maximum(const Vector<double>& new_independent_parameters_maximum)
{

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_maximum.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_maximum(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set maximum of independent parameters

   independent_parameters_maximum = new_independent_parameters_maximum;  
}


// void set_independent_parameter_maximum(int, double) method

/// This method sets a maximum value for a single independent parameter.
/// Such a value is used for scaling and unscaling that independent parameter with the minimum and maximum 
/// method.
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_maximum New maximum value for the independent parameter of index i.

void MultilayerPerceptron::set_independent_parameter_maximum(int independent_parameter_index, double new_independent_parameter_maximum)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_maximum(int, double) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);   
   }

   #endif

   // Set maximum vector

   if(independent_parameters_maximum.get_size() != independent_parameters_number)
   {
      independent_parameters_maximum.set(independent_parameters_number, 1.0);
   }

   // Set maximum of single independent parameter

   independent_parameters_maximum[independent_parameter_index] = new_independent_parameter_maximum;
}


// void set_independent_parameters_minimum_maximum(const Vector< Vector<double> >&) method

/// This method sets both the minimum and the values of all the independent parameters.
/// The format is a vector of two real vectors.
/// The first element must contain the minimum values values for the independent parameters.
/// The second element must contain the maximum values for the independent parameters.
/// These values are used for scaling and unscaling the independent parameters with the minimum and maximum method.
///
/// @param new_independent_parameters_minimum_maximum New set of minimum and maximum values for the independent 
/// parameters of the neural network.

void MultilayerPerceptron
::set_independent_parameters_minimum_maximum(const Vector< Vector<double> >& new_independent_parameters_minimum_maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_minimum_maximum.get_size() != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                << "Number of rows must be 2." << std::endl;

      exit(1);
   }
   else if(new_independent_parameters_minimum_maximum[0].get_size() != independent_parameters_number
        && new_independent_parameters_minimum_maximum[1].get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_minimum_maximum(const Vector< Vector<double> >&) method." << std::endl
                << "Number of columns must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   // Check that minimum of independent parameters is not greater than their maximum

   for(int i = 0; i < independent_parameters_number; i++)
   {
      if(new_independent_parameters_minimum_maximum[0][i] >= new_independent_parameters_minimum_maximum[1][i])

      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "void set_independent_parameters_minimum_maximum(const Vector< Vector<double> >&) method." 
                   << std::endl
                   << "Minimum of independent parameter "<< i << " is equal or greater than maximum of that parameter."
                   << std::endl;

         exit(1);
      }
   }

   #endif

   // Set minimum and maximum of independent parameters

   independent_parameters_minimum = new_independent_parameters_minimum_maximum[0];
   independent_parameters_maximum = new_independent_parameters_minimum_maximum[1];
}


// void set_independent_parameters_lower_bound(const Vector<double>&) method

/// This method sets the lower bound of all the independent parameters.
/// These values are used for unscaling the independent parameters so that they are not less than the lower 
/// bounds. 
///
/// @param new_independent_parameters_lower_bound New set of lower bounds for the independent parameters of the 
/// neural network.

void MultilayerPerceptron
::set_independent_parameters_lower_bound(const Vector<double>& new_independent_parameters_lower_bound)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_lower_bound.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_lower_bound(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set lower bound of independent parameters

   independent_parameters_lower_bound = new_independent_parameters_lower_bound; 
}


// void set_independent_parameter_lower_bound(int, double) method

/// This method sets the lower bound of a single independent parameter.
/// Such a value is used for unscaling that independent parameter so that it is not less than its lower 
/// bound. 
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_lower_bound New lower bound for that independent parameter.

void MultilayerPerceptron
::set_independent_parameter_lower_bound(int independent_parameter_index, double new_independent_parameter_lower_bound)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter_lower_bound(int, double) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than "
                << "number of independent parameters." << std::endl;

      exit(1);   
   }

   #endif

   // Set lower bound vector

   if(independent_parameters_lower_bound.get_size() != independent_parameters_number)
   {
      independent_parameters_lower_bound.set(independent_parameters_number, -1.0e99);
   }

   // Set lower bound of single independent parameter

   independent_parameters_lower_bound[independent_parameter_index] = new_independent_parameter_lower_bound;
}


// void set_independent_parameters_upper_bound(const Vector<double>&) method

/// This method sets the upper bound of all the independent parameters.
/// These values are used for unscaling the independent parameters so that they are not greater than the 
/// upper bounds. 
///
/// @param new_independent_parameters_upper_bound New set of upper bounds for the independent parameters of the 
/// neural network.

void MultilayerPerceptron
::set_independent_parameters_upper_bound(const Vector<double>& new_independent_parameters_upper_bound)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_upper_bound.get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_upper_bound(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set upper bound of independent parameters

   independent_parameters_upper_bound = new_independent_parameters_upper_bound;
}


// void set_independent_parameter_upper_bound(int, double) method

/// This method sets the upper bound of a single independent parameter.
/// Such a value is used for unscaling that independent parameter so that it is not greater than its upper 
/// bound. 
///
/// @param independent_parameter_index Index of independent parameter.
/// @param new_independent_parameter_upper_bound New upper bound for the independent parameter of index i.

void MultilayerPerceptron::set_independent_parameter_upper_bound
(int independent_parameter_index, double new_independent_parameter_upper_bound)
{
   int independent_parameters_number = get_independent_parameters_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(independent_parameter_index < 0 || independent_parameter_index >= independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameter_upper_bound(int, double) method." << std::endl
                << "Index of independent parameter must be equal or greater than zero and less than number of independent parameters." << std::endl;

      exit(1);   
   }

   #endif

   // Set upper bound vector

   if(independent_parameters_upper_bound.get_size() != independent_parameters_number)
   {
      independent_parameters_upper_bound.set(independent_parameters_number, 1.0e99);
   }

   // Set upper bound of single independent parameter

   independent_parameters_upper_bound[independent_parameter_index] = new_independent_parameter_upper_bound;
}


// void set_independent_parameters_bounds(const Vector< Vector<double> >&) method

/// This method sets both the lower and the upper bounds of all the independent parameters.
/// The format is a vector of two real vectors. 
/// The first element must contain the lower bound values values for the independent parameters.
/// The second element must contain the upper bound values for the independent parameters.
/// These values are used for unscaling the independent parameters so that they are neither less than the 
/// lower bounds nor greater than the upper bounds. 
///
/// @param new_independent_parameters_bounds New set of lower and upper bounds for the independent 
/// parameters of the neural network.

void MultilayerPerceptron::set_independent_parameters_bounds
(const Vector< Vector<double> >& new_independent_parameters_bounds)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int independent_parameters_number = get_independent_parameters_number();

   if(new_independent_parameters_bounds.get_size() != 2)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_bounds(const Vector< Vector<double> >&) method." 
                << std::endl
                << "Number of rows must be 2." << std::endl;

      exit(1);
   }
   else if(new_independent_parameters_bounds[0].get_size() != independent_parameters_number
	    && new_independent_parameters_bounds[1].get_size() != independent_parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl 
                << "void set_independent_parameters_bounds(const Vector< Vector<double> >&) method." 
                << std::endl
                << "Number of columns must be equal to number of independent parameters." << std::endl;

      exit(1);
   }

   #endif

   // Set lower and upper bounds of independent parameters

   independent_parameters_lower_bound = new_independent_parameters_bounds[0];
   independent_parameters_upper_bound = new_independent_parameters_bounds[1];
}


// void set_independent_parameters_statistics(const Vector< Vector<double> >&) method
/// This method sets both the lower and the upper bounds of all the independent parameters.
/// The format is a vector of six real vectors. 
///
/// <ul>
/// <li> Mean of independent parameters.
/// <li> Standard deviation of independent parameters.
/// <li> Minimum of independent parameters.
/// <li> Maximum of independent parameters.
/// </ul>
///
/// @param new_independent_parameters_statistics New statistics values for the independent 
/// parameters of the neural network.

void MultilayerPerceptron
::set_independent_parameters_statistics(const Vector< Vector<double> >& new_independent_parameters_statistics)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_independent_parameters_statistics.get_size() != 4)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_independent_parameters_statistics(const Vector< Vector<double> >&) method." << std::endl
                << "Size must be 6." << std::endl;

      exit(1);
   }

   #endif

   // Set all statistics
 
   set_independent_parameters_mean(new_independent_parameters_statistics[0]);
   set_independent_parameters_standard_deviation(new_independent_parameters_statistics[1]);

   set_independent_parameters_minimum(new_independent_parameters_statistics[2]);
   set_independent_parameters_maximum(new_independent_parameters_statistics[3]);
}


// void set_parameters(const Vector<double>&) method

/// This method sets all the parameters (neural parameters and independent parameters) from a single vector.
///
/// @param new_parameters New set of parameter values. 

void MultilayerPerceptron::set_parameters(const Vector<double>& new_parameters)
{
   // Control sentence (if debug)

   int independent_parameters_number = get_independent_parameters_number();

   #ifdef _DEBUG 

   int size = new_parameters.get_size();

   int parameters_number = get_parameters_number();

   if(size != parameters_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void set_parameters(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of parameters." << std::endl;

      exit(1);
   }

   #endif

   if((inputs_number != 0 && outputs_number != 0) && independent_parameters_number == 0)
   {// Only neural parameters 

      set_neural_parameters(new_parameters);
   }
   else if((inputs_number == 0 && outputs_number == 0) && independent_parameters_number != 0)
   {// Only independent parameters

      unscale_independent_parameters(new_parameters);
   }
   else if((inputs_number != 0 && outputs_number != 0) && independent_parameters_number != 0)
   {// Both neural and independent parameters

      // Neural parameters

      int neural_parameters_number = get_neural_parameters_number();

      Vector<double> neural_parameters = new_parameters.extract(0, neural_parameters_number);

      set_neural_parameters(neural_parameters);

      // Independent parameters

      Vector<double> scaled_independent_parameters 
	   = new_parameters.extract(neural_parameters_number, independent_parameters_number);

      unscale_independent_parameters(scaled_independent_parameters);
   }
   else 
   {// None neural neither independent parameters
      return;
   }
}


// void set_scaling_method(ScalingMethod) method

/// This method sets a unique method for scaling inputs, unscaling outputs and scaling and unscaling 
/// the independent parameters.
///
/// @param new_scaling_method New scaling and unscaling method for the neural network and the independent parameters.

void MultilayerPerceptron::set_scaling_method
(const MultilayerPerceptron::ScalingMethod& new_scaling_method)
{
   inputs_scaling_method = new_scaling_method;   
   outputs_unscaling_method = new_scaling_method;
   independent_parameters_scaling_method = new_scaling_method;   
}


// void set_display(bool) method

/// This method sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
///
/// @param new_display Display value.

void MultilayerPerceptron::set_display(bool new_display)
{
   display = new_display;
}


// void set_display_range_out_warning(bool) method

/// This method sets a new display out of range warning value. 
/// If it is set to true a warning message is to be displayed when inputs fall outside minimum and maximums.
/// if it is set to false that warning message is not to be displayed
///
/// @param new_display_range_out_warning Display value for the out of range warning.

void MultilayerPerceptron::set_display_range_out_warning(bool new_display_range_out_warning)
{
   display_range_out_warning = new_display_range_out_warning;
}


// void initialize_biases(double) method

/// This method initializes the biases of all the perceptrons in the neural network with a given value. 
/// @param value Biases initialization value. 

void MultilayerPerceptron::initialize_biases(double value)
{
   // Hidden layers

   int hidden_layers_number = get_hidden_layers_number();   

   for(int i = 0; i < hidden_layers_number; i++)
   {
	   for(int j = 0; j < hidden_layers_size[i]; j++)
	   {
	      hidden_layers[i][j].initialize_bias(value);
	   }
   }

   // Output layer

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer[i].initialize_bias(value);
   }
}


// void initialize_synaptic_weights(double) method

/// This method initializes the synaptic weights of all the perceptrons in the neural network with a given value. 
/// @param value Synaptic weights initialization value. 

void MultilayerPerceptron::initialize_synaptic_weights(double value)
{
   // Hidden layers

   int hidden_layers_number = get_hidden_layers_number();   

   for(int i = 0; i < hidden_layers_number; i++)
   {
	   for(int j = 0; j < hidden_layers_size[i]; j++)
	   {
	      hidden_layers[i][j].initialize_synaptic_weights(value);
	   }
   }

   // Output layer

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer[i].initialize_synaptic_weights(value);
   }
}


// void initialize_neural_parameters(double) method

/// This method initializes all the biases and synaptic weights in the neural newtork with a given value.
/// @param value Neural parameters initialization value. 

void MultilayerPerceptron::initialize_neural_parameters(double value)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number, value);

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_uniform(void) method

/// This method initializes all the biases and synaptic weights in the neural newtork at random with values comprised 
/// between -1 and +1.

void MultilayerPerceptron::initialize_neural_parameters_uniform(void)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_uniform();

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_uniform(double, double) method

/// This method initializes all the biases and synaptic weights in the neural network at random with values 
/// comprised between a minimum and a maximum values.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.

void MultilayerPerceptron::initialize_neural_parameters_uniform(double minimum, double maximum)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_uniform(minimum, maximum);

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_uniform(const Vector<double>&, const Vector<double>&) method

/// This method initializes all the biases and synaptic weights in the neural network at random, with values 
/// comprised between different minimum and maximum numbers for each parameter.
/// @param minimum Vector of minimum initialization values.
/// @param maximum Vector of maximum initialization values.

void MultilayerPerceptron
::initialize_neural_parameters_uniform(const Vector<double>& minimum, const Vector<double>& maximum)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_uniform(minimum, maximum);

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_uniform(const Vector< Vector<double> >&) method

/// This method initializes all the biases and synaptic weights in the neural network at random, with values 
/// comprised between a different minimum and maximum numbers for each parameter.
/// All minimum are maximum initialization values must be given from a vector of two real vectors.
/// The first element must contain the minimum inizizalization value for each parameter.
/// The second element must contain the maximum inizizalization value for each parameter.
/// @param minimum_maximum Vector of minimum and maximum initialization values.

void MultilayerPerceptron::initialize_neural_parameters_uniform(const Vector< Vector<double> >& minimum_maximum)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_uniform(minimum_maximum[0], minimum_maximum[1]);

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_normal(void) method

/// This method initializes all the biases and synaptic weights in the newtork with random values chosen from a 
/// normal distribution with mean 0 and standard deviation 1.

void MultilayerPerceptron::initialize_neural_parameters_normal(void)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_normal();

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_normal(double, double) method

/// This method initializes all the biases and synaptic weights in the neural network with random random values 
/// chosen from a normal distribution with a given mean and a given standard deviation.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.

void MultilayerPerceptron
::initialize_neural_parameters_normal(double mean, double standard_deviation)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_normal(mean, standard_deviation);

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_normal(const Vector<double>&, const Vector<double>&) method

/// This method initializes all the biases an synaptic weights in the neural network with random values chosen 
/// from normal distributions with different mean and standard deviation for each parameter.
/// @param mean Vector of mean values.
/// @param standard_deviation Vector of standard deviation values.

void MultilayerPerceptron
::initialize_neural_parameters_normal(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_normal(mean, standard_deviation);

   set_neural_parameters(neural_parameters);
}


// void initialize_neural_parameters_normal(const Vector< Vector<double> >&) method

/// This method initializes all the biases and synaptic weights in the neural network with random values chosen 
/// from normal distributions with different mean and standard deviation for each parameter.
/// All mean and standard deviation values are given from a vector of two real vectors.
/// The first element must contain the mean value for each parameter.
/// The second element must contain the standard deviation value for each parameter.
/// @param mean_standard_deviation Vector of mean and standard deviation values.

void MultilayerPerceptron::initialize_neural_parameters_normal(const Vector< Vector<double> >& mean_standard_deviation)
{
   int neural_parameters_number = get_neural_parameters_number();

   Vector<double> neural_parameters(neural_parameters_number);

   neural_parameters.initialize_normal(mean_standard_deviation[0], mean_standard_deviation[1]);

   set_neural_parameters(neural_parameters);
}


// void initialize_independent_parameters(double) method

/// This method initializes the independent parameters associated to the neural network with a given value. 
/// @param value Initialization value. 

void MultilayerPerceptron::initialize_independent_parameters(double value)
{
   independent_parameters.initialize(value);

   bound_independent_parameters();
}


// void initialize_independent_parameters_uniform(void) method

/// This method initializes the independent parameters associated to the newtork at random with values comprised 
/// between -1 and +1.

void MultilayerPerceptron::initialize_independent_parameters_uniform(void)
{
   independent_parameters.initialize_uniform();

   bound_independent_parameters();
}


// void initialize_independent_parameters_uniform(double, double) method

/// This method initializes the independent parameters associated to the neural network at random with values 
/// comprised between a minimum and a maximum values.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.

void MultilayerPerceptron::initialize_independent_parameters_uniform(double minimum, double maximum)
{
   independent_parameters.initialize_uniform(minimum, maximum);

   bound_independent_parameters();
}


// void initialize_independent_parameters_uniform(const Vector<double>&, const Vector<double>&) method

/// This method initializes the independent parameters associated to the neural network at random with values 
/// comprised between different minimum and maximum numbers for each independent parameter.
/// @param minimum Vector of minimum initialization values.
/// @param maximum Vector of maximum initialization values.

void MultilayerPerceptron
::initialize_independent_parameters_uniform(const Vector<double>& minimum, const Vector<double>& maximum)
{
   independent_parameters.initialize_uniform(minimum, maximum);

   bound_independent_parameters();
}


// void initialize_independent_parameters_uniform(const Vector< Vector<double> >&) method

/// This method initializes the independent parameters associated to the neural network at random values comprised
/// between different minimum and maximum numbers for each independent parameter.
/// All minimum and maximum values are given from a vector of two real vectors.
/// The first element must contain the minimum inizizalization value for each independent parameter.
/// The second element must contain the maximum inizizalization value for each independent parameter.
/// @param minimum_maximum Matrix of minimum and maximum initialization values.

void MultilayerPerceptron::initialize_independent_parameters_uniform(const Vector< Vector<double> >& minimum_maximum)
{
   independent_parameters.initialize_uniform(minimum_maximum[0], minimum_maximum[1]);

   bound_independent_parameters();
}



// void initialize_independent_parameters_normal(void) method

/// This method initializes the independent parameters associated to the newtork with random values chosen from a 
/// normal distribution with mean 0 and standard deviation 1.

void MultilayerPerceptron::initialize_independent_parameters_normal(void)
{
   independent_parameters.initialize_normal();

   bound_independent_parameters();
}


// void initialize_independent_parameters_normal(double, double) method

/// This method initializes the independent parameters associated to the neural network with random values chosen 
/// from a normal distribution with a given mean and a given standard deviation.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.

void MultilayerPerceptron::initialize_independent_parameters_normal(double mean, double standard_deviation)
{
   independent_parameters.initialize_normal(mean, standard_deviation);

   bound_independent_parameters();
}


// void initialize_independent_parameters_normal(const Vector<double>&, const Vector<double>&) method

/// This method initializes the independent parameters associated to the neural network with random values chosen 
/// from normal distributions with different mean and standard deviation for each independent parameter.
/// @param mean Vector of mean values.
/// @param standard_deviation Vector of standard deviation values.

void MultilayerPerceptron::initialize_independent_parameters_normal
(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   independent_parameters.initialize_normal(mean, standard_deviation);

   bound_independent_parameters();
}


// void initialize_independent_parameters_normal(const Vector< Vector<double> >&) method

/// This method initializes the independent parameters associated to the neural network with random values chosen 
/// from normal distributions with different mean and standard deviation for each independent parameter.
/// All mean and standard deviation values are given from a vector of two real vectors.
/// The first element must contain the mean value for each independent parameter.
/// The second element must contain the standard deviation value for each independent parameter.
/// @param mean_standard_deviation Vector of mean and standard deviation vectors.

void MultilayerPerceptron::initialize_independent_parameters_normal(const Vector< Vector<double> >& mean_standard_deviation)
{
   independent_parameters.initialize_normal(mean_standard_deviation[0], mean_standard_deviation[1]);

   bound_independent_parameters();
}


// void initialize_parameters(double) method

/// This method initializes all the neural and the independent parameters with a given value. 

void MultilayerPerceptron::initialize_parameters(double value)
{
   initialize_neural_parameters(value);
   initialize_independent_parameters(value);
}


// void initialize_parameters_uniform(void) method

/// This method initializes all the parameters in the newtork (biases and synaptic weiths + independent parameters) 
/// at random with values comprised between -1 and +1.

void MultilayerPerceptron::initialize_parameters_uniform(void)
{
   initialize_neural_parameters_uniform();  
   initialize_independent_parameters_uniform();  
}


// void initialize_parameters_uniform(double, double) method

/// This method initializes all the parameters in the newtork (biases and synaptic weiths + independent 
/// parameters) at random with values comprised between a given minimum and a given maximum values.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.

void MultilayerPerceptron::initialize_parameters_uniform(double minimum, double maximum)
{
   initialize_neural_parameters_uniform(minimum, maximum);  
   initialize_independent_parameters_uniform(minimum, maximum);  
}


// void initialize_parameters_uniform(const Vector<double>&, const Vector<double>&) method

/// This method initializes all the parameters in the newtork (biases and synaptic weiths + independent 
/// parameters) at random with values comprised between a different minimum and maximum numbers for each free 
/// parameter.
/// @param minimum Vector of minimum initialization values.
/// @param maximum Vector of maximum initialization values.

void MultilayerPerceptron::initialize_parameters_uniform(const Vector<double>& minimum, const Vector<double>& maximum)
{
   initialize_neural_parameters_uniform(minimum, maximum);  
   initialize_independent_parameters_uniform(minimum, maximum);  
}


// void initialize_parameters_uniform(const Vector< Vector<double> >&) method

/// This method initializes all the parameters in the newtork (biases and synaptic weiths + independent 
/// parameters) values comprised between a different minimum and maximum numbers for each parameter.
/// Minimum and maximum initialization values are given from a vector of two real vectors.
/// The first element must contain the minimum initialization value for each parameter.
/// The second element must contain the maximum initialization value for each parameter.
/// @param minimum_maximum Vector of minimum and maximum initialization vectors.

void MultilayerPerceptron::initialize_parameters_uniform(const Vector< Vector<double> >& minimum_maximum)
{
   initialize_neural_parameters_uniform(minimum_maximum);  
   initialize_independent_parameters_uniform(minimum_maximum);  
}


// void initialize_parameters_normal(void) method

/// This method initializes all the parameters in the neural newtork (biases and synaptic weiths + independent 
/// parameters) at random with values chosen from a normal distribution with mean 0 and standard deviation 1.

void MultilayerPerceptron::initialize_parameters_normal(void)
{
   initialize_neural_parameters_normal();  
   initialize_independent_parameters_normal();  
}


// void initialize_parameters_normal(double, double) method

/// This method initializes all the parameters in the newtork (biases and synaptic weiths + independent 
/// parameters) at random with values chosen from a normal distribution with a given mean and a given standard 
/// deviation.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.

void MultilayerPerceptron::initialize_parameters_normal(double mean, double standard_deviation)
{
   initialize_neural_parameters_normal(mean, standard_deviation);  
   initialize_independent_parameters_normal(mean, standard_deviation);  
}


// void initialize_parameters_normal(const Vector<double>&, const Vector<double>&) method

/// This method initializes all the parameters in the neural newtork (biases and synaptic weiths + 
/// independent parameters) at random with values chosen from normal distributions with a given mean and a given 
/// standard deviation for each parameter.
/// @param mean Vector of minimum initialization values.
/// @param standard_deviation Vector of maximum initialization values.

void MultilayerPerceptron
::initialize_parameters_normal(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   initialize_neural_parameters_normal(mean, standard_deviation);  
   initialize_independent_parameters_normal(mean, standard_deviation);  
}


// void initialize_parameters_normal(const Vector< Vector<double> >&) method

/// This method initializes all the parameters in the newtork (biases and synaptic weiths + independent 
/// parameters) at random with values chosen from normal distributions with a given mean and a given standard 
/// deviation for each parameter.
/// All mean and standard deviation values are given from a vector of two real vectors.
/// The first element must contain the mean value for each parameter.
/// The second element must contain the standard deviation value for each parameter.
/// @param mean_standard_deviation Mean and standard deviation vectors.

void MultilayerPerceptron::initialize_parameters_normal(const Vector< Vector<double> >& mean_standard_deviation)
{
   initialize_neural_parameters_normal(mean_standard_deviation);  
   initialize_independent_parameters_normal(mean_standard_deviation);  
}


// void check_input_range(const Vector<double>&) method

/// This method chechs whether the inputs to the neural network have the right size. 
/// If not, it displays an error message and exits the program. 
/// It also checks whether the input values are inside the range defined by the minimum and maximum values, and 
/// displays a warning message if they are outside.
/// @param input Set of inputs to the neural network.

void MultilayerPerceptron::check_input_range(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = input.get_size();

   if(size != inputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void check_input_range(const Vector<double>&) method." << std::endl
                << "Size of input must be equal to number of inputs." << std::endl;

      exit(1);
   }   

   #endif

   // Check input

   if(display_range_out_warning)
   {
      for(int i = 0; i < inputs_number; i++)
      {
         if(input[i] < input_variables_minimum[i])
         {
            std::cout << "Flood Warning: MultilayerPerceptron class." << std::endl
                      << "void check_input_range(const Vector<double>&) method."  << std::endl
                      << "Input variable " << i << " is less than minimum." << std::endl;                  
         }
         if(input[i] > input_variables_maximum[i])
         {
            std::cout << "Flood Warning: MultilayerPerceptron class." << std::endl
                      << "void check_input_range(const Vector<double>&) method." << std::endl
                      << "Input variable " << i << " is greater than maximum." << std::endl;
         }
      }
   }
}


// Vector<double> calculate_scaled_input(const Vector<double>&) method

/// This method preprocesses the inputs to the neural network in order to obtain a set of scaled inputs. 
/// @param input Set of inputs to the neural network.

Vector<double> MultilayerPerceptron::calculate_scaled_input(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = input.get_size();

   if(size != inputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_scaled_input(const Vector<double>&) method." << std::endl
                << "Size of input must be equal to number of inputs." << std::endl;

      exit(1);
   }   

   #endif

   // Preprocess input depending on the scaling and unscaling method

   switch(inputs_scaling_method)
   {
      case None:
      {
         return(input); 
      }
      break;
                                     
      case MeanStandardDeviation:
      {
         // Control sentence (if debug)

         #ifdef _DEBUG 

	      int mean_size = input_variables_mean.get_size();

         if(mean_size != inputs_number) 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "Vector<double> calculate_scaled_input(const Vector<double>&) method." << std::endl
                      << "Size of mean of input variables must be equal to number of inputs." 
					       << std::endl;

            exit(1);
         }   

   	     int standard_deviation_size = input_variables_standard_deviation.get_size();

         if(standard_deviation_size != inputs_number) 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "Vector<double> calculate_scaled_input(const Vector<double>&) method." << std::endl
                      << "Size of standard deviation of input variables must be equal to number of inputs." 
					  << std::endl;

            exit(1);
         }   

         #endif

         Vector<double> scaled_input(inputs_number);

         for(int i = 0; i < inputs_number; i++)
         {            
            if(input_variables_standard_deviation[i] < 1e-99)
            {      
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class." << std::endl
                            << "Vector<double> calculate_scaled_input(Vector<double>&) method." << std::endl
                            << "Standard deviation of input variable " << i << " is zero." << std::endl
                            << "Those inputs won't be scaled." << std::endl;
               }
               
               scaled_input[i] = input[i];
            }      
            else
            {             
               scaled_input[i] = (input[i] - input_variables_mean[i])/input_variables_standard_deviation[i];
            }
         }       

		 return(scaled_input);
      }
      break;

      case MinimumMaximum:
      {
         // Control sentence (if debug)

         #ifdef _DEBUG 

	     int minimum_size = input_variables_minimum.get_size();
		 int maximum_size = input_variables_maximum.get_size();

         if(minimum_size != inputs_number || maximum_size != inputs_number) 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "Vector<double> calculate_scaled_input(const Vector<double>&) method." << std::endl
                      << "Size of minimum and maximum of input variables must be equal to number of inputs." 
					  << std::endl;

            exit(1);
         }   

         #endif


         Vector<double> scaled_input(inputs_number);

         for(int i = 0; i < inputs_number; i++)
         {
            if(input_variables_maximum[i]-input_variables_minimum[i] < 1e-99)
            {      
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class" << std::endl
                            << "Vector<double> calculate_scaled_input(Vector<double>&) method." << std::endl               
                            << "Minimum and maximum values of input variable " << i << " are equal." << std::endl
                            << "Those inputs won't be scaled." << std::endl;
               }
               
               scaled_input[i] = input[i];
            }      
            else
            {             
               scaled_input[i] = 2.0*(input[i] - input_variables_minimum[i])
               /(input_variables_maximum[i]-input_variables_minimum[i]) - 1.0;
            }
         }

		 return(scaled_input);
      }            
      break;

      default:
      {
         std::cerr << "Flood Warning: MultilayerPerceptron class" << std::endl
                   << "Vector<double> calculate_scaled_input(Vector<double>&) method." << std::endl               
                   << "Unknown scaling and unscaling method." << std::endl;

         exit(1); 
      }
      break;
   }
}  


// Vector<double> calculate_hidden_layer_combination(int, const Vector<double>&) method

/// This method returns the combination to every perceptron in the hidden layer as a function of the input to that layer. 
/// @param i Index of hidden layer. 
/// @param hidden_layer_input Input to the hidden layer with the previous index. 

Vector<double> MultilayerPerceptron::calculate_hidden_layer_combination
(int i, const Vector<double>& hidden_layer_input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = hidden_layer_input.get_size();

   int hidden_layer_inputs_number = get_hidden_layer_inputs_number(i);

   if(size != hidden_layer_inputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_combination(int, const Vector<double>&) method."  << std::endl
                << "Size of input to hidden layer must be equal to number of layer inputs." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate combination to hidden layer

   Vector<double> hidden_layer_combination(hidden_layers_size[i]);
   
   for(int j = 0; j < hidden_layers_size[i]; j++)
   {         
      hidden_layer_combination[j] = hidden_layers[i][j].calculate_combination(hidden_layer_input);
   }             
   
   return(hidden_layer_combination);
}


// Vector<double> calculate_hidden_layer_activation(int, const Vector<double>&) method

/// This method returns the output from every perceptron in a hidden layer as a function of their combination. 
/// @param i Index of hidden layer. 
/// @param hidden_layer_combination Combination to every neuron in the hidden layer with the previous index. 

Vector<double> MultilayerPerceptron::
calculate_hidden_layer_activation(int i, const Vector<double>& hidden_layer_combination)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero." << std::endl;

      exit(1);
   }   

   int hidden_layers_number = get_hidden_layers_number();

   if(i >= hidden_layers_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be less than number of hidden layers." << std::endl;

      exit(1);
   }   

   int size = hidden_layer_combination.get_size();

   if(size != hidden_layers_size[i]) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation(int, const Vector<double>&) method." << std::endl
                << "Size must be equal to number of hidden neurons." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate output from hidden layer

   Vector<double> hidden_layer_output(hidden_layers_size[i]);
   
   for(int j = 0; j < hidden_layers_size[i]; j++)
   {
      hidden_layer_output[j] = hidden_layers[i][j].calculate_activation(hidden_layer_combination[j]);
   }

   return(hidden_layer_output);
}  


// Vector<double> calculate_hidden_layer_activation_derivative(int, const Vector<double>&) method

/// This method returns the activation derivative from every perceptron in a hidden layer as a function of their
/// combination. 
/// @param i Index of hidden layer index. 
/// @param hidden_layer_combination Combination to every neuron in the hidden layer with the previous index. 

Vector<double> MultilayerPerceptron::calculate_hidden_layer_activation_derivative
(int i, const Vector<double>& hidden_layer_combination)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation_derivative(int, const Vector<double>&) method." 
                << std::endl
                << "Index of hidden layer must be equal or greater than zero." << std::endl;

      exit(1);
   }   

   int hidden_layers_number = get_hidden_layers_number();

   if(i >= hidden_layers_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation_derivative(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be less than number of hidden layers." << std::endl;

      exit(1);
   }   

   int size = hidden_layer_combination.get_size();

   if(size != hidden_layers_size[i]) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation_derivative(int, const Vector<double>&) method." << std::endl
                << "Size must be equal to number of hidden neurons." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate activation derivative from hidden layer

   Vector<double> hidden_layer_activation_derivative(hidden_layers_size[i]);

   // Calculate output derivative from hidden layer

   for(int j = 0; j < hidden_layers_size[i]; j++)
   {          
      hidden_layer_activation_derivative[j] 
      = hidden_layers[i][j].calculate_activation_derivative(hidden_layer_combination[j]);      
   }

   return(hidden_layer_activation_derivative);
}


// Vector<double> calculate_hidden_layer_activation_second_derivative(int, const Vector<double>&) method

/// This method returns the activation second derivative from every perceptron in a hidden layer as a function of their
/// combination. 
/// @param i Index of hidden layer index. 
/// @param hidden_layer_combination Combination to every neuron in the hidden layer with the previous index. 

Vector<double> MultilayerPerceptron::calculate_hidden_layer_activation_second_derivative
(int i, const Vector<double>& hidden_layer_combination)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation_second_derivative(int, const Vector<double>&) method." 
                << std::endl
                << "Index of hidden layer must be equal or greater than zero." << std::endl;

      exit(1);
   }   

   int hidden_layers_number = get_hidden_layers_number();

   if(i >= hidden_layers_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation_second_derivative(int, const Vector<double>&) method." 
                << std::endl
                << "Index of hidden layer must be less than number of hidden layers." << std::endl;

      exit(1);
   }   

   int size = hidden_layer_combination.get_size();

   if(size != hidden_layers_size[i]) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_activation_second_derivative(int, const Vector<double>&) method." 
                << std::endl
                << "Size must be equal to number of hidden neurons." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate activation second derivative from hidden layer

   Vector<double> hidden_layer_activation_second_derivative(hidden_layers_size[i]);

   // Calculate output second derivative from hidden layer

   for(int j = 0; j < hidden_layers_size[i]; j++)
   {          
      hidden_layer_activation_second_derivative[j] 
      = hidden_layers[i][j].calculate_activation_second_derivative(hidden_layer_combination[j]);      
   }

   return(hidden_layer_activation_second_derivative);
}


// Vector<double> calculate_hidden_layer_output(int, const Vector<double>&) method

/// This method returns the output from every perceptron in a hidden layer as a function of their input. 
/// @param i Index of hidden layer index. 
/// @param hidden_layer_input Input vector to the hidden layer with the previous index. 

Vector<double> MultilayerPerceptron::
calculate_hidden_layer_output(int i, const Vector<double>& hidden_layer_input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_output(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero." << std::endl;

      exit(1);
   }   

   int hidden_layers_number = get_hidden_layers_number();

   if(i >= hidden_layers_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_output(int, const Vector<double>&) method." 
                << std::endl
                << "Index of hidden layer must be less than number of hidden layers." << std::endl;

      exit(1);
   }   

   int size = hidden_layer_input.get_size();

   int hidden_layer_inputs_number = get_hidden_layer_inputs_number(i);

   if(size != hidden_layer_inputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_hidden_layer_output(int, const Vector<double>&) method." 
                << std::endl
                << "Size must be equal to number of inputs to hidden layer." << std::endl;

      exit(1);
   }   

   #endif

   return(calculate_hidden_layer_activation(i, calculate_hidden_layer_combination(i, hidden_layer_input)));
}


// Vector<double> calculate_output_layer_combination(const Vector<double>&) method

/// This method returns the combination to every perceptron in the ouptut layer as a function of the output from 
/// the neurons of the last hidden layer. 
/// @param last_hidden_layer_output Output from every neuron in the last hidden layer. 

Vector<double> MultilayerPerceptron::calculate_output_layer_combination(const Vector<double>& last_hidden_layer_output)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = last_hidden_layer_output.get_size();

   int hidden_layers_number = get_hidden_layers_number();

   if(size != hidden_layers_size[hidden_layers_number-1]) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_output_layer_combination(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of neurons of last hidden layer." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate combination to hidden layer

   Vector<double> output_layer_combination(outputs_number);            
               
   // Calculate combination to output layer

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer_combination[i] = output_layer[i].calculate_combination(last_hidden_layer_output);
   }
   
   return(output_layer_combination);                  
}


// Vector<double> calculate_output_layer_activation(const Vector<double>&) method

/// This method returns the output from every perceptron in the ouptut layer as a function of their combination.
/// @param output_layer_combination Combination to every neuron in the output layer. 

Vector<double> MultilayerPerceptron::calculate_output_layer_activation(const Vector<double>& output_layer_combination)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = output_layer_combination.get_size();

   if(size != outputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_output_layer_activation(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate output

   Vector<double> output_layer_output(outputs_number, 0.0);
   
   for(int i = 0; i < outputs_number; i++)
   {  
      output_layer_output[i] = output_layer[i].calculate_activation(output_layer_combination[i]);
   }

   return(output_layer_output);
}  


// Vector<double> calculate_output_layer_activation_derivative(const Vector<double>&) method

/// This method returns the output derivative from every perceptron in the ouptut layer as a function of 
/// their combination. 
/// @param output_layer_combination Combination to every neuron in the output layer. 

Vector<double> MultilayerPerceptron::
calculate_output_layer_activation_derivative(const Vector<double>& output_layer_combination)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = output_layer_combination.get_size();

   if(size != outputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_output_layer_activation_derivative(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate output derivative

   Vector<double> output_layer_activation_derivative(outputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer_activation_derivative[i] 
      = output_layer[i].calculate_activation_derivative(output_layer_combination[i]);
   }

   return(output_layer_activation_derivative);
}  


// Vector<double> calculate_output_layer_activation_second_derivative(const Vector<double>&) method

/// This method returns the output second derivative from every perceptron in the ouptut layer as a function of 
/// their combination. 
/// @param output_layer_combination Combination to every neuron in the output layer. 

Vector<double> MultilayerPerceptron::
calculate_output_layer_activation_second_derivative(const Vector<double>& output_layer_combination)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = output_layer_combination.get_size();

   if(size != outputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_output_layer_activation_second_derivative(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }   

   #endif

   // Calculate output derivative

   Vector<double> output_layer_activation_second_derivative(outputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer_activation_second_derivative[i] 
      = output_layer[i].calculate_activation_second_derivative(output_layer_combination[i]);
   }

   return(output_layer_activation_second_derivative);
}  


// Vector<double> calculate_output_layer_output(const Vector<double>&) method

Vector<double> MultilayerPerceptron::
calculate_output_layer_output(const Vector<double>& output_layer_input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = output_layer_input.get_size();

   int output_layer_inputs_number = get_output_layer_inputs_number();

   if(size != output_layer_inputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_output_layer_output(const Vector<double>&) method." 
				<< std::endl
                << "Size must be equal to number of inputs to output layer." << std::endl;

      exit(1);
   }   

   #endif

   return(calculate_output_layer_activation(calculate_output_layer_combination(output_layer_input)));
}


// Vector<double> calculate_unscaled_output(const Vector<double>&) method

/// This method postprocesses the outputs from the neural network in order to obtain a set of unscaled outputs. 
/// @param scaled_output Set of outputs from the neural network.

Vector<double> MultilayerPerceptron::calculate_unscaled_output(const Vector<double>& scaled_output)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = scaled_output.get_size();

   if(size != outputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_unscaled_output(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }   

   #endif

   // Postprocess output 

   switch(outputs_unscaling_method)
   {
      case None:
      {
         return(scaled_output);
      }//end none
      break;

      case MeanStandardDeviation:
      {
         Vector<double> unscaled_output(outputs_number);

         for(int i = 0; i < outputs_number; i++)
         {
            if(output_variables_standard_deviation[i] < 1e-99)
            {      
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class." << std::endl
                            << "void calculate_unscaled_output(Vector<double>&) method." << std::endl               
                            << "Standard deviation of output variable " << i << " is zero." << std::endl 
                            << "Those outputs won't be unscaled." << std::endl;
               }
               
               unscaled_output[i] = scaled_output[i];
            }      
            else
            {
               unscaled_output[i] = scaled_output[i]*output_variables_standard_deviation[i] + output_variables_mean[i];
            }
         }

         return(unscaled_output);

      }// end mean and standard deviation
      break;

      case MinimumMaximum:
      {
         Vector<double> unscaled_output(outputs_number);

         for(int i = 0; i < outputs_number; i++)
         {
            if(output_variables_maximum[i]-output_variables_minimum[i] < 1e-99)
            {      
               if(display)
               {
                  std::cout << "Flood Warning: MultilayerPerceptron class." << std::endl
                            << "void calculate_unscaled_output(Vector<double>&) method." << std::endl               
                            << "Minimum and maximum values of output variable " << i << " are equal." << std::endl
                            << "Those outputs won't be unscaled."
                            << std::endl;
               }

               unscaled_output[i] = scaled_output[i];
            }      
            else
            {
               unscaled_output[i] = 0.5*(scaled_output[i] + 1.0)*(output_variables_maximum[i]-output_variables_minimum[i]) 
               + output_variables_minimum[i]; 
            }
         }

         return(unscaled_output);

      }// end minimum and maximum
      break;       

      default:
      {
         std::cerr << "Flood Warning: MultilayerPerceptron class." << std::endl
                   << "void calculate_unscaled_output(Vector<double>&) method." << std::endl               
                   << "Unknown scaling and unscaling method." << std::endl;
 
         exit(1);
      }// end default
      break;

   }// end switch
}  


// Vector<double> calculate_bounded_output(const Vector<double>&) method

/// This method postprocesses the outputs from the neural network in order to obtain a new set of outputs falling 
/// in the range defined by the lower and the upper bounds. 
/// @param output Set of outputs from the neural network.

Vector<double> MultilayerPerceptron::calculate_bounded_output(const Vector<double>& unbounded_output)
{            
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = unbounded_output.get_size();

   if(size != outputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_bounded_output(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of outputs." << std::endl;

      exit(1);
   }   

   #endif

   // Apply lower and upper bounds

   if(output_variables_lower_bound.get_size() != outputs_number && output_variables_upper_bound.get_size() != outputs_number)
   {
      return(unbounded_output);
   }
   else if(output_variables_lower_bound.get_size() == outputs_number && output_variables_upper_bound.get_size() == outputs_number)
   {
      return(unbounded_output.calculate_lower_upper_bounded(output_variables_lower_bound, output_variables_upper_bound));	  
   }
   else if(output_variables_lower_bound.get_size() == outputs_number)
   {
      return(unbounded_output.calculate_lower_bounded(output_variables_lower_bound));
   }
   else if(output_variables_upper_bound.get_size() == outputs_number)
   {
      return(unbounded_output.calculate_upper_bounded(output_variables_upper_bound));   
   }
   else
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_bounded_output(const Vector<double>&) method." << std::endl
                << "Unknown lower and upper bounds case." << std::endl;

      exit(1);   
   }
}  


// Vector<double> calculate_output(const Vector<double>&) method

/// This method calculates the output vector from the neural network in response to an input vector, when no 
/// boundary conditions are imposed.
/// The activity for that is the following:
/// check_input_range(const Vector<double>&).
/// calculate_scaled_input(const Vector<double>&).
/// calculate_hidden_layer_combination(const Vector<double>&).
/// calculate_hidden_layer_combination(const Vector<double>&).
/// calculate_hidden_layer_activation_derivative(const Vector<double>&).
/// calculate_output_layer_combination(const Vector<double>&).
/// calculate_output_layer_activation(const Vector<double>&).
/// calculate_output_layer_activation_derivative(const Vector<double>&).
/// calculate_unscaled_output(const Vector<double>&).
/// apply_bounds(const Vector<double>&).
/// @param input Set of inputs to the neural network.

Vector<double> MultilayerPerceptron::calculate_output(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   int size = input.get_size();

   if(size != inputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector<double> calculate_output(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }   
   
   #endif

   // Calculate output

   int hidden_layers_number = get_hidden_layers_number();

   check_input_range(input);

   Vector<double> scaled_input = calculate_scaled_input(input);
   
   Vector< Vector<double> > forward_propagation = calculate_forward_propagation(scaled_input);
   
   Vector<double> unscaled_output = calculate_unscaled_output(forward_propagation[hidden_layers_number]);
   
   Vector<double> bounded_output = calculate_bounded_output(unscaled_output);

   //std::cout << std::endl << "NN Output: " << bounded_output << std::endl; // Debugger

   return(bounded_output);
}


// Matrix<double> calculate_output_matrix(const Matrix<double>&) method

/// This method calculates a set of outputs from the neural network in response to a set of inputs vector, when no 
/// boundary conditions ar imposed.
/// The format is a matrix, where each row is a single input vector. 
/// @param input_matrix Matrix of inputs to the neural network. 

Matrix<double> MultilayerPerceptron::calculate_output_matrix(const Matrix<double>& input_matrix)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int columns_number = input_matrix.get_columns_number();

   if(columns_number != inputs_number) 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Matrix<double> calculate_output_matrix(const Matrix<double>&) method." << std::endl
                << "Number of columns must be equal to number of inputs." << std::endl;

      exit(1);
   }   

   #endif
  
   int input_vectors_number = input_matrix.get_rows_number();

   Matrix<double> output_matrix(input_vectors_number, outputs_number);

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);

   for(int i = 0; i < input_vectors_number; i++)
   {
      input = input_matrix.get_row(i);
      output = calculate_output(input);
      output_matrix.set_row(i, output);
   }

   return(output_matrix);
}


// Vector< Vector<double> > calculate_forward_propagation(const Vector<double>&) method

/// This method applies an input vector to the neural network and returns all the forward propagation quantities
/// from that input to the output.
/// The size of this vector is equal to the number of hidden layers plus one. 
/// The elements are the following:
/// <ul>
/// <li> Output from hidden layers.
/// <li> Output from output layer. 
/// </ul>
/// @param input Set of inputs to the neural network.

Vector< Vector<double> > MultilayerPerceptron::calculate_forward_propagation(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int input_size = input.get_size();

   if(input_size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector< Vector<double> > calculate_forward_propagation(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

        exit(1);
   }

   #endif

   int hidden_layers_number = get_hidden_layers_number();

   int size = hidden_layers_number + 1;

   Vector< Vector<double> > forward_propagation(size);

   // Hidden layers

   forward_propagation[0] = calculate_hidden_layer_output(0, input);
 
   for(int h = 1; h < hidden_layers_number; h++)
   {
      forward_propagation[h] = calculate_hidden_layer_output(h, forward_propagation[h-1]);
   }

   // Output layer

   forward_propagation[size-1] = calculate_output_layer_output(forward_propagation[hidden_layers_number-1]);

   return(forward_propagation);
}


// Vector< Vector<double> > calculate_forward_propagation_derivative(const Vector<double>&) method

/// This method returns a vector of vectors with the forward propagation values and their derivatives. 
/// The size of the vector is equal to two times the number of hidden layers plus two.
/// The elements are the following:
/// <ul>
/// <li> Output from hidden layers.
/// <li> Output derivative from hidden layers.
/// <li> Output from output layer. 
/// <li> Output derivative from output layer. 
/// </ul>
/// @param input Set of inputs to the neural network.

Vector< Vector<double> > MultilayerPerceptron::calculate_forward_propagation_derivative(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int input_size = input.get_size();

   if(input_size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector< Vector<double> > calculate_forward_propagation_derivative(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

        exit(1);
   }

   #endif

   int hidden_layers_number = get_hidden_layers_number();

   int size = 2*hidden_layers_number + 2;

   Vector< Vector<double> > forward_propagation_derivative(size);

   // Hidden layers

   Vector< Vector<double> > hidden_layers_combination(hidden_layers_number);
   Vector< Vector<double> > hidden_layers_activation(hidden_layers_number);
   Vector< Vector<double> > hidden_layers_activation_derivative(hidden_layers_number);

   hidden_layers_combination[0] = calculate_hidden_layer_combination(0, input);

   hidden_layers_activation[0] = calculate_hidden_layer_activation(0, hidden_layers_combination[0]);

   hidden_layers_activation_derivative[0] = calculate_hidden_layer_activation_derivative(0, hidden_layers_combination[0]);
  
   for(int h = 1; h < hidden_layers_number; h++)
   {
      hidden_layers_combination[h] = calculate_hidden_layer_combination(h, hidden_layers_activation[h-1]);
   
      hidden_layers_activation[h] = calculate_hidden_layer_activation(h, hidden_layers_combination[h]);

      hidden_layers_activation_derivative[h] 
      = calculate_hidden_layer_activation_derivative(h, hidden_layers_combination[h]);         
   }

   // Output layer

   Vector<double> output_layer_combination 
   = calculate_output_layer_combination(hidden_layers_activation[hidden_layers_number-1]);

   Vector<double> output_layer_activation = calculate_output_layer_activation(output_layer_combination);

   Vector<double> output_layer_activation_derivative 
   = calculate_output_layer_activation_derivative(output_layer_combination);

   // Assign values to forward propagation vector of vectors

   int index = 0;

   for(int h = 0; h < hidden_layers_number; h++)
   {
      forward_propagation_derivative[index] = hidden_layers_activation[h];
      index++;

      forward_propagation_derivative[index] = hidden_layers_activation_derivative[h];
      index++;
   }

   forward_propagation_derivative[index] = output_layer_activation;
   index++;

   forward_propagation_derivative[index] = output_layer_activation_derivative;
   index++;

   return(forward_propagation_derivative);
}


// Vector< Vector<double> > calculate_forward_propagation_second_derivative(const Vector<double>&) method

/// This method returns a vector of vectors with the forward propagation values, their derivatives and their second derivatives. 
/// The size of the vector is equal to three times the number of hidden layers plus three.
/// The elements are the following:
/// <ul>
/// <li> Output from hidden layers.
/// <li> Output derivative from hidden layers.
/// <li> Output second derivative from hidden layers.
/// <li> Output from output layer. 
/// <li> Output derivative from output layer. 
/// <li> Output second derivative from output layer. 
/// </ul>
/// @param input Set of inputs to the neural network.

Vector< Vector<double> > MultilayerPerceptron::
calculate_forward_propagation_second_derivative(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int input_size = input.get_size();

   if(input_size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "Vector< Vector<double> > calculate_forward_propagation_second_derivative(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

        exit(1);
   }

   #endif

   int hidden_layers_number = get_hidden_layers_number();

   int size = 3*hidden_layers_number + 3;

   Vector< Vector<double> > forward_propagation_second_derivative(size);

   // Hidden layers

   Vector< Vector<double> > hidden_layers_combination(hidden_layers_number);
   Vector< Vector<double> > hidden_layers_activation(hidden_layers_number);
   Vector< Vector<double> > hidden_layers_activation_derivative(hidden_layers_number);
   Vector< Vector<double> > hidden_layers_activation_second_derivative(hidden_layers_number);

   hidden_layers_combination[0] = calculate_hidden_layer_combination(0, input);

   hidden_layers_activation[0] = calculate_hidden_layer_activation(0, hidden_layers_combination[0]);

   hidden_layers_activation_derivative[0] 
   = calculate_hidden_layer_activation_derivative(0, hidden_layers_combination[0]);

   hidden_layers_activation_second_derivative[0] 
   = calculate_hidden_layer_activation_second_derivative(0, hidden_layers_combination[0]);

   for(int h = 1; h < hidden_layers_number; h++)
   {
      hidden_layers_combination[h] = calculate_hidden_layer_combination(h, hidden_layers_activation[h-1]);
   
      hidden_layers_activation[h] = calculate_hidden_layer_activation(h, hidden_layers_combination[h]);

      hidden_layers_activation_derivative[h] 
      = calculate_hidden_layer_activation_derivative(h, hidden_layers_combination[h]);         

      hidden_layers_activation_second_derivative[h] 
      = calculate_hidden_layer_activation_second_derivative(h, hidden_layers_combination[h]);         
   }

   // Output layer

   Vector<double> output_layer_combination 
   = calculate_output_layer_combination(hidden_layers_activation[hidden_layers_number-1]);

   Vector<double> output_layer_activation = calculate_output_layer_activation(output_layer_combination);

   Vector<double> output_layer_activation_derivative 
   = calculate_output_layer_activation_derivative(output_layer_combination);

   Vector<double> output_layer_activation_second_derivative 
   = calculate_output_layer_activation_second_derivative(output_layer_combination);

   // Assign values to forward propagation vector of vectors

   int index = 0;

   for(int h = 0; h < hidden_layers_number; h++)
   {
      forward_propagation_second_derivative[index] = hidden_layers_activation[h];
      index++;

      forward_propagation_second_derivative[index] = hidden_layers_activation_derivative[h];
      index++;

      forward_propagation_second_derivative[index] = hidden_layers_activation_second_derivative[h];
      index++;
   }

   forward_propagation_second_derivative[index] = output_layer_activation;
   index++;

   forward_propagation_second_derivative[index] = output_layer_activation_derivative;
   index++;

   forward_propagation_second_derivative[index] = output_layer_activation_second_derivative;
   index++;

   return(forward_propagation_second_derivative);
}


// Matrix<double> calculate_Jacobian_forward_differences(const Vector<double>&) method

/// This method calculates the Jacobian matrix for an input vector by means of the forward differences method 
/// of numerical differentiation. 
/// @param input Set of inputs to the neural network.

Matrix<double> MultilayerPerceptron::calculate_Jacobian_forward_differences(const Vector<double>& input)
{ 
   int hidden_layers_number = get_hidden_layers_number();

   Matrix<double> Jacobian(outputs_number, inputs_number);

   // Check input for size and maximum and minimum values
 
   check_input_range(input);

   // Preprocess input to obtain input to the neural network 

   Vector<double> scaled_input = calculate_scaled_input(input);

   // Calculate forward propagation

   Vector< Vector<double> > forward_propagation = calculate_forward_propagation(scaled_input);

   // Calculate output for input forward

   Vector<double> scaled_input_forward(scaled_input);

   Vector< Vector<double> > forward_propagation_forward(hidden_layers_number);  

   for(int i = 0; i < inputs_number; i++)
   {
      // Perturbate input 

      scaled_input_forward[i] += numerical_epsilon;

      // Calculate forward propagation forward

	  forward_propagation_forward = calculate_forward_propagation(scaled_input_forward);

      // Calculate Jacobian

      for(int k = 0; k < outputs_number; k++)
      {
         Jacobian[k][i] = (forward_propagation_forward[hidden_layers_number][k] - forward_propagation[hidden_layers_number][k])/numerical_epsilon;
      }

      // Restart original input 

      scaled_input_forward[i] -= numerical_epsilon;
   }

   return(Jacobian);
}


// Matrix<double> calculate_Jacobian_central_differences(const Vector<double>&) method

/// This method calculates the Jacobian matrix for an input vector by means of the central differences method 
/// of numerical differentiation. 
/// @param input Set of inputs to the neural network.

Matrix<double> MultilayerPerceptron::calculate_Jacobian_central_differences(const Vector<double>& input)
{
   Matrix<double> Jacobian(outputs_number, inputs_number);

   // Check input for size and maximum and minimum values
 
   check_input_range(input);

   int hidden_layers_number = get_hidden_layers_number();

   // Preprocess input to the neural network 

   Vector<double> scaled_input = calculate_scaled_input(input);

   Vector<double> scaled_input_forward(scaled_input);
   Vector<double> scaled_input_backward(scaled_input);

   Vector< Vector<double> > forward_propagation_forward(hidden_layers_number);  
   Vector< Vector<double> > forward_propagation_backward(hidden_layers_number);  

   for(int i = 0; i < inputs_number; i++)
   {
      // Perturbate input 

      scaled_input_forward[i] += numerical_epsilon;
      scaled_input_backward[i] -= numerical_epsilon;

      // Calculate output              

      forward_propagation_forward = calculate_forward_propagation(scaled_input_forward);
      forward_propagation_backward = calculate_forward_propagation(scaled_input_backward);

      // Calculate Jacobian

      for(int k = 0; k < outputs_number; k++)
      {
         Jacobian[k][i] = (forward_propagation_forward[hidden_layers_number][k] - forward_propagation_backward[hidden_layers_number][k])/(2.0*numerical_epsilon);
      }

      // Restart original input 

      scaled_input_forward[i] -= numerical_epsilon;
      scaled_input_backward[i] += numerical_epsilon;
   }

   return(Jacobian);
}


// Matrix<double> calculate_Jacobian(const Vector<double>&) method

/// This method returns the the Jacobian Matrix of the neural network for a set of inputs, corresponding to the 
/// point in input space at which the Jacobian Matrix is to be found. It uses a forward-propagation method.
/// @param input Set of inputs to the neural network.

Matrix<double> MultilayerPerceptron::calculate_Jacobian(const Vector<double>& input)
{   
   #ifdef _DEBUG 

   int size = input.get_size();

   if(size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void calculate_Jacobian(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   check_input_range(input);

   int hidden_layers_number = get_hidden_layers_number();

   Vector< Vector<double> > hidden_layers_output(hidden_layers_number);
   hidden_layers_output[0] = calculate_hidden_layer_output(0, input);   

   Vector< Matrix<double> > hidden_layers_Jacobian(hidden_layers_number);
   hidden_layers_Jacobian[0] = calculate_hidden_layer_Jacobian(0, input);

   for(int i = 1; i < hidden_layers_number; i++)
   {
      hidden_layers_output[i] 
      = calculate_hidden_layer_output(i, hidden_layers_output[i-1]);         

      hidden_layers_Jacobian[i] = calculate_hidden_layer_Jacobian(i, hidden_layers_output[i-1]);
   }

   Matrix<double> output_layer_Jacobian 
   = calculate_output_layer_Jacobian(hidden_layers_output[hidden_layers_number-1]);

   // Calculate Jacobian

   Matrix<double> Jacobian = output_layer_Jacobian.dot(hidden_layers_Jacobian[hidden_layers_number-1]);

   for(int i = hidden_layers_number-2; i > -1; i--)
   {
      Jacobian = Jacobian.dot(hidden_layers_Jacobian[i]);   
   }

   return(Jacobian);
}


// Matrix<double> calculate_Jacobian_numerical_differentiation(const Vector<double>&) method

/// This method returns the the Jacobian matrix of the neural network for a set of inputs corresponding to the 
/// point in input space at which the Jacobian Matrix is to be found. It uses numerical differentiation.
/// @param input: Set of inputs to the neural network.

Matrix<double> MultilayerPerceptron::calculate_Jacobian_numerical_differentiation(const Vector<double>& input)
{
   Matrix<double> Jacobian(outputs_number, inputs_number);

   switch(numerical_differentiation_method)   
   {
      case ForwardDifferences:
      {
         Jacobian = calculate_Jacobian_forward_differences(input);
      }                               
      break;

      case CentralDifferences:
      {
         Jacobian = calculate_Jacobian_central_differences(input);
      }
      break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "Matrix<double> calculate_Jacobian_numerical_differentiation(const Vector<double>&) method." << std::endl
                   << "Unknown numerical differentiation method." << std::endl;
 
         exit(1);
      }
      break;

   }// end numerical differentiation method switch

   return(Jacobian);
}

   
// Matrix<double> calculate_sensitivity(const Vector<double>&) method

/// This method calculates the sensitivity matrix of the multilayer perceptron for an input vector. 
/// The elements of that matrix are the partial derivatives of the outputs with respect to the neural parameters. 
/// @param input Set of inputs to the neural network.
Matrix<double> MultilayerPerceptron::calculate_sensitivity(const Vector<double>& input)
{   
   #ifdef _DEBUG 

   int size = input.get_size();

   if(size != inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void calculate_sensitivity(Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   return(calculate_sensitivity_numerical_differentiation(input));
}


// Matrix<double> calculate_sensitivity_forward_differences(const Vector<double>&) method

/// This method calculates the sensitivity matrix for an input vector by means of the forward differences method 
/// for numerical differentiation. 
/// @param input Set of inputs to the neural network.

Matrix<double> MultilayerPerceptron::calculate_sensitivity_forward_differences(const Vector<double>& input)
{
   int hidden_layers_number = get_hidden_layers_number();

   Vector<double> neural_parameters = get_neural_parameters();
   int neural_parameters_number = get_neural_parameters_number();

   Matrix<double> sensitivity(outputs_number, neural_parameters_number);

   // Check input for size and maximum and minimum values
 
   check_input_range(input);

   Vector<double> scaled_input = calculate_scaled_input(input);

   // Calculate output 

   Vector< Vector<double> > forward_propagation = calculate_forward_propagation(scaled_input);
   
   // Calculate output for input signal and neural parameters forward

   Vector<double> neural_parameters_forward(neural_parameters);

   Vector< Vector<double> > forward_propagation_forward(hidden_layers_number);  

   double actual_epsilon;

   for(int i = 0; i < neural_parameters_number; i++)
   {
      actual_epsilon = calculate_actual_epsilon(neural_parameters[i]);

      // Perturbate single neural parameter

      neural_parameters_forward[i] += actual_epsilon;
      set_neural_parameters(neural_parameters_forward);

      // Calculate output signal             

      forward_propagation_forward = calculate_forward_propagation(scaled_input);

      // Calculate sensitivity

      for(int k = 0; k < outputs_number; k++)
      {
         sensitivity[k][i] = (forward_propagation_forward[hidden_layers_number][k] - forward_propagation[hidden_layers_number][k])/actual_epsilon;
      }

      // Restart original neural parameters

      neural_parameters_forward[i] -= actual_epsilon;
      set_neural_parameters(neural_parameters_forward);
   }

   return(sensitivity);
}


// Matrix<double> calculate_sensitivity_central_differences(const Vector<double>&) method

/// This method calculates the Jacobian matrix for an input vector by means of the central differences method 
/// for numerical differentiation. 
/// @param input Set of inputs to the neural network.

Matrix<double> MultilayerPerceptron::calculate_sensitivity_central_differences(const Vector<double>& input)
{
   // Check input for size and maximum and minimum values
 
   check_input_range(input);

   int neural_parameters_number = get_neural_parameters_number();

   Matrix<double> sensitivity(outputs_number, neural_parameters_number);

   int hidden_layers_number = get_hidden_layers_number();

   Vector<double> scaled_input = calculate_scaled_input(input);

   Vector<double> neural_parameters = get_neural_parameters();

   Vector<double> neural_parameters_forward(neural_parameters);
   Vector<double> neural_parameters_backward(neural_parameters);

   Vector< Vector<double> > hidden_layers_output_forward(hidden_layers_number);  
   Vector< Vector<double> > hidden_layers_output_backward(hidden_layers_number);  

   Vector<double> output_layer_output_forward(outputs_number);  
   Vector<double> output_layer_output_backward(outputs_number);  

   double actual_epsilon;

   for(int i = 0; i < neural_parameters_number; i++)
   {
      actual_epsilon = calculate_actual_epsilon(neural_parameters[i]);

      // Perturbate neural parameters

      neural_parameters_forward[i] += actual_epsilon;
      set_neural_parameters(neural_parameters_forward);

      // Calculate output             

      hidden_layers_output_forward[0] = calculate_hidden_layer_output(0, input);
  
      for(int j = 1; j < hidden_layers_number; j++)

      {
         hidden_layers_output_forward[j] 
         = calculate_hidden_layer_output(j, hidden_layers_output_forward[j-1]);         
      }

      output_layer_output_forward 
      = calculate_output_layer_output(hidden_layers_output_forward[hidden_layers_number-1]);

      // Restart original neural parameters

      neural_parameters_forward[i] -= actual_epsilon;
      set_neural_parameters(neural_parameters_forward);

      // Perturbate neural parameters

      neural_parameters_backward[i] -= actual_epsilon;
      set_neural_parameters(neural_parameters_backward);

      // Calculate output             

      hidden_layers_output_backward[0] = calculate_hidden_layer_output(0, input);

      for(int j = 1; j < hidden_layers_number; j++)
      {
         hidden_layers_output_backward[j] 
         = calculate_hidden_layer_output(j, hidden_layers_output_backward[j-1]);              
      }

      output_layer_output_backward 
      = calculate_output_layer_output(hidden_layers_output_backward[hidden_layers_number-1]);

      // Restart original neural parameters

      neural_parameters_backward[i] += actual_epsilon;
      set_neural_parameters(neural_parameters_backward);       

      // Calculate sensitivity

      for(int k = 0; k < outputs_number; k++)
      {
          sensitivity[k][i] = (output_layer_output_forward[k] - output_layer_output_backward[k])/(2.0*actual_epsilon);
      }
   }

   return(sensitivity);
}


// Matrix<double> calculate_sensitivity_numerical_differentiation(const Vector<double>& input)

/// This method returns the sensitivity matrix for an input vector by means of numerical differentiation. 
/// The numerical differentiation method chosen is that of the corresponding member of this class. 
/// @param input Set of inputs to the neural network.

Matrix<double> MultilayerPerceptron::calculate_sensitivity_numerical_differentiation(const Vector<double>& input)
{
   int neural_parameters_number = get_neural_parameters_number();

   Matrix<double> sensitivity(outputs_number, neural_parameters_number);

   switch(numerical_differentiation_method)   
   {
      case ForwardDifferences:
      {
         return(calculate_sensitivity_forward_differences(input));
      }                               
      break;

      case CentralDifferences:
      {
         return(calculate_sensitivity_central_differences(input));
      }
      break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "Matrix<double> calculate_sensitivity_numerical_differentiation(const Vector<double>&) method." << std::endl
                   << "Unknown numerical differentiation method." << std::endl;
 
         exit(1);
      }
      break;
   }// end numerical differentiation method switch

   Matrix<double> d;
   return d;
}



// std::string to_XML(bool) method

/// This method returns a string representation of this multilayer perceptron object. The format of the string is XML-type. 
/// Please read the user's guide for more information about this. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

std::string MultilayerPerceptron::to_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Declaration

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='MultilayerPerceptron'>" << std::endl;
   }

   // Network architecture

   int hidden_layers_number = get_hidden_layers_number();

   buffer << "<InputsNumber>" << std::endl 
          << inputs_number << std::endl
          << "</InputsNumber>" << std::endl 
          << "<HiddenLayersNumber>" << std::endl
		  << hidden_layers_number << std::endl
		  << "</HiddenLayersNumber>" << std::endl
          << "<HiddenLayersSize>" << std::endl
          << hidden_layers_size << std::endl
          << "</HiddenLayersSize>" << std::endl
          << "<OutputsNumber>" << std::endl
          << outputs_number << std::endl
          << "</OutputsNumber>" << std::endl;

   int independent_parameters_number = get_independent_parameters_number();

   buffer << "<IndependentParametersNumber>" << std::endl 
          << independent_parameters_number << std::endl
          << "</IndependentParametersNumber>" << std::endl;


   if(inputs_number != 0 && hidden_layers_number != 0 && outputs_number != 0)
   {
      // Hidden layers activation function

      buffer << "<HiddenLayersActivationFunction>" << std::endl;   

      for(int i = 0; i < hidden_layers_number; i++)
      {
         buffer << get_hidden_layer_activation_function_name(i) << std::endl;            
      }

      buffer << "</HiddenLayersActivationFunction>" << std::endl;

      // Print output layer activation function

      buffer << "<OutputLayerActivationFunction>" << std::endl
		     << get_output_layer_activation_function_name() << std::endl
             << "</OutputLayerActivationFunction>" << std::endl;

      // Print inputs scaling method 

      buffer << "<InputsScalingMethod>" << std::endl
		     << get_inputs_scaling_method_name() << std::endl
		     << "</InputsScalingMethod>" << std::endl;

      // Print outputs unscaling method 

      buffer << "<OutputsUnscalingMethod>" << std::endl
		     << get_outputs_unscaling_method_name() << std::endl
		     << "</OutputsUnscalingMethod>" << std::endl;

      // Neural parameters

      Vector<double> neural_parameters = get_neural_parameters();

      buffer << "<NeuralParameters>" << std::endl 
             << neural_parameters << std::endl
             << "</NeuralParameters>" << std::endl; 

      // Name of input variables

      if(input_variables_name.get_size() != 0)
      {
         buffer << "<InputVariablesName>" << std::endl;
		 
		 for(int i = 0; i < inputs_number; i++)
		 {
			 buffer << "<Name>" << std::endl
				    << input_variables_name[i] << std::endl
					<< "</Name>" << std::endl;         		    		
		 }
		 
         buffer << "</InputVariablesName>" << std::endl;
      }

      // Name of output variables

      if(output_variables_name.get_size() != 0)
      {
         buffer << "<OutputVariablesName>" << std::endl;

		 for(int i = 0; i < outputs_number; i++)
		 {
			buffer << "<Name>" << std::endl 
                   << output_variables_name[i] << std::endl
			       << "</Name>" << std::endl;
		 }

         buffer << "</OutputVariablesName>" << std::endl;
      }

      // Units of input variables

      if(input_variables_units.get_size() != 0)
      {
         buffer << "<InputVariablesUnits>" << std::endl;

		 for(int i = 0; i < inputs_number; i++)
		 {
			 buffer << "<Units>" << std::endl
				    << input_variables_units[i] << std::endl
					<< "</Units>" << std::endl;         		    		
		 }

         buffer << "</InputVariablesUnits>" << std::endl;
      }

      // Units of output variables

      if(output_variables_units.get_size() != 0)
      {
         buffer << "<OutputVariablesUnits>" << std::endl;

		 for(int i = 0; i < outputs_number; i++)
		 {
			 buffer << "<Units>" << std::endl
				    << output_variables_units[i] << std::endl
					<< "</Units>" << std::endl;         		    		
		 }

		 buffer << "</OutputVariablesUnits>" << std::endl;
      }

      // Description of input variables

      if(input_variables_description.get_size() != 0)
      {
         buffer << "<InputVariablesDescription>" << std::endl;

		 for(int i = 0; i < inputs_number; i++)
		 {
			 buffer << "<Description>" << std::endl
				    << input_variables_description[i] << std::endl
					<< "</Description>" << std::endl;         		    		
		 }

         buffer << "</InputVariablesDescription>" << std::endl;
      }

      // Description of output variables

      if(output_variables_description.get_size() != 0)
      {
         buffer << "<OutputVariablesDescription>" << std::endl;

		 for(int i = 0; i < outputs_number; i++)
		 {
			 buffer << "<Description>" << std::endl
				    << output_variables_description[i] << std::endl
					<< "</Description>" << std::endl;         		    		
		 }

         buffer << "</OutputVariablesDescription>" << std::endl;
      }

      // Mean of input variables

      if(input_variables_mean.get_size() != 0)
      {
         buffer << "<InputVariablesMean>" << std::endl
                << input_variables_mean << std::endl
                << "</InputVariablesMean>" << std::endl;
      }

      // Standard deviation of input variables 

      if(input_variables_standard_deviation.get_size() != 0)
      {
         buffer << "<InputVariablesStandardDeviation>" << std::endl
                << input_variables_standard_deviation << std::endl
                << "</InputVariablesStandardDeviation>" << std::endl;
      }

      // Mean of output variables

      if(output_variables_mean.get_size() != 0)
      {
         buffer << "<OutputVariablesMean>" << std::endl
                << output_variables_mean << std::endl
                << "</OutputVariablesMean>" << std::endl;
      }

      // Standard deviation of output variables

      if(output_variables_standard_deviation.get_size() != 0)
      {
         buffer << "<OutputVariablesStandardDeviation>" << std::endl
                << output_variables_standard_deviation << std::endl
                << "</OutputVariablesStandardDeviation>" << std::endl;
      } 

      // Minimum of input variables

      if(input_variables_minimum.get_size() != 0)
      {
         buffer << "<InputVariablesMinimum>" << std::endl
                << input_variables_minimum << std::endl
                << "</InputVariablesMinimum>" << std::endl;
      }

      // Maximum of input variables

      if(input_variables_maximum.get_size() != 0)
      {
         buffer << "<InputVariablesMaximum>" << std::endl
                << input_variables_maximum << std::endl
                << "</InputVariablesMaximum>" << std::endl;
      }

      // Minimum of output variables

      if(output_variables_minimum.get_size() != 0)
      {
         buffer << "<OutputVariablesMinimum>" << std::endl
                << output_variables_minimum << std::endl
                << "</OutputVariablesMinimum>" << std::endl;
      }

      // Maximum of output variables

      if(output_variables_maximum.get_size() != 0)
      {
         buffer << "<OutputVariablesMaximum>" << std::endl
                << output_variables_maximum << std::endl
                << "</OutputVariablesMaximum>" << std::endl;
      }

      // Lower bound of output variables

      if(output_variables_lower_bound.get_size() != 0)
      {
         buffer << "<OutputVariablesLowerBound>" << std::endl
                << output_variables_lower_bound << std::endl
		        << "</OutputVariablesLowerBound>" << std::endl;
      }

      // Upper bound of output variables

      if(output_variables_upper_bound.get_size() != 0)
      {
         buffer << "<OutputVariablesUpperBound>" << std::endl
                << output_variables_upper_bound << std::endl
                << "</OutputVariablesUpperBound>" << std::endl;
	  }
   }

   // Number of independent parameters

   if(independent_parameters_number > 0)
   {             
      // Name of independent parameters

      if(independent_parameters_name.get_size() != 0)
      {
         buffer << "<IndependentParametersName>" << std::endl;

         for(int i = 0; i < independent_parameters_number; i++)
		 {
			 buffer << "<Name>" << std::endl
				    << independent_parameters_name[i] << std::endl
					<< "</Name>" << std::endl;
		 }

         buffer << "</IndependentParametersName>" << std::endl;
      }

      // Units of independent parameters

      if(independent_parameters_units.get_size() != 0)
      {
         buffer << "<IndependentParametersUnits>" << std::endl;

         for(int i = 0; i < independent_parameters_number; i++)
		 {
			 buffer << "<Units>" << std::endl
				    << independent_parameters_units[i] << std::endl
					<< "</Units>" << std::endl;
		 }

         buffer << "</IndependentParametersUnits>" << std::endl;
      }

      // Description of independent parameters

      if(independent_parameters_description.get_size() != 0)
      {
         buffer << "<IndependentParametersDescription>" << std::endl;

         for(int i = 0; i < independent_parameters_number; i++)
		 {
			 buffer << "<Description>" << std::endl
				    << independent_parameters_description[i] << std::endl
					<< "</Description>" << std::endl;
		 }

         buffer << "</IndependentParametersDescription>" << std::endl;
      }

      // Mean of independent parameters

      if(independent_parameters_mean.get_size() != 0)
      {
         buffer << "<IndependentParametersMean>" << std::endl
                << independent_parameters_mean << std::endl
                << "</IndependentParametersMean>" << std::endl;
      }

      // Standard deviation of independent parameters

      if(independent_parameters_standard_deviation.get_size() != 0)
      {
         buffer << "<IndependentParametersStandardDeviation>" << std::endl
                << independent_parameters_standard_deviation << std::endl
                << "</IndependentParametersStandardDeviation>" << std::endl;
      }

      // Minimum of independent parameters

      if(independent_parameters_minimum.get_size() != 0)
      {
         buffer << "<IndependentParametersMinimum>" << std::endl
                << independent_parameters_minimum << std::endl
                << "</IndependentParametersMinimum>" << std::endl;
      }

      // Maximum of independent parameters

      if(independent_parameters_maximum.get_size() != 0)
      {
         buffer << "<IndependentParametersMaximum>" << std::endl
                << independent_parameters_maximum << std::endl
                << "</IndependentParametersMaximum>" << std::endl;
      }

      // Lower bound of independent parameters

      if(independent_parameters_lower_bound.get_size() != 0)
      {
         buffer << "<IndependentParametersLowerBound>" << std::endl
                << independent_parameters_lower_bound << std::endl
                << "<IndependentParametersLowerBound>" << std::endl;
      }

      // Upper bound of independent parameters

      if(independent_parameters_upper_bound.get_size() != 0)
      {
         buffer << "<IndependentParametersUpperBound>" << std::endl
                << independent_parameters_upper_bound << std::endl
                << "</IndependentParametersUpperBound>" << std::endl;
      }

      // Independent parameters scaling and unscaling method 

      buffer << "<IndependentParametersScalingMethod>" << std::endl
		     << get_independent_parameters_scaling_method_name() << std::endl
             << "</IndependentParametersScalingMethod>" << std::endl;

      // Independent parameters

      buffer << "<IndependentParameters>" << std::endl 
             << independent_parameters << std::endl
             << "</IndependentParameters>" << std::endl;
   }

   // Numerical differentiation method 

   buffer << "<NumericalDifferentiationMethod>" << std::endl
   	      << get_numerical_differentiation_method_name() << std::endl
          << "</NumericalDifferentiationMethod>" << std::endl;

   // Numerical epsilon method

   buffer << "<NumericalEpsilonMethod>" << std::endl
          << get_numerical_epsilon_method_name() << std::endl
          << "</NumericalEpsilonMethod>" << std::endl;

   // Numerical epsilon

   buffer << "<NumericalEpsilon>" << std::endl
          << numerical_epsilon << std::endl
          << "</NumericalEpsilon>" << std::endl;

   // Display 

   buffer << "<Display>" << std::endl
          << display << std::endl
          << "</Display>" << std::endl;

   // Display out of range warning

   buffer << "<DisplayRangeOutWarning>" << std::endl
          << display_range_out_warning << std::endl
          << "</DisplayRangeOutWarning>" << std::endl;

   return(buffer.str());
}


// void print(void) method

/// This method prints to the screen the members of a multilayer perceptron object in a XML-type format.

void MultilayerPerceptron::print(void)
{
   if(display)
   {
      std::cout << to_XML(true);
   }
}


// void save(const char*) method 

/// This method saves to a XML-type format file the members of a multilayer perceptron object.
/// @param filename Name of multilayer perceptron XML-type file.

void MultilayerPerceptron::save(const char* filename)
{
   std::fstream file; 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void save(const char*) method." << std::endl
                << "Cannot open multilayer perceptron XML-type file." << std::endl;

      exit(1);
   }

   // Write file header

   file << to_XML(true);

   // Close file

   file.close();
}


// void load(const char*) method

/// This method loads from a XML-type file the members of a multilayer perceptron object.
/// Please mind about the file format, which is specified in the User's Guide. 
/// @param filename Name of multilayer perceptron XML-type file.

void MultilayerPerceptron::load(const char* filename)
{
   std::fstream file;

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open multilayer perceptron XML-type file." << std::endl;

      exit(1);
   }

   set();

   std::string line;
   std::string word;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='MultilayerPerceptron'>") 
   {
//      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
//                << "void load(const char*) method." << std::endl
//				<< "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   // Inputs number

   file >> word;

   if(word != "<InputsNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown inputs number begin tag: " << line << std::endl;
 
      exit(1);
   }

   int new_inputs_number;

   file >> new_inputs_number;

   file >> word;

   if(word != "</InputsNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown inputs number end tag: " << line << std::endl;
 
      exit(1);
   }

   // Hidden layers number 

   file >> word; 

   if(word != "<HiddenLayersNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
      	        << "Unknown hidden layers number begin tag: " << word << std::endl;
 
      exit(1);
   }

   int new_hidden_layers_number;
   file >> new_hidden_layers_number;

   file >> word; 

   if(word != "</HiddenLayersNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
    	        << "Unknown hidden layers number end tag: " << word << std::endl;
 
      exit(1);
   }  

   // Hidden layers size

   file >> word; 

   if(word != "<HiddenLayersSize>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Unknown hidden layers size begin tag: " << word << std::endl;
 
      exit(1);
   }

   Vector<int> new_hidden_layers_size(new_hidden_layers_number);
   file >> new_hidden_layers_size;

   file >> word; 

   if(word != "</HiddenLayersSize>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
   			    << "Unknown hidden layers size end tag: " << word << std::endl;
 
      exit(1);
   }  

   // Number of outputs

   file >> word; 

   if(word != "<OutputsNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
	     	    << "Unknown outputs number begin tag: " << word << std::endl;
 
      exit(1);
   }

   int new_outputs_number;
   file >> new_outputs_number;

   file >> word; 

   if(word != "</OutputsNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
      		    << "Unknown outputs number end tag: " << word << std::endl;
 
      exit(1);
   }  

   set_network_architecture(new_inputs_number, new_hidden_layers_size, new_outputs_number);

   // Number of independent parameters

   file >> word; 

   if(word != "<IndependentParametersNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
	     	    << "Unknown independent parameters number begin tag: " << word << std::endl;
 
       exit(1);
   }

   int new_independent_parameters_number;
   file >> new_independent_parameters_number;

   file >> word; 

   if(word != "</IndependentParametersNumber>") 
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void load(const char*) method." << std::endl
    	   	    << "Unknown independent parameters number end tag: " << word << std::endl;
 
      exit(1);
  }  

   set_independent_parameters_number(new_independent_parameters_number);

   while(!file.eof())
   {
      file >> word; 

      if(word == "<HiddenLayersActivationFunction>") 
      {
	     Vector<std::string> new_hidden_layers_activation_function(new_hidden_layers_number);
         file >> new_hidden_layers_activation_function;
		 set_hidden_layers_activation_function(new_hidden_layers_activation_function);

         file >> word; 

         if(word != "</HiddenLayersActivationFunction>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          	          << "Unknown hidden layers activation function end tag: " << word << std::endl;

             exit(1);
         }  
      }
      else if(word == "<OutputLayerActivationFunction>") 
      {
   	     std::string new_output_layer_activation_function;
         file >> new_output_layer_activation_function;
		 set_output_layer_activation_function(new_output_layer_activation_function);
		   
		 file >> word; 

         if(word != "</OutputLayerActivationFunction>") 
         {
             std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                       << "void load(const char*) method." << std::endl
          	           << "Unknown output layer activation function end tag: " << word << std::endl;
 
             exit(1);
         }   
      }
      else if(word == "<InputsScalingMethod>") 
      {
	     std::string new_inputs_scaling_method;
		 file >> new_inputs_scaling_method;
		 set_inputs_scaling_method(new_inputs_scaling_method);

         file >> word; 
			   
         if(word != "</InputsScalingMethod>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          	          << "Unknown inputs scaling method end tag: " << word << std::endl;
 
            exit(1);
         }   
      }
      else if(word == "<OutputsUnscalingMethod>") 
      {
	     std::string new_outputs_unscaling_method;
		 file >> new_outputs_unscaling_method;
		 set_outputs_unscaling_method(new_outputs_unscaling_method);

 	     file >> word; 

         if(word != "</OutputsUnscalingMethod>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          	          << "Unknown outputs unscaling method end tag: " << word << std::endl;
 
            exit(1);
         }   
      }
      else if(word == "<NeuralParameters>") 
      {
	     int neural_parameters_number = get_neural_parameters_number();

      	 Vector<double> new_neural_parameters(neural_parameters_number);
         file >> new_neural_parameters;

		 set_neural_parameters(new_neural_parameters);

		 file >> word; 

         if(word != "</NeuralParameters>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          	          << "Unknown neural parameters end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
      else if(word == "<InputVariablesName>")
      {
         for(int i = 0; i < inputs_number; i++) 
		 {
		    file >> word;
   
	        if(word != "<Name>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown name begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

	        set_input_variable_name(i, line);

            file >> word;
   
            if(word != "</Name>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown name end tag: " << word << std::endl;
 
               exit(1);
            }  
         }

		 file >> word; 

		 if(word != "</InputVariablesName>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
           	          << "Unknown input variables name end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
      else if(word == "<OutputVariablesName>")
	  {
	     for(int i = 0; i < outputs_number; i++) 
		 {
		    file >> word;
   
			if(word != "<Name>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown name begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

			set_output_variable_name(i, line);

			file >> word;
   
    		if(word != "</Name>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown name end tag: " << word << std::endl;
 
               exit(1);
            }  
         }

         file >> word; 
			   
		 if(word != "</OutputVariablesName>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
           	          << "Unknown output variables name end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
	  else if(word == "<InputVariablesUnits>")
      {
         for(int i = 0; i < inputs_number; i++) 
   	     {
		    file >> word;
   
            if(word != "<Units>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		         << "Unknown units begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

     	    set_input_variable_units(i, line);

            file >> word;
   
    		if(word != "</Units>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown units end tag: " << word << std::endl;
 
               exit(1);
            }  
         }

         file >> word; 
		if(word != "</InputVariablesUnits>") 
        {
           std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                     << "void load(const char*) method." << std::endl
          	         << "Unknown input variables units end tag: " << word << std::endl;
 
           exit(1);
        }  
      }
	  else if(word == "<OutputVariablesUnits>")
	  {         
         for(int i = 0; i < outputs_number; i++) 
		 {
		    file >> word;
   
    		if(word != "<Units>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown units begin tag: " << word << std::endl;
 
                exit(1);
            }  

            getline(file, line);
            getline(file, line);

	        set_output_variable_units(i, line);

			file >> word;
   
    		if(word != "</Units>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown units end tag: " << word << std::endl;
 
               exit(1);
            }  
         }

         file >> word; 

         if(word != "</OutputVariablesUnits>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          	          << "Unknown output variables units end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
	  else if(word == "<InputVariablesDescription>")
	  {
	     for(int i = 0; i < inputs_number; i++) 
		 {
		    file >> word;
   
    	    if(word != "<Description>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
                         << "Unknown description begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

	        set_input_variable_description(i, line);

			file >> word;
   
    	    if(word != "</Description>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          	             << "Unknown description end tag: " << word << std::endl;
 
               exit(1);
            }  
	     }

         file >> word; 

         if(word != "</InputVariablesDescription>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
             	      << "Unknown input variables description end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
	  else if(word == "<OutputVariablesDescription>")
      {
	     for(int i = 0; i < outputs_number; i++) 
	     {
			file >> word;
   
    	    if(word != "<Description>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		   	     << "Unknown description begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

		    set_output_variable_description(i, line);

			file >> word;
   
            if(word != "</Description>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		   	     << "Unknown description end tag: " << word << std::endl;
 
               exit(1);
            }  
	     }

         file >> word; 

         if(word != "</OutputVariablesDescription>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown output variables description end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
      else if(word == "<InputVariablesMean>")
      {
         Vector<double> new_input_variables_mean(inputs_number);
         file >> new_input_variables_mean;

         file >> word; 

         if(word != "</InputVariablesMean>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown input variables mean end tag: " << word << std::endl;
 
            exit(1);
         }  

		 set_input_variables_mean(new_input_variables_mean);
      }
      else if(word == "<InputVariablesStandardDeviation>")
      {
         Vector<double> new_input_variables_standard_deviation(inputs_number);
         file >> new_input_variables_standard_deviation;

         file >> word; 

         if(word != "</InputVariablesStandardDeviation>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown input variables standard deviation end tag: " << word << std::endl;
 
             exit(1);
         }  

		 set_input_variables_standard_deviation(new_input_variables_standard_deviation);
      }
      else if(word == "<OutputVariablesMean>")
      {
         Vector<double> new_output_variables_mean(outputs_number);
         file >> new_output_variables_mean;

         file >> word; 

	     if(word != "</OutputVariablesMean>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
            	   	  << "Unknown output variables mean end tag: " << word << std::endl;
 
             exit(1);
         }  

		 set_output_variables_mean(new_output_variables_mean);
      }
      else if(word == "<OutputVariablesStandardDeviation>")
	  {
         Vector<double> new_output_variables_standard_deviation(outputs_number);
         file >> new_output_variables_standard_deviation;

         file >> word; 

         if(word != "</OutputVariablesStandardDeviation>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown output variables standard deviation end tag: " << word << std::endl;
 
            exit(1);
         }  

		 set_output_variables_standard_deviation(new_output_variables_standard_deviation);
      }
 	  else if(word == "<InputVariablesMinimum>")
      {
         Vector<double> new_input_variables_minimum(inputs_number);
	     file >> new_input_variables_minimum;

         file >> word; 

         if(word != "</InputVariablesMinimum>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown input variables minimum end tag: " << word << std::endl;
 
            exit(1);
         }  

		 set_input_variables_minimum(new_input_variables_minimum);
      }
 	  else if(word == "<InputVariablesMaximum>")
      {
         Vector<double> new_input_variables_maximum(inputs_number);
         file >> new_input_variables_maximum;

         file >> word; 

         if(word != "</InputVariablesMaximum>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown input variables maximum end tag: " << word << std::endl;
 
             exit(1);
         }  

         set_input_variables_maximum(new_input_variables_maximum);
      }
      else if(word == "<OutputVariablesMinimum>")
      {
         Vector<double> new_output_variables_minimum(outputs_number);
	     file >> new_output_variables_minimum;

         file >> word; 

         if(word != "</OutputVariablesMinimum>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown output variables minimum end tag: " << word << std::endl;
 
             exit(1);
         }  

		 set_output_variables_minimum(new_output_variables_minimum);
      }
 	  else if(word == "<OutputVariablesMaximum>")
	  {
         Vector<double> new_output_variables_maximum(outputs_number);
         file >> new_output_variables_maximum;

         file >> word; 

         if(word != "</OutputVariablesMaximum>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown output variables maximum end tag: " << word << std::endl;
 
            exit(1);
         }  

		 set_output_variables_maximum(new_output_variables_maximum);
      }
      else if(word == "<OutputVariablesLowerBound>")
      {
         Vector<double> new_output_variables_lower_bound(outputs_number);
         file >> new_output_variables_lower_bound;

         file >> word; 

         if(word != "</OutputVariablesLowerBound>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          		   	  << "Unknown output variables lower bound end tag: " << word << std::endl;
 
             exit(1);
          }  

          set_output_variables_lower_bound(new_output_variables_lower_bound);
      }
      else if(word == "<OutputVariablesUpperBound>")
	  {
         Vector<double> new_output_variables_upper_bound(outputs_number);
         file >> new_output_variables_upper_bound;

         file >> word; 

         if(word != "</OutputVariablesUpperBound>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
       		   	      << "Unknown output variables upper bound end tag: " << word << std::endl;
 
            exit(1);
         }  

         set_output_variables_upper_bound(new_output_variables_upper_bound);
      }
      else if(word == "<IndependentParametersName>") 
      {             
	     for(int i = 0; i < new_independent_parameters_number; i++)
	     {
            file >> word;
   
    	    if(word != "<Name>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		   	     << "Unknown name begin tag: " << word << std::endl;
 
               exit(1);
            }  

            getline(file, line);
            getline(file, line);

		    set_independent_parameter_name(i, line);

			file >> word;
   
    	    if(word != "</Name>") 
            {
                std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                          << "void load(const char*) method." << std::endl
          		   	      << "Unknown name end tag: " << word << std::endl;
 
                exit(1);
            }  			
	     }
      }
      else if(word == "<IndependentParametersUnits>") 
      {
         for(int i = 0; i < new_independent_parameters_number; i++)
	     {
			file >> word;
   
    		if(word != "<Units>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		   	     << "Unknown units begin tag: " << word << std::endl;
 
                exit(1);
            }  

            getline(file, line);
            getline(file, line);

	        set_independent_parameter_units(i, line);

			file >> word;
   
            if(word != "</Units>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		   	     << "Unknown units end tag: " << word << std::endl;
 
               exit(1);
            }  			
         }		
      }
      else if(word == "<IndependentParametersDescription>") 
      {
   	     for(int i = 0; i < new_independent_parameters_number; i++)
	     {
			file >> word;
   
    	    if(word != "<Description>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		   	     << "Unknown description begin tag: " << word << std::endl;
 
                exit(1);
            }  

            getline(file, line);
            getline(file, line);

	        set_independent_parameter_description(i, line);

			file >> word;
   
    	    if(word != "</Description>") 
            {
               std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                         << "void load(const char*) method." << std::endl
          		   	     << "Unknown description end tag: " << word << std::endl;
 
               exit(1);
            }  					
         }
	  }
      else if(word == "<IndependentParametersMean>") 
      {
         Vector<double> new_independent_parameters_mean(new_independent_parameters_number);
               
	     file >> new_independent_parameters_mean;

         set_independent_parameters_mean(new_independent_parameters_mean);

         file >> word; 

	     if(word != "</IndependentParametersMean>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown independent parameters  mean end tag: " << word << std::endl;
 
             exit(1);
         }  
      }
      else if(word == "<IndependentParametersStandardDeviation>") 
      {
         Vector<double> new_independent_parameters_standard_deviation(new_independent_parameters_number);

	     file >> new_independent_parameters_standard_deviation;

         set_independent_parameters_standard_deviation(new_independent_parameters_standard_deviation);

         file >> word; 

	     if(word != "</IndependentParametersStandardDeviation>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown independent parameters standard deviation end tag: " << word << std::endl;
 
             exit(1);
         }  
      }
      else if(word == "<IndependentParametersMinimum>") 
      {
         Vector<double> new_independent_parameters_minimum(new_independent_parameters_number);

	     file >> new_independent_parameters_minimum;

         set_independent_parameters_minimum(new_independent_parameters_minimum);

         file >> word; 

	     if(word != "</IndependentParametersMinimum>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown independent parameters minimum end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
      else if(word == "<IndependentParametersMaximum>") 
      {
         Vector<double> new_independent_parameters_maximum(new_independent_parameters_number);

	     file >> new_independent_parameters_maximum;

         set_independent_parameters_maximum(new_independent_parameters_maximum);

         file >> word; 

	     if(word != "</IndependentParametersMaximum>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown independent parameters maximum end tag: " << word << std::endl;
 
            exit(1);
         }  
      }
	  else if(word == "<NumericalDifferentiationMethod>")
	  {
         file >> word;

         set_numerical_differentiation_method(word);

         file >> word;

		 if(word != "</NumericalDifferentiationMethod>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown numerical differentiation method end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<NumericalEpsilonMethod>")
	  {
         file >> word;

         set_numerical_epsilon_method(word);

         file >> word;

		 if(word != "</NumericalEpsilonMethod>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown numerical epsilon method end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<NumericalEpsilon>")
	  {
         double new_numerical_epsilon;

         file >> new_numerical_epsilon;
         
         set_numerical_epsilon(new_numerical_epsilon);

         file >> word;

		 if(word != "</NumericalEpsilon>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown numerical epsilon end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<DisplayRangeOutWarning>")
	  {	     
         file >> display_range_out_warning;

         file >> word;

		 if(word != "</DisplayRangeOutWarning>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown display range out warning end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
	  else if(word == "<Display>")
	  {
         file >> display;

         file >> word;

		 if(word != "</Display>") 
         {
            std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                      << "void load(const char*) method." << std::endl
          			  << "Unknown display end tag: " << word << std::endl;
 
            exit(1);
         }  
	  }
   }
}


// std::string get_expression(void) method

/// This method returns the mathematical expression of the function represented by the neural network. 
/// The format of this string is of XML-type. 

std::string MultilayerPerceptron::get_expression(void)
{
   std::stringstream expression;
   
   expression << "<Flood version='3.0' class='MultilayerPerceptron' content='Expression'>" << std::endl;
   
   // Inputs scaling

   expression << "<InputsScaling>" << std::endl;
   expression << get_inputs_scaling_expression();
   expression << "</InputsScaling>" << std::endl;

   // Forward propagation

   expression << "<ForwardPropagation>" << std::endl;
   expression << get_forward_propagation_expression();
   expression << "</ForwardPropagation>" << std::endl;


   // Outputs unscaling

   expression << "<OutputsUnscaling>" << std::endl;
   expression << get_outputs_unscaling_expression();
   expression << "</OutputsUnscaling>" << std::endl;

   return(expression.str());
}


// Vector<std::string> get_inputs_name_expression(void) method

/// This method returns a vector of string with the names of the inputs to the neural network to be included in the 
/// multilayer perceptron expression. 

Vector<std::string> MultilayerPerceptron::get_inputs_name_expression(void)
{
   Vector<std::string> inputs_name_expression(inputs_number);

   if(input_variables_name.get_size() != inputs_number)
   {
      for(int i = 0; i < inputs_number; i++)
	  {
         std::stringstream buffer;
         buffer << "x" << i+1;
         inputs_name_expression[i] = buffer.str();
	  }
   }
   else
   {
      inputs_name_expression = input_variables_name;
   }

   return(inputs_name_expression);
}


// Vector<std::string> get_scaled_inputs_name_expression(void) method

/// This method returns a vector of string with the names of the scaled inputs to the neural network to be included in the 
/// multilayer perceptron expression. 

Vector<std::string> MultilayerPerceptron::get_scaled_inputs_name_expression(void)
{
   Vector<std::string> scaled_inputs_name_expression(inputs_number);

   Vector<std::string> inputs_name_expression = get_inputs_name_expression();

   for(int i = 0; i < inputs_number; i++)
   {
      std::stringstream buffer;
      buffer << "scaled_" << inputs_name_expression[i];
      scaled_inputs_name_expression[i] = buffer.str();
   }       

   return(scaled_inputs_name_expression);
}


// Vector<std::string> get_hidden_layer_inputs_name_expression(int) method

/// This method returns a vector of string with the names of the inputs to a given hidden layer to be included in the 
/// multilayer perceptron expression. 
/// @param index Index of hidden layer.

Vector<std::string> MultilayerPerceptron::get_hidden_layer_inputs_name_expression(int index)
{
   if(index == 0)
   {
	  return(get_scaled_inputs_name_expression());
   }
   else
   {
      return(get_hidden_layer_outputs_name_expression(index-1));
   }
}


// Vector<std::string> get_hidden_layer_outputs_name_expression(int)

/// This method returns a vector of string with the names of the outputs from a given hidden layer to be included in the 
/// multilayer perceptron expression. 
/// @param index Index of hidden layer.

Vector<std::string> MultilayerPerceptron::get_hidden_layer_outputs_name_expression(int index)
{
   int hidden_layer_size = hidden_layers_size[index];

   Vector<std::string> hidden_layer_outputs_name_expression(hidden_layer_size);

   for(int i = 0; i < hidden_layer_size; i++)
   {
      std::stringstream buffer;
      buffer << "y" << index+1  << i+1;
      hidden_layer_outputs_name_expression[i] = buffer.str();
   }       

   return(hidden_layer_outputs_name_expression);
}


// Vector<std::string> get_output_layer_inputs_name_expression(void) method

/// This method returns a vector of string with the names of the inputs to the output layer to be included in the 
/// multilayer perceptron expression. 

Vector<std::string> MultilayerPerceptron::get_output_layer_inputs_name_expression(void) 
{
   int hidden_layers_number = get_hidden_layers_number();

   return(get_hidden_layer_outputs_name_expression(hidden_layers_number-1));
}


// Vector<std::string> get_scaled_outputs_name_expression(void) method

/// This method returns a vector of string with the names of the scaled outputs to be included in the 
/// multilayer perceptron expression. 

Vector<std::string> MultilayerPerceptron::get_scaled_outputs_name_expression(void)
{
   Vector<std::string> scaled_outputs_name_expression(outputs_number);

   Vector<std::string> outputs_name_expression = get_outputs_name_expression();

   for(int i = 0; i < outputs_number; i++)
   {
      std::stringstream buffer;
      buffer << "scaled_" << outputs_name_expression[i];
      scaled_outputs_name_expression[i] = buffer.str();
   }       

   return(scaled_outputs_name_expression);
}


// Vector<std::string> get_outputs_name_expression(void) method

/// This method returns a vector of string with the names of the outputs to be included in the 
/// multilayer perceptron expression. 

Vector<std::string> MultilayerPerceptron::get_outputs_name_expression(void)
{
   Vector<std::string> outputs_name_expression(outputs_number);

   if(output_variables_name.get_size() != outputs_number)
   {
      for(int i = 0; i < outputs_number; i++)
	  {
         std::stringstream buffer;
         buffer << "y" << i+1;
         outputs_name_expression[i] = buffer.str();
	  }
   }
   else
   {
      outputs_name_expression = output_variables_name;
   }

   return(outputs_name_expression);
}


// std::string get_hidden_layer_activation_function_expression(int) method

/// This method returns a string with the name of the activation function of a hidden layer.
/// @param i Index of hidden layer. 

std::string MultilayerPerceptron::get_hidden_layer_activation_function_expression(int i)
{
    switch(hidden_layers_activation_function[i])
    {
       case Logistic:
       {
         return("logistic");
       }
       break;

	   case HyperbolicTangent:
       {
          return("tanh");
       }          
       break;
   
       case Threshold:
       {
          return("threshold");
       }             
       break;

       case SymmetricThreshold:
       {
          return("symmetric_threshold");
       }          
       break;

       case Linear:
       {
          return("");
       }
       break;

       default:
       {
           std::cerr << "Flood Error: MultilayerPerceptron class" << std::endl
                     << "std::string get_hidden_layer_activation_function_expression(int) method." << std::endl 
                     << "Unknown hidden layer activation function." << std::endl;

           exit(1); 
       }
       break;		  
   }
}


// std::string get_hidden_layer_expression(int) method

/// This method returns a string with the expression of the input-output relationship of a hidden layer.
/// @param i Index of hidden layer. 

std::string MultilayerPerceptron::get_hidden_layer_expression(int i)
{
   std::stringstream hidden_layer_expression;

   int hidden_layer_outputs_number = hidden_layers_size[i];
   int hidden_layer_inputs_number = get_hidden_layer_inputs_number(i);

   Vector<std::string> hidden_layer_inputs_name_expression = get_hidden_layer_inputs_name_expression(i);
   Vector<std::string> hidden_layer_outputs_name_expression = get_hidden_layer_outputs_name_expression(i);

   std::string hidden_layer_activation_function_expression = get_hidden_layer_activation_function_expression(i);

   double bias;
   double synaptic_weight;

   // Write expression

   for(int j = 0; j < hidden_layer_outputs_number; j++)
   {
      hidden_layer_expression << hidden_layer_outputs_name_expression[j] << "=";

	  bias = hidden_layers[i][j].get_bias();

      hidden_layer_expression << hidden_layer_activation_function_expression << "(";

      hidden_layer_expression << bias;

      for(int k = 0; k < hidden_layer_inputs_number; k++)
	  {
         synaptic_weight = hidden_layers[i][j].get_synaptic_weight(k);

         if(synaptic_weight >= 0)
   	     {
            hidden_layer_expression << "+";	     
	     }

         hidden_layer_expression << synaptic_weight << "*" << hidden_layer_inputs_name_expression[k];
	  }

	  hidden_layer_expression << ");" << std::endl;
   }

   return(hidden_layer_expression.str());
}


// std::string get_output_layer_expression(void) method

/// This method returns a string with the expression of the input-output relationship of the output layer.

std::string MultilayerPerceptron::get_output_layer_expression(void)
{
   std::stringstream output_layer_expression;

   Vector<std::string> output_layer_inputs_name_expression = get_output_layer_inputs_name_expression();

   std::string output_layer_activation_function_expression = get_output_layer_activation_function_expression();  

   Vector<std::string> scaled_outputs_name_expression = get_scaled_outputs_name_expression();

   int output_layer_inputs_number = get_output_layer_inputs_number();

   double bias;
   double synaptic_weight;

   for(int i = 0; i < outputs_number; i++)
   {
      output_layer_expression << scaled_outputs_name_expression[i];
	  
	  output_layer_expression << "=";
      
      output_layer_expression << output_layer_activation_function_expression;

	  output_layer_expression << "(";

      bias = output_layer[i].get_bias();

      output_layer_expression << bias;     

	  for(int j = 0; j < output_layer_inputs_number; j++)
	  {
         synaptic_weight = output_layer[i].get_synaptic_weight(j);	 

	     if(synaptic_weight >= 0.0)
		 {
		    output_layer_expression << "+";
         }

		 output_layer_expression << synaptic_weight << "*" << output_layer_inputs_name_expression[j];
	  }

	  output_layer_expression << ");" << std::endl;
   }

   return(output_layer_expression.str());
}


// std::string get_forward_propagation_expression(void) method

/// This method returns a string with the expression of the forward propagation process in a multilayer perceptron.

std::string MultilayerPerceptron::get_forward_propagation_expression(void)
{
   std::stringstream forward_propagation_expression;

   int hidden_layers_number = get_hidden_layers_number();

   for(int i = 0; i< hidden_layers_number; i++)
   {
      forward_propagation_expression << get_hidden_layer_expression(i);
   }

   forward_propagation_expression << get_output_layer_expression();

   return(forward_propagation_expression.str());
}


// std::string get_inputs_scaling_expression(void) method

/// This method returns a string with the expression of the inputs scaling process in a multilayer perceptron. 

std::string MultilayerPerceptron::get_inputs_scaling_expression(void)
{
   std::stringstream inputs_scaling_expression;

   // Inputs name

   Vector<std::string> inputs_name_expression = get_inputs_name_expression();

   // Scaled inputs name

   Vector<std::string> scaled_inputs_name_expression = get_scaled_inputs_name_expression();

   // Preprocess inputs

   switch(inputs_scaling_method)
   {
      case None:
      {
         // Do nothing
      }
      break;
   
      case MeanStandardDeviation:
      {
         // Preprocess inputs

         for(int i = 0; i < inputs_number; i++)
         {
            inputs_scaling_expression 
		    << scaled_inputs_name_expression[i] << "=(" << inputs_name_expression[i] << "-" << input_variables_mean[i] 
            << ")/" << input_variables_standard_deviation[i] << ";" << std::endl;
         }
      }
      break;
   
      case MinimumMaximum:
      {
         // Preprocess inputs

         for(int i = 0; i < inputs_number; i++)
         {
            inputs_scaling_expression 
			<< scaled_inputs_name_expression[i] << "=2*(" << inputs_name_expression[i] << "-" << input_variables_minimum[i] 
            << ")/(" << input_variables_maximum[i] << "-" << input_variables_minimum[i] << ")-1;" << std::endl;
         }
      }
      break;

      default:
      {
         std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                   << "std::string get_inputs_scaling_expression(void) method." << std::endl
                   << "Unknown scaling and unscaling method." << std::endl;
 
         exit(1);
      }// end default
      break;
   }

   return(inputs_scaling_expression.str());
}


// std::string get_outputs_unscaling_expression(void) method

/// This method returns a string with the expression of the outputs unscaling process in a multilayer perceptron. 

std::string MultilayerPerceptron::get_outputs_unscaling_expression(void)
{
   std::stringstream outputs_unscaling_expression;

   // Scaled outputs name

   Vector<std::string> scaled_outputs_name_expression = get_scaled_outputs_name_expression();

   // Outputs name

   Vector<std::string> outputs_name_expression = get_outputs_name_expression();

   // Postprocess outputs

   switch(outputs_unscaling_method)   
   {
      case None:
      {
         // Do nothing
      }
      break;
  
      case MeanStandardDeviation:
      {
         // Postprocess outputs

         for(int i = 0; i < outputs_number; i++)
         {
            outputs_unscaling_expression << outputs_name_expression[i] << "=" <<  output_variables_mean[i] << "+" 
                                         << output_variables_standard_deviation[i] << "*" << scaled_outputs_name_expression[i] << ";" << std::endl;
         }
      }
      break;

      case MinimumMaximum:
      {   
         // Postprocess outputs

         for(int i = 0; i < outputs_number; i++)
         {
            outputs_unscaling_expression << outputs_name_expression[i] << "=0.5*(" << outputs_name_expression[i] << "+1.0)*(" 
                       << output_variables_maximum[i] << "-" << output_variables_minimum[i] << ")+" 
                       << output_variables_minimum[i] << ";" << std::endl;       
         }
      }
      break;
   }

   return(outputs_unscaling_expression.str());
}


// std::string get_output_layer_activation_function_expression(void) method

/// This method returns a string with the name of the activation function of the output layer. 

std::string MultilayerPerceptron::get_output_layer_activation_function_expression(void)
{
    switch(output_layer_activation_function)
    {
       case Logistic:
       {
         return("logistic");
       }
       break;

	   case HyperbolicTangent:
       {
          return("tanh");
       }          
       break;
   
       case Threshold:
       {
          return("threshold");
       }             
       break;

       case SymmetricThreshold:
       {
          return("symmetric_threshold");
       }          
       break;

       case Linear:
       {
          return("");
       }
       break;

       default:
       {
           std::cerr << "Flood Error: MultilayerPerceptron class" << std::endl
                     << "std::string get_output_layer_activation_function_expression(void) method." << std::endl 
                     << "Unknown hidden layer activation function." << std::endl;

           exit(1); 
       }
       break;		  
   }
}


// void save_expression(const char*) method

/// This method saves the explicit mathematical expression addressed by the multilayer perceptron to a XML-type file. 
/// @param filename Name of expression XML-type file.

void MultilayerPerceptron::save_expression(const char* filename)
{
   std::fstream file;

   file.precision(6); 

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void save_expression(const char*) method." << std::endl
                << "Cannot open expression XML-type file."  << std::endl;

      exit(1);
   }

   file << get_expression();

   file.close();
}


// void save_Hinton_diagram(const char*) method

/// This method saves the data needed to plot the Hinton diagram of the multilayer perceptron in XML-type format. 
/// This diagram displays the biases and synaptic weights of each layer in the neural network.
/// @param filename Filename.

void MultilayerPerceptron::save_Hinton_diagram(const char* filename)
{
   std::fstream file;

   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void save_Hinton_diagramData(const char*) method." << std::endl
                << "Cannot open Hinton Diagram XML-type file." << std::endl;

      exit(1);
   }

   // Write file header

   file << "% Flood Neural Network. Hinton Diagram Data." << std::endl;

   // Hidden layers data

   int hidden_layers_number = get_hidden_layers_number();

   Vector< Matrix<double> > hidden_layers_parameters = get_hidden_layers_parameters();

   for(int i = 0; i < hidden_layers_number; i++)
   {
      file << "% Hidden layer " << i << "." << std::endl;
      
      file << hidden_layers_parameters[i] << std::endl;
   }

   // Output layer data

   Matrix<double> output_layer_parameters = get_output_layer_parameters();

   file << "% Output layer." << std::endl;

   file << output_layer_parameters << std::endl;

   file.close();
}


// double calculate_actual_epsilon(double) method

/// This method returns the actual epsilon to be used for a given parameter in numerical differentiation.
/// This depends on the the numerical epsilon method and the numerical epsilon value. 
///
/// @param parameter Parameter value. 

double MultilayerPerceptron::calculate_actual_epsilon(double parameter)
{
   double actual_epsilon;

   // Numerical epsilon method

   switch(numerical_epsilon_method)   
   {
      case Absolute:
      {
         actual_epsilon = numerical_epsilon;
      }             
      break;
            
      case Relative:
      {
         if(fabs(parameter) < 1.0)
         {
            actual_epsilon = numerical_epsilon;              
         }
         else
         {     
            actual_epsilon = numerical_epsilon*fabs(parameter);
         }
      }                          
      break;           

      default:
      {
          std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                    << "double calculate_actual_epsilon(double) method." << std::endl
                    << "Unknown numerical epsilon method." << std::endl;
 
          exit(1);
      }// end default
      break;
   }// end numerical epsilon switch

   return(actual_epsilon);
}


// Matrix<double> calculate_hidden_layer_Jacobian(int, const Vector<double>&) method

/// This method returns the Jacobian matrix of a hidden layer for a given input to that layer. 
/// This is composed by the derivatives of the hidden layer outputs with respect to their inputs. 
/// The number of rows is the number of neurons in the hidden layer.
/// The number of columns is the number of inputs to that layer.
/// @param i Index of hidden layer.
/// @param hidden_layer_input Input to hidden layer.

Matrix<double> MultilayerPerceptron::calculate_hidden_layer_Jacobian
(int index, const Vector<double>& hidden_layer_input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = get_hidden_layers_number();

   if(index < 0)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void calculate_hidden_layer_Jacobian(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be equal or greater than zero." << std::endl;

      exit(1);
   }

   if(index >= hidden_layers_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void calculate_hidden_layer_Jacobian(int, const Vector<double>&) method." << std::endl
                << "Index of hidden layer must be less than number of hidden layers." << std::endl;

      exit(1);
   }

   #endif

   // Get number of inputs of hidden layer

   int hidden_layer_inputs_number = get_hidden_layer_inputs_number(index); 

   #ifdef _DEBUG 

   int size = hidden_layer_input.get_size();

   if(size != hidden_layer_inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void calculate_hidden_layer_Jacobian(int, const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs of hidden layer." << std::endl;

      exit(1);
   }

   #endif

   int hidden_layer_size = hidden_layers_size[index];

   Matrix<double> hidden_layer_Jacobian(hidden_layer_size, hidden_layer_inputs_number);

   Vector<double> hidden_layer_combination = calculate_hidden_layer_combination(index, hidden_layer_input);

   Vector<double> hidden_layer_activation_derivative 
   = calculate_hidden_layer_activation_derivative(index, hidden_layer_combination);

   for(int i = 0; i < hidden_layer_size; i++)
   {
      for(int j = 0; j < hidden_layer_inputs_number; j++)
      {
         hidden_layer_Jacobian[i][j] 
         = hidden_layer_activation_derivative[i]*hidden_layers[index][i].get_synaptic_weight(j);
      }
   }

   return(hidden_layer_Jacobian);
}


// Matrix<double> calculate_output_layer_Jacobian(const Vector<double>&);

/// This method returns the Jacobian matrix of the output layer for a given input to that layer. 
/// This is composed by the derivatives of the output layer outputs with respect to their inputs. 
/// The number of rows is the number of outputs.
/// The number of columns is the number of inputs to that layer.
///
/// @param output_layer_input Input to output layer.

Matrix<double> MultilayerPerceptron::calculate_output_layer_Jacobian(const Vector<double>& output_layer_input)
{
   int hidden_layers_number = get_hidden_layers_number();

   int output_layer_inputs_number = hidden_layers_size[hidden_layers_number-1];

   #ifdef _DEBUG 

   int size = output_layer_input.get_size();

   if(size != output_layer_inputs_number)
   {
      std::cerr << "Flood Error: MultilayerPerceptron class." << std::endl
                << "void calculate_output_layer_Jacobian(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs of output layer." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> output_layer_combination = calculate_output_layer_combination(output_layer_input);

   Vector<double> output_layer_activation_derivative 
   = calculate_output_layer_activation_derivative(output_layer_combination);

   Matrix<double> output_layer_Jacobian(outputs_number, output_layer_inputs_number);

   for(int i = 0; i < outputs_number; i++)
   {
      for(int j = 0; j < output_layer_inputs_number; j++)
      {
         output_layer_Jacobian[i][j] 
         = output_layer_activation_derivative[i]*output_layer[i].get_synaptic_weight(j);
      }
   }

   return(output_layer_Jacobian);
}


// int get_parameters_number(void) method

/// This method returns the number of parameters in the neural network. 
/// The number of parameters is the sum of all the neural parameters (biases and synaptic weights) and 
/// independent parameters.

int MultilayerPerceptron::get_parameters_number(void)
{
   int neural_parameters_number = get_neural_parameters_number();
   int independent_parameters_number = get_independent_parameters_number();

   int parameters_number = neural_parameters_number + independent_parameters_number;

   return(parameters_number);
}

}

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

