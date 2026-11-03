#ifndef __wrapper_Info_decl_Pythia_8_312_h__
#define __wrapper_Info_decl_Pythia_8_312_h__

#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Info.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_Rndm_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Info : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Info* (*__factory0)();
                static Abstract_Info* (*__factory1)(bool);
        
                // -- Other member variables: 
            public:
                int& LHEFversionSave;
                std::vector<double>& sigmaLHEFSave;
                bool& hasOwnEventAttributes;
                std::map<std::string, std::string>*& eventAttributes;
                std::map<std::string, double>*& weights_detailed;
                std::vector<double>*& weights_compressed;
                std::vector<double>& weights_detailed_vector;
                double& eventWeightLHEF;
                const double& CONVERTMB2PB;
                int& idASave;
                int& idBSave;
                double& pzASave;
                double& eASave;
                double& mASave;
                double& pzBSave;
                double& eBSave;
                double& mBSave;
                double& eCMSave;
                double& sSave;
                bool& lowPTmin;
                long int& nTry;
                long int& nSel;
                long int& nAcc;
                double& sigGen;
                double& sigErr;
                double& wtAccSum;
                std::map<int, std::basic_string<char>>& procNameM;
                std::map<int, long>& nTryM;
                std::map<int, long>& nSelM;
                std::map<int, long>& nAccM;
                std::map<int, double>& sigGenM;
                std::map<int, double>& sigErrM;
                int& lhaStrategySave;
                double& a0MPISave;
                bool& isRes;
                bool& isDiffA;
                bool& isDiffB;
                bool& isDiffC;
                bool& isND;
                bool& isLH;
                bool (&hasSubSave)[4];
                bool& bIsSet;
                bool& evolIsSet;
                bool& atEOF;
                bool& isVal1;
                bool& isVal2;
                bool& hasHistorySave;
                bool& abortPartonLevel;
                bool& isHardDiffA;
                bool& isHardDiffB;
                bool& hasUnresBeams;
                bool& hasPomPsys;
                int& codeSave;
                int (&codeSubSave)[4];
                int& nFinalSave;
                int (&nFinalSubSave)[4];
                int& nTotal;
                int (&id1Save)[4];
                int (&id2Save)[4];
                int (&id1pdfSave)[4];
                int (&id2pdfSave)[4];
                int& nMPISave;
                int& nISRSave;
                int& nFSRinProcSave;
                int& nFSRinResSave;
                double (&x1Save)[4];
                double (&x2Save)[4];
                double (&x1pdfSave)[4];
                double (&x2pdfSave)[4];
                double (&pdf1Save)[4];
                double (&pdf2Save)[4];
                double (&Q2FacSave)[4];
                double (&alphaEMSave)[4];
                double (&alphaSSave)[4];
                double (&Q2RenSave)[4];
                double (&scalupSave)[4];
                double (&sH)[4];
                double (&tH)[4];
                double (&uH)[4];
                double (&pTH)[4];
                double (&m3H)[4];
                double (&m4H)[4];
                double (&thetaH)[4];
                double (&phiH)[4];
                double& bMPISave;
                double& enhanceMPISave;
                double& enhanceMPIavgSave;
                double& bMPIoldSave;
                double& enhanceMPIoldSave;
                double& enhanceMPIoldavgSave;
                double& pTmaxMPISave;
                double& pTmaxISRSave;
                double& pTmaxFSRSave;
                double& pTnowSave;
                double& zNowISRSave;
                double& pT2NowISRSave;
                double& xPomA;
                double& xPomB;
                double& tPomA;
                double& tPomB;
                std::string& nameSave;
                std::string (&nameSubSave)[4];
                std::vector<int>& codeMPISave;
                std::vector<int>& iAMPISave;
                std::vector<int>& iBMPISave;
                std::vector<double>& pTMPISave;
                std::vector<double>& eMPISave;
                bool& isVMDstateAEvent;
                bool& isVMDstateBEvent;
                int& gammaModeEvent;
                int& idVMDASave;
                int& idVMDBSave;
                double& x1GammaSave;
                double& x2GammaSave;
                double& Q2Gamma1Save;
                double& Q2Gamma2Save;
                double& eCMsubSave;
                double& thetaLepton1;
                double& thetaLepton2;
                double& sHatNewSave;
                double& mVMDASave;
                double& mVMDBSave;
                double& scaleVMDASave;
                double& scaleVMDBSave;
                int (&counters)[50];
                std::map<std::string, std::string>& headers;
                std::string& headerBlock;
                std::string& eventComments;
                std::vector<int>& weakModes;
                std::vector<int>& weak2to2lines;
                std::vector<std::pair<int, int>>& weakDipoles;
                bool& oniumShower;
        
                // Member functions: 
            public:
                void list() const;
        
                int idA() const;
        
                int idB() const;
        
                double pzA() const;
        
                double pzB() const;
        
                double eA() const;
        
                double eB() const;
        
                double mA() const;
        
                double mB() const;
        
                double eCM() const;
        
                double s() const;
        
                bool tooLowPTmin() const;
        
                ::std::string name() const;
        
                int code() const;
        
                int nFinal() const;
        
                bool isResolved() const;
        
                bool isDiffractiveA() const;
        
                bool isDiffractiveB() const;
        
                bool isDiffractiveC() const;
        
                bool isNonDiffractive() const;
        
                bool isElastic() const;
        
                bool isMinBias() const;
        
                bool isLHA() const;
        
                bool atEndOfFile() const;
        
                bool hasSub(int i) const;
        
                bool hasSub() const;
        
                ::std::string nameSub(int i) const;
        
                ::std::string nameSub() const;
        
                int codeSub(int i) const;
        
                int codeSub() const;
        
                int nFinalSub(int i) const;
        
                int nFinalSub() const;
        
                int id1(int i) const;
        
                int id1() const;
        
                int id2(int i) const;
        
                int id2() const;
        
                double x1(int i) const;
        
                double x1() const;
        
                double x2(int i) const;
        
                double x2() const;
        
                double y(int i) const;
        
                double y() const;
        
                double tau(int i) const;
        
                double tau() const;
        
                int id1pdf(int i) const;
        
                int id1pdf() const;
        
                int id2pdf(int i) const;
        
                int id2pdf() const;
        
                double x1pdf(int i) const;
        
                double x1pdf() const;
        
                double x2pdf(int i) const;
        
                double x2pdf() const;
        
                double pdf1(int i) const;
        
                double pdf1() const;
        
                double pdf2(int i) const;
        
                double pdf2() const;
        
                double QFac(int i) const;
        
                double QFac() const;
        
                double Q2Fac(int i) const;
        
                double Q2Fac() const;
        
                bool isValence1() const;
        
                bool isValence2() const;
        
                double alphaS(int i) const;
        
                double alphaS() const;
        
                double alphaEM(int i) const;
        
                double alphaEM() const;
        
                double QRen(int i) const;
        
                double QRen() const;
        
                double Q2Ren(int i) const;
        
                double Q2Ren() const;
        
                double scalup(int i) const;
        
                double scalup() const;
        
                double xGammaA() const;
        
                double xGammaB() const;
        
                double Q2GammaA() const;
        
                double Q2GammaB() const;
        
                double eCMsub() const;
        
                double thetaScatLepA() const;
        
                double thetaScatLepB() const;
        
                double sHatNew() const;
        
                int photonMode() const;
        
                bool isVMDstateA() const;
        
                bool isVMDstateB() const;
        
                int idVMDA() const;
        
                int idVMDB() const;
        
                double mVMDA() const;
        
                double mVMDB() const;
        
                double scaleVMDA() const;
        
                double scaleVMDB() const;
        
                double mHat(int i) const;
        
                double mHat() const;
        
                double sHat(int i) const;
        
                double sHat() const;
        
                double tHat(int i) const;
        
                double tHat() const;
        
                double uHat(int i) const;
        
                double uHat() const;
        
                double pTHat(int i) const;
        
                double pTHat() const;
        
                double pT2Hat(int i) const;
        
                double pT2Hat() const;
        
                double m3Hat(int i) const;
        
                double m3Hat() const;
        
                double m4Hat(int i) const;
        
                double m4Hat() const;
        
                double thetaHat(int i) const;
        
                double thetaHat() const;
        
                double phiHat(int i) const;
        
                double phiHat() const;
        
                double weight(int i) const;
        
                double weight() const;
        
                double weightSum() const;
        
                double lhaStrategy() const;
        
                int nWeights() const;
        
                ::std::string weightLabel(int iWgt) const;
        
                int nWeightGroups() const;
        
                ::std::string getGroupName(int iGN) const;
        
                double getGroupWeight(int iGW) const;
        
                int nISR() const;
        
                int nFSRinProc() const;
        
                int nFSRinRes() const;
        
                double pTmaxMPI() const;
        
                double pTmaxISR() const;
        
                double pTmaxFSR() const;
        
                double pTnow() const;
        
                double a0MPI() const;
        
                double bMPI() const;
        
                double enhanceMPI() const;
        
                double enhanceMPIavg() const;
        
                double eMPI(int i) const;
        
                double bMPIold() const;
        
                double enhanceMPIold() const;
        
                double enhanceMPIoldavg() const;
        
                int nMPI() const;
        
                int codeMPI(int i) const;
        
                double pTMPI(int i) const;
        
                int iAMPI(int i) const;
        
                int iBMPI(int i) const;
        
                ::std::vector<int> codesHard() const;
        
                ::std::string nameProc(int i) const;
        
                ::std::string nameProc() const;
        
                long int nTried(int i) const;
        
                long int nTried() const;
        
                long int nSelected(int i) const;
        
                long int nSelected() const;
        
                long int nAccepted(int i) const;
        
                long int nAccepted() const;
        
                double sigmaGen(int i) const;
        
                double sigmaGen() const;
        
                double sigmaErr(int i) const;
        
                double sigmaErr() const;
        
                int getCounter(int i) const;
        
                void setCounter(int i, int value);
        
                void setCounter(int i);
        
                void addCounter(int i, int value);
        
                void addCounter(int i);
        
                void setTooLowPTmin(bool lowPTminIn);
        
                void setValence(bool isVal1In, bool isVal2In);
        
                void hasHistory(bool hasHistoryIn);
        
                bool hasHistory();
        
                void zNowISR(double zNowIn);
        
                double zNowISR();
        
                void pT2NowISR(double pT2NowIn);
        
                double pT2NowISR();
        
                double mergingWeight(int i) const;
        
                double mergingWeight() const;
        
                double mergingWeightNLO(int i) const;
        
                double mergingWeightNLO() const;
        
                ::std::string header(const std::string& key) const;
        
                ::std::vector<std::string> headerKeys() const;
        
                int nProcessesLHEF() const;
        
                double sigmaLHEF(int iProcess) const;
        
                void setLHEF3InitInfo();
        
                void setLHEF3EventInfo();
        
                ::std::string getEventAttribute(std::string key, bool doRemoveWhitespace) const;
        
                ::std::string getEventAttribute(std::string key) const;
        
                void setEventAttribute(std::string key, std::string value, bool doOverwrite);
        
                void setEventAttribute(std::string key, std::string value);
        
                int LHEFversion() const;
        
                unsigned int getInitrwgtSize() const;
        
                unsigned int getGeneratorSize() const;
        
                ::std::string getGeneratorValue(unsigned int n) const;
        
                ::std::string getGeneratorValue() const;
        
                ::std::string getGeneratorAttribute(unsigned int n, std::string key, bool doRemoveWhitespace) const;
        
                ::std::string getGeneratorAttribute(unsigned int n, std::string key) const;
        
                unsigned int getWeightsDetailedSize() const;
        
                double getWeightsDetailedValue(std::string n) const;
        
                ::std::string getWeightsDetailedAttribute(std::string n, std::string key, bool doRemoveWhitespace) const;
        
                ::std::string getWeightsDetailedAttribute(std::string n, std::string key) const;
        
                unsigned int getWeightsCompressedSize() const;
        
                double getWeightsCompressedValue(unsigned int n) const;
        
                ::std::string getWeightsCompressedAttribute(std::string key, bool doRemoveWhitespace) const;
        
                ::std::string getWeightsCompressedAttribute(std::string key) const;
        
                ::std::string getScalesValue(bool doRemoveWhitespace) const;
        
                ::std::string getScalesValue() const;
        
                double getScalesAttribute(std::string key) const;
        
                ::std::string getHeaderBlock() const;
        
                ::std::string getEventComments() const;
        
                void setHeader(const std::string& key, const std::string& val);
        
                void setAbortPartonLevel(bool abortIn);
        
                bool getAbortPartonLevel() const;
        
                bool hasUnresolvedBeams() const;
        
                bool hasPomPsystem() const;
        
                bool isHardDiffractive() const;
        
                bool isHardDiffractiveA() const;
        
                bool isHardDiffractiveB() const;
        
                double xPomeronA() const;
        
                double xPomeronB() const;
        
                double tPomeronA() const;
        
                double tPomeronB() const;
        
                ::std::vector<int> getWeakModes() const;
        
                ::std::vector<std::pair<int, int>> getWeakDipoles() const;
        
                ::std::vector<int> getWeak2to2lines() const;
        
                void setWeakModes(std::vector<int> weakModesIn);
        
                void setWeakDipoles(std::vector<std::pair<int, int>> weakDipolesIn);
        
                void setWeak2to2lines(std::vector<int> weak2to2linesIn);
        
                void setOniumShower(bool oniumShowerIn);
        
                bool getOniumShower() const;
        
                void setBeamIDs(int idAin, int idBin);
        
                void setBeamA(int idAin, double pzAin, double eAin, double mAin);
        
                void setBeamB(int idBin, double pzBin, double eBin, double mBin);
        
                void setECM(double eCMin);
        
                void setX1Gamma(double x1GammaIn);
        
                void setX2Gamma(double x2GammaIn);
        
                void setQ2Gamma1(double Q2gammaIn);
        
                void setQ2Gamma2(double Q2gammaIn);
        
                void setTheta1(double theta1In);
        
                void setTheta2(double theta2In);
        
                void setECMsub(double eCMsubIn);
        
                void setsHatNew(double sHatNewIn);
        
                void setGammaMode(double gammaModeIn);
        
                void setVMDstateA(bool isVMDAIn, int idAIn, double mAIn, double scaleAIn);
        
                void setVMDstateB(bool isVMDBIn, int idBIn, double mBIn, double scaleBIn);
        
                void clear();
        
                int sizeMPIarrays() const;
        
                void resizeMPIarrays(int newSize);
        
                void setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin, bool isDiffractiveBin, bool isDiffractiveCin, bool isLHAin);
        
                void setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin, bool isDiffractiveBin, bool isDiffractiveCin);
        
                void setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin, bool isDiffractiveBin);
        
                void setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn, bool isDiffractiveAin);
        
                void setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn, bool isResolvedIn);
        
                void setType(std::string nameIn, int codeIn, int nFinalIn, bool isNonDiffIn);
        
                void setType(std::string nameIn, int codeIn, int nFinalIn);
        
                void setSubType(int iDS, std::string nameSubIn, int codeSubIn, int nFinalSubIn);
        
                void setPDFalpha(int iDS, int id1pdfIn, int id2pdfIn, double x1pdfIn, double x2pdfIn, double pdf1In, double pdf2In, double Q2FacIn, double alphaEMIn, double alphaSIn, double Q2RenIn, double scalupIn);
        
                void setScalup(int iDS, double scalupIn);
        
                void setKin(int iDS, int id1In, int id2In, double x1In, double x2In, double sHatIn, double tHatIn, double uHatIn, double pTHatIn, double m3HatIn, double m4HatIn, double thetaHatIn, double phiHatIn);
        
                void setTypeMPI(int codeMPIIn, double pTMPIIn, int iAMPIIn, int iBMPIIn, double eMPIIn);
        
                void setTypeMPI(int codeMPIIn, double pTMPIIn, int iAMPIIn, int iBMPIIn);
        
                void setTypeMPI(int codeMPIIn, double pTMPIIn, int iAMPIIn);
        
                void setTypeMPI(int codeMPIIn, double pTMPIIn);
        
                void sigmaReset();
        
                void setSigma(int i, std::string procNameIn, long int nTryIn, long int nSelIn, long int nAccIn, double sigGenIn, double sigErrIn, double wtAccSumIn);
        
                void addSigma(int i, long int nTryIn, long int nSelIn, long int nAccIn, double sigGenIn, double sigErrIn);
        
                void setImpact(double bMPIIn, double enhanceMPIIn, double enhanceMPIavgIn, bool bIsSetIn, bool pushBack);
        
                void setImpact(double bMPIIn, double enhanceMPIIn, double enhanceMPIavgIn, bool bIsSetIn);
        
                void setImpact(double bMPIIn, double enhanceMPIIn, double enhanceMPIavgIn);
        
                void setPartEvolved(int nMPIIn, int nISRIn);
        
                void setEvolution(double pTmaxMPIIn, double pTmaxISRIn, double pTmaxFSRIn, int nMPIIn, int nISRIn, int nFSRinProcIn, int nFSRinResIn);
        
                void setPTnow(double pTnowIn);
        
                void seta0MPI(double a0MPIin);
        
                void setEndOfFile(bool atEOFin);
        
                void setWeight(double weightIn, int lhaStrategyIn);
        
                void setIsResolved(bool isResIn);
        
                void setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn, double xPomBIn, double tPomAIn, double tPomBIn);
        
                void setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn, double xPomBIn, double tPomAIn);
        
                void setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn, double xPomBIn);
        
                void setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn, double xPomAIn);
        
                void setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn, bool isHardDiffBIn);
        
                void setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn, bool isHardDiffAIn);
        
                void setHardDiff(bool hasUnresBeamsIn, bool hasPomPsysIn);
        
                void setHardDiff(bool hasUnresBeamsIn);
        
                void setHardDiff();
        
                void reassignDiffSystem(int iDSold, int iDSnew);
        
                void setHasUnresolvedBeams(bool hasUnresBeamsIn);
        
                void setHasPomPsystem(bool hasPomPsysIn);
        
                int numberOfWeights() const;
        
                double weightValueByIndex(int key) const;
        
                double weightValueByIndex() const;
        
                ::std::string weightNameByIndex(int key) const;
        
                ::std::string weightNameByIndex() const;
        
                ::std::vector<double> weightValueVector() const;
        
                ::std::vector<std::string> weightNameVector() const;
        
        
                // Wrappers for original constructors: 
            public:
                Info();
                Info(bool arg_1);
        
                // Special pointer-based constructor: 
                Info(Abstract_Info* in);
        
                // Copy constructor: 
                Info(const Info& in);
        
                // Assignment operator: 
                Info& operator=(const Info& in);
        
                // Destructor: 
                ~Info();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Info* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Info_decl_Pythia_8_312_h__ */
