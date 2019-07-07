#ifndef __wrapper_Particle_def_Pythia_EM_8_212_h__
#define __wrapper_Particle_def_Pythia_EM_8_212_h__

#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_ParticleDataEntry_decl.h"
#include <vector>
#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Particle::setEvtPtr(Pythia8::Event* evtPtrIn)
        {
            get_BEptr()->setEvtPtr__BOSS((*evtPtrIn).get_BEptr());
        }
        
        inline void Particle::setPDEPtr(Pythia8::ParticleDataEntry* pdePtrIn)
        {
            get_BEptr()->setPDEPtr__BOSS((*pdePtrIn).get_BEptr());
        }
        
        inline void Particle::setPDEPtr()
        {
            get_BEptr()->setPDEPtr__BOSS();
        }
        
        inline void Particle::id(int idIn)
        {
            get_BEptr()->id(idIn);
        }
        
        inline void Particle::status(int statusIn)
        {
            get_BEptr()->status(statusIn);
        }
        
        inline void Particle::statusPos()
        {
            get_BEptr()->statusPos();
        }
        
        inline void Particle::statusNeg()
        {
            get_BEptr()->statusNeg();
        }
        
        inline void Particle::statusCode(int statusIn)
        {
            get_BEptr()->statusCode(statusIn);
        }
        
        inline void Particle::mother1(int mother1In)
        {
            get_BEptr()->mother1(mother1In);
        }
        
        inline void Particle::mother2(int mother2In)
        {
            get_BEptr()->mother2(mother2In);
        }
        
        inline void Particle::mothers(int mother1In, int mother2In)
        {
            get_BEptr()->mothers(mother1In, mother2In);
        }
        
        inline void Particle::mothers(int mother1In)
        {
            get_BEptr()->mothers__BOSS(mother1In);
        }
        
        inline void Particle::mothers()
        {
            get_BEptr()->mothers__BOSS();
        }
        
        inline void Particle::daughter1(int daughter1In)
        {
            get_BEptr()->daughter1(daughter1In);
        }
        
        inline void Particle::daughter2(int daughter2In)
        {
            get_BEptr()->daughter2(daughter2In);
        }
        
        inline void Particle::daughters(int daughter1In, int daughter2In)
        {
            get_BEptr()->daughters(daughter1In, daughter2In);
        }
        
        inline void Particle::daughters(int daughter1In)
        {
            get_BEptr()->daughters__BOSS(daughter1In);
        }
        
        inline void Particle::daughters()
        {
            get_BEptr()->daughters__BOSS();
        }
        
        inline void Particle::col(int colIn)
        {
            get_BEptr()->col(colIn);
        }
        
        inline void Particle::acol(int acolIn)
        {
            get_BEptr()->acol(acolIn);
        }
        
        inline void Particle::cols(int colIn, int acolIn)
        {
            get_BEptr()->cols(colIn, acolIn);
        }
        
        inline void Particle::cols(int colIn)
        {
            get_BEptr()->cols__BOSS(colIn);
        }
        
        inline void Particle::cols()
        {
            get_BEptr()->cols__BOSS();
        }
        
        inline void Particle::p(Pythia8::Vec4 pIn)
        {
            get_BEptr()->p__BOSS(*pIn.get_BEptr());
        }
        
        inline void Particle::p(double pxIn, double pyIn, double pzIn, double eIn)
        {
            get_BEptr()->p(pxIn, pyIn, pzIn, eIn);
        }
        
        inline void Particle::px(double pxIn)
        {
            get_BEptr()->px(pxIn);
        }
        
        inline void Particle::py(double pyIn)
        {
            get_BEptr()->py(pyIn);
        }
        
        inline void Particle::pz(double pzIn)
        {
            get_BEptr()->pz(pzIn);
        }
        
        inline void Particle::e(double eIn)
        {
            get_BEptr()->e(eIn);
        }
        
        inline void Particle::m(double mIn)
        {
            get_BEptr()->m(mIn);
        }
        
        inline void Particle::scale(double scaleIn)
        {
            get_BEptr()->scale(scaleIn);
        }
        
        inline void Particle::pol(double polIn)
        {
            get_BEptr()->pol(polIn);
        }
        
        inline void Particle::vProd(Pythia8::Vec4 vProdIn)
        {
            get_BEptr()->vProd__BOSS(*vProdIn.get_BEptr());
        }
        
        inline void Particle::vProd(double xProdIn, double yProdIn, double zProdIn, double tProdIn)
        {
            get_BEptr()->vProd(xProdIn, yProdIn, zProdIn, tProdIn);
        }
        
        inline void Particle::xProd(double xProdIn)
        {
            get_BEptr()->xProd(xProdIn);
        }
        
        inline void Particle::yProd(double yProdIn)
        {
            get_BEptr()->yProd(yProdIn);
        }
        
        inline void Particle::zProd(double zProdIn)
        {
            get_BEptr()->zProd(zProdIn);
        }
        
        inline void Particle::tProd(double tProdIn)
        {
            get_BEptr()->tProd(tProdIn);
        }
        
        inline void Particle::tau(double tauIn)
        {
            get_BEptr()->tau(tauIn);
        }
        
        inline int Particle::id() const
        {
            return get_BEptr()->id();
        }
        
        inline int Particle::status() const
        {
            return get_BEptr()->status();
        }
        
        inline int Particle::mother1() const
        {
            return get_BEptr()->mother1();
        }
        
        inline int Particle::mother2() const
        {
            return get_BEptr()->mother2();
        }
        
        inline int Particle::daughter1() const
        {
            return get_BEptr()->daughter1();
        }
        
        inline int Particle::daughter2() const
        {
            return get_BEptr()->daughter2();
        }
        
        inline int Particle::col() const
        {
            return get_BEptr()->col();
        }
        
        inline int Particle::acol() const
        {
            return get_BEptr()->acol();
        }
        
        inline Pythia8::Vec4 Particle::p() const
        {
            return Pythia8::Vec4( const_cast<const Abstract_Particle*>(get_BEptr())->p__BOSS() );
        }
        
        inline double Particle::px() const
        {
            return get_BEptr()->px();
        }
        
        inline double Particle::py() const
        {
            return get_BEptr()->py();
        }
        
        inline double Particle::pz() const
        {
            return get_BEptr()->pz();
        }
        
        inline double Particle::e() const
        {
            return get_BEptr()->e();
        }
        
        inline double Particle::m() const
        {
            return get_BEptr()->m();
        }
        
        inline double Particle::scale() const
        {
            return get_BEptr()->scale();
        }
        
        inline double Particle::pol() const
        {
            return get_BEptr()->pol();
        }
        
        inline bool Particle::hasVertex() const
        {
            return get_BEptr()->hasVertex();
        }
        
        inline Pythia8::Vec4 Particle::vProd() const
        {
            return Pythia8::Vec4( const_cast<const Abstract_Particle*>(get_BEptr())->vProd__BOSS() );
        }
        
        inline double Particle::xProd() const
        {
            return get_BEptr()->xProd();
        }
        
        inline double Particle::yProd() const
        {
            return get_BEptr()->yProd();
        }
        
        inline double Particle::zProd() const
        {
            return get_BEptr()->zProd();
        }
        
        inline double Particle::tProd() const
        {
            return get_BEptr()->tProd();
        }
        
        inline double Particle::tau() const
        {
            return get_BEptr()->tau();
        }
        
        inline int Particle::idAbs() const
        {
            return get_BEptr()->idAbs();
        }
        
        inline int Particle::statusAbs() const
        {
            return get_BEptr()->statusAbs();
        }
        
        inline bool Particle::isFinal() const
        {
            return get_BEptr()->isFinal();
        }
        
        inline bool Particle::isRescatteredIncoming() const
        {
            return get_BEptr()->isRescatteredIncoming();
        }
        
        inline double Particle::m2() const
        {
            return get_BEptr()->m2();
        }
        
        inline double Particle::mCalc() const
        {
            return get_BEptr()->mCalc();
        }
        
        inline double Particle::m2Calc() const
        {
            return get_BEptr()->m2Calc();
        }
        
        inline double Particle::eCalc() const
        {
            return get_BEptr()->eCalc();
        }
        
        inline double Particle::pT() const
        {
            return get_BEptr()->pT();
        }
        
        inline double Particle::pT2() const
        {
            return get_BEptr()->pT2();
        }
        
        inline double Particle::mT() const
        {
            return get_BEptr()->mT();
        }
        
        inline double Particle::mT2() const
        {
            return get_BEptr()->mT2();
        }
        
        inline double Particle::pAbs() const
        {
            return get_BEptr()->pAbs();
        }
        
        inline double Particle::pAbs2() const
        {
            return get_BEptr()->pAbs2();
        }
        
        inline double Particle::eT() const
        {
            return get_BEptr()->eT();
        }
        
        inline double Particle::eT2() const
        {
            return get_BEptr()->eT2();
        }
        
        inline double Particle::theta() const
        {
            return get_BEptr()->theta();
        }
        
        inline double Particle::phi() const
        {
            return get_BEptr()->phi();
        }
        
        inline double Particle::thetaXZ() const
        {
            return get_BEptr()->thetaXZ();
        }
        
        inline double Particle::pPos() const
        {
            return get_BEptr()->pPos();
        }
        
        inline double Particle::pNeg() const
        {
            return get_BEptr()->pNeg();
        }
        
        inline double Particle::y() const
        {
            return get_BEptr()->y();
        }
        
        inline double Particle::eta() const
        {
            return get_BEptr()->eta();
        }
        
        inline Pythia8::Vec4 Particle::vDec() const
        {
            return Pythia8::Vec4( const_cast<const Abstract_Particle*>(get_BEptr())->vDec__BOSS() );
        }
        
        inline double Particle::xDec() const
        {
            return get_BEptr()->xDec();
        }
        
        inline double Particle::yDec() const
        {
            return get_BEptr()->yDec();
        }
        
        inline double Particle::zDec() const
        {
            return get_BEptr()->zDec();
        }
        
        inline double Particle::tDec() const
        {
            return get_BEptr()->tDec();
        }
        
        inline int Particle::index() const
        {
            return get_BEptr()->index();
        }
        
        inline int Particle::iTopCopy() const
        {
            return get_BEptr()->iTopCopy();
        }
        
        inline int Particle::iBotCopy() const
        {
            return get_BEptr()->iBotCopy();
        }
        
        inline int Particle::iTopCopyId(bool simplify) const
        {
            return get_BEptr()->iTopCopyId(simplify);
        }
        
        inline int Particle::iTopCopyId() const
        {
            return get_BEptr()->iTopCopyId__BOSS();
        }
        
        inline int Particle::iBotCopyId(bool simplify) const
        {
            return get_BEptr()->iBotCopyId(simplify);
        }
        
        inline int Particle::iBotCopyId() const
        {
            return get_BEptr()->iBotCopyId__BOSS();
        }
        
        inline ::std::vector<int, std::allocator<int> > Particle::motherList() const
        {
            return get_BEptr()->motherList();
        }
        
        inline ::std::vector<int, std::allocator<int> > Particle::daughterList() const
        {
            return get_BEptr()->daughterList();
        }
        
        inline ::std::vector<int, std::allocator<int> > Particle::sisterList(bool traceTopBot) const
        {
            return get_BEptr()->sisterList(traceTopBot);
        }
        
        inline ::std::vector<int, std::allocator<int> > Particle::sisterList() const
        {
            return get_BEptr()->sisterList__BOSS();
        }
        
        inline bool Particle::isAncestor(int iAncestor) const
        {
            return get_BEptr()->isAncestor(iAncestor);
        }
        
        inline int Particle::statusHepMC() const
        {
            return get_BEptr()->statusHepMC();
        }
        
        inline bool Particle::isFinalPartonLevel() const
        {
            return get_BEptr()->isFinalPartonLevel();
        }
        
        inline bool Particle::undoDecay()
        {
            return get_BEptr()->undoDecay();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Particle::name() const
        {
            return get_BEptr()->name();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Particle::nameWithStatus(int maxLen) const
        {
            return get_BEptr()->nameWithStatus(maxLen);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Particle::nameWithStatus() const
        {
            return get_BEptr()->nameWithStatus__BOSS();
        }
        
        inline int Particle::spinType() const
        {
            return get_BEptr()->spinType();
        }
        
        inline int Particle::chargeType() const
        {
            return get_BEptr()->chargeType();
        }
        
        inline double Particle::charge() const
        {
            return get_BEptr()->charge();
        }
        
        inline bool Particle::isCharged() const
        {
            return get_BEptr()->isCharged();
        }
        
        inline bool Particle::isNeutral() const
        {
            return get_BEptr()->isNeutral();
        }
        
        inline int Particle::colType() const
        {
            return get_BEptr()->colType();
        }
        
        inline double Particle::m0() const
        {
            return get_BEptr()->m0();
        }
        
        inline double Particle::mWidth() const
        {
            return get_BEptr()->mWidth();
        }
        
        inline double Particle::mMin() const
        {
            return get_BEptr()->mMin();
        }
        
        inline double Particle::mMax() const
        {
            return get_BEptr()->mMax();
        }
        
        inline double Particle::mSel() const
        {
            return get_BEptr()->mSel();
        }
        
        inline double Particle::constituentMass() const
        {
            return get_BEptr()->constituentMass();
        }
        
        inline double Particle::tau0() const
        {
            return get_BEptr()->tau0();
        }
        
        inline bool Particle::mayDecay() const
        {
            return get_BEptr()->mayDecay();
        }
        
        inline bool Particle::canDecay() const
        {
            return get_BEptr()->canDecay();
        }
        
        inline bool Particle::doExternalDecay() const
        {
            return get_BEptr()->doExternalDecay();
        }
        
        inline bool Particle::isResonance() const
        {
            return get_BEptr()->isResonance();
        }
        
        inline bool Particle::isVisible() const
        {
            return get_BEptr()->isVisible();
        }
        
        inline bool Particle::isLepton() const
        {
            return get_BEptr()->isLepton();
        }
        
        inline bool Particle::isQuark() const
        {
            return get_BEptr()->isQuark();
        }
        
        inline bool Particle::isGluon() const
        {
            return get_BEptr()->isGluon();
        }
        
        inline bool Particle::isDiquark() const
        {
            return get_BEptr()->isDiquark();
        }
        
        inline bool Particle::isParton() const
        {
            return get_BEptr()->isParton();
        }
        
        inline bool Particle::isHadron() const
        {
            return get_BEptr()->isHadron();
        }
        
        inline Pythia8::ParticleDataEntry& Particle::particleDataEntry() const
        {
            return const_cast<const Abstract_Particle*>(get_BEptr())->particleDataEntry__BOSS().get_init_wref();
        }
        
        inline void Particle::rescale3(double fac)
        {
            get_BEptr()->rescale3(fac);
        }
        
        inline void Particle::rescale4(double fac)
        {
            get_BEptr()->rescale4(fac);
        }
        
        inline void Particle::rescale5(double fac)
        {
            get_BEptr()->rescale5(fac);
        }
        
        inline void Particle::rot(double thetaIn, double phiIn)
        {
            get_BEptr()->rot(thetaIn, phiIn);
        }
        
        inline void Particle::bst(double betaX, double betaY, double betaZ)
        {
            get_BEptr()->bst(betaX, betaY, betaZ);
        }
        
        inline void Particle::bst(double betaX, double betaY, double betaZ, double gamma)
        {
            get_BEptr()->bst(betaX, betaY, betaZ, gamma);
        }
        
        inline void Particle::bst(const Pythia8::Vec4& pBst)
        {
            get_BEptr()->bst__BOSS(*pBst.get_BEptr());
        }
        
        inline void Particle::bst(const Pythia8::Vec4& pBst, double mBst)
        {
            get_BEptr()->bst__BOSS(*pBst.get_BEptr(), mBst);
        }
        
        inline void Particle::bstback(const Pythia8::Vec4& pBst)
        {
            get_BEptr()->bstback__BOSS(*pBst.get_BEptr());
        }
        
        inline void Particle::bstback(const Pythia8::Vec4& pBst, double mBst)
        {
            get_BEptr()->bstback__BOSS(*pBst.get_BEptr(), mBst);
        }
        
        inline void Particle::offsetHistory(int minMother, int addMother, int minDaughter, int addDaughter)
        {
            get_BEptr()->offsetHistory(minMother, addMother, minDaughter, addDaughter);
        }
        
        inline void Particle::offsetCol(int addCol)
        {
            get_BEptr()->offsetCol(addCol);
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia8::Particle::Particle() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn, double mIn, double scaleIn, double polIn) :
            WrapperBase(__factory1(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pxIn, pyIn, pzIn, eIn, mIn, scaleIn, polIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn, double mIn, double scaleIn) :
            WrapperBase(__factory2(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pxIn, pyIn, pzIn, eIn, mIn, scaleIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn, double mIn) :
            WrapperBase(__factory3(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pxIn, pyIn, pzIn, eIn, mIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn, double eIn) :
            WrapperBase(__factory4(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pxIn, pyIn, pzIn, eIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn, double pzIn) :
            WrapperBase(__factory5(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pxIn, pyIn, pzIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn, double pyIn) :
            WrapperBase(__factory6(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pxIn, pyIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, double pxIn) :
            WrapperBase(__factory7(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pxIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn) :
            WrapperBase(__factory8(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn) :
            WrapperBase(__factory9(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In) :
            WrapperBase(__factory10(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In) :
            WrapperBase(__factory11(idIn, statusIn, mother1In, mother2In, daughter1In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In) :
            WrapperBase(__factory12(idIn, statusIn, mother1In, mother2In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In) :
            WrapperBase(__factory13(idIn, statusIn, mother1In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn) :
            WrapperBase(__factory14(idIn, statusIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn) :
            WrapperBase(__factory15(idIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn, double mIn, double scaleIn, double polIn) :
            WrapperBase(__factory16(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pIn, mIn, scaleIn, polIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn, double mIn, double scaleIn) :
            WrapperBase(__factory17(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pIn, mIn, scaleIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn, double mIn) :
            WrapperBase(__factory18(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pIn, mIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia8::Particle::Particle(int idIn, int statusIn, int mother1In, int mother2In, int daughter1In, int daughter2In, int colIn, int acolIn, Pythia8::Vec4 pIn) :
            WrapperBase(__factory19(idIn, statusIn, mother1In, mother2In, daughter1In, daughter2In, colIn, acolIn, pIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia8::Particle::Particle(Pythia8::Abstract_Particle* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Pythia8::Particle::Particle(const Particle& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia8::Particle& Particle::operator=(const Particle& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Pythia8::Particle::~Particle()
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
        inline Pythia8::Abstract_Particle* Pythia8::Particle::get_BEptr() const
        {
            return dynamic_cast<Pythia8::Abstract_Particle*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Particle_def_Pythia_EM_8_212_h__ */
