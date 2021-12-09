//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Sparticle production cross-section calculators
///  for LEP.
///
///  Usage details are in the corresponding header
///  file.
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


#include <iostream>
#include <fstream>
#include <math.h>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/ColliderBit/lep_mssm_xsecs.hpp"


#define pow2(a) ((a)*(a)) // Get speedy

namespace Gambit
{

  namespace ColliderBit
  {

    /// Retrieve the production cross-section at an e+e- collider for slepton pairs.
    ///  If l_are_gauge_es = T, then l(bar)_chirality = 1 => (anti-)left-type  slepton
    ///                                               = 2 => (anti-)right-type slepton
    ///  If l_are_gauge_es = F, then l(bar)_chirality = 1 => (anti-)slepton is lightest family state
    ///                                               = 2 => (anti-)slepton is heaviest family state
    void get_sigma_ee_ll(triplet<double>& result, const double sqrts, const int generation, const int l_chirality,
                         const int lbar_chirality, const double gtol, const double ftol, const bool gpt_error,
                         const bool fpt_error, const Spectrum& spec, const double gammaZ, const bool l_are_gauge_es)
    {
      static const str genmap[3][2] =
      {
        {"~e_L",   "~e_R"  },
        {"~mu_L",  "~mu_R" },
        {"~tau_L", "~tau_R"}
      };

      // PDG codes
      const int id1 = 1000000*l_chirality + 11 +2*(generation-1);
      const int id2 = -(1000000*lbar_chirality + 11 +2*(generation-1));

      // SM parameters
      const double mZ = spec.safeget(Par::Pole_Mass,23,0);
      const double g2 = spec.safeget(Par::dimensionless,"g2");
      const double sinW2 = spec.safeget(Par::dimensionless,"sinW2");
      const double alpha = 0.25*sinW2*g2*g2/pi;
      // MSSM parameters
      const double tanb = spec.safeget(Par::dimensionless,"tanbeta");

      // Get the mass eigenstate strings and 2x2 slepton generation mass mixing matrix
      str mass_es1, mass_es2;
      MixMatrix sleptonmix(2,std::vector<double>(2));

      if (l_are_gauge_es)
      {
        // Requested final states are gauge eigenstates.  Pass diagonal mixing matrix to low-level routine.
        sleptonmix[0][0] = 1.0;
        sleptonmix[0][1] = 0.0;
        sleptonmix[1][0] = 0.0;
        sleptonmix[1][1] = 1.0;
        mass_es1 = slhahelp::mass_es_from_gauge_es(genmap[generation-1][l_chirality-1],    spec, gtol, LOCAL_INFO, gpt_error);
        mass_es2 = slhahelp::mass_es_from_gauge_es(genmap[generation-1][lbar_chirality-1], spec, gtol, LOCAL_INFO, gpt_error);
      }
      else
      {
        // Requested final states are family mass eigenstates.  Pass 2x2 family mass mixing matrix to low-level routine.
        str m_light, m_heavy;
        std::vector<double> slepton4vec = slhahelp::family_state_mix_matrix("~e-", generation, m_light, m_heavy, spec, ftol, LOCAL_INFO, fpt_error);
        mass_es1 = (l_chirality    == 1) ? m_light : m_heavy;
        mass_es2 = (lbar_chirality == 1) ? m_light : m_heavy;
        sleptonmix[0][0] = slepton4vec[0];
        sleptonmix[0][1] = slepton4vec[1];
        sleptonmix[1][0] = slepton4vec[2];
        sleptonmix[1][1] = slepton4vec[3];
      }
      const double m1 = spec.safeget(Par::Pole_Mass,mass_es1);
      // FIXME when spectrum object has separate pole mass getters for antiparticles
      //const double m2 = spec.safeget(Par::Pole_Mass,Models::ParticleDB().get_antiparticle(mass_es2));
      // until then
      const double m2 = spec.safeget(Par::Pole_Mass,mass_es2);
      std::pair<double,double> m1_uncerts(spec.safeget(Par::Pole_Mass_1srd_high, mass_es1),
                                          spec.safeget(Par::Pole_Mass_1srd_low,  mass_es1));
      std::pair<double,double> m2_uncerts(spec.safeget(Par::Pole_Mass_1srd_high, mass_es2),
                                          spec.safeget(Par::Pole_Mass_1srd_low,  mass_es2));

      // If the final state is kinematically inaccessible *even* if both masses
      // are 2simga lower than their central values, then return zero.
      if (m1*(1.0-2.0*m1_uncerts.second) + m2*(1.0-2.0*m2_uncerts.second) > sqrts)
      {
        result.central = 0.0;
        result.upper = 0.0;
        result.lower = 0.0;
        return;
      }

      // Get the neutralino masses
      const double neutmass[4] = { spec.safeget(Par::Pole_Mass,1000022,0), spec.safeget(Par::Pole_Mass,1000023,0),
                                   spec.safeget(Par::Pole_Mass,1000025,0), spec.safeget(Par::Pole_Mass,1000035,0) };
      // Get the 4x4 neutralino mixing matrix
      MixMatrix neutmix(4,std::vector<double>(4));
      for (int i=0; i<4; i++) for (int j=0; j<4; j++) neutmix[i][j] = spec.safeget(Par::Pole_Mixing,"~chi0",i+1,j+1);

      // Convert neutralino mixing matrix to BFM convention
      SLHA2BFM_NN(neutmix, tanb, sinW2);

      // Calculate the cross-section
      result.central = xsec_sleislej(id1, id2, sqrts, m1, m2, sleptonmix, neutmix, neutmass, alpha, mZ, gammaZ, sinW2);

      // Calculate the uncertainty on the cross-section due to final state masses varying by +/- 1 sigma
      std::vector<double> xsecs;
      xsecs.push_back(result.central);
      xsecs.push_back(xsec_sleislej(id1, id2, sqrts, m1*(1.+m1_uncerts.first), m2*(1.+m2_uncerts.first), sleptonmix, neutmix,
                                   neutmass, alpha, mZ, gammaZ, sinW2, false));
      xsecs.push_back(xsec_sleislej(id1, id2, sqrts, m1*(1.-m1_uncerts.second), m2*(1.+m2_uncerts.first), sleptonmix, neutmix,
                                   neutmass, alpha, mZ, gammaZ, sinW2, false));
      xsecs.push_back(xsec_sleislej(id1, id2, sqrts, m1*(1.+m1_uncerts.first), m2*(1.-m2_uncerts.second), sleptonmix, neutmix,
                                   neutmass, alpha, mZ, gammaZ, sinW2, false));
      xsecs.push_back(xsec_sleislej(id1, id2, sqrts, m1*(1.-m1_uncerts.second), m2*(1.-m2_uncerts.second), sleptonmix, neutmix,
                                   neutmass, alpha, mZ, gammaZ, sinW2, false));
      result.upper = *std::max_element(xsecs.begin(), xsecs.end());
      result.lower = *std::min_element(xsecs.begin(), xsecs.end());

    }


    /// Retrieve the production cross-section at an e+e- collider for neutralino pairs
    void get_sigma_ee_chi00(triplet<double>& result, const double sqrts, const int chi_first, const int chi_second,
                            const double tol, const bool pt_error, const Spectrum& spec, const double gammaZ)
    {

      // PDG codes
      const int id1 = 1000021 + chi_first  + (chi_first  > 2 ? 1 + (chi_first -3)*9 : 0);
      const int id2 = 1000021 + chi_second + (chi_second > 2 ? 1 + (chi_second-3)*9 : 0);

      // SM parameters
      const double mZ = spec.safeget(Par::Pole_Mass,23,0);
      const double g2 = spec.safeget(Par::dimensionless,"g2");
      const double sinW2 = spec.safeget(Par::dimensionless,"sinW2");
      const double alpha = 0.25*sinW2*g2*g2/pi;

      // MSSM parameters
      const double tanb = spec.safeget(Par::dimensionless,"tanbeta");
      // Get the mass eigenstates best corresponding to ~eL and ~eR.
      const str mass_esL = slhahelp::mass_es_from_gauge_es("~e_L", spec, tol, LOCAL_INFO, pt_error);
      const str mass_esR = slhahelp::mass_es_from_gauge_es("~e_R", spec, tol, LOCAL_INFO, pt_error);
      // Get the slepton masses
      const double mS[2] = {spec.safeget(Par::Pole_Mass,mass_esL), spec.safeget(Par::Pole_Mass,mass_esR)};
      // Get the neutralino masses
      const double m1 = spec.safeget(Par::Pole_Mass,id1,0);
      const double m2 = spec.safeget(Par::Pole_Mass,id2,0);
      std::pair<double,double> m1_uncerts(spec.safeget(Par::Pole_Mass_1srd_high, id1, 0),
                                          spec.safeget(Par::Pole_Mass_1srd_low,  id1, 0));
      std::pair<double,double> m2_uncerts(spec.safeget(Par::Pole_Mass_1srd_high, id2, 0),
                                          spec.safeget(Par::Pole_Mass_1srd_low,  id2, 0));

      // Just return zero if the final state is kinematically inaccessible
      // *even* if both masses are 2simga lower than their central values
      if (std::abs(m1)*(1.0-2.0*m1_uncerts.second) + std::abs(m2)*(1.0-2.0*m2_uncerts.second) > sqrts)
      {
        result.central = 0.0;
        result.upper = 0.0;
        result.lower = 0.0;
        return;
      }

      // Get the 4x4 neutralino mixing matrix
      MixMatrix neutmix(4,std::vector<double>(4));
      for (int i=0; i<4; i++) for (int j=0; j<4; j++) neutmix[i][j] = spec.safeget(Par::Pole_Mixing,"~chi0",i+1,j+1);

      // Convert neutralino mixing matrix to BFM convention
      SLHA2BFM_NN(neutmix, tanb, sinW2);

      // Calculate the cross-section
      result.central = xsec_neuineuj(id1, id2, sqrts, m1, m2, neutmix, mS, 1./tanb, alpha, mZ, gammaZ, sinW2);

      // Calculate the uncertainty on the cross-section due to final state masses varying by +/- 1 sigma
      std::vector<double> xsecs;
      xsecs.push_back(result.central);
      xsecs.push_back(xsec_neuineuj(id1, id2, sqrts, m1*(1.+m1_uncerts.first), m2*(1.+m2_uncerts.first),
                                    neutmix, mS, 1./tanb, alpha, mZ, gammaZ, sinW2));
      xsecs.push_back(xsec_neuineuj(id1, id2, sqrts, m1*(1.+m1_uncerts.first), m2*(1.-m2_uncerts.second),
                                    neutmix, mS, 1./tanb, alpha, mZ, gammaZ, sinW2));
      xsecs.push_back(xsec_neuineuj(id1, id2, sqrts, m1*(1.-m1_uncerts.second), m2*(1.+m2_uncerts.first),
                                    neutmix, mS, 1./tanb, alpha, mZ, gammaZ, sinW2));
      xsecs.push_back(xsec_neuineuj(id1, id2, sqrts, m1*(1.-m1_uncerts.second), m2*(1.-m2_uncerts.second),
                                    neutmix, mS, 1./tanb, alpha, mZ, gammaZ, sinW2));
      result.upper = *std::max_element(xsecs.begin(), xsecs.end());
      result.lower = *std::min_element(xsecs.begin(), xsecs.end());

    }

    /// Retrieve the production cross-section at an e+e- collider for chargino pairs
    void get_sigma_ee_chipm(triplet<double>& result, const double sqrts, const int chi_plus, const int chi_minus,
                            const double tol, const bool pt_error, const Spectrum& spec, const double gammaZ)
    {

      // PDG codes
      const int id1 = 1000023 + chi_plus + (chi_plus - 1)*12;
      const int id2 = -(1000023 + chi_minus + (chi_minus - 1)*12);

      // SM parameters
      const double mZ = spec.safeget(Par::Pole_Mass,23,0);
      const double g2 = spec.safeget(Par::dimensionless,"g2");
      const double sinW2 = spec.safeget(Par::dimensionless,"sinW2");
      const double alpha = 0.25*sinW2*g2*g2/pi;

      // MSSM parameters
      // Get the mass eigenstate best corresponding to ~nu_e_L.
      const str mass_snue = slhahelp::mass_es_from_gauge_es("~nu_e_L", spec, tol, LOCAL_INFO, pt_error);
      // Get the electron sneutrino mass
      const double msn = spec.safeget(Par::Pole_Mass,mass_snue);
      // Get the chargino masses
      const double m1 = spec.safeget(Par::Pole_Mass,id1,0);
      const double m2 = spec.safeget(Par::Pole_Mass,id2,0);
      std::pair<double,double> m1_uncerts(spec.safeget(Par::Pole_Mass_1srd_high, id1, 0),
                                          spec.safeget(Par::Pole_Mass_1srd_low,  id1, 0));
      std::pair<double,double> m2_uncerts(spec.safeget(Par::Pole_Mass_1srd_high, id2, 0),
                                          spec.safeget(Par::Pole_Mass_1srd_low,  id2, 0));

      // Just return zero if the final state is kinematically inaccessible
      // *even* if both masses are 2simga lower than their central values
      if (std::abs(m1)*(1.0-2.0*m1_uncerts.second) + std::abs(m2)*(1.0-2.0*m2_uncerts.second) > sqrts)
      {
        result.central = 0.0;
        result.upper = 0.0;
        result.lower = 0.0;
        return;
      }

      // Get the 2x2 chargino mixing matrices
      MixMatrix charginomixV(2,std::vector<double>(2));
      MixMatrix charginomixU(2,std::vector<double>(2));
      for (int i=0; i<2; i++) for (int j=0; j<2; j++)
      {
        charginomixV[i][j] = spec.safeget(Par::Pole_Mixing,"~chi+",i+1,j+1);
        charginomixU[i][j] = spec.safeget(Par::Pole_Mixing,"~chi-",i+1,j+1);
      }

      // Convert chargino mixing matrices to BFM convention
      SLHA2BFM_VV(charginomixV);
      SLHA2BFM_VV(charginomixU);

      // Calculate the cross-section
      result.central = xsec_chaichaj(id1, id2, sqrts, m1, m2, charginomixV, charginomixU,
                                     msn, alpha, mZ, gammaZ, sinW2);

      // Calculate the uncertainty on the cross-section due to final state masses varying by +/- 1 sigma
      std::vector<double> xsecs;
      xsecs.push_back(result.central);
      xsecs.push_back(xsec_chaichaj(id1, id2, sqrts, m1*(1.+m1_uncerts.first), m2*(1.+m2_uncerts.first), charginomixV, charginomixU,
                                     msn, alpha, mZ, gammaZ, sinW2));
      xsecs.push_back(xsec_chaichaj(id1, id2, sqrts, m1*(1.+m1_uncerts.first), m2*(1.-m2_uncerts.second), charginomixV, charginomixU,
                                     msn, alpha, mZ, gammaZ, sinW2));
      xsecs.push_back(xsec_chaichaj(id1, id2, sqrts, m1*(1.-m1_uncerts.second), m2*(1.+m2_uncerts.first), charginomixV, charginomixU,
                                     msn, alpha, mZ, gammaZ, sinW2));
      xsecs.push_back(xsec_chaichaj(id1, id2, sqrts, m1*(1.-m1_uncerts.second), m2*(1.-m2_uncerts.second), charginomixV, charginomixU,
                                     msn, alpha, mZ, gammaZ, sinW2));
      result.upper = *std::max_element(xsecs.begin(), xsecs.end());
      result.lower = *std::min_element(xsecs.begin(), xsecs.end());

    }

    /// Integrals for t-channel neutralino diagrams
    /// m1 and m2 are masses of final state sleptons
    /// mk and ml are neutralino masses
    /// @{
    double I1(double s, double m1, double m2, double mk, double ml)
    {
      double S = sqrt(s-pow2(m1+m2))*sqrt(s-pow2(m1-m2));
      double m1sq = pow2(m1);
      double m2sq = pow2(m2);
      double mksq = pow2(mk);
      double mlsq = pow2(ml);

      double I1 = 0;
      // Careful with degenerate masses!
      if( fabs(mksq-mlsq) < 0.1 ){
        I1 = (m1sq+m2sq-2.*mksq-s)*log((m1sq+m2sq-2.*mksq-s+S)/(m1sq+m2sq-2.*mksq-s-S))-4*S*((m1sq-mksq)*(m2sq-mksq)+mksq*s)/(m1sq+m2sq-2.*mksq-s-S)/(m1sq+m2sq-2.*mksq-s+S)-S;
      }
      else{
        I1 = (m1sq*(m2sq-mksq)+mksq*(mksq-m2sq+s))/(mksq-mlsq)*log((m1sq+m2sq-2.*mksq-s-S)/(m1sq+m2sq-2.*mksq-s+S));
        I1 += (m1sq*(m2sq-mlsq)+mlsq*(mlsq-m2sq+s))/(mlsq-mksq)*log((m1sq+m2sq-2.*mlsq-s-S)/(m1sq+m2sq-2.*mlsq-s+S));
        I1 -= S;
      }
      return I1;
    }
    double I2(double s, double m1, double m2, double mk, double ml)
    {
      double S = sqrt(s-pow2(m1+m2))*sqrt(s-pow2(m1-m2));
      double m1sq = pow2(m1);
      double m2sq = pow2(m2);
      double mksq = pow2(mk);
      double mlsq = pow2(ml);

      double I2 = 0;
      // Careful with degenerate masses!
      if( fabs(mksq-mlsq) < 0.1 )
      {
        I2 = S/(m1sq*(m2sq-mksq)+mksq*(-m2sq+mksq+s));
      }
      else
      {
        I2 = log((m1sq+m2sq-2.*mksq-(s-S))/(m1sq+m2sq-2.*mksq-(s+S)));
        I2 += log((m1sq+m2sq-2.*mlsq-(s+S))/(m1sq+m2sq-2.*mlsq-(s-S)));
        I2 *= 1./(mksq-mlsq);
      }
      return I2;
    }
    double I3(double s, double m1, double m2, double mk)
    {
      double S = sqrt(s-pow2(m1+m2))*sqrt(s-pow2(m1-m2));
      double m1sq = pow2(m1);
      double m2sq = pow2(m2);
      double mksq = pow2(mk);

      double I3 = 0;
      I3 = log((m1sq+m2sq-2.*mksq-(s+S))/(m1sq+m2sq-2.*mksq-(s-S)));
      I3 *= m1sq*(m2sq-mksq)+mksq*(-m2sq+mksq+s);
      I3 += (m1sq+m2sq-2.*mksq-s)*S/2.;
      return I3;
    }
    /// @}


    /// Cross section [pb] for \f$e^+e^- -> \tilde l_i \tilde l_j^*\f$
    /// To use, call SLHA2BFM first on SLHA mixing matrices constructed as a vector of vectors
    double xsec_sleislej(int pid1, int pid2, double sqrts, double m1, double m2, MixMatrix F,
                         MixMatrix N, const double mN[4], double alpha, double mZ, double gZ,
                         double sin2thetaW, bool CP_lock)
    {

      // Just return zero if the final state isn't kinematically accessible
      if (m1+m2 > sqrts) return 0.0;

      // Slepton mixing
      double cosphi = F[0][0];
      double sinphi = F[0][1];

      // Figure out what we are calculating
      double tempphi;
      bool bMixed = false;
      bool bSelectron = false;
      // ~e_L ~e_L^*
      if((pid1 == 1000011 && pid2 == -1000011) || (pid1 == -1000011 && pid2 == 1000011)){
        bSelectron = true;
        if(m1 != m2 and CP_lock) ColliderBit_warning().raise(LOCAL_INFO, "You are using a different mass for antiparticle!");
      }
      // ~e_L ~e_R^*
      else if((pid1 == 1000011 && pid2 == -2000011) || (pid1 == -2000011 && pid2 == 1000011)){
        bSelectron = true;
        bMixed = true;
      }
      // ~e_R ~e_L^*
      else if((pid1 == 2000011 && pid2 == -1000011) || (pid1 == -1000011 && pid2 == 2000011)){
        bSelectron = true;
        bMixed = true;
      }
      // ~e_R ~e_R^*
      else if((pid1 == 2000011 && pid2 == -2000011) || (pid1 == -2000011 && pid2 == 2000011)){
        bSelectron = true;
        tempphi = cosphi; cosphi = sinphi; sinphi = tempphi;
        if(m1 != m2 and CP_lock) ColliderBit_warning().raise(LOCAL_INFO, "You are using a different mass for antiparticle!");
      }
      // ~mu_L ~mu_L^*
      else if((pid1 == 1000013 && pid2 == -1000013) || (pid1 == -1000013 && pid2 == 1000013)){
        if(m1 != m2 and CP_lock) ColliderBit_warning().raise(LOCAL_INFO, "You are using a different mass for antiparticle!");
      }
      // ~mu_L ~mu_R^*
      else if((pid1 == 1000013 && pid2 == -2000013) || (pid1 == -2000013 && pid2 == 1000013)){
        bMixed = true;
        ColliderBit_warning().raise(LOCAL_INFO, "Will give zero cross section unless there is left-right smuon mixing!");
      }
      // ~mu_R ~mu_L^*
      else if((pid1 == 2000013 && pid2 == -1000013) || (pid1 == -1000013 && pid2 == 2000013)){
        bMixed = true;
        ColliderBit_warning().raise(LOCAL_INFO, "Will give zero cross section unless there is left-right smuon mixing!");
      }
      // ~mu_R ~mu_R^*
      else if((pid1 == 2000013 && pid2 == -2000013) || (pid1 == -2000013 && pid2 == 2000013)){
        tempphi = cosphi; cosphi = sinphi; sinphi = tempphi;
        if(m1 != m2 and CP_lock) ColliderBit_warning().raise(LOCAL_INFO, "You are using a different mass for antiparticle!");
      }
      // ~tau_1 ~tau_1^*
      else if((pid1 == 1000015 && pid2 == -1000015) || (pid1 == -1000015 && pid2 == 1000015)){
        if(m1 != m2 and CP_lock) ColliderBit_warning().raise(LOCAL_INFO, "You are using a different mass for antiparticle!");
      }
      // ~tau_1 ~tau_2^*
      else if((pid1 == 1000015 && pid2 == -2000015) || (pid1 == -2000015 && pid2 == 1000015)){
        bMixed = true;
      }
      // ~tau_2 ~tau_1^*
      else if((pid1 == 2000015 && pid2 == -1000015) || (pid1 == -1000015 && pid2 == 2000015)){
        bMixed = true;
      }
      // ~tau_2 ~tau_2^*
      else if((pid1 == 2000015 && pid2 == -2000015) || (pid1 == -2000015 && pid2 == 2000015)){
        tempphi = cosphi; cosphi = sinphi; sinphi = tempphi;
        if(m1 != m2 and CP_lock) ColliderBit_warning().raise(LOCAL_INFO, "You are using a different mass for antiparticle!");
      }
      else
      {
        std::stringstream ss;
        ss << "I don't know that process!" << endl
           << "You asked me to calculate slepton cross section with final states"
           << "PID1 " << pid1 << " PID2 " << pid2;
        ColliderBit_warning().raise(LOCAL_INFO, ss.str());
        return -1;
      }

      // Couplings
      double T3l = -0.5;
      double Le = T3l+sin2thetaW;
      double Re = sin2thetaW;
      // Left-right mixing
      double cos2phi = pow2(cosphi);
      double sin2phi = pow2(sinphi);

      double fL[4], fR[4];
      for(int k = 0; k < 4; k++){
        fL[k] = -sqrt(2.) * (1./sqrt(1.-sin2thetaW)*(T3l+sin2thetaW)*N[k][1]-sqrt(sin2thetaW)*N[k][0]);
        fR[k] = sqrt(2.) * sqrt(sin2thetaW) * (sqrt(sin2thetaW/(1.-sin2thetaW))*N[k][1]-N[k][0]);
      }

      // Kinematics
      double s, S, DZ2, ReDZ;
      s = pow2(sqrts);
      S = sqrt(s-pow2(m1+m2))*sqrt(s-pow2(m1-m2));
      DZ2 = 1./(pow2(s-pow2(mZ))+pow2(mZ*gZ)); // Breit-Wigner for Z
      ReDZ = (s-pow2(mZ))*DZ2;

      // Cross sections per diagram and interference terms
      double sigma, sigma_Z, sigma_Z_mix, sigma_g, sigma_gZ, sigma_N, sigma_N_mix, sigma_gN, sigma_ZN, sigma_ZN_mix;
      // gamma
      sigma_g = 2.*pi*pow2(alpha)/pow(s,4) * pow(S,3)/6.;
      // Z
      sigma_Z = pi*pow2(alpha)/pow2(s)/pow2(sin2thetaW)/pow2(1.-sin2thetaW) *  DZ2 * pow(S,3)/6.;
      sigma_Z *= (pow2(Le)+pow2(Re))*pow2(Le*cos2phi+Re*sin2phi);
      sigma_Z_mix = sigma_Z/pow2(Le*cos2phi+Re*sin2phi)*pow2(Le-Re)*cos2phi*sin2phi;
      // Interference
      sigma_gZ = 2*pi*pow2(alpha)/pow(s,3)/sin2thetaW/(1.-sin2thetaW) * ReDZ;
      sigma_gZ *= (Le+Re)*(Le*cos2phi+Re*sin2phi) * pow(S,3)/6.;
      // Neutralino
      // Loop over neutralinos
      sigma_N = 0;
      for(int k = 0; k < 4; k++){
        for(int l = 0; l < 4; l++){
          sigma_N += pow2(cos2phi)*I1(s,m1,m2,mN[k],mN[l])*pow2(fL[k]*fL[l]);
          sigma_N += pow2(sin2phi)*I1(s,m1,m2,mN[k],mN[l])*pow2(fR[k]*fR[l]);
          sigma_N += 2.*cos2phi*sin2phi*s*mN[k]*mN[l]*I2(s,m1,m2,mN[k],mN[l])*fL[k]*fL[l]*fR[k]*fR[l];
        }
      }
      sigma_N *= pi*pow2(alpha)/4./pow2(sin2thetaW)/pow2(s);
      sigma_N_mix = 0;
      for(int k = 0; k < 4; k++)
      {
        for(int l = 0; l < 4; l++)
        {
          sigma_N_mix += cos2phi*sin2phi*I1(s,m1,m2,mN[k],mN[l])*pow2(fL[k]*fL[l]);
          sigma_N_mix += cos2phi*sin2phi*I1(s,m1,m2,mN[k],mN[l])*pow2(fR[k]*fR[l]);
          sigma_N_mix += (pow2(cos2phi)+pow2(sin2phi))*s*mN[k]*mN[l]*I2(s,m1,m2,mN[k],mN[l])*fL[k]*fL[l]*fR[k]*fR[l];
        }
      }
      sigma_N_mix *= pi*pow2(alpha)/4./pow2(sin2thetaW)/pow2(s);
      // Neutralino interference terms
      sigma_gN = 0;
      for(int k = 0; k < 4; k++){
        sigma_gN += I3(s,m1,m2,mN[k])*(cos2phi*pow2(fL[k])+sin2phi*pow2(fR[k]));
      }
      sigma_gN *= pi*pow2(alpha)/sin2thetaW/pow(s,3);
      sigma_ZN = 0;
      for(int k = 0; k < 4; k++){
        sigma_ZN += I3(s,m1,m2,mN[k])*(Le*cos2phi*pow2(fL[k])+Re*sin2phi*pow2(fR[k]));
      }
      sigma_ZN *= pi*pow2(alpha)/pow2(sin2thetaW)/(1.-sin2thetaW)/pow2(s)*(Le*cos2phi+Re*sin2phi)*ReDZ;
      sigma_ZN_mix = 0;
      for(int k = 0; k < 4; k++){
        sigma_ZN_mix += I3(s,m1,m2,mN[k])*(Le*pow2(fL[k])-Re*pow2(fR[k]));
      }
      sigma_ZN_mix *= pi*pow2(alpha)/pow2(sin2thetaW)/(1.-sin2thetaW)/pow2(s)*sin2phi*cos2phi*(Le-Re)*ReDZ;

      // Total cross section
      if( bMixed ) { sigma = sigma_Z_mix; }
      else { sigma = sigma_g + sigma_Z + sigma_gZ; }
      if( bSelectron && !bMixed ) { sigma += sigma_N + sigma_gN + sigma_ZN; }
      else if( bSelectron && bMixed ) { sigma += sigma_N_mix + sigma_ZN_mix; }

      // Fix units
      sigma *= gev2pb;

      // Return zero in corner cases where numerical roundoff has sent sigma negative.
      return std::max(sigma, 0.0);

    }

    /// Cross section [pb] for \f$e^+e^- -> \tilde\chi^0_i \tilde\chi^0_j\f$
    /// Masses mi and mj for the neutralinos are signed. mS are the selectron masses (left = 0, right = 1).
    /// Warning! BFM uses inverted \f$\tan\beta\f$! Use tanb = 1 / tanb in converting from SLHA.
    double xsec_neuineuj(int pid1, int pid2, double sqrts, double mi, double mj, MixMatrix N,
                         const double mS[2], double tanb, double alpha, double mZ, double gZ, double sin2thetaW)
    {

      // Just return zero if the final state isn't kinematically accessible
      if (std::abs(mi)+std::abs(mj) > sqrts) return 0.0;

      // Translate from PDG codes to neutralino indices (starting at zero)
      int i, j;
      if(pid1 == 1000022) i = 0;
      else if(pid1 == 1000023) i = 1;
      else if(pid1 == 1000025) i = 2;
      else if(pid1 == 1000035) i = 3;
      else
      {
        std::stringstream ss;
        ss << "Invalid final state neutralino PDG code " << pid1;
        ColliderBit_error().raise(LOCAL_INFO, ss.str());
        return -1;
      }
      if(pid2 == 1000022) j = 0;
      else if(pid2 == 1000023) j = 1;
      else if(pid2 == 1000025) j = 2;
      else if(pid2 == 1000035) j = 3;
      else
      {
        std::stringstream ss;
        ss << "Invalid final state neutralino PDG code " << pid2;
        ColliderBit_error().raise(LOCAL_INFO, ss.str());
        return -1;
      }

      // Set slepton masses
      double msL = mS[0];
      double msR = mS[1];

      // Couplings
      // e = g \sin\theta_W = g' \cos\theta_W
      // alpha = e^2 / 4\pi
      int deltaij = 0;
      if (i == j) deltaij = 1;
      double cos2b = (1.-pow2(tanb))/(1.+pow2(tanb));
      double sin2b = 2.*tanb/(1.+pow2(tanb));
      double T3l = -0.5;
      double Le = T3l+sin2thetaW;
      double Re = sin2thetaW;
      double OL[4][4];
      for(int k = 0; k < 4; k++){
        for(int l = 0; l < 4; l++){
          OL[k][l] = 0.5*(N[k][2]*N[l][2]-N[k][3]*N[l][3])*cos2b-0.5*(N[k][2]*N[l][3]+N[k][3]*N[l][2])*sin2b;
        }
      }
      double fL[4], fR[4];
      for(int k = 0; k < 4; k++){
        fL[k] = -sqrt(2.) * (Le*N[k][1]/sqrt(1.-sin2thetaW)+sqrt(sin2thetaW)*N[k][0]);
        fR[k] = sqrt(2.) * sqrt(sin2thetaW) * (sqrt(sin2thetaW/(1.-sin2thetaW))*N[k][1]-N[k][0]);
      }

      // Kinematics
      double s, q, Ei, Ej, DZ2, ReDZ;
      s = pow2(sqrts);
      DZ2 = 1./(pow2(s-pow2(mZ))+pow2(mZ*gZ)); // Breit-Wigner for Z
      ReDZ = (s-pow2(mZ))*DZ2;
      Ei = (s+pow2(mi)-pow2(mj))/2./sqrts;  // Energy of \tilde\chi^0_i in e+e- CoM system
      q = sqrt(pow2(Ei)-pow2(mi));          // Momentum of \tilde\chi^0_i in e+e- CoM system
      Ej = sqrt(pow2(q)+pow2(mj));

      double dL, dR;
      dL = 0.5/s * (s + 2*pow2(msL) - pow2(mi) - pow2(mj));
      dR = 0.5/s * (s + 2*pow2(msR) - pow2(mi) - pow2(mj));

      // Cross sections per diagram and interference terms
      double sigma, sigma_Z, sigma_s, sigma_Zs;
      // Z
      sigma_Z = 4.*pi*pow2(alpha)/pow2(sin2thetaW)/pow2(1.-sin2thetaW) * DZ2 * q/sqrts * pow2(OL[i][j]) * (pow2(Le)+pow2(Re));
      sigma_Z *=  Ei*Ej + 1/3.*pow2(q)-mi*mj;
      // selectrons
      sigma_s  = pow2(fL[i]*fL[j]) * ((Ei*Ej-s*dL+pow2(q))/(s*pow2(dL)-pow2(q)) + 2. + 0.5*sqrts/q*(1.-2.*dL-mi*mj/s/dL)*log(fabs((dL+q/sqrts)/(dL-q/sqrts))));
      sigma_s += pow2(fR[i]*fR[j]) * ((Ei*Ej-s*dR+pow2(q))/(s*pow2(dR)-pow2(q)) + 2. + 0.5*sqrts/q*(1.-2.*dR-mi*mj/s/dR)*log(fabs((dR+q/sqrts)/(dR-q/sqrts))));
      sigma_s *= pi*pow2(alpha)/pow2(sin2thetaW) * q/s/sqrts;
      // Interference
      sigma_Zs  =  Le*fL[i]*fL[j] * (1./q/sqrts*(Ei*Ej-s*dL*(1.-dL)-mi*mj)*log(fabs((dL+q/sqrts)/(dL-q/sqrts)))+2.*(1-dL));
      sigma_Zs += -Re*fR[i]*fR[j] * (1./q/sqrts*(Ei*Ej-s*dR*(1.-dR)-mi*mj)*log(fabs((dR+q/sqrts)/(dR-q/sqrts)))+2.*(1-dR));
      sigma_Zs *= -2.*pi*pow2(alpha)/pow2(sin2thetaW)/(1.-sin2thetaW) * q/sqrts * ReDZ * OL[i][j];

      // Total cross section
      sigma = 0.5*(sigma_Z + sigma_s + sigma_Zs)*(2.-deltaij);

      // Fix units
      sigma *= gev2pb;

      // Return zero in corner cases where numerical roundoff has sent sigma negative.
      return std::max(sigma, 0.0);
    }


    /// Cross section [pb] for \f$e^+e^- -> \tilde\chi^+_i \tilde\chi^-_j\f$
    /// Masses mi and mj for the charginos are signed. msn is electron sneutrino mass.
    double xsec_chaichaj(int pid1, int pid2, double sqrts, double mi, double mj, MixMatrix V,
                         MixMatrix U, double ms, double alpha, double mZ, double gZ, double sin2thetaW)
    {
      // Just return zero if the final state isn't kinematically accessible
      if (std::abs(mi)+std::abs(mj) > sqrts) return 0.0;

      // Translate from PDG codes to chargino indices (silly paper convention that i=2 lighter than i=1!)
      int i, j;
      pid1 = abs(pid1); pid2 = abs(pid2);
      if(pid1 == 1000024) i = 1;
      else if(pid1 == 1000037) i = 0;
      else
      {
        std::stringstream ss;
        ss << "Invalid final state chargino PDG code " << pid1;
        ColliderBit_error().raise(LOCAL_INFO, ss.str());
        return -1;
      }
      if(pid2 == 1000024) j = 1;
      else if(pid2 == 1000037) j = 0;
      else
      {
        std::stringstream ss;
        ss << "Invalid final state chargino PDG code " << pid2;
        ColliderBit_error().raise(LOCAL_INFO, ss.str());
        return -1;
      }

      // Couplings
      int deltaij = 0;
      if (i == j) deltaij = 1;
      // e = g \sin\theta_W = g' \cos\theta_W
      double T3l = -0.5;
      double Le = T3l+sin2thetaW;
      double Re = sin2thetaW;
      double OL[2][2], OR[2][2];
      for(int k = 0; k < 2; k++){
        for(int l = 0; l < 2; l++){
          OL[k][l] = -V[k][0]*V[l][0]-0.5*V[k][1]*V[l][1]+deltaij*sin2thetaW;
          OR[k][l] = -U[k][0]*U[l][0]-0.5*U[k][1]*U[l][1]+deltaij*sin2thetaW;
        }
      }

      // Kinematics
      double s, q, Ei, Ej, DZ2, ReDZ;
      s = pow2(sqrts);
      Ei = (s+pow2(mi)-pow2(mj))/2./sqrts;  // Energy of \tilde\chi^+_i in e+e- CoM system
      q = sqrt(pow2(Ei)-pow2(mi));          // Momentum of \tilde\chi^+_i in e+e- CoM system
      Ej = sqrt(pow2(q)+pow2(mj));
      DZ2 = 1./(pow2(s-pow2(mZ))+pow2(mZ*gZ)); // Breit-Wigner for Z
      ReDZ = (s-pow2(mZ))*DZ2;

      double aL, bL, h;
      aL = 0.5/pow2(ms)*(2*pow2(ms)+s-pow2(mi)-pow2(mj));
      bL = q*sqrts/pow2(ms);
      h = 2.*q*sqrts-2.*pow2(q)*aL/bL+(Ei*Ej+pow2(q*aL/bL)-q*sqrts*aL/bL)*log(fabs((aL+bL)/(aL-bL)));

      // Cross sections per diagram and interference terms
      double sigma, sigma_g, sigma_Z, sigma_s, sigma_gZ, sigma_gs, sigma_Zs;
      // Gamma
      sigma_g = 8*pi*pow2(alpha) * q*sqrts/pow(s,3) * deltaij * (Ei*Ej+pow2(q)/3.+fabs(mi*mj));
      // Z
      sigma_Z = 2.*pi*pow2(alpha)/pow2(sin2thetaW)/pow2(1.-sin2thetaW) * q/sqrts * DZ2;
      sigma_Z *= (pow2(OL[i][j])+pow2(OR[i][j]))*(pow2(Le)+pow2(Re))*(Ei*Ej+pow2(q)/3.)+2.*(pow2(Le)+pow2(Re))*OL[i][j]*OR[i][j]*mi*mj;
      // Sneutrino
      sigma_s = pi*pow2(alpha)/2./pow2(sin2thetaW)*pow2(V[i][0]*V[j][0])/pow(ms,4) * q/sqrts;
      sigma_s *= (Ei*Ej+pow2(q)-q*sqrts*aL/bL)/(pow2(aL)-pow2(bL)) + 2.*pow2(q/bL) + 0.5/pow2(bL)*(q*sqrts-2.*pow2(q)*aL/bL)*log(fabs((aL+bL)/(aL-bL)));
      // Interference
      sigma_gZ = 4*pi*pow2(alpha)/(1.-sin2thetaW)/sin2thetaW * q*sqrts/pow2(s)*ReDZ*deltaij*(Le+Re);
      sigma_gZ *= (OL[i][j]+OR[i][j])*(Ei*Ej+pow2(q)/3.+fabs(mi*mj));
      sigma_gs = -pi*pow2(alpha)/sin2thetaW*pow2(V[i][0]) * deltaij/pow2(s);
      sigma_gs *= h + fabs(mi*mj)*log(fabs((aL+bL)/(aL-bL)));
      sigma_Zs = -pi*pow2(alpha)/pow2(sin2thetaW)/(1.-sin2thetaW)*V[i][0]*V[j][0] * ReDZ/s * Le;
      sigma_Zs *= OL[i][j]*h + OR[i][j]*mi*mj*log(fabs((aL+bL)/(aL-bL)));

      // Total cross section with interference terms
      sigma = sigma_g + sigma_Z + sigma_s+ sigma_gZ + sigma_gs + sigma_Zs;

      // Units
      sigma *= gev2pb;

      // Return zero in corner cases where numerical roundoff has sent sigma negative.
      return std::max(sigma, 0.0);

    }


    ///////////////////////////////////////////////////////////////////////
    /// Functions to convert mass matrices between SLHA and BFM conventions
    ///////////////////////////////////////////////////////////////////////
    /// @{

    /// Converts a neutralino mixing matrix in SLHA conventions to BFM conventions, \f$\tan\beta\f$ is as defined in SLHA
    void SLHA2BFM_NN(MixMatrix &NN, double tanb, double sin2thetaW)
    {
      // Define conversion matrix
      double sinthetaW = sqrt(sin2thetaW);
      double costhetaW = sqrt(1.-sin2thetaW);
      double tanv = 1./tanb;       // Needed because of convention difference
      double sinv = sin(atan(tanv));
      double cosv = cos(atan(tanv));
      MixMatrix T(4,std::vector<double>(4));
      T[0][0] = costhetaW; T[0][1] = -sinthetaW;
      T[1][0] = sinthetaW; T[1][1] = costhetaW;
      T[2][2] = sinv;   T[2][3] = cosv;
      T[3][2] = -cosv;  T[3][3] = sinv;
      // Multiply N_{BFM} = N_{SLHA} T
      NN = multiply(NN,T);
    }

    /// Converts the chargino mixing matrix V in SLHA conventions to BFM conventions
    void SLHA2BFM_VV(MixMatrix &VV)
    {
      // Define conversion matrix (\sigma_3)
      MixMatrix T(2,std::vector<double>(2));
      T[0][0] = 1; T[0][1] =  0;
      T[1][0] = 0; T[1][1] = -1;
      // Multiply V_{BFM} = \sigma_3 V_{SLHA}
      VV = multiply(T,VV);
    }

    /// Converts a neutralino mixing matrix in BFM conventions to SLHA conventions, \f$\tan\beta\f$ is as defined in SLHA
    void BFM2SLHA_NN(MixMatrix &NN, double tanb, double sin2thetaW)
    {
      // Define conversion matrix
      double sinthetaW = sqrt(sin2thetaW);
      double costhetaW = sqrt(1.-sin2thetaW);
      double tanv = 1./tanb;       // Needed because of convention difference
      double sinv = sin(atan(tanv));
      double cosv = cos(atan(tanv));
      MixMatrix T(4,std::vector<double>(4));
      T[0][0] = costhetaW; T[0][1] = -sinthetaW;
      T[1][0] = sinthetaW; T[1][1] = costhetaW;
      T[2][2] = sinv;   T[2][3] = cosv;
      T[3][2] = -cosv;  T[3][3] = sinv;
      // Multiply N_{SLHA} = N_{BFM} T^T
      NN = multiply(NN,transpose(T));
    }

    /// Converts the chargino mixing matrix V in BFM conventions to SLHA conventions
    void BFM2SLHA_VV(MixMatrix &VV)
    {
      SLHA2BFM_VV(VV);
    }

    /// Helper function to multiply matrices
    MixMatrix multiply(MixMatrix A, MixMatrix B)
    {
      int dim = A.size();
      MixMatrix C(dim,std::vector<double>(dim));
      for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
          for(int k = 0; k < dim; k++){
            C[i][j] += A[i][k] * B[k][j];
          }
        }
      }
      return C;
    }

    /// Helper function to find matrix transpose
    MixMatrix transpose(MixMatrix A)
    {
      double temp;
      int dim = A.size();
      for(int i = 0; i < dim; i++){
        for(int j = i+1; j < dim; j++){
          temp = A[i][j];
          A[i][j] = A[j][i];
          A[j][i] = temp;
        }
      }
      return A;
    }

    /// Helper function to print a matrix
    void print(MixMatrix A)
    {
      int dim = A.size();
      cout << "Matrix dimension: " << dim << endl;
      for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
          cout << A[i][j] << " ";
          if(j == dim-1) cout << endl;
        }
      }
    }

    /// @}

  }
}
