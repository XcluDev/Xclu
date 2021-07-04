# WARNING. 

This is old, obsolete scripts, kept alive for case if we will need to compile for qt59 env / xenial libs
and thus achieve debian-stretch compatibility inside github actions.

# Ubuntu 16 compilation scripts for Xclu project

This is almost same as [../debian](debian) scripts, but adopted to run inside Github Actions ubuntu-16 environment.

* Based on Qt from https://launchpad.net/~beineri packages.
* As a result of using beineri, we have to call `source /opt/qt59/bin/qt59-env.sh` to set the correct environment in build scripts.
This is their difference from debian scripts.

Main scripts:
* `10_setup_system.sh` - install packages required for compilation (Qt, Realsense, etc).
* `recompile_all.sh` - cleanup all, compile, generate portable zip.

Step scripts:
* `15_clean_all.sh` - remove all output and intermediate files produced.
* `20_build.sh` - build the project.
* `30_portable.sh`  - create a folder where project comes with all shared libraries required to run without Qt installation on target system.

### Table of versions compatibility of ubuntu and debian

* ubutnu 16 xenial =~ debian stretch
* ubutnu 18 bionic =~ debian buster
* ubuntu 20 focal  =~ debian buster(?)
* ubuntu 21 Hirsute Hippo

I noted that program compiled for Ubuntu 16+ works in Debian stretch.
