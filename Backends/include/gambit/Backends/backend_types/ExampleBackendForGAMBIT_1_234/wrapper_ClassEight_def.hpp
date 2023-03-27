#ifndef __wrapper_ClassEight_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassEight_def_ExampleBackendForGAMBIT_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace ClassNamespace
  {
    
    // Member functions: 
    inline double ClassEight::pop()
    {
      return get_BEptr()->pop();
    }
    
    inline void ClassEight::push(double item)
    {
      get_BEptr()->push(item);
    }
    
    inline int ClassEight::size()
    {
      return get_BEptr()->size();
    }
    
    inline ClassEight ClassEight::operator+(ClassNamespace::ClassEight other)
    {
      return ClassEight( get_BEptr()->operator_plus__BOSS(*other.get_BEptr()) );
    }
    
    
    // Wrappers for original constructors: 
    inline ClassEight::ClassEight() :
      WrapperBase(__factory0())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline ClassEight::ClassEight(Abstract_ClassEight* in) :
      WrapperBase(in)
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline ClassEight::ClassEight(const ClassEight& in) :
      WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline ClassEight& ClassEight::operator=(const ClassEight& in)
    {
      if (this != &in)
      {
        get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
    }
    
    
    // Destructor: 
    inline ClassEight::~ClassEight()
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
    inline Abstract_ClassEight* ClassNamespace::ClassEight::get_BEptr() const
    {
      return dynamic_cast<Abstract_ClassEight*>(BEptr);
    }
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassEight_def_ExampleBackendForGAMBIT_1_234_hpp__ */
