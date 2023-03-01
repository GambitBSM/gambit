#ifndef __wrapper_HL_ProfLikelihood_def_HepLike_2_0_h__
#define __wrapper_HL_ProfLikelihood_def_HepLike_2_0_h__

#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   // Member functions: 
   inline void HL_ProfLikelihood::Read()
   {
      get_BEptr()->Read();
   }
   
   inline double HL_ProfLikelihood::GetChi2(double theory)
   {
      return get_BEptr()->GetChi2(theory);
   }
   
   inline double HL_ProfLikelihood::GetChi2(double theory, double theory_err)
   {
      return get_BEptr()->GetChi2(theory, theory_err);
   }
   
   inline double HL_ProfLikelihood::GetLogLikelihood(double theory)
   {
      return get_BEptr()->GetLogLikelihood(theory);
   }
   
   inline double HL_ProfLikelihood::GetLogLikelihood(double theory, double theory_err)
   {
      return get_BEptr()->GetLogLikelihood(theory, theory_err);
   }
   
   inline double HL_ProfLikelihood::GetLikelihood(double theory)
   {
      return get_BEptr()->GetLikelihood(theory);
   }
   
   inline double HL_ProfLikelihood::GetLikelihood(double theory, double theory_err)
   {
      return get_BEptr()->GetLikelihood(theory, theory_err);
   }
   
   
   // Wrappers for original constructors: 
   inline HL_ProfLikelihood::HL_ProfLikelihood() :
      WrapperBase(__factory0()),
      nxbins( get_BEptr()->nxbins_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      ObsName( get_BEptr()->ObsName_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   inline HL_ProfLikelihood::HL_ProfLikelihood(::std::basic_string<char> s) :
      WrapperBase(__factory1(s)),
      nxbins( get_BEptr()->nxbins_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      ObsName( get_BEptr()->ObsName_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Special pointer-based constructor: 
   inline HL_ProfLikelihood::HL_ProfLikelihood(Abstract_HL_ProfLikelihood* in) :
      WrapperBase(in),
      nxbins( get_BEptr()->nxbins_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      ObsName( get_BEptr()->ObsName_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Copy constructor: 
   inline HL_ProfLikelihood::HL_ProfLikelihood(const HL_ProfLikelihood& in) :
      WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
      nxbins( get_BEptr()->nxbins_ref__BOSS()),
      xmin( get_BEptr()->xmin_ref__BOSS()),
      xmax( get_BEptr()->xmax_ref__BOSS()),
      central_mes_val( get_BEptr()->central_mes_val_ref__BOSS()),
      ObsName( get_BEptr()->ObsName_ref__BOSS()),
      HL_RootFile( get_BEptr()->HL_RootFile_ref__BOSS()),
      HL_PATH( get_BEptr()->HL_PATH_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Assignment operator: 
   inline HL_ProfLikelihood& HL_ProfLikelihood::operator=(const HL_ProfLikelihood& in)
   {
      if (this != &in)
      {
         get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
   }
   
   
   // Destructor: 
   inline HL_ProfLikelihood::~HL_ProfLikelihood()
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
   inline Abstract_HL_ProfLikelihood* HL_ProfLikelihood::get_BEptr() const
   {
      return dynamic_cast<Abstract_HL_ProfLikelihood*>(BEptr);
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_ProfLikelihood_def_HepLike_2_0_h__ */
