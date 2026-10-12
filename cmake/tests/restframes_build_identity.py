#!/usr/bin/env python3
"""RestFrames identity checks with script-only CMake and temporary Git sources.

No project configure, compiler, make, network, or real installation is used.
"""
from pathlib import Path
import hashlib
import os
import shutil
import subprocess
import tempfile
import unittest

from contrib_retention import bracket, CAPTURE

ROOT = Path(__file__).resolve().parents[2]
MODULE = ROOT / 'cmake/ContribBuildIdentity.cmake'
STEPS = ('download', 'update', 'prepare_source', 'patch', 'configure', 'build',
         'install', 'record_identity', 'done')


class RestFramesBuildIdentityTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix='gambit-restframes-identity-')
        self.work = Path(self.temporary.name)
        self.source = self.work / 'source tree [[x]]'
        self.build = self.work / 'build tree'
        self.package = self.source / 'contrib/RestFrames-1.0.2'
        self.cmake = shutil.which('cmake')
        self.assertIsNotNone(self.cmake)
        self.assertIsNotNone(shutil.which('git'))
        for name in ('ContribBuildIdentity.cmake', 'scripts/patch_restframes_quiet.cmake'):
            self.put(self.source / 'cmake' / name, (ROOT / 'cmake' / name).read_bytes())
        # A configure sentinel is tracked but is never executed.
        self.put(self.package / 'configure', b'NEVER RUN THIS FIXTURE CONFIGURE\n')
        self.pristine = b'#include "RestFrames/RFBase.hh"\nstatic void initializer(void){\n    printf("fixture");\n}\n'
        self.put(self.package / 'src/RFBase.cc', self.pristine)
        self.put(self.package / 'inc/RestFrames/RestFrames.hh', b'fixture header')
        self.git('init', '-q', str(self.package))
        self.git('-C', str(self.package), 'add', '.')
        self.git('-C', str(self.package), '-c', 'user.name=Fixture', '-c',
                 'user.email=fixture@example.invalid', '-c', 'commit.gpgsign=false',
                 '-c', 'core.hooksPath=/dev/null', 'commit', '-qm', 'fixture source')
        self.git('-C', str(self.package), 'tag', 'v1.0.2')
        self.git('-C', str(self.package), 'remote', 'add', 'origin', 'https://github.com/crogan/RestFrames')
        for name in ('C', 'CXX', 'Fortran'):
            self.put(self.work / f'compiler {name}', b'never execute')
        self.put(self.work / 'root/bin/root-config', b'never execute root-config')
        self.put(self.work / 'root/lib/libCore.a', b'fixture ROOT library')
        for name in ('RVersion.h', 'RConfigure.h'):
            self.put(self.work / 'root/include' / name, b'fixture ROOT header')
        self.put(self.source / 'contrib/unrelated/keep', b'keep')
        self.installation_files()
        self.reset_stamps()

    def tearDown(self):
        self.temporary.cleanup()

    def git(self, *args):
        return subprocess.run(['git', *args], check=True, capture_output=True, text=True)

    def put(self, path, data):
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)

    def installation_files(self):
        self.put(self.package / 'lib/libRestFrames.a', b'fixture installed library')
        self.put(self.package / 'src/.libs/RFBase.o', b'old object')
        self.put(self.package / 'src/libRestFrames_la-RFBase.lo', b'old libtool object')

    def stamp(self, step):
        return self.build / f'restframes-prefix/src/restframes-stamp/restframes-{step}'

    def reset_stamps(self):
        for step in STEPS:
            self.put(self.stamp(step), b'completed step')
        self.put(self.build / 'CMakeFiles/restframes-complete', b'completed target')

    def snapshot(self, root):
        return {str(p.relative_to(root)): (hashlib.sha256(p.read_bytes()).hexdigest(), p.stat().st_mtime_ns)
                for p in root.rglob('*') if p.is_file()}

    def selection(self, changes=None, enabled=True, root=True, bits='ColliderBit', repository=None, tag=None):
        settings = {'PROJECT_SOURCE_DIR': self.source, 'CMAKE_BINARY_DIR': self.build,
                    'PROJECT_BINARY_DIR': self.build, 'GAMBIT_BITS': bits,
                    'WITH_RESTFRAMES': 'ON' if enabled else 'OFF',
                    'ROOT_FOUND': 'TRUE' if root else 'FALSE', 'ROOT_VERSION': '6.36.02', 'ROOT_STD': '17',
                    'ROOT_INCLUDE_DIRS': self.work / 'root/include',
                    'ROOT_LIBRARY_DIR': self.work / 'root/lib', 'ROOT_LIBRARIES': self.work / 'root/lib/libCore.a',
                    'CMAKE_SYSTEM_NAME': 'Linux', 'CMAKE_BUILD_TYPE': 'Release', 'CMAKE_SYSTEM_PROCESSOR': 'test-cpu',
                    'CMAKE_CXX_STANDARD': '17', 'CMAKE_CXX_STANDARD_REQUIRED': 'ON', 'CMAKE_CXX_EXTENSIONS': 'OFF',
                    'BACKEND_C_FLAGS': '-O2', 'BACKEND_CXX_FLAGS': '-O2 -std=c++17',
                    'MAKE_SERIAL': 'make', 'MAKE_PARALLEL': 'make;-j8',
                    'CMAKE_FIND_LIBRARY_PREFIXES': 'lib', 'CMAKE_FIND_LIBRARY_SUFFIXES': '.a;.so;.dylib'}
        for name in ('C', 'CXX', 'Fortran'):
            settings.update({f'CMAKE_{name}_COMPILER': self.work / f'compiler {name}',
                             f'CMAKE_{name}_COMPILER_ID': 'GNU', f'CMAKE_{name}_COMPILER_VERSION': '15.0'})
        settings.update(changes or {})
        contrib = (ROOT / 'cmake/contrib.cmake').read_text()
        helpers = contrib[contrib.index('macro(get_paths '):contrib.index('#contrib/preload')]
        block = contrib[contrib.index('#contrib/RestFrames;'):contrib.index('#contrib/LHEF')]
        if repository is not None:
            block = block.replace('set(_restframes_git_repository "https://github.com/crogan/RestFrames")',
                                  'set(_restframes_git_repository ' + bracket(repository) + ')')
        if tag is not None:
            block = block.replace('set(_restframes_git_tag "v${ver}")',
                                  'set(_restframes_git_tag ' + bracket(tag) + ')')
        capture = self.work / 'capture.txt'
        script = self.work / 'selection.cmake'
        script.write_text('\n'.join(['cmake_minimum_required(VERSION 3.16.3)',
            *[f'set({key} {bracket(value)})' for key, value in settings.items()],
            'set(ENV{ROOTSYS} ' + bracket(self.work / 'root') + ')',
            'set(CAPTURE_FILE ' + bracket(capture) + ')', 'file(WRITE "${CAPTURE_FILE}" "")',
            CAPTURE, r'''
function(ExternalProject_Add_Step name step)
  file(APPEND "${CAPTURE_FILE}" "STEP|${name}/${step}|${ARGN}\n")
endfunction()
''', helpers, block,
            'file(APPEND "${CAPTURE_FILE}" "REUSABLE|restframes|${_restframes_reusable}\\n")',
            'get_directory_property(watched CMAKE_CONFIGURE_DEPENDS)',
            'file(APPEND "${CAPTURE_FILE}" "RECONFIGURE|inputs|${watched}\\n")']))
        result = subprocess.run([self.cmake, '-P', str(script)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return capture.read_text()

    def request(self):
        return self.build / 'restframes-prefix/tmp/restframes-identity-request.cmake'

    def record(self):
        return self.package / '.gambit-restframes-build-identity'

    def action(self, action, success=True):
        result = subprocess.run([self.cmake, '-DGAMBIT_CONTRIB_IDENTITY_ACTION=' + action,
                                 '-DGAMBIT_CONTRIB_IDENTITY_REQUEST=' + str(self.request()), '-P', str(MODULE)],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode == 0, success, result.stdout + result.stderr)
        return result

    def installed(self):
        self.selection()
        self.action('RECORD')
        self.reset_stamps()

    def test_legacy_install_invalidates_only_build_stamps_at_selection(self):
        before = self.snapshot(self.source)
        captured = self.selection()
        self.assertIn('REUSABLE|restframes|FALSE', captured)
        self.assertIn('DEPENDEES;update;DEPENDERS;patch', captured)
        self.assertIn('STEP|restframes/record_identity|', captured)
        self.assertIn('DEPENDEES;install', captured)
        self.assertEqual(self.snapshot(self.source), before)
        for step in STEPS:
            self.assertEqual(self.stamp(step).exists(), step in ('download', 'update'))
        self.assertFalse(self.record().exists())

    def test_matching_install_and_feature_switches_preserve_files_and_stamps(self):
        self.installed()
        before = self.snapshot(self.source), self.snapshot(self.build)
        self.assertIn('REUSABLE|restframes|TRUE', self.selection())
        for changes in ({'enabled': False}, {'root': False}, {'bits': 'DarkBit'}):
            self.selection(**changes)
            self.assertIn('REUSABLE|restframes|TRUE', self.selection())
        self.assertEqual((self.snapshot(self.source), self.snapshot(self.build)), before)

    def test_fresh_stamps_do_not_reset_a_matching_source(self):
        self.installed()
        shutil.rmtree(self.build / 'restframes-prefix/src')
        self.assertIn('REUSABLE|restframes|TRUE', self.selection())
        before = self.snapshot(self.source)
        self.action('PREPARE')
        self.assertEqual(self.snapshot(self.source), before)

    def test_changed_compiler_flags_root_and_platform_reject_old_objects(self):
        self.installed()
        for changes in ({'CMAKE_BUILD_TYPE': 'Debug'}, {'BACKEND_CXX_FLAGS': '-O0 -g'},
                        {'CMAKE_CXX_COMPILER_VERSION': '16.0'}, {'ROOT_VERSION': '6.38.00'},
                        {'ROOT_INCLUDE_DIRS': '/other/root'}, {'ROOT_CXX_FLAGS': '-std=c++20'},
                        {'MACOS_DEPLOYMENT_TARGET': '13.0'}, {'CMAKE_OSX_SYSROOT': '/other/sdk'}):
            with self.subTest(changes=changes):
                self.assertIn('REUSABLE|restframes|FALSE', self.selection(changes=changes))
                self.assertFalse(self.stamp('build').exists())
                self.reset_stamps()
        root_config = self.work / 'root/bin/root-config'
        os.utime(root_config, (root_config.stat().st_atime, root_config.stat().st_mtime + 2))
        self.assertIn('REUSABLE|restframes|FALSE', self.selection())

    def test_prepare_uses_clean_tag_removes_old_objects_before_patch(self):
        self.installed()
        self.put(self.package / 'src/RFBase.cc', self.pristine + b'// old local patch\n')
        self.selection(changes={'BACKEND_CXX_FLAGS': '-O0 -g'})
        unrelated = self.snapshot(self.source / 'contrib/unrelated')
        self.action('PREPARE')
        self.assertEqual((self.package / 'src/RFBase.cc').read_bytes(), self.pristine)
        self.assertFalse((self.package / 'src/.libs/RFBase.o').exists())
        self.assertFalse((self.package / 'src/libRestFrames_la-RFBase.lo').exists())
        self.assertFalse((self.package / 'lib/libRestFrames.a').exists())
        self.assertFalse(self.record().exists())
        self.assertEqual(self.snapshot(self.source / 'contrib/unrelated'), unrelated)
        self.assertEqual(self.git('-C', str(self.package), 'describe', '--tags', '--exact-match').stdout.strip(), 'v1.0.2')
        result = subprocess.run([self.cmake, '-DRFBASE_CC=' + str(self.package / 'src/RFBase.cc'),
                                 '-P', str(ROOT / 'cmake/scripts/patch_restframes_quiet.cmake')],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn(b'RESTFRAMES_QUIET', (self.package / 'src/RFBase.cc').read_bytes())
        self.installation_files()
        self.action('RECORD')
        self.assertIn('REUSABLE|restframes|TRUE', self.selection(changes={'BACKEND_CXX_FLAGS': '-O0 -g'}))

    def test_patch_is_watched_by_direct_build_regeneration(self):
        patch = str(self.source / 'cmake/scripts/patch_restframes_quiet.cmake')
        self.assertIn('RECONFIGURE|inputs|' + patch, self.selection())
        self.assertIn('RECONFIGURE|inputs|\n', self.selection(enabled=False))

    def test_touching_unchanged_patch_keeps_install_and_step_timestamps(self):
        self.installed()
        patch = self.source / 'cmake/scripts/patch_restframes_quiet.cmake'
        before = self.snapshot(self.package), self.snapshot(self.build)
        os.utime(patch, (patch.stat().st_atime, patch.stat().st_mtime + 2))
        self.assertIn('REUSABLE|restframes|TRUE', self.selection())
        self.assertEqual((self.snapshot(self.package), self.snapshot(self.build)), before)

    def test_patch_change_requires_pristine_preparation(self):
        self.installed()
        patch = self.source / 'cmake/scripts/patch_restframes_quiet.cmake'
        patch.write_bytes(patch.read_bytes() + b'\n# changed patch input\n')
        self.assertIn('REUSABLE|restframes|FALSE', self.selection())
        self.action('PREPARE')
        self.assertEqual((self.package / 'src/RFBase.cc').read_bytes(), self.pristine)
        self.assertFalse(self.record().exists())

    def test_missing_library_or_header_cannot_reuse_or_record(self):
        self.installed()
        for name in ('lib/libRestFrames.a', 'inc/RestFrames/RestFrames.hh'):
            path = self.package / name
            content = path.read_bytes()
            path.unlink()
            self.assertIn('REUSABLE|restframes|FALSE', self.selection())
            self.record().unlink(missing_ok=True)
            self.action('RECORD', success=False)
            self.assertFalse(self.record().exists())
            self.put(path, content)
            self.action('RECORD')

    def test_failed_pristine_checkout_keeps_existing_install(self):
        self.installed()
        self.selection(changes={'BACKEND_CXX_FLAGS': '-changed'})
        with self.request().open('a') as stream:
            stream.write('\nset(CONTRIB_GIT_TAG missing-tag)\nset(CONTRIB_GIT_REPOSITORY ' +
                         bracket(self.work / 'nonexistent-local-repository') + ')\n')
        before = self.snapshot(self.source)
        self.action('PREPARE', success=False)
        self.assertEqual(self.snapshot(self.source), before)

    def test_tag_change_invalidates_identity_with_unchanged_flags(self):
        self.installed()
        self.git('-C', str(self.package), 'tag', 'fixture-other-tag')
        original = self.record().read_bytes()
        self.assertIn('REUSABLE|restframes|FALSE', self.selection(tag='fixture-other-tag'))
        self.assertNotEqual((self.build / 'restframes-prefix/tmp/restframes-identity.txt').read_bytes(), original)
        self.action('PREPARE')
        self.assertFalse((self.package / 'src/.libs/RFBase.o').exists())

    def test_repository_change_uses_requested_source_instead_of_old_checkout(self):
        self.installed()
        alternate = self.work / 'alternate upstream'
        self.git('clone', str(self.package), str(alternate))
        changed = self.pristine + b'// alternate upstream implementation\n'
        self.put(alternate / 'src/RFBase.cc', changed)
        self.git('-C', str(alternate), 'add', 'src/RFBase.cc')
        self.git('-C', str(alternate), '-c', 'user.name=Fixture', '-c',
                 'user.email=fixture@example.invalid', '-c', 'commit.gpgsign=false',
                 '-c', 'core.hooksPath=/dev/null', 'commit', '-qm', 'different upstream source')
        self.git('-C', str(alternate), 'tag', '-f', 'v1.0.2')
        original = self.record().read_bytes()
        self.assertIn('REUSABLE|restframes|FALSE', self.selection(repository=alternate))
        self.assertNotEqual((self.build / 'restframes-prefix/tmp/restframes-identity.txt').read_bytes(), original)
        self.action('PREPARE')
        self.assertEqual((self.package / 'src/RFBase.cc').read_bytes(), changed)
        self.assertFalse((self.package / 'src/.libs/RFBase.o').exists())
        self.assertEqual(self.git('-C', str(self.package), 'remote', 'get-url', 'origin').stdout.strip(), str(alternate))
        self.installation_files()
        self.action('RECORD')
        self.assertIn('REUSABLE|restframes|TRUE', self.selection(repository=alternate))

    def test_source_drop_can_reconstruct_from_a_local_upstream(self):
        upstream = self.work / 'upstream'
        self.git('clone', '--bare', str(self.package), str(upstream))
        shutil.rmtree(self.package / '.git')
        self.selection()
        with self.request().open('a') as stream:
            stream.write('\nset(CONTRIB_GIT_REPOSITORY ' + bracket(upstream) + ')\n')
        self.action('PREPARE')
        self.assertTrue((self.package / '.git').exists())
        self.assertFalse((self.package / 'src/.libs/RFBase.o').exists())

    def test_prepare_rejects_foreign_source_paths(self):
        self.selection()
        foreign = self.work / 'outside/keep'
        self.put(foreign, b'keep')
        with self.request().open('a') as stream:
            stream.write('\nset(CONTRIB_SOURCE_DIR ' + bracket(foreign.parent) + ')\n')
        self.action('PREPARE', success=False)
        self.assertEqual(foreign.read_bytes(), b'keep')


if __name__ == '__main__':
    unittest.main(verbosity=2)
