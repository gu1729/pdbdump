# indent examples
/^`/s/^/  /

# indent text
/^[^#]/s/^/       /

# indent HTTPS
/^ *https/s/^/  /

# uppercase sections
/^#/s/.*/\U&/

# replace hashes
s/^##* *//

# some special cases
/`pdbdump.exe \[/s/^  //
/`pdbdump.exe \[/s/`//g

# for the examples, remove `
/^ *`/s/`//g

# add wprintf
s/^/wprintf(L"/
s/$/\\n");/
