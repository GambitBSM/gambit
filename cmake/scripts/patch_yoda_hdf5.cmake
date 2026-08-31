# Apply the YODA/HDF5 compatibility patch once, without prompting when a
# previous incremental build has already applied it.

if(NOT DEFINED YODA_SOURCE_DIR OR NOT DEFINED YODA_CONFIGURE OR NOT DEFINED YODA_PATCH)
  message(FATAL_ERROR "YODA_SOURCE_DIR, YODA_CONFIGURE and YODA_PATCH must be set")
endif()

file(READ "${YODA_CONFIGURE}" _yoda_configure)
string(FIND "${_yoda_configure}" "tr ';' ' '" _hdf5_separator_fix)
if(NOT _hdf5_separator_fix EQUAL -1)
  message(STATUS "YODA HDF5 separator fix is already applied")
  return()
endif()

execute_process(
  COMMAND patch -N -p1 -i "${YODA_PATCH}"
  WORKING_DIRECTORY "${YODA_SOURCE_DIR}"
  RESULT_VARIABLE _patch_result
  OUTPUT_VARIABLE _patch_stdout
  ERROR_VARIABLE _patch_stderr
)
if(NOT _patch_result EQUAL 0)
  message(FATAL_ERROR
    "Failed to apply YODA HDF5 separator fix (exit ${_patch_result}).\n"
    "stdout:\n${_patch_stdout}\nstderr:\n${_patch_stderr}")
endif()
