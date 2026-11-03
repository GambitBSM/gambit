#ifndef __wrapper_Pythia_def_Pythia_8_312_h__
#define __wrapper_Pythia_def_Pythia_8_312_h__

#include <string>
#include <istream>
#include <vector>
#include <ostream>
#include <sstream>
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Logger_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_CoupSUSY_decl.h"
#include "wrapper_SLHAinterface_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_PartonLevel_decl.h"
#include "wrapper_SigmaTotal_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline bool Pythia::checkVersion()
        {
            return get_BEptr()->checkVersion();
        }
        
        inline bool Pythia::readString(std::string arg_1, bool warn, int subrun)
        {
            return get_BEptr()->readString(arg_1, warn, subrun);
        }
        
        inline bool Pythia::readString(std::string arg_1, bool warn)
        {
            return get_BEptr()->readString__BOSS(arg_1, warn);
        }
        
        inline bool Pythia::readString(std::string arg_1)
        {
            return get_BEptr()->readString__BOSS(arg_1);
        }
        
        inline bool Pythia::readFile(std::string fileName, bool warn, int subrun)
        {
            return get_BEptr()->readFile(fileName, warn, subrun);
        }
        
        inline bool Pythia::readFile(std::string fileName, bool warn)
        {
            return get_BEptr()->readFile__BOSS(fileName, warn);
        }
        
        inline bool Pythia::readFile(std::string fileName)
        {
            return get_BEptr()->readFile__BOSS(fileName);
        }
        
        inline bool Pythia::readFile(std::string fileName, int subrun)
        {
            return get_BEptr()->readFile(fileName, subrun);
        }
        
        inline bool Pythia::readFile(std::istream& is, bool warn, int subrun)
        {
            return get_BEptr()->readFile(is, warn, subrun);
        }
        
        inline bool Pythia::readFile(std::istream& is, bool warn)
        {
            return get_BEptr()->readFile__BOSS(is, warn);
        }
        
        inline bool Pythia::readFile(std::istream& is)
        {
            return get_BEptr()->readFile__BOSS(is);
        }
        
        inline bool Pythia::readFile()
        {
            return get_BEptr()->readFile__BOSS();
        }
        
        inline bool Pythia::readFile(std::istream& is, int subrun)
        {
            return get_BEptr()->readFile(is, subrun);
        }
        
        inline bool Pythia::init(std::ostream& os)
        {
            return get_BEptr()->init(os);
        }
        
        inline bool Pythia::init()
        {
            return get_BEptr()->init__BOSS();
        }
        
        inline bool Pythia::next()
        {
            return get_BEptr()->next();
        }
        
        inline bool Pythia::next(int procTypeIn)
        {
            return get_BEptr()->next(procTypeIn);
        }
        
        inline bool Pythia::setBeamIDs(int idAin, int idBin)
        {
            return get_BEptr()->setBeamIDs(idAin, idBin);
        }
        
        inline bool Pythia::setBeamIDs(int idAin)
        {
            return get_BEptr()->setBeamIDs__BOSS(idAin);
        }
        
        inline bool Pythia::setKinematics(double eCMIn)
        {
            return get_BEptr()->setKinematics(eCMIn);
        }
        
        inline bool Pythia::setKinematics(double eAIn, double eBIn)
        {
            return get_BEptr()->setKinematics(eAIn, eBIn);
        }
        
        inline bool Pythia::setKinematics(double pxAIn, double pyAIn, double pzAIn, double pxBIn, double pyBIn, double pzBIn)
        {
            return get_BEptr()->setKinematics(pxAIn, pyAIn, pzAIn, pxBIn, pyBIn, pzBIn);
        }
        
        inline bool Pythia::setKinematics(Pythia8::Vec4 pAIn, Pythia8::Vec4 pBIn)
        {
            return get_BEptr()->setKinematics__BOSS(*pAIn.get_BEptr(), *pBIn.get_BEptr());
        }
        
        inline int Pythia::forceTimeShower(int iBeg, int iEnd, double pTmax, int nBranchMax)
        {
            return get_BEptr()->forceTimeShower(iBeg, iEnd, pTmax, nBranchMax);
        }
        
        inline int Pythia::forceTimeShower(int iBeg, int iEnd, double pTmax)
        {
            return get_BEptr()->forceTimeShower__BOSS(iBeg, iEnd, pTmax);
        }
        
        inline bool Pythia::forceHadronLevel(bool findJunctions)
        {
            return get_BEptr()->forceHadronLevel(findJunctions);
        }
        
        inline bool Pythia::forceHadronLevel()
        {
            return get_BEptr()->forceHadronLevel__BOSS();
        }
        
        inline bool Pythia::moreDecays()
        {
            return get_BEptr()->moreDecays();
        }
        
        inline bool Pythia::moreDecays(int index)
        {
            return get_BEptr()->moreDecays(index);
        }
        
        inline bool Pythia::forceRHadronDecays()
        {
            return get_BEptr()->forceRHadronDecays();
        }
        
        inline bool Pythia::doLowEnergyProcess(int i1, int i2, int procTypeIn)
        {
            return get_BEptr()->doLowEnergyProcess(i1, i2, procTypeIn);
        }
        
        inline double Pythia::getSigmaTotal()
        {
            return get_BEptr()->getSigmaTotal();
        }
        
        inline double Pythia::getSigmaTotal(double eCM12, int mixLoHi)
        {
            return get_BEptr()->getSigmaTotal(eCM12, mixLoHi);
        }
        
        inline double Pythia::getSigmaTotal(double eCM12)
        {
            return get_BEptr()->getSigmaTotal__BOSS(eCM12);
        }
        
        inline double Pythia::getSigmaTotal(int id1, int id2, double eCM12, int mixLoHi)
        {
            return get_BEptr()->getSigmaTotal(id1, id2, eCM12, mixLoHi);
        }
        
        inline double Pythia::getSigmaTotal(int id1, int id2, double eCM12)
        {
            return get_BEptr()->getSigmaTotal__BOSS(id1, id2, eCM12);
        }
        
        inline double Pythia::getSigmaTotal(int id1, int id2, double eCM12, double m1, double m2, int mixLoHi)
        {
            return get_BEptr()->getSigmaTotal(id1, id2, eCM12, m1, m2, mixLoHi);
        }
        
        inline double Pythia::getSigmaTotal(int id1, int id2, double eCM12, double m1, double m2)
        {
            return get_BEptr()->getSigmaTotal__BOSS(id1, id2, eCM12, m1, m2);
        }
        
        inline double Pythia::getSigmaPartial(int procTypeIn)
        {
            return get_BEptr()->getSigmaPartial(procTypeIn);
        }
        
        inline double Pythia::getSigmaPartial(double eCM12, int procTypeIn, int mixLoHi)
        {
            return get_BEptr()->getSigmaPartial(eCM12, procTypeIn, mixLoHi);
        }
        
        inline double Pythia::getSigmaPartial(double eCM12, int procTypeIn)
        {
            return get_BEptr()->getSigmaPartial__BOSS(eCM12, procTypeIn);
        }
        
        inline double Pythia::getSigmaPartial(int id1, int id2, double eCM12, int procTypeIn, int mixLoHi)
        {
            return get_BEptr()->getSigmaPartial(id1, id2, eCM12, procTypeIn, mixLoHi);
        }
        
        inline double Pythia::getSigmaPartial(int id1, int id2, double eCM12, int procTypeIn)
        {
            return get_BEptr()->getSigmaPartial__BOSS(id1, id2, eCM12, procTypeIn);
        }
        
        inline double Pythia::getSigmaPartial(int id1, int id2, double eCM12, double m1, double m2, int procTypeIn, int mixLoHi)
        {
            return get_BEptr()->getSigmaPartial(id1, id2, eCM12, m1, m2, procTypeIn, mixLoHi);
        }
        
        inline double Pythia::getSigmaPartial(int id1, int id2, double eCM12, double m1, double m2, int procTypeIn)
        {
            return get_BEptr()->getSigmaPartial__BOSS(id1, id2, eCM12, m1, m2, procTypeIn);
        }
        
        inline void Pythia::LHAeventList()
        {
            get_BEptr()->LHAeventList();
        }
        
        inline bool Pythia::LHAeventSkip(int nSkip)
        {
            return get_BEptr()->LHAeventSkip(nSkip);
        }
        
        inline void Pythia::stat()
        {
            get_BEptr()->stat();
        }
        
        inline bool Pythia::flag(std::string key)
        {
            return get_BEptr()->flag(key);
        }
        
        inline int Pythia::mode(std::string key)
        {
            return get_BEptr()->mode(key);
        }
        
        inline double Pythia::parm(std::string key)
        {
            return get_BEptr()->parm(key);
        }
        
        inline ::std::string Pythia::word(std::string key)
        {
            return get_BEptr()->word(key);
        }
        
        inline double Pythia::getSigmaMaxSum()
        {
            return get_BEptr()->getSigmaMaxSum();
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia::Pythia(std::string xmlDir, bool printBanner) :
            WrapperBase(__factory0(xmlDir, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(std::string xmlDir) :
            WrapperBase(__factory1(xmlDir)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia() :
            WrapperBase(__factory2()),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::Settings& settingsIn, Pythia8::ParticleData& particleDataIn, bool printBanner) :
            WrapperBase(__factory3(settingsIn, particleDataIn, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::Settings& settingsIn, Pythia8::ParticleData& particleDataIn) :
            WrapperBase(__factory4(settingsIn, particleDataIn)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(std::istream& settingsStrings, std::istream& particleDataStrings, bool printBanner) :
            WrapperBase(__factory5(settingsStrings, particleDataStrings, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(std::istream& settingsStrings, std::istream& particleDataStrings) :
            WrapperBase(__factory6(settingsStrings, particleDataStrings)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia::Pythia(Abstract_Pythia* in) :
            WrapperBase(in),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            logger( get_BEptr()->logger_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamA_ref__BOSS()).get_init_wref()),
            beamB( const_cast<Pythia8::Abstract_BeamParticle&>(get_BEptr()->beamB_ref__BOSS()).get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Destructor: 
        inline Pythia::~Pythia()
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
        inline Abstract_Pythia* Pythia8::Pythia::get_BEptr() const
        {
            return dynamic_cast<Abstract_Pythia*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Pythia_def_Pythia_8_312_h__ */
