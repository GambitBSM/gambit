# Isolated CBS preset orchestration.
#
# Ordinary `cmake ..` never includes this file.  Public presets set
# CBS_BUILD_PRESET in CMakePresets.json; CMakeLists.txt then loads this
# module and calls the macros below at the few points where GAMBIT's
# configure sequence needs them (Python before FindPython3, ROOT before
# optional.cmake, summary after all targets exist).
#
# Compiler/Python/ROOT discovery, validation, and the final summary live
# under cmake/presets/.  Native GAMBIT/ColliderBit build facts (FastJet,
# Rivet, OpenMP, macOS linker flags) belong in the main cmake files, not
# here.

include_guard(GLOBAL)

# Macros expand CMAKE_CURRENT_LIST_DIR at the call site (CMakeLists.txt).
# Capture this file's directory when it is included.
set(CBS_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}")

macro(cbs_preset_begin)
  set(CBS_PRESET_BUILD TRUE)
  option(CBS_AUTO_DETECT_PYTHON
         "CBS: pin python3 on PATH before FindPython3" ON)
  option(CBS_AUTO_DETECT_ROOT
         "CBS: enable ROOT when a C++17 root-config is found" ON)
  option(CBS_WITH_RIVET_CONTUR
         "CBS: enable Rivet/Contur when their prerequisites exist" ON)
  option(CBS_USE_LLD
         "CBS: use lld when linking the standalone executable" OFF)

  if(CBS_AUTO_DETECT_PYTHON)
    include("${CBS_CMAKE_DIR}/presets/CBSPythonDiscovery.cmake")
    cbs_configure_python_for_cbs_preset()
  endif()
endmacro()

macro(cbs_preset_after_python)
  include("${CBS_CMAKE_DIR}/presets/CBSPythonDiscovery.cmake")
  cbs_validate_python_for_cbs_preset()
  if(NOT DITCH_PYBIND AND NOT Python3_Development_FOUND)
    message(FATAL_ERROR
      "CBS requires Python development headers and libpython.\n"
      "Install python3-dev / python3-devel for ${Python3_EXECUTABLE}, "
      "or set -DPython3_EXECUTABLE to an interpreter that has them.")
  endif()
endmacro()

macro(cbs_preset_before_optional)
  if(CBS_AUTO_DETECT_ROOT)
    include("${CBS_CMAKE_DIR}/presets/CBSRootDiscovery.cmake")
    cbs_configure_root_for_cbs_preset()
  endif()
endmacro()

macro(cbs_preset_after_optional)
  if(NOT EXCLUDE_ROOT)
    set(_cbs_root_std "${ROOT_STD}")
    if(_cbs_root_std STREQUAL "1z")
      set(_cbs_root_std "17")
    elseif(_cbs_root_std STREQUAL "1y")
      set(_cbs_root_std "14")
    elseif(_cbs_root_std STREQUAL "0x")
      set(_cbs_root_std "11")
    endif()
    if(_cbs_root_std STREQUAL "" OR _cbs_root_std VERSION_LESS 17)
      message(FATAL_ERROR
        "ROOT at $ENV{ROOTSYS} is C++${ROOT_STD}, so CBS cannot keep C++17.\n"
        "Reconfigure with -DCBS_AUTO_DETECT_ROOT=OFF or -DWITH_ROOT=OFF, "
        "or use a C++17 ROOT.")
    endif()
  endif()

  if(CBS_WITH_RIVET_CONTUR AND NOT SQLite3_FOUND)
    set(CBS_RIVET_CONTUR_PREREQUISITES_FOUND FALSE)
    if(CBS_RIVET_CONTUR_PREREQUISITES_REASON)
      string(APPEND CBS_RIVET_CONTUR_PREREQUISITES_REASON
             "; SQLite3 development libraries were not found")
    else()
      set(CBS_RIVET_CONTUR_PREREQUISITES_REASON
          "SQLite3 development libraries were not found")
    endif()
    message(STATUS
      "CBS Rivet/Contur: unavailable (SQLite3 development libraries were not found)")
  endif()
endmacro()

macro(cbs_preset_attach_optional_backends)
  set(CBS_RIVET_CONTUR_ENABLED FALSE)
  if(TARGET CBS AND CBS_WITH_RIVET_CONTUR)
    if(CBS_RIVET_CONTUR_PREREQUISITES_FOUND AND TARGET rivet AND TARGET contur)
      add_dependencies(CBS rivet contur)
      set(CBS_RIVET_CONTUR_ENABLED TRUE)
    elseif(NOT CBS_RIVET_CONTUR_PREREQUISITES_REASON)
      set(CBS_RIVET_CONTUR_PREREQUISITES_REASON
          "the Rivet/Contur backend targets could not be configured")
    endif()
  endif()
endmacro()

macro(cbs_preset_finish)
  if(NOT TARGET CBS)
    message(FATAL_ERROR
      "CBS preset could not create the CBS target.\n"
      "Ensure ColliderBit, HepMC, and pybind11 are available, then rerun "
      "'cmake --preset ${CBS_BUILD_PRESET} --fresh'.")
  endif()
  cbs_preset_attach_optional_backends()
  include("${CBS_CMAKE_DIR}/presets/CBSValidation.cmake")
  cbs_validate_environment()
  include("${CBS_CMAKE_DIR}/presets/CBSCompilerSummary.cmake")
  cbs_print_compiler_summary()
  cbs_require_validated_environment()
endmacro()
