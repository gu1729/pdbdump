#pragma once

#define FATAL(fmt, ...)                            \
    wprintf(L"ERROR: " L##fmt L"\n", __VA_ARGS__); \
    exit(EXIT_FAILURE);

#define SYMBOL_PROPERTY(A)                         \
    A(access, DWORD, CV_access_e)                  \
    A(addressOffset, DWORD)                        \
    A(addressSection, DWORD)                       \
    A(addressTaken, BOOL)                          \
    A(age, DWORD)                                  \
    A(arrayIndexTypeId, DWORD)                     \
    A(backEndBuild, DWORD)                         \
    A(backEndMajor, DWORD)                         \
    A(backEndMinor, DWORD)                         \
    A(baseDataOffset, DWORD)                       \
    A(baseDataSlot, DWORD)                         \
    A(baseSymbolId, DWORD)                         \
    A(baseType, DWORD, BasicType)                  \
    A(bitPosition, DWORD)                          \
    A(builtInKind, DWORD)                          \
    A(callingConvention, DWORD, CV_call_e)         \
    A(classParentId, DWORD)                        \
    A(code, BOOL)                                  \
    A(compilerGenerated, BOOL)                     \
    A(compilerName, BSTR)                          \
    A(constructor, BOOL)                           \
    A(constType, BOOL)                             \
    A(count, DWORD)                                \
    A(countLiveRanges, DWORD)                      \
    A(customCallingConvention, BOOL)               \
    A(dataKind, DWORD, DataKind)                   \
    A(editAndContinueEnabled, BOOL)                \
    A(farReturn, BOOL)                             \
    A(framePointerPresent, BOOL)                   \
    A(frontEndBuild, DWORD)                        \
    A(frontEndMajor, DWORD)                        \
    A(frontEndMinor, DWORD)                        \
    A(function, BOOL)                              \
    A(guid, GUID)                                  \
    A(hasAlloca, BOOL)                             \
    A(hasAssignmentOperator, BOOL)                 \
    A(hasCastOperator, BOOL)                       \
    A(hasDebugInfo, BOOL)                          \
    A(hasEH, BOOL)                                 \
    A(hasEHa, BOOL)                                \
    A(hasInlAsm, BOOL)                             \
    A(hasLongJump, BOOL)                           \
    A(hasManagedCode, BOOL)                        \
    A(hasNestedTypes, BOOL)                        \
    A(hasSecurityChecks, BOOL)                     \
    A(hasSEH, BOOL)                                \
    A(hasSetJump, BOOL)                            \
    A(hfaFloat, BOOL)                              \
    A(hfaDouble, BOOL)                             \
    A(indirectVirtualBaseClass, BOOL)              \
    A(inlSpec, BOOL)                               \
    A(interruptReturn, BOOL)                       \
    A(intrinsic, BOOL)                             \
    A(intro, BOOL)                                 \
    A(isAcceleratorGroupSharedLocal, BOOL)         \
    A(isAcceleratorPointerTagLiveRange, BOOL)      \
    A(isAcceleratorStubFunction, BOOL)             \
    A(isAggregated, BOOL)                          \
    A(isCTypes, BOOL)                              \
    A(isCVTCIL, BOOL)                              \
    A(isDataAligned, BOOL)                         \
    A(isHLSLData, BOOL)                            \
    A(isHotpatchable, BOOL)                        \
    A(isLTCG, BOOL)                                \
    A(isMatrixRowMajor, BOOL)                      \
    A(isMSILNetmodule, BOOL)                       \
    A(isMultipleInheritance, BOOL)                 \
    A(isNaked, BOOL)                               \
    A(isOptimizedAway, BOOL)                       \
    A(isPointerBasedOnSymbolValue, BOOL)           \
    A(isPointerToDataMember, BOOL)                 \
    A(isPointerToMemberFunction, BOOL)             \
    A(isReturnValue, BOOL)                         \
    A(isSafeBuffers, BOOL)                         \
    A(isSdl, BOOL)                                 \
    A(isSingleInheritance, BOOL)                   \
    A(isSplitted, BOOL)                            \
    A(isStatic, BOOL)                              \
    A(isStripped, BOOL)                            \
    A(isVirtualInheritance, BOOL)                  \
    A(language, DWORD, CV_CFL_LANG)                \
    A(length, ULONGLONG)                           \
    A(lexicalParentId, DWORD)                      \
    A(libraryName, BSTR)                           \
    A(liveRangeLength, ULONGLONG)                  \
    A(liveRangeStartAddressOffset, DWORD)          \
    A(liveRangeStartAddressSection, DWORD)         \
    A(liveRangeStartRelativeVirtualAddress, DWORD) \
    A(localBasePointerRegisterId, DWORD)           \
    A(locationType, DWORD, LocationType)           \
    A(lowerBoundId, DWORD)                         \
    A(machineType, DWORD)                          \
    A(managed, BOOL)                               \
    A(memorySpaceKind, DWORD)                      \
    A(msil, BOOL)                                  \
    A(name, BSTR)                                  \
    A(nested, BOOL)                                \
    A(noInline, BOOL)                              \
    A(noReturn, BOOL)                              \
    A(noStackOrdering, BOOL)                       \
    A(notReached, BOOL)                            \
    A(numberOfAcceleratorPointerTags, DWORD)       \
    A(numberOfColumns, DWORD)                      \
    A(numberOfModifiers, DWORD)                    \
    A(numberOfRegisterIndices, DWORD)              \
    A(numberOfRows, DWORD)                         \
    A(objectFileName, BSTR)                        \
    A(oemId, DWORD)                                \
    A(oemSymbolId, DWORD)                          \
    A(offset, LONG)                                \
    A(offsetInUdt, DWORD)                          \
    A(optimizedCodeDebugInfo, BOOL)                \
    A(overloadedOperator, BOOL)                    \
    A(packed, BOOL)                                \
    A(paramBasePointerRegisterId, DWORD)           \
    A(platform, DWORD, CV_CPU_TYPE_e)              \
    A(pure, BOOL)                                  \
    A(rank, DWORD)                                 \
    A(reference, BOOL)                             \
    A(registerId, DWORD)                           \
    A(registerType, DWORD)                         \
    A(relativeVirtualAddress, DWORD)               \
    A(restrictedType, BOOL)                        \
    A(RValueReference, BOOL)                       \
    A(samplerSlot, DWORD)                          \
    A(scoped, BOOL)                                \
    A(sealed, BOOL)                                \
    A(signature, DWORD)                            \
    A(sizeInUdt, DWORD)                            \
    A(slot, DWORD)                                 \
    A(sourceFileName, BSTR)                        \
    A(stride, DWORD)                               \
    A(subTypeId, DWORD)                            \
    A(symbolsFileName, BSTR)                       \
    A(symIndexId, DWORD)                           \
    A(symTag, DWORD, SymTagEnum)                   \
    A(targetOffset, DWORD)                         \
    A(targetRelativeVirtualAddress, DWORD)         \
    A(targetSection, DWORD)                        \
    A(targetVirtualAddress, ULONGLONG)             \
    A(textureSlot, DWORD)                          \
    A(thisAdjust, LONG)                            \
    A(thunkOrdinal, DWORD)                         \
    A(timeStamp, DWORD)                            \
    A(token, DWORD)                                \
    A(typeId, DWORD)                               \
    A(uavSlot, DWORD)                              \
    A(udtKind, DWORD, UdtKind)                     \
    A(unalignedType, BOOL)                         \
    A(undecoratedName, BSTR)                       \
    A(unmodifiedTypeId, DWORD)                     \
    A(upperBoundId, DWORD)                         \
    A(value, VARIANT)                              \
    A(virtual, BOOL)                               \
    A(virtualAddress, ULONGLONG)                   \
    A(virtualBaseClass, BOOL)                      \
    A(virtualBaseDispIndex, DWORD)                 \
    A(virtualBaseOffset, DWORD)                    \
    A(virtualBasePointerOffset, LONG)              \
    A(virtualTableShapeId, DWORD)                  \
    A(volatileType, BOOL)

#define SQLITE3_TYPE_BOOL L"INTEGER"
#define SQLITE3_TYPE_DWORD L"INTEGER"
#define SQLITE3_TYPE_LONG L"INTEGER"
#define SQLITE3_TYPE_ULONGLONG L"INTEGER"
#define SQLITE3_TYPE_GUID L"TEXT"
#define SQLITE3_TYPE_BSTR L"TEXT"
#define SQLITE3_TYPE_VARIANT L"TEXT"

#define SQLITE3_CREATE_COLUMN(x, type, ...) \
    wprintf(L"  " L## #x L" " SQLITE3_TYPE_##type L" NOT NULL,\n");

#define DEFINE_PROPERTY_BOOL(x) static BOOL value = 0;
#define DEFINE_PROPERTY_DWORD(x) static DWORD value = 0;
#define DEFINE_PROPERTY_LONG(x) static LONG value = 0;
#define DEFINE_PROPERTY_ULONGLONG(x) static ULONGLONG value = 0;
#define DEFINE_PROPERTY_GUID(x) static GUID value;
#define DEFINE_PROPERTY_VARIANT(x) static VARIANT value;
#define DEFINE_PROPERTY_BSTR(x) static BSTR value;

enum class Format {
    JSON,
    XML,
    SQLITE3
};

#define DUMP_PROPERTY_BOOL(x)                             \
    switch (format) {                                     \
    case Format::JSON:                                    \
        wprintf(L", \"" L## #x L"\" : %d", value);        \
        break;                                            \
    case Format::XML:                                     \
        wprintf(L"<" L## #x L">%d</" L## #x L">", value); \
        break;                                            \
    case Format::SQLITE3:                                 \
        wprintf(L", %d", value);                          \
        break;                                            \
    }

#define DUMP_PROPERTY_DWORD(x)                             \
    switch (format) {                                      \
    case Format::JSON:                                     \
        wprintf(L", \"" L## #x L"\" : %lu", value);        \
        break;                                             \
    case Format::XML:                                      \
        wprintf(L"<" L## #x L">%lu</" L## #x L">", value); \
        break;                                             \
    case Format::SQLITE3:                                  \
        wprintf(L", %lu", value);                          \
        break;                                             \
    }

#define DUMP_PROPERTY_LONG(x)                              \
    switch (format) {                                      \
    case Format::JSON:                                     \
        wprintf(L", \"" L## #x L"\" : %ld", value);        \
        break;                                             \
    case Format::XML:                                      \
        wprintf(L"<" L## #x L">%ld</" L## #x L">", value); \
        break;                                             \
    case Format::SQLITE3:                                  \
        wprintf(L", %ld", value);                          \
        break;                                             \
    }

#define DUMP_PROPERTY_ULONGLONG(x)                          \
    switch (format) {                                       \
    case Format::JSON:                                      \
        wprintf(L", \"" L## #x L"\" : %llu", value);        \
        break;                                              \
    case Format::XML:                                       \
        wprintf(L"<" L## #x L">%llu</" L## #x L">", value); \
        break;                                              \
    case Format::SQLITE3:                                   \
        wprintf(L", %llu", value);                          \
        break;                                              \
    }

#define DUMP_PROPERTY_GUID(x)              \
    switch (format) {                      \
    case Format::JSON:                     \
        wprintf(L", \"" L## #x L"\" : 0"); \
        break;                             \
    case Format::XML:                      \
        break;                             \
    case Format::SQLITE3:                  \
        wprintf(L", \"\"");                \
        break;                             \
    }

#define DUMP_PROPERTY_VARIANT(x)           \
    switch (format) {                      \
    case Format::JSON:                     \
        wprintf(L", \"" L## #x L"\" : 0"); \
        break;                             \
    case Format::XML:                      \
        break;                             \
    case Format::SQLITE3:                  \
        wprintf(L", \"\"");                \
        break;                             \
    }

#define DUMP_PROPERTY_BSTR(x)                                          \
    switch (format) {                                                  \
    case Format::JSON:                                                 \
        wprintf(L", \"" L## #x L"\" : \"%ls\"", value);                \
        break;                                                         \
    case Format::XML:                                                  \
        wprintf(L"<" L## #x L"><![CDATA[%ls]]></" L## #x L">", value); \
        break;                                                         \
    case Format::SQLITE3:                                              \
        wprintf(L", \"%ls\"", value);                                  \
        break;                                                         \
    }

#define DUMP_PROPERTY(x, type, ...)                       \
    {                                                     \
        DEFINE_PROPERTY_##type(x);                        \
        if (FAILED(symbol->get_##x(&value))) {            \
            FATAL("Could not get property " L## #x L"."); \
        }                                                 \
        DUMP_PROPERTY_##type(x);                          \
    }

#define DUMP_PROPERTY_NAME(x, ...) \
    wprintf(L", " L## #x);\
