#pragma once
#include <windows.h>

typedef
VOID
(NTAPI *PPS_APC_ROUTINE)(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);

typedef
NTSTATUS
(NTAPI* PNT_QUEUE_APC_THREAD)(
	HANDLE ThreadHandle,
	PPS_APC_ROUTINE ApcRoutine,
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);


typedef enum _QUEUE_USER_APC_FLAGS {
	QueueUserApcFlagsNone,
	QueueUserApcFlagsSpecialUserApc,
	QueueUserApcFlagsMaxValue
} QUEUE_USER_APC_FLAGS;


typedef union _USER_APC_OPTION {
	ULONG_PTR UserApcFlags;
	HANDLE MemoryReserveHandle;
} USER_APC_OPTION, * PUSER_APC_OPTION;


typedef 
NTSTATUS
(NTAPI* PNT_QUEUE_APC_THREAD_EX)(
	IN HANDLE ThreadHandle,
	IN USER_APC_OPTION UserApcOption,
	IN PPS_APC_ROUTINE ApcRoutine,
	IN PVOID SystemArgument1 OPTIONAL,
	IN PVOID SystemArgument2 OPTIONAL,
	IN PVOID SystemArgument3 OPTIONAL
	);


typedef
NTSTATUS
(NTAPI* PNT_GET_NEXT_THREAD)(
	_In_ HANDLE ProcessHandle,
	_In_ HANDLE ThreadHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ ULONG HandleAttributes,
	_In_ ULONG Flags,
	_Out_ PHANDLE NewThreadHandle
	);


typedef 
HMODULE
(NTAPI* PLOAD_LIBRARY_A)(
	PCSTR LibraryName
	);


typedef struct _UNICODE_STRING *PUNICODE_STRING;

typedef
HMODULE
(NTAPI* PLDR_LOAD_DLL)(
	PWCHAR PathToFile,
	ULONG Flags,
	PUNICODE_STRING ModuleFileName,
	PHANDLE ModuleHandle
	);


extern PNT_GET_NEXT_THREAD NtGetNextThread;
extern PNT_QUEUE_APC_THREAD NtQueueApcThread;
extern PNT_QUEUE_APC_THREAD_EX NtQueueApcThreadEx;
extern PLOAD_LIBRARY_A LoadLibraryAPtr;
extern PLDR_LOAD_DLL LdrLoadDllPtr;
extern PNT_QUEUE_APC_THREAD RtlQueueApcWow64Thread;

VOID
InitializeApcLib(
	VOID
	);


PVOID
WriteLibraryNameToRemote(
	HANDLE ProcessHandle,
	PCSTR Library
	);


VOID
OpenTargetHandles(
	__in ULONG ProcessId,
	__in_opt ULONG ThreadId,
	__out PHANDLE ProcessHandle,
	__out PHANDLE ThreadHandle
	);

BOOLEAN
Is32bitDll(
	PCSTR DllFilePath
	);


BOOLEAN
Is32BitProcess(
	HANDLE ProcessHandle
	);

ULONG
GetExportOffset(
	PCSTR LibraryPath,
	PCSTR ExportName
	);

ULONG64
DecodeWow64ApcRoutine(
	ULONG64 ApcRoutine
	);

ULONG64
EncodeWow64ApcRoutine(
	ULONG64 ApcRoutine
	);

PVOID 
QueryWow64LoadLibraryAddress(
	HANDLE ProcessHandle
	);

PVOID
WriteUnicodeLibraryNameToRemote(
	HANDLE ProcessHandle,
	PCSTR Library
	);



PWSTR
AsciiStringToUnicodeString(
	PCSTR AsciiString
	);

