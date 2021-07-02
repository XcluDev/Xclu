# Debian compilation scripts for Xclu project

Main scripts:
* `10_setup_system.sh` - install packages required for compilation (Qt, Realsense, etc).
* `recompile_all.sh` - cleanup all, compile, generate portable zip.

Step scripts:
* `15_clean_all.sh` - remove all output and intermediate files produced.
* `20_build.sh` - build the project.
* `30_portable.sh`  - create a folder where project comes with all shared libraries required to run without Qt installation on target system.

# Notes

The idea was to use these scripts both for manual start by developer and by Github Actions for automation.

In reality, `debian/30_portable.sh` works in well Debian Stretch, but it doesn't work in Github Actions Ubuntu environment. The reason is:

* We cannot use Ubuntu 18+ in GA, because it conflicts with `linuxdeployqt` used by script.
* Ubuntu 16 has very old packages for qt - 5.3.

That's why we created separate ubuntu build scripts, which are designed for Ubuntu 16 but uses newer Qt.

# References

* https://github.com/probonopd/linuxdeployqt - linux portable generator being used.
* https://github.com/probonopd/linuxdeployqt/issues/340 - a note about Ubuntu 18+.
* https://github.com/QuasarApp/CQtDeployer - multi-platform portable generator (I checked it and seems it is so-so).