/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <atlcomcli.h>
#include "dia2.h"

/* helper */
#define FATAL(fmt, ...) wprintf(L ## fmt, __VA_ARGS__); return EXIT_FAILURE

/* main entry point */
int wmain(int argc, wchar_t* argv[]) {

  /* local variables */
  CComPtr<IDiaDataSource> source;

  /* initialize */
  HRESULT hr = CoInitialize(NULL);

  /* access source */
  hr = CoCreateInstance(CLSID_DiaSource,
    NULL,
    CLSCTX_INPROC_SERVER,
    __uuidof(IDiaDataSource),
    (void**)& source);

  if (FAILED(hr)) {
    FATAL("sasaas");
  }

  return EXIT_SUCCESS;
}
