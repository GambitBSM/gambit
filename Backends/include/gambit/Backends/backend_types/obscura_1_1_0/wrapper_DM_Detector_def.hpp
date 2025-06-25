#ifndef __wrapper_DM_Detector_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Detector_def_obscura_1_1_0_hpp__

#include <string>
#include <vector>
#include "wrapper_DM_Particle_decl.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        // Member functions: 
        inline ::std::string DM_Detector::Target_Particles()
        {
            return get_BEptr()->Target_Particles();
        }
        
        inline void DM_Detector::Set_Flat_Efficiency(double eff)
        {
            get_BEptr()->Set_Flat_Efficiency(eff);
        }
        
        inline double DM_Detector::Maximum_Energy_Deposit(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const
        {
            return get_BEptr()->Maximum_Energy_Deposit__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector::Minimum_DM_Speed(obscura::DM_Particle& DM) const
        {
            return get_BEptr()->Minimum_DM_Speed__BOSS(*DM.get_BEptr());
        }
        
        inline double DM_Detector::Minimum_DM_Mass(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const
        {
            return get_BEptr()->Minimum_DM_Mass__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector::dRdE(double E, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->dRdE__BOSS(E, *DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector::DM_Signals_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->DM_Signals_Total__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector::DM_Signal_Rate_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->DM_Signal_Rate_Total__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline ::std::vector<double> DM_Detector::DM_Signals_Binned(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->DM_Signals_Binned__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector::Log_Likelihood(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->Log_Likelihood__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector::Likelihood(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->Likelihood__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline ::std::vector<std::vector<double>> DM_Detector::Log_Likelihood_Scan(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, const std::vector<double>& masses, const std::vector<double>& couplings)
        {
            return get_BEptr()->Log_Likelihood_Scan__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr(), masses, couplings);
        }
        
        inline double DM_Detector::P_Value(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->P_Value__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline void DM_Detector::Set_Observed_Events(long unsigned int N)
        {
            get_BEptr()->Set_Observed_Events(N);
        }
        
        inline void DM_Detector::Set_Expected_Background(double B)
        {
            get_BEptr()->Set_Expected_Background(B);
        }
        
        inline void DM_Detector::Set_Observed_Events(std::vector<unsigned long> Ni)
        {
            get_BEptr()->Set_Observed_Events(Ni);
        }
        
        inline void DM_Detector::Set_Bin_Efficiencies(const std::vector<double>& eff)
        {
            get_BEptr()->Set_Bin_Efficiencies(eff);
        }
        
        inline void DM_Detector::Set_Expected_Background(const std::vector<double>& Bi)
        {
            get_BEptr()->Set_Expected_Background(Bi);
        }
        
        inline void DM_Detector::Use_Maximum_Gap(std::vector<double> energies)
        {
            get_BEptr()->Use_Maximum_Gap(energies);
        }
        
        inline void DM_Detector::Use_Energy_Threshold(double Ethr, double Emax)
        {
            get_BEptr()->Use_Energy_Threshold(Ethr, Emax);
        }
        
        inline void DM_Detector::Use_Energy_Bins(double Emin, double Emax, int bins)
        {
            get_BEptr()->Use_Energy_Bins(Emin, Emax, bins);
        }
        
        inline double DM_Detector::Upper_Limit(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, double certainty)
        {
            return get_BEptr()->Upper_Limit__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr(), certainty);
        }
        
        inline double DM_Detector::Upper_Limit(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->Upper_Limit__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline ::std::vector<std::vector<double>> DM_Detector::Upper_Limit_Curve(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, std::vector<double> masses, double certainty)
        {
            return get_BEptr()->Upper_Limit_Curve__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr(), masses, certainty);
        }
        
        inline ::std::vector<std::vector<double>> DM_Detector::Upper_Limit_Curve(obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr, std::vector<double> masses)
        {
            return get_BEptr()->Upper_Limit_Curve__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr(), masses);
        }
        
        inline void DM_Detector::Print_Summary(int MPI_rank) const
        {
            get_BEptr()->Print_Summary(MPI_rank);
        }
        
        inline void DM_Detector::Print_Summary() const
        {
            get_BEptr()->Print_Summary__BOSS();
        }
        
        
        // Wrappers for original constructors: 
        inline DM_Detector::DM_Detector() :
            WrapperBase(__factory0()),
            name( get_BEptr()->name_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Detector::DM_Detector(std::string label, double expo, std::string target_type) :
            WrapperBase(__factory1(label, expo, target_type)),
            name( get_BEptr()->name_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Detector::DM_Detector(Abstract_DM_Detector* in) :
            WrapperBase(in),
            name( get_BEptr()->name_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Detector::DM_Detector(const DM_Detector& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            name( get_BEptr()->name_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Detector& DM_Detector::operator=(const DM_Detector& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Detector::~DM_Detector()
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
        inline Abstract_DM_Detector* obscura::DM_Detector::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Detector*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Detector_def_obscura_1_1_0_hpp__ */
