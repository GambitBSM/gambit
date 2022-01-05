#include <iostream>
#include "functions.hpp"
// #include <fstream>
#include <ctime>

namespace SomeNamespace
{

  // A dummy function that modifies a ClassTwo instance
  void modify_instance(int j_in, ClassTwo& ct_in)
  {
    std::cout << "modify_instance: arg 1: j_in = " << j_in << ", arg 2: ct_in = ref-to-ClassTwo instance at " << &ct_in << std::endl;

    ct_in.j = j_in;
  }


  // Return two ints as a vector<int>
  std::vector<int> return_as_vector(int a, int b)
  {
    std::vector<int> vec = std::vector<int>{a,b};
    return vec;
  }

  // Same as return_as_vector, but now with one reference argument
  std::vector<int> return_as_vector_2(int a, int& b)
  {
    std::vector<int> vec = std::vector<int>{a,b};
    return vec;
  }


  std::vector<clock_t> return_as_vector_with_clock()
  {
    clock_t c = clock();
    std::vector<clock_t> vec; 
    vec.push_back(c);
    // = std::vector<std::filebuf>{fb};
    return vec;
  }

}

