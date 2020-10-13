//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Frontend for SUSYPOPE 0.2 backend
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
/// \author Peter Athron
///
///  *********************************************

#define BACKENDNAME SUSYPOPE
#define BACKENDLANG FORTRAN
#define VERSION 0.2
#define SAFE_VERSION 0_2

/* The following macro loads the library using dlopen 
 * when this header file is included somewhere. */

LOAD_LIBRARY

BE_FUNCTION(SetFlags_SUSYPOPE, void, (int&,int&,int&,int&,int&,int&,int&), "setflags_susypope_", "SetFlags_SUSYPOPE")

BE_FUNCTION(SetPara_SUSYPOPE, void,
            (int&,
             Fdouble&,Fdouble&,Fdouble&,Fdouble&,Fdouble&,
             Fdouble&,Fdouble&,Fdouble&,
             Fdouble&,Fdouble&,Fdouble&,
             Fdouble&,Fdouble&,Fdouble_complex&,
             Farray< Fdouble,1,4>&, Farray<Fdouble_complex,1,3,1,3>&,
             Fdouble&,Fdouble&,Fdouble&,Fdouble&,Fdouble&,
             Fdouble&,Fdouble&,Fdouble&,Fdouble&,Fdouble&,
             Fdouble&,Fdouble&,Fdouble&,Fdouble&,Fdouble&,
             Fdouble_complex&,Fdouble&,
             Fdouble_complex&,Fdouble_complex&,Fdouble_complex&,
             Fdouble_complex&,Fdouble_complex&,Fdouble_complex&,
             Fdouble_complex&,Fdouble_complex&,Fdouble_complex&,
             Fdouble&,Fdouble&,Fdouble&,
             Fdouble_complex&,Fdouble_complex&,Fdouble_complex&,
             Fdouble&,Fdouble&,
             Fdouble&,Fdouble&,Fdouble&), 
            "setpara_susypope_", "SetPara_SUSYPOPE")

BE_FUNCTION(CalcObs_SUSYPOPE, void,
            (int&, Farray<Fdouble,1,35>&,Farray<Fdouble,1,35>&),
            "calcobs_susypope_","CalcObs_SUSYPOPE")

BE_INI_FUNCTION{
   /// set flags for SUSYPOPE
   /// all flags as given in Appendix F (page 2 / 154 of) found in doc/ 
   /// directory of SUSYPOPE-0.2
   int error = 0, L = 5, iter = 1, Obs = 1, SMObs = 1, HOpt = 1, Verb = 1;
   SetFlags_SUSYPOPE(error, L, iter, Obs, SMObs, HOpt, Verb);
   //should probably test the error since we pass it
   
   //parameters as given in Appendix F (page 2 / 154 of) found in doc/ 
   /// directory of SUSYPOPE-0.2
   Fdouble MT = 172; //top quark mass, pole?
   Fdouble MB = 4.2; // bottom quark mass mb(mb) MSbar mass?
   Fdouble ML = 1.777; //tau lepton (pole?) mass 
   Fdouble MW = 80.385; //W (pole?) mass? starting value for iter
   Fdouble MZexp = 91.1876; //Z boson (pole?) mass
   Fdouble DeltaAlfa5had = 1e-2; /// hadronic contributions to photon vaccum 
                                 /// polarisation 
   Fdouble DeltaAlfaLept = 1e-2; /// leptonic contributions to photon vaccum 
                                 /// polarisation //DeltaAlfaQED in code
   Fdouble ZWidthexp = 1; /// experimental Z bosonm width (used to compute
                          /// Z boson pole mass
   
   Fdouble TB = 10; ///tan(beta)
   Fdouble MA0 = 250; /// masses of CP-odd and (real MSSM only) 
   /// set to -1 if complex MSSM
   Fdouble MHp = -1;  /// charged Higgs (complex MSSM only)
   /// set to -1 if real MSSM
   
   Fdouble Mho = 125;  /// light Higgs mass (specified for HOpt = 1)
   Fdouble MHH = 1250;  /// heavy Higgs mass (specified for HOpt = 1)
   Fdouble_complex SA; /// Higgs mixing angle
   SA.re =0.1;
   SA.im = 0;
   Farray< Fdouble,1,4> MHiggs;  /// complex MSSM 3 higgs masses 
   /// don't specify in real MSSM or HOpt=3
   Farray<Fdouble_complex,1,3,1,3> UHiggs; ///complex mising matrix for MHiggs
   /// don't specify in real MSSM or HOpt=3
   
   
   // soft-SUSY breaking parameters for g=1,2,3 generation sfermions
   Fdouble MSusy = 1000;
   Fdouble M3SL = MSusy, M2SL = M3SL, M1SL = M2SL; // sleptonFdoublet
   Fdouble M3SE = MSusy, M2SE = M3SE, M1SE = M2SE; // slepton singlet
   Fdouble M3SQ = MSusy, M2SQ = M3SQ, M1SQ = M2SQ; // squarkFdoublet
   Fdouble M3SU = MSusy, M2SU = M3SU, M1SU = M2SU; // up-type squark singlet
   Fdouble M3SD = MSusy, M2SD = M3SD, M1SD = M2SD; // down-type squark singlet
   Fdouble_complex MUE;  // Higgs mixing parameter mu
   MUE.re = 200; 
   MUE.im = 0;
   Fdouble MUEPhase=0; //aditional phase rotation to above parameter
   // soft-SUSY breaking parameters
   Fdouble_complex Af; 
   Af.re = 2000; 
   Af.im = 0.;
   Fdouble_complex At = Af, Ac = At, Au = Ac;
   Fdouble_complex Ab = Af, As = Ab, Ad = As;
   Fdouble_complex Atau = Af, Amu = Atau, Ae = Amu;
   //aditional phase rotation to above parameters
   Fdouble  AtPhase=0,AbPhase=0,AtauPhase=0;
   // gaugino mass parameters. M_1 == 0 => GUT relation is used
   Fdouble_complex M_1, M_2, M_3; 
   M_1.re = 0;   M_1.im = 0;
   M_2.re = 500; M_2.im = 0;
   M_3.re = 800; M_3.im = 0;
   //aditional phase rotation to above parameters
   Fdouble M1Phase=0,M2Phase=0;
   // soft-SUSY breaking parameters
   // the scales at which the sfermion input parameters M3S are given
   // < 0 indicates on-shell parameters which is reccomended in doc
   Fdouble Qtau = 1000; /// (not implemented doc says)
   Fdouble Qt = 1000;
   Fdouble Qb = 100;
   
   /// Set the parameters
   SetPara_SUSYPOPE(error, MT, MB, ML, MW, MZexp, 
                    DeltaAlfa5had, DeltaAlfaLept, ZWidthexp,
                    TB, MA0, MHp, Mho, MHH, SA, MHiggs, UHiggs,
                    M3SL, M3SE, M3SQ, M3SU, M3SD,
                    M2SL, M2SE, M2SQ, M2SU, M2SD,
                    M1SL, M1SE, M1SQ, M1SU, M1SD,
                    MUE, MUEPhase,
                    Atau, At, Ab, Amu, Ac, As, Ae, Au, Ad, 
                    AtPhase, AbPhase, AtauPhase,
                    M_1, M_2, M_3, 
                    M2Phase, M1Phase,
                    Qtau, Qt, Qb);   
   //should probably test the error since we pass it
   
}
END_BE_INI_FUNCTION

// Undefine macros to avoid conflict with other backends
#include "gambit/Backends/backend_undefs.hpp"
