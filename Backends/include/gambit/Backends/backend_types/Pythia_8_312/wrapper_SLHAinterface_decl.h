#ifndef __wrapper_SLHAinterface_decl_Pythia_8_312_h__
#define __wrapper_SLHAinterface_decl_Pythia_8_312_h__

#include <cstddef>
#include <sstream>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SLHAinterface.h"
#include "wrapper_Info_decl.h"
#include "wrapper_SusyLesHouches_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_CoupSM_decl.h"
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
                int& meMode;
        
                // Member functions: 
            public:
                void setPtr(Pythia8::Info* infoPtrIn);
        
                void init(bool& useSHLAcouplings, std::stringstream& ParticleDataBuffer);
        
                bool initSLHA();
        
                void pythia2slha();
        
        
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

#endif /* __wrapper_SLHAinterface_decl_Pythia_8_312_h__ */
