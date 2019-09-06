#ifndef __abstract_ResonanceDecays_Pythia_EM_8_212_h__
#define __abstract_ResonanceDecays_Pythia_EM_8_212_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Event_decl.h"
#include <vector>
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_ResonanceDecays : public virtual AbstractBase
        {
            public:
    
                virtual void init__BOSS(Pythia8::Abstract_Info*, Pythia8::Abstract_ParticleData*, Pythia8::Abstract_Rndm*) =0;
    
                virtual bool next__BOSS(Pythia8::Abstract_Event&, int) =0;
    
                virtual bool next__BOSS(Pythia8::Abstract_Event&) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_ResonanceDecays*) =0;
                virtual Abstract_ResonanceDecays* pointer_copy__BOSS() =0;
    
            private:
                ResonanceDecays* wptr;
                bool delete_wrapper;
            public:
                ResonanceDecays* get_wptr() { return wptr; }
                void set_wptr(ResonanceDecays* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_ResonanceDecays()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ResonanceDecays(const Abstract_ResonanceDecays&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ResonanceDecays& operator=(const Abstract_ResonanceDecays&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                ResonanceDecays* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                ResonanceDecays& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_ResonanceDecays() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ResonanceDecays_Pythia_EM_8_212_h__ */
