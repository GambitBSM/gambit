//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of module SpecBit, model MSSM
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Ben Farmer
///          (benjamin.farmer@fysik.su.se)
///    \date 2014 Sep - Dec, 2015 Jan - Mar
///
///  \author Christopher Rogan
///          (christophersrogan@gmail.com)
///  \date 2015 Apr
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date 2016 June, 2019 Oct-Nov
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015, 2016
///
///  *********************************************

#include "gambit/Utils/slhaea_helpers.hpp"

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/Elements/spectrum.hpp"
#include "gambit/Elements/smlike_higgs.hpp"

#include "gambit/SpecBit/SpecBit_rollcall.hpp"
#include "gambit/SpecBit/SpecBit_helpers.hpp"
#include "gambit/SpecBit/RegisteredSpectra.hpp"

// TODO: Breaks modularity?
#include "gambit/Printers/printermanager.hpp" // Needed by get_MSSM_spectrum_from_postprocessor to access reader object
#include "gambit/Printers/baseprinter.hpp" // Needed by get_MSSM_spectrum_from_postprocessor to use reader object

// Switch for debug mode
//#define SPECBIT_DEBUG

namespace Gambit
{

  namespace SpecBit
  {

    // {@ Spectrum module functions

    // MSSM spectrum from SPheno
    void get_MSSM_spectrum_SPheno (Spectrum& spectrum)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_SPheno;
      const SMInputs &sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // Get the spectrum from the Backend
      myPipe::BEreq::SPheno_MSSM_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);
      
      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    //helper function to add DMASS blocks to SLHA file I read in for test
    void add_DMASS_block(SLHAea::Coll & slha)
    {
       const double rel_uncertainty = 0.03;
    auto block = slha["MASS"];
    SLHAea_add_block(slha, "DMASS");
    for(auto it = block.begin(); it != block.end(); it++)
    {
      if((*it)[0] != "Block" )
      {
         // add lower relative uncertainty with second index 0
         slha["DMASS"][""] << (*it)[0] << "0" <<  rel_uncertainty
                          << "# "
                          << Models::ParticleDB().long_name(std::stoi((*it)[0]),0);
         // add upper realtive uncertainty with second index 1
         slha["DMASS"][""] << (*it)[0] << "1" <<  rel_uncertainty
                          << "# "
                          << Models::ParticleDB().long_name(std::stoi((*it)[0]),0);
      }
    }
    std::cout << "slha after adding DMASS: " << std::endl;
    std::cout << slha << std::endl;

    // For pole masses that come from SMINPUTS or are just know to be zero
    // (photon and gluon) we need to manually add DMASS entry.
    // TODO: decide if this is correct thing to do
    slha["DMASS"][""] << "21" << "0" <<  0.0 << "# gluon";
    slha["DMASS"][""] << "21" << "1" <<  0.0 << "# gluon";
    slha["DMASS"][""] << "22" << "0" <<  0.0 << "# photon";
    slha["DMASS"][""] << "22" << "1" <<  0.0 << "# photon";
    slha["DMASS"][""] << "23" << "0" <<  0.0 << "# MZ(pole)";
    slha["DMASS"][""] << "23" << "1" <<  0.0 << "# MZ(pole)";
    slha["DMASS"][""] << "11" << "0" <<  0.0 << "# e-";
    slha["DMASS"][""] << "11" << "1" <<  0.0 << "# e-";
    slha["DMASS"][""] << "13" << "0" <<  0.0 << "# mu-";
    slha["DMASS"][""] << "13" << "1" <<  0.0 << "# mu-";
    slha["DMASS"][""] << "15" << "0" <<  0.0 << "# tau";
    slha["DMASS"][""] << "15" << "1" <<  0.0 << "# tau";

    slha["DMASS"][""] << "12" << "0" <<  0.0 << "# nu_e";
    slha["DMASS"][""] << "12" << "1" <<  0.0 << "# nu_e";
    slha["DMASS"][""] << "14" << "0" <<  0.0 << "# nu_mu";
    slha["DMASS"][""] << "14" << "1" <<  0.0 << "# nu_mu";
    slha["DMASS"][""] << "16" << "0" <<  0.0 << "# nu_tau";
    slha["DMASS"][""] << "16" << "1" <<  0.0 << "# nu_tau";

    slha["DMASS"][""] << "6" << "0" <<  0.0 << "# top";
    slha["DMASS"][""] << "6" << "1" <<  0.0 << "# top";

    // Not in SMINPUTS as pole masses
    // slha["DMASS"][""] << "1" << "0" <<  0.0 << "# d";
    // slha["DMASS"][""] << "1" << "1" <<  0.0 << "# d";
    // slha["DMASS"][""] << "2" << "0" <<  0.0 << "# u";
    // slha["DMASS"][""] << "2" << "1" <<  0.0 << "# u";

    ///calling constructor from spectrum.hpp in Elements
    }
  // Runs FlexibleSUSY MSSM spectrum generator with CMSSM (GUT scale) boundary conditions
    // In principle an identical spectrum can be obtained from the function
    // get_MSSMatGUT_spectrum_FS
    // by setting the input parameters to match the CMSSM assumptions

    void get_CMSSM_spectrum_FS (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_CMSSM_spectrum_FS;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_CMSSM_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      // TODO: This is CMSSM only, no gravitino, right?
      //if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
      //    myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      //{   
      //  add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      //}

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
      // test against stored slha file from standalone version by
      // generating an SLHA of same GAMBIT form for easy diff
      bool test_spec = false; // replace with preprocessor debug statement
      if(test_spec) {
         double scale = spectrum.GetScale();
         // get slhaea object from test slha file
         std::ifstream in_file("SpecBit/Spectrum_Testing/LesHouches.out.CMSSM.test_2L_RGEs");
         SLHAea::Coll slha(in_file);
         add_DMASS_block(slha);
         Spectrum spectrum_test(slha, SpectrumContents::MSSM(), scale, false);
         //TODO need to be able to change the name of the slha file
         spectrum_test.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_test_unimproved_spectrum");
      }
    }

    // Runs FlexibleSUSY MSSM spectrum generator with GUT scale input (boundary conditions)
    void get_MSSMatMGUT_spectrum_FS (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatMGUT_spectrum_FS;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMatMGUT_input_parameters input;
      //input.mHu2IN = *myPipe::Param.at("mHu2");
      //input.mHd2IN = *myPipe::Param.at("mHd2");
      //input.SignMu = *myPipe::Param.at("SignMu");
      //if(input.SignMu!=-1 and input.SignMu!=1)
      //{
      //   std::ostringstream msg;
      //   msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
      //   SpecBit_error().raise(LOCAL_INFO,msg.str());
      //}
      //fill_MSSM63_input(input,myPipe::Param);

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatMGUT_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {   
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    // Runs FlexibleSUSY MSSM spectrum generator with GUT scale input (boundary conditions)
    // but with mA and mu as parameters instead of mHu2 and mHd2
    void get_MSSMatMGUT_mA_spectrum_FS (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatMGUT_mA_spectrum_FS;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMatMGUT_mAmu_input_parameters input;
      //input.MuInput  = *myPipe::Param.at("mu");
      // Note this spectrum generator mA2 is the parameter.
      // However this freedom is not used in GAMBIT
      // and not needed as mA is a DRbar mass eigenstate for a scalar
      //double mA = *myPipe::Param.at("mA");
      //input.mA2Input = mA*mA;
      //fill_MSSM63_input(input,myPipe::Param); // Fill the rest

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatMGUT_mA_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {   
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
 
    // Runs FlexibleSUSY MSSM spectrum generator with EWSB scale input (boundary conditions)
    void get_MSSMatQ_spectrum_FS (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatQ_spectrum_FS;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSM_input_parameters input;
      //input.Qin    = *myPipe::Param.at("Qin"); // MSSMatQ also requires input scale to be supplied
      //input.mHu2IN = *myPipe::Param.at("mHu2");
      //input.mHd2IN = *myPipe::Param.at("mHd2");
      //input.SignMu = *myPipe::Param.at("SignMu");
      //if(input.SignMu!=-1 and input.SignMu!=1)
      //{
      //   std::ostringstream msg;
      //   msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
      //   SpecBit_error().raise(LOCAL_INFO,msg.str());
      //}
      //fill_MSSM63_input(input,myPipe::Param);

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatQ_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {   
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    // Runs FlexibleSUSY MSSM spectrum generator with EWSB scale input (boundary conditions)
    // but with mA and mu as parameters instead of mHu2 and mHd2
    void get_MSSMatQ_mA_spectrum_FS (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatQ_mA_spectrum_FS;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSM_mAmu_input_parameters input;
      //input.Qin      = *myPipe::Param.at("Qin"); // MSSMatQ also requires input scale to be supplied
      //input.MuInput  = *myPipe::Param.at("mu");
      // Note this spectrum generator mA2 is the parameter.
      // However this freedom is not used in GAMBIT
      // and not needed as mA is a DRbar mass eigenstate for a scalar
      //double mA = *myPipe::Param.at("mA");
      //input.mA2Input = mA*mA;
      //fill_MSSM63_input(input,myPipe::Param); // Fill the rest

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatQ_mA_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {   
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    // Runs FlexibleSUSY MSSM spectrum generator with SUSY scale input (boundary conditions)
    // but with mA and mu as parameters instead of mHu2 and mHd2
    void get_MSSMatMSUSY_mA_spectrum_FS (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatMSUSY_mA_spectrum_FS;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMatMSUSY_mAmu_input_parameters input;
      //input.MuInput  = *myPipe::Param.at("mu");
      // Note this spectrum generator mA2 is the parameter.
      // However this freedom is not used in GAMBIT
      // and not needed as mA is a DRbar mass eigenstate for a scalar
      //double mA = *myPipe::Param.at("mA");
      //input.mA2Input = mA*mA;    // FS has mA^2 as the parameter
      //fill_MSSM63_input(input,myPipe::Param); // Fill the rest

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatMSUSY_mA_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {   
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    // Runs FlexibleSUSY MSSMatMGUTEFTHiggs model spectrum generator
    // and has m3^2 and mu as EWSB outputs, so it is for the
    // MSSMatMGUT_model.
    void get_MSSMatMGUT_spectrum_FlexibleEFTHiggs (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatMGUT_spectrum_FlexibleEFTHiggs;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMatMGUTEFTHiggs_input_parameters input;
      //input.mHu2IN = *myPipe::Param.at("mHu2");
      //input.mHd2IN = *myPipe::Param.at("mHd2");
      //input.SignMu = *myPipe::Param.at("SignMu");
      //if(input.SignMu!=-1 and input.SignMu!=1)
      //{
      //   std::ostringstream msg;
      //   msg << "Tried to set SignMu parameter to a value that is not a sign! ("<<input.SignMu<<")! This parameter must be set to either 1 or -1. Please check your inifile and try again.";
      //   SpecBit_error().raise(LOCAL_INFO,msg.str());
      //}

      //fill_MSSM63_input(input,myPipe::Param); // Fill the rest

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatMGUTEFTHiggs_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {   
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    // Runs FlexibleSUSY MSSMatMGUTEFTHiggs model spectrum generator
    // and has m3^2 and mu as EWSB outputs, so it is for the
    // MSSMatMGUT_model.
    void get_MSSMatMGUT_mA_spectrum_FlexibleEFTHiggs (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatMGUT_mA_spectrum_FlexibleEFTHiggs;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMatMGUTEFTHiggs_mAmu_input_parameters input;
      //input.MuInput  = *myPipe::Param.at("mu");
      // Note this spectrum generator mA2 is the parameter.
      // However this freedom is not used in GAMBIT
      // and not needed as mA is a DRbar mass eigenstate for a scalar
      //double mA = *myPipe::Param.at("mA");
      //input.mA2Input = mA*mA;

      //fill_MSSM63_input(input,myPipe::Param); // Fill the rest

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatMGUTEFTHiggs_mA_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or 
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {   
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    // Runs FlexibleSUSY MSSMEFTHiggs model spectrum generator
    // and has m3^2 and mu as EWSB outputs, so it is for the
    // MSSMatQ_model.
    void get_MSSMatQ_spectrum_FlexibleEFTHiggs (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatQ_spectrum_FlexibleEFTHiggs;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMEFTHiggs_input_parameters input;
      // MSSMatQ also requires input scale to be supplied with name MSUSY
      //input.MSUSY  = *myPipe::Param.at("Qin");
      //input.mHu2IN = *myPipe::Param.at("mHu2");
      //input.mHd2IN = *myPipe::Param.at("mHd2");
      //input.SignMu = *myPipe::Param.at("SignMu");
      //fill_MSSM63_input_altnames(input,myPipe::Param); // Fill the rest

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatQEFTHiggs_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    // Runs FlexibleSUSY MSSMEFTHiggs_mAmu spectrum generator with
    // boundary conditions at a user specified scale, ie accepts MSSM
    // parameters at Q, and has DRbar mA and mu as an input and mHu2
    // and mHd2 as EWSB outputs, so it is for the MSSMatMSUSY_mA model.
    void get_MSSMatQ_mA_spectrum_FlexibleEFTHiggs (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatQ_mA_spectrum_FlexibleEFTHiggs;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMEFTHiggs_mAmu_input_parameters input;
      //input.MuInput  = *myPipe::Param.at("mu");
      // This FS spectrum generator has mA as the parameter
      //input.mAInput = *myPipe::Param.at("mA");
      // Note: Qin has been named MSUSY inside the spectrum generator
      // but it is a user-input scale in this case.
      //input.MSUSY = *myPipe::Param.at("Qin");
      // Fill the rest.
      // Note: This particular spectrum generator has been created with
      // different names for parameter inputs.  We should standardise this
      //fill_MSSM63_input_altnames(input,myPipe::Param);

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatQEFTHiggs_mA_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }
 
    // Runs FlexibleSUSY MSSMEFTHiggs model spectrum generator with SUSY
    // scale boundary conditions, ie accepts MSSM parameters at MSUSY,
    // and has DRbar mA and mu as an input and mHu2 and mHd2 as EWSB
    // outputs, so it is for the MSSMatMSUSY_mA model.
    void get_MSSMatMSUSY_mA_spectrum_FlexibleEFTHiggs (Spectrum& spectrum)
    {
      // Access the pipes for this function to get model and parameter information
      namespace myPipe = Pipes::get_MSSMatMSUSY_mA_spectrum_FlexibleEFTHiggs;

      // Get SLHA2 SMINPUTS values
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS;

      // Set up the input structure
      SpectrumInputs inputs(sminputs, SpectrumContents::MSSM(), myPipe::Param, myPipe::runOptions);

      // TODO: This all goes to the backend source file
      //MSSMatMSUSYEFTHiggs_mAmu_input_parameters input;
      //input.MuInput  = *myPipe::Param.at("mu");
      // This FS spectrum generator has mA as the parameter
      //input.mAInput = *myPipe::Param.at("mA");
      //fill_MSSM63_input_altnames(input,myPipe::Param); // Fill the rest

      // Get the spectrum from the Backend
      myPipe::BEreq::FS_MSSMatMSUSYEFTHiggs_mA_Spectrum(spectrum, inputs);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add gravitino to the spectrum and LSP list
      if (myPipe::ModelInUse("MSSM63atQ_lightgravitino") or
          myPipe::ModelInUse("MSSM63atMGUT_lightgravitino"))
      {
        add_gravitino_mass(spectrum, LSPs, *myPipe::Param.at("mG"), myPipe::runOptions);
      }

      // Check that the LSP is the canonical LSP
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      // Drop SLHA files if requested
      spectrum.drop_SLHAs_if_requested(myPipe::runOptions, "GAMBIT_unimproved_spectrum");
    }

    /// Get an MSSM Spectrum object from an SLHA file
    /// This is mainly for testing against benchmark points, but may be a useful last
    /// resort for interacting with "difficult" spectrum generators.
    void get_MSSM_spectrum_from_SLHAfile(Spectrum &spectrum)
    {
      // Static counter running in a loop over all filenames
      static unsigned int counter = 0;
      static long int ncycle = 1;
      SLHAstruct input_slha;

      namespace myPipe = Pipes::get_MSSM_spectrum_from_SLHAfile;

      // Read filename from yaml file
      std::vector<std::string> filenames =
        myPipe::runOptions->getValue<std::vector<std::string>>("filenames");

      // Check how many loop over the input files we are doing.
      long int cycles = myPipe::runOptions->getValueOrDef<int>(-1,"cycles");

      // Check if we have completed the requested number of cycles
      if(cycles>0 and ncycle>cycles)
      {
         std::ostringstream msg;
         msg << "Preset number of loops through input files reached! Stopping. (tried to start cycle "<<ncycle<<" of "<<cycles<<")";
         SpecBit_error().raise(LOCAL_INFO,msg.str());
      }

      std::string filename = filenames[counter];

      logger() << "Reading SLHA file: " << filename << EOM;
      std::ifstream ifs(filename.c_str());
      if(!ifs.good()){ SpecBit_error().raise(LOCAL_INFO,"ERROR: SLHA file not found."); }
      ifs >> input_slha;
      ifs.close();
      counter++;
      if( counter >= filenames.size() )
      {
        logger() << "Returning to start of input SLHA file list (finished "<<ncycle<<" cycles)" << EOM;
        counter = 0;
        ncycle++;
      }

      // SpectrumContents struct
      SpectrumContents::MSSM mssm;

      // Create spectrum object
      // Get the scale from the MSOFT block
      spectrum = Spectrum(input_slha, mssm, SLHAea_get_scale(input_slha, "MSOFT"), false);

      // Add getter for susy scale if option set for this
      // TODO: This is obsolote, there is no susy_scale parameter anymore
      //bool add_susy_scale = myPipe::runOptions->getValueOrDef<bool>(false,"assume_Q_is_MSUSY");
      //if(add_susy_scale)
      //{
      //   spectrum.set_override(Par::mass1,spectrum.GetScale(),"susy_scale",true);
      //}

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add the gravitino mass to a spectrum object if it has been provided in an SLHAea object
      if(SLHAea_entry_exists(input_slha, "MASS", 1000039))
      {
        add_gravitino_mass(spectrum,LSPs,SLHAea_get(input_slha,"MASS",1000039),myPipe::runOptions);
      }

      // No sneaking in charged LSPs via SLHA, jävlar.
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);
    }

    /// Get an MSSMSpectrum object from an SLHAstruct
    /// This is kind of automatic with the new Spectrum class
    void get_MSSM_spectrum_from_SLHAstruct(Spectrum& spectrum)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_from_SLHAstruct;
      const SLHAstruct& input_slha = *myPipe::Dep::unimproved_MSSM_spectrum; // Retrieve dependency on SLHAstruct

      // SpectrumContents struct
      SpectrumContents::MSSM mssm;

      // Create spectrum object
      // Get the scale from the MSOFT block
      spectrum = Spectrum(input_slha, mssm, SLHAea_get_scale(input_slha, "MSOFT"), false);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // Add the gravitino mass to a spectrum object if it has been provided in an SLHAea object
      if(SLHAea_entry_exists(input_slha, "MASS", 1000039))
      {
        add_gravitino_mass(spectrum,LSPs,SLHAea_get(input_slha,"MASS",1000039),myPipe::runOptions);
      }

      // No sneaking in charged LSPs via SLHA, jävlar.
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

      /* TODO: The scale is set when creating the spectrum, but check if needs to be removed
      // In order to translate from e.g. MSSM63atMGUT to MSSM63atQ, we need
      // to know the input scale Q. This is generally not stored in SLHA format,
      // but we need it, so if you want to produce a Spectrum object this way you
      // will need to add this information to your SLHAstruct:
      // BLOCK GAMBIT
      //   1     <high_scale>    # Input scale of (upper) boundary conditions, e.g. GUT scale
      // For example, you could add this to your input SLHAstruct in C++ as follows:
      //input_slha["GAMBIT"][""] << "BLOCK" << "GAMBIT";
      //input_slha["GAMBIT"][""] <<      1  << 1e99 << "# Input scale";

      // Need to check if this information exists:
      SLHAstruct::const_iterator block = input_slha.find("GAMBIT");
      std::vector<std::string> key(1, "1");
      if(block == input_slha.end() or block->find(key) == block->end())
      {
       // Big problem
        std::ostringstream errmsg;
        errmsg << "Error constructing Spectrum object from a pre-existing SLHAstruct!    " << endl
               << "The supplied SLHAstruct did not have the special GAMBIT block added.  " << endl
               << "This block carries extra information from the spectrum generator      " << endl
               << "that is usually thrown away, but which is needed for properly creating" << endl
               << "a Spectrum object. In whatever module function created the SLHAstruct " << endl
               << "that you want to use, please add code that adds the following         " << endl
               << "information to the SLHAstruct (SLHAea::Coll):                         " << endl
               << "  BLOCK GAMBIT                                                        " << endl
               << " 1 <high_scale>  # Input scale of (upper) boundary conditions, e.g. GUT scale\n";
        SpecBit_error().raise(LOCAL_INFO,errmsg.str());
      }

      // OK the GAMBIT block exists, add the data to the MSSM SubSpectrum object.
      spectrum.set_override(Par::mass1,SLHAea::to<double>(input_slha.at("GAMBIT").at(1).at(1)), "high_scale", false);
    */
    }

    /// Extract an SLHAea version of the spectrum contained in a Spectrum object, in SLHA1 format
    void get_MSSM_spectrum_as_SLHAea_SLHA1(SLHAstruct &spectrum)
    {
      spectrum = Pipes::get_MSSM_spectrum_as_SLHAea_SLHA1::Dep::unimproved_MSSM_spectrum->getSLHAea(1);
    }

    /// Extract an SLHAea version of the spectrum contained in a Spectrum object, in SLHA2 format
    void get_MSSM_spectrum_as_SLHAea_SLHA2(SLHAstruct &spectrum)
    {
      spectrum = Pipes::get_MSSM_spectrum_as_SLHAea_SLHA2::Dep::unimproved_MSSM_spectrum->getSLHAea(2);
    }

    /// Get pre-computed MSSM spectrum from previous output file
    /// This function ONLY works when the scan is driven by the postprocessor!
    /// This is because it relies on the global reader object created by the
    /// postprocessor to retrieve output.
    void get_MSSM_spectrum_from_postprocessor(Spectrum& result)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_from_postprocessor;
      const SMInputs& sminputs = *myPipe::Dep::SMINPUTS; // Retrieve dependency on SLHAstruct

      // Retrieve the spectrum from whatever the point the global reader object is pointed at.
      // This should be the same point that the postprocessor has retrieved the
      // current set of ModelParameters from.
      // Will throw an error if no reader object exists, i.e. if the postprocessor is not
      // driving this scan.
      
      // Retrieve MSSM spectrum info into an SLHAea object 
      MSSM_SLHAstruct mssm_in; // Special type to trigger specialised MSSM retrieve routine
      bool mssm_is_valid = get_pp_reader().retrieve(mssm_in,"MSSM_spectrum");

      // Check if a valid spectrum was retrived
      // (if the required datasets don't exist an error will be thrown,
      //  so this is just checking that the spectrum was computed for
      //  the current input point)
      if(not (mssm_is_valid)) invalid_point().raise("Postprocessor: precomputed spectrum was set 'invalid' for this point");
       
      // Dump spectrum to output for testing
      SLHAstruct mssm = mssm_in; // Only this type has stream overloads etc. defined

      // Turns out we don't generically save tan_beta(mZ)_DRbar, so need to extract
      // this from model parameters (it is always an input, so we should have it in those)
      double tbmZ = *myPipe::Param.at("TanBeta");
      SLHAea_add(mssm, "MINPAR", 3, tbmZ, "tan beta (mZ)_DRbar");        

      // Create full Spectrum object
      result = Spectrum(mssm,sminputs,NULL,mass_cut,mass_ratio_cut);

      // SpectrumContents struct
      SpectrumContents::MSSM mssm_contents;

      // Create spectrum object
      // Get the scale from the MSOFT block
      spectrum = Spectrum(mssm, mssm_contents, SLHAea_get_scale(mssm, "MSOFT"), false);

      // Neutralino is canonical LSP
      std::vector<int> LSPs = {1000022};

      // No sneaking in charged LSPs via SLHA, jävlar.
      check_LSP(spectrum, LSPs);

      // Retrieve any mass cuts
      spectrum.check_mass_cuts(*myPipe::runOptions);

    }

    // Convert an unimproved_MSSM_spectrum into a standard map so that it can be printed
    void get_unimproved_MSSM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_unimproved_MSSM_spectrum_as_map;
      const Spectrum& mssmspec(*myPipe::Dep::unimproved_MSSM_spectrum);
      fill_map_from_spectrum<SpectrumContents::MSSM>(specmap, mssmspec);
      add_extra_MSSM_parameter_combinations(specmap, mssmspec);
    }
 
    // Convert an MSSM_spectrum into a standard map so that it can be printed
    void get_MSSM_spectrum_as_map (std::map<std::string,double>& specmap)
    {
      namespace myPipe = Pipes::get_MSSM_spectrum_as_map;
      const Spectrum& mssmspec(*myPipe::Dep::MSSM_spectrum);
      fill_map_from_spectrum<SpectrumContents::MSSM>(specmap, mssmspec);
      add_extra_MSSM_parameter_combinations(specmap, mssmspec);
    }

    // @}

    // {@ Improved Higgs mass module functions

    /// FeynHiggs SUSY masses and mixings
    void FH_MSSMMasses(fh_MSSMMassObs &result)
    {
      using namespace Pipes::FH_MSSMMasses;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FH_MSSMMasses ******" << endl;
      #endif

      // zero if minimal, non-zero if non-minimal flavour violation
      int nmfv;

      // MSf(s,t,g) MFV squark masses with indices
      // s = 1..2   sfermion index
      // t = 1..5   sfermion type nu,e,u,d,?
      // g = 1..3   generation index
      Farray<fh_real, 1,2, 1,5, 1,3> MSf;

      // USf(s1,s2,t,g) MFV squark mixing matrices with indices
      // s1 = 1..2  sfermion index (mass eigenstates)
      // s2 = 1..2  sfermion index (gauge eigenstates, L/R)
      // t  = 1..5  sfermion type nu,e,u,d,?
      // g  = 1..3  generation index
      Farray<fh_complex, 1,2, 1,2, 1,5, 1,3> USf;

      // NMFV squark masses, with indices
      // a = 1..6   extended sfermion index
      // t = 1..5   sfermion type
      Farray<fh_real, 1,6, 1,5> MASf;

      // NMFV squark mixing matrices, with indices
      // a1 = 1..6  extended sfermion index (mass eigenstates)
      // a2 = 1..6  extended sfermion index (gauge eigenstates)
      //  t = 1..5  sftermion type nu,e,u,d,?
      Farray<fh_complex, 1,36, 1,5> UASf;

      // chargino masses
      Farray<fh_real, 1,2> MCha;

      // chargino mixing matrices (mass,gauge) eigenstates (2 x 2)
      Farray<fh_complex, 1,4> UCha;
      Farray<fh_complex, 1,4> VCha;

      // neutralino masses
      Farray<fh_real, 1,4> MNeu;

      // neutralino mixing matrices (mass,gauge) eigenstates (4 x 4)
      Farray<fh_complex, 1,16> ZNeu;

      // correction to bottom Yukawa coupling
      fh_complex DeltaMB;

      // gluino mass
      fh_real MGl;

      // tree-level Higgs masses (Mh, MH, MA, MHpm)
      Farray<fh_real, 1,4> MHtree;

      // tree-level Higgs mixing parameters sin alpha
      fh_real SAtree;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHGetPara ******" << endl;
      #endif

      int error = 1;
      BEreq::FHGetPara(error, nmfv, MSf, USf, MASf, UASf,
           MCha, UCha, VCha, MNeu, ZNeu,
           DeltaMB, MGl, MHtree, SAtree);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHGetPara raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      fh_MSSMMassObs MassObs;
      for(int i = 0; i < 2; i++)
        for(int j = 0; j < 5; j++)
          for(int k = 0; k < 3; k++)
            MassObs.MSf[i][j][k] = MSf(i+1,j+1,k+1);
      for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
          for(int k = 0; k < 5; k++)
            for(int l = 0; l < 3; l++)
              MassObs.USf[i][j][k][l] = USf(i+1,j+1,k+1,l+1);
      for(int i = 0; i < 6; i++)
        for(int j = 0; j < 5; j++)
          MassObs.MASf[i][j] = MASf(i+1,j+1);
      for(int i = 0; i < 36; i++)
        for(int j = 0; j < 5; j++)
          MassObs.UASf[i][j] = UASf(i+1,j+1);
      for(int i = 0; i < 2; i++)
        MassObs.MCha[i] = MCha(i+1);
      for(int i = 0; i < 4; i++)
      {
        MassObs.UCha[i] = UCha(i+1);
        MassObs.VCha[i] = VCha(i+1);
      }
      for(int i = 0; i < 4; i++)
        MassObs.MNeu[i] = MNeu(i+1);
      for(int i = 0; i < 16; i++)
        MassObs.ZNeu[i] = ZNeu(i+1);
      MassObs.deltaMB = DeltaMB;
      MassObs.MGl = MGl;
      for(int i = 0; i < 4; i++)
        MassObs.MHtree[i] = MHtree(i+1);
      MassObs.SinAlphatree = SAtree;

      result = MassObs;
    }

    /// Higgs masses and mixings with theoretical uncertainties
    void FH_AllHiggsMasses(fh_HiggsMassObs &result)
    {
      using namespace Pipes::FH_AllHiggsMasses;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FH_HiggsMasses ******" << endl;
      #endif

      // Higgs mass with
      // 0 - m1 (Mh in rMSSM)
      // 1 - m2 (MH in rMSSM)
      // 2 - m3 (MA in rMSSM)
      // 3 - MHpm
      Farray<fh_real, 1,4> MHiggs;
      Farray<fh_real, 1,4> DeltaMHiggs;

      // sine of effective Higgs mixing angle, alpha_eff
      fh_complex SAeff;
      fh_complex DeltaSAeff;

      // matrix needed to rotate Higgs
      // mass matrix to diagonal form
      Farray<fh_complex, 1,3, 1,3> UHiggs;
      Farray<fh_complex, 1,3, 1,3> DeltaUHiggs;

      // matrix of Z-factors needed to combine
      // amplitudes involving on-shell Higgs
      Farray<fh_complex, 1,3, 1,3> ZHiggs;
      Farray<fh_complex, 1,3, 1,3> DeltaZHiggs;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHHiggsCorr ******" << endl;
      #endif

      int error = 1;
      BEreq::FHHiggsCorr(error, MHiggs, SAeff, UHiggs, ZHiggs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHHiggsCorr raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHUncertainties ******" << endl;
      #endif

      error = 1;
      BEreq::FHUncertainties(error, DeltaMHiggs, DeltaSAeff, DeltaUHiggs, DeltaZHiggs);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHUncertainties raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      fh_HiggsMassObs HiggsMassObs;
      for(int i = 0; i < 4; i++)
      {
        HiggsMassObs.MH[i] = MHiggs(i+1);
        HiggsMassObs.deltaMH[i] = DeltaMHiggs(i+1);
      }
      HiggsMassObs.SinAlphaEff = SAeff;
      HiggsMassObs.deltaSinAlphaEff = DeltaSAeff;
      for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
          HiggsMassObs.UH[i][j] = UHiggs(i+1,j+1);
          HiggsMassObs.deltaUH[i][j] = DeltaUHiggs(i+1,j+1);
          HiggsMassObs.ZH[i][j] = ZHiggs(i+1,j+1);
          HiggsMassObs.deltaZH[i][j] = DeltaZHiggs(i+1,j+1);
        }

      result = HiggsMassObs;
    }

    // SM-like Higgs mass with theoretical uncertainties
    void FH_HiggsMass(triplet<double>& result)
    {
      using namespace Pipes::FH_HiggsMass;
      //FH indices: 0=h0_1, 1=h0_2
      int i = 0;
      const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
      int higgs = SMlike_higgs_PDG_code(spec);
      if (higgs == 25) i = 0;
      else if (higgs == 35) i = 1;
      else SpecBit_error().raise(LOCAL_INFO, "Urecognised SM-like Higgs PDG code!");
      result.central = Dep::FH_HiggsMasses->MH[i];
      result.upper = Dep::FH_HiggsMasses->deltaMH[i];
      result.lower = Dep::FH_HiggsMasses->deltaMH[i];
    }

    // Non-SM-like, charged and CP-odd Higgs masses with theoretical uncertainties
    void FH_HeavyHiggsMasses(map_int_triplet_dbl& result)
    {
      using namespace Pipes::FH_HeavyHiggsMasses;
      const int neutrals[2] = {25, 35};
      int i = -1;
      const Spectrum& spec = *Dep::unimproved_MSSM_spectrum;
      int higgs = SMlike_higgs_PDG_code(spec);
      if (higgs == neutrals[0]) i = 1;
      else if (higgs == neutrals[1]) i = 0;
      else SpecBit_error().raise(LOCAL_INFO, "Urecognised SM-like Higgs PDG code!");
      result.clear();
      result[neutrals[i]].central = Dep::FH_HiggsMasses->MH[i];
      result[neutrals[i]].upper = Dep::FH_HiggsMasses->deltaMH[i];
      result[neutrals[i]].lower = Dep::FH_HiggsMasses->deltaMH[i];
      result[36].central = Dep::FH_HiggsMasses->MH[2];
      result[36].upper = Dep::FH_HiggsMasses->deltaMH[2];
      result[36].lower = Dep::FH_HiggsMasses->deltaMH[2];
      result[37].central = Dep::FH_HiggsMasses->MH[3];
      result[37].upper = Dep::FH_HiggsMasses->deltaMH[3];
      result[37].lower = Dep::FH_HiggsMasses->deltaMH[3];
    }

    // SM-like Higgs mass with theoretical uncertainties
    void SHD_HiggsMass(triplet<double>& result)
    {
      using namespace Pipes::SHD_HiggsMass;

      const Spectrum& spectrum = *Dep::unimproved_MSSM_spectrum;
      SLHAea::Coll slhaea = spectrum.getSLHAea(1);

      #ifdef SPECBIT_DEBUG
        cout << "****** calling SHD_HiggsMass ******" << endl;
      #endif

      MList<MReal> parameterList = {
        SLHAea::to<double>(slhaea.at("HMIX").at(2).at(1)), // tanbeta
        SLHAea::to<double>(slhaea.at("MSOFT").at(1).at(1)), // M1
        SLHAea::to<double>(slhaea.at("MSOFT").at(2).at(1)), // M2
        SLHAea::to<double>(slhaea.at("MSOFT").at(3).at(1)), // M3
        SLHAea::to<double>(slhaea.at("HMIX").at(1).at(1)), // mu
        SLHAea::to<double>(slhaea.at("AU").at(3).at(2)), // At
        SLHAea::to<double>(slhaea.at("MSOFT").at(43).at(1)), // mQ3
        SLHAea::to<double>(slhaea.at("MSOFT").at(46).at(1)), // mU3
        SLHAea::to<double>(slhaea.at("MSOFT").at(49).at(1)), // mD3
        SLHAea::to<double>(slhaea.at("MSOFT").at(42).at(1)), // mQ2
        SLHAea::to<double>(slhaea.at("MSOFT").at(45).at(1)), // mU2
        SLHAea::to<double>(slhaea.at("MSOFT").at(48).at(1)), // mD2
        SLHAea::to<double>(slhaea.at("MSOFT").at(41).at(1)), // mQ1
        SLHAea::to<double>(slhaea.at("MSOFT").at(44).at(1)), // mU1
        SLHAea::to<double>(slhaea.at("MSOFT").at(47).at(1)), // mD1
        SLHAea::to<double>(slhaea.at("MSOFT").at(33).at(1)), // mL3
        SLHAea::to<double>(slhaea.at("MSOFT").at(36).at(1)), // mE3
        SLHAea::to<double>(slhaea.at("MSOFT").at(32).at(1)), // mL2
        SLHAea::to<double>(slhaea.at("MSOFT").at(35).at(1)), // mE2
        SLHAea::to<double>(slhaea.at("MSOFT").at(31).at(1)), // mL1
        SLHAea::to<double>(slhaea.at("MSOFT").at(34).at(1)), // mE1
        sqrt(SLHAea::to<double>(slhaea.at("HMIX").at(4).at(1))) // mA
      };

      MReal MHiggs = BEreq::SUSYHD_MHiggs(parameterList);

      #ifdef SPECBIT_DEBUG
        cout << "****** calling SHD_DeltaHiggsMass ******" << endl;
      #endif

      MReal DeltaMHiggs = BEreq::SUSYHD_DeltaMHiggs(parameterList);

      result.central = MHiggs;

      bool use_SHD_uncertainty = runOptions->getValueOrDef<bool>(true, "use_SHD_uncertainty");

      if(use_SHD_uncertainty)
      {
        result.upper = DeltaMHiggs;
        result.lower = DeltaMHiggs;
      }
      else
      {
        result.upper = 0.0;
        result.lower = 0.0;
      }

    }

    // @}

    // {@ Higgs couplings module functions

    /// Call FH_Couplings from FeynHiggs and collect the output
    void FH_Couplings(fh_Couplings &result)
    {
      using namespace Pipes::FH_Couplings;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FH_Couplings ******" << endl;
      #endif

      // what to use for internal Higgs mixing
      // (ex. in couplings)
      // (default = 1)
      // 0 - no mixing
      // 1 - UHiggs
      // 2 - ZHiggs
      int uzint = 2;
      // what to use for external Higgs mixing
      // (ex. in decays)
      // (default = 2)
      // 0 - no mixing
      // 1 - UHiggs
      // 2 - ZHiggs
      int uzext = 2;
      // which effective bottom mass to use
      int mfeff = 1;

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHSelectUZ ******" << endl;
      #endif

      int error = 1;
      BEreq::FHSelectUZ(error, uzint, uzext, mfeff);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHSelectUZ raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      Farray<fh_complex, 1,ncouplings> couplings;        // MSSM Higgs couplings
      Farray<fh_complex, 1,ncouplingsms> couplings_sm;  // SM Higgs couplings
      Farray<fh_real, 1,ngammas> gammas;                // Higgs decay widths and BR's (MSSM)
      Farray<fh_real, 1,ngammasms> gammas_sm;           // Higgs decay widths and BR's (SM)
      int fast = 1;  // include off-diagonal fermion decays? (1 = no)

      #ifdef SPECBIT_DEBUG
        cout << "****** calling FHCouplings ******" << endl;
      #endif

      error = 1;
      BEreq::FHCouplings(error, couplings, couplings_sm,
                         gammas, gammas_sm, fast);
      if (error != 0)
      {
        std::ostringstream err;
        err << "BEreq::FHCouplings raised error flag: " << error << ".";
        invalid_point().raise(err.str());
      }

      fh_Couplings Couplings;
      for(int i = 0; i < ncouplings; i++) Couplings.couplings[i] = couplings(i+1);
      for(int i = 0; i < ncouplingsms; i++) Couplings.couplings_sm[i] = couplings_sm(i+1);
      for(int i = 0; i < ngammas; i++) Couplings.gammas[i] = gammas(i+1);
      for(int i = 0; i < ngammasms; i++) Couplings.gammas_sm[i] = gammas_sm(i+1);
      Couplings.calculator = BEreq::FHCouplings.origin();
      Couplings.calculator_version = BEreq::FHCouplings.version();

      result = Couplings;
    }

    /// Put together the Higgs couplings for the MSSM, from partial widths only
    void MSSM_higgs_couplings_pwid(HiggsCouplingsTable &result)
    {
      using namespace Pipes::MSSM_higgs_couplings_pwid;

      // Retrieve spectrum contents
      const Spectrum& spec = *Dep::MSSM_spectrum;

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");
      result.set_n_neutral_higgs(3);

      // Set up charged Higgses
      result.set_n_charged_higgs(1);

      // Set the CP of the Higgs states.  Note that this would need to be more sophisticated to deal with the complex MSSM!
      result.CP[0] = 1;  //h0_1
      result.CP[1] = 1;  //h0_2
      result.CP[2] = -1; //A0

      // Work out which SM values correspond to which SUSY Higgs
      int higgs = (SMlike_higgs_PDG_code(spec) == 25 ? 0 : 1);
      int other_higgs = (higgs == 0 ? 1 : 0);

      // Set the decays
      result.set_neutral_decays_SM(higgs, sHneut[higgs], *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(2, sHneut[2], *Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays(0, sHneut[0],  *Dep::Higgs_decay_rates);
      result.set_neutral_decays(1, sHneut[1], *Dep::h0_2_decay_rates);
      result.set_neutral_decays(2, sHneut[2], *Dep::A0_decay_rates);
      result.set_charged_decays(0, "H+", *Dep::H_plus_decay_rates);
      result.set_t_decays(*Dep::t_decay_rates);

      // Use them to compute effective couplings for all neutral higgses, except for hhZ.
      for (int i = 0; i < 3; i++)
      {
        result.C_WW2[i] = result.compute_effective_coupling(i, std::pair<int,int>(24, 0), std::pair<int,int>(-24, 0));
        result.C_ZZ2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(23, 0));
        result.C_tt2[i] = result.compute_effective_coupling(i, std::pair<int,int>(6, 1), std::pair<int,int>(-6, 1));
        result.C_bb2[i] = result.compute_effective_coupling(i, std::pair<int,int>(5, 1), std::pair<int,int>(-5, 1));
        result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int,int>(4, 1), std::pair<int,int>(-4, 1));
        result.C_tautau2[i] = result.compute_effective_coupling(i, std::pair<int,int>(15, 1), std::pair<int,int>(-15, 1));
        result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(22, 0), std::pair<int,int>(22, 0));
        result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int,int>(21, 0), std::pair<int,int>(21, 0));
        result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int,int>(13, 1), std::pair<int,int>(-13, 1));
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(21, 0));
        result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int,int>(3, 1), std::pair<int,int>(-3, 1));
      }

      // Calculate hhZ effective couplings.  Here we scale out the kinematic prefactor
      // of the decay width, assuming we are well above threshold if the channel is open.
      // If not, we simply assume SM couplings.
      const double mZ = spec.get(Par::Pole_Mass,23,0);
      const double scaling = 8.*sqrt(2.)*pi/Dep::MSSM_spectrum->get_SMInputs().GF;
      for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
      {
        double mhi = spec.get(Par::Pole_Mass, sHneut[i]);
        double mhj = spec.get(Par::Pole_Mass, sHneut[j]);
        if (mhi > mhj + mZ and result.get_neutral_decays(i).has_channel(sHneut[j], "Z0"))
        {
          double gamma = result.get_neutral_decays(i).width_in_GeV*result.get_neutral_decays(i).BF(sHneut[j], "Z0");
          double k[2] = {(mhj + mZ)/mhi, (mhj - mZ)/mhi};
          for (int l = 0; l < 2; l++) k[l] = (1.0 - k[l]) * (1.0 + k[l]);
          double K = mhi*sqrt(k[0]*k[1]);
          result.C_hiZ2[i][j] = scaling / (K*K*K) * gamma;
        }
        else // If the channel is missing from the decays or kinematically disallowed, just return the SM result.
        {
          result.C_hiZ2[i][j] = 1.;
        }
      }

      // Work out which invisible decays are possible
      result.invisibles = get_invisibles(spec);
    }

    /// Put together the Higgs couplings for the MSSM, using FeynHiggs
    void MSSM_higgs_couplings_FH(HiggsCouplingsTable &result)
    {
      using namespace Pipes::MSSM_higgs_couplings_FH;

      // Retrieve spectrum contents
      const Spectrum& spec = *Dep::MSSM_spectrum;
      const SMInputs& sminputs = Dep::MSSM_spectrum->get_SMInputs();

      // Set up neutral Higgses
      static const std::vector<str> sHneut = initVector<str>("h0_1", "h0_2", "A0");

      // Work out which SM values correspond to which SUSY Higgs
      int higgs = (SMlike_higgs_PDG_code(spec) == 25 ? 0 : 1);
      int other_higgs = (higgs == 0 ? 1 : 0);

      // Set the decays
      result.set_neutral_decays_SM(higgs, sHneut[higgs], *Dep::Reference_SM_Higgs_decay_rates);
      result.set_neutral_decays_SM(other_higgs, sHneut[other_higgs], *Dep::Reference_SM_other_Higgs_decay_rates);
      result.set_neutral_decays_SM(2, sHneut[2], *Dep::Reference_SM_A0_decay_rates);
      result.set_neutral_decays(0, sHneut[0], *Dep::Higgs_decay_rates);
      result.set_neutral_decays(1, sHneut[1], *Dep::h0_2_decay_rates);
      result.set_neutral_decays(2, sHneut[2], *Dep::A0_decay_rates);
      result.set_charged_decays(0, "H+", *Dep::H_plus_decay_rates);
      result.set_t_decays(*Dep::t_decay_rates);

      // Use the branching fractions to compute gluon, gamma/Z and second generation fermionic effective couplings
      for (int i = 0; i < 3; i++)
      {
        result.C_gg2[i] = result.compute_effective_coupling(i, std::pair<int,int>(21, 0), std::pair<int,int>(21, 0));
        result.C_gaga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(22, 0), std::pair<int,int>(22, 0));
        result.C_Zga2[i] = result.compute_effective_coupling(i, std::pair<int,int>(23, 0), std::pair<int,int>(22, 0));
        result.C_mumu2[i] = result.compute_effective_coupling(i, std::pair<int,int>(13, 1), std::pair<int,int>(-13, 1));
        result.C_ss2[i] = result.compute_effective_coupling(i, std::pair<int,int>(3, 1), std::pair<int,int>(-3, 1));
        result.C_cc2[i] = result.compute_effective_coupling(i, std::pair<int,int>(4, 1), std::pair<int,int>(-4, 1));
      }

      // Use couplings to get effective third-generation couplings
      for(int i = 0; i < 3; i++)
      {
        // Compute effective couplings
        double g2_s[3], g2_p[3];
        for (int j = 0; j < 3; j++) // j=0,1,2 => tau, t, b
        {
          fh_complex fh_L = Dep::FH_Couplings_output->couplings[H0FF(i+1,j+2,3,3)-1];
          fh_complex fh_R = Dep::FH_Couplings_output->couplings[H0FF(i+1,j+2,3,3)+Roffset-1];
          fh_complex fh_SM_L = Dep::FH_Couplings_output->couplings_sm[H0FF(i+1,j+2,3,3)-1];
          fh_complex fh_SM_R = Dep::FH_Couplings_output->couplings_sm[H0FF(i+1,j+2,3,3)+RSMoffset-1];
          std::complex<double> L(fh_L.re,fh_L.im);
          std::complex<double> R(fh_R.re,fh_R.im);
          std::complex<double> SM_L(fh_SM_L.re,fh_SM_L.im);
          std::complex<double> SM_R(fh_SM_R.re,fh_SM_R.im);
          g2_s[j] = 0.25*pow(std::abs(R/SM_R + L/SM_L), 2.);
          g2_p[j] = 0.25*pow(std::abs(R/SM_R - L/SM_L), 2.);
        }
        result.C_tautau2[i] = g2_s[0] + g2_p[0];
        result.C_tt2[i]     = g2_s[1] + g2_p[1];
        result.C_bb2[i]     = g2_s[2] + g2_p[2];

        // Calculate CP of state
        if(g2_p[2] < 1e-10)
          result.CP[i] = 1;
        else if(g2_s[2] < 1e-10)
          result.CP[i] = -1;
        else
          result.CP[i] = 0.;
      }

      // Use couplings to get di-boson effective couplings
      for(int i = 0; i < 3; i++)
      {
        fh_complex c_gWW = Dep::FH_Couplings_output->couplings[H0VV(i+1,4)-1];
        fh_complex c_gWW_SM = Dep::FH_Couplings_output->couplings_sm[H0VV(i+1,4)-1];
        fh_complex c_gZZ = Dep::FH_Couplings_output->couplings[H0VV(i+1,3)-1];
        fh_complex c_gZZ_SM = Dep::FH_Couplings_output->couplings_sm[H0VV(i+1,3)-1];
        std::complex<double> WW(c_gWW.re,c_gWW.im);
        std::complex<double> WW_SM(c_gWW_SM.re,c_gWW_SM.im);
        std::complex<double> ZZ(c_gZZ.re,c_gZZ.im);
        std::complex<double> ZZ_SM(c_gZZ_SM.re,c_gZZ_SM.im);
        result.C_WW2[i] = pow(std::abs(WW/WW_SM), 2.);
        result.C_ZZ2[i] = pow(std::abs(ZZ/ZZ_SM), 2.);
      }

      // Use couplings to get hhZ effective couplings
      double norm = sminputs.GF*sqrt(2.)*sminputs.mZ*sminputs.mZ;
      for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
      {
        fh_complex c_gHV = Dep::FH_Couplings_output->couplings[H0HV(i+1,j+1)-1];
        double g2HV = c_gHV.re*c_gHV.re+c_gHV.im*c_gHV.im;
        result.C_hiZ2[i][j] = g2HV/norm;
      }

      // Work out which invisible decays are possible
      result.invisibles = get_invisibles(spec);
    }

    // @}


  } // end namespace SpecBit
} // end namespace Gambit

