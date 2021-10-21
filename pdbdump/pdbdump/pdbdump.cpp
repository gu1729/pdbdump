#include <assert.h>
#include <atlcomcli.h>
#include <comdef.h>
#include <regex>
#include <stdio.h>
#include <stdlib.h>

#include "dia2.h"
#include "pdbdump.h"

static Format format = Format::JSON;
static bool showHelp = false;
static bool showVersion = false;
static bool showLicense = false;
static bool showList = false;
TOPIC(_, __, DEFINE_DUMP_ALL_PROPERTIES);
TOPIC(_, __, DEFINE_DUMP_TOPIC);

void wprint_string_bstr(Format format, BSTR value) {
    int len = SysStringLen(value);
    WCHAR s[2] = {0, 0};
    for (int i = 0; i < len; i++) {
        s[0] = value[i];
        switch (format) {
        case Format::JSON:
            if ((s[0] == '"') || (s[0] == '\\') || ('\x00' <= s[0] && s[0] <= '\x1f') || (s[0] >= 128)) {
                wprintf(L"\\u%04x", s[0]);
            } else {
                wprintf(L"%s", s);
            }
            break;
        case Format::XML:
            wprintf(L"%s", s);
            break;
        case Format::SQLITE3:
            wprintf(L"%s", s);
            break;
        case Format::CSV:
            wprintf(L"%s", s);
            break;
        }
    }
}

void wprint_string_wchar(Format format, WCHAR* value) {
    BSTR bstr = SysAllocString(value);
    wprint_string_bstr(format, bstr);
    SysFreeString(bstr);
}

int wmain(int argc, wchar_t* argv[])
{

    ULONG celt;
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

    if (showHelp == true) {
#include "help.h"
        exit(EXIT_SUCCESS);
    }

    if (showLicense == true) {
#include "license.h"
        exit(EXIT_SUCCESS);
    }

    if (showVersion == true) {
        wprintf(VERSION "\n");
        exit(EXIT_SUCCESS);
    }

    if (showList == true) {
        TOPIC(_, __, LIST_ALL_PROPERTIES);
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
        SYMBOL_PROPERTY(SYMBOL, __, SQLITE3_CREATE_COLUMN);
        wprintf(L"  FOREIGN KEY (pdbId) REFERENCES pdb (id)\n");
        wprintf(L");\n");
        wprintf(L"\n");
        wprintf(L"BEGIN TRANSACTION;\n");
        wprintf(L"\n");
        break;
    case Format::CSV:
        wprintf(L"\"pdb\"");
        SYMBOL_PROPERTY(SYMBOL, __, CSV_CREATE_COLUMN);
        wprintf(L"\n");
        break;
    }

    ULONG pdbId = 0;
    for (int i = 1; i < argc; i++) {
        OPTION(_, __, OPTION_HANDLER_DUMMY)
        if ((argv[i][1] != '\0') && ((argv[i][0] == '+') || (argv[i][0] == '-'))) {
        } else {
            pdbId++;

            CComPtr<IDiaDataSource> source;
            if (FAILED(CoCreateInstance(CLSID_DiaSource, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&source))) {
                FATAL("Could not initialize CLSID_DiaSource. Please register msdiaXXX.dll.");
            }
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
                wprintf(L"    \"name\" : \"");
                wprint_string_wchar(Format::JSON, argv[i]);
                wprintf(L"\",\n");
                break;
            case Format::XML:
                wprintf(L"  <pdb>\n");
                wprintf(L"    <name><![CDATA[%ls]]></name>\n", argv[i]);
                break;
            case Format::SQLITE3:
                wprintf(L"INSERT INTO pdb (id, name) VALUES (%lu, \"%s\");\n", pdbId, argv[i]);
                break;
            case Format::CSV:
                break;
            }

            ULONG topics = 0;

            if (dump_SYMBOL == true) {
                topics++;

                switch (format) {
                case Format::JSON:
                    if (topics > 1) {
                        wprintf(L",\n");
                    }
                    wprintf(L"    \"symbols\" : [\n");
                    break;
                case Format::XML:
                    break;
                case Format::SQLITE3:
                    break;
                case Format::CSV:
                    break;
                }
                CComPtr<IDiaEnumSymbols> enumSymbols;
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
                            SYMBOL_PROPERTY(SYMBOL, __, SERIALIZE_PROPERTY_NAME);
                            wprintf(L") VALUES (%lu", pdbId);
                            break;
                        case Format::CSV:
                            wprintf(L"%d", i);
                            break;
                        }
                        SYMBOL_PROPERTY(SYMBOL, __, SERIALIZE_PROPERTY);
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
                        case Format::CSV:
                            wprintf(L"\n");
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
                    break;
                case Format::XML:
                    break;
                case Format::SQLITE3:
                    break;
                }
            }

            switch (format) {
            case Format::JSON:
                wprintf(L"\n  }");
                break;
            case Format::XML:
                wprintf(L"  </pdb>\n");
                break;
            case Format::SQLITE3:
                wprintf(L"\n");
                break;
            case Format::CSV:
                wprintf(L"\n");
                break;
            }
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
    case Format::CSV:
        break;
    }

    exit(EXIT_SUCCESS);
}
