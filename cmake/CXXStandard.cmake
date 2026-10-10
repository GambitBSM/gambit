# One language-standard policy for GAMBIT and its native presets.
# Helpers are also used by read-only ROOT discovery; including this file does
# not select a compiler, configure a project, or run any compiler probes.
include_guard(GLOBAL)

function(gambit_normalise_cxx_standard value output)
  string(STRIP "${value}" standard)
  if(standard STREQUAL "0x")
    set(standard 11)
  elseif(standard STREQUAL "1y")
    set(standard 14)
  elseif(standard STREQUAL "1z")
    set(standard 17)
  elseif(standard STREQUAL "2a")
    set(standard 20)
  elseif(standard STREQUAL "2b")
    set(standard 23)
  endif()
  set(${output} "${standard}" PARENT_SCOPE)
endfunction()

function(gambit_cxx_standard_from_flags flags output)
  set(standard "")
  string(REGEX MATCHALL "(^|[ \t])-std=(c|gnu)\\+\\+[^ \t]+" options "${flags}")
  if(options)
    list(GET options -1 option)
    string(REGEX REPLACE "^[ \t]*-std=(c|gnu)\\+\\+" "" standard "${option}")
    gambit_normalise_cxx_standard("${standard}" standard)
  endif()
  set(${output} "${standard}" PARENT_SCOPE)
endfunction()

function(gambit_strip_cxx_standard_flags flags output)
  string(REGEX REPLACE "(^|[ \t])-std=(c|gnu)\\+\\+[^ \t]+" "\\1" flags "${flags}")
  string(STRIP "${flags}" flags)
  set(${output} "${flags}" PARENT_SCOPE)
endfunction()

# Autotools/Make projects do not inherit CMake target properties.
function(gambit_set_cxx_standard_flag flags standard output)
  gambit_strip_cxx_standard_flags("${flags}" flags)
  string(STRIP "${flags} -std=c++${standard}" flags)
  set(${output} "${flags}" PARENT_SCOPE)
endfunction()

function(gambit_require_cxx_standard standard)
  if(NOT "${standard}" MATCHES "^(17|20|23)$")
    message(FATAL_ERROR "GAMBIT supports C++17, C++20 and C++23; requested '${standard}'. "
                        "Use -DCMAKE_CXX_STANDARD=17, 20 or 23.")
  endif()
  if(standard EQUAL 23 AND CMAKE_VERSION VERSION_LESS 3.20)
    message(FATAL_ERROR "C++23 requires CMake 3.20 or newer. Upgrade CMake or select C++17/20.")
  endif()
  if(NOT "cxx_std_${standard}" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(FATAL_ERROR "CMake ${CMAKE_VERSION} cannot enable C++${standard} with "
                        "${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}. "
                        "Select a supported standard or upgrade the compiler/CMake.")
  endif()
endfunction()

macro(gambit_sync_backend_cxx_standard)
  foreach(_gambit_flags BACKEND_CXX_FLAGS BACKEND_CXX_FLAGS_NO_BUILD_OPTIMISATIONS
                        BACKEND_CXX_FLAGS_PLUS_MPI)
    if(DEFINED ${_gambit_flags})
      gambit_set_cxx_standard_flag("${${_gambit_flags}}" "${GAMBIT_CXX_STANDARD}" ${_gambit_flags})
    endif()
  endforeach()
endmacro()

macro(gambit_apply_cxx_standard standard reason)
  gambit_require_cxx_standard("${standard}")
  set(GAMBIT_CXX_STANDARD "${standard}")
  set(GAMBIT_CXX_STANDARD_REASON "${reason}")
  # Keep AUTO a per-configure decision. Only a user-supplied cache entry is
  # persistent, so the next configure can still follow a changed ROOT build.
  set(CMAKE_CXX_STANDARD "${standard}")
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
  foreach(_gambit_minimum 14 17 20 23)
    if(GAMBIT_CXX_STANDARD GREATER_EQUAL _gambit_minimum)
      set(GAMBIT_SUPPORTS_CXX${_gambit_minimum} TRUE)
    else()
      set(GAMBIT_SUPPORTS_CXX${_gambit_minimum} FALSE)
    endif()
  endforeach()
  gambit_sync_backend_cxx_standard()
endmacro()

macro(gambit_initialise_cxx_standard)
  if(NOT PERMIT_CXX17_PLUS_CHECK)
    message(FATAL_ERROR "The selected compiler/pybind11 combination cannot use C++17 or newer. "
                        "Upgrade the compiler or disable pybind11 with -DWITH_PYBIND11=OFF.")
  endif()

  set(GAMBIT_CXX_STANDARD_REQUESTED AUTO)
  if(DEFINED CMAKE_CXX_STANDARD AND NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    set(GAMBIT_CXX_STANDARD_REQUESTED "${CMAKE_CXX_STANDARD}")
  endif()

  # Accept legacy -std flags as an explicit request, but do not let global or
  # configuration-specific flags silently disagree with the target standard.
  set(_gambit_configurations DEBUG RELEASE RELWITHDEBINFO MINSIZEREL
                            ${CMAKE_BUILD_TYPE} ${CMAKE_CONFIGURATION_TYPES})
  set(_gambit_flag_variables CMAKE_CXX_FLAGS)
  foreach(_gambit_configuration IN LISTS _gambit_configurations)
    string(TOUPPER "${_gambit_configuration}" _gambit_configuration)
    list(APPEND _gambit_flag_variables "CMAKE_CXX_FLAGS_${_gambit_configuration}")
  endforeach()
  list(REMOVE_DUPLICATES _gambit_flag_variables)
  foreach(_gambit_flags IN LISTS _gambit_flag_variables)
    gambit_cxx_standard_from_flags("${${_gambit_flags}}" _gambit_flag_standard)
    if(NOT "${_gambit_flag_standard}" STREQUAL "")
      if(GAMBIT_CXX_STANDARD_REQUESTED STREQUAL "AUTO")
        set(GAMBIT_CXX_STANDARD_REQUESTED "${_gambit_flag_standard}")
      elseif(NOT GAMBIT_CXX_STANDARD_REQUESTED STREQUAL _gambit_flag_standard)
        message(FATAL_ERROR "${_gambit_flags} requests C++${_gambit_flag_standard}, but "
                            "C++${GAMBIT_CXX_STANDARD_REQUESTED} is already selected. "
                            "Remove conflicting -std flags and use CMAKE_CXX_STANDARD.")
      endif()
    endif()
    if(DEFINED ${_gambit_flags})
      gambit_strip_cxx_standard_flags("${${_gambit_flags}}" ${_gambit_flags})
    endif()
  endforeach()

  # CMake already determined the compiler's available language modes when
  # project() enabled CXX. Do not repeat flag-only compiler probes here.
  foreach(_gambit_standard 17 20 23)
    set(COMPILER_SUPPORTS_CXX${_gambit_standard} FALSE)
    if("cxx_std_${_gambit_standard}" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
      set(COMPILER_SUPPORTS_CXX${_gambit_standard} TRUE)
    endif()
  endforeach()
  if(GAMBIT_CXX_STANDARD_REQUESTED STREQUAL "AUTO")
    set(_gambit_selected "")
    foreach(_gambit_standard 23 20 17)
      if(COMPILER_SUPPORTS_CXX${_gambit_standard})
        set(_gambit_selected "${_gambit_standard}")
        break()
      endif()
    endforeach()
    if(NOT _gambit_selected)
      message(FATAL_ERROR "GAMBIT requires a compiler and CMake supporting at least C++17.")
    endif()
    gambit_apply_cxx_standard("${_gambit_selected}" "automatic compiler selection")
  else()
    gambit_apply_cxx_standard("${GAMBIT_CXX_STANDARD_REQUESTED}" "explicit request")
  endif()
endmacro()

macro(gambit_match_root_cxx_standard root_standard)
  gambit_require_cxx_standard("${root_standard}")
  if(NOT GAMBIT_CXX_STANDARD_REQUESTED STREQUAL "AUTO"
     AND NOT GAMBIT_CXX_STANDARD_REQUESTED STREQUAL "${root_standard}")
    message(FATAL_ERROR "Requested C++${GAMBIT_CXX_STANDARD_REQUESTED}, but ROOT was built with "
                        "C++${root_standard}. Use -DCMAKE_CXX_STANDARD=${root_standard}, "
                        "choose a matching ROOT installation, or set -DWITH_ROOT=OFF.")
  endif()
  gambit_apply_cxx_standard("${root_standard}" "ROOT compatibility")
endmacro()
