#ifndef __abstract_ClassTwo_ExampleBackend_1_234_hpp__
#define __abstract_ClassTwo_ExampleBackend_1_234_hpp__

#include <cstddef>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

// Forward declaration needed by the destructor pattern.
void set_delete_BEptr(CAT_3(BACKENDNAME,_,SAFE_VERSION)::SomeNamespace::ClassTwo*, bool);


// Forward declaration needed by the destructor pattern.
void wrapper_deleter(CAT_3(BACKENDNAME,_,SAFE_VERSION)::SomeNamespace::ClassTwo*);


// Forward declaration for wrapper_creator.
CAT_3(BACKENDNAME,_,SAFE_VERSION)::SomeNamespace::ClassTwo* wrapper_creator(CAT_3(BACKENDNAME,_,SAFE_VERSION)::SomeNamespace::Abstract_ClassTwo*);


namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  namespace SomeNamespace
  {
    class Abstract_ClassTwo : public virtual AbstractBase
    {
      public:
  
        virtual int& j_ref__BOSS() =0;
  
      public:
        virtual void pointer_assign__BOSS(Abstract_ClassTwo*) =0;
        virtual Abstract_ClassTwo* pointer_copy__BOSS() =0;
  
      private:
        ClassTwo* wptr;
        bool delete_wrapper;
      public:
        ClassTwo* get_wptr() { return wptr; }
        void set_wptr(ClassTwo* wptr_in) { wptr = wptr_in; }
        bool get_delete_wrapper() { return delete_wrapper; }
        void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
      public:
        Abstract_ClassTwo()
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassTwo(const Abstract_ClassTwo&)
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassTwo& operator=(const Abstract_ClassTwo&) { return *this; }
  
        virtual void init_wrapper()
        {
          if (wptr == 0)
          {
            wptr = wrapper_creator(this);
            delete_wrapper = true;
          }
        }
  
        ClassTwo* get_init_wptr()
        {
          init_wrapper();
          return wptr;
        }
  
        ClassTwo& get_init_wref()
        {
          init_wrapper();
          return *wptr;
        }
  
        virtual ~Abstract_ClassTwo()
        {
          if (wptr != 0)
          {
            set_delete_BEptr(wptr, false);
            if (delete_wrapper == true)
            {
              wrapper_deleter(wptr);
              wptr = 0;
              delete_wrapper = false;
            }
          }
        }
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ClassTwo_ExampleBackend_1_234_hpp__ */
