#ifndef __wrapper_DM_Particle_SI_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Particle_SI_def_obscura_1_1_0_hpp__

#include <string>
#include <random>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        // Member functions: 
        inline void DM_Particle_SI::Set_FormFactor_DM(std::string ff, double mMed)
        {
            get_BEptr()->Set_FormFactor_DM(ff, mMed);
        }
        
        inline void DM_Particle_SI::Set_FormFactor_DM(std::string ff)
        {
            get_BEptr()->Set_FormFactor_DM__BOSS(ff);
        }
        
        inline void DM_Particle_SI::Set_Mediator_Mass(double m)
        {
            get_BEptr()->Set_Mediator_Mass(m);
        }
        
        inline double DM_Particle_SI::dSigma_dq2_Electron(double q, double vDM, double param) const
        {
            return get_BEptr()->dSigma_dq2_Electron(q, vDM, param);
        }
        
        inline double DM_Particle_SI::dSigma_dq2_Electron(double q, double vDM) const
        {
            return get_BEptr()->dSigma_dq2_Electron__BOSS(q, vDM);
        }
        
        inline bool DM_Particle_SI::Is_Sigma_Total_V_Dependent() const
        {
            return get_BEptr()->Is_Sigma_Total_V_Dependent();
        }
        
        inline double DM_Particle_SI::Sigma_Total_Electron(double vDM, double param)
        {
            return get_BEptr()->Sigma_Total_Electron(vDM, param);
        }
        
        inline double DM_Particle_SI::Sigma_Total_Electron(double vDM)
        {
            return get_BEptr()->Sigma_Total_Electron__BOSS(vDM);
        }
        
        inline double DM_Particle_SI::PDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param)
        {
            return get_BEptr()->PDF_Scattering_Angle_Electron(cos_alpha, vDM, param);
        }
        
        inline double DM_Particle_SI::PDF_Scattering_Angle_Electron(double cos_alpha, double vDM)
        {
            return get_BEptr()->PDF_Scattering_Angle_Electron__BOSS(cos_alpha, vDM);
        }
        
        inline double DM_Particle_SI::CDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param)
        {
            return get_BEptr()->CDF_Scattering_Angle_Electron(cos_alpha, vDM, param);
        }
        
        inline double DM_Particle_SI::CDF_Scattering_Angle_Electron(double cos_alpha, double vDM)
        {
            return get_BEptr()->CDF_Scattering_Angle_Electron__BOSS(cos_alpha, vDM);
        }
        
        inline double DM_Particle_SI::Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM, double param)
        {
            return get_BEptr()->Sample_Scattering_Angle_Electron(PRNG, vDM, param);
        }
        
        inline double DM_Particle_SI::Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM)
        {
            return get_BEptr()->Sample_Scattering_Angle_Electron__BOSS(PRNG, vDM);
        }
        
        inline void DM_Particle_SI::Print_Summary(int MPI_rank) const
        {
            get_BEptr()->Print_Summary(MPI_rank);
        }
        
        inline void DM_Particle_SI::Print_Summary() const
        {
            get_BEptr()->Print_Summary__BOSS();
        }
        
        
        // Wrappers for original constructors: 
        inline DM_Particle_SI::DM_Particle_SI() :
            DM_Particle_Standard(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Particle_SI::DM_Particle_SI(double mDM) :
            DM_Particle_Standard(__factory1(mDM))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Particle_SI::DM_Particle_SI(double mDM, double sigmaP) :
            DM_Particle_Standard(__factory2(mDM, sigmaP))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Particle_SI::DM_Particle_SI(Abstract_DM_Particle_SI* in) :
            DM_Particle_Standard(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Particle_SI::DM_Particle_SI(const DM_Particle_SI& in) :
            DM_Particle_Standard(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Particle_SI& DM_Particle_SI::operator=(const DM_Particle_SI& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Particle_SI::~DM_Particle_SI()
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
        inline Abstract_DM_Particle_SI* obscura::DM_Particle_SI::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Particle_SI*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Particle_SI_def_obscura_1_1_0_hpp__ */
