#ifndef __wrapper_Logger_decl_Pythia_8_312_h__
#define __wrapper_Logger_decl_Pythia_8_312_h__

#include <cstddef>
#include <string>
#include <ostream>
#include <mutex>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Logger.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Logger : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Logger* (*__factory0)();
        
                // -- Other member variables: 
            public:
                const int& ABORT;
                const int& NORMAL;
                const int& REPORT;
        
                // Member functions: 
            public:
                void init(Pythia8::Settings& settings);
        
                void reportMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways);
        
                void reportMsg(std::string loc, std::string message, std::string extraInfo);
        
                void reportMsg(std::string loc, std::string message);
        
                void infoMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways);
        
                void infoMsg(std::string loc, std::string message, std::string extraInfo);
        
                void infoMsg(std::string loc, std::string message);
        
                void warningMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways);
        
                void warningMsg(std::string loc, std::string message, std::string extraInfo);
        
                void warningMsg(std::string loc, std::string message);
        
                void errorMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways);
        
                void errorMsg(std::string loc, std::string message, std::string extraInfo);
        
                void errorMsg(std::string loc, std::string message);
        
                void abortMsg(std::string loc, std::string message, std::string extraInfo, bool showAlways);
        
                void abortMsg(std::string loc, std::string message, std::string extraInfo);
        
                void abortMsg(std::string loc, std::string message);
        
                bool isQuiet() const;
        
                bool mayPrintInit() const;
        
                bool mayPrintNext() const;
        
                bool mayPrintErrors() const;
        
                void setVerbosity(int verbosityIn);
        
                int getVerbosity() const;
        
                void errorCombine(const Pythia8::Logger& other, std::string prefix);
        
                void errorCombine(const Pythia8::Logger& other);
        
                void errorReset();
        
                int errorTotalNumber() const;
        
                void errorStatistics() const;
        
                void errorStatistics(std::ostream& stream) const;
        
                ::std::ostream& infoStream();
        
                ::std::ostream& errorStream();
        
                ::std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int>> begin();
        
                ::std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int>> end();
        
                ::std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, int>> begin() const;
        
                ::std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, int>> end() const;
        
        
                // Wrappers for original constructors: 
            public:
                Logger();
        
                // Special pointer-based constructor: 
                Logger(Abstract_Logger* in);
        
                // Destructor: 
                ~Logger();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Logger* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Logger_decl_Pythia_8_312_h__ */
