# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration script to do Mac OSX
#  things for GAMBIT.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#  \date 2022 Jan
#
#  \author Are Raklev
#          (ahye@fys.uio.no)
#  \date 2023 Feb
#
#  \author Pengxuan Zhu
#          (pengxuan.zhu@adelaide.edu.au)
#  \date 2026 Aug, Oct
#
#************************************************

# Set a consistent MACOSX_RPATH default across all CMake versions.
# When CMake 3 is required, remove this block (see CMP0042).
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 1)
endif()

function(gambit_initialise_macos_sdk)
  if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    return()
  endif()

  # Resolve once before project(), so native and external compiler commands
  # use the same SDK. A cached selection takes precedence over SDKROOT.
  set(_gambit_sdk "${CMAKE_OSX_SYSROOT}")
  if(NOT "${_gambit_sdk}" STREQUAL "")
    set(_gambit_sdk_source CMAKE_OSX_SYSROOT)
  elseif(NOT "$ENV{SDKROOT}" STREQUAL "")
    set(_gambit_sdk "$ENV{SDKROOT}")
    set(_gambit_sdk_source SDKROOT)
  else()
    set(_gambit_sdk macosx)
    set(_gambit_sdk_source "automatic discovery")
  endif()

  if(IS_ABSOLUTE "${_gambit_sdk}" OR _gambit_sdk MATCHES "/")
    get_filename_component(_gambit_sdk_path "${_gambit_sdk}" ABSOLUTE)
  else()
    execute_process(
      COMMAND xcrun --sdk "${_gambit_sdk}" --show-sdk-path
      RESULT_VARIABLE _gambit_sdk_result
      OUTPUT_VARIABLE _gambit_sdk_path
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_VARIABLE _gambit_sdk_error
      TIMEOUT 10)
    if(NOT _gambit_sdk_result EQUAL 0)
      message(FATAL_ERROR
        "Cannot resolve macOS SDK '${_gambit_sdk}' from ${_gambit_sdk_source}: ${_gambit_sdk_error}. "
        "Set -DCMAKE_OSX_SYSROOT=<SDK directory or name> explicitly.")
    endif()
  endif()
  if("${_gambit_sdk_path}" STREQUAL "" OR NOT IS_DIRECTORY "${_gambit_sdk_path}")
    message(FATAL_ERROR
      "macOS SDK '${_gambit_sdk}' from ${_gambit_sdk_source} does not resolve to an existing directory. "
      "Set -DCMAKE_OSX_SYSROOT=<SDK directory or name> explicitly.")
  endif()
  set(CMAKE_OSX_SYSROOT "${_gambit_sdk_path}" CACHE PATH "macOS SDK directory" FORCE)
  set(CMAKE_OSX_SYSROOT "${_gambit_sdk_path}" PARENT_SCOPE)
endfunction()

function(gambit_initialise_macos_deployment_target)
  if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    return()
  endif()

  # Keep one project-level deployment target.  Honour CMake's standard value
  # on a fresh configure, otherwise use the selected SDK as the local default.
  set(MACOS_DEPLOYMENT_TARGET "${CMAKE_OSX_DEPLOYMENT_TARGET}" CACHE STRING
      "Minimum macOS version for GAMBIT and all external packages")
  if("${MACOS_DEPLOYMENT_TARGET}" STREQUAL "")
    set(_gambit_sdk "${CMAKE_OSX_SYSROOT}")
    if("${_gambit_sdk}" STREQUAL "")
      set(_gambit_sdk macosx)
    endif()
    execute_process(
      COMMAND xcrun --sdk "${_gambit_sdk}" --show-sdk-version
      RESULT_VARIABLE _gambit_sdk_version_result
      OUTPUT_VARIABLE MACOS_DEPLOYMENT_TARGET
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
      TIMEOUT 10)
    if(NOT _gambit_sdk_version_result EQUAL 0 OR "${MACOS_DEPLOYMENT_TARGET}" STREQUAL "")
      message(FATAL_ERROR
        "Cannot determine the macOS deployment target from SDK '${_gambit_sdk}'. "
        "Set -DMACOS_DEPLOYMENT_TARGET=<version> explicitly.")
    endif()
    set(MACOS_DEPLOYMENT_TARGET "${MACOS_DEPLOYMENT_TARGET}" CACHE STRING
        "Minimum macOS version for GAMBIT and all external packages" FORCE)
  endif()

  # CMake consumes this standard cache entry while project() enables languages.
  set(CMAKE_OSX_DEPLOYMENT_TARGET "${MACOS_DEPLOYMENT_TARGET}" CACHE STRING
      "Minimum macOS version" FORCE)
  message(STATUS "macOS deployment target: ${MACOS_DEPLOYMENT_TARGET}")
endfunction()

# Append one complete option group without changing user-provided flags.
function(gambit_append_flags_once variable flags)
  set(_value "${${variable}}")
  if(NOT "${flags}" STREQUAL "")
    string(FIND " ${_value} " " ${flags} " _position)
    if(_position EQUAL -1)
      string(APPEND _value " ${flags}")
    endif()
  endif()
  string(STRIP "${_value}" _value)
  set(${variable} "${_value}" PARENT_SCOPE)
endfunction()

# Reject a second SDK/minimum policy hidden in explicit compiler/linker flags.
# Parse arguments as data; do not execute or rewrite unrelated user options.
function(gambit_validate_macos_flags flags)
  separate_arguments(_options UNIX_COMMAND "${flags}")
  set(_next_is_sdk FALSE)
  foreach(_option IN LISTS _options)
    set(_sdk "")
    if(_next_is_sdk)
      set(_sdk "${_option}")
      set(_next_is_sdk FALSE)
    elseif(_option STREQUAL "-isysroot")
      set(_next_is_sdk TRUE)
    elseif(_option MATCHES "^-isysroot(.+)$")
      set(_sdk "${CMAKE_MATCH_1}")
    elseif(_option MATCHES "^-mmacosx-version-min=(.+)$")
      if(NOT "${CMAKE_MATCH_1}" VERSION_EQUAL "${MACOS_DEPLOYMENT_TARGET}")
        message(FATAL_ERROR "Conflicting macOS minimum in flags: '${_option}'. Use -DMACOS_DEPLOYMENT_TARGET=${MACOS_DEPLOYMENT_TARGET} as the common policy and remove this flag.")
      endif()
    endif()
    if(NOT _sdk STREQUAL "")
      get_filename_component(_sdk_real "${_sdk}" REALPATH)
      get_filename_component(_common_real "${CMAKE_OSX_SYSROOT}" REALPATH)
      if(NOT _sdk_real STREQUAL _common_real)
        message(FATAL_ERROR "Conflicting macOS SDK in flags: '${_sdk}'. Select the common SDK with -DCMAKE_OSX_SYSROOT and remove this flag.")
      endif()
    endif()
  endforeach()
  if(_next_is_sdk)
    message(FATAL_ERROR "Missing SDK path after -isysroot in flags. Use -DCMAKE_OSX_SYSROOT instead.")
  endif()
endfunction()

# Export platform options to shell/Autotools commands; native CMake commands
# obtain C/C++ SDK/minimum options from CMAKE_OSX_* instead.
function(gambit_macos_external_flags input output)
  set(_flags "${input}")
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    gambit_append_flags_once(_flags "-isysroot${_GAMBIT_MACOS_SYSROOT_FLAGS_PATH}")
    gambit_append_flags_once(_flags "${OSX_MIN}")
  endif()
  set(${output} "${_flags}" PARENT_SCOPE)
endfunction()

# CMake-based external projects receive CMAKE_OSX_* arguments. Drop only the
# matching common SDK/minimum options; preserve package-specific compiler flags.
function(gambit_macos_cmake_external_flags input output)
  set(_flags "${input}")
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    foreach(_option "-isysroot${_GAMBIT_MACOS_SYSROOT_FLAGS_PATH}" "${OSX_MIN}")
      string(REPLACE " ${_option} " " " _flags " ${_flags} ")
      string(STRIP "${_flags}" _flags)
    endforeach()
  endif()
  set(${output} "${_flags}" PARENT_SCOPE)
endfunction()

if(DEFINED PROJECT_NAME AND CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(_gambit_flag_configs DEBUG RELEASE RELWITHDEBINFO MINSIZEREL ${CMAKE_BUILD_TYPE} ${CMAKE_CONFIGURATION_TYPES})
  list(REMOVE_DUPLICATES _gambit_flag_configs)
  foreach(_kind C CXX Fortran EXE_LINKER SHARED_LINKER MODULE_LINKER)
    gambit_validate_macos_flags("${CMAKE_${_kind}_FLAGS}")
    foreach(_config IN LISTS _gambit_flag_configs)
      string(TOUPPER "${_config}" _config)
      gambit_validate_macos_flags("${CMAKE_${_kind}_FLAGS_${_config}}")
    endforeach()
  endforeach()
  gambit_append_flags_once(CMAKE_SHARED_LINKER_FLAGS "-Wl,-undefined,dynamic_lookup")
  set(OSX_MIN "-mmacosx-version-min=${MACOS_DEPLOYMENT_TARGET}")
  message(STATUS "Using this macOS SDK ${CMAKE_OSX_SYSROOT}")
  set(_GAMBIT_MACOS_SYSROOT_FLAGS_PATH "${CMAKE_OSX_SYSROOT}")
  if(_GAMBIT_MACOS_SYSROOT_FLAGS_PATH MATCHES "[ \t]")
    set(_GAMBIT_MACOS_SYSROOT_FLAGS_PATH "\"${CMAKE_OSX_SYSROOT}\"")
  endif()
  # Upstream Clang otherwise prefers its bundled libc++ headers while linking
  # Apple's system libc++. Use the selected SDK's matching headers for native
  # targets and BACKEND_CXX_FLAGS (including Autotools/Python extensions).
  # LLVM 22's float.h wrapper with the macOS 27 math.h can lose DBL_MAX when
  # math.h requests only infinity/NaN before a later inclusion of <cfloat>.
  # Honour explicit standard-library selections rather than overriding them.
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND
      EXISTS "${CMAKE_OSX_SYSROOT}/usr/include/c++/v1/__config")
    set(_gambit_stdlib_flags "${CMAKE_CXX_FLAGS} $ENV{CXXFLAGS}")
    foreach(_config IN LISTS _gambit_flag_configs)
      string(TOUPPER "${_config}" _config)
      string(APPEND _gambit_stdlib_flags " ${CMAKE_CXX_FLAGS_${_config}}")
    endforeach()
    if(NOT _gambit_stdlib_flags MATCHES "(^|[ \t])(-stdlib=|-stdlib\\+\\+-isystem|-nostdinc\\+\\+)")
      gambit_append_flags_once(CMAKE_CXX_FLAGS
          "-stdlib++-isystem${_GAMBIT_MACOS_SYSROOT_FLAGS_PATH}/usr/include/c++/v1")
      message(STATUS "Using macOS SDK libc++ headers for upstream Clang")
    endif()
    unset(_gambit_stdlib_flags)
  endif()
  gambit_append_flags_once(CMAKE_SHARED_LINKER_FLAGS "-L${_GAMBIT_MACOS_SYSROOT_FLAGS_PATH}/usr/lib")
  # CMake's GNU help-text detection can miss these options for gfortran.
  # Supply the common policy only when CMake is not supplying it itself.
  if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
    if(NOT CMAKE_Fortran_SYSROOT_FLAG)
      gambit_append_flags_once(CMAKE_Fortran_FLAGS "-isysroot${_GAMBIT_MACOS_SYSROOT_FLAGS_PATH}")
    endif()
    if(NOT CMAKE_Fortran_OSX_DEPLOYMENT_TARGET_FLAG)
      gambit_append_flags_once(CMAKE_Fortran_FLAGS "${OSX_MIN}")
    endif()
  endif()
  set(GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG
      "-DCMAKE_OSX_DEPLOYMENT_TARGET=${MACOS_DEPLOYMENT_TARGET}")
  set(GAMBIT_MACOS_CMAKE_SYSROOT_ARG "-DCMAKE_OSX_SYSROOT=${CMAKE_OSX_SYSROOT}")
endif()

# ld64 chained-fixup workaround; AppleClang and upstream LLVM share this linker.
# Single-token -Wl, form so rivet-build cannot split it.
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(NO_FIXUP_CHAINS "-Wl,-no_fixup_chains")
  endif()
endif()
