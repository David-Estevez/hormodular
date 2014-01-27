/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   U N I T   T E S T I N G   C L A S S   H E A D E R                                                          */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __UNITTESTING_H__
#define __UNITTESTING_H__

// Flood includes

#include "Vector.h"
#include "Matrix.h"

namespace Flood
{

/// This class contains a minimal set of utilities needed for automated unit testing. 

class UnitTesting
{

public:

   // DEFAULT CONSTRUCTOR

   explicit UnitTesting(void);

   // DESTRUCTOR

   virtual ~UnitTesting(void);

   // METHODS

   // Get methods

   int get_tests_count(void);
   int get_tests_passed_count(void);
   int get_tests_failed_count(void);

   std::string& get_message(void);

   bool get_display(void);

   // Set methods

   void set_tests_count(int);
   void set_tests_passed_count(int);
   void set_tests_failed_count(int);

   void set_message(const std::string&);

   void set_display(bool);

   // Unit testing methods

   void assert_true(bool, const std::string&);
   void assert_false(bool, const std::string&);
   
   // Test case methods

   /// This method runs all the methods contained in the test case. 

   virtual void run_test_case(void) = 0;

   void print_results(void);

protected:

   /// Number of performed tests. 

   int tests_count;

   /// Number of tests which have passed the test case. 
 
   int tests_passed_count;

   /// Number of tests which have failed the test case. 

   int tests_failed_count;

   /// String with the test case information.

   std::string message;

   /// True if messages from this class are to be displayed, false otherwise. 

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
