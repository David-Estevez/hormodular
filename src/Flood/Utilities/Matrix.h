/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   M A T R I X   C O N T A I N E R                                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MATRIX_H__
#define __MATRIX_H__

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <cmath>

// Flood includes

#include "Vector.h"

namespace Flood
{

/// This template class defines a matrix for general purpose use.
/// This matrix also implements some mathematical methods which can be useful. 

template <class Type>
class Matrix 
{

public:

   // CONSTRUCTORS

   explicit Matrix(void);

   explicit Matrix(int, int);

   explicit Matrix(int, int, const Type&);

   explicit Matrix(const char*);

   Matrix(const Matrix&);

   // DESTRUCTOR

   virtual ~Matrix(void);


   // ASSIGNMENT OPERATOR

   Matrix<Type>& operator = (const Matrix<Type>&);


   // REFERENCE OPERATORS

   inline Type* operator [] (int);
   inline const Type* operator [] (int) const;


   // ARITHMETIC OPERATORS

   Matrix<Type> operator + (const Type&) const;
   Matrix<Type> operator + (const Matrix<Type>&) const;

   Matrix<Type> operator - (const Type&) const;
   Matrix<Type> operator - (const Matrix<Type>&) const;

   Matrix<Type> operator * (const Type&) const;
   Matrix<Type> operator * (const Matrix<Type>&) const;

   Matrix<Type> operator / (const Type&) const;
   Matrix<Type> operator / (const Matrix<Type>&) const;


   // ARITHMETIC AND ASSIGNMENT OPERATORS

   //void operator += (const Type&) const;
   //void operator += (const Matrix<Type>&) const;

   //void operator -= (const Type&) const;
   //void operator -= (const Matrix<Type>&) const;

   //void operator *= (const Type&) const;
   //void operator *= (const Matrix<Type>&) const;

   //void operator /= (const Type&) const;
   //void operator /= (const Matrix<Type>&) const;


   // EQUALITY AND RELATIONAL OPERATORS 

   bool operator == (const Matrix<Type>&) const;
   bool operator == (const Type&) const;

   bool operator != (const Matrix<Type>&) const;
   bool operator != (const Type&) const;

   bool operator > (const Matrix<Type>&) const;
   bool operator > (const Type&) const;

   bool operator < (const Matrix<Type>&) const;
   bool operator < (const Type&) const;
   
   bool operator >= (const Matrix<Type>&) const;
   bool operator >= (const Type&) const;
   
   bool operator <= (const Matrix<Type>&) const;
   bool operator <= (const Type&) const;


   // METHODS

   // Get methods

   inline int get_rows_number(void) const;
   inline int get_columns_number(void) const;  

   Vector<Type> get_row(int) const;
   Vector<Type> get_column(int) const;

   Matrix<Type> get_submatrix(const Vector<int>&, const Vector<int>&) const;

   Vector<Type> get_diagonal(void) const;

   bool get_display(void) const;

   // Set methods

   void set(void);
   void set(int, int);
   void set(int, int, const Type&);
   void set(const Matrix&);
   void set(const char*);

   void set_row(int, const Vector<Type>&) const;
   void set_column(int, const Vector<Type>&) const;

   void set_rows_number(int);
   void set_columns_number(int);

   void set_display(bool);

   // Resize methods

   void resize(int, int);

   void add_row(const Vector<Type>&);
   void add_column(const Vector<Type>&);

   void subtract_row(int);
   void subtract_column(int);

   // Initialization methods

   void initialize(const Type&) const;

   void initialize_uniform(void);
   void initialize_uniform(double, double);
   void initialize_uniform(const Matrix<double>&, const Matrix<double>&) ;

   void initialize_normal(void);
   void initialize_normal(double, double);
   void initialize_normal(const Matrix<double>&, const Matrix<double>&);

   void set_to_identity(void) const;

   // Mathematical methods

   Vector<Type> dot(const Vector<Type>&) const;
   Matrix<Type> dot(const Matrix<Type>&) const;

   Vector< Vector<double> > calculate_mean_standard_deviation(void) const;
   Vector< Vector<double> > calculate_mean_standard_deviation(const Vector<int>&) const;
   Vector< Vector<double> > calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const;

   Vector< Vector<Type> > calculate_minimum_maximum(void) const;
   Vector< Vector<Type> > calculate_minimum_maximum(const Vector<int>&) const;
   Vector< Vector<Type> > calculate_minimum_maximum(const Vector<int>&, const Vector<int>&) const;

   Type calculate_determinant(void) const;
   Matrix<Type> calculate_transpose(void) const;
   Matrix<Type> calculate_cofactor(void) const;
   Matrix<Type> calculate_inverse(void) const;

   bool is_symmetric(void) const;
   bool is_antisymmetric(void) const;

   // Scaling methods

   void scale_mean_standard_deviation(const Vector<double>&, const Vector<double>&);
   void scale_minimum_maximum(const Vector<double>&, const Vector<double>&);

   // Unscaling methods

   void unscale_mean_standard_deviation(const Vector<double>&, const Vector<double>&);
   void unscale_minimum_maximum(const Vector<double>&, const Vector<double>&);

   // Utility methods

   std::string to_XML(bool);

   void print(void);
   void print_data(void);

   void save(const char*);
   void save_data(const char*);

   void load(const char*);
   void load_data(const char*);

private:

   /// Number of rows in matrix.

   int rows_number;

   /// Number of columns in matrix.

   int columns_number;

   bool display;

   /// Double pointer to a Type.

   Type** data;

   // Utility methods

   double calculate_random_uniform(double, double);
   double calculate_random_normal(double, double);
};


// CONSTRUCTORS

/// Default constructor. It creates a matrix with zero rows and zero columns.

template <class Type>
Matrix<Type>::Matrix(void) 
{
   rows_number = 0;
   columns_number = 0;
   display = true;
   data = NULL;
}


/// Constructor. It creates a matrix with n rows and m columns, containing n*m copies of the default value for Type. 
///
/// @param new_rows_number Number of rows in matrix.
/// @param new_columns_number Number of columns in matrix.

template <class Type>
Matrix<Type>::Matrix(int new_rows_number, int new_columns_number) 
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(new_rows_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int)." << std::endl
                << "Number of rows must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(new_columns_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int)." << std::endl
                << "Number of columns must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;
      data = NULL;
   }
   else if(new_rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int)." << std::endl
                << "Number of rows must be greater than zero." << std::endl;

      exit(1);   
   }
   else if(new_columns_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int)." << std::endl
                << "Number of columns must be greater than zero." << std::endl;

      exit(1);   
   }
   else
   {
      rows_number = new_rows_number;
      columns_number = new_columns_number;

      data = new Type*[rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(int i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }
   }

   display = true;
}


/// Constructor. It creates a matrix with n rows and m columns, containing n*m copies of the type value of Type. 
/// @param new_rows_number Number of rows in matrix.
/// @param new_columns_number Number of columns in matrix.
/// @param type Value of Type.

template <class Type>
Matrix<Type>::Matrix(int new_rows_number, int new_columns_number, const Type& type) 
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(new_rows_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int, const Type&)." << std::endl
                << "Number of rows must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(new_columns_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int, const Type&)." << std::endl
                << "Number of columns must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;
      data = NULL;
   }
   else if(new_rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int, const Type&)." << std::endl
                << "Number of rows must be greater than zero." << std::endl;

      exit(1);   
   }
   else if(new_columns_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Constructor Matrix(int, int, const Type&)." << std::endl
                << "Number of columns must be greater than zero." << std::endl;

      exit(1);   
   }
   else
   {
      // Set sizes

      rows_number = new_rows_number;
      columns_number = new_columns_number;

      data = new Type*[new_rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(int i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }

      // Initialize

      for(int i = 0; i < rows_number; i++)
      {
         for(int j = 0; j < columns_number; j++)
         {
            data[i][j] = type;
         }
      }
   }

   display = true;
}


/// File constructor. It creates a matrix which members are loaded froma a XML-type file.
/// @param filename Name of matrix XML-type file. 

template <class Type>
Matrix<Type>::Matrix(const char* filename) 
{
   rows_number = 0;
   columns_number = 0;
   display = true;
   data = NULL;

   load(filename);
}


/// Copy constructor. It creates a copy of an existing matrix. 
/// @param other_matrix Matrix to be copied.

template <class Type>
Matrix<Type>::Matrix(const Matrix& other_matrix) 
{
   int new_rows_number = other_matrix.rows_number;
   int new_columns_number = other_matrix.columns_number;

   display = other_matrix.display;
   data = NULL;

   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(new_rows_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Copy constructor." << std::endl
                << "Number of rows must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(new_columns_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Copy constructor." << std::endl
                << "Number of columns must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;
      data = NULL;
   }
   else if(new_rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Copy constructor." << std::endl
                << "Number of rows must be greater than zero." << std::endl;

      exit(1);   
   }
   else if(new_columns_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "Copy constructor." << std::endl
                << "Number of columns must be greater than zero." << std::endl;

      exit(1);   
   }
   else
   {
      rows_number = new_rows_number;
      columns_number = new_columns_number;

      data = new Type*[rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(int i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }
   }

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = other_matrix[i][j];
      }
   }
}


// DESTRUCTOR

/// Destructor. 

template <class Type>
Matrix<Type>::~Matrix(void)
{
   if(data != NULL) 
   {
      delete[] (data[0]);
      delete[] (data);
   }
}


// ASSIGNMENT OPERATORS

/// Assignment operator. It assigns to self a copy of an existing matrix.
/// @param other_matrix Matrix to be assigned.

template <class Type>
Matrix<Type>& Matrix<Type>::operator = (const Matrix<Type>& other_matrix)
{
   if(this != &other_matrix) 
   {
      if(rows_number != other_matrix.rows_number || columns_number != other_matrix.columns_number) // other sizes
      {
         if(data != NULL) 
         {
            delete[] (data[0]);
            delete[] (data);
         }

         rows_number = other_matrix.rows_number;
         columns_number = other_matrix.columns_number;

         data = new Type*[rows_number];
         data[0] = new Type[rows_number*columns_number];

         for(int i = 1; i < rows_number; i++)
         {
            data[i] = data[i-1] + columns_number;
         }
      }


      for(int i = 0; i < rows_number; i++)
      {
         for(int j = 0; j < columns_number; j++)
         {
            data[i][j] = other_matrix[i][j];
         }
      }
   }

   return(*this);
}


// REFERENCE OPERATORS

/// Reference operator.  

template <class Type>
inline Type* Matrix<Type>::operator [] (int i)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(i < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "operator [] (int)." << std::endl
                << "Row index (" << i << ") must be equal or greater than zero." << std::endl;

      exit(1);
   }

   if(i >= rows_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "operator [] (int)." << std::endl
                << "Row index (" << i << ") must be less than number of rows (" << rows_number << ")." << std::endl;

      exit(1);
   }

   #endif

   // Return matrix element

   return(data[i]);
}


/// Reference operator.  

template <class Type>
inline const Type* Matrix<Type>::operator [] (int i) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(i < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "operator [] (int) const." << std::endl
                << "Row index must be equal or greater than zero." << std::endl;

      exit(1);
   }

   if(i >= rows_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "operator [] (int) const." << std::endl
                << "Row index must be less than number of rows." << std::endl;

      exit(1);
   }

   #endif

   // Return matrix element

   return(data[i]);
}


// bool operator == (const Matrix<Type>&) const

/// Equivalent relational operator between this matrix and other matrix.
/// It produces true if all the elements of the two matrices are equal, and false otherwise.
/// @param other_matrix Matrix to be compared with.

template <typename Type>
bool Matrix<Type>::operator == (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();
   int other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator == (const Matrix<Type>&) const." << std::endl
                << "Both number of rows must be the same." << std::endl;

      exit(1);          
   }
   else if(other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator == (const Matrix<Type>&) const." << std::endl
                << "Both number of columns must be the same." << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] != other_matrix[i][j])
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator == (const Type&)

/// Equivalent relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <typename Type>
bool Matrix<Type>::operator == (const Type& value) const
{       
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] != value)
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator != (const Matrix<Type>&)

/// Not equivalent relational operator between this matrix and other matrix.
/// It produces true if the two matrices have any not equal element, and false otherwise.
/// @param other_matrix Matrix to be compared with.

template <typename Type>
bool Matrix<Type>::operator != (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();
   int other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator != (const Matrix<Type>&) const." << std::endl
                << "Both numbers of rows must be the same." << std::endl;

      exit(1);          
   }
   else if(other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator != (const Matrix<Type>&) const." << std::endl
                << "Both numbers of columns must be the same." << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] != other_matrix[i][j])
        {
            return(true);
        }     
      }
   }

   return(false);
}


// bool operator != (const Type&) const

/// Not equivalent relational operator between this matrix and a Type value.
/// It produces true if some element of this matrix is not equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <typename Type>
bool Matrix<Type>::operator != (const Type& value) const
{            
   // Control sentence (if debug)      
       
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] != value)
         {
            return(true);
         }     
      }
   }

   return(false);
}


// bool operator > (const Matrix<Type>&) const

/// Greater than relational operator between this matrix and other vector.
/// It produces true if all the elements of this matrix are greater than the corresponding elements of the other matrix,
/// and false otherwise.
/// @param other_matrix matrix to be compared with.

template <typename Type>
bool Matrix<Type>::operator > (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();
   int other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator > (const Matrix<Type>&) const." << std::endl
                << "Both numbers of rows must be the same." << std::endl;

      exit(1);          
   }
   else if(other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator > (const Matrix<Type>&) const." << std::endl
                << "Both numbers of columns must be the same." << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < rows_number; j++)
      {
         if(data[i][j] <= other_matrix[i][j])
          {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator > (const Type&) const

/// Greater than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are greater than the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <typename Type>
bool Matrix<Type>::operator > (const Type& value) const
{       
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < rows_number; j++)
      {
         if(data[i][j] <= value)
          {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator < (const Matrix<Type>&) const

/// Less than relational operator between this matrix and other matrix.
/// It produces true if all the elements of this matrix are less than the corresponding elements of the other matrix,
/// and false otherwise.
/// @param other_matrix Matrix to be compared with.

template <typename Type>
bool Matrix<Type>::operator < (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();
   int other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator < (const Matrix<Type>&) const." << std::endl
                << "Both numbers of rows must be the same." << std::endl;

      exit(1);          
   }
   else if(other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator < (const Matrix<Type>&) const." << std::endl
                << "Both numbers of columns must be the same." << std::endl;

      exit(1);          
   }

   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] >= other_matrix[i][j])
         {
           return(false);
         }      
      }
   }

   return(true);
}


// bool operator < (const Type&) const

/// Less than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are less than the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <typename Type>
bool Matrix<Type>::operator < (const Type& value) const
{       
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] >= value)
         {
           return(false);
         }      
      }
   }

   return(true);
}


// bool operator >= (const Matrix<Type>&) const

/// Greater than or equal to relational operator between this matrix and other matrix.
/// It produces true if all the elements of this matrix are greater than or equal to the corresponding elements of the
/// other matrix, and false otherwise.
/// @param other_matrix Matrix to be compared with.

template <typename Type>
bool Matrix<Type>::operator >= (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();
   int other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator >= (const Matrix<Type>&) const." << std::endl
                << "Both number of rows must be the same." << std::endl;

      exit(1);          
   }
   else if(other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator >= (const Matrix<Type>&) const." << std::endl
                << "Both number of columns must be the same." << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] < other_matrix[i][j])
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator >= (const Type&) const

/// Greater than or equal to than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are greater than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <typename Type>
bool Matrix<Type>::operator >= (const Type& value) const
{       
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] < value)
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator <= (const Matrix<Type>&) const

/// Less than or equal to relational operator between this matrix and other matrix.
/// It produces true if all the elements of this matrix are less than or equal to the corresponding elements of the
/// other matrix, and false otherwise.
/// @param other_matrix Matrix to be compared with.

template <typename Type>
bool Matrix<Type>::operator <= (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();
   int other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator >= (const Matrix<Type>&) const." << std::endl
                << "Both numbers of rows must be the same." << std::endl;

      exit(1);          
   }
   else if(other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool operator >= (const Matrix<Type>&) const." << std::endl
                << "Both numbers of columns must be the same." << std::endl;

      exit(1);          
   }
      
   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] > other_matrix[i][j])
          {
            return(false);
         }     
      }
   }

   return(true);
}


// bool operator <= (const Type&) const

/// Less than or equal to than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are less than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

template <typename Type>
bool Matrix<Type>::operator <= (const Type& value) const
{       
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] > value)
          {
            return(false);
         }     
      }
   }

   return(true);
}


// METHODS

// int get_rows_number(void) const method

/// This method returns the number of rows in the matrix. 

template <class Type>
inline int Matrix<Type>::get_rows_number(void) const
{
   return(rows_number);
}


// int get_columns_number(void) const method

/// This method returns the number of columns in the matrix. 

template <class Type>
inline int Matrix<Type>::get_columns_number(void) const
{
   return(columns_number);
}


// bool get_display(void) const method

/// This method returns true if messages from this class are to be displayed on the screen, and false otherwise.

template <class Type>
bool Matrix<Type>::get_display(void) const
{
   return(display);
}


// void set(void) method

/// This method set the numbers of rows and columns of the matrix to zero. 

template <class Type>
void Matrix<Type>::set(void)
{
   if(data != NULL) 
   {
      delete[] (data[0]);
      delete[] (data);
   }

   rows_number = 0;
   columns_number = 0;
   data = NULL;
}


// void set(int, int) method

/// This method set new numbers of rows and columns in the matrix. 
/// @param new_rows_number Number of rows.
/// @param new_columns_number Number of columns.

template <class Type>
void Matrix<Type>::set(int new_rows_number, int new_columns_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(new_rows_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "void set(int, int) method." << std::endl
                << "Number of rows must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(new_columns_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "void set(int, int) method." << std::endl
                << "Number of columns must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   if(new_rows_number == rows_number && new_columns_number == columns_number)
   {
      // do nothing
   }
   else if(new_rows_number == 0 && new_columns_number == 0)
   {
      set();
   }
   else if(new_rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void set(int, int) method." << std::endl
                << "Number of rows must be greater than zero." << std::endl;

      exit(1);          
   }
   else if(new_columns_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void set(int, int) method." << std::endl
                << "Number of columns must be greater than zero." << std::endl;

      exit(1);          
   }
   else
   {
      rows_number = new_rows_number;
      columns_number = new_columns_number;

      if(data != NULL) 
      {
         delete[] (data[0]);
         delete[] (data);
      }

      data = new Type*[rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(int i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }
   }
}


// void set(int, int, const Type&) method

/// This method set new numbers of rows and columns in the matrix.
/// It also initializes all the matrix elements to a given value. 
/// @param new_rows_number Number of rows.
/// @param new_columns_number Number of columns.
/// @param value Initialization value.

template <class Type>
void Matrix<Type>::set(int new_rows_number, int new_columns_number, const Type& value)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(new_rows_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "void set(int, int, const Type&) method." << std::endl
                << "Number of rows must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(new_columns_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "void set(int, int, const Type&) method." << std::endl
                << "Number of columns must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   if(new_rows_number == rows_number && new_columns_number == columns_number)
   {
      // do nothing
   }
   else if(new_rows_number == 0 && new_columns_number == 0)
   {
      set();
   }
   else if(new_rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void set(int, int, const Type&) method." << std::endl
                << "Number of rows must be greater than zero." << std::endl;

      exit(1);          
   }
   else if(new_columns_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void set(int, int, const Type&) method." << std::endl
                << "Number of columns must be greater than zero." << std::endl;

      exit(1);          
   }
   else
   {
      set(new_rows_number, new_columns_number);
      initialize(value);     
   }
}


// void set(const Matrix&) method

/// This method sets all the members of the matrix to those of another matrix.
/// @param other_matrix Setting matrix. 

template <class Type>
void Matrix<Type>::set(const Matrix& other_matrix)
{
}


// void set(const char*) method

/// This method sets the members of this object by loading them from a XML-type file. 
/// @param filename Name of XML-type matrix file. 

template <class Type>
void Matrix<Type>::set(const char* filename)
{
   load(filename);
}


// void set_rows_number(int) method

/// This method sets a new number of rows in the matrix. 
/// @param new_rows_number Number of matrix rows. 

template <class Type>
void Matrix<Type>::set_rows_number(int new_rows_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(new_rows_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "void set_rows_number(int) method." << std::endl
                << "Number of rows must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   if(new_rows_number != rows_number) 
   {
      if(data != NULL) 
      {
         delete[] (data[0]);
         delete[] (data);
      }
 
      if(new_rows_number == 0 && columns_number == 0)
      {
         rows_number = 0;
         columns_number = 0;
         data = NULL;
      }
      else if(new_rows_number == 0)
      {
         std::cerr << "Flood Error: Matrix Template. " << std::endl
                   << "void set(int, int) method." << std::endl
                   << "Number of rows must be greater than zero." << std::endl;

         exit(1);   
      }
      else if(columns_number == 0)
      {
         std::cerr << "Flood Error: Matrix Template. " << std::endl
                   << "void set(int, int) method." << std::endl
                   << "Number of columns must be greater than zero." << std::endl;

         exit(1);   
      }
      else
      {
         rows_number = new_rows_number;

         data = new Type*[rows_number];
         data[0] = new Type[rows_number*columns_number];

         for(int i = 1; i < rows_number; i++)
         {
            data[i] = data[i-1] + columns_number;
         }
      }
   }
}


// void set_columns_number(int) method

/// This method sets a new number of columns in the matrix. 
/// @param new_columns_number Number of matrix columns. 

template <class Type>
void Matrix<Type>::set_columns_number(int new_columns_number)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(new_columns_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "void set_columns_number(int) method." << std::endl
                << "Number of columns must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif
}


// void set_display(bool) method

/// This method sets a new display value. 
/// @param new_display Display value. 

template <class Type>
void Matrix<Type>::set_display(bool new_display)
{
   display = new_display;
}


// void resize(int, int) method

/// This method sets new numbers of rows and columns in the vector.
/// It does initialize the new matrix with the previous values. 
/// @param new_rows_number New number of rows.
/// @param new_columns_number New number of columns.

template <class Type>
void Matrix<Type>::resize(int new_rows_number, int new_columns_number)
{
   // Control sentence (if debug)      
       
   #ifdef _DEBUG 

   if(new_rows_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void resize(int, int) method." << std::endl
                << "Number of rows must be equal or greater than zero." << std::endl;

      exit(1);          
   }
   else if(new_columns_number < 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void resize(int, int) method." << std::endl
                << "Number of columns must be equal or greater than zero." << std::endl;

      exit(1);          
   }
      
   #endif

   // Resize

   if(new_rows_number == rows_number && new_columns_number == columns_number)
   {   
      // Do nothing
   }
   else if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;

      if(data != NULL) 
      {
         delete[] (data[0]);
         delete[] (data);
      }

      data = NULL;    
   }
   else if(new_rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void resize(int, int) method." << std::endl
                << "Number of rows must be greater than zero." << std::endl;

      exit(1);          
   }
   else if(new_columns_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void resize(int, int) method." << std::endl
                << "Number of columns must be greater than zero." << std::endl;

      exit(1);          
   }
   else
   {
      if(new_rows_number >= rows_number && new_columns_number >= columns_number)
	  {
	     Matrix<Type> copy(*this);

		 set(new_rows_number, new_columns_number);

		 for(int i = 0; i < copy.get_rows_number(); i++)
		 {
            for(int j = 0; j < copy.get_columns_number(); j++)
			{
			   data[i][j] = copy[i][j];
			}		 
		 }

	  }
      else if(new_rows_number >= rows_number && new_columns_number <= columns_number)
	  {
	     Matrix<Type> copy(*this);

		 set(new_rows_number, new_columns_number);

		 for(int i = 0; i < copy.get_rows_number(); i++)
		 {
            for(int j = 0; j < new_columns_number; j++)
			{
			   data[i][j] = copy[i][j];
			}		 
		 }
	  }
	  else if(new_rows_number <= rows_number && new_columns_number >= columns_number)
	  {
	     Matrix<Type> copy(*this);

		 set(new_rows_number, new_columns_number);

		 for(int i = 0; i < new_rows_number; i++)
		 {
            for(int j = 0; j < copy.get_columns_number(); j++)
			{
			   data[i][j] = copy[i][j];
			}		 
		 }
	  }
	  else if(new_rows_number <= rows_number && new_columns_number >= columns_number)
	  {
	     Matrix<Type> copy(*this);

		 set(new_rows_number, new_columns_number);

		 for(int i = 0; i < new_rows_number; i++)
		 {
            for(int j = 0; j < new_columns_number; j++)
			{
			   data[i][j] = copy[i][j];
			}		 
		 }
	  }
   }
}


// Vector<Type> get_submatrix(const Vector<int>&, const Vector<int>&) const method

/// This method returns a matrix with the values of given rows and columns from this matrix. 
/// @param row_indices Indices of matrix rows. 
/// @param column_indices Indices of matrix columns. 

template <class Type>
Matrix<Type> Matrix<Type>::get_submatrix(const Vector<int>& row_indices, const Vector<int>& column_indices) const
{
   int row_indices_size = row_indices.get_size();
   int column_indices_size = column_indices.get_size();

   Matrix<Type> submatrix(row_indices_size, column_indices_size);

   int row_index;
   int column_index;

   for(int i = 0; i < row_indices_size; i++)
   {
      row_index = row_indices[i];

      for(int j = 0; j < column_indices_size; j++)
	  {
         column_index = column_indices[j];
          
		 submatrix[i][j] = data[row_index][column_index];
	  }
   }

   return(submatrix);
}



// Vector<Type> get_row(int) const method

/// This method returns the row i of the matrix. 
/// @param i Index of row.

template <class Type>
Vector<Type> Matrix<Type>::get_row(int i) const
{
   Vector<Type> row(columns_number);

   for(int j = 0; j < columns_number; j++)
   {
      row[j] = data[i][j];
   }

   return(row);
}


// Vector<Type> get_column(int) const method

/// This method returns the column j of the matrix. 
/// @param j Index of column.

template <class Type>
Vector<Type> Matrix<Type>::get_column(int j) const
{
   Vector<Type> column(rows_number);

   for(int i = 0; i < rows_number; i++)
   {
      column[i] = data[i][j];
   }

   return(column);
}


// Vector<Type> get_diagonal(void) const method

/// This method returns the diagonal of the matrix. 

template <class Type>
Vector<Type> Matrix<Type>::get_diagonal(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
       
   if(rows_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "Vector<Type> get_diagonal(void) const method." << std::endl
                << "Matrix must be squared." << std::endl;

      exit(1);          
   }

   #endif

   Vector<Type> diagonal(rows_number);

   for(int i = 0; i < rows_number; i++)
   {
      diagonal[i] = data[i][i];
   }

   return(diagonal);
}


// void set_row(int, const Vector<Type>&) const method

/// This method sets new values of a single row in the matrix. 
/// @param row_index Index of row. 
/// @param new_row New values of single row. 

template <class Type>
void Matrix<Type>::set_row(int row_index, const Vector<Type>& new_row) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(row_index >= rows_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "set_row(int, const Vector<Type>&) const method." << std::endl
                << "Index must be less than number of rows." << std::endl;

      exit(1);
   }

   int size = new_row.get_size();

   if(size != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "set_row(int, const Vector<Type>&) const method." << std::endl
                << "Size must be equal to number of columns." << std::endl;

      exit(1);
   }

   #endif

   // Set new row

   for(int i = 0; i < columns_number; i++)
   {
      data[row_index][i] = new_row[i];
   }
}


// void set_column(int, const Vector<Type>&) const method

/// This method sets new values of a single column in the matrix. 
/// @param column_index Index of column. 
/// @param new_column New values of single column. 

template <class Type>
void Matrix<Type>::set_column(int column_index, const Vector<Type>& new_column) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(column_index >= columns_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "set_column(int, const Vector<Type>&) const." << std::endl
                << "Index must be less than number of columns." << std::endl;

      exit(1);
   }

   int size = new_column.get_size();

   if(size != rows_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "set_column(int, const Vector<Type>&) const." << std::endl
                << "Size must be equal to number of rows." << std::endl;

      exit(1);
   }

   #endif

   // Set new column

   for(int i = 0; i < rows_number; i++)
   {
      data[i][column_index] = new_column[i];
   }
}


// void add_row(const Vector<Type>&) const method

/// This method appends a new row to the matrix. 
/// The size of the row vector must be equal to the number of columns of the matrix.
/// Note that resizing is necessary here and therefore this method can be very inefficient. 
/// @param new_row Row to be appended.

template <class Type>
void Matrix<Type>::add_row(const Vector<Type>& new_row)
{
   #ifdef _DEBUG 

   int size = new_row.get_size();

   if(size != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "add_row(const Vector<Type>&) const." << std::endl
                << "Size must be equal to number of columns." << std::endl;

      exit(1);
   }

   #endif

   resize(rows_number+1, columns_number);

   set_row(rows_number-1, new_row);
}


// void add_column(const Vector<Type>&) const method

/// This method appends a new column to the matrix. 
/// The size of the column vector must be equal to the number of rows of the matrix.
/// Note that resizing is necessary here and therefore this method can be very inefficient. 
/// @param new_column Column to be appended.

template <class Type>
void Matrix<Type>::add_column(const Vector<Type>& new_column) 
{
   #ifdef _DEBUG 

   int size = new_column.get_size();

   if(size != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "add_column(const Vector<Type>&) const." << std::endl
                << "Size must be equal to number of columns." << std::endl;

      exit(1);
   }

   #endif

   resize(rows_number, columns_number+1);

   set_column(columns_number-1, new_column);
}


// void subtract_row(int) const method

/// This method removes the row with given index. 
/// Note that resizing is here necessary and this method can be very inefficient. 
/// @param row_index Index of row to be removed. 

template <class Type>
void Matrix<Type>::subtract_row(int row_index) 
{
   #ifdef _DEBUG 

   if(row_index < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "subtract_row(int) const." << std::endl
                << "Index of row must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(row_index >= rows_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "subtract_row(int) const." << std::endl
                << "Index of row must be less than number of rows." << std::endl;

      exit(1);
   }
   else if(rows_number < 2)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "subtract_row(int) const." << std::endl
                << "Number of rows must be equal or greater than two." << std::endl;

      exit(1);  
   }

   #endif

   Matrix<Type> new_matrix(rows_number-1, columns_number);

   for(int i = 0; i < row_index; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
        new_matrix[i][j] = data[i][j];
      }
   }

   for(int i = row_index+1; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         new_matrix[i-1][j] = data[i][j];
      }
   }

   *this = new_matrix;
}


// void subtract_column(int) method

/// This method removes the column with given index. 
/// Note that resizing is here necessary and this method can be very inefficient. 
/// @param column_index Index of column to be removed. 

template <class Type>
void Matrix<Type>::subtract_column(int column_index)
{
   #ifdef _DEBUG 

   if(column_index < 0)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "subtract_column(int) const." << std::endl
                << "Index of column must be equal or greater than zero." << std::endl;

      exit(1);
   }
   else if(column_index >= columns_number)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "subtract_column(int) const." << std::endl
                << "Index of column must be less than number of columns." << std::endl;

      exit(1);
   }
   else if(columns_number < 2)
   {
      std::cerr << "Flood Error: Matrix Template. " << std::endl
                << "subtract_column(int) const." << std::endl
                << "Number of columns must be equal or greater than two." << std::endl;

      exit(1);  
   }

   #endif

   Matrix<Type> new_matrix(rows_number, columns_number-1);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < column_index; j++)
      {
        new_matrix[i][j] = data[i][j];
      }
   }

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = column_index+1; j < columns_number; j++)
      {
         new_matrix[i][j-1] = data[i][j];
      }
   }

   *this = new_matrix;
}


// void initialize(const Type&) const method

/// This method initializes all the elements of the matrix with a given value.
/// @param value Type value.

template <class Type>
void Matrix<Type>::initialize(const Type& value) const
{
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = value;
      }
   }
}


// void initialize_uniform(void) method

/// This method initializes all the elements in the matrix with random values comprised between -1 and 1.

template <class Type>
void Matrix<Type>::initialize_uniform(void)
{
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_uniform(-1.0, 1.0);
      }
   }
}


// void initialize_uniform(double, double) method

/// This method initializes all the elements in the matrix with random values comprised between a minimum and a maximum
/// values.
/// @param minimum Minimum possible value. 
/// @param maximum Maximum possible value. 

template <class Type>
void Matrix<Type>::initialize_uniform(double minimum, double maximum)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(minimum > maximum)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void initialize_uniform(double, double) method." << std::endl
                << "Minimum value must be less or equal than maximum value." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_uniform(minimum, maximum);
      }
   }
}


// void initialize_uniform(const Matrix<double>&, const Matrix<double>&) method

/// This method initializes all the elements in the matrix with random values comprised between a minimum and a maximum
/// values for each element.
/// @param minimum Minimum possible values. 
/// @param maximum Maximum possible values. 

template <class Type>
void Matrix<Type>::initialize_uniform(const Matrix<double>& minimum, const Matrix<double>& maximum) 
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(minimum > maximum)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void initialize_uniform(const Matrix<double>&, const Matrix<double>&) method."
                << std::endl
                << "Minimum values must be less or equal than their respective maximum values." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_uniform(minimum[i][j], maximum[i][j]);
      }
   }
}


// void initialize_normal(void) method

/// This method assigns random values to each element in the matrix, taken from a normal distribution with
/// mean 0 and standard deviation 1. 

template <class Type>
void Matrix<Type>::initialize_normal(void)
{
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_normal(0.0, 1.0);
      }
   }
}


// void initialize_normal(double, double) method

/// This method assigns random values to each element in the matrix, taken from a normal distribution with
/// a given mean and a given standard deviation. 
/// @param mean Mean value of uniform distribution.  
/// @param standard_deviation Standard deviation value of uniform distribution.

template <class Type>
void Matrix<Type>::initialize_normal(double mean, double standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(standard_deviation < 0.0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void initialize_normal(double, double) method." << std::endl
                << "Standard deviation must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_normal(mean, standard_deviation);
      }
   }
}


// void initialize_normal(const Matrix<double>&, const Matrix<double>&) method

/// This method assigns random values to each element in the vector, taken from normal distributions with
/// given means and standard deviations for each element. 
/// @param mean Mean values of uniform distributions.  
/// @param standard_deviation Standard deviation values of uniform distributions.

template <class Type>
void Matrix<Type>::initialize_normal(const Matrix<double>& mean, const Matrix<double>& standard_deviation)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(standard_deviation < 0.0)
   { 
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "void initialize_normal(const Matrix<double>&, const Matrix<double>&) method."
                << std::endl
                << "Standard deviations must be equal or greater than zero." << std::endl;

       exit(1);
   }

   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_uniform(mean[i][j], standard_deviation[i][j]);
      }
   }
}


// void set_to_identity(void) const method

/// This method sets the diagonal elements in the matrix with ones and the rest elements with zeros. The matrix 
/// must be square. 

template <class Type>
void Matrix<Type>::set_to_identity(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(rows_number != columns_number)
   {
      std::cout << "Flood Error: Matrix Template." << std::endl
                << "set_to_identity(void) const method." << std::endl
                << "Matrix must be square." << std::endl;
      
      exit(1);
   }

   #endif

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(i==j)
         {
            data[i][j] = 1;
         }
         else
         {
            data[i][j] = 0;      
         }
      }
   }
}


// Vector<double> calculate_mean_standard_deviation(void) const method

/// This method returns a vector of vectors with the mean and standard deviation values of all the matrix columns. 
/// The size of the vector is two.
/// The size of each element is equal to the number of columns in the matrix. 

template <class Type>
Vector< Vector<double> > Matrix<Type>::calculate_mean_standard_deviation(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "Vector<double> calculate_mean_standard_deviation(void) const method." << std::endl 
                << "Number of rows must be greater than one." << std::endl;

      exit(1);
   }

   #endif

   // Mean 

   Vector<double> mean(columns_number, 0.0);

   for(int j = 0; j < columns_number; j++)
   {
      mean[j] = 0.0;

      for(int i = 0; i < rows_number; i++)
      {
         mean[j] += data[i][j];
      }

      mean[j] /= (double)rows_number;
   }

   // Standard deviation

   Vector<double> standard_deviation(columns_number, 0.0);

   for(int j = 0; j < columns_number; j++)
   {
      standard_deviation[j] = 0.0;

      for(int i = 0; i < rows_number; i++)
      {
         standard_deviation[j] += (data[i][j] - mean[j])*(data[i][j] - mean[j]);
      }

      standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
   }

   // Mean and standard deviation of input data

   Vector< Vector<double> > mean_standard_deviation(2);

   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Vector<double> calculate_mean_standard_deviation(const Vector<int>&) const method

/// This method returns a vector of vectors with the mean and standard deviation values of given columns. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param column_indices Indices of columns.  

template <class Type>
Vector< Vector<double> > Matrix<Type>::calculate_mean_standard_deviation(const Vector<int>& column_indices) const
{
   int column_indices_size = column_indices.get_size();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(column_indices_size < 0)
   {
	   std::cerr << "Flood Error: Matrix template." << std::endl
                << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&) const method." 
                << std::endl 
                << "Size of column indices must be equal or greater than zero." << std::endl;

      exit(1);
   }

   #endif

   int column_index;

   // Mean 

   Vector<double> mean(column_indices_size, 0.0);

   for(int j = 0; j < column_indices_size; j++)
   {
      column_index = column_indices[j];

      mean[j] = 0.0;  

      for(int i = 0; i < rows_number; i++)
      {
         mean[j] += data[i][column_index];
      }

      mean[j] /= (double)rows_number;
   }

   // Standard deviation

   Vector<double> standard_deviation(column_indices_size, 0.0);

   for(int j = 0; j < column_indices_size; j++)
   {
      column_index = column_indices[j];

      standard_deviation[j] = 0.0;

      for(int i = 0; i < rows_number; i++)
      {
         standard_deviation[j] += (data[i][column_index] - mean[j])*(data[i][column_index] - mean[j]);
      }

      standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
   }

   // Mean and standard deviation

   Vector< Vector<double> > mean_standard_deviation(2);

   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method

/// This method returns a vector of vectors with the mean and standard deviation values of given columns for given rows. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param row_indices Indices of rows.  
/// @param column_indices Indices of columns.  

template <class Type>
Vector< Vector<double> > Matrix<Type>::
calculate_mean_standard_deviation(const Vector<int>& row_indices, const Vector<int>& column_indices) const
{
   int row_indices_size = row_indices.get_size();
   int column_indices_size = column_indices.get_size();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   // Rows check

   if(row_indices_size > rows_number)
   {
	  std::cerr << "Flood Error: Matrix template." << std::endl
                << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method." << std::endl 
                << "Row indices size must be equal or less than rows number." << std::endl;

      exit(1);
   }

   for(int i = 0; i < row_indices_size; i++)
   {
      if(row_indices[i] < 0)
	  {
   	     std::cerr << "Flood Error: Matrix template." << std::endl
                   << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method." << std::endl 
                   << "Row index " << i << " must be equal or greater than zero." << std::endl;

         exit(1); 
	  }
      if(row_indices[i] >= rows_number)
	  {
   	     std::cerr << "Flood Error: Matrix template." << std::endl
                   << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method." << std::endl 
                   << "Row index " << i << " must be less than rows number." << std::endl;

         exit(1); 
	  }  
   }

   if(row_indices_size == 0)
   {
	  std::cerr << "Flood Error: Matrix template." << std::endl
                << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method." << std::endl 
                << "Size of row indices must be greater than zero." << std::endl;

      exit(1);
   }

   // Columns check

   if(column_indices_size > columns_number)
   {
	  std::cerr << "Flood Error: Matrix template." << std::endl
                << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method." << std::endl 
                << "Column indices size must be equal or less than columns number." << std::endl;

      exit(1);
   }

   for(int i = 0; i < column_indices_size; i++)
   {
      if(column_indices[i] < 0)
	  {
   	     std::cerr << "Flood Error: Matrix template." << std::endl
                   << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method." << std::endl 
                   << "Column index " << i << " must be equal or greater than zero." << std::endl;

         exit(1); 
	  }
      if(column_indices[i] >= columns_number)
	  {
   	     std::cerr << "Flood Error: Matrix template." << std::endl
                   << "Vector<double> calculate_mean_standard_deviation(const Vector<int>&, const Vector<int>&) const method." << std::endl 
                   << "Column index " << i << " must be less than columns number." << std::endl;

         exit(1); 
	  }  
   }

   #endif

   int row_index;
   int column_index;

   // Mean 

   Vector<double> mean(column_indices_size, 0.0);

   for(int j = 0; j < column_indices_size; j++)
   {
	  column_index = column_indices[j];
	   
	  mean[j] = 0.0;    

      for(int i = 0; i < row_indices_size; i++)
      {
         row_index = row_indices[i];

         mean[j] += data[row_index][column_index];
      }

      mean[j] /= (double)rows_number;
   }

   // Standard deviation

   Vector<double> standard_deviation(column_indices_size, 0.0);

   for(int j = 0; j < column_indices_size; j++)
   {
	  column_index = column_indices[j];
   
      standard_deviation[j] = 0.0;

      for(int i = 0; i < row_indices_size; i++)
      {
         row_index = row_indices[i];

         standard_deviation[j] += (data[row_index][column_index] - mean[j])*(data[row_index][column_index] - mean[j]);
      }

      standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
   }

   // Mean and standard deviation

   Vector< Vector<double> > mean_standard_deviation(2);

   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Vector< Vector<Type> > calculate_minimum_maximum(void) const method

/// This method returns a vector of vectors with the minimum and maximum values of all the matrix columns. 
/// The size of the vector is two.
/// The size of each element is equal to the number of columns in the matrix. 

template <class Type>
Vector< Vector<Type> > Matrix<Type>::calculate_minimum_maximum(void) const
{
   Vector< Vector<Type> > minimum_maximum(2);

   Vector<Type> minimum(columns_number,  1.0e99);
   Vector<Type> maximum(columns_number, -1.0e99);

   for(int j = 0; j < columns_number; j++)
   {
      for(int i = 0; i < rows_number; i++)
      {    
         if(data[i][j] < minimum[j])
         {
            minimum[j] = data[i][j];
         }

         if(data[i][j] > maximum[j])
         {
            maximum[j] = data[i][j];
         }
      }
   }

   // Minimum and maximum

   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// Vector<double> calculate_minimum_maximum(const Vector<int>&) const method

/// This method returns a vector of vectors with the minimum and maximum values of given columns. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param column_indices Indices of columns.  

template <class Type>
Vector< Vector<Type> > Matrix<Type>::calculate_minimum_maximum(const Vector<int>& column_indices) const
{
   int size = column_indices.get_size();

   #ifdef _DEBUG 

   for(int i = 0; i < size; i++)
   {      
      if(column_indices[i] < 0)
      {
         std::cerr << "Flood Error: Matrix template." 
                   << "Vector<Type> calculate_minimum_maximum(const Vector<int>&) const method." << std::endl 
                   << "Index of column must be equal or greater than zero." << std::endl;

         exit(1);
      }
      else if(column_indices[i] >= columns_number)
      {
         std::cerr << "Flood Error: Matrix template." 
                   << "Vector<Type> calculate_minimum_maximum(const Vector<int>&) const method." << std::endl 
                   << "Index of column must be less than number of columns." << std::endl;

         exit(1);
      }
   }   

   #endif

   int column_index;

   Vector<Type> minimum(size,  1.0e99);
   Vector<Type> maximum(size, -1.0e99);

   for(int j = 0; j < size; j++)
   {
      column_index = column_indices[j];

      for(int i = 0; i < rows_number; i++)
      {    
         if(data[i][column_index] < minimum[j])
         {
            minimum[j] = data[i][column_index];
         }

         if(data[i][column_index] > maximum[j])
         {
            maximum[j] = data[i][column_index];
         }
      }
   }

   // Minimum and maximum

   Vector< Vector<Type> > minimum_maximum(2);

   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// Vector<double> calculate_minimum_maximum(const Vector<int>&, const Vector<int>&) const method

/// This method returns a vector of vectors with the minimum and maximum values of given columns for given rows. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param row_indices Indices of rows.  
/// @param column_indices Indices of columns.  

template <class Type>
Vector< Vector<Type> > Matrix<Type>::
calculate_minimum_maximum(const Vector<int>& row_indices, const Vector<int>& column_indices) const
{
   int row_indices_size = row_indices.get_size();
   int column_indices_size = column_indices.get_size();

   Vector<Type> minimum(column_indices_size,  1.0e99);
   Vector<Type> maximum(column_indices_size, -1.0e99);

   int row_index;
   int column_index;

   for(int j = 0; j < column_indices_size; j++)
   {
      column_index = column_indices[j];

      for(int i = 0; i < row_indices_size; i++)
      {    
         row_index = row_indices[i];

         if(data[row_index][column_index] < minimum[j])
         {
            minimum[j] = data[row_index][column_index];
         }

         if(data[row_index][column_index] > maximum[j])
         {
            maximum[j] = data[row_index][column_index];
         }
      }
   }

   // Minimum and maximum

   Vector< Vector<Type> > minimum_maximum(2);

   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// void scale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method scales the matrix elements with given mean and standard deviation values. 
/// It updates the data in the matrix.
/// The size of the mean and standard deviation vectors must be equal to the number of columns in the matrix. 
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.

template <class Type>
void Matrix<Type>::scale_mean_standard_deviation(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   #ifdef _DEBUG 

   int mean_size = mean.get_size();

   if(mean_size != columns_number)
   {
      std::cerr << "Flood Error: Matrix template." 
                << "void scale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of mean vector must be equal to number of columns." << std::endl;

      exit(1);
   }

   int standard_deviation_size = standard_deviation.get_size();

   if(standard_deviation_size != columns_number)
   {
     std::cerr << "Flood Error: Matrix template." 
               << "void scale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of standard deviation vector must be equal to number of columns." << std::endl;

      exit(1);
   }   

   #endif

   // Rescale data

   for(int j = 0; j < columns_number; j++)
   {
      if(standard_deviation[j] < 1e-99)
      {
         if(display)
		 {
            std::cout << "Flood Warning: Matrix class." << std::endl
                      << "void scale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl
                      << "Standard deviation of column " << j << " is zero." << std::endl
                      << "Those values won't be scaled." << std::endl;
		 }

         // Do nothing
      }
      else
      {
         for(int i = 0; i < rows_number; i++)
         {
            data[i][j] = (data[i][j] - mean[j])/standard_deviation[j];
         }
      }
   }
}


// void scale_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method scales the matrix elements with given minimum and maximum values. 
/// It updates the data in the matrix.
/// The size of the minimum and maximum vectors must be equal to the number of columns in the matrix. 
/// @param minimum Minimum values.
/// @param maximum Maximum values.

template <class Type>
void Matrix<Type>::scale_minimum_maximum(const Vector<double>& minimum, const Vector<double>& maximum)
{
   #ifdef _DEBUG 

   int minimum_size = minimum.get_size();

   if(minimum_size != columns_number)
   {
      std::cerr << "Flood Error: Matrix template." 
                << "void scale_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of minimum vector must be equal to number of columns." << std::endl;

      exit(1);
   }

   int maximum_size = maximum.get_size();

   if(maximum_size != columns_number)
   {
     std::cerr << "Flood Error: Matrix template." 
               << "void scale_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of maximum vector must be equal to number of columns." << std::endl;

      exit(1);
   }   

   #endif

   // Rescale data

   for(int j = 0; j < columns_number; j++)
   {
      if(maximum[j] - minimum[j] < 1e-99)
      {
         if(display)
		 {
            std::cout << "Flood Warning: Matrix class." << std::endl
                      << "void scale_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl
                      << "Minimum and maximum values of column " << j << " are equal." << std::endl
                      << "Those values won't be scaled." << std::endl;
		 }

         // Do nothing
      }
      else
      {
         for(int i = 0; i < rows_number; i++)
         {
            data[i][j] = 2.0*(data[i][j] - minimum[j])/(maximum[j]-minimum[j])-1.0;
         }
      }
   }
}


// void unscale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method unscales the matrix elements with given mean and standard deviation values. 
/// It updates the matrix elements.
/// The size of the mean and standard deviation vectors must be equal to the number of columns in the matrix. 
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.

template <class Type>
void Matrix<Type>::unscale_mean_standard_deviation(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   #ifdef _DEBUG 

   int mean_size = mean.get_size();

   if(mean_size != columns_number)
   {
      std::cerr << "Flood Error: Matrix template." 
                << "void unscale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of mean vector must be equal to number of columns." << std::endl;

      exit(1);
   }

   int standard_deviation_size = standard_deviation.get_size();

   if(standard_deviation_size != columns_number)
   {
	   std::cerr << "Flood Error: Matrix template." << std::endl
                 << "void unscale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                 << "Size of standard deviation vector must be equal to number of columns." << std::endl;

      exit(1);
   }   

   #endif

   for(int j = 0; j < columns_number; j++)
   {
      if(standard_deviation[j] < 1e-99)
      {
         if(display)
         {                                          
            std::cout << "Flood Warning: Matrix template." << std::endl
                      << "void unscale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method." << std::endl 
                      << "Standard deviation of column variable " << j << " is zero." << std::endl
                      << "Those columns won't be scaled." << std::endl;
         }

         // Do nothing
      }
      else
      {
         for(int i = 0; i < rows_number; i++)
         {
            data[i][j] = data[i][j]*standard_deviation[j] + mean[j];
         }
      }
   }
}


// void unscale_minimum_maximum(const Vector<double>&, const Vector<double>&) method

/// This method unscales the matrix elements with given minimum and maximum values. 
/// It updates the matrix elements.
/// The size of the minimum and maximum vectors must be equal to the number of columns in the matrix. 
/// @param minimum Minimum values.
/// @param maximum Maximum deviation values.

template <class Type>
void Matrix<Type>::unscale_minimum_maximum(const Vector<double>& minimum, const Vector<double>& maximum)
{
   #ifdef _DEBUG 

   int minimum_size = minimum.get_size();

   if(minimum_size != columns_number)
   {
      std::cerr << "Flood Error: Matrix template." 
                << "void unscale_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl 
                << "Size of minimum vector must be equal to number of columns." << std::endl;

      exit(1);
   }

   int maximum_size = maximum.get_size();

   if(maximum_size != columns_number)
   {
     std::cerr << "Flood Error: Matrix template." 
               << "void unscale_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl 
               << "Size of maximum vector must be equal to number of columns." << std::endl;

      exit(1);
   }   

   #endif

   for(int j = 0; j < columns_number; j++)
   {
      if(maximum[j] - minimum[j] < 1e-99)
      {
         if(display)
         {
            std::cout << "Flood Warning: Matrix template." << std::endl
                      << "void unscale_minimum_maximum(const Vector<double>&, const Vector<double>&) method." << std::endl 
                      << "Minimum and maximum values of column " << j << " are equal." << std::endl
                      << "Those columns won't be unscaled." << std::endl;
         }

         // Do nothing
      }
      else
      {
         for(int i = 0; i < rows_number; i++)
         {
            data[i][j] = 0.5*(data[i][j] + 1.0)*(maximum[j]-minimum[j]) + minimum[j]; 
         }
      }
   }
}


// Matrix<Type> calculate_transpose(void) const method

/// This method returns the transpose of the matrix. 

template <class Type>
Matrix<Type> Matrix<Type>::calculate_transpose(void) const
{
   Matrix<Type> transpose(columns_number, rows_number);

   for(int i = 0; i < columns_number; i++)
   {
      for(int j = 0; j < rows_number; j++)
      {
         transpose[i][j] = data[j][i];
      }     
   }

   return(transpose);
}


// Type calculate_determinant(void) const method

/// This method returns the determinant of a square matrix. 

template <class Type>
Type Matrix<Type>::calculate_determinant(void) const
{ 
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(rows_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl
                << "calculate_determinant(void) const method." << std::endl
                << "Matrix must be square." << std::endl;
      
      exit(1);
   }

   #endif

   Type determinant = 0;
   
   if(rows_number == 0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl
                << "calculate_determinant(void) const method." << std::endl
                << "Size of matrix is zero." << std::endl;
      
      exit(1);                   
   }
   else if(rows_number == 1)
   {
      determinant = data[0][0];                   
   }
   else if(rows_number == 2)
   {
      determinant = data[0][0]*data[1][1] - data[1][0]*data[0][1];
   }
   else
   {
      int sign;

      for(int row_index = 0; row_index < rows_number; row_index++) 
      {
         // Calculate sub data
 
         Matrix<Type> sub_matrix(rows_number-1, columns_number-1);     
     
         for(int i = 1; i < rows_number; i++) 
         {
            int j2 = 0;
      
            for(int j = 0; j < columns_number; j++) 
            {
               if(j == row_index)
               {
                  continue;
               }

               sub_matrix[i-1][j2] = data[i][j];

               j2++;
            }
         }

         sign = (int)(pow(-1.0, row_index+2.0));
       
         determinant += sign*data[0][row_index]*sub_matrix.calculate_determinant();    
      }
   }
     
   return(determinant);
}


// Matrix<Type> calculate_cofactor(void) const method

/// This method returns the cofactor matrix.

template <class Type>
Matrix<Type> Matrix<Type>::calculate_cofactor(void) const
{
   Matrix<double> cofactor(rows_number, columns_number);
                  
   Matrix<double> c(rows_number-1, columns_number-1);

   for(int j = 0; j < rows_number; j++) 
   {
      for(int i = 0; i < rows_number; i++) 
      {
         // Form the adjoint a[i][j]

         int i1 = 0;

         for(int ii = 0; ii < rows_number; ii++) 
         {
            if(ii == i)
            {
               continue;
            }
            
            int j1 = 0;

            for(int jj = 0; jj < rows_number; jj++) 
            {
               if(jj == j)
               {
                  continue;
               }

               c[i1][j1] = data[ii][jj];
               j1++;
            }
            i1++;
         }

         double determinant = c.calculate_determinant();

         cofactor[i][j] = pow(-1.0, i+j+2.0)*determinant;
      }
   }

   return(cofactor);
}


// Matrix<Type> calculate_inverse(void) const method

/// This method returns the inverse of a square matrix.
/// An error message is printed if the matrix is singular.

template <class Type>
Matrix<Type> Matrix<Type>::calculate_inverse(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
   
   if(rows_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl
                << "calculate_inverse(void) const method." << std::endl
                << "Matrix must be square." << std::endl;
      
      exit(1);
   }

   #endif

   double determinant = calculate_determinant();

   if(determinant == 0.0)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl
                << "calculate_inverse(void) const method." << std::endl
                << "Matrix is singular." << std::endl;
      
      exit(1);
   }
   
   // Calculate cofactor matrix
   
   Matrix<double> cofactor = calculate_cofactor();

   // Adjoint matrix is the transpose of cofactor matrix

   Matrix<double> adjoint = cofactor.calculate_transpose();
   
   // Inverse matrix is adjoint matrix divided by matrix determinant

   Matrix<double> inverse = adjoint/determinant;

   return(inverse);
}


// Matrix<Type> operator + (const Type&) const method

/// Sum matrix+scalar arithmetic operator. 
/// @param scalar Scalar value to be added to this vector.

template <typename Type>
Matrix<Type> Matrix<Type>::operator + (const Type& scalar) const
{
   Matrix<Type> sum(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         sum[i][j] = data[i][j] + scalar;    
      }     
   }

   return(sum);
}


// Matrix<Type> operator + (const Matrix<Type>&) const method

/// Sum matrix+matrix arithmetic operator. 
/// @param other_matrix Matrix to be added to this vector.

template <typename Type>
Matrix<Type> Matrix<Type>::operator + (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();    
   int other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "Matrix<Type> operator + (const Matrix<Type>&) const." << std::endl
                << "Both matrix sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif

   Matrix<Type> sum(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         sum[i][j] = data[i][j] + other_matrix[i][j];    
      }     
   }

   return(sum);
}


// Matrix<Type> operator - (const Type&) const method

/// Difference matrix-scalar arithmetic operator. 
/// @param scalar Scalar value to be subtracted to this matrix.

template <typename Type>
Matrix<Type> Matrix<Type>::operator - (const Type& scalar) const
{
   Matrix<Type> difference(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         difference[i][j] = data[i][j] - scalar;    
      }     
   }

   return(difference);
}


// Matrix<Type> operator - (const Matrix<Type>&) const method 

/// Difference matrix-matrix arithmetic operator. 
/// @param other_matrix Matrix to be subtracted to this matrix.

template <typename Type>
Matrix<Type> Matrix<Type>::operator - (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();    
   int other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "Matrix<Type> operator - (const Matrix<Type>&) const method." << std::endl
                << "Both matrix sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif

   Matrix<Type> difference(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         difference[i][j] = data[i][j] - other_matrix[i][j];    
      }     
   }

   return(difference);
}


// Matrix<Type> operator * (const Type&) const method

/// Product matrix*scalar arithmetic operator. 
/// @param scalar Scalar value to be multiplied to this matrix.

template <typename Type>
Matrix<Type> Matrix<Type>::operator * (const Type& scalar) const
{
   Matrix<Type> product(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
          product[i][j] = data[i][j]*scalar;     
      }      
   }

   return(product);
}


// Matrix<Type> operator * (const Matrix<Type>&) const  method

/// Product matrix+matrix arithmetic operator. 
/// @param other_matrix Matrix to be multiplied to this vector.

template <typename Type>
Matrix<Type> Matrix<Type>::operator * (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();    
   int other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "Matrix<Type> operator * (const Matrix<Type>&) const method." << std::endl
                << "Both matrix sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif

   Matrix<Type> product(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         product[i][j] = data[i][j]*other_matrix[i][j];    
      }     
   }

   return(product);
}


// Matrix<Type> operator / (const Type&) const method

/// Cocient Matrix/scalar arithmetic operator. 
/// @param scalar Value of scalar. 

template <typename Type>
Matrix<Type> Matrix<Type>::operator / (const Type& scalar) const
{
   Matrix<Type> cocient(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         cocient[i][j] = data[i][j]/scalar;     
      }      
   }

   return(cocient);
}


// Matrix<Type> operator / (const Matrix<Type>&) const  method

/// Cocient matrix/matrix arithmetic operator. 
/// @param other_matrix Matrix to be divided to this vector.

template <typename Type>
Matrix<Type> Matrix<Type>::operator / (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int other_rows_number = other_matrix.get_rows_number();    
   int other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "Matrix<Type> operator / (const Matrix<Type>&) const method." << std::endl
                << "Both matrix sizes must be the same." << std::endl;

      exit(1);          
   }

   #endif

   Matrix<Type> cocient(rows_number, columns_number);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         cocient[i][j] = data[i][j]/other_matrix[i][j];    
      }     
   }

   return(cocient);
}


// Vector<Type> dot(const Vector<Type>&) const method

/// This method returns the dot product of this matrix with a vector.
/// The size of the vector must be equal to the number of columns of the matrix.
/// @param vector Vector to be multiplied to this matrix.

template <typename Type>
Vector<Type> Matrix<Type>::dot(const Vector<Type>& vector) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
       
   int size = vector.get_size();

   if(size != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "Vector<Type> dot(const Vector<Type>&) const method." << std::endl
                << "Vector size must be equal to matrix number of columns." << std::endl;

      exit(1);          
   }

   #endif

   // Calculate matrix-vector poduct   
      
   Vector<Type> product(rows_number);

   for(int i = 0; i < rows_number; i++)
   {     
      product[i] = 0;      

      for(int j = 0; j < columns_number; j++)
      {
         product[i] += vector[j]*data[i][j];
      }
   }

   return(product);
}


// Matrix<Type> dot(const Matrix<Type>&) const method

/// This method returns the dot product of this matrix with another matrix. 
///
/// @param other_matrix Matrix to be multiplied to this matrix.

template <typename Type>
Matrix<Type> Matrix<Type>::dot(const Matrix<Type>& other_matrix) const
{
   int other_columns_number = other_matrix.get_columns_number();    

   // Control sentence (if debug)

   #ifdef _DEBUG 
       
//   int other_rows_number = other_matrix.get_rows_number();

   #endif

   Matrix<Type> product(rows_number, other_columns_number, 0.0);

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < other_columns_number; j++)
      { 
         for(int k = 0; k < columns_number; k++)
         {
             product[i][j] += data[i][k]*other_matrix[k][j];
         }
      }
   }

   return(product);
}


// bool is_symmetric(void) const method

/// This method returns true if this matrix is symmetric.
/// A symmetric matrix is a squared matrix which is equal to its transpose.

template <typename Type>
bool Matrix<Type>::is_symmetric(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
       
   if(rows_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool is_symmetric(void) const method." << std::endl
                << "Matrix must be squared." << std::endl;

      exit(1);          
   }

   #endif

   Matrix<Type> transpose = calculate_transpose();

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(data[i][j] != transpose[i][j])
         {
            return(false);
         }
      }
   }

   return(true);
}


// bool is_antisymmetric(void) const method

/// This method returns true if this matrix is antysymmetric.
/// A symmetric matrix is a squared matrix which its opposed is equal to its transpose.
//@todo
template <typename Type>
bool Matrix<Type>::is_antisymmetric(void) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 
       
   if(rows_number != columns_number)
   {
      std::cerr << "Flood Error: Matrix Template." << std::endl 
                << "bool is_antisymmetric(void) const method." << std::endl
                << "Matrix must be squared." << std::endl;

      exit(1);          
   }

   #endif

   Matrix<Type> transpose = calculate_transpose();

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         if(i != j && -data[i][j] != transpose[i][j])
         {
            return(false);
         }
      }
   }

   return(true);
}


/// This method re-writes the input operator >> for the Vector template. 
///
/// @param is Input stream.
/// @param m Input matrix.

template<typename Type>
std::istream& operator >> (std::istream& is, Matrix<Type>& m) 
{
   int rows_number = m.get_rows_number();
   int columns_number = m.get_columns_number();

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         is >> m[i][j];
      }     
   }

   return(is);
}


// Output operator

/// This method re-writes the output operator << for the Vector template. 
///
/// @param os Output stream.
/// @param m Output matrix.

template<typename Type>
std::ostream& operator << (std::ostream& os, Matrix<Type>& m) 
{
   int rows_number = m.get_rows_number();
   int columns_number = m.get_columns_number();
   
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         os << m[i][j] << " ";
      }     

      os << std::endl;
   }

   return(os);
}


// std::string to_XML(bool) method

/// @param show_declaration True if an XML-type declaration is to be included at the beginning.

template <class Type>
std::string Matrix<Type>::to_XML(bool show_declaration)
{
   std::stringstream buffer;

   // Header     
   
   if(show_declaration)
   {
      buffer << "<Flood version='3.0' class='Matrix'>" << std::endl;
   }

   // Number of rows

   buffer << "<RowsNumber>" << std::endl
          << rows_number << std::endl
          << "</RowsNumber>" << std::endl;

   // Number of columns

   buffer << "<ColumnsNumber>" << std::endl
          << columns_number << std::endl
          << "</ColumnsNumber>" << std::endl;

   // Display

   buffer << "<Display>" << std::endl
          << display << std::endl
          << "</Display>" << std::endl;

   // Data

   buffer << "<Data>" << std::endl;

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         buffer << data[i][j] << " ";
      }     
      buffer << std::endl;
   }

   buffer << "</Data>" << std::endl;

   return(buffer.str());
}


// void print(void) method

/// This method prints to the screen in XML-type format the members of the matrix object. 

template <class Type>
void Matrix<Type>::print(void)
{
   std::cout << to_XML(true);
}


// void print_data(void) method

/// This method prints to the screen the matrix elements. 

template <class Type>
void Matrix<Type>::print_data(void)
{
   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
		  std::cout << data[i][j] << " ";
      }     
	  std::cout << std::endl;
   }
}


// void load(const char*) method

/// This method loads the numbers of rows and columns and the values of the matrix from a XML-type file. 
///
/// @param filename Filename.

template <class Type>
void Matrix<Type>::load(const char* filename)
{
   std::fstream file;

   // Open file
    
   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void load(const char*) method." << std::endl
                << "Cannot open matrix XML-type file."  << std::endl;

      exit(1);
   }

   // Read file

   std::string line;
   std::string word;

   // Declaration

   getline(file, line);

   if(line != "<Flood version='3.0' class='Matrix'>") 
   {
//      std::cerr << "Flood Error: Matrix template." << std::endl
//                << "void load(const char*) method." << std::endl
//				<< "Unknown file declaration: " << line << std::endl;
// 
//      exit(1);         
   }

   // Number of rows

   file >> word;

   if(word != "<RowsNumber>") 
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown rows number begin tag: " << word << std::endl;
 
      exit(1);
   }

   int new_rows_number;

   file >> new_rows_number;   

   file >> word;

   if(word != "</RowsNumber>") 
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown rows number end tag: " << word << std::endl;
 
      exit(1);
   }

   // Number of columns

   file >> word;

   if(word != "<ColumnsNumber>") 
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown columns number begin tag: " << word << std::endl;
 
      exit(1);
   }

   int new_columns_number;

   file >> new_columns_number;   

   file >> word;

   if(word != "</ColumnsNumber>") 
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void load(const char*) method." << std::endl
	       	    << "Unknown columns number end tag: " << word << std::endl;
 
      exit(1);
   }

   // Set matrix

   set(new_rows_number, new_columns_number);

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
            std::cerr << "Flood Error: Matrix template." << std::endl
                      << "void load(const char*) method." << std::endl
			      	  << "Unknown display end tag: " << word << std::endl;
 
            exit(1);
         }
	  }         
      else if(word == "<Data>") 
      {
         for(int i = 0; i < rows_number; i++)
         {
            for(int j = 0; j < columns_number; j++)
            {
	      	  file >> data[i][j];
            }     
         }
    
        file >> word;

        if(word != "</Data>") 
        {
           std::cerr << "Flood Error: Matrix template." << std::endl
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

/// This method loads the matrix data from a file. 
///
/// @param filename Filename.

template <class Type>
void Matrix<Type>::load_data(const char* filename)
{
   std::fstream file;

   // Open file
    
   file.open(filename, std::ios::in);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void load_data(const char*) method." << std::endl
                << "Cannot open data data file."  << std::endl;

      exit(1);
   }

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         file >> data[i][j];
      }     
   }

   // Close file

   file.close();
}


// void save(const char*) method

/// This method saves the numbers of rows and columns and the values of the matrix to a XML-type file. 
///
/// @param filename Filename.

template <class Type>
void Matrix<Type>::save(const char* filename)
{
   std::fstream file; 
   
   // Open file

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void save(const char*) method." << std::endl
                << "Cannot open matrix XML-type file." << std::endl;

      exit(1);
   }

   // Write file

   file << to_XML(true) << std::endl;

   // Close file

   file.close();
}


// void save_data(const char*) method

/// This method saves the the matrix data to a file. 
///
/// @param filename Filename.

template <class Type>
void Matrix<Type>::save_data(const char* filename)
{
   std::fstream file; 
   
   // Open file

   file.open(filename, std::ios::out);

   if(!file.is_open())
   {
      std::cerr << "Flood Error: Matrix template." << std::endl
                << "void save_data(const char*) method." << std::endl
                << "Cannot open matrix data file." << std::endl;

      exit(1);
   }

   // Write file

   for(int i = 0; i < rows_number; i++)
   {
      for(int j = 0; j < columns_number; j++)
      {
         file << data[i][j] << " ";
      }     
      file << std::endl;
   }

   // Close file

   file.close();
}


// double calculate_random_uniform(double, double) method

/// This method returns a random number chosen from a uniform distribution.
///
/// @param minimum Minimum value.
/// @param maximum Maximum value.

template <typename Type>
double Matrix<Type>::calculate_random_uniform(double minimum, double maximum)
{
   double random = (double)rand()/(RAND_MAX+1.0);

   double random_uniform = minimum + (maximum-minimum)*random;

   return(random_uniform);
}


// double calculate_random_normal(double, double) method

/// This method returns a random number chosen from a normal distribution.
///
/// @param mean Mean value of normal distribution.
/// @param standard_deviation Standard deviation value of normal distribution.

template <typename Type>
double Matrix<Type>::calculate_random_normal(double mean, double standard_deviation)
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
