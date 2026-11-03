#ifndef __wrapper_DM_Particle_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Particle_def_obscura_1_1_0_hpp__

#include <random>
#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        // Member functions: 
        inline void DM_Particle::Set_Mass(double mDM)
        {
            get_BEptr()->Set_Mass(mDM);
        }
        
        inline void DM_Particle::Set_Spin(double s)
        {
            get_BEptr()->Set_Spin(s);
        }
        
        inline void DM_Particle::Set_Low_Mass_Mode(bool ldm)
        {
            get_BEptr()->Set_Low_Mass_Mode(ldm);
        }
        
        inline void DM_Particle::Set_Fractional_Density(double f)
        {
            get_BEptr()->Set_Fractional_Density(f);
        }
        
        inline double DM_Particle::Get_Interaction_Parameter(std::string target) const
        {
            return get_BEptr()->Get_Interaction_Parameter(target);
        }
        
        inline void DM_Particle::Set_Interaction_Parameter(double par, std::string target)
        {
            get_BEptr()->Set_Interaction_Parameter(par, target);
        }
        
        inline bool DM_Particle::Interaction_Parameter_Is_Cross_Section() const
        {
            return get_BEptr()->Interaction_Parameter_Is_Cross_Section();
        }
        
        inline void DM_Particle::Set_Sigma_Proton(double sigma)
        {
            get_BEptr()->Set_Sigma_Proton(sigma);
        }
        
        inline void DM_Particle::Set_Sigma_Neutron(double sigma)
        {
            get_BEptr()->Set_Sigma_Neutron(sigma);
        }
        
        inline void DM_Particle::Set_Sigma_Electron(double sigma)
        {
            get_BEptr()->Set_Sigma_Electron(sigma);
        }
        
        inline double DM_Particle::dSigma_dq2_Electron(double q, double vDM, double param) const
        {
            return get_BEptr()->dSigma_dq2_Electron(q, vDM, param);
        }
        
        inline double DM_Particle::dSigma_dq2_Electron(double q, double vDM) const
        {
            return get_BEptr()->dSigma_dq2_Electron__BOSS(q, vDM);
        }
        
        inline double DM_Particle::Sigma_Proton() const
        {
            return get_BEptr()->Sigma_Proton();
        }
        
        inline double DM_Particle::Sigma_Neutron() const
        {
            return get_BEptr()->Sigma_Neutron();
        }
        
        inline double DM_Particle::Sigma_Electron() const
        {
            return get_BEptr()->Sigma_Electron();
        }
        
        inline bool DM_Particle::Is_Sigma_Total_V_Dependent() const
        {
            return get_BEptr()->Is_Sigma_Total_V_Dependent();
        }
        
        inline double DM_Particle::Sigma_Total_Electron(double vDM, double param)
        {
            return get_BEptr()->Sigma_Total_Electron(vDM, param);
        }
        
        inline double DM_Particle::Sigma_Total_Electron(double vDM)
        {
            return get_BEptr()->Sigma_Total_Electron__BOSS(vDM);
        }
        
        inline void DM_Particle::Print_Summary(int MPI_rank) const
        {
            get_BEptr()->Print_Summary(MPI_rank);
        }
        
        inline void DM_Particle::Print_Summary() const
        {
            get_BEptr()->Print_Summary__BOSS();
        }
        
        inline double DM_Particle::PDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param)
        {
            return get_BEptr()->PDF_Scattering_Angle_Electron(cos_alpha, vDM, param);
        }
        
        inline double DM_Particle::PDF_Scattering_Angle_Electron(double cos_alpha, double vDM)
        {
            return get_BEptr()->PDF_Scattering_Angle_Electron__BOSS(cos_alpha, vDM);
        }
        
        inline double DM_Particle::CDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param)
        {
            return get_BEptr()->CDF_Scattering_Angle_Electron(cos_alpha, vDM, param);
        }
        
        inline double DM_Particle::CDF_Scattering_Angle_Electron(double cos_alpha, double vDM)
        {
            return get_BEptr()->CDF_Scattering_Angle_Electron__BOSS(cos_alpha, vDM);
        }
        
        inline double DM_Particle::Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM, double param)
        {
            return get_BEptr()->Sample_Scattering_Angle_Electron(PRNG, vDM, param);
        }
        
        inline double DM_Particle::Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM)
        {
            return get_BEptr()->Sample_Scattering_Angle_Electron__BOSS(PRNG, vDM);
        }
        
        
        // Wrappers for original constructors: 
        inline DM_Particle::DM_Particle() :
            WrapperBase(__factory0()),
            mass( get_BEptr()->mass_ref__BOSS()),
            spin( get_BEptr()->spin_ref__BOSS()),
            fractional_density( get_BEptr()->fractional_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Particle::DM_Particle(double m, double s) :
            WrapperBase(__factory1(m, s)),
            mass( get_BEptr()->mass_ref__BOSS()),
            spin( get_BEptr()->spin_ref__BOSS()),
            fractional_density( get_BEptr()->fractional_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Particle::DM_Particle(double m) :
            WrapperBase(__factory2(m)),
            mass( get_BEptr()->mass_ref__BOSS()),
            spin( get_BEptr()->spin_ref__BOSS()),
            fractional_density( get_BEptr()->fractional_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Particle::DM_Particle(Abstract_DM_Particle* in) :
            WrapperBase(in),
            mass( get_BEptr()->mass_ref__BOSS()),
            spin( get_BEptr()->spin_ref__BOSS()),
            fractional_density( get_BEptr()->fractional_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Particle::DM_Particle(const DM_Particle& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            mass( get_BEptr()->mass_ref__BOSS()),
            spin( get_BEptr()->spin_ref__BOSS()),
            fractional_density( get_BEptr()->fractional_density_ref__BOSS()),
            DD_use_eta_function( get_BEptr()->DD_use_eta_function_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Particle& DM_Particle::operator=(const DM_Particle& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Particle::~DM_Particle()
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
        inline Abstract_DM_Particle* obscura::DM_Particle::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Particle*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Particle_def_obscura_1_1_0_hpp__ */
