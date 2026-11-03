#ifndef __wrapper_BeamParticle_def_Pythia_8_312_h__
#define __wrapper_BeamParticle_def_Pythia_8_312_h__

#include <utility>
#include <vector>
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void BeamParticle::initID(int idIn)
        {
            get_BEptr()->initID(idIn);
        }
        
        inline void BeamParticle::newValenceContent()
        {
            get_BEptr()->newValenceContent();
        }
        
        inline void BeamParticle::setValenceContent(int idq1, int idq2, int idq3)
        {
            get_BEptr()->setValenceContent(idq1, idq2, idq3);
        }
        
        inline void BeamParticle::setValenceContent(int idq1, int idq2)
        {
            get_BEptr()->setValenceContent__BOSS(idq1, idq2);
        }
        
        inline void BeamParticle::setValenceContent(int idq1)
        {
            get_BEptr()->setValenceContent__BOSS(idq1);
        }
        
        inline void BeamParticle::setBeamID(int idIn, int iPDFin)
        {
            get_BEptr()->setBeamID(idIn, iPDFin);
        }
        
        inline void BeamParticle::setBeamID(int idIn)
        {
            get_BEptr()->setBeamID__BOSS(idIn);
        }
        
        inline void BeamParticle::newPzE(double pzIn, double eIn)
        {
            get_BEptr()->newPzE(pzIn, eIn);
        }
        
        inline void BeamParticle::newM(double mIn)
        {
            get_BEptr()->newM(mIn);
        }
        
        inline int BeamParticle::id() const
        {
            return get_BEptr()->id();
        }
        
        inline int BeamParticle::idVMD() const
        {
            return get_BEptr()->idVMD();
        }
        
        inline Pythia8::Vec4 BeamParticle::p() const
        {
            return Pythia8::Vec4( const_cast<const Abstract_BeamParticle*>(get_BEptr())->p__BOSS() );
        }
        
        inline double BeamParticle::px() const
        {
            return get_BEptr()->px();
        }
        
        inline double BeamParticle::py() const
        {
            return get_BEptr()->py();
        }
        
        inline double BeamParticle::pz() const
        {
            return get_BEptr()->pz();
        }
        
        inline double BeamParticle::e() const
        {
            return get_BEptr()->e();
        }
        
        inline double BeamParticle::m() const
        {
            return get_BEptr()->m();
        }
        
        inline double BeamParticle::mVMD() const
        {
            return get_BEptr()->mVMD();
        }
        
        inline double BeamParticle::scaleVMD() const
        {
            return get_BEptr()->scaleVMD();
        }
        
        inline bool BeamParticle::isLepton() const
        {
            return get_BEptr()->isLepton();
        }
        
        inline bool BeamParticle::isUnresolved() const
        {
            return get_BEptr()->isUnresolved();
        }
        
        inline bool BeamParticle::isHadron() const
        {
            return get_BEptr()->isHadron();
        }
        
        inline bool BeamParticle::isMeson() const
        {
            return get_BEptr()->isMeson();
        }
        
        inline bool BeamParticle::isBaryon() const
        {
            return get_BEptr()->isBaryon();
        }
        
        inline bool BeamParticle::isGamma() const
        {
            return get_BEptr()->isGamma();
        }
        
        inline bool BeamParticle::hasResGamma() const
        {
            return get_BEptr()->hasResGamma();
        }
        
        inline bool BeamParticle::hasVMDstate() const
        {
            return get_BEptr()->hasVMDstate();
        }
        
        inline double BeamParticle::xMax(int iSkip)
        {
            return get_BEptr()->xMax(iSkip);
        }
        
        inline double BeamParticle::xMax()
        {
            return get_BEptr()->xMax__BOSS();
        }
        
        inline double BeamParticle::xfHard(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfHard(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfMax(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfMax(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfFlux(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfFlux(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfApprox(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfApprox(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfGamma(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfGamma(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfSame(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfSame(idIn, x, Q2);
        }
        
        inline double BeamParticle::xf(int idIn, double x, double Q2)
        {
            return get_BEptr()->xf(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfVal(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfVal(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfSea(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfSea(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfMPI(int idIn, double x, double Q2)
        {
            return get_BEptr()->xfMPI(idIn, x, Q2);
        }
        
        inline double BeamParticle::xfISR(int indexMPI, int idIn, double x, double Q2)
        {
            return get_BEptr()->xfISR(indexMPI, idIn, x, Q2);
        }
        
        inline bool BeamParticle::insideBounds(double x, double Q2)
        {
            return get_BEptr()->insideBounds(x, Q2);
        }
        
        inline double BeamParticle::alphaS(double Q2)
        {
            return get_BEptr()->alphaS(Q2);
        }
        
        inline double BeamParticle::mQuarkPDF(int idIn)
        {
            return get_BEptr()->mQuarkPDF(idIn);
        }
        
        inline int BeamParticle::nMembers()
        {
            return get_BEptr()->nMembers();
        }
        
        inline void BeamParticle::calcPDFEnvelope(int idNow, double xNow, double Q2Now, int valSea)
        {
            get_BEptr()->calcPDFEnvelope(idNow, xNow, Q2Now, valSea);
        }
        
        inline void BeamParticle::calcPDFEnvelope(std::pair<int, int> idNows, std::pair<double, double> xNows, double Q2Now, int valSea)
        {
            get_BEptr()->calcPDFEnvelope(idNows, xNows, Q2Now, valSea);
        }
        
        inline int BeamParticle::pickValSeaComp()
        {
            return get_BEptr()->pickValSeaComp();
        }
        
        inline void BeamParticle::initBeamKind()
        {
            get_BEptr()->initBeamKind();
        }
        
        inline int BeamParticle::size() const
        {
            return get_BEptr()->size();
        }
        
        inline int BeamParticle::sizeInit() const
        {
            return get_BEptr()->sizeInit();
        }
        
        inline void BeamParticle::clear()
        {
            get_BEptr()->clear();
        }
        
        inline void BeamParticle::resetGamma()
        {
            get_BEptr()->resetGamma();
        }
        
        inline void BeamParticle::resetGammaInLepton()
        {
            get_BEptr()->resetGammaInLepton();
        }
        
        inline int BeamParticle::append(int iPos, int idIn, double x, int companion)
        {
            return get_BEptr()->append(iPos, idIn, x, companion);
        }
        
        inline int BeamParticle::append(int iPos, int idIn, double x)
        {
            return get_BEptr()->append__BOSS(iPos, idIn, x);
        }
        
        inline void BeamParticle::popBack()
        {
            get_BEptr()->popBack();
        }
        
        inline void BeamParticle::list() const
        {
            get_BEptr()->list();
        }
        
        inline int BeamParticle::nValenceKinds() const
        {
            return get_BEptr()->nValenceKinds();
        }
        
        inline int BeamParticle::nValence(int idIn) const
        {
            return get_BEptr()->nValence(idIn);
        }
        
        inline bool BeamParticle::isUnresolvedLepton()
        {
            return get_BEptr()->isUnresolvedLepton();
        }
        
        inline bool BeamParticle::remnantFlavours(Pythia8::Event& event, bool isDIS)
        {
            return get_BEptr()->remnantFlavours__BOSS(*event.get_BEptr(), isDIS);
        }
        
        inline bool BeamParticle::remnantFlavours(Pythia8::Event& event)
        {
            return get_BEptr()->remnantFlavours__BOSS(*event.get_BEptr());
        }
        
        inline bool BeamParticle::remnantColours(Pythia8::Event& event, std::vector<int>& colFrom, std::vector<int>& colTo)
        {
            return get_BEptr()->remnantColours__BOSS(*event.get_BEptr(), colFrom, colTo);
        }
        
        inline double BeamParticle::xRemnant(int i)
        {
            return get_BEptr()->xRemnant(i);
        }
        
        inline bool BeamParticle::hasJunction() const
        {
            return get_BEptr()->hasJunction();
        }
        
        inline int BeamParticle::junctionCol(int i) const
        {
            return get_BEptr()->junctionCol(i);
        }
        
        inline void BeamParticle::junctionCol(int i, int col)
        {
            get_BEptr()->junctionCol(i, col);
        }
        
        inline bool BeamParticle::pickGluon(double mDiff)
        {
            return get_BEptr()->pickGluon(mDiff);
        }
        
        inline int BeamParticle::pickValence()
        {
            return get_BEptr()->pickValence();
        }
        
        inline int BeamParticle::pickRemnant() const
        {
            return get_BEptr()->pickRemnant();
        }
        
        inline double BeamParticle::zShare(double mDiff, double m1, double m2)
        {
            return get_BEptr()->zShare(mDiff, m1, m2);
        }
        
        inline double BeamParticle::pxShare() const
        {
            return get_BEptr()->pxShare();
        }
        
        inline double BeamParticle::pyShare() const
        {
            return get_BEptr()->pyShare();
        }
        
        inline bool BeamParticle::remnantFlavoursNew(Pythia8::Event& event)
        {
            return get_BEptr()->remnantFlavoursNew__BOSS(*event.get_BEptr());
        }
        
        inline void BeamParticle::findColSetup(Pythia8::Event& event)
        {
            get_BEptr()->findColSetup__BOSS(*event.get_BEptr());
        }
        
        inline void BeamParticle::setInitialCol(Pythia8::Event& event)
        {
            get_BEptr()->setInitialCol__BOSS(*event.get_BEptr());
        }
        
        inline void BeamParticle::updateCol(std::vector<std::pair<int, int>> colourChanges)
        {
            get_BEptr()->updateCol(colourChanges);
        }
        
        inline ::std::vector<std::pair<int, int>> BeamParticle::getColUpdates()
        {
            return get_BEptr()->getColUpdates();
        }
        
        inline bool BeamParticle::gammaInitiatorIsVal(int iResolved, int id, double x, double Q2)
        {
            return get_BEptr()->gammaInitiatorIsVal(iResolved, id, x, Q2);
        }
        
        inline bool BeamParticle::gammaInitiatorIsVal(int iResolved, double Q2)
        {
            return get_BEptr()->gammaInitiatorIsVal(iResolved, Q2);
        }
        
        inline int BeamParticle::getGammaValFlavour()
        {
            return get_BEptr()->getGammaValFlavour();
        }
        
        inline int BeamParticle::gammaValSeaComp(int iResolved)
        {
            return get_BEptr()->gammaValSeaComp(iResolved);
        }
        
        inline void BeamParticle::posVal(int iPosValIn)
        {
            get_BEptr()->posVal(iPosValIn);
        }
        
        inline void BeamParticle::gamVal(int iGamValIn)
        {
            get_BEptr()->gamVal(iGamValIn);
        }
        
        inline int BeamParticle::gamVal()
        {
            return get_BEptr()->gamVal();
        }
        
        inline void BeamParticle::resolvedGamma(bool isResolved)
        {
            get_BEptr()->resolvedGamma(isResolved);
        }
        
        inline bool BeamParticle::resolvedGamma() const
        {
            return get_BEptr()->resolvedGamma();
        }
        
        inline void BeamParticle::setGammaMode(int gammaModeIn)
        {
            get_BEptr()->setGammaMode(gammaModeIn);
        }
        
        inline int BeamParticle::getGammaMode() const
        {
            return get_BEptr()->getGammaMode();
        }
        
        inline bool BeamParticle::isResolvedUnresolved() const
        {
            return get_BEptr()->isResolvedUnresolved();
        }
        
        inline void BeamParticle::initGammaInBeam()
        {
            get_BEptr()->initGammaInBeam();
        }
        
        inline bool BeamParticle::gammaInBeam() const
        {
            return get_BEptr()->gammaInBeam();
        }
        
        inline void BeamParticle::setVMDstate(bool isVMDIn, int idIn, double mIn, double scaleIn, bool reassignState)
        {
            get_BEptr()->setVMDstate(isVMDIn, idIn, mIn, scaleIn, reassignState);
        }
        
        inline void BeamParticle::setVMDstate(bool isVMDIn, int idIn, double mIn, double scaleIn)
        {
            get_BEptr()->setVMDstate__BOSS(isVMDIn, idIn, mIn, scaleIn);
        }
        
        inline void BeamParticle::pT2gamma2qqbar(double pT2in)
        {
            get_BEptr()->pT2gamma2qqbar(pT2in);
        }
        
        inline double BeamParticle::pT2gamma2qqbar()
        {
            return get_BEptr()->pT2gamma2qqbar();
        }
        
        inline void BeamParticle::pTMPI(double pTminMPIin)
        {
            get_BEptr()->pTMPI(pTminMPIin);
        }
        
        inline bool BeamParticle::roomFor1Remnant(double eCM)
        {
            return get_BEptr()->roomFor1Remnant(eCM);
        }
        
        inline bool BeamParticle::roomFor1Remnant(int id1, double x1, double eCM)
        {
            return get_BEptr()->roomFor1Remnant(id1, x1, eCM);
        }
        
        inline bool BeamParticle::roomFor2Remnants(int id1, double x1, double eCM)
        {
            return get_BEptr()->roomFor2Remnants(id1, x1, eCM);
        }
        
        inline bool BeamParticle::roomForRemnants(Pythia8::BeamParticle beamOther)
        {
            return get_BEptr()->roomForRemnants__BOSS(*beamOther.get_BEptr());
        }
        
        inline double BeamParticle::remnantMass(int idIn)
        {
            return get_BEptr()->remnantMass(idIn);
        }
        
        inline double BeamParticle::gammaPDFxDependence(int flavour, double x)
        {
            return get_BEptr()->gammaPDFxDependence(flavour, x);
        }
        
        inline double BeamParticle::gammaPDFRefScale(int flavour)
        {
            return get_BEptr()->gammaPDFRefScale(flavour);
        }
        
        inline double BeamParticle::xIntegratedPDFs(double Q2)
        {
            return get_BEptr()->xIntegratedPDFs(Q2);
        }
        
        inline void BeamParticle::xGammaPDF()
        {
            get_BEptr()->xGammaPDF();
        }
        
        inline void BeamParticle::xGamma(double xGmIn)
        {
            get_BEptr()->xGamma(xGmIn);
        }
        
        inline void BeamParticle::Q2Gamma(double Q2GmIn)
        {
            get_BEptr()->Q2Gamma(Q2GmIn);
        }
        
        inline void BeamParticle::newGammaKTPhi(double kTIn, double phiIn)
        {
            get_BEptr()->newGammaKTPhi(kTIn, phiIn);
        }
        
        inline double BeamParticle::xGammaMin()
        {
            return get_BEptr()->xGammaMin();
        }
        
        inline double BeamParticle::xGammaHadr()
        {
            return get_BEptr()->xGammaHadr();
        }
        
        inline double BeamParticle::gammaFluxIntApprox()
        {
            return get_BEptr()->gammaFluxIntApprox();
        }
        
        inline bool BeamParticle::hasApproxGammaFlux()
        {
            return get_BEptr()->hasApproxGammaFlux();
        }
        
        inline double BeamParticle::xGamma() const
        {
            return get_BEptr()->xGamma();
        }
        
        inline double BeamParticle::Q2Gamma() const
        {
            return get_BEptr()->Q2Gamma();
        }
        
        inline double BeamParticle::gammaKTx() const
        {
            return get_BEptr()->gammaKTx();
        }
        
        inline double BeamParticle::gammaKTy() const
        {
            return get_BEptr()->gammaKTy();
        }
        
        inline double BeamParticle::gammaKT() const
        {
            return get_BEptr()->gammaKT();
        }
        
        inline double BeamParticle::gammaPhi() const
        {
            return get_BEptr()->gammaPhi();
        }
        
        inline void BeamParticle::xPom(double xpom)
        {
            get_BEptr()->xPom(xpom);
        }
        
        inline void BeamParticle::xPom()
        {
            get_BEptr()->xPom__BOSS();
        }
        
        inline double BeamParticle::sampleXgamma(double xMinIn)
        {
            return get_BEptr()->sampleXgamma(xMinIn);
        }
        
        inline double BeamParticle::sampleQ2gamma(double Q2min)
        {
            return get_BEptr()->sampleQ2gamma(Q2min);
        }
        
        
        // Wrappers for original constructors: 
        inline BeamParticle::BeamParticle() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline BeamParticle::BeamParticle(Abstract_BeamParticle* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline BeamParticle::BeamParticle(const BeamParticle& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline BeamParticle& BeamParticle::operator=(const BeamParticle& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline BeamParticle::~BeamParticle()
        {
            if (get_BEptr() != 0)
            {
                get_BEptr()->set_delete_wrapper(false);
                if (can_delete_BEptr())
                {
                    delete BEptr;
                    BEptr = 0;
                }
            }
            set_delete_BEptr(false);
        }
        
        // Returns correctly casted pointer to Abstract class: 
        inline Abstract_BeamParticle* Pythia8::BeamParticle::get_BEptr() const
        {
            return dynamic_cast<Abstract_BeamParticle*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_BeamParticle_def_Pythia_8_312_h__ */
