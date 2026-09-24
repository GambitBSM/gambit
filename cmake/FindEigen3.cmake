# - Try to find Eigen3 lib
#
# This module supports requiring a minimum version, e.g. you can do
#   find_package(Eigen3 3.1.2)
# to require version 3.1.2 or newer of Eigen3.
#
# Once done this will define
#
#  EIGEN3_FOUND - system has eigen lib with correct version
#  EIGEN3_INCLUDE_DIR - the eigen include directory
#  EIGEN3_VERSION - eigen version
#
# This module reads hints about search locations from
# the following enviroment variables:
#
# EIGEN3_ROOT
# EIGEN3_ROOT_DIR

# Copyright (c) 2006, 2007 Montel Laurent, <montel@kde.org>
# Copyright (c) 2008, 2009 Gael Guennebaud, <g.gael@free.fr>
# Copyright (c) 2009 Benoit Jacob <jacob.benoit.1@gmail.com>
# Redistribution and use is allowed according to the terms of the 2-clause BSD license.

if(NOT Eigen3_FIND_VERSION)
  if(NOT Eigen3_FIND_VERSION_MAJOR)
    set(Eigen3_FIND_VERSION_MAJOR 2)
  endif(NOT Eigen3_FIND_VERSION_MAJOR)
  if(NOT Eigen3_FIND_VERSION_MINOR)
    set(Eigen3_FIND_VERSION_MINOR 91)
  endif(NOT Eigen3_FIND_VERSION_MINOR)
  if(NOT Eigen3_FIND_VERSION_PATCH)
    set(Eigen3_FIND_VERSION_PATCH 0)
  endif(NOT Eigen3_FIND_VERSION_PATCH)

  set(Eigen3_FIND_VERSION "${Eigen3_FIND_VERSION_MAJOR}.${Eigen3_FIND_VERSION_MINOR}.${Eigen3_FIND_VERSION_PATCH}")
endif(NOT Eigen3_FIND_VERSION)

macro(_eigen3_check_version)
  file(READ "${EIGEN3_INCLUDE_DIR}/Eigen/src/Core/util/Macros.h" _eigen3_version_header)

  # Eigen 3.x exposes EIGEN_WORLD_VERSION / EIGEN_MAJOR_VERSION / EIGEN_MINOR_VERSION.
  # Eigen >= 5.0 dropped EIGEN_WORLD_VERSION (the leading "3" became part of the package
  # name) and does not define these version macros. We can dig it out of their *proper*
  # CMake config file, in lieu of migrating to use their more modern CMake setup.
  string(REGEX MATCH "define[ \t]+EIGEN_WORLD_VERSION[ \t]+([0-9]+)" _eigen3_world_version_match "${_eigen3_version_header}")
  set(EIGEN3_WORLD_VERSION "${CMAKE_MATCH_1}")
  string(REGEX MATCH "define[ \t]+EIGEN_MAJOR_VERSION[ \t]+([0-9]+)" _eigen3_major_version_match "${_eigen3_version_header}")
  set(EIGEN3_MAJOR_VERSION "${CMAKE_MATCH_1}")
  string(REGEX MATCH "define[ \t]+EIGEN_MINOR_VERSION[ \t]+([0-9]+)" _eigen3_minor_version_match "${_eigen3_version_header}")
  set(EIGEN3_MINOR_VERSION "${CMAKE_MATCH_1}")
  string(REGEX MATCH "define[ \t]+EIGEN_PATCH_VERSION[ \t]+([0-9]+)" _eigen3_patch_version_match "${_eigen3_version_header}")
  set(EIGEN3_PATCH_VERSION "${CMAKE_MATCH_1}")

  # Detect which scheme the installed Eigen uses so we report the correct version string.
  if(EIGEN3_WORLD_VERSION STREQUAL "")
    # New (>= 5.0) naming scheme.
    # Guess the Eigen cmake dir location relative to the include dir -- not robust,
    # but the version isn't encoded in the headers anymore
    file(READ "${EIGEN3_INCLUDE_DIR}/../../share/eigen3/cmake/Eigen3ConfigVersion.cmake" _eigen3_version_cmake)
    #message("${_eigen3_version_cmake}")
    string(REGEX MATCH "PACKAGE_VERSION .([0-9.]+)" _eigen3_cmake_version_match "${_eigen3_version_cmake}")
    #message(STATUS "${_eigen3_cmake_version_match}")
    #message(STATUS "${CMAKE_MATCH_1}")
    set(EIGEN3_VERSION "${CMAKE_MATCH_1}")
  else()
    # Legacy 3.x naming scheme.
    set(EIGEN3_VERSION ${EIGEN3_WORLD_VERSION}.${EIGEN3_MAJOR_VERSION}.${EIGEN3_MINOR_VERSION})
  endif()
  
  set(EIGEN3_VERSION_OK TRUE)
  if(${EIGEN3_VERSION} VERSION_LESS ${Eigen3_FIND_VERSION})
    set(EIGEN3_VERSION_OK FALSE)
  else()
    set(EIGEN3_VERSION_OK TRUE)
  endif()

  if(NOT EIGEN3_VERSION_OK)
    message(STATUS "Eigen3 version ${EIGEN3_VERSION} found in ${EIGEN3_INCLUDE_DIR}, "
                   "but at least version ${Eigen3_FIND_VERSION} is required")
  endif(NOT EIGEN3_VERSION_OK)
endmacro(_eigen3_check_version)

if (EIGEN3_INCLUDE_DIR)

  # in cache already
  _eigen3_check_version()
  set(EIGEN3_FOUND ${EIGEN3_VERSION_OK})

else (EIGEN3_INCLUDE_DIR)

  # search first if an Eigen3Config.cmake is available in the system,
  # if successful this would set EIGEN3_INCLUDE_DIR and the rest of
  # the script will work as usual
  find_package(Eigen3 ${Eigen3_FIND_VERSION} NO_MODULE QUIET)

  if(NOT EIGEN3_INCLUDE_DIR)
    find_path(EIGEN3_INCLUDE_DIR NAMES signature_of_eigen3_matrix_library
        HINTS
        ENV EIGEN3_ROOT
        ENV EIGEN3_ROOT_DIR
        PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        ${KDE4_INCLUDE_DIR}
        PATH_SUFFIXES eigen3 eigen
      )
  endif(NOT EIGEN3_INCLUDE_DIR)

  if(EIGEN3_INCLUDE_DIR)
    _eigen3_check_version()
  endif(EIGEN3_INCLUDE_DIR)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Eigen3 DEFAULT_MSG EIGEN3_INCLUDE_DIR EIGEN3_VERSION_OK)

  mark_as_advanced(EIGEN3_INCLUDE_DIR)

endif(EIGEN3_INCLUDE_DIR)
