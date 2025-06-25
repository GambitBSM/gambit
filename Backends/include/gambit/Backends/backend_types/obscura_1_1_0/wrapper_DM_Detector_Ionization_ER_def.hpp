#ifndef __wrapper_DM_Detector_Ionization_ER_def_obscura_1_1_0_hpp__
#define __wrapper_DM_Detector_Ionization_ER_def_obscura_1_1_0_hpp__

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
        
        // Wrappers for original constructors: 
        inline DM_Detector_Ionization_ER::DM_Detector_Ionization_ER() :
            DM_Detector_Ionization(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Detector_Ionization_ER::DM_Detector_Ionization_ER(std::string label, double expo, std::string atom) :
            DM_Detector_Ionization(__factory1(label, expo, atom))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Detector_Ionization_ER::DM_Detector_Ionization_ER(std::string label, double expo, std::vector<std::string> atoms, std::vector<double> mass_fractions) :
            DM_Detector_Ionization(__factory2(label, expo, atoms, mass_fractions))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DM_Detector_Ionization_ER::DM_Detector_Ionization_ER(std::string label, double expo, std::vector<std::string> atoms) :
            DM_Detector_Ionization(__factory3(label, expo, atoms))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DM_Detector_Ionization_ER::DM_Detector_Ionization_ER(Abstract_DM_Detector_Ionization_ER* in) :
            DM_Detector_Ionization(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DM_Detector_Ionization_ER::DM_Detector_Ionization_ER(const DM_Detector_Ionization_ER& in) :
            DM_Detector_Ionization(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DM_Detector_Ionization_ER& DM_Detector_Ionization_ER::operator=(const DM_Detector_Ionization_ER& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DM_Detector_Ionization_ER::~DM_Detector_Ionization_ER()
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
        inline Abstract_DM_Detector_Ionization_ER* obscura::DM_Detector_Ionization_ER::get_BEptr() const
        {
            return dynamic_cast<Abstract_DM_Detector_Ionization_ER*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DM_Detector_Ionization_ER_def_obscura_1_1_0_hpp__ */
