#ifndef __abstract_PartonLevel_Pythia_EM_8_212_h__
#define __abstract_PartonLevel_Pythia_EM_8_212_h__

#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_SigmaTotal_decl.h"
#include "wrapper_Event_decl.h"
#include <vector>
#include "wrapper_ResonanceDecays_decl.h"
#include <cstddef>
#include <iostream>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_PartonLevel : public virtual AbstractBase
        {
            public:
    
                virtual bool next__BOSS(Pythia8::Abstract_Event&, Pythia8::Abstract_Event&) =0;
    
                virtual void setupShowerSys__BOSS(Pythia8::Abstract_Event&, Pythia8::Abstract_Event&) =0;
    
                virtual bool resonanceShowers__BOSS(Pythia8::Abstract_Event&, Pythia8::Abstract_Event&, bool) =0;
    
                virtual bool wzDecayShowers__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual bool hasVetoed() const =0;
    
                virtual bool hasVetoedDiff() const =0;
    
                virtual void accumulate() =0;
    
                virtual void statistics(bool) =0;
    
                virtual void statistics__BOSS() =0;
    
                virtual void resetStatistics() =0;
    
                virtual void resetTrial() =0;
    
                virtual double pTLastInShower() =0;
    
                virtual int typeLastInShower() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_PartonLevel*) =0;
                virtual Abstract_PartonLevel* pointer_copy__BOSS() =0;
    
            private:
                PartonLevel* wptr;
                bool delete_wrapper;
            public:
                PartonLevel* get_wptr() { return wptr; }
                void set_wptr(PartonLevel* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_PartonLevel()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_PartonLevel(const Abstract_PartonLevel&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_PartonLevel& operator=(const Abstract_PartonLevel&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                PartonLevel* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                PartonLevel& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_PartonLevel() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_PartonLevel_Pythia_EM_8_212_h__ */
