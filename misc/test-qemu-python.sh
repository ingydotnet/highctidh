#!/usr/bin/env bash

# shellcheck disable=1091

set -e -u -o pipefail
set -x

FIELD_SIZE=$1
export VENV=venv${PYVER}
source "$VENV/bin/activate" &&
  "python${PYVER}" -m pytest -v -n"$(nproc)" \
    --doctest-modules -k "$FIELD_SIZE"
