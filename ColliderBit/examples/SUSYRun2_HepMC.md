# SUSYRun2 CBS single-point HepMC card

`yaml_files/CBS_SUSYRun2_HepMC.yaml` describes one EWino process with three
HepMC gzip files. The card sets `settings.processes` and `settings.output`, so
CBS checkpoints each finished HepMC file beside that JSON and merges the stored
results. Rivet files are scaled and merged for the collider, and Contur runs
once. CBS has been rebuilt with `cmake --build --preset cbs-llvm --target CBS`.
The merged result has not been run, so it has not been compared with the
previous single event loop.

## Prepared inputs

The files are `tag_1_pythia8_events.hepmc.gz` in
`/Users/p.zhu/Gambit-Workshop/CBS/EWinos/Events/run_02`, `run_03`, and `run_04`.
All have 10,000 events, 13 TeV pp beams, and identical SLHA parameters. They
sample the same physical process and point with different random seeds.

| Run | Seed | Cross section (pb) | Numerical integration error (pb) |
|---|---:|---:|---:|
| run_02 | 27 | 1.536122110520117 | 0.001713781957296088 |
| run_03 | 33 | 1.537055207687767 | 0.001652235255444058 |
| run_04 | 39 | 1.537272174707867 | 0.002045086053915896 |

The process cross section is the equal-event-count **mean**, 1.536816497638584 pb,
not the sum. Its 0.001046120181347737 pb error assumes independent numerical
integration estimates. It is not a scale/PDF or higher-order theory uncertainty.
The input files are read without modification or temporary full decompression.

The card explicitly selects `settings.nominal_weight_name: Weight`. These
samples have 146 weights; `Weight` is at index 145 and the first weight `1` is a
variation. CBS resolves names on each event, so reordering names and values
together does not change the selected nominal weight. Automatic selection is
available for an unambiguous conventional nominal name or a sole weight;
ambiguous multiweight files require an explicit name. Negative/non-finite nominal
weights, empty or damaged files, duplicate file paths (including symlink aliases),
zero weight denominators, inconsistent run conditions and duplicate process names
fail explicitly.

## Weight and process semantics

A process's files are repeat samples with a **common nominal-weight scale**.
Different process entries describe distinct signal contributions and their cross
sections are added within their collider. Do not place the same inclusive process
in several entries and add its cross section repeatedly. CBS cannot infer arbitrary
relative rescalings of weights in separate files: restore a common convention
before supplying repeat samples. A common rescaling of all weights of a process
cancels exactly in its normalisation.

For collider event count `N`, total process cross section `sigma`, process cross
section `sigma_p`, and the sum `S_p` of its nominal input weights, CBS uses

```text
c_p = N * sigma_p / (sigma * S_p)
w_event = c_p * nominal_input_weight
sum(collider event weights) = N

signal_SR = L * sigma/N * sum(selected event weights)
MC_error_SR = L * sigma/N * sqrt(sum(selected event weights squared))
```

This is the independent Poisson MC convention with a fixed normalisation
denominator. The weight-square sum is distinct from supplied weight systematic
errors. Unit weights in a single process preserve the usual `sigma/N` behaviour.
General NLO signed weights and correlated sub-event groups are outside this model.
The standard covariance/single-SR likelihood paths consume this MC error. The
optional ATLAS_FullLikes interface retains its existing yield-only signal map;
it does not consume SR MC errors. YAML cross-section uncertainty is recorded and
passed to Rivet, rather than automatically added as a separate global search
signal uncertainty. The prepared card does not enable FullLikes.
The existing CBS fixed-event likelihood estimator is MLE; UMVUE is incompatible
with consuming a fixed external event sample.

Rivet receives one weight channel named `nominal`, the same normalised weights as
the searches, and the collider's YAML cross section in pb. The user cross section
is pinned in every active handler. The 145 variations are intentionally omitted;
Rivet's `skipMultiWeights` code is not used. Cross-section metadata in the original
files cannot override the YAML normalisation.

Each physical event gets a distinct logical ID. Repeated generator event numbers
are retained as provenance, never used for deduplication. File boundaries only
change the serialised reader: all events already have identical run metadata and
cross section, and no handler is reset or notified of a new physical run. Each
thread's pending event group is collapsed by the final raw merge/finalize.

Different colliders stay separate mixtures. Search results are combined by
their assigned collider; Contur values are combined only when their pool keys
are disjoint. Repeated pool keys produce an error requiring a joint experimental
treatment. A card with `settings.processes` and `settings.output` uses the
checkpoint driver. A card without `settings.output` still uses one normalised
event loop within each collider, and multiple colliders without that output
still use one child task each. `run_and_merge` is not called by the CBS
frontend. `keep_batch_tmp` controls successful multi-collider child files;
failed child inputs remain for diagnosis.

## Build and run

The maintainer builds CBS using the existing shared `build/` tree and enabled
HepMC3, ROOT/RestFrames, Rivet 4.1.0 and Contur 3.0.0 backends. The CBS target
was rebuilt from that `cbs-llvm` cache. No CBS execution was performed for this
implementation. Contur's GAMBIT
initializer must include `CONTUR_DATA_PATH` (installation root) and
`CONTUR_USER_DIR` (`data/DB`), as prepared earlier in this branch.

From the repository root, after rebuilding:

```sh
OMP_NUM_THREADS=1 ./CBS ./yaml_files/CBS_SUSYRun2_HepMC.yaml
```

Expected input count is 30,000. Inspect enabled searches and the **actual** Rivet
analysis list; the 63 requested strings are still subject to Rivet beam matching.
The JSON is `runs/CBS_SUSYRun2_HepMC.json`. Invalid input or a missing/empty Contur
point aborts; it is not represented as a successful zero constraint.

`write_YODA_file: false` passes an in-memory YODA stream to Contur. Set it
to true to also write `GAMBIT_collider_measurements_CBS_pp_13TeV.yoda` in the
same directory as `settings.output`. Contur's log is `contur.log` in that
directory. The run prints the absolute JSON path when it finishes.
`trace_input_events: true`
adds source `(collider, process, file, file_event_index, original_event_number,
iteration)` records and per-SR accepted IDs to JSON. Keep tracing off for compact
production output. File indices are one-based; nominal weight indices are
zero-based (`-1` indicates an index that changed within a file).

The JSON also records per-file and per-process `sum_weights`/`sum_weights2`,
process cross sections, actual applied `weight_scale`, collider event counts,
`n_sig_MC_sumw2`, actual Rivet analyses, and `contur_evaluations` (one per collider).
SR counts and variances are in the transformed logical-weight convention above;
input-file sums are in the original nominal convention. With multiple colliders,
logical event IDs are local to their collider.

Acceptance materials, independent Rivet reference inputs and commands are
explained in `ColliderBit/tests/README.md`. Complete-input preflight validates
gzip integrity, counts and parses events before analysis, so startup reads the
inputs more than once. It avoids partial-result normalisation and needs no
large uncompressed temporary files.

## Terminal output

CBS prints full input paths, analysis/SR names, disabled-analysis reasons, Contur
pool names and formatted numbers. Table columns expand to fit their contents;
80 columns is only a default section-rule width. Multiple dominant measurements
for one Contur pool appear on separate aligned lines. The analysis catalogue
also retains complete summaries. A narrow terminal may wrap wide tables; a saved
log retains the complete lines. This display policy does not change numerical
formatting precision, analysis results or JSON values.

## Physics comparison boundaries

This card is adapted from local `gambit/master` `SUSYRun2_MSSMEW.yaml` at commit
`6535d4490a`. It requests its 63 Rivet strings and the current checkout's 38
search names, omitting Baselines and overlap-excluded searches. It does not
reproduce GAMBIT's model scan, generated sample, other likelihoods or cross-section
veto. The old ATLAS Z search is represented by `ATLAS_SUSY_2018_21_StopZH`.

Report metadata supports multiple registered classes through `Analyses`, retaining
one `.info` per report. All 38 requested classes resolve uniquely in the static
audit. Actual availability depends on the rebuilt binary, including ROOT for
`ATLAS_SUSY_2019_02` and ROOT/RestFrames for the RJR analyses. Missing validation
metadata alone does not establish numerical validation.

The CMS SUS-19-012 candidate-lepton truncation is separately corrected to keep
four rather than three when there are more than four. Record its physics effect
separately from input normalisation. The existing
`ATLAS_SUSY_2016_27_2Photon` photon-isolation limitation remains. Detector smearing
can change between thread counts, so real multithreaded physics results require
statistical comparison; identical seeds do not promise bitwise equality.
