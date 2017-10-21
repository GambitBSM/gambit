//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///
///  Example of GAMBIT ColliderBit standalone
///  main program.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  Martin White (martin.white@adelaide.edu.au)
///  January 2016
///  Anders Kvellestad (anders.kvellestad@nordita.org)
///  March 2017
///
///  *********************************************


//
// Note:
// For this example we use the GAMBIT backend Pythia 8.212.EM, which is connected to GAMBIT
// vis BOSS. For this to work, make sure that this version of Pythia is specificed in
// Backends/include/gambit/Backends/default_bossed_versions.hpp (use: #define Default_Pythia 8_212_EM).
//

// Always required for the standalone main file
#include "gambit/Elements/standalone_module.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"

using namespace ColliderBit::Accessors;     // Helper functions that provide some info about the module (here: ColliderBit)
using namespace ColliderBit::Functown;      // Functors wrapping the module's actual module functions
using namespace BackendIniBit::Functown;    // Functors wrapping the backend initialisation functions

using namespace std;

// Useful typedefs
typedef vector<int> vint;
typedef vector<double> vdouble;
typedef vector<bool> vbool;
typedef vector<string> vstr;
typedef vector<vector<string> > vvstr;



//
// ----------------------
//      Main program
// ----------------------
//
int main(int argc, char* argv[])
{

  try{

    // Initialise logs
    initialise_standalone_logs("runs/ColliderBit_standalone/logs/");
    logger()<<"Running ColliderBit standalone example"<<LogTags::info<<EOM;


    cout << endl;
    cout << "==================================" << endl;
    cout << "||                              ||" << endl;
    cout << "||    ColliderBit standalone    ||" << endl;
    cout << "||                              ||" << endl;
    cout << "==================================" << endl;
    cout << endl;


    // Check the number of command line arguments
    if (argc < 2)
    {
      // Tell the user how to run the program and exit
      cerr << "Usage: " << argv[0] << " <input SLHA file>" << endl << endl;
      return 1;
    }

    // Read input file name
    const string inputFileName = argv[1];


    // Check that required backends are present
    if (not Backends::backendInfo().works["Pythia8.212.EM"]) backend_error().raise(LOCAL_INFO, "Pythia 8.212.EM is missing!");
    if (not Backends::backendInfo().works["nulike1.0.5"]) backend_error().raise(LOCAL_INFO, "nulike 1.0.5 is missing!");

    // Output some info about ColliderBit
    cout << endl << "My name is " << name() << endl;
    cout << endl << "I can calculate: " << endl << iCanDo << endl;
    cout << endl << "...but I may need: " << endl << iMayNeed << endl << endl;




    // -----------------------------------
    //    Part 1:  Dependecy resolution
    // -----------------------------------
    //
    // We now set up the module functions that we wish use.
    // Dependencies and backend requirements of module functions are resolved by hand.
    // WARNING: DO NOT EDIT UNLESS YOU ARE AN EXPERT.
    //

    // Set up the LHC likelihood calculations
    calc_LHC_LogLike.resolveDependency(&runATLASAnalyses);
    calc_LHC_LogLike.resolveDependency(&runCMSAnalyses);
    calc_LHC_LogLike.resolveDependency(&runIdentityAnalyses);
    calc_LHC_LogLike.resolveBackendReq(&Backends::nulike_1_0_5::Functown::nulike_lnpiln); //treat systematics with a log normal distribution

    runATLASAnalyses.resolveDependency(&getATLASAnalysisContainer);
    runATLASAnalyses.resolveDependency(&getPythiaFileReader);
    runATLASAnalyses.resolveDependency(&smearEventATLAS);
    runCMSAnalyses.resolveDependency(&getCMSAnalysisContainer);
    runCMSAnalyses.resolveDependency(&getPythiaFileReader);
    runCMSAnalyses.resolveDependency(&smearEventCMS);
    runIdentityAnalyses.resolveDependency(&getIdentityAnalysisContainer);
    runIdentityAnalyses.resolveDependency(&getPythiaFileReader);
    runIdentityAnalyses.resolveDependency(&copyEvent);

    getATLASAnalysisContainer.resolveDependency(&getPythiaFileReader);
    getCMSAnalysisContainer.resolveDependency(&getPythiaFileReader);
    getIdentityAnalysisContainer.resolveDependency(&getPythiaFileReader);

    smearEventATLAS.resolveDependency(&generatePythia8Event);
    smearEventATLAS.resolveDependency(&getBuckFastATLAS);
    smearEventCMS.resolveDependency(&generatePythia8Event);
    smearEventCMS.resolveDependency(&getBuckFastCMS);
    copyEvent.resolveDependency(&generatePythia8Event);
    copyEvent.resolveDependency(&getBuckFastIdentity);

    generatePythia8Event.resolveDependency(&getPythiaFileReader);

    getPythiaFileReader.resolveLoopManager(&operateLHCLoop);
    getBuckFastATLAS.resolveLoopManager(&operateLHCLoop);
    getBuckFastCMS.resolveLoopManager(&operateLHCLoop);
    getBuckFastIdentity.resolveLoopManager(&operateLHCLoop);

    getATLASAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    getCMSAnalysisContainer.resolveLoopManager(&operateLHCLoop);
    getIdentityAnalysisContainer.resolveLoopManager(&operateLHCLoop);

    generatePythia8Event.resolveLoopManager(&operateLHCLoop);

    smearEventATLAS.resolveLoopManager(&operateLHCLoop);
    smearEventCMS.resolveLoopManager(&operateLHCLoop);
    copyEvent.resolveLoopManager(&operateLHCLoop);

    runATLASAnalyses.resolveLoopManager(&operateLHCLoop);
    runCMSAnalyses.resolveLoopManager(&operateLHCLoop);
    runIdentityAnalyses.resolveLoopManager(&operateLHCLoop);

    vector<functor*> nested_functions = initVector<functor*>(&getPythiaFileReader,
                                                                  &getBuckFastATLAS,
                                                                  &getBuckFastCMS,
                                                                  &getBuckFastIdentity,
                                                                  &getATLASAnalysisContainer,
                                                                  &getCMSAnalysisContainer,
                                                                  &getIdentityAnalysisContainer,
                                                                  &generatePythia8Event,
                                                                  &smearEventATLAS,
                                                                  &smearEventCMS,
                                                                  &copyEvent,
                                                                  &runATLASAnalyses,
                                                                  &runCMSAnalyses,
                                                                  &runIdentityAnalyses);
    operateLHCLoop.setNestedList(nested_functions);


    //
    // Examples of how to output info about the dependecy resolution:
    //

    // - Double-check which backend requirements have been filled with what
    // cout << endl << "My function calc_LHC_LogLike has had its backend requirement on lnlike_marg_poisson filled by:" << endl;
    // cout << ColliderBit::Pipes::calc_LHC_LogLike::BEreq::lnlike_marg_poisson_lognormal_error.origin() << "::";
    // cout << ColliderBit::Pipes::calc_LHC_LogLike::BEreq::lnlike_marg_poisson_lognormal_error.name() << endl;

    // - Double-check which dependencies have been filled with what (only a few combinations shown here)
    // cout << endl << "My function calc_LHC_LogLike has had its dependency on ATLASAnalysisNumbers filled by:" << endl;
    // cout << ColliderBit::Pipes::calc_LHC_LogLike::Dep::ATLASAnalysisNumbers.origin() << "::";
    // cout << ColliderBit::Pipes::calc_LHC_LogLike::Dep::ATLASAnalysisNumbers.name() << endl;
    // cout << endl << "My function calc_LHC_LogLike has had its dependency on CMSAnalysisNumbers filled by:" << endl;
    // cout << ColliderBit::Pipes::calc_LHC_LogLike::Dep::CMSAnalysisNumbers.origin() << "::";
    // cout << ColliderBit::Pipes::calc_LHC_LogLike::Dep::CMSAnalysisNumbers.name() << endl;
    // cout << endl << "My function runATLASAnalyses has had its dependency on ATLASSmearedEvent filled by:" << endl;
    // cout << ColliderBit::Pipes::runATLASAnalyses::Dep::ATLASSmearedEvent.origin() << "::";
    // cout << ColliderBit::Pipes::runATLASAnalyses::Dep::ATLASSmearedEvent.name() << endl;
    // cout << endl << "My function runATLASAnalyses has had its dependency on ATLASSmearedEvent filled by:" << endl;
    // cout << ColliderBit::Pipes::runATLASAnalyses::Dep::ATLASSmearedEvent.origin() << "::";
    // cout << ColliderBit::Pipes::runATLASAnalyses::Dep::ATLASSmearedEvent.name() << endl;




    // ----------------------------
    //    Part 2:  Configuration
    // ----------------------------
    //
    // Below we set the options for the various ColliderBit module functions.
    // This is where we configure our Pythia backends, choose detector simulation
    // and specify which LHC analyses to inlcude. See the ColiderBit manual for
    // available options.
    //

    //
    // Settings for the LHC event loop (ColliderBit function 'operateLHCLoop')
    //

    // Pass the collider names to the module function responsible for the event loop
    operateLHCLoop.setOption<vstr>("pythiaNames", vstr {"Pythia_EM_8Tev", "Pythia_EM_13TeV"});

    // Set number of LHC events
    operateLHCLoop.setOption<vint>("nEvents",vint {20000, 20000});

    // Should stdout be silenced during the event loop?
    operateLHCLoop.setOption<bool>("silenceLoop",false);


    //
    // Set up the collider(s), i.e. the different configurations of Pythia:
    //
    // For this example we will set up two colliders, "Pythia_EM_8Tev" and "Pythia_EM_13TeV".
    // As these are not pre-configured in ColliderBit/src/colliders/SpecializablePythia.cpp,
    // we should specify all required settings below.
    //
    // (The file SpecializablePythia.cpp defines some partly configured colliders, e.g "Pythia_SUSY_LHC_8TeV" and
    // "Pythia_SUSY_LHC_13TeV, and others can be added if needed.)
    //

    // NOTE: If you want to set a fixed seed for Pythia through "Random:seed = ...",
    //       this must currently be done directly in the module function getPythiaFileReader
    //       in ColliderBit/src/CollderBit.cpp, in a similar manner to what is done there now.
    //       This is to avoid potential problems with OpenMP threads getting identical seeds.
    //
    //       Also, Pythia options specified directly in getPythiaFileReader in ColliderBit.cpp
    //       can override options given here.

    getPythiaFileReader.setOption<vstr>("Pythia_EM_8Tev", vstr
        {"UserModel:all = on",
         "Beams:eCM = 8000",
         "PartonLevel:MPI = off",
         "PartonLevel:ISR = on",
         "PartonLevel:FSR = off",
         "HadronLevel:all = off",
         "TauDecays:mode = 0",
         "Random:setSeed = on"} );

    getPythiaFileReader.setOption<vstr>("Pythia_EM_13TeV", vstr
        {"UserModel:all = on",
         "Beams:eCM = 13000",
         "PartonLevel:MPI = off",
         "PartonLevel:ISR = on",
         "PartonLevel:FSR = off",
         "HadronLevel:all = off",
         "TauDecays:mode = 0",
         "Random:setSeed = on"} );


    // Set the correct XML path for Pythia
    getPythiaFileReader.setOption<string>("Pythia_doc_path","Backends/installed/pythia/8.212.EM/share/Pythia8/xmldoc/"); // specify the Pythia xml file location

    // Specify the SLHA input file.
    // For this example we take the command line argument stored in 'inputFileName'.
    getPythiaFileReader.setOption<vstr>("SLHA_filenames", vstr {inputFileName});



    //
    // Specify which analyses to run and which detectors to use.
    //
    // Note: Adding more detectors and analysis containers
    //       (e.g. for Delphes) will require additions to the
    //       manual dependecy resolution at the top.
    //

    // -- ATLAS analyses:
    getBuckFastATLAS.setOption<vbool>("useDetector",vbool {true, true});
    getBuckFastATLAS.setOption<vdouble>("antiktR",vdouble {0.4, 0.4});
    getBuckFastATLAS.setOption<vbool>("partonOnly",vbool {true, true});

    getATLASAnalysisContainer.setOption<vvstr>("analyses", vvstr
        { {"ATLAS_0LEP_20invfb"},
          {"ATLAS_13TeV_0LEP_13invfb"} });


    // -- CMS analyses:
    getBuckFastCMS.setOption<vbool>("useDetector",vbool {false, false});
    getBuckFastCMS.setOption<vdouble>("antiktR",vdouble {0.5, 0.5});
    getBuckFastCMS.setOption<vbool>("partonOnly",vbool {true, true});

    getCMSAnalysisContainer.setOption<vvstr>("analyses", vvstr
        { {"CMS_MONOJET_20invfb"},
          {} });


    // // -- Identity analyses (no detector sim):
    // getBuckFastIdentity.setOption<vbool>("useDetector",vbool {false, false});
    // getBuckFastIdentity.setOption<vdouble>("antiktR",vdouble {0.4, 0.4});
    // getBuckFastIdentity.setOption<vbool>("partonOnly",vbool {false, false});

    // getIdentityAnalysisContainer.setOption<vvstr>("analyses", vvstr { {}, {} });



    // -----------------------
    //    Part 3: Execution
    // -----------------------
    //
    // Here we call the ColliderBit module functions
    // that run the LHC event loop and calculate the
    // log-likelihood.
    //

    // Call the initialisation functions for all backends that are in use.
    nulike_1_0_5_init.reset_and_calculate();
    Pythia_8_212_EM_init.reset_and_calculate();

    // Run the simulation loop and calculate the LHC likelihood.
    operateLHCLoop.reset_and_calculate();
    calc_LHC_LogLike.reset_and_calculate();

    // Retrieve and print the LHC likelihood
    double loglike = calc_LHC_LogLike(0);

    cout.precision(5);
    cout << endl;
    cout << scientific << "LHC log likelihood is " << loglike << endl;
    cout << endl;

    // To print to the logs instead, use
    // logger() << "LHC log likelihood is " << loglike << EOM

    // To output additional info such as the number of signal events
    // predicted for a given analysis and signal region, edit the
    // calc_LHC_LogLike module function in ColliderBit/src/ColliderBit.cpp.

    // Done, all is well
    return 0;
  }

  catch (std::exception& e)
  {
    cerr << "ColliderBit_standalone example has exited with fatal exception: " << e.what() << endl;
  }

  // Done, but something went wrong
  return 1;

}

