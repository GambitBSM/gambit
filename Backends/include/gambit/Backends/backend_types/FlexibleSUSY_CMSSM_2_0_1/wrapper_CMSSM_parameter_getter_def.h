#ifndef __wrapper_CMSSM_parameter_getter_def_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_parameter_getter_def_FlexibleSUSY_CMSSM_2_0_1_h__

#include <string>
#include <vector>
#include <array>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline ::std::array<std::basic_string<char>, 111> CMSSM_parameter_getter::get_parameter_names() const
        {
            return get_BEptr()->get_parameter_names();
        }
        
        inline ::std::array<std::basic_string<char>, 18> CMSSM_parameter_getter::get_particle_names() const
        {
            return get_BEptr()->get_particle_names();
        }
        
        inline ::std::vector<std::basic_string<char>> CMSSM_parameter_getter::get_DRbar_mass_names() const
        {
            return get_BEptr()->get_DRbar_mass_names();
        }
        
        inline ::std::vector<std::basic_string<char>> CMSSM_parameter_getter::get_pole_mass_names() const
        {
            return get_BEptr()->get_pole_mass_names();
        }
        
        inline ::std::array<std::basic_string<char>, 289> CMSSM_parameter_getter::get_DRbar_mixing_names() const
        {
            return get_BEptr()->get_DRbar_mixing_names();
        }
        
        inline ::std::array<std::basic_string<char>, 289> CMSSM_parameter_getter::get_pole_mixing_names() const
        {
            return get_BEptr()->get_pole_mixing_names();
        }
        
        inline ::std::array<std::basic_string<char>, 5> CMSSM_parameter_getter::get_input_parameter_names() const
        {
            return get_BEptr()->get_input_parameter_names();
        }
        
        inline ::std::array<std::basic_string<char>, 0> CMSSM_parameter_getter::get_extra_parameter_names() const
        {
            return get_BEptr()->get_extra_parameter_names();
        }
        
        
        // Wrappers for original constructors: 
        inline CMSSM_parameter_getter::CMSSM_parameter_getter() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline CMSSM_parameter_getter::CMSSM_parameter_getter(Abstract_CMSSM_parameter_getter* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline CMSSM_parameter_getter::CMSSM_parameter_getter(const CMSSM_parameter_getter& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline CMSSM_parameter_getter& CMSSM_parameter_getter::operator=(const CMSSM_parameter_getter& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline CMSSM_parameter_getter::~CMSSM_parameter_getter()
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
        inline Abstract_CMSSM_parameter_getter* flexiblesusy::CMSSM_parameter_getter::get_BEptr() const
        {
            return dynamic_cast<Abstract_CMSSM_parameter_getter*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_parameter_getter_def_FlexibleSUSY_CMSSM_2_0_1_h__ */
