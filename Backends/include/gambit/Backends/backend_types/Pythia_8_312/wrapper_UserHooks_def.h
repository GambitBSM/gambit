#ifndef __wrapper_UserHooks_def_Pythia_8_312_h__
#define __wrapper_UserHooks_def_Pythia_8_312_h__

#include <vector>
#include "wrapper_SigmaProcess_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Particle_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline bool UserHooks::initAfterBeams()
        {
            return get_BEptr()->initAfterBeams();
        }
        
        inline bool UserHooks::canModifySigma()
        {
            return get_BEptr()->canModifySigma();
        }
        
        inline bool UserHooks::canBiasSelection()
        {
            return get_BEptr()->canBiasSelection();
        }
        
        inline double UserHooks::biasedSelectionWeight()
        {
            return get_BEptr()->biasedSelectionWeight();
        }
        
        inline bool UserHooks::canVetoProcessLevel()
        {
            return get_BEptr()->canVetoProcessLevel();
        }
        
        inline bool UserHooks::doVetoProcessLevel(Pythia8::Event& arg_1)
        {
            return get_BEptr()->doVetoProcessLevel__BOSS(*arg_1.get_BEptr());
        }
        
        inline bool UserHooks::canSetLowEnergySigma(int arg_1, int arg_2) const
        {
            return get_BEptr()->canSetLowEnergySigma(arg_1, arg_2);
        }
        
        inline double UserHooks::doSetLowEnergySigma(int arg_1, int arg_2, double arg_3, double arg_4, double arg_5) const
        {
            return get_BEptr()->doSetLowEnergySigma(arg_1, arg_2, arg_3, arg_4, arg_5);
        }
        
        inline bool UserHooks::canVetoResonanceDecays()
        {
            return get_BEptr()->canVetoResonanceDecays();
        }
        
        inline bool UserHooks::doVetoResonanceDecays(Pythia8::Event& arg_1)
        {
            return get_BEptr()->doVetoResonanceDecays__BOSS(*arg_1.get_BEptr());
        }
        
        inline bool UserHooks::canVetoPT()
        {
            return get_BEptr()->canVetoPT();
        }
        
        inline double UserHooks::scaleVetoPT()
        {
            return get_BEptr()->scaleVetoPT();
        }
        
        inline bool UserHooks::doVetoPT(int arg_1, const Pythia8::Event& arg_2)
        {
            return get_BEptr()->doVetoPT__BOSS(arg_1, *arg_2.get_BEptr());
        }
        
        inline bool UserHooks::canVetoStep()
        {
            return get_BEptr()->canVetoStep();
        }
        
        inline int UserHooks::numberVetoStep()
        {
            return get_BEptr()->numberVetoStep();
        }
        
        inline bool UserHooks::doVetoStep(int arg_1, int arg_2, int arg_3, const Pythia8::Event& arg_4)
        {
            return get_BEptr()->doVetoStep__BOSS(arg_1, arg_2, arg_3, *arg_4.get_BEptr());
        }
        
        inline bool UserHooks::canVetoMPIStep()
        {
            return get_BEptr()->canVetoMPIStep();
        }
        
        inline int UserHooks::numberVetoMPIStep()
        {
            return get_BEptr()->numberVetoMPIStep();
        }
        
        inline bool UserHooks::doVetoMPIStep(int arg_1, const Pythia8::Event& arg_2)
        {
            return get_BEptr()->doVetoMPIStep__BOSS(arg_1, *arg_2.get_BEptr());
        }
        
        inline bool UserHooks::canVetoPartonLevelEarly()
        {
            return get_BEptr()->canVetoPartonLevelEarly();
        }
        
        inline bool UserHooks::doVetoPartonLevelEarly(const Pythia8::Event& arg_1)
        {
            return get_BEptr()->doVetoPartonLevelEarly__BOSS(*arg_1.get_BEptr());
        }
        
        inline bool UserHooks::retryPartonLevel()
        {
            return get_BEptr()->retryPartonLevel();
        }
        
        inline bool UserHooks::canVetoPartonLevel()
        {
            return get_BEptr()->canVetoPartonLevel();
        }
        
        inline bool UserHooks::doVetoPartonLevel(const Pythia8::Event& arg_1)
        {
            return get_BEptr()->doVetoPartonLevel__BOSS(*arg_1.get_BEptr());
        }
        
        inline bool UserHooks::canSetResonanceScale()
        {
            return get_BEptr()->canSetResonanceScale();
        }
        
        inline double UserHooks::scaleResonance(int arg_1, const Pythia8::Event& arg_2)
        {
            return get_BEptr()->scaleResonance__BOSS(arg_1, *arg_2.get_BEptr());
        }
        
        inline bool UserHooks::canVetoISREmission()
        {
            return get_BEptr()->canVetoISREmission();
        }
        
        inline bool UserHooks::doVetoISREmission(int arg_1, const Pythia8::Event& arg_2, int arg_3)
        {
            return get_BEptr()->doVetoISREmission__BOSS(arg_1, *arg_2.get_BEptr(), arg_3);
        }
        
        inline bool UserHooks::canVetoFSREmission()
        {
            return get_BEptr()->canVetoFSREmission();
        }
        
        inline bool UserHooks::doVetoFSREmission(int arg_1, const Pythia8::Event& arg_2, int arg_3, bool arg_4)
        {
            return get_BEptr()->doVetoFSREmission__BOSS(arg_1, *arg_2.get_BEptr(), arg_3, arg_4);
        }
        
        inline bool UserHooks::doVetoFSREmission(int arg_1, const Pythia8::Event& arg_2, int arg_3)
        {
            return get_BEptr()->doVetoFSREmission__BOSS(arg_1, *arg_2.get_BEptr(), arg_3);
        }
        
        inline bool UserHooks::canVetoMPIEmission()
        {
            return get_BEptr()->canVetoMPIEmission();
        }
        
        inline bool UserHooks::doVetoMPIEmission(int arg_1, const Pythia8::Event& arg_2)
        {
            return get_BEptr()->doVetoMPIEmission__BOSS(arg_1, *arg_2.get_BEptr());
        }
        
        inline bool UserHooks::canReconnectResonanceSystems()
        {
            return get_BEptr()->canReconnectResonanceSystems();
        }
        
        inline bool UserHooks::doReconnectResonanceSystems(int arg_1, Pythia8::Event& arg_2)
        {
            return get_BEptr()->doReconnectResonanceSystems__BOSS(arg_1, *arg_2.get_BEptr());
        }
        
        inline bool UserHooks::canChangeFragPar()
        {
            return get_BEptr()->canChangeFragPar();
        }
        
        inline bool UserHooks::canVetoAfterHadronization()
        {
            return get_BEptr()->canVetoAfterHadronization();
        }
        
        inline bool UserHooks::doVetoAfterHadronization(const Pythia8::Event& arg_1)
        {
            return get_BEptr()->doVetoAfterHadronization__BOSS(*arg_1.get_BEptr());
        }
        
        inline bool UserHooks::canSetImpactParameter() const
        {
            return get_BEptr()->canSetImpactParameter();
        }
        
        inline double UserHooks::doSetImpactParameter()
        {
            return get_BEptr()->doSetImpactParameter();
        }
        
        
        // Wrappers for original constructors: 
        inline UserHooks::UserHooks(const Pythia8::UserHooks& arg_1) :
            WrapperBase(__factory0(arg_1))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline UserHooks::UserHooks(Abstract_UserHooks* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline UserHooks& UserHooks::operator=(const UserHooks& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline UserHooks::~UserHooks()
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
        inline Abstract_UserHooks* Pythia8::UserHooks::get_BEptr() const
        {
            return dynamic_cast<Abstract_UserHooks*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_UserHooks_def_Pythia_8_312_h__ */
