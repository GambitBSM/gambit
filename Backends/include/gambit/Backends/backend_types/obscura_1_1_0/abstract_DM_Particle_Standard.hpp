#ifndef __abstract_DM_Particle_Standard_obscura_1_1_0_hpp__
#define __abstract_DM_Particle_Standard_obscura_1_1_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_DM_Particle_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace obscura
    {
        class Abstract_DM_Particle_Standard : virtual public obscura::Abstract_DM_Particle
        {
            public:
    
                virtual void Set_Mass(double) =0;
    
                virtual double Get_Interaction_Parameter(std::string) const =0;
    
                virtual void Set_Interaction_Parameter(double, std::string) =0;
    
                virtual void Set_Sigma_Proton(double) =0;
    
                virtual void Set_Sigma_Neutron(double) =0;
    
                virtual void Set_Sigma_Electron(double) =0;
    
                virtual void Fix_Coupling_Ratio(double, double) =0;
    
                virtual void Fix_fn_over_fp(double) =0;
    
                virtual void Fix_fp_over_fn(double) =0;
    
                virtual void Unfix_Coupling_Ratios() =0;
    
                virtual double dSigma_dq2_Electron(double, double, double) const =0;
    
                virtual double dSigma_dq2_Electron__BOSS(double, double) const =0;
    
                virtual double Sigma_Proton() const =0;
    
                virtual double Sigma_Neutron() const =0;
    
                virtual double Sigma_Electron() const =0;
    
            public:
                using obscura::Abstract_DM_Particle::pointer_assign__BOSS;
                virtual void pointer_assign__BOSS(Abstract_DM_Particle_Standard*) =0;
                virtual Abstract_DM_Particle_Standard* pointer_copy__BOSS() =0;
    
            private:
                DM_Particle_Standard* wptr;
                bool delete_wrapper;
            public:
                DM_Particle_Standard* get_wptr() { return wptr; }
                void set_wptr(DM_Particle_Standard* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_DM_Particle_Standard()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Particle_Standard(const Abstract_DM_Particle_Standard& in) : 
                    obscura::Abstract_DM_Particle(in)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Particle_Standard& operator=(const Abstract_DM_Particle_Standard&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                DM_Particle_Standard* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                DM_Particle_Standard& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_DM_Particle_Standard() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_DM_Particle_Standard_obscura_1_1_0_hpp__ */
