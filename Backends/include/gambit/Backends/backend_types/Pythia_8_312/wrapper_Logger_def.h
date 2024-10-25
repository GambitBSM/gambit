#ifndef __wrapper_Logger_def_Pythia_8_312_h__
#define __wrapper_Logger_def_Pythia_8_312_h__

#include <string>
#include <ostream>
#include <mutex>
#include "wrapper_Settings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        // Member functions: 
        inline void Logger::init(Pythia8::Settings& settings)
        {
            get_BEptr()->init__BOSS(*settings.get_BEptr());
        }
        
        inline void Logger::reportMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways)
        {
            get_BEptr()->reportMsg(loc, message, extraInfo, showAlways);
        }
        
        inline void Logger::reportMsg(std::string loc, std::string message, std::string extraInfo)
        {
            get_BEptr()->reportMsg__BOSS(loc, message, extraInfo);
        }
        
        inline void Logger::reportMsg(std::string loc, std::string message)
        {
            get_BEptr()->reportMsg__BOSS(loc, message);
        }
        
        inline void Logger::infoMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways)
        {
            get_BEptr()->infoMsg(loc, message, extraInfo, showAlways);
        }
        
        inline void Logger::infoMsg(std::string loc, std::string message, std::string extraInfo)
        {
            get_BEptr()->infoMsg__BOSS(loc, message, extraInfo);
        }
        
        inline void Logger::infoMsg(std::string loc, std::string message)
        {
            get_BEptr()->infoMsg__BOSS(loc, message);
        }
        
        inline void Logger::warningMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways)
        {
            get_BEptr()->warningMsg(loc, message, extraInfo, showAlways);
        }
        
        inline void Logger::warningMsg(std::string loc, std::string message, std::string extraInfo)
        {
            get_BEptr()->warningMsg__BOSS(loc, message, extraInfo);
        }
        
        inline void Logger::warningMsg(std::string loc, std::string message)
        {
            get_BEptr()->warningMsg__BOSS(loc, message);
        }
        
        inline void Logger::errorMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways)
        {
            get_BEptr()->errorMsg(loc, message, extraInfo, showAlways);
        }
        
        inline void Logger::errorMsg(std::string loc, std::string message, std::string extraInfo)
        {
            get_BEptr()->errorMsg__BOSS(loc, message, extraInfo);
        }
        
        inline void Logger::errorMsg(std::string loc, std::string message)
        {
            get_BEptr()->errorMsg__BOSS(loc, message);
        }
        
        inline void Logger::abortMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways)
        {
            get_BEptr()->abortMsg(loc, message, extraInfo, showAlways);
        }
        
        inline void Logger::abortMsg(std::string loc, std::string message, std::string extraInfo)
        {
            get_BEptr()->abortMsg__BOSS(loc, message, extraInfo);
        }
        
        inline void Logger::abortMsg(std::string loc, std::string message)
        {
            get_BEptr()->abortMsg__BOSS(loc, message);
        }
        
        inline bool Logger::isQuiet() const
        {
            return get_BEptr()->isQuiet();
        }
        
        inline bool Logger::mayPrintInit() const
        {
            return get_BEptr()->mayPrintInit();
        }
        
        inline bool Logger::mayPrintNext() const
        {
            return get_BEptr()->mayPrintNext();
        }
        
        inline bool Logger::mayPrintErrors() const
        {
            return get_BEptr()->mayPrintErrors();
        }
        
        inline void Logger::setVerbosity(int verbosityIn)
        {
            get_BEptr()->setVerbosity(verbosityIn);
        }
        
        inline int Logger::getVerbosity() const
        {
            return get_BEptr()->getVerbosity();
        }
        
        inline void Logger::errorCombine(const Pythia8::Logger& other, std::string prefix)
        {
            get_BEptr()->errorCombine__BOSS(*other.get_BEptr(), prefix);
        }
        
        inline void Logger::errorCombine(const Pythia8::Logger& other)
        {
            get_BEptr()->errorCombine__BOSS(*other.get_BEptr());
        }
        
        inline void Logger::errorReset()
        {
            get_BEptr()->errorReset();
        }
        
        inline int Logger::errorTotalNumber() const
        {
            return get_BEptr()->errorTotalNumber();
        }
        
        inline void Logger::errorStatistics() const
        {
            get_BEptr()->errorStatistics();
        }
        
        inline void Logger::errorStatistics(std::ostream& stream) const
        {
            get_BEptr()->errorStatistics(stream);
        }
        
        inline ::std::ostream& Logger::infoStream()
        {
            return get_BEptr()->infoStream();
        }
        
        inline ::std::ostream& Logger::errorStream()
        {
            return get_BEptr()->errorStream();
        }
        
        inline ::std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int>> Logger::begin()
        {
            return get_BEptr()->begin();
        }
        
        inline ::std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int>> Logger::end()
        {
            return get_BEptr()->end();
        }
        
        inline ::std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, int>> Logger::begin() const
        {
            return get_BEptr()->begin();
        }
        
        inline ::std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, int>> Logger::end() const
        {
            return get_BEptr()->end();
        }
        
        
        // Wrappers for original constructors: 
        inline Logger::Logger() :
            WrapperBase(__factory0()),
            ABORT( get_BEptr()->ABORT_ref__BOSS()),
            NORMAL( get_BEptr()->NORMAL_ref__BOSS()),
            REPORT( get_BEptr()->REPORT_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Special pointer-based constructor: 
        inline Logger::Logger(Abstract_Logger* in) :
            WrapperBase(in),
            ABORT( get_BEptr()->ABORT_ref__BOSS()),
            NORMAL( get_BEptr()->NORMAL_ref__BOSS()),
            REPORT( get_BEptr()->REPORT_ref__BOSS())
        {
            get_BEptr()->set_wptr(this);
            get_BEptr()->set_delete_wrapper(false);
        }
        
        // Destructor: 
        inline Logger::~Logger()
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
        inline Abstract_Logger* Pythia8::Logger::get_BEptr() const
        {
            return dynamic_cast<Abstract_Logger*>(BEptr);
        }
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Logger_def_Pythia_8_312_h__ */
