#ifndef __wrapper_Command_line_options_def_FlexibleSUSY_CMSSM_2_4_0_h__
#define __wrapper_Command_line_options_def_FlexibleSUSY_CMSSM_2_4_0_h__

#include <ostream>
#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        // Member functions: 
        inline bool Command_line_options::must_exit() const
        {
            return get_BEptr()->must_exit();
        }
        
        inline bool Command_line_options::must_print_model_info() const
        {
            return get_BEptr()->must_print_model_info();
        }
        
        inline int Command_line_options::status() const
        {
            return get_BEptr()->status();
        }
        
        inline void Command_line_options::print_build_info(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const
        {
            get_BEptr()->print_build_info(arg_1);
        }
        
        inline void Command_line_options::print_usage(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const
        {
            get_BEptr()->print_usage(arg_1);
        }
        
        inline void Command_line_options::print_version(::std::basic_ostream<char, std::char_traits<char> >& arg_1) const
        {
            get_BEptr()->print_version(arg_1);
        }
        
        inline void Command_line_options::reset()
        {
            get_BEptr()->reset();
        }
        
        inline const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& Command_line_options::get_database_output_file() const
        {
            return get_BEptr()->get_database_output_file();
        }
        
        inline const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& Command_line_options::get_slha_input_file() const
        {
            return get_BEptr()->get_slha_input_file();
        }
        
        inline const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& Command_line_options::get_slha_output_file() const
        {
            return get_BEptr()->get_slha_output_file();
        }
        
        inline const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& Command_line_options::get_program_name() const
        {
            return get_BEptr()->get_program_name();
        }
        
        inline const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& Command_line_options::get_rgflow_file() const
        {
            return get_BEptr()->get_rgflow_file();
        }
        
        inline const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& Command_line_options::get_spectrum_file() const
        {
            return get_BEptr()->get_spectrum_file();
        }
        
        
        // Wrappers for original constructors: 
        inline flexiblesusy::Command_line_options::Command_line_options() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline flexiblesusy::Command_line_options::Command_line_options(int arg_1, char** arg_2) :
            WrapperBase(__factory1(arg_1, arg_2))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline flexiblesusy::Command_line_options::Command_line_options(flexiblesusy::Abstract_Command_line_options* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline flexiblesusy::Command_line_options::Command_line_options(const Command_line_options& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline flexiblesusy::Command_line_options& Command_line_options::operator=(const Command_line_options& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline flexiblesusy::Command_line_options::~Command_line_options()
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
        inline flexiblesusy::Abstract_Command_line_options* flexiblesusy::Command_line_options::get_BEptr() const
        {
            return dynamic_cast<flexiblesusy::Abstract_Command_line_options*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Command_line_options_def_FlexibleSUSY_CMSSM_2_4_0_h__ */
