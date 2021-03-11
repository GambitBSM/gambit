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

  // Container for dark matter - nucleon couplings
  struct DM_nucleon_couplings
  {
    double gps;
    double gns;
    double gpa;
    double gna;
  };

  /// \brief NREO couplings container
  /// Object containing coupling constants for generalised non-relativistic WIMP-nucleon effective operators
  struct NREO_DM_nucleon_couplings
  {
      public:
          // Various constructors
          NREO_DM_nucleon_couplings();
          NREO_DM_nucleon_couplings(const ModelParameters&);
          NREO_DM_nucleon_couplings(const Models::safe_param_map<safe_ptr<const double>>&);
          /// Store couplings in map for easier iteration
          /// Could use vector, but to match NREO model parameters we don't want to start indices at zero. I think this is less confusing?
          std::map<int,double> c0;
          std::map<int,double> c1;
          /// Function to prettify retrieval of couplings (also helpful for looping over 1,0 isospin integers, and error-checking operator numbers)
          double c(int,int) const;
  };

  struct DD_coupling_container
  {
    int coeff_structure;  // Simple integer to tell DDCalc which effective operators to set the WIMP object up with.
    DM_nucleon_couplings          DM_nucleon_coeffs; // Corresponds to int = 1. Direct DM-nucleon interactions.
    //std::map<std::string,double>  DD_nonrel_WCs;     // Corresponds to int = 2. Effective non-relativistic DM-nucleon Wilson coefficients.
    NREO_DM_nucleon_couplings     DD_nonrel_WCs; // Corresponds to int = 2. Effective non-relativistic DM-nucleon Wilson coefficients.
  };

}

#endif /* defined __DDCalc_types_hpp__ */
