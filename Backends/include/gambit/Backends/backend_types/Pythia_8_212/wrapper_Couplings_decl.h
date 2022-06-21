#ifndef __wrapper_Couplings_decl_Pythia_8_212_h__
#define __wrapper_Couplings_decl_Pythia_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Couplings.h"
#include "wrapper_CoupSM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Couplings : public CoupSM
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Couplings* (*__factory0)();
        
                // -- Other member variables: 
            public:
                bool& isSUSY;
        
                // Member functions: 
        
                // Wrappers for original constructors: 
            public:
                Couplings();
        
                // Special pointer-based constructor: 
                Couplings(Abstract_Couplings* in);
        
                // Copy constructor: 
                Couplings(const Couplings& in);
        
                // Assignment operator: 
                Couplings& operator=(const Couplings& in);
        
                // Destructor: 
                ~Couplings();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Couplings* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Couplings_decl_Pythia_8_212_h__ */
