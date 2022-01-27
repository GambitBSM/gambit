#include "classes.hpp"
#include "backend_types/ExampleBackend_1_234/wrapper_ClassThree.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"

extern "C"
{

Abstract_ClassThree<double>* Factory_ClassThree_0_double__BOSS_1()
{
  return new ClassThree<double>();
}


}

