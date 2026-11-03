#!/bin/sh

set -eu

GUM_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
MARTY_LIB_DIR="$GUM_DIR/contrib/MARTY/install/lib"

if [ "$#" -gt 1 ]; then
  echo "Usage: $0 [MARTY_EXECUTABLE]" >&2
  exit 2
fi

MARTY_EXECUTABLE=${1:-"$GUM_DIR/build/marty_test"}

if [ ! -x "$MARTY_EXECUTABLE" ]; then
  echo "ERROR: MARTY executable '$MARTY_EXECUTABLE' is not executable. Build it with ./compile.sh first." >&2
  exit 1
fi

if [ ! -f "$MARTY_LIB_DIR/libooptools.so" ]; then
  echo "ERROR: MARTY's libooptools.so was not found in $MARTY_LIB_DIR." >&2
  exit 1
fi

compat_dir=$(mktemp -d)
trap 'rm -rf "$compat_dir"' EXIT

ln -s "$MARTY_LIB_DIR/libooptools.so" "$compat_dir/liblooptools.so"
export LIBRARY_PATH="$compat_dir:$MARTY_LIB_DIR${LIBRARY_PATH:+:$LIBRARY_PATH}"
export LD_LIBRARY_PATH="$compat_dir:$MARTY_LIB_DIR${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

if "$MARTY_EXECUTABLE"; then
  exit 0
else
  status=$?
  exit "$status"
fi
