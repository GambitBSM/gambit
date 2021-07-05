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
#          (gonzalo@physik.rwth-aachen.de)
#  \date 2016 Sep
#  \date 2021 Mar
#
#  \author Will Handley
#          (wh260@cam.ac.uk)
#  \date 2018 Dec
#
#  \author Christopher Chang
#          (christopher.chang@uqconnect.edu.au)
#  \date 2021 Feb
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

# Execute script to prevent printing problems with standalones
function(add_elements_extras target)
  set(ELEMENTS_EXTRAS_SCRIPT ${PROJECT_SOURCE_DIR}/Elements/scripts/elements_extras.py)
  add_custom_target(${target} COMMAND ${PYTHON_EXECUTABLE} ${ELEMENTS_EXTRAS_SCRIPT} ${target}
                            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
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

      # Make the string comparison case insensitive
      string( TOLOWER "${child}" child_lower )
      string( TOLOWER "${excludes}" excludes_lower )
      
      if(NOT ${child_lower} STREQUAL "scannerbit")
        foreach(x ${excludes_lower})
          string( TOLOWER "${x}" x_lower )
          string(FIND ${child_lower} ${x_lower} location)
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
  set(patch_file "${package}-prefix/${safe_package}.dif")
  add_custom_target(clean-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring1}-BOSS ${rmstring1}-configure ${rmstring1}-build ${rmstring1}-install ${rmstring1}-done
                                     COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && (${target})) || true
                                     COMMAND [ -e ${reset_file} ] && ${PYTHON_EXECUTABLE} ${BOSS_dir}/boss.py -r ${reset_file} || true)
  add_custom_target(nuke-${package} DEPENDS clean-${package}
                                    COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring1}-download ${rmstring1}-download-failed ${rmstring1}-mkdir ${rmstring1}-patch ${rmstring1}-update ${rmstring1}-gitclone-lastrun.txt ${dl} || true
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory ${dir} || true
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory ${rmstring2} || true
                                    COMMAND [ -e ${patch_file} ] &&  patch -d/ -fsR -p0 < ${patch_file} && rm ${patch_file}|| true)
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
  add_dependencies(${libraryname} elements_extras)

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
  cmake_parse_arguments(ARG "" "" "SOURCES;HEADERS;LIBRARIES;MODULES;DEPENDENCIES" ${ARGN})

  # Assume that the standalone is to be included, unless we discover otherwise.
  set(standalone_permitted 1)

  # Exclude standalones that need HepMC if it has been excluded.
  if (EXCLUDE_HEPMC AND (";${ARG_DEPENDENCIES};" MATCHES ";hepmc;"))
    set(standalone_permitted 0)
  endif()

  # Iterate over modules, checking if the neccessary ones are present, and adding them to the target objects if so.
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
        # Temporarily add the printers module whenever SpecBit is present to avoid linking problems
        set(COMMA_SEPARATED_MODULES "${COMMA_SEPARATED_MODULES},Printers")
        set(STANDALONE_OBJECTS ${STANDALONE_OBJECTS} $<TARGET_OBJECTS:Printers>)
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

    # Add the elements_extras target
    add_elements_extras(${executablename}_elements_extras)
    add_dependencies(${executablename}_elements_extras elements_extras)
    add_dependencies(${executablename} ${executablename}_elements_extras)

    # Add each of the declared dependencies
    foreach(dep ${ARG_DEPENDENCIES})
      add_dependencies(${executablename} ${dep})
    endforeach()

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
      add_custom_target(${module}-${version}.tar.gz COMMAND ${CMAKE_COMMAND} -E remove_directory ${dirname}
                                      COMMAND ${CMAKE_COMMAND} -E make_directory ${dirname}
                                      COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/CMakeLists.txt ${dirname}/
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/${module} ${dirname}/${module}
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Logs ${dirname}/Logs
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Utils ${dirname}/Utils
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Printers ${dirname}/Printers
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/cmake ${dirname}/cmake
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/config ${dirname}/config
                                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/contrib ${dirname}/contrib
                                      COMMAND ${CMAKE_COMMAND} -E make_directory ${dirname}/yaml_files/
                                      COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/yaml_files/ScannerBit.yaml ${dirname}/yaml_files/
                                      COMMAND ${CMAKE_COMMAND} -E remove -f ${module}-${version}.tar.gz
                                      COMMAND ${CMAKE_COMMAND} -E tar cz ${module}-${version}.tar.gz ${dirname})
    else()
      add_custom_target(${module}-${version}.tar.gz COMMAND ${CMAKE_COMMAND} -E remove_directory ${dirname}
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
                                      COMMAND ${CMAKE_COMMAND} -E remove -f ${module}-${version}.tar.gz
                                      COMMAND ${CMAKE_COMMAND} -E tar cz ${module}-${version}.tar.gz ${dirname})
    endif()

    add_dependencies(${module}-${version}.tar.gz nuke-all)
    add_dependencies(standalone_tarballs ${module}-${version}.tar.gz)

  endforeach()

  # Add a special ad-hoc command to make a tarball containing SpecBit, DecayBit and PrecisionBit
  set(dirname "3Bit_${version}")
  add_custom_target(3Bit-${version}.tar.gz COMMAND ${CMAKE_COMMAND} -E remove_directory ${dirname}
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
                             COMMAND ${CMAKE_COMMAND} -E remove -f 3Bit-${version}.tar.gz
                             COMMAND ${CMAKE_COMMAND} -E tar cz 3Bit-${version}.tar.gz ${dirname})
  add_dependencies(3Bit-${version}.tar.gz nuke-all)
  add_dependencies(standalone_tarballs 3Bit-${version}.tar.gz)

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

macro(BOSS_backend name backend_version ${ARGN})

  # Replace "." by "_" in the backend version number
  string(REPLACE "." "_" backend_version_safe ${backend_version})

  # Check if there is a suffix
  set(extra_args ${ARGN})
  list(LENGTH extra_args n_extra_args)
  if (${n_extra_args} GREATER 0)
    set(suffix "_${ARGN}")
  else()
    set(suffix "")
  endif()

  # Construct path to the config file expected by BOSS
  set(config_file_path "${BOSS_dir}/configs/${name}_${backend_version_safe}${suffix}.py")

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
      set(castxml_dl "https://data.kitware.com/api/v1/file/57b5de9f8d777f10f2696378/download")
      set(castxml_dl_filename "castxml-macosx.tar.gz")
    else()
      set(castxml_dl "https://data.kitware.com/api/v1/file/57b5dea08d777f10f2696379/download")
      set(castxml_dl_filename "castxml-linux.tar.gz")
    endif()
    ExternalProject_Add_Step(${name}_${ver} BOSS
      # Check for castxml binaries and download if they do not exist
      COMMAND ${PROJECT_SOURCE_DIR}/cmake/scripts/download_castxml_binaries.sh ${BOSS_dir} ${CMAKE_COMMAND} ${CMAKE_DOWNLOAD_FLAGS} ${castxml_dl} ${castxml_dl_filename}
      # Run BOSS
      COMMAND ${PYTHON_EXECUTABLE} ${BOSS_dir}/boss.py ${BOSS_castxml_cc} ${BOSS_includes_Boost} ${BOSS_includes_Eigen3} ${BOSS_includes_GSL} ${name}_${backend_version_safe}${suffix}
      # Make a dif of the existing files in Backends/include and those generated by BOSS
      COMMAND diff -rupN ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_types/${name_in_frontend}_${backend_version_safe} BOSS_output/${name_in_frontend}_${backend_version_safe}/for_gambit/backend_types/${name_in_frontend}_${backend_version_safe} > ${name}_${backend_version}-prefix/${name}_${backend_version_safe}.dif || true
      COMMAND diff -rupN ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/frontends/${name_in_frontend}_${backend_version_safe}.hpp BOSS_output/${name_in_frontend}_${backend_version_safe}/frontends/${name_in_frontend}_${backend_version_safe}.hpp >> ${name}_${backend_version}-prefix/${name}_${backend_version_safe}.dif || true
      # Copy BOSS-generated files to correct folders within Backends/include
      COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_types/${name_in_frontend}_${backend_version_safe} || true
      COMMAND cp -r BOSS_output/${name_in_frontend}_${backend_version_safe}/for_gambit/backend_types/${name_in_frontend}_${backend_version_safe} ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_types/
      COMMAND cp BOSS_output/${name_in_frontend}_${backend_version_safe}/frontends/${name_in_frontend}_${backend_version_safe}.hpp ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/frontends/${name_in_frontend}_${backend_version_safe}.hpp
      DEPENDEES patch
      DEPENDERS configure
    )
  endif()
endmacro()
