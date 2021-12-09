#ifndef __wrapper_ResonanceWidths_decl_Pythia_8_212_h__
#define __wrapper_ResonanceWidths_decl_Pythia_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ResonanceWidths.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Couplings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class ResonanceWidths : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_ResonanceWidths* (*__factory0)(const Pythia8::ResonanceWidths&);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void initBasic(int idResIn, bool isGenericIn);
        
                void initBasic(int idResIn);
        
                bool init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Couplings* couplingsPtrIn);
        
                int id() const;
        
                double width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly, bool setBR, int idOutFlav1, int idOutFlav2);
        
                double width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly, bool setBR, int idOutFlav1);
        
                double width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly, bool setBR);
        
                double width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly);
        
                double width(int idSgn, double mHatIn, int idInFlavIn);
        
                double width(int idSgn, double mHatIn);
        
                double widthOpen(int idSgn, double mHatIn, int idIn);
        
                double widthOpen(int idSgn, double mHatIn);
        
                double widthStore(int idSgn, double mHatIn, int idIn);
        
                double widthStore(int idSgn, double mHatIn);
        
                double openFrac(int idSgn);
        
                double widthRescaleFactor();
        
                double widthChan(double mHatIn, int idOutFlav1, int idOutFlav2);
        
        
                // Wrappers for original constructors: 
            public:
                ResonanceWidths(const Pythia8::ResonanceWidths& arg_1);
        
                // Special pointer-based constructor: 
                ResonanceWidths(Abstract_ResonanceWidths* in);
        
                // Assignment operator: 
                ResonanceWidths& operator=(const ResonanceWidths& in);
        
                // Destructor: 
                ~ResonanceWidths();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_ResonanceWidths* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ResonanceWidths_decl_Pythia_8_212_h__ */
