#ifndef __wrapper_ClassSix_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassSix_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassSix.hpp"
#include "wrapper_ClassFive__ClassFour_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassSix : public ClassFive__ClassFour
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassSix* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
    public:
      int pop2();
  
      void push2(int item);
  
      int size2();
  
  
      // Wrappers for original constructors: 
    public:
      ClassSix();
  
      // Special pointer-based constructor: 
      ClassSix(Abstract_ClassSix* in);
  
      // Copy constructor: 
      ClassSix(const ClassSix& in);
  
      // Assignment operator: 
      ClassSix& operator=(const ClassSix& in);
  
      // Destructor: 
      ~ClassSix();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassSix* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassSix_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
