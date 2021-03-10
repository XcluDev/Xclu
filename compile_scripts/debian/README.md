# Debian compilation scripts for Xclu project

Main scripts:
* `10_setup_system.sh` - install packages required for compilation (Qt, Realsense, etc).
* `recompile_all.sh` - cleanup all, compile, generate portable zip.

Step scripts:
* `15_clean_all.sh` - remove all output and intermediate files produced.
* `20_build.sh` - build the project.
* `30_portable.sh`  - create a folder where project comes with all shared libraries required to run without Qt installation on target system.
