# Read-only prerequisite policy for public CBS presets. These requirements
# mirror CBSValidation.cmake; ROOT and Rivet/Contur remain optional.

include_guard(GLOBAL)
include("${CMAKE_CURRENT_LIST_DIR}/CBSRootDiscovery.cmake")

macro(preset_probe_prepare_cbs)
  set(BOOTSTRAP_PYTHON_DEVELOPMENT_FOUND FALSE)
  set(BOOTSTRAP_PYTHON_DEVELOPMENT_REASON "Python interpreter is unavailable")
  if(BOOTSTRAP_PYTHON_FOUND)
    set(Python3_EXECUTABLE "${BOOTSTRAP_PYTHON_EXECUTABLE}")
    cbs_discover_python(BOOTSTRAP_PYTHON_DEVELOPMENT_FOUND _probe_python_executable
      _probe_python_version _probe_python_root _probe_python_include _probe_python_library
      BOOTSTRAP_PYTHON_DEVELOPMENT_REASON)
  endif()
  cbs_find_root_installation(BOOTSTRAP_ROOT_FOUND BOOTSTRAP_ROOT_PREFIX
                            BOOTSTRAP_ROOT_VERSION BOOTSTRAP_ROOT_REASON)
  preset_probe_find_sqlite3(BOOTSTRAP_SQLITE_LIBRARIES_FOUND BOOTSTRAP_SQLITE_EXECUTABLE
                           BOOTSTRAP_SQLITE_VERSION)
  preset_probe_rivet_contur_reasons(BOOTSTRAP_RIVET_CONTUR_REASONS)
endmacro()

function(preset_probe_cbs name strategy display_name output_available)
  preset_probe_core_reasons(_probe_reasons)
  if(BOOTSTRAP_PYTHON_FOUND AND NOT BOOTSTRAP_PYTHON_DEVELOPMENT_FOUND)
    list(APPEND _probe_reasons "${BOOTSTRAP_PYTHON_DEVELOPMENT_REASON}")
  endif()
  if(NOT BOOTSTRAP_HDF5_FOUND)
    list(APPEND _probe_reasons "HDF5 C development headers/libraries were not found")
  endif()
  preset_probe_toolchain("${strategy}" _probe_c _probe_cxx _probe_fortran
                        _probe_toolchain_reason _probe_root)
  if(_probe_toolchain_reason)
    list(APPEND _probe_reasons ${_probe_toolchain_reason})
  endif()
  preset_probe_record_result("${name}" "${_probe_reasons}" "${_probe_c}" "${_probe_cxx}"
                             "${_probe_fortran}" "${_probe_root}" _probe_available)
  set(${output_available} "${_probe_available}" PARENT_SCOPE)
endfunction()

function(preset_probe_rivet_contur_reasons output)
  set(_cbs_backend_reasons "")
  if(NOT BOOTSTRAP_PYTHON_FOUND)
    list(APPEND _cbs_backend_reasons "Python is unavailable")
  else()
    cbs_python_missing_modules("${BOOTSTRAP_PYTHON_EXECUTABLE}" _cbs_backend_missing cython configobj pandas matplotlib)
    if(_cbs_backend_missing)
      string(REPLACE ";" ", " _cbs_backend_missing_text "${_cbs_backend_missing}")
      list(APPEND _cbs_backend_reasons "missing Python modules: ${_cbs_backend_missing_text}")
    endif()
  endif()
  if(NOT BOOTSTRAP_SQLITE_LIBRARIES_FOUND)
    list(APPEND _cbs_backend_reasons "SQLite3 development libraries were not found")
  endif()
  if(NOT BOOTSTRAP_HDF5_FOUND)
    list(APPEND _cbs_backend_reasons "HDF5 C development headers/libraries were not found")
  endif()
  if(NOT BOOTSTRAP_SQLITE_EXECUTABLE)
    list(APPEND _cbs_backend_reasons "sqlite3 command-line client was not found")
  endif()
  set(${output} "${_cbs_backend_reasons}" PARENT_SCOPE)
endfunction()

function(preset_probe_report_cbs)
  bootstrap_report_section("CBS environment")
  bootstrap_report_dependency("Python dev" "${BOOTSTRAP_PYTHON_DEVELOPMENT_FOUND}" "headers + shared library (required)")
  bootstrap_report_section("CBS optional features")
  if(BOOTSTRAP_ROOT_FOUND)
    bootstrap_report_dependency(ROOT TRUE "${BOOTSTRAP_ROOT_VERSION}")
    bootstrap_report_path(ROOT "${BOOTSTRAP_ROOT_PREFIX}")
  else()
    bootstrap_report_dependency(ROOT FALSE "${BOOTSTRAP_ROOT_REASON}")
  endif()
  bootstrap_report_dependency("SQLite3 libs" "${BOOTSTRAP_SQLITE_LIBRARIES_FOUND}" "development package")
  bootstrap_report_dependency("sqlite3 CLI" "${BOOTSTRAP_SQLITE_EXECUTABLE}" "${BOOTSTRAP_SQLITE_VERSION}")
  bootstrap_report_path(sqlite3 "${BOOTSTRAP_SQLITE_EXECUTABLE}")
  if(BOOTSTRAP_RIVET_CONTUR_REASONS)
    bootstrap_report_dependency("Rivet / Contur" FALSE "prerequisites incomplete")
    foreach(_cbs_reason IN LISTS BOOTSTRAP_RIVET_CONTUR_REASONS)
      bootstrap_report_line("      ${_cbs_reason}")
    endforeach()
  else()
    bootstrap_report_dependency("Rivet / Contur" TRUE "prerequisites · Rivet 4.1.0 / Contur 3.0.0")
  endif()
endfunction()

function(preset_probe_find_sqlite3 output_libraries_found output_executable output_version)
  # Keep this script read-only. `cmake --find-package` creates a CMakeFiles
  # directory in script mode, whereas pkg-config and Homebrew's prefix query do
  # not modify the source tree.
  set(_cbs_sqlite_libraries_found FALSE)
  cbs_resolve_command(_cbs_pkg_config "pkg-config")
  if(_cbs_pkg_config)
    execute_process(
      COMMAND "${_cbs_pkg_config}" --exists sqlite3
      RESULT_VARIABLE _cbs_sqlite_result
      ERROR_QUIET
      TIMEOUT 10)
  else()
    set(_cbs_sqlite_result 1)
  endif()
  if(_cbs_sqlite_result EQUAL 0)
    set(_cbs_sqlite_libraries_found TRUE)
  elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    cbs_resolve_command(_cbs_brew "brew")
    if(_cbs_brew)
      execute_process(
        COMMAND "${_cbs_brew}" --prefix sqlite
        RESULT_VARIABLE _cbs_brew_sqlite_result
        OUTPUT_VARIABLE _cbs_brew_sqlite_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        TIMEOUT 10)
      if(_cbs_brew_sqlite_result EQUAL 0 AND
         EXISTS "${_cbs_brew_sqlite_prefix}/include/sqlite3.h" AND
         EXISTS "${_cbs_brew_sqlite_prefix}/lib/libsqlite3.dylib")
        set(_cbs_sqlite_libraries_found TRUE)
      endif()
    endif()
  endif()

  cbs_resolve_command(_cbs_sqlite_executable "sqlite3")
  set(_cbs_sqlite_version "")
  if(_cbs_sqlite_executable)
    execute_process(
      COMMAND "${_cbs_sqlite_executable}" --version
      RESULT_VARIABLE _cbs_sqlite_version_result
      OUTPUT_VARIABLE _cbs_sqlite_version_text
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
      TIMEOUT 10)
    if(_cbs_sqlite_version_result EQUAL 0)
      string(REGEX MATCH "^[^ \\t]+" _cbs_sqlite_version
             "${_cbs_sqlite_version_text}")
    else()
      set(_cbs_sqlite_executable "")
      set(_cbs_sqlite_version "")
    endif()
  endif()

  set(${output_libraries_found} "${_cbs_sqlite_libraries_found}" PARENT_SCOPE)
  set(${output_executable} "${_cbs_sqlite_executable}" PARENT_SCOPE)
  set(${output_version} "${_cbs_sqlite_version}" PARENT_SCOPE)
endfunction()
