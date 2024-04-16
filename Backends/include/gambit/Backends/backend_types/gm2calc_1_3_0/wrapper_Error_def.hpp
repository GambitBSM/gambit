#ifndef __wrapper_Error_def_gm2calc_1_3_0_hpp__
#define __wrapper_Error_def_gm2calc_1_3_0_hpp__

#include <string>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   namespace gm2calc
   {
      
      // Member functions: 
      inline ::std::string Error::what() const
      {
         return get_BEptr()->what();
      }
      
      
      // Wrappers for original constructors: 
      inline Error::Error() :
         WrapperBase(__factory0())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Special pointer-based constructor: 
      inline Error::Error(Abstract_Error* in) :
         WrapperBase(in)
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Copy constructor: 
      inline Error::Error(const Error& in) :
         WrapperBase(in.get_BEptr()->pointer_copy__BOSS())
      {
         get_BEptr()->set_wptr(this);
         get_BEptr()->set_delete_wrapper(false);
      }
      
      // Assignment operator: 
      inline Error& Error::operator=(const Error& in)
      {
         if (this != &in)
         {
            get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
         }
         return *this;
      }
      
      
      // Destructor: 
      inline Error::~Error()
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
      inline Abstract_Error* gm2calc::Error::get_BEptr() const
      {
         return dynamic_cast<Abstract_Error*>(BEptr);
      }
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_Error_def_gm2calc_1_3_0_hpp__ */
