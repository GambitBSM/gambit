#ifndef __wrapper_CombineMatchingInput_decl_Pythia_VLQ_8_212_h__
#define __wrapper_CombineMatchingInput_decl_Pythia_VLQ_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_CombineMatchingInput.h"
#include "wrapper_Pythia_decl.h"
#include "wrapper_UserHooks_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class CombineMatchingInput : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_CombineMatchingInput* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                Pythia8::UserHooks* getHook(Pythia8::Pythia& pythia);
        
        
                // Wrappers for original constructors: 
            public:
                CombineMatchingInput();
        
                // Special pointer-based constructor: 
                CombineMatchingInput(Abstract_CombineMatchingInput* in);
        
                // Copy constructor: 
                CombineMatchingInput(const CombineMatchingInput& in);
        
                // Assignment operator: 
                CombineMatchingInput& operator=(const CombineMatchingInput& in);
        
                // Destructor: 
                ~CombineMatchingInput();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_CombineMatchingInput* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_CombineMatchingInput_decl_Pythia_VLQ_8_212_h__ */
