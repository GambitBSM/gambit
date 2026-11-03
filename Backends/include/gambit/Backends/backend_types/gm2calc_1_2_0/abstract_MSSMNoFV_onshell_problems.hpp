#ifndef __abstract_MSSMNoFV_onshell_problems_gm2calc_1_2_0_hpp__
#define __abstract_MSSMNoFV_onshell_problems_gm2calc_1_2_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   namespace gm2calc
   {
      class Abstract_MSSMNoFV_onshell_problems : public virtual AbstractBase
      {
         public:
   
            virtual void clear() =0;
   
            virtual void clear_problems() =0;
   
            virtual void clear_warnings() =0;
   
            virtual void flag_no_convergence_Mu_MassB_MassWB(double, unsigned int) =0;
   
            virtual void flag_no_convergence_me2(double, unsigned int) =0;
   
            virtual void flag_tachyon(const std::string&) =0;
   
            virtual void unflag_no_convergence_Mu_MassB_MassWB() =0;
   
            virtual void unflag_no_convergence_me2() =0;
   
            virtual bool have_tachyon() const =0;
   
            virtual bool have_problem() const =0;
   
            virtual bool have_warning() const =0;
   
            virtual ::std::string get_warnings() const =0;
   
            virtual ::std::string get_problems() const =0;
   
            virtual void print(std::ostream&) const =0;
   
            virtual void print_problems(std::ostream&) const =0;
   
            virtual void print_warnings(std::ostream&) const =0;
   
         public:
            virtual void pointer_assign__BOSS(Abstract_MSSMNoFV_onshell_problems*) =0;
            virtual Abstract_MSSMNoFV_onshell_problems* pointer_copy__BOSS() =0;
   
         private:
            MSSMNoFV_onshell_problems* wptr;
            bool delete_wrapper;
         public:
            MSSMNoFV_onshell_problems* get_wptr() { return wptr; }
            void set_wptr(MSSMNoFV_onshell_problems* wptr_in) { wptr = wptr_in; }
            bool get_delete_wrapper() { return delete_wrapper; }
            void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
         public:
            Abstract_MSSMNoFV_onshell_problems()
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_problems(const Abstract_MSSMNoFV_onshell_problems&)
            {
               wptr = 0;
               delete_wrapper = false;
            }
   
            Abstract_MSSMNoFV_onshell_problems& operator=(const Abstract_MSSMNoFV_onshell_problems&) { return *this; }
   
            virtual void init_wrapper() =0;
   
            MSSMNoFV_onshell_problems* get_init_wptr()
            {
               init_wrapper();
               return wptr;
            }
   
            MSSMNoFV_onshell_problems& get_init_wref()
            {
               init_wrapper();
               return *wptr;
            }
   
            virtual ~Abstract_MSSMNoFV_onshell_problems() =0;
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_MSSMNoFV_onshell_problems_gm2calc_1_2_0_hpp__ */
