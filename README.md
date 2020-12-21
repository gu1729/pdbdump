# Synopsis

pdbdump is a tool for dumping the content of PDB files to stdout.

PDB files (program databases) are produced by Microsoft Visual Studio
during the build of a project, for example C++ projects.
They hold debugging information, such as the user-defined types,
enumerations, functions etc.

pdbdump outputs these information in JSON, XML or SQLite3, thus allowing
for further processing, such as some static code analysis. For example,
one may track the growth of the size of some critical structs over
time, check packing of structs, generate some documentation etc.

Hint: the pdbdump tool only works on PDB files that have been
generated using the linker option `/DEBUG:FULL`.

# Usage

`pdbdump.exe [OPTION]... [FILTER]... [pdb-file]...`

## Options

    --help        show this help
    --json        output JSON, default
    --xml         output XML
    --sqlite3     output SQLite3, including code for table generation

## Filter

PDB files contain a lot of information, much of which might not be
of interest to you. To keep processes fast and output small, you
may filter the output according to your needs.

A filter option is a regular expression starting with either
`+` (for adding content) or `-` (for ignoring content).
Next follows the `symbol::`and then some regex.

For example, to select the `length` property, use the filter

`+symbol::length`

Selecting all properties starting with `virtual` can be achieved by

`+symbol::virtual.*`

Discarding all properties containing an `e` (for whatever reason)
is done via

`-symbol::.*e.*`

Dumping all properties for each symbol is simply

`+symbol::.*`

By default, only `name`, `symIndexId` and `symTag` for each symbol
are dumped.

# Examples

Dump some minimal information for each symbol in JSON format.

`pdbdump.exe test.pdb`

Do the same for multiple files

`pdbdump.exe test1.pdb test2.pdb test3.pdb`

Dump to a file

`pdbdump.exe test.pdb > test.json`

Dump a lot of information to a file

`pdbdump.exe +symbol::.* test.pdb > test.json`

Output in XML format

`pdbdump.exe --xml test.pdb`

Output in SQLite3 format

`pdbdump.exe --sqlite3 test.pdb`

The SQLite3 option also produces table generation code.
Hence, to create a SQLite3 database `test.db` one simply may

`pdbdump.exe --sqlite3 test.pdb | sqlite3.exe test.db`

# Further reading

For the meaning of the symbols properties etc., consult the
documentation of the DIA SDK (Debug Interface Access SDK)

https://docs.microsoft.com/de-de/visualstudio/debugger/debug-interface-access/debug-interface-access-sdk

# Homepage

The pdbdump project is hosted at

https://github.com/gu1729/pdbdump

