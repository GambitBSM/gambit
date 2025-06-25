#ifndef __wrapper_Settings_def_Pythia_8_312_h__
#define __wrapper_Settings_def_Pythia_8_312_h__

#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <set>
#include <map>
#include "wrapper_Logger_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Settings::initPtrs(Pythia8::Logger* loggerPtrIn)
        {
            get_BEptr()->initPtrs__BOSS((*loggerPtrIn).get_BEptr());
        }
        
        inline bool Settings::init(std::string startFile, bool append)
        {
            return get_BEptr()->init(startFile, append);
        }
        
        inline bool Settings::init(std::string startFile)
        {
            return get_BEptr()->init__BOSS(startFile);
        }
        
        inline bool Settings::init()
        {
            return get_BEptr()->init__BOSS();
        }
        
        inline bool Settings::init(std::istream& is, bool append)
        {
            return get_BEptr()->init(is, append);
        }
        
        inline bool Settings::init(std::istream& is)
        {
            return get_BEptr()->init__BOSS(is);
        }
        
        inline bool Settings::reInit(std::string startFile)
        {
            return get_BEptr()->reInit(startFile);
        }
        
        inline bool Settings::reInit()
        {
            return get_BEptr()->reInit__BOSS();
        }
        
        inline bool Settings::readString(std::string line, bool warn)
        {
            return get_BEptr()->readString(line, warn);
        }
        
        inline bool Settings::readString(std::string line)
        {
            return get_BEptr()->readString__BOSS(line);
        }
        
        inline bool Settings::registerPluginLibrary(std::string libName, std::string startFile)
        {
            return get_BEptr()->registerPluginLibrary(libName, startFile);
        }
        
        inline bool Settings::registerPluginLibrary(std::string libName)
        {
            return get_BEptr()->registerPluginLibrary__BOSS(libName);
        }
        
        inline bool Settings::writeFile(std::string toFile, bool writeAll)
        {
            return get_BEptr()->writeFile(toFile, writeAll);
        }
        
        inline bool Settings::writeFile(std::string toFile)
        {
            return get_BEptr()->writeFile__BOSS(toFile);
        }
        
        inline bool Settings::writeFile(std::ostream& os, bool writeAll)
        {
            return get_BEptr()->writeFile(os, writeAll);
        }
        
        inline bool Settings::writeFile(std::ostream& os)
        {
            return get_BEptr()->writeFile__BOSS(os);
        }
        
        inline bool Settings::writeFile()
        {
            return get_BEptr()->writeFile__BOSS();
        }
        
        inline bool Settings::writeFileXML(std::ostream& os)
        {
            return get_BEptr()->writeFileXML(os);
        }
        
        inline bool Settings::writeFileXML()
        {
            return get_BEptr()->writeFileXML__BOSS();
        }
        
        inline void Settings::listAll()
        {
            get_BEptr()->listAll();
        }
        
        inline void Settings::listChanged()
        {
            get_BEptr()->listChanged();
        }
        
        inline void Settings::list(std::string match)
        {
            get_BEptr()->list(match);
        }
        
        inline ::std::string Settings::output(std::string keyIn, bool fullLine)
        {
            return get_BEptr()->output(keyIn, fullLine);
        }
        
        inline ::std::string Settings::output(std::string keyIn)
        {
            return get_BEptr()->output__BOSS(keyIn);
        }
        
        inline ::std::vector<std::string> Settings::getReadHistory(int subrun)
        {
            return get_BEptr()->getReadHistory(subrun);
        }
        
        inline ::std::vector<std::string> Settings::getReadHistory()
        {
            return get_BEptr()->getReadHistory__BOSS();
        }
        
        inline void Settings::resetAll()
        {
            get_BEptr()->resetAll();
        }
        
        inline bool Settings::isFlag(std::string keyIn)
        {
            return get_BEptr()->isFlag(keyIn);
        }
        
        inline bool Settings::isMode(std::string keyIn)
        {
            return get_BEptr()->isMode(keyIn);
        }
        
        inline bool Settings::isParm(std::string keyIn)
        {
            return get_BEptr()->isParm(keyIn);
        }
        
        inline bool Settings::isWord(std::string keyIn)
        {
            return get_BEptr()->isWord(keyIn);
        }
        
        inline bool Settings::isFVec(std::string keyIn)
        {
            return get_BEptr()->isFVec(keyIn);
        }
        
        inline bool Settings::isMVec(std::string keyIn)
        {
            return get_BEptr()->isMVec(keyIn);
        }
        
        inline bool Settings::isPVec(std::string keyIn)
        {
            return get_BEptr()->isPVec(keyIn);
        }
        
        inline bool Settings::isWVec(std::string keyIn)
        {
            return get_BEptr()->isWVec(keyIn);
        }
        
        inline void Settings::addFlag(std::string keyIn, bool defaultIn)
        {
            get_BEptr()->addFlag(keyIn, defaultIn);
        }
        
        inline void Settings::addMode(std::string keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn, bool optOnlyIn)
        {
            get_BEptr()->addMode(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn, optOnlyIn);
        }
        
        inline void Settings::addMode(std::string keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn)
        {
            get_BEptr()->addMode__BOSS(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline void Settings::addParm(std::string keyIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn)
        {
            get_BEptr()->addParm(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline void Settings::addWord(std::string keyIn, std::string defaultIn)
        {
            get_BEptr()->addWord(keyIn, defaultIn);
        }
        
        inline void Settings::addFVec(std::string keyIn, std::vector<bool> defaultIn)
        {
            get_BEptr()->addFVec(keyIn, defaultIn);
        }
        
        inline void Settings::addMVec(std::string keyIn, std::vector<int> defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn)
        {
            get_BEptr()->addMVec(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline void Settings::addPVec(std::string keyIn, std::vector<double> defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn)
        {
            get_BEptr()->addPVec(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline void Settings::addWVec(std::string keyIn, std::vector<std::string> defaultIn)
        {
            get_BEptr()->addWVec(keyIn, defaultIn);
        }
        
        inline bool Settings::flag(std::string keyIn)
        {
            return get_BEptr()->flag(keyIn);
        }
        
        inline int Settings::mode(std::string keyIn)
        {
            return get_BEptr()->mode(keyIn);
        }
        
        inline double Settings::parm(std::string keyIn)
        {
            return get_BEptr()->parm(keyIn);
        }
        
        inline ::std::string Settings::word(std::string keyIn)
        {
            return get_BEptr()->word(keyIn);
        }
        
        inline ::std::vector<bool> Settings::fvec(std::string keyIn)
        {
            return get_BEptr()->fvec(keyIn);
        }
        
        inline ::std::vector<int> Settings::mvec(std::string keyIn)
        {
            return get_BEptr()->mvec(keyIn);
        }
        
        inline ::std::vector<double> Settings::pvec(std::string keyIn)
        {
            return get_BEptr()->pvec(keyIn);
        }
        
        inline ::std::vector<std::string> Settings::wvec(std::string keyIn)
        {
            return get_BEptr()->wvec(keyIn);
        }
        
        inline bool Settings::flagDefault(std::string keyIn)
        {
            return get_BEptr()->flagDefault(keyIn);
        }
        
        inline int Settings::modeDefault(std::string keyIn)
        {
            return get_BEptr()->modeDefault(keyIn);
        }
        
        inline double Settings::parmDefault(std::string keyIn)
        {
            return get_BEptr()->parmDefault(keyIn);
        }
        
        inline ::std::string Settings::wordDefault(std::string keyIn)
        {
            return get_BEptr()->wordDefault(keyIn);
        }
        
        inline ::std::vector<bool> Settings::fvecDefault(std::string keyIn)
        {
            return get_BEptr()->fvecDefault(keyIn);
        }
        
        inline ::std::vector<int> Settings::mvecDefault(std::string keyIn)
        {
            return get_BEptr()->mvecDefault(keyIn);
        }
        
        inline ::std::vector<double> Settings::pvecDefault(std::string keyIn)
        {
            return get_BEptr()->pvecDefault(keyIn);
        }
        
        inline ::std::vector<std::string> Settings::wvecDefault(std::string keyIn)
        {
            return get_BEptr()->wvecDefault(keyIn);
        }
        
        inline void Settings::flag(std::string keyIn, bool nowIn, bool force)
        {
            get_BEptr()->flag(keyIn, nowIn, force);
        }
        
        inline void Settings::flag(std::string keyIn, bool nowIn)
        {
            get_BEptr()->flag__BOSS(keyIn, nowIn);
        }
        
        inline bool Settings::mode(std::string keyIn, int nowIn, bool force)
        {
            return get_BEptr()->mode(keyIn, nowIn, force);
        }
        
        inline bool Settings::mode(std::string keyIn, int nowIn)
        {
            return get_BEptr()->mode__BOSS(keyIn, nowIn);
        }
        
        inline bool Settings::parm(std::string keyIn, double nowIn, bool force)
        {
            return get_BEptr()->parm(keyIn, nowIn, force);
        }
        
        inline bool Settings::parm(std::string keyIn, double nowIn)
        {
            return get_BEptr()->parm__BOSS(keyIn, nowIn);
        }
        
        inline void Settings::word(std::string keyIn, std::string nowIn, bool force)
        {
            get_BEptr()->word(keyIn, nowIn, force);
        }
        
        inline void Settings::word(std::string keyIn, std::string nowIn)
        {
            get_BEptr()->word__BOSS(keyIn, nowIn);
        }
        
        inline void Settings::fvec(std::string keyIn, std::vector<bool> nowIn, bool force)
        {
            get_BEptr()->fvec(keyIn, nowIn, force);
        }
        
        inline void Settings::fvec(std::string keyIn, std::vector<bool> nowIn)
        {
            get_BEptr()->fvec__BOSS(keyIn, nowIn);
        }
        
        inline bool Settings::mvec(std::string keyIn, std::vector<int> nowIn, bool force)
        {
            return get_BEptr()->mvec(keyIn, nowIn, force);
        }
        
        inline bool Settings::mvec(std::string keyIn, std::vector<int> nowIn)
        {
            return get_BEptr()->mvec__BOSS(keyIn, nowIn);
        }
        
        inline bool Settings::pvec(std::string keyIn, std::vector<double> nowIn, bool force)
        {
            return get_BEptr()->pvec(keyIn, nowIn, force);
        }
        
        inline bool Settings::pvec(std::string keyIn, std::vector<double> nowIn)
        {
            return get_BEptr()->pvec__BOSS(keyIn, nowIn);
        }
        
        inline void Settings::wvec(std::string keyIn, std::vector<std::string> nowIn, bool force)
        {
            get_BEptr()->wvec(keyIn, nowIn, force);
        }
        
        inline void Settings::wvec(std::string keyIn, std::vector<std::string> nowIn)
        {
            get_BEptr()->wvec__BOSS(keyIn, nowIn);
        }
        
        inline void Settings::forceMode(std::string keyIn, int nowIn)
        {
            get_BEptr()->forceMode(keyIn, nowIn);
        }
        
        inline void Settings::forceParm(std::string keyIn, double nowIn)
        {
            get_BEptr()->forceParm(keyIn, nowIn);
        }
        
        inline void Settings::forceMVec(std::string keyIn, std::vector<int> nowIn)
        {
            get_BEptr()->forceMVec(keyIn, nowIn);
        }
        
        inline void Settings::forcePVec(std::string keyIn, std::vector<double> nowIn)
        {
            get_BEptr()->forcePVec(keyIn, nowIn);
        }
        
        inline void Settings::resetFlag(std::string keyIn)
        {
            get_BEptr()->resetFlag(keyIn);
        }
        
        inline void Settings::resetMode(std::string keyIn)
        {
            get_BEptr()->resetMode(keyIn);
        }
        
        inline void Settings::resetParm(std::string keyIn)
        {
            get_BEptr()->resetParm(keyIn);
        }
        
        inline void Settings::resetWord(std::string keyIn)
        {
            get_BEptr()->resetWord(keyIn);
        }
        
        inline void Settings::resetFVec(std::string keyIn)
        {
            get_BEptr()->resetFVec(keyIn);
        }
        
        inline void Settings::resetMVec(std::string keyIn)
        {
            get_BEptr()->resetMVec(keyIn);
        }
        
        inline void Settings::resetPVec(std::string keyIn)
        {
            get_BEptr()->resetPVec(keyIn);
        }
        
        inline void Settings::resetWVec(std::string keyIn)
        {
            get_BEptr()->resetWVec(keyIn);
        }
        
        inline bool Settings::getIsInit()
        {
            return get_BEptr()->getIsInit();
        }
        
        inline bool Settings::readingFailed()
        {
            return get_BEptr()->readingFailed();
        }
        
        inline bool Settings::unfinishedInput()
        {
            return get_BEptr()->unfinishedInput();
        }
        
        inline bool Settings::hasHardProc()
        {
            return get_BEptr()->hasHardProc();
        }
        
        
        // Wrappers for original constructors: 
        inline Settings::Settings() :
            WrapperBase(__factory0())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Settings::Settings(Abstract_Settings* in) :
            WrapperBase(in)
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Copy constructor: 
        inline Settings::Settings(const Settings& in) :
            WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Assignment operator: 
        inline Settings& Settings::operator=(const Settings& in)
        {
            if (this != &in)
            {
                get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
            }
            return *this;
        }
        
        
        // Destructor: 
        inline Settings::~Settings()
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
        inline Abstract_Settings* Pythia8::Settings::get_BEptr() const
        {
            return dynamic_cast<Abstract_Settings*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Settings_def_Pythia_8_312_h__ */
