#ifndef __abstract_ClassThree_ExampleBackend_1_234_hpp__
#define __abstract_ClassThree_ExampleBackend_1_234_hpp__

#include <cstddef>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

// Forward declaration needed by the destructor pattern.
template <typename T>
void set_delete_BEptr(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<T>*, bool);

template <>
void set_delete_BEptr<double>(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<double>*, bool);


// Forward declaration needed by the destructor pattern.
template <typename T>
void wrapper_deleter(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<T>*);

template <>
void wrapper_deleter<double>(CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<double>*);


// Forward declaration for wrapper_creator.
template <typename T>
CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<T>* wrapper_creator(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassThree<T>*);

template <>
CAT_3(BACKENDNAME,_,SAFE_VERSION)::ClassThree<double>* wrapper_creator<double>(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_ClassThree<double>*);




namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template <typename T>
  class Abstract_ClassThree : public virtual AbstractBase
  {
    public:
  
      virtual T pop() =0;
  
      virtual void push(T) =0;
  
      virtual int size() =0;
  
    public:
      virtual void pointer_assign__BOSS(Abstract_ClassThree<T>*) =0;
      virtual Abstract_ClassThree<T>* pointer_copy__BOSS() =0;
  
    private:
      ClassThree<T>* wptr;
      bool delete_wrapper;
    public:
      ClassThree<T>* get_wptr() { return wptr; }
      void set_wptr(ClassThree<T>* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassThree()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassThree(const Abstract_ClassThree&)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassThree& operator=(const Abstract_ClassThree&) { return *this; }
  
      virtual void init_wrapper()
      {
        if (wptr == 0)
        {
          wptr = wrapper_creator<T>(this);
          delete_wrapper = true;
        }
      }
  
      ClassThree<T>* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassThree<T>& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassThree()
      {
        if (wptr != 0)
        {
          set_delete_BEptr<T>(wptr, false);
          if (delete_wrapper == true)
          {
            wrapper_deleter<T>(wptr);
            wptr = 0;
            delete_wrapper = false;
          }
        }
      }
  };
 
  

  
  // Anders: 
  // Below we repeat the entire Abstract_ClassThree class definition for
  // the specialization Abstract_ClassThree<double>. I had to do this to allow 
  // virtual inheritance for ClassThree, i.e. this code in classes.hpp:
  //
  //   template <typename T>         
  //   class ClassThree : public virtual Abstract_ClassThree<T> {
  //
  // Repeating the entire Abstract_ClassThree class feels very silly,
  // so it woul be nice if we could get around this somehow...
  // 


  template <>
  class Abstract_ClassThree<double> : public virtual AbstractBase
  {
    public:
  
      virtual double pop() =0;
  
      virtual void push(double) =0;
  
      virtual int size() =0;
  
    public:
      virtual void pointer_assign__BOSS(Abstract_ClassThree<double>*) =0;
      virtual Abstract_ClassThree<double>* pointer_copy__BOSS() =0;
  
    private:
      ClassThree<double>* wptr;
      bool delete_wrapper;
    public:
      ClassThree<double>* get_wptr() { return wptr; }
      void set_wptr(ClassThree<double>* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassThree()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassThree(const Abstract_ClassThree&)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassThree& operator=(const Abstract_ClassThree&) { return *this; }
  
      virtual void init_wrapper()
      {
        if (wptr == 0)
        {
          wptr = wrapper_creator<double>(this);
          delete_wrapper = true;
        }
      }
  
      ClassThree<double>* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassThree<double>& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassThree()
      {
        if (wptr != 0)
        {
          set_delete_BEptr<double>(wptr, false);
          if (delete_wrapper == true)
          {
            wrapper_deleter<double>(wptr);
            wptr = 0;
            delete_wrapper = false;
          }
        }
      }
  };




}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ClassThree_ExampleBackend_1_234_hpp__ */
