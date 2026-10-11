#!/usr/bin/env python3
"""Check ONNX feature scope and optional runtime paths without a native build.

Execute the real package selection, target helpers and header generation in
cmake -P. Target creation, external projects and discovery are captured.
"""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

from restframes_scope import PROBES
from standalone_objects import CAPTURE_TARGETS, bracket


ROOT = Path(__file__).resolve().parents[2]
HEADER = '"gambit/cmake/onnxruntime_variables.hpp"'

CAPTURE = r'''
function(add_library target kind)
  mock_put("${target}" TYPE "${kind}")
  mock_put("${target}" INSTALL_RPATH "${CMAKE_INSTALL_RPATH}")
  _set_property(GLOBAL APPEND PROPERTY mock_targets "${target}")
endfunction()
function(target_include_directories target scope)
  mock_append("${target}" INCLUDE_DIRECTORIES "${ARGN}")
  mock_append("${target}" INCLUDE_SCOPES "${scope};${ARGN}")
  if(scope STREQUAL "PUBLIC" OR scope STREQUAL "INTERFACE")
    mock_append("${target}" INTERFACE_INCLUDE_DIRECTORIES "${ARGN}")
  endif()
endfunction()
function(include_directories)
  file(APPEND "${CAPTURE_FILE}" "DIRECTORY||${ARGN}\n")
endfunction()
function(ExternalProject_Add name)
  file(APPEND "${CAPTURE_FILE}" "EXTERNAL|${name}|${ARGN}\n")
endfunction()
function(ExternalProject_Add_Step)
endfunction()
function(add_install_name_tool_step)
endfunction()
function(gambit_strip_openmp_from_flags)
endfunction()
function(gambit_write_codegen_options)
endfunction()
function(gambit_check_codegen_outputs)
endfunction()
function(execute_process)
  message(FATAL_ERROR "Unexpected external command: ${ARGV}")
endfunction()
function(try_compile)
  message(FATAL_ERROR "Unexpected compiler check: ${ARGV}")
endfunction()
function(try_run)
  message(FATAL_ERROR "Unexpected program check: ${ARGV}")
endfunction()
'''


class OnnxRuntimeScopeTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-onnx-scope-")
        self.work = Path(self.temporary.name)
        self.source = self.work / "source tree"
        self.build = self.work / "build tree"
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)
        (self.source / "cmake").mkdir(parents=True)
        for module in ("ColliderBit", "DarkBit"):
            (self.source / module / "examples").mkdir(parents=True)
        for name in ("cmake_variables.hpp.in", "restframes_variables.hpp.in",
                     "onnxruntime_variables.hpp.in", "ContribBuildIdentity.cmake",
                     "scripts/patch_restframes_quiet.cmake"):
            (self.source / "cmake" / name).parent.mkdir(parents=True, exist_ok=True)
            if (ROOT / "cmake" / name).exists():
                shutil.copy2(ROOT / "cmake" / name, self.source / "cmake" / name)

    def tearDown(self):
        self.temporary.cleanup()

    def run_case(self, onnx=True, restframes=True, platform="Linux", extra="",
                 metadata=True):
        contrib = (ROOT / "cmake/contrib.cmake").read_text()
        helpers = contrib[contrib.index("macro(get_paths "):contrib.index("#contrib/preload")]
        rest = contrib[contrib.index("#contrib/RestFrames;"):contrib.index("#contrib/LHEF")]
        onnx_package = contrib[contrib.index("# contrib/onnxruntime"):contrib.index("#contrib/YODA;")]
        utilities = (ROOT / "cmake/utilities.cmake").read_text()
        names = ("add_gambit_library", "normalise_gambit_link_libraries",
                 "add_gambit_executable", "gambit_configure_standalone_objects",
                 "add_standalone")
        functions = [re.search(rf"function\({name}\b.*?endfunction\(\)", utilities,
                               re.DOTALL).group(0) for name in names]
        capture = self.work / "capture.txt"
        script = self.work / "fixture.cmake"
        parts = [
            "cmake_minimum_required(VERSION 3.16.3)",
            "set(PROJECT_SOURCE_DIR " + bracket(self.source) + ")",
            "set(CMAKE_BINARY_DIR " + bracket(self.build) + ")",
            "set(CAPTURE_FILE " + bracket(capture) + ")",
            'file(WRITE "${CAPTURE_FILE}" "")',
            "set(GAMBIT_BITS ColliderBit DarkBit)",
            'set(GAMBIT_INCDIRS "${PROJECT_SOURCE_DIR}/ColliderBit/include;${PROJECT_SOURCE_DIR}/Utils/include")',
            "set(CMAKE_INSTALL_RPATH /user/runtime /shared/runtime)",
            "set(CMAKE_SYSTEM_NAME " + platform + ")",
            "set(WITH_ONNXRUNTIME " + ("ON" if onnx else "OFF") + ")",
            "set(WITH_RESTFRAMES " + ("ON" if restframes else "OFF") + ")",
            "set(ROOT_FOUND TRUE)",
            "set(EXCLUDE_ROOT FALSE)",
            "set(EXCLUDE_HEPMC TRUE)",
            "set(EXCLUDE_YODA TRUE)",
            "set(EXCLUDE_FASTJET TRUE)",
            "set(Python3_EXECUTABLE /fixture/python3)",
            "set(STANDALONE_FACILITATOR /fixture/facilitator.py)",
            "set(HARVEST_TOOLS /fixture/harvesting_tools.py)",
            CAPTURE_TARGETS, CAPTURE, helpers, *functions,
        ]
        if metadata:
            parts += [rest, onnx_package]
        parts += [extra,
                  'file(APPEND "${CAPTURE_FILE}" "GLOBAL|rpath|${CMAKE_INSTALL_RPATH}\n")']
        for name in ("ColliderBit", "Models", "Utils", "Backends"):
            parts.append(f"add_gambit_library({name} OPTION OBJECT SOURCES fixture.cpp)")
        for name in ("first", "fortran", "FarrayTest", "cbs_preload", "gambit_preload"):
            parts.append(f"add_library({name} SHARED fixture.cpp)")
        parts += [
            'add_standalone(CBS MODULES ColliderBit SOURCES ColliderBit/examples/solo.cpp)',
            'add_standalone(DBS MODULES DarkBit SOURCES DarkBit/examples/solo.cpp)',
            'add_gambit_executable(gambit "${RESTFRAMES_LDFLAGS};${ONNXRUNTIME_LDFLAGS}" SOURCES main.cpp "$<TARGET_OBJECTS:ColliderBit>")',
            'add_gambit_executable(scanner "" SOURCES scanner.cpp)',
            'add_gambit_executable(onnx_only "${ONNXRUNTIME_LDFLAGS}" SOURCES onnx.cpp)',
            'get_property(targets GLOBAL PROPERTY mock_targets)',
            'foreach(target IN LISTS targets)',
            '  foreach(property INCLUDE_DIRECTORIES INCLUDE_SCOPES INTERFACE_INCLUDE_DIRECTORIES INSTALL_RPATH LINK_LIBRARIES DEPENDENCIES)',
            '    get_target_property(value "${target}" "${property}")',
            '    file(APPEND "${CAPTURE_FILE}" "${property}|${target}|${value}\n")',
            '  endforeach()',
            'endforeach()',
            PROBES, (ROOT / "cmake/preprocessor.cmake").read_text(),
        ]
        script.write_text("\n".join(parts))
        result = subprocess.run([self.cmake, "-P", str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return [line.split("|", 2) for line in capture.read_text().splitlines()]

    def prop(self, records, target, name):
        values = [record[2] for record in records if record[:2] == [name, target]]
        self.assertEqual(len(values), 1, (target, name, values))
        return [] if values[0].endswith("-NOTFOUND") else values[0].split(";")

    def headers(self):
        directory = self.source / "cmake/include/gambit/cmake"
        return {name: ((directory / name).read_bytes(), (directory / name).stat().st_mtime_ns)
                for name in ("cmake_variables.hpp", "restframes_variables.hpp",
                             "onnxruntime_variables.hpp") if (directory / name).exists()}

    def test_include_is_public_on_colliderbit_and_reaches_program_objects(self):
        records = self.run_case()
        path = str(self.source / "contrib/onnxruntime-1.14.1/include")
        self.assertFalse(Path(path).exists())
        self.assertIn(path, self.prop(records, "ColliderBit", "INTERFACE_INCLUDE_DIRECTORIES"))
        for target in ("ColliderBit", "CBS", "CBS_objects", "gambit", "onnx_only"):
            self.assertIn(path, self.prop(records, target, "INCLUDE_DIRECTORIES"), target)
        for target in ("Models", "Utils", "Backends", "DBS", "DBS_objects", "scanner"):
            self.assertNotIn(path, self.prop(records, target, "INCLUDE_DIRECTORIES"), target)
        self.assertFalse(any(r[0] == "DIRECTORY" and path in r[2] for r in records))

    def test_on_off_on_keeps_includes_and_common_header_stable(self):
        before_records = self.run_case()
        before = self.headers()
        self.assertIn("onnxruntime_variables.hpp", before)
        self.assertNotIn(b"EXCLUDE_ONNXRUNTIME", before["cmake_variables.hpp"][0])
        disabled_records = self.run_case(onnx=False)
        disabled = self.headers()
        self.assertEqual(disabled["cmake_variables.hpp"], before["cmake_variables.hpp"])
        self.assertEqual(disabled["restframes_variables.hpp"], before["restframes_variables.hpp"])
        self.assertIn(b"#define EXCLUDE_ONNXRUNTIME 1", disabled["onnxruntime_variables.hpp"][0])
        for target in ("ColliderBit", "Models", "Utils", "Backends", "CBS", "CBS_objects", "gambit"):
            self.assertEqual(self.prop(before_records, target, "INCLUDE_DIRECTORIES"),
                             self.prop(disabled_records, target, "INCLUDE_DIRECTORIES"))
        self.assertFalse(any(r[:2] == ["EXTERNAL", "onnxruntime"] for r in disabled_records))
        self.run_case()
        restored = self.headers()
        self.assertEqual(restored["cmake_variables.hpp"], before["cmake_variables.hpp"])
        self.assertEqual(restored["onnxruntime_variables.hpp"][0], before["onnxruntime_variables.hpp"][0])

    def test_runtime_paths_belong_only_to_actual_link_consumers(self):
        for platform in ("Linux", "Darwin"):
            with self.subTest(platform=platform):
                records = self.run_case(platform=platform)
                base = ["/user/runtime", "/shared/runtime"]
                optional = [str(self.source / "contrib/RestFrames-1.0.2/lib"),
                            str(self.source / "contrib/onnxruntime-1.14.1/lib")]
                self.assertIn(["GLOBAL", "rpath", ";".join(base)], records)
                for target in ("CBS", "gambit"):
                    self.assertEqual(self.prop(records, target, "INSTALL_RPATH"), base + optional)
                self.assertEqual(self.prop(records, "onnx_only", "INSTALL_RPATH"), base + optional[1:])
                for target in ("first", "fortran", "FarrayTest", "cbs_preload", "gambit_preload", "DBS", "scanner"):
                    self.assertEqual(self.prop(records, target, "INSTALL_RPATH"), base, target)

    def test_each_feature_switch_only_changes_its_consumers_runtime_path(self):
        enabled = self.run_case()
        for args, suffix in (({"onnx": False}, "RestFrames-1.0.2/lib"),
                             ({"restframes": False}, "onnxruntime-1.14.1/lib")):
            with self.subTest(args=args):
                records = self.run_case(**args)
                expected = ["/user/runtime", "/shared/runtime", str(self.source / "contrib" / suffix)]
                self.assertEqual(self.prop(records, "CBS", "INSTALL_RPATH"), expected)
                for target in ("first", "fortran", "FarrayTest", "cbs_preload", "gambit_preload", "DBS", "scanner"):
                    self.assertEqual(self.prop(records, target, "INSTALL_RPATH"),
                                     self.prop(enabled, target, "INSTALL_RPATH"), target)

    def test_user_runtime_paths_preserved_without_duplicate_package_path(self):
        optional = str(self.source / "contrib/onnxruntime-1.14.1/lib")
        extra = 'set(CMAKE_INSTALL_RPATH /user/first ' + bracket(optional) + ' /user/last)'
        for enabled in (True, False):
            with self.subTest(onnx=enabled):
                records = self.run_case(onnx=enabled, restframes=False, extra=extra)
                self.assertEqual(self.prop(records, "CBS", "INSTALL_RPATH"),
                                 ["/user/first", optional, "/user/last"])

    def test_no_package_metadata_keeps_partial_project_helpers_working(self):
        records = self.run_case(metadata=False)
        for target in ("ColliderBit", "CBS", "CBS_objects", "gambit", "scanner"):
            self.assertFalse(any("onnxruntime" in value for value in self.prop(records, target, "INCLUDE_DIRECTORIES")))
        self.assertEqual(self.prop(records, "CBS", "INSTALL_RPATH"), ["/user/runtime", "/shared/runtime"])

    def test_unchanged_headers_keep_timestamps_and_other_settings_work(self):
        self.run_case()
        before = self.headers()
        self.run_case()
        self.assertEqual(self.headers(), before)
        self.run_case(extra="set(EXCLUDE_HEPMC FALSE)")
        changed = self.headers()
        self.assertNotEqual(changed["cmake_variables.hpp"][0], before["cmake_variables.hpp"][0])
        self.assertEqual(changed["onnxruntime_variables.hpp"], before["onnxruntime_variables.hpp"])

    def test_on_off_keeps_installed_files_and_external_stamps(self):
        paths = [self.source / "contrib/onnxruntime-1.14.1/lib/kept.so",
                 self.source / "contrib/onnxruntime-1.14.1/include/kept.hpp",
                 self.build / "onnxruntime-prefix/src/onnxruntime-stamp/onnxruntime-download",
                 self.build / "onnxruntime-prefix/src/onnxruntime-stamp/onnxruntime-done"]
        for path in paths:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text("kept")
        before = [(p.read_bytes(), p.stat().st_mtime_ns) for p in paths]
        self.run_case()
        self.run_case(onnx=False)
        self.run_case()
        self.assertEqual([(p.read_bytes(), p.stat().st_mtime_ns) for p in paths], before)

    def test_all_consumers_include_feature_header_before_guards(self):
        common = (ROOT / "cmake/cmake_variables.hpp.in").read_text()
        self.assertNotIn("ONNXRUNTIME", common)
        result = subprocess.run(["git", "ls-files", "-z", "--", "*.cpp", "*.cxx", "*.cc", "*.c", "*.hpp", "*.h", "*.hh", "*.hxx"],
                                cwd=ROOT, capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        paths = {ROOT / name for name in result.stdout.split("\0") if name}
        paths.update((ROOT / "ColliderBit").rglob("*.cpp"))
        consumers = set()
        for path in sorted(paths):
            source = path.read_text()
            use = re.search(r"\bEXCLUDE_ONNXRUNTIME\b", source)
            if use:
                consumers.add(path.relative_to(ROOT).as_posix())
                include = source.find("#include " + HEADER)
                self.assertGreaterEqual(include, 0, str(path))
                self.assertLess(include, use.start(), str(path))
        expected = {"ColliderBit/include/gambit/ColliderBit/onnx_rt_wrapper.hpp",
                    "ColliderBit/src/onnx_rt_wrapper.cpp",
                    "ColliderBit/src/analyses/AnalysisContainer.cpp",
                    "ColliderBit/src/analyses/Analysis_ATLAS_SUSY_2018_30.cpp"}
        self.assertTrue(expected <= consumers)
        for path in ROOT.glob("*/include/**/*.hpp"):
            if path.name != "onnx_rt_wrapper.hpp":
                self.assertNotIn(HEADER, path.read_text(), str(path))


if __name__ == "__main__":
    unittest.main(verbosity=2)
