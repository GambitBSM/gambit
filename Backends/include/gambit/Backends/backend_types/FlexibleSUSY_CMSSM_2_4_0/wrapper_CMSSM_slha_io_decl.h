#ifndef __wrapper_CMSSM_slha_io_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_CMSSM_slha_io_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_slha_io.h"
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
        
        class CMSSM_slha_io : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_CMSSM_slha_io* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void clear();
        
                void fill(softsusy::QedQcd& qedqcd) const;
        
                void fill(flexiblesusy::CMSSM_input_parameters& arg_1) const;
        
                void fill(flexiblesusy::Physical_input& arg_1) const;
        
                void fill(flexiblesusy::Spectrum_generator_settings& arg_1) const;
        
                double get_parameter_output_scale() const;
        
                void read_from_file(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& arg_1);
        
                void read_from_source(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& arg_1);
        
                void read_from_stream(::std::basic_istream<char, std::char_traits<char> >& arg_1);
        
                void set_input(const flexiblesusy::CMSSM_input_parameters& arg_1);
        
                void set_physical_input(const flexiblesusy::Physical_input& arg_1);
        
                void set_settings(const flexiblesusy::Spectrum_generator_settings& arg_1);
        
                void set_sminputs(const softsusy::QedQcd& arg_1);
        
                void set_spinfo(const flexiblesusy::Spectrum_generator_problems& arg_1);
        
                void set_spinfo(const ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > >& arg_1, const ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > >& arg_2);
        
                void set_print_imaginary_parts_of_majorana_mixings(bool arg_1);
        
                void write_to(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& arg_1) const;
        
                void write_to_file(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& file_name) const;
        
                void write_to_stream(::std::basic_ostream<char, std::char_traits<char> >& ostr) const;
        
                void write_to_stream() const;
        
                void fill_minpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3);
        
                void fill_extpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3);
        
                void fill_imminpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3);
        
                void fill_imextpar_tuple(flexiblesusy::CMSSM_input_parameters& arg_1, int arg_2, double arg_3);
        
        
                // Wrappers for original constructors: 
            public:
                CMSSM_slha_io();
        
                // Special pointer-based constructor: 
                CMSSM_slha_io(flexiblesusy::Abstract_CMSSM_slha_io* in);
        
                // Copy constructor: 
                CMSSM_slha_io(const CMSSM_slha_io& in);
        
                // Assignment operator: 
                CMSSM_slha_io& operator=(const CMSSM_slha_io& in);
        
                // Destructor: 
                ~CMSSM_slha_io();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_CMSSM_slha_io* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_slha_io_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
