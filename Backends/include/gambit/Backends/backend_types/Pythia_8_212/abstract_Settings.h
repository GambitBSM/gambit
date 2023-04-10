#ifndef __abstract_Settings_Pythia_8_212_h__
#define __abstract_Settings_Pythia_8_212_h__

#include <cstddef>
#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "wrapper_Info_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    
    namespace Pythia8
    {
        class Abstract_Settings : public virtual AbstractBase
        {
            public:
    
                virtual void initPtr__BOSS(Pythia8::Abstract_Info*) =0;
    
                virtual bool init(std::string, bool, std::ostream&) =0;
    
                virtual bool init__BOSS(std::string, bool) =0;
    
                virtual bool init__BOSS(std::string) =0;
    
                virtual bool init__BOSS() =0;
    
                virtual bool reInit(std::string, std::ostream&) =0;
    
                virtual bool reInit__BOSS(std::string) =0;
    
                virtual bool reInit__BOSS() =0;
    
                virtual bool readString(std::string, bool, std::ostream&) =0;
    
                virtual bool readString__BOSS(std::string, bool) =0;
    
                virtual bool readString__BOSS(std::string) =0;
    
                virtual bool readingFailed() =0;
    
                virtual bool writeFile(std::string, bool) =0;
    
                virtual bool writeFile__BOSS(std::string) =0;
    
                virtual bool writeFile(std::ostream&, bool) =0;
    
                virtual bool writeFile__BOSS(std::ostream&) =0;
    
                virtual bool writeFile__BOSS() =0;
    
                virtual void listAll(std::ostream&) =0;
    
                virtual void listAll__BOSS() =0;
    
                virtual void listChanged(std::ostream&) =0;
    
                virtual void listChanged__BOSS() =0;
    
                virtual void list(std::string, std::ostream&) =0;
    
                virtual void list__BOSS(std::string) =0;
    
                virtual ::std::string output(std::string, bool) =0;
    
                virtual ::std::string output__BOSS(std::string) =0;
    
                virtual void resetAll() =0;
    
                virtual bool isFlag(std::string) =0;
    
                virtual bool isMode(std::string) =0;
    
                virtual bool isParm(std::string) =0;
    
                virtual bool isWord(std::string) =0;
    
                virtual bool isFVec(std::string) =0;
    
                virtual bool isMVec(std::string) =0;
    
                virtual bool isPVec(std::string) =0;
    
                virtual void addFlag(std::string, bool) =0;
    
                virtual void addMode(std::string, int, bool, bool, int, int, bool) =0;
    
                virtual void addMode__BOSS(std::string, int, bool, bool, int, int) =0;
    
                virtual void addParm(std::string, double, bool, bool, double, double) =0;
    
                virtual void addWord(std::string, std::string) =0;
    
                virtual void addFVec(std::string, std::vector<bool>) =0;
    
                virtual void addMVec(std::string, std::vector<int>, bool, bool, int, int) =0;
    
                virtual void addPVec(std::string, std::vector<double>, bool, bool, double, double) =0;
    
                virtual bool flag(std::string) =0;
    
                virtual int mode(std::string) =0;
    
                virtual double parm(std::string) =0;
    
                virtual ::std::string word(std::string) =0;
    
                virtual ::std::vector<bool> fvec(std::string) =0;
    
                virtual ::std::vector<int> mvec(std::string) =0;
    
                virtual ::std::vector<double> pvec(std::string) =0;
    
                virtual bool flagDefault(std::string) =0;
    
                virtual int modeDefault(std::string) =0;
    
                virtual double parmDefault(std::string) =0;
    
                virtual ::std::string wordDefault(std::string) =0;
    
                virtual ::std::vector<bool> fvecDefault(std::string) =0;
    
                virtual ::std::vector<int> mvecDefault(std::string) =0;
    
                virtual ::std::vector<double> pvecDefault(std::string) =0;
    
                virtual void flag(std::string, bool) =0;
    
                virtual bool mode(std::string, int) =0;
    
                virtual void parm(std::string, double) =0;
    
                virtual void word(std::string, std::string) =0;
    
                virtual void fvec(std::string, std::vector<bool>) =0;
    
                virtual void mvec(std::string, std::vector<int>) =0;
    
                virtual void pvec(std::string, std::vector<double>) =0;
    
                virtual void forceMode(std::string, int) =0;
    
                virtual void forceParm(std::string, double) =0;
    
                virtual void forceMVec(std::string, std::vector<int>) =0;
    
                virtual void forcePVec(std::string, std::vector<double>) =0;
    
                virtual void resetFlag(std::string) =0;
    
                virtual void resetMode(std::string) =0;
    
                virtual void resetParm(std::string) =0;
    
                virtual void resetWord(std::string) =0;
    
                virtual void resetFVec(std::string) =0;
    
                virtual void resetMVec(std::string) =0;
    
                virtual void resetPVec(std::string) =0;
    
                virtual bool getIsInit() =0;
    
            public:
                virtual void pointer_assign__BOSS(Abstract_Settings*) =0;
                virtual Abstract_Settings* pointer_copy__BOSS() =0;
    
            private:
                Settings* wptr;
                bool delete_wrapper;
            public:
                Settings* get_wptr() { return wptr; }
                void set_wptr(Settings* wptr_in) { wptr = wptr_in; }
                bool get_delete_wrapper() { return delete_wrapper; }
                void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
    
            public:
                Abstract_Settings()
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Settings(const Abstract_Settings&)
                {
                    wptr = 0;
                    delete_wrapper = false;
                }
    
                Abstract_Settings& operator=(const Abstract_Settings&) { return *this; }
    
                virtual void init_wrapper() =0;
    
                Settings* get_init_wptr()
                {
                    init_wrapper();
                    return wptr;
                }
    
                Settings& get_init_wref()
                {
                    init_wrapper();
                    return *wptr;
                }
    
                virtual ~Abstract_Settings() =0;
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Settings_Pythia_8_212_h__ */
