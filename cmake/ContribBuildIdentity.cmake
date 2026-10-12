# Identities for contributed packages installed inside the source tree.
# Author: Pengxuan Zhu, 2026 Oct
if(DEFINED GAMBIT_CONTRIB_IDENTITY_ACTION)
  cmake_minimum_required(VERSION 3.16.3)
endif()
include_guard(GLOBAL)
set(_GAMBIT_CONTRIB_IDENTITY_MODULE "${CMAKE_CURRENT_LIST_FILE}")

function(gambit_contrib_write_if_changed path content)
  if(EXISTS "${path}")
    file(READ "${path}" previous)
    if("${previous}" STREQUAL "${content}")
      return()
    endif()
  endif()
  get_filename_component(parent "${path}" DIRECTORY)
  file(MAKE_DIRECTORY "${parent}")
  file(WRITE "${path}" "${content}")
endfunction()

function(gambit_contrib_build_identity output)
  set(fields CMAKE_SYSTEM_NAME CMAKE_SYSTEM_PROCESSOR CMAKE_BUILD_TYPE
      CMAKE_OSX_ARCHITECTURES CMAKE_OSX_SYSROOT MACOS_DEPLOYMENT_TARGET
      CMAKE_OSX_DEPLOYMENT_TARGET CMAKE_CXX_STANDARD
      CMAKE_CXX_STANDARD_REQUIRED CMAKE_CXX_EXTENSIONS)
  foreach(language C CXX Fortran)
    list(APPEND fields CMAKE_${language}_COMPILER CMAKE_${language}_COMPILER_ID
         CMAKE_${language}_COMPILER_VERSION CMAKE_${language}_COMPILER_TARGET
         CMAKE_${language}_COMPILER_ARG1 CMAKE_${language}_COMPILER_REALPATH
         CMAKE_${language}_COMPILER_TIMESTAMP)
    set(CMAKE_${language}_COMPILER_REALPATH "")
    set(CMAKE_${language}_COMPILER_TIMESTAMP "")
    if(NOT "${CMAKE_${language}_COMPILER}" STREQUAL "")
      get_filename_component(CMAKE_${language}_COMPILER_REALPATH
          "${CMAKE_${language}_COMPILER}" REALPATH)
      if(EXISTS "${CMAKE_${language}_COMPILER_REALPATH}")
        file(TIMESTAMP "${CMAKE_${language}_COMPILER_REALPATH}"
             CMAKE_${language}_COMPILER_TIMESTAMP "%Y-%m-%dT%H:%M:%SZ" UTC)
      endif()
    endif()
  endforeach()
  list(APPEND fields ${ARGN})
  set(identity "GAMBIT contrib build identity v1\n")
  foreach(field IN LISTS fields)
    # Length-prefix values so lists, newlines and argument boundaries are distinct.
    string(LENGTH "${${field}}" length)
    string(APPEND identity "${field}=${length}:${${field}}\n")
  endforeach()
  set(${output} "${identity}" PARENT_SCOPE)
endfunction()

function(gambit_contrib_identity_matches record identity result reason)
  set(${result} FALSE PARENT_SCOPE)
  if(NOT EXISTS "${record}" OR IS_DIRECTORY "${record}")
    set(${reason} "no recorded build identity" PARENT_SCOPE)
    return()
  endif()
  file(READ "${record}" previous)
  if(NOT "${previous}" STREQUAL "${identity}")
    set(${reason} "build identity changed" PARENT_SCOPE)
    return()
  endif()
  set(${result} TRUE PARENT_SCOPE)
  set(${reason} "build identity matches" PARENT_SCOPE)
endfunction()

function(gambit_find_contrib_library output name directory)
  # find_library otherwise trusts stale cached paths, even outside this prefix.
  set(_gambit_contrib_library "_gambit_contrib_library-NOTFOUND")
  find_library(_gambit_contrib_library NAMES "${name}" PATHS "${directory}"
               NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
  if(NOT EXISTS "${_gambit_contrib_library}" OR IS_DIRECTORY "${_gambit_contrib_library}")
    set(_gambit_contrib_library "${output}-NOTFOUND")
  endif()
  set(${output} "${_gambit_contrib_library}" CACHE FILEPATH
      "${name} in the GAMBIT contributed installation" FORCE)
  set(${output} "${_gambit_contrib_library}" PARENT_SCOPE)
  unset(_gambit_contrib_library CACHE)
endfunction()

function(gambit_write_contrib_identity_request package version checksum source prefix identity files libraries)
  cmake_parse_arguments(SOURCE "" "GIT_REPOSITORY;GIT_TAG" "" ${ARGN})
  set(CONTRIB_GIT_REPOSITORY "${SOURCE_GIT_REPOSITORY}")
  set(CONTRIB_GIT_TAG "${SOURCE_GIT_TAG}")
  if(CONTRIB_GIT_REPOSITORY)
    foreach(field CONTRIB_GIT_REPOSITORY CONTRIB_GIT_TAG)
      string(LENGTH "${${field}}" length)
      string(APPEND identity "${field}=${length}:${${field}}\n")
    endforeach()
  endif()
  set(request_dir "${CMAKE_BINARY_DIR}/${package}-prefix/tmp")
  set(CONTRIB_SOURCE_ROOT "${PROJECT_SOURCE_DIR}/contrib")
  set(CONTRIB_SOURCE_DIR "${source}")
  set(CONTRIB_BUILD_ROOT "${CMAKE_BINARY_DIR}")
  set(CONTRIB_STAGING_DIR "${request_dir}/${package}-pristine")
  set(CONTRIB_ARCHIVE "${CMAKE_BINARY_DIR}/${package}_${version}.tar.gz")
  set(CONTRIB_MD5 "${checksum}")
  set(CONTRIB_IDENTITY_INPUT "${request_dir}/${package}-identity.txt")
  set(CONTRIB_IDENTITY_RECORD "${prefix}/.gambit-${package}-build-identity")
  set(CONTRIB_REQUIRED_FILES "${files}")
  set(CONTRIB_LIBRARY_NAMES "${libraries}")
  set(CONTRIB_LIBRARY_DIR "${prefix}/lib")
  gambit_contrib_write_if_changed("${CONTRIB_IDENTITY_INPUT}" "${identity}")
  set(request "# Generated contrib build inputs.\n")
  foreach(field CONTRIB_SOURCE_ROOT CONTRIB_SOURCE_DIR CONTRIB_BUILD_ROOT
      CONTRIB_STAGING_DIR CONTRIB_ARCHIVE CONTRIB_MD5 CONTRIB_GIT_REPOSITORY
      CONTRIB_GIT_TAG CONTRIB_IDENTITY_INPUT
      CONTRIB_IDENTITY_RECORD CONTRIB_REQUIRED_FILES CONTRIB_LIBRARY_NAMES
      CONTRIB_LIBRARY_DIR CMAKE_FIND_LIBRARY_PREFIXES CMAKE_FIND_LIBRARY_SUFFIXES)
    set(equals "")
    string(FIND "${${field}}" "]${equals}]" closing)
    while(NOT closing EQUAL -1)
      string(APPEND equals "=")
      string(FIND "${${field}}" "]${equals}]" closing)
    endwhile()
    string(APPEND request "set(${field} [${equals}[${${field}}]${equals}])\n")
  endforeach()
  set(request_file "${request_dir}/${package}-identity-request.cmake")
  gambit_contrib_write_if_changed("${request_file}" "${request}")
  set(${package}_identity_input "${CONTRIB_IDENTITY_INPUT}" PARENT_SCOPE)
  set(${package}_identity_request "${request_file}" PARENT_SCOPE)
endfunction()

function(gambit_contrib_installation_matches request result reason)
  include("${request}")
  file(READ "${CONTRIB_IDENTITY_INPUT}" identity)
  gambit_contrib_identity_matches("${CONTRIB_IDENTITY_RECORD}" "${identity}" matches why)
  if(matches)
    foreach(path IN LISTS CONTRIB_REQUIRED_FILES)
      if(NOT EXISTS "${path}" OR IS_DIRECTORY "${path}")
        set(matches FALSE)
        set(why "missing required file: ${path}")
      endif()
    endforeach()
    foreach(name IN LISTS CONTRIB_LIBRARY_NAMES)
      gambit_find_contrib_library(library "${name}" "${CONTRIB_LIBRARY_DIR}")
      if(NOT library)
        set(matches FALSE)
        set(why "missing installed library: ${name}")
      endif()
    endforeach()
  endif()
  set(${result} "${matches}" PARENT_SCOPE)
  set(${reason} "${why}" PARENT_SCOPE)
endfunction()

function(gambit_add_contrib_identity_steps package)
  set(keep_stamps "${ARGV1}")
  # Missing files can leave old completion stamps valid. Invalidate only this
  # rejected package; source/install trees are changed by the build step later.
  set(stamp "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
  # An optional TRUE argument registers the steps while keeping completion
  # stamps for a matching in-source installation (RestFrames).
  if(NOT keep_stamps)
    foreach(step prepare_source patch configure build install done record_identity)
      file(REMOVE "${stamp}-${step}")
    endforeach()
    file(REMOVE "${CMAKE_BINARY_DIR}/CMakeFiles/${package}-complete")
  endif()
  include("${${package}_identity_request}")
  if(NOT CONTRIB_GIT_REPOSITORY)
    set(archive_valid FALSE)
    if(EXISTS "${CONTRIB_ARCHIVE}" AND NOT IS_DIRECTORY "${CONTRIB_ARCHIVE}")
      file(MD5 "${CONTRIB_ARCHIVE}" checksum)
      if(checksum STREQUAL CONTRIB_MD5)
        set(archive_valid TRUE)
      endif()
    endif()
    if(NOT archive_valid)
      file(REMOVE "${stamp}-download")
    endif()
  endif()
  ExternalProject_Add_Step(${package} prepare_source
    COMMAND "${CMAKE_COMMAND}" "-DGAMBIT_CONTRIB_IDENTITY_ACTION=PREPARE"
            "-DGAMBIT_CONTRIB_IDENTITY_REQUEST=${${package}_identity_request}"
            -P "${_GAMBIT_CONTRIB_IDENTITY_MODULE}"
    DEPENDEES update DEPENDERS patch
    DEPENDS "${${package}_identity_input}" "${${package}_identity_request}"
            "${_GAMBIT_CONTRIB_IDENTITY_MODULE}"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    COMMENT "Preparing pristine ${package} sources for the current build identity")
  ExternalProject_Add_Step(${package} record_identity
    COMMAND "${CMAKE_COMMAND}" "-DGAMBIT_CONTRIB_IDENTITY_ACTION=RECORD"
            "-DGAMBIT_CONTRIB_IDENTITY_REQUEST=${${package}_identity_request}"
            -P "${_GAMBIT_CONTRIB_IDENTITY_MODULE}"
    DEPENDEES install
    DEPENDS "${${package}_identity_input}" "${${package}_identity_request}"
            "${_GAMBIT_CONTRIB_IDENTITY_MODULE}"
    COMMENT "Recording successful ${package} installation identity")
endfunction()

function(gambit_contrib_require_child path root)
  # REALPATH does not canonicalise missing descendants on older CMake/macOS.
  # Resolve their closest existing ancestor, including /var -> /private/var.
  get_filename_component(existing "${path}" ABSOLUTE)
  set(tail "")
  while(NOT EXISTS "${existing}" AND NOT IS_SYMLINK "${existing}")
    get_filename_component(name "${existing}" NAME)
    get_filename_component(parent "${existing}" DIRECTORY)
    if(parent STREQUAL existing)
      message(FATAL_ERROR "Cannot resolve contrib path: ${path}")
    endif()
    set(tail "/${name}${tail}")
    set(existing "${parent}")
  endwhile()
  get_filename_component(existing "${existing}" REALPATH)
  set(path "${existing}${tail}")
  get_filename_component(root "${root}" REALPATH)
  file(RELATIVE_PATH relative "${root}" "${path}")
  if(relative STREQUAL "" OR relative STREQUAL "." OR relative STREQUAL ".."
     OR relative MATCHES "^[.][.]/" OR IS_ABSOLUTE "${relative}")
    message(FATAL_ERROR "Contrib path must be below ${root}: ${path}")
  endif()
endfunction()

function(gambit_prepare_git_contrib)
  file(REMOVE_RECURSE "${CONTRIB_STAGING_DIR}")
  set(clone_result 1)
  set(local_source FALSE)
  if(EXISTS "${CONTRIB_SOURCE_DIR}/.git")
    execute_process(COMMAND git -C "${CONTRIB_SOURCE_DIR}" remote get-url origin
      RESULT_VARIABLE origin_result OUTPUT_VARIABLE origin_url
      ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE TIMEOUT 10)
    if(origin_result EQUAL 0 AND origin_url STREQUAL CONTRIB_GIT_REPOSITORY)
      set(local_source TRUE)
    endif()
  endif()
  if(local_source)
    execute_process(COMMAND "${CMAKE_COMMAND}" -E env GIT_TERMINAL_PROMPT=0
      GIT_ASKPASS=/usr/bin/false SSH_ASKPASS=/usr/bin/false
      git clone --no-hardlinks --no-checkout "${CONTRIB_SOURCE_DIR}" "${CONTRIB_STAGING_DIR}"
      RESULT_VARIABLE clone_result ERROR_VARIABLE clone_error TIMEOUT 300)
    if(clone_result EQUAL 0)
      execute_process(COMMAND "${CMAKE_COMMAND}" -E env GIT_TERMINAL_PROMPT=0
        GIT_ASKPASS=/usr/bin/false SSH_ASKPASS=/usr/bin/false
        git -c core.hooksPath=/dev/null -C "${CONTRIB_STAGING_DIR}"
        checkout --detach --force "${CONTRIB_GIT_TAG}"
        RESULT_VARIABLE clone_result ERROR_VARIABLE clone_error TIMEOUT 60)
    endif()
  endif()
  if(NOT clone_result EQUAL 0)
    # Missing Git metadata, a different upstream, or a missing tag require a
    # fresh checkout. Keep the old installation until this succeeds.
    file(REMOVE_RECURSE "${CONTRIB_STAGING_DIR}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E env GIT_TERMINAL_PROMPT=0
      GIT_ASKPASS=/usr/bin/false SSH_ASKPASS=/usr/bin/false
      git -c core.hooksPath=/dev/null clone --branch "${CONTRIB_GIT_TAG}" --single-branch
      "${CONTRIB_GIT_REPOSITORY}" "${CONTRIB_STAGING_DIR}"
      RESULT_VARIABLE clone_result ERROR_VARIABLE clone_error TIMEOUT 300)
  endif()
  if(NOT clone_result EQUAL 0)
    message(FATAL_ERROR "Could not prepare pristine contrib sources: ${clone_error}")
  endif()
  execute_process(COMMAND git -C "${CONTRIB_STAGING_DIR}" remote set-url origin
      "${CONTRIB_GIT_REPOSITORY}" RESULT_VARIABLE origin_result ERROR_VARIABLE origin_error TIMEOUT 30)
  if(NOT origin_result EQUAL 0)
    message(FATAL_ERROR "Could not set contrib upstream: ${origin_error}")
  endif()
  if(NOT EXISTS "${CONTRIB_STAGING_DIR}/configure")
    message(FATAL_ERROR "Contrib checkout has no configure script: ${CONTRIB_GIT_REPOSITORY}")
  endif()
endfunction()

# Only build steps (and temporary script fixtures) enter this branch.
if(DEFINED GAMBIT_CONTRIB_IDENTITY_ACTION)
  if(NOT EXISTS "${GAMBIT_CONTRIB_IDENTITY_REQUEST}")
    message(FATAL_ERROR "Missing contrib identity request: ${GAMBIT_CONTRIB_IDENTITY_REQUEST}")
  endif()
  include("${GAMBIT_CONTRIB_IDENTITY_REQUEST}")
  gambit_contrib_require_child("${CONTRIB_SOURCE_DIR}" "${CONTRIB_SOURCE_ROOT}")
  gambit_contrib_require_child("${CONTRIB_IDENTITY_RECORD}" "${CONTRIB_SOURCE_ROOT}")
  if(GAMBIT_CONTRIB_IDENTITY_ACTION STREQUAL "PREPARE")
    gambit_contrib_require_child("${CONTRIB_STAGING_DIR}" "${CONTRIB_BUILD_ROOT}")
    if(CONTRIB_GIT_REPOSITORY)
      # --fresh may recreate EP stamps even when retained objects are valid.
      gambit_contrib_installation_matches("${GAMBIT_CONTRIB_IDENTITY_REQUEST}" reusable reason)
      if(reusable)
        return()
      endif()
      gambit_prepare_git_contrib()
      set(pristine "${CONTRIB_STAGING_DIR}")
    else()
      if(NOT EXISTS "${CONTRIB_ARCHIVE}")
        message(FATAL_ERROR "Missing downloaded contrib archive: ${CONTRIB_ARCHIVE}")
      endif()
      file(MD5 "${CONTRIB_ARCHIVE}" checksum)
      if(NOT checksum STREQUAL CONTRIB_MD5)
        message(FATAL_ERROR "Contrib archive checksum mismatch: ${CONTRIB_ARCHIVE}")
      endif()
      file(REMOVE_RECURSE "${CONTRIB_STAGING_DIR}")
      file(MAKE_DIRECTORY "${CONTRIB_STAGING_DIR}")
      execute_process(COMMAND "${CMAKE_COMMAND}" -E tar xf "${CONTRIB_ARCHIVE}"
          WORKING_DIRECTORY "${CONTRIB_STAGING_DIR}" RESULT_VARIABLE result)
      if(NOT result EQUAL 0)
        message(FATAL_ERROR "Could not extract contrib archive: ${CONTRIB_ARCHIVE}")
      endif()
      file(GLOB entries "${CONTRIB_STAGING_DIR}/*")
      list(LENGTH entries count)
      set(pristine "${CONTRIB_STAGING_DIR}")
      if(count EQUAL 1 AND IS_DIRECTORY "${entries}")
        set(pristine "${entries}")
      endif()
      if(NOT EXISTS "${pristine}/configure")
        message(FATAL_ERROR "Contrib archive has no configure script: ${CONTRIB_ARCHIVE}")
      endif()
    endif()
    file(REMOVE "${CONTRIB_IDENTITY_RECORD}")
    file(REMOVE_RECURSE "${CONTRIB_SOURCE_DIR}")
    file(MAKE_DIRECTORY "${CONTRIB_SOURCE_DIR}")
    file(COPY "${pristine}/" DESTINATION "${CONTRIB_SOURCE_DIR}")
    file(REMOVE_RECURSE "${CONTRIB_STAGING_DIR}")
  elseif(GAMBIT_CONTRIB_IDENTITY_ACTION STREQUAL "RECORD")
    foreach(path IN LISTS CONTRIB_REQUIRED_FILES)
      if(NOT EXISTS "${path}" OR IS_DIRECTORY "${path}")
        message(FATAL_ERROR "Cannot record an incomplete contrib installation: ${path}")
      endif()
    endforeach()
    foreach(name IN LISTS CONTRIB_LIBRARY_NAMES)
      gambit_find_contrib_library(library "${name}" "${CONTRIB_LIBRARY_DIR}")
      if(NOT library)
        message(FATAL_ERROR "Cannot record a contrib installation missing library: ${name}")
      endif()
    endforeach()
    file(READ "${CONTRIB_IDENTITY_INPUT}" identity)
    gambit_contrib_write_if_changed("${CONTRIB_IDENTITY_RECORD}" "${identity}")
  else()
    message(FATAL_ERROR "Unknown contrib identity action: ${GAMBIT_CONTRIB_IDENTITY_ACTION}")
  endif()
endif()
