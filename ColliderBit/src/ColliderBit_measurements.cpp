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
///  \date   May 2023
///  \date   Oct 2024
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"

#ifndef EXCLUDE_HEPMC
  #include "gambit/Utils/begin_ignore_warnings_hepmc.hpp"
  #include "HepMC3/ReaderAscii.h"
  #include "HepMC3/ReaderAsciiHepMC2.h"
  #include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#ifndef EXCLUDE_YODA
  #include "gambit/Utils/begin_ignore_warnings_yoda.hpp"
  #include "YODA/AnalysisObject.h"
  #include "YODA/IO.h"
  #include "gambit/Utils/end_ignore_warnings.hpp"
#endif

namespace Gambit
{

  namespace ColliderBit
  {

    //Small convenience function for supplying options to the contur argparser.
    void convert_yaml_options_for_contur(std::vector<std::string> &yaml_options)
    {
      for (size_t i{0}; i <yaml_options.size(); ++i)
      {
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

          static std::vector<std::unique_ptr<AnalysisHandler>> anahandlers;
          // TODO: Does event count ever go over int_max? Playing safe
          thread_local long int events_analysed = 0;
          static std::map<int, long int> events_analysed_perthread;

          static std::vector<string>  analyses;
          static std::vector<string> excluded_analyses;

          if (*Loop::iteration == COLLIDER_INIT)
          {
            // Wipe out all analysisHandlers (will be reinitialised in COLLIDER_INIT_OMP)
            anahandlers.clear();

            // Remainder of Loop iteration is to get analysis list.
            analyses.clear();
            excluded_analyses.clear();

            //Are we running in a standalone (i.e. CBS) or in GAMBIT proper
            //This should be added manually by the standalone
            const static bool runningStandalone = runOptions->getValueOrDef<bool>(false, "runningStandalone");

            if (!runningStandalone)
            {
              YAML::Node colNode = runOptions->getValue<YAML::Node>(Dep::RunMC->current_collider());
              Options colOptions(colNode);
              analyses = colOptions.getValueOrDef<std::vector<str> >(std::vector<str>(), "analyses");
              excluded_analyses = colOptions.getValueOrDef<std::vector<str> >(std::vector<str>(), "exclude_analyses");
            }
            else
            {
              analyses = runOptions->getValueOrDef<std::vector<str> >(std::vector<str>(), "analyses");
              excluded_analyses = runOptions->getValueOrDef<std::vector<str> >(std::vector<str>(), "exclude_analyses");
            }

            if(not analyses.size())
              ColliderBit_warning().raise(LOCAL_INFO, "No analyses set for Rivet. This means an empty yoda file will be passed to Contur");
            else
            {
              for (size_t i = 0; i < analyses.size() ; ++i)
              {
                //If the analysis is a special code referring to multiple analyses,
                //append these to the end of the vector, so they are dealt with
                //later in the loop
                if (analyses[i] == "13TeV" || analyses[i] == "8TeV" || analyses[i] == "7TeV")
                {
                  BEreq::Contur_GetAnalyses(analyses, analyses[i]);
                }
              }
            }
            // Now we have a final list of all analyses to add/exclude 
          }


          if (*Loop::iteration == COLLIDER_INIT_OMP){
            
            #pragma omp critical
            {
              anahandlers.emplace_back(std::make_unique<AnalysisHandler>());
              events_analysed_perthread[omp_get_thread_num()] = 0L;
              
              for (const std::string& ananame :  analyses){
                // Rememeber analysis list already formed.
                if (!(ananame == "13TeV" || ananame == "8TeV" || ananame == "7TeV"))
                  anahandlers.back()->addAnalysis(ananame);
              }
 
              //If the yaml file wants to exclude analyses, remove them
              //This feature was inspired by ATLAS_2016_I1469071, which is effectively
              //invalid for most BSM cases and can cause crashes.
              anahandlers.back()->removeAnalyses(excluded_analyses);

              //Write the utilised analyses to a file in yaml-like format
              //This will list only the analyses that RIVET has succesfully loaded.
              //Only do this the first time contur is run.
              if (omp_get_thread_num() == 0){
                const static bool output_used_analyses = runOptions->getValueOrDef<bool>(false, "drop_used_analyses");
                if (output_used_analyses)
                {
                  static bool analysis_file_opened = false;
                  static std::map<std::string, bool> analyses_written_to_file_per_collider;
                  if (analyses_written_to_file_per_collider.count(Dep::RunMC->current_collider()) == 0)
                  {
                    std::ofstream analyses_output_file;
                    //TODO please feel free to change name/put in more appropriate location.
                    str filename = "/GAMBIT_rivet_analyses.log";
                    if (!analysis_file_opened)
                    {
                      analyses_output_file.open(GAMBIT_DIR+std::string(filename));
                      analysis_file_opened = true;
                    }
                    else
                    {
                      analyses_output_file.open(GAMBIT_DIR+std::string(filename),std::ios_base::app);
                      analyses_output_file << "\n";
                    }
                    analyses_output_file << Dep::RunMC->current_collider() << ":\n";
                    analyses_output_file << "  analyses:";

                    // TODO: fix.
                    for (std::string an_analysis_string : anahandlers[0]->analysisNames())
                    {
                      analyses_output_file << "\n   - " << an_analysis_string;
                    }
                    analyses_output_file.close();
                    analyses_written_to_file_per_collider[Dep::RunMC->current_collider()] = true;
                  }
                }
              }
            }
          }

          // TODO: think about this whole event number check is still needed.
          if (*Loop::iteration == END_SUBPROCESS){
            //Save which threads have run enough events.
            events_analysed_perthread[omp_get_thread_num()] = events_analysed;
            #ifdef COLLIDERBIT_DEBUG
              std::cout << "Rivet: thread " << omp_get_thread_num() << " analysed " << events_analysed << " events" << std::endl;
            #endif
          }

          // TODO: consider cleaning up.
          if (*Loop::iteration == COLLIDER_FINALIZE)
          {
            //Check if events have actually been generated. If not, don't call finalise, as
            //rivet hasn't been fully initialised. Just return a nullptr, the contur functions
            //will know what to do.
            // Test if thread 0 analysed any events. If not, very unlikely any threads did and merging won't work properly - skip.
            if (events_analysed > 0)
            {
              #ifdef COLLIDERBIT_DEBUG
                std::cout << "Summary data from rivet:\n\tAnalyses used: ";
                for (auto analysis : anahandlers[0]->analysisNames()){
                    std::cout << analysis << ", ";
                }
                std::cout << "\n\tBeam IDs are " << anahandlers[0]->beamIds().first << ", " << anahandlers[0]->beamIds().second;
                std::cout << "\n\tXS: " << anahandlers[0]->nominalCrossSection();
                std::cout << "\n\tRunName: " << anahandlers[0]->runName();
                std::cout << "\n\tSqrtS: " << anahandlers[0]->sqrtS();
                std::cout << "\n\tList of available analyses: ";
                for (auto analysis : anahandlers[0]->stdAnalysisNames()){
                    std::cout << analysis << ", ";
                }
                std::cout << std::flush;
              #endif

              //Initialise somewhere for the yoda file to be outputted.
              //This circuitous route is necesarry because ostringstream does not support copy 
              //assignment or copy initialisation, and which is necesarry to access items via 
              //Gambit's backends system, so we need to go via a pointer. 
              result = std::make_shared<std::ostringstream>();
              const static bool drop_perthread_YODA_file = runOptions->getValueOrDef<bool>(false, "drop_perthread_YODA_file");
              int count = 0;
              for (const auto & handler : anahandlers){
                handler->finalize();
                if (drop_perthread_YODA_file){
                  handler->writeData("TEST_"+std::to_string(count++)+".yoda");
                }
              }

              //Merge non-master threads back into master IF they analysed any events.
              for (size_t j = 1; j < anahandlers.size(); ++j){
                //Note rivet needs uses the first event for init so need more than one to
                // actually do analysis.
                if (events_analysed_perthread[j] > 1){
                  #ifdef COLLIDERBIT_DEBUG
                  std::cout << "Merging yoda from thread " << j << " into master." << std::endl;
                  #endif
                  anahandlers[0]->merge(*anahandlers[j]);
                }
                else {
                  std::cout << "Not merging yoda from thread " << j << " into master." << std::endl;
                  ColliderBit_warning().raise(LOCAL_INFO, "Thread "+std::to_string(j)+" did not get any events to Rivet analyse" );
                }
              }
              anahandlers[0]->finalize();
              anahandlers[0]->writeData(*result, "yoda");

              // Drop YODA file if requested
              const static bool drop_YODA_file = runOptions->getValueOrDef<bool>(false, "drop_YODA_file");
              if(drop_YODA_file)
              {
                str filename = "GAMBIT_collider_measurements_"+Dep::RunMC->current_collider()+".yoda";     
                #pragma omp critical
                {
                  try{ anahandlers[0]->writeData(filename); }
                  catch (...)
                  { ColliderBit_error().raise(LOCAL_INFO, "Unexpected error in writing YODA file"); }
                }
              }
            }
            else{
              result = nullptr;
              ColliderBit_warning().raise(LOCAL_INFO, "Rivet didn't analyse any events at this point.");
            }

            anahandlers.clear();
          }

          // Don't do anything else during special iterations
          if (*Loop::iteration < 0) return;

          // Get the HepMC event
          HepMC3::GenEvent ge = *Dep::HardScatteringEvent;
          try {
            // The first event only must be analysed single-threaded
            if (events_analysed < 1){
              #pragma omp critical
              {
                anahandlers[omp_get_thread_num()]->analyze(ge); 
              }
            }
            else {
              anahandlers[omp_get_thread_num()]->analyze(ge); 
            }
            events_analysed++;
          }
          catch(std::runtime_error &e)
          {
            ColliderBit_error().raise(LOCAL_INFO, e.what());
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
            if (yodastream == nullptr)
            {
              temp_result = Contur_output();
            }
            //If rivet ran, run Contur.
            else
            {
              std::vector<std::string> yaml_contur_options = runOptions->getValueOrDef<std::vector<str>>(std::vector<str>(), "contur_options");
              convert_yaml_options_for_contur(yaml_contur_options);

              #pragma omp critical
              {
                ///Call contur
                Contur_output altOut = BEreq::Contur_Measurements(std::move(yodastream), yaml_contur_options);
                temp_result = altOut;
              }
            }
            results.push_back(temp_result);

            #ifdef COLLIDERBIT_DEBUG
              temp_result.print_Contur_output_debug();
            #endif
          }
          else if (*Loop::iteration == BASE_FINALIZE)
          {
            if(results.size() == 0)
            {
              result = Contur_output();
            }
            else
            {
              result = results[0];
              for(size_t i = 1; i < results.size(); ++i)
              {
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
            if (yodastream == nullptr)
            {
              Rivet_ran = false;
            } else Rivet_ran = true;

            //Now we need to loop over the different Contur settings:



            for (std::string contur_instance : contur_names)
            {
              std::shared_ptr<std::ostringstream> yodastreamcopy = yodastream;
              if (Rivet_ran)
              {
                std::vector<std::string> yaml_contur_options = runOptions->getValueOrDef<std::vector<str>>(std::vector<str>(), contur_instance);
                convert_yaml_options_for_contur(yaml_contur_options);
                #pragma omp critical
                {
                  ///Call contur
                  temp_result[contur_instance] = BEreq::Contur_Measurements(std::move(yodastreamcopy), yaml_contur_options);
                }
              }
              else
              {
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
          else if (*Loop::iteration == BASE_FINALIZE)
          {
            if(results.size() == 0)
            {
              result = Multi_Contur_output{};
            }
            else
            {
              result = results[0];
              for(size_t i = 1; i < results.size(); ++i)
              {
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
          //Which background type to use in the calculation.
          const static string background_type = runOptions->getValueOrDef<str>("DATABG", "background");
          if (background_type != "DATABG" && background_type != "SMBG" && background_type != "EXP"){
            ColliderBit_error().raise(LOCAL_INFO, "Requested Contur Background type does not exist");
          }
          Contur_output contur_likelihood_object = *Dep::LHC_measurements;
          result = contur_likelihood_object.outputs.at(background_type).LLR;
        }

        // Extracts the likelihood value for every set of contur settings from a map<string, Contur_output>
        // This is the likelihood that will actually be "used" by gambit
        void Multi_Contur_LHC_measurements_LogLike_all(map_str_dbl &result)
        {
          using namespace Pipes::Multi_Contur_LHC_measurements_LogLike_all;
          Multi_Contur_output contur_likelihood_object = *Dep::LHC_measurements;

          for (auto Contur_name : contur_likelihood_object)
          {
            for (const str & bkg : Contur_name.second._bkg_types){
              result[Contur_name.first + "_" + bkg + "_LLR"] = Contur_name.second.outputs.at(bkg).LLR;
            }
          }
        }

        // Extracts a single likelihood from a map<string, Contur_output> based on options
        void Multi_Contur_LHC_measurements_LogLike_single(double &result)
        {
          using namespace Pipes::Multi_Contur_LHC_measurements_LogLike_single;
          Multi_Contur_output contur_likelihood_object = *Dep::LHC_measurements;
          static const std::string which_as_LLR = runOptions->getValueOrDef<str>("Contur", "Use_as_likelihood");
          static const string background_type = runOptions->getValueOrDef<str>("DATABG", "background");
          if (background_type != "DATABG" && background_type != "SMBG" && background_type != "EXP"){
            ColliderBit_error().raise(LOCAL_INFO, "Requested Contur Background type does not exist");
          }
          result = contur_likelihood_object[which_as_LLR].outputs.at(background_type).LLR;
        }

        // Extracts the likelihood contribution from each contur pool from Contur_output
        void Contur_LHC_measurements_LogLike_perPool(map_str_dbl &result)
        {
          using namespace Pipes::Contur_LHC_measurements_LogLike_perPool;
          std::stringstream summary_line;
          summary_line << "LHC Contur LogLikes per pool: ";
          result = (*Dep::LHC_measurements).pool_LLR();

          for (auto const& entry : result)
          {
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
          for (const auto& contur_output_instance : contur_likelihood_object)
          {
            for (auto const& pool_LLR_entry : contur_output_instance.second.pool_LLR())
            {
              result[pool_LLR_entry.first + "_" + contur_output_instance.first] = pool_LLR_entry.second;
            }
          }
          for (auto const& entry : result)
          {
            summary_line << entry.first << ":" << entry.second << ", ";
          }
          logger() << LogTags::debug << summary_line.str() << EOM;
        }

        // Debug only: Get the dominant bin/histogram/correlated set thereof for each Contur pool
        // Note map_str_str will not print to hdf5! Use for ASCII debug only.
        void Contur_LHC_measurements_histotags_perPool(map_str_str &result)
        {
          using namespace Pipes::Contur_LHC_measurements_histotags_perPool;
          std::stringstream summary_line;
          summary_line << "LHC Contur LogLikes per pool: ";
          result = (*Dep::LHC_measurements).pool_tags();

          for (auto const& entry : result)
          {
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
          for (const auto& contur_output_instance : contur_likelihood_object)
          {
            for (auto const& pool_LLR_entry : contur_output_instance.second.pool_tags())
            {
              result[pool_LLR_entry.first + "_" + contur_output_instance.first] = pool_LLR_entry.second;
            }
          }
          for (auto const& entry : result)
          {
            summary_line << entry.first << ":" << entry.second << ", ";
          }
          logger() << LogTags::debug << summary_line.str() << EOM;
        }

      #endif //EXCLUDE_YODA
    #endif // HAVE_PYBIND11

  }  // namespace ColliderBit
}  // namespace Gambit
