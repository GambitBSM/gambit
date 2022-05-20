//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Declarations of B->Kstar mumu theory error
///  class.
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

#ifndef __Kstarmumu_theory_err_hpp__
#define __Kstarmumu_theory_err_hpp__

#include "gambit/Utils/util_types.hpp"
#include <boost/numeric/ublas/matrix.hpp>


namespace Gambit
{

  namespace FlavBit
  {

    /// Holder for theory errors for B->K* mumu observables
    class Kstarmumu_theory_err
    {

      private:

        int size_obs;
        std::vector<str> names_obs;
        std::vector< std::vector< double > >covariance;
        std::map<str,int> map_kstarmumu;

      public:

        /// Constructor
        Kstarmumu_theory_err();
        /// Return theory error covariance matrix for selected observables
        boost::numeric::ublas::matrix<double> get_th_cov(std::vector<str> observables);

    };

  }

}

#endif //#defined __Kstarmumu_theory_err_hpp__
