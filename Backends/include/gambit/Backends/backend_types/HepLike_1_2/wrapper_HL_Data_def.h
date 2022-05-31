#ifndef __wrapper_HL_Data_def_HepLike_1_2_h__
#define __wrapper_HL_Data_def_HepLike_1_2_h__

#include <string>
#include "yaml-cpp/yaml.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   // Member functions: 
   inline void HL_Data::Read()
   {
      get_BEptr()->Read();
   }
   
   inline void HL_Data::set_debug_yaml(bool arg_1)
   {
      get_BEptr()->set_debug_yaml(arg_1);
   }
   
   
   // Wrappers for original constructors: 
   inline HL_Data::HL_Data() :
      WrapperBase(__factory0()),
      HFile( get_BEptr()->HFile_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   inline HL_Data::HL_Data(::std::basic_string<char> arg_1) :
      WrapperBase(__factory1(arg_1)),
      HFile( get_BEptr()->HFile_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Special pointer-based constructor: 
   inline HL_Data::HL_Data(Abstract_HL_Data* in) :
      WrapperBase(in),
      HFile( get_BEptr()->HFile_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Copy constructor: 
   inline HL_Data::HL_Data(const HL_Data& in) :
      WrapperBase(in.get_BEptr()->pointer_copy__BOSS()),
      HFile( get_BEptr()->HFile_ref__BOSS())
   {
      get_BEptr()->set_wptr(this);
      get_BEptr()->set_delete_wrapper(false);
   }
   
   // Assignment operator: 
   inline HL_Data& HL_Data::operator=(const HL_Data& in)
   {
      if (this != &in)
      {
         get_BEptr()->pointer_assign__BOSS(in.get_BEptr());
      }
      return *this;
   }
   
   
   // Destructor: 
   inline HL_Data::~HL_Data()
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
   inline Abstract_HL_Data* HL_Data::get_BEptr() const
   {
      return dynamic_cast<Abstract_HL_Data*>(BEptr);
   }
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_Data_def_HepLike_1_2_h__ */
