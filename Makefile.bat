if not "%GIT_HOME%" == "" (
  pushd "%~dp0"
  "%GIT_HOME%\usr\bin\sed.exe" -f md2print.sed README.md > pdbdump\pdbdump\help.h
  "%GIT_HOME%\usr\bin\sed.exe" -f txt2print.sed LICENSE > pdbdump\pdbdump\license.h
  popd
)
