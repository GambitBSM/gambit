# \author Pengxuan Zhu
#         (pengxuan.zhu@adelaide.edu.au)
# \date 2026 Aug
#
# Configure-time validation for public CBS presets.  These checks deliberately
# use CMake's native probes and do not build GAMBIT or any external project.
# Rivet/Contur stay optional: missing pandas/SQLite never fails a CBS configure.

include_guard(GLOBAL)

function(cbs_validate_environment)
  if(NOT CBS_PRESET_BUILD)
    return()
  endif()

  include(CheckCSourceCompiles)
  include(CheckCXXSourceCompiles)
  include(CheckFortranSourceCompiles)
  include(CheckLinkerFlag)

  set(_cbs_saved_required_flags "${CMAKE_REQUIRED_FLAGS}")
  set(_cbs_saved_required_includes "${CMAKE_REQUIRED_INCLUDES}")
  set(_cbs_saved_required_libraries "${CMAKE_REQUIRED_LIBRARIES}")
  set(_cbs_saved_required_link_options "${CMAKE_REQUIRED_LINK_OPTIONS}")
  set(_cbs_saved_required_quiet "${CMAKE_REQUIRED_QUIET}")

  set(CMAKE_REQUIRED_QUIET TRUE)
  check_c_source_compiles(
    "int main(void) { return 0; }"
    CBS_VALIDATION_C_COMPILE_LINK)
  set(_cbs_cxx17_source [=[
#include <type_traits>
template <typename T> constexpr int cbs_value(T value) {
  if constexpr (std::is_integral_v<T>) return value;
  return 0;
}
int main() { static_assert(cbs_value(17) == 17); return 0; }
]=])
  check_cxx_source_compiles("${_cbs_cxx17_source}"
                            CBS_VALIDATION_CXX17_COMPILE_LINK)
  set(_cbs_fortran_source [=[
program cbs_fortran_validation
  implicit none
  integer :: value
  value = 17
  if (value /= 17) stop 1
end program cbs_fortran_validation
]=])
  check_fortran_source_compiles("${_cbs_fortran_source}"
                                _cbs_fortran_free_form_compile_link
                                SRC_EXT F90)
  set(CBS_VALIDATION_FORTRAN_COMPILE_LINK
      "${_cbs_fortran_free_form_compile_link}")

  set(CBS_VALIDATION_OPENMP FALSE)
  if(OPENMP_FOUND OR FOUND_BREW_OPENMP OR GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP)
    set(CBS_VALIDATION_OPENMP TRUE)
  endif()

  set(CBS_VALIDATION_DYNAMIC_LOOKUP_REQUIRED FALSE)
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CBS_VALIDATION_DYNAMIC_LOOKUP_REQUIRED TRUE)
    check_linker_flag(CXX "-Wl,-undefined,dynamic_lookup"
                      _cbs_dynamic_lookup)
  else()
    set(_cbs_dynamic_lookup TRUE)
  endif()
  set(CBS_VALIDATION_DYNAMIC_LOOKUP "${_cbs_dynamic_lookup}")

  if(Python3_INCLUDE_DIRS AND Python3_LIBRARIES)
    set(CMAKE_REQUIRED_INCLUDES "${Python3_INCLUDE_DIRS}")
    set(CMAKE_REQUIRED_LIBRARIES "${Python3_LIBRARIES}")
    set(_cbs_python_source [=[
#include <Python.h>
int main(void) { return Py_IsInitialized() ? 0 : 0; }
]=])
    check_c_source_compiles("${_cbs_python_source}"
                            _cbs_python_c_api_compile_link)
    set(_cbs_python_development "${_cbs_python_c_api_compile_link}")
  else()
    set(_cbs_python_development FALSE)
  endif()
  set(CBS_VALIDATION_PYTHON_DEVELOPMENT "${_cbs_python_development}")

  if(Boost_FOUND)
    set(CMAKE_REQUIRED_INCLUDES "${Boost_INCLUDE_DIR}")
    set(CMAKE_REQUIRED_LIBRARIES "")
    set(_cbs_boost_source [=[
#include <boost/version.hpp>
static_assert(BOOST_VERSION >= 104800, "Boost 1.48 is required");
int main() { return 0; }
]=])
    check_cxx_source_compiles("${_cbs_boost_source}" _cbs_boost)
  else()
    set(_cbs_boost FALSE)
  endif()
  set(CBS_VALIDATION_BOOST "${_cbs_boost}")

  if(HDF5_FOUND)
    set(CMAKE_REQUIRED_INCLUDES "${HDF5_INCLUDE_DIR};${HDF5_INCLUDE_DIRS}")
    list(REMOVE_DUPLICATES CMAKE_REQUIRED_INCLUDES)
    set(CMAKE_REQUIRED_LIBRARIES "${HDF5_LIBRARIES}")
    set(_cbs_hdf5_source [=[
#include <hdf5.h>
int main(void) { return H5open() < 0; }
]=])
    check_c_source_compiles("${_cbs_hdf5_source}" _cbs_hdf5)
  else()
    set(_cbs_hdf5 FALSE)
  endif()
  set(CBS_VALIDATION_HDF5 "${_cbs_hdf5}")

  if(SQLite3_FOUND)
    set(CMAKE_REQUIRED_INCLUDES "${SQLite3_INCLUDE_DIRS}")
    set(CMAKE_REQUIRED_LIBRARIES "${SQLite3_LIBRARIES}")
    set(_cbs_sqlite3_source [=[
#include <sqlite3.h>
int main(void) { return sqlite3_libversion_number() == 0; }
]=])
    check_c_source_compiles("${_cbs_sqlite3_source}" _cbs_sqlite3)
  else()
    set(_cbs_sqlite3 FALSE)
  endif()
  set(CBS_VALIDATION_SQLITE3 "${_cbs_sqlite3}")

  set(CMAKE_REQUIRED_FLAGS "${_cbs_saved_required_flags}")
  set(CMAKE_REQUIRED_INCLUDES "${_cbs_saved_required_includes}")
  set(CMAKE_REQUIRED_LIBRARIES "${_cbs_saved_required_libraries}")
  set(CMAKE_REQUIRED_LINK_OPTIONS "${_cbs_saved_required_link_options}")
  set(CMAKE_REQUIRED_QUIET "${_cbs_saved_required_quiet}")

  set(CBS_VALIDATION_CYTHON ${PY_cython_FOUND})
  set(CBS_VALIDATION_CONFIGOBJ ${PY_configobj_FOUND})
  set(CBS_VALIDATION_PANDAS ${PY_pandas_FOUND})
  set(CBS_VALIDATION_MATPLOTLIB ${PY_matplotlib_FOUND})
  set(CBS_VALIDATION_ROOT FALSE)
  if(NOT EXCLUDE_ROOT)
    set(CBS_VALIDATION_ROOT TRUE)
  endif()

  set(CBS_VALIDATION_FASTJET_STATE "unavailable")
  if(FASTJET_INSTALLED)
    set(CBS_VALIDATION_FASTJET_STATE "available")
  elseif(TARGET fastjet)
    set(CBS_VALIDATION_FASTJET_STATE "scheduled for build")
  endif()
  set(CBS_VALIDATION_FJCONTRIB_STATE "unavailable")
  if(FJCONTRIB_INSTALLED)
    set(CBS_VALIDATION_FJCONTRIB_STATE "available (includes LundPlane)")
  elseif(TARGET fjcontrib)
    set(CBS_VALIDATION_FJCONTRIB_STATE "scheduled for build (includes LundPlane)")
  endif()

  set(CBS_VALIDATION_HEPMC_TARGET FALSE)
  if(TARGET hepmc)
    set(CBS_VALIDATION_HEPMC_TARGET TRUE)
  endif()
  set(CBS_VALIDATION_YODA_TARGET FALSE)
  if(TARGET yoda)
    set(CBS_VALIDATION_YODA_TARGET TRUE)
  endif()
  set(CBS_VALIDATION_RIVET_TARGET FALSE)
  if(TARGET rivet)
    set(CBS_VALIDATION_RIVET_TARGET TRUE)
  endif()
  set(CBS_VALIDATION_CONTUR_TARGET FALSE)
  if(TARGET contur)
    set(CBS_VALIDATION_CONTUR_TARGET TRUE)
  endif()

  set(CBS_VALIDATION_CBS_TARGET FALSE)
  if(TARGET CBS)
    set(CBS_VALIDATION_CBS_TARGET TRUE)
  endif()

  set(_cbs_failures "")
  foreach(_cbs_required_check
      C_COMPILE_LINK
      CXX17_COMPILE_LINK
      FORTRAN_COMPILE_LINK
      OPENMP
      PYTHON_DEVELOPMENT
      BOOST
      CBS_TARGET)
    if(NOT CBS_VALIDATION_${_cbs_required_check})
      string(REPLACE "_" " " _cbs_required_name "${_cbs_required_check}")
      string(TOLOWER "${_cbs_required_name}" _cbs_required_name)
      list(APPEND _cbs_failures "${_cbs_required_name}")
    endif()
  endforeach()
  if(CBS_VALIDATION_DYNAMIC_LOOKUP_REQUIRED AND NOT CBS_VALIDATION_DYNAMIC_LOOKUP)
    list(APPEND _cbs_failures "macOS dynamic_lookup linker flag")
  endif()

  set(CBS_ENVIRONMENT_READY TRUE)
  if(_cbs_failures)
    set(CBS_ENVIRONMENT_READY FALSE)
  endif()
  set(CBS_VALIDATION_REQUIRED_FAILURES "${_cbs_failures}")

  foreach(_cbs_validation_variable
      CBS_VALIDATION_C_COMPILE_LINK
      CBS_VALIDATION_CXX17_COMPILE_LINK
      CBS_VALIDATION_FORTRAN_COMPILE_LINK
      CBS_VALIDATION_OPENMP
      CBS_VALIDATION_DYNAMIC_LOOKUP_REQUIRED
      CBS_VALIDATION_DYNAMIC_LOOKUP
      CBS_VALIDATION_PYTHON_DEVELOPMENT
      CBS_VALIDATION_BOOST
      CBS_VALIDATION_HDF5
      CBS_VALIDATION_SQLITE3
      CBS_VALIDATION_CYTHON
      CBS_VALIDATION_CONFIGOBJ
      CBS_VALIDATION_PANDAS
      CBS_VALIDATION_MATPLOTLIB
      CBS_VALIDATION_ROOT
      CBS_VALIDATION_FASTJET_STATE
      CBS_VALIDATION_FJCONTRIB_STATE
      CBS_VALIDATION_HEPMC_TARGET
      CBS_VALIDATION_YODA_TARGET
      CBS_VALIDATION_RIVET_TARGET
      CBS_VALIDATION_CONTUR_TARGET
      CBS_VALIDATION_CBS_TARGET
      CBS_VALIDATION_REQUIRED_FAILURES
      CBS_ENVIRONMENT_READY)
    set(${_cbs_validation_variable} "${${_cbs_validation_variable}}" PARENT_SCOPE)
  endforeach()
endfunction()

function(cbs_validation_status value output)
  if("${value}")
    set(${output} "PASS" PARENT_SCOPE)
  else()
    set(${output} "FAIL" PARENT_SCOPE)
  endif()
endfunction()

# Pad labels so every summary row's colon sits in the same column.
function(cbs_summary_line label value)
  set(_cbs_label_width 22)
  string(LENGTH "${label}" _cbs_label_len)
  math(EXPR _cbs_pad "${_cbs_label_width} - ${_cbs_label_len}")
  set(_cbs_spaces "")
  if(_cbs_pad GREATER 0)
    foreach(_cbs_i RANGE 1 ${_cbs_pad})
      string(APPEND _cbs_spaces " ")
    endforeach()
  endif()
  message(STATUS "  ${label}${_cbs_spaces} : ${value}")
endfunction()

function(cbs_print_validation_summary)
  if(NOT CBS_PRESET_BUILD)
    return()
  endif()

  cbs_validation_status("${CBS_VALIDATION_C_COMPILE_LINK}" _cbs_c_status)
  cbs_validation_status("${CBS_VALIDATION_CXX17_COMPILE_LINK}" _cbs_cxx_status)
  cbs_validation_status("${CBS_VALIDATION_FORTRAN_COMPILE_LINK}" _cbs_fortran_status)
  cbs_validation_status("${CBS_VALIDATION_OPENMP}" _cbs_openmp_status)
  cbs_validation_status("${CBS_VALIDATION_PYTHON_DEVELOPMENT}" _cbs_python_status)
  cbs_validation_status("${CBS_VALIDATION_BOOST}" _cbs_boost_status)
  cbs_validation_status("${CBS_VALIDATION_CBS_TARGET}" _cbs_target_status)

  if(CBS_VALIDATION_DYNAMIC_LOOKUP_REQUIRED)
    cbs_validation_status("${CBS_VALIDATION_DYNAMIC_LOOKUP}" _cbs_dynamic_lookup_status)
  else()
    set(_cbs_dynamic_lookup_status "N/A")
  endif()

  cbs_summary_line("C compile/link" "${_cbs_c_status}")
  cbs_summary_line("C++17 compile/link" "${_cbs_cxx_status}")
  cbs_summary_line("Fortran compile/link" "${_cbs_fortran_status}")
  cbs_summary_line("OpenMP" "${_cbs_openmp_status}")
  cbs_summary_line("dynamic_lookup" "${_cbs_dynamic_lookup_status}")
  cbs_summary_line("Python development" "${_cbs_python_status}")
  cbs_summary_line("Boost" "${_cbs_boost_status}")
  cbs_summary_line("CBS target" "${_cbs_target_status}")
  if(CBS_ENVIRONMENT_READY)
    cbs_summary_line("CBS environment" "READY")
  else()
    string(REPLACE ";" ", " _cbs_failure_text "${CBS_VALIDATION_REQUIRED_FAILURES}")
    cbs_summary_line("CBS environment" "NOT READY (${_cbs_failure_text})")
  endif()
endfunction()

function(cbs_require_validated_environment)
  if(NOT CBS_PRESET_BUILD)
    return()
  endif()
  if(CBS_ENVIRONMENT_READY)
    return()
  endif()

  string(REPLACE ";" ", " _cbs_failure_text
         "${CBS_VALIDATION_REQUIRED_FAILURES}")
  set(_cbs_hint "cmake --preset ${CBS_BUILD_PRESET} --fresh")
  if(NOT CBS_VALIDATION_CBS_TARGET)
    string(APPEND _cbs_hint
           " (the CBS executable needs ColliderBit, HepMC, and pybind11)")
  endif()
  message(FATAL_ERROR
    "CBS preset '${CBS_BUILD_PRESET}' is not ready: ${_cbs_failure_text}.\n"
    "Resolve the reported requirements and rerun '${_cbs_hint}'.")
endfunction()
