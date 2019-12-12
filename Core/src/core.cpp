//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT Core driver class implementation.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///  \date 2013 Aug
///  \date 2014 Mar, Aug, Dec
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2017 Jun
///
///  *********************************************

#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

// Headers for GNU getopt command line parsing library
#include <stdlib.h>
#include <getopt.h>

// Gambit headers
#include "gambit/Core/core.hpp"
#include "gambit/Core/error_handlers.hpp"
#include "gambit/Core/yaml_description_database.hpp"
#include "gambit/ScannerBit/plugin_loader.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/version.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/cmake/cmake_variables.hpp"

// Boost
#include <boost/algorithm/string/replace.hpp>

// MPI
#ifdef WITH_MPI
  #include "gambit/Utils/mpiwrapper.hpp"
  #define GET_RANK GMPI::Comm().Get_rank()
  #define GET_SIZE GMPI::Comm().Get_size()
#else
  #define GET_RANK 0
  #define GET_SIZE 1
#endif


namespace Gambit
{
    /// Definitions of public methods in GAMBIT core class.

    /// Constructor
    gambit_core::gambit_core(const Models::ModelFunctorClaw &claw, const Backends::backend_info &beinfo )
     : modelInfo(&claw)
     , backendData(&beinfo)
     , input_capability_descriptions(GAMBIT_DIR "/config/capabilities.dat")
     , input_model_descriptions(GAMBIT_DIR "/config/models.dat")
     , outprec(8)
     /* command line flags */
     , processed_options(false)
     , show_runorder(false)
     , resume(true)
     , verbose_flag(false)
     , found_inifile(false)
     , developer_mode(false)
    {}

    /// Getter for precision to use for cout
    int gambit_core::get_outprec() const { return outprec; }

    /// Inform the user of the ways to invoke GAMBIT, then die.
    void gambit_core::bail(int mpirank)
    {
      if (mpirank < 0) mpirank = GET_RANK;
      if (mpirank == 0)
      {
        cout << "\nusage: gambit [options] [<command>]                                        "
                "\n                                                                           "
                "\nRun scan:                                                                  "
                "\n   gambit -f <inifile>   Start a scan using instructions from inifile      "
                "\n                           e.g.: gambit -f gambit.yaml                     "
                "\n                                                                           "
                "\nAvailable commands:                                                        "
                "\n   modules               List registered modules                           "
                "\n   backends              List registered backends and their status         "
                "\n   models                List registered models and output model graph     "
                "\n   capabilities          List all registered function capabilities         "
                "\n   scanners              List registered scanners                          "
                "\n   test-functions        List registered scanner test objective functions  "
                "\n   <name>                Give info on a specific module, backend, model,   "
                "\n                           capability or scanner                           "
                "\n                           e.g.: gambit DarkBit                            "
                "\n                                 gambit Pythia                             "
                "\n                                 gambit MSSM                               "
                "\n                                 gambit IC79WL_loglike                     "
                "\n                                 gambit MultiNest                          "
                "\n                                                                           "
                "\nBasic options:                                                             "
                "\n   --version             Display GAMBIT version information                "
                "\n   --developer           Run in developer mode (suppress database errors)  "
                "\n   -h/--help             Display this usage information                    "
                "\n   -f <inifile>          Start scan using <inifile>                        "
                "\n   -v/--verbose          Turn on verbose mode                              "
                "\n   -d/--dryrun           List the function evaluation order computed based "
                "\n                           on inifile                                      "
                "\n   -r/--restart          Restart the scan defined by <inifile>. Existing   "
                "\n                         output files for the run will be overwritten.     "
                "\n                         Default behaviour in the absence of this option is"
                "\n                         to attempt to resume the scan from any existing   "
                "\n                         output.                                           "
                "\n" << endl << endl;
      }
      logger().disable();
      throw SilentShutdownException();
    }

    /// Process default mode command line options and return filename
    str gambit_core::process_primary_options(int argc, char **argv)
    {
      int index;
      int iarg=0;
      str filename;

      /// Gambit 'standard mode' command line option definitions (needed by getopt)
      // Basically this is a clone of the example in the getopt_long documentation
      // (http://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Getopt-Long-Option-Example.html#Getopt-Long-Option-Example)
      //
      // Note that specialised versions of this structure exist for some of the special run modes.
      const struct option primary_options[] =
      {
        {"version", no_argument, 0, 1}, /*1 is just a unique integer key to identify this argument*/
        {"developer", no_argument, 0, 2},
        {"verbose", no_argument, 0, 'v'},
        {"help",    no_argument, 0, 'h'},
        {"dryrun",  no_argument, 0, 'd'},
        {"restart", no_argument, 0, 'r'},
        {0,0,0,0},
      };

      // Must at least have one argument.
      if (argc < 2) bail();

      while(iarg != -1)
      {
        iarg = getopt_long(argc, argv, "vhdrf:", primary_options, &index);
        switch (iarg)
        {
          case 1:
          {
            // Shut down.
            logger().disable();
            throw SilentShutdownException();
          }
          case 'v':
            // Turn on verbose mode
            verbose_flag = true;
            break;
          case 2:
          // Turn on developer mode
            developer_mode = true;
            break;
          case 'h':
          case '?':
            // display usage message and quit (also happens on unrecognised options)
            bail();
            break;
          case 'd':
            // Display proposed functor evaluation order and quit
            show_runorder = true; // Sorted out in dependency resolver
            // Should not allow this on multiple processes, just produces
            // mixed up junk output.
            if(GET_SIZE>1)
            {
               cout << "Tried to run GAMBIT dry-run mode in parallel! This is not allowed, please use only one process when performing dry-runs." << endl;
               logger().disable();
               throw SilentShutdownException();
            }
            break;
          case 'r':
            // Restart scan (turn off "resume" mode, activate output overwrite)
            resume = false;
            break;
          case 'f':
            // Argument must contain the ini-filename
            filename = optarg;
            found_inifile = true;
        }
      }
      // Set flag telling core object that command line option processing is complete
      processed_options = true;
      return filename;
    }

    /// Add a new module to modules list
    void gambit_core::registerModule(str module) { modules.insert(module); }

    /// Add a new module functor to functorList
    void gambit_core::registerModuleFunctor(functor &f)
    {
      functorList.push_back(&f);
      capabilities.insert(f.capability());
    }

    /// Add a new module functor to nestFunctorList
    void gambit_core::registerNestedModuleFunctor(functor &f) { nestedFunctorList.push_back(&f); }

    /// Add a new backend functor to backendFunctorList
    void gambit_core::registerBackendFunctor(functor &f)
    {
      backendFunctorList.push_back(&f);
      capabilities.insert(f.capability());
    }

    /// Register a new backend
    void gambit_core::registerBackend(str be, str version) { backend_versions[be].insert(version); }

    /// Add a new primary model functor to primaryModelFunctorList
    void gambit_core::registerPrimaryModelFunctor(primary_model_functor &f)
    {
      primaryModelFunctorList.push_back(&f);
      capabilities.insert(f.capability());
    }

    /// Add entries to the map of activated primary model functors
    void gambit_core::registerActiveModelFunctors(const gambit_core::pmfVec& fvec)
    {
      for (gambit_core::pmfVec::const_iterator it = fvec.begin(); it != fvec.end(); ++it)
      {
        activeModelFunctorList[(*it)->origin()] = *it;
      }
    }

    /// Get a reference to the list of module functors
    const gambit_core::fVec& gambit_core::getModuleFunctors() const { return functorList; }

    /// Get a reference to the list of nested module functors
    const gambit_core::fVec& gambit_core::getNestedModuleFunctors() const { return nestedFunctorList; }

    /// Get a reference to the list of backend functors
    const gambit_core::fVec& gambit_core::getBackendFunctors() const { return backendFunctorList; }

    /// Get a reference to the list of primary model functors
    const gambit_core::pmfVec& gambit_core::getPrimaryModelFunctors() const { return primaryModelFunctorList; }

    /// Get a reference to the map of all user-activated primary model functors
    const gambit_core::pmfMap& gambit_core::getActiveModelFunctors() const { return activeModelFunctorList; }

    /// Tell the module functors which backends are actually present,
    /// so that they can deactivate themselves if they require a class
    /// that is supposed to be provided by a backend that is AWOL.
    void gambit_core::accountForMissingClasses() const
    {
      // Create a map of all the registered backends that are connected and fully functional (including factories for classloading)
      std::map<str, std::set<str> > working_bes;
      // Start by looping over all registered backends
      for (std::map<str, std::set<str> >::const_iterator it = backend_versions.begin(); it != backend_versions.end(); ++it)
      {
        // Then loop over all registered versions of this backend
        for (std::set<str>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
        {
          const str be_ver = it->first+*jt;
          if (backendData->works.at(be_ver))
          {
            if (backendData->classloader.at(be_ver))
            {
              if (backendData->classes_OK.at(be_ver)) working_bes[it->first].insert(*jt);
            }
            else
            {
              working_bes[it->first].insert(*jt);
            }
          }
        }
      }
      // Feed the new map to each of the module functors.
      for (fVec::const_iterator it = functorList.begin(); it != functorList.end(); ++it)
      {
        (*it)->notifyOfBackends(working_bes);
      }
    }



    /// Check the capability and model databases for conflicts and missing descriptions
    void gambit_core::check_databases()
    {
      // Loop through registered capabilities and try to find their descriptions (potentially from many files, but for now just checking one)
      DescriptionDatabase description_file(input_capability_descriptions); // Load descriptions file
      //std::set<str> parsed_descriptions; // Set of capabilities whose description we have parsed
      bool missing_flag = false; // Lets us know if any missing descriptions identified

      // Check for duplicate description keys
      std::map<str,int> duplicates = description_file.check_for_duplicates();

      // Search through GAMBIT for information about registered capabilities to match to the descriptions
      for (std::set<str>::const_iterator it = capabilities.begin(); it != capabilities.end(); ++it)
      {
        capability_info capinfo;
        capinfo.name = *it;

        // Make sets of matching module and backend functions
        for (fVec::const_iterator jt = functorList.begin(); jt != functorList.end(); ++jt)
        {
          if ((*jt)->capability() == *it)
          {
            str origin((*jt)->origin());
            std::pair<str,str> name_type((*jt)->name(), (*jt)->type());
            if (capinfo.modset.find(origin) == capinfo.modset.end()) capinfo.modset[origin] = std::set<std::pair<str,str> >();
            capinfo.modset[origin].insert(name_type);
          }
        }
        for (fVec::const_iterator jt = backendFunctorList.begin(); jt != backendFunctorList.end(); ++jt)
        {
          if ((*jt)->capability() == *it)
          {
            str origin((*jt)->origin() + " v" + (*jt)->version());
            std::pair<str,str> name_type((*jt)->name(), (*jt)->type());
            if (capinfo.beset.find(origin) == capinfo.beset.end()) capinfo.beset[origin] = std::set<std::pair<str,str> >();
            capinfo.beset[origin].insert(name_type);
          }
        }

        // Check original description files for descriptions matching this capability
        if( description_file.hasKey(*it) )
        {
          // Check whether there are duplicates of this key
          if ( duplicates[*it] > 0 )
          {
            std::vector<str> dups = description_file.get_all_values(*it);
            std::ostringstream errmsg;
            errmsg << "Error! Duplicate capability descriptions found for capability \""<<*it<<
             "\"! Only one description is permitted, since all capabilities going by the same name "
             "must provide the same information. Please rename a capability or delete one of the descriptions."<<endl;
            errmsg << "The duplicate descriptions are:" <<endl;
            errmsg << "---------------------" <<endl;
            int dup_num = 0;
            for(std::vector<str>::iterator kt = dups.begin(); kt != dups.end(); ++kt)
            {
              errmsg << dup_num << ":" <<endl;
              errmsg << *kt;
              errmsg << "----------------------" <<endl;
              dup_num++;
            }
            core_error().raise(LOCAL_INFO,errmsg.str());
          }
          else
          {
            capinfo.description = description_file.getValue<str>(*it);
            capinfo.has_description = true;
          }
        }
        else
        {
          // Record that this description is missing
          capinfo.description = "Missing!";
          capinfo.has_description = false;
          missing_flag = true;
        }
        capability_dbase.push_back(capinfo);
      }

      missing_capability_description = false;

      if(missing_flag)
      {
        // Warn user of missing descriptions
        missing_capability_description = true;
      }

      // Write out the centralised database file containing all this information
      // (we could also keep this in memory for other functions to use; it's probably not that large)
      // Should probably sort it by module or something.

      // Could have built this directly in the other loop, but for now it is separate.
      YAML::Emitter out;
      out << YAML::BeginSeq;
      for (std::vector<capability_info>::iterator it = capability_dbase.begin(); it != capability_dbase.end(); ++it)
      {
        //capability_info tmp = *it;
        out << *it; //custom emitter to do this is in yaml_description_database.hpp
      }
      out << YAML::EndSeq;
      // Create file and write YAML output there
      std::ofstream outfile;
      outfile.open(Utils::runtime_scratch()+"central_capabilities.dat");
      outfile << "# Auto-generated capability description library. Edits will be erased." << endl;;
      outfile << "# Edit \"" << input_capability_descriptions << "\" instead." << endl << endl << out.c_str();


      // Now the models
      // This is distressingly similar to the capabilities case, but it doesn't seem so straightforward to modularise any further...

      // Loop through registered models and try to find their descriptions (potentially from many files, but for now just checking one)
      DescriptionDatabase model_description_file(input_model_descriptions); // Load descriptions file
      missing_flag = false; // reset this flag

      // Check for duplicate description keys
      duplicates = description_file.check_for_duplicates();

      // Search through GAMBIT for information about registered models to match to the descriptions
      for (pmfVec::const_iterator it = primaryModelFunctorList.begin(); it != primaryModelFunctorList.end(); ++it)
      {
        model_info model;
        model.name = (*it)->origin();

        // Check original description files for descriptions matching this capability
        if( model_description_file.hasKey(model.name) )
        {
          // Check whether there are duplicates of this key
          if (duplicates[model.name] > 0)
          {
            std::vector<str> dups = model_description_file.get_all_values(model.name);
            std::ostringstream errmsg;
            errmsg << "Error! Duplicate model descriptions found for model \""<<model.name<<
             "\"! Only one description is permitted, since model names must be unique. "
             "Please rename a model or delete one of the descriptions."<<endl;
            errmsg << "The duplicate descriptions are:" <<endl;
            errmsg << "---------------------" <<endl;
            int dup_num = 0;
            for(std::vector<str>::iterator kt = dups.begin(); kt != dups.end(); ++kt)
            {
              errmsg << dup_num << ":" <<endl;
              errmsg << *kt;
              errmsg << "----------------------" <<endl;
              dup_num++;
            }
            core_error().raise(LOCAL_INFO,errmsg.str());
          }
          else
          {
            model.description = model_description_file.getValue<str>(model.name);
            model.has_description = true;
          }
        }
        else
        {
          // Record that this description is missing
          model.description = "Missing!";
          model.has_description = false;
          missing_flag = true;
        }

        // Get the rest of the info
        model.nparams = (*it)->valuePtr()->getNumberOfPars();
        model.parameters = (*it)->valuePtr()->getKeys();
        model.parent = modelInfo->get_parent(model.name);
        model.lineage = modelInfo->get_lineage(model.name);
        model.descendants = modelInfo->get_descendants(model.name);

        model_dbase.push_back(model);
      }

      if(missing_flag)
      {
        // Warn user of missing descriptions
        cout << "Descriptions are missing for the following models:" << endl;
        for (std::vector<model_info>::const_iterator it = model_dbase.begin(); it != model_dbase.end(); ++it)
        {
          if(not it->has_description)
          {
            cout << "   " << it->name << endl;
          }
        }
        cout << "Please add descriptions of these to "<< input_model_descriptions << endl;
      }

      // Write out the centralised database file containing all this information
      // (we could also keep this in memory for other functions to use; it's probably not that large)
      // Should probably sort it by module or something.

      // Could have built this directly in the other loop, but for now it is separate.
      YAML::Emitter out2;
      out2 << YAML::BeginSeq;
      for (std::vector<model_info>::const_iterator it = model_dbase.begin(); it != model_dbase.end(); ++it)
      {
        out2 << *it; //custom emitter to do this is in yaml_description_database.hpp
      }
      out2 << YAML::EndSeq;
      // Create file and write YAML output there
      std::ofstream outfile2;
      outfile2.open(Utils::runtime_scratch()+"central_models.dat");
      outfile2 << "# Auto-generated model description library. Edits will be erased." << endl;;
      outfile2 << "# Edit \"" << input_model_descriptions << "\" instead." << endl << endl << out2.c_str();

    }


    void gambit_core::check_capability_descriptions()
    {

      if (missing_capability_description)
      {
        cout << "Descriptions are missing for the following capabilities:" << endl;
        for (std::vector<capability_info>::const_iterator it = capability_dbase.begin(); it != capability_dbase.end(); ++it)
        {
          if(not it->has_description)
          {
            cout << "   " << it->name << endl;
          }
        }
        cout << "Please add descriptions of these to "<< input_capability_descriptions << endl;
      }
    }

    /// Get the description of the named capability from the description database
    const capability_info gambit_core::get_capability_info(const str& name) const
    {

      for(std::vector<capability_info>::const_iterator it=capability_dbase.begin();
           it!=capability_dbase.end();++it)
      {
         if(it->name==name)
         {
           return *it; //Should only be one match possible after database check
         }
      }
      // if no match...
      std::ostringstream errmsg;
      errmsg << "No capability with the name \""<<name<< "\" could be found in the capability database. "
       "This function should not run when we don't know if the capability exists! Either there is a bug "
       "in the calling code, or something went wrong creating the capability database.";
      core_error().raise(LOCAL_INFO,errmsg.str());
      return capability_info();
    }

    const model_info gambit_core::get_model_info(const str& name) const
    {
      for(std::vector<model_info>::const_iterator it=model_dbase.begin();
           it!=model_dbase.end();++it)
      {
         if(it->name==name)
         {
           return *it; //Should only be one match possible after database check
         }
      }
      // if no match...
      std::ostringstream errmsg;
      errmsg << "No model with the name \""<<name<< "\" could be found in the model database. This function "
       "should not run when we don't know if the model exists! Either there is a bug in the calling code, or "
       "something went wrong creating the model database.";
      core_error().raise(LOCAL_INFO,errmsg.str());
      return model_info();
    }

    /// Compute the status of a given backend
    str gambit_core::backend_status(str be, str version, bool& no_failures)
    {
      const str OK = "OK";
      const str bad = "absent/broken";
      const str badclass = "bad types";
      const str missingMath = "Mathematica absent";
      str status;
      if (backendData->works.at(be+version))
      {
        if (backendData->classloader.at(be+version))
        {
          status = (backendData->classes_OK.at(be+version) ? OK : badclass);
        }
        else { status = OK; }
      }
      else if (backendData->needsMathematica.at(be+version))
      {
        #ifdef HAVE_MATHEMATICA
          status = bad;
        #else
          status = missingMath;
        #endif
      }
      else if (backendData->missingPythonVersion.at(be+version) > 0)
      {
        std::ostringstream status_stream;
        status_stream << "needs Python " << backendData->missingPythonVersion.at(be+version);
        status = status_stream.str();
      }
      else { status = bad; }
      if (status == bad or status == badclass) no_failures = false;
      return status;
    }

    /// Launch non-interactive command-line diagnostic mode, for printing info about current GAMBIT configuration.
    str gambit_core::run_diagnostic(int argc, char **argv)
    {

      str filename;
      str command = "none";
      std::vector<std::string> didyoumean;

      // Parse the arguments, ignoring everything before gambit executable
      if (argc > 1)
      {
        for (int i = 0; i < argc-1; i++)
        {
          str arg = argv[i];
          str x(GAMBIT_EXECUTABLE);
          int len = arg.length();
          int xlen = x.length();
          if (len >= xlen and arg.substr(len-xlen,xlen) == x)
          {
            command = argv[i+1];
            break;
          }
        }
      }

      // Initial list of valid diagnostic commands
      std::vector<str> valid_commands = initVector<str>
      (
        "modules",
        "backends",
        "models",
        "capabilities",
        "scanners",
        "test-functions"
      );

      // Test if the user has requested one of the basic diagnostics
      if (std::find(valid_commands.begin(), valid_commands.end(), command) == valid_commands.end())
      {
        // If we aren't just checking what stuff is registered, we could end up running a scan, or needing the descriptions of things.
        // Therefore we must construct the description databases and make sure there are no naming conflicts etc.
        check_databases();

        // Add other valid diagnostic commands
        valid_commands.insert(valid_commands.end(), modules.begin(), modules.end());
        valid_commands.insert(valid_commands.end(), capabilities.begin(), capabilities.end());
        for (auto it = backend_versions.begin(); it != backend_versions.end(); ++it) valid_commands.push_back(it->first);
        for (auto it = primaryModelFunctorList.begin(); it != primaryModelFunctorList.end(); ++it) valid_commands.push_back((*it)->origin());
        std::vector<std::string> scanner_names = Scanner::Plugins::plugin_info().print_plugin_names("scanner");
        std::vector<std::string> objective_names = Scanner::Plugins::plugin_info().print_plugin_names("objective");
        std::vector<std::string> prior_groups = Scanner::Plugins::plugin_info().list_prior_groups();
        valid_commands.insert(valid_commands.end(), scanner_names.begin(), scanner_names.end());
        valid_commands.insert(valid_commands.end(), objective_names.begin(), objective_names.end());
        valid_commands.insert(valid_commands.end(), prior_groups.begin(), prior_groups.end());
        //valid_commands.push_back("priors");

        // If the user hasn't asked for a diagnostic at all, process the command line options for the standard run mode and get out.
        if (std::find(valid_commands.begin(), valid_commands.end(), command) == valid_commands.end())
        {
          if (not processed_options)
          {
            filename = process_primary_options(argc,argv);
            check_capability_descriptions();
            // Check if we indeed received a valid filename (needs the -f option)
            if (found_inifile) return filename;
            // Ok then, report an unrecognised command and bail
            int mpirank = GET_RANK;
            if (mpirank == 0) cout << "Unrecognised command received!" << endl;
            // Give a list of valid commands that user might have mistyped
            for (std::vector<str>::iterator it = valid_commands.begin(); it != valid_commands.end(); ++it)
            {
              if (Utils::are_similar(command,*it)){ didyoumean.push_back(*it); }
            }
            if (didyoumean.size() > 0)
            {
              if (mpirank == 0)
              {
                cout<<"Did you mean one of the following?"<<endl;
                for (std::vector<str>::iterator it = didyoumean.begin(); it != didyoumean.end(); ++it)
                {
                  if(Utils::are_similar(command,*it)){ cout<<"  "<<*it<<endl; }
                }
                cout<<endl;
                cout<<"Run \"gambit --help\" for a full list of options and usage instructions"<<endl;
              }
              logger().disable();
              throw SilentShutdownException();
            }
            else
            {
              bail(mpirank);
            }

          }
          else
          {
            int mpirank = GET_RANK;
            if (mpirank == 0) cout << "Command line options have already been "
             "processed in a special run mode... GAMBIT should not reach this "
             "point. Quitting..." << endl;
            logger().disable();
            throw SilentShutdownException();
          }
        }
      }



      // Guaranteed from this point that no scans (nor scanners) will be invoked.

      // Get MPI rank (assume MPI already initialised)
      int mpirank = GET_RANK;

      // Disable all but the master MPI node
      if (mpirank == 0)
      {
        if (command == "modules") module_diagnostic();
        if (command == "backends") backend_diagnostic();
        if (command == "models") model_diagnostic();
        if (command == "capabilities") capability_diagnostic();
        if (command == "scanners") scanner_diagnostic();
        if (command == "test-functions") test_function_diagnostic();
        if (command == "priors") prior_diagnostic();
        ff_module_diagnostic(command);
        ff_backend_diagnostic(command);
        ff_model_diagnostic(command);
        ff_capability_diagnostic(command);
        ff_scanner_diagnostic(command);
        ff_test_function_diagnostic(command);
        ff_prior_diagnostic(command);
        cout << endl;
      }

      // Silently print the logs to scratch/run_time/<processID>/default.log
      logger().emit_backlog(false);
      // Split.
      logger().disable();
      throw SilentShutdownException();
      return "";

    }

}
