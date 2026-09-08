# Idempotently silence RestFrames' load-time banner when RESTFRAMES_QUIET is set.
# RestFrames prints from a shared-library constructor; GAMBIT/CBS use this to
# keep --help / --list-analyses free of that banner.
#
# Required: -DRFBASE_CC=/path/to/src/RFBase.cc
# Optional: -DRF_DIR=/path/to/RestFrames-<ver>
#           -DREBUILD=ON  also remake/install if RFBase.cc is newer than the lib

if(NOT DEFINED RFBASE_CC OR "${RFBASE_CC}" STREQUAL "")
  message(FATAL_ERROR "patch_restframes_quiet.cmake requires -DRFBASE_CC=")
endif()
if(NOT EXISTS "${RFBASE_CC}")
  message(FATAL_ERROR "RestFrames source not found: ${RFBASE_CC}")
endif()

file(READ "${RFBASE_CC}" _rfbase_src)
set(_rfbase_dirty FALSE)

if(NOT _rfbase_src MATCHES "#include <stdlib.h>")
  string(REPLACE
    "#include \"RestFrames/RFBase.hh\"\n"
    "#include \"RestFrames/RFBase.hh\"\n#include <stdlib.h>\n"
    _rfbase_src "${_rfbase_src}")
  set(_rfbase_dirty TRUE)
endif()

if(NOT _rfbase_src MATCHES "RESTFRAMES_QUIET")
  string(REPLACE
    "static void initializer(void){\n    printf"
    "static void initializer(void){\n    if (getenv(\"RESTFRAMES_QUIET\")) { RestFrames::RFKey key(0); return; }\n    printf"
    _rfbase_src "${_rfbase_src}")
  if(NOT _rfbase_src MATCHES "RESTFRAMES_QUIET")
    message(FATAL_ERROR "Failed to insert RESTFRAMES_QUIET guard into ${RFBASE_CC}")
  endif()
  set(_rfbase_dirty TRUE)
endif()

if(_rfbase_dirty)
  file(WRITE "${RFBASE_CC}" "${_rfbase_src}")
endif()

if(NOT REBUILD)
  return()
endif()
if(NOT DEFINED RF_DIR OR "${RF_DIR}" STREQUAL "" OR NOT EXISTS "${RF_DIR}/Makefile")
  return()
endif()

set(_rf_lib "")
foreach(_candidate
    "${RF_DIR}/lib/libRestFrames.dylib"
    "${RF_DIR}/lib/libRestFrames.so"
    "${RF_DIR}/lib/libRestFrames.a")
  if(EXISTS "${_candidate}")
    set(_rf_lib "${_candidate}")
    break()
  endif()
endforeach()

set(_need_rebuild ${_rfbase_dirty})
if(NOT _need_rebuild AND _rf_lib)
  file(TIMESTAMP "${RFBASE_CC}" _src_ts)
  file(TIMESTAMP "${_rf_lib}" _lib_ts)
  if(_src_ts STRGREATER _lib_ts)
    set(_need_rebuild TRUE)
  endif()
endif()
if(NOT _need_rebuild AND NOT _rf_lib)
  set(_need_rebuild TRUE)
endif()
if(NOT _need_rebuild)
  return()
endif()

if(NOT DEFINED MAKE_PROGRAM OR "${MAKE_PROGRAM}" STREQUAL "")
  find_program(MAKE_PROGRAM NAMES make gmake)
endif()
if(NOT MAKE_PROGRAM)
  message(WARNING "RestFrames quiet-banner patch applied, but make was not found to rebuild RestFrames.")
  return()
endif()

execute_process(
  COMMAND "${MAKE_PROGRAM}"
  WORKING_DIRECTORY "${RF_DIR}"
  RESULT_VARIABLE _rf_build)
if(NOT _rf_build EQUAL 0)
  message(FATAL_ERROR "RestFrames rebuild after RESTFRAMES_QUIET patch failed (${_rf_build})")
endif()
execute_process(
  COMMAND "${MAKE_PROGRAM}" install
  WORKING_DIRECTORY "${RF_DIR}"
  RESULT_VARIABLE _rf_install)
if(NOT _rf_install EQUAL 0)
  message(FATAL_ERROR "RestFrames install after RESTFRAMES_QUIET patch failed (${_rf_install})")
endif()
