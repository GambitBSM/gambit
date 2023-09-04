# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake file for example backend libraries that
#  ship with GAMBIT.
#
#  You don't need to add to or emulate this file
#  if you add new backends; this file just builds
#  the example backends easily within the GAMBIT
#  cmake system.  True backends will come with
#  their own build systems.  Those will probably
#  be far more painful than this. ;)
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

# create libraries
add_library(first SHARED examples/libfirst.cpp)
add_library(fortran SHARED examples/libfortran.f90)
add_library(FarrayTest SHARED examples/libFarrayTest.f90)

# make sure they get built with the backends
add_dependencies(Backends first)
add_dependencies(Backends fortran)
add_dependencies(Backends FarrayTest)

# add dependencies to fix build order and avoid warnings about missing include dirs
if(NOT EXCLUDE_RESTFRAMES)
  add_dependencies(first restframes)
  add_dependencies(fortran restframes)
  add_dependencies(FarrayTest restframes)
endif()
if(NOT EXCLUDE_FLEXIBLESUSY)
  add_dependencies(first flexiblesusy)
  add_dependencies(fortran flexiblesusy)
  add_dependencies(FarrayTest flexiblesusy)
endif()

# Un-hide symbols in libfirst
make_symbols_visible(first)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set_target_properties(first PROPERTIES SUFFIX .so)
  set_target_properties(fortran PROPERTIES SUFFIX .so)
  set_target_properties(FarrayTest PROPERTIES SUFFIX .so)
endif()

set_target_properties( first fortran FarrayTest
PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples"
)
