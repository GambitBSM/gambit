//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for AlterBBN backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Janina Renk
///         (janina.renk@fysik.su.se)
/// \date 2018 Jun
/// \date 2020 Jan
/// \date 2020 May
///
/// \author Patrick Stöcker
///         (stoecker@physik.rwth-achen.de)
/// \date 2019 Sep
///
/// \author Will Handley
///         (wh260@cam.ac.uk)
/// \date 2020 Mar
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2020 Apr
///
///  \author Tomas Gonzalo
///          (gonzalo@physik.rwth-aachen.de)
///  \date 2022 Jan
///
///  *********************************************

#include <sstream>
#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/AlterBBN_2_2.hpp"

#define NNUC 26 // number of element abundances computed in AlterBBN 2.2

// Initialisation
BE_INI_FUNCTION{
}
END_BE_INI_FUNCTION

// Convenience functions (definitions)
BE_NAMESPACE
{
  static int                 nucl_err_res=0;
  static map_str_dbl         prev_AlterBBN_input{};
  static std::vector<double> prev_ratioH(0., NNUC+1);
  static std::vector<double> prev_cov_ratioH(0., (NNUC+1)*(NNUC+1));

  /// string set containing the name of all members of the AlterBBN relicparam structures that can currently
  /// be set with GAMBIT. If you add a new model and need to pass a different option to AlterBBN add e.g. "neutron_lifetime"
  /// here and in the function fill_cosmomodel below to modify the lifetime of the neutron
  std::set<std::string> known_relicparam_options = {"eta0", "Nnu", "dNnu", "neutron_lifetime", "err","failsafe"};

  /// Fill AlterBBN's relicparam with the entries from the AlterBBN_input
  void fill_cosmomodel(AlterBBN_2_2::relicparam * input_relicparam, map_str_dbl & AlterBBN_input)
  {
    // check that only options that are known to the interface, i.e. that they are one of the options
    // defined in the string set 'known_relicparam_options' above, are passed to AlterBBN
    static bool first_run = true;
    if(first_run)
    {
      for (const auto& it : AlterBBN_input)
      {
        // throw error if an option is not currently being passed on to AlterBBN & tell user how to change that
        if(known_relicparam_options.count(it.first)==0)
        {
          std::ostringstream errormsg;
          errormsg << "Option '" << it.first << "' tried to pass to AlterBBN_" << VERSION<< " is not know to the relicparam strucutre "<<std::endl;
          errormsg << "Known options are:";
          for(auto item : known_relicparam_options)
          {
            errormsg << " '" << item << "'";
          }
          errormsg << ". Check for typos or add new one to the string set 'known_relicparam_options' in Backends/src/frontends/AlterBBN_"<< VERSION<< ".cpp"<<std::endl;
          backend_error().raise(LOCAL_INFO,errormsg.str());
        }
      }
      first_run = false;
    }

    // below for the parameter you want to overwrite
    if (AlterBBN_input.count("eta0")){input_relicparam->eta0 = AlterBBN_input["eta0"];}
    if (AlterBBN_input.count("Nnu")){input_relicparam->Nnu = AlterBBN_input["Nnu"];}
    if (AlterBBN_input.count("dNnu")){input_relicparam->dNnu = AlterBBN_input["dNnu"];}
    if (AlterBBN_input.count("neutron_lifetime")){input_relicparam->life_neutron = AlterBBN_input["neutron_lifetime"];}

    // set error handling related parameters
    if (AlterBBN_input.count("failsafe")){input_relicparam->failsafe = (int)AlterBBN_input["failsafe"];}
    if (AlterBBN_input.count("err")){input_relicparam->err = (int)AlterBBN_input["err"];}
  }

  /// calls the AlterBBN routine nucl_err with the filled relicparam structure. This will fill the array ratioH with
  /// all computed element abundances, and cov_ratioH with their errors & covariances
  int call_nucl_err(map_str_dbl &AlterBBN_input, double* ratioH, double* cov_ratioH )
  {
    if (AlterBBN_input != prev_AlterBBN_input)
    {
      AlterBBN_2_2::relicparam input_relicparam;
      Init_cosmomodel(&input_relicparam); // initialise values of relicparam structure to their defaults
      fill_cosmomodel(&input_relicparam, AlterBBN_input); // fill strucutre with values contained in AlerBBN_input map which is filled in CosmoBit.ccp for different models
  
      nucl_err_res = nucl_err(&input_relicparam, ratioH, cov_ratioH);
      prev_ratioH = std::vector<double>(ratioH, ratioH+NNUC+1);
      prev_cov_ratioH = std::vector<double>(cov_ratioH, cov_ratioH+(NNUC+1)*(NNUC+1));
      prev_AlterBBN_input = AlterBBN_input;
    }
    else
    {
      for (size_t i=0;i<NNUC+1;i++) ratioH[i] = prev_ratioH[i];
      for (size_t i=0;i<(NNUC+1)*(NNUC+1);i++) cov_ratioH[i] = prev_cov_ratioH[i];
    }
    return nucl_err_res;
  }

  /// calls the AlterBBN routine nucl_err with the filled relicparam structure. This will fill the array ratioH with
  /// all computed element abundances, but without their errors & covariances
  int call_nucl(map_str_dbl &AlterBBN_input, double *ratioH)
  {
    AlterBBN_2_2::relicparam input_relicparam;
    Init_cosmomodel(&input_relicparam); // initialise values of relicparam structure to their defaults
    fill_cosmomodel(&input_relicparam, AlterBBN_input); // fill strucutre with values contained in AlerBBN_input map which is filled in CosmoBit.ccp for different models
    return !nucl(&input_relicparam, ratioH); // nucl returns 1 if there is an error and 0 otherwise, the opposite of nucl_err, so negate the return value
  }

  /// return the NNUC -- global parameter of AlterBBN specifying the number of
  /// elements for which abundances are calculated -> length of array ratioH is NNUC+1 (AlterBBN
  /// starts filling @ position 1)
  size_t get_NNUC() { return NNUC; }

  /// create a map that translates element name to position of element in ratioH vector
  /// (holding the computed element abundances)
  /// BE convinience function just in case it changes with a different version of AlterBBN
  map_str_int get_abund_map_AlterBBN()
  { return {{"H2",3},{"D",3},{"H3",4},{"He3",5},{"He4",6},{"Yp",6},{"Li6",7},{"Li7",8},{"Be7",9},{"Li8",10}}; }

}
END_BE_NAMESPACE
