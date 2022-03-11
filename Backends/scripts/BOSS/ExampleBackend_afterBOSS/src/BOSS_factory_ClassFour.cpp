#include "classes.hpp"
#include "backend_types/ExampleBackend_1_234/wrapper_ClassFour.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"

extern "C"
{
Abstract_ClassFour* Factory_ClassFour_0__BOSS_2()
{
  return new ClassFour();
}

}

