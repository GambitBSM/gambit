#ifndef __wrapper_ClassFive_def_ExampleBackend_1_234_hpp__
#define __wrapper_ClassFive_def_ExampleBackend_1_234_hpp__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  
  // Wrappers for original constructors: 
  inline ClassFive<ClassFour>::ClassFive() :
    WrapperBase(__factory0())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassFive<ClassFour>::ClassFive(Abstract_ClassFive<ClassFour>* in) :
    WrapperBase(in)
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassFive<ClassFour>::ClassFive(const ClassFive& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassFive<ClassFour>& ClassFive<ClassFour>::operator=(const ClassFive& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassFive<ClassFour>::~ClassFive()
  {
    if (get_BEptr() != 0)
    {
      get_BEptr()->set_delete_wrapper(false);
      if (can_delete_BEptr())
      {
        delete BEptr;
        BEptr = 0;
      }
    }
    set_delete_BEptr(false);
  }
  
  // Returns correctly casted pointer to Abstract class: 
  inline Abstract_ClassFive<ClassFour>* ClassFive<ClassFour>::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassFive<ClassFour>*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassFive_def_ExampleBackend_1_234_hpp__ */
