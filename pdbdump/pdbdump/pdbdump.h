#pragma once

#define TOPIC(_, __, A)        \
    A(_, __, SEGMENT, segment) \
    A(_, __, SYMBOL, symbol)

#define SEGMENT_PROPERTY(_, __, A)                 \
    A(_, __, addressSection, false, DWORD)         \
    A(_, __, execute, false, BOOL)                 \
    A(_, __, frame, false, DWORD)                  \
    A(_, __, length, false, DWORD)                 \
    A(_, __, offset, false, DWORD)                 \
    A(_, __, read, false, BOOL)                    \
    A(_, __, relativeVirtualAddress, false, DWORD) \
    A(_, __, virtualAddress, false, ULONGLONG)     \
    A(_, __, write, false, BOOL)

#define SYMBOL_PROPERTY(_, __, A)                                \
    A(_, __, access, false, DWORD, CV_access_e)                  \
    A(_, __, addressOffset, false, DWORD)                        \
    A(_, __, addressSection, false, DWORD)                       \
    A(_, __, addressTaken, false, BOOL)                          \
    A(_, __, age, false, DWORD)                                  \
    A(_, __, arrayIndexTypeId, false, DWORD)                     \
    A(_, __, backEndBuild, false, DWORD)                         \
    A(_, __, backEndMajor, false, DWORD)                         \
    A(_, __, backEndMinor, false, DWORD)                         \
    A(_, __, baseDataOffset, false, DWORD)                       \
    A(_, __, baseDataSlot, false, DWORD)                         \
    A(_, __, baseSymbolId, false, DWORD)                         \
    A(_, __, baseType, false, DWORD, BasicType)                  \
    A(_, __, bitPosition, false, DWORD)                          \
    A(_, __, buildInKind, false, DWORD)                          \
    A(_, __, callingConvention, false, DWORD, CV_call_e)         \
    A(_, __, classParentId, false, DWORD)                        \
    A(_, __, code, false, BOOL)                                  \
    A(_, __, compilerGenerated, false, BOOL)                     \
    A(_, __, compilerName, false, BSTR)                          \
    A(_, __, constructor, false, BOOL)                           \
    A(_, __, constType, false, BOOL)                             \
    A(_, __, count, false, DWORD)                                \
    A(_, __, countLiveRanges, false, DWORD)                      \
    A(_, __, customCallingConvention, false, BOOL)               \
    A(_, __, dataKind, false, DWORD, DataKind)                   \
    A(_, __, editAndContinueEnabled, false, BOOL)                \
    A(_, __, farReturn, false, BOOL)                             \
    A(_, __, framePointerPresent, false, BOOL)                   \
    A(_, __, frontEndBuild, false, DWORD)                        \
    A(_, __, frontEndMajor, false, DWORD)                        \
    A(_, __, frontEndMinor, false, DWORD)                        \
    A(_, __, function, false, BOOL)                              \
    A(_, __, guid, false, GUID)                                  \
    A(_, __, hasAlloca, false, BOOL)                             \
    A(_, __, hasAssignmentOperator, false, BOOL)                 \
    A(_, __, hasCastOperator, false, BOOL)                       \
    A(_, __, hasDebugInfo, false, BOOL)                          \
    A(_, __, hasEH, false, BOOL)                                 \
    A(_, __, hasEHa, false, BOOL)                                \
    A(_, __, hasInlAsm, false, BOOL)                             \
    A(_, __, hasLongJump, false, BOOL)                           \
    A(_, __, hasManagedCode, false, BOOL)                        \
    A(_, __, hasNestedTypes, false, BOOL)                        \
    A(_, __, hasSecurityChecks, false, BOOL)                     \
    A(_, __, hasSEH, false, BOOL)                                \
    A(_, __, hasSetJump, false, BOOL)                            \
    A(_, __, hfaFloat, false, BOOL)                              \
    A(_, __, hfaDouble, false, BOOL)                             \
    A(_, __, indirectVirtualBaseClass, false, BOOL)              \
    A(_, __, inlSpec, false, BOOL)                               \
    A(_, __, interruptReturn, false, BOOL)                       \
    A(_, __, intrinsic, false, BOOL)                             \
    A(_, __, intro, false, BOOL)                                 \
    A(_, __, isAcceleratorGroupSharedLocal, false, BOOL)         \
    A(_, __, isAcceleratorPointerTagLiveRange, false, BOOL)      \
    A(_, __, isAcceleratorStubFunction, false, BOOL)             \
    A(_, __, isAggregated, false, BOOL)                          \
    A(_, __, isCTypes, false, BOOL)                              \
    A(_, __, isCVTCIL, false, BOOL)                              \
    A(_, __, isDataAligned, false, BOOL)                         \
    A(_, __, isHLSLData, false, BOOL)                            \
    A(_, __, isHotpatchable, false, BOOL)                        \
    A(_, __, iSLTCG, false, BOOL)                                \
    A(_, __, isMatrixRowMajor, false, BOOL)                      \
    A(_, __, isMSILNetmodule, false, BOOL)                       \
    A(_, __, isMultipleInheritance, false, BOOL)                 \
    A(_, __, isNaked, false, BOOL)                               \
    A(_, __, isOptimizedAway, false, BOOL)                       \
    A(_, __, isPointerBasedOnSymbolValue, false, BOOL)           \
    A(_, __, isPointerToDataMember, false, BOOL)                 \
    A(_, __, isPointerToMemberFunction, false, BOOL)             \
    A(_, __, isReturnValue, false, BOOL)                         \
    A(_, __, isSafeBuffers, false, BOOL)                         \
    A(_, __, isSdl, false, BOOL)                                 \
    A(_, __, isSingleInheritance, false, BOOL)                   \
    A(_, __, isSplitted, false, BOOL)                            \
    A(_, __, isStatic, false, BOOL)                              \
    A(_, __, isStripped, false, BOOL)                            \
    A(_, __, isVirtualInheritance, false, BOOL)                  \
    A(_, __, language, false, DWORD, CV_CFL_LANG)                \
    A(_, __, length, false, ULONGLONG)                           \
    A(_, __, lexicalParentId, false, DWORD)                      \
    A(_, __, libraryName, false, BSTR)                           \
    A(_, __, liveRangeLength, false, ULONGLONG)                  \
    A(_, __, liveRangeStartAddressOffset, false, DWORD)          \
    A(_, __, liveRangeStartAddressSection, false, DWORD)         \
    A(_, __, liveRangeStartRelativeVirtualAddress, false, DWORD) \
    A(_, __, localBasePointerRegisterId, false, DWORD)           \
    A(_, __, locationType, false, DWORD, LocationType)           \
    A(_, __, lowerBoundId, false, DWORD)                         \
    A(_, __, machineType, false, DWORD)                          \
    A(_, __, managed, false, BOOL)                               \
    A(_, __, memorySpaceKind, false, DWORD)                      \
    A(_, __, msil, false, BOOL)                                  \
    A(_, __, name, false, BSTR)                                  \
    A(_, __, nested, false, BOOL)                                \
    A(_, __, noInline, false, BOOL)                              \
    A(_, __, noReturn, false, BOOL)                              \
    A(_, __, noStackOrdering, false, BOOL)                       \
    A(_, __, notReached, false, BOOL)                            \
    A(_, __, numberOfAcceleratorPointerTags, false, DWORD)       \
    A(_, __, numberOfColumns, false, DWORD)                      \
    A(_, __, numberOfModifiers, false, DWORD)                    \
    A(_, __, numberOfRegisterIndices, false, DWORD)              \
    A(_, __, numberOfRows, false, DWORD)                         \
    A(_, __, objectFilename, false, BSTR)                        \
    A(_, __, oemId, false, DWORD)                                \
    A(_, __, oemSymbolId, false, DWORD)                          \
    A(_, __, offset, false, LONG)                                \
    A(_, __, offsetInUdt, false, DWORD)                          \
    A(_, __, optimizedCodeDebugInfo, false, BOOL)                \
    A(_, __, overloadedOperator, false, BOOL)                    \
    A(_, __, packed, false, BOOL)                                \
    A(_, __, paramBasePointerRegisterId, false, DWORD)           \
    A(_, __, platform, false, DWORD, CV_CPU_TYPE_e)              \
    A(_, __, pure, false, BOOL)                                  \
    A(_, __, rank, false, DWORD)                                 \
    A(_, __, reference, false, BOOL)                             \
    A(_, __, registerId, false, DWORD)                           \
    A(_, __, registerType, false, DWORD)                         \
    A(_, __, relativeVirtualAddress, false, DWORD)               \
    A(_, __, restrictedType, false, BOOL)                        \
    A(_, __, RValueReference, false, BOOL)                       \
    A(_, __, samplerSlot, false, DWORD)                          \
    A(_, __, scoped, false, BOOL)                                \
    A(_, __, sealed, false, BOOL)                                \
    A(_, __, signature, false, DWORD)                            \
    A(_, __, sizeInUdt, false, DWORD)                            \
    A(_, __, slot, false, DWORD)                                 \
    A(_, __, sourceFileName, false, BSTR)                        \
    A(_, __, stride, false, DWORD)                               \
    A(_, __, subTypeId, false, DWORD)                            \
    A(_, __, symbolsFileName, false, BSTR)                       \
    A(_, __, symIndexId, true, DWORD)                            \
    A(_, __, symTag, true, DWORD, SymTagEnum)                    \
    A(_, __, targetOffset, false, DWORD)                         \
    A(_, __, targetRelativeVirtualAddress, false, DWORD)         \
    A(_, __, targetSection, false, DWORD)                        \
    A(_, __, targetVirtualAddress, false, ULONGLONG)             \
    A(_, __, textureSlot, false, DWORD)                          \
    A(_, __, thisAdjust, false, LONG)                            \
    A(_, __, thunkOrdinal, false, DWORD)                         \
    A(_, __, timeStamp, false, DWORD)                            \
    A(_, __, token, false, DWORD)                                \
    A(_, __, typeId, false, DWORD)                               \
    A(_, __, uavSlot, false, DWORD)                              \
    A(_, __, udtKind, false, DWORD, UdtKind)                     \
    A(_, __, unalignedType, false, BOOL)                         \
    A(_, __, undecoratedName, false, BSTR)                       \
    A(_, __, unmodifiedTypeId, false, DWORD)                     \
    A(_, __, upperBoundId, false, DWORD)                         \
    A(_, __, value, false, VARIANT)                              \
    A(_, __, virtual, false, BOOL)                               \
    A(_, __, virtualAddress, false, ULONGLONG)                   \
    A(_, __, virtualBaseClass, false, BOOL)                      \
    A(_, __, virtualBaseDispIndex, false, DWORD)                 \
    A(_, __, virtualBaseOffset, false, DWORD)                    \
    A(_, __, virtualBasePointerOffset, false, LONG)              \
    A(_, __, virtualTableShapeId, false, DWORD)                  \
    A(_, __, volatileType, false, BOOL)

#define DUMP_TOPIC(_, __, x, ...) \
    dump_##x

#define DEFINE_DUMP_TOPIC(_, __, x, ...) \
    static bool DUMP_TOPIC(_, __, x) = false;

#define DUMP_PROPERTY(topic, __, x, ...) \
    dump_##topic##_##x

#define DEFINE_DUMP_PROPERTY(topic, __, x, default, ...) \
    static bool DUMP_PROPERTY(topic, __, x) = default;

#define DEFINE_DUMP_ALL_PROPERTIES(_, __, x, ...) \
    x##_PROPERTY(x, __, DEFINE_DUMP_PROPERTY)

#define OR_DUMP_PROPERTY(topic, __, x, ...) \
    || DUMP_PROPERTY(topic, __, x)

#define CALC_DUMP_TOPIC(_, __, x, ...) \
    DUMP_TOPIC(_, __, x) = false x##_PROPERTY(x, __, OR_DUMP_PROPERTY);

#define PROPERTY_FQNAME(topic, name, x, ...) \
    L#name "::" #x

#define MATCH_PROPERTY(topic, name, x, ...)                                 \
    if (std::regex_match(PROPERTY_FQNAME(topic, name, x), m, re) == true) { \
        DUMP_PROPERTY(topic, __, x) = sign;                                 \
    }

#define MATCH_ALL_PROPERTIES(_, __, x, name, ...) \
    x##_PROPERTY(x, name, MATCH_PROPERTY)

#define SQLITE3_TYPE_BOOL "INTEGER"
#define SQLITE3_TYPE_DWORD "INTEGER"
#define SQLITE3_TYPE_LONG "INTEGER"
#define SQLITE3_TYPE_ULONGLONG "INTEGER"
#define SQLITE3_TYPE_GUID "TEXT"
#define SQLITE3_TYPE_BSTR "TEXT"
#define SQLITE3_TYPE_VARIANT "TEXT"

#define SQLITE3_CREATE_COLUMN(topic, __, x, default, type, ...)   \
    if (DUMP_PROPERTY(topic, __, x) == true) {                    \
        wprintf(L"  " #x " " SQLITE3_TYPE_##type " NOT NULL,\n"); \
    }

#define SQLITE3_CREATE_TABLE(_, __, x, name, ...)                \
    if (DUMP_TOPIC(_, __, x) == true) {                          \
        wprintf(L"CREATE TABLE " #name " (\n");                  \
        wprintf(L"  pdbId INTEGER NOT NULL,\n");                 \
        x##_PROPERTY(x, __, SQLITE3_CREATE_COLUMN);              \
        wprintf(L"  FOREIGN KEY (pdbId) REFERENCES pdb (id)\n"); \
        wprintf(L");\n");                                        \
        wprintf(L"\n");                                          \
    }

#define OPTION(_, __, A)                      \
    A(_, __, L"--help", show_help = true;)    \
    A(_, __, L"--json", format = JSON;)       \
    A(_, __, L"--xml", format = XML;)         \
    A(_, __, L"--sqlite3", format = SQLITE3;) \
    A(_, __, L"--names", use_names = true;)

#define OPTION_HANDLER(_, __, x, handler, ...) \
    if (wcscmp(x, argv[i]) == 0) {             \
        handler;                               \
    } else

#define OPTION_HANDLER_DUMMY(_, __, x, ...) \
    if (wcscmp(x, argv[i]) == 0) {          \
    } else
