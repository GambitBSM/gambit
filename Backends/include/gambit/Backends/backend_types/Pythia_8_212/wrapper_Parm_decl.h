#ifndef __wrapper_Parm_decl_Pythia_8_212_h__
#define __wrapper_Parm_decl_Pythia_8_212_h__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Parm.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
    
    namespace Pythia8
    {
        
        class Parm : public WrapperBase
        {
                // Member variables: 
            public:
                // -- Static factory pointers: 
                static Abstract_Parm* (*__factory0)(std::string, double, bool, bool, double, double);
                static Abstract_Parm* (*__factory1)(std::string, double, bool, bool, double);
                static Abstract_Parm* (*__factory2)(std::string, double, bool, bool);
                static Abstract_Parm* (*__factory3)(std::string, double, bool);
                static Abstract_Parm* (*__factory4)(std::string, double);
                static Abstract_Parm* (*__factory5)(std::string);
                static Abstract_Parm* (*__factory6)();
        
                // -- Other member variables: 
            public:
                std::string& name;
                double& valNow;
                double& valDefault;
                bool& hasMin;
                bool& hasMax;
                double& valMin;
                double& valMax;
        
                // Member functions: 
        
                // Wrappers for original constructors: 
            public:
                Parm(std::string nameIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn, double maxIn);
                Parm(std::string nameIn, double defaultIn, bool hasMinIn, bool hasMaxIn, double minIn);
                Parm(std::string nameIn, double defaultIn, bool hasMinIn, bool hasMaxIn);
                Parm(std::string nameIn, double defaultIn, bool hasMinIn);
                Parm(std::string nameIn, double defaultIn);
                Parm(std::string nameIn);
                Parm();
        
                // Special pointer-based constructor: 
                Parm(Abstract_Parm* in);
        
                // Copy constructor: 
                Parm(const Parm& in);
        
                // Assignment operator: 
                Parm& operator=(const Parm& in);
        
                // Destructor: 
                ~Parm();
        
                // Returns correctly casted pointer to Abstract class: 
                Abstract_Parm* get_BEptr() const;
        
        };
    }
    
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Parm_decl_Pythia_8_212_h__ */
