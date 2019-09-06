#ifndef __abstract_ParticleDecays_Pythia_EM_8_212_h__
#define __abstract_ParticleDecays_Pythia_EM_8_212_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include <vector>
#include "wrapper_Event_decl.h"
#include "wrapper_ParticleDataEntry_decl.h"
#include "wrapper_Particle_decl.h"
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_ParticleDecays : public virtual AbstractBase
        {
            public:
    
                virtual bool decay__BOSS(int, Pythia8::Abstract_Event&) =0;
    
                virtual bool moreToDo() const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_ParticleDecays*) =0;
                virtual Abstract_ParticleDecays* pointer_copy__BOSS() =0;
    
            private:
                ParticleDecays* wptr;
                bool delete_wrapper;
            public:
                ParticleDecays* get_wptr() { return wptr; }
                void set_wptr(ParticleDecays* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_ParticleDecays()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ParticleDecays(const Abstract_ParticleDecays&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ParticleDecays& operator=(const Abstract_ParticleDecays&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                ParticleDecays* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                ParticleDecays& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_ParticleDecays() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ParticleDecays_Pythia_EM_8_212_h__ */
