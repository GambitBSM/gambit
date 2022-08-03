#ifndef __wrapper_ClassSeven__double_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassSeven__double_def_ExampleBackendForGAMBIT_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline double ClassSeven__double::pop2()
  {
    return get_BEptr()->pop2();
  }
  
  inline void ClassSeven__double::push2(double item)
  {
    get_BEptr()->push2(item);
  }
  
  inline int ClassSeven__double::size2()
  {
    return get_BEptr()->size2();
  }
  
  
  // Wrappers for original constructors: 
  inline ClassSeven__double::ClassSeven__double() :
    ClassThree__double(__factory0())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassSeven__double::ClassSeven__double(Abstract_ClassSeven<double>* in) :
    ClassThree__double(in)
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassSeven__double::ClassSeven__double(const ClassSeven__double& in) :
    ClassThree__double(in.get_BEptr()->pointer_copy__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassSeven__double& ClassSeven__double::operator=(const ClassSeven__double& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassSeven__double::~ClassSeven__double()
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
  inline Abstract_ClassSeven<double>* ClassSeven__double::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassSeven<double>*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassSeven__double_def_ExampleBackendForGAMBIT_1_234_hpp__ */
