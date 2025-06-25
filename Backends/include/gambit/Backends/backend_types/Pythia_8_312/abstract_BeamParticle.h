#ifndef __abstract_BeamParticle_Pythia_8_312_h__
#define __abstract_BeamParticle_Pythia_8_312_h__

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_BeamParticle : public virtual AbstractBase
        {
            public:
    
                virtual void initID(int) =0;
    
                virtual void newValenceContent() =0;
    
                virtual void setValenceContent(int, int, int) =0;
    
                virtual void setValenceContent__BOSS(int, int) =0;
    
                virtual void setValenceContent__BOSS(int) =0;
    
                virtual void setBeamID(int, int) =0;
    
                virtual void setBeamID__BOSS(int) =0;
    
                virtual void newPzE(double, double) =0;
    
                virtual void newM(double) =0;
    
                virtual int id() const =0;
    
                virtual int idVMD() const =0;
    
                virtual Pythia8::Abstract_Vec4* p__BOSS() const =0;
    
                virtual double px() const =0;
    
                virtual double py() const =0;
    
                virtual double pz() const =0;
    
                virtual double e() const =0;
    
                virtual double m() const =0;
    
                virtual double mVMD() const =0;
    
                virtual double scaleVMD() const =0;
    
                virtual bool isLepton() const =0;
    
                virtual bool isUnresolved() const =0;
    
                virtual bool isHadron() const =0;
    
                virtual bool isMeson() const =0;
    
                virtual bool isBaryon() const =0;
    
                virtual bool isGamma() const =0;
    
                virtual bool hasResGamma() const =0;
    
                virtual bool hasVMDstate() const =0;
    
                virtual double xMax(int) =0;
    
                virtual double xMax__BOSS() =0;
    
                virtual double xfHard(int, double, double) =0;
    
                virtual double xfMax(int, double, double) =0;
    
                virtual double xfFlux(int, double, double) =0;
    
                virtual double xfApprox(int, double, double) =0;
    
                virtual double xfGamma(int, double, double) =0;
    
                virtual double xfSame(int, double, double) =0;
    
                virtual double xf(int, double, double) =0;
    
                virtual double xfVal(int, double, double) =0;
    
                virtual double xfSea(int, double, double) =0;
    
                virtual double xfMPI(int, double, double) =0;
    
                virtual double xfISR(int, int, double, double) =0;
    
                virtual bool insideBounds(double, double) =0;
    
                virtual double alphaS(double) =0;
    
                virtual double mQuarkPDF(int) =0;
    
                virtual int nMembers() =0;
    
                virtual void calcPDFEnvelope(int, double, double, int) =0;
    
                virtual void calcPDFEnvelope(std::pair<int, int>, std::pair<double, double>, double, int) =0;
    
                virtual int pickValSeaComp() =0;
    
                virtual void initBeamKind() =0;
    
                virtual int size() const =0;
    
                virtual int sizeInit() const =0;
    
                virtual void clear() =0;
    
                virtual void resetGamma() =0;
    
                virtual void resetGammaInLepton() =0;
    
                virtual int append(int, int, double, int) =0;
    
                virtual int append__BOSS(int, int, double) =0;
    
                virtual void popBack() =0;
    
                virtual void list() const =0;
    
                virtual int nValenceKinds() const =0;
    
                virtual int nValence(int) const =0;
    
                virtual bool isUnresolvedLepton() =0;
    
                virtual bool remnantFlavours__BOSS(Pythia8::Abstract_Event&, bool) =0;
    
                virtual bool remnantFlavours__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual bool remnantColours__BOSS(Pythia8::Abstract_Event&, std::vector<int>&, std::vector<int>&) =0;
    
                virtual double xRemnant(int) =0;
    
                virtual bool hasJunction() const =0;
    
                virtual int junctionCol(int) const =0;
    
                virtual void junctionCol(int, int) =0;
    
                virtual bool pickGluon(double) =0;
    
                virtual int pickValence() =0;
    
                virtual int pickRemnant() const =0;
    
                virtual double zShare(double, double, double) =0;
    
                virtual double pxShare() const =0;
    
                virtual double pyShare() const =0;
    
                virtual bool remnantFlavoursNew__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual void findColSetup__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual void setInitialCol__BOSS(Pythia8::Abstract_Event&) =0;
    
                virtual void updateCol(std::vector<std::pair<int, int>>) =0;
    
                virtual ::std::vector<std::pair<int, int>> getColUpdates() =0;
    
                virtual bool gammaInitiatorIsVal(int, int, double, double) =0;
    
                virtual bool gammaInitiatorIsVal(int, double) =0;
    
                virtual int getGammaValFlavour() =0;
    
                virtual int gammaValSeaComp(int) =0;
    
                virtual void posVal(int) =0;
    
                virtual void gamVal(int) =0;
    
                virtual int gamVal() =0;
    
                virtual void resolvedGamma(bool) =0;
    
                virtual bool resolvedGamma() const =0;
    
                virtual void setGammaMode(int) =0;
    
                virtual int getGammaMode() const =0;
    
                virtual bool isResolvedUnresolved() const =0;
    
                virtual void initGammaInBeam() =0;
    
                virtual bool gammaInBeam() const =0;
    
                virtual void setVMDstate(bool, int, double, double, bool) =0;
    
                virtual void setVMDstate__BOSS(bool, int, double, double) =0;
    
                virtual void pT2gamma2qqbar(double) =0;
    
                virtual double pT2gamma2qqbar() =0;
    
                virtual void pTMPI(double) =0;
    
                virtual bool roomFor1Remnant(double) =0;
    
                virtual bool roomFor1Remnant(int, double, double) =0;
    
                virtual bool roomFor2Remnants(int, double, double) =0;
    
                virtual bool roomForRemnants__BOSS(Pythia8::Abstract_BeamParticle&) =0;
    
                virtual double remnantMass(int) =0;
    
                virtual double gammaPDFxDependence(int, double) =0;
    
                virtual double gammaPDFRefScale(int) =0;
    
                virtual double xIntegratedPDFs(double) =0;
    
                virtual void xGammaPDF() =0;
    
                virtual void xGamma(double) =0;
    
                virtual void Q2Gamma(double) =0;
    
                virtual void newGammaKTPhi(double, double) =0;
    
                virtual double xGammaMin() =0;
    
                virtual double xGammaHadr() =0;
    
                virtual double gammaFluxIntApprox() =0;
    
                virtual bool hasApproxGammaFlux() =0;
    
                virtual double xGamma() const =0;
    
                virtual double Q2Gamma() const =0;
    
                virtual double gammaKTx() const =0;
    
                virtual double gammaKTy() const =0;
    
                virtual double gammaKT() const =0;
    
                virtual double gammaPhi() const =0;
    
                virtual void xPom(double) =0;
    
                virtual void xPom__BOSS() =0;
    
                virtual double sampleXgamma(double) =0;
    
                virtual double sampleQ2gamma(double) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_BeamParticle*) =0;
                virtual Abstract_BeamParticle* pointer_copy__BOSS() =0;
    
            private:
                BeamParticle* wptr;
                bool delete_wrapper;
            public:
                BeamParticle* get_wptr() { return wptr; }
                void set_wptr(BeamParticle* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_BeamParticle()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_BeamParticle(const Abstract_BeamParticle&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_BeamParticle& operator=(const Abstract_BeamParticle&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                BeamParticle* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                BeamParticle& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_BeamParticle() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_BeamParticle_Pythia_8_312_h__ */
