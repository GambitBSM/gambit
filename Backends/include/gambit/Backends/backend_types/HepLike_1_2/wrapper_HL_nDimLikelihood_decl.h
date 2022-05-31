#ifndef __wrapper_HL_nDimLikelihood_decl_HepLike_1_2_h__
#define __wrapper_HL_nDimLikelihood_decl_HepLike_1_2_h__

#include <cstddef>
#include <string>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_nDimLikelihood.h"
#include "wrapper_HL_Data_decl.h"
#include <boost/numeric/ublas/matrix.hpp>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_nDimLikelihood : public HL_Data
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_nDimLikelihood* (*__factory0)();
         static Abstract_HL_nDimLikelihood* (*__factory1)(::std::basic_string<char>);
   
         // -- Other member variables: 
      public:
         double& loglikelihood_penalty;
   
         // Member functions: 
      public:
         void Read();
   
         double GetChi2(::std::vector<double> theory);
   
         double GetChi2(::std::vector<double> theory, ::boost::numeric::ublas::matrix<double> theory_cov);
   
         double GetLikelihood(::std::vector<double> theory);
   
         double GetLikelihood(::std::vector<double> theory, ::boost::numeric::ublas::matrix<double> theory_cov);
   
         double GetLogLikelihood(::std::vector<double> theory);
   
         double GetLogLikelihood(::std::vector<double> theory, ::boost::numeric::ublas::matrix<double> theory_cov);
   
         void Profile();
   
         double GetChi2_profile(double theory, ::std::basic_string<char> arg_1);
   
         double GetLikelihood_profile(double theory, ::std::basic_string<char> axis);
   
         double GetLogLikelihood_profile(double theory, ::std::basic_string<char> X);
   
         ::std::vector<std::basic_string<char>> GetObservables();
   
   
         // Wrappers for original constructors: 
      public:
         HL_nDimLikelihood();
         HL_nDimLikelihood(::std::basic_string<char> s);
   
         // Special pointer-based constructor: 
         HL_nDimLikelihood(Abstract_HL_nDimLikelihood* in);
   
         // Copy constructor: 
         HL_nDimLikelihood(const HL_nDimLikelihood& in);
   
         // Assignment operator: 
         HL_nDimLikelihood& operator=(const HL_nDimLikelihood& in);
   
         // Destructor: 
         ~HL_nDimLikelihood();
   
         // Returns correctly casted pointer to Abstract class: 
         Abstract_HL_nDimLikelihood* get_BEptr() const;
   
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_nDimLikelihood_decl_HepLike_1_2_h__ */
