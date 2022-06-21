#ifndef __wrapper_PartonLevel_decl_Pythia_8_212_h__
#define __wrapper_PartonLevel_decl_Pythia_8_212_h__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_PartonLevel.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_SigmaTotal_decl.h"
#include "wrapper_UserHooks_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_ResonanceDecays_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class PartonLevel : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_PartonLevel* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                bool next(Pythia8::Event& process, Pythia8::Event& event);
        
                void setupShowerSys(Pythia8::Event& process, Pythia8::Event& event);
        
                bool resonanceShowers(Pythia8::Event& process, Pythia8::Event& event, bool skipForR);
        
                bool wzDecayShowers(Pythia8::Event& event);
        
                bool hasVetoed() const;
        
                bool hasVetoedDiff() const;
        
                void accumulate();
        
                void statistics(bool reset);
        
                void statistics();
        
                void resetStatistics();
        
                void resetTrial();
        
                double pTLastInShower();
        
                int typeLastInShower();
        
        
                // Wrappers for original constructors: 
            public:
                PartonLevel();
        
                // Special pointer-based constructor: 
                PartonLevel(Abstract_PartonLevel* in);
        
                // Copy constructor: 
                PartonLevel(const PartonLevel& in);
        
                // Assignment operator: 
                PartonLevel& operator=(const PartonLevel& in);
        
                // Destructor: 
                ~PartonLevel();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_PartonLevel* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_PartonLevel_decl_Pythia_8_212_h__ */
