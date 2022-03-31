#include "classes.hpp"
#include "backend_types/ExampleBackend_1_234/wrapper_ClassFive.hpp"
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"

extern "C"
{
Abstract_ClassFive<ClassFour>* Factory_ClassFive_0_ClassFour__BOSS_5()
{
  return new ClassFive<ClassFour>();
}

}

