#ifndef __abstract_ResonanceWidths_Pythia_8_212_h__
#define __abstract_ResonanceWidths_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
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
        class Abstract_ResonanceWidths : public virtual AbstractBase
        {
            public:
    
                virtual void initBasic(int, bool) =0;
    
                virtual void initBasic__BOSS(int) =0;
    
                virtual bool init__BOSS(Pythia8::Abstract_Info*, Pythia8::Abstract_Settings*, Pythia8::Abstract_ParticleData*, Pythia8::Abstract_Couplings*) =0;
    
                virtual int id() const =0;
    
                virtual double width(int, double, int, bool, bool, int, int) =0;
    
                virtual double width__BOSS(int, double, int, bool, bool, int) =0;
    
                virtual double width__BOSS(int, double, int, bool, bool) =0;
    
                virtual double width__BOSS(int, double, int, bool) =0;
    
                virtual double width__BOSS(int, double, int) =0;
    
                virtual double width__BOSS(int, double) =0;
    
                virtual double widthOpen(int, double, int) =0;
    
                virtual double widthOpen__BOSS(int, double) =0;
    
                virtual double widthStore(int, double, int) =0;
    
                virtual double widthStore__BOSS(int, double) =0;
    
                virtual double openFrac(int) =0;
    
                virtual double widthRescaleFactor() =0;
    
                virtual double widthChan(double, int, int) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_ResonanceWidths*) =0;
    
            private:
                ResonanceWidths* wptr;
                bool delete_wrapper;
            public:
                ResonanceWidths* get_wptr() { return wptr; }
                void set_wptr(ResonanceWidths* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_ResonanceWidths()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ResonanceWidths(const Abstract_ResonanceWidths&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_ResonanceWidths& operator=(const Abstract_ResonanceWidths&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                ResonanceWidths* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                ResonanceWidths& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_ResonanceWidths() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_ResonanceWidths_Pythia_8_212_h__ */
