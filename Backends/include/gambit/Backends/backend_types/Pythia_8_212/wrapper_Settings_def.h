#ifndef __wrapper_Settings_def_Pythia_8_212_h__
#define __wrapper_Settings_def_Pythia_8_212_h__

#include <string>
#include <ostream>
#include <vector>
#include "wrapper_Info_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Settings::initPtr(Pythia8::Info* infoPtrIn)
        {
            get_BEptr()->initPtr__BOSS((*infoPtrIn).get_BEptr());
        }
        
        inline bool Settings::init(::std::basic_string<char> startFile, bool append, ::std::basic_ostream<char>& os)
        {
            return get_BEptr()->init(startFile, append, os);
        }
        
        inline bool Settings::init(::std::basic_string<char> startFile, bool append)
        {
            return get_BEptr()->init__BOSS(startFile, append);
        }
        
        inline bool Settings::init(::std::basic_string<char> startFile)
        {
            return get_BEptr()->init__BOSS(startFile);
        }
        
        inline bool Settings::init()
        {
            return get_BEptr()->init__BOSS();
        }
        
        inline bool Settings::reInit(::std::basic_string<char> startFile, ::std::basic_ostream<char>& os)
        {
            return get_BEptr()->reInit(startFile, os);
        }
        
        inline bool Settings::reInit(::std::basic_string<char> startFile)
        {
            return get_BEptr()->reInit__BOSS(startFile);
        }
        
        inline bool Settings::reInit()
        {
            return get_BEptr()->reInit__BOSS();
        }
        
        inline bool Settings::readString(::std::basic_string<char> line, bool warn, ::std::basic_ostream<char>& os)
        {
            return get_BEptr()->readString(line, warn, os);
        }
        
        inline bool Settings::readString(::std::basic_string<char> line, bool warn)
        {
            return get_BEptr()->readString__BOSS(line, warn);
        }
        
        inline bool Settings::readString(::std::basic_string<char> line)
        {
            return get_BEptr()->readString__BOSS(line);
        }
        
        inline bool Settings::readingFailed()
        {
            return get_BEptr()->readingFailed();
        }
        
        inline bool Settings::writeFile(::std::basic_string<char> toFile, bool writeAll)
        {
            return get_BEptr()->writeFile(toFile, writeAll);
        }
        
        inline bool Settings::writeFile(::std::basic_string<char> toFile)
        {
            return get_BEptr()->writeFile__BOSS(toFile);
        }
        
        inline bool Settings::writeFile(::std::basic_ostream<char>& os, bool writeAll)
        {
            return get_BEptr()->writeFile(os, writeAll);
        }
        
        inline bool Settings::writeFile(::std::basic_ostream<char>& os)
        {
            return get_BEptr()->writeFile__BOSS(os);
        }
        
        inline bool Settings::writeFile()
        {
            return get_BEptr()->writeFile__BOSS();
        }
        
        inline void Settings::listAll(::std::basic_ostream<char>& os)
        {
            get_BEptr()->listAll(os);
        }
        
        inline void Settings::listAll()
        {
            get_BEptr()->listAll__BOSS();
        }
        
        inline void Settings::listChanged(::std::basic_ostream<char>& os)
        {
            get_BEptr()->listChanged(os);
        }
        
        inline void Settings::listChanged()
        {
            get_BEptr()->listChanged__BOSS();
        }
        
        inline void Settings::list(::std::basic_string<char> match, ::std::basic_ostream<char>& os)
        {
            get_BEptr()->list(match, os);
        }
        
        inline void Settings::list(::std::basic_string<char> match)
        {
            get_BEptr()->list__BOSS(match);
        }
        
        inline ::std::basic_string<char> Settings::output(::std::basic_string<char> keyIn, bool fullLine)
        {
            return get_BEptr()->output(keyIn, fullLine);
        }
        
        inline ::std::basic_string<char> Settings::output(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->output__BOSS(keyIn);
        }
        
        inline void Settings::resetAll()
        {
            get_BEptr()->resetAll();
        }
        
        inline bool Settings::isFlag(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->isFlag(keyIn);
        }
        
        inline bool Settings::isMode(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->isMode(keyIn);
        }
        
        inline bool Settings::isParm(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->isParm(keyIn);
        }
        
        inline bool Settings::isWord(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->isWord(keyIn);
        }
        
        inline bool Settings::isFVec(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->isFVec(keyIn);
        }
        
        inline bool Settings::isMVec(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->isMVec(keyIn);
        }
        
        inline bool Settings::isPVec(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->isPVec(keyIn);
        }
        
        inline void Settings::addFlag(::std::basic_string<char> keyIn, bool defaultIn)
        {
            get_BEptr()->addFlag(keyIn, defaultIn);
        }
        
        inline void Settings::addMode(::std::basic_string<char> keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn, bool optOnlyIn)
        {
            get_BEptr()->addMode(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn, optOnlyIn);
        }
        
        inline void Settings::addMode(::std::basic_string<char> keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn)
        {
            get_BEptr()->addMode__BOSS(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline void Settings::addParm(::std::basic_string<char> keyIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn)
        {
            get_BEptr()->addParm(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline void Settings::addWord(::std::basic_string<char> keyIn, ::std::basic_string<char> defaultIn)
        {
            get_BEptr()->addWord(keyIn, defaultIn);
        }
        
        inline void Settings::addFVec(::std::basic_string<char> keyIn, ::std::vector<bool> defaultIn)
        {
            get_BEptr()->addFVec(keyIn, defaultIn);
        }
        
        inline void Settings::addMVec(::std::basic_string<char> keyIn, ::std::vector<int> defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn)
        {
            get_BEptr()->addMVec(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline void Settings::addPVec(::std::basic_string<char> keyIn, ::std::vector<double> defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn)
        {
            get_BEptr()->addPVec(keyIn, defaultIn, hasMinIn, hasMaxIn, minIn, maxIn);
        }
        
        inline bool Settings::flag(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->flag(keyIn);
        }
        
        inline int Settings::mode(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->mode(keyIn);
        }
        
        inline double Settings::parm(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->parm(keyIn);
        }
        
        inline ::std::basic_string<char> Settings::word(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->word(keyIn);
        }
        
        inline ::std::vector<bool> Settings::fvec(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->fvec(keyIn);
        }
        
        inline ::std::vector<int> Settings::mvec(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->mvec(keyIn);
        }
        
        inline ::std::vector<double> Settings::pvec(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->pvec(keyIn);
        }
        
        inline bool Settings::flagDefault(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->flagDefault(keyIn);
        }
        
        inline int Settings::modeDefault(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->modeDefault(keyIn);
        }
        
        inline double Settings::parmDefault(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->parmDefault(keyIn);
        }
        
        inline ::std::basic_string<char> Settings::wordDefault(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->wordDefault(keyIn);
        }
        
        inline ::std::vector<bool> Settings::fvecDefault(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->fvecDefault(keyIn);
        }
        
        inline ::std::vector<int> Settings::mvecDefault(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->mvecDefault(keyIn);
        }
        
        inline ::std::vector<double> Settings::pvecDefault(::std::basic_string<char> keyIn)
        {
            return get_BEptr()->pvecDefault(keyIn);
        }
        
        inline void Settings::flag(::std::basic_string<char> keyIn, bool nowIn)
        {
            get_BEptr()->flag(keyIn, nowIn);
        }
        
        inline bool Settings::mode(::std::basic_string<char> keyIn, int nowIn)
        {
            return get_BEptr()->mode(keyIn, nowIn);
        }
        
        inline void Settings::parm(::std::basic_string<char> keyIn, double nowIn)
        {
            get_BEptr()->parm(keyIn, nowIn);
        }
        
        inline void Settings::word(::std::basic_string<char> keyIn, ::std::basic_string<char> nowIn)
        {
            get_BEptr()->word(keyIn, nowIn);
        }
        
        inline void Settings::fvec(::std::basic_string<char> keyIn, ::std::vector<bool> nowIn)
        {
            get_BEptr()->fvec(keyIn, nowIn);
        }
        
        inline void Settings::mvec(::std::basic_string<char> keyIn, ::std::vector<int> nowIn)
        {
            get_BEptr()->mvec(keyIn, nowIn);
        }
        
        inline void Settings::pvec(::std::basic_string<char> keyIn, ::std::vector<double> nowIn)
        {
            get_BEptr()->pvec(keyIn, nowIn);
        }
        
        inline void Settings::forceMode(::std::basic_string<char> keyIn, int nowIn)
        {
            get_BEptr()->forceMode(keyIn, nowIn);
        }
        
        inline void Settings::forceParm(::std::basic_string<char> keyIn, double nowIn)
        {
            get_BEptr()->forceParm(keyIn, nowIn);
        }
        
        inline void Settings::forceMVec(::std::basic_string<char> keyIn, ::std::vector<int> nowIn)
        {
            get_BEptr()->forceMVec(keyIn, nowIn);
        }
        
        inline void Settings::forcePVec(::std::basic_string<char> keyIn, ::std::vector<double> nowIn)
        {
            get_BEptr()->forcePVec(keyIn, nowIn);
        }
        
        inline void Settings::resetFlag(::std::basic_string<char> keyIn)
        {
            get_BEptr()->resetFlag(keyIn);
        }
        
        inline void Settings::resetMode(::std::basic_string<char> keyIn)
        {
            get_BEptr()->resetMode(keyIn);
        }
        
        inline void Settings::resetParm(::std::basic_string<char> keyIn)
        {
            get_BEptr()->resetParm(keyIn);
        }
        
        inline void Settings::resetWord(::std::basic_string<char> keyIn)
        {
            get_BEptr()->resetWord(keyIn);
        }
        
        inline void Settings::resetFVec(::std::basic_string<char> keyIn)
        {
            get_BEptr()->resetFVec(keyIn);
        }
        
        inline void Settings::resetMVec(::std::basic_string<char> keyIn)
        {
            get_BEptr()->resetMVec(keyIn);
        }
        
        inline void Settings::resetPVec(::std::basic_string<char> keyIn)
        {
            get_BEptr()->resetPVec(keyIn);
        }
        
        inline bool Settings::getIsInit()
        {
            return get_BEptr()->getIsInit();
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

#endif /* __wrapper_Settings_def_Pythia_8_212_h__ */
