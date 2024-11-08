#ifndef __wrapper_BeamParticle_decl_Pythia_8_312_h__
#define __wrapper_BeamParticle_decl_Pythia_8_312_h__

#include <cstddef>
#include <utility>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_BeamParticle.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class BeamParticle : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_BeamParticle* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void initID(int idIn);
        
                void newValenceContent();
        
                void setValenceContent(int idq1, int idq2, int idq3);
        
                void setValenceContent(int idq1, int idq2);
        
                void setValenceContent(int idq1);
        
                void setBeamID(int idIn, int iPDFin);
        
                void setBeamID(int idIn);
        
                void newPzE(double pzIn, double eIn);
        
                void newM(double mIn);
        
                int id() const;
        
                int idVMD() const;
        
                Pythia8::Vec4 p() const;
        
                double px() const;
        
                double py() const;
        
                double pz() const;
        
                double e() const;
        
                double m() const;
        
                double mVMD() const;
        
                double scaleVMD() const;
        
                bool isLepton() const;
        
                bool isUnresolved() const;
        
                bool isHadron() const;
        
                bool isMeson() const;
        
                bool isBaryon() const;
        
                bool isGamma() const;
        
                bool hasResGamma() const;
        
                bool hasVMDstate() const;
        
                double xMax(int iSkip);
        
                double xMax();
        
                double xfHard(int idIn, double x, double Q2);
        
                double xfMax(int idIn, double x, double Q2);
        
                double xfFlux(int idIn, double x, double Q2);
        
                double xfApprox(int idIn, double x, double Q2);
        
                double xfGamma(int idIn, double x, double Q2);
        
                double xfSame(int idIn, double x, double Q2);
        
                double xf(int idIn, double x, double Q2);
        
                double xfVal(int idIn, double x, double Q2);
        
                double xfSea(int idIn, double x, double Q2);
        
                double xfMPI(int idIn, double x, double Q2);
        
                double xfISR(int indexMPI, int idIn, double x, double Q2);
        
                bool insideBounds(double x, double Q2);
        
                double alphaS(double Q2);
        
                double mQuarkPDF(int idIn);
        
                int nMembers();
        
                void calcPDFEnvelope(int idNow, double xNow, double Q2Now, int valSea);
        
                void calcPDFEnvelope(std::pair<int, int> idNows, std::pair<double, double> xNows, double Q2Now, int valSea);
        
                int pickValSeaComp();
        
                void initBeamKind();
        
                int size() const;
        
                int sizeInit() const;
        
                void clear();
        
                void resetGamma();
        
                void resetGammaInLepton();
        
                int append(int iPos, int idIn, double x, int companion);
        
                int append(int iPos, int idIn, double x);
        
                void popBack();
        
                void list() const;
        
                int nValenceKinds() const;
        
                int nValence(int idIn) const;
        
                bool isUnresolvedLepton();
        
                bool remnantFlavours(Pythia8::Event& event, bool isDIS);
        
                bool remnantFlavours(Pythia8::Event& event);
        
                bool remnantColours(Pythia8::Event& event, std::vector<int>& colFrom, std::vector<int>& colTo);
        
                double xRemnant(int i);
        
                bool hasJunction() const;
        
                int junctionCol(int i) const;
        
                void junctionCol(int i, int col);
        
                bool pickGluon(double mDiff);
        
                int pickValence();
        
                int pickRemnant() const;
        
                double zShare(double mDiff, double m1, double m2);
        
                double pxShare() const;
        
                double pyShare() const;
        
                bool remnantFlavoursNew(Pythia8::Event& event);
        
                void findColSetup(Pythia8::Event& event);
        
                void setInitialCol(Pythia8::Event& event);
        
                void updateCol(std::vector<std::pair<int, int>> colourChanges);
        
                ::std::vector<std::pair<int, int>> getColUpdates();
        
                bool gammaInitiatorIsVal(int iResolved, int id, double x, double Q2);
        
                bool gammaInitiatorIsVal(int iResolved, double Q2);
        
                int getGammaValFlavour();
        
                int gammaValSeaComp(int iResolved);
        
                void posVal(int iPosValIn);
        
                void gamVal(int iGamValIn);
        
                int gamVal();
        
                void resolvedGamma(bool isResolved);
        
                bool resolvedGamma() const;
        
                void setGammaMode(int gammaModeIn);
        
                int getGammaMode() const;
        
                bool isResolvedUnresolved() const;
        
                void initGammaInBeam();
        
                bool gammaInBeam() const;
        
                void setVMDstate(bool isVMDIn, int idIn, double mIn, double scaleIn, bool reassignState);
        
                void setVMDstate(bool isVMDIn, int idIn, double mIn, double scaleIn);
        
                void pT2gamma2qqbar(double pT2in);
        
                double pT2gamma2qqbar();
        
                void pTMPI(double pTminMPIin);
        
                bool roomFor1Remnant(double eCM);
        
                bool roomFor1Remnant(int id1, double x1, double eCM);
        
                bool roomFor2Remnants(int id1, double x1, double eCM);
        
                bool roomForRemnants(Pythia8::BeamParticle beamOther);
        
                double remnantMass(int idIn);
        
                double gammaPDFxDependence(int flavour, double x);
        
                double gammaPDFRefScale(int flavour);
        
                double xIntegratedPDFs(double Q2);
        
                void xGammaPDF();
        
                void xGamma(double xGmIn);
        
                void Q2Gamma(double Q2GmIn);
        
                void newGammaKTPhi(double kTIn, double phiIn);
        
                double xGammaMin();
        
                double xGammaHadr();
        
                double gammaFluxIntApprox();
        
                bool hasApproxGammaFlux();
        
                double xGamma() const;
        
                double Q2Gamma() const;
        
                double gammaKTx() const;
        
                double gammaKTy() const;
        
                double gammaKT() const;
        
                double gammaPhi() const;
        
                void xPom(double xpom);
        
                void xPom();
        
                double sampleXgamma(double xMinIn);
        
                double sampleQ2gamma(double Q2min);
        
        
                // Wrappers for original constructors: 
            public:
                BeamParticle();
        
                // Special pointer-based constructor: 
                BeamParticle(Abstract_BeamParticle* in);
        
                // Copy constructor: 
                BeamParticle(const BeamParticle& in);
        
                // Assignment operator: 
                BeamParticle& operator=(const BeamParticle& in);
        
                // Destructor: 
                ~BeamParticle();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_BeamParticle* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_BeamParticle_decl_Pythia_8_312_h__ */
