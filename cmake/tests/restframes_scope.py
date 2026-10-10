#!/usr/bin/env python3
"""Check RestFrames include/header scope using script-only CMake fixtures.

Targets and probes are captured; no project configure, compiler, make,
download, or real installation is used. configure_file writes temporary headers.
"""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
HEADER = '"gambit/cmake/restframes_variables.hpp"'


def bracket(value):
    equals = ""
    while "]" + equals + "]" in str(value):
        equals += "="
    return "[" + equals + "[" + str(value) + "]" + equals + "]"


CAPTURE = r'''
function(add_library name)
  file(APPEND "${CAPTURE_FILE}" "LIBRARY|${name}|${ARGN}\n")
endfunction()
function(add_dependencies name)
  file(APPEND "${CAPTURE_FILE}" "DEPENDENCY|${name}|${ARGN}\n")
endfunction()
function(target_include_directories name scope)
  file(APPEND "${CAPTURE_FILE}" "INCLUDE|${name}|${scope};${ARGN}\n")
endfunction()
function(include_directories)
  file(APPEND "${CAPTURE_FILE}" "DIRECTORY||${ARGN}\n")
endfunction()
function(add_custom_target name)
  file(APPEND "${CAPTURE_FILE}" "CLEANUP|${name}|${ARGN}\n")
endfunction()
function(ExternalProject_Add name)
  file(APPEND "${CAPTURE_FILE}" "EXTERNAL|${name}|${ARGN}\n")
endfunction()
function(add_install_name_tool_step)
endfunction()
function(gambit_strip_openmp_from_flags)
endfunction()
function(execute_process)
  message(FATAL_ERROR "Unexpected external command: ${ARGV}")
endfunction()
'''


PROBES = r'''
# Replace only discovery; execute the actual header generation below.
function(include)
  if(NOT ARGV0 STREQUAL "CheckIncludeFiles" AND
     NOT ARGV0 STREQUAL "CMakeDependentOption")
    message(FATAL_ERROR "Unexpected include: ${ARGV}")
  endif()
endfunction()
macro(check_include_files header output)
  set(${output} FALSE)
endmacro()
macro(find_program output)
  set(${output} FALSE)
endmacro()
macro(cmake_dependent_option name description default dependency fallback)
  set(${name} "${fallback}")
endmacro()
'''


class RestFramesScopeTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-restframes-scope-")
        self.work = Path(self.temporary.name)
        self.source = self.work / "source tree"
        self.build = self.work / "build tree"
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)
        (self.source / "cmake").mkdir(parents=True)
        for name in ("cmake_variables.hpp.in", "restframes_variables.hpp.in"):
            shutil.copy2(ROOT / "cmake" / name, self.source / "cmake" / name)

    def tearDown(self):
        self.temporary.cleanup()

    def run_case(self, enabled=True, root=True, bits="ColliderBit", generate=True,
                 selection=True, extra=""):
        contrib = (ROOT / "cmake/contrib.cmake").read_text()
        helpers = contrib[contrib.index("macro(get_paths "):contrib.index("#contrib/preload")]
        package = contrib[contrib.index("#contrib/RestFrames;"):contrib.index("#contrib/LHEF")]
        utilities = (ROOT / "cmake/utilities.cmake").read_text()
        library = re.search(r"function\(add_gambit_library\b.*?endfunction\(\)",
                            utilities, re.DOTALL).group(0)
        capture = self.work / "capture.txt"
        script = self.work / "fixture.cmake"
        parts = [
            "cmake_minimum_required(VERSION 3.16.3)",
            "set(PROJECT_SOURCE_DIR " + bracket(self.source) + ")",
            "set(CMAKE_BINARY_DIR " + bracket(self.build) + ")",
            "set(CAPTURE_FILE " + bracket(capture) + ")",
            'file(WRITE "${CAPTURE_FILE}" "")',
            "set(GAMBIT_BITS " + bracket(bits) + ")",
            "set(WITH_RESTFRAMES " + ("ON" if enabled else "OFF") + ")",
            "set(ROOT_FOUND " + ("TRUE" if root else "FALSE") + ")",
            "set(EXCLUDE_ROOT " + ("FALSE" if root else "TRUE") + ")",
            'set(GAMBIT_INCDIRS "${PROJECT_SOURCE_DIR}/ColliderBit/include;${PROJECT_SOURCE_DIR}/Utils/include")',
            "set(CMAKE_SYSTEM_NAME Linux)",
            CAPTURE,
        ]
        if selection:
            parts.extend([helpers, package])
        parts.extend([library, extra])
        for name in ("ColliderBit", "Models", "Utils", "Backends", "CBS_objects", "mkpath"):
            parts.append(f"add_gambit_library({name} OPTION OBJECT SOURCES fixture.cpp)")
        parts.append('file(APPEND "${CAPTURE_FILE}" "EXCLUDED|restframes|${EXCLUDE_RESTFRAMES}\\n")')
        if generate:
            parts.extend([PROBES, (ROOT / "cmake/preprocessor.cmake").read_text()])
        script.write_text("\n".join(parts))
        result = subprocess.run([self.cmake, "-P", str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return [line.split("|", 2) for line in capture.read_text().splitlines()]

    def includes(self, records):
        return [record for record in records if record[0] in ("INCLUDE", "DIRECTORY")]

    def headers(self):
        directory = self.source / "cmake/include/gambit/cmake"
        return {name: ((directory / name).read_bytes(), (directory / name).stat().st_mtime_ns)
                for name in ("cmake_variables.hpp", "restframes_variables.hpp")}

    def test_enabled_path_is_private_and_only_on_colliderbit(self):
        records = self.run_case()
        path = str(self.source / "contrib/RestFrames-1.0.2/inc")
        self.assertFalse(Path(path).exists(), "No real installation is needed")
        references = [r for r in self.includes(records) if path in r[2]]
        self.assertEqual(references, [["INCLUDE", "ColliderBit", "PRIVATE;" + path]])
        self.assertFalse(any(r[0] == "DIRECTORY" for r in records))
        self.assertIn(["DEPENDENCY", "restframes", "gambit_preload"], records)
        self.assertEqual({r[1] for r in records if r[0] == "CLEANUP"},
                         {"clean-restframes", "nuke-restframes"})
        self.assertTrue(any(r[:2] == ["EXTERNAL", "restframes"] for r in records))

    def test_off_and_unavailable_keep_paths_without_registering_package(self):
        baseline = self.includes(self.run_case())
        for arguments in ({"enabled": False}, {"root": False},
                          {"bits": "DarkBit"}, {"bits": ""}):
            with self.subTest(arguments=arguments):
                records = self.run_case(**arguments)
                self.assertEqual(self.includes(records), baseline)
                self.assertIn(["EXCLUDED", "restframes", "TRUE"], records)
                self.assertFalse(any(r[0] == "EXTERNAL" for r in records))
                self.assertEqual({r[1] for r in records if r[0] == "CLEANUP"},
                                 {"clean-restframes", "nuke-restframes"})

    def test_library_helper_without_package_metadata_adds_no_private_path(self):
        records = self.run_case(generate=False, selection=False)
        self.assertTrue(self.includes(records))
        self.assertFalse(any("PRIVATE;" in r[2] for r in self.includes(records)))

    def test_off_on_only_changes_feature_header(self):
        self.run_case()
        before = self.headers()
        self.assertIn(b"/* #undef EXCLUDE_RESTFRAMES */", before["restframes_variables.hpp"][0])
        path_macro = ('#define RESTFRAMES_INCLUDE "' +
                      str(self.source / "contrib/RestFrames-1.0.2/inc") + '"').encode()
        self.assertIn(path_macro, before["restframes_variables.hpp"][0])
        self.run_case(enabled=False)
        disabled = self.headers()
        self.assertEqual(disabled["cmake_variables.hpp"], before["cmake_variables.hpp"])
        self.assertIn(b"#define EXCLUDE_RESTFRAMES 1", disabled["restframes_variables.hpp"][0])
        self.assertIn(path_macro, disabled["restframes_variables.hpp"][0])
        self.assertNotEqual(disabled["restframes_variables.hpp"][0], before["restframes_variables.hpp"][0])
        self.run_case()
        restored = self.headers()
        self.assertEqual(restored["cmake_variables.hpp"], before["cmake_variables.hpp"])
        self.assertEqual(restored["restframes_variables.hpp"][0], before["restframes_variables.hpp"][0])

    def test_unchanged_headers_stay_stable_and_other_options_still_update(self):
        self.run_case()
        before = self.headers()
        self.run_case()
        self.assertEqual(self.headers(), before)
        self.run_case(extra="set(EXCLUDE_HEPMC TRUE)")
        after = self.headers()
        self.assertNotEqual(after["cmake_variables.hpp"][0], before["cmake_variables.hpp"][0])
        self.assertEqual(after["restframes_variables.hpp"], before["restframes_variables.hpp"])

    def test_missing_root_excludes_both_features_in_their_headers(self):
        self.run_case(root=False)
        headers = self.headers()
        self.assertIn(b"#define EXCLUDE_ROOT 1", headers["cmake_variables.hpp"][0])
        self.assertIn(b"#define EXCLUDE_RESTFRAMES 1", headers["restframes_variables.hpp"][0])

    def test_consumers_include_feature_header_before_guards(self):
        common = (ROOT / "cmake/cmake_variables.hpp.in").read_text()
        self.assertNotIn("RESTFRAMES", common)
        self.assertNotIn("restframes_variables.hpp", common)
        # Audit tracked C/C++ sources across the repository, including contrib
        # preload. Also cover locally added ColliderBit implementations.
        result = subprocess.run(["git", "ls-files", "-z", "--", "*.cpp", "*.cxx", "*.cc",
                                 "*.c", "*.hpp", "*.h", "*.hh", "*.hxx"],
                                cwd=ROOT, capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        paths = {ROOT / name for name in result.stdout.split("\0") if name}
        paths.update((ROOT / "ColliderBit").rglob("*.cpp"))
        consumers = []
        for path in sorted(paths):
            source = path.read_text()
            use = re.search(r"\b(?:EXCLUDE_RESTFRAMES|RESTFRAMES_INCLUDE)\b", source)
            dependency = re.search(r'^\s*#\s*include\s*[<"]RestFrames/', source, re.MULTILINE)
            if use or dependency:
                consumers.append(path.name)
                include = source.find("#include " + HEADER)
                self.assertGreaterEqual(include, 0, str(path))
                self.assertLess(include, (use or dependency).start(), str(path))
        self.assertIn("AnalysisContainer.cpp", consumers)
        self.assertIn("gambit_preload.cpp", consumers)
        self.assertGreaterEqual(len(consumers), 6)
        for path in ROOT.glob("*/include/**/*.hpp"):
            self.assertNotIn(HEADER, path.read_text(), str(path))


if __name__ == "__main__":
    unittest.main(verbosity=2)
