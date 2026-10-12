# Apply an external-project patch, accepting sources that already contain it.
# A failed forward patch is only safe to skip if the entire reverse patch fits.
if(NOT IS_DIRECTORY "${SOURCE_DIR}" OR NOT EXISTS "${PATCH_FILE}")
  message(FATAL_ERROR "Patch source directory or patch file does not exist: ${SOURCE_DIR}, ${PATCH_FILE}")
endif()

find_program(PATCH_EXECUTABLE patch)
if(NOT PATCH_EXECUTABLE)
  message(FATAL_ERROR "The patch program is required to patch external projects.")
endif()

execute_process(
  COMMAND "${PATCH_EXECUTABLE}" --dry-run --batch --forward -p1 -i "${PATCH_FILE}"
  WORKING_DIRECTORY "${SOURCE_DIR}"
  RESULT_VARIABLE forward_result
  OUTPUT_VARIABLE forward_output
  ERROR_VARIABLE forward_error
)
if(forward_result STREQUAL "0")
  execute_process(
    COMMAND "${PATCH_EXECUTABLE}" --batch --forward -p1 -i "${PATCH_FILE}"
    WORKING_DIRECTORY "${SOURCE_DIR}"
    RESULT_VARIABLE patch_result
  )
  if(NOT patch_result STREQUAL "0")
    message(FATAL_ERROR "Failed to apply ${PATCH_FILE}: ${patch_result}")
  endif()
else()
  # --forward also prevents patch from guessing a second reversal when only
  # some files contain the patch (in particular with macOS/BSD patch).
  execute_process(
    COMMAND "${PATCH_EXECUTABLE}" --dry-run --batch --reverse --forward -p1 -i "${PATCH_FILE}"
    WORKING_DIRECTORY "${SOURCE_DIR}"
    RESULT_VARIABLE reverse_result
    OUTPUT_QUIET
    ERROR_QUIET
  )
  if(NOT reverse_result STREQUAL "0")
    message(FATAL_ERROR "Patch neither applies cleanly nor is already fully applied: ${PATCH_FILE}\n${forward_output}${forward_error}")
  endif()
  message(STATUS "Patch already applied: ${PATCH_FILE}")
endif()
