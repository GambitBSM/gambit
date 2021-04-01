//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Class for holding ColliderBit analyses.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Abram Krislock
///          (a.m.b.krislock@fys.uio.no)
///
///  \author Andy Buckley
///          (mostlikelytobefound@facebook.com)
///
///  \author Anders Kvellestad
///          (anders.kvellestad@fys.uio.no)
///  \date often
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2019 Feb
///
///  *********************************************

#include <stdexcept>

#include <omp.h>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/ColliderBit/analyses/AnalysisContainer.hpp"
#include "gambit/ColliderBit/analyses/Analysis.hpp"
#include "gambit/Utils/standalone_error_handlers.hpp"

// #define ANALYSISCONTAINER_DEBUG

namespace Gambit
{
  namespace ColliderBit
  {

    // Add analysis names here and only here (trick to avoid duplication)
    // - If the analysis depends on RestFrames (which uses ROOT), add it to MAP_ANALYSES_WITH_ROOT_RESTFRAMES
    // - If the analysis only depends on ROOT, add it to MAP_ANALYSES_WITH_ROOT
    // - Else, add the analysis to MAP_ANALYSES
    #define MAP_ANALYSES_WITH_ROOT_RESTFRAMES(F)     \
      F(ATLAS_13TeV_RJ3L_2Lep2Jets_36invfb)          \
      F(ATLAS_13TeV_RJ3L_3Lep_36invfb)               \
      F(ATLAS_13TeV_RJ3L_lowmass_36invfb)            \

    #define MAP_ANALYSES_WITH_ROOT(F)                \
      F(ATLAS_13TeV_1LEPStop_36invfb)                \

    #define MAP_ANALYSES(F)                          \
      F(Minimum)                                     \
      F(Covariance)                                  \
      F(ATLAS_13TeV_0LEP_13invfb)                    \
      F(ATLAS_13TeV_0LEP_36invfb)                    \
      F(ATLAS_13TeV_0LEP_139invfb)                   \
      F(ATLAS_13TeV_0LEPStop_36invfb)                \
      F(ATLAS_13TeV_2LEPStop_36invfb)                \
      F(ATLAS_13TeV_2LEPStop_139invfb)               \
      F(ATLAS_13TeV_2LEPStop_inclusive_139invfb)     \
      F(ATLAS_13TeV_2LEPStop_exclusive_139invfb)     \
      F(ATLAS_13TeV_MultiLEP_confnote_36invfb)       \
      F(ATLAS_13TeV_MultiLEP_36invfb)                \
      F(ATLAS_13TeV_MultiLEP_2Lep0Jets_36invfb)      \
      F(ATLAS_13TeV_MultiLEP_2LepPlusJets_36invfb)   \
      F(ATLAS_13TeV_MultiLEP_3Lep_36invfb)           \
      F(ATLAS_13TeV_MultiLEP_strong_139invfb)        \
      F(ATLAS_13TeV_2OSLEP_chargino_80invfb)         \
      F(ATLAS_13TeV_2OSLEP_chargino_binned_80invfb)  \
      F(ATLAS_13TeV_2OSLEP_chargino_inclusive_80invfb)  \
      F(ATLAS_13TeV_2OSLEP_chargino_139invfb)        \
      F(ATLAS_13TeV_2OSLEP_chargino_inclusive_139invfb) \
      F(ATLAS_13TeV_2OSLEP_chargino_binned_139invfb) \
      F(ATLAS_13TeV_4LEP_36invfb)                    \
      F(ATLAS_13TeV_4LEP_139invfb)                   \
      F(ATLAS_13TeV_2bMET_36invfb)                   \
      F(ATLAS_13TeV_3b_24invfb)                      \
      F(ATLAS_13TeV_3b_discoverySR_24invfb)          \
      F(ATLAS_13TeV_3b_36invfb)                      \
      F(ATLAS_13TeV_3b_discoverySR_36invfb)          \
      F(ATLAS_13TeV_PhotonGGM_36invfb)               \
      F(ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb)     \
      F(ATLAS_13TeV_2OSLEP_Z_139invfb)               \
      F(ATLAS_8TeV_0LEP_20invfb)                     \
      F(ATLAS_8TeV_0LEPStop_20invfb)                 \
      F(ATLAS_8TeV_1LEPStop_20invfb)                 \
      F(ATLAS_8TeV_2bStop_20invfb)                   \
      F(ATLAS_8TeV_2LEPEW_20invfb)                   \
      F(ATLAS_8TeV_2LEPStop_20invfb)                 \
      F(ATLAS_8TeV_3LEPEW_20invfb)                   \
      F(ATLAS_8TeV_1LEPbb_20invfb)                   \
      F(ATLAS_7TeV_1OR2LEPStop_4_7invfb)             \
      F(ATLAS_7TeV_2LEPStop_4_7invfb)                \
      F(CMS_13TeV_0LEP_13invfb)                      \
      F(CMS_13TeV_0LEP_36invfb)                      \
      F(CMS_13TeV_0LEP_137invfb)                     \
      F(CMS_13TeV_1LEPbb_36invfb)                    \
      F(CMS_13TeV_1LEPStop_36invfb)                  \
      F(CMS_13TeV_2LEPStop_36invfb)                  \
      F(CMS_13TeV_2LEPsoft_36invfb)                  \
      F(CMS_13TeV_2LEPsoft_36invfb_nocovar)          \
      F(CMS_13TeV_2LEPsoft_stop_36invfb)             \
      F(CMS_13TeV_2LEPsoft_stop_36invfb_nocovar)     \
      F(CMS_13TeV_2OSLEP_36invfb)                    \
      F(CMS_13TeV_2OSLEP_36invfb_nocovar)            \
      F(CMS_13TeV_2OSLEP_confnote_36invfb)           \
      F(CMS_13TeV_2OSLEP_chargino_stop_36invfb)      \
      F(CMS_13TeV_2OSLEP_for_stop_36invfb)           \
      F(CMS_13TeV_2OSLEP_for_chargino_36invfb)       \
      F(CMS_13TeV_2SSLEP_Stop_36invfb)               \
      F(CMS_13TeV_2SSLEP_Stop_inclusive_36invfb)     \
      F(CMS_13TeV_2SSLEP_Stop_exclusive_36invfb)     \
      F(CMS_13TeV_2SSLEP_Stop_137invfb)              \
      F(CMS_13TeV_Photon_GMSB_36invfb)               \
      F(CMS_13TeV_2Photon_GMSB_36invfb)              \
      F(CMS_13TeV_1Photon1Lepton_36invfb)            \
      F(CMS_13TeV_1Photon1Lepton_emu_combined_36invfb) \
      F(CMS_13TeV_MultiLEP_36invfb)                  \
      F(CMS_13TeV_MultiLEP_2SSLep_36invfb)           \
      F(CMS_13TeV_MultiLEP_3Lep_36invfb)             \
      F(CMS_13TeV_MultiLEP_Full_36invfb)             \
      F(CMS_13TeV_MultiLEP_Full_2SSLep_36invfb)      \
      F(CMS_13TeV_MultiLEP_Full_3Lep_36invfb)        \
      F(CMS_13TeV_MultiLEP_Full_3Lep_rebinned_36invfb) \
      F(CMS_13TeV_MONOJET_36invfb)                   \
      F(CMS_8TeV_1LEPDMTOP_20invfb)                  \
      F(CMS_8TeV_2LEPDMTOP_20invfb)                  \
      F(CMS_8TeV_MultiLEP_20invfb)                   \
      F(CMS_8TeV_MultiLEP_3Lep_20invfb)              \
      F(CMS_8TeV_MultiLEP_4Lep_20invfb)              \
      F(CMS_8TeV_MONOJET_20invfb)                    \

    /// For analysis factory function declaration
    #define DECLARE_ANALYSIS_FACTORY(ANAME)          \
      Analysis* create_Analysis_ ## ANAME();         \
      std::string getDetector_ ## ANAME();

    /// Forward declarations using DECLARE_ANALYSIS_FACTORY(ANAME)
    #ifndef EXCLUDE_ROOT
      #ifndef EXCLUDE_RESTFRAMES
        MAP_ANALYSES_WITH_ROOT_RESTFRAMES(DECLARE_ANALYSIS_FACTORY)
      #endif
      MAP_ANALYSES_WITH_ROOT(DECLARE_ANALYSIS_FACTORY)
    #endif
    MAP_ANALYSES(DECLARE_ANALYSIS_FACTORY)

    /// For the string-based factory function mkAnalysis()
    #define IF_X_RTN_CREATE_ANA_X(A)                                           \
      if (name == #A) return create_Analysis_ ## A();

    /// Factory definition
    Analysis* mkAnalysis(const str& name)
    {
      #ifndef EXCLUDE_ROOT
        #ifndef EXCLUDE_RESTFRAMES
          MAP_ANALYSES_WITH_ROOT_RESTFRAMES(IF_X_RTN_CREATE_ANA_X)
        #endif
        MAP_ANALYSES_WITH_ROOT(IF_X_RTN_CREATE_ANA_X)
      #endif
      MAP_ANALYSES(IF_X_RTN_CREATE_ANA_X)

      // If we end up here the analysis has not been found
      utils_error().raise(LOCAL_INFO, "The analysis " + name + " is not a known ColliderBit analysis.");
      return nullptr;
    }

    /// For the string-based analysis checker and detector retriever getDetector
    #define IF_X_RTN_DETECTOR(A)                                               \
      if (name == #A) return getDetector_ ## A();

    /// Return the detector to be used for a given analysis name (and check that the analysis exists).
    str getDetector(const str& name)
    {
      #ifndef EXCLUDE_ROOT
        #ifndef EXCLUDE_RESTFRAMES
          MAP_ANALYSES_WITH_ROOT_RESTFRAMES(IF_X_RTN_DETECTOR)
        #endif
        MAP_ANALYSES_WITH_ROOT(IF_X_RTN_DETECTOR)
      #endif
      MAP_ANALYSES(IF_X_RTN_DETECTOR)

      // If we end up here the analysis has not been found
      utils_error().raise(LOCAL_INFO, "The analysis " + name + " is not a known ColliderBit analysis.");
      return "";
    }

    /// A map with pointers to all instances of this class. The key is the thread number.
    std::map<str,std::map<int,AnalysisContainer*> > AnalysisContainer::instances_map;

    /// Constructor
    AnalysisContainer::AnalysisContainer() : current_collider(""),
                                             is_registered(false),
                                             n_threads(omp_get_max_threads()),
                                             base_key("")
    {
      #ifdef ANALYSISCONTAINER_DEBUG
        std::cout << "DEBUG: thread " << omp_get_thread_num() << ": AnalysisContainer::ctor: created at " << this << std::endl;
      #endif
    }


    /// Destructor
    AnalysisContainer::~AnalysisContainer()
    {
      clear();
    }


    /// Add container to instances map
    void AnalysisContainer::register_thread(str base_key_in)
    {
      base_key = base_key_in;

      #pragma omp critical
      {
        if (instances_map.count(base_key) == 0 || instances_map[base_key].count(omp_get_thread_num()) == 0)
        {
          // Add this instance to the instances map
          instances_map[base_key][omp_get_thread_num()] = this;
          is_registered = true;

          #ifdef ANALYSISCONTAINER_DEBUG
            std::cout << "DEBUG: thread " << omp_get_thread_num() << ": AnalysisContainer::register_thread: added " << this << " to instances_map with key " << base_key << "-" << omp_get_thread_num() << std::endl;
          #endif
        }
        else
        {
          if (not is_registered)
          {
            utils_error().raise(LOCAL_INFO, "There is already an entry with this key in instances_map, but it's not this one! Something has gone wrong...");
          }
          else
          {
            #ifdef ANALYSISCONTAINER_DEBUG
              std::cout << "DEBUG: thread " << omp_get_thread_num() << ": AnalysisContainer::register_thread: this instance is already in instances_map" << std::endl;
            #endif
          }
        }
      }
    }


    /// Delete and clear the analyses contained within this instance.
    void AnalysisContainer::clear()
    {
      /// @todo Storing smart ptrs to Analysis would make this way easier
      // Loop through double map and delete the analysis pointers
      for(auto& collider_map_pair : analyses_map)
      {
        for(auto& analysis_pointer_pair : collider_map_pair.second)
        {
          delete analysis_pointer_pair.second;
          analysis_pointer_pair.second = nullptr;
        }
      }

      // Clear the double map
      analyses_map.clear();
    }


    /// Set name of the current collider
    void AnalysisContainer::set_current_collider(str collider_name)
    {
      current_collider = collider_name;
    }


    /// Get the name of the current collider
    str AnalysisContainer::get_current_collider() const
    {
      return current_collider;
    }


    /// Does this instance contain analyses for the given collider
    bool AnalysisContainer::has_analyses(str collider_name) const
    {
      bool result = false;

      if (analyses_map.count(collider_name) > 0)
      {
        if (analyses_map.at(collider_name).size() > 0)
        {
          result = true;
        }
      }

      return result;
    }

    /// Does this instance contain analyses for the current collider
    bool AnalysisContainer::has_analyses() const
    {
      return has_analyses(current_collider);
    }


    /// Initialize analyses (by names) for a specified collider
    void AnalysisContainer::init(const std::vector<str>& analysis_names, str collider_name)
    {
      // If a map of analyses already exist for this collider, clear it
      if (analyses_map.count(collider_name) > 0)
      {
        analyses_map[collider_name].clear();
      }

      // Create analysis pointers and add to the map
      for (auto& aname : analysis_names)
      {
        analyses_map[collider_name][aname] = mkAnalysis(aname);
      }
    }

    /// Initialize analyses (by names) for the current collider
    void AnalysisContainer::init(const std::vector<str>& analysis_names)
    {
      init(analysis_names, current_collider);
    }


    /// Reset specific analysis
    void AnalysisContainer::reset(str collider_name, str analysis_name)
    {
      analyses_map[collider_name][analysis_name]->reset();
    }

    /// Reset all analyses for given collider
    void AnalysisContainer::reset(str collider_name)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        analysis_pointer_pair.second->reset();
      }
    }

    /// Reset all analyses for the current collider
    void AnalysisContainer::reset()
    {
      reset(current_collider);
    }

    /// Reset all analyses for all colliders
    void AnalysisContainer::reset_all()
    {
      for(auto& collider_map_pair : analyses_map)
      {
        reset(collider_map_pair.first);
      }
    }


    /// Get pointer to specific analysis
    const Analysis* AnalysisContainer::get_analysis_pointer(str collider_name, str analysis_name) const
    {
      return analyses_map.at(collider_name).at(analysis_name);
    }

    /// Get analyses map for a specific collider
    const std::map<str,Analysis*>& AnalysisContainer::get_collider_analyses_map(str collider_name) const
    {
      return analyses_map.at(collider_name);
    }

    /// Get analyses map for the current collider
    const std::map<str,Analysis*>& AnalysisContainer::get_current_analyses_map() const
    {
      return analyses_map.at(current_collider);
    }

    /// Get the full analyses map
    const std::map<str,std::map<str,Analysis*> >& AnalysisContainer::get_full_analyses_map() const
    {
      return analyses_map;
    }

    /// Pass event through specific analysis
    void AnalysisContainer::analyze(const HEPUtils::Event& event, str collider_name, str analysis_name) const
    {
      analyses_map.at(collider_name).at(analysis_name)->analyze(event);
    }

    /// Pass event through all analyses for a specific collider
    void AnalysisContainer::analyze(const HEPUtils::Event& event, str collider_name) const
    {
      for (auto& analysis_pointer_pair : analyses_map.at(collider_name))
      {
        analysis_pointer_pair.second->analyze(event);
      }
    }

    /// Pass event through all analysis for the current collider
    void AnalysisContainer::analyze(const HEPUtils::Event& event) const
    {
      analyze(event, current_collider);
    }

    /// Collect signal predictions from other threads and add to this one,
    /// for specific analysis. Note: Analysis::add will not add analyses to themselves.
    void AnalysisContainer::collect_and_add_signal(str collider_name, str analysis_name)
    {
      for (auto& thread_container_pair : instances_map.at(base_key))
      {
        AnalysisContainer* other_container = thread_container_pair.second;
        Analysis* other_analysis = other_container->analyses_map.at(collider_name).at(analysis_name);
        analyses_map.at(collider_name).at(analysis_name)->add(other_analysis);
      }
    }

    /// Collect signal predictions from other threads and add to this one,
    /// for all analyses for given collider
    void AnalysisContainer::collect_and_add_signal(str collider_name)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        str analysis_name = analysis_pointer_pair.first;
        collect_and_add_signal(collider_name, analysis_name);
      }
    }

    /// Collect signal predictions from other threads and add to this one,
    /// for all analyses for the current collider
    void AnalysisContainer::collect_and_add_signal()
    {
      collect_and_add_signal(current_collider);
    }

    /// Scale results for specific analysis
    void AnalysisContainer::scale(str collider_name, str analysis_name, double xsec_per_event)
    {
      analyses_map[collider_name][analysis_name]->scale(xsec_per_event);
    }

    /// Scale results for all analyses for given collider
    void AnalysisContainer::scale(str collider_name, double xsec_per_event)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        str analysis_name = analysis_pointer_pair.first;
        scale(collider_name, analysis_name, xsec_per_event);
      }
    }

    /// Scale results for all analyses for the current collider
    void AnalysisContainer::scale(double xsec_per_event)
    {
      scale(current_collider, xsec_per_event);
    }

    /// Scale results for all analyses across all colliders
    void AnalysisContainer::scale_all(double xsec_per_event)
    {
      for (auto& collider_map_pair : analyses_map)
      {
        str collider_name = collider_map_pair.first;
        scale(collider_name, xsec_per_event);
      }
    }

  }
}
