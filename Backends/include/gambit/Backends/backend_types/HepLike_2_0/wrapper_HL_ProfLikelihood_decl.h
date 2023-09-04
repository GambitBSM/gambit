#ifndef __wrapper_HL_ProfLikelihood_decl_HepLike_2_0_h__
#define __wrapper_HL_ProfLikelihood_decl_HepLike_2_0_h__

#include <cstddef>
#include <string>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_ProfLikelihood.h"

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_ProfLikelihood : public WrapperBase
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_ProfLikelihood* (*__factory0)();
         static Abstract_HL_ProfLikelihood* (*__factory1)(std::string);
   
         // -- Other member variables: 
      public:
         int& nxbins;
         double& xmin;
         double& xmax;
         double& central_mes_val;
         std::string& ObsName;
         std::string& HL_RootFile;
         std::string& HL_PATH;
   
         // Member functions: 
      public:
         void Read();
   
         double GetChi2(double theory);
   
         double GetChi2(double theory, double theory_err);
   
         double GetLogLikelihood(double theory);
   
         double GetLogLikelihood(double theory, double theory_err);
   
         double GetLikelihood(double theory);
   
         double GetLikelihood(double theory, double theory_err);
   
   
         // Wrappers for original constructors: 
      public:
         HL_ProfLikelihood();
         HL_ProfLikelihood(std::string s);
   
         // Special pointer-based constructor: 
         HL_ProfLikelihood(Abstract_HL_ProfLikelihood* in);
   
         // Copy constructor: 
         HL_ProfLikelihood(const HL_ProfLikelihood& in);
   
         // Assignment operator: 
         HL_ProfLikelihood& operator=(const HL_ProfLikelihood& in);
   
         // Destructor: 
         ~HL_ProfLikelihood();
   
         // Returns correctly casted pointer to Abstract class: 
         Abstract_HL_ProfLikelihood* get_BEptr() const;
   
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_ProfLikelihood_decl_HepLike_2_0_h__ */
