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
                static Abstract_SusyLesHouches* (*__factory2)(::std::basic_string<char>, int);
                static Abstract_SusyLesHouches* (*__factory3)(::std::basic_string<char>);
        
                // -- Other member variables: 
            public:
                std::basic_string<char>& slhaFile;
                std::map<int, int>& decayIndices;
                std::vector<std::basic_string<char>>& qnumbersName;
                std::vector<std::basic_string<char>>& qnumbersAntiName;
        
                // Member functions: 
            public:
                int readFile(::std::basic_string<char> slhaFileIn, int verboseIn, bool useDecayIn);
        
                int readFile(::std::basic_string<char> slhaFileIn, int verboseIn);
        
                int readFile(::std::basic_string<char> slhaFileIn);
        
                int readFile();
        
                int readFile(::std::basic_istream<char>& arg_1, int verboseIn, bool useDecayIn);
        
                int readFile(::std::basic_istream<char>& arg_1, int verboseIn);
        
                int readFile(::std::basic_istream<char>& arg_1);
        
                void setSLHAea(const ::SLHAea::Coll* inputSLHAea);
        
                void printHeader();
        
                void printFooter();
        
                void printSpectrum(int ifail);
        
                void printSpectrum();
        
                int checkSpectrum();
        
                int verbose();
        
                void verbose(int verboseIn);
        
                void message(int arg_1, ::std::basic_string<char> arg_2, ::std::basic_string<char> arg_3, int line);
        
                void message(int arg_1, ::std::basic_string<char> arg_2, ::std::basic_string<char> arg_3);
        
                void toLower(::std::basic_string<char>& name);
        
        
                // Wrappers for original constructors: 
            public:
                SusyLesHouches(int verboseIn);
                SusyLesHouches();
                SusyLesHouches(::std::basic_string<char> filename, int verboseIn);
                SusyLesHouches(::std::basic_string<char> filename);
        
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
