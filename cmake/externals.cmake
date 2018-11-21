# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration scripts for obtaining,
#  configuring, compiling and installing
#  'extra' non-GAMBIT packages.
#
#  Note that this is not necessarily the canonical
#  way to manage the compilation of all backends,
#  and GAMBIT support for backend compilation is
#  minimal, even with this method -- so please
#  contact the authors of the respective codes
#  if they won't compile!
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#  \date 2015 May
#
#  \author Ben Farmer
#          (b.farmer@imperial.ac.uk)
#  \date 2018 Oct
#
#************************************************


# Specify the location of unreleased codes in the gambit_internal repository.
set(GAMBIT_INTERNAL "${PROJECT_SOURCE_DIR}/../gambit_internal/unreleased")

# Specify CCPForge credentials
set(CCPForge_user "gambit_user")
set(CCPForge_p1 "bsm")
set(CCPForge_p2 "or")
set(CCPForge_p3 "bust")

# Specify the warning to give when trying to compile unreleased codes.
set(private_code_warning "       Retrieving unreleased code from GAMBIT Collaboration private repository. This will fail if you don't have the repository.")
set(private_code_warning1 "       Retrieving unreleased code from GAMBIT Collaboration private repository.")
if(NOT EXISTS ${GAMBIT_INTERNAL})
  set(private_code_warning2 "       The repository was not found by cmake, so this will probably fail!")
endif()

# Specify where all backend and scanner tarballs are to be stored
set(backend_download "${PROJECT_SOURCE_DIR}/Backends/downloaded")
set(scanner_download "${PROJECT_SOURCE_DIR}/ScannerBit/downloaded")

# Safer download function than what is in cmake (avoid buggy libcurl vs https issue)
set(DL_BACKEND "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${backend_download}" "${CMAKE_COMMAND}")
set(DL_SCANNER "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${scanner_download}" "${CMAKE_COMMAND}")

# Define the newline strings to use for OSX-safe substitution.
set(nl "___totally_unlikely_to_occur_naturally___")
set(true_nl \"\\n\")

# Define the module location switch differently depending on compiler
if("${CMAKE_Fortran_COMPILER_ID}" STREQUAL "Intel")
  set(FMODULE "module")
elseif("${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU")
  set(FMODULE "J")
endif()

# Arrange make backends command (will be filled in from backends.cmake)
if(EXISTS "${PROJECT_SOURCE_DIR}/Backends/")
  add_custom_target(backends)
endif()

# Arrange make scanners command (will be filled in from scanners.cmake)
if(EXISTS "${PROJECT_SOURCE_DIR}/ScannerBit/")
  add_custom_target(scanners)
endif()

# Add get-pippi target
set(name "pippi")
set(dir "${CMAKE_SOURCE_DIR}/${name}")
ExternalProject_Add(get-${name}
  GIT_REPOSITORY https://github.com/patscott/pippi.git
  SOURCE_DIR ${dir}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
set(rmstring "${CMAKE_BINARY_DIR}/get-${name}-prefix/src/get-${name}-stamp/get-${name}")
add_custom_target(nuke-pippi COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-download ${rmstring}-download-failed ${rmstring}-mkdir ${rmstring}-patch ${rmstring}-update ${rmstring}-gitclone-lastrun.txt || true
                             COMMAND ${CMAKE_COMMAND} -E remove_directory ${dir} || true)
add_dependencies(nuke-all nuke-pippi)
set_target_properties(get-pippi PROPERTIES EXCLUDE_FROM_ALL 1)

# Macro to clear the build stamp manually for an external project
macro(enable_auto_rebuild package)
  set(rmstring "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}-build")
  add_custom_target(check-rebuild-${package} ${CMAKE_COMMAND} -E remove -f ${rmstring})
  add_dependencies(${package} check-rebuild-${package})
endmacro()

# Macro to add all additional targets for a new backend or scanner
macro(add_extra_targets type package ver dir dl target)
  string(REPLACE "|" "| ${CMAKE_MAKE_PROGRAM}" updated_target ${target})
  string(FIND "${target}" "|" pipe_found)
  if (pipe_found STREQUAL "-1")
    set(updated_target "${CMAKE_MAKE_PROGRAM} ${target}")
  endif()
  string(REGEX REPLACE " " ";" updated_target "${updated_target}")
  if (${type} STREQUAL "backend model")
    set(pname "${package}_${model}_${ver}")
    add_dependencies(${pname} ${package}_${ver})
    add_chained_external_clean(${pname} ${dir} "${updated_target}" ${package}_${ver})
    add_dependencies(clean-backends clean-${pname})
  else()
    set(pname "${package}_${ver}")
    string(REGEX REPLACE ".*/" "${${type}_download}/" short_dl "${dl}")
    add_external_clean(${package}_${ver} ${dir} ${short_dl} "${updated_target}")
    add_dependencies(clean-${type}s clean-${pname})
    add_dependencies(nuke-${type}s nuke-${pname})
  endif()
  enable_auto_rebuild(${pname})
  set_target_properties(${pname} PROPERTIES EXCLUDE_FROM_ALL 1)
  set(rmstring "${CMAKE_BINARY_DIR}/${pname}-prefix/src/${pname}-stamp/${pname}-download")
  ExternalProject_Add_Step(${pname} verify
    COMMAND test -e ${rmstring}-failed && ${CMAKE_COMMAND} -E remove -f ${rmstring} ${rmstring}-failed || true
    DEPENDEES download
    DEPENDERS patch configure build)
endmacro()

# Function to check whether or not a given scanner or backend has been ditched
function(check_ditch_status name version)
  # Check first for optional argument for Mathematica backends
  if ((ARGN STREQUAL "Mathematica" OR ARGN STREQUAL "mathematica") AND NOT HAVE_MATHEMATICA)
    set (itch "${itch}" "${name}_${version}")
  endif()
  foreach(ditch_command ${itch})
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "print(\"${name}_${version}\".startswith(\"${ditch_command}\"))"
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output)
    if (output STREQUAL "True\n")
      if(NOT ditched_${name}_${ver})
        set(ditched_${name}_${version} TRUE)
        set(ditched_${name}_${version} TRUE PARENT_SCOPE)
        message("${BoldCyan} X Excluding ${name} ${version} from GAMBIT configuration.${ColourReset}")
      endif()
    endif()
  endforeach()
endfunction()

# Function to set up a new target with a generic name of a backend/scanner and associate it with the default version
function(set_as_default_version type name default)
  add_custom_target(${name})
  add_dependencies(${name} ${name}_${default})
  add_custom_target(clean-${name})
  add_dependencies(clean-${name} clean-${name}_${default})
  if (type STREQUAL "backend model")
    set(type "backend")
  else()
    add_custom_target(nuke-${name})
    add_dependencies(nuke-${name} nuke-${name}_${default})
  endif()
  add_dependencies(${type}s ${name})
endfunction()

if(EXISTS "${PROJECT_SOURCE_DIR}/Backends/")
  include(cmake/backends.cmake)
endif()
if(EXISTS "${PROJECT_SOURCE_DIR}/ScannerBit/")
  include(cmake/scanners.cmake)
endif()

# Print outcomes of BOSSing efforts
if(NOT needs_BOSSing STREQUAL "")
  message("${Yellow}-- BOSS step successfully generated for the following cmake targets: ${needs_BOSSing} ${ColourReset}")
endif()
if(NOT needs_BOSSing_failed STREQUAL "")
  message("${Yellow}-- Failed to generate BOSS step for the following cmake targets: ${needs_BOSSing_failed} ${ColourReset}")
endif()
