#ifndef __abstract_ClassTen_ExampleBackendForGAMBIT_1_234_hpp__
#define __abstract_ClassTen_ExampleBackendForGAMBIT_1_234_hpp__

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
    template <typename T>
    class Abstract_ClassTen
    {
      public:
        void pointer_assign__BOSS(Abstract_ClassTen<T>* in);
        Abstract_ClassTen<T>* pointer_copy__BOSS();
    };
  
    template <>
    class Abstract_ClassTen<double> : public virtual AbstractBase
    {
      public:
  
        virtual double pop() =0;
  
        virtual void push(double) =0;
  
        virtual int size() =0;
  
        virtual ClassNamespace::Abstract_ClassTen<double>* operator_plus__BOSS(ClassNamespace::Abstract_ClassTen<double>&) =0;
  
        virtual double& test_ref__BOSS() =0;
  
      public:
        virtual void pointer_assign__BOSS(Abstract_ClassTen<double>*) =0;
        virtual Abstract_ClassTen<double>* pointer_copy__BOSS() =0;
  
      private:
        ClassTen__double* wptr;
        bool delete_wrapper;
      public:
        ClassTen__double* get_wptr() { return wptr; }
        void set_wptr(ClassTen__double* wptr_in) { wptr = wptr_in; }
        bool get_delete_wrapper() { return delete_wrapper; }
        void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
      public:
        Abstract_ClassTen()
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassTen(const Abstract_ClassTen&)
        {
          wptr = 0;
          delete_wrapper = false;
        }
  
        Abstract_ClassTen& operator=(const Abstract_ClassTen&) { return *this; }
  
        virtual void init_wrapper() =0;
  
        ClassTen__double* get_init_wptr()
        {
          init_wrapper();
          return wptr;
        }
  
        ClassTen__double& get_init_wref()
        {
          init_wrapper();
          return *wptr;
        }
  
        virtual ~Abstract_ClassTen() =0;
    };
  
    typedef Abstract_ClassTen<double> Abstract_ClassTen__double;
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"



#endif /* __abstract_ClassTen_ExampleBackendForGAMBIT_1_234_hpp__ */
