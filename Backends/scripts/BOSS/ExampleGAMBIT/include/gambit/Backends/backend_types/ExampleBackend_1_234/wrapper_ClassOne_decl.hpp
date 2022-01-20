#ifndef __wrapper_ClassOne_decl_ExampleBackend_1_234_hpp__
#define __wrapper_ClassOne_decl_ExampleBackend_1_234_hpp__

#include <cstddef>
#include <map>
#include <vector>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_ClassOne.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class ClassOne : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_ClassOne* (*__factory0)();
      static Abstract_ClassOne* (*__factory1)(double, int);
  
      // -- Other member variables: 
    public:
      int& i;
      int& i_2;
      double& d;
      long int& li;
      long int& li_1;
      long unsigned int& li_2;
      std::map<int, std::vector<unsigned long, std::allocator<unsigned long> >, std::less<int>, std::allocator<std::pair<const int, std::vector<unsigned long, std::allocator<unsigned long> > > > >& testing_Var;
  
      // Member functions: 
    public:
      void some_method(int arg_1);
  
      void some_other_method(int i_in);
  
      long int return_clock_t();
  
      ::std::vector<int, std::allocator<int> > return_as_vector_with_int();
  
      ::std::vector<long, std::allocator<long> > return_as_vector_with_clock();
  
  
      // Wrappers for original constructors: 
    public:
      ClassOne();
      ClassOne(double first, int second);
  
      // Special pointer-based constructor: 
      ClassOne(Abstract_ClassOne* in);
  
      // Copy constructor: 
      ClassOne(const ClassOne& in);
  
      // Destructor: 
      ~ClassOne();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_ClassOne* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_ClassOne_decl_ExampleBackend_1_234_hpp__ */
