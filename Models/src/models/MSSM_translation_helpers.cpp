//
///  GAMBIT: Global and Modular BSM Inference Tool
///  *********************************************
///
///  Function implementations for MSSM translation
///  helpers.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///  \date 2015 Aug, 2017 Oct
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2018 Oct
///
///  *********************************************

#include <string>
#include <vector>

#include "gambit/Models/models/MSSM_translation_helpers.hpp"
#include "gambit/Elements/spectrum.hpp"

namespace Gambit
{

  void MSSMatX_to_MSSMatQ(const ModelParameters &myP, ModelParameters &targetP, const SubSpectrum& HE)
  {
    // Copy all the parameters of MSSM63atMGUT into MSSM63atQ
    targetP.setValues(myP);

    // Now only the "Qin" parameter is left unset. Need to extract this from the Spectrum object dependency.
    // Make sure the high-scale value was correctly added to the spectrum wrapper object
    if( HE.has(Par::mass1,"high_scale") )
    {
       targetP.setValue("Qin", HE.get(Par::mass1,"high_scale") );
    }
    else
    {
       model_error().raise(LOCAL_INFO,"Parameter with name 'high_scale' (type Par::mass1) not found in Spectrum object! Translation from MSSM63at<X> to MSSM63atQ is not possible without this value. Please use a Spectrum wrapper which provides it.");
    }
    // Done!
  }

  void MSSM_mA_to_MSSM_mhud(const ModelParameters &myP, ModelParameters &targetP, const SubSpectrum& HE)
  {
     // Copy all the common parameters of MSSM63at<X>_mA into MSSM63at<X>
     targetP.setValues(myP,false); // Set "missing_is_error" flag to false since e.g. mA parameter from MSSM63atQ_mA does not exist in MSSM63atQ. Similar for variants at other scales.

     // Set the sign of mu
     targetP.setValue("SignMu", Gambit::sgn(myP["mu"]));

     // Now only the "mHu2" and "mHd2" parameters are left unset. Extract these from the Spectrum object dependency.
     // Make sure the high-scale value was correctly added to the spectrum wrapper object
     if (HE.has(Par::mass2,"mHu2") and HE.has(Par::mass2,"mHd2"))
     {
        targetP.setValue("mHu2", HE.get(Par::mass2,"mHu2"));
        targetP.setValue("mHd2", HE.get(Par::mass2,"mHd2"));
     }
     else
     {
        model_error().raise(LOCAL_INFO,"Parameter with name 'mHu2' or 'mHd2' (type Par::mass2) not found in Spectrum object! "
                                       "Translation from MSSM<X>_mA to MSSM<X> is not possible without this value. "
                                       "Please use a Spectrum wrapper that provides it.");
     }

  }

  void MSSM20atX_to_MSSM25atX(const ModelParameters &myP, ModelParameters &targetP)
  {
     // Send all parameter values upstream to matching parameters in parent.
     // Ignore that some parameters don't exist in the parent, these are set below.
     targetP.setValues(myP,false);

     // RH squark soft masses, gen 1 and 2
     targetP.setValue("mq2_1",  myP["mq2_12"] ); // mq2_11 in MSSM63
     targetP.setValue("mq2_2",  myP["mq2_12"] ); // mq2_22   " "
     // RH slepton soft masses, gen 1 and 2
     targetP.setValue("ml2_1",  myP["ml2_12"] ); // ml2_11 in MSSM63
     targetP.setValue("ml2_2",  myP["ml2_12"] ); // ml2_22   " "
     // LH down-type squark soft masses
     targetP.setValue("md2_1",  myP["md2_12"] ); // ml2_11 in MSSM63
     targetP.setValue("md2_2",  myP["md2_12"] ); // ml2_22   " "
     // LH up-type squark soft masses
     targetP.setValue("mu2_1",  myP["mu2_12"] ); // mu2_11 in MSSM63
     targetP.setValue("mu2_2",  myP["mu2_12"] ); // mu2_22   " "
     // LH charged slepton soft masses
     targetP.setValue("me2_1",  myP["me2_12"] ); // me2_11 in MSSM63
     targetP.setValue("me2_2",  myP["me2_12"] ); // me2_22   " "
     // Done
  }

  void MSSM25atX_to_MSSM30atX(const ModelParameters &myP, ModelParameters &targetP)
  {
     // Copy all the common parameters of MSSM25atX into MSSM30atX
     targetP.setValues(myP,false);

     // Manually set the parameters which differ
     // slepton trilinear couplings
     // Off-diagonal elements set to zero by parent model
     // First and second generation elements set equal
     targetP.setValue("Ae_1",  myP["Ae_12"] ); // Ae2_11 in MSSM63
     targetP.setValue("Ae_2",  myP["Ae_12"] ); // Ae2_22   " "
     //targetP.setValue("Ae_3",  myP["Ae_3"]  ); // Ae2_33 // Taken care of by common parameter copy

     // down-type trilinear couplings
     // Off-diagonal elements set to zero by parent model
     // First and second generation to zero
     targetP.setValue("Ad_1",  0. );          // Ad2_11 in MSSM63
     targetP.setValue("Ad_2",  0. );          // Ad2_22   " "
     //targetP.setValue("Ad_3",  myP["Ad_3"] ); // Ad2_33 // Taken care of by common parameter copy

     // up-type trilinear couplings
     // Off-diagonal elements set to zero by parent model
     // First and second generation set to zero
     targetP.setValue("Au_1",  0. );          // Au2_11 in MSSM63
     targetP.setValue("Au_2",  0. );          // Au2_22   " "
     // targetP.setValue("Au_3",  myP["Au_3"] ); // Au2_33 // Taken care of by common parameter copy

     // Done
  }

  void MSSM30atX_to_MSSM63atX(const ModelParameters &myP, ModelParameters &targetP)
  {

     // Copy all common parameters of MSSM30atX into MSSM63atX
     targetP.setValues(myP,false);

     // Manually set parameters that differ

     // RH squark soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("mq2_11",  myP["mq2_1"] );
     targetP.setValue("mq2_12",  0. );
     targetP.setValue("mq2_13",  0. );

     //targetP.setValue("mq2_21",  0. );
     targetP.setValue("mq2_22",  myP["mq2_2"] );
     targetP.setValue("mq2_23",  0. );

     //targetP.setValue("mq2_31",  0. );
     //targetP.setValue("mq2_32",  0. );
     targetP.setValue("mq2_33",  myP["mq2_3"] );

     // RH slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("ml2_11",  myP["ml2_1"] );
     targetP.setValue("ml2_12",  0. );
     targetP.setValue("ml2_13",  0. );

     //targetP.setValue("ml2_21",  0. );
     targetP.setValue("ml2_22",  myP["ml2_2"] );
     targetP.setValue("ml2_23",  0. );

     //targetP.setValue("ml2_31",  0. );
     //targetP.setValue("ml2_32",  0. );
     targetP.setValue("ml2_33",  myP["ml2_3"] );

     // LH down-type slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("md2_11",  myP["md2_1"] );
     targetP.setValue("md2_12",  0. );
     targetP.setValue("md2_13",  0. );

     //targetP.setValue("md2_21",  0. );
     targetP.setValue("md2_22",  myP["md2_2"] );
     targetP.setValue("md2_23",  0. );

     //targetP.setValue("md2_31",  0. );
     //targetP.setValue("md2_32",  0. );
     targetP.setValue("md2_33",  myP["md2_3"] );

     // LH up-type slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("mu2_11",  myP["mu2_1"] );
     targetP.setValue("mu2_12",  0. );
     targetP.setValue("mu2_13",  0. );

     //targetP.setValue("mu2_21",  0. );
     targetP.setValue("mu2_22",  myP["mu2_2"] );
     targetP.setValue("mu2_23",  0. );

     //targetP.setValue("mu2_31",  0. );
     //targetP.setValue("mu2_32",  0. );
     targetP.setValue("mu2_33",  myP["mu2_3"] );

     // LH charged slepton soft masses
     // Off-diagonal elements set to zero
     // Only upper diagonal needed (symmetric)
     targetP.setValue("me2_11",  myP["me2_1"] );
     targetP.setValue("me2_12",  0. );
     targetP.setValue("me2_13",  0. );

     //targetP.setValue("me2_21",  0. );
     targetP.setValue("me2_22",  myP["me2_2"] );
     targetP.setValue("me2_23",  0. );

     //targetP.setValue("me2_31",  0. );
     //targetP.setValue("me2_32",  0. );
     targetP.setValue("me2_33",  myP["me2_3"] );

     // slepton trilinear couplings
     // Off-diagonal elements set to zero
     targetP.setValue("Ae_11",  myP["Ae_1"] );
     targetP.setValue("Ae_12",  0. );
     targetP.setValue("Ae_13",  0. );

     targetP.setValue("Ae_21",  0. );
     targetP.setValue("Ae_22",  myP["Ae_2"] );
     targetP.setValue("Ae_23",  0. );

     targetP.setValue("Ae_31",  0. );
     targetP.setValue("Ae_32",  0. );
     targetP.setValue("Ae_33",  myP["Ae_3"] );

     // down-type trilinear couplings
     // Off-diagonal elements set to zero
     // First and second generation to zero
     targetP.setValue("Ad_11",  myP["Ad_1"] );
     targetP.setValue("Ad_12",  0. );
     targetP.setValue("Ad_13",  0. );

     targetP.setValue("Ad_21",  0. );
     targetP.setValue("Ad_22",  myP["Ad_2"] );
     targetP.setValue("Ad_23",  0. );

     targetP.setValue("Ad_31",  0. );
     targetP.setValue("Ad_32",  0. );
     targetP.setValue("Ad_33",  myP["Ad_3"] );

     // up-type trilinear couplings
     // Off-diagonal elements set to zero
     // First and second generation set to zero
     targetP.setValue("Au_11",  myP["Au_1"] );
     targetP.setValue("Au_12",  0. );
     targetP.setValue("Au_13",  0. );

     targetP.setValue("Au_21",  0. );
     targetP.setValue("Au_22",  myP["Au_2"] );
     targetP.setValue("Au_23",  0. );

     targetP.setValue("Au_31",  0. );
     targetP.setValue("Au_32",  0. );
     targetP.setValue("Au_33",  myP["Au_3"] );

     // Done!
  }


}


