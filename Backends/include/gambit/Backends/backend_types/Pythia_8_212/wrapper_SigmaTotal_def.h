#ifndef __wrapper_SigmaTotal_def_Pythia_8_212_h__
#define __wrapper_SigmaTotal_def_Pythia_8_212_h__

#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void SigmaTotal::init(Pythia8::Info* infoPtrIn, Pythia8::Settings& settings, Pythia8::ParticleData* particleDataPtrIn)
        {
            get_BEptr()->init__BOSS((*infoPtrIn).get_BEptr(), *settings.get_BEptr(), (*particleDataPtrIn).get_BEptr());
        }
        
        inline bool SigmaTotal::calc(int idA, int idB, double eCM)
        {
            return get_BEptr()->calc(idA, idB, eCM);
        }
        
        inline bool SigmaTotal::hasSigmaTot() const
        {
            return get_BEptr()->hasSigmaTot();
        }
        
        inline double SigmaTotal::sigmaTot() const
        {
            return get_BEptr()->sigmaTot();
        }
        
        inline double SigmaTotal::sigmaEl() const
        {
            return get_BEptr()->sigmaEl();
        }
        
        inline double SigmaTotal::sigmaXB() const
        {
            return get_BEptr()->sigmaXB();
        }
        
        inline double SigmaTotal::sigmaAX() const
        {
            return get_BEptr()->sigmaAX();
        }
        
        inline double SigmaTotal::sigmaXX() const
        {
            return get_BEptr()->sigmaXX();
        }
        
        inline double SigmaTotal::sigmaAXB() const
        {
            return get_BEptr()->sigmaAXB();
        }
        
        inline double SigmaTotal::sigmaND() const
        {
            return get_BEptr()->sigmaND();
        }
        
        inline bool SigmaTotal::calcMBRxsecs(int idA, int idB, double eCM)
        {
            return get_BEptr()->calcMBRxsecs(idA, idB, eCM);
        }
        
        inline double SigmaTotal::ddpMax() const
        {
            return get_BEptr()->ddpMax();
        }
        
        inline double SigmaTotal::sdpMax() const
        {
            return get_BEptr()->sdpMax();
        }
        
        inline double SigmaTotal::dpepMax() const
        {
            return get_BEptr()->dpepMax();
        }
        
        inline double SigmaTotal::bSlopeEl() const
        {
            return get_BEptr()->bSlopeEl();
        }
        
        inline double SigmaTotal::bSlopeXB(double sX) const
        {
            return get_BEptr()->bSlopeXB(sX);
        }
        
        inline double SigmaTotal::bSlopeAX(double sX) const
        {
            return get_BEptr()->bSlopeAX(sX);
        }
        
        inline double SigmaTotal::bSlopeXX(double sX1, double sX2) const
        {
            return get_BEptr()->bSlopeXX(sX1, sX2);
        }
        
        inline double SigmaTotal::mMinXB() const
        {
            return get_BEptr()->mMinXB();
        }
        
        inline double SigmaTotal::mMinAX() const
        {
            return get_BEptr()->mMinAX();
        }
        
        inline double SigmaTotal::mMinAXB() const
        {
            return get_BEptr()->mMinAXB();
        }
        
        inline double SigmaTotal::cRes() const
        {
            return get_BEptr()->cRes();
        }
        
        inline double SigmaTotal::mResXB() const
        {
            return get_BEptr()->mResXB();
        }
        
        inline double SigmaTotal::mResAX() const
        {
            return get_BEptr()->mResAX();
        }
        
        inline double SigmaTotal::sProton() const
        {
            return get_BEptr()->sProton();
        }
        
        inline double SigmaTotal::bMinSlopeXB() const
        {
            return get_BEptr()->bMinSlopeXB();
        }
        
        inline double SigmaTotal::bMinSlopeAX() const
        {
            return get_BEptr()->bMinSlopeAX();
        }
        
        inline double SigmaTotal::bMinSlopeXX() const
        {
            return get_BEptr()->bMinSlopeXX();
        }
        
        
        // Wrappers for original constructors: 
        inline SigmaTotal::SigmaTotal() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline SigmaTotal::SigmaTotal(Abstract_SigmaTotal* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline SigmaTotal::SigmaTotal(const SigmaTotal& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline SigmaTotal& SigmaTotal::operator=(const SigmaTotal& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline SigmaTotal::~SigmaTotal()
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
        inline Abstract_SigmaTotal* Pythia8::SigmaTotal::get_BEptr() const
        {
            return dynamic_cast<Abstract_SigmaTotal*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SigmaTotal_def_Pythia_8_212_h__ */
