# Cache native compile/link checks by their effective inputs.  Keep expensive
# probes cached, but do not retain a PASS/FAIL after the selected inputs change.
include_guard(GLOBAL)

# Length-prefixed fields avoid collisions between values containing separators.
function(_gambit_check_field output key value)
  string(LENGTH "${key}" _key_length)
  string(LENGTH "${value}" _value_length)
  set(${output} "${${output}}${_key_length}:${key}${_value_length}:${value}" PARENT_SCOPE)
endfunction()

function(_gambit_check_file output path hash_contents)
  set(_identity "")
  _gambit_check_field(_identity path "${path}")
  if(EXISTS "${path}")
    get_filename_component(_real_path "${path}" REALPATH)
    file(TIMESTAMP "${path}" _modified "%Y-%m-%dT%H:%M:%S" UTC)
    _gambit_check_field(_identity real_path "${_real_path}")
    _gambit_check_field(_identity modified "${_modified}")
    if(IS_DIRECTORY "${path}")
      _gambit_check_field(_identity kind directory)
    else()
      file(SIZE "${path}" _size)
      _gambit_check_field(_identity size "${_size}")
      if(hash_contents)
        file(SHA256 "${path}" _content_hash)
        _gambit_check_field(_identity content "${_content_hash}")
      endif()
    endif()
  else()
    _gambit_check_field(_identity kind missing)
  endif()
  _gambit_check_field(${output} file "${_identity}")
  set(${output} "${${output}}" PARENT_SCOPE)
endfunction()

function(gambit_check_signature output language source)
  cmake_parse_arguments(PARSE_ARGV 3 _check "" "" "VARIABLES;HEADERS;FILES")
  if(_check_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Unknown validation-cache arguments: ${_check_UNPARSED_ARGUMENTS}")
  endif()
  set(_signature "GAMBIT native check inputs v1")
  _gambit_check_field(_signature language "${language}")
  _gambit_check_field(_signature source "${source}")
  set(_variables
    CMAKE_VERSION CMAKE_SYSTEM_NAME CMAKE_SYSTEM_VERSION CMAKE_SYSTEM_PROCESSOR
    CMAKE_GENERATOR CMAKE_GENERATOR_PLATFORM CMAKE_GENERATOR_TOOLSET
    CMAKE_BUILD_TYPE CMAKE_CONFIGURATION_TYPES CMAKE_TRY_COMPILE_CONFIGURATION
    CMAKE_TRY_COMPILE_TARGET_TYPE CMAKE_TRY_COMPILE_PLATFORM_VARIABLES
    CMAKE_TRY_COMPILE_NO_PLATFORM_VARIABLES
    CMAKE_${language}_COMPILER CMAKE_${language}_COMPILER_ID
    CMAKE_${language}_COMPILER_VERSION CMAKE_${language}_COMPILER_TARGET
    CMAKE_${language}_COMPILER_EXTERNAL_TOOLCHAIN CMAKE_${language}_COMPILER_ARG1
    CMAKE_${language}_COMPILER_LAUNCHER CMAKE_${language}_LINKER_LAUNCHER
    CMAKE_${language}_FLAGS
    CMAKE_${language}_STANDARD CMAKE_${language}_STANDARD_REQUIRED
    CMAKE_${language}_EXTENSIONS CMAKE_${language}_LINKER_FLAGS
    CMAKE_${language}_LINK_FLAGS
    CMAKE_EXE_LINKER_FLAGS
    CMAKE_LINKER CMAKE_LINKER_TYPE CMAKE_TOOLCHAIN_FILE
    CMAKE_SYSROOT CMAKE_SYSROOT_COMPILE CMAKE_SYSROOT_LINK
    CMAKE_OSX_SYSROOT CMAKE_OSX_DEPLOYMENT_TARGET CMAKE_OSX_ARCHITECTURES
    CMAKE_REQUIRED_FLAGS CMAKE_REQUIRED_DEFINITIONS CMAKE_REQUIRED_INCLUDES
    CMAKE_REQUIRED_LIBRARIES CMAKE_REQUIRED_LINK_OPTIONS
    CMAKE_REQUIRED_LINK_DIRECTORIES
    ${CMAKE_TRY_COMPILE_PLATFORM_VARIABLES} ${_check_VARIABLES})
  # try_compile may select a configuration independently of CMAKE_BUILD_TYPE.
  # Include custom configurations too, without assuming its default is Release.
  set(_configurations DEBUG RELEASE RELWITHDEBINFO MINSIZEREL
    ${CMAKE_CONFIGURATION_TYPES} ${CMAKE_BUILD_TYPE} ${CMAKE_TRY_COMPILE_CONFIGURATION})
  foreach(_configuration IN LISTS _configurations)
    string(TOUPPER "${_configuration}" _configuration)
    list(APPEND _variables CMAKE_${language}_FLAGS_${_configuration}
      CMAKE_${language}_LINK_FLAGS_${_configuration}
      CMAKE_EXE_LINKER_FLAGS_${_configuration})
  endforeach()
  list(REMOVE_DUPLICATES _variables)
  foreach(_variable IN LISTS _variables)
    if(DEFINED ${_variable})
      _gambit_check_field(_signature "${_variable}" "defined:${${_variable}}")
    else()
      _gambit_check_field(_signature "${_variable}" undefined)
    endif()
  endforeach()
  foreach(_environment PATH CPATH C_INCLUDE_PATH CPLUS_INCLUDE_PATH
      LIBRARY_PATH SDKROOT DEVELOPER_DIR)
    _gambit_check_field(_signature "env:${_environment}" "$ENV{${_environment}}")
  endforeach()

  # Small probe headers are hashed; large tool/library files use identity,
  # size and timestamp.  No recursive SDK or dependency-tree scan is performed.
  set(_files "${CMAKE_${language}_COMPILER}" "${CMAKE_LINKER}"
    "${CMAKE_SYSROOT}" "${CMAKE_SYSROOT_COMPILE}"
    "${CMAKE_SYSROOT_LINK}" "${CMAKE_OSX_SYSROOT}"
    ${CMAKE_REQUIRED_LIBRARIES} ${_check_FILES})
  list(REMOVE_DUPLICATES _files)
  foreach(_file IN LISTS _files)
    if(IS_ABSOLUTE "${_file}")
      _gambit_check_file(_signature "${_file}" FALSE)
    endif()
  endforeach()
  # The toolchain is small source input, so detect same-size edits too.
  if(IS_ABSOLUTE "${CMAKE_TOOLCHAIN_FILE}")
    _gambit_check_file(_signature "${CMAKE_TOOLCHAIN_FILE}" TRUE)
  endif()
  foreach(_include IN LISTS CMAKE_REQUIRED_INCLUDES)
    if(NOT _include STREQUAL "")
      foreach(_header IN LISTS _check_HEADERS)
        _gambit_check_file(_signature "${_include}/${_header}" TRUE)
      endforeach()
    endif()
  endforeach()
  string(SHA256 _signature "${_signature}")
  set(${output} "${_signature}" PARENT_SCOPE)
endfunction()

# A macro is required: native checks skip results defined in either the cache
# or the caller's normal variables.  Remove both in the exact probe scope.
macro(gambit_prepare_cached_check result language label source)
  gambit_check_signature(_gambit_check_signature "${language}" "${source}" ${ARGN})
  set(_gambit_check_key "GAMBIT_CHECK_CACHE_${result}_SIGNATURE")
  if(NOT DEFINED ${_gambit_check_key} OR
     NOT "${${_gambit_check_key}}" STREQUAL "${_gambit_check_signature}")
    message(STATUS "Validation: ${label} check inputs are new or changed")
    unset(${result} CACHE)
    unset(${result})
    set(${_gambit_check_key} "${_gambit_check_signature}" CACHE INTERNAL
      "Inputs to ${result}" FORCE)
  endif()
  unset(_gambit_check_signature)
  unset(_gambit_check_key)
endmacro()
