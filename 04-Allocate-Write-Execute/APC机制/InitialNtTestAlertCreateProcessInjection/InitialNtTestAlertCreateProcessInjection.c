#include <Windows.h>
#include <winternl.h>
#include <stdio.h>

typedef
VOID
(*PPS_APC_ROUTINE)(
	PVOID SystemArgument1,
	PVOID SystemArgument2,
	PVOID SystemArgument3
	);

typedef
NTSTATUS
(NTAPI* PNT_QUEUE_APC_THREAD)(
	IN HANDLE ThreadHandle,
	IN PPS_APC_ROUTINE ApcRoutine,
	IN PVOID SystemArgument1 OPTIONAL,
	IN PVOID SystemArgument2 OPTIONAL,
	IN PVOID SystemArgument3 OPTIONAL
	);


PVOID WriteLibraryNameToRemote(
	HANDLE ProcessHandle,
	PCWSTR Library
);

PNT_QUEUE_APC_THREAD NtQueueApcThread;

int
main(
	VOID
	)
{
	PROCESS_INFORMATION ProcessInformation;
	STARTUPINFO StartupInfo;
	PVOID LdrLoadDll;
	PVOID RemoteLibAddress;
	NTSTATUS Status;

	NtQueueApcThread = (PNT_QUEUE_APC_THREAD)(GetProcAddress(GetModuleHandle("ntdll"), "NtQueueApcThread"));
	LdrLoadDll = GetProcAddress(GetModuleHandle("ntdll"), "LdrLoadDll");

	RtlZeroMemory(&StartupInfo, sizeof(StartupInfo));
	RtlZeroMemory(&ProcessInformation, sizeof(PROCESS_INFORMATION));

	StartupInfo.cb = sizeof(StartupInfo);

	if (!CreateProcessA(
		"c:\\windows\\system32\\write.exe",
		NULL, NULL, NULL, FALSE,
		CREATE_SUSPENDED,
		NULL, NULL,
		&StartupInfo,
		&ProcessInformation
	)){
		printf("Error creating new process: 0x%08X\n", GetLastError());
		exit(-1);
	}


	RemoteLibAddress = WriteLibraryNameToRemote(ProcessInformation.hProcess, L"jscript.dll");

	Status = NtQueueApcThread(
				ProcessInformation.hThread, 
				(PPS_APC_ROUTINE)LdrLoadDll, 
				NULL, // PathToFile
				0,  // Flags
				RemoteLibAddress // ModuleFileName
				//
				// ModuleHandle is written to the _CONTEXT structure passed
				// to KiUserApcDispatcher.
				//
			);

	if (!NT_SUCCESS(Status)) {
		printf("NtQueueApcThread 0x%08X\n", Status);
	}

	ResumeThread(ProcessInformation.hThread);
}

PVOID WriteLibraryNameToRemote(
	HANDLE ProcessHandle,
	PCWSTR Library
)
{
	USHORT LibraryLength = (USHORT)(wcslen(Library) * sizeof(WCHAR));
	USHORT AllocationLength = LibraryLength+1+sizeof(UNICODE_STRING);

	PVOID LibraryRemoteAddress = VirtualAllocEx(
		ProcessHandle,
		NULL,
		AllocationLength,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE
	);

	if (!LibraryRemoteAddress) {
		printf("Cannot allocate memory for library path. Error: 0x%08X\n", GetLastError());
		exit(-1);
	}
	PUNICODE_STRING LocalUnicodeString = (PUNICODE_STRING)HeapAlloc(GetProcessHeap(), 0, AllocationLength);

	if (LocalUnicodeString == NULL) {
		exit(-1);
	}

	RtlZeroMemory(LocalUnicodeString, AllocationLength);
	
	LocalUnicodeString->MaximumLength = LibraryLength;
	LocalUnicodeString->Length = LibraryLength;
	LocalUnicodeString->Buffer = (PWCHAR) (((PUCHAR)LibraryRemoteAddress)+sizeof(UNICODE_STRING));
	
	RtlCopyMemory((((PUCHAR)LocalUnicodeString)+sizeof(UNICODE_STRING)), Library, LibraryLength);

	if (!WriteProcessMemory(
		ProcessHandle,
		LibraryRemoteAddress,
		LocalUnicodeString,
		sizeof(UNICODE_STRING) + LibraryLength + 1,
		NULL
	)) {
		printf("Cannot write library path to remote process. Error: 0x%08X\n", GetLastError());
		exit(-1);
	}

	return LibraryRemoteAddress;
}