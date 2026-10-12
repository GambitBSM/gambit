How to make a scanner plugin.

Introduction to Gambit plugins:

-- Plugin are self-contained pieces of code that are compiled
   in separate objects external to Gambit itself.  At runtime,
   ScannerBit selects and loads the appropriate plugins based
   on inifile entries.  The plugin themselves can be used for
   a wide variety of purposes.  "scanner_plugin"s specify
   a plugin that will be used as a scanner whereas "objective_plugin"s
   are general use plugins that can be used as test functions,
   likelihoods, priors, etc.  Below is an discription and instructions
   for these plugins.

Sections:

-- Plugin Declaration Section
-- Plugin Compilation Section
-- Plugin IniFile Section
-- External Compilation

**********************************************************************
**************** PLUGIN DECLARATION SECTION **************************
**********************************************************************

Example:

-- Lets start with an example of a scanner plugin, after which
   I'll explain what each macro does.  The relevant inifile
   entry is included at the end.

Quick discription of this example:

-- This example declares a scanner named "my_cool_scanner" of
   version "0.0.0-beta".  Inside it, it declares a "like_ptr"
   (named "loglike") which is a function of the form
   "double (const vector<double> &)", int num which
   will be set to the inifile entry "number", and an int
   "dim" which will be set to the dimension.  The actual
   scanner will be ran in "int plugin_main()".

////////////////////// START PLUGIN DECLARATION ///////////////////////////

#include "scanner_plugin.hpp"

/* declare a plugin of name "my_cool_scanner" of version "0.0.0-beta" */
scanner_plugin(my_cool_scanner, version(0, 0, 0, beta))
{
   /* specify that the entry "number" is required by gambit. */
   reqd_inifile_entries("number");

   /* tell gambit to look for the library "my_cool_library" */
   reqd_libraries("my_cool_library");

   /* tell gambit that the file "my_cool_header.h" is needed
      to compile this plugin.*/
   reqd_include_paths("my_cool_header.h");

   /* declare a scanner function "loglike" that inputs
      a "std::vector<double> &" and outout a "double" */
   like_ptr<double (const std::vector<double> &)> loglike;

   int num, dim;

   /* this macro runs when the plugin is loaded */
   plugin_constructor
   {
      /* Get a functor corresponding to the purpose "Likelihood" */
      likelihood = get_purpose("Likelihood");

      /* get the inifile entry "number" with the default value of "0" */
      num = get_inifile_value<int>("number", 0);

      /* get the dimension of the parameter space. */
      dim = get_dimension();
   }

   /* main function that will run the scanner. */
   int plugin_main(void)
   {
      std::vector<double> a(dim);
      for (int j = 0; j < num; j++)
      {
         for (int i = 0; i < ma; i++)
         {
            a[i] = Gambit::Random::draw();
         }
         loglike(a);
      }

      return 0;
   }

   /* this runs when the plugin is closed */
   plugin_deconstructor
   {
      std::cout << "no more plugin" << std::endl;
   }
}

///////////////////// END PLUGIN DECLARATION ///////////////////////////

******************** Plugin Commands **************************

Here are the different macros and functions that can be used:

scanner_plugin(plugin_name, version) {...}
-- declared a plugin with the name "plugin_name" of
   version "version".

objective_plugin(plugin_name, version) {...}
-- same as above, except declares an "objective" plugin.
   Used as test functions and prior plugins.

version(majar, minor, patch, release)
-- declares the version number to be "major.minor.patch-release"
   major, minor, and patch must be integers.  release is optional.

ret plugin_main(args... params) {...}
-- The function that is called when the plugin is ran.  For the
   scanner, it must be of the form "int plugin_name(void)"

plugin_constructor {...}
-- This function will be ran when the plugin to loaded.

plugin_deconstructor {...}
-- This function will be ran when the plugin to closed.

get_inifile_value<ret_type>("tag", default);
-- Gets the inifile value corresponding to the tag "tag".
   If "tag" is not specified, then the results defaults
   to "default".  The default entry is optional. If
   the default entry and the "tag" infile entry is not
   specified, ScannerBit will throw an error.

get_dimension()
-- Gets the dimension of the unit hypercube being explored.

get_purpose("purpose")
-- gets the functor corresponding to the purpose "purpose"

printer_interface &get_printer()
-- gets the printer interface. See printer command subsection.

like_ptr<ret (args...)>
-- a container functor of the form "ret like_ptr(args ...)".
   Used to contain the output of "get_purpose".

void set_resume_params(...)
-- tells ScannerBit which parameters need to be resume
   on resume.

set_dimension(...)
-- For objective plugins that will be used as priors.
   Set the hypercube dimension that will be operator
   over by the prior.

reqd_inifile_entries(...)
-- Tells ScannerBit that there entries must be in the inifile
   in order to load the plugin

reqd_libraries(...)
-- Tells ScannerBit to search for and link these libraries

reqd_headers(...)
-- Tells ScannerBit that these headers are required to exist
   in order for the plugin to compile.

cxx_flags(...)
-- Tells ScannerBit to compile this plugin with the flags specified.

**************** end plugin commands *******************

***************** printer commands *********************

There are two printer classes that ScannerBit interacts with.
All of these classes are within the Gambit::Scanner namespace.

printer_interface
-- class that interfaces with the printer system.

member functions:
  printer *get_stream(const std::string& name = "")
  -- gets the printer stream that corresponds to the name "name".
     if no name is specified, the main printer is returned.

  bool resume_mode()
  -- return true is in resume mode.

  void new_stream(const std::string& name, const Options& option)
  -- create a new stream named "name" with options "option".

printer
-- class that does the actual printing.

member functions:
  void reset(bool force=false)
  -- deletes output that was already in the stream.  When force
     is set to true, the main printer may be reset.

  void print(value, const std::string &param_name, int rank, ulonglong id)
  -- prints "value" of param_name with point id "id" and MPI rank "rank".

void assign_aux_numbers (...)
-- function that ensures that the specified params are MPI thread safe.

***************** end printer *********************

***************** functor commands *********************

Each functor generated by get_purpose has various useful member
functions.  For the above example, the following functions are
available:

loglike->getPurpose()
-- returns the purpose.

loglike->getRank()
-- returns the MPI rank.

loglike->getPtID()
-- returns the current point id.

***************** end functor commands *********************

***************************************************************
************* END PLUGIN DECLARATION SECTION ******************
***************************************************************

***************************************************************
*************** PLUGIN COMPILATION SECTION ********************
***************************************************************

compiling with gambit:

-- The suggested method of compiling is to use the internal
   Gambit compilation tools.  To do so, make a source
   directory in the ScannerBit/src/scanners or ScannerBit/src/objectives
   folders and, if need be, make the corresponding include directory
   of the same name in ScannerBit/include/scanners or
   ScannerBit/include/objectives.  Then, move your source and
   include files into these directories.

   In the example above, the commands would be

   mkdir ./ScannerBit/src/scanners/my_cool_scanner
   mkdir ./ScannerBit/include/scanners/my_cool_scanner
   mv my_cool_source.cpp ./ScannerBit/src/scanners/my_cool_scanner/
   mv my_cool_header.h ./ScannerBit/include/scanners/my_cool_scanner/

linking external libraries:

-- If you want to link external libraries to your plugin
   or use an external include path, you may specify
   these in config/scanner_locations.yaml or
   config/objective_locations.yaml with the line:

   my_plugin_name:
     version:
       - lib: path_to_my_external_library
       - inc: my_include_path

   for example, in the example above we'd include

   my_cool_scanner:
     0.0.0-beta:
       - lib: ./libmy_cool_library.so
       - inc: ./my_cool_path

   in config/scanner_locations.yaml.

-- Note that if you link to an external library, you must
   include the "reqd_libraries" function in the plugin declaration.
   For example, in the example above, the plugin declaration would be:

   scanner_plugin(my_cool_scanner, version(0, 0, 0, beta))
   {
     req_libraries();
   }

   Optionally, You can specify library names in the "reqd_libraries".
   If you do you, gambit will try to find these libraries for
   you.  In the above example, this would be:

   scanner_plugin(my_cool_scanner, version(0, 0, 0, beta))
   {
     req_libraries("my_cool_library");
   }

requiring existence of files to compile:

-- You can also specify that a certain file must be found in
   order to compile.  This is done with the "reqd_headers"
   function:

   scanner_plugin(my_cool_scanner, version(0, 0, 0, beta))
   {
     reqd_headers("my_cool_header.h");
   }

   In the above example, "my_cool_scanner" will not to compiled
   unless "my_cool_header.h" is found.

*************************************************************
************* END PLUGIN COMPILATION SECTION ****************
*************************************************************

*************************************************************
*************** PLUGIN INIFILE SECTION **********************
*************************************************************

Here is an example of an inifile entry for a scanner.

#################### inifile entries ####################

Scanner:

  use_scanner_plugin: my_plugin_tag

  plugins:

    my_plugin_tag:
      plugin: my_cool_scanner
      options:
        number: 1

#################### end infile entry ###################

description:
-- The plugins are declared under the "plugins" tag in the
   scanner section.  Each plugin is specified by an unique
   tag (in this case "my_plugin_tag").  The plugin name is
   specified by the "plugin" tag.  The options for that
   plugin either specified under the plugin tag or the
   "options" tag.  The "use_scanner_plugin" tag is used to
   specify which scanner to use.

***** Available tags that can be used under plugin tags *****

plugins:
-- declares plugin name (not optional).

options:
-- section where the plugin options are specified (optional).

purpose:
-- for Objective plugins:  specifies the purpose associated
   with the plugin.

*************************************************************

*** Available tags that can be used under the Scanner tag ***

use_scanner_plugin:
-- specifies the tag corresponding to the scanner plugin that
   is going to me used.

use_objective_plugins:
-- specifies the plugin or plugins that scannerbit is going
   to use.

*************************************************************

*********** specifying required inifile entries *************

-- You can specify required inifile entries with the function
   "reqd_inifile_entries(...)".  If you do, ScannerBit will
   not load the plugin if these inifile entries are not specified.
   In the above example, this is:

   scanner_plugin(my_cool_scanner, version(0, 0, 0, beta))
   {
     req_inifile_entries("example");
   }

*************************************************************
************* END PLUGIN INIFILE SECTION ********************
*************************************************************

*************************************************************
************ EXTERNAL COMPILATION SECTION *******************
*************************************************************

-- Because of Gambit's compilation tools, it is highly recommended
   to compile with gambit.  But there may be situations where
   compilation is too compilated or specialized to included
   as part of gambit.  Although, this method is not supported
   by the Gambit collaboration.  But, in such cases, ScannerBit
   provides a nifty "scanlibs" commandline tool and well as
   a plugin inifile convenance tag, "plugin_path:" for specifying
   external plugins that are stored external to gambit.

   For example, to compile externally, run:

   g++ `path_to_gambit/ScannerBit/bin/scanlibs --hdrs --cflags` sources.cpp -o plugins.so

   or on an intel compiler:

   icc `path_to_gambit/ScannerBit/bin/scanlibs --hdrs --cflags --intel` ...

-- Example:  statically linking directly to a plugin.
   By default, Gambit links static executables to the main
   executable.  But if the library is compiled with position
   independent code (with -fPIC), it is possible to statically
   link directly to the plugin.  To do this, first compile your
   plugin code with:

   g++ `./ScannerBit/bin/scanlibs --hdrs --boost` -c --std=c++11 plugin_src.cpp

   and then link with:

   g++ -shared -Wl,--whole-archive libconflict.a -Wl,--no-whole-archive plugin_src.o -o libmyplugin.so

-- For covenance, if your plugin object is not placed in
   in the ScannerBit/lib directory, you make specify the path
   to a plugin external to Gambit under the plugin tag
   for your specific scanner in the infile.  This is done
   with the sub-tag "plugin_path:":


# example infile entry:

Scanner:

  plugins:

    my_plugin_tag:
      plugin: my_external_plugin
      plugin_path: path_to_my_external_plugin/libplugin.so

# end example infile entry

*************************************************************
********** END EXTERNAL COMPILATION SECTION *****************
*************************************************************
