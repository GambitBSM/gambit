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
- `Backends/patches/rivet/4.1.0/patch_rivet_4.1.0.dif`: this patch (applied
  to Rivet's own source tree, independent of the `BOSS_backend()` call)
  turned out to **also** bake in BOSS-specific content: it added
  `BOSS_*.cc` source files to `src/Core/Makefile.in`'s build rules (files
  BOSS itself used to generate and copy into Rivet's own source tree —
  removing the `BOSS_backend()` call meant those files never got created,
  so `make` failed with "No rule to make target 'BOSS_wrapperutils.cc'"),
  added GAMBIT backend-type headers to `include/Rivet/Makefile.in`'s
  install list, and added a `dummy(YODA::AnalysisObject*)` method to
  `AnalysisHandler.hh`/`.cc` purely to force BOSS to pull in a header it
  needed. All of that has been stripped from the patch file; what's left
  is only the genuinely BOSS-independent parts: the `libRivet.so:` Makefile
  target the cmake `BUILD_COMMAND` actually calls, the `analyses/Makefile.in`
  plugin-directory restriction, the `exit(1)` → `throw` conversions in
  `AnalysisHandler.cc` (so a bad analysis doesn't kill the whole GAMBIT
  scan), and the `configure` FastJet-flags fix. **Lesson for other
  backends:** check a backend's own patch file
  (`Backends/patches/<name>/<ver>/patch_*.dif`) for BOSS-specific content,
  not just the BOSS config and GAMBIT-side generated files — BOSS can
  patch the backend's own build system to compile files it generates
  itself, and removing the `BOSS_backend()` call without also cleaning up
  that patch leaves a build rule pointing at a file nothing produces
  anymore.
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

## Pythia shim: a second, much less favourable, example

`pythia_shim.cpp` and the prototype frontend header
`Backends/include/gambit/Backends/frontends/shims/Pythia_8_312_shim.hpp`
apply the same idea to the Pythia 8.312 backend. **PROTOTYPE / NOT WIRED
INTO THE BUILD** -- unlike the Rivet shim, no `cmake/backends.cmake` or
`config/backend_locations.yaml.default` change has been made for Pythia;
see Step 7 of the `ShimGenerator` README for why that's deliberately a
separate decision.

### Why this backend is a worse fit for the pattern than Rivet

Rivet's BOSS config wraps ~1 class, used in ColliderBit through a handful
of methods on one long-lived `AnalysisHandler` object. Pythia's BOSS
config (`Backends/scripts/BOSS/configs/pythia_8_312.py`) lists ~30
classes, and reading the actual call sites
(`ColliderBit/include/gambit/ColliderBit/colliders/Pythia8/Py8Collider.hpp`,
`Py8Utils.hpp`, `Py8EventConversions.hpp`,
`generateEventPy8Collider.hpp`) shows why: GAMBIT doesn't just call
methods on one `Pythia` object, it reads several of its **public data
members** directly (`_pythiaBase->settings`,
`_pythiaInstance->particleData`, `_pythiaInstance->event`,
`_pythiaInstance->info`, `_pythiaInstance->slhaInterface.slha`), and uses
`Pythia8::Event`/`Particle`/`Vec4` as real, by-value types all over
ColliderBit's event-conversion code (walking the event record,
re-reading momenta, copy-assigning whole events), not just handing one
opaque object to a single consumer. That is exactly the "poor candidate"
signature flagged in the `ShimGenerator` README's Step 2 and final
checklist item -- it was still done here (nine small wrapper classes,
~35 flat functions, versus Rivet's one class and ~14), but it's a
meaningfully bigger and more fragile surface than Rivet's, and a real
decision-maker should weigh that against just leaving BOSS in place for
this backend.

### What was found, method by method

The only GAMBIT module code that touches Pythia8 types directly is
`ColliderBit`'s Pythia8 collider path. Grepping it (Step 1) and reading
every call site gave this list, which `pythia_shim.cpp` implements:

- **`Pythia8::Pythia`**: both real constructors used in practice (xmldoc
  path; shared `Settings`+`ParticleData`), `readString`, `init`, `next`,
  `getSigmaMaxSum`, plus accessors for each public data member actually
  read (`settings`, `particleData`, `event`, `info`,
  `slhaInterface.slha`). `initSLHA` is explicitly `ditch`ed in the BOSS
  config and was skipped here too.
- **`Pythia8::Event`**: `clear`, `size`, `operator[]`, `daughterList(int)`
  (distinct from `Particle::daughterList()` below -- same method name,
  different class, different meaning: don't conflate them), and the one
  `list(...)` overload actually called (4-argument,
  `showScaleAndVertex, showMothersAndDaughters, precision, ostream&`,
  used only to dump a failed event to the debug log).
- **`Pythia8::Particle`**: `id`, `isFinal`, `isParton`, `isHadron`,
  `motherList`, `daughterList`, `p()` (see Vec4 below).
- **`Pythia8::Vec4`**: only ever immediately decomposed into
  `px/py/pz/e/mCalc()` by
  `ColliderBit/colliders/Pythia8/Py8Utils.hpp`'s `mk_p4`/`mk_pseudojet` --
  never stored, passed around, or operated on as a `Vec4` itself.
- **`Pythia8::Info`**: `sigmaGen`/`sigmaGen(int)`, `sigmaErr`/`sigmaErr(int)`,
  `code`, `codesHard`.
- **`Pythia8::SusyLesHouches`** (reached only via
  `Pythia::slhaInterface.slha`): `setSLHAea`.
- **`Pythia8::Settings`, `Pythia8::ParticleData`**: never dereferenced for
  any method anywhere in GAMBIT -- only ever read off one `Pythia`
  instance and passed straight into another one's constructor. These
  needed no methods at all, just an opaque pass-through handle (see
  "new challenges" below).
- **`Pythia8::GAMBIT_hepmc_writer`**: a GAMBIT-authored class, not part
  of Pythia's real API -- it's patched into Pythia's own installed
  `include/Pythia8/` directory by
  `Backends/patches/pythia/8.312/patch_pythia_8.312.dif` (same mechanism
  flagged for Rivet in Step 6.5), and was already in the BOSS config's
  `load_classes`. `init`, `write_event_HepMC2`, `write_event_HepMC3`,
  `convert_to_HepMC_event` are the only methods called
  (`generateEventPy8Collider.hpp`).
- **`Pythia8::UserHooks`**: in the BOSS `load_classes` list, and
  `Py8Collider.hpp`/`SetHooksClass.hpp` have templated plumbing for a
  `SetHooks<PythiaT, EventT>::SetupHook()` that would use it -- but the
  only `SetHooks` specialisation actually present in this tree is the
  generic template, which unconditionally returns `false` without
  touching `UserHooks` at all. No real subclass exists anywhere in
  `ColliderBit/`, so (per Step 1's "check every call site is actually
  reachable" warning) this was left out entirely, the same way Rivet's
  dead `COLLIDERBIT_DEBUG` block was.
- Every other class in the BOSS config's `load_classes`
  (`AlphaEM`, `AlphaStrong`, `BeamParticle`, `Couplings`, `CoupSM`,
  `CoupSUSY`, `DecayChannel`, `Hist`, `LHdecayChannel`, `LHdecayTable`,
  `Logger`, `Parm`, `ParticleDataEntry`, `ParticleDecays`,
  `PartonLevel`, `ResonanceDecays`, `ResonanceGmZ`, `ResonanceWidths`,
  `Rndm`, `SigmaProcess`, `SigmaTotal`, `SlowJet`) has **zero** hits
  anywhere under `ColliderBit/` outside the BOSS-generated frontend
  itself -- BOSS's `load_classes` is substantially broader than what's
  actually used today, exactly as the generator README's Step 1 warns.

### New challenges found here, not covered by the Rivet writeup

These are now also folded into `Backends/scripts/ShimGenerator/README.md`:

1. **Public data members, not just methods, can cross the boundary.**
   Rivet's `AnalysisHandler` is used purely through method calls; Pythia's
   is used partly through plain field reads (`pythia.settings`,
   `pythia.event`, ...). A flat shim can't expose a data member directly
   -- each one needs its own `pythia_get_<member>()` accessor, and the
   GAMBIT-side wrapper class needs to call that accessor once (typically
   at construction) and store the result as a public member of its own,
   so that `instance.member` still works unchanged at call sites.
2. **Opaque handles sometimes need zero methods.** `Settings` and
   `ParticleData` are read off one `Pythia` instance and passed straight
   into another's constructor -- nothing in GAMBIT ever calls a method on
   them. Don't reflexively wrap methods nobody uses just because BOSS's
   `load_classes` mentions the class; here the entire "wrapper" is a
   `void*` with a type name on it.
3. **Some backend types need real value semantics, not just a handle.**
   `Event` is default-constructed, cleared, and copy-assigned by GAMBIT
   module code as an ordinary C++ value. The shim can't give the wrapper
   class free value semantics the way the real backend's own C++ class
   does -- it needs explicit `create`/`destroy`/`assign` entry points, and
   the GAMBIT-side wrapper must implement its own copy constructor and
   `operator=` by calling the `assign` entry point, rather than relying
   on a compiler-generated member-wise copy (which would just copy the
   `void*` handle, aliasing two "different" Events onto the same backend
   object).
4. **The same wrapper class can be owning or non-owning depending on
   where it came from.** A freshly-`new`'d `Event` (via the wrapper's
   default constructor) owns its handle and must destroy it; an `Event`
   reached via `Pythia::event` is a reference into the real `Pythia`
   object's own storage, and destroying it would be a double-free when
   the real `Pythia` is later destroyed. The wrapper class needs an
   internal owns-this-handle flag (or an equivalent private
   non-owning-constructor tag) to tell the two cases apart; it is not
   safe to assume every instance of a wrapper class should delete its
   handle in its destructor.
5. **Flatten a backend-internal compound return type when only its
   fields are read.** `Particle::p()` returns a `Vec4`; nothing in
   GAMBIT ever stores or operates on that `Vec4` except immediately
   reading `px/py/pz/e/mCalc()` off it. Rather than giving `Vec4` its own
   handle type and four more `BE_FUNCTION`s, the shim flattens it into a
   single call returning the four plain doubles (plus one more for
   `mCalc()`, which needs the real backend's own Vec4 arithmetic rather
   than a raw field read), and the GAMBIT-side `Vec4` wrapper is a
   trivial, header-only value type built from those doubles -- no
   `BE_FUNCTION` round-trip needed to read it back. This is worth
   checking for *any* method that returns a backend-internal compound
   type: if nothing downstream keeps the object around or mutates it,
   flattening beats adding another handle-based wrapper class.
6. **Watch for same-named methods on different classes at different
   scopes.** Both `Pythia8::Event::daughterList(int)` and
   `Pythia8::Particle::daughterList()` exist, with different meanings
   (the former walks the event record from an index; the latter reads
   one particle's own recorded daughters). Getting the call site's
   receiver type right matters when naming/implementing the
   corresponding shim functions -- `pythia_event_daughter_list` and
   `pythia_particle_daughter_list` are deliberately not merged or
   confused with one another despite the near-identical real API names.
7. **A backend's own patched-in, GAMBIT-authored classes are in scope
   too, and may be easy to miss.** `GAMBIT_hepmc_writer` isn't part of
   Pythia's real API at all -- it's a GAMBIT-authored header injected into
   Pythia's own install tree by the backend's patch file (same mechanism
   flagged in Step 6.5 for BOSS-generated `.cc` files, but here the
   injected file is itself hand-written C++ GAMBIT wants to keep calling,
   not a BOSS artifact to strip out). Check the BOSS config's
   `load_classes` for class names that don't appear in the backend's own
   upstream source at all -- that's the signal to go look at the patch
   file for where they come from, since they need to stay in the shim's
   scope exactly like any other wrapped class.

### What was *not* verified

Same caveats as the Rivet shim, and then some: this environment has
neither a Pythia install nor network access, and (unlike Rivet) no other
local checkout on this machine had Pythia 8.312 already built, so
`pythia_shim.cpp` has **not** been compiled against real Pythia8 headers
at all. Every method name, signature, and constness used here was taken
from the BOSS-generated wrapper/abstract header pairs already checked
into this tree under
`Backends/include/gambit/Backends/backend_types/Pythia_8_312/` (e.g.
`wrapper_Pythia_decl.h`, `wrapper_Event_decl.h`, `wrapper_Particle_decl.h`,
`wrapper_Vec4_decl.h`, `wrapper_Info_decl.h`,
`wrapper_GAMBIT_hepmc_writer_decl.h`) -- themselves the output of a real
castxml run against the real headers at some point in the past, so this
is a better starting point than guessing from documentation, but it is
**not** the same as compiling against the real thing the way the Rivet
shim was. Treat every signature here as unverified until it's actually
compiled against Pythia 8.312's real headers, exactly as Step 6
recommends.
