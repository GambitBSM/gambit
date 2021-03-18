//   GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
///
///  \file
///  Functions that do super fast ATLAS detector
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
///  \author Pat Scott
///  \author Tomas Gonzalo
///
///  *********************************************


#pragma once

#include <cfloat>

#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/Utils/threadsafe_rng.hpp"

#include "HEPUtils/MathUtils.h"
#include "HEPUtils/BinnedFn.h"
#include "HEPUtils/Event.h"

namespace Gambit
{

  namespace ColliderBit
  {


    /// ATLAS-specific efficiency and smearing functions for super fast detector simulation
    namespace ATLAS
    {

      /// @name ATLAS detector efficiency functions
      ///@{

        // /// Randomly filter the supplied particle list by parameterised electron tracking efficiency
        // /// @todo Remove? This is not the electron efficiency
        // inline void applyElectronTrackingEff(std::vector<const HEPUtils::Particle*>& electrons) {
        //   static HEPUtils::BinnedFn2D<double> _elTrackEff2d({{0, 1.5, 2.5, DBL_MAX}}, //< |eta|
        //                                                     {{0, 0.1, 1.0, 100, DBL_MAX}}, //< pT
        //                                                     {{0., 0.73, 0.95, 0.99,
        //                                                       0., 0.5,  0.83, 0.90,
        //                                                       0., 0.,   0.,   0.}});
        //   filtereff_etapt(electrons, _elTrackEff2d);
        // }


        /// Randomly filter the supplied particle list by parameterised electron efficiency
        /// @note Should be applied after the electron energy smearing
        inline void applyElectronEff(std::vector<const HEPUtils::Particle*>& electrons) {
          static HEPUtils::BinnedFn2D<double> _elEff2d({{0,1.5,2.5,DBL_MAX}}, //< |eta|
                                                       {{0,10.,DBL_MAX}}, //< pT
                                                       {{0., 0.95,
                                                         0., 0.85,
                                                         0., 0.}});
          filtereff_etapt(electrons, _elEff2d);
        }


        // /// Randomly filter the supplied particle list by parameterised muon tracking efficiency
        // /// @todo Remove? This is not the muon efficiency
        // inline void applyMuonTrackEff(std::vector<const HEPUtils::Particle*>& muons) {
        //   static HEPUtils::BinnedFn2D<double> _muTrackEff2d({{0,1.5,2.5,DBL_MAX}}, //< |eta|
        //                                                     {{0,0.1,1.0,DBL_MAX}}, //< pT
        //                                                     {{0., 0.75, 0.99,
        //                                                       0., 0.70, 0.98,
        //                                                       0., 0.,   0.}});
        //   filtereff_etapt(muons, _muTrackEff2d);
        // }


        /// Randomly filter the supplied particle list by parameterised muon efficiency
        inline void applyMuonEff(std::vector<const HEPUtils::Particle*>& muons) {
          static HEPUtils::BinnedFn2D<double> _muEff2d({{0,1.5,2.7,DBL_MAX}}, //< |eta|
                                                       {{0,10.0,DBL_MAX}}, //< pT
                                                       {{0., 0.95,
                                                         0., 0.85,
                                                         0., 0.}});
          filtereff_etapt(muons, _muEff2d);
        }


        /// Randomly filter the supplied particle list by parameterised muon efficiency
        inline void applyMuonEffR2(std::vector<const HEPUtils::Particle*>& muons) {
          static HEPUtils::BinnedFn2D<double> _muEff2d({0, 2.7, DBL_MAX}, //< |eta|
                                                       {0., 3.5, 4., 5., 6., 7., 8., 10., DBL_MAX}, //< pT
                                                       {0.00, 0.76, 0.94, 0.97, 0.98, 0.98, 0.98, 0.99,//
                                                        0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00});
          filtereff_etapt(muons, _muEff2d);
        }


        /// Randomly filter the supplied particle list by parameterised Run 1 tau efficiency
        /// @note From Delphes 3.1.2
        /// @todo Use https://cds.cern.ch/record/1233743/files/ATL-PHYS-PUB-2010-001.pdf -- it is more accurate and has pT-dependence
        inline void applyTauEfficiencyR1(std::vector<const HEPUtils::Particle*>& taus) {
          filtereff(taus, 0.40);
        }


        /// Randomly filter the supplied particle list by parameterised Run 2 tau efficiency
        /// @note From Delphes 3.3.2 & ATL-PHYS-PUB-2015-045, 60% for 1-prong, 70% for multi-prong: this is *wrong*!!
        /// @note No delete, because this should only ever be applied to copies of the Event Particle* vectors in Analysis routines
        inline void applyTauEfficiencyR2(std::vector<const HEPUtils::Particle*>& taus) {

          // Delphes 3.3.2 config:
          //   set DeltaR 0.2
          //   set DeltaRTrack 0.2
          //   set TrackPTMin 1.0
          //   set TauPTMin 1.0
          //   set TauEtaMax 2.5
          //   # instructions: {n-prongs} {eff}
          //   # 1 - one prong efficiency
          //   # 2 - two or more efficiency
          //   # -1 - one prong mistag rate
          //   # -2 - two or more mistag rate
          //   set BitNumber 0
          //   # taken from ATL-PHYS-PUB-2015-045 (medium working point)
          //   add EfficiencyFormula {1} {0.70}
          //   add EfficiencyFormula {2} {0.60}
          //   add EfficiencyFormula {-1} {0.02}
          //   add EfficiencyFormula {-2} {0.01}
          // filtereff(taus, 0.65);

          // Distributions from ATL-PHYS-PUB-2015-045, Fig 10
          const static std::vector<double> binedges_pt    = { 0.,  20.,  40.,   60.,   120.,  160.,   220.,   280.,   380.,    500.,  DBL_MAX };
          const static std::vector<double> bineffs_pt_1p  = { 0.,  .54,  .55,   .56,    .58,   .57,    .56,    .54,     .51,     0. };
          const static std::vector<double> bineffs_pt_3p  = { 0.,  .40,  .41,   .42,    .46,   .46,    .43,    .39,     .33,     0. };
          const static HEPUtils::BinnedFn1D<double> _eff_pt_1p(binedges_pt, bineffs_pt_1p);
          const static HEPUtils::BinnedFn1D<double> _eff_pt_3p(binedges_pt, bineffs_pt_3p);
          // 85% 1-prong, 15% >=3-prong
          const static std::vector<double> bineffs_pt_avg = { 0.,  .52,  .53,   .54,    .56,   .55,    .54,    .52,     .48,     0. };
          const static HEPUtils::BinnedFn1D<double> _eff_pt_avg(binedges_pt, bineffs_pt_avg);
          filtereff_pt(taus, _eff_pt_avg);

        }



        inline void applyPhotonEfficiencyR2(std::vector<const HEPUtils::Particle*>& photons) {

          const static std::vector<double> binedges_eta   = { 0., 0.6, 1.37, 1.52, 1.81, 2.37, DBL_MAX };
          const static std::vector<double> binedges_pt    = { 0., 10., 15., 20., 25., 30., 35., 40., 45., 50., 60., 80., 100., 125., 150., 175., 250., DBL_MAX };
          const static std::vector<double> bineffs_etapt  = { 0.00, 0.55, 0.70, 0.85, 0.89, 0.93, 0.95, 0.96, 0.96, 0.97, 0.97, 0.98, 0.97, 0.97, 0.97, 0.97, 0.97, //
                                                              0.00, 0.47, 0.66, 0.79, 0.86, 0.89, 0.94, 0.96, 0.97, 0.97, 0.98, 0.97, 0.98, 0.98, 0.98, 0.98, 0.98, //
                                                              0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, //
                                                              0.00, 0.54, 0.71, 0.84, 0.88, 0.92, 0.93, 0.94, 0.95, 0.96, 0.96, 0.96, 0.96, 0.96, 0.96, 0.96, 0.96, //
                                                              0.00, 0.61, 0.74, 0.83, 0.88, 0.91, 0.94, 0.95, 0.96, 0.97, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, 0.98, //
                                                              0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 };
          const static HEPUtils::BinnedFn2D<double> _eff_etapt(binedges_eta, binedges_pt, bineffs_etapt);
          filtereff_etapt(photons, _eff_etapt);
        }


        /// Randomly smear the supplied electrons' momenta by parameterised resolutions
        inline void smearElectronEnergy(std::vector<HEPUtils::Particle*>& electrons) {
          // Function that mimics the DELPHES electron energy resolution
          // We need to smear E, then recalculate pT, then reset 4 vector

          static HEPUtils::BinnedFn2D<double> coeffE2({{0, 2.5, 3., 5.}}, //< |eta|
                                                      {{0, 0.1, 25., DBL_MAX}}, //< pT
                                                      {{0.,          0.015*0.015, 0.005*0.005,
                                                        0.005*0.005, 0.005*0.005, 0.005*0.005,
                                                        0.107*0.107, 0.107*0.107, 0.107*0.107}});

          static HEPUtils::BinnedFn2D<double> coeffE({{0, 2.5, 3., 5.}}, //< |eta|
                                                     {{0, 0.1, 25., DBL_MAX}}, //< pT
                                                     {{0.,        0.,        0.05*0.05,
                                                       0.05*0.05, 0.05*0.05, 0.05*0.05,
                                                       2.08*2.08, 2.08*2.08, 2.08*2.08}});

          static HEPUtils::BinnedFn2D<double> coeffC({{0, 2.5, 3., 5.}}, //< |eta|
                                                     {{0, 0.1, 25., DBL_MAX}}, //< pT
                                                     {{0.,       0.,       0.25*0.25,
                                                       0.25*0.25,0.25*0.25,0.25*0.25,
                                                       0.,       0.,       0.}});

          // Now loop over the electrons and smear the 4-vectors
          for (HEPUtils::Particle* e : electrons) {
            if (e->abseta() > 5) continue;

            // Look up / calculate resolution
            const double c1 = coeffE2.get_at(e->abseta(), e->pT());
            const double c2 = coeffE.get_at(e->abseta(), e->pT());
            const double c3 = coeffC.get_at(e->abseta(), e->pT());
            const double resolution = sqrt(c1*HEPUtils::sqr(e->E()) + c2*e->E() + c3);

            // Smear by a Gaussian centered on the current energy, with width given by the resolution
            std::normal_distribution<> d(e->E(), resolution);
            double smeared_E = d(Random::rng());
            if (smeared_E < e->mass()) smeared_E = 1.01*e->mass();
            // double smeared_pt = smeared_E/cosh(e->eta()); ///< @todo Should be cosh(|eta|)?
            e->set_mom(HEPUtils::P4::mkEtaPhiME(e->eta(), e->phi(), e->mass(), smeared_E));
          }
        }


        /// Randomly smear the supplied muons' momenta by parameterised resolutions
        inline void smearMuonMomentum(std::vector<HEPUtils::Particle*>& muons) {
          // Function that mimics the DELPHES muon momentum resolution
          // We need to smear pT, then recalculate E, then reset 4 vector

          static HEPUtils::BinnedFn2D<double> _muEff({{0,1.5,2.5}},
                                                     {{0,0.1,1.,10.,200.,DBL_MAX}},
                                                     {{0.,0.03,0.02,0.03,0.05,
                                                       0.,0.04,0.03,0.04,0.05}});

          // Now loop over the muons and smear the 4-vectors
          for (HEPUtils::Particle* mu : muons) {
            if (mu->abseta() > 2.5) continue;

            // Look up resolution
            const double resolution = _muEff.get_at(mu->abseta(), mu->pT());

            // Smear by a Gaussian centered on the current energy, with width given by the resolution
            std::normal_distribution<> d(mu->pT(), resolution*mu->pT());
            double smeared_pt = d(Random::rng());
            if (smeared_pt < 0) smeared_pt = 0;
            // const double smeared_E = smeared_pt*cosh(mu->eta()); ///< @todo Should be cosh(|eta|)?
            // std::cout << "Muon pt " << mu_pt << " smeared " << smeared_pt << endl;
            mu->set_mom(HEPUtils::P4::mkEtaPhiMPt(mu->eta(), mu->phi(), mu->mass(), smeared_pt));
          }
        }


        /// Randomly smear the supplied jets' momenta by parameterised resolutions
        inline void smearJets(std::vector<HEPUtils::Jet*>& jets) {
          // Function that mimics the DELPHES jet momentum resolution.
          // We need to smear pT, then recalculate E, then reset the 4-vector.
          // Const resolution for now
          //const double resolution = 0.03;

          // Matthias jet smearing implemented roughly from
          // https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2015-017/
          // Parameterisation can be still improved, but eta dependence is minimal
          const std::vector<double>  binedges_eta = {0,10.};
          const std::vector<double>  binedges_pt = {0,50.,70.,100.,150.,200.,1000.,10000.};
          const std::vector<double> JetsJER = {0.145,0.115,0.095,0.075,0.07,0.05,0.04};
          static HEPUtils::BinnedFn2D<double> _resJets2D(binedges_eta,binedges_pt,JetsJER);

          // Now loop over the jets and smear the 4-vectors
          for (HEPUtils::Jet* jet : jets) {
            const double resolution = _resJets2D.get_at(jet->abseta(), jet->pT());
            std::normal_distribution<> d(1., resolution);
            // Smear by a Gaussian centered on 1 with width given by the (fractional) resolution
            double smear_factor = d(Random::rng());
            /// @todo Is this the best way to smear? Should we preserve the mean jet energy, or pT, or direction?
            jet->set_mom(HEPUtils::P4::mkXYZM(jet->mom().px()*smear_factor, jet->mom().py()*smear_factor, jet->mom().pz()*smear_factor, jet->mass()));
          }
        }


        /// Randomly smear the MET vector by parameterised resolutions
        inline void smearMET(HEPUtils::P4& pmiss, double set) {
          // Smearing function from ATLAS Run 1 performance paper, converted from Rivet
          // cf. https://arxiv.org/pdf/1108.5602v2.pdf, Figs 14 and 15

          // Linearity offset (Fig 14)
          if (pmiss.pT() < 25) pmiss *= 1.05;
          else if (pmiss.pT() < 40) pmiss *= (1.05 - (0.04/15)*(pmiss.pT() - 25)); //< linear decrease
          else pmiss *= 1.01;

          // Smear by a Gaussian with width given by the resolution(sumEt) ~ 0.45 sqrt(sumEt) GeV
          const double resolution = 0.45 * sqrt(set);
          std::normal_distribution<> d(pmiss.pT(), resolution);
          const double smearedmet = std::max(d(Random::rng()), 0.);

          pmiss *= smearedmet / pmiss.pT();
        }


        /// Randomly smear the supplied taus' momenta by parameterised resolutions
        inline void smearTaus(std::vector<HEPUtils::Particle*>& taus) {
          // We need to smear pT, then recalculate E, then reset the 4-vector.
          // Same as for jets, but on a vector of particles. (?)
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


        /// Efficiency function for Loose ID electrons
        /// @note Numbers digitised from Fig 3 of 13 TeV note (ATL-PHYS-PUB-2015-041)
        /// @todo What about faking by jets or non-electrons?
        inline void applyLooseIDElectronSelectionR2(std::vector<const HEPUtils::Particle*>& electrons) {
          if (electrons.empty()) return;

          // Manually symmetrised eta eff histogram
          const static std::vector<double> binedges_eta = { 0.0,   0.1,   0.8,   1.37,  1.52,  2.01,  2.37,  2.47, DBL_MAX };
          const static std::vector<double> bineffs_eta  = { 0.950, 0.965, 0.955, 0.885, 0.950, 0.935, 0.90, 0 };
          const static HEPUtils::BinnedFn1D<double> _eff_eta(binedges_eta, bineffs_eta);
          // Et eff histogram (10-20 GeV bin added by hand)
          const static std::vector<double> binedges_et = { 10,   20,   25,   30,   35,   40,    45,    50,   60,  80, DBL_MAX };
          const static std::vector<double> bineffs_et  = { 0.90, 0.91, 0.92, 0.94, 0.95, 0.955, 0.965, 0.97, 0.98, 0.98 };
          const static HEPUtils::BinnedFn1D<double> _eff_et(binedges_et, bineffs_et);

          auto keptElectronsEnd = std::remove_if(electrons.begin(), electrons.end(),
                                                 [](const HEPUtils::Particle* electron) {
                                                   const double e_pt = electron->pT();
                                                   const double e_aeta = electron->abseta();
                                                   if (e_aeta > 2.47 || e_pt < 10) return true;
                                                   const double eff1 = _eff_eta.get_at(e_aeta), eff2 = _eff_et.get_at(e_pt);
                                                   const double eff = std::min(eff1 * eff2 / 0.95, 1.0); //< norm factor as approximate double differential
                                                   return random_bool(1-eff);
                                                 } );
          electrons.erase(keptElectronsEnd, electrons.end());
        }

        /// Alias to allow non-const particle vectors
        inline void applyLooseIDElectronSelectionR2(std::vector<HEPUtils::Particle*>& electrons) {
          applyLooseIDElectronSelectionR2(reinterpret_cast<std::vector<const HEPUtils::Particle*>&>(electrons));
        }

        /// Efficiency function for Loose ID electrons
        /// @note Numbers digitised from Fig 3 of 13 TeV note (ATL-PHYS-PUB-2015-041)
        inline void applyMediumIDElectronSelectionR2(std::vector<const HEPUtils::Particle*>& electrons) {
          if (electrons.empty()) return;

          // Manually symmetrised eta eff histogram
          const static std::vector<double> binedges_eta = { 0.0,   0.1,   0.8,   1.37,  1.52,  2.01,  2.37,  2.47, DBL_MAX };
          const static std::vector<double> bineffs_eta  = { 0.900, 0.930, 0.905, 0.830, 0.900, 0.880, 0.85, 0 };
          const static HEPUtils::BinnedFn1D<double> _eff_eta(binedges_eta, bineffs_eta);
          // Et eff histogram (10-20 GeV bin added by hand)
          const static std::vector<double> binedges_et = { 10,   20,   25,   30,   35,   40,    45,    50,   60,  80, DBL_MAX };
          const static std::vector<double> bineffs_et  = { 0.83, 0.845, 0.87, 0.89, 0.90, 0.91, 0.92, 0.93, 0.95, 0.95 };
          const static HEPUtils::BinnedFn1D<double> _eff_et(binedges_et, bineffs_et);

          auto keptElectronsEnd = std::remove_if(electrons.begin(), electrons.end(),
                                                 [](const HEPUtils::Particle* electron) {
                                                   const double e_pt = electron->pT();
                                                   const double e_aeta = electron->abseta();
                                                   if (e_aeta > 2.47 || e_pt < 10) return true;
                                                   const double eff1 = _eff_eta.get_at(e_aeta), eff2 = _eff_et.get_at(e_pt);
                                                   const double eff = std::min(eff1 * eff2 / 0.95, 1.0); //< norm factor as approximate double differential
                                                   return random_bool(1-eff);
                                                 } );
          electrons.erase(keptElectronsEnd, electrons.end());
        }

        /// Alias to allow non-const particle vectors
        inline void applyMediumIDElectronSelectionR2(std::vector<HEPUtils::Particle*>& electrons) {
          applyMediumIDElectronSelectionR2(reinterpret_cast<std::vector<const HEPUtils::Particle*>&>(electrons));
        }

        /// Efficiency function for Medium ID electrons
        /// @note Numbers digitised from 8 TeV note (ATLAS-CONF-2014-032)
        inline void applyMediumIDElectronSelection(std::vector<const HEPUtils::Particle*>& electrons) {
          if (electrons.empty()) return;

          const static std::vector<double> binedges_E10_15 = {0., 0.0494681, 0.453578, 1.10675, 1.46298, 1.78963, 2.2766, 2.5};
          const static std::vector<double> binvalues_E10_15 = makeBinValues({0.730435, 0.730435, 0.782609, 0.776812, 0.765217, 0.773913, 0.77971, 0.776812});
          const static HEPUtils::BinnedFn1D<double> _eff_E10_15(binedges_E10_15, binvalues_E10_15);

          const static std::vector<double> binedges_E15_20 = {0., 0.0533175, 0.456161, 1.1019, 1.46327, 1.78318, 2.26303, 2.5};
          const static std::vector<double> binvalues_E15_20 = makeBinValues({0.77971, 0.77971, 0.82029, 0.817391, 0.701449, 0.797101, 0.828986, 0.828986});
          const static HEPUtils::BinnedFn1D<double> _eff_E15_20(binedges_E15_20, binvalues_E15_20);

          const static std::vector<double> binedges_E20_25 = {-2.5, -2.45249, -2.21496, -1.94181, -1.6924, -1.46675, -1.26485, -0.991686, -0.682898, -0.350356, -0.0415677, 0.0653207, 0.362233, 0.718527, 0.97981, 1.2886, 1.45487, 1.68052, 1.94181, 2.23872, 2.45249, 2.5};
          const static std::vector<double> binvalues_E20_25 = makeBinValues({0.827811, 0.82572, 0.790414, 0.798585, 0.779843, 0.727974, 0.802447, 0.798192, 0.812561, 0.812423, 0.808153, 0.779115, 0.822483, 0.816123, 0.795304, 0.793105, 0.772326, 0.778446, 0.794906, 0.78857, 0.821617, 0.821593});
          const static HEPUtils::BinnedFn1D<double> _eff_E20_25(binedges_E20_25, binvalues_E20_25);

          const static std::vector<double> binedges_E25_30 = {-2.5, -2.45249, -2.22684, -1.92993, -1.6924, -1.46675, -1.26485, -0.97981, -0.694774, -0.33848, -0.0534442, 0.0771971, 0.33848, 0.74228, 1.00356, 1.26485, 1.46675, 1.6924, 1.94181, 2.22684, 2.45249, 2.5};
          const static std::vector<double> binvalues_E25_30 = makeBinValues({0.84095, 0.838892, 0.8286, 0.830801, 0.818436, 0.76037, 0.841463, 0.83535, 0.850008, 0.852233, 0.837812, 0.82748, 0.854592, 0.854759, 0.838251, 0.844591, 0.76782, 0.815688, 0.836563, 0.824219, 0.838853, 0.838877});
          const static HEPUtils::BinnedFn1D<double> _eff_E25_30(binedges_E25_30, binvalues_E25_30);

          const static std::vector<double> binedges_E30_35 = {-2.5, -2.44062, -2.21496, -1.92993, -1.68052, -1.46675, -1.27672, -0.991686, -0.706651, -0.350356, -0.0534442, 0.0771971, 0.350356, 0.706651, 0.97981, 1.2886, 1.47862, 1.68052, 1.94181, 2.23872, 2.44062, 2.5};
          const static std::vector<double> binvalues_E30_35 = makeBinValues({0.849263, 0.849233, 0.840831, 0.853176, 0.844763, 0.771974, 0.873676, 0.865249, 0.877593, 0.883677, 0.869013, 0.856496, 0.879231, 0.883238, 0.870661, 0.870533, 0.779059, 0.839213, 0.84949, 0.834827, 0.834743, 0.834718});
          const static HEPUtils::BinnedFn1D<double> _eff_E30_35(binedges_E30_35, binvalues_E30_35);

          const static std::vector<double> binedges_E35_40 = {-2.5, -2.44841, -2.23431, -1.94914, -1.69969, -1.46336, -1.28359, -0.998664, -0.713488, -0.357087, -0.0723338, 0.0580256, 0.343519, 0.699955, 1.0085, 1.26989, 1.45836, 1.685, 1.93451, 2.23118, 2.46818, 2.5};
          const static std::vector<double> binvalues_E35_40 = makeBinValues({0.836795, 0.84095, 0.859644, 0.867953, 0.87003, 0.799407, 0.894955, 0.888724, 0.897033, 0.903264, 0.886647, 0.87003, 0.897033, 0.905341, 0.890801, 0.897033, 0.805638, 0.863798, 0.87003, 0.85549, 0.824332, 0.826409});
          const static HEPUtils::BinnedFn1D<double> _eff_E35_40(binedges_E35_40, binvalues_E35_40);

          const static std::vector<double> binedges_E40_45 = {-2.5, -2.45261, -2.22749, -1.93128, -1.68246, -1.46919, -1.27962, -0.995261, -0.7109, -0.343602, -0.0592417, 0.0473934, 0.35545, 0.699052, 0.983412, 1.27962, 1.4455, 1.69431, 1.94313, 2.22749, 2.44076, 2.5};
          const static std::vector<double> binvalues_E40_45 = makeBinValues({0.836795, 0.836795, 0.87003, 0.882493, 0.897033, 0.84095, 0.911573, 0.89911, 0.907418, 0.909496, 0.89911, 0.888724, 0.907418, 0.91365, 0.89911, 0.907418, 0.843027, 0.890801, 0.882493, 0.87003, 0.816024, 0.816024});
          const static HEPUtils::BinnedFn1D<double> _eff_E40_45(binedges_E40_45, binvalues_E40_45);

          const static std::vector<double> binedges_E45_50 = {-2.5, -2.46086, -2.22192, -1.93675, -1.68709, -1.46211, -1.27124, -0.986416, -0.689328, -0.356822, -0.0482438, 0.0584337, 0.355838, 0.712203, 0.996992, 1.28217, 1.45947, 1.68576, 1.93499, 2.21988, 2.44378, 2.5};
          const static std::vector<double>  binvalues_E45_50 =  makeBinValues({0.807101, 0.807101, 0.889941, 0.898225, 0.912722, 0.873373, 0.923077, 0.910651, 0.921006, 0.918935, 0.906509, 0.894083, 0.923077, 0.927219, 0.912722, 0.921006, 0.871302, 0.90858, 0.898225, 0.889941, 0.786391, 0.786391});
          const static HEPUtils::BinnedFn1D<double> _eff_E45_50 = {binedges_E45_50, binvalues_E45_50};

          const static std::vector<double> binedges_E50_60 = {-2.5, -2.44076, -2.21564, -1.93128, -1.69431, -1.46919, -1.26777, -0.983412, -0.7109, -0.35545, -0.0592417, 0.0592417, 0.35545, 0.7109, 0.983412, 1.27962, 1.46919, 1.68246, 1.91943, 2.22749, 2.44076, 2.5};
          const static std::vector<double>  binvalues_E50_60 = makeBinValues({0.785417, 0.785417, 0.891667, 0.9, 0.916667, 0.877083, 0.927083, 0.91875, 0.91875, 0.922917, 0.90625, 0.9, 0.922917, 0.929167, 0.920833, 0.925, 0.885417, 0.9125, 0.904167, 0.885417, 0.7625, 0.7625});
          const static HEPUtils::BinnedFn1D<double> _eff_E50_60 = {binedges_E50_60, binvalues_E50_60};

          const static std::vector<double> binedges_E60_80 = {-2.5, -2.44933, -2.22119, -1.9353, -1.68491, -1.47115, -1.2682, -0.982628, -0.696912, -0.351494, -0.0423579, 0.0526683, 0.350856, 0.719871, 1.00552, 1.29137, 1.46938, 1.69596, 1.94572, 2.24305, 2.45479, 2.5};
          const static std::vector<double>  binvalues_E60_80 = makeBinValues({0.779163, 0.779188, 0.893866, 0.904402, 0.927423, 0.896262, 0.92968, 0.921466, 0.921585, 0.932145, 0.909357, 0.896897, 0.930355, 0.928425, 0.924377, 0.93283, 0.899571, 0.922582, 0.908102, 0.89156, 0.741648, 0.741678});
          const static HEPUtils::BinnedFn1D<double> _eff_E60_80 = {binedges_E60_80, binvalues_E60_80};

          const static std::vector<double> binedges_E80 = {-2.5, -2.45835, -2.22058, -1.94663, -1.68451, -1.44712, -1.27961, -0.970161, -0.708258, -0.351259, -0.0537477, 0.0532884, 0.351188, 0.72041, 0.994111, 1.29176, 1.4815, 1.70839, 1.93419, 2.21998, 2.45825, 2.5};
          const static std::vector<double>  binvalues_E80 = makeBinValues({0.951041, 0.948944, 0.930151, 0.938346, 0.9507, 0.909058, 0.95884, 0.954557, 0.954449, 0.945992, 0.939637, 0.933361, 0.949854, 0.960086, 0.953741, 0.955695, 0.911996, 0.953445, 0.930502, 0.934538, 0.944824, 0.9448});
          const static HEPUtils::BinnedFn1D<double> _eff_E80 = {binedges_E80, binvalues_E80};

          // Now loop over the electrons and only keep those that pass the random efficiency cut
          /// @note No delete is necessary, because this should only ever be applied to a copy of the Event Particle* vectors
          /// @todo This is an exact duplication of the below filtering code -- split into a single util fn (in unnamed namespace?) when binned fns are static
          auto keptElectronsEnd = std::remove_if(electrons.begin(), electrons.end(),
                                             [](const HEPUtils::Particle* electron) {
                                               const double e_pt = electron->pT();
                                               const double e_eta = electron->eta();
                                               if (!(fabs(e_eta) < 2.5 && e_pt >= 10)) return true;
                                               else if (HEPUtils::in_range(e_pt, 10, 15)) return !random_bool(_eff_E10_15, fabs(e_eta));
                                               else if (HEPUtils::in_range(e_pt, 15, 20)) return !random_bool(_eff_E15_20, fabs(e_eta));
                                               else if (HEPUtils::in_range(e_pt, 20, 25)) return !random_bool(_eff_E20_25, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 25, 30)) return !random_bool(_eff_E25_30, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 30, 35)) return !random_bool(_eff_E30_35, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 35, 40)) return !random_bool(_eff_E35_40, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 40, 45)) return !random_bool(_eff_E40_45, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 45, 50)) return !random_bool(_eff_E45_50, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 50, 60)) return !random_bool(_eff_E50_60, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 60, 80)) return !random_bool(_eff_E60_80, e_eta);
                                               else return !random_bool(_eff_E80, e_eta);
                                             } );
          electrons.erase(keptElectronsEnd, electrons.end());
        }


        /// Alias to allow non-const particle vectors
        inline void applyMediumIDElectronSelection(std::vector<HEPUtils::Particle*>& electrons) {
          applyMediumIDElectronSelection(reinterpret_cast<std::vector<const HEPUtils::Particle*>&>(electrons));
        }


        /// Efficiency function for Tight ID electrons
        /// @note Numbers digitised from 8 TeV note (ATLAS-CONF-2014-032)
        inline void applyTightIDElectronSelection(std::vector<const HEPUtils::Particle*>& electrons) {

          const static std::vector<double> binedges_E10_15 = {0., 0.0485903, 0.458914, 1.10009, 1.46117, 1.78881, 2.27013, 2.5};
          const static std::vector<double> binvalues_E10_15 = makeBinValues({0.57971, 0.582609, 0.681159, 0.655072, 0.46087, 0.634783, 0.689855, 0.689855});
          const static HEPUtils::BinnedFn1D<double> _eff_E10_15(binedges_E10_15, binvalues_E10_15);

          const static std::vector<double> binedges_E15_20 = {0., 0.0533175, 0.450237, 1.09597, 1.46327, 1.78318, 2.26896, 2.5};
          const static std::vector<double> binvalues_E15_20 = makeBinValues({0.631884, 0.628986, 0.727536, 0.701449, 0.565217, 0.666667, 0.733333, 0.733333});
          const static HEPUtils::BinnedFn1D<double> _eff_E15_20(binedges_E15_20, binvalues_E15_20);

          const static std::vector<double> binedges_E20_25 =  {-2.5, -2.44062, -2.22684, -1.92993, -1.66865, -1.45487, -1.26485, -0.967933, -0.706651, -0.350356, -0.0415677, 0.0653207, 0.362233, 0.718527, 0.991686, 1.27672, 1.47862, 1.6924, 1.92993, 2.22684, 2.46437, 2.5};
          const static std::vector<double> binvalues_E20_25 = makeBinValues({0.678698, 0.678674, 0.70965, 0.65361, 0.655573, 0.599567, 0.6844, 0.694632, 0.729731, 0.731654, 0.665254, 0.640358, 0.743785, 0.733282, 0.697962, 0.672992, 0.585926, 0.660394, 0.652011, 0.703663, 0.670429, 0.668338});
          const static HEPUtils::BinnedFn1D<double> _eff_E20_25(binedges_E20_25, binvalues_E20_25);

          const static std::vector<double> binedges_E25_30 = {-2.5, -2.44062, -2.22684, -1.91805, -1.68052, -1.45487, -1.27672, -0.97981, -0.706651, -0.350356, -0.0415677, 0.0771971, 0.362233, 0.718527, 0.991686, 1.30048, 1.47862, 1.6924, 1.94181, 2.22684, 2.46437, 2.5};
          const static std::vector<double> binvalues_E25_30 = makeBinValues({0.678932, 0.681034, 0.737205, 0.683328, 0.695889, 0.633669, 0.720983, 0.733569, 0.758609, 0.769142, 0.69657, 0.688311, 0.771515, 0.771663, 0.734388, 0.717899, 0.636964, 0.699368, 0.689086, 0.730747, 0.67684, 0.67686});
          const static HEPUtils::BinnedFn1D<double> _eff_E25_30(binedges_E25_30, binvalues_E25_30);

          const static std::vector<double> binedges_E30_35 = {-2.5, -2.45249, -2.21496, -1.94181, -1.68052, -1.47862, -1.27672, -0.97981, -0.706651, -0.33848, -0.0415677, 0.0534442, 0.362233, 0.718527, 1.00356, 1.27672, 1.46675, 1.68052, 1.95368, 2.23872, 2.45249, 2.5};
          const static std::vector<double> binvalues_E30_35 = makeBinValues({0.691395, 0.691375, 0.749436, 0.716089, 0.726366, 0.653582, 0.749047, 0.771772, 0.800739, 0.802663, 0.731916, 0.71526, 0.802372, 0.810532, 0.773025, 0.75214, 0.656512, 0.722892, 0.712393, 0.745509, 0.670643, 0.6727});
          const static HEPUtils::BinnedFn1D<double> _eff_E30_35(binedges_E30_35, binvalues_E30_35);

          const static std::vector<double> binedges_E35_40 = {-2.5, -2.46296, -2.22413, -1.93966, -1.7017, -1.47721, -1.28567, -0.988409, -0.714721, -0.334744, -0.0510125, 0.0437527, 0.342215, 0.710598, 0.971211, 1.27968, 1.45638, 1.68306, 1.94399, 2.21764, 2.44185, 2.5};
          const static std::vector<double> binvalues_E35_40 = makeBinValues({0.683086, 0.683086, 0.759941, 0.726706, 0.751632, 0.683086, 0.772404, 0.793175, 0.824332, 0.820178, 0.743323, 0.728783, 0.820178, 0.832641, 0.793175, 0.774481, 0.689318, 0.749555, 0.728783, 0.757864, 0.6727, 0.6727});
          const static HEPUtils::BinnedFn1D<double> _eff_E35_40(binedges_E35_40, binvalues_E35_40);

          const static std::vector<double> binedges_E40_45 = {-2.5, -2.45261, -2.21564, -1.94313, -1.69431, -1.45735, -1.27962, -0.983412, -0.7109, -0.35545, -0.0592417, 0.0473934, 0.35545, 0.699052, 0.983412, 1.26777, 1.45735, 1.67062, 1.93128, 2.20379, 2.45261, 2.5};
          const static std::vector<double> binvalues_E40_45 = makeBinValues({0.693472, 0.693472, 0.782789, 0.757864, 0.784866, 0.726706, 0.797329, 0.803561, 0.836795, 0.805638, 0.747478, 0.735015, 0.805638, 0.843027, 0.807715, 0.797329, 0.732938, 0.780712, 0.762018, 0.782789, 0.674777, 0.674777});
          const static HEPUtils::BinnedFn1D<double> _eff_E40_45(binedges_E40_45, binvalues_E40_45);

          const static std::vector<double> binedges_E45_50 = {-2.5, -2.46311, -2.22329, -1.93875, -1.70073, -1.47585, -1.273, -0.976015, -0.714205, -0.358403, -0.0625448, 0.0560444, 0.354151, 0.711078, 0.98364, 1.28045, 1.45768, 1.68407, 1.94493, 2.20653, 2.4415, 2.5};
          const static std::vector<double>  binvalues_E45_50 =  makeBinValues({0.674556, 0.674556, 0.809172, 0.780178, 0.809172, 0.763609, 0.819527, 0.823669, 0.854734, 0.82574, 0.763609, 0.753254, 0.823669, 0.860947, 0.82574, 0.819527, 0.76568, 0.809172, 0.78432, 0.802959, 0.651775, 0.651775});
          const static HEPUtils::BinnedFn1D<double> _eff_E45_50 = {binedges_E45_50, binvalues_E45_50};

          const static std::vector<double> binedges_E50_60 = {-2.5, -2.45261, -2.21564, -1.93128, -1.68246, -1.45735, -1.27962, -0.995261, -0.699052, -0.343602, -0.0592417, 0.0592417, 0.35545, 0.699052, 0.983412, 1.26777, 1.4455, 1.68246, 1.94313, 2.21564, 2.45261, 2.5};
          const static std::vector<double>  binvalues_E50_60 = makeBinValues({0.6625, 0.6625, 0.810417, 0.795833, 0.81875, 0.779167, 0.839583, 0.84375, 0.860417, 0.841667, 0.777083, 0.764583, 0.841667, 0.877083, 0.85, 0.839583, 0.785417, 0.816667, 0.8, 0.804167, 0.64375, 0.64375});
          const static HEPUtils::BinnedFn1D<double> _eff_E50_60 = {binedges_E50_60, binvalues_E50_60};

          const static std::vector<double> binedges_E60_80 = {-2.5, -2.46326, -2.22265, -1.93711, -1.69844, -1.47299, -1.28152, -0.995631, -0.709702, -0.364674, -0.0564949, 0.0504716, 0.349652, 0.707116, 0.980538, 1.27812, 1.46757, 1.69447, 1.94394, 2.24157, 2.45288, 2.5};
          const static std::vector<double>  binvalues_E60_80 = makeBinValues({0.660412, 0.660432, 0.808449, 0.798151, 0.831584, 0.787928, 0.846341, 0.856877, 0.869496, 0.85714, 0.778101, 0.767729, 0.859521, 0.87842, 0.855617, 0.853658, 0.79332, 0.835081, 0.803935, 0.804059, 0.629147, 0.629172});
          const static HEPUtils::BinnedFn1D<double> _eff_E60_80 = {binedges_E60_80, binvalues_E60_80};

          const static std::vector<double> binedges_E80 = {-2.5, -2.45987, -2.22149, -1.94797, -1.69748, -1.47206, -1.29251, -0.994818, -0.709105, -0.352212, -0.0558319, 0.0513809, 0.374044, 0.719562, 0.981359, 1.27873, 1.46843, 1.70723, 1.9449, 2.20712, 2.45676, 2.5};
          const static std::vector<double>  binvalues_E80 = makeBinValues({0.859652, 0.859627, 0.876145, 0.859415, 0.888391, 0.8426, 0.900685, 0.904716, 0.904597, 0.889909, 0.817086, 0.821195, 0.893762, 0.910235, 0.903895, 0.889231, 0.843455, 0.884899, 0.859875, 0.87846, 0.857585, 0.85756});
          const static HEPUtils::BinnedFn1D<double> _eff_E80 = {binedges_E80, binvalues_E80};

          // Now loop over the electrons and only keep those that pass the random efficiency cut
          /// @note No delete is necessary, because this should only ever be applied to a copy of the Event Particle* vectors
          /// @todo This is an exact duplication of the above filtering code -- split into a single util fn (in unnamed namespace?) when binned fns are static
          auto keptElectronsEnd = std::remove_if(electrons.begin(), electrons.end(),
                                             [](const HEPUtils::Particle* electron) {
                                               const double e_pt = electron->pT();
                                               const double e_eta = electron->eta();
                                               if (!(fabs(e_eta) < 2.5 && e_pt >= 10)) return true;
                                               else if (HEPUtils::in_range(e_pt, 10, 15)) return !random_bool(_eff_E10_15, fabs(e_eta));
                                               else if (HEPUtils::in_range(e_pt, 15, 20)) return !random_bool(_eff_E15_20, fabs(e_eta));
                                               else if (HEPUtils::in_range(e_pt, 20, 25)) return !random_bool(_eff_E20_25, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 25, 30)) return !random_bool(_eff_E25_30, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 30, 35)) return !random_bool(_eff_E30_35, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 35, 40)) return !random_bool(_eff_E35_40, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 40, 45)) return !random_bool(_eff_E40_45, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 45, 50)) return !random_bool(_eff_E45_50, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 50, 60)) return !random_bool(_eff_E50_60, e_eta);
                                               else if (HEPUtils::in_range(e_pt, 60, 80)) return !random_bool(_eff_E60_80, e_eta);
                                               else return !random_bool(_eff_E80, e_eta);
                                             } );
          electrons.erase(keptElectronsEnd, electrons.end());
        }


        /// Alias to allow non-const particle vectors
        inline void applyTightIDElectronSelection(std::vector<HEPUtils::Particle*>& electrons) {
          applyTightIDElectronSelection(reinterpret_cast<std::vector<const HEPUtils::Particle*>&>(electrons));
        }


        /// Electron 2019 ID efficiency functions from https://arxiv.org/pdf/1902.04655.pdf
        /// @note These efficiencies are 1D efficiencies so only pT is used
        inline void applyElectronIDEfficiency2019(std::vector<const HEPUtils::Particle*>& electrons, str operating_point)
        {

          // digitised from Fig 8
          const static std::vector<double> binedges_pt  = { 0.0, 6.668795911849248, 9.673354432217419, 14.643593391597225, 19.57318312476409, 24.71356813100665, 29.655352632037403, 34.594233616910074, 39.73636073284749, 44.68221015649952, 49.6292209866148, 59.52440405330856, 79.51859702099242, DBL_MAX};
          const static std::vector<double> bineffs_pt_loose  = { 0.9054376657824932, 0.9267904509283819, 0.8757294429708221, 0.8450928381962863, 0.8775862068965516, 0.889655172413793, 0.9035809018567638, 0.9193633952254641, 0.929575596816976, 0.9370026525198938, 0.942572944297082, 0.9509283819628646, 0.9592838196286471};
          const static std::vector<double> bineffs_pt_medium  = { 0.7355437665782492, 0.7912466843501325, 0.7986737400530503, 0.7717506631299733, 0.8135278514588858, 0.8348806366047744, 0.8525198938992041, 0.8692307692307691, 0.8822281167108752, 0.889655172413793, 0.902652519893899, 0.9230769230769229, 0.9407161803713526 };
          const static std::vector<double> bineffs_pt_tight  = { 0.5572944297082227, 0.6213527851458884, 0.6547745358090185, 0.6714854111405835, 0.699336870026525, 0.7299734748010609, 0.7559681697612731, 0.7754641909814322, 0.7921750663129972, 0.8079575596816975, 0.8311671087533155, 0.8710875331564986, 0.8989389920424402 };

          // select operating point
          std::vector<double> bineffs_pt;
          if (operating_point == "Loose" or operating_point == "VeryLoose")
            bineffs_pt = bineffs_pt_loose;
          else if (operating_point == "Medium")
            bineffs_pt = bineffs_pt_medium;
          else if (operating_point == "Tight")
            bineffs_pt = bineffs_pt_tight;
          else
            utils_error().raise(LOCAL_INFO, "Unknown operating point");
          const static HEPUtils::BinnedFn1D<double> _eff_pt(binedges_pt, bineffs_pt);

          // filter electrons
          filtereff_pt(electrons, _eff_pt);

        }

        /// Electron 2019 Isolation efficiency functions from https://arxiv.org/pdf/1902.04655.pdf
        /// @note These efficiencies are 1D efficiencies so only pT is used
        inline void applyElectronIsolationEfficiency2019(std::vector<const HEPUtils::Particle*>& electrons, str operating_point)
        {

          // digitised from Fig 12
          const static std::vector<double> binedges_pt = {0.0, 6.548307897301772, 9.706735099256047, 19.611982283197417, 24.561829913760132, 29.71154676569653, 34.461525174885566, 39.61370954807349, 44.56047277707178, 49.5109372879474, 59.60803424919497, 79.4086585320716, DBL_MAX};
          const static std::vector<double> bineffs_pt_loose_trackonly = {0.9694027334287603, 0.9841898810834618, 0.9915715839022242, 0.9890807366218896, 0.9875756991852016, 0.9875509249064084, 0.9875261506276152, 0.9879947974014535, 0.9884634441752919, 0.9884386698964986, 0.9888959617925568, 0.9907953231667035, 0.9930404921823388};
          const static std::vector<double> bineffs_pt_loose = {0.9595332801145123, 0.9812303870292888, 0.9891055109006828, 0.9875994412023784, 0.9856020149746753, 0.9826167143800926, 0.9820985190486677, 0.9820737447698745, 0.9820489704910813, 0.9825186495265361, 0.9829749091609778, 0.9903008698524555, 0.9930394599207224};
          const static std::vector<double> bineffs_pt_gradient_loose = {0.8973632597445498, 0.9471843343977098, 0.9693676365338032, 0.9466465260955738, 0.947115172869412, 0.9485706617485136, 0.9539735190486678, 0.9593784408720547, 0.9642868448579609, 0.9706755120017618, 0.9780417308962784, 0.9843808494824929, 0.9851457553402335};
          const static std::vector<double> bineffs_pt_gradient = {0.8425935229024444, 0.9082030389781987, 0.944204195111209, 0.9007573359392205, 0.9081359419731337, 0.9145235768553183, 0.924368255890773, 0.9351987447698745, 0.9460292336489761, 0.9573531435807092, 0.9716251926888351, 0.9838874284298613, 0.9851457553402335};

          // select operating point
          std::vector<double> bineffs_pt;
          if (operating_point == "LooseTrackOnly")
            bineffs_pt = bineffs_pt_loose_trackonly;
          if (operating_point == "Loose")
            bineffs_pt = bineffs_pt_loose;
          else if (operating_point == "GradientLoose")
            bineffs_pt = bineffs_pt_gradient_loose;
          else if (operating_point == "Gradient")
            bineffs_pt = bineffs_pt_gradient;
          else
           utils_error().raise(LOCAL_INFO, "Unknown operating point");
          const static HEPUtils::BinnedFn1D<double> _eff_pt(binedges_pt, bineffs_pt);

          // filter electrons
          filtereff_pt(electrons, _eff_pt);
        }


        ///@}

      }
   }
}
