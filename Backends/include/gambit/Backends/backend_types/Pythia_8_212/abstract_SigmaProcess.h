#ifndef __abstract_SigmaProcess_Pythia_8_212_h__
#define __abstract_SigmaProcess_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
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
#include "wrapper_SLHAinterface_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Particle_decl.h"
#include "wrapper_SusyLesHouches_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_SigmaProcess : public virtual AbstractBase
        {
            public:
    
                virtual void init__BOSS(Pythia8::Abstract_Info*, Pythia8::Abstract_Settings*, Pythia8::Abstract_ParticleData*, Pythia8::Abstract_Rndm*, Pythia8::Abstract_BeamParticle*, Pythia8::Abstract_BeamParticle*, Pythia8::Abstract_Couplings*, Pythia8::Abstract_SigmaTotal*, Pythia8::Abstract_SLHAinterface*) =0;
    
                virtual void init__BOSS(Pythia8::Abstract_Info*, Pythia8::Abstract_Settings*, Pythia8::Abstract_ParticleData*, Pythia8::Abstract_Rndm*, Pythia8::Abstract_BeamParticle*, Pythia8::Abstract_BeamParticle*, Pythia8::Abstract_Couplings*, Pythia8::Abstract_SigmaTotal*) =0;
    
                virtual void init__BOSS(Pythia8::Abstract_Info*, Pythia8::Abstract_Settings*, Pythia8::Abstract_ParticleData*, Pythia8::Abstract_Rndm*, Pythia8::Abstract_BeamParticle*, Pythia8::Abstract_BeamParticle*, Pythia8::Abstract_Couplings*) =0;
    
                virtual void initProc() =0;
    
                virtual bool initFlux() =0;
    
                virtual void set1Kin(double, double, double) =0;
    
                virtual void set2Kin(double, double, double, double, double, double, double, double) =0;
    
                virtual void set2KinMPI(double, double, double, double, double, double, double, bool, double, double) =0;
    
                virtual void set3Kin__BOSS(double, double, double, Pythia8::Abstract_Vec4&, Pythia8::Abstract_Vec4&, Pythia8::Abstract_Vec4&, double, double, double, double, double, double) =0;
    
                virtual void sigmaKin() =0;
    
                virtual double sigmaHat() =0;
    
                virtual double sigmaHatWrap(int, int) =0;
    
                virtual double sigmaHatWrap__BOSS(int) =0;
    
                virtual double sigmaHatWrap__BOSS() =0;
    
                virtual double sigmaPDF() =0;
    
                virtual void pickInState(int, int) =0;
    
                virtual void pickInState__BOSS(int) =0;
    
                virtual void pickInState__BOSS() =0;
    
                virtual void setIdColAcol() =0;
    
                virtual bool final2KinMPI__BOSS(int, int, Pythia8::Abstract_Vec4&, Pythia8::Abstract_Vec4&, double, double) =0;
    
                virtual bool final2KinMPI__BOSS(int, int, Pythia8::Abstract_Vec4&, Pythia8::Abstract_Vec4&, double) =0;
    
                virtual bool final2KinMPI__BOSS(int, int, Pythia8::Abstract_Vec4&, Pythia8::Abstract_Vec4&) =0;
    
                virtual bool final2KinMPI__BOSS(int, int, Pythia8::Abstract_Vec4&) =0;
    
                virtual bool final2KinMPI__BOSS(int, int) =0;
    
                virtual bool final2KinMPI__BOSS(int) =0;
    
                virtual bool final2KinMPI__BOSS() =0;
    
                virtual double weightDecayFlav__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual double weightDecay__BOSS(Pythia8::Abstract_Event&, int, int) =0;
    
                virtual void setScale() =0;
    
                virtual ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > name() const =0;
    
                virtual int code() const =0;
    
                virtual int nFinal() const =0;
    
                virtual ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > inFlux() const =0;
    
                virtual bool convert2mb() const =0;
    
                virtual bool convertM2() const =0;
    
                virtual bool isLHA() const =0;
    
                virtual bool isNonDiff() const =0;
    
                virtual bool isResolved() const =0;
    
                virtual bool isDiffA() const =0;
    
                virtual bool isDiffB() const =0;
    
                virtual bool isDiffC() const =0;
    
                virtual bool isSUSY() const =0;
    
                virtual bool allowNegativeSigma() const =0;
    
                virtual int id3Mass() const =0;
    
                virtual int id4Mass() const =0;
    
                virtual int id5Mass() const =0;
    
                virtual int resonanceA() const =0;
    
                virtual int resonanceB() const =0;
    
                virtual bool isSChannel() const =0;
    
                virtual int idSChannel() const =0;
    
                virtual bool isQCD3body() const =0;
    
                virtual int idTchan1() const =0;
    
                virtual int idTchan2() const =0;
    
                virtual double tChanFracPow1() const =0;
    
                virtual double tChanFracPow2() const =0;
    
                virtual bool useMirrorWeight() const =0;
    
                virtual int gmZmode() const =0;
    
                virtual bool swappedTU() const =0;
    
                virtual int id(int) const =0;
    
                virtual int col(int) const =0;
    
                virtual int acol(int) const =0;
    
                virtual double m(int) const =0;
    
                virtual Pythia8::Abstract_Particle* getParton__BOSS(int) const =0;
    
                virtual double Q2Ren() const =0;
    
                virtual double alphaEMRen() const =0;
    
                virtual double alphaSRen() const =0;
    
                virtual double Q2Fac() const =0;
    
                virtual double pdf1() const =0;
    
                virtual double pdf2() const =0;
    
                virtual double thetaMPI() const =0;
    
                virtual double phiMPI() const =0;
    
                virtual double sHBetaMPI() const =0;
    
                virtual double pT2MPI() const =0;
    
                virtual double pTMPIFin() const =0;
    
                virtual void saveKin() =0;
    
                virtual void loadKin() =0;
    
                virtual void swapKin() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_SigmaProcess*) =0;
    
            private:
                SigmaProcess* wptr;
                bool delete_wrapper;
            public:
                SigmaProcess* get_wptr() { return wptr; }
                void set_wptr(SigmaProcess* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_SigmaProcess()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SigmaProcess(const Abstract_SigmaProcess&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SigmaProcess& operator=(const Abstract_SigmaProcess&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                SigmaProcess* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                SigmaProcess& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_SigmaProcess() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_SigmaProcess_Pythia_8_212_h__ */
