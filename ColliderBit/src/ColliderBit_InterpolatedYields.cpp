//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions for LHC analyses that use tabulated interpolations
///  rather than direct MC simulation. For now this functionality
///  is specific to the DMEFT model, but it will be turned into
///  a general feature in ColliderBit.
///  
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Martin White
///          (martin.white@adelaide.edu.au)
///
///  \author Andre Scaffidi
///          (andre.scaffidi@adelaide.edu.au)
///  \date 2019 Aug
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2021 Apr
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2021 May
///
///  Analyses based on: arxiv:1711.03301 and https://journals.aps.org/prd/abstract/10.1103/PhysRevD.97.092005
///  139invfb analysis based on arXiv:2102.10874 
///
///  *********************************************

// Needs GSL 2 
#include <gsl/gsl_math.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_sf_gamma.h>

#include "Eigen/Eigenvalues"
#include "Eigen/Eigen"

#include "multimin/multimin.hpp"

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/Utils/interp_collection.hpp"
#include "gambit/Utils/file_lock.hpp"
#include "gambit/Utils/util_macros.hpp"
#include "gambit/ColliderBit/Utils.hpp"


// #define COLLIDERBIT_DEBUG_PROFILING
// #define COLLIDERBIT_DEBUG
// #define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {  

    // =========== Useful stuff ===========

    /// A minimal class with analysis info, maps for containing collections of 1D/2D interpolators
    /// and some helper functions for adding and accessing the interpolators, and for 
    /// adding a background covariance matrix. Currently this class is tailored specifically 
    /// for the DMEFT model -- it will be generalized in the future.
    class DMEFT_analysis_info
    {
      public:

        // Standard analysis info:

        str name;
        double lumi_invfb;
        size_t n_signal_regions;
        std::vector<int> obsnum;
        std::vector<double> bkgnum;
        std::vector<double> bkgerr;
        Eigen::MatrixXd bkgcov;

        // A map to hold any extra non-standard numbers we might need for a given analysis.
        // For the DMEFT-specific case we'll use this to store the MET spectrum bin limits
        std::map<str, std::vector<double>> extra_info; // Any additional analysis-specific numbers

        // Maps containing 1D and 2D interpolators
        std::map<str,std::unique_ptr<Utils::interp1d_collection>> interp1d;
        std::map<str,std::unique_ptr<Utils::interp2d_collection>> interp2d;

        // Helper functions

        void add_bkgcov(const std::vector< std::vector<double>>& bkgcov_in)
        {
          assert( bkgcov_in.size() > 0 && bkgcov_in.size() == n_signal_regions );
          assert( bkgcov_in[0].size() > 0 && bkgcov_in[0].size() == n_signal_regions );

          // Fill our Eigen matrix
          bkgcov = Eigen::MatrixXd(n_signal_regions, n_signal_regions);
          for (size_t i = 0; i < n_signal_regions; i++)
          {
            bkgcov.row(i) = Eigen::VectorXd::Map(&bkgcov_in[i][0], bkgcov_in[i].size()); 
          }
        }

        void add_interp1d(str name, str filename, std::vector<str> colnames)
        {
          assert (interp1d.count(name) == 0); // Make sure we're not overwriting an existing entry
          interp1d[name] = std::unique_ptr<Utils::interp1d_collection>(new Utils::interp1d_collection(name, filename, colnames));
        }

        void add_interp2d(str name, str filename, std::vector<str> colnames)
        {
          assert (interp2d.count(name) == 0); // Make sure we're not overwriting an existing entry
          interp2d[name] = std::unique_ptr<Utils::interp2d_collection>(new Utils::interp2d_collection(name, filename, colnames));
        }

        const Utils::interp1d_collection& get_interp1d(str name) const
        {
          return *interp1d.at(name);
        }

        const Utils::interp2d_collection& get_interp2d(str name) const
        {
          return *interp2d.at(name);
        }
    };
  

    /// A struct to contain parameters for the GSL optimiser target function
    struct _gsl_target_func_params
    {
      double lambda;
      AnalysisDataPointers adata_ptrs_original;
      std::vector<str> skip_analyses;
      bool use_covar;
      bool use_marg;
      bool combine_nocovar_SRs;
    };


    /// A global map from analysis name to DMEFT_analysis_info instance.
    /// This map is initialized by the function fill_analysis_info_map,
    /// which is called the first time DMEFT_results run.
    std::map<str,DMEFT_analysis_info> analysis_info_map;


    // =========== Forward declarations ===========

    /// Forward declaration of funtion in LHC_likelihoods
    AnalysisLogLikes calc_loglikes_for_analysis(const AnalysisData&, bool, bool, bool, bool);

    /// Forward declarations of functions in this file
    void fill_analysis_info_map();

    void DMEFT_results(AnalysisDataPointers&);

    void get_all_DMEFT_signal_yields(std::vector<double>&, const DMEFT_analysis_info&, const Spectrum&);

    void get_DMEFT_signal_yields_dim6_operator(std::vector<double>&, const str, const DMEFT_analysis_info&, double, double, double, double);

    void get_DMEFT_signal_yields_dim7_operator(std::vector<double>&, const str, const DMEFT_analysis_info&, double, double, double);

    void DMEFT_results_profiled(AnalysisDataPointers&);

    void DMEFT_results_cutoff(AnalysisDataPointers&);

    void signal_modifier_function(AnalysisData&, double, double);

    void signal_cutoff_function(AnalysisData&, double);

    void _gsl_target_func(const size_t, const double*, void*, double*);

    void calc_DMEFT_profiled_LHC_nuisance_params(map_str_dbl&);

    void InterpolatedMCInfo(MCLoopInfo&);


    // =========== Functions ===========

    /// A function for filling the analysis_info_map.
    /// This is where all the analysis-specific numbers and file names go.
    void fill_analysis_info_map()
    {

      // Helper variables
      str current_analysis_name;
      std::vector<str> colnames;
      DMEFT_analysis_info empty_analysis_info;
      DMEFT_analysis_info* current_ainfo;

      // 
      // New analysis: CMS_13TeV_MONOJET_36invfb_interpolated
      // 

      // Analysis name
      current_analysis_name = "CMS_13TeV_MONOJET_36invfb_interpolated";

      // Create an entry in the global analysis_info_map and point the pointer current_ainfo to it
      analysis_info_map[current_analysis_name] = DMEFT_analysis_info();
      current_ainfo = &(analysis_info_map[current_analysis_name]);

      current_ainfo->name = current_analysis_name;
      current_ainfo->lumi_invfb = 36.1;

      current_ainfo->obsnum = {136865, 74340, 42540, 25316, 15653, 10092, 8298, 4906, 2987, 2032, 1514,
                               926, 557, 316, 233, 172, 101, 65, 46, 26, 31, 29};
      current_ainfo->bkgnum = {134500., 73400., 42320., 25490., 15430., 10160., 8480., 4865., 2970., 1915., 1506.,
                               844., 526., 325., 223., 169., 107., 88.1, 52.8, 25.0, 25.5, 26.9};
      current_ainfo->bkgerr = {3700., 2000., 810., 490., 310., 170., 140., 95., 49., 33., 32.,
                               18., 14., 12., 9., 8., 6., 5.3, 3.9, 2.5, 2.6, 2.8};
      assert(current_ainfo->obsnum.size() == current_ainfo->bkgerr.size());
      assert(current_ainfo->obsnum.size() == current_ainfo->bkgerr.size());
      current_ainfo->n_signal_regions = current_ainfo->obsnum.size(); // = 22

      current_ainfo->extra_info["metmins"] = {250., 280., 310., 340., 370., 400., 430., 470., 510., 550., 590.,
                                              640., 690., 740., 790., 840., 900., 960., 1020., 1090., 1160., 1250.};
      assert(current_ainfo->obsnum.size() == current_ainfo->extra_info["metmins"].size());

      // Construct the background covariance matrix
      std::vector< std::vector<double>> bkgcov = {
        {  1.37e+07,  7.18e+06,  2.58e+06,  1.54e+06,  9.29e+05,  4.28e+05,  3.26e+05,  2.04e+05,  8.34e+04,  5.37e+04,  4.62e+04,  2.33e+04,  1.45e+04,  1.20e+04,  6.66e+03,  7.99e+03,  4.00e+03,  1.57e+03,  0.00e+00,  1.30e+03,  3.85e+02, -4.14e+02 },
        {  7.18e+06,  4.00e+06,  1.38e+06,  8.43e+05,  5.02e+05,  2.28e+05,  1.74e+05,  1.05e+05,  4.51e+04,  2.84e+04,  2.30e+04,  1.22e+04,  7.56e+03,  6.48e+03,  3.24e+03,  4.00e+03,  2.28e+03,  1.06e+03,  1.56e+02,  8.00e+02,  3.64e+02, -1.68e+02 },
        {  2.58e+06,  1.38e+06,  6.56e+05,  3.57e+05,  2.18e+05,  1.07e+05,  8.73e+04,  5.31e+04,  2.34e+04,  1.50e+04,  1.35e+04,  7.00e+03,  4.20e+03,  3.30e+03,  2.26e+03,  1.81e+03,  1.12e+03,  6.44e+02,  2.21e+02,  3.04e+02,  1.47e+02,  2.27e+01 },
        {  1.54e+06,  8.43e+05,  3.57e+05,  2.40e+05,  1.32e+05,  6.58e+04,  5.14e+04,  3.17e+04,  1.44e+04,  9.22e+03,  8.15e+03,  4.06e+03,  2.88e+03,  2.00e+03,  1.32e+03,  1.25e+03,  7.06e+02,  3.64e+02,  5.73e+01,  1.59e+02,  7.64e+01, -2.74e+01 },
        {  9.29e+05,  5.02e+05,  2.18e+05,  1.32e+05,  9.61e+04,  4.11e+04,  3.21e+04,  1.88e+04,  8.81e+03,  5.73e+03,  5.46e+03,  2.57e+03,  1.78e+03,  1.34e+03,  6.98e+02,  9.18e+02,  4.28e+02,  1.64e+02,  3.63e+01,  1.32e+02,  1.05e+02, -8.68e+00 },
        {  4.28e+05,  2.28e+05,  1.07e+05,  6.58e+04,  4.11e+04,  2.89e+04,  1.76e+04,  1.07e+04,  5.16e+03,  2.92e+03,  2.83e+03,  1.62e+03,  9.76e+02,  8.77e+02,  3.82e+02,  4.49e+02,  2.04e+02,  1.08e+02,  9.94e+01,  1.02e+02,  3.98e+01,  4.76e+00 },
        {  3.26e+05,  1.74e+05,  8.73e+04,  5.14e+04,  3.21e+04,  1.76e+04,  1.96e+04,  9.18e+03,  4.39e+03,  2.82e+03,  2.46e+03,  1.39e+03,  9.21e+02,  7.39e+02,  5.17e+02,  3.70e+02,  2.35e+02,  9.65e+01,  8.19e+01,  4.20e+01,  1.82e+01,  3.14e+01 },
        {  2.04e+05,  1.04e+05,  5.31e+04,  3.17e+04,  1.88e+04,  1.07e+04,  9.18e+03,  9.02e+03,  2.61e+03,  1.72e+03,  1.70e+03,  8.55e+02,  4.52e+02,  4.67e+02,  2.48e+02,  2.66e+02,  1.54e+02,  5.04e+01,  3.33e+01,  1.19e+01,  3.21e+01,  7.98e+00 },
        {  8.34e+04,  4.51e+04,  2.34e+04,  1.44e+04,  8.81e+03,  5.16e+03,  4.39e+03,  2.61e+03,  2.40e+03,  9.22e+02,  8.94e+02,  4.67e+02,  2.13e+02,  2.41e+02,  1.41e+02,  1.29e+02,  4.70e+01,  4.41e+01,  7.64e+00,  2.08e+01,  2.55e+01,  5.49e+00 },
        {  5.37e+04,  2.84e+04,  1.50e+04,  9.22e+03,  5.73e+03,  2.92e+03,  2.82e+03,  1.72e+03,  9.22e+02,  1.09e+03,  5.17e+02,  3.03e+02,  1.62e+02,  1.47e+02,  8.91e+01,  8.18e+01,  3.17e+01,  2.10e+01,  1.29e+00,  7.42e+00,  7.72e+00,  4.62e+00 },
        {  4.62e+04,  2.30e+04,  1.35e+04,  8.15e+03,  5.46e+03,  2.83e+03,  2.46e+03,  1.70e+03,  8.94e+02,  5.17e+02,  1.02e+03,  2.65e+02,  1.57e+02,  1.61e+02,  9.22e+01,  7.94e+01,  3.84e+01,  3.39e+00, -1.25e+00,  1.44e+01,  3.33e+00, -8.96e-01 },
        {  2.33e+04,  1.22e+04,  7.00e+03,  4.06e+03,  2.57e+03,  1.62e+03,  1.39e+03,  8.55e+02,  4.67e+02,  3.03e+02,  2.65e+02,  3.24e+02,  8.57e+01,  9.07e+01,  5.83e+01,  3.02e+01,  2.70e+01,  2.00e+01,  7.02e+00,  2.25e+00,  5.15e+00,  7.06e+00 },
        {  1.45e+04,  7.56e+03,  4.20e+03,  2.88e+03,  1.78e+03,  9.76e+02,  9.21e+02,  4.52e+02,  2.13e+02,  1.62e+02,  1.57e+02,  8.57e+01,  1.96e+02,  5.21e+01,  3.91e+01,  3.92e+01,  2.69e+01,  8.90e+00,  6.55e+00,  0.00e+00,  1.46e+00,  1.57e+00 },
        {  1.20e+04,  6.48e+03,  3.30e+03,  2.00e+03,  1.34e+03,  8.77e+02,  7.39e+02,  4.67e+02,  2.41e+02,  1.47e+02,  1.61e+02,  9.07e+01,  5.21e+01,  1.44e+02,  3.02e+01,  2.02e+01,  1.44e+01,  3.18e+00,  4.68e-01,  4.50e+00,  2.18e+00,  3.02e+00 },
        {  6.66e+03,  3.24e+03,  2.26e+03,  1.32e+03,  6.98e+02,  3.82e+02,  5.17e+02,  2.48e+02,  1.41e+02,  8.91e+01,  9.22e+01,  5.83e+01,  3.91e+01,  3.02e+01,  8.10e+01,  1.15e+01,  1.19e+01,  7.63e+00,  3.16e+00, -2.25e-01,  1.40e+00,  2.52e+00 },
        {  7.99e+03,  4.00e+03,  1.81e+03,  1.25e+03,  9.18e+02,  4.49e+02,  3.70e+02,  2.66e+02,  1.29e+02,  8.18e+01,  7.94e+01,  3.02e+01,  3.92e+01,  2.02e+01,  1.15e+01,  6.40e+01,  1.92e+00, -1.27e+00, -3.12e-01,  1.40e+00,  2.70e+00, -6.72e-01 },
        {  4.00e+03,  2.28e+03,  1.12e+03,  7.06e+02,  4.28e+02,  2.04e+02,  2.35e+02,  1.54e+02,  4.70e+01,  3.17e+01,  3.84e+01,  2.70e+01,  2.69e+01,  1.44e+01,  1.19e+01,  1.92e+00,  3.60e+01,  5.09e+00,  3.74e+00, -1.65e+00,  1.40e+00,  1.51e+00 },
        {  1.57e+03,  1.06e+03,  6.44e+02,  3.64e+02,  1.64e+02,  1.08e+02,  9.65e+01,  5.04e+01,  4.41e+01,  2.10e+01,  3.39e+00,  2.00e+01,  8.90e+00,  3.18e+00,  7.63e+00, -1.27e+00,  5.09e+00,  2.81e+01,  6.20e-01, -1.19e+00,  5.51e-01, -4.45e-01 },
        {  0.00e+00,  1.56e+02,  2.21e+02,  5.73e+01,  3.63e+01,  9.95e+01,  8.19e+01,  3.33e+01,  7.64e+00,  1.29e+00, -1.25e+00,  7.02e+00,  6.55e+00,  4.68e-01,  3.16e+00, -3.12e-01,  3.74e+00,  6.20e-01,  1.52e+01,  7.80e-01,  3.04e-01,  1.64e+00 },
        {  1.30e+03,  8.00e+02,  3.04e+02,  1.59e+02,  1.32e+02,  1.02e+02,  4.20e+01,  1.19e+01,  2.08e+01,  7.42e+00,  1.44e+01,  2.25e+00,  0.00e+00,  4.50e+00, -2.25e-01,  1.40e+00, -1.65e+00, -1.19e+00,  7.80e-01,  6.25e+00,  1.30e-01,  6.30e-01 },
        {  3.85e+02,  3.64e+02,  1.47e+02,  7.64e+01,  1.05e+02,  3.98e+01,  1.82e+01,  3.21e+01,  2.55e+01,  7.72e+00,  3.33e+00,  5.15e+00,  1.46e+00,  2.18e+00,  1.40e+00,  2.70e+00,  1.40e+00,  5.51e-01,  3.04e-01,  1.30e-01,  6.76e+00,  5.82e-01 },
        { -4.14e+02, -1.68e+02,  2.27e+01, -2.74e+01, -8.68e+00,  4.76e+00,  3.14e+01,  7.98e+00,  5.49e+00,  4.62e+00, -8.96e-01,  7.06e+00,  1.57e+00,  3.02e+00,  2.52e+00, -6.72e-01,  1.51e+00, -4.45e-01,  1.64e+00,  6.30e-01,  5.82e-01,  7.84e+00 }
      };
      // Save it
      current_ainfo->add_bkgcov(bkgcov);

      // Create interpolated functions for the CMS analysis:

      // - 2d cross-sections
      colnames = {"mass", "theta", "xsec"};
      current_ainfo->add_interp2d("mass_theta_xsecpb_C61_C64", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_xsecpb_CMS_C61_C64.txt", colnames);
      current_ainfo->add_interp2d("mass_theta_xsecpb_C62_C63", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_xsecpb_CMS_C62_C63.txt", colnames);

      // - 1d cross-sections
      colnames = {"mass", "xsec"};
      current_ainfo->add_interp1d("mass_xsecpb_C71", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_CMS_C71.txt", colnames);
      current_ainfo->add_interp1d("mass_xsecpb_C72", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_CMS_C72.txt", colnames);
      current_ainfo->add_interp1d("mass_xsecpb_C73", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_CMS_C73.txt", colnames);
      current_ainfo->add_interp1d("mass_xsecpb_C74", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_CMS_C74.txt", colnames);

      // - 2d signal efficiencies
      colnames = {"mass", "theta", "SR1", "SR2", "SR3", "SR4", "SR5", "SR6", "SR7", "SR8", "SR9", "SR10",
                  "SR11", "SR12", "SR13", "SR14", "SR15", "SR16", "SR17", "SR18", "SR19", "SR20", "SR21", "SR22"};
      current_ainfo->add_interp2d("mass_theta_eff_C61_C64", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_eff_CMS_C61_C64.txt", colnames);
      current_ainfo->add_interp2d("mass_theta_eff_C62_C63", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_eff_CMS_C62_C63.txt", colnames);

      // - 1d signal efficiencies
      colnames = {"mass", "SR1", "SR2", "SR3", "SR4", "SR5", "SR6", "SR7", "SR8", "SR9", "SR10",
                  "SR11", "SR12", "SR13", "SR14", "SR15", "SR16", "SR17", "SR18", "SR19", "SR20", "SR21", "SR22"};
      current_ainfo->add_interp1d("mass_eff_C71", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_CMS_C71.txt", colnames);
      current_ainfo->add_interp1d("mass_eff_C72", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_CMS_C72.txt", colnames);
      current_ainfo->add_interp1d("mass_eff_C73", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_CMS_C73.txt", colnames);
      current_ainfo->add_interp1d("mass_eff_C74", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_CMS_C74.txt", colnames);

      // 'Clear' the pointer current_ainfo before moving on to the next analysis by pointing it to empty_analysis_info
      current_ainfo = &empty_analysis_info;


      // 
      // New analysis: ATLAS_13TeV_MONOJET_139invfb_interpolated
      // 

      // Analysis name
      current_analysis_name = "ATLAS_13TeV_MONOJET_139invfb_interpolated";

      // Create an entry in the global analysis_info_map and point the reference current_ainfo to it
      analysis_info_map[current_analysis_name] = DMEFT_analysis_info();
      current_ainfo = &(analysis_info_map[current_analysis_name]);

      current_ainfo->name = current_analysis_name;
      current_ainfo->lumi_invfb = 139.0;

      current_ainfo->obsnum = {1791624, 752328, 313912, 141036, 102888, 29458, 10203, 3986, 1663, 738, 413+187+207};
      current_ainfo->bkgnum = {1783000., 753000., 314000., 140100., 101600., 29200., 10000., 3870., 1640., 754., 359.+182.+218.};
      current_ainfo->bkgerr = {26000., 9000., 3500., 1600., 1200., 400., 180., 80., 40., 20., sqrt(10*10+6*6+9*9)};
      assert(current_ainfo->obsnum.size() == current_ainfo->bkgnum.size());
      assert(current_ainfo->obsnum.size() == current_ainfo->bkgerr.size());
      current_ainfo->n_signal_regions = current_ainfo->obsnum.size();

      current_ainfo->extra_info["metmins"] = {200., 250., 300., 350., 400., 500., 600., 700., 800., 900., 1000.};
      assert(current_ainfo->obsnum.size() == current_ainfo->extra_info["metmins"].size());


      // Create interpolated functions for the ATLAS analysis:

      // - 2d cross-sections
      colnames = {"mass", "theta", "xsec"};
      current_ainfo->add_interp2d("mass_theta_xsecpb_C61_C64", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_xsecpb_ATLAS_C61_C64.txt", colnames);
      current_ainfo->add_interp2d("mass_theta_xsecpb_C62_C63", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_xsecpb_ATLAS_C62_C63.txt", colnames);

      // - 1d cross-sections
      colnames = {"mass", "xsec"};
      current_ainfo->add_interp1d("mass_xsecpb_C71", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_ATLAS_C71.txt", colnames);
      current_ainfo->add_interp1d("mass_xsecpb_C72", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_ATLAS_C72.txt", colnames);
      current_ainfo->add_interp1d("mass_xsecpb_C73", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_ATLAS_C73.txt", colnames);
      current_ainfo->add_interp1d("mass_xsecpb_C74", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_xsecpb_ATLAS_C74.txt", colnames);

      // - 2d signal efficiencies
      colnames = {"mass", "theta", "SR1", "SR2", "SR3", "SR4", "SR5", "SR6", "SR7", "SR8", "SR9", "SR10", "SR11"};
      current_ainfo->add_interp2d("mass_theta_eff_C61_C64", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_eff_ATLAS_C61_C64.txt", colnames);
      current_ainfo->add_interp2d("mass_theta_eff_C62_C63", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_theta_eff_ATLAS_C62_C63.txt", colnames);

      // - 1d signal efficiencies
      colnames = {"mass", "SR1", "SR2", "SR3", "SR4", "SR5", "SR6", "SR7", "SR8", "SR9", "SR10", "SR11"};
      current_ainfo->add_interp1d("mass_eff_C71", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_ATLAS_C71.txt", colnames);
      current_ainfo->add_interp1d("mass_eff_C72", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_ATLAS_C72.txt", colnames);
      current_ainfo->add_interp1d("mass_eff_C73", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_ATLAS_C73.txt", colnames);
      current_ainfo->add_interp1d("mass_eff_C74", GAMBIT_DIR "/ColliderBit/data/DMEFT/mass_eff_ATLAS_C74.txt", colnames);

      // 'Clear' the pointer current_ainfo before moving on to the next analysis by pointing it to empty_analysis_info
      current_ainfo = &empty_analysis_info;

    }


    /// Results from DMEFT analyses before any modification of the MET spectrum
    void DMEFT_results(AnalysisDataPointers& result)
    { 
      using namespace Pipes::DMEFT_results;

      static bool first = true;

      // In this function we need to transfer info from the DMEFT-specific DMEFT_analysis_info objects
      // to a set of ColliderBit-native AnalysisData objects, and also fill these with the DMEFT signal prediction.

      // We need thread_local AnalysisData instances. Let's collect them in a map.
      thread_local std::map<str,AnalysisData> analysis_data_map;

      // The first time this function is run we must initialize the global analysis_info_map
      // and the thread_local analysis_data_map
      if (first)
      {
        fill_analysis_info_map();

        for (const std::pair<str,const DMEFT_analysis_info&> aname_ainfo_pair : analysis_info_map)
        {
          // Extract analysis name and use it to create an AnalysisData element in the analysis_data_map
          str aname = aname_ainfo_pair.first;
          analysis_data_map[aname] = AnalysisData(aname);
        }

        first = false;
      }

      // Clear previous vectors, etc.
      result.clear();

      // Get the theory spectrum to pass on masses and parameters
      const Spectrum& spec = *Dep::DMEFT_spectrum;

      // 
      // Loop over the analyses registered in the analysis_info_map
      // 

      for (const std::pair<str,const DMEFT_analysis_info&> aname_ainfo_pair : analysis_info_map)
      {
        // Extract analysis name and reference to the analysis_info instance
        str aname = aname_ainfo_pair.first;
        const DMEFT_analysis_info& ainfo = aname_ainfo_pair.second;

        // Grab a reference to corresponding AnalysisData instance 
        // and clear it before we start filling it for the current parameter point
        AnalysisData& adata = analysis_data_map.at(aname);
        adata.clear();
        
        // Vector to contain signal yield predictions
        std::vector<double> sr_nums(ainfo.n_signal_regions, 0.);

        // Fill the signal yield vector with DMEFT signal predictions
        get_all_DMEFT_signal_yields(sr_nums, ainfo, spec);

        // Create vector of SignalRegionData instances
        std::vector<SignalRegionData> srdata_vector;

        for (size_t sr_index = 0; sr_index < ainfo.n_signal_regions; ++sr_index) 
        {
          // Generate an 'sr-N' label 
          std::stringstream ss; ss << "sr-" << sr_index;

          // Construct a SignalRegionData instance and add it to srdata_vector
          SignalRegionData sr;
          sr.sr_label = ss.str();
          sr.n_obs = ainfo.obsnum.at(sr_index);
          sr.n_sig_MC = sr_nums.at(sr_index);
          sr.n_sig_scaled = sr_nums.at(sr_index);  // We have already scaled the signals in sr_nums to xsec * lumi
          sr.n_sig_MC_sys = 0.;
          sr.n_bkg = ainfo.bkgnum.at(sr_index);
          sr.n_bkg_err = ainfo.bkgerr.at(sr_index);

          srdata_vector.push_back(sr);
        }

        // Save our vector of SignalRegionData in the AnalysisData instance
        adata.srdata = srdata_vector;

        // If this analysis has a background covariance matrix, copy it to the AnalysisData instance
        if (ainfo.bkgcov.size() > 0)
        {
          adata.srcov = ainfo.bkgcov;
        }

        // Save a pointer to our AnalysisData instance in the 'result' variable
        result.push_back(&adata);

      } // End loop over analyses

    };


    /// Fill the input vector with the total DMEFT signal prediction for each SR in the given LHC analysis
    void get_all_DMEFT_signal_yields(std::vector<double>& sr_nums, const DMEFT_analysis_info& analysis_info, const Spectrum& spec)
    {

      // Get the parameters we need from the theory spectrum
      double C61 = spec.get(Par::dimensionless, "C61");
      double C62 = spec.get(Par::dimensionless, "C62");
      double C63 = spec.get(Par::dimensionless, "C63");
      double C64 = spec.get(Par::dimensionless, "C64");
      double C71 = spec.get(Par::dimensionless, "C71");
      double C72 = spec.get(Par::dimensionless, "C72");
      double C73 = spec.get(Par::dimensionless, "C73");
      double C74 = spec.get(Par::dimensionless, "C74");
      double lambda = spec.get(Par::mass1, "Lambda");      
      double m = spec.get(Par::Pole_Mass, "chi");


      // Get the dim-6 yields

      // C61+C64
      std::vector<double> sig_C61_C64(analysis_info.n_signal_regions, 0.);
      get_DMEFT_signal_yields_dim6_operator(sig_C61_C64, "C61_C64", analysis_info, m, C61, C64, lambda);

      // C62+C63
      std::vector<double> sig_C62_C63(analysis_info.n_signal_regions, 0.);
      get_DMEFT_signal_yields_dim6_operator(sig_C62_C63, "C62_C63", analysis_info, m, C62, C63, lambda);


      // Get the dim-7 yields

      // C71
      std::vector<double> sig_C71(analysis_info.n_signal_regions, 0.);
      get_DMEFT_signal_yields_dim7_operator(sig_C71, "C71", analysis_info, m, C71, lambda);
      
      // C72
      std::vector<double> sig_C72(analysis_info.n_signal_regions, 0.);
      get_DMEFT_signal_yields_dim7_operator(sig_C72, "C72", analysis_info, m, C72, lambda);

      // C73
      std::vector<double> sig_C73(analysis_info.n_signal_regions, 0.);
      get_DMEFT_signal_yields_dim7_operator(sig_C73, "C73", analysis_info, m, C73, lambda);

      // C74
      std::vector<double> sig_C74(analysis_info.n_signal_regions, 0.);
      get_DMEFT_signal_yields_dim7_operator(sig_C74, "C74", analysis_info, m, C74, lambda);


      // Add yields and save in sr_num
      for (size_t i = 0; i < analysis_info.n_signal_regions; ++i)
      {
        sr_nums[i] = sig_C61_C64[i] + sig_C62_C63[i] + sig_C71[i] + sig_C72[i] + sig_C73[i] + sig_C74[i];
      }
    }


    /// Fill the input vector with the DMEFT signal prediction for a given set of dim-6 operators
    void get_DMEFT_signal_yields_dim6_operator(std::vector<double>& signal_yields, const str operator_key, const DMEFT_analysis_info& analysis_info, double m, double O1, double O2, double lambda)
    {

      // Calculate theta
      double theta;
      if (O2==0)
      {
        theta = 0.5 * pi;
      }
      else
      {
        theta = atan(O1 / O2);
        if ( O1 / O2 < 0)
        {
          theta = theta + pi;
        }
      }

      // Calculate normalisation
      double norm = O1*O1 + O2*O2;
      if (norm < 0.0)
      {
        ColliderBit_error().raise(LOCAL_INFO, "ERROR! norm < 0 in function get_DMEFT_signal_yields_dim6_operator.");
      }

      // Scaling with lambda, relative to lambda = 1000 GeV which was used to generate the data tables
      double lambda_scaling = pow(1000.0 / lambda, 4);

      // Get the interpolator collections for the given operator_key
      const Utils::interp2d_collection& xsec_interp = analysis_info.get_interp2d("mass_theta_xsecpb_" + operator_key);
      const Utils::interp2d_collection& eff_interp = analysis_info.get_interp2d("mass_theta_eff_" + operator_key);

      // Compute the signal yield for each signal region
      for (size_t sr_i = 0; sr_i < analysis_info.n_signal_regions; ++sr_i)
      {

        // 
        // Get the cross-section at the point (m,theta)
        // 

        double xsec_pb = 0.;
        // Check if (m,theta) point is inside interpolation region
        if (not xsec_interp.is_inside_range(m,theta))
        {
          if (theta < xsec_interp.y_min || theta > xsec_interp.y_max)
          {
            ColliderBit_error().raise(LOCAL_INFO, "ERROR! Theta parameter out of range.");
          }

          if (m < xsec_interp.x_min)
          {
            ColliderBit_error().raise(LOCAL_INFO, "Mass parameter below lowest mass point in the cross-section table.");
          }

          if (m > xsec_interp.x_min)
          {
            // Set cross-section to 0 for masses above the tabulated range
            xsec_pb = 0.;
          }
        }
        else // All is OK, let's evaluate the cross-section
        {
          xsec_pb = xsec_interp.eval(m, theta);
        }

        
        // 
        // Get signal efficiency for signal region sr_i at the point (m,theta)
        // 

        double eff = 0.;
        // Check if (m,theta) point is inside interpolation region
        if (not eff_interp.is_inside_range(m,theta))
        {
          if (theta < eff_interp.y_min || theta > eff_interp.y_max)
          {
            ColliderBit_error().raise(LOCAL_INFO, "ERROR! Theta parameter out of range.");
          }

          if (m < eff_interp.x_min)
          {
            ColliderBit_error().raise(LOCAL_INFO, "Mass parameter below lowest mass point in the signal efficiency table.");
          }

          if (m > eff_interp.x_min)
          {
            // Set efficiency to 0 for masses above the tabulated range
            eff = 0.;
          }
        }
        else // All is OK, let's evaluate the efficiency
        {
          eff = eff_interp.eval(m, theta, sr_i);
        }

        // 
        // Compute signal prediction and save it in the signal_yields vector
        // 

        signal_yields[sr_i] = analysis_info.lumi_invfb * (xsec_pb * 1000.) * norm * lambda_scaling * eff; // converting cross-section from pb to fb

        #ifdef COLLIDERBIT_DEBUG
        {
          cerr << std::scientific << "DEBUG:" << " operator:" << operator_key << ", analysis:" << analysis_info.name 
               << ", sr_i:" << sr_i << ", m:" << m << ", theta:" << theta << ", xsec_pb:" << xsec_pb << ", eff:" << eff 
               << ", lambda_scaling:" << lambda_scaling << ", norm:" << norm << ", signal:" << signal_yields[sr_i] << endl;
        }
        #endif

      }  // End loop over signal regions

    }


    /// Fill the input vector with the DMEFT signal prediction for a given dim-7 operator
    void get_DMEFT_signal_yields_dim7_operator(std::vector<double>& signal_yields, const str operator_key, const DMEFT_analysis_info& analysis_info, double m, double O, double lambda)
    {

      // Calculate normalisation
      double norm = O*O;
      if (norm < 0.0)
      {
        ColliderBit_error().raise(LOCAL_INFO, "ERROR! norm < 0 in function get_DMEFT_signal_yields_dim7_operator.");
      }

      // Scaling with lambda, relative to lambda = 1000 GeV which was used to generate the data tables
      double lambda_scaling = pow(1000.0 / lambda, 6);

      // Get the interpolator collections for the given operator_key
      const Utils::interp1d_collection& xsec_interp = analysis_info.get_interp1d("mass_xsecpb_" + operator_key);
      const Utils::interp1d_collection& eff_interp = analysis_info.get_interp1d("mass_eff_" + operator_key);

      // Compute the signal yield for each signal region
      for (size_t sr_i = 0; sr_i < analysis_info.n_signal_regions; ++sr_i)
      {

        // 
        // Get the cross-section for mass m
        // 

        double xsec_pb = 0.;
        // Check if m is inside interpolation region
        if (not xsec_interp.is_inside_range(m))
        {
          if (m < xsec_interp.x_min)
          {
            ColliderBit_error().raise(LOCAL_INFO, "Mass parameter below lowest mass point in the cross-section table.");
          }

          if (m > xsec_interp.x_min)
          {
            // Set cross-section to 0 for masses above the tabulated range
            xsec_pb = 0.;
          }
        }
        else // All is OK, let's evaluate the cross-section
        {
          xsec_pb = xsec_interp.eval(m);
        }

        
        // 
        // Get signal efficiency for signal region sr_i and mass m
        // 

        double eff = 0.;
        // Check if m point is inside interpolation region
        if (not eff_interp.is_inside_range(m))
        {
          if (m < eff_interp.x_min)
          {
            ColliderBit_error().raise(LOCAL_INFO, "Mass parameter below lowest mass point in the signal efficiency table.");
          }

          if (m > eff_interp.x_min)
          {
            // Set efficiency to 0 for masses above the tabulated range
            eff = 0.;
          }
        }
        else // All is OK, let's evaluate the efficiency
        {
          eff = eff_interp.eval(m, sr_i);
        }

        // 
        // Compute signal prediction and save it in the signal_yields vector
        // 

        signal_yields[sr_i] = analysis_info.lumi_invfb * (xsec_pb * 1000.) * norm * lambda_scaling * eff; // converting cross-section from pb to fb

      }  // End loop over signal regions

    }


    /// Results from DMEFT analyses after profiling over the 'a' parameter in the smooth cut-off of the MET spectrum
    void DMEFT_results_profiled(AnalysisDataPointers& result)
    {
      using namespace Pipes::DMEFT_results_profiled;

      // Clear previous vectors, etc.
      result.clear();

      // Get the original AnalysisDataPointers that we will adjust
      result = *Dep::AllAnalysisNumbersUnmodified;

      // Get the best-fit nuisance parameter(s)
      map_str_dbl bestfit_nuisance_pars = *Dep::DMEFT_profiled_LHC_nuisance_params;
      double a_bestfit = bestfit_nuisance_pars.at("a");

      // Get Lambda
      const Spectrum& spec = *Dep::DMEFT_spectrum;
      double lambda = spec.get(Par::mass1, "Lambda");

      // Recalculate AnalysisData instances in "result", using the best-fit a-value
      for (AnalysisData* adata_ptr : result)
      {
        signal_modifier_function(*adata_ptr, lambda, a_bestfit);
      }
    }


    /// Results from DMEFT analyses after imposing a hard cut-off of the MET spectrum
    void DMEFT_results_cutoff(AnalysisDataPointers& result)
    {
      using namespace Pipes::DMEFT_results_cutoff;

      // Clear previous vectors, etc.
      result.clear();

      // Get the original AnalysisDataPointers that we will adjust
      result = *Dep::AllAnalysisNumbersUnmodified;

      // Get Lambda
      const Spectrum& spec = *Dep::DMEFT_spectrum;
      double lambda = spec.get(Par::mass1, "Lambda");

      // Apply the function signal_cutoff_function to each of the 
      // AnalysisData instances in "result"
      for (AnalysisData* adata_ptr : result)
      {
        signal_cutoff_function(*adata_ptr, lambda);
      }
    }


    /// Function to modify the DMEFT LHC signal prediction for ETmiss bins where ETmiss > Lambda.
    /// Alt 1: Gradually turn off the ETmiss spectrum above Lambda by multiplying 
    /// the spectrum with (ETmiss/Lambda)^-a
    void signal_modifier_function(AnalysisData& adata, double lambda, double a)
    {
      // Check that we have analysis info for the given analysis
      if (analysis_info_map.count(adata.analysis_name) == 0)
      {
        ColliderBit_error().raise(LOCAL_INFO, "Unknown analysis '" + adata.analysis_name +"' encountered in signal_modifier_function!");
      }

      // Get a shorthand reference to the DMEFT_analysis_info instance
      const DMEFT_analysis_info& ainfo = analysis_info_map.at(adata.analysis_name);

      // Modify signals
      for (size_t bin_index = 0; bin_index < ainfo.n_signal_regions; ++bin_index) 
      {
        double MET_min = ainfo.extra_info.at("metmins")[bin_index];
        double weight = 1.0;

        if (lambda < MET_min)
        {
          weight = pow(MET_min / lambda, -a);

          if (weight < 1.0e-8) { weight = 0.0; }
        }

        SignalRegionData& srdata = adata[bin_index];
        srdata.n_sig_MC *= weight;
        srdata.n_sig_scaled *= weight;
      } 

    }


    /// Function to modify the DMEFT LHC signal prediction for ETmiss bins where ETmiss > Lambda.
    /// Alt 2: Simply put a hard cut-off in the ETmiss spectrum for ETmiss > Lambda
    void signal_cutoff_function(AnalysisData& adata, double lambda)
    {
      // Check that we have analysis info for the given analysis
      if (analysis_info_map.count(adata.analysis_name) == 0)
      {
        ColliderBit_error().raise(LOCAL_INFO, "Unknown analysis '" + adata.analysis_name +"' encountered in signal_modifier_function!");
      }

      // Get a shorthand reference to the DMEFT_analysis_info instance
      const DMEFT_analysis_info& ainfo = analysis_info_map.at(adata.analysis_name);

      // Modify signals with a hard cutoff
      for (size_t bin_index = 0; bin_index < ainfo.n_signal_regions; ++bin_index) 
      {
        double MET_min = ainfo.extra_info.at("metmins")[bin_index];

        if (lambda < MET_min)
        {
          SignalRegionData& srdata = adata[bin_index];
          srdata.n_sig_MC = 0.0;
          srdata.n_sig_scaled = 0.0;
        }
      } 

    }


    /// A target function for the GSL optimiser
    void _gsl_target_func(const size_t /* n */ , const double* a, void* fparams, double* fval)
    {
      // Note: We don't use the first argument, it's just there for the GSL/multimin interface

      double total_loglike = 0.0;

      // Cast fparams to correct type
      _gsl_target_func_params* fpars = static_cast<_gsl_target_func_params*>(fparams);

      AnalysisLogLikes analoglikes;

      // Create a vector with temp AnalysisData instances by copying the original ones
      std::vector<AnalysisData> temp_adata_vec;
      for (AnalysisData* adata_ptr : fpars->adata_ptrs_original)
      {
        const str& analysis_name = adata_ptr->analysis_name;
        // If the analysis name is in skip_analyses, don't take it into account in this profiling
        if (std::find(fpars->skip_analyses.begin(), fpars->skip_analyses.end(), analysis_name) != fpars->skip_analyses.end())
        {
          continue;
        }
        // Make a copy of the AnalysisData instance that adata_ptr points to
        temp_adata_vec.push_back( AnalysisData(*adata_ptr) );
      }

      // Now loop over all the temp AnalysisData instances and calculate the total loglike for the current a-value
      for (AnalysisData& adata : temp_adata_vec)
      {
        signal_modifier_function(adata, fpars->lambda, *a);
        analoglikes = calc_loglikes_for_analysis(adata, fpars->use_covar, fpars->use_marg, fpars->combine_nocovar_SRs, false);
        total_loglike += analoglikes.combination_loglike;
      }

      *fval = -total_loglike;
    }



    // DMEFT: Profile the 'a' nuisance parameter, which is used to smoothly 
    // suppress signal predictions for MET bins with MET > Lambda
    void calc_DMEFT_profiled_LHC_nuisance_params(map_str_dbl& result)
    {
      using namespace Pipes::calc_DMEFT_profiled_LHC_nuisance_params;

      static bool first = true;

      // Check if user has requested a fixed value for the a parameter
      static bool use_fixed_value_a = false;
      static double fixed_a = -1e99;
      if (first)
      {
        if (runOptions->hasKey("use_fixed_value_a"))
        {
          use_fixed_value_a = true;
          fixed_a = runOptions->getValue<double>("use_fixed_value_a");
        }
        first = false;
      }

      if (use_fixed_value_a)
      {
        result["a"] = fixed_a;
        return;
      }

      // Steal the list of skipped analyses from the options from the "calc_combined_LHC_LogLike" function
      std::vector<str> default_skip_analyses;  // The default is empty lists of analyses to skip
      static const std::vector<str> skip_analyses = Pipes::calc_combined_LHC_LogLike::runOptions->getValueOrDef<std::vector<str> >(default_skip_analyses, "skip_analyses");
      
      // Steal some settings from the "calc_LHC_LogLikes" function
      static const bool use_covar = Pipes::calc_LHC_LogLikes::runOptions->getValueOrDef<bool>(true, "use_covariances");
      // Use marginalisation rather than profiling (probably less stable)?
      static const bool use_marg = Pipes::calc_LHC_LogLikes::runOptions->getValueOrDef<bool>(false, "use_marginalising");
      // Use the naive sum of SR loglikes for analyses without known correlations?
      static const bool combine_nocovar_SRs = Pipes::calc_LHC_LogLikes::runOptions->getValueOrDef<bool>(false, "combine_SRs_without_covariances");

      // Clear previous result map
      result.clear();

      // Optimiser parameters
      // Params: step1size, tol, maxiter, epsabs, simplex maxsize, method, verbosity
      // Methods:
      //  0: Fletcher-Reeves conjugate gradient
      //  1: Polak-Ribiere conjugate gradient
      //  2: Vector Broyden-Fletcher-Goldfarb-Shanno method
      //  3: Steepest descent algorithm
      //  4: Nelder-Mead simplex
      //  5: Vector Broyden-Fletcher-Goldfarb-Shanno method ver. 2
      //  6: Simplex algorithm of Nelder and Mead ver. 2
      //  7: Simplex algorithm of Nelder and Mead: random initialization

      static const double INITIAL_STEP = runOptions->getValueOrDef<double>(0.1, "nuisance_prof_initstep");
      static const double CONV_TOL = runOptions->getValueOrDef<double>(0.01, "nuisance_prof_convtol");
      static const unsigned MAXSTEPS = runOptions->getValueOrDef<unsigned>(10000, "nuisance_prof_maxsteps");
      static const double CONV_ACC = runOptions->getValueOrDef<double>(0.01, "nuisance_prof_convacc");
      static const double SIMPLEX_SIZE = runOptions->getValueOrDef<double>(1e-5, "nuisance_prof_simplexsize");
      static const unsigned METHOD = runOptions->getValueOrDef<unsigned>(6, "nuisance_prof_method");
      static const unsigned VERBOSITY = runOptions->getValueOrDef<unsigned>(0, "nuisance_prof_verbosity");

      static const struct multimin::multimin_params oparams = {INITIAL_STEP, CONV_TOL, MAXSTEPS, CONV_ACC, SIMPLEX_SIZE, METHOD, VERBOSITY};

      // Set fixed function parameters
      _gsl_target_func_params fpars;
      fpars.lambda = Dep::DMEFT_spectrum->get(Par::mass1, "Lambda");
      fpars.adata_ptrs_original = *Dep::AllAnalysisNumbersUnmodified;
      fpars.skip_analyses = skip_analyses;
      fpars.use_covar = use_covar;
      fpars.use_marg = use_marg;
      fpars.combine_nocovar_SRs = combine_nocovar_SRs;

      // Create a variable to store the best-fit loglike
      double minus_loglike_bestfit = 50000.;

      // Nuisance parameter(s) to be profiled 
      // NOTE: Currently we only profile one parameter ('a'), but the 
      //       below setup can  easily be extended to more parameters
      static const std::vector<double> init_values_a = runOptions->getValue<std::vector<double>>("init_values_a");
      static const std::pair<double,double> range_a = runOptions->getValue<std::pair<double,double>>("range_a");
      
      // How many times should we run the optimiser?
      static const size_t n_runs = init_values_a.size();
      size_t run_i = 0;
      double current_bestfit_a = init_values_a.at(0);
      double current_bestfit_loglike = -minus_loglike_bestfit;

      // Mute stderr while running multimin (due to verbose gsl output)?
      static bool silence_multimin = runOptions->getValueOrDef<bool>(true, "silence_multimin");

      // Do profiling n_runs times
      while (run_i < n_runs)
      {
        std::vector<double> nuisances = {init_values_a[run_i]};  // set initial guess for each nuisance parameter
        std::vector<double> nuisances_min = {range_a.first};   // min value for each nuisance parameter
        std::vector<double> nuisances_max = {range_a.second}; // max value for each nuisance parameter
        const size_t n_profile_pars = nuisances.size();
        // Choose boundary type for each nuisance param (see comment below)
        std::vector<unsigned int> boundary_types = {6};
        /*
        From multimin.cpp:
          Interval:                                       Transformation:
          0 unconstrained                                 x=y
          1 semi-closed right half line [ xmin,+infty )   x=xmin+y^2
          2 semi-closed left  half line ( -infty,xmax ]   x=xmax-y^2
          3 closed interval              [ xmin,xmax ]    x=SS+SD*sin(y)
          4 open right half line        ( xmin,+infty )   x=xmin+exp(y)
          5 open left  half line        ( -infty,xmax )   x=xmax-exp(y)
          6 open interval                ( xmin,xmax )    x=SS+SD*tanh(y)

          where SS=.5(xmin+xmax) SD=.5(xmax-xmin)
        */

        // Call the optimiser
        if (silence_multimin)
        {
          CALL_WITH_SILENCED_STDERR(
            multimin::multimin(n_profile_pars, &nuisances[0], &minus_loglike_bestfit,
                     &boundary_types[0], &nuisances_min[0], &nuisances_max[0],
                     &_gsl_target_func, nullptr, nullptr, &fpars, oparams) 
          )
        }
        else
        {
          multimin::multimin(n_profile_pars, &nuisances[0], &minus_loglike_bestfit,
                   &boundary_types[0], &nuisances_min[0], &nuisances_max[0],
                   &_gsl_target_func, nullptr, nullptr, &fpars, oparams);
        }

        double run_i_bestfit_a = nuisances[0];
        double run_i_bestfit_loglike = -minus_loglike_bestfit;
        
        // Save info for this run
        result["a_run" + std::to_string(run_i)] = run_i_bestfit_a;
        result["loglike_run" + std::to_string(run_i)] = run_i_bestfit_loglike;

        // Update the global result?
        if (run_i_bestfit_loglike > current_bestfit_loglike)
        {
          current_bestfit_loglike = run_i_bestfit_loglike;
          current_bestfit_a = run_i_bestfit_a;
        }

        run_i++;

      } // end optimisation loop

      // Save the overall best-fit results
      result["a"] = current_bestfit_a;
      result["loglike"] = current_bestfit_loglike;


      // DEBUG: Do a grid scan of a and Lambda parameter to investigate the profiled likelihood function
      #ifdef COLLIDERBIT_DEBUG_PROFILING
        double log10_a_min = -1.0;
        double log10_a_max = 3.0;
        double step_log10_a = 0.02;

        double log10_a = log10_a_min;
        std::vector<double> a = { pow(10., log10_a) };
        double ll_val = 0.0;

        double lambda_min = 670.0;
        double lambda_max = 1070.0;
        double step_lambda = 2.0;
        double lambda = lambda_min;

        ofstream f;
        f.open("lambda_a_loglike.dat");
        
        while (lambda <= lambda_max)
        {
          log10_a = log10_a_min;

          while (log10_a <= log10_a_max)
          {
            cerr << "DEBUG: lambda, log10_a : " << lambda << ", " << log10_a << endl;
            a[0] = pow(10., log10_a);

            fpars.lambda = lambda;

            _gsl_target_func(n_profile_pars, &a[0], &fpars, &ll_val);

            f << fixed << setprecision(8) << fpars.lambda << "  " << a[0] << "  " << ll_val << "\n";

            log10_a += step_log10_a;
          }
          lambda += step_lambda;
        }
        f.close();
      #endif

    }


    /// This makes an MCLoopInfo object for satisfying the ColliderBit dependency chain
    /// (This will not be needed once we have a general system for simulation-less analyses.)
    void InterpolatedMCInfo(MCLoopInfo& result)
    {
      result.event_gen_BYPASS = true;
      result.reset_flags();
    }


  } // namespace ColliderBit
    
} // namespace Gambit
