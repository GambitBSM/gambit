# Ensure DIR is a checkout of URL at TAG. Used as an ExternalProject
# DOWNLOAD_COMMAND so a leftover source tree does not fail git clone.

if(NOT DEFINED DIR OR "${DIR}" STREQUAL "" OR
   NOT DEFINED URL OR "${URL}" STREQUAL "" OR
   NOT DEFINED TAG OR "${TAG}" STREQUAL "")
  message(FATAL_ERROR "ensure_git_clone.cmake requires -DDIR= -DURL= -DTAG=")
endif()

set(_has_source FALSE)
if(EXISTS "${DIR}/configure" OR EXISTS "${DIR}/configure.ac")
  set(_has_source TRUE)
endif()

set(_is_empty TRUE)
if(EXISTS "${DIR}")
  file(GLOB _dir_contents LIST_DIRECTORIES TRUE "${DIR}/*")
  if(_dir_contents)
    set(_is_empty FALSE)
  endif()
endif()

# A complete source drop is usable even without .git.
if(_has_source AND NOT EXISTS "${DIR}/.git")
  return()
endif()

if(EXISTS "${DIR}" AND NOT EXISTS "${DIR}/.git" AND NOT _has_source AND NOT _is_empty)
  message(FATAL_ERROR
    "${DIR} exists but is not a git checkout of ${URL}. Remove it and rebuild.")
endif()

if(NOT EXISTS "${DIR}/.git")
  execute_process(
    COMMAND git clone "${URL}" "${DIR}"
    RESULT_VARIABLE _clone_result)
  if(NOT _clone_result EQUAL 0)
    message(FATAL_ERROR "git clone ${URL} ${DIR} failed (${_clone_result})")
  endif()
endif()

execute_process(
  COMMAND git -C "${DIR}" checkout -q "${TAG}"
  RESULT_VARIABLE _checkout_result
  ERROR_QUIET)
if(NOT _checkout_result EQUAL 0)
  execute_process(
    COMMAND git -C "${DIR}" fetch --tags --quiet
    RESULT_VARIABLE _fetch_result)
  if(NOT _fetch_result EQUAL 0)
    message(FATAL_ERROR "git fetch --tags in ${DIR} failed (${_fetch_result})")
  endif()
  execute_process(
    COMMAND git -C "${DIR}" checkout -q "${TAG}"
    RESULT_VARIABLE _checkout_result)
  if(NOT _checkout_result EQUAL 0)
    message(FATAL_ERROR "git checkout ${TAG} in ${DIR} failed (${_checkout_result})")
  endif()
endif()
