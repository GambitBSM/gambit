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

# Define the newline strings to use for OSX-safe substitution.
# This can be moved into externals.cmake if ever it is no longer used in this file.
set(nl "___totally_unlikely_to_occur_naturally___")
set(true_nl \"\\n\")

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

#contrib/yaml-cpp-0.6.2
set(yaml_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.6.2/include)
include_directories("${yaml_INCLUDE_DIR}")
add_definitions(-DYAML_CPP_DLL)
add_subdirectory(${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.6.2 EXCLUDE_FROM_ALL)


#contrib/RestFrames; include only if ColliderBit is in use, ROOT is found and WITH_RESTFRAMES=True (default).
set(restframes_VERSION "1.0.2")
set(restframes_CONTRIB_DIR "${PROJECT_SOURCE_DIR}/contrib/RestFrames-${restframes_VERSION}")
if(NOT ";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  message("${BoldCyan} X Excluding RestFrames from GAMBIT configuration. (ColliderBit is not in use.)${ColourReset}")
  set(EXCLUDE_RESTFRAMES TRUE)
elseif(DEFINED WITH_RESTFRAMES AND NOT WITH_RESTFRAMES)
  message("${BoldCyan} X Excluding RestFrames from GAMBIT configuration. (WITH_RESTFRAMES is set to False.)${ColourReset}")
  message("   RestFrames-dependent analyses in ColliderBit will be deactivated.")
  set(EXCLUDE_RESTFRAMES TRUE)
elseif(NOT ROOT_FOUND)
  message("${BoldCyan} X Excluding RestFrames from GAMBIT configuration. (ROOT was not found.)${ColourReset}")
  message("   RestFrames-dependent analyses in ColliderBit will be deactivated.")
  set(EXCLUDE_RESTFRAMES TRUE)
else() # OK, let's include RestFrames then
  message("-- RestFrames-dependent analyses in ColliderBit will be activated.")
  set(EXCLUDE_RESTFRAMES FALSE)
  # Check if the RestFrames library already exists and print info message
  unset(RestFrames_LIBRARY CACHE)
  find_library(RestFrames_LIBRARY RestFrames ${restframes_CONTRIB_DIR}/lib/)
  if(RestFrames_LIBRARY STREQUAL "RestFrames_LIBRARY-NOTFOUND")
    message("   RestFrames library not found. RestFrames v${restframes_VERSION} will be downloaded and installed when building GAMBIT.")
  else()
    message("   Found RestFrames library: ${RestFrames_LIBRARY}")
  endif()
endif()

# Add RestFrames as an external project that GAMBIT can depend on
if(NOT EXCLUDE_RESTFRAMES)
  set(name "restframes")
  set(ver "${restframes_VERSION}")
  set(dir "${restframes_CONTRIB_DIR}")
  set(patch "${PROJECT_SOURCE_DIR}/contrib/patches/${name}/${ver}/patch_${name}_${ver}.dif")
  set(RESTFRAMES_LDFLAGS "-L${dir}/lib -lRestFrames")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${dir}/lib")
  add_install_name_tool_step(${name} ${dir}/lib libRestFrames.so)
  include_directories("${dir}" "${dir}/inc")
  ExternalProject_Add(restframes
    DOWNLOAD_COMMAND git clone https://github.com/crogan/RestFrames ${dir}
             COMMAND ${CMAKE_COMMAND} -E chdir ${dir} git checkout -q v${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure -prefix=${dir}
    # Patch RestFrames to set the CPLUS_INCLUDE_PATH environment variable correctly when RestFrames is loaded.
    # This avoids having to run setup_RestFrames.sh.
    PATCH_COMMAND patch -p1 < ${patch}
          COMMAND sed ${dashi} -e "s|____replace_with_GAMBIT_version____|${GAMBIT_VERSION_FULL}|g" src/RFBase.cc src/RFBase.cc
          COMMAND sed ${dashi} -e "s|____replace_with_RestFrames_path____|${dir}|g" src/RFBase.cc
    BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
    INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} install
    )
  # Add clean-restframes and nuke-restframes
  set(rmstring "${CMAKE_BINARY_DIR}/restframes-prefix/src/restframes-stamp/restframes")
  add_custom_target(clean-restframes COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-configure ${rmstring}-build ${rmstring}-install ${rmstring}-done
    COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} distclean) || true)
  add_dependencies(distclean clean-restframes)
  add_custom_target(nuke-restframes COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-download ${rmstring}-mkdir ${rmstring}-patch ${rmstring}-update
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${dir}" || true)
  add_dependencies(nuke-restframes clean-restframes)
  add_dependencies(nuke-contrib nuke-restframes)
  add_dependencies(nuke-all nuke-restframes)
endif()


#contrib/fjcore-3.2.0
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
  set(FS_CXX_FLAGS "${BACKEND_CXX_FLAGS} -Wno-missing-field-initializers")
  set(FS_Fortran_FLAGS "${BACKEND_Fortran_FLAGS}")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FS_CXX_FLAGS "${FS_CXX_FLAGS} -O2")
    set(FS_Fortran_FLAGS "${FS_Fortran_FLAGS} -O2")
  endif()

  # Determine compiler libraries needed by flexiblesusy.
  if(CMAKE_Fortran_COMPILER MATCHES "gfortran*")
    set(flexiblesusy_compilerlibs "-lgfortran -lm")
  elseif(CMAKE_Fortran_COMPILER MATCHES "g77" OR CMAKE_Fortran_COMPILER MATCHES "f77")
    set(flexiblesusy_compilerlibs "-lg2c -lm")
  elseif(CMAKE_Fortran_COMPILER MATCHES "ifort")
    set(flexiblesusy_compilerlibs "-lifcore -limf -ldl -lintlc -lsvml")
  endif()
  set(flexiblesusy_LDFLAGS ${flexiblesusy_LDFLAGS} ${flexiblesusy_compilerlibs})

  # Silence the deprecated-declarations warnings comming from Eigen3
  set_compiler_warning("no-deprecated-declarations" FS_CXX_FLAGS)

  # Silence the unused parameter and variable warnings comming from FlexibleSUSY
  set_compiler_warning("no-unused-parameter" FS_CXX_FLAGS)
  set_compiler_warning("no-unused-variable" FS_CXX_FLAGS)

  # Construct the command to create the shared library
  set(FS_SO_LINK_COMMAND "${CMAKE_CXX_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} -shared -o")

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
       --enable-shared-libs
       --with-shared-lib-ext=.so
       --with-shared-lib-cmd=${FS_SO_LINK_COMMAND}
      #--enable-verbose flag causes verbose output at runtime as well. Maybe set it dynamically somehow in future.
     )

  # Set the models (spectrum generators) existing in flexiblesusy (could autogen this, but that would build some things we don't need)
  set(ALL_FS_MODELS MDM CMSSM MSSM MSSMatMGUT MSSM_mAmu MSSMatMSUSY_mAmu MSSMatMGUT_mAmu MSSMEFTHiggs MSSMEFTHiggs_mAmu MSSMatMSUSYEFTHiggs_mAmu MSSMatMGUTEFTHiggs MSSMatMGUTEFTHiggs_mAmu ScalarSingletDM_Z3 ScalarSingletDM_Z2)
  # Check if there has been command line instructions to only build with certain models. Default is to build everything!
  if(BUILD_FS_MODELS AND NOT ";${BUILD_FS_MODELS};" MATCHES ";ALL_FS_MODELS;")
    # Use whatever the user has supplied!
  else()
    set(BUILD_FS_MODELS ${ALL_FS_MODELS})
  endif()

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
    CONFIGURE_COMMAND ${config_command}
    BUILD_COMMAND $(MAKE) alllib
    INSTALL_COMMAND ""
  )

  # Set linking commands.  Link order matters! The core flexiblesusy libraries need to come after the model libraries but before the other link flags.
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${FS_DIR}/src")
  set(flexiblesusy_LDFLAGS "-L${FS_DIR}/src -lflexisusy ${flexiblesusy_LDFLAGS}")
  add_install_name_tool_step(flexiblesusy ${FS_DIR}/src libflexisusy.so)
  foreach(_MODEL ${BUILD_FS_MODELS})
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${FS_DIR}/models/${_MODEL}")
    set(flexiblesusy_LDFLAGS "-L${FS_DIR}/models/${_MODEL} -l${_MODEL} ${flexiblesusy_LDFLAGS}")
    add_install_name_tool_step(flexiblesusy ${FS_DIR}/models/${_MODEL} lib${_MODEL}.so)
  endforeach()

  # Strip out leading and trailing whitespace
  string(STRIP "${flexiblesusy_LDFLAGS}" flexiblesusy_LDFLAGS)

  # Set up include paths
  include_directories("${FS_DIR}/..")
  include_directories("${FS_DIR}/src")
  include_directories("${FS_DIR}/config")
  include_directories("${FS_DIR}/slhaea")
  # Dig through flexiblesusy "models" directory and add all subdirectories to the include list
  # (these contain the headers for the generated spectrum generators)
  foreach(_MODEL ${BUILD_FS_MODELS})
    include_directories("${FS_DIR}/models/${_MODEL}")
  endforeach()

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
