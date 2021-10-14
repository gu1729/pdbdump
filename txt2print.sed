# escape double quotes
s/"/\\"/g

# add wprintf
s/^/wprintf(L"/
s/$/\\n");/

# remove unnecessary spaces
s/L" *\\n/L"\\n/
