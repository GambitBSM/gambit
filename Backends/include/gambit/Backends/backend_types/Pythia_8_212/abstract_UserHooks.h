#ifndef __abstract_UserHooks_Pythia_8_212_h__
#define __abstract_UserHooks_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_SigmaTotal_decl.h"
#include "wrapper_SigmaProcess_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Particle_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_UserHooks : public virtual AbstractBase
        {
            public:
    
                virtual bool initAfterBeams() =0;
    
                virtual bool canModifySigma() =0;
    
                virtual bool canBiasSelection() =0;
    
                virtual double biasedSelectionWeight() =0;
    
                virtual bool canVetoProcessLevel() =0;
    
                virtual bool doVetoProcessLevel__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual bool canVetoResonanceDecays() =0;
    
                virtual bool doVetoResonanceDecays__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual bool canVetoPT() =0;
    
                virtual double scaleVetoPT() =0;
    
                virtual bool doVetoPT__BOSS(int, const Pythia8::Abstract_Event&) =0;
    
                virtual bool canVetoStep() =0;
    
                virtual int numberVetoStep() =0;
    
                virtual bool doVetoStep__BOSS(int, int, int, const Pythia8::Abstract_Event&) =0;
    
                virtual bool canVetoMPIStep() =0;
    
                virtual int numberVetoMPIStep() =0;
    
                virtual bool doVetoMPIStep__BOSS(int, const Pythia8::Abstract_Event&) =0;
    
                virtual bool canVetoPartonLevelEarly() =0;
    
                virtual bool doVetoPartonLevelEarly__BOSS(const Pythia8::Abstract_Event&) =0;
    
                virtual bool retryPartonLevel() =0;
    
                virtual bool canVetoPartonLevel() =0;
    
                virtual bool doVetoPartonLevel__BOSS(const Pythia8::Abstract_Event&) =0;
    
                virtual bool canSetResonanceScale() =0;
    
                virtual double scaleResonance__BOSS(int, const Pythia8::Abstract_Event&) =0;
    
                virtual bool canVetoISREmission() =0;
    
                virtual bool doVetoISREmission__BOSS(int, const Pythia8::Abstract_Event&, int) =0;
    
                virtual bool canVetoFSREmission() =0;
    
                virtual bool doVetoFSREmission__BOSS(int, const Pythia8::Abstract_Event&, int, bool) =0;
    
                virtual bool doVetoFSREmission__BOSS(int, const Pythia8::Abstract_Event&, int) =0;
    
                virtual bool canVetoMPIEmission() =0;
    
                virtual bool doVetoMPIEmission__BOSS(int, const Pythia8::Abstract_Event&) =0;
    
                virtual bool canReconnectResonanceSystems() =0;
    
                virtual bool doReconnectResonanceSystems__BOSS(int, Pythia8::Abstract_Event&) =0;
    
                virtual bool canEnhanceEmission() =0;
    
                virtual double enhanceFactor(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >) =0;
    
                virtual double vetoProbability(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >) =0;
    
                virtual void setEnhancedEventWeight(double) =0;
    
                virtual double getEnhancedEventWeight() =0;
    
                virtual bool canEnhanceTrial() =0;
    
                virtual void setEnhancedTrial(double, double) =0;
    
                virtual double getEnhancedTrialPT() =0;
    
                virtual double getEnhancedTrialWeight() =0;
    
                virtual bool canChangeFragPar() =0;
    
                virtual bool doVetoFragmentation__BOSS(Pythia8::Abstract_Particle&) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_UserHooks*) =0;
    
            private:
                UserHooks* wptr;
                bool delete_wrapper;
            public:
                UserHooks* get_wptr() { return wptr; }
                void set_wptr(UserHooks* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_UserHooks()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_UserHooks(const Abstract_UserHooks&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_UserHooks& operator=(const Abstract_UserHooks&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                UserHooks* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                UserHooks& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_UserHooks() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_UserHooks_Pythia_8_212_h__ */
