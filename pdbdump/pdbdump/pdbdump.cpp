#include <assert.h>
#include <atlcomcli.h>
#include <comdef.h>
#include <regex>
#include <stdio.h>
#include <stdlib.h>

#include "dia2.h"
#include "pdbdump.h"

#define FATAL(fmt, ...)                        \
    wprintf(L"ERROR: " fmt "\n", __VA_ARGS__); \
    exit(EXIT_FAILURE);

void help()
{
    wprintf(L"HELP!\n");
}

typedef enum _e_FORMAT {
    JSON,
    XML,
    SQLITE3
} FORMAT;

static bool show_help = false;
static bool use_names = false;
static FORMAT format = JSON;
TOPIC(_, __, DEFINE_DUMP_ALL_PROPERTIES);
TOPIC(_, __, DEFINE_DUMP_TOPIC);

int wmain(int argc, wchar_t* argv[])
{

    HRESULT hr = CoInitialize(NULL);

    for (int i = 1; i < argc; i++) {
        OPTION(_, __, OPTION_HANDLER)
        if ((argv[i][1] != '\0') && ((argv[i][0] == '+') || (argv[i][0] == '-'))) {
            bool sign = argv[i][0] == '+' ? true : false;
            std::wregex re(&argv[i][1]);
            std::wcmatch m;
            TOPIC(_, __, MATCH_ALL_PROPERTIES);
        }
    }
    TOPIC(_, __, CALC_DUMP_TOPIC);

    if (show_help == true) {
        help();
        return EXIT_SUCCESS;
    }

    switch (format) {
    case JSON:
        wprintf(L"[\n");
        break;
    case XML:
        wprintf(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n");
        wprintf(L"<pdbs>\n");
        break;
    case SQLITE3:
        wprintf(L"CREATE TABLE pdb (\n");
        wprintf(L"  id INTEGER NOT NULL,\n");
        wprintf(L"  name TEXT NOT NULL,\n");
        wprintf(L"  PRIMARY KEY (id)\n");
        wprintf(L");\n");
        wprintf(L"\n");
        TOPIC(_, __, SQLITE3_CREATE_TABLE);
        wprintf(L"BEGIN TRANSACTION;\n");
        wprintf(L"\n");
        break;
    }

    DWORD pdbId = 0;
    for (int i = 1; i < argc; i++) {
        OPTION(_, __, OPTION_HANDLER_DUMMY)
        if ((argv[i][1] != '\0') && ((argv[i][0] == '+') || (argv[i][0] == '-'))) {
        } else {
            pdbId++;
            switch (format) {
            case JSON:
                if (pdbId > 1) {
                    wprintf(L",\n");
                }
                wprintf(L"  {\n");
                wprintf(L"    \"name\": \"%s\",\n", argv[i]);
                break;
            case XML:
                wprintf(L"  <pdb>\n");
                wprintf(L"    <name><![CDATA[%s]]></name>\n", argv[i]);
                break;
            case SQLITE3:
                wprintf(L"INSERT INTO pdb (id, name) VALUES (%lu, \"%s\");\n", pdbId, argv[i]);
                break;
            }
            CComPtr<IDiaDataSource> source;
            if (FAILED(CoCreateInstance(CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&source))) {
                FATAL("Could not initialize CLSID_DiaSource. Please register msdiaXXX.dll.");
            }
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

            ULONG topics = 0;

            if (dump_SYMBOL) {
                topics++;

                switch (format) {
                case JSON:
                    if (topics > 1) {
                        wprintf(L",\n");
                    }
                    wprintf(L"    \"symbols\" : [\n");
                    break;
                case XML:
                    break;
                case SQLITE3:
                    break;
                }

                CComPtr<IDiaEnumSymbols> enumSymbols;
                CComPtr<IDiaSymbol> symbol;
                ULONG celt;
                hr = global->findChildren(SymTagNull, NULL, nsNone, &enumSymbols);
                if (SUCCEEDED(hr)) {
                    ULONG symbols = 0;
                    while (SUCCEEDED(hr = enumSymbols->Next(1, &symbol, &celt)) && celt == 1) {
                        symbols++;
                        switch (format) {
                        case JSON:
                            if (symbols > 1) {
                                wprintf(L",\n");
                            }
                            wprintf(L"      {\"%s\" : %lu", L"pdbId", pdbId);
                            break;
                        case XML:
                            break;
                        case SQLITE3:
                            break;
                        }
                        SYMBOL_PROPERTY(SYMBOL, symbol, DO_DUMP_PROPERTY);
                        switch (format) {
                        case JSON:
                            wprintf(L"}");
                            break;
                        case XML:
                            break;
                        case SQLITE3:
                            break;
                        }
                        symbol = 0;
                    }
                }
                switch (format) {
                case JSON:
                    wprintf(L"\n    ]");
                    break;
                case XML:
                    break;
                case SQLITE3:
                    break;
                }
            }

            switch (format) {
            case JSON:
                wprintf(L"\n  }\n");
                break;
            case XML:
                wprintf(L"  </pdb>\n");
                break;
            case SQLITE3:
                break;
            }
        }
    }

    switch (format) {
    case JSON:
        wprintf(L"]\n");
        break;
    case XML:
        wprintf(L"</pdbs>\n");
        break;
    case SQLITE3:
        wprintf(L"\nCOMMIT;\n");
        wprintf(L"\n");
        break;
    }

    exit(EXIT_SUCCESS);
}
