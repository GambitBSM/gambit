#ifndef __wrapper_ClassTwo_decl_ExampleBackend_1_234_hpp__
#define __wrapper_ClassTwo_decl_ExampleBackend_1_234_hpp__

#include <cstddef>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassTwo.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace SomeNamespace
  {
    
    class ClassTwo : public WrapperBase
    {
        // Member variables: 
      public:
        // -- Static factory pointers: 
        static Abstract_ClassTwo* (*__factory0)();
    
        // -- Other member variables: 
      public:
        int& j;
    
        // Member functions: 
    
        // Wrappers for original constructors: 
      public:
        ClassTwo();
    
        // Special pointer-based constructor: 
        ClassTwo(Abstract_ClassTwo* in);
    
        // Copy constructor: 
        ClassTwo(const ClassTwo& in);
    
        // Assignment operator: 
        ClassTwo& operator=(const ClassTwo& in);
    
        // Destructor: 
        ~ClassTwo();
    
        // Returns correctly casted pointer to Abstract class: 
        Abstract_ClassTwo* get_BEptr() const;
    
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassTwo_decl_ExampleBackend_1_234_hpp__ */
