#ifndef __wrapper_ClassTwo_def_ExampleBackend_1_234_hpp__
#define __wrapper_ClassTwo_def_ExampleBackend_1_234_hpp__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace SomeNamespace
  {
    
    // Member functions: 
    
    // Wrappers for original constructors: 
    inline ClassTwo::ClassTwo() :
      WrapperBase(__factory0()),
      j( get_BEptr()->j_ref__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline ClassTwo::ClassTwo(Abstract_ClassTwo* in) :
      WrapperBase(in),
      j( get_BEptr()->j_ref__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline ClassTwo::ClassTwo(const ClassTwo& in) :
      WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
      j( get_BEptr()->j_ref__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline ClassTwo& ClassTwo::operator=(const ClassTwo& in)
    {
      if (this != &in)
      {
        get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
    }
    
    
    // Destructor: 
    inline ClassTwo::~ClassTwo()
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
    inline Abstract_ClassTwo* SomeNamespace::ClassTwo::get_BEptr() const
    {
      return dynamic_cast<Abstract_ClassTwo*>(BEptr);
    }
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassTwo_def_ExampleBackend_1_234_hpp__ */
