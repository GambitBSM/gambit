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
  }


}
#endif //defined __spectrum_types_hpp__
