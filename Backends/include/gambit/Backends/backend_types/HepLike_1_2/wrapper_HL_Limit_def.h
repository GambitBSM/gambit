#ifndef __wrapper_HL_Limit_def_HepLike_1_2_h__
#define __wrapper_HL_Limit_def_HepLike_1_2_h__

#include <string>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   // Member functions: 
   inline void HL_Limit::Read()
   {
      get_BEptr()->Read();
   }
   
   inline double HL_Limit::GetChi2(double arg_1)
   {
      return get_BEptr()->GetChi2(arg_1);
   }
   
   inline double HL_Limit::GetLogLikelihood(double arg_1)
   {
      return get_BEptr()->GetLogLikelihood(arg_1);
   }
   
   inline double HL_Limit::GetLikelihood(double arg_1)
   {
      return get_BEptr()->GetLikelihood(arg_1);
   }
   
   inline double HL_Limit::GetCLs(double val)
   {
      return get_BEptr()->GetCLs(val);
   }
   
   
   // Wrappers for original constructors: 
   inline HL_Limit::HL_Limit() :
      HL_Data(__factory0())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   inline HL_Limit::HL_Limit(::std::basic_string<char> s) :
      HL_Data(__factory1(s))
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Special pointer-based constructor: 
   inline HL_Limit::HL_Limit(Abstract_HL_Limit* in) :
      HL_Data(in)
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Copy constructor: 
   inline HL_Limit::HL_Limit(const HL_Limit& in) :
      HL_Data(in.get_BEptr()->pointer_copy__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Assignment operator: 
   inline HL_Limit& HL_Limit::operator=(const HL_Limit& in)
   {
      if (this != &in)
      {
         get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
   }
   
   
   // Destructor: 
   inline HL_Limit::~HL_Limit()
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
   inline Abstract_HL_Limit* HL_Limit::get_BEptr() const
   {
      return dynamic_cast<Abstract_HL_Limit*>(BEptr);
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_Limit_def_HepLike_1_2_h__ */
