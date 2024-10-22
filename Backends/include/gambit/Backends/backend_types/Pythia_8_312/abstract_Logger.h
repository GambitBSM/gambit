#ifndef __abstract_Logger_Pythia_8_312_h__
#define __abstract_Logger_Pythia_8_312_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include <mutex>
#include <streambuf>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Settings_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Logger : public virtual AbstractBase
        {
            public:
    
                virtual void init__BOSS(Pythia8::Abstract_Settings&) =0;
    
                virtual void reportMsg(std::string, std::string, std::string, bool) =0;
    
                virtual void reportMsg__BOSS(std::string, std::string, std::string) =0;
    
                virtual void reportMsg__BOSS(std::string, std::string) =0;
    
                virtual void infoMsg(std::string, std::string, std::string, bool) =0;
    
                virtual void infoMsg__BOSS(std::string, std::string, std::string) =0;
    
                virtual void infoMsg__BOSS(std::string, std::string) =0;
    
                virtual void warningMsg(std::string, std::string, std::string, bool) =0;
    
                virtual void warningMsg__BOSS(std::string, std::string, std::string) =0;
    
                virtual void warningMsg__BOSS(std::string, std::string) =0;
    
                virtual void errorMsg(std::string, std::string, std::string, bool) =0;
    
                virtual void errorMsg__BOSS(std::string, std::string, std::string) =0;
    
                virtual void errorMsg__BOSS(std::string, std::string) =0;
    
                virtual void abortMsg(std::string, std::string, std::string, bool) =0;
    
                virtual void abortMsg__BOSS(std::string, std::string, std::string) =0;
    
                virtual void abortMsg__BOSS(std::string, std::string) =0;
    
                virtual bool isQuiet() const =0;
    
                virtual bool mayPrintInit() const =0;
    
                virtual bool mayPrintNext() const =0;
    
                virtual bool mayPrintErrors() const =0;
    
                virtual void setVerbosity(int) =0;
    
                virtual int getVerbosity() const =0;
    
                virtual void errorCombine__BOSS(const Pythia8::Abstract_Logger&, std::string) =0;
    
                virtual void errorCombine__BOSS(const Pythia8::Abstract_Logger&) =0;
    
                virtual void errorReset() =0;
    
                virtual int errorTotalNumber() const =0;
    
                virtual void errorStatistics() const =0;
    
                virtual void errorStatistics(std::ostream&) const =0;
    
                virtual ::std::ostream& infoStream() =0;
    
                virtual ::std::ostream& errorStream() =0;
    
                virtual ::std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int>> begin() =0;
    
                virtual ::std::_Rb_tree_iterator<std::pair<const std::basic_string<char>, int>> end() =0;
    
                virtual ::std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, int>> begin() const =0;
    
                virtual ::std::_Rb_tree_const_iterator<std::pair<const std::basic_string<char>, int>> end() const =0;
    
                virtual const int& ABORT_ref__BOSS() =0;
    
                virtual const int& NORMAL_ref__BOSS() =0;
    
                virtual const int& REPORT_ref__BOSS() =0;
    
    
            private:
                Logger* wptr;
                bool delete_wrapper;
            public:
                Logger* get_wptr() { return wptr; }
                void set_wptr(Logger* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Logger()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Logger(const Abstract_Logger&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Logger& operator=(const Abstract_Logger&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Logger* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Logger& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Logger() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Logger_Pythia_8_312_h__ */
