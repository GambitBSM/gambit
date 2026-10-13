#!/usr/bin/env python3
"""Code-generation regressions without configuring or compiling GAMBIT/CBS."""

import hashlib
import json
import os
from pathlib import Path
import pickle
import re
import shutil
import subprocess
import sys
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

    def test_cold_harvest_graph_preserves_inventory_and_noops_then_tracks_real_changes(self):
        # Run the real discovery, registration macro and CMake-list updater in
        # a LANGUAGES NONE project. The fake harvesters write only temporary
        # outputs; no GAMBIT configure, compiler, backend or network is involved.
        root = (self.work / "source with spaces").resolve()
        root.mkdir()
        build = root / "build"

        def put(relative, text="// fixture input\n"):
            path = root / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
            return path

        put("Utils/scripts/harvesting_tools.py", (ROOT / "Utils/scripts/harvesting_tools.py").read_text())
        put("scratch/build_time/keep", "")
        put("config/resolution_type_equivalency_classes.yaml", "{}\n")
        for module, directory, name in (
                ("Models", "models", "model.hpp"), ("Models", "model_types", "type.hh"),
                ("Backends", "frontends", "backend.hpp"),
                ("Printers", "printers", "printer.h"), ("ColliderBit", "models", "collider.hh")):
            put(module + "/include/gambit/" + module + "/" + directory + "/" + name)
            put(module + "/src/z.cpp")
            put(module + "/src/a.cpp")
        put("ColliderBit/include/gambit/ColliderBit/ColliderBit_rollcall.hpp")
        text = (ROOT / "CMakeLists.txt").read_text()
        discovery = text[text.index("# Identify the different harvester scripts"):
                         text.index("# Add backends and scanners. Done before")]
        utilities = (ROOT / "cmake/utilities.cmake").read_text()
        macro = re.search(r"macro\(add_gambit_custom\b.*?\nendmacro\(\)", utilities, re.S).group()
        registrations = []
        for label, kind, completion in (
                ("module", "MODULE", "modules_harvested"),
                ("backend", "BACKEND", "backends_harvested"),
                ("model", "MODEL", "models_harvested"),
                ("printer", "PRINTER", "printers_harvested"),
                ("collider", "COLLIDER", "colliders_harvested")):
            script = put("fake_" + label + ".py",
                         "from pathlib import Path\n"
                         "root = Path.cwd()\n"
                         "with (root / 'calls.log').open('a') as stream: stream.write(" + repr(label + "\n") + ")\n"
                         "for name in (root / 'build/" + kind + "-outputs.txt').read_text().split(';'):\n"
                         "    path = Path(name)\n"
                         "    path.parent.mkdir(parents=True, exist_ok=True)\n"
                         "    if not path.exists(): path.write_text('// stable generated content\\n')\n")
            registrations.extend([
                "set(" + kind + "_HARVESTER " + bracket(script) + ")",
                "file(WRITE \"${CMAKE_BINARY_DIR}/" + kind + "-outputs.txt\" \"${" + kind + "_HARVESTER_OUTPUTS}\")",
                "add_gambit_custom(" + label + "_harvest " + completion + " " + kind +
                "_HARVESTER " + kind + "_HARVESTER_FILES)",
            ])
        functors = put("fake_functors.py",
                       "from pathlib import Path\n"
                       "with Path('calls.log').open('a') as stream: stream.write('functors\\n')\n"
                       "path = Path('ColliderBit/examples/functors_for_CBS.cpp')\n"
                       "path.parent.mkdir(parents=True, exist_ok=True)\n"
                       "if not path.exists(): path.write_text('// stable functors\\n')\n")
        put("CMakeLists.txt", "\n".join([
            "cmake_minimum_required(VERSION 3.16.3)", "project(codegen_fixture LANGUAGES NONE)",
            "include(" + bracket(ROOT / "cmake/CodeGeneration.cmake") + ")", macro,
            "set(Python3_EXECUTABLE " + bracket(sys.executable) + ")", "set(GAMBIT_BITS ColliderBit)",
            discovery, *registrations,
            "add_dependencies(module_harvest backend_harvest model_harvest collider_harvest)",
            "add_dependencies(printer_harvest module_harvest)",
            "execute_process(COMMAND " + bracket(sys.executable) + " -B " +
            bracket(ROOT / "cmake/scripts/update_cmakelists.py") +
            " WORKING_DIRECTORY \"${PROJECT_SOURCE_DIR}\" RESULT_VARIABLE result)",
            "if(NOT result EQUAL 0)\n message(FATAL_ERROR \"Updater failed\")\nendif()",
            "add_custom_command(OUTPUT \"${CMAKE_BINARY_DIR}/functors_for_CBS.stamp\"",
            " BYPRODUCTS \"${PROJECT_SOURCE_DIR}/ColliderBit/examples/functors_for_CBS.cpp\"",
            " COMMAND " + bracket(sys.executable) + " -B " + bracket(functors),
            " COMMAND \"${CMAKE_COMMAND}\" -E touch \"${CMAKE_BINARY_DIR}/functors_for_CBS.stamp\"",
            " WORKING_DIRECTORY \"${PROJECT_SOURCE_DIR}\"",
            " DEPENDS \"${CMAKE_BINARY_DIR}/modules_harvested\" VERBATIM)",
            "add_custom_target(CBS DEPENDS \"${CMAKE_BINARY_DIR}/functors_for_CBS.stamp\")",
            "add_dependencies(CBS printer_harvest)", "",
        ]))
        environment = {**os.environ, "PYTHONDONTWRITEBYTECODE": "1"}
        environment.pop("PYTHONHOME", None)
        configure = [self.cmake, "-S", str(root), "-B", str(build), "-G", "Unix Makefiles"]
        compile_fixture = [self.cmake, "--build", str(build), "--target", "CBS"]

        def invoke(command):
            result = subprocess.run(command, cwd=root, env=environment, stdin=subprocess.DEVNULL,
                                    capture_output=True, text=True, timeout=20)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            return result.stdout + result.stderr

        def calls():
            path = root / "calls.log"
            return path.read_text().splitlines() if path.exists() else []

        def records():
            paths = list(build.glob("*harvest_options.stamp")) + list(build.glob("*_harvested"))
            paths += [build / "functors_for_CBS.stamp"]
            paths += [root / module / "CMakeLists.txt" for module in ("Backends", "Models", "Printers", "ColliderBit")]
            for manifest in build.glob("*-outputs.txt"):
                paths += [Path(name) for name in manifest.read_text().split(";")]
            paths += [root / "ColliderBit/examples/functors_for_CBS.cpp"]
            return {path: signature(path) for path in paths}

        def separate_input_times():
            # GNU Make 3.81 on macOS compares whole seconds. Use distinct
            # explicit timestamps rather than sleeps or subsecond assumptions.
            for path in root.rglob("*"):
                if path.is_file() and build not in path.parents:
                    os.utime(path, ns=(100_000_000_000, 100_000_000_000))
            for path in build.glob("*harvest_options.stamp"):
                os.utime(path, ns=(100_000_000_000, 100_000_000_000))
            for path in [*build.glob("*_harvested"), build / "functors_for_CBS.stamp"]:
                os.utime(path, ns=(200_000_000_000, 200_000_000_000))

        invoke(configure)
        model_options = (build / "model_harvest_options.stamp").read_text()
        self.assertIn(str(root / "Models/include/gambit/Models/model_types/type.hh"), model_options)
        for kind, relative in (
                ("printer", "Printers/include/gambit/Printers/printers/printer.h"),
                ("collider", "ColliderBit/include/gambit/ColliderBit/models/collider.hh")):
            self.assertIn(str(root / relative), (build / (kind + "_harvest_options.stamp")).read_text())
        self.assertIn("include/gambit/ColliderBit/ColliderBit_rollcall.hpp",
                      (root / "ColliderBit/CMakeLists.txt").read_text())
        for module in ("Models", "Backends", "Printers", "ColliderBit"):
            inventory = (root / module / "CMakeLists.txt").read_text()
            self.assertLess(inventory.index("src/a.cpp"), inventory.index("src/z.cpp"))
        invoke(compile_fixture)
        self.assertEqual(set(calls()), {"module", "backend", "model", "printer", "collider", "functors"})
        separate_input_times()
        before, executed = records(), calls()
        invoke(compile_fixture)
        self.assertEqual(calls(), executed, "direct build repeated a generator")
        invoke(configure)
        invoke(compile_fixture)
        self.assertEqual(calls(), executed, "identical configure repeated a generator")
        self.assertEqual(records(), before, "identical configure changed a durable generation record")

        # Addition/removal changes the real discovered input membership, even
        # when existing input files are older than the successful stamps.
        new_header = put("Models/include/gambit/Models/model_types/new.h")
        invoke(configure)
        invoke(compile_fixture)
        self.assertIn("model", calls()[len(executed):])
        separate_input_times()
        executed = calls()
        new_header.unlink()
        invoke(configure)
        invoke(compile_fixture)
        self.assertIn("model", calls()[len(executed):])

        # Editing an existing model-type input must invalidate the model
        # generator without relying on a CMake source-list content change.
        separate_input_times()
        executed = calls()
        model_type = root / "Models/include/gambit/Models/model_types/type.hh"
        model_type.write_text("// changed existing model type\n")
        invoke(compile_fixture)
        self.assertIn("model", calls()[len(executed):])

        # An explicit configure repairs a missing BYPRODUCT through its owner,
        # while keeping unrelated backend/collider/printer stamps unchanged.
        separate_input_times()
        before, executed = records(), calls()
        output = root / "Models/include/gambit/Models/model_rollcall.hpp"
        output.unlink()
        invoke(configure)
        invoke(compile_fixture)
        self.assertTrue(output.is_file())
        self.assertEqual(set(calls()[len(executed):]), {"model", "module", "functors"})
        after = records()
        for name in ("backends_harvested", "colliders_harvested", "printers_harvested"):
            self.assertEqual(before[build / name], after[build / name])
        separate_input_times()
        before, executed = records(), calls()
        invoke(configure)
        invoke(compile_fixture)
        self.assertEqual(calls(), executed)
        self.assertEqual(records(), before)

    def test_scanner_inventory_is_stable_from_cold_generation_and_header_repair(self):
        import sys

        directories = [
            "ScannerBit/src/scanners", "ScannerBit/src/objectives",
            "ScannerBit/include/gambit/ScannerBit/scanners",
            "ScannerBit/include/gambit/ScannerBit/objectives",
            "ScannerBit/include/gambit/ScannerBit/priors",
            "ScannerBit/lib", "Utils/scripts", "scratch/build_time", "config", "build",
        ]
        for directory in directories:
            (self.work / directory).mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / "Utils/scripts/harvesting_tools.py", self.work / "Utils/scripts")
        for name in ["scanner_locations.yaml.default", "objective_locations.yaml.default"]:
            (self.work / "config" / name).write_text("{}\n")
        (self.work / "ScannerBit/src/ordinary.cpp").write_text("// fixture\n")
        (self.work / "ScannerBit/include/gambit/ScannerBit/ordinary.hpp").write_text("// fixture\n")
        (self.work / "ScannerBit/include/gambit/ScannerBit/priors/simple.hpp").write_text("// fixture prior\n")
        # No plugin declarations need YAML parsing. Keep this fixture independent
        # of PyYAML while executing the real harvester and shared update helper.
        (self.work / "yaml.py").write_text(
            "def full_load(*args, **kwargs):\n"
            "    raise AssertionError('fixture must not parse plugin YAML')\n"
        )
        environment = {**os.environ, "PYTHONPATH": str(self.work),
                       "PYTHONNOUSERSITE": "1", "PYTHONDONTWRITEBYTECODE": "1"}
        environment.pop("PYTHONHOME", None)

        def generate():
            result = subprocess.run(
                [sys.executable, "-B", str(ROOT / "ScannerBit/scripts/scanner+_harvester.py"),
                 str(self.work / "build")],
                cwd=self.work, env=environment, stdin=subprocess.DEVNULL,
                capture_output=True, text=True, timeout=15,
            )
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertFalse(list((self.work / "build").glob("*.candidate")))

        cmake = self.work / "ScannerBit/CMakeLists.txt"
        header = self.work / "ScannerBit/include/gambit/ScannerBit/priors_rollcall.hpp"
        outputs = [cmake, header, self.work / "ScannerBit/lib/plugin_libraries.list",
                   self.work / "scratch/build_time/scanbit_reqd_entries.yaml",
                   self.work / "scratch/build_time/scanbit_flags.yaml",
                   self.work / "build/linkedout.cmake"]
        self.assertFalse(header.exists())
        generate()
        self.assertEqual(cmake.read_text().count(
            "include/gambit/ScannerBit/priors_rollcall.hpp"), 1)
        self.assertIn('#include "gambit/ScannerBit/priors/simple.hpp"', header.read_text())
        for path in outputs:
            os.utime(path, ns=(1_000_000_000, 1_000_000_000))
        before = {path: signature(path) for path in outputs}
        for _ in range(2):
            generate()
            self.assertEqual({path: signature(path) for path in outputs}, before)

        # Repair a deleted generated header without rewriting the CMake inventory
        # or unrelated outputs; the next identical run must preserve all outputs.
        header.unlink()
        generate()
        self.assertTrue(header.exists())
        self.assertIn('#include "gambit/ScannerBit/priors/simple.hpp"', header.read_text())
        self.assertEqual({path: signature(path) for path in outputs if path != header},
                         {path: value for path, value in before.items() if path != header})
        repaired = {path: signature(path) for path in outputs}
        generate()
        self.assertEqual({path: signature(path) for path in outputs}, repaired)

    def test_real_scanner_plugin_metadata_is_stable_across_hash_seeds_and_updates(self):
        root = (self.work / "scanner-metadata").resolve()
        build = root / "build"

        def put(relative, text="// fixture\n"):
            path = root / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
            return path

        for directory in ("ScannerBit/src/objectives", "ScannerBit/include/gambit/ScannerBit/objectives",
                          "ScannerBit/include/gambit/ScannerBit/scanners",
                          "ScannerBit/include/gambit/ScannerBit/priors", "ScannerBit/lib",
                          "scratch/build_time", "build", "fixtures/python", "fixtures/pybind", "fixtures/common"):
            (root / directory).mkdir(parents=True, exist_ok=True)
        for plugin in ("great", "minuit2_6.23.01", "python"):
            shutil.copytree(ROOT / "ScannerBit/src/scanners" / plugin,
                            root / "ScannerBit/src/scanners" / plugin)
        put("ScannerBit/src/ordinary.cpp")
        put("ScannerBit/include/gambit/ScannerBit/ordinary.hpp")
        put("Utils/scripts/harvesting_tools.py", (ROOT / "Utils/scripts/harvesting_tools.py").read_text())
        put("ScannerBit/src/scanners/explicit/explicit.cpp",
            'scanner_plugin(explicit, version(1, 0, 0)) {\n'
            'reqd_libraries("beta", "alpha", "beta");\nreqd_headers("first.hh");\n}\n')
        beta = put("fixtures/z/libbeta.so")
        alpha = put("fixtures/a/libalpha.so")
        put("fixtures/z/first.hh")
        for name in ("Minuit2", "Minuit2Math"):
            put("fixtures/lib/lib" + name + ".so", "fake library: never linked or executed\n")
        locations = {"explicit": {"any_version": [
            {"lib": "./fixtures/z/libbeta.so ./fixtures/a/libalpha.so ./fixtures/z/libbeta.so"},
            {"headers": "./fixtures/z ./fixtures/a"}]}}
        location_file = put("config/scanner_locations.yaml.default", json.dumps(locations))
        put("config/objective_locations.yaml.default", "{}\n")
        # JSON is a YAML subset. This adapter loads exactly our controlled
        # location data while keeping the policy suite standard-library-only;
        # the real harvester still parses the real multi-dependency plugins.
        put("yaml.py", "import json\ndef full_load(stream):\n    return json.load(stream)\n")
        put("CMakeLists.txt", "\n".join([
            "cmake_minimum_required(VERSION 3.16.3)", "project(scanner_metadata LANGUAGES NONE)",
            "include(" + bracket(ROOT / "cmake/CodeGeneration.cmake") + ")",
            "function(add_gambit_library name)\n add_custom_target(${name})\nendfunction()",
            "function(add_executable name)\n add_custom_target(${name})\nendfunction()",
            "function(target_include_directories)\nendfunction()",
            "function(target_link_libraries)\nendfunction()", "add_custom_target(yaml-cpp)",
            "set(CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH FALSE)",
            "set(CMAKE_FIND_USE_CMAKE_SYSTEM_PATH FALSE)",
            "set(CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH FALSE)",
            'set(CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/fixtures/lib")',
            'set(CMAKE_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/fixtures/common")',
            "set(ROOT_FOUND FALSE)", "set(Python3_FOUND TRUE)",
            'set(Python3_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/fixtures/python")',
            "set(pybind11_FOUND TRUE)", 'set(pybind11_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/fixtures/pybind")',
            "set(PLUG_VERBOSE FALSE)", "add_subdirectory(ScannerBit)", "",
        ]))
        configure = [self.cmake, "-S", str(root), "-B", str(build), "-G", "Unix Makefiles",
                     "-DCMAKE_SYSTEM_NAME=Linux", "-DCMAKE_MAKE_PROGRAM=" + shutil.which("make")]

        def generate(seed):
            environment = {**os.environ, "PYTHONPATH": str(root), "PYTHONHASHSEED": str(seed),
                           "PYTHONNOUSERSITE": "1", "PYTHONDONTWRITEBYTECODE": "1"}
            environment.pop("PYTHONHOME", None)
            for command in ([sys.executable, "-B", str(ROOT / "ScannerBit/scripts/scanner+_harvester.py"), str(build)],
                            configure):
                result = subprocess.run(command, cwd=root, env=environment, stdin=subprocess.DEVNULL,
                                        capture_output=True, text=True, timeout=20)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertFalse(list(build.glob("*.candidate")))
            self.assertFalse(list((root / "scratch/build_time").glob("*.candidate")))

        outputs = [root / relative for relative in (
            "ScannerBit/CMakeLists.txt", "ScannerBit/include/gambit/ScannerBit/priors_rollcall.hpp",
            "ScannerBit/lib/plugin_libraries.list", "scratch/build_time/scanbit_reqd_entries.yaml",
            "scratch/build_time/scanbit_flags.yaml", "scratch/build_time/scanbit_excluded_libs.yaml",
            "scratch/build_time/scanbit_linked_libs.yaml", "build/linkedout.cmake")]
        excluded, linked = outputs[5:7]
        generate(1)
        self.assertIn('file missing: "TGreatModel.h"', excluded.read_text())
        self.assertIn('file missing: "Math/Functor.h"', excluded.read_text())
        self.assertIn("Minuit2:", linked.read_text())
        self.assertIn('"Python3":', linked.read_text())
        link_block = re.search(r"set \(scanner_plugin_lib_full_paths_explicit(.*?)\n\)",
                               outputs[0].read_text(), re.S).group(1)
        self.assertEqual([line.strip() for line in link_block.splitlines() if line.strip()],
                         [str(beta), str(alpha), str(beta)], "explicit link order/duplicates must survive")
        for path in outputs:
            os.utime(path, ns=(1_000_000_000, 1_000_000_000))
        before = {path: signature(path) for path in outputs}
        for seed in (2, 42, 123, 1):
            generate(seed)
            self.assertEqual({path: signature(path) for path in outputs}, before)

        # Newly available real header inputs change diagnostic content; these
        # metadata outputs must remain responsive rather than being frozen.
        put("fixtures/common/Minuit2/Minuit2Minimizer.h")
        put("fixtures/common/Math/Functor.h")
        generate(2)
        self.assertNotIn("libscanner_minuit2_6.23.01.so:", excluded.read_text())
        self.assertNotEqual(signature(excluded), before[excluded])
        self.assertIn('"Math/Functor.h":', linked.read_text())
        changed = {path: signature(path) for path in outputs}
        generate(42)
        self.assertEqual({path: signature(path) for path in outputs}, changed)

        # User-specified library sequences remain ordered, including repeated
        # libraries, and changing that sequence updates both CMake and metadata.
        locations["explicit"]["any_version"][0]["lib"] = (
            "./fixtures/a/libalpha.so ./fixtures/z/libbeta.so ./fixtures/a/libalpha.so")
        location_file.write_text(json.dumps(locations))
        generate(123)
        link_block = re.search(r"set \(scanner_plugin_lib_full_paths_explicit(.*?)\n\)",
                               outputs[0].read_text(), re.S).group(1)
        self.assertEqual([line.strip() for line in link_block.splitlines() if line.strip()],
                         [str(alpha), str(beta), str(alpha)])
        self.assertNotEqual(signature(linked)[1], changed[linked][1])
        changed = {path: signature(path) for path in outputs}
        generate(1)
        self.assertEqual({path: signature(path) for path in outputs}, changed)


if __name__ == "__main__":
    unittest.main(verbosity=2)
