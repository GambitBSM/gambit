#include <vector>
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
#include "classes.hpp"



#include "backend_types/ExampleBackend_1_234/identification.hpp"

Abstract_ClassFour* ClassFour::pointer_copy__BOSS()
{
  Abstract_ClassFour* new_ptr = new ClassFour(*this);
  return new_ptr;
}

void ClassFour::pointer_assign__BOSS(Abstract_ClassFour* in)
{
  CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFour* wptr_temp = Abstract_ClassFour::get_wptr();
  *this = *dynamic_cast<ClassFour*>(in);
  Abstract_ClassFour::set_wptr(wptr_temp);
}

#include "gambit/Backends/backend_undefs.hpp"
