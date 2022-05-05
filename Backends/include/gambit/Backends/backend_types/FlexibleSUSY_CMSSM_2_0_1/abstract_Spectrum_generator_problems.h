#ifndef __abstract_Spectrum_generator_problems_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_Spectrum_generator_problems_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Spectrum_generator_problems : public virtual AbstractBase
        {
            public:
    
                virtual void clear() =0;
    
                virtual bool have_problem() const =0;
    
                virtual bool have_warning() const =0;
    
                virtual ::std::vector<std::basic_string<char>> get_problem_strings() const =0;
    
                virtual ::std::vector<std::basic_string<char>> get_warning_strings() const =0;
    
                virtual ::std::basic_string<char> get_problem_string() const =0;
    
                virtual ::std::basic_string<char> get_warning_string() const =0;
    
                virtual void print_problems(::std::basic_ostream<char>&) const =0;
    
                virtual void print_problems__BOSS() const =0;
    
                virtual void print_warnings(::std::basic_ostream<char>&) const =0;
    
                virtual void print_warnings__BOSS() const =0;
    
                virtual int get_number_of_models() const =0;
    
                virtual int get_number_of_bvp_solvers() const =0;
    
                virtual void flag_no_convergence() =0;
    
                virtual void unflag_no_convergence() =0;
    
                virtual bool no_convergence() const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Spectrum_generator_problems*) =0;
                virtual Abstract_Spectrum_generator_problems* pointer_copy__BOSS() =0;
    
            private:
                Spectrum_generator_problems* wptr;
                bool delete_wrapper;
            public:
                Spectrum_generator_problems* get_wptr() { return wptr; }
                void set_wptr(Spectrum_generator_problems* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Spectrum_generator_problems()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Spectrum_generator_problems(const Abstract_Spectrum_generator_problems&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Spectrum_generator_problems& operator=(const Abstract_Spectrum_generator_problems&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Spectrum_generator_problems* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Spectrum_generator_problems& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Spectrum_generator_problems() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Spectrum_generator_problems_FlexibleSUSY_CMSSM_2_0_1_h__ */
