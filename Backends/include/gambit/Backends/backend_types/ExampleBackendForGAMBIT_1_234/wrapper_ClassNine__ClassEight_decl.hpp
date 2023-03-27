#ifndef __wrapper_ClassNine__ClassEight_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassNine__ClassEight_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassNine__ClassEight.hpp"
#include "wrapper_ClassEight_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace ClassNamespace
  {
    
    class ClassNine__ClassEight : public WrapperBase
    {
        // Member variables: 
      public:
        // -- Static factory pointers: 
        static Abstract_ClassNine__ClassEight* (*__factory0)();
    
        // -- Other member variables: 
    
        // Member functions: 
      public:
        ClassEight pop();
    
        const ClassEight& last() const;
    
        void push(ClassNamespace::ClassEight item);
    
        int size();
    
    
        // Wrappers for original constructors: 
      public:
        ClassNine__ClassEight();
    
        // Special pointer-based constructor: 
        ClassNine__ClassEight(Abstract_ClassNine__ClassEight* in);
    
        // Copy constructor: 
        ClassNine__ClassEight(const ClassNine__ClassEight& in);
    
        // Assignment operator: 
        ClassNine__ClassEight& operator=(const ClassNine__ClassEight& in);
    
        // Destructor: 
        ~ClassNine__ClassEight();
    
        // Returns correctly casted pointer to Abstract class: 
        Abstract_ClassNine__ClassEight* get_BEptr() const;
    
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassNine__ClassEight_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
