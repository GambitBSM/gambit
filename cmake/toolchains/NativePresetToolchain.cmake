# Shared native preset setup. No profile-specific flags or output directories.

include_guard(GLOBAL)
include("${CMAKE_CURRENT_LIST_DIR}/../presets/NativeCompilerDiscovery.cmake")

function(native_configure_preset_toolchain strategy)
  # CMake can load CMakeSystem.cmake's saved toolchain on a reconfigure even
  # when a new preset supplies CMAKE_TOOLCHAIN_FILE. Compare the incoming
  # preset contract with the file actually loaded before trusting that cache.
  if(DEFINED GAMBIT_PRESET_TOOLCHAIN AND NOT "${GAMBIT_PRESET_TOOLCHAIN}" STREQUAL "${strategy}")
    message(FATAL_ERROR
      "The selected preset requests ${GAMBIT_PRESET_TOOLCHAIN}, but this build tree loaded the cached ${strategy} toolchain.\n"
      "All presets share build/. Rerun 'cmake --preset <selected-preset> --fresh'.")
  endif()
  list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES GAMBIT_PRESET_TOOLCHAIN)
  list(REMOVE_DUPLICATES CMAKE_TRY_COMPILE_PLATFORM_VARIABLES)
  set(CMAKE_TRY_COMPILE_PLATFORM_VARIABLES "${CMAKE_TRY_COMPILE_PLATFORM_VARIABLES}" PARENT_SCOPE)
  native_find_toolchain("${strategy}" _native_found _native_c _native_cxx
                        _native_fortran _native_root _native_version _native_reason)
  if(NOT _native_found)
    string(REPLACE ";" "\n" _native_reason_text "${_native_reason}")
    message(FATAL_ERROR "The ${strategy} preset toolchain is unavailable: ${_native_reason_text}")
  endif()

  foreach(_native_language C CXX Fortran)
    if(_native_language STREQUAL "C")
      set(_native_selected "${_native_c}")
    elseif(_native_language STREQUAL "CXX")
      set(_native_selected "${_native_cxx}")
    else()
      set(_native_selected "${_native_fortran}")
    endif()
    set(_native_variable CMAKE_${_native_language}_COMPILER)
    if(DEFINED ${_native_variable} AND NOT "${${_native_variable}}" STREQUAL "")
      cbs_resolve_command(_native_existing "${${_native_variable}}")
      get_filename_component(_native_existing_real "${_native_existing}" REALPATH)
      get_filename_component(_native_selected_real "${_native_selected}" REALPATH)
      if(NOT _native_existing_real STREQUAL _native_selected_real)
        message(FATAL_ERROR
          "The ${strategy} toolchain selected ${_native_selected}, but ${_native_variable} is already ${${_native_variable}}.\n"
          "All presets share build/. Rerun 'cmake --preset <selected-preset> --fresh' when switching compilers.")
      endif()
    endif()
    set(${_native_variable} "${_native_selected}" CACHE FILEPATH
        "Compiler selected by the ${strategy} native preset" FORCE)
    set(${_native_variable} "${_native_selected}" PARENT_SCOPE)
  endforeach()

  set(GAMBIT_RESOLVED_TOOLCHAIN "${strategy}" CACHE STRING "Resolved native preset compiler strategy" FORCE)
  if(strategy STREQUAL "llvm")
    set(GAMBIT_RESOLVED_LLVM_ROOT "${_native_root}" CACHE PATH "Resolved upstream LLVM installation" FORCE)
    set(GAMBIT_RESOLVED_LLVM_VERSION "${_native_version}" CACHE STRING "Resolved upstream LLVM version" FORCE)
  endif()
  # CMake re-reads toolchains during compiler checks. Announce once per process.
  get_property(_native_announced GLOBAL PROPERTY GAMBIT_NATIVE_TOOLCHAIN_ANNOUNCED)
  if(NOT _native_announced)
    message(STATUS "Native preset toolchain: ${strategy} ${_native_version}")
    set_property(GLOBAL PROPERTY GAMBIT_NATIVE_TOOLCHAIN_ANNOUNCED TRUE)
  endif()
endfunction()
