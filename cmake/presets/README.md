# Preset discovery

Run the read-only bootstrap from the repository root:

```sh
./cmake/bootstrap                       # all registered systems
./cmake/bootstrap --system gambit       # only GAMBIT
./cmake/bootstrap --system cbs          # all three CBS presets
./cmake/bootstrap --preset gambit-llvm   # one exact preset
./cmake/bootstrap --list                # registry only; no environment probes
./cmake/bootstrap --system cbs --list
./cmake/bootstrap --help
./cmake/bootstrap --system cbs --verbose # include full paths
```

`--system` and `--preset` can be repeated and accept `--system=cbs` /
`--preset=cbs-llvm`. Repeated values are alternatives within that filter;
supplying both kinds takes their intersection. Unknown selectors and empty
intersections fail before environment discovery. A valid discovery report exits
successfully even if a selected preset is unavailable; it reports each missing
prerequisite and suggests commands only for available presets. Presets for a
different host are marked `OTHER HOST` without running dependency probes.

The report groups preset status, the shared environment, system-specific
dependencies/optional features, and build commands. Shared dependencies appear
once per report. The default view shows compiler/package identities and keeps
full paths under `--verbose`. Colors are automatic on a terminal; redirected
stdout stays plain text. `NO_COLOR` and `TERM=dumb` disable automatic colors.
reports are written to stdout; argument/registry errors remain on stderr.

Each registered system provides three public configure/build presets:

| Compiler profile | GAMBIT | CBS | Host |
|---|---|---|---|
| Upstream LLVM | `gambit-llvm` | `cbs-llvm` | macOS or Linux |
| Native AppleClang | `gambit` | `cbs` | macOS |
| GNU C/C++/Fortran | `gambit-gnu` | `cbs-gnu` | Linux |

The existing unsuffixed names remain the native macOS entries. AppleClang is
LLVM-based internally; this profile means Apple's toolchain, separate from the
upstream LLVM installation selected by `*-llvm`. LLVM profiles use upstream
Clang for C/C++ and a discovered Fortran compiler (normally GNU Fortran).
The macOS profile resolves the active Xcode / Command Line Tools compiler via
`xcrun`. The GNU profile selects `gcc`, `g++`, and GNU Fortran. Explicit compiler
selections must match the profile. Configure and build presets have matching
host conditions; native CMake lists only entries enabled for the current host.
Bootstrap `--list` includes all registered entries with host mismatch reasons.

The entry point can also be invoked by absolute path from another directory.
Discovery uses the current `PATH`, `CC`, `CXX`, `FC`, and supported package hints.
It does not read `build/CMakeCache.txt`, run `project()`, configure the repository,
compile, download, install, or change the build tree. Native CMake remains
responsible for actual compiler selection, dependency versions, compile/link
checks, optional feature resolution, and backend construction. An `AVAILABLE`
report means the probed prerequisites were found; it does not certify a complete
build. Local user presets and arbitrary configure-time overrides are outside
this registry's scope.

GAMBIT and CBS both require C/C++/Fortran compilers, Python 3 with PyYAML, OpenMP,
Boost, Eigen, and GSL. The GAMBIT provider treats HDF5 as optional, matching native
GAMBIT configuration; it does not require Python development libraries. CBS
also requires HDF5 and Python development headers/shared libraries, matching
`CBSValidation.cmake`. CBS reports optional ROOT and Rivet/Contur prerequisites.
Selecting only GAMBIT does not run those CBS-specific probes.

Choose a reported preset and use native CMake commands:

```sh
cmake --preset gambit-llvm --fresh
cmake --build --preset gambit-llvm --parallel

# Or choose CBS:
cmake --preset cbs-llvm --fresh
cmake --build --preset cbs-llvm --parallel
```

All presets preserve the canonical `${sourceDir}/build` and GAMBIT output layout.
Use `--fresh` when switching profiles or compiler families in that shared tree.
Bootstrap does not perform the switch itself.

## Local HPC presets

Cluster software stacks differ, so keep site-specific settings in CMake's
standard `CMakeUserPresets.json` at the repository root. It is ignored by Git
and automatically loaded by CMake alongside `CMakePresets.json`. Start with the
tracked [example](../../CMakeUserPresets.json.example):

```sh
cp -n CMakeUserPresets.json.example CMakeUserPresets.json
# Load the site's compiler, Python, MPI (if needed), and dependency modules.
# Edit CMakeUserPresets.json to match those modules and the site paths.
cmake --list-presets
cmake --preset gambit-hpc --fresh
cmake --build --preset gambit-hpc --parallel 8
```

If `CMakeUserPresets.json` already exists, add the example's configure/build
pair to that file instead of replacing existing site settings. Presets require
CMake 3.24 or newer; load a newer CMake module when the cluster default is older.

The example inherits `gambit-base`, so it builds full GAMBIT in the canonical
`build/` tree with the usual output locations. Its compiler names resolve from
the `PATH` established by your module environment; replace them with absolute
paths if the site requires a specific installation. Set `CMAKE_PREFIX_PATH` to
one or more dependency installation prefixes separated by semicolons if CMake
cannot find packages from loaded modules. Other site-specific cache variables
such as `GSL_ROOT_DIR`, `Python3_EXECUTABLE`, or `HDF5_ROOT` can be added there.
Set `WITH_MPI` to `ON` only when using GAMBIT's MPI parallel sampling and after
loading a compatible MPI module. Keep the same modules loaded for configure,
build, and execution.

For another local profile, duplicate the configure/build pair under a new name
in `CMakeUserPresets.json`, then edit its settings. A CBS profile can inherit
`cbs-base`, set `CBS_BUILD_PRESET` to its local name, and build target `CBS`.
Use `--fresh` whenever changing profiles or compiler families because all
presets share `build/`. `./cmake/bootstrap` reports only the project's registered
presets; use `cmake --list-presets` to see local user presets. Native CMake
configure performs the authoritative compiler and dependency checks.

## Registering another system

The public configure presets in `CMakePresets.json` are the registration source.
Add metadata directly to each public preset that bootstrap should inspect:

```json
"vendor": {
  "gambit/bootstrap/1": {
    "system": "cbs",
    "toolchain": "llvm"
  }
}
```

`system` is a lowercase identifier; `toolchain` is `llvm`, `macos`, or `gnu`.
Register the three compiler profiles for every new system. Reuse
`llvm-native.cmake`, `macos-native.cmake`, and `gnu-native.cmake` under
`cmake/toolchains/`, and apply matching host conditions to both configure and
build presets. Keep profile cache values in one hidden `<system>-base` preset.
Native compiler discovery and setup are shared by all systems through
`NativeCompilerDiscovery.cmake` and `NativePresetToolchain.cmake`. Set each public
preset's `GAMBIT_PRESET_TOOLCHAIN` cache value to the same strategy as its vendor
metadata. This contract rejects an old toolchain loaded from the shared cache
when switching compiler profiles without `--fresh`.
Hidden presets and public presets without this metadata are not listed or probed.
The registration metadata must be explicit on public presets, even when their
build configuration inherits from a hidden base.

For a new system identifier, add `<UPPERCASE_SYSTEM>Availability.cmake` next to
`detect-presets.cmake`. Define
`preset_probe_<system>(name strategy display_name output_available)` and call
`preset_probe_record_result(name reasons c cxx fortran llvm_root output_available)`
to retain compiler facts and missing-prerequisite reasons for the report. Set
the output boolean in the parent scope. An optional `preset_probe_prepare_<system>`
macro runs once after common discovery to collect facts shared by that system's
selected presets. Providers must remain read-only and must not execute probes
while being included. Put system-specific policy there; reuse common environment
helpers from `PresetEnvironmentDiscovery.cmake` and the configure-time discovery
modules. An optional `preset_probe_report_<system>` function can append one
system-specific environment section using `BootstrapReport.cmake` helpers.
The CLI and dispatcher need no change when adding a provider that uses
the existing toolchain strategies.
