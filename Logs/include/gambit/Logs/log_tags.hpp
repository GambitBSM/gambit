//   GAMBIT: Global and Modular BSM Inference Tool
//   *********************************************
///  \file
///
///  Headeer for logging classes
///
///  *********************************************
///
///  Authors (add name and date if you modify):
///   
///  \author Ben Farmer
///          (benjamin.farmer@monash.edu.au)
///  \date 2014 Mar
///
///  \author Pat Scott
///          (patscott@physics.mcgill.ca)
///  \date 2014 Mar
///
///  *********************************************

#ifndef __log_tags_hpp__
#define __log_tags_hpp__

namespace Gambit
{

  // CAREFUL! These logging enum tags might clash with other names in the Gambit namespace! Be careful when adding new ones.
  // If you add a new tag, be sure to also add it to one of the tag category sets defined in logging.cpp as well.
  namespace LogTags
  {

    enum LogTag_declaration
    {
      /* Message tags */
      debug=0,
      info,
      warn,
      err,
      /* Flags */
      fatal,
      nonfatal,
      /* Echoes */
      repeat_to_cout,
      repeat_to_cerr,
      /* Component tags */
      def,
      core,
      logs,
      models,
      dependency_resolver,
      scanner,
      inifile,
      printers,
      utils,
      backends
      /* etc... */
    };

  }
 
  // Typedef to make usage of this enum type less cumbersome
  typedef LogTags::LogTag_declaration LogTag;

}

#endif //#ifndef __log_tags_hpp__
 
