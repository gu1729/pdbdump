pushd "%~dp0"
x64\Debug\pdbdump.exe --help    x64\Debug\test.pdb > expected\001_help.txt
x64\Debug\pdbdump.exe --version x64\Debug\test.pdb > expected\002_version.txt
x64\Debug\pdbdump.exe --license x64\Debug\test.pdb > expected\003_license.txt
x64\Debug\pdbdump.exe --list    x64\Debug\test.pdb > expected\004_list.txt
x64\Debug\pdbdump.exe           x64\Debug\test.pdb > expected\005_simple.json
x64\Debug\pdbdump.exe --json    x64\Debug\test.pdb > expected\006_simple.json
x64\Debug\pdbdump.exe --xml     x64\Debug\test.pdb > expected\007_simple.xml
x64\Debug\pdbdump.exe --sqlite3 x64\Debug\test.pdb > expected\008_simple.db
x64\Debug\pdbdump.exe --csv     x64\Debug\test.pdb > expected\009_simple.csv
popd
pause
