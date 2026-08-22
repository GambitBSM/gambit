# Project development rules

## CMake build-tree policy

- GAMBIT and every CBS configure preset use the canonical shared build tree
  `${sourceDir}/build`.  Do not add preset-specific binary directories such as
  `build/cbs` or `build/cbs-llvm`.
- Do not set preset-specific `CMAKE_RUNTIME_OUTPUT_DIRECTORY`,
  `CMAKE_LIBRARY_OUTPUT_DIRECTORY`, `CMAKE_ARCHIVE_OUTPUT_DIRECTORY`, or
  `GAMBIT_RUN_DIR`.  Presets must preserve GAMBIT's established output-layout
  defaults.
- `cbs` and `cbs-llvm` deliberately share one CMake cache.  Before switching
  between compiler families, configure with the desired preset and `--fresh`:
  `cmake --preset cbs --fresh` or `cmake --preset cbs-llvm --fresh`.
- CBS additions must adapt to GAMBIT's CMake system.  Keep GAMBIT-wide CMake
  behaviour unchanged unless a change is independently correct for GAMBIT;
  avoid CBS-only workarounds in shared GAMBIT targets or build phases.

## macOS deployment target

- `MACOS_DEPLOYMENT_TARGET` is the single macOS minimum-version policy for
  GAMBIT, CBS, and their external packages.  It is resolved in
  `cmake/MacOSX.cmake` and mirrored to CMake's
  `CMAKE_OSX_DEPLOYMENT_TARGET` before `project()` enables compilers.
- Do not add package- or preset-specific `-mmacosx-version-min` flags.  Pass
  the common CMake argument to CMake-based external projects and derive
  Autotools flags from the same resolved target.
