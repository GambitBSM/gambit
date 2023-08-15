//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///  \file
///
///  Object resolution functions, based on those provided at
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

#include "HEPUtils/Jet.h"
#include "HEPUtils/Vectors.h"
#include "HEPUtils/Particle.h"

namespace Gambit
{

  namespace ColliderBit
  {

    void getElectronResolution(const HEPUtils::Particle* obj, double &pt_reso,double &phi_reso);

    void getMuonResolution(const HEPUtils::Particle* obj, double &pt_reso,double &phi_reso);

    void getTauResolution(const HEPUtils::Particle* obj, double &pt_reso, double &phi_reso);

    void getPhotonResolution(const HEPUtils::Particle* obj, double &pt_reso,double &phi_reso);

    void getJetResolution(const HEPUtils::Jet* obj, double &pt_reso,double &phi_reso);

  }
}
