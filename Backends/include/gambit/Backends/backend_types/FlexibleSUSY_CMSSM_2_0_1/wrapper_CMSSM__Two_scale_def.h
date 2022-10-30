#ifndef __wrapper_CMSSM__Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM__Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <string>
#include <ostream>
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void CMSSM__Two_scale::calculate_spectrum()
        {
            get_BEptr()->calculate_spectrum();
        }
        
        inline void CMSSM__Two_scale::clear_problems()
        {
            get_BEptr()->clear_problems();
        }
        
        inline ::std::basic_string<char> CMSSM__Two_scale::name() const
        {
            return get_BEptr()->name();
        }
        
        inline void CMSSM__Two_scale::run_to(double scale, double eps)
        {
            get_BEptr()->run_to(scale, eps);
        }
        
        inline void CMSSM__Two_scale::run_to(double scale)
        {
            get_BEptr()->run_to__BOSS(scale);
        }
        
        inline void CMSSM__Two_scale::print(::std::basic_ostream<char>& out) const
        {
            get_BEptr()->print(out);
        }
        
        inline void CMSSM__Two_scale::print() const
        {
            get_BEptr()->print__BOSS();
        }
        
        inline void CMSSM__Two_scale::set_precision(double arg_1)
        {
            get_BEptr()->set_precision(arg_1);
        }
        
        
        // Wrappers for original constructors: 
        inline CMSSM__Two_scale::CMSSM__Two_scale(const flexiblesusy::CMSSM_input_parameters& input_) :
            Model(__factory0(input_)),
            CMSSM_mass_eigenstates(__factory0(input_))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline CMSSM__Two_scale::CMSSM__Two_scale() :
            Model(__factory1()),
            CMSSM_mass_eigenstates(__factory1())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CMSSM__Two_scale::CMSSM__Two_scale(Abstract_CMSSM__Two_scale* in) :
            Model(in),
            CMSSM_mass_eigenstates(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CMSSM__Two_scale::CMSSM__Two_scale(const CMSSM__Two_scale& in) :
            Model(in.get_BEptr()->pointer_copy__BOSS()),
            CMSSM_mass_eigenstates(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CMSSM__Two_scale& CMSSM__Two_scale::operator=(const CMSSM__Two_scale& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CMSSM__Two_scale::~CMSSM__Two_scale()
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
        inline Abstract_CMSSM__Two_scale* flexiblesusy::CMSSM__Two_scale::get_BEptr() const
        {
            return dynamic_cast<Abstract_CMSSM__Two_scale*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM__Two_scale_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
