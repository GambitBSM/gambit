//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of convenience (i.e. non-Gambit)
///  functions used by more than one SpecBit 
///  source file.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Nov
///
///  *********************************************

#include "gambit/SpecBit/SpecBit_helpers.hpp"

namespace Gambit
{

  namespace SpecBit
  {

    /// @{ SUSY-specific helper functions

    /// Check that the SUSY spectrum has the canonical LSP for the model being scanned.
    void check_LSP(const Spectrum& spec, std::vector<int> LSPs)
    {
      // Fill the list of possible candidate LSPs is the are part of the spectrum
      // {~d, ~u, ~l, ~nu, ~g, ~chi0, ~chip}
      std::vector<int> LSP_candidates = {1000001,1000002,1000011,1000012,1000021,1000022,1000024};

      std::vector<double> m_LSP_candidates;
      for(int lsp_candidate : LSP_candidates)
        if(spec.has(Par::Pole_Mass, lsp_candidate, 0))
          m_LSP_candidates.push_back(std::abs(spec.get(Par::Pole_Mass, lsp_candidate, 0)));

      // Get the lightest of the canonical LSPs for this model
      double canonical_LSP = LSPs[0];
      for(int lsp : LSPs)
        if(spec.get(Par::Pole_Mass, canonical_LSP, 0) > spec.get(Par::Pole_Mass, lsp, 0))
          canonical_LSP = lsp;

      // Loop over candidates and invalidate if one is the lightest
      for(m_lsp_candidate : m_LSP_candidates)
      {
        if(spec.get(Par::Pole_Mass, canonical_LSP, 0) > m_lsp_candidate)
        {
          str canonical_LSP_name = Models::ParticleDB().long_name(canonical_LSP, 0);
          invalid_point().raise(canonical_LSP_name + " is not LSP.");
        }
      }

    }

    /// Helper to work with pointer
    void check_LSP(const Spectrum* spec, std::vector<int> LSPs)
    {
      check_LSP(*spec, LSPs);
    }

    /// Add gravitino mass to the spectrum and list of LSPs
    void add_gravitino_mass(Spectrum& spec, std::vector<int> &LSPs, double mG, const safe_ptr<Options>& runOptions)
    {
        static const double gmax = runOptions->getValueOrDef<double>(10.0, "max_permitted_gravitino_mass_GeV");
        if (mG > gmax)
        {
          std::ostringstream msg;
          msg << "Gravitino mass ("<<mG<<" GeV) is greater than permitted in *_lightgravitno models ("<<gmax<<" GeV).\n"
            << "If you know what you are doing(!), this behaviour can be modified with option max_permitted_gravitino_mass_GeV.";
          SpecBit_error().raise(LOCAL_INFO,msg.str());
        }

        spec.set(mG, Par::Pole_Mass, "~G");
        if (runOptions->getValueOrDef<bool>(true, "only_gravitino_LSP"))
          LSPs = {1000039};
        else
          LSPs.push_back(1000039);
    }

    /// Adds additional information from interesting combinations of MSSM parameters
    void add_extra_MSSM_parameter_combinations(std::map<std::string,double>& specmap, const Spectrum& mssm)
    {
      double At = 0;
      double Ab = 0;
      const double Yt = mssm.get(Par::dimensionless, "Yu", 3, 3);
      const double Yb = mssm.get(Par::dimensionless, "Yd", 3, 3);
      if(std::abs(Yt) > 1e-12)
      {
        At = mssm.get(Par::mass1, "TYu", 3, 3) / Yt;
      }
      if(std::abs(Yb) > 1e-12)
      {
        Ab = mssm.get(Par::mass1, "TYd", 3, 3) / Yb;
      }

      const double MuSUSY = mssm.get(Par::mass1, "Mu");
      const double tb = mssm.get(Par::dimensionless, "tanbeta");

      specmap["Xt"] = At - MuSUSY / tb;
      specmap["Xb"] = Ab - MuSUSY * tb;
      /// Determine which states are the third gens then add them for printing
      str msf1, msf2;
      /// Since this is for printing we only want to invalidate the point
      /// if this is completely wrong.
      /// We can also plot the mixing if we are suspicious.
      const static double tol = 0.5;
      const static bool pt_error = true;
      slhahelp::family_state_mix_matrix("~u", 3, msf1, msf2, mssm, tol,
                                        LOCAL_INFO, pt_error);
      specmap["mstop1"] =  mssm.get(Par::Pole_Mass, msf1);
      specmap["mstop2"] =  mssm.get(Par::Pole_Mass, msf2);
      slhahelp::family_state_mix_matrix("~d", 3, msf1, msf2, mssm, tol,
                                        LOCAL_INFO, pt_error);
      specmap["msbottom1"] =  mssm.get(Par::Pole_Mass, msf1);
      specmap["msbottom2"] =  mssm.get(Par::Pole_Mass, msf2);
      slhahelp::family_state_mix_matrix("~e-", 3, msf1, msf2, mssm, tol,
                                        LOCAL_INFO, pt_error);
      specmap["mstau1"] =  mssm.get(Par::Pole_Mass, msf1);
      specmap["mstau2"] =  mssm.get(Par::Pole_Mass, msf2);
      /// return mass eigenstate strings that best represent required gauge
      /// eigenstate
      const str gs_suL = slhahelp::mass_es_from_gauge_es("~u_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msupL"] = mssm.get(Par::Pole_Mass,gs_suL);
      const str gs_scL = slhahelp::mass_es_from_gauge_es("~c_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mscharmL"] = mssm.get(Par::Pole_Mass,gs_scL);
      const str gs_sdL = slhahelp::mass_es_from_gauge_es("~d_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
     specmap["msdownL"] = mssm.get(Par::Pole_Mass,gs_sdL);
      const str gs_ssL = slhahelp::mass_es_from_gauge_es("~s_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msstrangeL"] = mssm.get(Par::Pole_Mass,gs_ssL);
      const str gs_suR = slhahelp::mass_es_from_gauge_es("~u_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msupR"] = mssm.get(Par::Pole_Mass,gs_suR);
      const str gs_scR = slhahelp::mass_es_from_gauge_es("~c_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mscharmR"] = mssm.get(Par::Pole_Mass,gs_scR);
      const str gs_sdR = slhahelp::mass_es_from_gauge_es("~d_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msdownR"] = mssm.get(Par::Pole_Mass,gs_sdR);
      const str gs_ssR = slhahelp::mass_es_from_gauge_es("~s_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msstrangeR"] = mssm.get(Par::Pole_Mass,gs_ssR);
      const str gs_seL = slhahelp::mass_es_from_gauge_es("~e_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mselectronL"] = mssm.get(Par::Pole_Mass,gs_seL);
      const str gs_sMuL = slhahelp::mass_es_from_gauge_es("~mu_L", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msmuonL"] = mssm.get(Par::Pole_Mass,gs_sMuL);
      const str gs_seR = slhahelp::mass_es_from_gauge_es("~e_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["mselectronR"] = mssm.get(Par::Pole_Mass,gs_seR);
      const str gs_sMuR = slhahelp::mass_es_from_gauge_es("~mu_R", mssm, tol,
                                                         LOCAL_INFO, pt_error);
      specmap["msmuonR"] = mssm.get(Par::Pole_Mass,gs_sMuR);

    }

    /// Helper function to work out if the LSP is invisible, and if so, which particle it is.
    std::vector<std::pair<str,str>> get_invisibles(const Spectrum& spec)
    {
      // Get the lighter of the lightest neutralino and the lightest sneutrino
      std::pair<str,double> neutralino("~chi0_1", spec.get(Par::Pole_Mass,"~chi0",1));
      std::pair<str,double> sneutrino("~nu_1", spec.get(Par::Pole_Mass,"~nu",1));
      std::pair<str,double> lnp = (neutralino.second < sneutrino.second ? neutralino : sneutrino);

      // Work out if this is indeed the LSP, and if decays of at least one neutral higgs to it are kinematically possible.
      bool inv_lsp = spec.get(Par::Pole_Mass,"~chi+",1) > lnp.second and
                     spec.get(Par::Pole_Mass,"~g") > lnp.second and
                     spec.get(Par::Pole_Mass,"~d",1) > lnp.second and
                     spec.get(Par::Pole_Mass,"~u",1) > lnp.second and
                     spec.get(Par::Pole_Mass,"~e-",1) > lnp.second and
                     (spec.get(Par::Pole_Mass,"h0",2) > 2.*lnp.second or
                      spec.get(Par::Pole_Mass,"A0") > 2.*lnp.second);

      // Create a vector containing all invisible products of higgs decays.
      if (inv_lsp) return initVector<std::pair<str,str>>(std::make_pair(lnp.first,lnp.first));
      return std::vector<std::pair<str,str>>();
    }



  }
}

