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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Aug
///
///  *********************************************

#ifndef __FlavBit_utils_hpp__
#define __FlavBit_utils_hpp__

#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "gambit/Backends/backend_types/SuperIso.hpp"
#include "gambit/Elements/flav_prediction.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/translator.hpp"


//#define FLAVBIT_DEBUG
//#define FLAVBIT_DEBUG_LL

namespace YAML
{
  template<>
  /// YAML conversion structure for SuperIso SM nuisance data
  struct convert<Gambit::nuiscorr>
  {
    static Node encode(const Gambit::nuiscorr& rhs)
    {
      Node node;
      node.push_back(rhs.obs1);
      node.push_back(rhs.obs2);
      node.push_back(rhs.value);
      return node;
    }
    static bool decode(const Node& node, Gambit::nuiscorr& rhs)
    {
      if(!node.IsSequence() || node.size() != 3) return false;
      std::string obs1 = node[0].as<std::string>();
      std::string obs2 = node[1].as<std::string>();
      obs1.resize(49);
      obs2.resize(49);
      strcpy(rhs.obs1, obs1.c_str());
      strcpy(rhs.obs2, obs2.c_str());
      rhs.value = node[2].as<double>();
      return true;
    }
  };
}


namespace Gambit
{

  namespace FlavBit
  {

    const bool flav_debug =
    #ifdef FLAVBIT_DEBUG
      true;
    #else
      false;
    #endif

    const bool flav_debug_LL =
    #ifdef FLAVBIT_DEBUG_LL
      true;
    #else
      false;
    #endif

    namespace ublas = boost::numeric::ublas;

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

    /// FlavBit observable name translator
    static Utils::translator translate_flav_obs(GAMBIT_DIR "/FlavBit/data/observables_key.yaml");

    /// Print function for FlavBit predictions
    void print(flav_prediction prediction , std::vector<std::string > names);

    /// Translate B->K*ll observables from theory to LHCb convention
    void Kstarll_Theory2Experiment_translation(flav_observable_map& prediction, int generation);

    /// Translate B->K*ll covariances from theory to LHCb convention
    void Kstarll_Theory2Experiment_translation(flav_covariance_map& prediction, int generation);

    /// Find the path to the latest installed version of the HepLike data
    str path_to_latest_heplike_data();

    /// Find the heplikedata file
    str heplike_data_file(str);

    /// Extract central values of the given observables from the central value map.
    std::vector<double> get_obs_theory(const flav_prediction& prediction, const std::vector<std::string>& observables);

    /// Reorder a FlavBit observables list to match ordering expected by HEPLike
    void update_obs_list(std::vector<str>& obs_list, const std::vector<str>& HL_obs_list);

    /// Extract covariance matrix of the given observables from the covariance map.
    boost::numeric::ublas::matrix<double> get_obs_covariance(const flav_prediction& prediction, const std::vector<std::string>& observables);

    /// Helper function to avoid code duplication.
    void SuperIso_prediction_helper(const std::vector<std::string>& FB_obslist, const std::vector<std::string>& SI_obslist, flav_prediction& result,
                                    const parameters& param, const nuisance& nuislist,
                                    void (*get_predictions_nuisance)(char**, int*, double**, const parameters*, const nuisance*),
                                    void (*observables)(int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*),
                                    void (*convert_correlation)(nuiscorr*, int, double**, char**, int),
                                    void (*get_th_covariance_nuisance)(double***, char**, int*, const parameters*, const nuisance*, double**),
                                    bool useSMCovariance,
                                    bool SMCovarianceCached
                                    );


    /// Scalar WCs at tree level in the THDM
    std::complex<double> THDM_DeltaCQ_NP(int, int, int, SMInputs&, Spectrum&);

    ///Function for WCs 9,10 and primes in the THDM
    std::complex<double> THDM_DeltaC_NP(int, int, int, SMInputs&, Spectrum&);

  }

}

#endif //#defined __FlavBit_utils_hpp__
