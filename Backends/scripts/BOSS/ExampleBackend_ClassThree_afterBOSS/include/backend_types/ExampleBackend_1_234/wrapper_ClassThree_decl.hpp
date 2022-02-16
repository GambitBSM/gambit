#ifndef __wrapper_ClassThree_decl_ExampleBackend_1_234_hpp__
#define __wrapper_ClassThree_decl_ExampleBackend_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassThree.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template<>
  class ClassThree<double> : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassThree<double>* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
    public:
      double pop();
  
      void push(double item);
  
      int size();
  
  
      // Wrappers for original constructors: 
    public:
      ClassThree();
  
      // Special pointer-based constructor: 
      ClassThree(Abstract_ClassThree<double>* in);
  
      // Copy constructor: 
      ClassThree(const ClassThree& in);
  
      // Assignment operator: 
      ClassThree& operator=(const ClassThree& in);
  
      // Destructor: 
      ~ClassThree();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassThree<double>* get_BEptr() const;
  
  };
  

  // 
  // Anders: Repeat everything above for any other specializations, e.g. ClassThree<int>
  // 

}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree_decl_ExampleBackend_1_234_hpp__ */
