#ifndef __abstract_SLHAinterface_Pythia_8_212_h__
#define __abstract_SLHAinterface_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <sstream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_SusyLesHouches_decl.h"
#include "wrapper_CoupSUSY_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_SLHAinterface : public virtual AbstractBase
        {
            public:
    
                virtual void setPtr__BOSS(Pythia8::Abstract_Info*) =0;
    
                virtual void init__BOSS(Pythia8::Abstract_Settings&, Pythia8::Abstract_Rndm*, Pythia8::Abstract_Couplings*, Pythia8::Abstract_ParticleData*, bool&, ::std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >&) =0;
    
                virtual bool initSLHA__BOSS(Pythia8::Abstract_Settings&, Pythia8::Abstract_ParticleData*) =0;
    
                virtual void pythia2slha__BOSS(Pythia8::Abstract_ParticleData*) =0;
    
                virtual Pythia8::Abstract_SusyLesHouches& slha_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_CoupSUSY& coupSUSY_ref__BOSS() =0;
    
                virtual int& meMode_ref__BOSS() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_SLHAinterface*) =0;
                virtual Abstract_SLHAinterface* pointer_copy__BOSS() =0;
    
            private:
                SLHAinterface* wptr;
                bool delete_wrapper;
            public:
                SLHAinterface* get_wptr() { return wptr; }
                void set_wptr(SLHAinterface* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_SLHAinterface()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SLHAinterface(const Abstract_SLHAinterface&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SLHAinterface& operator=(const Abstract_SLHAinterface&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                SLHAinterface* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                SLHAinterface& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_SLHAinterface() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_SLHAinterface_Pythia_8_212_h__ */
