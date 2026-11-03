#ifndef __wrapper_DM_Particle_Standard_decl_obscura_1_1_0_hpp__
#define __wrapper_DM_Particle_Standard_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DM_Particle_Standard.hpp"
#include "wrapper_DM_Particle_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class DM_Particle_Standard : public DM_Particle
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DM_Particle_Standard* (*__factory0)();
                static Abstract_DM_Particle_Standard* (*__factory1)(double, double);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void Set_Mass(double mDM);
        
                double Get_Interaction_Parameter(std::string target) const;
        
                void Set_Interaction_Parameter(double par, std::string target);
        
                void Set_Sigma_Proton(double sigma);
        
                void Set_Sigma_Neutron(double sigma);
        
                void Set_Sigma_Electron(double sigma);
        
                void Fix_Coupling_Ratio(double fp_rel, double fn_rel);
        
                void Fix_fn_over_fp(double ratio);
        
                void Fix_fp_over_fn(double ratio);
        
                void Unfix_Coupling_Ratios();
        
                double dSigma_dq2_Electron(double q, double vDM, double param) const;
        
                double dSigma_dq2_Electron(double q, double vDM) const;
        
                double Sigma_Proton() const;
        
                double Sigma_Neutron() const;
        
                double Sigma_Electron() const;
        
        
                // Wrappers for original constructors: 
            public:
                DM_Particle_Standard();
                DM_Particle_Standard(double mDM, double pre);
        
                // Special pointer-based constructor: 
                DM_Particle_Standard(Abstract_DM_Particle_Standard* in);
        
                // Copy constructor: 
                DM_Particle_Standard(const DM_Particle_Standard& in);
        
                // Assignment operator: 
                DM_Particle_Standard& operator=(const DM_Particle_Standard& in);
        
                // Destructor: 
                ~DM_Particle_Standard();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DM_Particle_Standard* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Particle_Standard_decl_obscura_1_1_0_hpp__ */
