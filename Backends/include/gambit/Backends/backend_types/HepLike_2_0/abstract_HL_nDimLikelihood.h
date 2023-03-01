#ifndef __abstract_HL_nDimLikelihood_HepLike_2_0_h__
#define __abstract_HL_nDimLikelihood_HepLike_2_0_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <boost/numeric/ublas/matrix.hpp>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class Abstract_HL_nDimLikelihood : public virtual AbstractBase
   {
      public:
   
         virtual Abstract_HL_nDimLikelihood& operator_equal__BOSS(const Abstract_HL_nDimLikelihood&) =0;
   
         virtual void Read() =0;
   
         virtual double GetChi2(::std::vector<double>) =0;
   
         virtual double GetChi2(::std::vector<double>, ::boost::numeric::ublas::matrix<double>) =0;
   
         virtual double GetLikelihood(::std::vector<double>) =0;
   
         virtual double GetLikelihood(::std::vector<double>, ::boost::numeric::ublas::matrix<double>) =0;
   
         virtual double GetLogLikelihood(::std::vector<double>) =0;
   
         virtual double GetLogLikelihood(::std::vector<double>, ::boost::numeric::ublas::matrix<double>) =0;
   
         virtual void Profile(::std::basic_string<char>) =0;
   
         virtual void Profile__BOSS() =0;
   
         virtual double GetChi2_profile(double, ::std::basic_string<char>) =0;
   
         virtual double GetLikelihood_profile(double, ::std::basic_string<char>) =0;
   
         virtual double GetLogLikelihood_profile(double, ::std::basic_string<char>) =0;
   
         virtual ::std::vector<std::basic_string<char>> GetObservables() =0;
   
         virtual double& loglikelihood_penalty_ref__BOSS() =0;
   
         virtual std::basic_string<char>& HL_RootFile_ref__BOSS() =0;
   
         virtual std::basic_string<char>& HL_PATH_ref__BOSS() =0;
   
         virtual std::vector<std::basic_string<char>>& Observables_ref__BOSS() =0;
   
         virtual int& NoOfObservables_ref__BOSS() =0;
   
         virtual int& size_restricted_ref__BOSS() =0;
   
         virtual double& xmin_ref__BOSS() =0;
   
         virtual double& xmax_ref__BOSS() =0;
   
         virtual double& ymin_ref__BOSS() =0;
   
         virtual double& ymax_ref__BOSS() =0;
   
         virtual double& zmin_ref__BOSS() =0;
   
         virtual double& zmax_ref__BOSS() =0;
   
         virtual std::vector<double>& central_mes_val_ref__BOSS() =0;
   
         virtual int& dim_ref__BOSS() =0;
   
         virtual int& n_binsX_ref__BOSS() =0;
   
         virtual int& n_binsY_ref__BOSS() =0;
   
         virtual int& n_binsZ_ref__BOSS() =0;
   
         virtual bool& profiled_ref__BOSS() =0;
   
      public:
         virtual void pointer_assign__BOSS(Abstract_HL_nDimLikelihood*) =0;
         virtual Abstract_HL_nDimLikelihood* pointer_copy__BOSS() =0;
   
      private:
         HL_nDimLikelihood* wptr;
         bool delete_wrapper;
      public:
         HL_nDimLikelihood* get_wptr() { return wptr; }
         void set_wptr(HL_nDimLikelihood* wptr_in) { wptr = wptr_in; }
         bool get_delete_wrapper() { return delete_wrapper; }
         void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
      public:
         Abstract_HL_nDimLikelihood()
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_nDimLikelihood(const Abstract_HL_nDimLikelihood&)
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_nDimLikelihood& operator=(const Abstract_HL_nDimLikelihood&) { return *this; }
   
         virtual void init_wrapper() =0;
   
         HL_nDimLikelihood* get_init_wptr()
         {
            init_wrapper();
            return wptr;
         }
   
         HL_nDimLikelihood& get_init_wref()
         {
            init_wrapper();
            return *wptr;
         }
   
         virtual ~Abstract_HL_nDimLikelihood() =0;
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_HL_nDimLikelihood_HepLike_2_0_h__ */
