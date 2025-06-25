#ifndef __wrapper_DM_Particle_Standard_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Particle_Standard_def_obscura_1_1_0_hpp__

#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        // Member functions: 
        inline void DM_Particle_Standard::Set_Mass(double mDM)
        {
            get_BEptr()->Set_Mass(mDM);
        }
        
        inline double DM_Particle_Standard::Get_Interaction_Parameter(std::string target) const
        {
            return get_BEptr()->Get_Interaction_Parameter(target);
        }
        
        inline void DM_Particle_Standard::Set_Interaction_Parameter(double par, std::string target)
        {
            get_BEptr()->Set_Interaction_Parameter(par, target);
        }
        
        inline void DM_Particle_Standard::Set_Sigma_Proton(double sigma)
        {
            get_BEptr()->Set_Sigma_Proton(sigma);
        }
        
        inline void DM_Particle_Standard::Set_Sigma_Neutron(double sigma)
        {
            get_BEptr()->Set_Sigma_Neutron(sigma);
        }
        
        inline void DM_Particle_Standard::Set_Sigma_Electron(double sigma)
        {
            get_BEptr()->Set_Sigma_Electron(sigma);
        }
        
        inline void DM_Particle_Standard::Fix_Coupling_Ratio(double fp_rel, double fn_rel)
        {
            get_BEptr()->Fix_Coupling_Ratio(fp_rel, fn_rel);
        }
        
        inline void DM_Particle_Standard::Fix_fn_over_fp(double ratio)
        {
            get_BEptr()->Fix_fn_over_fp(ratio);
        }
        
        inline void DM_Particle_Standard::Fix_fp_over_fn(double ratio)
        {
            get_BEptr()->Fix_fp_over_fn(ratio);
        }
        
        inline void DM_Particle_Standard::Unfix_Coupling_Ratios()
        {
            get_BEptr()->Unfix_Coupling_Ratios();
        }
        
        inline double DM_Particle_Standard::dSigma_dq2_Electron(double q, double vDM, double param) const
        {
            return get_BEptr()->dSigma_dq2_Electron(q, vDM, param);
        }
        
        inline double DM_Particle_Standard::dSigma_dq2_Electron(double q, double vDM) const
        {
            return get_BEptr()->dSigma_dq2_Electron__BOSS(q, vDM);
        }
        
        inline double DM_Particle_Standard::Sigma_Proton() const
        {
            return get_BEptr()->Sigma_Proton();
        }
        
        inline double DM_Particle_Standard::Sigma_Neutron() const
        {
            return get_BEptr()->Sigma_Neutron();
        }
        
        inline double DM_Particle_Standard::Sigma_Electron() const
        {
            return get_BEptr()->Sigma_Electron();
        }
        
        
        // Wrappers for original constructors: 
        inline DM_Particle_Standard::DM_Particle_Standard() :
            DM_Particle(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Particle_Standard::DM_Particle_Standard(double mDM, double pre) :
            DM_Particle(__factory1(mDM, pre))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Particle_Standard::DM_Particle_Standard(Abstract_DM_Particle_Standard* in) :
            DM_Particle(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Particle_Standard::DM_Particle_Standard(const DM_Particle_Standard& in) :
            DM_Particle(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Particle_Standard& DM_Particle_Standard::operator=(const DM_Particle_Standard& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Particle_Standard::~DM_Particle_Standard()
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
        inline Abstract_DM_Particle_Standard* obscura::DM_Particle_Standard::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Particle_Standard*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Particle_Standard_def_obscura_1_1_0_hpp__ */
