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

  # cbs and cbs-llvm deliberately share build/.  A normal cbs configure
  # cannot replace a cached cbs-llvm toolchain, so fail rather than report a
  # misleading system-toolchain configuration.
  if("${CBS_BUILD_PRESET}" STREQUAL "cbs"
     AND "${CBS_RESOLVED_TOOLCHAIN}" STREQUAL "upstream-llvm")
    message(FATAL_ERROR
      "The cbs preset found the cbs-llvm toolchain in the shared build/ cache.\n"
      "Switching compiler families requires a clean cache; rerun "
      "'cmake --preset cbs --fresh'.")
  endif()

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

  set(_cbs_sqlite_prerequisites_reason "")
  if(CBS_WITH_RIVET_CONTUR AND NOT SQLite3_FOUND)
    list(APPEND _cbs_sqlite_prerequisites_reason
         "SQLite3 development libraries were not found")
  endif()
  if(CBS_WITH_RIVET_CONTUR AND NOT SQLITE3_CLI_FOUND)
    list(APPEND _cbs_sqlite_prerequisites_reason
         "the sqlite3 command-line client was not found")
  endif()
  if(_cbs_sqlite_prerequisites_reason)
    string(REPLACE ";" "; " _cbs_sqlite_prerequisites_text
           "${_cbs_sqlite_prerequisites_reason}")
    set(CBS_RIVET_CONTUR_PREREQUISITES_FOUND FALSE)
    if(CBS_RIVET_CONTUR_PREREQUISITES_REASON)
      string(APPEND CBS_RIVET_CONTUR_PREREQUISITES_REASON
             "; ${_cbs_sqlite_prerequisites_text}")
    else()
      set(CBS_RIVET_CONTUR_PREREQUISITES_REASON
          "${_cbs_sqlite_prerequisites_text}")
    endif()
    message(STATUS
      "CBS Rivet/Contur: unavailable (${_cbs_sqlite_prerequisites_text})")
  endif()
  unset(_cbs_sqlite_prerequisites_reason)
  unset(_cbs_sqlite_prerequisites_text)
endmacro()

macro(cbs_preset_attach_optional_backends)
  set(CBS_RIVET_CONTUR_ENABLED FALSE)
  if(TARGET CBS AND CBS_WITH_RIVET_CONTUR)
    if(CBS_RIVET_CONTUR_PREREQUISITES_FOUND AND TARGET rivet AND TARGET contur)
      # BOSS writes Rivet's frontend headers.  Make the normal GAMBIT header
      # harvest wait for that write, otherwise a parallel first CBS build can
      # compile against the old headers and need a full second compilation.
      if(TARGET cbs_rivet_boss_headers AND TARGET backend_harvest)
        add_dependencies(backend_harvest cbs_rivet_boss_headers)
      endif()
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
