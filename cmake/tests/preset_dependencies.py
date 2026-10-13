#!/usr/bin/env python3
"""Check actual preset switches with a temporary, compiler-free CMake fixture.

Only a project with LANGUAGES NONE is configured. No GAMBIT configure, build,
compiler, network, or real dependency probe is allowed; ROOT/Python are fake.
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
PRESETS = {p['name']: p for p in json.loads((ROOT / 'CMakePresets.json').read_text())['configurePresets']}


def preset_values(name):
    preset = PRESETS[name]
    values = {}
    parents = preset.get('inherits', [])
    for parent in [parents] if isinstance(parents, str) else parents:
        values.update(preset_values(parent))
    for key, value in preset.get('cacheVariables', {}).items():
        values[key] = value.get('value') if isinstance(value, dict) else value
    return values


def bracket(value):
    return '[==[' + str(value) + ']==]'


FIXTURE = r'''
cmake_minimum_required(VERSION 3.16.3)
project(preset_dependencies LANGUAGES NONE)
set(_fixture_inputs "${FIXTURE_ROOT};${FIXTURE_PYTHON};${FIXTURE_ROOT_CONFIG}")
function(try_compile)
  message(FATAL_ERROR "Compilation is forbidden in this fixture")
endfunction()
function(try_run)
  message(FATAL_ERROR "Compilation is forbidden in this fixture")
endfunction()
function(execute_process)
  cmake_parse_arguments(PARSE_ARGV 0 P
    "OUTPUT_STRIP_TRAILING_WHITESPACE;ERROR_STRIP_TRAILING_WHITESPACE;ERROR_QUIET"
    "RESULT_VARIABLE;OUTPUT_VARIABLE;ERROR_VARIABLE;TIMEOUT" "COMMAND")
  list(GET P_COMMAND 0 program)
  get_filename_component(program "${program}" REALPATH)
  string(FIND "${program}" "${FIXTURE_ROOT}/" position)
  if(NOT position EQUAL 0)
    message(FATAL_ERROR "Fixture blocked real dependency probe: ${program}")
  endif()
  set(call "")
  math(EXPR last "${ARGC}-1")
  foreach(index RANGE 0 ${last})
    string(APPEND call " [==[${ARGV${index}}]==]")
  endforeach()
  cmake_language(EVAL CODE "_execute_process(${call})")
  foreach(key RESULT_VARIABLE OUTPUT_VARIABLE ERROR_VARIABLE)
    if(P_${key})
      set(${P_${key}} "${${P_${key}}}" PARENT_SCOPE)
    endif()
  endforeach()
endfunction()
function(find_program name)
  if(name STREQUAL "_cbs_root_config")
    if(EXISTS "${FIXTURE_ROOT_CONFIG}")
      set(${name} "${FIXTURE_ROOT_CONFIG}" CACHE FILEPATH "fixture root-config" FORCE)
    else()
      set(${name} "${name}-NOTFOUND" CACHE FILEPATH "fixture root-config" FORCE)
    endif()
    set(${name} "${${name}}" PARENT_SCOPE)
  elseif(name STREQUAL "_cbs_python_command")
    set(${name} "${FIXTURE_PYTHON}" PARENT_SCOPE)
  else()
    message(FATAL_ERROR "Fixture blocked unrelated program search: ${name}")
  endif()
endfunction()
include(@MODULE@)
gambit_initialise_preset_dependencies()
set(CBS_PRESET_BUILD FALSE)
if(CBS_BUILD_PRESET)
  set(CBS_PRESET_BUILD TRUE)
endif()
gambit_preset_discover_python()
gambit_preset_discover_root()
# Match native option() calls after discovery: they must leave AUTO in cache.
option(WITH_ROOT "Compile with ROOT enabled" OFF)
option(WITH_RESTFRAMES "Compile with RestFrames enabled" OFF)
option(WITH_ONNXRUNTIME "Compile with ONNX Runtime enabled" OFF)
option(CUTFLOW "Enable cut-flow output" OFF)
file(WRITE "${CMAKE_BINARY_DIR}/result.txt" "")
foreach(key Bits itch CBS_BUILD_PRESET GAMBIT_BUILD_PRESET CMAKE_BUILD_TYPE
    WITH_MPI WITH_HDF5 WITH_SQLite3 WITH_RESTFRAMES WITH_ONNXRUNTIME CUTFLOW
    CBS_WITH_RIVET_CONTUR WITH_ROOT GAMBIT_AUTO_DETECT_PYTHON
    GAMBIT_AUTO_DETECT_ROOT Python3_EXECUTABLE GAMBIT_ROOT_PREFIX
    GAMBIT_RESOLVED_ROOT GAMBIT_ROOT_SKIP_REASON)
  file(APPEND "${CMAKE_BINARY_DIR}/result.txt" "${key}=${${key}}\n")
endforeach()
get_property(request CACHE WITH_ROOT PROPERTY VALUE)
file(APPEND "${CMAKE_BINARY_DIR}/result.txt" "ROOT_REQUEST=${request}\n")
'''


class PresetDependencyTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix='gambit-preset-dependencies-')
        self.addCleanup(self.temporary.cleanup)
        self.work = Path(self.temporary.name).resolve()
        self.source = self.work / 'fixture'
        self.source.mkdir()
        self.build = self.work / 'build'
        self.cmake = shutil.which('cmake')
        self.make = shutil.which('make')
        self.assertIsNotNone(self.cmake)
        self.assertIsNotNone(self.make)
        self.log = self.work / 'probes.jsonl'
        self.packages = self.work / 'modules'
        self.packages.mkdir()
        (self.packages / 'yaml.py').write_text('')
        self.python = self.tool(self.work / 'python with spaces/bin/python3', '''
if any(Path(a).name == 'cbs_python_probe.py' for a in sys.argv[1:]):
    print(sys.argv[0]); print('3.13.9'); print(Path(sys.argv[0]).parent.parent)
    print(Path(sys.argv[0]).parent.parent / 'include')
    print(Path(sys.argv[0]).parent.parent / 'libpython.dylib')
else:
    os.execv(sys.executable, [sys.executable] + sys.argv[1:])
''')
        self.root = self.work / 'ROOT with spaces'
        self.root_config = self.root_tool(self.root)
        self.env = os.environ.copy()
        for key in ('ROOTSYS', 'PYTHONHOME', 'PYTHONPATH', 'CC', 'CXX', 'FC'):
            self.env.pop(key, None)
        self.env.update(PYTHONPATH=str(self.packages), PYTHONNOUSERSITE='1',
                        PYTHONDONTWRITEBYTECODE='1', FIXTURE_LOG=str(self.log))
        module = bracket(ROOT / 'cmake/presets/PresetDependencies.cmake')
        (self.source / 'CMakeLists.txt').write_text(FIXTURE.replace('@MODULE@', module))

    def tool(self, path, body):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text('#!' + sys.executable + '\n'
                        'from pathlib import Path\nimport json, os, sys\n'
                        'with open(os.environ["FIXTURE_LOG"], "a") as stream:\n'
                        '    stream.write(json.dumps(sys.argv) + "\\n")\n' + body)
        path.chmod(0o755)
        return path

    def root_tool(self, prefix, standard='23'):
        return self.tool(prefix / 'bin/root-config',
            "answers={'--prefix':" + repr(str(prefix)) + ", '--version':'6.38.00', '--cxxstd':" + repr(standard) + "}\n"
            "print(answers.get(sys.argv[1], ''))\n")

    def configure(self, preset='gambit-llvm', options=None, root_config=None, environment=None, success=True):
        values = preset_values(preset) if preset else {'CBS_BUILD_PRESET': '', 'GAMBIT_BUILD_PRESET': '',
                                                      'GAMBIT_PRESET_TOOLCHAIN': '', 'GAMBIT_PRESET_DEPENDENCIES': ''}
        values.update(options or {})
        values.update(FIXTURE_ROOT=self.work, FIXTURE_PYTHON=self.python,
                      FIXTURE_ROOT_CONFIG=root_config or self.root_config)
        args = [self.cmake, '-S', str(self.source), '-B', str(self.build),
                '-G', 'Unix Makefiles', '-DCMAKE_MAKE_PROGRAM=' + self.make]
        args += ['-D' + key + '=' + str(value) for key, value in values.items()]
        env = dict(self.env)
        env.update(environment or {})
        result = subprocess.run(args, text=True, capture_output=True, env=env)
        output = result.stdout + result.stderr
        self.assertEqual(result.returncode == 0, success, output)
        self.assertNotIn('Manually-specified variables were not used', output)
        if not success:
            return output
        records = dict(line.split('=', 1) for line in (self.build / 'result.txt').read_text().splitlines())
        return records, output

    def calls(self, name):
        return [row for row in map(json.loads, self.log.read_text().splitlines()) if Path(row[0]).name == name] if self.log.exists() else []

    def cache(self):
        text = (self.build / 'CMakeCache.txt').read_text()
        return dict(re.findall(r'^([^/#][^:=]*):[^=]*=(.*)$', text, re.MULTILINE))

    def test_cbs_to_gambit_keeps_dependencies_and_custom_configuration(self):
        first, _ = self.configure('cbs-llvm', {'CMAKE_BUILD_TYPE': 'Debug', 'WITH_MPI': 'ON'})
        second, _ = self.configure('gambit-llvm')
        for key in ('WITH_RESTFRAMES', 'WITH_ONNXRUNTIME', 'CUTFLOW', 'WITH_HDF5',
                    'WITH_SQLite3', 'WITH_MPI', 'CBS_WITH_RIVET_CONTUR',
                    'GAMBIT_AUTO_DETECT_ROOT', 'GAMBIT_AUTO_DETECT_PYTHON'):
            self.assertEqual(first[key], 'ON', key)
            self.assertEqual(second[key], 'ON', key)
        self.assertEqual(second['CMAKE_BUILD_TYPE'], 'Debug')
        self.assertEqual(second['Bits'], '')
        self.assertEqual(second['CBS_BUILD_PRESET'], '')
        self.assertEqual(second['GAMBIT_BUILD_PRESET'], 'gambit-llvm')
        self.assertEqual(second['Python3_EXECUTABLE'], str(self.python))
        self.assertEqual(second['GAMBIT_ROOT_PREFIX'], str(self.root))
        self.assertEqual(second['WITH_ROOT'], 'ON')
        self.assertEqual(second['ROOT_REQUEST'], 'AUTO')

    def test_gambit_to_cbs_keeps_explicit_disabled_features(self):
        choices = {key: 'OFF' for key in ('WITH_ROOT', 'WITH_RESTFRAMES', 'WITH_ONNXRUNTIME',
                                          'CUTFLOW', 'WITH_HDF5', 'WITH_SQLite3', 'CBS_WITH_RIVET_CONTUR')}
        self.configure('gambit-llvm', choices)
        values, _ = self.configure('cbs-llvm')
        for key in choices:
            self.assertEqual(values[key], 'OFF', key)
        self.assertEqual(values['Bits'], 'ColliderBit')
        self.assertEqual(values['GAMBIT_BUILD_PRESET'], '')
        self.assertFalse(self.calls('root-config'))

    def test_fresh_gambit_defaults_and_repeated_configuration_are_stable(self):
        first, _ = self.configure()
        second, _ = self.configure()
        self.assertEqual(first, second)
        self.assertEqual(first['CMAKE_BUILD_TYPE'], 'Release')
        for key in ('WITH_RESTFRAMES', 'WITH_ONNXRUNTIME', 'CUTFLOW', 'WITH_MPI', 'CBS_WITH_RIVET_CONTUR'):
            self.assertEqual(first[key], 'OFF', key)
        self.assertEqual(first['WITH_ROOT'], 'ON')
        self.assertEqual(first['ROOT_REQUEST'], 'AUTO')
        # A cached Python stays selected instead of being rediscovered on PATH.
        self.assertEqual(len(self.calls('python3')), 2)  # metadata + PyYAML

    def test_auto_root_recovers_when_installation_becomes_available(self):
        self.root_config.unlink()
        values, _ = self.configure('cbs-llvm')
        self.assertEqual(values['WITH_ROOT'], 'OFF')
        self.assertEqual(values['ROOT_REQUEST'], 'AUTO')
        self.root_tool(self.root)
        values, _ = self.configure('gambit-llvm')
        self.assertEqual(values['WITH_ROOT'], 'ON')
        self.assertEqual(values['ROOT_REQUEST'], 'AUTO')

    def test_root_selection_survives_path_changes_and_honours_rootsys(self):
        self.configure('cbs-llvm')
        other = self.work / 'another ROOT'
        tool = self.root_tool(other, '20')
        values, _ = self.configure(root_config=tool)
        self.assertEqual(values['GAMBIT_RESOLVED_ROOT'], str(self.root))
        values, _ = self.configure(root_config=tool, environment={'ROOTSYS': str(other)})
        self.assertEqual(values['GAMBIT_RESOLVED_ROOT'], str(other))

    def test_auto_root_rechecks_the_selected_installation(self):
        self.configure('cbs-llvm')
        self.root_tool(self.root, '14')
        values, output = self.configure()
        self.assertEqual(values['ROOT_REQUEST'], 'AUTO')
        self.assertEqual(values['WITH_ROOT'], 'OFF')
        self.assertIn('C++14', output)
        self.root_tool(self.root, '23')
        values, _ = self.configure()
        self.assertEqual(values['WITH_ROOT'], 'ON')

    def test_discovery_switches_are_shared_and_can_be_reenabled(self):
        self.configure('cbs-llvm', {'GAMBIT_AUTO_DETECT_ROOT': 'OFF', 'GAMBIT_AUTO_DETECT_PYTHON': 'OFF'})
        values, _ = self.configure()
        self.assertEqual(values['WITH_ROOT'], 'OFF')
        self.assertEqual(values['ROOT_REQUEST'], 'AUTO')
        self.assertFalse(self.calls('root-config'))
        self.assertFalse(self.calls('python3'))
        values, _ = self.configure(options={'GAMBIT_AUTO_DETECT_ROOT': 'ON', 'GAMBIT_AUTO_DETECT_PYTHON': 'ON'})
        self.assertEqual(values['WITH_ROOT'], 'ON')
        self.assertEqual(values['Python3_EXECUTABLE'], str(self.python))

    def test_explicit_root_on_keeps_native_findroot_with_discovery_disabled(self):
        values, _ = self.configure(options={'WITH_ROOT': 'ON', 'GAMBIT_AUTO_DETECT_ROOT': 'OFF'})
        self.assertEqual(values['WITH_ROOT'], 'ON')
        self.assertEqual(values['ROOT_REQUEST'], 'ON')
        self.assertFalse(self.calls('root-config'))

    def test_legacy_aliases_seed_shared_options_then_leave_the_cache(self):
        values, _ = self.configure('cbs-llvm', {'CBS_AUTO_DETECT_ROOT': 'OFF', 'CBS_AUTO_DETECT_PYTHON': 'OFF'})
        self.assertEqual(values['GAMBIT_AUTO_DETECT_ROOT'], 'OFF')
        self.assertEqual(values['GAMBIT_AUTO_DETECT_PYTHON'], 'OFF')
        self.assertNotIn('CBS_AUTO_DETECT_ROOT', self.cache())
        self.assertNotIn('CBS_AUTO_DETECT_PYTHON', self.cache())
        values, _ = self.configure(options={'GAMBIT_AUTO_DETECT_ROOT': 'ON', 'GAMBIT_AUTO_DETECT_PYTHON': 'ON'})
        self.assertEqual(values['WITH_ROOT'], 'ON')

    def test_common_names_take_precedence_over_legacy_aliases(self):
        values, _ = self.configure(options={'GAMBIT_AUTO_DETECT_ROOT': 'ON', 'CBS_AUTO_DETECT_ROOT': 'OFF'})
        self.assertEqual(values['WITH_ROOT'], 'ON')
        self.assertEqual(values['GAMBIT_AUTO_DETECT_ROOT'], 'ON')

    def test_legacy_root_off_is_preserved_until_user_selects_auto(self):
        values, _ = self.configure(options={'WITH_ROOT': 'OFF'})
        self.assertEqual(values['WITH_ROOT'], 'OFF')
        values, _ = self.configure(options={'WITH_ROOT': 'AUTO'})
        self.assertEqual(values['WITH_ROOT'], 'ON')
        self.assertEqual(values['ROOT_REQUEST'], 'AUTO')

    def test_explicit_python_selection_is_preserved_across_profiles(self):
        selected = self.tool(self.work / 'selected/bin/python3', 'raise RuntimeError("Must not probe an explicit interpreter")\n')
        self.configure('cbs-llvm', {'Python3_EXECUTABLE': selected})
        values, _ = self.configure()
        self.assertEqual(values['Python3_EXECUTABLE'], str(selected))
        self.assertFalse(self.calls('python3'))

    def test_ordinary_cmake_keeps_native_defaults(self):
        values, _ = self.configure(preset=None)
        self.assertEqual(values['WITH_ROOT'], 'OFF')
        self.assertEqual(values['ROOT_REQUEST'], 'OFF')
        self.assertNotIn('GAMBIT_AUTO_DETECT_ROOT', self.cache())
        self.assertNotIn('GAMBIT_AUTO_DETECT_PYTHON', self.cache())
        self.assertFalse(self.calls('root-config'))
        self.assertFalse(self.calls('python3'))

    def test_local_preset_inheriting_base_keeps_defaults_without_native_toolchain(self):
        values, _ = self.configure(options={'GAMBIT_PRESET_TOOLCHAIN': '', 'GAMBIT_BUILD_PRESET': ''})
        self.assertEqual(values['CMAKE_BUILD_TYPE'], 'Release')
        self.assertEqual(values['ROOT_REQUEST'], 'AUTO')
        self.assertEqual(values['WITH_ROOT'], 'ON')
        self.assertEqual(values['Python3_EXECUTABLE'], str(self.python))

    def test_invalid_root_mode_is_rejected(self):
        output = self.configure(options={'WITH_ROOT': 'AUTOO'}, success=False)
        self.assertIn("Invalid WITH_ROOT='AUTOO'", output)


if __name__ == '__main__':
    unittest.main(verbosity=2)
