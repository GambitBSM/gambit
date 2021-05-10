# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Master CMake configuration script for GAMBIT.
#
#  CMakeLists files in this project can refer to
#  the root source directory of the project as
#  ${PROJECT_SOURCE_DIR} and to the root binary
#  directory of the project as ${PROJECT_BINARY_DIR}.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#        2015 Jan, Feb, Apr, Sep
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#
#  \author Tomas Gonzao
#          (t.e.gonzalo@fys.uio.no)
#  \date 2016 Sep
#
#  \author Ben Farmer
#          (b.farmer@imperial.ac.uk)
#  \date 2018 Oct
#
#************************************************

# Define minimum cmake version
cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)


# Define minimum compiler versions
set(MIN_GCC_VERSION 5.1)
set(MIN_ICC_VERSION 15.0.2)

SET(CMAKE_BUILD_TYPE_STRING "Choose the type of build, options are: None Debug Release Release_O3 RelWithDebInfo MinSizeRel.")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  SET(CMAKE_BUILD_TYPE None CACHE STRING "${CMAKE_BUILD_TYPE_STRING}" FORCE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release_O3")
  SET(CMAKE_BUILD_TYPE Release CACHE STRING "${CMAKE_BUILD_TYPE_STRING}" FORCE)
  SET(FORCE_O3 TRUE)
endif()
message("${Yellow}-- Build type is set to ${CMAKE_BUILD_TYPE} ${ColourReset}")

# Set certain policies to NEW
foreach(p
  CMP0003 # CMake 2.6.0
  CMP0012 # CMake 2.8.0
  CMP0022 # CMake 2.8.12
  CMP0025 # CMake 3.0
  CMP0042 # CMake 3.0
  CMP0051 # CMake 3.1
  CMP0054 # CMake 3.1
  CMP0060 # CMake 3.16.2
  CMP0063 # CMake 3.3.2
  CMP0068 # CMake 3.9.1
  CMP0074 # CMake 3.12
  )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# Set the project name, enabling C, C++ and Fortran support
project(gambit C CXX Fortran)

# include macros and functions
# Warning flags macros
include(cmake/warnings.cmake)
# Include cmake utility scripts, including colour definitions.
include(cmake/utilities.cmake)
# Macros that do OSX checks
include(cmake/MacOSX.cmake)
# Optional packages and disable sections of GAMBIT accordingly
include(cmake/optional.cmake)
# Contrib macros  
include(cmake/contrib.cmake)
# Preprocessing macros
include(cmake/preprocessor.cmake)


# Don't relink all binaries when shared lib changes (programs will be rebuilt anyway if used headers change)
set(CMAKE_LINK_DEPENDS_NO_SHARED 1)

# Include ./cmake in search path for projects
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Add common system library search variables to cmake library search variable, used by find_library
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} $ENV{LIBRARY_PATH})
string(REPLACE ":" ";" CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}")

# When building, use the install RPATH already
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# Add the automatically determined parts of the RPATH that point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Check if pybind11 is to be ditched
string(REGEX MATCH ";pybind;|;pybind11;|;Pybind;|;Pybind11;" DITCH_PYBIND ";${itch};")

# now have converted Python interpreter checks into macro
CheckPython()

# set the compilation flags, such as -fPIC, 
SetCompilationFlags()

# Check for axel to speed up backend downloads
CheckAxel()

# update paths if running on OS X
MacOSXSetRPaths()

# Set output paths
set(mylibdir ${PROJECT_SOURCE_DIR}/lib)
set(mybindir ${PROJECT_SOURCE_DIR})
# First for the generic no-config case (e.g. with mingw)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${mybindir} )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${mylibdir} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${mylibdir} )
# Second, for multi-config builds (e.g. msvc)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${mybindir} )
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${mylibdir} )
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${mylibdir} )
endforeach()

# Check for OpenMP
SetOpenMP()

# Check for Boost
SetBoost()

# Check for Eigen
SetEigen()

# Check for Gnu Scientific Library (GSL)
SetGSL()

# Find git
SetGit()

# Check for Mathematica (But is this not optional? VERY Confusing)
SetMathematica()

# Construct the full set of compiler flags to be used for external projects
SetBackendCompliationFlags()

#Find DL Libraries
find_package(LibDL)

# Make symbols hidden by default when compiling GAMBIT source files only
if(${CMAKE_MAJOR_VERSION} MATCHES "2")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
  set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fvisibility=hidden")
else()
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_Fortran_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)
endif()

# Check for optional packages and disable sections of GAMBIT accordingly
SetOptionals()

# Add doxygen build as an external project
add_custom_target(docs WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND doxygen doc/doxygen.conf)

# Work out which modules to include in the compile
retrieve_bits(GAMBIT_BITS ${PROJECT_SOURCE_DIR} "${itch}" "Loud")

# Set up targets to make standalone tarballs of the different modules
add_standalone_tarballs("${GAMBIT_BITS}" "${GAMBIT_VERSION_FULL}")

# Include contributed packages
SetContrib()

# Reprocess the ditch set into a comma-separated list
string (REPLACE ";" "," itch_with_commas "${itch}")

# Create the scratch directory if it isn't there already
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/scratch")
  message("${Yellow}-- Creating scratch directory${ColourReset}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory scratch WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory build_time WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/scratch)
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory run_time WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/scratch)
  message("${Yellow}-- Creating scratch directory - done.${ColourReset}")
endif()

# Generate the ScannerBit compilation files
if(EXISTS "${PROJECT_SOURCE_DIR}/ScannerBit/")
  message("${Yellow}-- Updating GAMBIT scanner cmake and related files${ColourReset}")
  set(scanner_harvester ${PROJECT_SOURCE_DIR}/ScannerBit/scripts/scanner+_harvester.py ${PROJECT_BINARY_DIR} -x __not_a_real_name__,${itch_with_commas})
  execute_process(RESULT_VARIABLE result COMMAND ${PYTHON_EXECUTABLE} ${scanner_harvester} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  check_result(${result} ${scanner_harvester})
  message("${Yellow}-- Updating GAMBIT scanner cmake and related files - done.${ColourReset}")
endif()

# Generate the cmake_variables.hpp file
SetPreproccessing()

# Generate particle_database.cpp from particle_database.yaml.
if(EXISTS "${PROJECT_SOURCE_DIR}/Models/")
  set(particle_harvester ${PROJECT_SOURCE_DIR}/Models/scripts/particle_harvester.py ${PROJECT_BINARY_DIR} -x __not_a_real_name__,${itch_with_commas})
  execute_process(COMMAND ${PYTHON_EXECUTABLE} ${particle_harvester} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  message("${Yellow}-- Generated particle_database.cpp from particle_database.yaml.${ColourReset}")
endif()

# Add the main gambit sources and identify which modules are to be included.
include(cmake/gambit.cmake)

# Identify the different harvester scripts
set(MODULE_HARVESTER ${PROJECT_SOURCE_DIR}/Elements/scripts/module_harvester.py)
set(BACKEND_HARVESTER ${PROJECT_SOURCE_DIR}/Backends/scripts/backend_harvester.py)
set(MODEL_HARVESTER ${PROJECT_SOURCE_DIR}/Models/scripts/model_harvester.py)
set(PRINTER_HARVESTER ${PROJECT_SOURCE_DIR}/Printers/scripts/printer_harvester.py)
set(COLLIDER_HARVESTER ${PROJECT_SOURCE_DIR}/ColliderBit/scripts/collider_harvester.py)
set(HARVEST_TOOLS ${PROJECT_SOURCE_DIR}/Utils/scripts/harvesting_tools.py)

# Create module_rollcall.hpp, module_types_rollcall.hpp, module_functor_types.hpp, models_rollcall.hpp, model_types_rollcall.hpp,
# backend_rollcall.hpp, backend_types_rollcall.hpp, backend_functor_types.hpp, printer_rollcall.hpp, particle_database.cpp,
# ColliderBit_model_rollcall.hpp, ColliderPythia_typedefs.hpp
file(GLOB MODULE_HARVESTER_FILES   "${PROJECT_SOURCE_DIR}/*Bit*/include/gambit/*Bit*/*_rollcall.hpp"
                                   "${PROJECT_SOURCE_DIR}/*Bit*/include/gambit/*Bit*/*_types.hpp")
file(GLOB BACKEND_HARVESTER_FILES  "${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/frontends/*.hpp"
                                   "${PROJECT_SOURCE_DIR}/Backends/CMakeLists.txt")
file(GLOB MODEL_HARVESTER_FILES    "${PROJECT_SOURCE_DIR}/Models/include/gambit/Models/models/*.hpp"
                                   "${PROJECT_SOURCE_DIR}/Models/CMakeLists.txt")
file(GLOB PRINTER_HARVESTER_FILES  "${PROJECT_SOURCE_DIR}/Printers/include/gambit/Printers/printers/*.hpp"
                                   "${PROJECT_SOURCE_DIR}/Printers/CMakeLists.txt")
file(GLOB COLLIDER_HARVESTER_FILES "${PROJECT_SOURCE_DIR}/ColliderBit/include/gambit/ColliderBit/models/*.hpp"
                                   "${PROJECT_SOURCE_DIR}/Models/CMakeLists.txt")
string (REPLACE "//" "/" MODULE_HARVESTER_FILES   "${MODULE_HARVESTER_FILES}")
string (REPLACE "//" "/" BACKEND_HARVESTER_FILES  "${BACKEND_HARVESTER_FILES}")
string (REPLACE "//" "/" MODEL_HARVESTER_FILES    "${MODEL_HARVESTER_FILES}")   # (GLOB creates erroneous double slashes)
string (REPLACE "//" "/" PRINTER_HARVESTER_FILES  "${PRINTER_HARVESTER_FILES}")
string (REPLACE "//" "/" COLLIDER_HARVESTER_FILES "${COLLIDER_HARVESTER_FILES}")
list(REMOVE_ITEM MODULE_HARVESTER_FILES "${PROJECT_SOURCE_DIR}/ScannerBit//include//gambit//ScannerBit//priors_rollcall.hpp"
                                        "${PROJECT_SOURCE_DIR}/ScannerBit//include//gambit//ScannerBit//test_function_rollcall.hpp")
list(APPEND MODULE_HARVESTER_FILES "${PROJECT_SOURCE_DIR}/config/resolution_type_equivalency_classes.yaml")
set(MODULE_HARVESTER_FILES ${MODULE_HARVESTER_FILES} ${BACKEND_HARVESTER_FILES})
remove_build_files(models_harvested backends_harvested modules_harvested printers_harvested colliders_harvested)
if(EXISTS "${PROJECT_SOURCE_DIR}/Elements/")
  add_gambit_custom(module_harvest modules_harvested MODULE_HARVESTER MODULE_HARVESTER_FILES ${itch_with_commas})
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/Backends/")
  add_gambit_custom(backend_harvest backends_harvested BACKEND_HARVESTER BACKEND_HARVESTER_FILES ${itch_with_commas})
  add_dependencies(module_harvest backend_harvest)
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/Models/")
 add_gambit_custom(model_harvest models_harvested MODEL_HARVESTER MODEL_HARVESTER_FILES)
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/Printers/")
  add_gambit_custom(printer_harvest printers_harvested PRINTER_HARVESTER PRINTER_HARVESTER_FILES ${itch_with_commas})
  add_dependencies(printer_harvest module_harvest)
else()
  add_definitions(-DNO_PRINTERS)
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/ColliderBit/" AND ";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  add_gambit_custom(collider_harvest colliders_harvested COLLIDER_HARVESTER COLLIDER_HARVESTER_FILES)
  add_dependencies(module_harvest collider_harvest)
endif()

# Generate the CMakeLists.txt files for GAMBIT modules, Backends, Models and Printers)
message("${Yellow}-- Updating GAMBIT module, model, backend, and printer CMake files.${ColourReset}")
set(update_cmakelists ${PROJECT_SOURCE_DIR}/cmake/scripts/update_cmakelists.py -x __not_a_real_name__,${itch_with_commas})
execute_process(RESULT_VARIABLE result COMMAND ${PYTHON_EXECUTABLE} ${update_cmakelists} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
check_result(${result} ${update_cmakelists})
message("${Yellow}-- Updating GAMBIT module, backend, and printer CMake files - done.${ColourReset}")

# Add backends and scanners
include(cmake/externals.cmake)

# Add GAMBIT subdirectories.
add_subdirectory(Logs)
add_subdirectory(Utils)
add_subdirectory_if_present(Core)
add_subdirectory_if_present(Models)
add_subdirectory_if_present(Backends)
add_subdirectory_if_present(Elements)
add_subdirectory_if_present(Printers)

# Lists of different GAMBIT object files to link
set(GAMBIT_BASIC_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:Logs> $<TARGET_OBJECTS:Utils>)
set(GAMBIT_ALL_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:Models> $<TARGET_OBJECTS:Backends> $<TARGET_OBJECTS:Elements>)

# Set compilation targets for GAMBIT modules
foreach(bit ${GAMBIT_BITS})
  add_subdirectory(${bit})
  set(GAMBIT_BIT_OBJECTS ${GAMBIT_BIT_OBJECTS} "$<TARGET_OBJECTS:${bit}>")
endforeach()

# If ColliderBit is in use, make the collider_harvest step a dependency of ColliderBit
if(";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  add_dependencies(ColliderBit collider_harvest)
  # If RestFrames is in use, make it a dependency of ColliderBit
  if(NOT EXCLUDE_RESTFRAMES)
    add_dependencies(ColliderBit restframes)
  endif()
  # If HepMC is in use, make it a dependency of ColliderBit
  if(NOT EXCLUDE_HEPMC)
    add_dependencies(ColliderBit hepmc)
  endif()
endif()

# If SpecBit is in use, make flexiblesusy a dependency of SpecBit
if(";${GAMBIT_BITS};" MATCHES ";SpecBit;")
  add_dependencies(SpecBit flexiblesusy)
endif()

# Add the executables
include(cmake/executables.cmake)

# Finish setting the link commands and rpath variables for ScannerBit
if(EXISTS "${PROJECT_SOURCE_DIR}/ScannerBit/")
  include(${PROJECT_BINARY_DIR}/linkedout.cmake)
endif()

