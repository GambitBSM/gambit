#ifndef __wrapper_HL_Limit_decl_HepLike_1_2_h__
#define __wrapper_HL_Limit_decl_HepLike_1_2_h__

#include <cstddef>
#include <string>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_Limit.h"
#include "wrapper_HL_Data_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_Limit : public HL_Data
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_Limit* (*__factory0)();
         static Abstract_HL_Limit* (*__factory1)(::std::basic_string<char>);
   
         // -- Other member variables: 
   
         // Member functions: 
      public:
         void Read();
   
         double GetChi2(double arg_1);
   
         double GetLogLikelihood(double arg_1);
   
         double GetLikelihood(double arg_1);
   
         double GetCLs(double val);
   
   
         // Wrappers for original constructors: 
      public:
         HL_Limit();
         HL_Limit(::std::basic_string<char> s);
   
         // Special pointer-based constructor: 
         HL_Limit(Abstract_HL_Limit* in);
   
         // Copy constructor: 
         HL_Limit(const HL_Limit& in);
   
         // Assignment operator: 
         HL_Limit& operator=(const HL_Limit& in);
   
         // Destructor: 
         ~HL_Limit();
   
         // Returns correctly casted pointer to Abstract class: 
         Abstract_HL_Limit* get_BEptr() const;
   
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_Limit_decl_HepLike_1_2_h__ */
