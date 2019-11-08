#ifndef __wrapper_ResonanceDecays_decl_Pythia_EM_8_212_h__
#define __wrapper_ResonanceDecays_decl_Pythia_EM_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ResonanceDecays.h"
#include "wrapper_Info_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Event_decl.h"
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class ResonanceDecays : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Pythia8::Abstract_ResonanceDecays* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void init(Pythia8::Info* infoPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Rndm* rndmPtrIn);
        
                bool next(Pythia8::Event& process, int iDecNow);
        
                bool next(Pythia8::Event& process);
        
        
                // Wrappers for original constructors: 
            public:
                ResonanceDecays();
        
                // Special pointer-based constructor: 
                ResonanceDecays(Pythia8::Abstract_ResonanceDecays* in);
        
                // Copy constructor: 
                ResonanceDecays(const ResonanceDecays& in);
        
                // Assignment operator: 
                ResonanceDecays& operator=(const ResonanceDecays& in);
        
                // Destructor: 
                ~ResonanceDecays();
        
                // Returns correctly casted pointer to Abstract class: 
                Pythia8::Abstract_ResonanceDecays* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ResonanceDecays_decl_Pythia_EM_8_212_h__ */
