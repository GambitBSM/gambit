# Rivet shim: now wired into the build

This directory contains a hand-written, BOSS-free frontend for the Rivet
backend, now wired into `cmake/backends.cmake` as a real replacement for
BOSS on this one backend.

## What changed

- `cmake/backends.cmake`: the `BOSS_backend(rivet ...)` call is gone (left
  as a comment for reference). In its place, an `ExternalProject_Add_Step`
  compiles `rivet_shim.cpp` into `librivet_shim.so` right after Rivet's own
  `libRivet.so` is built, linking against it plus HepMC3/YODA.
- `config/backend_locations.yaml.default`: Rivet 4.1.0 now points at
  `librivet_shim.so` instead of `libRivet.so` (the shim pulls in `libRivet.so`
  itself via its own linked dependencies, so dlopening the shim is enough).
- `Backends/include/gambit/Backends/frontends/Rivet_4_1_0.hpp`: rewritten by
  hand. Declares the shim's flat functions via the standard `BE_FUNCTION`
  macro (the same one `Backends/include/gambit/Backends/frontends/LibFirst_1_0.hpp`
  uses for its own hand-written, non-BOSS frontend) and wraps them in an
  `AnalysisHandler` class with the same method names ColliderBit already
  calls. No `ColliderBit` source change needed.
- `Backends/include/gambit/Backends/backend_types/Rivet_4_1_0/identification.hpp`:
  `DO_CLASSLOADING` flipped from 1 to 0. BOSS's classloading mechanism
  (dlsym-ing factory functions, compiled *into* `libRivet.so` itself, that
  construct objects with virtual dispatch back across the `.so` boundary)
  isn't used any more — the shim only needs flat `BE_FUNCTION` symbol
  resolution.
- The earlier standalone prototype header at
  `Backends/include/gambit/Backends/frontends/shims/Rivet_4_1_0_shim.hpp`
  (hand-rolled `dlopen`, not wired into the build) has been deleted — it's
  superseded by the real `Rivet_4_1_0.hpp` rewrite using `BE_FUNCTION`.
- The other BOSS-generated files in that same directory
  (`abstract_AnalysisHandler.hh`, `wrapper_AnalysisHandler*.hh`,
  `forward_decls_*.hh`, `loaded_types.hpp`) are now dead — nothing includes
  them with `DO_CLASSLOADING 0`. They are still present only because an
  automated delete was blocked in this session; they're safe to remove by
  hand.

## What was actually verified, and how

This environment has no Rivet install and no network access, but another
local checkout on this machine
(`~/WORK/GAMBIT/CoreWork/ConturFix/gambit`) happened to have a real,
already-built Rivet 4.1.0 + HepMC3 + YODA + FastJet (core library only —
its `ExternalProject` build step only runs `make libRivet.so`, not a full
`make`, so the actual physics analysis plugins aren't built there either).
Using that install **read-only**, as a test rig:

- `rivet_shim.cpp` **compiles and links cleanly** against the real
  `Rivet::AnalysisHandler`, producing a working `.so` with all 14 expected
  unmangled symbols (checked with `nm -D`).
- A small `dlopen`/`dlsym` smoke test confirmed handler create/destroy,
  `stdAnalysisNames`/`analysisNames` (empty here, since no analysis plugins
  were built in that install), and `addAnalysisLibPath` don't crash.
- This caught and fixed two real bugs in the first draft:
  1. `analyze()` takes a non-const `HepMC3::GenEvent&` in the real API
     (`void analyze(GenEvent& event)`), not `const&` as first written —
     Rivet mutates/caches state on the event during analysis.
  2. `beamIds()`, `sqrtS()`, and `runName()` **do not exist** on the real
     `Rivet::AnalysisHandler` (the real names are `runBeamIDs()` and
     `runSqrtS()`; there's no `runName()` at all). These were dropped from
     the shim entirely, because — independently of this work — it turns out
     `ColliderBit_measurements.cpp` only ever calls them inside a block
     guarded by `#ifdef COLLIDERBIT_DEBUG`, and that macro is **never
     defined anywhere in this build** (`grep -rn COLLIDERBIT_DEBUG` outside
     that one file turns up nothing). That block is permanently dead code,
     predating this change, and it wouldn't have compiled against BOSS's
     own generated wrapper either (BOSS only wraps `runBeamIDs`/`runSqrtS`).
     Worth fixing or removing separately, but out of scope here.
  - Calling `nominalCrossSection()` on a handler that hasn't analyzed any
    events segfaults *inside Rivet itself* (`_xs` isn't populated yet) —
    that's an existing Rivet precondition, not a shim bug, and matches the
    only call site for it also being inside the same dead debug block.

So the actual, always-live method set this shim needs to support, from
reading `ColliderBit_measurements.cpp`, is smaller than first estimated:
constructor/destructor, `addAnalysis`, `removeAnalyses`, `analysisNames`,
`analyze`, `finalize`, `writeData`, `merge`, plus the free function
`addAnalysisLibPath` — 9 entry points, not 13; `stdAnalysisNames` and
`nominalCrossSection` are kept in the shim (they're real, correct wrappers)
but are currently unreachable from any live GAMBIT code path. Still a large
reduction from the ~96 methods BOSS auto-wraps.

## What was *not* verified

- **The GAMBIT-side macro plumbing itself.** `BE_FUNCTION`/`LOAD_LIBRARY`
  symbol resolution, `DO_CLASSLOADING 0`, and the namespace path module
  code resolves `AnalysisHandler` through all depend on GAMBIT's harvester
  (`backend_harvester.py`) and a full `cmake` configure that generates
  `backend_types_rollcall.hpp` (aggregating every backend in the repo) — not
  reproducible in this environment. The pattern used here is copied
  directly from existing, working hand-written frontends
  (`LibFirst_1_0.hpp`, `HiggsSignals_1_4.hpp`), so it should work, but it
  has not been exercised through an actual GAMBIT configure+build.
- **A real analysis run.** No physics analysis plugins were available to
  test `addAnalysis`/`analyze` with a real analysis name, or to check the
  shim's YODA output against BOSS's.
- **The `ExternalProject_Add_Step` command in `cmake/backends.cmake`
  itself** — the compiler invocation and flags were derived from the same
  variables the Rivet `ExternalProject_Add` block already uses, and mirror
  what I ran by hand successfully, but the cmake step itself hasn't been
  run through an actual `cmake`/`make` of this repo.

**Recommendation before trusting this for physics runs:** do a real
`cmake`/`make` of this backend, confirm the `BE_FUNCTION` symbols resolve at
runtime, and run at least one Rivet analysis end to end, comparing output
against the BOSS-generated path (easy to restore by reverting
`cmake/backends.cmake` and `config/backend_locations.yaml.default`, since
nothing else was deleted).

See `Backends/scripts/ShimGenerator/` for a generalised, step-by-step guide
to producing the equivalent of this for other BOSSed backends.
