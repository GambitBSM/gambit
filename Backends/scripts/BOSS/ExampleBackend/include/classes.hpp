#ifndef __classes_hpp__
#define __classes_hpp__

#include <iostream>
#include <vector>
#include <ctime>
#include <map> 

template <typename T> class ClassThree {
public:
  T pop();
  void push(T item);
  int size();

private:
  std::vector<T> stack;
  int curr_size;
};

template <class T>
class ClassFour {
public:
  T pop();
  void push(T item);
  int size();

private:
  std::vector<T> stack;
  int curr_size;
};

// A dummy class
class ClassOne
{

public:
  int i;
  int& i_2 = i;
  double d;
  long int li;
  long li_1;
  unsigned long li_2;
  std::map<int, std::vector<unsigned long int>> testing_Var;

  // Specify a type for ClassThree and ClassFour
  ClassThree<double> class_3;
  ClassFour<char> class_4;
  
  // Decalring it as a member variable
  //   std::vector<clock_t> my_vec_clock;
  
  // Constructor
  ClassOne() : d{10.01}, i{22} {}

  ClassOne(double first, int second):d{first}, i{second} {}

  // Some method, defined in classes.cpp
  void some_method(int);

  // Some other method, defined right here
  void some_other_method(int i_in)
  {
    std::cout << "ClassOne::some_other_method: arg 1: i_in = " << i_in << std::endl;
  }

  // Testing methods which returns a clock instead
  clock_t return_clock_t();

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
    // std::vector<ClassOne> loading_test;
  };
  

}


#endif