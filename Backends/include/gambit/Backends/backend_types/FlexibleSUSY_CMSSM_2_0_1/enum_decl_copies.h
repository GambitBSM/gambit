#ifndef __enum_decl_copies_FlexibleSUSY_CMSSM_2_0_1_h__
#define __enum_decl_copies_FlexibleSUSY_CMSSM_2_0_1_h__


#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace softsusy
    {
        typedef enum {mUp=1, mCharm=2, mTop=3, mDown=4, mStrange=5, mBottom=6, mElectron=7, mMuon=8, mTau=9} mass;
    }
    namespace softsusy
    {
        typedef enum {ALPHA=1, ALPHAS=2} leGauge;
    }
    
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __enum_decl_copies_FlexibleSUSY_CMSSM_2_0_1_h__ */
