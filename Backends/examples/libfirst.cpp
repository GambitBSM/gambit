/*
 * A dummy C++ library for testing GAMBIT backend setup 
 * 
 * \author Anders Kvellestad
 * \date 2013-03-26
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>

//
// Some global variables:
//
const int array_length = 10;
int someInt;
double someDouble;
double someArray[array_length];
std::vector<double> someVector;
bool isInitialized = false;
std::string prefix = "libfirst: ";

//
// Some functions:
//

// 'initialization'
void initialize(int a)
{
  std::cout << std::endl;
  std::cout << prefix << "This is function 'initialize'." << std::endl;
  someInt = a;
  for ( int x = 0; x < array_length; x++ ) { someArray[x] = 2.0*x; }
  someVector.push_back(1.5);
  someVector.push_back(1.6);
  isInitialized = true;
  std::cout << prefix << "Initialization done. Variable 'someInt' set to: " << someInt << std::endl;
} // end initialize


// 'calculation'
void someFunction()
{
  std::cout << std::endl;
  std::cout << prefix << "This is function 'someFunction'." << std::endl;

  if (isInitialized)
  {
    std::cout << prefix << "Will now perform a calculation..." << std::endl;
    someDouble = 3.1415*someInt;
    std::cout << prefix << "Result stored in variable 'someDouble' is: " << someDouble << std::endl;
  }
  else
  {
    std::cout << prefix << "Not initialized. Cannot perform calculation." << std::endl;
  }
} // end someFunction


// 'byRefExample'
double byRefExample (double& input)
{
  std::cout << prefix << "This is function 'byRefExample'." << std::endl;
  input = someDouble = 2.0*someInt;
  return 2.1*someInt;
}


// 'byRefExample2'
void byRefExample2 (double& input, double input2)
{
  std::cout << prefix << "This is function 'byRefExample2'." << std::endl;
  input = someDouble = 2.3*someInt + input2;
}


// return 'result'
double returnResult()
{
  std::cout << "I'm returnResult() from libfirst.so, and I'm feeling well." << std::endl;
  return someDouble;
}


// an example variadic function
double nastyExample(int count, ...)
{
  double result = 0;
  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; ++i)
  {
    result += va_arg(args, double);
  }
  va_end(args);
  return result;
}

// an example function taking a 1D array as an argument
double arrayarg_1D(double arg[10])
{
  return arg[0]*arg[9]; 
}

// an example function taking a 1D array as an argument
double arrayarg_2D(double arg[10][10])
{
  return arg[0][0]*arg[9][0]*arg[9][9]; 
}

// an example function taking a 1D array as an argument
double arrayarg_3D(double arg[10][10][10])
{
  return arg[0][0][0]*arg[9][0][0]*arg[9][9][9]; 
}
