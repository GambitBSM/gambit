#ifndef __wrapper_SLHAinterface_decl_Pythia_8_212_h__
#define __wrapper_SLHAinterface_decl_Pythia_8_212_h__

#include <cstddef>
#include <sstream>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SLHAinterface.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_SusyLesHouches_decl.h"
#include "wrapper_CoupSUSY_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class SLHAinterface : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_SLHAinterface* (*__factory0)();
        
                // -- Other member variables: 
            public:
                Pythia8::SusyLesHouches& slha;
                Pythia8::CoupSUSY& coupSUSY;
                int& meMode;
        
                // Member functions: 
            public:
                void setPtr(Pythia8::Info* infoPtrIn);
        
                void init(Pythia8::Settings& settings, Pythia8::Rndm* rndmPtr, Pythia8::Couplings* couplingsPtrIn, Pythia8::ParticleData* particleDataPtr, bool& useSHLAcouplings, ::std::basic_stringstream<char>& ParticleDataBuffer);
        
                bool initSLHA(Pythia8::Settings& settings, Pythia8::ParticleData* particleDataPtr);
        
                void pythia2slha(Pythia8::ParticleData* particleDataPtr);
        
        
                // Wrappers for original constructors: 
            public:
                SLHAinterface();
        
                // Special pointer-based constructor: 
                SLHAinterface(Abstract_SLHAinterface* in);
        
                // Copy constructor: 
                SLHAinterface(const SLHAinterface& in);
        
                // Assignment operator: 
                SLHAinterface& operator=(const SLHAinterface& in);
        
                // Destructor: 
                ~SLHAinterface();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_SLHAinterface* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SLHAinterface_decl_Pythia_8_212_h__ */
