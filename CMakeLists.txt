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

# Make sure the user hasn't accidentally set the C++ compiler to the C compiler.
get_filename_component(CXX_COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
if (CXX_COMPILER_NAME MATCHES "gcc.*$")
  message(FATAL_ERROR "\nYou have set CMAKE_CXX_COMPILER to gcc.  Did you mean g++?")
elseif (CXX_COMPILER_NAME MATCHES "clang($|-.*)")
  message(FATAL_ERROR "\nYou have set CMAKE_CXX_COMPILER to clang.  Did you mean clang++?")
elseif (CXX_COMPILER_NAME MATCHES "icc.*$")
  message(FATAL_ERROR "\nYou have set CMAKE_CXX_COMPILER to icc.  Did you mean icpc?")
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

# Include ./cmake in search path for projects
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

# Add common system library search variables to cmake library search variable, used by find_library
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} $ENV{LIBRARY_PATH})
string(REPLACE ":" ";" CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH}")

# When building, use the install RPATH already
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# Add the automatically determined parts of the RPATH that point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Include cmake utility scripts, including colour definitions.
include(cmake/utilities.cmake)

# Check for Python interpreter
# We also need to search for PythonLibs before letting pybind11 look for them,
# otherwise it seems to get it wrong.  Also, we need to add versions of python
# greater than 3.3 manually, for compatibility with CMake 2.8.12.
set(Python_ADDITIONAL_VERSIONS 3.4 3.5 3.6 3.7)
if (FORCE_PYTHON2)
  message("${BoldYellow}   Python 2 requested; searching for Python 2.7${ColourReset}")
  find_package(PythonInterp 2.7 REQUIRED)
  find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT)
elseif (FORCE_PYTHON3)
  message("${BoldYellow}   Python 3 requested; searching for Python 3.x${ColourReset}")
  find_package(PythonInterp 3 REQUIRED)
  find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT)
else()
  find_package(PythonInterp 3)
  if(PYTHONINTERP_FOUND)
    find_package(PythonLibs 3)
  else()
    message("${BoldYellow}   Python 3 not found, searching for Python 2.7${ColourReset}")
    find_package(PythonInterp 2 REQUIRED)
    if (PYTHON_VERSION_MINOR LESS 7)
      message(FATAL_ERROR "\nGAMBIT requires Python 2.7.  \nIf you need to set the path to the Python interpreter manually, "
                          "please use -DPYTHON_EXECUTABLE:FILEPATH=path/to/preferred/python.")
    endif()
    find_package(PythonLibs 2)
  endif()
endif()
message("${BoldYellow}   Using Python interpreter version ${PYTHON_VERSION_STRING} for build.${ColourReset}")
if(PYTHONLIBS_FOUND)
  message("${BoldYellow}   Using Python libraries version ${PYTHONLIBS_VERSION_STRING} for Python backend support.${ColourReset}")
  if (NOT "${PYTHON_VERSION_STRING}" STREQUAL "${PYTHONLIBS_VERSION_STRING}")
    message("${BoldRed}   NOTE: You are using different Python versions for the interpreter and the libraries!${ColourReset}\n"
            "   In principle this should be fine, as the interpreter is only used for building GAMBIT, and the\n"
            "   libraries are only used for providing support for Python backends at runtime.  However, if you\n"
            "   have matching versions installed, you can make this message go away by trying the following\n"
            "   (making sure to clean out your build directory in between any such changes):\n"
            "   1. invoke cmake as cmake -DFORCE_PYTHON2=True .. (or similar)\n"
            "   2. invoke cmake as cmake -DFORCE_PYTHON3=True .. (or similar)\n"
            "   3. set the following variables when invoking cmake:\n"
            "     PYTHON_LIBRARY\n"
            "     PYTHON_INCLUDE_DIR\n"
            "     PYTHON_INCLUDE_DIR2 (you might be able to get away without setting this one)\n"
            "     PYTHON_EXECUTABLE   (you might be able to get away without setting this one)\n")
  endif()
endif()

# Check for pybind11 if PythonLibs were found
if(NOT PYTHONLIBS_FOUND)
  message("${BoldRed}   PythonLibs NOT found, so pybind11 cannot be used. Ditching support for Python backends.${ColourReset}\n"
          "   If you *do* have the Python libraries installed, you should first try setting/unsetting\n"
          "   FORCE_PYTHON2 or FORCE_PYTHON3 when invoking cmake (make sure to clean out your build\n"
          "   directory in between any such changes).  If that does not work, you can manually set the\n"
          "   following variables when invoking cmake (also making sure to clean out your build dir):\n"
          "     PYTHON_LIBRARY\n"
          "     PYTHON_INCLUDE_DIR\n"
          "     PYTHON_INCLUDE_DIR2 (you might be able to get away without setting this one)\n"
          "     PYTHON_EXECUTABLE   (you might be able to get away without setting this one)")
else()
  set(MIN_pybind11_VERSION "2.4.3")
  set(PREFERRED_pybind11_VERSION "2.4.3")
  set(pybind11_CONTRIB_DIR "${PROJECT_SOURCE_DIR}/contrib/pybind11")
  find_package(pybind11 QUIET)
  if(NOT pybind11_FOUND AND EXISTS "${pybind11_CONTRIB_DIR}")
    use_contributed_pybind11()
  endif()
  if(pybind11_FOUND)
    if(pybind11_VERSION VERSION_LESS MIN_pybind11_VERSION)
      message("${BoldRed}   Found pybind11 ${pybind11_VERSION}. GAMBIT requires at least v${MIN_pybind11_VERSION}.${ColourReset}")
      set(pybind11_FOUND FALSE)
    else()
      message("${BoldYellow}   Found pybind11 ${pybind11_VERSION} at ${pybind11_DIR}.${ColourReset}")
      include_directories("${PYTHON_INCLUDE_DIRS};${PYBIND11_INCLUDE_DIR}")
    endif()
  else()
    message("${BoldRed}   The pybind11 library is not properly installed.${ColourReset}")
  endif()
  if(NOT pybind11_FOUND AND NOT EXISTS "${pybind11_CONTRIB_DIR}")
    message("${BoldRed}   CMake will now download and install pybind11 v${PREFERRED_pybind11_VERSION}.${ColourReset}")
    execute_process(RESULT_VARIABLE result COMMAND git clone https://github.com/pybind/pybind11.git ${pybind11_CONTRIB_DIR})
    if(${result} STREQUAL "0")
      execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${pybind11_CONTRIB_DIR} git checkout -q v${PREFERRED_pybind11_VERSION})
      use_contributed_pybind11()
      include_directories("${PYTHON_INCLUDE_DIRS};${PYBIND11_INCLUDE_DIR}")
    else()
      message("${BoldRed}   Attempt to clone git repository for pybind11 failed.  This may be because you are disconnected from the internet.\n   "
              "Otherwise, your git installation may be faulty. Errors about missing .so files are usually due to\n   "
              "your git installation being linked to a buggy version of libcurl.  In that case, try reinstalling libcurl.${ColourReset}")
    endif()
  endif()
  set(HAVE_PYBIND11 "${pybind11_FOUND}")
endif()

# Check for required Python libraries
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

# Check for C++11, C++14 and C++17 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
  CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1z)
  CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
  if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  else()
    CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1y)
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

# Fix Boost < 1.55 for Clang
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  if(${CMAKE_VERSION} VERSION_LESS 3.12.0)
    add_definitions(-DBOOST_PP_VARIADICS=1)
  else()
    add_compile_definitions(BOOST_PP_VARIADICS=1)
  endif()
endif()

# Check for Eigen
find_package(Eigen3 3.1.0)
if(EIGEN3_FOUND)
  include_directories("${EIGEN3_INCLUDE_DIR}")
  message("-- Eigen version: ${EIGEN3_VERSION}")
else()
  message("${BoldRed}   Eigen v3.1.0 or greater not found.  FlexibleSUSY and GM2Calc interfaces will be excluded.${ColourReset}")
  set(itch "${itch};gm2calc;flexiblesusy")
  message(FATAL_ERROR "\nFlexibleSUSY is currently included in the GAMBIT distribution, so in fact it cannot be ditched.  Please install Eigen3.\n(Note that this will change in future GAMBIT versions, where FlexibleSUSY will be a 'true' backend.)")
endif()

# Check for OpenMP
find_package(OpenMP QUIET)
if (OPENMP_FOUND)
  message("-- OpenMP found successfully")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  if (NOT DEFINED OpenMP_Fortran_FLAGS)
    set(OpenMP_Fortran_FLAGS "-fopenmp")
  endif()
  set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${OpenMP_Fortran_FLAGS}")
else()
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    find_program(BREW NAMES brew)
    # This block modified from https://github.com/CLIUtils/cmake/blob/master/PatchOpenMPApple.cmake
    if(BREW)
      execute_process(COMMAND ${BREW} ls libomp RESULT_VARIABLE BREW_RESULT_CODE OUTPUT_QUIET ERROR_QUIET)
      if(BREW_RESULT_CODE)
        message(FATAL_ERROR "You are using the Apple Clang compiler, and have HomeBrew installed, but have not installed OpenMP. Please run \"brew install libomp\"")
      else()
        execute_process(COMMAND ${BREW} --prefix libomp OUTPUT_VARIABLE BREW_LIBOMP_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
        set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
        set(OpenMP_CXX_LIB_NAMES "omp")
        set(OpenMP_omp_LIBRARY "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib")
        include_directories("${BREW_LIBOMP_PREFIX}/include")
        message(STATUS "Using Homebrew libomp from ${BREW_LIBOMP_PREFIX}")
      endif()
    else()
      message(FATAL_ERROR "\nOpenMP libraries not found. You are using the Apple Clang compiler. The easiest way to get OpenMP support for Apple Clang is to install it via HomeBrew. If you want to install it some other way, e.g. via MacPorts, you need to manually set -DOpenMP_CXX_FLAGS -DOpenMP_CXX_LIB_NAMES -DOpenMP_C_FLAGS -DOpenMP_C_LIB_NAMES -DOpenMP_omp_LIBRARY when invoking cmake.")
    endif()
  else()
    message(FATAL_ERROR "\nOpenMP libraries not found.  Your compiler installation seems to be broken.")
  endif()
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

# Check for Mathematica
string(REGEX MATCH ";M;|;Ma;|;Mat;|;Math;|;Mathe;|;Mathem;|;Mathema;|;Mathemat;|;Mathemati;|;Mathematic;|;Mathematica;|;m;|;ma;|;mat;|;math;|;mathe;|;mathem;|;mathema;|;mathemat;|;mathemati;|;mathematic;|;mathematica" DITCH_MATHEMATICA ";${itch};")
if(DITCH_MATHEMATICA)
  set(HAVE_MATHEMATICA 0)
  message("${BoldCyan} X Excluding Mathematica from GAMBIT configuration. All backends using Mathematica will be disabled${ColourReset}")
else()
  find_library(LIBUUID NAMES uuid)
  if(LIBUUID)
    message("   Found library libuuid")
    find_package(Mathematica 10.0)
    if(Mathematica_FOUND AND (NOT DEFINED Mathematica_Invalid_License OR IGNORE_MATHEMATICA_LICENSE))
      message("${BoldYellow}   Found Mathematica.${ColourReset}")
      if(Mathematica_WSTP_FOUND)
        message("${BoldYellow}   Found Wolfram Symbolic Transfer Protocol. Mathematica backends enabled.${ColourReset}")
        set(HAVE_MATHEMATICA 1)
        set(MATHEMATICA_WSTP_H "${Mathematica_WSTP_INCLUDE_DIR}/wstp.h")
        set(MATHEMATICA_KERNEL "${Mathematica_KERNEL_EXECUTABLE}")
        set(MATHEMATICA_WSTP_VERSION_MAJOR ${Mathematica_WSTP_VERSION_MAJOR})
        set(MATHEMATICA_WSTP_VERSION_MINOR ${Mathematica_WSTP_VERSION_MINOR})
      else()
        message("${BoldRed}  WSTP not found. Please make sure it is installed before attempting to use Mathematica backends.${ColourReset}")
        set(HAVE_MATHEMATICA 0)
      endif()
    elseif(DEFINED Mathematica_Invalid_License AND NOT IGNORE_MATHEMATICA_LICENSE)
      message("${BoldRed}   Mathematica found but with an invalid license. Backends using Mathematica will be disabled.${ColourReset}")
      message("${BoldRed}   To ignore this license check, add -DIGNORE_MATHEMATICA_LICENSE=True to your cmake command.${ColourReset}")
      set(HAVE_MATHEMATICA 0)
    else()
      message("${BoldRed}   Mathematica not found. Backends using Mathematica will be disabled.${ColourReset}")
      set(HAVE_MATHEMATICA 0)
    endif()
  else()
    message("${BoldRed}   Missing library libuuid required for WSTP. Mathematica will be disabled.${ColourReset}")
    set(HAVE_MATHEMATICA 0)
  endif()
endif()

# Check for DL libraries
include(cmake/FindLibDL.cmake)

# Add compiler warning flags
include(cmake/warnings.cmake)

# Construct the full set of compiler flags to be used for external projects
set(BACKEND_C_FLAGS_NO_BUILD_OPTIMISATIONS "${CMAKE_C_FLAGS}")
set(BACKEND_CXX_FLAGS_NO_BUILD_OPTIMISATIONS "${CMAKE_CXX_FLAGS}")
set(BACKEND_Fortran_FLAGS_NO_BUILD_OPTIMISATIONS "${CMAKE_Fortran_FLAGS}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
  set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
  set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  # Unless invoked with FORCE_O3, drop down to -O2 optimisation for more reasonable compile time.
  if (NOT DEFINED FORCE_O3)
    string(REGEX REPLACE "(-O3)" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    string(REGEX REPLACE "(-O3)" "-O2" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REGEX REPLACE "(-O3)" "-O2" CMAKE_Fortran_FLAGS_RELEASE "${CMAKE_Fortran_FLAGS_RELEASE}")
  endif()
  set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
  set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
  set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_RELEASE}")
  # Never send the -O3 from cmake's release build config onwards to backends, as some are touchy.
  string(REGEX REPLACE "(-O3)" "-O2" BACKEND_C_FLAGS "${BACKEND_C_FLAGS}")
  string(REGEX REPLACE "(-O3)" "-O2" BACKEND_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
  string(REGEX REPLACE "(-O3)" "-O2" BACKEND_Fortran_FLAGS "${BACKEND_Fortran_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
  set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_RELWITHDEBINFO}")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_MINSIZEREL}")
  set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MINSIZEREL}")
  set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_MINSIZEREL}")
else()
  set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS}")
  set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS}")
endif()

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
include(cmake/optional.cmake)

# Look for the latest tag and use it to set the version number.  If there is no such tag, use the tarball info file.
find_package(Git)
if(GIT_FOUND)
  get_version_from_git(GAMBIT_VERSION_MAJOR GAMBIT_VERSION_MINOR GAMBIT_VERSION_REVISION
                       GAMBIT_VERSION_PATCH GAMBIT_VERSION_FULL)
  if (GAMBIT_VERSION_MAJOR)
    message("${BoldYellow}   GAMBIT version detected from git tag: ${GAMBIT_VERSION_FULL}${ColourReset}")
  endif()
endif()
if(NOT GIT_FOUND OR NOT GAMBIT_VERSION_MAJOR)
  message("${BoldYellow}   GAMBIT version not detected via git.  Reverting to cmake/tarball_info.cmake.${ColourReset}")
  include(cmake/tarball_info.cmake)
endif()

# Add doxygen build as an external project
add_custom_target(docs WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND doxygen doc/doxygen.conf)

# Work out which modules to include in the compile
retrieve_bits(GAMBIT_BITS ${PROJECT_SOURCE_DIR} "${itch}" "Loud")

# Set up targets to make standalone tarballs of the different modules
add_standalone_tarballs("${GAMBIT_BITS}" "${GAMBIT_VERSION_FULL}")

# Include contributed packages
include(cmake/contrib.cmake)

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
include(cmake/preprocessor.cmake)

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
  add_gambit_custom(module_harvest modules_harvested MODULE_HARVESTER  MODULE_HARVESTER_FILES)
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/Backends/")
  add_gambit_custom(backend_harvest backends_harvested BACKEND_HARVESTER BACKEND_HARVESTER_FILES)
  add_dependencies(module_harvest backend_harvest)
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/Models/")
 add_gambit_custom(model_harvest models_harvested MODEL_HARVESTER MODEL_HARVESTER_FILES)
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/Printers/")
  add_gambit_custom(printer_harvest printers_harvested PRINTER_HARVESTER PRINTER_HARVESTER_FILES)
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
