#ifndef __wrapper_ClassTen__double_def_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassTen__double_def_ExampleBackendForGAMBIT_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace ClassNamespace
  {
    
    // Member functions: 
    inline double ClassTen__double::pop()
    {
      return get_BEptr()->pop();
    }
    
    inline void ClassTen__double::push(double item)
    {
      get_BEptr()->push(item);
    }
    
    inline int ClassTen__double::size()
    {
      return get_BEptr()->size();
    }
    
    inline ClassTen__double ClassTen__double::operator+(ClassNamespace::ClassTen__double other)
    {
      return ClassTen__double( get_BEptr()->operator_plus__BOSS(*other.get_BEptr()) );
    }
    
    
    // Wrappers for original constructors: 
    inline ClassTen__double::ClassTen__double() :
      WrapperBase(__factory0()),
      test( get_BEptr()->test_ref__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Special pointer-based constructor: 
    inline ClassTen__double::ClassTen__double(Abstract_ClassTen<double>* in) :
      WrapperBase(in),
      test( get_BEptr()->test_ref__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Copy constructor: 
    inline ClassTen__double::ClassTen__double(const ClassTen__double& in) :
      WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
      test( get_BEptr()->test_ref__BOSS())
    {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
    }
    
    // Assignment operator: 
    inline ClassTen__double& ClassTen__double::operator=(const ClassTen__double& in)
    {
      if (this != &in)
      {
        get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
    }
    
    
    // Destructor: 
    inline ClassTen__double::~ClassTen__double()
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
    inline Abstract_ClassTen<double>* ClassNamespace::ClassTen__double::get_BEptr() const
    {
      return dynamic_cast<Abstract_ClassTen<double>*>(BEptr);
    }
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassTen__double_def_ExampleBackendForGAMBIT_1_234_hpp__ */
