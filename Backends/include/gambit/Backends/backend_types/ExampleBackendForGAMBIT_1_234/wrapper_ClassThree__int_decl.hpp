#ifndef __wrapper_ClassThree__int_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassThree__int_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassThree.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassThree__int : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassThree<int>* (*__factory0)();
  
      // -- Other member variables: 
    public:
      int& test;
  
      // Member functions: 
    public:
      int pop();
  
      void push(int item);
  
      int size();
  
      ClassThree__int operator+(ClassThree__int& other);
  
  
      // Wrappers for original constructors: 
    public:
      ClassThree__int();
  
      // Special pointer-based constructor: 
      ClassThree__int(Abstract_ClassThree<int>* in);
  
      // Copy constructor: 
      ClassThree__int(const ClassThree__int& in);
  
      // Assignment operator: 
      ClassThree__int& operator=(const ClassThree__int& in);
  
      // Destructor: 
      ~ClassThree__int();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassThree<int>* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassThree__int_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
