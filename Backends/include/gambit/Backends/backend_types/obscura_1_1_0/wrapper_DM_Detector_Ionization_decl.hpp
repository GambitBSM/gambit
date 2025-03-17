#ifndef __wrapper_DM_Detector_Ionization_decl_obscura_1_1_0_hpp__
#define __wrapper_DM_Detector_Ionization_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include <vector>
#include <string>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DM_Detector_Ionization.hpp"
#include "wrapper_DM_Detector_decl.hpp"
#include "wrapper_DM_Particle_decl.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class DM_Detector_Ionization : public DM_Detector
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DM_Detector_Ionization* (*__factory0)(std::string, double, std::string, std::string);
                static Abstract_DM_Detector_Ionization* (*__factory1)(std::string, double, std::string, std::vector<std::string>, std::vector<double>);
                static Abstract_DM_Detector_Ionization* (*__factory2)(std::string, double, std::string, std::vector<std::string>);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                double Maximum_Energy_Deposit(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const;
        
                double Minimum_DM_Speed(obscura::DM_Particle& DM) const;
        
                double Minimum_DM_Mass(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const;
        
                double dRdE(double E, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                double DM_Signals_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                ::std::vector<double> DM_Signals_Binned(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                double R_ne(unsigned int ne, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                void Use_Electron_Threshold(unsigned int ne_thr, unsigned int nemax);
        
                void Use_Electron_Threshold(unsigned int ne_thr);
        
                void Use_Electron_Bins(unsigned int ne_thr, unsigned int N_bins);
        
                double R_S2(unsigned int S2, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, std::vector<double> electron_spectrum);
        
                double R_S2(unsigned int S2, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                void Use_PE_Threshold(double S2mu, double S2sigma, unsigned int nPE_thr, unsigned int nPE_max);
        
                void Import_Trigger_Efficiency_PE(std::string filename);
        
                void Import_Acceptance_Efficiency_PE(std::string filename);
        
                void Use_PE_Bins(double S2mu, double S2sigma, const std::vector<unsigned int>& bin_ranges);
        
                void Print_Summary(int MPI_rank) const;
        
                void Print_Summary() const;
        
        
                // Wrappers for original constructors: 
            public:
                DM_Detector_Ionization(std::string label, double expo, std::string target_particles, std::string atom);
                DM_Detector_Ionization(std::string label, double expo, std::string target_particles, std::vector<std::string> atoms, std::vector<double> mass_fractions);
                DM_Detector_Ionization(std::string label, double expo, std::string target_particles, std::vector<std::string> atoms);
        
                // Special pointer-based constructor: 
                DM_Detector_Ionization(Abstract_DM_Detector_Ionization* in);
        
                // Copy constructor: 
                DM_Detector_Ionization(const DM_Detector_Ionization& in);
        
                // Assignment operator: 
                DM_Detector_Ionization& operator=(const DM_Detector_Ionization& in);
        
                // Destructor: 
                ~DM_Detector_Ionization();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DM_Detector_Ionization* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Detector_Ionization_decl_obscura_1_1_0_hpp__ */
