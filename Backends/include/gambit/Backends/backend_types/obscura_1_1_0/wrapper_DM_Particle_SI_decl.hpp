#ifndef __wrapper_DM_Particle_SI_decl_obscura_1_1_0_hpp__
#define __wrapper_DM_Particle_SI_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include <string>
#include <random>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DM_Particle_SI.hpp"
#include "wrapper_DM_Particle_Standard_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class DM_Particle_SI : public DM_Particle_Standard
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DM_Particle_SI* (*__factory0)();
                static Abstract_DM_Particle_SI* (*__factory1)(double);
                static Abstract_DM_Particle_SI* (*__factory2)(double, double);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void Set_FormFactor_DM(std::string ff, double mMed);
        
                void Set_FormFactor_DM(std::string ff);
        
                void Set_Mediator_Mass(double m);
        
                double dSigma_dq2_Electron(double q, double vDM, double param) const;
        
                double dSigma_dq2_Electron(double q, double vDM) const;
        
                bool Is_Sigma_Total_V_Dependent() const;
        
                double Sigma_Total_Electron(double vDM, double param);
        
                double Sigma_Total_Electron(double vDM);
        
                double PDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param);
        
                double PDF_Scattering_Angle_Electron(double cos_alpha, double vDM);
        
                double CDF_Scattering_Angle_Electron(double cos_alpha, double vDM, double param);
        
                double CDF_Scattering_Angle_Electron(double cos_alpha, double vDM);
        
                double Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM, double param);
        
                double Sample_Scattering_Angle_Electron(std::mt19937& PRNG, double vDM);
        
                void Print_Summary(int MPI_rank) const;
        
                void Print_Summary() const;
        
        
                // Wrappers for original constructors: 
            public:
                DM_Particle_SI();
                DM_Particle_SI(double mDM);
                DM_Particle_SI(double mDM, double sigmaP);
        
                // Special pointer-based constructor: 
                DM_Particle_SI(Abstract_DM_Particle_SI* in);
        
                // Copy constructor: 
                DM_Particle_SI(const DM_Particle_SI& in);
        
                // Assignment operator: 
                DM_Particle_SI& operator=(const DM_Particle_SI& in);
        
                // Destructor: 
                ~DM_Particle_SI();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DM_Particle_SI* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Particle_SI_decl_obscura_1_1_0_hpp__ */
