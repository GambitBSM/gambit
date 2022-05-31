#ifndef __abstract_GAMBIT_hepmc_writer_Pythia_8_212_h__
#define __abstract_GAMBIT_hepmc_writer_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Pythia_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_GAMBIT_hepmc_writer : public virtual AbstractBase
        {
            public:
    
                virtual void init(::std::basic_string<char>, bool, bool) =0;
    
                virtual void write_event_HepMC3__BOSS(Pythia8::Abstract_Pythia*) =0;
    
                virtual void write_event_HepMC2__BOSS(Pythia8::Abstract_Pythia*) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_GAMBIT_hepmc_writer*) =0;
                virtual Abstract_GAMBIT_hepmc_writer* pointer_copy__BOSS() =0;
    
            private:
                GAMBIT_hepmc_writer* wptr;
                bool delete_wrapper;
            public:
                GAMBIT_hepmc_writer* get_wptr() { return wptr; }
                void set_wptr(GAMBIT_hepmc_writer* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_GAMBIT_hepmc_writer()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_GAMBIT_hepmc_writer(const Abstract_GAMBIT_hepmc_writer&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_GAMBIT_hepmc_writer& operator=(const Abstract_GAMBIT_hepmc_writer&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                GAMBIT_hepmc_writer* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                GAMBIT_hepmc_writer& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_GAMBIT_hepmc_writer() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_GAMBIT_hepmc_writer_Pythia_8_212_h__ */
