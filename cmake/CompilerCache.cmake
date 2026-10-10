# Optional C/C++ compiler caching for native GAMBIT targets.
# Automatic launchers are normal variables, so reconfiguring with OFF does not
# leave generated launcher values in the shared CMake cache.

include_guard(GLOBAL)

function(gambit_configure_compiler_cache)
  set(_default OFF)
  if(GAMBIT_PRESET_TOOLCHAIN OR GAMBIT_BUILD_PRESET OR CBS_BUILD_PRESET)
    set(_default AUTO)
  endif()
  if(DEFINED GAMBIT_COMPILER_CACHE)
    set(_default "${GAMBIT_COMPILER_CACHE}")
  endif()
  set(GAMBIT_COMPILER_CACHE "${_default}" CACHE STRING
      "Automatic C/C++ compiler cache: AUTO, CCACHE (required), or OFF")
  set_property(CACHE GAMBIT_COMPILER_CACHE PROPERTY STRINGS AUTO CCACHE OFF)
  string(TOUPPER "${GAMBIT_COMPILER_CACHE}" _mode)
  if(NOT _mode MATCHES "^(AUTO|CCACHE|OFF)$")
    message(FATAL_ERROR
      "Invalid GAMBIT_COMPILER_CACHE='${GAMBIT_COMPILER_CACHE}'. Use AUTO, CCACHE, or OFF.")
  endif()

  set(_languages "")
  foreach(_language C CXX)
    # A defined empty launcher is also an explicit choice. CMake imports its
    # launcher environment variables during project(), before this function.
    if(NOT DEFINED CMAKE_${_language}_COMPILER_LAUNCHER)
      list(APPEND _languages "${_language}")
    endif()
  endforeach()

  set(_automatic_languages "")
  if(_mode STREQUAL "OFF")
    set(_status "OFF (automatic launchers disabled)")
  elseif(NOT _languages)
    set(_status "${_mode} (explicit launchers retained)")
  elseif(NOT CMAKE_GENERATOR MATCHES "Makefiles|Ninja")
    set(_status "${_mode}: unavailable for generator ${CMAKE_GENERATOR}")
    if(_mode STREQUAL "CCACHE")
      message(FATAL_ERROR
        "Automatic ccache launchers require a Makefiles or Ninja generator. "
        "Use -DGAMBIT_COMPILER_CACHE=OFF with ${CMAKE_GENERATOR}.")
    endif()
  else()
    # Search again on each configure rather than retaining a stale discovered
    # path. Users who need a specific wrapper can set CMAKE_<LANG>_COMPILER_LAUNCHER.
    unset(_gambit_ccache_program)
    unset(_gambit_ccache_program CACHE)
    find_program(_gambit_ccache_program NAMES ccache
                 PATHS ENV PATH NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
    set(_gambit_ccache_program "${_gambit_ccache_program}")
    unset(_gambit_ccache_program CACHE)
    set(_version "")
    if(_gambit_ccache_program)
      execute_process(COMMAND "${_gambit_ccache_program}" --version
        RESULT_VARIABLE _result OUTPUT_VARIABLE _output ERROR_VARIABLE _error
        TIMEOUT 5)
      if("${_result}" STREQUAL "0" AND _output MATCHES "ccache version ([^ \r\n]+)")
        set(_version "${CMAKE_MATCH_1}")
      endif()
    endif()
    if(_version)
      foreach(_language IN LISTS _languages)
        set(CMAKE_${_language}_COMPILER_LAUNCHER "${_gambit_ccache_program}" PARENT_SCOPE)
      endforeach()
      set(_automatic_languages "${_languages}")
      set(_status "${_mode}: ccache ${_version}")
    else()
      set(_status "${_mode}: ccache unavailable (not found or --version failed)")
      if(_mode STREQUAL "CCACHE")
        message(FATAL_ERROR
          "GAMBIT_COMPILER_CACHE=CCACHE requires a working ccache on PATH. "
          "Install ccache or use -DGAMBIT_COMPILER_CACHE=AUTO/OFF.")
      endif()
    endif()
  endif()
  set(GAMBIT_COMPILER_CACHE_STATUS "${_status}" PARENT_SCOPE)
  set(GAMBIT_CCACHE_AUTOMATIC_LANGUAGES "${_automatic_languages}" PARENT_SCOPE)
  message(STATUS "Compiler cache: ${_status}")
endfunction()

function(gambit_print_compiler_cache_summary)
  cbs_summary_line("Compiler cache" "${GAMBIT_COMPILER_CACHE_STATUS}")
  foreach(_language C CXX)
    if(_language STREQUAL "CXX")
      set(_label "C++ launcher")
    else()
      set(_label "C launcher")
    endif()
    if(DEFINED CMAKE_${_language}_COMPILER_LAUNCHER)
      if("${CMAKE_${_language}_COMPILER_LAUNCHER}" STREQUAL "")
        set(_description "disabled (explicit empty)")
      elseif(_language IN_LIST GAMBIT_CCACHE_AUTOMATIC_LANGUAGES)
        set(_description "${CMAKE_${_language}_COMPILER_LAUNCHER} (automatic)")
      else()
        set(_description "${CMAKE_${_language}_COMPILER_LAUNCHER} (explicit)")
      endif()
    else()
      set(_description "none")
    endif()
    cbs_summary_line("${_label}" "${_description}")
  endforeach()
endfunction()
