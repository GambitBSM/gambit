#!/usr/bin/env python3
"""Check cached source extraction without downloads, configure or compilation."""

import io
import os
from pathlib import Path
import shutil
import stat
import subprocess
import tarfile
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
DOWNLOADER = ROOT / "cmake/scripts/safe_dl.sh"


class SourceDownloadTests(unittest.TestCase):
    def setUp(self):
        self.cmake = shutil.which("cmake")
        if not self.cmake or not shutil.which("sh"):
            self.skipTest("Requires CMake and sh; no downloads performed")
        temporary = tempfile.TemporaryDirectory(prefix="gambit-source-download-")
        self.addCleanup(temporary.cleanup)
        self.work = Path(temporary.name)
        self.cache = self.work / "cache"
        self.cache.mkdir()
        self.destination = self.work / "installed sources"
        # Deliberately write generated files before their inputs in the archive.
        # Copy order must never replace the package's dependency timestamps.
        self.files = {
            "aclocal.m4": (b"generated macros\n", 1_600_000_020, 0o644),
            "configure": (b"#!/bin/sh\nexit 0\n", 1_600_000_030, 0o755),
            "Makefile.in": (b"generated makefile\n", 1_600_000_030, 0o644),
            "m4/local.m4": (b"input macros\n", 1_600_000_000, 0o644),
            "configure.ac": (b"input configure\n", 1_600_000_010, 0o644),
            ".hidden": (b"hidden source\n", 1_600_000_000, 0o644),
        }

    def archive(self, container):
        prefix = "fixture-1.0/" if container else ""
        with tarfile.open(self.cache / "fixture_1.0.tar.gz", "w:gz") as archive:
            for name, (content, timestamp, mode) in self.files.items():
                member = tarfile.TarInfo(prefix + name)
                member.size, member.mtime, member.mode = len(content), timestamp, mode
                archive.addfile(member, io.BytesIO(content))
            link = tarfile.TarInfo(prefix + "configure-link")
            link.type, link.linkname = tarfile.SYMTYPE, "configure"
            archive.addfile(link)

    def extract(self, retain=False):
        command = ["sh", str(DOWNLOADER), str(ROOT), str(self.cache), self.cmake,
                   "", "https://invalid.example/fixture.tar.gz", "none",
                   str(self.destination), "fixture", "1.0"]
        if retain:
            command.append("retain container folder")
        result = subprocess.run(command, cwd=self.work, text=True,
                                capture_output=True, timeout=30)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def check_sources(self, directory):
        for name, (content, timestamp, mode) in self.files.items():
            with self.subTest(file=name):
                path = directory / name
                self.assertEqual(path.read_bytes(), content)
                self.assertEqual(path.stat().st_mtime_ns, timestamp * 1_000_000_000)
                self.assertEqual(stat.S_IMODE(path.stat().st_mode), mode)
        self.assertTrue((directory / "configure-link").is_symlink())
        self.assertEqual(os.readlink(directory / "configure-link"), "configure")

    def test_container_is_removed_and_timestamps_are_preserved(self):
        self.archive(container=True)
        self.extract()
        self.check_sources(self.destination)
        self.assertFalse((self.destination / "fixture-1.0").exists())

    def test_flat_archive_preserves_timestamps(self):
        self.archive(container=False)
        self.extract()
        self.check_sources(self.destination)

    def test_retain_container_folder(self):
        self.archive(container=True)
        self.extract(retain=True)
        self.check_sources(self.destination / "fixture-1.0")

    def test_existing_installation_is_retained_and_source_times_are_restored(self):
        self.archive(container=True)
        product = self.destination / "local/lib/kept.so"
        product.parent.mkdir(parents=True)
        product.write_bytes(b"existing installation")
        before = product.stat().st_mtime_ns
        self.extract()
        # Model a source copied by the former timestamp-losing downloader.
        os.utime(self.destination / "aclocal.m4", (1_700_000_000, 1_700_000_000))
        self.extract()
        self.check_sources(self.destination)
        self.assertEqual(product.read_bytes(), b"existing installation")
        self.assertEqual(product.stat().st_mtime_ns, before)


if __name__ == "__main__":
    unittest.main(verbosity=2)
