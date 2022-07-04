# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration script to arrange warning
#  options when compiling GAMBIT.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#
#  \author Andy Buckley
#          (andy.buckley@cern.ch)
#  \date 2016 Feb
#
#************************************************

option(WERROR "WERROR" OFF)

include(CheckCXXCompilerFlag)

macro(set_compiler_warning warning current_flags)
  CHECK_CXX_COMPILER_FLAG("-W${warning}" CXX_SUPPORTS_${warning})
  if (CXX_SUPPORTS_${warning})
    set(${current_flags} "${${current_flags}} -W${warning}")
  endif()
endmacro()

if(${WERROR})
  set_compiler_warning("error")
else()
  message(STATUS "${Red}Werror is disabled${ColourReset}")
endif()

set_compiler_warning("all" CMAKE_CXX_FLAGS)
set_compiler_warning("extra" CMAKE_CXX_FLAGS)
set_compiler_warning("no-misleading-indentation" CMAKE_CXX_FLAGS)

if(EIGEN3_FOUND AND EIGEN3_VERSION VERSION_LESS 3.3.0)
  set_compiler_warning("no-ignored-attributes" CMAKE_CXX_FLAGS)
  set_compiler_warning("no-deprecated-register" CMAKE_CXX_FLAGS)
  set_compiler_warning("no-deprecated-declarations" CMAKE_CXX_FLAGS)
endif()

# set intel warnings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # "remark #981: operands are evaluated in unspecified order"
  # This is a false positive, suppress it.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd981")

  # "remark #1418: external function definition with no prior declaration"
  # This can safely be ignord according to the ICC docs.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd1418")

  # "remark #1419: external declaration in primary source file"
  # This can safely be ignord according to the ICC docs.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd1419")
endif()

# Set warnings to stop complaints about old Python headers not being C++17 compliant
if(PYTHON_VERSION_MAJOR EQUAL 2)
  set_compiler_warning("no-register" CMAKE_CXX_FLAGS)
endif()

# Set warnings to stop complaining about deprecated copies in Eigen
if(EIGEN3_MAJOR_VERSION LESS 4 AND EIGEN3_MINOR_VERSION LESS 8)
  set_compiler_warning("no-deprecated-copy" CMAKE_CXX_FLAGS)
endif()
