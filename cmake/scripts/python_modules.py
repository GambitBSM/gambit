"""Import requested modules in one process and emit a small line protocol.

Run with -B; no persistent probe files are created. Flush each result so a later
crash/timeout does not discard earlier checks. Module output is suppressed.
"""
import importlib
import os
import re
import sys


class QuietImport:
    def __enter__(self):
        sys.stdout.flush()
        sys.stderr.flush()
        self.saved = [os.dup(1), os.dup(2)]
        self.null = os.open(os.devnull, os.O_WRONLY)
        os.dup2(self.null, 1)
        os.dup2(self.null, 2)

    def __exit__(self, *unused):
        sys.stdout.flush()
        sys.stderr.flush()
        for descriptor, saved in zip((1, 2), self.saved):
            os.dup2(saved, descriptor)
            os.close(saved)
        os.close(self.null)


def probe(name):
    found, hdf5_version, metadata_error = False, "-", False
    with QuietImport():
        try:
            module = importlib.import_module(name)
            found = True
        except (Exception, SystemExit):
            return False, "-", False
        if name == "h5py":
            try:
                hdf5_version = str(module.version.hdf5_version)
                if not re.fullmatch(r"[0-9]+(?:\.[0-9]+)+", hdf5_version):
                    raise ValueError("Invalid HDF5 version")
            except Exception:
                hdf5_version = "-"
                metadata_error = True
    return found, hdf5_version, metadata_error


if __name__ == "__main__":
    # Match the old `python -c "import ..."` search path: the working directory,
    # rather than this helper's cmake/scripts directory, is the first entry.
    sys.path[0] = os.getcwd()
    print("GAMBIT_PYTHON_MODULES_V1", flush=True)
    for name in sys.argv[1:]:
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*(?:\.[A-Za-z_][A-Za-z0-9_]*)*", name):
            raise SystemExit("Invalid module name: " + name)
        found, hdf5_version, metadata_error = probe(name)
        print("%s\t%d\t%s\t%d" % (name, found, hdf5_version, metadata_error), flush=True)
