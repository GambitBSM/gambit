#ifndef __wrapper_SlowJet_decl_Pythia_8_212_h__
#define __wrapper_SlowJet_decl_Pythia_8_212_h__

#include <cstddef>
#include <ostream>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_SlowJet.h"
#include "wrapper_Event_decl.h"
#include "wrapper_Vec4_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class SlowJet : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_SlowJet* (*__factory0)(int, double, double, double, int, int);
                static Abstract_SlowJet* (*__factory1)(int, double, double, double, int);
                static Abstract_SlowJet* (*__factory2)(int, double, double, double);
                static Abstract_SlowJet* (*__factory3)(int, double, double);
                static Abstract_SlowJet* (*__factory4)(int, double);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                bool analyze(const Pythia8::Event& event);
        
                bool setup(const Pythia8::Event& event);
        
                bool doStep();
        
                bool doNSteps(int nStep);
        
                bool stopAtN(int nStop);
        
                int sizeOrig() const;
        
                int sizeJet() const;
        
                int sizeAll() const;
        
                double pT(int i) const;
        
                double y(int i) const;
        
                double phi(int i) const;
        
                Pythia8::Vec4 p(int i) const;
        
                double m(int i) const;
        
                int multiplicity(int i) const;
        
                int iNext() const;
        
                int jNext() const;
        
                double dNext() const;
        
                void list(bool listAll, ::std::basic_ostream<char>& os) const;
        
                void list(bool listAll) const;
        
                void list() const;
        
                ::std::vector<int> constituents(int j);
        
                ::std::vector<int> clusConstituents(int j);
        
                int jetAssignment(int i);
        
                void removeJet(int i);
        
        
                // Wrappers for original constructors: 
            public:
                SlowJet(int powerIn, double Rin, double pTjetMinIn, double etaMaxIn, int selectIn, int massSetIn);
                SlowJet(int powerIn, double Rin, double pTjetMinIn, double etaMaxIn, int selectIn);
                SlowJet(int powerIn, double Rin, double pTjetMinIn, double etaMaxIn);
                SlowJet(int powerIn, double Rin, double pTjetMinIn);
                SlowJet(int powerIn, double Rin);
        
                // Special pointer-based constructor: 
                SlowJet(Abstract_SlowJet* in);
        
                // Copy constructor: 
                SlowJet(const SlowJet& in);
        
                // Assignment operator: 
                SlowJet& operator=(const SlowJet& in);
        
                // Destructor: 
                ~SlowJet();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_SlowJet* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_SlowJet_decl_Pythia_8_212_h__ */
