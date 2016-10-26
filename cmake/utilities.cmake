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
#************************************************

include(CMakeParseArguments)

# Add precompiled header support
##include(cmake/PrecompiledHeader.cmake)
#include(cmake/cotire.cmake)

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

#Macro to retrieve GAMBIT modules
macro(retrieve_bits bits root excludes quiet)

  set(${bits} "")
  file(GLOB children RELATIVE ${root} ${root}/*Bit*)

  foreach(child ${children})
    string(FIND ${child} ".dSYM" FOUND_DSYM)
    if(IS_DIRECTORY ${root}/${child} AND ${FOUND_DSYM} EQUAL -1)

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

# Arrange clean commands
include(cmake/cleaning.cmake)

# Macro to write some shell commands to clean an external code.  Adds clean-[package] and nuke-[package]
macro(add_external_clean package dir dl target)
  set(rmstring "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
  add_custom_target(clean-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-configure ${rmstring}-build ${rmstring}-install ${rmstring}-done
                                     COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} ${target}) || true)
  add_custom_target(nuke-${package} DEPENDS clean-${package}
                                    COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-download ${rmstring}-download-failed ${rmstring}-mkdir ${rmstring}-patch ${rmstring}-update ${rmstring}-gitclone-lastrun.txt ${dl} || true
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory ${dir} || true)
endmacro()

# Macro to write some shell commands to clean an external chained code.  Adds clean-[package] and nuke-[package]
macro(add_chained_external_clean package dir target dependee)
  set(rmstring "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
  add_custom_target(clean-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-configure ${rmstring}-build ${rmstring}-install ${rmstring}-done
                                     COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} ${target}) || true)
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

# Function to add GAMBIT library (STATIC, SHARED, or OBJECT depending on OPTION)
function(add_gambit_library libraryname)
  cmake_parse_arguments(ARG "" "OPTION" "SOURCES;HEADERS" ${ARGN})

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

  # Cotire speeds up compilation by automatically generating and precompiling prefix headers for the targets
  #cotire(${libraryname})
  ##add_precompiled_header(${libraryname} "${PROJECT_SOURCE_DIR}/Elements/include/gambit/Elements/common.hpp" TRUE)

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
  add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/${filename}
                     COMMAND python ${${HARVESTER}} -x __not_a_real_name__,${itch_with_commas}
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

  target_link_libraries(${executablename} ${LIBRARIES} yaml-cpp)
  add_dependencies(${executablename} mkpath)

  #For checking if all the needed libs are present.  Never add them manually with -lsomelib!!
  if(VERBOSE)
    message(STATUS ${LIBRARIES})
  endif()

  # Cotire speeds up compilation by automatically generating and precompiling prefix headers for the targets
  #cotire(${executablename})
  ##add_precompiled_header(${executablename} "${PROJECT_SOURCE_DIR}/Elements/include/gambit/Elements/common.hpp" TRUE)

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
        #set(STANDALONE_OBJECTS ${STANDALONE_OBJECTS} $<TARGET_OBJECTS:${module}>)
      else()
        set(COMMA_SEPARATED_MODULES "${module}")
        #set(STANDALONE_OBJECTS $<TARGET_OBJECTS:${module}>)
        set(first_module ${module})
      endif()
      # Exclude standalones that need SpecBit when FS has been excluded.  Remove this once FS is BOSSed.
      if(module STREQUAL "SpecBit" AND EXCLUDE_FLEXIBLESUSY)
        set(standalone_permitted 0)
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
                       COMMAND python ${STANDALONE_FACILITATOR} ${executablename} -m __not_a_real_name__,${COMMA_SEPARATED_MODULES}
                       COMMAND touch ${STANDALONE_FUNCTORS}
                       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                       DEPENDS modules_harvested
                               ${STANDALONE_FACILITATOR}
                               ${HARVEST_TOOLS}
                               ${PROJECT_BINARY_DIR}/CMakeCache.txt)

    # Do ad hoc checks for stuff that will eventually be BOSSed and removed from here.
    if (NOT EXCLUDE_FLEXIBLESUSY)
      set(ARG_LIBRARIES ${ARG_LIBRARIES} ${flexiblesusy_LDFLAGS})
    endif()
    if (NOT EXCLUDE_DELPHES)
      set(ARG_LIBRARIES ${ARG_LIBRARIES} ${DELPHES_LDFLAGS} ${ROOT_LIBRARIES} ${ROOT_LIBRARY_DIR}/libEG.so)
    endif()

    add_gambit_executable(${executablename} "${GAMBIT_ALL_COMMON_LIBS} ${ARG_LIBRARIES}"
                          SOURCES ${STANDALONE_SOURCES}
                                  ${STANDALONE_OBJECTS}
                          HEADERS ${ARG_HEADERS})

    # Do more ad hoc checks for stuff that will eventually be BOSSed and removed from here
    if (NOT EXCLUDE_FLEXIBLESUSY)
      add_dependencies(${executablename} flexiblesusy)
    endif()
    if (NOT EXCLUDE_DELPHES)
      add_dependencies(${executablename} delphes)
    endif()

    # Add the new executable to the standalones target
    add_dependencies(standalones ${executablename})

  endif()

endfunction()


# Simple function to find specific Python modules
macro(find_python_module module)
  execute_process(COMMAND python -c "import ${module}" RESULT_VARIABLE return_value ERROR_QUIET)
  if (NOT return_value)
    message(STATUS "Found Python module ${module}.")
    set(PY_${module}_FOUND TRUE)
  else()
    if(ARGC GREATER 1 AND ARGV1 STREQUAL "REQUIRED")
      message(FATAL_ERROR "-- FAILED to find Python module ${module}.")
    else()
      message(STATUS "FAILED to find Python module ${module}.")
    endif()
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
    set(BOSS_includes "-I ${Boost_INCLUDE_DIR}")
    if (NOT ${GSL_INCLUDE_DIR} STREQUAL "")
      set(BOSS_includes "${BOSS_includes} -I ${GSL_INCLUDE_DIR}")
    endif()
    ExternalProject_Add_Step(${name}_${ver} BOSS
      # Run BOSS
      COMMAND cd ${BOSS_dir} && python boss.py ${BOSS_includes} ${name}_${backend_version_safe}
      # Copy BOSS-generated files to correct folders within Backends/include
      COMMAND cp -r ${BOSS_dir}/BOSS_output/for_gambit/backend_types/${name_in_frontend}_${backend_version_safe} ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_types/
      COMMAND cp ${BOSS_dir}/BOSS_output/frontends/${name_in_frontend}_${backend_version_safe}.hpp ${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/frontends/${name_in_frontend}_${backend_version_safe}.hpp
      DEPENDEES patch
      DEPENDERS configure
    )
  endif()
endmacro()

