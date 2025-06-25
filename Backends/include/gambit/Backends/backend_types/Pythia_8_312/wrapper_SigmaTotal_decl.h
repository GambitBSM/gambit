#ifndef __wrapper_SigmaTotal_decl_Pythia_8_312_h__
#define __wrapper_SigmaTotal_decl_Pythia_8_312_h__

#include <cstddef>
#include <utility>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SigmaTotal.h"

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
                void init();
        
                bool calc(int idA, int idB, double eCM);
        
                bool hasSigmaTot();
        
                double sigmaTot();
        
                double rho();
        
                double sigmaEl();
        
                bool bElIsExp();
        
                double bSlopeEl();
        
                bool hasCoulomb();
        
                bool calcTotEl(int idAin, int idBin, double sIn, double mAin, double mBin);
        
                double dsigmaEl(double t, bool useCoulomb, bool onlyPomerons);
        
                double dsigmaEl(double t, bool useCoulomb);
        
                double dsigmaEl(double t);
        
                double sigmaXB() const;
        
                double sigmaAX() const;
        
                double sigmaXX() const;
        
                double sigmaAXB() const;
        
                double sigmaND() const;
        
                double dsigmaSD(double xi, double t, bool isXB, int step);
        
                double dsigmaSD(double xi, double t, bool isXB);
        
                double dsigmaSD(double xi, double t);
        
                bool splitDiff();
        
                double dsigmaDD(double xi1, double xi2, double t, int step);
        
                double dsigmaDD(double xi1, double xi2, double t);
        
                double dsigmaCD(double xi1, double xi2, double t1, double t2, int step);
        
                double dsigmaCD(double xi1, double xi2, double t1, double t2);
        
                double mMinCD();
        
                void chooseVMDstates(int idA, int idB, double eCM, int processCode);
        
                ::std::pair<double, double> tRange(double sIn, double s1In, double s2In, double s3In, double s4In);
        
                bool tInRange(double tIn, double sIn, double s1In, double s2In, double s3In, double s4In);
        
        
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

#endif /* __wrapper_SigmaTotal_decl_Pythia_8_312_h__ */
