# Xclu Github Actions scripts

These files configures https://docs.github.com/en/actions cloud engine to compile project when code is pushed to repository.

## Debian build

Auto-compile project to be sure it compiles.

* Uses [build/debian](../../build/debian) scripts
* Runs in GA ubuntu-latest
* Uses system os packages to get Qt.

## Ubuntu build

Auto-compile project to be sure it compiles + try generate release portable zips (ubunto-build workflow does not uploads these zips).

* Uses [build/ubuntu](../../build/ubuntu) scripts
* Runs in GA ubuntu-16
* Uses https://launchpad.net/~beineri to get Qt.

## Windows build

* Uses [build/windows](../../build/windows) scripts
* Runs in GA windows-latest
* Uses VC 2019 and Qt 5.15.2
* Qt is installed using Github action https://github.com/jurplel/
* VC2019 is pre-installed in github actions windows-latest runner.

It seems we may switch to mingw81 because it is preinstalled too, but we have to change Qt `arch` parameter in jurplel step and change `nmake` call to `make` in `Xclu/build/windows/20_build.cmd`.

Links:
* https://github.com/jurplel/install-qt-action/issues/49 note about vcvars.bat
* https://github.com/actions/virtual-environments/blob/releases/win19/20210309/images/win/Windows2019-Readme.md - info about what software is pre-installed in GA windows.

## Ubuntu generate release zip

When git tag is created starting with "v" (for example "v1.0.1"), generate and publish portable zip to release page.

How to use:
```
git tag v0.0.7 -m "This is my super release"
git push origin --tags
```

After this, a script `ubuntu-generate-release-zip.yml` will be run by GA, and
1) generate github release page for this tag,
2) generate Xclu ubuntu build, generate zip, and attach zip to that release.

Based on https://github.com/svenstaro/upload-release-action

* Alternatively, releases could be made in github browser interface.

## Windows generate release zip

Works same as ubuntu release.

# Links

* https://git-scm.com/book/en/v2/Git-Basics-Tagging - info about tagging in git
* https://github.com/marketplace/actions/gh-release - some interesting GA action
* https://github.community/t/how-to-get-just-the-tag-name/16241/6 - how to get tag name in GA action
* https://docs.github.com/en/developers/webhooks-and-events/github-event-types#releaseevent - data about commits, etc, for GA action code.

# Notes

It is possible to run `build` and `generate-release-zip` steps of same architecture together in one workflow, but I decided to left them separate
because it is clear where each code is located. BTW, these scripts currently do not run simultaneously - build is started on normal code push,
and release is started on tags push.

It is interesting that windows and ubuntu release scripts run simultaneously, and they will both try to create release pages in github, but it
seems to be ok, because https://github.com/svenstaro/upload-release-action creates release page if it doesn't exist and re-uses if one exist.

# Upload artifacts note

As a test, we upload portable versions generated during non-release ubuntu and windows builds as artifacts using https://github.com/actions/upload-artifact
Note, GA always compresses artifact files as zip, so to avoid double zips we pack directories using GA, avoiding our normal zipping using scripts.
