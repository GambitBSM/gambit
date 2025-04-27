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

gambit_backend_name      = 'obscura'
gambit_backend_version   = '1.1.0'
gambit_backend_reference = 'Emken:2021uzb'
gambit_base_namespace    = ''
gambit_minuit_version    = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.

input_files = [
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/Astronomy.hpp',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/Direct_Detection_Crystal.hpp',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/Direct_Detection.hpp',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/Direct_Detection_Ionization.hpp',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/Direct_Detection_ER.hpp',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/DM_Halo_Models.hpp',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/DM_Particle_Standard.hpp',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/obscura/Experiments.hpp',
]
include_paths = [
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/generated/',
    '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include/',
    '../../../Backends/installed/libphysica/0.1.5/include',
]
base_paths = ['../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version]

header_files_to = '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/include'
src_files_to    = '../../../Backends/installed/'+gambit_backend_name+'/'+gambit_backend_version+'/src'

load_classes = [
    'obscura::DM_Detector_Crystal',
    'obscura::DM_Detector_Ionization_ER',
    'obscura::DM_Detector_Ionization_Migdal',
    'obscura::Standard_Halo_Model',
    'obscura::DM_Particle_Standard',
    'obscura::DM_Particle_SI',
]

load_functions = [
    'obscura::XENON1T_S2_ER()',
    'obscura::DarkSide50_S2_ER()',
    'obscura::DarkSide50_S2_ER_2023()',
    'obscura::PandaX_4T_S2_ER()',
#    'obscura::LZ_S2_ER()',
    'obscura::SENSEI_at_MINOS()',
    'obscura::CDMS_HVeV_2020()',
    'obscura::DAMIC_M_2023()',
    'obscura::XENON1T_S2_Migdal()',
    'obscura::DarkSide50_S2_Migdal()',
    'obscura::DarkSide50_S2_Migdal_2023()',
    'obscura::PandaX_4T_S2_Migdal()',
#    'obscura::LZ_S2_Migdal()',
]

ditch = []


auto_detect_stdlib_paths = False


load_parent_classes    = True
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

convenience_functions = []

ini_function_in_header = True

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

# ~~~~~ Extra code to surround BOSS-generated code included in GAMBIT ~~~~~

# The listed code will be added at the top/bottom in the frontend header file
# and in the loaded_types.hpp header.

surround_code_begin = '''
'''

surround_code_end = '''
'''

