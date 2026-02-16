# VRJet Integration Update (CBS / ColliderBit)

Date: 2026-02-16

## 1. Goal and Scope
This note documents the VR jet (Variable-R jet) integration for CBS/ColliderBit, with a file-by-file description of what was changed and why.

Primary goals:
1. Allow users to declare VR jet collections in YAML.
2. Reconstruct VR jets in the event conversion path (at least for HepMC input used by CBS).
3. Expose VR jets to analyses via `event->vrjets("<collection_name>")`.
4. Ensure FastJet/FJContrib build/link configuration includes the required VariableR components.

---

## 2. User-Facing YAML Interface

VR jets are configured through an optional `VRJet_collections` block under `settings`.

Example:

```yaml
settings:
  jet_collections:
    antikt_R04:
      algorithm: "antikt"
      R: 0.4
      recombination_scheme: "E_scheme"
      strategy: "Best"

  jet_collection_taus: antikt_R04

  VRJet_collections:
    VRTrackJets:
      rho: 30.0
      Rmin: 0.02
      Rmax: 0.40
      pt_min: 5.0
```

Semantics:
1. `VRJet_collections` is optional.
2. If absent, VR jet reconstruction is disabled.
3. Each collection is keyed by name (for example `VRTrackJets`), and analyses access it by this key.
4. Per-collection parameters are `rho`, `Rmin`, `Rmax`, `pt_min`.

---

## 3. End-to-End Data Flow

The current intended flow is:

1. YAML `settings.VRJet_collections` is parsed in `solo`.
2. The node is passed to event conversion modules via module options.
3. Event conversion builds VR jets with FastJet VariableR plugin.
4. VR jets are stored in `HEPUtils::Event` under the configured key.
5. Analyses retrieve VR jets with `event->vrjets("<key>")`.

Relevant analysis usage examples:
1. `ColliderBit/src/analyses/Analysis_ATLAS_EXOT_2019_04.cpp` uses `event->vrjets("VRTrackJets")`.
2. `ColliderBit/src/analyses/Analysis_ATLAS_EXOT_2019_07.cpp` uses `event->vrjets("VRTrackJets")`.

---

## 4. Detailed File-by-File Changes

## 4.1 Core data structures

File: `ColliderBit/include/gambit/ColliderBit/Utils.hpp`

What was added:
1. `vrjet_collection_settings` struct.
2. Fields: `key`, `rho`, `Rmin`, `Rmax`, `pt_min`.
3. Inline documentation of expected YAML shape and defaults.

Why:
1. Provide a typed container for VR jet collection configuration shared across converters.

---

## 4.2 Collider state container

File: `ColliderBit/include/gambit/ColliderBit/colliders/BaseCollider.hpp`

What was added/used:
1. `std::vector<vrjet_collection_settings> all_vrjet_collection_settings`.
2. `bool use_vrjets`.
3. Constructor initializes VR-related fields (`all_vrjet_collection_settings({})`, `use_vrjets(false)`).

Why:
1. Keep VR jet configuration in collider-level runtime state.

---

## 4.3 Pythia-side option parsing

File: `ColliderBit/include/gambit/ColliderBit/getPy8Collider.hpp`

What was added:
1. Optional parsing of `VRJet_collections` from collider run options.
2. Empty-collection validation:
   - If `VRJet_collections` exists but has no entries, an explicit error is raised.
3. Populate `result.all_vrjet_collection_settings` with `{key, rho, Rmin, Rmax, pt_min}`.
4. Set `result.use_vrjets = true` only when collections are provided and valid.

Why:
1. Keep YAML-driven VR configuration consistent across ColliderBit execution modes.

---

## 4.4 Event conversion (where VR jets are built)

File: `ColliderBit/include/gambit/ColliderBit/colliders/Pythia8/Py8EventConversions.hpp`

What was changed:
1. Added include:
   - `#include "fastjet/contrib/VariableR.hh"`
2. Added type alias:
   - `using vr_jet_collection_settings = std::vector<vrjet_collection_settings>;`
3. Added overload strategy for `convertParticleEvent`:
   - Backward-compatible overload without VR arguments (builds no VR jets).
   - Extended overload with explicit `vr_collections`.
4. Implemented VR jet reconstruction block:
   - Loops over configured collections.
   - Builds `fastjet::contrib::VariableRPlugin` with `(rho, Rmin, Rmax, AKTLIKE)`.
   - Clusters `jetparticles`, applies `inclusive_jets(pt_min)`, sorts by `pT`.
   - Computes effective radius `Reff = clamp(rho/pt, Rmin, Rmax)` for flavor matching.
   - Builds tag map and stores jets via:
     - `result.add_vrjet(new HEPUtils::Jet(...), vr_key)`.

Why:
1. This is the central implementation that actually creates VR jets and makes them available to analyses.

---

## 4.5 HepMC input path (CBS main path)

File: `ColliderBit/src/getHepMCEvent.cpp`

What was added:
1. Helper `read_vrjet_collections_settings(...)`.
2. Optional parse of `VRJet_collections` from run options.
3. Pass parsed VR collection settings into conversion call:
   - `convertParticleEvent(..., vr_collections)` for both:
     - `getHepMCEvent_HEPUtils`
     - `convertHepMCEvent_HEPUtils`

Why:
1. Ensure CBS HepMC runs can reconstruct VR jets from YAML without changing analysis code.

Behavior:
1. If `VRJet_collections` is absent, `vr_collections` remains empty and no VR jets are built.

---

## 4.6 LHE input path

Files:
1. `ColliderBit/src/getLHEvent.cpp`
2. `ColliderBit/include/gambit/ColliderBit/lhef2heputils.hpp`
3. `ColliderBit/src/lhef2heputils.cpp`

What was added:
1. `getLHEvent.cpp` parses optional `VRJet_collections` and forwards them to an extended `get_HEPUtils_event` overload.
2. `lhef2heputils.hpp/.cpp` define that extended overload signature.

Current implementation status:
1. In `lhef2heputils.cpp`, the VR arguments are currently accepted but intentionally ignored.
2. The extended overload delegates to the existing non-VR implementation.

Why:
1. Keeps API compatibility and call chain ready.
2. Full LHE-side VR reconstruction is not yet implemented.

---

## 4.7 CBS standalone (`solo`) parsing and option forwarding

File: `ColliderBit/examples/solo.cpp`

What was added:
1. Optional read:
   - `settings.hasKey("VRJet_collections")`
2. If present, pass the YAML node to:
   - `getEvent.setOption<YAML::Node>("VRJet_collections", ...)`
   - `convertEvent.setOption<YAML::Node>("VRJet_collections", ...)`

Why:
1. Connect CBS YAML input directly to event conversion modules without touching analysis internals.

---

## 4.8 CBS process/batch mode behavior

File: `ColliderBit/examples/solo_batch.cpp`

Relevant behavior:
1. Batch jobs are created by cloning `infile["settings"]`:
   - `YAML::Clone(prepared_input.infile["settings"])`
2. Batch preprocessing removes only specific keys (`processes`, xsec/event file/output controls), and does not remove `VRJet_collections`.

Why:
1. VR jet settings survive per-file temporary YAML generation in process mode.
2. Multi-file/multi-process CBS runs can keep VR jet configuration unchanged.

---

## 4.9 YAML templates/examples updated

Files:
1. `CBS_yaml/CBS_complete_template.yaml`
2. `CBS_yaml/ATLAS_EXOT_2019_04_processes.yaml`

What was added:
1. Explicit `VRJet_collections` examples with `VRTrackJets` and typical parameters.

Why:
1. Provide working input examples for analyses that call `event->vrjets("VRTrackJets")`.

---

## 4.10 Build and link changes for VariableR availability

Files:
1. `cmake/contrib.cmake`
2. `cmake/executables.cmake`
3. `cmake/utilities.cmake`
4. `cmake/backends.cmake`

What changed:
1. `contrib.cmake`:
   - Include dirs include `.../fjcontrib-1.049/VariableR` and `EnergyCorrelator`.
   - `fjcontrib_LDFLAGS` includes `-lVariableR` and `-lEnergyCorrelator`.
2. `executables.cmake`:
   - Adds `fjcontrib_LDFLAGS` into executable linker flags when available.
3. `utilities.cmake`:
   - Standalone executables using ColliderBit include `fastjet` + `fjcontrib` link flags.
4. `backends.cmake`:
   - Uses `fjcontrib` version `1.049`.
   - Reuse logic can make backend dependencies use contrib-provided fastjet/fjcontrib to avoid duplicate builds.

Why:
1. VRjet code path depends on FJContrib VariableR library being present and linked.

---

## 5. Functional Behavior Summary

Supported now:
1. HepMC -> HEPUtils conversion with VR jet reconstruction from YAML-defined collections.
2. Analyses can consume VR jets by collection key.
3. CBS process mode preserves VR settings when generating temporary per-file YAML jobs.

Important caveats:
1. LHE path: VR options are parsed and forwarded, but currently not used to reconstruct VR jets.
2. Pythia conversion wrapper currently calls the non-VR overload in `generateEventPy8Collider.hpp`, so explicit VR collections are not yet propagated there.

---

## 6. Recommended Validation Checklist

Build/configure checks:
1. Ensure `fjcontrib` is included and linked (`-lVariableR` present in effective link flags).
2. If using reuse mode, check CMake message:
   - `Reusing contrib fastjet/fjcontrib for backend dependencies`.

Runtime checks with CBS HepMC input:
1. Add `VRJet_collections` in YAML with key `VRTrackJets`.
2. Run an analysis that consumes VR jets (for example `ATLAS_EXOT_2019_04`).
3. Compare outputs with and without `VRJet_collections`; acceptance/loglike should change when VR jet selections are active.

Failure-mode checks:
1. Provide `VRJet_collections: {}` and verify explicit error behavior (where enforced).
2. Omit `VRJet_collections` and verify run still succeeds (VR jets disabled).

---

## 7. Minimal Example for CBS Users

```yaml
analyses:
  - ATLAS_EXOT_2019_04

settings:
  event_file: /path/to/events.hepmc
  cross_section_fb: 5.0
  cross_section_uncert_fb: 0.5

  jet_collections:
    antikt_R04:
      algorithm: "antikt"
      R: 0.4
      recombination_scheme: "E_scheme"
      strategy: "Best"
    antikt_R10:
      algorithm: "antikt"
      R: 1.0
      recombination_scheme: "E_scheme"
      strategy: "Best"
  jet_collection_taus: antikt_R04

  VRJet_collections:
    VRTrackJets:
      rho: 30.0
      Rmin: 0.02
      Rmax: 0.40
      pt_min: 5.0
```

---

## 8. Files to Mention in Team Report

Core runtime:
1. `ColliderBit/include/gambit/ColliderBit/Utils.hpp`
2. `ColliderBit/include/gambit/ColliderBit/colliders/BaseCollider.hpp`
3. `ColliderBit/include/gambit/ColliderBit/colliders/Pythia8/Py8EventConversions.hpp`
4. `ColliderBit/include/gambit/ColliderBit/getPy8Collider.hpp`
5. `ColliderBit/src/getHepMCEvent.cpp`
6. `ColliderBit/src/getLHEvent.cpp`
7. `ColliderBit/include/gambit/ColliderBit/lhef2heputils.hpp`
8. `ColliderBit/src/lhef2heputils.cpp`
9. `ColliderBit/examples/solo.cpp`
10. `ColliderBit/examples/solo_batch.cpp`

Build system:
1. `cmake/contrib.cmake`
2. `cmake/executables.cmake`
3. `cmake/utilities.cmake`
4. `cmake/backends.cmake`

YAML templates:
1. `CBS_yaml/CBS_complete_template.yaml`
2. `CBS_yaml/ATLAS_EXOT_2019_04_processes.yaml`
