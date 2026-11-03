#!/usr/bin/env bash
#
# Local version of the GAMBIT GitHub CI tests (see .github/workflows/ci.yml
# and ci_linux_GH.yml). Builds GAMBIT and runs the CI test stages.
#
# Usage: cmake/scripts/run_ci_tests.sh [options]
#   -b DIR   Build directory (default: <repo>/build)
#   -j N     Parallel build jobs (default: half the number of cores)
#   -s LIST  Comma-separated stages to run (default: all). Stages:
#              configure,scanners,gambit,cli,spartan,collider,wc,standalones
#   -c "..."  Extra cmake arguments for the configure stage
#   -h       Show this help
#
# Stages 'collider' and 'wc' need extra backends and are not run by default;
# add them explicitly with -s. Set GAMBIT_CI_CMAKE_ARGS to override the
# default cmake arguments.

set -eo pipefail

REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD="${REPO}/build"
JOBS=$(( ($(nproc) + 1) / 2 ))
STAGES="configure,scanners,gambit,cli,spartan,standalones"
EXTRA_CMAKE=""

while getopts "b:j:s:c:h" opt; do
  case $opt in
    b) BUILD="$OPTARG" ;;
    j) JOBS="$OPTARG" ;;
    s) STAGES="$OPTARG" ;;
    c) EXTRA_CMAKE="$OPTARG" ;;
    h) sed -n '2,/^$/p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
    *) exit 1 ;;
  esac
done

# Same options as the CI configure step
CMAKE_ARGS="${GAMBIT_CI_CMAKE_ARGS:--D CMAKE_CXX_FLAGS=-rdynamic -D WITH_ROOT=OFF -D WITH_RESTFRAMES=OFF -D WITH_HEPMC=ON -D WITH_YODA=ON -D BUILD_FS_MODELS=CMSSM;MSSM;MDM -D WITH_MPI=OFF}"

TMPDIR_CI="$(mktemp -d)"
trap 'rm -rf "${TMPDIR_CI}"' EXIT

declare -a RESULTS
want() { [[ ",${STAGES}," == *",$1,"* ]]; }

# Run a stage, record pass/fail, and keep going so all stages are reported
stage() {
  local name="$1"; shift
  want "${name}" || return 0
  echo "=============== Stage: ${name} ==============="
  if ( set -e; "$@" ); then
    RESULTS+=("PASS  ${name}")
  else
    RESULTS+=("FAIL  ${name}")
  fi
}

# Run gambit on a copy of a yaml file with the hdf5 printer swapped for cout,
# so the tracked yaml files stay untouched.
run_yaml() {
  local src="${REPO}/yaml_files/$1"
  local tmp="${TMPDIR_CI}/$1"
  sed 's/ hdf5/ cout/g' "${src}" > "${tmp}"
  cd "${REPO}" && ./gambit -rf "${tmp}"
}

do_configure()   { mkdir -p "${BUILD}" && cd "${BUILD}" && cmake "${REPO}" ${CMAKE_ARGS} ${EXTRA_CMAKE}; }
do_scanners()    { cd "${BUILD}" && make -j"${JOBS}" scanners && cmake "${REPO}"; }
do_gambit()      { cd "${BUILD}" && make -j"${JOBS}" gambit; }
do_cli()         { cd "${REPO}" && ./gambit -h >/dev/null; }
do_spartan()     { run_yaml spartan.yaml; }
do_collider()    {
  cd "${BUILD}"
  for b in nulike susyhit rivet contur pythia higgsbounds higgssignals ATLAS_FullLikes; do make -j"${JOBS}" "${b}"; done
  run_yaml ColliderBit_CMSSM.yaml
}
do_wc()          {
  cd "${BUILD}"
  for b in superiso heplikedata heplike; do make -j"${JOBS}" "${b}"; done
  run_yaml WC.yaml
}
do_standalones() { cd "${BUILD}" && make -j"${JOBS}" standalones; }

stage configure   do_configure
stage scanners    do_scanners
stage gambit      do_gambit
stage cli         do_cli
stage spartan     do_spartan
stage collider    do_collider
stage wc          do_wc
stage standalones do_standalones

echo
echo "=============== Summary ==============="
printf '%s\n' "${RESULTS[@]}"
if printf '%s\n' "${RESULTS[@]}" | grep -q '^FAIL'; then exit 1; fi
