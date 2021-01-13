# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake configuration scripts for obtaining,
#  configuring, compiling and installing
#  backends.
#
#  To add an entry for a new backend, copy
#  and modify an existing one.  Don't use
#  CMAKE_C_FLAGS, CMAKE_CXX_FLAGS, etc here,
#  as these contain extra flags for building
#  GAMBIT itself that will break backends. Use
#  BACKEND_C_FLAGS
#  BACKEND_CXX_FLAGS
#  BACKEND_Fortran_FLAGS
#  If you need to avoid the optimisation
#  settings passed in those, instead use
#  BACKEND_C_FLAGS_NO_BUILD_OPTIMISATIONS
#  BACKEND_CXX_FLAGS_NO_BUILD_OPTIMISATIONS
#  BACKEND_Fortran_FLAGS_NO_BUILD_OPTIMISATIONS.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2014 Sep, Oct, Nov
#  \date 2015 Sep
#
#  \author Pat Scott
#          (p.scott@imperial.ac.uk)
#  \date 2014 Nov, Dec
#  \date 2015 May, Dec
#  \date For the term of my natural life
#
#  \author Chris Rogan
#          (crogan@cern.ch)
#  \date 2015 May
#
#  \author Anders Kvellestad
#          (anderkve@fys.uio.no)
#  \date 2015 May
#
#  \author Christoph Weniger
#          (c.weniger@uva.nl)
#  \date 2015 Sep
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2016 Apr, Dec
#  \date 2020 Apr
#
#  \author James McKay
#          (j.mckay14@imperial.ac.uk)
#  \date 2016 Aug
#
#  \author Ankit Beniwal
#      (ankit.beniwal@adelaide.edu.au)
#  \date 2016 Aug
#  \date 2017 Jun
#  \date 2018 Aug
#
#  \author Aaron Vincent
#          (aaron.vincent@cparc.ca)
#  \date 2017 Sep, Nov
#
#  \author Janina Renk
#          (janina.renk@fysik.su.se)
#  \data 2018 Jun
#
#  \author Patrick Stöcker
#          (stoecker@physik.rwth-aachen.de)
#  \date 2019 Aug
#
#  \author Will Handley
#          (wh260@cam.ac.uk)
#  \date 2020 Mar
#
#************************************************


# Compiler flags for AlterBBN
if("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
  set(AlterBBN_C_FLAGS "${BACKEND_C99_FLAGS} -fast")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
  # Include all flags from -ffast-math, except -ffinite-math-only (which has proved to cause incorrect results), and -fno-rounding-math -fno-signaling-nans (which don't exist in Clang and are defaults anyway for gcc).
  set(AlterBBN_C_FLAGS "${BACKEND_C99_FLAGS} -fno-math-errno -funsafe-math-optimizations")
  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(AlterBBN_C_FLAGS "${AlterBBN_C_FLAGS} -fcx-limited-range") # Clang doesn't have this one.
    # For some reason "-fomit-frame-pointer" must be explicitly included -- at least for gcc --
    # otherwise the uncertainty estimates of AlterBBN are bogus.
    set(AlterBBN_C_FLAGS "${AlterBBN_C_FLAGS} -fomit-frame-pointer")
  endif()
endif()

# AlterBBN
set(name "alterbbn")
set(ver "2.2")
set(lib "libbbn")
set(dl "https://alterbbn.hepforge.org/downloads?f=alterbbn_v2.2.tgz")
set(md5 "00441dde718ba00d3acbb2196a8a5439")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/${name}_${ver}.diff")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sed ${dashi} -e "s#CC = gcc#CC = ${CMAKE_C_COMPILER}#g" Makefile
          COMMAND sed ${dashi} -e "s/CFLAGS= -O3 -pipe -fomit-frame-pointer -mtune=native -ffast-math -fno-finite-math-only/CFLAGS= ${AlterBBN_C_FLAGS}/g" Makefile
          COMMAND sed ${dashi} -e "s/CFLAGS_MP= -fopenmp/CFLAGS_MP= ${OpenMP_C_FLAGS}/g" Makefile
          COMMAND ${MAKE_PARALLEL}
          COMMAND ar x src/libbbn.a
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_C_COMPILER} ${OpenMP_C_FLAGS} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o ${lib}.so *.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# CaptnGeneral
set(name "capgen")
set(ver "1.0")
set(lib "gencaplib")
set(dl "https://github.com/aaronvincent/captngen/archive/${ver}.tar.gz")
set(md5 "410034ac91593c6695a8ed1751a4214c")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${BACKEND_Fortran_FLAGS} MODULE=${FMODULE}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# DarkSUSY
set(name "darksusy")
set(ver "5.1.3")
set(dl "https://darksusy.hepforge.org/tars/${name}-${ver}.tar.gz")
set(md5 "ca95ffa083941a469469710fab2f3c97")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    # FIXME parallel relic density routines don't work yet.
    #COMMAND patch -b -p2 -d src < ${patch}/patchDS_OMP_src.dif
    #COMMAND patch -b -p2 -d include < ${patch}/patchDS_OMP_include.dif
    CONFIGURE_COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${BACKEND_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${BACKEND_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_SERIAL} dslib_shared
          COMMAND ${MAKE_PARALLEL} install_tables
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# DarkSUSY base (for all models)
set(name "darksusy")
set(ver "6.1.1")
set(dl "staff.fysik.su.se/~edsjo/darksusy/tars/${name}-${ver}.tar.gz")
set(md5 "448f72e9bfafbb086bf4526a2094a189")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_.${name}_${ver}_base)
  ExternalProject_Add(.${name}_${ver}_base
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${BACKEND_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${BACKEND_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL} tspack ds_core ds_common ds_empty inst_tab_if_loc
    # FIXME Need to add shared option
    #BUILD_COMMAND ${MAKE_PARALLEL} dslib_shared
    #      COMMAND ${MAKE_PARALLEL} install_tables
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend base (not functional alone)" ${name} ${ver} ${dir} ${dl} clean)
endif()

# DarkSUSY MSSM module
set(model "MSSM")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} feynhiggs higgsbounds higgssignals superiso libisajet ds_mssm
          COMMAND ${MAKE_PARALLEL} ds_mssm_shared
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/dummy ${model} "none")
endif()

# DarkSUSY generic_wimp module
set(model "generic_wimp")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ds_generic_wimp
          COMMAND ${MAKE_PARALLEL} ds_generic_wimp_shared
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/dummy ${model} "none")
endif()

# DarkSUSY base (for all models)
set(name "darksusy")
set(ver "6.2.2")
set(dl "https://darksusy.hepforge.org/tars/${name}-${ver}.tgz")
set(md5 "e23feb7363aebc5460aa8ae2c6906ce1")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_.${name}_${ver}_base)
  ExternalProject_Add(.${name}_${ver}_base
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${BACKEND_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${BACKEND_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL} makedirs tspack healpix ds_core ds_common ds_empty inst_tab_if_loc
    # FIXME Need to add shared option
    #BUILD_COMMAND ${MAKE_PARALLEL} dslib_shared
    #COMMAND ${MAKE_PARALLEL} install_tables
    #COMMAND ${MAKE_PARALLEL} ds_mssm_shared
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend base (not functional alone)" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend base (not functional alone)" ${name} ${ver})
endif()

# DarkSUSY MSSM module
set(model "MSSM")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} feynhiggs higgsbounds higgssignals superiso libisajet ds_mssm
          COMMAND ${MAKE_PARALLEL} ds_mssm_shared
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/dummy ${model} "none")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# DarkSUSY generic_wimp module
set(model "generic_wimp")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ds_generic_wimp
          COMMAND ${MAKE_PARALLEL} ds_generic_wimp_shared
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/dummy ${model} "none")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()


# SuperIso
set(name "superiso")
set(ver "3.6")
set(lib "libsuperiso")
set(dl "http://superiso.in2p3.fr/download/${name}_v${ver}.tgz")
set(md5 "df864ceeccb72467bfbe572a8da9711d")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sed ${dashi} -e "s#CC = gcc#CC = ${CMAKE_C_COMPILER}#g" Makefile
          COMMAND sed ${dashi} -e "s#rcsU#rcs#g" src/Makefile
          COMMAND sed ${dashi} -e "s/CFLAGS= -O3 -pipe -fomit-frame-pointer/CFLAGS= -fPIC ${BACKEND_C_FLAGS}/g" Makefile
          COMMAND ${MAKE_PARALLEL}
          COMMAND ar x src/libisospin.a
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_C_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o ${lib}.so *.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# DDCalc
set(name "ddcalc")
set(ver "1.0.0")
set(lib "libDDCalc")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "0c0da22b84721fc1d945f8039a4686c9")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ddcalc_flags "${BACKEND_Fortran_FLAGS} -${FMODULE} ${dir}/build")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${ddcalc_flags} DDCALC_DIR=${dir} OUTPUT_PIPE=>/dev/null
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

set(name "ddcalc")
set(ver "1.1.0")
set(lib "libDDCalc")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "47191564385379dd70aeba4811cd7c3b")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ddcalc_flags "${BACKEND_Fortran_FLAGS} -${FMODULE} ${dir}/build")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${ddcalc_flags} DDCALC_DIR=${dir} OUTPUT_PIPE=>/dev/null
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

set(name "ddcalc")
set(ver "1.2.0")
set(lib "libDDCalc")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "93b894b80b360159264f0d634cd7387e")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ddcalc_flags "${BACKEND_Fortran_FLAGS} -${FMODULE} ${dir}/build")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${ddcalc_flags} DDCALC_DIR=${dir} OUTPUT_PIPE=>/dev/null
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

set(name "ddcalc")
set(ver "2.0.0")
set(lib "libDDCalc")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "504cb95a298fa62d11097793dc318549")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}/")
set(ddcalc_flags "${BACKEND_Fortran_FLAGS} -${FMODULE} ${dir}/build")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${ddcalc_flags} DDCALC_DIR=${dir} OUTPUT_PIPE=>/dev/null
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

set(name "ddcalc")
set(ver "2.1.0")
set(lib "libDDCalc")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "2c9dbe2aea267e12d0fcb79abb64237b")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}/")
set(ddcalc_flags "${BACKEND_Fortran_FLAGS} -${FMODULE} ${dir}/build")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${ddcalc_flags} DDCALC_DIR=${dir} OUTPUT_PIPE=>/dev/null
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

set(name "ddcalc")
set(ver "2.2.0")
set(lib "libDDCalc")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "36a29b2c95d619b2676d5d1e47b86ab4")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}/")
set(ddcalc_flags "${BACKEND_Fortran_FLAGS} -${FMODULE} ${dir}/build")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${ddcalc_flags} DDCALC_DIR=${dir} OUTPUT_PIPE=>/dev/null
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# Gamlike
set(name "gamlike")
set(ver "1.0.0")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "16b763a2e8b9d6c174d8b7ca2f4cb575")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
if(GSL_FOUND)
  execute_process(
    COMMAND gsl-config --libs
    OUTPUT_VARIABLE GAMLIKE_GSL_LIBS
    RESULT_VARIABLE RET
  )
  if( RET EQUAL 0 )
    string( STRIP "${GAMLIKE_GSL_LIBS}" GAMLIKE_GSL_LIBS )
  endif()
endif()
set(gamlike_CXXFLAGS "${BACKEND_CXX_FLAGS}")
if (NOT GSL_INCLUDE_DIRS STREQUAL "")
  set(gamlike_CXXFLAGS "${gamlike_CXXFLAGS} -I${GSL_INCLUDE_DIRS}")
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${gamlike_CXXFLAGS} LDFLAGS=${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} LDLIBS=${GAMLIKE_GSL_LIBS} GAMLIKE_DATA_PATH=${dir}/data
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

set(name "gamlike")
set(ver "1.0.1")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "80b50ab2345e8b7d43b9eace5436e515")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
if(GSL_FOUND)
  execute_process(
    COMMAND gsl-config --libs
    OUTPUT_VARIABLE GAMLIKE_GSL_LIBS
    RESULT_VARIABLE RET
  )
  if( RET EQUAL 0 )
    string( STRIP "${GAMLIKE_GSL_LIBS}" GAMLIKE_GSL_LIBS )
  endif()
endif()
set(gamlike_CXXFLAGS "${BACKEND_CXX_FLAGS}")
if (NOT GSL_INCLUDE_DIRS STREQUAL "")
  set(gamlike_CXXFLAGS "${gamlike_CXXFLAGS} -I${GSL_INCLUDE_DIRS}")
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${gamlike_CXXFLAGS} LDFLAGS=${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} LDLIBS=${GAMLIKE_GSL_LIBS} GAMLIKE_DATA_PATH=${dir}/data
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# Ditch all MicrOmegas backends if using clang, as clang is apparently not supported by MO3.
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  message("   Compiling with clang; disabling MicrOmegas support in GAMBIT configuration.")
  set (itch "${itch}" "micromegas")
endif()

# MicrOmegas base (for all models)
set(name "micromegas")
set(ver "3.6.9.2")
set(dl "http://lapth.cnrs.fr/micromegas/downloadarea/code/${name}_${ver}.tgz")
set(md5 "72807f6d0ef80737554d8702b6b212c1")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_.${name}_${ver}_base)
  ExternalProject_Add(.${name}_${ver}_base
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    PATCH_COMMAND patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make flags
          COMMAND sed ${dashi} -e "s|FC =.*|FC = ${CMAKE_Fortran_COMPILER}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CC =.*|CC = ${CMAKE_C_COMPILER}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CXX =.*|CXX = ${CMAKE_CXX_COMPILER}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|FFLAGS =.*|FFLAGS = ${BACKEND_Fortran_FLAGS}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CFLAGS =.*|CFLAGS = ${BACKEND_C_FLAGS}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CXXFLAGS =.*|CXXFLAGS = ${BACKEND_CXX_FLAGS}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|FC=.*|FC=\"${CMAKE_Fortran_COMPILER}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CC=.*|CC=\"${CMAKE_C_COMPILER}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CXX=.*|CXX=\"${CMAKE_CXX_COMPILER}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|FFLAGS=.*|FFLAGS=\"${CMAKE_Fortran_FLAGS}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CFLAGS=.*|CFLAGS=\"${CMAKE_C_FLAGS}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CXXFLAGS=.*|CXXFLAGS=\"${BACKEND_CXX_FLAGS}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|lFort=.*|lFort=|" CalcHEP_src/FlagsForSh
          COMMAND make
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend base (functional alone)" ${name} ${ver} ${dir} ${dl} "yes | clean")
  set_as_default_version("backend base (functional alone)" ${name} ${ver})
endif()

# MicrOmegas MSSM model
set(model "MSSM")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas ScalarSingletDM_Z2 model
set(model "ScalarSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas ScalarSingletDM_Z3 model
set(model "ScalarSingletDM_Z3")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas VectorSingletDM_Z2 model
set(model "VectorSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas MajoranaSingletDM_Z2 model
set(model "MajoranaSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas DiracSingletDM_Z2 model
set(model "DiracSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MontePythonLike
set(name "montepythonlike")
set(ver "3.3.0")
set(sfver "3_3_0")
set(dl "https://github.com/brinckmann/montepython_public/archive/${ver}.tar.gz")
set(md5 "84944f0a5b9fb1cab0ddb5dd7be3ea17")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patchdir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/${name}_${ver}.diff")
set(ditch_if_absent "Python")
set(required_modules "numpy,scipy")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch -p1 < ${patch}
      CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/MontePythonLike.py ${dir}/montepython/MontePythonLike_${sfver}.py
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/fastPantheon__init__.py ${dir}/montepython/likelihoods/Pantheon/__init__.py
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/__init__eBOSS_DR14_Lya_combined.py ${dir}/montepython/likelihoods/eBOSS_DR14_Lya_combined/__init__.py
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/sdss_lrgDR7_fiducialmodel.dat ${dir}/data/sdss_lrgDR7/sdss_lrgDR7_fiducialmodel.dat
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/bao_eBOSS_2017.txt ${dir}/data/bao_eBOSS_2017.txt
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/bao_smallz_combined_2018.txt ${dir}/data/bao_smallz_combined_2018.txt
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/des_bao_Y1.txt ${dir}/data/des_bao_Y1.txt
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/WiggleZ_bao_highz ${dir}/montepython/likelihoods/WiggleZ_bao_highz/
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/bao_correlations ${dir}/montepython/likelihoods/bao_correlations/
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/bao_smallz_combined_2018 ${dir}/montepython/likelihoods/bao_smallz_combined_2018/
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/des_bao_Y1 ${dir}/montepython/likelihoods/des_bao_Y1/
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/bao_correlations_data ${dir}/data/bao_correlations/
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/MPLike_patch_script.py ${dir}/montepython/MPLike_patch_script.py
      COMMAND sed ${dashi} -e "s#from MontePythonLike import#from MontePythonLike_${sfver} import#g" ${dir}/montepython/MPLike_patch_script.py
      BUILD_COMMAND ""
      INSTALL_COMMAND ${PYTHON_EXECUTABLE} ${dir}/montepython/MPLike_patch_script.py
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# Pythia
set(name "pythia")
set(ver "8.212")
set(lib "libpythia8")
set(dl "http://home.thep.lu.se/~torbjorn/pythia8/pythia8212.tgz")
set(md5 "0886d1b2827d8f0cd2ae69b925045f40")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")

# - Add additional compiler-specific optimisation flags and suppress some warnings from -Wextra.
set(pythia_CXXFLAGS "${BACKEND_CXX_FLAGS}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -fast") # -fast sometimes makes xsecs come out as NaN, but we catch that and invalidate those points.
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  # Include all flags from -ffast-math, except -ffinite-math-only (which has proved to cause incorrect results), and -fno-rounding-math -fno-signaling-nans (which don't exist in Clang and are defaults anyway for gcc).
  set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -fno-math-errno -funsafe-math-optimizations")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -fcx-limited-range") # Clang doesn't have this one.
  endif()
  set_compiler_warning("no-extra" pythia_CXXFLAGS)
  set_compiler_warning("no-deprecated-declarations" pythia_CXXFLAGS)
endif()

# - Add "-undefined dynamic_lookup flat_namespace" to linker flags when OSX linker is used
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(pythia_CXX_SHARED_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup -flat_namespace")
  set(pythia_CXX_SONAME_FLABS "-Wl,-dylib_install_name")
else()
  set(pythia_CXX_SHARED_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS}")
  set(pythia_CXX_SONAME_FLAGS "-Wl,-soname")
endif()

# - Add option to turn off intel IPO if insufficient memory exists to use it.
option(PYTHIA_OPT "For Pythia: Switch Intel's multi-file interprocedural optimization on/off" ON)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel" AND NOT "${PYTHIA_OPT}")
  set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -no-ipo -ip")
endif()

# - Pythia 8.212 depends on std::auto_ptr which is removed in c++17, so we need to fall back to c++14 (or c++11)
if(COMPILER_SUPPORTS_CXX17)
  string(REGEX REPLACE "-std=c\\+\\+17" "-std=c++14" pythia_CXXFLAGS "${pythia_CXXFLAGS}")
endif()

# - Set include directories
set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -I${Boost_INCLUDE_DIR} -I${PROJECT_SOURCE_DIR}/contrib/slhaea/include")

# - Actual configure and compile commands
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ./configure --enable-shared --cxx="${CMAKE_CXX_COMPILER}" --cxx-common="${pythia_CXXFLAGS}" --cxx-shared="${pythia_CXX_SHARED_FLAGS}" --cxx-soname="${pythia_CXX_SONAME_FLAGS}" --lib-suffix=".so"
    BUILD_COMMAND ${MAKE_PARALLEL} CXX="${CMAKE_CXX_COMPILER}" lib/${lib}.so
    INSTALL_COMMAND ""
  )
  BOSS_backend(${name} ${ver})
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# Pythia external model (EM)
set(model "em")
set(name "pythia_${model}")
set(ver "8.212")
set(lib "libpythia8")
set(dl "http://home.thep.lu.se/~torbjorn/pythia8/pythia8212.tgz")
set(md5 "0886d1b2827d8f0cd2ae69b925045f40")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
set(ext_model_dir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/ExternalModel")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ./configure --enable-shared --cxx="${CMAKE_CXX_COMPILER}" --cxx-common="${pythia_CXXFLAGS}" --cxx-shared="${pythia_CXX_SHARED_FLAGS}" --cxx-soname="${pythia_CXX_SONAME_FLAGS}" --lib-suffix=".so"
    BUILD_COMMAND ${MAKE_PARALLEL} CXX="${CMAKE_CXX_COMPILER}" lib/${lib}.so
    INSTALL_COMMAND ""
  )
  ExternalProject_Add_Step(${name}_${ver} add_external_Pythia_model
    COMMAND ${CMAKE_COMMAND} -E copy ${ext_model_dir}/ProcessContainer.cc ${dir}/src/
    COMMAND ${CMAKE_COMMAND} -E copy ${ext_model_dir}/Index.xml  ${dir}/share/Pythia8/xmldoc/
    COMMAND ${CMAKE_COMMAND} -E copy ${ext_model_dir}/UserModel.xml ${dir}/share/Pythia8/xmldoc/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ext_model_dir}/src ${dir}/src/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ext_model_dir}/include ${dir}/include/
    DEPENDEES download
    DEPENDERS patch
  )
  BOSS_backend(${name} ${ver})
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# Nulike
set(name "nulike")
set(ver "1.0.4")
set(lib "libnulike")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "47649992d19984ee53df6a1655c48227")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FF=${CMAKE_Fortran_COMPILER} FOPT=${BACKEND_Fortran_FLAGS} MODULE=${FMODULE}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
endif()

# Nulike
set(name "nulike")
set(ver "1.0.5")
set(lib "libnulike")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "20cee73a38fb3560298b6a3acdd4d83a")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FF=${CMAKE_Fortran_COMPILER} FOPT=${BACKEND_Fortran_FLAGS} MODULE=${FMODULE}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
endif()

# Nulike
set(name "nulike")
set(ver "1.0.6")
set(lib "libnulike")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "fc4c35dc867bb1213d80acd12e5c1169")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FF=${CMAKE_Fortran_COMPILER} FOPT=${BACKEND_Fortran_FLAGS} MODULE=${FMODULE}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
endif()

# Nulike
set(name "nulike")
set(ver "1.0.7")
set(lib "libnulike")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "5c8e74d125b619abe01e196af7baf790")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FF=${CMAKE_Fortran_COMPILER} FOPT=${BACKEND_Fortran_FLAGS} MODULE=${FMODULE}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
endif()

# Nulike
set(name "nulike")
set(ver "1.0.8")
set(lib "libnulike")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "2ab62018b255cc987263daa6999b1ad6")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FF=${CMAKE_Fortran_COMPILER} FOPT=${BACKEND_Fortran_FLAGS} MODULE=${FMODULE}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
endif()

# Nulike
set(name "nulike")
set(ver "1.0.9")
set(lib "libnulike")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "b3f9d626fc964e9b0d1f33187504662d")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FF=${CMAKE_Fortran_COMPILER} FOPT=${BACKEND_Fortran_FLAGS} MODULE=${FMODULE}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# SUSY-HIT
set(name "susyhit")
set(ver "1.5")
set(lib "libsusyhit")
set(dl "https://www.itp.kit.edu/~maggie/SUSY-HIT/version${ver}_${name}.tar.gz")
set(md5 "493c7ba3a07e192918d3412875fb386a")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")

# - Due to a bug/instability in SUSYHIT, switch off optimization for Intel compilers
set(susyhit_Fortran_FLAGS "${BACKEND_Fortran_FLAGS}")
if("${CMAKE_Fortran_COMPILER_ID}" STREQUAL "Intel")
  set(susyhit_Fortran_FLAGS "${susyhit_Fortran_FLAGS} -O0")
endif()

check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FFLAGS=${susyhit_Fortran_FLAGS}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# FeynHiggs
set(name "feynhiggs")
set(ver "2.12.0")
set(lib "libFH")
set(dl "http://wwwth.mpp.mpg.de/members/heinemey/feynhiggs/newversion/FeynHiggs-${ver}.tar.gz")
set(md5 "da2d0787311525213cd4721da9946b86")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(FH_Fortran_FLAGS "${BACKEND_Fortran_FLAGS_NO_BUILD_OPTIMISATIONS}") #For skipping -O2, which seems to cause issues
set(FH_C_FLAGS "${BACKEND_C_FLAGS_NO_BUILD_OPTIMISATIONS}")             #For skipping -O2, which seems to cause issues
set(FH_CXX_FLAGS "${BACKEND_CXX_FLAGS_NO_BUILD_OPTIMISATIONS}")         #For skipping -O2, which seems to cause issues
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    # Fix bug preventing the use of array bounds checking.
    CONFIGURE_COMMAND sed ${dashi} -e "s#ComplexType spi_(2, 6:7, nvec, 1)#ComplexType spi_(2, 6:7, nvec, LEGS)#g" src/Decays/VecSet.F
              COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FFLAGS=${FH_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FH_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FH_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o lib/${lib}.so build/*.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# FeynHiggs
set(name "feynhiggs")
set(ver "2.11.3")
set(lib "libFH")
set(dl "http://wwwth.mpp.mpg.de/members/heinemey/feynhiggs/newversion/FeynHiggs-${ver}.tar.gz")
set(md5 "49f5ea1838cb233baffd85bbc1b0d87d")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(FH_Fortran_FLAGS "${BACKEND_Fortran_FLAGS_NO_BUILD_OPTIMISATIONS}") #For skipping -O2, which seems to cause issues
set(FH_C_FLAGS "${BACKEND_C_FLAGS_NO_BUILD_OPTIMISATIONS}")             #For skipping -O2, which seems to cause issues
set(FH_CXX_FLAGS "${BACKEND_CXX_FLAGS_NO_BUILD_OPTIMISATIONS}")         #For skipping -O2, which seems to cause issues
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    # Fix bug preventing the use of array bounds checking.
    CONFIGURE_COMMAND sed ${dashi} -e "s#ComplexType spi_(2, 6:7, nvec, 1)#ComplexType spi_(2, 6:7, nvec, LEGS)#g" src/Decays/VecSet.F
              COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FFLAGS=${FH_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FH_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FH_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o lib/${lib}.so build/*.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# FeynHiggs
set(name "feynhiggs")
set(ver "2.11.2")
set(lib "libFH")
set(dl "http://wwwth.mpp.mpg.de/members/heinemey/feynhiggs/newversion/FeynHiggs-${ver}.tar.gz")
set(md5 "edb73eafa6dab291bd8827242c16ac0a")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(FH_Fortran_FLAGS "${BACKEND_Fortran_FLAGS_NO_BUILD_OPTIMISATIONS}") #For skipping -O2, which seems to cause issues
set(FH_C_FLAGS "${BACKEND_C_FLAGS_NO_BUILD_OPTIMISATIONS}")             #For skipping -O2, which seems to cause issues
set(FH_CXX_FLAGS "${BACKEND_CXX_FLAGS_NO_BUILD_OPTIMISATIONS}")         #For skipping -O2, which seems to cause issues
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    # Fix bug preventing the use of array bounds checking.
    CONFIGURE_COMMAND sed ${dashi} -e "s#ComplexType spi_(2, 6:7, nvec, 1)#ComplexType spi_(2, 6:7, nvec, LEGS)#g" src/Decays/VecSet.F
              COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FFLAGS=${FH_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FH_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FH_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o lib/${lib}.so build/*.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()


# HiggsBounds tables
set(name "higgsbounds_tables")
set(ver "0.0")
set(dl "https://higgsbounds.hepforge.org/downloads/csboutput_trans_binary.tar.gz")
set(md5 "004decca30335ddad95654a04dd034a6")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver} "retain container folder"
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# HiggsBounds
set(name "higgsbounds")
set(ver "4.3.1")
set(lib "libhiggsbounds")
set(dl "https://${name}.hepforge.org/downloads/HiggsBounds-${ver}.tar.gz")
set(md5 "c1667613f814a9f0297d1f11a8b3ef34")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
set(hb_tab_name "higgsbounds_tables")
set(hb_tab_ver "0.0")
set(hb_tab_dir "${PROJECT_SOURCE_DIR}/Backends/installed/${hb_tab_name}/${hb_tab_ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS ${hb_tab_name}_${hb_tab_ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    PATCH_COMMAND patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy configure-with-chisq my_configure
              COMMAND sed ${dashi} -e "s|clsbtablesdir=.*|clsbtablesdir=\"${hb_tab_dir}/\"|" my_configure
              COMMAND sed ${dashi} -e "s|F90C =.*|F90C = ${CMAKE_Fortran_COMPILER}|" my_configure
              COMMAND sed ${dashi} -e "s|F77C =.*|F77C = ${CMAKE_Fortran_COMPILER}|" my_configure
              COMMAND sed ${dashi} -e "s|F90FLAGS =.*|F90FLAGS = ${BACKEND_Fortran_FLAGS}|" my_configure
              COMMAND sed ${dashi} -e "s|\\.SUFFIXES|.NOTPARALLEL:${nl}${nl}.SUFFIXES|" makefile.in
              COMMAND ${CMAKE_COMMAND} -E copy makefile.in makefile.in.tmp
              COMMAND awk "{gsub(/${nl}/,${true_nl})}{print}" makefile.in.tmp > makefile.in
              COMMAND ${CMAKE_COMMAND} -E remove makefile.in.tmp
              COMMAND ./my_configure
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o lib/${lib}.so *.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# HiggsBounds
set(name "higgsbounds")
set(ver "4.2.1")
set(lib "libhiggsbounds")
set(dl "https://${name}.hepforge.org/downloads/HiggsBounds-${ver}.tar.gz")
set(md5 "47b93330d4e0fddcc23b381548db355b")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(hb_tab_name "higgsbounds_tables")
set(hb_tab_ver "0.0")
set(hb_tab_dir "${PROJECT_SOURCE_DIR}/Backends/installed/${hb_tab_name}/${hb_tab_ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS ${hb_tab_name}_${hb_tab_ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy configure-with-chisq my_configure
              COMMAND sed ${dashi} -e "s|clsbtablesdir=.*|clsbtablesdir=\"${hb_tab_dir}/\"|" my_configure
              COMMAND sed ${dashi} -e "s|F90C =.*|F90C = ${CMAKE_Fortran_COMPILER}|" my_configure
              COMMAND sed ${dashi} -e "s|F77C =.*|F77C = ${CMAKE_Fortran_COMPILER}|" my_configure
              COMMAND sed ${dashi} -e "s|F90FLAGS =.*|F90FLAGS = ${BACKEND_Fortran_FLAGS}|" my_configure
              COMMAND sed ${dashi} -e "s|\\.SUFFIXES|.NOTPARALLEL:${nl}${nl}.SUFFIXES|" makefile.in
              COMMAND ${CMAKE_COMMAND} -E copy makefile.in makefile.in.tmp
              COMMAND awk "{gsub(/${nl}/,${true_nl})}{print}" makefile.in.tmp > makefile.in
              COMMAND ${CMAKE_COMMAND} -E remove makefile.in.tmp
              COMMAND ./my_configure
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o lib/${lib}.so *.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()


# HiggsSignals
set(name "higgssignals")
set(ver "1.4.0")
set(lib "libhiggssignals")
set(dl "https://higgsbounds.hepforge.org/downloads/HiggsSignals-${ver}.tar.gz")
set(md5 "537d3885b1cbddbe1163dbc843ec2beb")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
set(hb_name "higgsbounds")
set(hb_ver "4.3.1")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS higgsbounds_${hb_ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    PATCH_COMMAND patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy configure my_configure
              COMMAND sed ${dashi} -e "s|HBLIBS =.*|HBLIBS =-L../../${hb_name}/${hb_ver}|" my_configure
              COMMAND sed ${dashi} -e "s|HBINCLUDE =.*|HBINCLUDE =-I../../${hb_name}/${hb_ver}|" my_configure
              COMMAND sed ${dashi} -e "s|F90C =.*|F90C = ${CMAKE_Fortran_COMPILER}|" my_configure
              COMMAND sed ${dashi} -e "s|F77C =.*|F77C = ${CMAKE_Fortran_COMPILER}|" my_configure
              COMMAND sed ${dashi} -e "s|F90FLAGS =.*|F90FLAGS = ${BACKEND_Fortran_FLAGS}|" my_configure
              COMMAND sed ${dashi} -e "s|\\.SUFFIXES|.NOTPARALLEL:${nl}${nl}.SUFFIXES|" makefile.in
              COMMAND ${CMAKE_COMMAND} -E copy makefile.in makefile.in.tmp
              COMMAND awk "{gsub(/${nl}/,${true_nl})}{print}" makefile.in.tmp > makefile.in
              COMMAND ${CMAKE_COMMAND} -E remove makefile.in.tmp
              COMMAND ./my_configure
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E remove HiggsSignals.o
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o lib/${lib}.so ./*.o ../../${hb_name}/${hb_ver}/*.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# SPheno
set(name "spheno")
set(ver "3.3.8")
set(lib "lib/libSPheno.so")
set(dl "http://www.hepforge.org/archive/spheno/SPheno-${ver}.tar.gz")
set(md5 "4307cb4b736cebca5e57ca6c5e0b5836")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
string(REGEX REPLACE "(-cpp)|(-fpp)" "" SPheno_FLAGS "${BACKEND_Fortran_FLAGS}") #SPheno hates the preprocessor
set(SPheno_FLAGS "-c ${SPheno_FLAGS} -${FMODULE} ${dir}/include -I${dir}/include")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} $F90=${CMAKE_Fortran_COMPILER} FFLAGS=${SPheno_FLAGS} ${lib}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# SPheno
set(name "spheno")
set(ver "4.0.3")
set(lib "lib/libSPheno.so")
set(dl "http://www.hepforge.org/archive/spheno/SPheno-${ver}.tar.gz")
set(md5 "64787d6c8ce03cac38aec53d34ac46ad")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
string(REGEX REPLACE "(-cpp)|(-fpp)" "" SPheno_FLAGS "${BACKEND_Fortran_FLAGS}") #SPheno hates the preprocessor
set(SPheno_FLAGS "-c ${SPheno_FLAGS} -${FMODULE} ${dir}/include -I${dir}/include")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} F90=${CMAKE_Fortran_COMPILER} FFLAGS="${SPheno_FLAGS}" ${lib}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} cleanall)
  set_as_default_version("backend" ${name} ${ver})
endif()


# gm2calc
set(name "gm2calc")
set(ver "1.3.0")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "1bddab5a411a895edd382a1f8a991c15")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}")
# - Silence the deprecated-declarations warnings coming from Eigen3
set(GM2CALC_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
set_compiler_warning("no-deprecated-declarations" GM2CALC_CXX_FLAGS)
# - gm2calc 1.3 depends on std::ptr_fun which is removed in c++17, so we need to fall back to c++14 (or c++11)
if(COMPILER_SUPPORTS_CXX17)
  string(REGEX REPLACE "-std=c\\+\\+17" "-std=c++14" GM2CALC_CXX_FLAGS "${GM2CALC_CXX_FLAGS}")
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}_error.dif
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${GM2CALC_CXX_FLAGS} EIGENFLAGS=-I${EIGEN3_INCLUDE_DIR} BOOSTFLAGS=-I${Boost_INCLUDE_DIR} alllib
    INSTALL_COMMAND ""
  )
  BOSS_backend(${name} ${ver})
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# gm2calc
set(name "gm2calc")
set(ver "1.2.0")
set(dl "https://${name}.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "07d55bbbd648b8ef9b2d69ad1dfd8326")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}")
# - Silence the deprecated-declarations warnings coming from Eigen3
set(GM2CALC_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
set_compiler_warning("no-deprecated-declarations" GM2CALC_CXX_FLAGS)
# - gm2calc 1.2 depends on std::ptr_fun which is removed in c++17, so we need to fall back to c++14 (or c++11)
if(COMPILER_SUPPORTS_CXX17)
  string(REGEX REPLACE "-std=c\\+\\+17" "-std=c++14" GM2CALC_CXX_FLAGS "${GM2CALC_CXX_FLAGS}")
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}_makefile.dif
          COMMAND patch -p1 < ${patch}_module.dif
          COMMAND patch -p1 < ${patch}_error.dif
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${GM2CALC_CXX_FLAGS} EIGENFLAGS=-I${EIGEN3_INCLUDE_DIR} BOOSTFLAGS=-I${Boost_INCLUDE_DIR} sharedlib
    INSTALL_COMMAND ""
  )
  BOSS_backend(${name} ${ver})
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# SUSYHD
set(name "susyhd")
set(ver "1.0.2")
set(dl "http://users.ictp.it/~${name}/v${ver}/SUSYHD.tgz")
set(md5 "e831c3fa977552ff944e0db44db38e87")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Mathematica")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# cfitsio
set(name "cfitsio")
set(ver "3.390")
set(lib "libcfitsio")
set(dl "http://heasarc.gsfc.nasa.gov/FTP/software/fitsio/c/cfitsio3390.tar.gz")
set(md5 "e92dd2a4282a1c50d46167041a29fc67")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(CFITSIO_SO ".so")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --includedir=${dir}/include --libdir=${dir}/lib FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${BACKEND_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${BACKEND_CXX_FLAGS} SHLIB_SUFFIX=${CFITSIO_SO}
    BUILD_COMMAND ${MAKE_PARALLEL} shared SHLIB_SUFFIX=${CFITSIO_SO}
    INSTALL_COMMAND ${MAKE_PARALLEL} install SHLIB_SUFFIX=${CFITSIO_SO}
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# plc data
set(name "plc_data")
set(ver "2.0")
set(dl "http://pla.esac.esa.int/pla/aio/product-action?COSMOLOGY.FILE_ID=COM_Likelihood_Data-baseline_R2.00.tar.gz")
set(md5 "7e784819cea65dbc290ea3619420295a")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver} "retain container folder"
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# plc data
set(name "plc_data")
set(ver "3.0")
set(dl "http://pla.esac.esa.int/pla/aio/product-action?COSMOLOGY.FILE_ID=COM_Likelihood_Data-baseline_R3.00.tar.gz")
set(md5 "682e6859421b0e7bc7d82f1460613e06")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# plc
set(name "plc")
set(ver "3.0")
set(lib "libclik")
set(dl "http://pla.esac.esa.int/pla/aio/product-action?COSMOLOGY.FILE_ID=COM_Likelihood_Code-v3.0_R3.00.tar.gz")
set(md5 "23a7d80cffe3156b33575becbee7ac15")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(cfitsio_name "cfitsio")
set(cfitsio_ver "3.390")
set(cfitsio_dir "${PROJECT_SOURCE_DIR}/Backends/installed/${cfitsio_name}/${cfitsio_ver}")
if(NOT ${FOUND_MKL} EQUAL -1)
  if(DEFINED ENV{MKLROOT})
  string(STRIP $ENV{MKLROOT} STRIPPED_MKLROOT)
    if(NOT "${STRIPPED_MKLROOT}" STREQUAL "")
      set(mkl_libs_option "--lapack_mkl=${STRIPPED_MKLROOT}")
    else()
      set(mkl_libs_option "")
    endif()
  endif()
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS ${cfitsio_name}_${cfitsio_ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver} "retain container folder"
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    # Since someone put a tarball into a tarball, we need to extract again
    PATCH_COMMAND tar -C ${dir}/ -xf ${dir}/code/plc_3.0/plc-3.0.tar.bz2 --strip-components=1
    COMMAND patch -p1 < ${patch}/${name}_${ver}.diff
    CONFIGURE_COMMAND CC=${CMAKE_C_COMPILER} FC=${CMAKE_Fortran_COMPILER} ${PYTHON_EXECUTABLE} ${dir}/waf configure --cfitsio_include=${cfitsio_dir}/include --cfitsio_lib=${cfitsio_dir}/lib ${mkl_libs_option} --no_pytools
    BUILD_COMMAND ""
    INSTALL_COMMAND C_INCLUDE_PATH=$(C_INCLUDE_PATH):${PYTHON_INCLUDE_DIR} ${PYTHON_EXECUTABLE} ${dir}/waf install --no_pytools
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# classy
set(name "classy")
set(ver "2.6.3")
set(sfver "2_6_3")
set(lib "classy")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(dl "https://github.com/lesgourg/class_public/archive/v${ver}.tar.gz")
set(md5 "e6eb0fd721bb1098e642f5d1970501ce")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Python")
set(required_modules "cython,numpy,scipy")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch -p1 < ${patch}/${name}_${ver}.diff
      CONFIGURE_COMMAND ""
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_GNU99_FLAGS} LDFLAG=${BACKEND_GNU99_FLAGS} PYTHON=${PYTHON_EXECUTABLE} all
      COMMAND ${CMAKE_COMMAND} -E make_directory lib
      COMMAND find python/ -name "classy*.so" | xargs -I {} cp "{}" lib/
      COMMAND ${CMAKE_COMMAND} -E echo "#This is a trampoline script to import the cythonized python module under a different name" > lib/${lib}_${sfver}.py
      COMMAND ${CMAKE_COMMAND} -E echo "from ${lib} import *" >> lib/${lib}_${sfver}.py
      INSTALL_COMMAND ""
      COMMAND ${PYTHON_EXECUTABLE} ${patch}/../create_SDSSDR7_fid.py ${dir} ${sfver}
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# classy
set(name "classy")
set(ver "2.9.3")
set(sfver "2_9_3")
set(lib "classy")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(dl "https://github.com/lesgourg/class_public/archive/v${ver}.tar.gz")
set(md5 "91a28b6b6ad31e0cbc6a715c8589dab2")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Python")
set(required_modules "cython,numpy,scipy")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch -p1 < ${patch}/${name}_${ver}.diff
      CONFIGURE_COMMAND ""
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_GNU99_FLAGS} LDFLAG=${BACKEND_GNU99_FLAGS} PYTHON=${PYTHON_EXECUTABLE} all
      COMMAND ${CMAKE_COMMAND} -E make_directory lib
      COMMAND find python/ -name "classy*.so" | xargs -I {} cp "{}" lib/
      COMMAND ${CMAKE_COMMAND} -E echo "#This is a trampoline script to import the cythonized python module under a different name" > lib/${lib}_${sfver}.py
      COMMAND ${CMAKE_COMMAND} -E echo "from ${lib} import *" >> lib/${lib}_${sfver}.py
      INSTALL_COMMAND ""
      COMMAND ${PYTHON_EXECUTABLE} ${patch}/../create_SDSSDR7_fid.py ${dir} ${sfver}
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# classy
set(name "classy")
set(ver "2.9.4")
set(sfver "2_9_4")
set(lib "classy")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(dl "https://github.com/lesgourg/class_public/archive/v${ver}.tar.gz")
set(md5 "dac0e0920e333c553b76c9f4b063ec99")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Python")
set(required_modules "cython,numpy,scipy")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch -p1 < ${patch}/${name}_${ver}.diff
      CONFIGURE_COMMAND ""
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_GNU99_FLAGS} LDFLAG=${BACKEND_GNU99_FLAGS} PYTHON=${PYTHON_EXECUTABLE} all
      COMMAND ${CMAKE_COMMAND} -E make_directory lib
      COMMAND find python/ -name "classy*.so" | xargs -I {} cp "{}" lib/
      COMMAND ${CMAKE_COMMAND} -E echo "#This is a trampoline script to import the cythonized python module under a different name" > lib/${lib}_${sfver}.py
      COMMAND ${CMAKE_COMMAND} -E echo "from ${lib} import *" >> lib/${lib}_${sfver}.py
      INSTALL_COMMAND ""
      COMMAND ${PYTHON_EXECUTABLE} ${patch}/../create_SDSSDR7_fid.py ${dir} ${sfver}
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# classy
set(name "classy")
set(ver "exo_2.7.2")
set(sfver "exo_2_7_2")
set(lib "classy")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(dl "https://github.com/lesgourg/class_public/archive/42e8f9418e3442d1ea3f26ff84dc9f0e856a0f1d.tar.gz") # The huge number is the commit ID of ExoCLASS_2.7.0
set(md5 "8f3139eacae4d1cc5bb02bab3ec75073")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Python")
set(required_modules "cython,numpy,scipy")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch -p1 < ${patch}/${name}_${ver}.diff
      CONFIGURE_COMMAND ""
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_GNU99_FLAGS} LDFLAG=${BACKEND_GNU99_FLAGS} PYTHON=${PYTHON_EXECUTABLE} all
      COMMAND ${CMAKE_COMMAND} -E make_directory lib
      COMMAND find python/ -name "classy*.so" | xargs -I {} cp "{}" lib/
      COMMAND ${CMAKE_COMMAND} -E echo "#This is a trampoline script to import the cythonized python module under a different name" > lib/${lib}_${sfver}.py
      COMMAND ${CMAKE_COMMAND} -E echo "from ${lib} import *" >> lib/${lib}_${sfver}.py
      INSTALL_COMMAND ""
      COMMAND ${PYTHON_EXECUTABLE} ${patch}/../create_SDSSDR7_fid.py ${dir} ${sfver}
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# DarkAges
# Add correct symlink flags for OSX
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(DarkAges_SYMLINK_FLAGS "-hfs")
else()
  set(DarkAges_SYMLINK_FLAGS "-fs")
endif()
set(name "darkages")
set(ver "1.2.0")
set(sfver "1_2_0")
set(dl "https://github.com/pstoecker/DarkAges/archive/v${ver}.tar.gz")
set(md5 "d39d331ab750d1f9796d2b81d55e7703")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Python")
set(required_modules "scipy,dill,future,numpy")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ln ${DarkAges_SYMLINK_FLAGS} DarkAges DarkAges_${sfver}
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

#MultiModeCode
set(name "multimodecode")
set(ver "2.0.0")
set(lib "libmodecode")
set(dl "http://modecode.org/wp-content/uploads/2014/09/MultiModeCode.2.0.0.tar.gz")
set(md5 "03f99f02c572ea34383a0888fb0658d6")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
if("${CMAKE_Fortran_COMPILER_ID}" STREQUAL "Intel")
  set(multimode_Fortran_FLAGS "${BACKEND_Fortran_FLAGS} -r8")
elseif("${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU")
  set(multimode_Fortran_FLAGS "${BACKEND_Fortran_FLAGS} -fdefault-real-8")
else()
  set(multimode_Fortran_FLAGS "${BACKEND_Fortran_FLAGS}")
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}/multimodecode_${ver}.diff
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_SERIAL} F90C=${CMAKE_Fortran_COMPILER} FFLAGS=${multimode_Fortran_FLAGS}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()
