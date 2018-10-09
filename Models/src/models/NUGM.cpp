//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  NUGM model declarations. 
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Tomas Gonzalo  
///          (tomas.gonzalo@monash.edu)
///  \date 2018 Oct
///
///  *********************************************

#include "gambit/Models/model_macros.hpp"
#include "gambit/Models/model_helpers.hpp"
#include "gambit/Logs/logger.hpp"

#include "gambit/Models/models/NUGM.hpp"


#define MODEL NUGM
  void MODEL_NAMESPACE::NUGM_to_MSSM63atMGUT (const ModelParameters &myP, ModelParameters &targetP)
  {

     logger()<<"Running interpret_as_parent calculations for NUGM --> MSSM63atMGUT."<<LogTags::info<<EOM;
     
     targetP.setValue("TanBeta", myP["TanBeta"] );
     targetP.setValue("SignMu",  myP["SignMu"] );

     // M0
     static const char *M0init[] = {
       "mq2_11", "mq2_22", "mq2_33",
       /**/
       "ml2_11", "ml2_22", "ml2_33",
       /**/
       "md2_11", "md2_22", "md2_33",
       /**/
       "mu2_11", "mu2_22", "mu2_33",
       /**/
       "me2_11", "me2_22", "me2_33"
       };
     static const std::vector<std::string> M0vec(M0init,Utils::endA(M0init));
     double M0 = myP["M0"];
     set_many_to_one(targetP, M0vec, M0*M0);

     // Off diaginal soft scalara 
     static const char *m2ODinit[] = {
       "mq2_12", "mq2_13", "mq2_23",
       /**/
       "ml2_12", "ml2_13", "ml2_23",
       /**/
       "md2_12", "md2_13", "md2_23",
       /**/
       "mu2_12", "mu2_13", "mu2_23",
       /**/
       "me2_12", "me2_13", "me2_23"
       };
     static const std::vector<std::string> m2ODvec(m2ODinit,Utils::endA(m2ODinit));
     set_many_to_one(targetP,m2ODvec, 0.0);



     
     // MH2
     double mHu = myP["M0"];
     double mHd = myP["M0"];
     targetP.setValue("mHu2", mHu*mHu);
     targetP.setValue("mHd2", mHd*mHd);

     // M12
     targetP.setValue("M1",  myP["M1"] );
     targetP.setValue("M2",  myP["M2"] );
     targetP.setValue("M3",  myP["M3"] );

     // A0
     static const char *A0init[] = {
       "Ae_11", "Ae_22", "Ae_33",
       /**/
       "Ae_12", "Ae_13", "Ae_21",
       /**/
       "Ae_23", "Ae_31", "Ae_32",
       /**/
       "Ad_11", "Ad_22", "Ad_33",
       /**/
       "Ad_12", "Ad_13", "Ad_21",
       /**/
       "Ad_23", "Ad_31", "Ad_32",
       /**/
       "Au_11", "Au_22", "Au_33",
       /**/
       "Au_12", "Au_13", "Au_21",
       /**/
       "Au_23", "Au_31", "Au_32"
       };
     static const std::vector<std::string> A0vec(A0init,Utils::endA(A0init));
     set_many_to_one(targetP, A0vec, myP["A0"]);

  }

#undef MODEL


