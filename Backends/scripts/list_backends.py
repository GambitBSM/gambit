#!/usr/bin/env python3
"""Print a status table (one row per canonical BACKENDNAME) for every known
GAMBIT backend interface. Reads config/gambit_backend_interfaces.yaml plus
a data file written by CMakeLists.txt at configure time."""
import io
import os
import sys

import yaml

_HERE = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.normpath(os.path.join(_HERE, "..", ".."))
sys.path.insert(0, os.path.join(_REPO, "Utils", "scripts"))

from harvesting_tools import (  # noqa: E402
    compute_bits_per_backend,
    get_all_backendnames,
)
import list_table  # noqa: E402


def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: list_backends.py <data_file>\n")
        sys.exit(2)

    active_targets = []
    build_dir = ""
    ditched_set = set()
    with io.open(sys.argv[1], "r") as f:
        for line in f:
            if line.startswith("TARGETS="):
                active_targets = [s for s in line[len("TARGETS="):].rstrip("\n").split(";") if s]
            elif line.startswith("BUILD_DIR="):
                build_dir = line[len("BUILD_DIR="):].rstrip("\n").strip()
            elif line.startswith("DITCHED="):
                ditched_set = {s for s in line[len("DITCHED="):].rstrip("\n").split(";") if s}

    def is_ditched(canonical):
        # Match canonical (or its underscore-collapsed form, for cases like
        # SUSY_HIT vs susyhit_1.5) against any cmake ${itch} entry, with or
        # without a trailing _<ver>. Catches BOSSed backends that the
        # interfaces YAML keeps "enabled" for type availability after the
        # build itself was excluded.
        cl = canonical.lower()
        cl_collapsed = canonical.replace('_', '').lower()
        for entry in ditched_set:
            e = entry.lower()
            if e == cl or e.startswith(cl + "_"):
                return True
            if cl_collapsed != cl and (e == cl_collapsed or e.startswith(cl_collapsed + "_")):
                return True
        return False

    def is_target_installed(target):
        if not build_dir or not target:
            return False
        return os.path.exists(os.path.join(
            build_dir, target + "-prefix", "src",
            target + "-stamp", target + "-done"))

    with io.open(os.path.join(_REPO, "config", "gambit_backend_interfaces.yaml"), "r") as f:
        bdata = yaml.safe_load(f) or {}
    enabled_set = set((bdata.get("enabled") or {}).keys())

    frontend_dir = os.path.join(_REPO, "Backends", "include", "gambit", "Backends", "frontends")
    all_backends = get_all_backendnames(frontend_dir)
    bits_per = compute_bits_per_backend(_REPO, frontend_dir)

    # Group each target under its longest-matching canonical (so e.g.
    # darksusy_MSSM_6.4.0 lands under DarkSUSY_MSSM, not under DarkSUSY).
    canonicals_by_len = sorted(all_backends, key=len, reverse=True)
    targets_by_canonical = {b: [] for b in all_backends}
    for t in active_targets:
        tl = t.lower()
        matched = False
        for canonical in canonicals_by_len:
            if tl.startswith(canonical.lower() + "_"):
                targets_by_canonical[canonical].append(t)
                matched = True
                break
        # Fallback for canonicals whose make target drops internal underscores
        # (SUSY_HIT -> susyhit_1.5).
        if not matched:
            for canonical in canonicals_by_len:
                cl = canonical.replace("_", "").lower()
                if cl != canonical.lower() and tl.startswith(cl + "_"):
                    targets_by_canonical[canonical].append(t)
                    break

    rows = []
    for canonical in sorted(all_backends, key=lambda s: s.lower()):
        targets = sorted(targets_by_canonical[canonical])
        active = (canonical in enabled_set) and not is_ditched(canonical)
        bits = bits_per.get(canonical, [])
        rows.append((canonical, active, bits, targets))

    name_w = max(len(r[0]) for r in rows)
    name_w = max(name_w, len("Backend"))
    bits_w = max(len(", ".join(r[2]) if r[2] else "none") for r in rows)
    # "used by: " column spans the literal prefix (9 chars) plus the padded
    # bits string. Bump to fit the "Used by Bits" header if narrower.
    used_by_col_w = max(9 + bits_w, len("Used by Bits"))
    bits_w = used_by_col_w - 9
    print("  {bold}{h1:<{nw}}  {h2:<{tw}}  {h3:<{w3}}  {h4}{reset}".format(
        bold=list_table.BOLD, reset=list_table.RESET,
        h1="Backend", nw=name_w,
        h2="Status", tw=list_table.TAG_W,
        h3="Used by Bits", w3=used_by_col_w,
        h4="Make targets"))
    print("  {0}  {1}  {2}  {3}".format(
        "-" * name_w, "-" * list_table.TAG_W,
        "-" * used_by_col_w, "-" * len("Make targets")))

    for name, active, bits, targets in rows:
        if bits:
            bits_visible = ", ".join(bits)
            bits_field   = bits_visible + " " * (bits_w - len(bits_visible))
        else:
            bits_field = list_table.DIM + "none" + list_table.RESET + " " * (bits_w - len("none"))

        if not targets:
            targets_field = list_table.DIM + "none" + list_table.RESET
        else:
            ann = []
            for t in targets:
                if is_target_installed(t):
                    ann.append("{} [installed]".format(t))
                else:
                    ann.append(t)
            targets_field = ", ".join(ann)

        if not active:
            kind = "disabled"
        elif targets and any(is_target_installed(t) for t in targets):
            kind = "installed"
        elif targets:
            kind = "not_installed"
        else:
            kind = ""
        print("  {name:<{nw}}  {tag}  used by: {bits}  targets: {tgts}".format(
            name=name, nw=name_w, tag=list_table.tag_for_kind(kind),
            bits=bits_field, tgts=targets_field))


if __name__ == "__main__":
    main()