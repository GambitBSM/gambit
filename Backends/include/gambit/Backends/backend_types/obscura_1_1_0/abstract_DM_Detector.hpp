#ifndef __abstract_DM_Detector_obscura_1_1_0_hpp__
#define __abstract_DM_Detector_obscura_1_1_0_hpp__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"
#include "wrapper_DM_Particle_decl.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace obscura
    {
        class Abstract_DM_Detector : public virtual AbstractBase
        {
            public:
    
                virtual std::string& name_ref__BOSS() =0;
    
                virtual ::std::string Target_Particles() =0;
    
                virtual void Set_Flat_Efficiency(double) =0;
    
                virtual double Maximum_Energy_Deposit__BOSS(obscura::Abstract_DM_Particle&, const obscura::Abstract_DM_Distribution&) const =0;
    
                virtual double Minimum_DM_Speed__BOSS(obscura::Abstract_DM_Particle&) const =0;
    
                virtual double Minimum_DM_Mass__BOSS(obscura::Abstract_DM_Particle&, const obscura::Abstract_DM_Distribution&) const =0;
    
                virtual double dRdE__BOSS(double, const obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual double DM_Signals_Total__BOSS(const obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual double DM_Signal_Rate_Total__BOSS(const obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual ::std::vector<double> DM_Signals_Binned__BOSS(const obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual double Log_Likelihood__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual double Likelihood__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual ::std::vector<std::vector<double>> Log_Likelihood_Scan__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&, const std::vector<double>&, const std::vector<double>&) =0;
    
                virtual double P_Value__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual void Set_Observed_Events(long unsigned int) =0;
    
                virtual void Set_Expected_Background(double) =0;
    
                virtual void Set_Observed_Events(std::vector<unsigned long>) =0;
    
                virtual void Set_Bin_Efficiencies(const std::vector<double>&) =0;
    
                virtual void Set_Expected_Background(const std::vector<double>&) =0;
    
                virtual void Use_Maximum_Gap(std::vector<double>) =0;
    
                virtual void Use_Energy_Threshold(double, double) =0;
    
                virtual void Use_Energy_Bins(double, double, int) =0;
    
                virtual double Upper_Limit__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&, double) =0;
    
                virtual double Upper_Limit__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&) =0;
    
                virtual ::std::vector<std::vector<double>> Upper_Limit_Curve__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&, std::vector<double>, double) =0;
    
                virtual ::std::vector<std::vector<double>> Upper_Limit_Curve__BOSS(obscura::Abstract_DM_Particle&, obscura::Abstract_DM_Distribution&, std::vector<double>) =0;
    
                virtual void Print_Summary(int) const =0;
    
                virtual void Print_Summary__BOSS() const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_DM_Detector*) =0;
                virtual Abstract_DM_Detector* pointer_copy__BOSS() =0;
    
            private:
                DM_Detector* wptr;
                bool delete_wrapper;
            public:
                DM_Detector* get_wptr() { return wptr; }
                void set_wptr(DM_Detector* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_DM_Detector()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Detector(const Abstract_DM_Detector&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_DM_Detector& operator=(const Abstract_DM_Detector&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                DM_Detector* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                DM_Detector& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_DM_Detector() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_DM_Detector_obscura_1_1_0_hpp__ */
