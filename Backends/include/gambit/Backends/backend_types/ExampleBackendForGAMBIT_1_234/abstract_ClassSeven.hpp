#ifndef __abstract_ClassSeven_ExampleBackendForGAMBIT_1_234_hpp__
#define __abstract_ClassSeven_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <iostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_ClassThree__double_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template <typename T>
  class Abstract_ClassSeven
  {
    public:
      using Abstract_ClassThree<T>::pointer_assign__BOSS;
      void pointer_assign__BOSS(Abstract_ClassSeven<T>* in);
      Abstract_ClassSeven<T>* pointer_copy__BOSS();
  };
  
  template <>
  class Abstract_ClassSeven<double> : virtual public Abstract_ClassThree<double>
  {
    public:
  
      virtual double pop2() =0;
  
      virtual void push2(double) =0;
  
      virtual int size2() =0;
  
    public:
      using Abstract_ClassThree<double>::pointer_assign__BOSS;
      virtual void pointer_assign__BOSS(Abstract_ClassSeven<double>*) =0;
      virtual Abstract_ClassSeven<double>* pointer_copy__BOSS() =0;
  
    private:
      ClassSeven__double* wptr;
      bool delete_wrapper;
    public:
      ClassSeven__double* get_wptr() { return wptr; }
      void set_wptr(ClassSeven__double* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassSeven()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassSeven(const Abstract_ClassSeven& in) : 
        Abstract_ClassThree<double>(in)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassSeven& operator=(const Abstract_ClassSeven&) { return *this; }
  
      virtual void init_wrapper() =0;
  
      ClassSeven__double* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassSeven__double& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassSeven() =0;
  };
  
  typedef Abstract_ClassSeven<double> Abstract_ClassSeven__double;
  
}


#include "gambit/Backends/backend_undefs.hpp"


#include <cstddef>
#include <iostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_ClassThree__int_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template <>
  class Abstract_ClassSeven<int> : virtual public Abstract_ClassThree<int>
  {
    public:
  
      virtual int pop2() =0;
  
      virtual void push2(int) =0;
  
      virtual int size2() =0;
  
    public:
      using Abstract_ClassThree<int>::pointer_assign__BOSS;
      virtual void pointer_assign__BOSS(Abstract_ClassSeven<int>*) =0;
      virtual Abstract_ClassSeven<int>* pointer_copy__BOSS() =0;
  
    private:
      ClassSeven__int* wptr;
      bool delete_wrapper;
    public:
      ClassSeven__int* get_wptr() { return wptr; }
      void set_wptr(ClassSeven__int* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_ClassSeven()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassSeven(const Abstract_ClassSeven& in) : 
        Abstract_ClassThree<int>(in)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_ClassSeven& operator=(const Abstract_ClassSeven&) { return *this; }
  
      virtual void init_wrapper() =0;
  
      ClassSeven__int* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      ClassSeven__int& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_ClassSeven() =0;
  };
  
  typedef Abstract_ClassSeven<int> Abstract_ClassSeven__int;
  
}


#include "gambit/Backends/backend_undefs.hpp"



#endif /* __abstract_ClassSeven_ExampleBackendForGAMBIT_1_234_hpp__ */
