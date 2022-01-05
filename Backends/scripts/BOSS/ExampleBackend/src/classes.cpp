#include <iostream>
#include "classes.hpp"
// #include <ctime>


void ClassOne::some_method(int i_in)
{
  std::cout << "ClassOne::some_method: arg 1: i_in = " << i_in << std::endl;
}


std::vector<clock_t> ClassOne::return_as_vector_with_clock()
{
  clock_t c = clock();
  std::vector<clock_t> vec; 
  vec.push_back(c);
  // = std::vector<std::filebuf>{fb};
  return vec;
}
