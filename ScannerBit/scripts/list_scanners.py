#!/usr/bin/env python3
"""Print a status table of every known GAMBIT scanner plugin (one row per
canonical plugin name). Reads scratch/build_time/scanbit_excluded_libs.yaml
plus a data file written by CMakeLists.txt at configure time, and walks
ScannerBit/src/scanners/ for native scanner_plugin() registrations."""
import io
import os
import re
import sys

import yaml


_HERE = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.normpath(os.path.join(_HERE, "..", ".."))
sys.path.insert(0, os.path.join(_REPO, "Utils", "scripts"))

import list_table  # noqa: E402


def parse_data_file(path):
    external_targets = []
    python_scanners = []
    build_dir = ""
    with io.open(path, "r") as f:
        for line in f:
            if line.startswith("EXTERNAL_TARGETS="):
                external_targets = [s for s in line[len("EXTERNAL_TARGETS="):].rstrip("\n").split(";") if s]
            elif line.startswith("PYTHON_SCANNERS="):
                python_scanners = [s for s in line[len("PYTHON_SCANNERS="):].rstrip("\n").split(";") if s]
            elif line.startswith("BUILD_DIR="):
                build_dir = line[len("BUILD_DIR="):].rstrip("\n").strip()
    return external_targets, python_scanners, build_dir


def is_target_installed(build_dir, target):
    if not build_dir or not target:
        return False
    stamp = os.path.join(build_dir, target + "-prefix", "src",
                         target + "-stamp", target + "-done")
    return os.path.exists(stamp)


def is_scanner_lib_built(libname):
    return os.path.exists(os.path.join(
        _REPO, "ScannerBit", "lib", "lib" + libname + ".so"))


def parse_excluded_yaml(path):
    """Return {libname: [reason, ...]} for every excluded scanner/objective
    library in scanbit_excluded_libs.yaml."""
    excluded = {}
    if not os.path.exists(path):
        return excluded
    with io.open(path, "r") as f:
        data = yaml.safe_load(f) or {}
    for libfile, info in data.items():
        name = libfile
        if name.startswith("lib"):
            name = name[3:]
        if name.endswith(".so"):
            name = name[:-3]
        raw_reasons = info.get("reason") or []
        if isinstance(raw_reasons, str):
            raw_reasons = [raw_reasons]
        # ScannerBit emits each reason as a literal YAML entry like
        # '- file missing: "ROOT"', which yaml.safe_load parses as a
        # single-key mapping; flatten back to "key: value".
        reasons = []
        for r in raw_reasons:
            if isinstance(r, dict):
                for k, v in r.items():
                    reasons.append("{}: {}".format(str(k).strip(), str(v).strip()))
            elif r is not None:
                s = str(r).strip()
                if s:
                    reasons.append(s)
        excluded[name] = reasons
    return excluded


_PLUGIN_RE = re.compile(
    r"scanner_plugin\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*,\s*version\s*\(\s*([^)]*)\)\s*\)"
)


def parse_native_plugins(scanners_dir):
    """Walk ScannerBit/src/scanners/<libdir>/* and return a list of
    {libname, plugin, version} dicts derived from scanner_plugin(...)
    registrations. Skips python/ — those come from a separate data source."""
    rows = []
    if not os.path.isdir(scanners_dir):
        return rows
    for libdir in sorted(os.listdir(scanners_dir)):
        libpath = os.path.join(scanners_dir, libdir)
        if not os.path.isdir(libpath):
            continue
        if libdir == "python":
            continue
        libname = "scanner_" + libdir
        for root, _dirs, files in os.walk(libpath):
            for fname in files:
                if not fname.endswith((".cpp", ".cc", ".cxx", ".hpp", ".h")):
                    continue
                with io.open(os.path.join(root, fname), "r", errors="replace") as fh:
                    text = fh.read()
                for m in _PLUGIN_RE.finditer(text):
                    name = m.group(1)
                    parts = [p.strip() for p in m.group(2).split(",") if p.strip()]
                    ver = ".".join(parts)
                    rows.append({"libname": libname, "plugin": name, "version": ver})
    return rows


def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: list_scanners.py <data_file>\n")
        sys.exit(2)

    external_targets, python_scanner_lines, build_dir = parse_data_file(sys.argv[1])
    excluded = parse_excluded_yaml(
        os.path.join(_REPO, "scratch", "build_time", "scanbit_excluded_libs.yaml")
    )
    native = parse_native_plugins(os.path.join(_REPO, "ScannerBit", "src", "scanners"))

    # Map "<target>" -> "scanner_<target>" plus a versionless fallback for
    # canonical dirs that drop the version (e.g. ScannerBit/src/scanners/great).
    # Versionless slot is first-seen wins, which is fine because in practice
    # only one scanner family hits this fallback.
    target_for_lib = {}
    for tgt in external_targets:
        target_for_lib.setdefault("scanner_" + tgt, tgt)
        if "_" in tgt:
            target_for_lib.setdefault("scanner_" + tgt.rsplit("_", 1)[0], tgt)

    grouped = {}
    for r in native:
        libname = r["libname"]
        target  = target_for_lib.get(libname, "")
        grouped.setdefault(r["plugin"], []).append({
            "version":  r["version"],
            "library":  libname,
            "target":   target,
            "disabled": libname in excluded,
            "reason":   "; ".join(excluded.get(libname, [])),
        })

    # [installed] = the user's build action for this scanner kind has
    # completed: external scanners → ExternalProject stamp present;
    # native scanners → libscanner_<x>.so built.
    def _ver_key(v):
        return [int(c) if c.isdigit() else c
                for c in re.split('([0-9]+)', v["version"])]

    grouped_rows = []
    for name in sorted(grouped, key=str.lower):
        versions = sorted(grouped[name], key=_ver_key)
        all_disabled = all(v["disabled"] for v in versions)
        external_versions = [v for v in versions if v["target"]]
        native_versions   = [v for v in versions if not v["target"]]

        def is_version_ready(v):
            if v["disabled"]:
                return False
            if v["target"]:
                return is_target_installed(build_dir, v["target"])
            return is_scanner_lib_built(v["library"])

        any_ready = any(is_version_ready(v) for v in versions)
        if all_disabled:
            kind = "disabled"
        elif any_ready:
            kind = "installed"
        else:
            kind = "not_installed"

        parts = []
        if external_versions:
            tgt_strs = []
            for v in external_versions:
                if v["disabled"] and not all_disabled:
                    tgt_strs.append("{} [disabled]".format(v["target"]))
                elif is_version_ready(v):
                    tgt_strs.append("{} [installed]".format(v["target"]))
                else:
                    tgt_strs.append(v["target"])
            parts.append("targets: " + ", ".join(tgt_strs))
        if native_versions and not external_versions:
            body = "none; native GAMBIT scanner"
            if kind == "not_installed":
                body += " – build GAMBIT to install"
            parts.append("targets: " + list_table.DIM + body + list_table.RESET)
        info = "  ".join(parts)

        grouped_rows.append((name, kind, info))

    # Python rows: one per scanner. Status is libscanner_python lib status (if
    # excluded, all are disabled) overlaid with per-scanner Python module
    # availability.
    py_lib_disabled = "scanner_python" in excluded
    py_lib_built = is_scanner_lib_built("scanner_python")
    python_rows = []
    for line in python_scanner_lines:
        parts = line.split("|")
        if len(parts) < 2:
            continue
        pname = parts[0]
        pstatus = parts[1]
        # Restore "+" → ", " in the missing-pkgs field (see python_scanners.cmake).
        pmissing = parts[2].replace("+", ", ") if len(parts) > 2 else ""
        if py_lib_disabled or pstatus != "enabled":
            kind = "disabled"
        elif py_lib_built:
            kind = "installed"
        else:
            kind = "not_installed"
        python_rows.append((pname, kind, pmissing))

    all_names = [r[0] for r in grouped_rows] + [r[0] for r in python_rows]
    if not all_names:
        print("  (no scanner plugins found)")
        return
    name_w = max(max(len(n) for n in all_names), len("Scanner"))

    print("  {bold}{h1:<{nw}}  {h2:<{tw}}  {h3}{reset}".format(
        bold=list_table.BOLD, reset=list_table.RESET,
        h1="Scanner", nw=name_w,
        h2="Status", tw=list_table.TAG_W,
        h3="Make targets"))
    print("  {0}  {1}  {2}".format(
        "-" * name_w, "-" * list_table.TAG_W, "-" * len("Make targets")))

    # Print grouped (native+external) rows.
    for name, kind, info in grouped_rows:
        print("  {n:<{nw}}  {tag}  {info}".format(
            n=name, nw=name_w, tag=list_table.tag_for_kind(kind), info=info))

    # Print Python rows (sorted alphabetically for parity with the grouped section).
    for name, kind, missing in sorted(python_rows, key=lambda r: r[0].lower()):
        if kind == "disabled":
            if missing:
                body = "none; python plugin – install package(s) [{}] to enable".format(missing)
            else:
                body = "none; python plugin – install package(s) to enable"
        elif kind == "not_installed":
            body = "none; python plugin – all packages available, build GAMBIT to install"
        else:
            body = "none; python plugin"
        info = "targets: " + list_table.DIM + body + list_table.RESET
        print("  {n:<{nw}}  {tag}  {info}".format(
            n=name, nw=name_w, tag=list_table.tag_for_kind(kind), info=info))


if __name__ == "__main__":
    main()
