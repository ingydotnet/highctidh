#!/usr/bin/env bash

# shellcheck disable=1091

set -e -u -o pipefail
set -x

SOURCE_DATE_EPOCH=$(git log -1 --pretty=%ct)
export SOURCE_DATE_EPOCH
mkdir -p dist/source
mkdir -p build/tmp
export TMP=build/tmp
export VENV=venv${PYVER}
if [[ ! -d $VENV ]]
then
  "python${PYVER}" -m venv "$VENV"
else
  echo "venv exists: $VENV"
fi

source "$VENV/bin/activate" && CC=${CC} TMP=$TMP "pip${PYVER}" --cache-dir=build/ install --upgrade pip
source "$VENV/bin/activate" && CC=${CC} TMP=$TMP "pip${PYVER}" --cache-dir=build/ install pytest pytest-xdist
source "$VENV/bin/activate" && CC=${CC} TMP=$TMP "pip${PYVER}" --cache-dir=build/ install --no-clean .
