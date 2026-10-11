#!/usr/bin/env python3
"""Script-only validation-cache regression checks; never invokes a compiler.

Native Check* modules are replaced with probes that retain CMake's DEFINED and
CACHE semantics.  Both the production validator and optional HDF5 gate run.
"""
from pathlib import Path
import os
import shutil
import subprocess
import tempfile
import unittest

CMAKE_DIR = Path(__file__).resolve().parents[1]
CMAKE = shutil.which("cmake")
PROBES = (
    "CBS_VALIDATION_C_COMPILE_LINK", "CBS_VALIDATION_CXX_COMPILE_LINK",
    "_cbs_fortran_free_form_compile_link", "_cbs_dynamic_lookup",
    "_cbs_python_c_api_compile_link", "_cbs_boost", "_cbs_hdf5", "_cbs_sqlite3",
)

STUBS = r'''
function(execute_process)
  message(FATAL_ERROR "A script-only test attempted execute_process")
endfunction()
function(try_compile)
  message(FATAL_ERROR "A script-only test attempted try_compile")
endfunction()
function(try_run)
  message(FATAL_ERROR "A script-only test attempted try_run")
endfunction()
function(_fixture_probe result)
  if(NOT DEFINED ${result})
    get_property(_count GLOBAL PROPERTY "calls_${result}")
    if(NOT _count)
      set(_count 0)
    endif()
    math(EXPR _count "${_count} + 1")
    set_property(GLOBAL PROPERTY "calls_${result}" "${_count}")
    if(_fixture_fail STREQUAL result)
      set(${result} "" CACHE INTERNAL "Synthetic failure" FORCE)
    else()
      set(${result} 1 CACHE INTERNAL "Synthetic success" FORCE)
    endif()
  endif()
endfunction()
function(check_c_source_compiles source result)
  _fixture_probe("${result}")
endfunction()
function(check_cxx_source_compiles source result)
  _fixture_probe("${result}")
endfunction()
function(check_fortran_source_compiles source result)
  _fixture_probe("${result}")
endfunction()
function(check_linker_flag language flag result)
  _fixture_probe("${result}")
endfunction()
function(expect_calls result expected)
  get_property(_actual GLOBAL PROPERTY "calls_${result}")
  if(NOT _actual)
    set(_actual 0)
  endif()
  if(NOT "${_actual}" STREQUAL "${expected}")
    message(FATAL_ERROR "${result}: expected ${expected} probes, got ${_actual}")
  endif()
endfunction()
function(expect_all expected)
  foreach(_result IN LISTS _fixture_results)
    expect_calls("${_result}" "${expected}")
  endforeach()
endfunction()
function(expect_true result)
  if(NOT ${result})
    message(FATAL_ERROR "${result}: expected success")
  endif()
endfunction()
function(expect_false result)
  if(${result})
    message(FATAL_ERROR "${result}: expected failure")
  endif()
endfunction()
'''


@unittest.skipUnless(CMAKE, "cmake executable is required")
class ValidationCacheTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="gambit validation ")
        self.root = Path(self.temp.name)
        self.addCleanup(self.temp.cleanup)
        for package, headers in {
            "python": ("Python.h", "pyconfig.h", "patchlevel.h", "pylifecycle.h"),
            "boost": ("boost/version.hpp",),
            "hdf5": ("hdf5.h", "H5public.h", "H5pubconf.h", "H5Ppublic.h"),
            "sqlite": ("sqlite3.h",),
        }.items():
            for header in headers:
                path = self.root / package / "include" / header
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text("original\n")
            (self.root / package / "library").write_text("library\n")
        (self.root / "compiler").write_text("compiler\n")
        (self.root / "python" / "executable").write_text("python\n")
        modules = self.root / "modules"
        modules.mkdir()
        for name in ("CheckCSourceCompiles", "CheckCXXSourceCompiles",
                     "CheckFortranSourceCompiles", "CheckLinkerFlag"):
            (modules / f"{name}.cmake").write_text("# Stub installed by this fixture.\n")
        self.prefix = f'''cmake_minimum_required(VERSION 3.16)
set(_fixture_root [==[{self.root}]==])
set(CMAKE_MODULE_PATH "${{_fixture_root}}/modules")
{STUBS}
set(_fixture_results "{';'.join(PROBES)}")
set(CBS_PRESET_BUILD TRUE)
set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_COMPILER "${{_fixture_root}}/compiler")
set(CMAKE_CXX_COMPILER "${{_fixture_root}}/compiler")
set(CMAKE_Fortran_COMPILER "${{_fixture_root}}/compiler")
set(CMAKE_C_FLAGS "-O2")
set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_Fortran_FLAGS "-O2")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(GAMBIT_CXX_STANDARD 17)
set(GAMBIT_OPENMP_FOUND TRUE)
set(Python3_FOUND TRUE)
set(Python3_Development_FOUND TRUE)
set(Python3_INCLUDE_DIRS "${{_fixture_root}}/python/include")
set(Python3_LIBRARIES "${{_fixture_root}}/python/library")
set(Python3_EXECUTABLE "${{_fixture_root}}/python/executable")
set(Python3_VERSION 3.13)
set(Boost_FOUND TRUE)
set(Boost_INCLUDE_DIR "${{_fixture_root}}/boost/include")
set(Boost_VERSION 108900)
set(HDF5_FOUND TRUE)
set(HDF5_INCLUDE_DIRS "${{_fixture_root}}/hdf5/include")
set(HDF5_LIBRARIES "${{_fixture_root}}/hdf5/library")
set(HDF5_VERSION 1.14)
set(SQLite3_FOUND TRUE)
set(SQLite3_INCLUDE_DIRS "${{_fixture_root}}/sqlite/include")
set(SQLite3_LIBRARIES "${{_fixture_root}}/sqlite/library")
set(SQLite3_VERSION 3.50)
include([==[{CMAKE_DIR / 'presets' / 'CBSValidation.cmake'}]==])
'''

    def run_script(self, body):
        script = self.root / "test.cmake"
        script.write_text(self.prefix + body)
        completed = subprocess.run([CMAKE, "-P", str(script)], text=True,
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                   env=os.environ.copy())
        self.assertEqual(completed.returncode, 0, completed.stdout)

    def test_fortran_platform_flags_refresh_only_fortran_probe(self):
        self.run_script('''
cbs_validate_environment()
expect_all(1)
set(CMAKE_Fortran_SYSROOT_FLAG "-isysroot")
cbs_validate_environment()
expect_calls(_cbs_fortran_free_form_compile_link 2)
expect_calls(CBS_VALIDATION_C_COMPILE_LINK 1)
expect_calls(CBS_VALIDATION_CXX_COMPILE_LINK 1)
set(CMAKE_Fortran_OSX_DEPLOYMENT_TARGET_FLAG "-mmacosx-version-min=")
cbs_validate_environment()
expect_calls(_cbs_fortran_free_form_compile_link 3)
expect_calls(CBS_VALIDATION_CXX_COMPILE_LINK 1)
''')

    def test_unchanged_inputs_reuse_success_and_failure(self):
        self.run_script('''
set(_fixture_fail _cbs_sqlite3)
cbs_validate_environment()
expect_all(1)
expect_false(CBS_VALIDATION_SQLITE3)
cbs_validate_environment()
expect_all(1)
expect_false(CBS_VALIDATION_SQLITE3)
if("sqlite3" IN_LIST CBS_VALIDATION_REQUIRED_FAILURES)
  message(FATAL_ERROR "SQLite became a required dependency")
endif()
''')

    def test_dependency_changes_are_local_and_recover_failures(self):
        for result, public, change in (
            ("_cbs_python_c_api_compile_link", "PYTHON_DEVELOPMENT", 'set(Python3_VERSION 3.14)'),
            ("_cbs_boost", "BOOST", 'set(Boost_VERSION 109000)'),
            ("_cbs_hdf5", "HDF5", 'set(HDF5_VERSION 1.15)'),
            ("_cbs_sqlite3", "SQLITE3", 'set(SQLite3_VERSION 3.51)'),
        ):
            with self.subTest(result=result):
                self.run_script(f'''
set(_fixture_fail {result})
cbs_validate_environment()
expect_false(CBS_VALIDATION_{public})
set(_fixture_fail "")
{change}
cbs_validate_environment()
expect_true(CBS_VALIDATION_{public})
foreach(_result IN LISTS _fixture_results)
  if(_result STREQUAL "{result}")
    expect_calls("${{_result}}" 2)
  else()
    expect_calls("${{_result}}" 1)
  endif()
endforeach()
cbs_validate_environment()
expect_calls({result} 2)
''')

    def test_absent_then_found_cannot_resurrect_cached_success(self):
        self.run_script('''
cbs_validate_environment()
set(Boost_FOUND FALSE)
set(Python3_INCLUDE_DIRS "")
set(HDF5_FOUND FALSE)
set(SQLite3_FOUND FALSE)
cbs_validate_environment()
expect_all(1)
expect_false(CBS_VALIDATION_BOOST)
expect_false(CBS_VALIDATION_PYTHON_DEVELOPMENT)
expect_false(CBS_VALIDATION_HDF5)
expect_false(CBS_VALIDATION_SQLITE3)
set(Boost_FOUND TRUE)
set(Python3_INCLUDE_DIRS "${_fixture_root}/python/include")
set(HDF5_FOUND TRUE)
set(SQLite3_FOUND TRUE)
set(_fixture_fail _cbs_boost)
cbs_validate_environment()
expect_false(CBS_VALIDATION_BOOST)
foreach(_result _cbs_boost _cbs_python_c_api_compile_link _cbs_hdf5 _cbs_sqlite3)
  expect_calls("${_result}" 2)
endforeach()
expect_calls(CBS_VALIDATION_C_COMPILE_LINK 1)
''')

    def test_header_content_missing_and_repair(self):
        self.run_script('''
cbs_validate_environment()
file(WRITE "${_fixture_root}/python/include/Python.h" "modified\\n")
cbs_validate_environment()
expect_calls(_cbs_python_c_api_compile_link 2)
expect_calls(_cbs_boost 1)
file(REMOVE "${_fixture_root}/python/include/Python.h")
set(_fixture_fail _cbs_python_c_api_compile_link)
cbs_validate_environment()
expect_false(CBS_VALIDATION_PYTHON_DEVELOPMENT)
expect_calls(_cbs_python_c_api_compile_link 3)
file(WRITE "${_fixture_root}/python/include/Python.h" "repaired\\n")
set(_fixture_fail "")
cbs_validate_environment()
expect_true(CBS_VALIDATION_PYTHON_DEVELOPMENT)
expect_calls(_cbs_python_c_api_compile_link 4)
''')

    def test_same_metadata_header_and_toolchain_edits(self):
        for target, setup in (
            ("python/include/Python.h", 'set(CMAKE_REQUIRED_INCLUDES "${_fixture_root}/python/include")'),
            ("toolchain.cmake", 'set(CMAKE_TOOLCHAIN_FILE "${_fixture_root}/toolchain.cmake")'),
        ):
            with self.subTest(target=target):
                path = self.root / target
                path.write_text("original\n")
                before = path.stat()
                script = setup + '''
gambit_check_signature(_signature C "header/toolchain fixture" HEADERS Python.h)
file(WRITE "${_fixture_root}/signature" "${_signature}")
'''
                self.run_script(script)
                old_signature = (self.root / "signature").read_text()
                path.write_text("modified\n")
                os.utime(path, ns=(before.st_atime_ns, before.st_mtime_ns))
                self.assertEqual(path.stat().st_size, before.st_size)
                self.assertEqual(path.stat().st_mtime_ns, before.st_mtime_ns)
                self.run_script(script)
                self.assertNotEqual((self.root / "signature").read_text(), old_signature)

    def test_library_and_python_executable_metadata(self):
        self.run_script('''
cbs_validate_environment()
file(APPEND "${_fixture_root}/python/library" "upgraded")
cbs_validate_environment()
expect_calls(_cbs_python_c_api_compile_link 2)
file(APPEND "${_fixture_root}/python/executable" "upgraded")
cbs_validate_environment()
expect_calls(_cbs_python_c_api_compile_link 3)
expect_calls(_cbs_hdf5 1)
''')

    def test_symlink_retarget(self):
        for version in ("first", "second"):
            (self.root / version).mkdir()
            (self.root / version / "Python.h").write_text("original\n")
        (self.root / "selected").symlink_to(self.root / "first", target_is_directory=True)
        self.run_script('''
set(Python3_INCLUDE_DIRS "${_fixture_root}/selected")
cbs_validate_environment()
file(REMOVE "${_fixture_root}/selected")
file(CREATE_LINK "${_fixture_root}/second" "${_fixture_root}/selected" SYMBOLIC)
cbs_validate_environment()
expect_calls(_cbs_python_c_api_compile_link 2)
expect_calls(_cbs_hdf5 1)
''')

    def test_language_mode_and_normal_variable_invalidation(self):
        self.run_script('''
set(_fixture_fail CBS_VALIDATION_CXX_COMPILE_LINK)
cbs_validate_environment()
expect_false(CBS_VALIDATION_CXX_COMPILE_LINK)
set(_fixture_fail "")
set(GAMBIT_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
cbs_validate_environment()
expect_true(CBS_VALIDATION_CXX_COMPILE_LINK)
expect_calls(CBS_VALIDATION_CXX_COMPILE_LINK 2)
expect_calls(_cbs_boost 2)
expect_calls(CBS_VALIDATION_C_COMPILE_LINK 1)
set(CMAKE_C_FLAGS "-O0")
cbs_validate_environment()
expect_calls(CBS_VALIDATION_C_COMPILE_LINK 2)
expect_calls(_cbs_python_c_api_compile_link 2)
expect_calls(_cbs_fortran_free_form_compile_link 1)
set(CMAKE_Fortran_FLAGS "-O0")
cbs_validate_environment()
expect_calls(_cbs_fortran_free_form_compile_link 2)
''')

    def test_common_link_platform_and_required_inputs(self):
        # Each changed input must invalidate cached PASS and cached FAIL alike.
        changes = (
            'set(CMAKE_EXE_LINKER_FLAGS "-Wl,new")',
            'set(CMAKE_CXX_FLAGS_RELEASE "-O1")',
            'set(CMAKE_CXX_FLAGS_DEBUG "-O1")',
            'set(CMAKE_CONFIGURATION_TYPES "Debug;Site")\nset(CMAKE_CXX_FLAGS_SITE "-O1")',
            'set(CMAKE_CXX_LINK_FLAGS "-Wl,new")',
            'set(CMAKE_CXX_LINK_FLAGS_RELEASE "-Wl,new")',
            'set(CMAKE_REQUIRED_DEFINITIONS "-DNEW=1")',
            'set(CMAKE_REQUIRED_LINK_OPTIONS "-Wl,new")',
            'set(CMAKE_REQUIRED_LINK_DIRECTORIES "/other/libs")',
            'set(CMAKE_TRY_COMPILE_CONFIGURATION Debug)',
            'set(CMAKE_OSX_SYSROOT "/other/sdk")',
            'set(CMAKE_OSX_DEPLOYMENT_TARGET 27.1)',
            'set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")',
            'set(CMAKE_TRY_COMPILE_PLATFORM_VARIABLES SITE_ABI)\nset(SITE_ABI new)',
        )
        for change in changes:
            with self.subTest(change=change):
                self.run_script(f'''
cbs_validate_environment()
set(_fixture_fail CBS_VALIDATION_CXX_COMPILE_LINK)
{change}
cbs_validate_environment()
expect_calls(CBS_VALIDATION_CXX_COMPILE_LINK 2)
expect_false(CBS_VALIDATION_CXX_COMPILE_LINK)
cbs_validate_environment()
expect_calls(CBS_VALIDATION_CXX_COMPILE_LINK 2)
''')

    def test_compiler_file_change_invalidates_all(self):
        self.run_script('''
cbs_validate_environment()
file(APPEND "${_fixture_root}/compiler" "upgraded")
cbs_validate_environment()
expect_all(2)
''')

    def test_toolchain_file_content_and_manual_reset(self):
        self.run_script('''
file(WRITE "${_fixture_root}/toolchain.cmake" "initial")
set(CMAKE_TOOLCHAIN_FILE "${_fixture_root}/toolchain.cmake")
cbs_validate_environment()
file(APPEND "${_fixture_root}/toolchain.cmake" "changed")
cbs_validate_environment()
expect_all(2)
get_cmake_property(_cache_variables CACHE_VARIABLES)
foreach(_variable IN LISTS _cache_variables)
  if(_variable MATCHES "^GAMBIT_CHECK_CACHE_")
    unset("${_variable}" CACHE)
  endif()
endforeach()
cbs_validate_environment()
expect_all(3)
cbs_validate_environment()
expect_all(3)
''')

    def test_legacy_results_without_signatures_rechecked_once(self):
        self.run_script('''
foreach(_result IN LISTS _fixture_results)
  set(${_result} "" CACHE INTERNAL "Legacy failed probe")
  set(${_result} "")
endforeach()
set(CBS_VALIDATION_CXX_SIGNATURE old CACHE INTERNAL "Legacy key")
cbs_validate_environment()
expect_all(1)
expect_true(CBS_VALIDATION_C_COMPILE_LINK)
expect_true(CBS_VALIDATION_CXX_COMPILE_LINK)
if(DEFINED CBS_VALIDATION_CXX_SIGNATURE)
  message(FATAL_ERROR "Legacy C++ key was retained")
endif()
cbs_validate_environment()
expect_all(1)
''')

    def test_non_macos_skips_dynamic_lookup(self):
        self.run_script('''
set(CMAKE_SYSTEM_NAME Linux)
cbs_validate_environment()
expect_calls(_cbs_dynamic_lookup 0)
expect_true(CBS_VALIDATION_DYNAMIC_LOOKUP)
expect_false(CBS_VALIDATION_DYNAMIC_LOOKUP_REQUIRED)
foreach(_result IN LISTS _fixture_results)
  if(NOT _result STREQUAL "_cbs_dynamic_lookup")
    expect_calls("${_result}" 1)
  endif()
endforeach()
cbs_validate_environment()
expect_calls(CBS_VALIDATION_CXX_COMPILE_LINK 1)
''')

    def test_reuse_across_script_processes(self):
        state = self.root / "saved_cache.cmake"
        self.run_script('''
cbs_validate_environment()
get_cmake_property(_cache_variables CACHE_VARIABLES)
file(WRITE "${_fixture_root}/saved_cache.cmake" "")
foreach(_variable IN LISTS _cache_variables)
  if(_variable MATCHES "^GAMBIT_CHECK_CACHE_" OR _variable IN_LIST _fixture_results)
    file(APPEND "${_fixture_root}/saved_cache.cmake"
      "set(${_variable} [==[${${_variable}}]==] CACHE INTERNAL fixture)\\n")
  endif()
endforeach()
''')
        self.assertTrue(state.exists())
        self.run_script('''
include("${_fixture_root}/saved_cache.cmake")
cbs_validate_environment()
expect_all(0)
set(Python3_VERSION 3.14)
cbs_validate_environment()
expect_calls(_cbs_python_c_api_compile_link 1)
expect_calls(CBS_VALIDATION_C_COMPILE_LINK 0)
''')

    def test_required_state_restored(self):
        self.run_script('''
set(CMAKE_REQUIRED_FLAGS "-fixture-flag")
set(CMAKE_REQUIRED_INCLUDES "fixture/includes")
set(CMAKE_REQUIRED_LIBRARIES "fixture-library")
set(CMAKE_REQUIRED_LINK_OPTIONS "fixture-link-option")
set(CMAKE_REQUIRED_QUIET FALSE)
cbs_validate_environment()
if(NOT CMAKE_REQUIRED_FLAGS STREQUAL "-fixture-flag" OR
   NOT CMAKE_REQUIRED_INCLUDES STREQUAL "fixture/includes" OR
   NOT CMAKE_REQUIRED_LIBRARIES STREQUAL "fixture-library" OR
   NOT CMAKE_REQUIRED_LINK_OPTIONS STREQUAL "fixture-link-option" OR
   CMAKE_REQUIRED_QUIET)
  message(FATAL_ERROR "Required check state leaked into the caller")
endif()
cbs_validate_environment()
expect_all(1)
''')

    def test_hdf5_failure_recovers_before_feature_selection(self):
        source = (CMAKE_DIR / "optional.cmake").read_text()
        block = source[source.index("# Check for HDF5 libraries."):
                       source.index("# Check for SQLite libraries")]
        block = block.replace('${CMAKE_CURRENT_LIST_DIR}/ValidationCache.cmake',
                              str(CMAKE_DIR / "ValidationCache.cmake"))
        gate = self.root / "hdf5_gate.cmake"
        gate.write_text(block)
        self.run_script('''
function(find_package)
  set(HDF5_FOUND "${_fixture_hdf5_found}" PARENT_SCOPE)
endfunction()
function(include_directories)
endfunction()
set(_fixture_hdf5_found TRUE)
set(_fixture_fail GAMBIT_HDF5_USABLE)
include("${_fixture_root}/hdf5_gate.cmake")
expect_false(HDF5_FOUND)
expect_calls(GAMBIT_HDF5_USABLE 1)
include("${_fixture_root}/hdf5_gate.cmake")
expect_calls(GAMBIT_HDF5_USABLE 1)
file(APPEND "${_fixture_root}/hdf5/include/H5Ppublic.h" "repaired")
set(_fixture_fail "")
include("${_fixture_root}/hdf5_gate.cmake")
expect_true(HDF5_FOUND)
expect_calls(GAMBIT_HDF5_USABLE 2)
include("${_fixture_root}/hdf5_gate.cmake")
expect_calls(GAMBIT_HDF5_USABLE 2)
set(_fixture_hdf5_found FALSE)
include("${_fixture_root}/hdf5_gate.cmake")
set(_fixture_hdf5_found TRUE)
set(_fixture_fail GAMBIT_HDF5_USABLE)
include("${_fixture_root}/hdf5_gate.cmake")
expect_false(HDF5_FOUND)
expect_calls(GAMBIT_HDF5_USABLE 3)
''')


if __name__ == "__main__":
    unittest.main(verbosity=2)
