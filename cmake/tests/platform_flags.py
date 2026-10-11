#!/usr/bin/env python3
"""Script-only platform/OpenMP policy checks. No real tool or compiler probes.

The platform and OpenMP policy run with captured FindOpenMP results and synthetic
Homebrew replies. Real compiler detection and linking remain manual validation.
"""
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def bracket(value):
    return '[==[' + str(value) + ']==]'


STUBS = r'''
function(execute_process)
  cmake_parse_arguments(P "OUTPUT_STRIP_TRAILING_WHITESPACE;ERROR_QUIET"
    "RESULT_VARIABLE;OUTPUT_VARIABLE;ERROR_VARIABLE;TIMEOUT" "COMMAND" ${ARGN})
  list(LENGTH P_COMMAND n)
  if(NOT n EQUAL 3)
    message(FATAL_ERROR "Unexpected real probe: ${P_COMMAND}")
  endif()
  list(GET P_COMMAND 0 tool)
  list(GET P_COMMAND 1 option)
  list(GET P_COMMAND 2 package)
  if(NOT tool STREQUAL "${FIXTURE_ROOT}/brew" OR NOT option STREQUAL "--prefix")
    message(FATAL_ERROR "Real process blocked: ${P_COMMAND}")
  endif()
  set(result 0)
  if(package STREQUAL "libomp")
    set(output "${FIXTURE_OMP}")
  elseif(package STREQUAL "llvm")
    set(output "${FIXTURE_ROOT}/llvm")
  else()
    message(FATAL_ERROR "Unexpected package probe: ${package}")
  endif()
  if(FIXTURE_BREW_FAILURE)
    set(result 1)
    set(output "")
  endif()
  if(P_RESULT_VARIABLE)
    set(${P_RESULT_VARIABLE} "${result}" PARENT_SCOPE)
  endif()
  if(P_OUTPUT_VARIABLE)
    set(${P_OUTPUT_VARIABLE} "${output}" PARENT_SCOPE)
  endif()
endfunction()
function(try_compile)
  message(FATAL_ERROR "Real compiler probe blocked")
endfunction()
function(try_run)
  message(FATAL_ERROR "Real compiler probe blocked")
endfunction()
function(find_program name)
  if(NOT name STREQUAL "_gambit_openmp_brew")
    message(FATAL_ERROR "Unexpected program search: ${name}")
  endif()
  if(FIXTURE_NO_BREW)
    set(${name} FALSE PARENT_SCOPE)
  else()
    set(${name} "${FIXTURE_ROOT}/brew" PARENT_SCOPE)
  endif()
endfunction()
function(find_package package)
  if(NOT package STREQUAL "OpenMP" OR NOT "${ARGN}" STREQUAL "QUIET;COMPONENTS;C;CXX;Fortran")
    message(FATAL_ERROR "Unexpected package discovery: ${ARGV}")
  endif()
  foreach(lang C CXX Fortran)
    if(NOT DEFINED OpenMP_${lang}_FLAGS)
      set(OpenMP_${lang}_FLAGS "-fopenmp" CACHE STRING "fixture detected flag")
    endif()
    if(lang STREQUAL FIXTURE_MISSING_LANGUAGE)
      set(OpenMP_${lang}_FOUND FALSE PARENT_SCOPE)
    else()
      set(OpenMP_${lang}_FOUND TRUE PARENT_SCOPE)
    endif()
    if(lang STREQUAL "Fortran")
      set(OpenMP_${lang}_LIBRARIES "${FIXTURE_ROOT}/libgomp.dylib" PARENT_SCOPE)
    elseif(OpenMP_omp_LIBRARY)
      set(OpenMP_${lang}_LIBRARIES "${OpenMP_omp_LIBRARY}" PARENT_SCOPE)
    else()
      set(OpenMP_${lang}_LIBRARIES "${FIXTURE_ROOT}/libgomp.dylib" PARENT_SCOPE)
    endif()
  endforeach()
endfunction()
function(expect_equal actual expected)
  if(NOT "${actual}" STREQUAL "${expected}")
    message(FATAL_ERROR "Expected '${expected}', got '${actual}'")
  endif()
endfunction()
'''


class PlatformFlagTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='gambit platform ')
        self.addCleanup(self.temp.cleanup)
        self.work = Path(self.temp.name)
        self.cmake = shutil.which('cmake')
        self.assertIsNotNone(self.cmake)
        for name in ('sdk', 'SDK with spaces', 'omp/include', 'omp with spaces/include', 'llvm/bin'):
            (self.work / name).mkdir(parents=True)
        for name in ('brew', 'llvm/bin/clang++', 'libgomp.dylib', 'omp/lib/libomp.dylib',
                     'omp with spaces/lib/libomp.dylib', 'manual/libomp.dylib'):
            file = self.work / name
            file.parent.mkdir(parents=True, exist_ok=True)
            file.write_text('synthetic file; never executed')

    def run_case(self, settings=None, body='', platform=True, omp=True, fatal=False):
        values = {'FIXTURE_ROOT': self.work, 'FIXTURE_OMP': self.work / 'omp',
                  'CMAKE_SYSTEM_NAME': 'Darwin', 'CMAKE_C_COMPILER_ID': 'Clang',
                  'CMAKE_CXX_COMPILER_ID': 'Clang', 'CMAKE_Fortran_COMPILER_ID': 'GNU',
                  'CMAKE_CXX_COMPILER': self.work / 'llvm/bin/clang++',
                  'CMAKE_OSX_SYSROOT': self.work / 'sdk', 'MACOS_DEPLOYMENT_TARGET': '27.0',
                  'CMAKE_C_FLAGS': '-O1', 'CMAKE_CXX_FLAGS': '-O1', 'CMAKE_Fortran_FLAGS': '-O1'}
        values.update(settings or {})
        lines = ['cmake_minimum_required(VERSION 3.16.3)', STUBS]
        for name, value in values.items():
            lines.append('set(' + name + ' ' + bracket(value) + ')')
        lines += ['include(' + bracket(ROOT / 'cmake/MacOSX.cmake') + ')',
                  'include(' + bracket(ROOT / 'cmake/OpenMP.cmake') + ')']
        if platform:
            lines += ['set(PROJECT_NAME fixture)',
                      'include(' + bracket(ROOT / 'cmake/MacOSX.cmake') + ')']
        if omp:
            lines += ['gambit_configure_openmp()']
        lines += [body, '''foreach(key CMAKE_C_FLAGS CMAKE_CXX_FLAGS CMAKE_Fortran_FLAGS
            CMAKE_SHARED_LINKER_FLAGS OpenMP_C_FLAGS OpenMP_CXX_FLAGS OpenMP_Fortran_FLAGS
            GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP_LDFLAGS
            GAMBIT_MACOS_CMAKE_SYSROOT_ARG GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG
            external cmake_external backend_c99)
          message(STATUS "RESULT_${key}=[${${key}}]")
        endforeach()''']
        script = self.work / 'case.cmake'
        script.write_text('\n'.join(lines))
        result = subprocess.run([self.cmake, '-P', str(script)], cwd=self.work,
                                capture_output=True, text=True)
        output = result.stdout + result.stderr
        if fatal:
            self.assertNotEqual(result.returncode, 0, output)
            return ' '.join(output.split())
        self.assertEqual(result.returncode, 0, output)
        return dict(re.findall(r'RESULT_(\w+)=\[(.*?)\]', output))

    def test_native_c_and_cxx_leave_sdk_and_minimum_to_cmake(self):
        values = self.run_case()
        for lang in ('C', 'CXX'):
            flags = shlex.split(values['CMAKE_' + lang + '_FLAGS'])
            self.assertNotIn('-isysroot' + str(self.work / 'sdk'), flags)
            self.assertNotIn('-mmacosx-version-min=27.0', flags)
            self.assertEqual(flags.count('-fopenmp'), 1)
        self.assertNotIn('-mmacosx-version-min', values['CMAKE_SHARED_LINKER_FLAGS'])
        self.assertIn('-Wl,-undefined,dynamic_lookup', values['CMAKE_SHARED_LINKER_FLAGS'])

    def test_fortran_receives_missing_sdk_and_minimum_only_once(self):
        for sdk in ('sdk', 'SDK with spaces'):
            with self.subTest(sdk=sdk):
                values = self.run_case({'CMAKE_OSX_SYSROOT': self.work / sdk}, body=
                    'include(' + bracket(ROOT / 'cmake/MacOSX.cmake') + ')\ngambit_configure_openmp()')
                flags = shlex.split(values['CMAKE_Fortran_FLAGS'])
                self.assertEqual(flags.count('-isysroot' + str(self.work / sdk)), 1)
                self.assertEqual(flags.count('-mmacosx-version-min=27.0'), 1)
                self.assertEqual(flags.count('-fopenmp'), 1)

    def test_fortran_platform_support_avoids_manual_duplicate(self):
        for supported in ('SYSROOT', 'OSX_DEPLOYMENT_TARGET'):
            with self.subTest(supported=supported):
                settings = {'CMAKE_Fortran_' + supported + '_FLAG': 'supported'}
                flags = shlex.split(self.run_case(settings)['CMAKE_Fortran_FLAGS'])
                if supported == 'SYSROOT':
                    self.assertFalse(any(f.startswith('-isysroot') for f in flags))
                    self.assertIn('-mmacosx-version-min=27.0', flags)
                else:
                    self.assertNotIn('-mmacosx-version-min=27.0', flags)
                    self.assertIn('-isysroot' + str(self.work / 'sdk'), flags)

    def test_linux_flags_are_unchanged_by_macos_policy(self):
        values = self.run_case({'CMAKE_SYSTEM_NAME': 'Linux'}, omp=False, body='''
          gambit_macos_external_flags("-O2 -std=gnu99" external)
          gambit_macos_cmake_external_flags("${external}" cmake_external)''')
        self.assertEqual(values['CMAKE_Fortran_FLAGS'], '-O1')
        self.assertEqual(values['external'], '-O2 -std=gnu99')
        self.assertEqual(values['cmake_external'], values['external'])
        self.assertEqual(values['GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG'], '')

    def test_other_fortran_compilers_do_not_receive_gnu_fallback(self):
        flags = self.run_case({'CMAKE_Fortran_COMPILER_ID': 'IntelLLVM'}, omp=False)['CMAKE_Fortran_FLAGS']
        self.assertEqual(flags, '-O1')

    def test_conflicting_native_sdk_or_minimum_fails_clearly(self):
        for flags, text in (('-mmacosx-version-min=28.0', 'Conflicting macOS minimum'),
                            ('-isysroot /wrong/sdk', 'Conflicting macOS SDK'),
                            ('-isysroot/wrong/sdk', 'Conflicting macOS SDK'),
                            ('-isysroot', 'Missing SDK path')):
            with self.subTest(flags=flags):
                output = self.run_case({'CMAKE_Fortran_FLAGS': flags}, omp=False, fatal=True)
                self.assertIn(text, output)
        self.assertIn('Conflicting macOS minimum', self.run_case(
            {'CMAKE_CXX_FLAGS_RELEASE': '-mmacosx-version-min=28'}, omp=False, fatal=True))

    def test_matching_manual_policy_and_sdk_symlink_are_accepted(self):
        alias = self.work / 'sdk alias'
        alias.symlink_to(self.work / 'sdk')
        flags = '-isysroot "' + str(alias) + '" -mmacosx-version-min=27'
        self.run_case({'CMAKE_CXX_FLAGS': flags}, omp=False)

    def test_external_flags_share_policy_and_cmake_recipes_keep_package_options(self):
        values = self.run_case({'CMAKE_OSX_SYSROOT': self.work / 'SDK with spaces'}, omp=False, body='''
          gambit_macos_external_flags("-O2 -std=c++14 -stdlib=libc++ -I/special" external)
          gambit_macos_external_flags("${external}" external)
          gambit_macos_cmake_external_flags("${external}" cmake_external)''')
        flags = shlex.split(values['external'])
        self.assertEqual(flags.count('-isysroot' + str(self.work / 'SDK with spaces')), 1)
        self.assertEqual(flags.count('-mmacosx-version-min=27.0'), 1)
        self.assertEqual(shlex.split(values['cmake_external']),
                         ['-O2', '-std=c++14', '-stdlib=libc++', '-I/special'])
        self.assertEqual(values['GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG'], '-DCMAKE_OSX_DEPLOYMENT_TARGET=27.0')

    def test_native_cache_and_openmp_flags_use_the_same_hint(self):
        values = self.run_case(body='''
          foreach(lang C CXX)
            get_property(cached CACHE OpenMP_${lang}_FLAGS PROPERTY VALUE)
            expect_equal("${cached}" "${OpenMP_${lang}_FLAGS}")
            expect_equal("${CMAKE_${lang}_FLAGS}" "-O1 ${OpenMP_${lang}_FLAGS}")
          endforeach()''')
        self.assertEqual(shlex.split(values['OpenMP_CXX_FLAGS']),
                         ['-Xclang', '-fopenmp', '-I' + str(self.work / 'omp/include')])

    def test_exact_legacy_hints_are_migrated(self):
        values = self.run_case(omp=False, body='''
          foreach(lang C CXX)
            set(OpenMP_${lang}_FLAGS "-fopenmp=libomp -I${FIXTURE_OMP}/include" CACHE STRING fixture)
            set(OpenMP_${lang}_LIB_NAMES omp CACHE STRING fixture)
          endforeach()
          set(OpenMP_omp_LIBRARY "${FIXTURE_OMP}/lib/libomp.dylib" CACHE FILEPATH fixture)
          gambit_configure_openmp()
          get_property(cached CACHE OpenMP_CXX_FLAGS PROPERTY VALUE)
          expect_equal("${cached}" "${OpenMP_CXX_FLAGS}")''')
        self.assertEqual(shlex.split(values['OpenMP_CXX_FLAGS']),
                         ['-Xclang', '-fopenmp', '-I' + str(self.work / 'omp/include')])

    def test_manual_openmp_hints_are_preserved(self):
        values = self.run_case(omp=False, body='''
          set(OpenMP_CXX_FLAGS "-fopenmp=libomp -I/custom" CACHE STRING fixture)
          set(OpenMP_CXX_LIB_NAMES custom CACHE STRING fixture)
          set(OpenMP_omp_LIBRARY "${FIXTURE_ROOT}/manual/libomp.dylib" CACHE FILEPATH fixture)
          gambit_configure_openmp()
          expect_equal("${OpenMP_CXX_FLAGS}" "-fopenmp=libomp -I/custom")
          expect_equal("${OpenMP_CXX_LIB_NAMES}" custom)
          expect_equal("${OpenMP_omp_LIBRARY}" "${FIXTURE_ROOT}/manual/libomp.dylib")
          expect_equal("${OpenMP_CXX_LIBRARIES}" "${FIXTURE_ROOT}/manual/libomp.dylib")
        ''')
        self.assertEqual(shlex.split(values['GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP_LDFLAGS']),
                         ['-L' + str(self.work / 'manual'), '-Wl,-rpath,' + str(self.work / 'manual')])

    def test_owned_openmp_hints_follow_changed_prefix_across_script_processes(self):
        cache = self.work / 'saved_hints.cmake'
        self.run_case(body='''
          foreach(key OpenMP_C_FLAGS OpenMP_CXX_FLAGS OpenMP_C_LIB_NAMES OpenMP_CXX_LIB_NAMES OpenMP_omp_LIBRARY)
            file(APPEND "${FIXTURE_ROOT}/saved_hints.cmake"
              "set(${key} [==[${${key}}]==] CACHE STRING fixture)\\n"
              "set(GAMBIT_OPENMP_AUTO_${key} [==[${GAMBIT_OPENMP_AUTO_${key}}]==] CACHE INTERNAL fixture)\\n")
          endforeach()''')
        values = self.run_case({'FIXTURE_OMP': self.work / 'omp with spaces'}, omp=False,
                              body='include(' + bracket(cache) + ')\n' + '''
          gambit_configure_openmp()
          expect_equal("${OpenMP_omp_LIBRARY}" "${FIXTURE_OMP}/lib/libomp.dylib")''')
        self.assertEqual(shlex.split(values['OpenMP_CXX_FLAGS']),
                         ['-Xclang', '-fopenmp', '-I' + str(self.work / 'omp with spaces/include')])

    def test_user_edited_automatic_hint_is_preserved(self):
        self.run_case(body='''
          set(OpenMP_CXX_FLAGS "-custom-user-flags" CACHE STRING fixture FORCE)
          gambit_configure_openmp()
          expect_equal("${OpenMP_CXX_FLAGS}" "-custom-user-flags")
          if(DEFINED GAMBIT_OPENMP_AUTO_OpenMP_CXX_FLAGS)
            message(FATAL_ERROR "User-owned hint must not be marked automatic")
          endif()''')

    def test_all_three_openmp_languages_are_required(self):
        for lang in ('C', 'CXX', 'Fortran'):
            with self.subTest(language=lang):
                output = self.run_case({'FIXTURE_MISSING_LANGUAGE': lang}, fatal=True)
                self.assertIn('OpenMP is required for C, C++ and Fortran', output)

    def test_brew_failure_or_absence_keeps_finder_results(self):
        for settings in ({'FIXTURE_NO_BREW': 'TRUE'}, {'FIXTURE_BREW_FAILURE': 'TRUE'},
                         {'CMAKE_SYSTEM_NAME': 'Linux', 'CMAKE_C_COMPILER_ID': 'GNU', 'CMAKE_CXX_COMPILER_ID': 'GNU'}):
            with self.subTest(settings=settings):
                values = self.run_case(settings)
                self.assertEqual(values['OpenMP_CXX_FLAGS'], '-fopenmp')
                self.assertEqual(values['GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP'], 'FALSE')

    def test_appleclang_and_upstream_llvm_share_compile_flags_with_separate_runtime_guard(self):
        for compiler_id, guard in (('AppleClang', 'FALSE'), ('Clang', 'TRUE')):
            with self.subTest(compiler_id=compiler_id):
                values = self.run_case({'CMAKE_C_COMPILER_ID': compiler_id, 'CMAKE_CXX_COMPILER_ID': compiler_id})
                self.assertEqual(shlex.split(values['OpenMP_CXX_FLAGS']),
                                 ['-Xclang', '-fopenmp', '-I' + str(self.work / 'omp/include')])
                self.assertEqual(values['GAMBIT_MACOS_HOMEBREW_LLVM_OPENMP'], guard)

    def test_backend_c_dialects_receive_common_platform_policy(self):
        source = (ROOT / 'CMakeLists.txt').read_text()
        section = source[source.index('# Shell and Autotools projects'):source.index('string(FIND "${CMAKE_CXX_FLAGS}" "-rdynamic"')]
        values = self.run_case(omp=False, body='''set(BACKEND_C_FLAGS "-O2")
          set(BACKEND_CXX_FLAGS "-O2 -std=c++17")
          set(BACKEND_Fortran_FLAGS "${CMAKE_Fortran_FLAGS}")
          ''' + section + '''
          expect_equal("${BACKEND_C99_FLAGS}" "${BACKEND_C_FLAGS} -std=c99")
          set(backend_c99 "${BACKEND_C99_FLAGS}")
          gambit_macos_cmake_external_flags("${GAMBIT_BACKEND_SHARED_LINKER_FLAGS}" cmake_external)''')
        self.assertIn('-mmacosx-version-min=27.0', values['backend_c99'])
        self.assertNotIn('-mmacosx-version-min', values['cmake_external'])
        self.assertIn('-Wl,-undefined,dynamic_lookup', values['cmake_external'])

    def test_actual_cmake_recipe_arguments_drop_common_flags_but_keep_platform_arguments(self):
        count = 0
        for file in ('cmake/backends.cmake', 'cmake/contrib.cmake', 'cmake/scanners.cmake'):
            source = (ROOT / file).read_text()
            for recipe in re.finditer(r'^\s*CMAKE_ARGS ([^\n]+)$', source, re.MULTILINE):
                args = recipe.group(1)
                helpers = []
                definitions = []
                if '${VPP_CMAKE_FLAGS}' in args:
                    args_definition = re.search(r'^set\(VPP_CMAKE_FLAGS [^\n]+', source, re.MULTILINE).group(0)
                    flags_line = args_definition
                    definitions.append(args_definition)
                else:
                    flags_line = args
                outputs = re.findall(r'\$\{(\w+_CMAKE_EXTERNAL)\}', flags_line)
                for output in outputs:
                    helper = re.search(r'^\s*(gambit_macos_cmake_external_flags\("\$\{(\w+)\}" '
                                       + output + r'\))$', source, re.MULTILINE)
                    self.assertIsNotNone(helper)
                    self.assertLess(helper.start(), recipe.start())
                    helpers += ['set(' + helper.group(2) + ' "${external}")', helper.group(1)]
                body = '''
                  gambit_macos_external_flags("-O2 -std=c++14 -stdlib=libc++ -I/special" external)
                  function(capture_recipe)
                    foreach(arg IN LISTS ARGN)
                      if(arg MATCHES "^-DCMAKE_(C|CXX|SHARED_LINKER)_FLAGS=(.*)$")
                        expect_equal("${CMAKE_MATCH_2}" "-O2 -std=c++14 -stdlib=libc++ -I/special")
                      endif()
                    endforeach()
                    list(FIND ARGN "${GAMBIT_MACOS_CMAKE_SYSROOT_ARG}" sdk)
                    list(FIND ARGN "${GAMBIT_MACOS_CMAKE_DEPLOYMENT_TARGET_ARG}" minimum)
                    if(sdk EQUAL -1 OR minimum EQUAL -1)
                      message(FATAL_ERROR "Recipe lost the common SDK/minimum arguments: ${ARGN}")
                    endif()
                  endfunction()
                ''' + '\n'.join(helpers + definitions) + '\ncapture_recipe(' + args + ')'
                with self.subTest(file=file, recipe=args):
                    self.run_case(omp=False, body=body)
                count += 1
        self.assertEqual(count, 7)


if __name__ == '__main__':
    unittest.main(verbosity=2)
