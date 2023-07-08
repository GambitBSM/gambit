#ifndef __wrapper_MSSMNoFV_onshell_problems_decl_gm2calc_1_3_0_hpp__
#define __wrapper_MSSMNoFV_onshell_problems_decl_gm2calc_1_3_0_hpp__

#include <cstddef>
#include <string>
#include <ostream>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_MSSMNoFV_onshell_problems.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      class MSSMNoFV_onshell_problems : public WrapperBase
      {
            // Member variables: 
         public:
            // -- Static factory pointers: 
            static Abstract_MSSMNoFV_onshell_problems* (*__factory0)();
      
            // -- Other member variables: 
      
            // Member functions: 
         public:
            void clear();
      
            void clear_problems();
      
            void clear_warnings();
      
            void flag_no_convergence_Mu_MassB_MassWB(double arg_1, unsigned int arg_2);
      
            void flag_no_convergence_me2(double arg_1, unsigned int arg_2);
      
            void flag_tachyon(const std::string& arg_1);
      
            void unflag_no_convergence_Mu_MassB_MassWB();
      
            void unflag_no_convergence_me2();
      
            bool no_Mu_MassB_MassWB_convergence() const;
      
            bool no_me2_convergence() const;
      
            bool have_tachyon() const;
      
            bool have_problem() const;
      
            bool have_warning() const;
      
            ::std::string get_warnings() const;
      
            ::std::string get_problems() const;
      
            void print(std::ostream& arg_1) const;
      
            void print_problems(std::ostream& arg_1) const;
      
            void print_warnings(std::ostream& arg_1) const;
      
      
            // Wrappers for original constructors: 
         public:
            MSSMNoFV_onshell_problems();
      
            // Special pointer-based constructor: 
            MSSMNoFV_onshell_problems(Abstract_MSSMNoFV_onshell_problems* in);
      
            // Copy constructor: 
            MSSMNoFV_onshell_problems(const MSSMNoFV_onshell_problems& in);
      
            // Assignment operator: 
            MSSMNoFV_onshell_problems& operator=(const MSSMNoFV_onshell_problems& in);
      
            // Destructor: 
            ~MSSMNoFV_onshell_problems();
      
            // Returns correctly casted pointer to Abstract class: 
            Abstract_MSSMNoFV_onshell_problems* get_BEptr() const;
      
      };
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_MSSMNoFV_onshell_problems_decl_gm2calc_1_3_0_hpp__ */
