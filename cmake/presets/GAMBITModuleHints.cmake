# Hints printed at the end of a full GAMBIT preset configure.
# Lists the modules this configure kept and the commands that turn
# one or more of them off on the next cmake --preset invocation.
# Configure stays non-interactive: nothing here reads stdin.

include_guard(GLOBAL)

function(_gambit_hint_bit_directories out_var)
  set(_found "")
  file(GLOB _children RELATIVE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/*Bit*")
  foreach(_child ${_children})
    if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/${_child}")
      file(GLOB_RECURSE _src
           "${PROJECT_SOURCE_DIR}/${_child}/src/*.c"
           "${PROJECT_SOURCE_DIR}/${_child}/src/*.cc"
           "${PROJECT_SOURCE_DIR}/${_child}/src/*.cpp")
      file(GLOB_RECURSE _hdr
           "${PROJECT_SOURCE_DIR}/${_child}/include/*.h"
           "${PROJECT_SOURCE_DIR}/${_child}/include/*.hh"
           "${PROJECT_SOURCE_DIR}/${_child}/include/*.hpp")
      string(FIND "${_child}" ".dSYM" _dsym)
      if((_src OR _hdr) AND _dsym EQUAL -1)
        list(APPEND _found "${_child}")
      endif()
    endif()
  endforeach()
  list(SORT _found)
  set(${out_var} "${_found}" PARENT_SCOPE)
endfunction()

function(gambit_print_module_selection_hints)
  # Product presets such as darkbit-wimp also set GAMBIT_PRESET_TOOLCHAIN.
  # The ditch examples belong only to the full GAMBIT family.
  if(CBS_PRESET_BUILD OR NOT GAMBIT_BUILD_PRESET MATCHES "^(gambit|gambit-llvm|gambit-gnu)$")
    return()
  endif()
  set(_preset "${GAMBIT_BUILD_PRESET}")

  _gambit_hint_bit_directories(_all_bits)
  set(_enabled "")
  foreach(_bit ${GAMBIT_BITS})
    if(NOT _bit STREQUAL "")
      list(APPEND _enabled "${_bit}")
    endif()
  endforeach()
  list(SORT _enabled)

  set(_optional "")
  set(_disabled "")
  foreach(_bit ${_all_bits})
    if(_bit STREQUAL "ScannerBit")
      continue()
    endif()
    list(FIND _enabled "${_bit}" _on)
    if(_on EQUAL -1)
      list(APPEND _disabled "${_bit}")
    else()
      list(APPEND _optional "${_bit}")
    endif()
  endforeach()

  # Each command is complete. The preset clears Bits and itch when those
  # -D flags are left off, so a hint that only names the newly disabled
  # module would turn the others back on.
  set(_base_off "${_disabled}")

  set(_one "")
  foreach(_candidate ColliderBit CosmoBit NeutrinoBit FlavBit)
    list(FIND _optional "${_candidate}" _pick)
    if(_pick GREATER -1)
      set(_one "${_candidate}")
      break()
    endif()
  endforeach()
  if(_one STREQUAL "" AND _optional)
    list(GET _optional 0 _one)
  endif()
  set(_one_text "")
  if(NOT _one STREQUAL "")
    set(_one_list "${_base_off}")
    list(APPEND _one_list "${_one}")
    string(JOIN ";" _one_text ${_one_list})
  endif()

  set(_keep "")
  foreach(_candidate DarkBit PrecisionBit SpecBit DecayBit)
    list(FIND _optional "${_candidate}" _pick)
    if(_pick GREATER -1)
      list(APPEND _keep "${_candidate}")
    endif()
  endforeach()
  set(_keep_text "")
  list(LENGTH _keep _keep_count)
  list(LENGTH _optional _optional_count)
  if(_keep_count GREATER 0 AND _keep_count LESS _optional_count)
    string(JOIN ";" _keep_text ${_keep})
  endif()

  message("")
  message("${BoldYellow}-- Two examples for preset '${_preset}'. Repeat the same -D on every configure.${ColourReset}")
  message("${BoldYellow}   Leave it out and this preset turns the full module set back on.${ColourReset}")
  if(NOT _one_text STREQUAL "")
    if(_disabled)
      message("${BoldYellow}   Turn ${_one} off. Modules already off stay in this command:${ColourReset}")
    else()
      message("${BoldYellow}   Turn one module off:${ColourReset}")
    endif()
    message("${BoldYellow}     cmake --preset ${_preset} -Ditch=\"${_one_text}\"${ColourReset}")
  endif()
  if(NOT _keep_text STREQUAL "")
    message("${BoldYellow}   Keep only named modules:${ColourReset}")
    message("${BoldYellow}     cmake --preset ${_preset} -DBits=\"${_keep_text}\"${ColourReset}")
  endif()
endfunction()
