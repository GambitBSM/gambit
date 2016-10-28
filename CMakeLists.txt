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
#************************************************

# Require a minimum cmake version of 2.8.5
cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)

SET(CMAKE_BUILD_TYPE_STRING "Choose the type of build, options are: None Debug Release Release_03 RelWithDebInfo MinSizeRel.")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  SET(CMAKE_BUILD_TYPE None CACHE STRING "${CMAKE_BUILD_TYPE_STRING}" FORCE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release_03")
  SET(CMAKE_BUILD_TYPE Release CACHE STRING "${CMAKE_BUILD_TYPE_STRING}" FORCE)
  SET(FORCE_03 TRUE)
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
  )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# Set the project name, enabling C, C++ and Fortran support
project(gambit C CXX Fortran)

# Disable clang support
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  message(FATAL_ERROR "GAMBIT does not support the Clang compiler. Please choose another compiler.")
endif()

# Use ccache to speed up re-compiling if it is available
#find_program(CCACHE_FOUND ccache)
#if(CCACHE_FOUND)
#  message("-- Found ccache. Will use it to speed up recompilation.")
#  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
#  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
#endif(CCACHE_FOUND)

# Don't relink all binaries when shared lib changes (programs will be rebuilt anyway if used headers change)
set(CMAKE_LINK_DEPENDS_NO_SHARED 1)

# Set output directories for built components (libraries and executables)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include ./cmake in search path for projects
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Add common system library search variables to cmake library search variable, used by find_library
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} $ENV{LIBRARY_PATH})
string(REPLACE ":" ";" CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}")

# --- RPATH setup ---
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# When building, use the install RPATH already
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/lib")

# Add the automatically determined parts of the RPATH that point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# -------------------

# Include cmake utility scripts, including colour definitions.
include(cmake/utilities.cmake)

# Check for Python and required libs
include(FindPythonInterp)
find_package(PythonInterp REQUIRED)
foreach(module yaml os re datetime sys getopt shutil itertools)
  find_python_module(${module} REQUIRED)
endforeach()

# Check for axel
find_program(axel_FOUND axel)
if(axel_FOUND)
  message("${BoldYellow}   Found axel.${ColourReset} Backend and scanner downloads will be as fast as possible.")
else()
  message("${Red}   Axel utility not found.  Backend downloads would be faster if you installed axel.${ColourReset}")
endif()

# Do OSX checks
include(cmake/MacOSX.cmake)

# Add -fPIC for 64 bit systems
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
endif()

# Add some Fortran compiler flags
if(CMAKE_Fortran_COMPILER MATCHES "gfortran*" OR CMAKE_Fortran_COMPILER MATCHES "f95*")
  set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -ffree-line-length-none -ffixed-line-length-none -cpp")
elseif(CMAKE_Fortran_COMPILER MATCHES "ifort*")
  set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -extend-source -fpp")
endif()

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

enable_testing()

# Check for C++11 support -- if we use special c++11 features we should check for them too at a later stage...
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
  if(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  else()
   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
  endif()
endif()

# Check for Boost
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost 1.41)
if(Boost_FOUND)
  include_directories("${Boost_INCLUDE_DIR}")
else()
  message(FATAL_ERROR "GAMBIT requires Boost v1.41 or greater.\nPlease install a suitable version of Boost and rerun cmake.")
endif()

# Check for OpenMP
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    if (NOT DEFINED OpenMP_Fortran_FLAGS)
      set(OpenMP_Fortran_FLAGS "-fopenmp")
    endif()
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${OpenMP_Fortran_FLAGS}")
endif()

# Check for Gnu Scientific Library (GSL)
include(cmake/FindGSL.cmake)
if(GSL_FOUND)
  if (NOT GSL_INCLUDE_DIRS STREQUAL "")
    include_directories("${GSL_INCLUDE_DIRS}")
  endif()
else()
  message(FATAL_ERROR "GAMBIT requires the GSL libraries.")
endif()

# Check for DL libraries
include(cmake/FindLibDL.cmake)

# Add compiler warning flags
include(cmake/warnings.cmake)

# Construct the full set of compiler flags to be used for external projects
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(GAMBIT_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
  set(GAMBIT_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
  set(GAMBIT_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  # Unless invoked with FORCE_O3, drop down to -O2 optimisation for more reasonable compile time.
  if (NOT DEFINED FORCE_O3)
    string(REGEX REPLACE "(-O3)" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    string(REGEX REPLACE "(-O3)" "-O2" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REGEX REPLACE "(-O3)" "-O2" CMAKE_Fortran_FLAGS_RELEASE "${CMAKE_Fortran_FLAGS_RELEASE}")
  endif()
  set(GAMBIT_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
  set(GAMBIT_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
  set(GAMBIT_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_RELEASE}")
  # Never send the -O3 from cmake's release build config onwards to backends, as some are touchy.
  string(REGEX REPLACE "(-O3)" "-O2" GAMBIT_C_FLAGS "${GAMBIT_C_FLAGS}")
  string(REGEX REPLACE "(-O3)" "-O2" GAMBIT_CXX_FLAGS "${GAMBIT_CXX_FLAGS}")
  string(REGEX REPLACE "(-O3)" "-O2" GAMBIT_Fortran_FLAGS "${GAMBIT_Fortran_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(GAMBIT_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
  set(GAMBIT_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  set(GAMBIT_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_RELWITHDEBINFO}")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(GAMBIT_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_MINSIZEREL}")
  set(GAMBIT_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MINSIZEREL}")
  set(GAMBIT_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_MINSIZEREL}")
else()
  set(GAMBIT_C_FLAGS "${CMAKE_C_FLAGS}")
  set(GAMBIT_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(GAMBIT_Fortran_FLAGS "${CMAKE_Fortran_FLAGS}")
endif()

# Check for optional packages and disable sections of GAMBIT accordingly
include(cmake/optional.cmake)

# Set the version number (later to come directly from git tag)
set(GAMBIT_VERSION_MAJOR 1)
set(GAMBIT_VERSION_MINOR 0)
set(GAMBIT_VERSION_REVISION 0)

# Add doxygen build as an external project
add_custom_target(docs WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND doxygen doc/doxygen.conf)

# Work out which modules to include in the compile
retrieve_bits(GAMBIT_BITS ${PROJECT_SOURCE_DIR} "${itch}" "Loud")

# Include contributed packages
include(cmake/contrib.cmake)

# Reprocess the ditch set into a comma-separated list
string (REPLACE ";" "," itch_with_commas "${itch}")

# Create the scratch directory if it isn't there already
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/scratch")
  message("${Yellow}-- Creating scratch directory${ColourReset}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory scratch WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  message("${Yellow}-- Creating scratch directory - done.${ColourReset}")
endif()

# Generate the ScannerBit compilation files
if(EXISTS "${PROJECT_SOURCE_DIR}/ScannerBit/")
  message("${Yellow}-- Updating GAMBIT scanner cmake and related files${ColourReset}")
  set(scanner_harvester ${PROJECT_SOURCE_DIR}/ScannerBit/scripts/scanner+_harvester.py ${PROJECT_BINARY_DIR} -x __not_a_real_name__,${itch_with_commas})
  execute_process(RESULT_VARIABLE result COMMAND python ${scanner_harvester} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
  check_result(${result} ${scanner_harvester})
  message("${Yellow}-- Updating GAMBIT scanner cmake and related files - done.${ColourReset}")
endif()

# Generate the cmake_variables.hpp file
include(cmake/preprocessor.cmake)

# Identify the different harvester scripts
set(MODEL_HARVESTER ${PROJECT_SOURCE_DIR}/Models/scripts/model_harvester.py)
set(BACKEND_HARVESTER ${PROJECT_SOURCE_DIR}/Backends/scripts/backend_harvester.py)
set(MODULE_HARVESTER ${PROJECT_SOURCE_DIR}/Elements/scripts/module_harvester.py)
set(PRINTER_HARVESTER ${PROJECT_SOURCE_DIR}/Printers/scripts/printer_harvester.py)
set(HARVEST_TOOLS ${PROJECT_SOURCE_DIR}/Utils/scripts/harvesting_tools.py)

# Create all_functor_types.hpp, module_rollcall.hpp, module_types_rollcall.hpp, models_rollcall.hpp,
# model_types_rollcall.hpp, backend_rollcall.hpp, backend_types_rollcall.hpp and printer_rollcall.hpp.
file(GLOB MODEL_HARVESTER_FILES   "${PROJECT_SOURCE_DIR}/Models/include/gambit/Models/models/*.hpp"
                                  "${PROJECT_SOURCE_DIR}/Models/CMakeLists.txt")
file(GLOB BACKEND_HARVESTER_FILES "${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/frontends/*.hpp"
                                  "${PROJECT_SOURCE_DIR}/Backends/CMakeLists.txt")
file(GLOB PRINTER_HARVESTER_FILES "${PROJECT_SOURCE_DIR}/Printers/include/gambit/Printers/printers/*.hpp"
                                  "${PROJECT_SOURCE_DIR}/Printers/CMakeLists.txt")
file(GLOB MODULE_HARVESTER_FILES  "${PROJECT_SOURCE_DIR}/*Bit*/include/gambit/*Bit*/*_rollcall.hpp"
                                  "${PROJECT_SOURCE_DIR}/*Bit*/include/gambit/*Bit*/*_types.hpp")
string (REPLACE "//" "/" MODEL_HARVESTER_FILES   "${MODEL_HARVESTER_FILES}")    # (GLOB creates erroneous double slashes)
string (REPLACE "//" "/" BACKEND_HARVESTER_FILES "${BACKEND_HARVESTER_FILES}")
string (REPLACE "//" "/" PRINTER_HARVESTER_FILES "${PRINTER_HARVESTER_FILES}")
string (REPLACE "//" "/" MODULE_HARVESTER_FILES  "${MODULE_HARVESTER_FILES}")
list(REMOVE_ITEM MODULE_HARVESTER_FILES "${PROJECT_SOURCE_DIR}/ScannerBit//include//gambit//ScannerBit//priors_rollcall.hpp"
                                        "${PROJECT_SOURCE_DIR}/ScannerBit//include//gambit//ScannerBit//test_function_rollcall.hpp")
list(APPEND MODULE_HARVESTER_FILES "${PROJECT_SOURCE_DIR}/config/resolution_type_equivalency_classes.yaml")
set(MODULE_HARVESTER_FILES ${MODULE_HARVESTER_FILES} ${BACKEND_HARVESTER_FILES})
remove_build_files(models_harvested backends_harvested modules_harvested printers_harvested)
add_gambit_custom(model_harvest   models_harvested   MODEL_HARVESTER   MODEL_HARVESTER_FILES)
add_gambit_custom(backend_harvest backends_harvested BACKEND_HARVESTER BACKEND_HARVESTER_FILES)
add_gambit_custom(module_harvest  modules_harvested  MODULE_HARVESTER  MODULE_HARVESTER_FILES)
add_gambit_custom(printer_harvest printers_harvested PRINTER_HARVESTER PRINTER_HARVESTER_FILES)
add_dependencies(module_harvest backend_harvest)
add_dependencies(printer_harvest module_harvest)

# Generate the CMakeLists.txt files for GAMBIT modules, Backends, Models and Printers)
message("${Yellow}-- Updating GAMBIT module, model, backend, and printer CMake files.${ColourReset}")
set(update_cmakelists ${PROJECT_SOURCE_DIR}/cmake/scripts/update_cmakelists.py -x __not_a_real_name__,${itch_with_commas})
execute_process(RESULT_VARIABLE result COMMAND python ${update_cmakelists} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
check_result(${result} ${update_cmakelists})
message("${Yellow}-- Updating GAMBIT module, backend, and printer CMake files - done.${ColourReset}")

# Include other cmake scripts
include(cmake/gambit.cmake)
include(cmake/externals.cmake)

# Add GAMBIT subdirectories.
add_subdirectory(Logs)
add_subdirectory(Utils)
add_subdirectory_if_present(Models)
add_subdirectory_if_present(Backends)
add_subdirectory_if_present(Elements)
add_subdirectory_if_present(Printers)
add_subdirectory_if_present(Core)

# Lists of different GAMBIT libraries to link
set(GAMBIT_BASIC_COMMON_LIBS ${GAMBIT_BASIC_COMMON_LIBS} gambit-Logs gambit-Utils)
set(GAMBIT_ALL_COMMON_LIBS ${GAMBIT_BASIC_COMMON_LIBS} gambit-Models gambit-Backends gambit-Elements)

# Set compilation targets for GAMBIT modules
foreach(bit ${GAMBIT_BITS})
  add_subdirectory(${bit})
  #set(GAMBIT_BIT_OBJECTS ${GAMBIT_BIT_OBJECTS} "$<TARGET_OBJECTS:${bit}>")
  set(GAMBIT_BIT_LIBS ${GAMBIT_BIT_LIBS} gambit-${bit})
endforeach()

# Add the executables
include(cmake/executables.cmake)

# Finish setting the link commands and rpath variables
include(${PROJECT_BINARY_DIR}/linkedout.cmake)
