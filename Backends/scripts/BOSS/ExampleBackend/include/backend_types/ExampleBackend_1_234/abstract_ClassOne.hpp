#ifndef __abstract_ClassOne_ExampleBackend_1_234_hpp__
#define __abstract_ClassOne_ExampleBackend_1_234_hpp__

#include <cstddef>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

// Forward declaration needed by the destructor pattern.
void set_delete_BEptr(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassOne*, bool);


// Forward declaration needed by the destructor pattern.
void wrapper_deleter(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassOne*);


// Forward declaration for wrapper_creator.
CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassOne* wrapper_creator(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassOne*);


namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class Abstract_ClassOne : public virtual AbstractBase
  {
    public:
  
      virtual int& i_ref__BOSS() =0;
  
      virtual int& i_2_ref__BOSS() =0;
  
      virtual double& d_ref__BOSS() =0;
  
      virtual long int& li_ref__BOSS() =0;
  
      virtual long int& li_1_ref__BOSS() =0;
  
      virtual long unsigned int& li_2_ref__BOSS() =0;
  
      virtual void some_method(int) =0;
  
      virtual void some_other_method(int) =0;
  
      virtual long int return_clock_t() =0;
  
      virtual ::std::vector<int, std::allocator<int> > return_as_vector_with_int() =0;
  
      virtual ::std::vector<long, std::allocator<long> > return_as_vector_with_clock() =0;
  
    public:
      virtual Abstract_ClassOne* pointer_copy__BOSS() =0;
  
    private:
      ClassOne* wptr;
      bool delete_wrapper;
    public:
      ClassOne* get_wptr() { return wptr; }
      void set_wptr(ClassOne* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassOne()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassOne(const Abstract_ClassOne&)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassOne& operator=(const Abstract_ClassOne&) { return *this; }
  
      virtual void init_wrapper()
      {
        if (wptr == 0)
        {
          wptr = wrapper_creator(this);
          delete_wrapper = true;
        }
      }
  
      ClassOne* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassOne& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassOne()
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


#endif /* __abstract_ClassOne_ExampleBackend_1_234_hpp__ */
