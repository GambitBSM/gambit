#ifndef __wrapper_Info_def_Pythia_8_212_h__
#define __wrapper_Info_def_Pythia_8_212_h__

#include <ostream>
#include <string>
#include <vector>
#include <map>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Info::list(::std::basic_ostream<char, std::char_traits<char> >& os) const
        {
            get_BEptr()->list(os);
        }
        
        inline void Info::list() const
        {
            get_BEptr()->list__BOSS();
        }
        
        inline int Info::idA() const
        {
            return get_BEptr()->idA();
        }
        
        inline int Info::idB() const
        {
            return get_BEptr()->idB();
        }
        
        inline double Info::pzA() const
        {
            return get_BEptr()->pzA();
        }
        
        inline double Info::pzB() const
        {
            return get_BEptr()->pzB();
        }
        
        inline double Info::eA() const
        {
            return get_BEptr()->eA();
        }
        
        inline double Info::eB() const
        {
            return get_BEptr()->eB();
        }
        
        inline double Info::mA() const
        {
            return get_BEptr()->mA();
        }
        
        inline double Info::mB() const
        {
            return get_BEptr()->mB();
        }
        
        inline double Info::eCM() const
        {
            return get_BEptr()->eCM();
        }
        
        inline double Info::s() const
        {
            return get_BEptr()->s();
        }
        
        inline bool Info::tooLowPTmin() const
        {
            return get_BEptr()->tooLowPTmin();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::name() const
        {
            return get_BEptr()->name();
        }
        
        inline int Info::code() const
        {
            return get_BEptr()->code();
        }
        
        inline int Info::nFinal() const
        {
            return get_BEptr()->nFinal();
        }
        
        inline bool Info::isResolved() const
        {
            return get_BEptr()->isResolved();
        }
        
        inline bool Info::isDiffractiveA() const
        {
            return get_BEptr()->isDiffractiveA();
        }
        
        inline bool Info::isDiffractiveB() const
        {
            return get_BEptr()->isDiffractiveB();
        }
        
        inline bool Info::isDiffractiveC() const
        {
            return get_BEptr()->isDiffractiveC();
        }
        
        inline bool Info::isNonDiffractive() const
        {
            return get_BEptr()->isNonDiffractive();
        }
        
        inline bool Info::isMinBias() const
        {
            return get_BEptr()->isMinBias();
        }
        
        inline bool Info::isLHA() const
        {
            return get_BEptr()->isLHA();
        }
        
        inline bool Info::atEndOfFile() const
        {
            return get_BEptr()->atEndOfFile();
        }
        
        inline bool Info::hasSub(int i) const
        {
            return get_BEptr()->hasSub(i);
        }
        
        inline bool Info::hasSub() const
        {
            return get_BEptr()->hasSub__BOSS();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::nameSub(int i) const
        {
            return get_BEptr()->nameSub(i);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::nameSub() const
        {
            return get_BEptr()->nameSub__BOSS();
        }
        
        inline int Info::codeSub(int i) const
        {
            return get_BEptr()->codeSub(i);
        }
        
        inline int Info::codeSub() const
        {
            return get_BEptr()->codeSub__BOSS();
        }
        
        inline int Info::nFinalSub(int i) const
        {
            return get_BEptr()->nFinalSub(i);
        }
        
        inline int Info::nFinalSub() const
        {
            return get_BEptr()->nFinalSub__BOSS();
        }
        
        inline int Info::id1(int i) const
        {
            return get_BEptr()->id1(i);
        }
        
        inline int Info::id1() const
        {
            return get_BEptr()->id1__BOSS();
        }
        
        inline int Info::id2(int i) const
        {
            return get_BEptr()->id2(i);
        }
        
        inline int Info::id2() const
        {
            return get_BEptr()->id2__BOSS();
        }
        
        inline double Info::x1(int i) const
        {
            return get_BEptr()->x1(i);
        }
        
        inline double Info::x1() const
        {
            return get_BEptr()->x1__BOSS();
        }
        
        inline double Info::x2(int i) const
        {
            return get_BEptr()->x2(i);
        }
        
        inline double Info::x2() const
        {
            return get_BEptr()->x2__BOSS();
        }
        
        inline double Info::y(int i) const
        {
            return get_BEptr()->y(i);
        }
        
        inline double Info::y() const
        {
            return get_BEptr()->y__BOSS();
        }
        
        inline double Info::tau(int i) const
        {
            return get_BEptr()->tau(i);
        }
        
        inline double Info::tau() const
        {
            return get_BEptr()->tau__BOSS();
        }
        
        inline int Info::id1pdf(int i) const
        {
            return get_BEptr()->id1pdf(i);
        }
        
        inline int Info::id1pdf() const
        {
            return get_BEptr()->id1pdf__BOSS();
        }
        
        inline int Info::id2pdf(int i) const
        {
            return get_BEptr()->id2pdf(i);
        }
        
        inline int Info::id2pdf() const
        {
            return get_BEptr()->id2pdf__BOSS();
        }
        
        inline double Info::x1pdf(int i) const
        {
            return get_BEptr()->x1pdf(i);
        }
        
        inline double Info::x1pdf() const
        {
            return get_BEptr()->x1pdf__BOSS();
        }
        
        inline double Info::x2pdf(int i) const
        {
            return get_BEptr()->x2pdf(i);
        }
        
        inline double Info::x2pdf() const
        {
            return get_BEptr()->x2pdf__BOSS();
        }
        
        inline double Info::pdf1(int i) const
        {
            return get_BEptr()->pdf1(i);
        }
        
        inline double Info::pdf1() const
        {
            return get_BEptr()->pdf1__BOSS();
        }
        
        inline double Info::pdf2(int i) const
        {
            return get_BEptr()->pdf2(i);
        }
        
        inline double Info::pdf2() const
        {
            return get_BEptr()->pdf2__BOSS();
        }
        
        inline double Info::QFac(int i) const
        {
            return get_BEptr()->QFac(i);
        }
        
        inline double Info::QFac() const
        {
            return get_BEptr()->QFac__BOSS();
        }
        
        inline double Info::Q2Fac(int i) const
        {
            return get_BEptr()->Q2Fac(i);
        }
        
        inline double Info::Q2Fac() const
        {
            return get_BEptr()->Q2Fac__BOSS();
        }
        
        inline bool Info::isValence1() const
        {
            return get_BEptr()->isValence1();
        }
        
        inline bool Info::isValence2() const
        {
            return get_BEptr()->isValence2();
        }
        
        inline double Info::alphaS(int i) const
        {
            return get_BEptr()->alphaS(i);
        }
        
        inline double Info::alphaS() const
        {
            return get_BEptr()->alphaS__BOSS();
        }
        
        inline double Info::alphaEM(int i) const
        {
            return get_BEptr()->alphaEM(i);
        }
        
        inline double Info::alphaEM() const
        {
            return get_BEptr()->alphaEM__BOSS();
        }
        
        inline double Info::QRen(int i) const
        {
            return get_BEptr()->QRen(i);
        }
        
        inline double Info::QRen() const
        {
            return get_BEptr()->QRen__BOSS();
        }
        
        inline double Info::Q2Ren(int i) const
        {
            return get_BEptr()->Q2Ren(i);
        }
        
        inline double Info::Q2Ren() const
        {
            return get_BEptr()->Q2Ren__BOSS();
        }
        
        inline double Info::scalup(int i) const
        {
            return get_BEptr()->scalup(i);
        }
        
        inline double Info::scalup() const
        {
            return get_BEptr()->scalup__BOSS();
        }
        
        inline double Info::mHat(int i) const
        {
            return get_BEptr()->mHat(i);
        }
        
        inline double Info::mHat() const
        {
            return get_BEptr()->mHat__BOSS();
        }
        
        inline double Info::sHat(int i) const
        {
            return get_BEptr()->sHat(i);
        }
        
        inline double Info::sHat() const
        {
            return get_BEptr()->sHat__BOSS();
        }
        
        inline double Info::tHat(int i) const
        {
            return get_BEptr()->tHat(i);
        }
        
        inline double Info::tHat() const
        {
            return get_BEptr()->tHat__BOSS();
        }
        
        inline double Info::uHat(int i) const
        {
            return get_BEptr()->uHat(i);
        }
        
        inline double Info::uHat() const
        {
            return get_BEptr()->uHat__BOSS();
        }
        
        inline double Info::pTHat(int i) const
        {
            return get_BEptr()->pTHat(i);
        }
        
        inline double Info::pTHat() const
        {
            return get_BEptr()->pTHat__BOSS();
        }
        
        inline double Info::pT2Hat(int i) const
        {
            return get_BEptr()->pT2Hat(i);
        }
        
        inline double Info::pT2Hat() const
        {
            return get_BEptr()->pT2Hat__BOSS();
        }
        
        inline double Info::m3Hat(int i) const
        {
            return get_BEptr()->m3Hat(i);
        }
        
        inline double Info::m3Hat() const
        {
            return get_BEptr()->m3Hat__BOSS();
        }
        
        inline double Info::m4Hat(int i) const
        {
            return get_BEptr()->m4Hat(i);
        }
        
        inline double Info::m4Hat() const
        {
            return get_BEptr()->m4Hat__BOSS();
        }
        
        inline double Info::thetaHat(int i) const
        {
            return get_BEptr()->thetaHat(i);
        }
        
        inline double Info::thetaHat() const
        {
            return get_BEptr()->thetaHat__BOSS();
        }
        
        inline double Info::phiHat(int i) const
        {
            return get_BEptr()->phiHat(i);
        }
        
        inline double Info::phiHat() const
        {
            return get_BEptr()->phiHat__BOSS();
        }
        
        inline double Info::weight() const
        {
            return get_BEptr()->weight();
        }
        
        inline double Info::weightSum() const
        {
            return get_BEptr()->weightSum();
        }
        
        inline double Info::lhaStrategy() const
        {
            return get_BEptr()->lhaStrategy();
        }
        
        inline int Info::nISR() const
        {
            return get_BEptr()->nISR();
        }
        
        inline int Info::nFSRinProc() const
        {
            return get_BEptr()->nFSRinProc();
        }
        
        inline int Info::nFSRinRes() const
        {
            return get_BEptr()->nFSRinRes();
        }
        
        inline double Info::pTmaxMPI() const
        {
            return get_BEptr()->pTmaxMPI();
        }
        
        inline double Info::pTmaxISR() const
        {
            return get_BEptr()->pTmaxISR();
        }
        
        inline double Info::pTmaxFSR() const
        {
            return get_BEptr()->pTmaxFSR();
        }
        
        inline double Info::pTnow() const
        {
            return get_BEptr()->pTnow();
        }
        
        inline double Info::a0MPI() const
        {
            return get_BEptr()->a0MPI();
        }
        
        inline double Info::bMPI() const
        {
            return get_BEptr()->bMPI();
        }
        
        inline double Info::enhanceMPI() const
        {
            return get_BEptr()->enhanceMPI();
        }
        
        inline double Info::eMPI(int i) const
        {
            return get_BEptr()->eMPI(i);
        }
        
        inline int Info::nMPI() const
        {
            return get_BEptr()->nMPI();
        }
        
        inline int Info::codeMPI(int i) const
        {
            return get_BEptr()->codeMPI(i);
        }
        
        inline double Info::pTMPI(int i) const
        {
            return get_BEptr()->pTMPI(i);
        }
        
        inline int Info::iAMPI(int i) const
        {
            return get_BEptr()->iAMPI(i);
        }
        
        inline int Info::iBMPI(int i) const
        {
            return get_BEptr()->iBMPI(i);
        }
        
        inline ::std::vector<int, std::allocator<int> > Info::codesHard()
        {
            return get_BEptr()->codesHard();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::nameProc(int i)
        {
            return get_BEptr()->nameProc(i);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::nameProc()
        {
            return get_BEptr()->nameProc__BOSS();
        }
        
        inline long int Info::nTried(int i)
        {
            return get_BEptr()->nTried(i);
        }
        
        inline long int Info::nTried()
        {
            return get_BEptr()->nTried__BOSS();
        }
        
        inline long int Info::nSelected(int i)
        {
            return get_BEptr()->nSelected(i);
        }
        
        inline long int Info::nSelected()
        {
            return get_BEptr()->nSelected__BOSS();
        }
        
        inline long int Info::nAccepted(int i)
        {
            return get_BEptr()->nAccepted(i);
        }
        
        inline long int Info::nAccepted()
        {
            return get_BEptr()->nAccepted__BOSS();
        }
        
        inline double Info::sigmaGen(int i)
        {
            return get_BEptr()->sigmaGen(i);
        }
        
        inline double Info::sigmaGen()
        {
            return get_BEptr()->sigmaGen__BOSS();
        }
        
        inline double Info::sigmaErr(int i)
        {
            return get_BEptr()->sigmaErr(i);
        }
        
        inline double Info::sigmaErr()
        {
            return get_BEptr()->sigmaErr__BOSS();
        }
        
        inline int Info::getCounter(int i) const
        {
            return get_BEptr()->getCounter(i);
        }
        
        inline void Info::setCounter(int i, int value)
        {
            get_BEptr()->setCounter(i, value);
        }
        
        inline void Info::setCounter(int i)
        {
            get_BEptr()->setCounter__BOSS(i);
        }
        
        inline void Info::addCounter(int i, int value)
        {
            get_BEptr()->addCounter(i, value);
        }
        
        inline void Info::addCounter(int i)
        {
            get_BEptr()->addCounter__BOSS(i);
        }
        
        inline void Info::errorReset()
        {
            get_BEptr()->errorReset();
        }
        
        inline void Info::errorMsg(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > messageIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > extraIn, bool showAlways, ::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->errorMsg(messageIn, extraIn, showAlways, os);
        }
        
        inline void Info::errorMsg(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > messageIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > extraIn, bool showAlways)
        {
            get_BEptr()->errorMsg__BOSS(messageIn, extraIn, showAlways);
        }
        
        inline void Info::errorMsg(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > messageIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > extraIn)
        {
            get_BEptr()->errorMsg__BOSS(messageIn, extraIn);
        }
        
        inline void Info::errorMsg(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > messageIn)
        {
            get_BEptr()->errorMsg__BOSS(messageIn);
        }
        
        inline int Info::errorTotalNumber()
        {
            return get_BEptr()->errorTotalNumber();
        }
        
        inline void Info::errorStatistics(::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->errorStatistics(os);
        }
        
        inline void Info::errorStatistics()
        {
            get_BEptr()->errorStatistics__BOSS();
        }
        
        inline void Info::setTooLowPTmin(bool lowPTminIn)
        {
            get_BEptr()->setTooLowPTmin(lowPTminIn);
        }
        
        inline void Info::setValence(bool isVal1In, bool isVal2In)
        {
            get_BEptr()->setValence(isVal1In, isVal2In);
        }
        
        inline void Info::hasHistory(bool hasHistoryIn)
        {
            get_BEptr()->hasHistory(hasHistoryIn);
        }
        
        inline bool Info::hasHistory()
        {
            return get_BEptr()->hasHistory();
        }
        
        inline void Info::zNowISR(double zNowIn)
        {
            get_BEptr()->zNowISR(zNowIn);
        }
        
        inline double Info::zNowISR()
        {
            return get_BEptr()->zNowISR();
        }
        
        inline void Info::pT2NowISR(double pT2NowIn)
        {
            get_BEptr()->pT2NowISR(pT2NowIn);
        }
        
        inline double Info::pT2NowISR()
        {
            return get_BEptr()->pT2NowISR();
        }
        
        inline double Info::getWeightCKKWL() const
        {
            return get_BEptr()->getWeightCKKWL();
        }
        
        inline void Info::setWeightCKKWL(double weightIn)
        {
            get_BEptr()->setWeightCKKWL(weightIn);
        }
        
        inline double Info::mergingWeight() const
        {
            return get_BEptr()->mergingWeight();
        }
        
        inline double Info::mergingWeightNLO() const
        {
            return get_BEptr()->mergingWeightNLO();
        }
        
        inline double Info::getWeightFIRST() const
        {
            return get_BEptr()->getWeightFIRST();
        }
        
        inline void Info::setWeightFIRST(double weightIn)
        {
            get_BEptr()->setWeightFIRST(weightIn);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::header(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& key)
        {
            return get_BEptr()->header(key);
        }
        
        inline ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > Info::headerKeys()
        {
            return get_BEptr()->headerKeys();
        }
        
        inline int Info::nProcessesLHEF()
        {
            return get_BEptr()->nProcessesLHEF();
        }
        
        inline double Info::sigmaLHEF(int iProcess)
        {
            return get_BEptr()->sigmaLHEF(iProcess);
        }
        
        inline void Info::setLHEF3InitInfo()
        {
            get_BEptr()->setLHEF3InitInfo();
        }
        
        inline void Info::setLHEF3EventInfo()
        {
            get_BEptr()->setLHEF3EventInfo();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getEventAttribute(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key, bool doRemoveWhitespace)
        {
            return get_BEptr()->getEventAttribute(key, doRemoveWhitespace);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getEventAttribute(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key)
        {
            return get_BEptr()->getEventAttribute__BOSS(key);
        }
        
        inline int Info::LHEFversion()
        {
            return get_BEptr()->LHEFversion();
        }
        
        inline unsigned int Info::getInitrwgtSize()
        {
            return get_BEptr()->getInitrwgtSize();
        }
        
        inline unsigned int Info::getGeneratorSize()
        {
            return get_BEptr()->getGeneratorSize();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getGeneratorValue(unsigned int n)
        {
            return get_BEptr()->getGeneratorValue(n);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getGeneratorValue()
        {
            return get_BEptr()->getGeneratorValue__BOSS();
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getGeneratorAttribute(unsigned int n, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key, bool doRemoveWhitespace)
        {
            return get_BEptr()->getGeneratorAttribute(n, key, doRemoveWhitespace);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getGeneratorAttribute(unsigned int n, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key)
        {
            return get_BEptr()->getGeneratorAttribute__BOSS(n, key);
        }
        
        inline unsigned int Info::getWeightsDetailedSize()
        {
            return get_BEptr()->getWeightsDetailedSize();
        }
        
        inline double Info::getWeightsDetailedValue(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > n)
        {
            return get_BEptr()->getWeightsDetailedValue(n);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getWeightsDetailedAttribute(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > n, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key, bool doRemoveWhitespace)
        {
            return get_BEptr()->getWeightsDetailedAttribute(n, key, doRemoveWhitespace);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getWeightsDetailedAttribute(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > n, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key)
        {
            return get_BEptr()->getWeightsDetailedAttribute__BOSS(n, key);
        }
        
        inline unsigned int Info::getWeightsCompressedSize()
        {
            return get_BEptr()->getWeightsCompressedSize();
        }
        
        inline double Info::getWeightsCompressedValue(unsigned int n)
        {
            return get_BEptr()->getWeightsCompressedValue(n);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getWeightsCompressedAttribute(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key, bool doRemoveWhitespace)
        {
            return get_BEptr()->getWeightsCompressedAttribute(key, doRemoveWhitespace);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getWeightsCompressedAttribute(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key)
        {
            return get_BEptr()->getWeightsCompressedAttribute__BOSS(key);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getScalesValue(bool doRemoveWhitespace)
        {
            return get_BEptr()->getScalesValue(doRemoveWhitespace);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > Info::getScalesValue()
        {
            return get_BEptr()->getScalesValue__BOSS();
        }
        
        inline double Info::getScalesAttribute(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > key)
        {
            return get_BEptr()->getScalesAttribute(key);
        }
        
        inline void Info::setHeader(const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& key, const ::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& val)
        {
            get_BEptr()->setHeader(key, val);
        }
        
        inline void Info::setAbortPartonLevel(bool abortIn)
        {
            get_BEptr()->setAbortPartonLevel(abortIn);
        }
        
        inline bool Info::getAbortPartonLevel()
        {
            return get_BEptr()->getAbortPartonLevel();
        }
        
        inline bool Info::hasUnresolvedBeams() const
        {
            return get_BEptr()->hasUnresolvedBeams();
        }
        
        inline bool Info::hasPomPsystem() const
        {
            return get_BEptr()->hasPomPsystem();
        }
        
        inline bool Info::isHardDiffractive() const
        {
            return get_BEptr()->isHardDiffractive();
        }
        
        inline bool Info::isHardDiffractiveA() const
        {
            return get_BEptr()->isHardDiffractiveA();
        }
        
        inline bool Info::isHardDiffractiveB() const
        {
            return get_BEptr()->isHardDiffractiveB();
        }
        
        inline double Info::xPomeronA() const
        {
            return get_BEptr()->xPomeronA();
        }
        
        inline double Info::xPomeronB() const
        {
            return get_BEptr()->xPomeronB();
        }
        
        inline double Info::tPomeronA() const
        {
            return get_BEptr()->tPomeronA();
        }
        
        inline double Info::tPomeronB() const
        {
            return get_BEptr()->tPomeronB();
        }
        
        
        // Wrappers for original constructors: 
        inline Info::Info() :
            WrapperBase(__factory0()),
            LHEFversionSave( get_BEptr()->LHEFversionSave_ref__BOSS()),
            sigmaLHEFSave( get_BEptr()->sigmaLHEFSave_ref__BOSS()),
            eventAttributes( get_BEptr()->eventAttributes_ref__BOSS()),
            weights_detailed( get_BEptr()->weights_detailed_ref__BOSS()),
            weights_compressed( get_BEptr()->weights_compressed_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Info::Info(Abstract_Info* in) :
            WrapperBase(in),
            LHEFversionSave( get_BEptr()->LHEFversionSave_ref__BOSS()),
            sigmaLHEFSave( get_BEptr()->sigmaLHEFSave_ref__BOSS()),
            eventAttributes( get_BEptr()->eventAttributes_ref__BOSS()),
            weights_detailed( get_BEptr()->weights_detailed_ref__BOSS()),
            weights_compressed( get_BEptr()->weights_compressed_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Info::Info(const Info& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            LHEFversionSave( get_BEptr()->LHEFversionSave_ref__BOSS()),
            sigmaLHEFSave( get_BEptr()->sigmaLHEFSave_ref__BOSS()),
            eventAttributes( get_BEptr()->eventAttributes_ref__BOSS()),
            weights_detailed( get_BEptr()->weights_detailed_ref__BOSS()),
            weights_compressed( get_BEptr()->weights_compressed_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Info& Info::operator=(const Info& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Info::~Info()
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
        inline Abstract_Info* Pythia8::Info::get_BEptr() const
        {
            return dynamic_cast<Abstract_Info*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Info_def_Pythia_8_212_h__ */
