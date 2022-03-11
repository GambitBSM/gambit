#ifndef __abstract_ClassFour_ExampleBackend_1_234_hpp__
#define __abstract_ClassFour_ExampleBackend_1_234_hpp__

#include <cstddef>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

// Forward declaration needed by the destructor pattern.
void set_delete_BEptr(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFour*, bool);


// Forward declaration needed by the destructor pattern.
void wrapper_deleter(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFour*);


// Forward declaration for wrapper_creator.
CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFour* wrapper_creator(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassFour*);


namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class Abstract_ClassFour : public virtual AbstractBase
  {
    public:
  
      virtual double pop() =0;
  
      virtual void push(double) =0;
  
      virtual int size() =0;
  
    public:
      virtual void pointer_assign__BOSS(Abstract_ClassFour*) =0;
      virtual Abstract_ClassFour* pointer_copy__BOSS() =0;
  
    private:
      ClassFour* wptr;
      bool delete_wrapper;
    public:
      ClassFour* get_wptr() { return wptr; }
      void set_wptr(ClassFour* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassFour()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassFour(const Abstract_ClassFour&)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassFour& operator=(const Abstract_ClassFour&) { return *this; }
  
      virtual void init_wrapper()
      {
        if (wptr == 0)
        {
          wptr = wrapper_creator(this);
          delete_wrapper = true;
        }
      }
  
      ClassFour* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassFour& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassFour()
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


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ClassFour_ExampleBackend_1_234_hpp__ */
