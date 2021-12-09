#ifndef __wrapper_Command_line_options_decl_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_Command_line_options_decl_FlexibleSUSY_CMSSM_2_4_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Command_line_options.h"
#include <ostream>
#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Command_line_options : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static flexiblesusy::Abstract_Command_line_options* (*__factory0)();
                static flexiblesusy::Abstract_Command_line_options* (*__factory1)(int, char**);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                bool must_exit() const;
        
                bool must_print_model_info() const;
        
                int status() const;
        
                void print_build_info(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const;
        
                void print_usage(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const;
        
                void print_version(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const;
        
                void reset();
        
                const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_database_output_file() const;
        
                const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_slha_input_file() const;
        
                const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_slha_output_file() const;
        
                const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_program_name() const;
        
                const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_rgflow_file() const;
        
                const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_spectrum_file() const;
        
        
                // Wrappers for original constructors: 
            public:
                Command_line_options();
                Command_line_options(int arg_1, char** arg_2);
        
                // Special pointer-based constructor: 
                Command_line_options(flexiblesusy::Abstract_Command_line_options* in);
        
                // Copy constructor: 
                Command_line_options(const Command_line_options& in);
        
                // Assignment operator: 
                Command_line_options& operator=(const Command_line_options& in);
        
                // Destructor: 
                ~Command_line_options();
        
                // Returns correctly casted pointer to Abstract class: 
                flexiblesusy::Abstract_Command_line_options* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Command_line_options_decl_FlexibleSUSY_CMSSM_2_4_0_h__ */
