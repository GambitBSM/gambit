#  GUM: GAMBIT Universal Models
#  ****************************
#  \file
#
#  Master CMake configuration script for GUM
#
# **** *************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2019, 2020
#
#  \author Janina Renk
#          (janina.renk@fysik.su.se)
#  \date 2020
#
#  **************************************

cmake_minimum_required(VERSION 2.8)
project(GUM)
message("   Building GUM in ${CMAKE_CURRENT_SOURCE_DIR}")
include(ExternalProject)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Define the main GUM directory
set(GUM_DIR ${PROJECT_SOURCE_DIR})

# Cleaning steps
add_custom_target(distclean COMMAND ${CMAKE_MAKE_PROGRAM} clean)
add_custom_target(nuke-all DEPENDS distclean nuke-contrib)

# Define the sed command to use differently for OSX and linux.
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(dashi "-i ''")
else()
  set(dashi "-i")
endif()

# Set a consistent MACOSX_RPATH default across all CMake versions.
# When CMake 2.8.12 is required, change this default to 1.
# When CMake 3.0.0 is required, remove this block (see CMP0042).
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

# Check for Mathematica
include(../cmake/FindMathematica.cmake)
if(Mathematica_FOUND)
  message("   Found Mathematica")
  if(Mathematica_WSTP_FOUND)
    message("   Found Wolfram Symbolic Transfer Protocol. Mathematica interface enabled.")
    set(HAVE_MATHEMATICA 1)
    set(MATHEMATICA_WSTP_H "${Mathematica_WSTP_INCLUDE_DIR}/wstp.h")
    set(MATHEMATICA_KERNEL "${Mathematica_KERNEL_EXECUTABLE}")
  else()
    message(FATAL_ERROR "  WSTP not found. Please make sure it is installed before attempting to use Mathematica interface.")
    set(HAVE_MATHEMATICA 0)
  endif()
else()
  message(FATAL_ERROR "  Mathematica not found. GUM won't work.")
  set(HAVE_MATHEMATICA 0)
endif()

if(Mathematica_FOUND AND Mathematica_WSTP_FOUND)
  set(LIBRARIES ${LIBRARIES} ${Mathematica_WSTP_LIBRARIES} ${Mathematica_MathLink_LIBRARY})
endif()

# Contrib packages
include(cmake/contrib.cmake)

# Check for Python interpreter
# Also, we need to add versions of python  greater than 3.3 manually,
# for compatibility with CMake 2.8.12.
set(Python_ADDITIONAL_VERSIONS 3.4 3.5 3.6 3.7)
# If both FORCE_PYTHON2 and FORCE_PYTHON3 are set, throw error
if (FORCE_PYTHON2 AND FORCE_PYTHON3)
  message(FATAL_ERROR "Two different versions of python requested. Switch either FORCE_PYTHON2 or FORCE_PYTHON3 off.")
endif()
if (FORCE_PYTHON2)
  message("  Python 2 requested; searching for Python 2.7.")
  find_package(PythonInterp 2.7 REQUIRED)
  find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT)
elseif (FORCE_PYTHON3)
  message("  Python 3 requested; searching for Python 3.x.")
  find_package(PythonInterp 3 REQUIRED)
  find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT)
else()
  find_package(PythonInterp 3)
  if(PYTHONINTERP_FOUND)
    find_package(PythonLibs 3)
  else()
    message("  Python 3 not found, searching for Python 2.7.")
    find_package(PythonInterp 2 REQUIRED)
    if (PYTHON_VERSION_MINOR LESS 7)
      message(FATAL_ERROR "\nGUM requires Python 2.7.  \nIf you need to set the path to the Python interpreter manually, "
                          "please use -DPYTHON_EXECUTABLE:FILEPATH=path/to/preferred/python.")
    endif()
    find_package(PythonLibs 2 REQUIRED)
  endif()
endif()
include_directories(${PYTHON_INCLUDE_DIRS})
message("   Using Python interpreter version ${PYTHON_VERSION_STRING} for build.")

if(PYTHONLIBS_FOUND)
  string(FIND "${PYTHONLIBS_VERSION_STRING}" "2.7" PY2_POSITION)
  if(PY2_POSITION EQUAL 0)
    set(UNSUPPORTED_PYTHON_VERSION "3")
  else()
    set(UNSUPPORTED_PYTHON_VERSION "2.7")
  endif()
  message("   Using Python libraries version ${PYTHONLIBS_VERSION_STRING}.")
  # Remove trailing non-numeric characters from version
  string(REGEX REPLACE "[a-zA-Z]" "" PYTHONLIBS_VERSION_STRING_CLEAN ${PYTHONLIBS_VERSION_STRING})
  if (NOT "${PYTHON_VERSION_STRING}" STREQUAL "${PYTHONLIBS_VERSION_STRING_CLEAN}")
    message("  You are using different Python versions for the interpreter and the libraries! GUM might not work, please make sure to have matching versions installed.")
  endif()
else()
 message(FATAL_ERROR "  PythonLibs for Python version ${PYTHON_VERSION_STRING} NOT found! Plase make sure to install them to work with GUM.\n"
          "  If you *do* have the Python libraries installed, you should first try one of the following\n"
          "   (making sure to clean out your build directory in between any such changes):\n"
          "   1. invoke cmake as cmake -DFORCE_PYTHON2=True .. (or similar)\n"
          "   2. invoke cmake as cmake -DFORCE_PYTHON3=True .. (or similar)\n"
          "   3. set the following variables when invoking cmake:\n"
          "     PYTHON_LIBRARY\n"
          "     PYTHON_INCLUDE_DIR\n"
          "     PYTHON_EXECUTABLE\n")
endif()

# Simple function to find specific Python modules
macro(find_python_module module)
  execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import ${module}" RESULT_VARIABLE return_value ERROR_QUIET)
  if (NOT return_value)
    message(STATUS "Found Python module ${module}.")
    set(PY_${module}_FOUND TRUE)
  else()
    if(${ARGC} GREATER 1 AND ${ARGV1} STREQUAL "REQUIRED")
      message(FATAL_ERROR "-- FAILED to find Python module ${module}.")
    else()
      message(STATUS "FAILED to find Python module ${module}.")
    endif()
  endif()
endmacro()

# Check for required Python libraries
foreach(module yaml os re datetime sys getopt shutil itertools collections copy numpy distutils filecmp glob six argparse future)
  find_python_module(${module} REQUIRED)
endforeach()

# Add -fPIC for 64 bit systems
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Check for C++11 and C++14 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
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

# Check for Boost & drop FeynRules/SARAH shared object files.
# Note that for some Boost versions (1.67 or later, but also 1.58 sometimes), we'll need to match the Python version with the component, as e.g. COMPONENTS "python36".
# To avoid differences, we just look for the main library name, e.g. libboost_python3-py36.so
# In OSX, for Boost versions at least 1.62 the component name also needs changing
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost 1.41.0 QUIET)
if(Boost_FOUND)
  if(PYTHON_VERSION_MAJOR EQUAL 2)
    set(python_component python)
  elseif(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND Boost_VERSION LESS 105800)
    set(python_component python3)
  elseif(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND Boost_VERSION LESS 106700)
    set(python_component python-py${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
  else()
    set(python_component python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} )
  endif()
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,dynamic_lookup")
    set(python_component "${python_component}-mt")
  else()
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
  endif()
  find_package(Boost 1.41.0 REQUIRED COMPONENTS ${python_component} filesystem system)
  include_directories("${Boost_INCLUDE_DIR}")
  add_library(fr SHARED src/feynrules.cpp src/math_package.cpp)
  target_link_libraries(fr ${LIBRARIES} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
  add_library(sarah SHARED src/sarah.cpp src/math_package.cpp)
  target_link_libraries(sarah ${LIBRARIES} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
else()
  message(FATAL_ERROR "\nGUM requires Boost v1.41 or greater, including the compiled libraries Boost.Python, Boost.System and Boost.Filesystem.\nPlease install suitable Boost components and rerun cmake.")
endif()

# Configure cmake variables files
set(outfile "${PROJECT_SOURCE_DIR}/include/cmake_variables.hpp")
configure_file("${outfile}.in" ${outfile})
set(outfile "${PROJECT_SOURCE_DIR}/src/cmake_variables.py")
configure_file("${outfile}.in" ${outfile})

include_directories(src include ${Mathematica_WSTP_INCLUDE_DIR})

# set source and header files used in all executables
set(HEADER_FILES include/cmake_variables.hpp include/options.hpp include/math_package.hpp include/feynrules.hpp include/sarah.hpp)
set(SRC_FILES src/mathematica.cpp)
set(SRC_GUM src/mathematica.cpp src/options.cpp)
set(GUM_LIBS sarah fr)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS -L.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(mathematica ${SRC_GUM} ${HEADER_FILES})

TARGET_LINK_LIBRARIES(mathematica ${LIBRARIES} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${GUM_LIBS})

if (CMAKE_COMPILER_IS_GNUCXX)
    message("   Setting GCC flags")

    # Remove the -g flag when not debugging
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall -Wextra -W -pedantic -std=c++0x -O3")
else()
    message(status ": Setting MSVC flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
install(TARGETS mathematica DESTINATION ${CMAKE_BINARY_DIR}/lib)
