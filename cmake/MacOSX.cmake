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
#  \author Pengxuan Zhu
#          (pengxuan.zhu@adelaide.edu.au)
#  \date 2026 Aug
#
#************************************************

# Set a consistent MACOSX_RPATH default across all CMake versions.
# When CMake 3 is required, remove this block (see CMP0042).
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 1)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # Tell the OSX linker not to whinge about missing symbols when just making a library.
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
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

# Detect Homebrew libomp for macOS LLVM builds.
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  find_program(_GAMBIT_BREW_EXECUTABLE NAMES brew)
  if(_GAMBIT_BREW_EXECUTABLE)
    execute_process(
      COMMAND "${_GAMBIT_BREW_EXECUTABLE}" --prefix llvm
      RESULT_VARIABLE _GAMBIT_BREW_LLVM_RESULT
      OUTPUT_VARIABLE _GAMBIT_BREW_LLVM_PREFIX
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
    )
    execute_process(
      COMMAND "${_GAMBIT_BREW_EXECUTABLE}" --prefix libomp
      RESULT_VARIABLE _GAMBIT_BREW_LIBOMP_RESULT
      OUTPUT_VARIABLE BREW_LIBOMP_PREFIX
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
    )
    if(_GAMBIT_BREW_LLVM_RESULT EQUAL 0 AND _GAMBIT_BREW_LIBOMP_RESULT EQUAL 0)
      get_filename_component(_GAMBIT_CXX_COMPILER_REALPATH "${CMAKE_CXX_COMPILER}" REALPATH)
      get_filename_component(_GAMBIT_BREW_LLVM_CXX_REALPATH "${_GAMBIT_BREW_LLVM_PREFIX}/bin/clang++" REALPATH)
      if("${_GAMBIT_CXX_COMPILER_REALPATH}" STREQUAL "${_GAMBIT_BREW_LLVM_CXX_REALPATH}"
         AND EXISTS "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib")
        set(OpenMP_C_FLAGS "-Xclang -fopenmp -I${BREW_LIBOMP_PREFIX}/include" CACHE STRING "C compiler flags for OpenMP parallelization" FORCE)
        set(OpenMP_CXX_FLAGS "-Xclang -fopenmp -I${BREW_LIBOMP_PREFIX}/include" CACHE STRING "CXX compiler flags for OpenMP parallelization" FORCE)
        set(OpenMP_C_LIB_NAMES "omp" CACHE STRING "C compiler libraries for OpenMP parallelization" FORCE)
        set(OpenMP_CXX_LIB_NAMES "omp" CACHE STRING "CXX compiler libraries for OpenMP parallelization" FORCE)
        set(OpenMP_omp_LIBRARY "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib" CACHE FILEPATH "Path to the omp library for OpenMP" FORCE)
        set(GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP_LDFLAGS "-L${BREW_LIBOMP_PREFIX}/lib")
        set(GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP TRUE)
        message(STATUS "Using Homebrew libomp for Homebrew LLVM from ${BREW_LIBOMP_PREFIX}")
      endif()
    endif()
  endif()
endif()

# Settings specific to using the clang compiler on MacOS
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  # The ${NO_FIXUP_CHAINS} -Xlinker -no_fixup_chains had to be added Feb 2023 due to MacOS clang changes that leads to linking problems
  # See discussion in CPython forums and bug report to apple:
  # https://github.com/python/cpython/issues/97524
  set(NO_FIXUP_CHAINS "-Xlinker -no_fixup_chains")
endif()
