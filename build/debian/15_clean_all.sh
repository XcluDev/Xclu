#!/bin/bash -ex

# Purpose: remove all output and intermediate files produced by compilation

pushd "$(dirname "$0")"

rm -rf temp-build
rm -rf Xclu-bin
rm -rf Xclu-bin-portable
test -f *.zip && rm *.zip

popd

echo CLEAN SUCCESS