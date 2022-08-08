#ifndef __wrapper_HL_Gaussian_decl_HepLike_1_2_h__
#define __wrapper_HL_Gaussian_decl_HepLike_1_2_h__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_Gaussian.h"
#include "wrapper_HL_Data_decl.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_Gaussian : public HL_Data
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_Gaussian* (*__factory0)();
         static Abstract_HL_Gaussian* (*__factory1)(::std::basic_string<char>);
   
         // -- Other member variables: 
   
         // Member functions: 
      public:
         void Read();
   
         double GetChi2(double theory, double theory_err);
   
         double GetChi2(double theory);
   
         double GetLikelihood(double theory, double theory_err);
   
         double GetLikelihood(double theory);
   
         double GetLogLikelihood(double theory, double theory_err);
   
         double GetLogLikelihood(double theory);
   
   
         // Wrappers for original constructors: 
      public:
         HL_Gaussian();
         HL_Gaussian(::std::basic_string<char> s);
   
         // Special pointer-based constructor: 
         HL_Gaussian(Abstract_HL_Gaussian* in);
   
         // Copy constructor: 
         HL_Gaussian(const HL_Gaussian& in);
   
         // Assignment operator: 
         HL_Gaussian& operator=(const HL_Gaussian& in);
   
         // Destructor: 
         ~HL_Gaussian();
   
         // Returns correctly casted pointer to Abstract class: 
         Abstract_HL_Gaussian* get_BEptr() const;
   
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_Gaussian_decl_HepLike_1_2_h__ */
