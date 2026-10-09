# Rivet shim prototype

This directory contains a standalone prototype of a hand-written, BOSS-free
frontend for the Rivet backend, discussed as an alternative to BOSS's
castxml-based code generation.

**This is not wired into the GAMBIT build.** `cmake/backends.cmake` still
BOSSes Rivet exactly as before, and `ColliderBit_measurements.cpp` still uses
the BOSS-generated frontend at
`Backends/include/gambit/Backends/frontends/Rivet_4_1_0.hpp`. These files
exist to demonstrate the pattern and were not compiled against a real Rivet
install in this environment (Rivet/HepMC3/YODA are not present here, and
there is no network access to fetch them).

## Files

- `rivet_shim.cpp` — the shim itself. Ordinary C++, compiled directly
  against the real `Rivet/AnalysisHandler.hh`, `Rivet/Tools/RivetPaths.hh`
  and `HepMC3/GenEvent.h`. Exports a flat, unmangled (`extern "C"`) API
  covering the 13 `AnalysisHandler`/free-function entry points that
  `ColliderBit_measurements.cpp` actually calls, versus the ~96 methods the
  current BOSS config auto-wraps.
- `../../../include/gambit/Backends/frontends/shims/Rivet_4_1_0_shim.hpp` —
  the GAMBIT-side header. Presents a C++ `AnalysisHandler` class with the
  same method names/signatures ColliderBit already calls, backed by
  `dlsym`'d calls into the shim instead of BOSS-generated wrapper/abstract
  classes.

## What a real integration would still need

1. **A build target for the shim.** `rivet_shim.cpp` needs to be compiled
   into `librivet_shim.so` *after* Rivet/HepMC3/YODA are built, linked
   against them, analogous to the existing `ExternalProject_Add(rivet_4_1_0
   ...)` step in `cmake/backends.cmake`. The hand-rolled `ShimLibrary`
   loader in the header uses a bare `"librivet_shim.so"` path and `dlopen`
   as a stand-in for this — a real version should reuse GAMBIT's existing
   backend-path resolution (the same mechanism that locates `librivet.so`
   today) rather than hardcoding a filename.
2. **Reusing `LOAD_LIBRARY`/`BE_FUNCTION` instead of hand-rolled `dlsym`.**
   GAMBIT's frontend macros already do exactly this kind of symbol lookup
   (`BE_FUNCTION`'s `SYMBOLNAME` argument is already a list of mangled-name
   candidates resolved via `dlsym`) — the macros don't actually care whether
   the symbol came from BOSS or was hand-written. The prototype header
   reimplements a minimal version of this directly so it can be read
   standalone; a real patch would delete `ShimLibrary` and declare these
   functions through `BE_FUNCTION` the same way every other frontend does.
3. **Deciding where `Rivet_4_1_0_shim::AnalysisHandler` lives relative to
   the real one.** For this to be a drop-in replacement, it would need to
   end up in the same namespace/typedef position
   (`Gambit::Backends::Rivet_4_1_0::Rivet::AnalysisHandler`) that
   `ColliderBit_measurements.cpp` includes today, so no module code changes.
4. **Compile-testing against a real Rivet install**, which this environment
   doesn't have. Before this would be trusted for real physics runs it
   needs to actually build and run against Rivet 4.1.0, HepMC3 and YODA,
   and its output should be checked against the existing BOSS-generated
   path on at least one real analysis run.

See `Backends/scripts/ShimGenerator/` for a generalised, step-by-step guide
to producing the equivalent of this prototype for other BOSSed backends.
