#ifndef __abstract_CMSSM_parameter_getter_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_CMSSM_parameter_getter_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM_parameter_getter : public virtual AbstractBase
        {
            public:
    
                virtual ::std::array<std::basic_string<char>, 111> get_parameter_names() const =0;
    
                virtual ::std::array<std::basic_string<char>, 18> get_particle_names() const =0;
    
                virtual ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > get_DRbar_mass_names() const =0;
    
                virtual ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > get_pole_mass_names() const =0;
    
                virtual ::std::array<std::basic_string<char>, 289> get_DRbar_mixing_names() const =0;
    
                virtual ::std::array<std::basic_string<char>, 289> get_pole_mixing_names() const =0;
    
                virtual ::std::array<std::basic_string<char>, 5> get_input_parameter_names() const =0;
    
                virtual ::std::array<std::basic_string<char>, 0> get_extra_parameter_names() const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_CMSSM_parameter_getter*) =0;
                virtual Abstract_CMSSM_parameter_getter* pointer_copy__BOSS() =0;
    
            private:
                CMSSM_parameter_getter* wptr;
                bool delete_wrapper;
            public:
                CMSSM_parameter_getter* get_wptr() { return wptr; }
                void set_wptr(CMSSM_parameter_getter* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM_parameter_getter()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_parameter_getter(const Abstract_CMSSM_parameter_getter&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_parameter_getter& operator=(const Abstract_CMSSM_parameter_getter&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM_parameter_getter* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM_parameter_getter& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM_parameter_getter() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CMSSM_parameter_getter_FlexibleSUSY_CMSSM_2_0_1_h__ */
