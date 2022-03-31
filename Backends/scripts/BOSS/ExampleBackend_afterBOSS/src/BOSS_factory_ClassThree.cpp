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

Abstract_ClassThree<int>* Factory_ClassThree_0_int__BOSS_2()
{
  return new ClassThree<int>();
}

Abstract_ClassThree<ClassFour>* Factory_ClassThree_0_ClassFour__BOSS_3()
{
  return new ClassThree<ClassFour>();
}

}

