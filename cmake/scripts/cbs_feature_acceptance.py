#!/usr/bin/env python3
"""Maintainer-run CBS ONNX/RestFrames acceptance on an existing Make build.

Only --run executes configure/build/CBS. No clean, fresh, compiler switch or
source edits are performed. A failure stops the sequence and keeps its logs.
"""

import argparse
import hashlib
import json
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
import time


ROOT = Path(__file__).resolve().parents[2]
FLAGS = {"ColliderBit", "Models", "Utils", "Backends", "CBS_objects",
         "fjcontrib_nsubjettiness", "mkpath", "fortran", "gambit_preload"}
SHARED_LINKS = (
    "build/Backends/CMakeFiles/first.dir/link.txt",
    "build/Backends/CMakeFiles/fortran.dir/link.txt",
    "build/Backends/CMakeFiles/FarrayTest.dir/link.txt",
    "build/CMakeFiles/cbs_preload.dir/link.txt",
    "build/CMakeFiles/gambit_preload.dir/link.txt",
)
ANALYSES = "ColliderBit/CMakeFiles/ColliderBit.dir/src/analyses/"
ONNX_OBJECTS = {
    "ColliderBit/CMakeFiles/ColliderBit.dir/src/onnx_rt_wrapper.cpp.o",
    ANALYSES + "Analysis_ATLAS_SUSY_2018_30.cpp.o",
    ANALYSES + "AnalysisContainer.cpp.o",
}
REST_OBJECTS = {
    ANALYSES + "Analysis_" + name + ".cpp.o" for name in (
        "ATLAS_SUSY_2018_16", "ATLAS_SUSY_2018_12_RJR",
        "ATLAS_SUSY_2018_05_RJR", "ATLAS_SUSY_2017_03_RJR")
} | {ANALYSES + "AnalysisContainer.cpp.o",
     "CMakeFiles/gambit_preload.dir/contrib/preload/gambit_preload.cpp.o"}
FEATURES = (("ONNXRUNTIME", "onnxruntime", "onnxruntime-1.14.1"),
            ("RESTFRAMES", "RestFrames", "RestFrames-1.0.2"))
IDENTITY = ("CBS_BUILD_PRESET", "CMAKE_GENERATOR", "CMAKE_BUILD_TYPE",
            "CMAKE_C_COMPILER", "CMAKE_CXX_COMPILER", "CMAKE_Fortran_COMPILER",
            "CMAKE_COMMAND", "CMAKE_MAKE_PROGRAM", "CMAKE_TOOLCHAIN_FILE",
            "CMAKE_OSX_SYSROOT", "CMAKE_OSX_DEPLOYMENT_TARGET",
            "CMAKE_OSX_ARCHITECTURES", "MACOS_DEPLOYMENT_TARGET", "Bits",
            "Python3_EXECUTABLE", "ROOT_DIR", "ROOT_Core_LIBRARY")


class AcceptanceError(RuntimeError):
    pass


def require(condition, message):
    if not condition:
        raise AcceptanceError(message)


def cache_values(root):
    return dict(re.findall(r"^([^#/\n][^:\n]*):[^=\n]+=(.*)$",
                           (root / "build/CMakeCache.txt").read_text(), re.M))


def snapshot(root):
    targets = {name + ".dir" for name in FLAGS}
    flags = sorted(p for p in (root / "build").rglob("flags.make")
                   if p.parent.name in targets)
    require(len(flags) == len(FLAGS), "Expected nine target flags.make files")
    require({p.parent.name for p in flags} == targets,
            "Duplicate or missing target flags.make")
    paths = [root / "cmake/include/gambit/cmake/cmake_variables.hpp",
             *flags, *(root / p for p in SHARED_LINKS)]
    for _, _, package in FEATURES:
        for directory in ("include" if package.startswith("onnx") else "inc", "lib"):
            installed = sorted(p for p in (root / "contrib" / package / directory).rglob("*")
                               if p.is_file())
            require(installed, "Missing installed files: " + package + "/" + directory)
            paths.extend(installed)
    result = {}
    for path in paths:
        stat = path.stat()
        result[path.relative_to(root).as_posix()] = {
            "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            "mtime_ns": stat.st_mtime_ns, "size": stat.st_size,
            "resolved": str(path.resolve()),
        }
    return result


def check_snapshot(before, after):
    changed = sorted(name for name in before.keys() | after.keys()
                     if before.get(name) != after.get(name))
    require(not changed, "Stable file content/mtime changed: " + ", ".join(changed))


def check_features(root, onnx, rest, user_paths):
    cache = cache_values(root)
    link = shlex.split((root / "build/CMakeFiles/CBS.dir/link.txt").read_text())
    for (macro, library, package), enabled in zip(FEATURES, (onnx, rest)):
        require(cache.get("WITH_" + macro) == ("ON" if enabled else "OFF"),
                "Unexpected cached WITH_" + macro)
        header = (root / ("cmake/include/gambit/cmake/" + macro.lower()
                          + "_variables.hpp")).read_text()
        excluded = bool(re.search(r"^#define EXCLUDE_" + macro + r"\b", header, re.M))
        available = bool(re.search(r"/\* #undef EXCLUDE_" + macro + r" \*/", header))
        require((available, excluded) == (enabled, not enabled),
                "Feature header disagrees with WITH_" + macro)
        require(("-l" + library in link) == enabled, "Wrong CBS link item: " + library)
        directory = str(root / "contrib" / package / "lib")
        rpath = any(word == "-Wl,-rpath," + directory for word in link)
        require(rpath == (enabled or directory in user_paths),
                "Wrong CBS runtime path: " + package)


def build_events(text):
    text = re.sub(r"\x1b\[[0-9;]*m", "", text)
    return {
        "objects": [p.strip() for p in re.findall(r"Building (?:C|CXX|Fortran) object (.+)", text)],
        "links": [Path(p.strip()).name for p in re.findall(
            r"Linking (?:C|CXX|Fortran) (?:executable|shared library|static library) (.+)", text)],
        "extra": [line for line in text.splitlines() if re.search(
            r"\b(?:Generating |Performing .* step for|No .* step for|Completed '"
            r"|Recording successful|Installing analysis data files)", line)],
        "success": bool(re.search(r"Built target CBS\s*$", text, re.M)),
    }


def check_build(text, objects, links):
    events = build_events(text)
    require(events["success"], "Missing final Built target CBS")
    require(len(events["objects"]) == len(objects) and set(events["objects"]) == objects,
            "Unexpected compiled objects: " + repr(events["objects"]))
    require(len(events["links"]) == len(links) and set(events["links"]) == links,
            "Unexpected links: " + repr(events["links"]))
    require(not events["extra"], "Unexpected generation/external work: " + repr(events["extra"]))
    return events


def run_command(command, root, logfile):
    print("+ " + " ".join(shlex.quote(p) for p in command), flush=True)
    with logfile.open("w") as log:
        with subprocess.Popen(command, cwd=root, stdin=subprocess.DEVNULL, stdout=subprocess.PIPE,
                              stderr=subprocess.STDOUT, text=True) as process:
            for line in process.stdout:
                log.write(line)
                print(line, end="", flush=True)
            code = process.wait()
    require(code == 0, "Command exited " + str(code) + "; see " + str(logfile))
    return logfile.read_text()


def write_json(path, value):
    path.write_text(json.dumps(value, indent=2, sort_keys=True) + "\n")


def run(root, logdir, jobs, command=run_command):
    cache = cache_values(root)
    require(cache.get("CBS_BUILD_PRESET") == "cbs-llvm",
            "Use the already configured cbs-llvm build")
    require(cache.get("CMAKE_GENERATOR") == "Unix Makefiles", "Requires Unix Makefiles")
    user_paths = cache.get("CMAKE_INSTALL_RPATH", "").split(";")
    check_features(root, True, True, user_paths)
    before = snapshot(root)
    baseline = {key: cache.get(key) for key in IDENTITY}
    preload_link = shlex.split((root / SHARED_LINKS[-1]).read_text())
    preload = Path(preload_link[preload_link.index("-o") + 1]).name
    cmake = shutil.which("cmake")
    require(cmake, "cmake is not on PATH")
    require(jobs > 0, "jobs must be positive")
    logdir.mkdir()  # Existing results are never overwritten.
    print("Acceptance logs: " + str(logdir), flush=True)
    write_json(logdir / "before.json", before)
    summary = {"status": "RUNNING", "root": str(root), "identity": baseline,
               "jobs": jobs, "cases": [], "command_seconds": {}}
    def execute(argv, filename):
        started = time.monotonic()
        try:
            return command(argv, root, logdir / filename)
        finally:
            summary["command_seconds"][filename] = round(time.monotonic() - started, 3)

    build = [cmake, "--build", "build", "--target", "CBS", "--parallel", str(jobs)]
    name = "preflight"
    try:
        cases = (("onnx-off", False, True, ONNX_OBJECTS, {"CBS"}),
                 ("onnx-on", True, True, ONNX_OBJECTS, {"CBS"}),
                 ("restframes-off", True, False, REST_OBJECTS, {"CBS", preload}),
                 ("restframes-on", True, True, REST_OBJECTS, {"CBS", preload}))
        for name, onnx, rest, objects, links in cases:
            configure = [cmake, "--preset", "cbs-llvm",
                         "-DWITH_ONNXRUNTIME=" + ("ON" if onnx else "OFF"),
                         "-DWITH_RESTFRAMES=" + ("ON" if rest else "OFF")]
            execute(configure, name + "-configure.log")
            current = cache_values(root)
            require({key: current.get(key) for key in IDENTITY} == baseline,
                    "Toolchain/profile identity changed")
            text = execute(build, name + "-build.log")
            events = check_build(text, objects, links)
            after = snapshot(root)
            write_json(logdir / (name + "-snapshot.json"), after)
            check_snapshot(before, after)
            check_features(root, onnx, rest, user_paths)
            loader = execute([str(root / "CBS"), "--help"], name + "-loader.log")
            require("Usage:" in loader, "CBS --help did not print usage")
            summary["cases"].append({"name": name, "status": "PASS", **events})
            print("PASS " + name + ": " + str(len(objects)) + " objects; stable files retained",
                  flush=True)
        name = "final-noop"
        text = execute(build, "final-noop.log")
        events = check_build(text, set(), set())
        after = snapshot(root)
        write_json(logdir / "final-noop-snapshot.json", after)
        check_snapshot(before, after)
        check_features(root, True, True, user_paths)
        summary["cases"].append({"name": "final-noop", "status": "PASS", **events})
        summary["status"] = "PASS"
    except (AcceptanceError, OSError, ValueError, KeyboardInterrupt) as error:
        summary["status"], summary["error"] = "FAIL", str(error) or "Interrupted"
        summary["failed_case"] = name
        print("FAIL " + name + ": " + summary["error"], file=sys.stderr)
        print("To restore the ON baseline after a failed switch:", file=sys.stderr)
        print("  cd " + shlex.quote(str(root)), file=sys.stderr)
        print("  cmake --preset cbs-llvm -DWITH_ONNXRUNTIME=ON -DWITH_RESTFRAMES=ON",
              file=sys.stderr)
        print("  cmake --build build --target CBS --parallel " + str(jobs), file=sys.stderr)
    finally:
        write_json(logdir / "summary.json", summary)
    print("Result: " + summary["status"] + "; logs: " + str(logdir), flush=True)
    return 0 if summary["status"] == "PASS" else 1


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run", action="store_true", help="execute the maintainer acceptance sequence")
    parser.add_argument("--jobs", type=int, default=8)
    parser.add_argument("--log-dir", type=Path, help="new directory for logs (default: a unique temp directory)")
    args = parser.parse_args()
    if not args.run:
        parser.print_help()
        return 0
    if args.jobs <= 0:
        parser.error("--jobs must be positive")
    # Reserve a unique name; run() creates the directory only after preflight.
    if args.log_dir is None:
        directory = Path(tempfile.mkdtemp(prefix="cbs-feature-acceptance-"))
        directory.rmdir()
    else:
        directory = args.log_dir.resolve()
    try:
        return run(ROOT, directory, args.jobs)
    except (AcceptanceError, OSError, ValueError) as error:
        print("Preflight failed: " + str(error), file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
