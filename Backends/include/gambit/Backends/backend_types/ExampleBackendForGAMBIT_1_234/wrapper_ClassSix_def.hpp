#ifndef __wrapper_ClassSix_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassSix_def_ExampleBackendForGAMBIT_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline int ClassSix::pop2()
  {
    return get_BEptr()->pop2();
  }
  
  inline void ClassSix::push2(int item)
  {
    get_BEptr()->push2(item);
  }
  
  inline int ClassSix::size2()
  {
    return get_BEptr()->size2();
  }
  
  
  // Wrappers for original constructors: 
  inline ClassSix::ClassSix() :
    ClassFive__ClassFour(__factory0())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassSix::ClassSix(Abstract_ClassSix* in) :
    ClassFive__ClassFour(in)
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassSix::ClassSix(const ClassSix& in) :
    ClassFive__ClassFour(in.get_BEptr()->pointer_copy__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassSix& ClassSix::operator=(const ClassSix& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassSix::~ClassSix()
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
  inline Abstract_ClassSix* ClassSix::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassSix*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassSix_def_ExampleBackendForGAMBIT_1_234_hpp__ */
