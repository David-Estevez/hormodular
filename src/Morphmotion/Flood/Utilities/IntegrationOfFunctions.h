/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   I N T E G R A T I O N   O F   F U N C T I O N S   C L A S S   H E A D E R                                  */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __INTEGRATIONOFFUNCTIONS_H__
#define __INTEGRATIONOFFUNCTIONS_H__

#include "../Utilities/Vector.h"

namespace Flood
{

/// This class contains methods for numerical integration of functions. 
/// In particular it implements the trapezoid method and the Simpson's method.

class IntegrationOfFunctions 
{
   public:

   // CONSTRUCTOR

   explicit IntegrationOfFunctions(void);


   // DESTRUCTOR

   virtual ~IntegrationOfFunctions(void);


   // METHODS

   // Integration of C-style functions

   double calculate_trapezoid_integral(double (*f)(double), double, double, int);
   double calculate_Simpson_integral(double (*f)(double), double, double, int);
   
   // Integration of pairs of data (x,y)

   double calculate_trapezoid_integral(const Vector<double>&, const Vector<double>&);
   double calculate_Simpson_integral(const Vector<double>&, const Vector<double>&);

   // Integration of class member methods

   // template<class T> double calculate_trapezoid_integral(
   // T t, double (T::*f)(double), double a, double b, int n) method

   /// This method evaluates the integral of a function given as a class
   /// member method using the composite trapezoid rule with n intervals.
   ///
   /// @param t : Object constructor containing the member method to integrate.  
   /// @param f: Pointer to the member method.
   /// @param a: Lower integration limit. 
   /// @param b: Upper integration limit. 
   /// @param n: Number of intervals. 

   template<class T> 
   double calculate_trapezoid_integral(T& t, double (T::*f)(double), double a, double b, int n)
   {
      double trapezoid_integral = 0.0;

      // Integration step

      double h = (b-a)/(n-1.0);

      // Sum

      double sum = (t.*f)(a)/2.0;

      for(int i = 1; i < n-1; i++)
      {
         sum += (t.*f)(a + i*h);
      }

      sum += (t.*f)(b)/2.0;

      // Trapezoidal rule

      trapezoid_integral = h*sum;

      return(trapezoid_integral);
   }


   // template<class T> double calculate_Simpson_integral(
   // T t, double (T::*f)(double), double a, double b, int n) method

   /// This method evaluates the integral of a function given as a class
   /// member method using the composite Simpsons rule with n intervals. 
   ///
   /// @param t : Object constructor containing the member method to integrate.  
   /// @param f: Pointer to the member method.
   /// @param a: Lower integration limit. 
   /// @param b: Upper integration limit. 
   /// @param n: Number of intervals. 

   template<class T> 
   double calculate_Simpson_integral(T& t, double (T::*f)(double), double a, double b, int n)
   {
      double Simpson_integral = 0.0;

      // Integration step

      double h = (b-a)/(n-1.0);

      double sum = (t.*f)(a)/3.0;

      for(int i = 1; i < n-1; i++)
      {
         if(i%2 != 0) // odd
         {
            sum += 4.0*(t.*f)(a + i*h)/3.0;
         }
         else // even
         {
            sum += 2.0*(t.*f)(a + i*h)/3.0;       
         }
      }

      sum += (t.*f)(b)/3.0;

      // Simpson's rule

      Simpson_integral = h*sum;

      return(Simpson_integral);
   }

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
