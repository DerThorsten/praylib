#!/usr/bin/env bash

set -euo pipefail

#dir of this script
THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
REPO_ROOT=$THIS_DIR/..
REPO_ROOT=$(readlink -f "$REPO_ROOT")


praylib-wasm-deploy create-project --project-dir "$REPO_ROOT/sandbox/hello_world"
praylib-wasm-deploy build-project \
    --project-dir "$REPO_ROOT/sandbox/hello_world" \
    --extra-channels "$REPO_ROOT/emscripten_forge/output"

praylib-wasm-deploy pack-env --project-dir "$REPO_ROOT/sandbox/hello_world"