//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file FeynHiggs.cpp
///
///  Frontend source for the FeynHiggs backend.
///
///  Actual implementation of FeynHiggs ini function.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher S. Rogan
///          (crogan@cern.ch)
///  \date 2015 Sept
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2016 Aug
///
///  *********************************************

#include "gambit/Backends/frontend_macros.hpp"
#include "gambit/Backends/frontends/FeynHiggs_2_11_3.hpp"

//#define FEYNHIGGS_DEBUG

BE_INI_FUNCTION
{

  int error = 1;

  // Scan-level initialisation
  static bool scan_level = true;
  if(scan_level)
  {
    // initialize FeynHiggs flags
    int mssmpart = 4;  // scope of calculation (4 -> full MSSM, recommended)
    int fieldren = 0;  // one-loop field-renormalization constants (0 -> DRbar, strongly recommended))
    int tanbren = 0;   // one-loop one-loop tanBeta counter-term (0 -> DRbar, strongly recommended))
    int higgsmix = 2;  // mixing in Higgs sector (3 -> full 3 x 3 in neutral sector) -> HB says 2
    int p2approx = 4;  // 1-loop approximation (4 -> none, UHiggs eval. at p^2=0, recommended) -> HB says 0
    int looplevel = 2; // higher-order corrections? (2 -> various 2-loop contrib., recommended)
    int runningMT = 1; // top mass for 1/2-loop corr. (1 -> m_t^{run}, recommended)
    int botResum = 1;  // O(tan^n Beta) corr. ressummed? (1 -> yes, recommended)
    int tlCplxApprox = 0; // determines how 2-loop corr. are treated with complex param (0 for rMSSM, > 0 for cMSSM)

    #ifdef FEYNHIGGS_DEBUG
      cout << "****** calling FHSetFlags ******" << endl;
    #endif

    FHSetFlags(error, mssmpart, fieldren, tanbren, higgsmix,
         p2approx, looplevel, runningMT, botResum, tlCplxApprox);
  }
  scan_level = false;

  // retrieve MSSM_spectrum dependency
  const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
  const SMInputs& sminputs = spec.get_SMInputs();
  SLHAea::Coll slhaea = spec.getSLHAea(2);

  if (slhaea.find("SPINFO") == slhaea.end())
  {
    cout << slhaea << endl;
    backend_error().raise(LOCAL_INFO, "SPINFO block missing from SLHAea object.");
  }
  SLHAea::Block spinfo = slhaea.at("SPINFO");
  std::vector<std::string> k3(1, "3");
  std::vector<std::string> k4(1, "4");
  if(spinfo.find(k3) != spinfo.end() || spinfo.find(k4) != spinfo.end())
  {
    backend_error().raise(LOCAL_INFO, "Entry 3 or 4 missing in SPINFO block.");
  }

  //
  // SM input parameters: -1 gives default value
  //
  fh_real invAlfa = sminputs.alphainv; // 1/alpha_{QED}
  fh_real AlfasMZ = sminputs.alphaS;   // alpha_s @ MZ
  fh_real GF = sminputs.GF;            // Fermi constant

  fh_real ME = sminputs.mE;      // electron mass
  fh_real MU = sminputs.mU;      // up quark mass @ 2 GeV
  fh_real MD = sminputs.mD;      // down quark mass @ 2 GeV
  fh_real MM = sminputs.mMu;     // muon mass
  fh_real MC = sminputs.mCmC;    // charm mass at m_c
  fh_real MS = sminputs.mS;      // stange mass @ 2 GeV
  fh_real ML = sminputs.mTau;    // tau mass
  fh_real MB = sminputs.mBmB;    // bottom mass at m_b

  fh_real MW = spec.get(Par::Pole_Mass,"W+");  // W boson mass
  fh_real MZ = sminputs.mZ;                        // Z boson mass

  // CKM input parameters in Wolfenstein parameterization
  fh_real CKMlambda = sminputs.CKM.lambda;
  fh_real CKMA = sminputs.CKM.A;
  fh_real CKMrhobar = sminputs.CKM.rhobar;
  fh_real CKMetabar = sminputs.CKM.etabar;

  #ifdef FEYNHIGGS_DEBUG
    cout << "****** calling FHSetSMPara ******" << endl;
  #endif

  error = 1;
  FHSetSMPara(error, invAlfa, AlfasMZ, GF,
        ME, MU, MD, MM, MC, MS, ML, MB,
        MW, MZ,
        CKMlambda, CKMA, CKMrhobar, CKMetabar);

  fh_real MT = spec.get(Par::Pole_Mass,"t");                      // top quark mass
  fh_real TB = SLHAea::to<double>( slhaea.at("MINPAR").at(3).at(1) ); // tan Beta
  fh_real MA0 = spec.get(Par::Pole_Mass,"A0");   // masses of CP-odd and
  fh_real MHp = -1.;                                                  // charged Higgs (only one should be given)
  if(MA0 <= 0.){
    MA0 = -1.;
    MHp = spec.get(Par::Pole_Mass,"H+");
  }

  // cout << "** Top Mass: " << MT << endl;
  // cout << "** Tan beta: " << TB << endl;
  // cout << "** MA0: " << MA0 << endl;
  // cout << "** MHp: " << MHp << endl;

  // soft-SUSY breaking parameters for g=1,2,3 generation sfermions
  // slepton doublet
  fh_real M1SL = SLHAea::to<double>( slhaea.at("MSOFT").at(31).at(1) );
  fh_real M2SL = SLHAea::to<double>( slhaea.at("MSOFT").at(32).at(1) );
  fh_real M3SL = SLHAea::to<double>( slhaea.at("MSOFT").at(33).at(1) );
  // slepton singlet
  fh_real M1SE = SLHAea::to<double>( slhaea.at("MSOFT").at(34).at(1) );
  fh_real M2SE = SLHAea::to<double>( slhaea.at("MSOFT").at(35).at(1) );
  fh_real M3SE = SLHAea::to<double>( slhaea.at("MSOFT").at(36).at(1) );
  // squark doublet
  fh_real M1SQ = SLHAea::to<double>( slhaea.at("MSOFT").at(41).at(1) );
  fh_real M2SQ = SLHAea::to<double>( slhaea.at("MSOFT").at(42).at(1) );
  fh_real M3SQ = SLHAea::to<double>( slhaea.at("MSOFT").at(43).at(1) );
  // up-type squark singlet
  fh_real M1SU = SLHAea::to<double>( slhaea.at("MSOFT").at(44).at(1) );
  fh_real M2SU = SLHAea::to<double>( slhaea.at("MSOFT").at(45).at(1) );
  fh_real M3SU = SLHAea::to<double>( slhaea.at("MSOFT").at(46).at(1) );
  // down-type squark singlet
  fh_real M1SD = SLHAea::to<double>( slhaea.at("MSOFT").at(47).at(1) );
  fh_real M2SD = SLHAea::to<double>( slhaea.at("MSOFT").at(48).at(1) );
  fh_real M3SD = SLHAea::to<double>( slhaea.at("MSOFT").at(49).at(1) );

  // cout << "** soft-SUSY breaking parameters for g=1,2,3 sfermions:" << endl;
  // cout << "  ** M1SL = " << M1SL << endl;
  // cout << "  ** M2SL = " << M2SL << endl;
  // cout << "  ** M3SL = " << M3SL << endl << endl;
  // cout << "  ** M1SE = " << M1SE << endl;
  // cout << "  ** M2SE = " << M2SE << endl;
  // cout << "  ** M3SE = " << M3SE << endl << endl;
  // cout << "  ** M1SQ = " << M1SQ << endl;
  // cout << "  ** M2SQ = " << M2SQ << endl;
  // cout << "  ** M3SQ = " << M3SQ << endl << endl;
  // cout << "  ** M1SU = " << M1SU << endl;
  // cout << "  ** M2SU = " << M2SU << endl;
  // cout << "  ** M3SU = " << M3SU << endl << endl;
  // cout << "  ** M1SD = " << M1SD << endl;
  // cout << "  ** M2SD = " << M2SD << endl;
  // cout << "  ** M3SD = " << M3SD << endl << endl;

  // soft-SUSY breaking parameters
  fh_complex Af;
  Af.re = 0.;
  Af.im = 0.;
  fh_complex At = Af, Ac = Af, Au = Af;
  fh_complex Ab = Af, As = Af, Ad = Af;
  fh_complex Atau = Af, Amu = Af, Ae = Af;

  Au.re   = SLHAea::to<double>(slhaea.at("TU").at(1,1).at(2))/SLHAea::to<double>(slhaea.at("YU").at(1,1).at(2));
  Ac.re   = SLHAea::to<double>(slhaea.at("TU").at(2,2).at(2))/SLHAea::to<double>(slhaea.at("YU").at(2,2).at(2));
  At.re   = SLHAea::to<double>(slhaea.at("TU").at(3,3).at(2))/SLHAea::to<double>(slhaea.at("YU").at(3,3).at(2));
  Ad.re   = SLHAea::to<double>(slhaea.at("TD").at(1,1).at(2))/SLHAea::to<double>(slhaea.at("YD").at(1,1).at(2));
  As.re   = SLHAea::to<double>(slhaea.at("TD").at(2,2).at(2))/SLHAea::to<double>(slhaea.at("YD").at(2,2).at(2));
  Ab.re   = SLHAea::to<double>(slhaea.at("TD").at(3,3).at(2))/SLHAea::to<double>(slhaea.at("YD").at(3,3).at(2));
  Ae.re   = SLHAea::to<double>(slhaea.at("TE").at(1,1).at(2))/SLHAea::to<double>(slhaea.at("YE").at(1,1).at(2));
  Amu.re  = SLHAea::to<double>(slhaea.at("TE").at(2,2).at(2))/SLHAea::to<double>(slhaea.at("YE").at(2,2).at(2));
  Atau.re = SLHAea::to<double>(slhaea.at("TE").at(3,3).at(2))/SLHAea::to<double>(slhaea.at("YE").at(3,3).at(2));

  // cout << "** Au =" << endl;
  // cout << Au.re << " " << Ac.re << " " << At.re << endl;
  // cout << "** Ad =" << endl;
  // cout << Ad.re << " " << As.re << " " << Ab.re << endl;
  // cout << "** Ae =" << endl;
  // cout << Ae.re << " " << Amu.re << " " << Atau.re << endl;

  fh_complex MUE;  // Higgs mixing parameter mu
  MUE.re = spec.get(Par::mass1,"Mu");
  MUE.im = 0;

  // cout << "** MU = " << MUE.re << endl;

  // gaugino mass parameters. M_1 == 0 => GUT relation is used
  fh_complex M_1, M_2, M_3;
  M_1.re = spec.get(Par::mass1,"M1");
  M_1.im = 0;
  M_2.re = spec.get(Par::mass1,"M2");
  M_2.im = 0;
  M_3.re = spec.get(Par::mass1,"M3");
  M_3.im = 0;

  // cout << "** M1 = " << M_1.re << endl;
  // cout << "** M2 = " << M_2.re << endl;
  // cout << "** M3 = " << M_3.re << endl;

  // the scales at which the sfermion input parameters M3S are given
  // 0 indicates on-shell parameters
  double SCALE = spec.GetScale();

  // cout << "** SCALE = " << SCALE << endl;

  fh_real Qtau = SCALE;
  fh_real Qt = SCALE;
  fh_real Qb = SCALE;

  // the renormalization scale is Mtop times the 'scalefactor'
  fh_real scalefactor = 1.;

  #ifdef FEYNHIGGS_DEBUG
    cout << "****** calling FHSetPara ******" << endl;
  #endif

  error = 1;
  FHSetPara(error, scalefactor, MT, TB, MA0, MHp,
      M3SL, M3SE, M3SQ, M3SU, M3SD,
      M2SL, M2SE, M2SQ, M2SU, M2SD,
      M1SL, M1SE, M1SQ, M1SU, M1SD,
      MUE,
      Atau, At, Ab,
      Amu,  Ac, As,
      Ae,   Au, Ad,
      M_1, M_2, M_3,
      Qtau, Qt, Qb);

  //
  // Set NMFV parameters
  //
  /*
  fh_ccomplex deltaQLL12, deltaQLL23, deltaQLL13;
  fh_ccomplex deltaULR12, deltaULR23, deltaULR13;
  fh_ccomplex deltaURL12, deltaURL23, deltaURL13;
  fh_ccomplex deltaURR12, deltaURR23, deltaURR13;
  fh_ccomplex deltaDLR12, deltaDLR23, deltaDLR13;
  fh_ccomplex deltaDRL12, deltaDRL23, deltaDRL13;
  fh_ccomplex deltaDRR12, deltaDRR23, deltaDRR13;
  FHSetNMFV(error,
      deltaQLL12, deltaQLL23, deltaQLL13,
      deltaULR12, deltaULR23, deltaULR13,
      deltaURL12, deltaURL23, deltaURL13,
      deltaURR12, deltaURR23, deltaURR13,
      deltaDLR12, deltaDLR23, deltaDLR13,
      deltaDRL12, deltaDRL23, deltaDRL13,
      deltaDRR12, deltaDRR23, deltaDRR13);
  */
  //
  // Set LFV parameters
  //
  /*
  fh_ccomplex deltaLLL12, deltaLLL23, deltaLLL13;
  fh_ccomplex deltaELR12, deltaELR23, deltaELR13;
  fh_ccomplex deltaERL12, deltaERL23, deltaERL13;
  fh_ccomplex deltaERR12, deltaERR23, deltaERR13;
  FHSetLFV(error,
     deltaLLL12, deltaLLL23, deltaLLL13,
     deltaELR12, deltaELR23, deltaELR13,
     deltaERL12, deltaERL23, deltaERL13,
     deltaERR12, deltaERR23, deltaERR13);
  */

}
END_BE_INI_FUNCTION
