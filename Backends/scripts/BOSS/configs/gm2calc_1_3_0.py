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

gambit_backend_name      = 'gm2calc'
gambit_backend_version   = '1.3.0'
gambit_backend_reference = 'Athron:2015rva'
gambit_base_namespace    = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

input_files = [
    '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src/MSSMNoFV_onshell.hpp',
    '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src/gm2_1loop.hpp',
    '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src/gm2_2loop.hpp',
    '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src/gm2_uncertainty.hpp',
    '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src/gm2_error.hpp',
]
include_paths = [
    '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src',
    '../../../contrib/eigen3.2.8' # This should be learned from GAMBIT somehow to future-protect against version changes (and if user uses own library!)
]
base_paths = ['../../../Backends/installed/gm2calc/'+gambit_backend_version]

header_files_to = '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src'
src_files_to    = '../../../Backends/installed/gm2calc/'+gambit_backend_version+'/src'

load_classes = [
    'gm2calc::MSSMNoFV_onshell',
    'gm2calc::MSSMNoFV_onshell_mass_eigenstates',
    'gm2calc::MSSMNoFV_onshell_soft_parameters',
    'gm2calc::MSSMNoFV_onshell_susy_parameters',
    'gm2calc::MSSMNoFV_onshell_physical',
    'gm2calc::MSSMNoFV_onshell_problems',
    'gm2calc::Error',
    'gm2calc::ESetupError',
    'gm2calc::EInvalidInput',
    'gm2calc::EPhysicalProblem',
    'gm2calc::EReadError',
]

load_functions = [
  'gm2calc::calculate_amu_1loop(const gm2calc::MSSMNoFV_onshell&)',
  'gm2calc::calculate_amu_1loop_non_tan_beta_resummed(const gm2calc::MSSMNoFV_onshell&)',
  'gm2calc::calculate_amu_2loop(const gm2calc::MSSMNoFV_onshell&)',
  'gm2calc::calculate_amu_2loop_non_tan_beta_resummed(const gm2calc::MSSMNoFV_onshell&)',
  'gm2calc::calculate_uncertainty_amu_2loop(const gm2calc::MSSMNoFV_onshell&)'
]

ditch = []


auto_detect_stdlib_paths = False


load_parent_classes    = False
wrap_inherited_members = False


header_extension = '.hpp'
source_extension = '.cpp'

indent = 3


# ~~~~~ Information about other known types ~~~~~

# Dictionary key: type name
# Dictionary value: header file with containing type declaration.
#
# Example:
#   known_classes = {"SomeNamespace::KnownClassOne" : "path_to_header/KnownClassOne.hpp",
#                    "AnotherNamespace::KnownClassTwo" : "path_to_header/KnownClassTwo.hpp" }

known_classes = {
    "Eigen::Matrix" : "<Eigen/Core>",
    "Eigen::Array" : "<Eigen/Core>",
}


# ~~~~~ Pragma directives for the inclusion of BOSSed classes in GAMBIT ~~~~~

# The listed pragma directives will be added before/after including the
# the BOSS-generated headers in GAMBIT.

pragmas_begin = [
    '#include "gambit/Utils/begin_ignore_warnings_eigen.hpp"', # Contains pragmas to suppress warnings from Eigen
]

pragmas_end = [
    '#include "gambit/Utils/end_ignore_warnings.hpp"', # Restores the warning settings
]

