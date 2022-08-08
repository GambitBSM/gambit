#ifndef __wrapper_HL_nDimLikelihood_def_HepLike_1_2_h__
#define __wrapper_HL_nDimLikelihood_def_HepLike_1_2_h__

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
   
   inline double HL_nDimLikelihood::GetChi2(::std::vector<double> theory)
   {
      return get_BEptr()->GetChi2(theory);
   }
   
   inline double HL_nDimLikelihood::GetChi2(::std::vector<double> theory, ::boost::numeric::ublas::matrix<double> theory_cov)
   {
      return get_BEptr()->GetChi2(theory, theory_cov);
   }
   
   inline double HL_nDimLikelihood::GetLikelihood(::std::vector<double> theory)
   {
      return get_BEptr()->GetLikelihood(theory);
   }
   
   inline double HL_nDimLikelihood::GetLikelihood(::std::vector<double> theory, ::boost::numeric::ublas::matrix<double> theory_cov)
   {
      return get_BEptr()->GetLikelihood(theory, theory_cov);
   }
   
   inline double HL_nDimLikelihood::GetLogLikelihood(::std::vector<double> theory)
   {
      return get_BEptr()->GetLogLikelihood(theory);
   }
   
   inline double HL_nDimLikelihood::GetLogLikelihood(::std::vector<double> theory, ::boost::numeric::ublas::matrix<double> theory_cov)
   {
      return get_BEptr()->GetLogLikelihood(theory, theory_cov);
   }
   
   inline void HL_nDimLikelihood::Profile()
   {
      get_BEptr()->Profile();
   }
   
   inline double HL_nDimLikelihood::GetChi2_profile(double theory, ::std::basic_string<char> arg_1)
   {
      return get_BEptr()->GetChi2_profile(theory, arg_1);
   }
   
   inline double HL_nDimLikelihood::GetLikelihood_profile(double theory, ::std::basic_string<char> axis)
   {
      return get_BEptr()->GetLikelihood_profile(theory, axis);
   }
   
   inline double HL_nDimLikelihood::GetLogLikelihood_profile(double theory, ::std::basic_string<char> X)
   {
      return get_BEptr()->GetLogLikelihood_profile(theory, X);
   }
   
   inline ::std::vector<std::basic_string<char>> HL_nDimLikelihood::GetObservables()
   {
      return get_BEptr()->GetObservables();
   }
   
   
   // Wrappers for original constructors: 
   inline HL_nDimLikelihood::HL_nDimLikelihood() :
      HL_Data(__factory0()),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   inline HL_nDimLikelihood::HL_nDimLikelihood(::std::basic_string<char> s) :
      HL_Data(__factory1(s)),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Special pointer-based constructor: 
   inline HL_nDimLikelihood::HL_nDimLikelihood(Abstract_HL_nDimLikelihood* in) :
      HL_Data(in),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Copy constructor: 
   inline HL_nDimLikelihood::HL_nDimLikelihood(const HL_nDimLikelihood& in) :
      HL_Data(in.get_BEptr()->pointer_copy__BOSS()),
      loglikelihood_penalty( get_BEptr()->loglikelihood_penalty_ref__BOSS())
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

#endif /* __wrapper_HL_nDimLikelihood_def_HepLike_1_2_h__ */
