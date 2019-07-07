#ifndef __wrapper_AlphaEM_decl_Pythia_EM_8_212_h__
#define __wrapper_AlphaEM_decl_Pythia_EM_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_AlphaEM.h"
#include "wrapper_Settings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class AlphaEM : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Pythia8::Abstract_AlphaEM* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void init(int orderIn, Pythia8::Settings* settingsPtr);
        
                double alphaEM(double scale2);
        
        
                // Wrappers for original constructors: 
            public:
                AlphaEM();
        
                // Special pointer-based constructor: 
                AlphaEM(Pythia8::Abstract_AlphaEM* in);
        
                // Copy constructor: 
                AlphaEM(const AlphaEM& in);
        
                // Assignment operator: 
                AlphaEM& operator=(const AlphaEM& in);
        
                // Destructor: 
                ~AlphaEM();
        
                // Returns correctly casted pointer to Abstract class: 
                Pythia8::Abstract_AlphaEM* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_AlphaEM_decl_Pythia_EM_8_212_h__ */
