#ifndef __wrapper_DM_Detector_Crystal_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Detector_Crystal_def_obscura_1_1_0_hpp__

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
        inline double DM_Detector_Crystal::Maximum_Energy_Deposit(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const
        {
            return get_BEptr()->Maximum_Energy_Deposit__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector_Crystal::Minimum_DM_Speed(obscura::DM_Particle& DM) const
        {
            return get_BEptr()->Minimum_DM_Speed__BOSS(*DM.get_BEptr());
        }
        
        inline double DM_Detector_Crystal::Minimum_DM_Mass(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const
        {
            return get_BEptr()->Minimum_DM_Mass__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector_Crystal::dRdE(double E, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->dRdE__BOSS(E, *DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline double DM_Detector_Crystal::DM_Signals_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->DM_Signals_Total__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline ::std::vector<double> DM_Detector_Crystal::DM_Signals_Binned(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr)
        {
            return get_BEptr()->DM_Signals_Binned__BOSS(*DM.get_BEptr(), *DM_distr.get_BEptr());
        }
        
        inline void DM_Detector_Crystal::Use_Q_Threshold(unsigned int Q_thr)
        {
            get_BEptr()->Use_Q_Threshold(Q_thr);
        }
        
        inline void DM_Detector_Crystal::Use_Q_Bins(unsigned int Q_thr, unsigned int N_bins)
        {
            get_BEptr()->Use_Q_Bins(Q_thr, N_bins);
        }
        
        inline void DM_Detector_Crystal::Use_Q_Bins(unsigned int Q_thr)
        {
            get_BEptr()->Use_Q_Bins__BOSS(Q_thr);
        }
        
        inline void DM_Detector_Crystal::Print_Summary(int MPI_rank) const
        {
            get_BEptr()->Print_Summary(MPI_rank);
        }
        
        inline void DM_Detector_Crystal::Print_Summary() const
        {
            get_BEptr()->Print_Summary__BOSS();
        }
        
        
        // Wrappers for original constructors: 
        inline DM_Detector_Crystal::DM_Detector_Crystal() :
            DM_Detector(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Detector_Crystal::DM_Detector_Crystal(std::string label, double expo, std::string crys) :
            DM_Detector(__factory1(label, expo, crys))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Detector_Crystal::DM_Detector_Crystal(Abstract_DM_Detector_Crystal* in) :
            DM_Detector(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Detector_Crystal::DM_Detector_Crystal(const DM_Detector_Crystal& in) :
            DM_Detector(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Detector_Crystal& DM_Detector_Crystal::operator=(const DM_Detector_Crystal& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Detector_Crystal::~DM_Detector_Crystal()
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
        inline Abstract_DM_Detector_Crystal* obscura::DM_Detector_Crystal::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Detector_Crystal*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Detector_Crystal_def_obscura_1_1_0_hpp__ */
