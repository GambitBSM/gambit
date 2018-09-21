# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  CMake CMakeLists.txt file for stripped down
#  version of yaml-cpp 0.6.2.
#
#  Adapted from the original CMakeLists.txt for
#  integration into GAMBIT.
#
#************************************************
#
#  Authors (add name and date if you modify):
#
#  \author Antje Putze
#          (antje.putze@lapth.cnrs.fr)
#  \date 2015 Feb
#
#  \author Ben Farmer
#          (ben.farmer@gmail.com)
#  \date 2016 Jan
#
#  \author José Eliel Camargo-Molina
#          (Elielcamargomolina@gmail.com)
#  \date 2018 Aug
#
#************************************************

file(GLOB sources "src/[a-zA-Z]*.cpp")
file(GLOB_RECURSE public_headers "include/yaml-cpp/[a-zA-Z]*.h")
file(GLOB private_headers "src/[a-zA-Z]*.h")

file(GLOB contrib_sources "src/contrib/[a-zA-Z]*.cpp")
file(GLOB contrib_public_headers "include/yaml-cpp/contrib/[a-zA-Z]*.h")
file(GLOB contrib_private_headers "src/contrib/[a-zA-Z]*.h")

add_library(yaml-cpp STATIC
	${sources}
	${public_headers}
	${private_headers}
	${contrib_sources}
	${contrib_public_headers}
	${contrib_private_headers}
)

if(${CMAKE_VERSION} VERSION_GREATER 2.8.10)
  target_include_directories(yaml-cpp PUBLIC ${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.6.2/src ${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.6.2/include)
else()
  include_directories(${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.6.2/src ${PROJECT_SOURCE_DIR}/contrib/yaml-cpp-0.6.2/include)
endif()

set_target_properties(yaml-cpp PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
