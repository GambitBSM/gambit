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
function(expect value request)
  get_property(cached CACHE GAMBIT_TRIM_BACKEND_INTERFACES PROPERTY VALUE)
  get_property(type CACHE GAMBIT_TRIM_BACKEND_INTERFACES PROPERTY TYPE)
  if(NOT cached STREQUAL request OR NOT type STREQUAL "STRING")
    message(FATAL_ERROR "Expected persistent mode ${request}, got ${cached} (${type})")
  endif()
  if(NOT GAMBIT_TRIM_BACKEND_INTERFACES_EFFECTIVE STREQUAL value)
    message(FATAL_ERROR "Expected effective trim ${value}, got ${GAMBIT_TRIM_BACKEND_INTERFACES_EFFECTIVE}")
  endif()
  if(NOT GAMBIT_TRIM_BACKEND_INTERFACES_REQUESTED STREQUAL request)
    message(FATAL_ERROR "Incorrect requested mode")
  endif()
  if(DEFINED GAMBIT_TRIM_AUTOMATIC_VALUE)
    message(FATAL_ERROR "Obsolete automatic-value marker remains")
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
expect({value} {value})
set(GAMBIT_BITS DarkBit)
_gambit_resolve_trim_default()
expect({value} {value})
''')

    def test_automatic_trim_tracks_module_switches(self):
        self.trim_fixture('''
set(GAMBIT_BITS ColliderBit DarkBit ScannerBit)
_gambit_resolve_trim_default()
expect(OFF AUTO)
set(GAMBIT_BITS ColliderBit ScannerBit)
_gambit_resolve_trim_default()
expect(ON AUTO)
set(GAMBIT_BITS ColliderBit DarkBit ScannerBit)
_gambit_resolve_trim_default()
expect(OFF AUTO)
''')

    def test_override_of_automatic_trim_stays_explicit(self):
        self.trim_fixture('''
set(GAMBIT_BITS ColliderBit)
_gambit_resolve_trim_default()
expect(ON AUTO)
set(GAMBIT_TRIM_BACKEND_INTERFACES OFF CACHE BOOL "override" FORCE)
_gambit_resolve_trim_default()
expect(OFF OFF)
set(GAMBIT_BITS ColliderBit DarkBit ScannerBit)
_gambit_resolve_trim_default()
expect(OFF OFF)
set(GAMBIT_BITS ColliderBit)
_gambit_resolve_trim_default()
expect(OFF OFF)
''')

    def test_explicit_value_equal_to_old_automatic_result_is_persistent(self):
        for value, first, second in [('OFF', 'ColliderBit DarkBit ScannerBit', 'ColliderBit'),
                                     ('ON', 'ColliderBit', 'ColliderBit DarkBit ScannerBit')]:
            for kind in ('BOOL', 'STRING'):
                with self.subTest(value=value, type=kind):
                    self.trim_fixture(f'''
set(GAMBIT_BITS {first})
_gambit_resolve_trim_default()
expect({value} AUTO)
set(GAMBIT_TRIM_BACKEND_INTERFACES {value} CACHE {kind} "explicit" FORCE)
set(GAMBIT_BITS {second})
_gambit_resolve_trim_default()
expect({value} {value})
set(GAMBIT_BITS {first})
_gambit_resolve_trim_default()
expect({value} {value})
''')

    def test_legacy_caches_are_preserved_and_can_return_to_auto(self):
        for value in ('ON', 'OFF'):
            with self.subTest(value=value):
                self.trim_fixture(f'''
set(GAMBIT_TRIM_BACKEND_INTERFACES {value} CACHE BOOL "legacy" FORCE)
set(GAMBIT_TRIM_AUTOMATIC_VALUE {value} CACHE INTERNAL "ambiguous old default" FORCE)
set(GAMBIT_BITS ColliderBit DarkBit ScannerBit)
_gambit_resolve_trim_default()
expect({value} {value})
set(GAMBIT_TRIM_BACKEND_INTERFACES AUTO CACHE STRING "restore automatic mode" FORCE)
_gambit_resolve_trim_default()
expect(OFF AUTO)
set(GAMBIT_BITS ColliderBit)
_gambit_resolve_trim_default()
expect(ON AUTO)
''')

    def test_bool_aliases_and_normal_overrides_remain_supported(self):
        for value, expected in [('TRUE', 'ON'), ('yes', 'ON'), ('1', 'ON'), ('FALSE', 'OFF'),
                                ('no', 'OFF'), ('0', 'OFF'), ('', 'OFF')]:
            with self.subTest(value=value):
                self.trim_fixture('set(GAMBIT_TRIM_BACKEND_INTERFACES ' + bracket(value) + ')\n' +
                                  '_gambit_resolve_trim_default()\n' + f'expect({expected} {expected})')
        self.trim_fixture('''
set(GAMBIT_TRIM_BACKEND_INTERFACES AUTO CACHE STRING "initial" FORCE)
set(GAMBIT_TRIM_BACKEND_INTERFACES OFF)
set(GAMBIT_BITS ColliderBit)
_gambit_resolve_trim_default()
expect(OFF OFF)
''')

    def test_invalid_modes_fail_clearly(self):
        for value in ('AUTOO', 'maybe', '2'):
            with self.subTest(value=value):
                result = self.run_script(self.function('_gambit_resolve_trim_default') +
                    '\nset(GAMBIT_TRIM_BACKEND_INTERFACES ' + bracket(value) + ')\n' +
                    '_gambit_resolve_trim_default()', success=False)
                self.assertIn('Invalid GAMBIT_TRIM_BACKEND_INTERFACES', result.stderr)

    def test_optin_harvest_uses_effective_mode_and_propagates_it(self):
        resolver = self.function('_gambit_resolve_trim_default')
        configure = self.function('gambit_configure_optin_build')
        for mode, bits, effective in [('AUTO', 'ColliderBit;DarkBit;ScannerBit', 'OFF'),
                                      ('AUTO', 'ColliderBit', 'ON'), ('OFF', 'ColliderBit', 'OFF'),
                                      ('ON', 'ColliderBit;DarkBit;ScannerBit', 'ON')]:
            with self.subTest(mode=mode, bits=bits):
                self.run_script(resolver + '\n' + configure + '''
function(_gambit_print_optin_summary bits force output)
  set(${output} unused_backend PARENT_SCOPE)
endfunction()
set(ALL_GAMBIT_BITS ColliderBit DarkBit ScannerBit)
set(itch original)
''' + f'set(GAMBIT_BITS {bracket(bits)})\n' +
                    f'set(GAMBIT_TRIM_BACKEND_INTERFACES {mode} CACHE STRING "mode" FORCE)\n' +
                    'gambit_configure_optin_build()\n' +
                    f'set(expected {effective})\n' + '''
if(NOT GAMBIT_TRIM_BACKEND_INTERFACES_EFFECTIVE STREQUAL expected)
  message(FATAL_ERROR "Effective trim was not propagated")
endif()
if(expected)
  if(NOT BACKEND_HARVESTER_EXTRA_ARGS MATCHES "--bits=" OR NOT "unused_backend" IN_LIST itch)
    message(FATAL_ERROR "Trimming did not reach harvest/disabled targets")
  endif()
elseif(BACKEND_HARVESTER_EXTRA_ARGS OR NOT itch STREQUAL "original")
  message(FATAL_ERROR "AUTO resolving OFF or explicit OFF must not trim")
endif()
if(NOT "${BACKEND_HARVESTER_EXTRA_ARGS}" STREQUAL "${update_cmakelists_extra_args}")
  message(FATAL_ERROR "Harvester and generated CMake inputs disagree")
endif()
''')

    def test_summaries_use_effective_value_with_auto_input(self):
        for name, function in [('CBSCompilerSummary.cmake', 'cbs_print_compiler_summary'),
                               ('GAMBITBuildSummary.cmake', 'gambit_print_build_summary')]:
            source = (ROOT / 'cmake/presets' / name).read_text()
            body = re.search(rf'function\({function}\b.*?endfunction\(\)', source, re.DOTALL).group(0)
            for effective in ('ON', 'OFF'):
                with self.subTest(summary=name, effective=effective):
                    output = self.work / 'summary.txt'
                    script = ('''
function(cbs_summary_line key value)
  file(APPEND "${OUTPUT}" "${key}|${value}\n")
endfunction()
function(cbs_compiler_is_supported id version supported reason)
  set(${supported} TRUE PARENT_SCOPE)
endfunction()
function(gambit_print_compiler_cache_summary)
endfunction()
function(cbs_print_validation_summary)
endfunction()
function(preset_print_feature_groups)
endfunction()
''' + body + '\nset(OUTPUT ' + bracket(output) + ')\n' +
                    'file(WRITE "${OUTPUT}" "")\nset(GAMBIT_PRESET_TOOLCHAIN llvm)\n' +
                    f'set(CBS_PRESET_BUILD {"TRUE" if name.startswith("CBS") else "FALSE"})\n' +
                    'set(GAMBIT_TRIM_BACKEND_INTERFACES AUTO)\n' +
                    'set(GAMBIT_TRIM_BACKEND_INTERFACES_REQUESTED AUTO)\n' +
                    f'set(GAMBIT_TRIM_BACKEND_INTERFACES_EFFECTIVE {effective})\n' +
                    'set(GAMBIT_TRIM_TOTAL_COUNT 10)\nset(GAMBIT_TRIM_USED_COUNT 2)\n' + function + '()')
                    self.run_script(script)
                    lines = output.read_text().splitlines()
                    self.assertIn('Backend trim|AUTO -> ' + effective, lines)
                    self.assertIn('Backends|' + ('2 of 10 kept' if effective == 'ON' else 'not trimmed'), lines)

    def git_download_fixture(self, case):
        capture = self.work / 'git-commands.txt'
        directory = self.work / 'downloaded source'
        script = ('''
set(DIR ''' + bracket(directory) + ')\nset(URL fixture://no-network)\nset(TAG v1.0.2)\n' +
            'set(CAPTURE ' + bracket(capture) + ')\nset(CASE ' + bracket(case) + ')\n' + r'''
function(execute_process)
  # Capture real download command construction. Never run Git/network here.
  set(arguments "${ARGV}")
  foreach(expected GIT_TERMINAL_PROMPT=0 GIT_ASKPASS=/usr/bin/false SSH_ASKPASS=/usr/bin/false)
    if(NOT expected IN_LIST arguments)
      message(FATAL_ERROR "Interactive Git command: ${ARGV}")
    endif()
  endforeach()
  list(FIND arguments TIMEOUT index)
  if(index EQUAL -1)
    message(FATAL_ERROR "Unbounded Git command")
  endif()
  math(EXPR index "${index}+1")
  list(GET arguments ${index} timeout)
  if(NOT timeout EQUAL 300)
    message(FATAL_ERROR "Unexpected Git timeout")
  endif()
  list(FIND arguments RESULT_VARIABLE index)
  math(EXPR index "${index}+1")
  list(GET arguments ${index} result)
  list(FIND arguments ERROR_VARIABLE index)
  math(EXPR index "${index}+1")
  list(GET arguments ${index} error)
  set(status 0)
  if("clone" IN_LIST arguments)
    file(APPEND "${CAPTURE}" "clone\n")
    if(CASE STREQUAL "clone_failure")
      # Exercise diagnostic wrapping on every host/CMake version.
      set(status "Process\n  terminated due to timeout")
    else()
      file(MAKE_DIRECTORY "${DIR}/.git")
    endif()
  elseif("checkout" IN_LIST arguments)
    file(APPEND "${CAPTURE}" "checkout\n")
    get_property(count GLOBAL PROPERTY checkout_count)
    if(NOT count)
      set(count 0)
    endif()
    math(EXPR count "${count}+1")
    set_property(GLOBAL PROPERTY checkout_count "${count}")
    if(CASE STREQUAL "checkout_failure" OR (count EQUAL 1 AND NOT CASE STREQUAL "success"))
      set(status 1)
    endif()
  elseif("fetch" IN_LIST arguments)
    file(APPEND "${CAPTURE}" "fetch\n")
    if(CASE STREQUAL "fetch_failure")
      set(status 1)
    endif()
  else()
    message(FATAL_ERROR "Unexpected download command: ${ARGV}")
  endif()
  set(${result} "${status}" PARENT_SCOPE)
  set(${error} "fixture failure" PARENT_SCOPE)
endfunction()
''' + 'include(' + bracket(ROOT / 'cmake/scripts/ensure_git_clone.cmake') + ')')
        result = self.run_script(script, success=case in ('success', 'fetch_success', 'cached_source'))
        return result, capture.read_text().splitlines() if capture.exists() else []

    def test_git_download_is_noninteractive_and_bounded(self):
        _, commands = self.git_download_fixture('success')
        self.assertEqual(commands, ['clone', 'checkout'])

    def test_git_tag_fetch_retry_is_noninteractive_and_bounded(self):
        _, commands = self.git_download_fixture('fetch_success')
        self.assertEqual(commands, ['clone', 'checkout', 'fetch', 'checkout'])

    def test_complete_git_download_is_left_for_identity_preparation(self):
        directory = self.work / 'downloaded source'
        (directory / '.git').mkdir(parents=True)
        (directory / 'configure').write_text('existing source')
        _, commands = self.git_download_fixture('cached_source')
        self.assertEqual(commands, [])
        self.assertEqual((directory / 'configure').read_text(), 'existing source')

    def test_git_download_failures_stop_without_extra_steps(self):
        for case, expected, diagnostic in (
            ('clone_failure', ['clone'], 'Process terminated due to timeout'),
            ('fetch_failure', ['clone', 'checkout', 'fetch'], 'git fetch'),
            ('checkout_failure', ['clone', 'checkout', 'fetch', 'checkout'], 'git checkout')):
            with self.subTest(case=case):
                try:
                    result, commands = self.git_download_fixture(case)
                    self.assertEqual(commands, expected)
                    self.assertIn(diagnostic, ' '.join(result.stderr.split()))
                finally:
                    shutil.rmtree(self.work / 'downloaded source', ignore_errors=True)
                    (self.work / 'git-commands.txt').unlink(missing_ok=True)

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
