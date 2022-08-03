#ifndef __wrapper_ClassThree__int_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassThree__int_def_ExampleBackendForGAMBIT_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline int ClassThree__int::pop()
  {
    return get_BEptr()->pop();
  }
  
  inline void ClassThree__int::push(int item)
  {
    get_BEptr()->push(item);
  }
  
  inline int ClassThree__int::size()
  {
    return get_BEptr()->size();
  }
  
  inline ClassThree__int ClassThree__int::operator+(ClassThree__int& other)
  {
    return ClassThree__int( get_BEptr()->operator_plus__BOSS(*other.get_BEptr()) );
  }
  
  
  // Wrappers for original constructors: 
  inline ClassThree__int::ClassThree__int() :
    WrapperBase(__factory0()),
    test( get_BEptr()->test_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassThree__int::ClassThree__int(Abstract_ClassThree<int>* in) :
    WrapperBase(in),
    test( get_BEptr()->test_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassThree__int::ClassThree__int(const ClassThree__int& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
    test( get_BEptr()->test_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline ClassThree__int& ClassThree__int::operator=(const ClassThree__int& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline ClassThree__int::~ClassThree__int()
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
  inline Abstract_ClassThree<int>* ClassThree__int::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassThree<int>*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree__int_def_ExampleBackendForGAMBIT_1_234_hpp__ */
