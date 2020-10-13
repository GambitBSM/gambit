//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  GAMBIT Core diagnostics implementation.
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

#include "gambit/Core/core.hpp"
#include "gambit/Core/modelgraph.hpp"
#include "gambit/Utils/stream_overloads.hpp"
#include "gambit/Utils/screen_print_utils.hpp"
#include "gambit/Utils/table_formatter.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/ScannerBit/plugin_loader.hpp"
#include "gambit/cmake/cmake_variables.hpp"

namespace Gambit
{

  /// Basic module diagnostic function
  void gambit_core::module_diagnostic()
  {
    table_formatter table("Modules", "#functions");
    table.padding(1);
    table.capitalize_title();
    table.default_widths(25);
    for (std::set<str>::const_iterator it = modules.begin(); it != modules.end(); ++it)
    {
      int nf = 0;
      for (fVec::const_iterator jt = functorList.begin(); jt != functorList.end(); ++jt)
      {
        if ((*jt)->origin() == *it) nf++;
      }
      table << *it << nf;
    }
    std::stringstream out;
    out << table.str();
    if (out.str().size() > 0)
        print_to_screen(out.str(), "module");
  }

  /// Basic backend diagnostic function
  void gambit_core::backend_diagnostic()
  {
    bool all_good = true;
    table_formatter table("Backends", "Version", "Path to lib", "Status ", " #func ", "#types ", "#ctors");
    table.padding(1);
    table.capitalize_title();
    table.default_widths(18, 7, 70, 13, 3, 3);

    // Loop over all registered backends
    for (std::map<str, std::set<str> >::const_iterator it = backend_versions.begin(); it != backend_versions.end(); ++it)
    {
      // Loop over all registered versions of this backend
      for (std::set<str>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
      {
        int nfuncs = 0;
        int ntypes = 0;
        int nctors = 0;

        // Retrieve the status and path info.
        const str path = backendData->path(it->first,*jt);                              // Get the path of this backend
        const str status = backend_status(it->first, *jt, all_good);                    // Save the status of this backend

        // Count up the number of functions in this version of the backend, using the registered functors.
        for (fVec::const_iterator kt = backendFunctorList.begin(); kt != backendFunctorList.end(); ++kt)
        {
          if ((*kt)->origin() == it->first and (*kt)->version() == *jt) nfuncs++; // If backend matches, increment the count of the functions in this version
        }

        // Do things specific to versions that provide classes
        if (backendData->classloader.at(it->first+*jt))
        {
          std::set<str> classes = backendData->classes.at(it->first+*jt);     // Retrieve classes loaded by this version
          ntypes = classes.size();                                            // Get the number of classes loaded by this backend
          for (std::set<str>::const_iterator kt = classes.begin(); kt != classes.end(); ++kt)
          {
            nctors += backendData->factory_args.at(it->first+*jt+*kt).size(); // Add the number of factories for this class to the total
          }
        }

        // Print the info
        std::ostringstream ss1, ss2;
        str ss1a, ss2a;
        const str firstentry = (jt == it->second.begin() ? it->first : "");
        ss1 << nfuncs;
        ss2 << ntypes;
        table << firstentry << *jt << path;
        if (status == "OK")
            table.green() << status;
        else
            table.red() << status;
        table << " " + ss1.str() << ss2.str() << nctors;
      }
    }

    std::stringstream out;
    out << "All relative paths are given with reference to " << GAMBIT_DIR << ".";
    if (all_good) out << endl << endl << "\033[032m" << "All your backend are belong to us." << "\033[0m" << endl;
    out << endl;
    out << table.str();
    if (out.str().size() > 0)
        print_to_screen(out.str(), "backend");
  }

  /// Basic model diagnostic function
  void gambit_core::model_diagnostic()
  {
    std::stringstream out;
    table_formatter table("Model", "Parent", "Parameters");
    table.default_widths(35);
    table.padding(1);
    table.capitalize_title();
    for (pmfVec::const_iterator it = primaryModelFunctorList.begin(); it != primaryModelFunctorList.end(); ++it)
    {
      str model = (*it)->origin();
      str parentof = modelInfo->get_parent(model);
      int nparams = (*it)->valuePtr()->getNumberOfPars();
      table << model << parentof << nparams;
    }
    #ifdef HAVE_GRAPHVIZ
        // Create and spit out graph of the model hierarchy.
        str graphfile = Utils::runtime_scratch() + "GAMBIT_model_hierarchy.gv";
        ModelHierarchy modelGraph(*modelInfo,primaryModelFunctorList,graphfile,false);
        out << endl << "Created graphviz model hierarchy graph in "+graphfile+"." << endl;
        out << endl << "To get postscript plot of model hierarchy, please run: " << endl;
        out << GAMBIT_DIR << "/Core/scripts/./graphviz.sh "+graphfile << endl;
    #else
        out << endl << "To get postscript plot of model hierarchy, please install graphviz, rerun cmake and remake GAMBIT." << endl;
    #endif
      out << table.str();
    if (out.str().size() > 0)
    print_to_screen(out.str(), "model");
  }

  /// Basic capability diagnostic function
  void gambit_core::capability_diagnostic()
  {

    // Default, list-format output header
    table_formatter table("Capabilities", "Available in (modules/models)", "Available in (backends)");
    table.padding(1);
    table.capitalize_title();
    table.default_widths(35, 25);
    for (std::set<str>::const_iterator it = capabilities.begin(); it != capabilities.end(); ++it)
    {
      std::set<str> modset, beset;
      str mods, bes, description;

      // Make sets of matching modules and backends
      for (fVec::const_iterator jt = functorList.begin(); jt != functorList.end(); ++jt)
      {
        if ((*jt)->capability() == *it) modset.insert((*jt)->origin());
      }
      for (fVec::const_iterator jt = backendFunctorList.begin(); jt != backendFunctorList.end(); ++jt)
      {
        if ((*jt)->capability() == *it) beset.insert((*jt)->origin());
      }

      // Make strings out of the sets
      for (std::set<str>::const_iterator jt = modset.begin(); jt != modset.end(); ++jt)
      {
        if (jt != modset.begin()) mods += ", ";
        mods += *jt;
      }
      for (std::set<str>::const_iterator jt = beset.begin(); jt != beset.end(); ++jt)
      {
        if (jt != beset.begin()) bes += ", ";
        bes += *jt;
      }

      // Identify the primary model parameters with their models.
      if (mods.length() == 0 and bes.length() == 0) mods = it->substr(0,it->length()-11);

      // Print the entry in the table (list format)
      table << *it << mods << bes;
    }
    std::stringstream out;
    out << table.str();
    if (out.str().size() > 0)
        print_to_screen(out.str(), "capability");
  }

  /// Basic scanner diagnostic function
  void gambit_core::scanner_diagnostic()
  {
    // Import scanner plugin info from ScannerBit
    std::string output = Scanner::Plugins::plugin_info().print_all("scanner");
    if (output.length() > 0)
        print_to_screen(output, "scanners");
  }

  /// Basic test function diagnostic function
  void gambit_core::test_function_diagnostic()
  {
    std::string output = Scanner::Plugins::plugin_info().print_all("objective");
    if (output.length() > 0)
        print_to_screen(output, "objectives");
  }

  void gambit_core::prior_diagnostic()
  {
    std::string output = Scanner::Plugins::plugin_info().print_priors("priors");
    if (output.length() > 0)
        print_to_screen(output, "priors");
  }

  void gambit_core::ff_prior_diagnostic(str& command)
  {
    if (command != "priors")
    {
        std::string output = Scanner::Plugins::plugin_info().print_priors(command);
        if (output.length() > 0)
            print_to_screen(output, command);
    }
  }

  /// Free-form module diagnostic function
  void gambit_core::ff_module_diagnostic(str& command)
  {
    std::stringstream out; //added this!  not 'cout' but 'out'
    for (std::set<str>::const_iterator it = modules.begin(); it != modules.end(); ++it)
    {
      if (command == *it)
      {
        out << "Information for module " << *it << "." << std::endl << std::endl;
        table_formatter table("", "", "", "LOOP MANAGER:", "DEPENDENCIES / BACKEND REQUIREMENTS");
        table.new_titles("Function", "Capability", "Result Type", " IS  NEEDS", "[type]         {type}");
        table.padding(1);
        table.capitalize_title();
        table.default_widths(30, 35, 35, 19, 27);

        for (fVec::const_iterator jt = functorList.begin(); jt != functorList.end(); ++jt)
        {
          if ((*jt)->origin() == *it)              // Module matches
          {
            str f = (*jt)->name();
            str c = (*jt)->capability();
            str t = (*jt)->type();
            str islm = (*jt)->canBeLoopManager() ? "Yes" : "No ";
            str nlm  = (*jt)->loopManagerCapability();
            std::set<sspair> deps = (*jt)->dependencies();
            std::set<sspair> reqs = (*jt)->backendreqs();
            table.no_newline() << f << c << t << (" " + islm + " " + nlm);

            if (not deps.empty())
            {
              for (std::set<sspair>::const_iterator kt = deps.begin(); kt != deps.end(); ++kt)
              {
                if (kt != deps.begin())
                    table.no_newline() << "" << "" << "" << "" << kt->first + " [" + kt->second + "]";
                else
                    table << kt->first + " [" + kt->second + "]";
              }
            }
            if (not reqs.empty())
            {
              for (std::set<sspair>::const_iterator kt = reqs.begin(); kt != reqs.end(); ++kt)
              {
                if (kt != reqs.begin() or not deps.empty())
                    table.no_newline() << "" << "" << "" << "" << kt->first + " {" + kt->second + "}";
                else
                    table << kt->first + " {" + kt->second + "}";
              }
            }
            if (reqs.empty() and deps.empty()) table << "";
            table.newline(table.row_pos()-1);
          }
        }
        out << table.str();
        break;
      }
    }
    if (out.str().size() > 0)
        print_to_screen(out.str(), command);
  }

  /// Free-form backend diagnostic function
  void gambit_core::ff_backend_diagnostic(str& command)
  {
    std::stringstream out;
    //Iterate over all backends to see if command matches one of them
    for (std::map<str, std::set<str> >::const_iterator it = backend_versions.begin(); it != backend_versions.end(); ++it)
    {
      if (command == it->first)
      {
        const std::set<str> versions = it->second;
        bool has_classloader = false;
        out << "Information for backend " << it->first << "." << std::endl << std::endl;

        // Loop over all registered versions of this backend
        for (std::set<str>::const_iterator jt = versions.begin(); jt != versions.end(); ++jt)
        {
          bool who_cares;
          const str path = backendData->corrected_path(it->first,*jt);  // Save the path of this backend
          const str status = backend_status(it->first, *jt, who_cares); // Save the status of this backend
          out << "Version: " << *jt << std::endl;
          out << "Path to library: " << path << std::endl;
          out << "Library status: " << status << std::endl;
          //bool first = true;

          table_formatter back_table("  Function/Variable", "Capability", "Type", "Status");
          back_table.capitalize_title();
          back_table.default_widths(27, 35, 40, 40);
          back_table.padding(1);
          back_table.top_line(true);
          back_table.bottom_line(true);
          // Loop over all the backend functions and variables
          for (fVec::const_iterator kt = backendFunctorList.begin(); kt != backendFunctorList.end(); ++kt)
          {
            if (((*kt)->origin() == it->first) and ((*kt)->version() == (*jt)))
            {
              const str f = (*kt)->name();
              const str c = (*kt)->capability();
              const str t = (*kt)->type();
              const int s = (*kt)->status();
              back_table << ("  " + f) << c << t;
              if(s == -5) back_table.red() << "Mathematica absent";
              else if (s == -2) back_table.red() << "Function absent";//ss = "Function absent";
              else if (s == -1) back_table.red() << "Backend absent";//ss = "Backend absent";
              else if (s >= 0)  back_table.green() << "Available";//ss = "Available";
              else back_table << "";
            }
          }
          if (back_table.rows() > 0)
            out << back_table.str();
          table_formatter class_table("  Class", "Constructor overload", "Status");
          class_table.capitalize_title();
          class_table.default_widths(46, 60, 60);
          class_table.padding(1);
          class_table.top_line(true);
          class_table.bottom_line(true);
          // If this version has classes to offer, print out info on them too
          if (backendData->classloader.at(it->first+*jt))
          {
            std::set<str> classes;
            if (backendData->classes.find(it->first+*jt) != backendData->classes.end()) classes = backendData->classes.at(it->first+*jt);
            has_classloader = true;
            // Loop over the classes
            for (std::set<str>::const_iterator kt = classes.begin(); kt != classes.end(); ++kt)
            {
              const std::set<str> ctors = backendData->factory_args.at(it->first+*jt+*kt);
              // Loop over the constructors in each class
              for (std::set<str>::const_iterator lt = ctors.begin(); lt != ctors.end(); ++lt)
              {
                str args = *lt;
                boost::replace_all(args, "my_ns::", "");
                const str ss = backendData->constructor_status.at(it->first+*jt+*kt+args);
                const str firstentry = (lt == ctors.begin() ? *kt : "");
                class_table << ("  " + firstentry) << args;
                if (ss == "OK")
                    class_table.green() << status;
                else
                    class_table.red() << status;
              }
            }
          }
          if (class_table.rows() > 0)
              out << class_table.str();
        }
        // Tell the user what the default version is for classes of this backend (if there are any).
        if (has_classloader)
        {
          const std::map<str, str> defs = backendData->default_safe_versions;
          const str my_def = (defs.find(it->first) != defs.end() ? backendData->version_from_safe_version(it->first,defs.at(it->first)) : "none");
          out << std::endl << "Default version for loaded classes: "  << my_def << std::endl << std::endl;
        }
        break;
      }
    }
    if (out.str().size() > 0)
        print_to_screen(out.str(), command);
  }

  /// Free-form model diagnostic function
  void gambit_core::ff_model_diagnostic(str& command)
  {
    std::stringstream out;
    //Iterate over all models to see if command matches one of them
    for (pmfVec::const_iterator it = primaryModelFunctorList.begin(); it != primaryModelFunctorList.end(); ++it)
    {
      str model = (*it)->origin();
      if (command == model)
      {
        out << "Information for model " << model << "." << endl << endl;;

        // Retrieve info on this capability from the database file
        model_info mod = get_model_info(model);

        // Need copies of lineage and descendant vectors with self-reference removed
        std::vector<str> lin_X = mod.lineage;
        std::vector<str> des_X = mod.descendants;

        // Erase element matching name
        lin_X.erase(std::remove(lin_X.begin(), lin_X.end(), mod.name), lin_X.end());
        des_X.erase(std::remove(des_X.begin(), des_X.end(), mod.name), des_X.end());

        out << "  Parent Model: " << mod.parent << std::endl;
        out << "  Number of parameters: " << mod.nparams << std::endl;
        out << "  Parameter names:" << mod.parameters << std::endl;
        out << "  'Ancestor' models:" << lin_X << std::endl;
        out << "  'Descendant' models:" << des_X << std::endl;
        out << "  Description: " << endl << mod.description << std::endl;

        break;
      }
    }
    if (out.str().size() > 0)
        print_to_screen(out.str(), command);
  }

  /// Free-form capability diagnostic function
  void gambit_core::ff_capability_diagnostic(str& command)
  {
    std::stringstream out;
    //Iterate over all capabilities to see if command matches one of them
    for (std::set<str>::const_iterator it = capabilities.begin(); it != capabilities.end(); ++it)
    {
      if (command == *it)
      {
        out << "Information for capability " << *it << "." << std::endl << std::endl;

        // Retrieve info on this capability from the database file
        const capability_info cap = get_capability_info(*it);
        std::vector< std::pair<str, std::map<str, std::set<std::pair<str,str> > > > > origins;
        origins.push_back(std::pair<str, std::map<str, std::set<std::pair<str,str> > > >("modules", cap.modset));
        origins.push_back(std::pair<str, std::map<str, std::set<std::pair<str,str> > > >("backends", cap.beset));
        // Loop over {modules, backends}
        for (std::vector< std::pair<str, std::map<str, std::set<std::pair<str,str> > > > >::const_iterator it = origins.begin(); it != origins.end(); ++it)
        {
          if (not it->second.empty())
          {
            out << "  Available in " << it->first << ": " << std::endl;
            // Loop over modules or backends
            for (std::map<str, std::set<std::pair<str,str> > >::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
            {
              out << "    " << jt->first << ": " << std::endl;
              // Loop over matching module/backend functions
              for (std::set<std::pair<str,str> >::const_iterator kt = jt->second.begin(); kt != jt->second.end(); ++kt)
              {
                // Spit out: function name [function type]
                out << "      function " << kt->first << " [type " << kt->second << "]" << std::endl;
              }
            }
            out << std::endl;
          }
        }
        out << "  Description: " << std::endl << cap.description << std::endl;
        break;
      }
    }
    if (out.str().size() > 0)
        print_to_screen(out.str(), command);
  }

  /// Free-form scanner diagnostic function
  void gambit_core::ff_scanner_diagnostic(str& command)
  {
    std::string output = Scanner::Plugins::plugin_info().print_plugin("scanner", command);
    if (output.length() > 0)
        print_to_screen(output, command);
  }

  /// Free-form test function diagnostic function
  void gambit_core::ff_test_function_diagnostic(str& command)
  {
    std::string output = Scanner::Plugins::plugin_info().print_plugin("objective", command);
    if (output.length() > 0)
        print_to_screen(output, command);
  }

}
