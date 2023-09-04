#ifndef __wrapper_DecayChannel_decl_Pythia_8_212_h__
#define __wrapper_DecayChannel_decl_Pythia_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_DecayChannel.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class DecayChannel : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_DecayChannel* (*__factory0)(int, double, int, int, int, int, int, int, int, int, int);
                static Abstract_DecayChannel* (*__factory1)(int, double, int, int, int, int, int, int, int, int);
                static Abstract_DecayChannel* (*__factory2)(int, double, int, int, int, int, int, int, int);
                static Abstract_DecayChannel* (*__factory3)(int, double, int, int, int, int, int, int);
                static Abstract_DecayChannel* (*__factory4)(int, double, int, int, int, int, int);
                static Abstract_DecayChannel* (*__factory5)(int, double, int, int, int, int);
                static Abstract_DecayChannel* (*__factory6)(int, double, int, int, int);
                static Abstract_DecayChannel* (*__factory7)(int, double, int, int);
                static Abstract_DecayChannel* (*__factory8)(int, double, int);
                static Abstract_DecayChannel* (*__factory9)(int, double);
                static Abstract_DecayChannel* (*__factory10)(int);
                static Abstract_DecayChannel* (*__factory11)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void onMode(int onModeIn);
        
                void bRatio(double bRatioIn, bool countAsChanged);
        
                void bRatio(double bRatioIn);
        
                void rescaleBR(double fac);
        
                void meMode(int meModeIn);
        
                void multiplicity(int multIn);
        
                void product(int i, int prodIn);
        
                void setHasChanged(bool hasChangedIn);
        
                int onMode() const;
        
                double bRatio() const;
        
                int meMode() const;
        
                int multiplicity() const;
        
                int product(int i) const;
        
                bool hasChanged() const;
        
                bool contains(int id1) const;
        
                bool contains(int id1, int id2) const;
        
                bool contains(int id1, int id2, int id3) const;
        
                void currentBR(double currentBRIn);
        
                double currentBR() const;
        
                void onShellWidth(double onShellWidthIn);
        
                double onShellWidth() const;
        
                void onShellWidthFactor(double factor);
        
                void openSec(int idSgn, double openSecIn);
        
                double openSec(int idSgn) const;
        
        
                // Wrappers for original constructors: 
            public:
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6, int prod7);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0);
                DecayChannel(int onModeIn, double bRatioIn, int meModeIn);
                DecayChannel(int onModeIn, double bRatioIn);
                DecayChannel(int onModeIn);
                DecayChannel();
        
                // Special pointer-based constructor: 
                DecayChannel(Abstract_DecayChannel* in);
        
                // Copy constructor: 
                DecayChannel(const DecayChannel& in);
        
                // Assignment operator: 
                DecayChannel& operator=(const DecayChannel& in);
        
                // Destructor: 
                ~DecayChannel();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_DecayChannel* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DecayChannel_decl_Pythia_8_212_h__ */
