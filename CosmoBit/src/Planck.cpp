//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Planck routines in CosmoBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Selim C. Hotinli
///          (selim.hotinli14@pimperial.ac.uk)
///  \date 2017 Jul
///  \date 2018 May
///  \date 2018 Aug - Sep
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2017 Nov
///  \date 2018 Jan - May
///  \date 2019 Jan, Feb, June, Nov
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date 2018 June
///  \date 2019 Mar,June
///
///  \author Sanjay Bloor
///          (sanjay.bloor12@imperial.ac.uk)
///  \date 2019 June, Nov
///
///  *********************************************
#include <cmath>
#include <iostream>
#include <string>

#include "gambit/Utils/statistics.hpp"
#include "gambit/Utils/ascii_dict_reader.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/CosmoBit/CosmoBit_rollcall.hpp"

namespace Gambit
{

  namespace CosmoBit
  {
    using namespace LogTags;

    // Anonymous namespace
    // - It is only visible to this file
    // - Variables in here won't show up in the compiled files and are not seen by the linker
    namespace
    {
      // In the Planck analysis the monopole (CMB temperature) is assumed to be
      // T_cmb = 2.72548 K (FIRAS measurement).
      // To correctly reconstruct the dimensionful Cl out of the dimensionless Cl,
      // this value needs to be assumed rather than the (variable) value of T_cmb.
      // (cf. Appendix A of arXiv:2005.10656)
      double T_cmb_FIRAS = 2.72548;
    }

    /// Apply Gaussian priors on some of the Planck nuisance parameters (cf. table 16 of 1907.1287)
    /// By default, the 2018 priors are used.
    /// If the 2015 priors should be considered, set "version: 2015" in the rules of this function.
    /// If needed, a custom file with the priors can be passed via the "prior_file" keyword in the rules.
    void compute_Planck_nuisance_prior_loglike(double& result)
    {
      using namespace Pipes::compute_Planck_nuisance_prior_loglike;

      static std::map<std::string, std::vector<double> > data;

      // Read the data only at first iteration
      static bool first = true;
      if (first)
      {
        first = false;
        std::string filename;
        if (runOptions->hasKey("prior_file"))
        {
          filename = runOptions->getValue<std::string>("prior_file");
        }
        else
        {
          filename = GAMBIT_DIR "/CosmoBit/data/Planck/";
          std::string version = runOptions->getValueOrDef<std::string>("2018","version");
          filename += "priors_" + version + ".dat";
        }
        ASCIIdictReader reader(filename);
        logger() << LogTags::info << "Read priors for Planck nuisance parameters from file '"<<filename<<"'." << EOM;

        std::map<std::string, std::vector<double> > tmp = reader.get_dict();
        logger() << LogTags::info << "Found the follwing prior for planck parameters ( name -- [modelcode, mean, sig] )\n\n";
        logger() << LogTags::info << tmp << EOM;

        int modelcode = -1;
        if (ModelInUse("cosmo_nuisance_Planck_lite"))
          modelcode = 1;
        else if (ModelInUse("cosmo_nuisance_Planck_TT"))
          modelcode = 3;
        else if (ModelInUse("cosmo_nuisance_Planck_TTTEEE"))
          modelcode = 7;

        for (auto iter=tmp.begin(); iter != tmp.end(); iter++)
        {
          if ( int(iter->second[0]) <= modelcode )
          {
            std::string key = iter->first;
            try
            {
              *Param[key];
            }
            catch (std::exception &e)
            {
              std::ostringstream err;
              err << "Caught an undefined model parameter. The planck nuisance parameter \"" << key << "\" is not known.\n\n";
              err << "Original error was:\n\n" << e.what();
              CosmoBit_error().raise(LOCAL_INFO,err.str());
            }
            data[iter->first] = std::vector<double>({iter->second[1], iter->second[2]});
          }
        }
        logger() << LogTags::info << "Gaussian prior an Planck parameters used in this scan (name -- [mean, sig]):\n\n" << data << EOM;
        logger() << LogTags::info << "Data for Planck nuisance priors read." << EOM;
      }

      /// Loop over all parameters and apply the prior
      result = 0.0;
      for (auto iter = data.begin(); iter != data.end(); iter++)
      {
        result += Stats::gaussian_loglikelihood((*Param[iter->first]), iter->second[0], 0.0, iter->second[1], false);
      }
    }

    /// SZ- prior: Prior on the tSZ and kSZ amplitudes.
    /// Correlation is unconstrained by Planck. Use prior based on SPT and ACT data.
    /// (cf. https://arxiv.org/pdf/1507.02704.pdf -- eq. 32)
    void compute_Planck_sz_prior(double& result)
    {
      using namespace Pipes::compute_Planck_sz_prior;

      double ksz_norm = *Param["ksz_norm"];
      double A_sz = *Param["A_sz"];
      result = Stats::gaussian_loglikelihood((ksz_norm + 1.6*A_sz), 9.5, 0.0, 3.0, false);
    }


    /*** 2018 ***/

    /// Low-l TT likelihood (PR3 - 2018)
    void function_Planck_lowl_TT_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lowl_TT_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-29] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double cl_and_pars[31];
      int idx_tt;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if( Cl_TT.size() < 30)
      {
        std::ostringstream err;
        err << "For \"function_Planck_lowl_TT_2018_loglike\" the Cl need to be calculated for l up to 29.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 29)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT to Cl array-------------------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 30 ; ii++)
      {
        idx_tt = ii;
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[30] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_lowl_TT_2018(&cl_and_pars[0]);

    }

    /// Low-l E-mode polarisation likelihood (PR3 - 2018)
    void function_Planck_lowl_EE_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lowl_EE_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // EE[0-29] - Nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double cl_and_pars[31];
      int idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if( Cl_EE.size() < 30)
      {
        std::ostringstream err;
        err << "For \"function_Planck_lowl_EE_2018_loglike\" the Cl need to be calculated for l up to 29.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 29)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT to Cl array-------------------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 30 ; ii++)
      {
        idx_ee = ii;
        if (ii >= 2)
        {
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
        }
        else
        {
          cl_and_pars[idx_ee] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[30] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_lowl_EE_2018(&cl_and_pars[0]);

    }

    /// Combined low-l TT and and E-mode polarisation likelihood (PR3 - 2018)
    void function_Planck_lowl_TTEE_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lowl_TTEE_2018_loglike;

      // This function combines the lowl TT 2018 and the lowl EE 2018 likelihood

      // Array containing the relevant Cl and nuisance paramters for the TT part
      // The order will be the following:
      // TT[0-29] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double cl_and_pars_TT[31];
      int idx_tt;

      // Same as above but now for EE
      // The order will be the following:
      // EE[0-29] - nuisance parameter
      double cl_and_pars_EE[31];
      int idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if( Cl_TT.size() < 30 || Cl_EE.size() < 30)
      {
        std::ostringstream err;
        err << "For \"function_Planck_lowl_TTEE_2018_loglike\" the Cl need to be calculated for l up to 29.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 29)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT (EE) to Cl arrays-------------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 30 ; ii++)
      {
        idx_tt = ii;
        idx_ee = ii;

        if (ii >= 2)
        {
          cl_and_pars_TT[idx_tt] = Cl_TT.at(ii);
          cl_and_pars_EE[idx_ee] = Cl_EE.at(ii);
        }
        else
        {
          cl_and_pars_TT[idx_tt] = 0.;
          cl_and_pars_EE[idx_ee] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl arrays------------------------
      //--------------------------------------------------------------------------
      cl_and_pars_TT[30] = *Param["A_planck"];
      cl_and_pars_EE[30] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      double tmp_result = 0.0; // temporary to not spoil the printer output if the TT works but EE fails.
      tmp_result += BEreq::plc_loglike_lowl_TT_2018(&cl_and_pars_TT[0]);
      // The EE Planck likelihood shoulw always be < 0, if not something went wrong
      // FIXME: For now invalidate the point, until we find the source of the issue
      double EE = BEreq::plc_loglike_lowl_EE_2018(&cl_and_pars_EE[0]);
      if(EE > 0.0)
      {
        std::ostringstream err;
        err << "EE lowl Planck likelihood is problematic, with value " << EE;
        logger() << err.str() << EOM;
        invalid_point().raise(err.str());
      }
      tmp_result += EE;

      // Now update result
      result = tmp_result;

    }

    /// High-l TT likelihood (PR3 - 2018)
    void function_Planck_highl_TT_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TT_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-2508] - nuisance parameters
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double  cl_and_pars[2529];

      int idx_tt;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if( Cl_TT.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TT_2018_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err <<" (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT to Cl array-------------------------------
      //--------------------------------------------------------------------------

      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;

        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[2509] = *Param["A_cib_217"];
      cl_and_pars[2510] = *Param["cib_index"];
      cl_and_pars[2511] = *Param["xi_sz_cib"];
      cl_and_pars[2512] = *Param["A_sz"];
      cl_and_pars[2513] = *Param["ps_A_100_100"];
      cl_and_pars[2514] = *Param["ps_A_143_143"];
      cl_and_pars[2515] = *Param["ps_A_143_217"];
      cl_and_pars[2516] = *Param["ps_A_217_217"];
      cl_and_pars[2517] = *Param["ksz_norm"];
      cl_and_pars[2518] = *Param["gal545_A_100"];
      cl_and_pars[2519] = *Param["gal545_A_143"];
      cl_and_pars[2520] = *Param["gal545_A_143_217"];
      cl_and_pars[2521] = *Param["gal545_A_217"];
      // set A_sbpx_... to 1. (4 nusissance parameter)
      for (int i = 0; i < 4; i++) cl_and_pars[(i+2522)] = 1.;
      cl_and_pars[2526] = *Param["calib_100T"];
      cl_and_pars[2527] = *Param["calib_217T"];
      cl_and_pars[2528] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TT_2018(&cl_and_pars[0]);

    }

    /// Marginalised version of the high-l TT likelihood (PR3 - 2018)
    void function_Planck_highl_TT_lite_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TT_lite_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-2508] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double cl_and_pars[2510];

      int idx_tt;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if ( Cl_TT.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TT_lite_2018_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT to Cl array-------------------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[2509] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TT_lite_2018(&cl_and_pars[0]);

    }

    /// High-l TT and polarisation likelihood (PR3 - 2018)
    void function_Planck_highl_TTTEEE_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TTTEEE_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-2508] - EE[0-2508] - TE[0-2508] - nuisance parameters
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double  cl_and_pars[7574];
      int idx_tt, idx_te, idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_TE = *Dep::lensed_Cl_TE;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_TE.begin(), Cl_TE.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not, ask the user to adjust the inputs for CLASS
      if ( Cl_TT.size() < 2509 || Cl_TE.size() < 2509 || Cl_EE.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TTTEEE_2018_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT, EE and TE to Cl array--------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;
        idx_ee = ii + 2509;
        idx_te = ii + (2 * 2509);
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
          cl_and_pars[idx_te] = Cl_TE.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
          cl_and_pars[idx_ee] = 0.;
          cl_and_pars[idx_te] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[7527] = *Param["A_cib_217"];
      cl_and_pars[7528] = *Param["cib_index"];
      cl_and_pars[7529] = *Param["xi_sz_cib"];
      cl_and_pars[7530] = *Param["A_sz"];
      cl_and_pars[7531] = *Param["ps_A_100_100"];
      cl_and_pars[7532] = *Param["ps_A_143_143"];
      cl_and_pars[7533] = *Param["ps_A_143_217"];
      cl_and_pars[7534] = *Param["ps_A_217_217"];
      cl_and_pars[7535] = *Param["ksz_norm"];
      cl_and_pars[7536] = *Param["gal545_A_100"];
      cl_and_pars[7537] = *Param["gal545_A_143"];
      cl_and_pars[7538] = *Param["gal545_A_143_217"];
      cl_and_pars[7539] = *Param["gal545_A_217"];
      cl_and_pars[7540] = *Param["galf_EE_A_100"];
      cl_and_pars[7541] = *Param["galf_EE_A_100_143"];
      cl_and_pars[7542] = *Param["galf_EE_A_100_217"];
      cl_and_pars[7543] = *Param["galf_EE_A_143"];
      cl_and_pars[7544] = *Param["galf_EE_A_143_217"];
      cl_and_pars[7545] = *Param["galf_EE_A_217"];
      cl_and_pars[7546] = *Param["galf_EE_index"];
      cl_and_pars[7547] = *Param["galf_TE_A_100"];
      cl_and_pars[7548] = *Param["galf_TE_A_100_143"];
      cl_and_pars[7549] = *Param["galf_TE_A_100_217"];
      cl_and_pars[7550] = *Param["galf_TE_A_143"];
      cl_and_pars[7551] = *Param["galf_TE_A_143_217"];
      cl_and_pars[7552] = *Param["galf_TE_A_217"];
      cl_and_pars[7553] = *Param["galf_TE_index"];
      // set A_cnoise_.. and A_sbpx_... to 1. (13 nusissance parameter)
      for (int i = 0; i < 13; i++) cl_and_pars[(i+7554)] = 1.;
      cl_and_pars[7567] = *Param["calib_100T"];
      cl_and_pars[7568] = *Param["calib_217T"];
      cl_and_pars[7569] = *Param["calib_100P"];
      cl_and_pars[7570] = *Param["calib_143P"];
      cl_and_pars[7571] = *Param["calib_217P"];
      cl_and_pars[7572] = *Param["A_pol"];
      cl_and_pars[7573] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TTTEEE_2018(&cl_and_pars[0]);

    }

    /// Marginalised version of the high-l TT and polarisation likelihood (PR3 - 2018)
    void function_Planck_highl_TTTEEE_lite_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TTTEEE_lite_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-2508] - EE[0-2508] - TE[0-2508] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double  cl_and_pars[7528];

      int idx_tt, idx_te, idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_TE = *Dep::lensed_Cl_TE;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_TE.begin(), Cl_TE.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not, ask the user to adjust the inputs for CLASS
      if ( Cl_TT.size() < 2509 || Cl_TE.size() < 2509 || Cl_EE.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TTTEEE_lite_2018_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT, EE and TE to Cl array--------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;
        idx_ee = ii + 2509;
        idx_te = ii + (2 * 2509);
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
          cl_and_pars[idx_te] = Cl_TE.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
          cl_and_pars[idx_ee] = 0.;
          cl_and_pars[idx_te] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[7527] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TTTEEE_lite_2018(&cl_and_pars[0]);

    }

    /// Lensing likelihood (PR3 - 2018)
    void function_Planck_lensing_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lensing_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // PhiPhi[0-2500] - TT[0-2500] - EE[0-2500] - TE[0-2500] - nuisance parameters
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double  cl_and_pars[10005];

      int idx_pp, idx_tt, idx_te, idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_PhiPhi = *Dep::lensed_Cl_PhiPhi;
      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_TE = *Dep::lensed_Cl_TE;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_TE.begin(), Cl_TE.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not, ask the user to adjust the inputs for CLASS
      if ((Cl_PhiPhi.size() < 2501) || (Cl_TT.size() < 2501) || (Cl_TE.size() < 2501) || (Cl_EE.size() < 2501))
      {
        std::ostringstream err;
        err << "For \"function_Planck_lensing_2018_loglike\" the Cl need to be calculated for l up to 2500.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2500)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for PhiPhi, TT, EE and TE to Cl array-----------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2501 ; ii++)
      {
        idx_pp = ii;
        idx_tt = ii + 2501;
        idx_ee = ii + (2 * 2501);
        idx_te = ii + (3 * 2501);
        if (ii >= 2)
        {
          cl_and_pars[idx_pp] = Cl_PhiPhi.at(ii);
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
          cl_and_pars[idx_te] = Cl_TE.at(ii);
        }
        else
        {
          cl_and_pars[idx_pp] = 0.;
          cl_and_pars[idx_tt] = 0.;
          cl_and_pars[idx_ee] = 0.;
          cl_and_pars[idx_te] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[10004] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_lensing_2018(&cl_and_pars[0]);

    }

    /// Lensing Likelihood (marginalised over reference spectra for TT,EE, etc.) (PR3 - 2018)
    void function_Planck_lensing_marged_2018_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lensing_marged_2018_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // PhiPhi[0-2500] - nuisance parameters
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code)
      double  cl_and_pars[2502];

      int idx_pp;

      std::vector<double> Cl_PhiPhi = *Dep::lensed_Cl_PhiPhi;

      // Check if the sizes of the Cl arrays are suitable. If not, ask the user to adjust the inputs for CLASS
      if ((Cl_PhiPhi.size() < 2501))
      {
        std::ostringstream err;
        err << "For \"function_Planck_lensing_marged_2018_loglike\" the Cl need to be calculated for l up to 2500.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2500)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for PhiPhi, TT, EE and TE to Cl array-----------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2501 ; ii++)
      {
        idx_pp = ii;
        if (ii >= 2)
        {
          cl_and_pars[idx_pp] = Cl_PhiPhi.at(ii);
        }
        else
        {
          cl_and_pars[idx_pp] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[2501] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_lensing_marged_2018(&cl_and_pars[0]);

    }

    /*** 2015 ***/

    /// Low-l TT likelihood (PR2 - 2015)
    void function_Planck_lowl_TT_2015_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lowl_TT_2015_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-29] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code -> Previous releases -> 2015)
      double cl_and_pars[31];
      int idx_tt;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if( Cl_TT.size() < 30)
      {
        std::ostringstream err;
        err << "For \"function_Planck_lowl_TT_2015_loglike\" the Cl need to be calculated for l up to 29.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 29)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT to Cl array-------------------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 30 ; ii++)
      {
        idx_tt = ii;
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[30] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_lowl_TT_2015(&cl_and_pars[0]);

    }

    /// Low-l polarisation likelihood (PR2 - 2015)
    void function_Planck_lowl_TEB_2015_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lowl_TEB_2015_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-29] - EE[0-29] - BB[0-29] - TE[0-29] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code -> Previous releases -> 2015)
      double  cl_and_pars[121];

      int idx_tt, idx_te, idx_ee, idx_bb;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;
      std::vector<double> Cl_TE = *Dep::lensed_Cl_TE;
      std::vector<double> Cl_BB = *Dep::lensed_Cl_BB;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );
      std::for_each(Cl_TE.begin(), Cl_TE.end(), scale_func );
      std::for_each(Cl_BB.begin(), Cl_BB.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if( Cl_TT.size() < 30 || Cl_EE.size() < 30 || Cl_TE.size() < 30 || Cl_BB.size() < 30 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_lowl_TEB_2015_loglike\" the Cl need to be calculated for l up to 29.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 29)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT, EE, BB and TE to Cl array----------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 30 ; ii++)
      {
        idx_tt = ii;
        idx_ee = ii + 30;
        idx_bb = ii + (2 * 30);
        idx_te = ii + (3 * 30);
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
          cl_and_pars[idx_bb] = Cl_BB.at(ii);
          cl_and_pars[idx_te] = Cl_TE.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
          cl_and_pars[idx_te] = 0.;
          cl_and_pars[idx_bb] = 0.;
          cl_and_pars[idx_te] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[120] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_lowl_TEB_2015(&cl_and_pars[0]);

    }

    /// High-l TT likelihood (PR2 - 2015)
    void function_Planck_highl_TT_2015_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TT_2015_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-2508] - Nuisance parameters
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code -> Previous releases -> 2015)
      double  cl_and_pars[2525];

      int idx_tt;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if( Cl_TT.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TT_2015_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err <<" (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT to Cl array-------------------------------
      //--------------------------------------------------------------------------

      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;

        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[2509] = *Param["A_cib_217"];
      cl_and_pars[2510] = *Param["cib_index"];
      cl_and_pars[2511] = *Param["xi_sz_cib"];
      cl_and_pars[2512] = *Param["A_sz"];
      cl_and_pars[2513] = *Param["ps_A_100_100"];
      cl_and_pars[2514] = *Param["ps_A_143_143"];
      cl_and_pars[2515] = *Param["ps_A_143_217"];
      cl_and_pars[2516] = *Param["ps_A_217_217"];
      cl_and_pars[2517] = *Param["ksz_norm"];
      cl_and_pars[2518] = *Param["gal545_A_100"];
      cl_and_pars[2519] = *Param["gal545_A_143"];
      cl_and_pars[2520] = *Param["gal545_A_143_217"];
      cl_and_pars[2521] = *Param["gal545_A_217"];
      cl_and_pars[2522] = *Param["calib_100T"];
      cl_and_pars[2523] = *Param["calib_217T"];
      cl_and_pars[2524] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TT_2015(&cl_and_pars[0]);

    }

    /// Marginalised version of high-l TT likelihood (PR2 - 2015)
    void function_Planck_highl_TT_lite_2015_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TT_lite_2015_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // TT[0-2508] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code -> Previous releases -> 2015)
      double cl_and_pars[2510];

      int idx_tt;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not ask the user to adjust the inputs for CLASS
      if ( Cl_TT.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TT_lite_2015_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT to Cl array-------------------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[2509] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TT_lite_2015(&cl_and_pars[0]);

    }

    /// High-l TT and polarisation likelihood (PR2 - 2015)
    void function_Planck_highl_TTTEEE_2015_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TTTEEE_2015_loglike;

      // Array containing the relevant Cl and nuissance paramters
      // The order will be the following:
      // TT[0-2508] - EE[0-2508] - TE[0-2508] - nuisance parameters
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code -> Previous releases -> 2015)
      double  cl_and_pars[7621];
      int idx_tt, idx_te, idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_TE = *Dep::lensed_Cl_TE;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_TE.begin(), Cl_TE.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not, ask the user to adjust the inputs for CLASS
      if ( Cl_TT.size() < 2509 || Cl_TE.size() < 2509 || Cl_EE.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TTTEEE_2015_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT, EE and TE to Cl array--------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;
        idx_ee = ii + 2509;
        idx_te = ii + (2 * 2509);
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
          cl_and_pars[idx_te] = Cl_TE.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
          cl_and_pars[idx_ee] = 0.;
          cl_and_pars[idx_te] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[7527] = *Param["A_cib_217"];
      cl_and_pars[7528] = *Param["cib_index"];
      cl_and_pars[7529] = *Param["xi_sz_cib"];
      cl_and_pars[7530] = *Param["A_sz"];
      cl_and_pars[7531] = *Param["ps_A_100_100"];
      cl_and_pars[7532] = *Param["ps_A_143_143"];
      cl_and_pars[7533] = *Param["ps_A_143_217"];
      cl_and_pars[7534] = *Param["ps_A_217_217"];
      cl_and_pars[7535] = *Param["ksz_norm"];
      cl_and_pars[7536] = *Param["gal545_A_100"];
      cl_and_pars[7537] = *Param["gal545_A_143"];
      cl_and_pars[7538] = *Param["gal545_A_143_217"];
      cl_and_pars[7539] = *Param["gal545_A_217"];
      cl_and_pars[7540] = *Param["galf_EE_A_100"];
      cl_and_pars[7541] = *Param["galf_EE_A_100_143"];
      cl_and_pars[7542] = *Param["galf_EE_A_100_217"];
      cl_and_pars[7543] = *Param["galf_EE_A_143"];
      cl_and_pars[7544] = *Param["galf_EE_A_143_217"];
      cl_and_pars[7545] = *Param["galf_EE_A_217"];
      cl_and_pars[7546] = *Param["galf_EE_index"];
      cl_and_pars[7547] = *Param["galf_TE_A_100"];
      cl_and_pars[7548] = *Param["galf_TE_A_100_143"];
      cl_and_pars[7549] = *Param["galf_TE_A_100_217"];
      cl_and_pars[7550] = *Param["galf_TE_A_143"];
      cl_and_pars[7551] = *Param["galf_TE_A_143_217"];
      cl_and_pars[7552] = *Param["galf_TE_A_217"];
      cl_and_pars[7553] = *Param["galf_TE_index"];
      // set beam-leakage to zero (60 nusissance parameter)
      for (int i = 0; i < 60; i++) cl_and_pars[(i+7554)] = 0.;
      cl_and_pars[7614] = *Param["calib_100T"];
      cl_and_pars[7615] = *Param["calib_217T"];
      cl_and_pars[7616] = *Param["calib_100P"];
      cl_and_pars[7617] = *Param["calib_143P"];
      cl_and_pars[7618] = *Param["calib_217P"];
      cl_and_pars[7619] = *Param["A_pol"];
      cl_and_pars[7620] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TTTEEE_2015(&cl_and_pars[0]);

    }

    /// Marginalised version of high-l TT and polarisation likelihood (PR2 - 2015)
    void function_Planck_highl_TTTEEE_lite_2015_loglike(double& result)
    {
      using namespace Pipes::function_Planck_highl_TTTEEE_lite_2015_loglike;

      // Array containing the relevant Cl and nuissance paramters
      // The order will be the following:
      // TT[0-2508] - EE[0-2508] - TE[0-2508] - nuisance parameter
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code -> Previous releases -> 2015)
      double  cl_and_pars[7528];

      int idx_tt, idx_te, idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_TE = *Dep::lensed_Cl_TE;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_TE.begin(), Cl_TE.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not, ask the user to adjust the inputs for CLASS
      if ( Cl_TT.size() < 2509 || Cl_TE.size() < 2509 || Cl_EE.size() < 2509 )
      {
        std::ostringstream err;
        err << "For \"function_Planck_highl_TTTEEE_lite_2015_loglike\" the Cl need to be calculated for l up to 2508.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2508)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for TT, EE and TE to Cl array--------------------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2509 ; ii++)
      {
        idx_tt = ii;
        idx_ee = ii + 2509;
        idx_te = ii + (2 * 2509);
        if (ii >= 2)
        {
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
          cl_and_pars[idx_te] = Cl_TE.at(ii);
        }
        else
        {
          cl_and_pars[idx_tt] = 0.;
          cl_and_pars[idx_ee] = 0.;
          cl_and_pars[idx_te] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[7527] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_highl_TTTEEE_lite_2015(&cl_and_pars[0]);

    }

    /// Lensing likelihood (PR2 - 2015)
    void function_Planck_lensing_2015_loglike(double& result)
    {
      using namespace Pipes::function_Planck_lensing_2015_loglike;

      // Array containing the relevant Cl and nuisance paramters
      // The order will be the following:
      // PhiPhi[0-2048] - TT[0-2048] - EE[0-2048] - TE[0-2048] - nuisance parameters
      // (c.f. https://wiki.cosmos.esa.int/planck-legacy-archive/index.php/CMB_spectrum_%26_Likelihood_Code -> Previous releases -> 2015)
      double  cl_and_pars[8197];

      int idx_pp, idx_tt, idx_te, idx_ee;

      double Tcmb_in_mK = (1e6)*(T_cmb_FIRAS);
      auto scale_func = [Tcmb_in_mK](double& cl){cl *= pow( Tcmb_in_mK, 2);};

      std::vector<double> Cl_PhiPhi = *Dep::lensed_Cl_PhiPhi;
      std::vector<double> Cl_TT = *Dep::lensed_Cl_TT;
      std::vector<double> Cl_TE = *Dep::lensed_Cl_TE;
      std::vector<double> Cl_EE = *Dep::lensed_Cl_EE;

      std::for_each(Cl_TT.begin(), Cl_TT.end(), scale_func );
      std::for_each(Cl_TE.begin(), Cl_TE.end(), scale_func );
      std::for_each(Cl_EE.begin(), Cl_EE.end(), scale_func );

      // Check if the sizes of the Cl arrays are suitable. If not, ask the user to adjust the inputs for CLASS
      if ((Cl_PhiPhi.size() < 2049) || (Cl_TT.size() < 2049) || (Cl_TE.size() < 2049) || (Cl_EE.size() < 2049))
      {
        std::ostringstream err;
        err << "For \"function_Planck_lensing_2015_loglike\" the Cl need to be calculated for l up to 2048.\n";
        err << "The given Cl spectra do not provide this range. Please adjust the input for CLASS.";
        err << " (\"l_max_scalars\" should be at least 2048)";
        CosmoBit_error().raise(LOCAL_INFO, err.str());
      }

      //--------------------------------------------------------------------------
      //------addition of the Cl for PhiPhi, TT, EE and TE to Cl array-----------
      //--------------------------------------------------------------------------
      for(int ii = 0; ii < 2049 ; ii++)
      {
        idx_pp = ii;
        idx_tt = ii + 2049;
        idx_ee = ii + (2 * 2049);
        idx_te = ii + (3 * 2049);
        if (ii >= 2)
        {
          cl_and_pars[idx_pp] = Cl_PhiPhi.at(ii);
          cl_and_pars[idx_tt] = Cl_TT.at(ii);
          cl_and_pars[idx_ee] = Cl_EE.at(ii);
          cl_and_pars[idx_te] = Cl_TE.at(ii);
        }
        else
        {
          cl_and_pars[idx_pp] = 0.;
          cl_and_pars[idx_tt] = 0.;
          cl_and_pars[idx_ee] = 0.;
          cl_and_pars[idx_te] = 0.;
        }
      }

      //--------------------------------------------------------------------------
      //------addition of nuisance parameters to Cl array-------------------------
      //--------------------------------------------------------------------------
      cl_and_pars[8196] = *Param["A_planck"];

      //--------------------------------------------------------------------------
      //------calculation of the planck loglikelihood-----------------------------
      //--------------------------------------------------------------------------
      result = BEreq::plc_loglike_lensing_2015(&cl_and_pars[0]);

    }

  } // CosmoBit
} // Gambit
