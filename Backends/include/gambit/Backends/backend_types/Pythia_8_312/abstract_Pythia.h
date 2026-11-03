#ifndef __abstract_Pythia_Pythia_8_312_h__
#define __abstract_Pythia_Pythia_8_312_h__

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
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_CoupSUSY_decl.h"
#include "wrapper_SLHAinterface_decl.h"
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
    
                virtual bool checkVersion() =0;
    
                virtual bool readString(std::string, bool, int) =0;
    
                virtual bool readString__BOSS(std::string, bool) =0;
    
                virtual bool readString__BOSS(std::string) =0;
    
                virtual bool readFile(std::string, bool, int) =0;
    
                virtual bool readFile__BOSS(std::string, bool) =0;
    
                virtual bool readFile__BOSS(std::string) =0;
    
                virtual bool readFile(std::string, int) =0;
    
                virtual bool readFile(std::istream&, bool, int) =0;
    
                virtual bool readFile__BOSS(std::istream&, bool) =0;
    
                virtual bool readFile__BOSS(std::istream&) =0;
    
                virtual bool readFile__BOSS() =0;
    
                virtual bool readFile(std::istream&, int) =0;
    
                virtual bool init(std::ostream&) =0;
    
                virtual bool init__BOSS() =0;
    
                virtual bool next() =0;
    
                virtual bool next(int) =0;
    
                virtual bool setBeamIDs(int, int) =0;
    
                virtual bool setBeamIDs__BOSS(int) =0;
    
                virtual bool setKinematics(double) =0;
    
                virtual bool setKinematics(double, double) =0;
    
                virtual bool setKinematics(double, double, double, double, double, double) =0;
    
                virtual bool setKinematics__BOSS(Pythia8::Abstract_Vec4&, Pythia8::Abstract_Vec4&) =0;
    
                virtual int forceTimeShower(int, int, double, int) =0;
    
                virtual int forceTimeShower__BOSS(int, int, double) =0;
    
                virtual bool forceHadronLevel(bool) =0;
    
                virtual bool forceHadronLevel__BOSS() =0;
    
                virtual bool moreDecays() =0;
    
                virtual bool moreDecays(int) =0;
    
                virtual bool forceRHadronDecays() =0;
    
                virtual bool doLowEnergyProcess(int, int, int) =0;
    
                virtual double getSigmaTotal() =0;
    
                virtual double getSigmaTotal(double, int) =0;
    
                virtual double getSigmaTotal__BOSS(double) =0;
    
                virtual double getSigmaTotal(int, int, double, int) =0;
    
                virtual double getSigmaTotal__BOSS(int, int, double) =0;
    
                virtual double getSigmaTotal(int, int, double, double, double, int) =0;
    
                virtual double getSigmaTotal__BOSS(int, int, double, double, double) =0;
    
                virtual double getSigmaPartial(int) =0;
    
                virtual double getSigmaPartial(double, int, int) =0;
    
                virtual double getSigmaPartial__BOSS(double, int) =0;
    
                virtual double getSigmaPartial(int, int, double, int, int) =0;
    
                virtual double getSigmaPartial__BOSS(int, int, double, int) =0;
    
                virtual double getSigmaPartial(int, int, double, double, double, int, int) =0;
    
                virtual double getSigmaPartial__BOSS(int, int, double, double, double, int) =0;
    
                virtual void LHAeventList() =0;
    
                virtual bool LHAeventSkip(int) =0;
    
                virtual void stat() =0;
    
                virtual bool flag(std::string) =0;
    
                virtual int mode(std::string) =0;
    
                virtual double parm(std::string) =0;
    
                virtual ::std::string word(std::string) =0;
    
                virtual double getSigmaMaxSum() =0;
    
                virtual Pythia8::Abstract_Event& process_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Event& event_ref__BOSS() =0;
    
                virtual const Pythia8::Abstract_Info& info_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Logger& logger_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Settings& settings_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_ParticleData& particleData_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_Rndm& rndm_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_CoupSM& coupSM_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_CoupSUSY& coupSUSY_ref__BOSS() =0;
    
                virtual Pythia8::Abstract_SLHAinterface& slhaInterface_ref__BOSS() =0;
    
                virtual const Pythia8::Abstract_BeamParticle& beamA_ref__BOSS() =0;
    
                virtual const Pythia8::Abstract_BeamParticle& beamB_ref__BOSS() =0;
    
    
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


#endif /* __abstract_Pythia_Pythia_8_312_h__ */
