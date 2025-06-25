#ifndef __wrapper_Settings_decl_Pythia_8_312_h__
#define __wrapper_Settings_decl_Pythia_8_312_h__

#include <cstddef>
#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <set>
#include <map>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Settings.h"
#include "wrapper_Logger_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Settings : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Settings* (*__factory0)();
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void initPtrs(Pythia8::Logger* loggerPtrIn);
        
                bool init(std::string startFile, bool append);
        
                bool init(std::string startFile);
        
                bool init();
        
                bool init(std::istream& is, bool append);
        
                bool init(std::istream& is);
        
                bool reInit(std::string startFile);
        
                bool reInit();
        
                bool readString(std::string line, bool warn);
        
                bool readString(std::string line);
        
                bool registerPluginLibrary(std::string libName, std::string startFile);
        
                bool registerPluginLibrary(std::string libName);
        
                bool writeFile(std::string toFile, bool writeAll);
        
                bool writeFile(std::string toFile);
        
                bool writeFile(std::ostream& os, bool writeAll);
        
                bool writeFile(std::ostream& os);
        
                bool writeFile();
        
                bool writeFileXML(std::ostream& os);
        
                bool writeFileXML();
        
                void listAll();
        
                void listChanged();
        
                void list(std::string match);
        
                ::std::string output(std::string keyIn, bool fullLine);
        
                ::std::string output(std::string keyIn);
        
                ::std::vector<std::string> getReadHistory(int subrun);
        
                ::std::vector<std::string> getReadHistory();
        
                void resetAll();
        
                bool isFlag(std::string keyIn);
        
                bool isMode(std::string keyIn);
        
                bool isParm(std::string keyIn);
        
                bool isWord(std::string keyIn);
        
                bool isFVec(std::string keyIn);
        
                bool isMVec(std::string keyIn);
        
                bool isPVec(std::string keyIn);
        
                bool isWVec(std::string keyIn);
        
                void addFlag(std::string keyIn, bool defaultIn);
        
                void addMode(std::string keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn, bool optOnlyIn);
        
                void addMode(std::string keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn);
        
                void addParm(std::string keyIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn);
        
                void addWord(std::string keyIn, std::string defaultIn);
        
                void addFVec(std::string keyIn, std::vector<bool> defaultIn);
        
                void addMVec(std::string keyIn, std::vector<int> defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn);
        
                void addPVec(std::string keyIn, std::vector<double> defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn);
        
                void addWVec(std::string keyIn, std::vector<std::string> defaultIn);
        
                bool flag(std::string keyIn);
        
                int mode(std::string keyIn);
        
                double parm(std::string keyIn);
        
                ::std::string word(std::string keyIn);
        
                ::std::vector<bool> fvec(std::string keyIn);
        
                ::std::vector<int> mvec(std::string keyIn);
        
                ::std::vector<double> pvec(std::string keyIn);
        
                ::std::vector<std::string> wvec(std::string keyIn);
        
                bool flagDefault(std::string keyIn);
        
                int modeDefault(std::string keyIn);
        
                double parmDefault(std::string keyIn);
        
                ::std::string wordDefault(std::string keyIn);
        
                ::std::vector<bool> fvecDefault(std::string keyIn);
        
                ::std::vector<int> mvecDefault(std::string keyIn);
        
                ::std::vector<double> pvecDefault(std::string keyIn);
        
                ::std::vector<std::string> wvecDefault(std::string keyIn);
        
                void flag(std::string keyIn, bool nowIn, bool force);
        
                void flag(std::string keyIn, bool nowIn);
        
                bool mode(std::string keyIn, int nowIn, bool force);
        
                bool mode(std::string keyIn, int nowIn);
        
                bool parm(std::string keyIn, double nowIn, bool force);
        
                bool parm(std::string keyIn, double nowIn);
        
                void word(std::string keyIn, std::string nowIn, bool force);
        
                void word(std::string keyIn, std::string nowIn);
        
                void fvec(std::string keyIn, std::vector<bool> nowIn, bool force);
        
                void fvec(std::string keyIn, std::vector<bool> nowIn);
        
                bool mvec(std::string keyIn, std::vector<int> nowIn, bool force);
        
                bool mvec(std::string keyIn, std::vector<int> nowIn);
        
                bool pvec(std::string keyIn, std::vector<double> nowIn, bool force);
        
                bool pvec(std::string keyIn, std::vector<double> nowIn);
        
                void wvec(std::string keyIn, std::vector<std::string> nowIn, bool force);
        
                void wvec(std::string keyIn, std::vector<std::string> nowIn);
        
                void forceMode(std::string keyIn, int nowIn);
        
                void forceParm(std::string keyIn, double nowIn);
        
                void forceMVec(std::string keyIn, std::vector<int> nowIn);
        
                void forcePVec(std::string keyIn, std::vector<double> nowIn);
        
                void resetFlag(std::string keyIn);
        
                void resetMode(std::string keyIn);
        
                void resetParm(std::string keyIn);
        
                void resetWord(std::string keyIn);
        
                void resetFVec(std::string keyIn);
        
                void resetMVec(std::string keyIn);
        
                void resetPVec(std::string keyIn);
        
                void resetWVec(std::string keyIn);
        
                bool getIsInit();
        
                bool readingFailed();
        
                bool unfinishedInput();
        
                bool hasHardProc();
        
        
                // Wrappers for original constructors: 
            public:
                Settings();
        
                // Special pointer-based constructor: 
                Settings(Abstract_Settings* in);
        
                // Copy constructor: 
                Settings(const Settings& in);
        
                // Assignment operator: 
                Settings& operator=(const Settings& in);
        
                // Destructor: 
                ~Settings();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Settings* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Settings_decl_Pythia_8_312_h__ */
