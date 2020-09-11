#ifndef __wrapper_HL_Data_decl_HepLike_1_1_h__
#define __wrapper_HL_Data_decl_HepLike_1_1_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_Data.h"
#include <string>
#include "yaml-cpp/yaml.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_Data : public WrapperBase
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_Data* (*__factory0)();
         static Abstract_HL_Data* (*__factory1)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
   
         // -- Other member variables: 
      public:
         std::basic_string<char, std::char_traits<char>, std::allocator<char> >& HFile;
   
         // Member functions: 
      public:
         void Read();
   
         void set_debug_yaml(bool arg_1);
   
   
         // Wrappers for original constructors: 
      public:
         HL_Data();
         HL_Data(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > arg_1);
   
         // Special pointer-based constructor: 
         HL_Data(Abstract_HL_Data* in);
   
         // Copy constructor: 
         HL_Data(const HL_Data& in);
   
         // Assignment operator: 
         HL_Data& operator=(const HL_Data& in);
   
         // Destructor: 
         ~HL_Data();
   
         // Returns correctly casted pointer to Abstract class: 
         Abstract_HL_Data* get_BEptr() const;
   
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_Data_decl_HepLike_1_1_h__ */
