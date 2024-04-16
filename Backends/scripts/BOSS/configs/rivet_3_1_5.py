###################################
#                                 #
#  Configuration module for BOSS  #
#                                 #
###################################


# ~~~~~ CASTXML options ~~~~~

# See CastXML documentation for details on these options:
#
#   https://github.com/CastXML/CastXML/blob/master/doc/manual/castxml.1.rst
#

#
# *** Special note for OS X *** 
# 
# BOSS will most likely fail if 'g++' points to the Clang compiler.
# Install GNU g++ and point the castxml_cc variable below the GNU 
# g++ executable.   
#

castxml_cc_id  = 'gnu'         # Reference compiler: 'gnu', 'gnu-c', 'msvc', 'msvc-c'
castxml_cc     = 'g++'         # Name a specific compiler: 'g++', 'cl', ...
castxml_cc_opt = '-std=c++11'  # Additional option string passed to the compiler in castxml_cc (e.g. '-m32')


# ~~~~~ GAMBIT-specific options ~~~~~

gambit_backend_name    = 'Rivet'
gambit_backend_version = '3.1.5'
gambit_backend_reference = 'Bierlich:2019rhm'
gambit_base_namespace  = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

input_files = [
    '../../../Backends/installed/rivet/'+gambit_backend_version+'/include/Rivet/AnalysisHandler.hh',
    '../../../Backends/installed/rivet/'+gambit_backend_version+'/include/Rivet/Tools/RivetPaths.hh'
]
include_paths = [
    '../../../Backends/installed/rivet/'+gambit_backend_version+'/include',
    '../../../contrib/HepMC3-3.2.5/local/include',
    '../../../contrib/YODA-1.9.7/local/include',
    '../../../Backends/installed/fastjet/3.3.2/local/include'
]
base_paths = ['../../../Backends/installed/rivet/'+gambit_backend_version]

header_files_to = '../../../Backends/installed/rivet/'+gambit_backend_version+'/include'
src_files_to    = '../../../Backends/installed/rivet/'+gambit_backend_version+'/src/Core'

load_classes = [
    'Rivet::AnalysisHandler'
]

load_functions = [
    'Rivet::addAnalysisLibPath(const std::string&)'
]

ditch = [
    'Rivet::AnalysisHandler::stripOptions',
    'Rivet::AnalysisHandler::getPreload'
]


auto_detect_stdlib_paths = False


load_parent_classes    = False
wrap_inherited_members = False


header_extension = '.hh'
source_extension = '.cc'

indent = 3


# ~~~~~ Information about other known types ~~~~~

# Dictionary key: type name
# Dictionary value: header file with containing type declaration.
#
# Example:
#   known_classes = {"SomeNamespace::KnownClassOne" : "path_to_header/KnownClassOne.hpp",
#                    "AnotherNamespace::KnownClassTwo" : "path_to_header/KnownClassTwo.hpp" }

known_classes = {
      "HepMC3::GenEvent" : "HepMC3/GenEvent.h",
      "YODA::AnalysisObject" : "YODA/AnalysisObject.h"
}


# ~~~~~ Declarations to be added to the frontend header file ~~~~~

convenience_functions = []

ini_function_in_header = False


# ~~~~~ Pragma directives for the inclusion of BOSSed classes in GAMBIT ~~~~~

# The listed pragma directives will be added before/after including the
# the BOSS-generated headers in GAMBIT.

pragmas_begin = [
  '#include "gambit/Utils/begin_ignore_warnings_rivet_backend.hpp"', # Contains pragmas to suppress warnings from YODA and HepMC
]

pragmas_end = [
  '#include "gambit/Utils/end_ignore_warnings.hpp"', # Restores the warning settings
]


# ~~~~~ Extra code to surround BOSS-generated code included in GAMBIT ~~~~~

# The listed code will be added at the top/bottom in the frontend header file 
# and in the loaded_types.hpp header.

surround_code_begin = '''
#ifndef EXCLUDE_YODA
#ifndef EXCLUDE_HEPMC
'''

surround_code_end = ''' 
#endif
#endif
'''
