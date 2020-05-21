# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake preprocessor variable configuration.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2015 Apr, Sep
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2015 Apr
#
#************************************************

include(CheckIncludeFiles)

message("${Yellow}-- Updating GAMBIT with config data${ColourReset}")

# Check for link.h
check_include_files(link.h HAVE_LINK_H)

# Check for Graphviz
find_program(GRAPHVIZ_FOUND dot)
if (GRAPHVIZ_FOUND)
  message("${BoldYellow}   Found graphviz.${ColourReset} Model and module function hierarchy plots will be enabled.")
else()
  message("${BoldRed}   Did not find graphviz. Model and module function hierarchy plots will not be produced.${ColourReset}")
endif()

# Define HAVE_GRAPHVIZ compiler option
include(CMakeDependentOption)
cmake_dependent_option(HAVE_GRAPHVIZ "create Graphviz files" ON "GRAPHVIZ_FOUND" OFF)

# Configure the file
set(outhdr "${PROJECT_SOURCE_DIR}/cmake/include/gambit/cmake/cmake_variables.hpp")
configure_file("${PROJECT_SOURCE_DIR}/cmake/cmake_variables.hpp.in" ${outhdr})
message("${BoldYellow}   Configured ${outhdr}${ColourReset}")
message("${Yellow}-- Updating GAMBIT with config data - done.${ColourReset}")

