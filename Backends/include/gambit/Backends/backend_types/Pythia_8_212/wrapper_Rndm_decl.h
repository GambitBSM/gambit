#ifndef __wrapper_Rndm_decl_Pythia_8_212_h__
#define __wrapper_Rndm_decl_Pythia_8_212_h__

#include <cstddef>
#include <utility>
#include <vector>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Rndm.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Rndm : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Rndm* (*__factory0)();
                static Abstract_Rndm* (*__factory1)(int);
        
                // -- Other member variables: 
        
                // Member functions: 
            public:
                void init(int seedIn);
        
                void init();
        
                double flat();
        
                double exp();
        
                double xexp();
        
                double gauss();
        
                ::std::pair<double, double> gauss2();
        
                int pick(const ::std::vector<double>& prob);
        
                bool dumpState(::std::basic_string<char> fileName);
        
                bool readState(::std::basic_string<char> fileName);
        
        
                // Wrappers for original constructors: 
            public:
                Rndm();
                Rndm(int seedIn);
        
                // Special pointer-based constructor: 
                Rndm(Abstract_Rndm* in);
        
                // Copy constructor: 
                Rndm(const Rndm& in);
        
                // Assignment operator: 
                Rndm& operator=(const Rndm& in);
        
                // Destructor: 
                ~Rndm();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Rndm* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Rndm_decl_Pythia_8_212_h__ */
