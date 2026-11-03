//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Simple function for returning the cross section ratio 
///  R = sigma(e+e- -> hadrons)/sigma(e+e- -> mu+mu-)
///  as a function of the photon virtuality,
///  as read from data files from the PDG 
///  https://pdg.lbl.gov/2020/hadronic-xsections/hadron.html
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Felix Kahlhoefer
///  2022 May
///
///  *********************************************


#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/daFunk.hpp"
#include "gambit/Utils/util_types.hpp"

namespace Gambit
{  
  /// Hadronic cross section ratio as function of centre-of-mass energy [GeV] (0.3 - 188 GeV)
  double hadronic_cross_section_ratio(double,bool);
  
}
