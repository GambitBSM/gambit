#ifndef __wrapper_ParticleData_def_Pythia_8_312_h__
#define __wrapper_ParticleData_def_Pythia_8_312_h__

#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <map>
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
        
        // Member functions: 
        inline void ParticleData::initPtrs(Pythia8::Info* infoPtrIn)
        {
            get_BEptr()->initPtrs__BOSS((*infoPtrIn).get_BEptr());
        }
        
        inline bool ParticleData::init(std::string startFile)
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
        
        inline bool ParticleData::init(std::istream& is)
        {
            return get_BEptr()->init(is);
        }
        
        inline bool ParticleData::reInit(std::string startFile, bool xmlFormat)
        {
            return get_BEptr()->reInit(startFile, xmlFormat);
        }
        
        inline bool ParticleData::reInit(std::string startFile)
        {
            return get_BEptr()->reInit__BOSS(startFile);
        }
        
        inline bool ParticleData::readXML(std::string inFile, bool reset)
        {
            return get_BEptr()->readXML(inFile, reset);
        }
        
        inline bool ParticleData::readXML(std::string inFile)
        {
            return get_BEptr()->readXML__BOSS(inFile);
        }
        
        inline void ParticleData::listXML(std::string outFile)
        {
            get_BEptr()->listXML(outFile);
        }
        
        inline bool ParticleData::readXML(std::istream& is, bool reset)
        {
            return get_BEptr()->readXML(is, reset);
        }
        
        inline bool ParticleData::readXML(std::istream& is)
        {
            return get_BEptr()->readXML__BOSS(is);
        }
        
        inline bool ParticleData::copyXML(const Pythia8::ParticleData& particleDataIn)
        {
            return get_BEptr()->copyXML__BOSS(*particleDataIn.get_BEptr());
        }
        
        inline bool ParticleData::loadXML(std::string inFile, bool reset)
        {
            return get_BEptr()->loadXML(inFile, reset);
        }
        
        inline bool ParticleData::loadXML(std::string inFile)
        {
            return get_BEptr()->loadXML__BOSS(inFile);
        }
        
        inline bool ParticleData::loadXML(std::istream& is, bool reset)
        {
            return get_BEptr()->loadXML(is, reset);
        }
        
        inline bool ParticleData::loadXML(std::istream& is)
        {
            return get_BEptr()->loadXML__BOSS(is);
        }
        
        inline bool ParticleData::processXML(bool reset)
        {
            return get_BEptr()->processXML(reset);
        }
        
        inline bool ParticleData::processXML()
        {
            return get_BEptr()->processXML__BOSS();
        }
        
        inline bool ParticleData::readFF(std::string inFile, bool reset)
        {
            return get_BEptr()->readFF(inFile, reset);
        }
        
        inline bool ParticleData::readFF(std::string inFile)
        {
            return get_BEptr()->readFF__BOSS(inFile);
        }
        
        inline bool ParticleData::readFF(std::istream& is, bool reset)
        {
            return get_BEptr()->readFF(is, reset);
        }
        
        inline bool ParticleData::readFF(std::istream& is)
        {
            return get_BEptr()->readFF__BOSS(is);
        }
        
        inline void ParticleData::listFF(std::string outFile)
        {
            get_BEptr()->listFF(outFile);
        }
        
        inline bool ParticleData::readString(std::string lineIn, bool warn)
        {
            return get_BEptr()->readString(lineIn, warn);
        }
        
        inline bool ParticleData::readString(std::string lineIn)
        {
            return get_BEptr()->readString__BOSS(lineIn);
        }
        
        inline bool ParticleData::readingFailed()
        {
            return get_BEptr()->readingFailed();
        }
        
        inline void ParticleData::listAll(std::ostream& stream)
        {
            get_BEptr()->listAll(stream);
        }
        
        inline void ParticleData::listAll()
        {
            get_BEptr()->listAll();
        }
        
        inline void ParticleData::listChanged(bool changedRes)
        {
            get_BEptr()->listChanged(changedRes);
        }
        
        inline void ParticleData::listChanged()
        {
            get_BEptr()->listChanged__BOSS();
        }
        
        inline void ParticleData::list(std::ostream& stream, bool chargedOnly, bool changedRes)
        {
            get_BEptr()->list(stream, chargedOnly, changedRes);
        }
        
        inline void ParticleData::list(std::ostream& stream, bool chargedOnly)
        {
            get_BEptr()->list__BOSS(stream, chargedOnly);
        }
        
        inline void ParticleData::list(std::ostream& stream)
        {
            get_BEptr()->list__BOSS(stream);
        }
        
        inline void ParticleData::list(bool changedOnly, bool changedRes)
        {
            get_BEptr()->list(changedOnly, changedRes);
        }
        
        inline void ParticleData::list(bool changedOnly)
        {
            get_BEptr()->list__BOSS(changedOnly);
        }
        
        inline void ParticleData::list()
        {
            get_BEptr()->list__BOSS();
        }
        
        inline void ParticleData::list(int idList)
        {
            get_BEptr()->list(idList);
        }
        
        inline void ParticleData::list(std::vector<int> idList)
        {
            get_BEptr()->list(idList);
        }
        
        inline ::std::vector<std::string> ParticleData::getReadHistory(int subrun)
        {
            return get_BEptr()->getReadHistory(subrun);
        }
        
        inline ::std::vector<std::string> ParticleData::getReadHistory()
        {
            return get_BEptr()->getReadHistory__BOSS();
        }
        
        inline void ParticleData::checkTable(int verbosity)
        {
            get_BEptr()->checkTable(verbosity);
        }
        
        inline void ParticleData::checkTable()
        {
            get_BEptr()->checkTable__BOSS();
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In, bool varWidthIn)
        {
            get_BEptr()->addParticle(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In, varWidthIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn, colTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn, int chargeTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn, chargeTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, int spinTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, spinTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn);
        }
        
        inline void ParticleData::addParticle(int idIn)
        {
            get_BEptr()->addParticle__BOSS(idIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In, bool varWidthIn)
        {
            get_BEptr()->addParticle(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In, varWidthIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn, spinTypeIn);
        }
        
        inline void ParticleData::addParticle(int idIn, std::string nameIn, std::string antiNameIn)
        {
            get_BEptr()->addParticle__BOSS(idIn, nameIn, antiNameIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In, bool varWidthIn)
        {
            get_BEptr()->setAll(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In, varWidthIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn, double tau0In)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn, tau0In);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn, double mMaxIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn, mMaxIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn, double mMinIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn, mMinIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In, double mWidthIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In, mWidthIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn, double m0In)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn, m0In);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn, int colTypeIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn, colTypeIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn, int chargeTypeIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn, chargeTypeIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn, int spinTypeIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn, spinTypeIn);
        }
        
        inline void ParticleData::setAll(int idIn, std::string nameIn, std::string antiNameIn)
        {
            get_BEptr()->setAll__BOSS(idIn, nameIn, antiNameIn);
        }
        
        inline bool ParticleData::isParticle(int idIn) const
        {
            return get_BEptr()->isParticle(idIn);
        }
        
        inline int ParticleData::nextId(int idIn) const
        {
            return get_BEptr()->nextId(idIn);
        }
        
        inline void ParticleData::name(int idIn, std::string nameIn)
        {
            get_BEptr()->name(idIn, nameIn);
        }
        
        inline void ParticleData::antiName(int idIn, std::string antiNameIn)
        {
            get_BEptr()->antiName(idIn, antiNameIn);
        }
        
        inline void ParticleData::names(int idIn, std::string nameIn, std::string antiNameIn)
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
        
        inline void ParticleData::tauCalc(int idIn, bool tauCalcIn)
        {
            get_BEptr()->tauCalc(idIn, tauCalcIn);
        }
        
        inline void ParticleData::doExternalDecay(int idIn, bool doExternalDecayIn)
        {
            get_BEptr()->doExternalDecay(idIn, doExternalDecayIn);
        }
        
        inline void ParticleData::varWidth(int idIn, bool varWidthIn)
        {
            get_BEptr()->varWidth(idIn, varWidthIn);
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
        
        inline bool ParticleData::hasAnti(int idIn) const
        {
            return get_BEptr()->hasAnti(idIn);
        }
        
        inline int ParticleData::antiId(int idIn) const
        {
            return get_BEptr()->antiId(idIn);
        }
        
        inline ::std::string ParticleData::name(int idIn) const
        {
            return get_BEptr()->name(idIn);
        }
        
        inline int ParticleData::spinType(int idIn) const
        {
            return get_BEptr()->spinType(idIn);
        }
        
        inline int ParticleData::chargeType(int idIn) const
        {
            return get_BEptr()->chargeType(idIn);
        }
        
        inline double ParticleData::charge(int idIn) const
        {
            return get_BEptr()->charge(idIn);
        }
        
        inline int ParticleData::colType(int idIn) const
        {
            return get_BEptr()->colType(idIn);
        }
        
        inline double ParticleData::m0(int idIn) const
        {
            return get_BEptr()->m0(idIn);
        }
        
        inline double ParticleData::mWidth(int idIn) const
        {
            return get_BEptr()->mWidth(idIn);
        }
        
        inline double ParticleData::mMin(int idIn) const
        {
            return get_BEptr()->mMin(idIn);
        }
        
        inline double ParticleData::m0Min(int idIn) const
        {
            return get_BEptr()->m0Min(idIn);
        }
        
        inline double ParticleData::mMax(int idIn) const
        {
            return get_BEptr()->mMax(idIn);
        }
        
        inline double ParticleData::m0Max(int idIn) const
        {
            return get_BEptr()->m0Max(idIn);
        }
        
        inline double ParticleData::tau0(int idIn) const
        {
            return get_BEptr()->tau0(idIn);
        }
        
        inline bool ParticleData::isResonance(int idIn) const
        {
            return get_BEptr()->isResonance(idIn);
        }
        
        inline bool ParticleData::mayDecay(int idIn) const
        {
            return get_BEptr()->mayDecay(idIn);
        }
        
        inline bool ParticleData::tauCalc(int idIn) const
        {
            return get_BEptr()->tauCalc(idIn);
        }
        
        inline bool ParticleData::doExternalDecay(int idIn) const
        {
            return get_BEptr()->doExternalDecay(idIn);
        }
        
        inline bool ParticleData::isVisible(int idIn) const
        {
            return get_BEptr()->isVisible(idIn);
        }
        
        inline bool ParticleData::doForceWidth(int idIn) const
        {
            return get_BEptr()->doForceWidth(idIn);
        }
        
        inline bool ParticleData::hasChanged(int idIn) const
        {
            return get_BEptr()->hasChanged(idIn);
        }
        
        inline bool ParticleData::hasChangedMMin(int idIn) const
        {
            return get_BEptr()->hasChangedMMin(idIn);
        }
        
        inline bool ParticleData::hasChangedMMax(int idIn) const
        {
            return get_BEptr()->hasChangedMMax(idIn);
        }
        
        inline bool ParticleData::useBreitWigner(int idIn) const
        {
            return get_BEptr()->useBreitWigner(idIn);
        }
        
        inline bool ParticleData::varWidth(int idIn) const
        {
            return get_BEptr()->varWidth(idIn);
        }
        
        inline double ParticleData::constituentMass(int idIn) const
        {
            return get_BEptr()->constituentMass(idIn);
        }
        
        inline double ParticleData::mSel(int idIn) const
        {
            return get_BEptr()->mSel(idIn);
        }
        
        inline double ParticleData::mRun(int idIn, double mH) const
        {
            return get_BEptr()->mRun(idIn, mH);
        }
        
        inline bool ParticleData::canDecay(int idIn) const
        {
            return get_BEptr()->canDecay(idIn);
        }
        
        inline bool ParticleData::isLepton(int idIn) const
        {
            return get_BEptr()->isLepton(idIn);
        }
        
        inline bool ParticleData::isQuark(int idIn) const
        {
            return get_BEptr()->isQuark(idIn);
        }
        
        inline bool ParticleData::isGluon(int idIn) const
        {
            return get_BEptr()->isGluon(idIn);
        }
        
        inline bool ParticleData::isDiquark(int idIn) const
        {
            return get_BEptr()->isDiquark(idIn);
        }
        
        inline bool ParticleData::isParton(int idIn) const
        {
            return get_BEptr()->isParton(idIn);
        }
        
        inline bool ParticleData::isHadron(int idIn) const
        {
            return get_BEptr()->isHadron(idIn);
        }
        
        inline bool ParticleData::isMeson(int idIn) const
        {
            return get_BEptr()->isMeson(idIn);
        }
        
        inline bool ParticleData::isBaryon(int idIn) const
        {
            return get_BEptr()->isBaryon(idIn);
        }
        
        inline bool ParticleData::isOnium(int idIn) const
        {
            return get_BEptr()->isOnium(idIn);
        }
        
        inline bool ParticleData::isExotic(int idIn) const
        {
            return get_BEptr()->isExotic(idIn);
        }
        
        inline bool ParticleData::isOctetHadron(int idIn) const
        {
            return get_BEptr()->isOctetHadron(idIn);
        }
        
        inline int ParticleData::heaviestQuark(int idIn) const
        {
            return get_BEptr()->heaviestQuark(idIn);
        }
        
        inline int ParticleData::baryonNumberType(int idIn) const
        {
            return get_BEptr()->baryonNumberType(idIn);
        }
        
        inline int ParticleData::nQuarksInCode(int idIn, int idQIn) const
        {
            return get_BEptr()->nQuarksInCode(idIn, idQIn);
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
        
        inline bool ParticleData::getIsInit()
        {
            return get_BEptr()->getIsInit();
        }
        
        
        // Wrappers for original constructors: 
        inline ParticleData::ParticleData() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline ParticleData::ParticleData(Abstract_ParticleData* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline ParticleData::ParticleData(const ParticleData& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline ParticleData& ParticleData::operator=(const ParticleData& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline ParticleData::~ParticleData()
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
        inline Abstract_ParticleData* Pythia8::ParticleData::get_BEptr() const
        {
            return dynamic_cast<Abstract_ParticleData*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ParticleData_def_Pythia_8_312_h__ */
