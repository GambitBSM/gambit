//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class function definitions and specialization init functions for SpecializablePythia.

#include <stdexcept>
#include <sstream>
#include "gambit/ColliderBit/colliders/SpecializablePythia.hpp"
#include "gambit/ColliderBit/ColliderBit_macros.hpp"

/*#include "Pythia8/Sigma_MC4BSM_2012_UFO_gg_uvuvx.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_uvuvx.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_evevx.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_p1p2.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_p2p2.h"
#include "Pythia8/Sigma_MC4BSM_2012_UFO_qq_p1p1.h"*/

namespace Gambit
{
  namespace ColliderBit
  {

    /// @brief Contains a SpecializablePythia init function which does nothing
    /// @note Pythia settings may still be applied externally via yaml file input.
    namespace Pythia_external
    {
      void init(SpecializablePythia*) { }
    }

    /// @brief Contains a SpecializablePythia init function for a basic SUSY @ 8TeV LHC scenario.
    /// @note Additional Pythia settings may still be applied externally via yaml file input.
    namespace Pythia_SUSY_LHC_8TeV
    {

      void init(SpecializablePythia* specializeMe) {
        specializeMe->addToSettings("Beams:eCM = 8000");
        specializeMe->addToSettings("Main:timesAllowErrors = 1000");
        specializeMe->addToSettings("SUSY:all = on");
        specializeMe->addToSettings("Random:setSeed = on");
      }

    }

    /// @brief Contains a SpecializablePythia init function for gluino-squark production @ 8TeV LHC scenario.
    /// @note This "inherits" Pythia_SUSY_LHC_8TeV by explicitly calling its init before changing additional settings.
    /// @note Additional Pythia settings may still be applied externally via yaml file input.
    namespace Pythia_glusq_LHC_8TeV
    {

      void init(SpecializablePythia* specializeMe)
      {
        Pythia_SUSY_LHC_8TeV::init(specializeMe);
        specializeMe->addToSettings("SUSY:idA = 1000021");
        specializeMe->addToSettings("SUSY:idVecB = 1000001, 1000002, 1000003, 1000004, 2000001, 2000002, 2000003, 2000004");
      }
    }

    /// @brief Contains a SpecializablePythia init function for a basic SUSY @ 8TeV LHC scenario.
    /// @note Additional Pythia settings may still be applied externally via yaml file input.
    namespace Pythia_SUSY_LHC_13TeV
    {

      void init(SpecializablePythia* specializeMe) {
        specializeMe->addToSettings("Beams:eCM = 13000");
        specializeMe->addToSettings("Main:timesAllowErrors = 1000");
        specializeMe->addToSettings("SUSY:all = on");
        specializeMe->addToSettings("Random:setSeed = on");
      }

    }





    SpecializablePythia::~SpecializablePythia()
    {
      _pythiaSettings.clear();
      if (_pythiaInstance) delete _pythiaInstance;
      if (_pythiaBase) delete _pythiaBase;
    }

    void SpecializablePythia::clear()
    {
      _pythiaSettings.clear();
      if (_pythiaInstance)
      {
        delete _pythiaInstance;
        _pythiaInstance=nullptr;
      }
    }        

    void SpecializablePythia::init_user_model(const std::string pythiaDocPath,
                                              const std::vector<std::string>& externalSettings,
                                              const SLHAea::Coll* slhaea, std::ostream& os)
    {
      // Special version of the init function for user defined models
      // Needs to directly construct the new matrix elements (rather than use flags)

      // Settings acquired externally (ex from a gambit yaml file)
      for(const auto command : externalSettings) _pythiaSettings.push_back(command);

      // Specialized settings:
      _specialInit(this);

      if (!_pythiaBase)
      {
        _pythiaBase = new Pythia8::Pythia(pythiaDocPath, false);
      }
      // Pass all settings to _pythiaBase
      for(const auto command : _pythiaSettings) _pythiaBase->readString(command);

      // Create new _pythiaInstance from _pythiaBase
      if (_pythiaInstance) delete _pythiaInstance;
      _pythiaInstance = new Pythia8::Pythia(_pythiaBase->particleData, _pythiaBase->settings);

      // Send along the SLHAea::Coll pointer, if it exists
      if (slhaea) _pythiaInstance->slhaInterface.slha.setSLHAea(slhaea);

      if (!_pythiaInstance->init(os)) throw InitializationError();
    }

    void SpecializablePythia::init(const std::string pythiaDocPath,
                                   const std::vector<std::string>& externalSettings,
                                   const SLHAea::Coll* slhaea, std::ostream& os) {
      // Settings acquired externally (ex from a gambit yaml file)
      for(const auto command : externalSettings) _pythiaSettings.push_back(command);
      
      // Specialized settings:
      _specialInit(this);

      if (!_pythiaBase)
      {
        _pythiaBase = new Pythia8::Pythia(pythiaDocPath, false);
      }
      // Pass all settings to _pythiaBase
      for(const auto command : _pythiaSettings){
	_pythiaBase->readString(command);

      }

      // Create new _pythiaInstance from _pythiaBase
      if (_pythiaInstance) delete _pythiaInstance;
      _pythiaInstance = new Pythia8::Pythia(_pythiaBase->particleData, _pythiaBase->settings);

      // Send along the SLHAea::Coll pointer, if it exists
      if (slhaea) _pythiaInstance->slhaInterface.slha.setSLHAea(slhaea);

      // MJW attempts to read commands again to get SM decay table change working from yaml file
      for(const auto command : _pythiaSettings){
	_pythiaInstance->readString(command);
      }

	
	
      if (!_pythiaInstance->init(os)) throw InitializationError();
    }

    void SpecializablePythia::resetSpecialization(const std::string& specName)
    {

      clear();
      IF_X_SPECIALIZEX(Pythia_external)
      IF_X_SPECIALIZEX(Pythia_SUSY_LHC_8TeV)
      IF_X_SPECIALIZEX(Pythia_glusq_LHC_8TeV)
      IF_X_SPECIALIZEX(Pythia_SUSY_LHC_13TeV)
      // default to a Pythia instance configured entirely by external (yaml) settings:
      _specialInit = Pythia_external::init;
      std::cout<<"\n\n\n"
               <<"COLLIDERBIT WARNING: Pythia named "<<specName<<" is not coded in SpecializablePythia."
               <<"                     Now trying to configure Pythia entirely by yaml input..."
               <<"\n\n\n";
    }

  }
}
