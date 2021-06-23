//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for the plc 3.0 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Aug, Nov
///  \date 2020 Feb
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/plc_3_0.hpp"
#include "gambit/Utils/util_functions.hpp"

BE_NAMESPACE
{
  // Static varibales to be kept alive in the frontend for the scan.
  //  -> Prefix to the plc_2.0 data folder
  static std::string plc2_location;
  //  -> Prefix to the plc_3.0 data folder
  static std::string plc3_location;
  //  -> Container for all activated likelihood objects
  static std::map<std::string, std::shared_ptr<clik_object> > clik_map;
  static std::map<std::string, std::shared_ptr<clik_lensing_object> > clik_lensing_map;
  //  -> Array containing the required lmax.
  //     The order is [phiphi TT EE BB TE TB EB]
  static std::array<int,7> lmax_array{-1,-1,-1,-1,-1,-1,-1};

  // Initialise specific plc likelihood (helper function)
  void plc_init(const str& name, const str& location, const int& version, const bool& lensing)
  {
    logger() << "Loading the " << name << " likelihood " << EOM;
    std::string full_path = (version == 2 ? plc2_location : plc3_location) + location;
    if (not Utils::file_exists(full_path))
    {
      std::ostringstream err;
      err << "You have requested a plc " << version << " likelihood but it cannot be loaded." << endl
          << "The file \'" << full_path << "\' does not exist." << endl
          << "Please either do \'make plc_data" << (version == 2 ? "_2.0" : "")
          << "\', or set plc_data_" << version << "_path in the Rules section of your YAML file.";
      backend_error().raise(LOCAL_INFO, err.str());
    }
    char* clik_path = (char*)full_path.c_str();
    clik_error* plc_Error = initError();
    if (lensing)
    {
      auto destructor = [](clik_lensing_object* clikid){ clik_lensing_cleanup(&(clikid)); };
      clik_lensing_map[name] = std::shared_ptr<clik_lensing_object>(clik_lensing_init(clik_path, &plc_Error), destructor);
    }
    else
    {
      auto destructor = [](clik_object* clikid){ clik_cleanup(&(clikid)); };
      clik_map[name] = std::shared_ptr<clik_object>(clik_init(clik_path, &plc_Error), destructor);
    }
    cleanupError(&plc_Error);
  }

  // Compute specific plc likelihood(helper function)
  double plc_loglike(double* cl_and_pars, const str& name, const bool& lensing)
  {
    logger() << "Calling \"plc_loglike_" << name << "\":" << EOM;
    int map_count = (lensing ? clik_lensing_map.count(name) : clik_map.count(name));
    if (map_count == 0)
    {
      std::string mssg = "Could not find the Likelihood object \"";
      mssg += name;
      mssg += "\" in the map of activated likelihoods.";
      backend_error().raise(LOCAL_INFO,mssg.c_str());
    }
    double res;
    clik_error* plc_Error = initError();
    if (lensing)
      res = clik_lensing_compute(clik_lensing_map[name].get(), cl_and_pars, &plc_Error);
    else
      res = clik_compute(clik_map[name].get(), cl_and_pars, &plc_Error);
    if (isError(plc_Error) || !(std::isfinite(res)))
    {
      std::string err = "Calling \"plc_loglike_" + name + "\" was not successful.\n";
      char forwardedErr[4096];
      stringError(byVal(forwardedErr), plc_Error);
      invalid_point().raise(err + forwardedErr);
    }
    else
    {
      logger() << LogTags::debug << "Calling \"plc_loglike_" << name << "\""
               << " was successfull. Got " << res << EOM;
    }
    cleanupError(&plc_Error);
    return res;
  }

  // Define the individual likelihood functions for plc2
  double plc_loglike_highl_TTTEEE_2015     (double* x) { return plc_loglike(x, "highl_TTTEEE_2015",      false); }
  double plc_loglike_highl_TT_2015         (double* x) { return plc_loglike(x, "highl_TT_2015",          false); }
  double plc_loglike_highl_TTTEEE_lite_2015(double* x) { return plc_loglike(x, "highl_TTTEEE_lite_2015", false); }
  double plc_loglike_highl_TT_lite_2015    (double* x) { return plc_loglike(x, "highl_TT_lite_2015",     false); }
  double plc_loglike_lowl_TEB_2015         (double* x) { return plc_loglike(x, "lowl_TEB_2015",          false); }
  double plc_loglike_lowl_TT_2015          (double* x) { return plc_loglike(x, "lowl_TT_2015",           false); }
  double plc_loglike_lensing_2015          (double* x) { return plc_loglike(x, "lensing_2015",           true);  }

  // Define the individual likelihood functions for plc3
  double plc_loglike_highl_TTTEEE_2018     (double* x) { return plc_loglike(x, "highl_TTTEEE_2018",      false); }
  double plc_loglike_highl_TT_2018         (double* x) { return plc_loglike(x, "highl_TT_2018",          false); }
  double plc_loglike_highl_TTTEEE_lite_2018(double* x) { return plc_loglike(x, "highl_TTTEEE_lite_2018", false); }
  double plc_loglike_highl_TT_lite_2018    (double* x) { return plc_loglike(x, "highl_TT_lite_2018",     false); }
  double plc_loglike_lowl_TT_2018          (double* x) { return plc_loglike(x, "lowl_TT_2018",           false); }
  double plc_loglike_lowl_EE_2018          (double* x) { return plc_loglike(x, "lowl_EE_2018",           false); }
  double plc_loglike_lensing_2018          (double* x) { return plc_loglike(x, "lensing_2018",           true);  }
  double plc_loglike_lensing_marged_2018   (double* x) { return plc_loglike(x, "lensing_marged_2018",    true);  }

  void plc_required_Cl(int& lmax, bool& needs_tCl, bool& needs_pCl)
  {
    lmax = -1;
    for (const auto& it: lmax_array)
    {
      lmax = std::max(lmax, it);
    }
    needs_tCl = (lmax_array[1] > -1);
    auto begin = lmax_array.begin() + 2;
    auto end = lmax_array.end();
    needs_pCl = std::any_of(begin,end,[](int& i){return i > -1;});
  }

}
END_BE_NAMESPACE

BE_INI_FUNCTION
{
  // Most of the Backend initialisation is only relevant for the first parameter point
  static bool scan_level = true;
  if (scan_level)
  {
    // Check if "plc_data_2_path" and/or "plc_data_3_path" are in the runOptions. If not, look in the same place as plc for the data.
    str plc_default_path = Backends::backendInfo().path_dir("plc", STRINGIFY(VERSION)) + "/../../../plc_data/";
    plc2_location = runOptions->getValueOrDef<std::string>(plc_default_path+"2.0/plc_2.0","plc_data_2_path");
    plc3_location = runOptions->getValueOrDef<std::string>(plc_default_path+"3.0/plc_3.0","plc_data_3_path");
    if (plc2_location.back() != '/') plc2_location.push_back('/');
    if (plc3_location.back() != '/') plc3_location.push_back('/');

    // Initialise the plc2 likelihoods
    if (*InUse::plc_loglike_highl_TT_2015)          plc_init("highl_TT_2015",     "hi_l/plik/plik_dx11dr2_HM_v18_TT.clik",            2,false);
    if (*InUse::plc_loglike_highl_TTTEEE_2015)      plc_init("highl_TTTEEE_2015", "hi_l/plik/plik_dx11dr2_HM_v18_TTTEEE.clik",        2,false);
    if (*InUse::plc_loglike_highl_TT_lite_2015)     plc_init("highl_TT_lite_2015","hi_l/plik_lite/plik_lite_v18_TT.clik",             2,false);
    if (*InUse::plc_loglike_highl_TTTEEE_lite_2015) plc_init("highl_TTTEEE_lite_2015","hi_l/plik_lite/plik_lite_v18_TTTEEE.clik",     2,false);
    if (*InUse::plc_loglike_lowl_TEB_2015)          plc_init("lowl_TEB_2015","low_l/bflike/lowl_SMW_70_dx11d_2014_10_03_v5c_Ap.clik", 2,false);
    if (*InUse::plc_loglike_lowl_TT_2015)           plc_init("lowl_TT_2015","low_l/commander/commander_rc2_v1.1_l2_29_B.clik",        2,false);
    if (*InUse::plc_loglike_lensing_2015)           plc_init("lensing_2015","lensing/smica_g30_ftl_full_pp.clik_lensing",             2,true);

    // Initialise the plc3 likelihoods
    if (*InUse::plc_loglike_highl_TT_2018)          plc_init("highl_TT_2018","hi_l/plik/plik_rd12_HM_v22_TT.clik",                                               3,false);
    if (*InUse::plc_loglike_highl_TTTEEE_2018)      plc_init("highl_TTTEEE_2018","hi_l/plik/plik_rd12_HM_v22b_TTTEEE.clik",                                      3,false);
    if (*InUse::plc_loglike_highl_TT_lite_2018)     plc_init("highl_TT_lite_2018","hi_l/plik_lite/plik_lite_v22_TT.clik",                                        3,false);
    if (*InUse::plc_loglike_highl_TTTEEE_lite_2018) plc_init("highl_TTTEEE_lite_2018","hi_l/plik_lite/plik_lite_v22_TTTEEE.clik",                                3,false);
    if (*InUse::plc_loglike_lowl_TT_2018)           plc_init("lowl_TT_2018","low_l/commander/commander_dx12_v3_2_29.clik",                                       3,false);
    if (*InUse::plc_loglike_lowl_EE_2018)           plc_init("lowl_EE_2018","low_l/simall/simall_100x143_offlike5_EE_Aplanck_B.clik",                            3,false);
    if (*InUse::plc_loglike_lensing_2018)           plc_init("lensing_2018","lensing/smicadx12_Dec5_ftl_mv2_ndclpp_p_teb_consext8.clik_lensing",                 3,true);
    if (*InUse::plc_loglike_lensing_marged_2018)    plc_init("lensing_marged_2018","lensing/smicadx12_Dec5_ftl_mv2_ndclpp_p_teb_consext8_CMBmarged.clik_lensing",3,true);

    for (const auto& it: clik_map)
    {
      std::array<int,7> tmp{};
      clik_get_lmax(it.second.get(), tmp.data()+1, NULL);
      for (size_t i = 1; i < 7; ++i)
      {
        lmax_array[i] = std::max(lmax_array[i],tmp[i]);
      }
    }

    for (const auto& it: clik_lensing_map)
    {
      std::array<int,7> tmp{};
      clik_lensing_get_lmaxs(it.second.get(), tmp.data(), NULL);
      for (size_t i = 0; i < 7; ++i)
      {
        lmax_array[i] = std::max(lmax_array[i],tmp[i]);
      }
    }

    scan_level = false;
  }
}
END_BE_INI_FUNCTION
