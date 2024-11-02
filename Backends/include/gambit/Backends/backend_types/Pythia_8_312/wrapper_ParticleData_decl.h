#ifndef __wrapper_ParticleData_decl_Pythia_8_312_h__
#define __wrapper_ParticleData_decl_Pythia_8_312_h__

#include <cstddef>
#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <map>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ParticleData.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_CoupSM_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class ParticleData : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_ParticleData* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void initPtrs(Pythia8::Info* infoPtrIn);
        
                bool init(std::string startFile);
        
                bool init();
        
                bool init(const Pythia8::ParticleData& particleDataIn);
        
                bool init(std::istream& is);
        
                bool reInit(std::string startFile, bool xmlFormat);
        
                bool reInit(std::string startFile);
        
                bool readXML(std::string inFile, bool reset);
        
                bool readXML(std::string inFile);
        
                void listXML(std::string outFile);
        
                bool readXML(std::istream& is, bool reset);
        
                bool readXML(std::istream& is);
        
                bool copyXML(const Pythia8::ParticleData& particleDataIn);
        
                bool loadXML(std::string inFile, bool reset);
        
                bool loadXML(std::string inFile);
        
                bool loadXML(std::istream& is, bool reset);
        
                bool loadXML(std::istream& is);
        
                bool processXML(bool reset);
        
                bool processXML();
        
                bool readFF(std::string inFile, bool reset);
        
                bool readFF(std::string inFile);
        
                bool readFF(std::istream& is, bool reset);
        
                bool readFF(std::istream& is);
        
                void listFF(std::string outFile);
        
                bool readString(std::string lineIn, bool warn);
        
                bool readString(std::string lineIn);
        
                bool readingFailed();
        
                void listAll(std::ostream& stream);
        
                void listAll();
        
                void listChanged(bool changedRes);
        
                void listChanged();
        
                void list(std::ostream& stream, bool chargedOnly, bool changedRes);
        
                void list(std::ostream& stream, bool chargedOnly);
        
                void list(std::ostream& stream);
        
                void list(bool changedOnly, bool changedRes);
        
                void list(bool changedOnly);
        
                void list();
        
                void list(int idList);
        
                void list(std::vector<int> idList);
        
                ::std::vector<std::string> getReadHistory(int subrun);
        
                ::std::vector<std::string> getReadHistory();
        
                void checkTable(int verbosity);
        
                void checkTable();
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In, bool varWidthIn);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn);
        
                void addParticle(int idIn, std::string nameIn, int spinTypeIn);
        
                void addParticle(int idIn, std::string nameIn);
        
                void addParticle(int idIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In, bool varWidthIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In, bool varWidthIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn);
        
                bool isParticle(int idIn) const;
        
                int nextId(int idIn) const;
        
                void name(int idIn, std::string nameIn);
        
                void antiName(int idIn, std::string antiNameIn);
        
                void names(int idIn, std::string nameIn, std::string antiNameIn);
        
                void spinType(int idIn, int spinTypeIn);
        
                void chargeType(int idIn, int chargeTypeIn);
        
                void colType(int idIn, int colTypeIn);
        
                void m0(int idIn, double m0In);
        
                void mWidth(int idIn, double mWidthIn);
        
                void mMin(int idIn, double mMinIn);
        
                void mMax(int idIn, double mMaxIn);
        
                void tau0(int idIn, double tau0In);
        
                void isResonance(int idIn, bool isResonanceIn);
        
                void mayDecay(int idIn, bool mayDecayIn);
        
                void tauCalc(int idIn, bool tauCalcIn);
        
                void doExternalDecay(int idIn, bool doExternalDecayIn);
        
                void varWidth(int idIn, bool varWidthIn);
        
                void isVisible(int idIn, bool isVisibleIn);
        
                void doForceWidth(int idIn, bool doForceWidthIn);
        
                void hasChanged(int idIn, bool hasChangedIn);
        
                bool hasAnti(int idIn) const;
        
                int antiId(int idIn) const;
        
                ::std::string name(int idIn) const;
        
                int spinType(int idIn) const;
        
                int chargeType(int idIn) const;
        
                double charge(int idIn) const;
        
                int colType(int idIn) const;
        
                double m0(int idIn) const;
        
                double mWidth(int idIn) const;
        
                double mMin(int idIn) const;
        
                double m0Min(int idIn) const;
        
                double mMax(int idIn) const;
        
                double m0Max(int idIn) const;
        
                double tau0(int idIn) const;
        
                bool isResonance(int idIn) const;
        
                bool mayDecay(int idIn) const;
        
                bool tauCalc(int idIn) const;
        
                bool doExternalDecay(int idIn) const;
        
                bool isVisible(int idIn) const;
        
                bool doForceWidth(int idIn) const;
        
                bool hasChanged(int idIn) const;
        
                bool hasChangedMMin(int idIn) const;
        
                bool hasChangedMMax(int idIn) const;
        
                bool useBreitWigner(int idIn) const;
        
                bool varWidth(int idIn) const;
        
                double constituentMass(int idIn) const;
        
                double mSel(int idIn) const;
        
                double mRun(int idIn, double mH) const;
        
                bool canDecay(int idIn) const;
        
                bool isLepton(int idIn) const;
        
                bool isQuark(int idIn) const;
        
                bool isGluon(int idIn) const;
        
                bool isDiquark(int idIn) const;
        
                bool isParton(int idIn) const;
        
                bool isHadron(int idIn) const;
        
                bool isMeson(int idIn) const;
        
                bool isBaryon(int idIn) const;
        
                bool isOnium(int idIn) const;
        
                bool isExotic(int idIn) const;
        
                bool isOctetHadron(int idIn) const;
        
                int heaviestQuark(int idIn) const;
        
                int baryonNumberType(int idIn) const;
        
                int nQuarksInCode(int idIn, int idQIn) const;
        
                void rescaleBR(int idIn, double newSumBR);
        
                void rescaleBR(int idIn);
        
                void resInit(int idIn);
        
                double resWidth(int idIn, double mHat, int idInFlav, bool openOnly, bool setBR);
        
                double resWidth(int idIn, double mHat, int idInFlav, bool openOnly);
        
                double resWidth(int idIn, double mHat, int idInFlav);
        
                double resWidth(int idIn, double mHat);
        
                double resWidthOpen(int idIn, double mHat, int idInFlav);
        
                double resWidthOpen(int idIn, double mHat);
        
                double resWidthStore(int idIn, double mHat, int idInFlav);
        
                double resWidthStore(int idIn, double mHat);
        
                double resOpenFrac(int id1In, int id2In, int id3In);
        
                double resOpenFrac(int id1In, int id2In);
        
                double resOpenFrac(int id1In);
        
                double resWidthRescaleFactor(int idIn);
        
                double resWidthChan(int idIn, double mHat, int idAbs1, int idAbs2);
        
                double resWidthChan(int idIn, double mHat, int idAbs1);
        
                double resWidthChan(int idIn, double mHat);
        
                bool getIsInit();
        
        
                // Wrappers for original constructors: 
            public:
                ParticleData();
        
                // Special pointer-based constructor: 
                ParticleData(Abstract_ParticleData* in);
        
                // Copy constructor: 
                ParticleData(const ParticleData& in);
        
                // Assignment operator: 
                ParticleData& operator=(const ParticleData& in);
        
                // Destructor: 
                ~ParticleData();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_ParticleData* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ParticleData_decl_Pythia_8_312_h__ */
