//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SuperIso backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Nazila Mahmoudi
///         (nazila@cern.ch)
/// \date 2016 Jul
/// \date 2018 Jan
///
/// \author Pat Scott
///          (p.scott@imperial.ac.uk)
/// \date 2017 Mar, Apr
///
/// \author Marcin Chrzaszcz
///         (mchrzasz@cern.ch)
/// \date 2016
/// \date 2017
///
///  *********************************************

#include <sstream>
#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/SuperIso_3_6.hpp"
#include "gambit/Backends/backend_types/SuperIso.hpp"

/// Number of observables the SuperIso returns for B0 -> K(*) mu mu
#define Nobs_BKsll 30
#define Nobs_BKll 2


// Initialisation
BE_INI_FUNCTION{}
END_BE_INI_FUNCTION

// Convenience functions (definitions)
BE_NAMESPACE
{

  /// Helper functions to apply offsets to Wilson coefficients
  /// @{
  /// Note that we don't yet consider the impacts of modifying anything
  /// except Re(O_7), Re(O_9), Re(O_10), Q_1 and Q_2.
  void modify_WC(const parameters *param, double C0b[11])
  {
    C0b[7]+=param->Re_DeltaC7;
    C0b[9]+=param->Re_DeltaC9;
    C0b[10]+=param->Re_DeltaC10;
  }
  void modify_WC(const parameters *param, double C0b[11], std::complex<double> CQ0b[3])
  {
    modify_WC(param, C0b);
    CQ0b[1]+=std::complex<double>(param->Re_DeltaCQ1, param->Im_DeltaCQ1);
    CQ0b[2]+=std::complex<double>(param->Re_DeltaCQ2, param->Im_DeltaCQ2);
  }
  /// @}

  /// Helper function to double-check that SuperIso can handle the model.
  void check_model(const parameters *param, const str& where)
  {
    bool known_model = false;
    known_model = known_model or (param->model == -3 and param->SM == 1); // SM or a Flavour EFT model
    known_model = known_model or (param->model >= 0);                     // SUSY/2HDM/other BSM model that SuperIso can handle explicitly
    if (not known_model) backend_error().raise(where, "SuperIso convenience function called with incompatible model.");
  }

  /// B0 -> K*0 mu mu observables
  Flav_KstarMuMu_obs BKstarmumu_CONV(const parameters *param, double Q2_min, double Q2_max)
  {
    check_model(param, LOCAL_INFO);
    assert(std::abs(Q2_max-Q2_min)>0.01); // it's not safe to have such small bins => probably you are doing something wrong

    double C0b[11],C1b[11],C2b[11],C0w[11],C1w[11],C2w[11],Cpb[11];
    std::complex<double> CQ0b[3],CQ1b[3],CQpb[3];
    double obs[Nobs_BKsll+1];
    Flav_KstarMuMu_obs results;
    results.q2_min=Q2_min;
    results.q2_max=Q2_max;

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b_pole;

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    results.BR = BRBKstarll(2,0,byVal(Q2_min), byVal(Q2_max), byVal(obs),byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));

    // Fill the other results
    results.FL=obs[2];
    results.AFB=obs[1];
    results.S3=obs[25];
    results.S4=obs[26];
    results.S5=obs[27];
    results.S7=obs[28];
    results.S8=obs[29];
    results.S9=obs[30];

    return results;
  }

  /// RK* observables
  double RKstar_CONV(const parameters *param, double Q2_min, double Q2_max)
  {
    check_model(param, LOCAL_INFO);
    assert(std::abs(Q2_max-Q2_min)>0.01); // it's not safe to have such small bins => probably you are doing something wrong

    double C0b[11],C1b[11],C2b[11],C0w[11],C1w[11],C2w[11],Cpb[11];
    std::complex<double> CQ0b[3],CQ1b[3],CQpb[3];
    double C0be[11],C1be[11],C2be[11],C0we[11],C1we[11],C2we[11],Cpbe[11];
    std::complex<double> CQ0be[3],CQ1be[3],CQpbe[3];
    double obs[Nobs_BKsll+1];

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b_pole;

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    CW_calculator(1,byVal(C0we),byVal(C1we),byVal(C2we),byVal(mu_W),param);
    C_calculator_base1(byVal(C0we),byVal(C1we),byVal(C2we),byVal(mu_W),byVal(C0be),byVal(C1be),byVal(C2be),byVal(mu_b),param);
    CQ_calculator(1,byVal(CQ0be),byVal(CQ1be),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(1,byVal(Cpbe),byVal(CQpbe),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0be, CQ0be);

    return BRBKstarll(2,0,byVal(Q2_min), byVal(Q2_max), byVal(obs),byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b))/BRBKstarll(1,0,byVal(Q2_min), byVal(Q2_max), byVal(obs),byVal(C0be),byVal(C1be),byVal(C2be),byVal(CQ0be),byVal(CQ1be),byVal(Cpbe),byVal(CQpbe),param,byVal(mu_b));
  }
  
  /// RK observable
  double RK_CONV(const parameters *param, double Q2_min, double Q2_max)
  {
    check_model(param, LOCAL_INFO);
    assert(std::abs(Q2_max-Q2_min)>0.01); // it's not safe to have such small bins => probably you are doing something wrong

    double C0b[11],C1b[11],C2b[11],C0w[11],C1w[11],C2w[11],Cpb[11];
    std::complex<double> CQ0b[3],CQ1b[3],CQpb[3];
    double C0be[11],C1be[11],C2be[11],C0we[11],C1we[11],C2we[11],Cpbe[11];
    std::complex<double> CQ0be[3],CQ1be[3],CQpbe[3];
    double obs[Nobs_BKll+1];

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b_pole;

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    CW_calculator(1,byVal(C0we),byVal(C1we),byVal(C2we),byVal(mu_W),param);
    C_calculator_base1(byVal(C0we),byVal(C1we),byVal(C2we),byVal(mu_W),byVal(C0be),byVal(C1be),byVal(C2be),byVal(mu_b),param);
    CQ_calculator(1,byVal(CQ0be),byVal(CQ1be),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(1,byVal(Cpbe),byVal(CQpbe),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0be, CQ0be);

    return BRBKll(2,1,byVal(Q2_min), byVal(Q2_max), byVal(obs),byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b))/BRBKll(1,1,byVal(Q2_min), byVal(Q2_max), byVal(obs),byVal(C0be),byVal(C1be),byVal(C2be),byVal(CQ0be),byVal(CQ1be),byVal(Cpbe),byVal(CQpbe),param,byVal(mu_b));
  }
  
  /// Branching fraction of B -> X_s gamma
  double bsgamma_CONV(const parameters *param, double E_t)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b_1S/2.;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3];

    //cout<<"Checking WC at W scale , C7= "<<C0w[7]+C1w[7]+C2w[7]<<" ,C9= "<<C0w[9]+C1w[9]+C2w[9]<<" ,C10= "<<C0w[10]+C1w[10]+C2w[10]<<endl;
    //cout<<"CHecking that the parameters are filled: WC"<<param->mass_b<<"  "<<param->CKM_lambda<<endl;
    //cout<<"Params WC: "<<param->mtmt<<" "<<mu_W<<"  "<<param->mass_top_pole<<" "<<param->mass_b<<endl;

    //cout<<"Cross check NO WC: "<<param->alphas_MZ<<" "<<param->mass_Z<<" "<<param->mass_b<<" "<<param->mass_top_pole<<" "<<param->mass_mu<<" "<<param->mass_s<<" "<<mu_W<<endl;

    //cout<<"Cross check NO WC mu_b: "<<mu_b<<endl;
    //cout<<"Cross check NO WC: "<<param->mass_d<<" "<<param->mass_u<<" "<<param->mass_s<<" "<<param->mass_c<<" "<<param->mass_t<<" "<<param->mass_e<<" "<<param->mass_nue<<" "<<param->mass_mu<<" "<<param->mass_num<<" "<<param->mass_tau<<" "<<param->mass_nut<<endl;

    //cout<<"Cross check WC: "<<param->alphas_MZ<<" "<<param->mass_Z<<" "<<param->mass_b<<" "<<param->mass_top_pole<<" "<<param->mass_mu<<" "<<param->mass_s<<" "<<mu_W<<endl;

    //cout<<"Cross check WC mu_b: "<<mu_b<<endl;
    //cout<<"Cross check NO WC: "<<param->mass_d<<" "<<param->mass_u<<" "<<param->mass_s<<" "<<param->mass_c<<" "<<param->mass_t<<" "<<param->mass_e<<" "<<param->mass_nue<<" "<<param->mass_mu<<" "<<param->mass_num<<" "<<param->mass_tau<<" "<<param->mass_nut<<endl;

    //cout<<"Checking WC at W scale , C7= "<<C0w[7]+C1w[7]+C2w[7]<<" ,C9= "<<C0w[9]+C1w[9]+C2w[9]<<" ,C10= "<<C0w[10]+C1w[10]+C2w[10]<<endl;
    //cout<<"CHecking that the parameters are filled: WC"<<param->mass_b<<"  "<<param->CKM_lambda<<endl;
    //cout<<"Params WC: "<<param->mtmt<<" "<<mu_W<<"  "<<param->mass_top_pole<<" "<<param->mass_b<<endl;

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b);

    return bsgamma_Ecut(byVal(C0b),byVal(C1b),byVal(C2b),byVal(Cpb),byVal(mu_b),byVal(mu_W), E_t, param);
  }

  /// CP-averaged branching fraction of B0_s -> l+ l-
  double Bsll_untag_CONV(const parameters *param, int flav)
  {
    if (flav < 1 || flav > 3) backend_error().raise(LOCAL_INFO, "Unrecognised flavour!");
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0b[11],C1b[11],C2b[11],C0w[11],C1w[11],C2w[11],Cpb[11];
    std::complex<double> CQ0b[3],CQ1b[3],CQpb[3];

    CW_calculator(flav,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(flav,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(flav,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return Bsll_untag(flav,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  /// Branching fraction of B0 -> l+ l-
  double Bll_CONV(const parameters *param, int flav)
  {
    if (flav < 1 || flav > 3) backend_error().raise(LOCAL_INFO, "Unrecognised flavour!");
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0b[11],C1b[11],C2b[11],C0w[11],C1w[11],C2w[11];
    std::complex<double> CQ0b[3],CQ1b[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return Bll(byVal(flav),(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),param,byVal(mu_b));
  }

  double BRBXsmumu_lowq2_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3],CQ0b[3],CQ1b[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return BRBXsll_lowq2(2,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  double BRBXsmumu_highq2_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3],CQ0b[3],CQ1b[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return BRBXsll_highq2(2,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  double A_BXsmumu_lowq2_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3],CQ0b[3],CQ1b[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return A_BXsll_lowq2(2,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  double A_BXsmumu_highq2_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3],CQ0b[3],CQ1b[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return A_BXsll_highq2(2,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  double A_BXsmumu_zero_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3],CQ0b[3],CQ1b[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return A_BXsll_zero(2,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  double BRBXstautau_highq2_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3],CQ0b[3],CQ1b[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(2,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return BRBXsll_highq2(3,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  double A_BXstautau_highq2_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b;
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C2b[11],Cpb[11];
    std::complex<double> CQpb[3],CQ0b[3],CQ1b[3];

    CW_calculator(3,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    CQ_calculator(3,byVal(CQ0b),byVal(CQ1b),byVal(mu_W),byVal(mu_b),param);
    Cprime_calculator(3,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b, CQ0b);

    return A_BXsll_highq2(3,byVal(C0b),byVal(C1b),byVal(C2b),byVal(CQ0b),byVal(CQ1b),byVal(Cpb),byVal(CQpb),param,byVal(mu_b));
  }

  double delta0_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b_1S/2.;
    double lambda_h=0.5;
    double mu_spec=sqrt(lambda_h*param->mass_b);
    double C0w[11],C1w[11],C2w[11],C0b[11],C1b[11],C0spec[11],C1spec[11],Cpb[11];
    std::complex<double> CQpb[3];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base2(byVal(C0w),byVal(C1w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(mu_b),param);
    C_calculator_base2(byVal(C0w),byVal(C1w),byVal(mu_W),byVal(C0spec),byVal(C1spec),byVal(mu_spec),param);
    Cprime_calculator(2,byVal(Cpb),byVal(CQpb),byVal(mu_W),byVal(mu_b),param);
    modify_WC(param, C0b);

    return delta0(byVal(C0b),byVal(C0spec),byVal(C1b),byVal(C1spec),byVal(Cpb),param,byVal(mu_b),byVal(mu_spec),byVal(lambda_h));
  }

  double SI_AI_BKstarmumu_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b_1S/2.;
    double C0b[11],C1b[11],C2b[11],C0w[11],C1w[11],C2w[11];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b),param);
    modify_WC(param, C0b);

    return AI_BKstarmumu(1.,6.,byVal(C0b),byVal(C1b),byVal(C2b),param,byVal(mu_b));
  }

  double SI_AI_BKstarmumu_zero_CONV(const parameters *param)
  {
    check_model(param, LOCAL_INFO);

    double mu_W=2.*param->mass_W;
    double mu_b=param->mass_b_1S/2.;
    double C0b[11],C1b[11],C2b[11],C0w[11],C1w[11],C2w[11];

    CW_calculator(2,byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),param);
    C_calculator_base1(byVal(C0w),byVal(C1w),byVal(C2w),byVal(mu_W),byVal(C0b),byVal(C1b),byVal(C2b),byVal(mu_b), param);
    modify_WC(param, C0b);

    return AI_BKstarmumu_zero(byVal(C0b),byVal(C1b),byVal(C2b),param,byVal(mu_b));
  }

}
END_BE_NAMESPACE
