#ifndef __wrapper_AlphaStrong_def_Pythia_8_212_h__
#define __wrapper_AlphaStrong_def_Pythia_8_212_h__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void AlphaStrong::init(double valueIn, int orderIn, int nfmaxIn, bool useCMWIn)
        {
            get_BEptr()->init(valueIn, orderIn, nfmaxIn, useCMWIn);
        }
        
        inline void AlphaStrong::init(double valueIn, int orderIn, int nfmaxIn)
        {
            get_BEptr()->init__BOSS(valueIn, orderIn, nfmaxIn);
        }
        
        inline void AlphaStrong::init(double valueIn, int orderIn)
        {
            get_BEptr()->init__BOSS(valueIn, orderIn);
        }
        
        inline void AlphaStrong::init(double valueIn)
        {
            get_BEptr()->init__BOSS(valueIn);
        }
        
        inline void AlphaStrong::init()
        {
            get_BEptr()->init__BOSS();
        }
        
        inline void AlphaStrong::setThresholds(double mcIn, double mbIn, double mtIn)
        {
            get_BEptr()->setThresholds(mcIn, mbIn, mtIn);
        }
        
        inline double AlphaStrong::alphaS(double scale2)
        {
            return get_BEptr()->alphaS(scale2);
        }
        
        inline double AlphaStrong::alphaS1Ord(double scale2)
        {
            return get_BEptr()->alphaS1Ord(scale2);
        }
        
        inline double AlphaStrong::alphaS2OrdCorr(double scale2)
        {
            return get_BEptr()->alphaS2OrdCorr(scale2);
        }
        
        inline double AlphaStrong::Lambda3() const
        {
            return get_BEptr()->Lambda3();
        }
        
        inline double AlphaStrong::Lambda4() const
        {
            return get_BEptr()->Lambda4();
        }
        
        inline double AlphaStrong::Lambda5() const
        {
            return get_BEptr()->Lambda5();
        }
        
        inline double AlphaStrong::Lambda6() const
        {
            return get_BEptr()->Lambda6();
        }
        
        inline double AlphaStrong::muThres(int idQ)
        {
            return get_BEptr()->muThres(idQ);
        }
        
        inline double AlphaStrong::muThres2(int idQ)
        {
            return get_BEptr()->muThres2(idQ);
        }
        
        inline double AlphaStrong::facCMW(int nFin)
        {
            return get_BEptr()->facCMW(nFin);
        }
        
        
        // Wrappers for original constructors: 
        inline AlphaStrong::AlphaStrong() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline AlphaStrong::AlphaStrong(Abstract_AlphaStrong* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline AlphaStrong::AlphaStrong(const AlphaStrong& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline AlphaStrong& AlphaStrong::operator=(const AlphaStrong& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline AlphaStrong::~AlphaStrong()
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
        inline Abstract_AlphaStrong* Pythia8::AlphaStrong::get_BEptr() const
        {
            return dynamic_cast<Abstract_AlphaStrong*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_AlphaStrong_def_Pythia_8_212_h__ */
