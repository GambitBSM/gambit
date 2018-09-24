# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake configuration script for contributed
#  packages in GAMBIT.
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
#
#************************************************

include(ExternalProject)

#contrib/slhaea
include_directories("${PROJECT_SOURCE_DIR}/contrib/slhaea/include")

#contrib/mcutils
include_directories("${PROJECT_SOURCE_DIR}/contrib/mcutils/include")

#contrib/heputils
include_directories("${PROJECT_SOURCE_DIR}/contrib/heputils/include")

#contrib/mkpath
set(mkpath_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/contrib/mkpath/include")
include_directories("${mkpath_INCLUDE_DIR}")
add_gambit_library(mkpath OPTION OBJECT
                          SOURCES ${PROJECT_SOURCE_DIR}/contrib/mkpath/src/mkpath.c
                          HEADERS ${PROJECT_SOURCE_DIR}/contrib/mkpath/include/mkpath/mkpath.h)
set(GAMBIT_BASIC_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:mkpath>)

#contrib/yaml-cpp-0.5.3
set(yaml_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.5.3/include)
include_directories("${yaml_INCLUDE_DIR}")
add_subdirectory(${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.5.3 EXCLUDE_FROM_ALL)

#contrib/Delphes-3.1.2; include only if ColliderBit is in use and Delphes is not intentionally ditched.
set (DELPHES_DIR "${PROJECT_SOURCE_DIR}/contrib/Delphes-3.1.2")
set (DELPHES_DICTS "${PROJECT_SOURCE_DIR}/ColliderBit/src/delphes/BTaggingWithTruthModule_dict.cc"
                   "${PROJECT_SOURCE_DIR}/ColliderBit/src/delphes/AbsoluteIsolationModule_dict.cc"
                   "${PROJECT_SOURCE_DIR}/ColliderBit/include/gambit/ColliderBit/delphes/BTaggingWithTruthModule_dict.h"
                   "${PROJECT_SOURCE_DIR}/ColliderBit/include/gambit/ColliderBit/delphes/AbsoluteIsolationModule_dict.h")
string(REGEX MATCH ";D;|;De;|;Del;|;Delp;|;Delph;|;Delphe;|;Delphes" DITCH_DELPHES ";${itch};")
include_directories("${DELPHES_DIR}" "${DELPHES_DIR}/external" "${PROJECT_SOURCE_DIR}/ColliderBit/include/gambit/ColliderBit/delphes")
if(DITCH_DELPHES OR NOT ";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  set (EXCLUDE_DELPHES TRUE)
  add_custom_target(clean-delphes COMMAND "")
  message("${BoldCyan} X Excluding Delphes from GAMBIT configuration.${ColourReset}")
  foreach(DICT ${DELPHES_DICTS})
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${DICT})
  endforeach()
else()
  set (EXCLUDE_DELPHES FALSE)
  set (DELPHES_LDFLAGS "-L${DELPHES_DIR} -lDelphes")
  set (DELPHES_BAD_LINE "\\(..CC)\ ..patsubst\ -std=%,,..CXXFLAGS))\\)\ \\(..CXXFLAGS.\\)")
  set (CMAKE_INSTALL_RPATH "${DELPHES_DIR}")
  ExternalProject_Add(delphes
    SOURCE_DIR ${DELPHES_DIR}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure
              COMMAND sed ${dashi} "/^CXXFLAGS += .* -Iexternal\\/tcl/ s/$/ ${CMAKE_CXX_FLAGS}/" <SOURCE_DIR>/Makefile
              COMMAND sed ${dashi} "s,\ ..EXECUTABLE.,,g" <SOURCE_DIR>/Makefile
              COMMAND sed ${dashi} "s/${DELPHES_BAD_LINE}/\\1/g" <SOURCE_DIR>/Makefile
    BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} all
    INSTALL_COMMAND ""
  )
  message("${Yellow}-- Generating Delphes ROOT dictionaries...${ColourReset}")
  execute_process(COMMAND ./make_dicts.sh
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ColliderBit/src/delphes
                  RESULT_VARIABLE result
                 )
  if (NOT "${result}" STREQUAL "0")
    message(FATAL_ERROR "Could not automatically generate Delphes ROOT dictionaries.  Blame ROOT.")
  endif()
  message("${Yellow}-- Generating Delphes ROOT dictionaries - done.${ColourReset}")
  # Add clean info
  foreach(DICT ${DELPHES_DICTS})
    set(clean_files ${clean_files} ${DICT})
  endforeach()
  set(rmstring "${CMAKE_BINARY_DIR}/delphes-prefix/src/delphes-stamp/delphes")
  add_custom_target(clean-delphes COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-configure ${rmstring}-build ${rmstring}-install ${rmstring}-done
                                  COMMAND cd ${DELPHES_DIR} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} distclean) || true)
  add_dependencies(distclean clean-delphes)
endif()

#contrib/fjcore-3.2.0; compile only if Delphes is ditched and ColliderBit is not.
set(fjcore_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/contrib/fjcore-3.2.0")
include_directories("${fjcore_INCLUDE_DIR}")
add_definitions(-DFJCORE)
add_definitions(-DFJNS=gambit::fjcore)
add_gambit_library(fjcore OPTION OBJECT
                          SOURCES ${PROJECT_SOURCE_DIR}/contrib/fjcore-3.2.0/fjcore.cc
                          HEADERS ${PROJECT_SOURCE_DIR}/contrib/fjcore-3.2.0/fjcore.hh)
set(GAMBIT_BASIC_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:fjcore>)

#contrib/MassSpectra; include only if SpecBit is in use
set (FS_DIR "${PROJECT_SOURCE_DIR}/contrib/MassSpectra/flexiblesusy")
if(";${GAMBIT_BITS};" MATCHES ";SpecBit;")

  set (EXCLUDE_FLEXIBLESUSY FALSE)

  # Always use -O2 for flexiblesusy to ensure fast spectrum generation.
  set(FS_CXX_FLAGS "${GAMBIT_CXX_FLAGS} -Wno-missing-field-initializers")
  set(FS_Fortran_FLAGS "${GAMBIT_Fortran_FLAGS}")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FS_CXX_FLAGS "${FS_CXX_FLAGS} -O2")
    set(FS_Fortran_FLAGS "${FS_Fortran_FLAGS} -O2")
  endif()

  # Determine compiler libraries needed by flexiblesusy.
  if(CMAKE_Fortran_COMPILER MATCHES "gfortran*")
    set(flexiblesusy_extralibs "${flexiblesusy_extralibs} -lgfortran -lm")
  elseif(CMAKE_Fortran_COMPILER MATCHES "g77" OR CMAKE_Fortran_COMPILER MATCHES "f77")
    set(flexiblesusy_extralibs "${flexiblesusy_extralibs} -lg2c -lm")
  elseif(CMAKE_Fortran_COMPILER MATCHES "ifort")
    set(flexiblesusy_extralibs "${flexiblesusy_extralibs} -lifcore -limf -ldl -lintlc -lsvml")
  endif()
  #message("${Yellow}-- Determined FlexibleSUSY compiler library dependencies: ${flexiblesusy_extralibs}${ColourReset}")
  set(flexiblesusy_LDFLAGS "${flexiblesusy_LDFLAGS} ${flexiblesusy_extralibs}")

  # Silence the deprecated-declarations warnings comming from Eigen3
  set_compiler_warning("no-deprecated-declarations" FS_CXX_FLAGS)

  # Silence the unused parameter and variable warnings comming from FlexibleSUSY
  set_compiler_warning("no-unused-parameter" FS_CXX_FLAGS)
  set_compiler_warning("no-unused-variable" FS_CXX_FLAGS)

  # FlexibleSUSY configure options
  set(FS_OPTIONS ${FS_OPTIONS}
       --with-cxx=${CMAKE_CXX_COMPILER}
       --with-cxxflags=${FS_CXX_FLAGS}
       --with-shared-ldflags=${OpenMP_CXX_FLAGS}
       --with-fc=${CMAKE_Fortran_COMPILER}
       --with-fflags=${FS_Fortran_FLAGS}
       --with-eigen-incdir=${EIGEN3_INCLUDE_DIR}
       --with-boost-libdir=${Boost_LIBRARY_DIR}
       --with-boost-incdir=${Boost_INCLUDE_DIR}
       --with-lapack-libs=${LAPACK_LINKLIBS}
       --with-blas-libs=${LAPACK_LINKLIBS}
       --disable-librarylink
      #--enable-verbose flag causes verbose output at runtime as well. Maybe set it dynamically somehow in future.
     )

  # Set the models (spectrum generators) existing in flexiblesusy (could autogen this, but that would build some things we don't need)
  set(ALL_FS_MODELS CMSSM MSSM MSSMatMGUT MSSM_mAmu MSSMatMSUSY_mAmu MSSMatMGUT_mAmu MSSMEFTHiggs MSSMEFTHiggs_mAmu MSSMatMSUSYEFTHiggs_mAmu SingletDMZ3 SingletDM)

  # Check if there has been command line instructions to only build with certain models. Default is to build everything!
  if(BUILD_FS_MODELS AND NOT ";${BUILD_FS_MODELS};" MATCHES ";ALL_FS_MODELS;")
    # Use whatever the user has supplied!
  else()
    set(BUILD_FS_MODELS ${ALL_FS_MODELS})
  endif()

  #set(BUILD_FS_MODELS CMSSM MSSM MSSMatMGUT)
  set(EXCLUDED_FS_MODELS "")

  # Check that all the models the user asked for are in fact valid models
  foreach(MODELNAME ${BUILD_FS_MODELS})
    if(";${ALL_FS_MODELS};" MATCHES ";${MODELNAME};")
      # everything ok
    else()
      message(FATAL_ERROR "Configuring FlexibleSUSY failed. You asked for a model which is not known to GAMBIT! (saw request for ${MODELNAME} via -D BUILD_FS_MODELS=<list> flag).\n The models currently known to GAMBIT are as follows, please make sure your list of choices comes from this list, separated by semicolons: ${ALL_FS_MODELS}")
    endif()
  endforeach()

  # Loop through ALL_FS_MODELS and define C preprocessor tokens which tell us which ones have and haven't been built, so that we can check what models are available within the code.
  foreach(MODELNAME ${ALL_FS_MODELS})
    if(";${BUILD_FS_MODELS};" MATCHES ";${MODELNAME};")
      add_definitions(-DFS_MODEL_${MODELNAME}_IS_BUILT=1) # i.e. it IS available
    else()
      add_definitions(-DFS_MODEL_${MODELNAME}_IS_BUILT=0) # this model is turned off
      list(APPEND EXCLUDED_FS_MODELS ${MODELNAME})
    endif()
  endforeach()

  # Explain how to build each of the flexiblesusy spectrum generators we need.  Configure now, serially, to prevent parallel build issues.
  string (REPLACE ";" "," BUILD_FS_MODELS_COMMAS "${BUILD_FS_MODELS}")
  string (REPLACE ";" "," EXCLUDED_FS_MODELS_COMMAS "${EXCLUDED_FS_MODELS}")
   set(config_command ./configure ${FS_OPTIONS} --with-models=${BUILD_FS_MODELS_COMMAS})
  add_custom_target(configure-flexiblesusy COMMAND cd ${FS_DIR} && ${config_command})
  message("${Yellow}-- Configuring FlexibleSUSY for models: ${BoldYellow}${BUILD_FS_MODELS_COMMAS}${ColourReset}")
  if (NOT "${EXCLUDED_FS_MODELS_COMMAS}" STREQUAL "")
    message("${Red}   Switching OFF FlexibleSUSY support for models: ${BoldRed}${EXCLUDED_FS_MODELS_COMMAS}${ColourReset}")
  endif()
  #message("${Yellow}-- Using configure command \n${config_command}${output}${ColourReset}" )
  execute_process(COMMAND ${config_command}
                  WORKING_DIRECTORY ${FS_DIR}
                  RESULT_VARIABLE result
                  OUTPUT_VARIABLE output
                 )
  if (NOT "${result}" STREQUAL "0")
     message("${BoldRed}-- Configuring FlexibleSUSY failed.  Here's what I tried to do:\n${config_command}\n${output}${ColourReset}" )
     message(FATAL_ERROR "Configuring FlexibleSUSY failed." )
  endif()
  set(rmstring "${CMAKE_BINARY_DIR}/flexiblesusy-prefix/src/flexiblesusy-stamp/flexiblesusy")
  execute_process(COMMAND ${CMAKE_COMMAND} -E touch ${rmstring}-configure)

  message("${Yellow}-- Configuring FlexibleSUSY - done.${ColourReset}")

  # Add FlexibleSUSY as an external project
  ExternalProject_Add(flexiblesusy
    SOURCE_DIR ${FS_DIR}
    BUILD_IN_SOURCE 1
    BUILD_COMMAND $(MAKE) alllib
    CONFIGURE_COMMAND ${config_command}
    INSTALL_COMMAND ""
  )

  # Set linking commands.  Link order matters! The core flexiblesusy libraries need to come after the model libraries but before the other link flags.
  # for v 1.5.1 add "-L${FS_DIR}/legacy -llegacy"  after "-lflexiblesusy"
  set(flexiblesusy_LDFLAGS "-L${FS_DIR}/src -lflexisusy ${flexiblesusy_LDFLAGS}")
  foreach(_MODEL ${BUILD_FS_MODELS})
    set(flexiblesusy_LDFLAGS "-L${FS_DIR}/models/${_MODEL} -l${_MODEL} ${flexiblesusy_LDFLAGS}")
  endforeach()

  # Set up include paths
  include_directories("${FS_DIR}/..")
  include_directories("${FS_DIR}/src")
  include_directories("${FS_DIR}/legacy")
  include_directories("${FS_DIR}/config")
  include_directories("${FS_DIR}/slhaea")
  # Dig through flexiblesusy "models" directory and add all subdirectories to the include list
  # (these contain the headers for the generated spectrum generators)
  foreach(_MODEL ${BUILD_FS_MODELS})
    include_directories("${FS_DIR}/models/${_MODEL}")
  endforeach()

  # Strip out leading and trailing whitespace
  string(STRIP "${flexiblesusy_LDFLAGS}" flexiblesusy_LDFLAGS)

else()

  set (EXCLUDE_FLEXIBLESUSY TRUE)

endif()


# Add clean info
add_custom_target(clean-flexiblesusy COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-configure ${rmstring}-build ${rmstring}-install ${rmstring}-done
                                     COMMAND [ -e ${FS_DIR} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} clean) || true)
add_custom_target(distclean-flexiblesusy COMMAND cd ${FS_DIR} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} distclean) || true)
add_custom_target(nuke-flexiblesusy)
add_dependencies(distclean-flexiblesusy clean-flexiblesusy)
add_dependencies(nuke-flexiblesusy distclean-flexiblesusy)
add_dependencies(distclean distclean-flexiblesusy)
add_dependencies(nuke-all nuke-flexiblesusy)
