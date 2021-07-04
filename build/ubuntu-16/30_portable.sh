#!/bin/bash -ex

# Purpose: create a folder where Xclu comes with all shared libraries 
#          required to run without Qt installation on target system.
# Input: Xclu-bin folder
# Output: Xclu-bin-portable folder and xclu-bin-ubuntu-portable.zip file

source /opt/qt59/bin/qt59-env.sh || true
# we need to add || true because env.sh script contains logical error
# and returns errorlevel 1 even in success

pushd "$(dirname "$0")"

rm -rf Xclu-bin-portable
rm -f xclu-bin-ubuntu-portable.zip

# copy
cp -r Xclu-bin/ Xclu-bin-portable/

# make binary stand-alone
wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt-continuous-x86_64.AppImage

./linuxdeployqt-continuous-x86_64.AppImage ./Xclu-bin-portable/Xclu -no-translations -no-copy-copyright-files -bundle-non-qt-libs -verbose=2 -always-overwrite

# probably this file is required for AppImage, but not for now
rm Xclu-bin-portable/AppRun

zip -9 -r xclu-bin-ubuntu-portable.zip Xclu-bin-portable/

popd

echo PORTABLE SUCCESS
