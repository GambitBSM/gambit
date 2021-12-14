#ifndef __classes_hpp__
#define __classes_hpp__

#include <iostream>


// A dummy class
class ClassOne
{

public:

  int i;
  double d;

  // Constructor
  ClassOne() {}

  // Some method, defined in classes.cpp
  void some_method(int);

  // Some other method, defined right here
  void some_other_method(int i_in)
  {
    std::cout << "ClassOne::some_other_method: arg 1: i_in = " << i_in << std::endl;
  }

};



namespace SomeNamespace
{

  // Another dummy class
  class ClassTwo
  {
  public:
    int j;
  };

  // A dummy function that modifies a ClassTwo instance. Defined in functions.cpp.
  void modify_instance(int, ClassTwo&);

}


#endif