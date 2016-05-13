//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions shared by several
///  models, or otherwise generic.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (ben.farmer@gmail.com)
///  \date 2015 Aug
///  
///  *********************************************

#include <string>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/SpecBit/SpecBit_rollcall.hpp"

// QedQcd header from SoftSUSY (via FlexibleSUSY)
#include "flexiblesusy/src/lowe.h"

namespace Gambit
{

  namespace SpecBit
  {
    using namespace LogTags;

    // To check if a model is currently being scanned:
    // bool Pipes::<fname>::ModelInUse(str model_name)


    /// @{ Non-Gambit helper functions
    //  =======================================================================
    //  These are not known to Gambit, but they do basically all the real work.
    //  The Gambit module functions merely wrap the functions here and hook 
    //  them up to their dependencies, and input parameters.

    /// Initialise QedQcd object from SMInputs data
    void setup_QedQcd(softsusy::QedQcd& oneset /*output*/, const SMInputs& sminputs /*input*/)
    {
      /// set QED and QCD structure constants, and Fermi constant
      oneset.setAlpha(softsusy::ALPHA, 1./sminputs.alphainv);  // 1
      oneset.setFermiConstant(sminputs.GF);                    // 2
      oneset.setAlpha(softsusy::ALPHAS, sminputs.alphaS);      // 3
 
      // Set pole masses  
      oneset.setPoleMZ(sminputs.mZ);                           // 4
      softsusy::MZ = sminputs.mZ; // TODO! This is setting some global constant? Not very nice... but this is what FlexibleSUSY does, see flexiblesusy/src/slha_io.cpp  
      oneset.setMass(softsusy::mBottom, sminputs.mBmB);        // 5      
      oneset.setMbMb(sminputs.mBmB);                           // "
      //oneset.setPoleMb(...); ??
      oneset.setPoleMt(sminputs.mT);                           // 6
      oneset.setMass(softsusy::mTau, sminputs.mTau);           // 7                             
      oneset.setPoleMtau(sminputs.mTau);                       // "
      //oneset.setPoleMW(value);                               // 9 TODO: do we want to add this?

      /// NOTE! These assume the input electron and muon pole masses are "close
      /// enough" to MSbar masses at MZ. The object does the same with its 
      /// default values so I guess it is ok.
      oneset.setMass(softsusy::mElectron, sminputs.mE);       // 11
      oneset.setMass(softsusy::mMuon,     sminputs.mMu);      // 13

      /// Neutrino pole masses
      oneset.setNeutrinoPoleMass(3, sminputs.mNu3);           // 8
      oneset.setNeutrinoPoleMass(1, sminputs.mNu1);           // 12
      oneset.setNeutrinoPoleMass(2, sminputs.mNu2);           // 14  

      /// Running quark masses
      oneset.setMass(softsusy::mDown,    sminputs.mD);        // 21
      oneset.setMass(softsusy::mUp,      sminputs.mU);        // 22
      oneset.setMass(softsusy::mStrange, sminputs.mS);        // 23
      oneset.setMass(softsusy::mCharm,   sminputs.mCmC);      // 24

      /// Check:
      std::cout << "qedqcd mElectron:" << oneset.displayMass(softsusy::mElectron) << std::endl;
    }

    /// @} End module convenience functions

  
    /// @{ Gambit module functions 
    //  =======================================================================
    //  These are wrapped up in Gambit functor objects according to the
    //  instructions in the rollcall header

    /// Set SMINPUTS (SLHA2) struct to match StandardModel_SLHA2 parameters.
    //  Effectively just changes these model parameters into a more convenient form.
    //  But also opens up the possibility of rebuilding this struct from some other
    //  parameterisation.
    void get_SMINPUTS(SMInputs &result)
    {
      namespace myPipe = Pipes::get_SMINPUTS;
      SMInputs sminputs; 
      
      // Get values from Params pipe
      // (as defined in SLHA2)
      if(myPipe::ModelInUse("StandardModel_SLHA2"))
      {
         sminputs.alphainv = *myPipe::Param["alphainv"];
         sminputs.GF       = *myPipe::Param["GF"      ];
         sminputs.alphaS   = *myPipe::Param["alphaS"  ];

         sminputs.mZ       = *myPipe::Param["mZ"      ]; 

         sminputs.mE       = *myPipe::Param["mE"      ];
         sminputs.mMu      = *myPipe::Param["mMu"     ];
         sminputs.mTau     = *myPipe::Param["mTau"    ];

         sminputs.mNu1     = *myPipe::Param["mNu1"    ];
         sminputs.mNu2     = *myPipe::Param["mNu2"    ];
         sminputs.mNu3     = *myPipe::Param["mNu3"    ];

         sminputs.mD       = *myPipe::Param["mD"      ];
         sminputs.mU       = *myPipe::Param["mU"      ];
         sminputs.mS       = *myPipe::Param["mS"      ];
         sminputs.mCmC     = *myPipe::Param["mCmC"    ];
         sminputs.mBmB     = *myPipe::Param["mBmB"    ]; 
         sminputs.mT       = *myPipe::Param["mT"      ];

         // CKM
         sminputs.CKM.lambda   = *myPipe::Param["CKM_lambda" ];
         sminputs.CKM.A        = *myPipe::Param["CKM_A" ];
         sminputs.CKM.rhobar   = *myPipe::Param["CKM_rhobar" ];
         sminputs.CKM.etabar   = *myPipe::Param["CKM_etabar" ];
               
         // PMNS 
         sminputs.PMNS.theta12 = *myPipe::Param["theta12"];
         sminputs.PMNS.theta23 = *myPipe::Param["theta23"];
         sminputs.PMNS.theta13 = *myPipe::Param["theta13"];
         sminputs.PMNS.delta13 = *myPipe::Param["delta13"];
         sminputs.PMNS.alpha1  = *myPipe::Param["alpha1"];
         sminputs.PMNS.alpha2  = *myPipe::Param["alpha2"];

      }
      else
      {
         std::ostringstream errmsg;
         errmsg << "Error mapping Standard Model parameters to SMINPUTS capabilities!";
         errmsg << "Perhaps you have added a new model to the ALLOWED_MODELS of this ";
         errmsg << "module function but have not added a corresponding case in the ";
         errmsg << "function source (here)." << std::endl;
         SpecBit_error().raise(LOCAL_INFO,errmsg.str());  
      }
      // Return filled struct
      result = sminputs;
    }

    /// @} End Gambit module functions

  } // end namespace SpecBit
} // end namespace Gambit

