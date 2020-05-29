# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake CMakeLists.txt file for Utils
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
#  \date 2015 Jan, Feb, Apr
#
#************************************************

set(source_files src/ascii_table_reader.cpp
                 src/exceptions.cpp
                 src/file_lock.cpp
                 src/mpiwrapper.cpp
                 src/new_mpi_datatypes.cpp
                 src/model_parameters.cpp
                 src/screen_print_utils.cpp
                 src/signal_handling.cpp
                 src/signal_helpers.cpp
                 src/standalone_error_handlers.cpp
                 src/standalone_utils.cpp
                 src/statistics.cpp
                 src/stream_overloads.cpp
                 src/table_formatter.cpp
                 src/threadsafe_rng.cpp
                 src/util_functions.cpp
                 src/version.cpp
                 src/yaml_parser_base.cpp
                 src/yaml_node_utility.cpp
)

set(header_files include/gambit/Utils/ascii_table_reader.hpp
                 include/gambit/Utils/boost_fallbacks.hpp
                 include/gambit/Utils/cats.hpp
                 include/gambit/Utils/exceptions.hpp
                 include/gambit/Utils/file_lock.hpp
                 include/gambit/Utils/mpiwrapper.hpp
                 include/gambit/Utils/new_mpi_datatypes.hpp
                 include/gambit/Utils/factory_registry.hpp
                 include/gambit/Utils/local_info.hpp
                 include/gambit/Utils/model_parameters.hpp
                 include/gambit/Utils/numerical_constants.hpp
                 include/gambit/Utils/safebool.hpp
                 include/gambit/Utils/screen_print_utils.hpp
                 include/gambit/Utils/signal_handling.hpp
                 include/gambit/Utils/signal_helpers.hpp
                 include/gambit/Utils/standalone_error_handlers.hpp
                 include/gambit/Utils/standalone_utils.hpp
                 include/gambit/Utils/static_members.hpp
                 include/gambit/Utils/statistics.hpp
                 include/gambit/Utils/stream_overloads.hpp
                 include/gambit/Utils/threadsafe_rng.hpp
                 include/gambit/Utils/table_formatter.hpp
                 include/gambit/Utils/type_index.hpp
                 include/gambit/Utils/type_macros.hpp
                 include/gambit/Utils/util_functions.hpp
                 include/gambit/Utils/util_macros.hpp
                 include/gambit/Utils/util_types.hpp
                 include/gambit/Utils/version.hpp
                 include/gambit/Utils/variadic_functions.hpp
                 include/gambit/Utils/yaml_options.hpp
                 include/gambit/Utils/yaml_parser_base.hpp
                 include/gambit/Utils/yaml_variadic_functions.hpp
                 include/gambit/Utils/yaml_node_utility.hpp
)

add_gambit_library(Utils OPTION OBJECT SOURCES ${source_files} HEADERS ${header_files})
