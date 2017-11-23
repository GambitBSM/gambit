# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake CMakeLists.txt file for Logs
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
#  \date 2014 Dec
#  \date 2015 Feb
#
#************************************************

set(source_files src/logger.cpp
                 src/logging.cpp
                 src/logmaster.cpp
)

set(header_files include/gambit/Logs/log_tags.hpp
                 include/gambit/Logs/logger.hpp
                 include/gambit/Logs/logging.hpp
                 include/gambit/Logs/logmaster.hpp
)

add_gambit_library(Logs OPTION SHARED SOURCES ${source_files} HEADERS ${header_files})
