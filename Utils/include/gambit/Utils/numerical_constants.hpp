//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Basic set of known mathematical and physical
///  constants for GAMBIT.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date   2015 Mar
///
///  \author Christoph Weniger
///          (c.weniger@uva.nl)
///  \date   2015 Apr
///  \date   2016 Mar
//
///  *********************************************

#ifndef __numerical_constants_hpp__
#define __numerical_constants_hpp__

#include <cmath>

namespace Gambit
{

  const double pi = 3.141592653589793238462643383279502884197;
  const double root2 = sqrt(2.0);
  const double hbar = 6.582119514e-25;                          // GeV s  (http://pdg.lbl.gov/2017/reviews/rpp2017-rev-phys-constants.pdf)
  const double K2eV = 8.6173303e-5;                             // eV per K
  const double eV2g = 1.782661907e-33;                          // eV per g
  const double gev2cm = 197.327053e-16;                         // cm per GeV^-1
  const double gev2cm2 = pow(197.327053e-16, 2.0);              // cm^2 per GeV^-2
  const double gev2pb = gev2cm2*1e36;                           // pb per GeV^-2
  const double gev2tocm3s1 = 1.16733e-17;                       // cm^3 s^-1 per GeV^-2
  const double s2cm = 2.99792458e10;                            // cm per s
  const double m_planck = 1.220910e19;                          // Planck mass (GeV)
  const double m_planck_red = m_planck/sqrt(8.0*pi);            // reduced Planck mass (GeV)
  const double atomic_mass_unit = 0.931494028;                    // atomic mass unit (GeV/c^2)
  const double m_proton_amu = 1.00727646688;                    // proton mass (amu)
  const double m_neutron_amu = 1.0086649156;                    // neutron mass (amu)
  const double m_proton = m_proton_amu * atomic_mass_unit;      // proton mass (GeV/c^2)
  const double m_neutron = m_neutron_amu * atomic_mass_unit;    // neutron mass (GeV/c^2)
  const double m_electron = 0.5109989461e-3;                    // electron mass (GeV/c^2)
  const double alpha_EM = 7.2973525664e-3;                      // fine structure constant
  const double T_CMB = 2.7255;                                  // present day CMB temperature (K)

  /**
     @brief Thomson limit of \f$\alpha_e\f$ in OS scheme from
     <a href="http://pdg.lbl.gov/2017/reviews/rpp2017-rev-phys-constants.pdf">PDG 2017</a>
  */
  constexpr double alpha_e_OS_thomson_limit = 0.0072973525664;
  /**
     @brief \f$\alpha_e(M_Z)\f$ in OS scheme from
     <a href="https://arxiv.org/pdf/1105.3149.pdf">1105.3149</a>
  */
  constexpr double alpha_e_OS_MZ = 1. / 128.944;
  /**
     @brief \f$\Delta\alpha\f$ in OS scheme.

     Defined by
     \f[
     \alpha(M_Z) = \frac{\alpha(0)}{1 - \Delta\alpha}
     \f]
  */
  constexpr double delta_alpha_OS = 1. - alpha_e_OS_thomson_limit / alpha_e_OS_MZ;

  static const struct Mesons_masses
  {
    static constexpr double pi0 = 0.135;          // neutral pion mass (GeV/c^2)
    static constexpr double pi_plus = 0.1396;     // charged pion mass (GeV/c^2)
    static constexpr double pi_minus = 0.1396;    // charged pion mass (GeV/c^2)
    static constexpr double eta = 0.547;          // eta mass (GeV/c^2)
    static constexpr double rho0 = 0.775;         // neutral rho meson mass (GeV/c^2)
    static constexpr double rho_plus = 0.775;     // charged rho meson mass (GeV/c^2)
    static constexpr double rho_minus = 0.775;    // charged rho meson mass (GeV/c^2)
    static constexpr double omega = 0.7827;       // omega meson mass (GeV/c^2)
    static constexpr double rho1450 = 1.465;      // rho(1450) mass (GeV/c^2)
  } meson_masses;

  static const struct Mesons_decay_constants
  {
    static constexpr double pi_plus = 0.13041;    // (GeV)
  } meson_decay_constants;


  /// M_W (Breit-Wigner mass parameter ~ pole) = 80.385 +/- 0.015  GeV (1 sigma), Gaussian.
  /// Reference http://pdg.lbl.gov/2014/listings/rpp2014-list-w-boson.pdf = K.A. Olive et al. (Particle Data Group), Chin. Phys. C38, 090001 (2014)
  /// @{
  const double mw_central_observed = 80.385;
  const double mw_err_observed = 0.015;
  /// @}

}

#endif //#defined __numerical_constants_hpp__
