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
///  \author Tomas Gonzalo
///          (tomas.gonzalo@kit.edu)
///  \date 2019 June
///  \date 2023 Aug
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
    #define MAP_ANALYSES_WITH_ROOT_RESTFRAMES(F)        \
      F(ATLAS_SUSY_2017_03_RJR_2L2J)                    \
      F(ATLAS_SUSY_2017_03_RJR_3L)                      \
      F(ATLAS_SUSY_2017_03_RJR_Lowmass)                 \
      F(ATLAS_SUSY_2018_05_RJR)                         \
      F(ATLAS_SUSY_2018_12_RJR)                         \
      
    #define MAP_ANALYSES_WITH_ROOT(F)                   \
      F(ATLAS_SUSY_2016_06)                             \
      F(ATLAS_SUSY_2019_02)                             \

    #define MAP_ANALYSES_WITH_ONNX(F)                   \
      F(ATLAS_SUSY_2018_30)                             \

    #define MAP_ANALYSES(F)                             \
      F(Minimum)                                        \
      F(Covariance)                                     \
      F(Dummy)                                          \
      F(Baselines)                                      \
      F(ATLAS_8TeV_1LEPbb_20invfb)                      \
      F(ATLAS_EXOT_2016_013)                            \
      F(ATLAS_EXOT_2016_014)                            \
      F(ATLAS_EXOT_2016_017)                            \
      F(ATLAS_EXOT_2018_06)                             \
      F(ATLAS_EXOT_2019_07)                             \
      F(ATLAS_EXOT_2021_035)                             \
      F(ATLAS_SUSY_2018_41)                             \
      F(ATLAS_CONF_2016_078)                            \
      F(ATLAS_SUSY_2016_07)                             \
      F(ATLAS_SUSY_2018_22)                             \
      F(ATLAS_SUSY_2016_15)                             \
      F(ATLAS_SUSY_2018_12)                             \
      F(ATLAS_SUSY_2019_08)                             \
      F(ATLAS_SUSY_2018_07)                             \
      F(ATLAS_SUSY_2017_01)                             \
      F(ATLAS_SUSY_2018_05)                             \
      F(ATLAS_SUSY_2018_08)                             \
      F(ATLAS_SUSY_2018_08_inclusive)                   \
      F(ATLAS_SUSY_2018_08_exclusive)                   \
      F(ATLAS_CONF_2017_039)                            \
      F(ATLAS_SUSY_2016_24)                             \
      F(ATLAS_SUSY_2016_24_2Lep0Jets)                   \
      F(ATLAS_SUSY_2016_24_2LepPlusJets)                \
      F(ATLAS_SUSY_2016_24_3Lep)                     \
      F(ATLAS_SUSY_2018_09)                          \
      F(ATLAS_CONF_2018_042)                         \
      F(ATLAS_CONF_2018_042_chargino_binned)         \
      F(ATLAS_CONF_2018_042_chargino_inclusive)      \
      F(ATLAS_CONF_2019_008)                         \
      F(ATLAS_CONF_2019_008_chargino_inclusive)      \
      F(ATLAS_CONF_2019_008_chargino_binned)         \
      F(ATLAS_SUSY_2019_09)                          \
      F(ATLAS_SUSY_2018_06)                          \
      F(ATLAS_SUSY_2016_21)                          \
      F(ATLAS_SUSY_2018_02)                          \
      F(ATLAS_SUSY_2016_28)                          \
      F(ATLAS_SUSY_2017_02)                          \
      F(ATLAS_SUSY_2017_02_discoverySR)              \
      F(ATLAS_SUSY_2017_02_36invfb)                  \
      F(ATLAS_SUSY_2017_02_discoverySR_36invfb)      \
      F(ATLAS_SUSY_2020_16)                          \
      F(ATLAS_SUSY_2020_16_allyears)                 \
      F(ATLAS_SUSY_2020_16_discoverySR)              \
      F(ATLAS_SUSY_2016_27)                          \
      F(ATLAS_SUSY_2016_27_1Photon)                  \
      F(ATLAS_SUSY_2016_27_2Photon)                  \
      F(ATLAS_SUSY_2018_11)                          \
      F(ATLAS_CONF_2018_019)                         \
      F(ATLAS_SUSY_2018_21_StopZH)                   \
      F(ATLAS_SUSY_2018_21)                          \
      F(ATLAS_SUSY_2018_16)                          \
      F(ATLAS_SUSY_2019_18)                          \
      F(ATLAS_SUSY_2019_22)                          \
      F(ATLAS_SUSY_2013_02)                          \
      F(ATLAS_SUSY_2013_16)                          \
      F(ATLAS_CONF_2013_037)                         \
      F(ATLAS_SUSY_2013_05)                          \
      F(ATLAS_SUSY_2013_11)                          \
      F(ATLAS_SUSY_2013_19)                          \
      F(ATLAS_SUSY_2013_12)                          \
      F(ATLAS_SUSY_2012_10)                          \
      F(ATLAS_SUSY_2012_04)                          \
      F(CMS_SUS_16_014)                              \
      F(CMS_SUS_16_033)                              \
      F(CMS_SUS_19_006)                              \
      F(CMS_SUS_21_002_OLD)                          \
      F(CMS_SUS_21_002)                              \
      F(CMS_SUS_16_043)                              \
      F(CMS_SUS_20_003)                              \
      F(CMS_SUS_16_051)                              \
      F(CMS_SUS_17_001)                              \
      F(CMS_SUS_16_048)                              \
      F(CMS_SUS_16_048_nocovar)                      \
      F(CMS_SUS_16_048_stop)                         \
      F(CMS_SUS_16_048_stop_nocovar)                 \
      F(CMS_SUS_18_004)                              \
      F(CMS_SUS_18_004_ewino)                        \
      F(CMS_SUS_18_004_stop)                         \
      F(CMS_SUS_16_034_EW)                           \
      F(CMS_SUS_20_001)                              \
      F(CMS_SUS_20_001_strong_production)            \
      F(CMS_SUS_20_001_EW_production)                \
      F(CMS_SUS_20_001_Slepton)                      \
      F(CMS_SUS_16_034_EW_nocovar)                   \
      F(CMS_SUS_16_034)                              \
      F(CMS_SUS_17_010)                              \
      F(CMS_SUS_17_010_stop)                         \
      F(CMS_SUS_17_010_chargino)                     \
      F(CMS_SUS_16_035)                              \
      F(CMS_SUS_16_035_inclusive)                    \
      F(CMS_SUS_16_035_exclusive)                    \
      F(CMS_SUS_19_008)                              \
      F(CMS_SUS_16_046)                              \
      F(CMS_SUS_21_009)                              \
      F(CMS_SUS_17_011)                              \
      F(CMS_SUS_17_012)                              \
      F(CMS_SUS_17_012_emu_combined)                 \
      F(CMS_SUS_16_039)                              \
      F(CMS_SUS_16_039_2SSLep)                       \
      F(CMS_SUS_16_039_3Lep)                         \
      F(CMS_SUS_16_039_Full)                         \
      F(CMS_SUS_16_039_Full_2SSLep)                  \
      F(CMS_SUS_16_039_Full_3Lep)                    \
      F(CMS_SUS_16_039_Full_3Lep_rebinned)           \
      F(CMS_EXO_16_048)                              \
      F(CMS_SUS_19_012)                              \
      F(CMS_SUS_19_012_2Lep)                         \
      F(CMS_SUS_19_012_3Lep)                         \
      F(CMS_SUS_19_012_3LEPTau)                      \
      F(CMS_SUS_19_012_4LEP)                         \
      F(CMS_SUS_19_012_4LEPTau)                      \
      F(CMS_SUS_20_004)                              \
      F(CMS_SUS_19_010)                              \
      F(CMS_B2G_14_004)                              \
      F(CMS_B2G_13_004)                              \
      F(CMS_SUS_13_006)                              \
      F(CMS_SUS_13_006_3Lep)                         \
      F(CMS_SUS_13_006_4Lep)                         \
      F(CMS_EXO_12_048)                              \

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
    #ifndef EXCLUDE_ONNXRUNTIME
      MAP_ANALYSES_WITH_ONNX(DECLARE_ANALYSIS_FACTORY)
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
      #ifndef EXCLUDE_ONNXRUNTIME
        MAP_ANALYSES_WITH_ONNX(IF_X_RTN_CREATE_ANA_X)
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
      #ifndef EXCLUDE_ONNXRUNTIME
        MAP_ANALYSES_WITH_ONNX(IF_X_RTN_DETECTOR)
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
        analyses_map[collider_name][aname]->set_collider_name(collider_name);
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
