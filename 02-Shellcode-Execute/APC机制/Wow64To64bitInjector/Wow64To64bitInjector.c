#include <ApcLib/ApcLib.h>
#include <stdio.h>
#include <winternl.h>
#include "x64Call.h"

typedef struct _WOW64_TO_64BIT_INJECTOR_ARGS {
	PCSTR DllPath;
	ULONG TargetProcessId;
	ULONG TargetThreadId;
} WOW64_TO_64BIT_INJECTOR_ARGS, *PWOW64_TO_64BIT_INJECTOR_ARGS;


VOID 
ParseArguments(
	__in int argc, 
	__in const char** argv,
	__out PWOW64_TO_64BIT_INJECTOR_ARGS Args
	)
{
	argc--;
	argv++;

	RtlZeroMemory(Args, sizeof(WOW64_TO_64BIT_INJECTOR_ARGS));

	if (argc < 2) {
		printf("Wow64To64bitInjector.exe <dll_path> <process_id> [thread_id]\n");
		exit(-1);
	}

	Args->DllPath = argv[0];
	Args->TargetProcessId = atoi(argv[1]);

	if (argc >= 3) {
		Args->TargetProcessId = atoi(argv[2]);
	}
}

__declspec(align(16))
typedef struct _NT_QUEUE_APC_THREAD_ARGS {
	DWORD64 ThreadHandle;
	DWORD64 ApcRoutine;
	DWORD64 SystemArgument1;
	DWORD64 SystemArgument2;
	DWORD64 SystemArgument3;
} NT_QUEUE_APC_THREAD_ARGS, *PNT_QUEUE_APC_THREAD_ARGS;


int main(int argc, const char** argv)
{
	NTSTATUS Status;
	HANDLE ProcessHandle;
	HANDLE ThreadHandle;
	WOW64_TO_64BIT_INJECTOR_ARGS Args;
	NT_QUEUE_APC_THREAD_ARGS QueueApcArgs;
	PVOID RemoteLibraryPath;
	DWORD64 NtQueueApcThreadAddress;

	RtlZeroMemory(&QueueApcArgs, sizeof(QueueApcArgs));
	
	InitializeApcLib();

	ParseArguments(argc, argv, &Args);
	
	OpenTargetHandles(Args.TargetProcessId, Args.TargetThreadId, &ProcessHandle, &ThreadHandle);

	//
	// Write the path of the DLL to the remote process
	//
	RemoteLibraryPath = WriteUnicodeLibraryNameToRemote(ProcessHandle, Args.DllPath);

	//
	// Save the 64 bit arguments on a struct
	//
	QueueApcArgs.ThreadHandle = (DWORD64)ThreadHandle;
	QueueApcArgs.ApcRoutine = x64_GetNtdllProcedure("LdrLoadDll");
	QueueApcArgs.SystemArgument1 = 0;
	QueueApcArgs.SystemArgument2 = 0;
	QueueApcArgs.SystemArgument3 = (DWORD64)RemoteLibraryPath;
	
	//
	// Find the address of the system call routine in NTDLL
	//
	NtQueueApcThreadAddress = x64_GetSyscallAddress("NtQueueApcThread");

	//
	// Invoke the system call
	//
	Status = x64_InvokeSyscall(NtQueueApcThreadAddress, &QueueApcArgs, sizeof(QueueApcArgs));

	if (!NT_SUCCESS(Status)) {
		printf("NtQueueApcThread Error: 0x%08X\n", Status);
		return -1;
	}


}