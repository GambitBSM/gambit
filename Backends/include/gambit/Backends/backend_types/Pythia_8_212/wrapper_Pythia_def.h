#ifndef __wrapper_Pythia_def_Pythia_8_212_h__
#define __wrapper_Pythia_def_Pythia_8_212_h__

#include <string>
#include <istream>
#include <vector>
#include <ostream>
#include <sstream>
#include "wrapper_ParticleData_decl.h"
#include "wrapper_Settings_decl.h"
#include "wrapper_UserHooks_decl.h"
#include "wrapper_SigmaProcess_decl.h"
#include "wrapper_ResonanceWidths_decl.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Info_decl.h"
#include "wrapper_Rndm_decl.h"
#include "wrapper_Couplings_decl.h"
#include "wrapper_SLHAinterface_decl.h"
#include "wrapper_Vec4_decl.h"
#include "wrapper_BeamParticle_decl.h"
#include "wrapper_PartonLevel_decl.h"
#include "wrapper_SigmaTotal_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline bool Pythia::readString(::std::basic_string<char> arg_1, bool warn)
        {
            return get_BEptr()->readString(arg_1, warn);
        }
        
        inline bool Pythia::readString(::std::basic_string<char> arg_1)
        {
            return get_BEptr()->readString__BOSS(arg_1);
        }
        
        inline bool Pythia::readFile(::std::basic_string<char> fileName, bool warn, int subrun)
        {
            return get_BEptr()->readFile(fileName, warn, subrun);
        }
        
        inline bool Pythia::readFile(::std::basic_string<char> fileName, bool warn)
        {
            return get_BEptr()->readFile__BOSS(fileName, warn);
        }
        
        inline bool Pythia::readFile(::std::basic_string<char> fileName)
        {
            return get_BEptr()->readFile__BOSS(fileName);
        }
        
        inline bool Pythia::readFile(::std::basic_string<char> fileName, int subrun)
        {
            return get_BEptr()->readFile(fileName, subrun);
        }
        
        inline bool Pythia::readFile(::std::basic_istream<char>& is, bool warn, int subrun)
        {
            return get_BEptr()->readFile(is, warn, subrun);
        }
        
        inline bool Pythia::readFile(::std::basic_istream<char>& is, bool warn)
        {
            return get_BEptr()->readFile__BOSS(is, warn);
        }
        
        inline bool Pythia::readFile(::std::basic_istream<char>& is)
        {
            return get_BEptr()->readFile__BOSS(is);
        }
        
        inline bool Pythia::readFile()
        {
            return get_BEptr()->readFile__BOSS();
        }
        
        inline bool Pythia::readFile(::std::basic_istream<char>& is, int subrun)
        {
            return get_BEptr()->readFile(is, subrun);
        }
        
        inline bool Pythia::setUserHooksPtr(Pythia8::UserHooks* userHooksPtrIn)
        {
            return get_BEptr()->setUserHooksPtr__BOSS((*userHooksPtrIn).get_BEptr());
        }
        
        inline bool Pythia::setResonancePtr(Pythia8::ResonanceWidths* resonancePtrIn)
        {
            return get_BEptr()->setResonancePtr__BOSS((*resonancePtrIn).get_BEptr());
        }
        
        inline bool Pythia::init(::std::basic_ostream<char>& os)
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
        
        inline void Pythia::LHAeventList(::std::basic_ostream<char>& os)
        {
            get_BEptr()->LHAeventList(os);
        }
        
        inline void Pythia::LHAeventList()
        {
            get_BEptr()->LHAeventList__BOSS();
        }
        
        inline bool Pythia::LHAeventSkip(int nSkip)
        {
            return get_BEptr()->LHAeventSkip(nSkip);
        }
        
        inline void Pythia::stat()
        {
            get_BEptr()->stat();
        }
        
        inline bool Pythia::flag(::std::basic_string<char> key)
        {
            return get_BEptr()->flag(key);
        }
        
        inline int Pythia::mode(::std::basic_string<char> key)
        {
            return get_BEptr()->mode(key);
        }
        
        inline double Pythia::parm(::std::basic_string<char> key)
        {
            return get_BEptr()->parm(key);
        }
        
        inline ::std::basic_string<char> Pythia::word(::std::basic_string<char> key)
        {
            return get_BEptr()->word(key);
        }
        
        
        // Wrappers for original constructors: 
        inline Pythia::Pythia(::std::basic_string<char> xmlDir, bool printBanner) :
            WrapperBase(__factory0(xmlDir, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( get_BEptr()->info_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            couplings( get_BEptr()->couplings_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(::std::basic_string<char> xmlDir) :
            WrapperBase(__factory1(xmlDir)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( get_BEptr()->info_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            couplings( get_BEptr()->couplings_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia() :
            WrapperBase(__factory2()),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( get_BEptr()->info_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            couplings( get_BEptr()->couplings_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::ParticleData& particleDataIn, Pythia8::Settings& settingsIn, bool printBanner) :
            WrapperBase(__factory3(particleDataIn, settingsIn, printBanner)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( get_BEptr()->info_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            couplings( get_BEptr()->couplings_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        inline Pythia::Pythia(Pythia8::ParticleData& particleDataIn, Pythia8::Settings& settingsIn) :
            WrapperBase(__factory4(particleDataIn, settingsIn)),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( get_BEptr()->info_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            couplings( get_BEptr()->couplings_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Pythia::Pythia(Abstract_Pythia* in) :
            WrapperBase(in),
            process( get_BEptr()->process_ref__BOSS().get_init_wref()),
            event( get_BEptr()->event_ref__BOSS().get_init_wref()),
            info( get_BEptr()->info_ref__BOSS().get_init_wref()),
            settings( get_BEptr()->settings_ref__BOSS().get_init_wref()),
            particleData( get_BEptr()->particleData_ref__BOSS().get_init_wref()),
            rndm( get_BEptr()->rndm_ref__BOSS().get_init_wref()),
            couplings( get_BEptr()->couplings_ref__BOSS().get_init_wref()),
            slhaInterface( get_BEptr()->slhaInterface_ref__BOSS().get_init_wref())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Pythia& Pythia::operator=(const Pythia& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
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

#endif /* __wrapper_Pythia_def_Pythia_8_212_h__ */
