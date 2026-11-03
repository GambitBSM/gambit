# Changes from the mainline base

This document summarizes the committed changes on `GUMMARTY` relative to the
commit where it diverged from the repository's `master` branch.

- **Base commit:** [`6772f48511f48009c10577645aa5e10d2a1c05c3`](https://github.com/GambitBSM/gambit/commit/6772f48511f48009c10577645aa5e10d2a1c05c3), dated 2025-04-30
  (`Merge pull request #538 from GambitBSM/spartan_yaml_correction`)
- **Branch tip:** `3d9bdd7d55` (`Update MARTY test to avoid checking for things we don't want Also adds a dependency so marty_test will not build if MARTY has not been built`)
- **Scope:** 7 branch commits; 7 files changed (643 insertions, 89 deletions).

The comparison uses the common ancestor with `origin/master`, rather than the
latest `master` tip. Local uncommitted and untracked working-tree files are not
included.

## Summary

The branch adds an early integration path for using MARTY with GUM, including a
mode that can be configured without Mathematica, input parsing for MARTY model
files, and a C++ MARTY smoke-test target.

## Changes

### Build configuration and Mathematica-free mode

- Adds the `itch_Mathematica` CMake option. When enabled, GUM skips Mathematica,
  FeynRules, and SARAH detection and omits the corresponding Boost.Python
  libraries and `mathematica` executable. The regular setup remains in place
  when the option is disabled. See [gum/CMakeLists.txt](./gum/CMakeLists.txt).
- Adds a `gum_nomathematica` launcher and a Python entry point that use the
  interpreter selected during CMake configuration. The entry point handles
  command-line parsing, dry-run/reset checks, and routes `.gum` input through
  the MARTY-specific parser. See [gum/gum_nomathematica](./gum/gum_nomathematica)
  and [gum/gum_nomathematica.py](./gum/gum_nomathematica.py).

### MARTY input handling

- Adds MARTY-specific `.gum` validation and GUM input/output object creation.
  The new path accepts `marty` as the math package and currently handles
  Pythia output options. See [gum/src/parse.py](./gum/src/parse.py).
- Adds [gum/gum_files/MARTY_TEST.gum](./gum/gum_files/MARTY_TEST.gum), an example
  MSSM input requesting Pythia output and sample collider processes.

### MARTY build and smoke test

- Adds MARTY as a CMake external project, configured for installation under
  `gum/contrib/MARTY/install`.
- Adds a `marty_test` executable. CMake substitutes the MARTY install path into
  a generated source file, links the MARTY libraries, and makes generation
  depend on the MARTY external project.
- Adds [gum/src/marty_test.cpp](./gum/src/marty_test.cpp), which constructs a
  sample gauge model, computes a tree-level amplitude and squared amplitude,
  and asks MARTY to build a generated library.

## Merge conflict resolution

The merge conflict in [gum/CMakeLists.txt](./gum/CMakeLists.txt) was resolved
by preserving the `itch_Mathematica` conditional while adopting CMake's
`Python3_*` variables for Boost.Python component selection and library linking.
This keeps the Mathematica-free GUM configuration while using the Python 3
configuration introduced on the other side of the merge. Configuration was
verified with:

```bash
cmake -S gum -B gum/build -Ditch_Mathematica=ON
```

## Building and running the tests

Build MARTY (including its test executables) from the repository root:

```bash
cmake --build gum/build --target MARTY -j2
```

Run MARTY's unit tests with CTest's `units` label:

```bash
ctest --test-dir gum/build/MARTY-prefix/src/MARTY-build \
  -L units --output-on-failure
```

The GUM `marty_test` target is a separate smoke test, not part of that unit-test
suite. Build it with:

```bash
cmake --build gum/build --target marty_test -j2
```

Run it from the GUM directory so its generated output is written there, and
provide MARTY's installed shared libraries to the dynamic loader:

```bash
cd gum
LD_LIBRARY_PATH="$(pwd)/contrib/MARTY/install/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}" \
  ./build/marty_test
```

In the current environment, `marty_test` builds but crashes in MARTY's library
generation code after calculating the squared amplitude; successful compilation
does not yet mean this smoke test passes.

## Files changed

| File | Change |
|---|---|
| [gum/CMakeLists.txt](./gum/CMakeLists.txt) | Adds the Mathematica-free configuration path. |
| [gum/cmake/contrib.cmake](./gum/cmake/contrib.cmake) | Adds the MARTY external project and smoke-test target. |
| [gum/gum_files/MARTY_TEST.gum](./gum/gum_files/MARTY_TEST.gum) | Adds a sample MARTY input file. |
| [gum/gum_nomathematica](./gum/gum_nomathematica) | Adds the launcher for the new mode. |
| [gum/gum_nomathematica.py](./gum/gum_nomathematica.py) | Adds the Python entry point for the MARTY workflow. |
| [gum/src/marty_test.cpp](./gum/src/marty_test.cpp) | Adds the C++ MARTY smoke test. |
| [gum/src/parse.py](./gum/src/parse.py) | Adds MARTY-specific input parsing and object construction. |
