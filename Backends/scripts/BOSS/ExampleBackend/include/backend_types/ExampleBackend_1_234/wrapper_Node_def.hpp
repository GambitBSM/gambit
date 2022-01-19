#ifndef __wrapper_Node_def_ExampleBackend_1_234_hpp__
#define __wrapper_Node_def_ExampleBackend_1_234_hpp__



#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  // Member functions: 
  
  // Wrappers for original constructors: 
  inline Node::Node() :
    WrapperBase(__factory0()),
    d( get_BEptr()->d_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Special pointer-based constructor: 
  inline Node::Node(Abstract_Node* in) :
    WrapperBase(in),
    d( get_BEptr()->d_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Copy constructor: 
  inline Node::Node(const Node& in) :
    WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
    d( get_BEptr()->d_ref__BOSS())
  {
    get_BEptr()->set_wptr(this);
    get_BEptr()->set_delete_wrapper(false);
  }
  
  // Assignment operator: 
  inline Node& Node::operator=(const Node& in)
  {
    if (this != &in)
    {
      get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
    }
    return *this;
  }
  
  
  // Destructor: 
  inline Node::~Node()
  {
    if (get_BEptr() != 0)
    {
      get_BEptr()->set_delete_wrapper(false);
      if (can_delete_BEptr())
      {
        delete BEptr;
        BEptr = 0;
      }
    }
    set_delete_BEptr(false);
  }
  
  // Returns correctly casted pointer to Abstract class: 
  inline Abstract_Node* Node::get_BEptr() const
  {
    return dynamic_cast<Abstract_Node*>(BEptr);
  }
  
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Node_def_ExampleBackend_1_234_hpp__ */
