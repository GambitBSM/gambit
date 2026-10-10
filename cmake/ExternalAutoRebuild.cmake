# Keep external build stamps when declared sources and products are unchanged.
# Author: Pengxuan Zhu, 2026 Oct
include_guard(GLOBAL)
set(_GAMBIT_EXTERNAL_REBUILD_SCRIPT
    "${CMAKE_CURRENT_LIST_DIR}/scripts/external_rebuild.py")

function(gambit_enable_external_auto_rebuild package)
  cmake_parse_arguments(REBUILD "" "" "REBUILD_INPUTS;REBUILD_DEPENDENCY_INPUTS;REBUILD_OUTPUTS;REBUILD_CONFIGURE_OUTPUTS" ${ARGN})
  if(NOT REBUILD_REBUILD_INPUTS)
    # Packages without an audited input/product list retain the existing policy.
    set(stamp "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
    add_custom_target(check-rebuild-${package}
      COMMAND "${CMAKE_COMMAND}" -E remove -f "${stamp}-build" VERBATIM)
  else()
    if(NOT REBUILD_REBUILD_OUTPUTS OR REBUILD_UNPARSED_ARGUMENTS)
      message(FATAL_ERROR "Incomplete automatic rebuild declaration for ${package}")
    endif()
    ExternalProject_Get_Property(${package} STAMP_DIR TMP_DIR)
    set(stamp "${STAMP_DIR}/${package}")
    # Include the actual EP commands and tool identities, rather than a preset
    # name. Changes to command-line flags must also invalidate the snapshot.
    set(configuration "GAMBIT external source state v1\n")
    foreach(step CONFIGURE BUILD INSTALL)
      get_property(command TARGET ${package} PROPERTY _EP_${step}_COMMAND)
      foreach(argument IN LISTS command)
        string(LENGTH "${argument}" length)
        string(APPEND configuration "${step}=${length}:${argument}\n")
      endforeach()
    endforeach()
    foreach(language C CXX Fortran)
      foreach(field COMPILER COMPILER_ID COMPILER_VERSION)
        string(APPEND configuration
          "${language}_${field}=${CMAKE_${language}_${field}}\n")
      endforeach()
      if(EXISTS "${CMAKE_${language}_COMPILER}")
        get_filename_component(compiler "${CMAKE_${language}_COMPILER}" REALPATH)
        file(TIMESTAMP "${compiler}" timestamp "%Y-%m-%dT%H:%M:%SZ" UTC)
        string(APPEND configuration "${language}_FILE=${compiler};${timestamp}\n")
      endif()
    endforeach()
    file(SHA256 "${_GAMBIT_EXTERNAL_REBUILD_SCRIPT}" script_hash)
    string(APPEND configuration "TRACKER=${script_hash}\n")
    string(SHA256 configuration "${configuration}")
    set(arguments --package "${package}" --stamp "${stamp}"
        --record "${TMP_DIR}/${package}-source-state.json"
        --source-root "${PROJECT_SOURCE_DIR}"
        --configuration "${configuration}")
    foreach(path IN LISTS REBUILD_REBUILD_INPUTS)
      list(APPEND arguments --input "${path}")
    endforeach()
    foreach(path IN LISTS REBUILD_REBUILD_DEPENDENCY_INPUTS)
      list(APPEND arguments --dependency-input "${path}")
    endforeach()
    foreach(path IN LISTS REBUILD_REBUILD_OUTPUTS)
      list(APPEND arguments --output "${path}")
    endforeach()
    foreach(path IN LISTS REBUILD_REBUILD_CONFIGURE_OUTPUTS)
      list(APPEND arguments --configure-output "${path}")
    endforeach()
    add_custom_target(check-rebuild-${package}
      COMMAND "${Python3_EXECUTABLE}" "${_GAMBIT_EXTERNAL_REBUILD_SCRIPT}"
              check ${arguments} VERBATIM)
    # Check after prerequisite installations have finished, including when
    # several external projects are requested together in a parallel build.
    get_property(dependencies TARGET ${package} PROPERTY _EP_DEPENDS)
    if(dependencies)
      add_dependencies(check-rebuild-${package} ${dependencies})
    endif()
    ExternalProject_Add_Step(${package} record_source_state
      COMMAND "${Python3_EXECUTABLE}" "${_GAMBIT_EXTERNAL_REBUILD_SCRIPT}"
              record ${arguments}
      DEPENDEES install
      DEPENDS "${_GAMBIT_EXTERNAL_REBUILD_SCRIPT}"
      COMMENT "Recording successful ${package} source state")
  endif()
  add_dependencies(${package} check-rebuild-${package})
endfunction()
