#ifndef __abstract_Info_Pythia_8_212_h__
#define __abstract_Info_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Info : public virtual AbstractBase
        {
            public:
    
                virtual void list(std::ostream&) const =0;
    
                virtual void list__BOSS() const =0;
    
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
    
                virtual double weight() const =0;
    
                virtual double weightSum() const =0;
    
                virtual double lhaStrategy() const =0;
    
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
    
                virtual double eMPI(int) const =0;
    
                virtual int nMPI() const =0;
    
                virtual int codeMPI(int) const =0;
    
                virtual double pTMPI(int) const =0;
    
                virtual int iAMPI(int) const =0;
    
                virtual int iBMPI(int) const =0;
    
                virtual ::std::vector<int> codesHard() =0;
    
                virtual ::std::string nameProc(int) =0;
    
                virtual ::std::string nameProc__BOSS() =0;
    
                virtual long int nTried(int) =0;
    
                virtual long int nTried__BOSS() =0;
    
                virtual long int nSelected(int) =0;
    
                virtual long int nSelected__BOSS() =0;
    
                virtual long int nAccepted(int) =0;
    
                virtual long int nAccepted__BOSS() =0;
    
                virtual double sigmaGen(int) =0;
    
                virtual double sigmaGen__BOSS() =0;
    
                virtual double sigmaErr(int) =0;
    
                virtual double sigmaErr__BOSS() =0;
    
                virtual int getCounter(int) const =0;
    
                virtual void setCounter(int, int) =0;
    
                virtual void setCounter__BOSS(int) =0;
    
                virtual void addCounter(int, int) =0;
    
                virtual void addCounter__BOSS(int) =0;
    
                virtual void errorReset() =0;
    
                virtual void errorMsg(std::string, std::string, bool, std::ostream&) =0;
    
                virtual void errorMsg__BOSS(std::string, std::string, bool) =0;
    
                virtual void errorMsg__BOSS(std::string, std::string) =0;
    
                virtual void errorMsg__BOSS(std::string) =0;
    
                virtual int errorTotalNumber() =0;
    
                virtual void errorStatistics(std::ostream&) =0;
    
                virtual void errorStatistics__BOSS() =0;
    
                virtual void setTooLowPTmin(bool) =0;
    
                virtual void setValence(bool, bool) =0;
    
                virtual void hasHistory(bool) =0;
    
                virtual bool hasHistory() =0;
    
                virtual void zNowISR(double) =0;
    
                virtual double zNowISR() =0;
    
                virtual void pT2NowISR(double) =0;
    
                virtual double pT2NowISR() =0;
    
                virtual double getWeightCKKWL() const =0;
    
                virtual void setWeightCKKWL(double) =0;
    
                virtual double mergingWeight() const =0;
    
                virtual double mergingWeightNLO() const =0;
    
                virtual double getWeightFIRST() const =0;
    
                virtual void setWeightFIRST(double) =0;
    
                virtual ::std::string header(const std::string&) =0;
    
                virtual ::std::vector<std::string> headerKeys() =0;
    
                virtual int nProcessesLHEF() =0;
    
                virtual double sigmaLHEF(int) =0;
    
                virtual int& LHEFversionSave_ref__BOSS() =0;
    
                virtual std::vector<double>& sigmaLHEFSave_ref__BOSS() =0;
    
                virtual std::map<std::string, std::string>*& eventAttributes_ref__BOSS() =0;
    
                virtual std::map<std::string, double>*& weights_detailed_ref__BOSS() =0;
    
                virtual std::vector<double>*& weights_compressed_ref__BOSS() =0;
    
                virtual void setLHEF3InitInfo() =0;
    
                virtual void setLHEF3EventInfo() =0;
    
                virtual ::std::string getEventAttribute(std::string, bool) =0;
    
                virtual ::std::string getEventAttribute__BOSS(std::string) =0;
    
                virtual int LHEFversion() =0;
    
                virtual unsigned int getInitrwgtSize() =0;
    
                virtual unsigned int getGeneratorSize() =0;
    
                virtual ::std::string getGeneratorValue(unsigned int) =0;
    
                virtual ::std::string getGeneratorValue__BOSS() =0;
    
                virtual ::std::string getGeneratorAttribute(unsigned int, std::string, bool) =0;
    
                virtual ::std::string getGeneratorAttribute__BOSS(unsigned int, std::string) =0;
    
                virtual unsigned int getWeightsDetailedSize() =0;
    
                virtual double getWeightsDetailedValue(std::string) =0;
    
                virtual ::std::string getWeightsDetailedAttribute(std::string, std::string, bool) =0;
    
                virtual ::std::string getWeightsDetailedAttribute__BOSS(std::string, std::string) =0;
    
                virtual unsigned int getWeightsCompressedSize() =0;
    
                virtual double getWeightsCompressedValue(unsigned int) =0;
    
                virtual ::std::string getWeightsCompressedAttribute(std::string, bool) =0;
    
                virtual ::std::string getWeightsCompressedAttribute__BOSS(std::string) =0;
    
                virtual ::std::string getScalesValue(bool) =0;
    
                virtual ::std::string getScalesValue__BOSS() =0;
    
                virtual double getScalesAttribute(std::string) =0;
    
                virtual void setHeader(const std::string&, const std::string&) =0;
    
                virtual void setAbortPartonLevel(bool) =0;
    
                virtual bool getAbortPartonLevel() =0;
    
                virtual bool hasUnresolvedBeams() const =0;
    
                virtual bool hasPomPsystem() const =0;
    
                virtual bool isHardDiffractive() const =0;
    
                virtual bool isHardDiffractiveA() const =0;
    
                virtual bool isHardDiffractiveB() const =0;
    
                virtual double xPomeronA() const =0;
    
                virtual double xPomeronB() const =0;
    
                virtual double tPomeronA() const =0;
    
                virtual double tPomeronB() const =0;
    
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


#endif /* __abstract_Info_Pythia_8_212_h__ */
