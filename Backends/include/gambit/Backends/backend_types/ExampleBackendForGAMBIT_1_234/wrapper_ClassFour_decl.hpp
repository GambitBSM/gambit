#ifndef __wrapper_ClassFour_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassFour_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassFour.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassFour : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassFour* (*__factory0)();
  
      // -- Other member variables: 
  
      // Member functions: 
    public:
      double pop();
  
      void push(double item);
  
      int size();
  
      ClassFour operator+(ClassFour& other);
  
  
      // Wrappers for original constructors: 
    public:
      ClassFour();
  
      // Special pointer-based constructor: 
      ClassFour(Abstract_ClassFour* in);
  
      // Copy constructor: 
      ClassFour(const ClassFour& in);
  
      // Assignment operator: 
      ClassFour& operator=(const ClassFour& in);
  
      // Destructor: 
      ~ClassFour();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassFour* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassFour_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
