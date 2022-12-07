//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions of ColliderBit measurments.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Tomas Gonzalo
///          (tomas.gonzalo@monash.edu)
///  \date   2019
///
///  \author Tomasz Procter
///          (t.procter.1@research.gla.ac.uk)
///  \date   June 2021
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"

#ifndef EXCLUDE_HEPMC
  #include "HepMC3/ReaderAscii.h"
  #include "HepMC3/ReaderAsciiHepMC2.h"
#endif

#ifndef EXCLUDE_YODA
  #include "YODA/AnalysisObject.h"
  #include "YODA/IO.h"
#endif

namespace Gambit
{

  namespace ColliderBit
  {

    //Small convenience function for supplying options to the contur argparser.
    void convert_yaml_options_for_contur(std::vector<std::string> &yaml_options)
    {
      for (size_t i{0}; i <yaml_options.size(); ++i){
        yaml_options[i] = ("--"+yaml_options[i]);
      }
    }

    #ifndef EXCLUDE_HEPMC
      #ifndef EXCLUDE_YODA

        // Analyse HepMC events with Rivet's measurements
        // Collect results in a stream of a YODA file
        void Rivet_measurements(std::shared_ptr<std::ostringstream> &result)
        {
          using namespace Pipes::Rivet_measurements;
          using namespace Rivet_default::Rivet;

          static std::shared_ptr<AnalysisHandler> ah;
          static bool studying_first_event;
          static int events_analysed = 0;

          if (*Loop::iteration == COLLIDER_INIT)
          {
            if (ah != nullptr) {
              ah->~AnalysisHandler();
              ah = nullptr;
            }
            ah = std::make_shared<AnalysisHandler>();
            studying_first_event = true;

            //Are we running in a standalone (i.e. CBS) or in GAMBIT proper
            //This should be added manually
            bool runningStandalone = runOptions->getValueOrDef<bool>(false, "runningStandalone");
            std::vector<std::string> analyses, excluded_analyses;

            if (!runningStandalone){
              YAML::Node colNode = runOptions->getValue<YAML::Node>(Dep::RunMC->current_collider());
              Options colOptions(colNode);
              analyses = colOptions.getValueOrDef<std::vector<str> >(std::vector<str>(), "analyses");
              excluded_analyses = colOptions.getValueOrDef<std::vector<str> >(std::vector<str>(), "exclude_analyses");
            }
            else {
              analyses = runOptions->getValueOrDef<std::vector<str> >(std::vector<str>(), "analyses");
              excluded_analyses = runOptions->getValueOrDef<std::vector<str> >(std::vector<str>(), "exclude_analyses");
            }

            if(not analyses.size())
              ColliderBit_warning().raise(LOCAL_INFO, "No analyses set for Rivet. This means an empty yoda file will be passed to Contur");
            // TODO: Add somewhere a check to make sure we only do LHC analyses
            else{
              for (size_t i = 0; i < analyses.size() ; ++i){
                //If the analysis is a special code referring to multiple analyses,
                //append these to the end of the vector, so they are dealt with
                //later in the loop
                if (analyses[i] == "13TeV" || analyses[i] == "8TeV" || analyses[i] == "7TeV"){
                  BEreq::Contur_GetAnalyses(analyses, analyses[i]);
                }
                //If its a normal analyis just add it.
                else {
                  ah->addAnalysis(analyses[i]);
                }
              }
            }

            //If the yaml file wants to exclude analyses, remove them
            //This feature was inspired by ATLAS_2016_I1469071, which is effectively
            //invalid for most BSM cases and can cause crashes.
            ah->removeAnalyses(excluded_analyses);

            //Write the utilised analyses to a file in yaml-like format
            //This will list only the analyses that RIVET has succesfully loaded.
            //Only do this the first time contur is run.
            //TODO: the analysishandler can choose to autoremove analyses e.g. if the energy is wrong LATER.
            // Should we account for this? E.g. By wiping the file in base_init.
            const static bool output_used_analyses = runOptions->getValueOrDef<bool>(false, "drop_used_analyses");
            if (output_used_analyses){
              static bool analysis_file_opened = false;
              static std::map<std::string, bool> analyses_written_to_file_per_collider;
              if (analyses_written_to_file_per_collider.count(Dep::RunMC->current_collider()) == 0){
                std::ofstream analyses_output_file;
                //TODO please feel free to change name/put in more appropriate location.
                str filename = "/GAMBIT_rivet_analyses.log";
                if (!analysis_file_opened){
                  analyses_output_file.open(GAMBIT_DIR+std::string(filename));
                  analysis_file_opened = true;
                } else {
                  analyses_output_file.open(GAMBIT_DIR+std::string(filename),std::ios_base::app);
                  analyses_output_file << "\n";
                }
                analyses_output_file << Dep::RunMC->current_collider() << ":\n";
                analyses_output_file << "  analyses:";

                for (std::string an_analysis_string : ah->analysisNames()) {
                  analyses_output_file << "\n   - " << an_analysis_string;
                }
                analyses_output_file.close();
                analyses_written_to_file_per_collider[Dep::RunMC->current_collider()] = true;
              }
            }

          }

          if (*Loop::iteration == COLLIDER_FINALIZE)
          {
            //Check if events have actually been generated. If not, don't call finalise, as
            //rivet hasn't been fully initialised. Just return a nullptr, the contur functions
            //will know what to do.
            if (!studying_first_event)
            {
              #ifdef COLLIDERBIT_DEBUG
                std::cout << "Summary data from rivet:\n\tAnalyses used: ";
                for (auto analysis : ah->analysisNames()){
                    std::cout << analysis << ", ";
                }
                std::cout << "\n\tBeam IDs are " << ah->beamIds().first << ", " << ah->beamIds().second;
                std::cout << "\n\tXS: " << ah->nominalCrossSection();
                std::cout << "\n\tRunName: " << ah->runName();
                std::cout << "\n\tSqrtS: " << ah->sqrtS();
                std::cout << "\n\tList of available analyses: ";
                for (auto analysis : ah->stdAnalysisNames()){
                    std::cout << analysis << ", ";
                }
                std::cout << std::flush;
              #endif

              //Initialise somewhere for the yoda file to be outputted.
              //This circuitous route is necesarry because ostringstream does not support copy
              //assignment or copy initialisation, and which is necesarry to access items via
              //Gambit's backends system, so we need to go via a pointer.
              result = std::make_shared<std::ostringstream>();

              #pragma omp critical
              {
                ah->finalize();
                ah->writeData(*result, "yoda");
              }

              // Drop YODA file if requested
              bool drop_YODA_file = runOptions->getValueOrDef<bool>(false, "drop_YODA_file");
              if(drop_YODA_file)
              {
                str filename = "GAMBIT_collider_measurements_"+Dep::RunMC->current_collider()+".yoda";
                #pragma omp critical
                {
                  try{ ah->writeData(filename); }
                  catch (...)
                  { ColliderBit_error().raise(LOCAL_INFO, "Unexpected error in writing YODA file"); }
                }
              }
            }
            else{
              result = nullptr;
            }

            #pragma omp critical
            {
              ah->~AnalysisHandler();
              ah = nullptr;
            }
          }

          // Don't do anything else during special iterations
          if (*Loop::iteration < 0) return;

          if (studying_first_event){
            if (omp_get_thread_num() == 0)
            {
              // Get the HepMC event
              HepMC3::GenEvent ge = *Dep::HardScatteringEvent;
              try { ah->analyze(ge); }
              catch(std::runtime_error &e)
              {
                ColliderBit_error().raise(LOCAL_INFO, e.what());
              }
              studying_first_event = false;
            }
            #pragma omp barrier
            if (omp_get_thread_num() != 0)
            {
              #pragma omp critical
              {
                // Get the HepMC event
                HepMC3::GenEvent ge = *Dep::HardScatteringEvent;
                // Save the old event number in case other bits of Gambit need it.
                int old_events_analysed = ge.event_number();
                // Set the Event number to a stream independent total so Rivet can
                // make sense of things.
                ge.set_event_number(++events_analysed);
                try { ah->analyze(ge); }
                catch(std::runtime_error &e)
                {
                  ColliderBit_error().raise(LOCAL_INFO, e.what());
                }
                // Reset the old event number in case GAMBIT needs it elsewhere.
                ge.set_event_number(old_events_analysed);
              }
            }
          }
          else{
            # pragma omp critical
            {
              // Get the HepMC event
              HepMC3::GenEvent ge = *Dep::HardScatteringEvent;
              // Save the old event number in case other bits of Gambit need it.
              int old_events_analysed = ge.event_number();
              // Set the Event number to a stream independent total so Rivet can
              // make sense of things.
              ge.set_event_number(++events_analysed);
              try { ah->analyze(ge); }
              catch(std::runtime_error &e)
              {
                ColliderBit_error().raise(LOCAL_INFO, e.what());
              }
              // Reset the old event number in case GAMBIT needs it elsewhere.
              ge.set_event_number(old_events_analysed);
            }
          }
        }

      #endif //EXCLUDE_YODA
    #endif // EXCLUDE_HEPMC

    #ifdef HAVE_PYBIND11
      #ifndef EXCLUDE_YODA

        // Contur version, from YODA stream
        void Contur_LHC_measurements_from_stream(Contur_output &result)
        {
          static std::vector<Contur_output> results;

          using namespace Pipes::Contur_LHC_measurements_from_stream;
          if (*Loop::iteration == BASE_INIT)
          {
            results.clear();
          }
          else if (*Loop::iteration == COLLIDER_FINALIZE)
          {
            Contur_output temp_result;
            std::shared_ptr<std::ostringstream> yodastream = *Dep::Rivet_measurements;

            //Check that rivet actually ran. If not, produce an empty Contur_output object.
            if (yodastream == nullptr){
              temp_result = Contur_output();
            }
            //If rivet ran, run Contur.
            else {
              std::vector<std::string> yaml_contur_options = runOptions->getValueOrDef<std::vector<str>>(std::vector<str>(), "contur_options");
              convert_yaml_options_for_contur(yaml_contur_options);

              #pragma omp critical
              {
                ///Call contur
                temp_result = BEreq::Contur_Measurements(std::move(yodastream), yaml_contur_options);
              }
            }
            results.push_back(temp_result);

            #ifdef COLLIDERBIT_DEBUG
              std::cout << "\n\nSINGLE COLLIDER CCONTUR OBTAINED: ";
              temp_result.print_Contur_output_debug();
            #endif
          }
          else if (*Loop::iteration == BASE_FINALIZE){
            if(results.size() == 0){
              result = Contur_output();
            }
            else {
              result = results[0];
              for(size_t i = 1; i < results.size(); ++i){
                result = Gambit::merge_contur_outputs(result, results[i]);
              }
            }
            #ifdef COLLIDERBIT_DEBUG
              std::cout << "\n\nFINAL RESULT CONTUR OBTAINED: ";
              result.print_Contur_output_debug();
            #endif
          }
        }

        void Multi_Contur_LHC_measurements_from_stream(Multi_Contur_output &result)
        {

          using namespace Pipes::Multi_Contur_LHC_measurements_from_stream;
          static std::vector<Multi_Contur_output> results;

          if (*Loop::iteration == BASE_INIT)
          {
            results.clear();
          }
          else if (*Loop::iteration == COLLIDER_FINALIZE)
          {
            Multi_Contur_output temp_result;
            std::shared_ptr<std::ostringstream> yodastream = *Dep::Rivet_measurements;

            //Get the names of the contur instances we want to run.
            static const std::vector<string> contur_names = runOptions->getValueOrDef<std::vector<std::string>>({"Contur"}, "Contur_names");

            //Check that rivet actually ran. If not, produce an empty Contur_output object.
            bool Rivet_ran;
            if (yodastream == nullptr){
              Rivet_ran = false;
            } else Rivet_ran = true;

            //Now we need to loop over the different Contur settings:



            for (std::string contur_instance : contur_names){
              std::shared_ptr<std::ostringstream> yodastreamcopy = yodastream;
              if (Rivet_ran){
                std::vector<std::string> yaml_contur_options = runOptions->getValueOrDef<std::vector<str>>(std::vector<str>(), contur_instance);
                convert_yaml_options_for_contur(yaml_contur_options);
                #pragma omp critical
                {
                  ///Call contur
                  temp_result[contur_instance] = BEreq::Contur_Measurements(std::move(yodastreamcopy), yaml_contur_options);
                }
              } else {
                //Case rivet failed to run:
                temp_result[contur_instance] = Contur_output();
              }
            }

            results.push_back(temp_result);

            #ifdef COLLIDERBIT_DEBUG
              std::cout << "\n\nSINGLE COLLIDER CONTUR OBTAINED: ";
              print_Multi_Contur_output_debug(temp_result);
            #endif
          }
          else if (*Loop::iteration == BASE_FINALIZE){
            if(results.size() == 0){
              result = Multi_Contur_output{};
            }
            else {
              result = results[0];
              for(size_t i = 1; i < results.size(); ++i){
                result = Gambit::merge_multi_contur_outputs(result, results[i]);
              }
            }
            #ifdef COLLIDERBIT_DEBUG
              std::cout << "\n\nFINAL RESULT CONTUR OBTAINED: ";
              print_Multi_Contur_output_debug(result);
            #endif
          }
        }

        // Contur version, from YODA file
        void Contur_LHC_measurements_from_file(Contur_output &result)
        {
          using namespace Pipes::Contur_LHC_measurements_from_file;

          // This function only works if there is a file
          str YODA_filename = runOptions->getValueOrDef<str>("", "YODA_filename");

          if (YODA_filename == "" or not Utils::file_exists(YODA_filename))
            ColliderBit_error().raise(LOCAL_INFO, "YODA file "+YODA_filename+" not found.");

          std::vector<std::string> yaml_contur_options = runOptions->getValueOrDef<std::vector<str>>(std::vector<str>(), "contur_options");
          convert_yaml_options_for_contur(yaml_contur_options);

          #pragma omp critical
          {
            // Call Contur
            result = BEreq::Contur_Measurements(YODA_filename, yaml_contur_options);
          }
        }

        // Extracts the Likelihood from a Contur_output object
        void Contur_LHC_measurements_LogLike(double &result)
        {
          using namespace Pipes::Contur_LHC_measurements_LogLike;
          Contur_output contur_likelihood_object = *Dep::LHC_measurements;
          result = contur_likelihood_object.LLR;
        }

        // Extracts a single likelihood from a map<string, Contur_output> based on options
        // This is the likelihood that will actually be "used" by gambit
        void Multi_Contur_LHC_measurements_LogLike_all(map_str_dbl &result)
        {
          using namespace Pipes::Multi_Contur_LHC_measurements_LogLike_all;
          Multi_Contur_output contur_likelihood_object = *Dep::LHC_measurements;

          for (auto Contur_name : contur_likelihood_object){
            result[Contur_name.first + "_LLR"] = Contur_name.second.LLR;
          }
        }

        //Extracts the likelihood value for every set of contur settings from a map<string, Contur_output>
        void Multi_Contur_LHC_measurements_LogLike_single(double &result)
        {
          using namespace Pipes::Multi_Contur_LHC_measurements_LogLike_single;
          Multi_Contur_output contur_likelihood_object = *Dep::LHC_measurements;
          static const std::string which_as_LLR = runOptions->getValueOrDef<str>("Contur", "Use_as_likelihood");
          result = contur_likelihood_object[which_as_LLR].LLR;
        }

        // Extracts the likelihood contribution from each contur pool from Contur_output
        void Contur_LHC_measurements_LogLike_perPool(map_str_dbl &result)
        {
          using namespace Pipes::Contur_LHC_measurements_LogLike_perPool;
          std::stringstream summary_line;
          summary_line << "LHC Contur LogLikes per pool: ";
          result = (*Dep::LHC_measurements).pool_LLR;

          for( auto const& entry : result){
            summary_line << entry.first << ":" << entry.second << ", ";
          }
          logger() << LogTags::debug << summary_line.str() << EOM;
        }

        // Extracts the likelihood contribution from each contur pool in each run of contur from Map<string, Contur_output>
        void Multi_Contur_LHC_measurements_LogLike_perPool(map_str_dbl &result)
        {
          result.clear();
          using namespace Pipes::Multi_Contur_LHC_measurements_LogLike_perPool;
          std::stringstream summary_line;
          summary_line << "LHC Contur LogLikes per pool: ";
          Multi_Contur_output contur_likelihood_object = *Dep::LHC_measurements;
          for (const auto& contur_output_instance : contur_likelihood_object){
            for (auto const& pool_LLR_entry : contur_output_instance.second.pool_LLR){
              result[pool_LLR_entry.first + "_" + contur_output_instance.first] = pool_LLR_entry.second;
            }
          }
          for( auto const& entry : result){
            summary_line << entry.first << ":" << entry.second << ", ";
          }
          logger() << LogTags::debug << summary_line.str() << EOM;
        }

        // Debug only: Get the dominant bin/histogram/correlated set thereof for each Contur pool
        // Note map_str_str will not print to hdf5! Use for ASCII debug only.
        void Contur_LHC_measurements_histotags_perPool(map_str_str &result)
        {
          using namespace Pipes::Contur_LHC_measurements_LogLike_perPool;
          std::stringstream summary_line;
          summary_line << "LHC Contur LogLikes per pool: ";
          result = (*Dep::LHC_measurements).pool_tags;

          for( auto const& entry : result){
            summary_line << entry.first << ":" << entry.second << ", ";
          }

          logger() << LogTags::debug << summary_line.str() << EOM;
        }

        // Debug only: Get the dominant bin/histogram/correlated set thereof for each Contur pool in each contur run
        // Note map_str_str will not print to hdf5! Use for ASCII debug only.
        void Multi_Contur_LHC_measurements_histotags_perPool(map_str_str &result)
        {
          result.clear();
          using namespace Pipes::Multi_Contur_LHC_measurements_LogLike_perPool;
          std::stringstream summary_line;
          summary_line << "LHC Contur LogLikes per pool: ";

          Multi_Contur_output contur_likelihood_object = *Dep::LHC_measurements;
          for (const auto& contur_output_instance : contur_likelihood_object){
            for (auto const& pool_LLR_entry : contur_output_instance.second.pool_tags){
              result[pool_LLR_entry.first + "_" + contur_output_instance.first] = pool_LLR_entry.second;
            }
          }
          for( auto const& entry : result){
            summary_line << entry.first << ":" << entry.second << ", ";
          }
          logger() << LogTags::debug << summary_line.str() << EOM;
        }

      #endif //EXCLUDE_YODA
    #endif // HAVE_PYBIND11

  }  // namespace ColliderBit
}  // namespace Gambit
