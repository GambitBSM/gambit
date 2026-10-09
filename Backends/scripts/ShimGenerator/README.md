# Shim-based alternative to BOSS: instructions for generating a new one

## Context (read this before doing anything)

GAMBIT normally connects to C++ backends via **BOSS**
(`Backends/scripts/BOSS/`), which parses a backend's real headers (via
castxml/gccxml) and auto-generates abstract/wrapper C++ classes exposing the
*entire* parsed API. This is fragile: castxml chokes on modern C++ features,
and because it wraps everything in the header rather than just what GAMBIT
calls, any change anywhere in the real header — even to a method nobody
uses — can break the build.

The alternative sketched out here is a **hand-written, flat, `extern "C"`
shim**: a small `.cpp` file, compiled directly against the real backend
headers, that exports only the specific functions/methods GAMBIT modules
actually call, under plain unmangled C-style names. GAMBIT's existing
`dlopen`/`dlsym`-based backend-loading machinery (`BE_FUNCTION`,
`LOAD_LIBRARY`) doesn't care whether those symbols came from BOSS or were
written by hand — so the shim slots into the same loading mechanism, just
with a hand-maintained, much smaller surface.

A full worked example for the Rivet backend lives in
`Backends/src/frontends/shims/` with its own `README.md` — **read that
first**, it shows the actual pattern end to end (shim `.cpp` +
GAMBIT-side wrapper header) with real code, and explains a thread-safety
hazard that shims introduce and BOSS doesn't (see step 5 below).

This is only worth doing for backends where BOSS is genuinely painful — a
backend with a small, stable API that BOSS already handles cleanly doesn't
need this.

## Step 1 — Find out what GAMBIT actually calls

Don't wrap the whole backend API. Find the *actual* call sites and wrap
only those.

```
grep -rn "Dep::<BackendCapability>\|Pipes::.*<BackendName>\|BACKEND_REQ.*<BackendName>" --include=*.cpp --include=*.hpp <RelevantBitDirectory>/
```

For a backend wrapping a single class (like Rivet's `AnalysisHandler`), grep
module source for the class name directly and read every call site:

```
grep -rn "<ClassName>" <RelevantBitDirectory>/src <RelevantBitDirectory>/include
```

Write down the exact list of methods/functions called, with their argument
and return types as used at the call site (not the full overload set from
the header — just what's actually invoked). This list is the entire scope
of the shim.

**Check every call site is actually reachable before trusting it.** When
doing this for Rivet, three of the "called" methods
(`beamIds`/`sqrtS`/`runName`) turned out to be inside a block guarded by
`#ifdef COLLIDERBIT_DEBUG` — a macro never defined anywhere in the build
(`grep -rn COLLIDERBIT_DEBUG` outside that one file was empty). That block
was permanently dead code, and the method names it called didn't even
exist on the real class. Don't assume every grep hit is live: check whether
it sits behind an `#ifdef` for a macro that's actually ever defined, and
grep the surrounding code for `#ifdef`/`#endif` boundaries. For Rivet, once
the dead code was excluded, the real entry-point count dropped from 13 to
9, against ~96 BOSS-generated methods — expect a similarly large reduction
for most backends, but get the *real* count right rather than the first
grep's count.

Also check the existing BOSS config
(`Backends/scripts/BOSS/configs/<backend>_<version>.py`) for `load_classes`,
`load_functions`, and `ditch` — this tells you what BOSS was asked to wrap
and what it was told to skip, which is a useful cross-check but **not** a
substitute for grepping actual call sites: BOSS's `load_classes` may be
broader than what's actually used today.

## Step 2 — Note everything that crosses the boundary that isn't a plain type

For each call you found, identify arguments/return values that aren't
`int`/`double`/`bool`/C-strings:

- **`std::string`, `std::vector<T>`, etc.** — need an explicit convention
  for crossing an `extern "C"` boundary (see step 5).
- **Other backend types passed in from elsewhere in GAMBIT** (e.g. Rivet's
  `analyze()` takes a `HepMC3::GenEvent&`, which is produced by the Pythia
  frontend). These can cross as raw pointers *only* if every side that
  touches them is compiled with the same compiler/stdlib/ABI — true for
  GAMBIT's own contrib libraries, but check this assumption explicitly for
  anything unusual.
- **Objects whose lifetime GAMBIT doesn't fully control** — if the backend
  hands back a pointer/reference into its own internal storage (rather than
  a value GAMBIT owns), decide who is responsible for its lifetime and make
  that explicit in the shim, rather than relying on implicit C++ RAII the
  way the BOSS-generated wrapper does.

If what you find here is extensive — if most of what crosses the boundary
is complex, backend-internal types with unclear ownership — that's a signal
this particular backend is a poor candidate for a shim; BOSS's full
auto-wrapping may genuinely be less work for that one.

## Step 3 — Write the shim `.cpp`

One `extern "C"` function per entry point from step 1. Pattern (see
`Backends/src/frontends/shims/rivet_shim.cpp` for a full real example):

- Opaque handles: `void* create()` / `void destroy(void*)` wrapping
  `new`/`delete` of the real backend object.
- Plain-typed methods: `static_cast` the handle back to the real type and
  call through directly.
- Anything returning a string or a collection: see step 5 — do **not** use
  a shared or `static` buffer.

This file is still ordinary C++ — `extern "C"` only disables name mangling,
it does not restrict you to C types. You can and should pass real C++
pointer/reference types for arguments that are shared with other GAMBIT
frontends (per step 2), you just can't *return* a C++ object by value
across the boundary.

## Step 4 — Write the GAMBIT-side wrapper header

Write a C++ class, on the GAMBIT side, with the exact method
names/signatures that the existing call sites already use (from step 1),
implemented by `dlsym`-ing and calling the shim's flat functions. The goal
is that module code needs **zero changes** — the wrapper class is a
drop-in replacement for the type the BOSS-generated frontend currently
provides.

Don't hand-roll `dlopen`/`dlsym` — reuse GAMBIT's existing `LOAD_LIBRARY`
and `BE_FUNCTION` macros (`Backends/include/gambit/Backends/frontend_macros.hpp`),
exactly as the hand-written (non-BOSS) `LibFirst_1_0.hpp` and
`HiggsSignals_1_4.hpp` frontends already do, and as the real
`Backends/include/gambit/Backends/frontends/Rivet_4_1_0.hpp` now does.
`BE_FUNCTION` already does symbol resolution against a list of candidate
names via `dlsym`, and doesn't care whether the symbol was produced by
BOSS or written by hand — just give it the shim's plain, unmangled function
name as the `SYMBOLNAME` argument (no `"__BOSS_"`-style mangled candidates
needed, since the shim exports `extern "C"` names directly) and declare the
matching `void*`-handle-based signature. Set
`DO_CLASSLOADING 0` in the backend's `identification.hpp` if it was
previously 1 — a flat-function shim doesn't need BOSS's factory-based
classloading at all.

## Step 5 — Handle the thread-safety hazard explicitly

This is the main new failure mode a shim introduces that BOSS's generated
code doesn't have. A real C++ method returning e.g. `std::vector<std::string>`
constructs its return value fresh on the caller's stack every call — no
shared state, so it's safe to call from multiple threads on different
object instances without thinking about it.

An `extern "C"` function can't return a `std::string`/`std::vector` that
way. The *wrong* shortcut is a `static` (or even naive `thread_local` reused
across unrelated calls) buffer holding the string before handing back a
`const char*` into it — that buffer is shared process-wide, so two threads
calling the same shim function concurrently (even on two different backend
object instances) race on it, giving garbled or UB reads. This is
realistic for GAMBIT specifically because ColliderBit-style code
(`anahandlers[omp_get_thread_num()]->...`) calls backend methods from
OpenMP-parallel regions.

**Always use the caller-owned-buffer convention** for anything
variable-length: `void get_foo(handle, int index, char* buf, int buflen)`,
where `buf` is a stack buffer the caller passed in. See
`rivet_handler_analysis_name` in `rivet_shim.cpp` for the pattern. Check
every string/collection-returning function in your shim against this before
considering it done.

## Step 6 — Verify against a real install if there is any way to get one

Don't trust a shim that only "looks right" — method names, signatures, and
constness that look plausible from reading a header can still be wrong
(see the Rivet example: `analyze()`'s real signature takes a non-const
reference, and `beamIds`/`sqrtS`/`runName` don't exist on the real class at
all — both were only caught by actually compiling against the real
headers). If the real backend isn't installed in your environment:

- Check whether another local checkout of the same repo (a different
  branch, a colleague's machine, a CI artifact, an old build directory) has
  the backend already built. It doesn't need a working GAMBIT build at all
  — you only need its installed headers/libs to compile and link the shim
  `.cpp` directly with a one-off `g++ -shared` command, and ideally to
  `dlopen` the result from a tiny standalone test program and call each
  function once (lifecycle: create, call the real entry points with
  harmless/empty inputs, destroy — look for crashes, not correctness).
- Use `nm -D --defined-only your_shim.so` to confirm every expected symbol
  is present, unmangled, and exported.
- If genuinely nothing is available, say so explicitly rather than
  presenting an unverified shim as equivalent to BOSS's output — BOSS's
  castxml step at least parses the real header, so a hand-written shim that
  has never seen the real header is a strictly weaker guarantee.

## Step 6.5 — Check the backend's own patch file for BOSS content too

Don't assume BOSS only touches GAMBIT-side files
(`Backends/include/.../frontends/`, `backend_types/`). BOSS can also run as
part of the backend's own build and physically copy generated `.cc`/`.hh`
files into the backend's source tree (check the BOSS config's
`src_files_to`/`header_files_to` variables), and the backend's own
`Backends/patches/<name>/<ver>/patch_*.dif` can bake in Makefile build
rules for those generated files, or dummy methods purely to force BOSS to
pull in a type's header. For Rivet, disabling `BOSS_backend()` without
cleaning up `patch_rivet_4.1.0.dif` left a hard-coded Makefile rule for
`BOSS_wrapperutils.cc` — a file nothing produces any more — causing a "No
rule to make target" failure deep in the Rivet build, well after the shim
itself had already compiled fine standalone. `grep -n BOSS` the backend's
patch file and the backend's own installed source tree (if already
downloaded) before declaring the removal of BOSS complete, and strip any
hunks that reference BOSS-generated filenames, keeping everything else
(other patches in the same file are often for unrelated reasons, like
Rivet's own `exit(1)`→`throw` and FastJet-flags fixes, and must stay).

## Step 7 — Decide on and document build integration separately

Writing the shim and wrapper header doesn't require touching
`cmake/backends.cmake`, and you generally shouldn't do so in the same pass
as writing the files unless explicitly asked — it's a separate,
higher-blast-radius decision (changes real build/CI behavior for a backend
you likely can't fully compile-test without the real backend installed).
Treat "write the shim" and "wire it into the live build, replacing the
BOSS-generated frontend" as two separate pieces of work, and flag the
integration step explicitly to whoever you're doing this for rather than
doing it unprompted. `Backends/src/frontends/shims/README.md` documents
exactly what was changed and verified for the Rivet integration
(`cmake/backends.cmake`, `config/backend_locations.yaml.default`,
`identification.hpp`, the frontend header) and — just as importantly —
what was *not* verified, since the GAMBIT-side macro plumbing requires a
full `cmake` configure that pulls in every other backend in the repo.
State that boundary explicitly rather than implying full confidence.

## Checklist

- [ ] Grepped real call sites; have the exact, minimal method/function list
- [ ] Identified every non-plain-type argument/return value and how it
      crosses the boundary (step 2)
- [ ] Shim `.cpp` written, one `extern "C"` function per entry point
- [ ] Every string/collection-returning function uses a caller-owned buffer,
      not a shared/static temporary
- [ ] GAMBIT-side wrapper class matches existing call sites' method
      names/signatures exactly — module code needs no changes
- [ ] Symbol loading uses `BE_FUNCTION`/`LOAD_LIBRARY`, not a hand-rolled
      `dlopen`/`dlsym` loader; `DO_CLASSLOADING` set to 0
- [ ] Compiled (and ideally linked + smoke-tested) against a real install
      of the backend, from this environment or any other reachable one —
      or explicitly flagged as unverified if truly none was available
- [ ] Build-system integration explicitly called out as a separate
      decision, flagged to whoever you're doing this for — not silently
      wired into `cmake/backends.cmake` unless that was explicitly asked for
- [ ] Noted whether this backend is actually a good candidate (small
      fraction of the real API used, few complex cross-boundary types) —
      if not, say so instead of forcing the pattern
