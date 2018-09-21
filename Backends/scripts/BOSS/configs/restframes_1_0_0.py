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

gambit_backend_name    = 'restframes'
gambit_backend_version = '1.0.0'
gambit_base_namespace  = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

input_files = [
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/LabRecoFrame.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/DecayRecoFrame.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/VisibleRecoFrame.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/InvisibleRecoFrame.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/InvisibleGroup.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/ContraBoostInvJigsaw.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/SelfAssemblingRecoFrame.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/CombinatoricGroup.hh',
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/MinMassesCombJigsaw.hh'
]
include_paths = [
    '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/',
    '/home/mwhi/Root6/include/'
]
base_paths = ['../../../Backends/installed/restframes/'+gambit_backend_version]

header_files_to = '../../../Backends/installed/restframes/'+gambit_backend_version+'/inc/RestFrames/'
src_files_to    = '../../../Backends/installed/restframes/'+gambit_backend_version+'/src'

load_classes = [
    'RestFrames::LabRecoFrame',
    'RestFrames::DecayRecoFrame',
    'RestFrames::VisibleRecoFrame',
    'RestFrames::InvisibleRecoFrame',
    'RestFrames::InvisibleGroup',
    'RestFrames::ContraBoostInvJigsaw',
    'RestFrames::SelfAssemblingRecoFrame',
    'RestFrames::CombinatoricGroup',
    'RestFrames::MinMassesCombJigsaw',
]

load_functions = [
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


