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

For every profile, `CC`, `CXX`, `FC` and `CMAKE_<LANG>_COMPILER` selectors must
name one executable. Literal and quoted paths containing spaces work. Put options
in `CMAKE_C_FLAGS`, `CMAKE_CXX_FLAGS` or `CMAKE_Fortran_FLAGS`, and wrappers such
as ccache in the compiler launcher settings. Commands containing arguments are
rejected with the offending selector and the appropriate flag/launcher setting;
arguments are never silently discarded.

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
cmake --build --preset gambit-llvm --parallel 8

# Or choose CBS:
cmake --preset cbs-llvm --fresh
cmake --build --preset cbs-llvm --parallel 8
```

The examples use eight concurrent build jobs. `--parallel 8` and `-j8` are
equivalent for `cmake --build`; change the number to suit your CPU and memory.
Keep an explicit number: bare `--parallel` uses the native build tool's default,
which can mean unlimited jobs with Make. To use `CMAKE_BUILD_PARALLEL_LEVEL`
instead, omit the command-line parallel option, for example:

```sh
CMAKE_BUILD_PARALLEL_LEVEL=4 cmake --build --preset cbs-llvm
```

The explicit command-line option takes precedence over that environment default.
Changing the job count does not require clearing `build/` or reconfiguring.

All presets preserve the canonical `${sourceDir}/build` and GAMBIT output layout.
Dependency choices persist when switching profiles with the same compiler family.
Use `--fresh` when switching compiler families or deliberately resetting the
configuration. Bootstrap does not perform the switch itself.

## Shared dependency settings

Presets select the compiler and module scope; dependency defaults only initialise
missing cache entries. Switching `cbs-llvm` to `gambit-llvm` retains ROOT, Python,
RestFrames, ONNX Runtime, HDF5, SQLite3, MPI, cutflow, build type and custom package
paths. Explicit disabled choices persist too. A fresh CBS cache defaults to
RestFrames, ONNX Runtime, cutflow and CBS Rivet/Contur support enabled; a fresh
GAMBIT cache defaults to those features disabled. Switching an existing cache
preserves its choices rather than replacing them with the other profile's defaults.

```sh
cmake --preset cbs-llvm --fresh                 # initialise CBS defaults
cmake --preset gambit-llvm                     # keep dependency choices
cmake --preset gambit-llvm -DWITH_RESTFRAMES=OFF # persist an explicit change
```

`GAMBIT_AUTO_DETECT_PYTHON` and `GAMBIT_AUTO_DETECT_ROOT` default to `ON` for public
presets. Both CBS and GAMBIT use the same discovery steps. Python stays pinned to
the selected interpreter; an explicit `Python3_EXECUTABLE` takes precedence over
PATH discovery. CBS still requires Python development files; GAMBIT keeps its
native optional development-library policy.

`WITH_ROOT` accepts `AUTO`, `ON`, and `OFF` for presets. `AUTO` discovers a supported
ROOT installation, caches its prefix in `GAMBIT_ROOT_PREFIX`, and rechecks that
installation on subsequent configurations. The cache retains the `AUTO` request
even when ROOT is missing, so a later installation can be discovered. `OFF`
explicitly disables ROOT. `ON` retains GAMBIT's native FindROOT path, including
manual CMake package hints. `ROOTSYS` can select another installation. Ordinary
fresh configuration without a preset retains GAMBIT's original ROOT default of `OFF`.

The old `CBS_AUTO_DETECT_PYTHON` and `CBS_AUTO_DETECT_ROOT` entries are imported
once if their shared counterparts are unset, then removed. Shared names take
precedence. An old `WITH_ROOT=OFF` is preserved because it may have been an
explicit user choice. To enable automatic discovery in such an existing cache:

```sh
cmake --preset gambit-llvm -DWITH_ROOT=AUTO \
  -DGAMBIT_AUTO_DETECT_ROOT=ON -DGAMBIT_AUTO_DETECT_PYTHON=ON
```

Preserving dependencies does not guarantee a build without compilation: full
GAMBIT adds modules, and changes to the C++ standard or feature definitions may
rebuild affected targets. Existing matching external installations remain reusable.
Compiler-free cache-switch fixtures (temporary files and fake dependency tools):

```sh
python3 cmake/tests/preset_dependencies.py
```

## Compiler-free CMake regression tests

Run the shared script-test entry point from the repository root:

```sh
python3 cmake/tests/run_tests.py --list
python3 cmake/tests/run_tests.py
python3 cmake/tests/run_tests.py --log-dir /tmp/cmake-script-tests
```

The runner discovers the Python suites in `cmake/tests` and the C++ standard
policy script. It uses Python's standard library, CMake, Git, Make and standard
Unix tools. Each suite runs separately with a temporary working directory and
bytecode generation disabled. These checks do not configure or build GAMBIT,
execute real compilers, download packages or change existing installations.
Some tests configure temporary projects with `LANGUAGES NONE` to check cache
behaviour without enabling compilers.

`--list` only lists the suites and does not probe or execute tools. A normal run
retains per-suite logs in a fresh temporary directory and prints its path;
`--log-dir` selects a new directory and does not overwrite existing logs.
The per-suite timeout defaults to 120 seconds and can be changed with
`--timeout`. Failed, timed-out or incomplete suites make the runner exit
non-zero, while the remaining suites are still checked. Individual suite
scripts remain directly runnable.

The `CMake script tests` GitHub workflow uses this same entry point for pull
requests, selected branch pushes and manual runs. It retains logs for 14 days,
including failed runs. This quick CI checks build logic; full preset builds,
runtime smoke tests and package migration acceptance are separate work packages.

## Linux GNU preset build CI

The `CMake preset build` workflow adds the first TEST-02 job on Ubuntu 24.04.
It uses GNU 13, `/usr/bin/cmake`, a separate Python virtual environment and
the existing `cbs-gnu` configure preset and its `CBS` target. The job builds
the complete target and its declared dependencies in the checkout's canonical `build/`.
Executable, library and runtime directory defaults stay unchanged.

This initial baseline explicitly selects Release and C++17, with ONNX Runtime,
HDF5, SQLite3 and cutflow enabled. MPI, ROOT, RestFrames and CBS Rivet/Contur
integration are disabled. Required HepMC, YODA, FastJet/fjcontrib and nulike
remain part of the target. Python packages are fixed to pybind11 2.13.6 and
PyYAML 6.0.2; Ubuntu's older pybind11 package does not meet GAMBIT's minimum.
Cython is absent from this environment, so YODA builds its C++ library without
the optional Python extension. ROOT/RestFrames, Rivet/Contur, C++20/23, Linux
LLVM and automated macOS builds remain later matrix entries. The maintainer's
existing macOS acceptance remains valid.

The workflow runs for pull requests, `master`/`ci-*`/the current preset branch
pushes and manual dispatch. From a Mac, commit and push the workflow changes
normally; the Ubuntu runner performs the Linux build. Its virtual environment,
logs and fresh checkout belong to the job rather than the local Mac build.

The acceptance helper prints a plan by default, including on macOS:

```sh
python3 -B cmake/scripts/preset_build_acceptance.py
```

Actual execution requires Linux and both `--run` and `--fresh-checkout`. Use
only an independent, clean checkout with no existing `build/` or CBS artifacts;
the helper rejects existing build state rather than deleting it. The workflow
prepares the Python environment and supplies its matching pybind11 CMake path:

```sh
# Linux CI / independent fresh checkout only:
"$CBS_CI_PYTHON_DIR/bin/python" -B cmake/scripts/preset_build_acceptance.py \
  --run --fresh-checkout --root "$GITHUB_WORKSPACE" \
  --cmake /usr/bin/cmake --pybind11-dir "$CBS_CI_PYBIND11_DIR" \
  --jobs 2 --timeout 3600 --log-dir "$CBS_CI_LOG_DIR/acceptance"
```

The sequence is a fresh preset configure, complete CBS build, `CBS --help`,
direct repeated build, identical configure without `--fresh`, another build,
and final startup. Incremental phases retain the same build tree and feature
choices. Logs and file snapshots check native compilation, linking and code
generation, package preparation and audited external steps. Legacy repeated
build/install checks are reported separately; downloads, source resets and
patching cannot be hidden as incremental reuse. Native objects, libraries,
the executable, generated code and completion state must retain their content
and timestamps. Known configure-written diagnostic/version/HDF5-wrapper
metadata is compared by content, allowing its established timestamp rewrite.

Each command closes stdin and has a timeout; failure stops later phases and
retains the failed command's log and summary. `--log-dir` must name a new
directory. The job uses two build workers, has a 90-minute limit and retains
environment, dependency and acceptance diagnostics for 14 days under
`cbs-gnu-build-<run>-<attempt>`, including ordinary failed runs.

`CBS --help` validates startup and direct shared-library loading. Building or
running a Pythia backend, an analysis or a physics point requires separate
acceptance. Local fixture tests validate the helper; hosted Linux results are
recorded separately after the workflow runs.

## Maintainer acceptance

On 2026-10-13, the maintainer confirmed that macOS preset testing was
completed. macOS preset acceptance is complete for the tested local
environment. The detailed CBS feature-switch results below remain available
as the earlier acceptance record.

The current macOS `cbs-llvm` baseline has completed the ONNX/RestFrames scope
migration, full CBS linking, `--help` startup and direct/same-configuration no-op
builds.

Keep the current compiler, ROOT, SDK and shared `build/`. After the migration
build and the two no-op checks, run the feature acceptance helper from the
repository root with both features ON:

```sh
python3 cmake/scripts/cbs_feature_acceptance.py --run --jobs 8
```

The helper requires the existing `cbs-llvm` Unix Makefiles build. It runs ONNX
OFF/ON, then RestFrames OFF/ON, checks three/three/six/six compiled objects,
the expected links and CBS `--help` startup, then requires a final build with
zero compilation, linking or external steps. It compares the common header,
nine target flags, five shared-library link commands and installed package
headers/libraries by hash and nanosecond mtime. It records logs, snapshots,
command durations and `summary.json` in a new temporary directory printed at
startup. An optional `--log-dir /tmp/cbs-feature-check` must name a new directory.

Without `--run`, the script only prints help. It keeps the shared build and does
not clean, use `--fresh` or edit sources. A failure stops the sequence, retains
the logs and prints commands to restore both features ON; it can leave the last
tested feature OFF. A successful run restores both ON. Do not edit sources or
run another configure/build during the check. `--help` covers startup and direct
dynamic dependencies; analysis execution needs separate acceptance.

The current macOS `cbs-llvm` run passed all four switches and the final no-op
check, with 95 stable snapshot files and both features restored ON. This build baseline is ready for
delivery preparation; a small CBS YAML run remains separate functional acceptance.

Linux and independent new-environment builds require separate acceptance.
Use another checkout or test machine for an independent clean build; each
checkout still uses `build/`. Physical-result validation is recorded separately
from preset acceptance. Ninja and lld adaptations remain deferred. The
maintainer runs all real configure/build and executable checks.

## Selecting an LLVM compiler

For every `*-llvm` profile, each language uses `CMAKE_C_COMPILER` /
`CMAKE_CXX_COMPILER` first, then `CC` / `CXX`. With neither specified, discovery
keeps its existing Homebrew, standard installation and PATH search order.
Cached compiler paths count as explicit selections and take precedence over a
changed environment. Bootstrap reads the current environment without reading
the build cache, so its report can differ from an already configured build.

Explicit C/C++ selections must be supported upstream Clang with the same version.
A missing executable, AppleClang/GNU pair, old compiler or version mismatch is
reported without falling back to a different LLVM installation. If only one
language is specified, its companion is sought beside that executable or in its
real installation, including matching `clang-<major>` / `clang++-<major>` names.
If no matching companion exists, set the other compiler explicitly. The reported
LLVM root is derived from the real C++ executable.

For read-only discovery with your chosen installation:

```sh
CC=/path/to/llvm/bin/clang CXX=/path/to/llvm/bin/clang++ \
  ./cmake/bootstrap --preset cbs-llvm --verbose
```

For configure, use explicit cache values when working with an existing build:

```sh
cmake --preset cbs-llvm \
  -DCMAKE_C_COMPILER=/path/to/llvm/bin/clang \
  -DCMAKE_CXX_COMPILER=/path/to/llvm/bin/clang++
```

Keep the current compiler paths for an incremental check. When actually changing
compilers or versions, add `--fresh` and expect the necessary rebuild; all profiles
still share `build/`.

Script-only checks, with fake version reporters and no real compiler execution:

```sh
python3 cmake/tests/native_compiler_selection.py
```

## Selecting a macOS SDK

GAMBIT and CBS resolve the SDK before `project()` enables compilers. A non-empty
`CMAKE_OSX_SYSROOT` (including the cache) takes precedence over `SDKROOT`; with
neither set, `xcrun --sdk macosx --show-sdk-path` supplies the default. SDK names
such as `macosx` are resolved to an existing directory and saved as a cache path.
A missing path or failed name lookup is an error, with no fallback to another SDK.

```sh
cmake --preset cbs-llvm -DCMAKE_OSX_SYSROOT=/path/to/MacOSX.sdk
```

Native targets, backend flags and CMake external projects receive the selected
SDK. SDK paths containing spaces are quoted in the legacy flag strings. Existing
`MACOS_DEPLOYMENT_TARGET` settings are preserved; when no minimum is specified,
its initial default comes from the selected SDK's version.

On macOS, upstream Clang uses the selected SDK's libc++ headers alongside Apple's
system libc++ runtime. This also applies to external C++ builds, including YODA's
Python extension, and avoids the LLVM 22/macOS 27 header interaction that can
leave `DBL_MAX` undefined after including `Python.h` or `<cmath>`. Explicit
`-stdlib=`, `-stdlib++-isystem`, or `-nostdinc++` choices are preserved.

The resolved default is cached too. To discover the active SDK again without
clearing the build tree or other cache entries:

```sh
env -u SDKROOT cmake --preset cbs-llvm -U CMAKE_OSX_SYSROOT
```

Use your current SDK for the first incremental check. This change adds the SDK
argument to CMake external recipes, so an existing package such as HepMC may
configure/build/install once to migrate its command. A real SDK change can require
rebuilding dependencies; unchanged subsequent configurations should remain stable.

Script-only checks, with synthetic xcrun responses and no real probes or compilers:

```sh
python3 cmake/tests/macos_sdk.py
```

## OpenMP and macOS compiler flags

Native C/C++ compilation gets SDK and minimum-version options from
`CMAKE_OSX_SYSROOT` and `CMAKE_OSX_DEPLOYMENT_TARGET`; GAMBIT no longer appends
another copy to global compiler/linker flags. `MACOS_DEPLOYMENT_TARGET` remains
the common minimum policy. GNU Fortran receives an explicit fallback for each
option that CMake's platform detection omitted. Conflicting explicit `-isysroot`
or `-mmacosx-version-min` flags fail with guidance to use the common variables.

Autotools and handwritten Makefiles receive the same SDK/minimum through derived
backend flags, including the C dialect variants. CMake external recipes use the
common `CMAKE_OSX_*` arguments and omit these extra flags while retaining their
package-specific standard, includes, warnings and linker options.

One shared OpenMP discovery now requires C, C++ and Fortran support. On macOS,
Clang/AppleClang use Homebrew libomp hints when available; the automatic cache
values match the flags actually appended to native compilation. Executables link
the discovered library list, avoiding another copy of imported OpenMP compile
options. Fortran keeps its own discovered runtime. The CBS summary reports each
language's OpenMP flags/libraries and the common SDK/minimum.

Only GAMBIT-owned hints are refreshed automatically; editing such a cache value
makes it user-owned. The exact legacy Homebrew hint bundle is migrated once.
Other manual OpenMP hints are preserved and still must describe a usable setup.
This does not force the complete computed `CMAKE_<lang>_FLAGS` into the cache;
CMake's cache entries remain user inputs to the normal configure-time flags.

For the same compiler profile and SDK, keep `build/` and configure normally.
The first migration changes compilation and external recipe inputs, so rebuilding
native objects and some dependencies is expected. After it completes, repeat the
same configure/build to check stable reuse. Compiler-family switches still need
`--fresh`. Script-only policy checks use synthetic process/package results:

```sh
python3 cmake/tests/platform_flags.py
```

## Validation check caches

CBS keeps C/C++/Fortran, macOS linker and Python/Boost/HDF5/SQLite compile/link
results cached while their inputs are unchanged. The shared HDF5 usability check
also follows this policy, so a repaired install can recover before feature
selection disables its printers and readers.

A changed compiler identity, flags, configuration, SDK/minimum, required probe
settings, package version or selected include/library path invalidates the
corresponding result. Selected probe headers and the toolchain file are hashed;
absolute compiler, linker, interpreter and library files use real path, size and
timestamp. Missing/created files and symlink changes count too. Package-specific
changes normally recheck that package; common toolchain changes can recheck all
checks. New or changed inputs produce `Validation: ... check inputs are new or
changed` messages. The next identical configure reuses both PASS and FAIL.

An existing build rechecks once when migrating to these signatures. This adds
small configure-time probes; it does not clear objects or external installations.
Keep the current profile and `build/`, then configure/build normally:

```sh
cmake --preset cbs-llvm
cmake --build build --target CBS -j8
cmake --preset cbs-llvm
cmake --build build --target CBS -j8
```

To force only these validation results to be checked again, remove their input
signatures and reconfigure. Other cache entries and build outputs remain:

```sh
cmake --preset cbs-llvm -U 'GAMBIT_CHECK_CACHE_*'
cmake --preset cbs-llvm
```

This mechanism validates the inputs selected by `find_package`; it does not clear
finder caches or choose a different dependency installation. Set appropriate
package hints and confirm the reported paths when changing installs. It does not
scan all transitive headers/libraries or SDK contents. Binary changes preserving
both size and timestamp, unresolved library names/imported-target files, and
untracked transitive inputs may need the explicit reset above. A real compiler
family switch still requires `--fresh` under the shared-build policy.

Script-only regression checks use synthetic probes with native cache semantics;
no real compiler or project configure is invoked:

```sh
python3 cmake/tests/validation_cache.py
```

## Process-local discovery reuse

`ProcessProbe.cmake` reuses explicitly read-only compiler `--version` / GNU
version queries, Homebrew LLVM prefix queries, `xcrun --find`, and Python
metadata within the current CMake process. The key includes command arguments,
working directory, timeout, relevant toolchain/Python environment variables,
executable real path/size/timestamp, and explicit probe-script content hashes.
Compiler selection and profile validation still run normally. The helper is not
used for configure/build/install commands or compile/link validation.

Results use GLOBAL properties, never `CMakeCache.txt`. Each bootstrap or configure
process starts empty; toolchain child processes have their own results. Changing
the selected executable, supported environment inputs, or probe source within a
process creates a new key. Installing/removing modules or changing dependencies
between configurations is observed on the next configure. No persistent Python
module cache needs to be cleared. Package mutation during one configuration is
outside this reuse contract.

`PythonModules.cmake` imports each requested group in one Python process, then
shares the raw per-module results with native GAMBIT, CBS, backend and scanner
checks. The main required modules are batched with selected CBS Rivet/Contur
modules; distinct scanner requirements form another batch. Already checked
modules are excluded from later batches. The required/optional rules and scanner
package aliases remain unchanged. The native h5py/HDF5 version check is applied
to the shared import result whenever h5py is consumed, without launching another
interpreter. The script keeps the working directory on the import path and runs
with `-B`, without generating probe bytecode.

A batch uses a total timeout of ten seconds per requested module. Completed
records survive a crash or timeout; only unreported modules are retried separately
with a ten-second timeout. A failed required module still stops configuration;
failed optional imports retain their existing missing-dependency behavior.

Bootstrap gathers module requests only from selected, host-compatible providers.
GAMBIT requests `yaml`; CBS adds `cython`, `configobj`, `pandas`, and `matplotlib`.
The common interpreter metadata query is reused while each provider applies its
own development-library policy. `--list`, invalid filters, and selections for
another host still perform no environment probes.

Script fixtures can be run without configuring/building or querying real compilers:

```sh
python3 cmake/tests/process_probes.py
python3 cmake/tests/native_compiler_selection.py
```

For manual acceptance, use the existing shared `build/` without `--fresh` when
retaining the same compiler profile. Run bootstrap for both systems and only
GAMBIT, then configure/build twice. Preset identities and missing-module reasons
should stay consistent; unchanged configurations should not invalidate native
validation results or introduce object compilation, links or external package
steps. Measure configure time separately from generation/build time; process
count reductions alone do not establish a real-world speedup.

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
Use `--fresh` when changing compiler families or resetting dependency choices;
same-family profile switches retain the shared cache. `./cmake/bootstrap` reports
only the project's registered
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
An optional `preset_probe_python_modules_<system>(output_modules)` function can
return a module list in the parent scope before common discovery. The dispatcher
combines those requests with `yaml` for one import batch; providers keep their own
required/optional policy when consuming results.
The CLI and dispatcher need no change when adding a provider that uses
the existing toolchain strategies.

## Backend interface trimming

`GAMBIT_TRIM_BACKEND_INTERFACES` accepts `AUTO`, `ON`, or `OFF`:

| Mode | Behavior |
| --- | --- |
| `AUTO` (fresh-cache default) | Trim interfaces when any Bit is excluded; retain all interfaces with the full Bit set. |
| `ON` | Trim unused interfaces regardless of module selection. |
| `OFF` | Retain all interfaces, including unreferenced ones needed for backend development. |

The cache stores the requested mode. The effective ON/OFF result is resolved
for each configure and shown as `Backend trim: AUTO -> ON`, for example.
Explicit ON/OFF remains fixed across later module switches, even when it equals
the previous automatic result. With trimming enabled,
`GAMBIT_FORCE_BACKEND_INTERFACE="Name1;Name2"` retains selected interfaces.

Existing ON/OFF caches keep their values, including values written by the old
automatic policy: those caches cannot distinguish an automatic default from
an explicit selection of the same value. To restore automatic selection:

```sh
cmake --preset cbs-llvm -DGAMBIT_TRIM_BACKEND_INTERFACES=AUTO
```

This does not require clearing `build/`. The lean CBS module selection resolves
AUTO to ON. The conventional CMake BOOL spellings such as TRUE/FALSE and 1/0
remain accepted; unknown modes fail with a clear configure error.

## Retaining optional contributed packages

Disabling RestFrames, or selecting Bits without ColliderBit (which disables
HepMC and YODA), preserves their source/install trees, external build directories,
and completion stamps. Re-enabling the same package with the same toolchain and
inputs can reuse that work. A compiler, flags, dependency, or patch change may
still require reconfiguration or rebuilding.

The package's build target and link settings are excluded while disabled.
RestFrames retains a private include path on ColliderBit so switching OFF/ON
does not change its compile flags; unrelated targets receive no RestFrames path.
HepMC and YODA include paths are excluded while those packages are disabled.
The explicit `clean-<package>` and `nuke-<package>` targets remain
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

## RestFrames switch and native recompilation

RestFrames settings are generated in
`cmake/include/gambit/cmake/restframes_variables.hpp`, separate from the common
`cmake_variables.hpp`. RestFrames analyses, their registration container and
`gambit_preload.cpp` include it explicitly. Preload uses the feature settings to
set `CPLUS_INCLUDE_PATH` for enabled RestFrames. New or locally maintained
RestFrames analyses must include both headers before their feature guards:

```cpp
#include "gambit/cmake/cmake_variables.hpp"
#include "gambit/cmake/restframes_variables.hpp"
#ifndef EXCLUDE_ROOT
#ifndef EXCLUDE_RESTFRAMES
// RestFrames-dependent implementation
#endif
#endif
```

The RestFrames include path is private to the ColliderBit object library and
stays present even when disabled or not installed. `EXCLUDE_RESTFRAMES` determines
availability; the include path alone does not. Existing package dependencies
ensure the enabled headers are installed before ColliderBit compiles.

The first configure/build after this change can rebuild many native objects:
the common header loses the old RestFrames fields and unrelated targets lose
their old directory-level include path. After that migration, toggling only
`WITH_RESTFRAMES` should recompile the four RestFrames analyses,
`AnalysisContainer.cpp` and `gambit_preload.cpp`, with necessary links. Keep ROOT,
compiler, standard and all other settings fixed during this check; no build-tree
reset is needed. The optional runtime path policy below also prevents the
RestFrames switch from changing unrelated shared-library link commands.

RestFrames reuse also requires a matching build identity for the compiler,
flags, ROOT installation, platform, source repository/tag and patch inputs,
with required installed files present. A legacy installation without a record requires one rebuild.
The record is written only after a successful installation. Source preparation
reuses a local Git checkout only when its origin matches the requested
repository; a changed repository uses the requested upstream. Existing completed
downloads are left for this preparation step, so a new tag is not fetched from
a retained old origin.

CMake watches `cmake/scripts/patch_restframes_quiet.cmake`. Editing it and then
running a normal `cmake --build` automatically regenerates the configuration;
a changed patch hash schedules clean source preparation before patching.
Touching that file without changing its contents can regenerate CMake, but
retains matching RestFrames objects and installation stamps. Git downloads and
tag retries disable terminal/askpass prompts, use bounded timeouts and report
failures clearly.

Script-only checks:

```sh
python3 cmake/tests/restframes_build_identity.py
python3 cmake/tests/restframes_scope.py
python3 cmake/tests/contrib_retention.py
```

## ONNX switch and optional runtime paths

ONNX availability is generated in
`cmake/include/gambit/cmake/onnxruntime_variables.hpp`, separate from the common
configuration header. Include it before testing `EXCLUDE_ONNXRUNTIME`:

```cpp
#include "gambit/cmake/onnxruntime_variables.hpp"
#ifndef EXCLUDE_ONNXRUNTIME
// ONNX-dependent implementation
#endif
```

The public `onnx_rt_wrapper.hpp` includes this feature header itself and exposes
ONNX types. Its dependency include path therefore remains PUBLIC on ColliderBit,
with the same value while ONNX is OFF or its installation is not present yet.
Executables using ColliderBit objects receive that include path explicitly;
standalone program objects copy the executable's settings. Models, Utils,
Backends and unrelated standalones do not receive the ONNX path.

After the one-time migration of the common header and include flags, changing
only `WITH_ONNXRUNTIME` should recompile `onnx_rt_wrapper.cpp`,
`Analysis_ATLAS_SUSY_2018_30.cpp` and `AnalysisContainer.cpp`, then relink CBS.
Other analyses and standalone program objects should retain their compile flags.
ONNX download/installation and dependency ordering keep their existing policy;
disabling the feature does not remove the installed archive contents or stamps.

RestFrames and ONNX library directories are appended to an executable's
`INSTALL_RPATH` only when its link list uses that library. The helper preserves
inherited/user runtime paths and avoids adding a duplicate package path.
These two optional packages no longer change the global runtime path used by
unrelated shared libraries. Other runtime paths (ROOT, HepMC, YODA, FastJet and
FlexibleSUSY) keep their existing policy. Explicit user runtime paths are retained
when a feature is disabled.

The first build can recompile many objects and relink libraries because the
common header and existing include/runtime flags migrate. Keep the shared
`build/`; do not clean or use `--fresh`. Measure OFF/ON behavior only after the
initial build has completed successfully.

Script-only checks:

```sh
python3 cmake/tests/onnxruntime_scope.py
python3 cmake/tests/restframes_scope.py
python3 cmake/tests/standalone_objects.py
python3 cmake/tests/contrib_retention.py
python3 cmake/tests/cbs_feature_acceptance.py
```

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

## External backend incremental builds

`nulike_1.0.9`, `rivet_4.1.0` and `contur_3.0.0` check declared source inputs
and required products before invalidating their build stamps. Successful installs
record source paths, nanosecond modification times, sizes and content hashes in
`build/<package>-prefix/tmp/<package>-source-state.json`. The signature also covers
the actual external configure/build/install commands and compiler identities.
The first build runs these wrappers once to create their records.

Unchanged builds retain the stamps, skipping Rivet data installation/library
copying and the resulting Contur configure cascade. Editing, touching, adding or
removing a declared source still enables the package's incremental make step.
Missing required build products also enable that step; missing declared configure
products additionally invalidate configure. Records are written only after a
successful install and product check. Internal make determines which objects
need compilation; this does not introduce a compiler/ABI migration policy for
these backends.

Rivet tracks its C++/header/Python/analysis inputs, upstream FastJet/YODA/HepMC
headers and libraries, and checks after those dependencies finish. Contur tracks
its database Makefile/SQL inputs and requires its database and generated Python
initialization module. Rivet Python product checks accept both site-packages and
dist-packages. Generated objects, libtool objects and compilation/cache directories
are excluded from source snapshots. Other backend/scanner versions retain the
existing automatic make-check policy until their inputs and products are audited.
The existing explicit clean/nuke targets and pristine Rivet patch preparation
remain available.

Cached source downloads preserve the archive's file timestamps when copying
from the extraction staging directory. Rivet 4.1.0 ships generated Autotools
files; losing their timestamp ordering can cause `make` to request
`aclocal-1.17` and regenerate the `Makefile.in` files patched by GAMBIT. No
Autotools regeneration is needed for the supplied Rivet release and patches.
Rivet's pristine preparation tracks the downloader and its copy helper, so the
first build after this fix reconstructs an old source tree before patching and
BOSS. Preserve any manual edits to downloaded Rivet sources before that build.
Subsequent unchanged builds keep the existing preparation/patch stamps.

Use the existing compiler and shared build tree:

```sh
cmake --preset cbs-llvm
cmake --build build --target CBS -j8
cmake --build build --target CBS -j8
cmake --preset cbs-llvm
cmake --build build --target CBS -j8
```

After the initial successful build, the unchanged builds should have no external
configure/build/install or source-state record steps for these three packages.
The lightweight `check-rebuild-*` targets still run. No clean or build-tree reset
is needed. For a source-edit smoke test, touch
`Backends/installed/nulike/1.0.9/src/utils.f`, build CBS, then build again: only the
first build should re-enter nulike's build step.

Script-only regression checks:

```sh
python3 cmake/tests/external_auto_rebuild.py
python3 cmake/tests/source_download.py
python3 cmake/tests/rivet_installation.py
```

The source-download suite uses tiny cached fixtures without network access.
The Rivet suite additionally checks the real download/patch pipeline and its
Autotools timestamp ordering when `Backends/downloaded/rivet_4.1.0.tar.gz` is
already cached; it skips when the archive is absent. Neither suite configures
or compiles Rivet.

The current macOS LLVM build has passed initial recording, direct unchanged
builds and unchanged builds after reconfiguration. Source-touch, timestamp comparisons and other platforms remain
to be verified.

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
