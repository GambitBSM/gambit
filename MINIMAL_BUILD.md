# Minimal GAMBIT build

End-to-end recipe for a minimal GAMBIT build: ditching all the physics "Bits", not building any backends and only building a couple of scanners. 

The resulting `./gambit` binary can still be large and take several minutes to build
from scratch on 16 cores (the bottleneck is the single huge `Core/src/gambit.cpp`
translation unit).

## 1. System packages

```
sudo apt-get update
sudo apt-get install -y \
    gfortran g++-12 gcc-12 \
    libeigen3-dev libgsl-dev libboost-all-dev libhdf5-dev \
    libblas-dev liblapack-dev pkg-config
```

Why each:
- `gfortran` — required (Fortran backends, BLAS interfaces).
- `g++-12 / gcc-12` — `cmake/backends.cmake` hard-codes
  `--castxml-cc=g++-12` for the Prob3++ BOSS step (workaround for a
  g++-13/clang-castxml conflict). Without g++-12 the prob3pp build
  aborts at the BOSS/CastXML stage.
- `libeigen3-dev` — provides `/usr/include/eigen3`, used in the cmake
  invocation below.
- `libgsl-dev`, `libboost-all-dev`, `libhdf5-dev` — runtime / build deps.
- `libblas-dev liblapack-dev` — without LAPACK, cmake's optional.cmake
  errors out with "LAPACK shared library not found".

### Optional: MPI

To build GAMBIT with MPI support (required to run multi-process scans
with `mpiexec -np N ./gambit ...`, and to exercise any printer / scanner
code paths gated on `#ifdef WITH_MPI`), additionally install OpenMPI:

```
sudo apt-get install -y libopenmpi-dev openmpi-bin
```

This provides `mpiexec`, `mpicc`, `mpic++`, and the headers/libs that
cmake's MPI detection picks up. Then add `-DWITH_MPI=True` to the cmake
invocation in step 3. Verify the install with:

```
mpiexec --version    # should report Open MPI 4.x
which mpic++         # /usr/bin/mpic++
```

## 2. Python packages

By default cmake picks a different interpreter (e.g. `/usr/local/bin/python3`,
3.11 in this sandbox) and a different runtime libpython (the system one,
e.g. `libpython3.10`). That mismatch forces you to install runtime Python
packages (numpy, numba, pandas, scipy, mpmath) **twice** — once for each
interpreter — or `./gambit -h` aborts with `ModuleNotFoundError: numpy`.

Avoid this by pointing cmake at a single Python via `PYTHON_EXECUTABLE`,
`PYTHON_INCLUDE_DIR` and `PYTHON_LIBRARY` (see the cmake step below). Then
install the packages once for **that** interpreter:

```
pip install --user numpy numba pandas scipy mpmath
```

(In the Claude Code sandbox the chosen interpreter is
`/usr/local/bin/python3` = 3.11.15, so this `pip --user` install is the
one needed.)

## 3. Configure (cmake)

```
mkdir -p build && cd build
cmake -DPYTHON_EXECUTABLE=/usr/local/bin/python3 \
      -DPYTHON_INCLUDE_DIR=/usr/include/python3.11 \
      -DPYTHON_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.11.so \
      -DEIGEN3_INCLUDE_DIR=/usr/include/eigen3 \
      -DWITH_MPI=False \
      -DWITH_ROOT=False \
      -Ditch="ColliderBit;CosmoBit;DarkBit;NeutrinoBit;ObjectivesBit;FlavBit;DecayBit;SpecBit;PrecisionBit;Mathematica" \
      ..
```

Notes:
- `PYTHON_EXECUTABLE`/`PYTHON_INCLUDE_DIR`/`PYTHON_LIBRARY` make cmake use
  the same Python (3.11 here) for both build-time scripts and the runtime
  libpython — eliminating the dual pip install. Confirm by looking for
  matching versions in the cmake output:
  ```
  Using Python interpreter version 3.11.15 for build.
  Using Python libraries version 3.11.15 for Python backend support.
  ```
  If you see a `NOTE: You are using different Python versions for the
  interpreter and the libraries!` message, the flags weren't picked up
  (likely because `CMakeCache.txt` from a previous run is sticky — wipe
  the build dir and rerun).
- `itch` lists modules to **exclude** from the build.
- `WITH_MPI=False` and `WITH_ROOT=False` keep the build minimal. Set
  `-DWITH_MPI=True` instead if you installed OpenMPI per the optional
  step in section 1; cmake will then pick up `mpic++` automatically and
  compile the `#ifdef WITH_MPI` branches in the printer / scanner code.
- This first cmake call takes ~75 seconds (it clones pybind11, runs many
  feature checks).

## 4. Build scanners, then re-cmake, then build gambit

```
make diver
make multinest
cmake ..                  # re-detect newly built scanner libraries
make gambit -j$(nproc)
```

Expected timings on 16 cores:
- `diver`: ~1 min (mostly download)
- `multinest`: ~1 min (mostly download)
- `cmake ..`: ~75 s
- `make gambit -j16`: Can take ~25 min (gambit.cpp.o alone can take ~20 min)

The whole chain runs cleanly start-to-finish if build is done in the order above.

### Long-running build tip (Claude Code)

The `Bash` tool defaults to a 10-minute timeout, but exceeding it does
**not** kill the command — the tool returns "running in background" and
the build continues. You can poll with subsequent `ps`/`tail` calls. Or
raise the cap explicitly via the `BASH_MAX_TIMEOUT_MS` env var in
`~/.claude/settings.json` (e.g. set to `3600000` for 60 min):

```json
{
  "env": { "BASH_MAX_TIMEOUT_MS": "3600000" }
}
```

To watch a verbose log instead of the silent default, prepend `VERBOSE=1`:

```
make gambit -j$(nproc) VERBOSE=1
```

## 5. Smoke test

```
./gambit --version
./gambit -h
./gambit -d -f yaml_files/spartan.yaml   # dry-run, prints functor tree
```

A successful dry-run prints the resolved dependency tree.

## 6. Run example

Without MPI:

```
OMP_NUM_THREADS=1 ./gambit -rf yaml_files/spartan.yaml
```

With MPI (build configured with `-DWITH_MPI=True`):

```
OMP_NUM_THREADS=1 mpiexec -np 2 ./gambit -rf yaml_files/spartan.yaml
```

If `mpiexec` complains about running as root in a container, add
`--allow-run-as-root` (and, if you hit "not enough slots", also
`--oversubscribe`):

```
OMP_NUM_THREADS=1 mpiexec --allow-run-as-root --oversubscribe -np 2 \
    ./gambit -rf yaml_files/spartan.yaml
```

