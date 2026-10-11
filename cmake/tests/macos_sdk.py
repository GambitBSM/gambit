#!/usr/bin/env python3
"""Check macOS SDK selection with cmake -P and synthetic xcrun responses.

No project configuration, language enablement or real executable probes.
"""

from pathlib import Path
import os
import re
import shlex
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]


def bracket(value):
    equals = ""
    while "]" + equals + "]" in str(value):
        equals += "="
    return "[" + equals + "[" + str(value) + "]" + equals + "]"


GUARD = r'''
function(execute_process)
  cmake_parse_arguments(PROBE "OUTPUT_STRIP_TRAILING_WHITESPACE;ERROR_QUIET"
    "RESULT_VARIABLE;OUTPUT_VARIABLE;ERROR_VARIABLE;TIMEOUT" "COMMAND" ${ARGN})
  list(LENGTH PROBE_COMMAND count)
  if(NOT count EQUAL 4)
    message(FATAL_ERROR "Unexpected executable probe: ${PROBE_COMMAND}")
  endif()
  list(GET PROBE_COMMAND 0 program)
  list(GET PROBE_COMMAND 1 option)
  list(GET PROBE_COMMAND 2 sdk)
  list(GET PROBE_COMMAND 3 operation)
  if(NOT program STREQUAL "xcrun" OR NOT option STREQUAL "--sdk")
    message(FATAL_ERROR "Real executable probe blocked: ${PROBE_COMMAND}")
  endif()
  file(APPEND "${FIXTURE_LOG}" "${sdk}|${operation}\n")
  set(result 0)
  set(output "")
  set(error "")
  if(sdk STREQUAL "bad-sdk")
    set(result 1)
    set(error "SDK unavailable in fixture")
  elseif(operation STREQUAL "--show-sdk-path")
    if(sdk STREQUAL "macosx")
      set(output "${FIXTURE_DEFAULT_SDK}")
    elseif(sdk STREQUAL "macosx17.0")
      set(output "${FIXTURE_NAMED_SDK}")
    elseif(sdk STREQUAL "missing-directory")
      set(output "${FIXTURE_DEFAULT_SDK}/missing")
    elseif(NOT sdk STREQUAL "empty-sdk")
      message(FATAL_ERROR "Unexpected SDK name: ${sdk}")
    endif()
  elseif(operation STREQUAL "--show-sdk-version")
    if(FIXTURE_VERSION_FAILURE)
      set(result 1)
      set(output "99.0")
    elseif(sdk STREQUAL FIXTURE_NAMED_SDK)
      set(output "17.0")
    elseif(sdk STREQUAL FIXTURE_DEFAULT_SDK OR sdk STREQUAL "macosx")
      set(output "27.0")
    else()
      message(FATAL_ERROR "Unexpected SDK version query: ${sdk}")
    endif()
  else()
    message(FATAL_ERROR "Unexpected xcrun operation: ${operation}")
  endif()
  foreach(key RESULT_VARIABLE OUTPUT_VARIABLE ERROR_VARIABLE)
    if(PROBE_${key})
      if(key STREQUAL "RESULT_VARIABLE")
        set(${PROBE_${key}} "${result}" PARENT_SCOPE)
      elseif(key STREQUAL "OUTPUT_VARIABLE")
        set(${PROBE_${key}} "${output}" PARENT_SCOPE)
      else()
        set(${PROBE_${key}} "${error}" PARENT_SCOPE)
      endif()
    endif()
  endforeach()
endfunction()
'''


class MacOSSDKTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-macos-sdk-")
        self.work = Path(self.temporary.name)
        self.selected = self.work / "Chosen.sdk"
        self.default = self.work / "Default.sdk"
        self.spaced = self.work / "SDK with spaces.sdk"
        for directory in (self.selected, self.default, self.spaced):
            directory.mkdir()
        self.log = self.work / "queries.log"
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)

    def tearDown(self):
        self.temporary.cleanup()

    def run_case(self, settings=None, sdkroot=None, flags=False, deployment=False,
                 host="Darwin", extra="", fatal=False, initialise=True):
        env = os.environ.copy()
        env.pop("SDKROOT", None)
        if sdkroot is not None:
            env["SDKROOT"] = str(sdkroot)
        self.log.write_text("")
        module = bracket(ROOT / "cmake/MacOSX.cmake")
        lines = ["cmake_minimum_required(VERSION 3.16.3)",
                 "set(CMAKE_HOST_SYSTEM_NAME " + bracket(host) + ")",
                 "set(CMAKE_SYSTEM_NAME " + bracket(host) + ")",
                 "set(CMAKE_CXX_COMPILER_ID AppleClang)",
                 "set(FIXTURE_DEFAULT_SDK " + bracket(self.default) + ")",
                 "set(FIXTURE_NAMED_SDK " + bracket(self.selected) + ")",
                 "set(FIXTURE_LOG " + bracket(self.log) + ")", GUARD]
        for name, value in (settings or {}).items():
            lines.append("set(" + name + " " + bracket(value) + " CACHE STRING fixture)")
        lines.append("include(" + module + ")")
        if initialise:
            lines.append("gambit_initialise_macos_sdk()")
        if deployment or flags:
            lines.append("gambit_initialise_macos_deployment_target()")
        if flags:
            lines.extend(["set(PROJECT_NAME fixture)", "include(" + module + ")"])
            # Evaluate only the real SDK flag assignments, not external project
            # definitions or any of their configure/build commands.
            for file, variable in (("cmake/backends.cmake", "Rivet_CPP_FLAGS"),
                                   ("cmake/contrib.cmake", "YODA_CONFIG_LDFLAGS")):
                source = (ROOT / file).read_text()
                assignment = re.search(r'^\s*(set\(' + variable + r' "[^\n]*"\))$',
                                       source, re.MULTILINE)
                self.assertIsNotNone(assignment)
                lines.append(assignment.group(1))
        lines.extend([extra,
                      'get_property(cached_root CACHE CMAKE_OSX_SYSROOT PROPERTY VALUE)',
                      'foreach(name CMAKE_OSX_SYSROOT cached_root MACOS_DEPLOYMENT_TARGET',
                      '  CMAKE_OSX_DEPLOYMENT_TARGET CMAKE_C_FLAGS CMAKE_CXX_FLAGS',
                      '  CMAKE_SHARED_LINKER_FLAGS Rivet_CPP_FLAGS YODA_CONFIG_LDFLAGS',
                      '  GAMBIT_MACOS_CMAKE_SYSROOT_ARG GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG)',
                      '  message(STATUS "RESULT_${name}=[${${name}}]")', 'endforeach()'])
        script = self.work / "case.cmake"
        script.write_text("\n".join(lines))
        result = subprocess.run([self.cmake, "-P", str(script)], cwd=self.work,
                                env=env, capture_output=True, text=True)
        output = result.stdout + result.stderr
        if fatal:
            self.assertNotEqual(result.returncode, 0, output)
            return " ".join(output.split())
        self.assertEqual(result.returncode, 0, output)
        return dict(re.findall(r"RESULT_(\w+)=\[(.*?)\]", output))

    def assert_sdk(self, values, expected):
        self.assertEqual(values["CMAKE_OSX_SYSROOT"], str(expected))
        self.assertEqual(values["cached_root"], str(expected))

    def test_explicit_path_overrides_sdkroot_without_a_probe(self):
        for path in (self.selected, self.spaced):
            with self.subTest(path=path):
                values = self.run_case({"CMAKE_OSX_SYSROOT": path}, sdkroot=self.default)
                self.assert_sdk(values, path)
                self.assertEqual(self.log.read_text(), "")

    def test_explicit_sdk_name_resolves_only_that_sdk(self):
        values = self.run_case({"CMAKE_OSX_SYSROOT": "macosx17.0"}, sdkroot=self.default)
        self.assert_sdk(values, self.selected)
        self.assertEqual(self.log.read_text(), "macosx17.0|--show-sdk-path\n")

    def test_sdkroot_path_and_name_are_used_when_cmake_selection_is_empty(self):
        for sdkroot, path in ((self.selected, self.selected), ("macosx17.0", self.selected)):
            with self.subTest(sdkroot=sdkroot):
                values = self.run_case({"CMAKE_OSX_SYSROOT": ""}, sdkroot=sdkroot)
                self.assert_sdk(values, path)
                self.assertNotIn("macosx|", self.log.read_text())

    def test_default_discovery_and_repeated_initialisation_are_stable(self):
        extra = ('set(ENV{SDKROOT} "bad-sdk")\n'
                 'gambit_initialise_macos_sdk()')
        values = self.run_case(extra=extra)
        self.assert_sdk(values, self.default)
        self.assertEqual(self.log.read_text(), "macosx|--show-sdk-path\n")

    def test_invalid_selections_and_failed_discovery_do_not_fall_back(self):
        file = self.work / "not-a-directory"
        file.write_text("fixture")
        for path in (self.work / "missing", file):
            with self.subTest(path=path):
                output = self.run_case({"CMAKE_OSX_SYSROOT": path}, fatal=True)
                self.assertIn("CMAKE_OSX_SYSROOT", output)
                self.assertIn("existing directory", output)
                self.assertEqual(self.log.read_text(), "")
        for name in ("bad-sdk", "empty-sdk", "missing-directory"):
            with self.subTest(name=name):
                output = self.run_case({"CMAKE_OSX_SYSROOT": name}, fatal=True)
                self.assertIn("CMAKE_OSX_SYSROOT", output)
                self.assertEqual(self.log.read_text(), name + "|--show-sdk-path\n")
        output = self.run_case(sdkroot="bad-sdk", fatal=True)
        self.assertIn("SDKROOT", output)

    def test_deployment_target_uses_selected_sdk_and_preserves_explicit_policy(self):
        values = self.run_case({"CMAKE_OSX_SYSROOT": self.selected}, deployment=True)
        self.assertEqual(values["MACOS_DEPLOYMENT_TARGET"], "17.0")
        self.assertEqual(values["CMAKE_OSX_DEPLOYMENT_TARGET"], "17.0")
        self.assertEqual(self.log.read_text(), str(self.selected) + "|--show-sdk-version\n")
        for settings, expected in (({"CMAKE_OSX_DEPLOYMENT_TARGET": "13.0"}, "13.0"),
                                   ({"MACOS_DEPLOYMENT_TARGET": "12.0",
                                     "CMAKE_OSX_DEPLOYMENT_TARGET": "13.0"}, "12.0")):
            with self.subTest(settings=settings):
                values = self.run_case({"CMAKE_OSX_SYSROOT": self.selected, **settings},
                                       deployment=True)
                self.assertEqual(values["MACOS_DEPLOYMENT_TARGET"], expected)
                self.assertEqual(values["CMAKE_OSX_DEPLOYMENT_TARGET"], expected)
                self.assertEqual(self.log.read_text(), "")
        output = self.run_case({"CMAKE_OSX_SYSROOT": self.selected,
                                "FIXTURE_VERSION_FAILURE": "TRUE"}, deployment=True, fatal=True)
        self.assertIn("Cannot determine the macOS deployment target", output)

    def test_native_and_backend_flags_use_the_selected_sdk_and_handle_spaces(self):
        for sdk in (self.selected, self.spaced):
            with self.subTest(sdk=sdk):
                values = self.run_case({"CMAKE_OSX_SYSROOT": sdk,
                                        "MACOS_DEPLOYMENT_TARGET": "13.0"}, flags=True)
                self.assert_sdk(values, sdk)
                self.assertEqual(self.log.read_text(), "")
                for name in ("CMAKE_C_FLAGS", "CMAKE_CXX_FLAGS", "CMAKE_SHARED_LINKER_FLAGS"):
                    tokens = shlex.split(values[name])
                    self.assertIn("-isysroot" + str(sdk), tokens)
                    self.assertIn("-mmacosx-version-min=13.0", tokens)
                self.assertIn("-L" + str(sdk) + "/usr/lib",
                              shlex.split(values["CMAKE_SHARED_LINKER_FLAGS"]))
                self.assertEqual(shlex.split(values["Rivet_CPP_FLAGS"]), ["-isysroot", str(sdk)])
                self.assertEqual(shlex.split(values["YODA_CONFIG_LDFLAGS"]),
                                 ["-L" + str(sdk) + "/usr/lib"])
                self.assertEqual(values["GAMBIT_MACOS_CMAKE_SYSROOT_ARG"],
                                 "-DCMAKE_OSX_SYSROOT=" + str(sdk))
                self.assertEqual(values["GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG"],
                                 "-DCMAKE_OSX_DEPLOYMENT_TARGET=13.0")

    def test_post_project_include_no_longer_overwrites_a_selected_sdk(self):
        values = self.run_case({"CMAKE_OSX_SYSROOT": self.selected,
                                "MACOS_DEPLOYMENT_TARGET": "13.0"},
                               flags=True, initialise=False)
        self.assert_sdk(values, self.selected)
        self.assertEqual(self.log.read_text(), "")

    def test_non_macos_and_pre_project_order(self):
        values = self.run_case({"CMAKE_OSX_SYSROOT": "leave-untouched"},
                               sdkroot="bad-sdk", host="Linux", deployment=True)
        self.assert_sdk(values, "leave-untouched")
        self.assertEqual(values["MACOS_DEPLOYMENT_TARGET"], "")
        self.assertEqual(self.log.read_text(), "")
        source = (ROOT / "CMakeLists.txt").read_text()
        project = re.search(r'^project\(', source, re.MULTILINE).start()
        self.assertLess(source.index("gambit_initialise_macos_sdk()"), project)
        self.assertLess(source.index("gambit_initialise_macos_deployment_target()"), project)

    def test_cmake_external_recipes_receive_the_selected_sdk(self):
        for name in ("cmake/backends.cmake", "cmake/contrib.cmake", "cmake/scanners.cmake"):
            source = (ROOT / name).read_text()
            for line in source.splitlines():
                if "CMAKE_ARGS " in line:
                    with self.subTest(file=name, recipe=line):
                        if "${VPP_CMAKE_FLAGS}" in line:
                            definition = re.search(r'^set\(VPP_CMAKE_FLAGS .*$', source, re.MULTILINE)
                            self.assertIsNotNone(definition)
                            line = definition.group(0)
                        self.assertIn("${GAMBIT_MACOS_CMAKE_SYSROOT_ARG}", line)


if __name__ == "__main__":
    unittest.main(verbosity=2)
