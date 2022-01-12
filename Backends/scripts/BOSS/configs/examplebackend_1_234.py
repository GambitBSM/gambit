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

castxml_cc_id = 'gnu'      # Reference compiler: 'gnu', 'gnu-c', 'msvc', 'msvc-c'
castxml_cc = 'g++'      # Name a specific compiler: 'g++', 'cl', ...
# Additional option string passed to the compiler in castxml_cc (e.g. '-m32')
castxml_cc_opt = '-std=c++11'


# ~~~~~ GAMBIT-specific options ~~~~~

gambit_backend_name = 'ExampleBackend'
gambit_backend_version = '1.234'
gambit_backend_reference = ''
gambit_base_namespace = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.
input_files = [
    'ExampleBackend/include/classes.hpp',
    'ExampleBackend/include/functions.hpp',
]
include_paths = ['ExampleBackend/include']
base_paths = ['ExampleBackend']

header_files_to = 'ExampleBackend/include'
src_files_to = 'ExampleBackend/src'


load_classes = [
    'ClassOne',
    'SomeNamespace::ClassTwo',
]

load_functions = [
    'SomeNamespace::modify_instance(int, SomeNamespace::ClassTwo&)',
    'SomeNamespace::return_as_vector(int, int)',
    'SomeNamespace::return_as_vector_2(int, int&)',
    # 'ClassOne::return_clock_t()',
    # 'SomeNamespace::return_as_vector_with_clock()',
]

load_enums = [
]

ditch = []


auto_detect_stdlib_paths = False


load_parent_classes = False
wrap_inherited_members = False


header_extension = '.hpp'
source_extension = '.cpp'

indent = 2


# ~~~~~ Information about other known types ~~~~~

# Dictionary key: type name
# Dictionary value: header file with containing type declaration.
#
# Example:
#   known_classes = {"SomeNamespace::KnownClassOne" : "path_to_header/KnownClassOne.hpp",
#                    "AnotherNamespace::KnownClassTwo" : "path_to_header/KnownClassTwo.hpp" }

known_classes = {}

# ~~~~~ Declarations to be added to the frontend header file ~~~~~

convenience_functions = [
]

ini_function_in_header = True


# ~~~~~ Pragma directives for the inclusion of BOSSed classes in GAMBIT ~~~~~

# The listed pragma directives will be added before/after including the
# the BOSS-generated headers in GAMBIT.
#
# Example:
#   pragmas_begin = [
#       '#pragma GCC diagnostic push',
#       '#pragma GCC diagnostic ignored "-Wdeprecated-declarations"',
#   ]
#
#   pragmas_end = [
#       '#pragma GCC diagnostic pop'
#   ]

pragmas_begin = []
pragmas_end = []
