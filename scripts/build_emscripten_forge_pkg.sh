# this dir
THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
REPO_ROOT=$THIS_DIR/..
REPO_ROOT=$(readlink -f "$REPO_ROOT")


EMSCRIPTEN_FORGE_DIR=$REPO_ROOT/emscripten_forge
RECIPE_DIR="$EMSCRIPTEN_FORGE_DIR/recipe"
RECIPE_YAML_TEMPLATE="$RECIPE_DIR/recipe.yaml.template"
RECIPE_YAML="$RECIPE_DIR/recipe.yaml"
OUTPUT_DIR="$EMSCRIPTEN_FORGE_DIR/output"


# we create a seperate src dir where we copy
# the relevant files
RECIPE_SRC="$EMSCRIPTEN_FORGE_DIR/recipe_src/"
rm -rf "$RECIPE_SRC"
mkdir -p "$RECIPE_SRC"


# copy
# * pyproject.toml
cp "$REPO_ROOT/pyproject.toml" "$RECIPE_SRC/pyproject.toml"

# src
cp -r "$REPO_ROOT/src" "$RECIPE_SRC/src"

# CMakeLists.txt
cp "$REPO_ROOT/CMakeLists.txt" "$RECIPE_SRC/CMakeLists.txt"

# LICENSE
cp "$REPO_ROOT/LICENSE" "$RECIPE_SRC/LICENSE"

# remove any *.so from RECIPE_SRC
find "$RECIPE_SRC" -name "*.so" -exec rm -f {} +



# replace PATH_PLACEHOLDER_TO_BE_REPLACED in the recipe.yaml.template with the actual path
# (ie the value of REPO_ROOT)
sed "s|PATH_PLACEHOLDER_TO_BE_REPLACED|$RECIPE_SRC|g" "$RECIPE_YAML_TEMPLATE" > "$RECIPE_YAML"


VARIANT_URL="https://raw.githubusercontent.com/emscripten-forge/recipes/refs/heads/main/variant.yaml"
VARIANT_FILE="$EMSCRIPTEN_FORGE_DIR/variant.yaml"

# IF VARIANT_FILE does not exist, download it
if [ ! -f "$VARIANT_FILE" ]; then
    echo "Downloading variant file from $VARIANT_URL"
    curl -o "$VARIANT_FILE" "$VARIANT_URL"
else
    echo "Variant file already exists at $VARIANT_FILE"
fi


# get extra args
EXTRA_ARGS=()
if [ $# -gt 0 ]; then
    echo "Using extra args: $@"
    EXTRA_ARGS=("$@")
else
    echo "No extra args provided"
fi


rattler-build build \
    --package-format tar-bz2 \
    -c https://repo.prefix.dev/emscripten-forge-dev \
    -c microsoft \
    -c conda-forge \
    --target-platform emscripten-wasm32 \
    -m "$VARIANT_FILE" \
    --recipe "$RECIPE_DIR" \
    --output-dir "$OUTPUT_DIR" \
    ${EXTRA_ARGS[@]} \
