////////////////////////////////////////////////////////////////////////////////////////////////////
/// <file>  pdbdump\pdbdump.cpp. </file>
///
/// <copyright file="pdbdump.cpp" company="Georg Ulbrich">
/// Copyright (c) 2020 Georg Ulbrich. All rights reserved.
/// </copyright>
///
/// <summary> The main module. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <atlcomcli.h>
#include <stdio.h>
#include <stdlib.h>

#include "dia2.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> print error message and exit with failure </summary>
///
/// <param name="show_help">  The show help. </param>
/// <param name="fmt">        Describes the format to use. </param>
/// <param name="...">        Variable arguments providing additional
/// information. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

#define FATAL(show_help, fmt, ...)     \
    wprintf(L##fmt "\n", __VA_ARGS__); \
    if (show_help) {                   \
        help();                        \
    }                                  \
    exit(EXIT_FAILURE)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Print help. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

void help() { wprintf(L"HELP!\n"); }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Dumps an JSON comment </summary>
///
/// <param name="s"> The comment to be dumped. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void dump_comment_json(wchar_t* s) { }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Dumps an XML comment </summary>
///
/// <param name="s"> The comment to be dumped. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void dump_comment_xml(wchar_t* s)
{
    wprintf(L"<!-- %s -->\n", s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Dumps an sqlite3 comment </summary>
///
/// <param name="s"> The comment to be dumped. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void dump_comment_sqlite3(wchar_t* s)
{
    wprintf(L"-- %s\n", s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Dumps a comment. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*DUMP_COMMENT)(wchar_t* s);

static DUMP_COMMENT dump_comment = dump_comment_json; ///< pointer for dumping comments

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Dumps a file. </summary>
///
/// <param name="filename"> Filename of the file to be dumped. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void dump_file(wchar_t* filename)
{

    // initialize generic result value
    HRESULT hr = CoInitialize(NULL);

    // create source access
    CComPtr<IDiaDataSource> source;
    hr = CoCreateInstance(CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&source);
    if (FAILED(hr)) {
        FATAL(false, "Could not initialize CLSID_DiaSource. Please register msdiaXXX.dll.");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> Main entry point. </summary>
///
/// <param name="argc"> The number of commandline arguments. </param>
/// <param name="argv"> The commandline arguments. </param>
///
/// <returns> 0 iff all is okay. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int wmain(int argc, wchar_t* argv[])
{

    // check existence of commandline arguments
    if (argc < 2) {
        FATAL(true, "No commandline arguments given.");
    }

    // initialize index for files
    int start_idx = 1;

    // check for optional parameters
    if (argv[1][0] == '-') {
        if (wcscmp(L"--help", argv[1]) == 0) {
            help();
        } else if (wcscmp(L"--json", argv[1]) == 0) {
            dump_comment = dump_comment_json;
        } else if (wcscmp(L"--xml", argv[1]) == 0) {
            dump_comment = dump_comment_xml;
        } else if (wcscmp(L"--sqlite3", argv[1]) == 0) {
            dump_comment = dump_comment_sqlite3;
        } else {
            FATAL(false, "Invalid option %s.", argv[1]);
        }
        start_idx++;
    }

    // iterate through commandline arguments
    for (int idx = start_idx; idx < argc; idx++) {
        dump_file(argv[idx]);
    }

    // indicate success
    return EXIT_SUCCESS;
}
