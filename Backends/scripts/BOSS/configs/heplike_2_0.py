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
castxml_cc_opt = '-std=c++14 -D __builtin_sincos=::sincos'  # Additional option string passed to the compiler in castxml_cc (e.g. '-m32')



# ~~~~~ GAMBIT-specific options ~~~~~

gambit_backend_name    = 'HepLike'
gambit_backend_version = '2.0'
gambit_backend_reference = 'Bhom:2020bfe'
gambit_base_namespace  = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

install_path = '../../../Backends/installed/'+gambit_backend_name.lower()+'/'+gambit_backend_version

input_files = [
    install_path+'/include/HL_BifurGaussian.h',
    install_path+'/include/HL_Gaussian.h',
    install_path+'/include/HL_nDimBifurGaussian.h',
    install_path+'/include/HL_nDimGaussian.h',
    install_path+'/include/HL_nDimLikelihood.h',
    install_path+'/include/HL_ProfLikelihood.h',
]
include_paths = [install_path+'/include/', install_path+'/yaml-cpp/include/']
base_paths = [install_path]

header_files_to = install_path+'/include'
src_files_to    = install_path+'/src'

load_classes = [
    'HL_BifurGaussian',
    'HL_Gaussian',
    'HL_nDimBifurGaussian',
    'HL_nDimGaussian',
    'HL_ProfLikelihood',
    'HL_nDimLikelihood',
]

load_functions = []

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

convenience_functions = []

ini_function_in_header = True

known_classes = {
    "boost::numeric::ublas::matrix" : "<boost/numeric/ublas/matrix.hpp>",
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


# ~~~~~ Extra code to surround BOSS-generated code included in GAMBIT ~~~~~

# The listed code will be added at the top/bottom in the frontend header file 
# and in the loaded_types.hpp header.

surround_code_begin = '''
'''

surround_code_end = ''' 
'''
