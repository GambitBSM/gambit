///
///  \author Holly Pacey
///  \date 2024 January
///
///  *********************************************

// Based on https://cms-results.web.cern.ch/cms-results/public-results/publications/SUS-19-010/index.html
// Luminosity: 137 fb^-1

#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "SoftDrop.hh" 

#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/ColliderBit/analyses/AnalysisMacros.hpp"
#include "gambit/ColliderBit/CMSEfficiencies.hpp"
#include "gambit/ColliderBit/analyses/Cutflow.hpp"
#include "gambit/ColliderBit/mt2_bisect.h"

using namespace std;

namespace Gambit
{
  namespace ColliderBit
  {

    class Analysis_CMS_13TeV_0LEPStop_137invfb : public Analysis
    {

    protected:

      Cutflows _cutflows;

    private:

      struct ptComparison
      {
        bool operator() (const HEPUtils::Particle* i,const HEPUtils::Particle* j) {return (i->pT()>j->pT());}
      } comparePt;

      struct ptJetComparison
      {
        bool operator() (const HEPUtils::Jet* i,const HEPUtils::Jet* j) {return (i->pT()>j->pT());}
      } compareJetPt;


    public:

      bool doCutflow = false;

      // Required detector sim
      static constexpr const char* detector = "CMS";

      Analysis_CMS_13TeV_0LEPStop_137invfb()
      {
        set_analysis_name("CMS_13TeV_0LEPStop_137invfb");
        set_luminosity(137);
//
//      Counters for the number of accepted events for each signal region

//      Preselections:
//      Baseline: MET>250, Nj>=2, 0e+0mu, 0tau, Ht>300
//      Low dM:n_MergedTop+Nw+Nres=0, mTb<175 iff Nb>=1, dPhi(j123,MET)>0.5,0.15,0.15, N_ISR=1 && dPhi(MET, ISRjet)>2, MET/sqrt(Ht)>10
//      High dM: Nj>=5, Nb>=1, dPhi(MET,j1,2,3,4)>0.5

        if (doCutflow)
        {
            DEFINE_SIGNAL_REGION_NOCUTS("Total");
            DEFINE_SIGNAL_REGION_NOCUTS("baseline_MET");
            DEFINE_SIGNAL_REGION_NOCUTS("baseline_MET_Nj");
            DEFINE_SIGNAL_REGION_NOCUTS("baseline_MET_Nj_0e0mu");
            DEFINE_SIGNAL_REGION_NOCUTS("baseline_MET_Nj_0e0mu_0tau");
            DEFINE_SIGNAL_REGION_NOCUTS("baseline_MET_Nj_0e0mu_0tau_Ht");
            DEFINE_SIGNAL_REGION_NOCUTS("lowDM_NtNwNres");
            DEFINE_SIGNAL_REGION_NOCUTS("lowDM_NtNwNres_mTb");
            DEFINE_SIGNAL_REGION_NOCUTS("lowDM_NtNwNres_mTb_dPhi");
            DEFINE_SIGNAL_REGION_NOCUTS("lowDM_NtNwNres_mTb_dPhi_ISR");
            DEFINE_SIGNAL_REGION_NOCUTS("lowDM_NtNwNres_mTb_dPhi_ISR_METHt");
            DEFINE_SIGNAL_REGION_NOCUTS("highDM_Nj");
            DEFINE_SIGNAL_REGION_NOCUTS("highDM_Nj_Nb");
            DEFINE_SIGNAL_REGION_NOCUTS("highDM_Nj_Nb_dPhi");
        }

        // low dM 53 bins
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-0_2Nj5_Nb0_Nsv0_500ISR_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-1_2Nj5_Nb0_Nsv0_500ISR_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-2_2Nj5_Nb0_Nsv0_500ISR_650MET750");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-3_2Nj5_Nb0_Nsv0_500ISR_750MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-4_6Nj_Nb0_Nsv0_500ISR_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-5_6Nj_Nb0_Nsv0_500ISR_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-6_6Nj_Nb0_Nsv0_500ISR_650MET750");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-7_6Nj_Nb0_Nsv0_500ISR_750MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-8_2Nj5_Nb0_1Nsv_500ISR_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-9_2Nj5_Nb0_1Nsv_500ISR_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-10_2Nj5_Nb0_1Nsv_500ISR_650MET750");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-11_2Nj5_Nb0_1Nsv_500ISR_750MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-12_6Nj_Nb0_1Nsv_500ISR_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-13_6Nj_Nb0_1Nsv_500ISR_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-14_6Nj_Nb0_1Nsv_500ISR_650MET750");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-15_6Nj_Nb0_1Nsv_500ISR_750MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-16_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-17_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-18_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_500MET600");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-19_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_600MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-20_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-21_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-22_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_500MET600");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-23_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_600MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-24_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-25_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-26_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_650MET750");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-27_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_750MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-28_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-29_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-30_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_650MET750");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-31_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_750MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-32_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-33_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-34_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_500MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-35_2Nj_2Nb_mTb175_300ISR500_40pTb80_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-36_2Nj_2Nb_mTb175_300ISR500_40pTb80_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-37_2Nj_2Nb_mTb175_300ISR500_40pTb80_500MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-38_2Nj_2Nb_mTb175_300ISR500_80pTb140_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-39_2Nj_2Nb_mTb175_300ISR500_80pTb140_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-40_2Nj_2Nb_mTb175_300ISR500_80pTb140_500MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-41_7Nj_2Nb_mTb175_300ISR500_140pTb_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-42_7Nj_2Nb_mTb175_300ISR500_140pTb_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-43_7Nj_2Nb_mTb175_300ISR500_140pTb_500MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-44_2Nj_2Nb_mTb175_500ISR_40pTb80_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-45_2Nj_2Nb_mTb175_500ISR_40pTb80_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-46_2Nj_2Nb_mTb175_500ISR_40pTb80_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-47_2Nj_2Nb_mTb175_500ISR_80pTb140_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-48_2Nj_2Nb_mTb175_500ISR_80pTb140_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-49_2Nj_2Nb_mTb175_500ISR_80pTb140_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-50_7Nj_2Nb_mTb175_300ISR_140pTb_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-51_7Nj_2Nb_mTb175_300ISR_140pTb_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("lowDM-52_7Nj_2Nb_mTb175_300ISR_140pTb_650MET");

        // high dM 53 bins
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-53_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_250MET300");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-54_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-55_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-56_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_500MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-57_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_250MET300");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-58_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_300MET400");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-59_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_400MET500");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-60_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_500MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-61_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-62_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-63_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-64_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-65_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-66_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-67_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-68_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-69_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-70_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-71_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-72_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-73_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-74_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-75_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-76_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-77_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-78_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-79_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-80_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-81_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-82_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-83_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-84_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-85_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-86_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-87_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-88_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-89_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-90_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-91_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-92_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-93_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-94_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-95_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-96_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-97_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-98_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-99_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-100_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-101_175mTb_5Nj_Nb1_1Nt_0Nw_1Nres_300Ht_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-102_175mTb_5Nj_Nb1_1Nt_0Nw_1Nres_300Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-103_175mTb_5Nj_Nb1_0Nt_1Nw_1Nres_300Ht_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-104_175mTb_5Nj_Nb1_0Nt_1Nw_1Nres_300Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-105_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-106_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-107_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-108_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-109_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-110_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-111_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-112_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-113_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-114_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-115_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-116_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-117_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-118_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-119_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-120_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-121_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-122_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-123_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-124_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-125_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-126_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-127_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-128_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-129_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-130_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-131_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-132_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_450MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-133_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_550MET650");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-134_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_650MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-135_175mTb_5Nj_2Nb_1Nt_1Nw_0Nres_300Ht_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-136_175mTb_5Nj_2Nb_1Nt_1Nw_0Nres_300Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-137_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-138_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-139_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-140_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-141_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_350MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-142_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-143_175mTb_5Nj_2Nb_0Nt_1Nw_1Nres_300Ht_250MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-144_175mTb_5Nj_2Nb_0Nt_1Nw_1Nres_300Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-145_175mTb_5Nj_2Nb_2Nt_0Nw_0Nres_300Ht_250MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-146_175mTb_5Nj_2Nb_2Nt_0Nw_0Nres_300Ht_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-147_175mTb_5Nj_2Nb_0Nt_2Nw_0Nres_300Ht_250MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-148_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_300Ht1300_250MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-149_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_300Ht1300_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-150_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_1300Ht_250MET450");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-151_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_1300Ht_450MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-152_175mTb_5Nj_2Nb_3NtNwNres_300Ht_250MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-153_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-154_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_350MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-155_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-156_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-157_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_350MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-158_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-159_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-160_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_350MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-161_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-162_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-163_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_350MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-164_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-165_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-166_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_350MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-167_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-168_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-169_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_350MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-170_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-171_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-172_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_350MET550");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-173_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_550MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-174_175mTb_5Nj_3Nb_1Nt_1Nw_0Nres_300Ht_250MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-175_175mTb_5Nj_3Nb_1Nt_0Nw_1Nres_300Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-176_175mTb_5Nj_3Nb_1Nt_0Nw_1Nres_300Ht_350MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-177_175mTb_5Nj_3Nb_0Nt_1Nw_1Nres_300Ht_250MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-178_175mTb_5Nj_3Nb_2Nt_0Nw_0Nres_300Ht_250MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-179_175mTb_5Nj_3Nb_0Nt_2Nw_0Nres_300Ht_250MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-180_175mTb_5Nj_3Nb_0Nt_0Nw_2Nres_300Ht_250MET350");
        DEFINE_SIGNAL_REGION_NOCUTS("highDM-181_175mTb_5Nj_3Nb_0Nt_0Nw_2Nres_300Ht_350MET");

        DEFINE_SIGNAL_REGION_NOCUTS("highDM-182_175mTb_5Nj_3Nb_3NtNwNres_300Ht_250MET");


//        DEFINE_SIGNAL_REGION_NOCUTS("SR1BH_1L"); //, "METSig > 7");
//
      }

      bool passOverlap(vector<const HEPUtils::Jet*> ResolvedTopCand, vector<const HEPUtils::Jet*> MergedTopCands)
      {
        for (const HEPUtils::Jet* rjet : ResolvedTopCand)
        {
          for (const HEPUtils::Jet* mjet : MergedTopCands)
          {
            double dR = deltaR_eta(rjet->mom(), mjet->mom());
            if (dR<0.4) return false;
          }
        }
        return true;
      }

      double findMapValue(map<double, double> effMap, double pt)
      {
        double eff = -1.0;
        for (const auto& pair : effMap)
        {
          if (pt > pair.first)
          {
            eff = pair.second; 
          }
        }
        return eff;
      }


      void run(const HEPUtils::Event* event)
      {

        // Baseline objects
        vector<const HEPUtils::Particle*> Electrons;
        vector<const HEPUtils::Particle*> Muons;
        vector<const HEPUtils::Particle*> Taus;
        vector<const HEPUtils::Jet*> baselineJets;
        vector<const HEPUtils::Jet*> baselineFatJets;

        // Missing momentum and energy
        HEPUtils::P4 metVec = event->missingmom();
        double met = event->met();

        // Baseline electrons have |eta|<2.5
        for (const HEPUtils::Particle* electron : event->electrons())
        {
          if (electron->pT() > 5. && electron->abseta() < 2.5) Electrons.push_back(electron);
        }

        // Baseline muons have |eta|<2.4
        for (const HEPUtils::Particle* muon : event->muons())
        {
          if (muon->pT() > 5. && muon->abseta() < 2.4) Muons.push_back(muon);
        }

        // Baseline taus have |eta|<2.4, pT>20 GeV, mT<100GeV
        for (const HEPUtils::Particle* tau : event->taus())
        {
          if (tau->pT() > 20 && tau->abseta() < 2.4 && get_mT(tau, metVec) < 100.) Taus.push_back(tau);
        }

        // Only jet candidates with pT > 20 GeV and |η| < 2.4 are considered in the analysis
        double Ht = 0.; 
        for (const HEPUtils::Jet* jet : event->jets("antikt_R04"))
        {
          if (jet->pT()>20. && jet->abseta()<2.4)
          {
            baselineJets.push_back(jet);
            Ht += jet->pT();
          }
        }

        for (const HEPUtils::Jet* fjet : event->jets("antikt_R08"))
        {
          if (fjet->pT()>200. && fjet->abseta()<2.4)
          {
            baselineFatJets.push_back(fjet);
          }
        }

        // Signal objects
        vector<const HEPUtils::Jet*> signalJets_20 = baselineJets;
        vector<const HEPUtils::Jet*> signalJets_30;
        vector<const HEPUtils::Jet*> signalBJets_20;
        vector<const HEPUtils::Jet*> signalBJets_30;
        vector<const HEPUtils::Jet*> signalBJets_soft;

        // Signal jets have pT > 30 GeV
        for (const HEPUtils::Jet* jet : baselineJets)
        {
          if (jet->pT() > 30.)
          {
            signalJets_30.push_back(jet);
          }
        }

        // Find b-jets
        vector<int> signalJets_20_isB;
        double btag = 0.68; double cmisstag = 0.012; double misstag = 0.01;
        for (const HEPUtils::Jet* jet : signalJets_20)
        {
          // Tag or Mistag c-jet
          if( (jet->btag() && random_bool(btag)) || (jet->ctag() && random_bool(cmisstag)) )
          {
            signalBJets_20.push_back(jet);
            signalJets_20_isB.push_back(1);
          }
          // Misstag light jet
          else if( (!jet->btag() && !jet->ctag()) && random_bool(misstag) )
          {
            signalBJets_20.push_back(jet);
            signalJets_20_isB.push_back(1);
          }
          else
          {
            signalJets_20_isB.push_back(0);
          }
        }

        // Signal jets have pT > 30 GeV
        for (const HEPUtils::Jet* jet : signalBJets_20)
        {
          if (jet->pT() > 30.)
          {
            signalBJets_30.push_back(jet);
          }
        }

        // Find soft b-jets
        double softbtag = 0.475; double softmisstag = 0.035;
        for (const HEPUtils::Jet* jet : baselineJets)
        {
          // Tag
          if( jet->btag() && random_bool(softbtag) ) signalBJets_soft.push_back(jet);
          // Misstag light jet
          else if( !jet->btag() && random_bool(softmisstag) ) signalBJets_soft.push_back(jet);
        }
        removeOverlap(signalBJets_soft, signalBJets_20, 0.4);


        // Sort by pT
        sort(signalJets_20.begin(), signalJets_20.end(), compareJetPt);
        sort(signalJets_30.begin(), signalJets_30.end(), compareJetPt);
        sort(signalBJets_20.begin(), signalBJets_20.end(), compareJetPt);
        sort(signalBJets_30.begin(), signalBJets_30.end(), compareJetPt);
        sort(signalBJets_soft.begin(), signalBJets_soft.end(), compareJetPt);

        // Taggers
        
        // softDrop
        vector<const FJNS::PseudoJet*> SignalFatPseudoJets;
        double beta = 0.0;
        double z_cut = 0.1;
        double R0 = 0.8;
        FJNS::contrib::SoftDrop sd(beta, z_cut, R0);
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          FJNS::PseudoJet pj = jet->pseudojet();
          FJNS::PseudoJet groomed_jet = sd(pj);
          SignalFatPseudoJets.push_back(&groomed_jet);
        }

        // Merged Top
        map<double, double> MergedTop_Eff{ {0., 0.0}, {200., 0.000000077667}, {250., 0.0000058738}, {300., 0.00030479}, {350., 0.016794}, {400., 0.12272}, {450., 0.24526}, {500., 0.3266}, {550., 0.37828}, {600., 0.4164}, {650., 0.44189}, {700., 0.45802}, {750., 0.47089}, {800., 0.48097}, {850., 0.49454}, {900., 0.50686}, {950., 0.50204} };
        double QCDmistagTop_Eff = 0.005;
        vector<const HEPUtils::Jet*> MergedTopCands;
        vector<const FJNS::PseudoJet*> MergedTopPseudoJets;
        vector<bool> baselineFatJet_MergedTop;
        int count = 0;
        bool bFJ_isMT = false;
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          bFJ_isMT = false;
          if (jet->pT() > 400. && SignalFatPseudoJets.at(count)->m() > 105.)
          {
            // Tag boosted Top
            if( jet->btag() && random_bool(findMapValue(MergedTop_Eff, jet->pT())) )
            {
              MergedTopCands.push_back(jet);
              MergedTopPseudoJets.push_back(SignalFatPseudoJets.at(count));
              bFJ_isMT = true;
            }
            // Misstag QCD
            else if( !jet->btag() && random_bool(QCDmistagTop_Eff) )
            {
              MergedTopCands.push_back(jet);
              MergedTopPseudoJets.push_back(SignalFatPseudoJets.at(count));
              bFJ_isMT = true;
            }
          }
          baselineFatJet_MergedTop.push_back(bFJ_isMT);
          count++;
        }

        // Merged W
        map<double, double> W_Eff{ {0., 0.00000057412}, {50., 0.000024674}, {100., 0.013233}, {200., 0.16196}, {250., 0.2625}, {300., 0.31157}, {350., 0.35379}, {400., 0.37683}, {450., 0.39368}, {500., 0.41414}, {550., 0.4199}, {600., 0.43428}, {650., 0.47453}, {700., 0.45963}, {750., 0.46506}, {800., 0.43094}, {850., 0.47647}, {900., 0.44126}, {950., 0.47716} };
        double QCDmistagW_Eff = 0.01;
        vector<const FJNS::PseudoJet*> WPseudoJets;
        vector<const HEPUtils::Jet*> WCands;
        vector<bool> baselineFatJet_W;
        int countW = 0;
        bool bFJ_isW = false;
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          bFJ_isW = false;
          if (jet->pT() > 200. && (SignalFatPseudoJets.at(countW)->m() > 65. || SignalFatPseudoJets.at(countW)->m() < 105.))
          {
            // Tag boosted Top
            if( jet->btag() && random_bool(findMapValue(W_Eff, jet->pT())) )
            {
              WCands.push_back(jet);
              WPseudoJets.push_back(SignalFatPseudoJets.at(countW));
              bFJ_isW = true;
            }
            // Misstag QCD
            else if( !jet->btag() && random_bool(QCDmistagW_Eff) )
            {
              WCands.push_back(jet);
              WPseudoJets.push_back(SignalFatPseudoJets.at(countW));
              bFJ_isW = true;
            }
          }
          baselineFatJet_W.push_back(bFJ_isW);
          countW++;
        }

        // Resolved Top
        map<double, double> ResolvedTop_Eff{ {0., 0.036474}, {50., 0.11336}, {100., 0.1946}, {150., 0.25656}, {200., 0.29324}, {250., 0.30583}, {300., 0.30875}, {350., 0.29854}, {400., 0.19588}, {450., 0.10523}, {500., 0.061853}, {550., 0.036214}, {600., 0.020324}, {650., 0.010021}, {700., 0.0052826}, {750., 0.0031672}, {800., 0.0017965}, {850., 0.00064142}, {900., 0.0003081}, {950., 0.00040353} };        // Taggers
        double QCDmistagResTop_Eff = 0.02;
        // 3 smallR jets, pts >40,30,20 GeV, no more than 1 btag, all jets dR>3.1 of the centroid, no overlaps.
        vector<vector<const HEPUtils::Jet*>> ResolvedTopCands;
        vector<const HEPUtils::Jet*> ResolvedTopCand;
        set<int> jetsused;
        if (signalJets_20.size()>2)
        {
          for (unsigned int j1=0; j1<signalJets_20.size(); j1++)
          {
            if (jetsused.find(j1)!=jetsused.end()) continue;
            if (signalJets_20.at(j1)->pT()<=40.) continue; 
            for (unsigned int j2=1; j2<signalJets_20.size(); j2++)
            {
              if (j1>=j2) continue;
              if (jetsused.find(j2)!=jetsused.end()) continue;
              if (signalJets_20.at(j2)->pT()<=30.) continue; 
              for (unsigned int j3=2; j3<signalJets_20.size(); j3++)
              {
                if (j2>=j3) continue;
                if (signalJets_20.at(j3)->pT()<=20.) continue;
                // <=1 btag
                if ((signalJets_20_isB.at(j1) + signalJets_20_isB.at(j2) + signalJets_20_isB.at(j3)) > 1) continue;
                // near centroid
                HEPUtils::P4 centroid = signalJets_20.at(j1)->mom() + signalJets_20.at(j2)->mom() + signalJets_20.at(j3)->mom();
                if (deltaR_eta(centroid, signalJets_20.at(j1)->mom()) >= 3.1) continue;
                else if (deltaR_eta(centroid, signalJets_20.at(j2)->mom()) >= 3.1) continue;
                else if (deltaR_eta(centroid, signalJets_20.at(j3)->mom()) >= 3.1) continue;
                // don't use if jet already been used.
                if (jetsused.find(j3)!=jetsused.end()) continue;
                // Tag resolved Top
                bool trueResTop = signalJets_20.at(j1)->tagged(6) || signalJets_20.at(j2)->tagged(6) || signalJets_20.at(j3)->tagged(6);
                if( !( (trueResTop && random_bool(findMapValue(ResolvedTop_Eff, centroid.pT()))) || (!trueResTop && random_bool(QCDmistagResTop_Eff)) ) ) continue;
                // passed selections
                jetsused.insert(j1);
                jetsused.insert(j2);
                jetsused.insert(j3);
                ResolvedTopCand.push_back(signalJets_20.at(j1));
                ResolvedTopCand.push_back(signalJets_20.at(j2));
                ResolvedTopCand.push_back(signalJets_20.at(j3));
                if (!passOverlap(ResolvedTopCand, MergedTopCands)) continue;
                if (!passOverlap(ResolvedTopCand, WCands)) continue;
                ResolvedTopCands.push_back(ResolvedTopCand);
                ResolvedTopCand.clear();
              }
            }
          }
        }

        // Find non b-jets and non-tagged jets for ISR
        vector<const HEPUtils::Jet*> signalISRJets;
        double loosebtag = 0.80; double loosemisstag = 0.10;
        int f = 0;
        for (const HEPUtils::Jet* jet : baselineFatJets)
        {
          if (!(baselineFatJet_MergedTop.at(f) || baselineFatJet_W.at(f) || deltaPhi(jet->mom(),metVec)<=2))
          {
            // Tag
            if( jet->btag() && !random_bool(loosebtag) ) signalISRJets.push_back(jet);
            // Misstag light jet
            else if( !jet->btag() && !random_bool(loosemisstag) ) signalISRJets.push_back(jet);
          }
          f++;
        }

        // Count
        int n_MergedTop = MergedTopCands.size();
        int n_ResolvedTop = ResolvedTopCands.size();
        int n_W = WCands.size();
        int n_electrons = Electrons.size();
        int n_muons = Muons.size();
        int n_taus = Taus.size();
        int n_jets_30 = signalJets_30.size();
        int n_bjets_30 = signalBJets_30.size();
        int n_SV = signalBJets_soft.size();
        int n_ISR = signalISRJets.size();

        double mTb = -1.;
        double pTb = -1.;
        if (n_bjets_30==1)
        {
          mTb = get_mT(signalBJets_30.at(0)->mom(), metVec);
          pTb = signalBJets_30.at(0)->pT();
        }
        else if (n_bjets_30>1)
        {
          mTb = get_mT((signalBJets_30.at(0)->mom()+signalBJets_30.at(1)->mom()), metVec);
          pTb = signalBJets_30.at(0)->pT() + signalBJets_30.at(0)->pT();
        }

        /* Preselection */
        // True if passes this cut, false otherwise
        bool baseline_presel = false; // baseline Pre-selection cut
        bool low_dM_presel = false; // low dM Pre-selection cut
        bool high_dM_presel = false; // high dM Pre-selection cut

//        FILL_SIGNAL_REGION("Total");
        if (doCutflow){ FILL_SIGNAL_REGION("Total");}

        // Perform all pre-selection cuts
        BEGIN_PRESELECTION
        while(true)
        {

            // Passes MET > 250 GeV
            if (met > 250.)
            {
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET");}
              // Passes the Nj >= 2
              if (!(n_jets_30 >= 2))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj");}
              // Passes the e and mu veto
              if (!(n_electrons==0 && n_muons==0))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj_0e0mu");}
              // Passes the tau veto
              if (!(n_taus==0))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau");}
              // Passes Ht > 300 GeV
              if (!(Ht > 300.))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau_Ht");}
              // Set Baseline preselection as passed :)
              baseline_presel = true;
            }
            break;

        }
        while(true)
        {
            // Low dM selection
            if (baseline_presel)
            {
              // Passes then_MergedTop+NW+Nres=0
              if (!((n_W + n_ResolvedTop + n_MergedTop)==0))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowDM_NtNwNres");}
              // Passes the mtb cut
              if (!(n_bjets_30==0 || (n_bjets_30>0 && mTb < 175.)))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowDM_NtNwNres_mTb");}
              // Passes the dPhi jet met cuts 
              if (!( (deltaPhi(signalJets_30.at(0)->mom(),metVec)>0.5 && deltaPhi(signalJets_30.at(1)->mom(),metVec)>0.15) && (n_jets_30==2 || deltaPhi(signalJets_30.at(2)->mom(),metVec)>0.15)))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowDM_NtNwNres_mTb_dPhi");}
              // Passes ISR
              if (!(n_ISR==1))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowDM_NtNwNres_mTb_dPhi_ISR");}
              // Passes MET/HT
              if (!((met/sqrt(Ht)) > 10))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("lowDM_NtNwNres_mTb_dPhi_ISR_METHt");}
              // Set Low deltaM preselection as passed :)
              low_dM_presel = true;
            }
            break;

        }
        while(true)
        {
            // High dM selection
            if (baseline_presel)
            {
              // Passes the Nj cut
              if (!(n_jets_30 >= 5))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("highDM_Nj");}
              // Passes the Nb cut
              if (!(n_bjets_30 >= 1))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("highDM_Nj_Nb");}
              // Passes the dPhi jet met cuts
              if (!( deltaPhi(signalJets_30.at(0)->mom(),metVec)>0.5 && deltaPhi(signalJets_30.at(1)->mom(),metVec)>0.5 && deltaPhi(signalJets_30.at(2)->mom(),metVec)>0.5 && deltaPhi(signalJets_30.at(3)->mom(),metVec)>0.5 ))
              {
                break;
              }
              if (doCutflow){ FILL_SIGNAL_REGION("highDM_Nj_Nb_dPhi");}
              // Set Low deltaM preselection as passed :)
              high_dM_presel = true;
            }
  
  
            // Applied all cuts
            break;
  
        }

        // If event doesn't pass Pre-selection, exit early
        if (!(low_dM_presel || high_dM_presel)) return;

        END_PRESELECTION

        /* Signal Regions */

        if (low_dM_presel)
        {
          if (n_jets_30>=2 && n_jets_30<=5 && n_bjets_30==0 && n_SV==0 && signalISRJets.at(0)->pT()>500.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-0_2Nj5_Nb0_Nsv0_500ISR_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-1_2Nj5_Nb0_Nsv0_500ISR_550MET650");}
            else if (met>=650. && met<750.){ FILL_SIGNAL_REGION("lowDM-2_2Nj5_Nb0_Nsv0_500ISR_650MET750");}
            else if (met>=750.){ FILL_SIGNAL_REGION("lowDM-3_2Nj5_Nb0_Nsv0_500ISR_750MET");}
          }
          else if (n_jets_30>=6 && n_bjets_30==0 && n_SV==0 && signalISRJets.at(0)->pT()>500.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-4_6Nj_Nb0_Nsv0_500ISR_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-5_6Nj_Nb0_Nsv0_500ISR_550MET650");}
            else if (met>=650. && met<750.){ FILL_SIGNAL_REGION("lowDM-6_6Nj_Nb0_Nsv0_500ISR_650MET750");}
            else if (met>=750.){ FILL_SIGNAL_REGION("lowDM-7_6Nj_Nb0_Nsv0_500ISR_750MET");}
          }
          else if (n_jets_30>=2 && n_jets_30<=5 && n_bjets_30==0 && n_SV>=1 && signalISRJets.at(0)->pT()>500.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-8_2Nj5_Nb0_1Nsv_500ISR_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-9_2Nj5_Nb0_1Nsv_500ISR_550MET650");}
            else if (met>=650. && met<750.){ FILL_SIGNAL_REGION("lowDM-10_2Nj5_Nb0_1Nsv_500ISR_650MET750");}
            else if (met>=750.){ FILL_SIGNAL_REGION("lowDM-11_2Nj5_Nb0_1Nsv_500ISR_750MET");}
          }
          else if (n_jets_30>=6 && n_bjets_30==0 && n_SV>=1 && signalISRJets.at(0)->pT()>500.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-12_6Nj_Nb0_1Nsv_500ISR_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-13_6Nj_Nb0_1Nsv_500ISR_550MET650");}
            else if (met>=650. && met<750.){ FILL_SIGNAL_REGION("lowDM-14_6Nj_Nb0_1Nsv_500ISR_650MET750");}
            else if (met>=750.){ FILL_SIGNAL_REGION("lowDM-15_6Nj_Nb0_1Nsv_500ISR_750MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30==1 && n_SV==0 && mTb<175. && signalISRJets.at(0)->pT()>300. && signalISRJets.at(0)->pT()<=500. && pTb>20. && pTb<=40.)
          {
            if (met>=300. && met<400.){ FILL_SIGNAL_REGION("lowDM-16_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("lowDM-17_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_400MET500");}
            else if (met>=500. && met<600.){ FILL_SIGNAL_REGION("lowDM-18_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_500MET600");}
            else if (met>=600.){ FILL_SIGNAL_REGION("lowDM-19_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_600MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30==1 && n_SV==0 && mTb<175. && signalISRJets.at(0)->pT()>300. && signalISRJets.at(0)->pT()<=500. && pTb>40. && pTb<=70.)
          {
            if (met>=300. && met<400.){ FILL_SIGNAL_REGION("lowDM-20_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("lowDM-21_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_400MET500");}
            else if (met>=500. && met<600.){ FILL_SIGNAL_REGION("lowDM-22_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_500MET600");}
            else if (met>=600.){ FILL_SIGNAL_REGION("lowDM-23_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_600MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30==1 && n_SV==0 && mTb<175. && signalISRJets.at(0)->pT()>300. && signalISRJets.at(0)->pT()<=500. && pTb>20. && pTb<=40.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-24_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-25_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_550MET650");}
            else if (met>=650. && met<750.){ FILL_SIGNAL_REGION("lowDM-26_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_650MET750");}
            else if (met>=750.){ FILL_SIGNAL_REGION("lowDM-27_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_750MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30==1 && n_SV==0 && mTb<175. && signalISRJets.at(0)->pT()>500. && pTb>40. && pTb<=70.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-28_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-29_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_550MET650");}
            else if (met>=650. && met<750.){ FILL_SIGNAL_REGION("lowDM-30_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_650MET750");}
            else if (met>=750.){ FILL_SIGNAL_REGION("lowDM-31_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_750MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30==1 && n_SV>=1 && mTb<175. && signalISRJets.at(0)->pT()>300. && pTb>20. && pTb<=40.)
          {
            if (met>=300. && met<400.){ FILL_SIGNAL_REGION("lowDM-32_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("lowDM-33_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_400MET500");}
            else if (met>=500.){ FILL_SIGNAL_REGION("lowDM-34_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_500MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30>=2 && mTb<175. && signalISRJets.at(0)->pT()>300. && signalISRJets.at(0)->pT()<=500 && pTb>40. && pTb<=80.)
          {
            if (met>=300. && met<400.){ FILL_SIGNAL_REGION("lowDM-35_2Nj_2Nb_mTb175_300ISR500_40pTb80_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("lowDM-36_2Nj_2Nb_mTb175_300ISR500_40pTb80_400MET500");}
            else if (met>=500.){ FILL_SIGNAL_REGION("lowDM-37_2Nj_2Nb_mTb175_300ISR500_40pTb80_500MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30>=2 && mTb<175. && signalISRJets.at(0)->pT()>300. && signalISRJets.at(0)->pT()<=500 && pTb>80. && pTb<=140.)
          {
            if (met>=300. && met<400.){ FILL_SIGNAL_REGION("lowDM-38_2Nj_2Nb_mTb175_300ISR500_80pTb140_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("lowDM-39_2Nj_2Nb_mTb175_300ISR500_80pTb140_400MET500");}
            else if (met>=500.){ FILL_SIGNAL_REGION("lowDM-40_2Nj_2Nb_mTb175_300ISR500_80pTb140_500MET");}
          }
          else if (n_jets_30>=7 && n_bjets_30>=2 && mTb<175. && signalISRJets.at(0)->pT()>300. && signalISRJets.at(0)->pT()<=500 && pTb>140.)
          {
            if (met>=300. && met<400.){ FILL_SIGNAL_REGION("lowDM-41_7Nj_2Nb_mTb175_300ISR500_140pTb_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("lowDM-42_7Nj_2Nb_mTb175_300ISR500_140pTb_400MET500");}
            else if (met>=500.){ FILL_SIGNAL_REGION("lowDM-43_7Nj_2Nb_mTb175_300ISR500_140pTb_500MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30>=2 && mTb<175. && signalISRJets.at(0)->pT()>500. && pTb>40. && pTb<=80.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-44_2Nj_2Nb_mTb175_500ISR_40pTb80_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-45_2Nj_2Nb_mTb175_500ISR_40pTb80_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("lowDM-46_2Nj_2Nb_mTb175_500ISR_40pTb80_650MET");}
          }
          else if (n_jets_30>=2 && n_bjets_30>=2 && mTb<175. && signalISRJets.at(0)->pT()>500. && pTb>80. && pTb<=140.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-47_2Nj_2Nb_mTb175_500ISR_80pTb140_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-48_2Nj_2Nb_mTb175_500ISR_80pTb140_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("lowDM-49_2Nj_2Nb_mTb175_500ISR_80pTb140_650MET");}
          }
          else if (n_jets_30>=7 && n_bjets_30>=2 && mTb<175. && signalISRJets.at(0)->pT()>300. && pTb>140.)
          {
            if (met>=450. && met<550.){ FILL_SIGNAL_REGION("lowDM-50_7Nj_2Nb_mTb175_300ISR_140pTb_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("lowDM-51_7Nj_2Nb_mTb175_300ISR_140pTb_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("lowDM-52_7Nj_2Nb_mTb175_300ISR_140pTb_650MET");}
          }
        }
        else if (high_dM_presel)
        {
          if (mTb<175. && n_jets_30>=7 && n_bjets_30==1 && n_MergedTop>=0 && n_W>=0 && n_ResolvedTop>=1 && Ht>300.)
          {
            if (met>=250. && met<300.){ FILL_SIGNAL_REGION("highDM-53_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_250MET300");}
            else if (met>=300. && met<400.){ FILL_SIGNAL_REGION("highDM-54_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("highDM-55_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_400MET500");}
            else if (met>=500.){ FILL_SIGNAL_REGION("highDM-56_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_500MET");}
          }
          else if (mTb<175. && n_jets_30>=7 && n_bjets_30>=2 && n_MergedTop>=0 && n_W>=0 && n_ResolvedTop>=1 && Ht>300.)
          {
            if (met>=250. && met<300.){ FILL_SIGNAL_REGION("highDM-57_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_250MET300");}
            else if (met>=300. && met<400.){ FILL_SIGNAL_REGION("highDM-58_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_300MET400");}
            else if (met>=400. && met<500.){ FILL_SIGNAL_REGION("highDM-59_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_400MET500");}
            else if (met>=500.){ FILL_SIGNAL_REGION("highDM-60_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_500MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==0 && Ht>1000.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-61_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-62_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-63_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_450MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-64_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=2 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==0 && Ht>1000.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-65_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-66_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-67_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_450MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-68_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop>=1 && n_W==0 && n_ResolvedTop==0 && Ht>300. && Ht<=1000.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-69_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_250MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-70_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-71_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop>=1 && n_W==0 && n_ResolvedTop==0 && Ht>1000. && Ht<1500.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-72_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_250MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-73_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-74_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop>=1 && n_W==0 && n_ResolvedTop==0 && Ht>1500.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-75_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_250MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-76_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-77_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop==0 && n_W>=1 && n_ResolvedTop==0 && Ht>300. && Ht<=1300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-78_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-79_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_350MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-80_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop==0 && n_W>=1 && n_ResolvedTop==0 && Ht>1300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-81_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-82_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_350MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-83_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop==0 && n_W==0 && n_ResolvedTop>=1 && Ht>300. && Ht<=1000.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-84_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-85_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-86_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-87_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-88_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop==0 && n_W==0 && n_ResolvedTop>=1 && Ht>1000. && Ht<=1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-89_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-90_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-91_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-92_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-93_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop==0 && n_W==0 && n_ResolvedTop>=1 && Ht>1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-94_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-95_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-96_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-97_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-98_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop>=1 && n_W>=1 && n_ResolvedTop==0 && Ht>300.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-99_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht_250MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-100_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop>=1 && n_W==0 && n_ResolvedTop>=1 && Ht>300.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-101_175mTb_5Nj_Nb1_1Nt_0Nw_1Nres_300Ht_250MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-102_175mTb_5Nj_Nb1_1Nt_0Nw_1Nres_300Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==1 && n_MergedTop==0 && n_W>=1 && n_ResolvedTop>=1 && Ht>300.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-103_175mTb_5Nj_Nb1_0Nt_1Nw_1Nres_300Ht_250MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-104_175mTb_5Nj_Nb1_0Nt_1Nw_1Nres_300Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==0 && Ht>300. && Ht<=1000.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-105_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_250MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-106_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-107_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==0 && Ht>1000. && Ht<1500.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-108_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_250MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-109_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-110_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==0 && Ht>1500.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-111_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_250MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-112_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-113_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==1 && n_ResolvedTop==0 && Ht>300. && Ht<1300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-114_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-115_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_350MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-116_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==1 && n_ResolvedTop==0 && Ht>1300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-117_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-118_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_350MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-119_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==1 && Ht>300. && Ht<=1000.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-120_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-121_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-122_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-123_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-124_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==1 && Ht>1000. && Ht<=1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-125_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-126_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-127_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-128_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-129_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==1 && Ht>1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-130_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-131_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_350MET450");}
            else if (met>=450. && met<550.){ FILL_SIGNAL_REGION("highDM-132_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_450MET550");}
            else if (met>=550. && met<650.){ FILL_SIGNAL_REGION("highDM-133_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_550MET650");}
            else if (met>=650.){ FILL_SIGNAL_REGION("highDM-134_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_650MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==1 && n_W==1 && n_ResolvedTop==0 && Ht>300.)
          {
            if (met>=250. && met<450.){ FILL_SIGNAL_REGION("highDM-135_175mTb_5Nj_2Nb_1Nt_1Nw_0Nres_300Ht_250MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-136_175mTb_5Nj_2Nb_1Nt_1Nw_0Nres_300Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==1 && Ht>300. && Ht<=1300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-137_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-138_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_350MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-139_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==1 && Ht>1300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-140_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_250MET350");}
            else if (met>=350. && met<450.){ FILL_SIGNAL_REGION("highDM-141_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_350MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-142_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==1 && n_ResolvedTop==1 && Ht>300.)
          {
            if (met>=250. && met<550.){ FILL_SIGNAL_REGION("highDM-143_175mTb_5Nj_2Nb_0Nt_1Nw_1Nres_300Ht_250MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-144_175mTb_5Nj_2Nb_0Nt_1Nw_1Nres_300Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==2 && n_W==0 && n_ResolvedTop==0 && Ht>300.)
          {
            if (met>=250. && met<450.){ FILL_SIGNAL_REGION("highDM-145_175mTb_5Nj_2Nb_2Nt_0Nw_0Nres_300Ht_250MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-146_175mTb_5Nj_2Nb_2Nt_0Nw_0Nres_300Ht_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==2 && n_ResolvedTop==0 && Ht>300.)
          {
            if (met>=250.){ FILL_SIGNAL_REGION("highDM-147_175mTb_5Nj_2Nb_0Nt_2Nw_0Nres_300Ht_250MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==2 && Ht>300. && Ht<=1300.)
          {
            if (met>=250. && met<450.){ FILL_SIGNAL_REGION("highDM-148_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_300Ht1300_250MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-149_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_300Ht1300_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==2 && Ht>1300.)
          {
            if (met>=250. && met<450.){ FILL_SIGNAL_REGION("highDM-150_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_1300Ht_250MET450");}
            else if (met>=450.){ FILL_SIGNAL_REGION("highDM-151_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_1300Ht_450MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30==2 && (n_MergedTop+n_W+n_ResolvedTop)>=3 && Ht>300.)
          {
            if (met>=250.){ FILL_SIGNAL_REGION("highDM-152_175mTb_5Nj_2Nb_3NtNwNres_300Ht_250MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==0 && Ht>300. && Ht<=1300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-153_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_250MET350");}
            else if (met>=350. && met<550.){ FILL_SIGNAL_REGION("highDM-154_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_350MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-155_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==0 && Ht>1000. && Ht<=1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-156_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_250MET350");}
            else if (met>=350. && met<550.){ FILL_SIGNAL_REGION("highDM-157_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_350MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-158_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==0 && Ht>1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-159_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_250MET350");}
            else if (met>=350. && met<550.){ FILL_SIGNAL_REGION("highDM-160_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_350MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-161_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==0 && n_W==1 && n_ResolvedTop==0 && Ht>300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-162_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_250MET350");}
            else if (met>=350. && met<550.){ FILL_SIGNAL_REGION("highDM-163_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_350MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-164_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==1 && Ht>300. && Ht<=1000.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-165_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_250MET350");}
            else if (met>=350. && met<550.){ FILL_SIGNAL_REGION("highDM-166_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_350MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-167_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==1 && Ht>1000. && Ht<=1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-168_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_250MET350");}
            else if (met>=350. && met<550.){ FILL_SIGNAL_REGION("highDM-169_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_350MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-170_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==1 && Ht>1500.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-171_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_250MET350");}
            else if (met>=350. && met<550.){ FILL_SIGNAL_REGION("highDM-172_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_350MET550");}
            else if (met>=550.){ FILL_SIGNAL_REGION("highDM-173_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_550MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==1 && n_W==1 && n_ResolvedTop==0 && Ht>300.)
          {
            if (met>=250.){ FILL_SIGNAL_REGION("highDM-174_175mTb_5Nj_3Nb_1Nt_1Nw_0Nres_300Ht_250MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==1 && n_W==0 && n_ResolvedTop==1 && Ht>300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-175_175mTb_5Nj_3Nb_1Nt_0Nw_1Nres_300Ht_250MET350");}
            else if (met>=350.){ FILL_SIGNAL_REGION("highDM-176_175mTb_5Nj_3Nb_1Nt_0Nw_1Nres_300Ht_350MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==0 && n_W==1 && n_ResolvedTop==1 && Ht>300.)
          {
            if (met>=250.){ FILL_SIGNAL_REGION("highDM-177_175mTb_5Nj_3Nb_0Nt_1Nw_1Nres_300Ht_250MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==2 && n_W==0 && n_ResolvedTop==0 && Ht>300.)
          {
            if (met>=250.){ FILL_SIGNAL_REGION("highDM-178_175mTb_5Nj_3Nb_2Nt_0Nw_0Nres_300Ht_250MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==2 && n_W==0 && n_ResolvedTop==2 && Ht>300.)
          {
            if (met>=250.){ FILL_SIGNAL_REGION("highDM-179_175mTb_5Nj_3Nb_0Nt_2Nw_0Nres_300Ht_250MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && n_MergedTop==0 && n_W==0 && n_ResolvedTop==2 && Ht>300.)
          {
            if (met>=250. && met<350.){ FILL_SIGNAL_REGION("highDM-180_175mTb_5Nj_3Nb_0Nt_0Nw_2Nres_300Ht_250MET350");}
            else if (met>=350.){ FILL_SIGNAL_REGION("highDM-181_175mTb_5Nj_3Nb_0Nt_0Nw_2Nres_300Ht_350MET");}
          }
          else if (mTb>175. && n_jets_30>=5 && n_bjets_30>=3 && (n_MergedTop+n_W+n_ResolvedTop)>=3 && Ht>300.)
          {
            if (met>=250.){ FILL_SIGNAL_REGION("highDM-182_175mTb_5Nj_3Nb_3NtNwNres_300Ht_250MET");}
          }
        }

      } // End run function

      // This function can be overridden by the derived SR-specific classes
      virtual void collect_results()
      {
        // Obs. Exp. Err.

        if (doCutflow)
        {
            COMMIT_SIGNAL_REGION("Total", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj_0e0mu", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("baseline_MET_Nj_0e0mu_0tau_Ht", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowDM_NtNwNres", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowDM_NtNwNres_mTb", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowDM_NtNwNres_mTb_dPhi", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowDM_NtNwNres_mTb_dPhi_ISR", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("lowDM_NtNwNres_mTb_dPhi_ISR_METHt", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("highDM_Nj", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("highDM_Nj_Nb", 1., 1., 1.);
            COMMIT_SIGNAL_REGION("highDM_Nj_Nb_dPhi", 1., 1., 1.);
        }

        // low dM 53 bins
        COMMIT_SIGNAL_REGION("lowDM-0_2Nj5_Nb0_Nsv0_500ISR_450MET550", 7538, 7840., 585.);
        COMMIT_SIGNAL_REGION("lowDM-1_2Nj5_Nb0_Nsv0_500ISR_550MET650", 4920, 5120., 425.);
        COMMIT_SIGNAL_REGION("lowDM-2_2Nj5_Nb0_Nsv0_500ISR_650MET750", 2151, 2300., 220.);
        COMMIT_SIGNAL_REGION("lowDM-3_2Nj5_Nb0_Nsv0_500ISR_750MET", 1780, 1950., 190.);

        COMMIT_SIGNAL_REGION("lowDM-4_6Nj_Nb0_Nsv0_500ISR_450MET550", 277, 270., 19.);
        COMMIT_SIGNAL_REGION("lowDM-5_6Nj_Nb0_Nsv0_500ISR_550MET650", 146, 143., 14.);
        COMMIT_SIGNAL_REGION("lowDM-6_6Nj_Nb0_Nsv0_500ISR_650MET750", 63, 76., 32.);
        COMMIT_SIGNAL_REGION("lowDM-7_6Nj_Nb0_Nsv0_500ISR_750MET", 85, 69.4, 8.2);

        COMMIT_SIGNAL_REGION("lowDM-8_2Nj5_Nb0_1Nsv_500ISR_450MET550", 161, 205., 19.);
        COMMIT_SIGNAL_REGION("lowDM-9_2Nj5_Nb0_1Nsv_500ISR_550MET650", 126, 113., 13.5);
        COMMIT_SIGNAL_REGION("lowDM-10_2Nj5_Nb0_1Nsv_500ISR_650MET750", 67, 60.3, 8.2);
        COMMIT_SIGNAL_REGION("lowDM-11_2Nj5_Nb0_1Nsv_500ISR_750MET", 39, 40.0, 6.1);

        COMMIT_SIGNAL_REGION("lowDM-12_6Nj_Nb0_1Nsv_500ISR_450MET550", 12, 7.8, 1.85);
        COMMIT_SIGNAL_REGION("lowDM-13_6Nj_Nb0_1Nsv_500ISR_550MET650", 4, 3.8, 1.2);
        COMMIT_SIGNAL_REGION("lowDM-14_6Nj_Nb0_1Nsv_500ISR_650MET750", 2, 2.6, 1.3);
        COMMIT_SIGNAL_REGION("lowDM-15_6Nj_Nb0_1Nsv_500ISR_750MET", 3, 3.8, 1.55);

        COMMIT_SIGNAL_REGION("lowDM-16_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_300MET400", 2383, 2540., 165.);
        COMMIT_SIGNAL_REGION("lowDM-17_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_400MET500", 456, 501., 41.);
        COMMIT_SIGNAL_REGION("lowDM-18_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_500MET600", 68, 63., 9.7);
        COMMIT_SIGNAL_REGION("lowDM-19_2Nj_Nb1_Nsv0_mTb175_300ISR500_20pTb40_600MET", 14, 9.7, 2.5);

        COMMIT_SIGNAL_REGION("lowDM-20_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_300MET400", 1250, 1295., 87.5);
        COMMIT_SIGNAL_REGION("lowDM-21_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_400MET500", 222, 201., 21.);
        COMMIT_SIGNAL_REGION("lowDM-22_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_500MET600", 29, 18.6, 4.7);
        COMMIT_SIGNAL_REGION("lowDM-23_2Nj_Nb1_Nsv0_mTb175_300ISR500_40pTb70_600MET", 5, 3.8, 1.6);

        COMMIT_SIGNAL_REGION("lowDM-24_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_450MET550", 164, 185., 17.);
        COMMIT_SIGNAL_REGION("lowDM-25_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_550MET650", 72, 82., 10.);
        COMMIT_SIGNAL_REGION("lowDM-26_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_650MET750", 33, 30.4, 5.9);
        COMMIT_SIGNAL_REGION("lowDM-27_2Nj_Nb1_Nsv0_mTb175_500ISR_20pTb40_750MET", 29, 26.8, 5.95);

        COMMIT_SIGNAL_REGION("lowDM-28_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_450MET550", 81, 125., 13.);
        COMMIT_SIGNAL_REGION("lowDM-29_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_550MET650", 34, 35., 5.7);
        COMMIT_SIGNAL_REGION("lowDM-30_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_650MET750", 18, 19.5, 4.5);
        COMMIT_SIGNAL_REGION("lowDM-31_2Nj_Nb1_Nsv0_mTb175_500ISR_40pTb70_750MET", 12, 12.2, 3.7);

        COMMIT_SIGNAL_REGION("lowDM-32_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_300MET400", 128, 127., 19.);
        COMMIT_SIGNAL_REGION("lowDM-33_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_400MET500", 42, 29.3, 5.6);
        COMMIT_SIGNAL_REGION("lowDM-34_2Nj_Nb1_1Nsv_mTb175_300ISR_20pTb40_500MET", 16, 17.9, 4.2);

        COMMIT_SIGNAL_REGION("lowDM-35_2Nj_2Nb_mTb175_300ISR500_40pTb80_300MET400", 244, 253., 25.);
        COMMIT_SIGNAL_REGION("lowDM-36_2Nj_2Nb_mTb175_300ISR500_40pTb80_400MET500", 47, 50., 11.);
        COMMIT_SIGNAL_REGION("lowDM-37_2Nj_2Nb_mTb175_300ISR500_40pTb80_500MET", 9, 10.6, 3.8);

        COMMIT_SIGNAL_REGION("lowDM-38_2Nj_2Nb_mTb175_300ISR500_80pTb140_300MET400", 443, 493., 43.);
        COMMIT_SIGNAL_REGION("lowDM-39_2Nj_2Nb_mTb175_300ISR500_80pTb140_400MET500", 82, 107., 14.);
        COMMIT_SIGNAL_REGION("lowDM-40_2Nj_2Nb_mTb175_300ISR500_80pTb140_500MET", 8, 14.5, 3.3);

        COMMIT_SIGNAL_REGION("lowDM-41_7Nj_2Nb_mTb175_300ISR500_140pTb_300MET400", 54, 65.1, 8.4);
        COMMIT_SIGNAL_REGION("lowDM-42_7Nj_2Nb_mTb175_300ISR500_140pTb_400MET500", 15, 14.7, 3.2);
        COMMIT_SIGNAL_REGION("lowDM-43_7Nj_2Nb_mTb175_300ISR500_140pTb_500MET", 2, 10.0, 6.2);

        COMMIT_SIGNAL_REGION("lowDM-44_2Nj_2Nb_mTb175_500ISR_40pTb80_450MET550", 22, 12.7, 3.5);
        COMMIT_SIGNAL_REGION("lowDM-45_2Nj_2Nb_mTb175_500ISR_40pTb80_550MET650", 9, 7.6, 2.5);
        COMMIT_SIGNAL_REGION("lowDM-46_2Nj_2Nb_mTb175_500ISR_40pTb80_650MET", 4, 3.8, 2.0);

        COMMIT_SIGNAL_REGION("lowDM-47_2Nj_2Nb_mTb175_500ISR_80pTb140_450MET550", 41, 35.4, 5.5);
        COMMIT_SIGNAL_REGION("lowDM-48_2Nj_2Nb_mTb175_500ISR_80pTb140_550MET650", 14, 15.4, 3.7);
        COMMIT_SIGNAL_REGION("lowDM-49_2Nj_2Nb_mTb175_500ISR_80pTb140_650MET", 8, 9.0, 2.7);

        COMMIT_SIGNAL_REGION("lowDM-50_7Nj_2Nb_mTb175_300ISR_140pTb_450MET550", 20, 19., 3.6);
        COMMIT_SIGNAL_REGION("lowDM-51_7Nj_2Nb_mTb175_300ISR_140pTb_550MET650", 6, 6.5, 1.95);
        COMMIT_SIGNAL_REGION("lowDM-52_7Nj_2Nb_mTb175_300ISR_140pTb_650MET", 4, 4.2, 3.2);

        // high dM 53 bins
        COMMIT_SIGNAL_REGION("highDM-53_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_250MET300", 277, 231., 21.);
        COMMIT_SIGNAL_REGION("highDM-54_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_300MET400", 130, 122., 12.);
        COMMIT_SIGNAL_REGION("highDM-55_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_400MET500", 126, 29.5, 5.5);
        COMMIT_SIGNAL_REGION("highDM-56_mTb175_7Nj_Nb1_0Nt_0Nw_1Nres_300Ht_500MET", 9, 9.7, 2.9);

        COMMIT_SIGNAL_REGION("highDM-57_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_250MET300", 669, 668., 44.);
        COMMIT_SIGNAL_REGION("highDM-58_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_300MET400", 345, 363., 26.);
        COMMIT_SIGNAL_REGION("highDM-59_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_400MET500", 54, 70., 10.5);
        COMMIT_SIGNAL_REGION("highDM-60_mTb175_7Nj_Nb2_0Nt_0Nw_1Nres_300Ht_500MET", 21, 19.3, 3.7);

        COMMIT_SIGNAL_REGION("highDM-61_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_250MET350", 639, 526., 15.);
        COMMIT_SIGNAL_REGION("highDM-62_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_350MET450", 233, 206., 5.45);
        COMMIT_SIGNAL_REGION("highDM-63_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_450MET550", 124, 118., 15.5);
        COMMIT_SIGNAL_REGION("highDM-64_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1000Ht_550MET", 179, 177., 29.);

        COMMIT_SIGNAL_REGION("highDM-65_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_250MET350", 139, 135., 15.);
        COMMIT_SIGNAL_REGION("highDM-66_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_350MET450", 64, 44.2, 5.45);
        COMMIT_SIGNAL_REGION("highDM-67_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_450MET550", 23, 23.2, 3.85);
        COMMIT_SIGNAL_REGION("highDM-68_175mTb_5Nj_Nb2_0Nt_0Nw_0Nres_1000Ht_550MET", 45, 34.8, 5.75);

        COMMIT_SIGNAL_REGION("highDM-69_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_250MET550", 340, 428., 68.);
        COMMIT_SIGNAL_REGION("highDM-70_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_550MET650", 17, 14.9, 2.5);
        COMMIT_SIGNAL_REGION("highDM-71_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht1000_650MET", 6, 7.5, 1.45);

        COMMIT_SIGNAL_REGION("highDM-72_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_250MET550", 94, 101., 14.5);
        COMMIT_SIGNAL_REGION("highDM-73_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_550MET650", 2, 5.2, 1.05);
        COMMIT_SIGNAL_REGION("highDM-74_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1000Ht1500_650MET", 4, 6.9, 1.35);

        COMMIT_SIGNAL_REGION("highDM-75_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_250MET550", 28, 32.2, 5.);
        COMMIT_SIGNAL_REGION("highDM-76_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_550MET650", 4, 1.38, 0.42);
        COMMIT_SIGNAL_REGION("highDM-77_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_1500Ht_650MET", 3, 1.99, 0.48);

        COMMIT_SIGNAL_REGION("highDM-78_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_250MET350", 351, 406., 39.);
        COMMIT_SIGNAL_REGION("highDM-79_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_350MET450", 90, 98., 10.5);
        COMMIT_SIGNAL_REGION("highDM-80_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_300Ht1300_450MET", 29, 36.4, 5.0);

        COMMIT_SIGNAL_REGION("highDM-81_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_250MET350", 13, 11., 1.45);
        COMMIT_SIGNAL_REGION("highDM-82_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_350MET450", 4, 4.16, 0.815);
        COMMIT_SIGNAL_REGION("highDM-83_175mTb_5Nj_Nb1_0Nt_0Nw_0Nres_1300Ht_450MET", 4, 4.56, 0.81);

        COMMIT_SIGNAL_REGION("highDM-84_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_250MET350", 2506, 2670., 185.);
        COMMIT_SIGNAL_REGION("highDM-85_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_350MET450", 483, 490., 42.);
        COMMIT_SIGNAL_REGION("highDM-86_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_450MET550", 92, 100., 11.5);
        COMMIT_SIGNAL_REGION("highDM-87_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_550MET650", 25, 24.4, 3.8);
        COMMIT_SIGNAL_REGION("highDM-88_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_300Ht1000_650MET", 10, 8.8, 1.65);

        COMMIT_SIGNAL_REGION("highDM-89_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_250MET350", 69, 67., 7.3);
        COMMIT_SIGNAL_REGION("highDM-90_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_350MET450", 34, 28.2, 4.0);
        COMMIT_SIGNAL_REGION("highDM-91_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_450MET550", 9, 11.8, 1.8);
        COMMIT_SIGNAL_REGION("highDM-92_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_550MET650", 7, 6.1, 1.15);
        COMMIT_SIGNAL_REGION("highDM-93_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1000Ht1500_650MET", 3, 8.2, 1.55);

        COMMIT_SIGNAL_REGION("highDM-94_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_250MET350", 8, 10.5, 2.1);
        COMMIT_SIGNAL_REGION("highDM-95_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_350MET450", 1, 4.07, 0.88);
        COMMIT_SIGNAL_REGION("highDM-96_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_450MET550", 1, 1.7, 0.45);
        COMMIT_SIGNAL_REGION("highDM-97_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_550MET650", 0, 0.78, 0.25);
        COMMIT_SIGNAL_REGION("highDM-98_175mTb_5Nj_Nb1_0Nt_0Nw_1Nres_1500Ht_650MET", 4, 2.09, 0.52);

        COMMIT_SIGNAL_REGION("highDM-99_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht_250MET550", 2, 6.3, 1.1);
        COMMIT_SIGNAL_REGION("highDM-100_175mTb_5Nj_Nb1_1Nt_1Nw_0Nres_300Ht_550MET", 1, 0.71, 0.21);

        COMMIT_SIGNAL_REGION("highDM-101_175mTb_5Nj_Nb1_1Nt_0Nw_1Nres_300Ht_250MET550", 15, 10.9, 1.65);
        COMMIT_SIGNAL_REGION("highDM-102_175mTb_5Nj_Nb1_1Nt_0Nw_1Nres_300Ht_550MET", 1, 1.68, 0.34);

        COMMIT_SIGNAL_REGION("highDM-103_175mTb_5Nj_Nb1_0Nt_1Nw_1Nres_300Ht_250MET550", 34, 32.2, 4.2);
        COMMIT_SIGNAL_REGION("highDM-104_175mTb_5Nj_Nb1_0Nt_1Nw_1Nres_300Ht_550MET", 1, 1.05, 0.255);

        COMMIT_SIGNAL_REGION("highDM-105_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_250MET550", 79, 97., 15.5);
        COMMIT_SIGNAL_REGION("highDM-106_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_550MET650", 3, 5.1, 1.15);
        COMMIT_SIGNAL_REGION("highDM-107_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_300Ht1000_650MET", 2, 3.45, 0.78);

        COMMIT_SIGNAL_REGION("highDM-108_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_250MET550", 36, 30.2, 1.95);
        COMMIT_SIGNAL_REGION("highDM-109_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_550MET650", 3, 1.3, 0.41);
        COMMIT_SIGNAL_REGION("highDM-110_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1000Ht1500_650MET", 4, 2.46, 0.62);

        COMMIT_SIGNAL_REGION("highDM-111_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_250MET550", 9, 10.7, 1.95);
        COMMIT_SIGNAL_REGION("highDM-112_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_550MET650", 1, 0.86, 0.41);
        COMMIT_SIGNAL_REGION("highDM-113_175mTb_5Nj_2Nb_1Nt_0Nw_0Nres_1500Ht_650MET", 0, 0.96, 0.34);

        COMMIT_SIGNAL_REGION("highDM-114_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_250MET350", 44, 78.4, 8.7);
        COMMIT_SIGNAL_REGION("highDM-115_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_350MET450", 19, 17.5, 2.95);
        COMMIT_SIGNAL_REGION("highDM-116_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_300Ht1300_450MET", 10, 6.8, 1.05);

        COMMIT_SIGNAL_REGION("highDM-117_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_250MET350", 0, 2.86, 0.655);
        COMMIT_SIGNAL_REGION("highDM-118_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_350MET450", 0, 1.27, 0.48);
        COMMIT_SIGNAL_REGION("highDM-119_175mTb_5Nj_2Nb_0Nt_1Nw_0Nres_1300Ht_450MET", 2, 1.13, 0.37);

        COMMIT_SIGNAL_REGION("highDM-120_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_250MET350", 454, 492., 38.5);
        COMMIT_SIGNAL_REGION("highDM-121_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_350MET450", 114, 113., 11.);
        COMMIT_SIGNAL_REGION("highDM-122_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_450MET550", 35, 29.3, 4.05);
        COMMIT_SIGNAL_REGION("highDM-123_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_550MET650", 6, 8.3, 1.8);
        COMMIT_SIGNAL_REGION("highDM-124_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_300Ht1000_650MET", 4, 3.9, 1.);

        COMMIT_SIGNAL_REGION("highDM-125_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_250MET350", 27, 21.9, 3.9);
        COMMIT_SIGNAL_REGION("highDM-126_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_350MET450", 5, 7.8, 2.75);
        COMMIT_SIGNAL_REGION("highDM-127_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_450MET550", 4, 3.45, 0.735);
        COMMIT_SIGNAL_REGION("highDM-128_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_550MET650", 2, 1.77, 0.51);
        COMMIT_SIGNAL_REGION("highDM-129_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1000Ht1500_650MET", 1, 2.68, 0.69);

        COMMIT_SIGNAL_REGION("highDM-130_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_250MET350", 4, 3.44, 0.71);
        COMMIT_SIGNAL_REGION("highDM-131_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_350MET450", 2, 1.59, 0.45);
        COMMIT_SIGNAL_REGION("highDM-132_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_450MET550", 1, 0.46, 0.21);
        COMMIT_SIGNAL_REGION("highDM-133_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_550MET650", 0, 0.4, 0.18);
        COMMIT_SIGNAL_REGION("highDM-134_175mTb_5Nj_2Nb_0Nt_0Nw_1Nres_1500Ht_650MET", 0, 0.76, 0.28);

        COMMIT_SIGNAL_REGION("highDM-135_175mTb_5Nj_2Nb_1Nt_1Nw_0Nres_300Ht_250MET550", 3, 1.54, 0.29);
        COMMIT_SIGNAL_REGION("highDM-136_175mTb_5Nj_2Nb_1Nt_1Nw_0Nres_300Ht_550MET", 0, 0.36, 0.09);

        COMMIT_SIGNAL_REGION("highDM-137_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_250MET350", 5, 5.9, 1.25);
        COMMIT_SIGNAL_REGION("highDM-138_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_350MET450", 5, 2.52, 0.555);
        COMMIT_SIGNAL_REGION("highDM-139_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_300Ht1300_450MET", 3, 4.1, 1.5);

        COMMIT_SIGNAL_REGION("highDM-140_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_250MET350", 2, 0.9, 0.2);
        COMMIT_SIGNAL_REGION("highDM-141_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_350MET450", 0, 0.38, 0.13);
        COMMIT_SIGNAL_REGION("highDM-142_175mTb_5Nj_2Nb_1Nt_0Nw_1Nres_1300Ht_450MET", 0, 0.64, 0.165);

        COMMIT_SIGNAL_REGION("highDM-143_175mTb_5Nj_2Nb_0Nt_1Nw_1Nres_300Ht_250MET550", 6, 10.9, 1.7);
        COMMIT_SIGNAL_REGION("highDM-144_175mTb_5Nj_2Nb_0Nt_1Nw_1Nres_300Ht_550MET", 0, 0.37, 0.09);

        COMMIT_SIGNAL_REGION("highDM-145_175mTb_5Nj_2Nb_2Nt_0Nw_0Nres_300Ht_250MET450", 2, 1.74, 0.425);
        COMMIT_SIGNAL_REGION("highDM-146_175mTb_5Nj_2Nb_2Nt_0Nw_0Nres_300Ht_450MET", 0, 0.56, 0.19);

        COMMIT_SIGNAL_REGION("highDM-147_175mTb_5Nj_2Nb_0Nt_2Nw_0Nres_300Ht_250MET", 0, 0.74, 0.26);

        COMMIT_SIGNAL_REGION("highDM-148_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_300Ht1300_250MET450", 19, 26.5, 3.9);
        COMMIT_SIGNAL_REGION("highDM-149_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_300Ht1300_450MET", 3, 3.45, 0.82);

        COMMIT_SIGNAL_REGION("highDM-150_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_1300Ht_250MET450", 0, 0.46, 0.19);
        COMMIT_SIGNAL_REGION("highDM-151_175mTb_5Nj_2Nb_0Nt_0Nw_2Nres_1300Ht_450MET", 0, 0.24, 0.15);

        COMMIT_SIGNAL_REGION("highDM-152_175mTb_5Nj_2Nb_3NtNwNres_300Ht_250MET", 1, 0.44, 0.25);

        COMMIT_SIGNAL_REGION("highDM-153_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_250MET350", 8, 11.1, 2.2);
        COMMIT_SIGNAL_REGION("highDM-154_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_350MET550", 6, 9.3, 1.9);
        COMMIT_SIGNAL_REGION("highDM-155_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_300Ht1000_550MET", 4, 1.82, 0.65);

        COMMIT_SIGNAL_REGION("highDM-156_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_250MET350", 4, 5.9, 1.3);
        COMMIT_SIGNAL_REGION("highDM-157_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_350MET550", 1, 2.13, 0.65);
        COMMIT_SIGNAL_REGION("highDM-158_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1000Ht1500_550MET", 1, 0.52, 0.18);

        COMMIT_SIGNAL_REGION("highDM-159_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_250MET350", 9, 4.1, 1.4);
        COMMIT_SIGNAL_REGION("highDM-160_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_350MET550", 2, 0.82, 0.42);
        COMMIT_SIGNAL_REGION("highDM-161_175mTb_5Nj_3Nb_1Nt_0Nw_0Nres_1500Ht_550MET", 0, 0.3, 0.145);

        COMMIT_SIGNAL_REGION("highDM-162_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_250MET350", 7, 19.8, 2.8);
        COMMIT_SIGNAL_REGION("highDM-163_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_350MET550", 2, 4.5, 1.25);
        COMMIT_SIGNAL_REGION("highDM-164_175mTb_5Nj_3Nb_0Nt_1Nw_0Nres_300Ht_550MET", 0, 0.78, 0.33);

        COMMIT_SIGNAL_REGION("highDM-165_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_250MET350", 105, 94.4, 8.9);
        COMMIT_SIGNAL_REGION("highDM-166_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_350MET550", 20, 26.5, 4.3);
        COMMIT_SIGNAL_REGION("highDM-167_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_300Ht1000_550MET", 1, 1.2, 0.36);

        COMMIT_SIGNAL_REGION("highDM-168_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_250MET350", 7, 7.2, 1.7);
        COMMIT_SIGNAL_REGION("highDM-169_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_350MET550", 3, 2.15, 0.61);
        COMMIT_SIGNAL_REGION("highDM-170_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1000Ht1500_550MET", 1, 0.73, 0.29);

        COMMIT_SIGNAL_REGION("highDM-171_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_250MET350", 4, 1.53, 0.51);
        COMMIT_SIGNAL_REGION("highDM-172_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_350MET550", 1, 0.7, 0.38);
        COMMIT_SIGNAL_REGION("highDM-173_175mTb_5Nj_3Nb_0Nt_0Nw_1Nres_1500Ht_550MET", 0, 0.53, 0.4);

        COMMIT_SIGNAL_REGION("highDM-174_175mTb_5Nj_3Nb_1Nt_1Nw_0Nres_300Ht_250MET", 0, 0.66, 0.21);

        COMMIT_SIGNAL_REGION("highDM-175_175mTb_5Nj_3Nb_1Nt_0Nw_1Nres_300Ht_250MET350", 2, 2.72, 0.73);
        COMMIT_SIGNAL_REGION("highDM-176_175mTb_5Nj_3Nb_1Nt_0Nw_1Nres_300Ht_350MET", 0, 2.23, 0.55);

        COMMIT_SIGNAL_REGION("highDM-177_175mTb_5Nj_3Nb_0Nt_1Nw_1Nres_300Ht_250MET", 1, 1.39, 0.61);

        COMMIT_SIGNAL_REGION("highDM-178_175mTb_5Nj_3Nb_2Nt_0Nw_0Nres_300Ht_250MET", 1, 0.9, 0.27);

        COMMIT_SIGNAL_REGION("highDM-179_175mTb_5Nj_3Nb_0Nt_2Nw_0Nres_300Ht_250MET", 0, 0.08, 0.03);

        COMMIT_SIGNAL_REGION("highDM-180_175mTb_5Nj_3Nb_0Nt_0Nw_2Nres_300Ht_250MET350", 6, 3.4, 1.1);
        COMMIT_SIGNAL_REGION("highDM-181_175mTb_5Nj_3Nb_0Nt_0Nw_2Nres_300Ht_350MET", 0, 1.33, 0.395);

        COMMIT_SIGNAL_REGION("highDM-182_175mTb_5Nj_3Nb_3NtNwNres_300Ht_250MET", 0, 0.11, 0.03);

        COMMIT_CUTFLOWS;

      }

    protected:
      void analysis_specific_reset()
      {
        for (auto& pair : _counters)
        {
          pair.second.reset();
        }
      }

    };

    // Factory fn
    DEFINE_ANALYSIS_FACTORY(CMS_13TeV_0LEPStop_137invfb)

  }
}
