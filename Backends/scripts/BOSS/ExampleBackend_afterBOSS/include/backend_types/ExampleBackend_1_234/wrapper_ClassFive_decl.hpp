#ifndef __wrapper_ClassFive_decl_ExampleBackend_1_234_hpp__
#define __wrapper_ClassFive_decl_ExampleBackend_1_234_hpp__

#include <cstddef>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassFive.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  template <>
  class ClassFive<ClassFour> : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassFive<ClassFour>* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
  
      // Wrappers for original constructors: 
    public:
      ClassFive();
  
      // Special pointer-based constructor: 
      ClassFive(Abstract_ClassFive<ClassFour>* in);
  
      // Copy constructor: 
      ClassFive(const ClassFive& in);
  
      // Assignment operator: 
      ClassFive& operator=(const ClassFive& in);
  
      // Destructor: 
      ~ClassFive();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassFive<ClassFour>* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassFive_decl_ExampleBackend_1_234_hpp__ */
