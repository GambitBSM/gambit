//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Spectrum specific types.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2022 Oct
///
///  *********************************************

#ifndef __spectrum_types_hpp__
#define __spectrum_types_hpp__

#include <vector>
#include <string>

namespace Gambit
{

  enum THDM_TYPE : int
  {
     TYPE_I = 1,
     TYPE_II,
     TYPE_LS,
     TYPE_flipped,
     TYPE_III
  };

  namespace thdm
  {
    // identifies all particles in the THDM (needed to prevent excessive string comparisons)
    enum Particle{u1,u2,u3,d1,d2,d3,e1,e2,e3,v1,v2,v3, u1c,u2c,u3c,d1c,d2c,d3c,e1c,e2c,e3c,v1c,v2c,v3c, a,z,wp,wm,g, h1,h2,ha,hp,hm}; 

    // name for each particle in the THDM
    const std::vector<std::string> particle_name = {"u_1","u_2","u_3","d_1","d_2","d_3","e-_1","e-_2","e-_3","nu_1","nu_2","nu_3", 
      "ubar_1","ubar_2","ubar_3","dbar_1","dbar_2","dbar_3","e+_1","e+_2","e+_3","nubar_1","nubar_2","nubar_3", 
      "gamma","Z0","W+","W-","g", "h0_1","h0_2","A0","H+","H-"};
  }
}

#endif //defined __spectrum_types_hpp__
