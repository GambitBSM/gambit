#ifndef __wrapper_ClassThree__double_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassThree__double_def_ExampleBackendForGAMBIT_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline double ClassThree__double::pop()
  {
    return get_BEptr()->pop();
  }
  
  inline void ClassThree__double::push(double item)
  {
    get_BEptr()->push(item);
  }
  
  inline int ClassThree__double::size()
  {
    return get_BEptr()->size();
  }
  
  inline ClassThree__double ClassThree__double::operator+(ClassThree__double& other)
  {
    return ClassThree__double( get_BEptr()->operator_plus__BOSS(*other.get_BEptr()) );
  }
  
  
  // Wrappers for original constructors: 
  inline ClassThree__double::ClassThree__double() :
    WrapperBase(__factory0()),
    test( get_BEptr()->test_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassThree__double::ClassThree__double(Abstract_ClassThree<double>* in) :
    WrapperBase(in),
    test( get_BEptr()->test_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassThree__double::ClassThree__double(const ClassThree__double& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
    test( get_BEptr()->test_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassThree__double& ClassThree__double::operator=(const ClassThree__double& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassThree__double::~ClassThree__double()
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
  inline Abstract_ClassThree<double>* ClassThree__double::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassThree<double>*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree__double_def_ExampleBackendForGAMBIT_1_234_hpp__ */
