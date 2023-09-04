#ifndef __wrapper_HL_nDimGaussian_decl_HepLike_2_0_h__
#define __wrapper_HL_nDimGaussian_decl_HepLike_2_0_h__

#include <cstddef>
#include <string>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_nDimGaussian.h"
#include <boost/numeric/ublas/matrix.hpp>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_nDimGaussian : public WrapperBase
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_nDimGaussian* (*__factory0)();
         static Abstract_HL_nDimGaussian* (*__factory1)(std::string);
   
         // -- Other member variables: 
   
         // Member functions: 
      public:
         void Read();
   
         double GetChi2(std::vector<double> theory);
   
         double GetLikelihood(std::vector<double> theory);
   
         double GetLogLikelihood(std::vector<double> theory);
   
         double GetChi2(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov);
   
         double GetLikelihood(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov);
   
         double GetLogLikelihood(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov);
   
         bool Restrict(std::vector<std::string> arg_1);
   
         ::std::vector<std::string> GetObservables();
   
   
         // Wrappers for original constructors: 
      public:
         HL_nDimGaussian();
         HL_nDimGaussian(std::string s);
   
         // Special pointer-based constructor: 
         HL_nDimGaussian(Abstract_HL_nDimGaussian* in);
   
         // Copy constructor: 
         HL_nDimGaussian(const HL_nDimGaussian& in);
   
         // Assignment operator: 
         HL_nDimGaussian& operator=(const HL_nDimGaussian& in);
   
         // Destructor: 
         ~HL_nDimGaussian();
   
         // Returns correctly casted pointer to Abstract class: 
         Abstract_HL_nDimGaussian* get_BEptr() const;
   
   };
   
}


#include "gambit/Backends/backend_undefs.hpp"

#endif /* __wrapper_HL_nDimGaussian_decl_HepLike_2_0_h__ */
