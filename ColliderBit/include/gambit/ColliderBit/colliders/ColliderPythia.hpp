//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  The ColliderPythia class.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///  \date July 2016
///
///  \author Pat Scott
///  \date Jan 2019
///
///  *********************************************

#pragma once

#include <ostream>
#include <stdexcept>
#include "gambit/Elements/shared_types.hpp"
#include "gambit/ColliderBit/colliders/BaseCollider.hpp"
#include "SLHAea/slhaea.h"

namespace Gambit
{

  namespace ColliderBit
  {

    /// A specializable, recyclable class interfacing ColliderBit and Pythia.
    template <typename PythiaT, typename EventT>
    class ColliderPythia : public BaseCollider
    {

      protected:

        PythiaT* _pythiaInstance;
        PythiaT* _pythiaBase;
        std::vector<std::string> _pythiaSettings;


      public:

        /// Get the Pythia instance.
        const PythiaT* pythia() const { return _pythiaInstance; }


        /// @name Custom exceptions:
        ///@{

        /// An exception for when Pythia fails to initialize.
        class InitializationError : public std::exception
        {
          virtual const char* what() const throw()
          {
            return "Pythia could not initialize.";
          }
        };
        /// An exception for when Pythia fails to generate events.
        class EventGenerationError : public std::exception
        {
          virtual const char* what() const throw()
          {
            return "Pythia could not make the next event.";
          }
        };

        ///@}


        /// @name Construction, Destruction, and Recycling:
        ///@{

        ColliderPythia() : _pythiaInstance(nullptr), _pythiaBase(nullptr) {}

        ~ColliderPythia()
        {
          _pythiaSettings.clear();
          if (_pythiaInstance) delete _pythiaInstance;
          if (_pythiaBase) delete _pythiaBase;
        }

        void clear()
        {
          _pythiaSettings.clear();
          if (_pythiaInstance)
          {
            delete _pythiaInstance;
            _pythiaInstance=nullptr;
          }
        }

        ///@}


        /// @name (Re-)Initialization functions
        ///@{

        /// Add a command to the list of settings used by "init".
        void addToSettings(const std::string& command) { _pythiaSettings.push_back(command); }
        /// Create a useless Pythia instance just to print the banner.
        void banner(const std::string pythiaDocPath) { PythiaT myPythia(pythiaDocPath); }
        /// Initialize with no settings (error): override version.
        void init() { std::cout<<"No settings given to Pythia!\n\n"; throw InitializationError(); }

        /// Initialize from some external settings: override version.
        /// @note A string denoting the path to Pythia's xmldoc directory is
        /// @note assumed to be at the end of the settings vector:
        void init(const std::vector<std::string>& externalSettings)
        {
          std::string docPath = externalSettings.back();
          std::vector<std::string> settings(externalSettings);
          settings.pop_back();
          init(docPath, settings);
        }

        /// Initialize from some external settings.
        /// @note This override is most commonly used in ColliderBit.
        void init(const std::string pythiaDocPath,
                  const std::vector<std::string>& externalSettings,
                  const SLHAea::Coll* slhaea=nullptr, std::ostream& os=std::cout)
        {
          // Settings acquired externally (ex from a gambit yaml file)
          for(const auto command : externalSettings) _pythiaSettings.push_back(command);

          if (!_pythiaBase)
          {
            _pythiaBase = new PythiaT(pythiaDocPath, false);
          }

          // Pass all settings to _pythiaBase
          for(const auto command : _pythiaSettings) _pythiaBase->readString(command);

          // Create new _pythiaInstance from _pythiaBase
          if (_pythiaInstance) delete _pythiaInstance;
          _pythiaInstance = new PythiaT(_pythiaBase->particleData, _pythiaBase->settings);

          // Send along the SLHAea::Coll pointer, if it exists
          if (slhaea) _pythiaInstance->slhaInterface.slha.setSLHAea(slhaea);

          // Read command again to get SM decay table change from yaml file
          for(const auto command : _pythiaSettings)
          {
            _pythiaInstance->readString(command);
          }

          if (!_pythiaInstance->init(os)) throw InitializationError();
        }

        /// Initialize from some external settings.
        /// Special version of the init function for user defined models
        /// Needs to directly construct the new matrix elements (rather than use flags)
        void init_user_model(const std::string pythiaDocPath,
                             const std::vector<std::string>& externalSettings,
                             const SLHAea::Coll* slhaea=nullptr, std::ostream& os=std::cout)
        {
          // Settings acquired externally (for example, from a gambit yaml file)
          for(const auto command : externalSettings) _pythiaSettings.push_back(command);

          if (!_pythiaBase)
          {
            _pythiaBase = new PythiaT(pythiaDocPath, false);
          }

          // Pass all settings to _pythiaBase
          for(const auto command : _pythiaSettings) _pythiaBase->readString(command);

          // Create new _pythiaInstance from _pythiaBase
          if (_pythiaInstance) delete _pythiaInstance;
          _pythiaInstance = new PythiaT(_pythiaBase->particleData, _pythiaBase->settings);

          // Send along the SLHAea::Coll pointer, if it exists
          if (slhaea) _pythiaInstance->slhaInterface.slha.setSLHAea(slhaea);

          if (!_pythiaInstance->init(os)) throw InitializationError();
        }

        /// Initialize from some external settings, assuming no given SLHAea instance.
        void init(const std::string pythiaDocPath,
                  const std::vector<std::string>& externalSettings, std::ostream& os)
        {
          init(pythiaDocPath, externalSettings, nullptr, os);
        }

        /// Initialize from some external settings, assuming no given SLHAea instance.
        void init_user_model(const std::string pythiaDocPath,
                             const std::vector<std::string>& externalSettings, std::ostream& os)
        {
          init_user_model(pythiaDocPath, externalSettings, nullptr, os);
        }

        ///@}


        /// @name Event generation and cross section functions
        ///@{

        /// Event generation for any Pythia interface to Gambit.
        void nextEvent(EventT& event) const
        {
          // Try to make and populate an event
          bool accepted_event = _pythiaInstance->next();
          event = _pythiaInstance->event;
          if (!accepted_event)
          {
            throw EventGenerationError();
          }
        }

        /// Report the cross section (in pb) at the end of the subprocess.
        double xsec_pb() const { return _pythiaInstance->info.sigmaGen() * 1e9; }

        /// Report the cross section uncertainty (in pb) at the end of the subprocess.
        double xsecErr_pb() const { return _pythiaInstance->info.sigmaErr() * 1e9; }

        ///@}

     };

  }
}
