# \author Pengxuan Zhu
#         (pengxuan.zhu@adelaide.edu.au)
# \date 2026 Aug
#
# Resolve one CPython interpreter for public CBS presets.  Configure-time
# pinning only sets Python3_EXECUTABLE; FindPython3 locates headers and
# libpython so Debian multiarch and framework layouts keep working.

include_guard(GLOBAL)

set(_CBS_PYTHON_PROBE "${CMAKE_CURRENT_LIST_DIR}/cbs_python_probe.py")

function(cbs_discover_python output_found output_executable output_version output_root output_include output_library output_reason)
  if(DEFINED Python3_EXECUTABLE AND NOT "${Python3_EXECUTABLE}" STREQUAL "")
    set(_cbs_python_command "${Python3_EXECUTABLE}")
  else()
    unset(_cbs_python_command CACHE)
    unset(_cbs_python_command)
    find_program(_cbs_python_command NAMES python3)
  endif()

  if(NOT _cbs_python_command OR _cbs_python_command MATCHES "-NOTFOUND$")
    set(${output_found} FALSE PARENT_SCOPE)
    set(${output_executable} "" PARENT_SCOPE)
    set(${output_version} "" PARENT_SCOPE)
    set(${output_root} "" PARENT_SCOPE)
    set(${output_include} "" PARENT_SCOPE)
    set(${output_library} "" PARENT_SCOPE)
    set(${output_reason} "No python3 executable was found on PATH" PARENT_SCOPE)
    return()
  endif()

  if(NOT EXISTS "${_cbs_python_command}")
    set(${output_found} FALSE PARENT_SCOPE)
    set(${output_executable} "" PARENT_SCOPE)
    set(${output_version} "" PARENT_SCOPE)
    set(${output_root} "" PARENT_SCOPE)
    set(${output_include} "" PARENT_SCOPE)
    set(${output_library} "" PARENT_SCOPE)
    set(${output_reason} "Python executable was not found: ${_cbs_python_command}" PARENT_SCOPE)
    return()
  endif()

  execute_process(
    COMMAND "${_cbs_python_command}" "${_CBS_PYTHON_PROBE}"
    RESULT_VARIABLE _cbs_python_result
    OUTPUT_VARIABLE _cbs_python_output
    ERROR_VARIABLE _cbs_python_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    TIMEOUT 10)

  if(NOT _cbs_python_result EQUAL 0)
    set(${output_found} FALSE PARENT_SCOPE)
    set(${output_executable} "" PARENT_SCOPE)
    set(${output_version} "" PARENT_SCOPE)
    set(${output_root} "" PARENT_SCOPE)
    set(${output_include} "" PARENT_SCOPE)
    set(${output_library} "" PARENT_SCOPE)
    set(${output_reason} "Could not inspect ${_cbs_python_command}: ${_cbs_python_error}" PARENT_SCOPE)
    return()
  endif()

  string(REPLACE "\n" ";" _cbs_python_fields "${_cbs_python_output}")
  list(LENGTH _cbs_python_fields _cbs_python_field_count)
  if(_cbs_python_field_count LESS 5)
    set(${output_found} FALSE PARENT_SCOPE)
    set(${output_executable} "" PARENT_SCOPE)
    set(${output_version} "" PARENT_SCOPE)
    set(${output_root} "" PARENT_SCOPE)
    set(${output_include} "" PARENT_SCOPE)
    set(${output_library} "" PARENT_SCOPE)
    set(${output_reason} "Python inspection returned incomplete development information" PARENT_SCOPE)
    return()
  endif()

  list(GET _cbs_python_fields 0 _cbs_python_executable)
  list(GET _cbs_python_fields 1 _cbs_python_version)
  list(GET _cbs_python_fields 2 _cbs_python_root)
  list(GET _cbs_python_fields 3 _cbs_python_include)
  list(GET _cbs_python_fields 4 _cbs_python_library)

  if(NOT EXISTS "${_cbs_python_executable}")
    set(_cbs_python_reason "Python reported a non-existent executable: ${_cbs_python_executable}")
  elseif(NOT EXISTS "${_cbs_python_include}/Python.h")
    set(_cbs_python_reason "Python ${_cbs_python_version} has no development headers at ${_cbs_python_include} (install python3-dev / python3-devel)")
  elseif(NOT EXISTS "${_cbs_python_library}" OR "${_cbs_python_library}" MATCHES "\\.a$")
    set(_cbs_python_reason "Python ${_cbs_python_version} has no shared libpython (install python3-dev / python3-devel)")
  else()
    set(_cbs_python_reason "")
  endif()

  if(_cbs_python_reason)
    set(${output_found} FALSE PARENT_SCOPE)
  else()
    set(${output_found} TRUE PARENT_SCOPE)
  endif()
  set(${output_executable} "${_cbs_python_executable}" PARENT_SCOPE)
  set(${output_version} "${_cbs_python_version}" PARENT_SCOPE)
  set(${output_root} "${_cbs_python_root}" PARENT_SCOPE)
  set(${output_include} "${_cbs_python_include}" PARENT_SCOPE)
  set(${output_library} "${_cbs_python_library}" PARENT_SCOPE)
  set(${output_reason} "${_cbs_python_reason}" PARENT_SCOPE)
endfunction()

function(cbs_python_has_module executable module output_found)
  execute_process(
    COMMAND "${executable}" -c "import ${module}"
    RESULT_VARIABLE _cbs_module_result
    ERROR_QUIET
    TIMEOUT 10)
  if(_cbs_module_result EQUAL 0)
    set(${output_found} TRUE PARENT_SCOPE)
  else()
    set(${output_found} FALSE PARENT_SCOPE)
  endif()
endfunction()

function(cbs_python_missing_modules executable output_missing)
  set(_cbs_missing_modules "")
  foreach(_cbs_module ${ARGN})
    cbs_python_has_module("${executable}" "${_cbs_module}" _cbs_module_found)
    if(NOT _cbs_module_found)
      list(APPEND _cbs_missing_modules "${_cbs_module}")
    endif()
  endforeach()
  set(${output_missing} "${_cbs_missing_modules}" PARENT_SCOPE)
endfunction()

# yaml is required for CBS itself. Rivet/Contur Python modules stay optional.
function(cbs_validate_python_for_cbs_preset)
  if(NOT CBS_PRESET_BUILD)
    return()
  endif()

  set(_cbs_required_modules yaml)
  cbs_python_missing_modules("${Python3_EXECUTABLE}" _cbs_missing_modules ${_cbs_required_modules})
  if(_cbs_missing_modules)
    message(FATAL_ERROR
      "CBS preset selected ${Python3_EXECUTABLE} (${Python3_VERSION}), but it cannot import the required yaml module.\n"
      "Install PyYAML for that Python or select a different Python3_EXECUTABLE.")
  endif()

  if(NOT CBS_WITH_RIVET_CONTUR)
    set(CBS_RIVET_CONTUR_PREREQUISITES_FOUND FALSE PARENT_SCOPE)
    set(CBS_RIVET_CONTUR_PREREQUISITES_REASON
        "disabled by CBS_WITH_RIVET_CONTUR=OFF" PARENT_SCOPE)
    return()
  endif()

  cbs_python_missing_modules("${Python3_EXECUTABLE}" _cbs_backend_missing
                             Cython configobj pandas matplotlib)
  if(_cbs_backend_missing)
    string(REPLACE ";" ", " _cbs_backend_missing_text "${_cbs_backend_missing}")
    set(CBS_RIVET_CONTUR_PREREQUISITES_FOUND FALSE PARENT_SCOPE)
    set(CBS_RIVET_CONTUR_PREREQUISITES_REASON
        "Python modules missing: ${_cbs_backend_missing_text}" PARENT_SCOPE)
    message(STATUS "CBS Rivet/Contur: unavailable (${_cbs_backend_missing_text})")
    message(STATUS "CBS Rivet/Contur: install with '${Python3_EXECUTABLE} -m pip install Cython configobj pandas matplotlib', then reconfigure")
  else()
    # GAMBIT historically tests the lower-case module name 'cython'.
    set(PY_cython_FOUND TRUE PARENT_SCOPE)
    set(PY_configobj_FOUND TRUE PARENT_SCOPE)
    set(PY_pandas_FOUND TRUE PARENT_SCOPE)
    set(PY_matplotlib_FOUND TRUE PARENT_SCOPE)
    set(CBS_RIVET_CONTUR_PREREQUISITES_FOUND TRUE PARENT_SCOPE)
    set(CBS_RIVET_CONTUR_PREREQUISITES_REASON "" PARENT_SCOPE)
  endif()
endfunction()

function(cbs_configure_python_for_cbs_preset)
  if(NOT CBS_AUTO_DETECT_PYTHON)
    return()
  endif()

  if(DEFINED Python3_EXECUTABLE AND NOT "${Python3_EXECUTABLE}" STREQUAL "")
    message(STATUS "CBS Python: using Python3_EXECUTABLE=${Python3_EXECUTABLE}")
    return()
  endif()

  unset(_cbs_python_command CACHE)
  unset(_cbs_python_command)
  find_program(_cbs_python_command NAMES python3)
  if(NOT _cbs_python_command OR _cbs_python_command MATCHES "-NOTFOUND$")
    message(FATAL_ERROR
      "CBS preset Python discovery failed: no python3 executable was found on PATH.\n"
      "Set -DPython3_EXECUTABLE=/path/to/python3 or disable CBS_AUTO_DETECT_PYTHON.")
  endif()

  execute_process(
    COMMAND "${_cbs_python_command}" -c "import sys; print(sys.executable); print(sys.version.split()[0]); print(sys.base_prefix)"
    RESULT_VARIABLE _cbs_python_result
    OUTPUT_VARIABLE _cbs_python_output
    ERROR_VARIABLE _cbs_python_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    TIMEOUT 10)
  if(NOT _cbs_python_result EQUAL 0)
    message(FATAL_ERROR
      "CBS preset Python discovery failed: could not inspect ${_cbs_python_command}: ${_cbs_python_error}")
  endif()

  string(REPLACE "\n" ";" _cbs_python_fields "${_cbs_python_output}")
  list(LENGTH _cbs_python_fields _cbs_python_field_count)
  if(_cbs_python_field_count LESS 2)
    message(FATAL_ERROR
      "CBS preset Python discovery failed: ${_cbs_python_command} did not report an executable and version")
  endif()
  list(GET _cbs_python_fields 0 _cbs_python_executable)
  list(GET _cbs_python_fields 1 _cbs_python_version)
  if(_cbs_python_field_count GREATER 2)
    list(GET _cbs_python_fields 2 _cbs_python_root)
  else()
    set(_cbs_python_root "")
  endif()

  if(NOT EXISTS "${_cbs_python_executable}")
    message(FATAL_ERROR
      "CBS preset Python discovery failed: ${_cbs_python_command} reported a missing executable ${_cbs_python_executable}")
  endif()

  cbs_python_has_module("${_cbs_python_executable}" yaml _cbs_python_has_yaml)
  if(NOT _cbs_python_has_yaml)
    message(FATAL_ERROR
      "CBS preset Python discovery selected ${_cbs_python_executable} (${_cbs_python_version}), but it cannot import the required yaml module.\n"
      "Install PyYAML for that Python or select a different Python3_EXECUTABLE.")
  endif()

  set(Python3_EXECUTABLE "${_cbs_python_executable}" CACHE FILEPATH
      "Python interpreter selected by the CBS preset" FORCE)
  set(Python3_EXECUTABLE "${_cbs_python_executable}" PARENT_SCOPE)
  if(NOT "${_cbs_python_root}" STREQUAL "")
    set(Python3_ROOT_DIR "${_cbs_python_root}" CACHE PATH
        "Python prefix selected by the CBS preset")
    set(Python3_ROOT_DIR "${_cbs_python_root}" PARENT_SCOPE)
  endif()

  message(STATUS "CBS Python: selected CPython ${_cbs_python_version} (${_cbs_python_executable})")
endfunction()
