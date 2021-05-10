# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Helpful CMake utility macros and functions for
#  GAMBIT.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#        2015 Feb
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#
#  \author Ben Farmer
#          (benjamin.farmer@fysik.su.se)
#  \date 2016 Jan
#
#  \author Tomas Gonzalo
#          (t.e.gonzalo@fys.uio.no)
#  \date 2016 Sep
#
#  \author Will Handley
#          (wh260@cam.ac.uk)
#  \date 2018 Dec
#
#************************************************

include(CMakeParseArguments)
include(ExternalProject)

# defining some colors
string(ASCII 27 Esc)
set(ColourReset "${Esc}[m")
set(ColourBold  "${Esc}[1m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")
set(Magenta     "${Esc}[35m")
set(Cyan        "${Esc}[36m")
set(White       "${Esc}[37m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")
set(BoldBlue    "${Esc}[1;34m")
set(BoldMagenta "${Esc}[1;35m")
set(BoldCyan    "${Esc}[1;36m")
set(BoldWhite   "${Esc}[1;37m")

# Define the sed command to use differently for OSX and linux
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(dashi "-i ''")
else()
  set(dashi "-i")
endif()

#Crash function for failed execute_processes
function(check_result result command)
  if(NOT ${result} STREQUAL "0")
    message(FATAL_ERROR "${BoldRed}Cmake failed because a GAMBIT python script failed.  Culprit: ${command}${ColourReset}")
  endif()
endfunction()

#Check if a string starts with a give substring
function(starts_with str search)
  string(FIND "${str}" "${search}" out)
  if("${out}" EQUAL 0)
    return(true)
  endif()
  return(false)
endfunction()

#Macro to retrieve GAMBIT modules
macro(retrieve_bits bits root excludes quiet)

  set(${bits} "")
  file(GLOB children RELATIVE ${root} ${root}/*Bit*)

  foreach(child ${children})
    file(GLOB_RECURSE src RELATIVE ${root}/${child} ${root}/${child}/src/*.c
                                                    ${root}/${child}/src/*.cc
                                                    ${root}/${child}/src/*.cpp)
    file(GLOB_RECURSE hdr RELATIVE ${root}/${child} ${root}/${child}/include/*.h
                                                    ${root}/${child}/include/*.hh
                                                    ${root}/${child}/include/*.hpp)
    string(FIND ${child} ".dSYM" FOUND_DSYM)
    if(IS_DIRECTORY ${root}/${child} AND (src OR hdr) AND ${FOUND_DSYM} EQUAL -1)

      # Work out if this Bit should be excluded or not.  Never exclude ScannerBit.
      set(excluded "NO")
      if(NOT ${child} STREQUAL "ScannerBit")
        foreach(x ${excludes})
          string(FIND ${child} ${x} location)
          if(${location} EQUAL 0)
            set(excluded "YES")
          endif()
        endforeach()
      endif()

      # Exclude or add this bit.
      if(${excluded})
        if(NOT ${quiet} STREQUAL "Quiet")
          message("${BoldCyan} X Excluding ${child} from GAMBIT configuration.${ColourReset}")
        endif()
      else()
        list(APPEND ${bits} ${child})
      endif()

    endif()
  endforeach()

endmacro()

# Specify native make command to be put into external build steps (for correct usage of gmake jobserver)
if(CMAKE_MAKE_PROGRAM MATCHES "make$")
  set(MAKE_SERIAL   $(MAKE) -j1)
  set(MAKE_PARALLEL $(MAKE))
else()
  set(MAKE_SERIAL   "${CMAKE_MAKE_PROGRAM}")
  set(MAKE_PARALLEL "${CMAKE_MAKE_PROGRAM}")
endif()

# Arrange clean commands
include(cmake/cleaning.cmake)

# Macro to write some shell commands to clean an external code.  Adds clean-[package] and nuke-[package]
macro(add_external_clean package dir dl target)
  set(rmstring1 "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
  set(rmstring2 "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-build")
  string(REPLACE "." "_" safe_package ${package})
  set(reset_file "${CMAKE_BINARY_DIR}/BOSS_reset_info/reset_info.${safe_package}.boss")
  add_custom_target(clean-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring1}-BOSS ${rmstring1}-configure ${rmstring1}-build ${rmstring1}-install ${rmstring1}-done
                                     COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && (${target})) || true
                                     COMMAND [ -e ${reset_file} ] && ${PYTHON_EXECUTABLE} ${BOSS_dir}/boss.py -r ${reset_file} || true)
  add_custom_target(nuke-${package} DEPENDS clean-${package}
                                    COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring1}-download ${rmstring1}-download-failed ${rmstring1}-mkdir ${rmstring1}-patch ${rmstring1}-update ${rmstring1}-gitclone-lastrun.txt ${dl} || true
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory ${dir} || true
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory ${rmstring2} || true)
endmacro()

# Macro to write some shell commands to clean an external chained code.  Adds clean-[package] and nuke-[package]
macro(add_chained_external_clean package dir target dependee)
  set(rmstring "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
  add_custom_target(clean-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-configure ${rmstring}-build ${rmstring}-install ${rmstring}-done
                                     COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && (${target})) || true)
  add_custom_target(chained-nuke-${package} DEPENDS clean-${package}
                                    COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-download ${rmstring}-mkdir ${rmstring}-patch ${rmstring}-update ${rmstring}-gitclone-lastrun.txt || true)
  add_dependencies(clean-${dependee} clean-${package})
  add_dependencies(nuke-${dependee} chained-nuke-${package})
endmacro()

# Function to add GAMBIT directory if and only if it exists
function(add_subdirectory_if_present dir)
  if(EXISTS "${PROJECT_SOURCE_DIR}/${dir}")
    add_subdirectory(${dir})
  endif()
endfunction()

# Function to make symbols visible for a code component
function(make_symbols_visible lib)
  if(${CMAKE_MAJOR_VERSION} MATCHES "2")
    set_target_properties(${lib} PROPERTIES COMPILE_OPTIONS "-fvisibility=default")
  else()
    set_target_properties(${lib} PROPERTIES CXX_VISIBILITY_PRESET default)
  endif()
endfunction()

# Function to reset the install_name of a library compiled in an external project on OSX
function(add_install_name_tool_step proj path lib)
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ExternalProject_Add_Step(${proj}
      change-install-name-${lib}
      COMMENT "Fixing install name for ${lib}"
      COMMAND install_name_tool -id "@rpath/${lib}" ${path}/${lib}
      DEPENDEES install
    )
  endif()
endfunction()


# Function to add static GAMBIT library
function(add_gambit_library libraryname)
  cmake_parse_arguments(ARG "VISIBLE" "OPTION" "SOURCES;HEADERS" ${ARGN})

  add_library(${libraryname} ${ARG_OPTION} ${ARG_SOURCES} ${ARG_HEADERS})
  add_dependencies(${libraryname} model_harvest)
  add_dependencies(${libraryname} backend_harvest)
  add_dependencies(${libraryname} printer_harvest)
  add_dependencies(${libraryname} module_harvest)
  add_dependencies(${libraryname} yaml-cpp)

  if(${CMAKE_VERSION} VERSION_GREATER 2.8.10)
    foreach (dir ${GAMBIT_INCDIRS})
      target_include_directories(${libraryname} PUBLIC ${dir})
    endforeach()
  else()
    foreach (dir ${GAMBIT_INCDIRS})
      include_directories(${dir})
    endforeach()
  endif()

  if(${ARG_OPTION} STREQUAL SHARED AND APPLE)
    set_property(TARGET ${libraryname} PROPERTY SUFFIX .so)
  endif()

  # Reveal symbols if requested
  if(${ARG_VISIBLE})
    make_symbols_visible(${libraryname})
  endif()

endfunction()

# Macro to strip a library out of a set of full paths
macro(strip_library KEY LIBRARIES)
  set(TEMP "${${LIBRARIES}}")
  set(${LIBRARIES} "")
  foreach(lib ${TEMP})
    if ("${lib}" STREQUAL "debug"   OR
        "${lib}" STREQUAL "general" OR
        "${lib}" STREQUAL "optimized")
      set(LIB_TYPE_SPECIFIER "${lib}")
    else()
      string(FIND "${lib}" "/${KEY}." FOUND_KEY1)
      string(FIND "${lib}" "/lib${KEY}." FOUND_KEY2)
      if (${FOUND_KEY1} EQUAL -1 AND ${FOUND_KEY2} EQUAL -1)
        if (LIB_TYPE_SPECIFIER)
          list(APPEND ${LIBRARIES} ${LIB_TYPE_SPECIFIER})
        endif()
        list(APPEND ${LIBRARIES} ${lib})
      endif()
      set(LIB_TYPE_SPECIFIER "")
  endif()
  endforeach()
  set(TEMP "")
  set(FOUND_KEY1 "")
  set(FOUND_KEY2 "")
endmacro()

# Function to add a GAMBIT custom command and target
macro(add_gambit_custom target filename HARVESTER DEPS)
  set(ditch_string "")
  if (NOT "${ARGN}" STREQUAL "")
    set(ditch_string "-x __not_a_real_name__,${ARGN}")
  endif()
  add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/${filename}
                     COMMAND ${PYTHON_EXECUTABLE} ${${HARVESTER}} ${ditch_string}
                     COMMAND touch ${CMAKE_BINARY_DIR}/${filename}
                     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                     DEPENDS ${${HARVESTER}}
                             ${HARVEST_TOOLS}
                             ${PROJECT_BINARY_DIR}/CMakeCache.txt
                             ${${DEPS}})
  add_custom_target(${target} DEPENDS ${CMAKE_BINARY_DIR}/${filename})
endmacro()

# Function to remove specific GAMBIT build files
function(remove_build_files)
  foreach (f ${ARGN})
    if (EXISTS "${CMAKE_BINARY_DIR}/${f}")
      file(REMOVE "${CMAKE_BINARY_DIR}/${f}")
    endif()
  endforeach()
endfunction()

# Macro to set up internal variables for contrib version of pybind11
macro(use_contributed_pybind11)
  set(pybind11_FOUND TRUE)
  set(pybind11_DIR "${pybind11_CONTRIB_DIR}")
  set(pybind11_VERSION "${PREFERRED_pybind11_VERSION}")
  message("${BoldYellow}   Found pybind11 ${pybind11_VERSION} at ${pybind11_DIR}.${ColourReset}")
  add_subdirectory("${pybind11_DIR}")
  include_directories("${PYBIND11_INCLUDE_DIR}")
  add_custom_target(nuke-pybind11 COMMAND ${CMAKE_COMMAND} -E remove_directory "${pybind11_DIR}")
  add_dependencies(nuke-contrib nuke-pybind11)
endmacro()

# Function to add GAMBIT executable
function(add_gambit_executable executablename LIBRARIES)
  cmake_parse_arguments(ARG "" "" "SOURCES;HEADERS;" ${ARGN})

  add_executable(${executablename} ${ARG_SOURCES} ${ARG_HEADERS})
  set_target_properties(${executablename} PROPERTIES EXCLUDE_FROM_ALL 1)

  if(${CMAKE_VERSION} VERSION_GREATER 2.8.10)
    foreach (dir ${GAMBIT_INCDIRS})
      target_include_directories(${executablename} PUBLIC ${dir})
    endforeach()
  else()
    foreach (dir ${GAMBIT_INCDIRS})
      include_directories(${dir})
    endforeach()
  endif()

  if(MPI_CXX_FOUND)
    set(LIBRARIES ${LIBRARIES} ${MPI_CXX_LIBRARIES})
    if(MPI_CXX_LINK_FLAGS)
      set_target_properties(${executablename} PROPERTIES LINK_FLAGS ${MPI_CXX_LINK_FLAGS})
    endif()
  endif()
  if(MPI_C_FOUND)
    set(LIBRARIES ${LIBRARIES} ${MPI_C_LIBRARIES})
    if(MPI_C_LINK_FLAGS)
      set_target_properties(${executablename} PROPERTIES LINK_FLAGS ${MPI_C_LINK_FLAGS})
    endif()
  endif()
  if(MPI_Fortran_FOUND)
    set(LIBRARIES ${LIBRARIES} ${MPI_Fortran_LIBRARIES})
    if(MPI_Fortran_LINK_FLAGS)
        set_target_properties(${executablename} PROPERTIES LINK_FLAGS ${MPI_Fortran_LINK_FLAGS})
    endif()
  endif()
  if (LIBDL_FOUND)
    set(LIBRARIES ${LIBRARIES} ${LIBDL_LIBRARY})
  endif()
  if (Boost_FOUND)
    set(LIBRARIES ${LIBRARIES} ${Boost_LIBRARIES})
  endif()
  if (GSL_FOUND)
    if(HDF5_FOUND AND "${USE_MATH_LIBRARY_CHOSEN_BY}" STREQUAL "HDF5")
      strip_library(m GSL_LIBRARIES)
    endif()
    set(LIBRARIES ${LIBRARIES} ${GSL_LIBRARIES})
  endif()
  if(HDF5_FOUND)
    if(GSL_FOUND AND "${USE_MATH_LIBRARY_CHOSEN_BY}" STREQUAL "GSL")
      strip_library(m HDF5_LIBRARIES)
    endif()
    set(LIBRARIES ${LIBRARIES} ${HDF5_LIBRARIES})
  endif()
  if(Mathematica_FOUND AND Mathematica_WSTP_FOUND)
    set(LIBRARIES ${LIBRARIES} ${Mathematica_WSTP_LIBRARIES})
  endif()
  if(pybind11_FOUND)
    set(LIBRARIES ${LIBRARIES} ${PYTHON_LIBRARIES})
  endif()
  if(SQLite3_FOUND)
      set(LIBRARIES ${LIBRARIES} ${SQLite3_LIBRARIES})
  endif()

  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(${executablename} PRIVATE ${gambit_preload_LDFLAGS} ${LIBRARIES} yaml-cpp)
  else()
    target_link_libraries(${executablename} PRIVATE ${LIBRARIES} yaml-cpp ${gambit_preload_LDFLAGS})
  endif()

  add_dependencies(${executablename} mkpath gambit_preload)

  #For checking if all the needed libs are present.  Never add them manually with -lsomelib!!
  if(VERBOSE)
    message(STATUS ${LIBRARIES})
  endif()

endfunction()

# Standalone harvester script
set(STANDALONE_FACILITATOR ${PROJECT_SOURCE_DIR}/Elements/scripts/standalone_facilitator.py)

# Function to add a standalone executable
function(add_standalone executablename)
  cmake_parse_arguments(ARG "" "" "SOURCES;HEADERS;LIBRARIES;MODULES" ${ARGN})

  # Iterate over modules, checking if the neccessary ones are present, and adding them to the target objects if so.
  set(standalone_permitted 1)
  foreach(module ${ARG_MODULES})
    if(standalone_permitted AND EXISTS "${PROJECT_SOURCE_DIR}/${module}/" AND (";${GAMBIT_BITS};" MATCHES ";${module};"))
      if(COMMA_SEPARATED_MODULES)
        set(COMMA_SEPARATED_MODULES "${COMMA_SEPARATED_MODULES},${module}")
        set(STANDALONE_OBJECTS ${STANDALONE_OBJECTS} $<TARGET_OBJECTS:${module}>)
      else()
        set(COMMA_SEPARATED_MODULES "${module}")
        set(STANDALONE_OBJECTS $<TARGET_OBJECTS:${module}>)
        set(first_module ${module})
      endif()
      if(module STREQUAL "SpecBit")
        set(USES_SPECBIT TRUE)
      endif()
      if(module STREQUAL "ColliderBit")
        set(USES_COLLIDERBIT TRUE)
      endif()
    else()
      set(standalone_permitted 0)
    endif()
  endforeach()

  # Add the standalone only if the required modules are all present
  if(standalone_permitted)

    # Iterate over sources and add leading source path
    set(STANDALONE_FUNCTORS "${PROJECT_SOURCE_DIR}/${first_module}/examples/functors_for_${executablename}.cpp")
    foreach(source_file ${ARG_SOURCES})
      list(APPEND STANDALONE_SOURCES ${PROJECT_SOURCE_DIR}/${source_file})
    endforeach()
    list(APPEND STANDALONE_SOURCES ${STANDALONE_FUNCTORS})

    # Set up the target to call the facilitator script to make the functors source file for this standalone.
    add_custom_command(OUTPUT ${STANDALONE_FUNCTORS}
                       COMMAND ${PYTHON_EXECUTABLE} ${STANDALONE_FACILITATOR} ${executablename} -m __not_a_real_name__,${COMMA_SEPARATED_MODULES}
                       COMMAND touch ${STANDALONE_FUNCTORS}
                       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                       DEPENDS modules_harvested
                               ${STANDALONE_FACILITATOR}
                               ${HARVEST_TOOLS}
                               ${PROJECT_BINARY_DIR}/CMakeCache.txt)

    # Add linking flags for ROOT, RestFrames and/or HepMC if required.
    if (USES_COLLIDERBIT)
      if (NOT EXCLUDE_ROOT)
        set(ARG_LIBRARIES ${ARG_LIBRARIES} ${ROOT_LIBRARIES})
        if (NOT EXCLUDE_RESTFRAMES)
          set(ARG_LIBRARIES ${ARG_LIBRARIES} ${RESTFRAMES_LDFLAGS})
        endif()
      endif()
      if (NOT EXCLUDE_HEPMC)
        set(ARG_LIBRARIES ${ARG_LIBRARIES} ${HEPMC_LDFLAGS})
      endif()
    endif()

    # Do ad hoc checks for stuff that will eventually be BOSSed and removed from here.
    if (USES_SPECBIT AND NOT EXCLUDE_FLEXIBLESUSY)
      set(ARG_LIBRARIES ${ARG_LIBRARIES} ${flexiblesusy_LDFLAGS})
    endif()

    add_gambit_executable(${executablename} "${ARG_LIBRARIES}"
                          SOURCES ${STANDALONE_SOURCES}
                                  ${STANDALONE_OBJECTS}
                                  ${GAMBIT_ALL_COMMON_OBJECTS}
                          HEADERS ${ARG_HEADERS})

    # Add each of the declared dependencies
    foreach(dep ${ARG_DEPENDENCIES})
      add_dependencies(${executablename} ${dep})
    endforeach()

    # Add the new executable to the standalones target
    add_dependencies(standalones ${executablename})

  endif()

endfunction()


# Function to retrieve version number from git
macro(get_version_from_git major minor revision patch full)

  set(${major} "")
  set(${minor} "")
  set(${revision} "")
  set(${patch} "")
  set(${full} "")

  execute_process(COMMAND git describe --tags --abbrev=0 OUTPUT_VARIABLE ${full})

  string(REGEX MATCH "v([0-9]*)\\." ${major} "${${full}}")
  if ("${${major}}" STREQUAL "")
    string(REGEX MATCH "^([0-9]*)\\." ${major} "${${full}}")
    string(REGEX REPLACE "^([0-9]*)\\." "\\1" ${major} "${${major}}")
  else()
    string(REGEX REPLACE "v([0-9]*)\\." "\\1" ${major} "${${major}}")
  endif()

  string(REGEX MATCH "\\.([0-9]*)\\." ${minor} "${${full}}")
  if ("${${minor}}" STREQUAL "")
    string(REGEX MATCH "\\.([0-9]*)" ${minor} "${${full}}")
    string(REGEX REPLACE "\\.([0-9]*)" "\\1" ${minor} "${${minor}}")
    set(${revision} "0")
  else()
    string(REGEX REPLACE "\\.([0-9]*)\\." "\\1" ${minor} "${${minor}}")
    string(REGEX MATCH "\\.([0-9]*)-" ${revision} "${${full}}")
    if ("${${revision}}" STREQUAL "")
      string(REGEX MATCH "\\.([0-9]*)\n" ${revision} "${${full}}")
      string(REGEX REPLACE "\\.([0-9]*)\n" "\\1" ${revision} "${${revision}}")
    else()
      string(REGEX REPLACE "\\.([0-9]*)-" "\\1" ${revision} "${${revision}}")
    endif()
  endif()
  string(REGEX MATCH "-(.*)\n" ${patch} "${${full}}")
  string(REGEX REPLACE "-(.*)\n" "\\1" ${patch} "${${patch}}")

  if ("${${patch}}" STREQUAL "")
    set(${full} "${${major}}.${${minor}}.${${revision}}")
  else()
    set(${full} "${${major}}.${${minor}}.${${revision}}-${${patch}}")
  endif()

endmacro()


# Function to add all standalone tarballs as targets
function(add_standalone_tarballs modules version)

  add_custom_target(standalone_tarballs)

  file(WRITE "${PROJECT_SOURCE_DIR}/cmake/tarball_info.cmake"
   "#*** GAMBIT ***********************\n"
   "# This file automatically generated \n"
   "# by utlities.cmake. Do not modify. \n"
   "#**********************************\n\n"
   "set(GAMBIT_VERSION_MAJOR ${GAMBIT_VERSION_MAJOR})\n"
   "set(GAMBIT_VERSION_MINOR ${GAMBIT_VERSION_MINOR})\n"
   "set(GAMBIT_VERSION_REVISION ${GAMBIT_VERSION_REVISION})\n"
   "set(GAMBIT_VERSION_PATCH ${GAMBIT_VERSION_PATCH})\n"
   "set(GAMBIT_VERSION_FULL ${GAMBIT_VERSION_FULL})\n")

  foreach(module ${modules})

    set(dirname "${module}_${version}")

    if ("${module}" STREQUAL "ScannerBit")
      add_custom_target(${module}-${version}.tar COMMAND ${CMAKE_COMMAND} -E remove_directory ${dirname}
                                      COMMAND ${CMAKE_COMMAND} -E make_directory ${dirname}
                                      COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/CMakeLists.txt ${dirname}/
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/${module} ${dirname}/${module}
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Logs ${dirname}/Logs
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Utils ${dirname}/Utils
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Printers ${dirname}/Printers
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/cmake ${dirname}/cmake
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/config ${dirname}/config
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/contrib ${dirname}/contrib
                                      COMMAND ${CMAKE_COMMAND} -E remove -f ${module}-${version}.tar
                                      COMMAND ${CMAKE_COMMAND} -E tar c ${module}-${version}.tar ${dirname})
    else()
      add_custom_target(${module}-${version}.tar COMMAND ${CMAKE_COMMAND} -E remove_directory ${dirname}
                                      COMMAND ${CMAKE_COMMAND} -E make_directory ${dirname}
                                      COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/CMakeLists.txt ${dirname}/
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/${module} ${dirname}/${module}
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Logs ${dirname}/Logs
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Utils ${dirname}/Utils
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Models ${dirname}/Models
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Elements ${dirname}/Elements
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Backends ${dirname}/Backends
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/cmake ${dirname}/cmake
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/config ${dirname}/config
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/contrib ${dirname}/contrib
                                      COMMAND ${CMAKE_COMMAND} -E remove -f ${module}-${version}.tar
                                      COMMAND ${CMAKE_COMMAND} -E tar c ${module}-${version}.tar ${dirname})
    endif()

    add_dependencies(${module}-${version}.tar nuke-all)
    add_dependencies(standalone_tarballs ${module}-${version}.tar)

  endforeach()

  # Add a special ad-hoc command to make a tarball containing SpecBit, DecayBit and PrecisionBit
  set(dirname "3Bit_${version}")
  add_custom_target(3Bit-${version}.tar COMMAND ${CMAKE_COMMAND} -E remove_directory ${dirname}
                             COMMAND ${CMAKE_COMMAND} -E make_directory ${dirname}
                             COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/CMakeLists.txt ${dirname}/
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/SpecBit ${dirname}/SpecBit
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/DecayBit ${dirname}/DecayBit
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/PrecisionBit ${dirname}/PrecisionBit
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Logs ${dirname}/Logs
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Utils ${dirname}/Utils
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Models ${dirname}/Models
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Elements ${dirname}/Elements
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Backends ${dirname}/Backends
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/cmake ${dirname}/cmake
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/config ${dirname}/config
                             COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/contrib ${dirname}/contrib
                             COMMAND ${CMAKE_COMMAND} -E remove -f 3Bit-${version}.tar
                             COMMAND ${CMAKE_COMMAND} -E tar c 3Bit-${version}.tar ${dirname})
  add_dependencies(3Bit-${version}.tar nuke-all)
  add_dependencies(standalone_tarballs 3Bit-${version}.tar)

endfunction()


# Simple function to find specific Python modules
macro(gambit_find_python_module module)
  execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import ${module}" RESULT_VARIABLE return_value ERROR_QUIET)
  if (NOT return_value)
    message(STATUS "Found Python module ${module}.")
    set(PY_${module}_FOUND TRUE)
  else()
    if(${ARGC} GREATER 1)
      if (${ARGV1} STREQUAL "REQUIRED")
        message(FATAL_ERROR "-- FAILED to find Python module ${module}.")
      else()
        message(FATAL_ERROR "-- Unrecognised second argument to gambit_find_python_module: ${ARGV1}.")
      endif()
    endif()
    message(STATUS "FAILED to find Python module ${module}.")
  endif()
endmacro()

# Macro for BOSSing a backend
set(BOSS_dir "${PROJECT_SOURCE_DIR}/Backends/scripts/BOSS")
set(needs_BOSSing "")
set(needs_BOSSing_failed "")

macro(BOSS_backend name backend_version)

  # Replace "." by "_" in the backend version number
  string(REPLACE "." "_" backend_version_safe ${backend_version})

  # Construct path to the config file expected by BOSS
  set(config_file_path "${BOSS_dir}/configs/${name}_${backend_version_safe}.py")

  # Only add BOSS step to the build process if the config file exists
  if(NOT EXISTS ${config_file_path})
    message("${BoldRed}-- The config file ${config_file_path} required ")
    message("   to BOSS the backend ${name} ${backend_version} was not found. This backend will not be BOSSed. ${ColourReset}")
    list(APPEND needs_BOSSing_failed ${name}_${ver})
  else()
    list(APPEND needs_BOSSing ${name}_${ver})
    file(READ "${config_file_path}" conf_file)
    string(REGEX MATCH "gambit_backend_name[ \t\n]*=[ \t\n]*'\([^\n]+\)'" dummy "${conf_file}")
    set(name_in_frontend "${CMAKE_MATCH_1}")

    set(BOSS_includes_Boost "")
    if (NOT ${Boost_INCLUDE_DIR} STREQUAL "")
        set(BOSS_includes_Boost "-I${Boost_INCLUDE_DIR}")
    endif()
    set(BOSS_includes_GSL "")
    if (NOT ${GSL_INCLUDE_DIRS} STREQUAL "")
      set(BOSS_includes_GSL "-I${GSL_INCLUDE_DIRS}")
    endif()
    set(BOSS_includes_Eigen3 "")
    if (NOT ${EIGEN3_INCLUDE_DIR} STREQUAL "")
      set(BOSS_includes_Eigen3 "-I${EIGEN3_INCLUDE_DIR}")
    endif()

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      set(BOSS_castxml_cc "--castxml-cc=${CMAKE_CXX_COMPILER}")
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
      set(BOSS_castxml_cc "")
    endif()
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      set(dl "https://data.kitware.com/api/v1/file/57b5de9f8d777f10f2696378/download")
      set(dl_filename "castxml-macosx.tar.gz")
    else()
      set(dl "https://data.kitware.com/api/v1/file/57b5dea08d777f10f2696379/download")
      set(dl_filename "castxml-linux.tar.gz")
    endif()
    ExternalProject_Add_Step(${name}_${ver} BOSS
      # Check for castxml binaries and download if they do not exist
      COMMAND ${PROJECT_SOURCE_DIR}/cmake/scripts/download_castxml_binaries.sh ${BOSS_dir} ${CMAKE_COMMAND} ${CMAKE_DOWNLOAD_FLAGS} ${dl} ${dl_filename}
      # Run BOSS
      COMMAND ${PYTHON_EXECUTABLE} ${BOSS_dir}/boss.py ${BOSS_castxml_cc} ${BOSS_includes_Boost} ${BOSS_includes_Eigen3} ${BOSS_includes_GSL} ${name}_${backend_version_safe}
      # Copy BOSS-generated files to correct folders within Backends/include
      COMMAND cp -r BOSS_output/${name_in_frontend}_${backend_version_safe}/for_gambit/backend_types/${name_in_frontend}_${backend_version_safe} ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_types/
      COMMAND cp BOSS_output/${name_in_frontend}_${backend_version_safe}/frontends/${name_in_frontend}_${backend_version_safe}.hpp ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/frontends/${name_in_frontend}_${backend_version_safe}.hpp
      DEPENDEES patch
      DEPENDERS configure
    )
  endif()
endmacro()


# Adding Python macros 
macro(CheckPython)
  # Check for Python interpreter
  # We also need to search for PythonLibs before letting pybind11 look for them,
  # otherwise it seems to get it wrong.  Also, we need to add versions of python
  # greater than 3.3 manually, for compatibility with CMake 2.8.12.
  # If pybind11 is ditched, do not worry about PythonLibs
  set(Python_ADDITIONAL_VERSIONS 3.4 3.5 3.6 3.7 3.8 3.9)
  # If both FORCE_PYTHON2 and FORCE_PYTHON3 are set, throw error
  if (FORCE_PYTHON2 AND FORCE_PYTHON3)
    message(FATAL_ERROR "Two different versions of python requested. Switch either FORCE_PYTHON2 or FORCE_PYTHON3 off.")
  endif()
  if (FORCE_PYTHON2)
    message("${BoldYellow}   Python 2 requested; searching for Python 2.7${ColourReset}")
    find_package(PythonInterp 2.7 REQUIRED)
    if(NOT DITCH_PYBIND)
      find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT)
    endif()
  elseif (FORCE_PYTHON3)
    message("${BoldYellow}   Python 3 requested; searching for Python 3.x${ColourReset}")
    find_package(PythonInterp 3 REQUIRED)
    if(NOT DITCH_PYBIND)
      find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT)
    endif()
  else()
    find_package(PythonInterp 3)
    if(PYTHONINTERP_FOUND AND NOT DITCH_PYBIND)
      find_package(PythonLibs 3)
    else()
      message("${BoldYellow}   Python 3 not found, searching for Python 2.7${ColourReset}")
      find_package(PythonInterp 2 REQUIRED)
      if (PYTHON_VERSION_MINOR LESS 7)
        message(FATAL_ERROR "\nGAMBIT requires Python 2.7.  \nIf you need to set the path to the Python interpreter manually, "
                            "please use -D PYTHON_EXECUTABLE=path/to/preferred/python.")
      endif()
      if(NOT DITCH_PYBIND)
        find_package(PythonLibs 2)
      endif()
    endif()
  endif()
  message("${BoldYellow}   Using Python interpreter version ${PYTHON_VERSION_STRING} for build.${ColourReset}")

  if(PYTHONLIBS_FOUND)
    string(FIND "${PYTHONLIBS_VERSION_STRING}" "2.7" PY2_POSITION)
    if(PY2_POSITION EQUAL 0)
      set(UNSUPPORTED_PYTHON_VERSION "3")
    else()
      set(UNSUPPORTED_PYTHON_VERSION "2.7")
    endif()
    message("${BoldYellow}   Using Python libraries version ${PYTHONLIBS_VERSION_STRING} for Python backend support.${ColourReset}\n"
            "   Backends requiring Python ${UNSUPPORTED_PYTHON_VERSION} will be ditched.")
    if (NOT "${PYTHON_VERSION_STRING}" STREQUAL "${PYTHONLIBS_VERSION_STRING}")
      message("${BoldRed}   NOTE: You are using different Python versions for the interpreter and the libraries!${ColourReset}\n"
              "   In principle this should be fine, as the interpreter is only used for building GAMBIT, and the\n"
              "   libraries are only used for providing support for Python backends at runtime.  However, if you\n"
              "   have matching versions installed, you can make this message go away by trying one of the following\n"
              "   (making sure to clean out your build directory in between any such changes):\n"
              "   1. invoke cmake as cmake -DFORCE_PYTHON2=True .. (or similar)\n"
              "   2. invoke cmake as cmake -DFORCE_PYTHON3=True .. (or similar)\n"
              "   3. set the following variables when invoking cmake:\n"
              "     PYTHON_LIBRARY\n"
              "     PYTHON_INCLUDE_DIR\n"
              "     PYTHON_EXECUTABLE\n")
    endif()
  endif()

  # Check for pybind11 if PythonLibs were found and not ditched
  if(NOT PYTHONLIBS_FOUND)
    if(DITCH_PYBIND)
      message("${BoldCyan} X Excluding pybind11 from GAMBIT configuration. Ditching support for Python backends.${ColourReset}")
    else()
      message("${BoldRed}   PythonLibs NOT found, so pybind11 cannot be used. Ditching support for Python backends.${ColourReset}\n"
              "   If you *do* have the Python libraries installed, you should first try setting/unsetting\n"
              "   FORCE_PYTHON2 or FORCE_PYTHON3 when invoking cmake (make sure to clean out your build\n"
              "   directory in between any such changes).  If that does not work, you can manually set the\n"
              "   following variables when invoking cmake (also making sure to clean out your build dir):\n"
              "     PYTHON_LIBRARY\n"
              "     PYTHON_INCLUDE_DIR\n"
              "     PYTHON_EXECUTABLE")
    set(itch "${itch};pybind11")
    endif()
  else()
    set(MIN_pybind11_VERSION "2.5.0")
    set(PREFERRED_pybind11_VERSION "2.5.0")
    set(pybind11_CONTRIB_DIR "${PROJECT_SOURCE_DIR}/contrib/pybind11")
    include_directories("${PYTHON_INCLUDE_DIRS}")
    find_package(pybind11 QUIET)
    if(pybind11_FOUND)
      if(pybind11_VERSION VERSION_LESS MIN_pybind11_VERSION)
        if(EXISTS "${pybind11_CONTRIB_DIR}")
          use_contributed_pybind11()
        else()
          message("${BoldRed}   Found pybind11 ${pybind11_VERSION}. GAMBIT requires at least v${MIN_pybind11_VERSION}.${ColourReset}")
          set(pybind11_FOUND FALSE)
        endif()
      else()
        message("${BoldYellow}   Found pybind11 ${pybind11_VERSION} at ${pybind11_DIR}.${ColourReset}")
        # This doesn't include anything since PYBIND11_INCLUDE_DIR is not defined
        # include_directories("${PYBIND11_INCLUDE_DIR}")
      endif()
    endif()
    if(NOT pybind11_FOUND)
      if(EXISTS "${pybind11_CONTRIB_DIR}")
        use_contributed_pybind11()
      else()
        message("${BoldRed}   CMake will now download and install pybind11 v${PREFERRED_pybind11_VERSION}.${ColourReset}")
        execute_process(RESULT_VARIABLE result COMMAND git clone https://github.com/pybind/pybind11.git ${pybind11_CONTRIB_DIR})
        if(${result} STREQUAL "0")
          execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${pybind11_CONTRIB_DIR} git checkout -q v${PREFERRED_pybind11_VERSION})
          use_contributed_pybind11()
        else()
          message("${BoldRed}   Attempt to clone git repository for pybind11 failed.  This may be because you are disconnected from the internet.\n   "
                  "Otherwise, your git installation may be faulty. Errors about missing .so files are usually due to\n   "
                  "your git installation being linked to a buggy version of libcurl.  In that case, try reinstalling libcurl.${ColourReset}")
        endif()
      endif()
    endif()
    set(HAVE_PYBIND11 "${pybind11_FOUND}")
  endif()


  # Check for required Python libraries
  foreach(module yaml os re datetime sys getopt shutil itertools)
    gambit_find_python_module(${module} REQUIRED)
  endforeach()

  # Set warnings to stop complaints about old Python headers not being C++17 compliant
  if(PYTHON_VERSION_MAJOR EQUAL 2)
    set_compiler_warning("no-register" CMAKE_CXX_FLAGS)
  endif()

endmacro()

# check for Axel - Lightweight CLI download accelerator to speed up backend downloads
macro(CheckAxel)
  set(CMAKE_DOWNLOAD_FLAGS "NONE")
  option(WITH_AXEL "Compile with Axel enabled" OFF)
  if(WITH_AXEL)
    find_program(axel_FOUND axel)
    if(axel_FOUND)
      message("${BoldYellow}   Found axel.${ColourReset} Backend and scanner downloads will be as fast as possible.")
      set(CMAKE_DOWNLOAD_FLAGS "WITH_AXEL")
    else()
      message("${Red}   Axel utility not found.  Backend downloads would be faster if you installed axel.${ColourReset}")
    endif()
  else()
    message("${BoldCyan} X Axel is disabled. Please use -DWITH_AXEL=ON to enable fast downloads with Axel.${ColourReset}")
  endif()
endmacro()

# set the C, CXX, and Fortran compilation flags 
macro(SetCompilationFlags)

# Make sure the user hasn't accidentally set the C++ compiler to the C compiler.
  get_filename_component(CXX_COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
  if (CXX_COMPILER_NAME MATCHES "gcc.*$")
    message(FATAL_ERROR "\nYou have set CMAKE_CXX_COMPILER to gcc.  Did you mean g++?")
  elseif (CXX_COMPILER_NAME MATCHES "clang($|-.*)")
    message(FATAL_ERROR "\nYou have set CMAKE_CXX_COMPILER to clang.  Did you mean clang++?")
  elseif (CXX_COMPILER_NAME MATCHES "icc.*$")
    message(FATAL_ERROR "\nYou have set CMAKE_CXX_COMPILER to icc.  Did you mean icpc?")
  endif()

  # Enforce minimum versions for the C/C++ compiler
  if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS MIN_ICC_VERSION) OR
      ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS MIN_GCC_VERSION))
    message(FATAL_ERROR "${BoldRed}\nGAMBIT requires at least g++ ${MIN_GCC_VERSION} or icpc ${MIN_ICC_VERSION}.  Please install a newer compiler.${ColourReset}")
  endif()

  # Add some Fortran compiler flags so that fortran does not limit source code lines and can preprocess
  # lets just set the the new Fortran cmake variables that works in later cmake versions (>=3.18.0)
  # but this doesn't appear to work anyway 
  # set_target_properties(gambit PROPERTIES Fortran_FORMAT FIXED)
  # set_target_properties(gambit PROPERTIES Fortran_PREPROCESS ON)
  set(Fortran_PREPROCESS "ON")
  set(Fortran_FORMAT "FIXED")
  # thus here is an explicit if statement to check which fortran compiler and the specific flags for those compilers 
  if(CMAKE_Fortran_COMPILER MATCHES "gfortran*" OR CMAKE_Fortran_COMPILER MATCHES "f95*")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -ffree-line-length-none -cpp")
  elseif(CMAKE_Fortran_COMPILER MATCHES "ifort*")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -extend-source -fpp")
  #for cray fortran wrappers their rather irritatingly no uniform way of requesting no line truncation and preproccesing
  # the question is what to do
  endif()

  # Add -fPIC for 64 bit systems
  # PJE: Why only 64 bit? Shouldn't -fPIC be for all?
  if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
  endif()

  # Check if we are using 2019 intel compilers or gcc 6.1 or 6.2 together with pybind11, and forbid the use of C++17 if so.
  if(HAVE_PYBIND11)
    if(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 18.0.6) OR
      ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.6 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.3))
      set(PERMIT_CXX17_CHECK FALSE)
    else()
      set(PERMIT_CXX17_CHECK TRUE)
    endif()
  endif()

  # Check if we are using gnu version 7.2, and forbid the use of C++17 if so.
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.1 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.3)
    set(PERMIT_CXX17_CHECK FALSE)
  endif()

  # Check for C++11, C++14 and C++17 support.
  include(CheckCXXCompilerFlag)
  if(PERMIT_CXX17_CHECK)
    CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
  endif()
  if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_STANDARD 17) 
  else()
    if(PERMIT_CXX17_CHECK)
      CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1z)
    endif()
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    if(COMPILER_SUPPORTS_CXX14)
      set(CMAKE_CXX_STANDARD 14) 
    else()
      CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1y)
      CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
      if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_STANDARD 11) 
      else()
        CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
        if(COMPILER_SUPPORTS_CXX0X)
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        else()
          message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
        endif()
      endif()
    endif()
  endif()

  # Check for C99, C11 and C18 support
  include(CheckCCompilerFlag)
  CHECK_C_COMPILER_FLAG("-std=c18" COMPILER_SUPPORTS_C18)
  CHECK_C_COMPILER_FLAG("-std=c11" COMPILER_SUPPORTS_C11)
  CHECK_C_COMPILER_FLAG("-std=c99" COMPILER_SUPPORTS_C99)
  if(NOT COMPILER_SUPPORTS_C99)
    message("${BoldRed}   The compiler ${CMAKE_C_COMPILER} has no C99 support.  AlterBBN will be ditched.${ColourReset}")
    set(itch "${itch};alterbbn")
  endif()


  if(${WERROR})
    set_compiler_warning("error")
  else()
    message(STATUS "${Red}Werror is disabled${ColourReset}")
  endif()

  set_compiler_warning("all" CMAKE_CXX_FLAGS)
  set_compiler_warning("extra" CMAKE_CXX_FLAGS)
  set_compiler_warning("no-misleading-indentation" CMAKE_CXX_FLAGS)

  # set intel warnings
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # "remark #981: operands are evaluated in unspecified order"
    # This is a false positive, suppress it.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd981")

    # "remark #1418: external function definition with no prior declaration"
    # This can safely be ignord according to the ICC docs.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd1418")

    # "remark #1419: external declaration in primary source file"
    # This can safely be ignord according to the ICC docs.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd1419")
  endif()

  message("${BoldYellow} CMAKE_C_FLAGS       : ${CMAKE_C_FLAGS}")
  message("${BoldYellow} CMAKE_CXX_FLAGS     : ${CMAKE_CXX_FLAGS}")
  message("${BoldYellow} CMAKE_Fortran_FLAGS : ${CMAKE_Fortran_FLAGS}")
endmacro()


macro(SetOpenMP)
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
      set(OpenMP_C "${CMAKE_C_COMPILER}")
      set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
      set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
      set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
      set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
      set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
      set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
      set(OpenMP_CXX_LIB_NAMES "libomp")
      set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
      set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
      set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
    endif()
  endif()  
  find_package(OpenMP REQUIRED COMPONENTS C CXX Fortran)
  if (OPENMP_FOUND)
    message("${BoldYellow} -- OpenMP found successfully")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    if (NOT DEFINED OpenMP_Fortran_FLAGS)
      if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(OpenMP_Fortran_FLAGS "-fopenmp=libomp")
      else()
        set(OpenMP_Fortran_FLAGS "-fopenmp")
      endif()
    endif()
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${OpenMP_Fortran_FLAGS}")
  else()
    # check if brew is installed and the compiler id is AppleClang then fix OpenMP search
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
      find_program(BREW NAMES brew)
      # This block modified from https://github.com/CLIUtils/cmake/blob/master/PatchOpenMPApple.cmake
      if(BREW)
        execute_process(COMMAND ${BREW} ls libomp RESULT_VARIABLE BREW_RESULT_CODE OUTPUT_QUIET ERROR_QUIET)
        if(BREW_RESULT_CODE)
          message(FATAL_ERROR "You are using the Apple Clang compiler, and have HomeBrew installed, but have not installed OpenMP. Please run \"brew install libomp\"")
        else()
          execute_process(COMMAND ${BREW} --prefix libomp OUTPUT_VARIABLE BREW_LIBOMP_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)
          set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
          set(OpenMP_CXX_LIB_NAMES "omp")
          set(OpenMP_omp_LIBRARY "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib")
          include_directories("${BREW_LIBOMP_PREFIX}/include")
          message(STATUS "Using Homebrew libomp from ${BREW_LIBOMP_PREFIX}")
        endif()
      else()
        message(FATAL_ERROR "\nOpenMP libraries not found. You are using the Apple Clang compiler. The easiest way to get OpenMP support for Apple Clang is to install it via HomeBrew. If you want to install it some other way, e.g. via MacPorts, you need to manually set -DOpenMP_CXX_FLAGS -DOpenMP_CXX_LIB_NAMES -DOpenMP_C_FLAGS -DOpenMP_C_LIB_NAMES -DOpenMP_omp_LIBRARY when invoking cmake.")
      endif()
    else()
      message(FATAL_ERROR "\nOpenMP libraries not found.  Please use compiler with OpenMP.")
    endif()
  endif()
endmacro()


macro(SetGSL)
  include(cmake/FindGSL.cmake)
  if(GSL_FOUND)
    if (NOT GSL_INCLUDE_DIRS STREQUAL "")
      include_directories("${GSL_INCLUDE_DIRS}")
    endif()
  else()
    message(FATAL_ERROR "GAMBIT requires the GSL libraries.")
  endif()
endmacro()

macro(SetMathematica)
  string(REGEX MATCH ";M;|;Ma;|;Mat;|;Math;|;Mathe;|;Mathem;|;Mathema;|;Mathemat;|;Mathemati;|;Mathematic;|;Mathematica;|;m;|;ma;|;mat;|;math;|;mathe;|;mathem;|;mathema;|;mathemat;|;mathemati;|;mathematic;|;mathematica" DITCH_MATHEMATICA ";${itch};")
  if(DITCH_MATHEMATICA)
    set(HAVE_MATHEMATICA 0)
    message("${BoldCyan} X Excluding Mathematica from GAMBIT configuration. All backends using Mathematica will be disabled${ColourReset}")
  else()
    find_library(LIBUUID NAMES uuid)
    if(LIBUUID)
      message("   Found library libuuid")
      find_package(Mathematica 10.0 QUIET)
      if(Mathematica_FOUND AND (NOT DEFINED Mathematica_Invalid_License OR IGNORE_MATHEMATICA_LICENSE))
        message("${BoldYellow}   Found Mathematica.${ColourReset}")
        if(Mathematica_WSTP_FOUND)
          message("${BoldYellow}   Found Wolfram Symbolic Transfer Protocol. Mathematica backends enabled.${ColourReset}")
          set(HAVE_MATHEMATICA 1)
          set(MATHEMATICA_WSTP_H "${Mathematica_WSTP_INCLUDE_DIR}/wstp.h")
          set(MATHEMATICA_KERNEL "${Mathematica_KERNEL_EXECUTABLE}")
          set(MATHEMATICA_WSTP_VERSION_MAJOR ${Mathematica_WSTP_VERSION_MAJOR})
          set(MATHEMATICA_WSTP_VERSION_MINOR ${Mathematica_WSTP_VERSION_MINOR})
        else()
          message("${BoldRed}  WSTP not found. Please make sure it is installed before attempting to use Mathematica backends.${ColourReset}")
          set(HAVE_MATHEMATICA 0)
        endif()
      elseif(DEFINED Mathematica_Invalid_License AND NOT IGNORE_MATHEMATICA_LICENSE)
        message("${BoldRed}   Mathematica found but with an invalid license. Backends using Mathematica will be disabled.${ColourReset}")
        message("${BoldRed}   To ignore this license check, add -DIGNORE_MATHEMATICA_LICENSE=True to your cmake command.${ColourReset}")
        set(HAVE_MATHEMATICA 0)
      else()
        message("${BoldRed}   Mathematica not found. Backends using Mathematica will be disabled.${ColourReset}")
        set(HAVE_MATHEMATICA 0)
      endif()
    else()
      message("${BoldRed}   Missing library libuuid required for WSTP. Mathematica will be disabled.${ColourReset}")
      set(HAVE_MATHEMATICA 0)
    endif()
  endif()
endmacro()

macro(SetBackendCompliationFlags)
  set(BACKEND_C_FLAGS_NO_BUILD_OPTIMISATIONS "${CMAKE_C_FLAGS}")
  set(BACKEND_CXX_FLAGS_NO_BUILD_OPTIMISATIONS "${CMAKE_CXX_FLAGS}")
  set(BACKEND_Fortran_FLAGS_NO_BUILD_OPTIMISATIONS "${CMAKE_Fortran_FLAGS}")
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
    set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
    set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_DEBUG}")
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Unless invoked with FORCE_O3, drop down to -O2 optimisation for more reasonable compile time.
    if (NOT DEFINED FORCE_O3)
      string(REGEX REPLACE "(-O3)" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
      string(REGEX REPLACE "(-O3)" "-O2" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
      string(REGEX REPLACE "(-O3)" "-O2" CMAKE_Fortran_FLAGS_RELEASE "${CMAKE_Fortran_FLAGS_RELEASE}")
    endif()
    set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
    set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
    set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_RELEASE}")
    # Never send the -O3 from cmake's release build config onwards to backends, as some are touchy.
    string(REGEX REPLACE "(-O3)" "-O2" BACKEND_C_FLAGS "${BACKEND_C_FLAGS}")
    string(REGEX REPLACE "(-O3)" "-O2" BACKEND_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
    string(REGEX REPLACE "(-O3)" "-O2" BACKEND_Fortran_FLAGS "${BACKEND_Fortran_FLAGS}")
  elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_RELWITHDEBINFO}")
  elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_MINSIZEREL}")
    set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MINSIZEREL}")
    set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${CMAKE_Fortran_FLAGS_MINSIZEREL}")
  else()
    set(BACKEND_C_FLAGS "${CMAKE_C_FLAGS}")
    set(BACKEND_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS}")
  endif()
  set(BACKEND_C18_FLAGS "${BACKEND_C_FLAGS} -std=c18")
  set(BACKEND_C11_FLAGS "${BACKEND_C_FLAGS} -std=c11")
  set(BACKEND_C99_FLAGS "${BACKEND_C_FLAGS} -std=c99")
  set(BACKEND_GNU99_FLAGS "${BACKEND_C_FLAGS} -std=gnu99")
endmacro()

macro(SetEigen)
  find_package(Eigen3 3.1.0)
  if(EIGEN3_FOUND)
    include_directories("${EIGEN3_INCLUDE_DIR}")
    message("${BoldYellow} -- Eigen version: ${EIGEN3_VERSION}")
  else()
    message("${BoldRed}   Eigen v3.1.0 or greater not found.  FlexibleSUSY and GM2Calc interfaces will be excluded.${ColourReset}")
    set(itch "${itch};gm2calc;flexiblesusy")
    message(FATAL_ERROR "\nFlexibleSUSY is currently included in the GAMBIT distribution, so in fact it cannot be ditched.  Please install Eigen3.\n(Note that this will change in future GAMBIT versions, where FlexibleSUSY will be a 'true' backend.)")
  endif()
  if(EIGEN3_FOUND AND EIGEN3_VERSION VERSION_LESS 3.3.0)
    set_compiler_warning("no-ignored-attributes" CMAKE_CXX_FLAGS)
    set_compiler_warning("no-deprecated-register" CMAKE_CXX_FLAGS)
    set_compiler_warning("no-deprecated-declarations" CMAKE_CXX_FLAGS)
  endif()
  # Set warnings to stop complaining about deprecated copies in Eigen
  if(EIGEN3_VERSION_MINOR LESS 4 AND EIGEN3_VERSION_PATCH LESS 8)
    set_compiler_warning("no-deprecated-copy" CMAKE_CXX_FLAGS)
  endif()
endmacro()

macro(SetBoost)
  set(Boost_NO_BOOST_CMAKE ON)
  find_package(Boost 1.41)
  if(Boost_FOUND)
    include_directories("${Boost_INCLUDE_DIR}")
    message("${BoldYellow} -- Boost version: ${Boost_VERSION}")
  else()
    message(FATAL_ERROR "GAMBIT requires Boost v1.41 or greater.\nPlease install a suitable version of Boost and rerun cmake.")
  endif()

  # Fix Boost < 1.55 for Clang
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    if(${CMAKE_VERSION} VERSION_LESS 3.12.0)
      add_definitions(-DBOOST_PP_VARIADICS=1)
    else()
      add_compile_definitions(BOOST_PP_VARIADICS=1)
    endif()
  endif()
endmacro()

macro(SetGit)
  find_package(Git)
  if(GIT_FOUND)
    # Look for the latest tag and use it to set the version number.  If there is no such tag, use the tarball info file.
    get_version_from_git(GAMBIT_VERSION_MAJOR GAMBIT_VERSION_MINOR GAMBIT_VERSION_REVISION
                        GAMBIT_VERSION_PATCH GAMBIT_VERSION_FULL)
    if (GAMBIT_VERSION_MAJOR)
      message("${BoldYellow}   GAMBIT version detected from git tag: ${GAMBIT_VERSION_FULL}${ColourReset}")
    endif()
  endif()
  if(NOT GIT_FOUND OR NOT GAMBIT_VERSION_MAJOR)
    message("${BoldYellow}   GAMBIT version not detected via git.  Reverting to cmake/tarball_info.cmake.${ColourReset}")
    include(cmake/tarball_info.cmake)
  endif()
endmacro()