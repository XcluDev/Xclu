#!/bin/bash -ex

# Purpose: cleanup all, compile, generate portable zip
# Input: source folder in ../..
# Output: xclu-bin-portable.zip file

pushd "$(dirname "$0")"

./15_clean_all.sh
./20_build.sh
./30_portable.sh

popd

echo RECOPILE ALL SUCCESS
