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
#castxml_cc_opt = '-std=c++11'  # Additional option string passed to the compiler in castxml_cc (e.g. '-m32')
castxml_cc_opt = '-std=c++14 -D __builtin_sincos=::sincos'  # Additional option string passed to the compiler in castxml_cc (e.g. '-m32')


# ~~~~~ GAMBIT-specific options ~~~~~

gambit_backend_name    = 'HepLike'
gambit_backend_version = '1.2'
gambit_backend_reference = 'Bhom:2020bfe'
gambit_base_namespace  = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

install_path = '../../../Backends/installed/'+gambit_backend_name.lower()+'/'+gambit_backend_version

input_files = [
    install_path+'/include/HL_BifurGaussian.h',
    install_path+'/include/HL_Constants.h',
    install_path+'/include/HL_Data.h',
    install_path+'/include/HL_ExpPoints.h',
    install_path+'/include/HL_Gaussian.h',
    install_path+'/include/HL_Limit.h',
    install_path+'/include/HL_nDimBifurGaussian.h',
    install_path+'/include/HL_nDimGaussian.h',
    install_path+'/include/HL_nDimLikelihood.h',
    install_path+'/include/HL_ProfLikelihood.h',
    install_path+'/include/HL_Stats.h'
]
include_paths = [install_path+'/include/', '../../../contrib/yaml-cpp-0.6.2/include']
base_paths = [install_path]

header_files_to = install_path+'/include'
src_files_to    = install_path+'/src'

load_classes = [
    'HL_BifurGaussian',
    'HL_Data',
    'HL_ExpPoints',
    'HL_Gaussian',
    'HL_Limit',
    'HL_nDimBifurGaussian',
    'HL_nDimGaussian',
    'HL_ProfLikelihood',
    'HL_nDimLikelihood',
]

load_functions = [
    'HL_Data()',
    'HL_Data(std::string)',
    'read()',
    'set_debug_yaml( bool )',
    'Read()',
    'GetChi2(double, double )',
    'GetLikelihood(double, double )',
    'GetLogLikelihood(double, double )',
]

ditch = []


auto_detect_stdlib_paths = False


load_parent_classes    = False
wrap_inherited_members = False


header_extension = '.h'
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
    "boost::numeric::ublas::matrix" : "<boost/numeric/ublas/matrix.hpp>",
    "YAML::Node" : "yaml-cpp/yaml.h"
}


# ~~~~~ Pragma directives for the inclusion of BOSSed classes in GAMBIT ~~~~~

# The listed pragma directives will be added before/after including the
# the BOSS-generated headers in GAMBIT.

pragmas_begin = [
    '#pragma GCC diagnostic push',
    '#pragma GCC diagnostic ignored "-Wdeprecated-declarations"',
]

pragmas_end = [
    '#pragma GCC diagnostic pop'
]


