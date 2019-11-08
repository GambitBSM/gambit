#ifndef __wrapper_ParticleData_def_Pythia_EM_8_212_h__
#define __wrapper_ParticleData_def_Pythia_EM_8_212_h__

#include "wrapper_Info_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include <string>
#include <ostream>
#include <vector>
#include "wrapper_ParticleDataEntry_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void ParticleData::initPtr(Pythia8::Info* infoPtrIn, Pythia8::Settings* settingsPtrIn, Pythia8::Rndm* rndmPtrIn, Pythia8::Couplings* couplingsPtrIn)
        {
            get_BEptr()->initPtr__BOSS((*infoPtrIn).get_BEptr(), (*settingsPtrIn).get_BEptr(), (*rndmPtrIn).get_BEptr(), (*couplingsPtrIn).get_BEptr());
        }
        
        inline bool ParticleData::init(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > startFile)
        {
            return get_BEptr()->init(startFile);
        }
        
        inline bool ParticleData::init()
        {
            return get_BEptr()->init__BOSS();
        }
        
        inline bool ParticleData::init(const Pythia8::ParticleData& particleDataIn)
        {
            return get_BEptr()->init__BOSS(*particleDataIn.get_BEptr());
        }
        
        inline bool ParticleData::reInit(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > startFile, bool xmlFormat)
        {
            return get_BEptr()->reInit(startFile, xmlFormat);
        }
        
        inline bool ParticleData::reInit(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > startFile)
        {
            return get_BEptr()->reInit__BOSS(startFile);
        }
        
        inline bool ParticleData::readXML(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > inFile, bool reset)
        {
            return get_BEptr()->readXML(inFile, reset);
        }
        
        inline bool ParticleData::readXML(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > inFile)
        {
            return get_BEptr()->readXML__BOSS(inFile);
        }
        
        inline void ParticleData::listXML(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > outFile)
        {
            get_BEptr()->listXML(outFile);
        }
        
        inline bool ParticleData::copyXML(const Pythia8::ParticleData& particleDataIn)
        {
            return get_BEptr()->copyXML__BOSS(*particleDataIn.get_BEptr());
        }
        
        inline bool ParticleData::loadXML(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > inFile, bool reset)
        {
            return get_BEptr()->loadXML(inFile, reset);
        }
        
        inline bool ParticleData::loadXML(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > inFile)
        {
            return get_BEptr()->loadXML__BOSS(inFile);
        }
        
        inline bool ParticleData::processXML(bool reset)
        {
            return get_BEptr()->processXML(reset);
        }
        
        inline bool ParticleData::processXML()
        {
            return get_BEptr()->processXML__BOSS();
        }
        
        inline bool ParticleData::readFF(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > inFile, bool reset)
        {
            return get_BEptr()->readFF(inFile, reset);
        }
        
        inline bool ParticleData::readFF(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > inFile)
        {
            return get_BEptr()->readFF__BOSS(inFile);
        }
        
        inline void ParticleData::listFF(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > outFile)
        {
            get_BEptr()->listFF(outFile);
        }
        
        inline bool ParticleData::readString(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > lineIn, bool warn, ::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            return get_BEptr()->readString(lineIn, warn, os);
        }
        
        inline bool ParticleData::readString(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > lineIn, bool warn)
        {
            return get_BEptr()->readString__BOSS(lineIn, warn);
        }
        
        inline bool ParticleData::readString(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > lineIn)
        {
            return get_BEptr()->readString__BOSS(lineIn);
        }
        
        inline bool ParticleData::readingFailed()
        {
            return get_BEptr()->readingFailed();
        }
        
        inline void ParticleData::listAll(::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->listAll(os);
        }
        
        inline void ParticleData::listAll()
        {
            get_BEptr()->listAll__BOSS();
        }
        
        inline void ParticleData::listChanged(::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->listChanged(os);
        }
        
        inline void ParticleData::listChanged()
        {
            get_BEptr()->listChanged__BOSS();
        }
        
        inline void ParticleData::listChanged(bool changedRes, ::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->listChanged(changedRes, os);
        }
        
        inline void ParticleData::listChanged(bool changedRes)
        {
            get_BEptr()->listChanged__BOSS(changedRes);
        }
        
        inline void ParticleData::list(bool changedOnly, bool changedRes, ::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->list(changedOnly, changedRes, os);
        }
        
        inline void ParticleData::list(bool changedOnly, bool changedRes)
        {
            get_BEptr()->list__BOSS(changedOnly, changedRes);
        }
        
        inline void ParticleData::list(bool changedOnly)
        {
            get_BEptr()->list__BOSS(changedOnly);
        }
        
        inline void ParticleData::list()
        {
            get_BEptr()->list__BOSS();
        }
        
        inline void ParticleData::list(int idList, ::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->list(idList, os);
        }
        
        inline void ParticleData::list(int idList)
        {
            get_BEptr()->list__BOSS(idList);
        }
        
        inline void ParticleData::list(::std::vector<int, std::allocator<int> > idList, ::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->list(idList, os);
        }
        
        inline void ParticleData::list(::std::vector<int, std::allocator<int> > idList)
        {
            get_BEptr()->list__BOSS(idList);
        }
        
        inline void ParticleData::checkTable(::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->checkTable(os);
        }
        
        inline void ParticleData::checkTable()
        {
            get_BEptr()->checkTable__BOSS();
        }
        
        inline void ParticleData::checkTable(int verbosity, ::std::basic_ostream<char, std::char_traits<char> >& os)
        {
            get_BEptr()->checkTable(verbosity, os);
        }
        
        inline void ParticleData::checkTable(int verbosity)
        {
            get_BEptr()->checkTable__BOSS(verbosity);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In)
        {
            get_BEptr()->addParticle(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn, int chargeTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, int spinTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn);
        }
        
        inline void ParticleData::addParticle(int idIn)
        {
            get_BEptr()->addParticle__BOSS(idIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In)
        {
            get_BEptr()->addParticle(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In)
        {
            get_BEptr()->setAll(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn, int chargeTypeIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn, int spinTypeIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn);
        }
        
        inline void ParticleData::setAll(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn);
        }
        
        inline bool ParticleData::isParticle(int idIn)
        {
            return get_BEptr()->isParticle(idIn);
        }
        
        inline int ParticleData::nextId(int idIn)
        {
            return get_BEptr()->nextId(idIn);
        }
        
        inline void ParticleData::name(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn)
        {
            get_BEptr()->name(idIn, nameIn);
        }
        
        inline void ParticleData::antiName(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn)
        {
            get_BEptr()->antiName(idIn, antiNameIn);
        }
        
        inline void ParticleData::names(int idIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > nameIn, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > antiNameIn)
        {
            get_BEptr()->names(idIn, nameIn, antiNameIn);
        }
        
        inline void ParticleData::spinType(int idIn, int spinTypeIn)
        {
            get_BEptr()->spinType(idIn, spinTypeIn);
        }
        
        inline void ParticleData::chargeType(int idIn, int chargeTypeIn)
        {
            get_BEptr()->chargeType(idIn, chargeTypeIn);
        }
        
        inline void ParticleData::colType(int idIn, int colTypeIn)
        {
            get_BEptr()->colType(idIn, colTypeIn);
        }
        
        inline void ParticleData::m0(int idIn, double m0In)
        {
            get_BEptr()->m0(idIn, m0In);
        }
        
        inline void ParticleData::mWidth(int idIn, double mWidthIn)
        {
            get_BEptr()->mWidth(idIn, mWidthIn);
        }
        
        inline void ParticleData::mMin(int idIn, double mMinIn)
        {
            get_BEptr()->mMin(idIn, mMinIn);
        }
        
        inline void ParticleData::mMax(int idIn, double mMaxIn)
        {
            get_BEptr()->mMax(idIn, mMaxIn);
        }
        
        inline void ParticleData::tau0(int idIn, double tau0In)
        {
            get_BEptr()->tau0(idIn, tau0In);
        }
        
        inline void ParticleData::isResonance(int idIn, bool isResonanceIn)
        {
            get_BEptr()->isResonance(idIn, isResonanceIn);
        }
        
        inline void ParticleData::mayDecay(int idIn, bool mayDecayIn)
        {
            get_BEptr()->mayDecay(idIn, mayDecayIn);
        }
        
        inline void ParticleData::doExternalDecay(int idIn, bool doExternalDecayIn)
        {
            get_BEptr()->doExternalDecay(idIn, doExternalDecayIn);
        }
        
        inline void ParticleData::isVisible(int idIn, bool isVisibleIn)
        {
            get_BEptr()->isVisible(idIn, isVisibleIn);
        }
        
        inline void ParticleData::doForceWidth(int idIn, bool doForceWidthIn)
        {
            get_BEptr()->doForceWidth(idIn, doForceWidthIn);
        }
        
        inline void ParticleData::hasChanged(int idIn, bool hasChangedIn)
        {
            get_BEptr()->hasChanged(idIn, hasChangedIn);
        }
        
        inline bool ParticleData::hasAnti(int idIn)
        {
            return get_BEptr()->hasAnti(idIn);
        }
        
        inline ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > ParticleData::name(int idIn)
        {
            return get_BEptr()->name(idIn);
        }
        
        inline int ParticleData::spinType(int idIn)
        {
            return get_BEptr()->spinType(idIn);
        }
        
        inline int ParticleData::chargeType(int idIn)
        {
            return get_BEptr()->chargeType(idIn);
        }
        
        inline double ParticleData::charge(int idIn)
        {
            return get_BEptr()->charge(idIn);
        }
        
        inline int ParticleData::colType(int idIn)
        {
            return get_BEptr()->colType(idIn);
        }
        
        inline double ParticleData::m0(int idIn)
        {
            return get_BEptr()->m0(idIn);
        }
        
        inline double ParticleData::mWidth(int idIn)
        {
            return get_BEptr()->mWidth(idIn);
        }
        
        inline double ParticleData::mMin(int idIn)
        {
            return get_BEptr()->mMin(idIn);
        }
        
        inline double ParticleData::m0Min(int idIn)
        {
            return get_BEptr()->m0Min(idIn);
        }
        
        inline double ParticleData::mMax(int idIn)
        {
            return get_BEptr()->mMax(idIn);
        }
        
        inline double ParticleData::m0Max(int idIn)
        {
            return get_BEptr()->m0Max(idIn);
        }
        
        inline double ParticleData::tau0(int idIn)
        {
            return get_BEptr()->tau0(idIn);
        }
        
        inline bool ParticleData::isResonance(int idIn)
        {
            return get_BEptr()->isResonance(idIn);
        }
        
        inline bool ParticleData::mayDecay(int idIn)
        {
            return get_BEptr()->mayDecay(idIn);
        }
        
        inline bool ParticleData::doExternalDecay(int idIn)
        {
            return get_BEptr()->doExternalDecay(idIn);
        }
        
        inline bool ParticleData::isVisible(int idIn)
        {
            return get_BEptr()->isVisible(idIn);
        }
        
        inline bool ParticleData::doForceWidth(int idIn)
        {
            return get_BEptr()->doForceWidth(idIn);
        }
        
        inline bool ParticleData::hasChanged(int idIn)
        {
            return get_BEptr()->hasChanged(idIn);
        }
        
        inline bool ParticleData::useBreitWigner(int idIn)
        {
            return get_BEptr()->useBreitWigner(idIn);
        }
        
        inline double ParticleData::constituentMass(int idIn)
        {
            return get_BEptr()->constituentMass(idIn);
        }
        
        inline double ParticleData::mSel(int idIn)
        {
            return get_BEptr()->mSel(idIn);
        }
        
        inline double ParticleData::mRun(int idIn, double mH)
        {
            return get_BEptr()->mRun(idIn, mH);
        }
        
        inline bool ParticleData::canDecay(int idIn)
        {
            return get_BEptr()->canDecay(idIn);
        }
        
        inline bool ParticleData::isLepton(int idIn)
        {
            return get_BEptr()->isLepton(idIn);
        }
        
        inline bool ParticleData::isQuark(int idIn)
        {
            return get_BEptr()->isQuark(idIn);
        }
        
        inline bool ParticleData::isGluon(int idIn)
        {
            return get_BEptr()->isGluon(idIn);
        }
        
        inline bool ParticleData::isDiquark(int idIn)
        {
            return get_BEptr()->isDiquark(idIn);
        }
        
        inline bool ParticleData::isParton(int idIn)
        {
            return get_BEptr()->isParton(idIn);
        }
        
        inline bool ParticleData::isHadron(int idIn)
        {
            return get_BEptr()->isHadron(idIn);
        }
        
        inline bool ParticleData::isMeson(int idIn)
        {
            return get_BEptr()->isMeson(idIn);
        }
        
        inline bool ParticleData::isBaryon(int idIn)
        {
            return get_BEptr()->isBaryon(idIn);
        }
        
        inline bool ParticleData::isOctetHadron(int idIn)
        {
            return get_BEptr()->isOctetHadron(idIn);
        }
        
        inline int ParticleData::heaviestQuark(int idIn)
        {
            return get_BEptr()->heaviestQuark(idIn);
        }
        
        inline int ParticleData::baryonNumberType(int idIn)
        {
            return get_BEptr()->baryonNumberType(idIn);
        }
        
        inline void ParticleData::rescaleBR(int idIn, double newSumBR)
        {
            get_BEptr()->rescaleBR(idIn, newSumBR);
        }
        
        inline void ParticleData::rescaleBR(int idIn)
        {
            get_BEptr()->rescaleBR__BOSS(idIn);
        }
        
        inline void ParticleData::resInit(int idIn)
        {
            get_BEptr()->resInit(idIn);
        }
        
        inline double ParticleData::resWidth(int idIn, double mHat, int idInFlav, bool openOnly, bool setBR)
        {
            return get_BEptr()->resWidth(idIn, mHat, idInFlav, openOnly, setBR);
        }
        
        inline double ParticleData::resWidth(int idIn, double mHat, int idInFlav, bool openOnly)
        {
            return get_BEptr()->resWidth__BOSS(idIn, mHat, idInFlav, openOnly);
        }
        
        inline double ParticleData::resWidth(int idIn, double mHat, int idInFlav)
        {
            return get_BEptr()->resWidth__BOSS(idIn, mHat, idInFlav);
        }
        
        inline double ParticleData::resWidth(int idIn, double mHat)
        {
            return get_BEptr()->resWidth__BOSS(idIn, mHat);
        }
        
        inline double ParticleData::resWidthOpen(int idIn, double mHat, int idInFlav)
        {
            return get_BEptr()->resWidthOpen(idIn, mHat, idInFlav);
        }
        
        inline double ParticleData::resWidthOpen(int idIn, double mHat)
        {
            return get_BEptr()->resWidthOpen__BOSS(idIn, mHat);
        }
        
        inline double ParticleData::resWidthStore(int idIn, double mHat, int idInFlav)
        {
            return get_BEptr()->resWidthStore(idIn, mHat, idInFlav);
        }
        
        inline double ParticleData::resWidthStore(int idIn, double mHat)
        {
            return get_BEptr()->resWidthStore__BOSS(idIn, mHat);
        }
        
        inline double ParticleData::resOpenFrac(int id1In, int id2In, int id3In)
        {
            return get_BEptr()->resOpenFrac(id1In, id2In, id3In);
        }
        
        inline double ParticleData::resOpenFrac(int id1In, int id2In)
        {
            return get_BEptr()->resOpenFrac__BOSS(id1In, id2In);
        }
        
        inline double ParticleData::resOpenFrac(int id1In)
        {
            return get_BEptr()->resOpenFrac__BOSS(id1In);
        }
        
        inline double ParticleData::resWidthRescaleFactor(int idIn)
        {
            return get_BEptr()->resWidthRescaleFactor(idIn);
        }
        
        inline double ParticleData::resWidthChan(int idIn, double mHat, int idAbs1, int idAbs2)
        {
            return get_BEptr()->resWidthChan(idIn, mHat, idAbs1, idAbs2);
        }
        
        inline double ParticleData::resWidthChan(int idIn, double mHat, int idAbs1)
        {
            return get_BEptr()->resWidthChan__BOSS(idIn, mHat, idAbs1);
        }
        
        inline double ParticleData::resWidthChan(int idIn, double mHat)
        {
            return get_BEptr()->resWidthChan__BOSS(idIn, mHat);
        }
        
        inline Pythia8::ParticleDataEntry* ParticleData::particleDataEntryPtr(int idIn)
        {
            return get_BEptr()->particleDataEntryPtr__BOSS(idIn)->get_init_wptr();
        }
        
        inline bool ParticleData::getIsInit()
        {
            return get_BEptr()->getIsInit();
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia8::ParticleData::ParticleData() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia8::ParticleData::ParticleData(Pythia8::Abstract_ParticleData* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Pythia8::ParticleData::ParticleData(const ParticleData& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia8::ParticleData& ParticleData::operator=(const ParticleData& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Pythia8::ParticleData::~ParticleData()
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
        inline Pythia8::Abstract_ParticleData* Pythia8::ParticleData::get_BEptr() const
        {
            return dynamic_cast<Pythia8::Abstract_ParticleData*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ParticleData_def_Pythia_EM_8_212_h__ */
