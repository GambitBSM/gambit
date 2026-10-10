#!/usr/bin/env python3
"""FastJet reuse checks with cmake -P and temporary archives/files only.

No project configure, compiler, make, download or real installation is used.
"""
from pathlib import Path
import hashlib
import io
import os
import re
import shutil
import subprocess
import tarfile
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
MODULE = ROOT / "cmake/ContribBuildIdentity.cmake"
LIBRARIES = {"fastjet": ("fastjet", "fastjettools", "fastjetplugins", "siscone_spherical", "siscone"),
             "fjcontrib": ("fastjetcontribfragile", "RecursiveTools", "EnergyCorrelator", "VariableR")}
HEADERS = {"fastjet": ("ClusterSequence.hh", "D0RunIIConePlugin.hh", "TrackJetPlugin.hh"),
           "fjcontrib": ("contrib/Nsubjettiness.hh", "contrib/SoftDrop.hh", "contrib/LundGenerator.hh")}
SOURCES = ("AxesDefinition", "MeasureDefinition", "ExtraRecombiners", "TauComponents", "Njettiness", "Nsubjettiness")
STEPS = ("download", "update", "prepare_source", "patch", "configure", "build", "install", "done", "record_identity")


def bracket(value):
    equals = ""
    while "]" + equals + "]" in str(value):
        equals += "="
    return "[" + equals + "[" + str(value) + "]" + equals + "]"


CAPTURE = r'''
function(add_custom_target name)
  file(APPEND "${CAPTURE_FILE}" "TARGET|${name}|${ARGN}\n")
endfunction()
function(add_dependencies name)
  file(APPEND "${CAPTURE_FILE}" "DEPENDENCY|${name}|${ARGN}\n")
endfunction()
function(ExternalProject_Add name)
  file(APPEND "${CAPTURE_FILE}" "EXTERNAL|${name}|${ARGN}\n")
endfunction()
function(ExternalProject_Add_Step name step)
  file(APPEND "${CAPTURE_FILE}" "STEP|${name}/${step}|${ARGN}\n")
endfunction()
function(include_directories)
endfunction()
function(set_compiler_warning warning flags)
  set(${flags} "${${flags}} -W${warning}" PARENT_SCOPE)
endfunction()
function(gambit_openmp_runtime_mismatch library output)
  set(${output} "${TEST_OPENMP_MISMATCH}" PARENT_SCOPE)
endfunction()
function(execute_process)
  message(FATAL_ERROR "Unexpected configure-time command: ${ARGV}")
endfunction()
'''


class ContribBuildIdentityTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-contrib-identity-")
        self.work = Path(self.temporary.name)
        self.source = self.work / "source tree [[x]]"
        self.build = self.work / "build tree"
        self.fastjet = self.source / "contrib/fastjet-3.5.1"
        self.fjcontrib = self.source / "contrib/fjcontrib-1.101"
        self.prefix = self.fastjet / "local"
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)
        self.put(self.source / "cmake/ContribBuildIdentity.cmake", MODULE.read_bytes())
        for package, names in LIBRARIES.items():
            for name in names:
                self.put(self.prefix / f"lib/lib{name}.a", b"fixture library")
            for name in HEADERS[package]:
                self.put(self.prefix / f"include/fastjet/{name}", b"fixture header")
            for step in STEPS:
                self.put(self.stamp(package, step), b"completed step")
            self.put(self.build / f"CMakeFiles/{package}-complete", b"completed package")
        self.put(self.prefix / "bin/fastjet-config", b"fixture config - never execute")
        for name in SOURCES:
            self.put(self.fjcontrib / f"Nsubjettiness/{name}.cc", b"fixture source")
        self.put(self.fastjet / "old.o", b"stale object")
        self.put(self.fjcontrib / "old.o", b"stale object")
        self.put(self.source / "contrib/unrelated/kept", b"unrelated install")
        self.put(self.build / "hepmc-prefix/src/hepmc-stamp/hepmc-install", b"unrelated stamp")
        for language in ("C", "CXX", "Fortran"):
            self.put(self.work / f"compiler {language}", b"fixture compiler - never execute")

    def tearDown(self):
        self.temporary.cleanup()

    def put(self, path, content):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(content)

    def stamp(self, package, step):
        return self.build / f"{package}-prefix/src/{package}-stamp/{package}-{step}"

    def record(self, package):
        return self.prefix / f".gambit-{package}-build-identity"

    def snapshot(self, root):
        return {str(p.relative_to(root)): (hashlib.sha256(p.read_bytes()).hexdigest(), p.stat().st_mtime_ns)
                for p in root.rglob("*") if p.is_file() and p.name not in ("selection.cmake", "capture.txt")}

    def select(self, changes=None, cache=None, bits="ColliderBit", mutate=None):
        settings = {"PROJECT_SOURCE_DIR": self.source, "CMAKE_BINARY_DIR": self.build, "GAMBIT_BITS": bits,
                    "CMAKE_SYSTEM_NAME": "Linux", "CMAKE_SYSTEM_PROCESSOR": "test-cpu", "CMAKE_BUILD_TYPE": "Release",
                    "CMAKE_CXX_STANDARD": "17", "CMAKE_CXX_STANDARD_REQUIRED": "ON", "CMAKE_CXX_EXTENSIONS": "OFF",
                    "BACKEND_C_FLAGS": "-O2", "BACKEND_CXX_FLAGS": "-O2 -std=c++17", "BACKEND_Fortran_FLAGS": "-O2",
                    "CMAKE_FIND_LIBRARY_PREFIXES": "lib", "CMAKE_FIND_LIBRARY_SUFFIXES": ".a;.so;.dylib",
                    "MAKE_PARALLEL": "make;-j8", "MAKE_INSTALL_PARALLEL": "make;-j8;install", "MAKE_SERIAL": "make",
                    "TEST_OPENMP_MISMATCH": "FALSE"}
        for language in ("C", "CXX", "Fortran"):
            settings.update({f"CMAKE_{language}_COMPILER": self.work / f"compiler {language}",
                             f"CMAKE_{language}_COMPILER_ID": "GNU", f"CMAKE_{language}_COMPILER_VERSION": "15.0"})
        settings.update(changes or {})
        text = (ROOT / "cmake/contrib.cmake").read_text()
        helpers = text[text.index("macro(get_paths "):text.index("#contrib/preload")]
        section = text[text.index("# FastJet / fjcontrib;"):text.index("# Jet clustering requires")]
        if mutate:
            section = mutate(section)
        utils = (ROOT / "cmake/utilities.cmake").read_text()
        strip = utils[utils.index("function(gambit_strip_openmp_from_flags"):utils.index("# Homebrew LLVM on macOS:")]
        capture = self.work / "capture.txt"
        lines = ["cmake_minimum_required(VERSION 3.16.3)"]
        lines += [f"set({k} {bracket(v)})" for k, v in settings.items()]
        for k, v in (cache or {}).items():
            lines += [f'set({k} {bracket(v)} CACHE FILEPATH "stale path" FORCE)', f"set({k} {bracket(v)})"]
        lines += ["set(CAPTURE_FILE " + bracket(capture) + ")", "file(WRITE " + bracket(capture) + ' "")',
                  CAPTURE, helpers, strip, section]
        for package, names in LIBRARIES.items():
            for name in names:
                key = f"{'FASTJET' if package == 'fastjet' else 'FJCONTRIB'}_{name}_LIBRARY"
                lines += [f'file(APPEND "${{CAPTURE_FILE}}" "LIBRARY|{key}|${{{key}}}\\n")']
        script = self.work / "selection.cmake"
        script.write_text("\n".join(lines))
        result = subprocess.run([self.cmake, "-P", str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        records = {k: {} for k in ("TARGET", "DEPENDENCY", "EXTERNAL", "STEP", "LIBRARY")}
        for line in capture.read_text().splitlines():
            kind, key, value = line.split("|", 2)
            records[kind][key] = value.split(";") if value else []
        return records

    def request(self, package):
        return self.build / f"{package}-prefix/tmp/{package}-identity-request.cmake"

    def action(self, package, action, success=True):
        result = subprocess.run([self.cmake, f"-DGAMBIT_CONTRIB_IDENTITY_ACTION={action}",
                                 f"-DGAMBIT_CONTRIB_IDENTITY_REQUEST={self.request(package)}", "-P", str(MODULE)],
                                capture_output=True, text=True)
        if success:
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        else:
            self.assertNotEqual(result.returncode, 0)
        return result

    def installed(self):
        self.select()
        for package in LIBRARIES:
            self.action(package, "RECORD")
            for step in STEPS:
                self.put(self.stamp(package, step), b"completed step")
            self.put(self.build / f"CMakeFiles/{package}-complete", b"completed package")

    def archive(self, package, valid=True):
        version = "3.5.1" if package == "fastjet" else "1.101"
        path = self.build / f"{package}_{version}.tar.gz"
        with tarfile.open(path, "w:gz") as archive:
            for name, content in {"configure": b"never execute", "src/pristine.cc": b"fresh source"}.items():
                entry = tarfile.TarInfo(f"{package}-{version}/{name}")
                entry.mode = 0o755 if name == "configure" else 0o644
                entry.size = len(content)
                archive.addfile(entry, io.BytesIO(content))
        checksum = hashlib.md5(path.read_bytes()).hexdigest() if valid else "wrong-checksum"
        with self.request(package).open("a") as stream:
            stream.write(f"\nset(CONTRIB_MD5 {bracket(checksum)})\n")

    def test_legacy_install_requires_rebuild_without_configure_time_deletion(self):
        before = self.snapshot(self.source)
        records = self.select()
        self.assertEqual(set(records["EXTERNAL"]), set(LIBRARIES))
        self.assertEqual(self.snapshot(self.source), before)
        for package in LIBRARIES:
            self.assertFalse(self.record(package).exists())
            prep = records["STEP"][package + "/prepare_source"]
            record = records["STEP"][package + "/record_identity"]
            self.assertEqual(prep[prep.index("DEPENDEES") + 1], "update")
            self.assertEqual(prep[prep.index("DEPENDERS") + 1], "patch")
            self.assertEqual(record[record.index("DEPENDEES") + 1], "install")
            self.assertFalse(self.stamp(package, "build").exists())
            self.assertFalse(self.stamp(package, "download").exists())
        self.assertIn("fastjet", records["EXTERNAL"]["fjcontrib"])

    def test_recorded_install_reuses_both_packages_and_preserves_timestamps(self):
        self.installed()
        before = self.snapshot(self.work)
        records = self.select()
        self.assertEqual(self.snapshot(self.work), before)
        self.assertFalse(records["EXTERNAL"])
        self.assertFalse(records["STEP"])
        self.assertFalse(self.select(changes={"GAMBIT_COMPILER_CACHE": "CCACHE"})["EXTERNAL"])
        for package in LIBRARIES:
            for name in (package, "clean-" + package, "nuke-" + package):
                self.assertIn(name, records["TARGET"])

    def test_stale_cached_paths_cannot_hide_deleted_fastjet_library(self):
        self.installed()
        library = self.prefix / "lib/libfastjet.a"
        foreign = self.work / "foreign/libfastjet.a"
        self.put(foreign, b"foreign library")
        records = self.select(cache={"FASTJET_fastjet_LIBRARY": foreign})
        self.assertFalse(records["EXTERNAL"])
        self.assertEqual(records["LIBRARY"]["FASTJET_fastjet_LIBRARY"], [str(library)])
        library.unlink()
        records = self.select(cache={"FASTJET_fastjet_LIBRARY": library})
        self.assertEqual(set(records["EXTERNAL"]), set(LIBRARIES))
        self.assertTrue(records["LIBRARY"]["FASTJET_fastjet_LIBRARY"][0].endswith("-NOTFOUND"))
        for package in LIBRARIES:
            self.assertFalse(self.stamp(package, "prepare_source").exists())
            self.assertFalse((self.build / f"CMakeFiles/{package}-complete").exists())
        self.assertTrue((self.build / "hepmc-prefix/src/hepmc-stamp/hepmc-install").exists())

    def test_missing_contrib_files_rebuild_only_contrib(self):
        self.installed()
        for path in (self.prefix / "lib/libVariableR.a", self.prefix / "include/fastjet/contrib/SoftDrop.hh",
                     self.fjcontrib / "Nsubjettiness/TauComponents.cc"):
            with self.subTest(path=path):
                content = path.read_bytes(); path.unlink()
                self.assertEqual(set(self.select()["EXTERNAL"]), {"fjcontrib"})
                self.put(path, content)
        (self.prefix / "bin/fastjet-config").unlink()
        self.assertEqual(set(self.select()["EXTERNAL"]), set(LIBRARIES))

    def test_compile_configuration_changes_reject_recorded_identity(self):
        self.installed()
        changes = [{"CMAKE_CXX_STANDARD": "20"}, {"CMAKE_CXX_COMPILER_VERSION": "16.0"},
                   {"BACKEND_CXX_FLAGS": "-O0 -std=c++17"}, {"CMAKE_OSX_ARCHITECTURES": "x86_64"},
                   {"MACOS_DEPLOYMENT_TARGET": "13.0"}, {"CMAKE_OSX_SYSROOT": "/other sdk"},
                   {"CMAKE_SYSTEM_PROCESSOR": "other-cpu"}, {"BACKEND_Fortran_FLAGS": "-O0"}]
        for change in changes:
            with self.subTest(change=change):
                old = [self.record(p).read_bytes() for p in LIBRARIES]
                self.assertEqual(set(self.select(changes=change)["EXTERNAL"]), set(LIBRARIES))
                self.assertEqual([self.record(p).read_bytes() for p in LIBRARIES], old)
        compiler = self.work / "compiler CXX"
        alias = self.work / "compiler alias"; alias.symlink_to(compiler)
        self.assertEqual(set(self.select(changes={"CMAKE_CXX_COMPILER": alias})["EXTERNAL"]), set(LIBRARIES))
        os.utime(compiler, (compiler.stat().st_atime, compiler.stat().st_mtime + 2))
        self.assertEqual(set(self.select()["EXTERNAL"]), set(LIBRARIES))

    def test_openmp_mismatch_and_contrib_link_flags_rebuild_only_contrib(self):
        self.installed()
        self.assertEqual(set(self.select(changes={"TEST_OPENMP_MISMATCH": "TRUE"})["EXTERNAL"]), {"fjcontrib"})
        records = self.select(mutate=lambda s: s.replace('set(FJCONTRIB_FRAGILE_CXX_FLAGS "${FASTJET_CXX_FLAGS}")',
                              'set(FJCONTRIB_FRAGILE_CXX_FLAGS "${FASTJET_CXX_FLAGS} -changed-link-flag")'))
        self.assertEqual(set(records["EXTERNAL"]), {"fjcontrib"})

    def test_pristine_prepare_removes_old_objects_and_only_owned_records(self):
        self.installed()
        self.archive("fjcontrib")
        fastjet_record = self.record("fastjet").read_bytes()
        self.action("fjcontrib", "PREPARE")
        self.assertFalse((self.fjcontrib / "old.o").exists())
        self.assertEqual((self.fjcontrib / "configure").read_bytes(), b"never execute")
        self.assertTrue((self.fjcontrib / "src/pristine.cc").exists())
        self.assertFalse(self.record("fjcontrib").exists())
        self.assertEqual(self.record("fastjet").read_bytes(), fastjet_record)
        self.archive("fastjet"); self.action("fastjet", "PREPARE")
        self.assertFalse((self.fastjet / "old.o").exists())
        self.assertTrue((self.fastjet / "src/pristine.cc").exists())
        self.assertFalse(self.prefix.exists())
        self.assertTrue((self.source / "contrib/unrelated/kept").exists())

    def test_bad_archive_and_incomplete_install_cannot_create_success_record(self):
        self.installed(); self.archive("fastjet", valid=False)
        before = self.snapshot(self.source)
        result = self.action("fastjet", "PREPARE", success=False)
        self.assertIn("checksum mismatch", result.stderr)
        self.assertEqual(self.snapshot(self.source), before)
        self.record("fjcontrib").unlink(); (self.prefix / "lib/libVariableR.a").unlink()
        self.action("fjcontrib", "RECORD", success=False)
        self.assertFalse(self.record("fjcontrib").exists())

    def test_prepare_rejects_paths_outside_owned_contrib_tree(self):
        self.installed(); self.archive("fastjet")
        foreign = self.work / "outside/kept"
        self.put(foreign, b"keep outside source root")
        with self.request("fastjet").open("a") as stream:
            stream.write(f"\nset(CONTRIB_SOURCE_DIR {bracket(foreign.parent)})\n")
        before = self.snapshot(self.source)
        self.action("fastjet", "PREPARE", success=False)
        self.assertEqual(foreign.read_bytes(), b"keep outside source root")
        self.assertEqual(self.snapshot(self.source), before)

    def test_missing_or_bad_cached_archive_invalidates_download_stamp(self):
        self.installed()
        (self.prefix / "lib/libfastjet.a").unlink()
        self.select()
        self.assertFalse(self.stamp("fastjet", "download").exists())
        self.put(self.stamp("fastjet", "download"), b"old download stamp")
        archive = self.build / "fastjet_3.5.1.tar.gz"
        self.put(archive, b"bad cached archive")
        before = self.snapshot(self.source)
        self.select()
        self.assertFalse(self.stamp("fastjet", "download").exists())
        self.assertEqual(archive.read_bytes(), b"bad cached archive")
        self.assertEqual(self.snapshot(self.source), before)
        self.archive("fastjet")
        checksum = hashlib.md5(archive.read_bytes()).hexdigest()
        self.put(self.stamp("fastjet", "download"), b"valid cached archive stamp")
        self.select(mutate=lambda s: re.sub(r'set\(fastjet_md5 "[^"]+"\)',
                    f'set(fastjet_md5 "{checksum}")', s, count=1))
        self.assertTrue(self.stamp("fastjet", "download").exists())

    def test_disabled_colliderbit_keeps_install_and_stamps(self):
        self.installed(); before = self.snapshot(self.work)
        records = self.select(bits="DarkBit")
        self.assertFalse(records["EXTERNAL"]); self.assertFalse(records["STEP"])
        self.assertEqual(self.snapshot(self.work), before)


if __name__ == "__main__":
    unittest.main(verbosity=2)
