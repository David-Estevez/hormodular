/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   I N T E G R A T I O N   O F   F U N C T I O N S   C L A S S                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/


#include "IntegrationOfFunctions.h"

#include<iostream>

namespace Flood
{

// GENERAL CONSTRUCTOR

/// General constructor.

IntegrationOfFunctions::IntegrationOfFunctions(void)
{   

}


// DESTRUCTOR

/// Destructor.

IntegrationOfFunctions::~IntegrationOfFunctions(void)
{

}


// METHODS

// double calculate_trapezoid_integral(double (*f)(double), double, double, int) method

/// This method evaluates the integral of a function given as a pointer to a C-style function using the composite 
/// trapezoid rule with n intervals.
///
/// @param f Pointer to the C-style function to integrate.
/// @param a Lower integration limit. 
/// @param b Upper integration limit. 
/// @param n Number of intervals. 

double IntegrationOfFunctions
::calculate_trapezoid_integral(double (*f)(double), double a, double b , int n)
{
   double trapezoid_integral = 0.0;

   // Integration step

   double h = (b-a)/(n-1.0);

   // Sum

   double sum = 0.0;

   for(int i = 1; i < n; i++)
   {
      sum += f(a + i*h);
   }

   // Trapezoidal rule

   trapezoid_integral = h*(f(a)/2.0 + sum + f(b)/2.0);

   return(trapezoid_integral);
}


// double calculate_Simpson_integral(double (*f)(double), double, double, int) method

/// This method evaluates the integral of a function given as a pointer to a C-style function using the composite 
/// Simpson rule with n intervals.
///
/// @param f Pointer to the C-style function to integrate.
/// @param a Lower integration limit. 
/// @param b Upper integration limit. 
/// @param n Number of intervals. 

double IntegrationOfFunctions
::calculate_Simpson_integral(double (*f)(double), double a, double b, int n)
{
   double Simpson_integral = 0.0;

   // Integration step

   double h = (b-a)/(n-1.0);

   double sum = f(a)/3.0;

   for(int i = 1; i < n-1; i++)
   {
      if(i%2 != 0) // odd
      {
         sum += 4.0*f(a + i*h)/3.0;
      }
      else // even
      {
         sum += 2.0*f(a + i*h)/3.0;       
      }
   }

   sum += f(b)/3.0;

   // Simpson's rule

   Simpson_integral = h*sum;

   return(Simpson_integral);
}


// double calculate_trapezoid_integral(const Vector<double>&, const Vector<double>&) method

/// This method evaluates the integral of a function given as a set of n pairs of data (x,y) using the composite 
/// trapezoid rule. 
///
/// @param x Vector of x data.
/// @param y Vector of y data.

double IntegrationOfFunctions
::calculate_trapezoid_integral(const Vector<double>& x, const Vector<double>& y)
{
   // Number of integration points

   int n = x.get_size();

   // Calculate integral

   double trapezoid_integral = 0;

   for(int i = 0; i < n-1; i++)
   {
      trapezoid_integral += 0.5*(x[i+1]-x[i])*(y[i+1]+y[i]);
   }

   // Return integral value

   return(trapezoid_integral);
}


// double calculate_Simpson_integral(const Vector<double>&, const Vector<double>&) method

/// This method evaluates the integral of a function given as a set of n pairs of data (x,y) using the composite 
/// Simpson's rule. 
///
/// @param x Vector of x data.
/// @param y Vector of y data.

double IntegrationOfFunctions::calculate_Simpson_integral(const Vector<double>& x, const Vector<double>& y)
{
   double Simpson_integral = 0.0;

   // Number of integration points

   int n = x.get_size();
  
   int m = 0;

   double a = 0.0;
   double fa = 0.0;
   double b = 0.0;
   double fb = 0.0;
   double c = 0.0;
   double fc = 0.0;
   double wa = 0.0;
   double wb = 0.0;
   double wc = 0.0;
   double h = 0.0;

   double sum = 0.0;// evenSum = 0.0;
  
   if(n%2 != 0)
   { 
      m=(n-1)/2;

      for(int i = 0 ; i < m ; i++ )
      {
         a = x[2*i]; 
         b = x[2*i+1];  
         c = x[2*i+2];

         fa = y[2*i]; 
         fb = y[2*i+1]; 
         fc = y[2*i+2];
                   
         wa = (c-a)/((a-b)*(a-c))*(1.0/3.0*(a*a+c*c+a*c)-0.5*(a+c)*(b+c)+b*c);
         wb = (c-a)/((b-a)*(b-c))*(1.0/3.0*(a*a+c*c+a*c)-0.5*(a+c)*(a+c)+a*c);
         wc = (c-a)/((c-a)*(c-b))*(1.0/3.0*(a*a+c*c+a*c)-0.5*(a+c)*(a+b)+a*b);
          
         sum += wa*fa+wb*fb+wc*fc;
      }
   }
   else
   {
      m=(n-2)/2;

      for(int i = 0; i < m; i++ )
      {
         a = x[2*i]; 
         b = x[2*i+1];  
         c = x[2*i+2];

         fa = y[2*i]; 
         fb = y[2*i+1]; 
         fc = y[2*i+2];
             
         wa = (c-a)/((a-b)*(a-c))*(1.0/3.0*(a*a+c*c+a*c)-0.5*(a+c)*(b+c)+b*c);
         wb = (c-a)/((b-a)*(b-c))*(1.0/3.0*(a*a+c*c+a*c)-0.5*(a+c)*(a+c)+a*c);
         wc = (c-a)/((c-a)*(c-b))*(1.0/3.0*(a*a+c*c+a*c)-0.5*(a+c)*(a+b)+a*b);
         
	 sum += wa*fa+wb*fb+wc*fc;
      }

      // Trapezoid
       
      h = x[n-1]-x[n-2];

      sum += h*(y[n-1]+y[n-2])/2.0;          
   }
     
   Simpson_integral = sum ;

   return(Simpson_integral);
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
