#!/usr/bin/env python3
"""Static tests for acceptance-material generation and its independent oracle.

Does not execute or compile CBS, GAMBIT, Rivet or Contur.
"""
import copy
import gzip
import importlib.util
import math
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location("acceptance", Path(__file__).with_name("cbs_multifile_acceptance.py"))
acceptance = importlib.util.module_from_spec(spec)
spec.loader.exec_module(acceptance)

# Complete event framing is sufficient here: no physics parser is called.
EVENT = ["E 9 -1 -1 -1 -1 0 0 0 1 2 0 1 1\n", 'N 1 "Weight"\n', "U GEV MM\n"]


class MaterialsTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.directory = Path(self.temp.name)
        self.source = self.directory / "source.hepmc.gz"
        acceptance.write_events(self.source, [EVENT]*12)
        self.template = dict(analyses=["fixture"], settings={},
                             **{"rivet-settings": {"analyses": ["fixture"]}, "contur-settings": []})
        with patch.object(acceptance.subprocess, "run", side_effect=AssertionError("CBS execution forbidden in static tests")):
            self.manifest = acceptance.prepare(self.directory / "suite", self.source, 12, self.template)

    def tearDown(self):
        self.temp.cleanup()

    def test_unequal_split_is_lossless_and_repeated_numbers_retained(self):
        split = next(c for c in self.manifest["cases"] if c["name"] == "split")
        card = acceptance.yaml.safe_load(Path(split["card"]).read_text())
        files = card["settings"]["processes"][0]["files"]
        self.assertEqual([len(acceptance.read_events(Path(f), n)) for f, n in zip(files, (1, 3, 8))], [1, 3, 8])
        self.assertTrue(all(e[0].split()[1] == "7" for e in acceptance.read_events(Path(files[2]), 8)))

    def test_reordered_names_keep_nominal_value(self):
        event = acceptance.weighted_event(EVENT, 3.5, order=True)
        self.assertEqual(event[0].split()[-2:], ["3.5", "123"])
        self.assertEqual(acceptance.shlex.split(event[1]), ["N", "2", "Weight", "variation"])

    def test_bad_gzip_and_missing_listing_are_distinct_fixtures(self):
        for name in ("truncated", "corrupt"):
            with self.assertRaises((EOFError, gzip.BadGzipFile)):
                with gzip.open(self.directory / "suite" / (name + ".hepmc.gz"), "rt") as stream:
                    stream.read()
        self.assertNotIn(acceptance.FOOTER, (self.directory / "suite/incomplete.hepmc").read_text())
        self.assertEqual(len(self.manifest["cases"]), 26)

    def oracle_fixture(self):
        case = next(c for c in self.manifest["cases"] if c["name"] == "whole")
        card = acceptance.yaml.safe_load(Path(case["card"]).read_text())
        filename = card["settings"]["processes"][0]["files"][0]
        weights = self.manifest["weights"]
        scale = len(weights)/sum(weights)
        chosen = [weights[0]*scale, weights[2]*scale]
        factor = 10*5000/12
        result = {"run": {"n_events": 12, "contur_evaluations": 0,
                          "input_files": [{"file": filename, "n_events": 12, "sum_weights": sum(weights),
                                           "sum_weights2": sum(w*w for w in weights), "weight_scale": scale}],
                          "event_sources": [dict(iteration=i+1, file=filename, file_event_index=i+1,
                                                 original_event_number=7) for i in range(12)],
                          "colliders": [dict(name="c", cross_section_fb=5000, n_events=12)]},
                  "analyses": {"fixture": {"collider": "c", "luminosity": 10,
                     "signal_regions": {"SR": dict(accepted_event_ids=[1, 3], n_sig_MC=sum(chosen),
                         n_sig_MC_sumw2=sum(w*w for w in chosen), n_sig_MC_stat=math.sqrt(sum(w*w for w in chosen)),
                         n_sig_scaled=factor*sum(chosen), n_sig_scaled_err=factor*math.sqrt(sum(w*w for w in chosen)))}}}}
        return result, card

    def test_oracle_detects_wrong_variance_normalization_and_event_loss(self):
        result, card = self.oracle_fixture()
        acceptance.check_oracle(result, card)
        for field in ("n_sig_MC", "n_sig_MC_stat", "n_sig_MC_sumw2", "n_sig_scaled", "n_sig_scaled_err"):
            broken = copy.deepcopy(result)
            broken["analyses"]["fixture"]["signal_regions"]["SR"][field] *= 2
            with self.subTest(field=field), self.assertRaises(AssertionError):
                acceptance.check_oracle(broken, card)
        broken = copy.deepcopy(result); broken["run"]["input_files"][0]["weight_scale"] *= 2
        with self.assertRaises(AssertionError): acceptance.check_oracle(broken, card)
        broken = copy.deepcopy(result); broken["run"]["event_sources"].pop()
        with self.assertRaises(AssertionError): acceptance.check_oracle(broken, card)

    def test_preparation_never_overwrites_an_existing_suite(self):
        with self.assertRaises(FileExistsError):
            acceptance.prepare(self.directory / "suite", self.source, 12, self.template)


if __name__ == "__main__":
    unittest.main()
