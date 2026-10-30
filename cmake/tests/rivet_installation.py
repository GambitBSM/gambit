#!/usr/bin/env python3
"""Check the Rivet installation patch on pristine files without building anything.

Uses the existing download cache and a disposable directory. Never configures,
compiles, imports Rivet/Contur, or modifies an installed backend.
"""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
PATCH = ROOT / "Backends/patches/rivet/4.1.0/patch_rivet_4.1.0.dif"
ARCHIVE = ROOT / "Backends/downloaded/rivet_4.1.0.tar.gz"


class RivetInstallationPatch(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cmake = shutil.which("cmake")
        if (not ARCHIVE.is_file() or not cmake or not shutil.which("patch")
                or not shutil.which("sh")):
            raise unittest.SkipTest(
                "Requires cached rivet_4.1.0.tar.gz, CMake, sh and patch; no downloads performed")
        temporary = tempfile.TemporaryDirectory(prefix="rivet-installation-patch-")
        cls.addClassCleanup(temporary.cleanup)
        cls.directory = Path(temporary.name) / "rivet"
        # Use the real cached-download path, including its staging/copy step.
        # Checking a direct tar extraction would miss timestamp regressions.
        result = subprocess.run(
            ["sh", str(ROOT / "cmake/scripts/safe_dl.sh"), str(ROOT), str(ARCHIVE.parent),
             cmake, "", "https://invalid.example/Rivet-4.1.0.tar.gz",
             "9d33e74b9d64053a9e317ec437c71ff0", str(cls.directory), "rivet", "4.1.0"],
            cwd=temporary.name, text=True, capture_output=True, timeout=60,
        )
        if result.returncode != 0:
            raise AssertionError(result.stdout + result.stderr)
        result = subprocess.run(
            ["patch", "--batch", "--forward", "-p1", "-i", str(PATCH)],
            cwd=cls.directory, text=True, capture_output=True, check=False,
        )
        if result.returncode != 0:
            raise AssertionError(result.stdout + result.stderr)

    def test_patched_release_does_not_require_autotools_regeneration(self):
        inputs = [self.directory / "configure.ac", *(self.directory / "m4").glob("*.m4")]
        newest_input = max(path.stat().st_mtime_ns for path in inputs)
        aclocal_time = (self.directory / "aclocal.m4").stat().st_mtime_ns
        self.assertGreaterEqual(aclocal_time, newest_input)
        self.assertGreaterEqual((self.directory / "configure").stat().st_mtime_ns, aclocal_time)
        header = self.directory / "include/Rivet/Config/DummyConfig.hh.in"
        self.assertGreaterEqual(header.stat().st_mtime_ns, aclocal_time)
        for makefile in self.directory.rglob("Makefile.in"):
            with self.subTest(makefile=str(makefile.relative_to(self.directory))):
                self.assertGreaterEqual(makefile.stat().st_mtime_ns, aclocal_time)
                self.assertGreaterEqual(makefile.stat().st_mtime_ns,
                                        makefile.with_suffix(".am").stat().st_mtime_ns)

    def test_one_installed_library_before_plugins_and_python(self):
        text = (self.directory / "Makefile.in").read_text()
        recipe = text.split("libRivet.so:\n", 1)[1].split(".SUFFIXES:", 1)[0]
        install = recipe.index("install-libLTLIBRARIES")
        self.assertLess(install, recipe.index("cd ${top_builddir}/analyses"))
        self.assertLess(install, recipe.index("cd ${top_builddir}/pyext"))
        self.assertIn('ln -sf libRivet.dylib "${libdir}/libRivet.so"', recipe)
        self.assertNotIn("cp ${top_builddir}/src/.libs/libRivet", recipe)

    def test_macos_rewrites_installed_extension_not_build_copy(self):
        text = (self.directory / "pyext/Makefile.in").read_text()
        recipe = text.split(
            "@ENABLE_PYEXT_TRUE@@WITH_OSX_TRUE@install-exec-local: build/rivet/core.so", 1
        )[1].split("@ENABLE_PYEXT_TRUE@@WITH_OSX_FALSE@build/rivet/core.so", 1)[0]
        self.assertLess(recipe.index("cp -r"), recipe.index("install_name_tool -change"))
        self.assertIn("$(DESTDIR)$(RIVET_PYTHONPATH)/rivet/core.so", recipe)
        self.assertNotIn("$(abs_builddir)/build/rivet/core.so", recipe)
        self.assertIn("$(libdir)/libRivet.dylib", recipe)


if __name__ == "__main__":
    unittest.main(verbosity=2)
