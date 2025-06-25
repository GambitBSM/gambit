#ifndef __wrapper_DM_Particle_decl_obscura_1_1_0_hpp__
#define __wrapper_DM_Particle_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include <random>
#include <string>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DM_Particle.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class DM_Particle : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DM_Particle* (*__factory0)();
                static Abstract_DM_Particle* (*__factory1)(double, double);
                static Abstract_DM_Particle* (*__factory2)(double);
        
                // -- Other member variables: 
            public:
                double& mass;
                double& spin;
                double& fractional_density;
                bool& DD_use_eta_function;
        
                // Member functions: 
            public:
                void Set_Mass(double mDM);
        
                void Set_Spin(double s);
        
                void Set_Low_Mass_Mode(bool ldm);
        
                void Set_Fractional_Density(double f);
        
                double Get_Interaction_Parameter(std::string target) const;
        
                void Set_Interaction_Parameter(double par, std::string target);
        
                bool Interaction_Parameter_Is_Cross_Section() const;
        
                void Set_Sigma_Proton(double sigma);
        
                void Set_Sigma_Neutron(double sigma);
        
                void Set_Sigma_Electron(double sigma);
        
                double dSigma_dq2_Electron(double q, double vDM, double param) const;
        
                double dSigma_dq2_Electron(double q, double vDM) const;
        
                double Sigma_Proton() const;
        
                double Sigma_Neutron() const;
        
                double Sigma_Electron() const;
        
                bool Is_Sigma_Total_V_Dependent() const;
        
                double Sigma_Total_Electron(double vDM, double param);
        
                double Sigma_Total_Electron(double vDM);
        
                void Print_Summary(int MPI_rank) const;
        
                void Print_Summary() const;
        
                double PDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param);
        
                double PDF_Scattering_Angle_Electron(double cos_alpha, double vDM);
        
                double CDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param);
        
                double CDF_Scattering_Angle_Electron(double cos_alpha, double vDM);
        
                double Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM, double param);
        
                double Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM);
        
        
                // Wrappers for original constructors: 
            public:
                DM_Particle();
                DM_Particle(double m, double s);
                DM_Particle(double m);
        
                // Special pointer-based constructor: 
                DM_Particle(Abstract_DM_Particle* in);
        
                // Copy constructor: 
                DM_Particle(const DM_Particle& in);
        
                // Assignment operator: 
                DM_Particle& operator=(const DM_Particle& in);
        
                // Destructor: 
                ~DM_Particle();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DM_Particle* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Particle_decl_obscura_1_1_0_hpp__ */
