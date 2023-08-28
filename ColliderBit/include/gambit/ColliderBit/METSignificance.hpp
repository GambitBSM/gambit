//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  MET Significance functions, based on those provided at
///  https://gitlab.cern.ch/atlas-sa/framework
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Chris Chang
///  \date 2023 August
///
///  *********************************************

#include "gambit/ColliderBit/ObjectResolutions.hpp"

namespace Gambit
{

  namespace ColliderBit
  {

    double calcMETSignificance(std::vector<const HEPUtils::Particle*> electrons, std::vector<const HEPUtils::Particle*> photons,
                               std::vector<const HEPUtils::Particle*> muons, std::vector<const HEPUtils::Jet*> jets,
                               std::vector<const HEPUtils::Particle*> taus, HEPUtils::P4 &metVec);


  }
}
