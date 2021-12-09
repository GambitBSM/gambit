#ifndef __abstract_Command_line_options_FlexibleSUSY_CMSSM_2_4_0_h__
#define __abstract_Command_line_options_FlexibleSUSY_CMSSM_2_4_0_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include <ostream>
#include <string>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace flexiblesusy
    {
        class Abstract_Command_line_options : public virtual AbstractBase
        {
            public:
    
                virtual bool must_exit() const =0;
    
                virtual bool must_print_model_info() const =0;
    
                virtual int status() const =0;
    
                virtual void print_build_info(::std::basic_ostream<char, std::char_traits<char> >&) const =0;
    
                virtual void print_usage(::std::basic_ostream<char, std::char_traits<char> >&) const =0;
    
                virtual void print_version(::std::basic_ostream<char, std::char_traits<char> >&) const =0;
    
                virtual void reset() =0;
    
                virtual const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_database_output_file() const =0;
    
                virtual const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_slha_input_file() const =0;
    
                virtual const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_slha_output_file() const =0;
    
                virtual const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_program_name() const =0;
    
                virtual const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_rgflow_file() const =0;
    
                virtual const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& get_spectrum_file() const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Command_line_options*) =0;
                virtual Abstract_Command_line_options* pointer_copy__BOSS() =0;
    
            private:
                Command_line_options* wptr;
                bool delete_wrapper;
            public:
                Command_line_options* get_wptr() { return wptr; }
                void set_wptr(Command_line_options* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Command_line_options()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Command_line_options(const Abstract_Command_line_options&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Command_line_options& operator=(const Abstract_Command_line_options&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Command_line_options* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Command_line_options& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Command_line_options() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Command_line_options_FlexibleSUSY_CMSSM_2_4_0_h__ */
