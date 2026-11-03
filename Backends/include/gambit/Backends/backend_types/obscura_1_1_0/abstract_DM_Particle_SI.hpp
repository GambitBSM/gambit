#ifndef __abstract_DM_Particle_SI_obscura_1_1_0_hpp__
#define __abstract_DM_Particle_SI_obscura_1_1_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include <random>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_DM_Particle_Standard_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace obscura
    {
        class Abstract_DM_Particle_SI : virtual public obscura::Abstract_DM_Particle_Standard
        {
            public:
    
                virtual void Set_FormFactor_DM(std::string, double) =0;
    
                virtual void Set_FormFactor_DM__BOSS(std::string) =0;
    
                virtual void Set_Mediator_Mass(double) =0;
    
                virtual double dSigma_dq2_Electron(double, double, double) const =0;
    
                virtual double dSigma_dq2_Electron__BOSS(double, double) const =0;
    
                virtual bool Is_Sigma_Total_V_Dependent() const =0;
    
                virtual double Sigma_Total_Electron(double, double) =0;
    
                virtual double Sigma_Total_Electron__BOSS(double) =0;
    
                virtual double PDF_Scattering_Angle_Electron(double, double, double) =0;
    
                virtual double PDF_Scattering_Angle_Electron__BOSS(double, double) =0;
    
                virtual double CDF_Scattering_Angle_Electron(double, double, double) =0;
    
                virtual double CDF_Scattering_Angle_Electron__BOSS(double, double) =0;
    
                virtual double Sample_Scattering_Angle_Electron(std::mt19937&, double, double) =0;
    
                virtual double Sample_Scattering_Angle_Electron__BOSS(std::mt19937&, double) =0;
    
                virtual void Print_Summary(int) const =0;
    
                virtual void Print_Summary__BOSS() const =0;
    
            public:
                using obscura::Abstract_DM_Particle_Standard::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_DM_Particle_SI*) =0;
                virtual Abstract_DM_Particle_SI* pointer_copy__BOSS() =0;
    
            private:
                DM_Particle_SI* wptr;
                bool delete_wrapper;
            public:
                DM_Particle_SI* get_wptr() { return wptr; }
                void set_wptr(DM_Particle_SI* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_DM_Particle_SI()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Particle_SI(const Abstract_DM_Particle_SI& in) : 
                    obscura::Abstract_DM_Particle(in), obscura::Abstract_DM_Particle_Standard(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Particle_SI& operator=(const Abstract_DM_Particle_SI&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                DM_Particle_SI* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                DM_Particle_SI& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_DM_Particle_SI() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_DM_Particle_SI_obscura_1_1_0_hpp__ */
