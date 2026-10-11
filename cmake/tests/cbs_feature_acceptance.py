#!/usr/bin/env python3
"""Check the acceptance runner using temporary files and captured commands only."""

import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location(
    "acceptance", ROOT / "cmake/scripts/cbs_feature_acceptance.py")
acceptance = importlib.util.module_from_spec(spec)
spec.loader.exec_module(acceptance)


def build_log(objects=(), links=()):
    return "".join("[ 50%] Building CXX object " + p + "\n" for p in sorted(objects)) + \
        "".join("[100%] Linking CXX " + ("executable " if p == "CBS" else "shared library ")
                + "/path with spaces/" + p + "\n" for p in sorted(links)) + \
        "[100%] Built target CBS\n"


class AcceptanceTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="cbs-acceptance-fixture-")
        self.root = Path(self.temporary.name) / "source with spaces"
        self.root.mkdir()
        self.cache = {name: "/fixture/" + name for name in acceptance.IDENTITY}
        self.cache.update(CBS_BUILD_PRESET="cbs-llvm", CMAKE_GENERATOR="Unix Makefiles",
                          WITH_ONNXRUNTIME="ON", WITH_RESTFRAMES="ON")
        self.calls = []
        for name in acceptance.FLAGS:
            self.put("build/CMakeFiles/" + name + ".dir/flags.make", "stable flags")
        for name in acceptance.SHARED_LINKS:
            self.put(name, "/fixture/clang++ -o /fixture/libgambit_preload.dylib")
        self.put("cmake/include/gambit/cmake/cmake_variables.hpp", "stable common header")
        for _, _, package in acceptance.FEATURES:
            for directory in ("include" if package.startswith("onnx") else "inc", "lib"):
                self.put("contrib/" + package + "/" + directory + "/kept", "installed")
        self.features(True, True)

    def tearDown(self):
        self.temporary.cleanup()

    def put(self, name, content):
        path = self.root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content)
        return path

    def features(self, onnx, rest):
        link = ["/fixture/clang++", "-o", str(self.root / "CBS")]
        for (macro, library, package), enabled in zip(acceptance.FEATURES, (onnx, rest)):
            self.cache["WITH_" + macro] = "ON" if enabled else "OFF"
            self.put("cmake/include/gambit/cmake/" + macro.lower() + "_variables.hpp",
                     ("/* #undef EXCLUDE_" + macro + " */\n" if enabled else
                      "#define EXCLUDE_" + macro + "\n"))
            if enabled:
                link += ["-l" + library, "-Wl,-rpath," + str(self.root / "contrib" / package / "lib")]
        self.put("build/CMakeFiles/CBS.dir/link.txt", " ".join(
            "'" + word + "'" for word in link))
        self.put("build/CMakeCache.txt", "".join(k + ":STRING=" + v + "\n"
                                               for k, v in self.cache.items()))

    def captured_command(self, command, root, logfile):
        # No command received here is executed, including a real CMake path.
        self.assertEqual(root, self.root)
        self.assertNotIn("--fresh", command)
        self.calls.append(command)
        if "--preset" in command:
            values = {v.split("=", 1)[0]: v.split("=", 1)[1] for v in command if v.startswith("-D")}
            self.features(values["-DWITH_ONNXRUNTIME"] == "ON",
                          values["-DWITH_RESTFRAMES"] == "ON")
            text = "-- Configuring done\n"
        elif command[-1] == "--help":
            text = "Usage: ./CBS [options]\n"
        else:
            phase = logfile.stem
            objects = (acceptance.ONNX_OBJECTS if phase.startswith("onnx") else
                       acceptance.REST_OBJECTS if phase.startswith("restframes") else set())
            links = ({"CBS", "libgambit_preload.dylib"} if phase.startswith("restframes") else
                     {"CBS"} if phase.startswith("onnx") else set())
            text = build_log(objects, links)
        logfile.write_text(text)
        return text

    def execute(self, command=None):
        self.logs = self.root.parent / "logs"
        self.stdout, self.stderr = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(self.stdout), contextlib.redirect_stderr(self.stderr):
            return acceptance.run(self.root, self.logs, 8, command or self.captured_command)

    def test_full_sequence_restores_on_and_records_four_scopes_and_noop(self):
        self.assertEqual(self.execute(), 0)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertEqual(summary["status"], "PASS")
        self.assertEqual([len(c["objects"]) for c in summary["cases"]], [3, 3, 6, 6, 0])
        self.assertEqual(len(self.calls), 13)  # Four configure/build/help plus final build.
        self.assertEqual(len(summary["command_seconds"]), 13)
        self.assertTrue((self.logs / "final-noop-snapshot.json").is_file())
        self.assertEqual(self.cache["WITH_ONNXRUNTIME"], "ON")
        self.assertEqual(self.cache["WITH_RESTFRAMES"], "ON")

    def test_preflight_rejects_other_cache_before_creating_logs_or_commands(self):
        self.features(False, True)
        with self.assertRaisesRegex(acceptance.AcceptanceError, "WITH_ONNXRUNTIME"):
            self.execute()
        self.assertFalse(self.logs.exists())
        self.assertEqual(self.calls, [])

    def test_unexpected_object_fails_and_stops_before_the_next_switch(self):
        def command(argv, root, path):
            text = self.captured_command(argv, root, path)
            if path.name == "onnx-off-build.log":
                text = build_log(acceptance.ONNX_OBJECTS | {"unexpected.cpp.o"}, {"CBS"})
                path.write_text(text)
            return text
        self.assertEqual(self.execute(command), 1)
        self.assertEqual(len(self.calls), 2)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertIn("Unexpected compiled objects", summary["error"])

    def test_hash_mtime_and_deleted_install_files_are_all_detected(self):
        before = acceptance.snapshot(self.root)
        path = self.root / "contrib/onnxruntime-1.14.1/lib/kept"
        stat = path.stat()
        os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns + 1_000_000))
        with self.assertRaisesRegex(acceptance.AcceptanceError, "content/mtime"):
            acceptance.check_snapshot(before, acceptance.snapshot(self.root))
        path.write_text("different")
        os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
        with self.assertRaisesRegex(acceptance.AcceptanceError, "content/mtime"):
            acceptance.check_snapshot(before, acceptance.snapshot(self.root))
        path.unlink()
        with self.assertRaisesRegex(acceptance.AcceptanceError, "Missing installed"):
            acceptance.snapshot(self.root)

    def test_duplicate_links_and_external_or_generation_work_are_rejected(self):
        for extra in ("[100%] Linking CXX executable CBS\n",
                      "Performing build step for 'rivet'\n",
                      "Generating modules_harvested\n"):
            with self.subTest(extra=extra), self.assertRaises(acceptance.AcceptanceError):
                acceptance.check_build(build_log((), ()) + extra, set(), set())
        colored = "\x1b[32m" + build_log(acceptance.ONNX_OBJECTS, {"CBS"}) + "\x1b[0m"
        self.assertTrue(acceptance.check_build(colored, acceptance.ONNX_OBJECTS, {"CBS"})["success"])
        with self.assertRaisesRegex(acceptance.AcceptanceError, "Unexpected links"):
            acceptance.check_build(build_log((), {"CBS"}) + "Linking CXX executable CBS\n",
                                   set(), {"CBS"})

    def test_user_rpath_can_remain_off_but_wrong_library_and_header_fail(self):
        self.features(False, True)
        directory = str(self.root / "contrib/onnxruntime-1.14.1/lib")
        path = self.root / "build/CMakeFiles/CBS.dir/link.txt"
        path.write_text(path.read_text() + " '-Wl,-rpath," + directory + "'")
        acceptance.check_features(self.root, False, True, [directory])
        with self.assertRaises(acceptance.AcceptanceError):
            acceptance.check_features(self.root, False, True, [])
        path.write_text(path.read_text() + " -lonnxruntime")
        with self.assertRaisesRegex(acceptance.AcceptanceError, "Wrong CBS link item"):
            acceptance.check_features(self.root, False, True, [directory])
        self.features(False, True)
        self.put("cmake/include/gambit/cmake/onnxruntime_variables.hpp",
                 "/* #undef EXCLUDE_ONNXRUNTIME */\n")
        with self.assertRaisesRegex(acceptance.AcceptanceError, "Feature header"):
            acceptance.check_features(self.root, False, True, [])
        self.features(True, True)
        self.put("cmake/include/gambit/cmake/onnxruntime_variables.hpp", "truncated\n")
        with self.assertRaisesRegex(acceptance.AcceptanceError, "Feature header"):
            acceptance.check_features(self.root, True, True, [])

    def test_failed_build_stops_with_failure_report_and_manual_restore(self):
        def command(argv, root, path):
            text = self.captured_command(argv, root, path)
            if path.name == "onnx-off-build.log":
                raise acceptance.AcceptanceError("Command exited 2; see " + str(path))
            return text
        self.assertEqual(self.execute(command), 1)
        self.assertEqual(len(self.calls), 2)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertEqual(summary["status"], "FAIL")
        self.assertEqual(summary["failed_case"], "onnx-off")
        self.assertIn("exited 2", summary["error"])
        self.assertEqual(self.cache["WITH_ONNXRUNTIME"], "OFF")
        self.assertTrue((self.logs / "onnx-off-build.log").is_file())
        self.assertIn("-DWITH_ONNXRUNTIME=ON -DWITH_RESTFRAMES=ON", self.stderr.getvalue())
        self.assertIn("cd '" + str(self.root) + "'", self.stderr.getvalue())

    def test_toolchain_change_stops_before_any_build(self):
        def command(argv, root, path):
            text = self.captured_command(argv, root, path)
            if "--preset" in argv:
                self.cache["CMAKE_CXX_COMPILER"] = "/unexpected/clang++"
                self.features(False, True)
            return text
        self.assertEqual(self.execute(command), 1)
        self.assertEqual(len(self.calls), 1)
        self.assertIn("identity changed", (self.logs / "summary.json").read_text())

    def test_existing_logs_are_preserved_without_executing_commands(self):
        logs = self.root.parent / "logs"
        logs.mkdir()
        sentinel = logs / "summary.json"
        sentinel.write_text("previous result")
        with self.assertRaises(FileExistsError):
            self.execute()
        self.assertEqual(sentinel.read_text(), "previous result")
        self.assertEqual(self.calls, [])

    def test_unrelated_link_mutation_fails_before_loader_or_next_switch(self):
        def command(argv, root, path):
            text = self.captured_command(argv, root, path)
            if path.name == "onnx-off-build.log":
                self.put(acceptance.SHARED_LINKS[0], "unexpected link flags")
            return text
        self.assertEqual(self.execute(command), 1)
        self.assertEqual(len(self.calls), 2)
        self.assertIn("first.dir/link.txt", (self.logs / "summary.json").read_text())

    def test_missing_loader_usage_stops_before_the_next_switch(self):
        def command(argv, root, path):
            text = self.captured_command(argv, root, path)
            if argv[-1] == "--help":
                text = "incomplete startup\n"
                path.write_text(text)
            return text
        self.assertEqual(self.execute(command), 1)
        self.assertEqual(len(self.calls), 3)
        self.assertIn("did not print usage", (self.logs / "summary.json").read_text())

    def test_work_in_the_final_noop_fails_after_four_successful_switches(self):
        def command(argv, root, path):
            text = self.captured_command(argv, root, path)
            if path.name == "final-noop.log":
                text = build_log((), {"CBS"})
                path.write_text(text)
            return text
        self.assertEqual(self.execute(command), 1)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertEqual(summary["failed_case"], "final-noop")
        self.assertEqual(len(summary["cases"]), 4)
        self.assertEqual(self.cache["WITH_ONNXRUNTIME"], "ON")
        self.assertEqual(self.cache["WITH_RESTFRAMES"], "ON")

    def test_failed_process_exit_is_reported_with_output_log(self):
        logfile = self.root / "command.log"
        # Only Python prints fixture output and exits; no compiler/build tool.
        with contextlib.redirect_stdout(io.StringIO()), self.assertRaisesRegex(
                acceptance.AcceptanceError, "exited 17"):
            acceptance.run_command([sys.executable, "-c", "print('fixture');raise SystemExit(17)"],
                                   self.root, logfile)
        self.assertEqual(logfile.read_text(), "fixture\n")

    def test_default_cli_does_not_run_or_create_any_build_state(self):
        before = acceptance.snapshot(self.root)
        result = subprocess.run([sys.executable, "-B", str(ROOT / "cmake/scripts/cbs_feature_acceptance.py")],
                                capture_output=True, text=True, cwd=self.root)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("--run", result.stdout)
        self.assertEqual(self.calls, [])
        acceptance.check_snapshot(before, acceptance.snapshot(self.root))


if __name__ == "__main__":
    unittest.main(verbosity=2)
