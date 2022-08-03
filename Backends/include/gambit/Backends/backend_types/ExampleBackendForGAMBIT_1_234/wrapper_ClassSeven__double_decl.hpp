#ifndef __wrapper_ClassSeven__double_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassSeven__double_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassSeven.hpp"
#include "wrapper_ClassThree__double_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassSeven__double : public ClassThree__double
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassSeven<double>* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
    public:
      double pop2();
  
      void push2(double item);
  
      int size2();
  
  
      // Wrappers for original constructors: 
    public:
      ClassSeven__double();
  
      // Special pointer-based constructor: 
      ClassSeven__double(Abstract_ClassSeven<double>* in);
  
      // Copy constructor: 
      ClassSeven__double(const ClassSeven__double& in);
  
      // Assignment operator: 
      ClassSeven__double& operator=(const ClassSeven__double& in);
  
      // Destructor: 
      ~ClassSeven__double();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassSeven<double>* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassSeven__double_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
