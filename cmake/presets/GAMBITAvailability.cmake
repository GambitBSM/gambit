# Read-only prerequisite policy for the full GAMBIT preset.
# Keep required dependencies aligned with CMakeLists.txt. HDF5 and Python
# development support may be omitted by GAMBIT's native configuration.

include_guard(GLOBAL)

function(preset_probe_gambit name strategy display_name output_available)
  preset_probe_core_reasons(_probe_reasons)
  preset_probe_toolchain("${strategy}" _probe_c _probe_cxx _probe_fortran
                        _probe_toolchain_reason _probe_root)
  if(_probe_toolchain_reason)
    list(APPEND _probe_reasons ${_probe_toolchain_reason})
  endif()
  preset_probe_record_result("${name}" "${_probe_reasons}" "${_probe_c}" "${_probe_cxx}"
                             "${_probe_fortran}" "${_probe_root}" _probe_available)
  set(${output_available} "${_probe_available}" PARENT_SCOPE)
endfunction()
