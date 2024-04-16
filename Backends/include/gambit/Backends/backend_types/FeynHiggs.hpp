//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Definitions of types
///  for the FeynHiggs backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///  \date 2015 Apr
///
///  *********************************************

#ifndef __FeynHiggs_types_hpp__
#define __FeynHiggs_types_hpp__

#include "gambit/Utils/util_types.hpp"

// indexing macros from FeynHiggs' "FHCouplings.h", FH v2.10.2, edited

#define ncouplings 681
#define Roffset 472
// #define Coupling(c)    couplingS(c)
// #define LCoupling(c)   couplingS(c)
// #define RCoupling(c)   couplingS(c+Roffset)

#define ncouplingsms 231
#define RSMoffset 108
// #define CouplingSM(c)    couplingsmS(c)
// #define LCouplingSM(c)   couplingsmS(c)
// #define RCouplingSM(c)   couplingsmS(c+RSMoffset)

#define ngammas 978
#define BRoffset 491
// #define GammaTot(h)    gammaS(h)
// #define Gamma(c)   gammaS(c+4)
// #define BR(c)      gammaS(c+BRoffset)

#define ngammasms 250
#define BRSMoffset 127
// #define GammaSMTot(h)    gammasmS(h)
// #define GammaSM(c)   gammasmS(c+4)
// #define BRSM(c)      gammasmS(c+BRSMoffset)


#define H0VV(h,vv) (h)+3*(vv)-3
#if 0
h  = 1..3 Higgs: h0, HH, A0
  vv = 1..5 vector-boson pair: gamma gamma, gamma Z, ZZ, WW, gg
#endif

#define H0FF(h,t,g1,g2) (h)+3*(t)+12*(g1)+36*(g2)-36
#if 0
  h  = 1..3 Higgs: h0, HH, A0
  t  = 1..4 fermion type: nu, e, u, d
  g1 = 1..3 fermion 1 generation
  g2 = 1..3 fermion 2 generation
#endif

#define HpFF(p,g1,g2) (p)+2*(g1)+6*(g2)+115
#if 0
  p  = 1..2 decay products: leptons, quarks
  g1 = 1..3 up-type fermion 1 generation
  g2 = 1..3 down-type fermion 2 generation
#endif

#define H0ChaCha(h,c1,c2) (h)+3*(c1)+6*(c2)+132
#if 0
  h  = 1..3 Higgs: h0, HH, A0
  c1 = 1..2 chargino 1
  c2 = 1..2 chargino 2
#endif

#define H0NeuNeu(h,n1,n2) (h)+3*(n1)+12*(n2)+138
#if 0
  h  = 1..3 Higgs: h0, HH, A0
  n1 = 1..4 neutralino 1
  n2 = 1..4 neutralino 2
#endif

#define HpNeuCha(n1,c2) (n1)+4*(c2)+197
#if 0
  n1 = 1..4 neutralino
  c2 = 1..2 chargino
#endif

#define H0HV(h,hv) (h)+3*(hv)+206
#if 0
  h  = 1..3 decaying Higgs: h0, HH, A0
  hv = 1..3 produced pair: h0-Z, HH-Z, A0-Z
#endif

#define HpHV(hv) (hv)+218
#if 0
  hv = 1..3 produced pair: h0-W, HH-W, A0-W
#endif

#define H0HH(h,h1,h2) (h)+3*(h1)+12*(h2)+206
#if 0
  h  = 1..3 decaying Higgs: h0, HH, A0
  h1 = 1..4 produced Higgs 1: h0, HH, A0, Hp
  h2 = 1..4 produced Higgs 2: h0, HH, A0, Hp
#endif

#define H0SfSf(h,s1,s2,t,g) (h)+3*(s1)+6*(s2)+12*(t)+48*(g)+200
#if 0
  h  = 1..3 Higgs: h0, HH, A0
  s1 = 1..2 sfermion 1
  s2 = 1..2 sfermion 2
  t  = 1..4 sfermion type: nu, e, u, d
  g = 1..3  common sfermion generation
#endif

#define HpSfSf(s1,s2,p,g1,g2) (s1)+2*(s2)+4*(p)+8*(g1)+24*(g2)+375
#if 0
  s1 = 1..2 sfermion 1
  s2 = 1..2 sfermion 2
  p  = 1..2 decay products: sleptons, squarks
  g1 = 1..3 up-type sfermion 1 generation
  g2 = 1..3 down-type sfermion 2 generation
#endif

#define tBF(bf) (bf)+485
#if 0
  bf = 1..2 W-b, H-b
#endif


#define nprodxs 52

#define bbh(h)    prodXS(h)
#define bbhSM(h)  prodXS((h)+3)
#define btagbh(h) prodXS((h)+6)
#define btagbhSM(h) prodXS((h)+9)
#define ggh(h)    prodXS((h)+12)
#define ggh2(h)   prodXS((h)+15)
#define gghSM(h)  prodXS((h)+18)
#define qqh(h)    prodXS((h)+21)
#define qqhSM(h)  prodXS((h)+24)
#define tth(h)    prodXS((h)+27)
#define tthSM(h)  prodXS((h)+30)
#define Wh(h)   prodXS((h)+33)
#define WhSM(h)   prodXS((h)+36)
#define Zh(h)   prodXS((h)+39)
#define ZhSM(h)   prodXS((h)+42)
#define StSth(h)  prodXS((h)+45)
#define tHm   prodXS(49)
#define tHm2    prodXS(50)
#define tHm2lo    prodXS(51)
#define tHm2hi    prodXS(52)


namespace Gambit
{

  // variables for input to FH backend sub-routines
  typedef Fdouble fh_real;
  typedef Fdouble_complex fh_complex;
  typedef const fh_real fh_creal;
  typedef const fh_complex fh_ccomplex;

  // Container for FeynHiggs Higgs mass/mixings information (from FHHiggsCorr and FHUncertainties backend functions)
  struct fh_HiggsMassObs_container
  {
    // Higgs mass with
    // 0 - m1 (Mh in rMSSM)
    // 1 - m2 (MH in rMSSM)
    // 2 - m3 (MA in rMSSM)
    // 3 - MHpm
    fh_real MH[4];
    fh_real deltaMH[4];

    // sine of effective Higgs mixing angle, alpha_eff
    fh_complex SinAlphaEff;
    fh_complex deltaSinAlphaEff;

    // matrix needed to rotate Higgs
    // mass matrix to diagonal form
    fh_complex UH[3][3];
    fh_complex deltaUH[3][3];

    // matrix of Z-factors needed to combine
    // amplitudes involving on-shell Higgs
    fh_complex ZH[3][3];
    fh_complex deltaZH[3][3];
  };

  // Container for FeynHiggs Flavour observable information (from FHFlavour backend function)
  struct fh_FlavourObs_container
  {
    fh_real Bsg_MSSM;     // B -> Xs gamma in MSSM
    fh_real Bsg_SM;       // B -> Xs gamma in SM
    fh_real deltaMs_MSSM; // delta Ms in MSSM
    fh_real deltaMs_SM;   // delta Ms in SM
    fh_real Bsmumu_MSSM;  // Bs -> mu mu in MSSM
    fh_real Bsmumu_SM;    // Bs -> mu mu in SM
  };

  // Container for FeynHiggs precision constraints observables (from FHConstraints backend function)
  struct fh_PrecisionObs_container
  {
    fh_real gmu2;        // g_{mu}-2
    fh_real deltaRho;    // deltaRho
    fh_real MW_MSSM;     // W mass in MSSM
    fh_real MW_SM;       // W mass in SM
    fh_real sinW2_MSSM;  // weak mixing angle in MSSM
    fh_real sinW2_SM;    // weak mixing angle in SM
    fh_real edm_ele;     // electron EDM
    fh_real edm_neu;     // neutron EDM
    fh_real edm_Hg;      // mercury EDM
    int ccb;             // ?
  };

  // Container for FeynHiggs MSSM masses (from FHGetPara backend function)
  struct fh_MSSMMassObs_container
  {
    // zero if minimal, non-zero if non-minimal flavour violation
    int nmfv;

    // MSf(s,t,g) MFV squark masses with indices
    // s = 1..2   sfermion index
    // t = 1..5   sfermion type nu,e,u,d,?
    // g = 1..3   generation index
    fh_real MSf[2][5][3];

    // USf(s1,s2,t,g) MFV squark mixing matrices with indices
    // s1 = 1..2  sfermion index (mass eigenstates)
    // s2 = 1..2  sfermion index (gauge eigenstates, L/R)
    // t  = 1..5  sfermion type nu,e,u,d,?
    // g  = 1..3  generation index
    fh_complex USf[2][2][5][3];

    // NMFV squark masses, with indices
    // a = 1..6   extended sfermion index
    // t = 1..5   sfermion type
    fh_real MASf[6][5];

    // NMFV squark mixing matrices, with indices
    // a1 = 1..6  extended sfermion index (mass eigenstates)
    // a2 = 1..6  extended sfermion index (gauge eigenstates)
    //  t = 1..5  sftermion type nu,e,u,d,?
    fh_complex UASf[36][5];

    // chargino masses
    fh_real MCha[2];

    // chargino mixing matrices (mass,gauge) eigenstates (2 x 2)
    fh_complex UCha[4];
    fh_complex VCha[4];

    // neutralino masses
    fh_real MNeu[4];

    // neutralino mixing matrices (mass,gauge) eigenstates (4 x 4)
    fh_complex ZNeu[16];

    // correction to bottom Yukawa coupling
    fh_complex deltaMB;

    // gluino mass
    fh_real MGl;

    // tree-level Higgs masses (Mh, MH, MA, MHpm)
    fh_real MHtree[4];

    // tree-level Higgs mixing parameters sin alpha
    fh_real SinAlphatree;
  };

  // Container for FeynHiggs couplings (from FHCouplings backend function)
  struct fh_Couplings_container
  {
    fh_complex couplings[ncouplings];
    fh_complex couplings_sm[ncouplingsms];
    fh_real gammas[ngammas];
    fh_real gammas_sm[ngammasms];
    str calculator;
    str calculator_version;
  };

  // Container for FeynHiggs Higgs prod xsecs (from FHHiggsProd backend function)
  struct fh_HiggsProd_container
  {
    fh_real prodxs_Tev[nprodxs];
    fh_real prodxs_LHC7[nprodxs];
    fh_real prodxs_LHC8[nprodxs];
  };

}

#endif /* defined __FeynHiggs_types_hpp__ */
