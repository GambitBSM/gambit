#!/usr/bin/env python3
"""Merge regressions using CMake script fixtures, without configuring a project."""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def bracket(value):
    return '[==[' + str(value) + ']==]'


class MergeCompatibilityTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix='gambit-merge-compatibility-')
        self.work = Path(self.temporary.name)
        self.cmake = shutil.which('cmake')
        self.assertIsNotNone(self.cmake)

    def tearDown(self):
        self.temporary.cleanup()

    def run_script(self, body, success=True):
        script = self.work / 'fixture.cmake'
        script.write_text('cmake_minimum_required(VERSION 3.16.3)\n' + body)
        result = subprocess.run([self.cmake, '-P', str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode == 0, success, result.stdout + result.stderr)
        return result

    def function(self, name):
        source = (ROOT / 'cmake/utilities.cmake').read_text()
        return re.search(rf'function\({name}\b.*?endfunction\(\)', source, re.DOTALL).group(0)

    def trim_fixture(self, commands):
        self.run_script(self.function('_gambit_resolve_trim_default') + r'''
set(ALL_GAMBIT_BITS ColliderBit DarkBit ScannerBit)
function(expect value mode)
  if(NOT GAMBIT_TRIM_BACKEND_INTERFACES STREQUAL value)
    message(FATAL_ERROR "Expected trim ${value}, got ${GAMBIT_TRIM_BACKEND_INTERFACES}")
  endif()
  if(mode STREQUAL "explicit" AND DEFINED GAMBIT_TRIM_AUTOMATIC_VALUE)
    message(FATAL_ERROR "Explicit choice must remain explicit")
  elseif(mode STREQUAL "automatic" AND NOT GAMBIT_TRIM_AUTOMATIC_VALUE STREQUAL value)
    message(FATAL_ERROR "Missing automatic marker")
  endif()
endfunction()
''' + commands)

    def test_fresh_explicit_trim_choices_are_preserved(self):
        for value, bits in [('OFF', 'ColliderBit ScannerBit'),
                            ('ON', 'ColliderBit DarkBit ScannerBit')]:
            with self.subTest(value=value):
                self.trim_fixture(f'''
set(GAMBIT_BITS {bits})
set(GAMBIT_TRIM_BACKEND_INTERFACES {value} CACHE BOOL "explicit" FORCE)
_gambit_resolve_trim_default()
expect({value} explicit)
set(GAMBIT_BITS DarkBit)
_gambit_resolve_trim_default()
expect({value} explicit)
''')

    def test_automatic_trim_tracks_module_switches(self):
        self.trim_fixture('''
set(GAMBIT_BITS ColliderBit DarkBit ScannerBit)
_gambit_resolve_trim_default()
expect(OFF automatic)
set(GAMBIT_BITS ColliderBit ScannerBit)
_gambit_resolve_trim_default()
expect(ON automatic)
set(GAMBIT_BITS ColliderBit DarkBit ScannerBit)
_gambit_resolve_trim_default()
expect(OFF automatic)
''')

    def test_override_of_automatic_trim_stays_explicit(self):
        self.trim_fixture('''
set(GAMBIT_BITS ColliderBit)
_gambit_resolve_trim_default()
expect(ON automatic)
set(GAMBIT_TRIM_BACKEND_INTERFACES OFF CACHE BOOL "override" FORCE)
_gambit_resolve_trim_default()
expect(OFF explicit)
set(GAMBIT_BITS ColliderBit DarkBit ScannerBit)
_gambit_resolve_trim_default()
expect(OFF explicit)
set(GAMBIT_BITS ColliderBit)
_gambit_resolve_trim_default()
expect(OFF explicit)
''')

    def test_link_order_repetitions_and_configuration_pairs_are_preserved(self):
        bad = self.work / 'library.so'
        bad.write_text('not a directory')
        good = self.work / 'library directory'
        good.mkdir()
        items = ['optimized', 'A', 'debug', 'Ad', 'optimized', 'B', 'debug', 'Bd',
                 'general', 'C', 'A', 'B', 'A', '-Wl,--start-group', 'A', 'B',
                 '-Wl,--end-group', '-L' + str(good), '-L' + str(good)]
        inputs = items[:3] + ['-L', '-L' + str(bad)] + items[3:]
        self.run_script(self.function('normalise_gambit_link_libraries') + '\n' +
                        'normalise_gambit_link_libraries(actual ' +
                        ' '.join(bracket(item) for item in inputs) + ')\n' +
                        'set(expected ' + bracket(';'.join(items)) + ')\n' + r'''
if(NOT "${actual}" STREQUAL "${expected}")
  message(FATAL_ERROR "Link sequence changed: ${actual}")
endif()
''')

    def yoda_fixture(self, extra=''):
        source = (ROOT / 'cmake/contrib.cmake').read_text()
        block = source[source.index('  set(_yoda_h5cc_environment "")'):
                       source.index('  ExternalProject_Add(${name}', source.index('  set(_yoda_h5cc_environment "")'))]
        # The script uses only commands available at the legacy entry point.
        self.assertNotIn('file(CHMOD', re.sub(r'#.*', '', block))
        fake = self.work / 'h5cc'
        fake.write_text('#!/bin/sh\nif [ "$1" = "-showconfig" ]; then\n'
                        '  echo "Extra libraries: -lz;-ldl"\n'
                        'else\n  printf "%s\\n" "$@"\nfi\n')
        fake.chmod(0o755)
        body = 'set(UNIX TRUE)\nset(PROJECT_BINARY_DIR ' + bracket(self.work) + ')\n'
        body += 'set(_yoda_h5cc ' + bracket(fake) + ')\n' + extra + block
        return body

    def test_yoda_wrapper_is_executable_and_preserves_normal_arguments(self):
        self.run_script(self.yoda_fixture())
        wrapper = self.work / 'yoda-h5cc'
        self.assertEqual(wrapper.stat().st_mode & 0o777, 0o755)
        query = subprocess.run([str(wrapper), '-showconfig'], capture_output=True, text=True, check=True)
        self.assertEqual(query.stdout.strip(), 'Extra libraries: -lz -ldl')
        normal = subprocess.run([str(wrapper), 'argument with spaces', '-I/test'],
                                capture_output=True, text=True, check=True)
        self.assertEqual(normal.stdout.splitlines(), ['argument with spaces', '-I/test'])

    def test_yoda_permission_failure_is_reported(self):
        self.run_script(self.yoda_fixture('''
function(execute_process)
  set(_yoda_h5cc_chmod_result "permission denied" PARENT_SCOPE)
endfunction()
'''), success=False)


if __name__ == '__main__':
    unittest.main(verbosity=2)
