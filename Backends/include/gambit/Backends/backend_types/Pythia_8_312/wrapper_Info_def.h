#ifndef __wrapper_Info_def_Pythia_8_312_h__
#define __wrapper_Info_def_Pythia_8_312_h__

#include <string>
#include <vector>
#include <map>
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_CoupSUSY_decl.h"
#include "wrapper_SigmaTotal_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Info::list() const
        {
            get_BEptr()->list();
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
        
        inline ::std::string Info::name() const
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
        
        inline bool Info::isElastic() const
        {
            return get_BEptr()->isElastic();
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
        
        inline ::std::string Info::nameSub(int i) const
        {
            return get_BEptr()->nameSub(i);
        }
        
        inline ::std::string Info::nameSub() const
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
        
        inline double Info::xGammaA() const
        {
            return get_BEptr()->xGammaA();
        }
        
        inline double Info::xGammaB() const
        {
            return get_BEptr()->xGammaB();
        }
        
        inline double Info::Q2GammaA() const
        {
            return get_BEptr()->Q2GammaA();
        }
        
        inline double Info::Q2GammaB() const
        {
            return get_BEptr()->Q2GammaB();
        }
        
        inline double Info::eCMsub() const
        {
            return get_BEptr()->eCMsub();
        }
        
        inline double Info::thetaScatLepA() const
        {
            return get_BEptr()->thetaScatLepA();
        }
        
        inline double Info::thetaScatLepB() const
        {
            return get_BEptr()->thetaScatLepB();
        }
        
        inline double Info::sHatNew() const
        {
            return get_BEptr()->sHatNew();
        }
        
        inline int Info::photonMode() const
        {
            return get_BEptr()->photonMode();
        }
        
        inline bool Info::isVMDstateA() const
        {
            return get_BEptr()->isVMDstateA();
        }
        
        inline bool Info::isVMDstateB() const
        {
            return get_BEptr()->isVMDstateB();
        }
        
        inline int Info::idVMDA() const
        {
            return get_BEptr()->idVMDA();
        }
        
        inline int Info::idVMDB() const
        {
            return get_BEptr()->idVMDB();
        }
        
        inline double Info::mVMDA() const
        {
            return get_BEptr()->mVMDA();
        }
        
        inline double Info::mVMDB() const
        {
            return get_BEptr()->mVMDB();
        }
        
        inline double Info::scaleVMDA() const
        {
            return get_BEptr()->scaleVMDA();
        }
        
        inline double Info::scaleVMDB() const
        {
            return get_BEptr()->scaleVMDB();
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
        
        inline double Info::weight(int i) const
        {
            return get_BEptr()->weight(i);
        }
        
        inline double Info::weight() const
        {
            return get_BEptr()->weight__BOSS();
        }
        
        inline double Info::weightSum() const
        {
            return get_BEptr()->weightSum();
        }
        
        inline double Info::lhaStrategy() const
        {
            return get_BEptr()->lhaStrategy();
        }
        
        inline int Info::nWeights() const
        {
            return get_BEptr()->nWeights();
        }
        
        inline ::std::string Info::weightLabel(int iWgt) const
        {
            return get_BEptr()->weightLabel(iWgt);
        }
        
        inline int Info::nWeightGroups() const
        {
            return get_BEptr()->nWeightGroups();
        }
        
        inline ::std::string Info::getGroupName(int iGN) const
        {
            return get_BEptr()->getGroupName(iGN);
        }
        
        inline double Info::getGroupWeight(int iGW) const
        {
            return get_BEptr()->getGroupWeight(iGW);
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
        
        inline double Info::enhanceMPIavg() const
        {
            return get_BEptr()->enhanceMPIavg();
        }
        
        inline double Info::eMPI(int i) const
        {
            return get_BEptr()->eMPI(i);
        }
        
        inline double Info::bMPIold() const
        {
            return get_BEptr()->bMPIold();
        }
        
        inline double Info::enhanceMPIold() const
        {
            return get_BEptr()->enhanceMPIold();
        }
        
        inline double Info::enhanceMPIoldavg() const
        {
            return get_BEptr()->enhanceMPIoldavg();
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
        
        inline ::std::vector<int> Info::codesHard() const
        {
            return get_BEptr()->codesHard();
        }
        
        inline ::std::string Info::nameProc(int i) const
        {
            return get_BEptr()->nameProc(i);
        }
        
        inline ::std::string Info::nameProc() const
        {
            return get_BEptr()->nameProc__BOSS();
        }
        
        inline long int Info::nTried(int i) const
        {
            return get_BEptr()->nTried(i);
        }
        
        inline long int Info::nTried() const
        {
            return get_BEptr()->nTried__BOSS();
        }
        
        inline long int Info::nSelected(int i) const
        {
            return get_BEptr()->nSelected(i);
        }
        
        inline long int Info::nSelected() const
        {
            return get_BEptr()->nSelected__BOSS();
        }
        
        inline long int Info::nAccepted(int i) const
        {
            return get_BEptr()->nAccepted(i);
        }
        
        inline long int Info::nAccepted() const
        {
            return get_BEptr()->nAccepted__BOSS();
        }
        
        inline double Info::sigmaGen(int i) const
        {
            return get_BEptr()->sigmaGen(i);
        }
        
        inline double Info::sigmaGen() const
        {
            return get_BEptr()->sigmaGen__BOSS();
        }
        
        inline double Info::sigmaErr(int i) const
        {
            return get_BEptr()->sigmaErr(i);
        }
        
        inline double Info::sigmaErr() const
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
        
        inline double Info::mergingWeight(int i) const
        {
            return get_BEptr()->mergingWeight(i);
        }
        
        inline double Info::mergingWeight() const
        {
            return get_BEptr()->mergingWeight__BOSS();
        }
        
        inline double Info::mergingWeightNLO(int i) const
        {
            return get_BEptr()->mergingWeightNLO(i);
        }
        
        inline double Info::mergingWeightNLO() const
        {
            return get_BEptr()->mergingWeightNLO__BOSS();
        }
        
        inline ::std::string Info::header(const std::string& key) const
        {
            return get_BEptr()->header(key);
        }
        
        inline ::std::vector<std::string> Info::headerKeys() const
        {
            return get_BEptr()->headerKeys();
        }
        
        inline int Info::nProcessesLHEF() const
        {
            return get_BEptr()->nProcessesLHEF();
        }
        
        inline double Info::sigmaLHEF(int iProcess) const
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
        
        inline ::std::string Info::getEventAttribute(std::string key, bool doRemoveWhitespace) const
        {
            return get_BEptr()->getEventAttribute(key, doRemoveWhitespace);
        }
        
        inline ::std::string Info::getEventAttribute(std::string key) const
        {
            return get_BEptr()->getEventAttribute__BOSS(key);
        }
        
        inline void Info::setEventAttribute(std::string key, std::string value, bool doOverwrite)
        {
            get_BEptr()->setEventAttribute(key, value, doOverwrite);
        }
        
        inline void Info::setEventAttribute(std::string key, std::string value)
        {
            get_BEptr()->setEventAttribute__BOSS(key, value);
        }
        
        inline int Info::LHEFversion() const
        {
            return get_BEptr()->LHEFversion();
        }
        
        inline unsigned int Info::getInitrwgtSize() const
        {
            return get_BEptr()->getInitrwgtSize();
        }
        
        inline unsigned int Info::getGeneratorSize() const
        {
            return get_BEptr()->getGeneratorSize();
        }
        
        inline ::std::string Info::getGeneratorValue(unsigned int n) const
        {
            return get_BEptr()->getGeneratorValue(n);
        }
        
        inline ::std::string Info::getGeneratorValue() const
        {
            return get_BEptr()->getGeneratorValue__BOSS();
        }
        
        inline ::std::string Info::getGeneratorAttribute(unsigned int n, std::string key, bool doRemoveWhitespace) const
        {
            return get_BEptr()->getGeneratorAttribute(n, key, doRemoveWhitespace);
        }
        
        inline ::std::string Info::getGeneratorAttribute(unsigned int n, std::string key) const
        {
            return get_BEptr()->getGeneratorAttribute__BOSS(n, key);
        }
        
        inline unsigned int Info::getWeightsDetailedSize() const
        {
            return get_BEptr()->getWeightsDetailedSize();
        }
        
        inline double Info::getWeightsDetailedValue(std::string n) const
        {
            return get_BEptr()->getWeightsDetailedValue(n);
        }
        
        inline ::std::string Info::getWeightsDetailedAttribute(std::string n, std::string key, bool doRemoveWhitespace) const
        {
            return get_BEptr()->getWeightsDetailedAttribute(n, key, doRemoveWhitespace);
        }
        
        inline ::std::string Info::getWeightsDetailedAttribute(std::string n, std::string key) const
        {
            return get_BEptr()->getWeightsDetailedAttribute__BOSS(n, key);
        }
        
        inline unsigned int Info::getWeightsCompressedSize() const
        {
            return get_BEptr()->getWeightsCompressedSize();
        }
        
        inline double Info::getWeightsCompressedValue(unsigned int n) const
        {
            return get_BEptr()->getWeightsCompressedValue(n);
        }
        
        inline ::std::string Info::getWeightsCompressedAttribute(std::string key, bool doRemoveWhitespace) const
        {
            return get_BEptr()->getWeightsCompressedAttribute(key, doRemoveWhitespace);
        }
        
        inline ::std::string Info::getWeightsCompressedAttribute(std::string key) const
        {
            return get_BEptr()->getWeightsCompressedAttribute__BOSS(key);
        }
        
        inline ::std::string Info::getScalesValue(bool doRemoveWhitespace) const
        {
            return get_BEptr()->getScalesValue(doRemoveWhitespace);
        }
        
        inline ::std::string Info::getScalesValue() const
        {
            return get_BEptr()->getScalesValue__BOSS();
        }
        
        inline double Info::getScalesAttribute(std::string key) const
        {
            return get_BEptr()->getScalesAttribute(key);
        }
        
        inline ::std::string Info::getHeaderBlock() const
        {
            return get_BEptr()->getHeaderBlock();
        }
        
        inline ::std::string Info::getEventComments() const
        {
            return get_BEptr()->getEventComments();
        }
        
        inline void Info::setHeader(const std::string& key, const std::string& val)
        {
            get_BEptr()->setHeader(key, val);
        }
        
        inline void Info::setAbortPartonLevel(bool abortIn)
        {
            get_BEptr()->setAbortPartonLevel(abortIn);
        }
        
        inline bool Info::getAbortPartonLevel() const
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
        
        inline ::std::vector<int> Info::getWeakModes() const
        {
            return get_BEptr()->getWeakModes();
        }
        
        inline ::std::vector<std::pair<int, int>> Info::getWeakDipoles() const
        {
            return get_BEptr()->getWeakDipoles();
        }
        
        inline ::std::vector<int> Info::getWeak2to2lines() const
        {
            return get_BEptr()->getWeak2to2lines();
        }
        
        inline void Info::setWeakModes(std::vector<int> weakModesIn)
        {
            get_BEptr()->setWeakModes(weakModesIn);
        }
        
        inline void Info::setWeakDipoles(std::vector<std::pair<int, int>> weakDipolesIn)
        {
            get_BEptr()->setWeakDipoles(weakDipolesIn);
        }
        
        inline void Info::setWeak2to2lines(std::vector<int> weak2to2linesIn)
        {
            get_BEptr()->setWeak2to2lines(weak2to2linesIn);
        }
        
        inline void Info::setOniumShower(bool oniumShowerIn)
        {
            get_BEptr()->setOniumShower(oniumShowerIn);
        }
        
        inline bool Info::getOniumShower() const
        {
            return get_BEptr()->getOniumShower();
        }
        
        inline void Info::setBeamIDs(int idAin, int idBin)
        {
            get_BEptr()->setBeamIDs(idAin, idBin);
        }
        
        inline void Info::setBeamA(int idAin, double pzAin, double eAin, double mAin)
        {
            get_BEptr()->setBeamA(idAin, pzAin, eAin, mAin);
        }
        
        inline void Info::setBeamB(int idBin, double pzBin, double eBin, double mBin)
        {
            get_BEptr()->setBeamB(idBin, pzBin, eBin, mBin);
        }
        
        inline void Info::setECM(double eCMin)
        {
            get_BEptr()->setECM(eCMin);
        }
        
        inline void Info::setX1Gamma(double x1GammaIn)
        {
            get_BEptr()->setX1Gamma(x1GammaIn);
        }
        
        inline void Info::setX2Gamma(double x2GammaIn)
        {
            get_BEptr()->setX2Gamma(x2GammaIn);
        }
        
        inline void Info::setQ2Gamma1(double Q2gammaIn)
        {
            get_BEptr()->setQ2Gamma1(Q2gammaIn);
        }
        
        inline void Info::setQ2Gamma2(double Q2gammaIn)
        {
            get_BEptr()->setQ2Gamma2(Q2gammaIn);
        }
        
        inline void Info::setTheta1(double theta1In)
        {
            get_BEptr()->setTheta1(theta1In);
        }
        
        inline void Info::setTheta2(double theta2In)
        {
            get_BEptr()->setTheta2(theta2In);
        }
        
        inline void Info::setECMsub(double eCMsubIn)
        {
            get_BEptr()->setECMsub(eCMsubIn);
        }
        
        inline void Info::setsHatNew(double sHatNewIn)
        {
            get_BEptr()->setsHatNew(sHatNewIn);
        }
        
        inline void Info::setGammaMode(double gammaModeIn)
        {
            get_BEptr()->setGammaMode(gammaModeIn);
        }
        
        inline void Info::setVMDstateA(bool isVMDAIn, int idAIn, double mAIn, double scaleAIn)
        {
            get_BEptr()->setVMDstateA(isVMDAIn, idAIn, mAIn, scaleAIn);
        }
        
        inline void Info::setVMDstateB(bool isVMDBIn, int idBIn, double mBIn, double scaleBIn)
        {
            get_BEptr()->setVMDstateB(isVMDBIn, idBIn, mBIn, scaleBIn);
        }
        
        inline void Info::clear()
        {
            get_BEptr()->clear();
        }
        
        inline int Info::sizeMPIarrays() const
        {
            return get_BEptr()->sizeMPIarrays();
        }
        
        inline void Info::resizeMPIarrays(int newSize)
        {
            get_BEptr()->resizeMPIarrays(newSize);
        }
        
        inline void Info::setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin, bool isDiffractiveBin, bool isDiffractiveCin, bool isLHAin)
        {
            get_BEptr()->setType(nameIn, codeIn, nFinalIn, isNonDiffIn, isResolvedIn, isDiffractiveAin, isDiffractiveBin, isDiffractiveCin, isLHAin);
        }
        
        inline void Info::setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin, bool isDiffractiveBin, bool isDiffractiveCin)
        {
            get_BEptr()->setType__BOSS(nameIn, codeIn, nFinalIn, isNonDiffIn, isResolvedIn, isDiffractiveAin, isDiffractiveBin, isDiffractiveCin);
        }
        
        inline void Info::setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin, bool isDiffractiveBin)
        {
            get_BEptr()->setType__BOSS(nameIn, codeIn, nFinalIn, isNonDiffIn, isResolvedIn, isDiffractiveAin, isDiffractiveBin);
        }
        
        inline void Info::setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin)
        {
            get_BEptr()->setType__BOSS(nameIn, codeIn, nFinalIn, isNonDiffIn, isResolvedIn, isDiffractiveAin);
        }
        
        inline void Info::setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn)
        {
            get_BEptr()->setType__BOSS(nameIn, codeIn, nFinalIn, isNonDiffIn, isResolvedIn);
        }
        
        inline void Info::setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn)
        {
            get_BEptr()->setType__BOSS(nameIn, codeIn, nFinalIn, isNonDiffIn);
        }
        
        inline void Info::setType(std::string nameIn, int codeIn, int nFinalIn)
        {
            get_BEptr()->setType__BOSS(nameIn, codeIn, nFinalIn);
        }
        
        inline void Info::setSubType(int iDS, std::string nameSubIn, int codeSubIn, int nFinalSubIn)
        {
            get_BEptr()->setSubType(iDS, nameSubIn, codeSubIn, nFinalSubIn);
        }
        
        inline void Info::setPDFalpha(int iDS, int id1pdfIn, int id2pdfIn, double x1pdfIn, double x2pdfIn, double pdf1In, double pdf2In, double Q2FacIn, double alphaEMIn, double alphaSIn, double Q2RenIn, double scalupIn)
        {
            get_BEptr()->setPDFalpha(iDS, id1pdfIn, id2pdfIn, x1pdfIn, x2pdfIn, pdf1In, pdf2In, Q2FacIn, alphaEMIn, alphaSIn, Q2RenIn, scalupIn);
        }
        
        inline void Info::setScalup(int iDS, double scalupIn)
        {
            get_BEptr()->setScalup(iDS, scalupIn);
        }
        
        inline void Info::setKin(int iDS, int id1In, int id2In, double x1In, double x2In, double sHatIn, double tHatIn, double uHatIn, double pTHatIn, double m3HatIn, double m4HatIn, double thetaHatIn, double phiHatIn)
        {
            get_BEptr()->setKin(iDS, id1In, id2In, x1In, x2In, sHatIn, tHatIn, uHatIn, pTHatIn, m3HatIn, m4HatIn, thetaHatIn, phiHatIn);
        }
        
        inline void Info::setTypeMPI(int codeMPIIn, double pTMPIIn, int iAMPIIn, int iBMPIIn, double eMPIIn)
        {
            get_BEptr()->setTypeMPI(codeMPIIn, pTMPIIn, iAMPIIn, iBMPIIn, eMPIIn);
        }
        
        inline void Info::setTypeMPI(int codeMPIIn, double pTMPIIn, int iAMPIIn, int iBMPIIn)
        {
            get_BEptr()->setTypeMPI__BOSS(codeMPIIn, pTMPIIn, iAMPIIn, iBMPIIn);
        }
        
        inline void Info::setTypeMPI(int codeMPIIn, double pTMPIIn, int iAMPIIn)
        {
            get_BEptr()->setTypeMPI__BOSS(codeMPIIn, pTMPIIn, iAMPIIn);
        }
        
        inline void Info::setTypeMPI(int codeMPIIn, double pTMPIIn)
        {
            get_BEptr()->setTypeMPI__BOSS(codeMPIIn, pTMPIIn);
        }
        
        inline void Info::sigmaReset()
        {
            get_BEptr()->sigmaReset();
        }
        
        inline void Info::setSigma(int i, std::string procNameIn, long int nTryIn, long int nSelIn, long int nAccIn, double sigGenIn, double sigErrIn, double wtAccSumIn)
        {
            get_BEptr()->setSigma(i, procNameIn, nTryIn, nSelIn, nAccIn, sigGenIn, sigErrIn, wtAccSumIn);
        }
        
        inline void Info::addSigma(int i, long int nTryIn, long int nSelIn, long int nAccIn, double sigGenIn, double sigErrIn)
        {
            get_BEptr()->addSigma(i, nTryIn, nSelIn, nAccIn, sigGenIn, sigErrIn);
        }
        
        inline void Info::setImpact(double bMPIIn, double enhanceMPIIn, double enhanceMPIavgIn, bool bIsSetIn, bool pushBack)
        {
            get_BEptr()->setImpact(bMPIIn, enhanceMPIIn, enhanceMPIavgIn, bIsSetIn, pushBack);
        }
        
        inline void Info::setImpact(double bMPIIn, double enhanceMPIIn, double enhanceMPIavgIn, bool bIsSetIn)
        {
            get_BEptr()->setImpact__BOSS(bMPIIn, enhanceMPIIn, enhanceMPIavgIn, bIsSetIn);
        }
        
        inline void Info::setImpact(double bMPIIn, double enhanceMPIIn, double enhanceMPIavgIn)
        {
            get_BEptr()->setImpact__BOSS(bMPIIn, enhanceMPIIn, enhanceMPIavgIn);
        }
        
        inline void Info::setPartEvolved(int nMPIIn, int nISRIn)
        {
            get_BEptr()->setPartEvolved(nMPIIn, nISRIn);
        }
        
        inline void Info::setEvolution(double pTmaxMPIIn, double pTmaxISRIn, double pTmaxFSRIn, int nMPIIn, int nISRIn, int nFSRinProcIn, int nFSRinResIn)
        {
            get_BEptr()->setEvolution(pTmaxMPIIn, pTmaxISRIn, pTmaxFSRIn, nMPIIn, nISRIn, nFSRinProcIn, nFSRinResIn);
        }
        
        inline void Info::setPTnow(double pTnowIn)
        {
            get_BEptr()->setPTnow(pTnowIn);
        }
        
        inline void Info::seta0MPI(double a0MPIin)
        {
            get_BEptr()->seta0MPI(a0MPIin);
        }
        
        inline void Info::setEndOfFile(bool atEOFin)
        {
            get_BEptr()->setEndOfFile(atEOFin);
        }
        
        inline void Info::setWeight(double weightIn, int lhaStrategyIn)
        {
            get_BEptr()->setWeight(weightIn, lhaStrategyIn);
        }
        
        inline void Info::setIsResolved(bool isResIn)
        {
            get_BEptr()->setIsResolved(isResIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn, double xPomBIn, double tPomAIn, double tPomBIn)
        {
            get_BEptr()->setHardDiff(hasUnresBeamsIn, hasPomPsysIn, isHardDiffAIn, isHardDiffBIn, xPomAIn, xPomBIn, tPomAIn, tPomBIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn, double xPomBIn, double tPomAIn)
        {
            get_BEptr()->setHardDiff__BOSS(hasUnresBeamsIn, hasPomPsysIn, isHardDiffAIn, isHardDiffBIn, xPomAIn, xPomBIn, tPomAIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn, double xPomBIn)
        {
            get_BEptr()->setHardDiff__BOSS(hasUnresBeamsIn, hasPomPsysIn, isHardDiffAIn, isHardDiffBIn, xPomAIn, xPomBIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn)
        {
            get_BEptr()->setHardDiff__BOSS(hasUnresBeamsIn, hasPomPsysIn, isHardDiffAIn, isHardDiffBIn, xPomAIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn)
        {
            get_BEptr()->setHardDiff__BOSS(hasUnresBeamsIn, hasPomPsysIn, isHardDiffAIn, isHardDiffBIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn)
        {
            get_BEptr()->setHardDiff__BOSS(hasUnresBeamsIn, hasPomPsysIn, isHardDiffAIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn)
        {
            get_BEptr()->setHardDiff__BOSS(hasUnresBeamsIn, hasPomPsysIn);
        }
        
        inline void Info::setHardDiff(bool hasUnresBeamsIn)
        {
            get_BEptr()->setHardDiff__BOSS(hasUnresBeamsIn);
        }
        
        inline void Info::setHardDiff()
        {
            get_BEptr()->setHardDiff__BOSS();
        }
        
        inline void Info::reassignDiffSystem(int iDSold, int iDSnew)
        {
            get_BEptr()->reassignDiffSystem(iDSold, iDSnew);
        }
        
        inline void Info::setHasUnresolvedBeams(bool hasUnresBeamsIn)
        {
            get_BEptr()->setHasUnresolvedBeams(hasUnresBeamsIn);
        }
        
        inline void Info::setHasPomPsystem(bool hasPomPsysIn)
        {
            get_BEptr()->setHasPomPsystem(hasPomPsysIn);
        }
        
        inline int Info::numberOfWeights() const
        {
            return get_BEptr()->numberOfWeights();
        }
        
        inline double Info::weightValueByIndex(int key) const
        {
            return get_BEptr()->weightValueByIndex(key);
        }
        
        inline double Info::weightValueByIndex() const
        {
            return get_BEptr()->weightValueByIndex__BOSS();
        }
        
        inline ::std::string Info::weightNameByIndex(int key) const
        {
            return get_BEptr()->weightNameByIndex(key);
        }
        
        inline ::std::string Info::weightNameByIndex() const
        {
            return get_BEptr()->weightNameByIndex__BOSS();
        }
        
        inline ::std::vector<double> Info::weightValueVector() const
        {
            return get_BEptr()->weightValueVector();
        }
        
        inline ::std::vector<std::string> Info::weightNameVector() const
        {
            return get_BEptr()->weightNameVector();
        }
        
        
        // Wrappers for original constructors: 
        inline Info::Info() :
            WrapperBase(__factory0()),
            LHEFversionSave( get_BEptr()->LHEFversionSave_ref__BOSS()),
            sigmaLHEFSave( get_BEptr()->sigmaLHEFSave_ref__BOSS()),
            hasOwnEventAttributes( get_BEptr()->hasOwnEventAttributes_ref__BOSS()),
            eventAttributes( get_BEptr()->eventAttributes_ref__BOSS()),
            weights_detailed( get_BEptr()->weights_detailed_ref__BOSS()),
            weights_compressed( get_BEptr()->weights_compressed_ref__BOSS()),
            weights_detailed_vector( get_BEptr()->weights_detailed_vector_ref__BOSS()),
            eventWeightLHEF( get_BEptr()->eventWeightLHEF_ref__BOSS()),
            CONVERTMB2PB( get_BEptr()->CONVERTMB2PB_ref__BOSS()),
            idASave( get_BEptr()->idASave_ref__BOSS()),
            idBSave( get_BEptr()->idBSave_ref__BOSS()),
            pzASave( get_BEptr()->pzASave_ref__BOSS()),
            eASave( get_BEptr()->eASave_ref__BOSS()),
            mASave( get_BEptr()->mASave_ref__BOSS()),
            pzBSave( get_BEptr()->pzBSave_ref__BOSS()),
            eBSave( get_BEptr()->eBSave_ref__BOSS()),
            mBSave( get_BEptr()->mBSave_ref__BOSS()),
            eCMSave( get_BEptr()->eCMSave_ref__BOSS()),
            sSave( get_BEptr()->sSave_ref__BOSS()),
            lowPTmin( get_BEptr()->lowPTmin_ref__BOSS()),
            nTry( get_BEptr()->nTry_ref__BOSS()),
            nSel( get_BEptr()->nSel_ref__BOSS()),
            nAcc( get_BEptr()->nAcc_ref__BOSS()),
            sigGen( get_BEptr()->sigGen_ref__BOSS()),
            sigErr( get_BEptr()->sigErr_ref__BOSS()),
            wtAccSum( get_BEptr()->wtAccSum_ref__BOSS()),
            procNameM( get_BEptr()->procNameM_ref__BOSS()),
            nTryM( get_BEptr()->nTryM_ref__BOSS()),
            nSelM( get_BEptr()->nSelM_ref__BOSS()),
            nAccM( get_BEptr()->nAccM_ref__BOSS()),
            sigGenM( get_BEptr()->sigGenM_ref__BOSS()),
            sigErrM( get_BEptr()->sigErrM_ref__BOSS()),
            lhaStrategySave( get_BEptr()->lhaStrategySave_ref__BOSS()),
            a0MPISave( get_BEptr()->a0MPISave_ref__BOSS()),
            isRes( get_BEptr()->isRes_ref__BOSS()),
            isDiffA( get_BEptr()->isDiffA_ref__BOSS()),
            isDiffB( get_BEptr()->isDiffB_ref__BOSS()),
            isDiffC( get_BEptr()->isDiffC_ref__BOSS()),
            isND( get_BEptr()->isND_ref__BOSS()),
            isLH( get_BEptr()->isLH_ref__BOSS()),
            hasSubSave( get_BEptr()->hasSubSave_ref__BOSS()),
            bIsSet( get_BEptr()->bIsSet_ref__BOSS()),
            evolIsSet( get_BEptr()->evolIsSet_ref__BOSS()),
            atEOF( get_BEptr()->atEOF_ref__BOSS()),
            isVal1( get_BEptr()->isVal1_ref__BOSS()),
            isVal2( get_BEptr()->isVal2_ref__BOSS()),
            hasHistorySave( get_BEptr()->hasHistorySave_ref__BOSS()),
            abortPartonLevel( get_BEptr()->abortPartonLevel_ref__BOSS()),
            isHardDiffA( get_BEptr()->isHardDiffA_ref__BOSS()),
            isHardDiffB( get_BEptr()->isHardDiffB_ref__BOSS()),
            hasUnresBeams( get_BEptr()->hasUnresBeams_ref__BOSS()),
            hasPomPsys( get_BEptr()->hasPomPsys_ref__BOSS()),
            codeSave( get_BEptr()->codeSave_ref__BOSS()),
            codeSubSave( get_BEptr()->codeSubSave_ref__BOSS()),
            nFinalSave( get_BEptr()->nFinalSave_ref__BOSS()),
            nFinalSubSave( get_BEptr()->nFinalSubSave_ref__BOSS()),
            nTotal( get_BEptr()->nTotal_ref__BOSS()),
            id1Save( get_BEptr()->id1Save_ref__BOSS()),
            id2Save( get_BEptr()->id2Save_ref__BOSS()),
            id1pdfSave( get_BEptr()->id1pdfSave_ref__BOSS()),
            id2pdfSave( get_BEptr()->id2pdfSave_ref__BOSS()),
            nMPISave( get_BEptr()->nMPISave_ref__BOSS()),
            nISRSave( get_BEptr()->nISRSave_ref__BOSS()),
            nFSRinProcSave( get_BEptr()->nFSRinProcSave_ref__BOSS()),
            nFSRinResSave( get_BEptr()->nFSRinResSave_ref__BOSS()),
            x1Save( get_BEptr()->x1Save_ref__BOSS()),
            x2Save( get_BEptr()->x2Save_ref__BOSS()),
            x1pdfSave( get_BEptr()->x1pdfSave_ref__BOSS()),
            x2pdfSave( get_BEptr()->x2pdfSave_ref__BOSS()),
            pdf1Save( get_BEptr()->pdf1Save_ref__BOSS()),
            pdf2Save( get_BEptr()->pdf2Save_ref__BOSS()),
            Q2FacSave( get_BEptr()->Q2FacSave_ref__BOSS()),
            alphaEMSave( get_BEptr()->alphaEMSave_ref__BOSS()),
            alphaSSave( get_BEptr()->alphaSSave_ref__BOSS()),
            Q2RenSave( get_BEptr()->Q2RenSave_ref__BOSS()),
            scalupSave( get_BEptr()->scalupSave_ref__BOSS()),
            sH( get_BEptr()->sH_ref__BOSS()),
            tH( get_BEptr()->tH_ref__BOSS()),
            uH( get_BEptr()->uH_ref__BOSS()),
            pTH( get_BEptr()->pTH_ref__BOSS()),
            m3H( get_BEptr()->m3H_ref__BOSS()),
            m4H( get_BEptr()->m4H_ref__BOSS()),
            thetaH( get_BEptr()->thetaH_ref__BOSS()),
            phiH( get_BEptr()->phiH_ref__BOSS()),
            bMPISave( get_BEptr()->bMPISave_ref__BOSS()),
            enhanceMPISave( get_BEptr()->enhanceMPISave_ref__BOSS()),
            enhanceMPIavgSave( get_BEptr()->enhanceMPIavgSave_ref__BOSS()),
            bMPIoldSave( get_BEptr()->bMPIoldSave_ref__BOSS()),
            enhanceMPIoldSave( get_BEptr()->enhanceMPIoldSave_ref__BOSS()),
            enhanceMPIoldavgSave( get_BEptr()->enhanceMPIoldavgSave_ref__BOSS()),
            pTmaxMPISave( get_BEptr()->pTmaxMPISave_ref__BOSS()),
            pTmaxISRSave( get_BEptr()->pTmaxISRSave_ref__BOSS()),
            pTmaxFSRSave( get_BEptr()->pTmaxFSRSave_ref__BOSS()),
            pTnowSave( get_BEptr()->pTnowSave_ref__BOSS()),
            zNowISRSave( get_BEptr()->zNowISRSave_ref__BOSS()),
            pT2NowISRSave( get_BEptr()->pT2NowISRSave_ref__BOSS()),
            xPomA( get_BEptr()->xPomA_ref__BOSS()),
            xPomB( get_BEptr()->xPomB_ref__BOSS()),
            tPomA( get_BEptr()->tPomA_ref__BOSS()),
            tPomB( get_BEptr()->tPomB_ref__BOSS()),
            nameSave( get_BEptr()->nameSave_ref__BOSS()),
            nameSubSave( get_BEptr()->nameSubSave_ref__BOSS()),
            codeMPISave( get_BEptr()->codeMPISave_ref__BOSS()),
            iAMPISave( get_BEptr()->iAMPISave_ref__BOSS()),
            iBMPISave( get_BEptr()->iBMPISave_ref__BOSS()),
            pTMPISave( get_BEptr()->pTMPISave_ref__BOSS()),
            eMPISave( get_BEptr()->eMPISave_ref__BOSS()),
            isVMDstateAEvent( get_BEptr()->isVMDstateAEvent_ref__BOSS()),
            isVMDstateBEvent( get_BEptr()->isVMDstateBEvent_ref__BOSS()),
            gammaModeEvent( get_BEptr()->gammaModeEvent_ref__BOSS()),
            idVMDASave( get_BEptr()->idVMDASave_ref__BOSS()),
            idVMDBSave( get_BEptr()->idVMDBSave_ref__BOSS()),
            x1GammaSave( get_BEptr()->x1GammaSave_ref__BOSS()),
            x2GammaSave( get_BEptr()->x2GammaSave_ref__BOSS()),
            Q2Gamma1Save( get_BEptr()->Q2Gamma1Save_ref__BOSS()),
            Q2Gamma2Save( get_BEptr()->Q2Gamma2Save_ref__BOSS()),
            eCMsubSave( get_BEptr()->eCMsubSave_ref__BOSS()),
            thetaLepton1( get_BEptr()->thetaLepton1_ref__BOSS()),
            thetaLepton2( get_BEptr()->thetaLepton2_ref__BOSS()),
            sHatNewSave( get_BEptr()->sHatNewSave_ref__BOSS()),
            mVMDASave( get_BEptr()->mVMDASave_ref__BOSS()),
            mVMDBSave( get_BEptr()->mVMDBSave_ref__BOSS()),
            scaleVMDASave( get_BEptr()->scaleVMDASave_ref__BOSS()),
            scaleVMDBSave( get_BEptr()->scaleVMDBSave_ref__BOSS()),
            counters( get_BEptr()->counters_ref__BOSS()),
            headers( get_BEptr()->headers_ref__BOSS()),
            headerBlock( get_BEptr()->headerBlock_ref__BOSS()),
            eventComments( get_BEptr()->eventComments_ref__BOSS()),
            weakModes( get_BEptr()->weakModes_ref__BOSS()),
            weak2to2lines( get_BEptr()->weak2to2lines_ref__BOSS()),
            weakDipoles( get_BEptr()->weakDipoles_ref__BOSS()),
            oniumShower( get_BEptr()->oniumShower_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Info::Info(bool arg_1) :
            WrapperBase(__factory1(arg_1)),
            LHEFversionSave( get_BEptr()->LHEFversionSave_ref__BOSS()),
            sigmaLHEFSave( get_BEptr()->sigmaLHEFSave_ref__BOSS()),
            hasOwnEventAttributes( get_BEptr()->hasOwnEventAttributes_ref__BOSS()),
            eventAttributes( get_BEptr()->eventAttributes_ref__BOSS()),
            weights_detailed( get_BEptr()->weights_detailed_ref__BOSS()),
            weights_compressed( get_BEptr()->weights_compressed_ref__BOSS()),
            weights_detailed_vector( get_BEptr()->weights_detailed_vector_ref__BOSS()),
            eventWeightLHEF( get_BEptr()->eventWeightLHEF_ref__BOSS()),
            CONVERTMB2PB( get_BEptr()->CONVERTMB2PB_ref__BOSS()),
            idASave( get_BEptr()->idASave_ref__BOSS()),
            idBSave( get_BEptr()->idBSave_ref__BOSS()),
            pzASave( get_BEptr()->pzASave_ref__BOSS()),
            eASave( get_BEptr()->eASave_ref__BOSS()),
            mASave( get_BEptr()->mASave_ref__BOSS()),
            pzBSave( get_BEptr()->pzBSave_ref__BOSS()),
            eBSave( get_BEptr()->eBSave_ref__BOSS()),
            mBSave( get_BEptr()->mBSave_ref__BOSS()),
            eCMSave( get_BEptr()->eCMSave_ref__BOSS()),
            sSave( get_BEptr()->sSave_ref__BOSS()),
            lowPTmin( get_BEptr()->lowPTmin_ref__BOSS()),
            nTry( get_BEptr()->nTry_ref__BOSS()),
            nSel( get_BEptr()->nSel_ref__BOSS()),
            nAcc( get_BEptr()->nAcc_ref__BOSS()),
            sigGen( get_BEptr()->sigGen_ref__BOSS()),
            sigErr( get_BEptr()->sigErr_ref__BOSS()),
            wtAccSum( get_BEptr()->wtAccSum_ref__BOSS()),
            procNameM( get_BEptr()->procNameM_ref__BOSS()),
            nTryM( get_BEptr()->nTryM_ref__BOSS()),
            nSelM( get_BEptr()->nSelM_ref__BOSS()),
            nAccM( get_BEptr()->nAccM_ref__BOSS()),
            sigGenM( get_BEptr()->sigGenM_ref__BOSS()),
            sigErrM( get_BEptr()->sigErrM_ref__BOSS()),
            lhaStrategySave( get_BEptr()->lhaStrategySave_ref__BOSS()),
            a0MPISave( get_BEptr()->a0MPISave_ref__BOSS()),
            isRes( get_BEptr()->isRes_ref__BOSS()),
            isDiffA( get_BEptr()->isDiffA_ref__BOSS()),
            isDiffB( get_BEptr()->isDiffB_ref__BOSS()),
            isDiffC( get_BEptr()->isDiffC_ref__BOSS()),
            isND( get_BEptr()->isND_ref__BOSS()),
            isLH( get_BEptr()->isLH_ref__BOSS()),
            hasSubSave( get_BEptr()->hasSubSave_ref__BOSS()),
            bIsSet( get_BEptr()->bIsSet_ref__BOSS()),
            evolIsSet( get_BEptr()->evolIsSet_ref__BOSS()),
            atEOF( get_BEptr()->atEOF_ref__BOSS()),
            isVal1( get_BEptr()->isVal1_ref__BOSS()),
            isVal2( get_BEptr()->isVal2_ref__BOSS()),
            hasHistorySave( get_BEptr()->hasHistorySave_ref__BOSS()),
            abortPartonLevel( get_BEptr()->abortPartonLevel_ref__BOSS()),
            isHardDiffA( get_BEptr()->isHardDiffA_ref__BOSS()),
            isHardDiffB( get_BEptr()->isHardDiffB_ref__BOSS()),
            hasUnresBeams( get_BEptr()->hasUnresBeams_ref__BOSS()),
            hasPomPsys( get_BEptr()->hasPomPsys_ref__BOSS()),
            codeSave( get_BEptr()->codeSave_ref__BOSS()),
            codeSubSave( get_BEptr()->codeSubSave_ref__BOSS()),
            nFinalSave( get_BEptr()->nFinalSave_ref__BOSS()),
            nFinalSubSave( get_BEptr()->nFinalSubSave_ref__BOSS()),
            nTotal( get_BEptr()->nTotal_ref__BOSS()),
            id1Save( get_BEptr()->id1Save_ref__BOSS()),
            id2Save( get_BEptr()->id2Save_ref__BOSS()),
            id1pdfSave( get_BEptr()->id1pdfSave_ref__BOSS()),
            id2pdfSave( get_BEptr()->id2pdfSave_ref__BOSS()),
            nMPISave( get_BEptr()->nMPISave_ref__BOSS()),
            nISRSave( get_BEptr()->nISRSave_ref__BOSS()),
            nFSRinProcSave( get_BEptr()->nFSRinProcSave_ref__BOSS()),
            nFSRinResSave( get_BEptr()->nFSRinResSave_ref__BOSS()),
            x1Save( get_BEptr()->x1Save_ref__BOSS()),
            x2Save( get_BEptr()->x2Save_ref__BOSS()),
            x1pdfSave( get_BEptr()->x1pdfSave_ref__BOSS()),
            x2pdfSave( get_BEptr()->x2pdfSave_ref__BOSS()),
            pdf1Save( get_BEptr()->pdf1Save_ref__BOSS()),
            pdf2Save( get_BEptr()->pdf2Save_ref__BOSS()),
            Q2FacSave( get_BEptr()->Q2FacSave_ref__BOSS()),
            alphaEMSave( get_BEptr()->alphaEMSave_ref__BOSS()),
            alphaSSave( get_BEptr()->alphaSSave_ref__BOSS()),
            Q2RenSave( get_BEptr()->Q2RenSave_ref__BOSS()),
            scalupSave( get_BEptr()->scalupSave_ref__BOSS()),
            sH( get_BEptr()->sH_ref__BOSS()),
            tH( get_BEptr()->tH_ref__BOSS()),
            uH( get_BEptr()->uH_ref__BOSS()),
            pTH( get_BEptr()->pTH_ref__BOSS()),
            m3H( get_BEptr()->m3H_ref__BOSS()),
            m4H( get_BEptr()->m4H_ref__BOSS()),
            thetaH( get_BEptr()->thetaH_ref__BOSS()),
            phiH( get_BEptr()->phiH_ref__BOSS()),
            bMPISave( get_BEptr()->bMPISave_ref__BOSS()),
            enhanceMPISave( get_BEptr()->enhanceMPISave_ref__BOSS()),
            enhanceMPIavgSave( get_BEptr()->enhanceMPIavgSave_ref__BOSS()),
            bMPIoldSave( get_BEptr()->bMPIoldSave_ref__BOSS()),
            enhanceMPIoldSave( get_BEptr()->enhanceMPIoldSave_ref__BOSS()),
            enhanceMPIoldavgSave( get_BEptr()->enhanceMPIoldavgSave_ref__BOSS()),
            pTmaxMPISave( get_BEptr()->pTmaxMPISave_ref__BOSS()),
            pTmaxISRSave( get_BEptr()->pTmaxISRSave_ref__BOSS()),
            pTmaxFSRSave( get_BEptr()->pTmaxFSRSave_ref__BOSS()),
            pTnowSave( get_BEptr()->pTnowSave_ref__BOSS()),
            zNowISRSave( get_BEptr()->zNowISRSave_ref__BOSS()),
            pT2NowISRSave( get_BEptr()->pT2NowISRSave_ref__BOSS()),
            xPomA( get_BEptr()->xPomA_ref__BOSS()),
            xPomB( get_BEptr()->xPomB_ref__BOSS()),
            tPomA( get_BEptr()->tPomA_ref__BOSS()),
            tPomB( get_BEptr()->tPomB_ref__BOSS()),
            nameSave( get_BEptr()->nameSave_ref__BOSS()),
            nameSubSave( get_BEptr()->nameSubSave_ref__BOSS()),
            codeMPISave( get_BEptr()->codeMPISave_ref__BOSS()),
            iAMPISave( get_BEptr()->iAMPISave_ref__BOSS()),
            iBMPISave( get_BEptr()->iBMPISave_ref__BOSS()),
            pTMPISave( get_BEptr()->pTMPISave_ref__BOSS()),
            eMPISave( get_BEptr()->eMPISave_ref__BOSS()),
            isVMDstateAEvent( get_BEptr()->isVMDstateAEvent_ref__BOSS()),
            isVMDstateBEvent( get_BEptr()->isVMDstateBEvent_ref__BOSS()),
            gammaModeEvent( get_BEptr()->gammaModeEvent_ref__BOSS()),
            idVMDASave( get_BEptr()->idVMDASave_ref__BOSS()),
            idVMDBSave( get_BEptr()->idVMDBSave_ref__BOSS()),
            x1GammaSave( get_BEptr()->x1GammaSave_ref__BOSS()),
            x2GammaSave( get_BEptr()->x2GammaSave_ref__BOSS()),
            Q2Gamma1Save( get_BEptr()->Q2Gamma1Save_ref__BOSS()),
            Q2Gamma2Save( get_BEptr()->Q2Gamma2Save_ref__BOSS()),
            eCMsubSave( get_BEptr()->eCMsubSave_ref__BOSS()),
            thetaLepton1( get_BEptr()->thetaLepton1_ref__BOSS()),
            thetaLepton2( get_BEptr()->thetaLepton2_ref__BOSS()),
            sHatNewSave( get_BEptr()->sHatNewSave_ref__BOSS()),
            mVMDASave( get_BEptr()->mVMDASave_ref__BOSS()),
            mVMDBSave( get_BEptr()->mVMDBSave_ref__BOSS()),
            scaleVMDASave( get_BEptr()->scaleVMDASave_ref__BOSS()),
            scaleVMDBSave( get_BEptr()->scaleVMDBSave_ref__BOSS()),
            counters( get_BEptr()->counters_ref__BOSS()),
            headers( get_BEptr()->headers_ref__BOSS()),
            headerBlock( get_BEptr()->headerBlock_ref__BOSS()),
            eventComments( get_BEptr()->eventComments_ref__BOSS()),
            weakModes( get_BEptr()->weakModes_ref__BOSS()),
            weak2to2lines( get_BEptr()->weak2to2lines_ref__BOSS()),
            weakDipoles( get_BEptr()->weakDipoles_ref__BOSS()),
            oniumShower( get_BEptr()->oniumShower_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Info::Info(Abstract_Info* in) :
            WrapperBase(in),
            LHEFversionSave( get_BEptr()->LHEFversionSave_ref__BOSS()),
            sigmaLHEFSave( get_BEptr()->sigmaLHEFSave_ref__BOSS()),
            hasOwnEventAttributes( get_BEptr()->hasOwnEventAttributes_ref__BOSS()),
            eventAttributes( get_BEptr()->eventAttributes_ref__BOSS()),
            weights_detailed( get_BEptr()->weights_detailed_ref__BOSS()),
            weights_compressed( get_BEptr()->weights_compressed_ref__BOSS()),
            weights_detailed_vector( get_BEptr()->weights_detailed_vector_ref__BOSS()),
            eventWeightLHEF( get_BEptr()->eventWeightLHEF_ref__BOSS()),
            CONVERTMB2PB( get_BEptr()->CONVERTMB2PB_ref__BOSS()),
            idASave( get_BEptr()->idASave_ref__BOSS()),
            idBSave( get_BEptr()->idBSave_ref__BOSS()),
            pzASave( get_BEptr()->pzASave_ref__BOSS()),
            eASave( get_BEptr()->eASave_ref__BOSS()),
            mASave( get_BEptr()->mASave_ref__BOSS()),
            pzBSave( get_BEptr()->pzBSave_ref__BOSS()),
            eBSave( get_BEptr()->eBSave_ref__BOSS()),
            mBSave( get_BEptr()->mBSave_ref__BOSS()),
            eCMSave( get_BEptr()->eCMSave_ref__BOSS()),
            sSave( get_BEptr()->sSave_ref__BOSS()),
            lowPTmin( get_BEptr()->lowPTmin_ref__BOSS()),
            nTry( get_BEptr()->nTry_ref__BOSS()),
            nSel( get_BEptr()->nSel_ref__BOSS()),
            nAcc( get_BEptr()->nAcc_ref__BOSS()),
            sigGen( get_BEptr()->sigGen_ref__BOSS()),
            sigErr( get_BEptr()->sigErr_ref__BOSS()),
            wtAccSum( get_BEptr()->wtAccSum_ref__BOSS()),
            procNameM( get_BEptr()->procNameM_ref__BOSS()),
            nTryM( get_BEptr()->nTryM_ref__BOSS()),
            nSelM( get_BEptr()->nSelM_ref__BOSS()),
            nAccM( get_BEptr()->nAccM_ref__BOSS()),
            sigGenM( get_BEptr()->sigGenM_ref__BOSS()),
            sigErrM( get_BEptr()->sigErrM_ref__BOSS()),
            lhaStrategySave( get_BEptr()->lhaStrategySave_ref__BOSS()),
            a0MPISave( get_BEptr()->a0MPISave_ref__BOSS()),
            isRes( get_BEptr()->isRes_ref__BOSS()),
            isDiffA( get_BEptr()->isDiffA_ref__BOSS()),
            isDiffB( get_BEptr()->isDiffB_ref__BOSS()),
            isDiffC( get_BEptr()->isDiffC_ref__BOSS()),
            isND( get_BEptr()->isND_ref__BOSS()),
            isLH( get_BEptr()->isLH_ref__BOSS()),
            hasSubSave( get_BEptr()->hasSubSave_ref__BOSS()),
            bIsSet( get_BEptr()->bIsSet_ref__BOSS()),
            evolIsSet( get_BEptr()->evolIsSet_ref__BOSS()),
            atEOF( get_BEptr()->atEOF_ref__BOSS()),
            isVal1( get_BEptr()->isVal1_ref__BOSS()),
            isVal2( get_BEptr()->isVal2_ref__BOSS()),
            hasHistorySave( get_BEptr()->hasHistorySave_ref__BOSS()),
            abortPartonLevel( get_BEptr()->abortPartonLevel_ref__BOSS()),
            isHardDiffA( get_BEptr()->isHardDiffA_ref__BOSS()),
            isHardDiffB( get_BEptr()->isHardDiffB_ref__BOSS()),
            hasUnresBeams( get_BEptr()->hasUnresBeams_ref__BOSS()),
            hasPomPsys( get_BEptr()->hasPomPsys_ref__BOSS()),
            codeSave( get_BEptr()->codeSave_ref__BOSS()),
            codeSubSave( get_BEptr()->codeSubSave_ref__BOSS()),
            nFinalSave( get_BEptr()->nFinalSave_ref__BOSS()),
            nFinalSubSave( get_BEptr()->nFinalSubSave_ref__BOSS()),
            nTotal( get_BEptr()->nTotal_ref__BOSS()),
            id1Save( get_BEptr()->id1Save_ref__BOSS()),
            id2Save( get_BEptr()->id2Save_ref__BOSS()),
            id1pdfSave( get_BEptr()->id1pdfSave_ref__BOSS()),
            id2pdfSave( get_BEptr()->id2pdfSave_ref__BOSS()),
            nMPISave( get_BEptr()->nMPISave_ref__BOSS()),
            nISRSave( get_BEptr()->nISRSave_ref__BOSS()),
            nFSRinProcSave( get_BEptr()->nFSRinProcSave_ref__BOSS()),
            nFSRinResSave( get_BEptr()->nFSRinResSave_ref__BOSS()),
            x1Save( get_BEptr()->x1Save_ref__BOSS()),
            x2Save( get_BEptr()->x2Save_ref__BOSS()),
            x1pdfSave( get_BEptr()->x1pdfSave_ref__BOSS()),
            x2pdfSave( get_BEptr()->x2pdfSave_ref__BOSS()),
            pdf1Save( get_BEptr()->pdf1Save_ref__BOSS()),
            pdf2Save( get_BEptr()->pdf2Save_ref__BOSS()),
            Q2FacSave( get_BEptr()->Q2FacSave_ref__BOSS()),
            alphaEMSave( get_BEptr()->alphaEMSave_ref__BOSS()),
            alphaSSave( get_BEptr()->alphaSSave_ref__BOSS()),
            Q2RenSave( get_BEptr()->Q2RenSave_ref__BOSS()),
            scalupSave( get_BEptr()->scalupSave_ref__BOSS()),
            sH( get_BEptr()->sH_ref__BOSS()),
            tH( get_BEptr()->tH_ref__BOSS()),
            uH( get_BEptr()->uH_ref__BOSS()),
            pTH( get_BEptr()->pTH_ref__BOSS()),
            m3H( get_BEptr()->m3H_ref__BOSS()),
            m4H( get_BEptr()->m4H_ref__BOSS()),
            thetaH( get_BEptr()->thetaH_ref__BOSS()),
            phiH( get_BEptr()->phiH_ref__BOSS()),
            bMPISave( get_BEptr()->bMPISave_ref__BOSS()),
            enhanceMPISave( get_BEptr()->enhanceMPISave_ref__BOSS()),
            enhanceMPIavgSave( get_BEptr()->enhanceMPIavgSave_ref__BOSS()),
            bMPIoldSave( get_BEptr()->bMPIoldSave_ref__BOSS()),
            enhanceMPIoldSave( get_BEptr()->enhanceMPIoldSave_ref__BOSS()),
            enhanceMPIoldavgSave( get_BEptr()->enhanceMPIoldavgSave_ref__BOSS()),
            pTmaxMPISave( get_BEptr()->pTmaxMPISave_ref__BOSS()),
            pTmaxISRSave( get_BEptr()->pTmaxISRSave_ref__BOSS()),
            pTmaxFSRSave( get_BEptr()->pTmaxFSRSave_ref__BOSS()),
            pTnowSave( get_BEptr()->pTnowSave_ref__BOSS()),
            zNowISRSave( get_BEptr()->zNowISRSave_ref__BOSS()),
            pT2NowISRSave( get_BEptr()->pT2NowISRSave_ref__BOSS()),
            xPomA( get_BEptr()->xPomA_ref__BOSS()),
            xPomB( get_BEptr()->xPomB_ref__BOSS()),
            tPomA( get_BEptr()->tPomA_ref__BOSS()),
            tPomB( get_BEptr()->tPomB_ref__BOSS()),
            nameSave( get_BEptr()->nameSave_ref__BOSS()),
            nameSubSave( get_BEptr()->nameSubSave_ref__BOSS()),
            codeMPISave( get_BEptr()->codeMPISave_ref__BOSS()),
            iAMPISave( get_BEptr()->iAMPISave_ref__BOSS()),
            iBMPISave( get_BEptr()->iBMPISave_ref__BOSS()),
            pTMPISave( get_BEptr()->pTMPISave_ref__BOSS()),
            eMPISave( get_BEptr()->eMPISave_ref__BOSS()),
            isVMDstateAEvent( get_BEptr()->isVMDstateAEvent_ref__BOSS()),
            isVMDstateBEvent( get_BEptr()->isVMDstateBEvent_ref__BOSS()),
            gammaModeEvent( get_BEptr()->gammaModeEvent_ref__BOSS()),
            idVMDASave( get_BEptr()->idVMDASave_ref__BOSS()),
            idVMDBSave( get_BEptr()->idVMDBSave_ref__BOSS()),
            x1GammaSave( get_BEptr()->x1GammaSave_ref__BOSS()),
            x2GammaSave( get_BEptr()->x2GammaSave_ref__BOSS()),
            Q2Gamma1Save( get_BEptr()->Q2Gamma1Save_ref__BOSS()),
            Q2Gamma2Save( get_BEptr()->Q2Gamma2Save_ref__BOSS()),
            eCMsubSave( get_BEptr()->eCMsubSave_ref__BOSS()),
            thetaLepton1( get_BEptr()->thetaLepton1_ref__BOSS()),
            thetaLepton2( get_BEptr()->thetaLepton2_ref__BOSS()),
            sHatNewSave( get_BEptr()->sHatNewSave_ref__BOSS()),
            mVMDASave( get_BEptr()->mVMDASave_ref__BOSS()),
            mVMDBSave( get_BEptr()->mVMDBSave_ref__BOSS()),
            scaleVMDASave( get_BEptr()->scaleVMDASave_ref__BOSS()),
            scaleVMDBSave( get_BEptr()->scaleVMDBSave_ref__BOSS()),
            counters( get_BEptr()->counters_ref__BOSS()),
            headers( get_BEptr()->headers_ref__BOSS()),
            headerBlock( get_BEptr()->headerBlock_ref__BOSS()),
            eventComments( get_BEptr()->eventComments_ref__BOSS()),
            weakModes( get_BEptr()->weakModes_ref__BOSS()),
            weak2to2lines( get_BEptr()->weak2to2lines_ref__BOSS()),
            weakDipoles( get_BEptr()->weakDipoles_ref__BOSS()),
            oniumShower( get_BEptr()->oniumShower_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Info::Info(const Info& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
            LHEFversionSave( get_BEptr()->LHEFversionSave_ref__BOSS()),
            sigmaLHEFSave( get_BEptr()->sigmaLHEFSave_ref__BOSS()),
            hasOwnEventAttributes( get_BEptr()->hasOwnEventAttributes_ref__BOSS()),
            eventAttributes( get_BEptr()->eventAttributes_ref__BOSS()),
            weights_detailed( get_BEptr()->weights_detailed_ref__BOSS()),
            weights_compressed( get_BEptr()->weights_compressed_ref__BOSS()),
            weights_detailed_vector( get_BEptr()->weights_detailed_vector_ref__BOSS()),
            eventWeightLHEF( get_BEptr()->eventWeightLHEF_ref__BOSS()),
            CONVERTMB2PB( get_BEptr()->CONVERTMB2PB_ref__BOSS()),
            idASave( get_BEptr()->idASave_ref__BOSS()),
            idBSave( get_BEptr()->idBSave_ref__BOSS()),
            pzASave( get_BEptr()->pzASave_ref__BOSS()),
            eASave( get_BEptr()->eASave_ref__BOSS()),
            mASave( get_BEptr()->mASave_ref__BOSS()),
            pzBSave( get_BEptr()->pzBSave_ref__BOSS()),
            eBSave( get_BEptr()->eBSave_ref__BOSS()),
            mBSave( get_BEptr()->mBSave_ref__BOSS()),
            eCMSave( get_BEptr()->eCMSave_ref__BOSS()),
            sSave( get_BEptr()->sSave_ref__BOSS()),
            lowPTmin( get_BEptr()->lowPTmin_ref__BOSS()),
            nTry( get_BEptr()->nTry_ref__BOSS()),
            nSel( get_BEptr()->nSel_ref__BOSS()),
            nAcc( get_BEptr()->nAcc_ref__BOSS()),
            sigGen( get_BEptr()->sigGen_ref__BOSS()),
            sigErr( get_BEptr()->sigErr_ref__BOSS()),
            wtAccSum( get_BEptr()->wtAccSum_ref__BOSS()),
            procNameM( get_BEptr()->procNameM_ref__BOSS()),
            nTryM( get_BEptr()->nTryM_ref__BOSS()),
            nSelM( get_BEptr()->nSelM_ref__BOSS()),
            nAccM( get_BEptr()->nAccM_ref__BOSS()),
            sigGenM( get_BEptr()->sigGenM_ref__BOSS()),
            sigErrM( get_BEptr()->sigErrM_ref__BOSS()),
            lhaStrategySave( get_BEptr()->lhaStrategySave_ref__BOSS()),
            a0MPISave( get_BEptr()->a0MPISave_ref__BOSS()),
            isRes( get_BEptr()->isRes_ref__BOSS()),
            isDiffA( get_BEptr()->isDiffA_ref__BOSS()),
            isDiffB( get_BEptr()->isDiffB_ref__BOSS()),
            isDiffC( get_BEptr()->isDiffC_ref__BOSS()),
            isND( get_BEptr()->isND_ref__BOSS()),
            isLH( get_BEptr()->isLH_ref__BOSS()),
            hasSubSave( get_BEptr()->hasSubSave_ref__BOSS()),
            bIsSet( get_BEptr()->bIsSet_ref__BOSS()),
            evolIsSet( get_BEptr()->evolIsSet_ref__BOSS()),
            atEOF( get_BEptr()->atEOF_ref__BOSS()),
            isVal1( get_BEptr()->isVal1_ref__BOSS()),
            isVal2( get_BEptr()->isVal2_ref__BOSS()),
            hasHistorySave( get_BEptr()->hasHistorySave_ref__BOSS()),
            abortPartonLevel( get_BEptr()->abortPartonLevel_ref__BOSS()),
            isHardDiffA( get_BEptr()->isHardDiffA_ref__BOSS()),
            isHardDiffB( get_BEptr()->isHardDiffB_ref__BOSS()),
            hasUnresBeams( get_BEptr()->hasUnresBeams_ref__BOSS()),
            hasPomPsys( get_BEptr()->hasPomPsys_ref__BOSS()),
            codeSave( get_BEptr()->codeSave_ref__BOSS()),
            codeSubSave( get_BEptr()->codeSubSave_ref__BOSS()),
            nFinalSave( get_BEptr()->nFinalSave_ref__BOSS()),
            nFinalSubSave( get_BEptr()->nFinalSubSave_ref__BOSS()),
            nTotal( get_BEptr()->nTotal_ref__BOSS()),
            id1Save( get_BEptr()->id1Save_ref__BOSS()),
            id2Save( get_BEptr()->id2Save_ref__BOSS()),
            id1pdfSave( get_BEptr()->id1pdfSave_ref__BOSS()),
            id2pdfSave( get_BEptr()->id2pdfSave_ref__BOSS()),
            nMPISave( get_BEptr()->nMPISave_ref__BOSS()),
            nISRSave( get_BEptr()->nISRSave_ref__BOSS()),
            nFSRinProcSave( get_BEptr()->nFSRinProcSave_ref__BOSS()),
            nFSRinResSave( get_BEptr()->nFSRinResSave_ref__BOSS()),
            x1Save( get_BEptr()->x1Save_ref__BOSS()),
            x2Save( get_BEptr()->x2Save_ref__BOSS()),
            x1pdfSave( get_BEptr()->x1pdfSave_ref__BOSS()),
            x2pdfSave( get_BEptr()->x2pdfSave_ref__BOSS()),
            pdf1Save( get_BEptr()->pdf1Save_ref__BOSS()),
            pdf2Save( get_BEptr()->pdf2Save_ref__BOSS()),
            Q2FacSave( get_BEptr()->Q2FacSave_ref__BOSS()),
            alphaEMSave( get_BEptr()->alphaEMSave_ref__BOSS()),
            alphaSSave( get_BEptr()->alphaSSave_ref__BOSS()),
            Q2RenSave( get_BEptr()->Q2RenSave_ref__BOSS()),
            scalupSave( get_BEptr()->scalupSave_ref__BOSS()),
            sH( get_BEptr()->sH_ref__BOSS()),
            tH( get_BEptr()->tH_ref__BOSS()),
            uH( get_BEptr()->uH_ref__BOSS()),
            pTH( get_BEptr()->pTH_ref__BOSS()),
            m3H( get_BEptr()->m3H_ref__BOSS()),
            m4H( get_BEptr()->m4H_ref__BOSS()),
            thetaH( get_BEptr()->thetaH_ref__BOSS()),
            phiH( get_BEptr()->phiH_ref__BOSS()),
            bMPISave( get_BEptr()->bMPISave_ref__BOSS()),
            enhanceMPISave( get_BEptr()->enhanceMPISave_ref__BOSS()),
            enhanceMPIavgSave( get_BEptr()->enhanceMPIavgSave_ref__BOSS()),
            bMPIoldSave( get_BEptr()->bMPIoldSave_ref__BOSS()),
            enhanceMPIoldSave( get_BEptr()->enhanceMPIoldSave_ref__BOSS()),
            enhanceMPIoldavgSave( get_BEptr()->enhanceMPIoldavgSave_ref__BOSS()),
            pTmaxMPISave( get_BEptr()->pTmaxMPISave_ref__BOSS()),
            pTmaxISRSave( get_BEptr()->pTmaxISRSave_ref__BOSS()),
            pTmaxFSRSave( get_BEptr()->pTmaxFSRSave_ref__BOSS()),
            pTnowSave( get_BEptr()->pTnowSave_ref__BOSS()),
            zNowISRSave( get_BEptr()->zNowISRSave_ref__BOSS()),
            pT2NowISRSave( get_BEptr()->pT2NowISRSave_ref__BOSS()),
            xPomA( get_BEptr()->xPomA_ref__BOSS()),
            xPomB( get_BEptr()->xPomB_ref__BOSS()),
            tPomA( get_BEptr()->tPomA_ref__BOSS()),
            tPomB( get_BEptr()->tPomB_ref__BOSS()),
            nameSave( get_BEptr()->nameSave_ref__BOSS()),
            nameSubSave( get_BEptr()->nameSubSave_ref__BOSS()),
            codeMPISave( get_BEptr()->codeMPISave_ref__BOSS()),
            iAMPISave( get_BEptr()->iAMPISave_ref__BOSS()),
            iBMPISave( get_BEptr()->iBMPISave_ref__BOSS()),
            pTMPISave( get_BEptr()->pTMPISave_ref__BOSS()),
            eMPISave( get_BEptr()->eMPISave_ref__BOSS()),
            isVMDstateAEvent( get_BEptr()->isVMDstateAEvent_ref__BOSS()),
            isVMDstateBEvent( get_BEptr()->isVMDstateBEvent_ref__BOSS()),
            gammaModeEvent( get_BEptr()->gammaModeEvent_ref__BOSS()),
            idVMDASave( get_BEptr()->idVMDASave_ref__BOSS()),
            idVMDBSave( get_BEptr()->idVMDBSave_ref__BOSS()),
            x1GammaSave( get_BEptr()->x1GammaSave_ref__BOSS()),
            x2GammaSave( get_BEptr()->x2GammaSave_ref__BOSS()),
            Q2Gamma1Save( get_BEptr()->Q2Gamma1Save_ref__BOSS()),
            Q2Gamma2Save( get_BEptr()->Q2Gamma2Save_ref__BOSS()),
            eCMsubSave( get_BEptr()->eCMsubSave_ref__BOSS()),
            thetaLepton1( get_BEptr()->thetaLepton1_ref__BOSS()),
            thetaLepton2( get_BEptr()->thetaLepton2_ref__BOSS()),
            sHatNewSave( get_BEptr()->sHatNewSave_ref__BOSS()),
            mVMDASave( get_BEptr()->mVMDASave_ref__BOSS()),
            mVMDBSave( get_BEptr()->mVMDBSave_ref__BOSS()),
            scaleVMDASave( get_BEptr()->scaleVMDASave_ref__BOSS()),
            scaleVMDBSave( get_BEptr()->scaleVMDBSave_ref__BOSS()),
            counters( get_BEptr()->counters_ref__BOSS()),
            headers( get_BEptr()->headers_ref__BOSS()),
            headerBlock( get_BEptr()->headerBlock_ref__BOSS()),
            eventComments( get_BEptr()->eventComments_ref__BOSS()),
            weakModes( get_BEptr()->weakModes_ref__BOSS()),
            weak2to2lines( get_BEptr()->weak2to2lines_ref__BOSS()),
            weakDipoles( get_BEptr()->weakDipoles_ref__BOSS()),
            oniumShower( get_BEptr()->oniumShower_ref__BOSS())
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

#endif /* __wrapper_Info_def_Pythia_8_312_h__ */
