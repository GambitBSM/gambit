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
# \author Tomas Gonzalo
#         (tomas.gonzalo@monash.edu)
# \dae 2019 June
#
#************************************************

include(ExternalProject)

# Define the newline strings to use for OSX-safe substitution.
# This can be moved into externals.cmake if ever it is no longer used in this file.
set(nl "___totally_unlikely_to_occur_naturally___")
set(true_nl \"\\n\")

# Define the download command to use for contributed packages
set(DL_CONTRIB "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${CMAKE_BINARY_DIR}" "${CMAKE_COMMAND}" "${CMAKE_DOWNLOAD_FLAGS}")

# Define a series of functions and macros to be used for cleaning ditched components and adding nuke and clean targets for contributed codes
macro(get_paths package build_path clean_stamps nuke_stamps)
  set(stamp_path "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
  set(${build_path} "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-build")
  set(${clean_stamps} ${stamp_path}-configure ${stamp_path}-build ${stamp_path}-install ${stamp_path}-done)
  set(${nuke_stamps} ${stamp_path}-download ${stamp_path}-mkdir ${stamp_path}-patch ${stamp_path}-update)
endmacro()

function(nuke_ditched_contrib_content package dir)
  get_paths(${package} build_path clean-stamps nuke-stamps)
  execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory "${build_path}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory "${dir}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E remove -f ${clean-stamps} ${nuke-stamps})
endfunction()

function(add_contrib_clean_and_nuke package dir clean)
  get_paths(${package} build_path clean-stamps nuke-stamps)
  add_custom_target(clean-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${clean-stamps}
                                     COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && ${MAKE_SERIAL} ${clean}) || true
                                     COMMAND [ -e ${build_path} ] && cd ${build_path} && ([ -e makefile ] || [ -e Makefile ] && ${MAKE_SERIAL} ${clean}) || true)
  add_dependencies(distclean clean-${package})
  add_custom_target(nuke-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${nuke-stamps}
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory "${build_path}"
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory "${dir}")
  add_dependencies(nuke-${package} clean-${package})
  add_dependencies(nuke-contrib nuke-${package})
  add_dependencies(nuke-all nuke-${package})
endfunction()

#contrib/preload
set(name "gambit_preload")
set(dir "${CMAKE_BINARY_DIR}/contrib")
add_library(${name} SHARED "${PROJECT_SOURCE_DIR}/contrib/preload/gambit_preload.cpp")
target_include_directories(${name} PRIVATE "${PROJECT_SOURCE_DIR}/cmake/include" "${PROJECT_SOURCE_DIR}/Utils/include")
set_target_properties(${name} PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${dir}"
  LIBRARY_OUTPUT_DIRECTORY "${dir}"
  RUNTIME_OUTPUT_DIRECTORY "${dir}"
)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(gambit_preload_LDFLAGS "-L${dir} -lgambit_preload")
else()
  set(gambit_preload_LDFLAGS "-L${dir} -Wl,--no-as-needed -lgambit_preload")
endif()
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${dir}")

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

#contrib/RestFrames; include only if ColliderBit is in use, ROOT is found and WITH_RESTFRAMES=ON.
option(WITH_RESTFRAMES "Compile with RestFrames enabled" OFF)
if(NOT WITH_RESTFRAMES)
  message("${BoldCyan} X RestFrames is deactivated. Set -DWITH_RESTFRAMES=ON to activate RestFrames.${ColourReset}")
elseif(NOT ";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  message("${BoldCyan} X ColliderBit is not in use: excluding RestFrames from GAMBIT configuration.${ColourReset}")
  set(WITH_RESTFRAMES OFF)
elseif(NOT ROOT_FOUND)
  message("${BoldCyan} X Not compiling with ROOT support: excluding RestFrames from GAMBIT configuration.${ColourReset}")
  set(WITH_RESTFRAMES OFF)
endif()

set(name "restframes")
set(ver "1.0.2")
set(dir "${PROJECT_SOURCE_DIR}/contrib/RestFrames-${ver}")
if(WITH_RESTFRAMES)
  message("-- RestFrames-dependent analyses in ColliderBit will be activated.")
  message("   RestFrames v${ver} will be downloaded and installed when building GAMBIT.")
  set(EXCLUDE_RESTFRAMES FALSE)
else()
  message("   RestFrames-dependent analyses in ColliderBit will be deactivated.")
  nuke_ditched_contrib_content(${name} ${dir})
  set(EXCLUDE_RESTFRAMES TRUE)
endif()

if(NOT EXCLUDE_RESTFRAMES)
  set(RESTFRAMES_CPP "${CMAKE_C_COMPILER} -E")
  set(RESTFRAMES_CXXCPP "${CMAKE_CXX_COMPILER} -E")
  set(RESTFRAMES_LDFLAGS "-L${dir}/lib -lRestFrames")
  set(RESTFRAMES_INCLUDE "${dir}/inc")
  include_directories(${RESTFRAMES_INCLUDE})
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${dir}/lib")
  set(RESTFRAMES_CONFIG_LDFLAGS "-L${CMAKE_BINARY_DIR}/contrib -Wl,-rpath,${CMAKE_BINARY_DIR}/contrib")
  # OpenMP flags don't play nicely with clang and RestFrames' antiquated libtoolized build system.
  string(REGEX REPLACE "-Xclang -fopenmp" "" RESTFRAMES_C_FLAGS "${BACKEND_C_FLAGS}")
  string(REGEX REPLACE "-Xclang -fopenmp" "" RESTFRAMES_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(RESTFRAMES_CONFIG_LIBS "${CMAKE_SHARED_LINKER_FLAGS} -lgambit_preload")
  else()
    set(RESTFRAMES_CONFIG_LIBS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-as-needed -lgambit_preload")
  endif()
  ExternalProject_Add(${name}
    DOWNLOAD_COMMAND git clone https://github.com/crogan/RestFrames ${dir}
             COMMAND ${CMAKE_COMMAND} -E chdir ${dir} git checkout -q v${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure -prefix=${dir} CC=${CMAKE_C_COMPILER} CFLAGS=${RESTFRAMES_C_FLAGS} CPP=${RESTFRAMES_CPP} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${RESTFRAMES_CXX_FLAGS} CXXCPP=${RESTFRAMES_CXXCPP} LDFLAGS=${RESTFRAMES_CONFIG_LDFLAGS} LIBS=${RESTFRAMES_CONFIG_LIBS}
              COMMAND sed ${dashi} -e "s|.(ROOTAUXCXXFLAGS) .(ROOTCXXFLAGS)||" src/Makefile
    BUILD_COMMAND ${MAKE_PARALLEL}
    INSTALL_COMMAND ${MAKE_PARALLEL} install
    )
  # Force the preload library to come before RestFrames
  add_dependencies(${name} gambit_preload)
  # Add install name tool step for OSX
  add_install_name_tool_step(${name} ${dir}/lib libRestFrames.dylib)
  # Add clean-restframes and nuke-restframes
  add_contrib_clean_and_nuke(${name} ${dir} distclean)
endif()

#contrib/LHEF
set(LHEF_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/contrib/LHEF")
include_directories("${LHEF_INCLUDE_DIR}")

#contrib/HepMC3; include only if ColliderBit is in use and WITH_HEPMC=ON.
option(WITH_HEPMC "Compile with HepMC enabled" OFF)
if(NOT WITH_HEPMC)
  message("${BoldCyan} X HepMC is deactivated. Set -DWITH_HEPMC=ON to activate HepMC.${ColourReset}")
elseif(NOT ";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  message("${BoldCyan} X ColliderBit is not in use: excluding HepMC from GAMBIT configuration.${ColourReset}")
  set(WITH_HEPMC OFF)
endif()

set(name "hepmc")
set(ver "3.2.5")
set(HEPMC_PATH "${PROJECT_SOURCE_DIR}/contrib/HepMC3-${ver}")
if(WITH_HEPMC)
  message("-- HepMC-dependent functions in ColliderBit will be activated.")
  message("   HepMC v${ver} will be downloaded and installed when building GAMBIT.")
  message("   ColliderBit Solo (CBS) will be activated.")
  if(EXISTS "${PROJECT_SOURCE_DIR}/Backends/include/gambit/Backends/backend_types/Pythia_8_212/abstract_GAMBIT_hepmc_writer.h")
    message("   Pythia can now drop HepMC files.")
  else()
    message("${BoldRed}   Pythia has already been compiled without HepMC so the main gambit build will fail. Please nuke Pythia before compiling gambit.${ColourReset}")
  endif()
  message("   Backends depending on HepMC will be enabled.")
  if(NOT ROOT_FOUND)
    message("   No ROOT found, ROOT-IO in HepMC will be deactivated.")
    set(HEPMC3_ROOTIO OFF)
  else()
    set(HEPMC3_ROOTIO ON)
  endif()
  set(EXCLUDE_HEPMC FALSE)
else()
  message("   HepMC-dependent functions in ColliderBit will be deactivated.")
  message("   ColliderBit Solo (CBS) will be deactivated.")
  message("   Pythia will not drop HepMC files.")
  message("   Backends depending on HepMC (e.g. Rivet) will be disabled.")
  nuke_ditched_contrib_content(${name} ${HEPMC_PATH})
  set(EXCLUDE_HEPMC TRUE)
endif()

if(NOT EXCLUDE_HEPMC)
  set(lib "HepMC3")
  set(md5 "d3079a7ffcc926b34c5ad2868ed6d8f0")
  set(dl "https://hepmc.web.cern.ch/hepmc/releases/HepMC3-${ver}.tar.gz")
  include_directories("${HEPMC_PATH}/local/include")

  set(HEPMC_LDFLAGS "-L${HEPMC_PATH}/local/lib -l${lib}")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${HEPMC_PATH}/local/lib")
  set(HEPMC_CXX_FLAGS "${BACKEND_CXX_FLAGS}")

  # Silence some compiler warnings coming from HepMC
  set_compiler_warning("no-unused-parameter" HEPMC_CXX_FLAGS)
  set_compiler_warning("no-deprecated-copy" HEPMC_CXX_FLAGS)
  set_compiler_warning("no-sign-compare" HEPMC_CXX_FLAGS)

  ExternalProject_Add(${name}
    DOWNLOAD_COMMAND ${DL_CONTRIB} ${dl} ${md5} ${HEPMC_PATH} ${name} ${ver}
    SOURCE_DIR ${HEPMC_PATH}
    CMAKE_COMMAND ${CMAKE_COMMAND} ..
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=${HEPMC_CXX_FLAGS} -DHEPMC3_ENABLE_ROOTIO=${HEPMC3_ROOTIO} -DCMAKE_INSTALL_PREFIX=${HEPMC_PATH}/local -DCMAKE_INSTALL_LIBDIR=${HEPMC_PATH}/local/lib -DHEPMC3_ENABLE_PYTHON=OFF -DHEPMC3_ENABLE_SEARCH=OFF -DHEPMC3_BUILD_STATIC_LIBS=OFF
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}
    INSTALL_COMMAND ${CMAKE_INSTALL_COMMAND}
    )

  # Add clean-hepmc and nuke-hepmc
  add_contrib_clean_and_nuke(${name} ${HEPMC_PATH} clean)
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

#contrib/multimin
set(multimin_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/contrib/multimin/include")
include_directories("${multimin_INCLUDE_DIR}")
add_gambit_library(multimin OPTION OBJECT
                          SOURCES ${PROJECT_SOURCE_DIR}/contrib/multimin/src/multimin.cpp
                          HEADERS ${PROJECT_SOURCE_DIR}/contrib/multimin/include/multimin/multimin.hpp)
set(GAMBIT_BASIC_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:multimin>)


#contrib/MassSpectra; include only if SpecBit is in use and if
#BUILD_FS_MODELS is set to something other than "" or "None" or "none"
set (FS_DIR "${PROJECT_SOURCE_DIR}/contrib/MassSpectra/flexiblesusy")
# Set the models (spectrum generators) existing in flexiblesusy (could autogen this, but that would build some things we don't need).
# Doing this out here so that we can use them in messages even when FS is excluded
set(ALL_FS_MODELS MDM CMSSM MSSM MSSMatMGUT MSSM_mAmu MSSMatMSUSY_mAmu MSSMatMGUT_mAmu MSSMEFTHiggs MSSMEFTHiggs_mAmu MSSMatMSUSYEFTHiggs_mAmu MSSMatMGUTEFTHiggs MSSMatMGUTEFTHiggs_mAmu ScalarSingletDM_Z3 ScalarSingletDM_Z2)
if(";${GAMBIT_BITS};" MATCHES ";SpecBit;")
  set (EXCLUDE_FLEXIBLESUSY FALSE)

  # Always use -O2 for flexiblesusy to ensure fast spectrum generation.
  set(FS_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
  set(FS_Fortran_FLAGS "${BACKEND_Fortran_FLAGS}")
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FS_CXX_FLAGS "${FS_CXX_FLAGS} -O2")
    set(FS_Fortran_FLAGS "${FS_Fortran_FLAGS} -O2")
  endif()

  # Determine compiler libraries needed by flexiblesusy.
  if(CMAKE_Fortran_COMPILER MATCHES "gfortran*")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
      find_library(GFORTRAN_LIBRARY NAMES gfortran)
      if(GFORTRAN_LIBRARY STREQUAL "GFORTRAN_LIBRARY-NOTFOUND")
        execute_process(COMMAND "${CMAKE_Fortran_COMPILER}" "-v" ERROR_VARIABLE GFORTRAN_V_OUTPUT)
        string(REGEX MATCH "--libdir=[^\t\n ]+" GFORTRAN_LIB_DIR_STR "${GFORTRAN_V_OUTPUT}")
        string(REGEX REPLACE "--libdir=([^\t\n ]+)" "\\1" GFORTRAN_LIB_DIR_STR "${GFORTRAN_LIB_DIR_STR}")
        find_library(GFORTRAN_LIBRARY NAMES gfortran PATHS "${GFORTRAN_LIB_DIR_STR}")
        if(GFORTRAN_LIBRARY STREQUAL "GFORTRAN_LIBRARY-NOTFOUND")
          message(FATAL_ERROR "Could not find libgfortran.")
        endif()
      endif()
      message(STATUS "Found libgfortran at ${GFORTRAN_LIBRARY}.")
      set(flexiblesusy_compilerlibs "${GFORTRAN_LIBRARY} -lm")
    else()
      set(flexiblesusy_compilerlibs "-lgfortran -lm")
    endif()
  elseif(CMAKE_Fortran_COMPILER MATCHES "g77" OR CMAKE_Fortran_COMPILER MATCHES "f77")
    set(flexiblesusy_compilerlibs "-lg2c -lm")
  elseif(CMAKE_Fortran_COMPILER MATCHES "ifort")
    set(flexiblesusy_compilerlibs "-lifcore -limf -ldl -lintlc -lsvml")
  endif()
  set(flexiblesusy_LDFLAGS ${flexiblesusy_LDFLAGS} ${flexiblesusy_compilerlibs})

  # Silence the deprecated-declarations warnings coming from Eigen3
  set_compiler_warning("no-deprecated-declarations" FS_CXX_FLAGS)
  set_compiler_warning("no-deprecated-copy" FS_CXX_FLAGS)

  # Silence the mass of compiler warnings coming from FlexibleSUSY
  set_compiler_warning("no-unused-parameter" FS_CXX_FLAGS)
  set_compiler_warning("no-unused-variable" FS_CXX_FLAGS)
  set_compiler_warning("no-unused-private-field" FS_CXX_FLAGS)
  set_compiler_warning("no-unused-lambda-capture" FS_CXX_FLAGS)
  set_compiler_warning("no-missing-field-initializers" FS_CXX_FLAGS)
  set_compiler_warning("no-sign-compare" FS_CXX_FLAGS)
  set_compiler_warning("no-mismatched-tags" FS_CXX_FLAGS)
  set_compiler_warning("no-unneeded-internal-declaration" FS_CXX_FLAGS)

  # Construct the command to create the shared library
  set(FS_SO_LINK_COMMAND "${CMAKE_CXX_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -o")

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
       --with-gsl-config=${GSL_CONFIG_EXECUTABLE}
      #--enable-verbose flag causes verbose output at runtime as well. Maybe set it dynamically somehow in future.
     )

  # Check for command line instructions to build ALL models
  if(   ";${BUILD_FS_MODELS};" MATCHES ";ALL;"
     OR ";${BUILD_FS_MODELS};" MATCHES ";All;"
     OR ";${BUILD_FS_MODELS};" MATCHES ";all;"
    )
    set(BUILD_FS_MODELS ${ALL_FS_MODELS})
  elseif(";${BUILD_FS_MODELS};" MATCHES ";None;"
      OR ";${BUILD_FS_MODELS};" MATCHES ";none;"
      OR ";${BUILD_FS_MODELS};" MATCHES ";;"
      )
    set(BUILD_FS_MODELS "")
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

  # Explain how to build each of the flexiblesusy spectrum generators we need.
  string (REPLACE ";" "," BUILD_FS_MODELS_COMMAS "${BUILD_FS_MODELS}")
  string (REPLACE ";" "," EXCLUDED_FS_MODELS_COMMAS "${EXCLUDED_FS_MODELS}")
  set(config_command ./configure ${FS_OPTIONS} --with-models=${BUILD_FS_MODELS_COMMAS})

  # Add FlexibleSUSY as an external project
  ExternalProject_Add(flexiblesusy
    SOURCE_DIR ${FS_DIR}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${config_command}
    BUILD_COMMAND $(MAKE) alllib
    INSTALL_COMMAND ""
  )

  # Add clean info
  set(rmstring "${CMAKE_BINARY_DIR}/flexiblesusy-prefix/src/flexiblesusy-stamp/flexiblesusy")
  add_custom_target(clean-flexiblesusy COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-configure ${rmstring}-build ${rmstring}-install ${rmstring}-done
                                       COMMAND [ -e ${FS_DIR} ] && cd ${FS_DIR} && ([ -e makefile ] || [ -e Makefile ] && ${MAKE_SERIAL} clean) || true)
  add_custom_target(distclean-flexiblesusy COMMAND cd ${FS_DIR} && ([ -e makefile ] || [ -e Makefile ] && ${MAKE_SERIAL} distclean) || true)
  add_custom_target(nuke-flexiblesusy)
  add_dependencies(distclean-flexiblesusy clean-flexiblesusy)
  add_dependencies(nuke-flexiblesusy distclean-flexiblesusy)
  add_dependencies(distclean distclean-flexiblesusy)
  add_dependencies(nuke-all nuke-flexiblesusy)

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

  # Configure now, serially, to prevent parallel build issues.
  if(NOT "${BUILD_FS_MODELS}" STREQUAL "")
      message("${Yellow}-- Configuring FlexibleSUSY for models: ${BoldYellow}${BUILD_FS_MODELS_COMMAS}${ColourReset}")
      if (NOT "${EXCLUDED_FS_MODELS_COMMAS}" STREQUAL "")
          message("${BoldCyan}   Switching OFF FlexibleSUSY support for models: ${EXCLUDED_FS_MODELS_COMMAS}${ColourReset}")
      endif()
  else()
      message("${BoldCyan} X Switching OFF FlexibleSUSY support for ALL models.${ColourReset}")
      message("   If you want to activate support for any model(s) please list them in the cmake flag -DBUILD_FS_MODELS=<list> as a semi-colon separated list.")
      message("   Buildable models are: ${ALL_FS_MODELS}")
      message("   To build ALL models use ALL, All, or all.")
      message("   To build NO models use None or none.")
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
  execute_process(COMMAND ${CMAKE_COMMAND} -E touch ${rmstring}-configure)
  message("${Yellow}-- Configuring FlexibleSUSY - done.${ColourReset}")

else()

  set (EXCLUDE_FLEXIBLESUSY TRUE)

endif()
