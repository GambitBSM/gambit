# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake CMakeLists.txt file for Core
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Aug, Oct
#  \date 2015 Feb
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#  \date 2015 Feb
#  \date 2022 Nov
#
#************************************************

set(source_files src/container_factory.cpp
                 src/core.cpp
                 src/core_singleton.cpp
                 src/depresolver.cpp
                 src/diagnostics.cpp
                 src/error_handlers.cpp
                 src/functors.cpp
                 src/functors_with_signals.cpp
                 src/ini_functions.cpp
                 src/likelihood_container.cpp
                 src/modelgraph.cpp
                 src/observable.cpp
                 src/resolution_utilities.cpp 
                 src/rule.cpp
                 src/yaml_description_database.cpp
                 src/yaml_parser.cpp
)

set(header_files include/gambit/Core/container_factory.hpp
                 include/gambit/Core/core.hpp
                 include/gambit/Core/core_singleton.hpp
                 include/gambit/Core/depresolver.hpp
                 include/gambit/Core/error_handlers.hpp
                 include/gambit/Core/gambit.hpp
                 include/gambit/Core/ini_functions.hpp
                 include/gambit/Core/likelihood_container.hpp
                 include/gambit/Core/modelgraph.hpp
                 include/gambit/Core/observable.hpp
                 include/gambit/Core/resolution_utilities.hpp
                 include/gambit/Core/rule.hpp
                 include/gambit/Core/yaml_description_database.hpp
                 include/gambit/Core/yaml_parser.hpp
)

add_gambit_library(Core OPTION OBJECT SOURCES ${source_files} HEADERS ${header_files})
add_dependencies(Core module_harvest)
