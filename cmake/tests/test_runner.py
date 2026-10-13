#!/usr/bin/env python3
"""Exercise the unified runner using temporary fixture suites, never real ones."""

import contextlib
import io
import json
import os
from pathlib import Path
import sys
import tempfile
import time
import unittest
from unittest import mock

import run_tests as runner


class RunnerTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-runner-fixture-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.suites = self.root / "suite files with spaces"
        self.suites.mkdir()
        self.logs = self.root / "retained logs"
        self.run_number = 0

    def suite(self, name, source, requirements=()):
        path = self.suites / name
        path.write_text(source)
        return runner.Suite(path, requirements)

    def run_suites(self, suites, **options):
        self.run_number += 1
        self.logs = self.root / f"retained logs {self.run_number}"
        output = io.StringIO()
        with contextlib.redirect_stdout(output):
            result = runner.run(suites, self.logs, **options)
        summary = json.loads((self.logs / "summary.json").read_text())
        return result, summary, output.getvalue()

    def test_inventory_discovers_python_and_policy_but_not_runner(self):
        for name in ("run_tests.py", "__init__.py", "test_runner.py", "new_suite.py",
                     "cxx_standard.cmake", "helper.cmake", "notes.txt"):
            (self.suites / name).write_text("raise RuntimeError('must never import')")
        self.assertEqual([suite.path.name for suite in runner.inventory(self.suites)],
                         ["cxx_standard.cmake", "new_suite.py", "test_runner.py"])
        self.assertEqual(runner.inventory(self.suites)[-1].requirements, ())

    def test_policy_suite_remains_required_when_its_file_is_missing(self):
        self.suite("test_runner.py", "pass\n")
        suites = runner.inventory(self.suites)
        self.assertEqual([suite.path.name for suite in suites], ["cxx_standard.cmake", "test_runner.py"])
        self.assertFalse(suites[0].path.exists())
        self.assertEqual(suites[0].requirements, ("cmake",))

    def test_list_never_looks_up_tools_executes_suites_or_creates_logs(self):
        self.suite("probe.py", "raise RuntimeError('suite was executed')")
        with mock.patch.object(runner.shutil, "which", side_effect=AssertionError("tool probe")), \
             mock.patch.object(runner.subprocess, "Popen", side_effect=AssertionError("execution")), \
             mock.patch.object(runner.tempfile, "mkdtemp", side_effect=AssertionError("temporary write")), \
             contextlib.redirect_stdout(io.StringIO()) as output:
            result = runner.main(["--list", "--log-dir", str(self.logs), "--cmake", "missing"], self.suites)
        self.assertEqual(result, 0)
        self.assertIn("probe.py (requires: cmake)", output.getvalue())
        self.assertFalse(self.logs.exists())

    def test_existing_log_directory_is_rejected_without_changing_evidence(self):
        self.logs.mkdir()
        evidence = self.logs / "prior-failure.log"
        evidence.write_text("previous failure output")
        before = evidence.stat().st_mtime_ns, evidence.read_bytes()
        self.suite("test_runner.py", "raise RuntimeError('must not execute')")
        with mock.patch.object(runner.subprocess, "Popen", side_effect=AssertionError("execution")), \
             contextlib.redirect_stderr(io.StringIO()) as output:
            result = runner.main(["--log-dir", str(self.logs)], self.suites)
        self.assertEqual(result, 2)
        self.assertIn("choose a fresh --log-dir", output.getvalue())
        self.assertEqual((evidence.stat().st_mtime_ns, evidence.read_bytes()), before)
        self.assertEqual(list(self.logs.iterdir()), [evidence])

    def test_default_log_directory_is_new_and_retained(self):
        captured = []
        def execute(suites, directory, timeout, cmake):
            self.assertFalse(directory.exists())
            self.assertTrue(directory.parent.is_dir())
            directory.mkdir()
            captured.append(directory)
            return 0
        with mock.patch.object(runner, "run", side_effect=execute):
            self.assertEqual(runner.main([], self.suites), 0)
        self.assertTrue(captured[0].is_dir())
        captured[0].rmdir()
        captured[0].parent.rmdir()

    def test_subprocess_uses_current_python_no_bytecode_temp_cwd_and_eof_stdin(self):
        suite = self.suite("context.py", '''
import json, os, sys
from pathlib import Path
Path('relative-output').write_text('temporary only')
print(json.dumps({'python': sys.executable, 'cwd': os.getcwd(),
                  'bytecode': sys.dont_write_bytecode,
                  'environment': os.environ.get('PYTHONDONTWRITEBYTECODE'),
                  'stdin': sys.stdin.read()}))
''')
        result, summary, _ = self.run_suites([suite])
        self.assertEqual(result, 0)
        record = summary["suites"][0]
        lines = Path(record["log"]).read_text().splitlines()
        context = json.loads(next(line for line in lines if line.startswith("{\"python\"")))
        self.assertEqual(context["python"], sys.executable)
        self.assertTrue(context["bytecode"])
        self.assertEqual(context["environment"], "1")
        self.assertEqual(context["stdin"], "")
        self.assertNotEqual(context["cwd"], str(self.suites))
        self.assertFalse(Path(context["cwd"]).exists())
        self.assertFalse((self.suites / "relative-output").exists())
        self.assertFalse((self.suites / "__pycache__").exists())

    def test_failure_retains_all_output_and_continues_other_suites(self):
        fail = self.suite("failure.py", "import sys\nprint('FIRST')\nprint('x' * 50000)\n"
                          "print('LAST', file=sys.stderr)\nsys.exit(9)\n")
        passed = self.suite("pass.py", "print('following suite ran')\n")
        result, summary, _ = self.run_suites([fail, passed])
        self.assertEqual(result, 1)
        self.assertEqual([s["status"] for s in summary["suites"]], ["FAIL", "PASS"])
        self.assertEqual(summary["failed"], 1)
        self.assertEqual(summary["suites"][0]["returncode"], 9)
        log = Path(summary["suites"][0]["log"]).read_text()
        self.assertIn("FIRST", log)
        self.assertIn("x" * 50000, log)
        self.assertIn("LAST", log)

    def test_missing_cmake_skips_required_suite_and_fails_aggregate(self):
        required = self.suite("requires.py", "raise RuntimeError('must not run')", ("cmake",))
        passed = self.suite("independent.py", "print('independent suite ran')")
        result, summary, output = self.run_suites([required, passed], cmake=str(self.root / "absent-cmake"))
        self.assertEqual(result, 1)
        self.assertEqual(summary["skipped"], 1)
        self.assertEqual(summary["passed"], 1)
        self.assertEqual(summary["status"], "FAIL")
        self.assertIn("missing prerequisite", output)
        self.assertIn("absent-cmake", Path(summary["suites"][0]["log"]).read_text())

    def test_missing_extra_tool_is_not_silently_passed(self):
        suite = self.suite("requires.py", "raise RuntimeError('must not run')", ("absent-fixture-tool",))
        result, summary, _ = self.run_suites([suite])
        self.assertEqual(result, 1)
        self.assertEqual(summary["suites"][0]["status"], "SKIP")
        self.assertIn("absent-fixture-tool", summary["suites"][0]["reason"])

    @unittest.skipUnless(os.name == "posix", "supported runner hosts use POSIX process groups")
    def test_cmake_override_reaches_both_policy_and_python_path_lookup(self):
        fake = self.root / "selected tools" / "selected-cmake"
        fake.parent.mkdir()
        fake.write_text("#!" + sys.executable + "\nimport sys\nprint('SELECTED CMAKE', sys.argv[1:])\n")
        fake.chmod(0o755)
        policy = self.suite("cxx_standard.cmake", "# fake policy", ("cmake",))
        python = self.suite("lookup.py", "import shutil, subprocess\n"
                            "subprocess.run([shutil.which('cmake'), 'PATH-CHECK'], check=True)\n", ("cmake",))
        result, summary, _ = self.run_suites([policy, python], cmake=str(fake))
        self.assertEqual(result, 0)
        for record in summary["suites"]:
            self.assertIn("SELECTED CMAKE", Path(record["log"]).read_text())
        self.assertIn("'-P'", Path(summary["suites"][0]["log"]).read_text())
        self.assertIn("PATH-CHECK", Path(summary["suites"][1]["log"]).read_text())

    @unittest.skipUnless(os.name == "posix", "supported runner hosts use POSIX process groups")
    def test_timeout_kills_descendants_preserves_output_and_continues(self):
        marker = self.root / "descendant-survived"
        child = "import time; from pathlib import Path; time.sleep(0.7); Path(" + repr(str(marker)) + ").write_text('bad')"
        slow = self.suite("timeout.py", "import subprocess, sys, time\n"
                          "subprocess.Popen([sys.executable, '-c', " + repr(child) + "])\n"
                          "print('before timeout', flush=True)\ntime.sleep(30)\n")
        passed = self.suite("after.py", "print('ran after timeout')\n")
        result, summary, _ = self.run_suites([slow, passed], timeout=0.25)
        self.assertEqual(result, 1)
        self.assertEqual([s["status"] for s in summary["suites"]], ["TIMEOUT", "PASS"])
        log = Path(summary["suites"][0]["log"]).read_text()
        self.assertIn("before timeout", log)
        self.assertIn("timeout after", log)
        time.sleep(0.8)
        self.assertFalse(marker.exists(), "descendant escaped the suite timeout")

    def test_execution_error_is_reported_and_empty_inventory_cannot_pass(self):
        suite = self.suite("pass.py", "pass\n")
        with mock.patch.object(runner.subprocess, "Popen", side_effect=OSError("fixture execution denied")):
            result, summary, _ = self.run_suites([suite])
        self.assertEqual(result, 1)
        self.assertEqual(summary["suites"][0]["status"], "ERROR")
        self.assertIn("fixture execution denied", Path(summary["suites"][0]["log"]).read_text())
        result, summary, _ = self.run_suites([])
        self.assertEqual(result, 1)
        self.assertEqual(summary["status"], "FAIL")

    def test_cli_rejects_invalid_timeout_and_respects_cmake_environment_default(self):
        for value in ("0", "-1", "nan", "inf", "invalid"):
            with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as raised:
                runner.main(["--timeout", value], self.suites)
            self.assertEqual(raised.exception.code, 2)
        self.suite("test_runner.py", "pass\n")
        with mock.patch.dict(os.environ, {"CMAKE_COMMAND": "/selected/from/environment"}), \
             mock.patch.object(runner, "run", return_value=0) as execute:
            self.assertEqual(runner.main(["--log-dir", str(self.logs)], self.suites), 0)
        self.assertEqual(execute.call_args.args[-1], "/selected/from/environment")


if __name__ == "__main__":
    unittest.main(verbosity=2)
