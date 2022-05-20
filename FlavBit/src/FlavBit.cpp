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
///
///  \author Marcin Chrzaszcz
///  \date 2015 May
///  \date 2015 July
///  \date 2015 August
///  \date 2016 July
///  \date 2016 August
///  \date 2016 October
///  \date 2018 Jan
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date 2013 Nov
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 May, June
///  \date 2016 Aug
///  \date 2017 March
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 July
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
#include "gambit/FlavBit/Kstarmumu_theory_err.hpp"
#include "gambit/FlavBit/flav_utils.hpp"
#include "gambit/FlavBit/flav_loop_functions.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Utils/statistics.hpp"
#include "gambit/cmake/cmake_variables.hpp"

//#define FLAVBIT_DEBUG
//#define FLAVBIT_DEBUG_LL

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

    /// Fill SuperIso model info structure
    void SI_fill(parameters &result)
    {
      using namespace Pipes::SI_fill;
      using namespace std;

      SLHAstruct spectrum;
      // Obtain SLHAea object from spectrum
      if (ModelInUse("WC"))
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
        if (spectrum["SMINPUTS"][7].is_data_line()) result.mass_tau=SLHAea::to<double>(spectrum["SMINPUTS"][7][1]);
        if (spectrum["SMINPUTS"][8].is_data_line()) result.mass_nutau2=SLHAea::to<double>(spectrum["SMINPUTS"][8][1]);
        if (spectrum["SMINPUTS"][11].is_data_line()) result.mass_e2=SLHAea::to<double>(spectrum["SMINPUTS"][11][1]);
        if (spectrum["SMINPUTS"][12].is_data_line()) result.mass_nue2=SLHAea::to<double>(spectrum["SMINPUTS"][12][1]);
        if (spectrum["SMINPUTS"][13].is_data_line()) result.mass_mu2=SLHAea::to<double>(spectrum["SMINPUTS"][13][1]);
        if (spectrum["SMINPUTS"][14].is_data_line()) result.mass_numu2=SLHAea::to<double>(spectrum["SMINPUTS"][14][1]);
        if (spectrum["SMINPUTS"][21].is_data_line()) result.mass_d2=SLHAea::to<double>(spectrum["SMINPUTS"][21][1]);
        if (spectrum["SMINPUTS"][22].is_data_line()) result.mass_u2=SLHAea::to<double>(spectrum["SMINPUTS"][22][1]);
        if (spectrum["SMINPUTS"][23].is_data_line()) result.mass_s2=SLHAea::to<double>(spectrum["SMINPUTS"][23][1]);
        if (spectrum["SMINPUTS"][24].is_data_line()) result.mass_c2=SLHAea::to<double>(spectrum["SMINPUTS"][24][1]);
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
        if (spectrum["MASS"][4].is_data_line()) result.mass_c=SLHAea::to<double>(spectrum["MASS"][4][1]);
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

      else if (ModelInUse("WC"))
      {
        // The Higgs mass doesn't come through in the SLHAea object, as that's only for SLHA2 SM inputs.
        result.mass_h0 = Dep::SM_spectrum->get(Par::Pole_Mass, "h0_1");
        // Set the scale.
        result.Q = result.mass_Z;
      }

      BEreq::slha_adjust(&result);

      // Set the Z and W widths
      result.width_Z = Dep::Z_decay_rates->width_in_GeV;
      result.width_W = Dep::W_plus_decay_rates->width_in_GeV;

      // If requested, override the SuperIso b pole mass with the SpecBit value and recompute the 1S b mass.
      if (runOptions->getValueOrDef<bool>(false, "take_b_pole_mass_from_spectrum"))
      {
        if (ModelInUse("MSSM63atMGUT") or ModelInUse("MSSM63atQ"))
        {
          result.mass_h0 = Dep::MSSM_spectrum->get(Par::Pole_Mass, "h0_1");
        }
        else if (ModelInUse("WC"))
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
        // SuperIso can actually only handle real O_7, O_9 and O_10 too, so the imaginary
        // parts of those operators get ignored in subsequent calculations.
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

      }

      if (flav_debug) cout<<"Finished SI_fill"<<endl;
    }


    /// Br b-> s gamma decays
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


    /// B->K mu nu / B-> pi mu nu
    void SI_Rmu(double &result)
    {
      using namespace Pipes::SI_Rmu;
      if (flav_debug) cout<<"Starting SI_Rmu"<<endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result = BEreq::Kmunu_pimunu(&param);

      if (flav_debug) printf("R_mu=BR(K->mu nu)/BR(pi->mu nu)=%.3e\n",result);
      if (flav_debug) cout<<"Finished SI_Rmu"<<endl;
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
    DEFINE_BKSTARMUMU(1.1, 2.5, 11, 25)
    DEFINE_BKSTARMUMU(2.5, 4.0, 25, 40)
    DEFINE_BKSTARMUMU(4.0, 6.0, 40, 60)
    DEFINE_BKSTARMUMU(6.0, 8.0, 60, 80)
    DEFINE_BKSTARMUMU(15., 17., 15, 17)
    DEFINE_BKSTARMUMU(17., 19., 17, 19)
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

      pmc.diff.clear();
      for (int i=0;i<n_experiments;++i)
      {
        pmc.diff.push_back(pmc.value_exp(i,0)-pmc.value_th(i,0));
      }

      if (flav_debug) cout<<"Finished b2sll_measurements function"<<endl;
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
          Chi2+= diff[i] * cov_inv(i,j)*diff[j] ;
        }
      }

      result=-0.5*Chi2;

      if (flav_debug) cout<<"Finished b2sll_likelihood"<<endl;
      if (flav_debug_LL) cout<<"Likelihood result b2sll_likelihood : "<< result<<endl;

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

      const int n_experiments=8;
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



  }
}
