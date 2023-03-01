#ifndef __abstract_HL_ProfLikelihood_HepLike_2_0_h__
#define __abstract_HL_ProfLikelihood_HepLike_2_0_h__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class Abstract_HL_ProfLikelihood : public virtual AbstractBase
   {
      public:
   
         virtual Abstract_HL_ProfLikelihood& operator_equal__BOSS(const Abstract_HL_ProfLikelihood&) =0;
   
         virtual void Read() =0;
   
         virtual double GetChi2(double) =0;
   
         virtual double GetChi2(double, double) =0;
   
         virtual double GetLogLikelihood(double) =0;
   
         virtual double GetLogLikelihood(double, double) =0;
   
         virtual double GetLikelihood(double) =0;
   
         virtual double GetLikelihood(double, double) =0;
   
         virtual int& nxbins_ref__BOSS() =0;
   
         virtual double& xmin_ref__BOSS() =0;
   
         virtual double& xmax_ref__BOSS() =0;
   
         virtual double& central_mes_val_ref__BOSS() =0;
   
         virtual std::basic_string<char>& ObsName_ref__BOSS() =0;
   
         virtual std::basic_string<char>& HL_RootFile_ref__BOSS() =0;
   
         virtual std::basic_string<char>& HL_PATH_ref__BOSS() =0;
   
      public:
         virtual void pointer_assign__BOSS(Abstract_HL_ProfLikelihood*) =0;
         virtual Abstract_HL_ProfLikelihood* pointer_copy__BOSS() =0;
   
      private:
         HL_ProfLikelihood* wptr;
         bool delete_wrapper;
      public:
         HL_ProfLikelihood* get_wptr() { return wptr; }
         void set_wptr(HL_ProfLikelihood* wptr_in) { wptr = wptr_in; }
         bool get_delete_wrapper() { return delete_wrapper; }
         void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
      public:
         Abstract_HL_ProfLikelihood()
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_ProfLikelihood(const Abstract_HL_ProfLikelihood&)
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_ProfLikelihood& operator=(const Abstract_HL_ProfLikelihood&) { return *this; }
   
         virtual void init_wrapper() =0;
   
         HL_ProfLikelihood* get_init_wptr()
         {
            init_wrapper();
            return wptr;
         }
   
         HL_ProfLikelihood& get_init_wref()
         {
            init_wrapper();
            return *wptr;
         }
   
         virtual ~Abstract_HL_ProfLikelihood() =0;
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_HL_ProfLikelihood_HepLike_2_0_h__ */
