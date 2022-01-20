#ifndef __wrapper_ClassOne_def_ExampleBackend_1_234_hpp__
#define __wrapper_ClassOne_def_ExampleBackend_1_234_hpp__

#include <map>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  inline void ClassOne::some_method(int arg_1)
  {
    get_BEptr()->some_method(arg_1);
  }
  
  inline void ClassOne::some_other_method(int i_in)
  {
    get_BEptr()->some_other_method(i_in);
  }
  
  inline long int ClassOne::return_clock_t()
  {
    return get_BEptr()->return_clock_t();
  }
  
  inline ::std::vector<int, std::allocator<int> > ClassOne::return_as_vector_with_int()
  {
    return get_BEptr()->return_as_vector_with_int();
  }
  
  inline ::std::vector<long, std::allocator<long> > ClassOne::return_as_vector_with_clock()
  {
    return get_BEptr()->return_as_vector_with_clock();
  }
  
  
  // Wrappers for original constructors: 
  inline ClassOne::ClassOne() :
    WrapperBase(__factory0()),
    i( get_BEptr()->i_ref__BOSS()),
    i_2( get_BEptr()->i_2_ref__BOSS()),
    d( get_BEptr()->d_ref__BOSS()),
    li( get_BEptr()->li_ref__BOSS()),
    li_1( get_BEptr()->li_1_ref__BOSS()),
    li_2( get_BEptr()->li_2_ref__BOSS()),
    testing_Var( get_BEptr()->testing_Var_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  inline ClassOne::ClassOne(double first, int second) :
    WrapperBase(__factory1(first, second)),
    i( get_BEptr()->i_ref__BOSS()),
    i_2( get_BEptr()->i_2_ref__BOSS()),
    d( get_BEptr()->d_ref__BOSS()),
    li( get_BEptr()->li_ref__BOSS()),
    li_1( get_BEptr()->li_1_ref__BOSS()),
    li_2( get_BEptr()->li_2_ref__BOSS()),
    testing_Var( get_BEptr()->testing_Var_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline ClassOne::ClassOne(Abstract_ClassOne* in) :
    WrapperBase(in),
    i( get_BEptr()->i_ref__BOSS()),
    i_2( get_BEptr()->i_2_ref__BOSS()),
    d( get_BEptr()->d_ref__BOSS()),
    li( get_BEptr()->li_ref__BOSS()),
    li_1( get_BEptr()->li_1_ref__BOSS()),
    li_2( get_BEptr()->li_2_ref__BOSS()),
    testing_Var( get_BEptr()->testing_Var_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline ClassOne::ClassOne(const ClassOne& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
    i( get_BEptr()->i_ref__BOSS()),
    i_2( get_BEptr()->i_2_ref__BOSS()),
    d( get_BEptr()->d_ref__BOSS()),
    li( get_BEptr()->li_ref__BOSS()),
    li_1( get_BEptr()->li_1_ref__BOSS()),
    li_2( get_BEptr()->li_2_ref__BOSS()),
    testing_Var( get_BEptr()->testing_Var_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Destructor: 
  inline ClassOne::~ClassOne()
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
  inline Abstract_ClassOne* ClassOne::get_BEptr() const
  {
    return dynamic_cast<Abstract_ClassOne*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassOne_def_ExampleBackend_1_234_hpp__ */
