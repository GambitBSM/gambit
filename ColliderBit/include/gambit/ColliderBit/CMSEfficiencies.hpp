//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  \file
///  Functions that do super fast CMS detector
///  simulation based on four-vector smearing.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Andy Buckley
///  \author Abram Krislock
///  \author Anders Kvellestad
///  \author Matthias Danninger
///  \author Rose Kudzman-Blais
///
///  *********************************************


#pragma once

#include <cfloat>

#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"

#include "HEPUtils/MathUtils.h"
#include "HEPUtils/BinnedFn.h"
#include "HEPUtils/Event.h"
#include <iomanip>
#include <algorithm>


namespace Gambit
{

  namespace ColliderBit
  {


    /// CMS-specific efficiency and smearing functions for super fast detector simulation
    namespace CMS
    {

      /// @name CMS detector efficiency functions
      ///@{

      /// Randomly filter the supplied particle list by parameterised electron tracking efficiency
      inline void applyElectronTrackingEff(std::vector<const HEPUtils::Particle*>& electrons) {
        static HEPUtils::BinnedFn2D<double> _elTrackEff2d({{0, 1.5, 2.5, DBL_MAX}}, //< |eta|
                                                          {{0, 0.1, 1.0, DBL_MAX}}, //< pT
                                                          {{0., 0.70, 0.95, // |eta| 0.1-1.5
                                                            0., 0.60, 0.85, // |eta| 1.5-2.5
                                                            0., 0.,   0.}}); // |eta| > 2.5
        filtereff_etapt(electrons, _elTrackEff2d);
      }


      /// Randomly filter the supplied particle list by parameterised electron efficiency
      /// @note Should be applied after the electron energy smearing
      /// @note Eff values currently identical to those in ATLAS (AB, 2016-01-24)
      inline void applyElectronEff(std::vector<const HEPUtils::Particle*>& electrons) {
        static HEPUtils::BinnedFn2D<double> _elEff2d({{0, 1.5, 2.5, DBL_MAX}}, //< |eta|
                                                     {{0, 10., DBL_MAX}}, //< pT
                                                     {{0., 0.95, // |eta| 0.1-1.5
                                                       0., 0.85, // |eta| 1.5-2.5
                                                       0., 0.}}); // |eta| > 2.5
        filtereff_etapt(electrons, _elEff2d);
      }


      /// Randomly filter the supplied particle list by parameterised muon tracking efficiency
      /// @note Eff values currently identical to those in ATLAS (AB, 2016-01-24)
      inline void applyMuonTrackEff(std::vector<const HEPUtils::Particle*>& muons) {
        static HEPUtils::BinnedFn2D<double> _muTrackEff2d({{0, 1.5, 2.5, DBL_MAX}}, //< |eta|
                                                          {{0, 0.1, 1.0, DBL_MAX}}, //< pT
                                                          {{0, 0.75, 0.99, // |eta| 0.1-1.5
                                                            0, 0.70, 0.98, // |eta| 1.5-2.5
                                                            0, 0,    0}}); // |eta| > 2.5
        filtereff_etapt(muons, _muTrackEff2d);
      }


      /// Randomly filter the supplied particle list by parameterised muon efficiency
      inline void applyMuonEff(std::vector<const HEPUtils::Particle*>& muons) {
        if(muons.empty()) return;
        auto keptMuonsEnd = std::remove_if(muons.begin(), muons.end(),
                                           [](const HEPUtils::Particle* p) {
                                             bool rm(p->abseta() > 2.4 || p->pT() < 10);
                                             if (!rm)
                                             {
                                               const double eff = 0.95 * (p->pT() <= 1.0e3 ? 1 : exp(0.5 - 5e-4*p->pT()));
                                               rm = !random_bool(eff);
                                             }
                                             return rm;
                                           } );
        muons.erase(keptMuonsEnd, muons.end());
      }


      /// @brief Randomly filter the supplied particle list by parameterised tau efficiency
      /// @note No delete, because this should only ever be applied to copies of the Event Particle* vectors in Analysis routines
      inline void applyTauEfficiency(std::vector<const HEPUtils::Particle*>& taus) {
        filtereff(taus, 0.6);
      }


      /// @brief Randomly smear the supplied electrons' momenta by parameterised resolutions
      ///
      /// Function that mimics the DELPHES electron energy resolution.
      /// We need to smear E, then recalculate pT, then reset the 4-vector.
      inline void smearElectronEnergy(std::vector<HEPUtils::Particle*>& electrons) {

        // Now loop over the electrons and smear the 4-vectors
        for (HEPUtils::Particle* e : electrons) {

          // Calculate resolution
          // for pT > 0.1 GeV, E resolution = |eta| < 0.5 -> sqrt(0.06^2 + pt^2 * 1.3e-3^2)
          //                                  |eta| < 1.5 -> sqrt(0.10^2 + pt^2 * 1.7e-3^2)
          //                                  |eta| < 2.5 -> sqrt(0.25^2 + pt^2 * 3.1e-3^2)
          double resolution = 0;
          const double abseta = e->abseta();
          if (e->pT() > 0.1 && abseta < 2.5) {
            if (abseta < 0.5) {
              resolution = HEPUtils::add_quad(0.06, 1.3e-3 * e->pT());
            } else if (abseta < 1.5) {
              resolution = HEPUtils::add_quad(0.10, 1.7e-3 * e->pT());
            } else { // still |eta| < 2.5
              resolution = HEPUtils::add_quad(0.25, 3.1e-3 * e->pT());
            }
          }

          // Smear by a Gaussian centered on the current energy, with width given by the resolution
          if (resolution > 0) {
            std::normal_distribution<> d(e->E(), resolution);
            double smeared_E = d(Random::rng());
            if (smeared_E < e->mass()) smeared_E = 1.01*e->mass();
            // double smeared_pt = smeared_E/cosh(e->eta()); ///< @todo Should be cosh(|eta|)?
            e->set_mom(HEPUtils::P4::mkEtaPhiME(e->eta(), e->phi(), e->mass(), smeared_E));
          }
        }
      }


      /// @brief Randomly smear the supplied muons' momenta by parameterised resolutions
      ///
      /// Function that mimics the DELPHES muon momentum resolution.
      /// We need to smear pT, then recalculate E, then reset the 4-vector.
      inline void smearMuonMomentum(std::vector<HEPUtils::Particle*>& muons) {

        // Now loop over the muons and smear the 4-vectors
        for (HEPUtils::Particle* p : muons) {

          // Calculate resolution
          // for pT > 0.1 GeV, mom resolution = |eta| < 0.5 -> sqrt(0.01^2 + pt^2 * 2.0e-4^2)
          //                                    |eta| < 1.5 -> sqrt(0.02^2 + pt^2 * 3.0e-4^2)
          //                                    |eta| < 2.5 -> sqrt(0.05^2 + pt^2 * 2.6e-4^2)
          double resolution = 0;
          const double abseta = p->abseta();
          if (p->pT() > 0.1 && abseta < 2.5) {
            if (abseta < 0.5) {
              resolution = HEPUtils::add_quad(0.01, 2.0e-4 * p->pT());
            } else if (abseta < 1.5) {
              resolution = HEPUtils::add_quad(0.02, 3.0e-4 * p->pT());
            } else { // still |eta| < 2.5... but isn't CMS' mu acceptance < 2.4?
              resolution = HEPUtils::add_quad(0.05, 2.6e-4 * p->pT());
            }
          }

          // Smear by a Gaussian centered on the current pT, with width given by the resolution
          std::normal_distribution<> d(p->pT(), resolution*p->pT());
          double smeared_pt = d(Random::rng());
          if (smeared_pt < 0) smeared_pt = 0;
          // const double smeared_E = smeared_pt*cosh(mu->eta()); ///< @todo Should be cosh(|eta|)?
          // std::cout << "Muon pt " << mu_pt << " smeared " << smeared_pt << std::endl;
          p->set_mom(HEPUtils::P4::mkEtaPhiMPt(p->eta(), p->phi(), p->mass(), smeared_pt));
        }
      }


      /// @brief Randomly smear the supplied jets' momenta by parameterised resolutions
      ///
      /// Function that mimics the DELPHES jet momentum resolution.
      /// We need to smear pT, then recalculate E, then reset the 4-vector
      ///
      /// @todo Update cf. Matthias study for ATLAS
      inline void smearJets(std::vector<HEPUtils::Jet*>& jets) {

        // Const resolution for now
        /// @todo This is the ATLAS number... I can't find values for the CMS parameterisation, cf.
        ///   https://cds.cern.ch/record/1339945/files/JME-10-014-pas.pdf
        ///   https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideJetResolution
        ///   https://github.com/adrager/cmssw/blob/CMSSW_7_2_X/CondFormats/JetMETObjects/test/TestCorrections.C
        //const double resolution = 0.03;

        // Matthias jet smearing implemented roughly from https://arxiv.org/pdf/1607.03663.pdf
        // Parameterisation can be still improved as functional form is given
        // Pileup of <mu>=25 is taken, as JER depends strongly on mu
        // CMS does not include information about JER at eta>1.3
        const std::vector<double>  binedges_eta = {0,10.};
        const std::vector<double>  binedges_pt = {0,20,30,40,50.,70.,100.,150.,200.,1000.,10000.};
        const std::vector<double> JetsJER = {0.3,0.2,0.16,0.145,0.12,0.1,0.09,0.08,0.06,0.05};
        static HEPUtils::BinnedFn2D<double> _resJets2D(binedges_eta,binedges_pt,JetsJER);

        // Now loop over the jets and smear the 4-vectors
        for (HEPUtils::Jet* jet : jets) {
          const double resolution = _resJets2D.get_at(jet->abseta(), jet->pT());
          std::normal_distribution<> d(1., resolution);
          // Smear by a Gaussian centered on 1 with width given by the (fractional) resolution
          double smear_factor = d(Random::rng());
          jet->set_mom(HEPUtils::P4::mkXYZM(jet->mom().px()*smear_factor, jet->mom().py()*smear_factor, jet->mom().pz()*smear_factor, jet->mass()));
        }
      }


      /// @brief Randomly smear the supplied hadronic taus' momenta by parameterised resolutions
      ///
      /// We need to smear pT, then recalculate E, then reset the 4-vector.
      /// Same as for jets, but on a vector of particles. (?)
      ///
      /// @todo Update cf. Matthias study for ATLAS
      inline void smearTaus(std::vector<HEPUtils::Particle*>& taus) {

        // Const resolution for now
        const double resolution = 0.03;

        // Now loop over the jets and smear the 4-vectors
        std::normal_distribution<> d(1., resolution);
        for (HEPUtils::Particle* p : taus) {
          // Smear by a Gaussian centered on 1 with width given by the (fractional) resolution
          double smear_factor = d(Random::rng());
          /// @todo Is this the best way to smear? Should we preserve the mean jet energy, or pT, or direction?
          p->set_mom(HEPUtils::P4::mkXYZM(p->mom().px()*smear_factor, p->mom().py()*smear_factor, p->mom().pz()*smear_factor, p->mass()));
        }
      }

      ///Apply efficiency function to CSVv2 medium WP b-tagged jets
      ///@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/btag_eff_CSVv2_DeepCSV.pdf
      inline void applyCSVv2MediumBtagEff(std::vector<const HEPUtils::Jet*>& bjets) {
        if (bjets.empty()) return;

        const static std::vector<double> binedges_et = {25., 40., 60., 80., 100., 150., 200., 250., 300., 400., 500.,DBL_MAX };
        const static std::vector<double> bineffs_et  = {0.58, 0.61, 0.63, 0.64, 0.65, 0.62,0.6, 0.58, 0.56, 0.52, 0.48};
        const static HEPUtils::BinnedFn1D<double> _eff_et(binedges_et, bineffs_et);

        auto keptBjetsEnd = std::remove_if(bjets.begin(), bjets.end(),
                                              [](const HEPUtils::Jet* bjet) {
                                                 const double bjet_pt = bjet->pT();
                                                 const double bjet_aeta = bjet->abseta();
                                                 if (bjet_aeta > 2.4 || bjet_pt < 25) return true;
                                                 const double eff = _eff_et.get_at(bjet_pt);
                                                 return random_bool(1-eff);
                                               } );
        bjets.erase(keptBjetsEnd, bjets.end());
      }

      inline void applyCSVv2MediumBtagEff(std::vector<HEPUtils::Jet*>& bjets) {
        applyCSVv2MediumBtagEff(reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(bjets));
      }

      ///Apply efficiency function to CSVv2 loose WP b-tagged jets
      ///@note Numbers digitized from https://twiki.cern.ch/twiki/pub/CMSPublic/SUSMoriond2017ObjectsEfficiency/btag_eff_CSVv2_DeepCSV.pdf
      inline void applyCSVv2LooseBtagEff(std::vector<const HEPUtils::Jet*>& bjets) {
        if (bjets.empty()) return;

        const static std::vector<double> binedges_et = {25., 40., 60., 80., 100., 150., 200., 250., 300., 400., 500.,DBL_MAX };
        const static std::vector<double> bineffs_et  = {0.78, 0.80, 0.82, 0.83, 0.84, 0.825, 0.82, 0.81, 0.8, 0.795, 0.79};
        const static HEPUtils::BinnedFn1D<double> _eff_et(binedges_et, bineffs_et);

        auto keptBjetsEnd = std::remove_if(bjets.begin(), bjets.end(),
                                              [](const HEPUtils::Jet* bjet) {
                                                 const double bjet_pt = bjet->pT();
                                                 const double bjet_aeta = bjet->abseta();
                                                 if (bjet_aeta > 2.4 || bjet_pt < 25) return true;
                                                 const double eff = _eff_et.get_at(bjet_pt);
                                                 return random_bool(1-eff);
                                               } );
        bjets.erase(keptBjetsEnd, bjets.end());
      }

      inline void applyCSVv2LooseBtagEff(std::vector<HEPUtils::Jet*>& bjets) {
        applyCSVv2LooseBtagEff(reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(bjets));
      }


      ///Apply user-specified b-tag misidentification rate (flat)
      inline void applyBtagMisId(double mis_id_prob, std::vector<const HEPUtils::Jet*>& jets, std::vector<const HEPUtils::Jet*>& bjets) {
        if (jets.empty()) return;
        for (const HEPUtils::Jet* jet : jets) {
          // Only apply misidentification rate for non-b-jets
          if (!jet->btag() && random_bool(mis_id_prob)) bjets.push_back(jet);
        }
      }

      inline void applyBtagMisId(double mis_id_prob, std::vector<HEPUtils::Jet*>& jets, std::vector<HEPUtils::Jet*>& bjets) {
        applyBtagMisId(mis_id_prob, reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(jets), reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(bjets));
      }


      ///Apply b-tag misidentification rate for CSVv2 loose WP
      ///@note Numbers from Table 2 in https://arxiv.org/pdf/1712.07158.pdf
      inline void applyCSVv2LooseBtagMisId(std::vector<const HEPUtils::Jet*>& jets, std::vector<const HEPUtils::Jet*>& bjets) {
        if (jets.empty()) return;
        // For now we apply the (pT-averaged) light-flavour misidentification rate to all jets.
        // Realistically, the rate should be higher for c-jets.
        const static double mis_id_prob = 0.089;
        applyBtagMisId(mis_id_prob, jets, bjets);
      }

      inline void applyCSVv2LooseBtagMisId(std::vector<HEPUtils::Jet*>& jets, std::vector<HEPUtils::Jet*>& bjets) {
        applyCSVv2LooseBtagMisId(reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(jets), reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(bjets));
      }


      ///Apply both b-tag efficiency and misidentification rate for CSVv2 loose WP
      inline void applyCSVv2LooseBtagEffAndMisId(std::vector<const HEPUtils::Jet*>& jets, std::vector<const HEPUtils::Jet*>& bjets) {
        if (jets.empty() && bjets.empty()) return;
        // Apply b-tag efficiency
        applyCSVv2LooseBtagEff(bjets);
        // Apply misidentification rate to the non-b-jets in the jets vector
        applyCSVv2LooseBtagMisId(jets, bjets);
      }

      inline void applyCSVv2LooseBtagEffAndMisId(std::vector<HEPUtils::Jet*>& jets, std::vector<HEPUtils::Jet*>& bjets) {
        applyCSVv2LooseBtagEffAndMisId(reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(jets), reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(bjets));
      }


      ///Apply b-tag misidentification rate for CSVv2 medium WP
      ///@note Numbers from Table 2 in https://arxiv.org/pdf/1712.07158.pdf
      inline void applyCSVv2MediumBtagMisId(std::vector<const HEPUtils::Jet*>& jets, std::vector<const HEPUtils::Jet*>& bjets) {
        if (jets.empty()) return;
        // For now we apply the (pT-averaged) light-flavour misidentification rate to all jets.
        // Realistically, the rate should be higher for c-jets.
        const static double mis_id_prob = 0.009;
        applyBtagMisId(mis_id_prob, jets, bjets);
      }

      inline void applyCSVv2MediumBtagMisId(std::vector<HEPUtils::Jet*>& jets, std::vector<HEPUtils::Jet*>& bjets) {
        applyCSVv2MediumBtagMisId(reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(jets), reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(bjets));
      }


      ///Apply both b-tag efficiency and misidentification rate for CSVv2 medium WP
      inline void applyCSVv2MediumBtagEffAndMisId(std::vector<const HEPUtils::Jet*>& jets, std::vector<const HEPUtils::Jet*>& bjets) {
        if (jets.empty() && bjets.empty()) return;
        // Apply b-tag efficiency
        applyCSVv2MediumBtagEff(bjets);
        // Apply misidentification rate to the non-b-jets in the jets vector
        applyCSVv2MediumBtagMisId(jets, bjets);
      }

      inline void applyCSVv2MediumBtagEffAndMisId(std::vector<HEPUtils::Jet*>& jets, std::vector<HEPUtils::Jet*>& bjets) {
        applyCSVv2MediumBtagEffAndMisId(reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(jets), reinterpret_cast<std::vector<const HEPUtils::Jet*>&>(bjets));
      }

      ///@}

    }
  }
}
