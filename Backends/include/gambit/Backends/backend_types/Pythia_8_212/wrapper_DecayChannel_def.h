#ifndef __wrapper_DecayChannel_def_Pythia_8_212_h__
#define __wrapper_DecayChannel_def_Pythia_8_212_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void DecayChannel::onMode(int onModeIn)
        {
            get_BEptr()->onMode(onModeIn);
        }
        
        inline void DecayChannel::bRatio(double bRatioIn, bool countAsChanged)
        {
            get_BEptr()->bRatio(bRatioIn, countAsChanged);
        }
        
        inline void DecayChannel::bRatio(double bRatioIn)
        {
            get_BEptr()->bRatio__BOSS(bRatioIn);
        }
        
        inline void DecayChannel::rescaleBR(double fac)
        {
            get_BEptr()->rescaleBR(fac);
        }
        
        inline void DecayChannel::meMode(int meModeIn)
        {
            get_BEptr()->meMode(meModeIn);
        }
        
        inline void DecayChannel::multiplicity(int multIn)
        {
            get_BEptr()->multiplicity(multIn);
        }
        
        inline void DecayChannel::product(int i, int prodIn)
        {
            get_BEptr()->product(i, prodIn);
        }
        
        inline void DecayChannel::setHasChanged(bool hasChangedIn)
        {
            get_BEptr()->setHasChanged(hasChangedIn);
        }
        
        inline int DecayChannel::onMode() const
        {
            return get_BEptr()->onMode();
        }
        
        inline double DecayChannel::bRatio() const
        {
            return get_BEptr()->bRatio();
        }
        
        inline int DecayChannel::meMode() const
        {
            return get_BEptr()->meMode();
        }
        
        inline int DecayChannel::multiplicity() const
        {
            return get_BEptr()->multiplicity();
        }
        
        inline int DecayChannel::product(int i) const
        {
            return get_BEptr()->product(i);
        }
        
        inline bool DecayChannel::hasChanged() const
        {
            return get_BEptr()->hasChanged();
        }
        
        inline bool DecayChannel::contains(int id1) const
        {
            return get_BEptr()->contains(id1);
        }
        
        inline bool DecayChannel::contains(int id1, int id2) const
        {
            return get_BEptr()->contains(id1, id2);
        }
        
        inline bool DecayChannel::contains(int id1, int id2, int id3) const
        {
            return get_BEptr()->contains(id1, id2, id3);
        }
        
        inline void DecayChannel::currentBR(double currentBRIn)
        {
            get_BEptr()->currentBR(currentBRIn);
        }
        
        inline double DecayChannel::currentBR() const
        {
            return get_BEptr()->currentBR();
        }
        
        inline void DecayChannel::onShellWidth(double onShellWidthIn)
        {
            get_BEptr()->onShellWidth(onShellWidthIn);
        }
        
        inline double DecayChannel::onShellWidth() const
        {
            return get_BEptr()->onShellWidth();
        }
        
        inline void DecayChannel::onShellWidthFactor(double factor)
        {
            get_BEptr()->onShellWidthFactor(factor);
        }
        
        inline void DecayChannel::openSec(int idSgn, double openSecIn)
        {
            get_BEptr()->openSec(idSgn, openSecIn);
        }
        
        inline double DecayChannel::openSec(int idSgn) const
        {
            return get_BEptr()->openSec(idSgn);
        }
        
        
        // Wrappers for original constructors: 
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6, int prod7) :
            WrapperBase(__factory0(onModeIn, bRatioIn, meModeIn, prod0, prod1, prod2, prod3, prod4, prod5, prod6, prod7))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6) :
            WrapperBase(__factory1(onModeIn, bRatioIn, meModeIn, prod0, prod1, prod2, prod3, prod4, prod5, prod6))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5) :
            WrapperBase(__factory2(onModeIn, bRatioIn, meModeIn, prod0, prod1, prod2, prod3, prod4, prod5))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3, int prod4) :
            WrapperBase(__factory3(onModeIn, bRatioIn, meModeIn, prod0, prod1, prod2, prod3, prod4))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2, int prod3) :
            WrapperBase(__factory4(onModeIn, bRatioIn, meModeIn, prod0, prod1, prod2, prod3))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1, int prod2) :
            WrapperBase(__factory5(onModeIn, bRatioIn, meModeIn, prod0, prod1, prod2))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0, int prod1) :
            WrapperBase(__factory6(onModeIn, bRatioIn, meModeIn, prod0, prod1))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn, int prod0) :
            WrapperBase(__factory7(onModeIn, bRatioIn, meModeIn, prod0))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn, int meModeIn) :
            WrapperBase(__factory8(onModeIn, bRatioIn, meModeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn, double bRatioIn) :
            WrapperBase(__factory9(onModeIn, bRatioIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel(int onModeIn) :
            WrapperBase(__factory10(onModeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline DecayChannel::DecayChannel() :
            WrapperBase(__factory11())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline DecayChannel::DecayChannel(Abstract_DecayChannel* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline DecayChannel::DecayChannel(const DecayChannel& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline DecayChannel& DecayChannel::operator=(const DecayChannel& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline DecayChannel::~DecayChannel()
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
        inline Abstract_DecayChannel* Pythia8::DecayChannel::get_BEptr() const
        {
            return dynamic_cast<Abstract_DecayChannel*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_DecayChannel_def_Pythia_8_212_h__ */
