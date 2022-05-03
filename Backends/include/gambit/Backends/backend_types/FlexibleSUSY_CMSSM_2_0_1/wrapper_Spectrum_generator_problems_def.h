#ifndef __wrapper_Spectrum_generator_problems_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Spectrum_generator_problems_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <vector>
#include <string>
#include <ostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void Spectrum_generator_problems::clear()
        {
            get_BEptr()->clear();
        }
        
        inline bool Spectrum_generator_problems::have_problem() const
        {
            return get_BEptr()->have_problem();
        }
        
        inline bool Spectrum_generator_problems::have_warning() const
        {
            return get_BEptr()->have_warning();
        }
        
        inline ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > Spectrum_generator_problems::get_problem_strings() const
        {
            return get_BEptr()->get_problem_strings();
        }
        
        inline ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > Spectrum_generator_problems::get_warning_strings() const
        {
            return get_BEptr()->get_warning_strings();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Spectrum_generator_problems::get_problem_string() const
        {
            return get_BEptr()->get_problem_string();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Spectrum_generator_problems::get_warning_string() const
        {
            return get_BEptr()->get_warning_string();
        }
        
        inline void Spectrum_generator_problems::print_problems(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const
        {
            get_BEptr()->print_problems(arg_1);
        }
        
        inline void Spectrum_generator_problems::print_problems() const
        {
            get_BEptr()->print_problems__BOSS();
        }
        
        inline void Spectrum_generator_problems::print_warnings(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const
        {
            get_BEptr()->print_warnings(arg_1);
        }
        
        inline void Spectrum_generator_problems::print_warnings() const
        {
            get_BEptr()->print_warnings__BOSS();
        }
        
        inline int Spectrum_generator_problems::get_number_of_models() const
        {
            return get_BEptr()->get_number_of_models();
        }
        
        inline int Spectrum_generator_problems::get_number_of_bvp_solvers() const
        {
            return get_BEptr()->get_number_of_bvp_solvers();
        }
        
        inline void Spectrum_generator_problems::flag_no_convergence()
        {
            get_BEptr()->flag_no_convergence();
        }
        
        inline void Spectrum_generator_problems::unflag_no_convergence()
        {
            get_BEptr()->unflag_no_convergence();
        }
        
        inline bool Spectrum_generator_problems::no_convergence() const
        {
            return get_BEptr()->no_convergence();
        }
        
        
        // Wrappers for original constructors: 
        inline Spectrum_generator_problems::Spectrum_generator_problems() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Spectrum_generator_problems::Spectrum_generator_problems(Abstract_Spectrum_generator_problems* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Spectrum_generator_problems::Spectrum_generator_problems(const Spectrum_generator_problems& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Spectrum_generator_problems& Spectrum_generator_problems::operator=(const Spectrum_generator_problems& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Spectrum_generator_problems::~Spectrum_generator_problems()
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
        inline Abstract_Spectrum_generator_problems* flexiblesusy::Spectrum_generator_problems::get_BEptr() const
        {
            return dynamic_cast<Abstract_Spectrum_generator_problems*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Spectrum_generator_problems_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
