# CBS Update (2026-02-16)

## Section 1: Unify Cutflow Format via `Cutflow` Class
Goal: `Unify the format of cutflows by making use of the Cutflow class.`

### What was changed
1. Cutflow filling is now runtime-gated by a single CBS YAML switch: `check_cutflow` (bool).
2. CBS now uses one cutflow control path in standalone mode:
`check_cutflow=true` enables cutflow checks/filling/printing, and `check_cutflow=false` disables them.
3. `CollectAnalyses` now reads `check_cutflow` (with backward-compatible fallback to `print_cutflows`) for final cutflow printing.

### Main modified for this item
1. `/Users/p.zhu/Workshop/gambit/ColliderBit/include/gambit/ColliderBit/analyses/Cutflow.hpp`
Added runtime cutflow enable/disable control (`set_check_cutflow`) and no-op behavior when disabled.
2. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo.cpp`
Handling with a single YAML key:
`settings.check_cutflow`.

### Status
1. Mostly completed at the CBS framework level.
2. Still needs a full audit to confirm all analyses are consistently using `Cutflow` (especially legacy analyses with custom/manual cutflow code).

## Section 2: Control Cutflow Output from YAML
Goal: `Control the output of cutflows in YAML.`

### Outcome
1. Completed for CBS runtime control using a single YAML key: `settings.check_cutflow` (bool).
2. Behavior:
`check_cutflow=true` enables cutflow filling and printing in CBS outputs.
`check_cutflow=false` disables cutflow filling/printing at runtime.

### CMake relation (required condition)
1. `CHECK_CUTFLOW` is still a compile-time gate in ColliderBit analyses.
2. Therefore, runtime YAML control is effective when CBS is built with CMake option `CUTFLOW=ON` (which defines `-DCHECK_CUTFLOW`).
3. This compile-time option is provided in:
`/Users/p.zhu/Workshop/gambit/cmake/optional.cmake`

### Files used/updated for this item
1. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo.cpp`
2. `/Users/p.zhu/Workshop/gambit/ColliderBit/src/ColliderBit_eventloop.cpp`
3. `/Users/p.zhu/Workshop/gambit/ColliderBit/include/gambit/ColliderBit/analyses/Cutflow.hpp`
4. `/Users/p.zhu/Workshop/gambit/CBS_yaml/ATLAS_EXOT_2016_017.yaml`
5. `/Users/p.zhu/Workshop/gambit/CBS_yaml/ATLAS_EXOT_2019_04_processes.yaml`
6. `/Users/p.zhu/Workshop/gambit/CBS_yaml/CBS_complete_template.yaml`
7. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_example.yaml`

## Section 3: File Output in Addition to Screen Output
Goal: `Add an option to write results into files, in addition to screen output.`

### Outcome
1. Done. CBS now supports independent screen and file output.
2. Users can print to terminal, write to file, or do both in one run.

### YAML controls
```yaml
settings:
  screen_output: true
  output: /path/to/CBS_result.json
  output_format: json
  output_schema: cbs-solo-loglike-v1
  output_json_indent: 2
```

Behavior:
1. `screen_output=true` prints the human-readable summary.
2. `output` enables file writing.
3. `output_format` currently supports `json` only.
4. `output_schema` currently supports `cbs-solo-loglike-v1` only.
5. Output directories are created automatically if missing.

### What the output file looks like
Top-level JSON structure:
```json
{
  "schema_version": "cbs-solo-loglike-v1",
  "run": {
    "n_events": 12345,
    "with_contur": false,
    "output_format": "json",
    "output_json_indent": 2,
    "enabled_variants": ["nominal"]
  },
  "analyses": {
    "ATLAS_EXOT_2019_04": {
      "n_signal_regions": 1,
      "luminosity": 139.0,
      "combination": {
        "selected_sr_label": "SR",
        "selected_sr_index": 0,
        "nominal_loglike": -0.95,
        "alternatives": {}
      },
      "cutflows": [
        {
          "name": "SR",
          "cuts": [
            {
              "cut_index": 0,
              "cut_name": "initial",
              "count": 10000.0,
              "acceptance_cumulative": 1.0,
              "acceptance_incremental": null
            }
          ]
        }
      ],
      "signal_regions": {
        "SR": {
          "sr_index": 0,
          "n_obs": 262.0,
          "n_bkg": 260.0,
          "n_bkg_err": 17.0,
          "n_sig_MC": 336.0,
          "n_sig_MC_stat": 18.3,
          "n_sig_scaled": 34.9,
          "n_sig_scaled_err": 1.90,
          "loglike": -0.95,
          "alt_loglikes": {}
        }
      }
    }
  },
  "terms": [],
  "summary": {
    "n_analyses": 1,
    "combined_loglike": -0.95
  },
  "predefined_sets": {
    "default_total": ["ATLAS_EXOT_2019_04::combined::nominal"]
  }
}
```

Optional blocks:
1. `sampling_advice` appears in process/batch mode when MC top-up advice is produced.
2. `contur` appears only when Contur is enabled.

### Files modified for this item
1. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo.cpp`
Parses output settings and forwards output configuration.
2. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_output.hpp`
Defines output config and output API.
3. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_output.cpp`
Validates output config, prints screen summary, and writes JSON results.
4. `/Users/p.zhu/Workshop/gambit/CBS_yaml/CBS_complete_template.yaml`
Includes file-output settings in the template YAML.

## Section 4: Run CBS Multiple Times in One Command (Batch Support)
Goal: `Perhaps ability to run CBS multiple times ... properly coded into CBS.`

### Outcome
1. Done. CBS now supports process-list batch execution directly in `solo`.
2. Instead of a user-side bash loop, CBS can internally run one standard single-file job per HepMC file and then merge all outputs.

### How it works
1. User provides `settings.processes` in one YAML.
2. CBS creates per-file temporary YAML jobs internally.
3. Each file is run through the existing single-file CBS pipeline.
4. CBS reads per-file JSON outputs and merges them into one final likelihood result.

### Input format used for this feature
```yaml
settings:
  processes:
    - name: process_A
      cross_section_fb: 12.5
      cross_section_uncert_fb: 0.6
      files:
        - file: /path/A_1.hepmc
          generated_events: 50000
        - file: /path/A_2.hepmc
          generated_events: 50000
```

Notes:
1. `generated_events` can be provided explicitly.
2. If omitted, CBS can count events from HepMC files during input preparation.

### Files modified for this item
1. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_input.hpp`
2. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_input.cpp`
3. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_batch.hpp`
4. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_batch.cpp`
5. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo.cpp`
6. `/Users/p.zhu/Workshop/gambit/CBS_yaml/CBS_complete_template.yaml`

## Section 5: Multiple Cross-Sections + HepMC Files in One Likelihood Evaluation
Goal: `Allow passing multiple cross-sections and hepmc files into one likelihood evaluation.`

### Outcome
1. Done. CBS now supports two combination methods through `settings.processes`.

### Combination method A: Same physical process, multiple files (statistics split)
Use one process entry with multiple HepMC files:
1. One process-level cross-section is provided.
2. File-level contribution is assigned by event-count fraction within that process.
3. This is intended for combining statistically independent chunks of the same process.

### Combination method B: Different physical processes, each with own cross-section
Use multiple process entries:
1. Each process has its own `cross_section_*`.
2. SR predictions are combined at the end in one common likelihood evaluation.
3. Central values are summed, and independent MC uncertainties are combined in quadrature.

### Merging strategy used in CBS
For each analysis/SR:
1. `n_sig_scaled_total = sum_i n_sig_scaled_i`
2. `sigma_total = sqrt(sum_i sigma_i^2)`
3. Final likelihood is computed from the merged SR predictions (not by summing per-file loglikes).

### Files modified for this item
1. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_input.cpp`
2. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo_batch.cpp`
3. `/Users/p.zhu/Workshop/gambit/ColliderBit/examples/solo.cpp`
4. `/Users/p.zhu/Workshop/gambit/CBS_yaml/ATLAS_EXOT_2019_04_processes.yaml`
5. `/Users/p.zhu/Workshop/gambit/CBS_yaml/CBS_complete_template.yaml`

## Section 6: Report-Ready Items (Requested)
Use the following wording in the update list:

```tex
\item Perhaps ability to run CBS multiple times. Could be a bash script to generate yaml files from a list of cross-sections and hepmc files. Could also be properly coded into CBS. \px{Done! support a list of cross-section and hepmc files as input.}
\item Perhaps allow passing of multiple cross-sections and hepmc files that should go into a single likelihood evaluation. Could require assigning event weights based on the file cross-section. \px{Done! support two combination methods according to the processes.}
```

### Our handling method
1. `settings.processes` allows one YAML to include many processes and many HepMC files.
2. CBS runs each HepMC file through the standard single-file pipeline internally (batch mode in `solo`).
3. Then CBS combines all contributions at SR level and computes one final likelihood from merged predictions.
4. Two supported combination modes:
   - Same process split across multiple files: one process-level cross-section, file contributions combined as statistical chunks.
   - Different physical processes: each process has its own cross-section, then summed into one SR prediction.
5. Uncertainty merge rule for independent MC components: central values are summed, and MC statistical errors are added in quadrature.

## Section 7: FastJet Build Variant and Unification
Use the following wording in the update list:

```tex
\item Check that the required variant of fastjet is being built when we build CBS. \px{Done! CBS requires FastJet 3.4.2 + FJContrib 1.049, and the build path is explicitly controlled in CMake.}
\item Unify use of fastjet between Backends and contrib (avoid having both if possible). \px{Done! backend now reuses contrib fastjet/fjcontrib targets when available, avoiding duplicate builds in CBS workflows.}
```

### What was implemented
1. Added backend-side reuse logic:
`/Users/p.zhu/Workshop/gambit/cmake/backends.cmake` checks `if(TARGET fastjet AND TARGET fjcontrib)` and sets `FJ_BACKEND_REUSE_CONTRIB=TRUE`.
2. When reuse is active, backend dependencies (including Rivet) use contrib FastJet path:
`/Users/p.zhu/Workshop/gambit/contrib/fastjet-3.4.2/local`.
3. If contrib targets are not available, backend falls back to building its own `fastjet_3.4.2` and `fjcontrib_1.049`.
4. Contrib still defines the ColliderBit build targets `fastjet` and `fjcontrib` in:
`/Users/p.zhu/Workshop/gambit/cmake/contrib.cmake`.

### How to verify in CBS builds
1. During CMake configure, check for:
`Reusing contrib fastjet/fjcontrib for backend dependencies`.
2. In a CBS build, expect contrib targets (`fastjet`, `fjcontrib`) and avoid backend duplicate targets (`fastjet_3.4.2`, `fjcontrib_1.049`) when reuse is enabled.
