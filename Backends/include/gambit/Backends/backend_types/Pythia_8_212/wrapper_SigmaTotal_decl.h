#ifndef __wrapper_SigmaTotal_decl_Pythia_8_212_h__
#define __wrapper_SigmaTotal_decl_Pythia_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SigmaTotal.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class SigmaTotal : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_SigmaTotal* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void init(Pythia8::Info* infoPtrIn, Pythia8::Settings& settings, Pythia8::ParticleData* particleDataPtrIn);
        
                bool calc(int idA, int idB, double eCM);
        
                bool hasSigmaTot() const;
        
                double sigmaTot() const;
        
                double sigmaEl() const;
        
                double sigmaXB() const;
        
                double sigmaAX() const;
        
                double sigmaXX() const;
        
                double sigmaAXB() const;
        
                double sigmaND() const;
        
                bool calcMBRxsecs(int idA, int idB, double eCM);
        
                double ddpMax() const;
        
                double sdpMax() const;
        
                double dpepMax() const;
        
                double bSlopeEl() const;
        
                double bSlopeXB(double sX) const;
        
                double bSlopeAX(double sX) const;
        
                double bSlopeXX(double sX1, double sX2) const;
        
                double mMinXB() const;
        
                double mMinAX() const;
        
                double mMinAXB() const;
        
                double cRes() const;
        
                double mResXB() const;
        
                double mResAX() const;
        
                double sProton() const;
        
                double bMinSlopeXB() const;
        
                double bMinSlopeAX() const;
        
                double bMinSlopeXX() const;
        
        
                // Wrappers for original constructors: 
            public:
                SigmaTotal();
        
                // Special pointer-based constructor: 
                SigmaTotal(Abstract_SigmaTotal* in);
        
                // Copy constructor: 
                SigmaTotal(const SigmaTotal& in);
        
                // Assignment operator: 
                SigmaTotal& operator=(const SigmaTotal& in);
        
                // Destructor: 
                ~SigmaTotal();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_SigmaTotal* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SigmaTotal_decl_Pythia_8_212_h__ */
