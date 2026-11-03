#ifndef __abstract_HL_Gaussian_HepLike_2_0_h__
#define __abstract_HL_Gaussian_HepLike_2_0_h__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class Abstract_HL_Gaussian : public virtual AbstractBase
   {
      public:
   
         virtual void Read() =0;
   
         virtual double GetChi2(double, double) =0;
   
         virtual double GetChi2__BOSS(double) =0;
   
         virtual double GetLikelihood(double, double) =0;
   
         virtual double GetLikelihood__BOSS(double) =0;
   
         virtual double GetLogLikelihood(double, double) =0;
   
         virtual double GetLogLikelihood__BOSS(double) =0;
   
      public:
         virtual void pointer_assign__BOSS(Abstract_HL_Gaussian*) =0;
         virtual Abstract_HL_Gaussian* pointer_copy__BOSS() =0;
   
      private:
         HL_Gaussian* wptr;
         bool delete_wrapper;
      public:
         HL_Gaussian* get_wptr() { return wptr; }
         void set_wptr(HL_Gaussian* wptr_in) { wptr = wptr_in; }
         bool get_delete_wrapper() { return delete_wrapper; }
         void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
      public:
         Abstract_HL_Gaussian()
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_Gaussian(const Abstract_HL_Gaussian&)
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_Gaussian& operator=(const Abstract_HL_Gaussian&) { return *this; }
   
         virtual void init_wrapper() =0;
   
         HL_Gaussian* get_init_wptr()
         {
            init_wrapper();
            return wptr;
         }
   
         HL_Gaussian& get_init_wref()
         {
            init_wrapper();
            return *wptr;
         }
   
         virtual ~Abstract_HL_Gaussian() =0;
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_HL_Gaussian_HepLike_2_0_h__ */
