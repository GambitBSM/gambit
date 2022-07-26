#ifndef __wrapper_ClassThree__double_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassThree__double_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassThree.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassThree__double : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassThree<double>* (*__factory0)();
  
      // -- Other member variables: 
    public:
      double& test;
  
      // Member functions: 
    public:
      double pop();
  
      void push(double item);
  
      int size();
  
      ClassThree__double operator+(ClassThree__double& other);
  
  
      // Wrappers for original constructors: 
    public:
      ClassThree__double();
  
      // Special pointer-based constructor: 
      ClassThree__double(Abstract_ClassThree<double>* in);
  
      // Copy constructor: 
      ClassThree__double(const ClassThree__double& in);
  
      // Assignment operator: 
      ClassThree__double& operator=(const ClassThree__double& in);
  
      // Destructor: 
      ~ClassThree__double();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassThree<double>* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree__double_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
