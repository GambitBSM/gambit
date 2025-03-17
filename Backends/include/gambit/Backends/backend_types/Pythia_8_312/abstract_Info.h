#ifndef __abstract_Info_Pythia_8_312_h__
#define __abstract_Info_Pythia_8_312_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
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
        class Abstract_Info : public virtual AbstractBase
        {
            public:
    
                virtual Pythia8::Abstract_Info& operator_equal__BOSS(const Pythia8::Abstract_Info&) =0;
    
                virtual void list() const =0;
    
                virtual int idA() const =0;
    
                virtual int idB() const =0;
    
                virtual double pzA() const =0;
    
                virtual double pzB() const =0;
    
                virtual double eA() const =0;
    
                virtual double eB() const =0;
    
                virtual double mA() const =0;
    
                virtual double mB() const =0;
    
                virtual double eCM() const =0;
    
                virtual double s() const =0;
    
                virtual bool tooLowPTmin() const =0;
    
                virtual ::std::string name() const =0;
    
                virtual int code() const =0;
    
                virtual int nFinal() const =0;
    
                virtual bool isResolved() const =0;
    
                virtual bool isDiffractiveA() const =0;
    
                virtual bool isDiffractiveB() const =0;
    
                virtual bool isDiffractiveC() const =0;
    
                virtual bool isNonDiffractive() const =0;
    
                virtual bool isElastic() const =0;
    
                virtual bool isMinBias() const =0;
    
                virtual bool isLHA() const =0;
    
                virtual bool atEndOfFile() const =0;
    
                virtual bool hasSub(int) const =0;
    
                virtual bool hasSub__BOSS() const =0;
    
                virtual ::std::string nameSub(int) const =0;
    
                virtual ::std::string nameSub__BOSS() const =0;
    
                virtual int codeSub(int) const =0;
    
                virtual int codeSub__BOSS() const =0;
    
                virtual int nFinalSub(int) const =0;
    
                virtual int nFinalSub__BOSS() const =0;
    
                virtual int id1(int) const =0;
    
                virtual int id1__BOSS() const =0;
    
                virtual int id2(int) const =0;
    
                virtual int id2__BOSS() const =0;
    
                virtual double x1(int) const =0;
    
                virtual double x1__BOSS() const =0;
    
                virtual double x2(int) const =0;
    
                virtual double x2__BOSS() const =0;
    
                virtual double y(int) const =0;
    
                virtual double y__BOSS() const =0;
    
                virtual double tau(int) const =0;
    
                virtual double tau__BOSS() const =0;
    
                virtual int id1pdf(int) const =0;
    
                virtual int id1pdf__BOSS() const =0;
    
                virtual int id2pdf(int) const =0;
    
                virtual int id2pdf__BOSS() const =0;
    
                virtual double x1pdf(int) const =0;
    
                virtual double x1pdf__BOSS() const =0;
    
                virtual double x2pdf(int) const =0;
    
                virtual double x2pdf__BOSS() const =0;
    
                virtual double pdf1(int) const =0;
    
                virtual double pdf1__BOSS() const =0;
    
                virtual double pdf2(int) const =0;
    
                virtual double pdf2__BOSS() const =0;
    
                virtual double QFac(int) const =0;
    
                virtual double QFac__BOSS() const =0;
    
                virtual double Q2Fac(int) const =0;
    
                virtual double Q2Fac__BOSS() const =0;
    
                virtual bool isValence1() const =0;
    
                virtual bool isValence2() const =0;
    
                virtual double alphaS(int) const =0;
    
                virtual double alphaS__BOSS() const =0;
    
                virtual double alphaEM(int) const =0;
    
                virtual double alphaEM__BOSS() const =0;
    
                virtual double QRen(int) const =0;
    
                virtual double QRen__BOSS() const =0;
    
                virtual double Q2Ren(int) const =0;
    
                virtual double Q2Ren__BOSS() const =0;
    
                virtual double scalup(int) const =0;
    
                virtual double scalup__BOSS() const =0;
    
                virtual double xGammaA() const =0;
    
                virtual double xGammaB() const =0;
    
                virtual double Q2GammaA() const =0;
    
                virtual double Q2GammaB() const =0;
    
                virtual double eCMsub() const =0;
    
                virtual double thetaScatLepA() const =0;
    
                virtual double thetaScatLepB() const =0;
    
                virtual double sHatNew() const =0;
    
                virtual int photonMode() const =0;
    
                virtual bool isVMDstateA() const =0;
    
                virtual bool isVMDstateB() const =0;
    
                virtual int idVMDA() const =0;
    
                virtual int idVMDB() const =0;
    
                virtual double mVMDA() const =0;
    
                virtual double mVMDB() const =0;
    
                virtual double scaleVMDA() const =0;
    
                virtual double scaleVMDB() const =0;
    
                virtual double mHat(int) const =0;
    
                virtual double mHat__BOSS() const =0;
    
                virtual double sHat(int) const =0;
    
                virtual double sHat__BOSS() const =0;
    
                virtual double tHat(int) const =0;
    
                virtual double tHat__BOSS() const =0;
    
                virtual double uHat(int) const =0;
    
                virtual double uHat__BOSS() const =0;
    
                virtual double pTHat(int) const =0;
    
                virtual double pTHat__BOSS() const =0;
    
                virtual double pT2Hat(int) const =0;
    
                virtual double pT2Hat__BOSS() const =0;
    
                virtual double m3Hat(int) const =0;
    
                virtual double m3Hat__BOSS() const =0;
    
                virtual double m4Hat(int) const =0;
    
                virtual double m4Hat__BOSS() const =0;
    
                virtual double thetaHat(int) const =0;
    
                virtual double thetaHat__BOSS() const =0;
    
                virtual double phiHat(int) const =0;
    
                virtual double phiHat__BOSS() const =0;
    
                virtual double weight(int) const =0;
    
                virtual double weight__BOSS() const =0;
    
                virtual double weightSum() const =0;
    
                virtual double lhaStrategy() const =0;
    
                virtual int nWeights() const =0;
    
                virtual ::std::string weightLabel(int) const =0;
    
                virtual int nWeightGroups() const =0;
    
                virtual ::std::string getGroupName(int) const =0;
    
                virtual double getGroupWeight(int) const =0;
    
                virtual int nISR() const =0;
    
                virtual int nFSRinProc() const =0;
    
                virtual int nFSRinRes() const =0;
    
                virtual double pTmaxMPI() const =0;
    
                virtual double pTmaxISR() const =0;
    
                virtual double pTmaxFSR() const =0;
    
                virtual double pTnow() const =0;
    
                virtual double a0MPI() const =0;
    
                virtual double bMPI() const =0;
    
                virtual double enhanceMPI() const =0;
    
                virtual double enhanceMPIavg() const =0;
    
                virtual double eMPI(int) const =0;
    
                virtual double bMPIold() const =0;
    
                virtual double enhanceMPIold() const =0;
    
                virtual double enhanceMPIoldavg() const =0;
    
                virtual int nMPI() const =0;
    
                virtual int codeMPI(int) const =0;
    
                virtual double pTMPI(int) const =0;
    
                virtual int iAMPI(int) const =0;
    
                virtual int iBMPI(int) const =0;
    
                virtual ::std::vector<int> codesHard() const =0;
    
                virtual ::std::string nameProc(int) const =0;
    
                virtual ::std::string nameProc__BOSS() const =0;
    
                virtual long int nTried(int) const =0;
    
                virtual long int nTried__BOSS() const =0;
    
                virtual long int nSelected(int) const =0;
    
                virtual long int nSelected__BOSS() const =0;
    
                virtual long int nAccepted(int) const =0;
    
                virtual long int nAccepted__BOSS() const =0;
    
                virtual double sigmaGen(int) const =0;
    
                virtual double sigmaGen__BOSS() const =0;
    
                virtual double sigmaErr(int) const =0;
    
                virtual double sigmaErr__BOSS() const =0;
    
                virtual int getCounter(int) const =0;
    
                virtual void setCounter(int, int) =0;
    
                virtual void setCounter__BOSS(int) =0;
    
                virtual void addCounter(int, int) =0;
    
                virtual void addCounter__BOSS(int) =0;
    
                virtual void setTooLowPTmin(bool) =0;
    
                virtual void setValence(bool, bool) =0;
    
                virtual void hasHistory(bool) =0;
    
                virtual bool hasHistory() =0;
    
                virtual void zNowISR(double) =0;
    
                virtual double zNowISR() =0;
    
                virtual void pT2NowISR(double) =0;
    
                virtual double pT2NowISR() =0;
    
                virtual double mergingWeight(int) const =0;
    
                virtual double mergingWeight__BOSS() const =0;
    
                virtual double mergingWeightNLO(int) const =0;
    
                virtual double mergingWeightNLO__BOSS() const =0;
    
                virtual ::std::string header(const std::string&) const =0;
    
                virtual ::std::vector<std::string> headerKeys() const =0;
    
                virtual int nProcessesLHEF() const =0;
    
                virtual double sigmaLHEF(int) const =0;
    
                virtual int& LHEFversionSave_ref__BOSS() =0;
    
                virtual std::vector<double>& sigmaLHEFSave_ref__BOSS() =0;
    
                virtual bool& hasOwnEventAttributes_ref__BOSS() =0;
    
                virtual std::map<std::string, std::string>*& eventAttributes_ref__BOSS() =0;
    
                virtual std::map<std::string, double>*& weights_detailed_ref__BOSS() =0;
    
                virtual std::vector<double>*& weights_compressed_ref__BOSS() =0;
    
                virtual std::vector<double>& weights_detailed_vector_ref__BOSS() =0;
    
                virtual double& eventWeightLHEF_ref__BOSS() =0;
    
                virtual void setLHEF3InitInfo() =0;
    
                virtual void setLHEF3EventInfo() =0;
    
                virtual ::std::string getEventAttribute(std::string, bool) const =0;
    
                virtual ::std::string getEventAttribute__BOSS(std::string) const =0;
    
                virtual void setEventAttribute(std::string, std::string, bool) =0;
    
                virtual void setEventAttribute__BOSS(std::string, std::string) =0;
    
                virtual int LHEFversion() const =0;
    
                virtual unsigned int getInitrwgtSize() const =0;
    
                virtual unsigned int getGeneratorSize() const =0;
    
                virtual ::std::string getGeneratorValue(unsigned int) const =0;
    
                virtual ::std::string getGeneratorValue__BOSS() const =0;
    
                virtual ::std::string getGeneratorAttribute(unsigned int, std::string, bool) const =0;
    
                virtual ::std::string getGeneratorAttribute__BOSS(unsigned int, std::string) const =0;
    
                virtual unsigned int getWeightsDetailedSize() const =0;
    
                virtual double getWeightsDetailedValue(std::string) const =0;
    
                virtual ::std::string getWeightsDetailedAttribute(std::string, std::string, bool) const =0;
    
                virtual ::std::string getWeightsDetailedAttribute__BOSS(std::string, std::string) const =0;
    
                virtual unsigned int getWeightsCompressedSize() const =0;
    
                virtual double getWeightsCompressedValue(unsigned int) const =0;
    
                virtual ::std::string getWeightsCompressedAttribute(std::string, bool) const =0;
    
                virtual ::std::string getWeightsCompressedAttribute__BOSS(std::string) const =0;
    
                virtual ::std::string getScalesValue(bool) const =0;
    
                virtual ::std::string getScalesValue__BOSS() const =0;
    
                virtual double getScalesAttribute(std::string) const =0;
    
                virtual ::std::string getHeaderBlock() const =0;
    
                virtual ::std::string getEventComments() const =0;
    
                virtual void setHeader(const std::string&, const std::string&) =0;
    
                virtual void setAbortPartonLevel(bool) =0;
    
                virtual bool getAbortPartonLevel() const =0;
    
                virtual bool hasUnresolvedBeams() const =0;
    
                virtual bool hasPomPsystem() const =0;
    
                virtual bool isHardDiffractive() const =0;
    
                virtual bool isHardDiffractiveA() const =0;
    
                virtual bool isHardDiffractiveB() const =0;
    
                virtual double xPomeronA() const =0;
    
                virtual double xPomeronB() const =0;
    
                virtual double tPomeronA() const =0;
    
                virtual double tPomeronB() const =0;
    
                virtual ::std::vector<int> getWeakModes() const =0;
    
                virtual ::std::vector<std::pair<int, int>> getWeakDipoles() const =0;
    
                virtual ::std::vector<int> getWeak2to2lines() const =0;
    
                virtual void setWeakModes(std::vector<int>) =0;
    
                virtual void setWeakDipoles(std::vector<std::pair<int, int>>) =0;
    
                virtual void setWeak2to2lines(std::vector<int>) =0;
    
                virtual void setOniumShower(bool) =0;
    
                virtual bool getOniumShower() const =0;
    
                virtual const double& CONVERTMB2PB_ref__BOSS() =0;
    
                virtual int& idASave_ref__BOSS() =0;
    
                virtual int& idBSave_ref__BOSS() =0;
    
                virtual double& pzASave_ref__BOSS() =0;
    
                virtual double& eASave_ref__BOSS() =0;
    
                virtual double& mASave_ref__BOSS() =0;
    
                virtual double& pzBSave_ref__BOSS() =0;
    
                virtual double& eBSave_ref__BOSS() =0;
    
                virtual double& mBSave_ref__BOSS() =0;
    
                virtual double& eCMSave_ref__BOSS() =0;
    
                virtual double& sSave_ref__BOSS() =0;
    
                virtual bool& lowPTmin_ref__BOSS() =0;
    
                virtual long int& nTry_ref__BOSS() =0;
    
                virtual long int& nSel_ref__BOSS() =0;
    
                virtual long int& nAcc_ref__BOSS() =0;
    
                virtual double& sigGen_ref__BOSS() =0;
    
                virtual double& sigErr_ref__BOSS() =0;
    
                virtual double& wtAccSum_ref__BOSS() =0;
    
                virtual std::map<int, std::basic_string<char>>& procNameM_ref__BOSS() =0;
    
                virtual std::map<int, long>& nTryM_ref__BOSS() =0;
    
                virtual std::map<int, long>& nSelM_ref__BOSS() =0;
    
                virtual std::map<int, long>& nAccM_ref__BOSS() =0;
    
                virtual std::map<int, double>& sigGenM_ref__BOSS() =0;
    
                virtual std::map<int, double>& sigErrM_ref__BOSS() =0;
    
                virtual int& lhaStrategySave_ref__BOSS() =0;
    
                virtual double& a0MPISave_ref__BOSS() =0;
    
                virtual bool& isRes_ref__BOSS() =0;
    
                virtual bool& isDiffA_ref__BOSS() =0;
    
                virtual bool& isDiffB_ref__BOSS() =0;
    
                virtual bool& isDiffC_ref__BOSS() =0;
    
                virtual bool& isND_ref__BOSS() =0;
    
                virtual bool& isLH_ref__BOSS() =0;
    
                virtual bool (&hasSubSave_ref__BOSS())[4] =0;
    
                virtual bool& bIsSet_ref__BOSS() =0;
    
                virtual bool& evolIsSet_ref__BOSS() =0;
    
                virtual bool& atEOF_ref__BOSS() =0;
    
                virtual bool& isVal1_ref__BOSS() =0;
    
                virtual bool& isVal2_ref__BOSS() =0;
    
                virtual bool& hasHistorySave_ref__BOSS() =0;
    
                virtual bool& abortPartonLevel_ref__BOSS() =0;
    
                virtual bool& isHardDiffA_ref__BOSS() =0;
    
                virtual bool& isHardDiffB_ref__BOSS() =0;
    
                virtual bool& hasUnresBeams_ref__BOSS() =0;
    
                virtual bool& hasPomPsys_ref__BOSS() =0;
    
                virtual int& codeSave_ref__BOSS() =0;
    
                virtual int (&codeSubSave_ref__BOSS())[4] =0;
    
                virtual int& nFinalSave_ref__BOSS() =0;
    
                virtual int (&nFinalSubSave_ref__BOSS())[4] =0;
    
                virtual int& nTotal_ref__BOSS() =0;
    
                virtual int (&id1Save_ref__BOSS())[4] =0;
    
                virtual int (&id2Save_ref__BOSS())[4] =0;
    
                virtual int (&id1pdfSave_ref__BOSS())[4] =0;
    
                virtual int (&id2pdfSave_ref__BOSS())[4] =0;
    
                virtual int& nMPISave_ref__BOSS() =0;
    
                virtual int& nISRSave_ref__BOSS() =0;
    
                virtual int& nFSRinProcSave_ref__BOSS() =0;
    
                virtual int& nFSRinResSave_ref__BOSS() =0;
    
                virtual double (&x1Save_ref__BOSS())[4] =0;
    
                virtual double (&x2Save_ref__BOSS())[4] =0;
    
                virtual double (&x1pdfSave_ref__BOSS())[4] =0;
    
                virtual double (&x2pdfSave_ref__BOSS())[4] =0;
    
                virtual double (&pdf1Save_ref__BOSS())[4] =0;
    
                virtual double (&pdf2Save_ref__BOSS())[4] =0;
    
                virtual double (&Q2FacSave_ref__BOSS())[4] =0;
    
                virtual double (&alphaEMSave_ref__BOSS())[4] =0;
    
                virtual double (&alphaSSave_ref__BOSS())[4] =0;
    
                virtual double (&Q2RenSave_ref__BOSS())[4] =0;
    
                virtual double (&scalupSave_ref__BOSS())[4] =0;
    
                virtual double (&sH_ref__BOSS())[4] =0;
    
                virtual double (&tH_ref__BOSS())[4] =0;
    
                virtual double (&uH_ref__BOSS())[4] =0;
    
                virtual double (&pTH_ref__BOSS())[4] =0;
    
                virtual double (&m3H_ref__BOSS())[4] =0;
    
                virtual double (&m4H_ref__BOSS())[4] =0;
    
                virtual double (&thetaH_ref__BOSS())[4] =0;
    
                virtual double (&phiH_ref__BOSS())[4] =0;
    
                virtual double& bMPISave_ref__BOSS() =0;
    
                virtual double& enhanceMPISave_ref__BOSS() =0;
    
                virtual double& enhanceMPIavgSave_ref__BOSS() =0;
    
                virtual double& bMPIoldSave_ref__BOSS() =0;
    
                virtual double& enhanceMPIoldSave_ref__BOSS() =0;
    
                virtual double& enhanceMPIoldavgSave_ref__BOSS() =0;
    
                virtual double& pTmaxMPISave_ref__BOSS() =0;
    
                virtual double& pTmaxISRSave_ref__BOSS() =0;
    
                virtual double& pTmaxFSRSave_ref__BOSS() =0;
    
                virtual double& pTnowSave_ref__BOSS() =0;
    
                virtual double& zNowISRSave_ref__BOSS() =0;
    
                virtual double& pT2NowISRSave_ref__BOSS() =0;
    
                virtual double& xPomA_ref__BOSS() =0;
    
                virtual double& xPomB_ref__BOSS() =0;
    
                virtual double& tPomA_ref__BOSS() =0;
    
                virtual double& tPomB_ref__BOSS() =0;
    
                virtual std::string& nameSave_ref__BOSS() =0;
    
                virtual std::string (&nameSubSave_ref__BOSS())[4] =0;
    
                virtual std::vector<int>& codeMPISave_ref__BOSS() =0;
    
                virtual std::vector<int>& iAMPISave_ref__BOSS() =0;
    
                virtual std::vector<int>& iBMPISave_ref__BOSS() =0;
    
                virtual std::vector<double>& pTMPISave_ref__BOSS() =0;
    
                virtual std::vector<double>& eMPISave_ref__BOSS() =0;
    
                virtual bool& isVMDstateAEvent_ref__BOSS() =0;
    
                virtual bool& isVMDstateBEvent_ref__BOSS() =0;
    
                virtual int& gammaModeEvent_ref__BOSS() =0;
    
                virtual int& idVMDASave_ref__BOSS() =0;
    
                virtual int& idVMDBSave_ref__BOSS() =0;
    
                virtual double& x1GammaSave_ref__BOSS() =0;
    
                virtual double& x2GammaSave_ref__BOSS() =0;
    
                virtual double& Q2Gamma1Save_ref__BOSS() =0;
    
                virtual double& Q2Gamma2Save_ref__BOSS() =0;
    
                virtual double& eCMsubSave_ref__BOSS() =0;
    
                virtual double& thetaLepton1_ref__BOSS() =0;
    
                virtual double& thetaLepton2_ref__BOSS() =0;
    
                virtual double& sHatNewSave_ref__BOSS() =0;
    
                virtual double& mVMDASave_ref__BOSS() =0;
    
                virtual double& mVMDBSave_ref__BOSS() =0;
    
                virtual double& scaleVMDASave_ref__BOSS() =0;
    
                virtual double& scaleVMDBSave_ref__BOSS() =0;
    
                virtual int (&counters_ref__BOSS())[50] =0;
    
                virtual std::map<std::string, std::string>& headers_ref__BOSS() =0;
    
                virtual std::string& headerBlock_ref__BOSS() =0;
    
                virtual std::string& eventComments_ref__BOSS() =0;
    
                virtual void setBeamIDs(int, int) =0;
    
                virtual void setBeamA(int, double, double, double) =0;
    
                virtual void setBeamB(int, double, double, double) =0;
    
                virtual void setECM(double) =0;
    
                virtual void setX1Gamma(double) =0;
    
                virtual void setX2Gamma(double) =0;
    
                virtual void setQ2Gamma1(double) =0;
    
                virtual void setQ2Gamma2(double) =0;
    
                virtual void setTheta1(double) =0;
    
                virtual void setTheta2(double) =0;
    
                virtual void setECMsub(double) =0;
    
                virtual void setsHatNew(double) =0;
    
                virtual void setGammaMode(double) =0;
    
                virtual void setVMDstateA(bool, int, double, double) =0;
    
                virtual void setVMDstateB(bool, int, double, double) =0;
    
                virtual void clear() =0;
    
                virtual int sizeMPIarrays() const =0;
    
                virtual void resizeMPIarrays(int) =0;
    
                virtual void setType(std::string, int, int, bool, bool, bool, bool, bool, bool) =0;
    
                virtual void setType__BOSS(std::string, int, int, bool, bool, bool, bool, bool) =0;
    
                virtual void setType__BOSS(std::string, int, int, bool, bool, bool, bool) =0;
    
                virtual void setType__BOSS(std::string, int, int, bool, bool, bool) =0;
    
                virtual void setType__BOSS(std::string, int, int, bool, bool) =0;
    
                virtual void setType__BOSS(std::string, int, int, bool) =0;
    
                virtual void setType__BOSS(std::string, int, int) =0;
    
                virtual void setSubType(int, std::string, int, int) =0;
    
                virtual void setPDFalpha(int, int, int, double, double, double, double, double, double, double, double, double) =0;
    
                virtual void setScalup(int, double) =0;
    
                virtual void setKin(int, int, int, double, double, double, double, double, double, double, double, double, double) =0;
    
                virtual void setTypeMPI(int, double, int, int, double) =0;
    
                virtual void setTypeMPI__BOSS(int, double, int, int) =0;
    
                virtual void setTypeMPI__BOSS(int, double, int) =0;
    
                virtual void setTypeMPI__BOSS(int, double) =0;
    
                virtual void sigmaReset() =0;
    
                virtual void setSigma(int, std::string, long int, long int, long int, double, double, double) =0;
    
                virtual void addSigma(int, long int, long int, long int, double, double) =0;
    
                virtual void setImpact(double, double, double, bool, bool) =0;
    
                virtual void setImpact__BOSS(double, double, double, bool) =0;
    
                virtual void setImpact__BOSS(double, double, double) =0;
    
                virtual void setPartEvolved(int, int) =0;
    
                virtual void setEvolution(double, double, double, int, int, int, int) =0;
    
                virtual void setPTnow(double) =0;
    
                virtual void seta0MPI(double) =0;
    
                virtual void setEndOfFile(bool) =0;
    
                virtual void setWeight(double, int) =0;
    
                virtual void setIsResolved(bool) =0;
    
                virtual void setHardDiff(bool, bool, bool, bool, double, double, double, double) =0;
    
                virtual void setHardDiff__BOSS(bool, bool, bool, bool, double, double, double) =0;
    
                virtual void setHardDiff__BOSS(bool, bool, bool, bool, double, double) =0;
    
                virtual void setHardDiff__BOSS(bool, bool, bool, bool, double) =0;
    
                virtual void setHardDiff__BOSS(bool, bool, bool, bool) =0;
    
                virtual void setHardDiff__BOSS(bool, bool, bool) =0;
    
                virtual void setHardDiff__BOSS(bool, bool) =0;
    
                virtual void setHardDiff__BOSS(bool) =0;
    
                virtual void setHardDiff__BOSS() =0;
    
                virtual void reassignDiffSystem(int, int) =0;
    
                virtual void setHasUnresolvedBeams(bool) =0;
    
                virtual void setHasPomPsystem(bool) =0;
    
                virtual std::vector<int>& weakModes_ref__BOSS() =0;
    
                virtual std::vector<int>& weak2to2lines_ref__BOSS() =0;
    
                virtual std::vector<std::pair<int, int>>& weakDipoles_ref__BOSS() =0;
    
                virtual bool& oniumShower_ref__BOSS() =0;
    
                virtual int numberOfWeights() const =0;
    
                virtual double weightValueByIndex(int) const =0;
    
                virtual double weightValueByIndex__BOSS() const =0;
    
                virtual ::std::string weightNameByIndex(int) const =0;
    
                virtual ::std::string weightNameByIndex__BOSS() const =0;
    
                virtual ::std::vector<double> weightValueVector() const =0;
    
                virtual ::std::vector<std::string> weightNameVector() const =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Info*) =0;
                virtual Abstract_Info* pointer_copy__BOSS() =0;
    
            private:
                Info* wptr;
                bool delete_wrapper;
            public:
                Info* get_wptr() { return wptr; }
                void set_wptr(Info* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Info()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Info(const Abstract_Info&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Info& operator=(const Abstract_Info&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Info* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Info& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Info() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Info_Pythia_8_312_h__ */
