#ifndef __wrapper_ParticleData_decl_Pythia_8_212_h__
#define __wrapper_ParticleData_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include <ostream>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ParticleData.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_ParticleDataEntry_decl.h"

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
                void initPtr(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::Couplings* couplingsPtrIn);
        
                bool init(std::string startFile);
        
                bool init();
        
                bool init(const Pythia8::ParticleData& particleDataIn);
        
                bool reInit(std::string startFile, bool xmlFormat);
        
                bool reInit(std::string startFile);
        
                bool readXML(std::string inFile, bool reset);
        
                bool readXML(std::string inFile);
        
                void listXML(std::string outFile);
        
                bool copyXML(const Pythia8::ParticleData& particleDataIn);
        
                bool loadXML(std::string inFile, bool reset);
        
                bool loadXML(std::string inFile);
        
                bool processXML(bool reset);
        
                bool processXML();
        
                bool readFF(std::string inFile, bool reset);
        
                bool readFF(std::string inFile);
        
                void listFF(std::string outFile);
        
                bool readString(std::string lineIn, bool warn, std::ostream& os);
        
                bool readString(std::string lineIn, bool warn);
        
                bool readString(std::string lineIn);
        
                bool readingFailed();
        
                void listAll(std::ostream& os);
        
                void listAll();
        
                void listChanged(std::ostream& os);
        
                void listChanged();
        
                void listChanged(bool changedRes, std::ostream& os);
        
                void listChanged(bool changedRes);
        
                void list(bool changedOnly, bool changedRes, std::ostream& os);
        
                void list(bool changedOnly, bool changedRes);
        
                void list(bool changedOnly);
        
                void list();
        
                void list(int idList, std::ostream& os);
        
                void list(int idList);
        
                void list(std::vector<int> idList, std::ostream& os);
        
                void list(std::vector<int> idList);
        
                void checkTable(std::ostream& os);
        
                void checkTable();
        
                void checkTable(int verbosity, std::ostream& os);
        
                void checkTable(int verbosity);
        
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
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn);
        
                void addParticle(int idIn, std::string nameIn, std::string antiNameIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn);
        
                void setAll(int idIn, std::string nameIn, std::string antiNameIn);
        
                bool isParticle(int idIn);
        
                int nextId(int idIn);
        
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
        
                void doExternalDecay(int idIn, bool doExternalDecayIn);
        
                void isVisible(int idIn, bool isVisibleIn);
        
                void doForceWidth(int idIn, bool doForceWidthIn);
        
                void hasChanged(int idIn, bool hasChangedIn);
        
                bool hasAnti(int idIn);
        
                ::std::string name(int idIn);
        
                int spinType(int idIn);
        
                int chargeType(int idIn);
        
                double charge(int idIn);
        
                int colType(int idIn);
        
                double m0(int idIn);
        
                double mWidth(int idIn);
        
                double mMin(int idIn);
        
                double m0Min(int idIn);
        
                double mMax(int idIn);
        
                double m0Max(int idIn);
        
                double tau0(int idIn);
        
                bool isResonance(int idIn);
        
                bool mayDecay(int idIn);
        
                bool doExternalDecay(int idIn);
        
                bool isVisible(int idIn);
        
                bool doForceWidth(int idIn);
        
                bool hasChanged(int idIn);
        
                bool useBreitWigner(int idIn);
        
                double constituentMass(int idIn);
        
                double mSel(int idIn);
        
                double mRun(int idIn, double mH);
        
                bool canDecay(int idIn);
        
                bool isLepton(int idIn);
        
                bool isQuark(int idIn);
        
                bool isGluon(int idIn);
        
                bool isDiquark(int idIn);
        
                bool isParton(int idIn);
        
                bool isHadron(int idIn);
        
                bool isMeson(int idIn);
        
                bool isBaryon(int idIn);
        
                bool isOctetHadron(int idIn);
        
                int heaviestQuark(int idIn);
        
                int baryonNumberType(int idIn);
        
                void rescaleBR(int idIn, double newSumBR);
        
                void rescaleBR(int idIn);
        
                void setResonancePtr(int idIn, Pythia8::ResonanceWidths* resonancePtrIn);
        
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
        
                Pythia8::ParticleDataEntry* particleDataEntryPtr(int idIn);
        
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

#endif /* __wrapper_ParticleData_decl_Pythia_8_212_h__ */
