#include <iostream>
#include "functions.hpp"

namespace SomeNamespace
{

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

  // Function with return-by-value of a loaded class
  ClassFour return_a_ClassFour_instance()
  {
    ClassFour c;
    c.push(1.0);
    c.push(2.0);
    c.push(3.0);
    return c;
  }

}

