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
# Filip Rajec
# April 2020

#
# *** Special note for OS X *** 
# 
# BOSS will most likely fail if 'g++' points to the Clang compiler.
# Install GNU g++ and point the castxml_cc variable below the GNU 
# g++ executable.   
#



castxml_cc_id  = 'gnu'      # Reference compiler: 'gnu', 'gnu-c', 'msvc', 'msvc-c'
castxml_cc     = 'g++'      # Name a specific compiler: 'g++', 'cl', ...
castxml_cc_opt = '-std=c++11'         # Additional option string passed to the compiler in castxml_cc (e.g. '-m32')


# ~~~~~ GAMBIT-specific options ~~~~~

gambit_backend_name    = 'THDMC'
gambit_backend_version = '1.8.0'
gambit_base_namespace  = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.
input_files   = ['../../../Backends/installed/THDMC/'+gambit_backend_version+'/src/SM.h',
                '../../../Backends/installed/THDMC/'+gambit_backend_version+'/src/THDM.h',
                '../../../Backends/installed/THDMC/'+gambit_backend_version+'/src/Constraints.h',
                '../../../Backends/installed/THDMC/'+gambit_backend_version+'/src/DecayTableTHDM.h']
include_paths = ['../../../Backends/installed/THDMC/'+gambit_backend_version+'/lib/','../../../Backends/installed/THDMC/'+gambit_backend_version+'/src/','.']
base_paths    = ['../../../Backends/installed/THDMC/'+gambit_backend_version+'/']

header_files_to = '../../../Backends/installed/THDMC/'+gambit_backend_version+'/src'
src_files_to    = '../../../Backends/installed/THDMC/'+gambit_backend_version+'/src'

load_classes = ['SM',
                'THDM',
                'Constraints',
                'DecayTableTHDM']
load_functions = ['THDM::set_SM(THDM::SM)',
                 'Constraints::set_THDM(THDM::THDM)',
                 'DecayTableTHDM::set_model(THDM::THDM)']

ditch = []


auto_detect_stdlib_paths = False


load_parent_classes    = False
wrap_inherited_members = False


header_extension = '.h'
source_extension = '.cpp'

indent = 4

extra_output_dir       = 'BOSS_output'


# ~~~~~ Information about other known types ~~~~~

# Dictionary key: type name
# Dictionary value: header file with containing type declaration.
#
# Example:
#   known_classes = {"SomeNamespace::KnownClassOne" : "path_to_header/KnownClassOne.hpp",
#                    "AnotherNamespace::KnownClassTwo" : "path_to_header/KnownClassTwo.hpp" }

known_classes = {}

pragmas_begin = []
pragmas_end = []
