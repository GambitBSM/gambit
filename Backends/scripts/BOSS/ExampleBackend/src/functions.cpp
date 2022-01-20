#include <iostream>
#include "functions.hpp"

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

  std::vector<ClassOne> return_as_classOne_vec(double first, int second) {
    ClassOne class_test = ClassOne(first, second);
    std::vector<ClassOne> vec = std::vector<ClassOne>{class_test};
    return vec;
  }

}

