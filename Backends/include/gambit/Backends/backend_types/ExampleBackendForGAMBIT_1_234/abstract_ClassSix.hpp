#ifndef __abstract_ClassSix_ExampleBackendForGAMBIT_1_234_hpp__
#define __abstract_ClassSix_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <iostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_ClassFive__ClassFour_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class Abstract_ClassSix : virtual public Abstract_ClassFive__ClassFour
  {
    public:
  
      virtual int pop2() =0;
  
      virtual void push2(int) =0;
  
      virtual int size2() =0;
  
    public:
      using Abstract_ClassFive__ClassFour::pointer_assign__BOSS;
      virtual void pointer_assign__BOSS(Abstract_ClassSix*) =0;
      virtual Abstract_ClassSix* pointer_copy__BOSS() =0;
  
    private:
      ClassSix* wptr;
      bool delete_wrapper;
    public:
      ClassSix* get_wptr() { return wptr; }
      void set_wptr(ClassSix* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassSix()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassSix(const Abstract_ClassSix& in) : 
        Abstract_ClassFive__ClassFour(in)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassSix& operator=(const Abstract_ClassSix&) { return *this; }
  
      virtual void init_wrapper() =0;
  
      ClassSix* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassSix& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassSix() =0;
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ClassSix_ExampleBackendForGAMBIT_1_234_hpp__ */
