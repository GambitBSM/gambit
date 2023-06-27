#ifndef __wrapper_Pythia_def_Pythia_8_306_h__
#define __wrapper_Pythia_def_Pythia_8_306_h__

#include <string>
#include <istream>
#include <vector>
#include <sstream>
#include "wrapper_Settings_decl.h"
#include "wrapper_ParticleData_decl.h"
#include "wrapper_SigmaProcess_decl.h"
#include "wrapper_ResonanceWidths_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_CoupSM_decl.h"
#include "wrapper_CoupSUSY_decl.h"
#include "wrapper_SLHAinterface_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_Vec4_decl.h"
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
        
        inline bool Pythia::readString(std::string arg_1, bool warn)
        {
            return get_BEptr()->readString(arg_1, warn);
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
        
        inline bool Pythia::setResonancePtr(Pythia8::ResonanceWidths* resonancePtrIn)
        {
            return get_BEptr()->setResonancePtr__BOSS((*resonancePtrIn).get_BEptr());
        }
        
        inline bool Pythia::init()
        {
            return get_BEptr()->init();
        }
        
        inline bool Pythia::next()
        {
            return get_BEptr()->next();
        }
        
        inline bool Pythia::next(double eCMin)
        {
            return get_BEptr()->next(eCMin);
        }
        
        inline bool Pythia::next(double eAin, double eBin)
        {
            return get_BEptr()->next(eAin, eBin);
        }
        
        inline bool Pythia::next(double pxAin, double pyAin, double pzAin, double pxBin, double pyBin, double pzBin)
        {
            return get_BEptr()->next(pxAin, pyAin, pzAin, pxBin, pyBin, pzBin);
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
        
        inline bool Pythia::forceRHadronDecays()
        {
            return get_BEptr()->forceRHadronDecays();
        }
        
        inline bool Pythia::doLowEnergyProcess(int i1, int i2, int type)
        {
            return get_BEptr()->doLowEnergyProcess(i1, i2, type);
        }
        
        inline double Pythia::getLowEnergySigma(int i1, int i2, int type)
        {
            return get_BEptr()->getLowEnergySigma(i1, i2, type);
        }
        
        inline double Pythia::getLowEnergySigma(int i1, int i2)
        {
            return get_BEptr()->getLowEnergySigma__BOSS(i1, i2);
        }
        
        inline double Pythia::getLowEnergySigma(int id1, int id2, double eCM12, double m1, double m2, int type)
        {
            return get_BEptr()->getLowEnergySigma(id1, id2, eCM12, m1, m2, type);
        }
        
        inline double Pythia::getLowEnergySigma(int id1, int id2, double eCM12, double m1, double m2)
        {
            return get_BEptr()->getLowEnergySigma__BOSS(id1, id2, eCM12, m1, m2);
        }
        
        inline double Pythia::getLowEnergySigma(int id1, int id2, double eCM12, int type)
        {
            return get_BEptr()->getLowEnergySigma(id1, id2, eCM12, type);
        }
        
        inline double Pythia::getLowEnergySigma(int id1, int id2, double eCM12)
        {
            return get_BEptr()->getLowEnergySigma__BOSS(id1, id2, eCM12);
        }
        
        inline double Pythia::getLowEnergySlope(int id1, int id2, double eCM12, double m1, double m2, int type)
        {
            return get_BEptr()->getLowEnergySlope(id1, id2, eCM12, m1, m2, type);
        }
        
        inline double Pythia::getLowEnergySlope(int id1, int id2, double eCM12, double m1, double m2)
        {
            return get_BEptr()->getLowEnergySlope__BOSS(id1, id2, eCM12, m1, m2);
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
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(std::string xmlDir) :
            WrapperBase(__factory1(xmlDir)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia() :
            WrapperBase(__factory2()),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::Settings& settingsIn, Pythia8::ParticleData& particleDataIn, bool printBanner) :
            WrapperBase(__factory3(settingsIn, particleDataIn, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::Settings& settingsIn, Pythia8::ParticleData& particleDataIn) :
            WrapperBase(__factory4(settingsIn, particleDataIn)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::ParticleData& particleDataIn, Pythia8::Settings& settingsIn, bool printBanner) :
            WrapperBase(__factory5(particleDataIn, settingsIn, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::ParticleData& particleDataIn, Pythia8::Settings& settingsIn) :
            WrapperBase(__factory6(particleDataIn, settingsIn)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(std::istream& settingsStrings, std::istream& particleDataStrings, bool printBanner) :
            WrapperBase(__factory7(settingsStrings, particleDataStrings, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(std::istream& settingsStrings, std::istream& particleDataStrings) :
            WrapperBase(__factory8(settingsStrings, particleDataStrings)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( const_cast<Pythia8::Abstract_Info&>(get_BEptr()->info_ref__BOSS()).get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
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
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            coupSM( get_BEptr()->coupSM_ref__BOSS().get_init_wref()),
            coupSUSY( get_BEptr()->coupSUSY_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref()),
            beamA( get_BEptr()->beamA_ref__BOSS().get_init_wref()),
            beamB( get_BEptr()->beamB_ref__BOSS().get_init_wref())
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

#endif /* __wrapper_Pythia_def_Pythia_8_306_h__ */
