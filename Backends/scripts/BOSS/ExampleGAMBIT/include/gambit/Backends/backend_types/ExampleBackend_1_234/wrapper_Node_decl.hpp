#ifndef __wrapper_Node_decl_ExampleBackend_1_234_hpp__
#define __wrapper_Node_decl_ExampleBackend_1_234_hpp__

#include <cstddef>
#include "forward_decls_wrapper_classes.hpp"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_Node.hpp"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class Node : public WrapperBase
  {
      // Member variables: 
    public:
      // -- Static factory pointers: 
      static Abstract_Node* (*__factory0)();
  
      // -- Other member variables: 
    public:
      int& d;
  
      // Member functions: 
  
      // Wrappers for original constructors: 
    public:
      Node();
  
      // Special pointer-based constructor: 
      Node(Abstract_Node* in);
  
      // Copy constructor: 
      Node(const Node& in);
  
      // Assignment operator: 
      Node& operator=(const Node& in);
  
      // Destructor: 
      ~Node();
  
      // Returns correctly casted pointer to Abstract class: 
      Abstract_Node* get_BEptr() const;
  
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Node_decl_ExampleBackend_1_234_hpp__ */
