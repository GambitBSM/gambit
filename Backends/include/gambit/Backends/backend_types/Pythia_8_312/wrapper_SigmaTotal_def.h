#ifndef __wrapper_SigmaTotal_def_Pythia_8_312_h__
#define __wrapper_SigmaTotal_def_Pythia_8_312_h__

#include <utility>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void SigmaTotal::init()
        {
            get_BEptr()->init();
        }
        
        inline bool SigmaTotal::calc(int idA, int idB, double eCM)
        {
            return get_BEptr()->calc(idA, idB, eCM);
        }
        
        inline bool SigmaTotal::hasSigmaTot()
        {
            return get_BEptr()->hasSigmaTot();
        }
        
        inline double SigmaTotal::sigmaTot()
        {
            return get_BEptr()->sigmaTot();
        }
        
        inline double SigmaTotal::rho()
        {
            return get_BEptr()->rho();
        }
        
        inline double SigmaTotal::sigmaEl()
        {
            return get_BEptr()->sigmaEl();
        }
        
        inline bool SigmaTotal::bElIsExp()
        {
            return get_BEptr()->bElIsExp();
        }
        
        inline double SigmaTotal::bSlopeEl()
        {
            return get_BEptr()->bSlopeEl();
        }
        
        inline bool SigmaTotal::hasCoulomb()
        {
            return get_BEptr()->hasCoulomb();
        }
        
        inline bool SigmaTotal::calcTotEl(int idAin, int idBin, double sIn, double mAin, double mBin)
        {
            return get_BEptr()->calcTotEl(idAin, idBin, sIn, mAin, mBin);
        }
        
        inline double SigmaTotal::dsigmaEl(double t, bool useCoulomb, bool onlyPomerons)
        {
            return get_BEptr()->dsigmaEl(t, useCoulomb, onlyPomerons);
        }
        
        inline double SigmaTotal::dsigmaEl(double t, bool useCoulomb)
        {
            return get_BEptr()->dsigmaEl__BOSS(t, useCoulomb);
        }
        
        inline double SigmaTotal::dsigmaEl(double t)
        {
            return get_BEptr()->dsigmaEl__BOSS(t);
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
        
        inline double SigmaTotal::dsigmaSD(double xi, double t, bool isXB, int step)
        {
            return get_BEptr()->dsigmaSD(xi, t, isXB, step);
        }
        
        inline double SigmaTotal::dsigmaSD(double xi, double t, bool isXB)
        {
            return get_BEptr()->dsigmaSD__BOSS(xi, t, isXB);
        }
        
        inline double SigmaTotal::dsigmaSD(double xi, double t)
        {
            return get_BEptr()->dsigmaSD__BOSS(xi, t);
        }
        
        inline bool SigmaTotal::splitDiff()
        {
            return get_BEptr()->splitDiff();
        }
        
        inline double SigmaTotal::dsigmaDD(double xi1, double xi2, double t, int step)
        {
            return get_BEptr()->dsigmaDD(xi1, xi2, t, step);
        }
        
        inline double SigmaTotal::dsigmaDD(double xi1, double xi2, double t)
        {
            return get_BEptr()->dsigmaDD__BOSS(xi1, xi2, t);
        }
        
        inline double SigmaTotal::dsigmaCD(double xi1, double xi2, double t1, double t2, int step)
        {
            return get_BEptr()->dsigmaCD(xi1, xi2, t1, t2, step);
        }
        
        inline double SigmaTotal::dsigmaCD(double xi1, double xi2, double t1, double t2)
        {
            return get_BEptr()->dsigmaCD__BOSS(xi1, xi2, t1, t2);
        }
        
        inline double SigmaTotal::mMinCD()
        {
            return get_BEptr()->mMinCD();
        }
        
        inline void SigmaTotal::chooseVMDstates(int idA, int idB, double eCM, int processCode)
        {
            get_BEptr()->chooseVMDstates(idA, idB, eCM, processCode);
        }
        
        inline ::std::pair<double, double> SigmaTotal::tRange(double sIn, double s1In, double s2In, double s3In, double s4In)
        {
            return get_BEptr()->tRange(sIn, s1In, s2In, s3In, s4In);
        }
        
        inline bool SigmaTotal::tInRange(double tIn, double sIn, double s1In, double s2In, double s3In, double s4In)
        {
            return get_BEptr()->tInRange(tIn, sIn, s1In, s2In, s3In, s4In);
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

#endif /* __wrapper_SigmaTotal_def_Pythia_8_312_h__ */
