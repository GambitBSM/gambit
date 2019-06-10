#ifndef __wrapper_Hist_decl_Pythia_EM_8_212_h__
#define __wrapper_Hist_decl_Pythia_EM_8_212_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Hist.h"
#include <string>
#include <ostream>
#include <vector>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Hist : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Pythia8::Abstract_Hist* (*__factory0)();
                static Pythia8::Abstract_Hist* (*__factory1)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, double, double);
                static Pythia8::Abstract_Hist* (*__factory2)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, double);
                static Pythia8::Abstract_Hist* (*__factory3)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int);
                static Pythia8::Abstract_Hist* (*__factory4)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
                static Pythia8::Abstract_Hist* (*__factory5)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >, const Pythia8::Hist&);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn, double xMaxIn);
        
                void book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn);
        
                void book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn);
        
                void book(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn);
        
                void book();
        
                void name(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn);
        
                void name();
        
                void null();
        
                void fill(double x, double w);
        
                void fill(double x);
        
                void table(::std::basic_ostream<char, std::char_traits<char> >& os, bool printOverUnder, bool xMidBin) const;
        
                void table(::std::basic_ostream<char, std::char_traits<char> >& os, bool printOverUnder) const;
        
                void table(::std::basic_ostream<char, std::char_traits<char> >& os) const;
        
                void table() const;
        
                void table(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > fileName, bool printOverUnder, bool xMidBin) const;
        
                void table(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > fileName, bool printOverUnder) const;
        
                void table(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > fileName) const;
        
                double getBinContent(int iBin) const;
        
                int getEntries() const;
        
                bool sameSize(const Pythia8::Hist& h) const;
        
                void takeLog(bool tenLog);
        
                void takeLog();
        
                void takeSqrt();
        
                Pythia8::Hist& operator+=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator-=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator*=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator/=(const Pythia8::Hist& h);
        
                Pythia8::Hist& operator+=(double f);
        
                Pythia8::Hist& operator-=(double f);
        
                Pythia8::Hist& operator*=(double f);
        
                Pythia8::Hist& operator/=(double f);
        
        
                // Wrappers for original constructors: 
            public:
                Hist();
                Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn, double xMaxIn);
                Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn, double xMinIn);
                Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, int nBinIn);
                Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn);
                Hist(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > titleIn, const Pythia8::Hist& h);
        
                // Special pointer-based constructor: 
                Hist(Pythia8::Abstract_Hist* in);
        
                // Copy constructor: 
                Hist(const Hist& in);
        
                // Assignment operator: 
                Hist& operator=(const Hist& in);
        
                // Destructor: 
                ~Hist();
        
                // Returns correctly casted pointer to Abstract class: 
                Pythia8::Abstract_Hist* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Hist_decl_Pythia_EM_8_212_h__ */
