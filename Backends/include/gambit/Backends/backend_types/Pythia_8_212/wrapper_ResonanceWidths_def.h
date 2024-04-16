#ifndef __wrapper_ResonanceWidths_def_Pythia_8_212_h__
#define __wrapper_ResonanceWidths_def_Pythia_8_212_h__

#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_ParticleDataEntry_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void ResonanceWidths::initBasic(int idResIn, bool isGenericIn)
        {
            get_BEptr()->initBasic(idResIn, isGenericIn);
        }
        
        inline void ResonanceWidths::initBasic(int idResIn)
        {
            get_BEptr()->initBasic__BOSS(idResIn);
        }
        
        inline bool ResonanceWidths::init(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Couplings* couplingsPtrIn)
        {
            return get_BEptr()->init__BOSS((*infoPtrIn).get_BEptr(), (*settingsPtrIn).get_BEptr(), (*particleDataPtrIn).get_BEptr(), (*couplingsPtrIn).get_BEptr());
        }
        
        inline int ResonanceWidths::id() const
        {
            return get_BEptr()->id();
        }
        
        inline double ResonanceWidths::width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly, bool setBR, int idOutFlav1, int idOutFlav2)
        {
            return get_BEptr()->width(idSgn, mHatIn, idInFlavIn, openOnly, setBR, idOutFlav1, idOutFlav2);
        }
        
        inline double ResonanceWidths::width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly, bool setBR, int idOutFlav1)
        {
            return get_BEptr()->width__BOSS(idSgn, mHatIn, idInFlavIn, openOnly, setBR, idOutFlav1);
        }
        
        inline double ResonanceWidths::width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly, bool setBR)
        {
            return get_BEptr()->width__BOSS(idSgn, mHatIn, idInFlavIn, openOnly, setBR);
        }
        
        inline double ResonanceWidths::width(int idSgn, double mHatIn, int idInFlavIn, bool openOnly)
        {
            return get_BEptr()->width__BOSS(idSgn, mHatIn, idInFlavIn, openOnly);
        }
        
        inline double ResonanceWidths::width(int idSgn, double mHatIn, int idInFlavIn)
        {
            return get_BEptr()->width__BOSS(idSgn, mHatIn, idInFlavIn);
        }
        
        inline double ResonanceWidths::width(int idSgn, double mHatIn)
        {
            return get_BEptr()->width__BOSS(idSgn, mHatIn);
        }
        
        inline double ResonanceWidths::widthOpen(int idSgn, double mHatIn, int idIn)
        {
            return get_BEptr()->widthOpen(idSgn, mHatIn, idIn);
        }
        
        inline double ResonanceWidths::widthOpen(int idSgn, double mHatIn)
        {
            return get_BEptr()->widthOpen__BOSS(idSgn, mHatIn);
        }
        
        inline double ResonanceWidths::widthStore(int idSgn, double mHatIn, int idIn)
        {
            return get_BEptr()->widthStore(idSgn, mHatIn, idIn);
        }
        
        inline double ResonanceWidths::widthStore(int idSgn, double mHatIn)
        {
            return get_BEptr()->widthStore__BOSS(idSgn, mHatIn);
        }
        
        inline double ResonanceWidths::openFrac(int idSgn)
        {
            return get_BEptr()->openFrac(idSgn);
        }
        
        inline double ResonanceWidths::widthRescaleFactor()
        {
            return get_BEptr()->widthRescaleFactor();
        }
        
        inline double ResonanceWidths::widthChan(double mHatIn, int idOutFlav1, int idOutFlav2)
        {
            return get_BEptr()->widthChan(mHatIn, idOutFlav1, idOutFlav2);
        }
        
        
        // Wrappers for original constructors: 
        inline ResonanceWidths::ResonanceWidths(const Pythia8::ResonanceWidths& arg_1) :
            WrapperBase(__factory0(arg_1))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline ResonanceWidths::ResonanceWidths(Abstract_ResonanceWidths* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline ResonanceWidths& ResonanceWidths::operator=(const ResonanceWidths& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline ResonanceWidths::~ResonanceWidths()
        {
            if (get_BEptr() != 0)
            {
                get_BEptr()->set_delete_wrapper(false);
                if (can_delete_BEptr())
                {
                    delete BEptr;
                    BEptr = 0;
                }
            }
            set_delete_BEptr(false);
        }
        
        // Returns correctly casted pointer to Abstract class: 
        inline Abstract_ResonanceWidths* Pythia8::ResonanceWidths::get_BEptr() const
        {
            return dynamic_cast<Abstract_ResonanceWidths*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ResonanceWidths_def_Pythia_8_212_h__ */
