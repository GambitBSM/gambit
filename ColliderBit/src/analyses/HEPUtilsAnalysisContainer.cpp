#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/ColliderBit/ColliderBit_macros.hpp"
#include "gambit/ColliderBit/analyses/HEPUtilsAnalysisContainer.hpp"
#include "gambit/ColliderBit/analyses/BaseAnalysis.hpp"
#include <stdexcept>
#include <omp.h>
using namespace std;

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
    
    #define MAP_ANALYSES(F)             \
      F(Minimum)                                     \
      F(Covariance)                                  \
      F(Perf)                                        \
      F(ATLAS_13TeV_0LEP_13invfb)                    \
      F(ATLAS_13TeV_0LEP_36invfb)                    \
      F(ATLAS_13TeV_0LEPStop_36invfb)                \
      F(ATLAS_13TeV_2LEPStop_36invfb)                \
      F(ATLAS_13TeV_MultiLEP_confnote_36invfb)       \
      F(ATLAS_13TeV_MultiLEP_36invfb)                \
      F(ATLAS_13TeV_MultiLEP_2Lep0Jets_36invfb)      \
      F(ATLAS_13TeV_MultiLEP_2LepPlusJets_36invfb)   \
      F(ATLAS_13TeV_MultiLEP_3Lep_36invfb)           \
      F(ATLAS_13TeV_4LEP_36invfb)                    \
      F(ATLAS_13TeV_2bMET_36invfb)                   \
      F(ATLAS_13TeV_3b_24invfb)                      \
      F(ATLAS_13TeV_3b_discoverySR_24invfb)          \
      F(ATLAS_13TeV_3b_36invfb)                      \
      F(ATLAS_13TeV_3b_discoverySR_36invfb)          \
      /* F(ATLAS_13TeV_PhotonGGM_36invfb) */         \
      /* F(ATLAS_13TeV_ZGammaGrav_CONFNOTE_80invfb) */  \
      F(ATLAS_8TeV_0LEP_20invfb)                     \
      F(ATLAS_8TeV_0LEPStop_20invfb)                 \
      F(ATLAS_8TeV_1LEPStop_20invfb)                 \
      F(ATLAS_8TeV_2bStop_20invfb)                   \
      F(ATLAS_8TeV_2LEPEW_20invfb)                   \
      F(ATLAS_8TeV_2LEPStop_20invfb)                 \
      F(ATLAS_8TeV_3LEPEW_20invfb)                   \
      F(ATLAS_8TeV_1LEPbb_20invfb)                   \
      F(CMS_13TeV_0LEP_13invfb)                      \
      F(CMS_13TeV_0LEP_36invfb)                      \
      F(CMS_13TeV_1LEPbb_36invfb)                    \
      F(CMS_13TeV_1LEPStop_36invfb)                  \
      F(CMS_13TeV_2LEPStop_36invfb)                  \
      F(CMS_13TeV_2LEPsoft_36invfb)                  \
      F(CMS_13TeV_2LEPsoft_36invfb_nocovar)          \
      F(CMS_13TeV_2OSLEP_36invfb)                    \
      F(CMS_13TeV_2OSLEP_36invfb_nocovar)            \
      F(CMS_13TeV_2OSLEP_confnote_36invfb)           \
      F(CMS_13TeV_2OSLEP_chargino_stop_36invfb)      \
      F(CMS_13TeV_2OSLEP_for_stop_36invfb)           \
      F(CMS_13TeV_2OSLEP_for_chargino_36invfb)       \
      F(CMS_13TeV_MultiLEP_36invfb)                  \
      F(CMS_13TeV_MultiLEP_2SSLep_36invfb)           \
      F(CMS_13TeV_MultiLEP_3Lep_36invfb)             \
      F(CMS_13TeV_MultiLEP_Full_36invfb)             \
      F(CMS_13TeV_MultiLEP_Full_2SSLep_36invfb)      \
      F(CMS_13TeV_MultiLEP_Full_3Lep_36invfb)        \
      F(CMS_13TeV_MONOJET_36invfb)                   \
      F(CMS_8TeV_1LEPDMTOP_20invfb)                  \
      F(CMS_8TeV_2LEPDMTOP_20invfb)                  \
      F(CMS_8TeV_3LEPEW_20invfb)                     \
      F(CMS_8TeV_MONOJET_20invfb)                    \



    /// Forward declarations using #DECLARE_ANALYSIS_FACTORY(ANAME)
    #ifndef EXCLUDE_ROOT
      #ifndef EXCLUDE_RESTFRAMES
        MAP_ANALYSES_WITH_ROOT_RESTFRAMES(DECLARE_ANALYSIS_FACTORY)
      #endif
      MAP_ANALYSES_WITH_ROOT(DECLARE_ANALYSIS_FACTORY)
    #endif
    MAP_ANALYSES(DECLARE_ANALYSIS_FACTORY)

    // Factory definition
    HEPUtilsAnalysis* mkAnalysis(const std::string& name)
    {
      #ifndef EXCLUDE_ROOT
        #ifndef EXCLUDE_RESTFRAMES
          MAP_ANALYSES_WITH_ROOT_RESTFRAMES(IF_X_RTN_CREATE_ANA_X)
        #endif
        MAP_ANALYSES_WITH_ROOT(IF_X_RTN_CREATE_ANA_X)
      #endif
      MAP_ANALYSES(IF_X_RTN_CREATE_ANA_X)

      throw std::runtime_error("The analysis " + name + " is not a known ColliderBit analysis.");
      return nullptr;
    }

    /// Check that an analysis exists for a given analysis name
    bool checkAnalysis(const string& name)
    {
      #ifndef EXCLUDE_ROOT
        #ifndef EXCLUDE_RESTFRAMES
          MAP_ANALYSES_WITH_ROOT_RESTFRAMES(IF_X_RTN_TRUE)
        #endif
        MAP_ANALYSES_WITH_ROOT(IF_X_RTN_TRUE)
      #endif
      MAP_ANALYSES(IF_X_RTN_TRUE)

      // If we end up here the analysis has not been found
      return false;
    }


    /// A map with pointers to all instances of this class. The key is the thread number.
    std::map<string,std::map<int,HEPUtilsAnalysisContainer*> > HEPUtilsAnalysisContainer::instances_map;

    /// Constructor
    HEPUtilsAnalysisContainer::HEPUtilsAnalysisContainer() :
      current_collider(""),
      ready(false),
      is_registered(false),
      n_threads(omp_get_max_threads()),
      base_key("")
    {
      #ifdef ANALYSISCONTAINER_DEBUG
        std::cout << "DEBUG: thread " << omp_get_thread_num() << ": HEPUtilsAnalysisContainer::ctor: created at " << this << std::endl;
      #endif
    }


    /// Destructor
    HEPUtilsAnalysisContainer::~HEPUtilsAnalysisContainer()
    {
      clear();
    }


    /// Add container to instances map
    void HEPUtilsAnalysisContainer::register_thread(string base_key_in)
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
            std::cout << "DEBUG: thread " << omp_get_thread_num() << ": HEPUtilsAnalysisContainer::register_thread: added " << this << " to instances_map with key " << base_key << "-" << omp_get_thread_num() << std::endl;
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
              std::cout << "DEBUG: thread " << omp_get_thread_num() << ": HEPUtilsAnalysisContainer::register_thread: this instance is already in instances_map" << std::endl;
            #endif
          }
        }
      }
    }


    /// Delete and clear the analyses contained within this instance.
    void HEPUtilsAnalysisContainer::clear()
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
      ready = false;
    }


    /// Set name of the current collider
    void HEPUtilsAnalysisContainer::set_current_collider(string collider_name)
    {
      current_collider = collider_name;
    }


    /// Get the name of the current collider
    string HEPUtilsAnalysisContainer::get_current_collider() const
    {
      return current_collider;
    }


    /// Does this instance contain analyses for the given collider
    bool HEPUtilsAnalysisContainer::has_analyses(string collider_name) const
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
    bool HEPUtilsAnalysisContainer::has_analyses() const
    {
      return has_analyses(current_collider);
    }


    /// Initialize analyses (by names) for a specified collider
    void HEPUtilsAnalysisContainer::init(const std::vector<std::string>& analysis_names, string collider_name)
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

      // This instance is now ready
      ready = true;
    }

    /// Initialize analyses (by names) for the current collider
    void HEPUtilsAnalysisContainer::init(const std::vector<std::string>& analysis_names)
    {
      init(analysis_names, current_collider);
    }


    /// Reset specific analysis
    void HEPUtilsAnalysisContainer::reset(string collider_name, string analysis_name)
    {
      analyses_map[collider_name][analysis_name]->reset();
    }

    /// Reset all analyses for given collider
    void HEPUtilsAnalysisContainer::reset(string collider_name)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        analysis_pointer_pair.second->reset();
      }
    }

    /// Reset all analyses for the current collider
    void HEPUtilsAnalysisContainer::reset()
    {
      reset(current_collider);
    }

    /// Reset all analyses for all colliders
    void HEPUtilsAnalysisContainer::reset_all()
    {
      for(auto& collider_map_pair : analyses_map)
      {
        reset(collider_map_pair.first);
      }
    }


    /// Get pointer to specific analysis
    const HEPUtilsAnalysis* HEPUtilsAnalysisContainer::get_analysis_pointer(string collider_name, string analysis_name) const
    {
      return analyses_map.at(collider_name).at(analysis_name);
    }

    /// Get analyses map for a specific collider
    const std::map<string,HEPUtilsAnalysis*>& HEPUtilsAnalysisContainer::get_collider_analyses_map(string collider_name) const
    {
      return analyses_map.at(collider_name);
    }

    /// Get analyses map for the current collider
    const std::map<string,HEPUtilsAnalysis*>& HEPUtilsAnalysisContainer::get_current_analyses_map() const
    {
      return analyses_map.at(current_collider);
    }

    /// Get the full analyses map
    const std::map<string,std::map<string,HEPUtilsAnalysis*> >& HEPUtilsAnalysisContainer::get_full_analyses_map() const
    {
      return analyses_map;
    }


    /// Pass event through specific analysis
    void HEPUtilsAnalysisContainer::analyze(const HEPUtils::Event& event, string collider_name, string analysis_name) const
    {
      analyses_map.at(collider_name).at(analysis_name)->do_analysis(event);
    }

    /// Pass event through all analysis for a specific collider
    void HEPUtilsAnalysisContainer::analyze(const HEPUtils::Event& event, string collider_name) const
    {
      for (auto& analysis_pointer_pair : analyses_map.at(collider_name))
      {
        analysis_pointer_pair.second->do_analysis(event);
      }
    }

    /// Pass event through all analysis for the current collider
    void HEPUtilsAnalysisContainer::analyze(const HEPUtils::Event& event) const
    {
      analyze(event, current_collider);
    }


    /// Add cross-sections and errors for two different processes,
    /// for specific analysis
    void HEPUtilsAnalysisContainer::add_xsec(double xs, double xserr, string collider_name, string analysis_name)
    {
      analyses_map[collider_name][analysis_name]->add_xsec(xs, xserr);
    }

    /// Add cross-sections and errors for two different processes,
    /// for all analyses for a given collider
    void HEPUtilsAnalysisContainer::add_xsec(double xs, double xserr, string collider_name)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        analysis_pointer_pair.second->add_xsec(xs, xserr);
      }
    }

    /// Add cross-sections and errors for two different processes,
    /// for all analyses for the current collider
    void HEPUtilsAnalysisContainer::add_xsec(double xs, double xserr)
    {
      add_xsec(xs, xserr, current_collider);
    }


    /// Weighted combination of cross-sections and errors for the same process,
    /// for a specific analysis
    void HEPUtilsAnalysisContainer::improve_xsec(double xs, double xserr, string collider_name, string analysis_name)
    {
      analyses_map[collider_name][analysis_name]->improve_xsec(xs, xserr);
    }

    /// Weighted combination of cross-sections and errors for the same process,
    /// for all analyses for a given collider
    void HEPUtilsAnalysisContainer::improve_xsec(double xs, double xserr, string collider_name)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        analysis_pointer_pair.second->improve_xsec(xs, xserr);
      }
    }

    /// Weighted combination of cross-sections and errors for the same process,
    /// for all analyses for the current collider
    void HEPUtilsAnalysisContainer::improve_xsec(double xs, double xserr)
    {
      improve_xsec(xs, xserr, current_collider);
    }


    //
    // @todo Add the 'collect_and_add_signal' functions
    //

    /// Collect signal predictions from other threads and add to this one,
    /// for specific analysis
    void HEPUtilsAnalysisContainer::collect_and_add_signal(string collider_name, string analysis_name)
    {
      for (auto& thread_container_pair : instances_map.at(base_key))
      {
        if (thread_container_pair.first == omp_get_thread_num()) continue;

        HEPUtilsAnalysisContainer* other_container = thread_container_pair.second;
        // HEPUtilsAnalysis* other_analysis = other_container->get_analysis_pointer(collider_name, analysis_name);
        HEPUtilsAnalysis* other_analysis = other_container->analyses_map[collider_name][analysis_name];

        analyses_map[collider_name][analysis_name]->add(other_analysis);
      }
    }

    /// Collect signal predictions from other threads and add to this one,
    /// for all analyses for given collider
    void HEPUtilsAnalysisContainer::collect_and_add_signal(string collider_name)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        string analysis_name = analysis_pointer_pair.first;
        collect_and_add_signal(collider_name, analysis_name);
      }
    }

    /// Collect signal predictions from other threads and add to this one,
    /// for all analyses for the current collider
    void HEPUtilsAnalysisContainer::collect_and_add_signal()
    {
      collect_and_add_signal(current_collider);
    }


    /// Collect xsec predictions from other threads and do a weighted combination,
    /// for specific analysis
    void HEPUtilsAnalysisContainer::collect_and_improve_xsec(string collider_name, string analysis_name)
    {
      for (auto& thread_container_pair : instances_map.at(base_key))
      {
        if (thread_container_pair.first == omp_get_thread_num()) continue;

        HEPUtilsAnalysisContainer* other_container = thread_container_pair.second;
        const HEPUtilsAnalysis* other_analysis = other_container->get_analysis_pointer(collider_name, analysis_name);

        double other_xsec = other_analysis->xsec();
        double other_xsec_err = other_analysis->xsec_err();

        improve_xsec(other_xsec, other_xsec_err, collider_name, analysis_name);
      }
    }

    /// Collect xsec predictions from other threads and do a weighted combination,
    /// for all analyses for given collider
    void HEPUtilsAnalysisContainer::collect_and_improve_xsec(string collider_name)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        string analysis_name = analysis_pointer_pair.first;
        collect_and_improve_xsec(collider_name, analysis_name);
      }
    }

    /// Collect xsec predictions from other threads and do a weighted combination,
    /// for all analyses for the current collider
    void HEPUtilsAnalysisContainer::collect_and_improve_xsec()
    {
      collect_and_improve_xsec(current_collider);
    }


    /// Scale results for specific analysis
    void HEPUtilsAnalysisContainer::scale(string collider_name, string analysis_name, double factor)
    {
      analyses_map[collider_name][analysis_name]->scale(factor);
    }

    /// Scale results for all analyses for given collider
    void HEPUtilsAnalysisContainer::scale(string collider_name, double factor)
    {
      for (auto& analysis_pointer_pair : analyses_map[collider_name])
      {
        string analysis_name = analysis_pointer_pair.first;
        scale(collider_name, analysis_name, factor);
      }
    }

    /// Scale results for all analyses for the current collider
    void HEPUtilsAnalysisContainer::scale(double factor)
    {
      scale(current_collider, factor);
    }

    /// Scale results for all analyses across all colliders
    void HEPUtilsAnalysisContainer::scale_all(double factor)
    {
      for (auto& collider_map_pair : analyses_map)
      {
        string collider_name = collider_map_pair.first;
        scale(collider_name, factor);
      }
    }

  }
}
