# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# Apply a patch only when needed, while diagnosing a source tree that matches
# neither the unpatched nor the patched state.
#************************************************

foreach(required_variable PATCH_FILE PATCH_WORKING_DIRECTORY)
  if(NOT DEFINED ${required_variable} OR "${${required_variable}}" STREQUAL "")
    message(FATAL_ERROR "${required_variable} must be provided.")
  endif()
endforeach()

if(NOT EXISTS "${PATCH_FILE}")
  message(FATAL_ERROR "Patch file does not exist: ${PATCH_FILE}")
endif()

find_program(PATCH_EXECUTABLE patch)
if(NOT PATCH_EXECUTABLE)
  message(FATAL_ERROR "Could not find the 'patch' executable required for ${PATCH_FILE}.")
endif()

execute_process(
  COMMAND "${PATCH_EXECUTABLE}" --dry-run --batch --forward -p1 -i "${PATCH_FILE}"
  WORKING_DIRECTORY "${PATCH_WORKING_DIRECTORY}"
  RESULT_VARIABLE forward_result
  OUTPUT_VARIABLE forward_output
  ERROR_VARIABLE forward_error
)

if(forward_result EQUAL 0)
  execute_process(
    COMMAND "${PATCH_EXECUTABLE}" --batch --forward -p1 -i "${PATCH_FILE}"
    WORKING_DIRECTORY "${PATCH_WORKING_DIRECTORY}"
    RESULT_VARIABLE apply_result
    OUTPUT_VARIABLE apply_output
    ERROR_VARIABLE apply_error
  )
  if(NOT apply_result EQUAL 0)
    message(FATAL_ERROR
      "Failed to apply patch ${PATCH_FILE}.\n${apply_output}${apply_error}")
  endif()
else()
  execute_process(
    COMMAND "${PATCH_EXECUTABLE}" --dry-run --batch --forward -R -p1 -i "${PATCH_FILE}"
    WORKING_DIRECTORY "${PATCH_WORKING_DIRECTORY}"
    RESULT_VARIABLE reverse_result
    OUTPUT_VARIABLE reverse_output
    ERROR_VARIABLE reverse_error
  )
  if(reverse_result EQUAL 0)
    message(STATUS "Patch ${PATCH_FILE} is already applied; skipping.")
  else()
    message(FATAL_ERROR
      "Patch ${PATCH_FILE} cannot be applied cleanly and is not already applied.\n"
      "Forward dry-run output:\n${forward_output}${forward_error}\n"
      "Reverse dry-run output:\n${reverse_output}${reverse_error}")
  endif()
endif()
