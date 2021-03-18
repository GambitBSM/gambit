//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  ColliderBit module functions for calculating 
///  event weights
///
///  The weight functions in this file are
///  independent of the particular Py8Collider type
///  used in event generation.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Anders Kvellestad
///          (a.kvellestad@imperial.ac.uk)
///  \date   2019 Sep
///
///  *********************************************

#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"

#define COLLIDERBIT_DEBUG
#define DEBUG_PREFIX "DEBUG: OMP thread " << omp_get_thread_num() << ":  "

namespace Gambit
{

  namespace ColliderBit
  {

    /// A function that sets the event weight to unity, with zero uncertainty
    void _setEventWeight_unity(HEPUtils::Event& event, const BaseCollider*)  // <-- Ignoring second argument
    {
      event.set_weight(1.0);
      event.set_weight_err(0.0);
    }

    /// Module function providing an instance of EventWeighterFunctionType
    /// pointing to _setEventWeight_unity
    void setEventWeight_unity(EventWeighterFunctionType& result)
    {
      using namespace Pipes::setEventWeight_unity;
      result = std::bind(_setEventWeight_unity, std::placeholders::_1, std::placeholders::_2);
    }



    /// A function that sets the event weight based on the process cross-sections
    void _setEventWeight_fromCrossSection(HEPUtils::Event& event, const BaseCollider* HardScatteringSim_ptr, const map_int_process_xsec& ProcessCrossSectionsMap, const int use_trust_level)
    {
      // Initialize weight
      double weight = 1.0;
      double weight_err = 0.0;

      // Get process code from the generator
      int process_code = HardScatteringSim_ptr->process_code();

      #ifdef COLLIDERBIT_DEBUG
        cerr << DEBUG_PREFIX << "Current process_code: " << process_code << endl;
      #endif

      // Get the process_xsec_container instance that holds the externally provided cross-section for this process
      process_xsec_container xs = ProcessCrossSectionsMap.at(process_code);

      // Get the generator cross-section for this process
      double process_xsec_generator = HardScatteringSim_ptr->xsec_fb(process_code);
      double process_xsec_err_generator_sq = pow(HardScatteringSim_ptr->xsecErr_fb(process_code), 2);

      #ifdef COLLIDERBIT_DEBUG
          cerr << DEBUG_PREFIX << "- process_code: " << process_code << ", xsec_fb: " << HardScatteringSim_ptr->xsec_fb(process_code)
                                                                     << ", xsec_err_fb: " << HardScatteringSim_ptr->xsecErr_fb(process_code) << endl;
      #endif

      // Determine what to do based on the trust_level of the externally provided cross-section:
      if (xs.trust_level() >= use_trust_level)
      {
        // Add the generator cross-sections for other process codes which also 
        // contribute to the externaly provided cross-section
        for (int other_process_code : xs.processes_sharing_xsec())
        {
          process_xsec_generator += HardScatteringSim_ptr->xsec_fb(other_process_code);
          process_xsec_err_generator_sq += pow(HardScatteringSim_ptr->xsecErr_fb(other_process_code), 2);
          #ifdef COLLIDERBIT_DEBUG
            cerr << DEBUG_PREFIX << "- process_code: " << other_process_code << ", xsec_fb: " << HardScatteringSim_ptr->xsec_fb(other_process_code)
                                                                             << ", xsec_err_fb: " << HardScatteringSim_ptr->xsecErr_fb(other_process_code) << endl;
          #endif
        }
        double process_xsec_err_generator = sqrt(process_xsec_err_generator_sq);

        // Event weight = [external cross-section] / [sum of contributing generator cross-sections]
        if (process_xsec_generator > 0.0)
        {
          weight = xs.xsec() / process_xsec_generator;
          weight_err = sqrt(  pow(xs.xsec_err() / process_xsec_generator, 2) 
                            + pow(xs.xsec() * process_xsec_err_generator / pow(process_xsec_generator, 2), 2) );
        }
        else
        {
          std::stringstream errmsg_ss;
          errmsg_ss << "Generated an event of process " << process_code << " for which the generator itself predicts a cross-section <= 0. Not sure what to do with that...";
          ColliderBit_error().raise(LOCAL_INFO, errmsg_ss.str());
        }
      }
      else
      {
        // Too low trust_level. Will fall back to use the generator cross-section
        #ifdef COLLIDERBIT_DEBUG
          cerr << DEBUG_PREFIX << "process_xsec trust_level too low (" << xs.trust_level() << "). Setting event weight to 1.0." << endl;
        #endif
        weight = 1.0;
        weight_err = 0.0;
      }

      #ifdef COLLIDERBIT_DEBUG
        cerr << DEBUG_PREFIX << "total process_xsec: " << xs.xsec() << ",  process_xsec_MC: " << process_xsec_generator << ",  weight: " << weight << ",  weight_err: " << weight_err << ",  trust_level: " << xs.trust_level() << endl;
      #endif

      event.set_weight(weight);
      event.set_weight_err(weight_err);
    }

    /// Module function providing an instance of EventWeighterFunctionType
    /// pointing to _setEventWeight_fromCrossSection
    void setEventWeight_fromCrossSection(EventWeighterFunctionType& result)
    {
      using namespace Pipes::setEventWeight_fromCrossSection;

      const static int use_trust_level = runOptions->getValueOrDef<int>(1, "use_cross_section_trust_level");
      
      if(*Loop::iteration < 0) return;

      result = std::bind(_setEventWeight_fromCrossSection,
                         std::placeholders::_1,
                         std::placeholders::_2,
                         *Dep::ProcessCrossSectionsMap, 
                         use_trust_level);
    }


  } 
} 


