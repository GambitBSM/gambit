# GAMBIT: Global and Modular BSM Inference Tool
#************************************************
# \file
#
#  Cmake configuration script to do Mac OSX
#  things for GAMBIT.
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
#  \date 2022 Jan
#
#************************************************

# Set a consistent MACOSX_RPATH default across all CMake versions.
# When CMake 3 is required, remove this block (see CMP0042).
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 1)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # Tell the OSX linker not to whinge about missing symbols when just making a library.
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,dynamic_lookup")
  # Pass on the sysroot and minimum OSX version (for backend builds; this gets added automatically by cmake for others)
  if(CMAKE_OSX_DEPLOYMENT_TARGET)
    set(OSX_MIN "-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET}")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -isysroot${CMAKE_OSX_SYSROOT} ${OSX_MIN}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -isysroot${CMAKE_OSX_SYSROOT} ${OSX_MIN}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -isysroot${CMAKE_OSX_SYSROOT} -L${CMAKE_OSX_SYSROOT}/usr/lib ${OSX_MIN}")
endif()
