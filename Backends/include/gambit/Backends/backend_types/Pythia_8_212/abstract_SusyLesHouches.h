#ifndef __abstract_SusyLesHouches_Pythia_8_212_h__
#define __abstract_SusyLesHouches_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <istream>
#include <map>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "SLHAea/slhaea.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_SusyLesHouches : public virtual AbstractBase
        {
            public:
    
                virtual int readFile(std::string, int, bool) =0;
    
                virtual int readFile__BOSS(std::string, int) =0;
    
                virtual int readFile__BOSS(std::string) =0;
    
                virtual int readFile__BOSS() =0;
    
                virtual int readFile(std::istream&, int, bool) =0;
    
                virtual int readFile__BOSS(std::istream&, int) =0;
    
                virtual int readFile__BOSS(std::istream&) =0;
    
                virtual void setSLHAea(const SLHAea::Coll*) =0;
    
                virtual void printHeader() =0;
    
                virtual void printFooter() =0;
    
                virtual void printSpectrum(int) =0;
    
                virtual void printSpectrum__BOSS() =0;
    
                virtual int checkSpectrum() =0;
    
                virtual std::string& slhaFile_ref__BOSS() =0;
    
                virtual std::map<int, int>& decayIndices_ref__BOSS() =0;
    
                virtual std::vector<std::string>& qnumbersName_ref__BOSS() =0;
    
                virtual std::vector<std::string>& qnumbersAntiName_ref__BOSS() =0;
    
                virtual int verbose() =0;
    
                virtual void verbose(int) =0;
    
                virtual void message(int, std::string, std::string, int) =0;
    
                virtual void message__BOSS(int, std::string, std::string) =0;
    
                virtual void toLower(std::string&) =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_SusyLesHouches*) =0;
                virtual Abstract_SusyLesHouches* pointer_copy__BOSS() =0;
    
            private:
                SusyLesHouches* wptr;
                bool delete_wrapper;
            public:
                SusyLesHouches* get_wptr() { return wptr; }
                void set_wptr(SusyLesHouches* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_SusyLesHouches()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SusyLesHouches(const Abstract_SusyLesHouches&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_SusyLesHouches& operator=(const Abstract_SusyLesHouches&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                SusyLesHouches* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                SusyLesHouches& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_SusyLesHouches() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_SusyLesHouches_Pythia_8_212_h__ */
