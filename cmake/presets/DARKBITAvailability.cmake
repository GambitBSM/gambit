# Read-only prerequisite policy for the DarkBit standalone presets.
# WIMP, MSSM, and scalar singlet Z2 link the same core libraries as a
# narrowed GAMBIT configure, so the probe matches the full GAMBIT toolchain
# check. DarkBit_standalone_WIMP also needs pybind11, which configure enforces.

include_guard(GLOBAL)

function(preset_probe_darkbit name strategy display_name output_available)
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
