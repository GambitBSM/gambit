#ifndef __wrapper_EPhysicalProblem_def_gm2calc_1_3_0_hpp__
#define __wrapper_EPhysicalProblem_def_gm2calc_1_3_0_hpp__

#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline ::std::basic_string<char> EPhysicalProblem::what() const
      {
         return get_BEptr()->what();
      }
      
      
      // Wrappers for original constructors: 
      inline EPhysicalProblem::EPhysicalProblem(const ::std::basic_string<char>& message_) :
         Error(__factory0(message_))
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline EPhysicalProblem::EPhysicalProblem(Abstract_EPhysicalProblem* in) :
         Error(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline EPhysicalProblem::EPhysicalProblem(const EPhysicalProblem& in) :
         Error(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline EPhysicalProblem& EPhysicalProblem::operator=(const EPhysicalProblem& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline EPhysicalProblem::~EPhysicalProblem()
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
      inline Abstract_EPhysicalProblem* gm2calc::EPhysicalProblem::get_BEptr() const
      {
         return dynamic_cast<Abstract_EPhysicalProblem*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_EPhysicalProblem_def_gm2calc_1_3_0_hpp__ */
