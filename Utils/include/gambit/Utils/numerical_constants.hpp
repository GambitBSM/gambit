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
///
///  \author Janina Renk
///          (janina.renk@fysik.su.se)
///  \date   2019 Mar
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2020 Jan
//
///  *********************************************

#ifndef __numerical_constants_hpp__
#define __numerical_constants_hpp__

#include <cmath>

namespace Gambit
{

  const double pi = 3.141592653589793238462643383279502884197;
  const double root2 = sqrt(2.0);
  const double zeta3 = 1.2020569031595942855;                   // Riemann zeta function of 3
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
  const double atomic_mass_unit = 0.931494028;                  // atomic mass unit (GeV/c^2)
  const double m_proton_amu = 1.00727646688;                    // proton mass (amu)
  const double m_neutron_amu = 1.0086649156;                    // neutron mass (amu)
  const double m_proton = m_proton_amu * atomic_mass_unit;      // proton mass (GeV/c^2)
  const double m_neutron = m_neutron_amu * atomic_mass_unit;    // neutron mass (GeV/c^2)
  const double m_electron = 0.5109989461e-3;                    // electron mass (GeV/c^2)
  const double alpha_EM = 7.2973525664e-3;                      // fine structure constant

  /// Values from Particle Data Group 2018 (http://pdg.lbl.gov/2018/reviews/rpp2018-rev-phys-constants.pdf)
  const double c_SI = s2cm/100;                                 // speed of light in m/s
  const double eV_to_J = 1.6021766208e-19;                      // electron charge in C
  const double Mpc_SI = 969394202136*pow(10,11)/pi;             // Mpc in m

  const double GN_cgs = 6.67408e-8;                             // Newton's constant in cm^3.g^-1.s^-2
  const double GN_SI = GN_cgs/1e3;                              // Newton's constant in m^3.kg^-1.s^-2

  const double kB_SI = 1.38064852e-23;                          // Boltzmann constant in  Kg/K^4/s^3
  const double kB_eV_over_K = kB_SI/eV_to_J;                    // Boltzmann constant in eV/K

  const double hP_SI = 6.626070040e-34;                         // Planck const. in Js
  const double hP_eVs = hP_SI/eV_to_J;                          // Planck const. in eVs
  const double hc_eVcm =hP_eVs*s2cm;                            // Planck const. x speed of light in eV cm

  const double sigmaB_SI = 2*pow(pi,5)*pow(kB_SI,4)/(15*pow(hP_SI,3)*c_SI*c_SI); // Stefan-Boltzman constant in W/m^2/K^4 = Kg/K^4/s^3

  const double Neff_SM = 3.045;                                 // effective number of relativistic dof in the early Universe
  // the value of 3.045 holds for 3 SM neutrinos in the absence of any non-standard particles
  // or components. Value from de Salas, Pastor '16, arXiv:1606.06986

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
    static constexpr double kaon_plus = 0.4937;   // charged kaon meson mass (GeV/c^2)
    static constexpr double kaon_minus = 0.4937;  // charged kaon meson mass (GeV/c^2)
    static constexpr double kaon0 = 0.4976;       // neutral kaon meson mass (GeV/c^2)
    static constexpr double rho1450 = 1.465;      // rho(1450) mass (GeV/c^2)
    static constexpr double D_plus = 1.86962;     // charged D meson mass (GeV/c^2)
    static constexpr double D_s = 1.96847;        // D_s meson mass (GeV/c^2)
    static constexpr double B_plus = 5.27929;     // charged B meson mass (GeV/c^2)
    static constexpr double B_s = 5.36679;        // B_s meson mass (GeV/c^2)
    static constexpr double B_c = 6.2751;         // B_c meson mass (GeV/c^2)
    static constexpr double eta_prime = 0.95778;  // eta prime meson mass (GeV/c^2)
    static constexpr double eta_c = 2.9839;       // eta_c meson mass (GeV/c^2)
    static constexpr double Dstar_plus = 2.01026; // charged D* meson mass (GeV/c^2)
    static constexpr double Dstar_s = 2.1122;     // D*_s meson mass (GeV/c^2)
    static constexpr double phi = 1.019461;       // phi meson mass (GeV/c^2)
    static constexpr double Jpsi = 3.0969;        // Jpsi meson mass (GeV/c^2)
  } meson_masses;

  static const struct Mesons_decay_constants
  {
    // PDG 2018
    static constexpr double pi_plus = 0.1302;    // (GeV)
    static constexpr double pi0 = 0.1302;        // (GeV)
    static constexpr double K_plus = 0.1557;     // (GeV)
    static constexpr double D_plus = 0.2126;     // (GeV)
    static constexpr double D_s = 0.2499;        // (GeV)
    static constexpr double B_plus = 0.190;      // (GeV)

    // From 1503.05762
    static constexpr double B_c = 0.434;         // (GeV)

    // From 1805.08567
    static constexpr double eta = 0.0817;        // (GeV)
    static constexpr double eta_prime = -0.0947; // (GeV)
    static constexpr double eta_c = 0.237;       // (GeV)

    // From 0602110, using tau decays for rho
    static constexpr double rho_plus = 0.209;    // (GeV)
    static constexpr double rho0 = 0.209;        // (GeV)
    static constexpr double phi = 0.229;         // (GeV)

    // From 1708.07274, average of theoretical computations
    static constexpr double Dstar_plus = 0.24675;// (GeV)
    static constexpr double Dstar_s = 0.284;     // (GeV)

    // From 0901.3589, thought not sure where they got it from
    static constexpr double omega = 0.195;       // (GeV)

    // From 1312.2858
    static constexpr double Jpsi = 0.418;        // (GeV)

  } meson_decay_constants;


  /// M_W (Breit-Wigner mass parameter ~ pole) = 80.385 +/- 0.015  GeV (1 sigma), Gaussian.
  /// Reference http://pdg.lbl.gov/2014/listings/rpp2014-list-w-boson.pdf = K.A. Olive et al. (Particle Data Group), Chin. Phys. C38, 090001 (2014)
  /// @{
  const double mw_central_observed = 80.385;
  const double mw_err_observed = 0.015;
  /// @}

}

#endif //#defined __numerical_constants_hpp__
