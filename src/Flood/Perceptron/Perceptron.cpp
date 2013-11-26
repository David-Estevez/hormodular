/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   P E R C E P T R O N   C L A S S                                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Perceptron.h"
#include "../Utilities/Vector.h"

namespace Flood
{

/// Default constructor. It creates a perceptron object with zero inputs.
/// The neuron's bias is initialized to zero. 
/// This constructor also initializes the rest of class members to their default values:
/// <ul>
/// <li> Activation function: Hyperbolic tangent.
/// <li> Display: True.
/// </ul>  
	
Perceptron::Perceptron(void)
{
   set();
}


/// Inputs number constructor. It creates a perceptron object with a given number of inputs. 
/// The neuron's free paramameters (bias and synaptic weights) are initialized at random with a normal 
/// distribution of mean 0 and standard deviation 1.
/// This constructor also initializes the rest of class members to their default values:
/// <ul>
/// <li> Activation function: Hyperbolic tangent.
/// <li> Display: True.
/// </ul> 
/// @param new_inputs_number Number of inputs in the neuron.

Perceptron::Perceptron(int new_inputs_number)
{
   set(new_inputs_number);
}


/// Inputs number and initialization constructor. This creates a perceptron with a given number of inputs.
/// It also initializes the bias and synaptic weights with a given value. 
/// @param new_inputs_number Number of inputs in the neuron.
/// @param new_parameters_value Bias and synaptic weights initialization value. 

Perceptron::Perceptron(int new_inputs_number, double new_parameters_value)
{
	set(new_inputs_number, new_parameters_value);
}


/// File constructor. It creates a perceptron object by loading its members from a XML-type file. 
/// Please check the format of that file in the User's Guide. 
/// @param filename Name of perceptron XML-type.

Perceptron::Perceptron(const char* filename)
{
   load(filename);   
}


/// Copy constructor. It creates a percdeptron object by copying its members with those for other perceptron object. 
/// @param other_perceptron Perceptron object to be copied.

Perceptron::Perceptron(const Perceptron& other_perceptron)
{
   activation_function = other_perceptron.activation_function;

   inputs_number = other_perceptron.inputs_number;

   bias = other_perceptron.bias;
   
   synaptic_weights = other_perceptron.synaptic_weights;

   display = other_perceptron.display;
}


/// Destructor.

Perceptron::~Perceptron(void)
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. It assigns to the current perceptron the members of an existing perceptron.
/// @param other_perceptron Assigning perceptron object .

Perceptron& Perceptron::operator=(const Perceptron& other_perceptron)
{
   if(this != &other_perceptron) 
   {
      activation_function = other_perceptron.activation_function;

      inputs_number = other_perceptron.inputs_number;

      bias = other_perceptron.bias;
   
      synaptic_weights = other_perceptron.synaptic_weights;

      display = other_perceptron.display;
   }

   return(*this);
}



// METHODS

// ActivationFunction get_activation_function(void) method

/// This method returns the activation function of the neuron. 

Perceptron::ActivationFunction& Perceptron::get_activation_function(void)
{
   return(activation_function);                           
}


// std::string get_activation_function_name(void) method

/// This method returns a string with the name of the activation function of the neuron. 

std::string Perceptron::get_activation_function_name(void)
{
   switch(activation_function)
   {
      case Perceptron::Logistic:   
      {
         return("Logistic");
      }
      break;

      case Perceptron::HyperbolicTangent:   
      {
         return("HyperbolicTangent");
      }
      break;

      case Perceptron::Threshold:   
      {
         return("Threshold");
      }
      break;

      case Perceptron::SymmetricThreshold:   
      {
         return("SymmetricThreshold");
      }
      break;

      case Perceptron::Linear:   
      {
         return("Linear");
      }
      break;

      default:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "std::string get_activation_function(void) method." << std::endl
                   << "Unknown activation function." << std::endl;

         exit(1);
      }
      break;
   }
}


// double get_bias(void) method

/// This method returns the bias value of the neuron.

double Perceptron::get_bias(void)
{
   return(bias);
}


// Vector<double> get_synaptic_weights(void)

/// This method returns the synaptic weight values of the neuron.

Vector<double>& Perceptron::get_synaptic_weights(void)
{
   return(synaptic_weights);
}


// double get_synaptic_weight(int) method

/// This method returns the synaptic weight value with index i of the neuron.
/// @param synaptic_weight_index Synaptic weight index.
 
double Perceptron::get_synaptic_weight(int synaptic_weight_index)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(synaptic_weight_index < 0 || synaptic_weight_index >= inputs_number)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "double get_synaptic_weight(int) method." << std::endl
                << "Index of synaptic weight must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   // Get single synaptic weights

   return(synaptic_weights[synaptic_weight_index]);   
}


// bool get_display(void) method

/// This method returns true if messages from this class are to be displayed on the screen, or false if messages 
/// from this class are not to be displayed on the screen.

bool Perceptron::get_display(void)
{
   return(display);
}


//  void set(void) method

/// This method sets the number of inputs to zero and the rest of members to their default values. 

void Perceptron::set(void)
{
   activation_function = HyperbolicTangent;

   inputs_number = 0;

   initialize_bias_normal(0.0, 0.2);
   
   display = true;
}


// void set(int) method

/// This method sets a new number of inputs.
/// It also sets the other members of this object to their defaul values. 
/// @param new_inputs_number Number of inputs in the neuron. 

void Perceptron::set(int new_inputs_number)
{
   // Set synaptic weights

   activation_function = HyperbolicTangent;

   inputs_number = new_inputs_number;

   synaptic_weights.set(inputs_number);

   // Init bias and synaptic weights at random 
   
   initialize_bias_normal(0.0, 0.2);
   initialize_synaptic_weights_normal(0.0, 0.2);
   
   display = true;
}


// void set(int, double) method

/// This method sets the number of inputs to a given value and initializes the bias and the synaptic weights 
/// with a given value. 
/// @param new_inputs_number Number of inputs in the neuron. 
/// @param new_parameters_value Parameters initialization value.  

void Perceptron::set(int new_inputs_number, double new_parameters_value)
{
   inputs_number = new_inputs_number;

   activation_function = HyperbolicTangent;

   bias = new_parameters_value;
   synaptic_weights.set(inputs_number, new_parameters_value);

   display = true;
}


// void set(const Perceptron&)

/// This method sets the members of this perceptron object with those from other perceptron object. 
/// @param other_perceptron Setting perceptron object. 

void Perceptron::set(const Perceptron& other_perceptron)
{
   activation_function = other_perceptron.activation_function;

   inputs_number = other_perceptron.inputs_number;

   bias = other_perceptron.bias;
   
   synaptic_weights = other_perceptron.synaptic_weights;

   display = other_perceptron.display;
}


// void set_activation_function(const ActivationFunction&) method

/// This method sets a new activation function in the neuron. 
/// @param new_activation_function Activation function.

void Perceptron::set_activation_function(const Perceptron::ActivationFunction& new_activation_function)
{
   activation_function = new_activation_function;
}


// void set_activation_function(const std::string&) method

/// This method sets a new activation function in the perceptron with a string containing 
/// the name of the activation function.
/// @param new_activation_function_name String with name of activation function. 

void Perceptron::set_activation_function(const std::string& new_activation_function_name)
{
   if(new_activation_function_name == "Logistic")
   {
      activation_function = Logistic;
   }
   else if(new_activation_function_name == "HyperbolicTangent")
   {
      activation_function = HyperbolicTangent;
   }
   else if(new_activation_function_name == "Threshold")
   {
      activation_function = Threshold;
   }
   else if(new_activation_function_name == "SymmetricThreshold")
   {
      activation_function = SymmetricThreshold;
   }
   else
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void set_activation_function(const std::string&) method." << std::endl
				<< "Unknown activation function." << std::endl;

      exit(1);   
   }
}


// void set_bias(double) method

/// This method sets a new bias value for the perceptron.
/// @param new_bias Bias value.
 
void Perceptron::set_bias(double new_bias)
{
   bias = new_bias;   
}


// void set_synaptic_weights(const Vector<double>&) method

/// This method a new set of synaptic weights for the perceptron.
/// @param new_synaptic_weights Synaptic weight values.
 
void Perceptron::set_synaptic_weights(const Vector<double>& new_synaptic_weights)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_synaptic_weights.get_size() != inputs_number)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void set_synaptic_weights(const Vector<double>&) method." << std::endl
                << "Size of synaptic weights vector must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Set synaptic weights
   
   synaptic_weights = new_synaptic_weights;
}


// void set_synaptic_weight(int, double) method

/// This method sets the synaptic weight value with index i for the neuron.
/// @param synaptic_weight_index Synaptic weight index.
/// @param new_synaptic_weight Synaptic weight value.

void Perceptron::set_synaptic_weight(int synaptic_weight_index, double new_synaptic_weight)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(synaptic_weight_index < 0 || synaptic_weight_index >= inputs_number)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void set_synaptic_weight(int, double) method." << std::endl
                << "Index of synaptic weight must be equal or greater than zero and less than number of inputs." 
                << std::endl;

      exit(1);
   }

   #endif

   // Set single synaptic weight

   synaptic_weights[synaptic_weight_index] = new_synaptic_weight;
}


// void set_display(bool) method

/// This method sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.
 
void Perceptron::set_display(bool new_display)
{
   display = new_display;   
}


// void set_inputs_number(int) method

/// This method sets a new number of inputs in the neuron.
/// The new free paramameters (bias and synaptic weights) are initialized at random with a normal distribution of 
/// mean 0 and standard deviation 1.
/// @param new_inputs_number Number of inputs in the neuton.
 
void Perceptron::set_inputs_number(int new_inputs_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(new_inputs_number < 0)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void set_inputs_number(int) method." << std::endl
				<< "Number of inputs (" << new_inputs_number << ") must be equal or greater than zero: " 
				<< std::endl;

      exit(1);
   }

   #endif

   inputs_number = new_inputs_number;

   synaptic_weights.set_size(inputs_number);

   // Init bias and synaptic weights at random 

   initialize_bias_normal(0.0,1.0);
   initialize_synaptic_weights_normal(0.0,1.0);
}


// int get_parameters_number(void) method

/// This method returns the number of parameters (bias and synaptic weights) in the perceptron.

int Perceptron::get_parameters_number(void)
{
   int parameters_number = 1 + inputs_number;

   return(parameters_number);
}


// Vector<double> get_parameters(void) method

/// This method returns the parameters (bias and synaptic weights) of the perceptron.

Vector<double> Perceptron::get_parameters(void)
{
   int parameters_number = get_parameters_number();

   Vector<double> parameters(parameters_number);

   parameters[0] = bias;

   for(int i = 0; i < inputs_number; i++)
   {
      parameters[1+i] = synaptic_weights[i];
   }

   return(parameters); 
}


// void set_parameters(const Vector<double>&) method

/// This method set a new set of parameters (bias and synaptic weights) to the perceptron.
/// @param new_parameters New set of parameters

void Perceptron::set_parameters(const Vector<double>& new_parameters)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = new_parameters.get_size();

   if(size != 1+inputs_number)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void set_parameters(const Vector<double>&) method." << std::endl
                << "Size must be equal to one plus number of inputs." << std::endl;

      exit(1);
   }

   #endif

   bias = new_parameters[0];

   for(int i = 0; i < inputs_number; i++)
   {
      synaptic_weights[i] = new_parameters[i+1];
   }
}


// void initialize_bias(double) method

/// This method initializes the bias with a given value. 
/// @param value Initialization value. 

void Perceptron::initialize_bias(double value)
{
   bias = value;
}


// void initialize_bias_uniform(double, double) method

/// This method initializes the neuron's bias with a random value chosen from a uniform distribution.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.

void Perceptron::initialize_bias_uniform(double minimum, double maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(minimum > maximum)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl 
                << "initialize_bias_uniform(double, double) method." << std::endl
                << "Minimum value must be less than maximum value." << std::endl;

      exit(1);
   }

   #endif

   bias = calculate_random_uniform(minimum, maximum);
}


// void initialize_synaptic_weights(double) method

void Perceptron::initialize_synaptic_weights(double value)
{
   synaptic_weights.initialize(value);
}


// void initialize_synaptic_weights_uniform(double, double) method

/// This method initializes the neuron's synaptic weights with random values chosen from an uniform distribution.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.

void Perceptron::initialize_synaptic_weights_uniform(double minimum, double maximum)
{
   synaptic_weights.initialize_uniform(minimum, maximum);
}


// void initialize_bias_normal(double, double) method

/// This method initializes the neuron's bias with random values chosen from a normal distribution.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.

void Perceptron::initialize_bias_normal(double mean, double standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(standard_deviation < 0.0)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl 
                << "initialize_bias_normal(double, double) method." << std::endl
                << "Standard deviation must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   bias = calculate_random_normal(mean, standard_deviation);
}


// void initialize_synaptic_weights_normal(double, double) method

/// This method initializes the neuron's synaptic weights with random values chosen from a normal distribution.
/// @param mean Mean of normal distribution.
/// @param standard_deviation Standard deviation of normal distribution.

void Perceptron::initialize_synaptic_weights_normal(double mean, double standard_deviation)
{
   synaptic_weights.initialize_normal(mean, standard_deviation);
}


// void initialize_parameters(double) method

/// This method initializes the bias and the synaptic weights with a given value. 
/// @param value Parameters initialization value. 

void Perceptron::initialize_parameters(double value)
{
   bias = value;
   synaptic_weights.initialize(value);
}


// double calculate_combination(const Vector<double>&) method

/// This method returns the combination to the neuron for a set of input signals, using the dot product 
/// combination function.
/// @param input Set of input signals to the neuron.

double Perceptron::calculate_combination(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(inputs_number == 0)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl 
                << "calculate_combination(const Vector<double>&) method." << std::endl
                << "Number of inputs in the neuron must be greater than zero." << std::endl;

      exit(1);
   }
   else if(input.get_size() != inputs_number)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "double calculate_combination(const Vector<double>&) method." << std::endl
                << "Size of input must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Calculate combination
        
   return(bias + synaptic_weights.dot(input));   
}


// double calculate_activation(double) method

/// This method returns the activation from the neuron for a combination.
/// The output depends on the activation function used.
/// @param combination Combination of the neuron.

double Perceptron::calculate_activation(double combination)
{
   switch(activation_function)   
   {
      case Perceptron::Logistic:
      {  
         return(1.0/(1.0 + exp(-combination)));
      }
      break;
                                     
      case Perceptron::HyperbolicTangent:
      {  
         return(tanh(combination));
      }
      break;

      case Perceptron::Threshold:
      {  
         if(combination < 0)
         {
            return(0.0);
         }
         else
         {
            return(1.0);
         }
      }
      break;

      case Perceptron::SymmetricThreshold:
      {  
         if(combination < 0)
         {
            return(-1.0);
         }
         else
         {
            return(1.0);
         }
      }
      break;

      case Perceptron::Linear:
      {  
         return(combination);        
      }
      break;
      
      default:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "calculate_activation(double) method." << std::endl
                   << "Unknown activation function." << std::endl;

         exit(1);
      }
      break;
   }
}


// double calculate_activation_derivative(double) method

/// This method returns the activation derivative of the neuron for a combination.
/// The output derivative depends on the activation function used.
/// @param combination Combination of the neuron.

double Perceptron::calculate_activation_derivative(double combination)
{
   switch(activation_function)   
   {
      case Perceptron::Logistic:
      {
         return(exp(combination)/pow(1.0 + exp(combination), 2));
      }
      break;
                                     
      case Perceptron::HyperbolicTangent:
      {
         return(1.0 - pow(tanh(combination), 2));
      }
      break;

      case Perceptron::Threshold:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "calculate_activation_derivative(double) method." << std::endl
                   << "Threshold activation function is not derivable." << std::endl;

         exit(1);         
      }
      break;

      case Perceptron::SymmetricThreshold:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "calculate_activation_derivative(double) method." << std::endl
                   << "Symmetric threshold activation function is not derivable." << std::endl;

         exit(1);         
      }
      break;

      case Perceptron::Linear:
      {
         return(1.0);
      }
      break;

      default:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "calculate_activation_derivative(double) method." << std::endl
                   << "Unknown activation function." << std::endl;

         exit(1);
      }
      break;
   }
}


// double calculate_activation_second_derivative(double) method

/// This method returns the activation second derivative of the neuron for a combination.
/// The second derivative of the output depends on the activation function used.
/// @param combination Combination of the neuron.

double Perceptron::calculate_activation_second_derivative(double combination)
{
   switch(activation_function)   
   {
      case Perceptron::Logistic:
      {
         return(-exp(combination)*(exp(combination) - 1.0)/pow(exp(combination + 1), 3));
      }
      break;
                                     
      case Perceptron::HyperbolicTangent:
      {
         return(-2.0*tanh(combination)*(1.0 - pow(tanh(combination),2)));
      }
      break;

      case Perceptron::Threshold:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "calculate_activation_second_derivative(double) method." << std::endl
                   << "Threshold activation function is not derivable." << std::endl;

         exit(1);         
      }
      break;

      case Perceptron::SymmetricThreshold:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "calculate_activation_second_derivative(double) method." << std::endl
                   << "Symmetric threshold activation function is not derivable." << std::endl;

         exit(1);         
      }
      break;

      case Perceptron::Linear:
      {
         return(0.0);        
      }
      break;

      default:
      {
         std::cerr << "Flood Error: Perceptron class." << std::endl 
                   << "calculate_activation_second_derivative(double) method." << std::endl
                   << "Unknown activation function." << std::endl;

         exit(1);
      }
      break;
   }
}


// double calculate_output(const Vector<double>&) method

/// This method returns the output from the neuron for a set of input signals.
/// The output depends on the activation function used.
/// @param input Set of input signals to the neuron.

double Perceptron::calculate_output(const Vector<double>& input)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int size = input.get_size();

   if(size != inputs_number)
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl 
                << "double calculate_output(const Vector<double>&) method." << std::endl
                << "Size must be equal to number of inputs." << std::endl;

      exit(1);
   }

   #endif

   // Calculate output 

   return(calculate_activation(calculate_combination(input)));  
}


// std::string to_XML(bool) method

/// This method returns a XML-type string representation of this perceptron object. 
/// @param show_declaration True if a XML-type declaration is to be included at the begining, false otherwise. 

std::string Perceptron::to_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Header     
   
   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='Perceptron'>" << std::endl;
   }

   // Number of inputs

   buffer << "<InputsNumber>" << std::endl
          << inputs_number << std::endl
		  << "</InputsNumber>" << std::endl;

   // Activation function

   buffer << "<ActivationFunction>" << std::endl
	      << get_activation_function_name() << std::endl
          << "</ActivationFunction>" << std::endl;

   // Bias

   buffer << "<Bias>" << std::endl
          << bias << std::endl
          << "</Bias>" << std::endl;

   // Synaptic weights

   buffer << "<SynapticWeights>" << std::endl
          << synaptic_weights << std::endl   
          << "</SynapticWeights>" << std::endl;

   // Display

   buffer << "<Display>" << std::endl
          << display << std::endl   
          << "</Display>" << std::endl;

   return(buffer.str());
}


// void print(void) method

/// This method prints to the screen the members of this object in XML-type format. 

void Perceptron::print(void)
{
   if(display)
   {
      std::cout << to_XML(true);
   }
}


// void save(const char*) method

/// This method saves to a XML-type file a string representation of this object. 
/// @param filename Name of perceptron XML-type file. 

void Perceptron::save(const char* filename)
{
   std::fstream file; 

   // Open file

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void save(const char*) method." << std::endl
                << "Cannot open perceptron XML-type file." << std::endl;

      exit(1);
   }

   // Write file 

   file << to_XML(true);

   // Close file

   file.close();
}


// void load(const char*) method

/// This method loads from a XML-type file the members of the neuron. 
/// Please mind about the file format, which is specified in the User's Guide.

void Perceptron::load(const char* filename)
{
   std::fstream file;

   file.open(filename, std::ios::in);
  
   if(!file.is_open())
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open perceptron XML-type file." << std::endl;

      exit(1);
   }

   std::string line;
   std::string word;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='Perceptron'>") 
   {
//      std::cerr << "Flood Error: Perceptron class." << std::endl
//                << "void load(const char*) method." << std::endl
//				<< "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   // Number of inputs 

   file >> word;

   if(word != "<InputsNumber>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown inputs number begin tag: " << line << std::endl;
 
      exit(1);
   }

   int new_inputs_number;
   file >> new_inputs_number;
   set_inputs_number(new_inputs_number);

   file >> word;

   if(word != "</InputsNumber>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown inputs number end tag: " << line << std::endl;
 
      exit(1);
   }

   // Activation function

   file >> word;

   if(word != "<ActivationFunction>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown activation function begin tag: " << line << std::endl;
 
      exit(1);
   }

   std::string new_activation_function_name;
   file >> new_activation_function_name;
   set_activation_function(new_activation_function_name);

   file >> word;

   if(word != "</ActivationFunction>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown activation function end tag: " << line << std::endl;
 
      exit(1);
   }

   // Bias

   file >> word;

   if(word != "<Bias>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown bias begin tag: " << line << std::endl;
 
      exit(1);
   }

   double new_bias;
   file >> new_bias;
   set_bias(new_bias);

   file >> word; 

   if(word != "</Bias>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown bias end tag: " << line << std::endl;
 
      exit(1);
   }

   // Synaptic weights

   file >> word;

   if(word != "<SynapticWeights>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown synaptic weights begin tag: " << line << std::endl;
 
      exit(1);
   }

   Vector<double> new_synaptic_weights(inputs_number);
   file >> new_synaptic_weights;
   set_synaptic_weights(new_synaptic_weights);

   file >> word;

   if(word != "</SynapticWeights>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown synaptic weights end tag: " << line << std::endl;
 
      exit(1);
   }

   // Display 

   file >> word;

   if(word != "<Display>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown display begin tag: " << line << std::endl;
 
      exit(1);
   }

   bool new_display;
   file >> new_display;
   set_display(new_display);

   file >> word;

   if(word != "</Display>") 
   {
      std::cerr << "Flood Error: Perceptron class." << std::endl
                << "void load(const char*) method." << std::endl
				<< "Unknown display end tag: " << line << std::endl;
 
      exit(1);
   }

   file.close();
}


// double calculate_random_uniform(double, double) method

/// This method returns a random number chosen from a uniform distribution. 
/// @param minimum Minimum value.
/// @param maximum Maximum value.

double Perceptron::calculate_random_uniform(double minimum, double maximum)
{
   double random = (double)rand()/(RAND_MAX+1.0);

   double random_uniform = minimum + (maximum-minimum)*random;

   return(random_uniform);
}


// double calculate_random_normal(double, double) method

/// This method returns a random number chosen from a normal distribution. 
/// @param mean Mean value of normal distribution.
/// @param standard_deviation Standard deviation value of normal distribution. 

double Perceptron::calculate_random_normal(double mean, double standard_deviation)
{
   double random_normal = 0.0;

   const double pi = 4.0*atan(1.0);

   double random_uniform_1;
   double random_uniform_2;

   do
   {
      random_uniform_1 = (double)rand()/(RAND_MAX+1.0);

   }while(random_uniform_1 == 0.0);

   random_uniform_2 = (double)rand()/(RAND_MAX+1.0);

   // Box-Muller transformation

   random_normal = mean + sqrt(-2.0*log(random_uniform_1))*sin(2.0*pi*random_uniform_2)*standard_deviation;

   return(random_normal);
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

