#ifndef __wrapper_HL_nDimLikelihood_def_HepLike_2_0_h__
#define __wrapper_HL_nDimLikelihood_def_HepLike_2_0_h__

#include <string>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   // Member functions: 
   inline void HL_nDimLikelihood::Read()
   {
      get_BEptr()->Read();
   }
   
   inline double HL_nDimLikelihood::GetChi2(std::vector<double> theory)
   {
      return get_BEptr()->GetChi2(theory);
   }
   
   inline double HL_nDimLikelihood::GetChi2(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov)
   {
      return get_BEptr()->GetChi2(theory, theory_cov);
   }
   
   inline double HL_nDimLikelihood::GetLikelihood(std::vector<double> theory)
   {
      return get_BEptr()->GetLikelihood(theory);
   }
   
   inline double HL_nDimLikelihood::GetLikelihood(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov)
   {
      return get_BEptr()->GetLikelihood(theory, theory_cov);
   }
   
   inline double HL_nDimLikelihood::GetLogLikelihood(std::vector<double> theory)
   {
      return get_BEptr()->GetLogLikelihood(theory);
   }
   
   inline double HL_nDimLikelihood::GetLogLikelihood(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov)
   {
      return get_BEptr()->GetLogLikelihood(theory, theory_cov);
   }
   
   inline void HL_nDimLikelihood::Profile(std::string arg_1)
   {
      get_BEptr()->Profile(arg_1);
   }
   
   inline void HL_nDimLikelihood::Profile()
   {
      get_BEptr()->Profile__BOSS();
   }
   
   inline double HL_nDimLikelihood::GetChi2_profile(double theory, std::string arg_1)
   {
      return get_BEptr()->GetChi2_profile(theory, arg_1);
   }
   
   inline double HL_nDimLikelihood::GetLikelihood_profile(double theory, std::string axis)
   {
      return get_BEptr()->GetLikelihood_profile(theory, axis);
   }
   
   inline double HL_nDimLikelihood::GetLogLikelihood_profile(double theory, std::string X)
   {
      return get_BEptr()->GetLogLikelihood_profile(theory, X);
   }
   
   inline ::std::vector<std::string> HL_nDimLikelihood::GetObservables()
   {
      return get_BEptr()->GetObservables();
   }
   
   
   // Wrappers for original constructors: 
   inline HL_nDimLikelihood::HL_nDimLikelihood() :
      WrapperBase(__factory0()),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS()),
      Observables( get_BEptr()->Observables_ref__BOSS()),
      NoOfObservables( get_BEptr()->NoOfObservables_ref__BOSS()),
      size_restricted( get_BEptr()->size_restricted_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      ymin( get_BEptr()->ymin_ref__BOSS()),
      ymax( get_BEptr()->ymax_ref__BOSS()),
      zmin( get_BEptr()->zmin_ref__BOSS()),
      zmax( get_BEptr()->zmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      dim( get_BEptr()->dim_ref__BOSS()),
      n_binsX( get_BEptr()->n_binsX_ref__BOSS()),
      n_binsY( get_BEptr()->n_binsY_ref__BOSS()),
      n_binsZ( get_BEptr()->n_binsZ_ref__BOSS()),
      profiled( get_BEptr()->profiled_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   inline HL_nDimLikelihood::HL_nDimLikelihood(std::string s) :
      WrapperBase(__factory1(s)),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS()),
      Observables( get_BEptr()->Observables_ref__BOSS()),
      NoOfObservables( get_BEptr()->NoOfObservables_ref__BOSS()),
      size_restricted( get_BEptr()->size_restricted_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      ymin( get_BEptr()->ymin_ref__BOSS()),
      ymax( get_BEptr()->ymax_ref__BOSS()),
      zmin( get_BEptr()->zmin_ref__BOSS()),
      zmax( get_BEptr()->zmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      dim( get_BEptr()->dim_ref__BOSS()),
      n_binsX( get_BEptr()->n_binsX_ref__BOSS()),
      n_binsY( get_BEptr()->n_binsY_ref__BOSS()),
      n_binsZ( get_BEptr()->n_binsZ_ref__BOSS()),
      profiled( get_BEptr()->profiled_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Special pointer-based constructor: 
   inline HL_nDimLikelihood::HL_nDimLikelihood(Abstract_HL_nDimLikelihood* in) :
      WrapperBase(in),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS()),
      Observables( get_BEptr()->Observables_ref__BOSS()),
      NoOfObservables( get_BEptr()->NoOfObservables_ref__BOSS()),
      size_restricted( get_BEptr()->size_restricted_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      ymin( get_BEptr()->ymin_ref__BOSS()),
      ymax( get_BEptr()->ymax_ref__BOSS()),
      zmin( get_BEptr()->zmin_ref__BOSS()),
      zmax( get_BEptr()->zmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      dim( get_BEptr()->dim_ref__BOSS()),
      n_binsX( get_BEptr()->n_binsX_ref__BOSS()),
      n_binsY( get_BEptr()->n_binsY_ref__BOSS()),
      n_binsZ( get_BEptr()->n_binsZ_ref__BOSS()),
      profiled( get_BEptr()->profiled_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Copy constructor: 
   inline HL_nDimLikelihood::HL_nDimLikelihood(const HL_nDimLikelihood& in) :
      WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS()),
      Observables( get_BEptr()->Observables_ref__BOSS()),
      NoOfObservables( get_BEptr()->NoOfObservables_ref__BOSS()),
      size_restricted( get_BEptr()->size_restricted_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      ymin( get_BEptr()->ymin_ref__BOSS()),
      ymax( get_BEptr()->ymax_ref__BOSS()),
      zmin( get_BEptr()->zmin_ref__BOSS()),
      zmax( get_BEptr()->zmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      dim( get_BEptr()->dim_ref__BOSS()),
      n_binsX( get_BEptr()->n_binsX_ref__BOSS()),
      n_binsY( get_BEptr()->n_binsY_ref__BOSS()),
      n_binsZ( get_BEptr()->n_binsZ_ref__BOSS()),
      profiled( get_BEptr()->profiled_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Assignment operator: 
   inline HL_nDimLikelihood& HL_nDimLikelihood::operator=(const HL_nDimLikelihood& in)
   {
      if (this != &in)
      {
         get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
   }
   
   
   // Destructor: 
   inline HL_nDimLikelihood::~HL_nDimLikelihood()
   {
      if (get_BEptr() != 0)
      {
         get_BEptr()->set_delete_wrapper(false);
         if (can_delete_BEptr())
         {
            delete BEptr;
            BEptr = 0;
         }
      }
      set_delete_BEptr(false);
   }
   
   // Returns correctly casted pointer to Abstract class: 
   inline Abstract_HL_nDimLikelihood* HL_nDimLikelihood::get_BEptr() const
   {
      return dynamic_cast<Abstract_HL_nDimLikelihood*>(BEptr);
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_nDimLikelihood_def_HepLike_2_0_h__ */
