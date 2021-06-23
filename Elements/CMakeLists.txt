# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake CMakeLists.txt file for Elements
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2015 Apr
#
#************************************************

set(source_files src/decay_table.cpp
                 src/equivalency_singleton.cpp
                 src/functors.cpp
                 src/higgs_couplings_table.cpp
                 src/ini_functions.cpp
                 src/ini_catch.cpp
                 src/mssm_slhahelp.cpp
                 src/slhaea_helpers.cpp
                 src/sminputs.cpp
                 src/smlike_higgs.cpp
                 src/spectrum.cpp
                 src/subspectrum.cpp
                 src/terminator.cpp
                 src/type_equivalency.cpp
                 src/virtual_higgs.cpp
)

set(header_files include/gambit/Elements/decay_table.hpp
                 include/gambit/Elements/equivalency_singleton.hpp
                 include/gambit/Elements/functors.hpp
                 include/gambit/Elements/functor_definitions.hpp
                 include/gambit/Elements/higgs_couplings_table.hpp
                 include/gambit/Elements/ini_functions.hpp
                 include/gambit/Elements/ini_catch.hpp
                 include/gambit/Elements/module_macros_common.hpp
                 include/gambit/Elements/module_macros_incore.hpp
                 include/gambit/Elements/module_macros_incore_defs.hpp
                 include/gambit/Elements/module_macros_inmodule.hpp
                 include/gambit/Elements/module_macros_inmodule_defs.hpp
                 include/gambit/Elements/mssm_slhahelp.hpp
                 include/gambit/Elements/safety_bucket.hpp
                 include/gambit/Elements/shared_types.hpp
                 include/gambit/Elements/slhaea_helpers.hpp
                 include/gambit/Elements/sminputs.hpp
                 include/gambit/Elements/smlike_higgs.hpp
                 include/gambit/Elements/spectrum.hpp
                 include/gambit/Elements/spec_fptrfinder.hpp
                 include/gambit/Elements/spectrum_factories.hpp
                 include/gambit/Elements/spec.hpp
                 include/gambit/Elements/spec_head.hpp
                 include/gambit/Elements/standalone_module.hpp
                 include/gambit/Elements/subspectrum.hpp
                 include/gambit/Elements/terminator.hpp
                 include/gambit/Elements/type_equivalency.hpp
                 include/gambit/Elements/types_rollcall.hpp
                 include/gambit/Elements/virtual_higgs.hpp
)

add_gambit_library(Elements OPTION OBJECT SOURCES ${source_files} HEADERS ${header_files})
