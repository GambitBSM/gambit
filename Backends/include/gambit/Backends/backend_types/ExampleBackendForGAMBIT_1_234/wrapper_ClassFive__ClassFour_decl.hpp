#ifndef __wrapper_ClassFive__ClassFour_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassFive__ClassFour_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassFive__ClassFour.hpp"
#include "wrapper_ClassFour_decl.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassFive__ClassFour : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassFive__ClassFour* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
    public:
      ClassFour pop();
  
      void push(ClassFour item);
  
      int size();
  
  
      // Wrappers for original constructors: 
    public:
      ClassFive__ClassFour();
  
      // Special pointer-based constructor: 
      ClassFive__ClassFour(Abstract_ClassFive__ClassFour* in);
  
      // Copy constructor: 
      ClassFive__ClassFour(const ClassFive__ClassFour& in);
  
      // Assignment operator: 
      ClassFive__ClassFour& operator=(const ClassFive__ClassFour& in);
  
      // Destructor: 
      ~ClassFive__ClassFour();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassFive__ClassFour* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassFive__ClassFour_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
