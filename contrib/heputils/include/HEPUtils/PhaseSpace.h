// -*- C++ -*-
//
// This file is part of HEPUtils -- https://gitlab.com/hepcedar/heputils/
// Copyright (C) 2013-2022 Andy Buckley <andy.buckley@cern.ch>
//
// Embedding of HEPUtils code in other projects is permitted provided this
// notice is retained and the HEPUtils namespace and include path are changed.
//
#pragma once

#if __cplusplus <= 199711L
#error "This library needs at least a C++11 compliant compiler: are you using -std=c++11?"
#endif

#include "HEPUtils/MathUtils.h"

/// @file Phase space distributions in DeltaR
/// @author Andy Buckley <andy.buckley@cern.ch>

namespace HEPUtils {


  /// @defgroup phasespace Phase-space helpers
  /// @{


  /// Integral of acos(x)
  constexpr double iacos(double x) { return x*acos(x) - sqrt(1 - x*x); }

  /// Inverse secant
  constexpr double asec(double x) { return acos(1/x); }


  /// Maximum dR possible in a detector with total eta acceptance @a detamax
  constexpr double dr_max(double detamax) {
    return sqrt(sqr(detamax) + sqr(M_PI));
  }

  /// Compute eta-integrated DeltaR phase space Phi(dr, detamax)
  constexpr double dr_phase_space_Phi(double dr, double detamax) {
    if (dr == 0 || detamax == 0 || sqr(dr) > sqr(detamax) + sqr(M_PI))
      return 0.0;

    // Compute intuitive form via theta_max
    const double theta_max = dr < M_PI ? M_PI / 2.0 : asin(M_PI/dr);
    const double cos_theta_max = cos(theta_max);
    double L = (detamax - dr*cos_theta_max)*theta_max - dr*iacos(cos_theta_max);
    if (dr > detamax) L += dr*iacos(detamax/dr);
    return dr * L;

    // Compute via expanded form
    // const M_PI2 = sqr(M_PI);
    // const double dr2 = sqr(dr);
    // const double detamax2 = sqr(detamax);
    // double L = 0;
    // if (dr < M_PI) {
    //   L += M_PI*detamax/2. - dr;
    // } else {
    //   const double dr2_minus_pi2 = dr2 - M_PI2;
    //   L += (detamax - sqrt(dr2_minus_pi2))*asin(M_PI/dr) + M_PI + sqrt(dr2_minus_pi2)*asec(dr/sqrt(dr2_minus_pi2));
    // }
    // if (dr > detamax)
    //   L += sqrt(dr2 - detamax2) - detamax*acos(detamax/dr);
    // return dr * L;
  }


  /// Compute the integral IPhi(detamax) = \int Phi(dr, detamax) ddr.
  constexpr double dr_phase_space_IPhi(double detamax) {
    if (detamax == 0)
      return 0.0;
    const double M_PI2 = sqr(M_PI);
    const double M_PI3 = M_PI * M_PI2;
    const double detamax2 = sqr(detamax);
    const double psPhiIntegral = ((6 - detamax)*detamax*M_PI - 3*M_PI3 +
                                  2*(detamax2 + 3*M_PI2)*(asin(detamax/sqrt(detamax2 + M_PI2)) +
                                                          asin(M_PI/sqrt(detamax2 + M_PI2)))) * detamax/12.;
    return psPhiIntegral;
  }

  /// @}


}
