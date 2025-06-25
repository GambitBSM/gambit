#ifndef __wrapper_DM_Detector_decl_obscura_1_1_0_hpp__
#define __wrapper_DM_Detector_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include <string>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DM_Detector.hpp"
#include "wrapper_DM_Particle_decl.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class DM_Detector : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DM_Detector* (*__factory0)();
                static Abstract_DM_Detector* (*__factory1)(std::string, double, std::string);
        
                // -- Other member variables: 
            public:
                std::string& name;
        
                // Member functions: 
            public:
                ::std::string Target_Particles();
        
                void Set_Flat_Efficiency(double eff);
        
                double Maximum_Energy_Deposit(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const;
        
                double Minimum_DM_Speed(obscura::DM_Particle& DM) const;
        
                double Minimum_DM_Mass(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const;
        
                double dRdE(double E, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                double DM_Signals_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                double DM_Signal_Rate_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                ::std::vector<double> DM_Signals_Binned(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                double Log_Likelihood(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                double Likelihood(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                ::std::vector<std::vector<double>> Log_Likelihood_Scan(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, const std::vector<double>& masses, const std::vector<double>& couplings);
        
                double P_Value(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                void Set_Observed_Events(long unsigned int N);
        
                void Set_Expected_Background(double B);
        
                void Set_Observed_Events(std::vector<unsigned long> Ni);
        
                void Set_Bin_Efficiencies(const std::vector<double>& eff);
        
                void Set_Expected_Background(const std::vector<double>& Bi);
        
                void Use_Maximum_Gap(std::vector<double> energies);
        
                void Use_Energy_Threshold(double Ethr, double Emax);
        
                void Use_Energy_Bins(double Emin, double Emax, int bins);
        
                double Upper_Limit(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, double certainty);
        
                double Upper_Limit(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                ::std::vector<std::vector<double>> Upper_Limit_Curve(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, std::vector<double> masses, double certainty);
        
                ::std::vector<std::vector<double>> Upper_Limit_Curve(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, std::vector<double> masses);
        
                void Print_Summary(int MPI_rank) const;
        
                void Print_Summary() const;
        
        
                // Wrappers for original constructors: 
            public:
                DM_Detector();
                DM_Detector(std::string label, double expo, std::string target_type);
        
                // Special pointer-based constructor: 
                DM_Detector(Abstract_DM_Detector* in);
        
                // Copy constructor: 
                DM_Detector(const DM_Detector& in);
        
                // Assignment operator: 
                DM_Detector& operator=(const DM_Detector& in);
        
                // Destructor: 
                ~DM_Detector();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DM_Detector* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Detector_decl_obscura_1_1_0_hpp__ */
