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
of the shim. For Rivet this was 13 entry points out of ~96 BOSS-generated
ones; expect a similarly large reduction for most backends.

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

For symbol loading, don't hand-roll `dlopen`/`dlsym` the way the Rivet
prototype's `ShimLibrary` class does (that was written to be readable
standalone) — reuse GAMBIT's existing `LOAD_LIBRARY` and `BE_FUNCTION`
macros (`Backends/include/gambit/Backends/frontend_macros.hpp`). They
already do symbol resolution against a list of candidate mangled names via
`dlsym`, and don't care whether the symbol was produced by BOSS or written
by hand — only the `SYMBOLNAME` list and the function signature need to
match what you put in the shim.

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

## Step 6 — Decide on and document build integration separately

Writing the shim and wrapper header doesn't require touching
`cmake/backends.cmake`, and you generally shouldn't do so in the same pass
as writing the files — it's a separate, higher-blast-radius decision
(changes real build/CI behavior for a backend you likely can't
compile-test without the real backend installed). Treat "write the
prototype" and "wire it into the live build, replacing the BOSS-generated
frontend" as two separate pieces of work, and flag the integration step
explicitly to whoever you're doing this for rather than doing it
unprompted. See the "What a real integration would still need" section of
`Backends/src/frontends/shims/README.md` for the concrete list of
remaining steps (shim build target, reusing `BE_FUNCTION` for symbol
loading, matching the existing namespace/typedef that module code expects,
and actually compiling/testing against the real backend).

## Checklist

- [ ] Grepped real call sites; have the exact, minimal method/function list
- [ ] Identified every non-plain-type argument/return value and how it
      crosses the boundary (step 2)
- [ ] Shim `.cpp` written, one `extern "C"` function per entry point
- [ ] Every string/collection-returning function uses a caller-owned buffer,
      not a shared/static temporary
- [ ] GAMBIT-side wrapper class matches existing call sites' method
      names/signatures exactly — module code needs no changes
- [ ] Symbol loading uses (or is flagged as needing to switch to)
      `BE_FUNCTION`/`LOAD_LIBRARY`, not a hand-rolled loader
- [ ] Build-system integration explicitly called out as a separate,
      unstarted step — not silently wired into `cmake/backends.cmake`
- [ ] Noted whether this backend is actually a good candidate (small
      fraction of the real API used, few complex cross-boundary types) —
      if not, say so instead of forcing the pattern
