#!/usr/bin/env python3
"""Check the Rivet installation patch on pristine files without building anything.

Uses the existing download cache and a disposable directory. Never configures,
compiles, imports Rivet/Contur, or modifies an installed backend.
"""

from pathlib import Path
import shutil
import subprocess
import tarfile
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
PATCH = ROOT / "Backends/patches/rivet/4.1.0/patch_rivet_4.1.0.dif"
ARCHIVE = ROOT / "Backends/downloaded/rivet_4.1.0.tar.gz"


class RivetInstallationPatch(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not ARCHIVE.is_file() or not shutil.which("patch"):
            raise unittest.SkipTest("Requires cached rivet_4.1.0.tar.gz and patch; no downloads performed")
        temporary = tempfile.TemporaryDirectory(prefix="rivet-installation-patch-")
        cls.addClassCleanup(temporary.cleanup)
        cls.directory = Path(temporary.name)
        targets = {
            line.split()[1].split("/", 1)[1]
            for line in PATCH.read_text().splitlines() if line.startswith("--- ")
        }
        with tarfile.open(ARCHIVE) as archive:
            members = {
                member.name.split("/", 1)[1]: member
                for member in archive.getmembers()
                if member.isfile() and "/" in member.name
            }
            for target in targets:
                path = cls.directory / target
                if Path(target).is_absolute() or ".." in Path(target).parts:
                    raise ValueError("Unexpected patch target: " + target)
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(archive.extractfile(members[target]).read())
        result = subprocess.run(
            ["patch", "--batch", "--forward", "-p1", "-i", str(PATCH)],
            cwd=cls.directory, text=True, capture_output=True, check=False,
        )
        if result.returncode != 0:
            raise AssertionError(result.stdout + result.stderr)

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
