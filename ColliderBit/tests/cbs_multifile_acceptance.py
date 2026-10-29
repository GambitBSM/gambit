#!/usr/bin/env python3
"""Prepare weighted HepMC2 fixtures; execute CBS only with explicit --run.

Uses a small prefix of a supplied real sample so particle histories remain valid.
Does not configure, build, modify original inputs, or overwrite an existing suite.
Requires PyYAML. Numerical checks use source provenance and accepted event IDs,
not a reimplementation of the search selection.
"""
import argparse
import copy
import gzip
import json
import math
import os
from pathlib import Path
import shlex
import subprocess
import sys

import yaml

ROOT = Path(__file__).resolve().parents[2]
HEADER = "HepMC::Version 2.06.09\nHepMC::IO_GenEvent-START_EVENT_LISTING\n"
FOOTER = "HepMC::IO_GenEvent-END_EVENT_LISTING\n"


def read_events(path, limit):
    opener = gzip.open if path.suffix == ".gz" else open
    events, event = [], []
    with opener(path, "rt") as stream:
        for line in stream:
            if line.startswith("E "):
                if event:
                    events.append(event)
                    if len(events) == limit:
                        break
                event = [line]
            elif line.startswith("HepMC::IO_GenEvent-END"):
                if event:
                    events.append(event)
                break
            elif event:
                event.append(line)
    if len(events) < limit:
        raise ValueError(f"Need at least {limit} complete events in {path}")
    return events[:limit]


def weighted_event(lines, nominal, order=False, name="Weight"):
    fields = lines[0].split()
    # HepMC2 E: ... beam1 beam2 nRandom randomValues... nWeights weights...
    index = 12 + int(fields[11])
    fields[1] = "7"  # Repeated producer IDs must remain distinct physical events.
    fields = fields[:index] + ["2"]
    variation = 0.01 if nominal < 2 else 123.0
    weights = [variation, nominal]
    names = ["variation", name]
    if order:
        weights.reverse()
        names.reverse()
    fields += [format(value, ".17g") for value in weights]
    result = [" ".join(fields) + "\n", "N 2 " + " ".join(json.dumps(n) for n in names) + "\n"]
    result += [line for line in lines[1:] if not line.startswith("N ")]
    return result


def write_events(path, events):
    opener = gzip.open if path.suffix == ".gz" else open
    with opener(path, "wt") as stream:
        stream.write(HEADER)
        for event in events:
            stream.writelines(event)
        stream.write(FOOTER)
    return str(path.resolve())


def prepare(directory, source, count, template):
    directory.mkdir(parents=True, exist_ok=False)
    events = read_events(source, count)
    weights = [(.5, 1., 2., 5.)[i % 4] for i in range(count)]
    weighted = [weighted_event(e, w) for e, w in zip(events, weights)]
    whole = write_events(directory / "whole.hepmc.gz", weighted)
    cut = [0, 1, count // 3, count]
    split = [write_events(directory / f"part{i}.hepmc.gz", weighted[a:b])
             for i, (a, b) in enumerate(zip(cut, cut[1:]))]
    reordered_part = write_events(directory / "part_reordered.hepmc.gz", [
        weighted_event(e, w, order=True) for e, w in zip(events[cut[1]:cut[2]], weights[cut[1]:cut[2]])])
    plain = write_events(directory / "whole.hepmc", weighted)
    reordered = write_events(directory / "reordered.hepmc.gz",
                             [weighted_event(e, w, order=True) for e, w in zip(events, weights)])
    scaled = write_events(directory / "scaled.hepmc.gz",
                          [weighted_event(e, 17*w) for e, w in zip(events, weights)])
    missing = write_events(directory / "missing.hepmc.gz",
                           [weighted_event(e, w, name="not_nominal") for e, w in zip(events, weights)])
    negative = write_events(directory / "negative.hepmc.gz", [weighted_event(events[0], -1)])
    zero = write_events(directory / "zero.hepmc.gz", [weighted_event(events[0], 0)])
    duplicate_names = write_events(directory / "duplicate_names.hepmc.gz",
                                  [[line.replace('"variation"', '"Weight"') for line in weighted[0]]])
    nonfinite = write_events(directory / "nonfinite.hepmc.gz", [weighted_event(events[0], float("nan"))])
    half = count // 2
    halves = [write_events(directory / f"process{i}.hepmc.gz", group)
              for i, group in enumerate([weighted[:half], weighted[half:]])]
    bad_header = directory / "bad_header.hepmc"
    bad_header.write_text("not HepMC\n")
    empty = write_events(directory / "empty.hepmc.gz", [])
    truncated = directory / "truncated.hepmc.gz"
    truncated.write_bytes(Path(whole).read_bytes()[:-8])
    corrupt = directory / "corrupt.hepmc.gz"
    data = bytearray(Path(whole).read_bytes()); data[-8] ^= 1
    corrupt.write_bytes(data)
    listing = directory / "incomplete.hepmc"
    listing.write_text(HEADER + "".join(weighted[0]))
    # Change only the last event's beams; never run a partial point.
    changed = copy.deepcopy(weighted)
    for i, line in enumerate(changed[-1]):
        fields = line.split()
        if fields and fields[0] == "P" and fields[8] == "4":
            fields[2] = "11"
            changed[-1][i] = " ".join(fields) + "\n"
    wrong_run = write_events(directory / "changed_run.hepmc.gz", changed)
    cases = []

    def add(name, files, success=True, measurements=False, legacy=False, processes=None):
        card = copy.deepcopy(template)
        if not measurements:
            card.pop("rivet-settings", None); card.pop("contur-settings", None)
        else:
            card["rivet-settings"]["write_YODA_file"] = True
        settings = card["settings"]
        for key in list(settings):
            if key.startswith("cross_section_") or key in ("event_file", "processes"):
                settings.pop(key)
        settings.update(nominal_weight_name="Weight", trace_input_events=True,
                        seed=12345, screen_output=False, hepmc_progress=False,
                        output=str(directory / (name + ".json")))
        if legacy:
            settings.update(event_file=files[0], cross_section_pb=5., cross_section_uncert_pb=0.)
        else:
            settings["processes"] = processes or [dict(name="toy", cross_section_pb=5.,
                                                       cross_section_uncert_pb=0., files=files)]
        card_path = directory / (name + ".yaml")
        card_path.write_text(yaml.safe_dump(card, sort_keys=False))
        cases.append(dict(name=name, card=str(card_path), success=success, measurements=measurements))

    add("whole", [whole]); add("split", split); add("plain", [plain])
    add("reordered", [reordered]); add("split_reordered", [split[0], reordered_part, split[2]])
    add("scaled", [scaled]); add("legacy", [whole], legacy=True)
    add("two_processes", halves, processes=[dict(name="a", cross_section_pb=2., files=halves[:1]),
                                            dict(name="b", cross_section_pb=3., files=halves[1:])])
    for name, file in [("missing", missing), ("negative", negative), ("zero", zero),
                       ("duplicate_names", duplicate_names), ("nonfinite", nonfinite),
                       ("empty", empty), ("bad_header", bad_header), ("truncated", truncated),
                       ("corrupt", corrupt), ("incomplete", listing), ("changed_run", wrong_run)]:
        add(name, [str(file)], success=False)
    add("duplicate_file", [whole, whole], success=False)
    if "rivet-settings" in template and "contur-settings" in template:
        add("joint_whole", [whole], measurements=True)
        add("joint_split", split, measurements=True)
        add("joint_two_processes", halves, measurements=True,
            processes=[dict(name="a", cross_section_pb=2., files=halves[:1]),
                       dict(name="b", cross_section_pb=3., files=halves[1:])])
        # V07 has 0/1-event workers. Contur can legitimately reject a tiny sample
        # with no usable pools; inspect the written YODA counter in that case.
        for size in (1, 2, 3):
            tiny = write_events(directory / f"tiny{size}.hepmc.gz", weighted[:size])
            add(f"joint_tiny{size}", [tiny], measurements=True)
    # Canonical one-weight inputs for an independent Rivet CLI comparison.
    def reference_event(event, weight, event_id):
        fields = event[0].split(); k = 12 + int(fields[11])
        fields[1] = str(event_id)
        return [" ".join(fields[:k] + ["1", format(weight, ".17g")]) + "\n",
                'N 1 "nominal"\n', 'C 5 0\n'] + [line for line in event[1:]
                    if not line.startswith(("N ", "C "))]
    reference = write_events(directory / "reference_nominal.hepmc.gz", [
        reference_event(event, count*w/sum(weights), i+1)
        for i, (event, w) in enumerate(zip(events, weights))])
    two_reference = []
    for i, (event, w) in enumerate(zip(events, weights)):
        sigma = 2 if i < half else 3
        denominator = sum(weights[:half]) if i < half else sum(weights[half:])
        two_reference.append(reference_event(event, count*sigma*w/(5*denominator), i+1))
    two_reference_path = write_events(directory / "reference_two_processes.hepmc.gz", two_reference)
    if "rivet-settings" in template:
        analyses = []
        for name in template["rivet-settings"]["analyses"]:
            analyses.extend(["-a", name])
        command = ["rivet", *analyses, "-x", "5", "-o", str(directory / "reference.yoda"), reference]
        second = ["rivet", *analyses, "-x", "5", "-o", str(directory / "reference_two_processes.yoda"), two_reference_path]
        (directory / "rivet_reference_commands.sh").write_text(
            "#!/bin/sh\nset -eu\n" + shlex.join(command) + "\n" + shlex.join(second) + "\n")
    manifest = dict(source=str(source), n_events=count, weights=weights, cases=cases,
                    pending=["Independent Rivet/Contur reference comparison (V09/V10)",
                             "Multi-thread stochastic detector comparison (V08)",
                             "Two colliders, disjoint pools and overlapping-pool rejection (CBS-12)",
                             "Actual 30000-event SUSYRun2 run (V13)"])
    (directory / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def close(a, b, message):
    if not math.isclose(a, b, rel_tol=2e-9, abs_tol=1e-8):
        raise AssertionError(f"{message}: {a} != {b}")


def check_oracle(result, card):
    inputs = {f["file"]: f for f in result["run"]["input_files"]}
    sources = result["run"]["event_sources"]
    if len(sources) != result["run"]["n_events"] or len({(s['file'], s['file_event_index']) for s in sources}) != len(sources):
        raise AssertionError("Missing or duplicate physical events")
    if any(s["original_event_number"] != 7 for s in sources):
        raise AssertionError("Original generator event numbers were not retained")
    logical_weights = {}
    file_weights = {}
    for filename in inputs:
        count = inputs[filename]["n_events"]
        parsed = read_events(Path(filename), count)
        values = []
        for event in parsed:
            fields = event[0].split(); k = 12 + int(fields[11])
            names = shlex.split(next(line for line in event if line.startswith("N ")))[2:]
            values.append(float(fields[k + 1 + names.index("Weight")]))
        file_weights[filename] = values
        close(sum(values), inputs[filename]["sum_weights"], "input sumW")
        close(sum(w*w for w in values), inputs[filename]["sum_weights2"], "input sumW2")
    processes = card["settings"].get("processes")
    if processes is None:
        processes = [dict(cross_section_pb=card["settings"]["cross_section_pb"],
                          files=[card["settings"]["event_file"]])]
    sigma = lambda p: p["cross_section_fb"] if "cross_section_fb" in p else 1000*p["cross_section_pb"]
    total_sigma = sum(sigma(p) for p in processes)
    for process in processes:
        denominator = sum(sum(file_weights[f]) for f in process["files"])
        scale = len(sources) * sigma(process) / (total_sigma * denominator)
        for filename in process["files"]:
            close(inputs[filename]["weight_scale"], scale, "process mixture normalization")
    close(result["run"]["colliders"][0]["cross_section_fb"], total_sigma, "YAML cross section")
    for event in sources:
        file = inputs[event["file"]]
        logical_weights[event["iteration"]] = file_weights[event["file"]][event["file_event_index"]-1] * file["weight_scale"]
    close(sum(logical_weights.values()), len(sources), "normalized collider sumW")
    nonzero = 0
    for analysis in result["analyses"].values():
        collider = next(c for c in result["run"]["colliders"] if c["name"] == analysis["collider"])
        factor = analysis["luminosity"] * collider["cross_section_fb"] / collider["n_events"]
        for sr in analysis["signal_regions"].values():
            selected = [logical_weights[i] for i in sr["accepted_event_ids"]]
            close(sum(selected), sr["n_sig_MC"], "SR sumW")
            close(sum(w*w for w in selected), sr["n_sig_MC_sumw2"], "SR sumW2")
            close(math.sqrt(sum(w*w for w in selected)), sr["n_sig_MC_stat"], "SR MC standard error")
            close(factor * sum(selected), sr["n_sig_scaled"], "physical SR yield")
            close(factor * math.sqrt(sum(w*w for w in selected)), sr["n_sig_scaled_err"], "physical MC error")
            nonzero += bool(selected)
    if not nonzero:
        raise AssertionError("No selected SR events: increase --events or choose an accepted fixture")
    expected_contur = int("contur-settings" in card)
    if result["run"]["contur_evaluations"] != expected_contur:
        raise AssertionError("Unexpected number of Contur evaluations")


def compare_predictions(left, right):
    for name, analysis in left["analyses"].items():
        for label, sr in analysis["signal_regions"].items():
            other = right["analyses"][name]["signal_regions"][label]
            for key in ("n_sig_MC", "n_sig_MC_stat", "n_sig_scaled", "n_sig_scaled_err"):
                close(sr[key], other[key], f"{name}/{label}/{key}")
    if "contur" in left:
        close(left["contur"]["total_loglike"], right["contur"]["total_loglike"], "Contur total")
        if left["contur"]["pools"].keys() != right["contur"]["pools"].keys():
            raise AssertionError("Contur pool selection changed")
        for pool, value in left["contur"]["pools"].items():
            close(value["loglike"], right["contur"]["pools"][pool]["loglike"], pool)


def execute(directory, manifest, executable, measurements):
    results = {}; report = {"cases": [], "pending": manifest["pending"]}
    for case in manifest["cases"]:
        if case["measurements"] and (not measurements or "tiny" in case["name"]):
            continue
        name = case["name"]
        working = directory / (name + "_run"); working.mkdir(exist_ok=True)
        card = yaml.safe_load(Path(case["card"]).read_text())
        output = Path(card["settings"]["output"]); output.unlink(missing_ok=True)
        environment = dict(os.environ, OMP_NUM_THREADS="1", OMP_DYNAMIC="FALSE")
        with (working / "CBS.log").open("w") as log:
            completed = subprocess.run([str(executable), case["card"]], cwd=working,
                                       env=environment, stdout=log, stderr=subprocess.STDOUT)
        passed = completed.returncode == (0 if case["success"] else 1)
        if not case["success"] and output.exists():
            passed = False
        error = None
        if passed and case["success"]:
            try:
                results[name] = json.loads(output.read_text())
                check_oracle(results[name], card)
                base = "joint_whole" if name.startswith("joint_") else "whole"
                if name not in ("whole", "joint_whole", "two_processes", "joint_two_processes"):
                    compare_predictions(results[base], results[name])
            except (AssertionError, KeyError, ValueError, OSError) as exc:
                passed = False; error = str(exc)
        report["cases"].append(dict(name=name, passed=passed, exit_code=completed.returncode, error=error))
        print(f"{'PASS' if passed else 'FAIL'} {name}")
    (directory / "acceptance-results.json").write_text(json.dumps(report, indent=2) + "\n")
    return 0 if all(case["passed"] for case in report["cases"]) else 1


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--directory", required=True, type=Path)
    parser.add_argument("--input", type=Path, help="Real HepMC2 sample for fixture preparation")
    parser.add_argument("--events", type=int, default=96)
    parser.add_argument("--template", type=Path, default=ROOT / "yaml_files/CBS_SUSYRun2_HepMC.yaml")
    parser.add_argument("--run", action="store_true", help="Explicitly execute an already built CBS (maintainer only)")
    parser.add_argument("--cbs", type=Path, default=ROOT / "CBS")
    parser.add_argument("--with-measurements", action="store_true")
    args = parser.parse_args()
    directory = args.directory.resolve()
    if not directory.exists():
        if not args.input or args.events < 6:
            parser.error("Preparation requires --input and --events >= 6")
        manifest = prepare(directory, args.input.resolve(), args.events, yaml.safe_load(args.template.read_text()))
    else:
        manifest = json.loads((directory / "manifest.json").read_text())
    print(f"Suite: {directory}; {len(manifest['cases'])} cards; no build is performed.")
    if not args.run:
        print("Prepared only; CBS has not been executed. Use --run after the maintainer rebuild.")
        return 0
    return execute(directory, manifest, args.cbs.resolve(), args.with_measurements)


if __name__ == "__main__":
    sys.exit(main())
