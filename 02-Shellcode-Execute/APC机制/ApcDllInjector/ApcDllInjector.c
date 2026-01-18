#include <Windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ApcLib/ApcLib.h>


typedef enum _APC_TYPE {
	ApcTypeWin32,
	ApcTypeNative,
	ApcTypeSpecial
} APC_TYPE;

typedef struct _APC_INJECTOR_ARGS {
	APC_TYPE ApcType;
	PCSTR DllPath;
	ULONG ProcessId;
	ULONG ThreadId;
} APC_INJECTOR_ARGS, * PAPC_INJECTOR_ARGS;

VOID
ParseArguments(
	__in int ArgumentCount,
	__in const char** Arguments,
	__out PAPC_INJECTOR_ARGS Args)
{
	if (ArgumentCount < 4) {
		printf("Missing arguments!\n");
		printf("ApcDllInjector.exe <native/win32/special> <process_id> <dll_path> [thread_id]\n");
		exit(-1);
	}

	Args->ProcessId = atoi(Arguments[2]);
	Args->DllPath = Arguments[3];
	Args->ThreadId = 0;
	Args->ApcType = ApcTypeWin32;

	if (ArgumentCount > 4) {
		Args->ThreadId = atoi(Arguments[4]);
	}

	if (strcmp(Arguments[1], "native") == 0) {
		Args->ApcType = ApcTypeNative;
	}
	else if (strcmp(Arguments[1], "win32") == 0) {
		Args->ApcType = ApcTypeWin32;
	}
	else if (strcmp(Arguments[1], "special") == 0) {
		Args->ApcType = ApcTypeSpecial;
	}
	else {
		printf("Invalid injection mode '%s'\n", Arguments[1]);
		exit(-1);
	}
}

int main(int argc, const char** argv) {

	APC_INJECTOR_ARGS Args;
	NTSTATUS Status;
	HANDLE ThreadHandle;
	HANDLE ProcessHandle;
	PVOID RemoteLibraryAddress;

	InitializeApcLib();

	ParseArguments(argc, argv, &Args);

	OpenTargetHandles(
			Args.ProcessId,
			Args.ThreadId,
			&ProcessHandle,
			&ThreadHandle
		);

	RemoteLibraryAddress = WriteLibraryNameToRemote(ProcessHandle, Args.DllPath);


	switch (Args.ApcType) {
	case ApcTypeWin32: {
		if (!QueueUserAPC((PAPCFUNC)LoadLibraryAPtr, ThreadHandle, (ULONG_PTR)RemoteLibraryAddress)) {
			printf("QueueUserAPC Error! 0x%08X\n", GetLastError());
			exit(-1);
		}
	}
					   break;
	case ApcTypeNative: {
		Status = NtQueueApcThread(
			ThreadHandle,
			(PPS_APC_ROUTINE)LoadLibraryAPtr,
			RemoteLibraryAddress,
			NULL,
			NULL
		);

		if (!NT_SUCCESS(Status)) {
			printf("NtQueueApcThread Failed: 0x%08X\n", Status);
			exit(-1);
		}
	}
						break;
	case ApcTypeSpecial: {
		USER_APC_OPTION UserApcOption;
		UserApcOption.UserApcFlags = QueueUserApcFlagsSpecialUserApc;

		Status = NtQueueApcThreadEx(
			ThreadHandle,
			UserApcOption,
			(PPS_APC_ROUTINE)LoadLibraryAPtr,
			RemoteLibraryAddress,
			NULL,
			NULL
		);

		if (!NT_SUCCESS(Status)) {
			printf("NtQueueApcThreadEx Failed: 0x%08X\n", Status);
			exit(-1);
		}
	}
						 break;
	default:
		break;
	}

	return 0;
}