//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Functions specifically for triggering
///  backend initialisation code.
///
///  *********************************************
///
///  Authors
///  =======
///
///  (add name and date if you modify)
///
///  \author Pat Scott
///          (p.scott@imperial.ac.uk)
///  \date 2015 Feb
///
///  \author Tomas Gonzalo
///          (t.e.gonzalo@fys.uio.no)
///  \date 2016 Sep
///
///  *********************************************

#include <regex>

#include <boost/algorithm/string/replace.hpp>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Elements/functors.hpp"
#include "gambit/Elements/ini_catch.hpp"
#include "gambit/Backends/backend_singleton.hpp"
#include "gambit/Backends/ini_functions.hpp"
#include "gambit/Models/claw_singleton.hpp"
#include "gambit/Utils/util_functions.hpp"
#include "gambit/Logs/logging.hpp"

#ifdef HAVE_MATHEMATICA
  #include MATHEMATICA_WSTP_H
#endif


namespace Gambit
{

  /// Get back the "::" from things that use NS_SEP instead
  str fixns(str s)
  {
    str ns = STRINGIFY(NS_SEP);
    const str cc = "::";
    std::regex rgx1(ns), rgx2("my_ns"+cc), rgx3(cc+"\\("), rgx4(cc+"$");
    s = std::regex_replace(s, rgx1, cc);
    s = std::regex_replace(s, rgx2, "");
    s = std::regex_replace(s, rgx3, "(");
    s = std::regex_replace(s, rgx4, "");
    return s;
  }

  /// Call push back on a vector of strings
  int vectorstr_push_back(std::vector<str>& vec, str s)
  {
    try
    {
      vec.push_back(s);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Notify a backend functor of which models it can be used with
  int set_allowed_models(functor& be_functor, std::vector<str>& allowed_at_be_level, str models_string)
  {
    try
    {
      // Strip out parentheses
      models_string = models_string.substr(1,models_string.length()-2);
      // Get the models explicitly allowed in this command
      std::vector<str> models = Utils::delimiterSplit(models_string, ",");
      // Harmonise any models declared as allowed for the backend as a whole with those exlicitly allowed in this command.
      if (not allowed_at_be_level.empty())
      {
        // If there are no models explicitly allowed, just inherit the allowed models from the backend as a whole.
        if (models.empty())
        {
          models.insert(models.end(), allowed_at_be_level.begin(), allowed_at_be_level.end());
        }
        // If there are models explicitly allowed, and models allowed at the whole-backend level, make sure their declarations are consistent.
        else
        {
          // Loop over all the models explicitly allowed here, and make sure they fit with at least one of those declared at the backend level.
          for (std::vector<str>::const_iterator it = models.begin(); it != models.end(); ++it)
          {
            bool found_match = false;
            for (std::vector<str>::const_iterator jt = allowed_at_be_level.begin(); jt != allowed_at_be_level.end(); ++jt)
            {
              found_match = Models::ModelDB().upstream_of(*jt,*it);
              if (found_match) break;
            }
            if (not found_match)
            {
              std::stringstream msg;
              msg << "Conflicting model compatibility information provided for backend function or variable" << endl
                  << be_functor.origin() << "::" << be_functor.name() << "." << endl
                  << "The frontend header for " << be_functor.origin() << " declares that this function or variable" << endl
                  << "can be used with model " << *it << ", but that model is not interpretable (via ancestry or friend" << endl
                  << "relationships) as any of the models declared as allowed for the entire backend with the BE_ALLOW_MODELS" << endl
                  << "directive.  If the current declarations were to be taken at face value, this function/variable would " << endl
                  << "*never* be activated, for any model.  Please correct one or the other of these declarations." << endl;
              backend_error().raise(LOCAL_INFO, msg.str());
            }
          }
        }
      }
      // Allow the models
      if (not models.empty())
      {
        for (std::vector<str>::const_iterator it = models.begin(); it != models.end(); ++it)
        {
          be_functor.setAllowedModel(*it);
        }
      }
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a backend with the logging system
  int register_backend_with_log(str s)
  {
    try
    {
      int mytag = Logging::getfreetag();
      Logging::tag2str()[mytag] = s;
      Logging::components().insert(mytag);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Register a bossed type with the rollcall system
  int register_type(str bever, str classname)
  {
    try
    {
      Utils::strip_whitespace_except_after_const(classname);
      Backends::backendInfo().classes[bever].insert(classname);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Disable a C, C++ or Fortran backend functor if its library is missing or the symbol cannot be found.
  void set_backend_functor_status_C_CXX_Fortran(functor& be_functor, const std::vector<str>& symbol_names)
  {
    bool present = Backends::backendInfo().works.at(be_functor.origin() + be_functor.version());
    if (not present)
    {
      be_functor.setStatus(-1);
    }
    else if(dlerror() != NULL and symbol_names[0] != "no_symbol")
    {
      std::ostringstream err;
      err << "None of the library symbols (";
      for(str smb : symbol_names) { err << smb << ", "; }
      err.seekp(-2, std::ios_base::end);
      err << ") was found." << std::endl
          << "The backend function from this symbol will be disabled (i.e. get status = -2)" << std::endl;
      backend_warning().raise(LOCAL_INFO, err.str());
      be_functor.setStatus(-2);
    }
  }

  #ifdef HAVE_MATHEMATICA
  /// Disable a Mathematica backend functor if its package is missing or the function is not found in the package
  void set_backend_functor_status_Mathematica(functor& be_functor, str symbol_name)
  {
    const str be = be_functor.origin() + be_functor.version();
    bool present = Backends::backendInfo().works.at(be);
    if (not present)
    {
      be_functor.setStatus(-1);
    }
    else if(symbol_name != "no_symbol")
    {
      WSLINK pHandle = Backends::backendInfo().loaded_mathematica_backends.at(be);
      std::ostringstream err;
      // Replace \[ for \\[ so that names can have non-ASCII characters
      boost::replace_all(symbol_name, "\\[", "\\\\[");
      if(!WSPutFunction(pHandle, "NameQ", 1) or
         !WSPutFunction(pHandle, "StringDrop",2) or
         !WSPutFunction(pHandle, "StringDrop",2) or
         !WSPutFunction(pHandle, "ToString", 1) or
         !WSPutFunction(pHandle, "ToExpression", 3) or
         !WSPutString(pHandle, symbol_name.c_str()) or
         !WSPutSymbol(pHandle, "StandardForm") or
         !WSPutSymbol(pHandle, "Hold") or
         !WSPutInteger(pHandle, 5) or
         !WSPutInteger(pHandle, -1))
      {
        err << "Error sending packet through WSTP." << std::endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        be_functor.setStatus(-2);
      }

      int pkt;
      while( (pkt = WSNextPacket(pHandle), pkt) && pkt != RETURNPKT)
      {
        WSNewPacket(pHandle);
        if (WSError(pHandle))
        {
          err << "Error reading packet from WSTP" << std::endl;
          backend_warning().raise(LOCAL_INFO, err.str());
          be_functor.setStatus(-2);
        }
      }

      const char *symbol_exists;
      if(!WSGetString(pHandle, &symbol_exists))
      {
        err << "Error retrieving packet from WSTP." << std::endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        be_functor.setStatus(-2);
      }

      if(str(symbol_exists) == "False")
      {
        err << "Mathematica function " << symbol_name << " not found."  << std::endl
            << "The backend function from this symbol will be disabled (i.e. get status = -2)" << std::endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        be_functor.setStatus(-2);
      }
    }
  }
  #endif

  #ifdef HAVE_PYBIND11
  /// Disable a Python backend functor if its module is missing or the function is not found in the module
  void set_backend_functor_status_Python(functor& be_functor, const str& symbol_name)
  {
    const str be = be_functor.origin() + be_functor.version();
    bool present = Backends::backendInfo().works.at(be);
    if (not present)
    {
      be_functor.setStatus(-1);
    }
    else if(symbol_name != "no_symbol")
    {
      if (Backends::backendInfo().dlerrors[be] == symbol_name) be_functor.setStatus(-2);
    }
  }
  #endif


  /// Disable a backend functor if its library is missing or the symbol cannot be found.
  int set_backend_functor_status(functor& be_functor, const std::vector<str>& symbol_names)
  {
    // Extract the backend that we're dealing with from the functor metadata.
    str be = be_functor.origin() + be_functor.version();

    try
    {
      // Now switch according to the language of the backend
      if (Backends::backendInfo().needsMathematica.at(be))
      {
        if (symbol_names.size() != 1) backend_error().raise(LOCAL_INFO, be+" is a Mathematica backend; "
         +be_functor.origin()+"::"+be_functor.name()+" can have only one symbol.");
        // And switch according to whether the language has its dependencies met or not
        #ifdef HAVE_MATHEMATICA
          set_backend_functor_status_Mathematica(be_functor, symbol_names[0]);
        #else
          std::ostringstream err;
          err << "Mathematica is not found or it is disabled. " << std::endl
              << "The backend function for the symbol " << symbol_names[0] << " will be disabled  (i.e. get status = -5)" << endl;
          be_functor.setStatus(-5);
          backend_warning().raise(LOCAL_INFO, err.str());
        #endif
      }
      // and so on.
      if (Backends::backendInfo().needsPython.at(be))
      {
        if (symbol_names.size() != 1) backend_error().raise(LOCAL_INFO, be+" is a Python backend; "
         +be_functor.origin()+"::"+be_functor.name()+" can have only one symbol.");
        #ifdef HAVE_PYBIND11
          set_backend_functor_status_Python(be_functor, symbol_names[0]);
        #else
          std::ostringstream err;
          err << "Pybind11 for interfacing with Python backends is not found or disabled. " << std::endl
              << "The backend function for the symbol " << symbol_names[0] << " will be disabled  (i.e. get status = -6)" << endl;
          be_functor.setStatus(-6);
          backend_warning().raise(LOCAL_INFO, err.str());
        #endif
      }
      else
      {
        set_backend_functor_status_C_CXX_Fortran(be_functor, symbol_names);
      }

    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }


  /// Disable a backend initialisation function if the backend is missing.
  int set_BackendIniBit_functor_status(functor& ini_functor, str be, str v)
  {
    bool present = Backends::backendInfo().works.at(be + v);
    try
    {
      if (not present)
      {
        ini_functor.setStatus(-4);
      }
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

  /// Get the status of a factory pointer to a BOSSed type's wrapper constructor.
  int get_ctor_status(str be, str ver, str name, str barename, str args, const std::vector<str>& symbol_names)
  {
    bool present = Backends::backendInfo().works.at(be+ver);
    try
    {
      const str path = Backends::backendInfo().corrected_path(be,ver);
      Backends::backendInfo().factory_args[be+ver+fixns(barename)].insert(args);
      if (not present)
      {
        std::ostringstream err;
        Backends::backendInfo().classes_OK[be+ver] = false;
        Backends::backendInfo().constructor_status[be+ver+fixns(barename+args)] = "lib absent";
        return -1;
      }
      else if (dlerror() != NULL)
      {
        std::ostringstream err;
        Backends::backendInfo().classes_OK[be+ver] = false;
        Backends::backendInfo().constructor_status[be+ver+fixns(barename+args)] = "broken";
        err << "None of the library symbols (";
        for(str smb : symbol_names) { err << smb << ", "; }
        err.seekp(-2, std::ios_base::end);
        err << ") was found in " << path << "."
            << std::endl << "The BOSSed type relying on factory " << name << args
            << " will be unavailable." << std::endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        return -2;
      }
      else
      {
        logger() << "Succeeded in loading constructor " << fixns(barename+args) << " from "<< std::endl
                 << path << "." << LogTags::backends << LogTags::info << EOM;
        Backends::backendInfo().constructor_status[be+ver+fixns(barename+args)] = "OK";
      }
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }


  /// Set a backend rule for one or more models.
  int set_backend_rule_for_model(module_functor_common& f, str models, str tags)
  {
    try
    {
      f.makeBackendRuleForModel(models, tags);
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }


  /// Set the classloading requirements of a given functor.
  int set_classload_requirements(module_functor_common& f, str be, str verstr, str default_ver)
  {
    try
    {
      // Split up the passed version string into individual versions
      std::vector<str> versions = Utils::delimiterSplit(verstr, ",");
      // Add each version individually as required for classloading
      for (auto it = versions.begin() ; it != versions.end(); ++it)
      {
        // Retrieve the version corresponding to the default if needed
        if (*it == "default") *it = Backends::backendInfo().version_from_safe_version(be, default_ver);
        // Retrieve the safe version corresponding to this version
        str sv = Backends::backendInfo().safe_version_from_version(be, *it);
        // Set the requirement in the functor
        f.setRequiredClassloader(be,*it,sv);
      }
    }
    catch (std::exception& e) { ini_catch(e); }
    return 0;
  }

}
