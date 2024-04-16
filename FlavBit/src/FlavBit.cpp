//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module FlavBit
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Nazila Mahmoudi
///  \date 2013 Oct
///  \date 2014
///  \date 2015 Feb
///  \date 2016 Jul
///  \date 2018 Jan
///  \date 2019 Aug
///
///  \author Marcin Chrzaszcz
///  \date 2015 May
///  \date 2015 July
///  \date 2015 August
///  \date 2016 July
///  \date 2016 August
///  \date 2016 October
///  \date 2018 Jan
///  \date 2020 Jan
///  \date 2020 Feb
///  \date 2020 May
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2013 Nov
///
///  \author Pat Scott
///          (pat.scott@uq.edu.au)
///  \date 2015 May, June
///  \date 2016 Aug
///  \date 2017 March
///  \date 2019 Oct
///  \date 2020 Feb
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 July
///
///  \author Jihyun Bhom
///          (jihyun.bhom@ifj.edu.pl)
///  \date 2019 July
///  \date 2019 Nov
///  \date 2019 Dec
///  \date 2020 Jan
///  \date 2020 Feb
///
///  \author Markus Prim
///          (markus.prim@kit.edu)
///  \date 2019 Aug
///  \date 2019 Nov
///  \date 2020 Jan
///
///  *********************************************

#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/FlavBit_types.hpp"
#include "gambit/FlavBit/Flav_reader.hpp"
#include "gambit/FlavBit/flav_utils.hpp"
#include "gambit/FlavBit/flav_loop_functions.hpp"
#include "gambit/Elements/translator.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/cmake/cmake_variables.hpp"


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

    namespace ublas = boost::numeric::ublas;

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

    /// FlavBit observable name translator
    Utils::translator translate_flav_obs(GAMBIT_DIR "/FlavBit/data/observables_key.yaml");

    /// Some constants used in SuperIso likelihoods
    const int ncorrnuis = 463;
    const nuiscorr (&nuiscorr_help(nuiscorr (&arr)[ncorrnuis], const std::vector<nuiscorr>& v))[ncorrnuis] { std::copy(v.begin(), v.end(), arr); return arr; }
    nuiscorr arr[ncorrnuis];
    const nuiscorr (&corrnuis)[ncorrnuis] = nuiscorr_help(arr, YAML::LoadFile(GAMBIT_DIR "/FlavBit/data/SM_nuisance_correlations.yaml")["correlation_matrix"].as<std::vector<nuiscorr>>());

    /// Print function for FlavBit predictions
    void print(flav_prediction prediction , std::vector<std::string > names)
    {
      for(unsigned i=0; i<names.size(); i++)
      {
        std::cout<<names[i]<<": "<<prediction.central_values[names[i]]<< std::endl;
      }
      std::cout<<"Covariance:"<< std::endl;
      for( unsigned i=0; i<names.size(); i++)
      {
        std::stringstream row;
        for( unsigned j=0; j<names.size(); j++)
        {
          row<<(prediction.covariance)[names[i]]  [names[j]]<<" ";
        }
        std::cout<<row.str()<< std::endl;
      }
    }

    /// Translate B->K*ll observables from theory to LHCb convention
    void Kstarll_Theory2Experiment_translation(flav_observable_map& prediction, int generation)
    {
      // Only works for ll = ee and ll = mumu
      if (generation < 1 or generation > 2)
       FlavBit_error().raise(LOCAL_INFO, "Kstarll_Theory2Experiment_translation called with generation not 1 or 2");
      const std::vector<std::string> all_names[2] = {{"AT_Im"} , {"S4", "S7", "S9"}};
      const std::vector<std::string>& names = all_names[generation-1];
      for (unsigned i=0; i < names.size(); i++)
      {
        auto search = prediction.find(names[i]);
        if (search != prediction.end())
        {
          prediction[names[i]]=(-1.)*prediction[names[i]];
        }
      }
    }

    /// Translate B->K*ll covariances from theory to LHCb convention
    void Kstarll_Theory2Experiment_translation(flav_covariance_map& prediction, int generation)
    {
      // Only works for ll = ee and ll = mumu
      if (generation < 1 or generation > 2)
       FlavBit_error().raise(LOCAL_INFO, "Kstarll_Theory2Experiment_translation called with generation not 1 or 2");

      const std::vector<std::string> names[2] = {{"AT_Im"} , {"S4", "S7", "S9"}};
      std::vector<std::string> names_exist;

      for (unsigned i=0; i < names[generation-1].size(); i++)
      {
        auto search_i = prediction.find(names[generation-1][i]);
        if (search_i != prediction.end()) names_exist.push_back(names[generation-1][i]);
      }
      //changing the rows:
      for (unsigned i=0; i <  names_exist.size(); i++)
      {
        std::string name1=names_exist[i];
        std::map<const std::string, double> row=prediction[name1];
        for (std::map<const std::string, double>::iterator it=row.begin(); it !=row.end(); it++)
        {
          prediction[name1][it->first]=(-1.)*prediction[name1][it->first];
        }
      }
      // changing the columns:
      for (flav_covariance_map::iterator it=prediction.begin(); it !=prediction.end(); it++)
      {
        std::string name_columns=it->first;
        for (unsigned i=0; i <  names_exist.size(); i++)
        {
          std::string name1=names_exist[i];
          prediction[name_columns][name1]=(-1)*prediction[name_columns][name1];
        }
      }
    }

    /// Find the path to the latest installed version of the HepLike data
    str path_to_latest_heplike_data()
    {
      std::vector<str> working_data = Backends::backendInfo().working_versions("HepLikeData");
      if (working_data.empty()) FlavBit_error().raise(LOCAL_INFO, "No working HepLikeData installations detected.");
      std::sort(working_data.begin(), working_data.end());
      return Backends::backendInfo().corrected_path("HepLikeData", working_data.back());
    }

    /// Fill SuperIso model info structure
    void SuperIso_fill(parameters &result)
    {
      using namespace Pipes::SuperIso_fill;

      SLHAstruct spectrum;
      // Obtain SLHAea object from spectrum
      if (ModelInUse("WC")  || ModelInUse("WC_LR") || ModelInUse("WC_LUV") )
      {
        spectrum = Dep::SM_spectrum->getSLHAea(2);
      }
      else if (ModelInUse("MSSM63atMGUT") or ModelInUse("MSSM63atQ"))
      {
        spectrum = Dep::MSSM_spectrum->getSLHAea(2);
        // Add the MODSEL block if it is not provided by the spectrum object.
        SLHAea_add(spectrum,"MODSEL",1, 0, "General MSSM", false);
      }
      else
      {
        FlavBit_error().raise(LOCAL_INFO, "Unrecognised model.");
      }

      BEreq::Init_param(&result);

      int ie,je;

      result.model=-1;
      if (!spectrum["MODSEL"].empty())
      {
        if (spectrum["MODSEL"][1].is_data_line()) result.model=SLHAea::to<int>(spectrum["MODSEL"][1][1]);
        if (spectrum["MODSEL"][3].is_data_line()) result.NMSSM=SLHAea::to<int>(spectrum["MODSEL"][3][1]);
        if (spectrum["MODSEL"][4].is_data_line()) result.RV=SLHAea::to<int>(spectrum["MODSEL"][4][1]);
        if (spectrum["MODSEL"][5].is_data_line()) result.CPV=SLHAea::to<int>(spectrum["MODSEL"][5][1]);
        if (spectrum["MODSEL"][6].is_data_line()) result.FV=SLHAea::to<int>(spectrum["MODSEL"][6][1]);
        if (spectrum["MODSEL"][12].is_data_line()) result.Q=SLHAea::to<double>(spectrum["MODSEL"][12][1]);
      }

      if (result.NMSSM != 0) result.model=result.NMSSM;
      if (result.RV != 0) result.model=-2;
      if (result.CPV != 0) result.model=-2;

      if (!spectrum["SMINPUTS"].empty())
      {
        if (spectrum["SMINPUTS"][1].is_data_line()) result.inv_alpha_em=SLHAea::to<double>(spectrum["SMINPUTS"][1][1]);
        if (spectrum["SMINPUTS"][2].is_data_line()) result.Gfermi=SLHAea::to<double>(spectrum["SMINPUTS"][2][1]);
        if (spectrum["SMINPUTS"][3].is_data_line()) result.alphas_MZ=SLHAea::to<double>(spectrum["SMINPUTS"][3][1]);
        if (spectrum["SMINPUTS"][4].is_data_line()) result.mass_Z=SLHAea::to<double>(spectrum["SMINPUTS"][4][1]);
        if (spectrum["SMINPUTS"][5].is_data_line()) result.mass_b=SLHAea::to<double>(spectrum["SMINPUTS"][5][1]);
        if (spectrum["SMINPUTS"][6].is_data_line()) result.mass_top_pole=SLHAea::to<double>(spectrum["SMINPUTS"][6][1]);
        if (spectrum["SMINPUTS"][7].is_data_line()) result.mass_tau_pole=SLHAea::to<double>(spectrum["SMINPUTS"][7][1]);
        if (spectrum["SMINPUTS"][8].is_data_line()) result.mass_nut=SLHAea::to<double>(spectrum["SMINPUTS"][8][1]);
        if (spectrum["SMINPUTS"][11].is_data_line()) result.mass_e=SLHAea::to<double>(spectrum["SMINPUTS"][11][1]);
        if (spectrum["SMINPUTS"][12].is_data_line()) result.mass_nue=SLHAea::to<double>(spectrum["SMINPUTS"][12][1]);
        if (spectrum["SMINPUTS"][13].is_data_line()) result.mass_mu=SLHAea::to<double>(spectrum["SMINPUTS"][13][1]);
        if (spectrum["SMINPUTS"][14].is_data_line()) result.mass_num=SLHAea::to<double>(spectrum["SMINPUTS"][14][1]);
        if (spectrum["SMINPUTS"][21].is_data_line()) result.mass_d=SLHAea::to<double>(spectrum["SMINPUTS"][21][1]);
        if (spectrum["SMINPUTS"][22].is_data_line()) result.mass_u=SLHAea::to<double>(spectrum["SMINPUTS"][22][1]);
        if (spectrum["SMINPUTS"][23].is_data_line()) result.mass_s=SLHAea::to<double>(spectrum["SMINPUTS"][23][1]);
        if (spectrum["SMINPUTS"][24].is_data_line()) result.mass_c=SLHAea::to<double>(spectrum["SMINPUTS"][24][1]);result.scheme_c_mass=1;
      }

      if (!spectrum["VCKMIN"].empty())
      {
        if (spectrum["VCKMIN"][1].is_data_line()) result.CKM_lambda=SLHAea::to<double>(spectrum["VCKMIN"][1][1]);
        if (spectrum["VCKMIN"][2].is_data_line()) result.CKM_A=SLHAea::to<double>(spectrum["VCKMIN"][2][1]);
        if (spectrum["VCKMIN"][3].is_data_line()) result.CKM_rhobar=SLHAea::to<double>(spectrum["VCKMIN"][3][1]);
        if (spectrum["VCKMIN"][4].is_data_line()) result.CKM_etabar=SLHAea::to<double>(spectrum["VCKMIN"][4][1]);
      }

      if (!spectrum["UPMNSIN"].empty())
      {
        if (spectrum["UPMNSIN"][1].is_data_line()) result.PMNS_theta12=SLHAea::to<double>(spectrum["UPMNSIN"][1][1]);
        if (spectrum["UPMNSIN"][2].is_data_line()) result.PMNS_theta23=SLHAea::to<double>(spectrum["UPMNSIN"][2][1]);
        if (spectrum["UPMNSIN"][3].is_data_line()) result.PMNS_theta13=SLHAea::to<double>(spectrum["UPMNSIN"][3][1]);
        if (spectrum["UPMNSIN"][4].is_data_line()) result.PMNS_delta13=SLHAea::to<double>(spectrum["UPMNSIN"][4][1]);
        if (spectrum["UPMNSIN"][5].is_data_line()) result.PMNS_alpha1=SLHAea::to<double>(spectrum["UPMNSIN"][5][1]);
        if (spectrum["UPMNSIN"][6].is_data_line()) result.PMNS_alpha2=SLHAea::to<double>(spectrum["UPMNSIN"][6][1]);
      }

      if (!spectrum["MINPAR"].empty())
      {
        if (spectrum["MINPAR"][3].is_data_line()) result.tan_beta=SLHAea::to<double>(spectrum["MINPAR"][3][1]);
        switch(result.model)
        {
          case 1:
            if (spectrum["MINPAR"][1].is_data_line()) result.m0=SLHAea::to<double>(spectrum["MINPAR"][1][1]);
            if (spectrum["MINPAR"][2].is_data_line()) result.m12=SLHAea::to<double>(spectrum["MINPAR"][2][1]);
            if (spectrum["MINPAR"][4].is_data_line()) result.sign_mu=SLHAea::to<double>(spectrum["MINPAR"][4][1]);
            if (spectrum["MINPAR"][5].is_data_line()) result.A0=SLHAea::to<double>(spectrum["MINPAR"][5][1]);
            break;

          case 2:
            if (spectrum["MINPAR"][1].is_data_line()) result.Lambda=SLHAea::to<double>(spectrum["MINPAR"][1][1]);
            if (spectrum["MINPAR"][2].is_data_line()) result.Mmess=SLHAea::to<double>(spectrum["MINPAR"][2][1]);
            if (spectrum["MINPAR"][4].is_data_line()) result.sign_mu=SLHAea::to<double>(spectrum["MINPAR"][4][1]);
            if (spectrum["MINPAR"][5].is_data_line()) result.N5=SLHAea::to<double>(spectrum["MINPAR"][5][1]);
            if (spectrum["MINPAR"][6].is_data_line()) result.cgrav=SLHAea::to<double>(spectrum["MINPAR"][6][1]);
            break;

          case 3:
            if (spectrum["MINPAR"][1].is_data_line()) result.m32=SLHAea::to<double>(spectrum["MINPAR"][1][1]);
            if (spectrum["MINPAR"][2].is_data_line()) result.m0=SLHAea::to<double>(spectrum["MINPAR"][2][1]);
            if (spectrum["MINPAR"][4].is_data_line()) result.sign_mu=SLHAea::to<double>(spectrum["MINPAR"][4][1]);
            break;

          default:
            if (spectrum["MINPAR"][3].is_data_line()) result.tan_beta=SLHAea::to<double>(spectrum["MINPAR"][3][1]);
        }
      }

      if (!spectrum["EXTPAR"].empty())
      {
        if (spectrum["EXTPAR"][0].is_data_line()) result.Min=SLHAea::to<double>(spectrum["EXTPAR"][0][1]);
        if (spectrum["EXTPAR"][1].is_data_line()) result.M1_Min=SLHAea::to<double>(spectrum["EXTPAR"][1][1]);
        if (spectrum["EXTPAR"][2].is_data_line()) result.M2_Min=SLHAea::to<double>(spectrum["EXTPAR"][2][1]);
        if (spectrum["EXTPAR"][3].is_data_line()) result.M3_Min=SLHAea::to<double>(spectrum["EXTPAR"][3][1]);
        if (spectrum["EXTPAR"][11].is_data_line()) result.At_Min=SLHAea::to<double>(spectrum["EXTPAR"][11][1]);
        if (spectrum["EXTPAR"][12].is_data_line()) result.Ab_Min=SLHAea::to<double>(spectrum["EXTPAR"][12][1]);
        if (spectrum["EXTPAR"][13].is_data_line()) result.Atau_Min=SLHAea::to<double>(spectrum["EXTPAR"][13][1]);
        if (spectrum["EXTPAR"][21].is_data_line()) result.M2H1_Min=SLHAea::to<double>(spectrum["EXTPAR"][21][1]);
        if (spectrum["EXTPAR"][22].is_data_line()) result.M2H2_Min=SLHAea::to<double>(spectrum["EXTPAR"][22][1]);
        if (spectrum["EXTPAR"][23].is_data_line()) result.mu_Min=SLHAea::to<double>(spectrum["EXTPAR"][23][1]);
        if (spectrum["EXTPAR"][24].is_data_line()) result.M2A_Min=SLHAea::to<double>(spectrum["EXTPAR"][24][1]);
        if (spectrum["EXTPAR"][25].is_data_line()) result.tb_Min=SLHAea::to<double>(spectrum["EXTPAR"][25][1]);
        if (spectrum["EXTPAR"][26].is_data_line()) result.mA_Min=SLHAea::to<double>(spectrum["EXTPAR"][26][1]);
        if (spectrum["EXTPAR"][31].is_data_line()) result.MeL_Min=SLHAea::to<double>(spectrum["EXTPAR"][31][1]);
        if (spectrum["EXTPAR"][32].is_data_line()) result.MmuL_Min=SLHAea::to<double>(spectrum["EXTPAR"][32][1]);
        if (spectrum["EXTPAR"][33].is_data_line()) result.MtauL_Min=SLHAea::to<double>(spectrum["EXTPAR"][33][1]);
        if (spectrum["EXTPAR"][34].is_data_line()) result.MeR_Min=SLHAea::to<double>(spectrum["EXTPAR"][34][1]);
        if (spectrum["EXTPAR"][35].is_data_line()) result.MmuR_Min=SLHAea::to<double>(spectrum["EXTPAR"][35][1]);
        if (spectrum["EXTPAR"][36].is_data_line()) result.MtauR_Min=SLHAea::to<double>(spectrum["EXTPAR"][36][1]);
        if (spectrum["EXTPAR"][41].is_data_line()) result.MqL1_Min=SLHAea::to<double>(spectrum["EXTPAR"][41][1]);
        if (spectrum["EXTPAR"][42].is_data_line()) result.MqL2_Min=SLHAea::to<double>(spectrum["EXTPAR"][42][1]);
        if (spectrum["EXTPAR"][43].is_data_line()) result.MqL3_Min=SLHAea::to<double>(spectrum["EXTPAR"][43][1]);
        if (spectrum["EXTPAR"][44].is_data_line()) result.MuR_Min=SLHAea::to<double>(spectrum["EXTPAR"][44][1]);
        if (spectrum["EXTPAR"][45].is_data_line()) result.McR_Min=SLHAea::to<double>(spectrum["EXTPAR"][45][1]);
        if (spectrum["EXTPAR"][46].is_data_line()) result.MtR_Min=SLHAea::to<double>(spectrum["EXTPAR"][46][1]);
        if (spectrum["EXTPAR"][47].is_data_line()) result.MdR_Min=SLHAea::to<double>(spectrum["EXTPAR"][47][1]);
        if (spectrum["EXTPAR"][48].is_data_line()) result.MsR_Min=SLHAea::to<double>(spectrum["EXTPAR"][48][1]);
        if (spectrum["EXTPAR"][49].is_data_line()) result.MbR_Min=SLHAea::to<double>(spectrum["EXTPAR"][49][1]);
        if (spectrum["EXTPAR"][51].is_data_line()) result.N51=SLHAea::to<double>(spectrum["EXTPAR"][51][1]);
        if (spectrum["EXTPAR"][52].is_data_line()) result.N52=SLHAea::to<double>(spectrum["EXTPAR"][52][1]);
        if (spectrum["EXTPAR"][53].is_data_line()) result.N53=SLHAea::to<double>(spectrum["EXTPAR"][53][1]);
        if (spectrum["EXTPAR"][61].is_data_line()) result.lambdaNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][61][1]);
        if (spectrum["EXTPAR"][62].is_data_line()) result.kappaNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][62][1]);
        if (spectrum["EXTPAR"][63].is_data_line()) result.AlambdaNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][63][1]);
        if (spectrum["EXTPAR"][64].is_data_line()) result.AkappaNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][64][1]);
        if (spectrum["EXTPAR"][65].is_data_line()) result.lambdaSNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][65][1]);
        if (spectrum["EXTPAR"][66].is_data_line()) result.xiFNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][66][1]);
        if (spectrum["EXTPAR"][67].is_data_line()) result.xiSNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][67][1]);
        if (spectrum["EXTPAR"][68].is_data_line()) result.mupNMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][68][1]);
        if (spectrum["EXTPAR"][69].is_data_line()) result.mSp2NMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][69][1]);
        if (spectrum["EXTPAR"][70].is_data_line()) result.mS2NMSSM_Min=SLHAea::to<double>(spectrum["EXTPAR"][70][1]);
      }

      if (!spectrum["MASS"].empty())
      {
        if (spectrum["MASS"][1].is_data_line()) result.mass_d=SLHAea::to<double>(spectrum["MASS"][1][1]);
        if (spectrum["MASS"][2].is_data_line()) result.mass_u=SLHAea::to<double>(spectrum["MASS"][2][1]);
        if (spectrum["MASS"][3].is_data_line()) result.mass_s=SLHAea::to<double>(spectrum["MASS"][3][1]);
        if (spectrum["MASS"][4].is_data_line()) result.mass_c_pole=SLHAea::to<double>(spectrum["MASS"][4][1]);
        if (spectrum["MASS"][6].is_data_line()) result.mass_t=SLHAea::to<double>(spectrum["MASS"][6][1]);
        if (spectrum["MASS"][11].is_data_line()) result.mass_e=SLHAea::to<double>(spectrum["MASS"][11][1]);
        if (spectrum["MASS"][12].is_data_line()) result.mass_nue=SLHAea::to<double>(spectrum["MASS"][12][1]);
        if (spectrum["MASS"][13].is_data_line()) result.mass_mu=SLHAea::to<double>(spectrum["MASS"][13][1]);
        if (spectrum["MASS"][14].is_data_line()) result.mass_num=SLHAea::to<double>(spectrum["MASS"][14][1]);
        if (spectrum["MASS"][15].is_data_line()) result.mass_tau=result.mass_tau_pole=SLHAea::to<double>(spectrum["MASS"][15][1]);
        if (spectrum["MASS"][16].is_data_line()) result.mass_nut=SLHAea::to<double>(spectrum["MASS"][16][1]);
        if (spectrum["MASS"][21].is_data_line()) result.mass_gluon=SLHAea::to<double>(spectrum["MASS"][21][1]);
        if (spectrum["MASS"][22].is_data_line()) result.mass_photon=SLHAea::to<double>(spectrum["MASS"][22][1]);
        if (spectrum["MASS"][23].is_data_line()) result.mass_Z0=SLHAea::to<double>(spectrum["MASS"][23][1]);
        if (spectrum["MASS"][24].is_data_line()) result.mass_W=SLHAea::to<double>(spectrum["MASS"][24][1]);
        if (spectrum["MASS"][25].is_data_line()) result.mass_h0=SLHAea::to<double>(spectrum["MASS"][25][1]);
        if (spectrum["MASS"][35].is_data_line()) result.mass_H0=SLHAea::to<double>(spectrum["MASS"][35][1]);
        if (spectrum["MASS"][36].is_data_line()) result.mass_A0=SLHAea::to<double>(spectrum["MASS"][36][1]);
        if (spectrum["MASS"][37].is_data_line()) result.mass_H=SLHAea::to<double>(spectrum["MASS"][37][1]);
        if (spectrum["MASS"][39].is_data_line()) result.mass_graviton=SLHAea::to<double>(spectrum["MASS"][39][1]);
        if (spectrum["MASS"][45].is_data_line()) result.mass_H03=SLHAea::to<double>(spectrum["MASS"][45][1]);
        if (spectrum["MASS"][46].is_data_line()) result.mass_A02=SLHAea::to<double>(spectrum["MASS"][46][1]);
        if (spectrum["MASS"][1000001].is_data_line()) result.mass_dnl=SLHAea::to<double>(spectrum["MASS"][1000001][1]);
        if (spectrum["MASS"][1000002].is_data_line()) result.mass_upl=SLHAea::to<double>(spectrum["MASS"][1000002][1]);
        if (spectrum["MASS"][1000003].is_data_line()) result.mass_stl=SLHAea::to<double>(spectrum["MASS"][1000003][1]);
        if (spectrum["MASS"][1000004].is_data_line()) result.mass_chl=SLHAea::to<double>(spectrum["MASS"][1000004][1]);
        if (spectrum["MASS"][1000005].is_data_line()) result.mass_b1=SLHAea::to<double>(spectrum["MASS"][1000005][1]);
        if (spectrum["MASS"][1000006].is_data_line()) result.mass_t1=SLHAea::to<double>(spectrum["MASS"][1000006][1]);
        if (spectrum["MASS"][1000011].is_data_line()) result.mass_el=SLHAea::to<double>(spectrum["MASS"][1000011][1]);
        if (spectrum["MASS"][1000012].is_data_line()) result.mass_nuel=SLHAea::to<double>(spectrum["MASS"][1000012][1]);
        if (spectrum["MASS"][1000013].is_data_line()) result.mass_mul=SLHAea::to<double>(spectrum["MASS"][1000013][1]);
        if (spectrum["MASS"][1000014].is_data_line()) result.mass_numl=SLHAea::to<double>(spectrum["MASS"][1000014][1]);
        if (spectrum["MASS"][1000015].is_data_line()) result.mass_tau1=SLHAea::to<double>(spectrum["MASS"][1000015][1]);
        if (spectrum["MASS"][1000016].is_data_line()) result.mass_nutl=SLHAea::to<double>(spectrum["MASS"][1000016][1]);
        if (spectrum["MASS"][1000021].is_data_line()) result.mass_gluino=SLHAea::to<double>(spectrum["MASS"][1000021][1]);
        if (spectrum["MASS"][1000022].is_data_line()) result.mass_neut[1]=SLHAea::to<double>(spectrum["MASS"][1000022][1]);
        if (spectrum["MASS"][1000023].is_data_line()) result.mass_neut[2]=SLHAea::to<double>(spectrum["MASS"][1000023][1]);
        if (spectrum["MASS"][1000024].is_data_line()) result.mass_cha1=SLHAea::to<double>(spectrum["MASS"][1000024][1]);
        if (spectrum["MASS"][1000025].is_data_line()) result.mass_neut[3]=SLHAea::to<double>(spectrum["MASS"][1000025][1]);
        if (spectrum["MASS"][1000035].is_data_line()) result.mass_neut[4]=SLHAea::to<double>(spectrum["MASS"][1000035][1]);
        if (spectrum["MASS"][1000037].is_data_line()) result.mass_cha2=SLHAea::to<double>(spectrum["MASS"][1000037][1]);
        if (spectrum["MASS"][1000039].is_data_line()) result.mass_gravitino=SLHAea::to<double>(spectrum["MASS"][1000039][1]);
        if (spectrum["MASS"][1000045].is_data_line()) result.mass_neut[5]=SLHAea::to<double>(spectrum["MASS"][1000045][1]);
        if (spectrum["MASS"][2000001].is_data_line()) result.mass_dnr=SLHAea::to<double>(spectrum["MASS"][2000001][1]);
        if (spectrum["MASS"][2000002].is_data_line()) result.mass_upr=SLHAea::to<double>(spectrum["MASS"][2000002][1]);
        if (spectrum["MASS"][2000003].is_data_line()) result.mass_str=SLHAea::to<double>(spectrum["MASS"][2000003][1]);
        if (spectrum["MASS"][2000004].is_data_line()) result.mass_chr=SLHAea::to<double>(spectrum["MASS"][2000004][1]);
        if (spectrum["MASS"][2000005].is_data_line()) result.mass_b2=SLHAea::to<double>(spectrum["MASS"][2000005][1]);
        if (spectrum["MASS"][2000006].is_data_line()) result.mass_t2=SLHAea::to<double>(spectrum["MASS"][2000006][1]);
        if (spectrum["MASS"][2000011].is_data_line()) result.mass_er=SLHAea::to<double>(spectrum["MASS"][2000011][1]);
        if (spectrum["MASS"][2000012].is_data_line()) result.mass_nuer=SLHAea::to<double>(spectrum["MASS"][2000012][1]);
        if (spectrum["MASS"][2000013].is_data_line()) result.mass_mur=SLHAea::to<double>(spectrum["MASS"][2000013][1]);
        if (spectrum["MASS"][2000014].is_data_line()) result.mass_numr=SLHAea::to<double>(spectrum["MASS"][2000014][1]);
        if (spectrum["MASS"][2000015].is_data_line()) result.mass_tau2=SLHAea::to<double>(spectrum["MASS"][2000015][1]);
        if (spectrum["MASS"][2000016].is_data_line()) result.mass_nutr=SLHAea::to<double>(spectrum["MASS"][2000016][1]);
      }

      // The following blocks will only appear for SUSY models so let's not waste time checking them if we're not scanning one of those.
      if (ModelInUse("MSSM63atMGUT") or ModelInUse("MSSM63atQ"))
      {
        // The scale doesn't come through in MODSEL with all spectrum generators
        result.Q = Dep::MSSM_spectrum->get_HE().GetScale();

        if (!spectrum["ALPHA"].empty()) if (spectrum["ALPHA"].back().is_data_line()) result.alpha=SLHAea::to<double>(spectrum["ALPHA"].back().at(0));

        if (!spectrum["STOPMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["STOPMIX"][std::max(ie,je)].is_data_line()) result.stop_mix[ie][je]=SLHAea::to<double>(spectrum["STOPMIX"].at(ie,je)[2]);
        if (!spectrum["SBOTMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["SBOTMIX"][std::max(ie,je)].is_data_line()) result.sbot_mix[ie][je]=SLHAea::to<double>(spectrum["SBOTMIX"].at(ie,je)[2]);
        if (!spectrum["STAUMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["STAUMIX"][std::max(ie,je)].is_data_line()) result.stau_mix[ie][je]=SLHAea::to<double>(spectrum["STAUMIX"].at(ie,je)[2]);
        if (!spectrum["NMIX"].empty()) for (ie=1;ie<=4;ie++) for (je=1;je<=4;je++)
         if (spectrum["NMIX"][std::max(ie,je)].is_data_line()) result.neut_mix[ie][je]=SLHAea::to<double>(spectrum["NMIX"].at(ie,je)[2]);
        if (!spectrum["NMNMIX"].empty()) for (ie=1;ie<=5;ie++) for (je=1;je<=5;je++)
         if (spectrum["NMNMIX"][std::max(ie,je)].is_data_line()) result.neut_mix[ie][je]=SLHAea::to<double>(spectrum["NMNMIX"].at(ie,je)[2]);
        if (!spectrum["UMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["UMIX"][std::max(ie,je)].is_data_line()) result.charg_Umix[ie][je]=SLHAea::to<double>(spectrum["UMIX"].at(ie,je)[2]);
        if (!spectrum["VMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["VMIX"][std::max(ie,je)].is_data_line()) result.charg_Vmix[ie][je]=SLHAea::to<double>(spectrum["VMIX"].at(ie,je)[2]);

        if (!spectrum["GAUGE"].empty())
        {
          if (spectrum["GAUGE"][1].is_data_line()) result.gp_Q=SLHAea::to<double>(spectrum["GAUGE"][1][1]);
          if (spectrum["GAUGE"][2].is_data_line()) result.g2_Q=SLHAea::to<double>(spectrum["GAUGE"][2][1]);
          if (spectrum["GAUGE"][3].is_data_line()) result.g3_Q=SLHAea::to<double>(spectrum["GAUGE"][3][1]);
        }

        if (!spectrum["YU"].empty()) for (ie=1;ie<=3;ie++) if (spectrum["YU"][ie].is_data_line()) result.yut[ie]=SLHAea::to<double>(spectrum["YU"].at(ie,ie)[2]);
        if (!spectrum["YD"].empty()) for (ie=1;ie<=3;ie++) if (spectrum["YD"][ie].is_data_line()) result.yub[ie]=SLHAea::to<double>(spectrum["YD"].at(ie,ie)[2]);
        if (!spectrum["YE"].empty()) for (ie=1;ie<=3;ie++) if (spectrum["YE"][ie].is_data_line()) result.yutau[ie]=SLHAea::to<double>(spectrum["YE"].at(ie,ie)[2]);

        if (!spectrum["HMIX"].empty())
        {
          if (spectrum["HMIX"][1].is_data_line()) result.mu_Q=SLHAea::to<double>(spectrum["HMIX"][1][1]);
          if (spectrum["HMIX"][2].is_data_line()) result.tanb_GUT=SLHAea::to<double>(spectrum["HMIX"][2][1]);
          if (spectrum["HMIX"][3].is_data_line()) result.Higgs_VEV=SLHAea::to<double>(spectrum["HMIX"][3][1]);
          if (spectrum["HMIX"][4].is_data_line()) result.mA2_Q=SLHAea::to<double>(spectrum["HMIX"][4][1]);
        }

        if (!spectrum["NMHMIX"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["NMHMIX"][std::max(ie,je)].is_data_line()) result.H0_mix[ie][je]=SLHAea::to<double>(spectrum["NMHMIX"].at(ie,je)[2]);

        if (!spectrum["NMAMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["NMAMIX"][std::max(ie,je)].is_data_line()) result.A0_mix[ie][je]=SLHAea::to<double>(spectrum["NMAMIX"].at(ie,je)[2]);

        if (!spectrum["MSOFT"].empty())
        {
          if (!spectrum["MSOFT"].front().empty()) result.MSOFT_Q=SLHAea::to<double>(spectrum["MSOFT"].front().at(3));
          if (spectrum["MSOFT"][1].is_data_line()) result.M1_Q=SLHAea::to<double>(spectrum["MSOFT"][1][1]);
          if (spectrum["MSOFT"][2].is_data_line()) result.M2_Q=SLHAea::to<double>(spectrum["MSOFT"][2][1]);
          if (spectrum["MSOFT"][3].is_data_line()) result.M3_Q=SLHAea::to<double>(spectrum["MSOFT"][3][1]);
          if (spectrum["MSOFT"][21].is_data_line()) result.M2H1_Q=SLHAea::to<double>(spectrum["MSOFT"][21][1]);
          if (spectrum["MSOFT"][22].is_data_line()) result.M2H2_Q=SLHAea::to<double>(spectrum["MSOFT"][22][1]);
          if (spectrum["MSOFT"][31].is_data_line()) result.MeL_Q=SLHAea::to<double>(spectrum["MSOFT"][31][1]);
          if (spectrum["MSOFT"][32].is_data_line()) result.MmuL_Q=SLHAea::to<double>(spectrum["MSOFT"][32][1]);
          if (spectrum["MSOFT"][33].is_data_line()) result.MtauL_Q=SLHAea::to<double>(spectrum["MSOFT"][33][1]);
          if (spectrum["MSOFT"][34].is_data_line()) result.MeR_Q=SLHAea::to<double>(spectrum["MSOFT"][34][1]);
          if (spectrum["MSOFT"][35].is_data_line()) result.MmuR_Q=SLHAea::to<double>(spectrum["MSOFT"][35][1]);
          if (spectrum["MSOFT"][36].is_data_line()) result.MtauR_Q=SLHAea::to<double>(spectrum["MSOFT"][36][1]);
          if (spectrum["MSOFT"][41].is_data_line()) result.MqL1_Q=SLHAea::to<double>(spectrum["MSOFT"][41][1]);
          if (spectrum["MSOFT"][42].is_data_line()) result.MqL2_Q=SLHAea::to<double>(spectrum["MSOFT"][42][1]);
          if (spectrum["MSOFT"][43].is_data_line()) result.MqL3_Q=SLHAea::to<double>(spectrum["MSOFT"][43][1]);
          if (spectrum["MSOFT"][44].is_data_line()) result.MuR_Q=SLHAea::to<double>(spectrum["MSOFT"][44][1]);
          if (spectrum["MSOFT"][45].is_data_line()) result.McR_Q=SLHAea::to<double>(spectrum["MSOFT"][45][1]);
          if (spectrum["MSOFT"][46].is_data_line()) result.MtR_Q=SLHAea::to<double>(spectrum["MSOFT"][46][1]);
          if (spectrum["MSOFT"][47].is_data_line()) result.MdR_Q=SLHAea::to<double>(spectrum["MSOFT"][47][1]);
          if (spectrum["MSOFT"][48].is_data_line()) result.MsR_Q=SLHAea::to<double>(spectrum["MSOFT"][48][1]);
          if (spectrum["MSOFT"][49].is_data_line()) result.MbR_Q=SLHAea::to<double>(spectrum["MSOFT"][49][1]);
        }

        if (!spectrum["AU"].empty())
        {
          if (spectrum["AU"][1].is_data_line()) result.A_u=SLHAea::to<double>(spectrum["AU"].at(1,1)[2]);
          if (spectrum["AU"][2].is_data_line()) result.A_c=SLHAea::to<double>(spectrum["AU"].at(2,2)[2]);
          if (spectrum["AU"][3].is_data_line()) result.A_t=SLHAea::to<double>(spectrum["AU"].at(3,3)[2]);
        }

        if (!spectrum["AD"].empty())
        {
          if (spectrum["AD"][1].is_data_line()) result.A_d=SLHAea::to<double>(spectrum["AD"].at(1,1)[2]);
          if (spectrum["AD"][2].is_data_line()) result.A_s=SLHAea::to<double>(spectrum["AD"].at(2,2)[2]);
          if (spectrum["AD"][3].is_data_line()) result.A_b=SLHAea::to<double>(spectrum["AD"].at(3,3)[2]);
        }

        if (!spectrum["AE"].empty())
        {
          if (spectrum["AE"][1].is_data_line()) result.A_e=SLHAea::to<double>(spectrum["AE"].at(1,1)[2]);
          if (spectrum["AE"][2].is_data_line()) result.A_mu=SLHAea::to<double>(spectrum["AE"].at(2,2)[2]);
          if (spectrum["AE"][3].is_data_line()) result.A_tau=SLHAea::to<double>(spectrum["AE"].at(3,3)[2]);
        }

        if (!spectrum["NMSSMRUN"].empty())
        {
          if (spectrum["NMSSMRUN"][1].is_data_line()) result.lambdaNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][1][1]);
          if (spectrum["NMSSMRUN"][2].is_data_line()) result.kappaNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][2][1]);
          if (spectrum["NMSSMRUN"][3].is_data_line()) result.AlambdaNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][3][1]);
          if (spectrum["NMSSMRUN"][4].is_data_line()) result.AkappaNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][4][1]);
          if (spectrum["NMSSMRUN"][5].is_data_line()) result.lambdaSNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][5][1]);
          if (spectrum["NMSSMRUN"][6].is_data_line()) result.xiFNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][6][1]);
          if (spectrum["NMSSMRUN"][7].is_data_line()) result.xiSNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][7][1]);
          if (spectrum["NMSSMRUN"][8].is_data_line()) result.mupNMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][8][1]);
          if (spectrum["NMSSMRUN"][9].is_data_line()) result.mSp2NMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][9][1]);
          if (spectrum["NMSSMRUN"][10].is_data_line()) result.mS2NMSSM=SLHAea::to<double>(spectrum["NMSSMRUN"][10][1]);
        }

        if (!spectrum["USQMIX"].empty()) for (ie=1;ie<=6;ie++) for (je=1;je<=6;je++)
         if (spectrum["USQMIX"][std::max(ie,je)].is_data_line()) result.sU_mix[ie][je]=SLHAea::to<double>(spectrum["USQMIX"].at(ie,je)[2]);
        if (!spectrum["DSQMIX"].empty()) for (ie=1;ie<=6;ie++) for (je=1;je<=6;je++)
         if (spectrum["DSQMIX"][std::max(ie,je)].is_data_line()) result.sD_mix[ie][je]=SLHAea::to<double>(spectrum["DSQMIX"].at(ie,je)[2]);
        if (!spectrum["SELMIX"].empty()) for (ie=1;ie<=6;ie++) for (je=1;je<=6;je++)
         if (spectrum["SELMIX"][std::max(ie,je)].is_data_line()) result.sE_mix[ie][je]=SLHAea::to<double>(spectrum["SELMIX"].at(ie,je)[2]);
        if (!spectrum["SNUMIX"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["SNUMIX"][std::max(ie,je)].is_data_line()) result.sNU_mix[ie][je]=SLHAea::to<double>(spectrum["SNUMIX"].at(ie,je)[2]);

        if (!spectrum["MSQ2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSQ2"][std::max(ie,je)].is_data_line()) result.sCKM_msq2[ie][je]=SLHAea::to<double>(spectrum["MSQ2"].at(ie,je)[2]);
        if (!spectrum["MSL2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSL2"][std::max(ie,je)].is_data_line()) result.sCKM_msl2[ie][je]=SLHAea::to<double>(spectrum["MSL2"].at(ie,je)[2]);
        if (!spectrum["MSD2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSD2"][std::max(ie,je)].is_data_line()) result.sCKM_msd2[ie][je]=SLHAea::to<double>(spectrum["MSD2"].at(ie,je)[2]);
        if (!spectrum["MSU2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSU2"][std::max(ie,je)].is_data_line()) result.sCKM_msu2[ie][je]=SLHAea::to<double>(spectrum["MSU2"].at(ie,je)[2]);
        if (!spectrum["MSE2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSE2"][std::max(ie,je)].is_data_line()) result.sCKM_mse2[ie][je]=SLHAea::to<double>(spectrum["MSE2"].at(ie,je)[2]);

        if (!spectrum["IMVCKM"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["IMVCKM"][std::max(ie,je)].is_data_line()) result.IMCKM[ie][je]=SLHAea::to<double>(spectrum["IMVCKM"].at(ie,je)[2]);
        if (!spectrum["IMVCKM"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["IMVCKM"][std::max(ie,je)].is_data_line()) result.IMCKM[ie][je]=SLHAea::to<double>(spectrum["IMVCKM"].at(ie,je)[2]);

        if (!spectrum["UPMNS"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["UPMNS"][std::max(ie,je)].is_data_line()) result.PMNS_U[ie][je]=SLHAea::to<double>(spectrum["UPMNS"].at(ie,je)[2]);

        if (!spectrum["TU"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["TU"][std::max(ie,je)].is_data_line()) result.TU[ie][je]=SLHAea::to<double>(spectrum["TU"].at(ie,je)[2]);
        if (!spectrum["TD"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["TD"][std::max(ie,je)].is_data_line()) result.TD[ie][je]=SLHAea::to<double>(spectrum["TD"].at(ie,je)[2]);
        if (!spectrum["TE"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["TE"][std::max(ie,je)].is_data_line()) result.TE[ie][je]=SLHAea::to<double>(spectrum["TE"].at(ie,je)[2]);
      }

      else if (ModelInUse("WC")  || ModelInUse("WC_LR") || ModelInUse("WC_LUV") )
      {
        // The Higgs mass doesn't come through in the SLHAea object, as that's only for SLHA2 SM inputs.
        result.mass_h0 = Dep::SM_spectrum->get(Par::Pole_Mass, "h0_1");
        // Set the scale.
        result.Q = result.mass_Z;
      }

      if(byVal(result.mass_c_pole)>0.&&byVal(result.scheme_c_mass)<0)
      {
        if(byVal(result.mass_c_pole)<1.5) result.mass_c=BEreq::mcmc_from_pole(byVal(result.mass_c_pole),1,&result);
        else if(byVal(result.mass_c_pole)<1.75) result.mass_c=BEreq::mcmc_from_pole(byVal(result.mass_c_pole),2,&result);
        else result.mass_c=BEreq::mcmc_from_pole(byVal(result.mass_c_pole),3,&result);
      }

      BEreq::slha_adjust(&result);

      // Set the Z and W widths
      result.width_Z = Dep::Z_decay_rates->width_in_GeV;
      result.width_W = Dep::W_plus_decay_rates->width_in_GeV;

      for(int ie=1;ie<=30;ie++) result.deltaC[ie]=result.deltaCp[ie]=0.;
      for(int ie=1;ie<=6;ie++) result.deltaCQ[ie]=result.deltaCQp[ie]=0.;

      // If requested, override the SuperIso b pole mass with the SpecBit value and recompute the 1S b mass.
      if (runOptions->getValueOrDef<bool>(false, "take_b_pole_mass_from_spectrum"))
      {
        if (ModelInUse("MSSM63atMGUT") or ModelInUse("MSSM63atQ"))
        {
          result.mass_h0 = Dep::MSSM_spectrum->get(Par::Pole_Mass, "h0_1");
        }
        else if (ModelInUse("WC") || ModelInUse("WC_LUV") || ModelInUse("WC_LR") )
        {
          result.mass_h0 = Dep::SM_spectrum->get(Par::Pole_Mass, "h0_1");
        }
        result.mass_b_1S = BEreq::mb_1S(&result);
      }

      if (ModelInUse("WC"))
      {

        // Tell SuperIso to do its Wilson coefficient calculations for the SM.
        // We will adjust them with our BSM deviations in backend convenience
        // functions before we send them to SuperIso's observable calculation functions.
        result.SM = 1;

        // So far our model only deals with 5 operators: O_7, O_9, O_10, Q_1 and Q_2.
        result.Re_DeltaC7  = *Param["Re_DeltaC7"];
        result.Im_DeltaC7  = *Param["Im_DeltaC7"];
        result.Re_DeltaC9  = *Param["Re_DeltaC9"];
        result.Im_DeltaC9  = *Param["Im_DeltaC9"];
        result.Re_DeltaC10 = *Param["Re_DeltaC10"];
        result.Im_DeltaC10 = *Param["Im_DeltaC10"];
        result.Re_DeltaCQ1 = *Param["Re_DeltaCQ1"];
        result.Im_DeltaCQ1 = *Param["Im_DeltaCQ1"];
        result.Re_DeltaCQ2 = *Param["Re_DeltaCQ2"];
        result.Im_DeltaCQ2 = *Param["Im_DeltaCQ2"];

        /* Lines below are valid only in the flavour universal case
           deltaC[1..10] = Cmu[1..10], deltaC[11..20] = Ce[1..10], deltaC[21..30] = Ctau[1..10]
           deltaCQ[1,2] = CQmu[1,2], deltaCQ[1,2] = CQe[1,2], deltaCQ[1,2] = CQtau[1,2] */

        result.deltaC[7]=result.deltaC[17]=result.deltaC[27]=std::complex<double>(result.Re_DeltaC7, result.Im_DeltaC7);
        result.deltaC[9]=result.deltaC[19]=result.deltaC[29]=std::complex<double>(result.Re_DeltaC9, result.Im_DeltaC9);
        result.deltaC[10]=result.deltaC[20]=result.deltaC[30]=std::complex<double>(result.Re_DeltaC10, result.Im_DeltaC10);

        result.deltaCQ[1]=result.deltaCQ[3]=result.deltaCQ[5]=std::complex<double>(result.Re_DeltaCQ1, result.Im_DeltaCQ1);
        result.deltaCQ[2]=result.deltaCQ[4]=result.deltaCQ[6]=std::complex<double>(result.Re_DeltaCQ2, result.Im_DeltaCQ2);
      }

      if (ModelInUse("WC_LR"))
      {
        result.SM = 1;

        result.Re_DeltaC7  = *Param["Re_DeltaC7"];
        result.Im_DeltaC7  = *Param["Im_DeltaC7"];
        result.Re_DeltaC9  = *Param["Re_DeltaC9"];
        result.Im_DeltaC9  = *Param["Im_DeltaC9"];
        result.Re_DeltaC10 = *Param["Re_DeltaC10"];
        result.Im_DeltaC10 = *Param["Im_DeltaC10"];
        result.Re_DeltaCQ1 = *Param["Re_DeltaCQ1"];
        result.Im_DeltaCQ1 = *Param["Im_DeltaCQ1"];
        result.Re_DeltaCQ2 = *Param["Re_DeltaCQ2"];
        result.Im_DeltaCQ2 = *Param["Im_DeltaCQ2"];

        result.Re_DeltaC7_Prime  = *Param["Re_DeltaC7_Prime"];
        result.Im_DeltaC7_Prime  = *Param["Im_DeltaC7_Prime"];
        result.Re_DeltaC9_Prime  = *Param["Re_DeltaC9_Prime"];
        result.Im_DeltaC9_Prime  = *Param["Im_DeltaC9_Prime"];
        result.Re_DeltaC10_Prime = *Param["Re_DeltaC10_Prime"];
        result.Im_DeltaC10_Prime = *Param["Im_DeltaC10_Prime"];
        result.Re_DeltaCQ1_Prime = *Param["Re_DeltaCQ1_Prime"];
        result.Im_DeltaCQ1_Prime = *Param["Im_DeltaCQ1_Prime"];
        result.Re_DeltaCQ2_Prime = *Param["Re_DeltaCQ2_Prime"];
        result.Im_DeltaCQ2_Prime = *Param["Im_DeltaCQ2_Prime"];

        // left handed:
        result.deltaC[7]=result.deltaC[17]=result.deltaC[27]=std::complex<double>(result.Re_DeltaC7, result.Im_DeltaC7);
        result.deltaC[9]=result.deltaC[19]=result.deltaC[29]=std::complex<double>(result.Re_DeltaC9, result.Im_DeltaC9);
        result.deltaC[10]=result.deltaC[20]=result.deltaC[30]=std::complex<double>(result.Re_DeltaC10, result.Im_DeltaC10);
        result.deltaCQ[1]=result.deltaCQ[3]=result.deltaCQ[5]=std::complex<double>(result.Re_DeltaCQ1, result.Im_DeltaCQ1);
        result.deltaCQ[2]=result.deltaCQ[4]=result.deltaCQ[6]=std::complex<double>(result.Re_DeltaCQ2, result.Im_DeltaCQ2);

        // right handed:
        result.deltaCp[7]=result.deltaCp[17]=result.deltaCp[27]=std::complex<double>(result.Re_DeltaC7_Prime, result.Im_DeltaC7_Prime);
        result.deltaCp[9]=result.deltaCp[19]=result.deltaCp[29]=std::complex<double>(result.Re_DeltaC9_Prime, result.Im_DeltaC9_Prime);
        result.deltaCp[10]=result.deltaCp[20]=result.deltaCp[30]=std::complex<double>(result.Re_DeltaC10_Prime, result.Im_DeltaC10_Prime);
        result.deltaCQp[1]=result.deltaCQp[3]=result.deltaCQp[5]=std::complex<double>(result.Re_DeltaCQ1_Prime, result.Im_DeltaCQ1_Prime);
        result.deltaCQp[2]=result.deltaCQp[4]=result.deltaCQp[6]=std::complex<double>(result.Re_DeltaCQ2_Prime, result.Im_DeltaCQ2_Prime);
      }

      else if (ModelInUse("WC_LUV"))
      {
        result.SM = 1;

        // So far our model only deals with 5 operators: O_7, O_9, O_10, Q_1 and Q_2.
        result.Re_DeltaC7_mu  = *Param["Re_DeltaC7_mu"];
        result.Im_DeltaC7_mu  = *Param["Im_DeltaC7_mu"];
        result.Re_DeltaC9_mu  = *Param["Re_DeltaC9_mu"];
        result.Im_DeltaC9_mu  = *Param["Im_DeltaC9_mu"];
        result.Re_DeltaC10_mu = *Param["Re_DeltaC10_mu"];
        result.Im_DeltaC10_mu = *Param["Im_DeltaC10_mu"];
        result.Re_DeltaCQ1_mu = *Param["Re_DeltaCQ1_mu"];
        result.Im_DeltaCQ1_mu = *Param["Im_DeltaCQ1_mu"];
        result.Re_DeltaCQ2_mu = *Param["Re_DeltaCQ2_mu"];
        result.Im_DeltaCQ2_mu = *Param["Im_DeltaCQ2_mu"];

        result.Re_DeltaC7_e  = *Param["Re_DeltaC7_e"];
        result.Im_DeltaC7_e  = *Param["Im_DeltaC7_e"];
        result.Re_DeltaC9_e  = *Param["Re_DeltaC9_e"];
        result.Im_DeltaC9_e  = *Param["Im_DeltaC9_e"];
        result.Re_DeltaC10_e = *Param["Re_DeltaC10_e"];
        result.Im_DeltaC10_e = *Param["Im_DeltaC10_e"];
        result.Re_DeltaCQ1_e = *Param["Re_DeltaCQ1_e"];
        result.Im_DeltaCQ1_e = *Param["Im_DeltaCQ1_e"];
        result.Re_DeltaCQ2_e = *Param["Re_DeltaCQ2_e"];
        result.Im_DeltaCQ2_e = *Param["Im_DeltaCQ2_e"];

        result.Re_DeltaC7_tau  = *Param["Re_DeltaC7_tau"];
        result.Im_DeltaC7_tau  = *Param["Im_DeltaC7_tau"];
        result.Re_DeltaC9_tau  = *Param["Re_DeltaC9_tau"];
        result.Im_DeltaC9_tau  = *Param["Im_DeltaC9_tau"];
        result.Re_DeltaC10_tau = *Param["Re_DeltaC10_tau"];
        result.Im_DeltaC10_tau = *Param["Im_DeltaC10_tau"];
        result.Re_DeltaCQ1_tau = *Param["Re_DeltaCQ1_tau"];
        result.Im_DeltaCQ1_tau = *Param["Im_DeltaCQ1_tau"];
        result.Re_DeltaCQ2_tau = *Param["Re_DeltaCQ2_tau"];
        result.Im_DeltaCQ2_tau = *Param["Im_DeltaCQ2_tau"];

        /* Lines below are valid in the flavour NON-universal case
           deltaC[1..10] = Cmu[1..10], deltaC[11..20] = Ce[1..10], deltaC[21..30] = Ctau[1..10]
           deltaCQ[1,2] = CQmu[1,2], deltaCQ[1,2] = CQe[1,2], deltaCQ[1,2] = CQtau[1,2] */

        result.deltaC[7]=std::complex<double>(result.Re_DeltaC7_mu, result.Im_DeltaC7_mu);
        result.deltaC[9]=std::complex<double>(result.Re_DeltaC9_mu, result.Im_DeltaC9_mu);
        result.deltaC[10]=std::complex<double>(result.Re_DeltaC10_mu, result.Im_DeltaC10_mu);
        result.deltaCQ[1]=std::complex<double>(result.Re_DeltaCQ1_mu, result.Im_DeltaCQ1_mu);
        result.deltaCQ[2]=std::complex<double>(result.Re_DeltaCQ2_mu, result.Im_DeltaCQ2_mu);

        result.deltaC[17]=std::complex<double>(result.Re_DeltaC7_e, result.Im_DeltaC7_e);
        result.deltaC[19]=std::complex<double>(result.Re_DeltaC9_e, result.Im_DeltaC9_e);
        result.deltaC[20]=std::complex<double>(result.Re_DeltaC10_e, result.Im_DeltaC10_e);
        result.deltaCQ[3]=std::complex<double>(result.Re_DeltaCQ1_e, result.Im_DeltaCQ1_e);
        result.deltaCQ[4]=std::complex<double>(result.Re_DeltaCQ2_e, result.Im_DeltaCQ2_e);

        result.deltaC[27]=std::complex<double>(result.Re_DeltaC7_tau, result.Im_DeltaC7_tau);
        result.deltaC[29]=std::complex<double>(result.Re_DeltaC9_tau, result.Im_DeltaC9_tau);
        result.deltaC[30]=std::complex<double>(result.Re_DeltaC10_tau, result.Im_DeltaC10_tau);
        result.deltaCQ[5]=std::complex<double>(result.Re_DeltaCQ1_tau, result.Im_DeltaCQ1_tau);
        result.deltaCQ[6]=std::complex<double>(result.Re_DeltaCQ2_tau, result.Im_DeltaCQ2_tau);
      }

      if (flav_debug) std::cout<<"Finished SuperIso_fill"<< std::endl;
    }

    /// Fill SuperIso nuisance structure
    void SuperIso_nuisance_fill(nuisance &nuislist)
    {
      using namespace Pipes::SuperIso_nuisance_fill;
      if (flav_debug) std::cout<<"Starting SuperIso_nuisance_fill"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;

      BEreq::set_nuisance(&nuislist);
      BEreq::set_nuisance_value_from_param(&nuislist,&param);

      /* Here the nuisance parameters which should not be used for the correlation calculation have to be given a zero standard deviation.
         E.g. nuislist.mass_b.dev=0.; */

      if (flav_debug) std::cout<<"Finished SuperIso_nuisance_fill"<< std::endl;
    }

    /// Reorder a FlavBit observables list to match ordering expected by HEPLike
    void update_obs_list(std::vector<str>& obs_list, const std::vector<str>& HL_obs_list)
    {
      std::vector<str> FB_obs_list = translate_flav_obs("HEPLike", "FlavBit", HL_obs_list);
      std::vector<str> temp;
      for (auto it = FB_obs_list.begin(); it != FB_obs_list.end(); ++it)
      {
        if (std::find(obs_list.begin(), obs_list.end(), *it) != obs_list.end())
        {
          temp.push_back(*it);
        }
      }
      obs_list = temp;
    }

    /// Extract central values of the given observables from the central value map.
    std::vector<double> get_obs_theory(const flav_prediction& prediction, const std::vector<std::string>& observables)
    {
      if(flav_debug) std::cout<<"In get_obs_theory() function"<<std::endl;
      std::vector<double> obs_theory;
      obs_theory.reserve(observables.size());
      for (unsigned int i = 0; i < observables.size(); ++i)
      {
        if(flav_debug) std::cout<<"Trying to find: "<<observables[i]<<std::endl;
        obs_theory.push_back(prediction.central_values.at(observables[i]));
      }
      return obs_theory;
    };

    /// Extract covariance matrix of the given observables from the covariance map.
    boost::numeric::ublas::matrix<double> get_obs_covariance(const flav_prediction& prediction, const std::vector<std::string>& observables)
    {
      boost::numeric::ublas::matrix<double> obs_covariance(observables.size(), observables.size());
      for (unsigned int i = 0; i < observables.size(); ++i)
      {
        for (unsigned int j = 0; j < observables.size(); ++j)
        {
          obs_covariance(i, j) = prediction.covariance.at(observables[i]).at(observables[j]);
        }
      }
      return obs_covariance;
    };

    /// Helper function to avoid code duplication.
    void SuperIso_prediction_helper(const std::vector<std::string>& FB_obslist, const std::vector<std::string>& SI_obslist, flav_prediction& result,
                                    const parameters& param, const nuisance& nuislist,
                                    void (*get_predictions_nuisance)(char**, int*, double**, const parameters*, const nuisance*),
                                    void (*observables)(int, obsname*, int, double*, double*, const nuisance*, char**, const parameters*),
                                    void (*convert_correlation)(nuiscorr*, int, double**, char**, int),
                                    void (*get_th_covariance_nuisance)(double***, char**, int*, const parameters*, const nuisance*, double**),
                                    bool useSMCovariance,
                                    bool SMCovarianceCached
                                    )
    {
      if (flav_debug)
      {
        std::cout << "Starting SuperIso_prediction" << std::endl;
        std::cout << "Changing convention. Before:"<< std::endl;
        print(result,{"S3", "S4", "S5", "S8", "S9", "AT_Im"});
      }

      int nObservables = SI_obslist.size();
      if (flav_debug) std::cout<<"Observables: "<<std::endl;

      char obsnames[nObservables][50];
      for(int iObservable = 0; iObservable < nObservables; iObservable++)
      {
        strcpy(obsnames[iObservable], SI_obslist[iObservable].c_str());
        if( flav_debug) std::cout<<SI_obslist[iObservable].c_str()<<std::endl;
      }

      // ---------- CENTRAL VALUES ----------
      double *result_central;

      // Reserve memory
      result_central = (double *) calloc(nObservables, sizeof(double));

      // Needed for SuperIso backend
      get_predictions_nuisance((char**)obsnames, &nObservables, &result_central, &param, &nuislist);

      // Compute the central values
      for(int iObservable = 0; iObservable < nObservables; ++iObservable)
      {
        result.central_values[FB_obslist[iObservable]] = result_central[iObservable];
      }

      // Free memory
      free(result_central);
      result_central = NULL;

      if (flav_debug)
      {
        for(int iObservable = 0; iObservable < nObservables; ++iObservable)
        {
          printf("%s=%.4e\n", obsnames[iObservable], result.central_values[FB_obslist[iObservable]]);
        }
      }

      //Switch the observables to LHCb convention
      Kstarll_Theory2Experiment_translation(result.central_values, 1);
      Kstarll_Theory2Experiment_translation(result.central_values, 2);

      // If we need to compute the covariance, either because we're doing it for every point or we haven't cached the SM value, do it.
      if (not useSMCovariance or not SMCovarianceCached)
      {

        // ---------- COVARIANCE ----------
        static bool first = true;
        static const int nNuisance=161;
        static char namenuisance[nNuisance+1][50];
        static double **corr=(double  **) malloc((nNuisance+1)*sizeof(double *));  // Nuisance parameter correlations

        if (first)
        {
          observables(0, NULL, 0, NULL, NULL, &nuislist, (char **)namenuisance, &param); // Initialization of namenuisance

          // Reserve memory
          for(int iObservable = 0; iObservable <= nNuisance; ++iObservable)
          {
            corr[iObservable]=(double *) malloc((nNuisance+1)*sizeof(double));
          }

          // Needed for SuperIso backend
          convert_correlation((nuiscorr *)corrnuis, byVal(ncorrnuis), (double **)corr, (char **)namenuisance, byVal(nNuisance));

          first = false;
        }

        double **result_covariance;

        if (useSMCovariance)
        {
          // Copy the parameters and set all Wilson Coefficients to 0 (SM values)
          parameters param_SM = param;
          for(int ie=1;ie<=30;ie++)
          {
            param_SM.deltaC[ie]=0.;
            param_SM.deltaCp[ie]=0.;
          }
          for(int ie=1;ie<=6;ie++)
          {
            param_SM.deltaCQ[ie]=0.;
            param_SM.deltaCQp[ie]=0.;
          }
          // Use the SM values of the parameters to calculate the SM theory covariance.
          get_th_covariance_nuisance(&result_covariance, (char**)obsnames, &nObservables, &param_SM, &nuislist, (double **)corr);
        }
        else
        {
          // Calculate covariance at the new physics point.
          get_th_covariance_nuisance(&result_covariance, (char**)obsnames, &nObservables, &param, &nuislist, (double **)corr);
        }

        // Fill the covariance matrix in the result structure
        for(int iObservable=0; iObservable < nObservables; ++iObservable)
        {
          for(int jObservable = 0; jObservable < nObservables; ++jObservable)
          {
            result.covariance[FB_obslist[iObservable]][FB_obslist[jObservable]] = result_covariance[iObservable][jObservable];
          }
        }

        //Switch the covariances to LHCb convention
        Kstarll_Theory2Experiment_translation(result.covariance, 1);
        Kstarll_Theory2Experiment_translation(result.covariance, 2);

        // We are not freeing the memory because we made the variable static.
        // Just keeping this for reference on how to clean up the allocated
        // memory in case of non-static calculation of **corr.
        // Free memory
        //for(int iObservable = 0; iObservable <= nNuisance; ++iObservable) free(corr[iObservable]);
        //free(corr);
      }

      if (flav_debug)
      {
        for(int iObservable=0; iObservable < nObservables; ++iObservable)
        {
          for(int jObservable = iObservable; jObservable < nObservables; ++jObservable)
          {
            printf("Covariance %s - %s: %.4e\n",
              obsnames[iObservable], obsnames[jObservable], result.covariance[FB_obslist[iObservable]][FB_obslist[jObservable]]);
           }
        }
        std::cout << "Changing convention. After:"<< std::endl;
        print(result,{"S3", "S4", "S5", "S8", "S9", "AT_Im"});
        std::cout << "Finished SuperIso_prediction" << std::endl;
      }

    }


    #define THE_REST(bins)                                          \
      static const std::vector<str> SI_obslist =                    \
       translate_flav_obs("FlavBit", "SuperIso", FB_obslist,        \
       Utils::p2dot(bins));                                         \
      static bool use_SM_covariance =                               \
       runOptions->getValueOrDef<bool>(false, "use_SM_covariance"); \
      static bool SM_covariance_cached = false;                     \
      SuperIso_prediction_helper(                                   \
        FB_obslist,                                                 \
        SI_obslist,                                                 \
        result,                                                     \
        *Dep::SuperIso_modelinfo,                                   \
        *Dep::SuperIso_nuisance,                                    \
        BEreq::get_predictions_nuisance.pointer(),                  \
        BEreq::observables.pointer(),                               \
        BEreq::convert_correlation.pointer(),                       \
        BEreq::get_th_covariance_nuisance.pointer(),                \
        use_SM_covariance,                                          \
        SM_covariance_cached                                        \
    );                                                              \
    SM_covariance_cached = true;

    #define SI_SINGLE_PREDICTION_FUNCTION(name)                          \
    void CAT(SuperIso_prediction_,name)(flav_prediction& result)         \
    {                                                                    \
      using namespace CAT(Pipes::SuperIso_prediction_,name);             \
      static const std::vector<str> FB_obslist = {#name};                \
      THE_REST("")                                                       \
    }                                                                    \

    #define SI_SINGLE_PREDICTION_FUNCTION_BINS(name,bins)                \
    void CAT_3(SuperIso_prediction_,name,bins)(flav_prediction& result)  \
    {                                                                    \
      using namespace CAT_3(Pipes::SuperIso_prediction_,name,bins);      \
      static const std::vector<str> FB_obslist = {#name};                \
      THE_REST(#bins)                                                    \
    }                                                                    \

    #define SI_MULTI_PREDICTION_FUNCTION(name)                           \
    void CAT(SuperIso_prediction_,name)(flav_prediction& result)         \
    {                                                                    \
      using namespace CAT(Pipes::SuperIso_prediction_,name);             \
      static const std::vector<str> FB_obslist =                         \
       Downstream::subcaps->getNames();                                  \
      if (FB_obslist.empty()) FlavBit_error().raise(LOCAL_INFO,          \
       "Missing subcapabilities for SuperIso_prediction_"#name".");      \
      THE_REST("")                                                       \
    }                                                                    \

    #define SI_MULTI_PREDICTION_FUNCTION_BINS(name,bins,exp)             \
    void CAT_4(SuperIso_prediction_,name,bins,exp)(flav_prediction&      \
     result)                                                             \
    {                                                                    \
      using namespace CAT_4(Pipes::SuperIso_prediction_,name,bins,exp);  \
      static const std::vector<str> FB_obslist =                         \
       Downstream::subcaps->getNames();                                  \
      if (FB_obslist.empty()) FlavBit_error().raise(LOCAL_INFO,          \
       "Missing subcapabilities for SuperIso_prediction_"#name".");      \
      THE_REST(#bins)                                                    \
    }                                                                    \

    SI_SINGLE_PREDICTION_FUNCTION(B2taunu)
    SI_SINGLE_PREDICTION_FUNCTION(b2sgamma)

    SI_SINGLE_PREDICTION_FUNCTION(B2Kstargamma)
    SI_SINGLE_PREDICTION_FUNCTION(BRBXsmumu_lowq2)
    SI_SINGLE_PREDICTION_FUNCTION(BRBXsmumu_highq2)
    SI_SINGLE_PREDICTION_FUNCTION(AFBBXsmumu_lowq2)
    SI_SINGLE_PREDICTION_FUNCTION(AFBBXsmumu_highq2)

    SI_SINGLE_PREDICTION_FUNCTION_BINS(Bs2phimumuBr,_1_6)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(Bs2phimumuBr,_15_19)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KstarmumuBr,_0p1_0p98)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KstarmumuBr,_1p1_2p5)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KstarmumuBr,_2p5_4)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KstarmumuBr,_4_6)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KstarmumuBr,_6_8)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KstarmumuBr,_15_19)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KmumuBr,_0p05_2)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KmumuBr,_2_4p3)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KmumuBr,_4p3_8p68)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KmumuBr,_14p18_16)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KmumuBr,_16_18)
    SI_SINGLE_PREDICTION_FUNCTION_BINS(B2KmumuBr,_18_22)
    // TODO: these should be re-activated once RK and RKstar can be extracted from a future version of SuperIso using the check_nameobs function.
    //SI_SINGLE_PREDICTION_FUNCTION_BINS(RK_LHCb,_1p1_6)
    //SI_SINGLE_PREDICTION_FUNCTION_BINS(RKstar_LHCb,_0p045_1p1)
    //SI_SINGLE_PREDICTION_FUNCTION_BINS(RKstar_LHCb,_1p1_6)

    // TODO: Temporary restore of RK and RKstar convenience functions until their new interface is fixed
    /// SuperIso prediction for RK* in low q^2
    void SuperIso_RKstar_0045_11(double &result)
    {
      using namespace Pipes::SuperIso_RKstar_0045_11;
      if (flav_debug) std::cout<<"Starting SuperIso_RKstar_0045_11"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::SuperIso_RKstar_computation(&param,0.045,1.1);

      if (flav_debug) printf("RK*_lowq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_RKstar_0045_11"<< std::endl;
    }

    /// RK* in intermediate q^2
    void SuperIso_RKstar_11_60(double &result)
    {
      using namespace Pipes::SuperIso_RKstar_11_60;
      if (flav_debug) std::cout<<"Starting SuperIso_RKstar_11_60"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::SuperIso_RKstar_computation(&param,1.1,6.0);

      if (flav_debug) printf("RK*_intermq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_RKstar_11_60"<< std::endl;
    }

    /// RK between 1 and 6 GeV^2
    void SuperIso_RK(double &result)
    {
      using namespace Pipes::SuperIso_RK;
      if (flav_debug) std::cout<<"Starting SuperIso_RK"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::SuperIso_RK_computation(&param,1.0,6.0);

      if (flav_debug) printf("RK=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_RK"<< std::endl;
    }

    // The sub-capabilities that may be received from likelihood functions in order to feed them valid observables are listed
    // below. In principle though, these functions will accept as sub-capabilities *any* recognised SuperIso observable names.
    // The recognised observable names can be found in the check_nameobs function in src/chi2.c in SuperIso.
    SI_MULTI_PREDICTION_FUNCTION(B2mumu)                                // Typical subcaps: BRuntag_Bsmumu, BR_Bdmumu
    //SI_MULTI_PREDICTION_FUNCTION(RDRDstar)                            // TODO: Typical subcaps: RD, RDstar
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_0p1_2,_Atlas)     // Typical subcaps: FL, S3, S4, S5, S7, S8
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_2_4,_Atlas)       // Typical subcaps: FL, S3, S4, S5, S7, S8
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4_8,_Atlas)       // Typical subcaps: FL, S3, S4, S5, S7, S8
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_1_2,_CMS)         // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_2_4p3,_CMS)       // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4p3_6,_CMS)       // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_6_8p68,_CMS)      // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_10p09_12p86,_CMS) // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_14p18_16,_CMS)    // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_16_19,_CMS)       // Typical subcaps: P1, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_0p1_4,_Belle)     // Typical subcaps: P4prime, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4_8,_Belle)       // Typical subcaps: P4prime, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_10p9_12p9,_Belle) // Typical subcaps: P4prime, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_14p18_19,_Belle)  // Typical subcaps: P4prime, P5prime
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_0p1_0p98,_LHCb)   // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_1p1_2p5,_LHCb)    // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_2p5_4,_LHCb)      // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4_6,_LHCb)        // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_6_8,_LHCb)        // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_15_19,_LHCb)      // Typical subcaps: FL, AFB, S3, S4, S5, S7, S8, S9
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstareeAng,_0p0008_0p257,_LHCb) // Typical subcaps: FLee, AT_Re, AT_2, AT_Im

    #undef SI_PRED_HELPER_CALL
    #undef SI_SINGLE_PREDICTION_FUNCTION
    #undef SI_SINGLE_PREDICTION_FUNCTION_BINS
    #undef SI_MULTI_PREDICTION_FUNCTION
    #undef SI_MULTI_PREDICTION_FUNCTION_BINS


    /// Br B->tau nu_tau decays
    void SuperIso_prediction_Btaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Btaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Btaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Btaunu(&param);

      if (flav_debug) printf("BR(B->tau nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Btaunu"<< std::endl;
    }


    /// Br B->D_s tau nu
    void SuperIso_prediction_Dstaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Dstaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Dstaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dstaunu(&param);

      if (flav_debug) printf("BR(Ds->tau nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Dstaunu"<< std::endl;
    }


    /// Br B->D_s mu nu
    void SuperIso_prediction_Dsmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Dsmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Dsmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dsmunu(&param);

      if (flav_debug) printf("BR(Ds->mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Dsmunu"<< std::endl;
    }


    /// Br D -> mu nu
    void SuperIso_prediction_Dmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Dmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Dmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dmunu(&param);

      if (flav_debug) printf("BR(D->mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Dmunu"<< std::endl;
    }


    /// Br B -> D tau nu
    void SuperIso_prediction_BDtaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDtaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDtaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_tau_D  = 3.16; // 1.776**2
      double q2_max_tau_D  = 11.6;   // (5.28-1.869)**2
      int gen_tau_D        = 3;
      int charge_tau_D     = 0;// D* is the charged version
      double obs_tau_D[3];

      result=BEreq::BRBDlnu(byVal(gen_tau_D), byVal( charge_tau_D), byVal(q2_min_tau_D), byVal(q2_max_tau_D), byVal(obs_tau_D), &param);

      if (flav_debug) printf("BR(B-> D tau nu )=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDtaunu"<< std::endl;
    }


    /// Br B -> D mu nu
    void SuperIso_prediction_BDmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_mu_D=  0.012; // 0.105*0.105
      double q2_max_mu_D=  11.6;   // (5.28-1.869)**2
      int gen_mu_D        =2;
      int charge_mu_D     =0;// D* is the charged version
      double obs_mu_D[3];

      result= BEreq::BRBDlnu(byVal(gen_mu_D), byVal( charge_mu_D), byVal(q2_min_mu_D), byVal(q2_max_mu_D), byVal(obs_mu_D), &param);

      if (flav_debug) printf("BR(B->D mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDmunu"<< std::endl;
    }


    /// Br B -> D* tau nu
    void SuperIso_prediction_BDstartaunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDstartaunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDstartaunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_tau_Dstar = 3.16; // 1.776**2
      double q2_max_tau_Dstar = 10.67;   //(5.279-2.01027)*(5.279-2.01027);
      int gen_tau_Dstar        =3;
      int charge_tau_Dstar     =1;// D* is the charged version
      double obs_tau_Dstar[4];

      result= BEreq::BRBDstarlnu(byVal(gen_tau_Dstar), byVal( charge_tau_Dstar), byVal(q2_min_tau_Dstar), byVal(q2_max_tau_Dstar), byVal(obs_tau_Dstar), &param);

      if (flav_debug) printf("BR(B->Dstar tau nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDstartaunu"<< std::endl;
    }


    /// Br B -> D* mu nu
    void SuperIso_prediction_BDstarmunu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BDstarmunu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BDstarmunu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_mu_Dstar = 0.012; // 0.105*0.105
      double q2_max_mu_Dstar = 10.67;   //(5.279-2.01027)*(5.279-2.01027);
      int gen_mu_Dstar        =2;
      int charge_mu_Dstar     =1;// D* is the charged version
      double obs_mu_Dstar[4];

      result=BEreq::BRBDstarlnu(byVal(gen_mu_Dstar), byVal( charge_mu_Dstar), byVal(q2_min_mu_Dstar), byVal(q2_max_mu_Dstar), byVal(obs_mu_Dstar), &param);

      if (flav_debug) printf("BR(B->Dstar mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BDstarmunu"<< std::endl;
    }


    ///  B-> D tau nu / B-> D e nu decays
    void SuperIso_prediction_RD(double &result)
    {
      using namespace Pipes::SuperIso_prediction_RD;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_RD"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::BDtaunu_BDenu(&param);

      if (flav_debug) printf("BR(B->D tau nu)/BR(B->D e nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_RD"<< std::endl;
    }


    ///  B->D* tau nu / B-> D* e nu decays
    void SuperIso_prediction_RDstar(double &result)
    {
      using namespace Pipes::SuperIso_prediction_RDstar;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_RDstar"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::BDstartaunu_BDstarenu(&param);

      if (flav_debug) printf("BR(B->D* tau nu)/BR(B->D* e nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_RD*"<< std::endl;
    }


    /// B->K mu nu / B-> pi mu nu
    void SuperIso_prediction_Rmu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Rmu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Rmu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Kmunu_pimunu(&param);

      if (flav_debug) printf("R_mu=BR(K->mu nu)/BR(pi->mu nu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Rmu"<< std::endl;
    }


    /// 2-to-3-body decay ratio for semileptonic K and pi decays
    void SuperIso_prediction_Rmu23(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Rmu23;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Rmu23"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Rmu23(&param);

      if (flav_debug) printf("Rmu23=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Rmu23"<< std::endl;
    }


    /// Delta_0 (CP-averaged isospin asymmetry of B -> K* gamma)
    void SuperIso_prediction_delta0(double &result)
    {
      using namespace Pipes::SuperIso_prediction_delta0;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_delta0"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_delta0(&param);

      if (flav_debug) printf("Delta0(B->K* gamma)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_delta0"<< std::endl;
    }


    /// Zero crossing of the forward-backward asymmetry of B -> X_s mu mu
    void SuperIso_prediction_A_BXsmumu_zero(double &result)
    {
      using namespace Pipes::SuperIso_prediction_A_BXsmumu_zero;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_A_BXsmumu_zero"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXsmumu_zero(&param);

      if (flav_debug) printf("AFB(B->Xs mu mu)_zero=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_A_BXsmumu_zero"<< std::endl;
    }


    /// Inclusive branching fraction B -> X_s tau tau at high q^2
    void SuperIso_prediction_BRBXstautau_highq2(double &result)
    {
      using namespace Pipes::SuperIso_prediction_BRBXstautau_highq2;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_BRBXstautau_highq2"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::BRBXstautau_highq2(&param);

      if (flav_debug) printf("BR(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_BRBXstautau_highq2"<< std::endl;
    }


    /// Forward-backward asymmetry of B -> X_s tau tau at high q^2
    void SuperIso_prediction_A_BXstautau_highq2(double &result)
    {
      using namespace Pipes::SuperIso_prediction_A_BXstautau_highq2;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_A_BXstautau_highq2"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXstautau_highq2(&param);

      if (flav_debug) printf("AFB(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_A_BXstautau_highq2"<< std::endl;
    }

    // RK* for RHN, using same approximations as RK, low q^2
    void RHN_RKstar_0045_11(double &result)
    {
      using namespace Pipes::RHN_RKstar_0045_11;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) std::cout << "Starting RHN_RKstar_0045_11" << std::endl;

      const double mW = sminputs.mW;
      const double sinW2 = sqrt(1.0 - pow(sminputs.mW/sminputs.mZ,2));

      // NNLL calculation of SM Wilson coefficients from 1712.01593 and 0811.1214
      const double C10_SM = -4.103;
      const double C9_SM = 4.211;

      // Wilson coefficients for the RHN model, from 1706.07570
      std::complex<double> C10_mu = {0.0, 0.0}, C10_e = {0.0, 0.0};
      for(int i=0; i<3; i++)
      {
        C10_mu += 1.0/(4.0*sinW2)*Theta.adjoint()(i,1)*Theta(1,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
        C10_e += 1.0/(4.0*sinW2)*Theta.adjoint()(i,0)*Theta(0,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
      }
      std::complex<double> C9_mu = - C10_mu, C9_e = -C10_e;

      // Aproximated solution from eq A.3 in 1408.4097
      result =  std::norm(C10_SM + C10_mu) + std::norm(C9_SM + C9_mu);
      result /= std::norm(C10_SM + C10_e) + std::norm(C9_SM + C9_e);

      if (flav_debug) std::cout << "RK = " << result << std::endl;
      if (flav_debug) std::cout << "Finished RHN_RKstar_0045_11" << std::endl;

    }

    // RK* for RHN, using same approximations as RK, intermediate q^2
    void RHN_RKstar_11_60(double &result)
    {
      using namespace Pipes::RHN_RKstar_11_60;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) std::cout << "Starting RHN_RKstar_11_60" << std::endl;

      const double mW = sminputs.mW;
      const double sinW2 = sqrt(1.0 - pow(sminputs.mW/sminputs.mZ,2));

      // NNLL calculation of SM Wilson coefficients from 1712.01593 and 0811.1214
      const double C10_SM = -4.103;
      const double C9_SM = 4.211;

      // Wilson coefficients for the RHN model, from 1706.07570
      std::complex<double> C10_mu = {0.0, 0.0}, C10_e = {0.0, 0.0};
      for(int i=0; i<3; i++)
      {
        C10_mu += 1.0/(4.0*sinW2)*Theta.adjoint()(i,1)*Theta(1,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
        C10_e += 1.0/(4.0*sinW2)*Theta.adjoint()(i,0)*Theta(0,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
      }
      std::complex<double> C9_mu = - C10_mu, C9_e = -C10_e;

      // Aproximated solution from eq A.3 in 1408.4097
      result =  std::norm(C10_SM + C10_mu) + std::norm(C9_SM + C9_mu);
      result /= std::norm(C10_SM + C10_e) + std::norm(C9_SM + C9_e);

      if (flav_debug) std::cout << "RK = " << result << std::endl;
      if (flav_debug) std::cout << "Finished RHN_RKstar_11_60" << std::endl;

    }

    /// RK for RHN
    void RHN_RK(double &result)
    {
      using namespace Pipes::RHN_RK;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) std::cout << "Starting RHN_RK" << std::endl;

      const double mW = sminputs.mW;
      const double sinW2 = sqrt(1.0 - pow(sminputs.mW/sminputs.mZ,2));

      // NNLL calculation of SM Wilson coefficients from 1712.01593 and 0811.1214
      const double C10_SM = -4.103;
      const double C9_SM = 4.211;

      // Wilson coefficients for the RHN model, from 1706.07570
      std::complex<double> C10_mu = {0.0, 0.0}, C10_e = {0.0, 0.0};
      for(int i=0; i<3; i++)
      {
        C10_mu += 1.0/(4.0*sinW2)*Theta.adjoint()(i,1)*Theta(1,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
        C10_e += 1.0/(4.0*sinW2)*Theta.adjoint()(i,0)*Theta(0,i) * LoopFunctions::E(pow(mt/mW,2),pow(mN[i]/mW,2));
      }
      std::complex<double> C9_mu = - C10_mu, C9_e = -C10_e;

      // Aproximated solution from eq A.3 in 1408.4097
      result =  std::norm(C10_SM + C10_mu) + std::norm(C9_SM + C9_mu);
      result /= std::norm(C10_SM + C10_e) + std::norm(C9_SM + C9_e);

      if (flav_debug) std::cout << "RK = " << result << std::endl;
      if (flav_debug) std::cout << "Finished RHN_RK" << std::endl;
    }

    /// Isospin asymmetry of B-> K* mu mu
    void SuperIso_prediction_AI_BKstarmumu(double &result)
    {
      using namespace Pipes::SuperIso_prediction_AI_BKstarmumu;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_AI_BKstarmumu"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_AI_BKstarmumu(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_lowq2=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_AI_BKstarmumu"<< std::endl;
    }


    /// Zero crossing of isospin asymmetry of B-> K* mu mu
    void SuperIso_prediction_AI_BKstarmumu_zero(double &result)
    {
      using namespace Pipes::SuperIso_prediction_AI_BKstarmumu_zero;

      if (flav_debug) std::cout<<"Starting SuperIso_prediction_AI_BKstarmumu_zero"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::modified_AI_BKstarmumu_zero(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_zero=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_AI_BKstarmumu_zero"<< std::endl;
    }


    /// Flavour observables from FeynHiggs: B_s mass asymmetry, Br B_s -> mu mu, Br B -> X_s gamma
    void FeynHiggs_FlavourObs(fh_FlavourObs_container &result)
    {
      using namespace Pipes::FeynHiggs_FlavourObs;

      if (flav_debug) std::cout<<"Starting FeynHiggs_FlavourObs"<< std::endl;

      fh_real bsgMSSM;     // B -> Xs gamma in MSSM
      fh_real bsgSM;       // B -> Xs gamma in SM
      fh_real deltaMsMSSM; // delta Ms in MSSM
      fh_real deltaMsSM;   // delta Ms in SM
      fh_real bsmumuMSSM;  // Bs -> mu mu in MSSM
      fh_real bsmumuSM;    // Bs -> mu mu in SM

      int error = 1;
      BEreq::FHFlavour(error, bsgMSSM, bsgSM,
           deltaMsMSSM, deltaMsSM,
           bsmumuMSSM, bsmumuSM);

      fh_FlavourObs_container FlavourObs;
      FlavourObs.Bsg_MSSM = bsgMSSM;
      FlavourObs.Bsg_SM = bsgSM;
      FlavourObs.deltaMs_MSSM = deltaMsMSSM;
      FlavourObs.deltaMs_SM = deltaMsSM;
      FlavourObs.Bsmumu_MSSM = bsmumuMSSM;
      FlavourObs.Bsmumu_SM = bsmumuSM;

      result = FlavourObs;
      if (flav_debug) std::cout<<"Finished FeynHiggs_FlavourObs"<< std::endl;
    }


    ///These functions extract observables from a FeynHiggs flavour result
    ///@{
    void FeynHiggs_prediction_bsgamma(double &result)
    {
      result = Pipes::FeynHiggs_prediction_bsgamma::Dep::FlavourObs->Bsg_MSSM;
    }
    void FeynHiggs_prediction_Bsmumu (double &result)
    {
      result = Pipes::FeynHiggs_prediction_Bsmumu::Dep::FlavourObs->Bsmumu_MSSM;
    }
    void FeynHiggs_prediction_DeltaMs(double &result)
    {
      result = Pipes::FeynHiggs_prediction_DeltaMs::Dep::FlavourObs->deltaMs_MSSM;
    }
    ///@}

    /// Likelihood for Delta Ms
    void deltaMB_likelihood(double &result)
    {
      using namespace Pipes::deltaMB_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_DeltaMs_err, th_err;

      if (flav_debug) std::cout << "Starting Delta_Ms_likelihood"<< std::endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in Delta_Ms_likelihood"<< std::endl;
        fread.read_yaml_measurement("flav_data.yaml", "DeltaMs");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_DeltaMs_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) std::cout << "Experiment: " << exp_meas << " " << exp_DeltaMs_err << " " << th_err << std::endl;

      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::prediction_DeltaMs;
      double theory_DeltaMs_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) std::cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<theory_DeltaMs_err<< std::endl;

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_DeltaMs_err, exp_DeltaMs_err, profile);
    }

    /// Measurements for tree-level leptonic and semileptonic B decays
    void SL_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::SL_measurements;

      const int n_experiments=8;
      static bool th_err_absolute[n_experiments], first = true;
      static double th_err[n_experiments];

      if (flav_debug) std::cout<<"Starting SL_measurements"<< std::endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="SL_likelihood";

        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in SL_measurements"<< std::endl;

        // B-> tau nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Btaunu");
        // B-> D mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_BDmunu");
        // B-> D* mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_BDstarmunu");
        // RD
        fread.read_yaml_measurement("flav_data.yaml", "RD");
        // RDstar
        fread.read_yaml_measurement("flav_data.yaml", "RDstar");
        // Ds-> tau nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Dstaunu");
        // Ds -> mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Dsmunu");
        // D -> mu nu
        fread.read_yaml_measurement("flav_data.yaml", "BR_Dmunu");

        fread.initialise_matrices();
        pmc.cov_exp=fread.get_exp_cov();
        pmc.value_exp=fread.get_exp_value();

        pmc.value_th.resize(n_experiments,1);
        // Set all entries in the covariance matrix explicitly to zero, as we will only write the diagonal ones later.
        pmc.cov_th = boost::numeric::ublas::zero_matrix<double>(n_experiments,n_experiments);
        for (int i = 0; i < n_experiments; ++i)
        {
          th_err[i] = fread.get_th_err()(i,0).first;
          th_err_absolute[i] = fread.get_th_err()(i,0).second;
        }

        pmc.dim=n_experiments;

        // Init over.
        first = false;
      }

      // R(D) is calculated assuming isospin symmetry
      double theory[8];
      // B-> tau nu SI
      theory[0] = *Dep::Btaunu;
      // B-> D mu nu
      theory[1] = *Dep::BDmunu;
      // B-> D* mu nu
      theory[2] = *Dep::BDstarmunu;
      // RD
      theory[3] = *Dep::RD;
      // RDstar
      theory[4] = *Dep::RDstar;
      // Ds-> tau nu
      theory[5] = *Dep::Dstaunu;
      // Ds -> mu nu
      theory[6] = *Dep::Dsmunu;
      // D -> mu nu
      theory[7] =*Dep::Dmunu;

      for (int i = 0; i < n_experiments; ++i)
      {
        pmc.value_th(i,0) = theory[i];
        pmc.cov_th(i,i) = th_err[i]*th_err[i] * (th_err_absolute[i] ? 1.0 : theory[i]*theory[i]);
      }
      // Add in the correlations between B-> D mu nu and RD
      pmc.cov_th(1,3) = pmc.cov_th(3,1) = -0.55 * th_err[1]*th_err[3] * (th_err_absolute[1] ? 1.0 : theory[1]) * (th_err_absolute[3] ? 1.0 : theory[3]);
      // Add in the correlations between B-> D* mu nu and RD*
      pmc.cov_th(2,4) = pmc.cov_th(4,2) = -0.62 * th_err[2]*th_err[4] * (th_err_absolute[2] ? 1.0 : theory[2]) * (th_err_absolute[4] ? 1.0 : theory[4]);

      pmc.diff.clear();
      for (int i=0;i<n_experiments;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) std::cout<<"Finished SL_measurements"<< std::endl;

    }


    /// Likelihood for tree-level leptonic and semileptonic B decays
    void SL_likelihood(double &result)
    {
      using namespace Pipes::SL_likelihood;

      if (flav_debug) std::cout<<"Starting SL_likelihood"<< std::endl;

      predictions_measurements_covariances pmc = *Dep::SL_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;

      //calculating a diff
      std::vector<double> diff;
      diff=pmc.diff;

      boost::numeric::ublas::matrix<double> cov_inv(pmc.dim, pmc.dim);
      InvertMatrix(cov, cov_inv);

      double Chi2=0;
      for (int i=0; i < pmc.dim; ++i)
      {
        for (int j=0; j<pmc.dim; ++j)
        {
          Chi2+= diff[i] * cov_inv(i,j)*diff[j];
        }
      }

      result=-0.5*Chi2;

      if (flav_debug) std::cout<<"Finished SL_likelihood"<< std::endl;

      if (flav_debug_LL) std::cout<<"Likelihood result SL_likelihood  : "<< result<< std::endl;

    }

    // Helper function
    double G(const double x)
    {
      if(x)
        return (10.0 - 43.0*x + 78.0*pow(x,2) - 49.0*pow(x,3) + 4.0*pow(x,4) + 18.0*pow(x,3)*log(x)) / (3.0*pow(x - 1,4));
      else
        return 10.0/3;
    }

    // Contribution to mu -> e gamma from RHNs
    void RHN_muegamma(double &result)
    {
      using namespace Pipes::RHN_muegamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      std::vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      std::vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<std::complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mMu,5)/(4 * sminputs.alphainv);

      // Form factors
      int e = 0, mu = 1;
      std::complex<double> k2l = FormFactors::K2L(mu, e, sminputs, U, ml, mnu);
      std::complex<double> k2r = FormFactors::K2R(mu, e, sminputs, U, ml, mnu);

      result *= (std::norm(k2l) + std::norm(k2r));

      result /= Dep::mu_minus_decay_rates->width_in_GeV;

    }

    // Contribution to tau -> e gamma from RHNs
    void RHN_tauegamma(double &result)
    {
      using namespace Pipes::RHN_tauegamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      std::vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      std::vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<std::complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mTau,5)/(4*sminputs.alphainv);

      // Form factors
      int e = 0, tau = 2;
      std::complex<double> k2l = FormFactors::K2L(tau, e, sminputs, U, ml, mnu);
      std::complex<double> k2r = FormFactors::K2R(tau, e, sminputs, U, ml, mnu);

      result *= (std::norm(k2l) + std::norm(k2r));

      result /= Dep::tau_minus_decay_rates->width_in_GeV;

    }

    // Contribution to tau -> mu gamma from RHNs
    void RHN_taumugamma(double &result)
    {
      using namespace Pipes::RHN_taumugamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      std::vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      std::vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<std::complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mTau,5)/(4 * sminputs.alphainv);

      // Form factors
      int mu = 1, tau = 2;
      std::complex<double> k2l = FormFactors::K2L(tau, mu, sminputs, U, ml, mnu);
      std::complex<double> k2r = FormFactors::K2R(tau, mu, sminputs, U, ml, mnu);

      result *= (std::norm(k2l) + std::norm(k2r));

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    // General contribution to l_\alpha^- -> l_\beta^- l_\gamma^- l_\delta^+ from RHNs
    double RHN_l2lll(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix3cd Vnu, Eigen::Matrix3cd Theta, Eigen::Matrix3cd m_nu, double M1, double M2, double M3, double mH)
    {
      std::vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      std::vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), M1, M2, M3};

      Eigen::Matrix<std::complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      // Form factors
      std::complex<double> k2l = FormFactors::K2L(alpha, beta, sminputs, U, ml, mnu);
      std::complex<double> k2r = FormFactors::K2R(alpha, beta, sminputs, U, ml, mnu);
      std::complex<double> k1r = FormFactors::K1R(alpha, beta, sminputs, U, mnu);
      std::complex<double> asll = FormFactors::ASLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      std::complex<double> aslr = FormFactors::ASLR(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      std::complex<double> asrl = FormFactors::ASRL(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      std::complex<double> asrr = FormFactors::ASRR(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      std::complex<double> avll = FormFactors::AVLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      std::complex<double> avlr = FormFactors::AVLR(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      std::complex<double> avrl = FormFactors::AVLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      std::complex<double> avrr = FormFactors::AVRR(alpha, beta, gamma, delta, sminputs, U, ml, mnu);

      std::complex<double> avhatll = avll;
      std::complex<double> avhatlr = avlr;
      std::complex<double> avhatrl = avrl + 4. * pi / sminputs.alphainv * k1r;
      std::complex<double> avhatrr = avrr + 4. * pi / sminputs.alphainv * k1r;

      double l2lll = 0;
      if(beta == gamma and gamma == delta) // l(alpha)- -> l(beta)- l(beta)- l(beta)+
      {
        l2lll = real(16. * pow(pi,2) / pow(sminputs.alphainv,2) * (std::norm(k2l) + std::norm(k2r)) * (16./3.*log(ml[alpha]/ml[beta]) - 22./3.) + 1./24. * (std::norm(asll) + std::norm(asrr) + 2.*std::norm(aslr) + 2.*std::norm(asrl)) + 1./3. * (2.*std::norm(avhatll) + 2.*std::norm(avhatrr) + std::norm(avhatlr) + std::norm(avhatrl)) + 4.*pi/(3.*sminputs.alphainv)*(k2l*conj(asrl - 2.*avhatrl - 4.*avhatrr) + conj(k2l)*(asrl - 2.*avhatrl - 4.*avhatrr) + k2r*conj(aslr - 2.*avhatlr - 4.*avhatll) + conj(k2r)*(aslr - 2.*avhatlr - 4.*avhatll)) - 1./6. * (aslr*conj(avhatlr) + asrl*conj(avhatrl) + conj(aslr)*avhatlr + conj(asrl)*avhatrl));
      }
      else if(gamma == delta) // l(alpha)- -> l(beta)- l(gamma)- l(gamma)+
      {
        l2lll = real(16. *pow(pi,2) / pow(sminputs.alphainv,2) * (std::norm(k2l) + std::norm(k2r)) * (16./3.*log(ml[alpha]/ml[gamma]) - 8.) + 1./12. *(std::norm(asll) + std::norm(asrr) + std::norm(aslr) + std::norm(asrl)) + 1./3. * (std::norm(avhatll) + std::norm(avhatrr) + std::norm(avhatlr) + std::norm(avhatrl)) + 8.*pi/(3.*sminputs.alphainv) * (k2l*conj(avhatrl + avhatrr) + k2r*conj(avhatlr + avhatll) + conj(k2l)*(avhatrl + avhatrr) + conj(k2r)*(avhatlr + avhatll)));
      }
      else if(beta == gamma) // l(alpha)- -> l(beta)- l(beta)- l(delta)+
      {
        l2lll = real(1./24. * (std::norm(asll) + std::norm(asrr) + 2.*norm(aslr) + 2.*norm(asrl)) + 1./3.*(2.*norm(avhatll) + 2.*norm(avhatrr) + std::norm(avhatlr) + std::norm(avhatrl)) - 1./6.*(aslr*conj(avhatlr) + asrl*conj(avhatrl) + conj(aslr)*avhatlr + conj(asrl)*avhatrl));
      }
      return l2lll;

    }

    // Contribution to mu -> e e e from RHNs
    void RHN_mueee(double &result)
    {
      using namespace Pipes::RHN_mueee;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mMu,5)/(512*pow(pi,3));

      int e = 0, mu = 1;
      result *=  RHN_l2lll(mu, e, e, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::mu_minus_decay_rates->width_in_GeV;

    }

    // Contribution to tau -> e e e from RHNs
    void RHN_taueee(double &result)
    {
      using namespace Pipes::RHN_taueee;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, tau = 2;
      result *=  RHN_l2lll(tau, e, e, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;

    }

    // Contribution to tau -> mu mu mu from RHNs
    void RHN_taumumumu(double &result)
    {
      using namespace Pipes::RHN_taumumumu;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, mu, mu, mu, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;

    }

    // Contribution to tau^- -> mu^- e^- e^+ from RHNs
    void RHN_taumuee(double &result)
    {
      using namespace Pipes::RHN_taumuee;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, mu, e, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    // Contribution to tau^- -> e^- e^- mu^+ from RHNs
    void RHN_taueemu(double &result)
    {
      using namespace Pipes::RHN_taueemu;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, e, e, mu, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    // Contribution to tau^- -> e^- mu^- mu^+ from RHNs
    void RHN_tauemumu(double &result)
    {
      using namespace Pipes::RHN_tauemumu;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, e, mu, mu, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    // Contribution to tau^- -> mu^- mu^- e^+ from RHNs
    void RHN_taumumue(double &result)
    {
      using namespace Pipes::RHN_taumumue;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;

      result = pow(sminputs.mTau,5)/(512*pow(pi,3));

      int e = 0, mu = 1, tau = 2;
      result *=  RHN_l2lll(tau, mu, mu, e, sminputs, Vnu, Theta, m_nu, *Param["M_1"], *Param["M_2"], *Param["M_3"], *Param["mH"]);

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

    // Form factors for to mu - e conversion
    void RHN_mue_FF(const SMInputs sminputs, std::vector<double> &mnu, Eigen::Matrix<std::complex<double>,3,6> &U, const double mH, std::complex<double> &g0SL, std::complex<double> &g0SR, std::complex<double> &g0VL, std::complex<double> &g0VR, std::complex<double> &g1SL, std::complex<double> &g1SR, std::complex<double> &g1VL, std::complex<double> &g1VR)
    {
      std::vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};

      int e = 0, mu = 1;
      std::complex<double> k1r = FormFactors::K1R(mu, e, sminputs, U, mnu);
      std::complex<double> k2l = FormFactors::K2L(mu, e, sminputs, U, ml, mnu);
      std::complex<double> k2r = FormFactors::K2R(mu, e, sminputs, U, ml, mnu);

      int u = 0, d =0, s = 1;
      std::complex<double> CVLLu = FormFactors::CVLL(mu, e, u, u, sminputs, U, ml, mnu);
      std::complex<double> CVLLd = FormFactors::BVLL(mu, e, d, d, sminputs, U, ml, mnu);
      std::complex<double> CVLLs = FormFactors::BVLL(mu, e, s, s, sminputs, U, ml, mnu);
      std::complex<double> CVLRu = FormFactors::CVLR(mu, e, u, u, sminputs, U, ml, mnu);
      std::complex<double> CVLRd = FormFactors::BVLR(mu, e, d, d, sminputs, U, ml, mnu);
      std::complex<double> CVLRs = FormFactors::BVLR(mu, e, s, s, sminputs, U, ml, mnu);
      std::complex<double> CVRLu = FormFactors::CVRL(mu, e, u, u, sminputs, U, ml, mnu);
      std::complex<double> CVRLd = FormFactors::BVRL(mu, e, d, d, sminputs, U, ml, mnu);
      std::complex<double> CVRLs = FormFactors::BVRL(mu, e, s, s, sminputs, U, ml, mnu);
      std::complex<double> CVRRu = FormFactors::CVRR(mu, e, u, u, sminputs, U, ml, mnu);
      std::complex<double> CVRRd = FormFactors::BVRR(mu, e, d, d, sminputs, U, ml, mnu);
      std::complex<double> CVRRs = FormFactors::BVRR(mu, e, s, s, sminputs, U, ml, mnu);

      std::complex<double> CSLLu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml, mnu, mH);
      std::complex<double> CSLLd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      std::complex<double> CSLLs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml, mnu, mH);
      std::complex<double> CSLRu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml, mnu, mH);
      std::complex<double> CSLRd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      std::complex<double> CSLRs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml, mnu, mH);
      std::complex<double> CSRLu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml ,mnu, mH);
      std::complex<double> CSRLd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml ,mnu, mH);
      std::complex<double> CSRLs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml ,mnu, mH);
      std::complex<double> CSRRu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml ,mnu, mH);
      std::complex<double> CSRRd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      std::complex<double> CSRRs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml ,mnu, mH);

      double Qu = 2./3.;
      std::complex<double> gVLu = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qu * (0. - k2r) - 0.5*(CVLLu + CVLRu));
      std::complex<double> gSLu = -1./(sqrt(2)*sminputs.GF)*(CSLLu + CSLRu);
      std::complex<double> gVRu = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qu * (k1r - k2l) - 0.5*(CVRRu + CVRLu));
      std::complex<double> gSRu = -1./(sqrt(2)*sminputs.GF)*(CSRRu + CSRLu);

      double Qd = -1./3.;
      std::complex<double> gVLd = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qd * (0. - k2r) - 0.5*(CVLLd + CVLRd));
      std::complex<double> gSLd = -1./(sqrt(2)*sminputs.GF)*(CSLLd + CSLRd);
      std::complex<double> gVRd = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qd * (k1r - k2l) - 0.5*(CVRRd + CVRLd));
      std::complex<double> gSRd = -1./(sqrt(2)*sminputs.GF)*(CSRRd + CSRLd);

      double Qs = -1./3.;
      std::complex<double> gVLs = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qs * (0. - k2r) - 0.5*(CVLLs + CVLRs));
      std::complex<double> gSLs = -1./(sqrt(2)*sminputs.GF)*(CSLLs + CSLRs);
      std::complex<double> gVRs = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qs * (k1r - k2l) - 0.5*(CVRRs + CVRLs));
      std::complex<double> gSRs = -1./(sqrt(2)*sminputs.GF)*(CSRRs + CSRLs);

      double GVup = 2, GVdn = 2, GVdp = 1, GVun = 1, GVsp = 0, GVsn = 0;
      double GSup = 5.1, GSdn = 5.1, GSdp = 4.3, GSun = 4.3, GSsp = 2.5, GSsn = 2.5;

      g0SL = 0.5*(gSLu*(GSup + GSun) + gSLd*(GSdp + GSdn) + gSLs*(GSsp + GSsn));
      g0SR = 0.5*(gSRu*(GSup + GSun) + gSRd*(GSdp + GSdn) + gSRs*(GSsp + GSsn));
      g0VL = 0.5*(gVLu*(GVup + GVun) + gVLd*(GVdp + GVdn) + gVLs*(GVsp + GVsn));
      g0VR = 0.5*(gVRu*(GVup + GVun) + gVRd*(GVdp + GVdn) + gVRs*(GVsp + GVsn));
      g1SL = 0.5*(gSLu*(GSup - GSun) + gSLd*(GSdp - GSdn) + gSLs*(GSsp - GSsn));
      g1SR = 0.5*(gSRu*(GSup - GSun) + gSRd*(GSdp - GSdn) + gSRs*(GSsp - GSsn));
      g1VL = 0.5*(gVLu*(GVup - GVun) + gVLd*(GVdp - GVdn) + gVLs*(GVsp - GVsn));
      g1VR = 0.5*(gVRu*(GVup - GVun) + gVRd*(GVdp - GVdn) + gVRs*(GVsp - GVsn));

    }

    // Contribution to mu - e conversion in Ti nuclei from RHNs
    void RHN_mueTi(double &result)
    {
      using namespace Pipes::RHN_mueTi;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      std::vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<std::complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      std::complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);

      // Parameters for Ti, from Table 1 in 1209.2679 for Ti
      double Z = 22, N = 26;
      double Zeff = 17.6, Fp = 0.54;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 2.59e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (std::norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + std::norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));

    }

    // Contribution to mu - e conversion in Au nuclei from RHNs
    void RHN_mueAu(double &result)
    {
      using namespace Pipes::RHN_mueAu;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      std::vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<std::complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      std::complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);


      // Parameters for Au, from Table 1 in 1209.2679 for Au
      double Z = 79, N = 118;
      double Zeff = 33.5, Fp = 0.16;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 13.07e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (std::norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + std::norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));

    }


    // Contribution to mu - e conversion in Pb nuclei from RHNs
    void RHN_muePb(double &result)
    {
      using namespace Pipes::RHN_muePb;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      std::vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<std::complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      std::complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);

      // Parameters for Pb, from Table 1 in 1209.2679 for Pb
      double Z = 82, N = 126;
      double Zeff = 34., Fp = 0.15;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 13.45e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (std::norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + std::norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));
    }


    /// Likelihood for l -> l gamma processes
    void l2lgamma_likelihood(double &result)
    {
      using namespace Pipes::l2lgamma_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[3];
      double theory[3];

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // mu -> e gamma
        fread.read_yaml_measurement("flav_data.yaml", "BR_muegamma");
        // tau -> e gamma
        fread.read_yaml_measurement("flav_data.yaml", "BR_tauegamma");
        // tau -> mu gamma
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumugamma");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 3; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::muegamma;
     if(flav_debug) std::cout << "mu- -> e- gamma = " << theory[0] << std::endl;
     theory[1] = *Dep::tauegamma;
     if(flav_debug) std::cout << "tau- -> e- gamma = " << theory[1] << std::endl;
     theory[2] = *Dep::taumugamma;
     if(flav_debug) std::cout << "tau- -> mu- gamma = " << theory[2] << std::endl;

     result = 0;
     for (int i = 0; i < 3; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);

    }

    /// Likelihood for l -> l l l processes
    void l2lll_likelihood(double &result)
    {
      using namespace Pipes::l2lll_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[7];
      double theory[7];


      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // mu- -> e- e- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_mueee");
        // tau- -> e- e- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taueee");
        // tau- -> mu- mu- mu+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumumumu");
        // tau- -> mu- e- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumuee");
        // tau- -> e- e- mu+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taueemu");
        // tau- -> e- mu- mu+
        fread.read_yaml_measurement("flav_data.yaml", "BR_tauemumu");
        // tau- -> mu- mu- e+
        fread.read_yaml_measurement("flav_data.yaml", "BR_taumumue");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 7; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::mueee;
     if(flav_debug) std::cout << "mu-  -> e-  e-  e+  = " << theory[0] << std::endl;
     theory[1] = *Dep::taueee;
     if(flav_debug) std::cout << "tau- -> e-  e-  e+  = " << theory[1] << std::endl;
     theory[2] = *Dep::taumumumu;
     if(flav_debug) std::cout << "tau- -> mu- mu- mu+ = " << theory[2] << std::endl;
     theory[3] = *Dep::taumuee;
     if(flav_debug) std::cout << "tau- -> mu- e-  e-  = " << theory[3] << std::endl;
     theory[4] = *Dep::taueemu;
     if(flav_debug) std::cout << "tau- -> e-  e-  mu+ = " << theory[4] << std::endl;
     theory[5] = *Dep::tauemumu;
     if(flav_debug) std::cout << "tau- -> e-  mu- mu+ = " << theory[5] << std::endl;
     theory[6] = *Dep::taumumue;
     if(flav_debug) std::cout << "tau- -> mu- mu- e+  = " << theory[6] << std::endl;

     result = 0;
     for (int i = 0; i < 7; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);

    }

    /// Likelihood for mu - e conversion in nuclei
    void mu2e_likelihood(double &result)
    {
      using namespace Pipes::mu2e_likelihood;

      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static int n_measurements = 3;
      static double th_err[3];
      double theory[3];


      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        // mu - e (Ti)
        fread.read_yaml_measurement("flav_data.yaml", "R_mueTi");
        // mu - e (Au)
        fread.read_yaml_measurement("flav_data.yaml", "R_mueAu");
        // mu - e (Pb)
        fread.read_yaml_measurement("flav_data.yaml", "R_muePb");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < n_measurements; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

      theory[0] = *Dep::mueTi;
      if(flav_debug) std::cout << "mu - e (Ti) = " << theory[0] << std::endl;
      theory[1] = *Dep::mueAu;
      if(flav_debug) std::cout << "mu - e (Au) = " << theory[1] << std::endl;
      theory[2] = *Dep::muePb;
      if(flav_debug) std::cout << "mu - e (Pb) = " << theory[2] << std::endl;

      result = 0;
      for (int i = 0; i < n_measurements; ++i)
        result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);

    }

    /// HEPLike LogLikelihood RD RDstar
    // TODO: Recognised sub-capabilities:
    //    RD
    //    RDstar
    void HEPLike_RDRDstar_LogLikelihood(double& result)
    {
      using namespace Pipes::HEPLike_RDRDstar_LogLikelihood;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/HFLAV_18/Semileptonic/RD_RDstar.yaml";
      static HepLike_default::HL_nDimGaussian nDimGaussian(inputfile);
      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        nDimGaussian.Read();
        first = false;
      }

      // TODO: SuperIso is not ready to give correlations for these observables. So currently we fall back to the old way.
      //       Below code is for future reference.
      // static std::vector<str> obs_list = Downstream::subcaps->getNames();
      // flav_prediction prediction = *Dep::prediction_RDRDstar;
      // flav_observable_map theory = prediction.central_values;
      // flav_covariance_map theory_covariance = prediction.covariance;

      // result = nDimGaussian.GetLogLikelihood(get_obs_theory(prediction, obs_list), get_obs_covariance(prediction, obs_list));
      const std::vector<double> theory{*Dep::RD, *Dep::RDstar};
      result = nDimGaussian.GetLogLikelihood(theory /* , theory_covariance */);
      if (flav_debug) std::cout << "HEPLike_RDRDstar_LogLikelihood result: " << result << std::endl;
    }

    /// HEPLike single-observable likelihood
    #define HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(name, file)                            \
    void CAT_3(HEPLike_,name,_LogLikelihood)(double &result)                      \
    {                                                                             \
      using namespace CAT_3(Pipes::HEPLike_,name,_LogLikelihood);                 \
      static const std::string inputfile = path_to_latest_heplike_data() + file;  \
      static HepLike_default::HL_Gaussian gaussian(inputfile);                    \
      static bool first = true;                                                   \
                                                                                  \
      if (first)                                                                  \
      {                                                                           \
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " <<      \
         inputfile << std::endl;                                                       \
        gaussian.Read();                                                          \
        first = false;                                                            \
      }                                                                           \
                                                                                  \
      double theory = CAT(Dep::prediction_,name)->central_values.begin()->second; \
      double theory_variance = CAT(Dep::prediction_,name)->covariance.begin()->   \
       second.begin()->second;                                                    \
      result = gaussian.GetLogLikelihood(theory, theory_variance);                \
                                                                                  \
      if (flav_debug) std::cout << "HEPLike_" << #name                            \
       << "_LogLikelihood result: " << result << std::endl;                       \
    }                                                                             \

    HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(b2sgamma, "/data/HFLAV_18/RD/b2sgamma.yaml")
    HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(B2Kstargamma, "/data/HFLAV_18/RD/B2Kstar_gamma_BR.yaml")
    HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(B2taunu, "/data/PDG/Semileptonic/B2TauNu.yaml")

    /// HEPLike LogLikelihood B -> ll (CMS)
    /// Recognised sub-capabilities:
    ///    BRuntag_Bsmumu
    ///    BR_Bdmumu
    void HEPLike_B2mumu_LogLikelihood_CMS(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_CMS;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/CMS/RD/B2MuMu/CMS-PAS-BPH-16-004.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);
      static bool first = true;

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_CMS result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> ll (ATLAS)
    /// Recognised sub-capabilities:
    ///    BRuntag_Bsmumu
    ///    BR_Bdmumu
    void HEPLike_B2mumu_LogLikelihood_Atlas(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_Atlas;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/ATLAS/RD/B2MuMu/CERN-EP-2018-291.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_Atlas result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> ll (LHCb)
    /// Recognised sub-capabilities:
    ///    BRuntag_Bsmumu
    ///    BR_Bdmumu
    void HEPLike_B2mumu_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/B2MuMu/CERN-EP-2017-100.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angluar (ATLAS)
    /// Recognised sub-capabilities:
    ///   FL
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    void HEPLike_B2KstarmumuAng_LogLikelihood_Atlas(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_Atlas;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/ATLAS/RD/Bd2KstarMuMu_Angular/CERN-EP-2017-161_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        HepLike_default::HL_nDimGaussian(inputfile + "0.1_2.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.0_4.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_8.0.yaml"),
      };

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimGaussian.size(); ++i)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << std::endl;
          nDimGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        *Dep::prediction_B2KstarmumuAng_0p1_2_Atlas,
        *Dep::prediction_B2KstarmumuAng_2_4_Atlas,
        *Dep::prediction_B2KstarmumuAng_4_8_Atlas,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }
      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_Atlas result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (CMS)
    /// Recognised sub-capabilities:
    ///   P1
    ///   P5prime
    void HEPLike_B2KstarmumuAng_LogLikelihood_CMS(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_CMS;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/CMS/RD/Bd2KstarMuMu_Angular/CERN-EP-2017-240_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian = {
        HepLike_default::HL_nDimBifurGaussian(inputfile+"1.0_2.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"2.0_4.3.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"4.3_6.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"6.0_8.68.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"10.09_12.86.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"14.18_16.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"16.0_19.0.yaml")
      };

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << std::endl;
          nDimBifurGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        *Dep::prediction_B2KstarmumuAng_1_2_CMS,
        *Dep::prediction_B2KstarmumuAng_2_4p3_CMS,
        *Dep::prediction_B2KstarmumuAng_4p3_6_CMS,
        *Dep::prediction_B2KstarmumuAng_6_8p68_CMS,
        *Dep::prediction_B2KstarmumuAng_10p09_12p86_CMS,
        *Dep::prediction_B2KstarmumuAng_14p18_16_CMS,
        *Dep::prediction_B2KstarmumuAng_16_19_CMS
      };

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_CMS result: " << result << std::endl;
    }


    /// HEPLike LogLikelihood B -> K* mu mu Angular (Belle)
    /// Recognised sub-capabilities:
    ///   P4prime
    ///   P5prime
    void HEPLike_B2KstarmumuAng_LogLikelihood_Belle(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_Belle;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/Belle/RD/Bd2KstarMuMu_Angular/KEK-2016-54_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian = {
        HepLike_default::HL_nDimBifurGaussian(inputfile + "0.1_4.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "4.0_8.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "10.09_12.9.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "14.18_19.0.yaml"),
      };

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << std::endl;
          nDimBifurGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction =
      {
        *Dep::prediction_B2KstarmumuAng_0p1_4_Belle,
        *Dep::prediction_B2KstarmumuAng_4_8_Belle,
        *Dep::prediction_B2KstarmumuAng_10p9_12p9_Belle,
        *Dep::prediction_B2KstarmumuAng_14p18_19_Belle,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_Belle result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* ell ell Angular (Belle)
    /// Recognised sub-capabilities:
    ///   P4prime
    ///   P5prime
    void HEPLike_B2KstarellellAng_LogLikelihood_Belle(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarellellAng_LogLikelihood_Belle;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/Belle/RD/Bd2KstarEllEll_Angular/KEK-2016-54_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian =
      {
        HepLike_default::HL_nDimBifurGaussian(inputfile + "0.1_4.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "4.0_8.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "10.09_12.9.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "14.18_19.0.yaml"),
      };

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << std::endl;
          nDimBifurGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction =
      {
        *Dep::prediction_B2KstarmumuAng_0p1_4_Belle,
        *Dep::prediction_B2KstarmumuAng_4_8_Belle,
        *Dep::prediction_B2KstarmumuAng_10p9_12p9_Belle,
        *Dep::prediction_B2KstarmumuAng_14p18_19_Belle,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarellellAng_LogLikelihood_Belle result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    /// Recognised sub-capabilities:
    ///   FL
    ///   AFB
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    ///   S9
    void HEPLike_B2KstarmumuAng_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/PH-EP-2015-314_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian = {
        HepLike_default::HL_nDimBifurGaussian(inputfile + "0.1_0.98.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "1.1_2.5.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "2.5_4.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "4.0_6.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "6.0_8.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "15.0_19.yaml"),
      };

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << std::endl;
          nDimBifurGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        *Dep::prediction_B2KstarmumuAng_0p1_0p98_LHCb,
        *Dep::prediction_B2KstarmumuAng_1p1_2p5_LHCb,
        *Dep::prediction_B2KstarmumuAng_2p5_4_LHCb,
        *Dep::prediction_B2KstarmumuAng_4_6_LHCb,
        *Dep::prediction_B2KstarmumuAng_6_8_LHCb,
        *Dep::prediction_B2KstarmumuAng_15_19_LHCb,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    /// Recognised sub-capabilities:
    ///   FL
    ///   AFB
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    ///   S9
    void HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/CERN-EP-2020-027_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        HepLike_default::HL_nDimGaussian(inputfile + "0.1_0.98.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "1.1_2.5.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.5_4.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_6.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "6.0_8.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "15.0_19.0.yaml"),
      };

      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << std::endl;
          nDimGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        *Dep::prediction_B2KstarmumuAng_0p1_0p98_LHCb,
        *Dep::prediction_B2KstarmumuAng_1p1_2p5_LHCb,
        *Dep::prediction_B2KstarmumuAng_2p5_4_LHCb,
        *Dep::prediction_B2KstarmumuAng_4_6_LHCb,
        *Dep::prediction_B2KstarmumuAng_6_8_LHCb,
        *Dep::prediction_B2KstarmumuAng_15_19_LHCb,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_LHCb 2020 result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* e e Angular low q2 (LHCb)
    /// Recognised sub-capabilities:
    ///   FLee
    ///   AT_Re
    ///   AT_2
    ///   AT_Im
    void HEPLike_B2KstareeAng_Lowq2_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_B2KstareeAng_Lowq2_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarEE_Angular/CERN-EP-2020-176.yaml";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");
      static HepLike_default::HL_nDimGaussian nDimGaussian(inputfile);
      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        nDimGaussian.Read();
        first = false;
      }
      flav_prediction prediction = *Dep::prediction_B2KstareeAng_0p0008_0p257_LHCb;
      if (flav_debug)
      {
        std::cout<<"Have prediction"<<std::endl;
        for (unsigned int i=0; i <obs_list.size(); i++)
        {
          std::cout<<obs_list[i]<<std::endl;
        }
      }

      result = nDimGaussian.GetLogLikelihood(get_obs_theory(prediction, obs_list), get_obs_covariance(prediction, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2KstareeAng_Lowq_LogLikelihood result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood Bu -> K*+ mu mu Angular (LHCb)
    /// Recognised sub-capabilities:
    ///   FL
    ///   AFB
    ///   S3
    ///   S4
    ///   S5
    ///   S7
    ///   S8
    ///   S9
    void HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bu2KstarMuMu_Angular/CERN-EP-2020-239_q2_";
      static std::vector<str> obs_list = Downstream::subcaps->getNames();
      if (obs_list.empty()) FlavBit_error().raise(LOCAL_INFO, "No subcapabilities specified!");
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        HepLike_default::HL_nDimGaussian(inputfile + "0.1_0.98.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "1.1_2.5.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.5_4.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_6.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "6.0_8.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "15.0_19.0.yaml"),
      };

      static bool first = true;
      if (first)
        {
          for (unsigned int i = 0; i < nDimGaussian.size(); i++)
            {
              if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << std::endl;
              nDimGaussian[i].Read();
            }
          update_obs_list(obs_list, nDimGaussian[0].GetObservables());
          first = false;
        }

      std::vector<flav_prediction> prediction =
      {
        *Dep::prediction_B2KstarmumuAng_0p1_0p98_LHCb,
        *Dep::prediction_B2KstarmumuAng_1p1_2p5_LHCb,
        *Dep::prediction_B2KstarmumuAng_2p5_4_LHCb,
        *Dep::prediction_B2KstarmumuAng_4_6_LHCb,
        *Dep::prediction_B2KstarmumuAng_6_8_LHCb,
        *Dep::prediction_B2KstarmumuAng_15_19_LHCb,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list),
         get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_Bu2KstarmumuAng_LogLikelihood_LHCb 2020 result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Br (LHCb)
    void HEPLike_B2KstarmumuBr_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuBr_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Br/CERN-EP-2016-141_q2_";
      static std::vector<HepLike_default::HL_BifurGaussian> BifurGaussian = {
        HepLike_default::HL_BifurGaussian(inputfile + "0.1_0.98.yaml"),
        HepLike_default::HL_BifurGaussian(inputfile + "1.1_2.5.yaml"),
        HepLike_default::HL_BifurGaussian(inputfile + "2.5_4.yaml"),
        HepLike_default::HL_BifurGaussian(inputfile + "4_6.yaml"),
        HepLike_default::HL_BifurGaussian(inputfile + "6_8.yaml"),
        HepLike_default::HL_BifurGaussian(inputfile + "15_19.yaml")
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < BifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << std::endl;
          BifurGaussian[i].Read();
        }
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        *Dep::prediction_B2KstarmumuBr_0p1_0p98,
        *Dep::prediction_B2KstarmumuBr_1p1_2p5,
        *Dep::prediction_B2KstarmumuBr_2p5_4,
        *Dep::prediction_B2KstarmumuBr_4_6,
        *Dep::prediction_B2KstarmumuBr_6_8,
        *Dep::prediction_B2KstarmumuBr_15_19
      };

      result = 0;

      for (unsigned int i = 0; i < BifurGaussian.size(); i++)
      {
        double theory = prediction[i].central_values.begin()->second;
        double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        result += BifurGaussian[i].GetLogLikelihood(theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K+ mu mu Br (LHCb)
    void HEPLike_B2KmumuBr_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KmumuBr_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/B2KMuMu_Br/CERN-PH-EP-2012-263_q2_";
      static std::vector<HepLike_default::HL_Gaussian> Gaussian = {
        HepLike_default::HL_Gaussian(inputfile + "0.05_2.yaml"),
        HepLike_default::HL_Gaussian(inputfile + "2_4.3.yaml"),
        HepLike_default::HL_Gaussian(inputfile + "4.3_8.68.yaml"),
        HepLike_default::HL_Gaussian(inputfile + "14.18_16.yaml"),
        HepLike_default::HL_Gaussian(inputfile + "16_18.yaml"),
        HepLike_default::HL_Gaussian(inputfile + "18_22.yaml")
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < Gaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << std::endl;
          Gaussian[i].Read();
        }
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        *Dep::prediction_B2KmumuBr_0p05_2,
        *Dep::prediction_B2KmumuBr_2_4p3,
        *Dep::prediction_B2KmumuBr_4p3_8p68,
        *Dep::prediction_B2KmumuBr_14p18_16,
        *Dep::prediction_B2KmumuBr_16_18,
        *Dep::prediction_B2KmumuBr_18_22
      };

      result = 0;

      for (unsigned int i = 0; i < Gaussian.size(); i++)
      {
        double theory = prediction[i].central_values.begin()->second;
        double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        result += Gaussian[i].GetLogLikelihood(theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_B2KmumuBR_LogLikelihood_LHCb result: " << result << std::endl;
    }


    void HEPLike_Bs2phimumuBr_LogLikelihood(double &result)
    {
      using namespace Pipes::HEPLike_Bs2phimumuBr_LogLikelihood;

      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bs2PhiMuMu_Br/CERN-PH-EP-2015-145_";
      static std::vector<HepLike_default::HL_BifurGaussian> BifurGaussian = {
        HepLike_default::HL_BifurGaussian(inputfile + "1_6.yaml"),
        HepLike_default::HL_BifurGaussian(inputfile + "15_19.yaml")
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < BifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << std::endl;
          BifurGaussian[i].Read();
        }
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        *Dep::prediction_Bs2phimumuBr_1_6,
        *Dep::prediction_Bs2phimumuBr_15_19
      };

      result = 0;
      for (unsigned int i = 0; i < BifurGaussian.size(); i++)
      {
        double theory = prediction[i].central_values.begin()->second;
        double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        result += BifurGaussian[i].GetLogLikelihood(theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_Bs2phimumuBr_LogLikelihood result: " << result << std::endl;
    }


    void HEPLike_RK_LogLikelihood_LHCb(double &result)
    {
     using namespace Pipes::HEPLike_RK_LogLikelihood_LHCb;

      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Rk/CERN-EP-2019-043.yaml";
      static HepLike_default::HL_ProfLikelihood ProfLikelihood(inputfile);

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << std::endl;
        ProfLikelihood.Read();

        first = false;
      }

      const double theory = *Dep::RK;
      const double theory_variance = 0.001;

      result = ProfLikelihood.GetLogLikelihood(theory, theory_variance);

      if (flav_debug) std::cout << "HEPLike_RK_LogLikelihood_LHC_LHCb result: " << result << std::endl;
    }


    void HEPLike_RKstar_LogLikelihood_LHCb(double &result)
    {

      using namespace Pipes::HEPLike_RKstar_LogLikelihood_LHCb;

      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/RKstar/CERN-EP-2017-100_q2_";
      static std::vector<HepLike_default::HL_ProfLikelihood> ProfLikelihood;

      std::vector<double> prediction = {*Dep::RKstar_0045_11, *Dep::RKstar_11_60};
      std::vector<str> bins = {"0.045_1.1", "1.1_6"};

      static bool first = true;
      if (first)
      {
        for(str bin : bins)
        {
          ProfLikelihood.push_back(HepLike_default::HL_ProfLikelihood(inputfile + bin + ".yaml"));
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " <<  inputfile + bin + ".yaml"  << std::endl;
          ProfLikelihood[ProfLikelihood.size()-1].Read();

        }
        first = false;
      }

      result = 0;
      for (unsigned int i = 0; i < ProfLikelihood.size(); i++)
      {
        const double theory = prediction[i];
        const double theory_variance = 0.0;
        result += ProfLikelihood[i].GetLogLikelihood(theory, theory_variance);
      }

      if (flav_debug) std::cout << "HEPLike_RKstar_LogLikelihood_LHCb result: " << result << std::endl;

    }

  }
}
