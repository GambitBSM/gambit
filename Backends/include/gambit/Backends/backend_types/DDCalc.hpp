//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper types for DDCalc backend.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          p.scott@imperial.ac.uk
///  \date 2016 May
///
///  *************************

#ifndef __DDCalc_types_hpp__
#define __DDCalc_types_hpp__

namespace Gambit
{

  // Container for regular SI and SD dark matter - nucleon couplings
  struct DM_nucleon_couplings
  {
    double gps;
    double gns;
    double gpa;
    double gna;
  };

  // Container for fermionic Higgs-portal SI constant and q^2-dependent dark matter-nucleon couplings.
  // This can be removed in future, when newer versions of DDCalc are interfaced and support for HP
  // models with DDCalc 2.0.0 is dropped from GAMBIT.
  struct DM_nucleon_couplings_fermionic_HP
  {
    double gps;
    double gns;
    double gp_q2;
    double gn_q2;
  };

}

#endif /* defined __DDCalc_types_hpp__ */
