/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   V E C T O R   C O N T A I N E R                                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <cmath>

namespace Flood
{

/// Forward declaration of Matrix template

template <class Type> class Matrix;

/// This template class defines a vector for general purpose use.
/// This vector also implements some mathematical methods which can be useful. 

template <class Type>
class Vector
{

public:

   // CONSTRUCTORS

   // Default constructor

   explicit Vector(void);

   // Size constructor

   explicit Vector(int);

   // Size initialization constructor

   explicit Vector(int, const Type&);

   // File constructor

   explicit Vector(const char*);

   // Copy constructor 

   Vector(const Vector&);

   // DESTRUCTOR

   virtual ~Vector(void);

   // ASSINGMENT OPERATOR

   Vector& operator = (const Vector&);

   // REFERENCE OPERATORS

   inline Type& operator [] (int);
   inline const Type& operator [] (int) const;

   // ARITHMETIC OPERATORS

   Vector<Type> operator + (const Type&) const;
   Vector<Type> operator + (const Vector<Type>&) const;

   Vector<Type> operator - (const Type&) const;
   Vector<Type> operator - (const Vector<Type>&) const;

   Vector<Type> operator * (const Type&) const;
   Vector<Type> operator * (const Vector<Type>&) const;

   Vector<Type> operator / (const Type&) const;
   Vector<Type> operator / (const Vector<Type>&) const;

   // AITHMETIC AND ASSIGNMENT OPERATORS

   void operator += (const Type&) const;
   void operator += (const Vector<Type>&) const;

   void operator -= (const Type&) const;
   void operator -= (const Vector<Type>&) const;

   void operator *= (const Type&) const;
   void operator *= (const Vector<Type>&) const;

   void operator /= (const Type&) const;
   void operator /= (const Vector<Type>&) const;

   // EQUALITY AND RELATIONAL OPERATORS 

   bool operator == (const Vector<Type>&) const;
   bool operator == (const Type&) const;

   bool operator != (const Vector<Type>&) const;
   bool operator != (const Type&) const;

   bool operator > (const Vector<Type>&) const;
   bool operator > (const Type&) const;

   bool operator < (const Vector<Type>&) const;
   bool operator < (const Type&) const;
   
   bool operator >= (const Vector<Type>&) const;
   bool operator >= (const Type&) const;
   
   bool operator <= (const Vector<Type>&) const;
   bool operator <= (const Type&) const;


   // METHODS

   Type* begin() const;
   Type* end() const;

   // Get methods

   inline int get_size(void) const;

   bool get_display(void) const;

   // Set methods

   void set(void);
   void set(int);
   void set(int, const Type&);
   void set(const Vector&);
   void set(const char*);

   void set_size(int);
   void set_size(int, const Type&);
   void set_display(bool);

   // Resize methods

   void resize(int);

   bool is_zero(void) const;

   void insert(int, const Vector<Type>&) const;
   Vector<Type> extract(int, int) const;

   Vector<Type> assemble(const Vector<Type>&) const;

   // Initialization methods

   void initialize(const Type&) const;

   void initialize_sequential(void) const;

   void initialize_uniform(void) const;
   void initialize_uniform(double, double) const;
   void initialize_uniform(const Vector<double>&, const Vector<double>&) const;

   void initialize_normal(void) const;
   void initialize_normal(double, double) const;
   void initialize_normal(const Vector<double>&, const Vector<double>&) const;

   // Mathematical methods

   Type dot(const Vector<Type>&) const;
   Vector<Type> dot(const Matrix<Type>&) const;
   Matrix<Type> outer(const Vector<Type>&) const;

   Type calculate_sum(void) const;
   Type calculate_product(void) const;

   double calculate_mean(void) const;
   double calculate_standard_deviation(void) const;

   Vector<double> calculate_mean_standard_deviation(void) const;

   Type calculate_minimum(void) const;
   Type calculate_maximum(void) const;

   Vector<Type> calculate_minimum_maximum(void) const;

   int calculate_minimal_index(void) const;
   int calculate_maximal_index(void) const;

   Vector<int> calculate_minimal_maximal_index(void) const;

   double calculate_norm(void) const;

   Vector<Type> calculate_lower_bounded(const Type&) const;
   Vector<Type> calculate_lower_bounded(const Vector<Type>&) const;

   Vector<Type> calculate_upper_bounded(const Type&) const;
   Vector<Type> calculate_upper_bounded(const Vector<Type>&) const;

   Vector<Type> calculate_lower_upper_bounded(const Type&, const Type&) const;
   Vector<Type> calculate_lower_upper_bounded(const Vector<Type>&, const Vector<Type>&) const;

   void apply_lower_bound(const Type&);
   void apply_lower_bound(const Vector<Type>&);

   void apply_upper_bound(const Type&);
   void apply_upper_bound(const Vector<Type>&);

   void apply_lower_upper_bounds(const Type&, const Type&);
   void apply_lower_upper_bounds(const Vector<Type>&, const Vector<Type>&);

   // Utility methods

   std::string to_XML(bool);

   void save(const char*);
   void save_data(const char*);

   void load(const char*);
   void load_data(const char*);

private:

   /// Number of elements in vector.

   int size;

   bool display;

   /// Pointer to a Type.

   Type* data;

   // Utility methods

   double calculate_random_uniform(double, double) const;
   double calculate_random_normal(double, double) const;
};


// CONSTRUCTORS

/// Default constructor. It creates a vector of size zero.

template <class Type>
Vector<Type>::Vector(void)
{
   size = 0;
   display = true;
   data = NULL;
}


/// General constructor. It creates a vector of size n, containing n copies of the default value for Type.
/// @param new_size Size of vector.

template <class Type>
Vector<Type>::Vector(int new_size)
{
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(new_size < 0)
   {
      std::cout << "Flood Error: Vector Template." << std::endl 
                << "Vector(int) constructor." << std::endl
                << "Size must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif
   
   size = new_size;
   display = true;
   data = new Type[new_size];
}


/// Constant reference initialization constructor.
/// It creates a vector of size n, containing n copies of the type value of Type. 
/// @param new_size Size of Vector.
/// @param value Initialization value of Type.

template <class Type>
Vector<Type> ::Vector(int new_size, const Type& value) 
{
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(new_size < 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector(int, const Type&) constructor." << std::endl
                << "Size must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif
   
   size = new_size;
   display = true;
   data = new Type[new_size];
   
   for(int i = 0; i < size; i++)
   {
      data[i] = value;
   }
}


/// File constructor. It creates a vector object by loading its members from a XML-type file.
/// @param filename Name of vector XML-type file.

template <class Type>
Vector<Type>::Vector(const char* filename) 
{
   size = 0;
   display = true;
   data = NULL;

   load(filename);
}


/// Copy constructor. It creates a copy of an existing Vector. 
/// @param other_vector Vector to be copied.

template <class Type>
Vector<Type>::Vector(const Vector<Type>& other_vector) 
{
   size = other_vector.size;
   display = true;
   data = new Type[size];

   // Control sentence (if debug)      
       
   for(int i = 0; i < size; i++)
   {
      data[i] = other_vector[i];
   }
}


// DESTRUCTOR

/// Destructor. 

template <class Type> 
Vector<Type>::~Vector(void)
{
   if(data != NULL)
   {
      delete[](data);
   }
}


// ASSIGNMENT OPERATORS

/// Assignment operator. It assigns to the current vector the members of an existing vector.
/// @param other_vector vector to be assigned.

template <class Type>
Vector<Type>& Vector<Type>::operator = (const Vector<Type>& other_vector)
{
   if(this != &other_vector) // other vector
   {
      if(size != other_vector.get_size()) // other size
      {
         if(data != NULL)
         {
            // Control sentence (if debug)      
       
            //#ifdef _DEBUG 
            //std::cout << "Flood Warning: Vector Template." << std::endl 
            //          << "Vector& operator = (const Vector<Type>&)." << std::endl
            //          << "Assignment operator to non-empty vector." << std::endl;     
            //#endif

            delete [] (data);
         }

         size = other_vector.size;

         data = new Type[size];
      }

      for(int i = 0; i < size; i++)
      {
         data[i] = other_vector[i];
      }

	  display = other_vector.get_display();
   }

   return(*this);
}


// REFERENCE OPERATORS

/// Reference operator. It returns an element of the vector. 
/// @param i Index of element. 

template <class Type>
inline Type& Vector<Type>::operator [] (int i) 
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(size == 0)
   {
      std::cerr << "Flood Error: Vector Template. " << std::endl
                << "Reference operator []." << std::endl
                << "Size of vector is zero." << std::endl;

      exit(1);
   }
   else if(i < 0)
   {
      std::cerr << "Flood Error: Vector Template. " << std::endl
                << "Reference operator []." << std::endl
                << "Index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= size)
   {
      std::cerr << "Flood Error: Vector Template. " << std::endl
                << "Reference operator []." << std::endl
                << "Index is " << i << " and it must be less than " << size << "." << std::endl;

      exit(1);
   }

   #endif

   // Return vector element

   return(data[i]);
}


/// Reference operator. It returns an element of the vector. 
/// @param i Index of element. 

template <class Type>
inline const Type& Vector<Type>::operator [] (int i) const 
{
   // Control sentence (if debug)
   
   #ifdef _DEBUG 

   if(size == 0)
   {
      std::cerr << "Flood Error: Vector Template. " << std::endl
                << "Reference operator []." << std::endl
                << "Size of vector is zero." << std::endl;

      exit(1);
   }
   else if(i < 0)
   {
      std::cerr << "Flood Error: Vector Template. " << std::endl
                << "Reference operator []." << std::endl
                << "Index must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(i >= size)
   {
      std::cerr << "Flood Error: Vector Template. " << std::endl
                << "Reference operator []." << std::endl
                << "Index is " << i << " and it must be less than " << size << "." << std::endl;

      exit(1);
   }

   #endif

   return(data[i]);
}


// bool operator == (const Vector<Type>&) const

/// Equivalent relational operator between this vector and other vector.
/// It produces true if all the elements of the two vectors are equal, and false otherwise.
/// @param other_vector vector to be compared with.

template <class Type>
bool Vector<Type>::operator == (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "bool operator == (const Vector<Type>&) const." << std::endl
                << "Size of vectors are " << size << " and " << other_size << " and they must be the same."
                << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < size; i++)
   {
      if(data[i] != other_vector[i])
      {
        return(false);
      }     
   }
   
   return(true);
}


// bool operator == (const Type&) const

/// Equivalent relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <class Type>
bool Vector<Type>::operator == (const Type& value) const
{       
   for(int i = 0; i < size; i++)
   {
      if(data[i] != value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator != (const Vector<Type>&)

/// Not equivalent relational operator between this vector and other vector.
/// It produces true if the two vectors have any not equal element, and false otherwise.
/// @param other_vector vector to be compared with.

template <class Type>
bool Vector<Type>::operator != (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "bool operator != (const Vector<Type>&) const." << std::endl
                << "Size of vectors are " << size << " and " << other_size << " and they must be the same." 
                << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < size; i++)
   {
      if(data[i] != other_vector[i])
      {
         return(true);
      }     
   }

   return(false);
}


// bool operator != (const Type&) const

/// Not equivalent relational operator between this vector and a Type value.
/// It produces true if some element of this vector is not equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <class Type>
bool Vector<Type>::operator != (const Type& value) const
{            
   for(int i = 0; i < size; i++)
   {
      if(data[i] != value)
      {
         return(true);
      }     
   }

   return(false);
}


// bool operator > (const Vector<Type>&) const

/// Greater than relational operator between this vector and other vector.
/// It produces true if all the elements of this vector are greater than the corresponding elements of the other vector,
/// and false otherwise.
/// @param other_vector vector to be compared with.

template <class Type>
bool Vector<Type>::operator > (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "bool operator > (const Vector<Type>&) const." << std::endl
                << "Size of vectors are " << size << " and " << other_size << " and they must be the same." 
                << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < size; i++)
   {
      if(data[i] <= other_vector[i])
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator > (Type) const

/// Greater than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are greater than the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <class Type>
bool Vector<Type>::operator > (const Type& value) const
{       
   for(int i = 0; i < size; i++)
   {
      if(data[i] <= value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator < (const Vector<Type>&) const

/// Less than relational operator between this vector and other vector.
/// It produces true if all the elements of this vector are less than the corresponding elements of the other vector,
/// and false otherwise.
/// @param other_vector vector to be compared with.

template <class Type>
bool Vector<Type>::operator < (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "bool operator < (const Vector<Type>&) const." << std::endl
                << "Size of vectors are " << size << " and " << other_size << " and they must be the same." 
                << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < size; i++)
   {
      if(data[i] >= other_vector[i])
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator < (const Type&) const

/// Less than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are less than the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <class Type>
bool Vector<Type>::operator < (const Type& value) const
{       
   for(int i = 0; i < size; i++)
   {
      if(data[i] >= value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator >= (const Vector<Type>&) const

/// Greater than or equal to relational operator between this vector and other vector.
/// It produces true if all the elements of this vector are greater than or equal to the corresponding elements of the
/// other vector, and false otherwise.
/// @param other_vector vector to be compared with.

template <class Type>
bool Vector<Type>::operator >= (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "bool operator >= (const Vector<Type>&) const." << std::endl
                << "Size of vectors are " << size << " and " << other_size << " and they must be the same." << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < size; i++)
   {
      if(data[i] < other_vector[i])
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator >= (const Type&) const

/// Greater than or equal to than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are greater than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <class Type>
bool Vector<Type>::operator >= (const Type& value) const
{       
   for(int i = 0; i < size; i++)
   {
      if(data[i] < value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator <= (const Vector<Type>&) const

/// Less than or equal to relational operator between this vector and other vector.
/// It produces true if all the elements of this vector are less than or equal to the corresponding elements of the
/// other vector, and false otherwise.
/// @param other_vector vector to be compared with.

template <class Type>
bool Vector<Type>::operator <= (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "bool operator <= (const Vector<Type>&) const." << std::endl
                << "Size of vectors are " << size << " and " << other_size << " and they must be the same." 
                << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < size; i++)
   {
      if(data[i] > other_vector[i])
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator <= (const Type&) const

/// Less than or equal to than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are less than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <class Type>
bool Vector<Type>::operator <= (const Type& value) const
{
   for(int i = 0; i < size; i++)
   {
      if(data[i] > value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// METHODS

// int get_size(void) const method

/// This method returns the number of elements in the vector. 

template <class Type>
inline int Vector<Type>::get_size(void) const
{
   return(size);
}


// bool get_display(void) const method

/// This method returns true if messages from this class are to be displayed on the screen, 
/// or false if messages from this class are not to be displayed on the screen.

template <class Type>
inline bool Vector<Type>::get_display(void) const
{
   return(display);
}


// bool is_zero(void) const method

/// This method returns true if the vector is empty, i.e., has size zero, and false otherwise. 

template <class Type>
bool Vector<Type>::is_zero(void) const
{
   if(size == 0)
   {
      return(true);
   }
   else
   {
      return(false);
   }
}


// void set(void) method

/// This method sets the size of a vector to zero. 
/// It also sets the display value to true. 

template <class Type>
void Vector<Type>::set(void) 
{
   if(data != NULL)
   {
      delete[](data);
   }

   size = 0;
   display = true;
   data = NULL;   
}


// void set(int) method

/// This method sets a new size to the vector. It does not initialize the data.
/// It also sets the display value to true. 
/// @param new_size Size for the vector.

template <class Type>
void Vector<Type>::set(int new_size)
{
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(new_size < 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void set(int) method." << std::endl
                << "Size must be equal or greater than zero." << std::endl;

	  exit(1);
   }

   #endif

   if(new_size != size)
   {
      if(data != NULL)
      {
         delete[](data);
      }

      size = new_size;
      display = true;
      data = new Type[size];
   }   
}


// void set(int, const Type&) method

/// This method sets a new size to the vector and initializes all its elements with a given value. 
/// It also sets the display value to true. 
/// @param new_size Size for the vector.
/// @param new_value Value for all the elements.

template <class Type>
void Vector<Type>::set(int new_size, const Type& new_value)
{
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(new_size < 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void set(int) method." << std::endl
                << "Size must be equal or greater than zero." << std::endl;

	  exit(1);
   }

   #endif

   set(new_size);
   display = true;
   initialize(new_value);
}


// void set(const Vector&) method

/// This method sets the members of this object with the values of another vector. 
/// @param other_vector Object to set this vector. 

template <class Type>
void Vector<Type>::set(const Vector& other_vector)
{
   if(this != &other_vector) // other data
   {
      if(size != other_vector.size) // other size
      {
         if(data != NULL)
         {
            // Control sentence (if debug)      
       
            //#ifdef _DEBUG 
            //std::cout << "Flood Warning: Vector Template." << std::endl 
            //          << "Vector& operator = (const Vector<Type>&)." << std::endl
            //          << "Assignment operator to non-empty vector." << std::endl;     
            //#endif

            delete [] (data);
         }

         size = other_vector.get_size();
         display = other_vector.get_display();
         data = new Type[size];
      }

      for(int i = 0; i < size; i++)
      {
         data[i] = other_vector[i];
      }
   }
}


// void set(const char*) method

/// This method sets all the members of a vector object by loading them from an XML-type file.
/// The format is specified in the user's guide. 
/// @param filename Name of vector file. 

template <class Type>
void Vector<Type>::set(const char* filename) 
{
   load(filename);
}


// void set_display(bool) method

/// This method sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

template <class Type>
void Vector<Type>::set_display(bool new_display) 
{
   display = new_display;
}


// void set_size(int) method

/// This method sets a new size in the vector.
/// It does not initialize the new vector.
/// @param new_size New number of elements.

template <class Type>
void Vector<Type>::set_size(int new_size)
{
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   if(new_size < 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void set_size(int) method." << std::endl
                << "Size must be equal or greater than zero." << std::endl;

      exit(1);          
   }
      
   #endif

   if(size != new_size)
   {
      if(data != 0)
      {
         delete[](data);
      }

      data = new Type[new_size];
      size = new_size;
   }
}


// void set_size(int, const Type&) method

/// This method sets a new size in the vector.
/// It also initializes the elements with a given value.
/// @param new_size Number of elements.
/// @param new_value Initialization value.

template <class Type>
void Vector<Type>::set_size(int new_size, const Type& new_value)
{
   set_size(new_size);
   initialize(new_value);
}


// void resize(int) method

/// This method sets a new size in the vector.
/// It also initializes the elements of the new data with their corresponding previous values.
/// @param new_size New number of elements.

template <class Type>
void Vector<Type>::resize(int new_size)
{ 
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   if(new_size < 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void resize(int) method." << std::endl
                << "Size must be equal or greater than zero." << std::endl;

      exit(1);          
   }
      
   #endif

   // Resize vector

   if(new_size > size) // increase size
   {
      Vector<Type> copy(*this);

      set(new_size);

	  insert(0, copy);
   }
   else if(new_size < size) // decrease size
   {      
      Vector<Type> copy = extract(0, new_size);

	  set(copy);
   }
}


// void initialize(const Type&) const method

/// This method initializes all the elements of the vector with a given value.
/// @param value Type value.

template <class Type>
void Vector<Type>::initialize(const Type& value) const
{
   for(int i = 0; i < size; i++)
   {
      data[i] = value;
   }
}


// void initialize_sequential(void) const method

/// This method initializes all the elements of the vector in a sequential order.

template <class Type>
void Vector<Type>::initialize_sequential(void) const
{
   for(int i = 0; i < size; i++)
   {
      data[i] = i;
   }
}


// void initialize_uniform(void) const method

/// This method assigns a random value comprised between -1 and 1 to each element in the vector. 

template <class Type>
void Vector<Type>::initialize_uniform(void) const
{
   for(int i = 0; i < size; i++)
   {
      data[i] = calculate_random_uniform(-1.0, 1.0);
   }
}


// void initialize_uniform(double, double) const method

/// This method assigns a random value comprised between a minimum value and a maximum value to each element in
/// the vector. 
/// @param minimum Minimum initialization value.  
/// @param maximum Maximum initialization value.

template <class Type>
void Vector<Type>::initialize_uniform(double minimum, double maximum) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(minimum > maximum)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void initialize_uniform(double, double) const method." << std::endl
                << "Minimum value must be less or equal than maximum value." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < size; i++)
   {
      data[i] = calculate_random_uniform(minimum, maximum);
   }
}


// void initialize_uniform(const Vector<double>&, const Vector<double>&) const method

/// This method assigns a random value comprised between given minimum and a maximum values to every element in the 
/// vector. 
/// @param minimum Minimum initialization values.  
/// @param maximum Maximum initialization values.

template <class Type>
void Vector<Type>::initialize_uniform(const Vector<double>& minimum, const Vector<double>& maximum) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int minimum_size = minimum.get_size();
   int maximum_size = maximum.get_size();

   if(minimum_size != size || maximum_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void initialize_uniform(const Vector<double>&, const Vector<double>&) const method."
                << std::endl
                << "Minimum and maximum sizes must be equal to vector size." << std::endl;

      exit(1);
   }

   if(minimum > maximum)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void initialize_uniform(const Vector<double>&, const Vector<double>&) const method."
                << std::endl
                << "Minimum values must be less or equal than their corresponding maximum values." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < size; i++)
   {
      data[i] = calculate_random_uniform(minimum[i], maximum[i]);
   }
}


// void initialize_normal(void) const method

/// This method assigns random values to each element in the vector. These are taken from a normal distribution with
/// mean 0 and standard deviation 1. 

template <class Type>
void Vector<Type>::initialize_normal(void) const 
{
   for(int i = 0; i < size; i++)
   {
      data[i] = calculate_random_normal(0.0, 1.0);
   }
}


// void initialize_normal(double, double) const method

/// This method assigns random values to each element in the vector. 
/// These are taken from a normal distribution with single mean and standard deviation values for all the elements. 
/// @param mean Mean value of uniform distribution.  
/// @param standard_deviation Standard deviation value of uniform distribution.

template <class Type>
void Vector<Type>::initialize_normal(double mean, double standard_deviation) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(standard_deviation < 0.0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void initialize_normal(double, double) const method." << std::endl
                << "Standard deviation must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < size; i++)
   {
      data[i] = calculate_random_normal(mean, standard_deviation);
   }
}


// void initialize_normal(const Vector<double>, const Vector<double>) const method

/// This method assigns random values to each element in the vector. 
/// These are taken from normal distributions with given means and standard deviations for each element. 
/// @param mean Mean values of normal distributions.  
/// @param standard_deviation Standard deviation values of normal distributions.

template <class Type>
void Vector<Type>::initialize_normal(const Vector<double>& mean, const Vector<double>& standard_deviation) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
 
   int mean_size = mean.get_size();
   int standard_deviation_size = standard_deviation.get_size();

   if(mean_size != size || standard_deviation_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void initialize_normal(const Vector<double>&, const Vector<double>&) const method."
                << std::endl
                << "Mean and standard deviation sizes must be equal to vector size." << std::endl;

      exit(1);
   }

   if(standard_deviation < 0.0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void initialize_normal(const Vector<double>&, const Vector<double>&) const method."
                << std::endl
                << "Standard deviations must be equal or greater than zero." << std::endl;
      exit(1);
   }

   #endif

   for(int i = 0; i < size; i++)
   {
      data[i] = calculate_random_normal(mean[i], standard_deviation[i]);
   }
}


// Type calculate_minimum(void) const method

/// This method returns the smallest element in the vector.

template <class Type>
Type Vector<Type>::calculate_minimum(void) const
{
   Type minimum = data[0];

   for(int i = 1; i < size; i++)
   {
      if(data[i] < minimum)
      {
         minimum = data[i];
      }
   }
   
   return(minimum);
}


// Type calculate_maximum(void) const method

/// This method returns the largest element in the vector.

template <class Type>
Type Vector<Type>::calculate_maximum(void) const
{
   Type maximum = data[0];

   for(int i = 1; i < size; i++)
   {
      if(data[i] > maximum)
      {
         maximum = data[i];
      }
   }
   
   return(maximum);
}


// Vector<Type> calculate_minimum_maximum(void) const method

/// This method returns a vector containing the smallest and the largest elements in the vector.

template <class Type>
Vector<Type> Vector<Type>::calculate_minimum_maximum(void) const
{
   Type minimum = data[0];
   Type maximum = data[0];

   for(int i = 1; i < size; i++)
   {
      if(data[i] < minimum)
      {
         minimum = data[i];
      }

      if(data[i] > maximum)
      {
         maximum = data[i];
      }
   }

   Vector<Type> minimum_maximum(2);
   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// int calculate_minimal_index(void) const method

/// This method returns the index of the smallest element in the vector.

template <class Type>
int Vector<Type>::calculate_minimal_index(void) const
{
   Type minimum = data[0];
   int minimal_index = 0;

   for(int i = 1; i < size; i++)
   {
      if(data[i] < minimum)
      {
         minimum = data[i];
         minimal_index = i;
      }
   }
   
   return(minimal_index);
}


// int calculate_maximal_index(void) const method

/// This method returns the index of the largest element in the vector.

template <class Type>
int Vector<Type>::calculate_maximal_index(void) const
{
   Type maximum = data[0];
   int maximal_index = 0;

   for(int i = 1; i < size; i++)
   {
      if(data[i] > maximum)
      {
         maximum = data[i];
         maximal_index = i;
      }
   }
   
   return(maximal_index);
}


// Vector<int> calculate_minimal_maximal_index(void) const method

/// This method returns a vector with the indexes of the smallest and the largest elements in the vector.

template <class Type>
Vector<int> Vector<Type>::calculate_minimal_maximal_index(void) const
{
   Type minimum = data[0];
   Type maximum = data[0];

   int minimal_index = 0;
   int maximal_index = 0;

   for(int i = 1; i < size; i++)
   {
      if(data[i] < minimum)
      {
         minimum = data[i];
         minimal_index = i;
      }
      if(data[i] > maximum)
      {
         maximum = data[i];
         maximal_index = i;
      }
   }

   Vector<int> minimal_maximal_index(2);
   minimal_maximal_index[0] = minimal_index;
   minimal_maximal_index[1] = maximal_index;
   
   return(minimal_maximal_index);
}


// Type calculate_sum(void) const method

/// This method returns the sum of the elements in the vector.

template <class Type>
Type Vector<Type>::calculate_sum(void) const
{
   Type sum = 0;

   for(int i = 0; i < size; i++)
   {
      sum += data[i];
   }
   
   return(sum);
}


// Type calculate_product(void) const method

/// This method returns the product of the elements in the vector.

template <class Type>
Type Vector<Type>::calculate_product(void) const 
{
   Type product = 1;

   for(int i = 0; i < size; i++)
   {
      product *= data[i];
   }
   
   return(product);
}


// double calculate_mean(void) const method

/// This method returns the mean of the elements in the vector.

template <class Type>
double Vector<Type>::calculate_mean(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(size == 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "double calculate_mean(void)." << std::endl
                << "Size must be greater than zero." << std::endl;

      exit(1);      
   }

   #endif

   Type sum = calculate_sum();

   double mean = sum/(double)size;
   
   return(mean);
}


// double calculate_standard_deviation(void) method

/// This method returns the standard deviation of the elements in the vector.

template <class Type>
double Vector<Type>::calculate_standard_deviation(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(size == 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "double calculate_standard_deviation(void)." << std::endl
                << "Size must be greater than zero." << std::endl;

      exit(1);      
   }

   #endif

   double mean = calculate_mean();

   double sum = 0.0;
   
   for(int i = 0; i < size; i++)
   {
      sum += (data[i] - mean)*(data[i] - mean);
   }

   double standard_deviation = sqrt(sum/(double)size);
   
   return(standard_deviation);
}


// Vector<double> calculate_standard_deviation(void) const method

/// This method returns the mean and the standard deviation of the elements in the vector.

template <class Type>
Vector<double> Vector<Type>::calculate_mean_standard_deviation(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(size == 0)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "double calculate_mean_standard_deviation(void)." << std::endl
                << "Size must be greater than zero." << std::endl;

      exit(1);      
   }

   #endif

   double mean = calculate_mean();

   double sum = 0.0;
   
   for(int i = 0; i < size; i++)
   {
      sum += (data[i] - mean)*(data[i] - mean);
   }

   double standard_deviation = sqrt(sum/(double)size);

   Vector<double> mean_standard_deviation(2);
   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// double calculate_norm(void) const method

/// This element returns the vector norm.

template <class Type>
double Vector<Type>::calculate_norm(void) const
{
   // Control sentence (if debug)

   double norm = 0.0;

   for(int i = 0; i < size; i++)
   {
      norm += data[i]*data[i];
   }
   
   norm = sqrt(norm);
   
   return(norm);
}


// Vector<Type> calculate_lower_bounded(const Type&) const method

/// This method bounds the elements of the vector if they fall below a lower bound value.
/// @param lower_bound Lower bound values.

template <class Type>
Vector<Type> Vector<Type>::calculate_lower_bounded(const Type& lower_bound) const
{
   Vector<Type> bounded_vector(size);

   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound)
      {
         data[i] = lower_bound;
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_bounded(const Vector<Type>&) const method

/// This method bounds the elements of the vector if they fall below their corresponding lower bound values.
/// @param lower_bound Lower bound values.

template <class Type>
Vector<Type> Vector<Type>::calculate_lower_bounded(const Vector<Type>& lower_bound) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
 
   int lower_bound_size = lower_bound.get_size();

   if(lower_bound_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> calculate_lower_bounded(const Vector<Type>&) const method." << std::endl
                << "Lower bound size must be equal to vector size." << std::endl;

      exit(1);
   }

   #endif

   Vector<Type> bounded_vector(size);

   // Apply lower bound

   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound[i])
      {
         bounded_vector[i] = lower_bound[i];
      }
     else
     {
        bounded_vector[i] = data[i];
     }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_upper_bounded(const Type&) const method

/// This method bounds the elements of the vector if they fall above an upper bound value.
/// @param upper_bound Upper bound value.

template <class Type>
Vector<Type> Vector<Type>::calculate_upper_bounded(const Type& upper_bound) const
{
   Vector<Type> bounded_vector(size);

   for(int i = 0; i < size; i++)
   {
      if(data[i] > upper_bound)
      {
         bounded_vector[i] = upper_bound;
      }
     else
     {
        bounded_vector[i] = data[i];
     }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_upper_bounded(const Vector<Type>&) const method

/// This method bounds the elements of the vector if they fall above their corresponding upper bound values.
/// @param upper_bound Upper bound values.

template <class Type>
Vector<Type> Vector<Type>::calculate_upper_bounded(const Vector<Type>& upper_bound) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
 
   int upper_bound_size = upper_bound.get_size();

   if(upper_bound_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> calculate_upper_bounded(const Vector<Type>&) const method." << std::endl
                << "Upper bound size must be equal to vector size." << std::endl;

      exit(1);
   }

   #endif

   Vector<Type> bounded_vector(size);

   // Apply upper bound

   for(int i = 0; i < size; i++)
   {
      if(data[i] > upper_bound[i])
      {
         bounded_vector[i] = upper_bound[i];
      }
     else
     {
        bounded_vector[i] = data[i];
     }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_upper_bounded(const Type&, const Type&) const method

/// This method bounds the elements of the vector if they fall above or below their lower or upper
/// bound values, respectively.
/// @param lower_bound Lower bound value.
/// @param upper_bound Upper bound value.

template <class Type>
Vector<Type> Vector<Type>::calculate_lower_upper_bounded(const Type& lower_bound, const Type& upper_bound) const
{
   Vector<Type> bounded_vector(size);

   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound)
      {
         bounded_vector[i] = lower_bound;
      }
      else if(data[i] > upper_bound)
      {
         bounded_vector[i] = upper_bound;
      }
     else
     {
        bounded_vector[i] = data[i];
     }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_upper_bounded(const Vector<Type>&, const Vector<Type>&) const method

/// This method bounds the elements of the vector if they fall above or below their corresponding lower or upper
/// bound values, respectively.
/// @param lower_bound Lower bound values.
/// @param upper_bound Upper bound values.

template <class Type>
Vector<Type> Vector<Type>::calculate_lower_upper_bounded(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound)
const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
 
   int lower_bound_size = lower_bound.get_size();
   int upper_bound_size = upper_bound.get_size();

   if(lower_bound_size != size || upper_bound_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> calculate_lower_upper_bounded(const Vector<Type>&, const Vector<Type>&) const method." << std::endl
                << "Lower and upper bound sizes must be equal to vector size." << std::endl;

      exit(1);
   }

   #endif

   Vector<Type> bounded_vector(size);

   // Apply lower and upper bounds

   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound[i])
      {
         bounded_vector[i] = lower_bound[i];
      }
      else if(data[i] > upper_bound[i])
      {
         bounded_vector[i] = upper_bound[i];
      }
     else
     {
        bounded_vector[i] = data[i];
     }
   }

   return(bounded_vector);
}


// void apply_lower_bound(const Type&) method

template <class Type>
void Vector<Type>::apply_lower_bound(const Type& lower_bound) 
{       
   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound)
      {
         data[i] = lower_bound;
      }
   }
}


// void apply_lower_bound(const Vector<Type>&) method

template <class Type>
void Vector<Type>::apply_lower_bound(const Vector<Type>& lower_bound)
{
   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound[i])
      {
         data[i] = lower_bound[i];
      }
   }
}


// void apply_upper_bound(const Type&) method

template <class Type>
void Vector<Type>::apply_upper_bound(const Type& upper_bound)
{
   for(int i = 0; i < size; i++)
   {
      if(data[i] > upper_bound)
      {
         data[i] = upper_bound;
      }
   }
}


// void apply_upper_bound(const Vector<Type>&) method

template <class Type>
void Vector<Type>::apply_upper_bound(const Vector<Type>& upper_bound)
{
   for(int i = 0; i < size; i++)
   {
      if(data[i] > upper_bound[i])
      {
         data[i] = upper_bound[i];
      }
   }
}


// void apply_lower_upper_bounds(const Type&, const Type&) method

template <class Type>
void Vector<Type>::apply_lower_upper_bounds(const Type& lower_bound, const Type& upper_bound)
{
   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound)
      {
         data[i] = lower_bound;
      }
      else if(data[i] > upper_bound)
      {
         data[i] = upper_bound;
      }
   }
}


// void apply_lower_upper_bounds(const Vector<Type>&, const Vector<Type>&) method

template <class Type>
void Vector<Type>::apply_lower_upper_bounds(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound)
{
   for(int i = 0; i < size; i++)
   {
      if(data[i] < lower_bound[i])
      {
         data[i] = lower_bound[i];
      }
      else if(data[i] > upper_bound[i])
      {
         data[i] = upper_bound[i];
      }
   }
}


// Vector<Type> operator + (const Type&) const method 

/// Sum vector+scalar arithmetic operator. 
/// @param scalar Scalar value to be added to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator + (const Type& scalar) const
{       
   Vector<Type> sum(size);

   for(int i = 0; i < size; i++)
   {
      sum[i] = data[i] + scalar;
   }
   
   return(sum);
}


// Vector<Type> operator + (const Vector<Type>&) const method

/// Sum vector+vector arithmetic operator. 
/// @param other_vector Vector to be added to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator + (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template. " << std::endl
                << "Vector<Type> operator + (const Vector<Type>) const." << std::endl
                << "Size of vectors is " << size << " and " << other_size << " and they must be the same." 
                << std::endl;

      exit(1);          
   }

   #endif

   Vector<Type> sum(size);
  
   for(int i = 0; i < size; i++)
   {
      sum[i] = data[i] + other_vector[i];
   }
   
   return(sum);
}


//Vector<Type> operator - (const Type&) const method 

/// Difference vector-scalar arithmetic operator.
/// @param scalar Scalar value to be subtracted to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator - (const Type& scalar) const
{       
   Vector<Type> difference(size);

   for(int i = 0; i < size; i++)
   {
      difference[i] = data[i] - scalar;
   }
   
   return(difference);
}


// Vector<Type> operator - (const Vector<Type>&) const method

/// Difference vector-vector arithmetic operator.
/// @param other_vector vector to be subtracted to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator - (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> operator - (const Vector<Type>&) const." << std::endl
                << "Size of vectors is " << size << " and " << other_size << " and they must be the same." 
                << std::endl;

      exit(1);          
   }
      
   #endif

   Vector<Type> difference(size);
  
   for(int i = 0; i < size; i++)
   {
      difference[i] = data[i] - other_vector[i];
   }
   
   return(difference);
}


// Vector<Type> operator * (const Type&) const method 

/// Product vector*scalar arithmetic operator.
/// @param scalar Scalar value to be multiplied to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator * (const Type& scalar) const
{       
   Vector<Type> product(size);

   for(int i = 0; i < size; i++)
   {
      product[i] = data[i]*scalar;
   }
   
   return(product);
}


// Type operator * (const Vector<Type>&) const method

/// Element by element product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator * (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> operator * (const Vector<Type>&) const." << std::endl
                << "Size of other vector (" << other_size << ") must be equal to size of this vector (" << size << ")."
                << std::endl;

      exit(1);          
   }

   #endif

   Vector<Type> product(size);
  
   for(int i = 0; i < size; i++)
   {
      product[i] = data[i]*other_vector[i];
   }
   
   return(product);
}


// Vector<Type> dot(const Matrix<Type>&) const method

/// This method returns the dot product of this vector with a matrix.
/// The number of rows of the matrix must be equal to the size of the vector.
/// @param matrix matrix to be multiplied to this vector.

template <class Type>
Vector<Type> Vector<Type>::dot(const Matrix<Type>& matrix) const
{
   int rows_number = matrix.get_rows_number();

   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(rows_number != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> dot(const Matrix<Type>&) const method." << std::endl
                << "Matrix number of rows must be equal to vector size." << std::endl;

      exit(1);          
   }

   #endif

   int columns_number = matrix.get_columns_number();

   Vector<Type> product(columns_number);
  
   for(int j = 0; j < columns_number; j++)
   {     
      product[j] = 0;      

      for(int i = 0; i < rows_number; i++)
      {
         product[j] += data[i]*matrix[i][j];
      }
   }
    
   return(product);
}


// Vector<Type> dot(const Vector<Type>&) const method

/// Dot product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.

template <class Type>
Type Vector<Type>::dot(const Vector<Type>& other_vector) const
{            
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Type dot(const Vector<Type>&) const method." << std::endl
                << "Both vector sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif

   Type dot_product = 0;
  
   for(int i = 0; i < size; i++)
   {
      dot_product += data[i]*other_vector[i];
   }
   
   return(dot_product);
}


// Matrix<Type> outer(const Vector<Type>&) const method

/// Outer product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.

template <class Type>
Matrix<Type> Vector<Type>::outer(const Vector<Type>& other_vector) const
{            
   int other_size = other_vector.get_size();

   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Matrix<Type> outer(const Vector<Type>&) const method." << std::endl
                << "Both vector sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif

   int rows_number = size;
   int columns_number = other_size;
   
   Matrix<Type> outer(rows_number, columns_number);
     
   for(int i = 0;  i < rows_number; i++)
   {
      for(int j = 0;  j < columns_number; j++)
      {
         outer[i][j] = data[i]*other_vector[j];
      }           
   }
   
   return(outer);
}


//Vector<Type> operator / (const Type&) const method 

/// Cocient vector/scalar arithmetic operator.
/// @param scalar Scalar value to be divided to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator / (const Type& scalar) const
{       
   Vector<Type> cocient(size);

   for(int i = 0; i < size; i++)
   {
      cocient[i] = data[i]/scalar;
   }
   
   return(cocient);
}


// Vector<Type> operator / (const Vector<Type>&) const method

/// Cocient vector/vector arithmetic operator.
/// @param other_vector vector to be divided to this vector.

template <class Type>
Vector<Type> Vector<Type>::operator / (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)            

   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> operator / (const Vector<Type>&) const." << std::endl
                << "Both vector sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif

   Vector<Type> cocient(size);
  
   for(int i = 0; i < size; i++)
   {
      cocient[i] = data[i]/other_vector[i];
   }
   
   return(cocient);
}


// void operator += (const Type&) const

/// Scalar sum and assignment operator.
/// @param value Scalar value to be added to this vector.

template <class Type>
void Vector<Type>::operator += (const Type& value) const
{         
   for(int i = 0; i < size; i++)
   {
      data[i] += value;
   }
}


// void operator += (const Vector<Type>&) const

/// Vector sum and assignment operator.
/// @param other_vector Vector to be added to this vector.

template <class Type>
void Vector<Type>::operator += (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)            

   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void operator += (const Vector<Type>&) const." << std::endl
                << "Both vector sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif
  
   for(int i = 0; i < size; i++)
   {
      data[i] += other_vector[i];
   }
}


// void operator -= (const Type&) const

/// Scalar rest and assignment operator.
/// @param value Scalar value to be subtracted to this vector.

template <class Type>
void Vector<Type>::operator -= (const Type& value) const
{         
   for(int i = 0; i < size; i++)
   {
      data[i] -= value;
   }
}


// void operator -= (const Vector<Type>&) const

/// Vector rest and assignment operator.
/// @param other_vector Vector to be subtracted to this vector.

template <class Type>
void Vector<Type>::operator -= (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)            

   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void operator -= (const Vector<Type>&) const." << std::endl
                << "Both vector sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif
  
   for(int i = 0; i < size; i++)
   {
      data[i] -= other_vector[i];
   }
}


// void operator *= (const Type&) const

/// Scalar product and assignment operator.
/// @param value Scalar value to be multiplied to this vector.

template <class Type>
void Vector<Type>::operator *= (const Type& value) const
{         
   for(int i = 0; i < size; i++)
   {
      data[i] *= value;
   }
}


// void operator *= (const Vector<Type>&) const

/// Vector product and assignment operator.
/// @param other_vector Vector to be multiplied to this vector.

template <class Type>
void Vector<Type>::operator *= (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)            

   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void operator *= (const Vector<Type>&) const." << std::endl
                << "Both vector sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif
  
   for(int i = 0; i < size; i++)
   {
      data[i] *= other_vector[i];
   }
}


// void operator /= (const Type&) const

/// Scalar division and assignment operator.
/// @param value Scalar value to be divided to this vector.

template <class Type>
void Vector<Type>::operator /= (const Type& value) const
{         
   for(int i = 0; i < size; i++)
   {
      data[i] /= value;
   }
}


// void operator /= (const Vector<Type>&) const

/// Vector division and assignment operator.
/// @param other_vector Vector to be divided to this vector.

template <class Type>
void Vector<Type>::operator /= (const Vector<Type>& other_vector) const
{       
   // Control sentence (if debug)            

   #ifdef _DEBUG 

   int other_size = other_vector.get_size();

   if(other_size != size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void operator /= (const Vector<Type>&) const." << std::endl
                << "Both vector sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif
  
   for(int i = 0; i < size; i++)
   {
      data[i] /= other_vector[i];
   }
}


// Type* begin(void) const method

/// This method returns a vector to the first element in the container.

template <class Type>
Type* Vector<Type>::begin(void) const
{
   return(data);
}


// Type* end(void) const method

/// This method returns a vector to the last element in the container. 

template <class Type>
Type* Vector<Type>::end(void) const
{
   return(data + size);
}


// Input operator

/// This method re-writes the input operator >> for the Vector template. 
/// @param is Input stream.
/// @param v Input vector.

template<typename Type>
std::istream& operator >> (std::istream& is, Vector<Type>& v)
{
   int size = v.get_size();
   
   for(int i = 0; i < size; i++)
   {
      is >> v[i];
   }

   return(is);
}


// Output operator

/// This method re-writes the output operator << for the Vector template. 
/// @param os Output stream.
/// @param v Output vector.

template<typename Type>
std::ostream& operator << (std::ostream& os, Vector<Type>& v)
{
   int size = v.get_size();
   
   for(int i = 0; i < size; i++)
   {
      os << v[i] << " ";
   }

   return(os);
}


// std::string to_XML(bool) method

/// This method returns a string representation of a vector object. 
/// It contains the members in an XML-type format. 
/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

template <class Type>
std::string Vector<Type>::to_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Header 

   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='Vector'>" << std::endl;
   }

   // Size

   buffer << "<Size>" << std::endl
          << size << std::endl
          << "</Size>" << std::endl;

   // Display

   buffer << "<Display>" << std::endl
          << display << std::endl
          << "</Display>" << std::endl;
  
   // Data

   buffer << "<Data>" << std::endl;

   for(int i = 0; i < size; i++)
   {
      buffer << data[i] << " ";      
   }

   buffer << std::endl;

   buffer << "</Data>" << std::endl;

   return(buffer.str());   
}


// void load(const char*) method

/// This method loads the members of a vector from an XML-type file.
/// Please be careful with the file format, which is specified in the user's guide.
/// @param filename Name of vector file.

template <class Type>
void Vector<Type>::load(const char* filename)
{
   // Open file

   std::ifstream file(filename);
   
   if(!file.is_open())
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open vector XML-type file."  << std::endl;

      exit(1);
   }

   std::string line;
   std::string word;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='Vector'>") 
   {
//      std::cerr << "Flood Error: Vector template." << std::endl
//                << "void load(const char*) method." << std::endl
//				<< "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   // Size

   file >> word;

   if(word != "<Size>") 
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown size begin tag: " << line << std::endl;
 
      exit(1);
   }

   int new_size;

   file >> new_size;

   set_size(new_size);

   file >> word;

   if(word != "</Size>") 
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown size end tag: " << line << std::endl;
 
      exit(1);
   }

   while(!file.eof())
   {
      file >> word; 

      if(word == "<Display>")
	  {
         bool new_display;

         file >> new_display; 

		 file >> word;

         if(word != "</Display>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
			      	  << "Unknown display end tag: " << word << std::endl;
 
            exit(1);
         }
	  }         
      else if(word == "<Data>") 
      {
         for(int i = 0; i < size; i++)
         {
            file >> data[i];
         }
    
         file >> word;

         if(word != "</Data>") 
         {
            std::cerr << "Flood Error: Vector template." << std::endl
                      << "void load(const char*) method." << std::endl
	       	          << "Unknown data end tag: " << word << std::endl;
 
            exit(1);
         }
	  }
	  else
	  {
      //   std::cerr << "Flood Error: Matrix template." << std::endl
      //             << "void load(const char*) method." << std::endl
	  //     	       << "Unknown tag: " << word << std::endl;
 
      //   exit(1);
      }
   }

   // Close file

   file.close();
}


// void load_data(const char*) method

/// This method loads the elements of a vector from a data file.
/// The file format is as follows:
/// element_0 element_1 ... element_N-1
/// @param filename Filename.

template <class Type>
void Vector<Type>::load_data(const char* filename)
{
   // Open file

   std::ifstream file(filename);
   
   if(!file.is_open())
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void load_data(const char*) method." << std::endl
                << "Cannot open vector data file."  << std::endl;

      exit(1);
   }

   // Load data

   for(int i = 0; i < size; i++)
   {
      file >> data[i];
   }

   // Close file

   file.close();
}


// void save(const char*) method

/// This method saves to a XML-type file the elements of the vector.
/// The file format is as follows:
/// element_0 element_1 ... element_N-1
/// @param filename Name of vector XML-type file.

template <class Type>
void Vector<Type>::save(const char* filename)
{
   std::fstream file; 

   // Open file

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void save(const char*) method." << std::endl
                << "Cannot open vector file." << std::endl;

      exit(1);
   }

   // Write file

   file << to_XML(true) << std::endl;

   // Close file

   file.close();
}


// void save_data(const char*) method

/// This method saves to a data file the elements of the vector.
/// The file format is as follows:
/// element_0 element_1 ... element_N-1
/// @param filename Filename.

template <class Type>
void Vector<Type>::save_data(const char* filename)
{
   std::fstream file; 

   // Open file

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: Vector template." << std::endl
                << "void save_data(const char*) method." << std::endl
                << "Cannot open vector data file." << std::endl;

      exit(1);
   }

   // Write file

   for(int i = 0; i < size; i++)
   {
      file << data[i] << " ";
   
   }

   file << std::endl;

   // Close file

   file.close();
}


// void insert(int, const Vector<Type>&) const method

/// Insert another vector starting from a given position.
/// @param position Insertion position.
/// @param other_vector Vector to be inserted.

template <class Type>
void Vector<Type>::insert(int position, const Vector<Type>& other_vector) const
{
   int other_size = other_vector.get_size();

   // Control sentence (if debug)            

   #ifdef _DEBUG 

   if(position + other_size > size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "void insert(int, const Vector<Type>&) const method." << std::endl
                << "Cannot insert vector." << std::endl;

      exit(1);          
   }

   #endif

   for(int i = 0; i < other_size; i++)
   {
      data[position + i] = other_vector[i];
   }
}


// Vector<Type> extract(int, int) method

/// Extract a vector of a given size from a given position
/// @param position Extraction position.
/// @param other_size Size of vector to be extracted.

template <class Type>
Vector<Type> Vector<Type>::extract(int position, int other_size) const
{
   // Control sentence (if debug)            

   #ifdef _DEBUG 

   if(position + other_size > size)
   {
      std::cerr << "Flood Error: Vector Template." << std::endl 
                << "Vector<Type> extract(int, int) method." << std::endl
                << "Cannot extract vector." << std::endl;

      exit(1);          
   }

   #endif

   Vector<Type> other_vector(other_size);

   for(int i = 0; i < other_size; i++)
   {
      other_vector[i] = data[position + i];
   }

   return(other_vector);
}


// Vector<Type> assemble(const Vector<Type>&) const method

/// Assemble two vectors.
/// @param other_vector Vector to be assembled to this vector. 

template <class Type>
Vector<Type> Vector<Type>::assemble(const Vector<Type>& other_vector) const
{
   int other_size = other_vector.get_size();

   if(size == 0 && other_size == 0)
   {
      Vector<Type> assembly;

      return(assembly);
   }
   else if(size == 0)
   {
      return(other_vector);
   }
   else if(other_size == 0)
   {
      return(*this);
   }
   else
   {
      int other_size = other_vector.get_size();

      Vector<Type> assembly(size + other_size);

      for(int i = 0; i < size; i++)
      {
         assembly[i] = data[i];
      }

      for(int i = 0; i < other_size; i++)
      {
         assembly[size+i] = other_vector[i];
      } 
   
      return(assembly);
   }
}


// double calculate_random_uniform(double, double) method

/// This method returns a random number chosen from a uniform distribution.
/// @param minimum Minimum value.
/// @param maximum Maximum value.

template <class Type>
double Vector<Type>::calculate_random_uniform(double minimum, double maximum) const
{
   double random = (double)rand()/(RAND_MAX+1.0);

   double random_uniform = minimum + (maximum-minimum)*random;

   return(random_uniform);
}


// double calculate_random_normal(double, double) method

/// This method returns a random number chosen from a normal distribution.
/// @param mean Mean value of normal distribution.
/// @param standard_deviation Standard deviation value of normal distribution.

template <class Type>
double Vector<Type>::calculate_random_normal(double mean, double standard_deviation) const
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
