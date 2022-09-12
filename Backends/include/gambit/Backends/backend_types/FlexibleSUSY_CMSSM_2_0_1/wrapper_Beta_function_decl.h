#ifndef __wrapper_Beta_function_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_Beta_function_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Beta_function.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class Beta_function : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Beta_function* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void set_scale(double s);
        
                void set_number_of_parameters(int pars);
        
                void set_loops(int l);
        
                void set_thresholds(int t);
        
                void set_zero_threshold(double t);
        
                double get_scale() const;
        
                int get_number_of_parameters() const;
        
                int get_loops() const;
        
                int get_thresholds() const;
        
                double get_zero_threshold() const;
        
                void reset();
        
                void run(double arg_1, double arg_2, double eps);
        
                void run(double arg_1, double arg_2);
        
                void run_to(double arg_1, double eps);
        
                void run_to(double arg_1);
        
        
                // Wrappers for original constructors: 
            public:
                Beta_function();
        
                // Special pointer-based constructor: 
                Beta_function(Abstract_Beta_function* in);
        
                // Copy constructor: 
                Beta_function(const Beta_function& in);
        
                // Assignment operator: 
                Beta_function& operator=(const Beta_function& in);
        
                // Destructor: 
                ~Beta_function();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Beta_function* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Beta_function_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
