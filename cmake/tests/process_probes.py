#!/usr/bin/env python3
"""Exercise process-local discovery with cmake -P, fake tools and Python modules.

Never configure/build the project or invoke a real compiler. execute_process is
restricted to temporary fixture executables and CMake -E echo (report output).
Python imports use fixture packages.
"""
from pathlib import Path
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def quote(value):
    value = str(value)
    equals = ""
    while "]" + equals + "]" in value:
        equals += "="
    return "[" + equals + "[" + value + "]" + equals + "]"


GUARD = r'''
function(execute_process)
  cmake_parse_arguments(PARSE_ARGV 0 P
    "OUTPUT_STRIP_TRAILING_WHITESPACE;ERROR_STRIP_TRAILING_WHITESPACE;ERROR_QUIET"
    "RESULT_VARIABLE;OUTPUT_VARIABLE;ERROR_VARIABLE;TIMEOUT;WORKING_DIRECTORY" "COMMAND")
  list(GET P_COMMAND 0 program)
  get_filename_component(program "${program}" REALPATH)
  string(FIND "${program}" "${FIXTURE_ROOT}/" position)
  get_filename_component(cmake_program "${CMAKE_COMMAND}" REALPATH)
  if(program STREQUAL cmake_program AND P_COMMAND MATCHES ";-E;echo;")
    set(position 0) # bootstrap's output-only report writer
  endif()
  if(NOT position EQUAL 0)
    message(FATAL_ERROR "Fixture blocked executable: ${program}")
  endif()
  set(_call "")
  math(EXPR last "${ARGC} - 1")
  foreach(index RANGE 0 ${last})
    string(APPEND _call " [==[${ARGV${index}}]==]")
  endforeach()
  cmake_language(EVAL CODE "_execute_process(${_call})")
  foreach(key RESULT_VARIABLE OUTPUT_VARIABLE ERROR_VARIABLE)
    if(P_${key})
      set(${P_${key}} "${${P_${key}}}" PARENT_SCOPE)
    endif()
  endforeach()
endfunction()
function(try_compile)
  message(FATAL_ERROR "Fixture blocked compilation")
endfunction()
function(try_run)
  message(FATAL_ERROR "Fixture blocked compilation")
endfunction()
function(require_equal actual expected)
  if(NOT "${actual}" STREQUAL "${expected}")
    message(FATAL_ERROR "Expected [${expected}], got [${actual}]")
  endif()
endfunction()
'''


class ProcessProbeTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-process-probes-")
        self.work = Path(self.temporary.name).resolve()
        self.bin = self.work / "tools with spaces"
        self.bin.mkdir()
        self.packages = self.work / "modules"
        self.packages.mkdir()
        self.log = self.work / "calls.jsonl"
        self.env = os.environ.copy()
        for name in ("CC", "CXX", "FC", "PYTHONHOME", "PYTHONPATH", "SDKROOT",
                     "DEVELOPER_DIR", "CONDA_PREFIX", "VIRTUAL_ENV", "ROOTSYS"):
            self.env.pop(name, None)
        self.env.update(PATH=str(self.bin), PYTHONPATH=str(self.packages),
                        PYTHONNOUSERSITE="1", PYTHONDONTWRITEBYTECODE="1")
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake)
        self.python = self.tool("python3", '''
if any(Path(a).name == 'cbs_python_probe.py' for a in sys.argv[1:]):
    print(sys.argv[0]); print('3.13.9'); print(Path(sys.argv[0]).parent.parent)
    print(Path(sys.argv[0]).parent.parent / 'include')
    print(Path(sys.argv[0]).parent.parent / 'libpython.dylib')
else:
    os.execv(sys.executable, [sys.executable] + sys.argv[1:])
''')
        (self.work / "include").mkdir()
        (self.work / "include/Python.h").write_text("fixture")
        (self.work / "libpython.dylib").write_text("fixture")
        for module in ("yaml", "cython", "configobj", "pandas", "matplotlib",
                       "dynesty", "numpy", "emcee", "nautilus", "nessai", "pocomc",
                       "scipy", "ultranest", "packaging", "zeus", "paraprof", "mpi4py"):
            self.module(module)
        self.module("h5py", "class version:\n    hdf5_version = '1.14.6'\n")

    def tearDown(self):
        self.temporary.cleanup()

    def tool(self, name, body):
        path = self.bin / name
        path.write_text("#!" + sys.executable + "\n"
                        "from pathlib import Path\nimport sys, os, json, time\n"
                        f"with open({str(self.log)!r}, 'a') as log:\n"
                        "    log.write(json.dumps(sys.argv) + '\\n')\n" + body)
        path.chmod(0o755)
        return path

    def module(self, name, body=""):
        path = self.packages / (name + ".py")
        path.write_text(body)
        return path

    def calls(self, program=None):
        rows = [json.loads(line) for line in self.log.read_text().splitlines()] if self.log.exists() else []
        return [row for row in rows if program is None or row[0] == str(program)]

    def include(self, relative):
        return "include(" + quote(ROOT / relative) + ")\n"

    def run_case(self, body, fatal=None):
        script = self.work / "case.cmake"
        script.write_text("cmake_minimum_required(VERSION 3.24)\n"
                          + "set(FIXTURE_ROOT " + quote(self.work) + ")\n"
                          + "set(Python3_EXECUTABLE " + quote(self.python) + ")\n"
                          + GUARD + body)
        result = subprocess.run([self.cmake, "-P", str(script)], cwd=self.work,
                                env=self.env, capture_output=True, text=True, timeout=30)
        output = result.stdout + result.stderr
        if fatal:
            self.assertNotEqual(result.returncode, 0, output)
            self.assertIn(fatal, output)
        else:
            self.assertEqual(result.returncode, 0, output)
        self.assertNotIn("CMake Warning", output)
        self.assertFalse(list(self.work.rglob("CMakeCache.txt")))
        self.assertFalse(list(self.work.rglob("*.pyc")))
        return output

    def native_module_macro(self):
        text = (ROOT / "cmake/utilities.cmake").read_text()
        start = text.index("macro(gambit_find_python_module module)")
        end = text.index("endmacro()", start) + len("endmacro()")
        return self.include("cmake/PythonModules.cmake") + text[start:end] + "\n"

    def probe(self, tool, extra=""):
        return ("gambit_process_probe(COMMAND " + quote(tool) + " " + extra
                + " RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)\n")

    def status(self, module, found, hdf5="-", error="0"):
        return (f'gambit_python_module_status("${{Python3_EXECUTABLE}}" {module} found hdf5 error)\n'
                f'require_equal("${{found}}" "{found}")\n'
                f'require_equal("${{hdf5}}" "{hdf5}")\n'
                f'require_equal("${{error}}" "{error}")\n')

    def test_cached_raw_output_failure_and_argument_boundaries(self):
        tool = self.tool("report", "print(repr(sys.argv[1:])); print('stderr', file=sys.stderr); sys.exit(7)\n")
        body = self.include("cmake/ProcessProbe.cmake")
        body += self.probe(tool, quote("a;b") + " " + quote("two words"))
        body += 'set(first "${output}")\nrequire_equal("${result}" 7)\n'
        body += self.probe(tool, quote("a;b") + " " + quote("two words"))
        body += 'require_equal("${output}" "${first}")\n'
        body += self.probe(tool, "a b " + quote("two words"))
        self.run_case(body)
        self.assertEqual([row[1:] for row in self.calls(tool)], [["a;b", "two words"], ["a", "b", "two words"]])

    def test_environment_script_content_and_new_process_invalidate(self):
        tool = self.tool("report", "print(os.environ.get('PYENV_VERSION', 'default'))\n")
        data = self.work / "input.txt"
        data.write_text("same")
        probe = self.probe(tool, "INPUT_FILES " + quote(data))
        body = self.include("cmake/ProcessProbe.cmake") + probe + probe
        body += 'set(ENV{PYENV_VERSION} new)\n' + probe
        body += "file(WRITE " + quote(data) + " change)\n" + probe
        self.run_case(body)
        self.assertEqual(len(self.calls(tool)), 3)
        self.run_case(self.include("cmake/ProcessProbe.cmake") + probe)
        self.assertEqual(len(self.calls(tool)), 4)

    def test_input_hash_detects_same_size_same_timestamp_change(self):
        tool = self.tool("report", "print('ok')\n")
        data = self.work / "input.txt"
        data.write_text("aaaa")
        stamp = data.stat().st_mtime
        mutate = self.tool("mutate", f"p=Path({str(data)!r}); p.write_text('bbbb'); os.utime(p, ({stamp!r}, {stamp!r}))\n")
        probe = self.probe(tool, "INPUT_FILES " + quote(data))
        self.run_case(self.include("cmake/ProcessProbe.cmake") + probe
                      + "execute_process(COMMAND " + quote(mutate) + ")\n" + probe)
        self.assertEqual(len(self.calls(tool)), 2)

    def test_executable_symlink_target_and_missing_file_change(self):
        first = self.tool("one", "print('one')\n")
        second = self.tool("two", "print('two')\n")
        link = self.bin / "link"
        link.symlink_to(first)
        mutate = self.tool("retarget", f"p=Path({str(link)!r}); p.unlink(); p.symlink_to({str(second)!r})\n")
        self.run_case(self.include("cmake/ProcessProbe.cmake") + self.probe(link)
                      + "execute_process(COMMAND " + quote(mutate) + ")\n" + self.probe(link)
                      + 'require_equal("${output}" "two\n")\n')
        self.assertEqual(len(self.calls()), 3)

    def test_timeout_is_retained_within_process(self):
        tool = self.tool("slow", "print('started', flush=True); time.sleep(3)\n")
        probe = self.probe(tool, "TIMEOUT 1.0")
        self.run_case(self.include("cmake/ProcessProbe.cmake") + probe
                      + 'set(first "${result}")\n' + probe
                      + 'require_equal("${result}" "${first}")\n')
        self.assertEqual(len(self.calls(tool)), 1)

    def test_native_toolchain_reuses_versions_across_calls(self):
        c = self.tool("clang", "print('clang version 18.1.8')\n")
        cxx = self.tool("clang++", "print('clang version 18.1.8')\n")
        fc = self.tool("gfortran", "print('GNU compiler 14.2.0' if sys.argv[1:] == ['--version'] else '14.2.0')\n")
        body = self.include("cmake/presets/NativeCompilerDiscovery.cmake")
        body += "set(CMAKE_HOST_SYSTEM_NAME Darwin)\n"
        body += "set(CMAKE_C_COMPILER " + quote(c) + ")\nset(CMAKE_CXX_COMPILER " + quote(cxx) + ")\n"
        body += "set(CMAKE_Fortran_COMPILER " + quote(fc) + ")\n"
        body += '''foreach(provider gambit cbs repeated)
  native_find_toolchain(llvm found c cxx f root version reason)
  require_equal("${found}" TRUE)
  require_equal("${version}" 18.1.8)
endforeach()
'''
        self.run_case(body)
        self.assertEqual(len(self.calls(c)), 1)
        self.assertEqual(len(self.calls(cxx)), 1)
        self.assertEqual([row[1:] for row in self.calls(fc)], [["--version"], ["-dumpfullversion", "-dumpversion"]])

    def test_batch_and_single_consumers_share_raw_results(self):
        body = self.native_module_macro() + self.include("cmake/presets/CBSPythonDiscovery.cmake")
        body += 'gambit_probe_python_modules("${Python3_EXECUTABLE}" yaml cython pandas yaml)\n'
        body += self.status("yaml", "1") + self.status("cython", "1")
        body += 'gambit_find_python_module(yaml REQUIRED)\ncbs_python_missing_modules("${Python3_EXECUTABLE}" missing yaml pandas)\nrequire_equal("${missing}" "")\n'
        self.run_case(body)
        self.assertEqual(len(self.calls(self.python)), 1)
        self.assertEqual(self.calls(self.python)[0][3:], ["yaml", "cython", "pandas"])

    def test_native_core_and_selected_cbs_requirements_share_one_batch(self):
        main = (ROOT / "CMakeLists.txt").read_text()
        start = main.index("set(_gambit_python_modules yaml")
        end = main.index("unset(_gambit_python_modules)", start) + len("unset(_gambit_python_modules)")
        for selected, count in (("TRUE", 12), ("FALSE", 8)):
            with self.subTest(optional_backend=selected):
                self.log.write_text("")
                body = self.native_module_macro() + self.include("cmake/presets/CBSPythonDiscovery.cmake")
                body += 'set(CBS_PRESET_BUILD TRUE)\nset(CBS_WITH_RIVET_CONTUR ' + selected + ')\n'
                body += main[start:end] + '\ncbs_validate_python_for_cbs_preset()\n'
                body += 'foreach(module yaml os re datetime sys getopt shutil itertools)\n  gambit_find_python_module(${module} REQUIRED)\nendforeach()\n'
                self.run_case(body)
                self.assertEqual(len(self.calls(self.python)), 1)
                self.assertEqual(len(self.calls(self.python)[0][3:]), count)

    def test_loud_failed_and_system_exit_imports_do_not_hide_other_modules(self):
        self.module("loud", "import os\nprint('noise')\nos.write(2,b'noise')\n")
        self.module("broken", "raise RuntimeError('fixture')\n")
        self.module("exits", "raise SystemExit(0)\n")
        body = self.include("cmake/PythonModules.cmake")
        body += 'gambit_probe_python_modules("${Python3_EXECUTABLE}" loud broken exits yaml)\n'
        for name, found in (("loud", "1"), ("broken", "0"), ("exits", "0"), ("yaml", "1")):
            body += self.status(name, found)
        output = self.run_case(body)
        self.assertNotIn("noise", output)
        self.assertEqual(len(self.calls(self.python)), 1)

    def test_crashed_batch_preserves_completed_modules_and_isolates_remainder(self):
        self.module("crash", "import os\nos._exit(23)\n")
        body = self.include("cmake/PythonModules.cmake")
        body += 'gambit_probe_python_modules("${Python3_EXECUTABLE}" yaml crash pandas)\n'
        body += self.status("yaml", "1") + self.status("crash", "0") + self.status("pandas", "1")
        self.run_case(body)
        self.assertEqual([row[3:] for row in self.calls(self.python)], [["yaml", "crash", "pandas"], ["crash"], ["pandas"]])

    def test_python_environment_and_interpreter_changes_reprobe(self):
        alternative = self.work / "other modules"
        alternative.mkdir()
        (alternative / "fixtureonly.py").write_text("")
        second = self.tool("python-other", "os.execv(sys.executable, [sys.executable] + sys.argv[1:])\n")
        body = self.include("cmake/PythonModules.cmake") + self.status("fixtureonly", "0")
        body += "set(ENV{PYTHONPATH} " + quote(alternative) + ")\n" + self.status("fixtureonly", "1")
        body += "set(Python3_EXECUTABLE " + quote(second) + ")\n" + self.status("fixtureonly", "1")
        self.run_case(body)
        self.assertEqual(len(self.calls(self.python)), 2)
        self.assertEqual(len(self.calls(second)), 1)

    def test_import_search_includes_cwd_like_python_c(self):
        (self.work / "fixturecurrent.py").write_text("")
        self.run_case(self.include("cmake/PythonModules.cmake") + self.status("fixturecurrent", "1"))

    def test_failed_module_is_rechecked_next_cmake_process(self):
        body = self.include("cmake/PythonModules.cmake")
        self.run_case(body + self.status("fixtureonly", "0"))
        self.module("fixtureonly")
        self.run_case(body + self.status("fixtureonly", "1"))
        self.assertEqual(len(self.calls(self.python)), 2)

    def test_h5py_policy_is_applied_to_raw_import_without_another_process(self):
        body = self.native_module_macro()
        body += 'gambit_probe_python_modules("${Python3_EXECUTABLE}" h5py)\nset(HDF5_FOUND TRUE)\n'
        body += 'set(HDF5_VERSION 1.14.6)\ngambit_find_python_module(h5py)\nrequire_equal("${PY_h5py_FOUND}" TRUE)\n'
        body += 'set(HDF5_VERSION 2.0.0)\ngambit_find_python_module(h5py)\nrequire_equal("${PY_h5py_FOUND}" FALSE)\n'
        body += 'set(HDF5_VERSION 1.14.6)\ngambit_find_python_module(h5py)\nrequire_equal("${PY_h5py_FOUND}" TRUE)\n'
        self.run_case(body)
        self.assertEqual(len(self.calls(self.python)), 1)

    def test_h5py_corrupted_metadata_is_fatal_only_when_hdf5_is_selected(self):
        self.module("h5py", "class version:\n    hdf5_version = 'invalid'\n")
        body = self.native_module_macro() + 'gambit_find_python_module(h5py)\nrequire_equal("${PY_h5py_FOUND}" TRUE)\n'
        self.run_case(body + 'set(HDF5_FOUND TRUE)\ngambit_find_python_module(h5py)\n', fatal="h5py is corrupted")
        self.assertEqual(len(self.calls(self.python)), 1)

    def test_required_yaml_and_optional_backend_policy(self):
        (self.packages / "matplotlib.py").write_text("raise ImportError('fixture')\n")
        body = self.include("cmake/presets/CBSPythonDiscovery.cmake")
        body += 'set(CBS_PRESET_BUILD TRUE)\nset(CBS_WITH_RIVET_CONTUR TRUE)\n'
        body += 'gambit_probe_python_modules("${Python3_EXECUTABLE}" yaml cython configobj pandas matplotlib)\n'
        body += 'cbs_validate_python_for_cbs_preset()\nrequire_equal("${CBS_RIVET_CONTUR_PREREQUISITES_FOUND}" FALSE)\n'
        body += 'require_equal("${CBS_RIVET_CONTUR_PREREQUISITES_REASON}" "Python modules missing: matplotlib")\n'
        self.run_case(body)
        self.assertEqual(len(self.calls(self.python)), 1)
        self.module("yaml", "raise ImportError('fixture')\n")
        self.run_case(body, fatal="cannot import the required yaml module")

    def test_disabled_optional_backend_does_not_import_its_modules(self):
        body = self.include("cmake/presets/CBSPythonDiscovery.cmake")
        body += 'set(CBS_PRESET_BUILD TRUE)\nset(CBS_WITH_RIVET_CONTUR FALSE)\ncbs_validate_python_for_cbs_preset()\n'
        self.run_case(body)
        self.assertEqual(self.calls(self.python)[0][3:], ["yaml"])

    def test_scanner_batch_retains_package_aliases_and_h5py_policy(self):
        self.module("nautilus", "raise ImportError('fixture')\n")
        body = self.native_module_macro() + 'set(HDF5_FOUND TRUE)\nset(HDF5_VERSION 2.0.0)\n'
        body += self.include("cmake/python_scanners.cmake")
        body += '''if(NOT "nautilus|missing|nautilus-sampler" IN_LIST GAMBIT_PYTHON_SCANNER_STATUS)
  message(FATAL_ERROR "Scanner package alias lost")
endif()
if(NOT "emcee|missing|h5py" IN_LIST GAMBIT_PYTHON_SCANNER_STATUS)
  message(FATAL_ERROR "Scanner HDF5 policy lost")
endif()
'''
        self.run_case(body)
        self.assertEqual(len(self.calls(self.python)), 1)
        self.assertEqual(len(self.calls(self.python)[0][3:]), 13)

    def test_backend_group_batches_only_unchecked_modules(self):
        text = (ROOT / "cmake/externals.cmake").read_text()
        start = text.index("macro(check_python_modules")
        end = text.index("endmacro()", start) + len("endmacro()")
        body = self.native_module_macro() + text[start:end] + "\n"
        body += 'check_python_modules(example 1 "yaml,cython")\ncheck_python_modules(other 1 "cython,pandas")\n'
        self.run_case(body)
        self.assertEqual([row[3:] for row in self.calls(self.python)], [["yaml", "cython"], ["pandas"]])

    def test_helpers_included_in_function_keep_their_probe_source(self):
        body = 'function(load_helpers)\n' + self.include("cmake/presets/CBSPythonDiscovery.cmake")
        body += 'endfunction()\nload_helpers()\n'
        body += 'cbs_discover_python(found executable version root include library reason)\nrequire_equal("${found}" TRUE)\n'
        body += self.status("yaml", "1")
        self.run_case(body)
        self.assertEqual(len(self.calls(self.python)), 2)

    def test_light_and_strict_python_share_metadata_without_sharing_policy(self):
        (self.work / "include/Python.h").unlink()
        body = self.include("cmake/presets/PresetEnvironmentDiscovery.cmake")
        body += 'preset_probe_find_python(found executable version reason command)\nrequire_equal("${found}" TRUE)\n'
        body += 'cbs_discover_python(found executable version root include library reason)\nrequire_equal("${found}" FALSE)\n'
        self.run_case(body)
        self.assertEqual(len(self.calls(self.python)), 1)

    def test_bootstrap_batches_selected_provider_modules_and_versions(self):
        # Copy the real dispatcher/provider graph so all normal policies run.
        fixture = self.work / "source"
        shutil.copytree(ROOT / "cmake/presets", fixture / "cmake/presets")
        shutil.copy2(ROOT / "CMakePresets.json", fixture / "CMakePresets.json")
        for name in ("ProcessProbe.cmake", "PythonModules.cmake", "compiler_mins.cmake", "CXXStandard.cmake"):
            shutil.copy2(ROOT / "cmake" / name, fixture / "cmake" / name)
        shutil.copytree(ROOT / "cmake/scripts", fixture / "cmake/scripts")
        c = self.tool("clang", "print('clang version 18.1.8')\n")
        cxx = self.tool("clang++", "print('clang version 18.1.8')\n")
        fc = self.tool("gfortran", "print('GNU compiler 14.2.0' if sys.argv[1:] == ['--version'] else '14.2.0')\n")
        apple = self.tool("apple-clang", "print('Apple clang version 17.0.0')\n")
        apple_cxx = self.tool("apple-clang++", "print('Apple clang version 17.0.0')\n")
        self.tool("xcrun", f"print({str(apple)!r} if sys.argv[-1] == 'clang' else {str(apple_cxx)!r})\n")
        llvm = self.work / "llvm tree"
        (llvm / "bin").mkdir(parents=True)
        c = Path(shutil.move(c, llvm / "bin/clang"))
        cxx = Path(shutil.move(cxx, llvm / "bin/clang++"))
        self.tool("brew", f"print({str(llvm)!r}) if sys.argv[1:] == ['--prefix', 'llvm'] else sys.exit(1)\n")
        self.tool("pkg-config", "sys.exit(1)\n")
        self.tool("root-config", "sys.exit(1)\n")
        root = self.work / "root"
        (root / "bin").mkdir(parents=True)
        shutil.copy2(self.bin / "root-config", root / "bin/root-config")
        self.env.update(FC=str(fc), ROOTSYS=str(root))
        base = 'set(CMAKE_HOST_SYSTEM_NAME Darwin)\n'
        base += 'set(CMAKE_FIND_USE_CMAKE_SYSTEM_PATH FALSE)\nset(CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH TRUE)\n'
        dispatch = "include(" + quote(fixture / "cmake/presets/detect-presets.cmake") + ")\n"
        self.run_case(base + dispatch)
        metadata = [r for r in self.calls(self.python) if len(r) == 2]
        batches = [r for r in self.calls(self.python) if len(r) > 2]
        self.assertEqual(len(metadata), 1)
        self.assertEqual([r[3:] for r in batches], [["yaml", "cython", "configobj", "pandas", "matplotlib"]])
        self.assertEqual(len(self.calls(c)), 1)
        self.assertEqual(len(self.calls(cxx)), 1)
        self.assertEqual(len(self.calls(apple)), 1)
        self.assertEqual(len(self.calls(apple_cxx)), 1)
        self.assertEqual(len(self.calls(fc)), 2)
        self.assertEqual(len(self.calls(self.bin / "xcrun")), 2)
        self.assertEqual(len([r for r in self.calls(self.bin / "brew") if r[1:] == ["--prefix", "llvm"]]), 1)
        self.log.write_text("")
        self.run_case(base + 'set(BOOTSTRAP_SYSTEMS gambit)\n' + dispatch)
        batches = [r for r in self.calls(self.python) if len(r) > 2]
        self.assertEqual([r[3:] for r in batches], [["yaml"]])
        self.log.write_text("")
        self.run_case(base + 'set(BOOTSTRAP_LIST_ONLY TRUE)\n' + dispatch)
        self.assertEqual(self.calls(), [])
        self.run_case(base + 'set(BOOTSTRAP_SYSTEMS unknown)\n' + dispatch, fatal="Unknown system")
        self.assertEqual(self.calls(), [])
        self.assertFalse((fixture / "build").exists())


if __name__ == "__main__":
    unittest.main(verbosity=2)
