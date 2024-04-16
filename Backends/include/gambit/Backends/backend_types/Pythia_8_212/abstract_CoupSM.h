#ifndef __abstract_CoupSM_Pythia_8_212_h__
#define __abstract_CoupSM_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_AlphaStrong_decl.h"
#include "wrapper_AlphaEM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_CoupSM : public virtual AbstractBase
        {
            public:
    
                virtual void init__BOSS(Pythia8::Abstract_Settings&, Pythia8::Abstract_Rndm*) =0;
    
                virtual double alphaS(double) =0;
    
                virtual double alphaS1Ord(double) =0;
    
                virtual double alphaS2OrdCorr(double) =0;
    
                virtual double Lambda3() const =0;
    
                virtual double Lambda4() const =0;
    
                virtual double Lambda5() const =0;
    
                virtual double alphaEM(double) =0;
    
                virtual double sin2thetaW() =0;
    
                virtual double cos2thetaW() =0;
    
                virtual double sin2thetaWbar() =0;
    
                virtual double GF() =0;
    
                virtual double ef(int) =0;
    
                virtual double vf(int) =0;
    
                virtual double af(int) =0;
    
                virtual double t3f(int) =0;
    
                virtual double lf(int) =0;
    
                virtual double rf(int) =0;
    
                virtual double ef2(int) =0;
    
                virtual double vf2(int) =0;
    
                virtual double af2(int) =0;
    
                virtual double efvf(int) =0;
    
                virtual double vf2af2(int) =0;
    
                virtual double VCKMgen(int, int) =0;
    
                virtual double V2CKMgen(int, int) =0;
    
                virtual double VCKMid(int, int) =0;
    
                virtual double V2CKMid(int, int) =0;
    
                virtual double V2CKMsum(int) =0;
    
                virtual int V2CKMpick(int) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_CoupSM*) =0;
                virtual Abstract_CoupSM* pointer_copy__BOSS() =0;
    
            private:
                CoupSM* wptr;
                bool delete_wrapper;
            public:
                CoupSM* get_wptr() { return wptr; }
                void set_wptr(CoupSM* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_CoupSM()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CoupSM(const Abstract_CoupSM&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_CoupSM& operator=(const Abstract_CoupSM&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                CoupSM* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                CoupSM& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_CoupSM() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_CoupSM_Pythia_8_212_h__ */
