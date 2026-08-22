# Idempotently add an opt-in RESTFRAMES_QUIET guard to RestFrames' load-time
# banner. RestFrames prints from a shared-library constructor, before the
# executable's main() can decide how much output it wants.
#
# Required: -DRFBASE_CC=/path/to/src/RFBase.cc

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
