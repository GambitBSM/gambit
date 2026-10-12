# Supply RestFrames sources for ExternalProject's DOWNLOAD_COMMAND. Existing
# sources are retained; the following identity preparation step validates the
# requested repository/tag and reconstructs pristine sources before patching.
cmake_minimum_required(VERSION 3.16.3)

function(_gambit_ensure_git_command result)
  execute_process(COMMAND "${CMAKE_COMMAND}" -E env
    GIT_TERMINAL_PROMPT=0 GIT_ASKPASS=/usr/bin/false SSH_ASKPASS=/usr/bin/false
    git ${ARGN} RESULT_VARIABLE status ERROR_VARIABLE error TIMEOUT 300)
  set(${result} "${status}" PARENT_SCOPE)
  set(${result}_error "${error}" PARENT_SCOPE)
endfunction()

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

# Reuse completed downloads without checking out/fetching from an old origin.
# The preparation step handles repository/tag changes safely. In particular,
# fetching a new tag from a retained old origin could fail before preparation.
if(_has_source)
  return()
endif()

if(EXISTS "${DIR}" AND NOT EXISTS "${DIR}/.git" AND NOT _has_source AND NOT _is_empty)
  message(FATAL_ERROR
    "${DIR} exists but is not a git checkout of ${URL}. Remove it and rebuild.")
endif()

if(NOT EXISTS "${DIR}/.git")
  _gambit_ensure_git_command(_clone_result clone "${URL}" "${DIR}")
  if(NOT _clone_result EQUAL 0)
    message(FATAL_ERROR "git clone ${URL} ${DIR} failed (${_clone_result}): ${_clone_result_error}")
  endif()
endif()

_gambit_ensure_git_command(_checkout_result -C "${DIR}" checkout -q "${TAG}")
if(NOT _checkout_result EQUAL 0)
  _gambit_ensure_git_command(_fetch_result -C "${DIR}" fetch --tags --quiet)
  if(NOT _fetch_result EQUAL 0)
    message(FATAL_ERROR "git fetch --tags in ${DIR} failed (${_fetch_result}): ${_fetch_result_error}")
  endif()
  _gambit_ensure_git_command(_checkout_result -C "${DIR}" checkout -q "${TAG}")
  if(NOT _checkout_result EQUAL 0)
    message(FATAL_ERROR "git checkout ${TAG} in ${DIR} failed (${_checkout_result}): ${_checkout_result_error}")
  endif()
endif()
