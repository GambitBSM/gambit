//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Helper functions for SMInputs struct
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

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Elements/sminputs.hpp"
#include "gambit/Elements/mssm_slhahelp.hpp"

namespace Gambit
{

   // Create an SMInputs struct from an SLHAea object
   SMInputs::SMInputs(SLHAea::Coll& data)
   {
      // Defaults set from PDG 2014.
      // * from http://pdg.lbl.gov/2014/reviews/rpp2014-rev-standard-model.pdf
      // ** from http://pdg.lbl.gov/2014/reviews/rpp2014-rev-phys-constants.pdf
      //  § from http://pdg.lbl.gov/2014/tables/rpp2014-sum-leptons.pdf
      //  @ from http://pdg.lbl.gov/2014/tables/rpp2014-sum-quarks.pdf
      //    (for reference: http://pdg.lbl.gov/2014/reviews/rpp2014-rev-quark-masses.pdf)
      //  $ from http://arxiv.org/abs/1403.4427
      //  ! from http://pdg.lbl.gov/2014/listings/rpp2014-list-z-boson.pdf
      //  & from http://pdg.lbl.gov/2014/listings/rpp2014-list-b-quark.pdf
      //  % from http://pdg.lbl.gov/2014/listings/rpp2014-list-c-quark.pdf
      //  ^ from http://pdg.lbl.gov/2014/reviews/rpp2014-rev-qcd.pdf
      // If more than one source listed, values are equal in both sources.
      // Values in GeV where units apply.
      // SLHA1
      alphainv = SLHAea_get(data,"SMINPUTS",1 , 1.27940010E+02);   // alpha^{-1}(mZ)^MSbar *
      GF       = SLHAea_get(data,"SMINPUTS",2 , 1.16637870E-05);   // G_Fermi **
      alphaS   = SLHAea_get(data,"SMINPUTS",3 , 1.18500000E-01);   // alpha_s(mZ)^MSbar ^
      mZ       = SLHAea_get(data,"SMINPUTS",4 , 9.11876000E+01);   // mZ(pole) !
      mBmB     = SLHAea_get(data,"SMINPUTS",5 , 4.18000000E+00);   // mb(mb)^MSbar &
      mT       = SLHAea_get(data,"SMINPUTS",6 , 1.73340000E+02);   // mtop(pole) $
      mTau     = SLHAea_get(data,"SMINPUTS",7 , 1.77682000E+00);   // mtau(pole) §
      mNu3     = SLHAea_get(data,"SMINPUTS",8 ,              0);   // mnu3(pole)
      // SLHA2
      mE       = SLHAea_get(data,"SMINPUTS",11, 5.10998928E-04);   // melectron(pole) § **
      mNu1     = SLHAea_get(data,"SMINPUTS",12,              0);   // mnu1(pole)
      mMu      = SLHAea_get(data,"SMINPUTS",13, 1.05658372E-01);   // mmuon(pole) §
      mNu2     = SLHAea_get(data,"SMINPUTS",14,              0);   // mnu2(pole)
      mD       = SLHAea_get(data,"SMINPUTS",21, 4.80000000E-03);   // md(2 GeV)^MSbar @
      mU       = SLHAea_get(data,"SMINPUTS",22, 2.30000000E-03);   // mu(2 GeV)^MSbar @
      mS       = SLHAea_get(data,"SMINPUTS",23, 9.50000000E-02);   // ms(2 GeV)^MSbar @
      mCmC     = SLHAea_get(data,"SMINPUTS",24, 1.27500000E+00);   // mc(mc)^MSbar %

      // W boson mass
      // This is an output according to SLHA, however in cases where a spectrum generator doesn't run we
      // will still need it, for example in the SMSimpleSpec wrapper.  Default from numerical-constants.hpp.
      mW       = SLHAea_get(data,"MASS", 24, mw_central_observed);

      // CKM parameters
      // from http://pdg.lbl.gov/2014/reviews/rpp2014-rev-ckm-matrix.pdf
      CKM.lambda = SLHAea_get(data,"VCKMIN",1, 0.22537);
      CKM.A      = SLHAea_get(data,"VCKMIN",2, 0.814);
      CKM.rhobar = SLHAea_get(data,"VCKMIN",3, 0.117);
      CKM.etabar = SLHAea_get(data,"VCKMIN",4, 0.353);

      // PMNS parameters
      // from     http://pdg.lbl.gov/2014/tables/rpp2014-sum-leptons.pdf
      // see also http://pdg.lbl.gov/2014/reviews/rpp2014-rev-neutrino-mixing.pdf
      // Note: angles given as x = sin^2(2*theta), so I have converted them as:
      // theta = 0.5*arcsin(sqrt(x))
      // CP-violating phases not measured, so I set them to zero.
      PMNS.theta12 = SLHAea_get(data,"UPMNSIN",1, 0.58376); // the solar angle
      PMNS.theta23 = SLHAea_get(data,"UPMNSIN",2, 0.76958); // the atmospheric mixing angle
      PMNS.theta13 = SLHAea_get(data,"UPMNSIN",3, 0.15495);
      PMNS.delta13 = SLHAea_get(data,"UPMNSIN",4, 0);       // the Dirac CP-violating phase
      PMNS.alpha1  = SLHAea_get(data,"UPMNSIN",5, 0);       // the first Majorana CP-violating phase
      PMNS.alpha2  = SLHAea_get(data,"UPMNSIN",6, 0);       // the second CP-violating Majorana phase
   }

   // Return a fresh SLHAea object containing the contents of this object.
   SLHAstruct SMInputs::getSLHAea() const
   {
      SLHAstruct slha;
      this->add_to_SLHAea(slha);
      slhahelp::add_MODSEL_disclaimer(slha, "spectrum");
      return slha;
   }

   // Add the contents of this object to an existing SLHAea object.
   void SMInputs::add_to_SLHAea(SLHAea::Coll& data) const
   {
      // SMINPUTS block
      SLHAea_add(data,"SMINPUTS",1 , alphainv, "alpha^{-1}(mZ)^MSbar");
      SLHAea_add(data,"SMINPUTS",2 , GF      , "G_Fermi"             );
      SLHAea_add(data,"SMINPUTS",3 , alphaS  , "alpha_s(mZ)^MSbar"   );
      SLHAea_add(data,"SMINPUTS",4 , mZ      , "mZ(pole)"            );
      SLHAea_add(data,"SMINPUTS",5 , mBmB    , "mb(mb)^MSbar"        );
      SLHAea_add(data,"SMINPUTS",6 , mT      , "mtop(pole)"          );
      SLHAea_add(data,"SMINPUTS",7 , mTau    , "mtau(pole)"          );
      SLHAea_add(data,"SMINPUTS",8 , mNu3    , "mnu3(pole)"          );

      SLHAea_add(data,"SMINPUTS",11, mE      , "melectron(pole)"     );
      SLHAea_add(data,"SMINPUTS",12, mNu1    , "mnu1(pole)"          );
      SLHAea_add(data,"SMINPUTS",13, mMu     , "mmuon(pole)"         );
      SLHAea_add(data,"SMINPUTS",14, mNu2    , "mnu2(pole)"          );
      SLHAea_add(data,"SMINPUTS",21, mD      , "md(2 GeV)^MSbar"     );
      SLHAea_add(data,"SMINPUTS",22, mU      , "mu(2 GeV)^MSbar"     );
      SLHAea_add(data,"SMINPUTS",23, mS      , "ms(2 GeV)^MSbar"     );
      SLHAea_add(data,"SMINPUTS",24, mCmC    , "mc(mc)^MSbar"        );

      // VCKMIN block
      SLHAea_add(data,"VCKMIN",1, CKM.lambda, "lambda");
      SLHAea_add(data,"VCKMIN",2, CKM.A     , "A"     );
      SLHAea_add(data,"VCKMIN",3, CKM.rhobar, "rhobar");
      SLHAea_add(data,"VCKMIN",4, CKM.etabar, "etabar");

      // UPMNSIN block
      SLHAea_add(data,"UPMNSIN",1, PMNS.theta12, "theta12 (solar angle)");
      SLHAea_add(data,"UPMNSIN",2, PMNS.theta23, "theta23 (atmospheric mixing angle)");
      SLHAea_add(data,"UPMNSIN",3, PMNS.theta13, "theta13");
      SLHAea_add(data,"UPMNSIN",4, PMNS.delta13, "delta13 (Dirac CP-violating phase)");
      SLHAea_add(data,"UPMNSIN",5, PMNS.alpha1 , "alpha1 (first Majorana CP-violating phase)" );
      SLHAea_add(data,"UPMNSIN",6, PMNS.alpha2 , "alpha2 (second CP-violating Majorana phase)");

      // MASS block
      SLHAea_add(data,"MASS", 24, mW, "mW(pole)");

      return;
   }


} // end namespace Gambit

