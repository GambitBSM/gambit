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
///  \author Pengxuan Zhu
///  \date   2026 Oct
///
///  *********************************************

#include "gambit/Elements/gambit_module_headers.hpp"
#include "gambit/ColliderBit/ColliderBit_rollcall.hpp"
#include "gambit/ColliderBit/Utils.hpp"
#include "gambit/ColliderBit/ColliderBit_eventloop.hpp"
#include "gambit/ColliderBit/cbs_checkpoint_yoda.hpp"

#ifndef EXCLUDE_HEPMC
  #include "gambit/Utils/begin_ignore_warnings_hepmc.hpp"
  #include "HepMC3/ReaderAscii.h"
  #include "HepMC3/ReaderAsciiHepMC2.h"
  #include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#ifndef EXCLUDE_YODA
  #include "gambit/Utils/begin_ignore_warnings_yoda.hpp"
  #include "YODA/AnalysisObject.h"
  #include "YODA/Fillable.h"
  #include "YODA/IO.h"
  #include "gambit/Utils/end_ignore_warnings.hpp"
#endif

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace Gambit
{

  namespace ColliderBit
  {

    #if !defined(EXCLUDE_HEPMC) && !defined(EXCLUDE_YODA)
      namespace
      {
        std::vector<std::unique_ptr<Rivet_default::Rivet::AnalysisHandler>>& rivet_analysis_handlers()
        {
          static std::vector<std::unique_ptr<Rivet_default::Rivet::AnalysisHandler>> handlers;
          return handlers;
        }
      }
    #endif

    void clear_rivet_measurements() noexcept
    {
      #if !defined(EXCLUDE_HEPMC) && !defined(EXCLUDE_YODA)
        rivet_analysis_handlers().clear();
      #endif
    }

    //Small convenience function for supplying options to the contur argparser.
    void convert_yaml_options_for_contur(std::vector<std::string> &yaml_options)
    {
      for (size_t i{0}; i <yaml_options.size(); ++i)
      {
        yaml_options[i] = ("--"+yaml_options[i]);
      }
    }

    void scale_checkpoint_yoda(const std::string& source,
                               const std::string& destination,
                               double scale)
    {
      #if defined(EXCLUDE_HEPMC) || defined(EXCLUDE_YODA)
        (void) source;
        (void) destination;
        (void) scale;
        throw std::runtime_error("CBS checkpoint YODA scaling requires HepMC and YODA.");
      #else
        if (!(scale >= 0.0) || !std::isfinite(scale))
          throw std::runtime_error("Invalid CBS checkpoint YODA scale for " + source);
        std::vector<YODA::AnalysisObject*> objects;
        try
        {
          YODA::read(source, objects);
          for (YODA::AnalysisObject* object : objects)
          {
            const std::string path = object->path();
            if (path.find("/RAW/") == std::string::npos) continue;
            if (path.find("_XSEC") != std::string::npos) continue;
            if (path.find("_BEAMPZ") != std::string::npos) continue;
            // Estimates booked under /RAW/ are pre-finalize placeholders
            // (ratios and similar). Rivet recomputes them in finalize after
            // the fillable histograms have been merged. They are not weight sums.
            auto* fillable = dynamic_cast<YODA::Fillable*>(object);
            if (fillable == nullptr) continue;
            fillable->scaleW(scale);
          }
          YODA::write(destination, objects);
        }
        catch (...)
        {
          for (YODA::AnalysisObject* object : objects) delete object;
          throw;
        }
        for (YODA::AnalysisObject* object : objects) delete object;
      #endif
    }

    void merge_checkpoint_yodas(const std::vector<std::string>& scaled_files,
                                const std::string& destination,
                                double cross_section_pb,
                                double cross_section_uncert_pb)
    {
      #if defined(EXCLUDE_HEPMC) || defined(EXCLUDE_YODA)
        (void) scaled_files;
        (void) destination;
        (void) cross_section_pb;
        (void) cross_section_uncert_pb;
        throw std::runtime_error("CBS checkpoint YODA merge requires HepMC and YODA.");
      #else
        if (scaled_files.empty())
          throw std::runtime_error("CBS checkpoint YODA merge received no files.");
        if (!(cross_section_pb > 0.0) || !std::isfinite(cross_section_pb)
            || !std::isfinite(cross_section_uncert_pb) || cross_section_uncert_pb < 0.0)
          throw std::runtime_error("CBS checkpoint YODA merge requires a positive collider cross section.");

        using Rivet_default::Rivet::AnalysisHandler;
        AnalysisHandler handler;
        std::ostringstream discarded;
        std::streambuf* saved = std::cout.rdbuf(discarded.rdbuf());
        try
        {
          handler.mergeYODAs(scaled_files, {}, {}, {}, {}, true, false);
          handler.setCrossSection(std::make_pair(cross_section_pb, cross_section_uncert_pb), true);
          handler.finalize();
          handler.writeData(destination);
        }
        catch (const std::exception& error)
        {
          std::cout.rdbuf(saved);
          throw std::runtime_error(std::string("CBS checkpoint YODA merge failed: ") + error.what());
        }
        catch (...)
        {
          std::cout.rdbuf(saved);
          throw std::runtime_error("CBS checkpoint YODA merge failed.");
        }
        std::cout.rdbuf(saved);
      #endif
    }

    #ifndef EXCLUDE_HEPMC
      #ifndef EXCLUDE_YODA

        // Analyse HepMC events with Rivet's measurements
        // Collect results in a stream of a YODA file
        void Rivet_measurements(std::shared_ptr<std::ostringstream> &result)
        {
          using namespace Pipes::Rivet_measurements;
          using namespace Rivet_default::Rivet;

          auto& anahandlers = rivet_analysis_handlers();
          static std::vector<long long> events_analysed_perthread;

          static std::vector<string>  analyses;
          static std::vector<string> excluded_analyses;

          if (*Loop::iteration == COLLIDER_INIT)
          {
            // Wipe out all analysisHandlers (will be reinitialised in COLLIDER_INIT_OMP)
            anahandlers.clear();
            anahandlers.resize(omp_get_max_threads());
            events_analysed_perthread.assign(anahandlers.size(), 0);
            Dep::RunMC->rivet_analyses.clear();

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
            // Allocate by OpenMP thread ID, including threads which may be idle
            // during initialisation. Team sizes may change between regions.
            for (auto& handler : anahandlers)
            {
              handler = std::make_unique<AnalysisHandler>();
              for (const auto& name : analyses)
                if (name != "13TeV" && name != "8TeV" && name != "7TeV") handler->addAnalysis(name);
              handler->removeAnalyses(excluded_analyses);
            }
          }


          if (*Loop::iteration == COLLIDER_INIT_OMP){

            #pragma omp critical
            {
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
            #ifdef COLLIDERBIT_DEBUG
              std::cout << "Rivet: thread " << omp_get_thread_num() << " analysed " << events_analysed_perthread[omp_get_thread_num()] << " events" << std::endl;
            #endif
          }

          // TODO: consider cleaning up.
          if (*Loop::iteration == COLLIDER_FINALIZE)
          {
            std::size_t master = anahandlers.size();
            for (std::size_t i = 0; i < anahandlers.size(); ++i)
              if (anahandlers[i] && events_analysed_perthread[i] > 0) { master = i; break; }
            if (master != anahandlers.size())
            {
              result = std::make_shared<std::ostringstream>();
              // Merge raw statistics before finalizing exactly once. The first
              // event is a real analysed event, including on worker threads.
              for (std::size_t i = 0; i < anahandlers.size(); ++i)
                if (i != master && anahandlers[i] && events_analysed_perthread[i] > 0)
                  anahandlers[master]->merge(*anahandlers[i]);
              // Per-thread files are diagnostic snapshots. Finalize workers
              // only after their raw contents have been merged into the master.
              if (runOptions->getValueOrDef<bool>(false, "drop_perthread_YODA_file"))
                for (std::size_t i = 0; i < anahandlers.size(); ++i)
                  if (i != master && anahandlers[i] && events_analysed_perthread[i] > 0)
                  {
                    anahandlers[i]->finalize();
                    anahandlers[i]->writeData("TEST_" + std::to_string(i) + ".yoda");
                  }
              anahandlers[master]->finalize();
              Dep::RunMC->rivet_analyses = anahandlers[master]->analysisNames();
              if (Dep::RunMC->rivet_analyses.empty())
                ColliderBit_error().raise(LOCAL_INFO, "No Rivet analyses matched the input run conditions.");
              anahandlers[master]->writeData(*result, "yoda");

              // write_YODA_file true saves the merged YODA alongside the CBS
              // result. drop_YODA_file is the older name for the same choice:
              // true still writes the file.
              bool write_yoda_file = false;
              if (runOptions->hasKey("write_YODA_file"))
                write_yoda_file = runOptions->getValue<bool>("write_YODA_file");
              else
                write_yoda_file = runOptions->getValueOrDef<bool>(false, "drop_YODA_file");
              if(write_yoda_file)
              {
                // YODA_filename, when set, is the full output path. Callers that
                // omit it keep the collider-named file in YODA_output_directory.
                str filename;
                if (runOptions->hasKey("YODA_filename"))
                  filename = runOptions->getValue<str>("YODA_filename");
                else
                  filename = "GAMBIT_collider_measurements_"+Dep::RunMC->current_collider()+".yoda";
                if (!runOptions->hasKey("YODA_filename") && runOptions->hasKey("YODA_output_directory"))
                {
                  const str directory = runOptions->getValue<str>("YODA_output_directory");
                  if (directory != "" && directory != ".")
                  {
                    if (directory.back() == '/' || directory.back() == '\\')
                      filename = directory + filename;
                    else
                      filename = directory + "/" + filename;
                  }
                }
                #pragma omp critical
                {
                  try { anahandlers[master]->writeData(filename); }
                  catch (const std::exception& error)
                  {
                    ColliderBit_error().raise(LOCAL_INFO,
                      "Unexpected error in writing YODA file " + filename + ": " + error.what());
                  }
                  catch (...)
                  {
                    ColliderBit_error().raise(LOCAL_INFO,
                      "Unexpected error in writing YODA file " + filename);
                  }
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
          auto& events_analysed = events_analysed_perthread.at(omp_get_thread_num());
          std::string rivet_error;
          try {
            // Rivet's first-event plugin initialisation is serialised. Catch
            // inside the critical region: exceptions must not cross it.
            if (events_analysed < 1){
              #pragma omp critical
              {
                try { anahandlers[omp_get_thread_num()]->analyze(ge); }
                catch (const std::exception& error) { rivet_error = error.what(); }
                catch (int code) { rivet_error = "Rivet integer exception " + std::to_string(code); }
                catch (...) { rivet_error = "Rivet unknown non-standard exception during first-event initialization"; }
              }
              if (!rivet_error.empty()) throw std::runtime_error(rivet_error);
              if (runOptions->hasKey("cbs_cross_section_pb"))
                anahandlers[omp_get_thread_num()]->setCrossSection(
                  runOptions->getValue<double>("cbs_cross_section_pb"),
                  runOptions->getValue<double>("cbs_cross_section_uncert_pb"), true);
            }
            else {
              anahandlers[omp_get_thread_num()]->analyze(ge);
            }
            events_analysed++;
          }
          catch(const std::exception &e)
          {
            piped_errors.request(LOCAL_INFO, e.what());
            Loop::halt();
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
            Dep::RunMC->contur_evaluations = 0;
          }
          else if (*Loop::iteration == COLLIDER_FINALIZE)
          {
            Contur_output temp_result;
            std::shared_ptr<std::ostringstream> yodastream = *Dep::Rivet_measurements;

            //Check that rivet actually ran. If not, produce an empty Contur_output object.
            if (yodastream == nullptr)
            {
              ColliderBit_error().raise(LOCAL_INFO, "Rivet produced no measurement stream; Contur result is invalid.");
            }
            //If rivet ran, run Contur.
            else
            {
              std::vector<std::string> yaml_contur_options = runOptions->getValueOrDef<std::vector<str>>(std::vector<str>(), "contur_options");
              convert_yaml_options_for_contur(yaml_contur_options);

              std::string contur_error;
              #pragma omp critical
              {
                try
                {
                  temp_result = BEreq::Contur_Measurements(std::move(yodastream), yaml_contur_options);
                  if (temp_result.outputs.at("DATABG").pool_LLR.empty())
                    throw std::runtime_error("Contur found no usable measurement pools for this prediction.");
                  ++Dep::RunMC->contur_evaluations;
                }
                catch (const std::exception& error) { contur_error = error.what(); }
              }
              if (!contur_error.empty()) ColliderBit_error().raise(LOCAL_INFO, contur_error);
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
