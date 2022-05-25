#ifndef __abstract_HL_Data_HepLike_1_2_h__
#define __abstract_HL_Data_HepLike_1_2_h__

#include <cstddef>
#include <iostream>
#include <string>
#include "gambit/Backends/abstractbase.hpp"
#include "forward_decls_abstract_classes.h"
#include "forward_decls_wrapper_classes.h"
#include "yaml-cpp/yaml.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class Abstract_HL_Data : public virtual AbstractBase
   {
      public:
   
         virtual std::basic_string<char>& HFile_ref__BOSS() =0;
   
         virtual void Read() =0;
   
         virtual void set_debug_yaml(bool) =0;
   
      public:
         virtual void pointer_assign__BOSS(Abstract_HL_Data*) =0;
         virtual Abstract_HL_Data* pointer_copy__BOSS() =0;
   
      private:
         HL_Data* wptr;
         bool delete_wrapper;
      public:
         HL_Data* get_wptr() { return wptr; }
         void set_wptr(HL_Data* wptr_in) { wptr = wptr_in; }
         bool get_delete_wrapper() { return delete_wrapper; }
         void set_delete_wrapper(bool del_wrp_in) { delete_wrapper = del_wrp_in; }
   
      public:
         Abstract_HL_Data()
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_Data(const Abstract_HL_Data&)
         {
            wptr = 0;
            delete_wrapper = false;
         }
   
         Abstract_HL_Data& operator=(const Abstract_HL_Data&) { return *this; }
   
         virtual void init_wrapper() =0;
   
         HL_Data* get_init_wptr()
         {
            init_wrapper();
            return wptr;
         }
   
         HL_Data& get_init_wref()
         {
            init_wrapper();
            return *wptr;
         }
   
         virtual ~Abstract_HL_Data() =0;
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"


#endif /* __abstract_HL_Data_HepLike_1_2_h__ */
