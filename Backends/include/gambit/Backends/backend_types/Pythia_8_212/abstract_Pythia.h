#ifndef __abstract_Pythia_Pythia_8_212_h__
#define __abstract_Pythia_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <ostream>
#include <sstream>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_UserHooks_decl.h"
#include "wrapper_SigmaProcess_decl.h"
#include "wrapper_ResonanceWidths_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_SLHAinterface_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_PartonLevel_decl.h"
#include "wrapper_SigmaTotal_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Pythia : public virtual AbstractBase
        {
            public:
    
                virtual bool readString(::std::basic_string<char>, bool) =0;
    
                virtual bool readString__BOSS(::std::basic_string<char>) =0;
    
                virtual bool readFile(::std::basic_string<char>, bool, int) =0;
    
                virtual bool readFile__BOSS(::std::basic_string<char>, bool) =0;
    
                virtual bool readFile__BOSS(::std::basic_string<char>) =0;
    
                virtual bool readFile(::std::basic_string<char>, int) =0;
    
                virtual bool readFile(::std::basic_istream<char>&, bool, int) =0;
    
                virtual bool readFile__BOSS(::std::basic_istream<char>&, bool) =0;
    
                virtual bool readFile__BOSS(::std::basic_istream<char>&) =0;
    
                virtual bool readFile__BOSS() =0;
    
                virtual bool readFile(::std::basic_istream<char>&, int) =0;
    
                virtual bool setUserHooksPtr__BOSS(Pythia8::Abstract_UserHooks*) =0;
    
                virtual bool setResonancePtr__BOSS(Pythia8::Abstract_ResonanceWidths*) =0;
    
                virtual bool init(::std::basic_ostream<char>&) =0;
    
                virtual bool init__BOSS() =0;
    
                virtual bool next() =0;
    
                virtual int forceTimeShower(int, int, double, int) =0;
    
                virtual int forceTimeShower__BOSS(int, int, double) =0;
    
                virtual bool forceHadronLevel(bool) =0;
    
                virtual bool forceHadronLevel__BOSS() =0;
    
                virtual bool moreDecays() =0;
    
                virtual bool forceRHadronDecays() =0;
    
                virtual void LHAeventList(::std::basic_ostream<char>&) =0;
    
                virtual void LHAeventList__BOSS() =0;
    
                virtual bool LHAeventSkip(int) =0;
    
                virtual void stat() =0;
    
                virtual bool flag(::std::basic_string<char>) =0;
    
                virtual int mode(::std::basic_string<char>) =0;
    
                virtual double parm(::std::basic_string<char>) =0;
    
                virtual ::std::basic_string<char> word(::std::basic_string<char>) =0;
    
                virtual Pythia8::Abstract_Event& process_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Event& event_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Info& info_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Settings& settings_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_ParticleData& particleData_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Rndm& rndm_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Couplings& couplings_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_SLHAinterface& slhaInterface_ref__BOSS() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Pythia*) =0;
    
            private:
                Pythia* wptr;
                bool delete_wrapper;
            public:
                Pythia* get_wptr() { return wptr; }
                void set_wptr(Pythia* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Pythia()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Pythia(const Abstract_Pythia&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Pythia& operator=(const Abstract_Pythia&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Pythia* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Pythia& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Pythia() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Pythia_Pythia_8_212_h__ */
