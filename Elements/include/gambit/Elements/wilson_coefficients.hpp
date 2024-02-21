//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Wilson coefficient container type
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2024 Feb
///
///  *********************************************

#pragma once

namespace Gambit
{

  // Wilson coefficient struct contains complex WC values for each generation
  struct WilsonCoefficient
  {
    std::complex<double> e=0.;
    std::complex<double> mu=0.;
    std::complex<double> tau=0.;

    // Empty constructor
    WilsonCoefficient()
    {}

    // Constructor with only one flavour
    WilsonCoefficient(std::complex<double> wc)
    : e(wc)
    , mu(wc)
    , tau(wc)
    {}
    // Constructor with all three flavours
    WilsonCoefficient(std::complex<double> wc_e, std::complex<double> wc_mu, std::complex<double> wc_tau)
    : e(wc_e)
    , mu(wc_mu)
    , tau(wc_tau)
    {}
  };

  /// Stream overload
  inline std::ostream& operator << (std::ostream &os, const WilsonCoefficient &WC)
  {
    os << " e: " << WC.e << std::endl;
    os << " mu: " << WC.mu << std::endl;
    os << " tau: " << WC.tau << std::endl;

    return os;
  }

  typedef std::map<str, WilsonCoefficient> WilsonCoefficients;

}
