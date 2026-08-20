"""Print one coherent CPython install for CBS discovery.

Output (one field per line): executable, version, base prefix, include dir, library.
The library search covers Debian multiarch, config-dir layouts, and macOS
frameworks. Static archives are ignored when a shared library exists.
"""

from __future__ import print_function

import os
import sys
import sysconfig


def _unique(items):
    seen = []
    for item in items:
        if item and item not in seen:
            seen.append(item)
    return seen


def _first_file(paths, allow_static=False):
    seen = set()
    for path in paths:
        if not path:
            continue
        path = os.path.realpath(path)
        if path in seen:
            continue
        seen.add(path)
        if not os.path.isfile(path):
            continue
        if path.endswith(".a") and not allow_static:
            continue
        return path
    return ""


def _include_dir():
    candidates = [
        sysconfig.get_path("include") or "",
        sysconfig.get_config_var("INCLUDEPY") or "",
        sysconfig.get_config_var("CONFINCLUDEPY") or "",
        os.path.join(sys.base_prefix, "include",
                     "python%d.%d" % (sys.version_info[0], sys.version_info[1])),
    ]
    for path in _unique(candidates):
        if os.path.isdir(path) and os.path.isfile(os.path.join(path, "Python.h")):
            return path
    return candidates[0] if candidates else ""


def _library_candidates():
    version = "%d.%d" % (sys.version_info[0], sys.version_info[1])
    libdir = sysconfig.get_config_var("LIBDIR") or ""
    libpl = sysconfig.get_config_var("LIBPL") or ""
    multiarch = sysconfig.get_config_var("MULTIARCH") or ""
    shlib = sysconfig.get_config_var("SHLIB_SUFFIX") or (
        ".dylib" if sys.platform == "darwin" else ".so")
    names = _unique([
        sysconfig.get_config_var("LDLIBRARY") or "",
        sysconfig.get_config_var("INSTSONAME") or "",
        "libpython%s%s" % (version, shlib),
        "libpython%sm%s" % (version, shlib),
        "Python",
    ])
    dirs = _unique([
        libpl,
        os.path.join(libdir, multiarch) if libdir and multiarch else "",
        libdir,
        os.path.join(sys.base_prefix, "lib"),
        os.path.join(sys.base_prefix, "lib", multiarch) if multiarch else "",
        os.path.join(sys.base_prefix, "lib64"),
        os.path.join(sys.prefix, "lib"),
        sysconfig.get_config_var("PYTHONFRAMEWORKPREFIX") or "",
        os.path.join(sys.base_prefix, "Python.framework", "Versions", version),
        os.path.join(sys.base_prefix, "lib", "python%s" % version, "config-%s" % version),
        os.path.join(sys.base_prefix, "lib", "python%s" % version,
                     "config-%s-%s" % (version, multiarch)) if multiarch else "",
    ])
    paths = []
    for directory in dirs:
        for name in names:
            paths.append(os.path.join(directory, name))
    return paths


library = _first_file(_library_candidates(), allow_static=False)
if not library:
    library = _first_file(_library_candidates(), allow_static=True)

print(sys.executable)
print(sys.version.split()[0])
print(sys.base_prefix)
print(_include_dir())
print(library)
