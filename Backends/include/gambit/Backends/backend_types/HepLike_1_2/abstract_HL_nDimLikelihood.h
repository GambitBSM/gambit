#ifndef __abstract_HL_nDimLikelihood_HepLike_1_2_h__
#define __abstract_HL_nDimLikelihood_HepLike_1_2_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_HL_Data_decl.h"
#include <boost/numeric/ublas/matrix.hpp>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class Abstract_HL_nDimLikelihood : virtual public Abstract_HL_Data
   {
      public:
   
         virtual void Read() =0;
   
         virtual double GetChi2(::std::vector<double>) =0;
   
         virtual double GetChi2(::std::vector<double>, ::boost::numeric::ublas::matrix<double>) =0;
   
         virtual double GetLikelihood(::std::vector<double>) =0;
   
         virtual double GetLikelihood(::std::vector<double>, ::boost::numeric::ublas::matrix<double>) =0;
   
         virtual double GetLogLikelihood(::std::vector<double>) =0;
   
         virtual double GetLogLikelihood(::std::vector<double>, ::boost::numeric::ublas::matrix<double>) =0;
   
         virtual void Profile() =0;
   
         virtual double GetChi2_profile(double, ::std::basic_string<char>) =0;
   
         virtual double GetLikelihood_profile(double, ::std::basic_string<char>) =0;
   
         virtual double GetLogLikelihood_profile(double, ::std::basic_string<char>) =0;
   
         virtual ::std::vector<std::basic_string<char>> GetObservables() =0;
   
         virtual double& loglikelihood_penalty_ref__BOSS() =0;
   
      public:
         using Abstract_HL_Data::pointer_assign__BOSS;
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
   
         Abstract_HL_nDimLikelihood(const Abstract_HL_nDimLikelihood& in) : 
            Abstract_HL_Data(in)
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


#endif /* __abstract_HL_nDimLikelihood_HepLike_1_2_h__ */
