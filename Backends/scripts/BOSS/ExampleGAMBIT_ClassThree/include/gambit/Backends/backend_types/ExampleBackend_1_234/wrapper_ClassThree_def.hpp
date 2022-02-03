#ifndef __wrapper_ClassThree_def_ExampleBackend_1_234_hpp__
#define __wrapper_ClassThree_def_ExampleBackend_1_234_hpp__

#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  template <typename T>
  inline T ClassThree<T>::pop()
  {
    return get_BEptr()->pop();
  }
  
  template <typename T>
  inline void ClassThree<T>::push(T item)
  {
    get_BEptr()->push(item);
  }
  
  template <typename T>
  inline int ClassThree<T>::size()
  {
    return get_BEptr()->size();
  }
  
  
  // Wrappers for original constructors: 
  template <typename T>
  inline ClassThree<T>::ClassThree() :
    WrapperBase(__factory0())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  template <typename T>
  inline ClassThree<T>::ClassThree(Abstract_ClassThree<T>* in) :
    WrapperBase(in)
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  template <typename T>
  inline ClassThree<T>::ClassThree(const ClassThree& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  template <typename T>
  inline ClassThree<T>& ClassThree<T>::operator=(const ClassThree& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  template <typename T>
  inline ClassThree<T>::~ClassThree()
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
  template <typename T>
  inline Abstract_ClassThree<T>* ClassThree<T>::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassThree<T>*>(BEptr);
  }
  
  // static ClassThree<double> dummy_static_classthree_double;

}



#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree_def_ExampleBackend_1_234_hpp__ */
