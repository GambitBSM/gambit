#ifndef __wrapper_ClassEight_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassEight_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassEight.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace ClassNamespace
  {
    
    class ClassEight : public WrapperBase
    {
        // Member variables: 
      public:
        // -- Static factory pointers: 
        static Abstract_ClassEight* (*__factory0)();
    
        // -- Other member variables: 
    
        // Member functions: 
      public:
        double pop();
    
        void push(double item);
    
        int size();
    
        ClassEight operator+(ClassNamespace::ClassEight other);
    
    
        // Wrappers for original constructors: 
      public:
        ClassEight();
    
        // Special pointer-based constructor: 
        ClassEight(Abstract_ClassEight* in);
    
        // Copy constructor: 
        ClassEight(const ClassEight& in);
    
        // Assignment operator: 
        ClassEight& operator=(const ClassEight& in);
    
        // Destructor: 
        ~ClassEight();
    
        // Returns correctly casted pointer to Abstract class: 
        Abstract_ClassEight* get_BEptr() const;
    
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassEight_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
