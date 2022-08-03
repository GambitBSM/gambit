#ifndef __wrapper_ClassFour_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassFour_def_ExampleBackendForGAMBIT_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline double ClassFour::pop()
  {
    return get_BEptr()->pop();
  }
  
  inline void ClassFour::push(double item)
  {
    get_BEptr()->push(item);
  }
  
  inline int ClassFour::size()
  {
    return get_BEptr()->size();
  }
  
  inline ClassFour ClassFour::operator+(ClassFour& other)
  {
    return ClassFour( get_BEptr()->operator_plus__BOSS(*other.get_BEptr()) );
  }
  
  
  // Wrappers for original constructors: 
  inline ClassFour::ClassFour() :
    WrapperBase(__factory0())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassFour::ClassFour(Abstract_ClassFour* in) :
    WrapperBase(in)
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassFour::ClassFour(const ClassFour& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassFour& ClassFour::operator=(const ClassFour& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassFour::~ClassFour()
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
  inline Abstract_ClassFour* ClassFour::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassFour*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassFour_def_ExampleBackendForGAMBIT_1_234_hpp__ */
