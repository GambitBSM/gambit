# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake configuration script for building
#  the python interface to ScannerBit
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Ben Farmer
#          (ben.farmer@gmail.com)
#  \date 2017 Nov
#
#************************************************

# Require a minimum cmake version of 2.8.5
cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)

# Make shared libraries findable at runtime without having to be in the LD_LIBRARY_PATH paths
#set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(ScannerBitCAPI REQUIRED)
get_target_property(LIBS ScannerBitCAPI INTERFACE_LINK_LIBRARIES)
message("Libs: ${LIBS}")

# We will use pybind11 to create the Python extension module
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/pybind11-2.1.1")

# Kind of a drag... might be best to create a FindPackage file for yaml-cpp and install it properly.
# # Need yaml-cpp for parsing configuration file
# set(yaml_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../yaml-cpp-0.5.3/include)
# include_directories("${yaml_INCLUDE_DIR}")
# add_subdirectory(${PROJECT_SOURCE_DIR}/../yaml-cpp-0.5.3 EXCLUDE_FROM_ALL)

# Generate Python module
pybind11_add_module(pyscannerbit "${PROJECT_SOURCE_DIR}/src/pyScannerBit.cpp")
target_link_libraries(pyscannerbit PUBLIC ScannerBitCAPI)

