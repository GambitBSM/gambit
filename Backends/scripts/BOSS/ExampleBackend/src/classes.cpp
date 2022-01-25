#include <iostream>
#include "classes.hpp"

void ClassOne::some_method(int i_in)
{
  std::cout << "ClassOne::some_method: arg 1: i_in = " << i_in << std::endl;
}


clock_t ClassOne::return_clock_t() {
  clock_t c = clock();
  return c;
}

std::vector<int> ClassOne::return_as_vector_with_int()
{
  std::vector<int> vec = std::vector<int>{1,2};
  return vec;
}


std::vector<clock_t> ClassOne::return_as_vector_with_clock()
{
  clock_t c = clock();
  std::vector<clock_t> vec; 
  vec.push_back(c);
  return vec;
}

T ClassThree::pop()
{
  T top = stack.back()
  stack.pop_back();
  return top;
}

void ClassThree::push(T& item)
{
  stack.push_back(item);
}

int ClassThree::size()
{
  return stack.size();
}

T aRandomNamespace::ClassFour::pop()
{
  T top = stack.back()
  stack.pop_back();
  return top;
}

void aRandomNamespace::ClassFour::push(T& item)
{
  stack.push_back(item);
}

int aRandomNamespace::ClassFour::size()
{
  return stack.size();
}
