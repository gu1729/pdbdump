#include <assert.h>
#include <atlcomcli.h>
#include <comdef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dia2.h"
#include "pdbdump.h"

static Format format = Format::JSON;
static bool showHelp = false;

int wmain(int argc, wchar_t* argv[])
{

    HRESULT hr = CoInitialize(NULL);

    for (int i = 1; i < argc; i++) {
        if (wcscmp(L"--json", argv[i]) == 0) {
            format = Format::JSON;
        } else if (wcscmp(L"--xml", argv[i]) == 0) {
            format = Format::XML;
        } else if (wcscmp(L"--sqlite3", argv[i]) == 0) {
            format = Format::SQLITE3;
        } else if (wcscmp(L"--help", argv[i]) == 0) {
            showHelp = true;
        } else if (argv[i][0] == '-') {
            FATAL("Unknown option %ls.", argv[i]);
        }
    }

    if (showHelp == true) {
        wprintf(L"HELP!\n");
        exit(EXIT_SUCCESS);
    }

    switch (format) {
    case Format::JSON:
        wprintf(L"[\n");
        break;
    case Format::XML:
        wprintf(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n");
        wprintf(L"<pdbs>\n");
        break;
    case Format::SQLITE3:
        wprintf(L"CREATE TABLE pdb (\n");
        wprintf(L"  id INTEGER NOT NULL,\n");
        wprintf(L"  name TEXT NOT NULL,\n");
        wprintf(L"  PRIMARY KEY (id)\n");
        wprintf(L");\n");
        wprintf(L"\n");
        wprintf(L"CREATE TABLE symbol (\n");
        wprintf(L"  pdbId INTEGER NOT NULL,\n");
        SYMBOL_PROPERTY(SQLITE3_CREATE_COLUMN);
        wprintf(L"  FOREIGN KEY (pdbId) REFERENCES pdb (id)\n");
        wprintf(L");\n");
        wprintf(L"\n");
        wprintf(L"BEGIN TRANSACTION;\n");
        wprintf(L"\n");
        break;
    }

    ULONG pdbId = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            continue;
        }
        pdbId++;

        CComPtr<IDiaDataSource> source;
        if (FAILED(CoCreateInstance(CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&source))) {
            FATAL("Could not initialize CLSID_DiaSource. Please register msdiaXXX.dll.");
        }
        CComPtr<IDiaEnumSymbols> enumSymbols;
        CComPtr<IDiaSymbol> symbol;
        if (FAILED(source->loadDataFromPdb(argv[i]))) {
            if (FAILED(source->loadDataForExe(argv[i], NULL, NULL))) {
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

        switch (format) {
        case Format::JSON:
            if (pdbId > 1) {
                wprintf(L",\n");
            }
            wprintf(L"  {\n");
            wprintf(L"    \"name\" : \"%ls\",\n", argv[i]);
            wprintf(L"    \"symbols\" : [\n");
            break;
        case Format::XML:
            wprintf(L"  <pdb>\n");
            wprintf(L"    <name><![CDATA[%ls]]></name>\n", argv[i]);
            break;
        case Format::SQLITE3:
            wprintf(L"INSERT INTO pdb (id, name) VALUES (%lu, \"%s\");\n", pdbId, argv[i]);
            break;
        }

        ULONG celt;
        hr = global->findChildren(SymTagNull, NULL, nsNone, &enumSymbols);
        if (SUCCEEDED(hr)) {
            ULONG symbols = 0;
            while (SUCCEEDED(hr = enumSymbols->Next(1, &symbol, &celt)) && celt == 1) {
                symbols++;
                switch (format) {
                case Format::JSON:
                    if (symbols > 1) {
                        wprintf(L",\n");
                    }
                    wprintf(L"      {\"pdbId\" : %lu", pdbId);
                    break;
                case Format::XML:
                    wprintf(L"    <symbol>");
                    break;
                case Format::SQLITE3:
                    wprintf(L"INSERT INTO symbol (pdbId");
                    SYMBOL_PROPERTY(DUMP_PROPERTY_NAME);
                    wprintf(L") VALUES (%lu", pdbId);
                    break;
                }
                SYMBOL_PROPERTY(DUMP_PROPERTY);
                switch (format) {
                case Format::JSON:
                    wprintf(L"}");
                    break;
                case Format::XML:
                    wprintf(L"</symbol>\n");
                    break;
                case Format::SQLITE3:
                    wprintf(L");\n");
                    break;
                }
                symbol = 0;
            }
        } else {
            FATAL("Could not find symbol children of global");
        }

        switch (format) {
        case Format::JSON:
            wprintf(L"    ]\n");
            wprintf(L"  }");
            break;
        case Format::XML:
            wprintf(L"  </pdb>\n");
            break;
        case Format::SQLITE3:
            wprintf(L"\n");
            break;
        }
    }

    switch (format) {
    case Format::JSON:
        wprintf(L"\n]\n");
        break;
    case Format::XML:
        wprintf(L"</pdbs>\n");
        break;
    case Format::SQLITE3:
        wprintf(L"COMMIT;\n");
        wprintf(L"\n");
        break;
    }

    exit(EXIT_SUCCESS);
}
