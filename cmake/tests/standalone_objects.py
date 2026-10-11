#!/usr/bin/env python3
"""Check standalone target registration without a project configure or compiler."""

from pathlib import Path
import re
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


# Store target properties in CMake's script-safe GLOBAL properties. Native
# target creation is replaced with capture; the real GAMBIT functions execute.
CAPTURE_TARGETS = r'''
function(mock_put target property value)
  _set_property(GLOBAL PROPERTY "mock_${target}_${property}" "${value}")
endfunction()
function(mock_append target property value)
  get_property(previous GLOBAL PROPERTY "mock_${target}_${property}")
  if(previous)
    set(value "${previous};${value}")
  endif()
  mock_put("${target}" "${property}" "${value}")
endfunction()
function(get_target_property output target property)
  get_property(exists GLOBAL PROPERTY "mock_${target}_${property}" SET)
  if(exists)
    get_property(value GLOBAL PROPERTY "mock_${target}_${property}")
  else()
    set(value "${output}-NOTFOUND")
  endif()
  set(${output} "${value}" PARENT_SCOPE)
endfunction()
function(set_property scope)
  if(NOT scope STREQUAL "TARGET" OR NOT ARGV2 STREQUAL "PROPERTY")
    message(FATAL_ERROR "Unexpected captured property command: ${ARGV}")
  endif()
  mock_put("${ARGV1}" "${ARGV3}" "${ARGV4}")
endfunction()
function(set_target_properties target)
  set(index 2)
  while(index LESS ARGC)
    math(EXPR next "${index}+1")
    mock_put("${target}" "${ARGV${index}}" "${ARGV${next}}")
    math(EXPR index "${index}+2")
  endwhile()
endfunction()
function(add_library target kind)
  mock_put("${target}" TYPE "${kind}")
  mock_put("${target}" SOURCES "${ARGN}")
  _set_property(GLOBAL APPEND PROPERTY mock_targets "${target}")
endfunction()
function(add_executable target)
  mock_put("${target}" TYPE EXECUTABLE)
  mock_put("${target}" SOURCES "${ARGN}")
  # A few non-default values exercise the compile-setting copy.
  mock_put("${target}" CXX_STANDARD 17)
  mock_put("${target}" CXX_STANDARD_REQUIRED ON)
  mock_put("${target}" CXX_EXTENSIONS OFF)
  mock_put("${target}" CXX_VISIBILITY_PRESET hidden)
  mock_put("${target}" VISIBILITY_INLINES_HIDDEN TRUE)
  mock_put("${target}" COMPILE_OPTIONS "-Wall;-Wextra")
  mock_put("${target}" COMPILE_FLAGS -Wconversion)
  mock_put("${target}" CXX_COMPILER_LAUNCHER ccache)
  mock_put("${target}" COMPILE_DEFINITIONS CHECK_CUTFLOW)
  mock_put("${target}" COMPILE_FEATURES cxx_std_17)
  mock_put("${target}" OSX_ARCHITECTURES arm64)
  _set_property(GLOBAL APPEND PROPERTY mock_targets "${target}")
endfunction()
function(target_include_directories target scope)
  mock_append("${target}" INCLUDE_DIRECTORIES "${ARGN}")
endfunction()
function(target_link_libraries target scope)
  mock_append("${target}" LINK_LIBRARIES "${ARGN}")
endfunction()
function(target_compile_definitions target scope)
  mock_append("${target}" COMPILE_DEFINITIONS "${ARGN}")
endfunction()
function(add_dependencies target)
  mock_append("${target}" DEPENDENCIES "${ARGN}")
endfunction()
function(add_custom_command)
endfunction()
function(add_custom_target)
endfunction()
'''


class StandaloneObjectTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="gambit-standalone-")
        self.work = Path(self.temporary.name)
        self.cmake = shutil.which("cmake")
        self.assertIsNotNone(self.cmake, "cmake must be on PATH")
        for module in ["ColliderBit", "SpecBit"]:
            (self.work / module / "examples").mkdir(parents=True)

    def tearDown(self):
        self.temporary.cleanup()

    def run_case(self, name="CBS", modules="ColliderBit", sources=True,
                 settings="", excluded=False, before=""):
        utilities = (ROOT / "cmake/utilities.cmake").read_text()
        functions = []
        for function in ["normalise_gambit_link_libraries", "add_gambit_executable",
                         "gambit_configure_standalone_objects", "add_standalone"]:
            functions.append(re.search(
                rf"function\({function}\b.*?endfunction\(\)", utilities, re.DOTALL
            ).group(0))
        captured = self.work / "properties.txt"
        program_sources = ["solo.cpp", "solo_cli.cpp", "solo_input.cpp", "solo_batch.cpp", "solo_output.cpp"]
        arguments = [name, "MODULES", *modules.split(), "LIBRARIES", "plugin",
                     "DEPENDENCIES", "hepmc", "pybind11", "nulike_1.0.9"]
        if sources:
            arguments += ["SOURCES", *["ColliderBit/examples/" + s for s in program_sources]]
        body = "\n".join([
            "cmake_minimum_required(VERSION 3.16.3)",
            "include(CMakeParseArguments)",
            "include(" + bracket(ROOT / "cmake/CodeGeneration.cmake") + ")",
            CAPTURE_TARGETS,
            *functions,
            "set(PROJECT_SOURCE_DIR " + bracket(self.work) + ")",
            "set(CMAKE_BINARY_DIR " + bracket(self.work) + ")",
            "set(Python3_EXECUTABLE /python3)",
            "set(STANDALONE_FACILITATOR /standalone_facilitator.py)",
            "set(HARVEST_TOOLS /harvesting_tools.py)",
            "set(GAMBIT_BITS ColliderBit SpecBit)",
            "set(GAMBIT_INCDIRS /project/include)",
            'set(GAMBIT_ALL_COMMON_OBJECTS "$<TARGET_OBJECTS:Logs>" "$<TARGET_OBJECTS:Utils>")',
            "set(CMAKE_SYSTEM_NAME Linux)",
            "set(CMAKE_BUILD_TYPE Release)",
            "set(CMAKE_CONFIGURATION_TYPES Debug Release)",
            "set(HAVE_PYBIND11 TRUE)",
            "set(pybind11_FOUND TRUE)",
            "set(Python3_LIBRARIES /libpython)",
            "set(OpenMP_omp_LIBRARY /libomp)",
            "set(MPI_CXX_FOUND TRUE)",
            "set(MPI_CXX_LIBRARIES /libmpi)",
            "set(MPI_CXX_LINK_FLAGS -mpi-link)",
            "set(EXCLUDE_HEPMC " + ("TRUE" if excluded else "FALSE") + ")",
            before,
            "add_standalone(" + " ".join(bracket(a) for a in arguments) + ")",
            settings,
            "file(WRITE " + bracket(captured) + ' "")',
            "get_property(targets GLOBAL PROPERTY mock_targets)",
            "foreach(target IN LISTS targets)",
            "  foreach(property TYPE SOURCES EXCLUDE_FROM_ALL ENABLE_EXPORTS INCLUDE_DIRECTORIES",
            "                   COMPILE_OPTIONS COMPILE_FLAGS CXX_COMPILER_LAUNCHER COMPILE_DEFINITIONS COMPILE_FEATURES LINK_LIBRARIES",
            "                   CXX_STANDARD CXX_STANDARD_REQUIRED CXX_EXTENSIONS CXX_VISIBILITY_PRESET",
            "                   VISIBILITY_INLINES_HIDDEN OSX_ARCHITECTURES DEPENDENCIES",
            "                   INTERPROCEDURAL_OPTIMIZATION_DEBUG)",
            '    get_property(value GLOBAL PROPERTY "mock_${target}_${property}")',
            "    file(APPEND " + bracket(captured) + ' "${target}\t${property}\t${value}\n")',
            "  endforeach()",
            "endforeach()",
        ])
        script = self.work / "targets.cmake"
        script.write_text(body)
        result = subprocess.run([self.cmake, "-P", str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        properties = {}
        for line in captured.read_text().splitlines():
            target, property, value = line.split("\t")
            properties.setdefault(target, {})[property] = value
        return properties

    def test_program_objects_have_only_header_preparation_dependencies(self):
        for modules in ["ColliderBit", "ColliderBit SpecBit"]:
            with self.subTest(modules=modules):
                targets = self.run_case(modules=modules)
                objects = targets["CBS_objects"]
                executable = targets["CBS"]
                self.assertEqual(objects["TYPE"], "OBJECT")
                self.assertEqual(objects["EXCLUDE_FROM_ALL"], "1")
                self.assertEqual(len(objects["SOURCES"].split(";")), 5)
                self.assertIn("solo.cpp", objects["SOURCES"])
                self.assertNotIn("functors_for_CBS.cpp", objects["SOURCES"])
                self.assertNotIn("TARGET_OBJECTS", objects["SOURCES"])
                self.assertEqual(set(objects["DEPENDENCIES"].split(";")),
                                 {"contrib", "model_harvest", "backend_harvest", "module_harvest", "printer_harvest"})
                self.assertIn("$<TARGET_OBJECTS:CBS_objects>", executable["SOURCES"])
                self.assertIn("functors_for_CBS.cpp", executable["SOURCES"])
                self.assertIn("$<TARGET_OBJECTS:ColliderBit>", executable["SOURCES"])
                self.assertNotIn("/solo.cpp", executable["SOURCES"])
                self.assertIn("nulike_1.0.9", executable["DEPENDENCIES"])
                self.assertIn("CBS_functors", executable["DEPENDENCIES"])

    def test_program_objects_keep_compile_settings_and_imported_library_usage(self):
        targets = self.run_case()
        for property in ["INCLUDE_DIRECTORIES", "COMPILE_OPTIONS", "COMPILE_FLAGS", "CXX_COMPILER_LAUNCHER", "COMPILE_FEATURES", "LINK_LIBRARIES",
                         "CXX_STANDARD", "CXX_STANDARD_REQUIRED", "CXX_EXTENSIONS", "CXX_VISIBILITY_PRESET",
                         "VISIBILITY_INLINES_HIDDEN", "OSX_ARCHITECTURES"]:
            self.assertEqual(targets["CBS_objects"][property], targets["CBS"][property], property)
        self.assertIn("yaml-cpp", targets["CBS_objects"]["LINK_LIBRARIES"])
        self.assertIn("/libomp", targets["CBS_objects"]["LINK_LIBRARIES"])
        self.assertIn("/libmpi", targets["CBS_objects"]["LINK_LIBRARIES"])
        self.assertIn("/libpython", targets["CBS_objects"]["LINK_LIBRARIES"])
        self.assertEqual(set(targets["CBS_objects"]["COMPILE_DEFINITIONS"].split(";")),
                         {"CHECK_CUTFLOW", "CBS_EXPORTS"})

    def test_openmp_libraries_keep_runtime_and_avoid_imported_compile_options(self):
        targets = self.run_case(before='set(OpenMP_CXX_LIBRARIES /selected/libomp /selected/libpthread)')
        for name in ("CBS", "CBS_objects"):
            links = targets[name]["LINK_LIBRARIES"].split(";")
            self.assertIn("/selected/libomp", links)
            self.assertIn("/selected/libpthread", links)
            self.assertNotIn("OpenMP::OpenMP_CXX", links)
            self.assertNotIn("/libomp", links)

    def test_export_macros_and_configuration_specific_settings(self):
        targets = self.run_case(name="3bithit")
        self.assertIn("_3bithit_EXPORTS", targets["3bithit_objects"]["COMPILE_DEFINITIONS"])
        for symbol in ["CUSTOM_EXPORT", ""]:
            with self.subTest(symbol=symbol):
                settings = ('set_target_properties(CBS PROPERTIES DEFINE_SYMBOL ' + bracket(symbol)
                            + ' INTERPROCEDURAL_OPTIMIZATION_DEBUG TRUE)\n'
                            + 'gambit_configure_standalone_objects(CBS_objects CBS)')
                targets = self.run_case(settings=settings)
                definitions = set(targets["CBS_objects"]["COMPILE_DEFINITIONS"].split(";"))
                self.assertEqual(definitions, {"CHECK_CUTFLOW", symbol} if symbol else {"CHECK_CUTFLOW"})
                self.assertEqual(targets["CBS_objects"]["INTERPROCEDURAL_OPTIMIZATION_DEBUG"], "TRUE")

    def test_excluded_standalone_does_not_create_program_objects(self):
        self.assertEqual(self.run_case(excluded=True), {})

    def test_functor_only_standalone_does_not_create_empty_object_library(self):
        targets = self.run_case(sources=False)
        self.assertNotIn("CBS_objects", targets)
        self.assertIn("functors_for_CBS.cpp", targets["CBS"]["SOURCES"])


if __name__ == "__main__":
    unittest.main(verbosity=2)
