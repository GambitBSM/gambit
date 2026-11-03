#ifndef __wrapper_DM_Detector_Ionization_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Detector_Ionization_def_obscura_1_1_0_hpp__

#include <vector>
#include <string>
#include "wrapper_DM_Particle_decl.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        // Member functions: 
        inline double DM_Detector_Ionization::Maximum_Energy_Deposit(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const
        {
            return get_BEptr()->Maximum_Energy_Deposit__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector_Ionization::Minimum_DM_Speed(obscura::DM_Particle& DM) const
        {
            return get_BEptr()->Minimum_DM_Speed__BOSS(*DM.get_BEptr());
        }
        
        inline double DM_Detector_Ionization::Minimum_DM_Mass(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const
        {
            return get_BEptr()->Minimum_DM_Mass__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector_Ionization::dRdE(double E, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->dRdE__BOSS(E, *DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector_Ionization::DM_Signals_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->DM_Signals_Total__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline ::std::vector<double> DM_Detector_Ionization::DM_Signals_Binned(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->DM_Signals_Binned__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector_Ionization::R_ne(unsigned int ne, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->R_ne__BOSS(ne, *DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline void DM_Detector_Ionization::Use_Electron_Threshold(unsigned int ne_thr, unsigned int nemax)
        {
            get_BEptr()->Use_Electron_Threshold(ne_thr, nemax);
        }
        
        inline void DM_Detector_Ionization::Use_Electron_Threshold(unsigned int ne_thr)
        {
            get_BEptr()->Use_Electron_Threshold__BOSS(ne_thr);
        }
        
        inline void DM_Detector_Ionization::Use_Electron_Bins(unsigned int ne_thr, unsigned int N_bins)
        {
            get_BEptr()->Use_Electron_Bins(ne_thr, N_bins);
        }
        
        inline double DM_Detector_Ionization::R_S2(unsigned int S2, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, std::vector<double> electron_spectrum)
        {
            return get_BEptr()->R_S2__BOSS(S2, *DM.get_BEptr(), *DM_distr.get_BEptr(), electron_spectrum);
        }
        
        inline double DM_Detector_Ionization::R_S2(unsigned int S2, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->R_S2__BOSS(S2, *DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline void DM_Detector_Ionization::Use_PE_Threshold(double S2mu, double S2sigma, unsigned int nPE_thr, unsigned int nPE_max)
        {
            get_BEptr()->Use_PE_Threshold(S2mu, S2sigma, nPE_thr, nPE_max);
        }
        
        inline void DM_Detector_Ionization::Import_Trigger_Efficiency_PE(std::string filename)
        {
            get_BEptr()->Import_Trigger_Efficiency_PE(filename);
        }
        
        inline void DM_Detector_Ionization::Import_Acceptance_Efficiency_PE(std::string filename)
        {
            get_BEptr()->Import_Acceptance_Efficiency_PE(filename);
        }
        
        inline void DM_Detector_Ionization::Use_PE_Bins(double S2mu, double S2sigma, const std::vector<unsigned int>& bin_ranges)
        {
            get_BEptr()->Use_PE_Bins(S2mu, S2sigma, bin_ranges);
        }
        
        inline void DM_Detector_Ionization::Print_Summary(int MPI_rank) const
        {
            get_BEptr()->Print_Summary(MPI_rank);
        }
        
        inline void DM_Detector_Ionization::Print_Summary() const
        {
            get_BEptr()->Print_Summary__BOSS();
        }
        
        
        // Wrappers for original constructors: 
        inline DM_Detector_Ionization::DM_Detector_Ionization(std::string label, double expo, std::string target_particles, std::string atom) :
            DM_Detector(__factory0(label, expo, target_particles, atom))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Detector_Ionization::DM_Detector_Ionization(std::string label, double expo, std::string target_particles, std::vector<std::string> atoms, std::vector<double> mass_fractions) :
            DM_Detector(__factory1(label, expo, target_particles, atoms, mass_fractions))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Detector_Ionization::DM_Detector_Ionization(std::string label, double expo, std::string target_particles, std::vector<std::string> atoms) :
            DM_Detector(__factory2(label, expo, target_particles, atoms))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Detector_Ionization::DM_Detector_Ionization(Abstract_DM_Detector_Ionization* in) :
            DM_Detector(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Detector_Ionization::DM_Detector_Ionization(const DM_Detector_Ionization& in) :
            DM_Detector(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Detector_Ionization& DM_Detector_Ionization::operator=(const DM_Detector_Ionization& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Detector_Ionization::~DM_Detector_Ionization()
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
        inline Abstract_DM_Detector_Ionization* obscura::DM_Detector_Ionization::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Detector_Ionization*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Detector_Ionization_def_obscura_1_1_0_hpp__ */
