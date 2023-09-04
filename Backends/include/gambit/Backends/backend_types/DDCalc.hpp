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
///  \author Ben Farmer
///          (b.farmer@imperial.ac.uk)
///  \date 2019 Jul
///
///  \author Felix Kahlhofer
///          (kahlhoefer@physik.rwth-aachen.de)
///  \date 2020 May
///
///  *************************

#ifndef __DDCalc_types_hpp__
#define __DDCalc_types_hpp__

#include <map>

namespace Gambit
{

  // Forward declarations
  class ModelParameters;
  template<class T> class safe_ptr;
  namespace Models { template<class T> class safe_param_map; }

  // Container for SI/SD DM-nucleon couplings
  struct DM_nucleon_couplings
  {
    double gps;
    double gns;
    double gpa;
    double gna;
  };

  /// Container for effective non-relativistic DM-nucleon Wilson coefficients
  struct NREO_DM_nucleon_couplings
  {
      public:
          // Various constructors
          NREO_DM_nucleon_couplings();
          NREO_DM_nucleon_couplings(int CPT);
          NREO_DM_nucleon_couplings(const ModelParameters&);
          NREO_DM_nucleon_couplings(const Models::safe_param_map<safe_ptr<const double>>&);
          // Define operator basis
          // CPTbasis = 1 for NREFT_CPT basis
          // CPTbasis = 0 for NREffectiveTheory basis
          int CPTbasis;
          /// Store couplings in map for easier iteration
          std::map<int,double> c0;
          std::map<int,double> c1;
  };

  struct DD_coupling_container
  {
    int coeff_structure;                               // Simple integer to determine which WIMP type to initialise. Possible choices are
                                                       // int = 1: Spin-independent/spin-dependent interactions only
                                                       // int = 2: NREFT_CPT from arXiv:1708.02678
                                                       // int = 3: NREffectiveTheory from arXiv:1505.03117
    DM_nucleon_couplings          DM_nucleon_coeffs;   // SI/SD DM-nucleon couplings (relevant for int = 1)
    NREO_DM_nucleon_couplings     DD_nonrel_WCs;       // Effective non-relativistic DM-nucleon Wilson coefficients (relevant for int = 2, 3)
  };

}

#endif /* defined __DDCalc_types_hpp__ */
