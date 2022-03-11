

#include <vector>
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
#include "functions.hpp"
#include "gambit/Backends/function_return_utils.hpp"

namespace SomeNamespace
{
  extern "C"
  {
  ::std::vector<int, std::allocator<int>> return_as_vector__BOSS_2(int arg_1, int arg_2)
  {
    return return_as_vector(arg_1, arg_2);
  }
  
  }

}

