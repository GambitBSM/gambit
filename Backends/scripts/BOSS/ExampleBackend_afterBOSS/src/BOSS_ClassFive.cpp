#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
#include "classes.hpp"

Abstract_ClassFour* ClassFive<ClassFour>::pop__BOSS()
{
  return new ClassFour(pop());
}


void ClassFive<ClassFour>::push__BOSS(Abstract_ClassFour& item)
{
  push(dynamic_cast< ClassFour& >(item));
}




#include "backend_types/ExampleBackend_1_234/identification.hpp"

Abstract_ClassFive<ClassFour>* ClassFive<ClassFour>::pointer_copy__BOSS()
{
  Abstract_ClassFive<ClassFour>* new_ptr = new ClassFive<ClassFour>(*this);
  return new_ptr;
}

void ClassFive<ClassFour>::pointer_assign__BOSS(Abstract_ClassFive<ClassFour>* in)
{
  CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFive<ClassFour>* wptr_temp = Abstract_ClassFive<ClassFour>::get_wptr();
  *this = *dynamic_cast<ClassFive<ClassFour>*>(in);
  Abstract_ClassFive<ClassFour>::set_wptr(wptr_temp);
}

#include "gambit/Backends/backend_undefs.hpp"
