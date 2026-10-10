#!/usr/bin/env python3
"""Exercise automatic rebuild checks on temporary files and captured EP commands.

No project configure, compiler, make, download, or real installation is used.
"""

import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
TRACKER = ROOT / "cmake/scripts/external_rebuild.py"


def bracket(value):
    equals = ""
    while "]" + equals + "]" in str(value):
        equals += "="
    return "[" + equals + "[" + str(value) + "]" + equals + "]"


class ExternalAutoRebuildTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-external-rebuild-")
        self.work = Path(self.temporary.name)
        # An ancestor named build must not hide all declared source files.
        self.source = self.work / "build/source [[tree]]"
        self.build = self.work / "build tree"
        self.input = self.source / "src/code.cc"
        self.output = self.source / "local/lib/package.so"
        self.configure_output = self.source / "Makefile"
        self.stamp = self.build / "package-prefix/src/package-stamp/package"
        self.record = self.build / "package-prefix/tmp/package-source-state.json"
        for path in (self.input, self.output, self.configure_output):
            self.write(path, "original " + path.name)
        self.restore_stamps()

    def tearDown(self):
        self.temporary.cleanup()

    def write(self, path, text):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)

    def step(self, name):
        return Path(str(self.stamp) + "-" + name)

    def restore_stamps(self):
        for name in ("download", "patch", "configure", "build", "install", "done", "record_source_state"):
            self.write(self.step(name), "successful " + name)

    def run_tracker(self, action, configuration="compiler-and-flags", extra=(), success=True):
        command = [sys.executable, str(TRACKER), action, "--package", "package",
                   "--stamp", str(self.stamp), "--record", str(self.record),
                   "--source-root", str(self.source),
                   "--configuration", configuration,
                   "--input", str(self.source / "src/**/*"),
                   "--input", str(self.configure_output),
                   "--output", str(self.output),
                   "--configure-output", str(self.configure_output), *extra]
        result = subprocess.run(command, capture_output=True, text=True)
        self.assertEqual(result.returncode == 0, success, result.stdout + result.stderr)
        return result

    def snapshot(self):
        return {str(p): (p.read_bytes(), p.stat().st_mtime_ns)
                for p in self.work.rglob("*") if p.is_file()}

    def test_migration_and_unchanged_build_keep_source_products_and_stamps(self):
        before = self.snapshot()
        result = self.run_tracker("check")
        self.assertIn("no recorded successful", result.stdout)
        self.assertEqual(self.snapshot(), {k: v for k, v in before.items() if k != str(self.step("build"))})
        self.assertFalse(self.record.exists())
        self.restore_stamps()
        self.run_tracker("record")
        before = self.snapshot()
        self.assertEqual(self.run_tracker("check").stdout, "")
        self.run_tracker("record")
        self.assertEqual(self.snapshot(), before)
        self.assertIn(str(self.input), json.loads(self.record.read_text())["sources"])

    def test_content_edits_same_timestamp_and_nanosecond_touch_trigger_rebuild(self):
        self.run_tracker("record")
        stat = self.input.stat()
        self.input.write_bytes(b"x" * stat.st_size)
        os.utime(self.input, ns=(stat.st_atime_ns, stat.st_mtime_ns))
        self.run_tracker("check")
        self.assertFalse(self.step("build").exists())
        self.restore_stamps()
        self.run_tracker("record")
        stat = self.input.stat()
        os.utime(self.input, ns=(stat.st_atime_ns, stat.st_mtime_ns + 1))
        self.run_tracker("check")
        self.assertFalse(self.step("build").exists())

    def test_added_and_removed_sources_trigger_without_reconfigure(self):
        self.run_tracker("record")
        added = self.input.with_name("new.cc")
        self.write(added, "new source")
        self.run_tracker("check")
        self.assertFalse(self.step("build").exists())
        self.restore_stamps()
        self.run_tracker("record")
        added.unlink()
        self.run_tracker("check")
        self.assertFalse(self.step("build").exists())

    def test_generated_objects_and_cache_changes_are_ignored(self):
        self.run_tracker("record")
        for name in ("src/code.o", "src/code.lo", "src/code.la", "src/plugin.so",
                     "src/.libs/lib.a", "src/.deps/code.Plo", "src/build/generated.cc",
                     "src/__pycache__/code.pyc"):
            self.write(self.source / name, "generated")
        before = self.snapshot()
        self.assertEqual(self.run_tracker("check").stdout, "")
        self.assertEqual(self.snapshot(), before)

    def test_missing_library_and_configure_product_invalidate_only_owned_steps(self):
        self.run_tracker("record")
        self.output.unlink()
        self.run_tracker("check")
        self.assertFalse(self.step("build").exists())
        self.assertTrue(self.step("configure").exists())
        self.assertTrue(self.step("patch").exists())
        self.restore_stamps()
        self.write(self.output, "restored")
        self.configure_output.unlink()
        self.run_tracker("check")
        self.assertFalse(self.step("configure").exists())
        self.assertFalse(self.step("build").exists())
        self.assertTrue(self.step("patch").exists())

    def test_failed_build_or_incomplete_install_cannot_refresh_success_record(self):
        self.run_tracker("record")
        record = self.record.read_bytes(), self.record.stat().st_mtime_ns
        self.write(self.input, "changed")
        for _ in range(2):
            self.restore_stamps()
            self.run_tracker("check")
            self.assertFalse(self.step("build").exists())
            self.assertEqual((self.record.read_bytes(), self.record.stat().st_mtime_ns), record)
        self.output.unlink()
        self.run_tracker("record", success=False)
        self.assertEqual((self.record.read_bytes(), self.record.stat().st_mtime_ns), record)

    def test_build_command_change_and_installed_dependency_change_invalidate(self):
        self.run_tracker("record")
        self.run_tracker("check", configuration="new compiler flags")
        self.assertFalse(self.step("build").exists())
        self.restore_stamps()
        dependency = self.work / "dependency/local/lib/library.so"
        self.write(dependency, "installed dependency")
        extra = ["--dependency-input", str(dependency)]
        self.run_tracker("record", extra=extra)
        self.write(dependency, "changed library")
        self.run_tracker("check", extra=extra)
        self.assertFalse(self.step("build").exists())

    def test_corrupt_record_and_empty_source_install_are_rejected(self):
        self.write(self.record, "not valid JSON")
        self.run_tracker("check")
        self.assertFalse(self.step("build").exists())
        self.input.unlink()
        self.configure_output.unlink()
        self.run_tracker("record", success=False)
        self.assertEqual(self.record.read_text(), "not valid JSON")
        self.write(self.input, "restored source")
        self.write(self.configure_output, "restored Makefile")
        self.restore_stamps()
        self.record.write_bytes(b"\xff")
        self.run_tracker("check")
        self.assertFalse(self.step("build").exists())
        self.run_tracker("record")
        self.assertEqual(json.loads(self.record.read_text())["schema"], 1)

    def test_product_globs_accept_alternate_python_installation_layout(self):
        module = self.source / "local/local/lib/python3.11/dist-packages/rivet/core.so"
        self.write(module, "Python extension")
        extra = ["--output", str(self.source / "local/**/rivet/core.so")]
        self.run_tracker("record", extra=extra)
        self.assertEqual(self.run_tracker("check", extra=extra).stdout, "")
        module.unlink()
        self.run_tracker("check", extra=extra)
        self.assertFalse(self.step("build").exists())

    def registration(self, pyext=True):
        text = (ROOT / "cmake/externals.cmake").read_text()
        helpers = text[text.index("include(ExternalAutoRebuild)"):text.index("# Function to check whether")]
        text = (ROOT / "cmake/backends.cmake").read_text()
        nulike = text[text.index('# Nulike'):text.index('# SUSY-HIT')]
        rivet = text[text.index('# Rivet\n'):text.index('# Contur\n')]
        contur = text[text.index('# Contur\n'):text.index('unset(_contur_build_command)')]
        capture = self.work / "capture.txt"
        script = self.work / "registration.cmake"
        script.write_text("\n".join([
            "cmake_minimum_required(VERSION 3.16.3)",
            "set(CMAKE_MODULE_PATH " + bracket(ROOT / "cmake") + ")",
            "set(PROJECT_SOURCE_DIR " + bracket(self.source) + ")",
            "set(CMAKE_BINARY_DIR " + bracket(self.build) + ")",
            "set(Python3_EXECUTABLE " + bracket(sys.executable) + ")",
            "set(CAPTURE_FILE " + bracket(capture) + ")",
            "set(CMAKE_SYSTEM_NAME Linux)",
            "set(MAKE_SERIAL make -j1)", "set(MAKE_PARALLEL make)",
            "set(CBS_PRESET_BUILD TRUE)",
            "set(PY_cython_FOUND " + ("TRUE" if pyext else "FALSE") + ")",
            "set(PYTHON_VERSION_MAJOR 3)", "set(PYTHON_VERSION_MINOR 13)",
            "set(YODA_PATH " + bracket(self.source / "contrib/YODA") + ")",
            "set(HEPMC_PATH " + bracket(self.source / "contrib/HepMC") + ")",
            "set(fastjet_DIR " + bracket(self.source / "contrib/fastjet/local") + ")",
            r'''
function(add_custom_target name)
  file(APPEND "${CAPTURE_FILE}" "TARGET|${name}|${ARGN}\n")
endfunction()
function(add_dependencies name)
  file(APPEND "${CAPTURE_FILE}" "DEPENDENCY|${name}|${ARGN}\n")
endfunction()
function(ExternalProject_Add name)
  cmake_parse_arguments(EP "" "SOURCE_DIR;BUILD_IN_SOURCE" "DEPENDS;DOWNLOAD_COMMAND;PATCH_COMMAND;CONFIGURE_COMMAND;BUILD_COMMAND;INSTALL_COMMAND" ${ARGN})
  foreach(field DEPENDS CONFIGURE_COMMAND BUILD_COMMAND INSTALL_COMMAND)
    set(_CAP_${name}__EP_${field} "${EP_${field}}" CACHE INTERNAL "" FORCE)
  endforeach()
endfunction()
function(get_property output)
  set(${output} "${_CAP_${ARGV2}_${ARGV4}}" PARENT_SCOPE)
endfunction()
function(ExternalProject_Get_Property package)
  set(STAMP_DIR "${CMAKE_BINARY_DIR}/${package}-prefix/src/${package}-stamp" PARENT_SCOPE)
  set(TMP_DIR "${CMAKE_BINARY_DIR}/${package}-prefix/tmp" PARENT_SCOPE)
endfunction()
function(ExternalProject_Add_Step name step)
  file(APPEND "${CAPTURE_FILE}" "STEP|${name}:${step}|${ARGN}\n")
endfunction()
function(ExternalProject_Add_StepDependencies)
endfunction()
function(add_external_clean)
endfunction()
function(set_as_default_version)
endfunction()
function(set_target_properties)
endfunction()
function(check_ditch_status)
endfunction()
function(check_python_modules)
endfunction()
function(set_compiler_warning)
endfunction()
function(gambit_set_cxx_standard_flag flags standard output)
  set(${output} "${flags} -std=c++${standard}" PARENT_SCOPE)
endfunction()
function(gambit_find_python_module)
endfunction()
function(BOSS_backend name version)
  file(APPEND "${CAPTURE_FILE}" "BOSS|${name}_${version}|${ARGN}\n")
endfunction()
function(execute_process)
  message(FATAL_ERROR "Unexpected configure-time command: ${ARGV}")
endfunction()
''', helpers, nulike, rivet, contur]))
        result = subprocess.run([shutil.which("cmake"), "-P", str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        records = {}
        for line in capture.read_text().splitlines():
            kind, name, value = line.split("|", 2)
            records.setdefault(kind, {})[name] = value.split(";")
        return records

    def test_registration_tracks_three_packages_preserves_other_backends_and_order(self):
        records = self.registration()
        for package in ("nulike_1.0.9", "rivet_4.1.0", "contur_3.0.0"):
            command = records["TARGET"]["check-rebuild-" + package]
            self.assertIn(str(TRACKER), command)
            self.assertIn("check", command)
            self.assertIn("VERBATIM", command)
            self.assertIn("check-rebuild-" + package, records["DEPENDENCY"][package])
            step = records["STEP"][package + ":record_source_state"]
            self.assertIn("record", step)
            self.assertEqual(step[step.index("DEPENDEES") + 1], "install")
        legacy = records["TARGET"]["check-rebuild-nulike_1.0.8"]
        self.assertNotIn(str(TRACKER), legacy)
        self.assertIn("remove", legacy)
        self.assertIn("rivet_4.1.0", records["DEPENDENCY"]["check-rebuild-contur_3.0.0"])
        for package in ("castxml", "yoda", "hepmc", "fastjet", "fjcontrib"):
            self.assertIn(package, records["DEPENDENCY"]["check-rebuild-rivet_4.1.0"])
        self.assertIn("rivet_4.1.0:prepare_source", records["STEP"])
        self.assertIn("rivet_4.1.0", records["BOSS"])
        rivet = records["TARGET"]["check-rebuild-rivet_4.1.0"]
        self.assertIn(str(self.source / "contrib/fastjet/local/.gambit-*-build-identity"), rivet)
        self.assertIn(str(self.source / "Backends/installed/rivet/4.1.0/local/**/rivet/core.so"), rivet)

    def test_registration_without_python_extension_does_not_require_python_products(self):
        command = self.registration(pyext=False)["TARGET"]["check-rebuild-rivet_4.1.0"]
        self.assertFalse(any("/rivet/core.so" in item for item in command))
        self.assertIn("--configure-output", command)


if __name__ == "__main__":
    unittest.main(verbosity=2)
