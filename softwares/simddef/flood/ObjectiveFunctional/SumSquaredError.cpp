/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   S U M   S Q U A R E D   E R R O R   C L A S S                                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

// Flood includes

#include "SumSquaredError.h"

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

namespace Flood
{

// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a sum squared error objective functional object not associated to any 
/// multilayer perceptron and not measured on any input-target data set.
/// It also initializes all the rest of class members to their default values.

SumSquaredError::SumSquaredError(void) : ObjectiveFunctional()
{
   input_target_data_set_pointer = NULL;
}


// MULTILAYER PERCEPTRON CONSTRUCTOR

/// Multilayer perceptron constructor. It creates a sum squared error objective functional object associated to a 
/// multilayer perceptron object but not measured on any input-target data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.

SumSquaredError::SumSquaredError(MultilayerPerceptron* new_multilayer_perceptron_pointer) 
: ObjectiveFunctional(new_multilayer_perceptron_pointer)
{
   input_target_data_set_pointer = NULL;
}


// INPUT-TARGET DATA SET CONSTRUCTOR

/// Multilayer perceptron constructor. It creates a sum squared error objective functional object not associated to any 
/// multilayer perceptron but to be measured on an input-target data set object.
/// It also initializes all the rest of class members to their default values.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

SumSquaredError::SumSquaredError(InputTargetDataSet* new_input_target_data_set_pointer)
: ObjectiveFunctional()
{
   input_target_data_set_pointer = new_input_target_data_set_pointer;
}


// GENERAL CONSTRUCTOR

/// General constructor. It creates a sum squared error objective functional object associated to a multilayer 
/// perceptron and measured on an input-target data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

SumSquaredError::SumSquaredError(MultilayerPerceptron* new_multilayer_perceptron_pointer, 
InputTargetDataSet* new_input_target_data_set_pointer): ObjectiveFunctional(new_multilayer_perceptron_pointer)
{
   input_target_data_set_pointer = new_input_target_data_set_pointer;
}


// DESTRUCTOR

/// Destructor.

SumSquaredError::~SumSquaredError(void) 
{
}


// METHODS


// void set(void) method

/// This method sets the multilayer perceptron and input-target data set object pointers to NULL. 
/// It also initializes all the rest of class members to their default values.

void SumSquaredError::set(void)
{
   multilayer_perceptron_pointer = NULL;
   input_target_data_set_pointer = NULL;
   set_default();
}


// void set(MultilayerPerceptron*) method

/// This method sets a new multilayer perceptron pointer, and sets the input-target data set pointer to NULL. 
/// It also initializes all the rest of class members to their default values.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.

void SumSquaredError::set(MultilayerPerceptron* new_multilayer_perceptron_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;
   input_target_data_set_pointer = NULL;
   set_default();
}


// void set(InputTargetDataSet*) method

/// This method sets the multilayer perceptron pointer to null, and sets a new input-target data set pointer. 
/// It also initializes all the rest of class members to their default values.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

void SumSquaredError::set(InputTargetDataSet* new_input_target_data_set_pointer)
{
   multilayer_perceptron_pointer = NULL;
   input_target_data_set_pointer = new_input_target_data_set_pointer;
   set_default();
}


// void set(MultilayerPerceptron*, InputTargetDataSet*) method

/// This method sets new multilayer perceptron and input-target data set pointers. 
/// It also initializes all the rest of class members to their default values.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

void SumSquaredError::set(MultilayerPerceptron* new_multilayer_perceptron_pointer, InputTargetDataSet* new_input_target_data_set_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;
   input_target_data_set_pointer = new_input_target_data_set_pointer;
   set_default();
}


// void set_input_target_data_set_pointer(InputTargetDataSet*) method

/// This method sets a pointer to an input-data set object on which the objective functional is to be measured.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

void SumSquaredError::set_input_target_data_set_pointer(InputTargetDataSet* new_input_target_data_set_pointer)
{
   input_target_data_set_pointer = new_input_target_data_set_pointer;
}


// double calculate_objective(void) method

/// This method returns the objective value of a multilayer perceptron according to the sum squared error on 
/// an input-target data set.

double SumSquaredError::calculate_objective(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_objective(void) method." << std::endl
                << "Pointer to multilayer perceptron object cannot be NULL." << std::endl;

        exit(1);
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_objective(void) method." << std::endl
                << "Pointer to input-target data set object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();

   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifdef _DEBUG 

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();

   if(inputs_number != input_variables_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_objective(void) method." << std::endl
                << "Number of inputs in multilayer perceptron must be equal to " 
                << "number of input variables in input-target data set." << std::endl;

      exit(1);
   }

   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   if(outputs_number != target_variables_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_objective(void) method." << std::endl
                << "Number of outputs in multilayer perceptron must be equal to " 
                << "number of target variables in input-target data set." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);
   Vector<double> target(outputs_number);
   Vector<double> instance_error(outputs_number);

   double training_error = 0.0;

   for(int i = 0; i < training_instances_number; i++)
   {
      // Input vector

	  input = input_target_data_set_pointer->get_training_input_instance(i);

      // Output vector

      output = multilayer_perceptron_pointer->calculate_output(input);

      // Target vector

      target = input_target_data_set_pointer->get_training_target_instance(i);

      // Error

	   instance_error = output - target;

      // Sum of squares error

      training_error += instance_error.dot(instance_error);           
   }

   return(training_error);
}


// double calculate_validation_error(void) method

/// This method returns the sum squared error of the multilayer perceptron measured on the validation instances of the 
/// input-target data set.

double SumSquaredError::calculate_validation_error(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_validation_error(void) method." << std::endl
                << "Pointer to multilayer perceptron object cannot be NULL." << std::endl;

        exit(1);
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_validation_error(void) method." << std::endl
                << "Pointer to input-target data set object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifdef _DEBUG 

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   if(inputs_number != input_variables_number || outputs_number != target_variables_number)
   {
      std::cout << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_validation_error(void) method." << std::endl
                << "Number of inputs and outputs in multilayer perceptron must be equal to " 
                << "number of input and output variables in input-target data set." << std::endl;

      exit(1);
   }

   #endif

   int validation_instances_number = input_target_data_set_pointer->get_validation_instances_number();

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);
   Vector<double> target(outputs_number);

   double validation_error = 0.0;

   for(int i = 0; i < validation_instances_number; i++)
   {
      // Input vector

	  input = input_target_data_set_pointer->get_validation_input_instance(i);

      // Output vector

      output = multilayer_perceptron_pointer->calculate_output(input);

      // Target vector

      target = input_target_data_set_pointer->get_validation_target_instance(i);

      // Sum of squares error

      validation_error += (output - target).dot(output - target);           
   }

   return(validation_error);
}


// Vector<double> calculate_objective_gradient(void) method

/// This method calculates the objective gradient by means of the back-propagation algorithm, 
/// and returns it in a single vector of size the number of neural parameters. 

Vector<double> SumSquaredError::calculate_objective_gradient(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_objective_gradient(void) method." << std::endl
                << "Pointer to multilayer perceptron object cannot be NULL." << std::endl;

        exit(1);
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_objective_gradient(void) method." << std::endl
                << "Pointer to input-target data set object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   // Multilayer perceptron 

   int hidden_layers_number = multilayer_perceptron_pointer->get_hidden_layers_number();

   Vector<int> hidden_layers_size = multilayer_perceptron_pointer->get_hidden_layers_size();

   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   int forward_propagation_derivative_size = 2*hidden_layers_number + 2;

   Vector< Vector<double> > forward_propagation_derivative(forward_propagation_derivative_size);

   // Input-target data set

   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();    Vector<double> training_input_instance(input_variables_number);
   Vector<double> training_target_instance(target_variables_number);

   // Output and hidden errors

   Vector<double> output_errors(outputs_number);
   Vector< Vector<double> > hidden_errors(hidden_layers_number);

   for(int h = 0; h < hidden_layers_number; h++)
   {
      hidden_errors[h].set_size(hidden_layers_size[h]);
   }

   // Hidden and output layers gradients

   int hidden_layers_parameters_number = multilayer_perceptron_pointer->get_hidden_layers_parameters_number();
   int output_layer_parameters_number = multilayer_perceptron_pointer->get_output_layer_parameters_number();

   Vector<double> hidden_layers_error_gradient(hidden_layers_parameters_number, 0.0);
   Vector<double> output_layer_error_gradient(output_layer_parameters_number, 0.0);

   // Main loop

   for(int i = 0; i < training_instances_number; i++)
   {
      training_input_instance = input_target_data_set_pointer->get_training_input_instance(i);

      forward_propagation_derivative = multilayer_perceptron_pointer->calculate_forward_propagation_derivative(training_input_instance);

      training_target_instance = input_target_data_set_pointer->get_training_target_instance(i);

	  output_errors = calculate_output_errors(forward_propagation_derivative, training_target_instance);

      hidden_errors = calculate_hidden_errors(forward_propagation_derivative, output_errors);

      hidden_layers_error_gradient += calculate_hidden_layers_error_gradient(training_input_instance, forward_propagation_derivative, hidden_errors);
  
      output_layer_error_gradient += calculate_output_layer_error_gradient(forward_propagation_derivative, output_errors);
   }

   return(hidden_layers_error_gradient.assemble(output_layer_error_gradient));   
}


// Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method

/// This method returns the output errors to be used in the back-propagation algorithm for calculating the objective gradient. 
/// @param forward_propagation_derivative Forward propagation derivative. 
/// @param target Target values. 

Vector<double> SumSquaredError::calculate_output_errors
(const Vector< Vector<double> >& forward_propagation_derivative, const Vector<double>& target)
{
   int forward_propagation_derivative_size = forward_propagation_derivative.get_size();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int hidden_layers_number = multilayer_perceptron_pointer->get_hidden_layers_number();

   if(forward_propagation_derivative_size != 2*hidden_layers_number+2)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of forward propagation derivative vector must be equal to 2*hidden_layers_number+2." 
				<< std::endl;

        exit(1);
   }
      
   int output_layer_output_size = forward_propagation_derivative[forward_propagation_derivative_size-2].get_size();
      
   if(output_layer_output_size != outputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of output layer output ("<< output_layer_output_size << ") must be equal to "
                << "number of outputs (" << outputs_number << ")." << std::endl;

      exit(1);
   }

   int output_layer_output_derivative_size 
   = forward_propagation_derivative[forward_propagation_derivative_size-1].get_size();

   if(output_layer_output_derivative_size != outputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of output layer output derivative (" << output_layer_output_derivative_size << ")must be equal to "               << "number of outputs (" << outputs_number << ")." << std::endl;

      exit(1);
   }

   int target_size = target.get_size();

   if(target_size != outputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of target must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   Vector<double> output_layer_output_derivative = forward_propagation_derivative[forward_propagation_derivative_size-1];
   Vector<double> output_layer_output = forward_propagation_derivative[forward_propagation_derivative_size-2];

   Vector<double> output_errors(outputs_number);

   Vector<double> error(outputs_number);

   MultilayerPerceptron::ScalingMethod outputs_unscaling_method
   = multilayer_perceptron_pointer->get_outputs_unscaling_method();

   switch(outputs_unscaling_method)
   {
      case MultilayerPerceptron::None:
      {   
         error = output_layer_output-target;

         output_errors = output_layer_output_derivative*error*2.0;
      } 
      break;

      case MultilayerPerceptron::MeanStandardDeviation:
      {         
         Vector<double>& output_variables_standard_deviation 
         = multilayer_perceptron_pointer->get_output_variables_standard_deviation();

         // Control sentence (if debug)

         #ifdef _DEBUG 
 
		 int output_variables_standard_deviation_size = output_variables_standard_deviation.get_size();

         if(output_variables_standard_deviation_size != outputs_number)
         {
           std::cerr << "Flood Error: SumSquaredError class." << std::endl
                     << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                     << "Size of output variables standard deviation must be equal to number of outputs." << std::endl;

           exit(1);
         }

         #endif

         output_errors = output_layer_output_derivative*error*output_variables_standard_deviation*2.0;
      }
      break;

      case MultilayerPerceptron::MinimumMaximum:
      {
         Vector<double>& output_variables_minimum = multilayer_perceptron_pointer->get_output_variables_minimum();
         Vector<double>& output_variables_maximum = multilayer_perceptron_pointer->get_output_variables_maximum();

         // Control sentence (if debug)

         #ifdef _DEBUG 
 
		 int output_variables_minimum_size = output_variables_minimum.get_size();
		 int output_variables_maximum_size = output_variables_maximum.get_size();

         if(output_variables_minimum_size != outputs_number)
         {
           std::cerr << "Flood Error: SumSquaredError class." << std::endl
                     << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                     << "Size of output variables minimum must be equal to number of outputs." << std::endl;

           exit(1);
         }
         else if(output_variables_maximum_size != outputs_number)
         {
           std::cerr << "Flood Error: SumSquaredError class." << std::endl
                     << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                     << "Size of output variables maximum must be equal to number of outputs." << std::endl;

           exit(1);
         }

         #endif

         output_errors = output_layer_output_derivative*error*(output_variables_maximum-output_variables_minimum);
      }		 
      break;
      
      default:
      {
         std::cerr << "Flood Error: SumSquaredError class." << std::endl
                   << "Vector<double> calculate_output_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                   << "Unknown outputs unscaling method." << std::endl;

         exit(1);
      }		 
      break;
      
   }

   return(output_errors);
}


// Vector< Vector<double> > calculate_hidden_errors(const Vector< Vector<double> >&, const Vector<double>&) method

/// This method returns the hidden errors to be used in the back-propagation algorithm for calculating the objective gradient. 
/// @param forward_propagation_derivative Forward propagation derivative. 
/// @param output_errors Output errors. 

Vector< Vector<double> > SumSquaredError::calculate_hidden_errors
(const Vector< Vector<double> >& forward_propagation_derivative, const Vector<double>& output_errors)
{
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   int hidden_layers_number = multilayer_perceptron_pointer->get_hidden_layers_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int forward_propagation_derivative_size = forward_propagation_derivative.get_size();

   if(forward_propagation_derivative_size != 2*hidden_layers_number+2)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_hidden_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of forward propagation derivative vector must be equal to 2*hidden_layers_number+2." 
				<< std::endl;

        exit(1);
   }
      
   int output_layer_output_size = forward_propagation_derivative[forward_propagation_derivative_size-2].get_size();
      
   if(output_layer_output_size != outputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_hidden_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of output layer output ("<< output_layer_output_size << ") must be equal to "
                << "number of outputs (" << outputs_number << ")." << std::endl;

      exit(1);
   }

   int output_layer_output_derivative_size 
   = forward_propagation_derivative[forward_propagation_derivative_size-1].get_size();

   if(output_layer_output_derivative_size != outputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_hidden_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of output layer output derivative (" << output_layer_output_derivative_size << ")must be equal to " 
				<< "number of outputs (" << outputs_number << ")." << std::endl;

      exit(1);
   }

   int output_errors_size = output_errors.get_size();

   if(output_errors_size != outputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_hidden_errors(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of target must be equal to number of outputs." << std::endl;

      exit(1);
   }

   #endif

   // Set hidden errors vector of vectors

   Vector<int> hidden_layers_size = multilayer_perceptron_pointer->get_hidden_layers_size();

   Vector< Vector<double> > hidden_errors(hidden_layers_number);

   for(int h = 0; h < hidden_layers_number; h++)
   {
      hidden_errors[h].set_size(hidden_layers_size[h]);
   }

   // Multilayer perceptron

   Vector<Perceptron>& output_layer = multilayer_perceptron_pointer->get_output_layer();
   Vector< Vector<Perceptron> >& hidden_layers = multilayer_perceptron_pointer->get_hidden_layers();

   Vector< Vector<double> > hidden_layers_output_derivative(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
      hidden_layers_output_derivative[i] = forward_propagation_derivative[1+2*i];
   }

   Vector<double> synaptic_weights;

   double sum;
    
   // Last hidden layer

   for(int j = 0; j < hidden_layers_size[hidden_layers_number-1]; j++)
   {
      sum = 0.0;

      for(int k = 0; k < outputs_number; k++)
      {
         synaptic_weights = output_layer[k].get_synaptic_weights();

         sum += (synaptic_weights[j])*output_errors[k];
      }

      hidden_errors[hidden_layers_number-1][j] = hidden_layers_output_derivative[hidden_layers_number-1][j]*sum;
   }

   // Rest of hidden layers

   for(int h = hidden_layers_number-2; h >= 0; h--) 
   {   
      for(int j = 0; j < hidden_layers_size[h]; j++)
      {
         sum = 0.0;

         for(int k = 0; k < hidden_layers_size[h+1]; k++)
         {
            synaptic_weights = hidden_layers[h+1][k].get_synaptic_weights();

            sum += (synaptic_weights[j])*hidden_errors[h+1][k];
         }		 

         hidden_errors[h][j] = hidden_layers_output_derivative[h][j]*sum;
      }
   }

   return(hidden_errors);
}


// Vector<double> calculate_hidden_layers_error_gradient
// (const Vector<double>&, const Vector< Vector<double> >&, const Vector< Vector<double> >&) ) method

/// This method returns the  hidden layers error gradient to be used in the back-propagation algorithm for calculating the objective gradient. 
/// @param input Input values. 
/// @param forward_propagation_derivative Forward propagation derivative. 
/// @param hidden_errors Hidden errors. 

Vector<double> SumSquaredError::calculate_hidden_layers_error_gradient
(const Vector<double>& input, 
 const Vector< Vector<double> >& forward_propagation_derivative, 
 const Vector< Vector<double> >& hidden_errors)
{
   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int hidden_layers_number = multilayer_perceptron_pointer->get_hidden_layers_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int input_size = input.get_size();

   if(input_size != inputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_hidden_layers_error_gradient(const Vector< Vector<double> >&, const Vector<double>&, const Vector<double>&) method." << std::endl
                << "Size of input (" << input_size << ") must be equal to inputs number (" << inputs_number << ")." 
				<< std::endl;

        exit(1);
   }


   int forward_propagation_derivative_size = forward_propagation_derivative.get_size();

   if(forward_propagation_derivative_size != 2*hidden_layers_number+2)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_hidden_layers_error_gradient(const Vector< Vector<double> >&, const Vector<double>&, const Vector<double>&) method." << std::endl
                << "Size of forward propagation derivative (" << forward_propagation_derivative_size << ") must be equal to 2*hidden_layers_number+2 (" << 2*hidden_layers_number+2 << ")." 
				<< std::endl;

        exit(1);
   }
      
   int hidden_errors_size = hidden_errors.get_size();
      
   if(hidden_errors_size != hidden_layers_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_hidden_layers_error_gradient(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of output errors ("<< hidden_errors_size << ") must be equal to number of hidden layers (" << hidden_layers_number << ")." << std::endl;

      exit(1);
   }

   #endif

   // Multilayer perceptron stuff 

   Vector<int> hidden_layers_size = multilayer_perceptron_pointer->get_hidden_layers_size();

   int hidden_layers_parameters_number = multilayer_perceptron_pointer->get_hidden_layers_parameters_number();

   Vector< Vector<Perceptron> >& hidden_layers = multilayer_perceptron_pointer->get_hidden_layers();

   Vector<double> synaptic_weights;

   Vector< Vector<double> > hidden_layers_output(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
      hidden_layers_output[i] = forward_propagation_derivative[2*i];
   }

   int index = 0;

   Vector<double> hidden_layers_error_gradient(hidden_layers_parameters_number, 0.0);

   // First hidden layer

   for(int j = 0; j < hidden_layers_size[0]; j++)
   {
      // Bias

      hidden_layers_error_gradient[index] += hidden_errors[0][j];
      index++;

      // Synaptic weights

      synaptic_weights = hidden_layers[0][j].get_synaptic_weights();

      for(int k = 0; k < inputs_number; k++)
      {
         hidden_layers_error_gradient[index] += hidden_errors[0][j]*input[k];
         index++;   
      }
   }

   // Rest of hidden layers	
    
   for(int h = 1; h < hidden_layers_number; h++)
   {      
      for(int j = 0; j < hidden_layers_size[h]; j++)
      {
         // Bias

         hidden_layers_error_gradient[index] += hidden_errors[h][j];
         index++;

         // Synaptic weights

         synaptic_weights = hidden_layers[h][j].get_synaptic_weights();

         for(int k = 0; k < hidden_layers_size[h-1]; k++)
         {
            hidden_layers_error_gradient[index] += hidden_errors[h][j]*hidden_layers_output[h-1][k];
            index++;   
         }
      }
   }

   return(hidden_layers_error_gradient);
}


// Vector<double> calculate_output_layer_error_gradient(const Vector< Vector<double> >&, const Vector<double>&) method

/// This method returns the output layers error gradient to be used in the back-propagation algorithm for calculating the objective gradient. 
/// @param forward_propagation_derivative Forward propagation derivative. 
/// @param output_errors Output errors. 

Vector<double> SumSquaredError::calculate_output_layer_error_gradient
(const Vector< Vector<double> >& forward_propagation_derivative, const Vector<double>& output_errors)
{
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();
   int hidden_layers_number = multilayer_perceptron_pointer->get_hidden_layers_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int forward_propagation_derivative_size = forward_propagation_derivative.get_size();

   if(forward_propagation_derivative_size != 2*hidden_layers_number+2)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_output_layer_error_gradient(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of forward propagation derivative (" << forward_propagation_derivative_size << ") must be equal to 2*hidden_layers_number+2 (" << 2*hidden_layers_number+2 << ")." << std::endl;

        exit(1);
   }
      
   int output_errors_size = output_errors.get_size();
      
   if(output_errors_size != outputs_number)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "Vector< Vector<double> > calculate_output_layer_error_gradient(const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Size of output errors ("<< output_errors_size << ") must be equal to number of outputs (" << outputs_number << ")." << std::endl;

      exit(1);
   }

   #endif

   // Multilayer perceptron stuff

   Vector<int> hidden_layers_size = multilayer_perceptron_pointer->get_hidden_layers_size();

   int output_layer_parameters_number = multilayer_perceptron_pointer->get_output_layer_parameters_number();

   Vector< Vector<double> > hidden_layers_output(hidden_layers_number);

   for(int i = 0; i < hidden_layers_number; i++)
   {
      hidden_layers_output[i] = forward_propagation_derivative[2*i];
   }

   // Calculate gradient elements of output neurons

   Vector<double> output_layer_error_gradient(output_layer_parameters_number, 0.0);

   int index = 0;

   for(int j = 0; j < outputs_number; j++)
   {
      // Bias

      output_layer_error_gradient[index] += output_errors[j];
      index++;

      // Synaptic weights

      for(int k = 0; k < hidden_layers_size[hidden_layers_number-1]; k++)
      {
         output_layer_error_gradient[index] = hidden_layers_output[hidden_layers_number-1][k]*output_errors[j];
         index++;
      }
   }

   return(output_layer_error_gradient);
}


// Matrix<double> calculate_Jacobian(void) method

/// This method returns the Jacobian matrix of the sum squared error function, whose elements are given by the 
/// derivatives of the squared errors data set with respect to the neural parameters.
/// The Jacobian matrix here is computed using a back-propagation algorithm.

Matrix<double> SumSquaredError::calculate_Jacobian(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_Jacobian(void) method." << std::endl
                << "Pointer to multilayer perceptron object cannot be NULL." << std::endl;

        exit(1);
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_Jacobian(void) method." << std::endl
                << "Pointer to input-target data set object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();
   int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();

   Matrix<double> Jacobian(training_instances_number, neural_parameters_number);

   // Multilayer perceptron 

   int hidden_layers_number = multilayer_perceptron_pointer->get_hidden_layers_number();

   Vector<int> hidden_layers_size = multilayer_perceptron_pointer->get_hidden_layers_size();

   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   int forward_propagation_derivative_size = 2*hidden_layers_number + 2;

   Vector< Vector<double> > forward_propagation_derivative(forward_propagation_derivative_size);

   // Input-target data set

   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();    Vector<double> training_input_instance(target_variables_number);
   Vector<double> training_target_instance(target_variables_number);

   // Output and hidden errors

   Vector<double> output_errors(outputs_number);
   Vector< Vector<double> > hidden_errors(hidden_layers_number);

   for(int h = 0; h < hidden_layers_number; h++)
   {
      hidden_errors[h].set_size(hidden_layers_size[h]);
   }

   // Hidden and output layers gradients

   int hidden_layers_parameters_number = multilayer_perceptron_pointer->get_hidden_layers_parameters_number();
   int output_layer_parameters_number = multilayer_perceptron_pointer->get_output_layer_parameters_number();

   Vector<double> hidden_layers_error_gradient(hidden_layers_parameters_number, 0.0);
   Vector<double> output_layer_error_gradient(output_layer_parameters_number, 0.0);

   Vector<double> gradient(outputs_number);

   // Main loop

   for(int i = 0; i < training_instances_number; i++)
   {
      training_input_instance = input_target_data_set_pointer->get_training_input_instance(i);

      forward_propagation_derivative = multilayer_perceptron_pointer->calculate_forward_propagation_derivative(training_input_instance);

      training_target_instance = input_target_data_set_pointer->get_training_target_instance(i);

      output_errors = calculate_output_errors(forward_propagation_derivative, training_target_instance);

      hidden_errors = calculate_hidden_errors(forward_propagation_derivative, output_errors);

      hidden_layers_error_gradient = calculate_hidden_layers_error_gradient(training_input_instance, forward_propagation_derivative, hidden_errors);

      output_layer_error_gradient = calculate_output_layer_error_gradient(forward_propagation_derivative, output_errors);

      gradient = hidden_layers_error_gradient.assemble(output_layer_error_gradient);

      Jacobian.set_row(i, gradient);
   }

   return(Jacobian);
}


// Matrix<double> calculate_Jacobian_numerical_differentiation(void) method

/// This method returns the Jacobian matrix of the sum squared error function by means of numerical differentiation,
/// acording to the numerical differentiation class member. 

Matrix<double> SumSquaredError::calculate_Jacobian_numerical_differentiation(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_Jacobian_numerical_differentiation(void) method." << std::endl
                << "Pointer to multilayer perceptron object cannot be NULL." << std::endl;

        exit(1);
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_Jacobian_numerical_differentiation(void) method." << std::endl
                << "Pointer to input-target data set object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   switch(numerical_differentiation_method)   
   {
      case ForwardDifferences:
      {
         return(calculate_Jacobian_forward_differences());
      }
      break;

      case CentralDifferences:
      {
         return(calculate_Jacobian_central_differences());
      }
      break;

      default:
      {
         std::cerr << "Flood Error: SumSquaredError class." << std::endl
                   << "std::string calculate_Jacobian_numerical_differentiation(void) method." << std::endl
                   << "Unknown numerical differentiation method." << std::endl;
 
         exit(1);
      }
      break;
   }
}


// Matrix<double> calculate_Jacobian_forward_differences(void) method

/// This method returns the Jacobian matrix of the sum squared error function with the forward differences method
/// for numerical differentiation. 

Matrix<double> SumSquaredError::calculate_Jacobian_forward_differences(void)
{
   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();
   int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();

   Matrix<double> Jacobian(training_instances_number, neural_parameters_number);

   // Multilayer perceptron stuff

   Vector<double> neural_parameters = multilayer_perceptron_pointer->get_neural_parameters();

   // Objective functional stuff

   Vector<double> squared_errors = calculate_squared_errors(); 

   Vector<double> squared_errors_forward(training_instances_number);

   double actual_epsilon;

   // Calculate Jacobian

   for(int j = 0; j < neural_parameters_number; j++)
   {
      actual_epsilon = calculate_actual_epsilon(neural_parameters[j]);

      // Perturbate neural parameters

      neural_parameters[j] += actual_epsilon;
      multilayer_perceptron_pointer->set_neural_parameters(neural_parameters);

      // Calculate squared errors forward

      squared_errors_forward = calculate_squared_errors();

      // Restart biases and synaptic weights

      neural_parameters[j] -= actual_epsilon;
      multilayer_perceptron_pointer->set_neural_parameters(neural_parameters);

      // Calculate Jacobian elements
                        
      for(int i = 0; i < training_instances_number; i++)
      {
         Jacobian[i][j] = (squared_errors_forward[i] - squared_errors[i])/actual_epsilon;
      }
   }

   return(Jacobian);
}


// Matrix<double> calculate_Jacobian_central_differences(void) method

/// This method returns the Jacobian matrix of the sum squared error function with the central differences method
/// for numerical differentiation. 

Matrix<double> SumSquaredError::calculate_Jacobian_central_differences(void)
{
   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();
   int neural_parameters_number = multilayer_perceptron_pointer->get_neural_parameters_number();

   Matrix<double> Jacobian(training_instances_number, neural_parameters_number);

   // Multilayer perceptron stuff

   Vector<double> neural_parameters = multilayer_perceptron_pointer->get_neural_parameters();

   // Objective functional stuff
   
   Vector<double> squared_errors_forward(training_instances_number);
   Vector<double> squared_errors_backward(training_instances_number);

   double actual_epsilon;

   // Calculate Jacobian

   for(int j = 0; j < neural_parameters_number; j++)
   {
      actual_epsilon = calculate_actual_epsilon(neural_parameters[j]);
      
      // Perturbate neural parameters

      neural_parameters[j] += actual_epsilon;
      multilayer_perceptron_pointer->set_neural_parameters(neural_parameters);

      // Calculate squared errors     
 
      squared_errors_forward = calculate_squared_errors();
 
      // Restart neural parameters

      neural_parameters[j] -= actual_epsilon;
      multilayer_perceptron_pointer->set_neural_parameters(neural_parameters);

      // Perturbate neural parameters

      neural_parameters[j] -= actual_epsilon;
      multilayer_perceptron_pointer->set_neural_parameters(neural_parameters);

      // Calculate squared errors     
 
      squared_errors_backward = calculate_squared_errors();
 
      // Restart neural parameters

      neural_parameters[j] += actual_epsilon;
      multilayer_perceptron_pointer->set_neural_parameters(neural_parameters);

      // Calculate Jacobian elements

      for(int i = 0; i < training_instances_number; i++)
      {
         Jacobian[i][j] = (squared_errors_forward[i] - squared_errors_backward[i])/(2.0*actual_epsilon);
      }
   }

   return(Jacobian);
}


// Vector<double> calculate_squared_errors(void) method

/// This method returns the squared errors of the training instances. 

Vector<double> SumSquaredError::calculate_squared_errors(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(multilayer_perceptron_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_Jacobian_numerical_differentiation(void) method." << std::endl
                << "Pointer to multilayer perceptron object cannot be NULL." << std::endl;

        exit(1);
   }
   else if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: SumSquaredError class." << std::endl
                << "double calculate_Jacobian_numerical_differentiation(void) method." << std::endl
                << "Pointer to input-target data set object cannot be NULL." << std::endl;

      exit(1);
   }

   #endif

   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();

   Vector<double> squared_errors(training_instances_number);

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);
   Vector<double> target(outputs_number);
   Vector<double> instance_error(outputs_number);

   for(int i = 0; i < training_instances_number; i++)
   {
      // Input vector

	  input = input_target_data_set_pointer->get_training_input_instance(i);

      // Output vector

      output = multilayer_perceptron_pointer->calculate_output(input);

      // Target vector

      target = input_target_data_set_pointer->get_training_target_instance(i);

      // Error

	  squared_errors[i] = (output - target).dot(output - target);
   }

   return(squared_errors);
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

