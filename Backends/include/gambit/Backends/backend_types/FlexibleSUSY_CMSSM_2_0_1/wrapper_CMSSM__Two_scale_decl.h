#ifndef __wrapper_CMSSM__Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM__Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <string>
#include <ostream>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM__Two_scale.h"
#include "wrapper_Model_decl.h"
#include "wrapper_CMSSM_mass_eigenstates_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM__Two_scale : public Model, public CMSSM_mass_eigenstates
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_CMSSM__Two_scale* (*__factory0)(const flexiblesusy::CMSSM_input_parameters&);
                static Abstract_CMSSM__Two_scale* (*__factory1)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void calculate_spectrum();
        
                void clear_problems();
        
                ::std::basic_string<char> name() const;
        
                void run_to(double scale, double eps);
        
                void run_to(double scale);
        
                void print(::std::basic_ostream<char>& out) const;
        
                void print() const;
        
                void set_precision(double arg_1);
        
        
                // Wrappers for original constructors: 
            public:
                CMSSM__Two_scale(const flexiblesusy::CMSSM_input_parameters& input_);
                CMSSM__Two_scale();
        
                // Special pointer-based constructor: 
                CMSSM__Two_scale(Abstract_CMSSM__Two_scale* in);
        
                // Copy constructor: 
                CMSSM__Two_scale(const CMSSM__Two_scale& in);
        
                // Assignment operator: 
                CMSSM__Two_scale& operator=(const CMSSM__Two_scale& in);
        
                // Destructor: 
                ~CMSSM__Two_scale();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_CMSSM__Two_scale* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM__Two_scale_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
