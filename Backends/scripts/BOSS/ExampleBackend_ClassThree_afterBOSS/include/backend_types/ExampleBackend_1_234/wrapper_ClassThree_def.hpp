#ifndef __wrapper_ClassThree_def_ExampleBackend_1_234_hpp__
#define __wrapper_ClassThree_def_ExampleBackend_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline double ClassThree<double>::pop()
  {
    return get_BEptr()->pop();
  }
  
  inline void ClassThree<double>::push(double item)
  {
    get_BEptr()->push(item);
  }
  
  inline int ClassThree<double>::size()
  {
    return get_BEptr()->size();
  }
  
  
  // Wrappers for original constructors: 
  inline ClassThree<double>::ClassThree() :
    WrapperBase(__factory0())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassThree<double>::ClassThree(Abstract_ClassThree<double>* in) :
    WrapperBase(in)
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassThree<double>::ClassThree(const ClassThree& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassThree<double>& ClassThree<double>::operator=(const ClassThree& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassThree<double>::~ClassThree()
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
  inline Abstract_ClassThree<double>* ClassThree<double>::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassThree<double>*>(BEptr);
  }


  // 
  // Anders: Repeat everything above for any other specializations, e.g. ClassThree<int>
  // 
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree_def_ExampleBackend_1_234_hpp__ */
