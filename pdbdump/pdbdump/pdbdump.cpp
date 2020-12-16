#include <assert.h>
#include <atlcomcli.h>
#include <comdef.h>
#include <regex>
#include <stdio.h>
#include <stdlib.h>

#include "dia2.h"
#include "pdbdump.h"

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
        wprintf(L"  name TEXT NOT NULL\n");
        wprintf(L");\n");
        wprintf(L"\n");
        TOPIC(_, __, SQLITE3_CREATE_TABLE);
        wprintf(L"BEGIN TRANSACTION;\n");
        wprintf(L"\n");
        break;
    }

    for (int i = 1, pdbs = 0; i < argc; i++) {
        OPTION(_, __, OPTION_HANDLER_DUMMY)
        if ((argv[i][1] != '\0') && ((argv[i][0] == '+') || (argv[i][0] == '-'))) {
        } else {
            switch (format) {
            case JSON:
                if (pdbs > 0) {
                    wprintf(L",\n");
                }
                wprintf(L"  {\n");
                wprintf(L"    \"name\": \"%s\",\n", argv[i]);
                break;
            case XML:
                // TODO
                break;
            case SQLITE3:
                break;
            }

            pdbs++;
        }
    }

    return EXIT_SUCCESS;
}
