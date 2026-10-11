# Shared read-only environment probes for GAMBIT and standalone presets.
# These helpers query commands, headers and package metadata; they never
# configure the source tree or create a build directory.

include_guard(GLOBAL)
include("${CMAKE_CURRENT_LIST_DIR}/NativeCompilerDiscovery.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/CBSPythonDiscovery.cmake")

function(preset_probe_first_existing output)
  foreach(_cbs_path ${ARGN})
    if(EXISTS "${_cbs_path}")
      set(${output} "${_cbs_path}" PARENT_SCOPE)
      return()
    endif()
  endforeach()
  set(${output} "" PARENT_SCOPE)
endfunction()

function(preset_probe_find_openmp output_found output_description output_reason)
  set(_cbs_openmp_found FALSE)
  set(_cbs_openmp_description "unavailable")
  set(_cbs_openmp_reason "")

  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    cbs_resolve_command(_cbs_brew "brew")
    if(NOT _cbs_brew)
      set(_cbs_openmp_reason "Homebrew libomp was not found; run 'brew install libomp'")
    else()
      execute_process(
        COMMAND "${_cbs_brew}" --prefix libomp
        RESULT_VARIABLE _cbs_libomp_result
        OUTPUT_VARIABLE _cbs_libomp_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        TIMEOUT 10)
      if(_cbs_libomp_result EQUAL 0 AND EXISTS "${_cbs_libomp_prefix}/lib/libomp.dylib")
        set(_cbs_openmp_found TRUE)
        set(_cbs_openmp_description "Homebrew libomp (${_cbs_libomp_prefix})")
      else()
        set(_cbs_openmp_reason "Homebrew libomp was not found; run 'brew install libomp'")
      endif()
    endif()
  else()
    cbs_resolve_command(_cbs_pkg_config "pkg-config")
    if(_cbs_pkg_config)
      execute_process(
        COMMAND "${_cbs_pkg_config}" --exists libgomp
        RESULT_VARIABLE _cbs_gomp_pc
        TIMEOUT 10)
      if(NOT _cbs_gomp_pc EQUAL 0)
        execute_process(
          COMMAND "${_cbs_pkg_config}" --exists openmp
          RESULT_VARIABLE _cbs_gomp_pc
          TIMEOUT 10)
      endif()
      if(_cbs_gomp_pc EQUAL 0)
        set(_cbs_openmp_found TRUE)
        set(_cbs_openmp_description "pkg-config OpenMP")
      endif()
    endif()
    if(NOT _cbs_openmp_found)
      file(GLOB _cbs_gomp_hits
        /usr/lib/libgomp.so*
        /usr/lib64/libgomp.so*
        /usr/lib/*/libgomp.so*
        /usr/lib/gcc/*/libgomp.so*
        /usr/lib/llvm-*/lib/libomp.so*
        /usr/lib64/libomp.so*
        /usr/lib/libomp.so*)
      if(_cbs_gomp_hits)
        list(GET _cbs_gomp_hits 0 _cbs_gomp_lib)
        set(_cbs_openmp_found TRUE)
        set(_cbs_openmp_description "${_cbs_gomp_lib}")
      else()
        set(_cbs_openmp_reason "libgomp/libomp was not found")
      endif()
    endif()
  endif()

  set(${output_found} "${_cbs_openmp_found}" PARENT_SCOPE)
  set(${output_description} "${_cbs_openmp_description}" PARENT_SCOPE)
  set(${output_reason} "${_cbs_openmp_reason}" PARENT_SCOPE)
endfunction()

function(preset_probe_find_boost output_found output_path)
  set(_cbs_boost_hints "")
  if(DEFINED ENV{BOOST_INCLUDEDIR} AND NOT "$ENV{BOOST_INCLUDEDIR}" STREQUAL "")
    list(APPEND _cbs_boost_hints "$ENV{BOOST_INCLUDEDIR}/boost/version.hpp")
  endif()
  if(DEFINED ENV{BOOST_ROOT} AND NOT "$ENV{BOOST_ROOT}" STREQUAL "")
    list(APPEND _cbs_boost_hints "$ENV{BOOST_ROOT}/include/boost/version.hpp")
  endif()
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    cbs_resolve_command(_cbs_brew "brew")
    if(_cbs_brew)
      execute_process(
        COMMAND "${_cbs_brew}" --prefix boost
        RESULT_VARIABLE _cbs_brew_boost_result
        OUTPUT_VARIABLE _cbs_brew_boost_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        TIMEOUT 10)
      if(_cbs_brew_boost_result EQUAL 0)
        list(APPEND _cbs_boost_hints "${_cbs_brew_boost_prefix}/include/boost/version.hpp")
      endif()
    endif()
  endif()
  list(APPEND _cbs_boost_hints
    /usr/include/boost/version.hpp
    /usr/local/include/boost/version.hpp
    /opt/local/include/boost/version.hpp)
  preset_probe_first_existing(_cbs_boost ${_cbs_boost_hints})
  if(_cbs_boost)
    set(${output_found} TRUE PARENT_SCOPE)
    set(${output_path} "${_cbs_boost}" PARENT_SCOPE)
  else()
    set(${output_found} FALSE PARENT_SCOPE)
    set(${output_path} "" PARENT_SCOPE)
  endif()
endfunction()

function(preset_probe_find_eigen output_found output_path)
  set(_cbs_eigen_hints "")
  if(DEFINED EIGEN3_INCLUDE_DIR AND NOT "${EIGEN3_INCLUDE_DIR}" STREQUAL "")
    list(APPEND _cbs_eigen_hints
      "${EIGEN3_INCLUDE_DIR}/Eigen/Core"
      "${EIGEN3_INCLUDE_DIR}/eigen3/Eigen/Core")
  endif()
  if(DEFINED ENV{EIGEN3_INCLUDE_DIR} AND NOT "$ENV{EIGEN3_INCLUDE_DIR}" STREQUAL "")
    list(APPEND _cbs_eigen_hints
      "$ENV{EIGEN3_INCLUDE_DIR}/Eigen/Core"
      "$ENV{EIGEN3_INCLUDE_DIR}/eigen3/Eigen/Core")
  endif()
  if(DEFINED ENV{EIGEN3_ROOT} AND NOT "$ENV{EIGEN3_ROOT}" STREQUAL "")
    list(APPEND _cbs_eigen_hints
      "$ENV{EIGEN3_ROOT}/include/eigen3/Eigen/Core"
      "$ENV{EIGEN3_ROOT}/Eigen/Core")
  endif()
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    cbs_resolve_command(_cbs_brew "brew")
    if(_cbs_brew)
      execute_process(
        COMMAND "${_cbs_brew}" --prefix eigen
        RESULT_VARIABLE _cbs_brew_eigen_result
        OUTPUT_VARIABLE _cbs_brew_eigen_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        TIMEOUT 10)
      if(_cbs_brew_eigen_result EQUAL 0)
        list(APPEND _cbs_eigen_hints "${_cbs_brew_eigen_prefix}/include/eigen3/Eigen/Core")
      endif()
    endif()
  endif()
  list(APPEND _cbs_eigen_hints
    /usr/include/eigen3/Eigen/Core
    /usr/local/include/eigen3/Eigen/Core
    /opt/local/include/eigen3/Eigen/Core)
  preset_probe_first_existing(_cbs_eigen ${_cbs_eigen_hints})
  if(_cbs_eigen)
    set(${output_found} TRUE PARENT_SCOPE)
    set(${output_path} "${_cbs_eigen}" PARENT_SCOPE)
  else()
    set(${output_found} FALSE PARENT_SCOPE)
    set(${output_path} "" PARENT_SCOPE)
  endif()
endfunction()

function(preset_probe_find_gsl output_found output_path)
  cbs_resolve_command(_cbs_gsl_config "gsl-config")
  if(_cbs_gsl_config)
    set(${output_found} TRUE PARENT_SCOPE)
    set(${output_path} "${_cbs_gsl_config}" PARENT_SCOPE)
    return()
  endif()
  cbs_resolve_command(_cbs_pkg_config "pkg-config")
  if(_cbs_pkg_config)
    execute_process(
      COMMAND "${_cbs_pkg_config}" --exists gsl
      RESULT_VARIABLE _cbs_gsl_pc
      TIMEOUT 10)
    if(_cbs_gsl_pc EQUAL 0)
      set(${output_found} TRUE PARENT_SCOPE)
      set(${output_path} "pkg-config gsl" PARENT_SCOPE)
      return()
    endif()
  endif()
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    cbs_resolve_command(_cbs_brew "brew")
    if(_cbs_brew)
      execute_process(
        COMMAND "${_cbs_brew}" --prefix gsl
        RESULT_VARIABLE _cbs_brew_gsl_result
        OUTPUT_VARIABLE _cbs_brew_gsl_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        TIMEOUT 10)
      if(_cbs_brew_gsl_result EQUAL 0 AND EXISTS "${_cbs_brew_gsl_prefix}/bin/gsl-config")
        set(${output_found} TRUE PARENT_SCOPE)
        set(${output_path} "${_cbs_brew_gsl_prefix}/bin/gsl-config" PARENT_SCOPE)
        return()
      endif()
    endif()
  endif()
  set(${output_found} FALSE PARENT_SCOPE)
  set(${output_path} "" PARENT_SCOPE)
endfunction()

function(preset_probe_find_hdf5 output_found output_description)
  # Keep this probe read-only. Prefer the HDF5 metadata installed with its
  # development package, then fall back to known header/library layouts.
  cbs_resolve_command(_cbs_pkg_config "pkg-config")
  if(_cbs_pkg_config)
    foreach(_cbs_hdf5_package hdf5 hdf5-serial)
      execute_process(
        COMMAND "${_cbs_pkg_config}" --modversion "${_cbs_hdf5_package}"
        RESULT_VARIABLE _cbs_hdf5_pkg_result
        OUTPUT_VARIABLE _cbs_hdf5_pkg_version
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        TIMEOUT 10)
      if(_cbs_hdf5_pkg_result EQUAL 0)
        set(${output_found} TRUE PARENT_SCOPE)
        set(${output_description}
            "${_cbs_hdf5_package} ${_cbs_hdf5_pkg_version} (pkg-config)"
            PARENT_SCOPE)
        return()
      endif()
    endforeach()
  endif()

  cbs_resolve_command(_cbs_h5cc "h5cc")
  if(_cbs_h5cc)
    set(${output_found} TRUE PARENT_SCOPE)
    set(${output_description} "${_cbs_h5cc}" PARENT_SCOPE)
    return()
  endif()

  set(_cbs_hdf5_headers "")
  set(_cbs_hdf5_libraries "")
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    cbs_resolve_command(_cbs_brew "brew")
    if(_cbs_brew)
      execute_process(
        COMMAND "${_cbs_brew}" --prefix hdf5
        RESULT_VARIABLE _cbs_brew_hdf5_result
        OUTPUT_VARIABLE _cbs_brew_hdf5_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        TIMEOUT 10)
      if(_cbs_brew_hdf5_result EQUAL 0)
        list(APPEND _cbs_hdf5_headers
             "${_cbs_brew_hdf5_prefix}/include/H5Ipublic.h")
        list(APPEND _cbs_hdf5_libraries
             "${_cbs_brew_hdf5_prefix}/lib/libhdf5.dylib")
      endif()
    endif()
  endif()
  list(APPEND _cbs_hdf5_headers
       /usr/include/hdf5/serial/H5Ipublic.h
       /usr/include/H5Ipublic.h
       /usr/local/include/H5Ipublic.h
       /opt/local/include/H5Ipublic.h)
  file(GLOB _cbs_hdf5_system_libraries
       /usr/lib/*/hdf5/serial/libhdf5.so*
       /usr/lib/*/libhdf5_serial.so*
       /usr/lib/libhdf5.so*
       /usr/local/lib/libhdf5.*
       /opt/local/lib/libhdf5.*)
  list(APPEND _cbs_hdf5_libraries ${_cbs_hdf5_system_libraries})
  preset_probe_first_existing(_cbs_hdf5_header ${_cbs_hdf5_headers})
  preset_probe_first_existing(_cbs_hdf5_library ${_cbs_hdf5_libraries})
  if(_cbs_hdf5_header AND _cbs_hdf5_library)
    set(${output_found} TRUE PARENT_SCOPE)
    set(${output_description} "${_cbs_hdf5_header}" PARENT_SCOPE)
  else()
    set(${output_found} FALSE PARENT_SCOPE)
    set(${output_description} "" PARENT_SCOPE)
  endif()
endfunction()

# GAMBIT requires an interpreter, but Python development libraries are optional
# there. Reuse metadata, but do not apply the stricter CBS development policy.
function(preset_probe_find_python output_found output_executable output_version output_reason)
  set(_probe_found FALSE)
  set(_probe_executable "")
  set(_probe_version "")
  set(_probe_reason "No python3 executable was found on PATH")
  if(DEFINED Python3_EXECUTABLE AND NOT "${Python3_EXECUTABLE}" STREQUAL "")
    set(_probe_command "${Python3_EXECUTABLE}")
  else()
    cbs_resolve_command(_probe_command python3)
  endif()
  if(_probe_command)
    cbs_read_python_info("${_probe_command}" _probe_result _probe_output _probe_error)
    string(REPLACE "\n" ";" _probe_fields "${_probe_output}")
    list(LENGTH _probe_fields _probe_field_count)
    if(_probe_result EQUAL 0 AND _probe_field_count GREATER_EQUAL 3)
      list(GET _probe_fields 0 _probe_executable)
      list(GET _probe_fields 1 _probe_version)
      if(EXISTS "${_probe_executable}" AND _probe_version VERSION_GREATER_EQUAL 3)
        set(_probe_found TRUE)
        set(_probe_reason "")
      else()
        set(_probe_reason "Python 3 is required; ${_probe_command} reported ${_probe_version}")
      endif()
    else()
      set(_probe_reason "Could not inspect Python interpreter ${_probe_command}")
    endif()
  endif()
  set(${output_found} "${_probe_found}" PARENT_SCOPE)
  set(${output_executable} "${_probe_executable}" PARENT_SCOPE)
  set(${output_version} "${_probe_version}" PARENT_SCOPE)
  set(${output_reason} "${_probe_reason}" PARENT_SCOPE)
  if(ARGC GREATER 4)
    set(${ARGV4} "${_probe_command}" PARENT_SCOPE)
  endif()
endfunction()

# A macro leaves the collected facts in the script scope for all selected
# providers. No project() or find_package() is used in this discovery phase.
macro(preset_probe_collect_environment)
  preset_probe_find_python(BOOTSTRAP_PYTHON_FOUND BOOTSTRAP_PYTHON_EXECUTABLE
                          BOOTSTRAP_PYTHON_VERSION BOOTSTRAP_PYTHON_REASON BOOTSTRAP_PYTHON_COMMAND)
  set(BOOTSTRAP_PYTHON_HAS_YAML FALSE)
  if(BOOTSTRAP_PYTHON_FOUND)
    gambit_probe_python_modules("${BOOTSTRAP_PYTHON_EXECUTABLE}" ${BOOTSTRAP_PYTHON_MODULES})
    cbs_python_has_module("${BOOTSTRAP_PYTHON_EXECUTABLE}" yaml BOOTSTRAP_PYTHON_HAS_YAML)
  endif()
  preset_probe_find_openmp(BOOTSTRAP_OPENMP_FOUND BOOTSTRAP_OPENMP_DESCRIPTION
                          BOOTSTRAP_OPENMP_REASON)
  preset_probe_find_boost(BOOTSTRAP_BOOST_FOUND BOOTSTRAP_BOOST_PATH)
  preset_probe_find_eigen(BOOTSTRAP_EIGEN_FOUND BOOTSTRAP_EIGEN_PATH)
  preset_probe_find_gsl(BOOTSTRAP_GSL_FOUND BOOTSTRAP_GSL_PATH)
  preset_probe_find_hdf5(BOOTSTRAP_HDF5_FOUND BOOTSTRAP_HDF5_DESCRIPTION)
endmacro()

function(preset_probe_core_reasons output)
  set(_probe_reasons "")
  if(NOT BOOTSTRAP_PYTHON_FOUND)
    list(APPEND _probe_reasons "${BOOTSTRAP_PYTHON_REASON}")
  elseif(NOT BOOTSTRAP_PYTHON_HAS_YAML)
    list(APPEND _probe_reasons "Python ${BOOTSTRAP_PYTHON_VERSION} cannot import yaml (install PyYAML)")
  endif()
  if(NOT BOOTSTRAP_OPENMP_FOUND)
    list(APPEND _probe_reasons "${BOOTSTRAP_OPENMP_REASON}")
  endif()
  if(NOT BOOTSTRAP_BOOST_FOUND)
    list(APPEND _probe_reasons "Boost headers were not found (need Boost >= 1.48)")
  endif()
  if(NOT BOOTSTRAP_EIGEN_FOUND)
    list(APPEND _probe_reasons "Eigen headers were not found (need Eigen >= 3.1)")
  endif()
  if(NOT BOOTSTRAP_GSL_FOUND)
    list(APPEND _probe_reasons "GSL development package was not found (need GSL >= 2.1)")
  endif()
  set(${output} "${_probe_reasons}" PARENT_SCOPE)
endfunction()

function(preset_probe_toolchain strategy output_c output_cxx output_fortran output_reason output_root)
  native_find_toolchain("${strategy}" _probe_found _probe_c _probe_cxx _probe_fortran
                        _probe_root _probe_version _probe_reason)
  set(${output_c} "${_probe_c}" PARENT_SCOPE)
  set(${output_cxx} "${_probe_cxx}" PARENT_SCOPE)
  set(${output_fortran} "${_probe_fortran}" PARENT_SCOPE)
  set(${output_reason} "${_probe_reason}" PARENT_SCOPE)
  set(${output_root} "${_probe_root}" PARENT_SCOPE)
endfunction()


# Store facts for the presentation layer without printing or altering policy.
function(preset_probe_record_result name reasons c_compiler cxx_compiler fortran_compiler llvm_root output_available)
  if(reasons)
    set(_probe_available FALSE)
  else()
    set(_probe_available TRUE)
  endif()
  set_property(GLOBAL PROPERTY BOOTSTRAP_${name}_AVAILABLE "${_probe_available}")
  set_property(GLOBAL PROPERTY BOOTSTRAP_${name}_REASONS "${reasons}")
  set_property(GLOBAL PROPERTY BOOTSTRAP_${name}_C "${c_compiler}")
  set_property(GLOBAL PROPERTY BOOTSTRAP_${name}_CXX "${cxx_compiler}")
  set_property(GLOBAL PROPERTY BOOTSTRAP_${name}_FORTRAN "${fortran_compiler}")
  set_property(GLOBAL PROPERTY BOOTSTRAP_${name}_LLVM_ROOT "${llvm_root}")
  set(${output_available} "${_probe_available}" PARENT_SCOPE)
endfunction()
