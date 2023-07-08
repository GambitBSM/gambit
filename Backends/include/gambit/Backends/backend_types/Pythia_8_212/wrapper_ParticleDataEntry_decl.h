#ifndef __wrapper_ParticleDataEntry_decl_Pythia_8_212_h__
#define __wrapper_ParticleDataEntry_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ParticleDataEntry.h"
#include "wrapper_DecayChannel_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Couplings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class ParticleDataEntry : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_ParticleDataEntry* (*__factory0)(int, std::string, int, int, int, double, double, double, double, double);
                static Abstract_ParticleDataEntry* (*__factory1)(int, std::string, int, int, int, double, double, double, double);
                static Abstract_ParticleDataEntry* (*__factory2)(int, std::string, int, int, int, double, double, double);
                static Abstract_ParticleDataEntry* (*__factory3)(int, std::string, int, int, int, double, double);
                static Abstract_ParticleDataEntry* (*__factory4)(int, std::string, int, int, int, double);
                static Abstract_ParticleDataEntry* (*__factory5)(int, std::string, int, int, int);
                static Abstract_ParticleDataEntry* (*__factory6)(int, std::string, int, int);
                static Abstract_ParticleDataEntry* (*__factory7)(int, std::string, int);
                static Abstract_ParticleDataEntry* (*__factory8)(int, std::string);
                static Abstract_ParticleDataEntry* (*__factory9)(int);
                static Abstract_ParticleDataEntry* (*__factory10)();
                static Abstract_ParticleDataEntry* (*__factory11)(int, std::string, std::string, int, int, int, double, double, double, double, double);
                static Abstract_ParticleDataEntry* (*__factory12)(int, std::string, std::string, int, int, int, double, double, double, double);
                static Abstract_ParticleDataEntry* (*__factory13)(int, std::string, std::string, int, int, int, double, double, double);
                static Abstract_ParticleDataEntry* (*__factory14)(int, std::string, std::string, int, int, int, double, double);
                static Abstract_ParticleDataEntry* (*__factory15)(int, std::string, std::string, int, int, int, double);
                static Abstract_ParticleDataEntry* (*__factory16)(int, std::string, std::string, int, int, int);
                static Abstract_ParticleDataEntry* (*__factory17)(int, std::string, std::string, int, int);
                static Abstract_ParticleDataEntry* (*__factory18)(int, std::string, std::string, int);
                static Abstract_ParticleDataEntry* (*__factory19)(int, std::string, std::string);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void setDefaults();
        
                void initPtr(Pythia8::ParticleData* particleDataPtrIn);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn);
        
                void setAll(std::string nameIn, std::string antiNameIn, int spinTypeIn);
        
                void setAll(std::string nameIn, std::string antiNameIn);
        
                void setName(std::string nameIn);
        
                void setAntiName(std::string antiNameIn);
        
                void setNames(std::string nameIn, std::string antiNameIn);
        
                void setSpinType(int spinTypeIn);
        
                void setChargeType(int chargeTypeIn);
        
                void setColType(int colTypeIn);
        
                void setM0(double m0In);
        
                void setMWidth(double mWidthIn, bool countAsChanged);
        
                void setMWidth(double mWidthIn);
        
                void setMMin(double mMinIn);
        
                void setMMax(double mMaxIn);
        
                void setMMinNoChange(double mMinIn);
        
                void setMMaxNoChange(double mMaxIn);
        
                void setTau0(double tau0In);
        
                void setIsResonance(bool isResonanceIn);
        
                void setMayDecay(bool mayDecayIn, bool countAsChanged);
        
                void setMayDecay(bool mayDecayIn);
        
                void setDoExternalDecay(bool doExternalDecayIn);
        
                void setIsVisible(bool isVisibleIn);
        
                void setDoForceWidth(bool doForceWidthIn);
        
                void setHasChanged(bool hasChangedIn);
        
                int id() const;
        
                bool hasAnti() const;
        
                ::std::string name(int idIn) const;
        
                ::std::string name() const;
        
                int spinType() const;
        
                int chargeType(int idIn) const;
        
                int chargeType() const;
        
                double charge(int idIn) const;
        
                double charge() const;
        
                int colType(int idIn) const;
        
                int colType() const;
        
                double m0() const;
        
                double mWidth() const;
        
                double mMin() const;
        
                double mMax() const;
        
                double m0Min() const;
        
                double m0Max() const;
        
                double tau0() const;
        
                bool isResonance() const;
        
                bool mayDecay() const;
        
                bool doExternalDecay() const;
        
                bool isVisible() const;
        
                bool doForceWidth() const;
        
                bool hasChanged() const;
        
                void initBWmass();
        
                double constituentMass() const;
        
                double mSel();
        
                double mRun(double mH);
        
                bool useBreitWigner() const;
        
                bool canDecay() const;
        
                bool isLepton() const;
        
                bool isQuark() const;
        
                bool isGluon() const;
        
                bool isDiquark() const;
        
                bool isParton() const;
        
                bool isHadron() const;
        
                bool isMeson() const;
        
                bool isBaryon() const;
        
                bool isOctetHadron() const;
        
                int heaviestQuark(int idIn) const;
        
                int heaviestQuark() const;
        
                int baryonNumberType(int idIn) const;
        
                int baryonNumberType() const;
        
                void clearChannels();
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6, int prod7);
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6);
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5);
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4);
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3);
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2);
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1);
        
                void addChannel(int onMode, double bRatio, int meMode, int prod0);
        
                void addChannel(int onMode, double bRatio, int meMode);
        
                void addChannel(int onMode, double bRatio);
        
                void addChannel(int onMode);
        
                void addChannel();
        
                int sizeChannels() const;
        
                Pythia8::DecayChannel& channel(int i);
        
                const Pythia8::DecayChannel& channel(int i) const;
        
                void rescaleBR(double newSumBR);
        
                void rescaleBR();
        
                bool preparePick(int idSgn, double mHat, int idInFlav);
        
                bool preparePick(int idSgn, double mHat);
        
                bool preparePick(int idSgn);
        
                Pythia8::DecayChannel& pickChannel();
        
                void setResonancePtr(Pythia8::ResonanceWidths* resonancePtrIn);
        
                Pythia8::ResonanceWidths* getResonancePtr();
        
                void resInit(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Couplings* couplingsPtrIn);
        
                double resWidth(int idSgn, double mHat, int idIn, bool openOnly, bool setBR);
        
                double resWidth(int idSgn, double mHat, int idIn, bool openOnly);
        
                double resWidth(int idSgn, double mHat, int idIn);
        
                double resWidth(int idSgn, double mHat);
        
                double resWidthOpen(int idSgn, double mHat, int idIn);
        
                double resWidthOpen(int idSgn, double mHat);
        
                double resWidthStore(int idSgn, double mHat, int idIn);
        
                double resWidthStore(int idSgn, double mHat);
        
                double resOpenFrac(int idSgn);
        
                double resWidthRescaleFactor();
        
                double resWidthChan(double mHat, int idAbs1, int idAbs2);
        
                double resWidthChan(double mHat, int idAbs1);
        
                double resWidthChan(double mHat);
        
        
                // Wrappers for original constructors: 
            public:
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn);
                ParticleDataEntry(int idIn, std::string nameIn, int spinTypeIn);
                ParticleDataEntry(int idIn, std::string nameIn);
                ParticleDataEntry(int idIn);
                ParticleDataEntry();
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn);
                ParticleDataEntry(int idIn, std::string nameIn, std::string antiNameIn);
        
                // Special pointer-based constructor: 
                ParticleDataEntry(Abstract_ParticleDataEntry* in);
        
                // Copy constructor: 
                ParticleDataEntry(const ParticleDataEntry& in);
        
                // Assignment operator: 
                ParticleDataEntry& operator=(const ParticleDataEntry& in);
        
                // Destructor: 
                ~ParticleDataEntry();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_ParticleDataEntry* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ParticleDataEntry_decl_Pythia_8_212_h__ */
