//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Parameters used to define the Standard Model,
///  in SLHA2 format.
///
///  *********************************************
///
///  Authors:
///  <!-- add name and date if you modify -->
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Mar
///
///  *********************************************

#ifndef __SMInputs_hpp__
#define __SMInputs_hpp__

#include "gambit/Utils/slhaea_helpers.hpp"
#include "gambit/Utils/numerical_constants.hpp"

namespace Gambit
{

   /// Container class for Standard Model input information (defined as in SLHA2)
   struct SMInputs
   {

     // Default constructor
     SMInputs() {}

     // Create an SMInputs struct from an SLHAea object
     SMInputs(SLHAstruct&);

      // Block SMINPUTS
      // SLHA1
      double alphainv;  // 1: Inverse electromagnetic coupling at the Z pole in the MSbar scheme (with 5 active flavours)
      double GF;        // 2: Fermi constant (in units of GeV^-2)
      double alphaS;    // 3: Strong coupling at the Z pole in the MSbar scheme (with 5 active flavours).
      double mZ;        // 4: Z pole mass
      double mBmB;      // 5: b quark running mass in the MSbar scheme (at mB)
      double mT;        // 6: Top quark pole mass
      double mTau;      // 7: Tau pole mass

      // SLHA2
      double mNu3;      // 8: Heaviest neutrino pole mass

      double mE;        // 11: Electron pole mass
      double mNu1;      // 12: Lightest neutrino pole mass
      double mMu;       // 13: Muon pole mass
      double mNu2;      // 14: Second lightest neutrino pole mass

      double mD;        // 21: d quark running mass in the MSbar scheme at 2 GeV
      double mU;        // 22: u quark running mass in the MSbar scheme at 2 GeV
      double mS;        // 23: s quark running mass in the MSbar scheme at 2 GeV
      double mCmC;      // 24: c quark running mass in the MSbar scheme at mC

      // Block VCKMIN
      // Note: from SLHA2 manual:
      // "The input CKM matrix in the Wolfenstein parameterisation
      // Note that present CKM studies do not precisely define a
      // renormalisation scheme for this matrix since the electroweak
      // effects that renormalise it are highly suppressed and
      // generally neglected. We therefore assume that the CKM elements
      // given by PDG (or by UTFit[31] and CKMFitter [32], the main
      // collaborations that extract the CKM parameters) refer to SM
      // MSbar quantities defined at Q=mZ, to avoid any possible ambiguity."
      struct CKMdef
      {
        double lambda;
        double A;
        double rhobar;
        double etabar;
      };
      CKMdef CKM;

      // Block UPMNSIN
      // PDG parameterisation in terms of rotation angles (all in radians)
      struct PMNSdef
      {
        double theta12; // the solar angle
        double theta23; // the atmospheric mixing angle
        double theta13; // the reactor mixing angle
        double delta13; // the Dirac CP-violating phase
        double alpha1;  // the first Majorana CP-violating phase
        double alpha2;  // the second CP-violating Majorana phase
      };
      PMNSdef PMNS;

      // Block MASS
      // Just need W boson mass. Usually an output (according to SLHA), but
      // in some cases we do not generate a spectrum, so we need a default
      double mW = mw_central_observed; // 24: W pole mass

      // Return a fresh SLHAea object containing the contents of this object.
      SLHAstruct getSLHAea() const;

      // Add the contents of this object to an existing SLHAea object
      void add_to_SLHAea(SLHAstruct& slha /*modify*/) const;

   };

} // end namespace Gambit

#endif
