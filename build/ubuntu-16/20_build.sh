#!/bin/bash -ex

source /opt/qt59/bin/qt59-env.sh || true
# we need to add || true because env.sh script contains logical error
# and returns errorlevel 1 even in success

# Purpose: build Xclu project
# Input: source folder in ../..
# Output: Xclu-bin folder

# notes: * Xclu-bin folder name is configured in Xclu.pro file.
#        * please call 10_setup_system.sh once before running this build script

pushd "$(dirname "$0")"

test -d temp-build || mkdir temp-build
pushd temp-build

qmake ../../../Xclu.pro CONFIG+=Release
# Release word should start from Capital letter
# no need this, its already in pro file: DEFINES+=XCLU_DEPLOY
cpus=$(/usr/bin/nproc)
make -j$cpus

popd # from build-dir

popd

echo BUILD SUCCESS