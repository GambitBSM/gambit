//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit
///
///  SpecBit module functions related to the
///  Standard Model.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - Mar
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2019 Nov
///
///  *********************************************

#include <string>
#include <sstream>

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/RegisteredSpectra.hpp"

// Switch for debug mode
//#define SpecBit_DBUG

namespace Gambit
{

  namespace SpecBit
  {
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

         sminputs.mNu1     = *myPipe::Param["mNu1"    ];
         sminputs.mNu2     = *myPipe::Param["mNu2"    ];
         sminputs.mNu3     = *myPipe::Param["mNu3"    ];

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

         // W mass.  Stick with the observed value (set in the default constructor) unless instructed otherwise.
         if (myPipe::runOptions->getValueOrDef<bool>(false,"enforce_tree_level_MW"))
         {
           // Calculate MW from alpha, mZ and G_F, assuming the tree-level relation.
           const double pionroot2 = pi * pow(2,-0.5);
           double cosW2 = 0.5 + pow(0.25 - pionroot2 / (sminputs.alphainv * sminputs.GF * pow(sminputs.mZ,2.0)), 0.5);
           sminputs.mW = sminputs.mZ * pow(cosW2,0.5);
         }

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


    /// Get a Spectrum object for Standard-Model-only information
    void get_SM_spectrum(Spectrum &result)
    {
      namespace myPipe = Pipes::get_SM_spectrum;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Initialise an SLHAea object to carry the SM information
      SLHAea::Coll slha;
      SLHAea_add_block(slha, "SMINPUTS");
      SLHAea_add_block(slha, "SINTHETAW");
      SLHAea_add_block(slha, "MASS");
      SLHAea_add_block(slha, "VEVS");
      SLHAea_add_block(slha, "VCKM");
      SLHAea_add_block(slha, "UPMNS");

      // SMInputs parameters
      slha["SMINPUTS"][""] << 1 << sminputs.alphainv << "# alphainv";
      slha["SMINPUTS"][""] << 2 << sminputs.GF << "# GF";
      slha["SMINPUTS"][""] << 3 << sminputs.alphaS << "# alphaS";

      slha["SMINPUTS"][""] << 4 << sminputs.mZ << "# mZ";

      slha["SMINPUTS"][""] << 5 << sminputs.mBmB << "# mb(mb)";
      slha["SMINPUTS"][""] << 6 << sminputs.mT << "# mt";
      slha["SMINPUTS"][""] << 7 << sminputs.mTau << "# mtau";

      slha["SMINPUTS"][""] << 8 << sminputs.mNu3 << "# mnu_tau";
      slha["SMINPUTS"][""] << 11 << sminputs.mE << "# me";
      slha["SMINPUTS"][""] << 12 << sminputs.mNu1 << "# mnu_e";
      slha["SMINPUTS"][""] << 13 << sminputs.mMu << "# mmu";
      slha["SMINPUTS"][""] << 14 << sminputs.mNu2 << "# mnu_mu";

      slha["SMINPUTS"][""] << 21 << sminputs.mD << "# md(2 GeV)";
      slha["SMINPUTS"][""] << 22 << sminputs.mU << "# mu(2 GeV)";
      slha["SMINPUTS"][""] << 23 << sminputs.mS << "# ms(2 GeV)";
      slha["SMINPUTS"][""] << 24 << sminputs.mCmC << "# mc(mc)";

      // Weinberg angle
      double alpha_em = 1.0 / sminputs.alphainv;
      double C = alpha_em * pi / (sminputs.GF * pow(2,0.5));
      double sinW2 = 0.5 - pow( 0.25 - C/pow(sminputs.mZ,2) , 0.5);
      slha["SINTHETAW"][""] << 2 << sinW2 << "# sinW2";

      // Pole masses and masses not in sminputs
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("gamma").first << 0 << "# gamma";
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("g").first << 0 << "# g";
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("W+").first << sminputs.mW << "# mW";

      // For the bottom quark, we compute its pole mass
      // We take the sminputs msbar mass and pass it as a pole mass
      double mb = sminputs.mBmB;
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("b").first << mb << "# mb";

      // Charged lepton masses are pole mass in sminputs
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("e-").first << sminputs.mE << "# me";
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("mu-").first << sminputs.mMu << "# mmu";
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("tau-").first << sminputs.mTau << "# mtau";

      // Top quark is a pole mass in sminputs
      slha["MASS"][""] << Models::ParticleDB().pdg_pair("t").first << sminputs.mT << "# mt";

      // Higgs mass and vev
      double mh   = *myPipe::Param.at("mH");
      std::pair<int,int> pdg = Models::ParticleDB().pdg_pair("h0_1");
      slha["MASS"][""] << pdg.first << mh << "# mH";

      double vev = 1. / sqrt(sqrt(2.)*sminputs.GF);
      slha["VEVS"][""] << 1 << vev << " # vev";

      // CKM matrix
      slha["VCKM"][""] << 1 << sminputs.CKM.lambda << "# lambda (CKM)";
      slha["VCKM"][""] << 2 << sminputs.CKM.A << "# A (CKM)";
      slha["VCKM"][""] << 3 << sminputs.CKM.rhobar << "# rhobar (CKM)";
      slha["VCKM"][""] << 4 << sminputs.CKM.etabar << "# etabar (CKM)";

      // PMNS matrix
      slha["UPMNS"][""] << 1 << sminputs.PMNS.theta12 << "# theta_12 (PMNS)";
      slha["UPMNS"][""] << 2 << sminputs.PMNS.theta23 << "# theta_23 (PMNS)";
      slha["UPMNS"][""] << 3 << sminputs.PMNS.theta13 << "# theta_13 (PMNS)";
      slha["UPMNS"][""] << 4 << sminputs.PMNS.delta13 << "# delta_13 (PMNS)";
      slha["UPMNS"][""] << 5 << sminputs.PMNS.alpha1 << "# alpha_1 (PMNS)";
      slha["UPMNS"][""] << 6 << sminputs.PMNS.alpha2 << "# alpha_2 (PMNS)";

      // SpectrumContents struct
      SpectrumContents::SM sm;

      // Create spectrum object
      // Take mZ as the spectrum scale
      result = Spectrum(slha, sm, sminputs.mZ, false);

      // Retrieve any mass cuts
      result.check_mass_cuts(*myPipe::runOptions);
    }

    /// Put together the SM Higgs couplings
    void SM_higgs_couplings(HiggsCouplingsTable &result)
    {
      using namespace Pipes::SM_higgs_couplings;
      // Set the number of Higgses
      result.set_n_neutral_higgs(1);
      result.set_n_charged_higgs(0);
      // Set the CP of the Higgs.
      result.CP[0] = 1;
      // Set the decays
      result.set_neutral_decays_SM(0, "h0_1", *Dep::Higgs_decay_rates);
      result.set_neutral_decays(0, "h0_1", *Dep::Higgs_decay_rates);
      // Leave all the effective couplings for all neutral higgses set to unity (done at construction).
    }

    /// @} End Gambit module functions

  } // end namespace SpecBit
} // end namespace Gambit

