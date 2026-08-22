# \author Pengxuan Zhu
#         (pengxuan.zhu@adelaide.edu.au)
# \date 2026 Aug
#
# Native upstream-LLVM toolchain for the public cbs-llvm preset.
# CBS and GAMBIT both configure in build/; switching compiler families
# in that tree requires cmake --preset cbs-llvm --fresh.

include("${CMAKE_CURRENT_LIST_DIR}/../presets/CBSCompilerDiscovery.cmake")

cbs_find_llvm_toolchain(_cbs_llvm_found _cbs_llvm_c _cbs_llvm_cxx _cbs_llvm_version _cbs_llvm_origin _cbs_llvm_reason)
if(NOT _cbs_llvm_found)
  message(FATAL_ERROR
    "The cbs-llvm preset requires upstream LLVM Clang. ${_cbs_llvm_reason}")
endif()

foreach(_cbs_language C CXX)
  if(_cbs_language STREQUAL "C")
    set(_cbs_compiler_variable CMAKE_C_COMPILER)
    set(_cbs_selected_compiler "${_cbs_llvm_c}")
  else()
    set(_cbs_compiler_variable CMAKE_CXX_COMPILER)
    set(_cbs_selected_compiler "${_cbs_llvm_cxx}")
  endif()

  if(DEFINED ${_cbs_compiler_variable} AND NOT "${${_cbs_compiler_variable}}" STREQUAL "")
    get_filename_component(_cbs_existing_realpath "${${_cbs_compiler_variable}}" REALPATH)
    get_filename_component(_cbs_selected_realpath "${_cbs_selected_compiler}" REALPATH)
    if(NOT "${_cbs_existing_realpath}" STREQUAL "${_cbs_selected_realpath}")
      message(FATAL_ERROR
        "The cbs-llvm preset selected ${_cbs_selected_compiler}, but ${_cbs_compiler_variable} is already ${${_cbs_compiler_variable}}.\n"
        "GAMBIT uses a single build/ directory, so switching compiler requires a clean cache.\n"
        "Rerun 'cmake --preset cbs-llvm --fresh' (and unset CC/CXX if they are set in the environment).")
    endif()
  endif()

  set(${_cbs_compiler_variable} "${_cbs_selected_compiler}" CACHE FILEPATH
      "Compiler selected by the cbs-llvm preset" FORCE)
endforeach()

get_filename_component(_cbs_llvm_root "${_cbs_llvm_origin}" DIRECTORY)
set(CBS_RESOLVED_LLVM_ROOT "${_cbs_llvm_root}" CACHE PATH
    "LLVM installation selected by the cbs-llvm preset" FORCE)
set(CBS_RESOLVED_LLVM_BIN_DIR "${_cbs_llvm_origin}" CACHE PATH
    "LLVM compiler bin directory selected by the cbs-llvm preset" FORCE)
set(CBS_RESOLVED_LLVM_VERSION "${_cbs_llvm_version}" CACHE STRING
    "LLVM version selected by the cbs-llvm preset" FORCE)
set(CBS_RESOLVED_TOOLCHAIN "upstream-llvm" CACHE STRING
    "Compiler strategy selected by the CBS preset" FORCE)

# CMake may read a toolchain file more than once during one configure pass.
get_property(_cbs_toolchain_announced GLOBAL PROPERTY CBS_LLVM_TOOLCHAIN_ANNOUNCED)
if(NOT _cbs_toolchain_announced)
  message(STATUS "CBS LLVM toolchain: Clang ${_cbs_llvm_version} from ${_cbs_llvm_root}")
  set_property(GLOBAL PROPERTY CBS_LLVM_TOOLCHAIN_ANNOUNCED TRUE)
endif()
