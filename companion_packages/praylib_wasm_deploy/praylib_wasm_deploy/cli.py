import argparse
import tomllib
import os
import shutil
import subprocess
from pathlib import Path
from empack.file_patterns import pkg_file_filter_from_yaml
from empack.pack import (
    DEFAULT_CONFIG_PATH,
    add_tarfile_to_env_meta,
    pack_directory,
    pack_env,
    pack_file,
)

# this dir
this_dir = os.path.dirname(os.path.abspath(__file__))
defaults_dir = os.path.join(this_dir, "defaults")



def create_project(project_dir):
    os.makedirs(project_dir, exist_ok=True)

    # copy defaults
    shutil.copy(os.path.join(defaults_dir, "praylibconf.toml"), os.path.join(project_dir, "praylibconf.toml"))
    shutil.copy(os.path.join(defaults_dir, "environment-wasm.yml"), os.path.join(project_dir, "environment-wasm.yml"))
    
    # create deploy directory
    deploy_dir = os.path.join(project_dir, "deploy")
    os.makedirs(deploy_dir, exist_ok=True)

    # copy index.html from defaults
    shutil.copy(os.path.join(defaults_dir, "index.html"), os.path.join(deploy_dir, "index.html"))
    # overlay-worker.js
    shutil.copy(os.path.join(defaults_dir, "overlay-worker.js"), os.path.join(deploy_dir, "overlay-worker.js"))


def create_env(project_dir, extra_channels=None):
    if extra_channels is None:
        extra_channels = []

    prefix_dir = os.path.join(project_dir, "env")
    # if prefix exists, we delete it
    if os.path.exists(prefix_dir):
        shutil.rmtree(prefix_dir)

    args = [
        "micromamba", "create", 
        "-f", os.path.join(project_dir, "environment-wasm.yml"), 
        "--prefix", str(prefix_dir), 
        "--relocate-prefix", "/", 
        "--platform", "emscripten-wasm32",
        "--yes"
    ]
    
    for channel in extra_channels:
        args.extend(["-c", channel])
    print("args:", args)
    subprocess.run(args)

def build_project(project_dir, extra_channels=None):
    create_env(project_dir, extra_channels)

    # create the deployment dir
    os.makedirs(os.path.join(project_dir, "deploy"), exist_ok=True)

    # copy praylib_host.js / praylib_host.wasm from the env/bin
    deploy_dir = Path(project_dir/"deploy")

    shutil.copy(Path(project_dir/"env"/"bin"/"praylib_host.js"), Path(deploy_dir/"praylib_host.js"))
    shutil.copy(Path(project_dir/"env"/"bin"/"praylib_host.wasm"), Path(deploy_dir/"praylib_host.wasm"))


def pack_wasm_env(project_dir):
    file_filters = pkg_file_filter_from_yaml(DEFAULT_CONFIG_PATH)
    
    pack_env(
        env_prefix=Path(project_dir/"env"),
        relocate_prefix="/",
        file_filters=file_filters,
        outdir=Path(project_dir/"deploy"),
        use_cache=False
    )

    # pack the complete code directory
    pack_directory(
        host_dir=Path(project_dir/"code"),
        mount_dir=Path("/home/web_user/code"),
        outdir=Path(project_dir/"deploy"),
        outname='main.tar.gz'
    )

    add_tarfile_to_env_meta(
        env_meta_filename=Path(project_dir/"deploy"/"empack_env_meta.json"),
        tarfile=Path(project_dir/"deploy"/"main.tar.gz")
    )


def main():
    parser = argparse.ArgumentParser(description="Praylib WASM DEPLOY")
    parser.add_argument("--version", action="version", version="Praylib WASM DEPLOY")

    # we need the subcommand
    subparsers = parser.add_subparsers(dest="command")

    # create project subcommand
    create_project_parser = subparsers.add_parser("create-project", help="Create a new project")
    create_project_parser.add_argument("--project-dir", type=str, help="Directory for the project")

    # build project parser
    build_project_parser = subparsers.add_parser("build-project", help="Build the project")
    build_project_parser.add_argument("--project-dir", type=str, help="Directory for the project")
    build_project_parser.add_argument("--extra-channels", type=str, nargs="*", help="Extra channels to add")


    # pack 
    pack_env_parser = subparsers.add_parser("pack-env", help="Pack the environment")
    pack_env_parser.add_argument("--project-dir", type=str, help="Directory for the project")

    args = parser.parse_args()

    if args.command == "create-project":
        if not args.project_dir:
            print("Missing project directory.")
        else:
            create_project(Path(args.project_dir))

    elif args.command == "build-project":
        if not args.project_dir:
            print("Missing project directory.")
        else:
            build_project(Path(args.project_dir), args.extra_channels)

    elif args.command == "pack-env":
        if not args.project_dir:
            print("Missing project directory.")
        else:
            pack_wasm_env(Path(args.project_dir))