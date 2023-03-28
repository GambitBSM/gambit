#ifndef __wrapper_HL_nDimLikelihood_decl_HepLike_2_0_h__
#define __wrapper_HL_nDimLikelihood_decl_HepLike_2_0_h__

#include <cstddef>
#include <string>
#include <vector>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_nDimLikelihood.h"
#include <boost/numeric/ublas/matrix.hpp>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_nDimLikelihood : public WrapperBase
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_nDimLikelihood* (*__factory0)();
         static Abstract_HL_nDimLikelihood* (*__factory1)(std::string);
   
         // -- Other member variables: 
      public:
         double& loglikelihood_penalty;
         std::string& HL_RootFile;
         std::string& HL_PATH;
         std::vector<std::string>& Observables;
         int& NoOfObservables;
         int& size_restricted;
         double& xmin;
         double& xmax;
         double& ymin;
         double& ymax;
         double& zmin;
         double& zmax;
         std::vector<double>& central_mes_val;
         int& dim;
         int& n_binsX;
         int& n_binsY;
         int& n_binsZ;
         bool& profiled;
   
         // Member functions: 
      public:
         void Read();
   
         double GetChi2(std::vector<double> theory);
   
         double GetChi2(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov);
   
         double GetLikelihood(std::vector<double> theory);
   
         double GetLikelihood(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov);
   
         double GetLogLikelihood(std::vector<double> theory);
   
         double GetLogLikelihood(std::vector<double> theory, boost::numeric::ublas::matrix<double> theory_cov);
   
         void Profile(std::string arg_1);
   
         void Profile();
   
         double GetChi2_profile(double theory, std::string arg_1);
   
         double GetLikelihood_profile(double theory, std::string axis);
   
         double GetLogLikelihood_profile(double theory, std::string X);
   
         ::std::vector<std::string> GetObservables();
   
   
         // Wrappers for original constructors: 
      public:
         HL_nDimLikelihood();
         HL_nDimLikelihood(std::string s);
   
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

#endif /* __wrapper_HL_nDimLikelihood_decl_HepLike_2_0_h__ */
