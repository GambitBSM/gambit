#ifndef __wrapper_CMSSM_soft_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__
#define __wrapper_CMSSM_soft_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__

#include <cstddef>
#include <ostream>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CMSSM_soft_parameters.h"
#include "wrapper_CMSSM_susy_parameters_decl.h"
#include "wrapper_CMSSM_input_parameters_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace flexiblesusy
    {
        
        class CMSSM_soft_parameters : public CMSSM_susy_parameters
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_CMSSM_soft_parameters* (*__factory0)(const flexiblesusy::CMSSM_input_parameters&);
                static Abstract_CMSSM_soft_parameters* (*__factory1)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void print(::std::basic_ostream<char>& arg_1) const;
        
                CMSSM_soft_parameters calc_beta() const;
        
                CMSSM_soft_parameters calc_beta(int arg_1) const;
        
                void clear();
        
                void set_TYd(int i, int k, const double& value);
        
                void set_TYe(int i, int k, const double& value);
        
                void set_TYu(int i, int k, const double& value);
        
                void set_BMu(double BMu_);
        
                void set_mq2(int i, int k, const double& value);
        
                void set_ml2(int i, int k, const double& value);
        
                void set_mHd2(double mHd2_);
        
                void set_mHu2(double mHu2_);
        
                void set_md2(int i, int k, const double& value);
        
                void set_mu2(int i, int k, const double& value);
        
                void set_me2(int i, int k, const double& value);
        
                void set_MassB(double MassB_);
        
                void set_MassWB(double MassWB_);
        
                void set_MassG(double MassG_);
        
                double get_TYd(int i, int k) const;
        
                double get_TYe(int i, int k) const;
        
                double get_TYu(int i, int k) const;
        
                double get_BMu() const;
        
                double get_mq2(int i, int k) const;
        
                double get_ml2(int i, int k) const;
        
                double get_mHd2() const;
        
                double get_mHu2() const;
        
                double get_md2(int i, int k) const;
        
                double get_mu2(int i, int k) const;
        
                double get_me2(int i, int k) const;
        
                double get_MassB() const;
        
                double get_MassWB() const;
        
                double get_MassG() const;
        
        
                // Wrappers for original constructors: 
            public:
                CMSSM_soft_parameters(const flexiblesusy::CMSSM_input_parameters& input_);
                CMSSM_soft_parameters();
        
                // Special pointer-based constructor: 
                CMSSM_soft_parameters(Abstract_CMSSM_soft_parameters* in);
        
                // Copy constructor: 
                CMSSM_soft_parameters(const CMSSM_soft_parameters& in);
        
                // Assignment operator: 
                CMSSM_soft_parameters& operator=(const CMSSM_soft_parameters& in);
        
                // Destructor: 
                ~CMSSM_soft_parameters();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_CMSSM_soft_parameters* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CMSSM_soft_parameters_decl_FlexibleSUSY_CMSSM_2_0_1_h__ */
