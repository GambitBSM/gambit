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

gambit_backend_name    = 'FlexibleSUSY_CMSSM'
gambit_backend_version = '2.0.1'
gambit_backend_reference = 'Athron:2017fvs'
gambit_base_namespace  = ''


# ~~~~~ Information about the external code ~~~~~

# Use either absolute paths or paths relative to the main BOSS directory.
input_files   = [
#    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/src/command_line_options.hpp',
    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/models/CMSSM/CMSSM_two_scale_spectrum_generator.hpp',
#    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/models/CMSSM/CMSSM_slha_io.hpp',
]
include_paths = [
    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/src',
#    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/models/CMSSM',
    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/config',
    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/slhaea',
#    '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/model_specific/SM',
]
base_paths    = ['../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/']

header_files_to = '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/models/CMSSM'
src_files_to    = '../../../Backends/installed/flexiblesusy_CMSSM/'+gambit_backend_version+'/models/CMSSM'



load_classes = [
    'softsusy::QedQcd',
    'flexiblesusy::Error',
    'flexiblesusy::Spectrum_generator_settings',
    'flexiblesusy::Spectrum_generator_problems',
    'flexiblesusy::Command_line_options',
    'flexiblesusy::Physical_input',
    'flexiblesusy::CMSSM_slha_io', 
    'flexiblesusy::CMSSM_scales',
    'flexiblesusy::CMSSM_input_parameters',
    'flexiblesusy::CMSSM_parameter_getter',
    'flexiblesusy::Two_scale',
    'flexiblesusy::CMSSM_spectrum_generator<Two_scale>',
    'flexiblesusy::CMSSM_spectrum_generator_interface<Two_scale>',
    'flexiblesusy::CMSSM_slha_Model_Two_scale'
]

load_functions = [
]

load_enums = [
    'softsusy::mass',
    'softsusy::leGauge'
]

ditch = [
    'softsusy::QedQcd::displayMass',
    'softsusy::QedQcd::displayAlphas',
    'softsusy::QedQcd::display_input_parameter_names',
    'flexiblesusy::Command_line_options::get_parameter_value',
    'flexiblesusy::Command_line_options::starts_with',
    'flexiblesusy::Physical_input::get_names',
    'flexiblesusy::CMSSM_parameter_getter::get_number_of_masses',
]


auto_detect_stdlib_paths = False


load_parent_classes    = False
wrap_inherited_members = False


header_extension = '.h'
source_extension = '.cpp'

indent = 4


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
    {'name' : 'run_FS_Spectrum', 
     'returntype' : 'void', 
     'argtypes' : ['Spectrum&', 'const SpectrumInputs&'], 
     'capname' : 'FS_CMSSM_Spectrum'
    }
]

ini_function_in_header = False

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

pragmas_begin = [
       '#pragma GCC diagnostic push',
       '#pragma GCC diagnostic ignored "-Wdeprecated-declarations"',
]
pragmas_end = [
       '#pragma GCC diagnostic pop'
]


