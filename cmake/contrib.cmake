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
# \dae 2019 June, Oct
#
# \author Tomasz Procter
#         (t.procter.1@research.gla.ac.uk)
# \date June 2021
#
# \author Pengxuan Zhu
#         (pengxuan.zhu@adelaide.edu.au)
# \date 2026 Aug
#
#************************************************

include(ExternalProject)

# Define the newline strings to use for OSX-safe substitution.
# This can be moved into externals.cmake if ever it is no longer used in this file.
set(nl "___totally_unlikely_to_occur_naturally___")
set(true_nl \"\\n\")

# Define the download command to use for contributed packages
set(DL_CONTRIB "${PROJECT_SOURCE_DIR}/cmake/scripts/safe_dl.sh" "${PROJECT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" "${CMAKE_COMMAND}" "${CMAKE_DOWNLOAD_FLAGS}")

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
target_include_directories(${name} PRIVATE "${PROJECT_SOURCE_DIR}/cmake/include" "${PROJECT_SOURCE_DIR}/Core/include" "${PROJECT_SOURCE_DIR}/Utils/include")
set_target_properties(${name} PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${dir}"
  LIBRARY_OUTPUT_DIRECTORY "${dir}"
  RUNTIME_OUTPUT_DIRECTORY "${dir}"
)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(gambit_preload_LDFLAGS "-L${dir}" "-lgambit_preload")
else()
  set(gambit_preload_LDFLAGS "-L${dir}" "-Wl,--no-as-needed" "-lgambit_preload")
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
add_dependencies(contrib mkpath)

#contrib/yaml-cpp-0.6.2
set(yaml_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.6.2/include)
include_directories(SYSTEM "${yaml_INCLUDE_DIR}")
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
set(RESTFRAMES_VERSION "${ver}")
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
  set(RESTFRAMES_LDFLAGS "-L${dir}/lib" "-lRestFrames")
  set(RESTFRAMES_INCLUDE "${dir}/inc")
  set(RESTFRAMES_DIR "${dir}")
  include_directories(${RESTFRAMES_INCLUDE})
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${dir}/lib")
  set(RESTFRAMES_CONFIG_LDFLAGS "-L${CMAKE_BINARY_DIR}/contrib -Wl,-rpath,${CMAKE_BINARY_DIR}/contrib")
  # OpenMP flags don't play nicely with clang and RestFrames' antiquated libtoolized build system.
  set(RESTFRAMES_C_FLAGS "${BACKEND_C_FLAGS}")
  set(RESTFRAMES_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
  gambit_strip_openmp_from_flags(RESTFRAMES_C_FLAGS)
  gambit_strip_openmp_from_flags(RESTFRAMES_CXX_FLAGS)
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(RESTFRAMES_CONFIG_LIBS "${CMAKE_SHARED_LINKER_FLAGS} -lgambit_preload")
  else()
    set(RESTFRAMES_CONFIG_LIBS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-as-needed -lgambit_preload")
  endif()
  ExternalProject_Add(${name}
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DDIR=${dir}
      -DURL=https://github.com/crogan/RestFrames
      -DTAG=v${ver}
      -P ${PROJECT_SOURCE_DIR}/cmake/scripts/ensure_git_clone.cmake
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND ${CMAKE_COMMAND} -DRFBASE_CC=${dir}/src/RFBase.cc -P ${PROJECT_SOURCE_DIR}/cmake/scripts/patch_restframes_quiet.cmake
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

#contrib/HepMC3; include only if ColliderBit is in use.
if(";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  message("   ColliderBit included, so HepMC is included too")
  set(WITH_HEPMC ON)
else()
  set(WITH_HEPMC OFF)
  message("${BoldCyan} X ColliderBit is not in use: excluding HepMC from GAMBIT configuration.${ColourReset}")
endif()

set(name "hepmc")
set(ver "3.2.5")
set(HEPMC_VERSION "${ver}")
set(HEPMC_PATH "${PROJECT_SOURCE_DIR}/contrib/HepMC3-${ver}")
if(WITH_HEPMC)
  message("-- HepMC-dependent functions in ColliderBit will be activated.")
  message("   HepMC v${ver} will be downloaded and installed when building GAMBIT.")
  message("   Backends depending on HepMC will be enabled.")
  if(HAVE_PYBIND11)
    message("   ColliderBit Solo (CBS) will be activated.")
  endif()
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
  message("   Backends depending on HepMC (e.g. Pythia and Rivet) will be disabled.")
  nuke_ditched_contrib_content(${name} ${HEPMC_PATH})
  set(EXCLUDE_HEPMC TRUE)
endif()

if(NOT EXCLUDE_HEPMC)
  set(lib "HepMC3")
  set(md5 "d3079a7ffcc926b34c5ad2868ed6d8f0")
  set(dl "https://gitlab.cern.ch/hepmc/HepMC3/-/archive/${ver}/HepMC3-${ver}.tar.gz")
  include_directories("${HEPMC_PATH}/local/include")

  set(HEPMC_LDFLAGS "-L${HEPMC_PATH}/local/lib" "-l${lib}")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${HEPMC_PATH}/local/lib")
  set(HEPMC_CXX_FLAGS "${BACKEND_CXX_FLAGS}")

  # Recent ROOT CMake packages expose the required standard as
  # ROOT_CXX_STANDARD rather than adding -std=c++XX to ROOT_CXX_FLAGS.
  # HepMC3 otherwise falls back to C++11 for its ROOT-IO target, appending
  # -std=c++11 after GAMBIT's C++17 flags.
  set(HEPMC_CXX_STANDARD_ARG)
  if(DEFINED ROOT_CXX_STANDARD AND NOT "${ROOT_CXX_STANDARD}" STREQUAL "")
    set(HEPMC_CXX_STANDARD_ARG "-DHEPMC3_CXX_STANDARD=${ROOT_CXX_STANDARD}")
  endif()

  # Silence some compiler warnings coming from HepMC
  set_compiler_warning("no-unused-parameter" HEPMC_CXX_FLAGS)
  set_compiler_warning("no-deprecated-copy" HEPMC_CXX_FLAGS)
  set_compiler_warning("no-sign-compare" HEPMC_CXX_FLAGS)

  ExternalProject_Add(${name}
    DOWNLOAD_COMMAND ${DL_CONTRIB} ${dl} ${md5} ${HEPMC_PATH} ${name} ${ver}
    SOURCE_DIR ${HEPMC_PATH}
    CMAKE_COMMAND ${CMAKE_COMMAND} ..
    # HepMC3 enables both C and CXX in its project(). Pass both compilers
    # explicitly so a stale CC environment variable cannot select another
    # local toolchain for the external configure step.
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=${HEPMC_CXX_FLAGS} ${GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG} ${HEPMC_CXX_STANDARD_ARG} -DHEPMC3_ENABLE_ROOTIO=${HEPMC3_ROOTIO} -DCMAKE_INSTALL_PREFIX=${HEPMC_PATH}/local -DCMAKE_INSTALL_LIBDIR=${HEPMC_PATH}/local/lib -DHEPMC3_ENABLE_PYTHON=OFF -DHEPMC3_ENABLE_SEARCH=ON -DHEPMC3_BUILD_STATIC_LIBS=OFF -DCMAKE_POLICY_VERSION_MINIMUM=${CMAKE_POLICY_VERSION_MINIMUM}
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}
    INSTALL_COMMAND ${CMAKE_INSTALL_COMMAND}
    )

  # Add clean-hepmc and nuke-hepmc
  add_contrib_clean_and_nuke(${name} ${HEPMC_PATH} clean)
endif()

# contrib/onnxruntime
option(WITH_ONNXRUNTIME "Compile with ONNX Runtime enabled" OFF)
if (WITH_ONNXRUNTIME)
  message("   Using ONNX Runtime - Onnx dependent colliderbit analyses will be included")
  set (EXCLUDE_ONNXRUNTIME FALSE)
else ()
  message("   Not using ONNX Runtime - ONNX dependent colliderbit analyses will be excluded")
  set(EXCLUDE_ONNXRUNTIME TRUE)
endif()

set(name onnxruntime)
set(ver 1.14.1)
set(ONNXRUNTIME_VERSION "${ver}")
set(dir ${PROJECT_SOURCE_DIR}/contrib/${name}-${ver})
if (NOT EXCLUDE_ONNXRUNTIME)
  set(lib onnxruntime)
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(dl "https://github.com/microsoft/onnxruntime/releases/download/v1.14.1/onnxruntime-osx-universal2-${ver}.tgz")
    set(md5 9725836c49deb09fc352a57dc8a1b806)
  else ()
    set(dl "https://github.com/microsoft/onnxruntime/releases/download/v1.14.1/onnxruntime-linux-x64-${ver}.tgz")
    set(md5 9a3b855e2b22ace4ab110cec10b38b74)
  endif()
  include_directories(${dir}/include)
  set(ONNXRUNTIME_PATH "${dir}")
  set(ONNXRUNTIME_LIB "${dir}/lib")
  set(ONNXRUNTIME_LDFLAGS "-L${ONNXRUNTIME_LIB}" "-l${lib}")

  ExternalProject_Add(${name}
    DOWNLOAD_COMMAND ${DL_CONTRIB} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_contrib_clean_and_nuke(${name} ${dir} clean)
  set(MODULE_DEPENDENCIES ${MODULE_DEPENDENCIES} ${name})
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${ONNXRUNTIME_LIB}")
endif()


#contrib/YODA; include if ColliderBit is in, don't otherwise
if(";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  message("   ColliderBit included, so YODA is included too")
  set(WITH_YODA ON)
else()
  set(WITH_YODA OFF)
  message("${BoldCyan} X ColliderBit is not in use: excluding YODA from GAMBIT configuration.${ColourReset}")
endif()

set(name "yoda")
set(ver "2.1.0")
set(YODA_VERSION "${ver}")
set(dir "${PROJECT_SOURCE_DIR}/contrib/YODA-${ver}")
if(WITH_YODA)
  message("-- YODA-dependent functions in ColliderBit will be activated.")
  message("   Backends depending on YODA will be enabled.")
  set(EXCLUDE_YODA FALSE)
else()
  message("   YODA-dependent functions in ColliderBit will be deactivated.")
  message("   Backends depending on Yoda (e.g. Rivet, Contur) will de disabled.")
  nuke_ditched_contrib_content(${name} ${dir})
  set(EXCLUDE_YODA TRUE)
endif()

if(NOT EXCLUDE_YODA)
  set(lib "YODA")
  set(dl "https://yoda.hepforge.org/downloads/?f=YODA-${ver}.tar.gz")
  set(md5 "87da674a8e8127b54c408d1b465bf5f7")
  include_directories("${dir}/include")
  set(YODA_PATH "${dir}")
  set(YODA_LIB "${dir}/local/lib")
  set(YODA_LDFLAGS "-L${YODA_LIB}" "-l${lib}")

  # OpenMP flags do not play nicely with clang and YODA's libtool link step.
  # Strip only from YODA's private flags; OpenMP stays enabled for GAMBIT.
  set(YODA_C_FLAGS "${BACKEND_C_FLAGS}")
  set(YODA_CXX_FLAGS "${BACKEND_CXX_FLAGS} -O3")
  gambit_strip_openmp_from_flags(YODA_C_FLAGS)
  gambit_strip_openmp_from_flags(YODA_CXX_FLAGS)
  #set(YODA_CXX_FLAGS "${BACKEND_CXX_FLAGS} -O3" )
  set_compiler_warning("no-unused-parameter" YODA_CXX_FLAGS)
  set_compiler_warning("no-deprecated-copy" YODA_CXX_FLAGS)
  set_compiler_warning("no-implicit-fallthrough" YODA_CXX_FLAGS)
  set(YODA_PY_PATH "${dir}/local/lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/site-packages")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${YODA_LIB}")
  set(YODA_OPENMP_RUNTIME_MISMATCH FALSE)
  gambit_openmp_runtime_mismatch("${YODA_LIB}/lib${lib}.dylib" YODA_OPENMP_RUNTIME_MISMATCH)
  if(YODA_OPENMP_RUNTIME_MISMATCH)
    message("   YODA links a different OpenMP runtime and will be rebuilt.")
  endif()
  # contrib/YODA is in-source.  AppleClang libtool can leave -fopenmp in the
  # installed/build .la files; make clean does not rewrite them.  Check those
  # known paths only — do not walk the whole YODA tree on every configure.
  set(YODA_STALE_OPENMP_METADATA FALSE)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(_yoda_la_files
        "${dir}/src/libYODA.la"
        "${dir}/src/.libs/libYODA.la"
        "${dir}/local/lib/libYODA.la")
    file(GLOB _yoda_extra_la
         "${dir}/local/lib/*.la"
         "${dir}/src/.libs/*.la")
    list(APPEND _yoda_la_files ${_yoda_extra_la})
    list(REMOVE_DUPLICATES _yoda_la_files)
    foreach(_yoda_la IN LISTS _yoda_la_files)
      if(EXISTS "${_yoda_la}")
        file(READ "${_yoda_la}" _yoda_la_content)
        if(_yoda_la_content MATCHES "inherited_linker_flags=.*-fopenmp")
          set(YODA_STALE_OPENMP_METADATA TRUE)
          break()
        endif()
      endif()
    endforeach()
    unset(_yoda_la_files)
    unset(_yoda_extra_la)
    unset(_yoda_la_content)
  endif()
  if(YODA_STALE_OPENMP_METADATA)
    get_paths(${name} _yoda_build_path _yoda_clean_stamps _yoda_nuke_stamps)
    execute_process(COMMAND ${CMAKE_COMMAND} -E remove -f ${_yoda_clean_stamps})
    message("   YODA contains stale AppleClang OpenMP libtool metadata; it will be reconfigured.")
  endif()
  set(YODA_BUILD_COMMAND ${MAKE_PARALLEL} CC="${CMAKE_C_COMPILER}" CXX="${CMAKE_CXX_COMPILER}")
  if(YODA_OPENMP_RUNTIME_MISMATCH)
    set(YODA_BUILD_COMMAND ${MAKE_SERIAL} clean
                           COMMAND ${MAKE_PARALLEL} CC="${CMAKE_C_COMPILER}" CXX="${CMAKE_CXX_COMPILER}")
  endif()
  gambit_find_python_module(cython)
  if(PY_cython_FOUND)
    set(pyext yes)
    message("   Backends depending on YODA's python extension will be enabled.")
  else()
    set(pyext no)
    message("   Backends depending on YODA's python extension (e.g. Contur) will be disabled.")
  endif()
  # Set LDFLAGS for MacOS to find libz
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(YODA_CONFIG_LDFLAGS "-L${CMAKE_OSX_SYSROOT}/usr/lib")
  else()
    set(YODA_CONFIG_LDFLAGS "")
  endif()
  if(GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP)
    # Keep libtool's OpenMP link step on the same runtime as GAMBIT itself.
    set(YODA_CONFIG_LDFLAGS "${YODA_CONFIG_LDFLAGS} ${GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP_LDFLAGS}")
  endif()
  ExternalProject_Add(${name}
    DOWNLOAD_COMMAND ${DL_CONTRIB} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${YODA_PATH}/configure CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} CFLAGS=${YODA_C_FLAGS} CXXFLAGS=${YODA_CXX_FLAGS} LDFLAGS=${YODA_CONFIG_LDFLAGS} PYTHON=${Python3_EXECUTABLE} --prefix=${dir}/local --enable-static --enable-pyext=${pyext}
    BUILD_COMMAND ${YODA_BUILD_COMMAND}
    INSTALL_COMMAND ${MAKE_INSTALL_PARALLEL}
  )
  add_contrib_clean_and_nuke(${name} ${dir} clean)
endif()

# FastJet / fjcontrib; include only if ColliderBit is in use.
# FastJet 3.5.1 + fjcontrib 1.101 are required for Rivet 4 (C++ plugins,
# SoftDrop/LundPlane).
if(";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  set(fastjet_name "fastjet")
  set(fjcontrib_name "fjcontrib")
  set(fastjet_ver "3.5.1")
  set(fastjet_md5 "bfefd2ce16232cbd571b6d9d68f702d6")
  set(fjcontrib_ver "1.101")
  set(fjcontrib_md5 "7397da82cf31a719e56cec0035d8072b")
  set(FASTJET_VERSION "${fastjet_ver}")
  set(FJCONTRIB_VERSION "${fjcontrib_ver}")
  set(fastjet_dl "https://fastjet.fr/repo/fastjet-${fastjet_ver}.tar.gz")
  set(fastjet_path "${PROJECT_SOURCE_DIR}/contrib/fastjet-${fastjet_ver}")
  set(fastjet_DIR "${fastjet_path}/local")
  set(fjcontrib_dl "https://fastjet.fr/contrib/downloads/fjcontrib-${fjcontrib_ver}.tar.gz")
  set(fjcontrib_path "${PROJECT_SOURCE_DIR}/contrib/fjcontrib-${fjcontrib_ver}")

  include_directories("${fastjet_DIR}/include")
  include_directories("${fastjet_DIR}/include/fastjet/contrib")
  set(fastjet_LDFLAGS "-L${fastjet_DIR}/lib" "-lfastjettools" "-lfastjet" "-lfastjetplugins" "-lsiscone_spherical" "-lsiscone")
  set(fjcontrib_LDFLAGS "-L${fastjet_DIR}/lib" "-lfastjetcontribfragile" "-lRecursiveTools" "-lEnergyCorrelator" "-lVariableR")
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH};${fastjet_DIR}/lib")
  set(WITH_FASTJET_CONTRIB TRUE)
  set(EXCLUDE_FASTJET FALSE)
  set(EXCLUDE_FJCONTRIB FALSE)

  # FastJet's autotools build cannot handle the AppleClang OpenMP spelling.
  set(FASTJET_C_FLAGS "${BACKEND_C_FLAGS}")
  set(FASTJET_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
  gambit_strip_openmp_from_flags(FASTJET_C_FLAGS)
  gambit_strip_openmp_from_flags(FASTJET_CXX_FLAGS)
  set_compiler_warning("no-deprecated-declarations" FASTJET_CXX_FLAGS)
  set_compiler_warning("no-deprecated-copy" FASTJET_CXX_FLAGS)
  set(FJCONTRIB_FRAGILE_CXX_FLAGS "${FASTJET_CXX_FLAGS}")
  if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    # fjcontrib rewrites the install name of its fragile shared library.
    set(FJCONTRIB_FRAGILE_CXX_FLAGS "${FJCONTRIB_FRAGILE_CXX_FLAGS} -Wl,-headerpad_max_install_names")
  endif()

  # Rivet 4 needs the C++ plugins plus SoftDrop/LundPlane headers.
  set(_fastjet_required_headers
      fastjet/ClusterSequence.hh
      fastjet/D0RunIIConePlugin.hh
      fastjet/TrackJetPlugin.hh)
  set(_fjcontrib_required_headers
      fastjet/contrib/Nsubjettiness.hh
      fastjet/contrib/SoftDrop.hh
      fastjet/contrib/LundGenerator.hh)
  set(_fastjet_configure_options
      --prefix=${fastjet_DIR}
      --enable-silent-rules
      --enable-shared
      --disable-auto-ptr
      --enable-allcxxplugins)
  set(_fjcontrib_only Nsubjettiness,RecursiveTools,LundPlane,EnergyCorrelator,VariableR)

  set(FASTJET_INSTALLED TRUE)
  foreach(_fastjet_header IN LISTS _fastjet_required_headers)
    if(NOT EXISTS "${fastjet_DIR}/include/${_fastjet_header}")
      set(FASTJET_INSTALLED FALSE)
    endif()
  endforeach()
  foreach(fastjet_library fastjet fastjettools fastjetplugins siscone_spherical siscone)
    find_library(FASTJET_${fastjet_library}_LIBRARY NAMES ${fastjet_library} PATHS "${fastjet_DIR}/lib" NO_DEFAULT_PATH)
    if(NOT FASTJET_${fastjet_library}_LIBRARY)
      set(FASTJET_INSTALLED FALSE)
    endif()
  endforeach()

  if(FASTJET_INSTALLED)
    message("   Using existing FastJet ${fastjet_ver} installation at ${fastjet_DIR}.")
    add_custom_target(${fastjet_name})
  else()
    message("   ColliderBit included, so FastJet ${fastjet_ver} will be downloaded and built when building GAMBIT.")
    ExternalProject_Add(${fastjet_name}
      DOWNLOAD_COMMAND ${DL_CONTRIB} ${fastjet_dl} ${fastjet_md5} ${fastjet_path} ${fastjet_name} ${fastjet_ver}
      SOURCE_DIR ${fastjet_path}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FASTJET_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FASTJET_CXX_FLAGS} ${_fastjet_configure_options}
      BUILD_COMMAND ${MAKE_PARALLEL} install
      INSTALL_COMMAND ""
    )
    add_contrib_clean_and_nuke(${fastjet_name} ${fastjet_path} clean)
  endif()

  # GAMBIT compiles Nsubjettiness itself, but its public headers and the other
  # ColliderBit FastJet-contrib libraries must be installed beside FastJet.
  set(FJCONTRIB_INSTALLED TRUE)
  if(NOT EXISTS "${fjcontrib_path}/Nsubjettiness/Nsubjettiness.cc")
    set(FJCONTRIB_INSTALLED FALSE)
  endif()
  foreach(_fjcontrib_header IN LISTS _fjcontrib_required_headers)
    if(NOT EXISTS "${fastjet_DIR}/include/${_fjcontrib_header}")
      set(FJCONTRIB_INSTALLED FALSE)
    endif()
  endforeach()
  set(FJCONTRIB_OPENMP_RUNTIME_MISMATCH FALSE)
  foreach(fjcontrib_library fastjetcontribfragile RecursiveTools EnergyCorrelator VariableR)
    find_library(FJCONTRIB_${fjcontrib_library}_LIBRARY NAMES ${fjcontrib_library} PATHS "${fastjet_DIR}/lib" NO_DEFAULT_PATH)
    if(NOT FJCONTRIB_${fjcontrib_library}_LIBRARY OR
       NOT EXISTS "${FJCONTRIB_${fjcontrib_library}_LIBRARY}")
      set(FJCONTRIB_INSTALLED FALSE)
    else()
      gambit_openmp_runtime_mismatch("${FJCONTRIB_${fjcontrib_library}_LIBRARY}" FJCONTRIB_OPENMP_RUNTIME_MISMATCH)
      if(FJCONTRIB_OPENMP_RUNTIME_MISMATCH)
        set(FJCONTRIB_INSTALLED FALSE)
        message("   FastJet Contrib links a different OpenMP runtime and will be rebuilt.")
        break()
      endif()
    endif()
  endforeach()
  if(NOT FASTJET_INSTALLED)
    set(FJCONTRIB_INSTALLED FALSE)
  endif()
  set(FJCONTRIB_BUILD_COMMAND ${MAKE_PARALLEL} CXX="${CMAKE_CXX_COMPILER}")
  if(FJCONTRIB_OPENMP_RUNTIME_MISMATCH)
    # This target is not removed by fjcontrib's ordinary clean rule.
    set(FJCONTRIB_BUILD_COMMAND ${CMAKE_COMMAND} -E remove -f
                               "${fjcontrib_path}/libfastjetcontribfragile.dylib"
                               "${fastjet_DIR}/lib/libfastjetcontribfragile.dylib"
                               COMMAND ${MAKE_SERIAL} clean
                               COMMAND ${MAKE_PARALLEL} CXX="${CMAKE_CXX_COMPILER}")
  endif()

  if(FJCONTRIB_INSTALLED)
    message("   Using existing FastJet Contrib ${fjcontrib_ver} installation.")
    add_custom_target(${fjcontrib_name})
  else()
    message("   ColliderBit included, so FastJet Contrib ${fjcontrib_ver} will be downloaded and built when building GAMBIT.")
    ExternalProject_Add(${fjcontrib_name}
      DEPENDS ${fastjet_name}
      DOWNLOAD_COMMAND ${DL_CONTRIB} ${fjcontrib_dl} ${fjcontrib_md5} ${fjcontrib_path} ${fjcontrib_name} ${fjcontrib_ver}
      SOURCE_DIR ${fjcontrib_path}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ./configure CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FASTJET_CXX_FLAGS} --fastjet-config=${fastjet_DIR}/bin/fastjet-config --prefix=${fastjet_DIR} --only=${_fjcontrib_only}
      BUILD_COMMAND ${FJCONTRIB_BUILD_COMMAND}
      INSTALL_COMMAND ${MAKE_INSTALL_PARALLEL} CXX="${CMAKE_CXX_COMPILER}"
                      COMMAND ${MAKE_PARALLEL} fragile-shared-install CXX="${CMAKE_CXX_COMPILER}" CXXFLAGS=${FJCONTRIB_FRAGILE_CXX_FLAGS}
    )
    add_contrib_clean_and_nuke(${fjcontrib_name} ${fjcontrib_path} clean)
  endif()
  unset(_fastjet_configure_options)
  unset(_fastjet_required_headers)
  unset(_fjcontrib_required_headers)
  unset(_fjcontrib_only)
  unset(_fastjet_header)
  unset(_fjcontrib_header)
else()
  message("${BoldCyan} X ColliderBit is not in use: excluding FastJet and FastJet Contrib from GAMBIT configuration.${ColourReset}")
  set(EXCLUDE_FASTJET TRUE)
  set(EXCLUDE_FJCONTRIB TRUE)
  set(WITH_FASTJET_CONTRIB FALSE)
endif()

# Jet clustering requires the FastJet contrib build above.
if(WITH_FASTJET_CONTRIB)
  add_definitions(-DFJNS=fastjet)
  set(fjcontrib_nsubjettiness_dir "${fjcontrib_path}/Nsubjettiness")
  set(fjcontrib_nsubjettiness_sources
      ${fjcontrib_nsubjettiness_dir}/AxesDefinition.cc
      ${fjcontrib_nsubjettiness_dir}/MeasureDefinition.cc
      ${fjcontrib_nsubjettiness_dir}/ExtraRecombiners.cc
      ${fjcontrib_nsubjettiness_dir}/TauComponents.cc
      ${fjcontrib_nsubjettiness_dir}/Njettiness.cc
      ${fjcontrib_nsubjettiness_dir}/Nsubjettiness.cc)
  # Sources are fetched and installed at build time by the fjcontrib external project.
  set_source_files_properties(${fjcontrib_nsubjettiness_sources} PROPERTIES GENERATED TRUE)
  add_gambit_library(fjcontrib_nsubjettiness OPTION OBJECT
                            SOURCES ${fjcontrib_nsubjettiness_sources})
  add_dependencies(fjcontrib_nsubjettiness fastjet fjcontrib)
  set(GAMBIT_BASIC_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:fjcontrib_nsubjettiness>)
  add_dependencies(contrib fjcontrib_nsubjettiness)

  # METSignificance is ColliderBit-only and includes HEPUtils::Jet, which
  # needs FastJet headers. Do not declare it when the fastjet target is absent.
  set(METSignificance_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/contrib/METSignificance/include")
  include_directories("${METSignificance_INCLUDE_DIR}")
  add_gambit_library(METSignificance OPTION OBJECT
                            SOURCES ${PROJECT_SOURCE_DIR}/contrib/METSignificance/src/METSignificance.cpp
                            HEADERS ${PROJECT_SOURCE_DIR}/contrib/METSignificance/include/METSignificance/METSignificance.hpp)
  set(GAMBIT_BASIC_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:METSignificance>)
  add_dependencies(contrib METSignificance)
  add_dependencies(METSignificance fastjet)
endif()

#contrib/multimin
set(multimin_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/contrib/multimin/include")
include_directories("${multimin_INCLUDE_DIR}")
add_gambit_library(multimin OPTION OBJECT
                          SOURCES ${PROJECT_SOURCE_DIR}/contrib/multimin/src/multimin.cpp
                          HEADERS ${PROJECT_SOURCE_DIR}/contrib/multimin/include/multimin/multimin.hpp)
set(GAMBIT_BASIC_COMMON_OBJECTS "${GAMBIT_BASIC_COMMON_OBJECTS}" $<TARGET_OBJECTS:multimin>)
add_dependencies(contrib multimin)

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
    # External C++ link steps need the gfortran runtime path.
    execute_process(
      COMMAND "${CMAKE_Fortran_COMPILER}" "-print-file-name=libgfortran.dylib"
      OUTPUT_VARIABLE GFORTRAN_LIBRARY
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(NOT EXISTS "${GFORTRAN_LIBRARY}")
      execute_process(
        COMMAND "${CMAKE_Fortran_COMPILER}" "-print-file-name=libgfortran.so"
        OUTPUT_VARIABLE GFORTRAN_LIBRARY
        OUTPUT_STRIP_TRAILING_WHITESPACE
      )
    endif()
    if(NOT EXISTS "${GFORTRAN_LIBRARY}")
      message(FATAL_ERROR "Could not find libgfortran reported by ${CMAKE_Fortran_COMPILER}.")
    endif()
    message(STATUS "Found libgfortran at ${GFORTRAN_LIBRARY}.")
    set(flexiblesusy_compilerlibs "${GFORTRAN_LIBRARY} -lm")
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



# If ColliderBit is in use, set various dependencies
if(";${GAMBIT_BITS};" MATCHES ";ColliderBit;")
  # If RestFrames is in use, make it a dependency of contrib
  if(NOT EXCLUDE_RESTFRAMES)
    add_dependencies(contrib restframes)
  endif()
  # ONNX headers are fetched at build time; ColliderBit must not compile first.
  if(NOT EXCLUDE_ONNXRUNTIME)
    add_dependencies(contrib onnxruntime)
  endif()
  # contrib depends on HepMC
  if(EXCLUDE_HEPMC)
    message(FATAL_ERROR "\nColliderBit needs HepMC3. Either use -DWITH_HEPMC=ON or ditch ColliderBit with -Ditch=\"ColliderBit\".")
  endif()
  add_dependencies(contrib hepmc)
  # contrib depends on YODA
  if(EXCLUDE_YODA)
    message(FATAL_ERROR "\nColliderBit needs YODA. Either use -DWITH_YODA=ON or ditch ColliderBit with -Ditch=\"ColliderBit\".")
  endif()
  add_dependencies(contrib yoda)
endif()
