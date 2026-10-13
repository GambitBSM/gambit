# Keep code-generation dependencies stable across identical reconfigurations.
include_guard(GLOBAL)

function(gambit_write_file_if_different filename contents)
  file(WRITE "${filename}.candidate" "${contents}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${filename}.candidate" "${filename}" RESULT_VARIABLE result)
  file(REMOVE "${filename}.candidate")
  if(NOT result EQUAL 0)
    message(FATAL_ERROR "Cannot update generated file: ${filename}")
  endif()
endfunction()

function(gambit_write_codegen_options stamp)
  # Length-prefix each argument so argument boundaries are part of the identity.
  set(contents "")
  foreach(argument IN LISTS ARGN)
    string(LENGTH "${argument}" length)
    string(APPEND contents "${length}:${argument}\n")
  endforeach()
  gambit_write_file_if_different("${stamp}" "${contents}")
endfunction()

function(gambit_check_codegen_outputs stamp)
  # Make does not regenerate missing BYPRODUCTS on its own. On reconfigure,
  # invalidate only the generator whose outputs have been removed.
  foreach(output IN LISTS ARGN)
    if(NOT EXISTS "${output}")
      file(REMOVE "${stamp}")
      return()
    endif()
  endforeach()
endfunction()
