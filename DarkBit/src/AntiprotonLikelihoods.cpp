//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Likelihood for 7-year antiproton data from AMS-02
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Sowmiya Balan 
///          (sowmiya.balan@kit.edu)
///  \date 2022 June
///  
///
///  *********************************************

#include <iostream>
#include <fstream>
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/DarkBit/DarkBit_rollcall.hpp"
#include "gambit/Utils/util_functions.hpp"

#include <boost/multi_array.hpp>

namespace Gambit
{
  namespace DarkBit
  {
    void lnL_pbarAMS02 (map_str_dbl& result)
    {
      using namespace Pipes::lnL_pbarAMS02;
      LocalMaxwellianHalo LocalHaloParameters = *Dep::LocalHalo;
      double rho0 = LocalHaloParameters.rho0;     
      double rho0_eff = (*Dep::RD_fraction)*rho0/0.43;
      std::string DM_ID = Dep::WIMP_properties->name;
      std::string DMbar_ID = Dep::WIMP_properties->conjugate;
      double DM_mass = Dep::WIMP_properties->mass;
      TH_Process process = Dep::TH_ProcessCatalog->getProcess(DM_ID, DMbar_ID);
      map_str_dbl input;
      double sv=0;
      std::vector<std::string> fs;
      std::string finalStates;
      double rate=0;
      for (std::vector<TH_Channel>::iterator it = process.channelList.begin(); it!=process.channelList.end();it++)
      { 
        fs = it->finalStateIDs;
        finalStates = fs[0] + " " + fs[1];
        rate = it->genRate->bind("v")->eval(0.);
        rate = rate * rho0_eff * rho0_eff;
        input.insert({finalStates, rate});
        sv += rate;
      }  
      result = BEreq::drn_pbar_logLikes(DM_mass, input, sv);
    } 

    void lnL_pbarAMS02_uncorr (double& result)
    {
      using namespace Pipes::lnL_pbarAMS02_uncorr;
      map_str_dbl del_chi2 = *Dep::pbar_logLikes;
      result = del_chi2["uncorrelated"];
    }

    void lnL_pbarAMS02_corr (double& result)
    {
      using namespace Pipes::lnL_pbarAMS02_corr;
      map_str_dbl del_chi2 = *Dep::pbar_logLikes;
      result = del_chi2["correlated"];
    }
  } 
} 
