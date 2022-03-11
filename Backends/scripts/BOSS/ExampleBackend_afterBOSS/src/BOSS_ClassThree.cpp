#include <vector>
#include "gambit/Backends/abstracttypedefs.hpp"
#include "gambit/Backends/wrappertypedefs.hpp"
#include "classes.hpp"



#include "backend_types/ExampleBackend_1_234/identification.hpp"


template <typename T>
Abstract_ClassThree<T>* ClassThree<T>::pointer_copy__BOSS()
{
  Abstract_ClassThree<T>* new_ptr = new ClassThree<T>(*this);
  return new_ptr;
}

template <typename T>
void ClassThree<T>::pointer_assign__BOSS(Abstract_ClassThree<T>* in)
{
  CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<T>* wptr_temp = Abstract_ClassThree<T>::get_wptr();
  *this = *dynamic_cast<ClassThree<T>*>(in);
  Abstract_ClassThree<T>::set_wptr(wptr_temp);
}


#include "gambit/Backends/backend_undefs.hpp"
