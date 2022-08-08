#ifndef __wrapper_HL_ExpPoints_def_HepLike_1_2_h__
#define __wrapper_HL_ExpPoints_def_HepLike_1_2_h__

#include <string>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   // Member functions: 
   inline void HL_ExpPoints::Read()
   {
      get_BEptr()->Read();
   }
   
   inline double HL_ExpPoints::GetChi2(::std::vector<double> theory)
   {
      return get_BEptr()->GetChi2(theory);
   }
   
   inline double HL_ExpPoints::GetLogLikelihood(::std::vector<double> theory)
   {
      return get_BEptr()->GetLogLikelihood(theory);
   }
   
   inline double HL_ExpPoints::GetLikelihood(::std::vector<double> theory)
   {
      return get_BEptr()->GetLikelihood(theory);
   }
   
   inline bool HL_ExpPoints::InitData()
   {
      return get_BEptr()->InitData();
   }
   
   
   // Wrappers for original constructors: 
   inline HL_ExpPoints::HL_ExpPoints() :
      HL_Data(__factory0())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   inline HL_ExpPoints::HL_ExpPoints(::std::basic_string<char> s) :
      HL_Data(__factory1(s))
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Special pointer-based constructor: 
   inline HL_ExpPoints::HL_ExpPoints(Abstract_HL_ExpPoints* in) :
      HL_Data(in)
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Copy constructor: 
   inline HL_ExpPoints::HL_ExpPoints(const HL_ExpPoints& in) :
      HL_Data(in.get_BEptr()->pointer_copy__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Assignment operator: 
   inline HL_ExpPoints& HL_ExpPoints::operator=(const HL_ExpPoints& in)
   {
      if (this != &in)
      {
         get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
   }
   
   
   // Destructor: 
   inline HL_ExpPoints::~HL_ExpPoints()
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
   inline Abstract_HL_ExpPoints* HL_ExpPoints::get_BEptr() const
   {
      return dynamic_cast<Abstract_HL_ExpPoints*>(BEptr);
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_ExpPoints_def_HepLike_1_2_h__ */
