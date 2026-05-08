//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  HiggsTools backend input container (replaces hb_ModelParameters).
///
///  *********************************************

#ifndef __HiggsTools_types_hpp__
#define __HiggsTools_types_hpp__

#include <vector>

#include "gambit/Utils/util_types.hpp"

namespace Gambit
{
  /// Input dict for the HiggsTools Python wrapper.  Per-particle vectors have
  /// length n_neutral or n_charged; BR_hjhihi[i][j] = BF(h_i -> h_j h_j).
  ///
  /// HiggsTools' NeutralEffectiveCouplings has 15 fields; we fill these 11.
  /// The wrapper (init_by_GAMBIT.py) defaults dd/uu/ee from second-gen and
  /// lam = 1 (SM-aligned).  If a future model needs non-MFV first-gen
  /// Yukawas or a non-SM trilinear, extend HiggsCouplingsTable accordingly,
  /// add fields here, and drop the wrapper defaults.
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

    // Effective couplings squared (relative to a SM Higgs of the same mass).
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
