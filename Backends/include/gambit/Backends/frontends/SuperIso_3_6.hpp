//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SuperIso backend v3.6
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Nazila Mahmoudi
///  \date   2016 Jul
///  \date   2018 Jan
///
///  \author Pat Scott
///  \date   2015 May
///
///  *********************************************



#define BACKENDNAME SuperIso
#define BACKENDLANG CC
#define VERSION 3.6
#define SAFE_VERSION 3_6
#define REFERENCE Mahmoudi:2007vz,Mahmoudi:2008tp,Mahmoudi:2009zz

LOAD_LIBRARY

// Can't do anything non-MSSM with SuperIso yet, besides Willson coefficients.
// If you want to expand this to work in the 2HDM, it should all just work out of the box if you set the
// parameters object up correctly in FlavBit and specify the model(s) as allowed here.
BE_ALLOW_MODELS(MSSM63atQ, MSSM63atMGUT, WC)

BE_FUNCTION(Init_param, void, (parameters*), "Init_param", "Init_param")
BE_FUNCTION(slha_adjust, void, (parameters*), "slha_adjust", "slha_adjust")

BE_FUNCTION(CW_calculator, void, (int, double*, double*, double*, double, const parameters*), "CW_calculator", "CW_calculator")
BE_FUNCTION(C_calculator_base1, void, (double*, double*, double*, double, double*, double*, double*, double, const parameters*), "C_calculator_base1", "C_calculator_base1")
BE_FUNCTION(C_calculator_base2, void, (double*, double*, double, double*, double*, double, const parameters*), "C_calculator_base2", "C_calculator_base2")
BE_FUNCTION(Cprime_calculator, void, (int, double*, std::complex<double>*, double, double, const parameters*), "Cprime_calculator", "Cprime_calculator")
BE_FUNCTION(CQ_calculator, void, (int, std::complex<double>*, std::complex<double>*, double, double, const parameters*), "CQ_calculator", "CQ_calculator")

BE_FUNCTION(alphas_running, double, (double, double,  double, const parameters*), "alphas_running", "alphas_running")

BE_FUNCTION(bsgamma, double, (double*, double*, double*, double*, double, double, const parameters*), "bsgamma", "bsgamma")
BE_FUNCTION(bsgamma_Ecut, double, (double*, double*, double*, double*, double, double, double, const parameters*), "bsgamma_Ecut", "bsgamma_Ecut")

BE_FUNCTION(Bsmumu, double, (double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "Bsmumu", "Bsmumu")
BE_FUNCTION(Bsmumu_untag, double, (double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "Bsmumu_untag", "Bsmumu_untag")
BE_FUNCTION(Bsll_untag, double, (int, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "Bsll_untag", "Bsll_untag")
BE_FUNCTION(Bmumu, double, (double*, double*, double*, std::complex<double>*, std::complex<double>*, const parameters*, double), "Bdmumu", "Bmumu")
BE_FUNCTION(Btaunu, double, (const parameters*), "Btaunu", "Btaunu")
BE_FUNCTION(BDtaunu, double, (const parameters*), "BDtaunu", "BDtaunu")
BE_FUNCTION(BDtaunu_BDenu, double, (const parameters*), "BDtaunu_BDenu", "BDtaunu_BDenu")
BE_FUNCTION(BDstartaunu_BDstarenu, double, (const parameters*), "BDstartaunu_BDstarenu", "BDstartaunu_BDstarenu")
BE_FUNCTION(Blnu, double, (int, const parameters*), "Blnu", "Blnu")

BE_FUNCTION(Kmunu_pimunu, double, (const parameters*), "Kmunu_pimunu", "Kmunu_pimunu")
BE_FUNCTION(Rmu23, double, (const parameters*), "Rmu23", "Rmu23")
BE_FUNCTION(Dstaunu, double, (const parameters*), "Dstaunu", "Dstaunu")
BE_FUNCTION(Dsmunu, double, (const parameters*), "Dsmunu", "Dsmunu")
BE_FUNCTION(Dmunu, double, (const parameters*), "Dmunu", "Dmunu")
BE_FUNCTION(muon_gm2, double, (const parameters*), "muon_gm2", "muon_gm2")
BE_FUNCTION(delta0, double, (double*, double*, double*, double*, double*, const parameters*, double, double, double), "delta0", "delta0")
BE_FUNCTION(BRBXsll_lowq2, double, (int, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "BRBXsll_lowq2", "BRBXsll_lowq2")
BE_FUNCTION(BRBXsll_highq2, double, (int, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "BRBXsll_highq2", "BRBXsll_highq2")
BE_FUNCTION(A_BXsll_lowq2, double, (int, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "A_BXsll_lowq2", "A_BXsll_lowq2")
BE_FUNCTION(A_BXsll_highq2, double, (int, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "A_BXsll_highq2", "A_BXsll_highq2")
BE_FUNCTION(A_BXsll_zero, double, (int, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "A_BXsll_zero", "A_BXsll_zero")
BE_FUNCTION(BRBKstarll, double, (int, int, double, double, double*, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "BRBKstarll", "BRBKstarll")
BE_FUNCTION(BRBKll, double, (int, int, double, double, double*, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "BRBKll", "BRBKll")
BE_FUNCTION(BRBsphill, double, (int, int, double, double, double*, double*, double*, double*, std::complex<double>*, std::complex<double>*, double*, std::complex<double>*, const parameters*, double), "BRBsphill", "BRBsphill")
BE_FUNCTION(AI_BKstarmumu, double, (double, double, double*, double*, double*, const parameters*, double), "AI_BKstarmumu", "AI_BKstarmumu")
BE_FUNCTION(AI_BKstarmumu_zero, double, (double*, double*, double*, const parameters*, double), "AI_BKstarmumu_zero", "AI_BKstarmumu_zero")
BE_FUNCTION(Bll, double, (int, double*, double*, double*, std::complex<double>*, std::complex<double>*, const parameters*, double), "Bdll", "Bll")
BE_FUNCTION(BRBDlnu, double, (int, int, double,  double, double*, const parameters*), "BRBDlnu", "BRBDlnu")
BE_FUNCTION(BRBDstarlnu, double, (int, int, double,  double, double*, const parameters*), "BRBDstarlnu", "BRBDstarlnu")
BE_FUNCTION(mb_1S, double , (const parameters*), "mb_1S", "mb_1S")

// Convenience functions:
BE_CONV_FUNCTION(BKstarmumu_CONV, Flav_KstarMuMu_obs, (const parameters*, double, double), "BKstarmumu_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(RKstar_CONV, double, (const parameters*, double, double), "RKstar_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(RK_CONV, double, (const parameters*, double, double), "RK_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(bsgamma_CONV, double, (const parameters*, double), "bsgamma_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(Bsll_untag_CONV, double, (const parameters*, int), "Bsll_untag_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(Bll_CONV, double, (const parameters*, int), "Bll_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(BRBXsmumu_lowq2_CONV, double, (const parameters*), "BRBXsmumu_lowq2_CONV",(MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(BRBXsmumu_highq2_CONV, double, (const parameters*), "BRBXsmumu_highq2_CONV",(MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(A_BXsmumu_lowq2_CONV, double, (const parameters*), "A_BXsmumu_lowq2_CONV",(MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(A_BXsmumu_highq2_CONV, double, (const parameters*), "A_BXsmumu_highq2_CONV",(MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(A_BXsmumu_zero_CONV, double, (const parameters*), "A_BXsmumu_zero_CONV",(MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(BRBXstautau_highq2_CONV, double, (const parameters*), "BRBXstautau_highq2_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(A_BXstautau_highq2_CONV, double, (const parameters*), "A_BXstautau_highq2_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(SI_AI_BKstarmumu_CONV, double, (const parameters*), "SI_AI_BKstarmumu_CONV", (MSSM63atQ, MSSM63atMGUT, WC))
BE_CONV_FUNCTION(SI_AI_BKstarmumu_zero_CONV, double, (const parameters*), "SI_AI_BKstarmumu_zero_CONV", (MSSM63atQ, MSSM63atMGUT, WC))

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
