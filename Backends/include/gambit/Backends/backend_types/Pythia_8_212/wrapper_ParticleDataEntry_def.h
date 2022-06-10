#ifndef __wrapper_ParticleDataEntry_def_Pythia_8_212_h__
#define __wrapper_ParticleDataEntry_def_Pythia_8_212_h__

#include <string>
#include "wrapper_ParticleData_decl.h"
#include "wrapper_DecayChannel_decl.h"
#include "wrapper_ResonanceWidths_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Couplings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void ParticleDataEntry::setDefaults()
        {
            get_BEptr()->setDefaults();
        }
        
        inline void ParticleDataEntry::initPtr(Pythia8::ParticleData* particleDataPtrIn)
        {
            get_BEptr()->initPtr__BOSS((*particleDataPtrIn).get_BEptr());
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In)
        {
            get_BEptr()->setAll(nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn, spinTypeIn, chargeTypeIn);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn, spinTypeIn);
        }
        
        inline void ParticleDataEntry::setAll(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn)
        {
            get_BEptr()->setAll__BOSS(nameIn, antiNameIn);
        }
        
        inline void ParticleDataEntry::setName(::std::basic_string<char> nameIn)
        {
            get_BEptr()->setName(nameIn);
        }
        
        inline void ParticleDataEntry::setAntiName(::std::basic_string<char> antiNameIn)
        {
            get_BEptr()->setAntiName(antiNameIn);
        }
        
        inline void ParticleDataEntry::setNames(::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn)
        {
            get_BEptr()->setNames(nameIn, antiNameIn);
        }
        
        inline void ParticleDataEntry::setSpinType(int spinTypeIn)
        {
            get_BEptr()->setSpinType(spinTypeIn);
        }
        
        inline void ParticleDataEntry::setChargeType(int chargeTypeIn)
        {
            get_BEptr()->setChargeType(chargeTypeIn);
        }
        
        inline void ParticleDataEntry::setColType(int colTypeIn)
        {
            get_BEptr()->setColType(colTypeIn);
        }
        
        inline void ParticleDataEntry::setM0(double m0In)
        {
            get_BEptr()->setM0(m0In);
        }
        
        inline void ParticleDataEntry::setMWidth(double mWidthIn, bool countAsChanged)
        {
            get_BEptr()->setMWidth(mWidthIn, countAsChanged);
        }
        
        inline void ParticleDataEntry::setMWidth(double mWidthIn)
        {
            get_BEptr()->setMWidth__BOSS(mWidthIn);
        }
        
        inline void ParticleDataEntry::setMMin(double mMinIn)
        {
            get_BEptr()->setMMin(mMinIn);
        }
        
        inline void ParticleDataEntry::setMMax(double mMaxIn)
        {
            get_BEptr()->setMMax(mMaxIn);
        }
        
        inline void ParticleDataEntry::setMMinNoChange(double mMinIn)
        {
            get_BEptr()->setMMinNoChange(mMinIn);
        }
        
        inline void ParticleDataEntry::setMMaxNoChange(double mMaxIn)
        {
            get_BEptr()->setMMaxNoChange(mMaxIn);
        }
        
        inline void ParticleDataEntry::setTau0(double tau0In)
        {
            get_BEptr()->setTau0(tau0In);
        }
        
        inline void ParticleDataEntry::setIsResonance(bool isResonanceIn)
        {
            get_BEptr()->setIsResonance(isResonanceIn);
        }
        
        inline void ParticleDataEntry::setMayDecay(bool mayDecayIn, bool countAsChanged)
        {
            get_BEptr()->setMayDecay(mayDecayIn, countAsChanged);
        }
        
        inline void ParticleDataEntry::setMayDecay(bool mayDecayIn)
        {
            get_BEptr()->setMayDecay__BOSS(mayDecayIn);
        }
        
        inline void ParticleDataEntry::setDoExternalDecay(bool doExternalDecayIn)
        {
            get_BEptr()->setDoExternalDecay(doExternalDecayIn);
        }
        
        inline void ParticleDataEntry::setIsVisible(bool isVisibleIn)
        {
            get_BEptr()->setIsVisible(isVisibleIn);
        }
        
        inline void ParticleDataEntry::setDoForceWidth(bool doForceWidthIn)
        {
            get_BEptr()->setDoForceWidth(doForceWidthIn);
        }
        
        inline void ParticleDataEntry::setHasChanged(bool hasChangedIn)
        {
            get_BEptr()->setHasChanged(hasChangedIn);
        }
        
        inline int ParticleDataEntry::id() const
        {
            return get_BEptr()->id();
        }
        
        inline bool ParticleDataEntry::hasAnti() const
        {
            return get_BEptr()->hasAnti();
        }
        
        inline ::std::basic_string<char> ParticleDataEntry::name(int idIn) const
        {
            return get_BEptr()->name(idIn);
        }
        
        inline ::std::basic_string<char> ParticleDataEntry::name() const
        {
            return get_BEptr()->name__BOSS();
        }
        
        inline int ParticleDataEntry::spinType() const
        {
            return get_BEptr()->spinType();
        }
        
        inline int ParticleDataEntry::chargeType(int idIn) const
        {
            return get_BEptr()->chargeType(idIn);
        }
        
        inline int ParticleDataEntry::chargeType() const
        {
            return get_BEptr()->chargeType__BOSS();
        }
        
        inline double ParticleDataEntry::charge(int idIn) const
        {
            return get_BEptr()->charge(idIn);
        }
        
        inline double ParticleDataEntry::charge() const
        {
            return get_BEptr()->charge__BOSS();
        }
        
        inline int ParticleDataEntry::colType(int idIn) const
        {
            return get_BEptr()->colType(idIn);
        }
        
        inline int ParticleDataEntry::colType() const
        {
            return get_BEptr()->colType__BOSS();
        }
        
        inline double ParticleDataEntry::m0() const
        {
            return get_BEptr()->m0();
        }
        
        inline double ParticleDataEntry::mWidth() const
        {
            return get_BEptr()->mWidth();
        }
        
        inline double ParticleDataEntry::mMin() const
        {
            return get_BEptr()->mMin();
        }
        
        inline double ParticleDataEntry::mMax() const
        {
            return get_BEptr()->mMax();
        }
        
        inline double ParticleDataEntry::m0Min() const
        {
            return get_BEptr()->m0Min();
        }
        
        inline double ParticleDataEntry::m0Max() const
        {
            return get_BEptr()->m0Max();
        }
        
        inline double ParticleDataEntry::tau0() const
        {
            return get_BEptr()->tau0();
        }
        
        inline bool ParticleDataEntry::isResonance() const
        {
            return get_BEptr()->isResonance();
        }
        
        inline bool ParticleDataEntry::mayDecay() const
        {
            return get_BEptr()->mayDecay();
        }
        
        inline bool ParticleDataEntry::doExternalDecay() const
        {
            return get_BEptr()->doExternalDecay();
        }
        
        inline bool ParticleDataEntry::isVisible() const
        {
            return get_BEptr()->isVisible();
        }
        
        inline bool ParticleDataEntry::doForceWidth() const
        {
            return get_BEptr()->doForceWidth();
        }
        
        inline bool ParticleDataEntry::hasChanged() const
        {
            return get_BEptr()->hasChanged();
        }
        
        inline void ParticleDataEntry::initBWmass()
        {
            get_BEptr()->initBWmass();
        }
        
        inline double ParticleDataEntry::constituentMass() const
        {
            return get_BEptr()->constituentMass();
        }
        
        inline double ParticleDataEntry::mSel()
        {
            return get_BEptr()->mSel();
        }
        
        inline double ParticleDataEntry::mRun(double mH)
        {
            return get_BEptr()->mRun(mH);
        }
        
        inline bool ParticleDataEntry::useBreitWigner() const
        {
            return get_BEptr()->useBreitWigner();
        }
        
        inline bool ParticleDataEntry::canDecay() const
        {
            return get_BEptr()->canDecay();
        }
        
        inline bool ParticleDataEntry::isLepton() const
        {
            return get_BEptr()->isLepton();
        }
        
        inline bool ParticleDataEntry::isQuark() const
        {
            return get_BEptr()->isQuark();
        }
        
        inline bool ParticleDataEntry::isGluon() const
        {
            return get_BEptr()->isGluon();
        }
        
        inline bool ParticleDataEntry::isDiquark() const
        {
            return get_BEptr()->isDiquark();
        }
        
        inline bool ParticleDataEntry::isParton() const
        {
            return get_BEptr()->isParton();
        }
        
        inline bool ParticleDataEntry::isHadron() const
        {
            return get_BEptr()->isHadron();
        }
        
        inline bool ParticleDataEntry::isMeson() const
        {
            return get_BEptr()->isMeson();
        }
        
        inline bool ParticleDataEntry::isBaryon() const
        {
            return get_BEptr()->isBaryon();
        }
        
        inline bool ParticleDataEntry::isOctetHadron() const
        {
            return get_BEptr()->isOctetHadron();
        }
        
        inline int ParticleDataEntry::heaviestQuark(int idIn) const
        {
            return get_BEptr()->heaviestQuark(idIn);
        }
        
        inline int ParticleDataEntry::heaviestQuark() const
        {
            return get_BEptr()->heaviestQuark__BOSS();
        }
        
        inline int ParticleDataEntry::baryonNumberType(int idIn) const
        {
            return get_BEptr()->baryonNumberType(idIn);
        }
        
        inline int ParticleDataEntry::baryonNumberType() const
        {
            return get_BEptr()->baryonNumberType__BOSS();
        }
        
        inline void ParticleDataEntry::clearChannels()
        {
            get_BEptr()->clearChannels();
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6, int prod7)
        {
            get_BEptr()->addChannel(onMode, bRatio, meMode, prod0, prod1, prod2, prod3, prod4, prod5, prod6, prod7);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5, int prod6)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode, prod0, prod1, prod2, prod3, prod4, prod5, prod6);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4, int prod5)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode, prod0, prod1, prod2, prod3, prod4, prod5);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3, int prod4)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode, prod0, prod1, prod2, prod3, prod4);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2, int prod3)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode, prod0, prod1, prod2, prod3);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1, int prod2)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode, prod0, prod1, prod2);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0, int prod1)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode, prod0, prod1);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode, int prod0)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode, prod0);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio, int meMode)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio, meMode);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode, double bRatio)
        {
            get_BEptr()->addChannel__BOSS(onMode, bRatio);
        }
        
        inline void ParticleDataEntry::addChannel(int onMode)
        {
            get_BEptr()->addChannel__BOSS(onMode);
        }
        
        inline void ParticleDataEntry::addChannel()
        {
            get_BEptr()->addChannel__BOSS();
        }
        
        inline int ParticleDataEntry::sizeChannels() const
        {
            return get_BEptr()->sizeChannels();
        }
        
        inline Pythia8::DecayChannel& ParticleDataEntry::channel(int i)
        {
            return get_BEptr()->channel__BOSS(i).get_init_wref();
        }
        
        inline const Pythia8::DecayChannel& ParticleDataEntry::channel(int i) const
        {
            return const_cast<Pythia8::Abstract_DecayChannel&>(const_cast<const Abstract_ParticleDataEntry*>(get_BEptr())->channel__BOSS(i)).get_init_wref();
        }
        
        inline void ParticleDataEntry::rescaleBR(double newSumBR)
        {
            get_BEptr()->rescaleBR(newSumBR);
        }
        
        inline void ParticleDataEntry::rescaleBR()
        {
            get_BEptr()->rescaleBR__BOSS();
        }
        
        inline bool ParticleDataEntry::preparePick(int idSgn, double mHat, int idInFlav)
        {
            return get_BEptr()->preparePick(idSgn, mHat, idInFlav);
        }
        
        inline bool ParticleDataEntry::preparePick(int idSgn, double mHat)
        {
            return get_BEptr()->preparePick__BOSS(idSgn, mHat);
        }
        
        inline bool ParticleDataEntry::preparePick(int idSgn)
        {
            return get_BEptr()->preparePick__BOSS(idSgn);
        }
        
        inline Pythia8::DecayChannel& ParticleDataEntry::pickChannel()
        {
            return get_BEptr()->pickChannel__BOSS().get_init_wref();
        }
        
        inline void ParticleDataEntry::setResonancePtr(Pythia8::ResonanceWidths* resonancePtrIn)
        {
            get_BEptr()->setResonancePtr__BOSS((*resonancePtrIn).get_BEptr());
        }
        
        inline Pythia8::ResonanceWidths* ParticleDataEntry::getResonancePtr()
        {
            return get_BEptr()->getResonancePtr__BOSS()->get_init_wptr();
        }
        
        inline void ParticleDataEntry::resInit(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::ParticleData* particleDataPtrIn, Pythia8::Couplings* couplingsPtrIn)
        {
            get_BEptr()->resInit__BOSS((*infoPtrIn).get_BEptr(), (*settingsPtrIn).get_BEptr(), (*particleDataPtrIn).get_BEptr(), (*couplingsPtrIn).get_BEptr());
        }
        
        inline double ParticleDataEntry::resWidth(int idSgn, double mHat, int idIn, bool openOnly, bool setBR)
        {
            return get_BEptr()->resWidth(idSgn, mHat, idIn, openOnly, setBR);
        }
        
        inline double ParticleDataEntry::resWidth(int idSgn, double mHat, int idIn, bool openOnly)
        {
            return get_BEptr()->resWidth__BOSS(idSgn, mHat, idIn, openOnly);
        }
        
        inline double ParticleDataEntry::resWidth(int idSgn, double mHat, int idIn)
        {
            return get_BEptr()->resWidth__BOSS(idSgn, mHat, idIn);
        }
        
        inline double ParticleDataEntry::resWidth(int idSgn, double mHat)
        {
            return get_BEptr()->resWidth__BOSS(idSgn, mHat);
        }
        
        inline double ParticleDataEntry::resWidthOpen(int idSgn, double mHat, int idIn)
        {
            return get_BEptr()->resWidthOpen(idSgn, mHat, idIn);
        }
        
        inline double ParticleDataEntry::resWidthOpen(int idSgn, double mHat)
        {
            return get_BEptr()->resWidthOpen__BOSS(idSgn, mHat);
        }
        
        inline double ParticleDataEntry::resWidthStore(int idSgn, double mHat, int idIn)
        {
            return get_BEptr()->resWidthStore(idSgn, mHat, idIn);
        }
        
        inline double ParticleDataEntry::resWidthStore(int idSgn, double mHat)
        {
            return get_BEptr()->resWidthStore__BOSS(idSgn, mHat);
        }
        
        inline double ParticleDataEntry::resOpenFrac(int idSgn)
        {
            return get_BEptr()->resOpenFrac(idSgn);
        }
        
        inline double ParticleDataEntry::resWidthRescaleFactor()
        {
            return get_BEptr()->resWidthRescaleFactor();
        }
        
        inline double ParticleDataEntry::resWidthChan(double mHat, int idAbs1, int idAbs2)
        {
            return get_BEptr()->resWidthChan(mHat, idAbs1, idAbs2);
        }
        
        inline double ParticleDataEntry::resWidthChan(double mHat, int idAbs1)
        {
            return get_BEptr()->resWidthChan__BOSS(mHat, idAbs1);
        }
        
        inline double ParticleDataEntry::resWidthChan(double mHat)
        {
            return get_BEptr()->resWidthChan__BOSS(mHat);
        }
        
        
        // Wrappers for original constructors: 
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In) :
            WrapperBase(__factory0(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn) :
            WrapperBase(__factory1(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn) :
            WrapperBase(__factory2(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn) :
            WrapperBase(__factory3(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In) :
            WrapperBase(__factory4(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn) :
            WrapperBase(__factory5(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn, int chargeTypeIn) :
            WrapperBase(__factory6(idIn, nameIn, spinTypeIn, chargeTypeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, int spinTypeIn) :
            WrapperBase(__factory7(idIn, nameIn, spinTypeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn) :
            WrapperBase(__factory8(idIn, nameIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn) :
            WrapperBase(__factory9(idIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry() :
            WrapperBase(__factory10())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In) :
            WrapperBase(__factory11(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn) :
            WrapperBase(__factory12(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn) :
            WrapperBase(__factory13(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn) :
            WrapperBase(__factory14(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In) :
            WrapperBase(__factory15(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn) :
            WrapperBase(__factory16(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn, int chargeTypeIn) :
            WrapperBase(__factory17(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn, int spinTypeIn) :
            WrapperBase(__factory18(idIn, nameIn, antiNameIn, spinTypeIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline ParticleDataEntry::ParticleDataEntry(int idIn, ::std::basic_string<char> nameIn, ::std::basic_string<char> antiNameIn) :
            WrapperBase(__factory19(idIn, nameIn, antiNameIn))
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline ParticleDataEntry::ParticleDataEntry(Abstract_ParticleDataEntry* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline ParticleDataEntry::ParticleDataEntry(const ParticleDataEntry& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline ParticleDataEntry& ParticleDataEntry::operator=(const ParticleDataEntry& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline ParticleDataEntry::~ParticleDataEntry()
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
        inline Abstract_ParticleDataEntry* Pythia8::ParticleDataEntry::get_BEptr() const
        {
            return dynamic_cast<Abstract_ParticleDataEntry*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ParticleDataEntry_def_Pythia_8_212_h__ */
