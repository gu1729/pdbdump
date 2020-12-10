#include <atlcomcli.h>
#include <stdio.h>
#include <stdlib.h>

#include "dia2.h"

#define FATAL_IF(condition, show_help, fmt, ...)   \
    if (condition) {                               \
        wprintf(L"ERROR: " fmt "\n", __VA_ARGS__); \
        if (show_help) {                           \
            help();                                \
        }                                          \
        exit(EXIT_FAILURE);                        \
    }
#define FATAL_HELP(...) FATAL_IF(true, true, __VA_ARGS__)
#define FATAL(...) FATAL_IF(true, false, __VA_ARGS__)

void help() { wprintf(L"HELP!\n"); }

class Dumper {
protected:
    int pdbs = 0;

public:
    virtual void comment(wchar_t* s) = 0;
    virtual void attribute(wchar_t* name, wchar_t* value) = 0;
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void pdbSeparator() = 0;
    virtual void pdbStart() = 0;
    virtual void pdbEnd() = 0;
};

class JSONDumper : public Dumper {
public:
    JSONDumper() { }
    void comment(wchar_t* s) { }
    void attribute(wchar_t* name, wchar_t* value) { }
    void start() { wprintf(L"[\n"); }
    void end() { wprintf(L"]\n"); }
    void pdbSeparator() { wprintf(L",\n"); }
    void pdbStart() { wprintf(L"{\n"); }
    void pdbEnd() { wprintf(L"}\n"); }
};

class XMLDumper : public Dumper {
public:
    XMLDumper() { }
    void comment(wchar_t* s) { wprintf(L"<!-- %s -->\n", s); }
    void attribute(wchar_t* name, wchar_t* value) { }
    void start()
    {
        wprintf(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n");
        wprintf(L"<pdbs>\n");
    }
    void end() { wprintf(L"</pdbs>\n"); }
    void pdbSeparator() { }
    void pdbStart() { }
    void pdbEnd() { }
};

class SQLite3Dumper : public Dumper {
public:
    SQLite3Dumper() { }
    void comment(wchar_t* s) { wprintf(L"-- %s\n", s); }
    void attribute(wchar_t* name, wchar_t* value) { }
    void start() { }
    void end() { }
    void pdbSeparator() { }
    void pdbStart() { }
    void pdbEnd() { }
};

int wmain(int argc, wchar_t* argv[])
{
    if (argc < 2) {
        FATAL_HELP("No commandline arguments given.");
    }

    JSONDumper jsonDumper;
    XMLDumper xmlDumper;
    SQLite3Dumper sqlite3Dumper;
    Dumper* dumper = (Dumper*)&jsonDumper;

    int start_idx = 1;

    if (argv[1][0] == '-') {
        if (wcscmp(L"--help", argv[1]) == 0) {
            help();
            return EXIT_SUCCESS;
        } else if (wcscmp(L"--json", argv[1]) == 0) {
            dumper = (Dumper*)&jsonDumper;
        } else if (wcscmp(L"--xml", argv[1]) == 0) {
            dumper = (Dumper*)&xmlDumper;
        } else if (wcscmp(L"--sqlite3", argv[1]) == 0) {
            dumper = (Dumper*)&sqlite3Dumper;
        } else {
            FATAL_IF(true, false, "Invalid option %s.", argv[1]);
        }
        start_idx++;
    }

    dumper->start();
    for (int idx = start_idx; idx < argc; idx++) {
        if (idx > start_idx) {
            dumper->pdbSeparator();
        }
        dumper->pdbStart();
        CComPtr<IDiaDataSource> source;
        if (FAILED(CoCreateInstance(CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&source))) {
            FATAL("Could not initialize CLSID_DiaSource. Please register msdiaXXX.dll.");
        }
        if (FAILED(source->loadDataFromPdb(argv[idx]))) {
            if (FAILED(source->loadDataForExe(argv[idx], NULL, NULL))) {
                FATAL("Could not load data from pdb/exe.");
            }
        }
        CComPtr<IDiaSession> session;
        if (FAILED(source->openSession(&session))) {
            FATAL("Could not open session.");
        }
        CComPtr<IDiaSymbol> global;
        if (FAILED(session->get_globalScope(&global))) {
            FATAL("Could not query global scope.");
        }
        dumper->pdbEnd();
    }
    dumper->end();

    return EXIT_SUCCESS;
}
