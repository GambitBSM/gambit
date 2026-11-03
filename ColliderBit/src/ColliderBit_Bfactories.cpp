//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of ColliderBit B factories likelihoods.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Felix Kahlhoefer
///          (kahlhoefer@kit.edu)
///  \date   2023 July
///
///  *********************************************

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <numeric>
#include <sstream>
#include <vector>

#include <gsl/gsl_math.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_sf_gamma.h>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Utils/interp_collection.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/ColliderBit/Utils.hpp"


//#define COLLIDERBIT_DEBUG

namespace Gambit
{

  namespace ColliderBit
  {

    /// A class to hold analysis information for the BaBar single photon search (specific to dark photon models)
    class BaBar_single_photon_analysis_info
    {
      public:

        str name;

        // Maps containing 1D and 2D interpolators
        std::map<str,std::unique_ptr<Utils::interp1d_gsl_collection>> interp1d;

        void add_interp1d(str name, str filename, std::vector<str> colnames)
        {
          assert (interp1d.count(name) == 0); // Make sure we're not overwriting an existing entry
          interp1d[name] = std::unique_ptr<Utils::interp1d_gsl_collection>(new Utils::interp1d_gsl_collection(name, filename, colnames));
        }

        const Utils::interp1d_gsl_collection& get_interp1d(str name) const
        {
          return *interp1d.at(name);
        }

    };

    /// A Map between search name and the analysis info needed
    std::map<str,BaBar_single_photon_analysis_info> SubGeVDM_BaBar_single_photon_analysis_info;

    void fill_BaBar_single_photon()
    {

      str analysis_name = "BaBar_single_photon";
      SubGeVDM_BaBar_single_photon_analysis_info[analysis_name] = BaBar_single_photon_analysis_info();

      BaBar_single_photon_analysis_info* current_ainfo;

      current_ainfo = &(SubGeVDM_BaBar_single_photon_analysis_info[analysis_name]);

      // Set the analysis info:

      if (not(Utils::file_exists(GAMBIT_DIR "/ColliderBit/data/SubGeVDM/BaBar/single_photon.txt")))
      {
        ColliderBit_error().raise(LOCAL_INFO, "ERROR! BaBar single photon data file missing: /ColliderBit/data/SubGeVDM/BaBar/single_photon.txt.");
      }

      std::vector<str> colnames;
      colnames = {"mass", "central", "error"};
      current_ainfo->add_interp1d("BaBar_single_photon", GAMBIT_DIR "/ColliderBit/data/SubGeVDM/BaBar/single_photon.txt", colnames);

      // Clear the pointer
      BaBar_single_photon_analysis_info empty_analysis_info;
      current_ainfo = &empty_analysis_info;

    }

    /// Perform the actual likelihood evaluation
    double BaBar_single_photon_LogLike(double kappa, double mAp, double BRinv)
    {
      const Utils::interp1d_gsl_collection& BaBar_interp = SubGeVDM_BaBar_single_photon_analysis_info["BaBar_single_photon"].get_interp1d("BaBar_single_photon");

      if (!BaBar_interp.is_inside_range(mAp))
      {
        return 0.0;
      }

      // Calculate the interpolated coupling
      double central = BaBar_interp.eval(mAp,0) * 1e-6;
      double error = BaBar_interp.eval(mAp,1) * 1e-6;

      if(pow(kappa,2) * BRinv < central)
      {
        return 0.0;
      }
      else
      {
        return - pow(pow(kappa,2) * BRinv - central,2)/(2 * pow(error,2));
      }

    }

    void BaBar_single_photon_LogLike_SubGeVDM(double& result)
    {

      using namespace Pipes::BaBar_single_photon_LogLike_SubGeVDM;

      static bool first = true;
      if (first)
      {
        fill_BaBar_single_photon();
        first = false;
      }

      double mAp;
      double kappa;

      DecayTable::Entry decays;

      // Get the theory spectrum to pass on masses and parameters
      mAp = *Param["mAp"];
      kappa = *Param["kappa"];
      decays = *Dep::dark_photon_decay_rates;

      double BRinv = decays.BF("DM", "DM~");

      result = BaBar_single_photon_LogLike(kappa, mAp, BRinv);

    }
  }
}
