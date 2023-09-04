//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Exception objects required for standalone
///  compilation.
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Pat Scott 
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************

#include "gambit/Utils/standalone_error_handlers.hpp"
#include "gambit/Logs/log_tags.hpp"

namespace Gambit
{

  using namespace LogTags;

  /// Utility errors
  error& utils_error()
  { 
    static error local("A problem has been raised by one of the utility codes.","utils_error", utils); 
    return local;
  }

  /// Utility warnings
  warning& utils_warning()
  { 
    static warning local("A problem has been raised by one of the utility codes.","utils_warning", utils); 
    return local;
  }

  /// Backend errors
  error& backend_error()
  { 
    static error local("A problem has been raised by the backend system.","backend_error", backends); 
    return local;
  }

  /// Backend warnings
  warning& backend_warning()
  { 
    static warning local("A problem has been raised by the backend system.","backend_warning", backends); 
    return local;
  }

  /// Logging errors
  error& logging_error()
  { 
    static error local("A problem has occurred in the logging utilities.","logging_error", logs); 
    return local;
  }

  /// Logging warnings
  warning& logging_warning()
  { 
    static warning local("A problem has occurred in the logging utilities.","logging_warning", logs); 
    return local;
  }

  /// Model errors
  error& model_error()
  {
    static error local("A problem has been encountered in the model subsystem.","model_error", models);
    return local;
  }

  /// Model warnings
  warning& model_warning()
  {
    static warning local("A problem has been encountered in the model subsystem.","model_warning", models);
    return local;
  }

  /// Invalid point exceptions
  invalid_point_exception& invalid_point()
  {
    static invalid_point_exception local;
    return local;
  }

  namespace Printers
  {

    /// Printer errors
    error& printer_error()
    { 
      static error local("A problem has occurred in the printer utilities.","printer_error", printers); 
      return local;
    }

    /// Printer warnings
    warning& printer_warning()
    { 
      static warning local("A problem has occurred in the printer utilities.","printer_warning", printers); 
      return local;
    }

  }
  
  namespace IniParser
  {

    /// IniFile errors
    error& inifile_error()
    {
      static error local("A problem has been encountered in the iniFile reader subsystem.","inifile_error", inifile);
      return local;
    }

    /// IniFile warnings
    warning& inifile_warning()
    {
      static warning local("A problem has been encountered in the iniFile reader subsystem.","inifile_warning", inifile);
      return local;
    }

  }

    
}

