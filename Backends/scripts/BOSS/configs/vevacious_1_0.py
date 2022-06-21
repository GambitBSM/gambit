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

gambit_backend_name    = 'vevacious'
gambit_backend_version = '1.0'
gambit_base_namespace  = ''
gambit_minuit_version  = '5.34.14'


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

input_files = [
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/VevaciousPlusPlus.hpp',
]
include_paths = [
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/LHPC',
    '../../../Backends/installed/minuit2/'+gambit_minuit_version+'/include',
#    '../../../contrib/eigen3.2.8' # This should be learned from GAMBIT somehow to future-protect against version changes (and if user uses own library!)
]
base_paths = ['../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version]

header_files_to = '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include'
src_files_to    = '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/source'

load_classes = [
  'VevaciousPlusPlus::VevaciousPlusPlus'
]

load_functions = [
]

ditch = []


auto_detect_stdlib_paths = False


load_parent_classes    = False
wrap_inherited_members = False


header_extension = '.hpp'
source_extension = '.cpp'

indent = 4


# ~~~~~ Information about other known types ~~~~~

# Dictionary key: type name
# Dictionary value: header file with containing type declaration.
#
# Example:
#   known_classes = {"SomeNamespace::KnownClassOne" : "path_to_header/KnownClassOne.hpp",
#                    "AnotherNamespace::KnownClassTwo" : "path_to_header/KnownClassTwo.hpp" }

known_classes = {
#    "Eigen::Matrix" : "<Eigen/Core>",
#    "Eigen::Array" : "<Eigen/Core>",
}


# ~~~~~ Pragma directives for the inclusion of BOSSed classes in GAMBIT ~~~~~

# The listed pragma directives will be added before/after including the
# the BOSS-generated headers in GAMBIT.

pragmas_begin = [
]

pragmas_end = [
]


