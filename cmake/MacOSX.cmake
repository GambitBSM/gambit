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
#  \author Are Raklev
#          (ahye@fys.uio.no)
#  \date 2023 Feb
#
#************************************************

# Set a consistent MACOSX_RPATH default across all CMake versions.
# When CMake 3 is required, remove this block (see CMP0042).
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 1)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

  message("Compiling on Darwin with SDK ${CMAKE_OSX_SYSROOT} for MacOSX min version ${CMAKE_OSX_DEPLOYMENT_TARGET}")

  if(CMAKE_OSX_DEPLOYMENT_TARGET)
    set(OSX_MIN "-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET}")
  endif()
  
  # Tell the OSX linker not to whinge about missing symbols when just making a library.
  # Use the single-token -Wl form so that backend build scripts that split, sort or
  # deduplicate flags (e.g. Rivet's rivet-build) cannot separate the option from its value.
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,dynamic_lookup")
  # Strip leading whitespace in case this was first definition of CMAKE_SHARED_LINKER_FLAGS
  string(STRIP ${CMAKE_SHARED_LINKER_FLAGS} CMAKE_SHARED_LINKER_FLAGS)
  # Pass on the sysroot and minimum OSX version (for backend builds; this gets added automatically by cmake for others)
  if(CMAKE_OSX_DEPLOYMENT_TARGET)
    set(OSX_MIN "-mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET}")
  endif()
  if ("${CMAKE_CXX_SYSROOT}" STREQUAL "")
    execute_process(COMMAND xcrun --sdk macosx --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
  endif()
  message("Using this MacOS SDK ${CMAKE_OSX_SYSROOT}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isysroot${CMAKE_OSX_SYSROOT} ${OSX_MIN}")
  string(STRIP ${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -isysroot${CMAKE_OSX_SYSROOT} ${OSX_MIN}")
  string(STRIP ${CMAKE_C_FLAGS} CMAKE_C_FLAGS)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -isysroot${CMAKE_OSX_SYSROOT} -L${CMAKE_OSX_SYSROOT}/usr/lib ${OSX_MIN}")
  string(STRIP ${CMAKE_SHARED_LINKER_FLAGS} CMAKE_SHARED_LINKER_FLAGS)
endif()

# Disable chained fixups in the Apple linker.
# The ${NO_FIXUP_CHAINS} -no_fixup_chains linker flag had to be added Feb 2023 due to MacOS linker changes that lead to linking problems
# See discussion in CPython forums and bug report to apple:
# https://github.com/python/cpython/issues/97524
# The flag belongs to Apple's ld rather than to any particular compiler, so test whether the linker
# actually accepts it instead of keying on the compiler ID. It is given in the single-token -Wl form
# rather than as "-Xlinker -no_fixup_chains", because backend build scripts that split, sort or
# deduplicate flags (e.g. Rivet's rivet-build) can separate the two words and break the link.
set(NO_FIXUP_CHAINS "")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  include(CheckCXXSourceCompiles)
  set(CMAKE_REQUIRED_LINK_OPTIONS "-Wl,-no_fixup_chains")
  set(CMAKE_REQUIRED_QUIET TRUE)
  check_cxx_source_compiles("int main() { return 0; }" LINKER_SUPPORTS_NO_FIXUP_CHAINS)
  unset(CMAKE_REQUIRED_LINK_OPTIONS)
  unset(CMAKE_REQUIRED_QUIET)
  if (LINKER_SUPPORTS_NO_FIXUP_CHAINS)
    set(NO_FIXUP_CHAINS "-Wl,-no_fixup_chains")
    message("   Linker supports -no_fixup_chains; it will be used when building backends.")
  else()
    message("   Linker does not support -no_fixup_chains; it will not be used when building backends.")
  endif()
endif()

