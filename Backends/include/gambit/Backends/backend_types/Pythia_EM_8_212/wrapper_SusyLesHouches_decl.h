#ifndef __wrapper_SusyLesHouches_decl_Pythia_EM_8_212_h__
#define __wrapper_SusyLesHouches_decl_Pythia_EM_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SusyLesHouches.h"
#include <string>
#include <istream>
#include "SLHAea/slhaea.h"
#include <map>
#include <vector>

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
                static Pythia8::Abstract_SusyLesHouches* (*__factory0)(int);
                static Pythia8::Abstract_SusyLesHouches* (*__factory1)();
                static Pythia8::Abstract_SusyLesHouches* (*__factory2)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int);
                static Pythia8::Abstract_SusyLesHouches* (*__factory3)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
        
                // -- Other member variables: 
            public:
                std::basic_string<char, std::char_traits<char>, std::allocator<char> >& slhaFile;
                std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int> > >& decayIndices;
                std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > >& qnumbersName;
                std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > >& qnumbersAntiName;
        
                // Member functions: 
            public:
                int readFile(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > slhaFileIn, int verboseIn, bool useDecayIn);
        
                int readFile(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > slhaFileIn, int verboseIn);
        
                int readFile(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > slhaFileIn);
        
                int readFile();
        
                int readFile(::std::basic_istream<char, std::char_traits<char> >& arg_1, int verboseIn, bool useDecayIn);
        
                int readFile(::std::basic_istream<char, std::char_traits<char> >& arg_1, int verboseIn);
        
                int readFile(::std::basic_istream<char, std::char_traits<char> >& arg_1);
        
                int readSLHAea(int verboseIn, bool useDecayIn);
        
                int readSLHAea(int verboseIn);
        
                int readSLHAea();
        
                void setSLHAea(const ::SLHAea::Coll* inputSLHAea);
        
                void printHeader();
        
                void printFooter();
        
                void printSpectrum(int ifail);
        
                void printSpectrum();
        
                int checkSpectrum();
        
                int verbose();
        
                void verbose(int verboseIn);
        
                void message(int arg_1, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > arg_2, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > arg_3, int line);
        
                void message(int arg_1, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > arg_2, ::std::basic_string<char, std::char_traits<char>, std::allocator<char> > arg_3);
        
                void toLower(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >& name);
        
        
                // Wrappers for original constructors: 
            public:
                SusyLesHouches(int verboseIn);
                SusyLesHouches();
                SusyLesHouches(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > filename, int verboseIn);
                SusyLesHouches(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > filename);
        
                // Special pointer-based constructor: 
                SusyLesHouches(Pythia8::Abstract_SusyLesHouches* in);
        
                // Copy constructor: 
                SusyLesHouches(const SusyLesHouches& in);
        
                // Assignment operator: 
                SusyLesHouches& operator=(const SusyLesHouches& in);
        
                // Destructor: 
                ~SusyLesHouches();
        
                // Returns correctly casted pointer to Abstract class: 
                Pythia8::Abstract_SusyLesHouches* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SusyLesHouches_decl_Pythia_EM_8_212_h__ */
