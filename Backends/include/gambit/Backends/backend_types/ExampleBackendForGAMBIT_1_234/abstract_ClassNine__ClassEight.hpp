#ifndef __abstract_ClassNine__ClassEight_ExampleBackendForGAMBIT_1_234_hpp__
#define __abstract_ClassNine__ClassEight_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_ClassEight_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  namespace ClassNamespace
  {
    class Abstract_ClassNine__ClassEight : public virtual AbstractBase
    {
      public:
  
        virtual ClassNamespace::Abstract_ClassEight* pop__BOSS() =0;
  
        virtual const ClassNamespace::Abstract_ClassEight& last__BOSS() const =0;
  
        virtual void push__BOSS(ClassNamespace::Abstract_ClassEight&) =0;
  
        virtual int size() =0;
  
      public:
        virtual void pointer_assign__BOSS(Abstract_ClassNine__ClassEight*) =0;
        virtual Abstract_ClassNine__ClassEight* pointer_copy__BOSS() =0;
  
      private:
        ClassNine__ClassEight* wptr;
        bool delete_wrapper;
      public:
        ClassNine__ClassEight* get_wptr() { return wptr; }
        void set_wptr(ClassNine__ClassEight* wptr_in) { wptr = wptr_in; }
        bool get_delete_wrapper() { return delete_wrapper; }
        void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
      public:
        Abstract_ClassNine__ClassEight()
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassNine__ClassEight(const Abstract_ClassNine__ClassEight&)
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassNine__ClassEight& operator=(const Abstract_ClassNine__ClassEight&) { return *this; }
  
        virtual void init_wrapper() =0;
  
        ClassNine__ClassEight* get_init_wptr()
        {
          init_wrapper();
          return wptr;
        }
  
        ClassNine__ClassEight& get_init_wref()
        {
          init_wrapper();
          return *wptr;
        }
  
        virtual ~Abstract_ClassNine__ClassEight() =0;
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ClassNine__ClassEight_ExampleBackendForGAMBIT_1_234_hpp__ */
