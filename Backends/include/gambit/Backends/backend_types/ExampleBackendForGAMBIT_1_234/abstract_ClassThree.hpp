#ifndef __abstract_ClassThree_ExampleBackendForGAMBIT_1_234_hpp__
#define __abstract_ClassThree_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <iostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template <typename T>
  class Abstract_ClassThree
  {
    public:
      void pointer_assign__BOSS(Abstract_ClassThree<T>* in);
      Abstract_ClassThree<T>* pointer_copy__BOSS();
  };
  
  template <>
  class Abstract_ClassThree<double> : public virtual AbstractBase
  {
    public:
  
      virtual double pop() =0;
  
      virtual void push(double) =0;
  
      virtual int size() =0;
  
      virtual Abstract_ClassThree<double>* operator_plus__BOSS(Abstract_ClassThree<double>&) =0;
  
      virtual double& test_ref__BOSS() =0;
  
    public:
      virtual void pointer_assign__BOSS(Abstract_ClassThree<double>*) =0;
      virtual Abstract_ClassThree<double>* pointer_copy__BOSS() =0;
  
    private:
      ClassThree__double* wptr;
      bool delete_wrapper;
    public:
      ClassThree__double* get_wptr() { return wptr; }
      void set_wptr(ClassThree__double* wptr_in) { wptr = wptr_in; }
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
  
      virtual void init_wrapper() =0;
  
      ClassThree__double* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassThree__double& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassThree() =0;
  };
  
  typedef Abstract_ClassThree<double> Abstract_ClassThree__double;
  
}


#include "gambit/Backends/backend_undefs.hpp"


#include <cstddef>
#include <iostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template <>
  class Abstract_ClassThree<int> : public virtual AbstractBase
  {
    public:
  
      virtual int pop() =0;
  
      virtual void push(int) =0;
  
      virtual int size() =0;
  
      virtual Abstract_ClassThree<int>* operator_plus__BOSS(Abstract_ClassThree<int>&) =0;
  
      virtual int& test_ref__BOSS() =0;
  
    public:
      virtual void pointer_assign__BOSS(Abstract_ClassThree<int>*) =0;
      virtual Abstract_ClassThree<int>* pointer_copy__BOSS() =0;
  
    private:
      ClassThree__int* wptr;
      bool delete_wrapper;
    public:
      ClassThree__int* get_wptr() { return wptr; }
      void set_wptr(ClassThree__int* wptr_in) { wptr = wptr_in; }
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
  
      virtual void init_wrapper() =0;
  
      ClassThree__int* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassThree__int& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassThree() =0;
  };
  
  typedef Abstract_ClassThree<int> Abstract_ClassThree__int;
  
}


#include "gambit/Backends/backend_undefs.hpp"



#endif /* __abstract_ClassThree_ExampleBackendForGAMBIT_1_234_hpp__ */
