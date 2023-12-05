#  GUM: GAMBIT Universal Models
#  ****************************
#  \file
#
#  CMake configuration for contributed
#  packages in GUM.
#
# *****************************************
#
#  \author Sanjay Bloor
#          (sanjay.bloor12@imperial.ac.uk)
#  \date 2018, 2019, 2020
#
#  \author Tomas Gonzalo
#          (tomas.gonzalo@monash.edu)
#  \date 2020
#
#  **************************************

add_custom_target(nuke-contrib)
add_custom_target(clean-contrib)

# Define clean and nuke targets for contrib packages
function(add_contrib_clean_and_nuke package dir)
  set(stamp_path "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}")
  set(build_path "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-build")
  set(clean_stamps ${stamp_path}-configure ${stamp_path}-build ${stamp_path}-install ${stamp_path}-done)
  set(nuke_stamps ${stamp_path}-download ${stamp_path}-mkdir ${stamp_path}-patch ${stamp_path}-update)
  add_custom_target(clean-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${clean_stamps}
                                     COMMAND [ -e ${dir} ] && cd ${dir} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} clean) || true
                                   COMMAND [ -e ${build_path} ] && cd ${build_path} && ([ -e makefile ] || [ -e Makefile ] && ${CMAKE_MAKE_PROGRAM} clean) || true)
  add_dependencies(distclean clean-${package})
  add_custom_target(nuke-${package} COMMAND ${CMAKE_COMMAND} -E remove -f ${nuke_stamps}
                                    COMMAND ${CMAKE_COMMAND} -E remove_directory "${dir}")
#                                    COMMAND ${CMAKE_COMMAND} -E remove_directory "${build_path}"
  add_dependencies(nuke-${package} clean-${package})
  add_dependencies(nuke-all nuke-${package})
endfunction()

# Macro to add all additional targets for a contrib packages
macro(add_extra_targets package dir)
  add_contrib_clean_and_nuke(${package} ${dir})
  add_dependencies(clean-contrib clean-${package})
  add_dependencies(nuke-contrib nuke-${package})
  set(build_stamp "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}-build")
  add_custom_target(check-rebuild-${package} ${CMAKE_COMMAND} -E remove -f ${build_stamp})
  add_dependencies(${package} check-rebuild-${package})
  set(download_stamp "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp/${package}-download")
  ExternalProject_Add_Step(${package} verify
    COMMAND test -e ${rmstring}-failed && ${CMAKE_COMMAND} -E remove -f ${download_stamp} ${download_stamp}-failed || true
    DEPENDEES download
    DEPENDERS patch configure build)
endmacro()

# Download FeynRules
set(name "FeynRules")
set(ver "2.3.41")
# Archived backend
set(dl "https://github.com/GambitBSM/archived_backends/raw/main/feynrules-${ver}.tar.gz")
set(md5 "d0a075dc8fa12d4a7ebcc966350e4365")
set(patch "${CMAKE_SOURCE_DIR}/cmake/patch_${name}.dif")
# For Mathematica versions > 12.2 patch FR and SARAH to use the legacy version of ValueQ
if(${Mathematica_VERSION} VERSION_LESS "12.2")
  set(patch_command "")
else()
  set(patch_command patch -p1 < ${patch}) 
endif()
set(dir "${CMAKE_SOURCE_DIR}/contrib/${name}")
set(FEYNRULES_PATH "${dir}")
set(HAVE_FEYNRULES 1)
EXTERNALPROJECT_ADD(
    FeynRules
    URL ${dl}
    URL_MD5 ${md5}
    UPDATE_COMMAND ""
    PATCH_COMMAND ${patch_command}
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
add_extra_targets(${name} ${dir})

# Download SARAH
set(name "SARAH")
set(ver "4.14.0")
set(dl "https://sarah.hepforge.org/downloads/?f=SARAH-${ver}.tar.gz")
set(md5 "850b74625e531b93fd43a32c181c825b")
set(patch "${CMAKE_SOURCE_DIR}/cmake/patch_${name}.dif")
# For Mathematica versions > 12.2 patch FR and SARAH to use the legacy version of ValueQ
if(${Mathematica_VERSION} VERSION_LESS "12.2")
  set(patch_command "")
else()
  set(patch_command patch -p1 < ${patch}) 
endif()
set(dir "${CMAKE_SOURCE_DIR}/contrib/${name}")
set(SARAH_VERSION ${ver})
set(SARAH_PATH "${dir}")
set(HAVE_SARAH 1)
EXTERNALPROJECT_ADD(
    SARAH
    URL ${dl}
    URL_MD5 ${md5}
    UPDATE_COMMAND ""
    PATCH_COMMAND patch -p1 < ${patch}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
add_extra_targets(${name} ${dir})

# Download MadGraph
set(name "MadGraph")
set(dir "${CMAKE_SOURCE_DIR}/contrib/${name}")
set(ver "2.8.3.2")
set(dl "https://launchpad.net/mg5amcnlo/2.0/2.8.x/+download/MG5_aMC_v${ver}.tar.gz")
set(md5 "e409328828d45d159c8b6b83d02067ba")
set(patch "${CMAKE_SOURCE_DIR}/cmake/patch_${name}.dif")
EXTERNALPROJECT_ADD(
    MadGraph
    URL ${dl}
    URL_MD5 ${md5}
    UPDATE_COMMAND ""
    PATCH_COMMAND patch -p1 < ${patch}
    SOURCE_DIR ${dir}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
add_extra_targets(${name} ${dir})

# Download Pythia
set(name "Pythia")
set(dir "${CMAKE_SOURCE_DIR}/contrib/${name}")
set(dl "https://pythia.org/download/pythia82/pythia8212.tgz")
set(ver "212")
set(md5 "7bebd73edcabcaec591ce6a38d059fa3")
set(BASE_PYTHIA_VERSION ${ver})
set(PYTHIA_MD5 ${md5})
EXTERNALPROJECT_ADD(
    Pythia
    URL ${dl}
    URL_MD5 ${md5}
    UPDATE_COMMAND ""
    PATCH_COMMAND  ""
    SOURCE_DIR ${dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
add_extra_targets(${name} ${dir})

# Download SPheno
set(name "SPheno")
set(dir "${CMAKE_SOURCE_DIR}/contrib/${name}")
set(ver "4.0.3")
set(dl http://www.hepforge.org/archive/spheno/SPheno-${ver}.tar.gz)
set(md5 "64787d6c8ce03cac38aec53d34ac46ad")
set(SPHENO_DIR ${dir})
set(SPHENO_VERSION ${ver})
ExternalProject_Add(
  SPheno
  URL ${dl}
  URL_MD5 ${md5}
  SOURCE_DIR ${dir}
  PATCH_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
add_extra_targets(${name} ${dir})
