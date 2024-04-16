#ifndef __wrapper_ResonanceDecays_def_Pythia_8_212_h__
#define __wrapper_ResonanceDecays_def_Pythia_8_212_h__

#include <vector>
#include "wrapper_Info_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Event_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void ResonanceDecays::init(Pythia8::Info* infoPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn)
        {
            get_BEptr()->init__BOSS((*infoPtrIn).get_BEptr(), (*particleDataPtrIn).get_BEptr(), (*rndmPtrIn).get_BEptr());
        }
        
        inline bool ResonanceDecays::next(Pythia8::Event& process, int iDecNow)
        {
            return get_BEptr()->next__BOSS(*process.get_BEptr(), iDecNow);
        }
        
        inline bool ResonanceDecays::next(Pythia8::Event& process)
        {
            return get_BEptr()->next__BOSS(*process.get_BEptr());
        }
        
        
        // Wrappers for original constructors: 
        inline ResonanceDecays::ResonanceDecays() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline ResonanceDecays::ResonanceDecays(Abstract_ResonanceDecays* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline ResonanceDecays::ResonanceDecays(const ResonanceDecays& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline ResonanceDecays& ResonanceDecays::operator=(const ResonanceDecays& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline ResonanceDecays::~ResonanceDecays()
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
        inline Abstract_ResonanceDecays* Pythia8::ResonanceDecays::get_BEptr() const
        {
            return dynamic_cast<Abstract_ResonanceDecays*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ResonanceDecays_def_Pythia_8_212_h__ */
