//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper utilities for FlavBit
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Marcin Chrzaszcz
///          (mchrzasz@cern.ch)
///  \date 2016 August
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Mar
///
///  *********************************************

#ifndef __flav_utils_hpp__
#define __flav_utils_hpp__

#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>


namespace Gambit
{

  namespace FlavBit
  {

    using namespace std;

    /// Matrix inversion routine using Boost
    template<class T>
    bool InvertMatrix (const ublas::matrix<T>& input, ublas::matrix<T>& inverse)
    {
      using namespace boost::numeric::ublas;
      typedef permutation_matrix<std::size_t> pmatrix;

      // create a working copy of the input
      matrix<T> A(input);
      // create a permutation matrix for the LU-factorization
      pmatrix pm(A.size1());

      // perform LU-factorization
      int res = lu_factorize(A,pm);
      if ( res != 0 ) return false;

      // create identity matrix of "inverse"
      inverse.assign(identity_matrix<T>(A.size1()));

      // backsubstitute to get the inverse
      lu_substitute(A, pm, inverse);

      return true;
    }

    /// Scalar WCs at tree level in the THDM
    std::complex<double> THDM_DeltaCQ_NP(int, int, int, SMInputs&, Spectrum&);

    ///Function for WCs 9,10 and primes in the THDM
    std::complex<double> THDM_DeltaC_NP(int, int, int, SMInputs&, Spectrum&);

  }

}

#endif //#defined __flav_utils_hpp__
