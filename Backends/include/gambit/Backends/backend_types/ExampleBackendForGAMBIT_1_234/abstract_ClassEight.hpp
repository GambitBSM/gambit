#ifndef __abstract_ClassEight_ExampleBackendForGAMBIT_1_234_hpp__
#define __abstract_ClassEight_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <iostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  namespace ClassNamespace
  {
    class Abstract_ClassEight : public virtual AbstractBase
    {
      public:
  
        virtual double pop() =0;
  
        virtual void push(double) =0;
  
        virtual int size() =0;
  
        virtual ClassNamespace::Abstract_ClassEight* operator_plus__BOSS(ClassNamespace::Abstract_ClassEight&) =0;
  
      public:
        virtual void pointer_assign__BOSS(Abstract_ClassEight*) =0;
        virtual Abstract_ClassEight* pointer_copy__BOSS() =0;
  
      private:
        ClassEight* wptr;
        bool delete_wrapper;
      public:
        ClassEight* get_wptr() { return wptr; }
        void set_wptr(ClassEight* wptr_in) { wptr = wptr_in; }
        bool get_delete_wrapper() { return delete_wrapper; }
        void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
      public:
        Abstract_ClassEight()
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassEight(const Abstract_ClassEight&)
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassEight& operator=(const Abstract_ClassEight&) { return *this; }
  
        virtual void init_wrapper() =0;
  
        ClassEight* get_init_wptr()
        {
          init_wrapper();
          return wptr;
        }
  
        ClassEight& get_init_wref()
        {
          init_wrapper();
          return *wptr;
        }
  
        virtual ~Abstract_ClassEight() =0;
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ClassEight_ExampleBackendForGAMBIT_1_234_hpp__ */
