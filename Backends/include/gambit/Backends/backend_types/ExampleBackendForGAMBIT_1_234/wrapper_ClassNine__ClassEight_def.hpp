#ifndef __wrapper_ClassNine__ClassEight_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassNine__ClassEight_def_ExampleBackendForGAMBIT_1_234_hpp__

#include "wrapper_ClassEight_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace ClassNamespace
  {
    
    // Member functions: 
    inline ClassEight ClassNine__ClassEight::pop()
    {
      return ClassEight( get_BEptr()->pop__BOSS() );
    }
    
    inline const ClassEight& ClassNine__ClassEight::last() const
    {
      return const_cast<Abstract_ClassEight&>(const_cast<const Abstract_ClassNine__ClassEight*>(get_BEptr())->last__BOSS()).get_init_wref();
    }
    
    inline void ClassNine__ClassEight::push(ClassNamespace::ClassEight item)
    {
      get_BEptr()->push__BOSS(*item.get_BEptr());
    }
    
    inline int ClassNine__ClassEight::size()
    {
      return get_BEptr()->size();
    }
    
    
    // Wrappers for original constructors: 
    inline ClassNine__ClassEight::ClassNine__ClassEight() :
      WrapperBase(__factory0())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline ClassNine__ClassEight::ClassNine__ClassEight(Abstract_ClassNine__ClassEight* in) :
      WrapperBase(in)
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline ClassNine__ClassEight::ClassNine__ClassEight(const ClassNine__ClassEight& in) :
      WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline ClassNine__ClassEight& ClassNine__ClassEight::operator=(const ClassNine__ClassEight& in)
    {
      if (this != &in)
      {
        get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
    }
    
    
    // Destructor: 
    inline ClassNine__ClassEight::~ClassNine__ClassEight()
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
    inline Abstract_ClassNine__ClassEight* ClassNamespace::ClassNine__ClassEight::get_BEptr() const
    {
      return dynamic_cast<Abstract_ClassNine__ClassEight*>(BEptr);
    }
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassNine__ClassEight_def_ExampleBackendForGAMBIT_1_234_hpp__ */
