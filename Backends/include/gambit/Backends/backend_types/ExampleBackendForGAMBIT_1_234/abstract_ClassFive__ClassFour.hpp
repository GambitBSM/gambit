#ifndef __abstract_ClassFive__ClassFour_ExampleBackendForGAMBIT_1_234_hpp__
#define __abstract_ClassFive__ClassFour_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_ClassFour_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class Abstract_ClassFive__ClassFour : public virtual AbstractBase
  {
    public:
  
      virtual Abstract_ClassFour* pop__BOSS() =0;
  
      virtual const Abstract_ClassFour& last__BOSS() const =0;
  
      virtual void push__BOSS(Abstract_ClassFour&) =0;
  
      virtual int size() =0;
  
    public:
      virtual void pointer_assign__BOSS(Abstract_ClassFive__ClassFour*) =0;
      virtual Abstract_ClassFive__ClassFour* pointer_copy__BOSS() =0;
  
    private:
      ClassFive__ClassFour* wptr;
      bool delete_wrapper;
    public:
      ClassFive__ClassFour* get_wptr() { return wptr; }
      void set_wptr(ClassFive__ClassFour* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassFive__ClassFour()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassFive__ClassFour(const Abstract_ClassFive__ClassFour&)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassFive__ClassFour& operator=(const Abstract_ClassFive__ClassFour&) { return *this; }
  
      virtual void init_wrapper() =0;
  
      ClassFive__ClassFour* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassFive__ClassFour& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassFive__ClassFour() =0;
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ClassFive__ClassFour_ExampleBackendForGAMBIT_1_234_hpp__ */
