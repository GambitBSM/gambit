#ifndef __functions_hpp__
#define __functions_hpp__

#include <vector>
#include "classes.hpp"

namespace SomeNamespace
{

  // A dummy function that modifies a ClassTwo instance.
  void modify_instance(int, ClassTwo&);


  // Return two ints as a vector<int>
  std::vector<int> return_as_vector(int, int);

  // Same as return_as_vector, but now with one reference argument
  std::vector<int> return_as_vector_2(int, int&);

  std::vector<ClassOne> return_as_classOne_vec();

}


#endif