#ifndef __wrapper_UserHooks_decl_Pythia_8_212_h__
#define __wrapper_UserHooks_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_UserHooks.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_SigmaTotal_decl.h"
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
        
                bool canEnhanceEmission();
        
                double enhanceFactor(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > arg_1);
        
                double vetoProbability(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > arg_1);
        
                void setEnhancedEventWeight(double wt);
        
                double getEnhancedEventWeight();
        
                bool canEnhanceTrial();
        
                void setEnhancedTrial(double pTIn, double wtIn);
        
                double getEnhancedTrialPT();
        
                double getEnhancedTrialWeight();
        
                bool canChangeFragPar();
        
                bool doVetoFragmentation(Pythia8::Particle arg_1);
        
        
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

#endif /* __wrapper_UserHooks_decl_Pythia_8_212_h__ */
