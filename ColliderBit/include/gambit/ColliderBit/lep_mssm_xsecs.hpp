//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Sparticle production cross-section calculators for LEP.
///
///  Results are taken from
///  A. Bartl, H. Fraas, W. Majerotto, Z. Phys. C30 (1986) 441
///  A. Bartl, H. Fraas, W. Majerotto, Nucl. Phys. B278 (1986) 1
///  S. Dawson, E. Eichten and C. Quigg, Phys. Rev. D31 (1985) 1581
///  A. Bartl, H. Fraas, W. Majerotto, Z. Phys. C34 (1987) 411
///
///  The Bartl, Fraas and Majerotto (BFM) papers are based on a convention for
///  the neutralino decomposed into photino, zino and two higgsinos a and b:
///  \f$\tilde\chi_i^0 = N_{i1} \tilde\gamma + N_{i2} \tilde Z + N_{i3} \tilde H_a + N_{i4} \tilde H_b\f$
///  where \f$\tilde H_a = \tilde H_1^0 \sin\beta - \tilde H_2^0 \cos\beta\f$
///  and \f$\tilde H_b = \tilde H_1^0 \cos\beta + \tilde H_2^0 \sin\beta\f$
///
///  This corresponds to the conventions for N' in Haber & Kane (HK).
///  Haber & Kane in turn have similar conventions to Gunion & Haber which is used
///  in SLHA, however, \f$\tan\beta\f$ is upside down in HK.
///  A conversion routine SLHA2BFM_NN from SLHA to these conventions is included.
///
///  For the charginos a convention similar to HK is followed, which has almost
///  the same mixing matrices V and U as in SLHA, however, BFM uses \f$\sigma_3 V\f$
///  as the mixing matrix for negative charged states. HK refines this to be
///  dependent on the mass matrix determinant so as to always get positive masses.
///  For conversion from SLHA to BFM use SLHA2BFM_VV.
///
///  For sleptons the SLHA convention is followed. Thus \f$F_{11}=\cos\phi\f$, \f$F_{12}=\sin\phi\f$, etc.
///  For \f$\phi = 0\f$ we have \f$\tilde l_1 = \tilde l_L\f$ and \f$\tilde l_2 = \tilde l_R\f$.
///
///  *********************************************
///
///  Authors
///
///  \author Are Raklev
///          (ahye@fys.uio.no)
///  \date 2015 Jun
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Jul
///
///  *********************************************

#include <vector>


namespace Gambit
{

  namespace ColliderBit
  {

    typedef std::vector< std::vector<double> > MixMatrix;

    /// High-level cross section routines.
    /// @{
    /// Retrieve the production cross-section at an e+e- collider for slepton pairs.
    ///  If l_are_gauge_es = T, then l(bar)_chirality = 1 => (anti-)left-type  slepton
    ///                                               = 2 => (anti-)right-type slepton
    ///  If l_are_gauge_es = F, then l(bar)_chirality = 1 => (anti-)slepton is lightest family state
    ///                                               = 2 => (anti-)slepton is heaviest family state
    void get_sigma_ee_ll(triplet<double>& result, const double sqrts, const int generation, const int l_chirality,
                         const int lbar_chirality, const double gtol, const double ftol, const bool gpt_error,
                         const bool fpt_error, const Spectrum& spec, const double gammaZ, const bool l_are_gauge_es);
    /// Retrieve the production cross-section at an e+e- collider for neutralino pairs
    void get_sigma_ee_chi00(triplet<double>& result, const double sqrts, const int chi_first, const int chi_second,
                            const double tol, const bool pt_error, const Spectrum& spec, const double gammaZ);
    /// Retrieve the production cross-section at an e+e- collider for chargino pairs
    void get_sigma_ee_chipm(triplet<double>& result, const double sqrts, const int chi_plus, const int chi_minus,
                            const double tol, const bool pt_error, const Spectrum& spec, const double gammaZ);
    /// @}

    /// Low-level cross section routines.
    /// @{
    /// Cross section [pb] for \f$ e^+e^- -> \tilde l_i \tilde l_j^* \f$
    /// To use, call SLHA2BFM first on SLHA mixing matrices constructed as a vector of vectors
    double xsec_sleislej(int pid1, int pid2, double sqrts, double m1, double m2, MixMatrix F,
                         MixMatrix N, const double mN[4], double alpha, double mZ, double gZ,
                         double sin2thetaW, bool warn_on_CP_violating_masses = true);
    /// Cross section [pb] for \f$ e^+e^- -> \tilde\chi^0_i \tilde\chi^0_j \f$
    /// Masses mi and mj for the neutralinos are signed. mS are the selectron masses (left = 0, right = 1).
    /// Warning! BFM uses inverted \f$\tan\beta\f$! Use tanb = 1 / tanb in converting from SLHA.
    double xsec_neuineuj(int pid1, int pid2, double sqrts, double m1, double m2, MixMatrix N,
                         const double mS[2], double tanb, double alpha, double mZ, double gZ, double sin2thetaW);
    /// Cross section [pb] for \f$ e^+e^- -> \tilde\chi^+_i \tilde\chi^-_j \f$
    /// Masses mi and mj for the charginos are signed. msn is electron sneutrino mass.
    double xsec_chaichaj(int pid1, int pid2, double sqrts, double m1, double m2, MixMatrix V,
                         MixMatrix U, double msn, double alpha, double mZ, double gZ, double sin2thetaW);
    /// @}

    /// Conversion between SLHA and BFM conventions. \f$\tan\beta\f$ is as per SLHA.
    /// @{
    void SLHA2BFM_NN(MixMatrix &NN, double tanb, double sin2thetaW);
    void SLHA2BFM_VV(MixMatrix &VV);
    void BFM2SLHA_NN(MixMatrix &NN, double tanb, double sin2thetaW);
    void BFM2SLHA_VV(MixMatrix &VV);
    MixMatrix multiply(MixMatrix A, MixMatrix B);
    MixMatrix transpose(MixMatrix A);
    void print(MixMatrix A);
    /// @}

  }

}
