# Debian compilation scripts for Xclu project

Main scripts:
* `10_setup_system.sh` - install packages required for compilation (Qt, Realsense, etc).
* `recompile_all.sh` - cleanup all, compile, generate portable zip.

Step scripts:
* `15_clean_all.sh` - remove all output and intermediate files produced.
* `20_build.sh` - build the project.
* `30_portable.sh`  - create a folder where project comes with all shared libraries required to run without Qt installation on target system.

# Notes

* The idea was to use these scripts both for manual start by developer and by Github Actions for automation.
* These scripts work OK within Ubuntu and thus may be used for github actions.
* linuxdeployqt used for generating portable zip in Ubuntu works only in Ubuntu 18 bionic and doesnt work in Ubuntu 20. In debian it works ok.

# References

* https://github.com/probonopd/linuxdeployqt - linux portable generator being used.
* https://github.com/probonopd/linuxdeployqt/issues/340 - a note about Ubuntu 18+.
* https://github.com/QuasarApp/CQtDeployer - multi-platform portable generator (I checked it and seems it is so-so).
