#ifndef __wrapper_Spectrum_generator_problems_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_Spectrum_generator_problems_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Spectrum_generator_problems.h"
#include <vector>
#include <string>
#include <ostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Spectrum_generator_problems : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_Spectrum_generator_problems* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void clear();
        
                bool have_problem() const;
        
                bool have_warning() const;
        
                ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > get_problem_strings() const;
        
                ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > get_warning_strings() const;
        
                ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > get_problem_string(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& sep) const;
        
                ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > get_problem_string() const;
        
                ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > get_warning_string(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& sep) const;
        
                ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > get_warning_string() const;
        
                void print_problems(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const;
        
                void print_problems() const;
        
                void print_warnings(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const;
        
                void print_warnings() const;
        
                int get_number_of_models() const;
        
                int get_number_of_bvp_solvers() const;
        
                void flag_no_convergence();
        
                void unflag_no_convergence();
        
                bool no_convergence() const;
        
        
                // Wrappers for original constructors: 
            public:
                Spectrum_generator_problems();
        
                // Special pointer-based constructor: 
                Spectrum_generator_problems(flexiblesusy::Abstract_Spectrum_generator_problems* in);
        
                // Copy constructor: 
                Spectrum_generator_problems(const Spectrum_generator_problems& in);
        
                // Assignment operator: 
                Spectrum_generator_problems& operator=(const Spectrum_generator_problems& in);
        
                // Destructor: 
                ~Spectrum_generator_problems();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_Spectrum_generator_problems* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Spectrum_generator_problems_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
