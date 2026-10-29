# CBS multifile acceptance materials

No command below has been used to configure, compile, or run CBS during this
implementation. The maintainer performs those steps after rebuilding. Static
material-generation tests can be run without any CBS or backend executable:

```sh
python3 ColliderBit/tests/test_multifile_materials.py
```

## Generated suite

`cbs_multifile_acceptance.py` requires PyYAML. By default it only prepares a new
suite. It reads a prefix of a real HepMC2 sample, preserving particle histories,
and assigns artificial positive weights `[0.5, 1, 2, 5]` and a toy cross section
of 5 pb. The other weight deliberately has a different event dependence. Generator
numbers are all set to 7 to check that CBS does not deduplicate them. Original
sample files are never changed. Fixtures are control/statistics tests, not EWino
physics predictions.

A 96-event suite with 26 cards has already been prepared at
`P.Zhu/CBS_multifile_acceptance`. To prepare another directory:

```sh
python3 ColliderBit/tests/cbs_multifile_acceptance.py \
  --directory /tmp/my-cbs-multifile-suite \
  --input /path/to/real_events.hepmc.gz --events 96
```

After the maintainer rebuild, explicitly execute its automated subset:

```sh
python3 ColliderBit/tests/cbs_multifile_acceptance.py \
  --directory P.Zhu/CBS_multifile_acceptance --run --with-measurements
```

An existing directory is reused from its manifest; preparation never overwrites
it. The runner launches CBS with one OpenMP thread, saves a separate `CBS.log` per
case and writes `acceptance-results.json`. An expected invalid input must exit
with status 1 and produce no JSON; crashes do not count as passing rejection.
The runner never builds anything. Only use `--run` with the rebuilt binary.

For positive cases the oracle reads the generated weights independently,
reconstructs the expected process scales from the YAML cross sections and
per-process weight sums, and uses CBS's source/accepted-event IDs to check each
SR's sumW, sumW2, yield and MC error. A test with no accepted signal events fails
as inconclusive; increase `--events` in a new suite rather than interpreting all
zero bins as a weighted-statistics success. Input normalisation tests deliberately
use zero supplied weight systematic uncertainty.

Cases cover single-file, unequal three-way split, plain/gzip, nominal-name
reordering, common weight rescaling, legacy `event_file`, two physical processes,
missing/duplicate weight names, negative/zero/non-finite weights, empty/bad header,
truncated gzip trailer, CRC failure, missing listing footer, changing beams, and
duplicate files. Joint whole/split/two-process cards exercise search+Rivet+Contur.
Their JSON should show one Contur evaluation per collider.

## Independent Rivet and Contur comparison

Preparation also writes `reference_nominal.hepmc.gz`,
`reference_two_processes.hepmc.gz`, and `rivet_reference_commands.sh`. These have
exactly the normalised nominal weights, unique event IDs and 5 pb cross section
expected at the Rivet interface, with one weight channel. They are small,
independent reference inputs rather than concatenations of unnormalised original
files. In the maintainer's working Rivet/Contur environment:

```sh
sh P.Zhu/CBS_multifile_acceptance/rivet_reference_commands.sh

yodadiff -t 1e-8 \
  P.Zhu/CBS_multifile_acceptance/reference.yoda \
  P.Zhu/CBS_multifile_acceptance/joint_split_run/GAMBIT_collider_measurements_CBS_pp_13TeV.yoda

yodadiff -t 1e-8 \
  P.Zhu/CBS_multifile_acceptance/reference_two_processes.yoda \
  P.Zhu/CBS_multifile_acceptance/joint_two_processes_run/GAMBIT_collider_measurements_CBS_pp_13TeV.yoda
```

Compare raw `_EVTCOUNT`, `_XSEC`, sumW/sumW2 and representative histograms as well
as the final prediction. Do not use `--normalize` to hide a cross-section mismatch.
Evaluate each reference YODA with Contur's same backend version, database and
settings; compare its LLR after the GAMBIT `-0.5` conversion, pool LLRs and tags.
A CLI Contur invocation is `contur --nomultip -q reference.yoda`; use an isolated
output directory. Its text summary is supplementary: retain the API dictionary
if a numerical pool/tag comparison is needed.

## Remaining maintainer checks

The automatic subset does not certify the whole acceptance matrix. The manifest
explicitly lists the following outstanding runtime evidence:

- **V07**: run `joint_tiny1.yaml`, `joint_tiny2.yaml`, `joint_tiny3.yaml` with
  `OMP_NUM_THREADS=8 OMP_DYNAMIC=FALSE` from separate output directories. Inspect
  their YODA event counters for N=1/2/3. Contur may explicitly reject a tiny sample
  with no usable pools; that is not a valid zero constraint and is not an automatic
  V07 pass. Confirm the Rivet counter before interpreting that rejection.
- **V08**: rerun with multiple threads and compare event totals and normalisation
  exactly within floating tolerance. Compare stochastic detector yields with an
  appropriate statistical tolerance, not bitwise equality. Inspect a case where
  thread 0 has no events if runtime scheduling produces it.
- **V09/V10**: independent Rivet and Contur checks above, including backend output
  field/type validation and no-useful-measurements behaviour. Missing fields,
  `None`, non-finite LLRs and missing tags must be explicit errors.
- **CBS-12**: supply real samples at two collider energies and matching searches.
  Verify separate event counts, cross sections, one Contur evaluation per collider,
  disjoint-pool combination and repeated-pool rejection. The suite does not forge
  an 8 TeV sample by editing beams on a 13 TeV physical event.
- **V13**: run `yaml_files/CBS_SUSYRun2_HepMC.yaml` on all 30,000 events. Preserve
  the full JSON and logs, verify all 38 searches and actual Rivet list, and compare
  results/normalisation with the independent references.

`weighted_event_counter.cpp` is a separate maintainer-run C++ unit check for
`EventCounter` reset/merge, Poisson sum(w²), systematic separation and
`SignalRegionData` scaling. Build it with the configured ColliderBit, HEPUtils,
Eigen and FastJet include/link flags when performing the manual build. It is not
registered as a physics analysis or part of the CBS production target.


## Cutflow/worker exception regression

`cutflow_lifecycle.cpp` is a maintainer-run C++ regression for the crash reported
on 2026-10-28. It exercises weighted cutflow filling, preserving bookings across
`Analysis::reset()`, disabled diagnostics with signal counting still active,
and typed, contextual missing-cutflow diagnostics. Link it with the configured
ColliderBit/Utils objects and dependencies during manual validation. It has not
been compiled or executed by the agent.

The regression now also uses `mkAnalysis` for the real `ATLAS_SUSY_2016_27`,
`..._1Photon` and `..._2Photon` variants. Use a `CHECK_CUTFLOW` build, as in the
reported CBS run. With runtime diagnostics both on and off, it verifies that
each final analysis name resolves to exactly one 51-cut booking before and after
reset, while retaining respectively 7, 3 and 4 signal regions. This specifically
covers the constructor-order bug missed by the synthetic probe.

The full-card rerun must also confirm that an unexpected worker exception is
reported on the main thread with collider/iteration/thread and analysis context,
rather than aborting with `uncaught exception of type int`. A failure must not be
reported as a successfully completed partial prediction. No search or Rivet
analysis was disabled by this repair.

An exception after Rivet handlers have been allocated must also exit cleanly
with status 1, without a second crash in `Rivet::Log::getLog` during process
teardown. The loop now releases surviving handlers on both normal return and
exception unwinding, before Rivet's thread-local log maps are destroyed. This
error-path integration check and the full-card rerun remain maintainer checks;
source inspection is not evidence of a successful runtime test.

## macOS Rivet / Python installation regression

`python3 cmake/tests/rivet_installation.py` applies the repository patch to
pristine files from the existing Rivet download archive in a temporary directory.
It checks that the native library is installed before plugins/Python, the macOS
`.so` backend name aliases the installed `.dylib`, and the Python install recipe
corrects the installed extension rather than its build-tree copy. It never
configures, compiles, imports a backend, or modifies the installed backend.

The 2026-10-28 maintainer run reached 30,000 events but Contur's Python Rivet
loader reported all 63 requested analyses missing. Read-only `otool -L` showed
that installed `rivet/core.so` still used `src/.libs/libRivet.dylib`, while CBS
loaded a separate `local/lib/libRivet.so` copy; `local/lib/libRivet.dylib` was
absent. Contur then had no likelihood blocks and failed while iterating `None`.
The source patch now installs one native library and corrects the Python path.
Contur backend initialization also checks for an empty Python analysis registry
before the CBS event loop. This check does not replace full physics validation.

For the currently configured LLVM toolchain, the maintainer can rebuild with:

```sh
cmake --preset cbs-llvm
cmake --build build --target rivet_4.1.0 -j 8
cmake --build --preset cbs-llvm -j 8
./CBS ./yaml_files/CBS_SUSYRun2_HepMC.yaml
```

No compiler-family switch or `--fresh` is needed for this existing LLVM cache.
The changed patch activates the existing pristine-source preparation step;
do not manually patch the installed tree. The installed `.so` should resolve to
`local/lib/libRivet.dylib`, and `otool -L` on the installed Python `rivet/core.so`
should reference that installed library, with no Rivet dependency under
`src/.libs`. A successful full run still requires a complete JSON and usable
Contur pools, not just the absence of missing-analysis warnings.
