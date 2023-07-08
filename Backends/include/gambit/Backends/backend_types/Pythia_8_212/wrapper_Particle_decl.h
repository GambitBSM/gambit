#ifndef __wrapper_Particle_decl_Pythia_8_212_h__
#define __wrapper_Particle_decl_Pythia_8_212_h__

#include <cstddef>
#include <vector>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Particle.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_ParticleDataEntry_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Particle : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Particle* (*__factory0)();
                static Abstract_Particle* (*__factory1)(int, int, int, int, int, int, int, int, double, double, double, double, double, double, double);
                static Abstract_Particle* (*__factory2)(int, int, int, int, int, int, int, int, double, double, double, double, double, double);
                static Abstract_Particle* (*__factory3)(int, int, int, int, int, int, int, int, double, double, double, double, double);
                static Abstract_Particle* (*__factory4)(int, int, int, int, int, int, int, int, double, double, double, double);
                static Abstract_Particle* (*__factory5)(int, int, int, int, int, int, int, int, double, double, double);
                static Abstract_Particle* (*__factory6)(int, int, int, int, int, int, int, int, double, double);
                static Abstract_Particle* (*__factory7)(int, int, int, int, int, int, int, int, double);
                static Abstract_Particle* (*__factory8)(int, int, int, int, int, int, int, int);
                static Abstract_Particle* (*__factory9)(int, int, int, int, int, int, int);
                static Abstract_Particle* (*__factory10)(int, int, int, int, int, int);
                static Abstract_Particle* (*__factory11)(int, int, int, int, int);
                static Abstract_Particle* (*__factory12)(int, int, int, int);
                static Abstract_Particle* (*__factory13)(int, int, int);
                static Abstract_Particle* (*__factory14)(int, int);
                static Abstract_Particle* (*__factory15)(int);
                static Abstract_Particle* (*__factory16)(int, int, int, int, int, int, int, int, Pythia8::Vec4, double, double, double);
                static Abstract_Particle* (*__factory17)(int, int, int, int, int, int, int, int, Pythia8::Vec4, double, double);
                static Abstract_Particle* (*__factory18)(int, int, int, int, int, int, int, int, Pythia8::Vec4, double);
                static Abstract_Particle* (*__factory19)(int, int, int, int, int, int, int, int, Pythia8::Vec4);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void setEvtPtr(Pythia8::Event* evtPtrIn);
        
                void setPDEPtr(Pythia8::ParticleDataEntry* pdePtrIn);
        
                void setPDEPtr();
        
                void id(int idIn);
        
                void status(int statusIn);
        
                void statusPos();
        
                void statusNeg();
        
                void statusCode(int statusIn);
        
                void mother1(int mother1In);
        
                void mother2(int mother2In);
        
                void mothers(int mother1In, int mother2In);
        
                void mothers(int mother1In);
        
                void mothers();
        
                void daughter1(int daughter1In);
        
                void daughter2(int daughter2In);
        
                void daughters(int daughter1In, int daughter2In);
        
                void daughters(int daughter1In);
        
                void daughters();
        
                void col(int colIn);
        
                void acol(int acolIn);
        
                void cols(int colIn, int acolIn);
        
                void cols(int colIn);
        
                void cols();
        
                void p(Pythia8::Vec4 pIn);
        
                void p(double pxIn, double pyIn, double pzIn, double eIn);
        
                void px(double pxIn);
        
                void py(double pyIn);
        
                void pz(double pzIn);
        
                void e(double eIn);
        
                void m(double mIn);
        
                void scale(double scaleIn);
        
                void pol(double polIn);
        
                void vProd(Pythia8::Vec4 vProdIn);
        
                void vProd(double xProdIn, double yProdIn, double zProdIn, double tProdIn);
        
                void xProd(double xProdIn);
        
                void yProd(double yProdIn);
        
                void zProd(double zProdIn);
        
                void tProd(double tProdIn);
        
                void tau(double tauIn);
        
                int id() const;
        
                int status() const;
        
                int mother1() const;
        
                int mother2() const;
        
                int daughter1() const;
        
                int daughter2() const;
        
                int col() const;
        
                int acol() const;
        
                Pythia8::Vec4 p() const;
        
                double px() const;
        
                double py() const;
        
                double pz() const;
        
                double e() const;
        
                double m() const;
        
                double scale() const;
        
                double pol() const;
        
                bool hasVertex() const;
        
                Pythia8::Vec4 vProd() const;
        
                double xProd() const;
        
                double yProd() const;
        
                double zProd() const;
        
                double tProd() const;
        
                double tau() const;
        
                int idAbs() const;
        
                int statusAbs() const;
        
                bool isFinal() const;
        
                bool isRescatteredIncoming() const;
        
                double m2() const;
        
                double mCalc() const;
        
                double m2Calc() const;
        
                double eCalc() const;
        
                double pT() const;
        
                double pT2() const;
        
                double mT() const;
        
                double mT2() const;
        
                double pAbs() const;
        
                double pAbs2() const;
        
                double eT() const;
        
                double eT2() const;
        
                double theta() const;
        
                double phi() const;
        
                double thetaXZ() const;
        
                double pPos() const;
        
                double pNeg() const;
        
                double y() const;
        
                double eta() const;
        
                Pythia8::Vec4 vDec() const;
        
                double xDec() const;
        
                double yDec() const;
        
                double zDec() const;
        
                double tDec() const;
        
                int index() const;
        
                int iTopCopy() const;
        
                int iBotCopy() const;
        
                int iTopCopyId(bool simplify) const;
        
                int iTopCopyId() const;
        
                int iBotCopyId(bool simplify) const;
        
                int iBotCopyId() const;
        
                ::std::vector<int> motherList() const;
        
                ::std::vector<int> daughterList() const;
        
                ::std::vector<int> sisterList(bool traceTopBot) const;
        
                ::std::vector<int> sisterList() const;
        
                bool isAncestor(int iAncestor) const;
        
                int statusHepMC() const;
        
                bool isFinalPartonLevel() const;
        
                bool undoDecay();
        
                ::std::string name() const;
        
                ::std::string nameWithStatus(int maxLen) const;
        
                ::std::string nameWithStatus() const;
        
                int spinType() const;
        
                int chargeType() const;
        
                double charge() const;
        
                bool isCharged() const;
        
                bool isNeutral() const;
        
                int colType() const;
        
                double m0() const;
        
                double mWidth() const;
        
                double mMin() const;
        
                double mMax() const;
        
                double mSel() const;
        
                double constituentMass() const;
        
                double tau0() const;
        
                bool mayDecay() const;
        
                bool canDecay() const;
        
                bool doExternalDecay() const;
        
                bool isResonance() const;
        
                bool isVisible() const;
        
                bool isLepton() const;
        
                bool isQuark() const;
        
                bool isGluon() const;
        
                bool isDiquark() const;
        
                bool isParton() const;
        
                bool isHadron() const;
        
                Pythia8::ParticleDataEntry& particleDataEntry() const;
        
                void rescale3(double fac);
        
                void rescale4(double fac);
        
                void rescale5(double fac);
        
                void rot(double thetaIn, double phiIn);
        
                void bst(double betaX, double betaY, double betaZ);
        
                void bst(double betaX, double betaY, double betaZ, double gamma);
        
                void bst(const Pythia8::Vec4& pBst);
        
                void bst(const Pythia8::Vec4& pBst, double mBst);
        
                void bstback(const Pythia8::Vec4& pBst);
        
                void bstback(const Pythia8::Vec4& pBst, double mBst);
        
                void offsetHistory(int minMother, int addMother, int minDaughter, int addDaughter);
        
                void offsetCol(int addCol);
        
        
                // Wrappers for original constructors: 
            public:
                Particle();
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn, double mIn, double scaleIn, double polIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn, double mIn, double scaleIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn, double mIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In);
                Particle(int idIn, int statusIn, int mother1In, int mother2In);
                Particle(int idIn, int statusIn, int mother1In);
                Particle(int idIn, int statusIn);
                Particle(int idIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn, double mIn, double scaleIn, double polIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn, double mIn, double scaleIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn, double mIn);
                Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn);
        
                // Special pointer-based constructor: 
                Particle(Abstract_Particle* in);
        
                // Copy constructor: 
                Particle(const Particle& in);
        
                // Assignment operator: 
                Particle& operator=(const Particle& in);
        
                // Destructor: 
                ~Particle();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Particle* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Particle_decl_Pythia_8_212_h__ */
