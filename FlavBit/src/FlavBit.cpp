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
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2020 June-December
///  \date 2021 Jan-April
//
///  \author Douglas Jacob
///          (douglas.jacob@monash.edu)
///  \date 2020 Nov
///
///  \author Filip Rajec
///          (filip.rajec@adelaide.edu.au)
///  \date 2020 Apr
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

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/Elements/loop_functions.hpp"
#include "gambit/Elements/translator.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/thdm_slhahelp.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/FlavBit_types.hpp"
#include "gambit/FlavBit/Flav_reader.hpp"
#include "gambit/FlavBit/Kstarmumu_theory_err.hpp"
#include "gambit/FlavBit/flav_utils.hpp"

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

    using namespace std;
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

    // printing function
    void print(flav_prediction prediction , vector<std::string > names)
    {
      for(unsigned i=0; i<names.size(); i++)
        {
          cout<<names[i]<<": "<<prediction.central_values[names[i]]<<endl;
        }
      cout<<"Covariance:"<<endl;
      for( unsigned i=0; i<names.size(); i++)
        {
          stringstream row;
          for( unsigned j=0; j<names.size(); j++)
            {
              row<<(prediction.covariance)[names[i]]  [names[j]]<<" ";
            }
          cout<<row.str()<<endl;
        }
    }

    /// Translate B->K*mumu observables from theory to LHCb convention
    void Kstarmumu_Theory2Experiment_translation(flav_observable_map& prediction)
    {
      vector<std::string > names={"S4", "S7", "S9", "A4", "A7", "A9"};
      for (unsigned i=0; i < names.size(); i++)
      {
        auto search = prediction.find( names[i]);
        if (search != prediction.end()) {
          prediction[names[i]]=(-1.)*prediction[names[i]];
        }
      }
    }

    /// Translate B->K*mumu covariances from theory to LHCb convention
    void Kstarmumu_Theory2Experiment_translation(flav_covariance_map& prediction)
    {
      vector<std::string > names={"S4", "S7", "S9", "A4", "A7", "A9"};
      vector<std::string > names_exist;

      for (unsigned i=0; i < names.size(); i++)
      {
        auto search_i = prediction.find(names[i]);
        if (search_i != prediction.end()) names_exist.push_back(names[i]);
      }
      //changing the rows:
      for (unsigned i=0; i <  names_exist.size(); i++)
      {
        string name1=names_exist[i];
        std::map<const std::string, double> row=prediction[name1];
        for (std::map<const std::string, double>::iterator it=row.begin(); it !=row.end(); it++)
        {
          prediction[name1][it->first]=(-1.)*prediction[name1][it->first];
        }
      }
      // changing the columns:
      for (flav_covariance_map::iterator it=prediction.begin(); it !=prediction.end(); it++)
      {
        string name_columns=it->first;
        for (unsigned i=0; i <  names_exist.size(); i++)
        {
          string name1=names_exist[i];
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
    void SI_fill(parameters &result)
    {
      using namespace Pipes::SI_fill;
      using namespace std;

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
      else if(ModelInUse("THDM") or ModelInUse("THDMatQ"))
      {
        // Obtain SLHAea object
        spectrum = Dep::THDM_spectrum->getSLHAea(2);
        // Add the MODSEL block if it is not provided by the spectrum object.
        SLHAea_add(spectrum,"MODSEL",1, 10, "THDM", false);
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
         
          case 10:
          
            // THDM model parameter
            if(spectrum["FMODSEL"][1].is_data_line()) result.THDM_model=(SLHAea::to<int>(spectrum["FMODSEL"][1][1]) - 30);
            if (result.THDM_model == 0) result.THDM_model=10;
            if(spectrum["FMODSEL"][5].is_data_line()) result.CPV=SLHAea::to<int>(spectrum["FMODSEL"][5][1]);
            if(spectrum["MINPAR"][3].is_data_line())  result.tan_beta=SLHAea::to<double>(spectrum["MINPAR"][3][1]);
            if(spectrum["MINPAR"][18].is_data_line()) result.m12=SLHAea::to<double>(spectrum["MINPAR"][18][1]);
            if(spectrum["ALPHA"][0].is_data_line()) result.alpha=SLHAea::to<double>(spectrum["ALPHA"][0][1]);
            if (!spectrum["MSOFT"].empty()) { 
              if (!spectrum["MSOFT"].front().empty()) result.MSOFT_Q=SLHAea::to<double>(spectrum["MSOFT"].front().at(3));
            }
            for(int i=1; i<4; i++)
            {
              for(int j=1;j<4;j++)
              {  
                result.lambda_u[i][j] = SLHAea::to<double>(spectrum["YU1"].at(i,j)[2]);
                result.lambda_d[i][j] = SLHAea::to<double>(spectrum["YD1"].at(i,j)[2]);
                result.lambda_l[i][j] = SLHAea::to<double>(spectrum["YE1"].at(i,j)[2]);
              }
            }

            break;
          
          default:
          {
            if (spectrum["MINPAR"][3].is_data_line()) result.tan_beta=SLHAea::to<double>(spectrum["MINPAR"][3][1]);
            break;
          }
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
         if (spectrum["STOPMIX"][max(ie,je)].is_data_line()) result.stop_mix[ie][je]=SLHAea::to<double>(spectrum["STOPMIX"].at(ie,je)[2]);
        if (!spectrum["SBOTMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["SBOTMIX"][max(ie,je)].is_data_line()) result.sbot_mix[ie][je]=SLHAea::to<double>(spectrum["SBOTMIX"].at(ie,je)[2]);
        if (!spectrum["STAUMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["STAUMIX"][max(ie,je)].is_data_line()) result.stau_mix[ie][je]=SLHAea::to<double>(spectrum["STAUMIX"].at(ie,je)[2]);
        if (!spectrum["NMIX"].empty()) for (ie=1;ie<=4;ie++) for (je=1;je<=4;je++)
         if (spectrum["NMIX"][max(ie,je)].is_data_line()) result.neut_mix[ie][je]=SLHAea::to<double>(spectrum["NMIX"].at(ie,je)[2]);
        if (!spectrum["NMNMIX"].empty()) for (ie=1;ie<=5;ie++) for (je=1;je<=5;je++)
         if (spectrum["NMNMIX"][max(ie,je)].is_data_line()) result.neut_mix[ie][je]=SLHAea::to<double>(spectrum["NMNMIX"].at(ie,je)[2]);
        if (!spectrum["UMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["UMIX"][max(ie,je)].is_data_line()) result.charg_Umix[ie][je]=SLHAea::to<double>(spectrum["UMIX"].at(ie,je)[2]);
        if (!spectrum["VMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["VMIX"][max(ie,je)].is_data_line()) result.charg_Vmix[ie][je]=SLHAea::to<double>(spectrum["VMIX"].at(ie,je)[2]);

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
         if (spectrum["NMHMIX"][max(ie,je)].is_data_line()) result.H0_mix[ie][je]=SLHAea::to<double>(spectrum["NMHMIX"].at(ie,je)[2]);

        if (!spectrum["NMAMIX"].empty()) for (ie=1;ie<=2;ie++) for (je=1;je<=2;je++)
         if (spectrum["NMAMIX"][max(ie,je)].is_data_line()) result.A0_mix[ie][je]=SLHAea::to<double>(spectrum["NMAMIX"].at(ie,je)[2]);

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
         if (spectrum["USQMIX"][max(ie,je)].is_data_line()) result.sU_mix[ie][je]=SLHAea::to<double>(spectrum["USQMIX"].at(ie,je)[2]);
        if (!spectrum["DSQMIX"].empty()) for (ie=1;ie<=6;ie++) for (je=1;je<=6;je++)
         if (spectrum["DSQMIX"][max(ie,je)].is_data_line()) result.sD_mix[ie][je]=SLHAea::to<double>(spectrum["DSQMIX"].at(ie,je)[2]);
        if (!spectrum["SELMIX"].empty()) for (ie=1;ie<=6;ie++) for (je=1;je<=6;je++)
         if (spectrum["SELMIX"][max(ie,je)].is_data_line()) result.sE_mix[ie][je]=SLHAea::to<double>(spectrum["SELMIX"].at(ie,je)[2]);
        if (!spectrum["SNUMIX"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["SNUMIX"][max(ie,je)].is_data_line()) result.sNU_mix[ie][je]=SLHAea::to<double>(spectrum["SNUMIX"].at(ie,je)[2]);

        if (!spectrum["MSQ2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSQ2"][max(ie,je)].is_data_line()) result.sCKM_msq2[ie][je]=SLHAea::to<double>(spectrum["MSQ2"].at(ie,je)[2]);
        if (!spectrum["MSL2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSL2"][max(ie,je)].is_data_line()) result.sCKM_msl2[ie][je]=SLHAea::to<double>(spectrum["MSL2"].at(ie,je)[2]);
        if (!spectrum["MSD2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSD2"][max(ie,je)].is_data_line()) result.sCKM_msd2[ie][je]=SLHAea::to<double>(spectrum["MSD2"].at(ie,je)[2]);
        if (!spectrum["MSU2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSU2"][max(ie,je)].is_data_line()) result.sCKM_msu2[ie][je]=SLHAea::to<double>(spectrum["MSU2"].at(ie,je)[2]);
        if (!spectrum["MSE2"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["MSE2"][max(ie,je)].is_data_line()) result.sCKM_mse2[ie][je]=SLHAea::to<double>(spectrum["MSE2"].at(ie,je)[2]);

        if (!spectrum["IMVCKM"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["IMVCKM"][max(ie,je)].is_data_line()) result.IMCKM[ie][je]=SLHAea::to<double>(spectrum["IMVCKM"].at(ie,je)[2]);
        if (!spectrum["IMVCKM"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["IMVCKM"][max(ie,je)].is_data_line()) result.IMCKM[ie][je]=SLHAea::to<double>(spectrum["IMVCKM"].at(ie,je)[2]);

        if (!spectrum["UPMNS"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["UPMNS"][max(ie,je)].is_data_line()) result.PMNS_U[ie][je]=SLHAea::to<double>(spectrum["UPMNS"].at(ie,je)[2]);

        if (!spectrum["TU"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["TU"][max(ie,je)].is_data_line()) result.TU[ie][je]=SLHAea::to<double>(spectrum["TU"].at(ie,je)[2]);
        if (!spectrum["TD"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["TD"][max(ie,je)].is_data_line()) result.TD[ie][je]=SLHAea::to<double>(spectrum["TD"].at(ie,je)[2]);
        if (!spectrum["TE"].empty()) for (ie=1;ie<=3;ie++) for (je=1;je<=3;je++)
         if (spectrum["TE"][max(ie,je)].is_data_line()) result.TE[ie][je]=SLHAea::to<double>(spectrum["TE"].at(ie,je)[2]);
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
      if (ModelInUse("THDMatQ"))
      {
        result.Re_DeltaC2  = Dep::DeltaC7->real();
        result.Im_DeltaC7  = Dep::DeltaC2->imag();
        result.Re_DeltaC7  = Dep::DeltaC7->real();
        result.Im_DeltaC7  = Dep::DeltaC7->imag();
        result.Re_DeltaC8  = Dep::DeltaC8->real();
        result.Im_DeltaC8  = Dep::DeltaC8->imag();
        result.Re_DeltaC9  = Dep::DeltaC9->real();
        result.Im_DeltaC9  = Dep::DeltaC9->imag();
        result.Re_DeltaC10 = Dep::DeltaC10->real();
        result.Im_DeltaC10 = Dep::DeltaC10->imag();
        result.Re_DeltaCQ1 = Dep::DeltaCQ1->real();
        result.Im_DeltaCQ1 = Dep::DeltaCQ1->imag();
        result.Re_DeltaCQ2 = Dep::DeltaCQ2->real();
        result.Im_DeltaCQ2 = Dep::DeltaCQ2->imag();
        // Prime WCs
        result.Re_DeltaC7_Prime  = Dep::DeltaC7_Prime->real();
        result.Im_DeltaC7_Prime  = Dep::DeltaC7_Prime->imag();
        result.Re_DeltaC8_Prime  = Dep::DeltaC8_Prime->real();
        result.Im_DeltaC8_Prime  = Dep::DeltaC8_Prime->imag();
        result.Re_DeltaC9_Prime  = Dep::DeltaC9_Prime->real();
        result.Im_DeltaC9_Prime  = Dep::DeltaC9_Prime->imag();
        
        result.Re_DeltaCQ1_Prime = Dep::DeltaCQ1_Prime->real();
        result.Im_DeltaCQ1_Prime = Dep::DeltaCQ1_Prime->imag();
        result.Re_DeltaCQ2_Prime = Dep::DeltaCQ2_Prime->real();
        result.Im_DeltaCQ2_Prime = Dep::DeltaCQ2_Prime->imag();
      }     
      if (flav_debug) cout<<"Finished SI_fill"<<endl;
    }   
     /// Delta CQ1 at tree level for the general THDM
    void calculate_DeltaCQ1(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaCQ1;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double alpha = spectrum.get(Par::dimensionless,"alpha");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double sinb = sin(beta), cosb = cos(beta);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      const double mZ = Dep::SMINPUTS->mZ;
      const double mW = Dep::SMINPUTS->mW;
      const double SW = sqrt(1-pow(mW/mZ,2));
      double Ybs = spectrum.get(Par::dimensionless,"Yd2",3,2);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double xi_mumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      double xi_bs = Ybs/cosb;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      result = mBmB*(pow(pi,2)*xi_bs*(-((pow(mh,2) - pow(mH,2))*xi_mumu*cos(2*(alpha-beta))) +
               pow(2,0.75)*sqrt(sminputs.GF)*(pow(mh,2) - pow(mH,2))*mMu*sin(2*alpha-beta) +
               (pow(mh,2) + pow(mH,2))*(xi_mumu - pow(2,0.75)*sqrt(sminputs.GF)*mMu*sinb)))/
               (4.*pow(sminputs.GF,2)*pow(mh,2)*pow(mH,2)*pow(mW,2)*pow(SW,2)*Vtb*Vts*cosb*cosb);     
    }    
   
    void calculate_DeltaCQ1_Prime(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaCQ1_Prime;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double alpha = spectrum.get(Par::dimensionless,"alpha");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double sinb = sin(beta), cosb = cos(beta);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      const double mZ = Dep::SMINPUTS->mZ;
      const double mW = Dep::SMINPUTS->mW;
      const double SW = sqrt(1-pow(mW/mZ,2));
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double xi_mumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      double xi_sb = Ysb/cosb;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      result = mBmB*(pow(pi,2)*xi_sb*(-((pow(mh,2) - pow(mH,2))*xi_mumu*cos(2*(alpha-beta))) +
               pow(2,0.75)*sqrt(sminputs.GF)*(pow(mh,2) - pow(mH,2))*mMu*sin(2*alpha-beta) +
               (pow(mh,2) + pow(mH,2))*(xi_mumu - pow(2,0.75)*sqrt(sminputs.GF)*mMu*sinb)))/
               (4.*pow(sminputs.GF,2)*pow(mh,2)*pow(mH,2)*pow(mW,2)*pow(SW,2)*Vtb*Vts*cosb*cosb);
    }

     /// Delta CQ2 at tree level for the general THDM
    void calculate_DeltaCQ2(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaCQ2;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double sinb = sin(beta), cosb = cos(beta);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mBmB = Dep::SMINPUTS->mBmB;
      const double mZ = Dep::SMINPUTS->mZ;
      const double mW = Dep::SMINPUTS->mW;
      const double SW = sqrt(1-pow(mW/mZ,2));
      double mA = spectrum.get(Par::Pole_Mass,"A0");
      double Ybs = spectrum.get(Par::dimensionless,"Yd2",3,2);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double xi_mumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      double xi_bs = Ybs/cosb;
      //CKM elements
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      result = mBmB*(pow(pi,2)*xi_bs*(-xi_mumu + pow(2,0.75)*sqrt(sminputs.GF)*mMu*sinb))/
               (2.*pow(sminputs.GF,2)*pow(mA,2)*pow(mW,2)*pow(SW,2)*Vtb*Vts*cosb*cosb);
    }

   void calculate_DeltaCQ2_Prime(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaCQ2_Prime;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double sinb = sin(beta), cosb = cos(beta);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mBmB = Dep::SMINPUTS->mBmB;
      const double mZ = Dep::SMINPUTS->mZ;
      const double mW = Dep::SMINPUTS->mW;
      const double SW = sqrt(1-pow(mW/mZ,2));
      double mA = spectrum.get(Par::Pole_Mass,"A0");
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double xi_mumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      double xi_sb = Ysb/cosb;
      //CKM elements
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      result = -mBmB*(pow(pi,2)*xi_sb*(-xi_mumu + pow(2,0.75)*sqrt(sminputs.GF)*mMu*sinb))/
               (2.*pow(sminputs.GF,2)*pow(mA,2)*pow(mW,2)*pow(SW,2)*Vtb*Vts*cosb*cosb);
    }
    //Green functios for Delta C7 in THDM
    double F7_1(double t)
    {
        if(fabs(1.-t)<1.e-5) return F7_1(0.9999);
        return -((7 - 12*t - 3*t*t + 8*t*t*t +
           6*t*(-2 + 3*t)*log(1/t)))/(72.*pow(-1 + t,4));
    }

    double F7_2(double t)
    {
    if(fabs(1.-t)<1.e-5) return F7_2(0.9999);
        return sqrt(t)*(3 - 8*t + 5*t*t + (-4 + 6*t)*log(1/t))/
           (12.*pow(-1 + t,3));
    }
    double F7_3 (double t)
    {
    if (fabs (1. - t) < 1.e-5) return F7_3 (0.9999);
        return -(3*t*(-2*log (1/t) + 1) - 6*t*t + t*t*t + 2)/(24.* pow (-1 + t, 4));
    }

    double F7_4 (double t)
    {
    if (fabs (1. - t) < 1.e-5) return F7_4 (0.9999);
        return sqrt(t)*(-2*log (1/t) + 3 - 4*t + t*t)/(4.*pow (-1 + t, 3));
    }

    /// Delta C2 from the general THDM
    void calculate_DeltaC2(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC2;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double mC = Dep::SMINPUTS->mCmC;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      //Yukawa couplings
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xi_tc = Ytc/cosb;
      double xi_bb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xi_sb = Ysb/cosb;
      double xi_cc = -((sqrt(2)*mC*tanb)/v) + Ycc/cosb;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      std::complex<double> C2diag = (-7.*(xi_cc*conj(Vcs) + xi_tc*conj(Vts))*(Vcb*conj(xi_cc) + Vtb*conj(xi_tc)))/(72.*sqrt(2)*sminputs.GF*pow(mHp,2)*Vtb*Vts);

      std::complex<double> C2mix = -(mC*(xi_bb*conj(Vcb) + xi_sb*conj(Vcs))*(xi_cc*conj(Vcs) + xi_tc*conj(Vts))*(3 + 4*log(pow(mBmB,2)/pow(mHp,2))))/(12.*sqrt(2)*sminputs.GF*mBmB*pow(mHp,2)*Vtb*Vts);

      result = C2diag + C2mix;

    }


    /// Delta C7 from the general THDM
    void calculate_DeltaC7(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC7;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      //Yukawa couplings
      double Ytt = spectrum.get(Par::dimensionless,"Yu2",3,3);
      double Yct = spectrum.get(Par::dimensionless,"Yu2",2,3);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xi_tt = -((sqrt(2)*mT*tanb)/v) + Ytt/cosb;
      double xi_ct = Yct/cosb;
      double xi_bb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xi_sb = Ysb/cosb;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      std::complex<double> C70 = (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mHp))*((xi_ct*conj(Vcs) + xi_tt*conj(Vts))*
               (Vcb*conj(xi_ct) + Vtb*conj(xi_tt))*F7_1(pow(mT/mHp,2)))
               + (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mBmB))*((Vtb*xi_bb + Vts*xi_sb)*
               (conj(Vcs)*conj(xi_ct) + conj(Vts)*conj(xi_tt))*F7_2(pow(mT/mHp,2)));

      result = C70;

    }


    /// Delta C8 from the general THDM
    void calculate_DeltaC8(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC8;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      //Yukawa couplings
      double Ytt = spectrum.get(Par::dimensionless,"Yu2",3,3);
      double Yct = spectrum.get(Par::dimensionless,"Yu2",2,3);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xi_tt = -((sqrt(2)*mT*tanb)/v) + Ytt/cosb;
      double xi_ct = Yct/cosb;
      double xi_bb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xi_sb = Ysb/cosb;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);

      std::complex<double> C80 = (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mHp))*((xi_ct*conj(Vcs) + xi_tt*conj(Vts))*
               (Vcb*conj(xi_ct) + Vtb*conj(xi_tt))*F7_3(pow(mT/mHp,2)))
               + (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mBmB))*((Vtb*xi_bb + Vts*xi_sb)*
               (conj(Vcs)*conj(xi_ct) + conj(Vts)*conj(xi_tt))*F7_4(pow(mT/mHp,2)));

      result = C80;

    }

    //Green functios for Delta C9 and Delta C10 in THDM
    //Gamma penguin Green function
    double DHp(double t)
    {
     if(fabs(1.-t)<1.e-5) return DHp(0.9999);

         return -(-38 + 117*t - 126*t*t + 47*pow(t,3) +
            6*(4 - 6*t + 3*pow(t,3))*log(1/t))/
           (108.*pow(t-1,4));
    }
    //Z penguin Green function
    double CHp(double t)
    {
         if(fabs(1.-t)<1.e-5) return CHp(0.9999);

         return -t*(-1 + t + log(1/t))/(8.*pow(t-1,2));
    }
    //Zmix  penguin Green function
    double CHpmix(double t)
    {    
         if(fabs(1.-t)<1.e-5) return CHpmix(0.9999);
         
         return t*(-1 + t*t +2*t*log(1/t))/(pow(t-1,3));
    }

    //Box diagram Green function
    double BHp(double t)
    {
         if(fabs(1.-t)<1.e-5) return BHp(0.9999);

         return (-1 + t + t*log(1/t))/(16.*pow(t-1,2));
    }

    //Box diagram Green function for C9' and C10'
    double BHpp(double t)
    {
         if(fabs(1.-t)<1.e-5) return BHpp(0.9999);

         return ((-1 + t + t*log(1/t)))/(16.*pow(t-1,2));
    }
    
    //Function for GTHDM WCs 9,10 and primes
    void THDM_DeltaC_NP(int wc, int l, int lp, SMInputs sminputs, dep_bucket<SMInputs> *sminputspointer, Spectrum spectrum, std::complex<double> &result)
    {
      const double tanb = spectrum.get(Par::dimensionless,"tanb");
      const double beta = atan(tanb);
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double cosb = cos(beta);
      const double mMu = (*sminputspointer)->mMu;
      const double mTau = (*sminputspointer)->mTau;
      const double mBmB = (*sminputspointer)->mBmB;
      const double mS = (*sminputspointer)->mS;
      const double mCmC = (*sminputspointer)->mCmC;
      const double mT = (*sminputspointer)->mT;
      const double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double mW = (*sminputspointer)->mW;
      const double mZ = (*sminputspointer)->mZ;
      const double SW = sqrt(1 - pow(mW/mZ,2));
      const double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      const double Ymutau = spectrum.get(Par::dimensionless,"Ye2",2,3);
      const double Ytaumu = spectrum.get(Par::dimensionless,"Ye2",3,2);
      const double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      const double Ytt = spectrum.get(Par::dimensionless,"Yu2",3,3);
      const double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      const double Yct = spectrum.get(Par::dimensionless,"Yu2",2,3);
      const double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      const double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      const double Ybs = spectrum.get(Par::dimensionless,"Yd2",3,2);
      const double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      const double Yss = spectrum.get(Par::dimensionless,"Yd2",2,2);
      const double A      = (*sminputspointer)->CKM.A;
      const double lambda = (*sminputspointer)->CKM.lambda;
      //const double rhobar = (*sminputspointer)->CKM.rhobar;
      //const double etabar = (*sminputspointer)->CKM.etabar;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vub = 0;//This should be improved to call directly an Eigen object
      const double Vus = lambda;
      const double xi_tt = -((sqrt(2)*mT*tanb)/v) + Ytt/cosb;
      const double xi_cc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      const double xi_tc = Ytc/cosb;
      const double xi_ct = Yct/cosb;
      const double xi_bb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      const double xi_ss = -((sqrt(2)*mS*tanb)/v) + Yss/cosb;
      const double xi_sb = Ysb/cosb;
      const double xi_bs = Ybs/cosb;
      const double xi_mumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      const double xi_mutau = Ymutau/cosb;
      const double xi_taumu = Ytaumu/cosb;
      const double xi_tautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;

      Eigen::Matrix3cd xi_L;

      xi_L << 0,       0,       0,
              0,  xi_mumu, xi_mutau,
              0, xi_taumu, xi_tautau;

      Eigen::Vector3cd xil_m1 = xi_L.col(1);
      Eigen::Vector3cd xil_m1conj = xil_m1.conjugate();
      Eigen::Vector3cd xilp_m2 = xi_L.col(2);


      std::complex<double> C9_gamma = (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mHp))*(xi_ct*conj(Vcs) + xi_tt*conj(Vts))*
                                      (Vcb*conj(xi_ct) + Vtb*conj(xi_tt))*DHp(pow(mT/mHp,2));        
      std::complex<double> C9_Z =  ((4*SW*SW-1)/(sqrt(2)*mW*mW*SW*SW*real(Vtb*conj(Vts))*sminputs.GF))*(xi_ct*conj(Vcs) + xi_tt*conj(Vts))*
                                  (Vcb*conj(xi_ct) + Vtb*conj(xi_tt))*CHp(pow(mT/mHp,2));
      std::complex<double> C9_Zmix = (mBmB*(4*SW*SW-1)*(xi_bb*conj(Vtb) + xi_sb*conj(Vts))*(Vcs*conj(xi_ct) + Vts*conj(xi_tt)))*CHpmix(pow(mT/mHp,2))/(16.*sqrt(2)*sminputs.GF*mT*pow(mW,2)*pow(SW,2)*Vtb*conj(Vts));
  
      std::complex<double> C10_Ztotal = (1/(4*SW*SW-1))*(C9_Z+C9_Zmix);

      std::complex<double> C9p_gamma = (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mHp))*((Vtb*xi_bb + Vts*xi_sb)*(Vtb*xi_bs + Vts*xi_ss))*DHp(pow(mT/mHp,2));

      std::complex<double> C9p_Z = ((4*SW*SW-1)/(sqrt(2)*mW*mW*SW*SW*real(Vtb*conj(Vts))*sminputs.GF))*((Vtb*xi_bb + Vts*xi_sb)*(Vtb*xi_bs + Vts*xi_ss))*CHp(pow(mT/mHp,2));

      std::complex<double> C10p_Z = (1/(4*SW*SW-1))*C9p_Z;

      switch(wc)
      {
        case 9:
           if((l==1 && lp==2)||(l==2 && lp==1))
           {
           std::complex<double> C9_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(xil_m1conj.dot(xilp_m2))*(conj(Vcs)*(Vcb*xi_cc*conj(xi_cc) + Vcb*xi_ct*conj(xi_ct) + Vtb*xi_cc*conj(xi_tc) + Vtb*xi_ct*conj(xi_tt)) + conj(Vts)*(Vcb*xi_tc*conj(xi_cc) + Vcb*xi_tt*conj(xi_ct) + Vtb*xi_tc*conj(xi_tc) + Vtb*xi_tt*conj(xi_tt)))*BHp(pow(mT/mHp,2));
      
           result = C9_gamma + C9_Z + C9_Zmix + C9_Box;
           }
           else
           {
           std::complex<double> C9_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(pow(xi_mumu,2) + pow(xi_taumu,2))*(conj(Vcs)*(Vcb*xi_cc*conj(xi_cc) + Vcb*xi_ct*conj(xi_ct) + Vtb*xi_cc*conj(xi_tc) + Vtb*xi_ct*conj(xi_tt)) + conj(Vts)*(Vcb*xi_tc*conj(xi_cc) + Vcb*xi_tt*conj(xi_ct) + Vtb*xi_tc*conj(xi_tc) + Vtb*xi_tt*conj(xi_tt)))*BHp(pow(mT/mHp,2));
    
           result = C9_gamma + C9_Z + C9_Zmix + C9_Box;
           } 
           break;

        case 10:
           if((l==1 && lp==2)||(l==2 && lp==1))
           {
           std::complex<double> C10_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(xil_m1conj.dot(xilp_m2))*(conj(Vcs)*(Vcb*xi_cc*conj(xi_cc) + Vcb*xi_ct*conj(xi_ct) + Vtb*xi_cc*conj(xi_tc) + Vtb*xi_ct*conj(xi_tt)) + conj(Vts)*(Vcb*xi_tc*conj(xi_cc) + Vcb*xi_tt*conj(xi_ct) + Vtb*xi_tc*conj(xi_tc) + Vtb*xi_tt*conj(xi_tt)))*BHp(pow(mT/mHp,2));

           result = C10_Ztotal + C10_Box;
           }
           else
           {
           std::complex<double> C10_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp))*(pow(xi_mumu,2) + pow(xi_taumu,2))*(conj(Vcs)*(Vcb*xi_cc*conj(xi_cc) + Vcb*xi_ct*conj(xi_ct) + Vtb*xi_cc*conj(xi_tc) + Vtb*xi_ct*conj(xi_tt)) + conj(Vts)*(Vcb*xi_tc*conj(xi_cc) + Vcb*xi_tt*conj(xi_ct) + Vtb*xi_tc*conj(xi_tc) + Vtb*xi_tt*conj(xi_tt)))*BHp(pow(mT/mHp,2));

           result = C10_Ztotal + C10_Box;
           }
           break;

        case 11://C9prime
           if((l==1 && lp==2)||(l==2 && lp==1))
           {
           std::complex<double> C9p_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp)*((xil_m1conj.dot(xilp_m2))*(((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcb) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vtb) + (Vub*xi_bb + Vus*xi_sb)*conj(Vub))*conj(xi_bs) + ((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcs) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vts) + (Vub*xi_bb + Vus*xi_sb)*conj(Vus))*conj(xi_ss)))*BHpp(pow(mT/mHp,2)));
           result = C9p_gamma + C9p_Z + C9p_Box;//C9p_Zmix contribution is suppressed by the strange quark mass
           }
           else
           {
           std::complex<double> C9p_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp)*((pow(xi_mumu,2) + pow(xi_taumu,2))*(((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcb) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vtb) + (Vub*xi_bb + Vus*xi_sb)*conj(Vub))*conj(xi_bs) + ((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcs) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vts) + (Vub*xi_bb + Vus*xi_sb)*conj(Vus))*conj(xi_ss)))*BHpp(pow(mT/mHp,2)));

           result = C9p_gamma + C9p_Z + C9p_Box;//C9p_Zmix contribution is suppressed by the strange quark mass
           }
           break;

        case 12://C10prime
           if((l==1 && lp==2)||(l==2 && lp==1))
           {
           std::complex<double> C10p_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp)*((xil_m1conj.dot(xilp_m2))*(((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcb) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vtb) + (Vub*xi_bb + Vus*xi_sb)*conj(Vub))*conj(xi_bs) + ((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcs) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vts) + (Vub*xi_bb + Vus*xi_sb)*conj(Vus))*conj(xi_ss)))*BHpp(pow(mT/mHp,2)));
           result = C10p_Z + C10p_Box;
           }
           else
           {
           std::complex<double> C10p_Box = (1/(2*mW*mW*SW*SW*real(Vtb*conj(Vts))*pow(sminputs.GF,2)*mHp*mHp)*((pow(xi_mumu,2) + pow(xi_taumu,2))*(((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcb) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vtb) + (Vub*xi_bb + Vus*xi_sb)*conj(Vub))*conj(xi_bs) + ((Vcb*xi_bb + Vcs*xi_sb)*conj(Vcs) + (Vtb*xi_bb + Vts*xi_sb)*conj(Vts) + (Vub*xi_bb + Vus*xi_sb)*conj(Vus))*conj(xi_ss)))*BHpp(pow(mT/mHp,2)));
           
           result = C10p_Z + C10p_Box;
           }
           break;

      }
    }

    /// Delta C9 from the general THDM
    void calculate_DeltaC9(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC9; 
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      THDM_DeltaC_NP(9, l, lp, sminputs, sminputspointer, spectrum, result);
    }

      /// Delta C10 from the general THDM
    void calculate_DeltaC10(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC10;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      THDM_DeltaC_NP(10, l, lp, sminputs, sminputspointer, spectrum, result);
    }

 
    /// Delta C9' from the general THDM
    void calculate_DeltaC9_Prime(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC9_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      THDM_DeltaC_NP(11, l, lp, sminputs, sminputspointer, spectrum, result);
    }

    /// Delta C10' from the general THDM
    void calculate_DeltaC10_Prime(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC10_Prime;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 1;

      THDM_DeltaC_NP(12, l, lp, sminputs, sminputspointer, spectrum, result);
    }

    // Delta C7' from the GTHDM
    void calculate_DeltaC7_Prime(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC7_Prime;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      //Yukawa couplings
      double Ytt = spectrum.get(Par::dimensionless,"Yu2",3,3);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xi_tt = -((sqrt(2)*mT*tanb)/v) + Ytt/cosb;
      double xi_bb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xi_sb = Ysb/cosb;
      double xi_tc = Ytc/cosb;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vcb = A*lambda*lambda;

      std::complex<double> C7p0 =  (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mHp))*(xi_sb*conj(Vtb))*(Vtb*xi_bb + Vts*xi_sb)*F7_1(pow(mT/mHp,2))
               +(1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mBmB))*(Vtb*xi_sb)*(Vcb*conj(xi_tc) + Vtb*conj(xi_tt))*F7_2(pow(mT/mHp,2));

      result = C7p0;

    }

    // Delta C8' from the GTHDM
    void calculate_DeltaC8_Prime(std::complex<double> &result)
    {
      using namespace Pipes::calculate_DeltaC8_Prime;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double mT = Dep::SMINPUTS->mT;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      //Yukawa couplings
      double Ytt = spectrum.get(Par::dimensionless,"Yu2",3,3);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xi_tt = -((sqrt(2)*mT*tanb)/v) + Ytt/cosb;
      double xi_bb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xi_sb = Ysb/cosb;
      double xi_tc = Ytc/cosb;
      const double Vts = -A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      const double Vcb = A*lambda*lambda;

      std::complex<double> C8p0 =  (1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mHp))*(xi_sb*conj(Vtb))*(Vtb*xi_bb + Vts*xi_sb)*F7_3(pow(mT/mHp,2))
                 +(1/(sqrt(2)*real(Vtb*conj(Vts))*sminputs.GF*mHp*mBmB))*(Vtb*xi_sb)*(Vcb*conj(xi_tc) + Vtb*conj(xi_tt))*F7_4(pow(mT/mHp,2));


      result = C8p0;

    }

    ///  B-> D tau nu distributions in GTHDM
    double THDM_dGammaBDlnu(double gs, double q2)
    {
	  const double mB = 5.27961;
	  const double mD = 1.870;
	  const double ml = 1.77686;
          const double mb = 4.18;
          const double mc = 1.28;
          const double GF = 1.16638e-5;
          const double Vcb = 0.041344392;
	  
	  const double rho_D2 = 1.186;
	  const double V1_1 = 1.074;
	  const double Delta = 1;
	
          double C_V1=0.;
          double C_V2=0.;
          double C_T=0.;
	 
	  double lambda_D=((mB-mD)*(mB-mD)-q2)*((mB+mD)*(mB+mD)-q2);

	  double r_D=mD/mB;
	  double w=(mB*mB+mD*mD-q2)/2./mB/mD;
	  double z=(sqrt(w+1.)-sqrt(2.))/(sqrt(w+1.)+sqrt(2.));

	  double V1=V1_1*(1.-8.*rho_D2*z+(51.*rho_D2-10.)*z*z-(252.*rho_D2-84.)*z*z*z);
	  double S1=V1*(1.+Delta*(-0.019+0.041*(w-1.)-0.015*(w-1.)*(w-1.)));

	  double hp=1./2./(1.+r_D*r_D-2.*r_D*w)*(-(1.+r_D)*(1.+r_D)*(w-1.)*V1+(1.-r_D)*(1.-r_D)*(w+1.)*S1);
	  double hm=(1.-r_D*r_D)*(w+1.)/2./(1.+r_D*r_D-2.*r_D*w)*(S1-V1);
	  double hT=(mb+mc)/(mB+mD)*(hp-(1.+r_D)/(1.-r_D)*hm);

	  double F_1=1./2./sqrt(mB*mD)*((mB+mD)*hp-(mB-mD)*hm);
	  double F_0=1./2./sqrt(mB*mD)*(((mB+mD)*(mB+mD)-q2)/(mB+mD)*hp-((mB-mD)*(mB-mD)-q2)/(mB-mD)*hm);
	  double F_T=(mB+mD)/2./sqrt(mB*mD)*hT;
	
	  double Hs_V0=sqrt(lambda_D/q2)*F_1;
	  double Hs_Vt=(mB*mB-mD*mD)/sqrt(q2)*F_0;
	  double Hs_S=(mB*mB-mD*mD)/(mb-mc)*F_0;
	  double Hs_T=-sqrt(lambda_D)/(mB+mD)*F_T;
	

	  double dGamma_dq2=std::norm(pow(GF*Vcb,2.)/192./pow(pi,3.)/pow(mB,3.)*q2*sqrt(lambda_D)*pow(1.-ml*ml/q2,2.)*
	  (pow(1.+C_V1+C_V2,2.)*((1.+ml*ml/2./q2)*Hs_V0*Hs_V0+3./2.*ml*ml/q2*Hs_Vt*Hs_Vt)
	  +3./2.*pow(gs,2.)*Hs_S*Hs_S+8.*pow(C_T,2.)*(1.+2.*ml*ml/q2)*Hs_T*Hs_T
	  +3.*(1.+C_V1+C_V2)*conj(gs)*ml/sqrt(q2)*Hs_S*Hs_Vt
	  -12.*(1.+C_V1+C_V2)*conj(C_T)*ml/sqrt(q2)*Hs_T*Hs_V0));
	
	
      return dGamma_dq2;

    }
                
    ///  B->D* tau nu distributions in GTHDM
    double THDM_dGammaBDstarlnu(double gp, double q2)
    {
      
	  const double mB = 5.27961;
	  const double mDs = 2.007;
          const double ml = 1.77686;
          const double mb = 4.18;
          const double mc = 1.28;
          const double GF = 1.16638e-5;
          const double Vcb = 0.041344392;
	  
	  const double rho_Dstar2=1.214;
	  const double R1_1=1.403;
	  const double R2_1=0.864;
	  const double R3_1=0.97;
	  const double hA1_1=0.921;
      
          double C_V1=0.;
          double C_V2=0.;
          double C_T=0.;

	  double lambda_Ds=((mB-mDs)*(mB-mDs)-q2)*((mB+mDs)*(mB+mDs)-q2);

	  double r_Dstar=mDs/mB;
	  double w=(mB*mB+mDs*mDs-q2)/2./mB/mDs;
	  double z=(sqrt(w+1.)-sqrt(2.))/(sqrt(w+1.)+sqrt(2.));

	  double hA1=hA1_1*(1.-8.*rho_Dstar2*z+(53.*rho_Dstar2-15.)*z*z-(231.*rho_Dstar2-91.)*z*z*z);
	  double R1=R1_1-0.12*(w-1.)+0.05*(w-1.)*(w-1.);
	  double R2=R2_1-0.11*(w-1.)-0.06*(w-1.)*(w-1.);
	  double R3=R3_1-0.052*(w-1.)+0.026*(w-1.)*(w-1.);

          double hV=R1*hA1;
	  double hA2=(R2-R3)/2./r_Dstar*hA1;
	  double hA3=(R2+R3)/2.*hA1;

	  double hT1=1./2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*(1.-r_Dstar)*(1.-r_Dstar)*(w+1.)*hA1-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*(w-1.)*hV);
	  double hT2=(1.-r_Dstar*r_Dstar)*(w+1.)/2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*hA1-(mb+mc)/(mB+mDs)*hV);
	  double hT3=-1./2./(1.+r_Dstar)/(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(2.*(mb-mc)/(mB-mDs)*r_Dstar*(w+1.)*hA1-(mb-mc)/(mB-mDs)*(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(hA3-r_Dstar*hA2)-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*hV);
 
	  double V=(mB+mDs)/2./sqrt(mB*mDs)*hV;
	  double A_1=((mB+mDs)*(mB+mDs)-q2)/2./sqrt(mB*mDs)/(mB+mDs)*hA1;
	  double A_2=(mB+mDs)/2./sqrt(mB*mDs)*(hA3+mDs/mB*hA2);
	  double A_0=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/2./mDs*hA1-(mB*mB-mDs*mDs+q2)/2./mB*hA2-(mB*mB-mDs*mDs-q2)/2./mDs*hA3);	
	  double T_1=1./2./sqrt(mB*mDs)*((mB+mDs)*hT1-(mB-mDs)*hT2);
	  double T_2=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/(mB+mDs)*hT1-((mB-mDs)*(mB-mDs)-q2)/(mB-mDs)*hT2);
	  double T_3=1./2./sqrt(mB*mDs)*((mB-mDs)*hT1-(mB+mDs)*hT2-2.*(mB*mB-mDs*mDs)/mB*hT3);
	
	  double H_Vp=(mB+mDs)*A_1-sqrt(lambda_Ds)/(mB+mDs)*V;
	  double H_Vm=(mB+mDs)*A_1+sqrt(lambda_Ds)/(mB+mDs)*V;
	  double H_V0=(mB+mDs)/2./mDs/sqrt(q2)*(-(mB*mB-mDs*mDs-q2)*A_1+lambda_Ds/pow(mB+mDs,2)*A_2);
	  double H_Vt=-sqrt(lambda_Ds/q2)*A_0;
	  double H_S=-sqrt(lambda_Ds)/(mb+mc)*A_0;
	  double H_Tp=1./sqrt(q2)*((mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
	  double H_Tm=1./sqrt(q2)*(-(mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
	  double H_T0=1./2./mDs*(-(mB*mB+3.*mDs*mDs-q2)*T_2+lambda_Ds/(mB*mB-mDs*mDs)*T_3);
	  
	  double dGamma_dq2=std::norm(pow(GF*Vcb,2.)/192./pow(pi,3.)/pow(mB,3.)*q2*sqrt(lambda_Ds)*pow(1.-ml*ml/q2,2.)*
	  ((pow(1.+C_V1,2.)+pow(C_V2,2.))*((1.+ml*ml/2./q2)*(H_Vp*H_Vp+H_Vm*H_Vm+H_V0*H_V0)+3./2.*ml*ml/q2*H_Vt*H_Vt)
	  -2.*(1.+C_V1)*conj(C_V2)*((1.+ml*ml/2./q2)*(H_V0*H_V0+2.*H_Vp*H_Vm)+3./2.*ml*ml/q2*H_Vt*H_Vt)
	  +3./2.*pow(gp,2.)*H_S*H_S+8.*pow(C_T,2.)*(1.+2.*ml*ml/q2)*(H_Tp*H_Tp+H_Tm*H_Tm+H_T0*H_T0)
	  +3.*(1.+C_V1-C_V2)*(gp)*ml/sqrt(q2)*H_S*H_Vt
	  -12.*(1.+C_V1)*conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vp-H_Tm*H_Vm)
	  +12.*C_V2*conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vm-H_Tm*H_Vp)));
	  
      return dGamma_dq2;
    }
    
     
    ///  B->D* tau nu distribution for FLDstar
    double THDM_dFLDstar(double gp, double q2)
    {
      
	  const double mB = 5.27961;
	  const double mDs = 2.007;
          const double ml = 1.77686;
          const double mb = 4.18;
          const double mc = 1.28;
          const double GF = 1.16638e-5;
          const double Vcb = 0.041344392;
	  
	  const double rho_Dstar2=1.214;
	  const double R1_1=1.403;
	  const double R2_1=0.864;
	  const double R3_1=0.97;
	  const double hA1_1=0.921;
      
          double C_V1=0.;
          double C_V2=0.;
          double C_T=0.;

	  double lambda_Ds=((mB-mDs)*(mB-mDs)-q2)*((mB+mDs)*(mB+mDs)-q2);

	  double r_Dstar=mDs/mB;
	  double w=(mB*mB+mDs*mDs-q2)/2./mB/mDs;
	  double z=(sqrt(w+1.)-sqrt(2.))/(sqrt(w+1.)+sqrt(2.));

	  double hA1=hA1_1*(1.-8.*rho_Dstar2*z+(53.*rho_Dstar2-15.)*z*z-(231.*rho_Dstar2-91.)*z*z*z);
	  double R1=R1_1-0.12*(w-1.)+0.05*(w-1.)*(w-1.);
	  double R2=R2_1-0.11*(w-1.)-0.06*(w-1.)*(w-1.);
	  double R3=R3_1-0.052*(w-1.)+0.026*(w-1.)*(w-1.);

          double hV=R1*hA1;
	  double hA2=(R2-R3)/2./r_Dstar*hA1;
	  double hA3=(R2+R3)/2.*hA1;

	  double hT1=1./2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*(1.-r_Dstar)*(1.-r_Dstar)*(w+1.)*hA1-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*(w-1.)*hV);
	  double hT2=(1.-r_Dstar*r_Dstar)*(w+1.)/2./(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*((mb-mc)/(mB-mDs)*hA1-(mb+mc)/(mB+mDs)*hV);
	  double hT3=-1./2./(1.+r_Dstar)/(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(2.*(mb-mc)/(mB-mDs)*r_Dstar*(w+1.)*hA1-(mb-mc)/(mB-mDs)*(1.+r_Dstar*r_Dstar-2.*r_Dstar*w)*(hA3-r_Dstar*hA2)-(mb+mc)/(mB+mDs)*(1.+r_Dstar)*(1.+r_Dstar)*hV);
 
	  double V=(mB+mDs)/2./sqrt(mB*mDs)*hV;
	  double A_1=((mB+mDs)*(mB+mDs)-q2)/2./sqrt(mB*mDs)/(mB+mDs)*hA1;
	  double A_2=(mB+mDs)/2./sqrt(mB*mDs)*(hA3+mDs/mB*hA2);
	  double A_0=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/2./mDs*hA1-(mB*mB-mDs*mDs+q2)/2./mB*hA2-(mB*mB-mDs*mDs-q2)/2./mDs*hA3);	
	  double T_1=1./2./sqrt(mB*mDs)*((mB+mDs)*hT1-(mB-mDs)*hT2);
	  double T_2=1./2./sqrt(mB*mDs)*(((mB+mDs)*(mB+mDs)-q2)/(mB+mDs)*hT1-((mB-mDs)*(mB-mDs)-q2)/(mB-mDs)*hT2);
	  double T_3=1./2./sqrt(mB*mDs)*((mB-mDs)*hT1-(mB+mDs)*hT2-2.*(mB*mB-mDs*mDs)/mB*hT3);
	
	  double H_Vp=(mB+mDs)*A_1-sqrt(lambda_Ds)/(mB+mDs)*V;
	  double H_Vm=(mB+mDs)*A_1+sqrt(lambda_Ds)/(mB+mDs)*V;
	  double H_V0=(mB+mDs)/2./mDs/sqrt(q2)*(-(mB*mB-mDs*mDs-q2)*A_1+lambda_Ds/pow(mB+mDs,2)*A_2);
	  double H_Vt=-sqrt(lambda_Ds/q2)*A_0;
	  double H_S=-sqrt(lambda_Ds)/(mb+mc)*A_0;
	  double H_Tp=1./sqrt(q2)*((mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
	  double H_Tm=1./sqrt(q2)*(-(mB*mB-mDs*mDs)*T_2+sqrt(lambda_Ds)*T_1);
	  double H_T0=1./2./mDs*(-(mB*mB+3.*mDs*mDs-q2)*T_2+lambda_Ds/(mB*mB-mDs*mDs)*T_3);
	  
	  double dGamma_dq2=std::norm(pow(GF*Vcb,2.)/192./pow(pi,3.)/pow(mB,3.)*q2*sqrt(lambda_Ds)*pow(1.-ml*ml/q2,2.)*
	  ((pow(1.+C_V1,2.)+pow(C_V2,2.))*((1.+ml*ml/2./q2)*(H_V0*H_V0)+3./2.*ml*ml/q2*H_Vt*H_Vt)
	  -2.*(1.+C_V1)*conj(C_V2)*((1.+ml*ml/2./q2)*(H_V0*H_V0)+3./2.*ml*ml/q2*H_Vt*H_Vt)
	  +3./2.*pow(gp,2.)*H_S*H_S+8.*pow(C_T,2.)*(1.+2.*ml*ml/q2)*(H_Tp*H_Tp+H_Tm*H_Tm+H_T0*H_T0)
	  +3.*(1.+C_V1-C_V2)*(gp)*ml/sqrt(q2)*H_S*H_Vt
	  -12.*(1.+C_V1)*conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vp-H_Tm*H_Vm)
	  +12.*C_V2*conj(C_T)*ml/sqrt(q2)*(H_T0*H_V0+H_Tp*H_Vm-H_Tm*H_Vp)));
	  
      return dGamma_dq2;
    }
    

    //Partial decay width for B->D l nu computed with Simpson's rule
    double Gamma_BDlnu(double gs, int n)
    {
      const double a = 1.77686*1.77686;//mTau^2
      const double b = 3.40961*3.40961;//(mB-mD)^2	
      double h = (b-a)/n;
      double sum_odds = 0.0;
      for (int i = 1; i < n; i += 2)
      {
        sum_odds += THDM_dGammaBDlnu(gs, a + i * h);
      }
      double sum_evens = 0.0;
      for (int i = 2; i < n; i += 2)
      {
        sum_evens += THDM_dGammaBDlnu(gs, a + i * h);
      }
      return (THDM_dGammaBDlnu(gs, a) + THDM_dGammaBDlnu(gs, b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
    }
      
    //Partial decay width for B->D* l nu computed with Simpson's rule
    double Gamma_BDstarlnu(double gp, int n)
    {
      const double a = 1.77686*1.77686;//mTau^2
      const double b = 3.27261*3.27261;//(mB-mDs)^2      
      double h = (b-a)/n;
      double sum_odds = 0.0;
      for (int i = 1; i < n; i += 2)
      {
        sum_odds += THDM_dGammaBDstarlnu(gp, a + i * h);
      }
      double sum_evens = 0.0;
      for (int i = 2; i < n; i += 2)
      {
        sum_evens += THDM_dGammaBDstarlnu(gp, a + i * h);
      }
      return (THDM_dGammaBDstarlnu(gp, a) + THDM_dGammaBDstarlnu(gp, b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
    }

    //Partial decay width for B->D* l nu for lambda_Dstar=0 computed with Simpson's rule
    double GammaDstar_BDstarlnu(double gp, int n)
    {
      const double a = 1.77686*1.77686;//mTau^2
      const double b = 3.27261*3.27261;//(mB-mDs)^2      
      double h = (b-a)/n;
      double sum_odds = 0.0;
      for (int i = 1; i < n; i += 2)
      {
        sum_odds += THDM_dFLDstar(gp, a + i * h);
      }
      double sum_evens = 0.0;
      for (int i = 2; i < n; i += 2)
      {
        sum_evens += THDM_dFLDstar(gp, a + i * h);
      }
      return (THDM_dFLDstar(gp, a) + THDM_dFLDstar(gp, b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
    }

   // FLDstar Gamma=lambda_Dstar=0(B->D* l nu)/Gamma
    double GammaDstar_Gamma(double gp)
    { 
      double GammaDstar_Gamma = GammaDstar_BDstarlnu(gp, 13)/Gamma_BDstarlnu(gp, 13);
      
      return GammaDstar_Gamma;
    }
 
    /// FLDstar Gamma=lambda_Dstar=0(B->D* l nu)/Gamma in THMD
    void THDM_FLDstar(double &result)
    {
      using namespace Pipes::THDM_FLDstar;
      if (flav_debug) cout<<"Starting THDM_FLDstarlnu"<<endl;
      
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
     
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4); 
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double CSMcb = 4*sminputs.GF*Vcb/(sqrt(2.0));
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xitc = Ytc/cosb;
      double xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xisb = Ysb/cosb;
      double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      const double mCmC = Dep::SMINPUTS->mCmC;
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2); 
      double xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      double CRcb = -2.*std::norm((Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2));
      double CLcb = 2.*std::norm((Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*conj(xitautau)/pow(mHp,2));
      double gp =  (CRcb - CLcb)/CSMcb; 
      result = GammaDstar_Gamma(gp);
      if (flav_debug) printf("Gamma(B->D* tau nu)/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_FLDstar"<<endl;
    }


    // Normalized partial decay width  dGamma(B->D l nu)/dq2/Gamma
    void THDM_dGammaBDlnu_Gamma(double q2min, double q2max, SMInputs sminputs, dep_bucket<SMInputs> *sminputspointer, Spectrum spectrum, double &result)
    {
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double mTau = (*sminputspointer)->mTau;
      const double mBmB = (*sminputspointer)->mBmB;
      const double mCmC = (*sminputspointer)->mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      const double A      = (*sminputspointer)->CKM.A;
      const double lambda = (*sminputspointer)->CKM.lambda;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      double xitc = Ytc/cosb;
      double xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xisb = Ysb/cosb;
      double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      
      double CRcb = -2.*std::norm((Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2));
      double CLcb = 2.*std::norm((Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*conj(xitautau)/pow(mHp,2));
      const double CSMcb = 4*sminputs.GF*Vcb/(sqrt(2.0));

      double gs =  (CRcb + CLcb)/CSMcb;
      double q2 = (q2min + q2max)/2;	 

      double dGamma_dq2_Gamma = THDM_dGammaBDlnu(gs, q2)/Gamma_BDlnu(gs, 15);
      
      result = dGamma_dq2_Gamma;
    }

    // Normalized partial decay width  dGamma(B->D* l nu)/dq2/Gamma
    void THDM_dGammaBDstarlnu_Gamma(double q2min, double q2max, SMInputs sminputs, dep_bucket<SMInputs> *sminputspointer, Spectrum spectrum, double &result)
    {
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double mTau = (*sminputspointer)->mTau;
      const double mBmB = (*sminputspointer)->mBmB;
      const double mCmC = (*sminputspointer)->mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      const double A      = (*sminputspointer)->CKM.A;
      const double lambda = (*sminputspointer)->CKM.lambda;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      double xitc = Ytc/cosb;
      double xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xisb = Ysb/cosb;
      double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;

      double CRcb = -2.*std::norm((Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2));
      double CLcb = 2.*std::norm((Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*conj(xitautau)/pow(mHp,2));
      const double CSMcb = 4*sminputs.GF*Vcb/(sqrt(2.0));

      double gp =  (CRcb - CLcb)/CSMcb;
      double q2 = (q2min + q2max)/2;

      double dGamma_dq2_Gamma = THDM_dGammaBDstarlnu(gp, q2)/Gamma_BDstarlnu(gp, 13);

      result = dGamma_dq2_Gamma;

    }
      
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_40_45(double &result)
    {
      using namespace Pipes::THDM_BDlnu_40_45;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_40_45"<<endl;
      
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
     
      THDM_dGammaBDlnu_Gamma(4.0, 4.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_40_45"<<endl;
    }

    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_45_50(double &result)
    {
      using namespace Pipes::THDM_BDlnu_45_50;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_45_50"<<endl;

      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(4.5, 5.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_45_50"<<endl;
    }
       
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_50_55(double &result)
    {
      using namespace Pipes::THDM_BDlnu_50_55;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_50_55"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(5.0, 5.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_50_55"<<endl;
    }

    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_55_60(double &result)
    {
      using namespace Pipes::THDM_BDlnu_55_60;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_55_60"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(5.5, 6.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_55_60"<<endl;
    }
   
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_60_65(double &result)
    {
      using namespace Pipes::THDM_BDlnu_60_65;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_60_65"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(6.0, 6.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_60_65"<<endl;
    }

    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_65_70(double &result)
    {
      using namespace Pipes::THDM_BDlnu_65_70;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_65_70"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(6.5, 7.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_65_70"<<endl;
    }

   
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_70_75(double &result)
    {
      using namespace Pipes::THDM_BDlnu_70_75;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_70_75"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(7.0, 7.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_70_75"<<endl;
    }

    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_75_80(double &result)
    {
      using namespace Pipes::THDM_BDlnu_75_80;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_75_80"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(7.5, 8.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_75_80"<<endl;
    }
   
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_80_85(double &result)
    {
      using namespace Pipes::THDM_BDlnu_80_85;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_80_85"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(8.0, 8.5,  sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_80_85"<<endl;
    }

    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_85_90(double &result)
    {
      using namespace Pipes::THDM_BDlnu_85_90;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_85_90"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(8.5, 9.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_85_90"<<endl;
    }
    
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_90_95(double &result)
    {
      using namespace Pipes::THDM_BDlnu_90_95;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_90_95"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      
      THDM_dGammaBDlnu_Gamma(9.0, 9.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_90_95"<<endl;
    }

    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_95_100(double &result)
    {
      using namespace Pipes::THDM_BDlnu_95_100;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_95_100"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(9.5, 10.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_95_100"<<endl;
    }
   
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_100_105(double &result)
    {
      using namespace Pipes::THDM_BDlnu_100_105;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_100_105"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(10.0, 10.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_100_105"<<endl;
    }

    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_105_110(double &result)
    {
      using namespace Pipes::THDM_BDlnu_105_110;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_105_110"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(10.5, 11.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_105_110"<<endl;
    }
 
    ///  Normalized differential B-> D tau nu width
    void THDM_BDlnu_110_115(double &result)
    {
      using namespace Pipes::THDM_BDlnu_110_115;
      if (flav_debug) cout<<"Starting THDM_BRBDlnu_110_115"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDlnu_Gamma(11.0, 11.5, sminputs, sminputspointer, spectrum, result); 
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDlnu_110_115"<<endl;
    }
 
  
    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_40_45(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_40_45;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_40_45"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(4.0, 4.5, sminputs, sminputspointer, spectrum, result);     
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_40_45"<<endl;
    }

    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_45_50(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_45_50;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_45_50"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(4.5, 5.0, sminputs, sminputspointer, spectrum, result);

      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_45_50"<<endl;
    }
       
    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_50_55(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_50_55;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_50_55"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(5.0, 5.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_50_55"<<endl;
    }

    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_55_60(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_55_60;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_55_60"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(5.5, 6.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_55_60"<<endl;
    }
   
    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_60_65(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_60_65;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_60_65"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(6.0, 6.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_60_65"<<endl;
    }

    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_65_70(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_65_70;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_65_70"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(6.5, 7.0,  sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_65_70"<<endl;
    }

   
    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_70_75(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_70_75;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_70_75"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(7.0, 7.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_70_75"<<endl;
    }

    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_75_80(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_75_80;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_75_80"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(7.5, 8.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_75_80"<<endl;
    }
   
    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_80_85(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_80_85;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_80_85"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(8.0, 8.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_80_85"<<endl;
    }

    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_85_90(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_85_90;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_85_90"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(8.5, 9.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_85_90"<<endl;
    }
    
    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_90_95(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_90_95;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_90_95"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(9.0, 9.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_90_95"<<endl;
    }

    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_95_100(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_95_100;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_95_100"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(9.5, 10.0, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_95_100"<<endl;
    }
   
    ///  Normalized differential B-> D* tau nu width
    void THDM_BDstarlnu_100_105(double &result)
    {
      using namespace Pipes::THDM_BDstarlnu_100_105;
      if (flav_debug) cout<<"Starting THDM_BRBDstarlnu_100_105"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      THDM_dGammaBDstarlnu_Gamma(10.0, 10.5, sminputs, sminputspointer, spectrum, result);
      if (flav_debug) printf("dGamma(B->D tau nu)/dq2/Gamma=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_BRBDstarlnu_100_105"<<endl;
    }
   
    /// Measurements for tree-level semileptonic B decays
    void BDtaunu_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::BDtaunu_measurements;

      const int n_bins=15;
      static bool th_err_absolute[n_bins], first = true;
      static double th_err[n_bins];

      if (flav_debug) cout<<"Starting BDtaunu_measurements"<<endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="BDtaunu_likelihood";

        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in BDtaunu_measurements"<<endl;

        std::vector<string> observables;
        const vector<string> q2_bins_min_str = {"4.0", "4.5", "5.0", "5.5", "6.0","6.5","7.0","7.5","8.0","8.5","9.0","9.5","10.0","10.5","11.0"};
        const vector<string> q2_bins_max_str = {"4.5", "5.0", "5.5", "6.0", "6.5","7.0","7.5","8.0","8.5","9.0","9.5","10.0","10.5","11.0","11.5"};
        for (unsigned i=0;i<q2_bins_min_str.size();++i)
        {
         // create observable names
          observables.push_back("dBR_BDlnu_"+q2_bins_min_str[i]+"-"+q2_bins_max_str[i]);
        }

        const unsigned num_obs = observables.size();

        for (unsigned i=0;i<num_obs;++i)
        {
         // fill fread from observable names
          fread.read_yaml_measurement("flav_data.yaml", observables[i]);
        }
          
        fread.initialise_matrices();
        pmc.cov_exp=fread.get_exp_cov();
        pmc.value_exp=fread.get_exp_value();

        pmc.value_th.resize(n_bins,1);
        // Set all entries in the covariance matrix explicitly to zero, as we will only write the diagonal ones later.
        pmc.cov_th = boost::numeric::ublas::zero_matrix<double>(n_bins,n_bins);
        for (int i = 0; i < n_bins; ++i)
        {
          th_err[i] = fread.get_th_err()(i,0).first;
          th_err_absolute[i] = fread.get_th_err()(i,0).second;
        }

        pmc.dim=n_bins;

        // Init over.
        first = false;
      }

      double theory[14];
      
      theory[0] = *Dep::BDlnu_40_45;
      theory[1] = *Dep::BDlnu_45_50;
      theory[2] = *Dep::BDlnu_50_55;
      theory[3] = *Dep::BDlnu_55_60;
      theory[4] = *Dep::BDlnu_60_65;
      theory[5] = *Dep::BDlnu_65_70;
      theory[6] = *Dep::BDlnu_70_75;
      theory[7] = *Dep::BDlnu_75_80;
      theory[8] = *Dep::BDlnu_80_85;
      theory[9] = *Dep::BDlnu_85_90;
      theory[10] = *Dep::BDlnu_90_95;
      theory[11] = *Dep::BDlnu_95_100;
      theory[12] = *Dep::BDlnu_100_105;
      theory[13] = *Dep::BDlnu_105_110;
      theory[14] = *Dep::BDlnu_110_115;

      for (int i = 0; i < n_bins; ++i)
      {
        pmc.value_th(i,0) = theory[i];
        pmc.cov_th(i,i) = th_err[i]*th_err[i] * (th_err_absolute[i] ? 1.0 : theory[i]*theory[i]);
      }

      pmc.diff.clear();
      for (int i=0;i<n_bins;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) cout<<"Finished BDtaunu_measurements"<<endl;

    }

    /// Likelihood for tree-level leptonic and semileptonic B decays
    void BDtaunu_likelihood(double &result)
    {
      using namespace Pipes::BDtaunu_likelihood;

      if (flav_debug) cout<<"Starting BDtaunu_likelihood"<<endl;

      predictions_measurements_covariances pmc = *Dep::BDtaunu_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;
      //calculating a diff
      vector<double> diff;
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

      if (flav_debug) cout<<"Finished BDtaunu_likelihood"<<endl;

      if (flav_debug_LL) cout<<"Likelihood result BDtaunu_likelihood  : "<< result<<endl;

    }      
   
    /// Measurements for tree-level semileptonic B decays
    void BDstartaunu_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::BDstartaunu_measurements;

      const int n_bins=13;
      static bool th_err_absolute[n_bins], first = true;
      static double th_err[n_bins];

      if (flav_debug) cout<<"Starting BDstartaunu_measurements"<<endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="BDstartaunu_likelihood";

        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in BDstartaunu_measurements"<<endl;

        std::vector<string> observables;
        const vector<string> q2_bins_min_str = {"4.0", "4.5", "5.0", "5.5", "6.0","6.5","7.0","7.5","8.0","8.5","9.0","9.5","10.0"};
        const vector<string> q2_bins_max_str = {"4.5", "5.0", "5.5", "6.0", "6.5","7.0","7.5","8.0","8.5","9.0","9.5","10.0","10.5"};
        for (unsigned i=0;i<q2_bins_min_str.size();++i)
        {
         // create observable names
          observables.push_back("dBR_BDstarlnu_"+q2_bins_min_str[i]+"-"+q2_bins_max_str[i]);
        }

        const unsigned num_obs = observables.size();

        for (unsigned i=0;i<num_obs;++i)
        {
         // fill fread from observable names
          fread.read_yaml_measurement("flav_data.yaml", observables[i]);
        }
          
        fread.initialise_matrices();
        pmc.cov_exp=fread.get_exp_cov();
        pmc.value_exp=fread.get_exp_value();

        pmc.value_th.resize(n_bins,1);
        // Set all entries in the covariance matrix explicitly to zero, as we will only write the diagonal ones later.
        pmc.cov_th = boost::numeric::ublas::zero_matrix<double>(n_bins,n_bins);
        for (int i = 0; i < n_bins; ++i)
        {
          th_err[i] = fread.get_th_err()(i,0).first;
          th_err_absolute[i] = fread.get_th_err()(i,0).second;
        }

        pmc.dim=n_bins;

        // Init over.
        first = false;
      }

      double theory[12];
      
      theory[0] = *Dep::BDstarlnu_40_45;
      theory[1] = *Dep::BDstarlnu_45_50;
      theory[2] = *Dep::BDstarlnu_50_55;
      theory[3] = *Dep::BDstarlnu_55_60;
      theory[4] = *Dep::BDstarlnu_60_65;
      theory[5] = *Dep::BDstarlnu_65_70;
      theory[6] = *Dep::BDstarlnu_70_75;
      theory[7] = *Dep::BDstarlnu_75_80;
      theory[8] = *Dep::BDstarlnu_80_85;
      theory[9] = *Dep::BDstarlnu_85_90;
      theory[10] = *Dep::BDstarlnu_90_95;
      theory[11] = *Dep::BDstarlnu_95_100;
      theory[12] = *Dep::BDstarlnu_100_105;

      for (int i = 0; i < n_bins; ++i)
      {
        pmc.value_th(i,0) = theory[i];
        pmc.cov_th(i,i) = th_err[i]*th_err[i] * (th_err_absolute[i] ? 1.0 : theory[i]*theory[i]);
      }

      pmc.diff.clear();
      for (int i=0;i<n_bins;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) cout<<"Finished BDstartaunu_measurements"<<endl;

    }

    /// Likelihood for tree-level leptonic and semileptonic B decays
    void BDstartaunu_likelihood(double &result)
    {
      using namespace Pipes::BDstartaunu_likelihood;

      if (flav_debug) cout<<"Starting BDstartaunu_likelihood"<<endl;

      predictions_measurements_covariances pmc = *Dep::BDstartaunu_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;
      //calculating a diff
      vector<double> diff;
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

      if (flav_debug) cout<<"Finished BDstartaunu_likelihood"<<endl;

      if (flav_debug_LL) cout<<"Likelihood result BDstartaunu_likelihood  : "<< result<<endl;

    } 

    /// mu-e universality for the general THDM from JHEP07(2013)044
    /// Green functions
    double Fint(double x)
    {
      if (x < 0)
        FlavBit_error().raise(LOCAL_INFO, "Negative mass in loop function");
      if (x==0)
        return 1;
      return 1 + 9*x - 9*pow(x,2) - pow(x,3) + 6*x*(1 + x)*log(x);
    }
    
    double Fps(double x)
    {
      if (x < 0)
        FlavBit_error().raise(LOCAL_INFO, "Negative mass in loop function");
      if (x==0)
        return 1;
      return 1 - 8*x + 8*pow(x,3) - pow(x,4) - 12*pow(x,2)*log(x);
    }

    //Lepton universality test observable from JHEP07(2013)044
    void THDM_gmu_ge(double &result)
    {
      using namespace Pipes::THDM_gmu_ge;
      Spectrum spectrum = *Dep::THDM_spectrum;
      SMInputs sminputs = *Dep::SMINPUTS;
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double mMu = Dep::SMINPUTS->mMu;
      const double mTau = Dep::SMINPUTS->mTau;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double D = (2*mMu*Fint(pow(mMu,2)/pow(mTau,2)))/(mTau*Fps(pow(mMu,2)/pow(mTau,2)));
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double Ymutau = spectrum.get(Par::dimensionless,"Ye2",2,3);
      double Ytaumu = spectrum.get(Par::dimensionless,"Ye2",3,2);
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double xi_mumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      double xi_mutau = Ymutau/cosb;
      double xi_taumu = Ytaumu/cosb;
      double xi_tautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      double R = ((v*v)/(2*mHp*mHp))*(xi_mumu*xi_tautau);
      double Roff = ((v*v)/(2*mHp*mHp))*(xi_mutau*xi_taumu);
      //cout<<"D = "<<D<<endl;
      
      result =sqrt(1 + 0.25*(R*R+Roff*Roff) - D*(R+Roff));               
    }           
      
    /// Fill SuperIso nuisance structure
    void SI_nuisance_fill(nuisance &nuislist)
    {
      using namespace Pipes::SI_nuisance_fill;
      if (flav_debug) cout<<"Starting SI_nuisance_fill"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;

      BEreq::set_nuisance(&nuislist);
      BEreq::set_nuisance_value_from_param(&nuislist,&param);

      /* Here the nuisance parameters which should not be used for the correlation calculation have to be given a zero standard deviation.
         E.g. nuislist.mass_b.dev=0.; */

      if (flav_debug) cout<<"Finished SI_nuisance_fill"<<endl;
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
      std::vector<double> obs_theory;
      obs_theory.reserve(observables.size());
      for (unsigned int i = 0; i < observables.size(); ++i)
      {
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
        cout << "Starting SuperIso_prediction" << std::endl;
        cout << "Changing convention. Before:"<<endl;
        print(result,{"S3", "S4", "S5", "S8", "S9"});
      }

      int nObservables = SI_obslist.size();
      if (flav_debug) cout<<"Number of obserables: "<<nObservables<<endl;
      char obsnames[nObservables][50];
      for(int iObservable = 0; iObservable < nObservables; iObservable++)
      {
        strcpy(obsnames[iObservable], SI_obslist[iObservable].c_str());
      }
      if (flav_debug) cout<<"Copied obs"<<endl;
      // ---------- CENTRAL VALUES ----------
      double *result_central;

      // Reserve memory
      result_central = (double *) calloc(nObservables, sizeof(double));
      if (flav_debug)  cout<<"Testing compution: "<<obsnames[0]<<" = "<< result_central[0]<<endl;
      // Needed for SuperIso backend
      get_predictions_nuisance((char**)obsnames, &nObservables, &result_central, &param, &nuislist);
      if (flav_debug)  cout<<"Testing compution: "<<obsnames[0]<<" = "<< result_central[0]<<endl;
      
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
      if (flav_debug) cout<<"2"<<endl;
      //Switch the observables to LHCb convention
      Kstarmumu_Theory2Experiment_translation(result.central_values);
      if (flav_debug) cout<<"3"<<endl; 
      // If we need to compute the covariance, either because we're doing it for every point or we haven't cached the SM value, do it.
      if (not useSMCovariance or not SMCovarianceCached)
      {
        if (flav_debug) cout<<"4"<<endl; 
        // ---------- COVARIANCE ----------
        static bool first = true;
        static const int nNuisance=161;
        static char namenuisance[nNuisance+1][50];
        static double **corr=(double  **) malloc((nNuisance+1)*sizeof(double *));  // Nuisance parameter correlations
        
        if (first)
        {
          observables(0, NULL, 0, NULL, NULL, &nuislist, (char **)namenuisance, &param); // Initialization of namenuisance
          if (flav_debug) cout<<"5"<<endl;
          // Reserve memory
          for(int iObservable = 0; iObservable <= nNuisance; ++iObservable)
          {
            corr[iObservable]=(double *) malloc((nNuisance+1)*sizeof(double));
          }
          if (flav_debug) cout<<"6"<<endl;
          // Needed for SuperIso backend
          convert_correlation((nuiscorr *)corrnuis, byVal(ncorrnuis), (double **)corr, (char **)namenuisance, byVal(nNuisance));
          if (flav_debug) cout<<"7"<<endl;
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
          if (flav_debug) cout<<"70"<<endl; 
          
          // Use the SM values of the parameters to calculate the SM theory covariance.
          get_th_covariance_nuisance(&result_covariance, (char**)obsnames, &nObservables, &param_SM, &nuislist, (double **)corr);
          if (flav_debug) cout<<"71"<<endl; 
        }
        else
        {
          // Calculate covariance at the new physics point.
          get_th_covariance_nuisance(&result_covariance, (char**)obsnames, &nObservables, &param, &nuislist, (double **)corr);
        }
        if (flav_debug) cout<<"8"<<endl; 
        // Fill the covariance matrix in the result structure
        for(int iObservable=0; iObservable < nObservables; ++iObservable)
        {
          for(int jObservable = 0; jObservable < nObservables; ++jObservable)
          {
            result.covariance[FB_obslist[iObservable]][FB_obslist[jObservable]] = result_covariance[iObservable][jObservable];
          }
        }

        //Switch the covariances to LHCb convention
        Kstarmumu_Theory2Experiment_translation(result.covariance);
        if (flav_debug) cout<<"9"<<endl; 
        // Free memory  // We are not freeing the memory because we made the variable static. Just keeping this for reference on how to clean up the allocated memory in case of non-static caluclation of **corr.
        // for(int iObservable = 0; iObservable <= nNuisance; ++iObservable) {
        //   free(corr[iObservable]);
        // }
        // free(corr);
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
        if (flav_debug) cout << "Changing convention. After:"<<endl;
        if (flav_debug) print(result,{"S3", "S4", "S5", "S8", "S9"});
        if (flav_debug) std::cout << "Finished SuperIso_prediction" << std::endl;
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
      static const std::vector<str> FB_obslist = runOptions->            \
       getValue<std::vector<str>>("obs_list");                           \
      THE_REST("")                                                       \
    }                                                                    \

    #define SI_MULTI_PREDICTION_FUNCTION_BINS(name,bins,exp)             \
    void CAT_4(SuperIso_prediction_,name,bins,exp)(flav_prediction&      \
     result)                                                             \
    {                                                                    \
      using namespace CAT_4(Pipes::SuperIso_prediction_,name,bins,exp);  \
      static const std::vector<str> FB_obslist = runOptions->            \
       getValue<std::vector<str>>("obs_list");                           \
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

    SI_MULTI_PREDICTION_FUNCTION(B2mumu)
    SI_MULTI_PREDICTION_FUNCTION(RDRDstar)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_0p1_2,_Atlas)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_2_4,_Atlas)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4_8,_Atlas)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_1_2,_CMS)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_2_4p3,_CMS)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4p3_6,_CMS)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_6_8p68,_CMS)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_10p09_12p86,_CMS)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_14p18_16,_CMS)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_16_19,_CMS)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_0p1_4,_Belle)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4_8,_Belle)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_10p9_12p9,_Belle)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_14p18_19,_Belle)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_0p1_0p98,_LHCb)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_1p1_2p5,_LHCb)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_2p5_4,_LHCb)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_4_6,_LHCb)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_6_8,_LHCb)
    SI_MULTI_PREDICTION_FUNCTION_BINS(B2KstarmumuAng,_15_19,_LHCb)

    #undef SI_PRED_HELPER_CALL
    #undef SI_SINGLE_PREDICTION_FUNCTION
    #undef SI_SINGLE_PREDICTION_FUNCTION_BINS
    #undef SI_MULTI_PREDICTION_FUNCTION
    #undef SI_MULTI_PREDICTION_FUNCTION_BINS


    /// NEW! Compute values of list of observables
    void SI_compute_obs_list(flav_observable_map& result)  // TO BE MODIFIED
    {
      using namespace Pipes::SI_compute_obs_list;
      if (flav_debug) cout<<"Starting SI_compute_obs_list"<<endl;

      const parameters& param = *Dep::SuperIso_modelinfo;

      const nuisance& nuislist = *Dep::SuperIso_nuisance;
      const std::vector<std::string>& obslist = runOptions->getValue<std::vector<std::string>>("SuperIso_obs_list");

      // --- Needed for SuperIso backend
      int nObservables = obslist.size();

      char obsnames[nObservables][50];
      for(int iObservable = 0; iObservable < nObservables; iObservable++) {
          strcpy(obsnames[iObservable], obslist[iObservable].c_str());
      }

      double *res;
      // Reserve memory
      res = (double *) calloc(nObservables, sizeof(double));
      // --- Needed for SuperIso backend

      BEreq::get_predictions_nuisance((char**)obsnames, &nObservables, &res, &param, &nuislist);

      for(int iObservable = 0; iObservable < nObservables; ++iObservable) {
          result[obslist[iObservable]] = res[iObservable];
      }

      // Free memory
      free(res);
      if (flav_debug) {
          for(int iObservable = 0; iObservable < nObservables; ++iObservable) {
              printf("%s=%.4e\n", obsnames[iObservable], result[obslist[iObservable]]);
          }
      }

      if (flav_debug) {
          cout<<"Finished SI_compute_obs_list"<<endl;
      }
    }

    /// Br b	-> s gamma decays
    void SI_bsgamma(double &result)
    {
      using namespace Pipes::SI_bsgamma;
      if (flav_debug) cout<<"Starting SI_bsgamma"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      double E_cut=1.6;
      result=BEreq::bsgamma_CONV(&param, byVal(E_cut));
      if (flav_debug) printf("BR(b->s gamma)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_bsgamma"<<endl;
    }


    /// Br Bs->mumu decays for the untagged case (CP-averaged)
    void SI_Bsmumu_untag(double &result)
    {
      using namespace Pipes::SI_Bsmumu_untag;
      if (flav_debug) cout<<"Starting SI_Bsmumu_untag"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      int flav=2;
      result=BEreq::Bsll_untag_CONV(&param, byVal(flav));

      if (flav_debug) printf("BR(Bs->mumu)_untag=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Bsmumu_untag"<<endl;
    }


    /// Br Bs->ee decays for the untagged case (CP-averaged)
    void SI_Bsee_untag(double &result)
    {
      using namespace Pipes::SI_Bsee_untag;
      if (flav_debug) cout<<"Starting SI_Bsee_untag"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      int flav=1;
      result=BEreq::Bsll_untag_CONV(&param, byVal(flav));

      if (flav_debug) printf("BR(Bs->ee)_untag=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Bsee_untag"<<endl;
    }

    /// Br B0->mumu decays
    void SI_Bmumu(double &result)
    {
      using namespace Pipes::SI_Bmumu;
      if (flav_debug) cout<<"Starting SI_Bmumu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      int flav=2;
      result=BEreq::Bll_CONV(&param, byVal(flav));

      if (flav_debug) printf("BR(B->mumu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Bmumu"<<endl;
    }


    /// Br B->tau nu_tau decays
    void SI_Btaunu(double &result)
    {
      using namespace Pipes::SI_Btaunu;
      if (flav_debug) cout<<"Starting SI_Btaunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Btaunu(&param);

      if (flav_debug) printf("BR(B->tau nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Btaunu"<<endl;
    }

    // Br Bu->tau nu in gTHDM
    void THDM_Btaunu(double &result)//(flav_prediction &result)
    { 
      using namespace Pipes::THDM_Btaunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_B = 5.27926;//All values are taken from SuperIso 3.6
      const double f_B = 0.1905;
      const double hbar = 6.582119514e-25;
      const double life_B = 1.638e-12;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double Vus = lambda;
      const double Vub = 3.55e-3;
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ytaumu = spectrum.get(Par::dimensionless,"Ye2",3,2);
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double X13 = (v*(Vub*(-((sqrt(2)*mBmB*tanb)/v) + sqrt(1 + pow(tanb,2))*Ybb) + sqrt(1 + pow(tanb,2))*Vus*Ysb))/(sqrt(2)*mBmB);
      double Z33 = (v*(-((sqrt(2)*mTau*tanb)/v) + sqrt(1 + pow(tanb,2))*Ytautau))/(sqrt(2)*mTau);
      double Z32 = -((sqrt(1 + pow(tanb,2))*v*Ytaumu)/(sqrt(2)*mTau));
      
      double Deltaij = (pow(m_B,2)*X13*(Z33+Z32))/(pow(mHp,2)*Vub);
   
      double prediction = (pow(1 - Deltaij,2))*(pow(f_B,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_B,2),2)*m_B*life_B*pow(Vub,2))/(8.*hbar*pi);
      result = prediction;
      //result.central_values["B2taunu"] = prediction;
      if (flav_debug) cout << "BR(Bu->tau nu) = " << prediction << endl;
      if (flav_debug) cout << "Finished THDMB2taunu" << endl;
    }

    /// Br B->D_s tau nu
    void SI_Dstaunu(double &result)
    {
      using namespace Pipes::SI_Dstaunu;
      if (flav_debug) cout<<"Starting SI_Dstaunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dstaunu(&param);

      if (flav_debug) printf("BR(Ds->tau nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Dstaunu"<<endl;
    }

    // Br D_s->tau nu in gTHDM
    void THDM_Dstaunu(double &result)
    {
      using namespace Pipes::THDM_Dstaunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_Ds = 1.9683;//All values are taken from SuperIso 3.6
      const double f_Ds = 0.2486;
      const double hbar = 6.582119514e-25;
      const double life_Ds = 5.e-13;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double mTau = Dep::SMINPUTS->mTau;
      const double mS = Dep::SMINPUTS->mS;
      const double mCmC = Dep::SMINPUTS->mCmC;
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",2,3);
      double Ytaumu = spectrum.get(Par::dimensionless,"Ye2",3,2);
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double Yss = spectrum.get(Par::dimensionless,"Yd2",2,2);
      double Y22 = -((v*(Vcs*(-((sqrt(2)*mCmC*tanb)/v) + sqrt(1 + pow(tanb,2))*Ycc) + sqrt(1 + pow(tanb,2))*Vts*Ytc))/(sqrt(2)*mCmC));
      double X22 = (v*(sqrt(1 + pow(tanb,2))*Vcb*Ysb + Vcs*(-((sqrt(2)*mS*tanb)/v) + sqrt(1 + pow(tanb,2))*Yss)))/(sqrt(2)*mS);
      double Z33 = (v*(-((sqrt(2)*mTau*tanb)/v) + sqrt(1 + pow(tanb,2))*Ytautau))/(sqrt(2)*mTau);
      double Z32 = -((sqrt(1 + pow(tanb,2))*v*Ytaumu)/(sqrt(2)*mTau));
      
      double Deltaij = (pow(m_Ds,2)*(mS*X22 + mCmC*Y22)*(Z33+Z32))/(pow(mHp,2)*(mS + mCmC)*Vcs);

      result = (pow(1 - Deltaij,2))*(pow(f_Ds,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_Ds,2),2)*m_Ds*life_Ds*pow(Vcs,2))/(8.*hbar*pi);
  
      if (flav_debug) cout << "BR(Ds->tau nu) = " << result << endl;
      if (flav_debug) cout << "Finished THDM_Dstaunu" << endl;
    }

    /// Br B->D_s mu nu
    void SI_Dsmunu(double &result)
    {
      using namespace Pipes::SI_Dsmunu;
      if (flav_debug) cout<<"Starting SI_Dsmunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dsmunu(&param);

      if (flav_debug) printf("BR(Ds->mu nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Dsmunu"<<endl;
    }

    /// Br D_s->mu nu in gTHDM
    void THDM_Dsmunu(double &result)
    {
      using namespace Pipes::THDM_Dsmunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_Ds = 1.9683;//All values are taken from SuperIso 3.6
      const double f_Ds = 0.2486;
      const double hbar = 6.582119514e-25;
      const double life_Ds = 5.e-13;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vts = -A*lambda*lambda;
      const double mMu = Dep::SMINPUTS->mMu;
      const double mS = Dep::SMINPUTS->mS;
      const double mCmC = Dep::SMINPUTS->mCmC;
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",2,3);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double Ymutau = spectrum.get(Par::dimensionless,"Ye2",2,3);
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double Yss = spectrum.get(Par::dimensionless,"Yd2",2,2);
      double Y22 = -((v*(Vcs*(-((sqrt(2)*mCmC*tanb)/v) + sqrt(1 + pow(tanb,2))*Ycc) + sqrt(1 + pow(tanb,2))*Vts*Ytc))/(sqrt(2)*mCmC));
      double X22 = (v*(sqrt(1 + pow(tanb,2))*Vcb*Ysb + Vcs*(-((sqrt(2)*mS*tanb)/v) + sqrt(1 + pow(tanb,2))*Yss)))/(sqrt(2)*mS);
      double Z22 = (v*(-((sqrt(2)*mMu*tanb)/v) + sqrt(1 + pow(tanb,2))*Ymumu))/(sqrt(2)*mMu);
      double Z23 = (sqrt(1 + pow(tanb,2))*v*Ymutau)/(sqrt(2)*mMu);
      double Deltaij = (pow(m_Ds,2)*(mS*X22 + mCmC*Y22)*(Z22+Z23))/(pow(mHp,2)*(mS + mCmC)*Vcs);
      result = ((pow(1 - Deltaij,2))*pow(f_Ds,2)*pow(sminputs.GF,2)*pow(mMu,2)*pow(1 - pow(mMu,2)/pow(m_Ds,2),2)*m_Ds*life_Ds*pow(Vcs,2))/(8.*hbar*pi);
  
      if (flav_debug) cout << "BR(Ds->mu nu) = " << result << endl;
      if (flav_debug) cout << "Finished THDM_Dsmunu" << endl;
    } 

    /// Br D -> mu nu
    void SI_Dmunu(double &result)
    {
      using namespace Pipes::SI_Dmunu;
      if (flav_debug) cout<<"Starting SI_Dmunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Dmunu(&param);

      if (flav_debug) printf("BR(D->mu nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Dmunu"<<endl;
    }

    /// Br D->mu nu in gTHDM
    void THDM_Dmunu(double &result)
    {
      using namespace Pipes::THDM_Dmunu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double m_D = 1.86961;//All values are taken from SuperIso 3.6
      const double f_D = 0.2135;
      const double hbar = 6.582119514e-25;
      const double life_D = 1.040e-12;
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double Vcd = -lambda;
      const double Vtd = 8.54e-3;//This should be to be called directly from an Eigen object, for the moment is fine.
      const double mMu = Dep::SMINPUTS->mMu;
      const double mCmC = Dep::SMINPUTS->mCmC;
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",2,3);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double Ymutau = spectrum.get(Par::dimensionless,"Ye2",2,3); 
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double Y21 = -((v*(Vcd*(-((sqrt(2)*mCmC*tanb)/v) + sqrt(1 + pow(tanb,2))*Ycc) + sqrt(1 + pow(tanb,2))*Vtd*Ytc))/(sqrt(2)*mCmC));
      double Z22 = (v*(-((sqrt(2)*mMu*tanb)/v) + sqrt(1 + pow(tanb,2))*Ymumu))/(sqrt(2)*mMu);
      double Z23 = (sqrt(1 + pow(tanb,2))*v*Ymutau)/(sqrt(2)*mMu);
      double Deltaij = (pow(m_D,2)*Y21*(Z22+Z23))/(pow(mHp,2)*Vcd);
      result = ((pow(1 - Deltaij,2))*pow(f_D,2)*pow(sminputs.GF,2)*pow(mMu,2)*pow(1 - pow(mMu,2)/pow(m_D,2),2)*m_D*life_D*pow(Vcd,2))/(8.*hbar*pi);
  
      if (flav_debug) cout << "BR(D->mu nu) = " << result << endl;
      if (flav_debug) cout << "Finished THDM_Dmunu" << endl;
    }
    
    /// Br B -> D tau nu
    void SI_BDtaunu(double &result)
    {
      using namespace Pipes::SI_BDtaunu;
      if (flav_debug) cout<<"Starting SI_BDtaunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_tau_D  = 3.16; // 1.776**2
      double q2_max_tau_D  = 11.6;   // (5.28-1.869)**2
      int gen_tau_D        = 3;
      int charge_tau_D     = 0;// D* is the charged version
      double obs_tau_D[3];

      result=BEreq::BRBDlnu(byVal(gen_tau_D), byVal( charge_tau_D), byVal(q2_min_tau_D), byVal(q2_max_tau_D), byVal(obs_tau_D), &param);

      if (flav_debug) printf("BR(B-> D tau nu )=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_BDtaunu"<<endl;
    }


    /// Br B -> D mu nu
    void SI_BDmunu(double &result)
    {
      using namespace Pipes::SI_BDmunu;
      if (flav_debug) cout<<"Starting SI_BDmunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_mu_D=  0.012; // 0.105*0.105
      double q2_max_mu_D=  11.6;   // (5.28-1.869)**2
      int gen_mu_D        =2;
      int charge_mu_D     =0;// D* is the charged version
      double obs_mu_D[3];

      result= BEreq::BRBDlnu(byVal(gen_mu_D), byVal( charge_mu_D), byVal(q2_min_mu_D), byVal(q2_max_mu_D), byVal(obs_mu_D), &param);

      if (flav_debug) printf("BR(B->D mu nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_BDmunu"<<endl;
    }


    /// Br B -> D* tau nu
    void SI_BDstartaunu(double &result)
    {
      using namespace Pipes::SI_BDstartaunu;
      if (flav_debug) cout<<"Starting SI_BDstartaunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_tau_Dstar = 3.16; // 1.776**2
      double q2_max_tau_Dstar = 10.67;   //(5.279-2.01027)*(5.279-2.01027);
      int gen_tau_Dstar        =3;
      int charge_tau_Dstar     =1;// D* is the charged version
      double obs_tau_Dstar[3];

      result= BEreq::BRBDstarlnu(byVal(gen_tau_Dstar), byVal( charge_tau_Dstar), byVal(q2_min_tau_Dstar), byVal(q2_max_tau_Dstar), byVal(obs_tau_Dstar), &param);

      if (flav_debug) printf("BR(B->Dstar tau nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_BDstartaunu"<<endl;
    }


    /// Br B -> D* mu nu
    void SI_BDstarmunu(double &result)
    {
      using namespace Pipes::SI_BDstarmunu;
      if (flav_debug) cout<<"Starting SI_BDstarmunu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      if (param.model < 0) FlavBit_error().raise(LOCAL_INFO, "Unsupported model.");

      double q2_min_mu_Dstar = 0.012; // 0.105*0.105
      double q2_max_mu_Dstar = 10.67;   //(5.279-2.01027)*(5.279-2.01027);
      int gen_mu_Dstar        =2;
      int charge_mu_Dstar     =1;// D* is the charged version
      double obs_mu_Dstar[3];

      result=BEreq::BRBDstarlnu(byVal(gen_mu_Dstar), byVal( charge_mu_Dstar), byVal(q2_min_mu_Dstar), byVal(q2_max_mu_Dstar), byVal(obs_mu_Dstar), &param);

      if (flav_debug) printf("BR(B->Dstar mu nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_BDstarmunu"<<endl;
    }


    ///  B-> D tau nu / B-> D e nu decays
    void SI_RD(double &result)
    {
      using namespace Pipes::SI_RD;
      if (flav_debug) cout<<"Starting SI_RD"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::BDtaunu_BDenu(&param);

      if (flav_debug) printf("BR(B->D tau nu)/BR(B->D e nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_RD"<<endl;
    }


    ///  B->D* tau nu / B-> D* e nu decays
    void SI_RDstar(double &result)
    {
      using namespace Pipes::SI_RDstar;
      if (flav_debug) cout<<"Starting SI_RDstart"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::BDstartaunu_BDstarenu(&param);

      if (flav_debug) printf("BR(B->D* tau nu)/BR(B->D* e nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_RD*"<<endl;
    }

   ///  B-> D tau nu / B-> D e nu decays in THDM
    void THDM_RD(double &result)
    {
      using namespace Pipes::THDM_RD;
      if (flav_debug) cout<<"Starting THDM_RD"<<endl;
      
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4); 
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xitc = Ytc/cosb;
      double xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xisb = Ysb/cosb;
      double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      const double mCmC = Dep::SMINPUTS->mCmC;
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      double CRcb = -2.*std::norm((Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2));
      double CLcb = 2.*std::norm((Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*conj(xitautau)/pow(mHp,2));
      double gs =  (CRcb + CLcb)/CSMcb; 
      
      double RDSM = 0.299;
      
      result = RDSM*(1+1.5*real(gs)+1.0*norm(gs));

      if (flav_debug) printf("BR(B->D tau nu)/BR(B->D e nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_RD"<<endl;
    }


    ///  B->D* tau nu / B-> D* e nu decays in THDM
    void THDM_RDstar(double &result)
    {
      using namespace Pipes::THDM_RDstar;
      if (flav_debug) cout<<"Starting THDM_RDstar"<<endl;
      
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4); 
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xitc = Ytc/cosb;
      double xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xisb = Ysb/cosb;
      double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      const double mCmC = Dep::SMINPUTS->mCmC;
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      double CRcb = -2.*std::norm((Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2));
      double CLcb = 2.*std::norm((Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*conj(xitautau)/pow(mHp,2));
      
      double gp =  (CRcb - CLcb)/CSMcb; 
      
      double RDstarSM = 0.252;
      
      result = RDstarSM*(1+0.12*real(gp)+0.05*norm(gp));

      if (flav_debug) printf("BR(B->D tau nu)/BR(B->D e nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_RDstar"<<endl;
    }

    ///  Bc lifetime in THDM
    void THDM_Bc_lifetime(double &result)
    {
      using namespace Pipes::THDM_Bc_lifetime;
      if (flav_debug) cout<<"Starting THDM_Bc_lifetime"<<endl;

      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double A = Dep::SMINPUTS->CKM.A;
      const double Vcs = 1 - (1/2)*lambda*lambda;
      const double Vcb = A*lambda*lambda;
      const double Vtb = 1 - (1/2)*A*A*pow(lambda,4);
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      const double mC = Dep::SMINPUTS->mCmC;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xitc = Ytc/cosb;
      double xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      double xisb = Ysb/cosb;
      double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      const double m_Bc = 6.2749;//Values taken from SuperIso 3.6
      const double f_Bc = 0.434;
      // TODO: Don't hard code this again, use the one in Utils/numerical_constants
      const double hbar = 6.582119514e-25;
      const double mCmC = Dep::SMINPUTS->mCmC;
      double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      double xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      double CRcb = -2.*std::norm((Vcb*xibb+Vcs*xisb)*std::conj(xitautau)/pow(mHp,2));
      double CLcb = 2.*std::norm((Vcb*std::conj(xicc)+Vtb*std::conj(xitc))*conj(xitautau)/pow(mHp,2));
      double gp =  (CRcb - CLcb)/CSMcb;
      const double Gamma_Bc_SM = (hbar/(0.52e-12)); //Theoretical value in GeV^-1 from 1611.06676
      const double Gamma_Bc_exp = (hbar/(0.507e-12)); //experimental value in GeV^-1
      double BR_Bc_THDM = (1/Gamma_Bc_exp)*((m_Bc*pow(f_Bc,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_Bc,2),2)*pow(Vcb,2))/(8.*pi))*(pow(1 +(m_Bc*m_Bc/(mTau*(mBmB+mC)))*gp,2));
      double BR_Bc_SM = (1/Gamma_Bc_exp)*((m_Bc*pow(f_Bc,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_Bc,2),2)*pow(Vcb,2))/(8.*pi));
      double Gamma_Bc_THDM = (BR_Bc_THDM-BR_Bc_SM)*Gamma_Bc_exp;
      result = hbar/(Gamma_Bc_SM + Gamma_Bc_THDM);

      if (flav_debug) printf("THDM_Bc_lifetime=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_Bc_lifetime"<<endl;
    }


    /// BR(K->mu nu) /BR pi -> mu nu)
    void SI_Rmu(double &result)
    {
      using namespace Pipes::SI_Rmu;
      if (flav_debug) cout<<"Starting SI_Rmu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Kmunu_pimunu(&param);

      if (flav_debug) printf("R_mu=BR(K->mu nu)/BR(pi->mu nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Rmu"<<endl;
    }

    /// BR(K->mu nu) /BR pi-> mu nu) in gTHDM
    void THDM_Rmu(double &result)
    {
      using namespace Pipes::THDM_Rmu;
      if (flav_debug) cout<<"Starting THDM_Rmu"<<endl;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const double delta_em = -0.0070;//All values taken from SuperIso 3.6
      const double m_pi = 0.13957;
      const double m_K = 0.493677;
      const double fK_fpi = 1.193;
      const double life_pi=2.6033e-8;
      const double life_K=1.2380e-8; 
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double lambda = Dep::SMINPUTS->CKM.lambda;
      const double Vud = 1. - 0.5*pow(lambda,2);
      const double Vus = lambda;
      double Vub = 3.55e-3;//From superiso 3.6 manual
      const double mMu = Dep::SMINPUTS->mMu;
      const double mS = Dep::SMINPUTS->mS;
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double Ymutau = spectrum.get(Par::dimensionless,"Ye2",2,3);
      double Yss = spectrum.get(Par::dimensionless,"Yd2",2,2);
      double X12 = (v*(sqrt(1 + pow(tanb,2))*Vub*Ysb + Vus*(-((sqrt(2)*mS*tanb)/v) + sqrt(1 + pow(tanb,2))*Yss)))/(sqrt(2)*mS);
      double Z22 = (v*(-((sqrt(2)*mMu*tanb)/v) + sqrt(1 + pow(tanb,2))*Ymumu))/(sqrt(2)*mMu);
      double Z23 = (sqrt(1 + pow(tanb,2))*v*Ymutau)/(sqrt(2)*mMu); 
      double Deltaij = (pow(m_K,2)*X12*(Z22+Z23))/(pow(mHp,2)*Vus);
      double leptonFactor = pow((1 - pow(mMu,2)/pow(m_K,2))/(1 - pow(mMu,2)/pow(m_pi,2)),2);
      result = (life_K/life_pi)*pow(fK_fpi*Vus/Vud,2)*(m_K/m_pi)*leptonFactor*(1.+delta_em)*(pow(1 - Deltaij,2));

      if (flav_debug) printf("R_mu=BR(K->mu nu)/BR(pi->mu nu) in THDM =%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_Rmu"<<endl;
    }

    /// 2-to-3-body decay ratio for semileptonic K and pi decays
    void SI_Rmu23(double &result)
    {
    using namespace Pipes::SI_Rmu23;
      if (flav_debug) cout<<"Starting SI_Rmu23"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Rmu23(&param);

      if (flav_debug) printf("Rmu23=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Rmu23"<<endl;
    }


    /// Delta_0 (CP-averaged isospin asymmetry of B -> K* gamma)
    void SI_delta0(double &result)
    {
      using namespace Pipes::SI_delta0;
      if (flav_debug) cout<<"Starting SI_delta0"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::delta0_CONV(&param);

      if (flav_debug) printf("Delta0(B->K* gamma)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_delta0"<<endl;
    }


    /// Inclusive branching fraction B -> X_s mu mu at low q^2
    void SI_BRBXsmumu_lowq2(double &result)
    {
      using namespace Pipes::SI_BRBXsmumu_lowq2;
      if (flav_debug) cout<<"Starting SI_BRBXsmumu_lowq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::BRBXsmumu_lowq2_CONV(&param);

      if (flav_debug) printf("BR(B->Xs mu mu)_lowq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_BRBXsmumu_lowq2"<<endl;
    }


    /// Inclusive branching fraction B -> X_s mu mu at high q^2
    void SI_BRBXsmumu_highq2(double &result)
    {
      using namespace Pipes::SI_BRBXsmumu_highq2;
      if (flav_debug) cout<<"Starting SI_BRBXsmumu_highq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::BRBXsmumu_highq2_CONV(&param);

      if (flav_debug) printf("BR(B->Xs mu mu)_highq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_BRBXsmumu_highq2"<<endl;
    }


    /// Forward-backward asymmetry of B -> X_s mu mu at low q^2
    void SI_A_BXsmumu_lowq2(double &result)
    {
      using namespace Pipes::SI_A_BXsmumu_lowq2;
      if (flav_debug) cout<<"Starting SI_A_BXsmumu_lowq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXsmumu_lowq2_CONV(&param);

      if (flav_debug) printf("AFB(B->Xs mu mu)_lowq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_A_BXsmumu_lowq2"<<endl;
    }


    /// Forward-backward asymmetry of B -> X_s mu mu at high q^2
    void SI_A_BXsmumu_highq2(double &result)
    {
      using namespace Pipes::SI_A_BXsmumu_highq2;
      if (flav_debug) cout<<"Starting SI_A_BXsmumu_highq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXsmumu_highq2_CONV(&param);

      if (flav_debug) printf("AFB(B->Xs mu mu)_highq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_A_BXsmumu_highq2"<<endl;
    }


    /// Zero crossing of the forward-backward asymmetry of B -> X_s mu mu
    void SI_A_BXsmumu_zero(double &result)
    {
      using namespace Pipes::SI_A_BXsmumu_zero;
      if (flav_debug) cout<<"Starting SI_A_BXsmumu_zero"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXsmumu_zero_CONV(&param);

      if (flav_debug) printf("AFB(B->Xs mu mu)_zero=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_A_BXsmumu_zero"<<endl;
    }


    /// Inclusive branching fraction B -> X_s tau tau at high q^2
    void SI_BRBXstautau_highq2(double &result)
    {
      using namespace Pipes::SI_BRBXstautau_highq2;
      if (flav_debug) cout<<"Starting SI_BRBXstautau_highq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::BRBXstautau_highq2_CONV(&param);

      if (flav_debug) printf("BR(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_BRBXstautau_highq2"<<endl;
    }


    /// Forward-backward asymmetry of B -> X_s tau tau at high q^2
    void SI_A_BXstautau_highq2(double &result)
    {
      using namespace Pipes::SI_A_BXstautau_highq2;
      if (flav_debug) cout<<"Starting SI_A_BXstautau_highq2"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::A_BXstautau_highq2_CONV(&param);

      if (flav_debug) printf("AFB(B->Xs tau tau)_highq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_A_BXstautau_highq2"<<endl;
    }


    /// B-> K* mu mu observables in different q^2 bins
    /// @{
    #define DEFINE_BKSTARMUMU(Q2MIN, Q2MAX, Q2MIN_TAG, Q2MAX_TAG)                         \
    void CAT_4(SI_BKstarmumu_,Q2MIN_TAG,_,Q2MAX_TAG)(Flav_KstarMuMu_obs &result)          \
    {                                                                                       \
      using namespace Pipes::CAT_4(SI_BKstarmumu_,Q2MIN_TAG,_,Q2MAX_TAG);                 \
      if (flav_debug) cout<<"Starting " STRINGIFY(CAT_4(SI_BKstarmumu_,Q2MIN_TAG,_,Q2MAX_TAG))<<endl; \
      parameters const& param = *Dep::SuperIso_modelinfo;                                   \
      result=BEreq::BKstarmumu_CONV(&param, Q2MIN, Q2MAX);                                \
      if (flav_debug) cout<<"Finished " STRINGIFY(CAT_4(SI_BKstarmumu_,Q2MIN_TAG,_,Q2MAX_TAG))<<endl; \
    }
    DEFINE_BKSTARMUMU(0.1, 0.98, 0p1, 0p98)
    DEFINE_BKSTARMUMU(1.1, 2.5, 11, 25)
    DEFINE_BKSTARMUMU(2.5, 4.0, 25, 40)
    DEFINE_BKSTARMUMU(4.0, 6.0, 40, 60)
    DEFINE_BKSTARMUMU(6.0, 8.0, 60, 80)
    DEFINE_BKSTARMUMU(15., 17., 15, 17)
    DEFINE_BKSTARMUMU(17., 19., 17, 19)
    DEFINE_BKSTARMUMU(15., 19., 15, 19)
    /// @}
    #undef DEFINE_BKSTARMUMU

    /// RK* in low q^2
    void SI_RKstar_0045_11(double &result)
    {
      using namespace Pipes::SI_RKstar_0045_11;
      if (flav_debug) cout<<"Starting SI_RKstar_0045_11"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::RKstar_CONV(&param,0.045,1.1);

      if (flav_debug) printf("RK*_lowq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_RKstar_0045_11"<<endl;
    }

    /// RK* in intermediate q^2
    void SI_RKstar_11_60(double &result)
    {
      using namespace Pipes::SI_RKstar_11_60;
      if (flav_debug) cout<<"Starting SI_RKstar_11_60"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::RKstar_CONV(&param,1.1,6.0);

      if (flav_debug) printf("RK*_intermq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_RKstar_11_60"<<endl;
    }

    // RK* for RHN, using same approximations as RK, low q^2
    void RHN_RKstar_0045_11(double &result)
    {
      using namespace Pipes::RHN_RKstar_0045_11;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) cout << "Starting RHN_RKstar_0045_11" << endl;

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

      if (flav_debug) cout << "RK = " << result << endl;
      if (flav_debug) cout << "Finished RHN_RKstar_0045_11" << endl;

    }

    // RK* for RHN, using same approximations as RK, intermediate q^2
    void RHN_RKstar_11_60(double &result)
    {
      using namespace Pipes::RHN_RKstar_11_60;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) cout << "Starting RHN_RKstar_11_60" << endl;

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

      if (flav_debug) cout << "RK = " << result << endl;
      if (flav_debug) cout << "Finished RHN_RKstar_11_60" << endl;

    }

    /// RK between 1 and 6 GeV^2
    void SI_RK(double &result)
    {
      using namespace Pipes::SI_RK;
      if (flav_debug) cout<<"Starting SI_RK"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::RK_CONV(&param,1.0,6.0);

      if (flav_debug) printf("RK=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_RK"<<endl;
    }

    /// RK for RHN
    void RHN_RK(double &result)
    {
      using namespace Pipes::RHN_RK;
      SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      std::vector<double> mN = {*Param["M_1"],*Param["M_2"],*Param["M_3"]};
      double mt = *Param["mT"];

      if (flav_debug) cout << "Starting RHN_RK" << endl;

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

      if (flav_debug) cout << "RK = " << result << endl;
      if (flav_debug) cout << "Finished RHN_RK" << endl;
    }

    /// Isospin asymmetry of B-> K* mu mu
    void SI_AI_BKstarmumu(double &result)
    {
      using namespace Pipes::SI_AI_BKstarmumu;
      if (flav_debug) cout<<"Starting SI_AI_BKstarmumu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::SI_AI_BKstarmumu_CONV(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_lowq2=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_AI_BKstarmumu"<<endl;
    }


    /// Zero crossing of isospin asymmetry of B-> K* mu mu
    void SI_AI_BKstarmumu_zero(double &result)
    {
      using namespace Pipes::SI_AI_BKstarmumu_zero;

      if (flav_debug) cout<<"Starting SI_AI_BKstarmumu_zero"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::SI_AI_BKstarmumu_zero_CONV(&param);

      if (flav_debug) printf("A_I(B->K* mu mu)_zero=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_AI_BKstarmumu_zero"<<endl;
    }

    /// Measurement for Delta Bd (Bd mass splitting)
    void SI_Delta_MBd(double &result)
    {
      using namespace Pipes::SI_Delta_MBd;
      if (flav_debug) cout<<"Starting SI_Delta_MBd"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::Delta_MB(&param);

      if (flav_debug) printf("Delta_MBd=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Delta_MBd"<<endl;
    }

    /// Measurement for Delta Bs (Bs mass splitting)
    void SI_Delta_MBs(double &result)
    {
      using namespace Pipes::SI_Delta_MBs;
      if (flav_debug) cout<<"Starting SI_Delta_MBs"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::Delta_MBs(&param);

      if (flav_debug) printf("Delta_MBs=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Delta_MBs"<<endl;
    }

     /// DeltaMBs at tree level for the general THDM
    void THDM_Delta_MBs(double &result)
    { 
      using namespace Pipes::THDM_Delta_MBs;
      if (flav_debug) cout<<"Starting THDM_Delta_MBs"<<endl;     

      Spectrum spectrum = *Dep::THDM_spectrum;
      const double mBs = 5.36689;// values from 1602.03560
      const double fBs = 0.2303;
      const double Bag2 = 0.806;
      const double Bag3 = 1.10;
      const double Bag4 = 1.022;
      const double DeltaSM = 1.29022e-11; //.in GeV from  [arXiv:1602.03560]
      const double conv_factor = 1.519267e12;// from GeV to ps^-1
      double alpha = spectrum.get(Par::dimensionless,"alpha");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      double cba = cos(beta-alpha);
      const double mBmB = Dep::SMINPUTS->mBmB;
      const double mS = Dep::SMINPUTS->mS;
      double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      //double mA = spectrum.get(Par::Pole_Mass,"A0");
      const double U22 = 1.41304;//From JHEP02(2020)147
      const double U32 = -0.0516513;
      const double U44 = 1.79804;
      const double b2 = -1.6666;
      const double b3 = 0.3333;
      const double b4 = 2.0;
      double Ybs = spectrum.get(Par::dimensionless,"Yd2",3,2);
      double xi_bs = Ybs/cosb;
      double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      double xi_sb = Ysb/cosb;
      double M12_NP = -(0.125)*(pow(fBs,2)*pow(mBs,3)/(pow(mBmB+mS,2)))*((0.25)*pow(cba,2)*(pow(1/mh,2)-pow(1/mH,2))*((U22*Bag2*b2+U32*Bag3*b3)*(xi_bs*xi_bs+xi_sb*xi_sb)+2*U44*Bag4*b4*xi_sb*xi_bs)+(pow(1/mH,2)*U44*Bag4*b4*xi_sb*xi_bs));
      result = 2*abs(0.5*DeltaSM + M12_NP)*conv_factor;  
      if (flav_debug) printf("Delta_MBs=%.3e\n",result);
      if (flav_debug) cout<<"Finished THDM_Delta_MBs"<<endl;
    }


    /// Flavour observables from FeynHiggs: B_s mass asymmetry, Br B_s -> mu mu, Br B -> X_s gamma
    void FH_FlavourObs(fh_FlavourObs &result)
    {
      using namespace Pipes::FH_FlavourObs;

      if (flav_debug) cout<<"Starting FH_FlavourObs"<<endl;

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

      fh_FlavourObs FlavourObs;
      FlavourObs.Bsg_MSSM = bsgMSSM;
      FlavourObs.Bsg_SM = bsgSM;
      FlavourObs.deltaMs_MSSM = deltaMsMSSM;
      FlavourObs.deltaMs_SM = deltaMsSM;
      FlavourObs.Bsmumu_MSSM = bsmumuMSSM;
      FlavourObs.Bsmumu_SM = bsmumuSM;

      result = FlavourObs;
      if (flav_debug) cout<<"Finished FH_FlavourObs"<<endl;
    }


    ///These functions extract observables from a FeynHiggs flavour result
    ///@{
    void FH_bsgamma(double &result)
    {
      result = Pipes::FH_bsgamma::Dep::FH_FlavourObs->Bsg_MSSM;
    }
    void FH_Bsmumu (double &result)
    {
      result = Pipes::FH_Bsmumu::Dep::FH_FlavourObs->Bsmumu_MSSM;
    }
    void FH_DeltaMs(double &result)
    {
      result = Pipes::FH_DeltaMs::Dep::FH_FlavourObs->deltaMs_MSSM;
    }
    ///@}


    /// Measurements for electroweak penguin decays
    // BKstarmumu angular measurements
    void b2sll_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::b2sll_measurements;

      static bool first = true;
      static int n_experiments;

      if (flav_debug) cout<<"Starting b2sll_measurements function"<<endl;
      if (flav_debug and first) cout <<"Initialising Flav Reader in b2sll_measurements"<<endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="b2sll_likelihood";

        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        const vector<string> observablesn = {"FL", "AFB", "S3", "S4", "S5", "S7", "S8", "S9"};
        const vector<string> observablesq = {"1.1-2.5", "2.5-4", "4-6", "6-8", "15-17", "17-19"};
        vector<string> observables;
        for (unsigned i=0;i<observablesq.size();++i)
        {
          for (unsigned j=0;j<observablesn.size();++j)
          {
            observables.push_back(observablesn[j]+"_B0Kstar0mumu_"+observablesq[i]);
          }
        }

        for (unsigned i=0;i<observables.size();++i)
        {
          fread.read_yaml_measurement("flav_data.yaml", observables[i]);
        }

        fread.initialise_matrices();
        pmc.cov_exp = fread.get_exp_cov();
        pmc.value_exp = fread.get_exp_value();
        pmc.cov_th = Kstarmumu_theory_err().get_th_cov(observables);
        n_experiments = pmc.cov_th.size1();
        pmc.value_th.resize(n_experiments,1);
        pmc.dim=n_experiments;

        // We assert that the experiments and the observables are the same size
        assert(pmc.value_exp.size1() == observables.size());

        // Init out.
        first = false;
      }

      printf("BKstarmumu_11_25->FL=%.3e\n",Dep::BKstarmumu_11_25->FL);

      pmc.value_th(0,0)=Dep::BKstarmumu_11_25->FL;
      pmc.value_th(1,0)=Dep::BKstarmumu_11_25->AFB;
      pmc.value_th(2,0)=Dep::BKstarmumu_11_25->S3;
      pmc.value_th(3,0)=Dep::BKstarmumu_11_25->S4;
      pmc.value_th(4,0)=Dep::BKstarmumu_11_25->S5;
      pmc.value_th(5,0)=Dep::BKstarmumu_11_25->S7;
      pmc.value_th(6,0)=Dep::BKstarmumu_11_25->S8;
      pmc.value_th(7,0)=Dep::BKstarmumu_11_25->S9;

      pmc.value_th(8,0)=Dep::BKstarmumu_25_40->FL;
      pmc.value_th(9,0)=Dep::BKstarmumu_25_40->AFB;
      pmc.value_th(10,0)=Dep::BKstarmumu_25_40->S3;
      pmc.value_th(11,0)=Dep::BKstarmumu_25_40->S4;
      pmc.value_th(12,0)=Dep::BKstarmumu_25_40->S5;
      pmc.value_th(13,0)=Dep::BKstarmumu_25_40->S7;
      pmc.value_th(14,0)=Dep::BKstarmumu_25_40->S8;
      pmc.value_th(15,0)=Dep::BKstarmumu_25_40->S9;

      pmc.value_th(16,0)=Dep::BKstarmumu_40_60->FL;
      pmc.value_th(17,0)=Dep::BKstarmumu_40_60->AFB;
      pmc.value_th(18,0)=Dep::BKstarmumu_40_60->S3;
      pmc.value_th(19,0)=Dep::BKstarmumu_40_60->S4;
      pmc.value_th(20,0)=Dep::BKstarmumu_40_60->S5;
      pmc.value_th(21,0)=Dep::BKstarmumu_40_60->S7;
      pmc.value_th(22,0)=Dep::BKstarmumu_40_60->S8;
      pmc.value_th(23,0)=Dep::BKstarmumu_40_60->S9;

      pmc.value_th(24,0)=Dep::BKstarmumu_60_80->FL;
      pmc.value_th(25,0)=Dep::BKstarmumu_60_80->AFB;
      pmc.value_th(26,0)=Dep::BKstarmumu_60_80->S3;
      pmc.value_th(27,0)=Dep::BKstarmumu_60_80->S4;
      pmc.value_th(28,0)=Dep::BKstarmumu_60_80->S5;
      pmc.value_th(29,0)=Dep::BKstarmumu_60_80->S7;
      pmc.value_th(30,0)=Dep::BKstarmumu_60_80->S8;
      pmc.value_th(31,0)=Dep::BKstarmumu_60_80->S9;

      pmc.value_th(32,0)=Dep::BKstarmumu_15_17->FL;
      pmc.value_th(33,0)=Dep::BKstarmumu_15_17->AFB;
      pmc.value_th(34,0)=Dep::BKstarmumu_15_17->S3;
      pmc.value_th(35,0)=Dep::BKstarmumu_15_17->S4;
      pmc.value_th(36,0)=Dep::BKstarmumu_15_17->S5;
      pmc.value_th(37,0)=Dep::BKstarmumu_15_17->S7;
      pmc.value_th(38,0)=Dep::BKstarmumu_15_17->S8;
      pmc.value_th(39,0)=Dep::BKstarmumu_15_17->S9;

      pmc.value_th(40,0)=Dep::BKstarmumu_17_19->FL;
      pmc.value_th(41,0)=Dep::BKstarmumu_17_19->AFB;
      pmc.value_th(42,0)=Dep::BKstarmumu_17_19->S3;
      pmc.value_th(43,0)=Dep::BKstarmumu_17_19->S4;
      pmc.value_th(44,0)=Dep::BKstarmumu_17_19->S5;
      pmc.value_th(45,0)=Dep::BKstarmumu_17_19->S7;
      pmc.value_th(46,0)=Dep::BKstarmumu_17_19->S8;
      pmc.value_th(47,0)=Dep::BKstarmumu_17_19->S9;

      //double FL = pmc.value_th(24,0);
      //double S5 = pmc.value_th(28,0);
      //double AFB = pmc.value_th(25,0);

      //cout<<"BKstarmumu_6_8->P5' "<< S5/sqrt(FL*(1-FL)) <<endl;
      //cout<<"BKstarmumu_6_8->P2 "<< 2*AFB/(3*(1-FL)) <<endl;

      pmc.diff.clear();
      for (int i=0;i<n_experiments;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) cout<<"Finished b2sll_measurements function"<<endl;
    }

    // BKstarmumu branching
    void b2sll_BR_measurement(std::vector<double> &meas)
    {
      using namespace Pipes::b2sll_BR_measurement;

      if (flav_debug) cout<<"Starting b2sll_BR_measurement function"<<endl;

      meas.clear();
      meas.push_back(Dep::BKstarmumu_11_25->BR);
      meas.push_back(Dep::BKstarmumu_25_40->BR);
      meas.push_back(Dep::BKstarmumu_40_60->BR);
      meas.push_back(Dep::BKstarmumu_60_80->BR);
      meas.push_back(Dep::BKstarmumu_15_17->BR);
      meas.push_back(Dep::BKstarmumu_17_19->BR);

    }

    /// Likelihood for electroweak penguin decays
    void b2sll_likelihood(double &result)
    {
      using namespace Pipes::b2sll_likelihood;

      if (flav_debug) cout<<"Starting b2sll_likelihood"<<endl;

      // Get experimental measurements
      predictions_measurements_covariances pmc=*Dep::b2sll_M;

      // Get experimental covariance
      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimenta covariance
      cov+=pmc.cov_th;

      //calculating a diff
      vector<double> diff;
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

      if (flav_debug) cout<<"Finished b2sll_likelihood"<<endl;
      if (flav_debug_LL) cout<<"Likelihood result b2sll_likelihood : "<< result<<endl;

    }

    /// Likelihood for electroweak penguin decays
    void b2sll_BR_likelihood(double &result)
    {
      using namespace Pipes::b2sll_BR_likelihood;

      if (flav_debug) cout<<"Starting b2sll_BR_likelihood"<<endl;
      
      result = 0.0;
      std::vector<double> meas = *Dep::b2sll_BR_M;
      std::vector<string> observables;
      const vector<string> q2_bins_min_str = {"1.1", "2.5", "4", "6", "15", "17"};
      const vector<string> q2_bins_max_str = {"2.5", "4", "6", "8", "17", "19"};

      Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
      fread.debug_mode(flav_debug);

      for (unsigned i=0;i<q2_bins_min_str.size();++i)
      {
        // create observable names
        observables.push_back("BR_B0Kstar0mumu_"+q2_bins_min_str[i]+"-"+q2_bins_max_str[i]);
      }

      const unsigned num_obs = observables.size();

      for (unsigned i=0;i<num_obs;++i)
      {
        // fill fread from observable names
        fread.read_yaml_measurement("flav_data.yaml", observables[i]);
      }
          
      fread.initialise_matrices();

      boost::numeric::ublas::matrix<double> cov_exp = fread.get_exp_cov();
      boost::numeric::ublas::matrix<double> value_exp = fread.get_exp_value();
      std::vector<double> th_err;
      std::vector<double> th_err_absolute;

      for (unsigned i=0;i<num_obs;++i)
      {
        // integrate each branching * error over q^2 bin
        double dq2 = std::stod(q2_bins_max_str[i])-std::stod(q2_bins_min_str[i]);
        value_exp(i,0) = value_exp(i,0)*dq2;
        cov_exp(i,0) = cov_exp(i,0)*dq2*dq2;
        // fill remaining theory error and abs theory error
        th_err.push_back(fread.get_th_err()(i,0).first);
        th_err_absolute.push_back(fread.get_th_err()(i,0).second);          
      }

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      // calculate likelihood
      for (unsigned i=0;i<num_obs;++i)
      {
        if (flav_debug) cout << "Experiment: " << meas[i] << " " << sqrt(cov_exp(i,i)) << " " << th_err << endl;
        double theory_err = th_err[i] * (th_err_absolute[i] ? 1.0 : std::abs(value_exp(i,0)));
        if (flav_debug) cout << "Theory prediction: "<< value_exp(i,0) <<" +/- "<< theory_err <<endl;
        result += Stats::gaussian_loglikelihood(meas[i], value_exp(i,0), theory_err, sqrt(cov_exp(i,i)), profile);
      }

      if (flav_debug) cout<<"Finished b2sll_BR_likelihood"<<endl;
      if (flav_debug_LL) cout<<"Likelihood result b2sll_BR_likelihood : "<< result<<endl;
    }

    // likelihood for zero of isospin asymmetry BKstarmumu
    void BKstarmumu_AI_zero_ll(double &result)
    {
      using namespace Pipes::BKstarmumu_AI_zero_ll;
      if (flav_debug) cout<<"Starting BKstarmumu_AI_zero_ll"<<endl;

      static bool th_err_absolute, first = true;
      static double exp_meas, exp_err, th_err;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in BKstarmumu_AI_zero_ll"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "AI_zero_B0Kstar0mumu");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_err << " " << th_err << endl;

      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::AI_BKstarmumu_zero;
      double theory_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<theory_err<<endl;

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_err, exp_err, profile);

      if (flav_debug) cout<<"Finished BKstarmumu_AI_zero_ll"<<endl;
    }
 
    // likelihood for isospin asymmetry BKstarmumu q2=[1,6]
    void BKstarmumu_AI_ll(double &result)
    {
      using namespace Pipes::BKstarmumu_AI_ll;
      if (flav_debug) cout<<"Starting BKstarmumu_AI_ll"<<endl;

      static bool th_err_absolute, first = true;
      static double exp_meas, exp_err, th_err;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in BKstarmumu_AI_ll"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "AI_B0Kstar0mumu_1-6");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_err << " " << th_err << endl;

      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::AI_BKstarmumu;
      double theory_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<theory_err<<endl;

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_err, exp_err, profile);

      if (flav_debug) cout<<"Finished BKstarmumu_AI_ll"<<endl;
    }

    // likelihood for delta0
    void delta0_ll(double &result)
    { 
      using namespace Pipes::delta0_ll;
      if (flav_debug) cout<<"Starting delta0"<<endl;
      
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_err, th_err;
      
      if (first)
      { 
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in delta0"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "delta0");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }
      
      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_err << " " << th_err << endl;
      
      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::delta0;
      double theory_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<theory_err<<endl;
      
      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");
      
      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_err, exp_err, profile);
      
      if (flav_debug) cout<<"delta0_ll"<<endl;
    }

    /// Likelihood for Delta Ms
    void deltaMB_likelihood(double &result)
    {
      using namespace Pipes::deltaMB_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_DeltaMs_err, th_err;

      if (flav_debug) cout << "Starting Delta_Ms_likelihood"<<endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in Delta_Ms_likelihood"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "DeltaMs");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_DeltaMs_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_DeltaMs_err << " " << th_err << endl;

      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::DeltaMs;
      double theory_DeltaMs_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<theory_DeltaMs_err<<endl;

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_DeltaMs_err, exp_DeltaMs_err, profile);
    }

    /// Likelihood for Delta Md
    void deltaMBd_likelihood(double &result)
    {
      using namespace Pipes::deltaMBd_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_DeltaMd_err, th_err;

      if (flav_debug) cout << "Starting Delta_Md_likelihood"<<endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in Delta_Md_likelihood"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "DeltaMd");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_DeltaMd_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_DeltaMd_err << " " << th_err << endl;

      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::DeltaMd;
      double theory_DeltaMs_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_DeltaMd_err<<endl;

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_DeltaMs_err, exp_DeltaMd_err, profile);
    }


    /// Likelihood for b->s gamma
    void b2sgamma_likelihood(double &result)
    {
      using namespace Pipes::b2sgamma_likelihood;

      static bool th_err_absolute, first = true;
      static double exp_meas, exp_b2sgamma_err, th_err;

      if (flav_debug) cout << "Starting b2sgamma_measurements"<<endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in b2sgamma_measurements"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "BR_b2sgamma");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_b2sgamma_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_b2sgamma_err << " " << th_err << endl;

      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::bsgamma;
      double theory_b2sgamma_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<theory_b2sgamma_err<<endl;

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_b2sgamma_err, exp_b2sgamma_err, profile);
    }


    /// Measurements for rare purely leptonic B decays
    void b2ll_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::b2ll_measurements;

      static bool bs2mumu_err_absolute, b2mumu_err_absolute, first = true;
      static double theory_bs2mumu_err, theory_b2mumu_err;

      if (flav_debug) cout<<"Starting b2ll_measurements"<<endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="b2ll_likelihood";

        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        if (flav_debug) cout<<"Initiated Flav reader in b2ll_measurements"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "BR_Bs2mumu");
        fread.read_yaml_measurement("flav_data.yaml", "BR_B02mumu");
        if (flav_debug) cout<<"Finished reading b->mumu data"<<endl;

        fread.initialise_matrices();

        theory_bs2mumu_err = fread.get_th_err()(0,0).first;
        theory_b2mumu_err = fread.get_th_err()(1,0).first;
        bs2mumu_err_absolute = fread.get_th_err()(0,0).second;
        b2mumu_err_absolute = fread.get_th_err()(1,0).second;

        pmc.value_exp=fread.get_exp_value();
        pmc.cov_exp=fread.get_exp_cov();

        pmc.value_th.resize(2,1);
        pmc.cov_th.resize(2,2);

        pmc.dim=2;

        // Init over and out.
        first = false;
      }

      // Get theory prediction
      pmc.value_th(0,0)=*Dep::Bsmumu_untag;
      pmc.value_th(1,0)=*Dep::Bmumu;

      // Compute error on theory prediction and populate the covariance matrix
      double theory_bs2mumu_error = theory_bs2mumu_err * (bs2mumu_err_absolute ? 1.0 : *Dep::Bsmumu_untag);
      double theory_b2mumu_error = theory_b2mumu_err * (b2mumu_err_absolute ? 1.0 : *Dep::Bmumu);
      pmc.cov_th(0,0)=theory_bs2mumu_error*theory_bs2mumu_error;
      pmc.cov_th(0,1)=0.;
      pmc.cov_th(1,0)=0.;
      pmc.cov_th(1,1)=theory_b2mumu_error*theory_b2mumu_error;

      // Save the differences between theory and experiment
      pmc.diff.clear();
      for (int i=0;i<2;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) cout<<"Finished b2ll_measurements"<<endl;

    }


    /// Likelihood for rare purely leptonic B decays
    void b2ll_likelihood(double &result)
    {
      using namespace Pipes::b2ll_likelihood;

      if (flav_debug) cout<<"Starting b2ll_likelihood"<<endl;

      predictions_measurements_covariances pmc = *Dep::b2ll_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;

      //calculating a diff
      vector<double> diff;
      diff=pmc.diff;

      boost::numeric::ublas::matrix<double> cov_inv(pmc.dim, pmc.dim);
      InvertMatrix(cov, cov_inv);

      // calculating the chi2
      double Chi2=0;

      for (int i=0; i < pmc.dim; ++i)
      {
        for (int j=0; j<pmc.dim; ++j)
        {
          Chi2+= diff[i] * cov_inv(i,j)*diff[j];
        }
      }

      result=-0.5*Chi2;

      if (flav_debug) cout<<"Finished b2ll_likelihood"<<endl;
      if (flav_debug_LL) cout<<"Likelihood result b2ll_likelihood : "<< result<<endl;

    }


    /// Measurements for tree-level leptonic and semileptonic B decays
    void SL_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::SL_measurements;

      const int n_experiments=9;//8;
      static bool th_err_absolute[n_experiments], first = true;
      static double th_err[n_experiments];

      if (flav_debug) cout<<"Starting SL_measurements"<<endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
      {
        pmc.LL_name="SL_likelihood";

        // Read in experimental measuremens
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in SL_measurements"<<endl;

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
         // R_mu
        fread.read_yaml_measurement("flav_data.yaml", "R_mu");
       
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
      double theory[9];//[8];
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
      //R_mu
      theory[8] =*Dep::Rmu;
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

      if (flav_debug) cout<<"Finished SL_measurements"<<endl;

    }


    /// Likelihood for tree-level leptonic and semileptonic B decays
    void SL_likelihood(double &result)
    {
      using namespace Pipes::SL_likelihood;

      if (flav_debug) cout<<"Starting SL_likelihood"<<endl;

      predictions_measurements_covariances pmc = *Dep::SL_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;

      //calculating a diff
      vector<double> diff;
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

      if (flav_debug) cout<<"Finished SL_likelihood"<<endl;

      if (flav_debug_LL) cout<<"Likelihood result SL_likelihood  : "<< result<<endl;

    }

    // Helper function
    double G(const double x)
    {
      if(x)
        return (10.0 - 43.0*x + 78.0*pow(x,2) - 49.0*pow(x,3) + 4.0*pow(x,4) + 18.0*pow(x,3)*log(x)) / (3.0*pow(x - 1,4));
      else
        return 10.0/3;
    }

    // TODO add RHN contributions to muon g-2

    // Contribution to mu -> e gamma from RHNs
    void RHN_muegamma(double &result)
    {
      using namespace Pipes::RHN_muegamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mMu,5)/(4 * sminputs.alphainv);

      // Form factors
      int e = 0, mu = 1;
      complex<double> k2l = FormFactors::K2L(mu, e, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(mu, e, sminputs, U, ml, mnu);

      result *= (norm(k2l) + norm(k2r));

      result /= Dep::mu_minus_decay_rates->width_in_GeV;

    }

    // Contribution to tau -> e gamma from RHNs
    void RHN_tauegamma(double &result)
    {
      using namespace Pipes::RHN_tauegamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mTau,5)/(4*sminputs.alphainv);

      // Form factors
      int e = 0, tau = 2;
      complex<double> k2l = FormFactors::K2L(tau, e, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(tau, e, sminputs, U, ml, mnu);

      result *= (norm(k2l) + norm(k2r));

      result /= Dep::tau_minus_decay_rates->width_in_GeV;

    }

    // Contribution to tau -> mu gamma from RHNs
    void RHN_taumugamma(double &result)
    {
      using namespace Pipes::RHN_taumugamma;
      SMInputs sminputs = *Dep::SMINPUTS;

      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};

      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      result = pow(sminputs.mTau,5)/(4 * sminputs.alphainv);

      // Form factors
      int mu = 1, tau = 2;
      complex<double> k2l = FormFactors::K2L(tau, mu, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(tau, mu, sminputs, U, ml, mnu);

      result *= (norm(k2l) + norm(k2r));

      result /= Dep::tau_minus_decay_rates->width_in_GeV;
    }

// BR(l -> l' gamma) for the GTHDM from 1511.08880
    void THDM_llpgamma(int l, int lp, SMInputs sminputs, dep_bucket<SMInputs> *sminputspointer, Spectrum spectrum, double &result)
    {
      const double Alpha = 1/(sminputs.alphainv);
      const double alpha = spectrum.get(Par::dimensionless,"alpha");
      const double tanb = spectrum.get(Par::dimensionless,"tanb");
      const double beta = atan(tanb);
      const double cosb = cos(beta);
      const double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      const double cab = cos(alpha-beta);
      const double mE = (*sminputspointer)->mE;
      const double mMu = (*sminputspointer)->mMu;
      const double mTau = (*sminputspointer)->mTau;
      const double mNu1 = (*sminputspointer)->mNu1;
      const double mNu2 = (*sminputspointer)->mNu2;
      const double mNu3 = (*sminputspointer)->mNu3;
      const double mBmB = (*sminputspointer)->mBmB;
      const double mS = (*sminputspointer)->mS;
      const double mCmC = (*sminputspointer)->mCmC;
      const double mT = (*sminputspointer)->mT;
      const double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      const double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      const double mA = spectrum.get(Par::Pole_Mass,"A0");
      const double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const vector<double> ml = {mE, mMu, mTau};     // charged leptons
      const vector<double> mvl = {mNu1, mNu2, mNu3}; // neutrinos
      const vector<double> mlf = {mTau, mBmB, mT};   // fermions in the second loop
      const vector<double> mphi = {mh, mH, mA, mHp};
      const double Yee = spectrum.get(Par::dimensionless,"Ye2",1,1);
      const double Yemu = spectrum.get(Par::dimensionless,"Ye2",1,2);
      const double Ymue = spectrum.get(Par::dimensionless,"Ye2",2,1);
      const double Yetau = spectrum.get(Par::dimensionless,"Ye2",1,3);
      const double Ytaue = spectrum.get(Par::dimensionless,"Ye2",3,1);
      const double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      const double Ymutau = spectrum.get(Par::dimensionless,"Ye2",2,3);
      const double Ytaumu = spectrum.get(Par::dimensionless,"Ye2",3,2);
      const double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      const double Ytt = spectrum.get(Par::dimensionless,"Yu2",3,3);
      const double Ytc = spectrum.get(Par::dimensionless,"Yu2",3,2);
      const double Yct = spectrum.get(Par::dimensionless,"Yu2",2,3);
      const double Ycc = spectrum.get(Par::dimensionless,"Yu2",2,2);
      const double Ybb = spectrum.get(Par::dimensionless,"Yd2",3,3);
      const double Ybs = spectrum.get(Par::dimensionless,"Yd2",3,2);
      const double Ysb = spectrum.get(Par::dimensionless,"Yd2",2,3);
      const double Yss = spectrum.get(Par::dimensionless,"Yd2",2,2);
      const double A      = (*sminputspointer)->CKM.A;
      const double lambda = (*sminputspointer)->CKM.lambda;
      const double rhobar = (*sminputspointer)->CKM.rhobar;
      const double etabar = (*sminputspointer)->CKM.etabar;
      const complex<double> Vud(1 - (1/2)*lambda*lambda);
      const complex<double> Vcd(-lambda,0);
      const complex<double> Vtd((1-rhobar)*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      const complex<double> Vus(lambda,0);
      const complex<double> Vcs(1 - (1/2)*lambda*lambda,0);
      const complex<double> Vts(-A*lambda*lambda,0);
      const complex<double> Vub(rhobar*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      const complex<double> Vcb(A*lambda*lambda,0);
      const complex<double> Vtb(1,0);
      const double xitt = -((sqrt(2)*mT*tanb)/v) + Ytt/cosb;
      const double xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      const double xitc = Ytc/cosb;
      const double xict = Yct/cosb;
      const double xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      const double xiss = -((sqrt(2)*mS*tanb)/v) + Yss/cosb;
      const double xisb = Ysb/cosb;
      const double xibs = Ybs/cosb;
      const double xiee = -((sqrt(2)*mE*tanb)/v) + Yee/cosb;
      const double xiemu = Yemu/cosb;
      const double ximue = Ymue/cosb;
      const double xietau = Yetau/cosb;
      const double xitaue = Ytaue/cosb;
      const double ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      const double ximutau = Ymutau/cosb;
      const double xitaumu = Ytaumu/cosb;
      const double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;

      Eigen::Matrix3cd xi_L, xi_U, xi_D, VCKM;

      xi_L << xiee,  xiemu,  xietau,
              ximue, ximumu, ximutau,
              xitaue, xitaumu, xitautau;

      xi_U << 0,   0,    0,
              0, xicc, xict,
              0, xitc, xitt;

      xi_D << 0,   0,    0,
              0, xiss, xibs,
              0, xisb, xibb;

      const vector<Eigen::Matrix3cd> xi_f = {xi_L, xi_D, xi_U};

      // Needed for Hpm-l-vl couplings
      VCKM << Vud, Vus, Vub,
              Vcd, Vcs, Vcb,
              Vtd, Vts, Vtb;

      int f = 0;

      // One loop amplitude
      complex<double> Aloop1L = 0;
      complex<double> Aloop1R = 0;
      //Charged higgs contributions are being neglected
      //no longer
      for (int phi=0; phi<=3; ++phi)
      {
        for (int li = 0; li <=2; ++li)
        {
          Aloop1L += (1/(16*pow(pi*mphi[phi],2)))*Amplitudes::A_loop1L(f, l, li, lp, phi, mvl, ml, mphi[phi], xi_L, VCKM, v, cab);
          Aloop1R += (1/(16*pow(pi*mphi[phi],2)))*Amplitudes::A_loop1R(f, l, li, lp, phi, mvl, ml, mphi[phi], xi_L, VCKM, v, cab);
        }
      }

      /// Two loop amplitude
      const double mW = (*sminputspointer)->mW;
      const double mZ = (*sminputspointer)->mZ;
      const double sw2 = 1 - pow(mW/mZ,2);
      const vector<double> Qf = {2./3.,-1./3.,-1.};
      const vector<double> QfZ = {-1./2.*2.-4.*Qf[0]*sw2,1./2.*2.-4.*Qf[1]*sw2,-1./2.*2.-4.*Qf[2]*sw2};
      const vector<double> Nc = {3.,3.,1.};
      //Fermionic contribution
      complex<double> Aloop2fL = 0;
      complex<double> Aloop2fR = 0;
      for (int phi=0; phi<=2; ++phi)
         for (int lf=0; lf<=2; ++lf)
              {
               {
                  Aloop2fL += -((Nc[lf]*Qf[lf]*Alpha)/(8*pow(pi,3))/(ml[l]*mlf[lf]))*Amplitudes::A_loop2fL(f, lf, l, lp, phi, ml[l], mlf[lf], mphi[phi], mZ, Qf[lf], QfZ[lf], xi_f[lf], xi_L, VCKM, sw2, v, cab);
                  Aloop2fR += -((Nc[lf]*Qf[lf]*Alpha)/(8*pow(pi,3))/(ml[l]*mlf[lf]))*Amplitudes::A_loop2fR(f, lf, l, lp, phi, ml[l], mlf[lf], mphi[phi], mZ, Qf[lf], QfZ[lf], xi_f[lf], xi_L, VCKM, sw2, v, cab);
               }
              }

      //Bosonic contribution
      complex<double> Aloop2bL = 0;
      complex<double> Aloop2bR = 0;
      for (int phi=0; phi<=1; ++phi)
      {
       const complex<double> sab(sqrt(1-cab*cab),0);
       const complex<double> Cab(cab,0);//auxiliary definition to deal with the complex product
       const vector<complex<double>> angle = {sab,Cab};
       Aloop2bL += (Alpha/(16*pow(pi,3)*ml[l]*v))*angle[phi]*Amplitudes::A_loop2bL(f, l, lp, phi, ml[l], mphi[phi], xi_L, VCKM, sw2, v, cab, mW, mZ);
       Aloop2bR += (Alpha/(16*pow(pi,3)*ml[l]*v))*angle[phi]*Amplitudes::A_loop2bR(f, l, lp, phi, ml[l], mphi[phi], xi_L, VCKM, sw2, v, cab, mW, mZ);
      }

      result = norm(Aloop1L+Aloop2fL+Aloop2bL) + norm(Aloop1R+Aloop2fR+Aloop2bR);
      double BRtautomununu = 17.39/100;//BR(tau->mu nu nu) from PDG 2018
      result *= BRtautomununu*48*pow(pi,3)*Alpha/pow(sminputs.GF,2);

    }


// BR(mu -> e  gamma) for gTHDM from 1511.08880
    void THDM_muegamma(double &result)
    {
      using namespace Pipes::THDM_muegamma;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 1, lp = 0;

      THDM_llpgamma(l, lp, sminputs, sminputspointer, spectrum, result);
    }

// BR(tau -> e gamma) for gTHDM from 1511.08880
    void THDM_tauegamma(double &result)
    {
      using namespace Pipes::THDM_tauegamma;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 0;

      THDM_llpgamma(l, lp, sminputs, sminputspointer, spectrum, result);
    }

// BR(tau -> mu gamma) for gTHDM from 1511.08880
    void THDM_taumugamma(double &result)
    {
      using namespace Pipes::THDM_taumugamma;
      SMInputs sminputs = *Dep::SMINPUTS;
      dep_bucket<SMInputs> *sminputspointer = &Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;
      const int l = 2, lp = 1;

      THDM_llpgamma(l, lp, sminputs, sminputspointer, spectrum, result);
    }

    // General contribution to l_\alpha^- -> l_\beta^- l_\gamma^- l_\delta^+ from RHNs
    double RHN_l2lll(int alpha, int beta, int gamma, int delta, SMInputs sminputs, Eigen::Matrix3cd Vnu, Eigen::Matrix3cd Theta, Eigen::Matrix3cd m_nu, double M1, double M2, double M3, double mH)
    {
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};
      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), M1, M2, M3};

      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      // Form factors
      complex<double> k2l = FormFactors::K2L(alpha, beta, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(alpha, beta, sminputs, U, ml, mnu);
      complex<double> k1r = FormFactors::K1R(alpha, beta, sminputs, U, mnu);
      complex<double> asll = FormFactors::ASLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> aslr = FormFactors::ASLR(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> asrl = FormFactors::ASRL(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> asrr = FormFactors::ASRR(alpha, beta, gamma, delta, sminputs, U, ml, mnu, mH);
      complex<double> avll = FormFactors::AVLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      complex<double> avlr = FormFactors::AVLR(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      complex<double> avrl = FormFactors::AVLL(alpha, beta, gamma, delta, sminputs, U, ml, mnu);
      complex<double> avrr = FormFactors::AVRR(alpha, beta, gamma, delta, sminputs, U, ml, mnu);

      complex<double> avhatll = avll;
      complex<double> avhatlr = avlr;
      complex<double> avhatrl = avrl + 4. * pi / sminputs.alphainv * k1r;
      complex<double> avhatrr = avrr + 4. * pi / sminputs.alphainv * k1r;

      double l2lll = 0;
      if(beta == gamma and gamma == delta) // l(alpha)- -> l(beta)- l(beta)- l(beta)+
      {
        l2lll = real(16. * pow(pi,2) / pow(sminputs.alphainv,2) * (norm(k2l) + norm(k2r)) * (16./3.*log(ml[alpha]/ml[beta]) - 22./3.) + 1./24. * (norm(asll) + norm(asrr) + 2.*norm(aslr) + 2.*norm(asrl)) + 1./3. * (2.*norm(avhatll) + 2.*norm(avhatrr) + norm(avhatlr) + norm(avhatrl)) + 4.*pi/(3.*sminputs.alphainv)*(k2l*conj(asrl - 2.*avhatrl - 4.*avhatrr) + conj(k2l)*(asrl - 2.*avhatrl - 4.*avhatrr) + k2r*conj(aslr - 2.*avhatlr - 4.*avhatll) + conj(k2r)*(aslr - 2.*avhatlr - 4.*avhatll)) - 1./6. * (aslr*conj(avhatlr) + asrl*conj(avhatrl) + conj(aslr)*avhatlr + conj(asrl)*avhatrl));
      }
      else if(gamma == delta) // l(alpha)- -> l(beta)- l(gamma)- l(gamma)+
      {
        l2lll = real(16. *pow(pi,2) / pow(sminputs.alphainv,2) * (norm(k2l) + norm(k2r)) * (16./3.*log(ml[alpha]/ml[gamma]) - 8.) + 1./12. *(norm(asll) + norm(asrr) + norm(aslr) + norm(asrl)) + 1./3. * (norm(avhatll) + norm(avhatrr) + norm(avhatlr) + norm(avhatrl)) + 8.*pi/(3.*sminputs.alphainv) * (k2l*conj(avhatrl + avhatrr) + k2r*conj(avhatlr + avhatll) + conj(k2l)*(avhatrl + avhatrr) + conj(k2r)*(avhatlr + avhatll)));
      }
      else if(beta == gamma) // l(alpha)- -> l(beta)- l(beta)- l(delta)+
      {
        l2lll = real(1./24. * (norm(asll) + norm(asrr) + 2.*norm(aslr) + 2.*norm(asrl)) + 1./3.*(2.*norm(avhatll) + 2.*norm(avhatrr) + norm(avhatlr) + norm(avhatrl)) - 1./6.*(aslr*conj(avhatlr) + asrl*conj(avhatrl) + conj(aslr)*avhatlr + conj(asrl)*avhatrl));
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

    //l2lll from THDMs

    // General contribution to l_\i^- -> l_\j^- l_\k^- l_\l^+ for gTHDM from 1511.08880
    double THDM_l2lll(int i, int j, int k, int l, SMInputs sminputs, Spectrum spectrum)
    {
      double alpha = spectrum.get(Par::dimensionless,"alpha");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      double v = sqrt(1.0/(sqrt(2.0)*sminputs.GF));
      double cab = cos(alpha-beta);
      double mE = sminputs.mE;
      double mMu = sminputs.mMu;
      double mTau = sminputs.mTau;
      vector<double> ml = {mE, mMu, mTau};
      double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      double mH = spectrum.get(Par::Pole_Mass,"h0",2);
      double mA = spectrum.get(Par::Pole_Mass,"A0");
      vector<double> mphi= {mh, mH, mA};
      double Yee = spectrum.get(Par::dimensionless,"Ye2",1,1);
      double Yemu = spectrum.get(Par::dimensionless,"Ye2",1,2);
      double Ymue = spectrum.get(Par::dimensionless,"Ye2",2,1);
      double Yetau = spectrum.get(Par::dimensionless,"Ye2",1,3);
      double Ytaue = spectrum.get(Par::dimensionless,"Ye2",3,1);
      double Ymumu = spectrum.get(Par::dimensionless,"Ye2",2,2);
      double Ymutau = spectrum.get(Par::dimensionless,"Ye2",2,3);
      double Ytaumu = spectrum.get(Par::dimensionless,"Ye2",3,2);
      double Ytautau = spectrum.get(Par::dimensionless,"Ye2",3,3);
      double A      = sminputs.CKM.A;
      double lambda = sminputs.CKM.lambda;
      double rhobar = sminputs.CKM.rhobar;
      double etabar = sminputs.CKM.etabar;
      complex<double> Vud(1 - (1/2)*lambda*lambda);
      complex<double> Vcd(-lambda,0);
      complex<double> Vtd((1-rhobar)*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      complex<double> Vus(lambda,0);
      complex<double> Vcs(1 - (1/2)*lambda*lambda,0);
      complex<double> Vts(-A*lambda*lambda,0);
      complex<double> Vub(rhobar*A*pow(lambda,3),-etabar*A*pow(lambda,3));
      complex<double> Vcb(A*lambda*lambda,0);
      complex<double> Vtb(1,0);
      double xiee = -((sqrt(2)*mE*tanb)/v) + Yee/cosb;
      double xiemu = Yemu/cosb;
      double ximue = Ymue/cosb;
      double xietau = Yetau/cosb;
      double xitaue = Ytaue/cosb;
      double ximumu = -((sqrt(2)*mMu*tanb)/v) + Ymumu/cosb;
      double ximutau = Ymutau/cosb;
      double xitaumu = Ytaumu/cosb;
      double xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      Eigen::Matrix3cd xi_L, VCKM;

      xi_L << xiee,  xiemu,  xietau,
              ximue, ximumu, ximutau,
              xitaue, xitaumu, xitautau;

      // Needed for Hpm-l-vl couplings
      VCKM << Vud, Vus, Vub,
              Vcd, Vcs, Vcb,
              Vtd, Vts, Vtb;

      int f=0;
      double l2lll = 0;
      complex<double> two(2,0);

      for (int phi=0; phi<=2; ++phi)
      {
        for (int phip=0; phip<=2; ++phip)
        {
         if(j == k and k == l) // l(i)- -> l(j)- l(j)- l(j)+
         {

                   l2lll += real(0.5*(1/pow(mphi[phi]*mphi[phip],2))*( two*(Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           + two*(Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           +   (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))
                                                           +   (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))));
         }
         else if(k == l) // l(i)- -> l(j)- l(k)- l(k)+
         {
                   l2lll += real( 1/(pow(mphi[phi]*mphi[phip],2))*( (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           + (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab)))
                                                           +   (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))
                                                           +   (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, k, k, phi, ml[k], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, k, k, phip, ml[k], xi_L, VCKM, v, cab))))));
         }

         else if(j == k) // l(i)- -> l(j)- l(j)- l(l)+
         {
                   l2lll +=  real(0.5*(1/pow(mphi[phi]*mphi[phip],2))*( two*(Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f,  l, l, phi, ml[l], xi_L, VCKM, v, cab)))
                                                           + two*(Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab)) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab)))
                                                           +   (Yukawas::yff_phi(f, k, i, phi,  ml[k], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, k, i, phip, ml[k], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab))))
                                                           +   (Yukawas::yff_phi(f, i, k, phi,  ml[i], xi_L, VCKM, v, cab)*Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab) * (conj(Yukawas::yff_phi(f, i, k, phip, ml[i], xi_L, VCKM, v, cab))*conj(Yukawas::yff_phi(f, l, l, phi, ml[l], xi_L, VCKM, v, cab))))));
          }
         }
       }

      double BRtautomununu = 17.39/100;//BR(tau->mu nu nu) from PDG 2018
      return (BRtautomununu/(32*pow(sminputs.GF,2)))*l2lll;
    }


    // Contribution to mu -> e e e from THDM
    void THDM_mueee(double &result)
    {
      using namespace Pipes::THDM_mueee;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1;
      result =  THDM_l2lll(mu, e, e, e, sminputs,spectrum);

    }

    // Contribution to tau -> e e e from THDM
    void THDM_taueee(double &result)
    {
      using namespace Pipes::THDM_taueee;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, tau = 2;
      result =  THDM_l2lll(tau, e, e, e, sminputs, spectrum);

    }

    // Contribution to tau -> mu mu mu from THDM
    void THDM_taumumumu(double &result)
    {
      using namespace Pipes::THDM_taumumumu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int mu = 1, tau = 2;
      result =  THDM_l2lll(tau, mu, mu, mu, sminputs, spectrum);

    }

    // Contribution to tau^- -> mu^- e^- e^+ from THDM
    void THDM_taumuee(double &result)
    {
      using namespace Pipes::THDM_taumuee;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, mu, e, e, sminputs, spectrum);

    }

    // Contribution to tau^- -> e^- e^- mu^+ from THDM
    void THDM_taueemu(double &result)
    {
      using namespace Pipes::THDM_taueemu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, e, e, mu, sminputs, spectrum);

    }

    // Contribution to tau^- -> e^- mu^- mu^+ from THDM
    void THDM_tauemumu(double &result)
    {
      using namespace Pipes::THDM_tauemumu;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, e, mu, mu, sminputs, spectrum);

    }

    // Contribution to tau^- -> mu^- mu^- e^+ from THDM
    void THDM_taumumue(double &result)
    {
      using namespace Pipes::THDM_taumumue;
      SMInputs sminputs = *Dep::SMINPUTS;
      Spectrum spectrum = *Dep::THDM_spectrum;

      int e = 0, mu = 1, tau = 2;
      result =  THDM_l2lll(tau, mu, mu, e, sminputs, spectrum);

    }

    // Form factors for to mu - e conversion
    void RHN_mue_FF(const SMInputs sminputs, std::vector<double> &mnu, Eigen::Matrix<complex<double>,3,6> &U, const double mH, complex<double> &g0SL, complex<double> &g0SR, complex<double> &g0VL, complex<double> &g0VR, complex<double> &g1SL, complex<double> &g1SR, complex<double> &g1VL, complex<double> &g1VR)
    {
      vector<double> ml = {sminputs.mE, sminputs.mMu, sminputs.mTau};

      int e = 0, mu = 1;
      complex<double> k1r = FormFactors::K1R(mu, e, sminputs, U, mnu);
      complex<double> k2l = FormFactors::K2L(mu, e, sminputs, U, ml, mnu);
      complex<double> k2r = FormFactors::K2R(mu, e, sminputs, U, ml, mnu);

      int u = 0, d =0, s = 1;
      complex<double> CVLLu = FormFactors::CVLL(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVLLd = FormFactors::BVLL(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVLLs = FormFactors::BVLL(mu, e, s, s, sminputs, U, ml, mnu);
      complex<double> CVLRu = FormFactors::CVLR(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVLRd = FormFactors::BVLR(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVLRs = FormFactors::BVLR(mu, e, s, s, sminputs, U, ml, mnu);
      complex<double> CVRLu = FormFactors::CVRL(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVRLd = FormFactors::BVRL(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVRLs = FormFactors::BVRL(mu, e, s, s, sminputs, U, ml, mnu);
      complex<double> CVRRu = FormFactors::CVRR(mu, e, u, u, sminputs, U, ml, mnu);
      complex<double> CVRRd = FormFactors::BVRR(mu, e, d, d, sminputs, U, ml, mnu);
      complex<double> CVRRs = FormFactors::BVRR(mu, e, s, s, sminputs, U, ml, mnu);

      complex<double> CSLLu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml, mnu, mH);
      complex<double> CSLLd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      complex<double> CSLLs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml, mnu, mH);
      complex<double> CSLRu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml, mnu, mH);
      complex<double> CSLRd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      complex<double> CSLRs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml, mnu, mH);
      complex<double> CSRLu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml ,mnu, mH);
      complex<double> CSRLd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml ,mnu, mH);
      complex<double> CSRLs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml ,mnu, mH);
      complex<double> CSRRu = FormFactors::CSLL(mu, e, u, u, sminputs, U, ml ,mnu, mH);
      complex<double> CSRRd = FormFactors::BSLL(mu, e, d, d, sminputs, U, ml, mnu, mH);
      complex<double> CSRRs = FormFactors::BSLL(mu, e, s, s, sminputs, U, ml ,mnu, mH);

      double Qu = 2./3.;
      complex<double> gVLu = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qu * (0. - k2r) - 0.5*(CVLLu + CVLRu));
      complex<double> gSLu = -1./(sqrt(2)*sminputs.GF)*(CSLLu + CSLRu);
      complex<double> gVRu = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qu * (k1r - k2l) - 0.5*(CVRRu + CVRLu));
      complex<double> gSRu = -1./(sqrt(2)*sminputs.GF)*(CSRRu + CSRLu);

      double Qd = -1./3.;
      complex<double> gVLd = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qd * (0. - k2r) - 0.5*(CVLLd + CVLRd));
      complex<double> gSLd = -1./(sqrt(2)*sminputs.GF)*(CSLLd + CSLRd);
      complex<double> gVRd = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qd * (k1r - k2l) - 0.5*(CVRRd + CVRLd));
      complex<double> gSRd = -1./(sqrt(2)*sminputs.GF)*(CSRRd + CSRLd);

      double Qs = -1./3.;
      complex<double> gVLs = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qs * (0. - k2r) - 0.5*(CVLLs + CVLRs));
      complex<double> gSLs = -1./(sqrt(2)*sminputs.GF)*(CSLLs + CSLRs);
      complex<double> gVRs = sqrt(2)/sminputs.GF * (4.*pi / sminputs.alphainv * Qs * (k1r - k2l) - 0.5*(CVRRs + CVRLs));
      complex<double> gSRs = -1./(sqrt(2)*sminputs.GF)*(CSRRs + CSRLs);

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

      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);

      // Parameters for Ti, from Table 1 in 1209.2679 for Ti
      double Z = 22, N = 26;
      double Zeff = 17.6, Fp = 0.54;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 2.59e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));

    }

    // Contribution to mu - e conversion in Au nuclei from RHNs
    void RHN_mueAu(double &result)
    {
      using namespace Pipes::RHN_mueAu;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);


      // Parameters for Au, from Table 1 in 1209.2679 for Au
      double Z = 79, N = 118;
      double Zeff = 33.5, Fp = 0.16;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 13.07e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));

    }


    // Contribution to mu - e conversion in Pb nuclei from RHNs
    void RHN_muePb(double &result)
    {
      using namespace Pipes::RHN_muePb;
      const SMInputs sminputs = *Dep::SMINPUTS;
      Eigen::Matrix3cd m_nu = *Dep::m_nu;
      Eigen::Matrix3cd Vnu = *Dep::SeesawI_Vnu;
      Eigen::Matrix3cd Theta = *Dep::SeesawI_Theta;

      vector<double> mnu = {real(m_nu(0,0)), real(m_nu(1,1)), real(m_nu(2,2)), *Param["M_1"], *Param["M_2"], *Param["M_3"]};
      Eigen::Matrix<complex<double>,3,6> U;

      for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
          U(i,j) = Vnu(i,j);
          U(i,j+3) = Theta(i,j);
        }

      complex<double> g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR;
      RHN_mue_FF(sminputs, mnu, U, *Param["mH"], g0SL, g0SR, g0VL, g0VR, g1SL, g1SR, g1VL, g1VR);

      // Parameters for Pb, from Table 1 in 1209.2679 for Pb
      double Z = 82, N = 126;
      double Zeff = 34., Fp = 0.15;
      double hbar = 6.582119514e-25; // GeV * s
      double GammaCapt = 13.45e6 * hbar;

      result = (pow(sminputs.GF,2)*pow(sminputs.mMu,5)*pow(Zeff,4)*pow(Fp,2)) / (8.*pow(pi,4)*pow(sminputs.alphainv,3)*Z*GammaCapt) * (norm((Z+N)*(g0VL + g0SL) + (Z-N)*(g1VL + g1SL)) + norm((Z+N)*(g0VR + g0SR) + (Z-N)*(g1VR + g1SR)));
    }

    /// Likelihood for  mu-e universality
    void gmu_ge_likelihood(double &result)
    {
      using namespace Pipes::gmu_ge_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_gmu_ge_err, th_err;

      if (flav_debug) cout << "gmu_ge_likelihood"<<endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in gmu_ge_ikelihood"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "gmu_ge");
        fread.initialise_matrices(); 
        exp_meas = fread.get_exp_value()(0,0);
        exp_gmu_ge_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_gmu_ge_err << " " << th_err << endl;

      double theory_prediction = *Dep::gmu_ge;
      double theory_gmu_ge_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_gmu_ge_err<<endl;

      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_gmu_ge_err, exp_gmu_ge_err, profile);
    }

    /// Likelihood for the Bc lifetime
    void Bc_lifetime_likelihood(double &result)
    {
      using namespace Pipes::Bc_lifetime_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_taulifetime_err, th_err;

      if (flav_debug) cout << "Bc_lifetime_likelihood"<<endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in Bc_lifetime_ikelihood"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "Bc_lifetime");
        fread.initialise_matrices();
        exp_meas = fread.get_exp_value()(0,0);
        exp_taulifetime_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_taulifetime_err << " " << th_err << endl;

      double theory_prediction = *Dep::Bc_lifetime;
      double theory_taulifetime_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_taulifetime_err<<endl;

      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_taulifetime_err, exp_taulifetime_err, profile);
    }


    /// Likelihood for FLDstar
    void FLDstar_likelihood(double &result)
    {
      using namespace Pipes::FLDstar_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_FLDstar_err, th_err;

      if (flav_debug) cout << "FLDstar_likelihood"<<endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) cout<<"Initialised Flav reader in FLDstar_likelihood"<<endl;
        fread.read_yaml_measurement("flav_data.yaml", "FLDstar");
        fread.initialise_matrices();
        exp_meas = fread.get_exp_value()(0,0);
        exp_FLDstar_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) cout << "Experiment: " << exp_meas << " " << exp_FLDstar_err << " " << th_err << endl;

      double theory_prediction = *Dep::FLDstar;
      double theory_FLDstar_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_FLDstar_err<<endl;

      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_FLDstar_err, exp_FLDstar_err, profile);
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
     if(flav_debug) cout << "mu- -> e- gamma = " << theory[0] << endl;
     theory[1] = *Dep::tauegamma;
     if(flav_debug) cout << "tau- -> e- gamma = " << theory[1] << endl;
     theory[2] = *Dep::taumugamma;
     if(flav_debug) cout << "tau- -> mu- gamma = " << theory[2] << endl;

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
     if(flav_debug) cout << "mu-  -> e-  e-  e+  = " << theory[0] << endl;
     theory[1] = *Dep::taueee;
     if(flav_debug) cout << "tau- -> e-  e-  e+  = " << theory[1] << endl;
     theory[2] = *Dep::taumumumu;
     if(flav_debug) cout << "tau- -> mu- mu- mu+ = " << theory[2] << endl;
     theory[3] = *Dep::taumuee;
     if(flav_debug) cout << "tau- -> mu- e-  e-  = " << theory[3] << endl;
     theory[4] = *Dep::taueemu;
     if(flav_debug) cout << "tau- -> e-  e-  mu+ = " << theory[4] << endl;
     theory[5] = *Dep::tauemumu;
     if(flav_debug) cout << "tau- -> e-  mu- mu+ = " << theory[5] << endl;
     theory[6] = *Dep::taumumue;
     if(flav_debug) cout << "tau- -> mu- mu- e+  = " << theory[6] << endl;

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
      if(flav_debug) cout << "mu - e (Ti) = " << theory[0] << endl;
      theory[1] = *Dep::mueAu;
      if(flav_debug) cout << "mu - e (Au) = " << theory[1] << endl;
      theory[2] = *Dep::muePb;
      if(flav_debug) cout << "mu - e (Pb) = " << theory[2] << endl;

      result = 0;
      for (int i = 0; i < n_measurements; ++i)
        result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);

    }

    /// Measurements for LUV in b->sll
    void LUV_measurements(predictions_measurements_covariances &pmc)
    {
      using namespace Pipes::LUV_measurements;
      static bool first = true;

      static double theory_RKstar_0045_11_err, theory_RKstar_11_60_err, theory_RK_err;
      if (flav_debug) cout<<"Starting LUV_measurements"<<endl;

      // Read and calculate things based on the observed data only the first time through, as none of it depends on the model parameters.
      if (first)
        {
          pmc.LL_name="LUV_likelihood";

          Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
          fread.debug_mode(flav_debug);

          if (flav_debug) cout<<"Initiated Flav reader in LUV_measurements"<<endl;
          fread.read_yaml_measurement("flav_data.yaml", "RKstar_0045_11");
          fread.read_yaml_measurement("flav_data.yaml", "RKstar_11_60");
          fread.read_yaml_measurement("flav_data.yaml", "RK");

          if (flav_debug) cout<<"Finished reading LUV data"<<endl;

          fread.initialise_matrices();

          theory_RKstar_0045_11_err = fread.get_th_err()(0,0).first;
          theory_RKstar_11_60_err = fread.get_th_err()(1,0).first;
          theory_RK_err = fread.get_th_err()(2,0).first;

          pmc.value_exp=fread.get_exp_value();
          pmc.cov_exp=fread.get_exp_cov();

          pmc.value_th.resize(3,1);
          pmc.cov_th.resize(3,3);

          pmc.dim=3;

          // Init over and out.
          first = false;
        }

      // Get theory prediction
      pmc.value_th(0,0)=*Dep::RKstar_0045_11;
      pmc.value_th(1,0)=*Dep::RKstar_11_60;
      pmc.value_th(2,0)=*Dep::RK;

      // Compute error on theory prediction and populate the covariance matrix
      pmc.cov_th(0,0)=theory_RKstar_0045_11_err;
      pmc.cov_th(0,1)=0.;
      pmc.cov_th(0,2)=0.;
      pmc.cov_th(1,0)=0.;
      pmc.cov_th(1,1)=theory_RKstar_11_60_err;
      pmc.cov_th(1,2)=0.;
      pmc.cov_th(2,0)=0.;
      pmc.cov_th(2,1)=0.;
      pmc.cov_th(2,2)=theory_RK_err;



      // Save the differences between theory and experiment
      pmc.diff.clear();
      for (int i=0;i<3;++i)
        {
          pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
        }

      if (flav_debug) cout<<"Finished LUV_measurements"<<endl;


    }
    /// Likelihood  for LUV in b->sll
    void LUV_likelihood(double &result)
    {
      using namespace Pipes::LUV_likelihood;

      if (flav_debug) cout<<"Starting LUV_likelihood"<<endl;

      predictions_measurements_covariances pmc = *Dep::LUV_M;

      boost::numeric::ublas::matrix<double> cov=pmc.cov_exp;

      // adding theory and experimental covariance
      cov+=pmc.cov_th;

      //calculating a diff
      vector<double> diff;
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

      if (flav_debug) cout<<"Finished LUV_likelihood"<<endl;

      if (flav_debug_LL) cout<<"Likelihood result LUV_likelihood  : "<< result<<endl;

    }

    /// Br Bs->mumu decays for the untagged case (CP-averaged)
    void Flavio_test(double &result)
    {
      using namespace Pipes::Flavio_test;
      if (flav_debug) cout<<"Starting Flavio_test"<<endl;

      result=BEreq::sm_prediction_CONV("BR(Bs->mumu)");
      std::cout<<"Flavio result: "<<result<<std::endl;
    }

    /// HEPLike LogLikelihood RD RDstar
    void HEPLike_RDRDstar_LogLikelihood(double& result)
    {
      using namespace Pipes::HEPLike_RDRDstar_LogLikelihood;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/HFLAV_18/Semileptonic/RD_RDstar.yaml";
      static HepLike_default::HL_nDimGaussian nDimGaussian(inputfile);
      static bool first = true;
      if (first)
      {
        std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        nDimGaussian.Read();
        first = false;
      }
      const std::vector<double> theory{*Dep::RD, *Dep::RDstar};
      result = nDimGaussian.GetLogLikelihood(theory /* , theory_covariance */);
      // TODO: SuperIso is not ready to give correlations for these observables. So currently we fall back to the old way.
      //       Below code is for future reference.
      // static const std::vector<std::string> observables{
      //   "RD",
      //   "RDstar"
      // };

      // flav_prediction prediction = *Dep::prediction_RDRDstar;
      // flav_observable_map theory = prediction.central_values;
      // flav_covariance_map theory_covariance = prediction.covariance;

      // result = nDimGaussian.GetLogLikelihood(get_obs_theory(observables), get_obs_covariance(observables));
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
         inputfile << endl;                                                       \
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
    HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(B2Kstargamma, "/data/HFLAV_18/RD/B2Kstar_gamma_S.yaml")
    HEPLIKE_GAUSSIAN_1D_LIKELIHOOD(B2taunu, "/data/PDG/Semileptonic/B2TauNu.yaml")

    /// HEPLike LogLikelihood B -> ll (CMS)
    void HEPLike_B2mumu_LogLikelihood_CMS(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_CMS;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/CMS/RD/B2MuMu/CMS-PAS-BPH-16-004.yaml";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);
      static bool first = true;

      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_CMS result: " << result << std::endl;
    }


    /// HEPLike LogLikelihood B -> ll (ATLAS)
    void HEPLike_B2mumu_LogLikelihood_Atlas(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_Atlas;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/ATLAS/RD/B2MuMu/CERN-EP-2018-291.yaml";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_Atlas result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> ll (LHCb)
    void HEPLike_B2mumu_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2mumu_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/B2MuMu/CERN-EP-2017-100.yaml";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static HepLike_default::HL_nDimLikelihood nDimLikelihood(inputfile);

      static bool first = true;
      if (first)
      {
        if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << inputfile << endl;
        nDimLikelihood.Read();
        update_obs_list(obs_list, nDimLikelihood.GetObservables());
        first = false;
      }

      /* nDimLikelihood does not support theory errors */
      result = nDimLikelihood.GetLogLikelihood(get_obs_theory(*Dep::prediction_B2mumu, obs_list));

      if (flav_debug) std::cout << "HEPLike_B2mumu_LogLikelihood_LHCb result: " << result << std::endl;
    }

    /// HEPLike LogLikelihood B -> K* mu mu Angluar (ATLAS)
    void HEPLike_B2KstarmumuAng_LogLikelihood_Atlas(double &result)
    {
      if (flav_debug) std::cout << "Starting HEPLike_B2KstarmumuAng_LogLikelihood_Atlas"<<std::endl;
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_Atlas;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/ATLAS/RD/Bd2KstarMuMu_Angular/CERN-EP-2017-161_q2_";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        HepLike_default::HL_nDimGaussian(inputfile + "0.1_2.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.0_4.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_8.0.yaml"),
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimGaussian.size(); ++i)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
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


    /// HEPLike LogLikelihood B -> K* mu mu Angluar (ATLAS) without the lowest q2 region.
    void HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Atlas(double &result)
    {
      if (flav_debug) std::cout << "Starting HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Atlas"<<std::endl;
      using namespace Pipes::HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Atlas;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/ATLAS/RD/Bd2KstarMuMu_Angular/CERN-EP-2017-161_q2_";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        //HepLike_default::HL_nDimGaussian(inputfile + "0.1_2.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.0_4.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_8.0.yaml"),
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimGaussian.size(); ++i)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
          nDimGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        //*Dep::prediction_B2KstarmumuAng_0p1_2_Atlas,
        *Dep::prediction_B2KstarmumuAng_2_4_Atlas,
        *Dep::prediction_B2KstarmumuAng_4_8_Atlas,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimGaussian.size(); i++)
      {
        result += nDimGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }
      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Atlas result: " << result << std::endl;
    }




    
    /// HEPLike LogLikelihood B -> K* mu mu Angular (CMS)
    void HEPLike_B2KstarmumuAng_LogLikelihood_CMS(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_CMS;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/CMS/RD/Bd2KstarMuMu_Angular/CERN-EP-2017-240_q2_";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian = {
        HepLike_default::HL_nDimBifurGaussian(inputfile+"1.0_2.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"2.0_4.3.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"4.3_6.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"6.0_8.68.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"10.09_12.86.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"14.18_16.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile+"16.0_19.0.yaml")
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << endl;
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
    void HEPLike_B2KstarmumuAng_LogLikelihood_Belle(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_Belle;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/Belle/RD/Bd2KstarMuMu_Angular/KEK-2016-54_q2_";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian = {
        HepLike_default::HL_nDimBifurGaussian(inputfile + "0.1_4.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "4.0_8.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "10.09_12.9.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "14.18_19.0.yaml"),
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
          nDimBifurGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction = {
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


    
    /// HEPLike LogLikelihood B -> K* mu mu Angular (Belle)
    void HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Belle(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Belle;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/Belle/RD/Bd2KstarMuMu_Angular/KEK-2016-54_q2_";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian = {
        //     HepLike_default::HL_nDimBifurGaussian(inputfile + "0.1_4.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "4.0_8.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "10.09_12.9.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "14.18_19.0.yaml"),
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
          nDimBifurGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimBifurGaussian[0].GetObservables());
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        //        *Dep::prediction_B2KstarmumuAng_0p1_4_Belle,
        *Dep::prediction_B2KstarmumuAng_4_8_Belle,
        *Dep::prediction_B2KstarmumuAng_10p9_12p9_Belle,
        *Dep::prediction_B2KstarmumuAng_14p18_19_Belle,
      };

      result = 0;
      for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
      {
        result += nDimBifurGaussian[i].GetLogLikelihood(get_obs_theory(prediction[i], obs_list), get_obs_covariance(prediction[i], obs_list));
      }

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_Belle result: " << result << std::endl;
    }
    
    /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    void HEPLike_B2KstarmumuAng_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/PH-EP-2015-314_q2_";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimBifurGaussian> nDimBifurGaussian = {
        HepLike_default::HL_nDimBifurGaussian(inputfile + "0.1_0.98.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "1.1_2.5.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "2.5_4.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "4.0_6.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "6.0_8.0.yaml"),
        HepLike_default::HL_nDimBifurGaussian(inputfile + "15.0_19.yaml"),
      };

      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimBifurGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
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
    void HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/CERN-EP-2020-027_q2_";
      if (flav_debug) std::cout << "Starting HEPLike_B2KstarmumuAng_LogLikelihood_LHCb_2020"<<std::endl;
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        HepLike_default::HL_nDimGaussian(inputfile + "0.1_0.98.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "1.1_2.5.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.5_4.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_6.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "6.0_8.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "15.0_19.0.yaml"),
      };
      if (flav_debug) std::cout << inputfile + "15.0_19.yaml"<<std::endl;
      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
          nDimGaussian[i].Read();
          if (flav_debug) std::cout << "Read"<<endl;
        }
        if (flav_debug) std::cout <<" Read all"<<endl;
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }
      if (flav_debug) std::cout << "READ"<<std::endl;
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
     /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    void HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_LHCb_2020(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_LHCb_2020;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/CERN-EP-2020-027_q2_";
      if (flav_debug) std::cout << "Starting HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_LHCb_2020"<<std::endl;
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        //      HepLike_default::HL_nDimGaussian(inputfile + "0.1_0.98.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "1.1_2.5.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.5_4.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_6.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "6.0_8.0.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "15.0_19.0.yaml"),
      };
      if (flav_debug) std::cout << inputfile + "15.0_19.yaml"<<std::endl;
      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
          nDimGaussian[i].Read();
        }
        update_obs_list(obs_list, nDimGaussian[0].GetObservables());
        first = false;
      }
      if (flav_debug) std::cout << "READ"<<std::endl;
      std::vector<flav_prediction> prediction = {
        //   *Dep::prediction_B2KstarmumuAng_0p1_0p98_LHCb,
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

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_LHCb 2020 result: " << result << std::endl;
    }


    
     /// HEPLike LogLikelihood B -> K* mu mu Angular (LHCb)
    void HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Angular/PH-EP-2015-314_q2_";
      static std::vector<str> obs_list = runOptions->getValue<std::vector<str>>("obs_list");
      static std::vector<HepLike_default::HL_nDimGaussian> nDimGaussian = {
        HepLike_default::HL_nDimGaussian(inputfile + "0.1_0.98_CPA.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "1.1_2.5_CPA.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "2.5_4.0_CPA.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "4.0_6.0_CPA.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "6.0_8.0_CPA.yaml"),
        HepLike_default::HL_nDimGaussian(inputfile + "15.0_19_CPA.yaml"),
      };
      if (flav_debug) std::cout << inputfile + "0.1_0.98_CPA.yaml" <<std::endl;
      static bool first = true;
      if (first)
      {
        for (unsigned int i = 0; i < nDimGaussian.size(); i++)
        {
          if (flav_debug) std::cout << "Debug: Reading HepLike data file: " << i << endl;
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

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_CPAssym_LogLikelihood_LHCb  result: " << result << std::endl;
    }


    /// HEPLike LogLikelihood B -> K* mu mu Br (LHCb)
    void HEPLike_B2KstarmumuBr_NoLowq2_LogLikelihood_LHCb(double &result)
    {
      using namespace Pipes::HEPLike_B2KstarmumuBr_NoLowq2_LogLikelihood_LHCb;
      static const std::string inputfile = path_to_latest_heplike_data() + "/data/LHCb/RD/Bd2KstarMuMu_Br/CERN-EP-2016-141_q2_";
      static std::vector<HepLike_default::HL_BifurGaussian> BifurGaussian = {
        //       HepLike_default::HL_BifurGaussian(inputfile + "0.1_0.98.yaml"),
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << endl;
          BifurGaussian[i].Read();
        }
        first = false;
      }

      std::vector<flav_prediction> prediction = {
        //    *Dep::prediction_B2KstarmumuBr_0p1_0p98,
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

      if (flav_debug) std::cout << "HEPLike_B2KstarmumuAng_NoLowq2_LogLikelihood_LHCb result: " << result << std::endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << endl;
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
      cout<<"kstarmumu Br"<<endl;
        
      for (unsigned int i = 0; i < BifurGaussian.size(); i++)
      {
        double theory = prediction[i].central_values.begin()->second;
        double theory_variance = prediction[i].covariance.begin()->second.begin()->second;
        cout<<theory<<endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << endl;
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
          if (flav_debug) std::cout << "Debug: Reading HepLike data file " << i << endl;
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

    

    
    void HEPLike_RK_LogLikelihood(double &result)
    {

      using namespace Pipes::HEPLike_RK_LogLikelihood;


      static const std::string inputfile_0 = path_to_latest_heplike_data() + "/data/LHCb/RD/Rk/CERN-EP-2019-043.yaml";
      static HepLike_default::HL_ProfLikelihood rk(inputfile_0);


      static bool first = true;
      if (first)
      {
        std::cout << "Debug: Reading HepLike data file: " << inputfile_0 << endl;
        rk.Read();

        first = false;
      }
      static const std::vector<std::string> observables{
              "R-1_BKll_1.1_6",
      };


      flav_observable_map theory = *Dep::SuperIso_obs_values;
      flav_covariance_map theory_covariance;

      theory_covariance     = *Dep::SuperIso_theory_covariance;



      result = rk.GetLogLikelihood(
                                   1.+theory[observables[0]],
                                   theory_covariance[observables[0]][observables[0]]
                                   );

      if (flav_debug) std::cout << "HEPLike_RK_LogLikelihood result: " << result << std::endl;

    }



    void HEPLike_RKstar_LogLikelihood_LHCb(double &result)
    {

      using namespace Pipes::HEPLike_RKstar_LogLikelihood_LHCb;


      static const std::string inputfile_0 = path_to_latest_heplike_data() + "/data/LHCb/RD/RKstar/CERN-EP-2017-100_q2_0.045_1.1.yaml";
      static const std::string inputfile_1 = path_to_latest_heplike_data() + "/data/LHCb/RD/RKstar/CERN-EP-2017-100_q2_1.1_6.yaml";
      static HepLike_default::HL_ProfLikelihood rkstar1(inputfile_0);
      static HepLike_default::HL_ProfLikelihood rkstar2(inputfile_1);

      static bool first = true;
      if (first)
      {
        std::cout << "Debug: Reading HepLike data file: " << inputfile_0 << endl;
        rkstar1.Read();
        rkstar2.Read();
        first = false;
      }
      static const std::vector<std::string> observables{
        "R-1_B0Kstar0ll_0.045_1.1",
        "R-1_B0Kstar0ll_1.1_6",
      };

      flav_observable_map theory = *Dep::SuperIso_obs_values;
      flav_covariance_map theory_covariance;

      theory_covariance     = *Dep::SuperIso_theory_covariance;


      result = rkstar1.GetLogLikelihood(
                                         1.+theory[observables[0]],
                                         theory_covariance[observables[0]][observables[0]]
                                        );

      result+= rkstar2.GetLogLikelihood(

                                        1.+theory[observables[1]],
                                        theory_covariance[observables[1]][observables[1]]
                                        );
      if (flav_debug) std::cout << "HEPLike_RKstar_LogLikelihood_LHCb result: " << result << std::endl;

    }



  }
}
