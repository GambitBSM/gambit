//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  SUSY-specific sources for ColliderBit.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2023
///
///  *********************************************

#include "gambit/ColliderBit/getPy8Collider.hpp"
#include "gambit/ColliderBit/generateEventPy8Collider.hpp"

namespace Gambit
{
  namespace ColliderBit
  {

    // Get spectrum and decays for Pythia
    //GET_SPECTRUM_AND_DECAYS_FOR_PYTHIA_NONSUSY(getSpectrumAndDecaysForPythia_THDM, THDM_spectrum)

    void getSpectrumAndDecaysForPythia_THDM(SLHAstruct& result)
    {
      using namespace Pipes::getSpectrumAndDecaysForPythia_THDM;
      result.clear();
      /* Get decays */
      result = Dep::decay_rates->getSLHAea(2);
      /* Get spectrum */
      SLHAstruct slha_spectrum = Dep::THDM_spectrum->getSLHAea(2);

      // Add in the Higgs Couplings
      const HiggsCouplingsTable higgs_tbl = *Dep::Higgs_Couplings;

      double H1_coup2d = higgs_tbl.C_ss2.at(0);
      double H1_coup2u = higgs_tbl.C_cc2.at(0);
      double H1_coup2l = higgs_tbl.C_mumu2.at(0);
      double H1_coup2Z = higgs_tbl.C_ZZ.at(0);
      double H1_coup2W = higgs_tbl.C_WW.at(0);

      double H2_coup2d = higgs_tbl.C_ss2.at(1);
      double H2_coup2u = higgs_tbl.C_cc2.at(1);
      double H2_coup2l = higgs_tbl.C_mumu2.at(1);
      double H2_coup2Z = higgs_tbl.C_ZZ.at(1);
      double H2_coup2W = higgs_tbl.C_WW.at(1);
      double H2_coup2H1Z = (higgs_tbl.C_hiZ.at(1)).at(0);
      double H2_coup2HchgW = 0.0; // TODO: NOt yet filled

      double A3_coup2d = higgs_tbl.C_ss2.at(2);
      double A3_coup2u = higgs_tbl.C_cc2.at(2);
      double A3_coup2l = higgs_tbl.C_mumu2.at(2);
      double A3_coup2Z = higgs_tbl.C_ZZ.at(2);
      double A3_coup2W = higgs_tbl.C_WW.at(2);
      double A3_coup2H1Z = (higgs_tbl.C_hiZ.at(2)).at(0);
      double A3_coup2H2Z = (higgs_tbl.C_hiZ.at(2)).at(1);
      double A3_coup2HchgW = 0.0; // TODO: NOt yet filled

      double tanb = Dep::THDM_spectrum->get(Par::dimensionless, "tanb");
      double Hchg_coup2H1W = 0.0; // TODO: NOt yet filled
      double Hchg_coup2H2W = 0.0; // TODO: NOt yet filled

      double H1_coup2Hchg = 0.0; // TODO: NOt yet filled
      double H2_coup2Hchg = 0.0; // TODO: NOt yet filled
      double H2_coup2H1H1 = 0.0; // TODO: NOt yet filled
      double H2_coup2A3A3 = 0.0; // TODO: NOt yet filled
      double H2_coup2A3H1 = 0.0; // TODO: NOt yet filled
      double A3_coup2H1H1 = 0.0; // TODO: NOt yet filled
      double A3_coup2Hchg = 0.0; // TODO: NOt yet filled

      SLHAea_add_block(slha_spectrum, "THDMCOUPLINGS");
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 1, H1_coup2d, "HiggsH1:coup2d", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 2, H1_coup2u, "HiggsH1:coup2u", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 3, H1_coup2l, "HiggsH1:coup2l", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 4, H1_coup2Z, "HiggsH1:coup2Z", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 5, H1_coup2W, "HiggsH1:coup2W", true);

      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 6, H2_coup2d, "HiggsH2:coup2d", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 7, H2_coup2u, "HiggsH2:coup2u", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 8, H2_coup2l, "HiggsH2:coup2l", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 9, H2_coup2Z, "HiggsH2:coup2Z", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 10, H2_coup2W, "HiggsH2:coup2W", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 11, H2_coup2H1Z, "HiggsH2:coup2H1Z", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 12, H2_coup2HchgW, "HiggsH2:coup2HchgW", true);

      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 13, A3_coup2d, "HiggsA3:coup2d", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 14, A3_coup2u, "HiggsA3:coup2u", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 15, A3_coup2l, "HiggsA3:coup2l", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 16, A3_coup2Z, "HiggsA3:coup2Z", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 17, A3_coup2W, "HiggsA3:coup2W", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 18, A3_coup2H1Z, "HiggsA3:coup2H1Z", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 19, A3_coup2H2Z, "HiggsA3:coup2H2Z", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 20, A3_coup2HchgW, "HiggsA3:coup2HchgW", true);

      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 21, tanb, "HiggsHchg:tanBeta", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 22, Hchg_coup2H1W, "HiggsHchg:coup2H1W", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 23, Hchg_coup2H2W, "HiggsHchg:coup2H2W", true);

      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 24, H1_coup2Hchg, "HiggsH1:coup2Hchg", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 25, H2_coup2Hchg, "HiggsH2:coup2Hchg", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 26, H2_coup2H1H1, "HiggsH2:coup2H1H1", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 27, H2_coup2A3A3, "HiggsH2:coup2A3A3", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 28, H2_coup2A3H1, "HiggsH2:coup2A3H1", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 29, A3_coup2H1H1, "HiggsA3:coup2H1H1", true);
      SLHAea_add(slha_spectrum, "THDMCOUPLINGS", 30, A3_coup2Hchg, "HiggsA3:coup2Hchg", true);

      result.insert(result.begin(), slha_spectrum.begin(), slha_spectrum.end());
    }


    // Get Monte Carlo event generator
    GET_SPECIFIC_PYTHIA(getPythia_THDM, Pythia_default, /* blank MODEL_EXTENSION argument */ )
    GET_PYTHIA_AS_BASE_COLLIDER(getPythiaAsBase_THDM)

    // Run event generator
    GET_PYTHIA_EVENT(generateEventPythia_THDM, Pythia_default::Pythia8::Event)

  }
}
