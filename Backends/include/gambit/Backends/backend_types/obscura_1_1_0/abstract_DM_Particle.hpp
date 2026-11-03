#ifndef __abstract_DM_Particle_obscura_1_1_0_hpp__
#define __abstract_DM_Particle_obscura_1_1_0_hpp__

#include <cstddef>
#include <iostream>
#include <random>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace obscura
    {
        class Abstract_DM_Particle : public virtual AbstractBase
        {
            public:
    
                virtual double& mass_ref__BOSS() =0;
    
                virtual double& spin_ref__BOSS() =0;
    
                virtual double& fractional_density_ref__BOSS() =0;
    
                virtual bool& DD_use_eta_function_ref__BOSS() =0;
    
                virtual void Set_Mass(double) =0;
    
                virtual void Set_Spin(double) =0;
    
                virtual void Set_Low_Mass_Mode(bool) =0;
    
                virtual void Set_Fractional_Density(double) =0;
    
                virtual double Get_Interaction_Parameter(std::string) const =0;
    
                virtual void Set_Interaction_Parameter(double, std::string) =0;
    
                virtual bool Interaction_Parameter_Is_Cross_Section() const =0;
    
                virtual void Set_Sigma_Proton(double) =0;
    
                virtual void Set_Sigma_Neutron(double) =0;
    
                virtual void Set_Sigma_Electron(double) =0;
    
                virtual double dSigma_dq2_Electron(double, double, double) const =0;
    
                virtual double dSigma_dq2_Electron__BOSS(double, double) const =0;
    
                virtual double Sigma_Proton() const =0;
    
                virtual double Sigma_Neutron() const =0;
    
                virtual double Sigma_Electron() const =0;
    
                virtual bool Is_Sigma_Total_V_Dependent() const =0;
    
                virtual double Sigma_Total_Electron(double, double) =0;
    
                virtual double Sigma_Total_Electron__BOSS(double) =0;
    
                virtual void Print_Summary(int) const =0;
    
                virtual void Print_Summary__BOSS() const =0;
    
                virtual double PDF_Scattering_Angle_Electron(double, double, double) =0;
    
                virtual double PDF_Scattering_Angle_Electron__BOSS(double, double) =0;
    
                virtual double CDF_Scattering_Angle_Electron(double, double, double) =0;
    
                virtual double CDF_Scattering_Angle_Electron__BOSS(double, double) =0;
    
                virtual double Sample_Scattering_Angle_Electron(std::mt19937&, double, double) =0;
    
                virtual double Sample_Scattering_Angle_Electron__BOSS(std::mt19937&, double) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_DM_Particle*) =0;
                virtual Abstract_DM_Particle* pointer_copy__BOSS() =0;
    
            private:
                DM_Particle* wptr;
                bool delete_wrapper;
            public:
                DM_Particle* get_wptr() { return wptr; }
                void set_wptr(DM_Particle* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_DM_Particle()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Particle(const Abstract_DM_Particle&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Particle& operator=(const Abstract_DM_Particle&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                DM_Particle* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                DM_Particle& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_DM_Particle() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_DM_Particle_obscura_1_1_0_hpp__ */
