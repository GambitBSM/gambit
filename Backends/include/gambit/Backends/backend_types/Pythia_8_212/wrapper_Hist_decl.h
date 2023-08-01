#ifndef __wrapper_Hist_decl_Pythia_8_212_h__
#define __wrapper_Hist_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include <ostream>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Hist.h"

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
                static Abstract_Hist* (*__factory0)();
                static Abstract_Hist* (*__factory1)(std::string, int, double, double);
                static Abstract_Hist* (*__factory2)(std::string, int, double);
                static Abstract_Hist* (*__factory3)(std::string, int);
                static Abstract_Hist* (*__factory4)(std::string);
                static Abstract_Hist* (*__factory5)(std::string, const Pythia8::Hist&);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void book(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn);
        
                void book(std::string titleIn, int nBinIn, double xMinIn);
        
                void book(std::string titleIn, int nBinIn);
        
                void book(std::string titleIn);
        
                void book();
        
                void name(std::string titleIn);
        
                void name();
        
                void null();
        
                void fill(double x, double w);
        
                void fill(double x);
        
                void table(std::ostream& os, bool printOverUnder, bool xMidBin) const;
        
                void table(std::ostream& os, bool printOverUnder) const;
        
                void table(std::ostream& os) const;
        
                void table() const;
        
                void table(std::string fileName, bool printOverUnder, bool xMidBin) const;
        
                void table(std::string fileName, bool printOverUnder) const;
        
                void table(std::string fileName) const;
        
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
                Hist(std::string titleIn, int nBinIn, double xMinIn, double xMaxIn);
                Hist(std::string titleIn, int nBinIn, double xMinIn);
                Hist(std::string titleIn, int nBinIn);
                Hist(std::string titleIn);
                Hist(std::string titleIn, const Pythia8::Hist& h);
        
                // Special pointer-based constructor: 
                Hist(Abstract_Hist* in);
        
                // Copy constructor: 
                Hist(const Hist& in);
        
                // Assignment operator: 
                Hist& operator=(const Hist& in);
        
                // Destructor: 
                ~Hist();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Hist* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Hist_decl_Pythia_8_212_h__ */
