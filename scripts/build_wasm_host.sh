
#!/bin/sh

# clear CXX
export CXX=
export CXXFLAGS=
export CXXFLAGS_USED=
export LDFLAGS=
export LDFLAGS_USED=
export LDFLAGS_LD_USED=
export CFLAGS=
export CFLAGS_USED=




THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
REPO_ROOT=$THIS_DIR/..
REPO_ROOT=$(readlink -f "$REPO_ROOT")
DEPLOYMENT_DIR=$REPO_ROOT/deploy



set -eux

if false; then
    micromamba create -f environment-wasm-host.yml --platform=emscripten-wasm32 --yes
fi



cd $REPO_ROOT


if true; then

    export PREFIX=$MAMBA_ROOT_PREFIX/envs/praylib-wasm-host
    # echo "PREFIX=$PREFIX" >> $GITHUB_ENV
    export CMAKE_PREFIX_PATH=$PREFIX
    export CMAKE_SYSTEM_PREFIX_PATH=$PREFIX



    export CMAKE_PREFIX_PATH=$PREFIX
    export CMAKE_SYSTEM_PREFIX_PATH=$PREFIX

    mkdir -p build_wasm
    cd build_wasm

    pwd


    emcmake cmake .. \
        -DCMAKE_FIND_ROOT_PATH_MODE_PACKAGE=ON          \
        -DCMAKE_BUILD_TYPE=Release                      \
        -DCMAKE_INSTALL_PREFIX=$PREFIX                  \
        -DCMAKE_FIND_ROOT_PATH=$PREFIX                  \
        -DBUILD_EXTENSION=OFF                           \
        -DBUILD_WASM_HOST=ON                            \
        -Dpybind11_DIR=$PREFIX/share/cmake/pybind11/    \
        -DBUILD_WASM_HOST=ON

    emmake make -j 8

    cd ..

fi



WASM_DEPLOY_ENV_NAME=praylib-wasm-deploy
WASM_DEPLOY_ENV_PREFIX=$MAMBA_ROOT_PREFIX/envs/$WASM_DEPLOY_ENV_NAME
if false; then

    rm -rf $WASM_DEPLOY_ENV_PREFIX

    micromamba create -n $WASM_DEPLOY_ENV_NAME \
        --platform=emscripten-wasm32 \
        -c $OUTPUT_DIR \
        -c https://repo.prefix.dev/emscripten-forge-dev \
        --yes \
        "python>=3.13" \
        pyjs \
        numpy \
        praylib

    # pack
    empack pack env --env-prefix $WASM_DEPLOY_ENV_PREFIX --outdir $DEPLOYMENT_DIR


fi


if true; then

    # rm -rf $DEPLOYMENT_DIR
    mkdir -p $DEPLOYMENT_DIR

    cp -r $REPO_ROOT/build_wasm/praylib_host.js $DEPLOYMENT_DIR
    cp -r $REPO_ROOT/build_wasm/praylib_host.wasm $DEPLOYMENT_DIR

    cp -r $REPO_ROOT/src/index.html $DEPLOYMENT_DIR
fi

