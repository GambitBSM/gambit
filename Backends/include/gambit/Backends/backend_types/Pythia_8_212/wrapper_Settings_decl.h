#ifndef __wrapper_Settings_decl_Pythia_8_212_h__
#define __wrapper_Settings_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include <ostream>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Settings.h"
#include "wrapper_Info_decl.h"

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
                void initPtr(Pythia8::Info* infoPtrIn);
        
                bool init(std::string startFile, bool append, std::ostream& os);
        
                bool init(std::string startFile, bool append);
        
                bool init(std::string startFile);
        
                bool init();
        
                bool reInit(std::string startFile, std::ostream& os);
        
                bool reInit(std::string startFile);
        
                bool reInit();
        
                bool readString(std::string line, bool warn, std::ostream& os);
        
                bool readString(std::string line, bool warn);
        
                bool readString(std::string line);
        
                bool readingFailed();
        
                bool writeFile(std::string toFile, bool writeAll);
        
                bool writeFile(std::string toFile);
        
                bool writeFile(std::ostream& os, bool writeAll);
        
                bool writeFile(std::ostream& os);
        
                bool writeFile();
        
                void listAll(std::ostream& os);
        
                void listAll();
        
                void listChanged(std::ostream& os);
        
                void listChanged();
        
                void list(std::string match, std::ostream& os);
        
                void list(std::string match);
        
                ::std::string output(std::string keyIn, bool fullLine);
        
                ::std::string output(std::string keyIn);
        
                void resetAll();
        
                bool isFlag(std::string keyIn);
        
                bool isMode(std::string keyIn);
        
                bool isParm(std::string keyIn);
        
                bool isWord(std::string keyIn);
        
                bool isFVec(std::string keyIn);
        
                bool isMVec(std::string keyIn);
        
                bool isPVec(std::string keyIn);
        
                void addFlag(std::string keyIn, bool defaultIn);
        
                void addMode(std::string keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn, bool optOnlyIn);
        
                void addMode(std::string keyIn, int defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn);
        
                void addParm(std::string keyIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn);
        
                void addWord(std::string keyIn, std::string defaultIn);
        
                void addFVec(std::string keyIn, std::vector<bool> defaultIn);
        
                void addMVec(std::string keyIn, std::vector<int> defaultIn, bool hasMinIn, bool hasMaxIn, int minIn, int maxIn);
        
                void addPVec(std::string keyIn, std::vector<double> defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn);
        
                bool flag(std::string keyIn);
        
                int mode(std::string keyIn);
        
                double parm(std::string keyIn);
        
                ::std::string word(std::string keyIn);
        
                ::std::vector<bool> fvec(std::string keyIn);
        
                ::std::vector<int> mvec(std::string keyIn);
        
                ::std::vector<double> pvec(std::string keyIn);
        
                bool flagDefault(std::string keyIn);
        
                int modeDefault(std::string keyIn);
        
                double parmDefault(std::string keyIn);
        
                ::std::string wordDefault(std::string keyIn);
        
                ::std::vector<bool> fvecDefault(std::string keyIn);
        
                ::std::vector<int> mvecDefault(std::string keyIn);
        
                ::std::vector<double> pvecDefault(std::string keyIn);
        
                void flag(std::string keyIn, bool nowIn);
        
                bool mode(std::string keyIn, int nowIn);
        
                void parm(std::string keyIn, double nowIn);
        
                void word(std::string keyIn, std::string nowIn);
        
                void fvec(std::string keyIn, std::vector<bool> nowIn);
        
                void mvec(std::string keyIn, std::vector<int> nowIn);
        
                void pvec(std::string keyIn, std::vector<double> nowIn);
        
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
        
                bool getIsInit();
        
        
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

#endif /* __wrapper_Settings_decl_Pythia_8_212_h__ */
