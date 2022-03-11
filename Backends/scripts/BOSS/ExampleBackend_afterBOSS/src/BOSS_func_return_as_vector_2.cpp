

#include <vector>
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
#include "functions.hpp"
#include "gambit/Backends/function_return_utils.hpp"

namespace SomeNamespace
{
  extern "C"
  {
  ::std::vector<int, std::allocator<int>> return_as_vector_2__BOSS_3(int arg_1, int& arg_2)
  {
    return return_as_vector_2(arg_1, arg_2);
  }
  
  }

}

