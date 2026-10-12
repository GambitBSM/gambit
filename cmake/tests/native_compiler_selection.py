#!/usr/bin/env python3
"""Check native compiler selection with cmake -P and fake version reporters.

Never configure the project, enable languages, or invoke a real compiler.
All executable probes outside the temporary fixture are blocked.
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
  cmake_parse_arguments(PROBE "OUTPUT_STRIP_TRAILING_WHITESPACE;ERROR_STRIP_TRAILING_WHITESPACE;ERROR_QUIET"
    "RESULT_VARIABLE;OUTPUT_VARIABLE;ERROR_VARIABLE;TIMEOUT" "COMMAND" ${ARGN})
  list(GET PROBE_COMMAND 0 program)
  get_filename_component(program_real "${program}" REALPATH)
  get_filename_component(fixture_real "${FIXTURE_ROOT}" REALPATH)
  string(FIND "${program_real}" "${fixture_real}/" position)
  if(position EQUAL 0)
    _execute_process(${ARGV})
  else()
    # Automatic search may inspect real installation locations, but cannot
    # execute anything in them. They are unavailable in this fixture.
    set(${PROBE_RESULT_VARIABLE} 97)
    if(PROBE_OUTPUT_VARIABLE)
      set(${PROBE_OUTPUT_VARIABLE} "")
    endif()
    if(PROBE_ERROR_VARIABLE)
      set(${PROBE_ERROR_VARIABLE} "Real executable blocked by fixture")
    endif()
  endif()
  foreach(key RESULT_VARIABLE OUTPUT_VARIABLE ERROR_VARIABLE)
    if(PROBE_${key})
      set(${PROBE_${key}} "${${PROBE_${key}}}" PARENT_SCOPE)
    endif()
  endforeach()
endfunction()
'''


class NativeCompilerSelectionTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-compiler-selection-")
        self.work = Path(self.temporary.name)
        self.bin = self.work / "path tools"
        self.bin.mkdir()
        self.log = self.work / "probes.log"
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)
        self.selected = self.pair("chosen llvm", "18.1.8")
        self.default = self.pair("default llvm", "22.1.8")
        self.fortran = self.compiler(self.bin / "gfortran", "GNU", "14.2.0")
        brew = self.bin / "brew"
        brew.write_text("#!/bin/sh\n"
                        + 'printf "%s\\n" "$0 $*" >> ' + shlex.quote(str(self.log)) + "\n"
                        + '[ "$*" = "--prefix llvm" ] || exit 99\n'
                        + 'printf "%s\\n" "$FIXTURE_LLVM_ROOT"\n')
        brew.chmod(0o755)

    def tearDown(self):
        self.temporary.cleanup()

    def compiler(self, path, family="Clang", version="18.1.8"):
        path.parent.mkdir(parents=True, exist_ok=True)
        banner = {"Clang": "clang version ", "AppleClang": "Apple clang version ",
                  "GNU": "GNU compiler "}[family] + version
        path.write_text("#!/bin/sh\n"
                        + 'printf "%s\\n" "$0 $*" >> ' + shlex.quote(str(self.log)) + "\n"
                        + 'if [ "$*" = "--version" ]; then\n'
                        + "  printf '%s\\n' " + shlex.quote(banner) + "\n"
                        + 'elif [ "$*" = "-dumpfullversion -dumpversion" ]; then\n'
                        + "  printf '%s\\n' " + shlex.quote(version) + "\n"
                        + "else\n  exit 99\nfi\n")
        path.chmod(0o755)
        return path

    def pair(self, name, version, family="Clang", suffix=""):
        directory = self.work / name / "bin"
        return (self.compiler(directory / ("clang" + suffix), family, version),
                self.compiler(directory / ("clang++" + suffix), family, version))

    def run_case(self, settings=None, environment=None, mode="find", host="Darwin",
                 strategy="llvm", extra="", fatal=False):
        env = os.environ.copy()
        for name in ("CC", "CXX", "FC", "CMAKE_C_COMPILER", "CMAKE_CXX_COMPILER"):
            env.pop(name, None)
        env.update({"PATH": str(self.bin), "FC": shlex.quote(str(self.fortran)),
                    "FIXTURE_LLVM_ROOT": str(self.default[0].parents[1])})
        env.update(environment or {})
        self.log.write_text("")
        script = self.work / "case.cmake"
        lines = ["cmake_minimum_required(VERSION 3.16.3)",
                 "set(FIXTURE_ROOT " + bracket(self.work) + ")",
                 "set(CMAKE_HOST_SYSTEM_NAME " + bracket(host) + ")",
                 "set(CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH FALSE)",
                 "set(CMAKE_FIND_USE_CMAKE_PATH FALSE)",
                 "set(CMAKE_FIND_USE_CMAKE_SYSTEM_PATH FALSE)",
                 "set(CMAKE_FIND_USE_PACKAGE_ROOT_PATH FALSE)", GUARD]
        for name, value in (settings or {}).items():
            lines.append("set(" + name + " " + bracket(value) + " CACHE STRING fixture)")
        if mode == "configure":
            lines.extend(["include(" + bracket(ROOT / "cmake/toolchains/NativePresetToolchain.cmake") + ")",
                          "native_configure_preset_toolchain(" + strategy + ")", extra,
                          'set(found TRUE)', 'set(c "${CMAKE_C_COMPILER}")',
                          'set(cxx "${CMAKE_CXX_COMPILER}")', 'set(fortran "${CMAKE_Fortran_COMPILER}")',
                          'set(root "${GAMBIT_RESOLVED_LLVM_ROOT}")',
                          'set(version "${GAMBIT_RESOLVED_LLVM_VERSION}")', 'set(reason "")'])
        else:
            lines.extend(["include(" + bracket(ROOT / "cmake/presets/NativeCompilerDiscovery.cmake") + ")",
                          f"native_find_toolchain({strategy} found c cxx fortran root version reason)", extra])
        lines.extend(['foreach(name found c cxx fortran root version reason)',
                      '  message(STATUS "RESULT_${name}=[${${name}}]")', 'endforeach()'])
        script.write_text("\n".join(lines))
        result = subprocess.run([self.cmake, "-P", str(script)], env=env, cwd=self.work,
                                capture_output=True, text=True)
        text = result.stdout + result.stderr
        if fatal:
            self.assertNotEqual(result.returncode, 0, text)
            return text
        self.assertEqual(result.returncode, 0, text)
        values = dict(re.findall(r"RESULT_(\w+)=\[(.*?)\]", text))
        self.assertEqual(set(values), {"found", "c", "cxx", "fortran", "root", "version", "reason"}, text)
        return values

    def assert_selected(self, values, pair=None):
        pair = pair or self.selected
        self.assertEqual(values["found"], "TRUE", values["reason"])
        self.assertEqual(values["c"], str(pair[0]))
        self.assertEqual(values["cxx"], str(pair[1]))
        self.assertEqual(values["fortran"], str(self.fortran))
        self.assertEqual(values["root"], str(pair[1].resolve().parents[1]))
        self.assertNotIn("brew --prefix", self.log.read_text())

    def test_cached_compilers_override_environment_and_default_installation(self):
        for mode in ("find", "configure"):
            with self.subTest(mode=mode):
                values = self.run_case({"CMAKE_C_COMPILER": self.selected[0],
                                        "CMAKE_CXX_COMPILER": self.selected[1]},
                                       {"CC": "/missing/cc", "CXX": str(self.default[1])}, mode)
                self.assert_selected(values)

        values = self.run_case({"CMAKE_C_COMPILER": self.selected[0]},
                               {"CC": str(self.default[0]), "CXX": str(self.selected[1])})
        self.assert_selected(values)

    def test_environment_pair_overrides_default_for_bootstrap_and_toolchain(self):
        for mode in ("find", "configure"):
            with self.subTest(mode=mode):
                values = self.run_case(environment={"CC": str(self.selected[0]),
                                                    "CXX": str(self.selected[1])}, mode=mode)
                self.assert_selected(values)

    def test_partial_selection_finds_matching_companion(self):
        for settings, environment in (({"CMAKE_C_COMPILER": self.selected[0]}, {}),
                                      ({"CMAKE_CXX_COMPILER": self.selected[1]}, {}),
                                      ({}, {"CC": str(self.selected[0])}),
                                      ({}, {"CXX": str(self.selected[1])})):
            with self.subTest(settings=settings, environment=environment):
                self.assert_selected(self.run_case(settings, environment))

    def test_versioned_names_do_not_select_an_unversioned_other_version(self):
        pair = self.pair("shared bin", "18.1.8", suffix="-18")
        self.pair("shared bin", "22.1.8")
        for name, path in (("CC", pair[0]), ("CXX", pair[1])):
            with self.subTest(name=name):
                self.assert_selected(self.run_case(environment={name: str(path)}), pair)

    def test_symlink_companion_and_root_use_the_real_installation(self):
        alias = self.bin / "clang-18"
        alias.symlink_to(self.selected[0])
        values = self.run_case(environment={"CC": str(alias)})
        self.assert_selected(values, (alias, self.selected[1].resolve()))

    def test_command_names_and_quoted_or_literal_paths_with_spaces(self):
        for quoted in (False, True):
            with self.subTest(quoted=quoted):
                pair = [shlex.quote(str(p)) if quoted else str(p) for p in self.selected]
                values = self.run_case({"CMAKE_C_COMPILER": pair[0], "CMAKE_CXX_COMPILER": pair[1]},
                                       mode="configure")
                self.assert_selected(values)
        self.compiler(self.work / "clang", "GNU", "14.2.0")
        values = self.run_case(environment={"PATH": str(self.selected[0].parent) + os.pathsep + str(self.bin),
                                            "CC": "clang", "CXX": "clang++"})
        self.assert_selected(values)

    def test_invalid_explicit_selections_fail_without_automatic_fallback(self):
        apple = self.pair("apple", "17.0.0", "AppleClang")
        gnu = self.pair("gnu", "14.2.0", "GNU")
        old = self.pair("old llvm", "9.0.0")
        cases = [({"CC": "/missing/clang", "CXX": str(self.selected[1])}, "CC requests"),
                 ({"CC": str(self.selected[0]), "CXX": "/missing/clang++"}, "CXX requests"),
                 ({"CC": str(apple[0]), "CXX": str(apple[1])}, "AppleClang"),
                 ({"CC": str(gnu[0]), "CXX": str(gnu[1])}, "GNU"),
                 ({"CC": str(old[0]), "CXX": str(old[1])}, "older than"),
                 ({"CC": str(self.selected[0]), "CXX": str(self.default[1])}, "18.1.8"),
                 ({"CC": str(self.selected[0]), "CXX": str(apple[1])}, "AppleClang")]
        for env, reason in cases:
            with self.subTest(environment=env):
                values = self.run_case(environment=env)
                self.assertEqual(values["found"], "FALSE")
                self.assertIn(reason, values["reason"])
                self.assertNotIn("brew --prefix", self.log.read_text())
        error = self.run_case({"CMAKE_C_COMPILER": "/missing/compiler"}, mode="configure", fatal=True)
        self.assertIn("CMAKE_C_COMPILER requests", error)

    def test_missing_companion_and_compiler_arguments_have_clear_errors(self):
        alone = self.compiler(self.work / "half install/bin/clang")
        values = self.run_case(environment={"CC": str(alone)})
        self.assertEqual(values["found"], "FALSE")
        self.assertIn("set CMAKE_CXX_COMPILER or CXX explicitly", values["reason"])
        self.assertNotIn("brew --prefix", self.log.read_text())
        plain = self.compiler(self.work / "plain/bin/clang")
        for command in (shlex.quote(str(self.selected[0])) + " --target=fixture",
                        str(plain) + ";--target=fixture"):
            with self.subTest(command=command):
                values = self.run_case(environment={"CC": command})
                self.assertEqual(values["found"], "FALSE")
                self.assertIn("must name one compiler executable", values["reason"])

    def test_all_profiles_reject_arguments_in_compiler_selectors(self):
        for strategy, host, family in (("llvm", "Darwin", "Clang"),
                                       ("macos", "Darwin", "AppleClang"),
                                       ("gnu", "Linux", "GNU")):
            pair = self.pair(strategy, "18.1.8", family)
            environment = {"CC": str(pair[0]), "CXX": str(pair[1])}
            for language, name, path in (("C", "CC", pair[0]), ("CXX", "CXX", pair[1]),
                                         ("Fortran", "FC", self.fortran)):
                for cached in (False, True):
                    selector = "CMAKE_" + language + "_COMPILER" if cached else name
                    for command in (shlex.quote(str(path)) + " --target=fixture",
                                    str(path) + ";--target=fixture",
                                    "ccache " + shlex.quote(str(path))):
                        settings = {selector: command} if cached else {}
                        env = dict(environment)
                        if not cached:
                            env[name] = command
                        with self.subTest(strategy=strategy, selector=selector, command=command):
                            values = self.run_case(settings, env, strategy=strategy, host=host)
                            self.assertEqual(values["found"], "FALSE")
                            self.assertIn(selector + " must name one compiler executable", values["reason"])
                            self.assertIn("CMAKE_" + language + "_FLAGS", values["reason"])
                            error = self.run_case(settings, env, mode="configure", fatal=True,
                                                  strategy=strategy, host=host)
                            self.assertIn("must name one compiler executable", " ".join(error.split()))

    def test_fortran_selection_reports_missing_explicit_executable_without_fallback(self):
        for cached in (False, True):
            selector = "CMAKE_Fortran_COMPILER" if cached else "FC"
            settings = {selector: "/missing/fortran"} if cached else {}
            environment = {} if cached else {"FC": "/missing/fortran"}
            with self.subTest(selector=selector):
                values = self.run_case(settings, environment)
                self.assertEqual(values["found"], "FALSE")
                self.assertIn(selector + " requests", values["reason"])
                self.assertNotIn(str(self.fortran) + " --version", self.log.read_text())

    def test_all_profiles_accept_fortran_paths_with_spaces_and_separate_flags(self):
        for strategy, host, family in (("llvm", "Darwin", "Clang"),
                                       ("macos", "Darwin", "AppleClang"),
                                       ("gnu", "Linux", "GNU")):
            pair = self.pair(strategy, "18.1.8", family)
            for quoted in (False, True):
                fortran = shlex.quote(str(self.fortran)) if quoted else str(self.fortran)
                for cached in (False, True):
                    settings = {"CMAKE_C_FLAGS": "-fno-omit-frame-pointer",
                                "CMAKE_CXX_FLAGS": "-fsanitize=undefined",
                                "CMAKE_Fortran_FLAGS": "-ffpe-trap=invalid"}
                    environment = {"CC": str(pair[0]), "CXX": str(pair[1])}
                    if cached:
                        settings["CMAKE_Fortran_COMPILER"] = fortran
                        environment["FC"] = "/missing/overridden-fortran"
                    else:
                        environment["FC"] = fortran
                    extra = "\n".join(
                        'if(NOT "${' + name + '}" STREQUAL ' + bracket(value) + ')\n'
                        '  message(FATAL_ERROR "Compiler flags changed: ' + name + '")\nendif()'
                        for name, value in settings.items() if name.endswith("_FLAGS"))
                    with self.subTest(strategy=strategy, quoted=quoted, cached=cached):
                        values = self.run_case(settings, environment, mode="configure", extra=extra,
                                               strategy=strategy, host=host)
                        self.assertEqual(values["found"], "TRUE")
                        self.assertEqual(values["fortran"], str(self.fortran))

    def test_cached_pair_stays_selected_on_repeated_toolchain_load(self):
        extra = ('set(ENV{CC} "/missing/new-cc")\n'
                 'set(ENV{CXX} "/missing/new-cxx")\n'
                 'native_configure_preset_toolchain(llvm)')
        values = self.run_case(environment={"CC": str(self.selected[0]), "CXX": str(self.selected[1])},
                               mode="configure", extra=extra)
        self.assert_selected(values)

    def test_no_selection_keeps_automatic_search_on_both_hosts(self):
        values = self.run_case()
        self.assertEqual(values["found"], "TRUE", values["reason"])
        self.assertEqual(values["c"], str(self.default[0]))
        self.assertIn("brew --prefix llvm", self.log.read_text())
        pair = (self.compiler(self.bin / "clang-22", version="22.1.8"),
                self.compiler(self.bin / "clang++-22", version="22.1.8"))
        values = self.run_case(host="Linux")
        self.assertEqual(values["found"], "TRUE", values["reason"])
        self.assertEqual((values["c"], values["cxx"]), tuple(map(str, pair)))
        self.assertNotIn("brew --prefix", self.log.read_text())

    def test_other_profiles_and_shared_cache_contract_are_preserved(self):
        for strategy, host, family in (("macos", "Darwin", "AppleClang"), ("gnu", "Linux", "GNU")):
            pair = self.pair(strategy, "17.0.0", family)
            with self.subTest(strategy=strategy):
                values = self.run_case(environment={"CC": str(pair[0]), "CXX": str(pair[1])},
                                       strategy=strategy, host=host, mode="configure")
                self.assertEqual(values["found"], "TRUE")
                self.assertEqual((values["c"], values["cxx"]), tuple(map(str, pair)))
        error = self.run_case({"GAMBIT_PRESET_TOOLCHAIN": "macos"}, mode="configure", fatal=True)
        self.assertIn("loaded the cached llvm toolchain", " ".join(error.split()))
        self.assertIn("--fresh", error)


if __name__ == "__main__":
    unittest.main(verbosity=2)
