#ifndef __abstract_Node_ExampleBackend_1_234_hpp__
#define __abstract_Node_ExampleBackend_1_234_hpp__

#include <cstddef>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.hpp"
#include "forward_decls_wrapper_classes.hpp"

#include "identification.hpp"

// Forward declaration needed by the destructor pattern.
void set_delete_BEptr(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Node*, bool);


// Forward declaration needed by the destructor pattern.
void wrapper_deleter(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Node*);


// Forward declaration for wrapper_creator.
CAT_3(BACKENDNAME,_,SAFE_VERSION)::Node* wrapper_creator(CAT_3(BACKENDNAME,_,SAFE_VERSION)::Abstract_Node*);


namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
  
  
  class Abstract_Node : public virtual AbstractBase
  {
    public:
  
      virtual int& d_ref__BOSS() =0;
  
    public:
      virtual void pointer_assign__BOSS(Abstract_Node*) =0;
      virtual Abstract_Node* pointer_copy__BOSS() =0;
  
    private:
      Node* wptr;
      bool delete_wrapper;
    public:
      Node* get_wptr() { return wptr; }
      void set_wptr(Node* wptr_in) { wptr = wptr_in; }
      bool get_delete_wrapper() { return delete_wrapper; }
      void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
  
    public:
      Abstract_Node()
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_Node(const Abstract_Node&)
      {
        wptr = 0;
        delete_wrapper = false;
      }
  
      Abstract_Node& operator=(const Abstract_Node&) { return *this; }
  
      virtual void init_wrapper()
      {
        if (wptr == 0)
        {
          wptr = wrapper_creator(this);
          delete_wrapper = true;
        }
      }
  
      Node* get_init_wptr()
      {
        init_wrapper();
        return wptr;
      }
  
      Node& get_init_wref()
      {
        init_wrapper();
        return *wptr;
      }
  
      virtual ~Abstract_Node()
      {
        if (wptr != 0)
        {
          set_delete_BEptr(wptr, false);
          if (delete_wrapper == true)
          {
            wrapper_deleter(wptr);
            wptr = 0;
            delete_wrapper = false;
          }
        }
      }
  };
  
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_Node_ExampleBackend_1_234_hpp__ */
