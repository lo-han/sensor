from subprocess import run
from shutil import rmtree
from os import chdir

BUILD_FOLDER = "build"

try:
    rmtree(BUILD_FOLDER)
except:
    pass

try:
    run("cmake -S . -B build -Wno-dev", shell=True, check=True)
    run("cmake --build build", shell=True, check=True)
    chdir(BUILD_FOLDER)
    run("ctest --rerun-failed --output-on-failure", shell=True, check=True)
    chdir("..")
except:
    pass