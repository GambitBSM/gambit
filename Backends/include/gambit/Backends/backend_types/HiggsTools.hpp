//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of types for the HiggsTools backend.
///
///  Replaces the older HiggsBounds.hpp / hb_ModelParameters[_effC] structs
///  used by the Fortran HiggsBounds and HiggsSignals backends.
///
///  *********************************************

#ifndef __HiggsTools_types_hpp__
#define __HiggsTools_types_hpp__

#include <vector>

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{
  /// Container for HiggsTools input (masses, widths, BRs, effective couplings).
  /// All vectors of length n_neutral or n_charged; BR_hjhihi is n_neutral x
  /// n_neutral (BR_hjhihi[i][j] = BF(h_i -> h_j h_j)).  The frontend converts
  /// this struct to a Python dict and hands it to the HiggsTools wrapper.
  struct HiggsTools_input
  {
    int n_neutral;
    int n_charged;

    // Neutral Higgs sector
    std::vector<double> Mh;
    std::vector<double> deltaMh;
    std::vector<double> hGammaTot;
    std::vector<double> CP;
    std::vector<double> BR_hjss;
    std::vector<double> BR_hjcc;
    std::vector<double> BR_hjbb;
    std::vector<double> BR_hjmumu;
    std::vector<double> BR_hjtautau;
    std::vector<double> BR_hjWW;
    std::vector<double> BR_hjZZ;
    std::vector<double> BR_hjZga;
    std::vector<double> BR_hjgaga;
    std::vector<double> BR_hjgg;
    std::vector<double> BR_hjinvisible;
    std::vector<std::vector<double>> BR_hjhihi;

    // Effective couplings squared (relative to a SM Higgs of the same mass)
    std::vector<double> g2hjss;
    std::vector<double> g2hjcc;
    std::vector<double> g2hjbb;
    std::vector<double> g2hjtt;
    std::vector<double> g2hjmumu;
    std::vector<double> g2hjtautau;
    std::vector<double> g2hjWW;
    std::vector<double> g2hjZZ;
    std::vector<double> g2hjgaga;
    std::vector<double> g2hjZga;
    std::vector<double> g2hjgg;

    // Charged Higgs sector
    std::vector<double> MHplus;
    std::vector<double> deltaMHplus;
    std::vector<double> HpGammaTot;
    std::vector<double> BR_Hpjcs;
    std::vector<double> BR_Hpjcb;
    std::vector<double> BR_Hptaunu;

    // Top quark BRs
    double BR_tWpb;
    std::vector<double> BR_tHpjb;
  };
}

#endif
