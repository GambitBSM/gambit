#!/usr/bin/env python3
"""Exercise Linux CBS acceptance with temporary fixtures and fake tools only."""

import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys
import tempfile
import time
import unittest
from unittest import mock


ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location(
    "preset_acceptance", ROOT / "cmake/scripts/preset_build_acceptance.py")
acceptance = importlib.util.module_from_spec(spec)
spec.loader.exec_module(acceptance)


class AcceptanceTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="preset-acceptance-fixture-")
        self.root = Path(self.temporary.name).resolve() / "source with spaces"
        self.root.mkdir()
        (self.root / ".git").mkdir()
        self.put("CMakeLists.txt", "# fixture: never configure this project\n")
        self.put("CMakePresets.json", (ROOT / "CMakePresets.json").read_text())
        self.hint = self.root.parent / "pybind11 cmake"
        self.hint.mkdir()
        (self.hint / "pybind11Config.cmake").write_text("# installed fixture\n")
        (self.hint / "pybind11ConfigVersion.cmake").write_text('set(PACKAGE_VERSION "2.13.6")\n')
        self.calls = []
        self.logs = self.root.parent / "logs"

    def tearDown(self):
        self.temporary.cleanup()

    def put(self, relative, text="stable fixture\n", only_new=False):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        if not only_new or not path.exists():
            path.write_text(text)
        return path

    def configure(self):
        cache = dict(acceptance.FEATURES)
        cache.update(CBS_BUILD_PRESET="cbs-gnu", CMAKE_GENERATOR="Unix Makefiles",
                     CMAKE_HOME_DIRECTORY=str(self.root), Python3_EXECUTABLE=sys.executable,
                     pybind11_DIR=str(self.hint), Bits="ColliderBit", CMAKE_CXX_EXTENSIONS="OFF")
        for language, tool in (("C", "gcc"), ("CXX", "g++"), ("Fortran", "gfortran")):
            compiler = "/fixture/GNU tools/" + tool
            cache["CMAKE_" + language + "_COMPILER"] = compiler
            self.put("build/CMakeFiles/3.28.3/CMake" + language + "Compiler.cmake",
                     'set(CMAKE_' + language + '_COMPILER "' + compiler + '")\n'
                     'set(CMAKE_' + language + '_COMPILER_ID "GNU")\n'
                     'set(CMAKE_' + language + '_COMPILER_VERSION "13.2.0")\n')
        self.put("build/CMakeCache.txt", "".join(key + ":STRING=" + value + "\n"
                                                 for key, value in cache.items()))
        for target in acceptance.NATIVE_TARGETS:
            self.put("build/CMakeFiles/" + target + ".dir/flags.make",
                     "CXX_FLAGS = -O3 -std=c++17\n", only_new=True)
        for relative, text in ((acceptance.GENERATED[0], "#define EXCLUDE_ROOT\n"),
                               (acceptance.GENERATED[1], "#define EXCLUDE_RESTFRAMES\n"),
                               (acceptance.GENERATED[2], "/* #undef EXCLUDE_ONNXRUNTIME */\n")):
            self.put(relative, text, only_new=True)
        self.put("build/CMakeFiles/CBS.dir/link.txt", shlex.join(
            ["/fixture/GNU tools/g++", "-o", str(self.root / "CBS"), "-lonnxruntime"]), only_new=True)
        # CMake emits metadata for targets not built by CBS. Their missing
        # executables must not make a complete CBS snapshot fail.
        self.put("build/CMakeFiles/gambit.dir/link.txt", "/fixture/g++ -o ../gambit\n", only_new=True)
        for relative in ("cmake/tarball_info.cmake", "build/yoda-h5cc", "build/list_backend_data.txt"):
            self.put(relative)
        labels = ("C compile/link", "C++17 compile/link", "Fortran compile/link", "OpenMP",
                  "Python development", "Boost", "HDF5 C development", "CBS target", "SQLite3 development")
        return "".join("--   " + label + " : PASS\n" for label in labels) + "--   CBS environment : READY\n"

    def build(self):
        for target in acceptance.NATIVE_TARGETS:
            unit = "unit.f90.o" if target in ("fortran", "FarrayTest") else "unit.cpp.o"
            self.put("build/CMakeFiles/" + target + ".dir/" + unit)
        for relative in (*acceptance.GENERATED, *acceptance.NATIVE_BINARIES):
            self.put(relative, only_new=True)
        # A linked archive supplements the explicit executable/shared outputs.
        self.put("build/CMakeFiles/yaml-cpp.dir/link.txt", "/fixture/ar qc yaml-cpp/libyaml-cpp.a unit.o\n")
        self.put("build/yaml-cpp/libyaml-cpp.a")
        for relative, pattern in acceptance.DEPENDENCIES:
            self.put(relative + "/lib/" + pattern.replace("*", ""))
            headerdir = str(Path(relative).parent / "include") if "YODA" in relative else relative + "/include"
            self.put(headerdir + "/dependency.inc")
        fastjet = "contrib/fastjet-3.5.1/local"
        for name in ("Nsubjettiness.hh", "SoftDrop.hh", "LundGenerator.hh"):
            self.put(fastjet + "/include/fastjet/contrib/" + name)
        for name in ("fastjetcontribfragile", "RecursiveTools", "EnergyCorrelator", "VariableR"):
            self.put(fastjet + "/lib/lib" + name + ".a")
        for directory in ("ColliderBit", "ScannerBit", "Backends", "Models", "Printers"):
            self.put(directory + "/CMakeLists.txt", only_new=True)
        for relative in ("build/fastjet_options.stamp", "build/BOSS_reset_info/package.state",
                         "scratch/build_time/harvest-state", "build/BOSS_output/package.cpp",
                         "contrib/fastjet-3.5.1/local/.gambit-fastjet-build-identity",
                         "build/hepmc-prefix/src/hepmc-stamp/hepmc-done",
                         "build/CMakeFiles/hepmc-complete",
                         "build/nulike_1.0.9-prefix/tmp/nulike_1.0.9-source-state.json"):
            self.put(relative)
        return "[100%] Built target CBS\n"

    def captured(self, argv, root, log, timeout):
        self.assertEqual(root, self.root)
        self.assertEqual(timeout, 2)
        self.calls.append((log.stem, argv))
        if log.stem == "source-identity":
            text = "a" * 40 + "\n"
        elif log.stem == "source-clean":
            text = ""
        elif log.stem == "cmake-version":
            text = "cmake version fixture\n"
        elif log.stem.startswith("configure"):
            text = self.configure()
        elif log.stem == "build-first":
            text = self.build()
        elif argv[-1] == "--help":
            text = "Usage: ./CBS [options]\n"
        else:
            text = "[100%] Built target CBS\n"
        log.write_text(text)
        return text

    def execute(self, command=None):
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()), \
                mock.patch.object(acceptance.shutil, "which", return_value=sys.executable):
            return acceptance.run(self.root, self.logs, fresh_checkout=True, pybind11_dir=self.hint,
                                  timeout=2, command=command or self.captured, host="linux")

    def fixture_graph(self):
        self.configure()
        self.build()

    def test_complete_sequence_uses_real_presets_and_records_evidence(self):
        self.assertEqual(self.execute(), 0)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertEqual(summary["status"], "PASS")
        self.assertEqual(summary["commit"], "a" * 40)
        self.assertEqual(len(summary["noops"]), 2)
        self.assertEqual(set(summary["identity"]["compilers"]), {"C", "CXX", "Fortran"})
        phases = [name for name, _ in self.calls]
        self.assertEqual(phases, ["source-identity", "source-clean", "cmake-version"] +
                         [name for name, _ in acceptance.commands(self.root, "cmake", self.hint, 2)])
        configure = [argv for _, argv in self.calls if "--preset" in argv]
        self.assertEqual(configure[0][:-1], configure[1])
        self.assertEqual(configure[0][-1], "--fresh")
        self.assertIn("Unix Makefiles", configure[0])
        for key, value in acceptance.FEATURES.items():
            self.assertIn("-D" + key + "=" + value, configure[0])
        self.assertIn("-DPython3_EXECUTABLE=" + sys.executable, configure[0])
        self.assertEqual(sum("--fresh" in argv for _, argv in self.calls), 1)
        for _, argv in self.calls:
            if "--build" in argv:
                self.assertEqual(argv[2], "build")
                self.assertNotIn("--clean-first", argv)
        snapshot = json.loads((self.logs / "baseline-snapshot.json").read_text())
        self.assertIn("build/CMakeFiles/fortran.dir/unit.f90.o", snapshot)
        self.assertIn("build/yaml-cpp/libyaml-cpp.a", snapshot)
        self.assertIn("contrib/YODA-2.1.0/include/dependency.inc", snapshot)
        self.assertFalse(snapshot["build/yoda-h5cc"]["mtime_strict"])
        self.assertNotIn("gambit", snapshot)

    def test_default_plan_does_not_probe_tools_or_write(self):
        with contextlib.redirect_stdout(io.StringIO()) as output, \
                mock.patch.object(acceptance, "run", side_effect=AssertionError("must not run")), \
                mock.patch.object(acceptance.shutil, "which", side_effect=AssertionError("must not probe")), \
                mock.patch.object(acceptance.tempfile, "mkdtemp", side_effect=AssertionError("must not write")):
            self.assertEqual(acceptance.main(["--root", str(self.root), "--log-dir", str(self.logs)]), 0)
        self.assertIn("Plan only", output.getvalue())
        self.assertIn("<explicit pybind11 CMake directory>", output.getvalue())
        self.assertFalse((self.root / "build").exists())
        self.assertFalse(self.logs.exists())

    def test_preflight_rejects_unsafe_execution_before_any_command(self):
        args = (self.root, True, self.hint, 2, 2)
        with self.assertRaisesRegex(acceptance.AcceptanceError, "Linux"):
            acceptance.preflight(*args, host="darwin")
        with self.assertRaisesRegex(acceptance.AcceptanceError, "fresh-checkout"):
            acceptance.preflight(self.root, False, self.hint, 2, 2, "linux")
        with self.assertRaisesRegex(acceptance.AcceptanceError, "pybind11-dir"):
            acceptance.preflight(self.root, True, None, 2, 2, "linux")
        (self.hint / "pybind11ConfigVersion.cmake").write_text('set(PACKAGE_VERSION "2.11.1")\n')
        with self.assertRaisesRegex(acceptance.AcceptanceError, "2.13.6"):
            acceptance.preflight(*args, host="linux")
        (self.hint / "pybind11ConfigVersion.cmake").write_text('set(PACKAGE_VERSION "2.13.6")\n')
        for existing in ("build", "CBS", "CMakeUserPresets.json"):
            with self.subTest(existing=existing):
                path = self.put(existing)
                with self.assertRaises(acceptance.AcceptanceError):
                    acceptance.preflight(*args, host="linux")
                path.unlink()
        for existing in acceptance.EXTERNAL_WORKSPACES:
            with self.subTest(existing=existing):
                path = self.root / existing
                path.mkdir(parents=True)
                with self.assertRaisesRegex(acceptance.AcceptanceError, "external workspace"):
                    acceptance.preflight(*args, host="linux")
                path.rmdir()
        self.put("contrib/yaml-cpp/CMakeLists.txt", "# legitimate bundled source\n")
        acceptance.preflight(*args, host="linux")
        self.assertEqual(self.calls, [])

    def test_preset_contract_rejects_split_build_or_output_override(self):
        original = json.loads((self.root / "CMakePresets.json").read_text())
        for field, value in (("binaryDir", "${sourceDir}/build/cbs"), ("generator", "Ninja"),
                             ("cacheVariables", {"GAMBIT_RUN_DIR": "/other"})):
            with self.subTest(field=field):
                data = json.loads(json.dumps(original))
                next(p for p in data["configurePresets"] if p["name"] == "cbs-base")[field] = value
                self.put("CMakePresets.json", json.dumps(data))
                with self.assertRaises(acceptance.AcceptanceError):
                    acceptance.preset_contract(self.root)

    def test_existing_logs_are_preserved(self):
        self.logs.mkdir()
        marker = self.logs / "summary.json"
        marker.write_text("keep prior evidence\n")
        with self.assertRaises(FileExistsError):
            self.execute()
        self.assertEqual(marker.read_text(), "keep prior evidence\n")
        self.assertEqual(self.calls, [])
        self.assertFalse((self.root / "build").exists())

    def test_failed_command_stops_and_preserves_partial_log(self):
        def fail(argv, root, log, timeout):
            if log.stem == "build-first":
                self.calls.append((log.stem, argv))
                log.write_text("partial build evidence\n")
                raise acceptance.AcceptanceError("fixture failed build")
            return self.captured(argv, root, log, timeout)
        self.assertEqual(self.execute(fail), 1)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertEqual(summary["failed_step"], "build-first")
        self.assertEqual(summary["steps"][-1]["status"], "FAIL")
        self.assertEqual(self.calls[-1][0], "build-first")
        self.assertIn("partial build evidence", (self.logs / "build-first.log").read_text())

    def test_exit_zero_cbs_log_cannot_hide_missing_fortran_output(self):
        def missing(argv, root, log, timeout):
            text = self.captured(argv, root, log, timeout)
            if log.stem == "build-first":
                (root / "Backends/examples/libfortran.so").unlink()
            return text
        self.assertEqual(self.execute(missing), 1)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertEqual(summary["failed_step"], "build-first")
        self.assertEqual(summary["steps"][-1]["status"], "FAIL")
        self.assertIn("libfortran.so", summary["error"])

    def test_quiet_native_mutation_fails_direct_noop_and_stops(self):
        def changed(argv, root, log, timeout):
            text = self.captured(argv, root, log, timeout)
            if log.stem == "build-direct-noop":
                self.put("build/CMakeFiles/ColliderBit.dir/unit.cpp.o", "silent real compilation")
            return text
        self.assertEqual(self.execute(changed), 1)
        summary = json.loads((self.logs / "summary.json").read_text())
        self.assertEqual(summary["failed_step"], "build-direct-noop")
        self.assertEqual(self.calls[-1][0], "build-direct-noop")
        self.assertIn("unit.cpp.o", summary["error"])
        self.assertTrue((self.logs / "build-direct-noop-snapshot.json").exists())

    def test_empty_or_incomplete_object_graph_cannot_pass(self):
        self.fixture_graph()
        obj = self.root / "build/CMakeFiles/FarrayTest.dir/unit.f90.o"
        obj.unlink()
        with self.assertRaisesRegex(acceptance.AcceptanceError, "FarrayTest"):
            acceptance.snapshot(self.root)

    def test_snapshot_detects_addition_removal_mtime_library_and_generation(self):
        self.fixture_graph()
        before = acceptance.snapshot(self.root)
        for relative in ("build/CMakeFiles/CBS_objects.dir/unit.cpp.o", "Backends/examples/libFarrayTest.so",
                         "build/functors_for_CBS.stamp", "contrib/fastjet-3.5.1/local/lib/libRecursiveTools.a",
                         "build/hepmc-prefix/src/hepmc-stamp/hepmc-done",
                         "build/nulike_1.0.9-prefix/tmp/nulike_1.0.9-source-state.json",
                         "contrib/fastjet-3.5.1/local/.gambit-fastjet-build-identity"):
            with self.subTest(relative=relative):
                path = self.root / relative
                stat = path.stat()
                os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns + 1000000))
                with self.assertRaisesRegex(acceptance.AcceptanceError, "snapshot changed"):
                    acceptance.check_snapshot(before, acceptance.snapshot(self.root))
                os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
        added = self.put("build/CMakeFiles/CBS.dir/new.cpp.o")
        with self.assertRaisesRegex(acceptance.AcceptanceError, "new.cpp.o"):
            acceptance.check_snapshot(before, acceptance.snapshot(self.root))
        added.unlink()
        removed = self.root / "build/CMakeFiles/CBS.dir/unit.cpp.o"
        removed.unlink()
        with self.assertRaises(acceptance.AcceptanceError):
            acceptance.snapshot(self.root)

    def test_configure_probe_changes_do_not_change_native_snapshot(self):
        self.fixture_graph()
        before = acceptance.snapshot(self.root)
        probes = [
            "build/CMakeFiles/hdf5/cmake_hdf5_test.o",
            "build/CMakeFiles/hdf5/flags.make",
            "build/CMakeFiles/hdf5/link.txt",
            "build/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_fixture.dir/test.o",
            "build/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_fixture.dir/flags.make",
            "build/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_fixture.dir/link.txt",
            "build/CMakeFiles/CMakeScratch/TryCompile-fixture/CMakeFiles/cmTC_fixture.dir/test.o",
            "build/CMakeFiles/CMakeScratch/TryCompile-fixture/CMakeFiles/cmTC_fixture.dir/flags.make",
            "build/CMakeFiles/CMakeScratch/TryCompile-fixture/CMakeFiles/cmTC_fixture.dir/link.txt",
            "build/hepmc-prefix/src/hepmc-build/CMakeFiles/HepMC3.dir/test.o",
        ]
        for relative in probes:
            with self.subTest(relative=relative):
                path = self.put(relative, "initial configure probe\n")
                after = acceptance.snapshot(self.root)
                self.assertNotIn(relative, after)
                acceptance.check_snapshot(before, after)
                stat = path.stat()
                os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns + 1000000))
                acceptance.check_snapshot(before, acceptance.snapshot(self.root))
                path.write_text("rebuilt configure probe\n")
                acceptance.check_snapshot(before, acceptance.snapshot(self.root))
                path.unlink()
                acceptance.check_snapshot(before, acceptance.snapshot(self.root))
        for relative in ("build/CMakeFiles/CBS.dir/flags.make", "build/CMakeFiles/CBS.dir/link.txt"):
            self.assertIn(relative, before)
            self.assertTrue(before[relative]["mtime_strict"])

    def test_probe_names_in_real_native_targets_remain_strict(self):
        self.fixture_graph()
        native = [
            "build/CMakeFiles/CBS_objects.dir/cmake_hdf5_test.o",
            "build/CMakeFiles/CBS_objects.dir/src/CMakeScratch/Foo.cpp.o",
            "build/CMakeFiles/CBS_objects.dir/src/CMakeTmp/Foo.cpp.o",
            "build/nested/CMakeFiles/additional_native.dir/cmake_hdf5_test.o",
            "build/nested/CMakeFiles/additional_native.dir/flags.make",
            "build/nested/CMakeFiles/additional_native.dir/link.txt",
        ]
        before = acceptance.snapshot(self.root)
        for relative in native:
            with self.subTest(relative=relative):
                path = self.put(relative)
                observed = acceptance.snapshot(self.root)
                self.assertIn(relative, observed)
                self.assertTrue(observed[relative]["mtime_strict"])
                with self.assertRaisesRegex(acceptance.AcceptanceError, "snapshot changed"):
                    acceptance.check_snapshot(before, observed)
                stat, content = path.stat(), path.read_bytes()
                os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns + 1000000))
                with self.assertRaisesRegex(acceptance.AcceptanceError, "snapshot changed"):
                    acceptance.check_snapshot(observed, acceptance.snapshot(self.root))
                path.write_text("changed real native artifact\n")
                os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
                with self.assertRaisesRegex(acceptance.AcceptanceError, "snapshot changed"):
                    acceptance.check_snapshot(observed, acceptance.snapshot(self.root))
                path.write_bytes(content)
                os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))
                acceptance.check_snapshot(observed, acceptance.snapshot(self.root))
                path.unlink()
                with self.assertRaisesRegex(acceptance.AcceptanceError, "snapshot changed"):
                    acceptance.check_snapshot(observed, acceptance.snapshot(self.root))
                acceptance.check_snapshot(before, acceptance.snapshot(self.root))

    def test_missing_broken_or_directory_dependency_library_fails(self):
        self.fixture_graph()
        path = self.root / "contrib/onnxruntime-1.14.1/lib/libonnxruntime.so"
        path.unlink()
        with self.assertRaisesRegex(acceptance.AcceptanceError, "dependency library"):
            acceptance.snapshot(self.root)
        path.symlink_to(path.parent / "missing.so")
        with self.assertRaisesRegex(acceptance.AcceptanceError, "dependency library"):
            acceptance.snapshot(self.root)
        path.unlink()
        path.mkdir()
        with self.assertRaisesRegex(acceptance.AcceptanceError, "dependency library"):
            acceptance.snapshot(self.root)

    def test_native_output_cannot_resolve_outside_checkout(self):
        self.fixture_graph()
        external = Path(self.temporary.name) / "outside-library.so"
        external.write_text("outside")
        output = self.root / "Backends/examples/libfirst.so"
        output.unlink()
        output.symlink_to(external)
        with self.assertRaisesRegex(acceptance.AcceptanceError, "escaped checkout"):
            acceptance.snapshot(self.root)

    def test_identity_rejects_actual_compiler_mode_and_link_disagreements(self):
        self.configure()
        cases = (
            ("build/CMakeFiles/3.28.3/CMakeCXXCompiler.cmake", 'set(CMAKE_CXX_COMPILER_ID "Clang")\n'),
            ("build/CMakeFiles/CBS.dir/flags.make", "CXX_FLAGS = -std=c++17 -std=c++23\n"),
            (acceptance.GENERATED[0], "/* #undef EXCLUDE_ROOT */\n"),
            ("build/CMakeFiles/CBS.dir/link.txt", "/fixture/g++ -o CBS\n"),
            ("build/CMakeFiles/CBS.dir/link.txt", "/fixture/g++ -o CBS -lonnxruntime /fixture/libCore.so.6.30\n"),
        )
        for relative, bad in cases:
            with self.subTest(relative=relative, bad=bad):
                old = (self.root / relative).read_text()
                self.put(relative, bad)
                with self.assertRaises(acceptance.AcceptanceError):
                    acceptance.identity(self.root, self.hint)
                self.put(relative, old)

    def test_configure_validation_missing_or_failed_is_not_a_pass(self):
        text = self.configure()
        self.assertEqual(acceptance.configure_report(text)["CBS environment"], "READY")
        for bad in (text.replace("Fortran compile/link : PASS", "Fortran compile/link : FAIL"), ""):
            with self.assertRaises(acceptance.AcceptanceError):
                acceptance.configure_report(bad)

    def test_noop_reports_legacy_wrappers_but_rejects_real_work_and_audited_steps(self):
        clean = "[100%] Built target CBS\n"
        legacy = "Performing 'build' step for 'legacy'\nPerforming 'install' step for 'legacy'\nCompleted 'legacy'\n"
        self.assertEqual(len(acceptance.check_noop(legacy + clean)["external_steps"]), 3)
        for line in ("Building Fortran object FarrayTest.dir/lower.f90.o", "Linking CXX executable CBS",
                     "Generating functors_for_CBS.stamp", "Generated backend_rollcall.hpp",
                     "Preparing pristine HepMC 3.2.5 sources", "BOSSing pythia",
                     "Performing 'download' step for 'legacy'", "Performing 'patch' step for 'legacy'",
                     "Performing 'configure' step for 'legacy'", "Recording successful fastjet installation",
                     *("Performing 'build' step for '" + name + "'" for name in acceptance.AUDITED_PACKAGES)):
            with self.subTest(line=line):
                with self.assertRaises(acceptance.AcceptanceError):
                    acceptance.check_noop(line + "\n" + clean)
        with self.assertRaisesRegex(acceptance.AcceptanceError, "Built target CBS"):
            acceptance.check_noop("nothing happened\n")

    def test_actual_cmake_unquoted_and_parenthetical_external_messages(self):
        clean = "[100%] Built target CBS\n"
        # These forms are emitted in the existing EP build.make files; older
        # quoted-step fixtures alone miss CMake's actual warm-build messages.
        for line, step, package in (
                ("[ 15%] Performing build step for 'hepmc'", "build", "hepmc"),
                ("[ 20%] Performing download step (download, verify and extract) for 'yoda'", "download", "yoda"),
                ("Performing 'patch' step for 'legacy'", "patch", "legacy"),
                ("Performing download step (git clone) for 'legacy'", "download", "legacy"),
                ("Performing patch step for 'nulike_1.0.9'", "patch", "nulike_1.0.9"),
                ("No install step for 'onnxruntime'", "install", "onnxruntime")):
            with self.subTest(line=line):
                event = acceptance.build_events(line)["external_steps"]
                self.assertEqual([(entry["step"], entry["package"]) for entry in event], [(step, package)])
                with self.assertRaises(acceptance.AcceptanceError):
                    acceptance.check_noop(line + "\n" + clean)
        events = acceptance.check_noop("Performing build step for 'legacy'\n" + clean)
        self.assertEqual(events["external_steps"][0]["step"], "build")

    def test_cmake_override_or_environment_is_resolved_consistently(self):
        with mock.patch.object(acceptance, "run", return_value=0) as run, \
                mock.patch.dict(os.environ, {"CMAKE_COMMAND": "/fixture/custom cmake"}):
            self.assertEqual(acceptance.main(["--run", "--fresh-checkout", "--pybind11-dir", str(self.hint)]), 0)
            self.assertEqual(run.call_args.kwargs["cmake"], "/fixture/custom cmake")
            self.assertEqual(acceptance.main(["--run", "--fresh-checkout", "--cmake", "/explicit/cmake"]), 0)
            self.assertEqual(run.call_args.kwargs["cmake"], "/explicit/cmake")

    def test_missing_cmake_preserves_failure_summary_without_configure(self):
        with contextlib.redirect_stdout(io.StringIO()), contextlib.redirect_stderr(io.StringIO()), \
                mock.patch.object(acceptance.shutil, "which", return_value=None):
            self.assertEqual(acceptance.run(self.root, self.logs, fresh_checkout=True, pybind11_dir=self.hint,
                                           host="linux", command=self.captured), 1)
        self.assertEqual(self.calls, [])
        self.assertIn("missing", json.loads((self.logs / "summary.json").read_text())["error"])

    def test_subprocess_closes_stdin_sanitizes_python_and_captures_full_output(self):
        logfile = Path(self.temporary.name) / "process.log"
        code = "import os,sys; print(repr(sys.stdin.read())); print(os.getenv('PYTHONPATH')); print('x'*100000)"
        with contextlib.redirect_stdout(io.StringIO()), \
                mock.patch.dict(os.environ, {"PYTHONHOME": "/invalid", "PYTHONPATH": "/unexpected"}):
            text = acceptance.run_command([sys.executable, "-c", code], self.root, logfile, 2)
        self.assertTrue(text.startswith("''\nNone\n"))
        self.assertGreater(len(text), 100000)
        self.assertEqual(text, logfile.read_text())

    @unittest.skipUnless(os.name == "posix", "process-group acceptance requires POSIX")
    def test_timeout_kills_descendants_for_hanging_and_exited_parents(self):
        for parent_exits in (False, True):
            with self.subTest(parent_exits=parent_exits):
                marker = Path(self.temporary.name) / ("escaped-" + str(parent_exits))
                logfile = Path(self.temporary.name) / ("timeout-" + str(parent_exits) + ".log")
                child = "import time,pathlib; time.sleep(.8); pathlib.Path(" + repr(str(marker)) + ").write_text('escaped')"
                code = "import subprocess,sys,time; subprocess.Popen([sys.executable,'-c'," + repr(child) + "]); print('partial',flush=True)"
                if not parent_exits:
                    code += "; time.sleep(30)"
                started = time.monotonic()
                with contextlib.redirect_stdout(io.StringIO()), self.assertRaisesRegex(acceptance.AcceptanceError, "timed out"):
                    acceptance.run_command([sys.executable, "-c", code], self.root, logfile, .2)
                self.assertLess(time.monotonic() - started, 2)
                self.assertIn("partial", logfile.read_text())
                self.assertIn("process-group timeout", logfile.read_text())
                time.sleep(.85)
                self.assertFalse(marker.exists(), "descendant survived process-group timeout")


if __name__ == "__main__":
    unittest.main()
