#!/usr/bin/env python3
"""Invalidate only changed external builds; record inputs after successful install.

The caller declares source globs and required products. This script never invokes
make, a compiler, configuration, downloads, or patches.
"""

import argparse
import glob
import hashlib
import json
import os
from pathlib import Path
import re
import sys


# Ignore generated compilation/cache files within the declared source trees.
GENERATED_DIRECTORIES = {".libs", ".deps", "__pycache__", "build"}
GENERATED_SUFFIXES = {".o", ".lo", ".la", ".a", ".so", ".dylib", ".mod", ".pyc", ".pyo"}


def expand(pattern, source_root):
    # The checkout path is literal even when its name contains glob characters.
    root = str(Path(source_root)) if source_root else ""
    if root and pattern.startswith(root + os.sep):
        pattern = glob.escape(root) + pattern[len(root):]
    return glob.iglob(pattern, recursive=True)


def source_state(args):
    files = set()
    for pattern in args.input + args.dependency_input:
        # Filter beneath each declared tree, not arbitrary parent directories
        # named "build" in the user's checkout path.
        root = str(Path(args.source_root)) if args.source_root else ""
        relative = pattern[len(root):] if root and pattern.startswith(root + os.sep) else pattern
        prefix = re.split(r"[*?\[]", relative, maxsplit=1)[0]
        if relative != pattern:
            prefix = root + prefix
        base = Path(prefix) if prefix.endswith(os.sep) else Path(prefix).parent
        for name in expand(pattern, args.source_root):
            path = Path(name)
            generated = (GENERATED_DIRECTORIES.intersection(path.relative_to(base).parts)
                         or path.suffix.lower() in GENERATED_SUFFIXES)
            if path.is_file() and (pattern in args.dependency_input or not generated):
                files.add(path)
    sources = {}
    for path in sorted(files):
        stat = path.stat()
        sources[str(path)] = [str(path.resolve()), stat.st_mtime_ns, stat.st_size,
                              hashlib.sha256(path.read_bytes()).hexdigest()]
    return {"schema": 1, "configuration": args.configuration,
            "inputs": args.input, "dependency_inputs": args.dependency_input,
            "outputs": args.output,
            "configure_outputs": args.configure_output, "sources": sources}


def missing(patterns, source_root):
    return [pattern for pattern in patterns
            if not any(Path(path).is_file() for path in expand(pattern, source_root))]


def remove_stamp(path):
    try:
        Path(path).unlink()
    except FileNotFoundError:
        pass


def run(args):
    state = source_state(args)
    record = Path(args.record)
    absent_configure = missing(args.configure_output, args.source_root)
    absent_outputs = missing(args.output, args.source_root)
    if args.action == "record":
        if not state["sources"]:
            raise RuntimeError("cannot record an installation with no source inputs")
        if absent_configure or absent_outputs:
            raise RuntimeError("cannot record an incomplete installation: "
                               + ", ".join(absent_configure + absent_outputs))
        contents = (json.dumps(state, sort_keys=True, indent=2) + "\n").encode("utf-8")
        if record.is_file() and record.read_bytes() == contents:
            return
        record.parent.mkdir(parents=True, exist_ok=True)
        temporary = record.with_name(record.name + ".tmp")
        temporary.write_bytes(contents)
        os.replace(temporary, record)
        return

    try:
        previous = json.loads(record.read_bytes())
    except (FileNotFoundError, json.JSONDecodeError, UnicodeDecodeError):
        previous = None
    if absent_configure:
        reason = "missing configure output: " + absent_configure[0]
        remove_stamp(args.stamp + "-configure")
    elif absent_outputs:
        reason = "missing build output: " + absent_outputs[0]
    elif previous is None:
        reason = "no recorded successful source state"
    elif previous != state:
        reason = "source inputs or build command changed"
    else:
        return
    remove_stamp(args.stamp + "-build")
    print(f"-- {args.package}: rebuilding ({reason}).")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("check", "record"))
    for name in ("package", "stamp", "record", "configuration"):
        parser.add_argument("--" + name, required=True)
    parser.add_argument("--source-root", default="")
    for name in ("input", "dependency-input", "output", "configure-output"):
        parser.add_argument("--" + name, action="append", default=[])
    args = parser.parse_args()
    if not args.input or not args.output:
        parser.error("at least one input pattern and output are required")
    try:
        run(args)
    except (OSError, RuntimeError, ValueError) as error:
        print(f"{args.package}: automatic rebuild check failed: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
