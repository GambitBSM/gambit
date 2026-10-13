#!/usr/bin/env python3
"""Accept the Linux GNU CBS baseline in an explicitly fresh independent checkout.

Default invocation prints a plan only. --run --fresh-checkout authorizes one
initial fresh configure, then builds, startup checks and two no-op checks. The
checkout must have no build tree or native binaries. No cleaning is performed.
"""

import argparse
import hashlib
import json
import math
import os
from pathlib import Path
import re
import shlex
import shutil
import signal
import subprocess
import sys
import tempfile
import threading
import time


ROOT = Path(__file__).resolve().parents[2]
FEATURES = {
    "CMAKE_BUILD_TYPE": "Release", "CMAKE_CXX_STANDARD": "17",
    "WITH_ROOT": "OFF", "WITH_RESTFRAMES": "OFF", "WITH_MPI": "OFF",
    "WITH_ONNXRUNTIME": "ON", "WITH_HDF5": "ON", "WITH_SQLite3": "ON",
    "CBS_WITH_RIVET_CONTUR": "OFF",
    "CUTFLOW": "ON",
}
IDENTITY_KEYS = ("CBS_BUILD_PRESET", "CMAKE_GENERATOR", "CMAKE_BUILD_TYPE",
                 "CMAKE_CXX_STANDARD", "CMAKE_CXX_EXTENSIONS", "CMAKE_HOME_DIRECTORY",
                 "CMAKE_C_COMPILER", "CMAKE_CXX_COMPILER", "CMAKE_Fortran_COMPILER",
                 "CMAKE_C_FLAGS", "CMAKE_CXX_FLAGS", "CMAKE_Fortran_FLAGS",
                 "CMAKE_TOOLCHAIN_FILE", "CMAKE_MAKE_PROGRAM", "Python3_EXECUTABLE",
                 "pybind11_DIR", "Bits", *FEATURES)
AUDITED_PACKAGES = {"restframes", "hepmc", "yoda", "onnxruntime", "fastjet", "fjcontrib", "nulike_1.0.9",
                    "rivet_4.1.0", "contur_3.0.0"}
NATIVE_TARGETS = {"CBS", "CBS_objects", "ColliderBit", "Logs", "Utils", "Models",
                  "Backends", "Elements", "Printers", "mkpath", "multimin",
                  "fjcontrib_nsubjettiness", "METSignificance", "yaml-cpp",
                  "first", "fortran", "FarrayTest", "gambit_preload", "cbs_preload"}
GENERATED = (
    "cmake/include/gambit/cmake/cmake_variables.hpp",
    "cmake/include/gambit/cmake/restframes_variables.hpp",
    "cmake/include/gambit/cmake/onnxruntime_variables.hpp",
    "Core/include/gambit/Core/module_rollcall.hpp",
    "Elements/include/gambit/Elements/module_types_rollcall.hpp",
    "Elements/include/gambit/Elements/module_functor_types.hpp",
    "Backends/include/gambit/Backends/backend_functor_types.hpp",
    "Backends/include/gambit/Backends/backend_rollcall.hpp",
    "Backends/include/gambit/Backends/backend_types_rollcall.hpp",
    "Models/include/gambit/Models/model_rollcall.hpp",
    "Models/include/gambit/Models/model_types_rollcall.hpp",
    "Printers/include/gambit/Printers/printer_rollcall.hpp",
    "ColliderBit/include/gambit/ColliderBit/ColliderBit_models_rollcall.hpp",
    "ColliderBit/include/gambit/ColliderBit/colliders/Pythia8/Py8Collider_typedefs.hpp",
    "ScannerBit/include/gambit/ScannerBit/priors_rollcall.hpp",
    "Models/src/particle_database.cpp", "ColliderBit/examples/functors_for_CBS.cpp",
    "config/gambit_bits.yaml", "config/gambit_backend_interfaces.yaml",
    "scratch/build_time/harvested_types.pickle",
    *("build/" + name + "_harvested" for name in
      ("modules", "backends", "models", "printers", "colliders")),
    "build/functors_for_CBS.stamp",
)
NATIVE_BINARIES = ("CBS", "Backends/examples/libfirst.so", "Backends/examples/libfortran.so",
                   "Backends/examples/libFarrayTest.so", "build/contrib/libgambit_preload.so",
                   "build/contrib/libcbs_preload.so")
DEPENDENCIES = (
    ("contrib/HepMC3-3.2.5/local", "libHepMC3.so*"),
    ("contrib/YODA-2.1.0/local", "libYODA.so*"),
    ("contrib/fastjet-3.5.1/local", "libfastjet.so*"),
    ("contrib/onnxruntime-1.14.1", "libonnxruntime.so*"),
    ("Backends/installed/nulike/1.0.9", "libnulike.so"),
)
EXTERNAL_WORKSPACES = ("contrib/HepMC3-3.2.5", "contrib/YODA-2.1.0",
                       "contrib/fastjet-3.5.1", "contrib/fjcontrib-1.101",
                       "contrib/onnxruntime-1.14.1", "Backends/installed/nulike/1.0.9")


class AcceptanceError(RuntimeError):
    pass


def require(condition, message):
    if not condition:
        raise AcceptanceError(message)


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n", encoding="utf-8")


def positive(value):
    number = float(value)
    if not math.isfinite(number) or number <= 0:
        raise argparse.ArgumentTypeError("value must be positive and finite")
    return number


def commands(root, cmake, pybind11_dir, jobs):
    hint = str(pybind11_dir) if pybind11_dir else "<explicit pybind11 CMake directory>"
    configure = [cmake, "--preset", "cbs-gnu", "-G", "Unix Makefiles",
                 *("-D" + key + "=" + value for key, value in FEATURES.items()),
                 "-DPython3_EXECUTABLE=" + sys.executable, "-Dpybind11_DIR=" + hint]
    build = [cmake, "--build", "build", "--target", "CBS", "--parallel", str(jobs)]
    startup = [str(root / "CBS"), "--help"]
    return [("configure-fresh", configure + ["--fresh"]), ("build-first", build),
            ("startup-first", startup), ("build-direct-noop", build),
            ("configure-same", configure), ("build-configure-noop", build),
            ("startup-final", startup)]


def preset_contract(root):
    data = json.loads((root / "CMakePresets.json").read_text())
    presets = {preset["name"]: preset for preset in data["configurePresets"]}
    def resolve(name, parents=()):
        require(name in presets and name not in parents, "Invalid preset inheritance: " + name)
        current = presets[name]
        outputs = {"CMAKE_RUNTIME_OUTPUT_DIRECTORY", "CMAKE_LIBRARY_OUTPUT_DIRECTORY",
                   "CMAKE_ARCHIVE_OUTPUT_DIRECTORY", "GAMBIT_RUN_DIR"}
        require(not outputs.intersection(current.get("cacheVariables", {})),
                "Presets must preserve GAMBIT output defaults")
        inherited = current.get("inherits", [])
        inherited = [inherited] if isinstance(inherited, str) else inherited
        result = {}
        for parent in reversed(inherited):
            result.update(resolve(parent, parents + (name,)))
        result.update(current)
        return result
    preset = resolve("cbs-gnu")
    require(preset.get("binaryDir") == "${sourceDir}/build", "cbs-gnu must use ${sourceDir}/build")
    require(preset.get("generator", "Unix Makefiles") == "Unix Makefiles",
            "First acceptance requires Unix Makefiles")


def preflight(root, fresh_checkout, pybind11_dir, jobs, timeout, host=None):
    require((host or sys.platform) == "linux", "This acceptance is restricted to Linux")
    require(fresh_checkout, "Actual execution requires --run --fresh-checkout in an independent checkout")
    require(jobs > 0 and math.isfinite(timeout) and timeout > 0, "Jobs and timeout must be positive")
    require((root / ".git").exists() and (root / "CMakeLists.txt").is_file(), "Requires a Git source checkout")
    require(not (root / "build").exists() and not (root / "build").is_symlink(),
            "Refusing an existing build tree; use an independent fresh checkout")
    require(not (root / "CMakeUserPresets.json").exists(), "Fresh acceptance cannot use CMakeUserPresets.json")
    for relative in NATIVE_BINARIES:
        require(not (root / relative).exists() and not (root / relative).is_symlink(),
                "Refusing existing native output: " + relative)
    for relative in EXTERNAL_WORKSPACES:
        require(not (root / relative).exists() and not (root / relative).is_symlink(),
                "Refusing existing external workspace/installation: " + relative)
    preset_contract(root)
    require(pybind11_dir is not None, "--pybind11-dir is required for actual execution")
    require((pybind11_dir / "pybind11Config.cmake").is_file(), "Missing hinted pybind11Config.cmake")
    version = (pybind11_dir / "pybind11ConfigVersion.cmake").read_text()
    match = re.search(r'set\(PACKAGE_VERSION\s+"?(\d+)\.(\d+)\.(\d+)', version)
    require(match and tuple(map(int, match.groups())) >= (2, 13, 6), "Hinted pybind11 must be at least 2.13.6")
    return ".".join(match.groups())


def stop_process(process):
    try:
        os.killpg(process.pid, signal.SIGKILL)
    except ProcessLookupError:
        pass
    process.wait()


def run_command(argv, root, logfile, timeout):
    print("+ " + shlex.join(argv), flush=True)
    environment = os.environ.copy()
    for key in ("PYTHONHOME", "PYTHONPATH"):
        environment.pop(key, None)
    environment.update(PYTHONDONTWRITEBYTECODE="1", GIT_TERMINAL_PROMPT="0")
    deadline = time.monotonic() + timeout
    with logfile.open("wb") as stream:
        process = subprocess.Popen(argv, cwd=root, env=environment, stdin=subprocess.DEVNULL,
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                   start_new_session=True)
        read_errors = []
        def pump():
            try:
                for block in iter(lambda: process.stdout.read1(65536), b""):
                    stream.write(block)
                    stream.flush()
            except OSError as error:
                read_errors.append(str(error))
        reader = threading.Thread(target=pump, daemon=True)
        reader.start()
        try:
            code = process.wait(timeout=timeout)
            reader.join(timeout=max(0, deadline - time.monotonic()))
            if reader.is_alive():
                raise subprocess.TimeoutExpired(argv, timeout)
        except (subprocess.TimeoutExpired, KeyboardInterrupt):
            stop_process(process)
            reader.join(timeout=5)
            stream.write(b"\nAcceptance: command/process-group timeout or interruption.\n")
            raise AcceptanceError("Command timed out or interrupted; see " + str(logfile))
        finally:
            if not reader.is_alive():
                process.stdout.close()
    require(code == 0, "Command exited " + str(code) + "; see " + str(logfile))
    require(not read_errors, "Could not preserve command output: " + repr(read_errors))
    return logfile.read_text(encoding="utf-8", errors="replace")


def cache_values(root):
    return dict(re.findall(r"^([^#/\n][^:\n]*):[^=\n]+=(.*)$",
                           (root / "build/CMakeCache.txt").read_text(), re.M))


def configure_report(text):
    text = re.sub(r"\x1b\[[0-9;]*m", "", text)
    labels = ("C compile/link", "C++17 compile/link", "Fortran compile/link", "OpenMP",
              "Python development", "Boost", "HDF5 C development", "CBS target")
    result = {}
    for label in (*labels, "SQLite3 development", "CBS environment"):
        values = re.findall(r"^--\s+" + re.escape(label) + r"\s*:\s*(.*?)\s*$", text, re.M)
        require(values, "Missing CBS validation: " + label)
        result[label] = values[-1]
    require(all(result[label] == "PASS" for label in labels) and result["CBS environment"] == "READY",
            "CBS environment checks failed: " + json.dumps(result))
    return result


def identity(root, pybind11_dir):
    cache = cache_values(root)
    for key, value in FEATURES.items():
        require(cache.get(key) == value, "Cached contract differs: " + key)
    require(cache.get("CBS_BUILD_PRESET") == "cbs-gnu", "Wrong cached CBS preset")
    require(cache.get("CMAKE_GENERATOR") == "Unix Makefiles", "Wrong generator")
    require(Path(cache.get("CMAKE_HOME_DIRECTORY", "")).resolve() == root, "Wrong source checkout in cache")
    require(Path(cache.get("Python3_EXECUTABLE", "")).absolute() == Path(sys.executable).absolute(),
            "Python interpreter differs from acceptance interpreter")
    require(Path(cache.get("pybind11_DIR", "")).resolve() == pybind11_dir.resolve(), "pybind11 hint not selected")
    compilers = {}
    for language in ("C", "CXX", "Fortran"):
        files = list((root / "build/CMakeFiles").glob("*/CMake" + language + "Compiler.cmake"))
        require(len(files) == 1, "Missing or ambiguous compiler identity: " + language)
        text = files[0].read_text()
        record = {}
        for field in ("COMPILER", "COMPILER_ID", "COMPILER_VERSION"):
            found = re.search(r'set\(CMAKE_' + language + '_' + field + r'\s+"([^\"]+)"\)', text)
            require(found, "Missing compiler field: " + language + "_" + field)
            record[field] = found.group(1)
        require(record["COMPILER_ID"] == "GNU", "Non-GNU compiler identity: " + language)
        require(Path(record["COMPILER"]).resolve() == Path(cache.get("CMAKE_" + language + "_COMPILER", "")).resolve(),
                "Compiler cache/record differ: " + language)
        compilers[language] = record
    for target in ("CBS", "CBS_objects", "ColliderBit"):
        files = [p for p in native_files(root) if p.name == "flags.make" and p.parent.name == target + ".dir"]
        flags = re.search(r'^CXX_FLAGS\s*=\s*(.*)$', files[0].read_text(), re.M) if len(files) == 1 else None
        modes = [word for word in shlex.split(flags.group(1)) if word.startswith("-std=")] if flags else []
        require(modes and modes[-1] in ("-std=c++17", "-std=gnu++17"),
                "Missing/mismatched C++17 flags for " + target)
    for relative, macro, excluded in ((GENERATED[0], "EXCLUDE_ROOT", True),
                                      (GENERATED[1], "EXCLUDE_RESTFRAMES", True),
                                      (GENERATED[2], "EXCLUDE_ONNXRUNTIME", False)):
        header = (root / relative).read_text()
        defined = bool(re.search(r'^\s*#define\s+' + macro + r'\b', header, re.M))
        undefined = bool(re.search(r'/\*\s*#undef\s+' + macro + r'\s*\*/', header))
        require((defined, undefined) == (excluded, not excluded), "Wrong feature header: " + macro)
    link = (root / "build/CMakeFiles/CBS.dir/link.txt").read_text()
    require("-lonnxruntime" in shlex.split(link) or re.search(r'libonnxruntime\.so', link), "CBS does not link ONNX Runtime")
    require(not re.search(r'-(?:lRestFrames|lCore|lRIO|lTree)\b', link)
            and not any(re.match(r'lib(?:RestFrames|Core|RIO|Tree)\.so(?:\.|$)', Path(word).name)
                        for word in shlex.split(link)), "Disabled ROOT/RestFrames library in CBS link")
    return {"cache": {key: cache.get(key) for key in IDENTITY_KEYS}, "compilers": compilers}


def native_files(root):
    return [p for p in (root / "build").rglob("*") if p.is_file()
            and not any(part.endswith("-prefix") for part in p.relative_to(root / "build").parts)
            and (p.suffix == ".o" or p.name in ("flags.make", "link.txt"))]


def required_libraries(directory, pattern):
    matches = list(directory.glob(pattern))
    require(matches and all(path.is_file() for path in matches),
            "Missing/invalid dependency library: " + str(directory / pattern))
    return matches


def snapshot(root):
    paths = set(native_files(root))
    objects = [p for p in paths if p.suffix == ".o"]
    observed = {part[:-4] for p in objects for part in p.parts if part.endswith(".dir")}
    require(NATIVE_TARGETS <= observed, "Missing native object targets: " + ", ".join(sorted(NATIVE_TARGETS - observed)))
    for target in ("fortran", "FarrayTest"):
        require(any(target + ".dir" in p.parts and p.name.endswith(".f90.o") for p in objects),
                "Missing GNU Fortran object: " + target)
    for relative in (*GENERATED, *NATIVE_BINARIES):
        path = root / relative
        require(path.is_file(), "Missing required generated/native output: " + relative)
        paths.add(path)
    # link.txt points to native shared/static outputs without traversing external
    # source/build trees. This also covers libraries emitted in existing lib/.
    for link in [p for p in paths if p.name == "link.txt" and p.parent.name[:-4] in observed]:
        words = shlex.split(link.read_text())
        outputs = [words[i + 1] for i, word in enumerate(words[:-1]) if word == "-o"]
        if not outputs:
            outputs = [word for word in words if word.endswith(".a")][:1]
        for output in outputs:
            path = Path(output)
            path = path if path.is_absolute() else link.parent.parent.parent / path
            require(path.is_file(), "Missing linked native output: " + str(path))
            paths.add(path.absolute())
    for relative, library in DEPENDENCIES:
        prefix = root / relative
        required_libraries(prefix / "lib", library)
        headers = prefix / "include"
        if "YODA" in relative:
            headers = prefix.parent / "include"
        require(headers.is_dir() and any(p.is_file() for p in headers.rglob("*")),
                "Missing dependency headers: " + str(headers))
        paths.update(p for p in headers.rglob("*") if p.is_file())
        paths.update(p for p in (prefix / "lib").rglob("*") if p.is_file())
        paths.update(prefix.glob(".gambit-*-build-identity"))
    fastjet = root / "contrib/fastjet-3.5.1/local"
    for name in ("Nsubjettiness.hh", "SoftDrop.hh", "LundGenerator.hh"):
        require((fastjet / "include/fastjet/contrib" / name).is_file(), "Missing fjcontrib header: " + name)
    for name in ("fastjetcontribfragile", "RecursiveTools", "EnergyCorrelator", "VariableR"):
        required_libraries(fastjet / "lib", "lib" + name + ".*")
    for directory in ("scratch/build_time", "build/BOSS_output", "build/BOSS_reset_info"):
        paths.update(p for p in (root / directory).rglob("*") if p.is_file() and not p.name.endswith(".candidate"))
    for pattern in ("*_options.stamp", "functors_for_*.stamp"):
        paths.update((root / "build").glob(pattern))
    # Completion and recorded source state are durable EP outputs. Avoid
    # configure-time generated command files and ordinary dependency scans.
    for package in AUDITED_PACKAGES:
        prefix = root / "build" / (package + "-prefix")
        stamp = prefix / "src" / (package + "-stamp")
        for step in ("mkdir", "download", "update", "patch", "prepare_source", "configure",
                     "build", "install", "done", "record_identity", "record_source_state"):
            path = stamp / (package + "-" + step)
            if path.exists() or path.is_symlink():
                paths.add(path)
        paths.update((prefix / "tmp").glob("*-source-state.json"))
        complete = root / "build/CMakeFiles" / (package + "-complete")
        if complete.exists() or complete.is_symlink():
            paths.add(complete)
    for directory in ("ColliderBit", "ScannerBit", "Backends", "Models", "Printers"):
        paths.add(root / directory / "CMakeLists.txt")
    content_only = {root / "cmake/tarball_info.cmake", root / "build/yoda-h5cc",
                    *(root / "build").glob("list_*_data.txt")}
    paths.update(p for p in content_only if p.is_file())
    result = {}
    for path in sorted({Path(os.path.abspath(path)) for path in paths}):
        require(path.is_file(), "Snapshot file missing: " + str(path))
        try:
            path.resolve().relative_to(root)
        except ValueError:
            raise AcceptanceError("Native/dependency output escaped checkout: " + str(path))
        stat = path.stat()
        result[path.relative_to(root).as_posix()] = {
            "sha256": hashlib.sha256(path.read_bytes()).hexdigest(), "mtime_ns": stat.st_mtime_ns,
            "size": stat.st_size, "resolved": str(path.resolve()), "mtime_strict": path not in content_only,
        }
    return result


def check_snapshot(before, after):
    def compared(record):
        return {key: value for key, value in record.items() if key != "mtime_ns" or record["mtime_strict"]}
    changed = [name for name in sorted(before.keys() | after.keys())
               if name not in before or name not in after or compared(before[name]) != compared(after[name])]
    require(not changed, "No-op snapshot changed: " + ", ".join(changed))


def build_events(text):
    text = re.sub(r"\x1b\[[0-9;]*m", "", text)
    steps = []
    for line in text.splitlines():
        match = re.search(r"\b(Performing|No)\s+(?:'([^']+)'|(\S+))\s+step"
                          r"(?:\s+\([^)]*\))?\s+for\s+'([^']+)'", line)
        if match:
            steps.append({"step": match.group(2) or match.group(3),
                          "package": match.group(4), "line": line, "empty": match.group(1) == "No"})
        else:
            match = re.search(r"\bCompleted '([^']+)'", line)
            if match:
                steps.append({"step": "completed", "package": match.group(1), "line": line, "empty": False})
            else:
                match = re.search(r"Recording successful (\S+) (?:source state|installation)", line)
                if match:
                    steps.append({"step": "record", "package": match.group(1), "line": line, "empty": False})
    return {"objects": re.findall(r"Building (?:C|CXX|Fortran) object (.+)", text),
            "links": re.findall(r"Linking (?:C|CXX|Fortran) (?:executable|shared library|static library) (.+)", text),
            "generation": [line for line in text.splitlines() if re.search(
                r"\bGenerat(?:ing|ed)\s+(?!done\b)|Preparing pristine|\bBOSS(?:ing)?\b", line)],
            "external_steps": steps,
            "success": bool(re.search(r"Built target CBS\s*$", text, re.M))}


def check_noop(text):
    events = build_events(text)
    require(events["success"], "Missing Built target CBS")
    require(not events["objects"] and not events["links"] and not events["generation"],
            "Unexpected no-op compile/link/code generation: " + json.dumps(events))
    for step in events["external_steps"]:
        require(step["package"] not in AUDITED_PACKAGES, "Audited package repeated step: " + step["line"])
        require(step["empty"] or step["step"] in ("build", "install", "verify", "completed"),
                "Unexpected repeated external preparation/configuration: " + step["line"])
    return events


def run(root, logdir, *, fresh_checkout, pybind11_dir, jobs=2, timeout=3600,
        cmake=None, command=run_command, host=None):
    root = root.resolve()
    pybind11_dir = pybind11_dir.resolve() if pybind11_dir is not None else None
    version = preflight(root, fresh_checkout, pybind11_dir, jobs, timeout, host)
    if logdir is None:
        logdir = Path(tempfile.mkdtemp(prefix="gambit-preset-acceptance-")) / "logs"
    logdir = logdir.resolve()
    logdir.mkdir(parents=True, exist_ok=False)
    summary = {"status": "RUNNING", "root": str(root), "build": str(root / "build"),
               "preset": "cbs-gnu", "features": FEATURES, "python": sys.executable,
               "pybind11": {"directory": str(pybind11_dir), "version": version},
               "jobs": jobs, "timeout_seconds": timeout, "steps": [], "noops": [],
               "scope": "Linux GNU CBS startup/build/incremental baseline; no physics or Pythia runtime acceptance",
               "pending_matrix": ["ROOT", "RestFrames", "Rivet/Contur", "Linux LLVM", "macOS CI"]}
    phase = "source-identity"
    def execute(name, argv):
        nonlocal phase
        phase = name
        row = {"name": name, "command": argv, "log": name + ".log", "status": "RUNNING"}
        summary["steps"].append(row)
        write_json(logdir / "summary.json", summary)
        started = time.monotonic()
        try:
            text = command(argv, root, logdir / row["log"], timeout)
            row["status"] = "PASS"
            return text
        except (AcceptanceError, OSError, ValueError, KeyboardInterrupt):
            row["status"] = "FAIL"
            raise
        finally:
            row["seconds"] = round(time.monotonic() - started, 3)
    try:
        selected = shutil.which(cmake or os.environ.get("CMAKE_COMMAND", "cmake"))
        require(selected, "CMake executable is missing")
        selected = str(Path(selected).resolve())
        commit = execute("source-identity", ["git", "rev-parse", "HEAD"]).strip()
        require(re.fullmatch(r"[0-9a-fA-F]{40,64}", commit), "Git commit identity unavailable")
        summary["commit"] = commit
        require(not execute("source-clean", ["git", "status", "--porcelain", "--untracked-files=no"]).strip(),
                "Fresh checkout has tracked changes")
        summary["cmake_version"] = execute("cmake-version", [selected, "--version"]).strip()
        baseline_identity, baseline = None, None
        for name, argv in commands(root, selected, pybind11_dir, jobs):
            text = execute(name, argv)
            if name.startswith("configure"):
                validation = configure_report(text)
                summary.setdefault("validation", {})[name] = validation
                current = identity(root, pybind11_dir)
                if baseline_identity is None:
                    baseline_identity = current
                    summary["identity"] = current
                else:
                    require(current == baseline_identity, "Same configure changed normalized identity")
            elif name == "build-first":
                require(build_events(text)["success"], "Missing first Built target CBS")
                baseline = snapshot(root)
                write_json(logdir / "baseline-snapshot.json", baseline)
            elif "noop" in name:
                events = check_noop(text)
                after = snapshot(root)
                write_json(logdir / (name + "-snapshot.json"), after)
                check_snapshot(baseline, after)
                require(identity(root, pybind11_dir) == baseline_identity, "No-op changed normalized identity")
                summary["noops"].append({"name": name, "status": "PASS", **events})
            else:
                require("Usage:" in text, "CBS startup did not print usage")
            print("PASS " + name, flush=True)
        summary["status"] = "PASS"
    except (AcceptanceError, OSError, ValueError, KeyboardInterrupt) as error:
        if summary["steps"] and summary["steps"][-1]["name"] == phase:
            summary["steps"][-1]["status"] = "FAIL"
        summary.update(status="FAIL", failed_step=phase, error=str(error) or "Interrupted")
        print("FAIL " + phase + ": " + summary["error"], file=sys.stderr)
    finally:
        write_json(logdir / "summary.json", summary)
    print("Result: " + summary["status"] + "; logs: " + str(logdir), flush=True)
    return 0 if summary["status"] == "PASS" else 1


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run", action="store_true")
    parser.add_argument("--fresh-checkout", action="store_true", help="assert this is an independent fresh checkout; required with --run")
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--pybind11-dir", type=Path, help="explicit installed pybind11 CMake package directory (required with --run)")
    parser.add_argument("--cmake", default=os.environ.get("CMAKE_COMMAND", "cmake"))
    parser.add_argument("--jobs", type=int, default=2)
    parser.add_argument("--timeout", type=positive, default=3600)
    parser.add_argument("--log-dir", type=Path, help="fresh log directory; never overwrite prior evidence")
    args = parser.parse_args(argv)
    if not args.run:
        print("Plan only; execution requires --run --fresh-checkout on Linux.")
        for name, command in commands(args.root.resolve(), args.cmake, args.pybind11_dir, args.jobs):
            print(name + ": " + shlex.join(command))
        return 0
    try:
        return run(args.root, args.log_dir, fresh_checkout=args.fresh_checkout,
                   pybind11_dir=args.pybind11_dir, jobs=args.jobs, timeout=args.timeout, cmake=args.cmake)
    except (AcceptanceError, OSError, ValueError) as error:
        print("Preflight failed: " + str(error), file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
