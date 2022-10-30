#ifndef __abstract_CMSSM_slha_io_FlexibleSUSY_CMSSM_2_0_1_h__
#define __abstract_CMSSM_slha_io_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <ostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_QedQcd_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"
#include "wrapper_CMSSM_mass_eigenstates_decl.h"
#include "wrapper_Spectrum_generator_settings_decl.h"
#include "wrapper_Spectrum_generator_problems_decl.h"

#include "enum_decl_copies.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_CMSSM_slha_io : public virtual AbstractBase
        {
            public:
    
                virtual void clear() =0;
    
                virtual void fill__BOSS(softsusy::Abstract_QedQcd&) const =0;
    
                virtual void fill__BOSS(flexiblesusy::Abstract_CMSSM_input_parameters&) const =0;
    
                virtual void fill__BOSS(flexiblesusy::Abstract_CMSSM_mass_eigenstates&) const =0;
    
                virtual void fill__BOSS(flexiblesusy::Abstract_Spectrum_generator_settings&) const =0;
    
                virtual double get_parameter_output_scale() const =0;
    
                virtual void read_from_file(const ::std::basic_string<char>&) =0;
    
                virtual void read_from_source(const ::std::basic_string<char>&) =0;
    
                virtual void read_from_stream(::std::basic_istream<char>&) =0;
    
                virtual void set_input__BOSS(const flexiblesusy::Abstract_CMSSM_input_parameters&) =0;
    
                virtual void set_settings__BOSS(const flexiblesusy::Abstract_Spectrum_generator_settings&) =0;
    
                virtual void set_sminputs__BOSS(const softsusy::Abstract_QedQcd&) =0;
    
                virtual void set_spinfo__BOSS(const flexiblesusy::Abstract_Spectrum_generator_problems&) =0;
    
                virtual void set_spinfo(const ::std::vector<std::basic_string<char>>&, const ::std::vector<std::basic_string<char>>&) =0;
    
                virtual void set_print_imaginary_parts_of_majorana_mixings(bool) =0;
    
                virtual void write_to(const ::std::basic_string<char>&) const =0;
    
                virtual void write_to_file(const ::std::basic_string<char>&) const =0;
    
                virtual void write_to_stream(::std::basic_ostream<char>&) const =0;
    
                virtual void write_to_stream__BOSS() const =0;
    
                virtual void fill_minpar_tuple__BOSS(flexiblesusy::Abstract_CMSSM_input_parameters&, int, double) =0;
    
                virtual void fill_extpar_tuple__BOSS(flexiblesusy::Abstract_CMSSM_input_parameters&, int, double) =0;
    
                virtual void fill_imminpar_tuple__BOSS(flexiblesusy::Abstract_CMSSM_input_parameters&, int, double) =0;
    
                virtual void fill_imextpar_tuple__BOSS(flexiblesusy::Abstract_CMSSM_input_parameters&, int, double) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_CMSSM_slha_io*) =0;
                virtual Abstract_CMSSM_slha_io* pointer_copy__BOSS() =0;
    
            private:
                CMSSM_slha_io* wptr;
                bool delete_wrapper;
            public:
                CMSSM_slha_io* get_wptr() { return wptr; }
                void set_wptr(CMSSM_slha_io* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CMSSM_slha_io()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_slha_io(const Abstract_CMSSM_slha_io&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CMSSM_slha_io& operator=(const Abstract_CMSSM_slha_io&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CMSSM_slha_io* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CMSSM_slha_io& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CMSSM_slha_io() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CMSSM_slha_io_FlexibleSUSY_CMSSM_2_0_1_h__ */
