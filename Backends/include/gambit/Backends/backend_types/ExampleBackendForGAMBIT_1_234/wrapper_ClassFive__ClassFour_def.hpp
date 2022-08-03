#ifndef __wrapper_ClassFive__ClassFour_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassFive__ClassFour_def_ExampleBackendForGAMBIT_1_234_hpp__

#include "wrapper_ClassFour_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline ClassFour ClassFive__ClassFour::pop()
  {
    return ClassFour( get_BEptr()->pop__BOSS() );
  }
  
  inline void ClassFive__ClassFour::push(ClassFour item)
  {
    get_BEptr()->push__BOSS(*item.get_BEptr());
  }
  
  inline int ClassFive__ClassFour::size()
  {
    return get_BEptr()->size();
  }
  
  
  // Wrappers for original constructors: 
  inline ClassFive__ClassFour::ClassFive__ClassFour() :
    WrapperBase(__factory0())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassFive__ClassFour::ClassFive__ClassFour(Abstract_ClassFive__ClassFour* in) :
    WrapperBase(in)
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassFive__ClassFour::ClassFive__ClassFour(const ClassFive__ClassFour& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassFive__ClassFour& ClassFive__ClassFour::operator=(const ClassFive__ClassFour& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassFive__ClassFour::~ClassFive__ClassFour()
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
  inline Abstract_ClassFive__ClassFour* ClassFive__ClassFour::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassFive__ClassFour*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassFive__ClassFour_def_ExampleBackendForGAMBIT_1_234_hpp__ */
