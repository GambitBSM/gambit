# \author Pengxuan Zhu
#         (pengxuan.zhu@adelaide.edu.au)
# \date 2026 Aug
#
# Locate a native ROOT installation for public CBS presets before GAMBIT's
# optional.cmake consumes ROOTSYS. ROOT remains optional. Only installations
# built with one of GAMBIT's supported C++ standards (17, 20, 23) are accepted;
# optional.cmake resolves the exact standard shared by ROOT and GAMBIT.

include_guard(GLOBAL)
include("${CMAKE_CURRENT_LIST_DIR}/../CXXStandard.cmake")

function(cbs_root_cxx_standard root_config output_standard)
  set(_cbs_std "")
  execute_process(
    COMMAND "${root_config}" --cxxstd
    RESULT_VARIABLE _cbs_cxxstd_result
    OUTPUT_VARIABLE _cbs_cxxstd
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
    TIMEOUT 10)
  if(_cbs_cxxstd_result EQUAL 0)
    gambit_normalise_cxx_standard("${_cbs_cxxstd}" _cbs_std)
  endif()
  if(NOT "${_cbs_std}" MATCHES "^[0-9]+$")
    execute_process(
      COMMAND "${root_config}" --cflags
      RESULT_VARIABLE _cbs_cflags_result
      OUTPUT_VARIABLE _cbs_cflags
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE
      TIMEOUT 10)
    if(_cbs_cflags_result EQUAL 0)
      gambit_cxx_standard_from_flags("${_cbs_cflags}" _cbs_std)
    endif()
  endif()
  set(${output_standard} "${_cbs_std}" PARENT_SCOPE)
endfunction()

function(cbs_find_root_installation output_found output_prefix output_version output_reason)
  set(_cbs_root_found FALSE)
  set(_cbs_root_prefix "")
  set(_cbs_root_version "")
  set(_cbs_root_reason "")
  set(_cbs_root_config "")
  if(DEFINED ENV{ROOTSYS} AND EXISTS "$ENV{ROOTSYS}/bin/root-config")
    set(_cbs_root_config "$ENV{ROOTSYS}/bin/root-config")
  else()
    unset(_cbs_root_config)
    unset(_cbs_root_config CACHE)
    find_program(_cbs_root_config NAMES root-config
      HINTS /opt/homebrew/opt/root/bin /usr/local/opt/root/bin)
  endif()

  if(NOT _cbs_root_config OR _cbs_root_config MATCHES "-NOTFOUND$")
    set(_cbs_root_reason "root-config was not found")
  else()
    execute_process(
      COMMAND "${_cbs_root_config}" --prefix
      RESULT_VARIABLE _cbs_root_prefix_result
      OUTPUT_VARIABLE _cbs_root_prefix
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE
      TIMEOUT 10)
    execute_process(
      COMMAND "${_cbs_root_config}" --version
      RESULT_VARIABLE _cbs_root_version_result
      OUTPUT_VARIABLE _cbs_root_version
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE
      TIMEOUT 10)

    if(NOT _cbs_root_prefix_result EQUAL 0 OR NOT IS_DIRECTORY "${_cbs_root_prefix}")
      set(_cbs_root_prefix "")
      set(_cbs_root_version "")
      set(_cbs_root_reason "${_cbs_root_config} did not report a usable ROOT prefix")
    else()
      cbs_root_cxx_standard("${_cbs_root_config}" _cbs_root_std)
      if("${_cbs_root_std}" STREQUAL "")
        set(_cbs_root_reason
            "${_cbs_root_config} did not report its C++ standard; CBS requires ROOT built with C++17, C++20 or C++23")
      elseif(NOT _cbs_root_std MATCHES "^(17|20|23)$")
        set(_cbs_root_reason
            "${_cbs_root_prefix} is C++${_cbs_root_std}; CBS requires ROOT built with C++17, C++20 or C++23 (set CBS_AUTO_DETECT_ROOT=OFF to silence this)")
      else()
        set(_cbs_root_found TRUE)
        if(NOT _cbs_root_version_result EQUAL 0)
          set(_cbs_root_version "")
        endif()
      endif()
    endif()
  endif()

  set(${output_found} "${_cbs_root_found}" PARENT_SCOPE)
  set(${output_prefix} "${_cbs_root_prefix}" PARENT_SCOPE)
  set(${output_version} "${_cbs_root_version}" PARENT_SCOPE)
  set(${output_reason} "${_cbs_root_reason}" PARENT_SCOPE)
endfunction()

function(cbs_configure_root_for_cbs_preset)
  if(DEFINED WITH_ROOT AND NOT WITH_ROOT)
    set(CBS_ROOT_SKIP_REASON "disabled by WITH_ROOT=OFF" PARENT_SCOPE)
    return()
  endif()
  if(NOT CBS_AUTO_DETECT_ROOT)
    return()
  endif()

  cbs_find_root_installation(_cbs_root_found _cbs_root_prefix _cbs_root_version _cbs_root_reason)
  if(NOT _cbs_root_found)
    message(STATUS "CBS ROOT: ${_cbs_root_reason}; ROOT-dependent features remain disabled")
    set(CBS_ROOT_SKIP_REASON "${_cbs_root_reason}" PARENT_SCOPE)
    return()
  endif()

  set(ENV{ROOTSYS} "${_cbs_root_prefix}")
  set(WITH_ROOT ON PARENT_SCOPE)
  set(CBS_RESOLVED_ROOT "${_cbs_root_prefix}" PARENT_SCOPE)
  set(CBS_ROOT_SKIP_REASON "" PARENT_SCOPE)
  if(NOT "${_cbs_root_version}" STREQUAL "")
    set(CBS_RESOLVED_ROOT_VERSION "${_cbs_root_version}" PARENT_SCOPE)
    message(STATUS "CBS ROOT: ${_cbs_root_version} from ${_cbs_root_prefix}")
  else()
    message(STATUS "CBS ROOT: detected at ${_cbs_root_prefix}")
  endif()
endfunction()
