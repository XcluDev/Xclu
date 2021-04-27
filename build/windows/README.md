# Windows compilation scripts for Xclu project

Based on Qt which should be already installed.

Main scripts:
* `10_setup_system.cmd` - install packages required for compilation (Realsense, etc).

Step scripts:
* `20_build.cmd` - build the project.
* `30_portable.cmd`  - create a folder where project comes with all shared libraries required to run without Qt installation on target system.

# Notes

These scripts assume that:
* Qt is already installed.
* Visual studio is already installed.

`20_build.cmd` script is configured for Visual Studio. 
To switch to mingw, install approriate qt and call make instead of nmake.
