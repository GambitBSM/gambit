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
#  \date 2023 Jun
#
#  \author Christoph Weniger
#          (c.weniger@uva.nl)
#  \date 2015 Sep
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2016 Apr, Dec
#  \date 2017 Nov
#  \date 2019 June-Sep
#  \date 2020 Apr
#
#  \author James McKay
#          (j.mckay14@imperial.ac.uk)
#  \date 2016 Aug
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2017 May
#  \date 2018 Sep
#
#  \author Ankit Beniwal
#      (ankit.beniwal@adelaide.edu.au)
#  \date 2016 Aug
#  \date 2017 Jun
#  \date 2018 Aug
#
#  \author Torsten Bringmann
#      (torsten.bringmann@uio.no)
#  \date 2022 Jan
#
#  \author Aaron Vincent
#          (aaron.vincent@cparc.ca)
#  \date 2017 Sep, Nov
#
#  \author Marcin Chrzaszcz
#          (mchrzasz@cern.ch)
#  \date 2019 July
#
#  \author Jihyun Bhom
#          (jihyun.bhom@ifj.edu.pl)
#  \date 2019 July

#  \author Janina Renk
#          (janina.renk@fysik.su.se)
#  \data 2018 Jun
#
#  \author Patrick Stöcker
#          (stoecker@physik.rwth-aachen.de)
#  \date 2019 Aug
#  \date 2021 Sep
#
#  \author Will Handley
#          (wh260@cam.ac.uk)
#  \date 2020 Mar
#
#  \author Are Raklev
#          (ahye@fys.uio.no)
#  \date 2022 Feb
#
#  \author Timon Emken
#          (timon.emken@fysik.su.se)
#  \date 2022 Mar
#
#  \author Quan Huynh
#          (qhuy0003@student.monash.edu)
#  \date 2022 Apr
#
#************************************************


# Target for downloading castxml (required by BOSS)
set(name "castxml")
set(dir "${CMAKE_SOURCE_DIR}/Backends/scripts/BOSS/castxml")
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm64")
    set(castxml_dl "https://data.kitware.com/api/v1/item/63c469666d3fc641a02d80ca/download")
    set(castxml_dl_filename "castxml-macos-arm64.tar.gz")
  else()
    set(castxml_dl "https://data.kitware.com/api/v1/item/63bed7726d3fc641a02d7e9e/download")
    set(castxml_dl_filename "castxml-macosx.tar.gz")
  endif()
else()
  set(castxml_dl "https://data.kitware.com/api/v1/item/63bed74d6d3fc641a02d7e98/download")
  set(castxml_dl_filename "castxml-linux.tar.gz")
endif()
ExternalProject_Add(${name}
  DOWNLOAD_COMMAND ${PROJECT_SOURCE_DIR}/cmake/scripts/download_castxml_binaries.sh ${dir} ${CMAKE_COMMAND} ${CMAKE_DOWNLOAD_FLAGS} ${castxml_dl} ${castxml_dl_filename}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
set(rmstring "${CMAKE_BINARY_DIR}/${name}-prefix/src/${name}-stamp/${name}")
add_custom_target(nuke-castxml COMMAND ${CMAKE_COMMAND} -E remove -f ${rmstring}-download ${rmstring}-download-failed ${rmstring}-mkdir ${rmstring}-patch ${rmstring}-update || true
                               COMMAND ${CMAKE_COMMAND} -E remove_directory ${dir} || true)
add_dependencies(nuke-all nuke-castxml)
set_target_properties(castxml PROPERTIES EXCLUDE_FROM_ALL 1)

# Acropolis
set(name "acropolis")
set(ver "1.2.1")
set(dl "https://acropolis.hepforge.org/downloads/${name}-${ver}.tar.gz")
set(md5 "e427da6d401d5b63ad485b4a8841f6d2")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/${name}_${ver}_patch.diff")
set(required_modules "numpy,scipy,numba")
check_ditch_status(${name} ${ver} ${dir})
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
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


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
    BUILD_COMMAND ${MAKE_SERIAL} CC=${CMAKE_C_COMPILER} ARFLAGS=rcs CFLAGS=${AlterBBN_C_FLAGS} CFLAGS_MP=${OpenMP_C_FLAGS}
          COMMAND ar x src/libbbn.a
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_C_COMPILER} ${OpenMP_C_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o ${lib}.so *.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# ATLAS_FullLikes
set(name "ATLAS_FullLikes")
set(ver "1.0")
set(dl "no-download-url")
set(ditch_if_absent "Python")
set(required_modules "pyhf")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(examples_dir "${PROJECT_SOURCE_DIR}/Backends/examples/${name}/${ver}")
check_ditch_status(${name} ${ver} "none" ${ditch_if_absent})
# Ditch if Python version < v3.6 (required for pyhf)
if(PYTHON_VERSION VERSION_LESS 3.6)
  message("${BoldCyan} X Excluding ATLAS FullLikes from GAMBIT configuration. Configure with Python >= v3.6 to activate ATLAS FullLikes: ${ColourReset}")
  set(ditched_${name}_${ver} true)
endif()
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DOWNLOAD_COMMAND ""
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND ""
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ${CMAKE_COMMAND} -E copy_directory ${examples_dir} ${dir}
      INSTALL_COMMAND ""
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# CaptnGeneral
set(name "capgen")
set(ver "2.1")
set(lib "gencaplib")
set(dl "https://github.com/aaronvincent/captngen/archive/refs/tags/${ver}.tar.gz")
set(md5 "6996c0ae9828f3b14f6c9bd45d46fb78")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(capgen_Fortran_FLAGS "${BACKEND_Fortran_FLAGS}")
if("${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_Fortran_COMPILER_VERSION VERSION_LESS 10)
  set(capgen_Fortran_FLAGS "${capgen_Fortran_FLAGS} -std=legacy")
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
  DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
  SOURCE_DIR ${dir}
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${MAKE_PARALLEL} ${lib}.so FC=${CMAKE_Fortran_COMPILER} FOPT=${capgen_Fortran_FLAGS} MODULE=${FMODULE}
  INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# DarkCast
set(name "darkcast")
set(ver "1.1")
set(lib "darkcastlib")
set(dl "https://gitlab.com/philten/darkcast/-/archive/v1.1/darkcast-v1.1.tar.gz")
set(md5 "b9a4cd71e6959230480478ed5262835d")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${name}_patch.diff")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# DarkSUSY
set(name "darksusy")
set(ver "5.1.3")
# Ditch DarkSUSY 5 if using gfortran 10 or later, as it won't compile due to FeynHiggs
if("${ver}" STREQUAL "5.1.3" AND "${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_Fortran_COMPILER_VERSION VERSION_LESS 10)
  set(itch "${itch}" "darksusy_5.1.3")
endif()
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
# Ditch DarkSUSY 6.1.1 if using gfortran 10 or later, as it won't compile due to FeynHiggs
if("${ver}" STREQUAL "6.1.1" AND "${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_Fortran_COMPILER_VERSION VERSION_LESS 10)
  set(itch "${itch}" "darksusy_6.1.1")
endif()
set(dl "staff.fysik.su.se/~edsjo/darksusy/tars/${name}-${ver}.tar.gz")
set(md5 "448f72e9bfafbb086bf4526a2094a189")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
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
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
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
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
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
# Ditch DarkSUSY 6.2.2 if using gfortran 10 or later, as it won't compile due to FeynHiggs
if("${ver}" STREQUAL "6.2.2" AND "${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_Fortran_COMPILER_VERSION VERSION_LESS 10)
  set(itch "${itch}" "darksusy_6.2.2")
endif()
set(dl "https://darksusy.hepforge.org/tars/${name}-${ver}.tgz")
set(md5 "e23feb7363aebc5460aa8ae2c6906ce1")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
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
endif()

# DarkSUSY MSSM module
set(model "MSSM")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
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
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
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
set(ver "6.2.5")
set(dl "https://darksusy.hepforge.org/tars/${name}-${ver}.tgz")
set(md5 "9d9d85b2220d14d82a535ef45dcb4537")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patchdir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(.${name}_${ver}_base
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${BACKEND_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${BACKEND_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL} makedirs healpix tspack ds_core ds_common ds_empty install_tables
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend base (not functional alone)" ${name} ${ver} ${dir} ${dl} clean)
endif()

# Ditch DarkSUSY_MSSM_6.2.5 if using gfortran 10 or later, as it won't compile due to FeynHiggs
if("${ver}" STREQUAL "6.2.5" AND "${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_Fortran_COMPILER_VERSION VERSION_LESS 10)
  set(itch "${itch}" "darksusy_MSSM_6.2.5")
endif()

# DarkSUSY MSSM module
set(model "MSSM")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
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
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
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
set(ver "6.4.0")
set(dl "https://darksusy.hepforge.org/tars/${name}-${ver}.tgz")
set(md5 "1bf46347bac64fb019a8b2c617586d0a")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patchdir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(.${name}_${ver}_base
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    # Apart from the standard patch we want to replace some yield tables with higher resolution versions
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}updated_tables/ ${dir}/data/yields_hazma/
    CONFIGURE_COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${BACKEND_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${BACKEND_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL} ds_core ds_empty install_tables
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend base (not functional alone)" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend base (not functional alone)" ${name} ${ver})
endif()

# DarkSUSY MSSM module
set(model "MSSM")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} higgsbounds higgssignals ds_mssm
          COMMAND ${MAKE_PARALLEL} ds_mssm_shared
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/dummy ${model} "none")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# DarkSUSY generic_wimp module
set(model "generic_wimp")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${ver} AND NOT ditched_${name}_${model}_${ver})
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

# DMsimp_Data
# This is the MonoJet and DiJet data associated with the simplified dark matter models.
set(name "DMsimp_data")
set(ver "1.0")
set(dl "https://zenodo.org/record/7619478/files/DMsimp.zip")
set(dir "${PROJECT_SOURCE_DIR}/ColliderBit/data/DMsimp_data/")
set(md5 "a20fb95888e005b6665ca3bac811c426")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
endif()

# HepLikedata
set(name "heplikedata")
set(ver "1.4")
set(dl "https://github.com/KrakowHEPSoft/HEPLikeData/archive/V${ver}.zip")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(md5 "b11c715ee3af25727b85297b6681c9b5")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# HepLike
set(name "heplike")
set(ver "2.0")
set(dl "https://github.com/tegonzalo/HEPLike/archive/V${ver}.zip")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(md5 "a9b674b8a11037a15bfed69835aac1a6")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
set(HL_CXXFLAGS "${BACKEND_CXX_FLAGS} -I${yaml_INCLUDE_DIR}")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(HL_CXXFLAGS "${HL_CXXFLAGS} -undefined dynamic_lookup -flat_namespace")
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  set(HL_CXXFLAGS "${HL_CXXFLAGS} ${NO_FIXUP_CHAINS}")
endif()
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS heplikedata
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    UPDATE_COMMAND ${CMAKE_COMMAND} -E echo "set_target_properties(HEPLike_shared PROPERTIES OUTPUT_NAME HEPLike SUFFIX \".so\")" >> ${dir}/CMakeLists.txt
    CMAKE_COMMAND ${CMAKE_COMMAND} ..
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=${HL_CXXFLAGS} -DCMAKE_MODULE_PATH=${PROJECT_SOURCE_DIR}/cmake -DUSE_ROOT=false -DBoost_INCLUDE_DIRS=${Boost_INCLUDE_DIR} -DBoost_LIBRARIES=${Boost_LIBRARIES} -DGSL_INCLUDE_DIR=${GSL_INCLUDE_DIR} -DGSL_LIBRARIES=${GSL_LIBRARIES}
    BUILD_COMMAND ${MAKE_PARALLEL} HEPLike_shared
    INSTALL_COMMAND ""
    )
  BOSS_backend(${name} ${ver})
  # ROOT flags not needed right now. Left as comment in case they are needed in the future
  # BOSS_backend(${name} ${ver} "--castxml-cc-opt=${ROOT_CXX_FLAG}" "-I${ROOT_INCLUDE_DIRS}")
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# SuperIso
set(name "superiso")
set(ver "4.1")
set(lib "libsuperiso")
set(dl "http://superiso.in2p3.fr/download/${name}_v${ver}_flavbit3.tgz")
set(md5 "524ac68f60fbe76f9db4b760e88e77c4")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/remove_omp.patch")
set(SI_C_FLAGS ${BACKEND_C_FLAGS})
set_compiler_warning("no-format-overflow" SI_C_FLAGS)
set_compiler_warning("no-format" SI_C_FLAGS)
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_SERIAL} CC=${CMAKE_C_COMPILER} ARFLAGS=rcs CFLAGS=${SI_C_FLAGS}
          COMMAND ar x src/libsuperiso.a
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_C_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -o ${lib}.so *.o" > make_so.sh
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
endif()

set(name "ddcalc")
set(ver "2.3.0")
set(lib "libDDCalc")
set(dl "https://github.com/GambitBSM/${name}/archive/refs/tags/v${ver}.tar.gz")
set(md5 "f70e47a4a1412dc5497744d6477505e7")
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


# MicrOmegas base (for all models)
set(name "micromegas")
set(ver "3.6.9.2")
set(dl "http://lapth.cnrs.fr/micromegas/downloadarea/code/${name}_${ver}.tgz")
set(md5 "72807f6d0ef80737554d8702b6b212c1")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_.${name}_${ver}_base)
  set(MO_C_FLAGS "${BACKEND_C_FLAGS} -fcommon")
  set_compiler_warning("no-format" MO_C_FLAGS)
  set_compiler_warning("no-implicit-function-declaration" MO_C_FLAGS)
  set(MO_CXX_FLAGS "${BACKEND_CXX_FLAGS} -fcommon")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    # Fix error due to C99 non-compliance
    set(MO_C_FLAGS "${MO_C_FLAGS} -Wno-error=implicit-function-declaration")
    set(MO_CXX_FLAGS "${MO_CXX_FLAGS} -Wno-error=implicit-function-declaration")
  endif()
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    # Find the path to libx11
    execute_process(COMMAND ${BREW} --prefix libx11 RESULT_VARIABLE BREW_RESULT_CODE OUTPUT_VARIABLE X11_INSTALL_DIR)
    if(NOT BREW_RESULT_CODE)
      STRING(REPLACE "\n" "" X11_INSTALL_DIR "${X11_INSTALL_DIR}")
      set(MO_LX11 "-L${X11_INSTALL_DIR}/lib")
    endif()
  endif()
  ExternalProject_Add(.${name}_${ver}_base
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    PATCH_COMMAND patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND sed ${dashi} -e "s|\$CC -o a\\.out test\\.c  1>/dev/null 2>/dev/null|#Fails with AppleClang: $CC -o a.out test.c  1>/dev/null 2>/dev/null|g" CalcHEP_src/getFlags
          COMMAND ${MAKE_SERIAL} LX11=${MO_LX11} flags
          COMMAND sed ${dashi} -e "s|FC =.*|FC = ${CMAKE_Fortran_COMPILER}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CC =.*|CC = ${CMAKE_C_COMPILER}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CXX =.*|CXX = ${CMAKE_CXX_COMPILER}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|FFLAGS =.*|FFLAGS = ${BACKEND_Fortran_FLAGS}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CFLAGS =.*|CFLAGS = ${MO_C_FLAGS}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|CXXFLAGS =.*|CXXFLAGS = ${MO_CXX_FLAGS}|" CalcHEP_src/FlagsForMake
          COMMAND sed ${dashi} -e "s|FC=.*|FC=\"${CMAKE_Fortran_COMPILER}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CC=.*|CC=\"${CMAKE_C_COMPILER}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CXX=.*|CXX=\"${CMAKE_CXX_COMPILER}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|FFLAGS=.*|FFLAGS=\"${CMAKE_Fortran_FLAGS}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CFLAGS=.*|CFLAGS=\"${MO_C_FLAGS}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|CXXFLAGS=.*|CXXFLAGS=\"${MO_CXX_FLAGS}\"|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|lFort=.*|lFort=|" CalcHEP_src/FlagsForSh
          COMMAND sed ${dashi} -e "s|@if(test -z \"`grep lX11 FlagsForMake|#@if(test -z \"`grep lX11 FlagsForMake|" CalcHEP_src/Makefile
          COMMAND ${MAKE_SERIAL} CFLAGS=${MO_C_FLAGS}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend base (functional alone)" ${name} ${ver} ${dir} ${dl} "yes | clean")
  set_as_default_version("backend base (functional alone)" ${name} ${ver})
endif()

# MicrOmegas MSSM model
set(model "MSSM")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/MSSM/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} CFLAGS=${MO_C_FLAGS} CXXFLAGS=${MO_CXX_FLAGS} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas ScalarSingletDM_Z2 model
set(model "ScalarSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/ScalarSingletDM_Z2/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} CFLAGS=${MO_C_FLAGS} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas ScalarSingletDM_Z3 model
set(model "ScalarSingletDM_Z3")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/ScalarSingletDM_Z3/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} CFLAGS=${MO_C_FLAGS} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas VectorSingletDM_Z2 model
set(model "VectorSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/VectorSingletDM_Z2/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} CFLAGS=${MO_C_FLAGS} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas MajoranaSingletDM_Z2 model
set(model "MajoranaSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/MajoranaSingletDM_Z2/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} CFLAGS=${MO_C_FLAGS} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()

# MicrOmegas DiracSingletDM_Z2 model
set(model "DiracSingletDM_Z2")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/DiracSingletDM_Z2/patch_${name}_${ver}_${model}")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    PATCH_COMMAND ./newProject ${model} && patch -p1 < ${patch}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${MAKE_PARALLEL} CFLAGS=${MO_C_FLAGS} sharedlib main=main.c
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend model" ${name} ${ver} ${dir}/${model} ${model} "yes | clean")
  set_as_default_version("backend model" ${name} ${ver} ${model})
endif()



# MicrOmegas DMsimpVectorMedVectorDM model
set(model "DMsimpVectorMedVectorDM")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/DMsimpVectorMedVectorDM/patch_${name}_${ver}_${model}.dif")
set(patchdir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/DMsimpVectorMedVectorDM")
check_ditch_status(${name}_${model} ${ver} ${dir})
if(NOT ditched_${name}_${model}_${ver})
  ExternalProject_Add(${name}_${model}_${ver}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND ./newProject ${model} && patch -p0 < ${patch}
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/mdlfiles ${dir}/${model}/work/models/
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir ${model} ${CMAKE_MAKE_PROGRAM} sharedlib main=main.c
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
      # Apply main patch (modifications to existing likelihoods etc.)
      PATCH_COMMAND patch -p1 < ${patch}
      # Add additional likelihoods that are not shipped with montepython
      COMMAND patch -p1 < ${patchdir}/bao_correlations_likelihood.diff
      COMMAND patch -p1 < ${patchdir}/bao_smallz_combined_2018_likelihood.diff
      COMMAND patch -p1 < ${patchdir}/des_bao_Y1_likelihood.diff
      COMMAND patch -p1 < ${patchdir}/WiggleZ_bao_highz.diff
      # Add GAMBIT specific files that will fix the likelihoods to work with GAMBIT in the 'install' step
      CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/MontePythonLike.py ${dir}/montepython/MontePythonLike_${sfver}.py
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/../MPLike_patch_script.py ${dir}/montepython/MPLike_patch_script.py
      COMMAND sed ${dashi} -e "s/X_Y_Z/${sfver}/g" ${dir}/montepython/MPLike_patch_script.py
      BUILD_COMMAND ""
      # Execute the script that fixes the likelihoods
      INSTALL_COMMAND ${PYTHON_EXECUTABLE} ${dir}/montepython/MPLike_patch_script.py
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

# MontePythonLike
set(name "montepythonlike")
set(ver "3.5.0")
set(sfver "3_5_0")
set(dl "https://github.com/brinckmann/montepython_public/archive/v${ver}.tar.gz")
set(md5 "3467ba885320817d133e32493838e571")
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
      # Apply main patch (modifications to existing likelihoods etc.)
      PATCH_COMMAND patch -p1 < ${patch}
      # Add additional likelihoods that are not shipped with montepython
      COMMAND patch -p1 < ${patchdir}/bao_correlations_likelihood.diff
      COMMAND patch -p1 < ${patchdir}/bao_smallz_combined_2018_likelihood.diff
      COMMAND patch -p1 < ${patchdir}/des_bao_Y1_likelihood.diff
      COMMAND patch -p1 < ${patchdir}/WiggleZ_bao_highz.diff
      # Add GAMBIT specific files that will fix the likelihoods to work with GAMBIT in the 'install' step
      CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/MontePythonLike.py ${dir}/montepython/MontePythonLike_${sfver}.py
      COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/../MPLike_patch_script.py ${dir}/montepython/MPLike_patch_script.py
      COMMAND sed ${dashi} -e "s/X_Y_Z/${sfver}/g" ${dir}/montepython/MPLike_patch_script.py
      BUILD_COMMAND ""
      # Execute the script that fixes the likelihoods
      INSTALL_COMMAND ${PYTHON_EXECUTABLE} ${dir}/montepython/MPLike_patch_script.py
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# Libphysica
set(name "libphysica")
set(ver "0.1.5")
set(dl "https://github.com/temken/${name}/archive/refs/tags/v${ver}.zip")
set(md5 "none")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(libphysica_dir "${dir}")
set(libphysica_ver "${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${libphysica_dir} ${name} ${ver}
    SOURCE_DIR ${libphysica_dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=${BACKEND_CXX_FLAGS} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_C_FLAGS=${BACKEND_C_FLAGS} -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF -DCODE_COVERAGE=OFF -DCMAKE_BUILD_TYPE=Release
    BUILD_COMMAND ${MAKE_PARALLEL} ${dir}
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${libphysica_dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# Obscura
set(name "obscura")
set(ver "1.1.0")
set(dl "https://github.com/temken/obscura/archive/refs/tags/v${ver}.tar.gz")
set(md5 "0a39d7a4da0757d89d041ada592a758f")
set(lib "libobscura")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  set(obscura_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
  set(obscura_C_FLAGS "${BACKEND_C_FLAGS}")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(obscura_CXX_FLAGS "${obscura_CXX_FLAGS} -Wl,-undefined,dynamic_lookup,-flat_namespace")
    set(obscura_C_FLAGS "${obscura_C_FLAGS} -Wl,-undefined,dynamic_lookup,-flat_namespace")
  endif()
  set_compiler_warning("no-unused-parameter" obscura_CXX_FLAGS)
  set_compiler_warning("no-type-limits" obscura_CXX_FLAGS)
  set_compiler_warning("no-maybe-uninitialized" obscura_CXX_FLAGS)
  set_compiler_warning("no-unused-but-set-variable" obscura_CXX_FLAGS)
  ExternalProject_Add(${name}_${ver}
    DEPENDS "castxml;libphysica"
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
          COMMAND  ${CMAKE_COMMAND} -E make_directory "${dir}/generated/"
          COMMAND ${CMAKE_COMMAND} -E echo "" > "${dir}/generated/version.hpp"
    CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_CXX_FLAGS=${obscura_CXX_FLAGS} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_C_FLAGS=${obscura_C_FLAGS} -DBUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF -DCODE_COVERAGE=OFF -DCMAKE_BUILD_TYPE=Release ${dir} -Dlibphysica_SOURCE_DIR=${libphysica_dir}
    BUILD_COMMAND ${MAKE_PARALLEL} libobscura
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
  BOSS_backend(${name} ${ver})
endif()


# Pythia
set(name "pythia")
set(ver "8.212")
set(lib "libpythia8")
set(dl "https://pythia.org/download/pythia82/pythia8212.tgz")
set(md5 "7bebd73edcabcaec591ce6a38d059fa3")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")

# Add additional compiler-specific optimisation flags and suppress some warnings from -Wextra.
set(pythia_CXXFLAGS "${BACKEND_CXX_FLAGS}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # -fast sometimes makes xsecs come out as NaN, we catch that and invalidate those points
  set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -fast")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  # Include all flags from -ffast-math, except -ffinite-math-only (which has proved to cause incorrect results), and -fno-rounding-math -fno-signaling-nans (which don't exist in Clang and are defaults anyway for gcc).
  set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -fno-math-errno -funsafe-math-optimizations")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -fcx-limited-range") # Clang doesn't have this one.
  endif()
  set_compiler_warning("no-extra" pythia_CXXFLAGS)
  set_compiler_warning("no-deprecated-declarations" pythia_CXXFLAGS)
endif()

# Add "-undefined dynamic_lookup" to linker flags on OSX
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(pythia_CXX_SHARED_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup -flat_namespace ${NO_FIXUP_CHAINS}")
  set(pythia_CXX_SONAME_FLAGS "-Wl,-dylib_install_name")
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
set(ditch_if_absent "hepmc")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
set(pythia_CXXFLAGS "${pythia_CXXFLAGS} -I${Boost_INCLUDE_DIR} -I${PROJECT_SOURCE_DIR}/contrib/slhaea/include -I${HEPMC_PATH}/local/include -I${HEPMC_PATH}/interfaces/pythia8/include")
set(pythia_CXX_SHARED_FLAGS "${pythia_CXX_SHARED_FLAGS}  -L${HEPMC_PATH}/local/lib -Wl,-rpath ${HEPMC_PATH}/local/lib -lHepMC3")

# - Actual configure and compile commands
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS hepmc
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ./configure --with-hepmc3=${HEPMC_PATH}/local --enable-shared --cxx="${CMAKE_CXX_COMPILER}" --cxx-common="${pythia_CXXFLAGS}" --cxx-shared="${pythia_CXX_SHARED_FLAGS}" --cxx-soname="${pythia_CXX_SONAME_FLAGS}" --lib-suffix=".so"
    BUILD_COMMAND ${MAKE_PARALLEL} CXX="${CMAKE_CXX_COMPILER}" lib/${lib}.so
    INSTALL_COMMAND ""
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


# Ditch all FeynHiggs if using gfortran 10 or later, as it won't compile
if("${CMAKE_Fortran_COMPILER_ID}" STREQUAL "GNU" AND NOT CMAKE_Fortran_COMPILER_VERSION VERSION_LESS 10)
  set(itch "${itch}" "feynhiggs")
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
    DOWNLOAD_COMMAND IGNORE_HTTP_CERTIFICATE=1 ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    # Fix bug preventing the use of array bounds checking.
    CONFIGURE_COMMAND sed ${dashi} -e "s#ComplexType spi_(2, 6:7, nvec, 1)#ComplexType spi_(2, 6:7, nvec, LEGS)#g" src/Decays/VecSet.F
              COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FFLAGS=${FH_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FH_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FH_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -o lib/${lib}.so build/*.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

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
    DOWNLOAD_COMMAND IGNORE_HTTP_CERTIFICATE=1 ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    # Fix bug preventing the use of array bounds checking.
    CONFIGURE_COMMAND sed ${dashi} -e "s#ComplexType spi_(2, 6:7, nvec, 1)#ComplexType spi_(2, 6:7, nvec, LEGS)#g" src/Decays/VecSet.F
              COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FFLAGS=${FH_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FH_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FH_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -o lib/${lib}.so build/*.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

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
    DOWNLOAD_COMMAND IGNORE_HTTP_CERTIFICATE=1 ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    # Fix bug preventing the use of array bounds checking.
    CONFIGURE_COMMAND sed ${dashi} -e "s#ComplexType spi_(2, 6:7, nvec, 1)#ComplexType spi_(2, 6:7, nvec, LEGS)#g" src/Decays/VecSet.F
              COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FFLAGS=${FH_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FH_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FH_CXX_FLAGS}
    BUILD_COMMAND ${MAKE_PARALLEL}
          COMMAND ${CMAKE_COMMAND} -E make_directory lib
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -o lib/${lib}.so build/*.o" > make_so.sh
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
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -o lib/${lib}.so *.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

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
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -o lib/${lib}.so *.o" > make_so.sh
          COMMAND chmod u+x make_so.sh
          COMMAND ./make_so.sh
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
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
          COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_Fortran_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -o lib/${lib}.so ./*.o ../../${hb_name}/${hb_ver}/*.o" > make_so.sh
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
    BUILD_COMMAND ${MAKE_PARALLEL} F90=${CMAKE_Fortran_COMPILER} FFLAGS=${SPheno_FLAGS} ${lib}
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
set(GM2CALC_MAKESHAREDLIB "${CMAKE_CXX_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS}")
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
    BUILD_COMMAND ${MAKE_PARALLEL} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${GM2CALC_CXX_FLAGS} EIGENFLAGS=-I${EIGEN3_INCLUDE_DIR} BOOSTFLAGS=-I${Boost_INCLUDE_DIR} MAKESHAREDLIB=${GM2CALC_MAKESHAREDLIB} sharedlib
    INSTALL_COMMAND ""
  )
  BOSS_backend(${name} ${ver})
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
endif()

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
set(GM2CALC_MAKESHAREDLIB "${CMAKE_CXX_COMPILER} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} ${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}_error.dif
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${MAKE_PARALLEL} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${GM2CALC_CXX_FLAGS} EIGENFLAGS=-I${EIGEN3_INCLUDE_DIR} BOOSTFLAGS=-I${Boost_INCLUDE_DIR} MAKESHAREDLIB=${GM2CALC_MAKESHAREDLIB} alllib
    INSTALL_COMMAND ""
  )
  BOSS_backend(${name} ${ver})
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# phc
set(name "phc")
set(ver "2.4.77")
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(dl "https://github.com/janverschelde/PHCpack/releases/download/v2.4.77/mactel64y_phcv24p.tar.gz")
  #set(md5 "2e347b1794201d7ca462d2e4b5630147")
  set(md5 "none")
else()
  set(dl "https://github.com/janverschelde/PHCpack/releases/download/v2.4.77/x86_64phcv24p.tar.gz")
  #set(md5 "7b589002b78037c40a8c52269bf39c0e")
  set(md5 "none")
endif()
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
          DOWNLOAD_COMMAND IGNORE_HTTP_CERTIFICATE=1 ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
          SOURCE_DIR ${dir}
          BUILD_IN_SOURCE 1
          CONFIGURE_COMMAND ""
          BUILD_COMMAND ""
          INSTALL_COMMAND ""
          )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# hom4ps
set(name "hom4ps")
set(ver "2.0")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(dl "http://www.math.nsysu.edu.tw/~leetsung/works/HOM4PS_soft_files/HOM4PS2_MacOSX.tar.gz")
  set(md5 "daa880bd51fc166a9a2f85332b025fae")
else()
  set(dl "http://www.math.nsysu.edu.tw/~leetsung/works/HOM4PS_soft_files/HOM4PS2_64-bit.tar.gz")
  set(md5 "134a2539faf2c0596eaf039e7ccc1677")
endif()

set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
          DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
          SOURCE_DIR ${dir}
          BUILD_IN_SOURCE 1
          CONFIGURE_COMMAND ""
          BUILD_COMMAND ""
          INSTALL_COMMAND ""
          )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean) # FIGURE THIS OUT
  set_as_default_version("backend" ${name} ${ver})
endif()


# Vevacious
set(name "vevacious")
set(ver "1.0")
set(dl "http://github.com/JoseEliel/VevaciousPlusPlus_Development/archive/refs/heads/master.zip")
set(md5 "none") # Keep none for now because there is no tagged release of vevacious yet
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patchdir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(Minuit_name "minuit2")
set(Minuit_ver "6.23.01")
set(Minuit_lib_name "libminuit2")
set(phc_ver "2.4.77")
set(hom4ps_ver "2.0")
set(Minuit_include "${PROJECT_SOURCE_DIR}/ScannerBit/installed/${Minuit_name}/${Minuit_ver}/inc/")
set(Minuit_lib "${PROJECT_SOURCE_DIR}/ScannerBit/installed/${Minuit_name}/${Minuit_ver}/lib/")
set(VPP_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS}")
set(VPP_CXX_FLAGS "${BACKEND_CXX_FLAGS} -I./include/ -I./include/LHPC/ -I${Boost_INCLUDE_DIR} -I${EIGEN3_INCLUDE_DIR} -I${Minuit_include}")
set_compiler_warning("no-unused-local-typedefs" VPP_CXX_FLAGS)
set_compiler_warning("no-unused-parameter" VPP_CXX_FLAGS)
set_compiler_warning("no-reorder" VPP_CXX_FLAGS)
set_compiler_warning("no-deprecated-copy" VPP_CXX_FLAGS)
set_compiler_warning("no-unused-variable" VPP_CXX_FLAGS)
set_compiler_warning("no-pessimizing-move" VPP_CXX_FLAGS)
set(VPP_CMAKE_FLAGS -DCMAKE_C_FLAGS=${BACKEND_C_FLAGS} -DCMAKE_CXX_FLAGS=${VPP_CXX_FLAGS} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_SHARED_LINKER_FLAGS=${VPP_SHARED_LINKER_FLAGS} -DEIGEN3_INCLUDE_DIR=${EIGEN3_INCLUDE_DIR} -DBoost_INCLUDE_DIR=${Boost_INCLUDE_DIR} -DWITHIN_GAMBIT=True -DSILENT_MODE=TRUE -DMinuit_include=${Minuit_include} -DMinuit_lib=${Minuit_lib})
set(BOSSregex "s#cpp)#cpp   source/BOSS_factory_VevaciousPlusPlus.cpp       source/BOSS_wrapperutils.cpp        source/BOSS_VevaciousPlusPlus.cpp)#g")
set(FLAGSregex1 "s#_FLAGS} -O3 -fPIC#_FLAGS}#g")
set(FLAGSregex2 "s#_FLAGS} -Wall -Wno-unused-local-typedefs -O3 -fPIC -fopenmp#_FLAGS}#g")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
          DEPENDS ${Minuit_name}_${Minuit_ver}
          DEPENDS phc_${phc_ver}
          DEPENDS hom4ps_${hom4ps_ver}
          DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
          SOURCE_DIR ${dir}
          PATCH_COMMAND patch -p1 < ${patchdir}/patch_${name}_${ver}.dif
          CMAKE_COMMAND ${CMAKE_COMMAND} ${dir}
          CMAKE_ARGS ${VPP_CMAKE_FLAGS}
          BUILD_COMMAND ${MAKE_PARALLEL} ${VPP_FLAGS} MINUITLIBDIR=${Minuit_lib} MINUITLIBNAME=${Minuit_lib_name} VevaciousPlusPlus-lib
                COMMAND ${CMAKE_COMMAND} -E make_directory ${patchdir}/VevaciousPlusPlus/ModelFiles/
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/VevaciousPlusPlus/ModelFiles/ ${dir}/ModelFiles/
          INSTALL_COMMAND ""
          )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
  BOSS_backend(${name} ${ver})
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


# DirectDM
set(name "directdm")
set(ver "2.2.0")
set(dl "https://github.com/DirectDM/directdm-py/archive/v2.2.0.tar.gz")
set(md5 "c22d26ae7bec44bbfe1eb5f4306a23e0")
set(lib "libdirectdm")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Python")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# CalcHEP
set(name "calchep")
set(ver "3.6.27")
set(dl "http://theory.sinp.msu.ru/~pukhov/CALCHEP/calchep_3.6.27.tgz")
set(md5 "7914181e15791fe03373bd37819ef638")
set(lib "libcalchep")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(patchdir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/")
set(ditch_if_absent "X11")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  # Add -fcommon compiler flag to tell the compiler to accept and merge a multiple variable definiton in calchep
  set(calchep_CXX_FLAGS "${BACKEND_CXX_FLAGS} -fcommon")
  set(calchep_C_FLAGS "${BACKEND_C_FLAGS} -fcommon")
  set(calchep_Fortran_FLAGS "${BACKEND_Fortran_FLAGS} -fcommon")
  set_compiler_warning("no-format" calchep_C_FLAGS)
  set_compiler_warning("no-implicit-function-declaration" calchep_C_FLAGS)
  set_compiler_warning("no-int-conversion" calchep_C_FLAGS)
  set_compiler_warning("no-incompatible-pointer-types" calchep_C_FLAGS)
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(calchep_CXX_FLAGS "${calchep_CXX_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS}")
    set(calchep_C_FLAGS "${calchep_C_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS}")
    set(calchep_Fortran_FLAGS "${calchep_Fortran_FLAGS} ${NO_FIXUP_CHAINS}")
  endif()
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    # Fix error due to C99 non-compliance
    set(calchep_C_FLAGS "${calchep_C_FLAGS} -Wno-error=implicit-function-declaration")
  endif()
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    # Find the path to libx11
    execute_process(COMMAND ${BREW} --prefix libx11 RESULT_VARIABLE BREW_RESULT_CODE OUTPUT_VARIABLE X11_INSTALL_DIR)
    if(NOT BREW_RESULT_CODE)
      STRING(REPLACE "\n" "" X11_INSTALL_DIR "${X11_INSTALL_DIR}")
      set(calchep_LX11 "-L${X11_INSTALL_DIR}/lib")
    endif()
  endif()
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E copy ${patchdir}/main.c ${dir}/c_source/dynamicME/main.c
              COMMAND ${CMAKE_COMMAND} -E copy ${dir}/c_source/strfun/pdf_dummy.c ${dir}/c_source/num/pdf_dummy.c
    PATCH_COMMAND patch -p0 < ${patchdir}/patch_${name}_${ver}.dif
    BUILD_COMMAND ${MAKE_SERIAL} flags
          COMMAND sed ${dashi} -e "s#GAMBITDIR#${PROJECT_SOURCE_DIR}#g" ${dir}/c_source/dynamicME/vp_dynam.c
          COMMAND sed ${dashi} -e "s|\$CC -o a\\.out test\\.c  1>/dev/null 2>/dev/null|#Fails with AppleClang: $CC -o a.out test.c  1>/dev/null 2>/dev/null|g" ${dir}/getFlags
          COMMAND LX11=${calchep_LX11} ${dir}/getFlags
          COMMAND sed ${dashi} -e "s|FC =.*|FC = ${CMAKE_Fortran_COMPILER}|" ${dir}/FlagsForMake
          COMMAND sed ${dashi} -e "s|CC =.*|CC = ${CMAKE_C_COMPILER}|" ${dir}/FlagsForMake
          COMMAND sed ${dashi} -e "s|CXX =.*|CXX = ${CMAKE_CXX_COMPILER}|" ${dir}/FlagsForMake
          COMMAND sed ${dashi} -e "s|FFLAGS =.*|FFLAGS = ${calchep_Fortran_FLAGS}|" ${dir}/FlagsForMake
          COMMAND sed ${dashi} -e "s|CFLAGS =.*|CFLAGS = ${calchep_C_FLAGS}|" ${dir}/FlagsForMake
          COMMAND sed ${dashi} -e "s|CXXFLAGS =.*|CXXFLAGS = ${calchep_CXX_FLAGS}|" ${dir}/FlagsForMake
          COMMAND sed ${dashi} -e "s|FC=.*|FC=\"${CMAKE_Fortran_COMPILER}\"|" ${dir}/FlagsForSh
          COMMAND sed ${dashi} -e "s|CC=.*|CC=\"${CMAKE_C_COMPILER}\"|" ${dir}/FlagsForSh
          COMMAND sed ${dashi} -e "s|CXX=.*|CXX=\"${CMAKE_CXX_COMPILER}\"|" ${dir}/FlagsForSh
          COMMAND sed ${dashi} -e "s|FFLAGS=.*|FFLAGS=\"${calchep_Fortran_FLAGS}\"|" ${dir}/FlagsForSh
          COMMAND sed ${dashi} -e "s|CFLAGS=.*|CFLAGS=\"${calchep_C_FLAGS}\"|" ${dir}/FlagsForSh
          COMMAND sed ${dashi} -e "s|CXXFLAGS=.*|CXXFLAGS=\"${calchep_CXX_FLAGS}\"|" ${dir}/FlagsForSh
          COMMAND sed ${dashi} -e "s|lFort=.*|lFort=|" ${dir}/FlagsForSh
          COMMAND sed ${dashi} -e "s|@if(test -z \"`grep lX11 FlagsForMake|#@if(test -z \"`grep lX11 FlagsForMake|" ${dir}/Makefile
          COMMAND ${MAKE_SERIAL}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${patchdir}/Models/ ${dir}/models/
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} "yes | clean")
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
    CONFIGURE_COMMAND sed ${dashi} -e s/C_UNIV_SWITCH="-arch i386 -arch x86_64"/C_UNIV_SWITCH="-arch ${CMAKE_SYSTEM_PROCESSOR}"/g configure
              COMMAND ./configure --includedir=${dir}/include --libdir=${dir}/lib FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${BACKEND_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${BACKEND_CXX_FLAGS} SHLIB_SUFFIX=${CFITSIO_SO}
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
  #set_as_default_version("backend" ${name} ${ver})
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
          COMMAND sed ${dashi} -e "s#x86_64#${CMAKE_SYSTEM_PROCESSOR}#g" waf_tools/mbits.py
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "CC=${CMAKE_C_COMPILER} FC=${CMAKE_Fortran_COMPILER} LDFLAGS=\"${CMAKE_SHARED_LINKER_FLAGS}\" CFLAGS=\"${BACKEND_C_FLAGS}\" ${PYTHON_EXECUTABLE} ${dir}/waf configure --cfitsio_include=${cfitsio_dir}/include --cfitsio_lib=${cfitsio_dir}/lib ${mkl_libs_option} --no_pytools" > run_waf.sh
              COMMAND chmod u+x run_waf.sh
              COMMAND ./run_waf.sh
    BUILD_COMMAND ""
    INSTALL_COMMAND C_INCLUDE_PATH=$(C_INCLUDE_PATH):${PYTHON_INCLUDE_DIR} ${PYTHON_EXECUTABLE} ${dir}/waf install --no_pytools
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# Fastjet
set(name "fastjet")
set(ver "3.3.2")
set(dl "https://fastjet.fr/repo/fastjet-3.3.2.tar.gz")
set(md5 "ca3708785c9194513717a54c1087bfb0")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
# OpenMP flags don't play nicely with clang and FastJet's antiquated libtoolized build system.
string(REGEX REPLACE "-Xclang -fopenmp" "" FJ_C_FLAGS "${BACKEND_C_FLAGS}")
string(REGEX REPLACE "-Xclang -fopenmp" "" FJ_CXX_FLAGS "${BACKEND_CXX_FLAGS}")
# FastJet 3.3.2 depends on std::auto_ptr which is removed in c++17, so we need to fall back to c++14 (or c++11)
string(REGEX REPLACE "-std=c\\+\\+17" "-std=c++14" FJ_CXX_FLAGS "${FJ_CXX_FLAGS}")
string(REGEX REPLACE "-std=c\\+\\+17" "-std=c++14" FJ_C_FLAGS "${FJ_C_FLAGS}")
set_compiler_warning("no-deprecated-declarations" FJ_CXX_FLAGS)
set_compiler_warning("no-deprecated-copy" FJ_CXX_FLAGS)
set(FJ_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS}")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ./configure FC=${CMAKE_Fortran_COMPILER} FCFLAGS=${BACKEND_Fortran_FLAGS} FFLAGS=${BACKEND_Fortran_FLAGS} CC=${CMAKE_C_COMPILER} CFLAGS=${FJ_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FJ_CXX_FLAGS} LIBS=${FJ_LINKER_FLAGS}  --prefix=${dir}/local --enable-allcxxplugins --enable-silent-rules
    BUILD_COMMAND ${MAKE_PARALLEL} install
    INSTALL_COMMAND ""
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  #set_as_default_version("backend" ${name} ${ver})
endif()


# Fjcontrib
set(name "fjcontrib")
set(ver "1.041")
set(dl "http://fastjet.hepforge.org/contrib/downloads/${name}-${ver}.tar.gz")
set(md5 "b37674a8701af52b58ebced94a270877")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(fastjet_name "fastjet")
set(fastjet_ver "3.3.2")
set(fastjet_dir "${PROJECT_SOURCE_DIR}/Backends/installed/${fastjet_name}/${fastjet_ver}")
set(FJCONTRIB_CXX_FLAGS ${FJ_CXX_FLAGS})
#set(FJCONTRIB_CXX_FLAGS ${BACKEND_CXX_FLAGS})
set_compiler_warning("no-deprecated-declarations" FJCONTRIB_CXX_FLAGS)
set_compiler_warning("no-unused-parameter" FJCONTRIB_CXX_FLAGS)
set_compiler_warning("no-sign-compare" FJCONTRIB_CXX_FLAGS)
set_compiler_warning("no-catch-value" FJCONTRIB_CXX_FLAGS)
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS ${fastjet_name}_${fastjet_ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ./configure CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${FJCONTRIB_CXX_FLAGS} --fastjet-config=${fastjet_dir}/fastjet-config --prefix=${fastjet_dir}/local
    BUILD_COMMAND ${MAKE_PARALLEL} CXX="${CMAKE_CXX_COMPILER}" fragile-shared-install
    INSTALL_COMMAND ${MAKE_INSTALL_PARALLEL}
  )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  #set_as_default_version("backend" ${name} ${ver})
endif()

# Rivet
set(name "rivet")
set(ver "3.1.5")
set(Rivet_ver "${ver}")
set(dl "https://rivet.hepforge.org/downloads/?f=Rivet-${ver}.tar.gz")
set(md5 "7f3397b16386c0bfcb49420c2eb395b1")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(yoda_name "yoda")
set(yoda_dir "${YODA_PATH}/local")
set(hepmc_name "hepmc")
set(hepmc_dir "${HEPMC_PATH}/local")
set(fastjet_name "fastjet")
set(fastjet_ver "3.3.2")
set(fastjet_dir "${PROJECT_SOURCE_DIR}/Backends/installed/${fastjet_name}/${fastjet_ver}/local")
set(fjcontrib_name "fjcontrib")
set(fjcontrib_ver "1.041")
#set(Rivet_CXX_FLAGS "${BACKEND_CXX_FLAGS} -I${dir}/include/Rivet -O3")
set(Rivet_CXX_FLAGS "${FJ_CXX_FLAGS} -I${dir}/include/Rivet -O3")
set_compiler_warning("no-deprecated-declarations" Rivet_CXX_FLAGS)
set_compiler_warning("no-deprecated-copy" Rivet_CXX_FLAGS)
set_compiler_warning("no-type-limits" Rivet_CXX_FLAGS)
set_compiler_warning("no-unused-parameter" Rivet_CXX_FLAGS)
set_compiler_warning("no-ignored-qualifiers" Rivet_CXX_FLAGS)
#set(Rivet_C_FLAGS "${BACKEND_C_FLAGS} -I${dir}/include/Rivet")
set(Rivet_C_FLAGS "${FJ_C_FLAGS} -I${dir}/include/Rivet")
# TODO: Separate the library and linker flags to avoid compiler complaints
set(Rivet_LD_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS} -L${dir}/include/Rivet -L${HEPMC_PATH}/local/lib -Wl,-rpath,${HEPMC_PATH}/local/lib")
set(Rivet_dirs "${dir}/src/Core" "${dir}/src/Projections" "${dir}/src/Tools" "${dir}/src/AnalysisTools" "${dir}/src")

# For MacOS we need to specify the (weird) root directory for headers (isysroot)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(Rivet_CPP_FLAGS "-isysroot${CMAKE_OSX_SYSROOT}")
else()
  set(Rivet_CPP_FLAGS "")
endif()

set(patch_dir "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(patch "${patch_dir}/patch_${name}_${ver}.dif")
## Rivet needs to be compiled with c++14 or c++17, otherwise it will fail to compile
set(ditch_if_absent "HepMC;YODA;c++14")
## If cython is not installed disable the python extension
gambit_find_python_module(cython)
if(PY_cython_FOUND)
  set(pyext yes)
  set(Rivet_PY_PATH "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}/local/lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/site-packages")
  set(Rivet_LIB "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}/local/lib/libRivet.so")
  message("   Backends depending on Rivet's python extension will be enabled.")
else()
  set(pyext no)
  message("   Backends depending on Rivet's python extension (e.g. Contur) will be disabled.")
endif()

check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DEPENDS castxml
    DEPENDS ${yoda_name}
    DEPENDS ${hepmc_name}
    DEPENDS ${fjcontrib_name}_${fjcontrib_ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    PATCH_COMMAND patch -p1 < ${patch}
    CONFIGURE_COMMAND ./configure CC=${CMAKE_C_COMPILER} CFLAGS=${Rivet_C_FLAGS} CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${Rivet_CXX_FLAGS} LDFLAGS=${Rivet_LD_FLAGS} CPPFLAGS=${Rivet_CPP_FLAGS} PYTHON=${PYTHON_EXECUTABLE} --with-yoda=${yoda_dir} --with-hepmc3=${hepmc_dir} -with-fastjet=${fastjet_dir} --prefix=${dir}/local --enable-shared=yes --enable-static=no --libdir=${dir}/local/lib --enable-pyext=${pyext}
          COMMAND ${CMAKE_COMMAND} -E echo "Rivet_dirs=\"${Rivet_dirs}\"" > touch_files.sh
          COMMAND sh -c "cat ${patch_dir}/touch_files.sh" >> touch_files.sh
          COMMAND chmod u+x touch_files.sh
          COMMAND ./touch_files.sh
    BUILD_COMMAND ${MAKE_PARALLEL} libRivet.so
    INSTALL_COMMAND ""
  )
  BOSS_backend(${name} ${ver})
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()

# Contur
set(name "contur")
set(ver "2.1.1")
set(dl "https://gitlab.com/hepcedar/${name}/-/archive/${name}-${ver}/${name}-${name}-${ver}.tar.gz")
set(md5 "ecb91229775b62e5d71c8089d78b2ff6")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(contur_dir "${dir}/contur")
set(init_file ${contur_dir}/init_by_GAMBIT.py)
set(Rivet_name "rivet")
set(ditch_if_absent "Python;SQLITE3;YODA;HepMC;Rivet")
set(required_modules "cython;configobj;pandas;matplotlib;")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}/patch_${name}_${ver}.dif")
check_ditch_status(${name} ${ver} ${dir} ${ditch_if_absent})
if(NOT ditched_${name}_${ver})
  check_python_modules(${name} ${ver} ${required_modules})
  if(modules_missing_${name}_${ver})
    inform_of_missing_modules(${name} ${ver} ${modules_missing_${name}_${ver}})
  else()
    ExternalProject_Add(${name}_${ver}
      DEPENDS ${Rivet_name}_${Rivet_ver}
      DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
      SOURCE_DIR ${dir}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch -p1 < ${patch}
      CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "import sys" > ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "import os" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "sys.path.append('${YODA_PY_PATH}')" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "sys.path.append('${Rivet_PY_PATH}')" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "sys.path.append('${dir}')" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "os.environ[\"CONTUR_ROOT\"]='${dir}'" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "from ctypes import *" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "cdll.LoadLibrary(\"${Rivet_LIB}\")" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "from run import run_analysis" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "from run import arg_utils" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "from data import static_db" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "from io import StringIO" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "from rivet import addAnalysisLibPath, addAnalysisDataPath" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "addAnalysisLibPath(\"${dir}/data/Rivet\")" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "addAnalysisDataPath(\"${dir}/data/Rivet\")" >> ${init_file}
                COMMAND ${CMAKE_COMMAND} -E echo "addAnalysisDataPath(\"${dir}/data/Theory\")" >> ${init_file}
      BUILD_COMMAND ${MAKE_PARALLEL} "data/DB/analyses.db"
      INSTALL_COMMAND ""
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} clean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# Linker flags used in the class makefile when linking executables
set(CLASSY_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${NO_FIXUP_CHAINS}")
# This is the link command used by cython when compiling Python.
set(CYTHON_LINK "LDSHARED=${CMAKE_C_COMPILER} ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} ${CLASSY_LINKER_FLAGS}")
# Modified OpenMP settings and linker flags for classy
if(FOUND_BREW_OPENMP)
  set(CLASSY_OpenMP_C_FLAGS "${OpenMP_C_FLAGS} -I${BREW_LIBOMP_PREFIX}/include")
else()
  set(CLASSY_OpenMP_C_FLAGS "${OpenMP_C_FLAGS}")
endif()
if(OpenMP_omp_LIBRARY)
  set(lgomp_REPLACEMENT "'${OpenMP_omp_LIBRARY}'")
else()
  set(lgomp_REPLACEMENT "'-lgomp'")
endif()
if("${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
  set(lgomp_REPLACEMENT "${lgomp_REPLACEMENT},  '-arch', '${CMAKE_SYSTEM_PROCESSOR}'")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set(lgomp_REPLACEMENT "${lgomp_REPLACEMENT},  '-march=native'")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
  set(lgomp_REPLACEMENT "${lgomp_REPLACEMENT},  '-xHost'")
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
set(required_modules "cython,numpy,scipy,six")
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
      COMMAND sed ${dashi} -e "s#'-lgomp'#${lgomp_REPLACEMENT}#g" python/setup.py
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${CLASSY_OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_C_FLAGS} LDFLAG=${CLASSY_LINKER_FLAGS} PYTHON=${PYTHON_EXECUTABLE} ${CYTHON_LINK} CFLAGS=${BACKEND_C_FLAGS} all
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
set(required_modules "cython,numpy,scipy,six")
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
      COMMAND sed ${dashi} -e "s#'-lgomp'#${lgomp_REPLACEMENT}#g" python/setup.py
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${CLASSY_OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_C_FLAGS} LDFLAG=${CLASSY_LINKER_FLAGS} PYTHON=${PYTHON_EXECUTABLE} ${CYTHON_LINK} CFLAGS=${BACKEND_C_FLAGS} all
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
set(required_modules "cython,numpy,scipy,six")
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
      COMMAND sed ${dashi} -e "s#'-lgomp'#${lgomp_REPLACEMENT}#g" python/setup.py
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${CLASSY_OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_C_FLAGS} LDFLAG=${CLASSY_LINKER_FLAGS} PYTHON=${PYTHON_EXECUTABLE} ${CYTHON_LINK} CFLAGS=${BACKEND_C_FLAGS} all
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
set(ver "3.1.0")
set(sfver "3_1_0")
set(lib "classy")
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
set(dl "https://github.com/lesgourg/class_public/archive/v${ver}.tar.gz")
set(md5 "01b9ece412d34300df6c7984198c0d43")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(ditch_if_absent "Python")
set(required_modules "cython,numpy,scipy,six")
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
      COMMAND sed ${dashi} -e "s#'-lgomp'#${lgomp_REPLACEMENT}#g" python/setup.py
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${CLASSY_OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_C_FLAGS} LDFLAG=${CLASSY_LINKER_FLAGS} PYTHON=${PYTHON_EXECUTABLE} ${CYTHON_LINK} CFLAGS=${BACKEND_C_FLAGS} all
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
set(required_modules "cython,numpy,scipy,six")
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
      COMMAND sed ${dashi} -e "s#'-lgomp'#${lgomp_REPLACEMENT}#g" python/setup.py
      COMMAND sed ${dashi} -e "s#autosetup.py install#autosetup.py build#g" Makefile
      COMMAND sed ${dashi} -e "s#rm -f libclass.a#rm -rf libclass.a lib#g" Makefile
      COMMAND sed ${dashi} -e "s#\"[.]\"#\"${dir}\"#g" include/common.h
      BUILD_COMMAND ${MAKE_PARALLEL} CC=${CMAKE_C_COMPILER} OMPFLAG=${CLASSY_OpenMP_C_FLAGS} OPTFLAG= CCFLAG=${BACKEND_C_FLAGS} LDFLAG=${CLASSY_LINKER_FLAGS} PYTHON=${PYTHON_EXECUTABLE} ${CYTHON_LINK} CFLAGS=${BACKEND_C_FLAGS} all
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
set(patch "${PROJECT_SOURCE_DIR}/Backends/patches/${name}/${ver}")
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
      PATCH_COMMAND patch -p1 < ${patch}/${name}_${ver}.diff
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
# Currently archived backend
set(dl "https://github.com/GambitBSM/archived_backends/raw/main/multimodecode_2.0.0.tar.gz")
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


# simplexs
set(name "simplexs")
set(ver "1.0")
set(dl "https://github.com/GambitBSM/gambit_simplexs/archive/refs/heads/main.zip")
set(dir "${PROJECT_SOURCE_DIR}/Backends/examples/simple_xs/1.0/")
set(md5 "5bf400a48e30049e92bff80b69cfd523")
check_ditch_status(${name} ${ver} ${dir})
if(NOT ditched_${name}_${ver})
  ExternalProject_Add(${name}_${ver}
    DOWNLOAD_COMMAND ${DL_BACKEND} ${dl} ${md5} ${dir} ${name} ${ver}
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
endif()


# pbarlike
set(name "pbarlike")
set(ver "1.0")
set(lib "libpbarlike")
set(dl "https://github.com/sowmiya-balan/pbarlike/archive/refs/tags/v1.0.tar.gz")
set(md5 "f72c48ffc9913102b50268cc456cc3e4")
set(md5 "none")
set(dir "${PROJECT_SOURCE_DIR}/Backends/installed/${name}/${ver}")
set(required_modules "numpy,tensorflow,iminuit,h5py")
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
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
    )
  endif()
  add_extra_targets("backend" ${name} ${ver} ${dir} ${dl} distclean)
  set_as_default_version("backend" ${name} ${ver})
endif()


# Alternative download command for getting unreleased things from the gambit_internal repository.
# If you don't know what that is, you don't need to tinker with these.
#    DOWNLOAD_COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --yellow --bold ${private_code_warning1}
#             COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold ${private_code_warning2}
#             COMMAND ${CMAKE_COMMAND} -E copy_directory ${loc} ${dir}
