#ifndef __wrapper_UserHooks_decl_Pythia_8_312_h__
#define __wrapper_UserHooks_decl_Pythia_8_312_h__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_UserHooks.h"
#include "wrapper_SigmaProcess_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Particle_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class UserHooks : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_UserHooks* (*__factory0)(const Pythia8::UserHooks&);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                bool initAfterBeams();
        
                bool canModifySigma();
        
                bool canBiasSelection();
        
                double biasedSelectionWeight();
        
                bool canVetoProcessLevel();
        
                bool doVetoProcessLevel(Pythia8::Event& arg_1);
        
                bool canSetLowEnergySigma(int arg_1, int arg_2) const;
        
                double doSetLowEnergySigma(int arg_1, int arg_2, double arg_3, double arg_4, double arg_5) const;
        
                bool canVetoResonanceDecays();
        
                bool doVetoResonanceDecays(Pythia8::Event& arg_1);
        
                bool canVetoPT();
        
                double scaleVetoPT();
        
                bool doVetoPT(int arg_1, const Pythia8::Event& arg_2);
        
                bool canVetoStep();
        
                int numberVetoStep();
        
                bool doVetoStep(int arg_1, int arg_2, int arg_3, const Pythia8::Event& arg_4);
        
                bool canVetoMPIStep();
        
                int numberVetoMPIStep();
        
                bool doVetoMPIStep(int arg_1, const Pythia8::Event& arg_2);
        
                bool canVetoPartonLevelEarly();
        
                bool doVetoPartonLevelEarly(const Pythia8::Event& arg_1);
        
                bool retryPartonLevel();
        
                bool canVetoPartonLevel();
        
                bool doVetoPartonLevel(const Pythia8::Event& arg_1);
        
                bool canSetResonanceScale();
        
                double scaleResonance(int arg_1, const Pythia8::Event& arg_2);
        
                bool canVetoISREmission();
        
                bool doVetoISREmission(int arg_1, const Pythia8::Event& arg_2, int arg_3);
        
                bool canVetoFSREmission();
        
                bool doVetoFSREmission(int arg_1, const Pythia8::Event& arg_2, int arg_3, bool arg_4);
        
                bool doVetoFSREmission(int arg_1, const Pythia8::Event& arg_2, int arg_3);
        
                bool canVetoMPIEmission();
        
                bool doVetoMPIEmission(int arg_1, const Pythia8::Event& arg_2);
        
                bool canReconnectResonanceSystems();
        
                bool doReconnectResonanceSystems(int arg_1, Pythia8::Event& arg_2);
        
                bool canChangeFragPar();
        
                bool canVetoAfterHadronization();
        
                bool doVetoAfterHadronization(const Pythia8::Event& arg_1);
        
                bool canSetImpactParameter() const;
        
                double doSetImpactParameter();
        
        
                // Wrappers for original constructors: 
            public:
                UserHooks(const Pythia8::UserHooks& arg_1);
        
                // Special pointer-based constructor: 
                UserHooks(Abstract_UserHooks* in);
        
                // Assignment operator: 
                UserHooks& operator=(const UserHooks& in);
        
                // Destructor: 
                ~UserHooks();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_UserHooks* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_UserHooks_decl_Pythia_8_312_h__ */
