//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Implementations of B->Kstar mumu theory error
///  class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Marcin Chrzaszcz
///          (mchrzasz@cern.ch)
///  \date 2015 May
///  \date 2016 July
///  \date 2016 August
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017 Mar
///
///  *********************************************

#include "gambit/FlavBit/Kstarmumu_theory_err.hpp"


namespace Gambit
{

  namespace FlavBit
  {


    /// Implementation of Kstarmumu_theory_err methods
    /// @{

    /// Constructor
    Kstarmumu_theory_err::Kstarmumu_theory_err()
    {
      size_obs=476+1;
      names_obs= std:: vector<str>(size_obs);
      #include "gambit/FlavBit/BKstarmumu_theory_error_names.hpp"
      for(int i=0;i<size_obs;++i)
      {
        map_kstarmumu[names_obs[i]]=i;
        covariance.push_back(std::vector<double>(size_obs));
      }
      #include "gambit/FlavBit/BKstarmumu_theory_error_matrix.hpp"
    }


    /// Return theory error covariance matrix for selected observables
    boost::numeric::ublas::matrix<double> Kstarmumu_theory_err::get_th_cov(std::vector<str> observables)
    {
     boost::numeric::ublas::matrix<double> cov_th(observables.size(), observables.size());
     for(unsigned i=0;i<observables.size();++i)
     {
       for(unsigned j=0;j<observables.size();++j)
       {
         cov_th(i,j)=covariance[map_kstarmumu[observables[i]]][map_kstarmumu[observables[j]]];
       }
     }
     return  cov_th;
    }
    /// @}

  }
}
