#ifndef __wrapper_CMSSM_slha_io_def_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_CMSSM_slha_io_def_FlexibleSUSY_CMSSM_2_4_0_h__

#include "wrapper_QedQcd_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"
#include "wrapper_Physical_input_decl.h"
#include "wrapper_Spectrum_generator_settings_decl.h"
#include <string>
#include <istream>
#include <vector>
#include "wrapper_Spectrum_generator_problems_decl.h"
#include <ostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline void CMSSM_slha_io::clear()
        {
            get_BEptr()->clear();
        }
        
        inline void CMSSM_slha_io::fill(softsusy::QedQcd& qedqcd) const
        {
            get_BEptr()->fill__BOSS(*qedqcd.get_BEptr());
        }
        
        inline void CMSSM_slha_io::fill(flexiblesusy::CMSSM_input_parameters& arg_1) const
        {
            get_BEptr()->fill__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_slha_io::fill(flexiblesusy::Physical_input& arg_1) const
        {
            get_BEptr()->fill__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_slha_io::fill(flexiblesusy::Spectrum_generator_settings& arg_1) const
        {
            get_BEptr()->fill__BOSS(*arg_1.get_BEptr());
        }
        
        inline double CMSSM_slha_io::get_parameter_output_scale() const
        {
            return get_BEptr()->get_parameter_output_scale();
        }
        
        inline void CMSSM_slha_io::read_from_file(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& arg_1)
        {
            get_BEptr()->read_from_file(arg_1);
        }
        
        inline void CMSSM_slha_io::read_from_source(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& arg_1)
        {
            get_BEptr()->read_from_source(arg_1);
        }
        
        inline void CMSSM_slha_io::read_from_stream(::std::basic_istream<char, std::char_traits<char> >& arg_1)
        {
            get_BEptr()->read_from_stream(arg_1);
        }
        
        inline void CMSSM_slha_io::set_input(const flexiblesusy::CMSSM_input_parameters& arg_1)
        {
            get_BEptr()->set_input__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_slha_io::set_physical_input(const flexiblesusy::Physical_input& arg_1)
        {
            get_BEptr()->set_physical_input__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_slha_io::set_settings(const flexiblesusy::Spectrum_generator_settings& arg_1)
        {
            get_BEptr()->set_settings__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_slha_io::set_sminputs(const softsusy::QedQcd& arg_1)
        {
            get_BEptr()->set_sminputs__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_slha_io::set_spinfo(const flexiblesusy::Spectrum_generator_problems& arg_1)
        {
            get_BEptr()->set_spinfo__BOSS(*arg_1.get_BEptr());
        }
        
        inline void CMSSM_slha_io::set_spinfo(const ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > >& arg_1, const ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > >& arg_2)
        {
            get_BEptr()->set_spinfo(arg_1, arg_2);
        }
        
        inline void CMSSM_slha_io::set_print_imaginary_parts_of_majorana_mixings(bool arg_1)
        {
            get_BEptr()->set_print_imaginary_parts_of_majorana_mixings(arg_1);
        }
        
        inline void CMSSM_slha_io::write_to(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& arg_1) const
        {
            get_BEptr()->write_to(arg_1);
        }
        
        inline void CMSSM_slha_io::write_to_file(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& file_name) const
        {
            get_BEptr()->write_to_file(file_name);
        }
        
        inline void CMSSM_slha_io::write_to_stream(::std::basic_ostream<char, std::char_traits<char> >& ostr) const
        {
            get_BEptr()->write_to_stream(ostr);
        }
        
        inline void CMSSM_slha_io::write_to_stream() const
        {
            get_BEptr()->write_to_stream__BOSS();
        }
        
        inline void CMSSM_slha_io::fill_minpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3)
        {
            get_BEptr()->fill_minpar_tuple__BOSS(*arg_1.get_BEptr(), arg_2, arg_3);
        }
        
        inline void CMSSM_slha_io::fill_extpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3)
        {
            get_BEptr()->fill_extpar_tuple__BOSS(*arg_1.get_BEptr(), arg_2, arg_3);
        }
        
        inline void CMSSM_slha_io::fill_imminpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3)
        {
            get_BEptr()->fill_imminpar_tuple__BOSS(*arg_1.get_BEptr(), arg_2, arg_3);
        }
        
        inline void CMSSM_slha_io::fill_imextpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3)
        {
            get_BEptr()->fill_imextpar_tuple__BOSS(*arg_1.get_BEptr(), arg_2, arg_3);
        }
        
        
        // Wrappers for original constructors: 
        inline flexiblesusy::CMSSM_slha_io::CMSSM_slha_io() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline flexiblesusy::CMSSM_slha_io::CMSSM_slha_io(flexiblesusy::Abstract_CMSSM_slha_io* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline flexiblesusy::CMSSM_slha_io::CMSSM_slha_io(const CMSSM_slha_io& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline flexiblesusy::CMSSM_slha_io& CMSSM_slha_io::operator=(const CMSSM_slha_io& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline flexiblesusy::CMSSM_slha_io::~CMSSM_slha_io()
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
        inline flexiblesusy::Abstract_CMSSM_slha_io* flexiblesusy::CMSSM_slha_io::get_BEptr() const
        {
            return dynamic_cast<flexiblesusy::Abstract_CMSSM_slha_io*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_slha_io_def_FlexibleSUSY_CMSSM_2_4_0_h__ */
