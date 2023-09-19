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
///          (tomas.gonzalo@kit.edu)
///  \date 2017 July
///  \date 2022 Aug
///
///  \author Cristian Sierra
///          (cristian.sierra@monash.edu)
///  \date 2020 June-December
///  \date 2021 Jan-Sep
///  \date 2022 June
///
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

#include "gambit/Utils/statistics.hpp"
#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum_types.hpp"
#include "gambit/FlavBit/FlavBit_rollcall.hpp"
#include "gambit/FlavBit/FlavBit_types.hpp"
#include "gambit/FlavBit/Flav_reader.hpp"
#include "gambit/FlavBit/FlavBit_utils.hpp"

namespace Gambit
{

  namespace FlavBit
  {

    /// Fill SuperIso model info structure
    void SuperIso_fill(parameters &result)
    {
      using namespace Pipes::SuperIso_fill;

      SLHAstruct spectrum;
      // Obtain SLHAea object from spectrum
      if (ModelInUse("GWC"))
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
        SLHAea_add(spectrum,"MODSEL",1, -3, "THDM", false);
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

          case -3:
            // THDM model parameters
            if(spectrum["FMODSEL"][1].is_data_line()) result.THDM_model=(SLHAea::to<int>(spectrum["FMODSEL"][1][1]) - 30);
            if (result.THDM_model == 0) result.THDM_model=-3;
            if(spectrum["FMODSEL"][5].is_data_line()) result.CPV=SLHAea::to<int>(spectrum["FMODSEL"][5][1]);
            if(spectrum["MINPAR"][3].is_data_line())  result.tan_beta=SLHAea::to<double>(spectrum["MINPAR"][3][1]);
            if(spectrum["MINPAR"][18].is_data_line()) result.m12=SLHAea::to<double>(spectrum["MINPAR"][18][1]);
            if(spectrum["ALPHA"][0].is_data_line()) result.alpha=SLHAea::to<double>(spectrum["ALPHA"][0][1]);
            if (!spectrum["MSOFT"].empty()) {
              if (!spectrum["MSOFT"].front().empty()) result.MSOFT_Q=SLHAea::to<double>(spectrum["MSOFT"].front().at(3));
            }
            {
              double beta = Dep::THDM_spectrum->get_HE().get(Par::dimensionless, "beta");
              THDM_TYPE model_type = (THDM_TYPE) Dep::THDM_spectrum->get_HE().get(Par::dimensionless, "model_type");

              for(int i=1; i<4; i++)
              {
                // NOTE: SuperISO expects the reduced H+ff couplings (no mass factors)
                switch(model_type)
                {
                  case TYPE_I:
                    result.lambda_u[i][i] = 1/tan(beta);
                    result.lambda_d[i][i] = 1/tan(beta);
                    result.lambda_l[i][i] = 1/tan(beta);
                    break;
                  case TYPE_II:
                    result.lambda_u[i][i] = 1/tan(beta);
                    result.lambda_d[i][i] = -tan(beta);
                    result.lambda_l[i][i] = -tan(beta);
                    break;
                  case TYPE_LS:
                    result.lambda_u[i][i] = 1/tan(beta);
                    result.lambda_d[i][i] = 1/tan(beta);
                    result.lambda_l[i][i] = -tan(beta);
                    break;
                  case TYPE_flipped:
                    result.lambda_u[i][i] = 1/tan(beta);
                    result.lambda_d[i][i] = -tan(beta);
                    result.lambda_l[i][i] = 1/tan(beta);
                    break;
                  case TYPE_III:
                    for(int j=1;j<4;j++)
                    {
                      result.lambda_u[i][j] = SLHAea::to<double>(spectrum["YU1"].at(i,j)[2]);
                      result.lambda_d[i][j] = SLHAea::to<double>(spectrum["YD1"].at(i,j)[2]);
                      result.lambda_l[i][j] = SLHAea::to<double>(spectrum["YE1"].at(i,j)[2]);
                    }
                    break;
                  default:
                    FlavBit_error().raise(LOCAL_INFO, "invalid model type");
                }
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

      else if (ModelInUse("GWC"))
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
        else if (ModelInUse("GWC"))
        {
          result.mass_h0 = Dep::SM_spectrum->get(Par::Pole_Mass, "h0_1");
        }
        result.mass_b_1S = BEreq::mb_1S(&result);
      }

      if (ModelInUse("GWC"))
      {

        // Tell SuperIso to do its Wilson coefficient calculations for the SM.
        // We will adjust them with our BSM deviations in backend convenience
        // functions before we send them to SuperIso's observable calculation functions.
        // So far our model only deals with 5 operators: O_7, O_9, O_10, Q_1 and Q_2.
        result.SM = 1;

        // Fill the flavour-independent WCs too, for backwards compatibility with functions in SuperIso that don't take into account LFUV yet.
        result.Re_DeltaC7  = *Param["Re_DeltaC7_mu"];
        result.Im_DeltaC7  = *Param["Im_DeltaC7_mu"];
        result.Re_DeltaC9  = *Param["Re_DeltaC9_mu"];
        result.Im_DeltaC9  = *Param["Im_DeltaC9_mu"];
        result.Re_DeltaC10 = *Param["Re_DeltaC10_mu"];
        result.Im_DeltaC10 = *Param["Im_DeltaC10_mu"];
        result.Re_DeltaCQ1 = *Param["Re_DeltaCQ1_mu"];
        result.Im_DeltaCQ1 = *Param["Im_DeltaCQ1_mu"];
        result.Re_DeltaCQ2 = *Param["Re_DeltaCQ2_mu"];
        result.Im_DeltaCQ2 = *Param["Im_DeltaCQ2_mu"];

        result.Re_DeltaC7_Prime  = *Param["Re_DeltaC7_mu_Prime"];
        result.Im_DeltaC7_Prime  = *Param["Im_DeltaC7_mu_Prime"];
        result.Re_DeltaC9_Prime  = *Param["Re_DeltaC9_mu_Prime"];
        result.Im_DeltaC9_Prime  = *Param["Im_DeltaC9_mu_Prime"];
        result.Re_DeltaC10_Prime = *Param["Re_DeltaC10_mu_Prime"];
        result.Im_DeltaC10_Prime = *Param["Im_DeltaC10_mu_Prime"];
        result.Re_DeltaCQ1_Prime = *Param["Re_DeltaCQ1_mu_Prime"];
        result.Im_DeltaCQ1_Prime = *Param["Im_DeltaCQ1_mu_Prime"];
        result.Re_DeltaCQ2_Prime = *Param["Re_DeltaCQ2_mu_Prime"];
        result.Im_DeltaCQ2_Prime = *Param["Im_DeltaCQ2_mu_Prime"];

        // Flavour dependent WCs
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

        result.Re_DeltaC7_mu_Prime  = *Param["Re_DeltaC7_mu_Prime"];
        result.Im_DeltaC7_mu_Prime  = *Param["Im_DeltaC7_mu_Prime"];
        result.Re_DeltaC9_mu_Prime  = *Param["Re_DeltaC9_mu_Prime"];
        result.Im_DeltaC9_mu_Prime  = *Param["Im_DeltaC9_mu_Prime"];
        result.Re_DeltaC10_mu_Prime = *Param["Re_DeltaC10_mu_Prime"];
        result.Im_DeltaC10_mu_Prime = *Param["Im_DeltaC10_mu_Prime"];
        result.Re_DeltaCQ1_mu_Prime = *Param["Re_DeltaCQ1_mu_Prime"];
        result.Im_DeltaCQ1_mu_Prime = *Param["Im_DeltaCQ1_mu_Prime"];
        result.Re_DeltaCQ2_mu_Prime = *Param["Re_DeltaCQ2_mu_Prime"];
        result.Im_DeltaCQ2_mu_Prime = *Param["Im_DeltaCQ2_mu_Prime"];

        result.Re_DeltaC7_e_Prime  = *Param["Re_DeltaC7_e_Prime"];
        result.Im_DeltaC7_e_Prime  = *Param["Im_DeltaC7_e_Prime"];
        result.Re_DeltaC9_e_Prime  = *Param["Re_DeltaC9_e_Prime"];
        result.Im_DeltaC9_e_Prime  = *Param["Im_DeltaC9_e_Prime"];
        result.Re_DeltaC10_e_Prime = *Param["Re_DeltaC10_e_Prime"];
        result.Im_DeltaC10_e_Prime = *Param["Im_DeltaC10_e_Prime"];
        result.Re_DeltaCQ1_e_Prime = *Param["Re_DeltaCQ1_e_Prime"];
        result.Im_DeltaCQ1_e_Prime = *Param["Im_DeltaCQ1_e_Prime"];
        result.Re_DeltaCQ2_e_Prime = *Param["Re_DeltaCQ2_e_Prime"];
        result.Im_DeltaCQ2_e_Prime = *Param["Im_DeltaCQ2_e_Prime"];

        result.Re_DeltaC7_tau_Prime  = *Param["Re_DeltaC7_tau_Prime"];
        result.Im_DeltaC7_tau_Prime  = *Param["Im_DeltaC7_tau_Prime"];
        result.Re_DeltaC9_tau_Prime  = *Param["Re_DeltaC9_tau_Prime"];
        result.Im_DeltaC9_tau_Prime  = *Param["Im_DeltaC9_tau_Prime"];
        result.Re_DeltaC10_tau_Prime = *Param["Re_DeltaC10_tau_Prime"];
        result.Im_DeltaC10_tau_Prime = *Param["Im_DeltaC10_tau_Prime"];
        result.Re_DeltaCQ1_tau_Prime = *Param["Re_DeltaCQ1_tau_Prime"];
        result.Im_DeltaCQ1_tau_Prime = *Param["Im_DeltaCQ1_tau_Prime"];
        result.Re_DeltaCQ2_tau_Prime = *Param["Re_DeltaCQ2_tau_Prime"];
        result.Im_DeltaCQ2_tau_Prime = *Param["Im_DeltaCQ2_tau_Prime"];

        /* Lines below are valid in the flavour NON-universal case
           deltaC[1..10] = Cmu[1..10], deltaC[11..20] = Ce[1..10], deltaC[21..30] = Ctau[1..10]
           deltaCQ[1,2] = CQmu[1,2], deltaCQ[1,2] = CQe[1,2], deltaCQ[1,2] = CQtau[1,2] */

        // left handed:
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

        // Right-handed:
        result.deltaCp[7]=std::complex<double>(result.Re_DeltaC7_mu_Prime, result.Im_DeltaC7_mu_Prime);
        result.deltaCp[9]=std::complex<double>(result.Re_DeltaC9_mu_Prime, result.Im_DeltaC9_mu_Prime);
        result.deltaCp[10]=std::complex<double>(result.Re_DeltaC10_mu_Prime, result.Im_DeltaC10_mu_Prime);
        result.deltaCQp[1]=std::complex<double>(result.Re_DeltaCQ1_mu_Prime, result.Im_DeltaCQ1_mu_Prime);
        result.deltaCQp[2]=std::complex<double>(result.Re_DeltaCQ2_mu_Prime, result.Im_DeltaCQ2_mu_Prime);

        result.deltaCp[17]=std::complex<double>(result.Re_DeltaC7_e_Prime, result.Im_DeltaC7_e_Prime);
        result.deltaCp[19]=std::complex<double>(result.Re_DeltaC9_e_Prime, result.Im_DeltaC9_e_Prime);
        result.deltaCp[20]=std::complex<double>(result.Re_DeltaC10_e_Prime, result.Im_DeltaC10_e_Prime);
        result.deltaCQp[3]=std::complex<double>(result.Re_DeltaCQ1_e_Prime, result.Im_DeltaCQ1_e_Prime);
        result.deltaCQp[4]=std::complex<double>(result.Re_DeltaCQ2_e_Prime, result.Im_DeltaCQ2_e_Prime);

        result.deltaCp[27]=std::complex<double>(result.Re_DeltaC7_tau_Prime, result.Im_DeltaC7_tau_Prime);
        result.deltaCp[29]=std::complex<double>(result.Re_DeltaC9_tau_Prime, result.Im_DeltaC9_tau_Prime);
        result.deltaCp[30]=std::complex<double>(result.Re_DeltaC10_tau_Prime, result.Im_DeltaC10_tau_Prime);
        result.deltaCQp[5]=std::complex<double>(result.Re_DeltaCQ1_tau_Prime, result.Im_DeltaCQ1_tau_Prime);
        result.deltaCQp[6]=std::complex<double>(result.Re_DeltaCQ2_tau_Prime, result.Im_DeltaCQ2_tau_Prime);
      }

      // @asw ONLY use new WC interface for Type-III
      if (ModelInUse("THDM") or ModelInUse("THDMatQ"))
      {
        THDM_TYPE model_type = (THDM_TYPE) Dep::THDM_spectrum->get_HE().get(Par::dimensionless, "model_type");

        if (model_type != TYPE_III)
        {
          result.SM = 0;
          result.model = 10;
          result.THDM_model = (int)model_type;
        }
        else
        {
          result.SM = 1;
          result.model = -3; //force SI to read the THDM as an EFT
          result.Re_DeltaC2  = Dep::DeltaC2->real();
          result.Im_DeltaC2  = Dep::DeltaC2->imag();
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

          result.deltaC[2]=std::complex<double>(result.Re_DeltaC2, result.Im_DeltaC2);
          result.deltaC[7]=std::complex<double>(result.Re_DeltaC7, result.Im_DeltaC7);
          result.deltaC[8]=std::complex<double>(result.Re_DeltaC8, result.Im_DeltaC8);
          result.deltaC[9]=std::complex<double>(result.Re_DeltaC9, result.Im_DeltaC9);
          result.deltaC[10]=std::complex<double>(result.Re_DeltaC10, result.Im_DeltaC10);
          result.deltaCQ[1]=std::complex<double>(result.Re_DeltaCQ1, result.Im_DeltaCQ1);
          result.deltaCQ[2]=std::complex<double>(result.Re_DeltaCQ2, result.Im_DeltaCQ2);

          // Prime WCs
          result.Re_DeltaC7_Prime  = Dep::DeltaC7_Prime->real();
          result.Im_DeltaC7_Prime  = Dep::DeltaC7_Prime->imag();
          result.Re_DeltaC8_Prime  = Dep::DeltaC8_Prime->real();
          result.Im_DeltaC8_Prime  = Dep::DeltaC8_Prime->imag();
          result.Re_DeltaC9_Prime  = Dep::DeltaC9_Prime->real();
          result.Im_DeltaC9_Prime  = Dep::DeltaC9_Prime->imag();
          result.Im_DeltaC10_Prime = Dep::DeltaC10_Prime->imag();
          result.Re_DeltaCQ1_Prime = Dep::DeltaCQ1_Prime->real();
          result.Im_DeltaCQ1_Prime = Dep::DeltaCQ1_Prime->imag();
          result.Re_DeltaCQ2_Prime = Dep::DeltaCQ2_Prime->real();
          result.Im_DeltaCQ2_Prime = Dep::DeltaCQ2_Prime->imag();

          result.deltaCp[7]=std::complex<double>(result.Re_DeltaC7_Prime, result.Im_DeltaC7_Prime);
          result.deltaCp[8]=std::complex<double>(result.Re_DeltaC8_Prime, result.Im_DeltaC8_Prime);
          result.deltaCp[9]=std::complex<double>(result.Re_DeltaC9_Prime, result.Im_DeltaC9_Prime);
          result.deltaCp[10]=std::complex<double>(result.Re_DeltaC10_Prime, result.Im_DeltaC10_Prime);
          result.deltaCQp[1]=std::complex<double>(result.Re_DeltaCQ1_Prime, result.Im_DeltaCQ1_Prime);
          result.deltaCQp[2]=std::complex<double>(result.Re_DeltaCQ2_Prime, result.Im_DeltaCQ2_Prime);

          //tautau WCs
          result.Re_DeltaC9_tau  = Dep::DeltaC9_tautau->real();
          result.Im_DeltaC9_tau  = Dep::DeltaC9_tautau->imag();
          result.Re_DeltaC10_tau = Dep::DeltaC10_tautau->real();
          result.Im_DeltaC10_tau = Dep::DeltaC10_tautau->imag();
          result.Re_DeltaCQ1_tau = Dep::DeltaCQ1_tautau->real();
          result.Im_DeltaCQ1_tau = Dep::DeltaCQ1_tautau->imag();
          result.Re_DeltaCQ2_tau = Dep::DeltaCQ2_tautau->real();
          result.Im_DeltaCQ2_tau = Dep::DeltaCQ2_tautau->imag();
          // tautau Prime WCs
          result.Re_DeltaC9_tau_Prime  = Dep::DeltaC9_tautau_Prime->real();
          result.Im_DeltaC9_tau_Prime  = Dep::DeltaC9_tautau_Prime->imag();
          result.Re_DeltaC10_tau_Prime = Dep::DeltaC10_tautau_Prime->real();
          result.Im_DeltaC10_tau_Prime = Dep::DeltaC10_tautau_Prime->imag();
          result.Re_DeltaCQ1_tau_Prime = Dep::DeltaCQ1_tautau_Prime->real();
          result.Im_DeltaCQ1_tau_Prime = Dep::DeltaCQ1_tautau_Prime->imag();
          result.Re_DeltaCQ2_tau_Prime = Dep::DeltaCQ2_tautau_Prime->real();
          result.Im_DeltaCQ2_tau_Prime = Dep::DeltaCQ2_tautau_Prime->imag();
        }
      }
      if (flav_debug) std::cout << "Finished SuperIso_fill" << std::endl;
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

    ///  Bc lifetime in the THDM
    void THDM_Bc_lifetime(double &result)
    {
      using namespace Pipes::THDM_Bc_lifetime;
      if (flav_debug) std::cout<<"Starting THDM_Bc_lifetime"<< std::endl;

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
      const double v = spectrum.get(Par::mass1, "vev");
      const double CSMcb = 4*sminputs.GF*Vcb/sqrt(2.0);
      const double mTau = Dep::SMINPUTS->mTau;
      const double mBmB = Dep::SMINPUTS->mBmB;
      double mHp = spectrum.get(Par::Pole_Mass,"H+");
      const double m_Bc = 6.2749;//Values taken from SuperIso 3.6
      const double f_Bc = 0.434;
      const double hbar = 6.582119514e-25;
      const double mCmC = Dep::SMINPUTS->mCmC;
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytautau(spectrum.get(Par::dimensionless,"Ye2",3,3), spectrum.get(Par::dimensionless, "ImYe2",3,3));
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> Ybb(spectrum.get(Par::dimensionless,"Yd2",3,3), spectrum.get(Par::dimensionless, "ImYd2",3,3));
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xitc = Ytc/cosb;
      std::complex<double> xibb = -((sqrt(2)*mBmB*tanb)/v) + Ybb/cosb;
      std::complex<double> xisb = Ysb/cosb;
      std::complex<double> xitautau = -((sqrt(2)*mTau*tanb)/v) + Ytautau/cosb;
      std::complex<double> ximutau = Ymutau/cosb;
      std::complex<double> Ycc(spectrum.get(Par::dimensionless,"Yu2",2,2), spectrum.get(Par::dimensionless, "ImYu2",2,2));
      std::complex<double> xicc = -((sqrt(2)*mCmC*tanb)/v) + Ycc/cosb;
      std::complex<double> CRcb = -2.*(Vcb*xibb+Vcs*xisb)*conj(xitautau)/pow(mHp,2);
      std::complex<double> CLcb = 2.*(Vcb*conj(xicc)+Vtb*conj(xitc))*conj(xitautau)/pow(mHp,2);
      std::complex<double> CRcbmutau = -2.*(Vcb*xibb+Vcs*xisb)*conj(ximutau)/pow(mHp,2);
      std::complex<double> CLcbmutau = 2.*(Vcb*conj(xicc)+Vtb*conj(xitc))*conj(ximutau)/pow(mHp,2);
      std::complex<double> gp =  (CRcb - CLcb)/CSMcb;
      std::complex<double> gpmutau =  (CRcbmutau - CLcbmutau)/CSMcb;

      std::complex<double> factor = {(m_Bc*m_Bc/(mTau*(mBmB+mCmC))),0};
      std::complex<double> one = {1,0};
      const double Gamma_Bc_SM = (hbar/(0.52e-12)); //Theoretical value in GeV^-1 from 1611.06676
      const double Gamma_Bc_exp = (hbar/(0.510e-12)); //experimental value in GeV^-1
      double BR_Bc_THDM = (1/Gamma_Bc_exp)*((m_Bc*pow(f_Bc,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_Bc,2),2)*pow(Vcb,2))/(8.*pi))*(norm(one + factor*gp)+norm(factor*gpmutau));
      double BR_Bc_SM = (1/Gamma_Bc_exp)*((m_Bc*pow(f_Bc,2)*pow(sminputs.GF,2)*pow(mTau,2)*pow(1 - pow(mTau,2)/pow(m_Bc,2),2)*pow(Vcb,2))/(8.*pi));
      double Gamma_Bc_THDM = (BR_Bc_THDM-BR_Bc_SM)*Gamma_Bc_exp;
      result = hbar/(Gamma_Bc_SM + Gamma_Bc_THDM);

      if (flav_debug) printf("THDM_Bc_lifetime=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_Bc_lifetime"<< std::endl;
    }


    /// Measurement for Delta Bd (Bd mass splitting)
    void SuperIso_prediction_Delta_MBd(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Delta_MBd;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Delta_MBd"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::Delta_MB(&param);

      if (flav_debug) printf("Delta_MBd=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Delta_MBd"<< std::endl;
    }

    /// Measurement for Delta Bs (Bs mass splitting)
    void SuperIso_prediction_Delta_MBs(double &result)
    {
      using namespace Pipes::SuperIso_prediction_Delta_MBs;
      if (flav_debug) std::cout<<"Starting SuperIso_prediction_Delta_MBs"<< std::endl;

      parameters const& param = *Dep::SuperIso_modelinfo;
      result=BEreq::Delta_MBs(&param);

      if (flav_debug) printf("Delta_MBs=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished SuperIso_prediction_Delta_MBs"<< std::endl;
    }

    /// DeltaMBs at tree level for the general THDM
    void THDM_Delta_MBs(double &result)
    {
      using namespace Pipes::THDM_Delta_MBs;
      if (flav_debug) std::cout<<"Starting THDM_Delta_MBs"<< std::endl;

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
      std::complex<double> Ybs(spectrum.get(Par::dimensionless,"Yd2",3,2), spectrum.get(Par::dimensionless, "ImYd2",3,2));
      std::complex<double> xi_bs = Ybs/cosb;
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xi_sb = Ysb/cosb;
      std::complex<double> M12_NP = -(0.125)*(pow(fBs,2)*pow(mBs,3)/(pow(mBmB+mS,2)))*((0.25)*pow(cba,2)*(pow(1/mh,2)-pow(1/mH,2))*((U22*Bag2*b2+U32*Bag3*b3)*(xi_bs*xi_bs+xi_sb*xi_sb)+2*U44*Bag4*b4*xi_sb*xi_bs)+(pow(1/mH,2)*U44*Bag4*b4*xi_sb*xi_bs));
      result = 2*abs(real(0.5*DeltaSM + M12_NP))*conv_factor;
      if (flav_debug) printf("Delta_MBs=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_Delta_MBs"<< std::endl;
    }

    /// BR(h->bs) at tree level for the general THDM from JHEP02(2020)147
    void THDM_h2bs(double &result)
    {
      using namespace Pipes::THDM_h2bs;
      if (flav_debug) std::cout<<"Starting THDM_h2bs"<< std::endl;

      Spectrum spectrum = *Dep::THDM_spectrum;
      const double mBs = 5.36689;// values from 1602.03560
      const double fBs = 0.2303;
      const double Bag2 = 0.806;
      const double Bag3 = 1.10;
      const double Bag4 = 1.022;
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
      std::complex<double> Ybs(spectrum.get(Par::dimensionless,"Yd2",3,2), spectrum.get(Par::dimensionless, "ImYd2",3,2));
      std::complex<double> xi_bs = Ybs/cosb;
      std::complex<double> Ysb(spectrum.get(Par::dimensionless,"Yd2",2,3), spectrum.get(Par::dimensionless, "ImYd2",2,3));
      std::complex<double> xi_sb = Ysb/cosb;
      std::complex<double> M12_NP = -(0.125)*((pow(fBs,2)*pow(mBs, 3))/(pow(mBmB+ mS, 2)))*(0.25*pow(cba,2)*(pow(1/mh, 2) - pow(1/mH, 2))*((U22*Bag2*b2 + U32*Bag3*b3)*(pow(xi_bs, 2) + pow(xi_sb, 2)) + 2*U44*Bag4*b4*xi_sb*xi_bs) + pow(1/mH, 2)*U44*Bag4*b4*xi_sb*xi_bs);
      result = 2*abs(real(M12_NP));
      const double A = (pow(fBs,2)*pow(mBs,3)/(4*pow(mBmB+mS,2)));
      const double Gammah = 4.07e-3;
      const double factor = 2.2; //Factor extracted from JHEP02(2020)147 eq.4.18
      double BRhbs = ((3*pow(mh, 3)*pow(mH, 2))/(16*pi*Gammah*(pow(mH, 2) - pow(mh, 2))))*(1/(A*abs(U22*Bag2*b2 + U32*Bag3*b3 + factor*U44*Bag4*b4)));
      result*= BRhbs;
      if (flav_debug) printf("BR(h->bs)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_h2bs"<< std::endl;
    }

    /// BR(t->ch) at tree level for the general THDM from JHEP02(2020)147
    void THDM_t2ch(double &result)
    {
      using namespace Pipes::THDM_t2ch;
      if (flav_debug) std::cout<<"Starting THDM_t2ch"<< std::endl;
      Spectrum spectrum = *Dep::THDM_spectrum;
      double alpha = spectrum.get(Par::dimensionless,"alpha");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      double cba = cos(beta-alpha);
      const double mT = Dep::SMINPUTS->mT;
      double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      std::complex<double> Yct(spectrum.get(Par::dimensionless,"Yu2",2,3), spectrum.get(Par::dimensionless, "ImYu2",2,3));
      std::complex<double> xi_ct = Yct/cosb;
      std::complex<double> Ytc(spectrum.get(Par::dimensionless,"Yu2",3,2), spectrum.get(Par::dimensionless, "ImYu2",3,2));
      std::complex<double> xi_tc = Ytc/cosb;
      const double Gamma = 1.42;//From PDG 2021 in GeV
      result = real((1/Gamma)*(mT*pow(cba,2)/(32*pi))*(pow(xi_tc,2)+pow(xi_ct,2))*pow(1-pow(mh/mT,2),2));
      if (flav_debug) printf("BR(t->ch)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_t2ch"<< std::endl;
    }

    /// BR(h->taumu) at tree level for the general THDM from JHEP, 06:119, 2019 (ArXiv:1903.10440)
    void THDM_h2taumu(double &result)
    {
      using namespace Pipes::THDM_h2taumu;
      if (flav_debug) std::cout<<"Starting THDM_h2taumu"<< std::endl;
      Spectrum spectrum = *Dep::THDM_spectrum;
      double alpha = spectrum.get(Par::dimensionless,"alpha");
      double tanb = spectrum.get(Par::dimensionless,"tanb");
      double beta = atan(tanb);
      double cosb = cos(beta);
      double cba = cos(beta-alpha);
      const double mTau = Dep::SMINPUTS->mTau;
      double mh = spectrum.get(Par::Pole_Mass,"h0",1);
      std::complex<double> Ymutau(spectrum.get(Par::dimensionless,"Ye2",2,3), spectrum.get(Par::dimensionless, "ImYe2",2,3));
      std::complex<double> Ytaumu(spectrum.get(Par::dimensionless,"Ye2",3,2), spectrum.get(Par::dimensionless, "ImYe2",3,2));
      std::complex<double> xi_mutau = Ymutau/cosb;
      std::complex<double> xi_taumu = Ytaumu/cosb;
      const double Gamma = 0.0032;//From PDG 2021 in GeV
      result = real((1/Gamma)*(3*mh*pow(cba,2)/(8*pi))*(pow(xi_mutau,2)+pow(xi_taumu,2))*pow(1-pow(mTau/mh,2),2));
      if (flav_debug) printf("BR(h->taumu)=%.3e\n",result);
      if (flav_debug) std::cout<<"Finished THDM_h2taumu"<< std::endl;
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

    ///@}

    /// Helper function G
//    double G(const double x)
//    {
//      if(x)
//        return (10.0 - 43.0*x + 78.0*pow(x,2) - 49.0*pow(x,3) + 4.0*pow(x,4) + 18.0*pow(x,3)*log(x)) / (3.0*pow(x - 1,4));
//      else
//        return 10.0/3;
//    }

    ///------------------------///
    ///      Likelihoods       ///
    ///------------------------///


    /// Likelihood for t->ch
    void t2ch_likelihood(double &result)
    {
      using namespace Pipes::t2ch_likelihood;
      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[1];
      double theory[1];

      if (first)
      {
        // Read in experimental measurements
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        fread.read_yaml_measurement("flav_data.yaml", "BR_t2ch");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 1; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::t2ch;
     if(flav_debug) std::cout << "BR(t -> c h) = " << theory[0] << std::endl;

     result = 0;
     for (int i = 0; i < 1; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

    /// Likelihood for h->taumu
    void h2taumu_likelihood(double &result)
    {
      using namespace Pipes::h2taumu_likelihood;
      static bool first = true;
      static boost::numeric::ublas::matrix<double> cov_exp, value_exp;
      static double th_err[1];
      double theory[1];

      if (first)
      {
        // Read in experimental measurements
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);

        fread.read_yaml_measurement("flav_data.yaml", "BR_h2taumu");

        fread.initialise_matrices();
        cov_exp=fread.get_exp_cov();
        value_exp=fread.get_exp_value();

        for (int i = 0; i < 1; ++i)
          th_err[i] = fread.get_th_err()(i,0).first;

        // Init over.
        first = false;
      }

     theory[0] = *Dep::h2taumu;
     if(flav_debug) std::cout << "BR(h -> tau mu) = " << theory[0] << std::endl;

     result = 0;
     for (int i = 0; i < 1; ++i)
       result += Stats::gaussian_upper_limit(theory[i], value_exp(i,0), th_err[i], sqrt(cov_exp(i,i)), false);
    }

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

    /// Likelihood for Delta Md
    void deltaMBd_likelihood(double &result)
    {
      using namespace Pipes::deltaMBd_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_DeltaMd_err, th_err;

      if (flav_debug) std::cout << "Starting Delta_Md_likelihood"<< std::endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in Delta_Md_likelihood"<< std::endl;
        fread.read_yaml_measurement("flav_data.yaml", "DeltaMd");
        fread.initialise_matrices(); // here we have a single measurement ;) so let's be sneaky:
        exp_meas = fread.get_exp_value()(0,0);
        exp_DeltaMd_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) std::cout << "Experiment: " << exp_meas << " " << exp_DeltaMd_err << " " << th_err << std::endl;

      // Now we do the stuff that actually depends on the parameters
      double theory_prediction = *Dep::DeltaMd;
      double theory_DeltaMs_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) std::cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_DeltaMd_err<< std::endl;

      /// Option profile_systematics<bool>: Use likelihood version that has been profiled over systematic errors (default false)
      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_DeltaMs_err, exp_DeltaMd_err, profile);
    }


    /// Likelihood for the Bc lifetime
    void Bc_lifetime_likelihood(double &result)
    {
      using namespace Pipes::Bc_lifetime_likelihood;
      static bool th_err_absolute, first = true;
      static double exp_meas, exp_taulifetime_err, th_err;

      if (flav_debug) std::cout << "Bc_lifetime_likelihood"<< std::endl;

      if (first)
      {
        Flav_reader fread(GAMBIT_DIR  "/FlavBit/data");
        fread.debug_mode(flav_debug);
        if (flav_debug) std::cout<<"Initialised Flav reader in Bc_lifetime_ikelihood"<< std::endl;
        fread.read_yaml_measurement("flav_data.yaml", "Bc_lifetime");
        fread.initialise_matrices();
        exp_meas = fread.get_exp_value()(0,0);
        exp_taulifetime_err = sqrt(fread.get_exp_cov()(0,0));
        th_err = fread.get_th_err()(0,0).first;
        th_err_absolute = fread.get_th_err()(0,0).second;
        first = false;
      }

      if (flav_debug) std::cout << "Experiment: " << exp_meas << " " << exp_taulifetime_err << " " << th_err << std::endl;

      double theory_prediction = *Dep::Bc_lifetime;
      double theory_taulifetime_err = th_err * (th_err_absolute ? 1.0 : std::abs(theory_prediction));
      if (flav_debug) std::cout<<"Theory prediction: "<<theory_prediction<<" +/- "<<exp_taulifetime_err<< std::endl;

      bool profile = runOptions->getValueOrDef<bool>(false, "profile_systematics");

      result = Stats::gaussian_loglikelihood(theory_prediction, exp_meas, theory_taulifetime_err, exp_taulifetime_err, profile);
    }

  }
}
