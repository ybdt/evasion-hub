#include <ApcLib/ApcLib.h>
#include <stdio.h>
#include <winternl.h>

typedef struct _X64_TO_WOW64_CMD_ARGS {
	PCSTR DllPath;
	ULONG TargetProcessId;
	ULONG TargetThreadId;
} X64_TO_WOW64_CMD_ARGS, *PX64_TO_WOW64_CMD_ARGS;

X64_TO_WOW64_CMD_ARGS 
ParseArguments(
	int argc,
	const char** argv
	)
{
	X64_TO_WOW64_CMD_ARGS Args;
	RtlZeroMemory(&Args, sizeof(Args));

	if (argc < 3) {
		printf("Missing arguments.\n");
		printf("x64ToWow64ApcInjector.exe <dll_path> <process_id> <thread_id>\n");
		exit(-1);
	}

	Args.DllPath = argv[1];
	Args.TargetProcessId = atoi(argv[2]);

	if (argc >= 4) {
		Args.TargetThreadId = atoi(argv[3]);
	}

	return Args;
}

int main(
	int argc,
	const char** argv
	)
{
	NTSTATUS Status;
	HANDLE ProcessHandle;
	HANDLE ThreadHandle;
	BOOL IsWow64;
	PVOID RemoteLibraryPath;
	PVOID LoadLibraryAWowAddress;
	
	InitializeApcLib();

	X64_TO_WOW64_CMD_ARGS Args = ParseArguments(argc, argv);

	OpenTargetHandles(
		Args.TargetProcessId,
		Args.TargetThreadId,
		&ProcessHandle,
		&ThreadHandle
	);

	if (!IsWow64Process(ProcessHandle, &IsWow64)) {
		printf("IsWow64Process Failed. 0x%08X\n", GetLastError());
		exit(-1);
	}

	if (!IsWow64) {
		printf("Target process is not a wow64 process.\n");
		exit(-1);
	}


	//
	// Ok now we have 2 choices:
	//
	// - If the DLL is a 32 bit DLL, we need to create a Wow64 APC
	// - If the DLL is a 64 bit DLL, we need to create a normal APC to ntdll,
	//   because the 64 bit kernel32 is not loaded.
	//

	if (Is32bitDll(Args.DllPath)) {
		//
		// The DLL we want to load is a 32 bit DLL.
		// First, we need to write the path of the library to the remote process.
		//
		RemoteLibraryPath = WriteLibraryNameToRemote(ProcessHandle, Args.DllPath);

		//
		// To load this library, we can use the 32 bit LoadLibraryA routine inside kernel32.
		// To find the address of this routine, we can do the following:
		//	- Parse the kernel32.dll DLL from disk and find the offset of LoadLibraryA from the ImageBase.
		//	- Find the base of this DLL using EnumProcessModules and add the offset.
		//
		LoadLibraryAWowAddress = QueryWow64LoadLibraryAddress(ProcessHandle);
		
		//
		// Because the APC needs to run in a Wow64 environment, we need to encode the routine.
		//
		PPS_APC_ROUTINE ApcRoutine = (PPS_APC_ROUTINE)EncodeWow64ApcRoutine((ULONG64)LoadLibraryAWowAddress);

		//
		// Use NtQueueApcThread to queue the APC.
		//
		Status = NtQueueApcThread(
			ThreadHandle,
			ApcRoutine,
			RemoteLibraryPath,
			NULL,
			NULL
		);

		/*
		ntdll has a routine called "RtlQueueApcWow64Thread" which can be used to perform the encoding.

		Status = RtlQueueApcWow64Thread(
					ThreadHandle,
					LoadLibraryAWowAddress,
					RemoteLibraryPath,
					NULL,
					NULL
				);
		*/
	}
	else {
		//
		// The DLL is a 64 bit DLL and we want to load it to a 32 bit process.
		// We can use ntdll!LdrLoadDll to do it.
		//
		RemoteLibraryPath = WriteUnicodeLibraryNameToRemote(ProcessHandle, Args.DllPath);

		Status = NtQueueApcThread(
			ThreadHandle,
			(PPS_APC_ROUTINE)LdrLoadDllPtr,
			NULL,
			0,
			RemoteLibraryPath
		);
	}

	if (!NT_SUCCESS(Status)){
		printf("NtQueueApcThread Failed. 0x%08X\n", GetLastError());
		exit(-1);
	}
}