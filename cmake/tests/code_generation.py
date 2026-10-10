#!/usr/bin/env python3
"""Code-generation regressions without configuring or compiling GAMBIT/CBS."""

import hashlib
import os
from pathlib import Path
import pickle
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]


def signature(path):
    return path.stat().st_mtime_ns, hashlib.sha256(path.read_bytes()).hexdigest()


def bracket(value):
    """Pass literal strings to CMake without expanding dollars or backslashes."""
    equals = ""
    while "]" + equals + "]" in str(value):
        equals += "="
    return "[" + equals + "[" + str(value) + "]" + equals + "]"


class CodeGenerationTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-codegen-")
        self.work = Path(self.temporary.name)
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake, "cmake must be on PATH")

    def tearDown(self):
        self.temporary.cleanup()

    def run_cmake(self, body):
        script = self.work / "test.cmake"
        script.write_text(
            "cmake_minimum_required(VERSION 3.16.3)\n"
            + "include(" + bracket(ROOT / "cmake/CodeGeneration.cmake") + ")\n"
            + body
        )
        result = subprocess.run(
            [self.cmake, "-P", str(script)], capture_output=True, text=True
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def write_options(self, stamp, arguments):
        self.run_cmake(
            "gambit_write_codegen_options("
            + " ".join(bracket(arg) for arg in [stamp, *arguments])
            + ")\n"
        )

    def test_unchanged_options_preserve_timestamp(self):
        stamp = self.work / "options with spaces.stamp"
        command = ["COMMAND", "/python path/python3", "harvester.py", "-x", "A,B"]
        self.write_options(stamp, command)
        # Give the existing file a distinct timestamp; don't rely on clock resolution.
        os.utime(stamp, ns=(1_000_000_000, 1_000_000_000))
        before = signature(stamp)
        self.write_options(stamp, command)
        self.assertEqual(signature(stamp), before)
        self.assertFalse(Path(str(stamp) + ".candidate").exists())

    def test_options_and_input_membership_invalidate(self):
        stamp = self.work / "options.stamp"
        cases = [
            ["COMMAND", "python3", "harvester.py", "--bits=ColliderBit", "INPUTS", "a", "b"],
            ["COMMAND", "other python3", "harvester.py", "--bits=ColliderBit", "INPUTS", "a", "b"],
            ["COMMAND", "other python3", "harvester.py", "--bits=DarkBit", "INPUTS", "a", "b"],
            ["COMMAND", "other python3", "harvester.py", "--bits=DarkBit", "INPUTS", "a"],
            ["COMMAND", "other python3", "harvester.py", "--bits=DarkBit", "INPUTS", "a", "old new file"],
            # Argument boundaries and literal CMake metacharacters are preserved.
            ["COMMAND", "a b", "c", "${literal}", "C:\\path"],
            ["COMMAND", "a", "b c", "${literal}", "C:\\path"],
        ]
        previous = None
        for arguments in cases:
            with self.subTest(arguments=arguments):
                if stamp.exists():
                    os.utime(stamp, ns=(1_000_000_000, 1_000_000_000))
                self.write_options(stamp, arguments)
                self.assertNotEqual(stamp.read_bytes(), previous)
                self.assertNotEqual(stamp.stat().st_mtime_ns, 1_000_000_000)
                previous = stamp.read_bytes()

    def test_missing_output_invalidates_only_its_generator(self):
        stamp = self.work / "completed.stamp"
        other_stamp = self.work / "other.stamp"
        output = self.work / "generated.hpp"
        for path in [stamp, other_stamp, output]:
            path.write_text("existing\n")
        before = signature(stamp)
        call = "gambit_check_codegen_outputs(" + bracket(stamp) + " " + bracket(output) + ")\n"
        self.run_cmake(call)
        self.assertEqual(signature(stamp), before)
        output.unlink()
        self.run_cmake(call)
        self.assertFalse(stamp.exists())
        self.assertTrue(other_stamp.exists())

    def test_generator_registration_uses_real_interpreter_and_completion_stamp(self):
        # Execute the real registration functions in script mode with target
        # creation captured instead of configuring a project or probing a compiler.
        utilities = (ROOT / "cmake/utilities.cmake").read_text()

        def definition(kind, name):
            return re.search(
                rf"{kind}\({name}\b.*?end{kind}\(\)", utilities, re.DOTALL
            ).group(0)

        (self.work / "ColliderBit/examples").mkdir(parents=True)
        captured = self.work / "commands.txt"
        dependencies = self.work / "dependencies.txt"
        python = "/correct interpreter/python3"
        harvester = self.work / "backend harvester.py"
        body = "\n".join([
            'include(CMakeParseArguments)',
            'function(add_custom_command)',
            '  file(APPEND ' + bracket(captured) + ' "${ARGV}\\n")',
            'endfunction()',
            'function(add_custom_target)',
            'endfunction()',
            'function(add_dependencies)',
            '  file(APPEND ' + bracket(dependencies) + ' "${ARGV}\\n")',
            'endfunction()',
            'function(add_gambit_executable)',
            'endfunction()',
            definition("macro", "add_gambit_custom"),
            definition("function", "add_standalone"),
            'set(PROJECT_SOURCE_DIR ' + bracket(self.work) + ')',
            'set(CMAKE_BINARY_DIR ' + bracket(self.work) + ')',
            'set(Python3_EXECUTABLE ' + bracket(python) + ')',
            'set(PYTHON_EXECUTABLE /wrong/python)',
            'set(HARVESTER ' + bracket(harvester) + ')',
            'set(HARVESTER_EXTRA_ARGS --bits=ColliderBit --force-backends=Pythia)',
            'set(HARVESTER_OUTPUTS ' + bracket(self.work / "generated.hpp") + ')',
            'set(DEPS ' + bracket(self.work / "input.hpp") + ')',
            'add_gambit_custom(backend_harvest backends_harvested HARVESTER DEPS A,B)',
            'set(GAMBIT_BITS ColliderBit)',
            'set(STANDALONE_FACILITATOR ' + bracket(ROOT / "Elements/scripts/standalone_facilitator.py") + ')',
            'add_standalone(CBS MODULES ColliderBit)',
        ])
        self.run_cmake(body)
        commands = captured.read_text()
        self.assertIn("COMMAND;" + python + ";" + str(harvester)
                      + ";-x;__not_a_real_name__,A,B;--bits=ColliderBit;--force-backends=Pythia", commands)
        self.assertNotIn("/wrong/python", commands)
        self.assertIn("OUTPUT;" + str(self.work / "functors_for_CBS.stamp")
                      + ";BYPRODUCTS;" + str(self.work / "ColliderBit/examples/functors_for_CBS.cpp"), commands)
        self.assertNotIn("touch;" + str(self.work / "ColliderBit/examples/functors_for_CBS.cpp"), commands)
        self.assertIn("CBS_functors;module_harvest", dependencies.read_text())
        self.assertIn("CBS;CBS_functors", dependencies.read_text())
        options = (self.work / "backend_harvest_options.stamp").read_text()
        self.assertIn("--bits=ColliderBit", options)
        self.assertIn("--force-backends=Pythia", options)
        self.assertIn(python, options)

    def test_input_discovery_tracks_shared_headers_without_self_dependencies(self):
        cmake_lists = (ROOT / "CMakeLists.txt").read_text()
        discovery = cmake_lists[
            cmake_lists.index("# Identify the different harvester scripts"):
            cmake_lists.index("# Add backends and scanners. Done before")
        ]
        inputs = [
            "ColliderBit/include/gambit/ColliderBit/ColliderBit_rollcall.hpp",
            "Backends/include/gambit/Backends/default_bossed_versions.hpp",
            "Backends/include/gambit/Backends/frontends/shared_includes/shared.hpp",
            "Backends/include/gambit/Backends/backend_types/Pythia/loaded_types.hpp",
            "Models/include/gambit/Models/model_types/result.h",
            "Elements/include/gambit/Elements/types_rollcall.hpp",
        ]
        generated = [
            "Elements/include/gambit/Elements/module_functor_types.hpp",
            "Backends/include/gambit/Backends/backend_functor_types.hpp",
            "Backends/include/gambit/Backends/backend_rollcall.hpp",
        ]
        for name in inputs + generated:
            path = self.work / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text("// test header\n")
        captured = self.work / "inputs.txt"
        self.run_cmake("\n".join([
            'set(PROJECT_SOURCE_DIR ' + bracket(self.work) + ')',
            'set(CMAKE_BINARY_DIR ' + bracket(self.work / "build") + ')',
            'set(GAMBIT_BITS ColliderBit)',
            discovery,
            '''
foreach(harvester MODULE BACKEND MODEL PRINTER COLLIDER)
  set(self_outputs ${${harvester}_HARVESTER_OUTPUTS})
  foreach(input IN LISTS ${harvester}_HARVESTER_FILES)
    if(input IN_LIST self_outputs)
      message(FATAL_ERROR "Self dependency: ${harvester}: ${input}")
    endif()
  endforeach()
endforeach()
''',
            'file(WRITE ' + bracket(captured) + ' "${MODULE_HARVESTER_FILES}\\n${BACKEND_HARVESTER_FILES}\\n")',
        ]))
        module_inputs, backend_inputs = captured.read_text().splitlines()
        module_inputs = module_inputs.split(";")
        backend_inputs = backend_inputs.split(";")
        for name in inputs:
            self.assertIn(str(self.work / name), module_inputs)
            self.assertIn(str(self.work / name), backend_inputs)
        self.assertNotIn(str(self.work / generated[0]), module_inputs)
        self.assertNotIn(str(self.work / generated[1]), module_inputs)
        self.assertNotIn(str(self.work / generated[2]), backend_inputs)
        # Cross-generator dependencies remain; only self-dependencies are excluded.
        self.assertIn(str(self.work / generated[2]), module_inputs)

    def test_functors_are_stable_across_hash_seeds_and_update_for_new_types(self):
        import sys

        scratch = self.work / "scratch/build_time"
        scratch.mkdir(parents=True)
        helpers = self.work / "Utils/scripts"
        helpers.mkdir(parents=True)
        shutil.copy2(ROOT / "Utils/scripts/harvesting_tools.py", helpers)
        output_dir = self.work / "ColliderBit/examples"
        output_dir.mkdir(parents=True)
        output = output_dir / "functors_for_CBS.cpp"
        types = {
            "non_module": {"double", "ModelParameters", "std::vector<double>"},
            "ColliderBit": {"float", "std::vector<float>", "MyResult"},
        }

        def generate(seed):
            with (scratch / "harvested_types.pickle").open("wb") as handle:
                pickle.dump(types, handle)
            result = subprocess.run(
                [sys.executable, str(ROOT / "Elements/scripts/standalone_facilitator.py"),
                 "CBS", "-m", "__not_a_real_name__,ColliderBit"],
                cwd=self.work, env={**os.environ, "PYTHONHASHSEED": str(seed)},
                capture_output=True, text=True,
            )
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

        generate(1)
        os.utime(output, ns=(1_000_000_000, 1_000_000_000))
        before = signature(output)
        for seed in [2, 42, 123]:
            generate(seed)
            self.assertEqual(signature(output), before)
        types["ColliderBit"].add("NewResult")
        generate(4)
        after = signature(output)
        self.assertNotEqual(after, before)
        self.assertIn("template class module_functor<NewResult>;", output.read_text())
        generate(5)
        self.assertEqual(signature(output), after)


if __name__ == "__main__":
    unittest.main(verbosity=2)
