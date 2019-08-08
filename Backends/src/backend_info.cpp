//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Container used for storing info about
///  backends during initialisation time.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Dec
///  \date 2017 Dec
///
///  \author Patrick Stoecker
///          (stoecker@physik.rwth-aachen.de)
///  \date 2019 Jun
///
///  *********************************************

#include <dlfcn.h>

#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/Backends/backend_info.hpp"
#include "gambit/Logs/logger.hpp"

#ifdef HAVE_MATHEMATICA
  #include MATHEMATICA_WSTP_H
#endif

#ifdef HAVE_PYBIND11
  #include <pybind11/embed.h>
#endif

#ifdef HAVE_LINK_H
  #include <link.h>
#endif


namespace Gambit
{

  // Public method definitions for backend_info class

  /// Constructor
  Backends::backend_info::backend_info()
   : filename(GAMBIT_DIR "/config/backend_locations.yaml")
   , default_filename(GAMBIT_DIR "/config/backend_locations.yaml.default")
   #ifdef HAVE_PYBIND11
     , python_started(false)
   #endif
  {
    // Attempt to read user yaml configuration file
    try
    {
      bepathfile = YAML::LoadFile(filename);
      logger() << LogTags::backends << LogTags::debug << "Successfully loaded custom user backend location file "
               << filename << "." << EOM;
      custom_bepathfile_exists = true;
    }
    catch (YAML::Exception &e)
    {
      logger() << LogTags::backends << LogTags::debug << "Custom user backend location file " << filename
               << " could not be read; employing default only." << EOM;
      custom_bepathfile_exists = false;
    }
    // Attempt to read default yaml configuration file
    try
    {
      default_bepathfile = YAML::LoadFile(default_filename);
      logger() << LogTags::backends << LogTags::debug << "Successfully loaded default backend location file "
               << default_filename << "." << EOM;
    }
    catch (YAML::Exception &e)
    {
      std::ostringstream msg;
      msg << "Could not read default backend locations file \""<<filename<<"\"!" << endl;
      msg << "Please check that file exists and contains valid YAML." << endl;
      msg << "("<<e.what()<<")";
      backend_error().raise(LOCAL_INFO,msg.str());
    }
  }

  /// Destructor
  Backends::backend_info::~backend_info()
  {
    #ifdef HAVE_PYBIND11
      if (python_started)
      {
        for (auto it = loaded_python_backends.begin();
                  it != loaded_python_backends.end();
                  it++)
        {
          delete it->second;
        }
        delete python_interpreter;
      }
    #endif
  }

  /// Indicate whether a custom backend locations file exists
  bool Backends::backend_info::custom_locations_exist() const
  {
    return custom_bepathfile_exists;
  }

  /// Return the path to any custom user backend locations file
  str Backends::backend_info::backend_locations() const
  {
    return filename;
  }

  /// Return the path to the default backend locations file
  str Backends::backend_info::default_backend_locations() const
  {
    return default_filename;
  }

  /// Return the path to a backend library, given a backend name and version.
  str Backends::backend_info::path(str be, str ver) const
  {
    const str default_path("no path in config/backend_locations.yaml.default");
    str p;
    auto be_it = bepathoverrides.find(be);
    bool override_present = (be_it != bepathoverrides.end());
    if (override_present)
    {
      auto ver_it = be_it->second.find(ver);
      if (ver_it != be_it->second.end())
      {
        p = ver_it->second;
        if (p.substr(0,2) == "./") p = p.substr(2,p.npos);
      }
      else
      {
        override_present = false;
      }
    }
    if (not override_present)
    {
      if (custom_bepathfile_exists and bepathfile[be] and bepathfile[be][ver])
      {
        p = bepathfile[be][ver].as<str>();
        if (p.substr(0,2) == "./") p = p.substr(2,p.npos);
      }
      else
      {
        if (default_bepathfile[be] and default_bepathfile[be][ver])
        {
          p = default_bepathfile[be][ver].as<str>();
          if (p.substr(0,2) == "./") p = p.substr(2,p.npos);
        }
        else
        {
          p = default_path;
          static bool warning_raised = false;
          if (not warning_raised)
          {
            std::ostringstream msg;
            msg << "Could not find path for backend "<< be <<" v" << ver << endl;
            msg << "in " << default_filename;
            if (custom_bepathfile_exists) msg << " nor in " << filename;
            msg << "." << endl;
            msg << "Setting path to \"" << default_path << "\".";
            backend_warning().raise(LOCAL_INFO,msg.str());
            warning_raised = true;
          }
        }
      }
    }
    return p;
  }

  /// Return the complete path to a backend library, given a backend name and version.
  str Backends::backend_info::corrected_path(str be, str ver) const
  {
    str p = path(be,ver);
    if (p.substr(0,1) != "/")
    {
      p = GAMBIT_DIR "/"+p;
    }
    return p;
  }

  /// Return the path to the folder in which a backend library resides
  str Backends::backend_info::path_dir(str be, str ver) const
  {
    str p = corrected_path(be,ver);
    for (int i = p.length()-1; i >= 0; --i)
    {
      if (p[i] == '/') return p.substr(0,i);
    }
    return p;
  }

  /// Return the bare name of the library of a backend library, with no path or extension
  str Backends::backend_info::lib_name(str be, str ver) const
  {
    str p = corrected_path(be,ver);
    int i, end = p.length();
    for (i = end-1; i >= 0; --i)
    {
      if (p[i] == '.') end = i-1;
      if (p[i] == '/') break;
    }
    return p.substr(i+1,end-i);
  }

  /// Given a backend and a safe version (with no periods), return the true version
  str Backends::backend_info::version_from_safe_version (str be, str sv) const
  {
    return safe_version_map.at(be).first.at(sv);
  }

  /// Given a backend and a true version (with periods), return the safe version
  str Backends::backend_info::safe_version_from_version (str be, str v) const
  {
    return safe_version_map.at(be).second.at(v);
  }

  /// Link a backend's version and safe version
  void Backends::backend_info::link_versions(str be, str v, str sv)
  {
    safe_version_map[be].first[sv] = v;
    safe_version_map[be].second[v] = sv;
  }

  /// Override a backend's config file location
  void Backends::backend_info::override_path(const str& be, const str& ver, str path)
  {
    int l = str(GAMBIT_DIR).length();
    if (path.substr(0,l) == GAMBIT_DIR) path.replace(0, l, ".");
    bepathoverrides[be][ver] = path;
  }

  /// Get the default version of a BOSSed backend.
  str Backends::backend_info::default_version(const str& be) const
  {
    if (default_safe_versions.find(be) == default_safe_versions.end())
    {
      std::ostringstream msg;
      msg << "The backend \"" << be << "\" does not contain any classes for loading, "
          << endl << "and therefore has no default version.";
      backend_error().raise(LOCAL_INFO, msg.str());
    }
    return version_from_safe_version(be,default_safe_versions.at(be));
  }

  /// Get all versions of a given backend that are successfully loaded.
  std::vector<str> Backends::backend_info::working_versions(const str& be)
  {
    std::vector<str> working_versions;
    // Retrieve the versions known of the given backend.
    if (safe_version_map.find(be) == safe_version_map.end())
    {
      std::ostringstream msg;
      msg << "The backend \"" << be << "\" is not known to GAMBIT.";
      backend_error().raise(LOCAL_INFO, msg.str());
    }
    std::map<str,str> versions = safe_version_map[be].second;
    // Iterate over all known versions of the given backend, retaining only those that work.
    for (auto it = versions.begin(); it != versions.end(); ++it)
    {
      if (works.at(be + it->first)) working_versions.push_back(it->first);
    }
    return working_versions;
  }


  /// Get all safe versions of a given backend that are successfully loaded.
  std::vector<str> Backends::backend_info::working_safe_versions(const str& be)
  {
    // Get the working versions, then iterate over them and convert them to safe versions.
    std::vector<str> safe_versions;
    const std::vector<str> versions = working_versions(be);
    for (auto it = versions.begin(); it != versions.end(); ++it)
    {
      safe_versions.push_back(safe_version_from_version(be, *it));
    }
    return safe_versions;
  }


  /// Try to resolve a pointer to a partial path to a shared library and use it to override the stored backend path.
  void Backends::backend_info::attempt_backend_path_override(const str& be, const str& ver, const char* name)
  {
    char *fullname = realpath(name, NULL);
    if (not fullname)
    {
      std::ostringstream err;
      err << "Problem retrieving absolute library path for " << be << " v" << ver << "." << endl
          << "The path to this library has not been fully determined.";
      backend_warning().raise(LOCAL_INFO,err.str());
    }
    else
    {
      override_path(be, ver, fullname);
    }
    free(fullname);
  }


  /// Attempt to load a backend library.
  int Backends::backend_info::loadLibrary(const str& be, const str& ver, const str& sv, bool with_BOSS, const str& lang)
  {
    try
    {
      // Initialize variable to avoid issues later
      needsMathematica[be+ver] = false;
      needsPython[be+ver] = false;
      classloader[be+ver] = false;
      missingPythonVersion[be+ver] = -1;

     // Now switch according to the language of the backend
      if (lang == "MATHEMATICA"
       or lang == "Mathematica")
      {
        needsMathematica[be+ver] = true;
        // And switch according to whether the language has its dependencies met or not
        #ifdef HAVE_MATHEMATICA
          loadLibrary_Mathematica(be, ver, sv);
        #else
          works[be+ver] = false;
          std::ostringstream err;
          err << "Backend requires Mathematica and WSTP, but one of them is not found in the system. "
              << "Please install/buy Mathematica and/or WSTP before using this backend." << endl;
          backend_warning().raise(LOCAL_INFO, err.str());
        #endif
      }
      // and so on.
      else if (lang == "PYTHON" or lang == "Python" or
               lang == "PYTHON2" or lang == "Python2" or
               lang == "PYTHON3" or lang == "Python3")
      {
        needsPython[be+ver] = true;
        #ifdef HAVE_PYBIND11
          loadLibrary_Python(be, ver, sv, lang);
        #else
          works[be+ver] = false;
          std::ostringstream err;
          err << "GAMBIT requires pybind11 to interface with Python, but it was not found in "
              << "the system. Please install it before using this backend." << endl
              << "You can do this with 'make pybind11' from the GAMBIT build directory." << endl;
          backend_warning().raise(LOCAL_INFO, err.str());
        #endif
      }
      else if (lang == "C"
            or lang == "C++"
            or lang == "CC"
            or lang == "CXX"
            or lang == "CPP"
            or lang == "F90"
            or lang == "F95"
            or lang == "F2003"
            or lang == "FORTRAN"
            or lang == "Fortran")
      {
        loadLibrary_C_CXX_Fortran(be, ver, sv, with_BOSS);
      }
      else
      {
        std::ostringstream err;
        err << "Unrecognised/unsupported backend language: " << lang << endl;
        err << "Issue comes from " << be << " " << ver << endl;
        backend_error().raise(LOCAL_INFO, err.str());
      }

    }

    catch (std::exception& e)
    {
      std::cout << "GAMBIT has failed to initialise due to fatal exception when trying to load backends: " << e.what() << std::endl;
      throw(e);
    }

    return 0;
  }


  /// Load a backend library written in C, C++ or Fortran.
  void Backends::backend_info::loadLibrary_C_CXX_Fortran(const str& be, const str& ver, const str& sv, bool with_BOSS)
  {
    const str path = corrected_path(be,ver);
    link_versions(be, ver, sv);
    classloader[be+ver] = with_BOSS;
    needsMathematica[be+ver] = false;
    needsPython[be+ver] = false;

    if (with_BOSS) classes_OK[be+ver] = true;
    void* pHandle = dlopen(path.c_str(), RTLD_LAZY);
    if (pHandle)
    {
      // If dlinfo is available, use it to verify the path of the backend that was just loaded.
      #ifdef HAVE_LINK_H
        link_map *map;
        dlinfo(pHandle, RTLD_DI_LINKMAP, &map);
        if (not map)
        {
          std::ostringstream err;
          err << "Problem retrieving library path.  The sought lib is " << path << "." << endl
              << "The path to this library has not been fully verified.";
          backend_warning().raise(LOCAL_INFO,err.str());
        }
        else
        {
          attempt_backend_path_override(be, ver, map->l_name);
        }
      #else
        override_path(be, ver, ".so loaded but path unverified (system lacks dlinfo)");
      #endif
      logger() << "Succeeded in loading " << corrected_path(be,ver)
               << LogTags::backends << LogTags::info << EOM;
      works[be+ver] = true;
      loaded_C_CXX_Fortran_backends[be+ver] = pHandle;
    }
    else
    {
      std::ostringstream err;
      str error = dlerror();
      dlerrors[be+ver] = error;
      err << "Failed loading library from " << path << " due to: " << endl
          << error << endl
          << "All functions in this backend library will be disabled (i.e. given status = -1).";
      backend_warning().raise(LOCAL_INFO,err.str());
      works[be+ver] = false;
    }
  }


  #ifdef HAVE_MATHEMATICA

    /// Load WSTP for Mathematica backends
    void Backends::backend_info::loadLibrary_Mathematica(const str& be, const str& ver, const str& sv)
    {
      const str path = corrected_path(be,ver);
      link_versions(be, ver, sv);
      classloader[be+ver] = false;
      needsMathematica[be+ver] = true;
      needsPython[be+ver] = false;

      int WSerrno;
      WSLINK pHandle;
      std::ostringstream err;

      // If the file does not exists do not wait for Mathematica to figure it out
      std::ifstream f(path.c_str());
      if(!f.good())
      {
        err << "Failed loading Mathematica package; package not found at " << path << endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        works[be+ver] = false;
        return;
      }

      // This initializes WSTP library functions.
      WSENV WSenv = WSInitialize(0);
      if(WSenv == NULL)
      {
        err << "Unable to initialize WSTP environment" << endl;
        backend_warning().raise(LOCAL_INFO,err.str());
        works[be+ver] = false;
        return;
      }

      // This opens a WSTP connection
      std::stringstream WSTPflags;
      #ifdef __APPLE__
        WSTPflags << "-linkname " << MATHEMATICA_KERNEL << " -mathlink";
      #else
        WSTPflags << "-linkname math -mathlink";
      #endif

      pHandle = WSOpenString(WSenv, WSTPflags.str().c_str(), &WSerrno);
      if(pHandle == NULL || WSerrno != WSEOK)
      {
        err << "Unable to create link to the Kernel" << endl;
        backend_warning().raise(LOCAL_INFO,err.str());
        backend_warning().raise(LOCAL_INFO, WSErrorMessage(pHandle));
        works[be+ver] = false;
        WSNewPacket(pHandle);
        return;
      }

      // Tell WSTP to load up the Mathematica package of the backend
      if(!WSPutFunction(pHandle, "Once", 1)
           or !WSPutFunction(pHandle, "Get", 1)
           or !WSPutString(pHandle, path.c_str())
           or !WSEndPacket(pHandle))
      {
        err << "Error sending packet through WSTP" << endl;
        backend_warning().raise(LOCAL_INFO,err.str());
        backend_warning().raise(LOCAL_INFO, WSErrorMessage(pHandle));
        works[be+ver] = false;
        WSNewPacket(pHandle);
        return;
      }

      // Jump to the end of this packet, discarding all output
      // We do not care about errors here because the package exists
      int pkt;
      while( (pkt = WSNextPacket(pHandle), pkt) && pkt != RETURNPKT)
        WSNewPacket(pHandle);

      logger() << "Succeeded in loading " << corrected_path(be,ver)
               << LogTags::backends << LogTags::info << EOM;
      works[be+ver] = true;
      loaded_mathematica_backends[be+ver] = pHandle;
      WSNewPacket(pHandle);

      //TODO: Add this to die functions
      //WSPutFunction(pHandle, "Exit", 0);
      //WSClose(pHandle);
      //WSDeinitialize(WSenv);
    }

  #endif


  #ifdef HAVE_PYBIND11

    /// Load a Python backend module
    void Backends::backend_info::loadLibrary_Python(const str& be, const str& ver, const str& sv, const str& lang)
    {
      // Set the internal info for this backend
      const str path = corrected_path(be,ver);
      link_versions(be, ver, sv);

      // Bail now if the backend is not present.
      std::ifstream f(path.c_str());
      std::ostringstream err;
      if(!f.good())
      {
        err << "Failed loading Python backend; source file not found at " << path << endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        works[be+ver] = false;
        return;
      }

      // Bail now if the backend requires a version of Python that GAMBIT is not configured with.
      if (PYTHON_VERSION_MAJOR < 2 or PYTHON_VERSION_MAJOR > 3)
      {
        err << "Unrecognised version of Python: " << PYTHON_VERSION_MAJOR << endl;
        backend_error().raise(LOCAL_INFO, err.str());
        works[be+ver] = false;
        return;
      }
      if (PYTHON_VERSION_MAJOR != 2 and (lang == "Python2" or lang == "PYTHON2"))
      {
        err << "Failed loading Python backend " << be << " " << ver << "." << endl
            << "GAMBIT was configured with Python " << PYTHON_VERSION_MAJOR << " but this backend needs Python 2." << endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        works[be+ver] = false;
        missingPythonVersion[be+ver] = 2;
        return;
      }
      if (PYTHON_VERSION_MAJOR != 3 and (lang == "Python3" or lang == "PYTHON3"))
      {
        err << "Failed loading Python backend " << be << "." << endl
            << "GAMBIT was configured with Python " << PYTHON_VERSION_MAJOR << " but this backend needs Python 3." << endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        works[be+ver] = false;
        missingPythonVersion[be+ver] = 3;
        return;
      }

      // Fire up the Python interpreter if it hasn't been started yet.
      if (not python_started) start_python();

      // Add the path to the backend to the Python system path
      pybind11::object sys_path = sys->attr("path");
      pybind11::object sys_path_insert = sys_path.attr("insert");
      sys_path_insert(0,path_dir(be, ver));

      // Attempt to import the module
      const str name = lib_name(be, ver);
      pybind11::module* new_module;
      try
      {
        new_module = new pybind11::module(pybind11::module::import(name.c_str()));
      }
      catch (std::exception& e)
      {
        err << "Failed to import Python module from " << path << "." << endl
            << "Python error was: " << e.what() << endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        works[be+ver] = false;
        return;
      }

      // Check if the loaded moule has actually come from the expected path.
      // First get the relevant os functions.
      pybind11::object os_path = os->attr("path");
      pybind11::object os_path_split = os_path.attr("split");
      // Get the path to the loaded module (Split the path at the last '/')
      pybind11::tuple full_loaded_path = os_path_split( new_module->attr("__file__") );
      // For Python modules with an underlying '__init__.py' script we need to repeat this split step
      if ((full_loaded_path[1]).cast<str>().find("__init__") != str::npos)
        full_loaded_path = os_path_split(full_loaded_path[0]);

      // Compare the expected and the actual location. If they differ, declare the module as broken.
      const str loaded_loc = (full_loaded_path[0]).cast<str>();
      const str expected_loc = path_dir(be,ver);
      if (loaded_loc.compare(expected_loc) != 0)
      {
        err << "Failed to import Python module from " << path << "." << endl
            << "A module with the same name was loaded but its location is not what is expected" << endl
            << "Got: " << loaded_loc << " (expected: " << expected_loc << ")" << endl;
        backend_warning().raise(LOCAL_INFO, err.str());
        works[be+ver] = false;
        return;
      }

      // Remove the path to the backend from the Python system path
      pybind11::object sys_path_remove = sys_path.attr("remove");
      sys_path_remove(path_dir(be, ver));

      logger() << "Succeeded in loading " << path << LogTags::backends << LogTags::info << EOM;
      works[be+ver] = true;
      loaded_python_backends[be+ver] = new_module;
    }

    /// Fire up the Python interpreter
    void Backends::backend_info::start_python()
    {
      // Create an instance of the interpreter.
      python_interpreter = new pybind11::scoped_interpreter;
      // Import the sys module, and save a wrapper to it for later.
      static pybind11::module local_sys = pybind11::module::import("sys");
      sys = &local_sys;
      // Import the os module, and save a wrapper to it for later.
      static pybind11::module local_os = pybind11::module::import("os");
      os = &local_os;

      logger() << LogTags::backends << LogTags::debug << "Python interpreter successfully started." << EOM;
      python_started = true;
    }

    pybind11::module& Backends::backend_info::getPythonBackend(const str& be, const str& ver)
    {
      static pybind11::module empty_python_module;
      return (works.at(be+ver) ? *loaded_python_backends.at(be+ver) : empty_python_module);
    }

  #endif

}
