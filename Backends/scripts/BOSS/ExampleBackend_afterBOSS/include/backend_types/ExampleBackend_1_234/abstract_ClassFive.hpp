#ifndef __abstract_ClassFive_ExampleBackend_1_234_hpp__
#define __abstract_ClassFive_ExampleBackend_1_234_hpp__

#include <cstddef>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"
template <typename T1>
void set_delete_BEptr(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFive<T1>*, bool);

template <typename T1>
void wrapper_deleter(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFive<T1>*);

template <typename T1>
CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassFive<T1>* wrapper_creator(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassFive<T1>*);


namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template <typename T1>
  class Abstract_ClassFive : public virtual AbstractBase
  {
  
    public:
      virtual void pointer_assign__BOSS(Abstract_ClassFive<T1>*) =0;
      virtual Abstract_ClassFive<T1>* pointer_copy__BOSS() =0;
  
    private:
      ClassFive<T1>* wptr;
      bool delete_wrapper;
    public:
      ClassFive<T1>* get_wptr() { return wptr; }
      void set_wptr(ClassFive<T1>* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassFive()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassFive(const Abstract_ClassFive& in)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassFive& operator=(const Abstract_ClassFive&) { return *this; }
  
      virtual void init_wrapper()
      {
        if (wptr == 0)
        {
          wptr = wrapper_creator<T1>(this);
          delete_wrapper = true;
        }
      }
  
      ClassFive<T1>* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassFive<T1>& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassFive()
      {
        if (wptr != 0)
        {
          set_delete_BEptr<T1>(wptr, false);
          if (delete_wrapper == true)
          {
            wrapper_deleter<T1>(wptr);
            wptr = 0;
            delete_wrapper = false;
          }
        }
      }
  };

}


#include "gambit/Backends/backend_undefs.hpp"



#endif /* __abstract_ClassFive_ExampleBackend_1_234_hpp__ */
