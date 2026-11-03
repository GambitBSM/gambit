#!/usr/bin/env bash

set -Eeuo pipefail

GUM_DIR=$(cd -- "$(dirname -- "$0")" && pwd)
MARTY_INSTALL_DIR="$GUM_DIR/contrib/MARTY/install"
TEST_TMP_DIR=$(mktemp -d)
BUILD_LOG="$TEST_TMP_DIR/build.log"
UNIT_TEST_LOG="$TEST_TMP_DIR/unit-tests.log"
RUN_LOG="$TEST_TMP_DIR/run.log"
SUCCESS=0

cleanup() {
  if [ "$SUCCESS" -eq 1 ]; then
    rm -rf "$TEST_TMP_DIR"
  else
    echo "Test failed; logs and generated files retained in: $TEST_TMP_DIR" >&2
  fi
}
trap cleanup EXIT

has_warnings() {
  grep -Ein '(^|[[:space:]])(CMake[[:space:]]+)?Warning([[:space:]:]|$)|warning:' "$1"
}

cd "$GUM_DIR"

echo "Cleaning GUM build and MARTY install directories..."
rm -rf "$GUM_DIR/build" "$MARTY_INSTALL_DIR"

echo "Configuring GUM..."
if ! cmake -S "$GUM_DIR" -B "$GUM_DIR/build" -Ditch_Mathematica=ON 2>&1 | tee "$BUILD_LOG"; then
  echo "ERROR: GUM configuration failed." >&2
  exit 1
fi

echo "Building MARTY and marty_test from a clean build directory..."
if ! cmake --build "$GUM_DIR/build" --target marty_test --parallel "${JOBS:-$(nproc)}" 2>&1 | tee -a "$BUILD_LOG"; then
  echo "ERROR: MARTY and marty_test build failed." >&2
  exit 1
fi

if has_warnings "$BUILD_LOG"; then
  echo "ERROR: Build/configuration output contains warnings; refusing to run the test." >&2
  exit 1
fi
echo "Build completed with no warnings."

MARTY_BUILD_DIR="$GUM_DIR/build/MARTY-prefix/src/MARTY-build"
UNIT_TEST_LIST=$(ctest --test-dir "$MARTY_BUILD_DIR" -L units -N)
printf '%s\n' "$UNIT_TEST_LIST"
UNIT_TEST_COUNT=$(sed -n 's/^Total Tests: //p' <<<"$UNIT_TEST_LIST")
if [ -z "$UNIT_TEST_COUNT" ] || [ "$UNIT_TEST_COUNT" -eq 0 ]; then
  echo "ERROR: No MARTY unit tests were discovered in $MARTY_BUILD_DIR." >&2
  exit 1
fi

echo "Running $UNIT_TEST_COUNT MARTY unit tests..."
if ! ctest --test-dir "$MARTY_BUILD_DIR" -L units --output-on-failure 2>&1 | tee "$UNIT_TEST_LOG"; then
  echo "ERROR: MARTY unit tests failed." >&2
  exit 1
fi

mkdir "$TEST_TMP_DIR/run"
echo "Running marty_test..."
if ! (cd "$TEST_TMP_DIR/run" && "$GUM_DIR/run_marty_executable.sh") 2>&1 | tee "$RUN_LOG"; then
  echo "ERROR: marty_test failed." >&2
  exit 1
fi

if has_warnings "$RUN_LOG"; then
  echo "ERROR: Test output contains warnings." >&2
  exit 1
fi

SUCCESS=1
echo "MARTY unit tests and marty_test passed; build completed with no warnings."
