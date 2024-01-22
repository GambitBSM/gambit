#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <sstream>
#include <cassert>

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"

/*
  A simulation of CMS paper PAS SUS-13-006, http://cds.cern.ch/record/1563142/files/SUS-13-006-pas.pdf

  Original code by Martin White, Daniel Murnane,
  Revised version by Anders Kvellestad.

  Known features:
    a) Must run with a dedicated detector card due to odd b tagging and isolation

    Anders: Not sure if this comment still applies?

  Missing:
    Implement SRs for the 2lep2jet final states


  NOTE:
  To protect against copy/paste mistakes and other inconsistencies when
  the results are used both in the base and the derived analysis classes below,
  we first define some macros that will be used in the collect_results()
  functions in the classes below.
*/


//
// SR group 1
//
#define ADD_RESULTS_SRGROUP_1 \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss50-100_mll<75"), 138., {132., 19.}));          \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss50-100_mll75-105"), 821., {776., 125.}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss50-100_mll>105"), 49., {45., 7.}));           \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss100-150_mll<75"), 16., {20., 4.}));           \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss100-150_mll75-105"), 123., {131., 30.}));  \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss100-150_mll>105"), 10., {10.0, 1.9}));       \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss150-200_mll<75"), 5., {4.0, 0.8}));           \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss150-200_mll75-105"), 34., {34., 8.}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss150-200_mll>105"), 4., {2.5, 0.5}));         \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss200-250_mll<75"), 2., {1.9, 0.4}));           \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss200-250_mll75-105"), 14., {21., 7.}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT<120_ETmiss200-250_mll>105"), 4., {1.2, 0.3}));         \
  \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss50-100_mll<75"), 8., {9.6, 1.7}));           \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss50-100_mll75-105"), 29., {23., 5.}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss50-100_mll>105"), 4., {2.7, 0.5}));         \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss100-150_mll<75"), 2., {3.3, 0.8}));         \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss100-150_mll75-105"), 4., {3.4, 0.7}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss100-150_mll>105"), 2., {0.71, 0.22}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss150-200_mll<75"), 0., {0.26, 0.10}));       \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss150-200_mll75-105"), 1., {0.72, 0.19})); \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss150-200_mll>105"), 0., {0.38, 0.14}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss200-250_mll<75"), 0., {0.29, 0.11}));       \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss200-250_mll75-105"), 1., {0.36, 0.12})); \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT120-160_ETmiss200-250_mll>105"), 0., {0.24, 0.20}));     \
  \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss50-100_mll<75"), 12., {5.8, 1.1}));         \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss50-100_mll75-105"), 13., {7.5, 1.4}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss50-100_mll>105"), 1., {2.6, 1.2}));        \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss100-150_mll<75"), 3., {4.5, 1.1}));        \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss100-150_mll75-105"), 8., {4.0, 1.0}));  \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss100-150_mll>105"), 3., {1.8, 0.9}));      \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss150-200_mll<75"), 2., {1.5, 0.4}));        \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss150-200_mll75-105"), 3., {1.5, 0.5}));  \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss150-200_mll>105"), 0., {0.7, 0.4}));      \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss200-250_mll<75"), 0., {0.81, 0.21}));      \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss200-250_mll75-105"), 2., {1.1, 0.4}));  \
  add_result(SignalRegionData(_counters.at("SR3l_OSSF_mT>160_ETmiss200-250_mll>105"), 0., {0.40, 0.24}));    \


//
// SR group 2
//
#define ADD_RESULTS_SRGROUP_2 \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss50-100_mll<100"), 29., { 32., 7.}));      \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss50-100_mll>100"), 1., {1.7, 0.4}));       \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss100-150_mll<100"), 5., {7.3, 1.7}));     \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss100-150_mll>100"), 0., {0.30, 0.11}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss150-200_mll<100"), 1., {1.0, 0.3}));     \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss150-200_mll>100"), 0., {0.14, 0.09}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss200-250_mll<100"), 0., {0.53, 0.24}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT<120_ETmiss200-250_mll>100"), 0., {0.03, 0.03}));   \
  \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss50-100_mll<100"), 3., {5.5, 1.2}));       \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss50-100_mll>100"), 1., {0.25, 0.07}));     \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss100-150_mll<100"), 1., {1.9, 0.5}));     \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss100-150_mll>100"), 0., {0.19, 0.10}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss150-200_mll<100"), 1., {0.46, 0.18}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss150-200_mll>100"), 0., {0.03, 0.03}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss200-250_mll<100"), 0., {0.10, 0.05}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT120-160_ETmiss200-250_mll>100"), 0., {0.008, 0.010})); \
  \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss50-100_mll<100"), 2., {3.2, 0.8}));       \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss50-100_mll>100"), 0., {0.44, 0.33}));     \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss100-150_mll<100"), 3., {2.1, 0.7}));     \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss100-150_mll>100"), 0., {0.42, 0.19}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss150-200_mll<100"), 0., {0.59, 0.18}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss150-200_mll>100"), 0., {0.10, 0.06}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss200-250_mll<100"), 1., {0.37, 0.13}));   \
  add_result(SignalRegionData(_counters.at("SR3l_noOSSF_mT>160_ETmiss200-250_mll>100"), 0., {0.16, 0.14}));   \


//
// SR group 3
//
#define ADD_RESULTS_SRGROUP_3 \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss50-100_mll<100"), 46., {51., 8.}));       \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss50-100_mll>100"), 3., {2.8, 0.6}));       \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss100-150_mll<100"), 1., {6.0, 1.3}));     \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss100-150_mll>100"), 0., {0.50, 0.14}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss150-200_mll<100"), 0., {2.0, 0.4}));     \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss150-200_mll>100"), 0., {0.11, 0.07}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss200-250_mll<100"), 0., {0.90, 0.24}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT<120_ETmiss200-250_mll>100"), 0., {0.042, 0.021})); \
  \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss50-100_mll<100"), 6., {5.5, 1.0}));       \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss50-100_mll>100"), 1., {0.35, 0.13}));     \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss100-150_mll<100"), 2., {0.91, 0.26}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss100-150_mll>100"), 0., {0.06, 0.05}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss150-200_mll<100"), 0., {0.15, 0.10}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss150-200_mll>100"), 0., {0., 0.008}));    \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss200-250_mll<100"), 0., {0.06, 0.08}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT120-160_ETmiss200-250_mll>100"), 0., {0.011, 0.012})); \
  \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss50-100_mll<100"), 2., {3.1, 0.6}));       \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss50-100_mll>100"), 1., {0.50, 0.21}));     \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss100-150_mll<100"), 1., {2.3, 0.5}));     \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss100-150_mll>100"), 1., {0.40, 0.17}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss150-200_mll<100"), 0., {0.52, 0.16}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss150-200_mll>100"), 0., {0.21, 0.11}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss200-250_mll<100"), 2., {0.41, 0.12}));   \
  add_result(SignalRegionData(_counters.at("SR3l_SS1tau_mT>160_ETmiss200-250_mll>100"), 0., {0.06, 0.05}));   \


//
// SR group 4
//
#define ADD_RESULTS_SRGROUP_4 \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss50-100_mll<100"), 290., {259., 93.}));  \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss50-100_mll>100"), 27., {30., 13.}));    \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss100-150_mll<100"), 62., {60., 25.}));  \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss100-150_mll>100"), 8., {5.9, 2.6}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss150-200_mll<100"), 10., {11., 5.}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss150-200_mll>100"), 0., {2.3, 1.4}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss200-250_mll<100"), 2., {2.9, 1.4}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT<120_ETmiss200-250_mll>100"), 0., {1.1, 0.6}));   \
  \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss50-100_mll<100"), 41., {42., 16.}));    \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss50-100_mll>100"), 7., {8.3, 2.9}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss100-150_mll<100"), 18., {17., 9.}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss100-150_mll>100"), 4., {2.3, 1.3}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss150-200_mll<100"), 2., {2.0, 1.2}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss150-200_mll>100"), 0., {0.27, 0.32})); \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss200-250_mll<100"), 1., {0.8, 0.5}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT120-160_ETmiss200-250_mll>100"), 0., {0.5, 0.4}));   \
  \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss50-100_mll<100"), 19., {15., 8.}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss50-100_mll>100"), 2., {5.7, 2.3}));     \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss100-150_mll<100"), 14., {14., 9.}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss100-150_mll>100"), 3., {4.0, 2.2}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss150-200_mll<100"), 1., {3.7, 2.1}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss150-200_mll>100"), 3., {1.3, 1.0}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss200-250_mll<100"), 2., {1.5, 1.0}));   \
  add_result(SignalRegionData(_counters.at("SR3l_OS1tau_mT>160_ETmiss200-250_mll>100"), 1., {0.7, 0.4}));   \


//
// SR group 5
//
#define ADD_RESULTS_SRGROUP_5 \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF0tau_ETmiss<30"), 1., {2.3, 0.6}));       \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF0tau_ETmiss30-50"), 3., {1.2, 0.3}));   \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF0tau_ETmiss50-100"), 2., {1.5, 0.4})); \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF0tau_ETmiss>100"), 2., {0.8, 0.3}));     \
  \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF1tau_ETmiss<30"), 33., {25., 12.}));      \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF1tau_ETmiss30-50"), 11., {11., 3.1}));  \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF1tau_ETmiss50-100"), 9., {9.3, 1.9})); \
  add_result(SignalRegionData(_counters.at("SR4l_1OSSF1tau_ETmiss>100"), 2., {2.9, 0.6}));     \
  \
  add_result(SignalRegionData(_counters.at("SR4l_2OSSF0tau_ETmiss<30"), 142., {149., 46.}));    \
  add_result(SignalRegionData(_counters.at("SR4l_2OSSF0tau_ETmiss30-50"), 25., {28., 11.}));  \
  add_result(SignalRegionData(_counters.at("SR4l_2OSSF0tau_ETmiss50-100"), 4., {4.5, 2.7})); \
  add_result(SignalRegionData(_counters.at("SR4l_2OSSF0tau_ETmiss>100"), 1., {0.8, 0.3}));     \




namespace Gambit {
  namespace ColliderBit {

    using namespace std;

    // This analysis class is a base class for the following SR-specific
    // analysis classes defined further down:
    // - Analysis_CMS_8TeV_MultiLEP_3Lep_20invfb
    // - Analysis_CMS_8TeV_MultiLEP_4Lep_20invfb
    class Analysis_CMS_8TeV_MultiLEP_20invfb : public Analysis {

    protected:


    private:

      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


      // Jet lepton overlap removal
      // Discards jets if they are within DeltaRMax of a lepton
      void JetLeptonOverlapRemoval(vector<const HEPUtils::Jet*>& jets, vector<const HEPUtils::Particle*>& leptons, double DeltaRMax)
      {
        vector<const HEPUtils::Jet*> survivors;
        for(const HEPUtils::Jet* jet : jets)
        {
          bool overlap = false;
          for(const HEPUtils::Particle* lepton : leptons)
          {
            double dR = jet->mom().deltaR_eta(lepton->mom());
            if(fabs(dR) <= DeltaRMax) overlap = true;
          }
          if(!overlap) survivors.push_back(jet);
        }
        jets = survivors;
        return;
      }


      // Identify the particle pair with invariant mass closest to a given value
      vector<const HEPUtils::Particle*> getClosestMllPair(vector<vector<const HEPUtils::Particle*>> pairs, double mll_compare) {

        assert(pairs.size()>0);

        vector<const HEPUtils::Particle*> pair = pairs.at(0);
        double mll = (pair.at(0)->mom() + pair.at(1)->mom()).m();

        if (pairs.size() > 1) {
          for (vector<const HEPUtils::Particle*> pair_tmp : pairs)
          {
            double mll_tmp = (pair_tmp.at(0)->mom() + pair_tmp.at(1)->mom()).m();
            if (fabs(mll_compare - mll_tmp) < fabs(mll_compare - mll)) {
              pair = pair_tmp;
              mll = mll_tmp;
            }
          }
        }
        return pair;
      }


      // Identify the lepton that is *not* part of the pair
      const HEPUtils::Particle* getLeptonNotInPair(vector<const HEPUtils::Particle*> leptons, vector<const HEPUtils::Particle*> pair) {

        // Check that there is only one more element in 'leptons' than in 'pair'
        // FIXME: This does not work if the pair is made with a tau and one of the light leptons
        //assert(leptons.size() == pair.size()+1);

        const HEPUtils::Particle* lepton = NULL;

        for (const HEPUtils::Particle* l : leptons) {
          // If l is not in pair, we're done
          if (find(pair.begin(), pair.end(), l) == pair.end()) {
            lepton = l;
            break;
          }
        }
        // The lepton pointer should never be NULL at this point...
        assert(lepton);
        return lepton;
      }


      // Calculate transverse mass
      double transverseMass(double ETmiss, double pTmissPhi, double lepPt, double lepPhi) {
        return sqrt(2. * ETmiss * lepPt * (1. - cos(lepPhi - pTmissPhi)));
      }


    public:

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_8TeV_MultiLEP_20invfb()
      {

        // Counters for the number of accepted events for each signal region
        // SRs in Table 1
        _counters["SR3l_OSSF_mT<120_ETmiss50-100_mll<75"] = EventCounter("SR3l_OSSF_mT<120_ETmiss50-100_mll<75");
        _counters["SR3l_OSSF_mT<120_ETmiss50-100_mll75-105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss50-100_mll75-105");
        _counters["SR3l_OSSF_mT<120_ETmiss50-100_mll>105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss50-100_mll>105");
        _counters["SR3l_OSSF_mT<120_ETmiss100-150_mll<75"] = EventCounter("SR3l_OSSF_mT<120_ETmiss100-150_mll<75");
        _counters["SR3l_OSSF_mT<120_ETmiss100-150_mll75-105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss100-150_mll75-105");
        _counters["SR3l_OSSF_mT<120_ETmiss100-150_mll>105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss100-150_mll>105");
        _counters["SR3l_OSSF_mT<120_ETmiss150-200_mll<75"] = EventCounter("SR3l_OSSF_mT<120_ETmiss150-200_mll<75");
        _counters["SR3l_OSSF_mT<120_ETmiss150-200_mll75-105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss150-200_mll75-105");
        _counters["SR3l_OSSF_mT<120_ETmiss150-200_mll>105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss150-200_mll>105");
        _counters["SR3l_OSSF_mT<120_ETmiss200-250_mll<75"] = EventCounter("SR3l_OSSF_mT<120_ETmiss200-250_mll<75");
        _counters["SR3l_OSSF_mT<120_ETmiss200-250_mll75-105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss200-250_mll75-105");
        _counters["SR3l_OSSF_mT<120_ETmiss200-250_mll>105"] = EventCounter("SR3l_OSSF_mT<120_ETmiss200-250_mll>105");

        _counters["SR3l_OSSF_mT120-160_ETmiss50-100_mll<75"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss50-100_mll<75");
        _counters["SR3l_OSSF_mT120-160_ETmiss50-100_mll75-105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss50-100_mll75-105");
        _counters["SR3l_OSSF_mT120-160_ETmiss50-100_mll>105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss50-100_mll>105");
        _counters["SR3l_OSSF_mT120-160_ETmiss100-150_mll<75"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss100-150_mll<75");
        _counters["SR3l_OSSF_mT120-160_ETmiss100-150_mll75-105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss100-150_mll75-105");
        _counters["SR3l_OSSF_mT120-160_ETmiss100-150_mll>105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss100-150_mll>105");
        _counters["SR3l_OSSF_mT120-160_ETmiss150-200_mll<75"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss150-200_mll<75");
        _counters["SR3l_OSSF_mT120-160_ETmiss150-200_mll75-105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss150-200_mll75-105");
        _counters["SR3l_OSSF_mT120-160_ETmiss150-200_mll>105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss150-200_mll>105");
        _counters["SR3l_OSSF_mT120-160_ETmiss200-250_mll<75"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss200-250_mll<75");
        _counters["SR3l_OSSF_mT120-160_ETmiss200-250_mll75-105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss200-250_mll75-105");
        _counters["SR3l_OSSF_mT120-160_ETmiss200-250_mll>105"] = EventCounter("SR3l_OSSF_mT120-160_ETmiss200-250_mll>105");

        _counters["SR3l_OSSF_mT>160_ETmiss50-100_mll<75"] = EventCounter("SR3l_OSSF_mT>160_ETmiss50-100_mll<75");
        _counters["SR3l_OSSF_mT>160_ETmiss50-100_mll75-105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss50-100_mll75-105");
        _counters["SR3l_OSSF_mT>160_ETmiss50-100_mll>105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss50-100_mll>105");
        _counters["SR3l_OSSF_mT>160_ETmiss100-150_mll<75"] = EventCounter("SR3l_OSSF_mT>160_ETmiss100-150_mll<75");
        _counters["SR3l_OSSF_mT>160_ETmiss100-150_mll75-105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss100-150_mll75-105");
        _counters["SR3l_OSSF_mT>160_ETmiss100-150_mll>105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss100-150_mll>105");
        _counters["SR3l_OSSF_mT>160_ETmiss150-200_mll<75"] = EventCounter("SR3l_OSSF_mT>160_ETmiss150-200_mll<75");
        _counters["SR3l_OSSF_mT>160_ETmiss150-200_mll75-105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss150-200_mll75-105");
        _counters["SR3l_OSSF_mT>160_ETmiss150-200_mll>105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss150-200_mll>105");
        _counters["SR3l_OSSF_mT>160_ETmiss200-250_mll<75"] = EventCounter("SR3l_OSSF_mT>160_ETmiss200-250_mll<75");
        _counters["SR3l_OSSF_mT>160_ETmiss200-250_mll75-105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss200-250_mll75-105");
        _counters["SR3l_OSSF_mT>160_ETmiss200-250_mll>105"] = EventCounter("SR3l_OSSF_mT>160_ETmiss200-250_mll>105");

        // SRs in Table 2
        _counters["SR3l_noOSSF_mT<120_ETmiss50-100_mll<100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss50-100_mll<100");
        _counters["SR3l_noOSSF_mT<120_ETmiss50-100_mll>100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss50-100_mll>100");
        _counters["SR3l_noOSSF_mT<120_ETmiss100-150_mll<100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss100-150_mll<100");
        _counters["SR3l_noOSSF_mT<120_ETmiss100-150_mll>100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss100-150_mll>100");
        _counters["SR3l_noOSSF_mT<120_ETmiss150-200_mll<100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss150-200_mll<100");
        _counters["SR3l_noOSSF_mT<120_ETmiss150-200_mll>100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss150-200_mll>100");
        _counters["SR3l_noOSSF_mT<120_ETmiss200-250_mll<100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss200-250_mll<100");
        _counters["SR3l_noOSSF_mT<120_ETmiss200-250_mll>100"] = EventCounter("SR3l_noOSSF_mT<120_ETmiss200-250_mll>100");

        _counters["SR3l_noOSSF_mT120-160_ETmiss50-100_mll<100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss50-100_mll<100");
        _counters["SR3l_noOSSF_mT120-160_ETmiss50-100_mll>100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss50-100_mll>100");
        _counters["SR3l_noOSSF_mT120-160_ETmiss100-150_mll<100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss100-150_mll<100");
        _counters["SR3l_noOSSF_mT120-160_ETmiss100-150_mll>100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss100-150_mll>100");
        _counters["SR3l_noOSSF_mT120-160_ETmiss150-200_mll<100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss150-200_mll<100");
        _counters["SR3l_noOSSF_mT120-160_ETmiss150-200_mll>100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss150-200_mll>100");
        _counters["SR3l_noOSSF_mT120-160_ETmiss200-250_mll<100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss200-250_mll<100");
        _counters["SR3l_noOSSF_mT120-160_ETmiss200-250_mll>100"] = EventCounter("SR3l_noOSSF_mT120-160_ETmiss200-250_mll>100");

        _counters["SR3l_noOSSF_mT>160_ETmiss50-100_mll<100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss50-100_mll<100");
        _counters["SR3l_noOSSF_mT>160_ETmiss50-100_mll>100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss50-100_mll>100");
        _counters["SR3l_noOSSF_mT>160_ETmiss100-150_mll<100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss100-150_mll<100");
        _counters["SR3l_noOSSF_mT>160_ETmiss100-150_mll>100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss100-150_mll>100");
        _counters["SR3l_noOSSF_mT>160_ETmiss150-200_mll<100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss150-200_mll<100");
        _counters["SR3l_noOSSF_mT>160_ETmiss150-200_mll>100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss150-200_mll>100");
        _counters["SR3l_noOSSF_mT>160_ETmiss200-250_mll<100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss200-250_mll<100");
        _counters["SR3l_noOSSF_mT>160_ETmiss200-250_mll>100"] = EventCounter("SR3l_noOSSF_mT>160_ETmiss200-250_mll>100");

        // SRs in Table 3
        _counters["SR3l_SS1tau_mT<120_ETmiss50-100_mll<100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss50-100_mll<100");
        _counters["SR3l_SS1tau_mT<120_ETmiss50-100_mll>100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss50-100_mll>100");
        _counters["SR3l_SS1tau_mT<120_ETmiss100-150_mll<100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss100-150_mll<100");
        _counters["SR3l_SS1tau_mT<120_ETmiss100-150_mll>100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss100-150_mll>100");
        _counters["SR3l_SS1tau_mT<120_ETmiss150-200_mll<100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss150-200_mll<100");
        _counters["SR3l_SS1tau_mT<120_ETmiss150-200_mll>100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss150-200_mll>100");
        _counters["SR3l_SS1tau_mT<120_ETmiss200-250_mll<100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss200-250_mll<100");
        _counters["SR3l_SS1tau_mT<120_ETmiss200-250_mll>100"] = EventCounter("SR3l_SS1tau_mT<120_ETmiss200-250_mll>100");

        _counters["SR3l_SS1tau_mT120-160_ETmiss50-100_mll<100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss50-100_mll<100");
        _counters["SR3l_SS1tau_mT120-160_ETmiss50-100_mll>100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss50-100_mll>100");
        _counters["SR3l_SS1tau_mT120-160_ETmiss100-150_mll<100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss100-150_mll<100");
        _counters["SR3l_SS1tau_mT120-160_ETmiss100-150_mll>100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss100-150_mll>100");
        _counters["SR3l_SS1tau_mT120-160_ETmiss150-200_mll<100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss150-200_mll<100");
        _counters["SR3l_SS1tau_mT120-160_ETmiss150-200_mll>100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss150-200_mll>100");
        _counters["SR3l_SS1tau_mT120-160_ETmiss200-250_mll<100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss200-250_mll<100");
        _counters["SR3l_SS1tau_mT120-160_ETmiss200-250_mll>100"] = EventCounter("SR3l_SS1tau_mT120-160_ETmiss200-250_mll>100");

        _counters["SR3l_SS1tau_mT>160_ETmiss50-100_mll<100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss50-100_mll<100");
        _counters["SR3l_SS1tau_mT>160_ETmiss50-100_mll>100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss50-100_mll>100");
        _counters["SR3l_SS1tau_mT>160_ETmiss100-150_mll<100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss100-150_mll<100");
        _counters["SR3l_SS1tau_mT>160_ETmiss100-150_mll>100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss100-150_mll>100");
        _counters["SR3l_SS1tau_mT>160_ETmiss150-200_mll<100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss150-200_mll<100");
        _counters["SR3l_SS1tau_mT>160_ETmiss150-200_mll>100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss150-200_mll>100");
        _counters["SR3l_SS1tau_mT>160_ETmiss200-250_mll<100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss200-250_mll<100");
        _counters["SR3l_SS1tau_mT>160_ETmiss200-250_mll>100"] = EventCounter("SR3l_SS1tau_mT>160_ETmiss200-250_mll>100");

        // SRs in Table 4
        _counters["SR3l_OS1tau_mT<120_ETmiss50-100_mll<100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss50-100_mll<100");
        _counters["SR3l_OS1tau_mT<120_ETmiss50-100_mll>100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss50-100_mll>100");
        _counters["SR3l_OS1tau_mT<120_ETmiss100-150_mll<100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss100-150_mll<100");
        _counters["SR3l_OS1tau_mT<120_ETmiss100-150_mll>100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss100-150_mll>100");
        _counters["SR3l_OS1tau_mT<120_ETmiss150-200_mll<100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss150-200_mll<100");
        _counters["SR3l_OS1tau_mT<120_ETmiss150-200_mll>100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss150-200_mll>100");
        _counters["SR3l_OS1tau_mT<120_ETmiss200-250_mll<100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss200-250_mll<100");
        _counters["SR3l_OS1tau_mT<120_ETmiss200-250_mll>100"] = EventCounter("SR3l_OS1tau_mT<120_ETmiss200-250_mll>100");

        _counters["SR3l_OS1tau_mT120-160_ETmiss50-100_mll<100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss50-100_mll<100");
        _counters["SR3l_OS1tau_mT120-160_ETmiss50-100_mll>100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss50-100_mll>100");
        _counters["SR3l_OS1tau_mT120-160_ETmiss100-150_mll<100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss100-150_mll<100");
        _counters["SR3l_OS1tau_mT120-160_ETmiss100-150_mll>100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss100-150_mll>100");
        _counters["SR3l_OS1tau_mT120-160_ETmiss150-200_mll<100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss150-200_mll<100");
        _counters["SR3l_OS1tau_mT120-160_ETmiss150-200_mll>100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss150-200_mll>100");
        _counters["SR3l_OS1tau_mT120-160_ETmiss200-250_mll<100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss200-250_mll<100");
        _counters["SR3l_OS1tau_mT120-160_ETmiss200-250_mll>100"] = EventCounter("SR3l_OS1tau_mT120-160_ETmiss200-250_mll>100");

        _counters["SR3l_OS1tau_mT>160_ETmiss50-100_mll<100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss50-100_mll<100");
        _counters["SR3l_OS1tau_mT>160_ETmiss50-100_mll>100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss50-100_mll>100");
        _counters["SR3l_OS1tau_mT>160_ETmiss100-150_mll<100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss100-150_mll<100");
        _counters["SR3l_OS1tau_mT>160_ETmiss100-150_mll>100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss100-150_mll>100");
        _counters["SR3l_OS1tau_mT>160_ETmiss150-200_mll<100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss150-200_mll<100");
        _counters["SR3l_OS1tau_mT>160_ETmiss150-200_mll>100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss150-200_mll>100");
        _counters["SR3l_OS1tau_mT>160_ETmiss200-250_mll<100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss200-250_mll<100");
        _counters["SR3l_OS1tau_mT>160_ETmiss200-250_mll>100"] = EventCounter("SR3l_OS1tau_mT>160_ETmiss200-250_mll>100");

        // SRs in Table 5
        _counters["SR4l_1OSSF0tau_ETmiss<30"] = EventCounter("SR4l_1OSSF0tau_ETmiss<30");
        _counters["SR4l_1OSSF0tau_ETmiss30-50"] = EventCounter("SR4l_1OSSF0tau_ETmiss30-50");
        _counters["SR4l_1OSSF0tau_ETmiss50-100"] = EventCounter("SR4l_1OSSF0tau_ETmiss50-100");
        _counters["SR4l_1OSSF0tau_ETmiss>100"] = EventCounter("SR4l_1OSSF0tau_ETmiss>100");
        _counters["SR4l_1OSSF1tau_ETmiss<30"] = EventCounter("SR4l_1OSSF1tau_ETmiss<30");
        _counters["SR4l_1OSSF1tau_ETmiss30-50"] = EventCounter("SR4l_1OSSF1tau_ETmiss30-50");
        _counters["SR4l_1OSSF1tau_ETmiss50-100"] = EventCounter("SR4l_1OSSF1tau_ETmiss50-100");
        _counters["SR4l_1OSSF1tau_ETmiss>100"] = EventCounter("SR4l_1OSSF1tau_ETmiss>100");
        _counters["SR4l_2OSSF0tau_ETmiss<30"] = EventCounter("SR4l_2OSSF0tau_ETmiss<30");
        _counters["SR4l_2OSSF0tau_ETmiss30-50"] = EventCounter("SR4l_2OSSF0tau_ETmiss30-50");
        _counters["SR4l_2OSSF0tau_ETmiss50-100"] = EventCounter("SR4l_2OSSF0tau_ETmiss50-100");
        _counters["SR4l_2OSSF0tau_ETmiss>100"] = EventCounter("SR4l_2OSSF0tau_ETmiss>100");


        set_analysis_name("CMS_8TeV_MultiLEP_20invfb");
        set_luminosity(19.5);
      }


      void run(const HEPUtils::Event* event) {

        // Missing energy
        double met = event->met();
        double pTmissPhi = event->missingmom().phi();


        // Create vectors of physics objects:
        // - electrons
        vector<const HEPUtils::Particle*> signalElectrons;
        for (const HEPUtils::Particle* electron : event->electrons()) {
          if (electron->pT() > 10. && fabs(electron->eta()) < 2.4) signalElectrons.push_back(electron);
        }

        // Apply electron efficiency
        applyEfficiency(signalElectrons, CMS::eff2DEl.at("Generic"));

        // - muons
        vector<const HEPUtils::Particle*> signalMuons;
        for (const HEPUtils::Particle* muon : event->muons()) {
          if (muon->pT() > 10. && fabs(muon->eta()) < 2.4) signalMuons.push_back(muon);
        }

        // Apply muon efficiency
        applyEfficiency(signalMuons, CMS::eff2DMu.at("Generic"));

        // - taus
        vector<const HEPUtils::Particle*> signalTaus;
        for (const HEPUtils::Particle* tau : event->taus()) {
          if (tau->pT() > 20. && fabs(tau->eta()) < 2.4) signalTaus.push_back(tau);
        }
        applyEfficiency(signalTaus, CMS::effTau.at("Generic"));

        // - jets
        vector<const HEPUtils::Jet*> signalJets;
        vector<const HEPUtils::Jet*> signalBjets;
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04")) {
          if (jet->pT() > 30. && fabs(jet->eta()) < 2.5) signalJets.push_back(jet);
          if(jet->btag() && fabs(jet->eta()) < 2.5 && jet->pT() > 30.) signalBjets.push_back(jet);
        }



        // Missing: pT-dependent isolation check for leptons


        // Jet overlap removal
        JetLeptonOverlapRemoval(signalJets,signalElectrons,0.4);
        JetLeptonOverlapRemoval(signalJets,signalMuons,0.4);

        // Create combined vectors with signal leptons and taus
        vector<const HEPUtils::Particle*> signalLeptons = signalElectrons;
        signalLeptons.insert(signalLeptons.end(), signalMuons.begin(), signalMuons.end());

        vector<const HEPUtils::Particle*> signalLeptonsTaus = signalLeptons;
        signalLeptonsTaus.insert(signalLeptonsTaus.end(), signalTaus.begin(), signalTaus.end());

        // Sort by pT
        sort(signalJets.begin(), signalJets.end(), compareJetPt);
        sort(signalLeptons.begin(), signalLeptons.end(), comparePt);
        sort(signalLeptonsTaus.begin(), signalLeptonsTaus.end(), comparePt);

        // Count signal leptons, taus and jets
        int nSignalElectrons = signalElectrons.size();
        int nSignalMuons = signalMuons.size();
        int nSignalLeptons = signalLeptons.size();
        int nSignalTaus = signalTaus.size();
        // int nSignalJets = signalJets.size();
        int nSignalBjets = signalBjets.size();

        // Has the highest-pT lepton pT > 20 GeV?
        bool hasPt20Lepton = false;
        if (nSignalLeptons > 0) {
          if (signalLeptons.at(0)->pT() > 20) hasPt20Lepton = true;
        }

        // Get OS and OSSF pairs
        vector<vector<const HEPUtils::Particle*>> OSSFpairs = getSFOSpairs(signalLeptons);
        vector<vector<const HEPUtils::Particle*>> OSSFpairsWithTaus = getSFOSpairs(signalLeptonsTaus);
        vector<vector<const HEPUtils::Particle*>> OSpairs = getOSpairs(signalLeptons);
        vector<vector<const HEPUtils::Particle*>> OSpairsWithTaus = getOSpairs(signalLeptonsTaus);
        vector<vector<const HEPUtils::Particle*>> SSpairs = getSSpairs(signalLeptons);
        vector<vector<const HEPUtils::Particle*>> SSpairsWithTaus = getSSpairs(signalLeptonsTaus);
        int nOSSFpairs = OSSFpairs.size();
        // int nOSSFpairsWithTaus = OSSFpairsWithTaus.size();
        int nOSpairs = OSpairs.size();
        int nOSpairsWithTaus = OSpairsWithTaus.size();
        int nSSpairs = SSpairs.size();
        // int nSSpairsWithTaus = SSpairsWithTaus.size();

        // Is there an OSSF ee/mumu pair with invraiant mass below 12 GeV?
        bool hasLowmassOSSFpair = false;
        for (vector<const HEPUtils::Particle*> pair : OSSFpairs) {
          double mll_pair = (pair.at(0)->mom() + pair.at(1)->mom()).m();
          if (mll_pair < 12.) {
            hasLowmassOSSFpair = true;
            break;
          }
        }


        // Determine which group of SRs the event belongs to and
        // calculate the transverse mass and invariant mass accordingly.

        int SRgroup = 0; // Use numbering corresponding to the results tables in the paper
        double mll = 0;
        double mT = 0;
        static const double mZ = 91.2;

        //
        // Events from Table 1: ee/mumu OSSF pair + one more e or mu
        //
        if (nSignalLeptons==3 && nSignalTaus==0 && nOSSFpairs>0) {

          // Set SR group
          SRgroup = 1;

          // Choose OSSF pair with mll closest to mZ
          vector<const HEPUtils::Particle*> pair = getClosestMllPair(OSSFpairs, mZ);
          mll = (pair.at(0)->mom() + pair.at(1)->mom()).m();

          // Identify the 'third lepton', i.e. the signal lepton
          // that is not part of the OSSF pair
          const HEPUtils::Particle* third_lepton = getLeptonNotInPair(signalLeptons, pair);

          // Calculate mT with the third lepton
          mT = transverseMass(met, pTmissPhi, third_lepton->pT(), third_lepton->phi());
        }
        //
        // Events from Table 2: eemu/emumu events *without* OSSF pair
        //
        else if (nSignalLeptons==3 && nSignalElectrons<3 && nSignalMuons<3 &&
                 nSignalTaus==0 && nOSSFpairs==0 && nOSpairs>0) {

          // Set SR group
          SRgroup = 2;

          // Choose OS pair with mll closest to 50 GeV.
          // (Since nOSSFpairs==0, this pair must be an e-mu pair.)
          vector<const HEPUtils::Particle*> pair = getClosestMllPair(OSpairs, 50.);
          mll = (pair.at(0)->mom() + pair.at(1)->mom()).m();

          // Identify the 'third lepton', i.e. the signal lepton
          // that is not part of the OSSF pair
          const HEPUtils::Particle* third_lepton = getLeptonNotInPair(signalLeptons, pair);

          // Calculate mT with the third lepton
          mT = transverseMass(met, pTmissPhi, third_lepton->pT(), third_lepton->phi());
        }
        //
        // Events from Table 3: same-sign ee/mumu/emu pair + one tau
        //
        else if (nSignalLeptons==2 && nSignalTaus==1 && nSSpairs==1 && nOSpairsWithTaus>0) {

          // Set SR group
          SRgroup = 3;

          // Choose OS (e-tau or mu-tau) pair with mll closest to 60 GeV
          vector<const HEPUtils::Particle*> pair = getClosestMllPair(OSpairsWithTaus, 60.);
          mll = (pair.at(0)->mom() + pair.at(1)->mom()).m();

          // Identify the 'third lepton', i.e. the signal lepton
          // that is not part of the OS pair
          const HEPUtils::Particle* third_lepton = getLeptonNotInPair(signalLeptons, pair);

          // Calculate mT with the third lepton
          mT = transverseMass(met, pTmissPhi, third_lepton->pT(), third_lepton->phi());
        }
        //
        // Events from Table 4: opposite-sign emu pair + one tau
        //
        else if (nSignalElectrons==1 && nSignalMuons==1 && nSignalTaus==1 && nOSpairs==1) {

          // Set SR group
          SRgroup = 4;

          // mll for emu OS pair
          vector<const HEPUtils::Particle*> pair_emu = OSpairs.at(0);
          double mll_emu = (pair_emu.at(0)->mom() + pair_emu.at(1)->mom()).m();

          // mll for etau or mutau OS pair
          const HEPUtils::Particle* tau = signalTaus.at(0);
          vector<const HEPUtils::Particle*> pair_withtau;
          pair_withtau.push_back(tau);
          // - Pick the particle from the OS emu pair that has the opposite sign to the tau
          if (pair_emu.at(0)->pid() * tau->pid() < 0) {
            pair_withtau.push_back(pair_emu.at(0));
          }
          else {
            pair_withtau.push_back(pair_emu.at(1));
          }
          double mll_withtau = (pair_withtau.at(0)->mom() + pair_withtau.at(1)->mom()).m();

          // Use the invariant mass that is closest to the the expected mass resulting from
          // Z -> tautau events (50 GeV for emu pair, 60 GeV for etau/mutau pair).
          // Then calculate mT using the remaining e/mu/tau.
          if (fabs(mll_emu - 50.) < fabs(mll_withtau - 60.)) {
            // The emu pair is the OS pair, the tau is the "third lepton"
            mll = mll_emu;
            mT = transverseMass(met, pTmissPhi, tau->pT(), tau->phi());
          }
          else {
            // The etau/mutau pair is the OS pair, the leftover e/mu is the "third lepton"
            mll = mll_withtau;
            const HEPUtils::Particle* third_lepton = getLeptonNotInPair(signalLeptons, pair_withtau);
            mT = transverseMass(met, pTmissPhi, third_lepton->pT(), third_lepton->phi());
          }
        }
        //
        // Events from Table 5: 4-leptons (including at most one tau), and one OSSF pair consistent with a Z
        //
        else if ((nSignalLeptons + nSignalTaus)==4 && nSignalTaus<=1 && nOSSFpairs>=1) {

          // Set SR group
          SRgroup = 5;

          // Choose OSSF pair with mll closest to mZ and use this as the mll value
          vector<const HEPUtils::Particle*> pair = getClosestMllPair(OSSFpairs, mZ);
          mll = (pair.at(0)->mom() + pair.at(1)->mom()).m();

          // Note: mT not used for this SR group
        }


        // Preselection cuts
        bool preselection = (hasPt20Lepton && !hasLowmassOSSFpair && nSignalBjets==0);

        // Increment SR counter:
        if (preselection && SRgroup > 0) {
          //
          // SR group 1
          //
          if (SRgroup==1) {
            if (mT<120 && met>50 && met<100 && mll<75)             _counters.at("SR3l_OSSF_mT<120_ETmiss50-100_mll<75").add_event(event);
            if (mT<120 && met>50 && met<100 && mll>75 && mll<105)  _counters.at("SR3l_OSSF_mT<120_ETmiss50-100_mll75-105").add_event(event);
            if (mT<120 && met>50 && met<100 && mll>105)            _counters.at("SR3l_OSSF_mT<120_ETmiss50-100_mll>105").add_event(event);
            if (mT<120 && met>100 && met<150 && mll<75)            _counters.at("SR3l_OSSF_mT<120_ETmiss100-150_mll<75").add_event(event);
            if (mT<120 && met>100 && met<150 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT<120_ETmiss100-150_mll75-105").add_event(event);
            if (mT<120 && met>100 && met<150 && mll>105)           _counters.at("SR3l_OSSF_mT<120_ETmiss100-150_mll>105").add_event(event);
            if (mT<120 && met>150 && met<200 && mll<75)            _counters.at("SR3l_OSSF_mT<120_ETmiss150-200_mll<75").add_event(event);
            if (mT<120 && met>150 && met<200 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT<120_ETmiss150-200_mll75-105").add_event(event);
            if (mT<120 && met>150 && met<200 && mll>105)           _counters.at("SR3l_OSSF_mT<120_ETmiss150-200_mll>105").add_event(event);
            if (mT<120 && met>200 && met<250 && mll<75)            _counters.at("SR3l_OSSF_mT<120_ETmiss200-250_mll<75").add_event(event);
            if (mT<120 && met>200 && met<250 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT<120_ETmiss200-250_mll75-105").add_event(event);
            if (mT<120 && met>200 && met<250 && mll>105)           _counters.at("SR3l_OSSF_mT<120_ETmiss200-250_mll>105").add_event(event);

            if (mT>120 && mT<160 && met>50 && met<100 && mll<75)             _counters.at("SR3l_OSSF_mT120-160_ETmiss50-100_mll<75").add_event(event);
            if (mT>120 && mT<160 && met>50 && met<100 && mll>75 && mll<105)  _counters.at("SR3l_OSSF_mT120-160_ETmiss50-100_mll75-105").add_event(event);
            if (mT>120 && mT<160 && met>50 && met<100 && mll>105)            _counters.at("SR3l_OSSF_mT120-160_ETmiss50-100_mll>105").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll<75)            _counters.at("SR3l_OSSF_mT120-160_ETmiss100-150_mll<75").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT120-160_ETmiss100-150_mll75-105").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll>105)           _counters.at("SR3l_OSSF_mT120-160_ETmiss100-150_mll>105").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll<75)            _counters.at("SR3l_OSSF_mT120-160_ETmiss150-200_mll<75").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT120-160_ETmiss150-200_mll75-105").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll>105)           _counters.at("SR3l_OSSF_mT120-160_ETmiss150-200_mll>105").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll<75)            _counters.at("SR3l_OSSF_mT120-160_ETmiss200-250_mll<75").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT120-160_ETmiss200-250_mll75-105").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll>105)           _counters.at("SR3l_OSSF_mT120-160_ETmiss200-250_mll>105").add_event(event);

            if (mT>160 && met>50 && met<100 && mll<75)             _counters.at("SR3l_OSSF_mT>160_ETmiss50-100_mll<75").add_event(event);
            if (mT>160 && met>50 && met<100 && mll>75 && mll<105)  _counters.at("SR3l_OSSF_mT>160_ETmiss50-100_mll75-105").add_event(event);
            if (mT>160 && met>50 && met<100 && mll>105)            _counters.at("SR3l_OSSF_mT>160_ETmiss50-100_mll>105").add_event(event);
            if (mT>160 && met>100 && met<150 && mll<75)            _counters.at("SR3l_OSSF_mT>160_ETmiss100-150_mll<75").add_event(event);
            if (mT>160 && met>100 && met<150 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT>160_ETmiss100-150_mll75-105").add_event(event);
            if (mT>160 && met>100 && met<150 && mll>105)           _counters.at("SR3l_OSSF_mT>160_ETmiss100-150_mll>105").add_event(event);
            if (mT>160 && met>150 && met<200 && mll<75)            _counters.at("SR3l_OSSF_mT>160_ETmiss150-200_mll<75").add_event(event);
            if (mT>160 && met>150 && met<200 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT>160_ETmiss150-200_mll75-105").add_event(event);
            if (mT>160 && met>150 && met<200 && mll>105)           _counters.at("SR3l_OSSF_mT>160_ETmiss150-200_mll>105").add_event(event);
            if (mT>160 && met>200 && met<250 && mll<75)            _counters.at("SR3l_OSSF_mT>160_ETmiss200-250_mll<75").add_event(event);
            if (mT>160 && met>200 && met<250 && mll>75 && mll<105) _counters.at("SR3l_OSSF_mT>160_ETmiss200-250_mll75-105").add_event(event);
            if (mT>160 && met>200 && met<250 && mll>105)           _counters.at("SR3l_OSSF_mT>160_ETmiss200-250_mll>105").add_event(event);
          }
          //
          // SR group 2
          //
          else if (SRgroup==2) {
            if (mT<120 && met>50 && met<100 && mll<100)  _counters.at("SR3l_noOSSF_mT<120_ETmiss50-100_mll<100").add_event(event);
            if (mT<120 && met>50 && met<100 && mll>100)  _counters.at("SR3l_noOSSF_mT<120_ETmiss50-100_mll>100").add_event(event);
            if (mT<120 && met>100 && met<150 && mll<100) _counters.at("SR3l_noOSSF_mT<120_ETmiss100-150_mll<100").add_event(event);
            if (mT<120 && met>100 && met<150 && mll>100) _counters.at("SR3l_noOSSF_mT<120_ETmiss100-150_mll>100").add_event(event);
            if (mT<120 && met>150 && met<200 && mll<100) _counters.at("SR3l_noOSSF_mT<120_ETmiss150-200_mll<100").add_event(event);
            if (mT<120 && met>150 && met<200 && mll>100) _counters.at("SR3l_noOSSF_mT<120_ETmiss150-200_mll>100").add_event(event);
            if (mT<120 && met>200 && met<250 && mll<100) _counters.at("SR3l_noOSSF_mT<120_ETmiss200-250_mll<100").add_event(event);
            if (mT<120 && met>200 && met<250 && mll>100) _counters.at("SR3l_noOSSF_mT<120_ETmiss200-250_mll>100").add_event(event);

            if (mT>120 && mT<160 && met>50 && met<100 && mll<100)  _counters.at("SR3l_noOSSF_mT120-160_ETmiss50-100_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>50 && met<100 && mll>100)  _counters.at("SR3l_noOSSF_mT120-160_ETmiss50-100_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll<100) _counters.at("SR3l_noOSSF_mT120-160_ETmiss100-150_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll>100) _counters.at("SR3l_noOSSF_mT120-160_ETmiss100-150_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll<100) _counters.at("SR3l_noOSSF_mT120-160_ETmiss150-200_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll>100) _counters.at("SR3l_noOSSF_mT120-160_ETmiss150-200_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll<100) _counters.at("SR3l_noOSSF_mT120-160_ETmiss200-250_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll>100) _counters.at("SR3l_noOSSF_mT120-160_ETmiss200-250_mll>100").add_event(event);

            if (mT>160 && met>50 && met<100 && mll<100)  _counters.at("SR3l_noOSSF_mT>160_ETmiss50-100_mll<100").add_event(event);
            if (mT>160 && met>50 && met<100 && mll>100)  _counters.at("SR3l_noOSSF_mT>160_ETmiss50-100_mll>100").add_event(event);
            if (mT>160 && met>100 && met<150 && mll<100) _counters.at("SR3l_noOSSF_mT>160_ETmiss100-150_mll<100").add_event(event);
            if (mT>160 && met>100 && met<150 && mll>100) _counters.at("SR3l_noOSSF_mT>160_ETmiss100-150_mll>100").add_event(event);
            if (mT>160 && met>150 && met<200 && mll<100) _counters.at("SR3l_noOSSF_mT>160_ETmiss150-200_mll<100").add_event(event);
            if (mT>160 && met>150 && met<200 && mll>100) _counters.at("SR3l_noOSSF_mT>160_ETmiss150-200_mll>100").add_event(event);
            if (mT>160 && met>200 && met<250 && mll<100) _counters.at("SR3l_noOSSF_mT>160_ETmiss200-250_mll<100").add_event(event);
            if (mT>160 && met>200 && met<250 && mll>100) _counters.at("SR3l_noOSSF_mT>160_ETmiss200-250_mll>100").add_event(event);
          }
          //
          // SR group 3
          //
          else if (SRgroup==3) {
            if (mT<120 && met>50 && met<100 && mll<100)  _counters.at("SR3l_SS1tau_mT<120_ETmiss50-100_mll<100").add_event(event);
            if (mT<120 && met>50 && met<100 && mll>100)  _counters.at("SR3l_SS1tau_mT<120_ETmiss50-100_mll>100").add_event(event);
            if (mT<120 && met>100 && met<150 && mll<100) _counters.at("SR3l_SS1tau_mT<120_ETmiss100-150_mll<100").add_event(event);
            if (mT<120 && met>100 && met<150 && mll>100) _counters.at("SR3l_SS1tau_mT<120_ETmiss100-150_mll>100").add_event(event);
            if (mT<120 && met>150 && met<200 && mll<100) _counters.at("SR3l_SS1tau_mT<120_ETmiss150-200_mll<100").add_event(event);
            if (mT<120 && met>150 && met<200 && mll>100) _counters.at("SR3l_SS1tau_mT<120_ETmiss150-200_mll>100").add_event(event);
            if (mT<120 && met>200 && met<250 && mll<100) _counters.at("SR3l_SS1tau_mT<120_ETmiss200-250_mll<100").add_event(event);
            if (mT<120 && met>200 && met<250 && mll>100) _counters.at("SR3l_SS1tau_mT<120_ETmiss200-250_mll>100").add_event(event);

            if (mT>120 && mT<160 && met>50 && met<100 && mll<100)  _counters.at("SR3l_SS1tau_mT120-160_ETmiss50-100_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>50 && met<100 && mll>100)  _counters.at("SR3l_SS1tau_mT120-160_ETmiss50-100_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll<100) _counters.at("SR3l_SS1tau_mT120-160_ETmiss100-150_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll>100) _counters.at("SR3l_SS1tau_mT120-160_ETmiss100-150_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll<100) _counters.at("SR3l_SS1tau_mT120-160_ETmiss150-200_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll>100) _counters.at("SR3l_SS1tau_mT120-160_ETmiss150-200_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll<100) _counters.at("SR3l_SS1tau_mT120-160_ETmiss200-250_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll>100) _counters.at("SR3l_SS1tau_mT120-160_ETmiss200-250_mll>100").add_event(event);

            if (mT>160 && met>50 && met<100 && mll<100)  _counters.at("SR3l_SS1tau_mT>160_ETmiss50-100_mll<100").add_event(event);
            if (mT>160 && met>50 && met<100 && mll>100)  _counters.at("SR3l_SS1tau_mT>160_ETmiss50-100_mll>100").add_event(event);
            if (mT>160 && met>100 && met<150 && mll<100) _counters.at("SR3l_SS1tau_mT>160_ETmiss100-150_mll<100").add_event(event);
            if (mT>160 && met>100 && met<150 && mll>100) _counters.at("SR3l_SS1tau_mT>160_ETmiss100-150_mll>100").add_event(event);
            if (mT>160 && met>150 && met<200 && mll<100) _counters.at("SR3l_SS1tau_mT>160_ETmiss150-200_mll<100").add_event(event);
            if (mT>160 && met>150 && met<200 && mll>100) _counters.at("SR3l_SS1tau_mT>160_ETmiss150-200_mll>100").add_event(event);
            if (mT>160 && met>200 && met<250 && mll<100) _counters.at("SR3l_SS1tau_mT>160_ETmiss200-250_mll<100").add_event(event);
            if (mT>160 && met>200 && met<250 && mll>100) _counters.at("SR3l_SS1tau_mT>160_ETmiss200-250_mll>100").add_event(event);
          }
          //
          // SR group 4
          //
          else if (SRgroup==4) {
            if (mT<120 && met>50 && met<100 && mll<100)  _counters.at("SR3l_OS1tau_mT<120_ETmiss50-100_mll<100").add_event(event);
            if (mT<120 && met>50 && met<100 && mll>100)  _counters.at("SR3l_OS1tau_mT<120_ETmiss50-100_mll>100").add_event(event);
            if (mT<120 && met>100 && met<150 && mll<100) _counters.at("SR3l_OS1tau_mT<120_ETmiss100-150_mll<100").add_event(event);
            if (mT<120 && met>100 && met<150 && mll>100) _counters.at("SR3l_OS1tau_mT<120_ETmiss100-150_mll>100").add_event(event);
            if (mT<120 && met>150 && met<200 && mll<100) _counters.at("SR3l_OS1tau_mT<120_ETmiss150-200_mll<100").add_event(event);
            if (mT<120 && met>150 && met<200 && mll>100) _counters.at("SR3l_OS1tau_mT<120_ETmiss150-200_mll>100").add_event(event);
            if (mT<120 && met>200 && met<250 && mll<100) _counters.at("SR3l_OS1tau_mT<120_ETmiss200-250_mll<100").add_event(event);
            if (mT<120 && met>200 && met<250 && mll>100) _counters.at("SR3l_OS1tau_mT<120_ETmiss200-250_mll>100").add_event(event);

            if (mT>120 && mT<160 && met>50 && met<100 && mll<100)  _counters.at("SR3l_OS1tau_mT120-160_ETmiss50-100_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>50 && met<100 && mll>100)  _counters.at("SR3l_OS1tau_mT120-160_ETmiss50-100_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll<100) _counters.at("SR3l_OS1tau_mT120-160_ETmiss100-150_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>100 && met<150 && mll>100) _counters.at("SR3l_OS1tau_mT120-160_ETmiss100-150_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll<100) _counters.at("SR3l_OS1tau_mT120-160_ETmiss150-200_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>150 && met<200 && mll>100) _counters.at("SR3l_OS1tau_mT120-160_ETmiss150-200_mll>100").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll<100) _counters.at("SR3l_OS1tau_mT120-160_ETmiss200-250_mll<100").add_event(event);
            if (mT>120 && mT<160 && met>200 && met<250 && mll>100) _counters.at("SR3l_OS1tau_mT120-160_ETmiss200-250_mll>100").add_event(event);

            if (mT>160 && met>50 && met<100 && mll<100)  _counters.at("SR3l_OS1tau_mT>160_ETmiss50-100_mll<100").add_event(event);
            if (mT>160 && met>50 && met<100 && mll>100)  _counters.at("SR3l_OS1tau_mT>160_ETmiss50-100_mll>100").add_event(event);
            if (mT>160 && met>100 && met<150 && mll<100) _counters.at("SR3l_OS1tau_mT>160_ETmiss100-150_mll<100").add_event(event);
            if (mT>160 && met>100 && met<150 && mll>100) _counters.at("SR3l_OS1tau_mT>160_ETmiss100-150_mll>100").add_event(event);
            if (mT>160 && met>150 && met<200 && mll<100) _counters.at("SR3l_OS1tau_mT>160_ETmiss150-200_mll<100").add_event(event);
            if (mT>160 && met>150 && met<200 && mll>100) _counters.at("SR3l_OS1tau_mT>160_ETmiss150-200_mll>100").add_event(event);
            if (mT>160 && met>200 && met<250 && mll<100) _counters.at("SR3l_OS1tau_mT>160_ETmiss200-250_mll<100").add_event(event);
            if (mT>160 && met>200 && met<250 && mll>100) _counters.at("SR3l_OS1tau_mT>160_ETmiss200-250_mll>100").add_event(event);
          }
          //
          // SR group 5
          //
          else if (SRgroup==5) {
            if (nOSSFpairs==1 && nSignalTaus==0 && mll>75 && mll<105 && met<30)            _counters.at("SR4l_1OSSF0tau_ETmiss<30").add_event(event);
            if (nOSSFpairs==1 && nSignalTaus==0 && mll>75 && mll<105 && met>30 && met<50)  _counters.at("SR4l_1OSSF0tau_ETmiss30-50").add_event(event);
            if (nOSSFpairs==1 && nSignalTaus==0 && mll>75 && mll<105 && met>50 && met<100) _counters.at("SR4l_1OSSF0tau_ETmiss50-100").add_event(event);
            if (nOSSFpairs==1 && nSignalTaus==0 && mll>75 && mll<105 && met>100)           _counters.at("SR4l_1OSSF0tau_ETmiss>100").add_event(event);

            if (nOSSFpairs==1 && nSignalTaus==1 && mll>75 && mll<105 && met<30)            _counters.at("SR4l_1OSSF1tau_ETmiss<30").add_event(event);
            if (nOSSFpairs==1 && nSignalTaus==1 && mll>75 && mll<105 && met>30 && met<50)  _counters.at("SR4l_1OSSF1tau_ETmiss30-50").add_event(event);
            if (nOSSFpairs==1 && nSignalTaus==1 && mll>75 && mll<105 && met>50 && met<100) _counters.at("SR4l_1OSSF1tau_ETmiss50-100").add_event(event);
            if (nOSSFpairs==1 && nSignalTaus==1 && mll>75 && mll<105 && met>100)           _counters.at("SR4l_1OSSF1tau_ETmiss>100").add_event(event);

            if (nOSSFpairs==2 && nSignalTaus==0 && mll>75 && mll<105 && met<30)            _counters.at("SR4l_2OSSF0tau_ETmiss<30").add_event(event);
            if (nOSSFpairs==2 && nSignalTaus==0 && mll>75 && mll<105 && met>30 && met<50)  _counters.at("SR4l_2OSSF0tau_ETmiss30-50").add_event(event);
            if (nOSSFpairs==2 && nSignalTaus==0 && mll>75 && mll<105 && met>50 && met<100) _counters.at("SR4l_2OSSF0tau_ETmiss50-100").add_event(event);
            if (nOSSFpairs==2 && nSignalTaus==0 && mll>75 && mll<105 && met>100)           _counters.at("SR4l_2OSSF0tau_ETmiss>100").add_event(event);
          }
        }

      }

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results() {

        // Format:
        // add_result(SignalRegionData(_counters.at("SR label"), n_obs, {b, b_sys}));

        // Using the macros defined at the top of the file
        ADD_RESULTS_SRGROUP_1
        ADD_RESULTS_SRGROUP_2
        ADD_RESULTS_SRGROUP_3
        ADD_RESULTS_SRGROUP_4
        ADD_RESULTS_SRGROUP_5
      }


    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters) { pair.second.reset(); }
        #ifdef CHECK_CUTFLOW
          std::fill(cutFlowVector.begin(), cutFlowVector.end(), 0);
        #endif
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_8TeV_MultiLEP_20invfb)



    //
    //  Derived analysis class for the 3-lepton SRs
    //
    class Analysis_CMS_8TeV_MultiLEP_3Lep_20invfb : public Analysis_CMS_8TeV_MultiLEP_20invfb {

    public:
      Analysis_CMS_8TeV_MultiLEP_3Lep_20invfb() {
        set_analysis_name("CMS_8TeV_MultiLEP_3Lep_20invfb");
      }

      virtual void collect_results() {
        // Adding results from the SR groups 1-4 (the 3-lepton SR groups)
        ADD_RESULTS_SRGROUP_1
        ADD_RESULTS_SRGROUP_2
        ADD_RESULTS_SRGROUP_3
        ADD_RESULTS_SRGROUP_4
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_8TeV_MultiLEP_3Lep_20invfb)


    //
    //  Derived analysis class for the 4-lepton SRs
    //
    class Analysis_CMS_8TeV_MultiLEP_4Lep_20invfb : public Analysis_CMS_8TeV_MultiLEP_20invfb {

    public:
      Analysis_CMS_8TeV_MultiLEP_4Lep_20invfb() {
        set_analysis_name("CMS_8TeV_MultiLEP_4Lep_20invfb");
      }

      virtual void collect_results() {
        // Adding results from the SR group 5 (the 4-lepton SR group)
        ADD_RESULTS_SRGROUP_5
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_8TeV_MultiLEP_4Lep_20invfb)


  }
}
