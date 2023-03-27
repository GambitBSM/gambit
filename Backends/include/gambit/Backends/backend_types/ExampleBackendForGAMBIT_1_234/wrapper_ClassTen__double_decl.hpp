#ifndef __wrapper_ClassTen__double_decl_ExampleBackendForGAMBIT_1_234_hpp__
#define __wrapper_ClassTen__double_decl_ExampleBackendForGAMBIT_1_234_hpp__

#include <cstddef>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassTen.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  namespace ClassNamespace
  {
    
    class ClassTen__double : public WrapperBase
    {
        // Member variables: 
      public:
        // -- Static factory pointers: 
        static Abstract_ClassTen<double>* (*__factory0)();
    
        // -- Other member variables: 
      public:
        double& test;
    
        // Member functions: 
      public:
        double pop();
    
        void push(double item);
    
        int size();
    
        ClassTen__double operator+(ClassNamespace::ClassTen__double other);
    
    
        // Wrappers for original constructors: 
      public:
        ClassTen__double();
    
        // Special pointer-based constructor: 
        ClassTen__double(Abstract_ClassTen<double>* in);
    
        // Copy constructor: 
        ClassTen__double(const ClassTen__double& in);
    
        // Assignment operator: 
        ClassTen__double& operator=(const ClassTen__double& in);
    
        // Destructor: 
        ~ClassTen__double();
    
        // Returns correctly casted pointer to Abstract class: 
        Abstract_ClassTen<double>* get_BEptr() const;
    
    };
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassTen__double_decl_ExampleBackendForGAMBIT_1_234_hpp__ */
