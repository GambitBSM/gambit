#ifndef __classes_hpp__
#define __classes_hpp__

#include <iostream>
#include <vector>
#include <ctime>

// A dummy class
class ClassOne
{

public:

  int i;
  double d;
  std::vector<clock_t> my_vec_clock;

  // Constructor
  ClassOne() {}

  // Some method, defined in classes.cpp
  void some_method(int);

  // Some other method, defined right here
  void some_other_method(int i_in)
  {
    std::cout << "ClassOne::some_other_method: arg 1: i_in = " << i_in << std::endl;
  }

  // Testing methods that return vectors

  std::vector<int> return_as_vector_with_int();

  std::vector<clock_t> return_as_vector_with_clock();

};



namespace SomeNamespace
{

  // Another dummy class
  class ClassTwo
  {
  public:
    int j;
  };

}


#endif