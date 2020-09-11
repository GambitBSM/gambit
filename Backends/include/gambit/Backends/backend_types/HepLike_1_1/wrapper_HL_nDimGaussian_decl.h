#ifndef __wrapper_HL_nDimGaussian_decl_HepLike_1_1_h__
#define __wrapper_HL_nDimGaussian_decl_HepLike_1_1_h__

#include <cstddef>
#include "forward_decls_wrapper_classes.h"
#include "gambit/Backends/wrapperbase.hpp"
#include "abstract_HL_nDimGaussian.h"
#include "wrapper_HL_Data_decl.h"
#include <string>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

#include "identification.hpp"

namespace CAT_3(BACKENDNAME,_,SAFE_VERSION)
{
   
   
   class HL_nDimGaussian : public HL_Data
   {
         // Member variables: 
      public:
         // -- Static factory pointers: 
         static Abstract_HL_nDimGaussian* (*__factory0)();
         static Abstract_HL_nDimGaussian* (*__factory1)(::std::basic_string<char, std::char_traits<char>, std::allocator<char> >);
   
         // -- Other member variables: 
   
         // Member functions: 
      public:
         void Read();
   
         double GetChi2(::std::vector<double, std::allocator<double> > theory);
   
         double GetLikelihood(::std::vector<double, std::allocator<double> > theory);
   
         double GetLogLikelihood(::std::vector<double, std::allocator<double> > theory);
   
         double GetChi2(::std::vector<double, std::allocator<double> > theory, ::boost::numeric::ublas::matrix<double, boost::numeric::ublas::basic_row_major<unsigned long, long>, boost::numeric::ublas::unbounded_array<double, std::allocator<double> > > theory_cov);
   
         double GetLikelihood(::std::vector<double, std::allocator<double> > theory, ::boost::numeric::ublas::matrix<double, boost::numeric::ublas::basic_row_major<unsigned long, long>, boost::numeric::ublas::unbounded_array<double, std::allocator<double> > > theory_cov);
   
         double GetLogLikelihood(::std::vector<double, std::allocator<double> > theory, ::boost::numeric::ublas::matrix<double, boost::numeric::ublas::basic_row_major<unsigned long, long>, boost::numeric::ublas::unbounded_array<double, std::allocator<double> > > theory_cov);
   
         bool Restrict(::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > arg_1);
   
         ::std::vector<std::basic_string<char>, std::allocator<std::basic_string<char> > > GetObservables();
   
   
         // Wrappers for original constructors: 
      public:
         HL_nDimGaussian();
         HL_nDimGaussian(::std::basic_string<char, std::char_traits<char>, std::allocator<char> > s);
   
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

#endif /* __wrapper_HL_nDimGaussian_decl_HepLike_1_1_h__ */
