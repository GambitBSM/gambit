#ifndef __wrapper_DM_Detector_Crystal_decl_obscura_1_1_0_hpp__
#define __wrapper_DM_Detector_Crystal_decl_obscura_1_1_0_hpp__

#include <cstddef>
#include <vector>
#include <string>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DM_Detector_Crystal.hpp"
#include "wrapper_DM_Detector_decl.hpp"
#include "wrapper_DM_Particle_decl.hpp"
#include "wrapper_DM_Distribution_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace obscura
    {
        
        class DM_Detector_Crystal : public DM_Detector
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DM_Detector_Crystal* (*__factory0)();
                static Abstract_DM_Detector_Crystal* (*__factory1)(std::string, double, std::string);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                double Maximum_Energy_Deposit(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const;
        
                double Minimum_DM_Speed(obscura::DM_Particle& DM) const;
        
                double Minimum_DM_Mass(obscura::DM_Particle& DM, const obscura::DM_Distribution& DM_distr) const;
        
                double dRdE(double E, const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                double DM_Signals_Total(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                ::std::vector<double> DM_Signals_Binned(const obscura::DM_Particle& DM, obscura::DM_Distribution& DM_distr);
        
                void Use_Q_Threshold(unsigned int Q_thr);
        
                void Use_Q_Bins(unsigned int Q_thr, unsigned int N_bins);
        
                void Use_Q_Bins(unsigned int Q_thr);
        
                void Print_Summary(int MPI_rank) const;
        
                void Print_Summary() const;
        
        
                // Wrappers for original constructors: 
            public:
                DM_Detector_Crystal();
                DM_Detector_Crystal(std::string label, double expo, std::string crys);
        
                // Special pointer-based constructor: 
                DM_Detector_Crystal(Abstract_DM_Detector_Crystal* in);
        
                // Copy constructor: 
                DM_Detector_Crystal(const DM_Detector_Crystal& in);
        
                // Assignment operator: 
                DM_Detector_Crystal& operator=(const DM_Detector_Crystal& in);
        
                // Destructor: 
                ~DM_Detector_Crystal();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DM_Detector_Crystal* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Detector_Crystal_decl_obscura_1_1_0_hpp__ */
