#include <assert.h>
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
#define dump(...)                          \
    {                                      \
        for (int i = 0; i < indent; i++) { \
            putwchar(' ');                 \
        }                                  \
        wprintf(__VA_ARGS__);              \
    }

inline int myDebugBreak(int)
{
    DebugBreak();
    return 0;
}
#define MAXELEMS(x) (sizeof(x) / sizeof(x[0]))
#define SafeDRef(a, i) ((i < MAXELEMS(a)) ? a[i] : a[myDebugBreak(i)])

void help()
{
    wprintf(L"HELP!\n");
}

const wchar_t* const rgTags[] = {
    L"(SymTagNull)",
    L"Executable (Global)",
    L"Compiland",
    L"CompilandDetails",
    L"CompilandEnv",
    L"Function",
    L"Block",
    L"Data",
    L"Annotation",
    L"Label",
    L"PublicSymbol",
    L"UserDefinedType",
    L"Enum",
    L"FunctionType",
    L"PointerType",
    L"ArrayType",
    L"BaseType",
    L"Typedef",
    L"BaseClass",
    L"Friend",
    L"FunctionArgType",
    L"FuncDebugStart",
    L"FuncDebugEnd",
    L"UsingNamespace",
    L"VTableShape",
    L"VTable",
    L"Custom",
    L"Thunk",
    L"CustomType",
    L"ManagedType",
    L"Dimension",
    L"CallSite",
    L"InlineSite",
    L"BaseInterface",
    L"VectorType",
    L"MatrixType",
    L"HLSLType",
    L"Caller",
    L"Callee",
    L"Export",
    L"HeapAllocationSite",
    L"CoffGroup",
    L"Inlinee",
};

class Dumper {
protected:
    int indent = 0;

public:
    void push() { indent += 2; }
    void pop() { indent -= 2; }
    virtual void comment(wchar_t* s) = 0;
    virtual void attribute(const wchar_t* name, ULONG value, bool separator) = 0;
    virtual void attribute(const wchar_t* name, ULONGLONG value, bool separator) = 0;
    virtual void attribute(const wchar_t* name, wchar_t* value, bool separator) = 0;
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void pdbSeparator() = 0;
    virtual void pdbStart(ULONG id, wchar_t* name) = 0;
    virtual void pdbEnd() = 0;
    virtual void listStart(const wchar_t* name) = 0;
    virtual void listEnd(const wchar_t* name) = 0;
    virtual void symbolSeparator() = 0;
    virtual void symbolStart(ULONG pdbId) = 0;
    virtual void symbolEnd() = 0;
};

class JSONDumper : public Dumper {
public:
    JSONDumper() { }
    void comment(wchar_t* s) { }
    void attribute(const wchar_t* name, ULONG value, bool separator)
    {
        dump(L"\"%s\" : \"%lu\"", name, value);
        if (separator) {
            wprintf(L",");
        }
        wprintf(L"\n");
    }
    void attribute(const wchar_t* name, ULONGLONG value, bool separator)
    {
        dump(L"\"%s\" : \"%llu\"", name, value);
        if (separator) {
            wprintf(L",");
        }
        wprintf(L"\n");
    }
    void attribute(const wchar_t* name, wchar_t* value, bool separator)
    {
        dump(L"\"%s\" : \"%s\"", name, value);
        if (separator) {
            wprintf(L",");
        }
        wprintf(L"\n");
    }
    void start() { dump(L"[\n"); }
    void end() { dump(L"]\n"); }
    void pdbSeparator() { dump(L",\n"); }
    void pdbStart(ULONG id, wchar_t* name)
    {
        wprintf(L"  {\n");
        wprintf(L"    \"name\": \"%s\",\n", name);
    }
    void pdbEnd() { wprintf(L"  }\n"); }
    void listStart(const wchar_t* name) { dump(L"\"%s\" : [\n", name); }
    void listEnd(const wchar_t* name) { dump(L"]\n"); }
    void symbolSeparator() { dump(L",\n"); }
    void symbolStart(ULONG pdbId) { dump(L"{\n"); }
    void symbolEnd() { dump(L"}\n"); }
};

class XMLDumper : public Dumper {
public:
    XMLDumper() { }
    void comment(wchar_t* s) { dump(L"<!-- %s -->\n", s); }
    void attribute(const wchar_t* name, ULONG value, bool separator) { }
    void attribute(const wchar_t* name, ULONGLONG value, bool separator) { }
    void attribute(const wchar_t* name, wchar_t* value, bool separator) { }
    void start()
    {
        dump(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n");
        dump(L"<pdbs>\n");
    }
    void end() { dump(L"</pdbs>\n"); }
    void pdbSeparator() { }
    void pdbStart(ULONG id, wchar_t* name) { }
    void pdbEnd() { }
    void listStart(const wchar_t* name) { }
    void listEnd(const wchar_t* name) { }
    void symbolSeparator() { }
    void symbolStart(ULONG pdbId) { }
    void symbolEnd() { }
};

class SQLite3Dumper : public Dumper {
public:
    SQLite3Dumper() { }
    void comment(wchar_t* s)
    {
        wprintf(L"--\n");
        wprintf(L"-- %s\n", s);
        wprintf(L"--\n");
        wprintf(L"\n");
    }
    void attribute(const wchar_t* name, ULONG value, bool separator)
    {
        wprintf(L"%lu", value);
        if (separator) {
            wprintf(L", ");
        }
    }
    void attribute(const wchar_t* name, ULONGLONG value, bool separator)
    {
        wprintf(L"%llu", value);
        if (separator) {
            wprintf(L", ");
        }
    }
    void attribute(const wchar_t* name, wchar_t* value, bool separator)
    {
        wprintf(L"\"%s\"", value);
        if (separator) {
            wprintf(L", ");
        }
    }
    void start()
    {
        comment((wchar_t*)L"create tables");
        wprintf(L"CREATE TABLE pdb (\n");
        wprintf(L"  id INTEGER NOT NULL,\n");
        wprintf(L"  name TEXT NOT NULL\n");
        wprintf(L");\n");
        wprintf(L"\n");
        wprintf(L"CREATE TABLE symbol (\n");
        wprintf(L"  pdbId INTEGER NOT NULL,\n");
        wprintf(L"  symIndexId INTEGER NOT NULL,\n");
        wprintf(L"  name TEXT NOT NULL,\n");
        wprintf(L"  symTag TEXT NOT NULL,\n");
        wprintf(L"  length INTEGER NOT NULL\n");
        wprintf(L");\n");
        wprintf(L"\n");
        comment((wchar_t*)L"start transaction");
        wprintf(L"BEGIN TRANSACTION;\n");
        wprintf(L"\n");
    }
    void end()
    {
        wprintf(L"\n");
        comment((wchar_t*)L"end transaction");
        wprintf(L"COMMIT;\n");
        wprintf(L"\n");
    }
    void pdbSeparator() { }
    void pdbStart(ULONG id, wchar_t* name)
    {
        wprintf(L"INSERT INTO pdb (id, name) VALUES (%lu, '%s');\n", id, name);
    }
    void pdbEnd() { }
    void listStart(const wchar_t* name) { }
    void listEnd(const wchar_t* name) { }
    void symbolSeparator() { }
    void symbolStart(ULONG pdbId)
    {
        wprintf(L"INSERT INTO symbol (pdbId, symIndexId, name, symTag, length) VALUES (%lu, ", pdbId);
    }
    void symbolEnd() { wprintf(L");\n"); }
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

    HRESULT hr = CoInitialize(NULL);

    dumper->start();
    dumper->push();
    for (int idx = start_idx; idx < argc; idx++) {
        if (idx > start_idx) {
            dumper->pdbSeparator();
        }
        dumper->comment(argv[idx]);
        ULONG pdbId = (ULONG)(idx - start_idx + 1);
        dumper->pdbStart(pdbId, argv[idx]);
        dumper->push();
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
        dumper->listStart(L"symbols");
        dumper->push();
        CComPtr<IDiaEnumSymbols> pEnum;
        CComPtr<IDiaSymbol> pSymbol;
        ULONG celt;
        hr = global->findChildren(SymTagNull, NULL, nsNone, &pEnum);
        if (SUCCEEDED(hr)) {
            ULONG symbols = 0;
            while (SUCCEEDED(hr = pEnum->Next(1, &pSymbol, &celt)) && celt == 1) {
                if (symbols > 0) {
                    dumper->symbolSeparator();
                }
                dumper->symbolStart(pdbId);
                dumper->push();
                DWORD symIndexId = 0;
                if (FAILED(pSymbol->get_symIndexId(&symIndexId))) {
                    FATAL("Could not get symbol symIndexId.")
                }
                dumper->attribute(L"symIndexId", symIndexId, true);
                BSTR name;
                if (FAILED(pSymbol->get_name(&name))) {
                    FATAL("Could not get symbol name.");
                }
                dumper->attribute(L"name", name, true);
                SysFreeString(name);
                DWORD symTag = 0;
                if (FAILED(pSymbol->get_symTag(&symTag))) {
                    FATAL("Could not get symbol symTag.")
                }
                dumper->attribute(L"symTag", (wchar_t*)SafeDRef(rgTags, symTag), true);
                ULONGLONG length = 0;
                if (FAILED(pSymbol->get_length(&length))) {
                    FATAL("Could not get symbol length.")
                }
                dumper->attribute(L"length", length, false);
                dumper->pop();
                dumper->symbolEnd();
                pSymbol = 0;
                symbols++;
            }
        }
        dumper->pop();
        dumper->listEnd(L"symbols");
        dumper->pop();
        dumper->pdbEnd();
    }
    dumper->pop();
    dumper->end();

    return EXIT_SUCCESS;
}
