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

## Retaining optional contributed packages

Disabling RestFrames, or selecting Bits without ColliderBit (which disables
HepMC and YODA), preserves their source/install trees, external build directories,
and completion stamps. Re-enabling the same package with the same toolchain and
inputs can reuse that work. A compiler, flags, dependency, or patch change may
still require reconfiguration or rebuilding.

The package's build target, include paths, and link settings are excluded while
disabled. Its explicit `clean-<package>` and `nuke-<package>` targets remain
available, including `restframes`, `hepmc`, and `yoda`. `nuke-contrib` and `nuke-all`
include these retained packages as well. For example, when you intend to remove
the RestFrames source/install tree and external build directory:

```sh
cmake --build build --target nuke-restframes
```

This also removes its standard download/configure/build/install stamps; the
next enabled build must prepare the package again. Turning a feature off alone
does not request this removal. To check preservation without compiling:

```sh
python3 cmake/tests/contrib_retention.py
```

See the [development ledger](../../doc/CMAKE_PRESET_DEVELOPMENT_LEDGER.md#build-04-实施与验证)
for maintainer verification with real installed libraries and timestamps.

## FastJet installation reuse

FastJet and FastJet Contrib are reused when the required libraries, headers,
`fastjet-config`, native Nsubjettiness sources and recorded build identity all
match. Library lookup rechecks the owned installation instead of trusting cached
paths. The identity includes compiler paths/versions/real paths/file timestamps,
C++ standard, target architecture, SDK/deployment settings, package checksums,
configure options and the package's effective compiler flags. Contrib also records
the FastJet identity it was built against.

Older installations have no identity record and require one rebuild. Configure
prints the reason and invalidates only the rejected package's build stamps; the
source/install trees are replaced during the requested build. A verified archive
is extracted in a temporary directory before replacing old sources, so old
Autotools objects cannot survive a compiler/flags change. Missing or invalid
cached archives make the download step eligible to run again.

After installation, required files are checked again before writing
`contrib/fastjet-3.5.1/local/.gambit-fastjet-build-identity` and
`.gambit-fjcontrib-build-identity`. Failed/incomplete installations do not create
new success records. Rebuilding FastJet also rebuilds Contrib; a Contrib-only
problem keeps a matching FastJet installation. Explicit clean/nuke targets remain
available when an installation is reused.

Use the existing build tree for the first rebuild, then repeat configure/build
with the same settings to check reuse:

```sh
cmake --preset cbs-llvm
cmake --build build --target fjcontrib -j8
cmake --build build --target CBS -j8
cmake --preset cbs-llvm
cmake --build build --target CBS -j8
```

The second configure should report `build identity matches` for both packages;
subsequent builds should skip their preparation/configure/compile/install steps.
The `fjcontrib` target builds FastJet first through its dependency. No build-tree
reset is needed. Keep local modifications to downloaded sources elsewhere before
requesting a rebuild, since pristine preparation replaces those package trees.

Script-only regression checks:

```sh
python3 cmake/tests/contrib_build_identity.py
```

See the [development ledger](../../doc/CMAKE_PRESET_DEVELOPMENT_LEDGER.md#build-05-实施与验证)
for maintainer checks and the remaining platform validation.

## Compiler caching

On a new preset configuration, `GAMBIT_COMPILER_CACHE` defaults to `AUTO`:
use a working `ccache` from `PATH` for native C/C++ targets when available,
otherwise continue without automatic caching. A new ordinary `cmake` configuration
defaults to `OFF`. The policy is cached; an existing selection is preserved.
Choose it explicitly when needed:

```sh
cmake --preset cbs-llvm -DGAMBIT_COMPILER_CACHE=AUTO
cmake --preset cbs-llvm -DGAMBIT_COMPILER_CACHE=CCACHE  # require working ccache
cmake --preset cbs-llvm -DGAMBIT_COMPILER_CACHE=OFF
```

These changes do not switch compilers and need neither `--fresh` nor a build-tree
cleanup. `AUTO` falls back if ccache is missing or its `--version` check fails;
`CCACHE` reports an error instead. Unknown policy values also produce an error.
Automatic launchers use CMake's Makefiles/Ninja launcher mechanism; this does not
add Ninja support to GAMBIT's external-project build system. With other generators,
`AUTO` skips automatic caching and `CCACHE` reports the unsupported generator.

An existing `CMAKE_C_COMPILER_LAUNCHER` or `CMAKE_CXX_COMPILER_LAUNCHER` takes
precedence for that language, including an explicitly empty value. This covers
command-line/cache, toolchain, and standard launcher environment selections.
For example, to choose a wrapper or disable only C++ caching:

```sh
cmake --preset cbs-llvm -DCMAKE_CXX_COMPILER_LAUNCHER=/path/to/sccache
cmake --preset cbs-llvm -DCMAKE_CXX_COMPILER_LAUNCHER:STRING=
```

`OFF` disables automatic injection; it preserves explicit launchers. Remove an
explicit setting with `-U CMAKE_CXX_COMPILER_LAUNCHER` (and the corresponding
environment variable if set) to return that language to automatic selection.
Automatically discovered launcher paths are not cached, so `OFF` stops them on
the next configure, and `AUTO` rechecks availability. The build summary shows
the policy, detected ccache version, and both effective launcher values.

Caching applies to native C/C++ targets, including contributed libraries added
with `add_subdirectory` and standalone program objects. It does not add a
Fortran launcher or change separate ExternalProject Make/Autotools compiler
commands. It also does not change ccache's directory, size, or global settings.
Existing object files do not populate the cache until compiled through ccache;
an unchanged build has no compiler work to cache. Verify hits by recompiling
unchanged content twice, for example:

```sh
cmake --preset cbs-llvm -DGAMBIT_COMPILER_CACHE=CCACHE
ccache -s
touch ColliderBit/examples/solo_cli.cpp
cmake --build build --target CBS_objects -j8 --verbose
ccache -s
touch ColliderBit/examples/solo_cli.cpp
cmake --build build --target CBS_objects -j8 --verbose
ccache -s
cmake --build build --target CBS -j8
```

The compile command should prefix the compiler with ccache. The second content-
identical compilation should increase the hit count; compare the statistics
before and after each build. Keep the same compiler, flags, headers, and cache
environment. No cache clear, global statistics reset, or full rebuild is needed.
Policy regression tests run without project configuration or compilers:

```sh
python3 cmake/tests/compiler_cache.py
```

See CMake's [launcher variable](https://cmake.org/cmake/help/v3.16/variable/CMAKE_LANG_COMPILER_LAUNCHER.html)
and the [ccache manual](https://ccache.dev/manual/latest.html#_cache_statistics)
for target initialisation and statistics.

## C++ language standard

GAMBIT and CBS require C++17 or newer and accept `CMAKE_CXX_STANDARD=17`,
`20`, or `23`. Without an explicit selection, CMake chooses the newest of
23, 20, and 17 supported by its compiler metadata. C++23 needs CMake 3.20 or
newer; older supported CMake versions automatically choose at most C++20.
These are language modes, not a claim that every compiler implements every
library feature of the selected standard.

When ROOT is enabled, its build standard must match exactly. Automatic mode
adopts ROOT's standard. An explicit conflicting standard produces an error
with the matching setting; it is never silently downgraded. For example:

```sh
cmake --preset cbs-llvm -DCMAKE_CXX_STANDARD=17
cmake --preset cbs-llvm -DCMAKE_CXX_STANDARD=20 -DWITH_ROOT=OFF
```

Use `-U CMAKE_CXX_STANDARD` to return to automatic selection. Also remove any
legacy `-std=` options in `CMAKE_CXX_FLAGS` or configuration-specific flags:
these count as explicit selections, and conflicting selections are rejected.
Standard aliases in legacy flags (`1z`, `2a`, `2b`) are normalized. The main
project uses CMake's required standard property with C++ extensions disabled.
The configure summary shows the request, effective standard, and reason.
The usual shared-build-tree rules still apply when switching compiler families.

External Make/Autotools projects receive one explicit standard flag derived
from the resolved choice, including MPI and unoptimized backend variants.
Package-specific compatibility exceptions remain: macOS Pythia is capped at
C++17, GM2Calc 1.2/1.3 uses C++14, Rivet uses C++17, and HepMC uses ROOT's
standard when ROOT is enabled or C++17 otherwise. These exceptions do not
change the language mode of GAMBIT/CBS.

The selection and parsing rules can be checked without configuring or compiling:

```sh
cmake -P cmake/tests/cxx_standard.cmake
```
