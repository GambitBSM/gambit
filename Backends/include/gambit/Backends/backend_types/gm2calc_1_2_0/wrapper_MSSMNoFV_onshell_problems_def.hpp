#ifndef __wrapper_MSSMNoFV_onshell_problems_def_gm2calc_1_2_0_hpp__
#define __wrapper_MSSMNoFV_onshell_problems_def_gm2calc_1_2_0_hpp__

#include <string>
#include <ostream>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline void MSSMNoFV_onshell_problems::clear()
      {
         get_BEptr()->clear();
      }
      
      inline void MSSMNoFV_onshell_problems::clear_problems()
      {
         get_BEptr()->clear_problems();
      }
      
      inline void MSSMNoFV_onshell_problems::clear_warnings()
      {
         get_BEptr()->clear_warnings();
      }
      
      inline void MSSMNoFV_onshell_problems::flag_no_convergence_Mu_MassB_MassWB(double arg_1, unsigned int arg_2)
      {
         get_BEptr()->flag_no_convergence_Mu_MassB_MassWB(arg_1, arg_2);
      }
      
      inline void MSSMNoFV_onshell_problems::flag_no_convergence_me2(double arg_1, unsigned int arg_2)
      {
         get_BEptr()->flag_no_convergence_me2(arg_1, arg_2);
      }
      
      inline void MSSMNoFV_onshell_problems::flag_tachyon(const ::std::basic_string<char>& arg_1)
      {
         get_BEptr()->flag_tachyon(arg_1);
      }
      
      inline void MSSMNoFV_onshell_problems::unflag_no_convergence_Mu_MassB_MassWB()
      {
         get_BEptr()->unflag_no_convergence_Mu_MassB_MassWB();
      }
      
      inline void MSSMNoFV_onshell_problems::unflag_no_convergence_me2()
      {
         get_BEptr()->unflag_no_convergence_me2();
      }
      
      inline bool MSSMNoFV_onshell_problems::have_tachyon() const
      {
         return get_BEptr()->have_tachyon();
      }
      
      inline bool MSSMNoFV_onshell_problems::have_problem() const
      {
         return get_BEptr()->have_problem();
      }
      
      inline bool MSSMNoFV_onshell_problems::have_warning() const
      {
         return get_BEptr()->have_warning();
      }
      
      inline ::std::basic_string<char> MSSMNoFV_onshell_problems::get_warnings() const
      {
         return get_BEptr()->get_warnings();
      }
      
      inline ::std::basic_string<char> MSSMNoFV_onshell_problems::get_problems() const
      {
         return get_BEptr()->get_problems();
      }
      
      inline void MSSMNoFV_onshell_problems::print(::std::basic_ostream<char>& arg_1) const
      {
         get_BEptr()->print(arg_1);
      }
      
      inline void MSSMNoFV_onshell_problems::print_problems(::std::basic_ostream<char>& arg_1) const
      {
         get_BEptr()->print_problems(arg_1);
      }
      
      inline void MSSMNoFV_onshell_problems::print_warnings(::std::basic_ostream<char>& arg_1) const
      {
         get_BEptr()->print_warnings(arg_1);
      }
      
      
      // Wrappers for original constructors: 
      inline MSSMNoFV_onshell_problems::MSSMNoFV_onshell_problems() :
         WrapperBase(__factory0())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline MSSMNoFV_onshell_problems::MSSMNoFV_onshell_problems(Abstract_MSSMNoFV_onshell_problems* in) :
         WrapperBase(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline MSSMNoFV_onshell_problems::MSSMNoFV_onshell_problems(const MSSMNoFV_onshell_problems& in) :
         WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline MSSMNoFV_onshell_problems& MSSMNoFV_onshell_problems::operator=(const MSSMNoFV_onshell_problems& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline MSSMNoFV_onshell_problems::~MSSMNoFV_onshell_problems()
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
      inline Abstract_MSSMNoFV_onshell_problems* gm2calc::MSSMNoFV_onshell_problems::get_BEptr() const
      {
         return dynamic_cast<Abstract_MSSMNoFV_onshell_problems*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_problems_def_gm2calc_1_2_0_hpp__ */
