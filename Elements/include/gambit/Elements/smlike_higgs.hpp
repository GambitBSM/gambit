//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper function to determine which Higgs is
///  most SM-like.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Peter Athron
///          (peter.athron@coepp.org.au)
///  \date 2017
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2017
///
///  *********************************************

#include "gambit/Elements/spectrum.hpp"

namespace Gambit
{

  /// Determine which MSSM higgs is most SM-like.
  /// Needs expansion to work with non-MSSM (e.g. *HDM) models
  int SMlike_higgs_PDG_code(const Spectrum&);

}
