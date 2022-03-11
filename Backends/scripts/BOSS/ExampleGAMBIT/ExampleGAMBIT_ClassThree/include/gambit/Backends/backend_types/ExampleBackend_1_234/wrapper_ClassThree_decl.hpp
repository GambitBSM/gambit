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
  
  
  template<typename T>
  class ClassThree : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassThree<T>* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
    public:
      T pop();
  
      void push(T item);
  
      int size();
  
  
      // Wrappers for original constructors: 
    public:
      ClassThree();
  
      // Special pointer-based constructor: 
      ClassThree(Abstract_ClassThree<T>* in);
  
      // Copy constructor: 
      ClassThree(const ClassThree& in);
  
      // Assignment operator: 
      ClassThree& operator=(const ClassThree& in);
  
      // Destructor: 
      ~ClassThree();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassThree<T>* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree_decl_ExampleBackend_1_234_hpp__ */
