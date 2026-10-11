# One OpenMP discovery path for native GAMBIT and CBS. Keep global compilation
# flags (used by module libraries) and link explicit libraries in executables.
include_guard(GLOBAL)
include("${CMAKE_CURRENT_LIST_DIR}/ProcessProbe.cmake")

# Mark only values we supplied. A user changing an automatically seeded cache
# value takes ownership; remove unchanged automatic hints before rediscovery.
macro(_gambit_clear_openmp_hints)
  foreach(_key OpenMP_C_FLAGS OpenMP_CXX_FLAGS OpenMP_C_LIB_NAMES
      OpenMP_CXX_LIB_NAMES OpenMP_omp_LIBRARY)
    if(DEFINED GAMBIT_OPENMP_AUTO_${_key} AND
       "${${_key}}" STREQUAL "${GAMBIT_OPENMP_AUTO_${_key}}")
      unset(${_key} CACHE)
      unset(${_key})
    endif()
    unset(GAMBIT_OPENMP_AUTO_${_key} CACHE)
  endforeach()
endmacro()

macro(_gambit_seed_openmp_hint key type value)
  if(NOT DEFINED ${key})
    set(${key} "${value}" CACHE ${type} "OpenMP discovery hint")
    set(GAMBIT_OPENMP_AUTO_${key} "${value}" CACHE INTERNAL "GAMBIT automatic OpenMP hint" FORCE)
  endif()
endmacro()

macro(gambit_configure_openmp)
  set(FOUND_BREW_OPENMP FALSE)
  set(GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP FALSE)
  set(GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP_LDFLAGS "")
  _gambit_clear_openmp_hints()
  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND
     CMAKE_C_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    find_program(_gambit_openmp_brew NAMES brew)
    if(_gambit_openmp_brew)
      gambit_process_probe(COMMAND "${_gambit_openmp_brew}" --prefix libomp
        RESULT_VARIABLE _brew_result OUTPUT_VARIABLE BREW_LIBOMP_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET TIMEOUT 10)
      if(_brew_result EQUAL 0 AND EXISTS "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib")
        # Migrate the exact legacy Homebrew hint bundle. Other manual hints
        # remain authoritative, including a different runtime or include path.
        if("${OpenMP_C_FLAGS}" STREQUAL "-fopenmp=libomp -I${BREW_LIBOMP_PREFIX}/include" AND
           "${OpenMP_CXX_FLAGS}" STREQUAL "-fopenmp=libomp -I${BREW_LIBOMP_PREFIX}/include" AND
           "${OpenMP_C_LIB_NAMES}" STREQUAL "omp" AND "${OpenMP_CXX_LIB_NAMES}" STREQUAL "omp" AND
           "${OpenMP_omp_LIBRARY}" STREQUAL "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib")
          foreach(_key OpenMP_C_FLAGS OpenMP_CXX_FLAGS OpenMP_C_LIB_NAMES
              OpenMP_CXX_LIB_NAMES OpenMP_omp_LIBRARY)
            unset(${_key} CACHE)
            unset(${_key})
          endforeach()
          message(STATUS "OpenMP: migrating legacy Homebrew hints")
        endif()
        set(_include "${BREW_LIBOMP_PREFIX}/include")
        if(_include MATCHES "[ \t]")
          set(_include "\"${_include}\"")
        endif()
        # Enable code generation without adding a compiler-selected runtime.
        # C/C++ link the explicit FindOpenMP library list below.
        _gambit_seed_openmp_hint(OpenMP_C_FLAGS STRING "-Xclang -fopenmp -I${_include}")
        _gambit_seed_openmp_hint(OpenMP_CXX_FLAGS STRING "-Xclang -fopenmp -I${_include}")
        _gambit_seed_openmp_hint(OpenMP_C_LIB_NAMES STRING omp)
        _gambit_seed_openmp_hint(OpenMP_CXX_LIB_NAMES STRING omp)
        _gambit_seed_openmp_hint(OpenMP_omp_LIBRARY FILEPATH "${BREW_LIBOMP_PREFIX}/lib/libomp.dylib")
      endif()
    endif()
  endif()

  find_package(OpenMP QUIET COMPONENTS C CXX Fortran)
  if(NOT OpenMP_C_FOUND OR NOT OpenMP_CXX_FOUND OR NOT OpenMP_Fortran_FOUND)
    message(FATAL_ERROR "OpenMP is required for C, C++ and Fortran. Check the selected compilers and OpenMP development libraries. On macOS install libomp, or provide matching OpenMP_<lang>_FLAGS / LIB_NAMES / <library>_LIBRARY hints.")
  endif()
  # OpenMP flags are global because shared/static module libraries need them.
  # Executables use the library list, avoiding a second compile-option copy
  # from OpenMP::OpenMP_CXX's interface usage requirements.
  foreach(_language C CXX Fortran)
    set(_flags "${OpenMP_${_language}_FLAGS}")
    foreach(_include IN LISTS OpenMP_${_language}_INCLUDE_DIRS)
      if(_include MATCHES "[ \t]")
        set(_include "\"${_include}\"")
      endif()
      gambit_append_flags_once(_flags "-I${_include}")
    endforeach()
    gambit_append_flags_once(CMAKE_${_language}_FLAGS "${_flags}")
  endforeach()
  set(OPENMP_FOUND TRUE)
  set(GAMBIT_OPENMP_FOUND TRUE)

  if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(EXISTS "${OpenMP_omp_LIBRARY}")
      set(FOUND_BREW_OPENMP TRUE)
    endif()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND _gambit_openmp_brew)
      gambit_process_probe(COMMAND "${_gambit_openmp_brew}" --prefix llvm
        RESULT_VARIABLE _llvm_result OUTPUT_VARIABLE _llvm_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET TIMEOUT 10)
      get_filename_component(_compiler "${CMAKE_CXX_COMPILER}" REALPATH)
      get_filename_component(_brew_compiler "${_llvm_prefix}/bin/clang++" REALPATH)
      if(_llvm_result EQUAL 0 AND _compiler STREQUAL _brew_compiler AND EXISTS "${OpenMP_omp_LIBRARY}")
        set(GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP TRUE)
        get_filename_component(_runtime_dir "${OpenMP_omp_LIBRARY}" DIRECTORY)
        if(_runtime_dir MATCHES "[ \t]")
          set(_runtime_dir "\"${_runtime_dir}\"")
        endif()
        set(GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP_LDFLAGS "-L${_runtime_dir} -Wl,-rpath,${_runtime_dir}")
      endif()
    endif()
  endif()
  message(STATUS "OpenMP found successfully (C, C++, Fortran)")
endmacro()
