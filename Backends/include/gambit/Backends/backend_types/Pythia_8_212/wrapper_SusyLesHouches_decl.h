#ifndef __wrapper_SusyLesHouches_decl_Pythia_8_212_h__
#define __wrapper_SusyLesHouches_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include <istream>
#include <map>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SusyLesHouches.h"
#include "SLHAea/slhaea.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class SusyLesHouches : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_SusyLesHouches* (*__factory0)(int);
                static Abstract_SusyLesHouches* (*__factory1)();
                static Abstract_SusyLesHouches* (*__factory2)(std::string, int);
                static Abstract_SusyLesHouches* (*__factory3)(std::string);
        
                // -- Other member variables: 
            public:
                std::string& slhaFile;
                std::map<int, int>& decayIndices;
                std::vector<std::string>& qnumbersName;
                std::vector<std::string>& qnumbersAntiName;
        
                // Member functions: 
            public:
                int readFile(std::string slhaFileIn, int verboseIn, bool useDecayIn);
        
                int readFile(std::string slhaFileIn, int verboseIn);
        
                int readFile(std::string slhaFileIn);
        
                int readFile();
        
                int readFile(std::istream& arg_1, int verboseIn, bool useDecayIn);
        
                int readFile(std::istream& arg_1, int verboseIn);
        
                int readFile(std::istream& arg_1);
        
                void setSLHAea(const SLHAea::Coll* inputSLHAea);
        
                void printHeader();
        
                void printFooter();
        
                void printSpectrum(int ifail);
        
                void printSpectrum();
        
                int checkSpectrum();
        
                int verbose();
        
                void verbose(int verboseIn);
        
                void message(int arg_1, std::string arg_2, std::string arg_3, int line);
        
                void message(int arg_1, std::string arg_2, std::string arg_3);
        
                void toLower(std::string& name);
        
        
                // Wrappers for original constructors: 
            public:
                SusyLesHouches(int verboseIn);
                SusyLesHouches();
                SusyLesHouches(std::string filename, int verboseIn);
                SusyLesHouches(std::string filename);
        
                // Special pointer-based constructor: 
                SusyLesHouches(Abstract_SusyLesHouches* in);
        
                // Copy constructor: 
                SusyLesHouches(const SusyLesHouches& in);
        
                // Assignment operator: 
                SusyLesHouches& operator=(const SusyLesHouches& in);
        
                // Destructor: 
                ~SusyLesHouches();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_SusyLesHouches* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SusyLesHouches_decl_Pythia_8_212_h__ */
