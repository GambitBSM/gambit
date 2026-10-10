#!/usr/bin/env python3
"""Exercise compiler-cache policy with cmake -P, never configure or compile."""

from pathlib import Path
import os
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


class CompilerCacheTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-compiler-cache-")
        self.work = Path(self.temporary.name)
        # The space also verifies command argument boundaries for launchers.
        self.bin = self.work / "tools with space"
        self.bin.mkdir()
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)

    def tearDown(self):
        self.temporary.cleanup()

    def fake_ccache(self, broken=False):
        path = self.bin / "ccache"
        path.write_text(
            "#!/bin/sh\n"
            '[ "$1" = --version ] || exit 99\n'
            + ("exit 42\n" if broken else "printf 'ccache version 4.13.6\\n'\n")
        )
        path.chmod(0o755)
        return str(path)

    def run_case(self, settings="", cache_input="", fail=False):
        script = self.work / "case.cmake"
        # Search only the fixture PATH, with actual find_program semantics.
        script.write_text("\n".join([
            "cmake_minimum_required(VERSION 3.16.3)",
            "set(CMAKE_GENERATOR \"Unix Makefiles\")",
            "set(CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH FALSE)",
            "set(CMAKE_FIND_USE_CMAKE_PATH FALSE)",
            "set(CMAKE_FIND_USE_CMAKE_SYSTEM_PATH FALSE)",
            "set(CMAKE_FIND_USE_PACKAGE_ROOT_PATH FALSE)",
            cache_input,
            settings,
            "include(" + bracket(ROOT / "cmake/CompilerCache.cmake") + ")",
            "gambit_configure_compiler_cache()",
            "function(cbs_summary_line label value)",
            '  message(STATUS "${label}: ${value}")',
            "endfunction()",
            "gambit_print_compiler_cache_summary()",
            "foreach(language C CXX Fortran)",
            '  if(DEFINED CMAKE_${language}_COMPILER_LAUNCHER)',
            '    message(STATUS "LAUNCHER_${language}=[${CMAKE_${language}_COMPILER_LAUNCHER}]")',
            "  else()",
            '    message(STATUS "LAUNCHER_${language}=UNDEFINED")',
            "  endif()",
            "endforeach()",
            # Persist only cache variables to simulate the next configure.
            "get_cmake_property(variables CACHE_VARIABLES)",
            "file(WRITE " + bracket(self.work / "saved-cache.cmake") + ' "")',
            "foreach(variable IN LISTS variables)",
            '  if(variable MATCHES "^(GAMBIT_COMPILER_CACHE|CMAKE_(C|CXX|Fortran)_COMPILER_LAUNCHER)$")',
            '    get_property(value CACHE "${variable}" PROPERTY VALUE)',
            "    file(APPEND " + bracket(self.work / "saved-cache.cmake")
            + ' "set(${variable} [====[${value}]====] CACHE STRING fixture FORCE)\\n")',
            "  endif()",
            "endforeach()",
            'if(DEFINED CACHE{_gambit_ccache_program})',
            '  message(FATAL_ERROR "Discovery path must not persist in cache")',
            "endif()",
        ]))
        env = os.environ.copy()
        env["PATH"] = str(self.bin)
        result = subprocess.run([self.cmake, "-P", str(script)], env=env,
                                capture_output=True, text=True)
        output = result.stdout + result.stderr
        if fail:
            self.assertNotEqual(result.returncode, 0, output)
        else:
            self.assertEqual(result.returncode, 0, output)
        return output

    def test_preset_auto_and_ordinary_configure_defaults(self):
        ccache = self.fake_ccache()
        output = self.run_case()
        self.assertIn("Compiler cache: OFF", output)
        self.assertIn("LAUNCHER_CXX=UNDEFINED", output)
        for selector in ("CBS_BUILD_PRESET cbs-llvm", "GAMBIT_PRESET_TOOLCHAIN gnu",
                         "GAMBIT_BUILD_PRESET gambit-hpc"):
            with self.subTest(selector=selector):
                output = self.run_case(f"set({selector})")
                self.assertIn("AUTO: ccache 4.13.6", output)
                for language in ("C", "CXX"):
                    self.assertIn(f"LAUNCHER_{language}=[{ccache}]", output)
                self.assertIn("LAUNCHER_Fortran=UNDEFINED", output)

    def test_explicit_launchers_and_empty_values_are_preserved(self):
        ccache = self.fake_ccache()
        for explicit in ("/custom/sccache", "/usr/bin/env;CACHE_MODE=test;/custom/cache", ""):
            with self.subTest(explicit=explicit):
                output = self.run_case(
                    "set(GAMBIT_COMPILER_CACHE AUTO)\n"
                    + "set(CMAKE_CXX_COMPILER_LAUNCHER " + bracket(explicit) + " CACHE STRING fixture)\n"
                    + "set(CMAKE_Fortran_COMPILER_LAUNCHER /custom/fortran)")
                self.assertIn(f"LAUNCHER_CXX=[{explicit}]", output)
                self.assertIn(f"LAUNCHER_C=[{ccache}]", output)
                self.assertIn("LAUNCHER_Fortran=[/custom/fortran]", output)
                self.assertIn("explicit" if explicit else "explicit empty", output)
        # Fully explicit choices take precedence even over required ccache.
        (self.bin / "ccache").unlink()
        output = self.run_case(
            "set(GAMBIT_COMPILER_CACHE CCACHE)\n"
            "set(CMAKE_C_COMPILER_LAUNCHER /custom/wrapper)\n"
            "set(CMAKE_CXX_COMPILER_LAUNCHER \"\")")
        self.assertIn("explicit launchers retained", output)

    def test_missing_or_broken_ccache_falls_back_or_fails_as_requested(self):
        for broken in (False, True):
            with self.subTest(broken=broken):
                if broken:
                    self.fake_ccache(broken=True)
                output = self.run_case("set(GAMBIT_COMPILER_CACHE AUTO)")
                self.assertIn("ccache unavailable", output)
                self.assertIn("LAUNCHER_CXX=UNDEFINED", output)
                output = self.run_case("set(GAMBIT_COMPILER_CACHE CCACHE)", fail=True)
                self.assertIn("requires a working ccache on PATH", output)

    def test_off_and_reconfigure_do_not_leave_automatic_launchers_cached(self):
        ccache = self.fake_ccache()
        self.run_case("set(CBS_BUILD_PRESET cbs-llvm)")
        saved = (self.work / "saved-cache.cmake").read_text()
        self.assertIn("GAMBIT_COMPILER_CACHE", saved)
        self.assertNotIn("COMPILER_LAUNCHER", saved)
        # OFF is effective on a new configure without -U or --fresh.
        output = self.run_case("set(GAMBIT_COMPILER_CACHE OFF CACHE STRING fixture FORCE)",
                               cache_input=saved)
        self.assertIn("LAUNCHER_CXX=UNDEFINED", output)
        # A user launcher remains a user choice when auto caching is off.
        output = self.run_case(
            "set(GAMBIT_COMPILER_CACHE OFF)\n"
            + "set(CMAKE_CXX_COMPILER_LAUNCHER " + bracket(ccache) + " CACHE STRING fixture)")
        self.assertIn(f"LAUNCHER_CXX=[{ccache}]", output)

    def test_reconfigure_rechecks_tool_availability_and_keeps_user_cache(self):
        self.fake_ccache()
        self.run_case("set(CBS_BUILD_PRESET cbs-llvm)\n"
                      "set(CMAKE_C_COMPILER_LAUNCHER /custom/wrapper CACHE STRING fixture)")
        saved = (self.work / "saved-cache.cmake").read_text()
        (self.bin / "ccache").unlink()
        output = self.run_case(cache_input=saved)
        self.assertIn("AUTO: ccache unavailable", output)
        self.assertIn("LAUNCHER_CXX=UNDEFINED", output)
        self.assertIn("LAUNCHER_C=[/custom/wrapper]", output)

    def test_generator_support_and_invalid_mode_diagnostics(self):
        self.fake_ccache()
        for generator in ("Unix Makefiles", "Ninja", "Ninja Multi-Config"):
            with self.subTest(generator=generator):
                output = self.run_case("set(GAMBIT_COMPILER_CACHE CCACHE)\n"
                                       + "set(CMAKE_GENERATOR " + bracket(generator) + ")")
                self.assertIn("CCACHE: ccache 4.13.6", output)
        output = self.run_case("set(GAMBIT_COMPILER_CACHE AUTO)\nset(CMAKE_GENERATOR Xcode)")
        self.assertIn("unavailable for generator Xcode", output)
        self.assertIn("LAUNCHER_CXX=UNDEFINED", output)
        output = self.run_case("set(GAMBIT_COMPILER_CACHE CCACHE)\nset(CMAKE_GENERATOR Xcode)", fail=True)
        self.assertIn("require a Makefiles or Ninja generator", output)
        output = self.run_case("set(GAMBIT_COMPILER_CACHE typo)", fail=True)
        self.assertIn("Use AUTO, CCACHE, or OFF", output)

    def test_launcher_initialisation_precedes_all_native_targets_and_summaries_use_it(self):
        main = (ROOT / "CMakeLists.txt").read_text()
        self.assertLess(main.index("project(gambit C CXX Fortran)"),
                        main.index("gambit_configure_compiler_cache()"))
        self.assertLess(main.index("gambit_configure_compiler_cache()"),
                        main.index("use_contributed_pybind11()"))
        for name in ("CBSCompilerSummary.cmake", "GAMBITBuildSummary.cmake"):
            self.assertIn("gambit_print_compiler_cache_summary()",
                          (ROOT / "cmake/presets" / name).read_text())


if __name__ == "__main__":
    unittest.main(verbosity=2)
