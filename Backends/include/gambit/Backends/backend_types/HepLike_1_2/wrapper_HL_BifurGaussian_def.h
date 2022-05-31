#ifndef __wrapper_HL_BifurGaussian_def_HepLike_1_2_h__
#define __wrapper_HL_BifurGaussian_def_HepLike_1_2_h__

#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   // Member functions: 
   inline void HL_BifurGaussian::Read()
   {
      get_BEptr()->Read();
   }
   
   inline double HL_BifurGaussian::GetChi2(double theory, double theory_err)
   {
      return get_BEptr()->GetChi2(theory, theory_err);
   }
   
   inline double HL_BifurGaussian::GetChi2(double theory)
   {
      return get_BEptr()->GetChi2__BOSS(theory);
   }
   
   inline double HL_BifurGaussian::GetLikelihood(double theory, double theory_err)
   {
      return get_BEptr()->GetLikelihood(theory, theory_err);
   }
   
   inline double HL_BifurGaussian::GetLikelihood(double theory)
   {
      return get_BEptr()->GetLikelihood__BOSS(theory);
   }
   
   inline double HL_BifurGaussian::GetLogLikelihood(double theory, double theory_err)
   {
      return get_BEptr()->GetLogLikelihood(theory, theory_err);
   }
   
   inline double HL_BifurGaussian::GetLogLikelihood(double theory)
   {
      return get_BEptr()->GetLogLikelihood__BOSS(theory);
   }
   
   
   // Wrappers for original constructors: 
   inline HL_BifurGaussian::HL_BifurGaussian() :
      HL_Gaussian(__factory0())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   inline HL_BifurGaussian::HL_BifurGaussian(::std::basic_string<char> s) :
      HL_Gaussian(__factory1(s))
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Special pointer-based constructor: 
   inline HL_BifurGaussian::HL_BifurGaussian(Abstract_HL_BifurGaussian* in) :
      HL_Gaussian(in)
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Copy constructor: 
   inline HL_BifurGaussian::HL_BifurGaussian(const HL_BifurGaussian& in) :
      HL_Gaussian(in.get_BEptr()->pointer_copy__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Assignment operator: 
   inline HL_BifurGaussian& HL_BifurGaussian::operator=(const HL_BifurGaussian& in)
   {
      if (this != &in)
      {
         get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
   }
   
   
   // Destructor: 
   inline HL_BifurGaussian::~HL_BifurGaussian()
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
   inline Abstract_HL_BifurGaussian* HL_BifurGaussian::get_BEptr() const
   {
      return dynamic_cast<Abstract_HL_BifurGaussian*>(BEptr);
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_BifurGaussian_def_HepLike_1_2_h__ */
