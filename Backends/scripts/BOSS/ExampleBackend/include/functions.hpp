#ifndef __functions_hpp__
#define __functions_hpp__

#include <vector>
#include "classes.hpp"

namespace SomeNamespace
{

  // Return two ints as a vector<int>
  std::vector<int> return_as_vector(int, int);

  // Same as return_as_vector, but now with one reference argument
  std::vector<int> return_as_vector_2(int, int&);

  // Function with return-by-value of a loaded class
  ClassFour return_a_ClassFour_instance();

}


#endif