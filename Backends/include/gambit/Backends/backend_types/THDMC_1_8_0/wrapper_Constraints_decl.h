#ifndef __wrapper_Constraints_decl_THDMC_1_8_0_h__
#define __wrapper_Constraints_decl_THDMC_1_8_0_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Constraints.h"
#include "wrapper_THDM_decl.h"
#include "wrapper_SM_decl.h"
#include "wrapper_DecayTableTHDM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    class Constraints : public WrapperBase
    {
            // Member variables: 
        public:
            // -- Static factory pointers: 
            static Abstract_Constraints* (*__factory0)();
            static Abstract_Constraints* (*__factory1)(THDM);
    
            // -- Other member variables: 
    
            // Member functions: 
        public:
            void set_THDM(THDM mod);
    
            bool check_unitarity(double unitarity_limit);
    
            bool check_unitarity();
    
            bool check_perturbativity(double perturbativity_limit);
    
            bool check_perturbativity();
    
            bool check_stability();
    
            bool check_positivity();
    
            bool check_masses();
    
            bool check_lep();
    
            bool check_charged(bool& HpHp, bool& HpHptau, bool& HpHpcs);
    
            bool check_NMSSMTools(bool& hZ, bool& hZ2b, bool& hZ2tau, bool& hZinv, bool& hZ2j, bool& hZ2gamma, bool& hZ4b, bool& hZ4tau, bool& hZ2b2tau, bool& hA, bool& hA4b, bool& hA4tau, bool& hA2b2tau, bool& hA6b, bool& hA6tau, bool& ZhZjj);
    
            double delta_amu();
    
            double delta_rho(double mh);
    
            void oblique_param(double mh, double& S, double& T, double& U, double& V, double& W, double& X);
    
            void print_all(double mh_ref);
    
    
            // Wrappers for original constructors: 
        public:
            Constraints();
            Constraints(THDM mod);
    
            // Special pointer-based constructor: 
            Constraints(Abstract_Constraints* in);
    
            // Copy constructor: 
            Constraints(const Constraints& in);
    
            // Assignment operator: 
            Constraints& operator=(const Constraints& in);
    
            // Destructor: 
            ~Constraints();
    
            // Returns correctly casted pointer to Abstract class: 
            Abstract_Constraints* get_BEptr() const;
    
    };
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Constraints_decl_THDMC_1_8_0_h__ */
