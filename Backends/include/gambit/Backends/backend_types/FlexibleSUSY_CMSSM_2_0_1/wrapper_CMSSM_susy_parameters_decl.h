#ifndef __wrapper_CMSSM_susy_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_susy_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <ostream>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_susy_parameters.h"
#include "wrapper_Beta_function_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM_susy_parameters : public Beta_function
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_CMSSM_susy_parameters* (*__factory0)(const flexiblesusy::CMSSM_input_parameters&);
                static Abstract_CMSSM_susy_parameters* (*__factory1)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void print(::std::basic_ostream<char>& arg_1) const;
        
                const CMSSM_input_parameters& get_input() const;
        
                CMSSM_input_parameters& get_input();
        
                void set_input_parameters(const flexiblesusy::CMSSM_input_parameters& arg_1);
        
                CMSSM_susy_parameters calc_beta() const;
        
                CMSSM_susy_parameters calc_beta(int arg_1) const;
        
                void clear();
        
                void set_Yd(int i, int k, const double& value);
        
                void set_Ye(int i, int k, const double& value);
        
                void set_Yu(int i, int k, const double& value);
        
                void set_Mu(double Mu_);
        
                void set_g1(double g1_);
        
                void set_g2(double g2_);
        
                void set_g3(double g3_);
        
                void set_vd(double vd_);
        
                void set_vu(double vu_);
        
                double get_Yd(int i, int k) const;
        
                double get_Ye(int i, int k) const;
        
                double get_Yu(int i, int k) const;
        
                double get_Mu() const;
        
                double get_g1() const;
        
                double get_g2() const;
        
                double get_g3() const;
        
                double get_vd() const;
        
                double get_vu() const;
        
                double get_SHdSHd() const;
        
                double get_SHuSHu() const;
        
        
                // Wrappers for original constructors: 
            public:
                CMSSM_susy_parameters(const flexiblesusy::CMSSM_input_parameters& input_);
                CMSSM_susy_parameters();
        
                // Special pointer-based constructor: 
                CMSSM_susy_parameters(Abstract_CMSSM_susy_parameters* in);
        
                // Copy constructor: 
                CMSSM_susy_parameters(const CMSSM_susy_parameters& in);
        
                // Assignment operator: 
                CMSSM_susy_parameters& operator=(const CMSSM_susy_parameters& in);
        
                // Destructor: 
                ~CMSSM_susy_parameters();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_CMSSM_susy_parameters* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_susy_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
