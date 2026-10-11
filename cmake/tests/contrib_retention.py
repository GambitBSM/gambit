#!/usr/bin/env python3
"""Check contrib retention with captured CMake registration and temporary files.

No project configure, make, compiler, download, or real installation is used.
"""

from pathlib import Path
import hashlib
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
PACKAGES = {"restframes": "RestFrames-1.0.2", "hepmc": "HepMC3-3.2.5", "yoda": "YODA-2.1.0"}
STEPS = ("configure", "build", "install", "done", "download", "mkdir", "patch", "update")


def bracket(value):
    equals = ""
    while "]" + equals + "]" in str(value):
        equals += "="
    return "[" + equals + "[" + str(value) + "]" + equals + "]"


CAPTURE = r'''
function(add_custom_target name)
  get_property(exists GLOBAL PROPERTY "target_${name}" SET)
  if(exists)
    message(FATAL_ERROR "Duplicate cleanup target: ${name}")
  endif()
  set_property(GLOBAL PROPERTY "target_${name}" "${ARGN}")
  file(APPEND "${CAPTURE_FILE}" "TARGET|${name}|${ARGN}\n")
endfunction()
function(add_dependencies name)
  file(APPEND "${CAPTURE_FILE}" "DEPENDENCY|${name}|${ARGN}\n")
endfunction()
function(ExternalProject_Add name)
  file(APPEND "${CAPTURE_FILE}" "EXTERNAL|${name}|\n")
endfunction()
function(ExternalProject_Add_Step)
endfunction()
function(include_directories)
endfunction()
function(add_install_name_tool_step)
endfunction()
function(set_compiler_warning)
endfunction()
function(gambit_strip_openmp_from_flags)
endfunction()
function(gambit_set_cxx_standard_flag flags standard output)
  set(${output} "${flags}" PARENT_SCOPE)
endfunction()
function(gambit_openmp_runtime_mismatch library output)
  set(${output} FALSE PARENT_SCOPE)
endfunction()
macro(gambit_find_python_module name)
  set(PY_${name}_FOUND FALSE)
endmacro()
# Fail immediately if a package selection starts any configure-time command.
function(execute_process)
  message(FATAL_ERROR "Unexpected configure-time command: ${ARGV}")
endfunction()
'''


class ContribRetentionTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-contrib-retention-")
        self.work = Path(self.temporary.name)
        self.source = self.work / "source tree"
        self.build = self.work / "build tree"
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)
        for package, directory in PACKAGES.items():
            for path in (self.source / "contrib" / directory / "src/kept.cpp",
                         self.source / "contrib" / directory / "local/lib/kept.so",
                         self.source / "contrib" / directory / "include/kept.hpp",
                         self.build / f"{package}-prefix/src/{package}-build/kept.o"):
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("retained " + package)
            for step in STEPS:
                path = self.stamp(package, step)
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("completed " + step)

        # Seed an installation recorded under the same fixture configuration.
        # Legacy installations are tested separately in restframes_build_identity.
        for name in ("ContribBuildIdentity.cmake", "scripts/patch_restframes_quiet.cmake"):
            target = self.source / "cmake" / name
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(ROOT / "cmake" / name, target)
        for name in ("inc/RestFrames/RestFrames.hh", "lib/libRestFrames.a"):
            target = self.source / "contrib/RestFrames-1.0.2" / name
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text("fixture installation")
        self.run_selection()
        identity = self.build / "restframes-prefix/tmp/restframes-identity.txt"
        record = self.source / "contrib/RestFrames-1.0.2/.gambit-restframes-build-identity"
        record.write_bytes(identity.read_bytes())
        for step in STEPS:
            self.stamp("restframes", step).write_text("completed " + step)

    def tearDown(self):
        self.temporary.cleanup()

    def stamp(self, package, step):
        return self.build / f"{package}-prefix/src/{package}-stamp/{package}-{step}"

    def snapshot(self, package=None):
        roots = [self.source, self.build]
        if package:
            roots = [self.source / "contrib" / PACKAGES[package],
                     self.build / f"{package}-prefix"]
        return {str(path): (hashlib.sha256(path.read_bytes()).hexdigest(), path.stat().st_mtime_ns)
                for root in roots for path in root.rglob("*") if path.is_file()}

    def run_selection(self, bits="ColliderBit", restframes=True, root=True):
        text = (ROOT / "cmake/contrib.cmake").read_text()
        helpers = text[text.index("macro(get_paths "):text.index("#contrib/preload")]
        sections = []
        for start, end in (("#contrib/RestFrames;", "#contrib/LHEF"),
                           ("#contrib/HepMC3;", "# contrib/onnxruntime"),
                           ("#contrib/YODA;", "# FastJet / fjcontrib;")):
            sections.append(text[text.index(start):text.index(end)])
        capture = self.work / "capture.txt"
        script = self.work / "registration.cmake"
        script.write_text("\n".join([
            "cmake_minimum_required(VERSION 3.16.3)",
            "set(PROJECT_SOURCE_DIR " + bracket(self.source) + ")",
            "set(CMAKE_BINARY_DIR " + bracket(self.build) + ")",
            "set(PROJECT_BINARY_DIR " + bracket(self.build) + ")",
            "set(CAPTURE_FILE " + bracket(capture) + ")",
            "file(WRITE " + bracket(capture) + ' "")',
            "set(GAMBIT_BITS " + bracket(bits) + ")",
            "set(WITH_RESTFRAMES " + ("ON" if restframes else "OFF") + ")",
            "set(ROOT_FOUND " + ("TRUE" if root else "FALSE") + ")",
            "set(EXCLUDE_ROOT " + ("FALSE" if root else "TRUE") + ")",
            "set(ROOT_STD 17)",
            "set(CMAKE_SYSTEM_NAME Linux)",
            "set(CMAKE_CXX_COMPILER_ID GNU)",
            "set(CMAKE_FIND_LIBRARY_PREFIXES lib)",
            "set(CMAKE_FIND_LIBRARY_SUFFIXES .a .so .dylib)",
            "set(UNIX FALSE)",  # skip the unrelated HDF5 wrapper probe
            "set(MAKE_SERIAL make)",
            "set(MAKE_PARALLEL make -j8)",
            CAPTURE, "include(" + bracket(ROOT / "cmake/MacOSX.cmake") + ")", helpers, *sections,
            'file(APPEND "${CAPTURE_FILE}" "EXCLUDED|restframes|${EXCLUDE_RESTFRAMES}\\n")',
            'file(APPEND "${CAPTURE_FILE}" "EXCLUDED|hepmc|${EXCLUDE_HEPMC}\\n")',
            'file(APPEND "${CAPTURE_FILE}" "EXCLUDED|yoda|${EXCLUDE_YODA}\\n")',
        ]))
        result = subprocess.run([self.cmake, "-P", str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        records = {"TARGET": {}, "DEPENDENCY": {}, "EXTERNAL": {}, "EXCLUDED": {}}
        for line in capture.read_text().splitlines():
            kind, name, value = line.split("|", 2)
            records[kind].setdefault(name, []).extend(value.split(";") if value else [])
        return records

    def assert_cleanup_available(self, records):
        for package in PACKAGES:
            for prefix in ("clean-", "nuke-"):
                self.assertIn(prefix + package, records["TARGET"])
                self.assertNotIn("ALL", records["TARGET"][prefix + package])
            self.assertIn("clean-" + package, records["DEPENDENCY"]["nuke-" + package])
            self.assertIn("nuke-" + package, records["DEPENDENCY"]["nuke-contrib"])
            self.assertIn("nuke-" + package, records["DEPENDENCY"]["nuke-all"])
            self.assertIn("clean-" + package, records["DEPENDENCY"]["distclean"])

    def test_restframes_off_keeps_all_content_and_excludes_only_its_target(self):
        before = self.snapshot()
        records = self.run_selection(restframes=False)
        self.assertEqual(self.snapshot(), before)
        self.assertEqual(records["EXCLUDED"]["restframes"], ["TRUE"])
        self.assertNotIn("restframes", records["EXTERNAL"])
        self.assertEqual(set(records["EXTERNAL"]), {"hepmc", "yoda"})
        self.assert_cleanup_available(records)

    def test_missing_root_disables_restframes_without_deletion(self):
        before = self.snapshot()
        records = self.run_selection(root=False)
        self.assertEqual(self.snapshot(), before)
        self.assertNotIn("restframes", records["EXTERNAL"])
        self.assertEqual(records["EXCLUDED"]["restframes"], ["TRUE"])
        self.assert_cleanup_available(records)

    def test_without_colliderbit_keeps_three_packages_and_their_stamps(self):
        for bits in ("DarkBit", "SpecBit", ""):
            with self.subTest(bits=bits):
                before = self.snapshot()
                records = self.run_selection(bits=bits)
                self.assertEqual(self.snapshot(), before)
                self.assertEqual(records["EXTERNAL"], {})
                for package in PACKAGES:
                    self.assertEqual(records["EXCLUDED"][package], ["TRUE"])
                self.assert_cleanup_available(records)

    def test_reenable_restores_registration_without_touching_retained_files(self):
        before = self.snapshot()
        self.run_selection(bits="DarkBit")
        records = self.run_selection()
        self.assertEqual(self.snapshot(), before)
        self.assertEqual(set(records["EXTERNAL"]), set(PACKAGES))
        for package in PACKAGES:
            self.assertEqual(records["EXCLUDED"][package], ["FALSE"])
        self.assert_cleanup_available(records)
        self.assertIn("gambit_preload", records["DEPENDENCY"]["restframes"])

    def test_explicit_nuke_commands_remove_only_requested_fixture(self):
        records = self.run_selection(bits="DarkBit")
        other = {p: self.snapshot(p) for p in ("hepmc", "yoda")}
        # Exercise the real registered cmake -E cleanup commands in this fixture
        # only. Never execute the clean target's shell/make commands.
        for target in ("clean-restframes", "nuke-restframes"):
            arguments = records["TARGET"][target]
            starts = [i for i, arg in enumerate(arguments) if arg == "COMMAND"]
            for index, start in enumerate(starts):
                end = starts[index + 1] if index + 1 < len(starts) else len(arguments)
                command = arguments[start + 1:end]
                if command[:2] != [self.cmake, "-E"]:
                    continue
                self.assertIn(command[2], ("remove", "remove_directory"))
                for argument in command[3:]:
                    if argument != "-f":
                        self.assertIn(self.work.resolve(), Path(argument).resolve().parents)
                result = subprocess.run(command, capture_output=True, text=True)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertFalse((self.source / "contrib/RestFrames-1.0.2").exists())
        self.assertFalse((self.build / "restframes-prefix/src/restframes-build").exists())
        for step in STEPS:
            self.assertFalse(self.stamp("restframes", step).exists())
        for package, before in other.items():
            self.assertEqual(self.snapshot(package), before)


if __name__ == "__main__":
    unittest.main(verbosity=2)
