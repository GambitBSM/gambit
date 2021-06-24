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
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020 Nov
#
#************************************************


# Specify CCPForge credentials
set(CCPForge_user "gambit_user")
set(CCPForge_p1 "bsm")
set(CCPForge_p2 "or")
set(CCPForge_p3 "bust")

# Specify where all backend and scanner tarballs are to be stored
set(backend_download "${PROJECT_SOURCE_DIR}/Backends/downloaded")
set(scanner_download "${PROJECT_SOURCE_DIR}/ScannerBit/downloaded")

# Safer download function than what is in cmake (avoid buggy libcurl vs https issue)
set(DL_BACKEND "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${backend_download}" "${CMAKE_COMMAND}" "${CMAKE_DOWNLOAD_FLAGS}")
set(DL_SCANNER "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${scanner_download}" "${CMAKE_COMMAND}" "${CMAKE_DOWNLOAD_FLAGS}")
set(DL_CONTRIB "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${CMAKE_BUILD_DIR}" "${CMAKE_COMMAND}" "${CMAKE_DOWNLOAD_FLAGS}")

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

  # Make sense of multi-line responses given for the clean target
  string(REPLACE "|" "| ${MAKE_SERIAL}" updated_target ${target})
  string(FIND "${target}" "|" pipe_found)
  if (pipe_found STREQUAL "-1")
    set(updated_target "${MAKE_SERIAL} ${target}")
  endif()
  string(REGEX REPLACE " " ";" updated_target "${updated_target}")

  # Add extra targets needed for backend models
  if (${type} STREQUAL "backend model")

    set(pname "${package}_${model}_${ver}")
    add_dependencies(${pname} .${package}_${ver}_base)
    add_dependencies(${package}_all_models_${ver} ${pname})
    add_chained_external_clean(${pname} ${dir} "${updated_target}" .${package}_${ver}_base)
    add_dependencies(clean-backends clean-${pname})

  else()

    # Choose settings for extra targets needed for backend bases
    if (${type} MATCHES "^backend base")

      set(effective_type "backend")
      set(pname ".${package}_${ver}_base")
      #Add the all_models target
      add_custom_target(${package}_all_models_${ver})

    # Choose settings for extra targets needed for scanners and self-contained backends
    else()

      set(effective_type ${type})
      set(pname "${package}_${ver}")

    endif()

    # Add extra targets needed for backend bases, scanners and self-contained backends
    string(REGEX MATCH "zip|tar.gz|tgz" suffix "${dl}")
    if("${suffix}" STREQUAL "")
      string(REGEX REPLACE ".*\\." "" suffix ${dl})
    endif()
    set(short_dl "${${effective_type}_download}/${package}_${ver}.${suffix}")
    add_external_clean(${pname} ${dir} ${short_dl} "${updated_target}")
    add_dependencies(clean-${effective_type}s clean-${pname})
    add_dependencies(nuke-${effective_type}s nuke-${pname})

    if(${type} STREQUAL "backend base (functional alone)")
      # Add extra targets needed only for a backend base that is able to function as a backend in its own right
      # This is a bit sneaky; here we overload the use of set_as_default_version to make an alias package_ver to .package_ver_base
      set_as_default_version("backend" ${package}_${ver} "base")
    elseif(${type} STREQUAL "backend base (not functional alone)")
      # Add an extra target for a backend base unable to function without a backend model.  This is just a dummy target that throws an error.
      add_error_target(${package} ${ver})
      # Add additional clean and nuke aliases
      add_custom_target(clean-${package}_${ver} DEPENDS clean-${pname})
      add_custom_target(nuke-${package}_${ver} DEPENDS nuke-${pname})
    endif()

  endif()

  #Add extra targets common to everything.
  enable_auto_rebuild(${pname})
  set_target_properties(${pname} PROPERTIES EXCLUDE_FROM_ALL 1)
  set(rmstring "${CMAKE_BINARY_DIR}/${pname}-prefix/src/${pname}-stamp/${pname}-download")
  ExternalProject_Add_Step(${pname} verify
    COMMAND test -e ${rmstring}-failed && ${CMAKE_COMMAND} -E remove -f ${rmstring} ${rmstring}-failed || true
    DEPENDEES download
    DEPENDERS patch configure build)

endmacro()

# Function to check whether or not a given scanner or backend has been ditched
function(check_ditch_status name version dir)
  # Check first for optional argument
  foreach(arg0 ${ARGN})
    string(TOLOWER ${arg0} arg)
    if ((arg STREQUAL "mathematica") AND NOT HAVE_MATHEMATICA)
      set (itch "${itch}" "${name}_${version};")
    elseif ((arg STREQUAL "python") AND NOT HAVE_PYBIND11)
      set (itch "${itch}" "${name}_${version};")
    elseif ((arg STREQUAL "python2") AND (NOT PYTHON_VERSION_MAJOR EQUAL 2 OR NOT HAVE_PYBIND11))
      set (itch "${itch}" "${name}_${version};")
    elseif ((arg STREQUAL "python3") AND (NOT PYTHON_VERSION_MAJOR EQUAL 3 OR NOT HAVE_PYBIND11))
      set (itch "${itch}" "${name}_${version};")
    elseif ((arg STREQUAL "hepmc") AND EXCLUDE_HEPMC)
      set (itch "${itch}" "${name}_${version}")
    elseif ((arg STREQUAL "yoda") AND EXCLUDE_YODA)
      set (itch "${itch}" "${name}_${version}")
    elseif ((arg STREQUAL "sqlite3") AND NOT SQLITE3_FOUND)
      set (itch "${itch}" "${name}_${version}")
    endif()
  endforeach()
  foreach(ditch_command ${itch})
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "print(\"${name}_${version}\".lower().startswith(\"${ditch_command}\".lower()))"
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    RESULT_VARIABLE result
                    OUTPUT_VARIABLE output)
    if (output STREQUAL "True\n")
      if(NOT ditched_${name}_${ver})
        set(ditched_${name}_${version} TRUE)
        set(ditched_${name}_${version} TRUE PARENT_SCOPE)
        message("${BoldCyan} X Excluding ${name} ${version} from GAMBIT configuration.${ColourReset}")
      endif()
      # Remove the build and source dirs to prevent errors when building after later re-cmaking without ditching this component
      execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${name}_${version}-prefix)
      execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${dir})
    endif()
  endforeach()
endfunction()

# Add a new target that just prints a helpful error explaining that the target for a backend base is not activated.
macro(add_error_target name)
  if(${ARGC} GREATER 1)
    set(_ver "_${ARGV1}")
  else()
    set(_ver "")
  endif()
  add_custom_target(${name}${_ver}
    COMMAND ${CMAKE_COMMAND} -E echo
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "Sorry, the make target ${name}${_ver} does not actually exist, as the"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "base package of this backend cannot be used without a model-specific"
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "extension. Please build either:"
    COMMAND ${CMAKE_COMMAND} -E echo
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow " a. All model-specific extensions of ${name}${_ver}, by running"
    COMMAND ${CMAKE_COMMAND} -E echo
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow --bold "    make ${name}_all_models${_ver}"
    COMMAND ${CMAKE_COMMAND} -E echo
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow " b. A single model-specific extension of ${name}${_ver}, by running"
    COMMAND ${CMAKE_COMMAND} -E echo
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow --bold "    make ${name}_[model name]${_ver}"
    COMMAND ${CMAKE_COMMAND} -E echo
    COMMAND exit 1)
endmacro()

# Function to set up a new target with a generic name of a backend/scanner and associate it with the default version
function(set_as_default_version type name default)

  #Retrieve the model name if it is also passed
  if(${ARGC} GREATER 3)
    set(model ${ARGV3})
    set(target ${name}_${model})
  else()
    set(target ${name})
  endif()

  # Add clean targets for default version of hidden/unhidden target
  add_custom_target(clean-${target})
  if (TARGET clean-${target}_${default})
    add_dependencies(clean-${target} clean-${target}_${default})
  else()
    add_dependencies(clean-${target} clean-.${target}_${default})
  endif()

  # Add nuke or all_models target
  if (type STREQUAL "backend model")
    if (NOT TARGET ${name}_all_models)
      add_custom_target(${name}_all_models)
    endif()
    add_dependencies(${name}_all_models ${target})
    set(type "backend")
  else()
    add_custom_target(nuke-${target})
    if (TARGET nuke-${target}_${default})
      add_dependencies(nuke-${target} nuke-${target}_${default})
    else()
      add_dependencies(nuke-${target} nuke-.${target}_${default})
    endif()
  endif()

  # Add the actual default target, and add it to the backends or scanners target if relevant
  if (type STREQUAL "backend base (not functional alone)")
    add_error_target(${target})
  else()
    add_custom_target(${target})
    if (TARGET ${target}_${default})
      add_dependencies(${target} ${target}_${default})
    else()
      add_dependencies(${target} .${target}_${default})
    endif()
    if (type STREQUAL "backend base (functional alone)")
      add_dependencies(backends ${target})
    else()
      add_dependencies(${type}s ${target})
    endif()
  endif()

endfunction()

# Check whether or not Python modules required for backend builds are available
macro(check_python_modules name ver modules)
  set(_modules ${modules} ${ARGN})
  string (REPLACE "," ";" _modules "${_modules}")
  string (REPLACE " " "" _modules "${_modules}")
  foreach(module ${_modules})
    if (NOT DEFINED PY_${module}_FOUND)
      gambit_find_python_module(${module})
      if (NOT PY_${module}_FOUND)
        set(PY_${module}_FOUND FALSE)
      endif()
    endif()
    if (NOT PY_${module}_FOUND)
      set(modules_missing_${name}_${ver} "${modules_missing_${name}_${ver}},${module}" )
    endif()
  endforeach()
endmacro()

# Set up a mock external project that tells the user about missing Python modules and forces a rerun of cmake at next attempted build
macro(inform_of_missing_modules name ver missing_with_commas)
  string (REPLACE "," " " missing "${missing_with_commas}")
  set(package ${name}_${ver})
  set(rmstring "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}-configure")
  set(errmsg1 "Cannot make ${package} because you are missing Python module(s):${missing}")
  set(errmsg2 "Please install the missing package(s), e.g. with ")
  set(errmsg3 "  pip install --user${missing}")
  set(errmsg4 "and then rerun ")
  set(errmsg5 "  make ${package}")
  ExternalProject_Add(${package}
    DOWNLOAD_COMMAND ${CMAKE_COMMAND} -E make_directory ${package}-prefix/src/${package}
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo
              COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold ${errmsg1}
              COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold ${errmsg2}
              COMMAND ${CMAKE_COMMAND} -E echo
              COMMAND ${CMAKE_COMMAND} -E cmake_echo_color       --bold ${errmsg3}
              COMMAND ${CMAKE_COMMAND} -E echo
              COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold ${errmsg4}
              COMMAND ${CMAKE_COMMAND} -E echo
              COMMAND ${CMAKE_COMMAND} -E cmake_echo_color       --bold ${errmsg5}
              COMMAND ${CMAKE_COMMAND} -E echo
    BUILD_COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_SOURCE_DIR}/cmake/backends.cmake
    INSTALL_COMMAND ${CMAKE_COMMAND} -E remove ${rmstring}
  )
endmacro()

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
