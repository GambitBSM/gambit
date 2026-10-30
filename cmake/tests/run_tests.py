#!/usr/bin/env python3
"""Run the CMake regression suites without configuring or building GAMBIT.

Suites use script-mode CMake or isolated fixtures (including a LANGUAGES NONE
project). They need Python's standard library, CMake, and the tools listed by
--list; no compiler, installed backend, or network access is required.
"""

import argparse
from dataclasses import dataclass
import json
import math
import os
from pathlib import Path
import shutil
import signal
import subprocess
import sys
import tempfile
import time


TEST_DIR = Path(__file__).resolve().parent
# Other Python suites exercise CMake. Keep exceptions/prerequisites explicit so
# a unittest skip (notably validation_cache's missing CMake) is never a pass.
REQUIREMENTS = {
    "cbs_feature_acceptance.py": (),
    "preset_build_acceptance.py": (),
    "test_runner.py": (),
    "source_download.py": ("cmake", "sh"),
    "rivet_installation.py": ("cmake", "sh", "patch"),
    "code_generation.py": ("cmake", "make"),
    "preset_dependencies.py": ("cmake", "make"),
    "restframes_build_identity.py": ("cmake", "git"),
    "restframes_scope.py": ("cmake", "git"),
    "onnxruntime_scope.py": ("cmake", "git"),
    "merge_compatibility.py": ("cmake", "sh", "chmod"),
}


@dataclass(frozen=True)
class Suite:
    path: Path
    requirements: tuple = ("cmake",)


def inventory(tests_dir=TEST_DIR):
    """Discover suite files without importing tests or looking up executables."""
    suites = [Suite(path.resolve(), REQUIREMENTS.get(path.name, ("cmake",)))
              for path in tests_dir.glob("*.py")
              if path.name not in ("run_tests.py", "__init__.py")]
    policy = tests_dir / "cxx_standard.cmake"
    # This policy suite is mandatory: deleting it must not shrink a green run.
    suites.append(Suite(policy.resolve()))
    return sorted(suites, key=lambda suite: suite.path.name)


def positive_timeout(value):
    try:
        timeout = float(value)
    except ValueError:
        raise argparse.ArgumentTypeError("timeout must be a positive number")
    if not math.isfinite(timeout) or timeout <= 0:
        raise argparse.ArgumentTypeError("timeout must be a positive finite number")
    return timeout


def stop_process(process):
    """Kill the entire suite process group on supported macOS/Linux hosts."""
    try:
        if os.name == "posix":
            os.killpg(process.pid, signal.SIGKILL)
        else:
            process.kill()
    except ProcessLookupError:
        pass
    process.wait()


def execute_suite(suite, command, environment, timeout, log):
    started = time.monotonic()
    status, returncode = "ERROR", None
    # A default-relative CMake/Python write cannot reach the repository build.
    with tempfile.TemporaryDirectory(prefix="gambit-test-work-") as work:
        with log.open("w", encoding="utf-8") as stream:
            stream.write("Command: " + json.dumps(command) + "\n")
            stream.write("Working directory: " + work + "\n\n")
            stream.flush()
            try:
                process = subprocess.Popen(command, cwd=work, env=environment,
                                           stdin=subprocess.DEVNULL, stdout=stream,
                                           stderr=subprocess.STDOUT,
                                           start_new_session=os.name == "posix")
                try:
                    returncode = process.wait(timeout=timeout)
                    status = "PASS" if returncode == 0 else "FAIL"
                except subprocess.TimeoutExpired:
                    stop_process(process)
                    returncode = process.returncode
                    status = "TIMEOUT"
                    stream.write(f"\nRunner: timeout after {timeout:g} seconds.\n")
                except BaseException:
                    stop_process(process)
                    raise
            except OSError as error:
                stream.write("\nRunner: cannot execute suite: " + str(error) + "\n")
    return {"suite": suite.path.name, "status": status, "returncode": returncode,
            "seconds": round(time.monotonic() - started, 3), "log": str(log)}


def run(suites, log_dir, timeout=120, cmake="cmake"):
    log_dir = log_dir.resolve()
    # Never truncate the evidence from an earlier run, including failed runs.
    log_dir.mkdir(parents=True, exist_ok=False)
    environment = os.environ.copy()
    environment["PYTHONDONTWRITEBYTECODE"] = "1"
    path = environment.get("PATH", "")
    selected_cmake = shutil.which(cmake, path=path)
    if selected_cmake:
        selected_cmake = str(Path(selected_cmake).resolve())
    tools = {tool: shutil.which(tool, path=path)
             for tool in {tool for suite in suites for tool in suite.requirements}
             if tool != "cmake"}
    tools["cmake"] = selected_cmake
    print("Logs: " + str(log_dir), flush=True)
    results = []
    # Existing suites find 'cmake' on PATH. A temporary alias keeps --cmake and
    # CMAKE_COMMAND selections consistent without changing those suites.
    with tempfile.TemporaryDirectory(prefix="gambit-test-tools-") as aliases:
        if selected_cmake:
            alias = Path(aliases) / ("cmake.exe" if os.name == "nt" else "cmake")
            alias.symlink_to(Path(selected_cmake).resolve())
            environment["PATH"] = aliases + os.pathsep + path
        for suite in suites:
            log = log_dir / (suite.path.name + ".log")
            missing = [tool for tool in suite.requirements if not tools.get(tool)]
            if missing:
                reason = "missing prerequisite: " + ", ".join(
                    cmake if tool == "cmake" else tool for tool in missing)
                log.write_text("Suite not executed: " + reason + "\n", encoding="utf-8")
                result = {"suite": suite.path.name, "status": "SKIP", "returncode": None,
                          "seconds": 0, "log": str(log), "reason": reason}
            else:
                command = ([sys.executable, "-B", str(suite.path)]
                           if suite.path.suffix == ".py" else
                           [selected_cmake, "-P", str(suite.path)])
                result = execute_suite(suite, command, environment, timeout, log)
            results.append(result)
            detail = result.get("reason", f"{result['seconds']:.3f}s")
            print(f"{result['status']:7} {suite.path.name} ({detail})", flush=True)
            if result["status"] != "PASS":
                print("        " + str(log), flush=True)
    passed = sum(result["status"] == "PASS" for result in results)
    skipped = sum(result["status"] == "SKIP" for result in results)
    failed = len(results) - passed - skipped
    success = bool(results) and passed == len(results)
    summary = {"status": "PASS" if success else "FAIL", "passed": passed,
               "failed": failed, "skipped": skipped, "suites": results}
    (log_dir / "summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(f"Suites: {passed} passed, {failed} failed, {skipped} skipped.", flush=True)
    return 0 if success else 1


def main(argv=None, tests_dir=TEST_DIR):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--list", action="store_true", help="list suites and prerequisites without running probes")
    parser.add_argument("--log-dir", type=Path,
                        help="retain suite logs in a fresh directory (default: new temporary logs)")
    parser.add_argument("--timeout", type=positive_timeout, default=120,
                        help="timeout in seconds for each suite (default: 120)")
    parser.add_argument("--cmake", default=os.environ.get("CMAKE_COMMAND", "cmake"),
                        help="CMake executable name or path (default: CMAKE_COMMAND or cmake)")
    args = parser.parse_args(argv)
    suites = inventory(tests_dir)
    if args.list:
        for suite in suites:
            requirements = ", ".join(suite.requirements) or "Python standard library"
            print(f"{suite.path.name} (requires: {requirements})")
        return 0
    log_dir = args.log_dir or Path(tempfile.mkdtemp(prefix="gambit-cmake-tests-")) / "logs"
    try:
        return run(suites, log_dir, args.timeout, args.cmake)
    except FileExistsError:
        print("Runner: log directory already exists; choose a fresh --log-dir: "
              + str(log_dir), file=sys.stderr)
        return 2
    except OSError as error:
        print("Runner: " + str(error), file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
