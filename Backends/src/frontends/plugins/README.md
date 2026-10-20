# Backend plugins: Pythia and Rivet

This directory holds the sources of the *plugin libraries* through which
GAMBIT uses Pythia and Rivet. A plugin is a small library, compiled against
the backend as part of the backend's own build, that implements an abstract
C++ interface defined by ColliderBit. GAMBIT loads it as the backend.

## The idea

For a C++ backend, the usual question is how GAMBIT can call the backend's
C++ API without being compiled against the backend's headers. BOSS answers
it by generating wrapper classes for the backend's whole API. The plugins
here answer it the other way round: GAMBIT defines the interface it needs,
as an abstract class, and a library compiled with the backend implements
it.

- `ColliderBit/include/gambit/ColliderBit/colliders/BaseCollider.hpp`
  defines `BaseCollider`, everything ColliderBit needs from a
  hard-scattering event generator: initialise for a point, generate an
  event, hand the latest event over as a generator-neutral `EventRecord`
  (`colliders/EventRecord.hpp`) or as a `HepMC3::GenEvent`, report cross
  sections and process codes, write HepMC files, print the event record.
- `ColliderBit/include/gambit/ColliderBit/AnalysisHandler.hpp` defines
  `AnalysisHandler`, everything ColliderBit needs from a Rivet-style
  analysis handler: add and remove analyses, analyse an event, finalise,
  write YODA output to a file or stream, merge handlers.

`pythia_plugin.cpp` implements `BaseCollider` on top of Pythia 8, and
`rivet_plugin.cpp` implements `AnalysisHandler` on top of Rivet. Each
exports a few `extern "C"` functions: a factory that returns a new instance
through a pointer to the abstract class, a function returning the version
of the interface the plugin was built against, and for Rivet a function to
register the analysis directory. GAMBIT's frontend headers
(`Backends/include/gambit/Backends/frontends/Pythia_8_312.hpp` and
`Rivet_4_1_0.hpp`) declare just these functions with `BE_FUNCTION`, and
ColliderBit's module functions obtain their generator or handler through
an ordinary `BACKEND_REQ`. All other calls are virtual calls on the
returned object.

Nothing in GAMBIT includes a Pythia or Rivet header, so GAMBIT and
ColliderBit build without either backend being present, and the dependency
resolver disables the functions that need them when they are missing. The
plugins are compiled as a `build_plugin` step of the backend's
`ExternalProject` in `cmake/backends.cmake`, with the same compiler flags
as the backend itself and with ColliderBit's include path for the
interface headers.

**Where the physics stops being the generator's business.** A generator
plugin fills an `EventRecord`: for every entry of its native event record,
the PDG code, whether the particle is final, a parton or a hadron (by the
generator's own definitions), the four-momentum and generated mass, and
the indices of its mothers and daughters. That is all. What a prompt
lepton or photon is, which particles enter the jet clustering, how b, c,
tau, W, Z and Higgs candidates are identified, the acceptance cut and the
missing momentum are defined once, in
`ColliderBit/src/colliders/EventConversion.cpp`, and applied to every
generator's record alike. ColliderBit fills the same record from HepMC
events, so HepMC input and generator plugins share one conversion.

## Rules

**One toolchain.** A C++ interface across a `dlopen` boundary requires both
sides to be built with the same compiler and standard library. The
`build_plugin` steps use the backend's flags, which are derived from the
flags used for GAMBIT, so this holds by construction. It is the same
assumption GAMBIT already makes for its contrib libraries.

**Versioned interfaces.** Any change to `BaseCollider` or `AnalysisHandler`
changes the class layout and must be accompanied by a bump of
`COLLIDERBIT_COLLIDER_INTERFACE_VERSION` or
`COLLIDERBIT_ANALYSIS_HANDLER_INTERFACE_VERSION`. The backend init
functions (`Backends/src/frontends/Pythia_8_312.cpp`, `Rivet_4_1_0.cpp`)
compare the version the plugin reports with the one GAMBIT was compiled
with at scan start, and raise a backend error on a mismatch, so a stale
plugin cannot run.

**No exceptions across the boundary.** Every interface method that can
fail returns `false` and leaves a message for `last_error()`. The plugins
catch everything at their boundary; GAMBIT raises its own errors or
invalidates the point as appropriate.

**Interface headers stay standalone.** `BaseCollider.hpp`,
`EventRecord.hpp` and `AnalysisHandler.hpp` are compiled by GAMBIT and by
the plugins, so they may include only the standard library and the GAMBIT
contrib headers SLHAea and HepMC3. The GAMBIT-side handle types live in
`colliders/ColliderHandle.hpp`, which plugins never see.

**Ownership.** A `BaseCollider` is created once per thread, on first use,
and kept for the rest of the run; GAMBIT holds it in a `ColliderHandle`
(the type of the `HardScatteringSim` capability), together with the
per-collider conversion settings from the yaml file. Analysis handlers are
created per collider and thread and destroyed through their virtual
destructor. The generated event stays inside the generator; the
`HardScatteringEvent` capability of type `GeneratorEvent` is a handle to
it, through which the `HEPUtils::Event` and `HepMC3::GenEvent` versions
of the same event are produced.

## Adding another generator or analysis tool

Implement the interface in a new plugin source here, export the same
`extern "C"` functions under new names, add a `build_plugin` step to the
backend's section of `cmake/backends.cmake`, write a frontend header with
the corresponding `BE_FUNCTION` lines (with the same capability names
`create_collider` or `create_analysis_handler`, so that existing module
functions can use the new backend through yaml rules), and point
`config/backend_locations.yaml.default` at the plugin library. No
ColliderBit code needs to change.

## Verification status

Checked in October 2026 on Linux with g++ 11, in a ColliderBit-only build
(`cmake -DBits=ColliderBit`):

- `./gambit backends` reports Pythia 8.312 and Rivet 4.1.0 as OK through
  their plugin libraries.
- `ColliderBit/examples/ColliderBit_SLHA_file_model.yaml` runs to
  completion with 2000 and with 10000 Pythia events, giving nonzero signal
  yields and a likelihood, and writes HepMC3 event files when
  `drop_HepMC3_file` is set.
- The same example extended with `Rivet_measurements` (all 13 TeV analyses
  via Contur) and `LHC_measurements_LogLike` runs to completion: Rivet
  analyses the events through the plugin, writes YODA output to a file and
  to the in-memory stream, and Contur returns a likelihood.
- A Pythia plugin deliberately built against a different interface version
  is rejected at startup with a fatal error naming both versions.
- Equivalence with the BOSS-based frontends: the same example (2000 events,
  fixed `rng: seed`, `OMP_NUM_THREADS=1`) was run with this code and with a
  build of the last BOSS-based master commit against the same Pythia and
  Rivet versions. All 16 signal-region yields, the combined log-likelihood
  and the HepMC3 event file (byte for byte, after the event-numbering and
  file-closing fixes described below) are identical. With `Rivet_measurements`
  (all 13 TeV analyses) and Contur added, the Contur log-likelihoods and the
  YODA file (4357 objects) are also byte-identical between the two builds.
- HepMC input path: for 2000 generated events, the unsmeared `HEPUtils::Event`
  obtained from the Pythia record and the one obtained by converting the
  event to HepMC3 (in memory, or written to ASCII and read back) and filling
  the record with `fillEventRecord` agree exactly in all particles, jets and
  tags; the missing momentum agrees to 3e-14 GeV (summation order). HepMC
  carries no copy of Pythia's mother/daughter indices, so those lists differ
  for a few percent of intermediate entries, without any effect on the
  b/c/tau/W/Z/h candidates or the prompt-lepton classification.
- `ColliderBit/examples/solo.cpp` (ColliderBit Solo) runs on the HepMC3 file
  written by the Pythia path. Solo was broken on master independently of this
  work: it resolved the analysis containers' `TotalCrossSection` dependency
  with the `InitialTotalCrossSection` functor; it now uses `getYAMLCrossSection`.

Two defects found by these tests were fixed in the Pythia plugin: HepMC event
numbers are assigned per distinct generated event (converting the same event
for Rivet and for a HepMC file no longer skips numbers), and HepMC output
files are closed through `BaseCollider::close_HepMC_files()` at program exit
so that they end with the HepMC footer.

## Not covered

- GUM's templates (`gum/Templates/ColliderBit_model.hpp` and `.cpp`) still
  emit the old `NEEDS_CLASSES_FROM(Pythia_@MODEL@, default)` lines and the
  old macro arguments. Models generated with GUM need the same treatment as
  `ColliderBit/include/gambit/ColliderBit/models/SUSY.hpp` received here.
- The BOSS configurations `Backends/scripts/BOSS/configs/pythia_8_312.py`
  and `rivet_4_1_0.py`, and the `GAMBIT_hepmc_writer` class in the Pythia
  patch, are no longer used by the build.
