#ifndef __wrapper_ClassSeven__int_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassSeven__int_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassSeven.hpp"
#include "wrapper_ClassThree__int_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassSeven__int : public ClassThree__int
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassSeven<int>* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
    public:
      int pop2();
  
      void push2(int item);
  
      int size2();
  
  
      // Wrappers for original constructors: 
    public:
      ClassSeven__int();
  
      // Special pointer-based constructor: 
      ClassSeven__int(Abstract_ClassSeven<int>* in);
  
      // Copy constructor: 
      ClassSeven__int(const ClassSeven__int& in);
  
      // Assignment operator: 
      ClassSeven__int& operator=(const ClassSeven__int& in);
  
      // Destructor: 
      ~ClassSeven__int();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassSeven<int>* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassSeven__int_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
